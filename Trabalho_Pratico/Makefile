SHELL = /bin/sh

BIN_NAME = calor

CXX = gcc
LD  = gcc

#CXX = icpc
#LD  = icpc

#-fopenmp/-openmp for GNU/Intel

CXXFLAGS   = -O3 -fopenmp -Wall -Wextra -std=c99 -Wno-unused-parameter #-vec-report3

ifeq ($(DEBUG),yes)
        CXXFLAGS += -ggdb3
endif

ifeq ($(SEQUENTIAL),yes)
        CXXFLAGS += -DD_SEQUENTIAL
endif

ifeq ($(PARALLEL),yes)
        CXXFLAGS += -DD_PARALLEL
endif

################################################################################
# Control awesome stuff
################################################################################

SRC_DIR = src
BIN_DIR = bin
BUILD_DIR = build
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))
DEPS = $(patsubst build/%.o,build/%.d,$(OBJ))
BIN = $(BIN_NAME)

vpath %.c $(SRC_DIR)

################################################################################
# Rules
################################################################################

.DEFAULT_GOAL = all

$(BUILD_DIR)/%.d: %.c
        $(CXX) -M $(CXXFLAGS) $(INCLUDES) $< -o $@ -lpthread

$(BUILD_DIR)/%.o: %.c
        $(CXX) -c $(CXXFLAGS) $(INCLUDES) $< -o $@ -lpthread

$(BIN_DIR)/$(BIN_NAME): $(DEPS) $(OBJ)
        $(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $(OBJ) -lpthread

checkdirs:
        @mkdir -p $(BUILD_DIR)
        @mkdir -p $(BIN_DIR)

all: checkdirs $(BIN_DIR)/$(BIN_NAME)

clean:
        rm -f $(BUILD_DIR)/* $(BIN_DIR)/*