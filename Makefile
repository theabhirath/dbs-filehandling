MKDIR   := mkdir -p
RMDIR   := rm -rf
CC      := gcc
BIN     := ./bin
OBJ     := ./obj
INCLUDE := ./include
SRC     := ./src
SRCS    := $(wildcard $(SRC)/*.c)
OBJS    := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
EXE     := $(BIN)/main.exe
CFLAGS  := -I$(INCLUDE)
LDLIBS  := -lm

.PHONY: all run clean

all: $(EXE)

$(EXE): $(OBJS) $(VISOBJS) | $(BIN)
	$(CC) $^ -o $@ $(LDLIBS) 

$(OBJ)/%.o: $(SRC)/%.c | $(OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN) $(OBJ):
	$(MKDIR) $@

clean:
	$(RMDIR) $(OBJ) $(BIN)