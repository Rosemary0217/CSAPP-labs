/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2018 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
/* We do not support C11 <threads.h>.  */
//bit-level
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  return (~(~x & ~y)) & (~(x & y));
}
/* 
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (least significant) to 3 (most significant)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
// int getByte(int x, int n) {
//   int mask = 127 << (n << 3);
//   return (x & mask) >> (n << 3);  //再算术移位导致补符号位
// }
int getByte(int x, int n) {
  return (x >> (n << 3)) & 0xff;
}
/* 
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3 
 */
int logicalShift(int x, int n) {
  int mask = ~(((1 << 31) >> n) << 1);
  int xx = x >> n;
  int res = xx & mask;
  return res;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  int m, mask1, mask2, one_bits, sum;
  m = 0x11 | (0x11 << 8);
  mask1 = m | (m << 16);   // partition 32 bits into 8 groups where 1 is LSB in each group
  one_bits = x & mask1;
  one_bits += x >> 1 & mask1;
  one_bits += x >> 2 & mask1;
  one_bits += x >> 3 & mask1;

  sum = one_bits + (one_bits >> 16);  // combine the higher 16 bits and lower 16 bits
  mask2 = 0xf | (0xf << 8); // mask2: zeros-ones in lower 16 bits
  sum = (sum & mask2) + ((sum >> 4) & mask2);  // former part: higher 4 bits in each 8-bit group; latter: lower part

  return (sum + (sum >> 8)) & 0x3f; // take the least significant 6 bits(at most 32 1's)
}
/* 
 * conditional - same as x ? y : z 
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // !!x gives 1(0000..1) when x=1, o.w. gets 0; 
  x = ~(!!x + (~0));  // take complement to get the mask(x=1:11111..,x=0:00000...)
  return (y & x) | (z & ~x) ;
}
//two's complement
/* 
 * tmin - return minimum two's complement integer 
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  return 0x1 << 31;
}
/* 
 * fitsBits - return 1 if x can be represented as an 
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /* if the bits in position n~31 are of the same value, it can be represented using n bits
  Since arithmetic shift fill with sign bits, we can use this to check */
  int flag_zeros, flag_ones, xshr;
  xshr = x >> (n + (~0));  
  flag_zeros = !!xshr;  // if all zeros, should be 0
  flag_ones = !!(xshr + 1); // if all ones, should be 0 too
  return flag_ones ^ flag_zeros; // if yes, only one condition will be satisfied
}
/* 
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: dividePower2(15,1) = 7, dividePower2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int dividePower2(int x, int n) {
    int selector = x >> 31;  // 000.. for x>=0; 111.. for x<0
    return (selector & ((x + (1 << n) + (~0))) >> n) | (~selector & (x >> n)); // rounding strategy
}
/* 
 * negate - return -x 
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  // find the most left bit diff. to sign bit and +1
  int flag_16, flag_8, flag_4, flag_2, flag_1;
  int sign = !!(x >> 31);
  x = x ^ (sign << 31 >> 31);  // if sign=1, negate x(y^1=~y,y^0=y)

  flag_16 = !!(x >> 15);  // if there is a '1' in the most significant 16 bits, check the upper part, o.w. check the lower part
  flag_8 = !!(x >> ((flag_16 << 4) + 7));  // lowest 8 bits in the 2 groups
  flag_4 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + 3));
  flag_2 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + 1));
  flag_1 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + (flag_2 << 1)));

  return (flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + (flag_2 << 1) + flag_1 + 1;
}
/* 
 * isLessOrEqual - if x <= y  then return 1, else return 0 
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  //int diff  = x + ~y + 1;  // why not: cannot judge when diff=0
  int sdiff = (y + ~x + 1) >> 31;
  int sx = !!(x >> 31), sy = !!(y >> 31);
  return ((!!(sx & !sy)) | ((!(sx ^ sy)) & (!sdiff)));    // when x being neg and y pos or sign bit of diff. is 1,lessOrEqual
}
/*
 * intLog2 - return floor(log base 2 of x), where x > 0
 *   Example: intLog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int intLog2(int x) {  //index(most sig 1)-1
  // calculate #bits and -1
  int flag_16, flag_8, flag_4, flag_2, flag_1;
  
  flag_16 = !!(x >> 15);  // if there is a '1' in the most significant 16 bits, check the upper part, o.w. check the lower part
  flag_8 = !!(x >> ((flag_16 << 4) + 7));  // lowest 8 bits in the 2 groups
  flag_4 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + 3));
  flag_2 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + 1));
  flag_1 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + (flag_2 << 1)));

  return (flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + (flag_2 << 1) + flag_1 + (~0);
}
//float
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  // first check whether uf is NaN(exp=1111...and frac is non-zero)
  if((((uf >> 23) & 0xff) == 0xff) && (uf & 0x7fffff)) 
    return uf;
  else   // set sign bit to be 0
    return uf & 0x7fffffff;  
}
/* 
 * floatScale1d2 - Return bit-level equivalent of expression 0.5*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
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
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int sign = !!(uf >> 31);  // gets 0 for pos and 1 for neg
  int exp = (uf >> 23) & 0xff, frac = uf & 0x007fffff; 
  if(exp == 0) 
    return 0;  // in fact there are two cases, if frac==0 it's 0; o.w. E=-126, casting to int gives 0
  if(exp == 255)
    return 0x80000000u;

  int E = exp - 127;
  if(E < 0)  // E too small
    return 0;
  if(E >= 32)  // too big
    return 0x80000000u;
  frac = frac | 0x00800000;  // 1.xxxx, now there are 24 bits in frac
  
  /* if Ee23, dot is on the left of the float dot
     otherwise dot should be on the right */
  if(E >= 23)  // left shift by at most 8 bits
    frac = frac << (E - 23);  
  else 
    frac = frac >> (23 - E);
  
  if(sign) //negative
    return ~frac + 1;
  return frac;  
}
