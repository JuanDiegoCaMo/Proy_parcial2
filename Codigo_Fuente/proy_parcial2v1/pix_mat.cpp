#include "pix_mat.h"

#include <iostream>
pix_mat::pix_mat(QImage image_dir)
{
    auxX = new int;
    auxY = new int;
    for(int color = 0; color <= 2; color++){
        *auxX = image_dir.width();
        *auxY = image_dir.height();
        while(*auxX >= 32 && *auxY >= 32){
            for(int indy = 0; indy+1 < *auxY; indy=indy+2){
                for(int indx = 0; indx+1 < *auxX; indx=indx+2){
                    QColor tipo_color(image_dir.pixelColor(indx/2,indy/2).red(),image_dir.pixelColor(indx/2,indy/2).green(),image_dir.pixelColor(indx/2,indy/2).blue());
                    if(color == 0){
                        tipo_color.setRed((image_dir.pixelColor(indx,indy).red() + image_dir.pixelColor(indx+1,indy).red() + image_dir.pixelColor(indx,indy+1).red() + image_dir.pixelColor(indx+1,indy+1).red())/4);
                    }
                    else if(color == 1){
                        tipo_color.setGreen((image_dir.pixelColor(indx,indy).green() + image_dir.pixelColor(indx+1,indy).blue() + image_dir.pixelColor(indx,indy+1).green() + image_dir.pixelColor(indx+1,indy+1).green())/4);
                    }
                    else if(color == 2){
                        tipo_color.setBlue((image_dir.pixelColor(indx,indy).blue() + image_dir.pixelColor(indx+1,indy).blue() + image_dir.pixelColor(indx,indy+1).blue() + image_dir.pixelColor(indx+1,indy+1).blue())/4);
                    }
                    image_dir.setPixelColor(indx/2,indy/2,tipo_color);
                }
            }
            *auxX = *auxX/2;
            *auxY = *auxY/2;
        }
    }
    if(*auxX == 8 && *auxY == 8) assignToPix(image_dir);
    else if(*auxX > 8 && *auxY > 8){
        submuestreo(image_dir, auxX, auxY);
    }
    else if(*auxX < 8 && *auxY < 8){
        sobremuestreo(image_dir, auxX, auxY);
    }
}

void pix_mat::assignToPix(QImage image_dir)
{
    for(int y = 0; y < *auxY; y++){
        for(int x = 0; x < *auxX; x++){
            pixel.push_back(short(image_dir.pixelColor(x,y).red()));
            pixel.push_back(short(image_dir.pixelColor(x,y).green()));
            pixel.push_back(short(image_dir.pixelColor(x,y).blue()));
        }
    }
}

void pix_mat::submuestreo(QImage image_dir, int *auxX, int *auxY)
{
    float distOriginX = 1 /(float(*auxX) - float(2)), dist = 1 /(float(8)), distOriginY = 1/(float(*auxY) - float(2));
    for(int y = 0; y < 8; y++){
        int iy = 0;
        for(;;iy++){
            if(iy*distOriginY > y*dist+dist/2) break;
        }
        int iy_min = iy;
        for(;iy_min >= 0; iy_min--){
            if(iy_min*distOriginY <= y*dist+dist/2) break;
        }
        for(int x = 0; x < 8; x++){
            int ix = 0;
            for(;;ix++){
                if(ix*distOriginX > x*dist+dist/2) break;
            }
            int ix_min = ix;
            for(;ix_min >= 0;ix_min--){
                if(ix_min*distOriginX <= x * dist+dist/2) break;
            }
            pixel.push_back(short((1/((ix*distOriginX-ix_min*distOriginX)*(iy*distOriginY-iy_min*distOriginY)))*((image_dir.pixelColor(ix_min,iy_min).red()*(ix*distOriginX-(x*dist+dist/2))*(iy*distOriginY-(y*dist+dist/2)))+(image_dir.pixelColor(ix,iy_min).red()*((x*dist+dist/2)-ix_min*distOriginX)*(iy*distOriginY-(y*dist+dist/2)))+(image_dir.pixelColor(ix_min,iy).red()*(ix*distOriginX-(x*dist+dist/2))*((y*dist+dist/2)-iy_min*distOriginY))+(image_dir.pixelColor(ix,iy).red()*((x*dist+dist/2)-ix_min*distOriginX)*((y*dist+dist/2)-iy_min*distOriginY)))));
            pixel.push_back(short((1/((ix*distOriginX-ix_min*distOriginX)*(iy*distOriginY-iy_min*distOriginY)))*((image_dir.pixelColor(ix_min,iy_min).green()*(ix*distOriginX-(x*dist+dist/2))*(iy*distOriginY-(y*dist+dist/2)))+(image_dir.pixelColor(ix,iy_min).green()*((x*dist+dist/2)-ix_min*distOriginX)*(iy*distOriginY-(y*dist+dist/2)))+(image_dir.pixelColor(ix_min,iy).green()*(ix*distOriginX-(x*dist+dist/2))*((y*dist+dist/2)-iy_min*distOriginY))+(image_dir.pixelColor(ix,iy).green()*((x*dist+dist/2)-ix_min*distOriginX)*((y*dist+dist/2)-iy_min*distOriginY)))));
            pixel.push_back(short((1/((ix*distOriginX-ix_min*distOriginX)*(iy*distOriginY-iy_min*distOriginY)))*((image_dir.pixelColor(ix_min,iy_min).blue()*(ix*distOriginX-(x*dist+dist/2))*(iy*distOriginY-(y*dist+dist/2)))+(image_dir.pixelColor(ix,iy_min).blue()*((x*dist+dist/2)-ix_min*distOriginX)*(iy*distOriginY-(y*dist+dist/2)))+(image_dir.pixelColor(ix_min,iy).blue()*(ix*distOriginX-(x*dist+dist/2))*((y*dist+dist/2)-iy_min*distOriginY))+(image_dir.pixelColor(ix,iy).blue()*((x*dist+dist/2)-ix_min*distOriginX)*((y*dist+dist/2)-iy_min*distOriginY)))));
            cout << short((1/((ix*distOriginX-ix_min*distOriginX)*(iy*distOriginY-iy_min*distOriginY)))*((image_dir.pixelColor(ix_min,iy_min).red()*(ix*distOriginX-(x*dist+dist/2))*(iy*distOriginY-(y*dist+dist/2)))+(image_dir.pixelColor(ix,iy_min).red()*((x*dist+dist/2)-ix_min*distOriginX)*(iy*distOriginY-(y*dist+dist/2)))+(image_dir.pixelColor(ix_min,iy).red()*(ix*distOriginX-(x*dist+dist/2))*((y*dist+dist/2)-iy_min*distOriginY))+(image_dir.pixelColor(ix,iy).red()*((x*dist+dist/2)-ix_min*distOriginX)*((y*dist+dist/2)-iy_min*distOriginY)))) << "\t";
        }
        cout << endl;
    }
}

