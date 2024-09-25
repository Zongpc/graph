CC:=x86_64-linux-gnu-gcc
KEY_COMP=$(shell echo $(CC) | sed 's/...$$//')
CXX?=$(KEY_COMP)g++
OBJDUMP?=$(KEY_COMP)objdump
CFLAGS=-static
LDFLAGS?= 
SRC_DIR=.
SOURCES_C:= $(wildcard $(SRC_DIR)/*.c)
SOURCES_CPP= $(wildcard $(SRC_DIR)/*.cpp)
EXEC?=graph
DISASM= $(EXEC).asm

all: clean $(EXEC) $(DISASM)

$(EXEC): $(SOURCES_C) $(SOURCES_CPP)
	$(CC) $(CFLAGS) -o $(EXEC) $(SOURCES_C) $(SOURCES_CPP) $(LDFLAGS)

$(DISASM): $(EXEC)
	$(OBJDUMP) -d $(EXEC) > $(DISASM)

clean:
	rm -f $(EXEC) $(DISASM)