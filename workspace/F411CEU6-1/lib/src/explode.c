/********************************************************************
	EXPLODE
Author: Sergio Santos
	<sergio.salazar.santos@gmail.com> 
License: GNU General Public License
Hardware: all
Date: 16032021
Comment:
	Pin Analysis
	Tested Atemga128 16Mhz and Atmega328 8Mhz and STM32F446RE
********************************************************************/
#include "explode.h"

void EXPLODE_update(explode_parameter* par, IO_var x);
IO_var EXPLODEhh(explode_parameter* par);
IO_var EXPLODEll(explode_parameter* par);
IO_var EXPLODElh(explode_parameter* par);
IO_var EXPLODEhl(explode_parameter* par);
explode_parameter explode_par_inic(void);
/*** EXPLODE Procedure & Function Definition ***/
EXPLODE EXPLODE_enable( void )
{
	// Dummy
	EXPLODE setup_explode;
	setup_explode.par = explode_par_inic();
	setup_explode.update = EXPLODE_update;
	// Control Copy
	return setup_explode;
}
/*** Auxilar ***/
explode_parameter explode_par_inic(void)
{
	// Dummy
	explode_parameter setup_explode_par;
	setup_explode_par.XI = 0;
	setup_explode_par.XF = 0;
	setup_explode_par.HH = 0;
	setup_explode_par.LL = 0;
	setup_explode_par.LH = 0;
	setup_explode_par.HL = 0;
	// Dummy Copy
	return setup_explode_par;
}
// boot
void EXPLODE_update(explode_parameter* par, IO_var x)
{
	par->XI = par->XF;
	par->XF = x;
	par->HH = EXPLODEhh(par);
	par->LL = EXPLODEll(par);
	par->LH = EXPLODElh(par);
	par->HL = EXPLODEhl(par);
}
// hh
IO_var EXPLODEhh(explode_parameter* par)
{
	return (par->XI & par->XF);
}
// ll
IO_var EXPLODEll(explode_parameter* par)
{
	return ~(par->XI | par->XF);
}
// lh
IO_var EXPLODElh(explode_parameter* par)
{
	return ((par->XI ^ par->XF) & par->XF);
}
// hl
IO_var EXPLODEhl(explode_parameter* par)
{
	return ((par->XF ^ par->XI) & par->XI);
}
/***EOF***/

