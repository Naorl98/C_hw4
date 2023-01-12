#include <stdio.h>
#include "graph.h"
#include <stdlib.h>
#include <stddef.h>
#define GET if(getCommand(command) == EOF) return EOF;

pnode findNode(pnode *head,int num){
   pnode *t = head;
       while(*t){
      if((**t).node_num == num ){
         return *t;
      }
      t = &((*t)->next);
    }
    return 0;
}

int getCommand(char * com){
   int i = 0;
   int command ;
   int save = 0;
   command = fgetc(stdin) ;
  while(command != ' ' && command != '\n' && command != EOF){

      com [i] = (char) command;
      i++;
      com = realloc(com,(i+1)*sizeof(char));
      command = fgetc(stdin) ;
   }

   if(command == EOF){
      free(com);
      return EOF;
   }
   return 0;
   
}
int build_graph_cmd(pnode *head){
char * command = malloc(sizeof(char));
pnode *t = &(*head);
GET
int len = atoi(command);
for (int i = 0; i < len; i++)
{  
   
   (*t) = (pnode ) malloc(sizeof(node)); 
   (**t).node_num = i;
   (*t)->edges = (pedge ) malloc(sizeof(edge)); ;
    t = &((*t)->next);
}
 GET
 if(command [0]!= 'n'){
    exit(0);
 }
GET
 pnode point= findNode(head, atoi(command));
 t = &point;
 pedge *edgeH =&((*t)->edges);
 while (1)
 {     
    GET
   if(command[0] >=65 && command[0]<=90) {
      int letter = command[0];
      free(command);
      return letter;
   }
    if(command[0] == 'n'){ 
      GET   
    point= findNode(head, atoi(command));
    t = &point;
    edgeH =&((*t)->edges);
    }
   else{
      if(!*edgeH) (*edgeH) = (pedge ) malloc(sizeof(edge)); 
     pnode to = findNode(head,atoi(command));
    (*edgeH)->endpoint = &(*to);
    GET
    (*edgeH)->weight = atoi(command);
    edgeH = &((*edgeH)->next);
 }
 
 }
 
}
int insert_node_cmd(pnode *head){
   char * command = malloc(sizeof(char));
   GET
   int num = atoi(command);
   pnode *t = &(*head);
    while(*t){
      if((**t).node_num == num ){
         pedge p =  &(*(*t)->edges);
         free(p);
          edge e;
          pedge pe =(pedge ) malloc(sizeof(edge)); 
          pe = &e;
         (*t)->edges = &(*pe);
         break;
      }
      t = &((*t)->next);
    }
   if(!*t){

   (*t) = (pnode ) malloc(sizeof(node)); 
   (**t).node_num = num;
    (*t)->edges = (pedge ) malloc(sizeof(edge)); 

   }
   pedge *edgeH =&((*t)->edges);
   while(1){
   GET
   if(command[0] >=65 && command[0]<=90) {
      int letter = command[0];
      free(command);
      return letter;
   }
     if(!*edgeH) 
       (*edgeH) = (pedge ) malloc(sizeof(edge)); 
      pnode to = findNode(head,atoi(command));
    (*edgeH)->endpoint = &(*to);
    GET
    (*edgeH)->weight = atoi(command);
    edgeH = &((*edgeH)->next);
   }
}


int delete_node_cmd(pnode *head){}
void printGraph_cmd(pnode head) //for self debug
{}
int deleteGraph_cmd(pnode* head){}
int shortsPath_cmd(pnode head){}
int TSP_cmd(pnode head){}
int main(){
   printf("hii\n");

node a;
pnode head = &a;

int x =fgetc(stdin);
while(x != EOF){
if(x == 'A'){
   x =fgetc(stdin);
 x = build_graph_cmd(&head);
}
else if(x == 'B'){
  x=  insert_node_cmd(&head);
}

}

pnode no = head;
while(no){
   printf(" nude num : %d\n",no->node_num);
   pedge *ed = &(no->edges);
    printf("edges: \n");
    if((*ed)->endpoint){
   while(*ed){
   printf(" to node: %d, weight: %d\n",(*ed)->endpoint->node_num, (*ed)->weight );
   ed = &((*ed)->next);
   }
   
   }
   else printf("No edges\n");
   no = no->next;
}

exit(0);


}