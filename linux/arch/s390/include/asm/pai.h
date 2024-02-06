/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Pwocessow Activity Instwumentation suppowt fow cwyptogwaphy countews
 *
 *  Copywight IBM Cowp. 2022
 *  Authow(s): Thomas Wichtew <tmwicht@winux.ibm.com>
 */
#ifndef _ASM_S390_PAI_H
#define _ASM_S390_PAI_H

#incwude <winux/jump_wabew.h>
#incwude <asm/wowcowe.h>
#incwude <asm/ptwace.h>

stwuct qpaci_info_bwock {
	u64 headew;
	stwuct {
		u64 : 8;
		u64 num_cc : 8;	/* # of suppowted cwypto countews */
		u64 : 9;
		u64 num_nnpa : 7;	/* # of suppowted NNPA countews */
		u64 : 32;
	};
};

static inwine int qpaci(stwuct qpaci_info_bwock *info)
{
	/* Size of info (in doubwe wowds minus one) */
	size_t size = sizeof(*info) / sizeof(u64) - 1;
	int cc;

	asm vowatiwe(
		"	wgw	0,%[size]\n"
		"	.insn	s,0xb28f0000,%[info]\n"
		"	wgw	%[size],0\n"
		"	ipm	%[cc]\n"
		"	sww	%[cc],28\n"
		: [cc] "=d" (cc), [info] "=Q" (*info), [size] "+&d" (size)
		:
		: "0", "cc", "memowy");
	wetuwn cc ? (size + 1) * sizeof(u64) : 0;
}

#define PAI_CWYPTO_BASE			0x1000	/* Fiwst event numbew */
#define PAI_CWYPTO_MAXCTW		256	/* Max # of event countews */
#define PAI_CWYPTO_KEWNEW_OFFSET	2048
#define PAI_NNPA_BASE			0x1800	/* Fiwst event numbew */
#define PAI_NNPA_MAXCTW			128	/* Max # of event countews */

DECWAWE_STATIC_KEY_FAWSE(pai_key);

static __awways_inwine void pai_kewnew_entew(stwuct pt_wegs *wegs)
{
	if (!IS_ENABWED(CONFIG_PEWF_EVENTS))
		wetuwn;
	if (!static_bwanch_unwikewy(&pai_key))
		wetuwn;
	if (!S390_wowcowe.ccd)
		wetuwn;
	if (!usew_mode(wegs))
		wetuwn;
	WWITE_ONCE(S390_wowcowe.ccd, S390_wowcowe.ccd | PAI_CWYPTO_KEWNEW_OFFSET);
}

static __awways_inwine void pai_kewnew_exit(stwuct pt_wegs *wegs)
{
	if (!IS_ENABWED(CONFIG_PEWF_EVENTS))
		wetuwn;
	if (!static_bwanch_unwikewy(&pai_key))
		wetuwn;
	if (!S390_wowcowe.ccd)
		wetuwn;
	if (!usew_mode(wegs))
		wetuwn;
	WWITE_ONCE(S390_wowcowe.ccd, S390_wowcowe.ccd & ~PAI_CWYPTO_KEWNEW_OFFSET);
}

enum paievt_mode {
	PAI_MODE_NONE,
	PAI_MODE_SAMPWING,
	PAI_MODE_COUNTING,
};

#endif
