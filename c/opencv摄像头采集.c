#include "highgui.h"

int main()
{
    CvCapture* pCap = cvCreateCameraCapture( -1 );
    IplImage *frame = NULL;

    if (cvCreateCameraCapture == NULL)
    {
        return(0);
    }

    cvNamedWindow("Camera",CV_WINDOW_FULLSCREEN);
    while ((frame = cvQueryFrame(pCap)) != 0 &&  cvWaitKey(20) != 27)
    {
        frame = cvQueryFrame(pCap);
        cvShowImage("Camera", frame);
    }

    cvReleaseCapture(&pCap);
    cvDestroyWindow("Camera");
    return (0);
}
