#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>

typedef struct Node {
	int data;
	Node *head;
}Node ;

/*void CREATE_LL(Node *node1){
	node1=(Node *)malloc(sizeof(Node));
	node1->data=NULL;
	node1->head=NULL;
}
*/

void InsertAtBegin(Node **node1 , int head1){
	Node *node=(Node *)malloc(sizeof(Node));
	node->data=head1;
	node->head=(*node1);
	(*node1)=node;
}

void INSERTATEND(Node **node1,int da){
		Node *node=(Node *)malloc(sizeof(Node));
	node->data=da;
    Node *temp=(*node1);
    while(temp->head!=NULL){
    	temp=temp->head;
	}
	temp->head=(node);
	node->head=NULL;
	(*node1)=(temp);
}

void INSERTatMID(Node **node1,int da,int place){
		Node *node=(Node *)malloc(sizeof(Node));
	node->data=da;
	Node *temp=(*node1);
	int i=0;
	while(i<place){
		temp=temp->head;
		i++;
	}
	node->head=temp->head;
	temp->head=node;
	(*node1)=temp;
}

Node** REMOVE_At_Begin(Node **Node1){
	int N;
    Node *temp=*Node1;
    *Node1=(*Node1)->head;
    N=temp->data;
    printf("The Removed element is %d:\n",N);
    return &temp; 
}

Node** REMOVE_AT_Mid(Node **Node1,int place){
	int N;
	Node *temp=*Node1;
	Node *prev=NULL;
	Node *next=NULL;
	int i=0;
	while(i<place){
		prev=temp;
		temp=temp->head;
		next=temp;
		i++;
	}
	prev->head=temp->head;  
	*Node1=prev;
	N=next->data;
	return &next;
}

Node** REMOVE_at_LAST(Node **Node1){
	int N;
	Node *temp=*Node1;
    Node *prev=NULL;
	while(temp->head!=NULL){
		prev=temp;
		temp=temp->head;
	}	
	prev->head=NULL;
	N=temp->data;
	printf("The removed element is %d:\n",N);
	*Node1=prev;
	return &temp;
}

void Print_LL(Node **head) {
    Node *temp = *head;
    int i=0;
    while (temp != NULL&& i<5) {
        printf("%d -> ", temp->data);
        temp = temp->head;
        i++;
    }
    printf("NULL\n");
}
void REVERSE_LL(Node **node1){
	struct 	Node *prev=NULL;
		struct 	Node *next=NULL;
			struct 	Node *current=*node1;
				int j=0;
				
			while(current!=NULL){
				next=current->head;
				current->head=prev;
				prev=current;
				current=next;
				//printf("Issue inside the while");
				j++;
			}
			printf("%d",j);
			printf("Here is the isse outise ");
		 *node1 = prev; 
}

int main()
{
	Node *node1=(Node *)malloc(sizeof(Node));
	InsertAtBegin(&node1,10);
	InsertAtBegin(&node1,20);
	InsertAtBegin(&node1,30);
	InsertAtBegin(&node1,50);
	InsertAtBegin(&node1,60);
//	REVERSE_LL(&node1);
	Print_LL(&node1);

}