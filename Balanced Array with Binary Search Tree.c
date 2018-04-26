#include<stdio.h>
#include<stdlib.h>
#include <math.h>
typedef struct BST{
	int data;
	struct BST *left,*right;
}node;
node *createNode(){
	node *tmp;
	tmp=(node*)malloc(sizeof(node));
	if(tmp==NULL){
		printf("Yer ayrýlamadi");
		exit(0);
	}	
		tmp->left=NULL;
		tmp->right=NULL;
	return tmp;
}
void insert(node *root,node *newNode){
	if(newNode->data<root->data){
		if(root->left==NULL) 
		root->left=newNode;
		else insert(root->left,newNode);
	}
	else{
		if(root->right==NULL)
		 root->right=newNode;
		else insert(root->right,newNode);
		}	
}
node *createTree(int dizi[],int size){
	node *newNode;node *root=NULL;
	int i;
	for(i=0;i<size;i++){
		newNode=createNode();
		newNode->data=dizi[i];
		if(root==NULL)
		root=newNode;
		else insert(root,newNode);
	}
	return root;
}
int j=0;
void splitArray(int dizi[],int alt,int ust,int temp[]){
int ortanca;
	if(alt<ust){
		ortanca=alt+(ust-alt)/2;
		temp[j]=dizi[ortanca];
		j++;
		splitArray(dizi,alt,ortanca,temp);
		splitArray(dizi,ortanca+1,ust,temp);
	}	
}
void treeConvertToArray(node *root,int helpArray[],int i){
	if(root!=NULL){
		helpArray[i]=root->data;
		treeConvertToArray(root->left,helpArray,2*i+1);
		treeConvertToArray(root->right,helpArray,2*i+2);	
	}
}
int arrangeSizeOfArray(int dizi[],int size){
	int sayac=0;
	while(size>0) {
		size=size/2;
		sayac++;
	}
	int boyut=pow(2,sayac)-1;
	int i;
	dizi[boyut];
	for(i=0;i<boyut;i++)dizi[i]=0;
	return boyut;
}
int main(){
	int size=0;
	int temp;
	char ch;
	node *root;
	FILE *fp;
	int boyut;
	if((fp=fopen("input1.txt","r"))==NULL){
		printf("Dosya acma hatasi");
	}
	fseek(fp,0,SEEK_SET);
	while(!feof(fp)){
		fscanf(fp,"%d",&temp);
		fscanf(fp,"%c",&ch);
		size++;
		}
	int	array[size];
	fseek(fp,0,SEEK_SET);
	int i;
	for(i=0;i<size;i++){
		fscanf(fp,"%d",&temp);
		fscanf(fp,"%c",&ch);
		array[i]=temp;
		printf("%3d",array[i]);
	}	
	printf("\n");
	int help[size];
	
	splitArray(array,0,size,help);
	root=createTree(help,size);
	boyut=arrangeSizeOfArray(help,size);
	treeConvertToArray(root,help,0);
	
	for(i=0;i<boyut;i++)
	printf("%3d",help[i]);
}		