void pix_mat::sobremuestreo(QImage image_dir, int *auxX, int *auxY)
{
    /*float distOriginX = 1 /(float(*auxX)), dist = 1 /(float(8)), distOriginY = 1/(float(*auxY));
    for(int y = 0; y < 8; y++){
        int iy = 0;
        for(;;iy++){
            if(iy+1 > *auxY) break;
            else if(iy*distOriginY+distOriginY/2 > y*dist) break;
        }
        int iy_min = iy;
        while(iy_min >= 0){
            if(iy_min - 1 < 0) break;
            else if(iy_min*distOriginY+distOriginY/2 <= y*dist) break;
            else iy_min--;
        }
        for(int x = 0; x < 8; x++){
            int ix = 0;
            for(;;ix++){
                if(ix+1 > *auxX) break;
                else if(ix*distOriginX+distOriginX/2 > x*dist) break;
            }
            int ix_min = ix;
            while(ix_min >= 0){
                if(ix_min - 1 < 0) break;
                else if(ix_min*distOriginX+distOriginX/2 <= x*dist) break;
                else ix_min--;
            }
            if(ix == ix_min && iy == iy_min){
                pixel.push_back(short(image_dir.pixelColor(ix,iy).red()));
                cout << pixel.back() << "\t";
                pixel.push_back(short(image_dir.pixelColor(ix,iy).green()));
                pixel.push_back(short(image_dir.pixelColor(ix,iy).blue()));
            }
            else if(iy == iy_min && ix != ix_min){
                pixel.push_back(short((image_dir.pixelColor(ix_min,iy).red()*((ix*distOriginX+distOriginX/2)-x*dist)/((ix*distOriginX+distOriginX/2)-(ix_min*distOriginX+distOriginX/2)))+(image_dir.pixelColor(ix,iy).red()*(x*dist-(ix*distOriginX+distOriginX/2))/((ix*distOriginX+distOriginX/2)-(ix_min*distOriginX+distOriginX/2)))));
                cout << pixel.back() << "\t";
                pixel.push_back(short((image_dir.pixelColor(ix_min,iy).green()*((ix*distOriginX+distOriginX/2)-x*dist)/((ix*distOriginX+distOriginX/2)-(ix_min*distOriginX+distOriginX/2)))+(image_dir.pixelColor(ix,iy).green()*(x*dist-(ix*distOriginX+distOriginX/2))/((ix*distOriginX+distOriginX/2)-(ix_min*distOriginX+distOriginX/2)))));
                pixel.push_back(short((image_dir.pixelColor(ix_min,iy).blue()*((ix*distOriginX+distOriginX/2)-x*dist)/((ix*distOriginX+distOriginX/2)-(ix_min*distOriginX+distOriginX/2)))+(image_dir.pixelColor(ix,iy).blue()*(x*dist-(ix*distOriginX+distOriginX/2))/((ix*distOriginX+distOriginX/2)-(ix_min*distOriginX+distOriginX/2)))));
            }
            else if(ix == ix_min && iy != iy_min){
                pixel.push_back(short((image_dir.pixelColor(ix,iy_min).red()*((iy*distOriginY+distOriginY/2)-y*dist)/((iy*distOriginY+distOriginY/2)-(iy_min*distOriginY+distOriginY/2)))+(image_dir.pixelColor(ix,iy).red()*(y*dist-(iy*distOriginY+distOriginY/2))/((iy*distOriginY+distOriginY/2)-(iy_min*distOriginY+distOriginY/2)))));
                cout << pixel.back() << "\t";;
                pixel.push_back(short((image_dir.pixelColor(ix,iy_min).green()*((iy*distOriginY+distOriginY/2)-y*dist)/((iy*distOriginY+distOriginY/2)-(iy_min*distOriginY+distOriginY/2)))+(image_dir.pixelColor(ix,iy).green()*(y*dist-(iy*distOriginY+distOriginY/2))/((iy*distOriginY+distOriginY/2)-(iy_min*distOriginY+distOriginY/2)))));
                pixel.push_back(short((image_dir.pixelColor(ix,iy_min).blue()*((iy*distOriginY+distOriginY/2)-y*dist)/((iy*distOriginY+distOriginY/2)-(iy_min*distOriginY+distOriginY/2)))+(image_dir.pixelColor(ix,iy).blue()*(y*dist-(iy*distOriginY+distOriginY/2))/((iy*distOriginY+distOriginY/2)-(iy_min*distOriginY+distOriginY/2)))));
            }
            else{
            pixel.push_back(short((1/(((ix*distOriginX+distOriginX/2)-(ix_min*distOriginX+distOriginX/2))*((iy*distOriginY+distOriginY/2)-(iy_min*distOriginY+distOriginY/2))))*((image_dir.pixelColor(ix_min,iy_min).red()*((ix*distOriginX+distOriginX/2)-x*dist)*((iy*distOriginY+distOriginY/2)-y*dist))+(image_dir.pixelColor(ix,iy_min).red()*(x*dist-(ix_min*distOriginX+distOriginX/2))*((iy*distOriginY+distOriginY/2)-y*dist))+(image_dir.pixelColor(ix_min,iy).red()*((ix*distOriginX+distOriginX/2)-x*dist)*(y*dist-(iy_min*distOriginY+distOriginY/2)))+(image_dir.pixelColor(ix,iy).red()*(x*dist-(ix_min*distOriginX+distOriginX/2))*(y*dist-(iy_min*distOriginY+distOriginY/2))))));
            cout << pixel.back() << "\t";
            pixel.push_back(short((1/(((ix*distOriginX+distOriginX/2)-(ix_min*distOriginX+distOriginX/2))*((iy*distOriginY+distOriginY/2)-(iy_min*distOriginY+distOriginY/2))))*((image_dir.pixelColor(ix_min,iy_min).green()*((ix*distOriginX+distOriginX/2)-x*dist)*((iy*distOriginY+distOriginY/2)-y*dist))+(image_dir.pixelColor(ix,iy_min).green()*(x*dist-(ix_min*distOriginX+distOriginX/2))*((iy*distOriginY+distOriginY/2)-y*dist))+(image_dir.pixelColor(ix_min,iy).green()*((ix*distOriginX+distOriginX/2)-x*dist)*(y*dist-(iy_min*distOriginY+distOriginY/2)))+(image_dir.pixelColor(ix,iy).green()*(x*dist-(ix_min*distOriginX+distOriginX/2))*(y*dist-(iy_min*distOriginY+distOriginY/2))))));
            pixel.push_back(short((1/(((ix*distOriginX+distOriginX/2)-(ix_min*distOriginX+distOriginX/2))*((iy*distOriginY+distOriginY/2)-(iy_min*distOriginY+distOriginY/2))))*((image_dir.pixelColor(ix_min,iy_min).blue()*((ix*distOriginX+distOriginX/2)-x*dist)*((iy*distOriginY+distOriginY/2)-y*dist))+(image_dir.pixelColor(ix,iy_min).blue()*(x*dist-(ix_min*distOriginX+distOriginX/2))*((iy*distOriginY+distOriginY/2)-y*dist))+(image_dir.pixelColor(ix_min,iy).blue()*((ix*distOriginX+distOriginX/2)-x*dist)*(y*dist-(iy_min*distOriginY+distOriginY/2)))+(image_dir.pixelColor(ix,iy).blue()*(x*dist-(ix_min*distOriginX+distOriginX/2))*(y*dist-(iy_min*distOriginY+distOriginY/2))))));
            }
        }
        cout << endl;
    }
*/
    int total = *auxX * *auxY;
    int ix = 0, iy = 0;
    for(int y = 0; y < *auxY; y++){
        for(int x = 0; x < *auxX; x++){

        }
    }
}
