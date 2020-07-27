#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>

using namespace cv;

using namespace std;

#define VERDE ((0 << 16) | (255 << 8) | 0)

int c;

int *colorsTxt = new int[256 * 256 * 256];

void loadFile(string file)
{
    for (int i = 0; i < 256 * 256 * 256; i++)
    {
        colorsTxt[i] = -1;
    }
    string line;
    ifstream inFile(file.c_str(), ios::in);
    if (inFile)
    {
        while (getline(inFile, line))
        {
            //cout << line << '\n';
            istringstream actualColor(line);
            actualColor >> c;
            //cout << colorsTxt[c] << endl;
            colorsTxt[c] = VERDE;
            //cout << colorsTxt[c] << endl;

            actualColor.str("");
        }
        inFile.close();
    }
    else
        cout << "could not open file" << endl;
}

void clustering(Mat img)
{
    int R, G, B;
    int col;
    for (int y = 0; y < img.rows; y++)
    {
        for (int x = 0; x < img.cols; x++)
        {
            Vec3b color = img.at<Vec3b>(y, x);
            B = (int)color.val[0];
            G = (int)color.val[1];
            R = (int)color.val[2];
            col = (B << 16) | (G << 8) | R;

            if (colorsTxt[col] != -1)
            {
                color.val[0] = 0;
                color.val[1] = 255;
                color.val[2] = 0;
            }
            img.at<Vec3b>(y, x) = color;
        }
    }
    imshow("Clusterized", img);
}

int main(int argc, char **argv)
{
    Mat img_rgb;
	loadFile("clustering.txt");
	img_rgb = imread(argv[1], CV_LOAD_IMAGE_COLOR);
    clustering(img_rgb);

    waitKey(0); // Wait for a keystroke in the window
    return 0;
}