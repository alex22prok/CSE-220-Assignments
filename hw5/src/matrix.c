#include "global.h"

/**
 * SparseMatrix converts 2D matrix to sparse matrix representation, 
 * Input:
 *  int row : # rows in M
 *  int col : # columns in M
 *  int** M : pointer to beginning of original 2D matrix
 *  int** S : pointer to preallocated matrix to store sparse matrix
 * 
 * Output : (int) # of non-zero elements found in matrix M  
 */
int SparseMatrix(int row, int col, int** M, int** S){
    //threshold for consideration of sparse (the larger of the two numbers row or col)
    int m = (row > col) ? row : col;
    //# of non-zero elements
    int count = 0;

    //Go thru M to count # of elements
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int val = *(*(M + i) + j); //val = M[i][j]
            if (val != 0) {
                if (count >= m) {
                    return -1;  //Not sparse
                }
                //Store non-zero element metadata into S
                *(*(S + 0) + count) = i;     //Row index
                *(*(S + 1) + count) = j;     //Column index
                *(*(S + 2) + count) = val;   //Value
                count++; //increment
            }
        }
    }

    //If no non-zero elements found
    if (count == 0)
    {
        return 0;
    }

    //Fill remaining entries with 0s
    for (int i = count; i < m; i++) {
        *(*(S + 0) + i) = 0;
        *(*(S + 1) + i) = 0;
        *(*(S + 2) + i) = 0;
    }

    return count;
    abort();
}

/**
 * Addition on two 2D integer matrices M and N storing the result in matrix A.
 *  Supports partial overlap.
 * 
 * Input:
 *  int RM : # rows in M
 *  int CM : # columns in M
 *  int RN : # rows in N
 *  int CN : # columns in N
 *  int RA : # rows in output A
 *  int CA : # columns in output A
 *  int** M : Pointer to matrix M
 *  int** N : Pointer to matrix N
 *  int** A : Pointer to matrix A
 * 
 * Output: (int)
 *  1 if M, N, and A all have the same size
 *  2 if M and N are same size, and A is larger than needed
 *  -1 if M and N are different sizes, but A can hold the intersection
 *  -2 if M and N are different sizes, and A is too small
 *  -3 if M and N are same size, but A is too small
 */
int Addition(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A){
   //Initialize A to zeros
    for(int i = 0; i < RA; i++){
        for(int j = 0; j < CA; j++){
            *(*(A + i) + j) = 0;
        }
    }

    //Calculate overlap dimensions
    int minR = (RM < RN) ? RM : RN; //min(RM, RN) rows of two Matrices
    int minC = (CM < CN) ? CM : CN; //min(CM, CN) cols of two Matrices
    int overlapR = (minR < RA) ? minR : RA; //overlap rows with respect to A
    int overlapC = (minC < CA) ? minC : CA; //overlap cols with respect to A

    //add overlapping elements of M and N and store in A
    for(int i = 0; i < overlapR; i++){
        for(int j = 0; j < overlapC; j++){
            *(*(A + i) + j) = *(*(M + i) + j) + *(*(N + i) + j);
        }
    }

    //M and N have same size
    if(RM == RN && CM == CN){
        if(RA >= RM && CA >= CM){
            if(RA == RM && CA == CM)
                return 1;  //perfectly sized
            else
                return 2;  //oversized
        } else {
            return -3;     //too small
        }
    }

    //M and N are incompatible
    int interR = (RM < RN) ? RM : RN;
    int interC = (CM < CN) ? CM : CN;

    if (RA >= interR && CA >= interC)
        return -1;  // A can hold the full intersection
    else
        return -2;  // A is too small for the full intersection
    abort();
}

/**
 * Multiplication between matrices M and N, storing the result in A.
 *        Supports both valid and partial multiplication based on matrix dimensions.
 * 
 * Input:
 *  int RM : # rows in M
 *  int CM : # columns in M
 *  int RN : # rows in N
 *  int CN : # columns in N
 *  int RA : # rows in output A
 *  int CA : # columns in output A
 *  int** M : Pointer to matrix M
 *  int** N : Pointer to matrix N
 *  int** A : Pointer to matrix A
 * 
 * Output: (int)
 *  1 if multiplication is valid and A is perfectly sized
 *  2 if multiplication is valid and A is larger than needed
 *  -1 if M × N is invalid but A can hold fallback partial result
 *  -2 if M × N is invalid and A is too small for fallback result
 *  -3 if M × N is valid but A is too small
 */
