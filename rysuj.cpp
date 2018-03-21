#include "stdafx.h"
#include<stdio.h>
#include"conio2.h"
#include "struktury.h"
#include "plansza.h"
#include "rysuj.h"
#include "sprawdzanie.h"


void rysujPlansze(struct stan_t *stan, int x, int y) {

	int xPoczatkowy = stan->x;
	int yPoczatkowy = stan->y;
	int tloPoczatkowe = stan->back;
	int kolorPoczatkowy = stan->attr;
	gotoxy(x, y);

	for (int i = 0; i < stan->plansza->rozmiar; i++) {

		for (int j = 0; j < stan->plansza->rozmiar; j++) {

			stan->attr = stan->plansza->pola[i][j].kolor;
			stan->back = stan->plansza->pola[i][j].tlo;
			textcolor(stan->attr);
			textbackground(stan->back);
			putch(stan->plansza->pola[i][j].wartosc);
		}

		gotoxy(x, ++y);	//przejscie do nastepnego wiersza
	}

	gotoxy(xPoczatkowy, yPoczatkowy);
	stan->attr = kolorPoczatkowy;
	stan->back = tloPoczatkowe;
}


int pozycjaYLegendy(int reset) {

	static int pozycjaY = YLEGENDY;

	if (reset == RESETUJ) {

		pozycjaY = YLEGENDY;
		return pozycjaY;
	}
	else {

		return pozycjaY++;
	}
}


void piszLegende(const char *legenda) {

	gotoxy(XLEGENDY, pozycjaYLegendy(POBIERZ));

	cputs(legenda);
}


void rysujGre(struct stan_t *stan) {

	char txt[32];

	textbackground(stan->back);
	clrscr();
	textcolor(stan->attr);
	pozycjaYLegendy(RESETUJ);
	piszOpcje();
	rysujPlansze(stan, XPLANSZY, YPLANSZY);
	textcolor(stan->attr);
	if (stan->automat == true) {

		textcolor(RED);
		piszLegende("TRYB AUTO");
		if(czyUkonczenie(stan) == false)piszLegende("NIE MOZNA UKONCZYC");
		textcolor(stan->attr);
		wyswietlReg2(stan);
	}
	if (stan->zn != 'r' && stan->zn != 'R') {

		sprintf(txt, "x = %d y = %d", stan->x, stan->y);
		piszLegende(txt);
		gotoxy(stan->x, stan->y);
	}
	else {

		stan->x = XPLANSZY + RAMKA;
		stan->y = YPLANSZY + RAMKA;
		sprintf(txt, "x = %d y = %d", stan->x, stan->y);
		piszLegende(txt);
		gotoxy(stan->x, stan->y);
	}
	if (liczWypelnienie(stan->plansza) == (stan->plansza->rozmiar - 2 * RAMKA)*(stan->plansza->rozmiar - 2 * RAMKA))piszLegende("WYGRALES");
	textbackground(stan->back);
	textcolor(stan->attr);
}


void piszOpcje() {

	piszLegende("Kamil Jedrzejczak 171660");
	piszLegende("a,b,c,d,e,f,g,h,i,j,k,l,m,n");
	piszLegende("ESC = wyjscie");
	piszLegende("strzalki = poruszanie");
	piszLegende("0 1 . = wpisanie cyfry");
	piszLegende("n = nowa gra");
	piszLegende("o = losuj plansze");
	piszLegende("p = podpowiedz");
	piszLegende("r = wprowadz rozmiar planszy");
	piszLegende("k = mozliwosc ukonczenia");
	piszLegende("d = wyswietl regule2");
	piszLegende("j = wyswietl jednoznaczne");
	piszLegende("a = tryb automatyczny");
	piszLegende("s = zapis gry");
	piszLegende("l = wczytaj gre");
}