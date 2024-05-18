# Daniel Tsadik
# ID: 209307727
# Mail: tsadik88@gmail.com

# Compiler and compiler flags
CXX = clang++
CXXFLAGS = -std=c++11 -Werror -Wsign-conversion

# Valgrind flags for memory check
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=99

# Source files and corresponding object files
SOURCES = Graph.cpp Algorithms.cpp
OBJECTS = $(subst .cpp,.o,$(SOURCES))

# Default target to run tests
run: test
	./$^

# Target to build and run the demo program
demo: Demo.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o demo

# Target to build and run the test suite
test: TestCounter.o Test.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o test

# Target to run clang-tidy with specific checks
tidy:
	clang-tidy $(SOURCES) -checks=bugprone-*,clang-analyzer-*,cppcoreguidelines-*,performance-*,portability-*,readability-*,-cppcoreguidelines-pro-bounds-pointer-arithmetic,-cppcoreguidelines-owning-memory --warnings-as-errors=-* --

# Target to run valgrind memory check on demo and test programs
valgrind: demo test
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./demo 2>&1 | { egrep "lost| at " || true; }
	valgrind --tool=memcheck $(VALGRIND_FLAGS) ./test 2>&1 | { egrep "lost| at " || true; }

# Pattern rule to compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

# Target to clean up generated files
clean:
	rm -f *.o demo test
