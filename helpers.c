#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    float greyval;

    for(int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            greyval = (float) (image[i][j].rgbtBlue + (float) image[i][j].rgbtGreen + (float) image[i][j].rgbtRed ) / 3.0;

            image[i][j].rgbtBlue = round(greyval);
            image[i][j].rgbtRed = round(greyval);
            image[i][j].rgbtGreen = round(greyval);
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float newRed, newGreen, newBlue;

            newRed = (float) 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            newGreen = (float) 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            newBlue = (float) 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;

            if (newBlue > 255)
            {
                newBlue = 255;
            }

            if (newRed > 255)
            {
                newRed = 255;
            }

            if (newGreen > 255)
            {
                newGreen = 255;
            }

            image[i][j].rgbtRed = round(newRed);
            image[i][j].rgbtGreen = round(newGreen);
            image[i][j].rgbtBlue = round(newBlue);
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            BYTE tempBlue, tempRed, tempGreen;

            tempBlue = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = tempBlue;

            tempRed = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tempRed;

            tempGreen = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tempGreen;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float FinalBlue = 0, FinalGreen = 0, FinalRed = 0;

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
                        FinalBlue += image[i + m][j + n].rgbtBlue;
                        FinalRed += image[i + m][j + n].rgbtRed;
                        FinalGreen += image[i + m][j + n].rgbtGreen;
                        count++;
                    }
                }
            }

            copy[i][j].rgbtBlue = round(FinalBlue / (float) count);
            copy[i][j].rgbtGreen = round(FinalGreen / (float) count);
            copy[i][j].rgbtRed = round(FinalRed / (float) count);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
        }
    }
}
