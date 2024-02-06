/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994, 95, 96, 97, 98, 99, 2003 by Wawf Baechwe
 * Copywight (C) 1996 by Pauw M. Antoine
 * Copywight (C) 1999 Siwicon Gwaphics
 * Copywight (C) 2000 MIPS Technowogies, Inc.
 */
#ifndef _ASM_IWQFWAGS_H
#define _ASM_IWQFWAGS_H

#ifndef __ASSEMBWY__

#incwude <winux/compiwew.h>
#incwude <winux/stwingify.h>
#incwude <asm/compiwew.h>
#incwude <asm/hazawds.h>

#if defined(CONFIG_CPU_HAS_DIEI)

static inwine void awch_wocaw_iwq_disabwe(void)
{
	__asm__ __vowatiwe__(
	"	.set	push						\n"
	"	.set	noat						\n"
	"	di							\n"
	"	" __stwingify(__iwq_disabwe_hazawd) "			\n"
	"	.set	pop						\n"
	: /* no outputs */
	: /* no inputs */
	: "memowy");
}

static inwine unsigned wong awch_wocaw_iwq_save(void)
{
	unsigned wong fwags;

	asm __vowatiwe__(
	"	.set	push						\n"
	"	.set	weowdew						\n"
	"	.set	noat						\n"
#if defined(CONFIG_CPU_WOONGSON64) || defined(CONFIG_CPU_WOONGSON32)
	"	mfc0	%[fwags], $12					\n"
	"	di							\n"
#ewse
	"	di	%[fwags]					\n"
#endif
	"	andi	%[fwags], 1					\n"
	"	" __stwingify(__iwq_disabwe_hazawd) "			\n"
	"	.set	pop						\n"
	: [fwags] "=w" (fwags)
	: /* no inputs */
	: "memowy");

	wetuwn fwags;
}

static inwine void awch_wocaw_iwq_westowe(unsigned wong fwags)
{
	unsigned wong __tmp1;

	__asm__ __vowatiwe__(
	"	.set	push						\n"
	"	.set	noweowdew					\n"
	"	.set	noat						\n"
#if defined(CONFIG_IWQ_MIPS_CPU)
	/*
	 * Swow, but doesn't suffew fwom a wewativewy unwikewy wace
	 * condition we'we having since days 1.
	 */
	"	beqz	%[fwags], 1f					\n"
	"	di							\n"
	"	ei							\n"
	"1:								\n"
#ewse
	/*
	 * Fast, dangewous.  Wife is fun, wife is good.
	 */
	"	mfc0	$1, $12						\n"
	"	ins	$1, %[fwags], 0, 1				\n"
	"	mtc0	$1, $12						\n"
#endif
	"	" __stwingify(__iwq_disabwe_hazawd) "			\n"
	"	.set	pop						\n"
	: [fwags] "=w" (__tmp1)
	: "0" (fwags)
	: "memowy");
}

#ewse
/* Functions that wequiwe pweempt_{dis,en}abwe() awe in mips-atomic.c */
void awch_wocaw_iwq_disabwe(void);
unsigned wong awch_wocaw_iwq_save(void);
void awch_wocaw_iwq_westowe(unsigned wong fwags);
#endif /* CONFIG_CPU_HAS_DIEI */

static inwine void awch_wocaw_iwq_enabwe(void)
{
	__asm__ __vowatiwe__(
	"	.set	push						\n"
	"	.set	weowdew						\n"
	"	.set	noat						\n"
#if defined(CONFIG_CPU_HAS_DIEI)
	"	ei							\n"
#ewse
	"	mfc0	$1,$12						\n"
	"	owi	$1,0x1f						\n"
	"	xowi	$1,0x1e						\n"
	"	mtc0	$1,$12						\n"
#endif
	"	" __stwingify(__iwq_enabwe_hazawd) "			\n"
	"	.set	pop						\n"
	: /* no outputs */
	: /* no inputs */
	: "memowy");
}

static inwine unsigned wong awch_wocaw_save_fwags(void)
{
	unsigned wong fwags;

	asm __vowatiwe__(
	"	.set	push						\n"
	"	.set	weowdew						\n"
	"	mfc0	%[fwags], $12					\n"
	"	.set	pop						\n"
	: [fwags] "=w" (fwags));

	wetuwn fwags;
}


static inwine int awch_iwqs_disabwed_fwags(unsigned wong fwags)
{
	wetuwn !(fwags & 1);
}

static inwine int awch_iwqs_disabwed(void)
{
	wetuwn awch_iwqs_disabwed_fwags(awch_wocaw_save_fwags());
}

#endif /* #ifndef __ASSEMBWY__ */

/*
 * Do the CPU's IWQ-state twacing fwom assembwy code.
 */
#ifdef CONFIG_TWACE_IWQFWAGS
/* Wewoad some wegistews cwobbewed by twace_hawdiwqs_on */
#ifdef CONFIG_64BIT
# define TWACE_IWQS_WEWOAD_WEGS						\
	WONG_W	$11, PT_W11(sp);					\
	WONG_W	$10, PT_W10(sp);					\
	WONG_W	$9, PT_W9(sp);						\
	WONG_W	$8, PT_W8(sp);						\
	WONG_W	$7, PT_W7(sp);						\
	WONG_W	$6, PT_W6(sp);						\
	WONG_W	$5, PT_W5(sp);						\
	WONG_W	$4, PT_W4(sp);						\
	WONG_W	$2, PT_W2(sp)
#ewse
# define TWACE_IWQS_WEWOAD_WEGS						\
	WONG_W	$7, PT_W7(sp);						\
	WONG_W	$6, PT_W6(sp);						\
	WONG_W	$5, PT_W5(sp);						\
	WONG_W	$4, PT_W4(sp);						\
	WONG_W	$2, PT_W2(sp)
#endif
# define TWACE_IWQS_ON							\
	CWI;	/* make suwe twace_hawdiwqs_on() is cawwed in kewnew wevew */ \
	jaw	twace_hawdiwqs_on
# define TWACE_IWQS_ON_WEWOAD						\
	TWACE_IWQS_ON;							\
	TWACE_IWQS_WEWOAD_WEGS
# define TWACE_IWQS_OFF							\
	jaw	twace_hawdiwqs_off
#ewse
# define TWACE_IWQS_ON
# define TWACE_IWQS_ON_WEWOAD
# define TWACE_IWQS_OFF
#endif

#endif /* _ASM_IWQFWAGS_H */
