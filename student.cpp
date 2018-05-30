/*
 * Functions to manipulate student class
 */

#include <iostream>
#include "student.h"
#include <stdexcept>


using namespace std;

// constructor
Student::Student()
{
	initialize();
}

// purpose: initialize everything in the Student class
// arguments: none
// returns: none
void Student::initialize()
{
	student_name = " ";
	taed_size = 0;
	taken_size = 0;
	taed_capacity = 0;
	taken_capacity = 0;
	adjacency_size = 0;
	adjacency_capacity = 0;
	classes_taed = NULL;
	classes_taken = NULL;
	adjacency_list = NULL;
	marked = false;
	in_both = false;
}

// assignment operator
Student &Student::operator=(const Student &rhs)
{
	if (this != &rhs){
		delete[] classes_taed;
		delete[] classes_taken;
		delete[] adjacency_list;
		initialize();
		student_name = rhs.student_name;
		in_both = rhs.in_both;
		copy(rhs.classes_taed, rhs.classes_taken, rhs.adjacency_list,
		rhs.size("taed"), rhs.size("taken"), rhs.size("adjacency"));
	}
	return *this;
}

// copy constructor
Student::Student(const Student &source)
{
	initialize();
	in_both = source.in_both;
	student_name = source.student_name;
	copy(source.classes_taed, source.classes_taken, source.adjacency_list,
	source.size("taed"), source.size("taken"), source.size("adjacency"));
}

// destructor
Student::~Student()
{
	delete[] classes_taed;
	delete[] classes_taken;
	delete[] adjacency_list;
}

// purpose: copy array of classes taed, classes taken, and adjacency list
// arguments: arrays of classes to copy, array of students to copy, sizes
//	      of each array
// returns: none
void Student::copy(string *ta_copy, string *taken_copy, Student **adja_copy,
		int taedC_size, int takenC_size, int adjC_size)
{
	for (int i = 0; i < taedC_size; i++){
		add_class(ta_copy[i], "taed");
	}
	for (int i = 0; i < takenC_size; i++){
		add_class(taken_copy[i], "taken");
	}
	for (int i = 0; i < adjC_size; i++){
		add_adjacency(adja_copy[i]);
	}
}

//purpose: return a pointer to the Student at a given index of the adjacency
// 	   list
// arguments: int (index of adjacency_list array)
// returns: pointer to Student
Student* Student::get_adjacency(int index)
{
	if (index >= adjacency_size){
		throw runtime_error("Index out of bounds");
	}
	return adjacency_list[index];
}

// purpose: set a given index of the adjacency_list array to a given Student
// arguments: int (index), Student
// returns: none
void Student::set_adjacency(int index, Student *s)
{
	if (index >= adjacency_size){
		throw runtime_error("Index out of bounds");
	}
	adjacency_list[index] = s;
}

// purpose: adds a Student to the end of the adjacency_list array
// arguments: Student
// returns: none
void Student::add_adjacency(Student *s)
{
	if (adjacency_size == adjacency_capacity){
		expand("adjacency");
	}
	adjacency_list[adjacency_size] = s;
	adjacency_size++;
}

// purpose: return the class at a certain index of a one of the class arrays
// arguments: int (index), string (specifies which array)
// returns: string (class)
string Student::get_class(int index, string array_type)
{
	if (array_type == "taed"){
		if (index >= taed_size){
			throw runtime_error("Index out of bounds");
		}
		return classes_taed[index];
	}
	else if (array_type == "taken"){
		if (index >= taken_size){
			throw runtime_error("Index out of bounds");
		}
		return classes_taken[index];
	}
}

// purpose: returns marked- used to show if the Student has been visited when
//	    making paths
// arguments: none
// returns: boolian
bool Student::isMarked()
{
	return marked;
}

// purpose: set marked to true or false
// arguments: boolian
// returns: none
void Student::mark(bool value)
{
	marked = value;
}

// purpose: returns in_both- to show if student is in both files
// arguments: none
// returns: boolian
bool Student::isInBoth()
{
	return in_both;
}

// purpose: set in_both to true or false
// arguments: boolian
// returns: none
void Student::setInBoth(bool value)
{
	in_both = value;
}
// purpose: set a given index of a given class array to a given class
// arguments: int (index), string (class to set at index), string (type of
//	      class array)
// returns: none
void Student::set_class(int index, string new_class, string array_type)
{
	if (array_type == "taed"){
		if (index >= taed_size){
			throw runtime_error("Index out of bounds");
		}
		classes_taed[index] = new_class;
	}
	else if (array_type == "taken"){
		if (index >= taken_size){
			throw runtime_error("Index out of bounds");
		}
		classes_taken[index] = new_class;
	}
}

// purpose: add a given class to the end of a given class array
// arguments: string (class to add), string (type of class array)
// returns: none
void Student::add_class(string new_class, string array_type)
{
	if (array_type == "taed"){
		if (taed_size == taed_capacity){
			expand(array_type);
		}
		classes_taed[taed_size] = new_class;
		taed_size++;
	}
	else if (array_type == "taken"){
		if (taken_size == taken_capacity){
			expand(array_type);
		}
		classes_taken[taken_size] = new_class;
		taken_size++;
	}
}

// purpose: returns the size of a given array
// arguments: string (type of array)
// returns: int (size of array)
int Student::size(string array_type)const
{
	if (array_type == "taed"){
		return taed_size;
	}
	else if (array_type == "taken"){
		return taken_size;
	}
	else if (array_type == "adjacency"){
		return adjacency_size;
	}
}

// purpose: returns the capacity of a given array
// arguments: string (type of array)
// returns: int (capacity of array)
int Student::capcity(string array_type)const
{
	if (array_type == "taed"){
		return taed_capacity;
	}
	else if (array_type == "taken"){
		return taken_capacity;
	}
	else if (array_type == "adjacency"){
		return adjacency_capacity;
	}
}

// purpose: set the name of the student
// arguments: string (name)
// returns: none
void Student::set_name(string name)
{
	student_name = name;
}

// purpose: returns the name of the Student
// arguments: none
// returns: string (name)
string Student::name()
{
	return student_name;
}

// purpose: expands array of a given type
// arguments: string (type of array)
// returns: none
void Student::expand(string array_type)
{
	if (array_type == "taed"){
		taed_capacity = taed_capacity * 2 + 1;
		string *bigger_array = new string[taed_capacity];
		for (int i = 0; i<taed_size; i++){
			bigger_array[i] = classes_taed[i];
		}
		delete[] classes_taed;
		classes_taed = bigger_array;
	}
	else if (array_type == "taken"){
		taken_capacity = taken_capacity * 2 + 1;
		string *bigger_array = new string[taken_capacity];
		for (int i = 0; i<taken_size; i++){
			bigger_array[i] = classes_taken[i];
		}
		delete[] classes_taken;
		classes_taken = bigger_array;
	}
	else if (array_type == "adjacency"){
		adjacency_capacity = adjacency_capacity * 2 + 1;
		Student **bigger_array = new Student*[adjacency_capacity];
		for (int i = 0; i<adjacency_size; i++){
			bigger_array[i] = adjacency_list[i];
		}
		delete[] adjacency_list;
		adjacency_list = bigger_array;
	}
}
