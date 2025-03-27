# 栈库文档

本文件提供了带交换功能的动态栈实现的详细文档。每个函数都包含演示其用法的示例。

## 概述

该栈是一个使用动态数组实现的后进先出(LIFO)数据结构。主要特性包括：
- 栈满时自动扩容
- 内存安全检查
- 栈交换功能
- 类型安全操作(针对整数)

## 常量定义

- `STACK_INIT_CAPACITY` (4): 默认初始容量
- `STACK_EXPAND_FACTOR` (2): 栈满时的扩容系数
- `STACK_EMPTY_VALUE` (-1): 栈空时的返回值

## API参考

### stack_create

创建具有指定初始容量的新栈。

**参数:**
- `initCapacity`: 初始容量(≤0时使用默认值)

**返回值:**
- 新栈指针，失败时返回NULL

**示例:**
```c
Stack *s = stack_create(10);  // 创建容量为10的栈
if (!s) {
    printf("栈创建失败\n");
    return;
}
// ... 使用栈 ...
stack_destroy(s);
```

### stack_destroy

销毁栈并释放其内存。

**参数:**
- `stack`: 栈指针(可安全传入NULL)

**示例:**
```c
Stack *s = stack_create(0);
// ... 使用栈 ...
stack_destroy(s);  // 正确清理
s = NULL;          // 销毁后设为NULL是良好实践
```

### stack_isEmpty

检查栈是否为空。

**参数:**
- `stack`: 要检查的栈指针

**返回值:**
- `true`表示栈为空或NULL，`false`表示非空

**示例:**
```c
Stack *s = stack_create(0);
if (stack_isEmpty(s)) {
    printf("栈为空(符合预期)\n");
}

stack_push(s, 42);
if (!stack_isEmpty(s)) {
    printf("栈不为空(符合预期)\n");
}
stack_destroy(s);
```

### stack_top

返回栈顶元素但不移除。

**参数:**
- `stack`: 栈指针

**返回值:**
- 栈顶元素，栈空/NULL时返回`STACK_EMPTY_VALUE`

**示例:**
```c
Stack *s = stack_create(0);
printf("空栈的栈顶: %d\n", stack_top(s));  // -1

stack_push(s, 10);
stack_push(s, 20);
printf("当前栈顶: %d\n", stack_top(s));  // 20
stack_destroy(s);
```

### stack_push

将元素压入栈中。

**参数:**
- `stack`: 栈指针
- `value`: 要压入的整数值

**返回值:**
- 成功返回`true`，失败返回`false`(NULL或分配失败)

**示例:**
```c
Stack *s = stack_create(2);  // 小容量用于演示
for (int i = 0; i < 5; i++) {
    if (!stack_push(s, i*10)) {
        printf("压入失败 i=%d\n", i);
        break;
    }
    printf("已压入: %d, 大小: %d, 容量: %d\n", 
           i*10, stack_size(s), s->capacity);
}
stack_destroy(s);
```

### stack_pop

移除并可选地返回栈顶元素。

**参数:**
- `stack`: 栈指针
- `pValue`: 存储弹出值的指针(可为NULL)

**返回值:**
- 成功弹出返回`true`，栈空/NULL返回`false`

**示例:**
```c
Stack *s = stack_create(0);
stack_push(s, 100);
stack_push(s, 200);

int val;
while (stack_pop(s, &val)) {
    printf("已弹出: %d\n", val);
}

if (!stack_pop(s, NULL)) {
    printf("没有更多元素可弹出(符合预期)\n");
}
stack_destroy(s);
```

### stack_size

返回栈中元素数量。

**参数:**
- `stack`: 栈指针

**返回值:**
- 元素数量(NULL或空栈时为0)

**示例:**
```c
Stack *s = stack_create(0);
printf("初始大小: %d\n", stack_size(s));  // 0

for (int i = 1; i <= 3; i++) {
    stack_push(s, i);
    printf("压入%d后的大小: %d\n", i, stack_size(s));
}
stack_destroy(s);
```

### stack_swap

高效交换两个栈的内容。

**参数:**
- `a`: 第一个栈指针
- `b`: 第二个栈指针

**注意:**
- 即使栈容量不同也能正常工作
- 任一指针为NULL时不执行任何操作

**示例:**
```c
Stack *a = stack_create(0);
Stack *b = stack_create(100);  // 不同容量

stack_push(a, 1);
stack_push(a, 2);
stack_push(b, 99);

printf("交换前 - A栈顶: %d, B栈顶: %d\n", stack_top(a), stack_top(b));
stack_swap(a, b);
printf("交换后 - A栈顶: %d, B栈顶: %d\n", stack_top(a), stack_top(b));

stack_destroy(a);
stack_destroy(b);
```

## 使用说明

1. 始终检查`stack_create`和`stack_push`的返回值
2. 销毁后将栈指针设为NULL
3. 该栈实现不是线程安全的
4. 生产环境中考虑添加错误日志
5. 实现使用`static`链接 - 仅在单个源文件中包含头文件，或多文件使用时移除`static`

## 内存管理

栈在满时会自动扩容(按`STACK_EXPAND_FACTOR`系数)，但不会自动缩容。如需可手动添加容量管理。

## 错误处理

函数返回布尔值表示成功/失败或特殊值(如`STACK_EMPTY_VALUE`)，而不是使用断言或异常。
