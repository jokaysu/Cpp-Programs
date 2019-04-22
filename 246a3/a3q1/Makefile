CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = drone
OBJECTS = a3q1.o drone.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
