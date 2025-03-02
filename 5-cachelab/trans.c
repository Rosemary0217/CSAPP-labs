/* 
 * trans.c - Matrix transpose B = A^T
 * 
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 * 
 * 姓名: 刘婧婷
 * 学号：1120201050
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
    int bj, bi, i, j;
    int a0, a1, a2, a3, a4, a5, a6, a7;  //8 local variables
    if(M == 32){
        for (bi = 0; bi < M; bi += 8) 
            for (bj = 0; bj < N; bj += 8) 
                for (i = bi; i < bi + 8; i++) {
                    /*每转移8个元素，A只需要读入一次, 一次复制一个cache line中的*/
                    a0 = A[i][bj+0]; 
                    a1 = A[i][bj+1]; 
                    a2 = A[i][bj+2]; 
                    a3 = A[i][bj+3];
                    a4 = A[i][bj+4]; 
                    a5 = A[i][bj+5]; 
                    a6 = A[i][bj+6]; 
                    a7 = A[i][bj+7]; 
                    /*B也只需要读入一次，因为一次可以读入8行*/
                    B[bj+0][i] = a0; 
                    B[bj+1][i] = a1; 
                    B[bj+2][i] = a2; 
                    B[bj+3][i] = a3;
                    B[bj+4][i] = a4; 
                    B[bj+5][i] = a5; 
                    B[bj+6][i] = a6; 
                    B[bj+7][i] = a7; 
            }   
    }else if(M == 64){
        for (bi = 0; bi < N; bi += 8) {
            for (bj = 0; bj < M; bj += 8) {
                // 仍然以8*8为单位
                for (i = bi; i < bi + 4; i++) {
                    // a0~a8是A中同一行内容，在同一次cache读入，不会缺页
                    a0 = A[i][bj]; a1 = A[i][bj+1]; a2 = A[i][bj+2]; a3 = A[i][bj+3];  
                    a4 = A[i][bj+4]; a5 = A[i][bj+5]; a6 = A[i][bj+6]; a7 = A[i][bj+7];  
                    // 正确位置
                    B[bj][i] = a0; B[bj+1][i] = a1; B[bj+2][i] = a2; B[bj+3][i] = a3;    
                    // 同4行，这一列的后面第4列，此过程B不会产生缺页          
                    B[bj][i+4] = a4; B[bj+1][i+4] = a5; B[bj+2][i+4] = a6; B[bj+3][i+4] = a7;  
                }
                // 下4行左4列移动到刚才已转置但暂存的4*4块位置上，暂存的4*4块使用局部变量暂存
                for (j = bj; j < bj + 4; j++) {
                    // 下4行的A值
                    a0 = A[bi+4][j]; a1 = A[bi+5][j]; a2 = A[bi+6][j]; a3 = A[bi+7][j];  
                    // 暂存在B中已转置的A右上角
                    a4 = B[j][bi+4]; a5 = B[j][bi+5]; a6 = B[j][bi+6]; a7 = B[j][bi+7];  
                    // A左下角
                    B[j][bi+4] = a0; B[j][bi+5] = a1; B[j][bi+6] = a2; B[j][bi+7] = a3;        
                    // 发生一次miss 
                    B[j+4][bi] = a4; B[j+4][bi+1] = a5; B[j+4][bi+2] = a6; B[j+4][bi+3] = a7;  
                }
                // 下4行的右4列
                for (i = bi + 4; i < bi + 8; i++) {
                    a0 = A[i][bj+4]; a1 = A[i][bj+5]; a2 = A[i][bj+6]; a3 = A[i][bj+7]; 
                    B[bj+4][i] = a0; B[bj+5][i] = a1; B[bj+6][i] = a2; B[bj+7][i] = a3; 
                }
            }
        }
    }else{
        int a8;
        for (bj = 0; bj < M; bj += 9) {
            for (bi = 0; bi < N; bi++) {
                a0 = A[bi][bj];    a1 = A[bi][bj+1];  a2 = A[bi][bj+2];
                a3 = A[bi][bj+3];  a4 = A[bi][bj+4];  a5 = A[bi][bj+5];
                a6 = A[bi][bj+6];
                if (bj + 7 < M) {  // 61 % 9 = 7
                    a7 = A[bi][bj+7];
                    a8 = A[bi][bj+8];
                }    
                // 转置到B中
                B[bj][bi] = a0;    B[j+1][bi] = a1;  B[bj+2][bi] = a2;
                B[bj+3][bi] = a3;  B[j+4][bi] = a4;  B[bj+5][bi] = a5;
                B[bj+6][bi] = a6;
                if (bj + 7 < M) {
                    B[bj+7][bi] = a7;
                    B[bj+8][bi] = a8;
                }
            }
        }
    }
    return;
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    // registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

