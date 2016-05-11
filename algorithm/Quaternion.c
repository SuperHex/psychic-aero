#include "Quaternion.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

Quaternion newQ(double real, double i, double j, double k)
{
  Quaternion q = malloc(sizeof(struct Q));
  q->real = real;
  q->complex = malloc(sizeof(struct I));
  q->complex->i = i;
  q->complex->j = j;
  q->complex->k = k;
  return q;
}

void deleteQ(Quaternion ptr)
{
  free(ptr->complex);
  free(ptr);
}

Quaternion addQ(Quaternion lhs, Quaternion rhs)
{
  Quaternion res = newQ(0,0,0,0);
  res->real = lhs->real + rhs->real;
  res->complex->i = lhs->complex->i + rhs->complex->i;
  res->complex->j = lhs->complex->j + rhs->complex->j;
  res->complex->k = lhs->complex->k + rhs->complex->k;
  return res;
}

Quaternion subQ(Quaternion lhs, Quaternion rhs)
{
  Quaternion res = newQ(0,0,0,0);
  res->real = lhs->real - rhs->real;
  res->complex->i = lhs->complex->i - rhs->complex->i;
  res->complex->j = lhs->complex->j - rhs->complex->j;
  res->complex->k = lhs->complex->k - rhs->complex->k;
  return res;
}

double dotQ(Quaternion lhs, Quaternion rhs)
{
  return -1 * ( lhs->complex->i * rhs->complex->i
              + lhs->complex->j * rhs->complex->j
              + lhs->complex->k * rhs->complex->k
                );
}

Quaternion crossQ(Quaternion lhs, Quaternion rhs)
{
  Quaternion res = newQ(0,0,0,0);
  res->complex->i = lhs->complex->j * rhs->complex->k - rhs->complex->j * lhs->complex->k;
  res->complex->j = lhs->complex->k * rhs->complex->i - rhs->complex->k * lhs->complex->i;
  res->complex->k = lhs->complex->i * rhs->complex->j - rhs->complex->i * lhs->complex->j;
  return res;
}

Quaternion scaleQ(double n, Quaternion q)
{
  Quaternion res = newQ(0,0,0,0);
  res->real = q->real * n;
  res->complex->i = q->complex->i * n;
  res->complex->j = q->complex->j * n;
  res->complex->k = q->complex->k * n;
  return res;
}

Quaternion productQ(Quaternion lhs, Quaternion rhs)
{
  Quaternion res = newQ(0,0,0,0);
  res->real = lhs->real * rhs->real - dotQ(lhs, rhs);
  Quaternion a = scaleQ(lhs->real, rhs);
  Quaternion b = scaleQ(rhs->real, lhs);
  Quaternion c = addQ( addQ(a, b), crossQ(lhs, rhs));

  *(res->complex) = *(c->complex);
  deleteQ(a);
  deleteQ(b);
  deleteQ(c);
  return res;
}

void pretty_print(Quaternion ptr)
{
  printf("(%.1lf, %.1lfi + %.1lfj + %.1lfk)\n"
         , ptr->real
         , ptr->complex->i
         , ptr->complex->j
         , ptr->complex->k
         );
}

double normQ(Quaternion q)
{
  return sqrt( q->real * q->real
             + q->complex->i * q->complex->i
             + q->complex->j * q->complex->j
             + q->complex->k * q->complex->k
              );
}

Quaternion conjugateQ(Quaternion q)
{
  q->complex->i *= -1;
  q->complex->j *= -1;
  q->complex->k *= -1;
  return q;
}

Quaternion inverseQ(Quaternion q)
{
  Quaternion res = newQ(0,0,0,0);
  double norm = normQ(q);
  *res = *q;
  res = conjugateQ(res);
  res->real /= norm;
  res->complex->i /= norm;
  res->complex->j /= norm;
  res->complex->k /= norm;
  return res;
}

int main()
{
  Quaternion p = newQ(0,2,0,0);
  Quaternion q  = newQ(0.707,0.5,0,0.5);
  pretty_print(productQ(productQ(q,p),inverseQ(q)));
  pretty_print(inverseQ(q));
  deleteQ(q);
  deleteQ(p);
  return 0;
}
