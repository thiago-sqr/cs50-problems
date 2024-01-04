#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum = 0;

            sum += image[i][j].rgbtRed;
            sum += image[i][j].rgbtGreen;
            sum += image[i][j].rgbtBlue;

            int avg = round(sum / 3.0);

            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            RGBTRIPLE aux = image[i][j];
            image[i][j] = image[i][(width - 1) - j];
            image[i][(width - 1) - j] = aux;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumRed = 0, sumGreen = 0, sumBlue = 0;
            int counter = 0;

            for (int a = i - 1; a <= i + 1; a++)
            {
                for (int b = j - 1; b <= j + 1; b++)
                {
                    if ((a >= 0 && a < height) && (b >= 0 && b < width))
                    {
                        sumRed += copy[a][b].rgbtRed;
                        sumGreen += copy[a][b].rgbtGreen;
                        sumBlue += copy[a][b].rgbtBlue;
                        counter++;
                    }
                }
            }

            image[i][j].rgbtRed = round(sumRed / (float) counter);
            image[i][j].rgbtGreen = round(sumGreen / (float) counter);
            image[i][j].rgbtBlue = round(sumBlue / (float) counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int GXsumRed = 0, GXsumGreen = 0, GXsumBlue = 0;
            int GYsumRed = 0, GYsumGreen = 0, GYsumBlue = 0;

            for (int a = i - 1, u = 0; a <= i + 1; a++)
            {
                for (int b = j - 1, v = 0; b <= j + 1; b++)
                {
                    if ((a >= 0 && a < height) && (b >= 0 && b < width))
                    {
                        GXsumRed += copy[a][b].rgbtRed * Gx[u][v];
                        GXsumGreen += copy[a][b].rgbtGreen * Gx[u][v];
                        GXsumBlue += copy[a][b].rgbtBlue * Gx[u][v];

                        GYsumRed += copy[a][b].rgbtRed * Gy[u][v];
                        GYsumGreen += copy[a][b].rgbtGreen * Gy[u][v];
                        GYsumBlue += copy[a][b].rgbtBlue * Gy[u][v];
                    }
                    v++;
                }
                u++;
            }

            int newRedValue = round(sqrt(pow(GXsumRed, 2) + pow(GYsumRed, 2)));
            image[i][j].rgbtRed = (newRedValue > 255) ? 255 : newRedValue;

            int newGreenValue = round(sqrt(pow(GXsumGreen, 2) + pow(GYsumGreen, 2)));
            image[i][j].rgbtGreen = (newGreenValue > 255) ? 255 : newGreenValue;

            int newBlueValue = round(sqrt(pow(GXsumBlue, 2) + pow(GYsumBlue, 2)));
            image[i][j].rgbtBlue = (newBlueValue > 255) ? 255 : newBlueValue;
        }
    }
    return;
}
