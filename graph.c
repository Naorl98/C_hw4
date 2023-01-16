#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <resolv.h>
#include <malloc.h>
#define GET if (getCommand(command) == EOF) return EOF;
int charindex;
int length ;
// Queue Start

void add(pqueue *headQ, pqueue enter)
{

    if ((*headQ) == NULL)
        (*headQ) = enter;
    else
    {
        pqueue first = (*headQ);
        if ((**headQ).priority > (*enter).priority)
        {
            enter->next = (*headQ);
            (*headQ) = enter;
        }

        else
        {
            while (first->next != NULL && first->next->priority < enter->priority)
            {
                first = first->next;
            }
            enter->next = first->next;
            first->next = enter;
        }
    }
}
pqueue pop(pqueue *headQ)
{
    pqueue out = *headQ;
    (*headQ) = (*headQ)->next;
    return out;
}
// Queue End

pnode findNode(pnode *head, int num)
{
    pnode *t = head;
    while (*t)
    {
        if ((**t).node_num == num)
        {
            return *t;
        }
        t = &((*t)->next);
    }
    return 0;
}

void dijkastra(pnode head, int *dist)
{
    pqueue pfirst = malloc(sizeof(queue));
    pfirst->point = head;
    pfirst->next = NULL;
    pfirst->priority = 0;
    pqueue *QueueH = &pfirst;
    pedge newE = NULL;
    dist[head->node_num] = pfirst->priority;
    while ((*QueueH) != NULL)
    {
        pqueue out = pop(QueueH);
        pnode Qnode = out->point;
        newE = &(*(out->point->edges));

        while (newE != NULL && newE->endpoint != NULL)
        {

            if ((dist[Qnode->node_num] + newE->weight) < dist[newE->endpoint->node_num])
            {
                dist[newE->endpoint->node_num] = dist[Qnode->node_num] + newE->weight;
                pqueue pnew = malloc(sizeof(queue));
                pnew->point = newE->endpoint;
                pnew->next = NULL;
                pnew->priority = dist[newE->endpoint->node_num];
                add(QueueH, pnew);
            }
            newE = &(*(newE->next));
        }
        free(out);
    }
}

int getCommand(char *com)
{
    int command;
    memset(com, 0, (charindex + 1) * sizeof(int));
    charindex = 0;
    command = fgetc(stdin);
    while (command != ' ' && command != '\n' && command != EOF)
    {
        com[charindex] = (char)command;
        charindex++;
        com = realloc(com, (charindex + 1) * sizeof(char));
        command = fgetc(stdin);
    }

    if (command == EOF)
    {
        free(com);
        return EOF;
    }
    return 0;
}
int build_graph_cmd(pnode *head)
{    
    
    if ((*head) != NULL)
    {
        pnode *t1 = &(*head);
        pnode newhead = NULL;
        deleteGraph_cmd(t1);
        (*head) = newhead;
    }
    pnode *t = &(*head);
    char *command = malloc(sizeof(char));
    GET 
    int len = atoi(command);

    length = len;
    for (int i = 0; i < len; i++)
    {
        (*t) = (pnode)malloc(sizeof(node));
        (**t).node_num = i;
        t = &((*t)->next);
    }
    GET

        if (command[0] != 'n')
    {
        printf("Wrong char - need to be n\n");
        exit(0);
    }
    GET

    pnode point = findNode(head, atoi(command));
    t = &point;
    pedge *edgeH = &((*t)->edges);
    while (1)
    {
        GET if (command[0] >= 65 && command[0] <= 90)
        {
            int letter = command[0];
            free(command);
            return letter;
        }
        if (command[0] == 'n')
        {
            GET
                point = findNode(head, atoi(command));
            t = &point;
            edgeH = &((*t)->edges);
        }
        else
        {
            if (!*edgeH)
            {
                (*edgeH) = (pedge)malloc(sizeof(pedge));
                (*edgeH)->next = NULL;
            }
            pnode to = findNode(head, atoi(command));
            (*edgeH)->endpoint = &(*to);
            GET(*edgeH)->weight = atoi(command);
            edgeH = &((*edgeH)->next);
        }
    }
}
int insert_node_cmd(pnode *head)
{
    char *command = malloc(sizeof(char));
    GET int num = atoi(command);
    pnode *t = &(*head);
    while (*t)
    {
        if ((**t).node_num == num)
        {
            pedge *p = &((*t)->edges);
            while (*p)
            {
                pedge dP = (*p)->next;
                free(*p);
                p = &dP;
            }
            ((*t)->edges) = NULL;
            break;
        }
        t = &((*t)->next);
    }
    if (!*t)
    {
        length = num + 1;
        (*t) = malloc(sizeof(node));
        (**t).node_num = num;
    }
    pedge *edgeH = &((*t)->edges);
    while (1)
    {
        GET if (command[0] >= 65 && command[0] <= 90)
        {
            int letter = command[0];
            free(command);
            return letter;
        }
        if (!*edgeH)
        {
            (*edgeH) = (pedge)malloc(sizeof(pedge));
            (*edgeH)->next = NULL;
        }
        num = atoi(command);
        pnode to = findNode(head, num);
        (*edgeH)->endpoint = to;
        GET
            num = atoi(command);
        (*edgeH)->weight = num;
        edgeH = &((*edgeH)->next);
    }
}

