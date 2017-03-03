#
# Autoconfig makefile
# Copyright by Piotr Styczyński (2017)
# MIT License
#
# Use:
#  Create build.config file / file by default should look like this:
#
#  PROJECT_DESCR  := Some compilable project in C/C++
#  PEFFERED_CC  := GCPP
#  SUPPORT_GCC   := null
#  SUPPORT_GCPP  := -std=c++11 -O3 -w -I./include
#  SUPPORT_CLANG := null
#
# For null keys compiler is marked as non-supporting project builds.
# For the rest SUPPORT_* flags are applied to the compiler autoconfigured path
#
# If you want to manipulate specific compile functions you can decalre
# also:
#
# CC_SEL_GEN_O := $$(CC) -c -o $$@ $$<
# CC_SEL_GEN_EXE := $$(CC) -o $$@ $$<
#
# The make file creates _autoconf_.config file with the autoconfigured flags and compiler path
# If this config don't work dor you, just edit _autoconf_ file.
#
#

ECHO := @

include build.config

TGTCC_AVCC=
TGTCC_AVCC_SIZE=0
CC_GC_VERSION=$(shell gcc -dumpversion 2> /dev/null || echo "")
CC_GCPP_VERSION=$(shell g++ -dumpversion 2> /dev/null || echo "")
CC_CLANG_VERSION=$(shell g++ -dumpversion 2> /dev/null || echo "")

CC_SEL=null
CC_SEL_FLAGS=
CC_SEL_GEN_O=
CC_SEL_GEN_EXE=
CC_SUP_GCC=false
CC_SUP_GCPP=false
CC_SUP_CLANG=false
CC_SUP_ANY=

COM_AUTOCONF1=
COM_AUTOCONF2=
COM_PREP_DIR1=
COM_PREP_DIR2=

RUN_AUTOCONF=false
ifneq (,$(filter config,$(MAKECMDGOALS)))
RUN_AUTOCONF=true
endif
ifeq (,$(wildcard _autoconf_.config))
RUN_AUTOCONF=true
endif

ifeq (true,$(RUN_AUTOCONF))

ifneq (,$(CC_GC_VERSION))
ifeq (,$(CC_SUP_ANY))
CC_SUP_ANY:=GCC
endif
ifneq (null,$(SUPPORT_GCC))
$(info [Compiler autoconf] gcc version detected $(CC_GC_VERSION)   [SUPPORTED])
TGTCC_AVCC:=$(TGTCC_AVCC)$$(($(TGTCC_AVCC_SIZE)+1)).) gcc ($(CC_GC_VERSION))\\n
TGTCC_AVCC_SIZE:=$$(($(TGTCC_AVCC_SIZE)+1))
CC_SUP_GCC=true
else
$(info [Compiler autoconf] gcc version detected $(CC_GC_VERSION)   [no support])
endif
endif

ifneq (,$(CC_GCPP_VERSION))
ifeq (,$(CC_SUP_ANY))
CC_SUP_ANY:=GCPP
endif
ifneq (null,$(SUPPORT_GCPP))
$(info [Compiler autoconf] g++ version detected $(CC_GCPP_VERSION)   [SUPPORTED])
TGTCC_AVCC:=$(TGTCC_AVCC)$$(($(TGTCC_AVCC_SIZE)+1)).) g++ ($(CC_GCPP_VERSION)) \\n
TGTCC_AVCC_SIZE:=$$(($(TGTCC_AVCC_SIZE)+1))
CC_SUP_GCPP=true
else
$(info [Compiler autoconf] g++ version detected $(CC_GCPP_VERSION)   [no support])
endif
endif

ifneq (,$(CC_CLANG_VERSION))
ifeq (,$(CC_SUP_ANY))
CC_SUP_ANY:=CLANG
endif
ifneq (null,$(SUPPORT_CLANG))
$(info [Compiler autoconf] clang version detected $(CC_CLANG_VERSION)   [SUPPORTED])
TGTCC_AVCC:=$(TGTCC_AVCC)$$(($(TGTCC_AVCC_SIZE)+1)).) clang ($(CC_CLANG_VERSION))\\n
TGTCC_AVCC_SIZE:=$$(($(TGTCC_AVCC_SIZE)+1))
CC_SUP_CLANG=true
else
$(info [Compiler autoconf] clang version detected $(CC_CLANG_VERSION)   [no support])
endif
endif


ifeq (true,$$( CC_SUP_$(PREFFERED_CC) ))
$(info [Compiler autoconf] Selected preffered compiler: $(PREFFERED_CC))
CC_SEL:=$(PREFFERED_CC)
CC_SEL_FLAGS:=$()
else
$(info [Compiler autoconf] No preffered compiler available. Selecting any other.)
ifeq (true,$(CC_SUP_GCC))
$(info [Compiler autoconf] Selecting available compiler: gcc)
CC_SEL:=GCC
else
ifeq (true,$(CC_SUP_GCPP))
$(info [Compiler autoconf] Selecting available compiler: g++)
CC_SEL:=GCPP
else
ifeq (true,$(CC_SUP_CLANG))
$(info [Compiler autoconf] Selecting available compiler: clang)
CC_SEL:=CLANG
else
$(info [Compiler autoconf] No available compiler to compile the code!)
ifeq (,$(CC_SUP_ANY))
$(info Autoconf detected youve got no suitable compiler.)
$(info You have to compile the code manually.)
$(error No suitable compiler detected.)
else
$(info Autoconf detected youve got a suitable compiler.)
$(info Please change SUPPORT_$(CC_SUP_ANY) to flags for $(CC_SUP_ANY) compiler.)
$(info Then redo make command.)
$(error No support for $(CC_SUP_ANY) compiler.)
endif

