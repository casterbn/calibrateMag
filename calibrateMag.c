#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ArrayFloat.h>
#include <ArrayFloat.c>

#define PI 3.14159265358979323846

float max(float x,float y)
{
    if(x>y) return x;
    return y;
}

 
void getCalibratePara(float *pMagXMaxMin,float *pMagYMaxMin,float *pMagZMaxMin,float *pMagOffset_s,float *pMagOffset_b)
{
    float xMaxSace = pMagXMaxMin[0] - pMagXMaxMin[1];
    float yMaxSace = pMagYMaxMin[0] - pMagYMaxMin[1];
    float zMaxSace = pMagZMaxMin[0] - pMagZMaxMin[1];

    float refMaxSace = max(max(xMaxSace,yMaxSace),zMaxSace); 

    float xs = refMaxSace/xMaxSace;
    float ys = refMaxSace/yMaxSace;
    float zs = refMaxSace/zMaxSace;

    float xb = xs*(xMaxSace/2-pMagXMaxMin[0]);
    float yb = ys*(yMaxSace/2-pMagYMaxMin[0]);
    float zb = zs*(zMaxSace/2-pMagZMaxMin[0]);

    pMagOffset_s[0] = xs;
    pMagOffset_s[1] = ys;
    pMagOffset_s[2] = zs;

    pMagOffset_b[0] = xb;
    pMagOffset_b[1] = yb;
    pMagOffset_b[2] = zb;

}

void compensateMag(float *pdrData,float *pMagOffset_s,float *pMagOffset_b)
{
    pdrData[6] = pdrData[6]*pMagOffset_s[0] + pMagOffset_b[0];
    pdrData[7] = pdrData[7]*pMagOffset_s[1] + pMagOffset_b[1];
    pdrData[8] = pdrData[8]*pMagOffset_s[2] + pMagOffset_b[2];

}

void getMagMaxMin(float *pdrData,float *pMagXMaxMin,float *pMagYMaxMin,float *pMagZMaxMin)
{
    float Mx = pdrData[6];
    float My = pdrData[7];
    float Mz = pdrData[8];
    if(Mx>pMagXMaxMin[0])
    {
        pMagXMaxMin[0] = Mx;
    }
    if(Mx<pMagXMaxMin[1])
    {
        pMagXMaxMin[1] = Mx;
    }
    if(My>pMagYMaxMin[0])
    {
        pMagYMaxMin[0] = My;
    }
    if(My<pMagYMaxMin[1])
    {
        pMagYMaxMin[1] = My;
    }
    if(Mz>pMagZMaxMin[0])
    {
        pMagZMaxMin[0] = Mz;
    }
    if(Mz<pMagZMaxMin[1])
    {
        pMagZMaxMin[1] = Mz;
    }
}

// read pdr data
void read()
{
    int type = 1; // 1:校准磁力，2：正常定位
    float magOffset_s[2] = {0};
    float magOffset_b[2] = {0};
    float magXMaxMin[2] = {0};
    float magYMaxMin[2] = {0};
    float magZMaxMin[2] = {0};

    char StrLine[1024];
    FILE *fp;
    fp = fopen("F:\\xihe\\pdr_algorithm\\pdr_algorithm\\test_data.txt","r");
    
    // Determining whether documents exist and readable
    if(fp == NULL){ 
        printf("error!!! file is not exist or cannot read" );
        return;
    }

    int i = 0;
    // getLine
    while(!feof(fp))
    {
        // readdata
        i = i + 1;
        fgets(StrLine,1024,fp); 
        char *ptr,*retptr;
        ptr = StrLine;
        int k = 0;
        float pdrData[9] = {0};
        char seps[] = " ,\t"; // string delimiter
        while((retptr=strtok(ptr,seps)) != NULL)
        {   
            pdrData[k++] = atof(retptr);
            ptr = NULL;
        }

        switch (type)
        {
            case 1: // calibrate mag
                if( i == 1)
                {
                    magXMaxMin[0] = pdrData[6];magXMaxMin[1] = pdrData[6];
                    magYMaxMin[0] = pdrData[7];magYMaxMin[1] = pdrData[7];
                    magZMaxMin[0] = pdrData[8];magZMaxMin[1] = pdrData[8];
                    break;
                }
                getMagMaxMin(pdrData,magXMaxMin,magYMaxMin,magZMaxMin);
                printf("i = %d,magZMax = %.6f,magZMin = %.6f\n",i,magZMaxMin[0],magZMaxMin[1]);
                break;
            case 2: // compensate mag
                compensateMag(pdrData,magOffset_s,magOffset_b);
                break;
            default:
                printf("magOffset: invalid parameter!!!");
                break;
        }
    }
    getCalibrationPara(magXMaxMin,magYMaxMin,magZMaxMin,magOffset_s,magOffset_b);
    fclose(fp);
    return;
}


int main(void)
{
    // read data
    read();

    system("pause");

    return 0;
}