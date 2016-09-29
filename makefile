CC = arm-linux-gnueabihf-gcc
host: CC = gcc
bbb:  CC = arm-linux-gnueabihf-gcc
frdm: CC = arm-none-eabi-gcc
host: SZ = size
bbb:  SZ = arm-linux-gnueabihf-size
frdm: SZ = arm-none-eabi-size
include sources.mk
CFLAGS = -Werror -g -O0 -std=c99 -Arch=x86
host: CFLAGS = -Werror -g -O0 -std=c99 -Arch=x86
bbb:  CFLAGS = -Werror -g -O0 -std=c99 -Arch=ARM
frdm:  CFLAGS = -Werror -g -O0 -std=c99 -Arch=ARM --specs=nosys.specs
override DEFINES += -DPROJECT1
LDFLAGS = -Xlinker -Map=main.map
OBJS = $(SRCS:.c=.o)
LIBOBJS = $(LIBS:.c=.o)
PREOBJS = $(SRCS:.c=.i)
ASMOBJS = $(SRCS:.c=.S)
OUTPUT = proj1

.PHONY: size host bbb frdm preprocess asm-file compile-all build clean build-lib %.o %.i %.S

host: $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $(OUTPUT) $(LDFLAGS) $(DEFINES)
	$(SZ) $(OUTPUT)

bbb: $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $(OUTPUT)bbb $(LDFLAGS) $(DEFINES)
	$(SZ) $(OUTPUT)bbb

frdm: $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) $(INCLUDES) -o $(OUTPUT)frdm $(DEFINES) -DFRDM
	$(SZ) $(OUTPUT)frdm

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
	mv $*.o ./ObjectFiles/

%.i: %.c
	$(CC) -E -o $*.i $*.c $(INCLUDES)
	mv $*.i ./Preprocess/

%.S: %.c
	$(CC) $(CFLAGS) -S -o $*.S $*.c $(INCLUDES)
	mv $*.S ./Assembly/

clean:
	-rm -f $(OUTPUT)* ./*/*.o ./*/*.d ./*/*.i ./*/*.S main.map *.a ./Preprocess/* \
	./ObjectFiles/* ./Assembly/*
