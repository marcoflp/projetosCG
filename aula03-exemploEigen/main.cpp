#include <iostream>
#include <cmath>
#include "PGM.hpp"

using namespace std;


#include <Eigen/Dense>
using namespace Eigen;

#define _PI	3.14159265358979323846

float degree2rad(float ang) {
	float r = ang * (float)(_PI / 180.0);

	return r;
}

Matrix3f getTranslacao(float tx, float ty)
{
	Matrix3f T = Matrix3f::Identity();
	T(0,2) = tx;
	T(1,2) = ty;
	return T;
}

Matrix3f getRotacao(float ang)
{
	float rad = degree2rad (ang);
	float s = sin(rad);
	float c = cos(rad);
	Matrix3f T = Matrix3f::Identity();
	T(0,0) = c;
	T(0,1) = -s;
	T(1,0) = s;
	T(1,1) = c;
	return T;
}

void exercLista3F(){
	Vector2f pontoCentro (6.0f,4.0f);
	Matrix3f T = getTranslacao(pontoCentro.x(), pontoCentro.y());
	Matrix3f Tinv = getTranslacao(-pontoCentro.x(), -pontoCentro.y());
	Matrix3f R = getRotacao(-30.0f);
	Matrix3f M = T * R * Tinv;
	cout<< endl << M <<endl;
	vector<Vector3f> pontos;
	pontos.push_back(Vector3f(4.0f, 2.0f, 1.0f));
	pontos.push_back(Vector3f(8.0f, 2.0f, 1.0f));
	pontos.push_back(Vector3f(6.0f, 7.0f, 1.0f));

	for (int i = 0; i < pontos.size(); i++)
	{
		Vector3f p  = M * pontos[i];
		cout << "Ponto " << i+1 << ": " << p.transpose() << endl;
	}
}

//ler img de entrada e criar img de saida antesde chamar a funcao
void transf2D(PGM* imgE, PGM* imgS, Matrix3f M)
{
	if (imgE->larg!=imgS->larg || imgE->alt!=imgS->alt)
		return;
	
	for (size_t yE = 0; yE < imgE->alt; yE++)
	{
		for (size_t xE = 0; xE < imgE->alt; xE++)
		{
			Vector3f coordSaida = M * Vector3f(xE, yE, 1);
			float xSaida = round(coordSaida.x());
			float ySaida = round(coordSaida.y());
			if (coordValida(imgS, xSaida, ySaida))
			{
				setPixel (imgS, xSaida, ySaida, getPixel(imgE, xE, yE));
			}
		}
	}
	
	
}

void transf2DInv(PGM* imgE, PGM* imgS, Matrix3f Minv)
{
	if (imgE->larg!=imgS->larg || imgE->alt!=imgS->alt)
		return;
	
	for (size_t yS = 0; yS < imgE->alt; yS++)
	{
		for (size_t xS = 0; xS < imgE->alt; xS++)
		{
			Vector3f coordEntrada = Minv * Vector3f(xS, yS, 1);
			float xE = round(coordEntrada.x());
			float yE = round(coordEntrada.y());
			if (coordValida(imgE, xE, yE))
			{
				setPixel (imgS, xS, yS, getPixel(imgE, xE, yE));
			}
		}
	}
	
	
}

int main(void)
{
	setlocale(LC_ALL, "Portuguese");

	exercLista3F();

	PGM imgE, imgS;
	ler(&imgE, "numeros.pgm");
	criar(&imgS, imgE.larg, imgE.alt, 0);

	Vector2f pontoCentro((imgE.larg-1)/2.0, (imgE.alt-1)/2.0);
	Matrix3f T = getTranslacao(pontoCentro.x(), pontoCentro.y());
	Matrix3f Tinv = getTranslacao(-pontoCentro.x(), -pontoCentro.y());
	Matrix3f R = getRotacao(45.0f);

	Matrix3f M = T * R * Tinv;

	Matrix3f Minv = M.inverse();
	transf2DInv(&imgE, &imgS, Minv);
	gravar(&imgS, "numeros_rotacaoinv.pgm");
	transf2D (&imgE, &imgS, M);
	gravar(&imgS, "numeros_rotacao45.pgm");
	cout << "Pressione uma tecla para encerrar o programa.\n";
	getchar();
	return EXIT_SUCCESS; 
}