SOURCE		= scanner
CFLAGS		= -g -c
CC		= gcc
OUT		= scanner
LIBS		= 
INCS		= 

all:	$(SOURCE).o 
	gcc -g -o $(OUT) $(SOURCE).o 

$(SOURCE).o:	$(SOURCE).c
	$(CC) $(CFLAGS) $(SOURCE).c

clean:	
	rm -f $(SOURCE).o $(OUT)
	
