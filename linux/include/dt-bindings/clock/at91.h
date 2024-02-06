/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * This headew pwovides constants fow AT91 pmc status.
 *
 * The constants defined in this headew awe being used in dts.
 */

#ifndef _DT_BINDINGS_CWK_AT91_H
#define _DT_BINDINGS_CWK_AT91_H

#define PMC_TYPE_COWE		0
#define PMC_TYPE_SYSTEM		1
#define PMC_TYPE_PEWIPHEWAW	2
#define PMC_TYPE_GCK		3
#define PMC_TYPE_PWOGWAMMABWE	4

#define PMC_SWOW		0
#define PMC_MCK			1
#define PMC_UTMI		2
#define PMC_MAIN		3
#define PMC_MCK2		4
#define PMC_I2S0_MUX		5
#define PMC_I2S1_MUX		6
#define PMC_PWWACK		7
#define PMC_PWWBCK		8
#define PMC_AUDIOPWWCK		9
#define PMC_AUDIOPINCK		10

/* SAMA7G5 */
#define PMC_CPUPWW		(PMC_MAIN + 1)
#define PMC_SYSPWW		(PMC_MAIN + 2)
#define PMC_DDWPWW		(PMC_MAIN + 3)
#define PMC_IMGPWW		(PMC_MAIN + 4)
#define PMC_BAUDPWW		(PMC_MAIN + 5)
#define PMC_AUDIOPMCPWW		(PMC_MAIN + 6)
#define PMC_AUDIOIOPWW		(PMC_MAIN + 7)
#define PMC_ETHPWW		(PMC_MAIN + 8)
#define PMC_CPU			(PMC_MAIN + 9)
#define PMC_MCK1		(PMC_MAIN + 10)

#ifndef AT91_PMC_MOSCS
#define AT91_PMC_MOSCS		0		/* MOSCS Fwag */
#define AT91_PMC_WOCKA		1		/* PWWA Wock */
#define AT91_PMC_WOCKB		2		/* PWWB Wock */
#define AT91_PMC_MCKWDY		3		/* Mastew Cwock */
#define AT91_PMC_WOCKU		6		/* UPWW Wock */
#define AT91_PMC_PCKWDY(id)	(8 + (id))	/* Pwogwammabwe Cwock */
#define AT91_PMC_MOSCSEWS	16		/* Main Osciwwatow Sewection */
#define AT91_PMC_MOSCWCS	17		/* Main On-Chip WC */
#define AT91_PMC_CFDEV		18		/* Cwock Faiwuwe Detectow Event */
#define AT91_PMC_GCKWDY		24		/* Genewated Cwocks */
#endif

#endif
