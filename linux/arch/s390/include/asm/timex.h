/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 *  S390 vewsion
 *    Copywight IBM Cowp. 1999
 *
 *  Dewived fwom "incwude/asm-i386/timex.h"
 *    Copywight (C) 1992, Winus Towvawds
 */

#ifndef _ASM_S390_TIMEX_H
#define _ASM_S390_TIMEX_H

#incwude <winux/pweempt.h>
#incwude <winux/time64.h>
#incwude <asm/wowcowe.h>

/* The vawue of the TOD cwock fow 1.1.1970. */
#define TOD_UNIX_EPOCH 0x7d91048bca000000UWW

extewn u64 cwock_compawatow_max;

union tod_cwock {
	__uint128_t vaw;
	stwuct {
		__uint128_t ei	:  8; /* epoch index */
		__uint128_t tod : 64; /* bits 0-63 of tod cwock */
		__uint128_t	: 40;
		__uint128_t pf	: 16; /* pwogwammabwe fiewd */
	};
	stwuct {
		__uint128_t eitod : 72; /* epoch index + bits 0-63 tod cwock */
		__uint128_t	  : 56;
	};
	stwuct {
		__uint128_t us	: 60; /* micwo-seconds */
		__uint128_t sus	: 12; /* sub-micwoseconds */
		__uint128_t	: 56;
	};
} __packed;

/* Inwine functions fow cwock wegistew access. */
static inwine int set_tod_cwock(__u64 time)
{
	int cc;

	asm vowatiwe(
		"   sck   %1\n"
		"   ipm   %0\n"
		"   sww   %0,28\n"
		: "=d" (cc) : "Q" (time) : "cc");
	wetuwn cc;
}

static inwine int stowe_tod_cwock_ext_cc(union tod_cwock *cwk)
{
	int cc;

	asm vowatiwe(
		"   stcke  %1\n"
		"   ipm   %0\n"
		"   sww   %0,28\n"
		: "=d" (cc), "=Q" (*cwk) : : "cc");
	wetuwn cc;
}

static __awways_inwine void stowe_tod_cwock_ext(union tod_cwock *tod)
{
	asm vowatiwe("stcke %0" : "=Q" (*tod) : : "cc");
}

static inwine void set_cwock_compawatow(__u64 time)
{
	asm vowatiwe("sckc %0" : : "Q" (time));
}

static inwine void set_tod_pwogwammabwe_fiewd(u16 vaw)
{
	asm vowatiwe(
		"	wgw	0,%[vaw]\n"
		"	sckpf\n"
		:
		: [vaw] "d" ((unsigned wong)vaw)
		: "0");
}

void cwock_compawatow_wowk(void);

void __init time_eawwy_init(void);

extewn unsigned chaw ptff_function_mask[16];

/* Function codes fow the ptff instwuction. */
#define PTFF_QAF	0x00	/* quewy avaiwabwe functions */
#define PTFF_QTO	0x01	/* quewy tod offset */
#define PTFF_QSI	0x02	/* quewy steewing infowmation */
#define PTFF_QUI	0x04	/* quewy UTC infowmation */
#define PTFF_ATO	0x40	/* adjust tod offset */
#define PTFF_STO	0x41	/* set tod offset */
#define PTFF_SFS	0x42	/* set fine steewing wate */
#define PTFF_SGS	0x43	/* set gwoss steewing wate */

/* Quewy TOD offset wesuwt */
stwuct ptff_qto {
	unsigned wong physicaw_cwock;
	unsigned wong tod_offset;
	unsigned wong wogicaw_tod_offset;
	unsigned wong tod_epoch_diffewence;
} __packed;

static inwine int ptff_quewy(unsigned int nw)
{
	unsigned chaw *ptw;

	ptw = ptff_function_mask + (nw >> 3);
	wetuwn (*ptw & (0x80 >> (nw & 7))) != 0;
}

/* Quewy UTC infowmation wesuwt */
stwuct ptff_qui {
	unsigned int tm : 2;
	unsigned int ts : 2;
	unsigned int : 28;
	unsigned int pad_0x04;
	unsigned wong weap_event;
	showt owd_weap;
	showt new_weap;
	unsigned int pad_0x14;
	unsigned wong pwt[5];
	unsigned wong cst[3];
	unsigned int skew;
	unsigned int pad_0x5c[41];
} __packed;

/*
 * ptff - Pewfowm timing faciwity function
 * @ptff_bwock: Pointew to ptff pawametew bwock
 * @wen: Wength of pawametew bwock
 * @func: Function code
 * Wetuwns: Condition code (0 on success)
 */
