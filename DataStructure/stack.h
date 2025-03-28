/**
 * @file stack.h
 * @brief A complete stack data structure implementation
 * 
 * This header provides a full implementation of a stack data structure including:
 * - Initialization
 * - Push/pop operations
 * - Top element access
 * - Size checking
 * - Stack swapping
 * - Memory management
 * 
 * Implementation features:
 * - Linked list based implementation
 * - Dynamic memory allocation
 * - Not thread-safe (for single-threaded use)
 * - Comprehensive error handling
 * - Complete memory management
 */

 #ifndef STACK_H
 #define STACK_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 
 /**
  * @brief Stack node structure
  * 
  * Represents a single element in the stack containing:
  * - The data value
  * - Pointer to the next node
  */
 typedef struct StackNode {
     int data;               ///< Data stored in the node
     struct StackNode* next; ///< Pointer to the next node
 } StackNode;
 
 /**
  * @brief Stack structure
  * 
  * Contains the metadata for the stack:
  * - Pointer to the top node
  * - Current size of the stack
  */
 typedef struct {
     StackNode* top;  ///< Pointer to the top node of the stack
     int size;        ///< Current number of elements in the stack
 } Stack;
 
 /* ====================== Basic Operations ====================== */
 
 /**
  * @brief Creates a new empty stack
  * 
  * @return Stack* Pointer to the newly created stack
  * @note The caller must call stack_free() to release memory
  */
 static Stack* stack_create() {
     Stack* s = (Stack*)malloc(sizeof(Stack));
     if (s == NULL) {
         fprintf(stderr, "Error: Memory allocation failed for stack\n");
         exit(EXIT_FAILURE);
     }
     s->top = NULL;
     s->size = 0;
     return s;
 }
 
 /**
  * @brief Checks if the stack is empty
  * 
  * @param s Pointer to the stack
  * @return true if stack is empty
  * @return false if stack contains elements
  */
 static bool stack_isEmpty(Stack* s) {
     return s->top == NULL;
 }
 
 /**
  * @brief Pushes an element onto the stack
  * 
  * @param s Pointer to the stack
  * @param item Value to push onto the stack
  */
 static void stack_push(Stack* s, int item) {
     StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
     if (newNode == NULL) {
         fprintf(stderr, "Error: Memory allocation failed for stack node\n");
         exit(EXIT_FAILURE);
     }
     newNode->data = item;
     newNode->next = s->top;  // New node points to previous top
     s->top = newNode;        // Update top pointer
     s->size++;               // Increment size counter
 }
 
 /**
  * @brief Pops an element from the top of the stack
  * 
  * @param s Pointer to the stack
  * @return int The popped value
  * @warning Calling this on an empty stack will terminate the program
  */
 static int stack_pop(Stack* s) {
     if (stack_isEmpty(s)) {
         fprintf(stderr, "Error: Stack underflow (pop from empty stack)\n");
         exit(EXIT_FAILURE);
     }
     StackNode* temp = s->top;  // Save current top
     int poppedItem = temp->data;
     s->top = s->top->next;     // Move top pointer
     free(temp);                // Free old top node
     s->size--;                 // Decrement size counter
     return poppedItem;
 }
 
 /* ====================== Accessors ====================== */
 
 /**
  * @brief Returns the top element without removing it
  * 
  * @param s Pointer to the stack
  * @return int Value at the top of the stack
  * @warning Calling this on an empty stack will terminate the program
  */
 static int stack_top(Stack* s) {
     if (stack_isEmpty(s)) {
         fprintf(stderr, "Error: Accessing top of empty stack\n");
         exit(EXIT_FAILURE);
     }
     return s->top->data;
 }
 
 /**
  * @brief Returns the current size of the stack
  * 
  * @param s Pointer to the stack
  * @return int Number of elements in the stack
  */
 static int stack_size(Stack* s) {
     return s->size;
 }
 
 /* ====================== Advanced Operations ====================== */
 
 /**
  * @brief Swaps the contents of two stacks
  * 
  * Efficiently swaps all contents between two stacks including:
  * - Top pointers
  * - Size counters
  * 
  * @param s1 Pointer to first stack
  * @param s2 Pointer to second stack
  */
 static void stack_swap(Stack* s1, Stack* s2) {
     // Swap top pointers
     StackNode* tempTop = s1->top;
     s1->top = s2->top;
     s2->top = tempTop;
     
     // Swap size counters
     int tempSize = s1->size;
     s1->size = s2->size;
     s2->size = tempSize;
 }
 
 /* ====================== Memory Management ====================== */
 
 /**
  * @brief Frees all memory associated with a stack
  * 
  * Releases all stack nodes and the stack structure itself
  * 
  * @param s Pointer to the stack to free
  * @note The stack pointer becomes invalid after this call
  */
 static void stack_free(Stack* s) {
     // Pop all elements to free nodes
     while (!stack_isEmpty(s)) {
         stack_pop(s);
     }
     // Free the stack structure itself
     free(s);
 }
 
 #endif // STACK_H
