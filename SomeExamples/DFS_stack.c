#include "stack.h"  // 使用之前定义的栈实现
#include <stdio.h>

#define MAX_VERTICES 100

// 图的邻接矩阵表示
typedef struct {
    int matrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

// 初始化图
void graph_init(Graph* g, int numVertices) {
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numVertices; j++) {
            g->matrix[i][j] = 0;
        }
    }
}

// 添加边
void graph_addEdge(Graph* g, int src, int dest) {
    g->matrix[src][dest] = 1;
    g->matrix[dest][src] = 1; // 无向图
}

// 使用栈实现的DFS
void dfs_stack(Graph* g, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    Stack* s = stack_create();
    
    // 标记起始顶点为已访问并压入栈
    visited[startVertex] = 1;
    stack_push(s, startVertex);
    
    printf("DFS traversal starting from vertex %d: ", startVertex);
    
    while (!stack_isEmpty(s)) {
        int currentVertex = stack_top(s);
        stack_pop(s);
        printf("%d ", currentVertex);
        
        // 访问所有邻接顶点
        for (int i = 0; i < g->numVertices; i++) {
            if (g->matrix[currentVertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                stack_push(s, i);
            }
        }
    }
    
    stack_free(s);
    printf("\n");
}

int main() {
    Graph g;
    graph_init(&g, 6);
    
    // 添加边
    graph_addEdge(&g, 0, 1);
    graph_addEdge(&g, 0, 2);
    graph_addEdge(&g, 1, 3);
    graph_addEdge(&g, 1, 4);
    graph_addEdge(&g, 2, 4);
    graph_addEdge(&g, 3, 4);
    graph_addEdge(&g, 3, 5);
    graph_addEdge(&g, 4, 5);
    
    // 从顶点0开始DFS
    dfs_stack(&g, 0);
    
    return 0;
}