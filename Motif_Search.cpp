//Implementing Ukkonen's algorithm to construct a suffix tree and searching for motifs in the suffix tree
//Time complexity: O(n) for constructing the suffix tree, O(m) for searching for a motif of length m
//Space complexity: O(n) for the suffix tree

//C++ Libraries
#include <chrono>  // To measure time taken to construct the suffix tree
#include <vector>  
#include <iostream>
#include <fstream>
#include <string>

// Constants for buffer size and growth factor
#define INITIAL_SIZE 2048 
#define GROWTH_FACTOR 2 
#define ALPHABET_SIZE 5 // A, T, G, C, and $

//Global Variables and Constants
const int oo = 1 << 25;  // Represents infinity
int root, last_added, current_position, needSL, r, active_node, active_edge_index, active_length;

using namespace std;

// Node structure to represent a node in the suffix tree
struct node {
    int start; //Start index of the edge
    int end;    // End index of the edge
    int suffix_link; // suffix link
    vector<int> nextIndices;  // Dynamic array to store the next node pointers

    // Constructor to initialize the node
    node() : nextIndices(ALPHABET_SIZE, 0), start(0), end(0), suffix_link(0) {}

    // Calculate the length of the edge
    int edge_length() {
        return min(end, current_position + 1) - start;
    }
};

// Global variables
vector<node> tree;
string input_string;

// Function to map 'A', 'T', 'G', 'C', '$' to indices
int char_to_index(char c) {
    switch (c) {
        case 'A': return 0;
        case 'T': return 1;
        case 'G': return 2;
        case 'C': return 3;
        case '$': return 4;  
        default: return -1;
    }
}

// Function to initialize a new node
int new_node(int start, int end = oo) {
    node nd;
    nd.start = start;
    nd.end = end;
    nd.suffix_link = 0;
    tree.push_back(nd);  // Add the new node to the end of the tree vector
    return ++last_added; 
}

// Create a new leaf node
char active_edge() {
    return input_string[active_edge_index];
}

// Add a suffix link
void add_SL(int node) {
    if (needSL > 0) tree[needSL].suffix_link = node;
    needSL = node;
}

// Check if we can move further down the tree from the given node
bool walk_down(int node) {
    if (active_length >= tree[node].edge_length()) {
        active_edge_index += tree[node].edge_length();
        active_length -= tree[node].edge_length();
        active_node = node;
        return true;
    }
    return false;
}

// Initialize the suffix tree
void st_init() {
    needSL = 0;
    last_added = -1;
    current_position = -1;
    r = 0;
    active_node = 0;
    active_edge_index = 0;
    active_length = 0;
    tree.clear();  
    tree.reserve(2);
    root = active_node = new_node(-1, -1);  // Initialize root node
}

// Extension function for Ukkonen's algorithm to add characters to the suffix tree
void extend_suffix_tree(char new_char) {
    input_string += new_char;  // Add the new character to the input_string
    current_position++;  
    needSL = 0;  // Reset the suffix link necessity
    r++;  // Increment the active extension count

    while (r > 0) {
        if (active_length == 0) {
            active_edge_index = current_position;  // Set active edge index
        }

        int edge_index = char_to_index(active_edge());
        if (tree[active_node].nextIndices[edge_index] == 0) {
            int leaf_node = new_node(current_position);  // Create a new leaf node
            tree[active_node].nextIndices[edge_index] = leaf_node;  // Add leaf to the active node's children
            add_SL(active_node); // Link the suffix
        } else {
            int next_node = tree[active_node].nextIndices[edge_index]; // Get the next node
            if (walk_down(next_node)) continue; // If walked down, continue with the loop

            if (input_string[tree[next_node].start + active_length] == new_char) {
                active_length++;  // Increase the active length
                add_SL(active_node); // Link the suffix
                break;  // Exit the loop as the current character matched
            }

            int split_node = new_node(tree[next_node].start, tree[next_node].start + active_length);
            tree[active_node].nextIndices[edge_index] = split_node; // Update the active node's edge to the new split node

            int new_leaf = new_node(current_position); // Create a new leaf for the current position
            tree[split_node].nextIndices[char_to_index(new_char)] = new_leaf; // Add new leaf to the split node

            tree[next_node].start += active_length; // Update the existing edge
            tree[split_node].nextIndices[char_to_index(input_string[tree[next_node].start])] = next_node;

            add_SL(split_node); // Link the suffix
        }
        r--; // Decrease the active extension count

        if (active_node == root && active_length > 0) {
            active_length--; // Decrease the active length
            active_edge_index = current_position - r + 1; // Move to the next character
        } else {
            active_node = (tree[active_node].suffix_link > 0) ? tree[active_node].suffix_link : root; // Navigate suffix link or return to root
        }
    }
}

