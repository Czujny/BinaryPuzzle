#include "stdafx.h"
#include<stdio.h>
#include <stdlib.h>
#include"conio2.h"
#include "struktury.h"
#include "plansza.h"
#include "rysuj.h"
#include "sprawdzanie.h"
#include "pliki.h"
#include <time.h>


struct plansza_t *stworzPlansze(int rozmiar) {

	struct plansza_t *plansza = new struct plansza_t;
	plansza->rozmiar = rozmiar + 2*RAMKA;
	plansza->pola = new struct pole_t *[rozmiar + 2*RAMKA];

	for (int i = 0; i < rozmiar + 2*RAMKA; i++) {

		plansza->pola[i] = new struct pole_t[rozmiar + 2*RAMKA];
	}

	for (int i = 0; i < rozmiar + 2*RAMKA; i++) {

		for (int j = 0; j < rozmiar + 2*RAMKA; j++) {

			if (i == 0 || i == rozmiar + RAMKA || j == 0 || j == rozmiar + RAMKA) {

				plansza->pola[i][j].wartosc = '*';
				plansza->pola[i][j].modyfikowalna = false;
				plansza->pola[i][j].kolor = KOLORNIEMOD;
				plansza->pola[i][j].tlo = BLACK;
			}
			else {

				plansza->pola[i][j].wartosc = '.';
				plansza->pola[i][j].modyfikowalna = true;
				plansza->pola[i][j].kolor = KOLORMOD;
				plansza->pola[i][j].tlo = BLACK;
			}
		}
	}

	return plansza;
}


bool wpisz(struct stan_t *stan, int i, int j, char znak) {

	
	if (znak != '.' && czyWpisanie(stan->plansza, i, j, znak)) {

		stan->plansza->pola[i][j].wartosc = znak;
		return true;
	}
	else if (znak == '.') {

		stan->plansza->pola[i][j].wartosc = znak;
		return true;
	}
			
	return false;
}


void usunGre(struct plansza_t *plansza) {

	if (plansza != NULL) {

		for (int i = 0; i < plansza->rozmiar; i++)delete[] plansza->pola[i];

		delete[] plansza->pola;
		delete[] plansza;
		plansza = NULL;
	}
}


void losowaPlansza(int rozmiar, struct stan_t *stan) {

	struct plansza_t *losowa = stworzPlansze(rozmiar);
	usunGre(stan->plansza);
	stan->plansza = losowa;
	int licznik = 0;
	srand(time(NULL));
	int wypelnienie = MINLOS + rand() % (MAXLOS - MINLOS);

	for (int k = 0; k < MAXPROB; k++) {

		int i = 1 + rand() % rozmiar;
		int j = 1 + rand() % rozmiar;
		char wartosc = rand() % 2 + '0';

		gotoxy(YPLANSZY + i, XPLANSZY + j);

		if (wpisz(stan, i, j, wartosc) == true) {

			losowa->pola[i][j].modyfikowalna = false;
			losowa->pola[i][j].kolor = KOLORNIEMOD;
			losowa->pola[i][j].tlo = BLACK;
			licznik++;
			if (wypelnienie < (100*licznik)/(rozmiar*rozmiar))break;	//wypelnienie jest wartoscia procent
		}
	}

	gotoxy(XPLANSZY + RAMKA, YPLANSZY + RAMKA);
}


void usunPodswietlenia(struct plansza_t *plansza) {

	for (int i = 1; i < plansza->rozmiar - RAMKA; i++) {

		for (int j = 1; j < plansza->rozmiar - RAMKA; j++) {

			if (plansza->pola[i][j].tlo != BLACK) {

				plansza->pola[i][j].tlo = BLACK;
			}
		}
	}
}


void usunWartosci(struct plansza_t *plansza) {

	for (int i = 1; i < plansza->rozmiar - RAMKA; i++) {

		for (int j = 1; j < plansza->rozmiar - RAMKA; j++) {

			if (plansza->pola[i][j].tlo != BLACK) {

				plansza->pola[i][j].wartosc = '.';
			}
		}
	}
}


char *kopiujWK(struct plansza_t *plansza, int i, int j, int wck, char znak) {

	int licznik = 0;
	char *kopia = new char[plansza->rozmiar - RAMKA]();

	if (wck == WIERSZ)for (int k = 1; k < plansza->rozmiar - RAMKA; k++) {

		if (plansza->pola[i][k].wartosc == '.')licznik++;

		if (licznik > 1) {

			delete[] kopia;
			return NULL;
		}

		if (k != j)kopia[k - 1] = plansza->pola[i][k].wartosc;
		else kopia[k - 1] = znak;
	}
	else if (wck == KOLUMNA)for (int k = 1; k < plansza->rozmiar - RAMKA; k++) {

		if (plansza->pola[k][j].wartosc == '.')licznik++;

		if (licznik > 1) {

			delete[] kopia;
			return NULL;
		}

		if (k != i)kopia[k - 1] = plansza->pola[k][j].wartosc;
		else kopia[k - 1] = znak;
	}
	kopia[plansza->rozmiar - RAMKA - 1] = '\0';

	return kopia;
}


struct plansza_t *kopiujPlansze(struct plansza_t *plansza) {

	struct plansza_t *kopia = stworzPlansze(plansza->rozmiar - 2*RAMKA);

	for (int i = 1; i < plansza->rozmiar - RAMKA; i++) {

		for (int j = 1; j < plansza->rozmiar - RAMKA; j++) {

			kopia->pola[i][j].wartosc = plansza->pola[i][j].wartosc;
			kopia->pola[i][j].kolor = plansza->pola[i][j].kolor;
			kopia->pola[i][j].modyfikowalna = plansza->pola[i][j].modyfikowalna;
			kopia->pola[i][j].tlo = plansza->pola[i][j].tlo;
		}
	}

	return kopia;
}


int liczWypelnienie(struct plansza_t *plansza) {

	int licznik = 0;

	for (int i = 1; i < plansza->rozmiar - RAMKA; i++) {

		for (int j = 1; j < plansza->rozmiar - RAMKA; j++) {

			if (plansza->pola[i][j].wartosc != '.')licznik++;
		}
	}

	return licznik;
}