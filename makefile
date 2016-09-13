CC = c99
XCC = arm-linux-gnueabihf-gcc
LD = ld
XLD = arm-linux.gnueabi-ld
CFLAGS = -Wall -g -O0 -std=c99
LDFLAGS = -Map hw2.map -T
SRCS = \
	main.c \
	hw1.c
OBJS = $(SRCS:.c=.o)
INCLUDES = -I .
OUTPUT = hw2

hw2.exe: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(OUTPUT).exe

hw2BB.exe: $(OBJS)
	$(XCC) $(CFLAGS) $(INCLUDES) $(SRCS) -o $(OUTPUT)BB.exe

%.o: %.c
	$(CC) $(OPTIONS) -c $*.c $(INCLUDES) 

clean:
	-rm -f *.exe *.o