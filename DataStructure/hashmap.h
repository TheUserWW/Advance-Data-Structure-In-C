#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 默认哈希表大小
#define HASHMAP_DEFAULT_CAPACITY 16
// 负载因子阈值，超过则扩容
#define HASHMAP_LOAD_FACTOR 0.75

typedef struct HashMapEntry {
    char* key;
    void* value;
    struct HashMapEntry* next; // 链表解决哈希冲突
} HashMapEntry;

typedef struct {
    HashMapEntry** buckets;
    int capacity;
    int size;
} HashMap;

// 创建哈希表
HashMap* hashmap_create(int initial_capacity);

// 销毁哈希表
void hashmap_destroy(HashMap* map);

// 插入/更新键值对
void hashmap_put(HashMap* map, const char* key, void* value);

// 获取键对应的值
void* hashmap_get(HashMap* map, const char* key);

// 删除键值对
int hashmap_remove(HashMap* map, const char* key);

// 获取哈希表大小
int hashmap_size(HashMap* map);

// 内部函数：哈希函数
static unsigned int _hash(const char* key, int capacity);

// 内部函数：扩容哈希表
static void _resize(HashMap* map);

// ------------------------- 实现部分 -------------------------

HashMap* hashmap_create(int initial_capacity) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    if (!map) return NULL;
    
    map->capacity = initial_capacity > 0 ? initial_capacity : HASHMAP_DEFAULT_CAPACITY;
    map->size = 0;
    map->buckets = (HashMapEntry**)calloc(map->capacity, sizeof(HashMapEntry*));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    return map;
}

void hashmap_destroy(HashMap* map) {
    if (!map) return;
    
    for (int i = 0; i < map->capacity; i++) {
        HashMapEntry* entry = map->buckets[i];
        while (entry) {
            HashMapEntry* next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(map->buckets);
    free(map);
}

void hashmap_put(HashMap* map, const char* key, void* value) {
    if (!map || !key) return;
    
    // 检查是否需要扩容
    if ((float)map->size / map->capacity >= HASHMAP_LOAD_FACTOR) {
        _resize(map);
    }
    
    unsigned int index = _hash(key, map->capacity);
    HashMapEntry* entry = map->buckets[index];
    
    // 检查是否已存在该key
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value; // 更新值
            return;
        }
        entry = entry->next;
    }
    
    // 创建新entry
    HashMapEntry* new_entry = (HashMapEntry*)malloc(sizeof(HashMapEntry));
    if (!new_entry) return;
    
    new_entry->key = strdup(key);
    new_entry->value = value;
    new_entry->next = map->buckets[index];
    map->buckets[index] = new_entry;
    map->size++;
}

void* hashmap_get(HashMap* map, const char* key) {
    if (!map || !key) return NULL;
    
    unsigned int index = _hash(key, map->capacity);
    HashMapEntry* entry = map->buckets[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    
    return NULL; // 未找到
}

int hashmap_remove(HashMap* map, const char* key) {
    if (!map || !key) return 0;
    
    unsigned int index = _hash(key, map->capacity);
    HashMapEntry* prev = NULL;
    HashMapEntry* entry = map->buckets[index];
    
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                map->buckets[index] = entry->next;
            }
            free(entry->key);
            free(entry);
            map->size--;
            return 1; // 删除成功
        }
        prev = entry;
        entry = entry->next;
    }
    
    return 0; // 未找到
}

int hashmap_size(HashMap* map) {
    return map ? map->size : 0;
}

static unsigned int _hash(const char* key, int capacity) {
    unsigned int hash = 5381;
    int c;
    
    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }
    
    return hash % capacity;
}

static void _resize(HashMap* map) {
    int new_capacity = map->capacity * 2;
    HashMapEntry** new_buckets = (HashMapEntry**)calloc(new_capacity, sizeof(HashMapEntry*));
    if (!new_buckets) return;
    
    // 重新哈希所有元素
    for (int i = 0; i < map->capacity; i++) {
        HashMapEntry* entry = map->buckets[i];
        while (entry) {
            HashMapEntry* next = entry->next;
            unsigned int new_index = _hash(entry->key, new_capacity);
            
            // 插入到新桶中
            entry->next = new_buckets[new_index];
            new_buckets[new_index] = entry;
            
            entry = next;
        }
    }
    
    free(map->buckets);
    map->buckets = new_buckets;
    map->capacity = new_capacity;
}

#endif // HASHMAP_H