/* Author:	Ryan Armstrong
 * Project:	OLA 2 
 * Due:		October 25, 2018
 * Instructor: 	Dr. Phillips
 * Course:	CSCI 4350-001
 */
#include <iostream>
#include <random>
#include <stdlib.h>
#include <math.h>
#include "SumofGaussians.h"

using namespace std;

#define CYCLES 100000

int main(int argc, char** argv)
{
	int seed 	= atoi(argv[1]);
	int dims 	= atoi(argv[2]);
	int centers	= atoi(argv[3]);

	srand(seed);
	SumofGaussians sog(dims, centers);
	uniform_real_distribution<double> stepSizeDist(-0.01, 0.01);
	uniform_real_distribution<double> probabilityDist(0.0, 1.0);
	default_random_engine gen;

	// get random starting location in D-Cube
	double cur[dims];
	for (int i = 0; i < dims; i++)
		cur[i] = getRandom() * 10;

	// perform simulated annealing with a max of CYCLES cyles
	// Using additive trigonometric cooling curve for T 
	double T_start 	= 1.0;
	double T_end	= pow(10, -8);
	double T 	= T_start; // temperature
	double Tk;
	//double m;
	//double bestVal;
	for (int i = 0; i < CYCLES; i++)
	{
		double curVal = sog.eval(cur);

		// print current location and value of function
		for (int j = 0; j < dims; j++)
			cout << cur[j] << ' ';
		cout << curVal << endl;

		// generate random neighbor
		double neighbor[dims];
		for (int j = 0; j < dims; j++)
			neighbor[j] = cur[j] + stepSizeDist(gen);
		double neighborVal = sog.eval(neighbor);

		// decide whether we should accept the neighbor or not
		double prob = exp((neighborVal - curVal) / T);
		if (neighborVal > curVal)
		{
			for (int j = 0; j < dims; j++)
				cur[j] = neighbor[j];
			curVal = neighborVal;
		}
		else if (probabilityDist(gen) <= prob)
		{
			for (int j = 0; j < dims; j++)
				cur[j] = neighbor[j];
			curVal = neighborVal;
		}
		//bestVal = (curVal > bestVal) ? curVal : bestVal;
	
		// calculate temperature
		Tk = T_end + 0.5 * (T_start - T_end) * (1 + cos(i * M_PI / CYCLES));
		//m = 1 + (curVal - bestVal) / curVal;
		//T = m * Tk;
		T = Tk;
	}

	return 0;
}
