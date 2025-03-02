## 一、实验目的

本实验目的是加强学生对位级运算的理解及熟练使用的能力。

## 二、报告要求

本报告要求学生把实验中实现的所有函数逐一进行分析说明，写出实现的依据，也就是推理过程，可以是一个简单的数学证明，也可以是代码分析，根据实现中你的想法不同而异。

## 三、函数分析

1. bitXor函数

**函数要求：**

函数名 | bitXor
-|-
参数 | int , int
功能实现 | x^y
要求 | 只能使用 ~ 和 \| 运算符，将结果返回

**实现分析：**

将x、y转化为逻辑值，则x、y可能的取值情况有4种（xy=00，01，10，11），令ret = x ^y，可以画出真值表：

xy | ret
-|-
00 | 0
01 | 1
10 | 1
11 | 0

若使用逻辑表达式，$ret = \bar{x}y+x\bar{y}= \overline{\bar{x}\bar{y}}\cdot\overline{xy}$, 转换成对应的位操作得：(~(~x&~y))&(~(x&y))。


**函数实现：**

```C
int bitXor(int x, int y) {
  return (~(~x & ~y)) & (~(x & y));
}
```

2. getByte函数

**函数要求：**

函数名 | getByte
-|-
参数 | int x, int n
功能实现 | 返回文字x的第n个字节内容
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多6次；返回结果

**分析：**

使用一个字节值为全1、其它字节值为全0的mask，将它与输入的文字做按位与操作即可选出一个字节的内容。与操作前根据指定的字节序号将文字进行移位即可选出指定字节的内容。

注意：一个字节有8个位，需要对文字进行移位的数量为8*n。由于不能使用\*运算符，移位位数为n<<3。

**函数实现：**

```C
int getByte(int x, int n) {
  return (x >> (n << 3)) & 0xff;
}
```

3. logicalShift函数

**函数要求：**

函数名 | logicalShift
-|-
参数 | int x, int n
功能实现 | 将文字x逻辑右移n位（高位补0）
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多20次；返回结果

**分析：**

由于C语言的>>运算符进行算术右移，可以先对文字x进行算术右移，再将x的高n位置为0。第二步可以通过与高n位为0，低位全为1的mask做按位与运算实现。

为获取需要的mask，先将1左移31位得0x80000000，然后算术右移n位得111...10...0(n+1个1)，再左移一位后按位取反即可。


**函数实现：**

```C
int logicalShift(int x, int n) {
  int mask = ~(((1 << 31) >> n) << 1);
  return (x >> n) & mask;
}
```

4. bitCount函数

**函数要求：**

函数名 | bitCount
-|-
参数 | int
功能实现 | 返回文字补码表示中1的个数
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多40次；返回结果

**分析：**

我们可以通过32个只有一位为1的掩码分别检验x的每一位是否为1，求和获得结果。但是这样操作涉及的&操作数量过多，因此将32位分为8组，通过1次&操作检验8位。具体做法如下：

令mask=0x11111111，mask&x每组的十六进制数取值表示x32位每组的LSB（least significant bit）是否为1，记为one_bits, 这样我们可以通过8个十六进制数之和得到x的8个LSB中1的数量。将x右移1位后&mask，可以得到每组第1位1的数量，与上一步结果累加得到每组第0、1位为1的数量。依此类推，将x右移0、1、2、3位并&mask后的结果之和，8个十六进制数的取值即为8组中1的数量。

下一步将8个十六进制数求和：先将one_bits的高16位与低16位求和，结果sum的第k~k+3位为x的第k~k+3位与第k+16~k+19位1的数量之和（k=0，4，8，12），这样我们只用关注one_bits的低16位即可，同样用分治法求和。通过mask2=0x0f0f将16位分为4组，sum&mask2得到sum的第0-3位和8-11位，(sum>>4)&mask2得到sum的第4-7位和12-15位,求和后只需再对结果的0-7位和8-15位求和（此时可能存在5位才能表示的结果）。由于32位的int最多有32位为1，结果用6位即可表示，为保证结果准确性，对求和结果取最低6位。


