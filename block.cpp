#include "block.h"
#include <cmath>
#include <iostream>

int Block::width() const
{
    return data.size();
}

int Block::height() const
{
    if (data.size() != 0) {
        return data[0].size();
    } else {
        return 0;
    }
}

void Block::render(PNG &im, int column, int row) const
{
    for (int x = column; x < column + width(); x++) {
        for (int y = row; y < row + height(); y++) {
            *(im.getPixel(x,y)) = data[x-column][y-row];
        }
    }
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
    for (int x = column; x < column + width; x++){
        vector<HSLAPixel> col;
        for (int y = row; y < row + height; y++){
            HSLAPixel* pixel = im.getPixel(x,y);
            col.push_back(*pixel);
        }
        data.push_back(col);
    } 
}

void Block::flip()
{
    vector<vector<HSLAPixel>> newData;
    for(int x = 0; x < width(); x++){
        vector<HSLAPixel> col;
        for (int y = height() - 1; y >= 0; y--){
            col.push_back(data[x][y]);
        }
        newData.push_back(col);
    }
    data = newData;
}