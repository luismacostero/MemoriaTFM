#pragma omp task inout([b][b]A)
void po_cholesky (double *A, int b, int ld)
{
 static int        INFO = 0;
 static const char UP   = 'U';
 dpotrf (&UP, &b, A, &ld, &INFO);  // LAPACK Cholesky factorization
}

#pragma omp task in([b][b]A) inout([b][b]B)
void tr_solve (double *A, double *B, int b, int ld)
{
 static double     DONE = 1.0;
 static const char LE   = 'L', UP = 'U', TR = 'T', NU = 'N';
 dtrsm (&LE, &UP, &TR, &NU, &b, &b, 
        &DONE, A, &ld, B, &ld);    // BLAS-3 triangular solve
}

#pragma omp task in([b][b]A, [b][b]B) inout([b][b]C)
void ge_multiply (double *A, double *B, double *C, int b, int ld)
{
 static double     DONE = 1.0, DMONE = -1.0;
 static const char TR   = 'T', NT    = 'N';
 dgemm (&TR, &NT, &b, &b, &b, 
        &DMONE, A, &ld, B, &ld, 
        &DONE,  C, &ld);           // BLAS-3 matrix multiplication
}

#pragma omp task in([b][b]A) inout([b][b]C)
void sy_update (double *A, double *C, int b, int ld)
{
 static double     DONE = 1.0, DMONE = -1.0;
 static const char UP   = 'U', TR    = 'T';
 dsyrk (&UP, &TR, &b, &b, 
        &DMONE, A, &ld, 
        &DONE,  C, &ld);           // BLAS-3 symmetric rank-b update
}

