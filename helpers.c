#include "helpers.h"
#include <math.h>

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
    return;
}
