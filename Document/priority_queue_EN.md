# **Priority Queue (Min-Heap) Implementation Documentation**

---

## **1. Introduction**
This document describes the implementation of a **priority queue** based on a **min-heap**. This priority queue efficiently supports insertion (`push`), deletion (`pop`), and retrieval of the minimum (`front`) and maximum (`back`) elements.

---

## **2. Data Structure**
The priority queue is implemented using a **binary min-heap**, where:
- The smallest element is always at the root node (`heap[1]`)
- The value of each parent node ≤ the values of its child nodes
- The heap is stored in an array starting from index `1` for easier parent-child node calculations

---

## **3. Function Descriptions**

### **3.1 `pq_create()` - Create a Priority Queue**
**Function**:  
Allocates memory to create a new empty priority queue with an initial capacity of `0`.  
**Time Complexity**: \(O(1)\)  
**Space Complexity**: \(O(1)\)  

**Example**:
```c
PriorityQueue *pq = pq_create();  // Creates an empty priority queue
```

---

### **3.2 `pq_free(PriorityQueue *pq)` - Free Memory**
**Function**:  
Releases the memory occupied by the heap array and the priority queue structure.  
**Time Complexity**: \(O(1)\)  
**Space Complexity**: \(O(1)\)  

**Example**:
```c
pq_free(pq);  // Releases all memory used by the priority queue
```

---

### **3.3 `pq_swap(int *a, int *b)` - Swap Two Elements**
**Function**:  
A helper function to swap two integer values.  
**Time Complexity**: \(O(1)\)  
**Space Complexity**: \(O(1)\)  

**Example**:
```c
int x = 5, y = 10;
pq_swap(&x, &y);  // After swapping, x=10, y=5
```

---

### **3.4 `pq_swim(PriorityQueue *pq, int k)` - Swim Operation**
**Function**:  
Moves an element upward to maintain the min-heap property.  
**Time Complexity**: \(O(\log n)\) (worst-case: moves from a leaf node to the root)  
**Space Complexity**: \(O(1)\)  

**Example**:
```c
pq_push(pq, 3);  // If 3 is smaller than its parent, it swims up
```

---

### **3.5 `pq_sink(PriorityQueue *pq, int k)` - Sink Operation**
**Function**:  
Moves an element downward to maintain the min-heap property.  
**Time Complexity**: \(O(\log n)\) (worst-case: moves from the root to a leaf node)  
**Space Complexity**: \(O(1)\)  

**Example**:
```c
pq_pop(pq);  // After swapping the root with the last element, the new root sinks down
```

---

### **3.6 `pq_empty(PriorityQueue *pq)` - Check if Empty**
**Function**:  
Determines whether the priority queue is empty.  
**Time Complexity**: \(O(1)\)  
**Space Complexity**: \(O(1)\)  

**Example**:
```c
if (pq_empty(pq)) printf("Queue is empty!\n");
```

---

### **3.7 `pq_push(PriorityQueue *pq, int value)` - Insert Element**
**Function**:  
Inserts a new element into the priority queue and adjusts the heap structure.
- If the heap is full, **doubles** the capacity (using `realloc`)
- Then performs a **swim** operation to maintain the heap property

**Time Complexity**:
- Average: \(O(\log n)\) (swim operation)
- Worst-case (during expansion): \(O(n)\)

**Space Complexity**:
- Amortized \(O(1)\) (due to doubling strategy)

**Example**:
```c
pq_push(pq, 10);  // Inserts 10 into the heap
pq_push(pq, 5);   // Inserts 5, which may swim up
```

---

### **3.8 `pq_front(PriorityQueue *pq)` - Get Minimum Element**
**Function**:  
Returns the smallest element (the root of the min-heap).  
**Time Complexity**: \(O(1)\)  
**Space Complexity**: \(O(1)\)  

**Example**:
```c
int min_val = pq_front(pq);  // Retrieves the smallest element
```

---

### **3.9 `pq_back(PriorityQueue *pq)` - Get Maximum Element**
**Function**:  
Finds the largest element (which must be in a leaf node).  
**Time Complexity**: \(O(n)\) (scans all leaf nodes in the worst case)  
**Space Complexity**: \(O(1)\)  

**Example**:
```c
int max_val = pq_back(pq);  // Retrieves the largest element in the heap
```

---

### **3.10 `pq_pop(PriorityQueue *pq)` - Remove Minimum Element**
**Function**:  
Removes and returns the smallest element.
- Swaps the root node with the last element
- Performs a **sink** operation to restore the heap property
- If the heap becomes too sparse, **halves** the capacity (using `realloc`)

**Time Complexity**:
- Average: \(O(\log n)\) (sink operation)
- Worst-case (during contraction): \(O(n)\)

**Space Complexity**:
- Amortized \(O(1)\) (due to halving strategy)

**Example**:
```c
int min_val = pq_pop(pq);  // Removes and returns the smallest element
```

---

### **3.11 `pq_size(PriorityQueue *pq)` - Get Element Count**
**Function**:  
Returns the number of elements in the priority queue.  
**Time Complexity**: \(O(1)\)  
**Space Complexity**: \(O(1)\)  

**Example**:
```c
int size = pq_size(pq);  // Gets the current number of elements
```

---

## **4. Time Complexity Summary**
| Operation | Average Case | Worst Case |
|-----------|-------------|------------|
| `pq_create()` | \(O(1)\) | \(O(1)\) |
| `pq_free()` | \(O(1)\) | \(O(1)\) |
| `pq_push()` | \(O(\log n)\) | \(O(n)\) (during expansion) |
| `pq_pop()` | \(O(\log n)\) | \(O(n)\) (during contraction) |
| `pq_front()` | \(O(1)\) | \(O(1)\) |
| `pq_back()` | \(O(n)\) | \(O(n)\) |
| `pq_empty()` | \(O(1)\) | \(O(1)\) |
| `pq_size()` | \(O(1)\) | \(O(1)\) |

---

## **5. Conclusion**
This implementation provides an efficient **min-heap-based priority queue** with:
- Fast insertion and deletion operations (average `O(log n)`)
- Automatic capacity adjustment (amortized `O(1)` space per insertion)
- Convenient access to the minimum (`O(1)`) and maximum (`O(n)`) elements
