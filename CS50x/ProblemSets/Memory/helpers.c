#include "helpers.h"
#include <math.h>

// Constants
#define COLOR 3
#define SOBEL 3
#define MAX 255

// 修复bug5：Gy数组赋值错误的问题
int Gx[SOBEL][SOBEL] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
int Gy[SOBEL][SOBEL] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE ave;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // 修复bug1：没有四舍五入到最接近整数 | 注意"整型提升"规则
            ave = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.);
            image[i][j].rgbtBlue = ave;
            image[i][j].rgbtGreen = ave;
            image[i][j].rgbtRed = ave;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid = width / 2;
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < mid; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// A function to help with blur
void help_blur(int x, int y, int height, int width, RGBTRIPLE image[height][width],
               RGBTRIPLE tmp[height][width])
{
    // 错误代码, 尝试使用结构体分别来记录RGB的和值, 但是BYTE类型到达255就溢出回到0导致求和错误
    // RGBTRIPLE sum = {0, 0, 0};

    // 修复bug4：应使用int来保存RGB各像素的值, 如果使用上面的结构体会溢出导致结果出错
    int sum[COLOR] = {0};
    int total = 0;

    // 修复bug2：i, j计数范围, 均为+2
    for (int i = x - 1; i < x + 2; i++)
    {
        for (int j = y - 1; j < y + 2; j++)
        {
            if (i < 0 || j < 0 || i > height - 1 || j > width - 1)
                continue;
            else
            {
                total++;
                sum[0] += image[i][j].rgbtBlue;
                sum[1] += image[i][j].rgbtGreen;
                sum[2] += image[i][j].rgbtRed;
            }
        }
    }

    // 修复bug3：使用临时数组tmp来存储结果，而不是直接覆盖原数组影响后续值的计算
    tmp[x][y].rgbtBlue = round(sum[0] / (double) total);
    tmp[x][y].rgbtGreen = round(sum[1] / (double) total);
    tmp[x][y].rgbtRed = round(sum[2] / (double) total);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            help_blur(i, j, height, width, image, tmp);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}

// A function to help with detecting edges
void help_edges(int x, int y, int height, int width, RGBTRIPLE image[height][width],
                RGBTRIPLE tmp[height][width])
{
    // 解决和Blur实现一样的溢出问题
    // RGBTRIPLE gx = {0, 0, 0}, gy = {0, 0, 0};

    int gx[COLOR] = {0}, gy[COLOR] = {0};
    int x_start = 0, y_start = 0;
    for (int i = x - 1; i < x + 2; i++)
    {
        for (int j = y - 1; j < y + 2; j++)
        {
            if (i < 0 || j < 0 || i > height - 1 || j > width - 1)
            {
                // 修复bug6：若continue，则y_start未能正确更新
                // continue;
                // do nothing
            }
            else
            {
                gx[0] += Gx[x_start][y_start] * image[i][j].rgbtBlue;
                gx[1] += Gx[x_start][y_start] * image[i][j].rgbtGreen;
                gx[2] += Gx[x_start][y_start] * image[i][j].rgbtRed;
                gy[0] += Gy[x_start][y_start] * image[i][j].rgbtBlue;
                gy[1] += Gy[x_start][y_start] * image[i][j].rgbtGreen;
                gy[2] += Gy[x_start][y_start] * image[i][j].rgbtRed;
            }
            y_start++;
        }
        y_start = 0;
        x_start++;
    }

    // 修复bug7：若结果>255, 应该取255, 而不是溢出后取余的值
    int blue = round(sqrt(gx[0] * gx[0] + gy[0] * gy[0]));
    int green = round(sqrt(gx[1] * gx[1] + gy[1] * gy[1]));
    int red = round(sqrt(gx[2] * gx[2] + gy[2] * gy[2]));
    tmp[x][y].rgbtBlue = blue > MAX ? MAX : blue;
    tmp[x][y].rgbtGreen = green > MAX ? MAX : green;
    tmp[x][y].rgbtRed = red > MAX ? MAX : red;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            help_edges(i, j, height, width, image, tmp);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp[i][j];
        }
    }
    return;
}
