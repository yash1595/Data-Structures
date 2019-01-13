#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define BUFFSIZE    3

typedef enum{Buffer_Full,Success,BuffAllocationError,CycBuffAllocationError,FreeingError,FreedCycBuffs,DataDeletionError,InvalidIndex}errtype;
char* errtypes[]={"\nBuffer Full\n","\nSuccess\n","\nBuffer Allocation Error\n","\nCyclic Buffer Allocation Error\n","\nFreeing Error\n","\nFreed Cyclic Buffers\n","\nError Deleting Data\n","\nInvalid Index\n"};
char* functions[]={"alloc","add","disp","free","del","realloc","exit"};
//typedef enum{CLEAR,SET}flag_status;
#define CLEAR	0
#define SET	1
errtype ring_t_init(char,uint32_t);
errtype AddDataCycBuff(char ,uint32_t);
errtype DelDataCycBuff(char ,uint32_t);
errtype DisplayCycBuff(char ,uint32_t);
errtype DisplayAllBuffers(char , uint32_t);
errtype Allocate(char,uint32_t);
errtype FreeMem(char,uint32_t);
errtype exit_main(char,uint32_t);
typedef struct{
    char* buffer;
    uint32_t Ini;
    uint32_t Outi;
    uint32_t length;
    uint8_t full_flag;
    uint8_t buff_flag;
    uint8_t add_flag;
    uint8_t realloc_flag
}ring_t;
int8_t index_=-1;
ring_t* CycBuffs[BUFFSIZE]={NULL};
/*flag_status add_flag=CLEAR;
flag_status realloc_flag=CLEAR;
flag_status buff_flag=CLEAR;*/
//flag_status full_flag=CLEAR;

errtype (*ptr[7]) (char , uint32_t );

uint32_t characters[256]={0};
uint8_t i=0,entered=0;

errtype ring_t_init(char data,uint32_t length){
    uint32_t buff_index=0,i=0;
    
    for(buff_index=0;buff_index<3;buff_index+=1)
    {
        if(CycBuffs[buff_index]==NULL)break;
    }
    if(CycBuffs[buff_index]!=NULL)return CycBuffAllocationError;
    

    CycBuffs[buff_index]=(ring_t*)malloc(sizeof(ring_t));
    if(CycBuffs[buff_index]==NULL)return CycBuffAllocationError;
    CycBuffs[buff_index]->Ini=0;
    CycBuffs[buff_index]->Outi=0;
    CycBuffs[buff_index]->length=length;
    CycBuffs[buff_index]->full_flag=CLEAR;
    CycBuffs[buff_index]->buff_flag=CLEAR;
    CycBuffs[buff_index]->realloc_flag=CLEAR;
    //CycBuffs[buff_index]->buffer = (char*)malloc(CycBuffs[buff_index]->length);
    CycBuffs[buff_index]->buffer = (char*)malloc(CycBuffs[buff_index]->length);
    printf("%d",(CycBuffs[buff_index]->length));
    //memset( (void *)&buffer, '\0', sizeof(buffer));
    memset(CycBuffs[buff_index]->buffer,'\0',sizeof(char)*length);
    //while(i<length){puts(CycBuffs[buff_index]->buffer[i]+'0');i++;}
    if(CycBuffs[buff_index]->buffer==NULL)return BuffAllocationError;
    index_++;

    return Success; 
}

