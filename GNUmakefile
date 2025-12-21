CXX = clang++ -std=c++11
# CXX = clang++ -std=c++03
CC = clang

LLDB = ../lldb
UNWIND = $(LLDB)/source/Plugins/Process/Utility/libunwind/
CCTOOLS  = ../cctools-795
INCLUDES = \
	-I$(CCTOOLS)/include \
	-I$(UNWIND)/include -I$(UNWIND)/src \
	-Isrc/ld -Isrc/abstraction

CXXFLAGS = -O0 -g0 $(INCLUDES) \
	-DSUPPORT_ARCH_i386 -DSUPPORT_ARCH_x86_64 \
	-DSUPPORT_ARCH_ppc -DSUPPORT_ARCH_ppc64

CFLAGS = -O0 -g0 $(INCLUDES) \
	-DSUPPORT_ARCH_i386 -DSUPPORT_ARCH_x86_64 \
	-DSUPPORT_ARCH_ppc -DSUPPORT_ARCH_ppc64

LDFLAGS =

SRCS_CPP = $(wildcard src/ld/*.cpp)
SRCS_C = $(wildcard src/ld/*.c)
OBJS = $(SRCS_CPP:.cpp=.o) $(SRCS_C:.c=.o)

all: ld libprune_trie.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

ld: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f $(OBJS) ld
	rm -f PruneTrie.o libprune_trie.a

libprune_trie.a: PruneTrie.o
	$(AR) $(ARFLAGS) $@ $^

PruneTrie.o: src/other/PruneTrie.cpp
	$(CXX) $(CXXFLAGS) -Isrc/other -o $@ -c $<
