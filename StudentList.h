/*
 * sixdegree.h
 *
 *  Created on: Apr 14, 2016
 *      Author: vhong01
 */
#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "student.h"

class StudentList
{
public:
	StudentList();
	StudentList(int initialSize);
	~StudentList();
	StudentList(const StudentList &source);
	void copy(Student *copy_list) const;
	StudentList &operator=(const StudentList &rhs);

	Student* get(int index);
	void set(int index, Student *newStudent);
	void add(Student *newStudent);

	int get_size();
	void set_size(int newSize);
	int get_capacity();
	Student* get_list();
private:
	Student *list;
	int size;
	int capacity;
	void expand();
};
#endif
