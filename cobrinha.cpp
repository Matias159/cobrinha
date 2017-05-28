#include <stdio.h>
#include <iostream>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

using namespace std;

const float FPS = 60;
const int SCREEN_W = 700;
const int SCREEN_H = 500;

ALLEGRO_BITMAP *fundo;
bool comAudio = true;

bool teclas[4] = { false, false, false, false };

enum TECLAS {
   KEY_UP, KEY_DOWN, KEY_W, KEY_S
};

class Segmento{
protected:
    ALLEGRO_BITMAP *bmp;
	int x;
	int y;
public:
	Segmento(int cabeca_x, int cabeca_y)
	{
        cout << "segmento criado" << endl;
		x = cabeca_x;
		y = cabeca_y;
	}
    int setCoordenadaX(int _x)
	{
		x = _x;
	}
	int setCoordenadaY(int _y)
	{
        y = _y;
	}
    int getCoordenadaX()
	{
		return x;
	}
	int getCoordenadaY()
	{
		return y;
	}
	void imprimeCabecaParaCima()
	{
        bmp = al_load_bitmap("cabeca_para_cima.png");
        if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
		al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
	}
    void imprimeCabecaParaBaixo()
	{
        bmp = al_load_bitmap("cabeca_para_baixo.png");
        if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
		al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
	}
    void imprimeCabecaParaEsquerda()
	{
        bmp = al_load_bitmap("cabeca_para_esquerda.png");
        if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
		al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
	}
    void imprimeCabecaParaDireita()
	{
        bmp = al_load_bitmap("cabeca_para_direita.png");
        if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
		al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
	}
    void imprimeCorpoReto()
	{
		bmp = al_load_bitmap("corpo_reto.png");
		if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
		al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
  	}
    void imprimeCorpoDeLado()
	{
		bmp = al_load_bitmap("corpo_de_lado.png");
		if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
		al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
  	}
  	void imprimeRabinhoParaBaixo()
  	{
        bmp = al_load_bitmap("rabinho_para_baixo.png");
		if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
		al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
  	}
    void imprimeRabinhoParaCima()
  	{
        bmp = al_load_bitmap("rabinho_para_cima.png");
		if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
		al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
  	}
    void imprimeRabinhoParaEsquerda()
  	{
        bmp = al_load_bitmap("rabinho_para_esquerda.png");
		if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
		al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
  	}
    void imprimeRabinhoParaDireita()
  	{
        bmp = al_load_bitmap("rabinho_para_direita.png");
		if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
		al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
  	}

    ~Segmento()
    {
        cout << "segmento destruido" << endl;
        al_destroy_bitmap(bmp);
    }
};

class Cobrinha {
	int tamanho;
	static const int tamanho_maximo = 30;
	Segmento **segmentos;
public:
	Cobrinha()
	{
	    int x = (1 + ((rand() % 700)));
	    int y = (1 + ((rand() % 500)));
		tamanho = 8;
		segmentos = new Segmento*[tamanho_maximo];
		for(int i = 0; i < tamanho; i++)
        {
            segmentos[i] = new Segmento(x, y);
            x += 60;
        }
        cout << "cobrinha criada" << endl;
	}
	void mover()
	{
        for(int i = 1; i < tamanho; i++)
        {
            if(tamanho-i == 0)
            {
                break;
            }
            else
            {
                segmentos[tamanho-i]->setCoordenadaX(segmentos[tamanho-1-i]->getCoordenadaX());
            }
        }
        (segmentos[0]->setCoordenadaX(segmentos[0]->getCoordenadaX() - 60));
        imprimeCobrinha();
        al_flip_display();
	}
  	void imprimeCobrinha()
  	{
  	    segmentos[0]->imprimeCabecaParaEsquerda();
  	    al_flip_display();
        for(int i = 1; i < (tamanho-1); i++)
        {
            segmentos[i]->imprimeCorpoDeLado();
            al_flip_display();
        }
        segmentos[tamanho-1]->imprimeRabinhoParaDireita();
        al_flip_display();
  	}
	~Cobrinha()
	{
        for(int i = 0; i < tamanho; i++)
        {
            delete segmentos[i];
        }
        delete[] segmentos;
        cout << "cobrinha destruida" << endl;
	}
};

class criaBitmap
{
public:
	criaBitmap(){}
	int imagemDeFundo()
	{
		fundo = al_load_bitmap("fundo.jpg");
		if(!fundo)
		{
			printf("failed to create bitmap!\n");
			return -1;
		}
		al_draw_bitmap(fundo, 0, 0, 0);
		al_flip_display();
  	}
};

int main()
{
    srand((unsigned)time(NULL));

    //Reponsável pela impressão na tela
    ALLEGRO_DISPLAY *display = NULL;
    //Fila de eventos
    //ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    //Eventos de tempo (ocorrem a cada X tempo)
    //ALLEGRO_TIMER *timer = NULL;

    //timer = al_create_timer(1.0 / FPS);
    //if(!timer)
    //{
        //cout << "failed to create timer!\n";
        //return -1;
    //}

	criaBitmap bitmap;
    Cobrinha cobrinha;

    //Iniciamos o Allegro
    if(!al_init()) {
        cout << "failed to initialize allegro!\n";
        return -1;
    }

    // Inicializa o add-on para utilização de imagens
    al_init_image_addon();


    display = al_create_display(SCREEN_W, SCREEN_H);
    if(!display) {
        cout << "failed to create display!\n";
        return -1;
    }

    if(bitmap.imagemDeFundo() == -1)
      return -1;

    cobrinha.imprimeCobrinha();

    al_set_target_bitmap(al_get_backbuffer(display));

    //cobrinha.imprimeCobrinha();
    //cobrinha.imprimeCobrinha();

    while(1)
    {
        cobrinha.mover();
    }

    al_rest(10.0);

	al_destroy_display(display);

	return 0;
}
