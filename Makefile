CXX = g++
CXXSTANDARD = c++23
CXXFLAGS = -Wall -Wextra -Wpedantic -O3 -std=$(CXXSTANDARD)

LIBRARY = libstack_vector.a
SOURCES =
OBJECTS = $(SOURCES:.cpp=.o)

EXAMPLE = example
EXAMPLE_SOURCES = example.cpp
EXAMPLE_OBJECTS = $(EXAMPLE_SOURCES:.cpp=.o)

all: $(LIBRARY) $(EXAMPLE)

$(LIBRARY): $(OBJECTS)
	ar rcs $@ $^

$(EXAMPLE): $(EXAMPLE_OBJECTS) $(LIBRARY)
	$(CXX) $(CXXFLAGS) -o $@ $^

stats: $(EXAMPLE)
	ls -al $(EXAMPLE)
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes --simulate-cache=yes --collect-systime=yes ./$(EXAMPLE)

static: $(EXAMPLE)
	clang-tidy $(EXAMPLE_SOURCES) --
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --std=$(CXXSTANDARD) --language=c++ $(EXAMPLE_SOURCES)

clean:
	rm -f $(OBJECTS) $(EXAMPLE_OBJECTS) $(LIBRARY) $(EXAMPLE)
