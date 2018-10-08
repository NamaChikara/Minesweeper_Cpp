#include "Probability.h"

double get_random() 
{
	std::random_device rd;		// a uniformly-distributed integer random number generator
	std::mt19937 g(rd());		// mt19937 is a type of the mersenne_twister_engine (a random number generator)
	std::uniform_real_distribution<double> dis(0.0, 1.0);
	double rand = dis(g);
	return rand;
}

int get_bucket(int n, double prob) 
{
	double dn = n;
	for (int i = 0; i < n; ++i) {
		// determine the endpoints of the interval
		double lower = i / dn;
		double higher = (i + 1.0) / dn;
		// check to see if the value lies in the interval
		if (lower <= prob && prob < higher)
			return (int)i;
	}
	// rare case that prob is not in the set [0, 1).
	if (prob == 1)
		return n;
	return -1;	// error in locating prob within the distribution
}

std::vector<int> random_subset(int number, int low, int high)
{
	// declare the output vector
	std::vector<int> subset;

	// generate the set of numbers to pull from
	std::vector<int> remaining;
	for (int i = 0; i <= high - low; ++i)
	{
		remaining.push_back(i + low);
	}

	// this loop selects a random number, and then replaces it with
	//  the tail value to avoid duplicate selection
	double rand_value = 0;
	int location;
	for (int i = 0; i < number; ++i)
	{
		rand_value = get_random();
		// to make make the range of numbers inclusive of low and high,
		//  we must add 1 to the number of buckets
		location = get_bucket(high - low + 1 - i, rand_value);
		subset.push_back(remaining[location]);
		remaining[location] = remaining[remaining.size() - i - 1];
	}

	return subset;
}