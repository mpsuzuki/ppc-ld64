PREFIX ?= /opt/local
CXX = clang++ -std=c++11
# CXX = clang++ -std=c++03
CC = clang

# CCTOOLS = ../cctools-795
# CCTOOLS_INCLUDES = -I$(CCTOOLS)/include
CCTOOLS_INCLUDES = -I$(PREFIX)/include/ppc-cctools

# LLDB = ../lldb
# UNWIND = $(LLDB)/source/Plugins/Process/Utility/libunwind/
# UNWIND_INCLUDES = -I$(UNWIND)/include -I$(UNWIND)/src
UNWIND_INCLUDES = -I$(PREFIX)/include/ppc-libunwind

INCLUDES = \
	$(CCTOOLS_INCLUDES) $(UNWIND_INCLUDES) \
	-Isrc/ld -Isrc/abstraction

DEFINES = \
	-DSUPPORT_ARCH_i386 -DSUPPORT_ARCH_x86_64 \
	-DSUPPORT_ARCH_ppc -DSUPPORT_ARCH_ppc64

OPTFLAGS = -O0
DEBUGFLAGS = -g0

LDFLAGS ?=
LIBS ?=

SRCS_CPP = $(wildcard src/ld/*.cpp)
SRCS_C = $(wildcard src/ld/*.c)
OBJS = $(SRCS_CPP:.cpp=.o) $(SRCS_C:.c=.o)

all: ld libprune_trie.a

%.o: %.c
	$(CC) $(OPTFLAGS) $(DEBUGFLAGS) $(DEFINES) $(INCLUDES) \
		$(CFLAGS) -c $< -o $@

%.o: %.cpp
	$(CXX) $(OPTFLAGS) $(DEBUGFLAGS) $(DEFINES) $(INCLUDES) \
		$(CXXFLAGS) -c $< -o $@

ld: $(OBJS)
	$(CXX) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)

clean:
	rm -f $(OBJS) ld
	rm -f PruneTrie.o libprune_trie.a

install: ld
	mkdir -p $(DESTDIR)$(PREFIX)/bin
	install -m 755 ld $(DESTDIR)$(PREFIX)/bin/ld64

libprune_trie.a: PruneTrie.o
	$(AR) $(ARFLAGS) $@ $^

PruneTrie.o: src/other/PruneTrie.cpp
	$(CXX) $(OPTFLAGS) $(DEBUGFLAGS) $(DEFINES) $(INCLUDES) \
		$(CXXFLAGS) -Isrc/other -o $@ -c $<

install-prune-trie: libPruneTrie.a
	mkdir -p $(DESTDIR)$(PREFIX)/include/ppc-ld64/
	install -m 744 src/other/prune_trie.h $(DESTDIR)$(PREFIX)/include/ppc-ld64/
	mkdir -p $(DESTDIR)$(PREFIX)/libexec/ppc-ld64/
	install -m 744 libPruneTrie.a $(DESTDIR)$(PREFIX)/libexec/ppc-ld64/
