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
ALLEGRO_BITMAP *bmp;
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
	Segmento()
	{
        cout << "construiu segmentos" << endl;
		x = 200;
		y = 300;
        bmp = al_load_bitmap("fundo.jpg");
	    if(!bmp)
		{
			printf("failed to create bitmap!\n");
		}
	}
	Segmento(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
	void imprimeSegmentos()
	{
	    al_draw_bitmap(bmp, x, y, 0);
		al_flip_display();
	}
	int getCoordenadaX()
	{
		return x;
	}
	int getCoordenadaY()
	{
		return y;
	}
    ~Segmento()
    {
        al_destroy_bitmap(bmp);
        cout << "destruiu segmento" << endl;
    }
};

class Cobrinha : public Segmento{
	int tamanho;
	static const int tamanho_maximo = 30;
	Segmento cabeca;
	//Segmento **segmentos;
public:
	Cobrinha()
	{
		tamanho = 1;
		//segmentos = new Segmento*[tamanho_maximo];
		//segmentos[0] = new Segmento(cabeca.getCoordenadaX() - 65, cabeca.getCoordenadaY());
	}
	void imprimeCobrinha()
	{
		cabeca.imprimeSegmentos();
        //for (int i = 0; i < tamanho; i++)
            //segmentos[i]->imprimeSegmentos();
        al_flip_display();
    }
	~Cobrinha()
	{
	    //for (int i = 0; i < tamanho; i++)
            //delete segmentos[i];
        //delete[] segmentos;
        cout << "destruiu cobrinha" << endl;
	}
};

class criaFundo
{
	ALLEGRO_BITMAP *fundo;
public:
	criaFundo(){}
	int imagemDeFundo()
	{
		fundo = al_load_bitmap("fundo.jpg");
		if(!fundo)
		{
			printf("failed to create bitmap!\n");
			return -1;
		}
		al_draw_bitmap(fundo, 0, 0, 0);
		al_set_target_bitmap(fundo);
		al_flip_display();
  	}
  	~criaFundo()
  	{
  		al_destroy_bitmap(fundo);
  		cout << "destruiu bitmap" << endl;
  	}
};

/*class criaDisplay
{
    ALLEGRO_DISPLAY *display = NULL;
public:
    criaDisplay()
    {
        display = al_create_display(SCREEN_W, SCREEN_H);
        if(!display)
        {
            cout << "failed to create display!\n";
        }
    }
    void set_target()
	{
		al_set_target_bitmap(al_get_backbuffer(display));
	}
	~criaDisplay()
	{
	    al_destroy_display(display);
	}
};*/

int main()
{
    srand((unsigned)time(NULL));

    //Reponsável pela impressão na tela
    //criaDisplay display;
    ALLEGRO_DISPLAY *display = NULL;
    //Fila de eventos
    //ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    //Eventos de tempo (ocorrem a cada X tempo)
    //ALLEGRO_TIMER *timer = NULL;

    criaFundo fundo;
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

    if(fundo.imagemDeFundo() == -1)
      return -1;

    //display.set_target();
    al_set_target_bitmap(al_get_backbuffer(display));

    //cobrinha.imprimeCobrinha();
    //cobrinha.imprimeCobrinha();

    al_rest(5.0);

    al_destroy_display(display);

	return 0;
}
