#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <random>

using namespace std;

double nextNormalRandom()
{	
	static std::default_random_engine generator;
	static std::normal_distribution<double> distribution(0.0,1.0);

	return distribution(generator);
}

double nextNormalRandom(unsigned seed)
{	
	static std::default_random_engine generator(seed);
	static std::normal_distribution<double> distribution(0.0,1.0);

	return distribution(generator);
}
/*
double nextNormalRandom()
{
	static bool first = true;
	static double unif[2];
	static double random[2];

	static std::default_random_engine generator;
	static std::uniform_real_distribution<double> distribution(0.0,1.0);

	if(first)
	{
		unif[0] = distribution(generator);
		unif[1] = distribution(generator);

		random[0] = sqrt(-2*log(unif[0])) * cos(unif[1] * 2 * M_PI);	
		random[1] = sqrt(-2*log(unif[0])) * sin(unif[1] * 2 * M_PI);	
		
		first = false;
		return random[0];
	}
	else
	{
		first = true;
		return random[1];
	}
}
*/

void getNoise(double * noise, int cellCount)
{
	for(int i = 0; i < cellCount; i++)
	{
		noise[i] = nextNormalRandom();	
	}
}

void getNoise(double * noise, int cellCount, unsigned seed)
{
	for(int i = 0; i < cellCount; i++)
	{
		noise[i] = nextNormalRandom(seed);	
	}
}

void getMask(double * mask, int bound, double cellSize, double d, double e, double f)
{
	double sum = 0.0;
	double distance;
	double weight;

	int nCol = 2 * bound + 1;

	for(int i = 0; i < 2 * bound + 1; i++)
	{
		for(int j = 0; j < 2 * bound + 1; j ++)
		{
			distance = sqrt((i - bound) * (i - bound) + (j - bound) * (j - bound)) * cellSize; 
			
			if(distance <= f)
			{
				weight = 1.0;
			}
			else if(distance >= d)
			{
				weight = 0.0;
			}
			else
			{
				weight = pow((d - distance)/(d - f), e);
			}

			sum += weight * weight;

			mask[i * nCol + j] = weight;
		}
	}
	
	sum = sqrt(sum);

	for(int i = 0; i <= 2 * bound; i++)
	{
		for(int j = 0; j <= 2 * bound; j++)
		{
			mask[i * nCol + j] /= sum;
		}
	}

}

void generateRandomField(double * noise, double * result, double * mask, int nCol, int nRow, int bound)
{
	int maskSize = 2 * bound + 1;
	int noiseCol = 2 * bound + nCol;
	double value;
	for(int i = 0; i < nRow; i++)
	{
		for(int j = 0; j < nCol; j++)
		{
			value = 0.0f;
			for(int im = 0; im < maskSize; im ++)
			{
				for(int jm = 0; jm < maskSize; jm ++)
				{
					value += mask[im * maskSize + jm] * noise[(i + im) * noiseCol + j + jm];
				}
			}
			result[i * nCol + j] = value;
		}
	}	
}
/*
double erf(double x)
{  
	double y = 1.0 / ( 1.0 + 0.3275911 * x);
	return 1 - (((((
        + 1.061405429  * y
        - 1.453152027) * y
        + 1.421413741) * y
        - 0.284496736) * y 
        + 0.254829592) * y) 
        * exp (-x * x);      
}
*/
void normalToUniform(double * normal, float * uniform, int nCells)
{
	double sqrt2 = sqrt(2.0);
	for(int i = 0; i < nCells; i++)
	{
		uniform[i] = 0.5 * (1 + erf(normal[i] / sqrt2));
		if(uniform[i] < 0)
		{
			uniform[i] = 0.0;
		}
		if(uniform[i] > 1.0)
		{
			uniform[i] = 1.0;
		}
	}
}
