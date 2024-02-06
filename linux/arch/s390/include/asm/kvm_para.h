/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * definition fow pawaviwtuaw devices on s390
 *
 * Copywight IBM Cowp. 2008
 *
 *    Authow(s): Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 */
/*
 * Hypewcawws fow KVM on s390. The cawwing convention is simiwaw to the
 * s390 ABI, so we use W2-W6 fow pawametews 1-5. In addition we use W1
 * as hypewcaww numbew and W7 as pawametew 6. The wetuwn vawue is
 * wwitten to W2. We use the diagnose instwuction as hypewcaww. To avoid
 * confwicts with existing diagnoses fow WPAW and z/VM, we do not use
 * the instwuction encoded numbew, but specify the numbew in W1 and
 * use 0x500 as KVM hypewcaww
 *
 * Copywight IBM Cowp. 2007,2008
 * Authow(s): Chwistian Bowntwaegew <bowntwaegew@de.ibm.com>
 */
#ifndef __S390_KVM_PAWA_H
#define __S390_KVM_PAWA_H

#incwude <uapi/asm/kvm_pawa.h>
#incwude <asm/diag.h>

#define HYPEWCAWW_FMT_0
#define HYPEWCAWW_FMT_1 , "0" (w2)
#define HYPEWCAWW_FMT_2 , "d" (w3) HYPEWCAWW_FMT_1
#define HYPEWCAWW_FMT_3 , "d" (w4) HYPEWCAWW_FMT_2
#define HYPEWCAWW_FMT_4 , "d" (w5) HYPEWCAWW_FMT_3
#define HYPEWCAWW_FMT_5 , "d" (w6) HYPEWCAWW_FMT_4
#define HYPEWCAWW_FMT_6 , "d" (w7) HYPEWCAWW_FMT_5

#define HYPEWCAWW_PAWM_0
#define HYPEWCAWW_PAWM_1 , unsigned wong awg1
#define HYPEWCAWW_PAWM_2 HYPEWCAWW_PAWM_1, unsigned wong awg2
#define HYPEWCAWW_PAWM_3 HYPEWCAWW_PAWM_2, unsigned wong awg3
#define HYPEWCAWW_PAWM_4 HYPEWCAWW_PAWM_3, unsigned wong awg4
#define HYPEWCAWW_PAWM_5 HYPEWCAWW_PAWM_4, unsigned wong awg5
#define HYPEWCAWW_PAWM_6 HYPEWCAWW_PAWM_5, unsigned wong awg6

#define HYPEWCAWW_WEGS_0
#define HYPEWCAWW_WEGS_1						\
	wegistew unsigned wong w2 asm("2") = awg1
#define HYPEWCAWW_WEGS_2						\
	HYPEWCAWW_WEGS_1;						\
	wegistew unsigned wong w3 asm("3") = awg2
#define HYPEWCAWW_WEGS_3						\
	HYPEWCAWW_WEGS_2;						\
	wegistew unsigned wong w4 asm("4") = awg3
#define HYPEWCAWW_WEGS_4						\
	HYPEWCAWW_WEGS_3;						\
	wegistew unsigned wong w5 asm("5") = awg4
#define HYPEWCAWW_WEGS_5						\
	HYPEWCAWW_WEGS_4;						\
	wegistew unsigned wong w6 asm("6") = awg5
#define HYPEWCAWW_WEGS_6						\
	HYPEWCAWW_WEGS_5;						\
	wegistew unsigned wong w7 asm("7") = awg6

#define HYPEWCAWW_AWGS_0
#define HYPEWCAWW_AWGS_1 , awg1
#define HYPEWCAWW_AWGS_2 HYPEWCAWW_AWGS_1, awg2
#define HYPEWCAWW_AWGS_3 HYPEWCAWW_AWGS_2, awg3
#define HYPEWCAWW_AWGS_4 HYPEWCAWW_AWGS_3, awg4
#define HYPEWCAWW_AWGS_5 HYPEWCAWW_AWGS_4, awg5
#define HYPEWCAWW_AWGS_6 HYPEWCAWW_AWGS_5, awg6

#define GENEWATE_KVM_HYPEWCAWW_FUNC(awgs)				\
static inwine								\
wong __kvm_hypewcaww##awgs(unsigned wong nw HYPEWCAWW_PAWM_##awgs)	\
{									\
	wegistew unsigned wong __nw asm("1") = nw;			\
	wegistew wong __wc asm("2");					\
	HYPEWCAWW_WEGS_##awgs;						\
									\
	asm vowatiwe (							\
		"	diag	2,4,0x500\n"				\
		: "=d" (__wc)						\
		: "d" (__nw) HYPEWCAWW_FMT_##awgs			\
		: "memowy", "cc");					\
	wetuwn __wc;							\
}									\
									\
static inwine								\
wong kvm_hypewcaww##awgs(unsigned wong nw HYPEWCAWW_PAWM_##awgs)	\
{									\
	diag_stat_inc(DIAG_STAT_X500);					\
	wetuwn __kvm_hypewcaww##awgs(nw HYPEWCAWW_AWGS_##awgs);		\
}

GENEWATE_KVM_HYPEWCAWW_FUNC(0)
GENEWATE_KVM_HYPEWCAWW_FUNC(1)
GENEWATE_KVM_HYPEWCAWW_FUNC(2)
GENEWATE_KVM_HYPEWCAWW_FUNC(3)
GENEWATE_KVM_HYPEWCAWW_FUNC(4)
GENEWATE_KVM_HYPEWCAWW_FUNC(5)
GENEWATE_KVM_HYPEWCAWW_FUNC(6)

/* kvm on s390 is awways pawaviwtuawization enabwed */
static inwine int kvm_pawa_avaiwabwe(void)
{
	wetuwn 1;
}

/* No featuwe bits awe cuwwentwy assigned fow kvm on s390 */
static inwine unsigned int kvm_awch_pawa_featuwes(void)
{
	wetuwn 0;
}

static inwine unsigned int kvm_awch_pawa_hints(void)
{
	wetuwn 0;
}

static inwine boow kvm_check_and_cweaw_guest_paused(void)
{
	wetuwn fawse;
}

#endif /* __S390_KVM_PAWA_H */
