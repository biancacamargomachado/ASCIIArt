#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// Para usar strings

// SOIL é a biblioteca para leitura das imagens
#include "SOIL.h"

// Um pixel RGB
typedef struct {
    unsigned char r, g, b;
} RGB;

// Uma imagem em RGB
typedef struct {
    int width, height;
    RGB* img;
} Img;

// Protótipos
int load(char* name, Img* pic);

// Carrega uma imagem para a struct Img
int load(char* name, Img* pic)
{
    int chan;
    pic->img = (unsigned char*) SOIL_load_image(name, &pic->width, &pic->height, &chan, SOIL_LOAD_RGB);
    if(!pic->img)
    {
        printf( "SOIL loading error: '%s'\n", SOIL_last_result() );
        exit(1);
    }
    printf("Load: %d x %d x %d\n", pic->width, pic->height, chan);
   return pic->height*pic->width;
}

int main(int argc, char** argv)
{
    Img pic;
    if(argc < 1) {
        printf("loader [img]\n");
        exit(1);
    }
    int size = load(argv[1], &pic);

    int y=pic.height;
    int x=pic.width;

    // Impressao do html

    FILE *picture; // Ponteiro que aponta para um arquivo
    picture = fopen("result.html", "w"); // w = write // cria um arq no dir do codigo
    printf("Toda a imagem! VAI DEMORAR :\n");
    fprintf(picture,"<html><head></head>");
    fprintf(picture,"<html><body>");
    fprintf(picture,"<style> pre {color: white;font-family: Courier;} body {background-color:black;}</style>");
    fprintf(picture, "<pre>");
    for (int i=0, j=0; i<size; i++,j++){
        if ((x-1)==j){
            fprintf(picture,"<br> \n");
            j=0;
        }
            fprintf(picture,"[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
    }
    fprintf(picture, "</pre>");
    fprintf(picture,"</body></html>");

    printf("size %d --tirar depois", size);
    printf("\n");

    free(pic.img);


}

