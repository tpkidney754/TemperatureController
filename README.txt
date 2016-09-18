Makefile commands:

make host: Compiles for the host
make bbb: Comiles for the Beagle Bone Black
make frdm: Compiles for the MKL25Z FRDM board
make preprocess: This will run the preprocess portion of compliling and then stop
make asm-file: This will compile but not assemble and link all files.
make compile-all: This will compile and assemble but not link all files.
make build: This will compile, assemble, and link for the three main targets.
make upload: This will compile, assemble, link, and upload the executable 
			 to the Beagle Bone Black.
make build-lib: This will build an archive library for the data.c and memory.c files.
make /Directory/file.o: This will individually compile and assemble a file when passed 
						 the directory and file the user wishes to build and output to
						 the same directory file.o
make /Directory/file.i: This will individually preprocess a file when passed 
						 the directory and file the user wishes to preprocess and output to
						 the same directory file.i
make /Directory/file.S: This will individually compile but not assemble a file when passed 
						 the directory and file the user wishes to compile and output to
						 the same directory file.S
make clean: This will remove and *.o, *.d, *.i, *.S, *.map or *.a file located in the 
				directory.

The make file will output and executable as follows:
host: proj1
bbb: proj1bbb
frdm: proj1frdm