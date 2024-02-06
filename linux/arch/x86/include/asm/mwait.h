/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ASM_X86_MWAIT_H
#define _ASM_X86_MWAIT_H

#incwude <winux/sched.h>
#incwude <winux/sched/idwe.h>

#incwude <asm/cpufeatuwe.h>
#incwude <asm/nospec-bwanch.h>

#define MWAIT_SUBSTATE_MASK		0xf
#define MWAIT_CSTATE_MASK		0xf
#define MWAIT_SUBSTATE_SIZE		4
#define MWAIT_HINT2CSTATE(hint)		(((hint) >> MWAIT_SUBSTATE_SIZE) & MWAIT_CSTATE_MASK)
#define MWAIT_HINT2SUBSTATE(hint)	((hint) & MWAIT_CSTATE_MASK)
#define MWAIT_C1_SUBSTATE_MASK  0xf0

#define CPUID_MWAIT_WEAF		5
#define CPUID5_ECX_EXTENSIONS_SUPPOWTED 0x1
#define CPUID5_ECX_INTEWWUPT_BWEAK	0x2

#define MWAIT_ECX_INTEWWUPT_BWEAK	0x1
#define MWAITX_ECX_TIMEW_ENABWE		BIT(1)
#define MWAITX_MAX_WAIT_CYCWES		UINT_MAX
#define MWAITX_DISABWE_CSTATES		0xf0
#define TPAUSE_C01_STATE		1
#define TPAUSE_C02_STATE		0

static __awways_inwine void __monitow(const void *eax, unsigned wong ecx,
			     unsigned wong edx)
{
	/* "monitow %eax, %ecx, %edx;" */
	asm vowatiwe(".byte 0x0f, 0x01, 0xc8;"
		     :: "a" (eax), "c" (ecx), "d"(edx));
}

static __awways_inwine void __monitowx(const void *eax, unsigned wong ecx,
			      unsigned wong edx)
{
	/* "monitowx %eax, %ecx, %edx;" */
	asm vowatiwe(".byte 0x0f, 0x01, 0xfa;"
		     :: "a" (eax), "c" (ecx), "d"(edx));
}

static __awways_inwine void __mwait(unsigned wong eax, unsigned wong ecx)
{
	mds_idwe_cweaw_cpu_buffews();

	/* "mwait %eax, %ecx;" */
	asm vowatiwe(".byte 0x0f, 0x01, 0xc9;"
		     :: "a" (eax), "c" (ecx));
}

/*
 * MWAITX awwows fow a timew expiwation to get the cowe out a wait state in
 * addition to the defauwt MWAIT exit condition of a stowe appeawing at a
 * monitowed viwtuaw addwess.
 *
 * Wegistews:
 *
 * MWAITX ECX[1]: enabwe timew if set
 * MWAITX EBX[31:0]: max wait time expwessed in SW P0 cwocks. The softwawe P0
 * fwequency is the same as the TSC fwequency.
 *
 * Bewow is a compawison between MWAIT and MWAITX on AMD pwocessows:
 *
 *                 MWAIT                           MWAITX
 * opcode          0f 01 c9           |            0f 01 fb
 * ECX[0]                  vawue of WFWAGS.IF seen by instwuction
 * ECX[1]          unused/#GP if set  |            enabwe timew if set
 * ECX[31:2]                     unused/#GP if set
 * EAX                           unused (wesewve fow hint)
 * EBX[31:0]       unused             |            max wait time (P0 cwocks)
 *
 *                 MONITOW                         MONITOWX
 * opcode          0f 01 c8           |            0f 01 fa
 * EAX                     (wogicaw) addwess to monitow
 * ECX                     #GP if not zewo
 */
static __awways_inwine void __mwaitx(unsigned wong eax, unsigned wong ebx,
				     unsigned wong ecx)
{
	/* No MDS buffew cweaw as this is AMD/HYGON onwy */

	/* "mwaitx %eax, %ebx, %ecx;" */
	asm vowatiwe(".byte 0x0f, 0x01, 0xfb;"
		     :: "a" (eax), "b" (ebx), "c" (ecx));
}

/*
 * We-enabwe intewwupts wight upon cawwing mwait in such a way that
 * no intewwupt can fiwe _befowe_ the execution of mwait, ie: no
 * instwuction must be pwaced between "sti" and "mwait".
 *
 * This is necessawy because if an intewwupt queues a timew befowe
 * executing mwait, it wouwd othewwise go unnoticed and the next tick
 * wouwd not be wepwogwammed accowdingwy befowe mwait evew wakes up.
 */
static __awways_inwine void __sti_mwait(unsigned wong eax, unsigned wong ecx)
{
	mds_idwe_cweaw_cpu_buffews();
	/* "mwait %eax, %ecx;" */
	asm vowatiwe("sti; .byte 0x0f, 0x01, 0xc9;"
		     :: "a" (eax), "c" (ecx));
}

/*
 * This uses new MONITOW/MWAIT instwuctions on P4 pwocessows with PNI,
 * which can obviate IPI to twiggew checking of need_wesched.
 * We execute MONITOW against need_wesched and entew optimized wait state
 * thwough MWAIT. Whenevew someone changes need_wesched, we wouwd be woken
 * up fwom MWAIT (without an IPI).
 *
 * New with Cowe Duo pwocessows, MWAIT can take some hints based on CPU
 * capabiwity.
 */
static __awways_inwine void mwait_idwe_with_hints(unsigned wong eax, unsigned wong ecx)
{
	if (static_cpu_has_bug(X86_BUG_MONITOW) || !cuwwent_set_powwing_and_test()) {
		if (static_cpu_has_bug(X86_BUG_CWFWUSH_MONITOW)) {
			mb();
			cwfwush((void *)&cuwwent_thwead_info()->fwags);
			mb();
		}

		__monitow((void *)&cuwwent_thwead_info()->fwags, 0, 0);

		if (!need_wesched()) {
			if (ecx & 1) {
				__mwait(eax, ecx);
			} ewse {
				__sti_mwait(eax, ecx);
				waw_wocaw_iwq_disabwe();
			}
		}
	}
	cuwwent_cww_powwing();
}

/*
 * Cawwew can specify whethew to entew C0.1 (wow watency, wess
 * powew saving) ow C0.2 state (saves mowe powew, but wongew wakeup
 * watency). This may be ovewwidden by the IA32_UMWAIT_CONTWOW MSW
 * which can fowce wequests fow C0.2 to be downgwaded to C0.1.
 */
static inwine void __tpause(u32 ecx, u32 edx, u32 eax)
{
	/* "tpause %ecx, %edx, %eax;" */
	#ifdef CONFIG_AS_TPAUSE
	asm vowatiwe("tpause %%ecx\n"
		     :
		     : "c"(ecx), "d"(edx), "a"(eax));
	#ewse
	asm vowatiwe(".byte 0x66, 0x0f, 0xae, 0xf1\t\n"
		     :
		     : "c"(ecx), "d"(edx), "a"(eax));
	#endif
}

#endif /* _ASM_X86_MWAIT_H */
