SHEDSKIN_LIBDIR=/usr/local/lib/python2.7/dist-packages/shedskin/lib
CC=g++
CCFLAGS=-O2 -march=native -Wno-deprecated $(CPPFLAGS) -I. -I${SHEDSKIN_LIBDIR}
LFLAGS=-lgc $(LDFLAGS)

CPPFILES=/home/gabriel/Desktop/INF1608_Visualizacao_Volumetrica/vri_cpp.cpp \
	${SHEDSKIN_LIBDIR}/math.cpp \
	${SHEDSKIN_LIBDIR}/builtin.cpp

HPPFILES=/home/gabriel/Desktop/INF1608_Visualizacao_Volumetrica/vri_cpp.hpp \
	${SHEDSKIN_LIBDIR}/math.hpp \
	${SHEDSKIN_LIBDIR}/builtin.hpp

all:	vri_cpp

vri_cpp:	$(CPPFILES) $(HPPFILES)
	$(CC)  $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o vri_cpp

vri_cpp_prof:	$(CPPFILES) $(HPPFILES)
	$(CC) -pg -ggdb $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o vri_cpp_prof

vri_cpp_debug:	$(CPPFILES) $(HPPFILES)
	$(CC) -g -ggdb $(CCFLAGS) $(CPPFILES) $(LFLAGS) -o vri_cpp_debug

clean:
	rm -f vri_cpp vri_cpp_prof vri_cpp_debug

.PHONY: all clean

