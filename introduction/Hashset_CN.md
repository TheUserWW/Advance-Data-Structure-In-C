# 哈希集合库文档

本文件提供了高性能哈希集合实现的详细文档，包含每个函数的使用示例。

## 概述

该哈希集合是一个使用链地址法解决冲突的动态哈希表实现。主要特性包括：
- 自动扩容机制
- 支持泛型数据类型
- 预定义整数和字符串类型支持
- 自定义哈希函数和比较函数
- 内存安全释放

## 常量定义

- `HASHSET_INIT_CAPACITY` (101): 默认初始容量(质数)
- `HASHSET_MAX_LOAD` (0.7): 触发扩容的最大负载因子

## 预定义类型支持

### 整数类型支持
```c
size_t int_hash(const void* data);      // 整数哈希函数
bool int_compare(const void* a, const void* b);  // 整数比较函数
```

### 字符串类型支持
```c
size_t str_hash(const void* data);      // 字符串哈希函数
bool str_compare(const void* a, const void* b);  // 字符串比较函数
void str_free(void* data);              // 字符串内存释放函数
```

## API参考

### hashset_create

创建新的哈希集合。

**参数:**
- `data_size`: 数据类型大小(字节)
- `hash_func`: 哈希函数指针
- `compare_func`: 比较函数指针
- `free_func`: 数据释放函数指针(可为NULL)

**返回值:**
- 新哈希集合指针，失败返回NULL

**示例:**
```c
// 创建整数集合
HashSet* intSet = hashset_create(sizeof(int), int_hash, int_compare, NULL);

// 创建字符串集合
HashSet* strSet = hashset_create(sizeof(char*), str_hash, str_compare, str_free);

// 创建自定义类型集合
typedef struct { int x; int y; } Point;
size_t point_hash(const void* p) { /*...*/ }
bool point_compare(const void* a, const void* b) { /*...*/ }
HashSet* pointSet = hashset_create(sizeof(Point), point_hash, point_compare, NULL);
```

### 便捷宏

```c
HASHSET_INT()    // 创建整数集合
HASHSET_STR()    // 创建字符串集合
HASHSET_CUSTOM(type, hash_fn, cmp_fn, free_fn)  // 创建自定义类型集合
```

**示例:**
```c
HashSet* intSet = HASHSET_INT();
HashSet* strSet = HASHSET_STR();
```

### hashset_add

向集合中添加元素。

**参数:**
- `set`: 哈希集合指针
- `data`: 要添加的数据指针

**返回值:**
- 成功添加返回true，已存在或失败返回false

**示例:**
```c
HashSet* set = HASHSET_INT();
int num = 42;
hashset_add(set, &num);  // 添加整数42

HashSet* strSet = HASHSET_STR();
char* name = "Alice";
hashset_add(strSet, &name);  // 添加字符串指针
```

### hashset_add_str

便捷函数，添加字符串(自动复制)。

**参数:**
- `set`: 哈希集合指针
- `str`: 要添加的字符串

**返回值:**
- 成功添加返回true，已存在或失败返回false

**示例:**
```c
HashSet* set = HASHSET_STR();
hashset_add_str(set, "Hello");
hashset_add_str(set, "World");
```

### hashset_add_all

批量添加元素数组。

**参数:**
- `set`: 哈希集合指针
- `data`: 元素数组指针
- `count`: 元素数量

**返回值:**
- 全部添加成功返回true，任意失败返回false

**示例:**
```c
HashSet* set = HASHSET_INT();
int numbers[] = {1, 2, 3, 4, 5};
hashset_add_all(set, numbers, 5);
```

### hashset_contains

检查集合是否包含指定元素。

**参数:**
- `set`: 哈希集合指针
- `data`: 要查找的数据指针

**返回值:**
- 存在返回true，不存在返回false

**示例:**
```c
HashSet* set = HASHSET_INT();
int num = 42;
hashset_add(set, &num);

if (hashset_contains(set, &num)) {
    printf("集合包含%d\n", num);
}
```

### hashset_free

释放哈希集合及其所有元素。

**参数:**
- `set`: 哈希集合指针

**示例:**
```c
HashSet* set = HASHSET_STR();
hashset_add_str(set, "Test");
hashset_free(set);  // 正确释放所有内存
```

## 内部函数

### resize

当负载因子超过阈值时自动扩容哈希表。

**参数:**
- `set`: 哈希集合指针

**注意:**
- 自动调用，无需手动调用
- 容量总是扩展为质数以减少哈希冲突

## 使用说明

1. 对于字符串集合，必须使用`HASHSET_STR()`或指定`str_free`作为释放函数
2. 自定义类型需要提供适当的哈希函数和比较函数
3. 集合不保证元素的顺序
4. 线程不安全，多线程环境需要外部同步
5. 扩容操作可能较慢，预估大小时可适当增大初始容量

## 内存管理

- 添加元素时会自动复制数据
- 释放集合时会递归释放所有节点和数据
- 字符串类型会深度释放字符串内存
- 自定义类型需要提供适当的释放函数

## 性能考虑

- 负载因子设置为0.7以平衡空间和时间效率
- 使用质数容量减少哈希冲突
- 哈希函数使用乘法散列法(整数)和DJB2算法(字符串)
