# graph-implementation-DSA2020
Assignment 1 of Data Structures and Alogirthms (31251) - Graph Implementation in C++
Task is to implement a weighted, directed graph with weighted vertices in C++.

This repository is here as a self-reference of this assignment and useful backup. Assignment was part of Data Structures and Algorithms class (31251) taken in Autumn 2020.

See below for original assessment specification and description:

## Overview
Your task is to implement a directed_graph class, where each node/edge has a weight.

For example, the following weighted directed graph has five nodes { A, B, C, D, E } and seven edges { (A, B), (A, C), (B, E), (C, D), (D, A), (D, C), (D, E)}. Node C has a weight of 400, and its incident edges: (A, C) has the weight of 9; (D, C) has the weight of 7; (C, D) has the weight of 4.

![Example graph.](https://imgur.com/QqV6oAw.png)

The class should offer a reasonably effective suite of operations. Some (but not all) of basic operations are:

Adding and removing nodes and edges (with weights);
-Depth-first and breadth-first traversals;
-Computing the minimum spanning tree (MST);
-Pre-order, in-order, and post-order traversals of the MST;

Besides the above, the class should offer an operation to solve the following open question:
- Consider each node as a twitter user, the node's weight as the number of followers of the user, and the weight of each directed edge as how many times a user liked another user. For example, in the above graph, A and C have 800 and 400 followers, respectively; A liked C nine times while C never liked A. Can you find a way to assess the importance or popularity of the users, so as to rank the users in descending order? Note that no single best answer may exist to this question.

You need to carefully consider:
- Whether it is necessary to declare other classes apart from the directed_graph class.

## The Code
You are provided with a directed_graph.hpp file, which includes most (if not all) of the basic definitions you will need. You made add extra methods, classes, structs, etc., as long as they don't interfere with the existing definitions.

You have also been provided with a main.cpp for ad-hoc testing purposes. main.cpp file does not form part of the assignment, and will not be marked. You can do anything you like with it. When the "run" button is pressed, it will compile and run main.cpp. When the "mark" button is pressed, your code will be run against the tests. Note that the testing code can only mark your code when your code does not cause a program crash (e.g. a segfault). If you get any errors during compiling, make sure you fix that problem first!

Remember to read over all the code before starting.

You have terminal access if you so desire it.

## Directed Graphs
As the abstract data structure, and the possibilities for implementing it, have been covered in the lectures. Some parts of the task may require you to develop some thinking because the lectures may not readily give you the solution. Don't hesitate to ask questions if you are unclear about the task requirements. 

## The directed_graph Class
directed_graph is probably the most complicated C++ class you will have had to implement, but it bears a great resemblance to many of the things we've already done, so just break it down into smaller, more manageable tasks. The code itself is commented to indicate the purpose of each method. Again, to avoid clutter, I won't repeat it all here, but do not hesitate to ask if anything is unclear (there's a forum specifically for the assignment on Ed: 31251 Discussion - Assignments - A1).

## Marking
The assignment will be marked against three components: functionality, design and style.

**Functionality** will be marked by the tests and verified by the teaching team. It constitutes 17% of the subject's total mark. You must submit your code to test against our tests by 23:59 22 May 2020.

**Design** will be marked in your Week 9-10 tutorials by your tutor. It constitutes 12% of the total mark. It does not depend on the functionality of your code. You may be asked questions by your tutor to help them test your understanding of your code. It will be marked qualitatively against the following rubric:
- Pass The code shows a basic understanding of how to employ data structures to achieve a goal. The design should avoid unnecessary data structures and should make reasonable use of iteration and recursion when appropriate.
- Credit The design shows a solid understanding of data structures and demonstrate effective use of control structures to achieve the program’s goals.
- Distinction The design shows a high degree of understanding of how to use data structures to achieve a goal efficiently, and demonstrate some evidence that the design does not use unnecessary resources. The design should be clean and efficient.
- High Distinction The design demonstrates a high degree of understanding of data structures and how to efficiently employ them to build algorithms that not only meet technical goals but also support maintenance and future development.

**Style** will also be marked in your Week 9-10 tutorials by your tutor (6%). It will be marked qualitatively against the following rubric:
- Pass The code mostly uses some formatting standard and is somewhat readable.
- Credit The code adheres well to a formatting standard and variables are well named.
- Distinction At least as well formatted as for Credit standards, along with sufficient inline commenting to explain the code.
- High Distinction Excellent formatting and variable naming. Excellent, judiciously employed comments that explain the code without just repeating the code.

**Marking Schedule**

All being well, assuming you submit before the deadline and attend your Week 9-10 tutorials (in the class you are actually enrolled in - exceptions will only be made for cases where attendance at your enrolled tutorial is impossible), we aim to return the marks for the assignment within a week of the tutorial. The "mark" button will become available two weeks before the due date, which is Friday 8 May 2020, to give you some peacetime to focus on your assignment.

