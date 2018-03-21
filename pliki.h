#pragma once
#ifndef PLIKI_H
#define PLIKI_H
#define ROZSZERZENIE ".sav"	//rozszerzenie plikow zapisu
#define DOMYSLNAN "12"		//nazwa zapisu zawierajacego standardowa plansze do nowej gry
#define ROOT "gry/"			//folder z zapisami
#define MAXDLUGOSCNAZWYZAPISU 32


void planszaZPliku(struct stan_t *stan, const char *zrodlo);	//otwiera plansze z pliku badz tworzy losowa przy podawaniu rozmiaru

void podajRozmiar(struct stan_t *stan);	//pobiera rozmiar od uzytkownika

void zapiszGre(struct stan_t *stan);	//zapisuje gre do pliku w folderze z zapisami

void wczytajGre(struct stan_t *stan);	//wczytuje zapis gry

char *podajNazwe();	//pobiera nazwe zapisu od uzytkownika

bool wczytajPlansze(struct stan_t *stan, FILE *plik, int romziar);	//wczytuje zapis o nazwie podanej przez uzytkownika

bool wczytajPodswietlenia(struct stan_t *stan, FILE *plik);	//wczytuje podswietlenie z pliku zapisu
#endif // !PLIKI_H
