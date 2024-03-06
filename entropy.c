#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) 
{
    FILE* fp;
    int i, counter[256]={0}, gcounter=0;
    double prob[256], entropy=0;

    fp = fopen(argv[1], "rb");
    if(fp == NULL)
    {
        printf("File could not be opened");
        exit(1);
    }

    unsigned int b;
    while(fread(&b, 1, 1, fp))
    {
        counter[b]++;
        gcounter++;
    }
    fclose(fp);

    for(i = 0; i < 256; i++)
    {
        prob[i] = (double)counter[i] / gcounter;
        printf("prob[%c]=%g\n", i, prob[i]);
        if(prob[i] != 0)
            entropy -= prob[i] * (log(prob[i]) / log(2));
    }

    printf("H(S)=%g\n", entropy);
    return 0;
}
