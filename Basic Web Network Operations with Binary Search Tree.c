#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct BST{
	int kimlikNo;
	char ad[20] ;
	char soyad[20] ;
	int *arkadasKimlikNo;
	struct BST *right,*left;
}node;

node *createNode(){
	node *tmp;
	tmp=(node*)malloc(sizeof(node));
	if(tmp==NULL){
		printf("Yetersiz Bellek Alani");
		exit(0);
	}
	tmp->arkadasKimlikNo=(int *)malloc(20*sizeof(int));
	if(tmp->arkadasKimlikNo==NULL){
		printf("Yetersiz Bellek Alani");
		exit(0);
	}	
		tmp->left=NULL;
		tmp->right=NULL;
	return tmp;
}
void insertNewUser(node *root,node *newRoot){
	if(newRoot->kimlikNo<root->kimlikNo){
		if(root->left==NULL) 
		root->left=newRoot;
		else insertNewUser(root->left,newRoot);
	}
	else{
		if(root->right==NULL)
		 root->right=newRoot;
		else insertNewUser(root->right,newRoot);
		}
}
int size(node *root,int nums){
	if(root==NULL)return 0;
	else{
	if(root->left!=NULL){
	nums=size(root->left,nums);
	}
	if(root->right!=NULL){
	nums=size(root->right,nums);
	}
}
	return nums+1;
}

void contains(node *root,int value){
	if(root==NULL) {
	printf("User is not Found\n");
	return ;
}
	else{
	
	if(root->kimlikNo==value){
		printf("%s %s\n",root->ad,root->soyad);
		return ;
	}
	else{
		if(root->kimlikNo > value)
		contains(root->left,value);
		
		else contains(root->right,value);
		}
	}
}
node *searchUser(node *root,int value){
	if(root==NULL)
	 return NULL;
	 
	else{
	
	if(root->kimlikNo==value){
		return root;
	}
	else{
		if(root->kimlikNo > value)
		searchUser(root->left,value);
		
		else searchUser(root->right,value);
		}
	}
}
void Friends(node *root,int value){
	node *tmp;
	tmp=searchUser(root,value);
	if(tmp==NULL){
		printf("User is not Found\n");
	}
	else{
	int i;
	for(i=0;tmp->arkadasKimlikNo[i]!=NULL;i++){
	contains(root,tmp->arkadasKimlikNo[i]);	
	}
}
}
void helperPrintNext(node *root,int value){
	if(root!=NULL){
		helperPrintNext(root->left,value);
		if(root->kimlikNo!=value)
		printf("%d %s %s\n",root->kimlikNo,root->ad,root->soyad);
		helperPrintNext(root->right,value);
	}	
}
void printNext(node *root,int value){
	node *tmp;
	tmp=searchUser(root,value);
	if(tmp==NULL)
	printf("User is not found!");
	else{
	
		if(tmp->left==NULL && tmp->right==NULL)
		printf("There is not subtree!");
		else helperPrintNext(tmp,value);		
	}
}
void helperPrintGreater(node *root,int value){
	if(root!=NULL){
		helperPrintGreater(root->left,value);
		if(root->kimlikNo > value)
		printf("%d %s %s\n",root->kimlikNo,root->ad,root->soyad);
		helperPrintGreater(root->right,value);
	}	
}

void printInOrder(node *root){
	if(root!=NULL){
		printInOrder(root->left);
		printf("%d %s %s\n",root->kimlikNo,root->ad,root->soyad);
		printInOrder(root->right);
	}	
}


