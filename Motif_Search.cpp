// Implementing Ukkonen's algorithm to construct a suffix tree and searching for motifs in the suffix tree
// Time complexity: O(n) for constructing the suffix tree, O(m) for searching for a motif of length m
// Space complexity: O(n) for the suffix tree

// C++ Libraries
#include <chrono>  // To measure time taken to construct the suffix tree and motif search
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

#define INITIAL_SIZE 2048 
#define GROWTH_FACTOR 2 
#define ALPHABET_SIZE 5 // A, T, G, C, and $

// Global Variables and Constants
const int oo = 1 << 25;
int root, last_added, current_position, needSL, r, active_node, active_edge_index, active_length;

using namespace std;

// Node structure to represent a node in the suffix tree
struct node {
    int start;
    int end;
    int suffix_link;
    vector<int> nextIndices;

    node() : nextIndices(ALPHABET_SIZE, 0), start(0), end(0), suffix_link(0) {}

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
    tree.push_back(nd);
    return ++last_added;
}

char active_edge() {
    return input_string[active_edge_index];
}

void add_SL(int node) {
    if (needSL > 0) tree[needSL].suffix_link = node;
    needSL = node;
}

bool walk_down(int node) {
    if (active_length >= tree[node].edge_length()) {
        active_edge_index += tree[node].edge_length();
        active_length -= tree[node].edge_length();
        active_node = node;
        return true;
    }
    return false;
}

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
    root = active_node = new_node(-1, -1);
}

void extend_suffix_tree(char new_char) {
    input_string += new_char;
    current_position++;
    needSL = 0;
    r++;

    while (r > 0) {
        if (active_length == 0) {
            active_edge_index = current_position;
        }

        int edge_index = char_to_index(active_edge());
        if (tree[active_node].nextIndices[edge_index] == 0) {
            int leaf_node = new_node(current_position);
            tree[active_node].nextIndices[edge_index] = leaf_node;
            add_SL(active_node);
        } else {
            int next_node = tree[active_node].nextIndices[edge_index];
            if (walk_down(next_node)) continue;

            if (input_string[tree[next_node].start + active_length] == new_char) {
                active_length++;
                add_SL(active_node);
                break;
            }

            int split_node = new_node(tree[next_node].start, tree[next_node].start + active_length);
            tree[active_node].nextIndices[edge_index] = split_node;

            int new_leaf = new_node(current_position);
            tree[split_node].nextIndices[char_to_index(new_char)] = new_leaf;

            tree[next_node].start += active_length;
            tree[split_node].nextIndices[char_to_index(input_string[tree[next_node].start])] = next_node;

            add_SL(split_node);
        }
        r--;

        if (active_node == root && active_length > 0) {
            active_length--;
            active_edge_index = current_position - r + 1;
        } else {
            active_node = (tree[active_node].suffix_link > 0) ? tree[active_node].suffix_link : root;
        }
    }
}

// Function to read the content of the file into a dynamically allocated string
char* readFile(const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file." << endl;
        exit(1);
    }

    int capacity = INITIAL_SIZE;
    int length = 0;
    char* buffer = (char*)malloc(capacity * sizeof(char));
    char ch;

    while (file.get(ch)) {
        buffer[length++] = ch;
        if (length >= capacity) {
            capacity *= GROWTH_FACTOR;
            buffer = (char*)realloc(buffer, capacity * sizeof(char));
        }
    }

    buffer[length] = '\0';
    file.close();

    buffer = (char*)realloc(buffer, (length + 2) * sizeof(char));
    buffer[length] = '$';
    buffer[length + 1] = '\0';

    return buffer;
}

// Function to count the number of leaf nodes in a subtree
int count_leaf_nodes(int node) {
    if (tree[node].nextIndices[0] == 0 && tree[node].nextIndices[1] == 0 &&
        tree[node].nextIndices[2] == 0 && tree[node].nextIndices[3] == 0 &&
        tree[node].nextIndices[4] == 0) {
        return 1;
    }

    int count = 0;
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        if (tree[node].nextIndices[i] > 0) {
            count += count_leaf_nodes(tree[node].nextIndices[i]);
        }
    }
    return count;
}

// Function to search motif and return the number of occurrences
int search_motif(const string &motif) {
    int current_node = root;
    int length = motif.length();
    int index = 0;

    while (index < length) {
        int edge_index = char_to_index(motif[index]);
        if (tree[current_node].nextIndices[edge_index] == 0) {
            return 0;
        }

        current_node = tree[current_node].nextIndices[edge_index];
        int edge_start = tree[current_node].start;
        int edge_length = tree[current_node].edge_length();

        for (int j = 0; j < edge_length && index < length; ++j) {
            if (input_string[edge_start + j] != motif[index]) {
                return 0;
            }
            index++;
        }
    }

    return count_leaf_nodes(current_node);
}

// Driver function
int main() {
    // Read the input string from the file
    char* input = readFile("Data.txt");
    string input_str(input);

    // Measure time to construct the suffix tree
    auto start_time = chrono::high_resolution_clock::now();
    
    st_init();
    for (char c : input_str) {
        extend_suffix_tree(c);
    }

    auto end_time = chrono::high_resolution_clock::now();
    auto build_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
    cout << "Time taken to build the suffix tree: " << build_time << " milliseconds." << endl;

    // Loop to search for motifs until the user enters 'Q'
    string motif;
    while (true) {
        cout << "\nEnter the motif to search for (or 'Q' to quit): ";
        cin >> motif;

        if (motif == "Q" || motif == "q") {
            break;
        }

        // Measure time to search the motif
        start_time = chrono::high_resolution_clock::now();

        int count = search_motif(motif);

        end_time = chrono::high_resolution_clock::now();
        auto search_time = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
        cout << "Time taken to search for the motif: " << search_time << " milliseconds." << endl;

        if (count > 0) {
            cout << "The motif \"" << motif << "\" is present in the string " << count << " times." << endl;
        } else {
            cout << "The motif \"" << motif << "\" is not present in the string." << endl;
        }
    }

    return 0;
}
