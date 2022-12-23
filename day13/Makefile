CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD
OBJECTS = day13p2.o list.o integer.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = day13

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