**函数实现：**

```C
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
```

5. conditional函数

**函数要求：**

函数名 | conditional
-|-
参数 | int, int, int 
功能实现 | x ? y : z
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多16次；返回结果

**分析：**

将x通过!!x操作得到对应的逻辑值xbool，xbool为1时取y，否则取0，则返回值的逻辑表达式为$ret = xbool\cdot y +\overline{xbool} \cdot z$。取值操作转换成对应的位操作为与111...1做&操作，舍弃操作转换成与000...0做&操作，逻辑表达式转换为位操作$ret = mask \& y \;|$ ~$mask \& z$，其中mask的取值由xbool决定。通过~（xbool-1）可以得到x=1时为111...1、x=0时为000...0的mask。

**函数实现：**

```C
int conditional(int x, int y, int z) {
  // !!x gives 1(0000..1) when x=1, o.w. gets 0; 
  x = ~(!!x + (~0));  // take complement to get the mask(x=1:11111..,x=0:00000...)
  return (y & x) | (z & ~x) ;
}
```

6. tmin函数

**函数要求：**

函数名 | tmin
-|-
参数 | void
功能实现 | 返回最小的二进制补码数
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多4次；返回结果

**分析：**

n位二进制补码数最小值的补码表示为1000...0，将1左移（n-1）位即可。

**函数实现：**

```C
int tmin(void) {
  return 0x1 << 31;
}
```

7. fitsBits函数

**函数要求：**

函数名 | fitsBits
-|-
参数 | int x, int n
功能实现 | 判断x是否可以表示为n位二进制补码整数，若可以，返回1，否则返回0
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多15次；返回结果

**分析：**

这个问题可以转换为判断x的第n~31位是否全为0或1，若是，则x可以表示为n位二进制补码整数，反之不能。由于对正数和负数的判定规则相似，只是0和1反过来而已，可以先将负数按位取反，然后判断是否第n~31位均为0即可。

将x算术右移n-1位，若x的第n~31位全为1，加1后溢出得0，布尔值为0；若x的第n~31位全为0，取其布尔值也为0。若两者亦或得1，则x的第n~31位全为0或1，可以用n位二进制补码数表示。


**函数实现：**

```C
int fitsBits(int x, int n) {
  /* if the bits in position n~31 are of the same value, it can be represented using n bits
  Since arithmetic shift fill with sign bits, we can use this to check */
  int flag_zeros, flag_ones, xshr;
  xshr = x >> (n + (~0));  // compare the most significant bit in n(sign bit) to the most signficant bit in 32
  flag_zeros = !!xshr;  // if all zeros, should be 0
  flag_ones = !!(xshr + 1); // if all ones, should be 0 too
  return flag_ones ^ flag_zeros; // if yes, only one condition will be satisfied
}
```

8. dividePower2函数

**函数要求：**

函数名 | dividePower2
-|-
参数 | int x, int n
功能实现 | 计算$\frac{x}{2^n}$，结果向0舍入
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多15次；返回结果

**分析：**

计算$\frac{x}{2^n}$可以通过算术右移n位实现，但是C语言默认的正数和负数舍入规则为向下取整，要实现向0舍入，对于负数在>>前应该先加$2^{n-1}$。

**函数实现：**

```C
int dividePower2(int x, int n) {
    int selector = x >> 31;  // 000.. for x>=0; 111.. for x<0
    return (selector & ((x + (1 << n) + (~0))) >> n) | (~selector & (x >> n)); // rounding strategy
}
```

9. negate函数

**函数要求：**

函数名 | negate
-|-
参数 | int
功能实现 | 返回-x
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多5次；返回结果

**分析：**

补码的编码规则中，-x = ~x + 1。

**函数实现：**

```C
int negate(int x) {
  return ~x + 1;
}
```

