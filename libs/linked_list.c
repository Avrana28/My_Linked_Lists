#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>


struct Node* create_node(void* data){
  struct Node* new = calloc(1, sizeof(struct Node));
  if (new == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    return NULL;
  }
  new->data = data;
  return new;
}

struct Node* append(struct Node* head, void* data) {
  if (head == NULL) {
    return create_node(data);
  }
  if (head->next == NULL) {
    struct Node* new_node = create_node(data);
    if (new_node == NULL) return head;
    head->next = new_node;
    new_node->prev = head;
    return head;
  }

  head->next = append(head->next, data);
  return head;
}

struct Node* pop(struct Node* head) {
  if (head == NULL) {
    fprintf(stderr, "No elements to pop\n");
    return NULL;
  }
  if (head->next == NULL) {
    free(head);

    return NULL;
  }
  head->next = pop(head->next);
  return head;
}

struct Node* insert(struct Node* head, void* data, int index) {
  if (head == NULL && index > 0) {
    fprintf(stderr, "Index out of scope\n");
    return head;
  }
  if (index == 0) {
    struct Node* new_node = create_node(data);
    if (new_node == NULL) return head;
    
    new_node->next = head;
    if (head != NULL) {
      head->prev = new_node;
    }
    return new_node;
  }
  struct Node* new_next = insert(head->next, data, --index);

  head->next = new_next;

  if (new_next != NULL) {
    new_next->prev = head;
  }
  
  return head;
}

struct Node* delete_node_by_value(struct Node* head, void* data, CompareFunc cmp){
  if (head == NULL) {
    fprintf(stderr, "Value not Found");
    return NULL;
  }
  if(cmp(head->data, data) == 0) {
    struct Node* next_node = head->next;
    free(head);
    return next_node;
  }

  head->next = delete_node_by_value(head->next, data, cmp);
  if (head->next != NULL) {
    head->next->prev = head;
  }

  return head;
}

void free_list(struct Node* head) {
  if (head == NULL) {
    return;
  }
  struct Node* next = head->next;
  free(head);
  free_list(next);
}
