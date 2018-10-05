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

void alterar_cor(Img *pic, unsigned int intensidade)
{
    pic->img->r = intensidade;
    pic->img->g = intensidade;
    pic->img->b = intensidade;
}

char getAsc(unsigned char color)
{
    float value = 0;

    if((int)color!=0)
        value = (float) ((float)color / 255);

    if(value==0)
        return '#'; //mais intenso
    else{
        if(value<=0.1) //outros menos intenso que podem dar float
            return '@';
        else if(value<=0.2)
            return '0';
        else if(value<=0.4)
            return 'O';
        else if(value<=0.5)
            return 'C';
        else if(value<=0.5647)
            return 'M';
        else if(value<=0.6)
            return 'o';
        else if(value<=0.6556)
            return 'B';
        else if(value<=0.7)
            return 'c';
        else if(value<=0.72)
            return 'Z';
        else if(value<=0.7725)
            return '|';
        else if(value<=0.8)
            return ':';
        else if(value<=0.8549)
            return '*';
        else if(value<=0.9)
            return '.';
        else if(value<=1)
            return ' ';
    }
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

    //tons de cinza
    unsigned int intensidade = 0;
    for (int i = 0; i < size; i ++) {
            intensidade = (unsigned int)(pic.img[i].r*0.3 + pic.img[i].g*0.59 + pic.img[i].b*0.11);
            printf(" %d ",intensidade);
            alterar_cor(&pic,intensidade);
    }

    // Impressao do html
    FILE *picture; // Ponteiro que aponta para um arquivo
    picture = fopen("result.html", "w"); // w = write // cria um arq no dir do codigo
    printf("Toda a imagem! VAI DEMORAR :\n");
    fprintf(picture,"<html><head></head>");
    fprintf(picture,"<html><body>");
    fprintf(picture,"<style> pre {color: white;font-family: Courier;} body {background-color:black;}</style>");
    fprintf(picture, "<pre>");
    for (int i=0, j=0; i<size; i++,j++){
        if ((x)==j){//controlar a largura
            fprintf(picture,"<br>");
            j=0;
        }
            fprintf(picture,"%c%c%c",getAsc(pic.img[i].r),getAsc(pic.img[i].r),getAsc(pic.img[i].r));
    }
    fprintf(picture, "</pre>");
    fprintf(picture,"</body></html>");

    printf("size %d --tirar depois", size);
    printf("\n");

    free(pic.img);


}

/*
void resize (){
    Img pic;
	int new_width = 1;
	int new_height = 1;

		if( (new_width != pic.width) || (new_height != pic.height) ){
			unsigned char *resampled = (unsigned char*)malloc( channels*new_width*new_height );

			up_scale_image(
					pic, pic.width, pic.height, channels,
					resampled, new_width, new_height );

			SOIL_save_image( pic, SOIL_SAVE_TYPE_BMP,
							new_width, new_height, channels,
							resampled );

			SOIL_free_image_data( pic );
			pic = resampled;
			width = new_width;
			height = new_height;

		}
	}
**/

