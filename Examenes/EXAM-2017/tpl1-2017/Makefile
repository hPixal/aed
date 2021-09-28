# -*- mode: makefile -*-
## GITVERSION: aed-3.1-44-g8bbf219a
CPP := util_btree.cpp,util.cpp,util_tree.cpp
HPP := eval.hpp util.hpp util_tree.hpp tree.hpp util_btree.hpp 
SRCS := $(CPP) $(HPP)
.PHONY: force
program.bin: force
	g++ -I. -std=gnu++11 -g3 -O0 -o $@ program.cpp aedtools/{$(CPP)}

check:
	$(MAKE) program.bin
	./program.bin
