#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct morse
{
	char ch,morse[7];
	struct morse *next;
}M;
M *hptr=0;
void morse_init()
{
	M *temp;
	temp=malloc(sizeof(M));
	FILE *fp;
	fp=fopen("data","r");
	if(fp<0)
	{
		perror("data");
		exit(0);
	}
	while(fscanf(fp,"%c %s\n",&temp->ch,temp->morse)!=EOF)
	{
		temp->next = hptr;
		hptr = temp;
		temp=malloc(sizeof(M));
	} 
}

void morse_print(M *ptr)
{
	while(ptr)
	{ 
		printf("%c %s\n",ptr->ch,ptr->morse);
		ptr=ptr->next;
	}
}

int main(int argc, char **argv)
{
	if(argc <=2)
	{
		if(argc!=2 || strcmp(argv[1],"--help")!=0)
			printf("Usage : ./a.out option message\n\nTry ./a.out --help morse for details\n");
		else
			printf("./a.out option message\n\noptions:\n\t m or M --message to morse code\n\t a or A  --Message to Ascii\n"); 
		return ;
	}

	morse_init();
	// morse_print(hptr); // for checking
	if(strcmp(argv[1],"m")==0 || strcmp(argv[1],"M")==0)
		ascii_to_morse(argv[2]); 
	//else if(strcmp(argv[1],"a")==0 || strcmp(argv[1],"A")==0)
	//    morse_to_ascii(argv[2]); 
	else
		printf("Inavlid option\n");
	printf("\n");          
	return 0;
} 

void ascii_to_morse(const char *str)
{
	int i=0;
	M *ptr;
	while(str[i])
	{
		ptr=hptr;
		while(ptr)
		{
			if(ptr->ch==str[i] || ptr->ch==str[i]-32)
			{
				printf("%s ",ptr->morse);
				break;
			}
			ptr=ptr->next;
		}
		if(ptr==0)
			printf("   ");
		i++;
	}
}
