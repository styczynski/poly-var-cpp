ECHO := @

TGTCC_GC_CEFLAGS=  hehe
TGTCC_GCPP_CEFLAGS=-pthread -lm -std=c++11 -O3 -w
TGTCC_CLANG_CEFLAGS=  hehe
TGTCC_AVCC=
TGTCC_AVCC_SIZE=0


CC_GC_VERSION=$(shell gcc -dumpversion 2> /dev/null || echo "")
CC_GCPP_VERSION=$(shell g++ -dumpversion 2> /dev/null || echo "")
CC_CLANG_VERSION=$(shell g++ -dumpversion 2> /dev/null || echo "")

define colorecho
@tput setaf 6
@echo $1
@tput sgr0
endef

ifneq (,$(filter conf init,$(MAKECMDGOALS)))

ifneq (,$(CC_GC_VERSION))
ifneq (,$(TGTCC_GC_CEFLAGS))
$(info [Compiler autoconf] gcc version detected $(CC_GC_VERSION)   [SUPPORTED])
TGTCC_AVCC:=$(TGTCC_AVCC)$$(($(TGTCC_AVCC_SIZE)+1)).) gcc ($(CC_GC_VERSION))\\n
TGTCC_AVCC_SIZE:=$$(($(TGTCC_AVCC_SIZE)+1))
else
$(info [Compiler autoconf] clang version detected $(CC_GC_VERSION)   [no support])
endif
endif

ifneq (,$(CC_GCPP_VERSION))
ifneq (,$(TGTCC_GCPP_CEFLAGS))
$(info [Compiler autoconf] g++ version detected $(CC_GCPP_VERSION)   [SUPPORTED])
TGTCC_AVCC:=$(TGTCC_AVCC)$$(($(TGTCC_AVCC_SIZE)+1)).) g++ ($(CC_GCPP_VERSION)) \\n
TGTCC_AVCC_SIZE:=$$(($(TGTCC_AVCC_SIZE)+1))
else
$(info [Compiler autoconf] clang version detected $(CC_GCPP_VERSION)   [no support])
endif
endif

ifneq (,$(CC_CLANG_VERSION))
ifneq (,$(TGTCC_CLANG_CEFLAGS))
$(info [Compiler autoconf] clang version detected $(CC_CLANG_VERSION)   [SUPPORTED])
TGTCC_AVCC:=$(TGTCC_AVCC)$$(($(TGTCC_AVCC_SIZE)+1)).) clang ($(CC_CLANG_VERSION))\\n
TGTCC_AVCC_SIZE:=$$(($(TGTCC_AVCC_SIZE)+1))
else
$(info [Compiler autoconf] clang version detected $(CC_CLANG_VERSION)   [no support])
endif
endif

endif


CC := $(ECHO)g++
CFLINKS :=
CEFLAGS_DEBUG := -pthread -lm -std=c++11 -O2 -Wall -W -Wextra -Wdouble-promotion -pedantic -Wmissing-include-dirs -Wunused -Wuninitialized -Wextra -Wstrict-overflow=3 -Wtrampolines -Wfloat-equal -Wconversion -Wmissing-field-initializers -Wno-multichar -Wpacked -Winline -Wshadow
CEFLAGS_RELEASE := -pthread -lm -std=c++11 -O3 -w
CEFLAGS := $(CEFLAGS_RELEASE)
EXAMPLES_FILES := $(wildcard ./examples/src/*.cpp)
EXAMPLES_FILES_LIST := $(addprefix ,$(notdir $(EXAMPLES_FILES:.cpp=)))
EXAMPLES_OBJ_FILES := $(addprefix ./examples/bin/,$(notdir $(EXAMPLES_FILES:.cpp=.o)))
EXAMPLES_EXE_FILES := $(addprefix ./examples/bin/,$(notdir $(EXAMPLES_FILES:.cpp=.exe)))
EXAMPLES_BUILT_FILES := $(addprefix ./examples/bin/,$(notdir $(wildcard ./examples/bin/*)))
EXAMPLES_NUMBER := $(words $(EXAMPLES_FILES))
EXAMPLES_MADE_NUMBER := %

CC_FLAGS=-I./include $(CEFLAGS)
LF_FLAGS=$(CFLINKS)

$(mkdir ./examples/bin)


ifneq (,$(findstring run-example-,$(MAKECMDGOALS)))
RUN_EXAMPLE_NAME=$(subst run-example-,,$(MAKECMDGOALS))
RUN_EXAMPLE_PATH=./examples/bin/$(RUN_EXAMPLE_NAME).exe
ifneq ("$(wildcard $(RUN_EXAMPLE_PATH))","")
else
$(error Cannot run an example if the examples weren't built. Run 'make examples' command firstly)
endif
endif

ifneq (,$(filter clean clean-all,$(MAKECMDGOALS)))
ifeq (,$(EXAMPLES_BUILT_FILES))
$(error Directory is clean)
endif
endif


help:
	$(info poly-vars-cpp - Polymorphic variables implementation in C++)
	$(info Makefile)
	$(info To compile all examples use 'make all' or 'make examples' command)
	$(info To get list of all available examples use 'make run-example' command)
	$(info To run the specified example use 'make run-example-NAME' e.g. 'make run-example-demo')
	$(info To clean project use 'make clean' command)

rebuild: clean-all examples

clean: clean-all
	$(info Project cleaned. Done)

clean-all: clean-examples

all: examples

examples: examples_ $(EXAMPLES_OBJ_FILES) $(EXAMPLES_EXE_FILES) clean-examples-build
	$(info Examples compiled. Done)

examples_:
	$(info $(EXAMPLES_NUMBER) examples are available)

run-example:
	$(info All available examples: $(EXAMPLES_FILES_LIST))

run-example-%:
	$(ECHO)./examples/bin/$*.exe

clean-examples:
	$(ECHO)rm $(EXAMPLES_BUILT_FILES)

clean-examples-build:
	$(info Cleaning build)
	$(ECHO)rm $(EXAMPLES_OBJ_FILES)

./examples/bin/%.exe: ./examples/bin/%.o
	$(CC) $(LF_FLAGS) -o $@ $<

./examples/bin/%.o: ./examples/src/%.cpp
	$(info Compiling example: $<)
	$(CC) $(CC_FLAGS) -c -o $@ $<

init:
	@printf "[Compiler autoconf] Which compiler do you prefer to use?\n$(TGTCC_AVCC)> "
	@read DELICIOUS_PATH
