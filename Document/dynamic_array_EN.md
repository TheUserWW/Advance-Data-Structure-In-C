# Dynamic Array Library Documentation

## Overview

This dynamic array library provides a generic container implementation similar to C++'s vector, supporting automatic expansion, random access, insertion/deletion operations, and more. All functions are implemented as inline for high performance and low overhead.

## Data Structure

```c
typedef struct {
    void *data;          // Data storage pointer
    size_t size;         // Current number of elements
    size_t capacity;     // Current storage capacity
    size_t element_size; // Size of single element (bytes)
} DynamicArray;
```

## API Reference

### Initialization and Destruction

#### `dynamic_array_init`

```c
bool dynamic_array_init(DynamicArray *da, size_t element_size, size_t initial_capacity);
```

- **Function**: Initializes a dynamic array
- **Parameters**:
  - `da`: Dynamic array pointer
  - `element_size`: Size of single element (bytes)
  - `initial_capacity`: Initial capacity
- **Returns**: `true` on success, `false` on failure
- **Time Complexity**: O(1)
- **Space Complexity**: O(n), n=initial_capacity

#### `dynamic_array_destroy`

```c
void dynamic_array_destroy(DynamicArray *da);
```

- **Function**: Releases dynamic array memory
- **Parameters**:
  - `da`: Dynamic array pointer
- **Time Complexity**: O(1)
- **Space Complexity**: O(1)

### Capacity Management

#### `dynamic_array_reserve`

```c
bool dynamic_array_reserve(DynamicArray *da, size_t new_capacity);
```

- **Function**: Pre-allocates storage space
- **Parameters**:
  - `da`: Dynamic array pointer
  - `new_capacity`: New capacity size
- **Returns**: `true` on success, `false` on failure
- **Time Complexity**: O(n), n=current element count
- **Space Complexity**: O(n), n=new_capacity

#### `dynamic_array_clear`

```c
void dynamic_array_clear(DynamicArray *da);
```

- **Function**: Clears the array (retains capacity)
- **Parameters**:
  - `da`: Dynamic array pointer
- **Time Complexity**: O(1)
- **Space Complexity**: O(1)

### Element Access

#### `dynamic_array_get`

```c
void* dynamic_array_get(const DynamicArray *da, size_t index);
```

- **Function**: Gets element pointer
- **Parameters**:
  - `da`: Dynamic array pointer
  - `index`: Element index
- **Returns**: Pointer to element, or `NULL` if index invalid
- **Time Complexity**: O(1)
- **Space Complexity**: O(1)

#### `dynamic_array_size`

```c
size_t dynamic_array_size(const DynamicArray *da);
```

- **Function**: Gets number of elements
- **Parameters**:
  - `da`: Dynamic array pointer
- **Returns**: Current element count
- **Time Complexity**: O(1)
- **Space Complexity**: O(1)

### Modification Operations

#### `dynamic_array_push_back`

```c
bool dynamic_array_push_back(DynamicArray *da, const void *element);
```

- **Function**: Adds element at the end
- **Parameters**:
  - `da`: Dynamic array pointer
  - `element`: Pointer to element to add
- **Returns**: `true` on success, `false` on failure
- **Time Complexity**:
  - Average case: O(1)
  - Worst case (needs expansion): O(n), n=current element count
- **Space Complexity**:
  - Average case: O(1)
  - Worst case: O(n), n=new capacity

#### `dynamic_array_insert`

```c
bool dynamic_array_insert(DynamicArray *da, size_t index, const void *element);
```

- **Function**: Inserts element at specified position
- **Parameters**:
  - `da`: Dynamic array pointer
  - `index`: Insertion position index
  - `element`: Pointer to element to insert
- **Returns**: `true` on success, `false` on failure
- **Time Complexity**:
  - Average case: O(n), n=size-index
  - Worst case (needs expansion): O(n), n=current element count
- **Space Complexity**:
  - Average case: O(1)
  - Worst case: O(n), n=new capacity

#### `dynamic_array_remove_at`

```c
bool dynamic_array_remove_at(DynamicArray *da, size_t index);
```

- **Function**: Removes element at specified position
- **Parameters**:
  - `da`: Dynamic array pointer
  - `index`: Element index to remove
- **Returns**: `true` on success, `false` on failure
- **Time Complexity**: O(n), n=size-index-1
- **Space Complexity**: O(1)

### Algorithm Operations

#### `dynamic_array_find`

```c
int dynamic_array_find(const DynamicArray *da, const void *element, 
                     int (*compare)(const void*, const void*));
```

- **Function**: Finds element
- **Parameters**:
  - `da`: Dynamic array pointer
  - `element`: Pointer to element to find
  - `compare`: Comparison function
- **Returns**: Index if found, -1 if not found
- **Time Complexity**: O(n), n=element count
- **Space Complexity**: O(1)

#### `dynamic_array_sort`

```c
void dynamic_array_sort(DynamicArray *da, int (*compare)(const void*, const void*));
```

- **Function**: Sorts array
- **Parameters**:
  - `da`: Dynamic array pointer
  - `compare`: Comparison function
- **Time Complexity**: O(n log n), n=element count
- **Space Complexity**: Depends on qsort implementation, typically O(log n)

## Complexity Summary

| Operation              | Time Complexity       | Space Complexity      |
|------------------------|-----------------------|-----------------------|
| init                   | O(1)                  | O(n)                  |
| destroy                | O(1)                  | O(1)                  |
| reserve                | O(n)                  | O(n)                  |
| clear                  | O(1)                  | O(1)                  |
| get                    | O(1)                  | O(1)                  |
| size                   | O(1)                  | O(1)                  |
| push_back (average)    | O(1)                  | O(1)                  |
| push_back (worst)      | O(n)                  | O(n)                  |
| insert (average)       | O(n)                  | O(1)                  |
| insert (worst)         | O(n)                  | O(n)                  |
| remove_at              | O(n)                  | O(1)                  |
| find                   | O(n)                  | O(1)                  |
| sort                   | O(n log n)            | O(log n)              |

## Best Practices

1. **Initial Capacity Selection**: Set reasonable initial capacity based on estimated data volume to avoid frequent expansions
2. **Batch Operations**: Pre-call `reserve` to allocate sufficient space and reduce reallocation
3. **Element Access**: Use `dynamic_array_get` to obtain pointer and cast to correct type
4. **Custom Comparison**: Provide appropriate comparison functions for sorting and searching

## Example Code

```c
#include "dynamic_array.h"
#include <stdio.h>

// Comparison function
int compare_int(const void *a, const void *b) {
    return *(const int*)a - *(const int*)b;
}

int main() {
    DynamicArray da;
    dynamic_array_init(&da, sizeof(int), 10); // Initial capacity 10

    // Add elements
    for (int i = 0; i < 20; i++) {
        int val = 20 - i;
        dynamic_array_push_back(&da, &val);
    }

    // Sort
    dynamic_array_sort(&da, compare_int);

    // Find
    int target = 10;
    int idx = dynamic_array_find(&da, &target, compare_int);
    if (idx != -1) {
        printf("Found %d at index %d\n", target, idx);
    }

    // Iterate
    for (size_t i = 0; i < dynamic_array_size(&da); i++) {
        printf("%d ", *(int*)dynamic_array_get(&da, i));
    }

    dynamic_array_destroy(&da);
    return 0;
}
```

## Limitations and Notes

1. Not thread-safe - requires external synchronization for multithreaded environments
2. Elements must be POD (Plain Old Data) types - doesn't support complex objects requiring construction/destruction
3. Simple error handling - callers need to check return values
