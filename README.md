# CS201_PROJECT

Project Title: DNA Motif Sequencing using Suffix Trees

Mentoring TA : Ms. Monisha Singh

Group members: Jagrati Gupta(2023MCB1211)
               Ishita Garg(2023CSB1125)
               Yashasvi Chaudhary(2023CSB1174)

SUMMARY OF THE PROJECT:

In this project, we aimed to implement a suffix tree for string processing in C++. This implementation was developed with the goal of understanding the basic structure of suffix trees and exploring their applications, especially in areas like DNA sequencing. Suffix trees are particularly useful in bioinformatics because they allow efficient searching for patterns and repeated sequences within a long string, such as a DNA sequence. 

Our project focuses on DNA motif sequencing, aiming to identify and analyse specific patterns within DNA sequences efficiently. We are utilizing suffix trees, which allow us to store and manipulate DNA strings in a way that facilitates rapid searches for motifs. By constructing a suffix tree for the given DNA sequence, we can quickly find all occurrences of desired motifs and analyse their characteristics. This approach not only enhances the speed of motif discovery but also allows for a more comprehensive analysis of sequence variations. Our execution plan includes preprocessing the DNA data to ensure optimal suffix tree construction and implementing algorithms that will traverse the tree to extract relevant motifs, ultimately contributing to advancements in genomics research.

We employed both the naive algorithm and Ukkonen's algorithm to construct suffix trees and analyze DNA sequences. The naive algorithm, while straightforward, involves a more direct approach by generating all possible suffixes of the DNA sequence and organizing them in a tree structure. This method helps us understand the basic principles of suffix tree construction, although it can be inefficient for longer sequences due to its quadratic time complexity.

In contrast, Ukkonen's algorithm offers a more advanced and efficient approach by building the suffix tree in a linear time complexity of O(n). This algorithm incrementally constructs the suffix tree by processing each character of the DNA sequence and maintaining the tree structure dynamically. This efficiency is particularly beneficial for large datasets, enabling us to handle complex sequences and motifs more effectively. By combining these two algorithms, we can compare their performance and utility, gaining insights into the trade-offs between simplicity and efficiency in suffix tree construction for DNA motif analysis.

An application of the suffix tree we implement is DNA motif searching, that allows us to search for repeated patterns in linear time complexity O(n).
In conclusion, our exploration of DNA motif sequencing through suffix trees has yielded valuable insights into the efficiency of pattern recognition in biological data. This project has not only enhanced our technical skills but also emphasized the relevance of computational techniques in advancing genetic research.

HOW TO RUN THE CODES OF THE ALGORITHMS: NAIVE, UKKONEN and MOTIF SEARCH:

To run the DNA motif sequencing project code in Visual Studio Code, first, ensure you have a C++ compiler installed on your system. Open the project folder in VS Code and locate the main code file. Ensure that the data file containing the DNA sequences is in the same directory as your code file for easy access. Use the integrated terminal in VS Code to compile the code by running the command g++ -o motif_sequencer your_code_file.cpp, replacing your_code_file.cpp with the actual file name. After compilation, execute the program by typing ./motif_sequencer in the terminal. The program will then read the sequences from the data file, process them using the selected algorithms, and output the results to the terminal or a specified output file, depending on your implementation.


