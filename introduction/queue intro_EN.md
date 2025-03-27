Here's the professional English documentation for the `queue.h` header file:

---

# Dynamic Circular Queue Library Documentation

## Overview
`queue.h` provides an array-based dynamic circular queue implementation with automatic expansion and efficient FIFO (First-In-First-Out) operations. All operations are not thread-safe - external synchronization is required for multithreaded use.

## Data Types

### `Queue`
Queue structure containing private members (users should not access directly):
- `data`: Dynamic array storing elements
- `front`: Index of queue head
- `rear`: Index of queue tail
- `capacity`: Current allocated capacity
- `count`: Current number of elements

## API Reference

### Lifecycle Management

#### `queue_create`
```c
Queue* queue_create(int initCapacity);
```
- **Purpose**: Creates a new queue
- **Parameters**:
  - `initCapacity`: Initial capacity (recommended ≥2, automatically set to 2 if <2)
- **Returns**:
  - Success: Queue pointer
  - Failure: NULL (memory allocation failed)
- **Time Complexity**: O(1)

#### `queue_destroy`
```c
void queue_destroy(Queue *q);
```
- **Purpose**: Destroys queue and releases memory
- **Parameters**:
  - `q`: Queue pointer to destroy (safely accepts NULL)
- **Time Complexity**: O(1)

### Status Queries

#### `queue_empty`
```c
bool queue_empty(Queue *q);
```
- **Purpose**: Checks if queue is empty
- **Parameters**:
  - `q`: Queue pointer
- **Returns**:
  - true: Queue is empty or invalid pointer
  - false: Queue contains elements
- **Time Complexity**: O(1)

#### `queue_size`
```c
int queue_size(Queue *q);
```
- **Purpose**: Gets current element count
- **Parameters**:
  - `q`: Queue pointer
- **Returns**:
  - ≥0: Number of elements
  - 0: Queue is empty or invalid pointer
- **Time Complexity**: O(1)

### Core Operations

#### `queue_push`
```c
bool queue_push(Queue *q, int value);
```
- **Purpose**: Inserts element at the tail
- **Parameters**:
  - `q`: Queue pointer
  - `value`: Integer value to insert
- **Returns**:
  - true: Insert successful
  - false: Insert failed (insufficient memory or invalid pointer)
- **Expansion**: Automatically doubles capacity when full
- **Time Complexity**:
  - Average: O(1)
  - Worst-case (during expansion): O(n)

#### `queue_pop`
```c
bool queue_pop(Queue *q);
```
- **Purpose**: Removes element from the head
- **Parameters**:
  - `q`: Queue pointer
- **Returns**:
  - true: Remove successful
  - false: Queue empty or invalid pointer
- **Time Complexity**: O(1)

#### `queue_front`
```c
int queue_front(Queue *q);
```
- **Purpose**: Retrieves (without removing) head element
- **Parameters**:
  - `q`: Queue pointer
- **Returns**:
  - Head element value (returns -1 if queue empty or invalid)
- **Time Complexity**: O(1)

#### `queue_back`
```c
int queue_back(Queue *q);
```
- **Purpose**: Retrieves (without removing) tail element
- **Parameters**:
  - `q`: Queue pointer
- **Returns**:
  - Tail element value (returns -1 if queue empty or invalid)
- **Time Complexity**: O(1)

## Usage Example

### Basic Usage
```c
#include "queue.h"

int main() {
    // Create queue with capacity 3
    Queue *q = queue_create(3);
    
    // Insert elements (auto-expands)
    queue_push(q, 10);
    queue_push(q, 20);
    queue_push(q, 30);
    queue_push(q, 40);  // Triggers expansion
    
    // Process queue
    while (!queue_empty(q)) {
        printf("Front element: %d\n", queue_front(q));
        queue_pop(q);
    }
    
    queue_destroy(q);
    return 0;
}
```

### Expected Output
```
Front element: 10
Front element: 20
Front element: 30
Front element: 40
```

## Design Notes

1. **Circular Buffer**:
   - Uses modulo arithmetic for circular access
   - Formula: `index = (current + 1) % capacity`

2. **Expansion Strategy**:
   - Triggered when `count == capacity`
   - New capacity = Old capacity × 2
   - Maintains element order during expansion

3. **Special Returns**:
   - All fallible operations return bool status
   - Empty queue access returns -1 (check with `queue_empty` first)

## Memory Management
- Each queue requires 1 `malloc` (struct) + 1 `malloc` (data array)
- Must call `queue_destroy` to avoid memory leaks

## Limitations
1. Maximum elements limited by `INT_MAX`
2. Not thread-safe
3. Only supports `int` elements (can be modified for generics)

## Extension Suggestions
1. Add `queue_reserve` for memory pre-allocation
2. Implement iterator interface
3. Add thread-safe wrapper

## Version History
- v1.0 (2023-08-20): Initial release
- v1.1 (2023-08-22): Added order preservation during expansion

---

This documentation includes:
1. Standard API specifications (parameters/returns/complexity)
2. Practical usage examples
3. Internal implementation insights
4. Clear limitations and extension suggestions
5. Version control information

Recommended to save as `QUEUE.md` alongside the header file, or use Doxygen for more detailed documentation generation.
