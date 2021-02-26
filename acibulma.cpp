#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp> #include<opencv2/opencv.hpp> #include<iostream> #include<Windows.h> #include<math.h>
using namespace cv;
using namespace std;
//Point2f noktalar[3]; vector<Point>nokta;
Mat resim = imread("aci.png");

int egim(Point nok1, Point nok2)
{
    int val = (nok2.y - nok1.y) / (nok2.x - nok1.x);

    return val;
}
void aci(vector<Point> &nokta)
{

    float m1 = egim(nokta[0], nokta[1]);
    float m2 = egim(nokta[0], nokta[2]);
    float aciTan = atan((m2 - m1) / (1 + (m1 * m2)));
    double aciD = round((aciTan * 180) / CV_PI);
    cout << aciD;
    line(resim, nokta[0], nokta[1], Scalar::all(129), 3);
    line(resim, nokta[0], nokta[2], Scalar::all(129), 3);
}
void fareHareketi(int event, int x, int y, int flags, void *veri)
{

    if (event == EVENT_LBUTTONDOWN)
    {
        nokta.push_back(Point(x, y));
    }
    if (nokta.size() == 3)
    {
        for (int i = 0; i < 3; i++)
        {
            circle(resim, nokta[i], 2, Scalar::all(0), 3);
            cout << "Nokta" << i + 1 << ":" << nokta[i];
        }
        aci(nokta);
    }

    if (nokta.size() % 3 == 0 && nokta.size() != 0)
        nokta.clear();
}

int main()
{

    namedWindow("Resim", WINDOW_AUTOSIZE);
    while (true)
    {
        setMouseCallback("Resim", fareHareketi, NULL);
        imshow("Resim", resim);

        waitKey(1);
    }
}
