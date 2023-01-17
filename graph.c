#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <resolv.h>
#include <malloc.h>
int length;

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
    pnode t = *head;
    while (t)
    {
        if (t->node_num == num)
        {
            return t;
        }
        t = t->next;
    }
    return 0;
}

void dijkastra(pnode head, int *dist)
{
    pqueue pfirst = (pqueue)malloc(sizeof(queue));
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
                pqueue pnew =(pqueue) malloc(sizeof(queue));
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

void build_graph_cmd(pnode *head, int setlen)
{
    length = setlen;
    int getNum;
    scanf("%d",&getNum);
    pnode newPoint = findNode(head,getNum);
    pnode new = newPoint;
    pedge prevEdge = NULL;
    while (scanf("%d",&getNum) == 1)
    {
        pedge newEdge = NULL;
        newEdge = (pedge)malloc(sizeof(edge));
        pnode to = findNode(head, getNum);
        newEdge->endpoint = to;
        scanf("%d",&getNum);
        newEdge->weight = getNum;
        newEdge->next = prevEdge;
        new->edges = newEdge;
        prevEdge = newEdge;
    }
}
void insert_node_cmd(pnode *head)
{
    int getNum;
    scanf("%d",&getNum);
    pnode new = findNode(head,getNum);
    if(new){
        pedge theE = new->edges;
        while(theE){
            pedge prev = theE;
            theE = theE->next; 
            free(prev);
        }
    }
    else{
        new = (pnode)malloc(sizeof(node));
        new->node_num =getNum;
        new->next = NULL;
        new->edges = NULL;
        pnode last = findNode(head,length-1);
        length = getNum + 1;
        last->next = new;
    }
    pedge prevEdge = NULL;
    while (scanf("%d",&getNum) == 1)
    {
        pedge newEdge = NULL;

        newEdge = (pedge)malloc(sizeof(pedge));
        pnode to = findNode(head, getNum);
        newEdge->endpoint = to;
        scanf("%d",&getNum);
        newEdge->weight = getNum;
        newEdge->next = prevEdge;
        new->edges = newEdge;
        prevEdge = newEdge;
    }
}

void delete_node_cmd(pnode *head)
{
    if((*head == NULL)) return;
    int num;
    scanf("%d",&num);
    pnode delED = *head;
 
    while(delED)
    {
        
        if(delED->node_num != num && delED->edges){
            pedge delEdge = delED->edges;
            if(delEdge->endpoint->node_num == num){
                pedge deleted = delEdge;
                delED->edges = delEdge->next;
                free(deleted);
            }
            else{
            while(delEdge->next!= NULL){
                if(delEdge->next->endpoint->node_num == num){
                    pedge deleted = delEdge->next;
                    delEdge->next = deleted->next;
                    free(deleted);
                    break;
                }
                delEdge = delEdge->next;
            }}
        }
        delED = delED->next;
    }

    if (num == length - 1)
        length--;
    pnode t = *head;
    pnode deleND = NULL;
    if(t->node_num == num){
        *head = t->next;
        deleND = t;
    }
    else{

        while(t->next){
            if(t->next->node_num== num){
                deleND = t->next;
                t->next = deleND->next;
                break;
            }
        t = t->next;
        }
    }
    pedge delE = deleND->edges;
    while (delE)
    {
        pedge save = delE;
        delE = delE->next;
        free(save);
    }

}

void deleteGraph_cmd(pnode *head)
{
    if(head!=NULL||*head!=NULL) {
    pnode delHead; 
    delHead = *head;
    while (delHead!=NULL)
    {   
        pedge delHeadEd = delHead->edges;
        while(delHeadEd){
            pedge delEd = delHeadEd;
            delHeadEd = delHeadEd->next;
            free(delEd);

        }
         pnode del = delHead;
         delHead = delHead->next;
         free(del);
    }
    *head=NULL;

    }
}

void shortsPath_cmd(pnode head)
{   

    int source;
    scanf("%d",&source);
    int dest;
    scanf("%d",&dest);

    int dist[length];
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
void TSP_cmd(pnode head)
{

    int len;
    scanf("%d",&len);
    int dist[length];
    int numbers[len];
    int fact = 1;
    int min = 0;
    int minall = __INT_MAX__;
    pnode *start = &head;

    for (int i = 0; i < length; i++)
        dist[i] = __INT_MAX__;
    for (int k = 0; k < len; k++)
    {
        scanf("%d",&numbers[k]);
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
}
