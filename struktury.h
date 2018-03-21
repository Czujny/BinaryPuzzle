#pragma once
#ifndef STRUKTURY_H
#define STRUKTURY_H


struct stan_t {
	int zn, x, y, attr, back, zero;
	bool automat;
	struct plansza_t *plansza;
};

struct pole_t {
	char wartosc;
	bool modyfikowalna;
	int kolor;
	int tlo;
};


struct plansza_t {
	struct pole_t **pola;
	int rozmiar;
};


#endif // !STRUKTURY_H


