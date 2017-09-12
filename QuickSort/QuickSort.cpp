#include "QuickSort.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>

using namespace std;

int choosePivotRandom(int min, int max) //range : [min, max]
{
   static bool first = true;
   if (first)
   {
      srand(time(NULL)); //seeding for the first time only!
      first = false;
   }
   return min + rand() % (max - min + 1);
}

int choosePivotRandom2(int min, int max)
{
    random_device rd;  // obtain a random number from hardware
    mt19937 eng(rd()); // seed the generator
    uniform_int_distribution<> distr(min, max); // define the range
    return distr(eng);
}

int choosePivotMin(int min, int max)
{
    return min;
}

int choosePivotMax(int min, int max)
{
    return max;
}

