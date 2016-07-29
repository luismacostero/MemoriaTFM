source("1core.m")

gemm_symm = blis_sgemm_nn_ccc;

source("2core.m")

gemm_asymm = blis_sgemm_nn_ccc;


plot( gemm_symm(:, 1), gemm_symm(:, 4),
      gemm_asymm(:, 1), gemm_asymm(:, 4) )

axis( [32 384 0 9] )
%xrange( [32 32 384] )

xlabel( "Problem size (m=n=k)" )
ylabel( "GFLOPS" )

title( "SGEMM on ODROID XU-3" )

legend( "1 A15 core", "1 A15 core + 1 A7 core (ASYM BLIS)", "location", "northwest" )

xtick=32:32:384;
set(gca,'xtick',xtick);

grid on;

print -dpdf cross_point.pdf
print -color -deps cross_point.eps
