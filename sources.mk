INCLUDES = \
	-I ./Main/   \
	-I ./Data/   \
	-I ./Memory/ \
	-I ./Project1/ \
	-I ./Testing/ \
	-I ./CircularBuffer/ \
	-I ./FRDM_INCLUDES/ \
	-I ./Modules \
	-I ./FRDM_Startup_Code/ \
	-I ./Logging/


SRCS = \
	./Main/main.c   \
	./Memory/memory.c \
	./Data/data.c \
	./Project1/project1.c \
	./CircularBuffer/circularbuffer.c \
	./Modules/uart.c \
	./Modules/led.c \
	./Modules/timers.c \
	./Modules/diags.c \
	./Modules/spi.c \
	./Logging/uartlogging.c \
	./Testing/testing.c \
	./Testing/datatesting.c \
	./Testing/memorytesting.c \
	./Testing/circularbuffertesting.c \
	./Testing/performancetesting.c \


STARTUP = \
	./FRDM_Startup_Code/startup_MKL25Z4.S \
	./FRDM_Startup_Code/system_MKL25Z4.c \

LIBS = \
	./Memory/memory.c \
	./Data/data.c \
	./CircularBuffer/circularbuffer.c \
	./Modules/uart.c \
	./Modules/led.c \
	./Modules/timers.c \
	./Modules/diags.c 	\
