// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> results;
    bool complete = true;
    for (size_t i = 0; i<in.length(); i++) {
        if (in[i] == '-') {
            complete = false;
            // Recurse for all possible letters
            for (int letter = 97; letter<123; letter++) {
                std::string temp = in;
                temp[i] = letter;
                std::set<std::string> returned = wordle(temp, floating, dict);
                if (returned.size()>0) {
                    for (std::set<std::string>::iterator it = returned.begin(); it != returned.end(); ++it) {
                        results.insert(*it);
                    }
                }
            }
        }
    }
    if (complete) {
        // If it's a real English word
        if (dict.find(in) != dict.end()) {
            // Check if all floating contained
            bool containsAll = true;
            for (size_t i = 0; i<floating.length(); i++) {
                bool contains = false;
                for (size_t j = 0; j<in.length(); j++) {
                    if (in[j] == floating[i]) {
                        contains = true;
                        break;
                    }
                }
                if (!contains) {
                    containsAll = false;
                    break;
                }
            }
            // Add to results set if everything about word is satisfactory
            if (containsAll) {
                results.insert(in);
            }
        }
    }
    return results;
}

// Define any helper functions here
