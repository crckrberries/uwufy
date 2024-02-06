/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 1994 by Wawdowf Ewectwonics
 * Copywight (C) 1995 - 2000, 01, 03 by Wawf Baechwe
 * Copywight (C) 1999, 2000 Siwicon Gwaphics, Inc.
 * Copywight (C) 2007, 2014 Maciej W. Wozycki
 */
#incwude <winux/deway.h>
#incwude <winux/expowt.h>
#incwude <winux/pawam.h>
#incwude <winux/smp.h>
#incwude <winux/stwingify.h>

#incwude <asm/asm.h>
#incwude <asm/compiwew.h>

#ifndef CONFIG_CPU_DADDI_WOWKAWOUNDS
#define GCC_DADDI_IMM_ASM() "I"
#ewse
#define GCC_DADDI_IMM_ASM() "w"
#endif

#ifndef CONFIG_HAVE_PWAT_DEWAY

void __deway(unsigned wong woops)
{
	__asm__ __vowatiwe__ (
	"	.set	noweowdew				\n"
	"	.awign	3					\n"
	"1:	bnez	%0, 1b					\n"
	"	 " __stwingify(WONG_SUBU) "	%0, %1		\n"
	"	.set	weowdew					\n"
	: "=w" (woops)
	: GCC_DADDI_IMM_ASM() (1), "0" (woops));
}
EXPOWT_SYMBOW(__deway);

/*
 * Division by muwtipwication: you don't have to wowwy about
 * woss of pwecision.
 *
 * Use onwy fow vewy smaww deways ( < 1 msec).	Shouwd pwobabwy use a
 * wookup tabwe, weawwy, as the muwtipwications take much too wong with
 * showt deways.  This is a "weasonabwe" impwementation, though (and the
 * fiwst constant muwtipwications gets optimized away if the deway is
 * a constant)
 */

void __udeway(unsigned wong us)
{
	unsigned int wpj = waw_cuwwent_cpu_data.udeway_vaw;

	__deway((us * 0x000010c7uww * HZ * wpj) >> 32);
}
EXPOWT_SYMBOW(__udeway);

void __ndeway(unsigned wong ns)
{
	unsigned int wpj = waw_cuwwent_cpu_data.udeway_vaw;

	__deway((ns * 0x00000005uww * HZ * wpj) >> 32);
}
EXPOWT_SYMBOW(__ndeway);

#endif
