#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> /* Inclusion du header de SDL_image (adapter le dossier au besoin) */

Uint8 median8(Uint8 *tableau, int tailletableau);
Uint8 median16(Uint16 *tableau, int tailletableau);
Uint8 median24(Uint32 *tableau, int tailletableau);
Uint8 median32(Uint32 *tableau, int tailletableau);

void PutPixel8_nolock(SDL_Surface * surface, int x, int y, Uint8 color);
void PutPixel16_nolock(SDL_Surface * surface, int x, int y, Uint16 color);
void PutPixel24_nolock(SDL_Surface * surface, int x, int y, Uint32 color);
void PutPixel32_nolock(SDL_Surface * surface, int x, int y, Uint32 color);

int main(int argc, char *argv[])
{
    SDL_Surface *original_image = NULL;
    SDL_Surface *new_image = NULL;
    SDL_PixelFormat *fmt;
    //Uint32 temp, pixel;
    //Uint8 red, green, blue;
    int w,h;
    int x,y;

    original_image = IMG_Load("Median_filter_example.jpg");
    new_image = IMG_Load("Median_filter_example.jpg");
    fmt=original_image->format;
    w = original_image->w;
    h = original_image->h;

    //printf("width : %d height : %d\n", w,h);
    int bit = 0;

    /*
    if(fmt->BitsPerPixel==8){
        fprintf(stderr, "8-bit surface.\n");

    }else if (fmt->BitsPerPixel==16){
        fprintf(stderr, "16-bit surface.\n");

    }else if (fmt->BitsPerPixel==24){
        fprintf(stderr, "24-bit surface.\n");

    }else if (fmt->BitsPerPixel==32){
        fprintf(stderr, "32-bit surface.\n");
    }*/

    /* Lock the surface */

    int fenetre = 0;
    printf("indiquez la taille de la fenêtre : ");
    scanf("%d", &fenetre);
    //printf("\nfenetre : %d\n",fenetre);
    int tailletableau = ((fenetre*2)+1)*((fenetre*2)+1);
    //printf("taille tableau : %d\n",tailletableau);

    SDL_LockSurface(original_image);
    SDL_LockSurface(new_image);
    if(fmt->BitsPerPixel==8){
        for (x = fenetre ; x <= w-fenetre ; x++)
        {
            for (y = fenetre ; y <= h-fenetre ; y++)
            {
                Uint8 tableau[tailletableau];

                int t = 0;
                int i;
                int j;

                for (i = x-fenetre ; i <= x+fenetre ; i++)
                {
                    for (j = y-fenetre; j <= y+fenetre ; j++)
                    {
                        Uint8 * pixel = (Uint8*)original_image->pixels;
                        pixel += (j * original_image->pitch) + (i * sizeof(Uint8));
                        tableau[t] = *pixel;
                        t+=1;
                    }
                }
                Uint8 new_pixel;
                new_pixel = median8(tableau,tailletableau);
                PutPixel8_nolock(new_image,x,y, new_pixel);
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
    }

    //pixel = *((Uint32*)image->pixels);
    SDL_UnlockSurface(original_image);
    SDL_UnlockSurface(new_image);

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

    /*

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

    */

    SDL_SaveBMP(new_image,"output.bmp");
    //IMG_SavePNG(image,"output.png"); je voulais utiliser cette ligne mais pour une raison qui m'échappe j'ai une erreur disant que la méthode n'est pas définie alors que'elle est bien présente dans le header de la librairie que j'importe

    SDL_FreeSurface(original_image);
    SDL_FreeSurface(new_image);
    SDL_Quit();

    return EXIT_SUCCESS;
}

Uint8 median8(Uint8 tableau[], int taille)
{
    Uint8 a[taille];
    int b;
    for(b = 0; b < taille ; b++)
    {
        a[b] = tableau[b];
    }
    //int i,j;
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
	//printf("taille/2 : %d\n",taille/2);
	return a[taille/2];
}

Uint8 median16(Uint16 tableau[], int taille)
{
    Uint16 a[taille];
    int b;
    for(b = 0; b < taille ; b++)
    {
        a[b] = tableau[b];
    }
    //int i,j;
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
	//printf("taille/2 : %d\n",taille/2);
	return a[taille/2];
}

Uint8 median24(Uint32 tableau[], int taille)
{
    Uint32 a[taille];
    int b;
    for(b = 0; b < taille ; b++)
    {
        a[b] = tableau[b];
    }
    //int i,j;
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
	//printf("taille/2 : %d\n",taille/2);
	return a[taille/2];
}

Uint8 median32(Uint32 tableau[], int taille)
{
    Uint32 a[taille];
    int b;
    for(b = 0; b < taille ; b++)
    {
        a[b] = tableau[b];
    }
    //int i,j;
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
	//printf("taille/2 : %d\n",taille/2);
	return a[taille/2];
}

void PutPixel8_nolock(SDL_Surface * surface, int x, int y, Uint8 color)
{
    Uint8 * pixel = (Uint8*)surface->pixels;
    pixel += (x * surface->pitch) + (y * sizeof(Uint8));
    *pixel = color;
}

void PutPixel16_nolock(SDL_Surface * surface, int x, int y, Uint16 color)
{
    Uint16 * pixel = (Uint16*)surface->pixels;
    pixel += (x * surface->pitch) + (y * sizeof(Uint16));
    *pixel = color;
}

void PutPixel24_nolock(SDL_Surface * surface, int x, int y, Uint32 color)
{
    Uint32 * pixel = (Uint32*)surface->pixels;
    pixel += (x * surface->pitch) + (y * sizeof(Uint8)*3);
    *pixel = color;
}

void PutPixel32_nolock(SDL_Surface * surface, int x, int y, Uint32 color)
{
    Uint32 * pixel = (Uint32*)surface->pixels;
    pixel += (x * surface->pitch) + (y * sizeof(Uint32));
    *pixel = color;
}
