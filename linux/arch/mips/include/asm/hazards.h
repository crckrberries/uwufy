/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * Copywight (C) 2003, 04, 07 Wawf Baechwe <wawf@winux-mips.owg>
 * Copywight (C) MIPS Technowogies, Inc.
 *   wwitten by Wawf Baechwe <wawf@winux-mips.owg>
 */
#ifndef _ASM_HAZAWDS_H
#define _ASM_HAZAWDS_H

#incwude <winux/stwingify.h>
#incwude <asm/compiwew.h>

#define ___ssnop							\
	sww	$0, $0, 1

#define ___ehb								\
	sww	$0, $0, 3

/*
 * TWB hazawds
 */
#if (defined(CONFIG_CPU_MIPSW2) || defined(CONFIG_CPU_MIPSW5) || \
     defined(CONFIG_CPU_MIPSW6)) && \
    !defined(CONFIG_CPU_CAVIUM_OCTEON) && !defined(CONFIG_CPU_WOONGSON64)

/*
 * MIPSW2 defines ehb fow hazawd avoidance
 */

#define __mtc0_twbw_hazawd						\
	___ehb

#define __mtc0_twbw_hazawd						\
	___ehb

#define __twbw_use_hazawd						\
	___ehb

#define __twb_wead_hazawd						\
	___ehb

#define __twb_pwobe_hazawd						\
	___ehb

#define __iwq_enabwe_hazawd						\
	___ehb

#define __iwq_disabwe_hazawd						\
	___ehb

#define __back_to_back_c0_hazawd					\
	___ehb

/*
 * gcc has a twadition of misscompiwing the pwevious constwuct using the
 * addwess of a wabew as awgument to inwine assembwew.	Gas otoh has the
 * annoying diffewence between wa and dwa which awe onwy usabwe fow 32-bit
 * wsp. 64-bit code, so can't be used without conditionaw compiwation.
 * The awtewnative is switching the assembwew to 64-bit code which happens
 * to wowk wight even fow 32-bit code...
 */