// Function to calculate the space occupied by the suffix tree in bytes
size_t calculate_space() {
    size_t total_size = 0;
    for (const auto& nd : tree) {
        total_size += sizeof(nd.start) + sizeof(nd.end) + sizeof(nd.suffix_link); 
        total_size += nd.nextIndices.capacity() * sizeof(int);  
    }
    return total_size;
}

// Function to print the suffix tree
void print_suffix_tree(int node, const string &input, const string &prefix) {
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (tree[node].nextIndices[i] > 0) {
            int child = tree[node].nextIndices[i];
            string edge = input.substr(tree[child].start, tree[child].edge_length());
            cout << prefix << edge << endl;  // Print the edge label
            print_suffix_tree(child, input, prefix + edge);  // Recursive call
        }
    }
}

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

// Function to count the number of leaf nodes in a subtree
int count_leaf_nodes(int node) {
    // If the current node is a leaf, return 1
    if (tree[node].nextIndices[0] == 0 && tree[node].nextIndices[1] == 0 &&
        tree[node].nextIndices[2] == 0 && tree[node].nextIndices[3] == 0 &&
        tree[node].nextIndices[4] == 0) {
        return 1;
    }

    int count = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (tree[node].nextIndices[i] > 0) {
            count += count_leaf_nodes(tree[node].nextIndices[i]);  // Recursive count of leaf nodes
        }
    }
    return count;  
}

// Function to count occurrences of motif
int search_motif(const string &motif) {
    int current_node = root;
    int length = motif.length();
    int index = 0;  // Current index in the motif

    while (index < length) {
        int edge_index = char_to_index(motif[index]);
        if (tree[current_node].nextIndices[edge_index] == 0) {
            return 0;  // Motif not found
        }

        current_node = tree[current_node].nextIndices[edge_index];
        int edge_start = tree[current_node].start;
        int edge_length = tree[current_node].edge_length();

        // Check how much of the motif matches the edge
        for (int j = 0; j < edge_length && index < length; ++j) {
            if (input_string[edge_start + j] != motif[index]) {
                return 0;  // Motif not found
            }
            index++;
        }
    }

    return count_leaf_nodes(current_node); 
}

//Driver function
int main() {

   // Read the input string from the file
    char* input = readFile("Data.txt");
    string input_str(input);  // Convert char* to string

    //Construct the suffix tree
    st_init(); 
    for (char c : input_str) {
        extend_suffix_tree(c);
    }

    // Loop to search for motifs until the user enters 'Q'
    string motif;
    while (true) {
        cout << "\nEnter the motif to search for (or 'Q' to quit): ";
        cin >> motif;

        if (motif == "Q" || motif == "q") {
            break;  // Exit the loop if user enters 'Q' or 'q'
        }

        // Search for the motif in the suffix tree and get the count
        int count = search_motif(motif);
        if (count > 0) {
            cout << "The motif \"" << motif << "\" is present in the string " << count << " times." << endl;
        } else {
            cout << "The motif \"" << motif << "\" is not present in the string." << endl;
        }
    }

    return 0;
}
