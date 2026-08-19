# `linked_list` Module Documentation

A lightweight, generic doubly linked list implementation in C with built-in type tagging and a graph abstraction layer. Designed as a reusable component within the project, it provides safe memory management for nodes/edges while leaving payload lifecycle control to the caller.

## 📦 Overview
- **Core Structure:** Doubly linked list (`struct Node`) supporting front/back insertion, indexed access, and value-based deletion.
- **Type System:** Payloads are stored as `void*` with an explicit `DataType` tag (`TYPE_INT`, `TYPE_FLOAT`, `TYPE_DOUBLE`, `TYPE_STRING`, `TYPE_CUSTOM`).
- **Graph Layer:** `struct Graph` built on top of the list structure, supporting directed/undirected and weighted/unweighted configurations.
- **Extensibility:** Custom comparison logic via `CompareFunc` and custom printing via `PrintFunc`.

## ✨ Key Features
| Feature | Details |
|---------|---------|
| **Generic Storage** | Stores any data type; type safety enforced at call site via `DataType` enum. |
| **List Operations** | `append`, `push` (front), `pop_back`, indexed insert/delete, value-based delete. |
| **Graph Support** | Vertices store payloads; adjacency lists manage edges automatically based on graph configuration. |
| **Printing Utilities** | Built-in formatters for int/float/double/string; fallback to user-provided `PrintFunc` or pointer dump. |
| **Memory Safety** | Dedicated `free_list()` and `free_graph()` handle all internal node/edge/list allocations. |

## 📖 API Reference

### Linked List Operations
| Function | Description |
|----------|-------------|
| `create_node(data, type)` | Allocates a new list node. Returns `NULL` on failure. |
| `append(head, data, type)` | Adds node to the end of the list. |
| `push(head, data, type)` | Inserts node at the front (O(1)). |
| `pop_back(head)` | Removes and frees the last node. Returns new head or `NULL`. |
| `insert_at_index(head, data, index, type)` | Inserts at position `index` (0-based). Logs error if out of bounds. |
| `delete_at_index(head, index)` | Removes node at `index`. Adjusts pointers safely. |
| `delete_node_by_value(head, data, cmp)` | Deletes first matching node using user-provided comparator (`cmp(a,b)==0` means match). |
| `get_node_at_index(head, index)` | Returns pointer to node at `index`, or `NULL` if invalid. |
| `print_node_data(node, print_custom)` | Prints payload based on stored type; uses `print_custom` for `TYPE_CUSTOM`. |
| `free_list(head)` | Traverses and frees all nodes in the list. **Does not free payload data.** |

### Graph Operations
| Function | Description |
|----------|-------------|
| `create_graph(is_directed, is_weighted)` | Initializes graph structure. Flags control edge behavior. |
| `add_vertex(graph, data, type)` | Creates vertex and appends it to internal vertex list. |
| `add_edge(graph, from, to)` | Adds unweighted edge. Falls back to weighted with weight `1.0f` if graph is configured as weighted. |
| `add_weighted_edge(graph, from, to, weight)` | Adds directed/undirected weighted edge based on graph config. Returns early if graph isn't weighted. |
| `free_graph(graph)` | Safely frees all edges (if weighted), adjacency lists, vertices, vertex list, and graph struct. **Does not free payload data.** |

## 💡 Usage Examples

### Basic List with Custom Comparison
```c
#include "linked_list.h"

int compare_ints(void* a, void* b) {
    return *(int*)a - *(int*)b; // Returns 0 on match
}

void print_custom_data(const void* data) {
    printf("Custom payload: %p", data);
}

// ...
struct Node* head = NULL;
int value = 42;
head = append(head, &value, TYPE_INT);

delete_node_by_value(head, &value, compare_ints); // Safe removal by value
free_list(head); // Frees nodes only; caller must manage `value` if dynamically allocated
```

### Weighted Undirected Graph
```c
struct Graph* g = create_graph(0, 1); // undirected, weighted

int node_a_data = 10, node_b_data = 20;
struct Graph_Node* A = add_vertex(g, &node_a_data, TYPE_INT);
struct Graph_Node* B = add_vertex(g, &node_b_data, TYPE_INT);

add_weighted_edge(g, A, B, 3.5f); // Automatically creates bidirectional weighted edges
free_graph(g); // Cleans up all internal graph allocations
```

## ⚠️ Important Notes & Responsibilities
1. **Payload Lifecycle:** The library stores pointers to your data (`void*`). It **never copies or frees payload memory**. You are responsible for ensuring referenced data remains valid while the list/graph exists, and for freeing it after `free_list()`/`free_graph()`.
2. **Comparison Functions:** As noted in the header: *"Users are responsable for passing the right CompareFunc"*. The comparator must match the actual stored type and return `0` when values are equal (standard C convention). Mismatched comparators lead to undefined behavior or failed deletions.
3. **Error Handling:** Allocation failures, invalid indices, or missing values log messages to `stderr` and return safely (`NULL`, original head, or unchanged state). No exceptions or error codes are returned.
4. **Thread Safety:** Not thread-safe. Concurrent reads/writes require external synchronization.

## 🛠 Integration & Building
- Drop `linked_list.h` and `linked_list.c` into your project's source tree.
- Compile with standard C99+ compiler:  
  ```bash
  gcc -std=c99 -Wall -Wextra linked_list.c -c -o linked_list.o
  ```
- Link the object file or archive against your application. No external dependencies required (`stdlib.h`, `stdio.h` only).

---
*This module is maintained as a standalone branch/component within the project. API stability should be verified before cross-module refactoring.*


# Disclaimer
This README.md is AI generated but the code is by me, I did not want to write the explenation of something that alredy exist and probably done better
