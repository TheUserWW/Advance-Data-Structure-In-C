# 动态数组库文档

## 概述

本动态数组库提供了一种类似C++ vector的泛型容器实现，支持自动扩容、随机访问、插入删除等操作。所有函数均为内联实现，具有高性能和低开销的特点。

## 数据结构

```c
typedef struct {
    void *data;          // 数据存储指针
    size_t size;         // 当前元素数量
    size_t capacity;     // 当前存储容量
    size_t element_size; // 单个元素大小(字节)
} DynamicArray;
```

## API 参考

### 初始化与销毁

#### `dynamic_array_init`

```c
bool dynamic_array_init(DynamicArray *da, size_t element_size, size_t initial_capacity);
```

- **功能**：初始化动态数组
- **参数**：
  - `da`: 动态数组指针
  - `element_size`: 单个元素大小(字节)
  - `initial_capacity`: 初始容量
- **返回**：成功返回`true`，失败返回`false`
- **时间复杂度**：O(1)
- **空间复杂度**：O(n)，n=initial_capacity

#### `dynamic_array_destroy`

```c
void dynamic_array_destroy(DynamicArray *da);
```

- **功能**：释放动态数组内存
- **参数**：
  - `da`: 动态数组指针
- **时间复杂度**：O(1)
- **空间复杂度**：O(1)

### 容量管理

#### `dynamic_array_reserve`

```c
bool dynamic_array_reserve(DynamicArray *da, size_t new_capacity);
```

- **功能**：预分配存储空间
- **参数**：
  - `da`: 动态数组指针
  - `new_capacity`: 新的容量大小
- **返回**：成功返回`true`，失败返回`false`
- **时间复杂度**：O(n)，n=当前元素数量
- **空间复杂度**：O(n)，n=new_capacity

#### `dynamic_array_clear`

```c
void dynamic_array_clear(DynamicArray *da);
```

- **功能**：清空数组（保留容量）
- **参数**：
  - `da`: 动态数组指针
- **时间复杂度**：O(1)
- **空间复杂度**：O(1)

### 元素访问

#### `dynamic_array_get`

```c
void* dynamic_array_get(const DynamicArray *da, size_t index);
```

- **功能**：获取元素指针
- **参数**：
  - `da`: 动态数组指针
  - `index`: 元素索引
- **返回**：指向元素的指针，索引无效返回`NULL`
- **时间复杂度**：O(1)
- **空间复杂度**：O(1)

#### `dynamic_array_size`

```c
size_t dynamic_array_size(const DynamicArray *da);
```

- **功能**：获取元素数量
- **参数**：
  - `da`: 动态数组指针
- **返回**：当前元素数量
- **时间复杂度**：O(1)
- **空间复杂度**：O(1)

### 修改操作

#### `dynamic_array_push_back`

```c
bool dynamic_array_push_back(DynamicArray *da, const void *element);
```

- **功能**：在末尾添加元素
- **参数**：
  - `da`: 动态数组指针
  - `element`: 要添加的元素指针
- **返回**：成功返回`true`，失败返回`false`
- **时间复杂度**：
  - 平均情况：O(1)
  - 最坏情况（需要扩容）：O(n)，n=当前元素数量
- **空间复杂度**：
  - 平均情况：O(1)
  - 最坏情况：O(n)，n=新容量

#### `dynamic_array_insert`

```c
bool dynamic_array_insert(DynamicArray *da, size_t index, const void *element);
```

- **功能**：在指定位置插入元素
- **参数**：
  - `da`: 动态数组指针
  - `index`: 插入位置索引
  - `element`: 要插入的元素指针
- **返回**：成功返回`true`，失败返回`false`
- **时间复杂度**：
  - 平均情况：O(n)，n=size-index
  - 最坏情况（需要扩容）：O(n)，n=当前元素数量
- **空间复杂度**：
  - 平均情况：O(1)
  - 最坏情况：O(n)，n=新容量

#### `dynamic_array_remove_at`

```c
bool dynamic_array_remove_at(DynamicArray *da, size_t index);
```

- **功能**：删除指定位置的元素
- **参数**：
  - `da`: 动态数组指针
  - `index`: 要删除的元素索引
- **返回**：成功返回`true`，失败返回`false`
- **时间复杂度**：O(n)，n=size-index-1
- **空间复杂度**：O(1)

### 算法操作

#### `dynamic_array_find`

```c
int dynamic_array_find(const DynamicArray *da, const void *element, 
                     int (*compare)(const void*, const void*));
```

- **功能**：查找元素
- **参数**：
  - `da`: 动态数组指针
  - `element`: 要查找的元素指针
  - `compare`: 比较函数
- **返回**：找到返回索引，未找到返回-1
- **时间复杂度**：O(n)，n=元素数量
- **空间复杂度**：O(1)

#### `dynamic_array_sort`

```c
void dynamic_array_sort(DynamicArray *da, int (*compare)(const void*, const void*));
```

- **功能**：排序数组
- **参数**：
  - `da`: 动态数组指针
  - `compare`: 比较函数
- **时间复杂度**：O(n log n)，n=元素数量
- **空间复杂度**：取决于qsort实现，通常O(log n)

## 复杂度总结

| 操作                 | 时间复杂度          | 空间复杂度          |
|----------------------|---------------------|---------------------|
| init                 | O(1)                | O(n)                |
| destroy              | O(1)                | O(1)                |
| reserve              | O(n)                | O(n)                |
| clear                | O(1)                | O(1)                |
| get                  | O(1)                | O(1)                |
| size                 | O(1)                | O(1)                |
| push_back (平均)     | O(1)                | O(1)                |
| push_back (最坏)     | O(n)                | O(n)                |
| insert (平均)        | O(n)                | O(1)                |
| insert (最坏)        | O(n)                | O(n)                |
| remove_at            | O(n)                | O(1)                |
| find                 | O(n)                | O(1)                |
| sort                 | O(n log n)          | O(log n)            |

## 最佳实践

1. **初始容量选择**：根据预估数据量设置合理的初始容量，避免频繁扩容
2. **批量操作**：预先调用`reserve`预留足够空间，减少重新分配次数
3. **元素访问**：使用`dynamic_array_get`获取指针后，转换为正确的类型
4. **自定义比较**：排序和查找需要提供适当的比较函数

## 示例代码

```c
#include "dynamic_array.h"
#include <stdio.h>

// 比较函数
int compare_int(const void *a, const void *b) {
    return *(const int*)a - *(const int*)b;
}

int main() {
    DynamicArray da;
    dynamic_array_init(&da, sizeof(int), 10); // 初始容量10

    // 添加元素
    for (int i = 0; i < 20; i++) {
        int val = 20 - i;
        dynamic_array_push_back(&da, &val);
    }

    // 排序
    dynamic_array_sort(&da, compare_int);

    // 查找
    int target = 10;
    int idx = dynamic_array_find(&da, &target, compare_int);
    if (idx != -1) {
        printf("Found %d at index %d\n", target, idx);
    }

    // 遍历
    for (size_t i = 0; i < dynamic_array_size(&da); i++) {
        printf("%d ", *(int*)dynamic_array_get(&da, i));
    }

    dynamic_array_destroy(&da);
    return 0;
}
```

## 限制与注意事项

1. 不是线程安全的，多线程环境需要外部同步
2. 元素必须是POD(Plain Old Data)类型，不支持需要构造/析构的复杂对象
3. 错误处理较为简单，调用者需要检查返回值
