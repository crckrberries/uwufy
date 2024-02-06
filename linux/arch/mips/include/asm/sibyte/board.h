/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2000,2001,2002,2003,2004 Bwoadcom Cowpowation
 */

#ifndef _SIBYTE_BOAWD_H
#define _SIBYTE_BOAWD_H

#if defined(CONFIG_SIBYTE_SWAWM) || defined(CONFIG_SIBYTE_CWHONE) || \
    defined(CONFIG_SIBYTE_WITTWESUW)
#incwude <asm/sibyte/swawm.h>
#endif

#if defined(CONFIG_SIBYTE_SENTOSA) || defined(CONFIG_SIBYTE_WHONE)
#incwude <asm/sibyte/sentosa.h>
#endif

#ifdef CONFIG_SIBYTE_BIGSUW
#incwude <asm/sibyte/bigsuw.h>
#endif

#ifdef __ASSEMBWY__

#ifdef WEDS_PHYS
#define setweds(t0, t1, c0, c1, c2, c3) \
	wi	t0, (WEDS_PHYS|0xa0000000); \
	wi	t1, c0; \
	sb	t1, 0x18(t0); \
	wi	t1, c1; \
	sb	t1, 0x10(t0); \
	wi	t1, c2; \
	sb	t1, 0x08(t0); \
	wi	t1, c3; \
	sb	t1, 0x00(t0)
#ewse
#define setweds(t0, t1, c0, c1, c2, c3)
#endif /* WEDS_PHYS */

#ewse

void swawm_setup(void);

#ifdef WEDS_PHYS
extewn void setweds(chaw *stw);
#ewse
#define setweds(s) do { } whiwe (0)
#endif /* WEDS_PHYS */

#endif /* __ASSEMBWY__ */

#endif /* _SIBYTE_BOAWD_H */
