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

void alterar_cor(int height, int width,Img *pic, double intensidade)
{
    pic->height = height;
    pic->width = width;
    pic->img->r = intensidade;
    pic->img->g = intensidade;
    pic->img->b = intensidade;
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

    int image[pic.width][pic.height];

    // armazena o cinza no pixel
   // EscreveCor(x,y,i,i,i) # x,y,r,g,b
    //tons de cinza
    int intensidade = 0;
    /*for (int i=0; i<5; i++){
        int intensidade = (int)(0.3 * pic.img[i].r + 0.59 * pic.img[i].g + 0.11 * pic.img[i].b);
        printf("%d \n",intensidade);
        //printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
        //alterar_cor(&pic.img[i],(0.3 * pic.img[i].r + 0.59 * pic.img[i].g + 0.11 * pic.img[i].b));
       // printf("[%02X %02X %02X] ", pic.img[i].r, pic.img[i].g, pic.img[i].b);
    }*/
    for (int i = 0; i < pic.height; i ++) {
        //grayImage[i] = (int) ((int)image->img[i].r*0.3 + (int)image->img[i].g*0.59 + (int)image->img[i].b*0.11);
        for (int j = 0; j < pic.width; j++) {
            intensidade = (int) ((float)pic.img[i*pic.width+j].r*0.3 + (float)pic.img[i*pic.width+j].g*0.59 + (float)pic.img[i*pic.width+j].b*0.11);
            printf(" %d ",intensidade);
            alterar_cor(i,j,&pic,(0.3 * pic.img[i].r + 0.59 * pic.img[i].g + 0.11 * pic.img[i].b));
            //continuar
        }

    }
    printf("a");
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

