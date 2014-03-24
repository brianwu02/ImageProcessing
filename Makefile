#
# Sample Makefile for Image Processing class
#
#	George Wolberg (wolberg@cs.ccny.cuny.edu)
#
# This Makefile can be used for all homework assignments, simply
# by changing the ALL variable, and each of the target names
#
#
CC	= g++	# Use gcc compiler. Use g++ for C++ compilation.
CFLAGS	= -g # Compiler flags: -g for debug, -O for optimization
LDFLAGS	= 	# Linker flags
LIBS	= -lm	# Libraries to link with (-lm is the math library)

# This is the Master Compile command, which can be used for
# all executables. Simply make a new entry for each one underneath,
# and change the ALL variable.
# YOU SHOULD NOT NEED TO TOUCH THIS.
#
#   $@ stands for the target name (i.e., the resulting executable)
#   $? stands for the dependency list (i.e., the .o files)
#
COMPILE_EXECUTABLE = $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $? $(LIBS)

# These are all the files to be compiled.
ALL = blur sharpen unordered_dither ordered_dither halftone error_diffusion error_diffusion1 median convolve 
all:	$(ALL)

# List of executable targets
blur: $($@.o) IPutil.o
unordered_dither: $($@.o) IPutil.o
ordered_dither: $($@.o) IPutil.o
halftone: $($@.o) IPutil.o
error_diffusion: $($@.o) IPutil.o
error_diffusion1: $($@.o) IPutil.o
sharpen: $(@.o) IPutil.o
median: $(@.o) IPutil.o
convolve: $(@.o) IPutil.o briansFunctions.o


# Clean target to remove backup, object, and core files
clean:
	rm -f *~ *.o core
cleanx:
	rm -f *~ *.o core $(ALL)

# Dependencies
IPutil.o:	IP.h
briansFunctions.o: IP.h

blur.o: IP.h
unordered_dither.o: IP.h
ordered_dither.o: IP.h
halftone.o: IP.h
error_diffusion.o: IP.h
error_diffusion1.o: IP.h
sharpen.o: IP.h
median.o: IP.h
convolve.o: IP.h


