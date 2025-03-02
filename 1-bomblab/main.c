#include "stdio.h"
#include "stdlib.h"
#include "bits.h"

// int getByte(int x, int n) {
//   return (x >> (n << 3)) & 0xff;
// }

// int logicalShift(int x, int n) {
//   int mask = ~(((1 << 31) >> n) << 1);
//   int xx = x >> n;
//   int res = xx & mask;
//   return res;
// }

// int fitsBits(int x, int n) {
//   /* if the bits in position n~31 are of the same value, it can be represented using n bits
//   Since arithmetic shift fill with sign bits, we can use this to check */
//   int flag_zeros, flag_ones, xshr;
//   xshr = x >> (n + (~0));  // the highest n bits
//   // printf("xshr = %d\n",xshr);
//   flag_zeros = !!xshr;  // if all zeros, should be 0
//   // printf("zeros = %d\n",flag_zeros);
//   flag_ones = !!(xshr + 1); // if all ones, should be 0 too
//   // printf("ones = %d\n",flag_ones);
//   return flag_ones ^ flag_zeros; // if yes, only one condition will be satisfied
// }

// int howManyBits(int x) {
//   // find the most left bit diff. to sign bit and +1
//   int flag_16, flag_8, flag_4, flag_2, flag_1;
//   int sign = !!(x >> 31);
//   x = x ^ (sign << 31 >> 31);  // if sign=1, negate x(y^1=~y,y^0=y)

//   flag_16 = !!(x >> 15);  // if there is a '1' in the most significant 16 bits, check the upper part, o.w. check the lower part
//   flag_8 = !!(x >> ((flag_16 << 4) + 7));  // lowest 8 bits in the 2 groups
//   flag_4 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + 3));
//   flag_2 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + 1));
//   flag_1 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + (flag_2 << 1)));

//   return (flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + (flag_2 << 1) + flag_1 + 1;
// }


// int isLessOrEqual(int x, int y) {
//   //int diff  = x + ~y + 1;  // why not: cannot judge when diff=0
//   int sdiff = (y + ~x + 1) >> 31;
//   int sx = !!(x >> 31), sy = !!(y >> 31);
//   return !!((sx & !sy) | (!(sx ^ sy)) & !sdiff);    // when x being neg and y pos or sign bit of diff. is 1,lessOrEqual
// }

// int intLog2(int x) {  //index(most sig 1)-1
//   // calculate #bits and -1
//   int flag_16, flag_8, flag_4, flag_2, flag_1;
  
//   flag_16 = !!(x >> 15);  // if there is a '1' in the most significant 16 bits, check the upper part, o.w. check the lower part
//   flag_8 = !!(x >> ((flag_16 << 4) + 7));  // lowest 8 bits in the 2 groups
//   flag_4 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + 3));
//   flag_2 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + 1));
//   flag_1 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + (flag_2 << 1)));

//   return (flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + (flag_2 << 1) + flag_1 + (~0);
// }

// unsigned floatAbsVal(unsigned uf) {
//   // first check whether uf is NaN(exp=1111...and frac is non-zero)
//   if((((uf >> 23) & 0xff) == 0xff) && (uf & 0x7fffff)) 
//     return uf;
//   else   // set sign bit to be 0
//     return uf & 0x7fffffff;  
// }

// int floatFloat2Int(unsigned uf) {
//   int sign = !!(uf >> 31);  // gets 0 for pos and 1 for neg
//   int exp = (uf >> 23) & 0xff, frac = uf & 0x007fffff; 
//   if(exp == 0) 
//     return 0;  // in fact there are two cases, if frac==0 it's 0; o.w. E=-126, casting to int gives 0
//   if(exp == 255)
//     return 0x80000000u;

//   int E = exp - 127;
//   if(E < 0)  // E too small
//     return 0;
//   if(E >= 32)  // too big
//     return 0x80000000u;
//   frac = frac | 0x00800000;  // 1.xxxx, now there are 24 bits in frac
  
//   /* if Ee23, dot is on the left of the float dot
//      otherwise dot should be on the right */
//   if(E >= 23)  // left shift by at most 8 bits
//     frac = frac << (E - 23);  
//   else 
//     frac = frac >> (23 - E);
  
//   if(sign) //negative
//     return ~frac + 1;
//   return frac;  // sign bit
// }

unsigned floatScale1d2(unsigned uf) {
  int exp, frac;
  exp = (uf >> 23) & 0xff;
  frac = uf & 0x7fffff;
  // first check whether uf is NaN(exp=111... and frac non-zero) or infinity(exp=111... and frac=000..)
  if(exp == 0xff) 
    return uf;
  
  if(exp <= 1){  // denormalized or after division it's denormalized
    if((frac & 0x3) == 0x3)
      uf = uf + 0x2;  // round towards even
    return ((uf >> 1) & 0x007fffff)|(uf & 0x80000000);  // former:frac; latter:sign bit & set exp=0 
  }
  else  // before and after division it's normalized
    return uf - 0x00800000; // exp-1  
}

int main(){

    // printf("%d\n", getByte(0x80000000,3));
    // printf("%d\n",logicalShift(0x80000000, 0));

    // printf("%d\n",fitsBits(0x80000000,1));
    // printf("%d\n",fitsBits(0x80000000,31));

    // printf("%d\n",isLessOrEqual(0x80000000,0x7fffffff));
    // printf("%d\n",isLessOrEqual(0x80000000,0x80000000));

    // printf("%d\n",howManyBits(0x80000000));  // 32
    // printf("%d\n",howManyBits(298));  // 10
    // printf("%d\n",howManyBits(12));  // 5
    // printf("%d\n",howManyBits(-5));  // 4
    // printf("%d\n",howManyBits(0));  // 1
    // printf("%d\n",howManyBits(0xffffffff));  // 1
    // printf("%d\n",howManyBits(0x7fffffff));  // 32
    // printf("%d\n",howManyBits(0xa062));

    // printf("%d\n",intLog2(16));
    // printf("%d\n",intLog2(0x7fffffff));

    // printf("0x%x\n",floatAbsVal(0xffc00000));
    // printf("0x%x\n",floatAbsVal(0x80800001));

    // printf("0x%x\n",floatFloat2Int(0x3f800000));
    // printf("0x%x\n",floatFloat2Int(0xbf800000));

    // printf("0x%x\n",floatScale1d2(0x800000));
    // printf("0x%x\n",floatScale1d2(0xff800000));

    printf("0x%x\n",1 << 31);

    return 0;
}
