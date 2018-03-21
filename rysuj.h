#pragma once
#ifndef RYSUJ_H
#define RYSUJ_H
#define XPLANSZY 35	//x poczatku planszy >= dlugosci legendy + 4(dlugosc wyswietlReg2)
#define YPLANSZY 3	//y poczatku planszy >= 3 przez wyswietlReg2
#define XLEGENDY 1	//x poczatku legendy
#define YLEGENDY 1	//y poczatku legendy
#define POBIERZ 0	//flaga funkcji pozycjaYLegendy do pobrania bez resetu
#define RESETUJ 1	//flaga funkcji pozycjaYLegendy do pobrania z resetem (przed poczatkiem rysowania)


void rysujPlansze(struct stan_t *stan, int x, int y);	//rysuje plansze

int pozycjaYLegendy(int reset);	//przechowuje aktualna pozycje legendy 

void piszLegende(const char *legenda);	//wypisuje pojedyncza legende na ekranie

void rysujGre(struct stan_t *stan);	//rysuje cala gre

void piszOpcje();	//wypisuje opcje na ekran

#endif
