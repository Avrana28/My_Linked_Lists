// Users are responsable for passing the right CompareFunc
#ifndef MY_LINKED_LIST 
#define MY_LINKED_LIST

typedef int (*CompareFunc)(void*, void*);

typedef void (*PrintFunc)(const void*);

typedef enum {
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_DOUBLE,
  TYPE_STRING,
  TYPE_CUSTOM
} DataType;

struct Node {
  void *data;
  DataType type;
  struct Node* next;
  struct Node* prev;
};

struct Node* create_node(void* data, DataType type);

struct Node* append(struct Node* head, void* data, DataType type);

struct Node* delete_node_by_value(struct Node* head, void* data, CompareFunc cmp);

struct Node* pop_back(struct Node* head);

struct Node* push(struct Node* head, void* data, DataType type);

struct Node* insert_at_index(struct Node* head, void* data, int index, DataType type);

struct Node *delete_at_index(struct Node *head, int index);

struct Node* get_node_at_index(const struct Node* head, int index);

DataType get_node_type(const struct Node *node);

void print_node_data(const struct Node* node, PrintFunc print_custom);

void free_list(struct Node* head);

#endif // MY_LINKED_LIST
