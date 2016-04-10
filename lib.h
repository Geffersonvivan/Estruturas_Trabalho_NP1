typedef struct _node{
    int info;
    struct _node *next;
    struct _node *prev;
} node;

typedef struct _nodeset{
    node *head;
    struct _nodeset *next;
    struct _nodeset *prev;
} nodeset;

node * init();
nodeset * init_nodeset();
node * push(node *current, int info);
int pop(node *current);
void print(node *head);
nodeset * push_nodeset(nodeset *current);
int pop_nodeset(nodeset *current);
void print_nodesets(nodeset *head);
nodeset * get_nodeset(nodeset *first, int index);
void alloc_error();
void invalid_option();
void no_nodesets();
