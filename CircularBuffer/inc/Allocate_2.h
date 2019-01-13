#include "global_2.h"

errtype ring_t_init(char* data,uint32_t buff_index,uint32_t length){
    //uint32_t buff_index=0;
    
    for(buff_index=0;buff_index<3;buff_index+=1)
    {
        if(CycBuffs[buff_index]==NULL)break;
    }
    if(CycBuffs[buff_index]!=NULL)return 0;
    

    CycBuffs[buff_index]=(ring_t*)malloc(sizeof(ring_t));
    if(CycBuffs[buff_index]==NULL)return 0;
    CycBuffs[buff_index]->Ini=0;
    CycBuffs[buff_index]->Outi=0;
    CycBuffs[buff_index]->length=length;
    //CycBuffs[buff_index]->buffer = (char*)malloc(CycBuffs[buff_index]->length);
    CycBuffs[buff_index]->buffer = (char*)malloc(CycBuffs[buff_index]->length);
    printf("%d",(CycBuffs[buff_index]->length));
    //memset( (void *)&buffer, '\0', sizeof(buffer));
    memset(CycBuffs[buff_index]->buffer,'\0',sizeof(char)*length);
    //while(i<length){puts(CycBuffs[buff_index]->buffer[i]+'0');i++;}
    if(CycBuffs[buff_index]->buffer==NULL)return 0;
    index_++;

    return 1; 
}

errtype AddDataCycBuff(char* data,uint32_t buff_index,uint32_t length){
	while(*data!='\n'){
        //if((int)ch[0]==13 || (int)ch[0]==10 || ch[0]=='\n' || ch[0]==27)return Success; //ASCII value of carriage return
	uint32_t next = CycBuffs[buff_index]->Ini+1;
	if(next>=CycBuffs[buff_index]->length)next=0;
	if(buff_flag==SET){CycBuffs[buff_index]->Ini=next;next+=1;buff_flag=CLEAR;}
	if(CycBuffs[buff_index]->Ini>=CycBuffs[buff_index]->length){CycBuffs[buff_index]->Ini=0;next+=1;}			
	CycBuffs[buff_index]->buffer[CycBuffs[buff_index]->Ini]=*data;
	//printf("Ini:%d,",CycBuffs[buff_index]->Ini);
	if(next==CycBuffs[buff_index]->Outi){buff_flag=SET;full_flag=SET;return 0;}
	data+=1;
	CycBuffs[buff_index]->Ini=next;
	}
	return 1;
}

errtype DelDataCycBuff(char* data,uint32_t buff_index,uint32_t num_of_loc){
    if(num_of_loc >= CycBuffs[buff_index]->length) return 0;
    if(CycBuffs[buff_index]->buffer[((((CycBuffs[buff_index]->Outi)+num_of_loc)%(CycBuffs[buff_index]->length))-1)]=='\0') return 0;
    uint32_t next,i=0;
    for(i=0;i<num_of_loc;i++){
        next = CycBuffs[buff_index]->Outi+1;
        if(next>=CycBuffs[buff_index]->length)next=0;
        if(CycBuffs[buff_index]->Outi==CycBuffs[buff_index]->Ini){
            return 0;
        }
        CycBuffs[buff_index]->buffer[CycBuffs[buff_index]->Outi]='\0';
        CycBuffs[buff_index]->Outi=next;//=next;
    }
    full_flag=CLEAR;
    return 1;
}

errtype DisplayCycBuff(char* data,uint32_t buff_index,uint32_t length){
    if(buff_index>=BUFFSIZE || CycBuffs[buff_index]==NULL)return 0;
    uint32_t next=CycBuffs[buff_index]->Outi;
    if(CycBuffs[buff_index]->Ini<CycBuffs[buff_index]->Outi){
        for(i=next;i<CycBuffs[buff_index]->length;i++);//{printf("%c",CycBuffs[buff_index]->buffer[i]);}
        next=0;
    }
    if(next<=CycBuffs[buff_index]->Ini){
        for(i=next;i<=CycBuffs[buff_index]->Ini;i++);//{printf("%c",CycBuffs[buff_index]->buffer[i]);}
    }
    return 1;
}

errtype Allocate(char* data,uint32_t buff_index,uint32_t length)
{   
    errtype AllocateStatus=-1;
    if(buff_index<0 || buff_index>3)return 0;
    if(length>256)return 0;
    AllocateStatus= ring_t_init(data,0,length);
    return AllocateStatus;
}

errtype DisplayAllBuffers(char* data,uint32_t buff_index,uint32_t length)
{
    uint32_t size=0,num=0;
    for(size=0;size<BUFFSIZE;size+=1){
        printf("%d",size);
        printf(" : ");
        if(CycBuffs[size]==NULL)printf(" ");
        else{
            num=CycBuffs[size]->length;
            printf("%d",num);
            
        }
        printf("\n");
    }
    return Success;
}

errtype FreeMem(char* data,uint32_t buff_index,uint32_t length)
{
        if(buff_index>index_)return 0;
        if(CycBuffs[buff_index]==NULL)return 0;
        free(CycBuffs[buff_index]->buffer);
        CycBuffs[buff_index]->buffer=NULL;
        free(CycBuffs[buff_index]);
        CycBuffs[buff_index]=NULL;
        index_-=1;
        return 1;
}

errtype FreeAll(char* data,uint32_t buff_index,uint32_t length)
{
    uint8_t k=0;
    for(k=0;k<10;k+=1)free(CycBuffs[k]);
    return FreedCycBuffs;
}

errtype ReallocBuff(char* data,uint32_t buff_index,uint32_t length)
{
    if(buff_index>index_ || buff_index<0)return 0;
    if(length>255 || length<0 || length<=CycBuffs[buff_index]->length)return 0;
    CycBuffs[buff_index]->buffer = (char*)realloc(CycBuffs[buff_index]->buffer,length);
    CycBuffs[buff_index]->length=length;
    printf("%d",(CycBuffs[buff_index]->length));
    if(CycBuffs[buff_index]->buffer==NULL)return 0;
    realloc_flag=SET;
    return 1;
    
}

errtype exit_main(char* data,uint32_t buff_index,uint32_t length)
{
	exit(1);
}
