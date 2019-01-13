objects = main2.o CircularBufferHeader.h a.out 
edit	:	$(objects)
project1_latest.o : main2.c CircularBufferHeader.h
					cc -c main2.c
		    gcc main2.c -w	
																
a.out		: main2.o CircularBufferHeader.h
		gcc main2.c -w
		
CircularBufferHeader.h	:	main2.c

clean: 
		rm edit $(objects)
