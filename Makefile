clocktest: Core.cxx main.cxx Core.h
	g++ -std=c++11 -O2 Core.cxx main.cxx -o $@