errtype AddDataCycBuff(char data,uint32_t buff_index)
{   
    buff_index=-1;
    printf("Enter the buffer index:");
    while(buff_index==-1)
        {
            scanf("%d",&buff_index);//buff_index= uart0_strtoint();
            if(buff_index<0 || buff_index>255)return Buffer_Full;
            if(buff_index>index_||CycBuffs[buff_index]==NULL)buff_index=-1;
        }
   if(CycBuffs[buff_index]->full_flag==SET)return Buffer_Full;
    uint8_t singleton=1;
    char ch[0]={};
    printf("Enter the characters:");
    scanf("%c",&ch[0]);//data=getchar();
    if((ch[0]=='\n') || (ch[0]==13) || (ch[0]==10))
    {
        scanf("%c",&ch[0]); 
        if((ch[0]=='\n') || ((int)ch[0]==13) || ((int)ch[0]==10) ) return Success;
        else printf("%c",ch[0]);
    }
    while(1){
        if((int)ch[0]==13 || (int)ch[0]==10 || ch[0]=='\n' || ch[0]==27)return Success; //ASCII value of carriage return
	if(singleton!=0){
	uint32_t next = CycBuffs[buff_index]->Ini+1;
	if(next>=CycBuffs[buff_index]->length)next=0;
	if(CycBuffs[buff_index]->buff_flag==SET){CycBuffs[buff_index]->Ini=next;next+=1;CycBuffs[buff_index]->buff_flag=CLEAR;}
	if(CycBuffs[buff_index]->Ini>=CycBuffs[buff_index]->length){CycBuffs[buff_index]->Ini=0;next+=1;}			
	CycBuffs[buff_index]->buffer[CycBuffs[buff_index]->Ini]=ch[0];
	if(next==CycBuffs[buff_index]->Outi){CycBuffs[buff_index]->buff_flag=SET;CycBuffs[buff_index]->full_flag=SET;return Buffer_Full;}
	CycBuffs[buff_index]->Ini=next;
	}
	singleton=1;	
	scanf("%c",&ch[0]);//data=getchar();
    	printf("%c",ch[0]);
    	if(ch[0]==13 || ch[0]==10 || ch[0]=='\n' || ch[0]==27)return Success;
	}

}
errtype DelDataCycBuff(char data,uint32_t buff_index){
    printf("Enter the buffer to delete data:");
    uint32_t num_of_loc=0;
    buff_index=-1;
    while(buff_index==-1)
    {
        scanf("%d",&buff_index);//buff_index=uart0_strtoint();
       // if(buff_index<0 || buff_index>255)return Buffer_Full;
        if(buff_index<0 || buff_index>255||(CycBuffs[buff_index]==NULL))return InvalidIndex;
    }
    if(CycBuffs[buff_index]==NULL)return DataDeletionError;
    printf("Enter the number of locations:");
    scanf("%d",&num_of_loc);    
    if(num_of_loc >= CycBuffs[buff_index]->length) return DataDeletionError;

    uint32_t index_value=((CycBuffs[buff_index]->Outi)+num_of_loc)%(CycBuffs[buff_index]->length);
    if(index_value!=0)
    {
	if(index_value==0 || CycBuffs[buff_index]->buffer[((index_value)-1)]=='\0') return Buffer_Full;  
    }
    //if(index_value!=0)if(CycBuffs[buff_index]->buffer[((index_value)-1)]=='\0') return Buffer_Full;
    errtype value=0;
    uint32_t next,i=0;
    for(i=0;i<num_of_loc;i++){
        next = CycBuffs[buff_index]->Outi+1;
        //puts(CycBuffs[buff_index]->Outi+'0');
        if(next>=CycBuffs[buff_index]->length)next=0; /////changed
        if(CycBuffs[buff_index]->Outi==CycBuffs[buff_index]->Ini){
            printf("Outi:%d\tIni:%d\n",CycBuffs[buff_index]->Outi,CycBuffs[buff_index]->Ini);	
            return Buffer_Full;
        }
	
        CycBuffs[buff_index]->buffer[CycBuffs[buff_index]->Outi]='\0';
        CycBuffs[buff_index]->Outi=next;//=next;
	}
    //printf("Outi:%d\tIni:%d\n",CycBuffs[buff_index]->Outi,CycBuffs[buff_index]->Ini);
    CycBuffs[buff_index]->full_flag=CLEAR;
    return Success;
}

