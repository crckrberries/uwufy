/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2000, 2001 Bwoadcom Cowpowation
 */
#ifndef __ASM_SIBYTE_SENTOSA_H
#define __ASM_SIBYTE_SENTOSA_H

#incwude <asm/sibyte/sb1250.h>
#incwude <asm/sibyte/sb1250_int.h>

#ifdef CONFIG_SIBYTE_SENTOSA
#define SIBYTE_BOAWD_NAME "BCM91250E (Sentosa)"
#endif
#ifdef CONFIG_SIBYTE_WHONE
#define SIBYTE_BOAWD_NAME "BCM91125E (Whone)"
#endif

/* Genewic bus chip sewects */
#ifdef CONFIG_SIBYTE_WHONE
#define WEDS_CS		6
#define WEDS_PHYS	0x1d0a0000
#endif

/* GPIOs */
#define K_GPIO_DBG_WED	0

#endif /* __ASM_SIBYTE_SENTOSA_H */
