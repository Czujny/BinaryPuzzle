#pragma once
#ifndef PLANSZA_H
#define PLANSZA_H
#define RAMKA 1		//wielkosc ramki
#define MAXLOS 30	//maksymalny procent wypelnienia 
#define MINLOS 20	//minimalny procent wypelnienia
#define MAXPROB (rozmiar*rozmiar*rozmiar)	//maksymalna ilosc prob przy losowaniu planszy
#define MAXROZMIAR 22	//maksymalny rozmiar planszy
#define MINROZMIAR 2	//minimalny rozmiar planszy
#define MAXDLUGOSCROZMIAR 3 //maksymalna dlugosc rozmiaru planszy (liczba dwucyfrowa + NULL)
#define KOLORMOD 2			//kolor pola modyfikowalnego
#define KOLORNIEMOD 4		//kolor pola niemodyfikowalnego


struct plansza_t *stworzPlansze(int rozmiar);	//tworzy pusta plansze o zadanym rozmiarze

bool wpisz(struct stan_t *stan, int i, int j, char cyfra);	//wpisuje do miejsca w planszy znak jezeli to mozliwe

void usunGre(struct plansza_t *plansza);	//usuwa plansze

void losowaPlansza(int rozmiar, struct stan_t *stan);	//tworzy losowa plansze o zadanym rozmiarze

void usunPodswietlenia(struct plansza_t *plansza);	//usuwa wszelkie podswietlenia z planszy

void usunWartosci(struct plansza_t *plansza);	//usuwa wartosci nalozone przez funkcje(wywyolanie musi byc przed usunPodswietlenia)

char *kopiujWK(struct plansza_t *plansza, int i, int j, int wck, char znak);	//kopiuje wiersz badz kolumne jezeli po wpisaniu znaku bylaby pelna

struct plansza_t *kopiujPlansze(struct plansza_t *plansza);	//kopiuje cala plansze

int liczWypelnienie(struct plansza_t *plansza);	//liczy znaki na planszy

#endif // !RYSUJ_H
