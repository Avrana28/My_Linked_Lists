// Users are responsable for passing the right CompareFunc
#ifndef MY_LINKED_LIST 
#define MY_LINKED_LIST

typedef int (*CompareFunc)(void*, void*); 

struct Node {
  void* data;
  struct Node* next;
  struct Node* prev;
};

struct Node* create_node(void* data);

struct Node* append(struct Node* head, void* data);

struct Node* delete_node_by_value(struct Node* head, void* data, CompareFunc cmp);

struct Node* pop(struct Node* head);

struct Node* insert(struct Node* head, void* data, int index);

struct Node* delete_at_index(struct Node* head, int index);

void free_list(struct Node* head);

#endif // MY_LINKED_LIST