10. howManyBits函数

**函数要求：**

函数名 | howManyBits
-|-
参数 | int
功能实现 | 计算使用二进制补码表示x的最小位数
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多90次；返回结果

**分析：**

这道题思路与countBits相近，使用二分法解决。首先判断是否需要16位数，假如需要，判断是否需要24位数，否则判断是否需要8位数......以此类推，最后加上符号位。

**函数实现：**

```C
int howManyBits(int x) {
  // find the most left bit diff. to sign bit and +1
  int flag_16, flag_8, flag_4, flag_2, flag_1;
  int sign = !!(x >> 31);
  x = x ^ ((sign << 31 ) >> 31);  // if sign=1, negate x(y^1=~y,y^0=y)

  flag_16 = !!(x >> 15);  // if there is a '1' in the most significant 16 bits, check the upper part, o.w. check the lower part
  flag_8 = !!(x >> ((flag_16 << 4) + 7));  // highest 8 bits in the 2 groups
  flag_4 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + 3));
  flag_2 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + 1));
  flag_1 = !!(x >> ((flag_16 << 4) + (flag_8 << 3) + (flag_4 << 2) + (flag_2 << 1)));

  return (flag_16 << 4)+ (flag_8 << 3) + (flag_4 << 2) + (flag_2 << 1) + flag_1 + 1;
}
```

11. isLessOrEqual函数

**函数要求：**

函数名 | isLessOrEqual
-|-
参数 | int x, int y
功能实现 | 若x≤y，返回1；否则返回0
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多24次；返回结果

**分析：**

输入数字的符号有4种可能的组合，通过分析发现，返回1的时候有两种情况：x负y正或x、y同号但x-y$\leq0$。因此我们只需取x、y的符号位sx、sy，首先判断sx & !sy是否成立，若不成立再作差并判断diff = x-y是否为非正值。

值得注意的一点是，由于0的符号位为0，负数的符号位1为1，若判断diff的符号位为1，可能误判diff=0的情况。因此在实代码现中，取diff=y-x，然后判断diff的符号位是否为0即可。

**函数实现：**

```C
int isLessOrEqual(int x, int y) {
  int sdiff = (y + ~x + 1) >> 31;
  int sx = !!(x >> 31), sy = !!(y >> 31);
  return ((!!(sx & !sy)) | ((!(sx ^ sy)) & (!sdiff)));    // when x being neg and y pos or sign bit of diff. is 1,lessOrEqual
}
```

12. intLog2函数

**函数要求：**

函数名 | intLog2
-|-
参数 | int
功能实现 | 计算$\lfloor log_{2}x \rfloor$
要求 | 只能使用! ~ & ^ \| + << >>运算符，最多90次；返回结果

**分析：**

计算$\lfloor log_{2}x \rfloor$的本质是寻找最高位1的编号。在howManyBits中我们已经找到了表示x所需的最少位数，只需在此基础上忽略符号位并-1即可（1由位编号和权重之间的差值导致）。

**函数实现：**

```C
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
```

13. floatAbsVal函数

**函数要求：**

函数名 | floatAbsVal
-|-
参数 | unsigned
功能实现 | 以位级表示返回输入浮点数的绝对值
要求 | 可使用任意int/unsigned操作符，包括\|\|,&&,if,while，最多10次
说明 | 浮点数以unsigned int格式输入，将它的位级表示转换为等价的浮点数表示，返回值也以unsigned int类型返回

**分析：**

首先对输入判断是否为NaN，若是直接返回输入；否则保留exp和frac部分，将符号位s设为0。

**函数实现：**

```C
unsigned floatAbsVal(unsigned uf) {
  // first check whether uf is NaN(exp=1111...and frac is non-zero)
  if((((uf >> 23) & 0xff) == 0xff) && (uf & 0x7fffff)) 
    return uf;
  else   // set sign bit to be 0
    return uf & 0x7fffffff;  
}
```

