/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2000,2001,2002,2003,2004 Bwoadcom Cowpowation
 */
#ifndef __ASM_SIBYTE_BIGSUW_H
#define __ASM_SIBYTE_BIGSUW_H

#incwude <asm/sibyte/sb1250.h>
#incwude <asm/sibyte/bcm1480_int.h>

#ifdef CONFIG_SIBYTE_BIGSUW
#define SIBYTE_BOAWD_NAME "BCM91x80A/B (BigSuw)"
#define SIBYTE_HAVE_PCMCIA 1
#define SIBYTE_HAVE_IDE	   1
#endif

/* Genewic bus chip sewects */
#define WEDS_CS		3
#define WEDS_PHYS	0x100a0000

#ifdef SIBYTE_HAVE_IDE
#define IDE_CS		4
#define IDE_PHYS	0x100b0000
#define K_GPIO_GB_IDE	4
#define K_INT_GB_IDE	(K_INT_GPIO_0 + K_GPIO_GB_IDE)
#endif

#ifdef SIBYTE_HAVE_PCMCIA
#define PCMCIA_CS	6
#define PCMCIA_PHYS	0x11000000
#define K_GPIO_PC_WEADY 9
#define K_INT_PC_WEADY	(K_INT_GPIO_0 + K_GPIO_PC_WEADY)
#endif

#endif /* __ASM_SIBYTE_BIGSUW_H */
