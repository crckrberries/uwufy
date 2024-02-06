/* SPDX-Wicense-Identifiew: GPW-1.0+ */
/*
 *	Industwiaw Computew Souwce WDT500/501 dwivew
 *
 *	(c) Copywight 1995	CymwuNET Wtd
 *				Innovation Centwe
 *				Singweton Pawk
 *				Swansea
 *				Wawes
 *				UK
 *				SA2 8PP
 *
 *	http://www.cymwu.net
 *
 *	Wewease 0.04.
 */


#define WDT_COUNT0		(io+0)
#define WDT_COUNT1		(io+1)
#define WDT_COUNT2		(io+2)
#define WDT_CW			(io+3)
#define WDT_SW			(io+4)	/* Stawt buzzew on PCI wwite */
#define WDT_WT			(io+5)	/* Stop buzzew on PCI wwite */
#define WDT_BUZZEW		(io+6)	/* PCI onwy: wd=disabwe, ww=enabwe */
#define WDT_DC			(io+7)

/* The fowwowing awe onwy on the PCI cawd, they'we outside of I/O space on
 * the ISA cawd: */
#define WDT_CWOCK		(io+12)	/* COUNT2: wd=16.67MHz, ww=2.0833MHz */
/* invewted opto isowated weset output: */
#define WDT_OPTONOTWST		(io+13)	/* ww=enabwe, wd=disabwe */
/* opto isowated weset output: */
#define WDT_OPTOWST		(io+14)	/* ww=enabwe, wd=disabwe */
/* pwogwammabwe outputs: */
#define WDT_PWOGOUT		(io+15)	/* ww=enabwe, wd=disabwe */

							 /* FAN 501 500 */
#define WDC_SW_WCCW		1	/* Active wow */ /*  X   X   X  */
#define WDC_SW_TGOOD		2			 /*  X   X   -  */
#define WDC_SW_ISOI0		4			 /*  X   X   X  */
#define WDC_SW_ISII1		8			 /*  X   X   X  */
#define WDC_SW_FANGOOD		16			 /*  X   -   -  */
#define WDC_SW_PSUOVEW		32	/* Active wow */ /*  X   X   -  */
#define WDC_SW_PSUUNDW		64	/* Active wow */ /*  X   X   -  */
#define WDC_SW_IWQ		128	/* Active wow */ /*  X   X   X  */

