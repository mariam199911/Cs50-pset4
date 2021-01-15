#include "helpers.h"
#include "math.h"
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float y = ((image[h][w].rgbtRed + image[h][w].rgbtGreen + image[h][w].rgbtBlue) / 3.0);
            
            image[h][w].rgbtRed = round(y);
            image[h][w].rgbtGreen = round(y);
            image[h][w].rgbtBlue = round(y);
        }
    }
    return;
}
void swap(RGBTRIPLE *p1, RGBTRIPLE *p2)
{
    RGBTRIPLE t = *p1;
    *p1 = *p2;
    *p2 = t;
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width / 2; w++)
        {
            if (w < width && h < height)
            {
                swap(&image[h][w], &image[h][width - 1 - w]);
            }
        }
    }
    return;
}

// Blur image


void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int o = 0; o < height; o++)
    {
        for (int u = 0; u < width; u++)
        {
            copy[o][u].rgbtRed = image[o][u].rgbtRed;
            copy[o][u].rgbtGreen = image[o][u].rgbtGreen;
            copy[o][u].rgbtBlue = image[o][u].rgbtBlue;
            
        }    
    }        
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float count = 0.0;
            int sumred = 0;
            int sumblue = 0;
            int sumgreen = 0;
            for (int h1 = h - 1 ; h1 <= h + 1; h1++)
            {
                if (h1 < 0 || h1 >= height)
                {
                    continue;
                }
                for (int w1 = w - 1; w1 <= w + 1; w1++)
                {  
                    if (w1 < 0 || w1 >= width)
                    {
                        continue;
                    }
                    count++;
                    sumred += copy[h1][w1].rgbtRed;
                    sumgreen += copy[h1][w1].rgbtGreen;
                    sumblue += copy[h1][w1].rgbtBlue;
                }
            }
            image[h][w].rgbtRed = round((float)sumred / count);
            image[h][w].rgbtGreen = round((float)sumgreen / count);
            image[h][w].rgbtBlue = round((float)sumblue / count);
        }
    }    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int o = 0; o < height; o++)
    {
        for (int u = 0; u < width; u++)
        {
            copy[o][u].rgbtRed = image[o][u].rgbtRed;
            copy[o][u].rgbtGreen = image[o][u].rgbtGreen;
            copy[o][u].rgbtBlue = image[o][u].rgbtBlue;
            
        }    
    }   
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int GX_red = 0;
            int GX_Green = 0;
            int GX_Blue = 0;
            int GY_red = 0; 
            int GY_Green = 0;
            int GY_Blue = 0;
            if (h - 1 < 0 && w - 1 < 0)
            {
                GX_red = (2 * copy[h][w + 1].rgbtRed + copy[h + 1][w + 1].rgbtRed);
                GX_Green = (2 * copy[h][w + 1].rgbtGreen + copy[h + 1][w + 1].rgbtGreen);
                GX_Blue = (2 * copy[h][w + 1].rgbtBlue + copy[h + 1][w + 1].rgbtBlue);
                //GY
                GY_red = (copy[h + 1][w + 1].rgbtRed + 2 * copy[h + 1][w].rgbtRed);
                GY_Green = (copy[h + 1][w + 1].rgbtGreen + 2 * copy[h + 1][w].rgbtGreen);
                GY_Blue = (copy[h + 1][w + 1].rgbtBlue + 2 * copy[h + 1][w].rgbtBlue);
            }
            else if (h - 1 < 0 && w + 1 > width)
            {
                GX_red = (-2 * copy[h][w - 1].rgbtRed - copy[h + 1][w - 1].rgbtRed);
                GX_Green = (-2 * copy[h][w - 1].rgbtGreen - copy[h + 1][w - 1].rgbtGreen);
                GX_Blue = (-2 * copy[h][w - 1].rgbtBlue - copy[h + 1][w - 1].rgbtBlue);
                //GY
                GY_red = (2 * copy[h + 1][w].rgbtRed + copy[h + 1][w - 1].rgbtRed);
                GY_Green = (2 * copy[h + 1][w].rgbtGreen + copy[h + 1][w - 1].rgbtGreen);
                GY_Blue = (2 * copy[h + 1][w].rgbtBlue + copy[h + 1][w - 1].rgbtBlue);
            }
            else if (h + 1 >= height && w - 1 < 0)
            {
                GX_red = (copy[h - 1][w + 1].rgbtRed + 2 * copy[h][w + 1].rgbtRed);
                GX_Green = (copy[h - 1][w + 1].rgbtGreen + 2 * copy[h][w + 1].rgbtGreen);
                GX_Blue = (copy[h - 1][w + 1].rgbtBlue + 2 * copy[h][w + 1].rgbtBlue);
                //GY
                GY_red = (-2 * copy[h - 1][w].rgbtRed - copy[h - 1][w + 1].rgbtRed);
                GY_Green = (-2 * copy[h - 1][w].rgbtGreen - copy[h - 1][w + 1].rgbtGreen);
                GY_Blue = (-2 * copy[h - 1][w].rgbtBlue - copy[h - 1][w + 1].rgbtBlue);
            }
            else if (h + 1 >=  height && w + 1 >= width)
            {
                GX_red = (-copy[h - 1][w - 1].rgbtRed - 2 * copy[h][w - 1].rgbtRed);
                GX_Green = (-copy[h - 1][w - 1].rgbtGreen - 2 * copy[h][w - 1].rgbtGreen);
                GX_Blue = (-copy[h - 1][w - 1].rgbtBlue - 2 * copy[h][w - 1].rgbtBlue);
                //GY
                GY_red = (-2 * copy[h - 1][w].rgbtRed - copy[h - 1][w - 1].rgbtRed);
                GY_Green = (-2 * copy[h - 1][w].rgbtGreen - copy[h - 1][w - 1].rgbtGreen);
                GY_Blue = (-2 * copy[h - 1][w].rgbtBlue - copy[h - 1][w - 1].rgbtBlue);
            }
            else if (w - 1 < 0)
            {
                GX_red = (copy[h - 1][w + 1].rgbtRed + 2 * copy[h][w + 1].rgbtRed + copy[h + 1][w + 1].rgbtRed);
                GX_Green = (copy[h - 1][w + 1].rgbtGreen + 2 * copy[h][w + 1].rgbtGreen + copy[h + 1][w + 1].rgbtGreen);
                GX_Blue = (copy[h - 1][w + 1].rgbtBlue + 2 * copy[h][w + 1].rgbtBlue + copy[h + 1][w + 1].rgbtBlue);
                //GY
                GY_red = (-2 * copy[h - 1][w].rgbtRed - copy[h - 1][w + 1].rgbtRed + copy[h + 1][w + 1].rgbtRed + 2 * copy[h + 1][w].rgbtRed);
                GY_Green = (-2 * copy[h - 1][w].rgbtGreen - copy[h - 1][w + 1].rgbtGreen + copy[h + 1][w + 1].rgbtGreen + 2 * copy[h +
                            1][w].rgbtGreen);
                GY_Blue = (-2 * copy[h - 1][w].rgbtBlue - copy[h - 1][w + 1].rgbtBlue + copy[h +  1][w + 1].rgbtBlue + 2 * copy[h + 1][w].rgbtBlue);
            }
            else if (w + 1 >= width)
            {
                GX_red = (-copy[h - 1][w - 1].rgbtRed - 2 * copy[h][w - 1].rgbtRed - copy[h + 1][w - 1].rgbtRed);
                GX_Green = (-copy[h - 1][w - 1].rgbtGreen - 2 * copy[h][w - 1].rgbtGreen - copy[h + 1][w - 1].rgbtGreen);
                GX_Blue = (-copy[h - 1][w - 1].rgbtBlue - 2 * copy[h][w - 1].rgbtBlue - copy[h + 1][w - 1].rgbtBlue);
                //GY
                GY_red = (-2 * copy[h - 1][w].rgbtRed - copy[h - 1][w - 1].rgbtRed + 2 * copy[h + 1][w].rgbtRed + copy[h + 1][w - 1].rgbtRed);
                GY_Green = (-2 * copy[h - 1][w].rgbtGreen - copy[h - 1][w - 1].rgbtGreen + 2 * copy[h + 1][w].rgbtGreen + copy[h + 1][w -
                            1].rgbtGreen);
                GY_Blue = (-2 * copy[h - 1][w].rgbtBlue - copy[h - 1][w - 1].rgbtBlue + 2 * copy[h + 1][w].rgbtBlue + copy[h + 1][w - 1].rgbtBlue);
            }        
            else if (h + 1 >= height)
            {
                //GX
                GX_red = (-copy[h - 1][w - 1].rgbtRed - 2 * copy[h][w - 1].rgbtRed + copy[h - 1][w + 1].rgbtRed + 2 * copy[h][w + 1].rgbtRed);
                GX_Green = (-copy[h - 1][w - 1].rgbtGreen - 2 * copy[h][w - 1].rgbtGreen + copy[h - 1][w + 1].rgbtGreen + 2 * copy[h][w +
                            1].rgbtGreen);
                GX_Blue = (-copy[h - 1][w - 1].rgbtBlue - 2 * copy[h][w - 1].rgbtBlue + copy[h - 1][w + 1].rgbtBlue + 2 * copy[h][w + 1].rgbtBlue);
                //GY
                GY_red = (-2 * copy[h - 1][w].rgbtRed - copy[h - 1][w - 1].rgbtRed - copy[h - 1][w + 1].rgbtRed);
                GY_Green = (-2 * copy[h - 1][w].rgbtGreen - copy[h - 1][w - 1].rgbtGreen - copy[h - 1][w + 1].rgbtGreen);
                GY_Blue = (-2 * copy[h - 1][w].rgbtBlue - copy[h - 1][w - 1].rgbtBlue - copy[h - 1][w + 1].rgbtBlue);
            }
            else if (h - 1 < 0)
            {
                GX_red = (-2 * copy[h][w - 1].rgbtRed - copy[h + 1][w - 1].rgbtRed + 2 * copy[h][w + 1].rgbtRed + copy[h + 1][w + 1].rgbtRed);
                GX_Green = (-2 * copy[h][w - 1].rgbtGreen - copy[h + 1][w - 1].rgbtGreen + 2 * copy[h][w + 1].rgbtGreen + copy[h + 1][w +
                            1].rgbtGreen);
                GX_Blue = (-2 * copy[h][w - 1].rgbtBlue - copy[h + 1][w - 1].rgbtBlue + 2 * copy[h][w + 1].rgbtBlue + copy[h + 1][w + 1].rgbtBlue);
                //GY
                GY_red = (copy[h + 1][w + 1].rgbtRed + 2 * copy[h + 1][w].rgbtRed + copy[h + 1][w - 1].rgbtRed);
                GY_Green = (copy[h + 1][w + 1].rgbtGreen + 2 * copy[h + 1][w].rgbtGreen + copy[h + 1][w - 1].rgbtGreen);
                GY_Blue = (copy[h + 1][w + 1].rgbtBlue + 2 * copy[h + 1][w].rgbtBlue + copy[h + 1][w - 1].rgbtBlue);
            }
            
            else
            {
                GX_red = (-1 * copy[h - 1][w - 1].rgbtRed - 2 * copy[h][w - 1].rgbtRed - copy[h + 1][w - 1].rgbtRed + copy[h - 1][w + 1].rgbtRed + 2
                          * copy[h][w + 1].rgbtRed + copy[h + 1][w + 1].rgbtRed);
                GX_Green = (-1 * copy[h - 1][w - 1].rgbtGreen - 2 * copy[h][w - 1].rgbtGreen - copy[h + 1][w - 1].rgbtGreen + copy[h - 1][w + 
                            1].rgbtGreen + 2 * copy[h][w + 1].rgbtGreen + copy[h + 1][w + 1].rgbtGreen);
                GX_Blue = (-1 * copy[h - 1][w - 1].rgbtBlue - 2 * copy[h][w - 1].rgbtBlue - copy[h + 1][w - 1].rgbtBlue + copy[h - 1][w +
                           1].rgbtBlue + 2 * copy[h][w + 1].rgbtBlue + copy[h + 1][w + 1].rgbtBlue);
                //GY
                GY_red = (-2 * copy[h - 1][w].rgbtRed - copy[h - 1][w - 1].rgbtRed - copy[h - 1][w + 1].rgbtRed + copy[h + 1][w + 1].rgbtRed + 2 * 
                          copy[h + 1][w].rgbtRed + copy[h + 1][w - 1].rgbtRed);
                GY_Green = (-2 * copy[h - 1][w].rgbtGreen - copy[h - 1][w - 1].rgbtGreen - copy[h - 1][w + 1].rgbtGreen + copy[h + 1][w + 
                            1].rgbtGreen + 2 * copy[h + 1][w].rgbtGreen + copy[h + 1][w - 1].rgbtGreen);
                GY_Blue = (-2 * copy[h - 1][w].rgbtBlue - copy[h - 1][w - 1].rgbtBlue - copy[h - 1][w + 1].rgbtBlue + copy[h + 1][w + 1].rgbtBlue +
                           2 * copy[h + 1][w].rgbtBlue + copy[h + 1][w - 1].rgbtBlue);
            }
            
            /*image[h][w].rgbtRed= round((float)sqrt((GX_red*GX_red)+(GY_red*GY_red)));
            image[h][w].rgbtGreen= round((float)sqrt((GX_Green*GX_Green)+(GY_Green*GY_Green)));
            image[h][w].rgbtBlue= round((float)sqrt((GX_Blue*GX_Blue)+(GY_Blue*GY_Blue)));
            if(image[h][w].rgbtRed>255)
            image[h][w].rgbtRed=225;
            if(image[h][w].rgbtGreen>255)
            image[h][w].rgbtGreen=255;
            if(image[h][w].rgbtBlue>255)
            image[h][w].rgbtBlue=255;*/
 
            if (round(sqrt((GX_red * GX_red) + (GY_red * GY_red))) > 255)
            {
                image[h][w].rgbtRed = 255;
            }
            else
            {
                image[h][w].rgbtRed = round((float)sqrt((GX_red * GX_red) + (GY_red * GY_red)));
            }
            if (round(sqrt((GX_Green * GX_Green) + (GY_Green * GY_Green))) > 255)
            {
                image[h][w].rgbtGreen = 255;
            }
            else
            {
                image[h][w].rgbtGreen = round((float)sqrt((GX_Green * GX_Green) + (GY_Green * GY_Green)));
            }
            if (round(sqrt((GX_Blue * GX_Blue) + (GY_Blue * GY_Blue))) > 255)
            {
                image[h][w].rgbtBlue = 255;
            }
            else
            {
                image[h][w].rgbtBlue = round((float)sqrt((GX_Blue * GX_Blue) + (GY_Blue * GY_Blue)));
            }
        }
    }
    return;
}