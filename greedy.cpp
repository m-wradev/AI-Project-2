/* Author:	Ryan Armstrong
 * Project:	OLA 2 
 * Due:		October 25, 2018
 * Instructor: 	Dr. Phillips
 * Course:	CSCI 4350-001
 */
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SumofGaussians.h"

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		cout << "greedy takes three command-line arguments:\n\t1) random number seed (integer)\n\t2) number of dimensions for SoG function (integer)\n\t3) number of Gaussians for SoG function (integer)" << endl;
		return -1;
	}

	int seed 	= atoi(argv[1]); // seed for random
	int dims	= atoi(argv[2]); // number of dimensions for SoG function (D)
	int centers	= atoi(argv[3]); // number of gaussians (centers) for SoG function (N)

	srand(seed);
	SumofGaussians sog(dims, centers);

	// start at a random point in the D-Cube
	double cur[dims];
	for (int i = 0; i < dims; i++)
		cur[i] = getRandom() * 10;

	// gradient ascent until value of function no longer increases (1e-8 tolerance)
	double curVal 	= sog.eval(cur);
	double prevVal 	= NAN;
	for (double partials[dims]; isnan(prevVal) || curVal - prevVal > pow(10, -8); prevVal = curVal, curVal = sog.eval(cur))
	{
		// print current location and value of function
		for (int i = 0; i < dims; i++)
			cout << cur[i] << ' ';
		cout << curVal << endl;

		// calculate partial derivatives and move up the hill
		sog.deriv(cur, partials);
		for (int i = 0; i < dims; i++)
			cur[i] = cur[i] + 0.01 * partials[i];
	}

	return 0;
}
