CXX = g++
CXXSTANDARD = c++23
CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -std=$(CXXSTANDARD) -fstack-usage -Wstack-usage=2048
ifdef SIZE
CXXFLAGS += -DSIZE=$(SIZE)
endif

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
	size $(EXAMPLE)
	@# Output the stack usage. Requires -fstack-usage to be enabled.
	cat $(EXAMPLE).su

static: $(EXAMPLE)
	clang-tidy $(EXAMPLE_SOURCES) --
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --std=$(CXXSTANDARD) --language=c++ $(EXAMPLE_SOURCES)
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes --simulate-cache=yes --collect-systime=yes ./$(EXAMPLE)

clean:
	rm -f $(OBJECTS) $(EXAMPLE_OBJECTS) $(LIBRARY) $(EXAMPLE)
