
Purpose of Program:

- read in two files, one of students and one of tas with each file listing the
  student or ta and the class they have taken or taed respectively
- store the files in data structures in order to support the commands:
	- ls - lists students found in both input files
	- lc - lists course found in both input files
	- taed <student_name> - lists courses that <student_name> has taed
	- roster <course_name> - lists roster of class <course_name>
	- paths <student_a> <student_b> - print all paths between <student_a>
	  and <student_b>
	- shortestpath <student_a> <student_b> - prints the shortest path 
	  between <student_a> and <student_b>

Files:

main.cpp -- contains main that calls functions to read in files, store info
	    correctly, reads in commands, and prints the correct output
Roster.cpp -- contains all the functions to manipulate the Roster class
	      including add_classes, get_size, get, etc.
Roster.h -- contains the header functions for Roster.cpp
student.cpp -- contains all the functions to manipulate the Student class 
	       including get_adjacency, set_adjacency, add_class, size, etc.
student.h -- contains the header functions for student.cpp
StudentList.cpp -- contains all the functions to manipulate the StudentList
		   class including get_size, get_capacity, add, set, etc.
StudentList.h -- contains all the header functions for StudentList.cpp
hashfunc.cpp -- contains functions for producing 32-bit hashes for hashtable
		lookup
hashfunc.h -- contains header functions for hashfunc.cpp

How to compile:

- use included Makefile

Outline of Data Structure:

- StudentList class contains an array of instances of the Student class
  which contains the name of the student, every class they've taken, every
  class they've taed, an adjacency list of Students they're adjacent to, and 
  boolians that are used in the commands
- Roster class contains an array of Classes structs which contain in them a 
  course name, an array of students who have taken the course and a boolian
  that is used in the commands
- all arrays in the various classes and structs are dynamic and the classes
  and structs contain the variables associated with the arrays (size, capacity)
  
Outline of Algorithm and Complexity:

- Hashing- the hashing is done by getting a hashcode to store the Student in 
  the list array of StudentList at
  	- if there is a Student already there, the Student will be stored in 
  	  the next available spot
  	- best case complexity is O(1), if none of the hashcodes overlap
  	- worst case complexity is O(n), if the elements are hashed into the
  	  same key- also because only the attempt is added to the hashcode
  	  instead of a jump, the likelihood of a worse complexity increases
- Making Directed Graph- iterate through every student and for every class they
  ta, iterate through every student and check if the student has taken the 
  class that the original student taed
  	- for s number of students and c number of classes, the complexity 
  	  would be O(s^2*c^2) because for every student, iterate through every
  	  class they've taed, and for every class taed, iterate through every
  	  student, and for every student, iterate through every class they've
  	  taken
- Finding paths- both shortest path and paths are recursive functions that 
  do depth first search
   	- for finding the shortest path, instead of printing every path, check
   	  if the new path found is shorter than the previously stored path
   	- complexity for shortest path is equal to complexity for finding all 
   	  paths because still go through every path and compare sizes to find
   	  shortest (a BFS would have found shortest path first, but could
   	  potentially have a poor space complexity, time complexity is the same)
   	- complexity for a single path is, for branching b (number of adjacent)
   	  and depth d O(b^d), multiply complexity by number of paths
   	  
   	  
Side note: if had more time, would have added an adjacent classes array to 
student class and stored the class in common between two students parallel to 
adjacency list to deal with multiple edges between two nodes- print function
would have been altered, paths would have included the string class after 
name of students, find edge would not be needed.