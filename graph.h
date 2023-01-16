#ifndef GRAPH_
#define GRAPH_


typedef struct GRAPH_NODE_ *pnode;;

typedef struct Queue_ {
    int priority;
    pnode point;
    struct Queue_ *next;
} queue,*pqueue;

typedef struct edge_ {
    int weight;
    pnode endpoint;
    struct edge_ *next;
} edge, *pedge;


typedef struct GRAPH_NODE_ {
    int node_num;
    pedge edges;
    struct GRAPH_NODE_ *next;
} node, *pnode;

//Queue start
void dijkastra( pnode , int *);
pqueue pop(pqueue *);
void add(pqueue *, pqueue );
//Queue end

pnode findNode(pnode *, int);
int getCommand(char *);
int build_graph_cmd(pnode *head);
int insert_node_cmd(pnode *head);
int delete_node_cmd(pnode *head, int);
void swap(int *, int *);
void prmot(int *, int , int , int [720][6], int *);
void deleteGraph_cmd(pnode* head);
int shortsPath_cmd(pnode head);
int TSP_cmd(pnode head);

#endif
