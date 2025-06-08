
#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

void REMOVE_DUP(int *arr , int n ){
	int max;
	int i;
	int maximum=0;
	for(i=0;i<n;i++){
		if(arr[i]>maximum){
			maximum=arr[i];
		}
	}
	if(maximum<n){
		maximum=n;
	}
	int help;
	int helper[maximum]={0};
//	for(help=0;help<n;help++){
//		printf("%d",helper[help]);
//		printf(" ");
//	}
	int j;
	for(j=0;j<n;j++){
		helper[arr[j]]++;
	}
	/*for(help=0;help<n;help++){
		printf("%d",helper[help]);
		printf(" ");
	}*/
	int m;
	for(m=0;m<n;m++){
		if(helper[arr[m]]>1){
			arr[m]=0;
		}
	}
	
	//Printing after modifications 
	
	int k;
	for(k=0;k<n;k++){
		printf("%d",arr[k]);
		printf(" ");
	}
	printf("\n");
}

int main()
{
	int n;
	scanf("%d",&n);
	int *arr=(int *)malloc(n*(sizeof(int)));
	int i;
	for(i=0;i<n;i++){
		scanf("%d",&arr[i]);
	}
	
    REMOVE_DUP(arr,n);	
}