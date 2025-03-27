/**
 * @file stack.h
 * @brief 动态栈实现（带交换功能）Stack with swap capability
 */

 #ifndef STACK_H
 #define STACK_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdbool.h>
 
 #ifdef __cplusplus
 extern "C" {
 #endif
 
 // ==================== 结构定义 ====================
 typedef struct {
     int *array;     // 动态数组
     int top;        // 栈顶索引（-1为空）
     int capacity;   // 当前容量
 } Stack;
 
 // ==================== 常量定义 ====================
 #define STACK_INIT_CAPACITY 4   // 默认初始容量
 #define STACK_EXPAND_FACTOR 2   // 扩容倍数
 #define STACK_EMPTY_VALUE -1    // 栈空返回值
 
 // ==================== API声明 ====================
 
 /**
  * @brief 创建新栈
  * @param initCapacity 初始容量（若≤0则使用默认值）
  * @return 栈指针（失败返回NULL）
  */
 static Stack* stack_create(int initCapacity);
 
 /**
  * @brief 销毁栈
  * @param stack 栈指针（可安全传入NULL）
  */
 static void stack_destroy(Stack *stack);
 
 /**
  * @brief 检查栈空
  * @param stack 栈指针
  * @return true为空栈
  */
 static bool stack_isEmpty(const Stack *stack);
 
 /**
  * @brief 直接获取栈顶元素
  * @param stack 栈指针
  * @return 栈顶元素（栈空返回STACK_EMPTY_VALUE）
  */
 static int stack_top(const Stack *stack);
 
 /**
  * @brief 压入元素
  * @param stack 栈指针
  * @param value 要压入的值
  * @return 成功返回true，失败返回false
  */
 static bool stack_push(Stack *stack, int value);
 
 /**
  * @brief 弹出元素
  * @param stack 栈指针
  * @param[out] pValue 接收弹出值的指针（可NULL）
  * @return 成功返回true，栈空返回false
  */
 static bool stack_pop(Stack *stack, int *pValue);
 
 /**
  * @brief 获取元素数量
  * @param stack 栈指针
  * @return 当前栈中元素个数
  */
 static int stack_size(const Stack *stack);
 
 /**
  * @brief 完全交换两个栈的内容
  * @param a 第一个栈指针
  * @param b 第二个栈指针
  * @note 即使两个栈容量不同也能正确交换
  */
 static void stack_swap(Stack *a, Stack *b);
 
 // ==================== 实现部分 ====================
 #ifdef STACK_IMPLEMENTATION
 
 static Stack* stack_create(int initCapacity) {
     Stack *stack = (Stack*)malloc(sizeof(Stack));
     if (!stack) return NULL;
 
     int capacity = (initCapacity > 0) ? initCapacity : STACK_INIT_CAPACITY;
     stack->array = (int*)malloc(capacity * sizeof(int));
     if (!stack->array) {
         free(stack);
         return NULL;
     }
 
     stack->top = -1;
     stack->capacity = capacity;
     return stack;
 }
 
 static void stack_destroy(Stack *stack) {
     if (stack) {
         free(stack->array);
         free(stack);
     }
 }
 
 static bool stack_isEmpty(const Stack *stack) {
     return !stack || stack->top == -1;
 }
 
 static int stack_top(const Stack *stack) {
     return stack_isEmpty(stack) ? STACK_EMPTY_VALUE : stack->array[stack->top];
 }
 
 static bool stack_expand(Stack *stack) {
     if (!stack) return false;
     
     int newCap = stack->capacity * STACK_EXPAND_FACTOR;
     int *newArray = (int*)realloc(stack->array, newCap * sizeof(int));
     if (!newArray) return false;
 
     stack->array = newArray;
     stack->capacity = newCap;
     return true;
 }
 
 static bool stack_push(Stack *stack, int value) {
     if (!stack) return false;
     
     if (stack->top == stack->capacity - 1 && !stack_expand(stack)) {
         return false;
     }
     
     stack->array[++stack->top] = value;
     return true;
 }
 
 static bool stack_pop(Stack *stack, int *pValue) {
     if (stack_isEmpty(stack)) return false;
     
     if (pValue) {
         *pValue = stack->array[stack->top];
     }
     stack->top--;
     return true;
 }
 
 static int stack_size(const Stack *stack) {
     return stack ? stack->top + 1 : 0;
 }
 
 static void stack_swap(Stack *a, Stack *b) {
     if (!a || !b) return;
     
     // 交换数组指针
     int *tmp_array = a->array;
     a->array = b->array;
     b->array = tmp_array;
     
     // 交换栈顶索引
     int tmp_top = a->top;
     a->top = b->top;
     b->top = tmp_top;
     
     // 交换容量
     int tmp_cap = a->capacity;
     a->capacity = b->capacity;
     b->capacity = tmp_cap;
 }
 
 #endif // STACK_IMPLEMENTATION
 
 #ifdef __cplusplus
 }
 #endif
 
 #endif // STACK_H
