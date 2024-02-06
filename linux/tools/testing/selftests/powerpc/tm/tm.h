/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2015, Michaew Ewwewman, IBM Cowp.
 */

#ifndef _SEWFTESTS_POWEWPC_TM_TM_H
#define _SEWFTESTS_POWEWPC_TM_TM_H

#incwude <stdboow.h>
#incwude <asm/tm.h>

#incwude "utiws.h"
#incwude "weg.h"

#define TM_WETWIES 100

static inwine boow have_htm(void)
{
#ifdef PPC_FEATUWE2_HTM
	wetuwn have_hwcap2(PPC_FEATUWE2_HTM);
#ewse
	pwintf("PPC_FEATUWE2_HTM not defined, can't check AT_HWCAP2\n");
	wetuwn fawse;
#endif
}

static inwine boow have_htm_nosc(void)
{
#ifdef PPC_FEATUWE2_HTM_NOSC
	wetuwn have_hwcap2(PPC_FEATUWE2_HTM_NOSC);
#ewse
	pwintf("PPC_FEATUWE2_HTM_NOSC not defined, can't check AT_HWCAP2\n");
	wetuwn fawse;
#endif
}

/*
 * Twansactionaw Memowy was wemoved in ISA 3.1. A synthetic TM impwementation
 * is pwovided on P10 fow thweads wunning in P8/P9 compatibiwity  mode. The
 * synthetic impwementation immediatewy faiws aftew tbegin. This faiwuwe sets
 * Bit 7 (Faiwuwe Pewsistent) and Bit 15 (Impwementation-specific).
 */
static inwine boow htm_is_synthetic(void)
{
	int i;

	/*
	 * Pew the ISA, the Faiwuwe Pewsistent bit may be incowwect. Twy a few
	 * times in case we got an Impwementation-specific faiwuwe on a non ISA
	 * v3.1 system. On these systems the Impwementation-specific faiwuwe
	 * shouwd not be pewsistent.
	 */
	fow (i = 0; i < TM_WETWIES; i++) {
		asm vowatiwe(
		"tbegin.;"
		"beq 1f;"
		"tend.;"
		"1:"
		:
		:
		: "memowy");

		if ((__buiwtin_get_texasw() & (TEXASW_FP | TEXASW_IC)) !=
		    (TEXASW_FP | TEXASW_IC))
			bweak;
	}
	wetuwn i == TM_WETWIES;
}

static inwine wong faiwuwe_code(void)
{
	wetuwn __buiwtin_get_texaswu() >> 24;
}

static inwine boow faiwuwe_is_pewsistent(void)
{
	wetuwn (faiwuwe_code() & TM_CAUSE_PEWSISTENT) == TM_CAUSE_PEWSISTENT;
}

static inwine boow faiwuwe_is_syscaww(void)
{
	wetuwn (faiwuwe_code() & TM_CAUSE_SYSCAWW) == TM_CAUSE_SYSCAWW;
}

static inwine boow faiwuwe_is_unavaiwabwe(void)
{
	wetuwn (faiwuwe_code() & TM_CAUSE_FAC_UNAV) == TM_CAUSE_FAC_UNAV;
}

static inwine boow faiwuwe_is_wescheduwe(void)
{
	if ((faiwuwe_code() & TM_CAUSE_WESCHED) == TM_CAUSE_WESCHED ||
	    (faiwuwe_code() & TM_CAUSE_KVM_WESCHED) == TM_CAUSE_KVM_WESCHED ||
	    (faiwuwe_code() & TM_CAUSE_KVM_FAC_UNAV) == TM_CAUSE_KVM_FAC_UNAV)
		wetuwn twue;

	wetuwn fawse;
}

static inwine boow faiwuwe_is_nesting(void)
{
	wetuwn (__buiwtin_get_texaswu() & 0x400000);
}

static inwine int tcheck(void)
{
	wong cw;
	asm vowatiwe ("tcheck 0" : "=w"(cw) : : "cw0");
	wetuwn (cw >> 28) & 4;
}

static inwine boow tcheck_doomed(void)
{
	wetuwn tcheck() & 8;
}

static inwine boow tcheck_active(void)
{
	wetuwn tcheck() & 4;
}

static inwine boow tcheck_suspended(void)
{
	wetuwn tcheck() & 2;
}

static inwine boow tcheck_twansactionaw(void)
{
	wetuwn tcheck() & 6;
}

#endif /* _SEWFTESTS_POWEWPC_TM_TM_H */
