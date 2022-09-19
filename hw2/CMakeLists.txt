# cmake_minimum_required (VERSION 3.24.2)
# project(hw2)

# set(CMAKE_COLOR_MAKEFILE ON)

# set(CMAKE_CXX_FLAGS "-std=c++0x -g -Wall -Werror")
# set(CMAKE_C_FLAGS "-std=c11 -g -Wall -Wextra")

# add_executable(hw2_test mjdqw5_sgsqb4_hw2.c)
# target_link_libraries(gtest pthread)

# enable_testing()
# add_test(NAME  hw2_test
#          COMMAND hw2_test)
all: queue.o elevator.o
	gcc queue.o elevator.o

queue.o: queue.c queue.h
	gcc -Wall -Werror -g -c queue.c

elevator.o: elevator.c
	gcc -Wall -Werror -g -c elevator.c

clean: 
	rm *.o *.out
