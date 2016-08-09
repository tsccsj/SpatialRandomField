#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "io.h"
#include "field.h"

int main(int argc, char ** argv)
{
	if(argc < 6)
	{
		printf("Incorrect number of input arguments: \n\tRandomField <OutputFieldName> <ReferenceFileName> <Distance> <Exponent> <flat> <seed(optional)>\n");
		return 1;
	}

	double d = atof(argv[3]);
	double e = atof(argv[4]);
	double f = atof(argv[5]);

	bool withSeed = false;

	unsigned seed;

	if(argc > 6)
	{
		seed = atoi(argv[6]);
		withSeed = true;
	}

	double xMin, xMax, yMin, yMax, cellSize;
	int nCol, nRow, bound;

	
	getRasterInfo(argv[2], &nRow, &nCol, &xMin, &yMax, &cellSize);

	xMax = xMin + nCol * cellSize;
	yMin = yMax - nRow * cellSize;

	bound = d / cellSize;

	printf("Generating spatial random field of %d(col) X %d(row)\n", nCol, nRow);
	printf("Cell Size: %lf\n", cellSize);
	printf("xRange: %lf ~ %lf\n", xMin, xMax);
	printf("yRange: %lf ~ %lf\n", yMin, yMax);
	printf("D=%lf\tE=%lf\tF=%lf\n", d, e, f);

	double * noise;
	double * mask;
	double * normal;
	float * uniform;

	if(NULL == (noise = (double *) malloc ((nCol + 2 * bound) * (nRow + 2 * bound) * sizeof(double))))
	{
		printf("ERROR: Out of memory in line %d of file %s!\n", __LINE__, __FILE__);
		exit(1);
	}

	if(NULL == (mask = (double *) malloc ((1 + 2 * bound) * (1 + 2 * bound) * sizeof(double))))
	{
		printf("ERROR: Out of memory in line %d of file %s!\n", __LINE__, __FILE__);
		exit(1);
	}

	if(NULL == (normal = (double *) malloc (nCol * nRow * sizeof(double))))
	{
		printf("ERROR: Out of memory in line %d of file %s!\n", __LINE__, __FILE__);
		exit(1);
	}

	if(NULL == (uniform = (float *) malloc (nCol * nRow * sizeof(float))))
	{
		printf("ERROR: Out of memory in line %d of file %s!\n", __LINE__, __FILE__);
		exit(1);
	}

	if(withSeed)
	{
		getNoise(noise, (nCol + 2 * bound) * (nRow + 2 * bound), seed);
	}
	else
	{
		getNoise(noise, (nCol + 2 * bound) * (nRow + 2 * bound));
	}

	getMask(mask, bound, cellSize, d, e, f);
	
	generateRandomField(noise, normal, mask, nCol, nRow, bound);

	free(noise);
	free(mask);

	normalToUniform(normal, uniform, nRow * nCol);

	free(normal);

	writeGeoTiffF(argv[1], uniform, nRow, nCol, xMin, yMax, cellSize);

	free(uniform);

	
	return 0;
}
