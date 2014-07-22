/**
 * @file lsd_opencv_example.cpp
 *
 * Test the LSD algorithm with OpenCV
 */
#include <highgui.h>
#include <cv.h>
#include <lsd.h>

int main(int argc, char **argv)
{
    cv::Mat src = cv::imread("./../../images/test.jpg", CV_LOAD_IMAGE_COLOR);
    cv::Mat tmp, src_gray;
    cv::cvtColor(src, tmp, CV_RGB2GRAY);
    tmp.convertTo(src_gray, CV_64FC1);

    int cols  = src_gray.cols;
    int rows = src_gray.rows;

    image_double image = new_image_double(cols, rows);
    image->data = src_gray.ptr<double>(0);
    ntuple_list ntl = lsd(image);

    cv::Mat lsd = cv::Mat::zeros(rows, cols, CV_8UC1);

    for (int j = 0; j != ntl->size ; ++j)
    {
        cv::Point pt1, pt2;
        pt1.x = ntl->values[0 + j * ntl->dim];
        pt1.y = ntl->values[1 + j * ntl->dim];
        pt2.x = ntl->values[2 + j * ntl->dim];
        pt2.y = ntl->values[3 + j * ntl->dim];
        cv::line(lsd, pt1, pt2, cv::Scalar(255), 1, CV_AA);
    }
    free_ntuple_list(ntl);

    cv::namedWindow("src", CV_WINDOW_AUTOSIZE);
    cv::imshow("src", src);
    cv::namedWindow("lsd", CV_WINDOW_AUTOSIZE);
    cv::imshow("lsd", lsd);
    cv::waitKey(0);
    cv::destroyAllWindows();
}