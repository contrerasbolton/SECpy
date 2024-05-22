CC        = g++
DEBOPT    = -O3
LFLAGS    = -Wl,-O3
GNUFLAGS  = -Wno-write-strings -fPIC #-Wall
MCCFLAGS  = -shared -DSYSV -DMCC_DOUBLE -DLINUX
CFLAGS    = $(DEBOPT) $(MCCFLAGS) $(GNUFLAGS)
OBJDIR    = ./obj
CSOURCES  = auxiliary.c \
            reinitdistlabels.c \
            heaps.c \
            GoldbergTarjan.c \
            PadbergRinaldi.c \
            mincut.c \
            initdistlabels.c \
            PadbergRinaldiPrep.c

OBJECTS   = $(CSOURCES:.c=.o)

all: lala

lala: $(OBJECTS)
	g++ -DSYSV -DMCC_DOUBLE -DLINUX -O3 -Wall -fPIC -fno-strict-aliasing -DIL_STD -std=c++14 -Wno-reorder -Wno-ignored-attributes -c SEC.c -o SEC.o
	g++ auxiliary.o reinitdistlabels.o heaps.o GoldbergTarjan.o PadbergRinaldi.o mincut.o initdistlabels.o PadbergRinaldiPrep.o -shared -o SEC.so -fPIC SEC.o

clean:
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -f $(TARGET) $(wildcard *.so)

%.o: %.c
	$(CC) $(CFLAGS) -c $<
	
