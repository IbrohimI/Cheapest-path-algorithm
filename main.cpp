#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <list>

using namespace std;

class mountainType
{
public:
    list<int> exitX;
    list<int> exitY;
    list<int>::iterator exitXItr;
    list<int>::iterator exitYItr;
    double seed[100][100][1];
    double perlin[100][100][1];
    double perlinOut[100][100][1];
    double sampling;
    int numOfScaleFactor;
    int length;
    int row;
public:
    mountainType()
    {
        length = 100;
        row = 100;
        numOfScaleFactor = 7;
        srand(time(0));
        for(int index1 = 0; index1 < row; index1++)
        {
            for(int index2 = 0; index2 < length; index2++)
            {
                seed[index1][index2][1] = rand() % 300;
                perlin[index1][index2][1] = 0;
                perlinOut[index1][index2][1] = 0;
            }
        }
    }
    void makeTerrain()
    {
        for(int index1 = 0; index1 < row; index1++)
        {
            for( int index2 = 0; index2 < length; index2++)
            {
                float fNoise = 0.0f;
                float fScale = 1.0f;
                float fScaleACC = 0.0f;
                for(int index3 = 0; index3 < numOfScaleFactor; index3++)
                {
                    int nPitch = row >> index3;
                    int nSample1Y = (index2 / nPitch) * nPitch;
                    int nSample2Y = (nSample1Y + nPitch) % row;

                    int nSample1X = (index1 / nPitch) * nPitch;
                    int nSample2X = (nSample1X + nPitch) % row;

                    float fBlendY = float(index2 - nSample1Y) / float(nPitch);
                    float fBlendX = float(index1 - nSample1X) / float(nPitch);

                    float fSampleT = (1.0f - fBlendY) * seed[nSample1X][nSample1Y][1] + fBlendY * seed[nSample1X][nSample2Y][1];
                    float fSampleB = (1.0f - fBlendY) * seed[nSample2X][nSample1Y][1] + fBlendY * seed[nSample2X][nSample2Y][1];

                    fNoise += (fBlendX * (fSampleB - fSampleT) + fSampleT) * fScale;
                    fScaleACC += fScale;
                    fScale = fScale / 2.0f;
                }
                perlin[index1][index2][1] = fNoise / fScaleACC;
            }
        }
    }
    void findExit()
    {
        int objectX;
        int objectY;

        srand(time(0));
        objectX = rand() % 100;
        objectY = rand() % 100;

        exitX.push_back(objectX);
        exitY.push_back(objectY);

        double temp = perlin[objectX][objectY][1];

        int temp1X = objectX;
        int temp2X = objectX;
        int temp3X = objectX;
        int temp4X = objectX;
        int temp5X = objectX;
        int temp6X = objectX;
        int tempX = objectX;

        int temp1Y = objectY;
        int temp2Y = objectY;
        int temp3Y = objectY;
        int temp4Y = objectY;
        int temp5Y = objectY;
        int temp6Y = objectY;
        int tempY = objectY;

        for(int index = 0; index < 100; index++)
        {
            double num1 = abs(temp - perlin[temp1X - 1][tempY][1]);
            double num2 = abs(temp - perlin[temp2X + 1][tempY][1]);
            double num3 = abs(temp - perlin[tempX][temp1Y - 1][1]);
            double num4 = abs(temp - perlin[tempX][temp2Y + 1][1]);
            double num5 = abs(temp - perlin[temp1X - 1][temp2Y + 1][1]);
            double num6 = abs(temp - perlin[temp2X + 1][temp1Y - 1][1]);
            double num7 = abs(temp - perlin[temp2X + 1][temp2Y + 1][1]);
            double num8 = abs(temp - perlin[temp1X - 1][temp1Y - 1][1]);


            if(num1 <= num2 && num1 <= num3 && num1 <= num4
               && num1 <= num5 && num1 <= num6 && num1 <= num7 && num1 <= num8)
            {
                temp1X = tempX - 1;
                exitX.push_back(temp1X);
                exitY.push_back(tempY);
                tempX = temp1X;
                temp = perlin[temp1X - 1][tempY][1];
                temp1X = temp1X - 1;
            }
            else if(num2 <= num1 && num2 <= num3 && num2 <= num4
               && num2 <= num5 && num2 <= num6 && num2 <= num7 && num2 <= num8)
            {
                temp2X = tempX + 1;
                exitX.push_back(temp2X);
                exitY.push_back(tempY);
                tempX = temp2X;
                temp = perlin[temp2X + 1][tempY][1];
                temp2X = temp2X + 1;
            }
            else if(num3 <= num1 && num3 <= num2 && num3 <= num4
               && num3 <= num5 && num3 <= num6 && num3 <= num7 && num3 <= num8)
            {
                temp1Y = tempY - 1;
                exitX.push_back(tempX);
                exitY.push_back(temp1Y);
                tempY = temp1Y;
                temp = perlin[tempX][temp1Y - 1][1];
                temp1Y = temp1Y - 1;
            }
            else if(num4 <= num1 && num4 <= num2 && num4 <= num3
               && num4 <= num5 && num4 <= num6 && num4 <= num7 && num4 <= num8)
            {
                temp2Y = tempY + 1;
                exitX.push_back(tempX);
                exitY.push_back(temp2Y);
                tempY = temp2Y;
                temp = perlin[tempX][temp2Y + 1][1];
                temp2Y = temp2Y + 1;
            }
            else if(num5 <= num1 && num5 <= num2 && num5 <= num3
               && num5 <= num4 && num5 <= num6 && num5 <= num7 && num5 <= num8)
               {
                   temp3X = tempX - 1;
                   temp3Y = tempY + 1;
                   exitX.push_back(temp3X);
                   exitY.push_back(temp3Y);
                   tempY = temp3Y;
                   tempX = temp3X;
                   temp = perlin[temp3X - 1][temp3Y + 1][1];
                   temp3Y = temp3Y + 1;
                   temp3X = temp3X - 1;
               }
            else if(num6 <= num1 && num6 <= num2 && num6 <= num3
               && num6 <= num4 && num6 <= num5 && num6 <= num7 && num6 <= num8)
               {
                   temp4X = tempX + 1;
                   temp4Y = tempY - 1;
                   exitX.push_back(temp4X);
                   exitY.push_back(temp4Y);
                   tempY = temp4Y;
                   tempX = temp4X;
                   temp = perlin[temp4X + 1][temp4Y - 1][1];
                   temp4Y = temp4Y - 1;
                   temp4X = temp4X + 1;
               }
               else if(num7 <= num1 && num7 <= num2 && num7 <= num3
               && num7 <= num4 && num7 <= num5 && num7 <= num6 && num7 <= num8)
               {
                   temp5X = tempX + 1;
                   temp5Y = tempY + 1;
                   exitX.push_back(temp5X);
                   exitY.push_back(temp5Y);
                   tempY = temp5Y;
                   tempX = temp5X;
                   temp = perlin[temp5X + 1][temp5Y + 1][1];
                   temp5Y = temp5Y + 1;
                   temp5X = temp5X + 1;
               }
               else if(num8 <= num1 && num8 <= num2 && num8 <= num3
               && num8 <= num4 && num8 <= num5 && num8 <= num6 && num8 <= num7)
               {
                   temp6X = tempX - 1;
                   temp6Y = tempY - 1;
                   exitX.push_back(temp6X);
                   exitY.push_back(temp6Y);
                   tempY = temp6Y;
                   tempX = temp6X;
                   temp = perlin[temp6X - 1][temp6Y - 1][1];
                   temp6Y = temp6Y - 1;
                   temp6X = temp6X - 1;
               }
            if(tempX <= 0 || tempX >= row - 1 || tempY <= 0 || tempY >= length - 1)
            {
                break;
            }
        }

        return;
    }
    void makeData()
    {
        ofstream outFile;
        outFile.open("data.txt");
        ofstream outFile1;
        outFile1.open("data1.txt");

        exitXItr = exitX.begin();
        exitYItr = exitY.begin();
        while(exitXItr != exitX.end())
        {
            perlinOut[*exitXItr][*exitYItr][1] = perlin[*exitXItr][*exitYItr][1];
            exitXItr++;
            exitYItr++;
        }

        for(int index1 = 0; index1 < row; index1++)
        {
            for(int index2 = 0; index2 < length; index2++)
            {
                outFile << "   " << perlin[index1][index2][1];
            }
            outFile << endl;
        }
        exitXItr = exitX.begin();
        exitYItr = exitY.begin();
        while(exitXItr != exitX.end())
        {
            outFile1 << *exitYItr << "   " << *exitXItr << "   " << perlinOut[*exitXItr][*exitYItr][1] << endl;
            exitXItr++;
            exitYItr++;
        }
    }
    void draw()
    {
        fstream comfout;
        comfout.open("command.txt",ios::out);
        comfout << "set terminal png" << endl;
        comfout << "set output \"output.png\"" << endl;

        comfout<<"set xlabel \"x location\""<<endl;
        comfout<<"set ylabel \"y location\""<<endl;

        comfout<<"set yrange [0:100]"<<endl;
        comfout<<"set xrange [0:100]"<<endl;
        comfout<<"set hidden3d trianglepattern 7"<< endl;
        comfout<<"splot \"data.txt\" matrix w l notitle, \"data1.txt\" u 1:2:3 w l lw 2 linecolor rgb \"black\" notitle"<< endl;
        //comfout<<"splot \"data1.txt\" w l notitle"<< endl;
        comfout<<"pause -1"<<endl;
        comfout.close();
        system("gnuplot command.txt");
    }
};

int main()
{
    mountainType mountain;
    mountain.makeTerrain();
    mountain.findExit();
    mountain.makeData();
    mountain.draw();

    return 0;
}
