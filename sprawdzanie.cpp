#include "stdafx.h"
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include"conio2.h"
#include "struktury.h"
#include "plansza.h"
#include "rysuj.h"
#include "klawiatura.h"
#include "sprawdzanie.h"


bool regula1(struct plansza_t *plansza, int i, int j, int znak) {
	
	if (znak == '.')return true;

	if (i - 2 > 0 && znak == plansza->pola[i-1][j].wartosc && znak == plansza->pola[i-2][j].wartosc)return false;
	else if (i + 2 < plansza->rozmiar - RAMKA && znak == plansza->pola[i+1][j].wartosc && znak == plansza->pola[i+2][j].wartosc)return false;
	else if (j - 2 > 0 && znak == plansza->pola[i][j-1].wartosc && znak == plansza->pola[i][j-2].wartosc)return false;
	else if (j + 2 < plansza->rozmiar - RAMKA && znak == plansza->pola[i][j+1].wartosc && znak == plansza->pola[i][j+2].wartosc)return false;
	else if (i - 1 > 0 && i + 1 < plansza->rozmiar - RAMKA && znak == plansza->pola[i - 1][j].wartosc && znak == plansza->pola[i + 1][j].wartosc)return false;
	else if (j - 1 > 0 && j + 1 < plansza->rozmiar - RAMKA && znak == plansza->pola[i][j - 1].wartosc && znak == plansza->pola[i][j + 1].wartosc)return false;

	return true;
}


int regula2(struct plansza_t *plansza, int i, int j, char znak) { 

	if ((licz01(plansza, znak, i, WIERSZ) >= (plansza->rozmiar - 2 * RAMKA) / 2) && (licz01(plansza, znak, j, KOLUMNA) >= (plansza->rozmiar - 2 * RAMKA) / 2))return WIERSZIKOLUMNA;
	if (licz01(plansza, znak, i, WIERSZ) >= (plansza->rozmiar - 2 * RAMKA)/2)return WIERSZ;
	else if (licz01(plansza, znak, j, KOLUMNA) >= (plansza->rozmiar - 2 * RAMKA)/2)return KOLUMNA;

	return ZGODNOSC;
}


int *regula3(struct plansza_t *plansza, int i, int j, char znak) {

	char *wiersz = kopiujWK(plansza, i, j, WIERSZ, znak);
	char *kolumna = kopiujWK(plansza, i, j, KOLUMNA, znak);
	int *krotka = new int[4]();
	bool flaga = false;

	if (wiersz != NULL) {	//czy wiersz jest pelny

		int jednakowa = czyJednakowe(plansza, wiersz, i, WIERSZ);
		if (jednakowa != NIEZGODNOSC) {
			krotka[0] = WIERSZ;
			krotka[1] = jednakowa;
			flaga = true;
		}
	}

	if (kolumna != NULL) {	//czy kolumna jest pelna

		int jednakowa = czyJednakowe(plansza, kolumna, i, KOLUMNA);
		if (jednakowa != NIEZGODNOSC) {
			krotka[2] = KOLUMNA;
			krotka[3] = jednakowa;
			flaga = true;
		}
	}

	delete[] wiersz;
	delete[] kolumna;
	if (flaga == true)return krotka;

	delete[] krotka;

	return NULL;
}


int licz01(struct plansza_t *plansza, char znak, int lp, int wck) {

	int liczba = 0;

	if (wck == WIERSZ) {

		for (int k = 1; k < plansza->rozmiar - RAMKA; k++) {

			if (plansza->pola[lp][k].wartosc == znak)liczba++;
		}
	}
	else if (wck == KOLUMNA) {

		for (int k = 1; k < plansza->rozmiar - RAMKA; k++) {

			if (plansza->pola[k][lp].wartosc == znak)liczba++;
		}
	}

	return liczba;
}


int czyJednakowe(struct plansza_t *plansza, char *linia, int lp, int wck) {

	int licznik = 0;

	if(wck == WIERSZ)for (int k = 1; k < plansza->rozmiar - RAMKA; k++) {

		for (int l = 1; l < plansza->rozmiar - RAMKA; l++) {

			if (k == lp || plansza->pola[k][l].wartosc == '.')break;
			if (linia[l - 1] == plansza->pola[k][l].wartosc)licznik++;	//linia nie posiada ramki
		}

		if (licznik == plansza->rozmiar - 2 * RAMKA)return k;
		licznik = 0;
	}
	else if(wck == KOLUMNA)for (int k = 1; k < plansza->rozmiar - RAMKA; k++) {

		for (int l = 1; l < plansza->rozmiar - RAMKA; l++) {

			if (k == lp || plansza->pola[l][k].wartosc == '.')break;
			if (linia[l - 1] == plansza->pola[l][k].wartosc)licznik++;
		}

		if (licznik == plansza->rozmiar - 2 * RAMKA)return k;
		licznik = 0;
	}

	return NIEZGODNOSC;
}


