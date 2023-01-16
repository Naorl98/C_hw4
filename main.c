#include <stdio.h>
#include "graph.h"
#include <stdlib.h>

int main()
{

    pnode head;
    int getX[2];
    getX[0] = fgetc(stdin);
    getX[1] = fgetc(stdin);
    int x = getX[0];
    while (x != EOF)
    {
        if (x == 'A')
        {
            x = build_graph_cmd(&head);
        }
        else if (x == 'B')
        {
            x = insert_node_cmd(&head);
        }
        else if (x == 'D')
        {
            x = delete_node_cmd(&head, -1);
        }
        else if (x == 'S')
        {
            x = shortsPath_cmd(head);
        }
        else if (x == 'T')
        {
            x = TSP_cmd(head);
        }
    }
    deleteGraph_cmd(&head);
    return 0;
}
