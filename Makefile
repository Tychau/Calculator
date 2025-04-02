# Compiler
CC = g++

# Compiler flags
CFLAGS = -Wall -g
TESTFLAGS = -DTEST_MODE

# Boost header path
BOOST_INCLUDE = C:/Users/Vangay/OneDrive/Desktop/CodeFiles/boost_1_87_0

# Executable names
MAIN_EXEC = main
TEST_EXEC = test
BOOST_TEST_EXEC = boost_test

# Source files
MAIN_SRC = main.cpp
TEST_SRC = $(MAIN_SRC)
BOOST_TEST_SRC = boost_test.cpp $(MAIN_SRC)

# Default target
all: $(MAIN_EXEC)

# --- Build targets ---

# Build main program
$(MAIN_EXEC): $(MAIN_SRC)
	$(CC) $(CFLAGS) -I$(BOOST_INCLUDE) $(MAIN_SRC) -o $(MAIN_EXEC)

# Build your custom test program
$(TEST_EXEC): $(TEST_SRC)
	$(CC) $(CFLAGS) $(TESTFLAGS) -I$(BOOST_INCLUDE) $(TEST_SRC) -o $(TEST_EXEC)

# Build Boost test program (exclude main() by defining TEST_MODE)
$(BOOST_TEST_EXEC): $(BOOST_TEST_SRC)
	$(CC) $(CFLAGS) -DTEST_MODE -I$(BOOST_INCLUDE) $(BOOST_TEST_SRC) -o $(BOOST_TEST_EXEC)

# --- Run targets ---

run: $(MAIN_EXEC)
	./$(MAIN_EXEC)

run_test: $(TEST_EXEC)
	./$(TEST_EXEC)

run_boost_test: $(BOOST_TEST_EXEC)
	./$(BOOST_TEST_EXEC)

# Clean build artifacts 
clean:
	del $(wildcard *.exe) $(wildcard *.o)