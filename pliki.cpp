#include "stdafx.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "struktury.h"
#include "plansza.h"
#include "rysuj.h"
#include "sprawdzanie.h"
#include "pliki.h"
#include "klawiatura.h"


void planszaZPliku(struct stan_t *stan, const char *zrodlo) {

	stan->automat = false;
	char *sciezka = new char[strlen(zrodlo) + strlen(ROOT) + strlen(ROZSZERZENIE) + 1](); // strlen nie liczy \0
	char root[5] = ROOT;
	char rozmiarbuff[MAXDLUGOSCROZMIAR] = "", buffer;
	int liczba = 0, rozmiar = 0;
	strcat(sciezka, root);
	strcat(sciezka, zrodlo);
	strcat(sciezka, ROZSZERZENIE);
	FILE *plik = fopen(sciezka, "r");
	delete[] sciezka;
	
	if (plik != NULL) {
		do {

			buffer = fgetc(plik);
			rozmiarbuff[liczba] = buffer;
			liczba++;
		} while (buffer != '\n' && liczba <= 1);
		rozmiarbuff[2] = '\0';
		rozmiar = atoi(rozmiarbuff);
		wczytajPlansze(stan, plik, rozmiar);
		fclose(plik);
	}
	else if (atoi(zrodlo) != 0 || zrodlo[0] == '0') {

		rozmiar = atoi(zrodlo);
		if (rozmiar % 2 == 1 || rozmiar > MAXROZMIAR || rozmiar < MINROZMIAR) {

			clrscr();
			pozycjaYLegendy(RESETUJ);
			piszLegende("Bledny rozmiar");
			piszLegende("Nacisinj dowolny przycisk aby powrocic");
			getch();
		}
		else losowaPlansza(atoi(zrodlo), stan);
	}
		else {

			clrscr();
			pozycjaYLegendy(RESETUJ);
			piszLegende("Bledny plik");
			piszLegende("Nacisinj dowolny przycisk aby powrocic");
			getch();
		}

		stan->x = XPLANSZY + RAMKA;
		stan->y = YPLANSZY + RAMKA;
}


void podajRozmiar(struct stan_t *stan) {

	char liczba[MAXDLUGOSCROZMIAR] = "", buffor;
	int dlugosc = 0;
	clrscr();
	pozycjaYLegendy(RESETUJ);
	piszLegende("Podaj rozmiar nowej planszy: ");
	do {
		buffor = getch();
		if (buffor >= '0' && buffor <= '9' && dlugosc < MAXDLUGOSCROZMIAR - 1) {
			liczba[dlugosc] = buffor;
			putch(buffor);
			dlugosc++;
		}
		else if (buffor == BACKSPACE && dlugosc > 0) {

			liczba[--dlugosc] = '\0';
			clrscr();
			pozycjaYLegendy(RESETUJ);
			piszLegende("Podaj rozmiar nowej planszy: ");
			for (int i = 0; liczba[i] != '\0'; i++)putch(liczba[i]);
		}
	} while (buffor != ENTER);

	liczba[MAXDLUGOSCROZMIAR - 1] = '\0';
	
	planszaZPliku(stan, liczba);
}


void zapiszGre(struct stan_t *stan) {

	char *nazwa = podajNazwe(), buffor, rozmiar[3];
	_itoa(stan->plansza->rozmiar - 2*RAMKA, rozmiar, 10);
	char zrodlo[40] = ROOT;
	strcat(zrodlo, nazwa);
	strcat(zrodlo, ROZSZERZENIE);
	delete[] nazwa;
	FILE *zapis = fopen(zrodlo, "w");

	if (zapis != NULL) {

		fputs(rozmiar, zapis);
		fputc('\n', zapis);
		for (int i = 1; i < stan->plansza->rozmiar - RAMKA; i++) {
			
			for (int j = 1; j < stan->plansza->rozmiar - RAMKA; j++) {

				fputc(stan->plansza->pola[i][j].wartosc, zapis);
			}

			fputc('\n', zapis);
		}

		for (int i = 1; i < stan->plansza->rozmiar - RAMKA; i++) {

			for (int j = 1; j < stan->plansza->rozmiar - RAMKA; j++) {

				fputc(stan->plansza->pola[i][j].kolor, zapis);
			}

			fputc('\n', zapis);
		}
	}

	if (stan->automat == true)fputc(1, zapis);
	else if (stan->automat == false)fputc(0, zapis);

	fclose(zapis);
}


void wczytajGre(struct stan_t *stan) {

	char *nazwa = podajNazwe();

	planszaZPliku(stan, nazwa);

	delete[] nazwa;
}


char *podajNazwe() {

	char *nazwa = new char[MAXDLUGOSCNAZWYZAPISU](), buffor;
	int dlugosc = 0;
	clrscr();
	pozycjaYLegendy(RESETUJ);
	piszLegende("Podaj nazwe zapisu: ");
	do {
		buffor = getch();
		if (buffor == 0)getch();
		else if (((buffor >= 'a' && buffor <= 'z') || (buffor >= 'A' && buffor <= 'Z')) && dlugosc < MAXDLUGOSCNAZWYZAPISU - 1) {	//dlugosc musi byc odpowiednia aby tablica zmiescila \0
			nazwa[dlugosc] = buffor;
			putch(buffor);
			dlugosc++;
		}
		else if (buffor == BACKSPACE && dlugosc > 0) {

			nazwa[--dlugosc] = '\0';
			clrscr();
			pozycjaYLegendy(RESETUJ);
			piszLegende("Podaj nazwe zapisu: ");
			for (int i = 0; nazwa[i] != '\0'; i++)putch(nazwa[i]);
		}
	} while (buffor != ENTER);

	nazwa[dlugosc] = '\0';

	return nazwa;
}


bool wczytajPlansze(struct stan_t *stan, FILE *plik, int rozmiar) {

	if (plik != NULL) {

		usunGre(stan->plansza);
		stan->plansza = stworzPlansze(rozmiar);
		char buff;

		for (int i = 1; i < stan->plansza->rozmiar - RAMKA; i++) {

			for (int j = 1; j < stan->plansza->rozmiar - RAMKA; j++) {

				buff = fgetc(plik);
				if (buff != '\n')stan->plansza->pola[i][j].wartosc = buff;
				else stan->plansza->pola[i][j].wartosc = fgetc(plik);		//jezeli znak == \n pomin go i pobierz nastepny znak
			}
		}

		wczytajPodswietlenia(stan, plik);

		return true;
	}

	return false;
}


bool wczytajPodswietlenia(struct stan_t *stan, FILE *plik) {

	if (plik != NULL) {

		int buff;

		for (int i = 1; i < stan->plansza->rozmiar - RAMKA; i++) {

			for (int j = 1; j < stan->plansza->rozmiar - RAMKA; j++) {

				buff = fgetc(plik);
				if (buff != '\n')stan->plansza->pola[i][j].kolor = buff;
				else stan->plansza->pola[i][j].kolor = fgetc(plik);
				if (stan->plansza->pola[i][j].kolor == KOLORNIEMOD)stan->plansza->pola[i][j].modyfikowalna = false;
			}
		}

		fgetc(plik);	//pozbycie sie \n miedzy podswietleniem a auto w pliku z zapisem
		buff = fgetc(plik);
		if (buff == 1)stan->automat = true;
		else if(buff == 0) stan->automat = false;

		return true;
	}

	return false;
}