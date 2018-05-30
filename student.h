/*
 * Student class containing student name, classes TAed, classes taken,
 * an adjacency list, and a marked boolian
 */
#ifndef STUDENT_H
#define STUDENT_H
using namespace std;
class Student
{
public:
	Student();
	~Student();
	Student(const Student &source);
	void initialize();
	void copy(string *ta_copy, string *taken_copy,
			Student **adjacency_copy, int taC_size, int takenC_size,
			int adjC_size);
	Student &operator=(const Student &rhs);

	Student* 	get_adjacency(int index);
	void	 	set_adjacency(int index, Student *s);
	void 		add_adjacency(Student *s);

	string 		get_class(int index, string array_type);
	void 		set_class(int index, string new_class, string array_type);
	void 		add_class(string new_class, string array_type);

	int 		size(string array_type)const;
	int 		capcity(string array_type)const;

	void 		set_name(string name);
	string 		name();
	bool		isMarked();
	void		mark(bool);
	bool		isInBoth();
	void		setInBoth(bool);


private:
	string student_name;
	int taed_size;
	int taken_size;
	int taed_capacity;
	int taken_capacity;
	int adjacency_size;
	int adjacency_capacity;
	bool marked;
	bool in_both;
	string *classes_taed;
	string *classes_taken;
	Student **adjacency_list;
	void expand(string array_type);

};
#endif
