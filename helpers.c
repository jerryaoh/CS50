#include "helpers.h"
#include <math.h>

typedef struct
{
    int blue;
    int red;
    int green;
}
matrix;

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float greyval;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            greyval = (float) (image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0;
            image[i][j].rgbtBlue = round(greyval);
            image[i][j].rgbtRed = round(greyval);
            image[i][j].rgbtGreen = round(greyval);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE tempGreen, tempBlue, tempRed;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            tempGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tempGreen;

            tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = tempBlue;

            tempRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tempRed;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float sumGreen = 0, sumRed = 0, sumBlue = 0;

            for (int m = -1; m < 2; m++)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (i + m < 0 || j + n < 0)
                    {
                        continue;
                    }

                    else if (i + m >= height || j + n >= width)
                    {
                        continue;
                    }

                    else
                    {
                        sumGreen += image[i + m][j + n].rgbtGreen;
                        sumBlue += image[i + m][j + n].rgbtBlue;
                        sumRed += image[i + m][j + n].rgbtRed;
                        count++;
                    }
                }
            }

            copy[i][j].rgbtGreen = round(sumGreen / (float) count);
            copy[i][j].rgbtBlue = round(sumBlue / (float) count);
            copy[i][j].rgbtRed = round(sumRed / (float) count);
        }
    }

    for (int i = 0; i < height ; i++)
    {
        for (int j = 0; j < height; j++)
        {
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    matrix GX[height][width], GY[height][width], Final[height][width];

    // Computing GX
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int n = -1; n < 2; n += 2)
            {
                for (int m = -1; m < 2; m++)
                {
                    if (i + m < 0 || j + n < 0)
                    {
                        continue;
                    }

                    if (i + m >= height || j + n >= width)
                    {
                        continue;
                    }
                    else
                    {
                        if (m == -1 || m == 1)
                        {
                            GX[i][j].blue += image[i + m][j + n].rgbtBlue * n;
                            GX[i][j].red += image[i + m][j + n].rgbtBlue * n;
                            GX[i][j].green += image[i + m][j + n].rgbtBlue * n;
                        }

                        else if (m == 0)
                        {
                            GX[i][j].blue += image[i + m][j + n].rgbtBlue * 2 * n;
                            GX[i][j].red += image[i + m][j + n].rgbtRed * 2 * n;
                            GX[i][j].green += image[i + m][j + n].rgbtGreen * 2 * n;
                        }
                    }
                }
            }
        }
    }

    // Computing GY
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int m = -1; m < 2; m += 2)
            {
                for (int n = -1; n < 2; n++)
                {
                    if (i + m < 0 || j + n < 0)
                    {
                        continue;
                    }

                    if (i + m >= height || j + n >= width)
                    {
                        continue;
                    }

                    else
                    {
                        if (n == -1 || n == 1)
                        {
                            GY[i][j].blue += image[i + m][j + n].rgbtBlue * m;
                            GY[i][j].red += image[i + m][j + n].rgbtBlue * m;
                            GY[i][j].green += image[i + m][j + n].rgbtBlue * m;
                        }

                        else if (n == 0)
                        {
                            GY[i][j].blue += image[i + m][j + n].rgbtBlue * 2 * m;
                            GY[i][j].red += image[i + m][j + n].rgbtRed * 2 * m;
                            GY[i][j].green += image[i + m][j + n].rgbtGreen * 2 * m;
                        }
                    }
                }
            }
        }
    }

    // Calculate square root of GX^2 and GY^2
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float s_blue = pow(GX[i][j].blue, 2) + pow(GY[i][j].blue, 2);
            float s_green = pow(GX[i][j].green, 2) + pow(GY[i][j].green, 2);
            float s_red = pow(GX[i][j].red, 2) + pow(GY[i][j].red, 2);
            float x = round(sqrt(s_blue));
            float y = round(sqrt(s_green));
            float z = round(sqrt(s_red));

            if (x > 255)
            {
                x = 255;
            }
            if (y > 255)
            {
                y = 255;
            }
            if (z > 255)
            {
                z = 255;
            }

            image[i][j].rgbtBlue = x;
            image[i][j].rgbtGreen = y;
            image[i][j].rgbtRed = z;
        }
    }
}
