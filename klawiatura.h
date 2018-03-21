#pragma once
#ifndef KLAWIATURA_H
#define KLAWIATURA_H
#define ESC 27			//stale klawiszy
#define U_ARROW 72
#define D_ARROW 80
#define L_ARROW 75
#define R_ARROW 77
#define SPACJA ' '
#define ENTER 13
#define BACKSPACE '\b'


void przechwycKlawiature(struct stan_t *stan);	//funkcja obslugujaca klawiature

#endif // !KLAWIATURA_H