void wyswietlPodpowiedz(struct stan_t *stan){

	textcolor(CYAN);

	if (stan->plansza->pola[stan->y - YPLANSZY][stan->x - XPLANSZY].modyfikowalna == false)piszLegende("Pole niemodyfikowalne");
	else {

		if (podpowiedzZnak(stan, '0') == true)piszLegende("Mozna wpisac 0");
		if (podpowiedzZnak(stan, '1') == true)piszLegende("Mozna wpisac 1");
	}

	textcolor(stan->attr);

	int klawiatura = getch();
	if (klawiatura == 0)getch();	//zabepieczenie na wypadek strzalek
}


bool podpowiedzZnak(struct stan_t *stan, char znak) {

	bool warunek1 = regula1(stan->plansza, stan->y - YPLANSZY, stan->x - XPLANSZY, znak), flaga = true;
	int warunek2 = regula2(stan->plansza, stan->y - YPLANSZY, stan->x - XPLANSZY, znak);
	int *warunek3 = regula3(stan->plansza, stan->y - YPLANSZY, stan->x - XPLANSZY, znak);
	char tekst[50];

	if (warunek1 == false) {

		sprintf(tekst, "3 znaki %c obok siebie", znak);
		piszLegende(tekst);
		flaga = false;
	}
	if (warunek2 == WIERSZ) {

		sprintf(tekst, "Ponad polowa %c w wierszu", znak);
		piszLegende(tekst);
		flaga = false;
	}
	else if (warunek2 == KOLUMNA) {

		sprintf(tekst, "Ponad polowa %c w kolumine", znak);
		piszLegende(tekst);
		flaga = false;
	}
	else if (warunek2 == WIERSZIKOLUMNA) {

		sprintf(tekst, "Ponad polowa %c w wierszu", znak);
		piszLegende(tekst);
		sprintf(tekst, "Ponad polowa %c w kolumine", znak);
		piszLegende(tekst);
		flaga = false;
	}
	if (warunek3 != NULL && warunek3[0] == WIERSZ) {

		sprintf(tekst, "Dla %c wiersz taki sam jak %d", znak, warunek3[1]);
		piszLegende(tekst);
		flaga = false;
	}
	if (warunek3 != NULL && warunek3[2] == KOLUMNA) {

		sprintf(tekst, "Dla %c kolumna taka sama jak %d", znak, warunek3[3]);
		piszLegende(tekst);
		flaga = false;
	}

	delete[] warunek3;
	return flaga;
}


bool czyUkonczenie(struct stan_t *stan) {

	bool flaga = sprawdzUkonczenie(stan->plansza);
	int klawiatura = 1;

	if (flaga == false) {

		rysujPlansze(stan, XPLANSZY, YPLANSZY);

		if (stan->automat != true)klawiatura = getch();	//jezeli tryb automatyczny jest wlaczony nie czeka na klawisz
		if (klawiatura == 0)getch();	//zabezpiczenie na wypadek strzalek

		usunPodswietlenia(stan->plansza);
	}

	return flaga;
}


bool sprawdzUkonczenie(struct plansza_t *plansza) {

	bool flaga = true;

	for (int i = 1; i < plansza->rozmiar - RAMKA; i++) {

		for (int j = 1; j < plansza->rozmiar - RAMKA; j++) {

			if (plansza->pola[i][j].wartosc == '.') {

				int regula01 = regula1(plansza, i, j, '0'), regula02 = regula2(plansza, i, j, '0'), *regula03 = regula3(plansza, i, j, '0');
				int regula11 = regula1(plansza, i, j, '1'), regula12 = regula2(plansza, i, j, '1'), *regula13 = regula3(plansza, i, j, '1');

				if ((regula01 == false || regula02 != ZGODNOSC || regula03 != NULL) && (regula11 == false || regula12 != ZGODNOSC || regula13 != NULL)) {

					flaga = false;
					plansza->pola[i][j].tlo = RED;
				}

				delete[] regula03;
				delete[] regula13;
			}
		}
	}

	return flaga;
}


void wyswietlReg2(struct stan_t *stan) {
	
	int xPoczatkowy = stan->x;
	int yPoczatkowy = stan->y;
	int kolorPoczatkowy = stan->attr;

	textcolor(CYAN);

	liczbaWiersze(stan->plansza);
	liczbaKolumny(stan->plansza);

	textcolor(kolorPoczatkowy);
	stan->x = xPoczatkowy;
	stan->y = yPoczatkowy;
	gotoxy(stan->x, stan->y);
	int klawiatura = 1;
	if(stan->automat != true)klawiatura = getch();	//jezeli tryb automatyczny jest wlaczony nie czeka na klawisz
	if (klawiatura == 0)getch();	//zabezpieczenie na wypadek strzalek
}


