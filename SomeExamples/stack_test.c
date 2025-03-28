#include "stack.h"

int main() {
    // 创建栈
    Stack* s1 = stack_create();
    Stack* s2 = stack_create();
    
    // 压入元素
    stack_push(s1, 10);
    stack_push(s1, 20);
    stack_push(s2, 30);
    
    // 获取栈信息
    printf("Stack 1 top: %d, size: %d\n", stack_top(s1), stack_size(s1));
    printf("Stack 2 top: %d, size: %d\n", stack_top(s2), stack_size(s2));
    
    // 交换栈
    stack_swap(s1, s2);
    printf("\nAfter swap:\n");
    printf("Stack 1 top: %d, size: %d\n", stack_top(s1), stack_size(s1));
    printf("Stack 2 top: %d, size: %d\n", stack_top(s2), stack_size(s2));
    
    // 释放栈
    stack_free(s1);
    stack_free(s2);
    
    return 0;
}