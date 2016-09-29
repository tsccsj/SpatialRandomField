# SpatialRandomField
SpatialRandomField is a software that generates uniform-distributed spatial random fields using a moving average approach. It is both a stand-alone tool, and an integrated part of QuantumPopulationGeo-Analytics.

# Software instruction at
http://digitalpopulations.pbworks.com/w/page/110082820/SpatialRandomFieldGenerator

What does it do?
 1. Generate normal-distributed spatial noise
    i. Each raster cell is assigned a random number from a normal distribution
 2. Generate a normal-distributed spatial random field from the spatial noise
    i. A new raster is created, with each cell value calculated using a moving average filter function from the original spatial noise
 3. Covert the normal-distributed spatial random field to a uniform-distributed random field
 4. Output the random field as a GeoTIFF

# Prerequisites
 GDAL

# To run
Find the compiled executable (i.e. DigPopPopulationDensity) and run it with the following arguments: <br/>
  RandomField OutputFieldName ReferenceFileName Distance Exponent flat seed(optional)

Input arguments:
 1. OutputFieldName: the output GeoTiff
 2. ReferenceFileName: the input GeoTiff from which the software gets spatial bounds, cell size and spatial reference system
 3. Distance: the radius of spatial moving window (filtering function)
 4. Exponent: the exponent of the filtering function
 5. Flat: the radius in the filtering function where all cells within such radius have the same maximum weight
 6. Seed(optional): the initial seed to generate random numbers
 
