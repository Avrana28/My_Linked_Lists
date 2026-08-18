#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>


struct Node* create_node(void* data, DataType type){
  struct Node* new = calloc(1, sizeof(struct Node));
  if (new == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    return NULL;
  }
  new->data = data;
  new->type = type;
  return new;
}

struct Node *append(struct Node *head, void *data, DataType type) {
  struct Node *new_node = create_node(data, type);
  if (new_node == NULL)
    return head;
  
  if (head == NULL) {
    return new_node;
  }
  struct Node* current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->next = new_node;
  new_node->prev = current;
  return head;
}

struct Node* push(struct Node* head, void* data, DataType type) {
  if (head == NULL) {
    head = create_node(data, type);
    return head;
  }
  struct Node* new_node = create_node(data, type);
  if (new_node == NULL)
    return head;
  head->prev = new_node;
  new_node->next = head;
  return new_node;
}

struct Node* pop_back(struct Node* head) {
  if (head == NULL) {
    fprintf(stderr, "No elements to pop\n");
    return NULL;
  }
  if (head->next == NULL) {
    free(head);
    return NULL;
  }
  struct Node *current = head;
  while (current->next != NULL) {
    current = current->next;
  }
  current->prev->next = NULL;
  free(current);
  
  return head;
}

struct Node* insert_at_index(struct Node *head, void *data, int index, DataType type) {
  if (index < 0) return head;
  struct Node *new_node = create_node(data, type);
  if (new_node == NULL)
    return head;

  if (index == 0 || head == NULL) {
    new_node->next = head;
    if (head != NULL) {
      head->prev = new_node;
    }
    return new_node;
  }
  
  struct Node* current = head;
  int len = 1;
  while (current->next != NULL && len < index) {
    current = current->next;
    len++;
  }
  if (len < index) {
    fprintf(stderr, "Index out of scope.");
    free(new_node);
    return head;
  }

  new_node->next = current->next;
  new_node->prev = current;
  if (current->next != NULL) {
    current->next->prev = new_node;
  }
  current->next = new_node;
  return head;
}

struct Node* delete_at_index(struct Node* head, int index) {
  if (index < 0 || head == NULL)
    return head;
  if (index == 0) {
    struct Node *new_head = head->next;
    free(head);
    if (new_head != NULL)
      new_head->prev = NULL;
    return new_head;
  }
  struct Node *current = head;
  for (int i = 0; i < index && current != NULL; ++i) {
    current = current->next;
  }
  if (current == NULL) {
    fprintf(stderr, "Index %d  out of scope.", index);
   return head;
  }

  current->prev->next = current->next;
  if (current->next != NULL) {
    current->next->prev = current->prev;
  }
  free(current);
  return head;
}
  

struct Node* delete_node_by_value(struct Node* head, void* data, CompareFunc cmp) {
  struct Node* current = head;
  while (current != NULL) {
    if (cmp(current->data, data) == 0) {
      if (head == current) {
        struct Node *new_head = head->next;
        free(head);
	if (new_head != NULL){
	  new_head->prev = NULL;
	}
	return new_head;
      }

      current->prev->next = current->next;
      if (current->next != NULL) {
        current->next->prev = current->prev;
      }
      
      free(current);
      return head;
    }
    current = current->next;
  }
  fprintf(stderr, "Value not found.");
  return head;
}


struct Node* get_node_at_index(const struct Node *head, int index) {
  if (head == NULL || index < 0) return NULL;
  const struct Node* current = head;
  for (int i = 0; i < index; ++i) {
    current = current->next;
    if (current == NULL) {
      fprintf(stderr, "Index %d out of scope.", index);
      return NULL;
    }
  }
  return (struct Node*)current;
}

DataType get_node_type(const struct Node *node) {
  return (node != NULL) ? node->type : TYPE_CUSTOM;
}

void print_node_data(const struct Node *node, PrintFunc print_custom) {
  if (node == NULL) return;
  switch(node->type) {
  case TYPE_INT:
    printf("%d", *(int *)node->data);
    break;
  case TYPE_FLOAT:
    printf("%f", *(float *)node->data);
    break;
  case TYPE_DOUBLE:
    printf("%f", *(double *)node->data);
    break;
  case TYPE_STRING:
    printf("%s", (char *)node->data);
    break;
  case TYPE_CUSTOM:
    if (print_custom != NULL) {
      print_custom(node->data);
    } else {
      printf("[Custom Data @ %p]", node->data);
    }
    break;
  default:
    fprintf(stderr, "Corrupted data type");
    break;
  }
}

