#ifndef IOH
#define IOH

void getRasterInfo(char * fileName, int * nRow, int * nCol, double * xMin, double * yMax, double * cellSize);
void writeGeoTiffF(char * fileName, float * result, int nRow, int nCol, double xMin, double yMax, double cellSize);

#endif
