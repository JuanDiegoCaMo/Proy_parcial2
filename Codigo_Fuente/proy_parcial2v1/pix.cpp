#include "pix.h"
pix::pix(QImage image_dir, int posX, int posY)
{
    im = image_dir;
    float pixperCol = im.width()/float(neopix_cant);
    float pixperFil = im.height()/float(neopix_cant);
    for(int indx = posX*pixperCol; indx < (posX*pixperCol)+1; indx++){
        for(int indy = posY*pixperFil; indy < (posY*pixperFil)+1; indy++){

        }
    }
}
