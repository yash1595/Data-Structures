/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


/******************************************************************************

Welcome to GDB Online.
GDB online is an online compiler and debugger tool for C, C++, Python, Java, PHP, Ruby, Perl,
C#, VB, Swift, Pascal, Fortran, Haskell, Objective-C, Assembly, HTML, CSS, JS, SQLite, Prolog.
Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/

//#include "fibonacci.h"

#ifdef __linux__
#include "../inc/CircularBufferHeader.h"
#endif


#ifdef __linux__
int main (void)
{
     errtype status=-1;
     ptr[0]=Allocate;
     ptr[1]=AddDataCycBuff;
     ptr[2]=DisplayCycBuff;
     ptr[3]=FreeMem;
     ptr[4]=DelDataCycBuff;
     ptr[5]=ReallocBuff;//InitCycBuff(0,0);
     ptr[6]=exit_main;//ring_t_init();

     char ch=0;
     char str[10];
     uint32_t func_index=-1;
     uint8_t i=0;
     while(1)
     {
                scanf("%s",&str);;
                for(i=0;i<7;i++)
                {   //puts("here");
                    if(strcmp(str,functions[i])==0)
                    {
                        status=(*ptr[i])('0',0);
                        printf("%s",errtypes[status]);
                        break;
                    }

                }

     }
     return 0;
}


#else
#include "MKL25Z4.h"
#include  "nvic.h"
#include "Uart0_Init.h"
#include "circular_buff_init.h"
#include "enums.h"
#include "TSI_lib.h"

int main(){
	 uart0_pinset();
	 uart0_init();
	 uint8_t entered=0,in=0;
	 ptr[0]=Allocate;
	 ptr[1]=AddDataCycBuff;
	 ptr[2]=DisplayCycBuff;
	 ptr[3]=FreeMem;
	 ptr[4]=DelDataCycBuff;
	 ptr[5]=ReallocBuff;
	 char ch=0;
	 uint32_t i=0,func_index=-1;
	 uart0_putstr("Select Mode of Input\n1.Blocking\t2.Non-blocking\n");
	 while(1)
	 {
	 	 	 ch=uart0_getchar();
	 	 	 if(ch=='1'){mode=BLOCKING;break;}
	 	 	 if(ch=='2'){mode=NONBLOCKING;break;}

	 }
	 if(mode==BLOCKING)
	 {//case BLOCKING:
	 uart0_putstr("Select Mode of Input\n1.TSI\t2.TYPE\n");
	 while(1)
	 	{
	 		ch=uart0_getchar();
	 		if(ch=='1'){type=TSI;break;}
	 		if(ch=='2'){type=TYPE;break;}

	 	}

	 if(type==TYPE)
	 	{	 uart0_putstr("Entered the type mode\n");
	 	 	 uart0_putstr("0.allocate,1.add,2.disp,3.free,4.del\n,5.realloc\n");
	 	 	 while(1)status=uart0_getstr();

	 	}
	 else if(type==TSI)
	 {	 uart0_putstr("Entered the TSI mode\n");
		 InitLEDsGPIO();
		 InitTSI();
		 EnableInterrupts;
		 enable_irq(12);
		 set_irq_priority((12), 2);
		 ISR();
		 static uint8_t alternate=0;
		 while(1)
		 {
			 ScanTSI();
			 if((deltaResult[0] > THRESHOLD) ||(deltaResult[1] > THRESHOLD))
			 {
				 alternate=alternate^1;
				 if(alternate==1)ChangeLEDColor(ReadTSI()); // Use LEDs to display touch
			 }
			 else LEDsOff(); // No touch present, turn off LEDs


		 }
	 }
	 }

	 else if(mode==NONBLOCKING){
	 uart0_putstr("Non-blocking\n");
	 status=ring_t_init(0,256);
	 uart0_putstr(errtypes[status]);
	 InitLEDsGPIO();
	 EnableInterrupts;
	 enable_irq(12);
	 set_irq_priority((12), 2);
	 ISR();
	 uart0_putstr("Enter the characters\n");
	 while(1)
	 {
	     if(flag==SET)
	     	{
	    	 	 disable_irq(12);
	    	 	 stat=Success;
	    	 	 flag=CLEAR;
	    	 	 uart0_inttostr(CycBuffs[0]->Outi);
	    	 	 enable_irq(12);
	    	 	 display_character_count();
	     	}
	     else fibonacci();

	   }

	  }
   }
#endif


