#include "pix_mat.h"

#include <iostream>
pix_mat::pix_mat(QImage image_dir)
{
    auxX = new int;
    auxY = new int;
    for(int color = 0; color <= 2; color++){
        *auxX = image_dir.width();
        *auxY = image_dir.height();
        while(*auxX >= 16 && *auxY >= 16){
            for(int indx = 0; indx+1 < *auxX; indx=indx+2){
                for(int indy = 0; indy+1 < *auxY; indy=indy+2){
                    QColor tipo_color(image_dir.pixelColor(indx/2,indy/2).red(),image_dir.pixelColor(indx/2,indy/2).blue(),image_dir.pixelColor(indx/2,indy/2).green());
                    if(color == 0){
                        cout << indx << indy << " = " << image_dir.pixelColor(indx,indy).red() << " " << image_dir.pixelColor(indx+1,indy).red() << " " << image_dir.pixelColor(indx,indy+1).red() << " " << image_dir.pixelColor(indx+1,indy+1).red() << endl;
                        tipo_color.setRed((image_dir.pixelColor(indx,indy).red() + image_dir.pixelColor(indx+1,indy).red() + image_dir.pixelColor(indx,indy+1).red() + image_dir.pixelColor(indx+1,indy+1).red())/4);
                    }
                    else if(color == 1){
                        tipo_color.setBlue((image_dir.pixelColor(indx,indy).blue() + image_dir.pixelColor(indx+1,indy).blue() + image_dir.pixelColor(indx,indy+1).blue() + image_dir.pixelColor(indx+1,indy+1).blue())/4);
                    }
                    else if(color == 2){
                        tipo_color.setGreen((image_dir.pixelColor(indx,indy).green() + image_dir.pixelColor(indx+1,indy).green() + image_dir.pixelColor(indx,indy+1).green() + image_dir.pixelColor(indx+1,indy+1).green())/4);
                    }
                    image_dir.setPixelColor(indx/2,indy/2,tipo_color);
                    cout << image_dir.pixelColor(indx/2,indy/2).red() << endl;
                }
            }
            *auxX = *auxX/2;
            *auxY = *auxY/2;
        }
    }
    for(int x = 0; x < *auxX; x++){
        for(int y = 0; y < *auxY; y++){
            cout << image_dir.pixelColor(x,y).red() << "\t";
            //cout << image_dir.pixelColor(x,y).blue() << "\t";
            //cout << image_dir.pixelColor(x,y).green() << "\t";
        }
        cout << endl;
    }
}
