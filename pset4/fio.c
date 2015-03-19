#include <stdio.h>

int main(void)
{
	FILE* f = fopen("test.txt", "w");
	
	if(f == NULL)
		return 1;
		
	char a[] = "ABCDEFGHUJKLMONPQRSTUVWXYZ";
	fwrite(a, sizeof(a[0]), sizeof(a) / sizeof(a[0]), f);
	
	fclose(f);
	
	return 0;
}
