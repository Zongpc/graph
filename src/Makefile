CC:=x86_64-linux-gnu-gcc
X86CC:=x86_64-linux-gnu-gcc
ARM64CC:=aarch64-linux-gnu-gcc
KEY_COMP=$(shell echo $(CC) | sed 's/...$$//')
CXX?=$(KEY_COMP)g++
OBJDUMP?=$(KEY_COMP)objdump
CFLAGS=-static -O3
LDFLAGS?=-D USEM5
LIBS?=-I../../gem5_study/include -L../../gem5_study/util/m5/build/arm64/out -lm5 -lpthread -lm 
SRC_DIR=.
SOURCES_C:= $(wildcard $(SRC_DIR)/*.c)
SOURCES_CPP= $(wildcard $(SRC_DIR)/*.cpp)
EXEC?=graph
DISASM= $(EXEC).asm

all: clean $(EXEC) $(DISASM)
	@echo "****************************************************************************************"
	@echo "*If you need cross compile to target arm64 use command: make CC=\"aarch64-linux-gnu-gcc\"*"
	@echo "*Default target is x86_64                                                              *"
	@echo "****************************************************************************************"

$(EXEC): $(SOURCES_C) $(SOURCES_CPP)
ifeq ($(CC),$(ARM64CC))
	$(CC) $(CFLAGS) -o $(EXEC) $(SOURCES_C) $(SOURCES_CPP) $(LDFLAGS) $(LIBS)
else ifeq ($(CC),$(X86CC))
	$(CC) $(CFLAGS) -o $(EXEC) $(SOURCES_C) $(SOURCES_CPP) 
endif

$(DISASM): $(EXEC)
	$(OBJDUMP) -d -S $(EXEC) > $(DISASM)

clean:
	rm -f $(EXEC) $(DISASM)