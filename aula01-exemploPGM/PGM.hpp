#ifndef PGM_H_INCLUDED
#define PGM_H_INCLUDED
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct PGM
{
    string tipo;
    int larg;
    int alt;
    int vmax;
    unsigned char *pixels; // unsigned char -> 0 a 255
    PGM()                  // construtor -> inicializar variaveis
    {
        pixels = nullptr;
        larg = 0;
        alt = 0;
        vmax = 255;
        tipo = "";
    }
};

void destruir(PGM *pgm)
{
    if (pgm->pixels)
        delete pgm->pixels;
    pgm->pixels = nullptr;
    pgm->larg = 0;
    pgm->alt = 0;
    pgm->tipo = "";
    pgm->vmax = 255;
}

void imprimir(PGM *pgm)
{
    cout << "\nPGM\n";
    cout << "Tipo: " << pgm->tipo << endl;
    cout << "Dimensao: " << pgm->larg << "x" << pgm->alt << endl;
    cout << "vMax: " << pgm->vmax << endl;
    if (pgm->pixels) // verifica se o vetor de pixels está alocado
        cout << "Vetor de pixels: " << &(pgm->pixels) << endl;
    else
        cout << "Vetor de pixels: NULL\n";
}

//exerc 4
void criar(PGM *pgm, int largura, int altura, unsigned char corFundo)
{
    if (pgm->pixels)
        delete pgm->pixels;
    
    int tamanho = largura * altura;

    pgm->tipo = "P2";
    pgm->larg = largura;
    pgm->alt = altura;
    pgm->vmax = 255;
    pgm->pixels = new unsigned char[tamanho];

    for (int i = 0; i < tamanho; i++)
        pgm->pixels[i] = corFundo;
}

bool gravar(PGM *pgm, string caminho)
{
    if (!pgm->pixels)
        return false;

    ofstream arq;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    arq << pgm->tipo << endl;

    arq << pgm->larg << " " << pgm->alt << endl;

    arq << 255 << endl; // valor máximo de cor fixo em 255

    int tam = pgm->larg * pgm->alt;
    for (int i = 0; i < tam; i++)
    {
        arq << (int)pgm->pixels[i] << endl;
        arq.flush();
    }

    arq.close();
    return true;
}


string lerLinhaArquivo(std::ifstream &arq)
{
    string linha = "", dadoLido = "";
    while (!arq.eof())
    {
        linha = "";
        std::getline(arq, linha);
		
		// Remove \r do final da linha (caso exista)
        if (!linha.empty() && linha.back() == '\r')
            linha.pop_back();
		
        if (linha.size() > 0 && linha[0] != '#')
            return linha;
    }
    return linha;
}

bool ler(PGM *pgm, string caminho)
{
    ifstream arq;
    string dado;
    stringstream str;

    arq.open(caminho);
    if (!arq.is_open())
    {
        cout << "PGM: endereco do arquivo invalido\n";
        return false;
    }

    // ler o tipo
    dado = lerLinhaArquivo(arq);
    if (dado == "P2")
        pgm->tipo = dado;
    else
    {
        cout << "PGM: erro ao ler o tipo da imagem\n";
        return false;
    }

    // ler largura e altura
    dado = lerLinhaArquivo(arq);
    str = stringstream(dado);
    if (!(str >> pgm->larg))
    {
        cout << "PGM: erro ao ler a largura\n";
        return false;
    }
    if (!(str >> pgm->alt))
    {
        cout << "PGM: erro ao ler a largura\n";
        return false;
    }

    // ler vmax
    dado = lerLinhaArquivo(arq);
    str = stringstream(dado);
    if (!(str >> pgm->vmax))
    {
        cout << "PGM: erro ao ler vmax\n";
        return false;
    }

    if (pgm->pixels)
        delete pgm->pixels;

    int tam = pgm->larg * pgm->alt;

    pgm->pixels = new unsigned char[tam];

    int i = 0, p;
    while (!arq.eof())
    {

        if (arq >> p)
        {
            if (i < tam)
                pgm->pixels[i] = (unsigned char)p;
            i++;
        }
        else
            break;
    }

    if (i != tam)
    {
        cout << "PGM: erro ao ler os pixels\n";
        return false;
    }
    arq.close();
    return true;
}


unsigned char getPixel(PGM *pgm, int x, int y)
{
    if (!pgm->pixels)
        return 0;

    return pgm->pixels[y * pgm->larg + x];
}
void setPixel(PGM *pgm, int x, int y, unsigned char cor)
{
    if (!pgm->pixels)
        return;

    pgm->pixels[y * pgm->larg + x] = cor;
}

//exerc 5
void setLinha(PGM *pgm, int linha, unsigned char cor)
{
    if (!pgm->pixels)
        return;

    for (int i = 0; i < pgm->larg; i++)
        pgm->pixels[linha * pgm->larg + i] = cor;
        
}

//exerc 6: x = largura, y = altura
bool coordValida(PGM *pgm, int x, int y)
{
    if (x<0 || x>=pgm->larg || y<0 || y>=pgm->alt)
        return false;
    return true;
}

//exerc7: preencher uma regiao retangular com uma cor
//pgm (img 5 (eixo x->coluna) por 7(eixo y-> linha)) 1,2,5,6
void preencherRegiao (PGM *pgm, int x1, int y1, int x2, int y2, unsigned char cor){
    if (!coordValida(pgm,x1, y1) || !coordValida (pgm,x2,y2))
    {
        cout<<"\ncoord invalida\n";
        return;
    }
    else {
        for (int i = x1; i<x2; i++){
            for (int j = y1; j<y2; j++){
                setPixel(pgm, i, j, cor);
            }
        }
    }
}

