INCLUDES = \
	-I ./Main/   \
	-I ./Data/   \
	-I ./Memory/ \
	-I ./Project1/ \
	-I ./Testing/ \
	-I ./CircularBuffer/ \
	-I ./HW3/ \
	-I ./FRDM_INCLUDES/ \
	-I ./Modules \
	-I ./FRDM_Startup_Code/ \

SRCS = \
	./Main/main.c   \
	./Memory/memory.c \
	./Data/data.c \
	./Project1/project1.c \
	./Testing/testing.c \
	./CircularBuffer/circularbuffer.c \
	./HW3/hw3.c \
	./Modules/uart.c \
	./Modules/led.c \
	./Modules/timers.c \
	./FRDM_Startup_Code/system_MKL25Z4.c \

STARTUP = \
	./FRDM_Startup_Code/startup_MKL25Z4.S \

LIBS = \
	./Memory/memory.c \
	./Data/data.c \
	./CircularBuffer/circularbuffer.c \
	./Modules/uart.c \
	./Modules/led.c \
	./Modules/timers.c \
