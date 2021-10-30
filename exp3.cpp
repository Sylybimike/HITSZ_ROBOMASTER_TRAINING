#include <iostream>
#include <vector>
#include <math.h>
using namespace cv;
using namespace std;
//exp3

Mat Conv2D(Mat &src,int _size,Mat &kernel){
    assert(_size%2 == 1);
    int height = src.size().height;
    int width = src.size().width;
    Mat dst(src.size(),CV_8UC1);
    //use no pad
    int start_point = (_size-1)/2;

    for (int row=start_point;row<height-start_point;row++){         //fix one row
        for (int col=start_point;col<width-start_point;col++){      //fix one col
            double sum = 0;
            double val = 0;
            for (int i = 0; i < _size; ++i) {
                for (int j = 0; j < _size; ++j) {
                        //process one kernel area
                        val += float(kernel.at<uchar>[i][j])*float(src.at<uchar>[row-1+i][col-1+j]);
                }
            }
            sum += val;
            dst.at<uchar>(row,col) = uchar(val);
        }
    }
    dst = dst/sum;
    return dst;
}

Mat NMS(Mat &src){
    int height = src.size().height;
    int width = src.size().width;
    Mat dst = src.clone();
    for (int row=1;row<height-1;row++){         //fix one row
        for (int col=1;col<width-1;col++){      //fix one col
            std::vector<double> val;

            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    val.push_back(double(src.at<uchar>(row-1+i,col-1+j)));
                }
            }
            auto max = std::max_element(std::begin(val), std::end(val));
            if(std::distance(val.begin(),max)==4) dst.at<uchar>(row,col) = uchar(0);
        }
    }
    return dst;
}


Mat CannyThreshold(Mat &src,int lt,int ht){
    int height = src.size().height;
    int width = src.size().width;
    Mat dst = src.clone();
    for (int row=1;row<height-1;row++) {         //fix one row
        for (int col = 1; col < width - 1; col++) {      //fix one col
            if (int(src.at<uchar>(row,col)) >ht)
                dst.at<uchar>(row,col) = uchar(255);
            else if(int(src.at<uchar>(row,col)) < lt)
                dst.at<uchar>(row,col) = uchar(0);
            else{
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if(int(src.at<uchar>(row-1+i,col-1+j))>ht){
                            dst.at<uchar>(row,col) = uchar(255);
                        } else{
                            dst.at<uchar>(row,col) = uchar(0);
                        }
                    }
                }
            }
        }
    }
    return dst;
}

void MyCanny(Mat &src,double lt,double ht)
{
    //Gaussian

    //Sobel
    Mat kernel = getSobelElement(3);
    auto after_gradient = Conv2D(dst,3,kernel);

    //NMS
    auto after_NMS = NMS(after_gradient);

    //threshold
    auto after_threshold = CannyThreshold(after_NMS,lt,ht);

    imshow("after_threshold",after_threshold);
    waitKey(0);
}


const int rmax = 10;
const int rmin = 5;
void HoughLine(Mat &src,double theta_step,double r_step){
    //convert to gray img
    //pass
    //Canny
    Mat dst;
    int height = src.size().height;
    int width = src.size().width;
    Canny(src,dst,30,50);
    int r_range = (rmax-rmin)/r_step;
    vector<vector<int>> vote(r_range,vector<int>(CV_PI/theta_step,0));
    for(int row=0;row<height;row++){
        for (int col = 0; col < width; ++col) {
            //for each pixel we do:using tiny theta step to cal p,the pair(p,theta') will be voted;
            for(double theta=0;theta<CV_PI/theta_step;theta+=theta_step){
                int p = (row)*cos(theta) + (col)*sin(theta);
                if (p>rmin&&p<rmax&&(p%r_step)==0) {
                    int r_index = (p-rmin)/r_step;
                    int theta_index = (theta-0)/theta_step;
                    vote[r_index][theta_index]++;
                }
            }
        }
    }
    int max_r = 0;
    int max_theta = 0;
    int max_vote  = 0;
    for(int i=0;i<vote[0].size();++i){
        for(int j=0;j<vote.size();++j){
            if(vote[i][j]>max_vote){
                max_vote = vote[i][j];
                max_theta = j;
                max_r = i;
            }
        }
    }
    max_theta = ;
    max_r = rmin+r_step*max_r;
    max_theta = 0+theta_step*max_theta;

    Point start = (0,max_r/sin(max_theta));
    Point end = (max_r/cos(max_theta),0);
    line()
}
int main() {
    Mat src = imread("");
    cvtColor(src,src,CV_BGR2GRAY);
    MyCanny(src,30,50);
}
