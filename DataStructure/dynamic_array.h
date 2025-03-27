#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    void *data;          // 数据存储指针
    size_t size;         // 当前元素数量
    size_t capacity;     // 当前存储容量
    size_t element_size; // 单个元素大小
} DynamicArray;

/* 初始化动态数组
 * 参数：
 *   da - 动态数组指针
 *   element_size - 单个元素大小(字节)
 *   initial_capacity - 初始容量
 * 返回：成功返回true，失败返回false
 */
static inline bool dynamic_array_init(DynamicArray *da, size_t element_size, size_t initial_capacity) {
    if (initial_capacity == 0) initial_capacity = 1;
    
    da->data = malloc(element_size * initial_capacity);
    if (!da->data) return false;
    
    da->size = 0;
    da->capacity = initial_capacity;
    da->element_size = element_size;
    return true;
}

/* 释放动态数组内存 */
static inline void dynamic_array_destroy(DynamicArray *da) {
    free(da->data);
    da->data = NULL;
    da->size = da->capacity = 0;
}

/* 内部扩容函数 */
static inline bool dynamic_array_reserve_internal(DynamicArray *da, size_t new_capacity) {
    if (new_capacity <= da->capacity) return true;
    
    void *new_data = realloc(da->data, da->element_size * new_capacity);
    if (!new_data) return false;
    
    da->data = new_data;
    da->capacity = new_capacity;
    return true;
}

/* 在末尾添加元素
 * 参数：
 *   da - 动态数组指针
 *   element - 要添加的元素指针
 * 返回：成功返回true，失败返回false
 */
static inline bool dynamic_array_push_back(DynamicArray *da, const void *element) {
    if (da->size >= da->capacity) {
        if (!dynamic_array_reserve_internal(da, da->capacity * 2)) return false;
    }
    
    memcpy((char*)da->data + da->size * da->element_size, element, da->element_size);
    da->size++;
    return true;
}

/* 在指定位置插入元素
 * 参数：
 *   da - 动态数组指针
 *   index - 插入位置索引
 *   element - 要插入的元素指针
 * 返回：成功返回true，失败返回false
 */
static inline bool dynamic_array_insert(DynamicArray *da, size_t index, const void *element) {
    if (index > da->size) return false;
    
    if (da->size >= da->capacity) {
        if (!dynamic_array_reserve_internal(da, da->capacity * 2)) return false;
    }
    
    char *dest = (char*)da->data + (index + 1) * da->element_size;
    char *src = (char*)da->data + index * da->element_size;
    size_t bytes_to_move = (da->size - index) * da->element_size;
    
    memmove(dest, src, bytes_to_move);
    memcpy(src, element, da->element_size);
    da->size++;
    return true;
}

/* 删除指定位置的元素
 * 参数：
 *   da - 动态数组指针
 *   index - 要删除的元素索引
 * 返回：成功返回true，失败返回false
 */
static inline bool dynamic_array_remove_at(DynamicArray *da, size_t index) {
    if (index >= da->size) return false;
    
    char *dest = (char*)da->data + index * da->element_size;
    char *src = dest + da->element_size;
    size_t bytes_to_move = (da->size - index - 1) * da->element_size;
    
    memmove(dest, src, bytes_to_move);
    da->size--;
    return true;
}

/* 查找元素
 * 参数：
 *   da - 动态数组指针
 *   element - 要查找的元素指针
 *   compare - 比较函数
 * 返回：找到返回索引，未找到返回-1
 */
static inline int dynamic_array_find(const DynamicArray *da, const void *element, 
                                   int (*compare)(const void*, const void*)) {
    for (size_t i = 0; i < da->size; i++) {
        void *current = (char*)da->data + i * da->element_size;
        if (compare(current, element) == 0) {
            return (int)i;
        }
    }
    return -1;
}

/* 排序数组
 * 参数：
 *   da - 动态数组指针
 *   compare - 比较函数
 */
static inline void dynamic_array_sort(DynamicArray *da, int (*compare)(const void*, const void*)) {
    qsort(da->data, da->size, da->element_size, compare);
}

/* 获取元素数量
 * 参数：
 *   da - 动态数组指针
 * 返回：当前元素数量
 */
static inline size_t dynamic_array_size(const DynamicArray *da) {
    return da->size;
}

/* 获取元素指针
 * 参数：
 *   da - 动态数组指针
 *   index - 元素索引
 * 返回：指向元素的指针，索引无效返回NULL
 */
static inline void* dynamic_array_get(const DynamicArray *da, size_t index) {
    if (index >= da->size) return NULL;
    return (char*)da->data + index * da->element_size;
}

/* 清空数组（保留容量）
 * 参数：
 *   da - 动态数组指针
 */
static inline void dynamic_array_clear(DynamicArray *da) {
    da->size = 0;
}

/* 预分配空间
 * 参数：
 *   da - 动态数组指针
 *   new_capacity - 新的容量大小
 * 返回：成功返回true，失败返回false
 */
static inline bool dynamic_array_reserve(DynamicArray *da, size_t new_capacity) {
    return dynamic_array_reserve_internal(da, new_capacity);
}

#ifdef __cplusplus
}
#endif

#endif // DYNAMIC_ARRAY_H