void free_list(struct Node *head) {
  struct Node* current = head;
  while (current != NULL) {
    struct Node *next = current->next;
    free(current);
    current = next;
  }
}

struct Graph* create_graph(int is_directed, int is_weighted) {
  struct Graph* graph = calloc(1, sizeof(struct Graph));
  if (graph == NULL) {
    fprintf(stderr, "Failed to allocate memory");
    free(graph);
    return NULL;
  }
  graph->all_vertices = NULL;
  graph->is_directed = is_directed;
  graph->is_weighted = is_weighted;
  return graph;
}

struct Graph_Node* add_vertex(struct Graph* graph, void* data, DataType type) {
  struct Graph_Node* new_node = calloc(1, sizeof(struct Graph_Node));
  if (new_node == NULL) {
    fprintf(stderr, "Failed to allocate memory");
    return NULL;
  }
  
  new_node->data = data;
  new_node->type = type;
  
  graph->all_vertices = append(graph->all_vertices, new_node, TYPE_CUSTOM);
  return new_node;
}

void add_edge(struct Graph* graph, struct Graph_Node* from, struct Graph_Node* to) {
  if (graph == NULL || from == NULL || to == NULL) {
    fprintf(stderr, "Invalid function input");
    return;
  }
  if (graph->is_weighted == 1) {
    return add_weighted_edge(graph, from, to, 1.0f);
  }
  if (graph->is_directed == 1) {
    from->connected_nodes = append(from->connected_nodes, to, TYPE_CUSTOM);
  } else {
    from->connected_nodes = append(from->connected_nodes, to, TYPE_CUSTOM);
    to->connected_nodes = append(to->connected_nodes, from, TYPE_CUSTOM);
  }

  return;
}

void add_weighted_edge(struct Graph* graph, struct Graph_Node* from, struct Graph_Node* to, float weight) {
  if (graph == NULL || from == NULL || to == NULL) {
    fprintf(stderr, "Invalid function input");
    return;
  }
  if (graph->is_weighted != 1) {
    fprintf(stderr, "Graph is not weighted");
    return;
  }
  if (graph->is_directed == 1) {
    struct Edge* edge_to = calloc(1 sizeof(struct Edge));
    if (edge_to == NULL) {
      fprintf(stderr, "Failed to allocate memory,");
      free(edge_to);
      return;
    }
    edge_to->weight = weight;
    edge_to->dest = to;
    from->connected_nodes = append(from->connected_nodes, edge_to, TYPE_CUSTOM);
  } else {
    struct Edge* edge_to = calloc(1 sizeof(struct Edge));
    struct Edge* edge_from = calloc(1 sizeof(struct Edge));
    if (edge_to == NULL || edge_from == NULL) {
      fprintf(stderr, "Failed to allocate memory,");
      free(edge_to);
      free(edge_from);
      return;
    }
    edge_to->weight = weight;
    edge_to->dest = to;
    edge_from->weight = weight;
    edge_from->dest = from;
    from->connected_nodes = append(from->connected_nodes, edge_to, TYPE_CUSTOM);
    to->connected_nodes = append(to->connected_nodes, edge_from, TYPE_CUSTOM);
  }
}
  
  
void free_graph(struct Graph* graph) {
  if (graph == NULL) return;

  struct Node* list = graph->all_vertices;
  while (list != NULL) {
    struct Graph_Node* current = (struct Graph_Node*)list->data;
    if (current != NULL){
      if (graph->is_weighted == 1) {
	struct Node* current_list = current->connected_nodes;
	while (current_list != NULL) {
	  struct Edge* current_edge = (struct Edge*)current_list->data;
	  free(current_edge);
	  current_list = current_list->next;
	}
      }
      free_list(current->connected_nodes);
      free(current);
      list = list->next;
  }
  free_list(graph->all_vertices);
  free(graph);
  return;
}

