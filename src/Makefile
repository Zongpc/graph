CC:=x86_64-linux-gnu-gcc
X86CC:=x86_64-linux-gnu-gcc
ARM64CC:=aarch64-linux-gnu-gcc
KEY_COMP=$(shell echo $(CC) | sed 's/...$$//')
CXX?=$(KEY_COMP)g++
OBJDUMP?=$(KEY_COMP)objdump
CFLAGS=-static -O1 
OPERATION?=BFS #BFS or PRIM or SSSP
OPERATION_LOW:=$(shell echo $(OPERATION) | tr 'A-Z' 'a-z')
LDFLAGS?=-D USEM5
LIBS?=-I../../gem5_study/include -L../../gem5_study/util/m5/build/arm64/out -lm5 -lpthread -lm 
SRC_DIR=.
POSTFIX?=
SOURCES_C:= $(wildcard $(SRC_DIR)/*.c)
#SOURCES_CPP= $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SOURCES_C:.c=.o)

ifeq ($(CC),$(ARM64CC))
	PLATFORM=aarch64
else ifeq ($(CC),$(X86CC))
	PLATFORM=x86
endif

EXEC?=graph_$(PLATFORM)_$(OPERATION_LOW)${POSTFIX}
DISASM= $(EXEC).asm
OPERATION:= $(strip $(OPERATION))

#check_var:
#ifeq ($(filter $(OPERATION),BFS PRIM SSSP),)
#	$(error Variable OPERATION must be either 'BFS'\(default\), 'PRIM', or 'SSSP')
#endif


all: clean $(EXEC) $(DISASM)
	@echo "                                                                 "
	@echo "INFO \"PLATFORM: ${PLATFORM},  OPERATION: ${OPERATION}\" "
	@echo "                                                                 "
	mv $(EXEC) ./output/
	mv $(DISASM) ./output/
	@echo "****************************************************************************************************************"
	@echo "* If you need cross compile PRIM to target arm64 use command: make CC=\"aarch64-linux-gnu-gcc\" OPERATION=\"PRIM\" *"
	@echo "* Default target is x86_64, default OPERATION is BFS                                                           *"
	@echo "****************************************************************************************************************"

#$(EXEC): $(SOURCES_C) $(SOURCES_CPP)
#ifeq ($(CC),$(ARM64CC))
#	$(CC) $(CFLAGS) -o $(EXEC) $(SOURCES_C) $(SOURCES_CPP) $(LDFLAGS) $(LIBS)
#else ifeq ($(CC),$(X86CC))
#	$(CC) $(CFLAGS) -o $(EXEC) $(SOURCES_C) $(SOURCES_CPP) 
#endif

$(DISASM): $(EXEC)
	$(OBJDUMP) -d -S $(EXEC) > $(DISASM)

# 链接目标
$(EXEC): $(OBJS)
ifeq ($(CC),$(ARM64CC))
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
else ifeq ($(CC),$(X86CC))
	$(CC) $(CFLAGS) -o $@ $^
endif

# 编译源文件为对象文件
%.o: %.c
ifeq ($(CC),$(ARM64CC))
	$(CC) $(CFLAGS) -c $< -o $@ -D $(OPERATION) $(LDFLAGS) $(LIBS)
else ifeq ($(CC),$(X86CC))
	$(CC) $(CFLAGS) -c $< -o $@ -D $(OPERATION)
endif

clean:
	rm -f $(EXEC) $(DISASM) *.o