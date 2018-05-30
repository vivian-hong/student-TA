#
# Makefile for HW6
#
CXX      = clang++
CXXFLAGS = -g -Wall -Wextra
LDFLAGS  = -g

hw6degrees: main.o hashfunc.o StudentList.o student.o Roster.o
	${CXX} ${CXXFLAGS} -o hw6degrees $^
main.o: main.cpp StudentList.h hashfunc.h Roster.h
StudentList.o: StudentList.cpp StudentList.h student.h
student.o: student.cpp student.h
Roster.o: Roster.cpp Roster.h

clean:
	rm -f hw6degrees

provide:
	provide comp15 hw6 main.cpp Makefile ReadMe.md hashfunc.cpp hashfunc.h StudentList.cpp StudentList.h student.cpp student.h Roster.cpp Roster.h
