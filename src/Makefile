CC?=x86_64-linux-gnu-gcc
CXX?=x86_64-linux-gnu-g++
OBJDUMP?=x86_64-linux-gnu-objdump
CFLAGS=-static
LDFLAGS?= 
SRC_DIR=.
SOURCES_C:= $(wildcard $(SRC_DIR)/*.c)
SOURCES_CPP= $(wildcard $(SRC_DIR)/*.cpp)
EXEC?=graph
DISASM= $(EXEC).asm

all: $(EXEC) $(DISASM)

$(EXEC): $(SOURCES_C) $(SOURCES_CPP)
	$(CC) $(CFLAGS) -o $(EXEC) $(SOURCES_C) $(SOURCES_CPP) $(LDFLAGS)

$(DISASM): $(EXEC)
	$(OBJDUMP) -d $(EXEC) > $(DISASM)

clean:
	rm -f $(EXEC) $(DISASM)