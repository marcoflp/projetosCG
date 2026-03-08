#include <iostream>
#include "PGM.hpp"

using namespace std;



int main(void)
{

	//#Exemplo1#: criando uma imagem e gravando no disco
	PGM img1;
	criar(&img1, 5, 7, 0);
	cout<<coordValida(&img1, 3, 3)<<endl; 
	cout<<coordValida(&img1, 5, 7)<<endl; 
	cout<<coordValida(&img1, -1, -1)<<endl;
	setLinha(&img1, 3, 255); //alterar a linha 3 para branco
	gravar(&img1, "exemplo1.pgm");
	destruir(&img1);

	//#Exemplo2#: imprimindo os atributos da imagem 
	PGM img2;
	cout << "#Exemplo 2#\n";
	imprimir(&img2);
	criar(&img2, 700, 500, 128);
	imprimir(&img2);
	gravar(&img2, "exemplo2.pgm");
	destruir(&img2);
	imprimir(&img2);

	//#Exemplo3#: ler imagem, getPixel, setPixel 
	PGM img3;
	unsigned char corP;
	cout << "\n\n#Exemplo 3#\n";
	ler(&img3, "feep.pgm");

	//ler o valor do pixel de coordenadas (x=1, y=1)
	corP = getPixel(&img3, 1,1);
	cout << "A cor do pixel(1,1): " << (int) corP << endl;

	setPixel(&img3, 1, 1, 255); //alterar a cor do pixel(1,1) para branco(255)
	gravar(&img3, "exemplo3.pgm"); //gravar o resultado no disco
	destruir(&img3);

	//#Exemplo4#: preencher regiao
	cout << "\n\n#Exemplo 4#\n";
	cout << "Gerando img 4" << endl;
	PGM img4;
	criar(&img4, 5, 7, 0);
	preencherRegiao(&img4, 1, 1, 4, 5, 255); //do pixel(1,1) ate pixel(3,4) -> preencher com branco(255)
	gravar(&img4, "exemplo4.pgm");
	destruir(&img4);

	cout << "\n\n#Exemplo 5#\n";
	cout << "Gerando img 5" << endl;
	PGM img5;
	criar(&img5, 500, 500, 0);
	setLinhas50(&img5);
	gravar(&img5, "exemplo5.pgm");
	destruir(&img5);

	cout<<"\n\n#Exemplo 6#\n";
	cout<<"Gerando img 6"<<endl;
	PGM img6;
	ler(&img6, "feep.pgm");
	imprimir(&img6);
	inverterVertical(&img6);
	gravar(&img6, "exemplo6.pgm");
	destruir(&img6);

	cout<<"\n\n#Exemplo 7#\n";
	cout<<"DESENHAR BORDA"<<endl;
	PGM entrada;
	ler(&entrada, "numeros.pgm");
	desenharBorda(&entrada, 0, 5);
	gravar(&entrada, "numerosborda.pgm");
	PGM saida;
	cout<<"COPIAR REGIAO"<<endl;
	copiarRegiao(&entrada, &saida, 120, 0, 225, 160); //x =
	gravar(&saida, "exemplo7.pgm");
	destruir(&entrada);
	destruir(&saida);

	cout<<"\n\n#Exemplo 8#\n";
	cout<<"DESENHAR X"<<endl;
	PGM img8;
	ler(&img8, "numeros.pgm");
	desenharX(&img8, 0);
	gravar(&img8, "numerosx.pgm");
	destruir(&img8);

	
	cout << "Pressione uma tecla para encerrar o programa.\n";
	getchar();
	return EXIT_SUCCESS; 
}