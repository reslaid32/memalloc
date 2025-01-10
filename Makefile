CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0
LDFLAGS = 

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
TEST_DIR = test

SRCS = $(SRC_DIR)/mm.c $(SRC_DIR)/syscallapi.s
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(filter %.c, $(SRCS))) \
       $(patsubst $(SRC_DIR)/%.s, $(BUILD_DIR)/%.o, $(filter %.s, $(SRCS)))
TARGET = $(BUILD_DIR)/libmemalloc.so

TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SRCS))
TEST_TARGET = $(BUILD_DIR)/test_suite

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJS)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -shared -o $@ $(OBJS) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

# Using GAS
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJS) $(OBJS)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -o $@ $(TEST_OBJS) $(OBJS)

$(BUILD_DIR)/%.o: $(TEST_DIR)/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

.PHONY: all clean test
