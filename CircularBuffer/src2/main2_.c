#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#define function_count	6

static int i=0;
static int global_num=0;

char str[100];
char inputstr[100];
char* errors[]={"Success\n","Allocate Memory First\n","Index out of Bounds\n","Failed To Allocate\n","Already allocated\n"};
typedef enum{Success=0,AllocateFirst=1,OutofBounds=2,FailedToAlloc=3,AlreadyAllocated=4}errtype;

errtype Allocate(const char*);
errtype Add(const char*);
errtype Del(const char*);
errtype Free(const char*);
errtype Disp(const char*);
errtype Exit(const char*);

typedef enum{CLEAR,SET}flag;
flag allocated_flag=CLEAR;


int* memory=NULL;

int num=0;
char* funct[] = {"allocate\n","add\n","del\n","free\n","disp\n","exit\n"};
char* names[] = {"Allocate:","Add:","Del:","Free:","Disp:","Exit:"};
errtype (*f_ptr[function_count])(const char*);
FILE *fp;
time_t rawtime;
struct tm * timeinfo;


int main(void)
{	
	fp=fopen("/home/ubuntu/Documents/cunit/Project_2/src2/out.txt","w");
	time ( &rawtime );
  	timeinfo = localtime ( &rawtime );
	fprintf (fp,"[Current local time and date: %s]-------------------------------", asctime (timeinfo) );
	//openlog("main2.c", 0, LOG_USER);	
	errtype status=Success;
	f_ptr[0]=Allocate;
	f_ptr[1]=Add;
	f_ptr[2]=Del;
	f_ptr[3]=Free;
	f_ptr[4]=Disp;
	f_ptr[5]=Exit;

	printf("Enter the option\n");
	while(1)
	{
		fgets(inputstr,100,stdin);
		fprintf(fp,"%s\n",inputstr);
		//fclose(fp);
		for(i=0;i<function_count;i++)
		{
			if(strcmp((char*)funct[i],(char*)inputstr)==0)
				{	printf("%s",names[i]);
					/*time ( &rawtime );
  					timeinfo = localtime ( &rawtime );
					fprintf (fp,"[Current local time and date: %s]", asctime (timeinfo) );
					fprintf(fp,"%s--Function\n",names[i]);
					*/
					logfunc(names[i]);
					status=(*f_ptr[i])(fgets(str,100,stdin));
					printf("%s\n",errors[status]);
					/*time ( &rawtime );
  					timeinfo = localtime ( &rawtime );
					fprintf (fp,"[Current local time and date: %s]", asctime (timeinfo) );
					fprintf(fp,"%s--Status\n",errors[status]);
					*/
					logfunc(errors[status]);
					//syslog(LOG_INFO, "%s",errors[status]);
				}
		}
	  
	}

return 0;
}

errtype Allocate(const char* loc)
{	errtype status=Success;
	if(allocated_flag==SET)status=AlreadyAllocated;
	int num=atoi(loc);
	if(num<0)status=OutofBounds;
	if(status==Success)
	{	fprintf(fp,"%d\n",num);
		printf("Locations:%d\n",num);
		memory = (int*)malloc(num*sizeof(char));
		if(memory==NULL)status=FailedToAlloc;
		allocated_flag=SET;
		global_num=num;
	}
	return status;
	
	
}

errtype Add(const char* values)
{	errtype status=Success;
	if(allocated_flag==CLEAR)status=AllocateFirst;
	if(status==Success)
	{	
		static int i=0;
		i=0;
		while(values[i]!='\n')
		{	if(i>=global_num){status=OutofBounds;break;}
			memory[i]=values[i];
			fprintf(fp,"%c",values[i]);
			i+=1;
		}
	}
	return status;

}

errtype Del(const char* loc)
{	
	errtype status=Success;
	if(allocated_flag==CLEAR)status=AllocateFirst;
	int num=atoi(loc);
	static int i=0;
	if(num>global_num || num<0)status=OutofBounds;
	if(status==Success)
	{
		i=0;
		while(i<num)
		{
			memory[i]=32;
			fprintf(fp,"%c",memory[i]);
			i+=1;
		}
	}
	return status;
}


errtype Free(const char* loc)
{	errtype status=Success;
	if(allocated_flag==CLEAR)status=AllocateFirst;
	if(status==Success)
	{
		if(num>global_num)status=OutofBounds;
		if(status==Success)
		{
			free(memory);
		}
	}
	allocated_flag=CLEAR;
	return status;
}

errtype Disp(const char* loc)
{	errtype status=Success;
	if(allocated_flag==CLEAR)status=AllocateFirst;
	int locations=atoi(loc);
	static int i=0;
	if(locations>global_num || locations<0)status=OutofBounds;
	if(status==Success)
	{	fprintf(fp,"loations:%d\n",locations);
		i=0;
		while(i<locations)
		{
			printf("%c",memory[i]);
			fprintf(fp,"%c",memory[i]);
			i+=1;
		}
	}
	//fprintf(fp,"\n");
	return status;
}

errtype Exit(const char* loc)
{	errtype status=Success;
	if(allocated_flag==SET)
	{
		printf("Freeing memory\n");
		free(memory);
	}
	fclose(fp);
	exit(1);
	return status;
}

void logfunc(char* string)
{	
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	fprintf (fp,"[Current local time and date: %s]--------------------------", asctime (timeinfo));
	fprintf(fp,"%s\n",*string);
}