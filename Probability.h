#pragma once

#ifndef Probability_H
#define Probability_H

#include <iostream>
#include <vector>
#include <random>
#include <limits>	// for getting maximum int value

// return a random double between 0 and 1
double get_random();

// generate a uniform distribution based on the value of
//  the int argument, and locate the double within it
int get_bucket(int, double);

// select a number of unique random ints from a range of ints,
//  low <= int <= high
std::vector<int> random_subset(int number, int low, int high);

#endif