void liczbaWiersze(struct plansza_t *plansza) {


	int liczba0, liczba1;
	char info[32];

	for (int i = 1; i < plansza->rozmiar - RAMKA; i++) {

		liczba0 = licz01(plansza, '0', i, WIERSZ);
		liczba1 = licz01(plansza, '1', i, WIERSZ);
		
		sprintf(info, "0: %d", liczba0);
		gotoxy(XPLANSZY + plansza->rozmiar, YPLANSZY + i);
		puts(info);

		sprintf(info, "1: %d", liczba1);
		gotoxy(XPLANSZY - strlen(info), YPLANSZY + i);
		puts(info);
	}

}


void liczbaKolumny(struct plansza_t *plansza){

	int liczba0, liczba1;
	char ilosc0[3], ilosc1[3];

	gotoxy(XPLANSZY - 1, YPLANSZY - 1);
	putch('0');
	putch(':');
	gotoxy(XPLANSZY - 1, YPLANSZY + plansza->rozmiar);
	putch('1');
	putch(':');

	for (int i = 1; i < plansza->rozmiar - RAMKA; i++) {

		liczba0 = licz01(plansza, '0', i, KOLUMNA);
		liczba1 = licz01(plansza, '1', i, KOLUMNA);

		_itoa(liczba0, ilosc0, 10);
		_itoa(liczba1, ilosc1, 10);

		if (ilosc0[1] == '\0') {
			
			gotoxy(XPLANSZY + i, YPLANSZY - 1);
			putch(ilosc0[0]);
		}
		else if(ilosc0[1] != '\0'){

			gotoxy(XPLANSZY + i, YPLANSZY - 2);
			putch(ilosc0[0]);
			gotoxy(XPLANSZY + i, YPLANSZY - 1);
			putch(ilosc0[1]);
		}

		gotoxy(XPLANSZY + i, YPLANSZY + plansza->rozmiar);
		putch(ilosc1[0]);
		if (ilosc1[1] != '\0') {
			gotoxy(XPLANSZY + i, YPLANSZY + plansza->rozmiar + 1);
			putch(ilosc1[1]);
		}
	}
	
}


bool czyWpisanie(struct plansza_t *plansza, int i, int j, char znak) {

	int wynik1 = regula1(plansza, i, j, znak);
	int wynik2 = regula2(plansza, i, j, znak);
	int *wynik3 = regula3(plansza, i, j, znak);
	
	if (plansza->pola[i][j].modyfikowalna && wynik1 == true && wynik2 == ZGODNOSC && wynik3 == NULL) {

		delete[] wynik3;
		return true;
	}

	delete[] wynik3;
	return false;
}


void wyswietlJednoznaczne(struct stan_t *stan) {

	struct plansza_t *kopia = kopiujPlansze(stan->plansza), *oryginal = stan->plansza;

	int flaga = czyPlanszaJednoznaczne(stan->plansza, kopia);

	if (flaga > 0) {

		stan->plansza = kopia;
		rysujPlansze(stan, XPLANSZY, YPLANSZY);
		textcolor(CYAN);
		piszLegende("w = wpisz wartosci");
		textcolor(stan->attr);
		int klawiatura = getch();

		if (klawiatura == 'w' || klawiatura == 'W') {

			usunPodswietlenia(stan->plansza);
			usunGre(oryginal);
			return;
		}
		else {

			if (klawiatura == 0)getch();	//zabezpieczenie na wypadek strzalek
			stan->plansza = oryginal;
			usunGre(kopia);
			return;
		}
	}

	usunGre(kopia);
}


char czyPoleJednoznaczne(struct plansza_t *oryginal, struct plansza_t *kopia, int i, int j) {

	if (kopia->pola[i][j].wartosc == '.') {

		if (czyWpisanie(oryginal, i, j, '0') == true && czyWpisanie(oryginal, i, j, '1') == false && czyWpisanie(kopia, i, j, '0') == true)return '0';

		if (czyWpisanie(oryginal, i, j, '1') == true && czyWpisanie(oryginal, i, j, '0') == false && czyWpisanie(kopia, i, j, '1') == true)return '1';
	}

	return NIEZGODNOSC;
}


int czyPlanszaJednoznaczne(struct plansza_t *oryginal, struct plansza_t *kopia) {

	int iloscJednoznacznych = 0;

	for (int i = 1; i < oryginal->rozmiar - RAMKA; i++) {

		for (int j = 1; j < oryginal->rozmiar - RAMKA; j++) {

			if (czyPoleJednoznaczne(oryginal, kopia, i, j) == '0') {

				iloscJednoznacznych++;
				kopia->pola[i][j].wartosc = '0';
				kopia->pola[i][j].tlo = LIGHTGREEN;
			}
			else if (czyPoleJednoznaczne(oryginal, kopia, i, j) == '1') {

				iloscJednoznacznych++;
				kopia->pola[i][j].wartosc = '1';
				kopia->pola[i][j].tlo = LIGHTGREEN;
			}
		}
	}

	return iloscJednoznacznych;
}


