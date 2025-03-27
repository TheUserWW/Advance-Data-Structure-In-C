# Stack Library Documentation

This document provides detailed documentation for the dynamic stack implementation with swap capability. Each function includes an example demonstrating its usage.

## Overview

The stack is a Last-In-First-Out (LIFO) data structure implemented using a dynamic array. Key features include:
- Automatic expansion when full
- Memory safety checks
- Stack swapping capability
- Type-safe operations (for integers)

## Constants

- `STACK_INIT_CAPACITY` (4): Default initial capacity
- `STACK_EXPAND_FACTOR` (2): Expansion multiplier when stack is full
- `STACK_EMPTY_VALUE` (-1): Return value when stack is empty

## API Reference

### stack_create

Creates a new stack with specified initial capacity.

**Parameters:**
- `initCapacity`: Initial capacity (uses default if ≤0)

**Returns:**
- Pointer to new stack, or NULL on failure

**Example:**
```c
Stack *s = stack_create(10);  // Create stack with capacity 10
if (!s) {
    printf("Stack creation failed\n");
    return;
}
// ... use stack ...
stack_destroy(s);
```

### stack_destroy

Destroys a stack and frees its memory.

**Parameters:**
- `stack`: Stack pointer (safe to pass NULL)

**Example:**
```c
Stack *s = stack_create(0);
// ... use stack ...
stack_destroy(s);  // Proper cleanup
s = NULL;          // Good practice after destruction
```

### stack_isEmpty

Checks if a stack is empty.

**Parameters:**
- `stack`: Stack pointer to check

**Returns:**
- `true` if stack is empty or NULL, `false` otherwise

**Example:**
```c
Stack *s = stack_create(0);
if (stack_isEmpty(s)) {
    printf("Stack is empty (expected)\n");
}

stack_push(s, 42);
if (!stack_isEmpty(s)) {
    printf("Stack is not empty (expected)\n");
}
stack_destroy(s);
```

### stack_top

Returns the top element without removing it.

**Parameters:**
- `stack`: Stack pointer

**Returns:**
- Top element, or `STACK_EMPTY_VALUE` if empty/NULL

**Example:**
```c
Stack *s = stack_create(0);
printf("Top of empty stack: %d\n", stack_top(s));  // -1

stack_push(s, 10);
stack_push(s, 20);
printf("Current top: %d\n", stack_top(s));  // 20
stack_destroy(s);
```

### stack_push

Pushes an element onto the stack.

**Parameters:**
- `stack`: Stack pointer
- `value`: Integer value to push

**Returns:**
- `true` on success, `false` on failure (NULL or allocation failed)

**Example:**
```c
Stack *s = stack_create(2);  // Small capacity for demonstration
for (int i = 0; i < 5; i++) {
    if (!stack_push(s, i*10)) {
        printf("Push failed at i=%d\n", i);
        break;
    }
    printf("Pushed: %d, size: %d, capacity: %d\n", 
           i*10, stack_size(s), s->capacity);
}
stack_destroy(s);
```

### stack_pop

Removes and optionally returns the top element.

**Parameters:**
- `stack`: Stack pointer
- `pValue`: Pointer to store popped value (can be NULL)

**Returns:**
- `true` if popped successfully, `false` if empty/NULL

**Example:**
```c
Stack *s = stack_create(0);
stack_push(s, 100);
stack_push(s, 200);

int val;
while (stack_pop(s, &val)) {
    printf("Popped: %d\n", val);
}

if (!stack_pop(s, NULL)) {
    printf("No more elements to pop (expected)\n");
}
stack_destroy(s);
```

### stack_size

Returns the number of elements in the stack.

**Parameters:**
- `stack`: Stack pointer

**Returns:**
- Number of elements (0 if NULL or empty)

**Example:**
```c
Stack *s = stack_create(0);
printf("Initial size: %d\n", stack_size(s));  // 0

for (int i = 1; i <= 3; i++) {
    stack_push(s, i);
    printf("Size after push %d: %d\n", i, stack_size(s));
}
stack_destroy(s);
```

### stack_swap

Swaps the contents of two stacks efficiently.

**Parameters:**
- `a`: First stack pointer
- `b`: Second stack pointer

**Note:**
- Works even if stacks have different capacities
- Does nothing if either pointer is NULL

**Example:**
```c
Stack *a = stack_create(0);
Stack *b = stack_create(100);  // Different capacities

stack_push(a, 1);
stack_push(a, 2);
stack_push(b, 99);

printf("Before swap - A top: %d, B top: %d\n", stack_top(a), stack_top(b));
stack_swap(a, b);
printf("After swap - A top: %d, B top: %d\n", stack_top(a), stack_top(b));

stack_destroy(a);
stack_destroy(b);
```

## Usage Notes

1. Always check return values from `stack_create` and `stack_push`
2. Set stack pointers to NULL after destruction
3. The stack is not thread-safe
4. For production use, consider adding error logging
5. The implementation uses `static` linkage - include the header in only one source file or remove `static` for multi-file use

## Memory Management

The stack automatically expands when full (by `STACK_EXPAND_FACTOR`), but never shrinks. Manual capacity management can be added if needed.

## Error Handling

Functions return boolean success/failure or special values (like `STACK_EMPTY_VALUE`) rather than using assertions or exceptions.
