#include <stdio.h>
#include <stdlib.h>
#include <gdal.h>
#include <ogr_srs_api.h>
#include <ogr_api.h>
#include <cpl_conv.h>

void getRasterInfo(char * fileName, int * nRow, int * nCol, double * xMin, double * yMax, double * cellSize)
{
	GDALAllRegister();

	GDALDatasetH dataSet;
	double adfGeoTransform[6];
	
	
	if(NULL == (dataSet = GDALOpen(fileName, GA_ReadOnly)))
	{
		printf("ERROR: Can't open input file%s.\n", fileName);
		exit(1);		
	}

	GDALGetGeoTransform(dataSet, adfGeoTransform);

	*xMin = adfGeoTransform[0];
	*yMax = adfGeoTransform[3];
	if(adfGeoTransform[1] != -adfGeoTransform[5])
	{
		printf("ERROR: The resolution along X and Y are different\n");
		exit(1);
	}
	*cellSize = adfGeoTransform[1];

	*nCol = GDALGetRasterXSize(dataSet);
	*nRow = GDALGetRasterYSize(dataSet);


	GDALClose(dataSet);
}

void writeGeoTiffF(char * fileName, float * result, int nRow, int nCol, double xMin, double yMax, double cellSize)
{
	
	GDALAllRegister();
	OGRRegisterAll();

	GDALDatasetH hDstDS;
	GDALDriverH hDriver;
	GDALRasterBandH hBand;
	double adfGeoTransform[6];

	char *papszOptions[] = {"COMPRESS=LZW",NULL};
	const char *pszFormat="GTiff";

	if(NULL == (hDriver = GDALGetDriverByName(pszFormat)))
	{
		printf("ERROR: hDriver is null cannot output using GDAL\n");
		exit(1);
	}
	
	hDstDS = GDALCreate(hDriver, fileName, nCol, nRow, 1, GDT_Float32, papszOptions);

	adfGeoTransform[0] = xMin;
	adfGeoTransform[1] = cellSize;
	adfGeoTransform[2] = 0;
	adfGeoTransform[3] = yMax;
	adfGeoTransform[4] = 0;
	adfGeoTransform[5] = -cellSize;

	GDALSetGeoTransform(hDstDS,adfGeoTransform);

	hBand=GDALGetRasterBand(hDstDS,1);
	GDALSetRasterNoDataValue(hBand,-1);
	GDALRasterIO(hBand, GF_Write, 0, 0, nCol, nRow, result, nCol, nRow, GDT_Float32, 0, 0 );
	
	GDALClose(hDstDS);

	return;
}

