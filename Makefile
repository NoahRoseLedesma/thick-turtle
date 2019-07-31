CXX		:= g++
CXXFLAGS	:= -Wall -Werror -Wextra -Werror
LDFLAGS		:=
BUILD_DIR	:= ./bin
OBJ_DIR		:= $(BUILD_DIR)/obj
TARGET		:= thick_turtle
INCLUDE_DIR	:= -Iinclude/
SRC		:= $(wildcard src/*.cc)
OBJECTS		:= $(SRC:%.cc=$(OBJ_DIR)/%.o)

all: build $(BUILD_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cc
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) -o $@ -c $<

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIR) $(LDFLAGS) -o $(BUILD_DIR)/$(TARGET) $(OBJECTS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)
	-@rm -v $(BUILD_DIR)/*
