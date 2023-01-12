#ifndef GRAPH_
#define GRAPH_
#include <stdio.h>
#include <malloc.h>

typedef struct GRAPH_NODE_ *pnode;;

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
pnode findNode(pnode *head, int);
int getCommand(char *);
int build_graph_cmd(pnode *head);
int insert_node_cmd(pnode *head);
int delete_node_cmd(pnode *head);
void printGraph_cmd(pnode head); //for self debug
int deleteGraph_cmd(pnode* head);
int shortsPath_cmd(pnode head);
int TSP_cmd(pnode head);

#endif