14. floatScale1d2函数

**函数要求：**

函数名 | floatScale1d2
-|-
参数 | unsigned
功能实现 | 返回0.5*f的等价位级表示
要求 | 可使用任意int/unsigned操作符，包括\|\|,&&,if,while，最多30次；返回结果

**分析：**

首先判断输入uf是否为NaN或$\infty$，即exp部分的二进制表示是否为111...1，是则直接返回uf；另一种简单的情况是除2前后，uf对应的浮点数均为规格化的数，即exp>1时，此时frac保持不变，仅需从exp部分减去1即可。

对于非规格化或除2前规格化、除2后非规格化的浮点数，它们的exp部分除2后为0，frac部分改变且可能发生舍入。当frac部分的末两位为11时，直接移位得到的末位为1，按照超过一半精度时向最近偶数舍入的规定，先对frac部分加10后移位，得到正确舍入结果。


**函数实现：**

```C
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
```

15. floatFloat2Int函数

**函数要求：**

函数名 | floatFloat2Int
-|-
参数 | unsigned
功能实现 | 返回浮点数f转换为整数的等价位级表示
要求 | 可使用任意int/unsigned操作符，包括\|\|,&&,if,while，最多30次；返回结果

**分析：**

对于输入的unsigned表示的浮点数，通过移位和掩码操作取出浮点数的三个组成成分：s，exp，frac。首先判断输入是否为非规格化数，即exp是否为0，若是则返回0；然后判断是否为NaN或$\infty$,即exp部分是否为111...1，是则按题目要求返回0x80000000u。其它情况下，uf对应的浮点数为规格化数。

对于规格化的数，首先计算E = exp - bias， 这里bias = 127。若E<0,由于frac<2，对应值v的绝对值小于1，转换为int结果为0；若E>31，会发生溢出，按$\infty$处理；否则对应浮点数绝对值为$1.x_1x_2x_3...\cdot 2^E$，考虑到frac部分LSB从第23位开始，需比较E与23的大小，通过移位|23-E|次使v的大小正确。最后，由于二进制补码整数表示中$-x=$~$x + 1$，对于s=1的负浮点数需要进行绝对值到int的变换。

**函数实现：**

```C
int floatFloat2Int(unsigned uf) {
  int sign = !!(uf >> 31);  // gets 0 for pos and 1 for neg
  int exp = (uf >> 23) & 0xff, frac = uf & 0x007fffff; 
  if(exp == 0) 
    return 0;  // in fact there are two cases, if frac==0 it's 0; o.w. E=-126(denormalized), casting to int gives 0
  if(exp == 255)
    return 0x80000000u;

  int E = exp - 127;
  if(E < 0)  // E too small
    return 0;
  if(E >= 32)  // too big
    return 0x80000000u;
  frac = frac | 0x00800000;  // 1.xxxx, now there are 24 bits in frac
  
  /* if E>23, dot is on the left of the float dot
     otherwise dot should be on the right */
  if(E >= 23)  // left shift by at most 8 bits
    frac = frac << (E - 23);  
  else 
    frac = frac >> (23 - E);
  
  if(sign) //negative
    return ~frac + 1;
  return frac;  // positive
}
```

## 四、实验总结

在实验过程中，我遇到了许多困难，部分由逻辑错误引起，但是多数由未考虑边界条件所致，如对于isLessOrEqual函数中diff=0的情况，我最初设置的判断条件是符号位为1，进行本地测试时，用例x=0x7fffffff，y=0x80000000返回的结果为1，但实际应该是0。对于逻辑上的困难，我通过btest给出的报错信息和用例进行修改，部分错误在思考未果后我查询了互联网；对于未考虑边界条件所致的错误，我在调试过程中找出判断错误的位置并修改判断条件，最终修复了所有bug。

经过这次实验，我意识到边界情况检查在程序编写中的重要性，提醒我以后在编写代码时注意判断边界条件下程序是否运行正确。
