# HashMap (C Implementation) Documentation  

---

## **Overview**  
This is a generic hash table implementation in C, supporting string keys (`char*`) and values of any type. It uses **separate chaining** to resolve hash collisions, supports dynamic resizing, and provides basic operations: insertion, querying, deletion, and automatic resizing.  

---

## **Complexity Analysis**  
### **Time Complexity**  
| Operation   | Average Case | Worst Case     |  
|-------------|-------------|---------------|  
| `put`       | O(1)        | O(n)          |  
| `get`       | O(1)        | O(n)          |  
| `remove`    | O(1)        | O(n)          |  
| `resize`    | O(n)        | O(n)          |  

- **Worst case**: Degenerates to linked list operations when all keys collide.  
- **Resize operation**: Triggers rehashing of all elements (O(n)).  

### **Space Complexity**  
- **Total space**: O(n + m)  
  - `n`: Number of stored elements  
  - `m`: Number of hash table buckets (`capacity`)  
- **Per element**: Additional storage for linked list pointers (12-16 bytes per node).  

---

## **API Documentation**  

### **1. Create a Hash Map**  
```c  
HashMap* hashmap_create(int initial_capacity);  
```  
- **Parameters**:  
  - `initial_capacity`: Initial capacity (uses default 16 if ≤ 0).  
- **Returns**: Pointer to the new hash map, or `NULL` on failure.  
- **Note**: Recommended to use powers of 2 for optimal performance.  

---

### **2. Destroy a Hash Map**  
```c  
void hashmap_destroy(HashMap* map);  
```  
- **Parameters**:  
  - `map`: Target hash map.  
- **Behavior**:  
  - Frees all keys (`free(key)`).  
  - Frees all node and bucket memory.  
  - **Does not free values** (managed by the caller).  

---

### **3. Insert/Update a Key-Value Pair**  
```c  
void hashmap_put(HashMap* map, const char* key, void* value);  
```  
- **Parameters**:  
  - `map`: Target hash map.  
  - `key`: String key (internally copied via `strdup`).  
  - `value`: Pointer to any type of value.  
- **Behavior**:  
  - Updates the value if the key already exists.  
  - Triggers resizing if `size/capacity ≥ 0.75`.  

---

### **4. Retrieve a Value**  
```c  
void* hashmap_get(HashMap* map, const char* key);  
```  
- **Parameters**:  
  - `map`: Target hash map.  
  - `key`: Key to search for.  
- **Returns**: Pointer to the value if found, otherwise `NULL`.  

---

### **5. Remove a Key-Value Pair**  
```c  
int hashmap_remove(HashMap* map, const char* key);  
```  
- **Parameters**:  
  - `map`: Target hash map.  
  - `key`: Key to delete.  
- **Returns**: `1` if successfully removed, `0` if not found.  
- **Behavior**:  
  - Frees the key memory (`free(key)`).  
  - Frees the node memory.  
  - **Does not free the value memory**.  

---

### **6. Get Hash Map Size**  
```c  
int hashmap_size(HashMap* map);  
```  
- **Returns**: Current number of key-value pairs.  

---

## **Key Implementation Details**  
1. **Hash Function**:  
   ```c  
   hash = hash * 33 + c  // Modified DJB2 algorithm  
   ```  
   - Provides good distribution for strings.  

2. **Dynamic Resizing**:  
   - Trigger: `size/capacity ≥ 0.75`.  
   - New capacity: `old_capacity * 2`.  
   - Rehashes all elements.  

3. **Memory Management**:  
   - Keys (`key`) are copied via `strdup`.  
   - Values (`value`) must be managed by the caller.  

---

## **Usage Example**  
```c  
#include "hashmap.h"  
#include <stdio.h>  

int main() {  
    // Create a hash map  
    HashMap* map = hashmap_create(0);  

    // Insert data  
    int a = 10, b = 20;  
    hashmap_put(map, "age", &a);  
    hashmap_put(map, "score", &b);  

    // Query data  
    int* value = (int*)hashmap_get(map, "age");  
    if (value) {  
        printf("Age: %d\n", *value); // Output: Age: 10  
    }  

    // Delete data  
    hashmap_remove(map, "score");  

    // Destroy the hash map  
    hashmap_destroy(map);  
    return 0;  
}  
```  

---

## **Notes**  
1. **Thread Safety**: This implementation is **not thread-safe**; external synchronization is required for multi-threaded use.  
2. **Value Lifetime**: The hash map does not free value pointers; the caller must manage them.  
3. **Hash Function Limitation**: Only supports string keys. Modify the hash function for other key types.  
4. **Error Handling**: Does not handle memory allocation failures; add checks for production use.  

---

## **Extension Suggestions**  
1. **Iterator Support**: Add traversal functionality.  
   ```c  
   typedef void (*HashMapIterFunc)(const char* key, void* value);  
   void hashmap_foreach(HashMap* map, HashMapIterFunc func);  
   ```  
2. **Generic Key Support**: Use unions to support multiple key types.  
3. **Memory Pool Optimization**: Reduce frequent `malloc/free` calls.  
4. **Performance Metrics**: Track maximum collision chain length for optimization.  

---

## **Performance Optimization Tips**  
- **Capacity Selection**: Set initial capacity to ~1.3x the expected element count.  
- **Hash Function**: Choose a better algorithm based on actual key types.  
- **Memory Alignment**: Adjust struct member ordering to reduce wasted space.  
- **Bulk Operations**: Add methods like `put_all` for batch operations.  

--- 

This implementation balances usability and performance, making it suitable for most C applications requiring fast key-value lookups.
