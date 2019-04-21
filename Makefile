TARGET  := test
SRC_DIR := ../../src
OBJ_DIR := objs
BIN_DIR := bin
CC      := gcc

CFLAGS += -Wall -g 

INCS += -I.
INCS += -I$(SRC_DIR)

SRCS += file_scan.c
SRCS += common_queue.c
SRCS += main.c

OBJS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRCS))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo build $<
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $< $(DEPS) -o $@ $(INCS)
	
$(OBJ_DIR)/%.o: %.c
	@echo build $<
	@mkdir -p $(dir $@)
	@$(CC) -c $(CFLAGS) $< $(DEPS) -o $@ $(INCS)

all: $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CC) $(CFLAGS) -o $(BIN_DIR)/$(TARGET) $(OBJS) -lm
	@echo build done

.PHONY: all clean

clean:
	@rm -rf objs bin
