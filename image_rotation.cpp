#include<opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

Mat rotate(Mat src, double angle)
{
    Mat dst;

    //get rotation matrix for rotating the image around its center in pixel coordinates
    Point2f center(src.cols / 2., src.rows / 2.);
    Mat r = getRotationMatrix2D(center, angle, 1.0);

    //determine bounding rectangle,center not relevant
    Rect2f bbox = RotatedRect(Point2f(), src.size(), angle).boundingRect2f();

    // adjust transformation matrix
    r.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
    r.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;

    warpAffine(src, dst, r, bbox.size());
    return dst;
}

int main()
{
    string path;
    getline(cin, path);
    Mat src = imread(path);  //to read the path of the image

    Mat dst;
    double angle;
    cin >> angle;
    dst = rotate(src, angle);
    string windowname = "my flower image";
    namedWindow(windowname);  //shows the name of the window
    imshow("src", src);
    imshow(windowname, dst);
    waitKey(0);  // to destroy the window
    return 0;
}

