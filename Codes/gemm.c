void gemm (double A[m][k], double B[k][n], double C[m][n], 
           int m,  int n,  int k, int mc, int nc, int kc)
{
   double *Ac = malloc (mc * kc * sizeof (double)), 
          *Bc = malloc (kc * nc * sizeof (double));

   for (int jc = 0; jc < n; jc+=nc) {              // Bucle 1
      int jb = min(n-jc+1, nc);

      for (int pc = 0; pc < k; jc+=kc) {           // Bucle 2
         int pb = min(k-pc+1, kc);

         pack_buffB (B[pc][jc], Bc, kb, nb);       // Empaquetar A->Ac

         for (int ic = 0; ic < m; ic+=mc) {        // Bucle 3
            int ib = min(m-ic+1, mc);

            pack_buffA (A[ic][pc], Ac, mb, kb);    // Empaquetar A->Ac

            gemm_kernel (Ac, Bc, C[ic][jc], 
                         mb, nb, kb, mc, nc, kc);  // Macro-kernel
         }
      }
   }
}
