Project Title: DNA Motif Sequencing using Suffix Trees

Mentoring TA : Ms. Monisha Singh

Group members: Jagrati Gupta(2023MCB1211)
               Ishita Garg(2023CSB1125)
               Yashasvi Chaudhary(2023CSB1174)

HOW TO RUN THE CODES:

1. Suffix Tree Construction Using Naive Approach

   Requirements
•  C++ Compiler (e.g., GCC, Clang, MSVC)
•  Input data file named Data.txt containing the string to build the suffix tree for

   Assumptions
•  Input string size should be n <= 10^4 for reasonable performance, given the naive time and space complexity O(n^2).

   Files
•  Naive.cpp: The main source file containing the implementation of the suffix tree.
•  Data.txt: The input file containing the string data (this file should be in the same directory as Naive.cpp).

   How to Run
1. Compile the Code: Open a terminal or command prompt, navigate to the directory containing Naive.cpp, and run:
        		g++ Naive.cpp -o suffix_tree
2. Run the Program: After successful compilation, execute the program with:
               		./suffix_tree

The program will prompt you for additional inputs and display outputs in the terminal.

3.  Program Prompts:
o   The program reads the string from Data.txt and adds a terminating character ($) to mark the end.
o   It will display the length of the string, memory usage, and construction time.
o   It will prompt to display the structure of the suffix tree:
   Enter 1 to print the suffix tree.
   Enter any other number to skip printing.

Output
•   Number of Characters: Shows the total characters in the input string, including the added $ terminator.
•   Memory Usage: Reports memory occupied by both the input string and the suffix tree.
•   Tree Construction Time: Shows time taken in milliseconds to construct the suffix tree.

Example

$ g++ Naive.cpp -o suffix_tree
$ ./suffix_tree
Number of characters in the string: 10
Memory occupied by the input string: 0.011 KB
Time taken to construct suffix tree: 2.5 ms
Memory occupied by the suffix tree: 0.580 KB

Enter 1 to print the suffix tree: 1
Suffix Tree for the input file:
[... tree structure ...]

Note:
Ensure Data.txt is in the same directory and formatted correctly with your input string.
Cleanup:
The program automatically frees allocated memory after execution to avoid memory leaks.

2. Suffix Tree Construction using Ukkonen's Algorithm

   Features

•  File Input Support: Reads the input sequence from Data.txt.
•  Suffix Tree Representation: Option to print the tree structure after construction.
•  Performance Metrics: Calculates and displays memory usage and construction time.

Prerequisites

•  C++ Compiler: Compatible with any standard C++ compiler (e.g., g++).
•  Data File: A text file named Data.txt in the same directory, containing the DNA sequence to analyze.

Compilation
To compile the code, use the following command:
		g++ -o suffix_tree Ukkonen.cpp

Usage
1.Ensure the input file Data.txt is in the same directory as the compiled executable. This file should contain the DNA sequence, with no special characters except A, T, G, C, and a termination character $.
2.Run the program using:
			./suffix_tree

3. After running, the program will:
o Display the length of the input string.
o Show the memory usage of the suffix tree in KB.
o Display the time taken to construct the suffix tree.

4. When prompted, enter 1 if you wish to print the suffix tree structure, or enter any other number to skip this step.

Example Output

Length of the input string (including terminal character): [Length]
Size of the input string: [Size] KB
Time taken to construct suffix tree: [Time] ms
Memory occupied by the suffix tree: [Memory] KB
Enter 1 to print the suffix tree: 1
Suffix Tree:
[Tree Structure Output]

Code Summary
•  readFile: Reads and dynamically resizes buffer to accommodate the input DNA sequence from Data.txt.
•  extend_suffix_tree: Builds the suffix tree by adding characters one at a time.
•  calculate_space: Calculates memory usage of the suffix tree.
•  print_suffix_tree: Optionally prints the constructed suffix tree.

3. DNA Motif Searching with Suffix Tree Construction (Ukkonen's Algorithm)

Features
1.  Efficient Suffix Tree Construction: Constructs the suffix tree in linear time O(n)O(n)O(n) using Ukkonen's algorithm.
2.  Motif Search: Searches for motifs in the constructed suffix tree with a time complexity of O(m)O(m)O(m).
3.  Performance Metrics: Measures time taken to construct the suffix tree and search motifs.
4.  Memory Management: Dynamically allocates memory for the input string and the suffix tree, with resizing as needed.

File Structure
•  Motif_Search.cpp : The main file implementing Ukkonen's algorithm, reading the DNA sequence, constructing the suffix tree, and searching motifs.
•  Data.txt: Input file containing the DNA sequence for which the suffix tree is built.

Prerequisites
•  C++ Compiler: Ensure you have a C++ compiler (like g++) installed on your system.
•  Input File: Create or place the DNA sequence file (Data.txt) in the same directory as the code. This file should contain only the DNA sequence without spaces or special characters.

Compilation Instructions

1.  Open a terminal or command prompt.
2.  Navigate to the directory containing Motif_Search.cpp.
3.  Run the following command to compile the code:

   			 g++ Motif_Search.cpp -o dna_motif_search

Running the Program

1.  After compilation, execute the program with the following command:

    			./dna_motif_search

2.  The program will prompt for input file Data.txt (containing the DNA sequence).

3.  Once the suffix tree is constructed, you can enter motifs to search within the DNA sequence. To quit the search, enter Q.
Input/Output
•  Input: The program reads the DNA sequence from Data.txt and constructs a suffix tree by appending a terminal character $.
•  Output:
o   Displays time taken to construct the suffix tree.
o   Asks for motif input, displaying:
   Time taken to search each motif.
   The number of occurrences of the motif within the DNA sequence.
   If the motif is not found, it notifies that the motif is absent.

Example:

Time taken to build the suffix tree: 12 milliseconds.

Enter the motif to search for (or 'Q' to quit): ATG
Time taken to search for the motif: 1 milliseconds.
The motif "ATG" is present in the string 3 times.

Enter the motif to search for (or 'Q' to quit): CGA
Time taken to search for the motif: 0 milliseconds.
The motif "CGA" is not present in the string.

Code Details
Important Components
1.  Node Structure: Defines a node with start and end indices, a suffix link, and an array for next node indices.
2.  Suffix Tree Initialization and Extension: Implements functions to build the suffix tree incrementally.
3.  File Reading: Reads Data.txt and dynamically resizes memory for the input sequence.
4.  Motif Search: Traverses the suffix tree to check for motif presence and counts occurrences.

Complexity
•  Time Complexity: O(n) for suffix tree construction, O(m)for searching a motif of length mmm.
•  Space Complexity: O(n) for the suffix tree.

________________________________________

