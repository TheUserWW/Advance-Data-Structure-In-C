#include "priority_queue.h"
#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 100

// Graph representation (adjacency matrix)
int graph[MAX_NODES][MAX_NODES];
bool visited[MAX_NODES];
int distances[MAX_NODES];
int parent[MAX_NODES];

// Initialize graph data structures
void init_graph(int num_nodes) {
    for (int i = 0; i < num_nodes; i++) {
        visited[i] = false;
        distances[i] = -1; // -1 represents infinity/unvisited
        parent[i] = -1;
        for (int j = 0; j < num_nodes; j++) {
            graph[i][j] = 0;
        }
    }
}

// Add edge to the graph
void add_edge(int from, int to) {
    graph[from][to] = 1;
    graph[to][from] = 1; // For undirected graph
}

// BFS implementation using priority queue
void bfs(int start_node, int num_nodes) {
    PriorityQueue* pq = pq_create(MAX_NODES);
    
    // Initialize starting node
    distances[start_node] = 0;
    visited[start_node] = true;
    pq_push(pq, start_node);
    
    while (!pq_empty(pq)) {
        int current_node = pq_pop(pq);
        printf("Visiting node %d (distance: %d)\n", current_node, distances[current_node]);
        
        // Explore neighbors
        for (int neighbor = 0; neighbor < num_nodes; neighbor++) {
            if (graph[current_node][neighbor] && !visited[neighbor]) {
                visited[neighbor] = true;
                distances[neighbor] = distances[current_node] + 1;
                parent[neighbor] = current_node;
                pq_push(pq, neighbor);
            }
        }
    }
    
    pq_free(pq);
}

// Print shortest path from start to target
void print_path(int start, int target) {
    if (target == start) {
        printf("%d ", start);
    } else if (parent[target] == -1) {
        printf("No path exists from %d to %d\n", start, target);
    } else {
        print_path(start, parent[target]);
        printf("%d ", target);
    }
}

int main() {
    int num_nodes = 6;
    init_graph(num_nodes);
    
    // Create a sample graph
    add_edge(0, 1);
    add_edge(0, 2);
    add_edge(1, 3);
    add_edge(2, 3);
    add_edge(2, 4);
    add_edge(3, 5);
    add_edge(4, 5);
    
    printf("BFS Traversal:\n");
    bfs(0, num_nodes);
    
    printf("\nShortest path from 0 to 5:\n");
    print_path(0, 5);
    printf("\n");
    
    return 0;
}
