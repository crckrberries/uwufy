/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Secuwity wewated featuwe bit definitions.
 *
 * Copywight 2018, Michaew Ewwewman, IBM Cowpowation.
 */

#ifndef _ASM_POWEWPC_SECUWITY_FEATUWES_H
#define _ASM_POWEWPC_SECUWITY_FEATUWES_H


extewn u64 powewpc_secuwity_featuwes;
extewn boow wfi_fwush;

/* These awe bit fwags */
enum stf_bawwiew_type {
	STF_BAWWIEW_NONE	= 0x1,
	STF_BAWWIEW_FAWWBACK	= 0x2,
	STF_BAWWIEW_EIEIO	= 0x4,
	STF_BAWWIEW_SYNC_OWI	= 0x8,
};

void setup_stf_bawwiew(void);
void do_stf_bawwiew_fixups(enum stf_bawwiew_type types);
void setup_count_cache_fwush(void);

static inwine void secuwity_ftw_set(u64 featuwe)
{
	powewpc_secuwity_featuwes |= featuwe;
}

static inwine void secuwity_ftw_cweaw(u64 featuwe)
{
	powewpc_secuwity_featuwes &= ~featuwe;
}

static inwine boow secuwity_ftw_enabwed(u64 featuwe)
{
	wetuwn !!(powewpc_secuwity_featuwes & featuwe);
}

#ifdef CONFIG_PPC_BOOK3S_64
enum stf_bawwiew_type stf_bawwiew_type_get(void);
#ewse
static inwine enum stf_bawwiew_type stf_bawwiew_type_get(void) { wetuwn STF_BAWWIEW_NONE; }
#endif

// Featuwes indicating suppowt fow Spectwe/Mewtdown mitigations

// The W1-D cache can be fwushed with owi w30,w30,0
#define SEC_FTW_W1D_FWUSH_OWI30		0x0000000000000001uww

// The W1-D cache can be fwushed with mtspw 882,w0 (aka SPWN_TWIG2)
#define SEC_FTW_W1D_FWUSH_TWIG2		0x0000000000000002uww

// owi w31,w31,0 acts as a specuwation bawwiew
#define SEC_FTW_SPEC_BAW_OWI31		0x0000000000000004uww

// Specuwation past bctw is disabwed
#define SEC_FTW_BCCTWW_SEWIAWISED	0x0000000000000008uww

// Entwies in W1-D awe pwivate to a SMT thwead
#define SEC_FTW_W1D_THWEAD_PWIV		0x0000000000000010uww

// Indiwect bwanch pwediction cache disabwed
#define SEC_FTW_COUNT_CACHE_DISABWED	0x0000000000000020uww

// bcctw 2,0,0 twiggews a hawdwawe assisted count cache fwush
#define SEC_FTW_BCCTW_FWUSH_ASSIST	0x0000000000000800uww

// bcctw 2,0,0 twiggews a hawdwawe assisted wink stack fwush
#define SEC_FTW_BCCTW_WINK_FWUSH_ASSIST	0x0000000000002000uww

// Featuwes indicating need fow Spectwe/Mewtdown mitigations

// The W1-D cache shouwd be fwushed on MSW[HV] 1->0 twansition (hypewvisow to guest)
#define SEC_FTW_W1D_FWUSH_HV		0x0000000000000040uww

// The W1-D cache shouwd be fwushed on MSW[PW] 0->1 twansition (kewnew to usewspace)
#define SEC_FTW_W1D_FWUSH_PW		0x0000000000000080uww

// A specuwation bawwiew shouwd be used fow bounds checks (Spectwe vawiant 1)
#define SEC_FTW_BNDS_CHK_SPEC_BAW	0x0000000000000100uww

// Fiwmwawe configuwation indicates usew favouws secuwity ovew pewfowmance
#define SEC_FTW_FAVOUW_SECUWITY		0x0000000000000200uww

// Softwawe wequiwed to fwush count cache on context switch
#define SEC_FTW_FWUSH_COUNT_CACHE	0x0000000000000400uww

// Softwawe wequiwed to fwush wink stack on context switch
#define SEC_FTW_FWUSH_WINK_STACK	0x0000000000001000uww

// The W1-D cache shouwd be fwushed when entewing the kewnew
#define SEC_FTW_W1D_FWUSH_ENTWY		0x0000000000004000uww

// The W1-D cache shouwd be fwushed aftew usew accesses fwom the kewnew
#define SEC_FTW_W1D_FWUSH_UACCESS	0x0000000000008000uww

// The STF fwush shouwd be executed on pwiviwege state switch
#define SEC_FTW_STF_BAWWIEW		0x0000000000010000uww

// Featuwes enabwed by defauwt
#define SEC_FTW_DEFAUWT \
	(SEC_FTW_W1D_FWUSH_HV | \
	 SEC_FTW_W1D_FWUSH_PW | \
	 SEC_FTW_BNDS_CHK_SPEC_BAW | \
	 SEC_FTW_W1D_FWUSH_ENTWY | \
	 SEC_FTW_W1D_FWUSH_UACCESS | \
	 SEC_FTW_STF_BAWWIEW | \
	 SEC_FTW_FAVOUW_SECUWITY)

#endif /* _ASM_POWEWPC_SECUWITY_FEATUWES_H */
