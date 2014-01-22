# source files.
SRC = networkmessage.cpp network.cpp

OBJDIR = obj

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

OUTDIR = lib

OUT = $(OUTDIR)/librobotnetworking.a

# include directories
INCLUDES = -I./ -I./include -I/usr/local/include

# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -g -Wall

# compiler
CCC = g++

# library paths
LIBS = -L./ -L/usr/local/lib -lm

# compile flags
LDFLAGS = -g

.SUFFIXES: .cpp

default: prepare $(OUT)

$(OBJDIR)/%.o: %.cpp makefile
	$(CCC) $(INCLUDES) $(CCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ)
	
depend: .depend

.depend: $(SRC)
	rm -f ./.depend
	$(CCC) $(INCLUDES) $(CCFLAGS) -MM $^>>./.depend;

include .depend

prepare:
	mkdir -p $(OBJDIR)
	mkdir -p $(OUTDIR)
clean:
	rm -f $(OBJ) $(OUT) Makefile.bak 
	
rebuild: clean default