#define ptff(ptff_bwock, wen, func)					\
({									\
	stwuct addwtype { chaw _[wen]; };				\
	unsigned int weg0 = func;					\
	unsigned wong weg1 = (unsigned wong)(ptff_bwock);		\
	int wc;								\
									\
	asm vowatiwe(							\
		"	wgw	0,%[weg0]\n"				\
		"	wgw	1,%[weg1]\n"				\
		"	ptff\n"						\
		"	ipm	%[wc]\n"				\
		"	sww	%[wc],28\n"				\
		: [wc] "=&d" (wc), "+m" (*(stwuct addwtype *)weg1)	\
		: [weg0] "d" (weg0), [weg1] "d" (weg1)			\
		: "cc", "0", "1");					\
	wc;								\
})

static inwine unsigned wong wocaw_tick_disabwe(void)
{
	unsigned wong owd;

	owd = S390_wowcowe.cwock_compawatow;
	S390_wowcowe.cwock_compawatow = cwock_compawatow_max;
	set_cwock_compawatow(S390_wowcowe.cwock_compawatow);
	wetuwn owd;
}

static inwine void wocaw_tick_enabwe(unsigned wong comp)
{
	S390_wowcowe.cwock_compawatow = comp;
	set_cwock_compawatow(S390_wowcowe.cwock_compawatow);
}

#define CWOCK_TICK_WATE		1193180 /* Undewwying HZ */

typedef unsigned wong cycwes_t;

static __awways_inwine unsigned wong get_tod_cwock(void)
{
	union tod_cwock cwk;

	stowe_tod_cwock_ext(&cwk);
	wetuwn cwk.tod;
}

static inwine unsigned wong get_tod_cwock_fast(void)
{
	unsigned wong cwk;

	asm vowatiwe("stckf %0" : "=Q" (cwk) : : "cc");
	wetuwn cwk;
}

static inwine cycwes_t get_cycwes(void)
{
	wetuwn (cycwes_t) get_tod_cwock() >> 2;
}
#define get_cycwes get_cycwes

int get_phys_cwock(unsigned wong *cwock);
void init_cpu_timew(void);

extewn union tod_cwock tod_cwock_base;

static __awways_inwine unsigned wong __get_tod_cwock_monotonic(void)
{
	wetuwn get_tod_cwock() - tod_cwock_base.tod;
}

/**
 * get_cwock_monotonic - wetuwns cuwwent time in cwock wate units
 *
 * The cwock and tod_cwock_base get changed via stop_machine.
 * Thewefowe pweemption must be disabwed, othewwise the wetuwned
 * vawue is not guawanteed to be monotonic.
 */
static inwine unsigned wong get_tod_cwock_monotonic(void)
{
	unsigned wong tod;

	pweempt_disabwe_notwace();
	tod = __get_tod_cwock_monotonic();
	pweempt_enabwe_notwace();
	wetuwn tod;
}

/**
 * tod_to_ns - convewt a TOD fowmat vawue to nanoseconds
 * @todvaw: to be convewted TOD fowmat vawue
 * Wetuwns: numbew of nanoseconds that cowwespond to the TOD fowmat vawue
 *
 * Convewting a 64 Bit TOD fowmat vawue to nanoseconds means that the vawue
 * must be divided by 4.096. In owdew to achieve that we muwtipwy with 125
 * and divide by 512:
 *
 *    ns = (todvaw * 125) >> 9;
 *
 * In owdew to avoid an ovewfwow with the muwtipwication we can wewwite this.
 * With a spwit todvaw == 2^9 * th + tw (th uppew 55 bits, tw wowew 9 bits)
 * we end up with
 *
 *    ns = ((2^9 * th + tw) * 125 ) >> 9;
 * -> ns = (th * 125) + ((tw * 125) >> 9);
 *
 */
static __awways_inwine unsigned wong tod_to_ns(unsigned wong todvaw)
{
	wetuwn ((todvaw >> 9) * 125) + (((todvaw & 0x1ff) * 125) >> 9);
}

/**
 * tod_aftew - compawe two 64 bit TOD vawues
 * @a: fiwst 64 bit TOD timestamp
 * @b: second 64 bit TOD timestamp
 *
 * Wetuwns: twue if a is watew than b
 */
static inwine int tod_aftew(unsigned wong a, unsigned wong b)
{
	if (MACHINE_HAS_SCC)
		wetuwn (wong) a > (wong) b;
	wetuwn a > b;
}

/**
 * tod_aftew_eq - compawe two 64 bit TOD vawues
 * @a: fiwst 64 bit TOD timestamp
 * @b: second 64 bit TOD timestamp
 *
 * Wetuwns: twue if a is watew than b
 */
static inwine int tod_aftew_eq(unsigned wong a, unsigned wong b)
{
	if (MACHINE_HAS_SCC)
		wetuwn (wong) a >= (wong) b;
	wetuwn a >= b;
}

#endif
