
// Implementation of Construction of Suffix Tree using Naive Approach
// Time complexity: O(n^2)
// Space complexity: O(n^2)
// Recommended size of input string: n <= 10^4


// C++ Libraries
#include <cstdlib>   
#include <iostream>  
#include <vector>   
#include <cstring>   
#include <fstream>  
#include <chrono>   // For measuring time


// Constants for buffer size, max character and growth factor
#define INITIAL_SIZE 2048 
#define GROWTH_FACTOR 2   
#define MAX_CHAR 256 


// Suffix Tree Node class
class SuffixTreeNode {
public:
    std::vector<SuffixTreeNode*> children; // Array of pointers pointing to child nodes
    int start;                               // Starting index of the edge
    int* end;                                // End index of the edge
    int suffixIndex;                         // Suffix index (for leaves)

    // Constructor to initialize the suffix tree node
    SuffixTreeNode(int start, int* end) : start(start), end(end), suffixIndex(-1) {
        children.resize(MAX_CHAR, nullptr); // Initialize children with nullptrs
    }
};


// Global variable to store the input string
char* input_string;


// Function to read the content of the file into a dynamically allocated string
char* readFile(const char* filename) {

    std::ifstream file(filename); 
    if (!file.is_open()) {
        std::cerr << "Error opening file." << std::endl; // Error handling
        exit(1);
    }

    int capacity = INITIAL_SIZE; 
    int length = 0;               
    char* buffer = (char*)malloc(capacity * sizeof(char)); // Allocate initial buffer

    char ch;

    // Read characters from the file until EOF
    while (file.get(ch)) {
        buffer[length++] = ch; 

        // Expand buffer if needed
        if (length >= capacity) {
            capacity *= GROWTH_FACTOR; 
            buffer = (char*)realloc(buffer, capacity * sizeof(char));
        }
    }

    buffer[length] = '\0'; // Null-terminate the string
    file.close();

    // Add a termination character '$' to the string
    buffer = (char*)realloc(buffer, (length + 2) * sizeof(char)); 
    buffer[length] = '$';
    buffer[length + 1] = '\0'; // Proper null termination

    return buffer; 
}


// Function to build the suffix tree using naive approach
SuffixTreeNode* buildSuffixTree(char* input) {
    input_string = input; 
    int length = strlen(input_string); 

    // Create the root node of the suffix tree
    SuffixTreeNode* root = new SuffixTreeNode(-1, new int(-1));

    // Loop through all suffixes to build the tree
    for (int i = 0; i < length; i++) {
        SuffixTreeNode* node = root; // Start from the root node
        for (int j = i; j < length; j++) {
            int index = static_cast<unsigned char>(input_string[j]); 
            if (node->children[index] == nullptr) {

                // Create a new leaf node if no edge exists for this character
                node->children[index] = new SuffixTreeNode(j, new int(length - 1));
                node->children[index]->suffixIndex = i; // Store suffix index
            }
            node = node->children[index]; // Move to the child node
        }
    }
    return root; // Return the root of the suffix tree
}


// Utility function to print the edges of the suffix tree
void printEdge(int start, int end) {
    for (int i = start; i <= end; i++) {
        std::cout << input_string[i]; // Print characters from start to end index
    }
}


// Recursive function to print the suffix tree in a structured format
void printSuffixTree(SuffixTreeNode* node, int level) {
    if (node == nullptr) return; // Base case for recursion

    // If it's not the root node and has a valid start position, print the edge
    if (node->start != -1) {
        for (int k = 0; k < level; k++) std::cout << "    "; 
        printEdge(node->start, *(node->end)); // Print the edge from the parent to this node
        std::cout << std::endl; 
    }

    // Recursively print all children
    for (size_t i = 0; i < MAX_CHAR; i++) {
        if (node->children[i] != nullptr) {
            printSuffixTree(node->children[i], level + 1);
        }
    }
}


// Function to calculate the total memory occupied by the suffix tree
size_t calculateMemoryUsage(SuffixTreeNode* node) {
    if (node == nullptr) return 0; // Base case for recursion

    size_t totalMemory = sizeof(SuffixTreeNode);
    for (size_t i = 0; i < MAX_CHAR; i++) {
        totalMemory += calculateMemoryUsage(node->children[i]); 
    }
    return totalMemory; 
}


// Free the suffix tree to prevent memory leaks
void freeSuffixTree(SuffixTreeNode* node) {
    if (node == nullptr) return; // Base case for recursion

    for (size_t i = 0; i < MAX_CHAR; i++) {
        if (node->children[i] != nullptr) {
            freeSuffixTree(node->children[i]); 
        }
    }
    delete node->end; 
    delete node; 
}


// Driver function

int main() {

    // Read the file content and add '$' termination character
    char* input = readFile("Data.txt");

    // Get the length of the input string
    int length = strlen(input);
    std::cout << "Number of characters in the string: " << length << std::endl;

    // Calculate and display the memory occupied by the input string in kilobytes
    size_t inputStringSize = sizeof(char) * (length + 1); // +1 for null terminator
    std::cout << "Memory occupied by the input string: " << inputStringSize / 1024.0 << " KB" << std::endl;

    // Start measuring time for suffix tree construction
    auto start = std::chrono::high_resolution_clock::now();
    SuffixTreeNode* root = buildSuffixTree(input);
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate and display the time taken to construct the suffix tree
    std::chrono::duration<double, std::milli> cpu_time_used = end - start;
    std::cout << "\nTime taken to construct suffix tree: " << cpu_time_used.count() << " ms" << std::endl;

    // Calculate and display memory usage of the suffix tree in kilobytes
    size_t memoryUsage = calculateMemoryUsage(root);
    std::cout << "Memory occupied by the suffix tree: " << memoryUsage / 1024.0 << " KB" << std::endl;

    // Prompt user for printing the suffix tree
    int choice;
    std::cout << "\nEnter 1 to print the suffix tree: ";
    std::cin >> choice;
    if (choice == 1) {
        std::cout << "Suffix Tree for the input file:" << std::endl;
        printSuffixTree(root, 0); // Print the suffix tree
    }

    // Free memory allocated for suffix tree and input text
    freeSuffixTree(root);
    free(input); // Free the input string

    return 0; 
}
