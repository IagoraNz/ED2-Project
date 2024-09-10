# 📄 Work related to tree content in Data Structure II

The objective of this project is to evaluate the ability of respective programmers to deal with defined requirements and implement a program using fundamental data structures in computing.

## 🔗 Development environment
🔧 GCC
```
gcc.exe (tdm64-1) 10.3.0
Copyright (C) 2020 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```

🔧 Visual Studio Code
```
1.89.1
```

## 🔗 **Implementation**

### **1. Write a C program that records data about students and their history within a particular course. To do this, you need to have the following data structures:**
   
   *a. List of Students:* Student registration, Student name, Course Code, Grade tree, Enrollment, the list must be organized alphabetically by student name.
   
   *b. Course Tree:* Course code, Course name, number of Periods and a tree of Disciplines. The tree must be organized by the name of the Course Code.
   
   *c. Subject tree:* subject code, subject name, period, workload. The tree must be organized by the discipline code.
   
   *d. Grade Tree:* subject code, semester attended, final grade obtained by the student. The tree must be organized by the discipline code.
   
   *e. Enrollment Tree:* subject code, organized by subject code

Then, allow the user to do the following actions with the appropriate restrictions:

  *i)* Register students at any time in the list, so that you can only register a course code that has already been registered in the course tree.
  
  *ii)* Register courses at any time in the course tree, so that the user does not need to register subjects to allow course registration.
  
  *iii)* Register subjects at any time in a subject tree of a given course, or In other words, a subject can only be registered if the course has already been registered, in addition, the period of subject must be valid, that is, be between 1 and the maximum number of periods of the course. The load
  The course timetable must be a multiple of 15, ranging between 30 and 90.
  
  *iv)* Register a registration number, where it is an organized tree and contains only one registration code a subject in the student's course.
  
  *v)* Register Grades, allow the registration of grades only for subjects that are in the class tree enrollment, and when the grade is registered, the subject must be removed from the enrollment tree to
  note tree.

### **2. In relation to exercise 1, check the times**

  a. insertion of each element in the Courses tree (in item ii) of exercise 1);

  b. searching for a grade for a student's subject (in item xii) of exercise 1);

To check execution times, search for the C time function. Insert commands into the code to obtain
the starting time before taking the survey and the ending time after completing the survey.

🗞️ **Note 1:** for experiments, each run must insert the same Courses in a different order.

🗞️ **Note 2:** Remember that there cannot be printing between the start time and the end time, as printing
consumes a lot of time.

🗞️ **Note 3:** To validate the search time, it must be repeated 30 times. Take an average to get the
end result.
