# HashMap (C语言实现) 文档

---

## **概述**
这是一个用C语言实现的通用哈希表，支持字符串键（`char*`）和任意类型值的存储。采用**链地址法**解决哈希冲突，支持动态扩容，提供基本操作：插入、查询、删除和自动扩容。

---

## **复杂度分析**
### **时间复杂度**
| 操作       | 平均情况     | 最坏情况       |
|------------|-------------|---------------|
| `put`      | O(1)        | O(n)          |
| `get`      | O(1)        | O(n)          |
| `remove`   | O(1)        | O(n)          |
| `resize`   | O(n)        | O(n)          |

- **最坏情况**：当所有键的哈希值冲突时退化为链表操作
- **扩容操作**：触发时会重新哈希所有元素（O(n)）

### **空间复杂度**
- **总空间**：O(n + m)  
  - `n`：存储的元素数量
  - `m`：哈希表桶的数量（`capacity`）
- **每个元素**：额外存储链表指针（每个节点额外12-16字节）

---

## **API 文档**

### **1. 创建哈希表**
```c
HashMap* hashmap_create(int initial_capacity);
```
- **参数**：
  - `initial_capacity`：初始容量（若≤0则使用默认值16）
- **返回**：新哈希表指针，失败返回`NULL`
- **注意**：建议初始容量为2的幂以获得最佳性能

---

### **2. 销毁哈希表**
```c
void hashmap_destroy(HashMap* map);
```
- **参数**：
  - `map`：目标哈希表
- **行为**：
  - 释放所有键的内存（`free(key)`）
  - 释放所有节点和桶的内存
  - **不会释放值的内存**（需用户自行管理）

---

### **3. 插入/更新键值对**
```c
void hashmap_put(HashMap* map, const char* key, void* value);
```
- **参数**：
  - `map`：目标哈希表
  - `key`：字符串键（内部会复制该字符串）
  - `value`：任意类型值的指针
- **行为**：
  - 键已存在时更新值
  - 触发扩容条件：`size/capacity ≥ 0.75`

---

### **4. 获取值**
```c
void* hashmap_get(HashMap* map, const char* key);
```
- **参数**：
  - `map`：目标哈希表
  - `key`：要查找的键
- **返回**：找到则返回值的指针，否则返回`NULL`

---

### **5. 删除键值对**
```c
int hashmap_remove(HashMap* map, const char* key);
```
- **参数**：
  - `map`：目标哈希表
  - `key`：要删除的键
- **返回**：成功删除返回1，未找到返回0
- **行为**：
  - 释放键的内存（`free(key)`）
  - 释放节点内存
  - **不会释放值的内存**

---

### **6. 获取哈希表大小**
```c
int hashmap_size(HashMap* map);
```
- **返回**：当前存储的键值对数量

---

## **关键实现细节**
1. **哈希函数**：
   ```c
   hash = hash * 33 + c  // DJB2算法变种
   ```
   - 提供较好的字符串分布特性

2. **动态扩容**：
   - 扩容条件：`size/capacity ≥ 0.75`
   - 新容量：`old_capacity * 2`
   - 重新哈希所有元素

3. **内存管理**：
   - 键（`key`）使用`strdup`复制
   - 值（`value`）由调用者管理生命周期

---

## **使用示例**
```c
#include "hashmap.h"
#include <stdio.h>

int main() {
    // 创建哈希表
    HashMap* map = hashmap_create(0);
    
    // 插入数据
    int a = 10, b = 20;
    hashmap_put(map, "age", &a);
    hashmap_put(map, "score", &b);
    
    // 查询数据
    int* value = (int*)hashmap_get(map, "age");
    if (value) {
        printf("Age: %d\n", *value); // 输出: Age: 10
    }
    
    // 删除数据
    hashmap_remove(map, "score");
    
    // 销毁哈希表
    hashmap_destroy(map);
    return 0;
}
```

---

## **注意事项**
1. **线程安全**：该实现**不是线程安全**的，多线程环境需自行加锁
2. **值生命周期**：哈希表不会释放值的指针，需调用者管理
3. **哈希函数限制**：仅支持字符串键，如需其他类型需修改哈希函数
4. **错误处理**：未处理内存分配失败，生产环境需添加错误检查

---

## **扩展建议**
1. **迭代器支持**：添加遍历功能
   ```c
   typedef void (*HashMapIterFunc)(const char* key, void* value);
   void hashmap_foreach(HashMap* map, HashMapIterFunc func);
   ```
2. **泛型键支持**：通过联合体支持多种键类型
3. **内存池优化**：减少频繁的`malloc/free`调用
4. **统计信息**：记录最大冲突链长度等性能指标

---

## **性能优化建议**
- **容量选择**：初始容量设为预期元素数量的1.3倍
- **哈希函数**：根据实际键类型选择更优的哈希算法
- **内存对齐**：调整结构体成员顺序减少内存浪费
- **批量操作**：添加`put_all`等批量操作方法

--- 
