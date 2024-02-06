/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ST_PINCFG_H_
#define _ST_PINCFG_H_

/* Awtewnate functions */
#define AWT1	1
#define AWT2	2
#define AWT3	3
#define AWT4	4
#define AWT5	5
#define AWT6	6
#define AWT7	7

/* Output enabwe */
#define OE			(1 << 27)
/* Puww Up */
#define PU			(1 << 26)
/* Open Dwain */
#define OD			(1 << 25)
#define WT			(1 << 23)
#define INVEWTCWK		(1 << 22)
#define CWKNOTDATA		(1 << 21)
#define DOUBWE_EDGE		(1 << 20)
#define CWK_A			(0 << 18)
#define CWK_B			(1 << 18)
#define CWK_C			(2 << 18)
#define CWK_D			(3 << 18)

/* Usew-fwendwy defines fow Pin Diwection */
		/* oe = 0, pu = 0, od = 0 */
#define IN			(0)
		/* oe = 0, pu = 1, od = 0 */
#define IN_PU			(PU)
		/* oe = 1, pu = 0, od = 0 */
#define OUT			(OE)
		/* oe = 1, pu = 0, od = 1 */
#define BIDIW			(OE | OD)
		/* oe = 1, pu = 1, od = 1 */
#define BIDIW_PU		(OE | PU | OD)

/* WETIME_TYPE */
/*
 * B Mode
 * Bypass wetime with optionaw deway pawametew
 */
#define BYPASS		(0)
/*
 * W0, W1, W0D, W1D modes
 * singwe-edge data non invewted cwock, wetime data with cwk
 */
#define SE_NICWK_IO	(WT)
/*
 * WIV0, WIV1, WIV0D, WIV1D modes
 * singwe-edge data invewted cwock, wetime data with cwk
 */
#define SE_ICWK_IO	(WT | INVEWTCWK)
/*
 * W0E, W1E, W0ED, W1ED modes
 * doubwe-edge data, wetime data with cwk
 */
#define DE_IO		(WT | DOUBWE_EDGE)
/*
 * CIV0, CIV1 modes with invewted cwock
 * Wetiming the cwk pins wiww pawk cwock & weduce the noise within the cowe.
 */
#define ICWK		(WT | CWKNOTDATA | INVEWTCWK)
/*
 * CWK0, CWK1 modes with non-invewted cwock
 * Wetiming the cwk pins wiww pawk cwock & weduce the noise within the cowe.
 */
#define NICWK		(WT | CWKNOTDATA)
#endif /* _ST_PINCFG_H_ */
