# HashSet Library Documentation

This document provides detailed documentation for the high-performance hash set implementation, including usage examples for each function.

## Overview

This hash set is a dynamic hash table implementation using separate chaining for collision resolution. Key features include:
- Automatic resizing mechanism
- Support for generic data types
- Predefined support for integer and string types
- Customizable hash and comparison functions
- Memory-safe deallocation

## Constant Definitions

- `HASHSET_INIT_CAPACITY` (101): Default initial capacity (prime number)
- `HASHSET_MAX_LOAD` (0.7): Maximum load factor triggering resizing

## Predefined Type Support

### Integer Type Support
```c
size_t int_hash(const void* data);      // Integer hash function
bool int_compare(const void* a, const void* b);  // Integer comparison function
```

### String Type Support
```c
size_t str_hash(const void* data);      // String hash function
bool str_compare(const void* a, const void* b);  // String comparison function
void str_free(void* data);              // String memory deallocation function
```

## API Reference

### hashset_create

Creates a new hash set.

**Parameters:**
- `data_size`: Size of data type (in bytes)
- `hash_func`: Pointer to hash function
- `compare_func`: Pointer to comparison function
- `free_func`: Pointer to data deallocation function (can be NULL)

**Returns:**
- Pointer to new hash set, NULL on failure

**Example:**
```c
// Create integer set
HashSet* intSet = hashset_create(sizeof(int), int_hash, int_compare, NULL);

// Create string set
HashSet* strSet = hashset_create(sizeof(char*), str_hash, str_compare, str_free);

// Create custom type set
typedef struct { int x; int y; } Point;
size_t point_hash(const void* p) { /*...*/ }
bool point_compare(const void* a, const void* b) { /*...*/ }
HashSet* pointSet = hashset_create(sizeof(Point), point_hash, point_compare, NULL);
```

### Convenience Macros

```c
HASHSET_INT()    // Create integer set
HASHSET_STR()    // Create string set
HASHSET_CUSTOM(type, hash_fn, cmp_fn, free_fn)  // Create custom type set
```

**Example:**
```c
HashSet* intSet = HASHSET_INT();
HashSet* strSet = HASHSET_STR();
```

### hashset_add

Adds an element to the set.

**Parameters:**
- `set`: Hash set pointer
- `data`: Pointer to data to add

**Returns:**
- true if successfully added, false if already exists or failed

**Example:**
```c
HashSet* set = HASHSET_INT();
int num = 42;
hashset_add(set, &num);  // Add integer 42

HashSet* strSet = HASHSET_STR();
char* name = "Alice";
hashset_add(strSet, &name);  // Add string pointer
```

### hashset_add_str

Convenience function to add string (automatically duplicates).

**Parameters:**
- `set`: Hash set pointer
- `str`: String to add

**Returns:**
- true if successfully added, false if already exists or failed

**Example:**
```c
HashSet* set = HASHSET_STR();
hashset_add_str(set, "Hello");
hashset_add_str(set, "World");
```

### hashset_add_all

Adds an array of elements in batch.

**Parameters:**
- `set`: Hash set pointer
- `data`: Pointer to element array
- `count`: Number of elements

**Returns:**
- true if all added successfully, false if any failed

**Example:**
```c
HashSet* set = HASHSET_INT();
int numbers[] = {1, 2, 3, 4, 5};
hashset_add_all(set, numbers, 5);
```

### hashset_contains

Checks if set contains specified element.

**Parameters:**
- `set`: Hash set pointer
- `data`: Pointer to data to find

**Returns:**
- true if exists, false otherwise

**Example:**
```c
HashSet* set = HASHSET_INT();
int num = 42;
hashset_add(set, &num);

if (hashset_contains(set, &num)) {
    printf("Set contains %d\n", num);
}
```

### hashset_free

Frees hash set and all its elements.

**Parameters:**
- `set`: Hash set pointer

**Example:**
```c
HashSet* set = HASHSET_STR();
hashset_add_str(set, "Test");
hashset_free(set);  // Properly deallocates all memory
```

## Internal Functions

### resize

Automatically resizes hash table when load factor exceeds threshold.

**Parameters:**
- `set`: Hash set pointer

**Note:**
- Called automatically, no manual invocation needed
- Capacity always expands to prime numbers to reduce hash collisions

## Usage Notes

1. For string sets, must use `HASHSET_STR()` or specify `str_free` as deallocation function
2. Custom types require appropriate hash and comparison functions
3. Set does not guarantee element ordering
4. Not thread-safe, requires external synchronization in multi-threaded environments
5. Resizing operation can be slow, consider larger initial capacity for big sets

## Memory Management

- Data is automatically duplicated when added
- Set deallocation recursively frees all nodes and data
- String type performs deep deallocation of string memory
- Custom types require appropriate deallocation functions

## Performance Considerations

- Load factor set to 0.7 to balance space and time efficiency
- Uses prime number capacities to reduce hash collisions
- Hash functions use multiplicative hashing (integers) and DJB2 algorithm (strings)
