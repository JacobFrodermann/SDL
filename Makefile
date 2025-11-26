# tool macros
DBGFLAGS = -g


COBJFLAGS=-c -O2 -Wall -I/usr/include/SDL3 -D_REENTRANT -g 

CFLAGS= -L /usr/local/lib/ -L/usr/lib -lsharpyuv -ljxl -lyuv -lSDL3 -lSDL3_image -lspdlog -lfmt -std=c++17

CC=g++

# path macros
BIN_PATH := bin
OBJ_PATH := obj
SRC_PATH := src
DBG_PATH := debug

# compile macros
TARGET_NAME := AsteroidShooter

ifeq ($(OS),Windows_NT)
	TARGET_NAME := $(addsuffix .exe,$(TARGET_NAME))
endif

TARGET := $(BIN_PATH)/$(TARGET_NAME)
TARGET_DEBUG := $(DBG_PATH)/$(TARGET_NAME)

# src files & obj files
SRC := $(shell find $(SRC_PATH) -type f -name '*.cpp')

OBJ := $(patsubst $(SRC_PATH)/%.cpp, $(OBJ_PATH)/%.o, $(SRC))

OBJ_DEBUG := $(patsubst $(SRC_PATH)/%.cpp, $(DBG_PATH)/%.o, $(SRC))


# clean files list
DISTCLEAN_LIST := $(OBJ) \
                  $(OBJ_DEBUG)

CLEAN_LIST := $(TARGET) \
			  $(TARGET_DEBUG) \
			  $(DISTCLEAN_LIST)

# default rule
default: makedir all

# non-phony targets
$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(CFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	@mkdir -p $(dir $@)
	$(CC) $(COBJFLAGS) -o $@ $<

$(DBG_PATH)/%.o: $(SRC_PATH)/%.c*
	@mkdir -p $(dir $@)
	$(CC) $(COBJFLAGS) $(DBGFLAGS) -o $@ $<

$(TARGET_DEBUG): $(OBJ_DEBUG)
	$(CC) $(CFLAGS) $(DBGFLAGS) $(OBJ_DEBUG) -o $@

# phony rules
.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH) $(DBG_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: debug
debug: $(TARGET_DEBUG)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)

.PHONY: distclean
distclean:
	@echo CLEAN $(DISTCLEAN_LIST)
	@rm -f $(DISTCLEAN_LIST)

.PHONY: run
run: all
	./bin/AsteroidShooter