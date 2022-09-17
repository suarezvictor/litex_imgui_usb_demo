all: core.cpp

core.cpp:
	cython -I../imgui core.pyx -2 -D --cplus -o core.cpp
	
clean:
	rm -f core.cpp core.h *.d
