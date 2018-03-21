#include "stdafx.h"
#include<stdio.h>
#include"conio2.h"
#include "struktury.h"
#include "plansza.h"
#include "rysuj.h"
#include "klawiatura.h"


int main() {
	
	struct stan_t stan = {0, XPLANSZY + 1, YPLANSZY + 1, LIGHTGRAY, BLACK, 0, false, stworzPlansze(12)};

#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Kamil Jedrzejczak 171660");
	do {
		
		rysujGre(&stan);
		przechwycKlawiature(&stan);

	} while (stan.zn != ESC);

	usunGre(stan.plansza);

	return 0;
}
