# mtx_to_edge_list.py

import sys
import random

def mtx_to_edge_list(mtx_file, edge_file):
    with open(mtx_file, 'r') as f:
        lines = f.readlines()

    # 解析头部
    header = []
    idx = 0
    while lines[idx].startswith('%'):
        header.append(lines[idx].strip())
        idx += 1

    # 读取尺寸信息
    size_info = lines[idx].strip().split()
    num_rows, num_cols, num_nonzeros = map(int, size_info)
    idx += 1

    # 判断是否对称
    symmetric = False
    for line in header:
        if 'symmetric' in line.lower():
            symmetric = True
            break

    # 读取数据并转换为边列表
    edges = []
    for i in range(num_nonzeros):
        data = lines[idx + i].strip().split()
        if len(data) == 2:
            row, col = map(int, data)
            weight = 1  # 默认权重为1
        elif len(data) == 3:
            row, col, weight = data
            row = int(row)
            col = int(col)
            try:
                weight = float(weight)
            except ValueError:
                weight = weight  # 保留原始类型
        else:
            continue  # 忽略不符合格式的行
        edges.append((row, col, weight))

        #if row != col:
        #    edges.append((row, col, weight))

        #    if symmetric:
        #        edges.append((col, row, weight))  # 对称添加

    ## 去重（对于无向图）
    #if symmetric:
    #    unique_edges = set()
    #    for edge in edges:
    #        sorted_edge = tuple(sorted((edge[0], edge[1]))) + (edge[2],)
    #        unique_edges.add(sorted_edge)
    #    edges = list(unique_edges)

    # 写入边列表文件
    random.shuffle(edges)
    with open(edge_file, 'w') as f:
        for edge in edges:
            if len(edge) == 3:
                f.write(f"{edge[0]} {edge[1]} {edge[2]}\n")
            else:
                f.write(f"{edge[0]} {edge[1]}\n")

    print(f"转换完成！边列表已保存到 {edge_file}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("用法: python mtx_to_edge_list.py <输入.mtx> <输出.edge>")
        sys.exit(1)

    mtx_file = sys.argv[1]
    edge_file = sys.argv[2]
    mtx_to_edge_list(mtx_file, edge_file)
