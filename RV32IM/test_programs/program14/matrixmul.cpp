#include<stdio.h>
#include<stdlib.h>

void matrixmul(int image[40][40],int kernel[37][37], int result [4][4])
{

    for(int on_image_vindex=0; on_image_vindex<4;on_image_vindex++){
        for(int on_image_hindex=0; on_image_hindex<4;on_image_hindex++){
            for(int i=0;i < 37;i++){
                for(int j=0;j<37;j++){
                   result[on_image_vindex][on_image_hindex] = result[on_image_vindex][on_image_hindex] + image[on_image_vindex+i][on_image_hindex+j] * kernel[i][j];
                }
            }
        }
    }
}
