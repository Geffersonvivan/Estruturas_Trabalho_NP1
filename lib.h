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

node * initNode();
node * insertNode(node *current, int info);
int deleteNode(node *current);
void printNode(node *head);
nodeset * initNodeSet();
nodeset * insertNodeSet(nodeset *current);
int deleteNodeSet(nodeset *current);
void printNodeSets(nodeset *first);
nodeset * getNodeSet(nodeset *first, int index);



void alloc_error();
void invalid_option();
void no_nodesets();
