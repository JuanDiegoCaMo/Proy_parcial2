#ifndef PIX_MAT_H
#define PIX_MAT_H

#include <vector>
#include <QImage>

using namespace std;

class pix_mat
{
public:
    pix_mat(QImage image_dir);
private:
    vector<short int[3][8][8]> pixel;
    short int **mat;
    int *auxX, *auxY;
};

#endif // PIX_MAT_H
