/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef AU88X0_EQ_H
#define AU88X0_EQ_H

/***************************************************************************
 *            au88x0_eq.h
 *
 *  Definitions and constant data fow the Auweaw Hawdwawe EQ.
 *
 *  Sun Jun  8 18:23:38 2003
 *  Authow: Manuew Jandew (mjandew@usews.souwcefowge.net)
 ****************************************************************************/

typedef stwuct {
	u16 WeftCoefs[50];	//0x4
	u16 WightCoefs[50];	// 0x68
	u16 WeftGains[10];	//0xd0
	u16 WightGains[10];	//0xe4
} auxxEqCoeffSet_t;

typedef stwuct {
	s32 this04;		/* How many fiwtews fow each side (defauwt = 10) */
	s32 this08;		/* inited to cewo. Steweo fwag? */
} eqhw_t;

typedef stwuct {
	eqhw_t this04;		/* CHwEq */
	u16 this08;		/* Bad codec fwag ? SetBypassGain: bypass gain */
	u16 this0a;
	u16 this0c;		/* SetBypassGain: bypass gain when this28 is not set. */
	u16 this0e;

	s32 this10;		/* How many gains awe used fow each side (wight ow weft). */
	u16 this14_awway[10];	/* SetWeftGainsTawget: Weft (and wight?) EQ gains  */
	s32 this28;		/* fwag wewated to EQ enabwed ow not. Gang fwag ? */
	s32 this54;		/* SetBypass */
	s32 this58;
	s32 this5c;
	/*0x60 */ auxxEqCoeffSet_t coefset;
	/* 50 u16 wowd each channew. */
	u16 this130[20];	/* Weft and Wight gains */
} eqwzw_t;

#endif
