#include<stdio.h>
#include<stdlib.h>

typedef struct S{
	int data;
	struct S *next;
	
}node;
/*The foolowing function shows common operation in the union and intersection functions.
It takes head of linked list and auxiliary variable  as parameters
and returns auxilary variable to create intersection or union sequence.*/
node *common(node *tmp,node *root){
	tmp->next=(node *)malloc(sizeof(node));
				if(tmp->next==NULL){
					printf("place was not held");
					exit(0);
				}
				
				tmp=tmp->next;
				tmp->data=root->data;
				tmp->next=NULL;
				return tmp;
}

/*In order to reach the next elements, the variable showing the first node takes as parameter 
and prints the elements of the linked list to the screen.*/
void print(node *root){
	while(root!=NULL){
		printf("%3d->",root->data);
		root=root->next;
	}
	printf("\n");
}
/*creates the array by taking the array and the size of the array as parameters.*/
void createArray(int dizi[],int boyut){
	int i;
	for(i=0;i<boyut;i++){
		printf("%d.element:",i+1);
		scanf("%d",&dizi[i]);
	}	
	printf("\n");
}
/*The following function takes the array and size parameters and keeps each element of the array in the linked list structure. */
node *createLinkedList(int dizi[],int boyut){
		node *head;//it will provide access to the first element of the linked list that is created.
		node *temp;//temp is the variable that will be used as a helper here.
		head=(node *)malloc(sizeof(node));
		if(head==NULL){
				printf("place was not held");
				exit(0);
			}
		head->data=dizi[0];
		temp=head;
		int i;
		for(i=0;i<boyut-1;i++){
			temp->next=(node *)malloc(sizeof(node));
			if(temp->next==NULL){
				printf("place was not held");
				exit(0);
			}	
			temp=temp->next;
			temp->data=dizi[i+1];
			temp->next=NULL;
					
		}
		printf("\n");
		return head;
}
/*Following function takes nodes that represent the first elements of the linked list 
created from the arrrays A and B  as parameter to obtain the intersection list as a linked list.*/
void _intersection(node *rootA,node *rootB){
	
	node *diziC;//It will show the intersection linked list created from A and B arrays.
	node *intersecttmp;//indicates the utility variable at the intersection.
	diziC=(node *)malloc(sizeof(node));
	diziC->next=NULL;//If there is no intersection of the two indexes, the print function will be recovered from the infinite loop 
	intersecttmp=diziC;//the elements of the intersection  will be created using the auxiliary variable.
	while(rootA!=NULL && rootB!=NULL){
		
		if(rootA->data <= rootB->data){
			if(rootA->data==rootB->data){
				intersecttmp=common(intersecttmp,rootA);
				rootA=rootA->next;
				rootB=rootB->next;		
			}
			else
			rootA=rootA->next;	
		}
		else
		rootB=rootB->next;			
	}
	printf("Intersect Array:");
		print(diziC->next);
}

/*Following function takes nodes that represent the first elements of the linked list 
created from the A and B arrays as parameter to obtain the union list as a linked list.*/
void _union(node *rootA,node *rootB){
	node *diziD;//It shows the union linked lists created from A and B arrays.
	node *uniontmp;//indicates the utility variable at the union.
	diziD=(node *)malloc(sizeof(node));
	uniontmp=diziD;//the elements of the union  will be created using the auxiliary variable.
	
	while(rootA!=NULL && rootB!=NULL){
		
		if(rootA->data <= rootB->data){
			if(rootA->data==rootB->data){
				uniontmp=common(uniontmp,rootA);
				rootA=rootA->next;
				rootB=rootB->next;		
			}
			else{
			uniontmp=common(uniontmp,rootA);
			rootA=rootA->next;
		}		
	}
		else{
		uniontmp=common(uniontmp,rootB);
		rootB=rootB->next;	
		}
	} 
	/*in the above loop, the loop will end when it sees a null in the linked lists A or B.
	Therefore,Adds the remaining members of the linked list that do not have null values to the union list.*/
		if(rootA==NULL){
			while(rootB!=NULL){
		uniontmp=common(uniontmp,rootB);
		rootB=rootB->next;	
			}
		}
		else{
		while(rootA!=NULL){
		uniontmp=common(uniontmp,rootA);
		rootA=rootA->next;
		}
	}
	printf("Union Array:");
		print(diziD->next);
}
int main(){
	int boyut;//Dimension of Array A and B
	int diziA[boyut];// Array A
	int diziB[boyut];//Array B
	node *head1;//It is used to access the first element (node) of the linked list that will be created from the A array.
	node *head2;//It is used to access the first element (node) of the linked list that will be created from the B array.
	
	printf("Enter the dimension of Array A:");
	scanf("%d",&boyut);
	printf("Array A\n");
	createArray(diziA,boyut);
	head1=createLinkedList(diziA,boyut);
		
	printf("Enter the dimension of Array B:");
	scanf("%d",&boyut);
	printf("Array B\n");
	createArray(diziB,boyut);
	head2=createLinkedList(diziB,boyut);
	
	printf("Array A:");
	print(head1);
	printf("Array B:");
	print(head2);
	
	_intersection(head1,head2);
	_union(head1,head2);
	return 0;
}
