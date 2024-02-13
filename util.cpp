#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{

    std::set<std::string> words;

    std::string sub;
    int start = 0;

    for(size_t i = 0; i < rawWords.length(); i++) {
        // if the curr character is punctuation
        if(std::ispunct(rawWords[i]) || rawWords[i] == ' ') {
            // std::cout << i << std::endl;
            // create a substring that stores the current word up until the punct
            sub = rawWords.substr(start, i - start); 
            // trims rawwords of any whitespace
            trim(sub);
            // convert to lower
            sub = convToLower(sub);
            // if the length of the word is greater than 2, then add to set of words
            if(sub.length() >= 2) {
                words.insert(sub);
            }
            // increment start to the index after the punctuation
            start = i + 1;
        }
    }
    sub = rawWords.substr(start, rawWords.length() - start); 
    sub = convToLower(trim(sub));

    if(sub.length() >= 2) {
        words.insert(sub);
    }

    return words;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}