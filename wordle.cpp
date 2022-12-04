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
    // prototypes are in header file

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
            // Recurse to fill letters
            std::set<std::string> returned = insertLetter(in, i, floating, dict);
            if (returned.size()>0) addToResults(results, returned.begin(), returned.end());
        }
    }
    if (complete) {
        // Check if all floating contained
        bool containsAll = true;
        std::string temp = in;
        for (size_t i = 0; i<floating.length(); i++) {
            bool contains = false;
            for (size_t j = 0; j<temp.length(); j++) {
                if (temp[j] == floating[i]) {
                    contains = true;
                    temp[j] = '.';
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
            if (dict.find(in) != dict.end()) results.insert(in);
        }
    }
    return results;
}

// Define any helper functions here
void addToResults(std::set<std::string>& results, std::set<std::string>::iterator toAdd, std::set<std::string>::iterator end) {
    if (toAdd != end) {
        results.insert(*toAdd);
        ++toAdd;
        addToResults(results, toAdd, end);
    }
}

std::set<std::string> insertLetter(
    const std::string& in,
    size_t i,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> results;
    std::string temp = in;
    
    if (floating.length() > 0) {
        std::string floatTemp = floating;
        temp[i] = floatTemp[floatTemp.length()-1];
        floatTemp.pop_back();
        std::set<std::string> returned = wordle(temp, floatTemp, dict);
        if (returned.size()>0) addToResults(results, returned.begin(), returned.end());
    } else {
        for (int letter = 97; letter<123; letter++) {
            temp[i] = letter;
            std::set<std::string> returned = wordle(temp, floating, dict);
            if (returned.size()>0) addToResults(results, returned.begin(), returned.end());
        }
    }

    return results;
}