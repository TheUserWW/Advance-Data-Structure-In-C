以下是 `queue.h` 的完整文档说明，采用标准的 API 文档格式：

---

# 动态循环队列库文档

## 概述
`queue.h` 提供基于数组的动态循环队列实现，支持自动扩容和高效的 FIFO（先进先出）操作。所有操作都是线程不安全的，如需多线程使用需外部同步。

## 数据类型

### `Queue`
队列结构体，包含以下私有成员（用户不应直接访问）：
- `data`: 存储元素的动态数组
- `front`: 队头索引
- `rear`: 队尾索引
- `capacity`: 当前分配的容量
- `count`: 当前元素数量

## API 参考

### 生命周期管理

#### `queue_create`
```c
Queue* queue_create(int initCapacity);
```
- **功能**：创建新队列
- **参数**：
  - `initCapacity`: 初始容量（建议≥2，若<2会自动设为2）
- **返回**：
  - 成功：队列指针
  - 失败：NULL（内存分配失败）
- **时间复杂度**：O(1)

#### `queue_destroy`
```c
void queue_destroy(Queue *q);
```
- **功能**：销毁队列并释放内存
- **参数**：
  - `q`: 要销毁的队列指针（可安全传入NULL）
- **时间复杂度**：O(1)

### 状态查询

#### `queue_empty`
```c
bool queue_empty(Queue *q);
```
- **功能**：检查队列是否为空
- **参数**：
  - `q`: 队列指针
- **返回**：
  - true: 队列为空或无效指针
  - false: 队列非空
- **时间复杂度**：O(1)

#### `queue_size`
```c
int queue_size(Queue *q);
```
- **功能**：获取队列当前元素数量
- **参数**：
  - `q`: 队列指针
- **返回**：
  - ≥0: 元素个数
  - 0: 队列为空或无效指针
- **时间复杂度**：O(1)

### 核心操作

#### `queue_push`
```c
bool queue_push(Queue *q, int value);
```
- **功能**：在队尾插入元素
- **参数**：
  - `q`: 队列指针
  - `value`: 要插入的整数值
- **返回**：
  - true: 插入成功
  - false: 插入失败（内存不足或无效指针）
- **扩容机制**：当队列满时自动扩容为原来2倍
- **时间复杂度**：
  - 平均：O(1)
  - 最坏（扩容时）：O(n)

#### `queue_pop`
```c
bool queue_pop(Queue *q);
```
- **功能**：移除队首元素
- **参数**：
  - `q`: 队列指针
- **返回**：
  - true: 移除成功
  - false: 队列为空或无效指针
- **时间复杂度**：O(1)

#### `queue_front`
```c
int queue_front(Queue *q);
```
- **功能**：获取队首元素（不移除）
- **参数**：
  - `q`: 队列指针
- **返回**：
  - 队首元素值（队列空或无效指针时返回-1）
- **时间复杂度**：O(1)

#### `queue_back`
```c
int queue_back(Queue *q);
```
- **功能**：获取队尾元素（不移除）
- **参数**：
  - `q`: 队列指针
- **返回**：
  - 队尾元素值（队列空或无效指针时返回-1）
- **时间复杂度**：O(1)

## 使用示例

### 基本用法
```c
#include "queue.h"

int main() {
    // 创建容量为3的队列
    Queue *q = queue_create(3);
    
    // 插入元素（会自动扩容）
    queue_push(q, 10);
    queue_push(q, 20);
    queue_push(q, 30);
    queue_push(q, 40);  // 触发扩容
    
    // 遍历队列
    while (!queue_empty(q)) {
        printf("Front element: %d\n", queue_front(q));
        queue_pop(q);
    }
    
    queue_destroy(q);
    return 0;
}
```

### 输出示例
```
Front element: 10
Front element: 20
Front element: 30
Front element: 40
```

## 设计说明

1. **循环缓冲区**：
   - 使用模运算实现循环访问
   - 公式：`index = (current + 1) % capacity`

2. **扩容策略**：
   - 当 `count == capacity` 时触发
   - 新容量 = 旧容量 × 2
   - 扩容时会重新排列元素保持顺序

3. **特殊返回值**：
   - 所有可能失败的操作都返回bool状态
   - 空队列访问返回-1（可通过`queue_empty`预先检查）

## 内存管理
- 每个队列需要1次`malloc`（结构体） + 1次`malloc`（数据数组）
- 销毁时必须调用`queue_destroy`避免内存泄漏

## 限制
1. 最大元素数量受`INT_MAX`限制
2. 非线程安全
3. 仅支持`int`类型元素（可修改为泛型）

## 扩展建议
1. 添加`queue_reserve`预分配内存
2. 实现迭代器接口
3. 添加线程安全包装器

## 版本历史
- v1.0 (2023-08-20): 初始版本
- v1.1 (2023-08-22): 添加扩容时的顺序保持

---

这个文档包含：
1. 规范的API说明（参数/返回/时间复杂度）
2. 实际使用示例
3. 内部实现原理
4. 明确的限制和扩展建议
5. 版本控制信息

建议保存为`QUEUE.md`与头文件一起分发，或使用Doxygen生成更详细的文档。