int Multiplication(int RM, int CM, int RN, int CN, int RA, int CA, int** M, int** N, int** A){
    //Initialize A to zeros
    for(int i = 0; i < RA; i++){
        for(int j = 0; j < CA; j++){
            *(*(A + i) + j) = 0;
        }
    }

    //Case: M and N are compatible (CM == RN)
    if (CM == RN) {
        //perform matrix multiplication
        for (int i = 0; i < RM && i < RA; i++) {
            for (int j = 0; j < CN && j < CA; j++) {
                int sum = 0;
                for (int k = 0; k < CM; k++) {
                    sum += *(*(M + i) + k) * *(*(N + k) + j);
                }
                *(*(A + i) + j) = sum;
            }
        }
        
        //check if A matches output size
        if (RA >= RM && CA >= CN) {
            if (RA == RM && CA == CN)
                return 1;  //exact fit
            else
                return 2;  //oversized but fits
        } else {
            return -3;     //too small --> partial result stored
        }
    }

    //Case: M and N not compatible --> fallback multiplication for overlap
    int minK = (CM < RN) ? CM : RN; //Min(CM, RN) col of M or Row of N (max k we can iterate over)
    int overlapR = (RM < RA) ? RM : RA; //Min(RM, RA) min rows between M and A
    int overlapC = (CN < CA) ? CN : CA; //Min(CN, CA) min cols between N and A

    //partial multiplication
    for (int i = 0; i < overlapR; i++) {
        for (int j = 0; j < overlapC; j++) {
            int sum = 0;
            for (int k = 0; k < minK; k++) {
                sum += *(*(M + i) + k) * *(*(N + k) + j);
            }
            *(*(A + i) + j) = sum;
        }
    }

    //check if A can hold fallback result
    if (RA >= RM && CA >= CN)
        return -1;  // A can hold full fallback result
    else
        return -2;  // A cannot hold full fallback result
}

/**
 * Transposes matrix A into matrix AT, with support for oversized or undersized output.
 * 
 * Input:
 *  int RA : # rows in output A
 *  int RC : # columns in matrix A
 *  int RAT : # rows in transposed matrix AT
 *  int CAT : # columns in transposed matrix AT
 *  int** A : Input matrix to be transposed
 *  int** AT : Output matrix to store the transposed result
 * 
 * Output: (int)
 *  1 if the transpose was exact
 *  2 if AT was larger than needed
 *  -1 if AT was too small, and only a partial transpose was stored
 */
int Transpose(int RA, int RC, int RAT, int CAT, int** A, int** AT){
    //Initialize AT to zeros
    for(int i = 0; i < RAT; i++){
        for(int j = 0; j < CAT; j++){
            *(*(AT + i) + j) = 0;
        }
    }

    //Compute overlap dimensions
    int minR = (RC < RAT) ? RC : RAT;
    int minC = (RA < CAT) ? RA : CAT;

    //Perform transpose on overlap
    for(int i = 0; i < minR; i++){
        for(int j = 0; j < minC; j++){
            *(*(AT + i) + j) = *(*(A + j) + i);
        }
    }

    //Return based on compatibility
    if (RAT >= RC && CAT >= RA) {
        if (RAT == RC && CAT == RA)
            return 1;  //exact
        else
            return 2;  //oversized but fits
    } else {
        return -1;     //too small, partial transpose stored
    }
    abort();
}

// Helper functions for Testing
int** initializeMatrix(int n, int m, int* values){
    int** ret = (int**)malloc(n*sizeof(int*));
    for(int i=0; i<n; i++){
        ret[i] = (int*)malloc(m*sizeof(int));
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            ret[i][j] = values[i*m+j];
        }
    }
    return ret;
}

void freeMatrix(int n, int** M){
    for(int i=0; i<n; i++){
        free(M[i]);
    }
    free(M);
}

#ifndef STUDENT_MAIN /* Do not remove this line*/
int main(int argc, char* argv[]){
    (void)argc;
	(void)argv;

    return 0;
}
#endif