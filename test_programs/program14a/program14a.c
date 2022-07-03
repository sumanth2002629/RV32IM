#include "firmware.h"

void conv40(void)
{
    int image[40][40];
    int  kernel[37][37];
    int  result[4][4];

    for(int i=0;i<40;i++)
    {
        for(int j=0;j<40;j++)
        {
            image[i][j] = 1;
        }
    }


    for(int i=0;i<37;i++)
    {
        for(int j=0;j<37;j++)
        {
            kernel[i][j] = 1;
        }
    }

   

    result[0][0] = 0; result[0][1] = 0; result[0][2] = 0; result[0][3] = 0;
    result[1][0] = 0; result[1][1] = 0; result[1][2] = 0; result[1][3] = 0;
    result[2][0] = 0; result[2][1] = 0; result[2][2] = 0; result[2][3] = 0;
    result[3][0] = 0; result[3][1] = 0; result[3][2] = 0; result[3][3] = 0;

    for(int on_image_vindex=0; on_image_vindex<(6-2);on_image_vindex++){
        for(int on_image_hindex=0; on_image_hindex<(6-2);on_image_hindex++){
            for(int i=0;i < 37;i++){
                for(int j=0;j<37;j++){
                   result[on_image_vindex][on_image_hindex] = result[on_image_vindex][on_image_hindex] + image[on_image_vindex+i][on_image_hindex+j] * kernel[i][j];
                }
            }
        }
    }
    


}