errtype DisplayCycBuff(char data,uint32_t buff_index){
    uint32_t i=0,sum=0;
    buff_index=-1;
    printf("Enter the buffer index:");
    while(buff_index==-1)
    {
        scanf("%d",&buff_index);//buff_index= uart0_strtoint();
        //if(buff_index>index_||CycBuffs[buff_index]==NULL){buff_index=-1;continue;}
        if(buff_index<0 || buff_index>255 || CycBuffs[buff_index]==NULL)return InvalidIndex;//buff_index=-1;//
    }
    uint32_t next=CycBuffs[buff_index]->Outi;
    uint32_t current=CycBuffs[buff_index]->Ini;
    if(current>=CycBuffs[buff_index]->length)current=0;
    //if(CycBuffs[buff_index]->Ini==next){printf("Circular Array Full\n");return Buffer_Full;}
    if(current<CycBuffs[buff_index]->Outi){
        for(i=next;i<CycBuffs[buff_index]->length;i++){printf("%c",CycBuffs[buff_index]->buffer[i]);sum++;}
        next=0;
    }
    if(next<=current){
        for(i=next;i<=current;i++){printf("%c",CycBuffs[buff_index]->buffer[i]);sum++;}
    }
    printf("Outi:%d\tIni:%d\n",CycBuffs[buff_index]->Outi,current);//if(type==TSI)enable_irq(12);
    printf("Sum:%d\n",sum);
    return Success;
}

errtype Allocate(char data,uint32_t length)
{   
    errtype AllocateStatus=-1;
    printf("Enter the length of the buffer:");
    length=-1;
    scanf("%d",&length);//length = uart0_strtoint();
    if(index_>BUFFSIZE || length<=0 || length>255){printf("%d",index);return Buffer_Full;}
    AllocateStatus= ring_t_init(data,length);
   
    //if(type==TSI)enable_irq(12);
    return AllocateStatus;
}

errtype DisplayAllBuffers(char data, uint32_t length)
{
    uint32_t size=0,rev=0,count=0,num=0;
    for(size=0;size<BUFFSIZE;size+=1){
        printf("%d",size);
        printf(" : ");
        if(CycBuffs[size]==NULL)printf(" ");
        else{
            //if(CycBuffs[size]->length<10)printf("%d",CycBuffs[size]->length);
            num=CycBuffs[size]->length;
            printf("%d",num);//uart0_inttostr(num);
            
        }
        printf("\n");
    }
    return Success;
}

errtype FreeMem(char data,uint32_t buff_index)
{
        errtype FreeStatus=-1;
        DisplayAllBuffers(0,0);
        buff_index=-1;
        while(buff_index==-1)
        {
        printf("Enter the index of the buffer\n");
        scanf("%d",&buff_index);//buff_index = uart0_strtoint();
        if(buff_index<0 || buff_index>255)return Buffer_Full;
        //if(CycBuffs[buff_index]->buffer=NULL)buff_index=-1;
        }
       // if(buff_index>index_)return FreeingError;
        if(CycBuffs[buff_index]==NULL)return FreeingError;
        free(CycBuffs[buff_index]->buffer);
        CycBuffs[buff_index]->buffer=NULL;
        free(CycBuffs[buff_index]);
        CycBuffs[buff_index]=NULL;
        index_-=1;
        //if(type==TSI)enable_irq(12);
        return Success;
}

errtype FreeAll(char data,uint32_t buff_index)
{
    errtype FreeStatus=-1;
    uint8_t k=0;
    for(k;k<10;k+=1)free(CycBuffs[k]);
    return FreedCycBuffs;
}

errtype ReallocBuff(char data,uint32_t buff_index)
{
    uint32_t index,i=0,resize=0;
    buff_index=-1;
    printf("Enter the buffer index:");
    while(buff_index==-1)
    {
        scanf("%d",&buff_index);//buff_index= uart0_strtoint();
        if(buff_index>index_||CycBuffs[buff_index]==NULL)buff_index=-1;
        if(buff_index<0 || buff_index>255)return Buffer_Full;//buff_index=-1;//
    }
    printf("Enter the new size:");
    scanf("%d",&resize);
    if(resize>255 || resize<0)return BuffAllocationError;
    CycBuffs[buff_index]->buffer = (char*)realloc(CycBuffs[buff_index]->buffer,resize);
    CycBuffs[buff_index]->length=resize;
   // CycBuffs[buff_index]->buffer=realloc(CycBuffs[buff_index]->buffer,sizeof(uint32_t)*resize);
    printf("%d",(CycBuffs[buff_index]->length));
    if(CycBuffs[buff_index]->buffer==NULL)return BuffAllocationError;
    CycBuffs[buff_index]->realloc_flag=SET;
    return Success;
    
}
errtype exit_main(char data,uint32_t buff_index)
{
	exit(1);
}
