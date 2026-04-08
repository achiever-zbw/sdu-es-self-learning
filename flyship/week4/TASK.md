# 任务

1. 动手搭建简单的智能体，实现工具的接入与调用
2. 动手搭建MCP server，为AI拓展新能力，设计提示词工程、MCP工具等
3. 在AI IDE中使用自然语言交互完成项目功能的添加。

---

# 关于 MCP Client 和 MCP Server

[https://zhuanlan.zhihu.com/p/1921247530034897084](https://zhuanlan.zhihu.com/p/1921247530034897084)

1. 用户输入 → MCP Client 接收用户的问题
2. Client 获取工具清单 → Client 向 MCP Server 请求可用工具列表
3. Server 返回工具清单 → Server 返回自己包含的工具和资源描述
4. Client 交给 LLM 决策 → Client 把用户问题 + 工具清单一起发给 LLM，让 LLM 决定是否需要调用工具
5. LLM 返回工具调用指令 → LLM 判断需要调用哪个工具，返回 tool_call 指令
6. Client 执行工具调用 → Client 根据 LLM 的指令，向 MCP Server 发起具体的工具调用请求
7. Server 执行并返回结果 → Server 执行工具（如查询天气、读写文件），把结果返回给 Client
8. LLM 整理最终回答 → Client 把工具执行结果交给 LLM，LLM 将其整理成自然语言回复
9. 展示给用户 → Client 把 LLM 整理好的回复展示给用户

# 步骤

- `uv version` 检查一下是否安装 uv第三方库，没有的话 `pip install uv` 进行安装
- `uv init mcp-server-demo` uv init 项目名字
- `uv add "mcp[cli]"`

- 安装完所有依赖，开始编写 Server 端的代码

Cursor、Trae、Claude Code 等都可以作为 MCP 的客户端，但是当我们需要在一个项目中集成一个自己的智能体，
就需要自己搭建一个 Client，配置自己的大模型和工具。