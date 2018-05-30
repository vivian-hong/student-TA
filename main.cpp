/*
 * main.cpp
 *
 *  Created on: Apr 14, 2016
 *      Author: vhong01
 */

#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "StudentList.h"
#include "hashfunc.h"
#include "Roster.h"


using namespace std;

void 	readTaken(char *argv[], StudentList &s, Roster &r);
void 	readStudentsTaken(StudentList &s, string name, string course);
void	readRoster(Roster &r, string name, string course);
void 	checkRoster(Roster &r, string course);
void	readTAed(char *argv[], StudentList &s, Roster &r);
void 	readStudentsTaed(StudentList &s, string name, string course);
void 	hashStudentList(StudentList &s);
void 	makeDirected(StudentList &s);
void	iterThroughTaken(StudentList &s, int i, int j);
void 	readCommand(StudentList &s, Roster &r);
void	ls(StudentList &s);
void	lc(Roster &r);
void 	taed(StudentList &r);
void	roster(Roster &r);
void 	paths(StudentList &s);
int	findStudent(StudentList &s, string name);
void	shortestpath(StudentList &s);
void 	unmarkAll(StudentList &s);
string 	findEdge(Student *a, Student *b);
void	printPath(Student **path, int size);
void 	allPathsHelper(Student *a, Student *b, Student **path, int size,
		StudentList &s);
void	shortestPathsHelper(Student *a, Student *b, Student **path, int size,
		StudentList &s, StudentList &shortest);
void	sameStudentEdgeCase(Student *a, Student *b);

int main(int argc, char *argv[])
{
	//check for correct command line
	if (argc < 3){
		cout<< "Error: Not enough files provided."
			" Please include a student file and a ta file."<<endl;
		return 0;
	}
	if (argc > 3){
		cout<< "Error: Too many files provided."
			" Please include a student file and a ta file."<<endl;
		return 0;
	}

	StudentList s;
	Roster r;

	readTaken(argv, s, r);
	readTAed(argv, s, r);

	hashStudentList(s);

	makeDirected(s);

	readCommand(s, r);

	return 0;
}

// purpose: read the file containing students, passes student name and course
//	    taken to other functions to store in StudentList and Roster
// arguments: command line, StudentList, Roster
// returns: none
void readTaken(char *argv[], StudentList &s, Roster &r)
{
	ifstream input;
	string line;
	input.open(argv[1]);
	while (! getline(input, line).eof()){
		int i=0;
		string name;
		string course;
		while (line[i] != *":"){ //will only store up to first colon
			name += line[i];
			i++;
		}
		i++;
		int length = line.length();//so can compare int to int
		while (i<length){
			if (line[i] != *":") //so wont store colon in course
				course += line[i];
				i++;
		}
		readStudentsTaken(s, name, course);
		readRoster(r, name, course);
	}
	input.close();
}

// purpose: stores Students in StudentList (creates Student sets name, adds
// 	    to courses taken)
// arguments: StudentList, string (name of student), string (course)
// returns: none
void readStudentsTaken(StudentList &s, string name, string course)
{
	bool is_in = false;
	// if Student already exists, add to it
	for (int i = 0; i < s.get_size(); i++){
		if (name == s.get(i)->name()){
			is_in = true;
			s.get(i)->add_class(course, "taken");
			break;
		}
	}
	// if Student doesn't exist, create Student and store
	if (is_in == false){
		Student *stu = new Student;
		stu->set_name(name);
		stu->add_class(course, "taken");
		s.add(stu);
	}
}

// purpose: stores a student name and course in Roster
// arguments: Roster, string (name of student), string (course)
// returns: none
void readRoster(Roster &r, string name, string course)
{
	r.add_classes(course, name);
}

// purpose: read the file containing tas, passes ta name and course
//	    taed to other functions to store in StudentList
// arguments: command line, StudentList
// returns: none
void readTAed(char *argv[], StudentList &s, Roster &r)
{
	ifstream input;
	string line;
	input.open(argv[2]);
	while (! getline(input, line).eof()){
		int i=0;
		string name;
		string course;
		while (line[i] != *":"){ //only stores up to first colon
			name += line[i];
			i++;
		}
		i++;
		int length = line.length();//so can compare int to int
		while (i<length){
			if (line[i] != *":") // wont store colon in course
				course += line[i];
				i++;
		}
		readStudentsTaed(s, name, course);
		checkRoster(r, course);
	}
	input.close();
}

// purpose: checks if course in ta file is already stored in roster
// arguments: Roster, string (course)
// returns: none
void checkRoster (Roster &r, string course)
{
	for( int i = 0; i < r.get_size(); i++){
		if (r.get(i).class_name == course){
			r.set_in_both(i,true);
			break;
		}
	}
}
// purpose: stores Students in StudentList (creates Student sets name, adds
// 	    to courses taed)
// arguments: StudentList, string (name of student), string (course)
// returns: none
void readStudentsTaed(StudentList &s, string name, string course)
{
	bool is_in = false;
	// if Student exists, add to it
	for (int i = 0; i < s.get_size(); i++){
		if (name == s.get(i)->name()){
			is_in = true;
			s.get(i)->add_class(course, "taed");
			s.get(i)->setInBoth(true);
			break;
		}
	}
	// if Student doesn't exist, create and store
	if (is_in == false){
		Student *stu = new Student;
		stu->set_name(name);
		stu->add_class(course, "taed");
		s.add(stu);
	}
}

