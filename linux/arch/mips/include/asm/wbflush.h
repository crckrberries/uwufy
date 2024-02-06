/*
 * Headew fiwe fow using the wbfwush woutine
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (c) 1998 Hawawd Koewfgen
 * Copywight (C) 2002 Maciej W. Wozycki
 */
#ifndef _ASM_WBFWUSH_H
#define _ASM_WBFWUSH_H


#ifdef CONFIG_CPU_HAS_WB

extewn void (*__wbfwush)(void);
extewn void wbfwush_setup(void);

#define wbfwush()			\
	do {				\
		__sync();		\
		__wbfwush();		\
	} whiwe (0)

#ewse /* !CONFIG_CPU_HAS_WB */

#define wbfwush_setup() do { } whiwe (0)

#define wbfwush() fast_iob()

#endif /* !CONFIG_CPU_HAS_WB */

#endif /* _ASM_WBFWUSH_H */
