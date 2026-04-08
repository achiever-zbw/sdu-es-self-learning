from mcp.server import FastMCP
from pathlib import Path

# 初始化 mcp
mcp = FastMCP()

# 添加一个工具
@mcp.tool()
def list_files(path: str):
    """ 
    列出指定目录下的所有文件和子目录
    Args:
        path: 要列出的目录路径
    Returns:
        list: 文件和子目录列表
    """
    try:
        # 识别目录
        path = Path(path)
        if not path.exists():
            print(f"目录 {path} 不存在")
            return []
        
        results = []
        for item in path.iterdir():
            results.append({
                "name": item.name,
                "type" : "file" if item.is_file() else "directory",
                "size": item.stat().st_size if item.is_file() else 0 
            })
        return results
    except Exception as e:
        print(f"列出目录 {path} 失败: {e}")
        return []

if __name__ == "__main__":
    # 启动 mcp 服务器
    mcp.run()
