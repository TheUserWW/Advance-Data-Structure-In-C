# Priority Queue (Min-Heap) Documentation

## Overview

This header file provides a priority queue implementation in C using a min-heap data structure. The priority queue allows efficient access to the smallest element (front) and maintains optimized access to the largest element (back).

## Features

- **Min-Heap Implementation**: Always provides O(1) access to the smallest element
- **Efficient Operations**: Insertion and extraction in O(log n) time
- **Dual-End Access**: Quick access to both smallest (front) and largest (back) elements
- **Dynamic Size**: Automatically handles queue capacity
- **Type Safety**: Currently supports integer values

## Data Structure

```c
typedef struct {
    int *heap;          // Array to store heap elements (1-based indexing)
    int capacity;       // Maximum number of elements
    int count;          // Current number of elements
    int max_leaf;       // Cache of the maximum leaf value (for pq_back)
} PriorityQueue;
```

## API Reference

### Creation and Destruction

#### `pq_create`
```c
PriorityQueue* pq_create(int max_size);
```
Creates a new priority queue with specified capacity.

**Parameters:**
- `max_size`: Maximum number of elements the queue can hold

**Returns:**
- Pointer to newly created PriorityQueue
- NULL on allocation failure

#### `pq_free`
```c
void pq_free(PriorityQueue *pq);
```
Releases all resources associated with the priority queue.

**Parameters:**
- `pq`: Pointer to the priority queue to destroy

### Capacity Operations

#### `pq_empty`
```c
bool pq_empty(PriorityQueue *pq);
```
Checks if the priority queue is empty.

**Returns:**
- true if queue is empty
- false otherwise

#### `pq_full`
```c
bool pq_full(PriorityQueue *pq);
```
Checks if the priority queue is full.

**Returns:**
- true if queue is at capacity
- false otherwise

#### `pq_size`
```c
int pq_size(PriorityQueue *pq);
```
Returns the current number of elements in the queue.

### Element Access

#### `pq_front`
```c
int pq_front(PriorityQueue *pq);
```
Access the smallest element (top of min-heap).

**Returns:**
- Value of smallest element
- INT_MAX if queue is empty

#### `pq_back`
```c
int pq_back(PriorityQueue *pq);
```
Access the largest element in the queue.

**Returns:**
- Value of largest element
- INT_MIN if queue is empty

### Modifiers

#### `pq_push`
```c
void pq_push(PriorityQueue *pq, int value);
```
Inserts a new element into the priority queue.

**Parameters:**
- `value`: Integer value to insert

**Notes:**
- Prints error message if queue is full
- Maintains heap property after insertion

#### `pq_pop`
```c
int pq_pop(PriorityQueue *pq);
```
Removes and returns the smallest element.

**Returns:**
- Value of smallest element
- INT_MAX if queue is empty

## Usage Example

```c
#include "priority_queue.h"
#include <stdio.h>

int main() {
    // Create priority queue with capacity 10
    PriorityQueue *pq = pq_create(10);
    
    // Insert elements
    pq_push(pq, 5);
    pq_push(pq, 3);
    pq_push(pq, 8);
    pq_push(pq, 1);
    pq_push(pq, 4);
    
    // Access elements
    printf("Front (min): %d\n", pq_front(pq));  // Output: 1
    printf("Back (max): %d\n", pq_back(pq));     // Output: 8
    
    // Process all elements
    while (!pq_empty(pq)) {
        printf("%d ", pq_pop(pq));
    }
    // Output: 1 3 4 5 8
    
    // Clean up
    pq_free(pq);
    return 0;
}
```

## Performance Characteristics

| Operation    | Time Complexity | Notes                          |
|--------------|-----------------|--------------------------------|
| pq_create    | O(1)            | Single allocation             |
| pq_free      | O(1)            | Single deallocation           |
| pq_push      | O(log n)        | Heap insertion                |
| pq_pop       | O(log n)        | Heap extraction               |
| pq_front     | O(1)            | Direct access to root         |
| pq_back      | O(1) amortized  | Maintained during operations   |
| pq_empty     | O(1)            | Count comparison              |
| pq_full      | O(1)            | Count comparison              |

## Notes

1. The implementation uses 1-based indexing for easier parent/child calculations
2. Error conditions return INT_MAX/INT_MIN and print to stderr
3. For production use, consider:
   - Adding error codes instead of printing
   - Making it generic with void pointers
   - Adding resize capability
4. The max_leaf optimization provides O(1) access to the largest element while maintaining O(log n) insertion time
