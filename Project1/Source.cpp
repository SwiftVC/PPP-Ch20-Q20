/*
*	Author: CS
*	Date:	2022_03_14
* 
*	The standard chrono header is used to measure the times of
*	using vector or list for storing and sorting N ints.
* 
*	At about N = 400, the list starts to return an improvement in performance which
*	increases with N.
*	(Using Visual Studio standard C++ headers std::list::sort and <algorithm>'s std::sort(iterator, iterator) for std::vector)
* 
*	The list is expected to perform better at push_back as only pointers need to be changed.
*	Whereas the vector must dynamically reallocate and construct it's entirety in frequent intervals as it's allocated space is exceeded.
*	(When every 8 vector elements are added, in the C++ Standard implementation.)
* 
*	The N dependency of time for both looks like O(c^n) (exponential)
*/
#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <random>
#include <iomanip>
#include <string>

inline int rand_int(int min, int max)
{
	static std::default_random_engine ran;
	return std::uniform_int_distribution<>{min, max}(ran);
}

int main() {
	int initial = 400;
	int Nmax = 2000;
	int interval = 50;
	int set_width = 10;

	std::cout << "time (milliseconds) to store-sort a random int N times:\n";
	std::cout << std::string(set_width, ' ');
	std::cout << std::setw(set_width) << "list<int>";
	std::cout << std::string(set_width, ' ');
	std::cout << std::setw(set_width) << "vect<int>\n";

	for (int N = initial; N < Nmax; N += interval)
	{
		std::cout << std::setw(set_width) << "N : " + std::to_string(N);
		{
			auto t1 = std::chrono::system_clock::now();
			std::vector<int> vect;
			for (int i = 0; i < N; i++) {
				vect.push_back(rand_int(INT32_MIN, INT32_MAX));
				std::sort(vect.begin(), vect.end());
			}
			auto t2 = std::chrono::system_clock::now();
			std::cout << std::setw(set_width) << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
		}
		std::cout << std::setw(set_width) << "VS";
		{
			auto t1 = std::chrono::system_clock::now();
			std::list<int> list;
			for (int i = 0; i < N; i++) {
				list.push_back(rand_int(INT32_MIN, INT32_MAX));
				list.sort();
			}
			auto t2 = std::chrono::system_clock::now();
			std::cout << std::setw(set_width) << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << std::endl;
		}
	}
	return 0;
}