endif
endif
endif
endif

ifeq (GCC,$(CC_SEL))
CC_SEL:=gcc
CC_SEL_FLAGS:=$(SUPPORT_GCC)
CC_SEL_GEN_O:=$(SUPPORT_GCC_GEN_O)
CC_SEL_GEN_EXE:=$(SUPPORT_GCC_GEN_EXE)
endif
ifeq (GCPP,$(CC_SEL))
CC_SEL:=g++
CC_SEL_FLAGS:=$(SUPPORT_GCPP)
CC_SEL_GEN_O:=$(SUPPORT_GCPP_GEN_O)
CC_SEL_GEN_EXE:=$(SUPPORT_GCPP_GEN_EXE)
endif
ifeq (CLANG,$(CC_SEL))
CC_SEL:=clang
CC_SEL_FLAGS:=$(SUPPORT_CLANG)
CC_SEL_GEN_O:=$(SUPPORT_CLANG_GEN_O)
CC_SEL_GEN_EXE:=$(SUPPORT_GCPP_GEN_EXE)
endif

ifeq (,$(CC_SEL_GEN_O))
CC_SEL_GEN_O:=\$$\$$(CC) -c -o \$$\$$@ \$$\$$<
endif
ifeq (,$(CC_SEL_GEN_EXE))
CC_SEL_GEN_EXE:=\$$\$$(CC) -o \$$\$$@ \$$\$$<
endif

COM_AUTOCONF1:=@printf "\#\n\# Autoconfig makefile\n\# Edit only if your compiler is not supported\n\#\n\n\n\# Compiler executable path:\nCC_SEL := $(CC_SEL)\n\n\# Compiler flags:\nCC_SEL_FLAGS := $(CC_SEL_FLAGS)\n\n\# Compiler intruction for building object files:\nCC_SEL_GEN_O := $(CC_SEL_GEN_O)\n\n\# Compiler intruction for building executable files:\nCC_SEL_GEN_EXE := $(CC_SEL_GEN_EXE)" > _autoconf_.config
COM_AUTOCONF2:=@echo Autoconf file was created.

CC_SEL_GEN_O:=$(subst \,,$(CC_SEL_GEN_O))
CC_SEL_GEN_EXE:=$(subst \,,$(CC_SEL_GEN_EXE))

CC_SEL_GEN_O:=$(subst $$$$,$$,$(CC_SEL_GEN_O))
CC_SEL_GEN_EXE:=$(subst $$$$,$$,$(CC_SEL_GEN_EXE))

else

include _autoconf_.config
$(info Using compiler from autoconfig file ($(CC_SEL)))

#$(error FY)

endif


CC := $(ECHO)$(CC_SEL) $(CC_SEL_FLAGS)
EXAMPLES_FILES := $(wildcard ./examples/src/*.cpp)
EXAMPLES_FILES_LIST := $(addprefix ,$(notdir $(EXAMPLES_FILES:.cpp=)))
EXAMPLES_OBJ_FILES := $(addprefix ./examples/bin/,$(notdir $(EXAMPLES_FILES:.cpp=.o)))
EXAMPLES_EXE_FILES := $(addprefix ./examples/bin/,$(notdir $(EXAMPLES_FILES:.cpp=.exe)))
EXAMPLES_BUILT_FILES := $(addprefix ./examples/bin/,$(notdir $(wildcard ./examples/bin/*)))
EXAMPLES_NUMBER := $(words $(EXAMPLES_FILES))
EXAMPLES_MADE_NUMBER := %


ifeq (,$(wildcard ./examples/bin))
COM_PREP_DIR1=@mkdir ./examples/bin
COM_PREP_DIR2=@echo Prepared needed directories.
endif


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
	$(info )
	$(info )
	$(info $(PROJECT_DESCR))
	$(info )
	$(info Autoconf makefile by Piotr Styczynski <MIT>)
	$(info )
	$(info To compile all examples use 'make all' or 'make examples' command)
	$(info To get list of all available examples use 'make run-example' command)
	$(info To run the specified example use 'make run-example-NAME' e.g. 'make run-example-demo')
	$(info To clean project use 'make clean' command)
	$(info )
	$(info )
	$(info )
	$(info )

config: init

init:
	$(COM_AUTOCONF1)
	$(COM_AUTOCONF2)
	$(COM_PREP_DIR1)
	$(COM_PREP_DIR2)

rebuild: init clean-all examples

clean: clean-all
	$(info Project cleaned. Done)

clean-all: clean-examples

all: init examples

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

define make-tgt-o
./examples/bin/%.o: ./examples/src/%.cpp
	$$(info Compiling example: $$<)
	$(CC_SEL_GEN_O)

./examples/bin/%.o: ./examples/src/%.c
	$$(info Compiling example: $$<)
	$(CC_SEL_GEN_O)
endef

define make-tgt-exe
./examples/bin/%.exe: ./examples/bin/%.o
	$(CC_SEL_GEN_EXE)
endef


$(eval $(call make-tgt-o))
$(eval $(call make-tgt-exe))
