#include "kt_math.h"


int kt_math::faktor(int i){
int b = i;
for(int a = b - 1; a > 0;a-- ){
    b = a * b;
}


return b;
}