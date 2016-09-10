void RGB565TGRAY(uchar* imageDataRGB , uchar* pGray , int width , int height)
{
    uchar   gm_red, gm_green, gm_blue;
    uchar   *p;
    ushort  *pt;

    int i,j;
    pt = (ushort *)imageDataRGB;
    p = pGray;
    for(i=0 ; i < height ; i++)
    {
        for(j=0 ; j < width ; j++)
        {
               gm_red       = ((*(ushort *)pt) & 0xF800) >> 8;
               gm_green     = ((*(ushort *)pt) & 0x07E0) >> 3;
               gm_blue      = ((*(ushort *)pt) & 0x001F) <<  3;
               p[0] = ( uchar )((gm_red*77+gm_green*150+gm_blue*29+128)/256);

               if(p[0] > 255)
               {
                   p[0]=255;
               }

               if(p[0] < 0)
               {
                   p[0]=0;
               }
               p++;
               pt++;
        }
    }
}