int delete_node_cmd(pnode *head, int all)
{
    char *command;
    int num = -1;
    if (all == -1)
    {
        command = malloc(sizeof(char));
        GET
            num = atoi(command);
    }
    else
        num = all;
    pnode *t = &(*head);
    pnode *prev = &(*head);
    while (*t)
    {
        if ((**t).node_num == num)
        {
            break;
        }
        prev = &(*t);
        t = &((*t)->next);
    }
    if (*t)
    {
        if (num == length - 1)
            length--;
        pedge *delE = &((*t)->edges);
        pedge *save = &((*t)->edges->next);

        while (*delE)
        {
            free(*delE);
            delE = &(*save);
            save = &((*save)->next);
        }
        pnode delN = *t;
        pnode new = &(*((*t)->next));
        if ((*prev)->node_num == num)
            (*prev) = new;
        else
            (*prev)->next = new;
        t = &(*head);
        while (*t)
        {
            delE = &((*t)->edges);
            save = &((*t)->edges->next);
            while (*delE)
            {
                if (((*delE)->endpoint) && ((*delE)->endpoint->node_num) == num)
                {
                    pedge new2 = &(*((*delE)->next));
                    (*delE) = new2;
                }
                else
                {
                    delE = &(*save);
                    save = &((*save)->next);
                }
            }
            t = &((*t)->next);
        }
        free(delN);
    }
    else
    {
        printf("Not find Node number : %d\n", num);
        return EOF;
    }
    if (all == -1)
    {
        GET int letter = command[0];
        free(command);
        return letter;
    }
    return -2;
}

void deleteGraph_cmd(pnode *head)
{
    int x = -2;
    if (*head && x == -2)
    {
        deleteGraph_cmd((&(*head)->next));
        x = delete_node_cmd(head, (*head)->node_num);
    }
}

int shortsPath_cmd(pnode head)
{

    char *command = malloc(sizeof(char));
    int dist[length];
    GET int source = atoi(command);
    GET int dest = atoi(command);
    pnode *start = &head;
    while ((*start)->node_num != source)
    {
        start = &((*start)->next);
    }
    for (int i = 0; i < length; i++)
    {
        dist[i] = __INT_MAX__;
    }
    dijkastra((*start), dist);

    printf("Dijsktra shortest path: %d \n", dist[dest]);

    GET int letter = command[0];
    free(command);
    return letter;
}
void swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void prmot(int *arr, int start, int end, int sumbit[720][6], int *index)
{
    if (start == end)
    {
        int i, j;
        j = (*index);
        for (i = 0; i < end + 1; i++)
        {
            sumbit[j][i] = arr[i];
        }

        j += 1;
        (*index) = j;
    }
    int i;
    for (i = start; i <= end; i++)
    {
        swap((arr + i), (arr + start));
        prmot(arr, start + 1, end, sumbit, index);
        swap((arr + i), (arr + start));
    }
}
int TSP_cmd(pnode head)
{
    char *command = malloc(sizeof(char));
    GET int len = atoi(command);
    int dist[length];
    int numbers[len];
    int num = 0;
    int fact = 1;
    int min = 0;
    int minall = __INT_MAX__;
    pnode *start = &head;

    for (int i = 0; i < length; i++)
        dist[i] = __INT_MAX__;
    for (int k = 0; k < len; k++)
    {
        GET
            num = atoi(command);
        numbers[k] = num;

        fact *= k + 1;
    }
    if (len == 1)
        printf("TSP shortest path: 0 \n");
    int permo[720][6];
    int ins = 0;
    int *index = &ins;
    prmot(numbers, 0, len - 1, permo, index);
    for (int row = 0; row < fact; row++)
    {
        for (int col = 0; col < len - 1; col++)
        {
            pnode first = findNode(start, permo[row][col]);
            dijkastra(first, dist);
            if (dist[permo[row][col + 1]] == INT_MAX)
            {
                min = 0;
                for (int i = 0; i < length; i++)
                    dist[i] = __INT_MAX__;
                break;
            }
            min += dist[permo[row][col + 1]];
            for (int i = 0; i < length; i++)
                dist[i] = __INT_MAX__;
        }
        if (min != 0)
        {
            minall = MIN(minall, min);
        }
        min = 0;
    }

    if (minall == INT_MAX)
        printf("TSP shortest path: -1 \n");
    else
        printf("TSP shortest path: %d \n", minall);
    GET int letter = command[0];
    free(command);
    return letter;
}
