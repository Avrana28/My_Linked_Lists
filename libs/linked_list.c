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
