CC          = gcc
CXX         = g++
OBJDIR      = obj
BINDIR      = bin
INCLUDEDIR  = .
TESTDIR     = tests

# Source files
SOURCES     = ExpressionParser.cpp Tokenizer.cpp
MAIN        = main.cpp
TEST_MAIN   = $(TESTDIR)/test_main.cpp
TEST_SOURCES = $(filter-out $(TEST_MAIN), $(wildcard $(TESTDIR)/*.cpp))

# Object files
OBJECTS     = $(SOURCES:%.cpp=$(OBJDIR)/%.o)
MAIN_OBJ    = $(OBJDIR)/main.o
TEST_OBJECTS = $(TEST_SOURCES:$(TESTDIR)/%.cpp=$(OBJDIR)/%.o)
TEST_MAIN_OBJ = $(OBJDIR)/test_main.o

# Executables
EXECUTABLE  = simplifier
TEXECUTABLE = utests

# Compiler flags
CPPFLAGS    = -std=c++14 -Wall -Werror -O3
CXXFLAGS    = $(CPPFLAGS)
LIBS        =

# Create directories
$(shell mkdir -p $(OBJDIR) $(BINDIR))

.PHONY: all clean tests

all: $(BINDIR)/$(EXECUTABLE)

# Main program
$(BINDIR)/$(EXECUTABLE): $(OBJECTS) $(MAIN_OBJ)
	$(CXX) $^ $(LIBS) -o $@

# Tests
tests: $(BINDIR)/$(TEXECUTABLE)

$(BINDIR)/$(TEXECUTABLE): $(OBJECTS) $(TEST_OBJECTS) $(TEST_MAIN_OBJ)
	$(CXX) $^ $(LIBS) -o $@

# Object files
$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: $(TESTDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)