void printGreater(node *root,int value){
	node *tmp;
	tmp=searchUser(root,value);
	if(tmp==NULL)
	printf("User is not found");
	else
		 helperPrintGreater(root,value);			
}
int k=0;
void splitArray(node *dizi[],int alt,int ust,node *temp[]){
int ortanca;
	if(alt<ust){
		ortanca=alt+(ust-alt)/2;
		temp[k]=dizi[ortanca];
		k++;
		splitArray(dizi,alt,ortanca,temp);
		splitArray(dizi,ortanca+1,ust,temp);
	}	
}
node *createTree(node *dizi[],int size){
	node *newNode;
	node *root=NULL;
	int i;
	for(i=0;i<size;i++){
		newNode=createNode();
		newNode=dizi[i];
		if(root==NULL)
		root=newNode;
		else insertNewUser(root,newNode);
	}
	return root;
}
node *parentSearch(node *root,node *child){
	node *parent=root;
	if(child->kimlikNo<root->kimlikNo ){
	parent=root;
	root=root->left;
	if(child->kimlikNo!=root->kimlikNo )
	parent=parentSearch(root,child);
	}
	else if(child->kimlikNo>root->kimlikNo  ){
	parent=root;
	root=root->right;
	if(child->kimlikNo!=root->kimlikNo)
	parent=parentSearch(root,child);
	}
	return parent;
}
node *helperDelete(node *root,node *newRoot,int value){
	if(root->kimlikNo==value){
	return newRoot;
}
	else{
	if(newRoot->kimlikNo<root->kimlikNo){
		if(root->left->kimlikNo==value) 
		root->left=newRoot;
		else helperDelete(root->left,newRoot,value);
	}
	else{
		if(root->right->kimlikNo==value) 
		 root->right=newRoot;
		else helperDelete(root->right,newRoot,value);
		}
		
	}
	return root;
}
node *deleteUser(node *root,int value){
	node *parent,*child;
	node *tmp,*tmp2;
	child=searchUser(root,value);
	if(child==NULL)printf("User is not found");
	else{
		if(child->left==NULL && child->right==NULL){//if the node is leaf.
		parent=parentSearch(root,child);
		if(child->kimlikNo<parent->kimlikNo)
		parent->left=NULL;
		else parent->right=NULL;
		}
		else{
		
 		if(child->right==NULL){//if the node has one child.
			tmp=child->left;
			root=helperDelete(root,tmp,value);
		}
		if(child->left==NULL){//Node has one child
			tmp=child->right;
			root=helperDelete(root,tmp,value);
		}
		if(child->left!=NULL && child->right!=NULL){//Node has two child
			tmp=child->left;
			tmp2=child->right;
			root=helperDelete(root,tmp,value);
			insertNewUser(root,tmp2);
		}
	}
}
	return root;
}
int main(){
	int numNodes=0;
	int i=0,count=0;
	node *root;
	char *str,*str2;//These variable is used file operations
	char tmp[50];//These variable is used file operations
	FILE *fp;//These variable is used file operations
	if((fp=fopen("input2.txt","r"))==NULL){
		printf("Dosya acma hatasi");
	}
	fseek(fp,0,SEEK_SET);
	while(!feof(fp)){
	count++;
	str2=fgets(tmp,50,fp);
	}
//	node *newNode[count];
	node *newNode;
	fseek(fp,0,SEEK_SET);
	str=fgets(tmp,50,fp);
	while(str!=NULL){
		
		newNode=createNode();
		str2=strtok(tmp,",");
		sscanf(str2,"%d",&newNode->kimlikNo);
		str2=strtok(NULL," ");
		sscanf(str2,"%s",&newNode->ad);
		printf("Ad:%s\n",&newNode->ad);
		str2=strtok(NULL,",");
		sscanf(str2,"%s",&newNode->soyad);
		int j=0;
		while(str2!=NULL)
		{
				str2=strtok(NULL,"-");
				if(str2!='\0'){
				sscanf(str2,"%d",&newNode->arkadasKimlikNo[j]);
				printf("kimlik:%d\n",newNode->arkadasKimlikNo[j]);
			}
				j++;
		}
		i++;
		str=fgets(tmp,50,fp);
		if(root==NULL)
		root=newNode;
		else insertNewUser(root,newNode);
	}
/*	node *help[count];
	splitArray(newNode,0,i,help);
	root=createTree(help,count);*/
	
	
	
	int kimlikNo;
	printf("\nSilinecek kimlik No giriniz:\n");
	scanf("%d",&kimlikNo);
	root=deleteUser(root,kimlikNo);
	printf("\n------------------------------------------\n");
	printf("\nArama yapilacak kimlik No giriniz:\n");
	scanf("%d",&kimlikNo);
	contains(root,kimlikNo);
	printf("\n------------------------------------------\n");
	printf("\nAlt agacinda yer alan kisileri bulmak icin kimlik No giriniz:\n");
	scanf("%d",&kimlikNo);
	printNext(root,kimlikNo);
	printf("\nSize:%d",size(root,numNodes));
	printf("\nArkadaslari aranacak kisinin kimlik No giriniz:\n");
	scanf("%d",&kimlikNo);
	Friends(root,kimlikNo);
	printf("\n------------------------------------------\n");

	printf("\n------------------------------------------\n");
	printf("\nVereceginiz kimlik No'dan buyuk olan kiþiler bulunacaktir\n");
	scanf("%d",&kimlikNo);
	printGreater(root,kimlikNo);
	printf("\n------------------------------------------");
}
