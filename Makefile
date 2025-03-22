CC = g++
CFLAGS = -Wall -g # -Wall enables all warnings, -g adds debugging information
LDFLAGS = 
TESTFLAGS = -DTEST_MODE

# Source files and object files
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)

MAIN_EXEC = main
TEST_EXEC = test

# Default target
all: $(MAIN_EXEC)

# Compile main.cpp normally
$(MAIN_EXEC):
	$(CC) $(CFLAGS) main.cpp -o $(MAIN_EXEC)

# Compile object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
# $(MAIN_EXEC): $(OBJECTS)
# 	$(CC) $(LDFLAGS) $^ -o $@

$(TEST_EXEC): $(SOURCES)
	$(CC) $(TESTFLAGS) $(SOURCES) -o $(TEST_EXEC)

# Run programs
run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

run_test: $(TEST_EXEC)
	./$(TEST_EXEC)

# Clean build artifacts 
clean:
	del $(wildcard *.exe) $(wildcard *.o)