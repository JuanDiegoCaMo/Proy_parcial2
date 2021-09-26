#ifndef PIX_MAT_H
#define PIX_MAT_H

#include <vector>
#include <QImage>

using namespace std;

class pix_mat
{
public:
    pix_mat(QImage image_dir);
    void assignToPix(QImage image_dir);
    void remuestreo(QImage image_dir, int *auxX, int *auxY);
private:
    vector<short int> pixel;
    short int **mat;
    int *auxX, *auxY;
};

#endif // PIX_MAT_H
