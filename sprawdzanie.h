#pragma once
#ifndef SPRAWDZANIE_H
#define SPRAWDZANIE_H	//stale do funkcji sprawdzajacych
#define WIERSZ 1		//ozaczenie wiersza
#define KOLUMNA 2		//oznaczenie kolumny
#define ZGODNOSC 3		//wartosc zwracana gdy i wiersz i kolumna jest zgodna z zasada w funckjach nie zwracajacych bool
#define WIERSZIKOLUMNA 4	//oznaczenie wiersza i kolumny
#define NIEZGODNOSC -1	//wartosc zwracana gdy wystepuje niezgodnosc w funkcji ktora nie zwraca bool


bool regula1(struct plansza_t *plansza, int i, int j, int znak);	//sprawdza regule1

int regula2(struct plansza_t *plansza, int i, int j, char znak);	//sprawdza regule2

int *regula3(struct plansza_t *plansza, int i, int j, char znak);	//sprawdza regule3

int licz01(struct plansza_t *plansza, char znak, int lp, int wck);	//liczy ilosc znaku w wierszu badz kolumnie

int czyJednakowe(struct plansza_t *plansza, char *linia, int lp, int wck);	//sprawdza czy istnieje taki sam wiersz lub kolmna jak linia

void wyswietlPodpowiedz(struct stan_t *stan);	//wyswietla jaki znak mozna wstawic w danym miejscu

bool podpowiedzZnak(struct stan_t *stan, char znak);	//wyswietla dlaczego nie mozna wstawic danego znaku

bool czyUkonczenie(struct stan_t *stan);	//podswietla pola ktorych nie mozna wypelnic

bool sprawdzUkonczenie(struct plansza_t *plansza);	//sprawdza czy jest mozliwe ukonczenie gry

void wyswietlReg2(struct stan_t *stan);	//wyswietla liczbe 0 i 1 w wierszach i kolumnach

void liczbaWiersze(struct plansza_t *plansza);	//wyswietla liczbe 0 i 1 w wierszach

void liczbaKolumny(struct plansza_t *plansza);	//wyswietla liczbe 0 i 1 w kolumnach

bool czyWpisanie(struct plansza_t *plansza, int i, int j, char znak);	//sprawdza czy wpisanie znaku jest mozliwe

void wyswietlJednoznaczne(struct stan_t *stan);	//wyswietla plansze z jednoznacznymi polami i umozliwia ich wpisanie do planszy

char czyPoleJednoznaczne(struct plansza_t *oryginal, struct plansza_t *kopia, int i, int j);	//sprawdza czy pole jest jednoznaczne

int czyPlanszaJednoznaczne(struct plansza_t *oryginal, struct plansza_t *kopia);	//zmienia kolor tla pol jednoznacznych i zwraca ich ilosc

#endif