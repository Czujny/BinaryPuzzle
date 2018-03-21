#include "stdafx.h"
#include<stdio.h>
#include"conio2.h"
#include "sprawdzanie.h"
#include "klawiatura.h"
#include "plansza.h"
#include "pliki.h"
#include "struktury.h"
#include "rysuj.h"


void przechwycKlawiature(struct stan_t *stan) {
	
	stan->zero = 0;
	stan->zn = getch();
	if (stan->zn == 0) {
		stan->zero = 1;
		stan->zn = getch();
		if (stan->zn == U_ARROW && stan->y > YPLANSZY + RAMKA) stan->y--;
		else if (stan->zn == D_ARROW && stan->y < YPLANSZY + stan->plansza->rozmiar - 2*RAMKA) stan->y++;
		else if (stan->zn == L_ARROW && stan->x > XPLANSZY + RAMKA) stan->x--;
		else if (stan->zn == R_ARROW && stan->x < XPLANSZY + stan->plansza->rozmiar - 2*RAMKA) stan->x++;
	}
	else if (stan->zn == '1')wpisz(stan,stan->y - YPLANSZY, stan->x - XPLANSZY, '1');
	else if (stan->zn == '0')wpisz(stan, stan->y - YPLANSZY, stan->x - XPLANSZY, '0');
	else if (stan->zn == '.')wpisz(stan, stan->y - YPLANSZY, stan->x - XPLANSZY, '.');
	else if (stan->zn == 'n' || stan->zn == 'N')planszaZPliku(stan, DOMYSLNAN);
	else if (stan->zn == 'o' || stan->zn == 'O') {

		int losRozmiar = stan->plansza->rozmiar;
		losowaPlansza(losRozmiar - 2*RAMKA, stan);
	}
	else if (stan->zn == 'p' || stan->zn == 'P')wyswietlPodpowiedz(stan);
	else if (stan->zn == 'r' || stan->zn == 'R')podajRozmiar(stan);
	else if (stan->zn == 'k' || stan->zn == 'K')czyUkonczenie(stan);
	else if (stan->zn == 'j' || stan->zn == 'J')wyswietlJednoznaczne(stan);
	else if (stan->zn == 'a' || stan->zn == 'A') {
		
		if(stan->automat == false)stan->automat = true;
		else if (stan->automat == true)stan->automat = false;
	}
	else if(stan->zn == 'd' || stan->zn == 'D')	wyswietlReg2(stan);
	else if (stan->zn == 's' || stan->zn == 'S')zapiszGre(stan);
	else if (stan->zn == 'l' || stan->zn == 'L')wczytajGre(stan);
}