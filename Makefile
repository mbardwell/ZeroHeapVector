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
	@echo "\033[0;32mBuilding Library\033[0m"
	ar rcs $@ $^

$(EXAMPLE): $(EXAMPLE_OBJECTS) $(LIBRARY)
	@echo "\033[0;32mCompiling\033[0m"
	$(CXX) $(CXXFLAGS) -o $@ $^

stats: $(EXAMPLE)
	@echo "\033[0;32mStats\033[0m"
	@size $(EXAMPLE)
	@# Output the stack usage. Requires -fstack-usage to be enabled.
	@echo -n "Stack usage: " && grep "main" $(EXAMPLE).su

static: $(EXAMPLE)
	@echo "\033[0;32mStatic Analysis\033[0m"
	clang-tidy $(EXAMPLE_SOURCES) --
	cppcheck --enable=all --inconclusive --suppress=missingIncludeSystem --std=$(CXXSTANDARD) --language=c++ $(EXAMPLE_SOURCES)
	valgrind --tool=callgrind --dump-instr=yes --collect-jumps=yes --simulate-cache=yes --collect-systime=yes ./$(EXAMPLE)

clean:
	@echo "\033[0;32mCleaning\033[0m"
	rm -f $(OBJECTS) $(EXAMPLE_OBJECTS) $(LIBRARY) $(EXAMPLE)
