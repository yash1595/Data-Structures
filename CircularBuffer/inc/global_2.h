#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define BUFFSIZE    3

typedef enum{Buffer_Full,Success,BuffAllocationError,CycBuffAllocationError,FreeingError,FreedCycBuffs,DataDeletionError}errtype;
char* errtypes[]={"\nBuffer Full\n","\nSuccess\n","\nBuffer Allocation Error\n","\nCyclic Buffer Allocation Error\n","\nFreeing Error\n","\nFreed Cyclic Buffers\n","\nError Deleting Data\n"};
char* functions[]={"alloc","add","disp","free","del","realloc"};
typedef enum{CLEAR,SET}flag_status;
errtype ring_t_init(char*,uint32_t,uint32_t);
errtype AddDataCycBuff(char*,uint32_t,uint32_t);
errtype DelDataCycBuff(char*,uint32_t,uint32_t);
errtype DisplayCycBuff(char*,uint32_t,uint32_t);
errtype DisplayAllBuffers(char*,uint32_t,uint32_t);
errtype Allocate(char*,uint32_t,uint32_t);
errtype FreeMem(char*,uint32_t,uint32_t);
typedef struct{
    char* buffer;
    uint32_t Ini;
    uint32_t Outi;
    uint32_t length;
}ring_t;
int8_t index_=-1;
ring_t* CycBuffs[BUFFSIZE]={NULL};
flag_status add_flag=CLEAR;
flag_status realloc_flag=CLEAR;
flag_status buff_flag=CLEAR,full_flag=CLEAR;

errtype (*ptr[6]) (char , uint32_t );

uint32_t characters[256]={0};
uint8_t i=0,entered=0;
