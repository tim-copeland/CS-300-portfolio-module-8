# CS-300-portfolio-module-8
What was the problem you were solving in the projects for this course?
The objective was to develop an application where ABCU University can handle their catalog of courses. This program should be capable of importing information regarding courses (such as name and pre-requisites) from a file. It should also enable the search capability for finding out specific details related to any particular course or even printing out the entire list of courses in sorted order.

How did you approach the problem? Consider why data structures are important to understand.
This is where I made use of a Hash Table along with a custom hashing algorithm and collision resolution using chaining. Data structures play a very important role as the efficiency of the entire application is dependent on them. The Hash Table provides a nearly constant time O(1) lookup feature which is highly desirable for an application where the advisors would be required to look up courses.

How did you overcome any roadblocks you encountered while going through the activities or project?
One of the main obstacles in the development process included making the "Print All Courses" functionality work because Hash Tables are sorted. I managed to overcome this problem through the creation of an auxiliary function that will transfer information from the Hash Table to an intermediate Vector and then sort the Vector in alphabetical order via std::sort with the use of a lambda expression.
Another problem encountered in the project was associated with the parsing of input files, which was solved using stringstream for tokenization.

How has your work on this project expanded your approach to designing software and developing programs?
Through this project, I learned how to build scalable software. From my analysis in project one, despite having their individual merits, Hash Tables can be very useful when dealing with large sets of data. Now when designing software, I begin by carrying out an analysis of the expected tasks. If searching will be needed frequently, I consider Hash Tables; if sorting is always needed, I consider Trees.

How has your work on this project evolved the way you write programs that are maintainable, readable, and adaptable?
I have moved from coding “monolithic” programs to developing programs in a modular fashion. Dividing the logic into different classes, such as HashTable, and functions, including displayCourse() and loadCourses(), has made my code much more manageable. I paid close attention to designing a code that could be easily adaptable. Using a prime number for tableSize and chaining would help handle a greater number of courses without compromising performance.
