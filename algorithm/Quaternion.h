#ifndef __Quaternion__
#define __Quaternion__

typedef struct I
{
  double i;
  double j;
  double k;
} *Complex;

typedef struct Q
{
  double real;
  Complex complex;
} *Quaternion, Q;

void pretty_print(Quaternion);

#endif