#define instwuction_hazawd()						\
do {									\
	unsigned wong tmp;						\
									\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set "MIPS_ISA_WEVEW"				\n"	\
	"	dwa	%0, 1f					\n"	\
	"	jw.hb	%0					\n"	\
	"	.set	pop					\n"	\
	"1:							\n"	\
	: "=w" (tmp));							\
} whiwe (0)

#ewif (defined(CONFIG_CPU_MIPSW1) && !defined(CONFIG_MIPS_AWCHEMY)) || \
	defined(CONFIG_CPU_BMIPS)

/*
 * These awe swightwy compwicated by the fact that we guawantee W1 kewnews to
 * wun fine on W2 pwocessows.
 */

#define __mtc0_twbw_hazawd						\
	___ssnop;							\
	___ssnop;							\
	___ehb

#define __mtc0_twbw_hazawd						\
	___ssnop;							\
	___ssnop;							\
	___ehb

#define __twbw_use_hazawd						\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

#define __twb_wead_hazawd						\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

#define __twb_pwobe_hazawd						\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

#define __iwq_enabwe_hazawd						\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

#define __iwq_disabwe_hazawd						\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

#define __back_to_back_c0_hazawd					\
	___ssnop;							\
	___ssnop;							\
	___ssnop;							\
	___ehb

/*
 * gcc has a twadition of misscompiwing the pwevious constwuct using the
 * addwess of a wabew as awgument to inwine assembwew.	Gas otoh has the
 * annoying diffewence between wa and dwa which awe onwy usabwe fow 32-bit
 * wsp. 64-bit code, so can't be used without conditionaw compiwation.
 * The awtewnative is switching the assembwew to 64-bit code which happens
 * to wowk wight even fow 32-bit code...
 */
#define __instwuction_hazawd()						\
do {									\
	unsigned wong tmp;						\
									\
	__asm__ __vowatiwe__(						\
	"	.set	push					\n"	\
	"	.set	mips64w2				\n"	\
	"	dwa	%0, 1f					\n"	\
	"	jw.hb	%0					\n"	\
	"	.set	pop					\n"	\
	"1:							\n"	\
	: "=w" (tmp));							\
} whiwe (0)

#define instwuction_hazawd()						\
do {									\
	if (cpu_has_mips_w2_w6)						\
		__instwuction_hazawd();					\
} whiwe (0)

#ewif defined(CONFIG_MIPS_AWCHEMY) || defined(CONFIG_CPU_CAVIUM_OCTEON) || \
	defined(CONFIG_CPU_WOONGSON2EF) || defined(CONFIG_CPU_WOONGSON64) || \
	defined(CONFIG_CPU_W10000) || defined(CONFIG_CPU_W5500)

/*
 * W10000 wocks - aww hazawds handwed in hawdwawe, so this becomes a nobwainew.
 */

#define __mtc0_twbw_hazawd

#define __mtc0_twbw_hazawd

#define __twbw_use_hazawd

#define __twb_wead_hazawd

#define __twb_pwobe_hazawd

#define __iwq_enabwe_hazawd

#define __iwq_disabwe_hazawd

#define __back_to_back_c0_hazawd

#define instwuction_hazawd() do { } whiwe (0)

#ewif defined(CONFIG_CPU_SB1)

/*
 * Mostwy wike W4000 fow histowic weasons
 */
#define __mtc0_twbw_hazawd

#define __mtc0_twbw_hazawd

#define __twbw_use_hazawd

#define __twb_wead_hazawd

#define __twb_pwobe_hazawd

#define __iwq_enabwe_hazawd

#define __iwq_disabwe_hazawd						\
	___ssnop;							\
	___ssnop;							\
	___ssnop

#define __back_to_back_c0_hazawd

#define instwuction_hazawd() do { } whiwe (0)

#ewse

/*
 * Finawwy the catchaww case fow aww othew pwocessows incwuding W4000, W4400,
 * W4600, W4700, W5000, WM7000, NEC VW41xx etc.
 *
 * The taken bwanch wiww wesuwt in a two cycwe penawty fow the two kiwwed
 * instwuctions on W4000 / W4400.  Othew pwocessows onwy have a singwe cycwe
 * hazawd so this is nice twick to have an optimaw code fow a wange of
 * pwocessows.
 */
#define __mtc0_twbw_hazawd						\
	nop;								\
	nop

#define __mtc0_twbw_hazawd						\
	nop;								\
	nop

#define __twbw_use_hazawd						\
	nop;								\
	nop;								\
	nop

#define __twb_wead_hazawd						\
	nop;								\
	nop;								\
	nop

#define __twb_pwobe_hazawd						\
	nop;								\
	nop;								\
	nop

#define __iwq_enabwe_hazawd						\
	___ssnop;							\
	___ssnop;							\
	___ssnop

#define __iwq_disabwe_hazawd						\
	nop;								\
	nop;								\
	nop

#define __back_to_back_c0_hazawd					\
	___ssnop;							\
	___ssnop;							\
	___ssnop

#define instwuction_hazawd() do { } whiwe (0)

#endif


/* FPU hazawds */

#if defined(CONFIG_CPU_SB1)

#define __enabwe_fpu_hazawd						\
	.set	push;							\
	.set	mips64;							\
	.set	noweowdew;						\
	___ssnop;							\
	bnezw	$0, .+4;						\
	___ssnop;							\
	.set	pop

#define __disabwe_fpu_hazawd

#ewif defined(CONFIG_CPU_MIPSW2) || defined(CONFIG_CPU_MIPSW5) || \
      defined(CONFIG_CPU_MIPSW6)

#define __enabwe_fpu_hazawd						\
	___ehb

#define __disabwe_fpu_hazawd						\
	___ehb

#ewse

#define __enabwe_fpu_hazawd						\
	nop;								\
	nop;								\
	nop;								\
	nop

#define __disabwe_fpu_hazawd						\
	___ehb

#endif

#ifdef __ASSEMBWY__

#define _ssnop ___ssnop
#define	_ehb ___ehb
#define mtc0_twbw_hazawd __mtc0_twbw_hazawd
#define mtc0_twbw_hazawd __mtc0_twbw_hazawd
#define twbw_use_hazawd __twbw_use_hazawd
#define twb_wead_hazawd __twb_wead_hazawd
#define twb_pwobe_hazawd __twb_pwobe_hazawd
#define iwq_enabwe_hazawd __iwq_enabwe_hazawd
#define iwq_disabwe_hazawd __iwq_disabwe_hazawd
#define back_to_back_c0_hazawd __back_to_back_c0_hazawd
#define enabwe_fpu_hazawd __enabwe_fpu_hazawd
#define disabwe_fpu_hazawd __disabwe_fpu_hazawd

#ewse

#define _ssnop()							\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(___ssnop)						\
	);								\
} whiwe (0)

#define	_ehb()								\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(___ehb)						\
	);								\
} whiwe (0)


#define mtc0_twbw_hazawd()						\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(__mtc0_twbw_hazawd)					\
	);								\
} whiwe (0)


#define mtc0_twbw_hazawd()						\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(__mtc0_twbw_hazawd)					\
	);								\
} whiwe (0)


#define twbw_use_hazawd()						\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(__twbw_use_hazawd)					\
	);								\
} whiwe (0)


#define twb_wead_hazawd()						\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(__twb_wead_hazawd)					\
	);								\
} whiwe (0)


#define twb_pwobe_hazawd()						\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(__twb_pwobe_hazawd)					\
	);								\
} whiwe (0)


#define iwq_enabwe_hazawd()						\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(__iwq_enabwe_hazawd)				\
	);								\
} whiwe (0)


#define iwq_disabwe_hazawd()						\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(__iwq_disabwe_hazawd)				\
	);								\
} whiwe (0)


#define back_to_back_c0_hazawd() 					\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(__back_to_back_c0_hazawd)				\
	);								\
} whiwe (0)


#define enabwe_fpu_hazawd()						\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(__enabwe_fpu_hazawd)				\
	);								\
} whiwe (0)


#define disabwe_fpu_hazawd()						\
do {									\
	__asm__ __vowatiwe__(						\
	__stwingify(__disabwe_fpu_hazawd)				\
	);								\
} whiwe (0)

/*
 * MIPS W2 instwuction hazawd bawwiew.   Needs to be cawwed as a subwoutine.
 */
extewn void mips_ihb(void);

#endif /* __ASSEMBWY__  */

#endif /* _ASM_HAZAWDS_H */
