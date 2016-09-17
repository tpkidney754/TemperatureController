host: CC = gcc
bbb:  CC = arm-linux-gnueabi-gcc
frdm: CC = arm-none-eabi-gcc
include sources.mk
CFLAGS = -Werror -g -O0 -std=c99
LDFLAGS = -Xlinker -Map=main.map
OBJS = $(SRCS:.c=.o)
OBJS = $(SRCS:.c=.o)
LIBOBJS = $(LIBS:.c=.o)
PREOBJS = $(SRCS:.c=.i)
ASMOBJS = $(SRCS:.c=.S)
OUTPUT = proj1
.PHONY: host bbb frdm preprocess asm-file compile-all build clean build-lib %.o %.i %.S

host: $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $(OUTPUT)

bbb: $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $(OUTPUT)bbb

frdm: $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $(OUTPUT)frdm

preprocess: $(PREOBJS)

asm-file: $(ASMOBJS)

compile-all: $(OBJS)

build: host bbb frdm

upload: bbb
	scp $(OUTPUT)bbb root@192.168.1.10:/home/debian/bin/

build-lib: $(LIBOBJS)
	ar rcs libproject1.a $(LIBOBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $*.c $(INCLUDES) -o $@
	$(CC) -M $(CFLAGS) $*.c > $*.d $(INCLUDES)

%.i: %.c
	$(CC) -E -o $*.i $*.c $(INCLUDES)

%.S: %.c
	$(CC) $(CFLAGS) -S -o $*.S $*.c $(INCLUDES)

clean:
	-rm -f $(OUTPUT)* ./*/*.o ./*/*.d ./*/*.i ./*/*.S main.map *.a
