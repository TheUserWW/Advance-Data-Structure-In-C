/**
 * @file hashset.h
 * @brief 高性能哈希集合实现 (完整修正版)
 */

 #ifndef HASHSET_H
 #define HASHSET_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include <stdint.h>
 
 #define HASHSET_INIT_CAPACITY 101
 #define HASHSET_MAX_LOAD 0.7
 
 typedef struct SetNode {
     void* data;
     size_t hash;
     struct SetNode* next;
 } SetNode;
 
 typedef struct {
     SetNode** buckets;
     size_t size;
     size_t capacity;
     size_t data_size;
     size_t (*hash_func)(const void*);
     bool (*compare_func)(const void*, const void*);
     void (*free_func)(void*);
 } HashSet;
 
 // ==================== 预定义类型支持 ====================
 
 static size_t int_hash(const void* data) {
     int val = *(const int*)data;
     return (size_t)(val * 2654435761ULL);
 }
 
 static bool int_compare(const void* a, const void* b) {
     return *(const int*)a == *(const int*)b;
 }
 
 static size_t str_hash(const void* data) {
     const char* str = *(const char**)data;
     size_t hash = 5381;
     int c;
     while ((c = *str++)) {
         hash = ((hash << 5) + hash) ^ c;
     }
     return hash;
 }
 
 static bool str_compare(const void* a, const void* b) {
     return strcmp(*(const char**)a, *(const char**)b) == 0;
 }
 
 static void str_free(void* data) {
     free(*(char**)data);
 }
 
 // ==================== 核心实现 ====================
 
 HashSet* hashset_create(size_t data_size,
                         size_t (*hash_func)(const void*),
                         bool (*compare_func)(const void*, const void*),
                         void (*free_func)(void*)) 
 {
     HashSet* set = (HashSet*)malloc(sizeof(HashSet));
     if (!set) return NULL;
     
     set->capacity = HASHSET_INIT_CAPACITY;
     set->size = 0;
     set->data_size = data_size;
     set->hash_func = hash_func;
     set->compare_func = compare_func;
     set->free_func = free_func;
     
     set->buckets = (SetNode**)calloc(set->capacity, sizeof(SetNode*));
     if (!set->buckets) {
         free(set);
         return NULL;
     }
     return set;
 }
 
 static bool is_prime(size_t num) {
     if (num <= 1) return false;
     if (num <= 3) return true;
     if (num % 2 == 0 || num % 3 == 0) return false;
     
     for (size_t i = 5; i*i <= num; i += 6) {
         if (num % i == 0 || num % (i+2) == 0) {
             return false;
         }
     }
     return true;
 }
 
 static void resize(HashSet* set) {
     size_t new_capacity = set->capacity * 2;
     while (!is_prime(new_capacity)) new_capacity++;
     
     SetNode** new_buckets = (SetNode**)calloc(new_capacity, sizeof(SetNode*));
     if (!new_buckets) return;
     
     for (size_t i = 0; i < set->capacity; i++) {
         SetNode* node = set->buckets[i];
         while (node) {
             SetNode* next = node->next;
             size_t new_index = node->hash % new_capacity;
             
             node->next = new_buckets[new_index];
             new_buckets[new_index] = node;
             
             node = next;
         }
     }
     
     free(set->buckets);
     set->buckets = new_buckets;
     set->capacity = new_capacity;
 }
 
 bool hashset_add(HashSet* set, const void* data) {
     if ((double)set->size / set->capacity > HASHSET_MAX_LOAD) {
         resize(set);
     }
 
     size_t hash = set->hash_func(data);
     size_t index = hash % set->capacity;
 
     SetNode* current = set->buckets[index];
     while (current) {
         if (current->hash == hash && 
             set->compare_func(current->data, data)) {
             return false;
         }
         current = current->next;
     }
 
     SetNode* newNode = (SetNode*)malloc(sizeof(SetNode));
     if (!newNode) return false;
     
     newNode->data = malloc(set->data_size);
     if (!newNode->data) {
         free(newNode);
         return false;
     }
     
     memcpy(newNode->data, data, set->data_size);
     newNode->hash = hash;
     newNode->next = set->buckets[index];
     set->buckets[index] = newNode;
     set->size++;
     return true;
 }
 
 bool hashset_contains(const HashSet* set, const void* data) {
     size_t hash = set->hash_func(data);
     size_t index = hash % set->capacity;
 
     SetNode* current = set->buckets[index];
     while (current) {
         if (current->hash == hash && 
             set->compare_func(current->data, data)) {
             return true;
         }
         current = current->next;
     }
     return false;
 }
 
 void hashset_free(HashSet* set) {
     if (!set) return;
     
     for (size_t i = 0; i < set->capacity; i++) {
         SetNode* node = set->buckets[i];
         while (node) {
             SetNode* next = node->next;
             if (set->free_func) {
                 set->free_func(node->data);
             }
             free(node->data);
             free(node);
             node = next;
         }
     }
     free(set->buckets);
     free(set);
 }
 
 // ==================== 便捷接口 ====================
 
 #define HASHSET_INT() \
     hashset_create(sizeof(int), int_hash, int_compare, NULL)
 
 #define HASHSET_STR() \
     hashset_create(sizeof(char*), str_hash, str_compare, str_free)
 
 #define HASHSET_CUSTOM(type, hash_fn, cmp_fn, free_fn) \
     hashset_create(sizeof(type), hash_fn, cmp_fn, free_fn)
 
 bool hashset_add_str(HashSet* set, const char* str) {
     char* copy = strdup(str);
     if (!copy) return false;
     
     bool result = hashset_add(set, &copy);
     if (!result) free(copy);
     return result;
 }
 
 bool hashset_add_all(HashSet* set, const void* data, size_t count) {
     const char* ptr = (const char*)data;
     for (size_t i = 0; i < count; i++) {
         if (!hashset_add(set, ptr + i * set->data_size)) {
             return false;
         }
     }
     return true;
 }
 
 #endif // HASHSET_H
