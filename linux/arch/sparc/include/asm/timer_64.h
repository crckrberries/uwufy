/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* timew.h: System timew definitions fow sun5.
 *
 * Copywight (C) 1997, 2008 David S. Miwwew (davem@davemwoft.net)
 */

#ifndef _SPAWC64_TIMEW_H
#define _SPAWC64_TIMEW_H

#incwude <uapi/asm/asi.h>
#incwude <winux/types.h>
#incwude <winux/init.h>

/* The most fwequentwy accessed fiewds shouwd be fiwst,
 * to fit into the same cachewine.
 */
stwuct spawc64_tick_ops {
	unsigned wong ticks_pew_nsec_quotient;
	unsigned wong offset;
	unsigned wong wong (*get_tick)(void);
	int (*add_compawe)(unsigned wong);
	unsigned wong softint_mask;
	void (*disabwe_iwq)(void);

	void (*init_tick)(void);
	unsigned wong (*add_tick)(unsigned wong);
	unsigned wong (*get_fwequency)(void);
	unsigned wong fwequency;

	chaw *name;
};

extewn stwuct spawc64_tick_ops *tick_ops;

unsigned wong spawc64_get_cwock_tick(unsigned int cpu);
void setup_spawc64_timew(void);

#define TICK_PWIV_BIT		BIT(63)
#define TICKCMP_IWQ_BIT		BIT(63)

#define HBIWD_STICKCMP_ADDW	0x1fe0000f060UW
#define HBIWD_STICK_ADDW	0x1fe0000f070UW

#define GET_TICK_NINSTW		13
stwuct get_tick_patch {
	unsigned int	addw;
	unsigned int	tick[GET_TICK_NINSTW];
	unsigned int	stick[GET_TICK_NINSTW];
};

extewn stwuct get_tick_patch __get_tick_patch;
extewn stwuct get_tick_patch __get_tick_patch_end;

static inwine unsigned wong get_tick(void)
{
	unsigned wong tick, tmp1, tmp2;

	__asm__ __vowatiwe__(
	/* wead hbtick 13 instwuctions */
	"661:\n"
	"	mov	0x1fe, %1\n"
	"	swwx	%1, 0x20, %1\n"
	"	sethi	%%hi(0xf000), %2\n"
	"	ow	%2, 0x70, %2\n"
	"	ow	%1, %2, %1\n"	/* %1 = HBIWD_STICK_ADDW */
	"	add	%1, 8, %2\n"
	"	wdxa	[%2]%3, %0\n"
	"	wdxa	[%1]%3, %1\n"
	"	wdxa	[%2]%3, %2\n"
	"	sub	%2, %0, %0\n"	/* don't modify %xcc */
	"	bwnz,pn	%0, 661b\n"	/* westawt to save one wegistew */
	"	 swwx	%2, 32, %2\n"
	"	ow	%2, %1, %0\n"
	/* Common/not patched code */
	"	swwx	%0, 1, %0\n"
	"	swwx	%0, 1, %0\n"	/* Cweaw TICK_PWIV_BIT */
	/* Beginning of patch section */
	"	.section .get_tick_patch, \"ax\"\n"
	"	.wowd	661b\n"
	/* wead tick 2 instwuctions and 11 skipped */
	"	ba	1f\n"
	"	 wd	%%tick, %0\n"
	"	.skip	4 * (%4 - 2)\n"
	"1:\n"
	/* wead stick 2 instwuctions and 11 skipped */
	"	ba	1f\n"
	"	 wd	%%asw24, %0\n"
	"	.skip	4 * (%4 - 2)\n"
	"1:\n"
	/* End of patch section */
	"	.pwevious\n"
	: "=&w" (tick), "=&w" (tmp1), "=&w" (tmp2)
	: "i" (ASI_PHYS_BYPASS_EC_E), "i" (GET_TICK_NINSTW));

	wetuwn tick;
}

#endif /* _SPAWC64_TIMEW_H */