//exerc 8: linha branca a cada 50 linhas
void setLinhas50(PGM *pgm){
    for ( int i = 0; i<pgm->alt; i++){
        if (i%50 == 0)
            setLinha(pgm, i, 255);
    }
}

//exerc 9: inverter vertical
void inverterVertical (PGM *pgm){
    for (int y = 0; y<pgm->alt/2; y++){ //percorre ate a metade, pra nao trocar duas vezes e voltar ao original
        for (int x = 0; x<pgm->larg; x++){ //percorre toda a largura, pra trocar na altura apenas ate a metade e na largura completamente
            unsigned char temp = getPixel(pgm, x, y); //guarda o pixel de cima
            setPixel(pgm, x, y, getPixel(pgm, x, pgm->alt-1-y)); //copia o pixrel de baixo pra cima
            setPixel(pgm, x, pgm->alt-1-y, temp); //coloca o puxel guardado (q era o de cima) embaixo
        }
    }
}

//exerc 10: copiar regiao p outra img
void copiarRegiao(PGM *entrada, PGM *saida, int x1, int y1, int x2, int y2) {
    
    criar(saida, entrada->larg, entrada->alt, 0);
    
    for (int y = y1; y < y2; y++) {
        for (int x = x1; x < x2; x++) {
            
            if (coordValida(entrada, x, y)) {
                unsigned char cor = getPixel(entrada, x, y);
                setPixel(saida, x, y, cor);
            }
        }
    }
}

//exerc 11: desenhar borda
void desenharBorda(PGM *pgm, unsigned char cor, int espessura) {
    
    // limita a espessura a 10
    if (espessura > 10) 
        espessura = 10;
    
    // percorre as primeiras/últimas linhas
    for (int e = 0; e < espessura; e++) {
        setLinha(pgm, e, cor);                    // topo
        setLinha(pgm, pgm->alt - 1 - e, cor);    // baixo
    }
    
    for (int y = 0; y < pgm->alt; y++) {
        for (int e = 0; e < espessura; e++) {
            setPixel(pgm, e, y, cor);                   // esquerda
            setPixel(pgm, pgm->larg - 1 - e, y, cor);  // direita
        }
    }
}

//exerc 12
void desenharX(PGM *pgm, unsigned char cor) {
    for (int y = 0; y < pgm->alt; y++) {
        // diagonal principal: x cresce junto com y
        int x1 = (y * (pgm->larg - 1)) / (pgm->alt - 1);
        // diagonal secundária: x decresce conforme y cresce
        int x2 = pgm->larg - 1 - x1;
        setPixel(pgm, x1, y, cor);
        setPixel(pgm, x2, y, cor);
    }
}

//exerc 13
void combinar(PGM *img1, PGM *img2, PGM *imgSaida, int opcao){
    if(!img1->pixels || !img2->pixels){
        cout<<"\nImagens invalidas\n";
        return;
    }
    if(img1->larg != img2->larg || img1->alt != img2->alt){
        cout<<"\nImagens com dimensoes diferentes\n";
        return;
    }
    
    criar(imgSaida, img1->larg, img1->alt, 0);
    
    for(int y = 0; y < img1->alt; y++){
        for(int x = 0; x < img1->larg; x++){
            unsigned char c1 = getPixel(img1, x, y);
            unsigned char c2 = getPixel(img2, x, y);
            unsigned char corFinal;
            
            if(opcao == 1)
                corFinal = (c1 + c2) / 2;
            else if(opcao == 2)
                corFinal = (c1 > c2) ? c1 : c2;
            else if(opcao == 3)
                corFinal = (c1 < c2) ? c1 : c2;
            else
                corFinal = 0;
            
            setPixel(imgSaida, x, y, corFinal);
        }
    }
}

//desenhar borda em regiao definida por dois pontos
void desenharBordaRegiao(PGM *pgm, int x1, int y1, int x2, int y2, unsigned char cor){
    if(!coordValida(pgm, x1, y1) || !coordValida(pgm, x2, y2)){
        cout<<"\nCoordenadas invalidas\n";
        return;
    }
    
    //garantir que x1,y1 seja o canto superior esquerdo
    if(x1 > x2){
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if(y1 > y2){
        int temp = y1;
        y1 = y2;
        y2 = temp;
    }
    
    //desenhar linhas horizontais (topo e baixo)
    for(int x = x1; x <= x2; x++){
        setPixel(pgm, x, y1, cor);
        setPixel(pgm, x, y2, cor);
    }
    
    //desenhar linhas verticais (esquerda e direita)
    for(int y = y1; y <= y2; y++){
        setPixel(pgm, x1, y, cor);
        setPixel(pgm, x2, y, cor);
    }
}

//converter tons de cinza para preto e branco
void converterPretoBranco(PGM *entrada, PGM *saida){
    if(!entrada->pixels){
        cout<<"\nImagem de entrada invalida\n";
        return;
    }
    
    criar(saida, entrada->larg, entrada->alt, 0);
    
    for(int y = 0; y < entrada->alt; y++){
        for(int x = 0; x < entrada->larg; x++){
            unsigned char cor = getPixel(entrada, x, y);
            if(cor > 128)
                setPixel(saida, x, y, 255);
            else
                setPixel(saida, x, y, 0);
        }
    }
}


#endif