/* 
 * Program to simulate the LFU page replacement algorithm
 * Uses a vector to keep track of cache, with the end of the vector
 * holding the most recently used, and the beginning holding the least
 * recently used.
 */

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include <cctype>

using namespace std;

/* The following function is referenced from http://stackoverflow.com/questions/8888748/how-to-check-if-given-c-string-or-char-contains-only-digits
 *
 * The member function string::find_first_not_of returns the position of 
 * the first character than is not a digit. If all characters in the string
 * are one of the specified characters (0-9), then it returns string::npos.
 * The member string::npos has the value of the end of the string.
 *
 */

bool is_digit(const string &str)
{
	return str.find_first_not_of("0123456789") == string::npos;
}

int main (int argc, char ** argv)
{
	if(argc != 2) {
		cerr << "Incorrect number of arguments" << endl;
		return 0;
	}

	/* Variables to store command line arguments */
	int total_pages = atoi(argv[1]);

	int page_requests = 0;
	int page_faults = 0;
	bool found_page = false;
	string line;
	vector<int> cache;
	vector<int>::iterator it;

		for (line; getline(cin, line);) {
	
			string buffer;
			stringstream ss(line);

			vector<string> tokens;

			while (ss >> buffer)
				tokens.push_back(buffer);

			/* Check if the line starts with a number
			 * If not, read the next line
			 */
			if(!is_digit(tokens[0]))
			{
				continue;
			}

			page_requests++;
			
			/* Store number from stream */
			stringstream s(line);
			int number;

			s >> number;
			found_page = false;

			if(cache.size() < total_pages) {

				/* 
				 * Check if a number was found in the cache.
				 * If not, add it to end of vector
				 */
				it = cache.begin();
				while(it != cache.end())
				{
					if(*it == number) {

						found_page = true;
						cache.erase(it);
						cache.push_back(number);
						break;
					}
					else
						++it;
				}

				if(!found_page) {
					cache.push_back(number);
					page_faults++;
					cout << number << endl;
				}
			} else {
				it = cache.begin();

				/* 
				 * If the cache is full, and a number is found,
				 * move it to the end of the cache.
				 */

				while(it != cache.end())
				{
					if(*it == number) {
						found_page = true;
						cache.erase(it);
						cache.push_back(number);
						break;
					}
					else
						++it;
				}
				
				/* 
				 * If there is a page fault and the cache is full,
				 * remove the least recently used page (the head) and
				 * add the new page to the end.
				 */
				if(!found_page) {
					cache.push_back(number);
					cache.erase(cache.begin());
					page_faults++;
					cout << number << endl;
				}
					
			}

		}
	cerr << page_requests << endl;
	cerr << page_faults << endl;

	return 0;
}
