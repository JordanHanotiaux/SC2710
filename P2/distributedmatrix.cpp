#include <iostream>
#include <cassert>
#include "distributedmatrix.hpp"

using namespace std;

// Constructors

DistributedMatrix :: DistributedMatrix(const Matrix& matrix, int numProcesses){
    MPI_Comm_rank(MPI_COMM_WORLD, &this->rank);

    (*this).globalRows = matrix.numRows();
    (*this).globalCols = matrix.numCols();
    (*this).numProcesses = numProcesses

    (*this).localCols = globalCols / numProcesses;
    int remainingCols = globalCols % numProcesses;
    
    (*this).startCol = rank * localCols + min(rank, remainingCols);
    if (rank < remainingCols) {
        (*this).localCols++;
    }
    
    (*this).localData = getLocalData();
}