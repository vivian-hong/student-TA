/*
 * StudentList.cpp
 */
#include <iostream>
#include <stdexcept>
#include "StudentList.h"

using namespace std;

// constructor
StudentList::StudentList()
{
	list = NULL;
	size = 0;
	capacity = 0;
}

// constructor with an initial size
StudentList::StudentList(int initialSize)
{
	size = initialSize;
	capacity = initialSize;
	list = new Student[initialSize];
}

// destructor
StudentList::~StudentList()
{
	delete[] list;
}

// copy constructor
StudentList::StudentList(const StudentList &source)
{
	size = 0;
	capacity = 0;
	copy(source.list);
}

// purpose: copy the list array of a StudentList
// arguments: array of Students
// returns: none
void StudentList::copy(Student *copy_list) const
{
	for (int i = 0; i < size; i++){
		list[i] = copy_list[i];
	}
}

// assignment operator
StudentList &StudentList::operator=(const StudentList &rhs)
{
	if (this != &rhs){
		delete[] list;
		list = new Student[rhs.size];
		size = rhs.size;
		capacity = rhs.capacity;
		copy(rhs.list);
	}
	return *this;
}

// purpose: returns a pointer to a Student at a given index
// arguments: int (index)
// returns: pointer to a Student
Student* StudentList::get(int index)
{
	if (index >= size){
		throw runtime_error("Index out of bounds");
	}
	return &list[index];
}

// purpose: sets list at a given index to a Student
// arguments: int (index), Student
// returns: none
void StudentList::set(int index, Student *newStudent)
{
	if (index >= size){
		throw runtime_error("Index out of bounds");
	}
	list[index] = *newStudent;
}

// purpose: adds a Student at the end of the list array
// arguments: Student
// returns: none
void StudentList::add(Student *newStudent)
{
	if (size == capacity){
		expand();
	}
	list[size] = *newStudent;
	size++;
}

// purpose: expands the list array
// arguments: none
// returns: none
void StudentList::expand()
{
	capacity = capacity * 2 + 1;
	Student *bigger_array = new Student[capacity];
	for (int i = 0; i < size; i++){
		bigger_array[i] = list[i];
	}
	delete[] list;
	list = bigger_array;
}

// purpose: returns size of list array
// arguments: none
// returns int (size)
int StudentList::get_size()
{
	return size;
}

// purpose: sets the size of the list array- this is used when finding shortest
// 	    path, any other usage could lead to seg faults
// arguments: int (size)
// returns: none
void StudentList::set_size(int newSize)
{
	size = newSize;
}

// purpose: get the capacity of the list array
// arguments: none
// returns: int (capacity)
int StudentList::get_capacity()
{
	return capacity;
}

// purpose: returns the list array
// arguments: none
// returns: array of Students
Student *StudentList::get_list()
{
	return list;
}
