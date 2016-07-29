void cholesky (double *A[s][s], int b, int s)
{
   for (int k = 0; k < s; k++) {

      po_cholesky (A[k][k], b, b);              // Cholesky factorization
                                                // (diagonal block)
      for (int j = k + 1; j < s; j++) 
         tr_solve (A[k][k], A[k][j], b, b);     // Triangular solve

      for (int i = k + 1; i < s; i++) {
         for (int j = i + 1; j < s; j++)
            ge_multiply (A[k][i], A[k][j], 
                         A[i][j], b, b);        // Matrix multiplication
         sy_update (A[k][i], A[i][i], b, b);    // Symmetric rank-b update
      }

   }
}
