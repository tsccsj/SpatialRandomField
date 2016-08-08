#ifndef FIELDH
#define FIELDH
void getNoise(double * noise, int cellCount);
void getNoise(double * noise, int cellCount, unsigned seed);
void getMask(double * mask, int bound, double cellSize, double d, double e, double f);
void generateRandomField(double * noise, double * result, double * mask, int nCol, int nRow, int bound);
void normalToUniform(double * normal, float * uniform, int nCells);
#endif
