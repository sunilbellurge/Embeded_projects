#include<stdio.h>
#include<stdlib.h>

void swap(int *a , int *b){
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
void reverse(int *arr , int n){
	int i=0;
	int m=n-1;
	while(i<=m){
		swap(&arr[i],&arr[m]);
		i++;
		m--;
	}
	int j;
	for(j=0;j<n;j++){
		printf("%d",arr[j]);
		printf(",");
	}
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
	
	printf("Array after swaping\n");
	reverse(arr,n);
}