// purpose: hashes the StudentList list array so the Students are easily found
// arguments: StudentList
// returns: none
void hashStudentList(StudentList &s)
{
	StudentList temp = StudentList(s.get_size());
	Student *s_list = s.get_list();
	for (int i = 0; i < s.get_size(); i++){
		uint32_t hashcode = hash_string(s_list[i].name());
		hashcode = hashcode % s.get_size();
		while (temp.get(hashcode)->name() != " "){
			hashcode = (hashcode + 1) % s.get_size();
		}
		temp.set(hashcode, &s_list[i]);
	}
	for (int i = 0; i < s.get_size(); i++){
		Student *stu = temp.get(i);
		s.set(i,stu);
	}
}

// purpose: begins to make adjacency lists for each student, iterates through
// 	    every Student and accesses classes taed, then calls function to
// 	    compare with classes taken by every Student
// arguments: StudentList
// returns: none
void makeDirected (StudentList &s)
{
	for (int i = 0; i < s.get_size(); i++){ //iterate through every Student
		for (int ta = 0; ta < s.get(i)->size("taed"); ta++){
			iterThroughTaken(s, i, ta);
		}
	}
}

// purpose: iterates through every class taken by every Student and if a
//	    student has taken a class that another student has taed, they are
// 	    added to the ta's adjacency list
// arguments: StudentList, int (student ta index), int (index of class taed)
// returns: none
void iterThroughTaken(StudentList &s, int i, int ta)
{
	for (int k = 0; k < s.get_size(); k++){ //iterate through every Student
		for (int take = 0;take < s.get(k)->size("taken"); take++){
			if (s.get(i)->get_class(ta, "taed") ==
				s.get(k)->get_class(take, "taken")){
				s.get(i)->add_adjacency(s.get(k));
			}
		}
	}
}

// purpose: reads cin commands and calls appropriate function
// arguments: StudentList, Roster
// returns: none
void readCommand(StudentList &s, Roster &r)
{
	string command;
	while (cin>>command and !cin.eof()){
		if (command == "ls"){
			ls(s);
		}
		if (command == "lc"){
			lc(r);
		}
		if (command == "taed"){
			taed(s);
		}
		if (command == "roster"){
			roster(r);
		}
		if (command ==  "paths"){
			paths(s);
		}
		if (command == "shortestpath"){
			shortestpath(s);
		}
		if (command == "quit"){
			break;
		}
	}
}

// purpose: prints every Student in both files
// arguments: StudentList
// returns: none
void ls(StudentList &s)
{
	for (int i = 0; i < s.get_size(); i++){
		if (s.get(i)->isInBoth()){
			cout<< s.get(i)->name()<<endl;
		}
	}
}

// purpose: prints every course in both files
// arguments: Roster
// returns: none
void lc(Roster &r)
{
	for (int i = 0; i < r.get_size(); i++){
		if (r.get(i).in_both == true){
			cout<< r.get(i).class_name<<endl;
		}
	}
}

// purpose: prints every course that a given Student taed
// arguments: StudentList
// returns: none
void taed(StudentList &s)
{
	string sName;
	cin >> sName;
	int count = 0;
	uint32_t hashcode = (hash_string(sName)) % s.get_size();
	while ( sName != s.get(hashcode)->name()){
		if (count > s.get_size()){
			cout<<"Student not found"<<endl;
			return;
		}
		hashcode = (hashcode + 1) % s.get_size();
		count++;
	}
	for (int i = 0; i < s.get(hashcode)->size("taed"); i++){
		cout<< s.get(hashcode)->get_class(i, "taed")<<endl;
	}

}

// purpose: prints every student in a given course
// arguments: Roster
// returns: none
void roster(Roster &r)
{
	string course;
	cin >> course;
	int i;
	for (i = 0; i<r.get_size(); i++){
		if (r.get(i).class_name == course){
			break;
		}
	}
	if(r.get(i).class_name != course){
		cout<<"Course not found"<<endl;
		return;
	}
	for (int j = 0; j<r.get(i).size; j++){
		cout<<r.get(i).students[j]<<endl;
	}
}

// purpose: finds every path between two given students
// arguments: StudentList
// returns: none
void paths(StudentList &s)
{
	string studentA;
	string studentB;
	cin>> studentA;
	cin>> studentB;
	int hashcode = findStudent(s, studentA);
	if (hashcode == -1)
		return;
	Student *a = s.get(hashcode);
	hashcode = findStudent(s, studentB);
	if (hashcode == -1)
		return;
	Student *b = s.get(hashcode);
	unmarkAll(s);
	if (a->name() == b->name()){
		sameStudentEdgeCase(a, b);
		return;
	}
	Student *path[s.get_size()];
	int size = 0;
	allPathsHelper(a, b, path, size, s);
}

