void countset(int num){
	int i;
	int res;
	for(i=0;i<32;i++){
		res=((num>>i)&1);
		if(res==1){
		printf("%d",res);
		printf(",");
	}}
}

int main()
{
	int n;
	scanf("%d",&n);
	printf("The Set bits \n");
	countset(n);
}