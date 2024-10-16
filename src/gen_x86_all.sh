#!/bin/bash


# 定义 -r 参数的值
r_values=("BFS" "PRIM" "SSSP")

postfix=""

# 遍历 r_values 数组并执行命令
for r in "${r_values[@]}"; do

    make OPERATION="$r" POSTFIX="$postfix" 

done

echo "所有可执行文件已生成。"

