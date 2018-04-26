#include<stdio.h>
#include<stdlib.h>

int currentclass=0;
int labelcount=0;
int vertex;
void initializeLabel(int label[]){
	int i;
	for(i=0;i<vertex;i++) 
		label[i]=0;
}
int flag(int label[],int value){
	int i;
	for(i=0;i<vertex;i++)
		if(label[i]==value)return 0;
	return 1;
}
void Clustering(int uu,int vv,int label[],int clusterNums){
	int zeroCount=0;
	int k;
		for(k=0;k<vertex;k++) 
			if(label[k]==0)zeroCount++;
		if(clusterNums-currentclass>=zeroCount){
			for(k=0;k<vertex;k++){
				if(label[k]==0){
					labelcount++;
					currentclass++;
					label[k]=labelcount;
				}
			}				
		}
		else{
		
		if(label[uu]+label[vv]==0){
			labelcount++;
			currentclass++;
			label[uu]=labelcount;
			label[vv]=labelcount;
		}
		else{
			if(label[uu]!=label[vv]){
				if(label[uu]==0){
					label[uu]=label[vv];
				}
				else{
					if(label[vv]==0){
						label[vv]=label[uu];
				}
				else{
					if(currentclass>clusterNums){
						int value=label[uu];
						currentclass--;
						for(k=0;k<vertex;k++)
							if(label[k]==value)
							label[k]=label[vv];
						}
					}
				}
			}	
		}
	}
}
void minSpan(int graph[][vertex],int label[],int ClusterNums){
	int i,j;
	int stop=0;
	int value=1;
	
	while(currentclass!=ClusterNums || stop==0){
		for(i=0;i<vertex;i++){
			for(j=i+1;j<vertex;j++){
				if(graph[i][j]==value)
				Clustering(i,j,label,ClusterNums);
			}
		}
		value++;
		stop=flag(label,0);
	}
}
void arrangeAndPrint(int label[]){
	int Clusterlabel=1;
	int i,k,tmp;
	int labeltmp=1;
	for(k=0;k<labelcount;k++){
	tmp=flag(label,labeltmp);
	if(tmp==1)
	labeltmp++;
	else{
		for(i=0;i<vertex;i++){
			if(label[i]==labeltmp)
			label[i]=Clusterlabel;
		}
		labeltmp++;
		Clusterlabel++;
		}
	}
	for(i=1;i<Clusterlabel;i++){
		printf("\n%d.Cluster:",i);
		for(k=0;k<vertex;k++){
			if(label[k]==i)
			printf("%3d",k);
	}
	}
}
void minDistanceBetweenClusters(int Cluster1,int Cluster2,int graph[][vertex],int label[]){
	int min=1000;
	int i,j;
	for(i=0;i<vertex;i++){
		if(label[i]==Cluster1){
			for(j=0;j<vertex;j++){
				if(label[j]==Cluster2){
					if(graph[i][j]<min && graph[i][j]!=0)
					min=graph[i][j];
				}
			}
		}
	}
	if(min==1000)printf("\nThere is no connection between these Clusters");
	else
	printf("\nMinimum Distance Between Cluster:%d and Cluster:%d : %d",Cluster1,Cluster2,min);
}	
int main(){
	int vertexNums;
	int clusterNums;
	int i,j;
	char temp;
	printf("Enter the Vertex number:\n");
	scanf("%d",&vertexNums);
	printf("\nEnter Cluster Number:");
	scanf("%d",&clusterNums);
	vertex=vertexNums;
	int label[vertexNums];
	int graph[vertexNums][vertexNums];
	FILE *fp;
	
	if((fp=fopen("data.txt","r"))==NULL){
		printf("File is not opened");
	}
	
	fseek(fp,0,SEEK_SET);
	for(i=0;i<vertexNums;i++){
		
		for(j=0;j<vertexNums;j++){
		fscanf(fp,"%d",&graph[i][j]);
		fscanf(fp,"%c",&temp);
	}
}
  	initializeLabel(label);
	minSpan(graph,label,clusterNums);
	arrangeAndPrint(label);
	
	int Cluster1;
	int Cluster2;
	printf("\n\nEnter the two Clusters which you want to calculate distance between them:");
	printf("\nFirts Cluster Number:");
	scanf("%d",&Cluster1);
	printf("\nSecond Cluster Number:");
	scanf("%d",&Cluster2);
	minDistanceBetweenClusters(Cluster1,Cluster2,graph,label);
}
