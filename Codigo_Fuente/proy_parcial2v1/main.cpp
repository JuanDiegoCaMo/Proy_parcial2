#include <iostream>
#include <QImage>
#include "pix_mat.h"

using namespace std;

int main()
{
    cout << "Bienvenido a Informa2 S.A.S." << endl;
    cout << "Estimado usuario, se le informa de antemano que, con el fin de representar su imagen exitosamente en la matriz de neopixeles construida," << endl;
    cout << "debe hacer uso de este programa y otro localizado en el sitio web de Tinkercad. Dicho esto, procedo con las instrucciones." << endl;
    cout << "Primero, ingrese la direccion de la imagen de la bandera que desea representar:" << endl;
    cout << "  - Para conocer dicha direccion, ubiquese en el lugar del explorador de archivos de su ordenador donde se encuentra la imagen," << endl;
    cout << "  despues, haga clic derecho a la derecha de la ruta de la imagen en la barra de direcciones y escoja la opcion Copiar direccion como texto." << endl;
    cout << "  Finalmente, pegue la direccion aqui, cambie todos los backslash por slash y agregue el nombre de la imagen incluyendo su respectiva extension." << endl;
    cout << "  - Recuerde que el formato de la imagen debe ser en formato JPG." << endl;
    cout << "  Para ver el formato de su imagen, dirigase al explorador de archivos de su ordenador:" << endl;
    cout << "  Seccion Vista > Apartado Mostrar u Ocultar > Activar la casilla de Extensiones de nombre de archivo" << endl;
    cout << "  A continuacion, dirigase al lugar donde tiene guardada su imagen y fijese en el nombre de su imagen," << endl;
    cout << "  las letras que se encuentran despues del punto, ese es el formato de su imagen." << endl;
    cout << "  Ej: Si el nombre de la imagen es imagen_Colombia.png, la imagen esta en formato PNG." << endl;
    string filename;
    getline(cin,filename);
    QImage im(filename.c_str());
    pix_mat matriz_pixeles(im);
    return 0;
}
