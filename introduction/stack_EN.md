# Stack Data Structure Documentation

## Overview
This header file provides a complete implementation of a stack data structure using a linked list approach. The implementation includes all basic stack operations plus additional utility functions.

**File:** `stack.h`  
**Author:** [Your Name]  
**Date:** [Current Date]  
**Version:** 1.0

## Data Structures

### StackNode
```c
typedef struct StackNode {
    int data;               ///< Data stored in the node
    struct StackNode* next; ///< Pointer to the next node
} StackNode;
```
- **Purpose:** Represents individual elements in the stack
- **Memory:** Each node occupies `sizeof(int) + sizeof(pointer)` bytes

### Stack
```c
typedef struct {
    StackNode* top;  ///< Pointer to the top node of the stack
    int size;        ///< Current number of elements in the stack
} Stack;
```
- **Purpose:** Main stack container holding metadata
- **Memory:** Fixed size of `sizeof(pointer) + sizeof(int)`

## API Reference

### Basic Operations

#### `stack_create()`
```c
Stack* stack_create();
```
- **Description:** Initializes a new empty stack
- **Time Complexity:** O(1)
- **Space Complexity:** O(1)
- **Returns:** Pointer to newly created stack
- **Notes:** Caller must free with `stack_free()`

#### `stack_push()`
```c
void stack_push(Stack* s, int item);
```
- **Description:** Pushes an item onto the stack
- **Time Complexity:** O(1)
- **Space Complexity:** O(1) per operation (amortized)
- **Parameters:**
  - `s`: Stack pointer
  - `item`: Integer value to push
- **Error Handling:** Terminates on memory allocation failure

#### `stack_pop()`
```c
int stack_pop(Stack* s);
```
- **Description:** Removes and returns the top item
- **Time Complexity:** O(1)
- **Space Complexity:** O(1)
- **Returns:** The popped integer value
- **Error Handling:** Terminates on empty stack
- **Warning:** Always check `stack_isEmpty()` first in production code

### Accessors

#### `stack_top()`
```c
int stack_top(Stack* s);
```
- **Description:** Returns the top item without removal
- **Time Complexity:** O(1)
- **Space Complexity:** O(1)
- **Returns:** Top integer value
- **Error Handling:** Terminates on empty stack

#### `stack_size()`
```c
int stack_size(Stack* s);
```
- **Description:** Returns current number of elements
- **Time Complexity:** O(1)
- **Space Complexity:** O(1)
- **Returns:** Current stack size

#### `stack_isEmpty()`
```c
bool stack_isEmpty(Stack* s);
```
- **Description:** Checks if stack is empty
- **Time Complexity:** O(1)
- **Space Complexity:** O(1)
- **Returns:** Boolean indicating empty state

### Advanced Operations

#### `stack_swap()`
```c
void stack_swap(Stack* s1, Stack* s2);
```
- **Description:** Efficiently swaps contents of two stacks
- **Time Complexity:** O(1)
- **Space Complexity:** O(1)
- **Parameters:** Two stack pointers to swap
- **Note:** Only pointer/size metadata is swapped

### Memory Management

#### `stack_free()`
```c
void stack_free(Stack* s);
```
- **Description:** Releases all stack memory
- **Time Complexity:** O(n) where n is stack size
- **Space Complexity:** O(1)
- **Parameters:** Stack pointer to free
- **Postcondition:** Stack pointer becomes invalid

## Complexity Summary

| Operation      | Time Complexity | Space Complexity |
|---------------|-----------------|------------------|
| create        | O(1)            | O(1)             |
| push          | O(1)            | O(1) per op      |
| pop           | O(1)            | O(1)             |
| top           | O(1)            | O(1)             |
| size          | O(1)            | O(1)             |
| isEmpty       | O(1)            | O(1)             |
| swap          | O(1)            | O(1)             |
| free          | O(n)            | O(1)             |

## Memory Usage
- **Per Stack:** Constant overhead (pointer + int)
- **Per Element:** sizeof(StackNode) = sizeof(int) + sizeof(pointer)
- **Total Memory:** ~(n * (sizeof(int) + sizeof(pointer)) + constant

## Best Practices
1. Always check `stack_isEmpty()` before `pop()` or `top()`
2. Balance every `stack_create()` with a `stack_free()`
3. Use `stack_swap()` instead of manual element transfer when possible
4. For time-critical sections, prefer `stack_size()` over repeated `stack_isEmpty()` checks

## Limitations
1. Not thread-safe (requires external synchronization for concurrent access)
2. Fixed to `int` data type (can be modified for other types)
3. Error handling terminates program (may want to modify for library use)

## Example Usage
See the example in the header file comments for complete demonstration of all operations.
