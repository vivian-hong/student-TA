/*
 * Roster.cpp
 *
 *  Created on: Apr 20, 2016
 *      Author: vhong01
 */
#include <iostream>
#include <stdexcept>
#include "Roster.h"

using namespace std;

// constructor
Roster::Roster()
{
	size = 0;
	capacity = 0;
	roster = NULL;
}

// destructor
Roster::~Roster()
{
	delete[] roster;
}

// purpose: adds classes to an array and within classes add students to array
//	    of students who have taken the class
// arguments: string class name and student name
// returns: none
void Roster::add_classes(string course, string stu)
{
	bool is_in = false;
	int i;
	//check if course already exists
	for (i = 0; i < size; i++){
		if (roster[i].class_name == course){
			is_in = true;
			break;
		}
	}
	//course doesn't already exits, add the course and the student to
	//the course's array of students
	if (is_in == false){
		if (size == capacity){
			expand_roster();
		}
		roster[size].class_name = course;
		expand_student_list(size);
		roster[size].students[0] = stu;
		roster[size].size++;
		size++;
	}else{//course exists, add student to course's array of students
		if(roster[i].size == roster[i].capacity){
			expand_student_list(i);
		}
		roster[i].students[roster[i].size] = stu;
		roster[i].size++;
	}
}

// purpose: return size of the array of courses taken
// arguments: none
// returns: int (size of array)
int Roster::get_size()
{
	return size;
}

// purpose: return the course at a given index
// arguments: int (index of course array)
// return: Classes struct (of course at index)
Classes Roster::get(int index)
{
	return roster[index];
}

void Roster::set_in_both(int index, bool value)
{
	roster[index].in_both = value;
}
// purpose: expands the array of Classes structs
// arguments: none
// returns: none
void Roster::expand_roster()
{
	capacity = capacity * 2 + 1;
	Classes *bigger_array = new Classes[capacity];
	for (int i = 0; i < size; i++){
		bigger_array[i].class_name = roster[i].class_name;
		bigger_array[i].capacity = roster[i].capacity;
		bigger_array[i].size = roster[i].size;
		bigger_array[i].students = roster[i].students;
	}
	delete[] roster;
	roster = bigger_array;
}

// purpose: expands the array of students (in the Classes struct)
// arguments: int (index of Classes array in order to expand correct array of
// 	      students
// returns: none
void Roster::expand_student_list(int index)
{
	roster[index].capacity = roster[index].capacity * 2 + 1;
	string *bigger_array = new string[roster[index].capacity];
	for (int i = 0; i < roster[index].size; i++){
		bigger_array[i] = roster[index].students[i];
	}
	delete[] roster[index].students;
	roster[index].students = bigger_array;
}