// purpose: helper function that finds a student given the name of a student,
//	    exception for when Student isn't found
// arguments: StudentList, string (name)
// returns: int (index of Student in StudentList list array)
int findStudent(StudentList &s, string name)
{
	int count = 0;
	uint32_t hashcode = (hash_string(name)) % s.get_size();
	while ( name != s.get(hashcode)->name()){
		if (count > s.get_size()){
			cout<< "Student not found"<<endl;
			return -1;
		}
		hashcode = (hashcode + 1) % s.get_size();
		count++;
	}
	return hashcode;
}

// purpose: recursive function that finds all paths between two students
// arguments: pointer to two Students, an array of Students (the path between
//	      the students), size of the path array, StudentList
// returns: none
void allPathsHelper(Student *a, Student *b, Student **path, int size,
		StudentList &s)
{
	a->mark(true); // marks as visited
	path[size] = a;
	size++;
	if (a->name() == b->name()){
		printPath(path, size);
	}
	else {
		for (int i = 0; i < a->size("adjacency"); i++){
			if (!a->get_adjacency(i)->isMarked()){
				allPathsHelper(a->get_adjacency(i), b,
						path, size, s);
			}
		}
	}
	size--;
	a->mark(false); // removes Student from path if it's wrong
}
// purpose: finds the shortest path between two students
// arguments: StudentList
// returns: none
void shortestpath(StudentList &s)
{
	string studentA;
	string studentB;
	cin>> studentA;
	cin>> studentB;
	int hashcode = findStudent(s, studentA);
	if (hashcode == -1)
		return;
	Student *a = s.get(hashcode);
	hashcode = findStudent(s, studentB);
	if (hashcode == -1)
		return;
	Student *b = s.get(hashcode);
	unmarkAll(s);
	if (a->name() == b->name()){
		sameStudentEdgeCase(a, b);
		return;
	}
	Student *path[s.get_size()];
	StudentList shortest;
	shortest.set_size(s.get_size()); //for comparison to size of paths
	int size = 0;
	shortestPathsHelper(a, b, path, size, s, shortest);
	if (shortest.get_list() == NULL)
		return;
	for (int i = 0; i < shortest.get_size(); i++){
		path[i] = shortest.get(i);
	}
	printPath(path, shortest.get_size());
}

// purpose: deals with the edge case of find a path between the same student
// arguments: pointers to two Students
// returns: none
void sameStudentEdgeCase(Student *a, Student *b)
{
	if (findEdge(a,b) == " "){
		return;
	}else{ //case if student taed a class they took, piazza said required
		cout<< a->name();
		cout<< " +- ";
		cout<< findEdge(a,b);
		cout<<" -> ";
		cout<< b->name()<<endl;
	}
}

// purpose: recursive function that finds the shortest path betwee two students
// arguments: pointers to two Students, array of pointers to Students (path
//	      between two Students), size of array, StudentList (original list),
//	      StudentList (stores shortest path
// returns: none
void shortestPathsHelper(Student *a, Student *b, Student** path, int size,
		StudentList &s, StudentList &shortest)
{
	a->mark(true);
	path[size] = a;
	size++;
	if (a->name() == b->name()){
		if (size < shortest.get_size()){
			shortest.set_size(0);
			for (int i = 0; i < size; i++){
				shortest.add(path[i]);
			}
		}//makes sure that shortest always contains the shortest path
	}
	else {
		for (int i = 0; i < a->size("adjacency"); i++){
			if (!a->get_adjacency(i)->isMarked())
				shortestPathsHelper(a->get_adjacency(i), b,
						path, size, s, shortest);
		}
	}
	size--;
	a->mark(false);
}

// purpose: finds class that connects two students
// arguments: pointers to two Students
// returns: string (class)
string findEdge(Student *a, Student *b)
{
	for (int ta = 0; ta < a->size("taed"); ta++){
		for (int take = 0; take < b->size("taken"); take++){
			if (a->get_class(ta,"taed") ==
					b->get_class(take,"taken")){
				return a->get_class(ta, "taed");
			}
		}
	}
	return " ";
}

// purpose: prints the path between two students
// arguments: array of pointers to Students, size of array
// returns: none
void printPath(Student *path[], int size)
{
	for (int i = 0; i < size-1; i++){
		cout<<path[i]->name();
		cout<< " +- ";
		cout<< findEdge(path[i], path[i+1]);
		cout<< " -> ";
	}
	cout<<path[size-1]->name()<<endl;
}

// purpose: unmarks all the Students in StudentList
// arguments: StudentList
// returns: none
void unmarkAll(StudentList &s)
{
	for (int i = 0; i<s.get_size(); i++){
		s.get(i)->mark(false);
	}
}
