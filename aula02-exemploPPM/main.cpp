#include <iostream>
#include "PPM.hpp"

using namespace std;



int main(void)
{

	//#Exemplo1#: criando uma imagem e gravando no disco
	PPM img1;
	criar(&img1, 5, 7);
	gravar(&img1, "exemplo1.ppm");
	destruir(&img1);

	//#Exemplo2#: imprimindo os atributos da imagem 
	PPM img2;
	cout << "#Exemplo 2#\n";
	imprimir(&img2);
	criar(&img2, 700, 500);
	imprimir(&img2);
	gravar(&img2, "exemplo2.ppm");
	destruir(&img2);
	imprimir(&img2);

	//#Exemplo3#: ler imagem, getPixel, setPixel 
	PPM img3;
	RGB corP;
	cout << "\n\n#Exemplo 3#\n";
	ler(&img3, "exemploPPM.ppm");

	//ler o valor do pixel de coordenadas (x=1, y=1)
	corP = getPixel(&img3, 0,0);
	cout << "A cor do pixel(0,0): [" << corP << "] " << endl;

	setPixel(&img3, 1, 0, RGB(0, 128, 128)); //alterar a cor do pixel(1, 0) para RGB(0, 128, 128)
	setPixel(&img3, 2, 0, RGB(255, 0, 255)); //alterar a cor do pixel(2, 0) para rosa
	setPixel(&img3, 2, 4, RGB(128, 0, 128)); //alterar a cor do pixel(2, 4) para roxo
	gravar(&img3, "exemplo3.ppm"); //gravar o resultado no disco
	destruir(&img3);

	
	cout << "Pressione uma tecla para encerrar o programa.\n";
	getchar();
	return EXIT_SUCCESS; 
}