#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> /* Inclusion du header de SDL_image (adapter le dossier au besoin) */

Uint8 median(Uint8 *tableau, int tailletableau);
void PutPixel_nolock(SDL_Surface * surface, int x, int y, Uint8 color, int b);
void pause();

int main(int argc, char *argv[])
{
    SDL_Surface *image = NULL;
    SDL_PixelFormat *fmt;
    //Uint32 temp, pixel;
    //Uint8 red, green, blue;
    int w,h;
    int x,y;

    image = IMG_Load("Medianfilterp.png");
    fmt=image->format;
    w = image->w;
    h = image->h;
    //printf("width : %d height : %d\n", w,h);
    int bit = 0;


    if(fmt->BitsPerPixel==8){
        fprintf(stderr, "8-bit surface.\n");

    }else if (fmt->BitsPerPixel==16){
        fprintf(stderr, "16-bit surface.\n");

    }else if (fmt->BitsPerPixel==24){
        fprintf(stderr, "24-bit surface.\n");

    }else if (fmt->BitsPerPixel==32){
        fprintf(stderr, "32-bit surface.\n");
    }

    /* Lock the surface */
    SDL_LockSurface(image);
    for (x = 1 ; x < w ; x++)
    {
        for (y = 1 ; y < h ; y++)
        {
            Uint8 tableau[9];
            int t = 0;
            int i;
            int j;

            for (i = x-1 ; i <= x+1 ; i++)
            {
                for (j = y-1; j <= y+1 ; j++)
                {
                    Uint8 * pixel = (Uint8*)image->pixels;
                    if(fmt->BitsPerPixel==8){
                        pixel += (j * image->pitch) + (i * sizeof(Uint8));
                        bit = 8;
                        }
                    else if (fmt->BitsPerPixel==16){
                        pixel += (j * image->pitch) + (i * sizeof(Uint16));
                        bit = 16;
                    }
                    else if (fmt->BitsPerPixel==24){
                        pixel += (j * image->pitch) + (i * sizeof(Uint8)*3);
                        bit = 24;
                    }
                    else if (fmt->BitsPerPixel==32){
                        pixel += (j * image->pitch) + (i * sizeof(Uint32));
                        bit = 32;
                    }
                    tableau[t] = *pixel;
                    t+=1;
                }
            }
            Uint8 new_pixel;
            new_pixel = median(tableau,9);
            PutPixel_nolock(image,x,y, new_pixel,bit);
            /*
            if (x==500 && y==500)
            {
                printf("median : %d\n", test);

                int a;
                for (a = 0 ; a < 9 ; a++)
                {
                    printf("%d\n", tableau[a]);
                }

            }*/
            }
    }

    //pixel = *((Uint32*)image->pixels);
    SDL_UnlockSurface(image);

    /* Get Red component */
    //temp = pixel & fmt->Rmask;  /* Isolate red component */
    //temp = temp >> fmt->Rshift; /* Shift it down to 8-bit */
    //temp = temp << fmt->Rloss;  /* Expand to a full 8-bit number */
    //red = (Uint8)temp;

    /* Get Green component */
    //temp = pixel & fmt->Gmask;  /* Isolate green component */
    //temp = temp >> fmt->Gshift; /* Shift it down to 8-bit */
    //temp = temp << fmt->Gloss;  /* Expand to a full 8-bit number */
    //green = (Uint8)temp;

    /* Get Blue component */
    //temp = pixel & fmt->Bmask;  /* Isolate blue component */
    //temp = temp >> fmt->Bshift; /* Shift it down to 8-bit */
    //temp = temp << fmt->Bloss;  /* Expand to a full 8-bit number */
    //blue = (Uint8)temp;

    //printf("Pixel Color -> R: %d,  G: %d,  B: %d\n", red, green, blue);
    //printf("pixel %d", pixel);

    SDL_Surface *ecran = NULL;
    SDL_Rect positionFond;

    positionFond.x = 0;
    positionFond.y = 0;

    SDL_Init(SDL_INIT_VIDEO);
    ecran = SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
    SDL_WM_SetCaption("Chargement d'images en SDL", NULL);

    SDL_BlitSurface(image, NULL, ecran, &positionFond);

    SDL_Flip(ecran);
    pause();

    SDL_FreeSurface(image);
    SDL_Quit();

    return EXIT_SUCCESS;
}

Uint8 median(Uint8 tableau[], int taille)
{
    Uint8 a[taille];
    int b;
    for(b = 0; b < taille ; b++)
    {
        a[b] = tableau[b];
    }
    int i,j;
    for (int i = 0; i < taille; i++)                     //Loop for ascending ordering
	{
		for (int j = 0; j < taille; j++)             //Loop for comparing other values
		{
			if (a[j] > a[i])                //Comparing other array elements
			{
				int tmp = a[i];         //Using temporary variable for storing last value
				a[i] = a[j];            //replacing value
				a[j] = tmp;             //storing last value
			}
		}
	}
	return a[4];
}

void PutPixel_nolock(SDL_Surface * surface, int x, int y, Uint8 color,int b)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    if(b==8){
        pixel += (x * surface->pitch) + (y * sizeof(Uint8));
        }
    else if (b==16){
        pixel += (x * surface->pitch) + (y * sizeof(Uint16));
        }
    else if (b==24){
        pixel += (y * surface->pitch) + (x * sizeof(Uint8)*3);
        *((Uint8*)pixel) = color;
    }
    else if (b==32){
        pixel += (x * surface->pitch) + (y * sizeof(Uint32));
    }
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
