/*
 * Roster.h
 *
 *  Created on: Apr 20, 2016
 *      Author: vhong01
 */

#ifndef ROSTER_H_
#define ROSTER_H_

using namespace std;

struct Classes
{
	string class_name;
	string *students;
	int size;
	int capacity;
	bool in_both;
	Classes(){
		class_name = " ";
		students = NULL;
		size = 0;
		capacity = 0;
		in_both = false;
	}
};
class Roster{
public:
	Roster();
	~Roster();
	void add_classes(string class_name, string students);
	int get_size();
	Classes get(int i);
	void set_in_both(int i, bool);
private:
	Classes *roster;
	int size;
	int capacity;
	void expand_roster();
	void expand_student_list(int i);
};

#endif /* ROSTER_H_ */
