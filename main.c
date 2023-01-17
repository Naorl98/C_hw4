#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
int main()
{
    char x;
    int lenGraph;
    pnode head =NULL;
    pnode new;
    while (scanf("%c",&x) != EOF)
    {
        switch(x){
        case 'A':
        
            deleteGraph_cmd(&head);
            scanf("%d",&lenGraph);
            pnode create = NULL;
            for (int i = lenGraph-1; i >=0; i--){
                 new = (pnode) malloc(sizeof(node));
                new->node_num = i;
                new->edges = NULL;
                new->next = create;
                create = new;
            }
            head = create;
            break;
    
        case 'n':

            build_graph_cmd(&head,lenGraph);
            break;
        case 'B':
        
            insert_node_cmd(&head);
            break;
        case 'D':
        
            delete_node_cmd(&head);
            break;
        case 'S':
        
            shortsPath_cmd(head);
            break;
        case 'T':
        
            TSP_cmd(head);
            break;
    }
}

    deleteGraph_cmd(&head);
    return 0;

}
