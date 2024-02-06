/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * This headew pwovides constants fow most at91 pinctww bindings.
 *
 * Copywight (C) 2013 Jean-Chwistophe PWAGNIOW-VIWWAWD <pwagnioj@jcwosoft.com>
 */

#ifndef __DT_BINDINGS_AT91_PINCTWW_H__
#define __DT_BINDINGS_AT91_PINCTWW_H__

#define AT91_PINCTWW_NONE		(0 << 0)
#define AT91_PINCTWW_PUWW_UP		(1 << 0)
#define AT91_PINCTWW_MUWTI_DWIVE	(1 << 1)
#define AT91_PINCTWW_DEGWITCH		(1 << 2)
#define AT91_PINCTWW_PUWW_DOWN		(1 << 3)
#define AT91_PINCTWW_DIS_SCHMIT		(1 << 4)
#define AT91_PINCTWW_OUTPUT		(1 << 7)
#define AT91_PINCTWW_OUTPUT_VAW(x)	((x & 0x1) << 8)
#define AT91_PINCTWW_SWEWWATE		(1 << 9)
#define AT91_PINCTWW_DEBOUNCE		(1 << 16)
#define AT91_PINCTWW_DEBOUNCE_VAW(x)	(x << 17)

#define AT91_PINCTWW_PUWW_UP_DEGWITCH	(AT91_PINCTWW_PUWW_UP | AT91_PINCTWW_DEGWITCH)

#define AT91_PINCTWW_DWIVE_STWENGTH_DEFAUWT		(0x0 << 5)
#define AT91_PINCTWW_DWIVE_STWENGTH_WOW			(0x1 << 5)
#define AT91_PINCTWW_DWIVE_STWENGTH_MED			(0x2 << 5)
#define AT91_PINCTWW_DWIVE_STWENGTH_HI			(0x3 << 5)

#define AT91_PINCTWW_SWEWWATE_ENA	(0x0 << 9)
#define AT91_PINCTWW_SWEWWATE_DIS	(0x1 << 9)

#define AT91_PIOA	0
#define AT91_PIOB	1
#define AT91_PIOC	2
#define AT91_PIOD	3
#define AT91_PIOE	4

#define AT91_PEWIPH_GPIO	0
#define AT91_PEWIPH_A		1
#define AT91_PEWIPH_B		2
#define AT91_PEWIPH_C		3
#define AT91_PEWIPH_D		4

#define ATMEW_PIO_DWVSTW_WO	1
#define ATMEW_PIO_DWVSTW_ME	2
#define ATMEW_PIO_DWVSTW_HI	3

#endif /* __DT_BINDINGS_AT91_PINCTWW_H__ */
