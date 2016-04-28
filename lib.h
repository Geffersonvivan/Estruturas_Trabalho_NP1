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

node * mergeSort(node *head);
node * initNode();
node * insertNode(node *current, int info);
node * getNodeByValue(node *first, int value);
int deleteNode(node *current);
node * deleteNodesWithValue(node *first, int value);
int deleteAllNodes(node *first);
void printNode(node *head);
nodeset * initNodeSet();
nodeset * insertNodeSet(nodeset *current);
nodeset * deleteNodeSet(nodeset *current);
void printNodeSets(nodeset *first);
nodeset * getNodeSet(nodeset *first, int index);
node * getUnion(node *head1, node *head2);
node * getInt(node *head1, node *head2);
node * getDif(node *head1, node *head2);
node * executeOp(nodeset *head, int op);
void alloc_error();
void invalid_option();
void no_nodesets();
void invalid_value();
