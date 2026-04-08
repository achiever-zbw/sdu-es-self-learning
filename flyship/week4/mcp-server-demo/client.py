import json
import os
import asyncio
from contextlib import AsyncExitStack
from typing import Optional
from dotenv import load_dotenv
from mcp import ClientSession, StdioServerParameters
from mcp.client.stdio import stdio_client
from openai import AsyncOpenAI


class MCPClient:
    def __init__(self):
        # self.session 用于存储与 MCP 服务器之间的会话，初始设为 None
        self.session: Optional[ClientSession] = None
        # self.exit_stack 用于管理异步资源的释放，比如关闭连接、清理资源等，确保所有资源在程序结束后能正确关闭
        self.exit_stack = AsyncExitStack()
        # self.client 是最关键的，用于创建 OpenAI 异步客户端，能够访问大语言模型，需要配置 URL 和 API 密钥
        self.client = AsyncOpenAI(
            base_url=os.getenv("BASE_URL"),
            api_key=os.getenv("OPENAI_API_KEY"),
        )
    
    # 服务器连接
    async def connect_to_server(self , server_path: str):
        """
        connect_to_server 方法用于与服务器建立连接，接受这个 server_path 参数，就是我们写的 server.py 文件的路径
        """
        # 配置启动服务器的参数
        server_params = StdioServerParameters(
            # 使用 python 命令启动服务器
            command = "python" , 
            # 传递 server.py 文件路径作为参数
            args = [server_path] ,
        )

        # 建立双向通信通道，确保 client 和 server 能够互相通信
        stdio_transport = await self.exit_stack.enter_async_context(stdio_client(server_params))
        self.stdio, self.write = stdio_transport

        # 创建并初始化会话
        self.session = await self.exit_stack.enter_async_context(ClientSession(self.stdio, self.write))
        await self.session.initialize()

        # 列出所有我们注册的工具
        response = await self.session.list_tools()
        tools = response.tools

        # 输出所有工具
        print("\n连接服务器，获取所有可用工具 :", [tool.name for tool in tools])

    # 处理用户的请求
    async def process_query(self, query: str) -> str:
        """使用 LLM 和 MCP 服务器提供的工具处理查询"""
        messages = [
            {
                "role": "user",
                "content": query
            }
        ]

        # 获取所有可用工具
        response = await self.session.list_tools()
        # 将工具转换为 OpenAI 格式
        available_tools = [{
            "type": "function",
            "function": {
                "name": tool.name,
                "description": tool.description,
                "parameters": tool.inputSchema
            }
        } for tool in response.tools]

        # 初始化 LLM API 调用
        response = await self.client.chat.completions.create(
            model=os.getenv("MODEL"),
            messages=messages,
            tools=available_tools
        )

        # 处理响应并处理工具调用
        final_text = []
        message = response.choices[0].message
        final_text.append(message.content or "")

        # 处理响应并处理工具调用
        while message.tool_calls:
            # 处理每个工具调用
            for tool_call in message.tool_calls:
                tool_name = tool_call.function.name
                tool_args = json.loads(tool_call.function.arguments)

                # 执行工具调用
                result = await self.session.call_tool(tool_name, tool_args)
                final_text.append(f"[Calling tool {tool_name} with args {tool_args}]")

                # 将工具调用和结果添加到消息历史
                messages.append({
                    "role": "assistant",
                    "tool_calls": [
                        {
                            "id": tool_call.id,
                            "type": "function",
                            "function": {
                                "name": tool_name,
                                "arguments": json.dumps(tool_args)
                            }
                        }
                    ]
                })
                messages.append({
                    "role": "tool",
                    "tool_call_id": tool_call.id,
                    "content": str(result.content)
                })

            # 将工具调用的结果交给 LLM，得到大语言模型处理后的结果
            response = await self.client.chat.completions.create(
                model=os.getenv("MODEL"),
                messages=messages,
                tools=available_tools
            )

            message = response.choices[0].message
            if message.content:
                final_text.append(message.content)

        return "\n".join(final_text)

    async def run(self):
        print("欢迎使用 MCP 客户端！")
        print("输入 'exit' 退出程序")
        while True:
            query = input("\n请输入你的问题: ")
            if query.lower() == "exit":
                print("再见！")
                break
            response = await self.process_query(query)
            print("\n响应:", response)


async def main() -> None:
    load_dotenv(".env")
    client = MCPClient()
    # 我们的 MCP 服务脚本
    server_script = str("mcp-server-demo/server.py")
    try:
        await client.connect_to_server(server_script)
        await client.run()
    finally:
        await client.exit_stack.aclose()


if __name__ == "__main__":
    asyncio.run(main())