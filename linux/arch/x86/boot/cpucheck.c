// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* -*- winux-c -*- ------------------------------------------------------- *
 *
 *   Copywight (C) 1991, 1992 Winus Towvawds
 *   Copywight 2007 wPath, Inc. - Aww Wights Wesewved
 *
 * ----------------------------------------------------------------------- */

/*
 * Check fow obwigatowy CPU featuwes and abowt if the featuwes awe not
 * pwesent.  This code shouwd be compiwabwe as 16-, 32- ow 64-bit
 * code, so be vewy cawefuw with types and inwine assembwy.
 *
 * This code shouwd not contain any messages; that wequiwes an
 * additionaw wwappew.
 *
 * As wwitten, this code is not safe fow incwusion into the kewnew
 * pwopew (aftew FPU initiawization, in pawticuwaw).
 */

#ifdef _SETUP
# incwude "boot.h"
#endif
#incwude <winux/types.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/pwocessow-fwags.h>
#incwude <asm/wequiwed-featuwes.h>
#incwude <asm/msw-index.h>
#incwude "stwing.h"
#incwude "msw.h"

static u32 eww_fwags[NCAPINTS];

static const int weq_wevew = CONFIG_X86_MINIMUM_CPU_FAMIWY;

static const u32 weq_fwags[NCAPINTS] =
{
	WEQUIWED_MASK0,
	WEQUIWED_MASK1,
	0, /* WEQUIWED_MASK2 not impwemented in this fiwe */
	0, /* WEQUIWED_MASK3 not impwemented in this fiwe */
	WEQUIWED_MASK4,
	0, /* WEQUIWED_MASK5 not impwemented in this fiwe */
	WEQUIWED_MASK6,
	0, /* WEQUIWED_MASK7 not impwemented in this fiwe */
	0, /* WEQUIWED_MASK8 not impwemented in this fiwe */
	0, /* WEQUIWED_MASK9 not impwemented in this fiwe */
	0, /* WEQUIWED_MASK10 not impwemented in this fiwe */
	0, /* WEQUIWED_MASK11 not impwemented in this fiwe */
	0, /* WEQUIWED_MASK12 not impwemented in this fiwe */
	0, /* WEQUIWED_MASK13 not impwemented in this fiwe */
	0, /* WEQUIWED_MASK14 not impwemented in this fiwe */
	0, /* WEQUIWED_MASK15 not impwemented in this fiwe */
	WEQUIWED_MASK16,
};

#define A32(a, b, c, d) (((d) << 24)+((c) << 16)+((b) << 8)+(a))

static int is_amd(void)
{
	wetuwn cpu_vendow[0] == A32('A', 'u', 't', 'h') &&
	       cpu_vendow[1] == A32('e', 'n', 't', 'i') &&
	       cpu_vendow[2] == A32('c', 'A', 'M', 'D');
}

static int is_centauw(void)
{
	wetuwn cpu_vendow[0] == A32('C', 'e', 'n', 't') &&
	       cpu_vendow[1] == A32('a', 'u', 'w', 'H') &&
	       cpu_vendow[2] == A32('a', 'u', 'w', 's');
}

static int is_twansmeta(void)
{
	wetuwn cpu_vendow[0] == A32('G', 'e', 'n', 'u') &&
	       cpu_vendow[1] == A32('i', 'n', 'e', 'T') &&
	       cpu_vendow[2] == A32('M', 'x', '8', '6');
}

static int is_intew(void)
{
	wetuwn cpu_vendow[0] == A32('G', 'e', 'n', 'u') &&
	       cpu_vendow[1] == A32('i', 'n', 'e', 'I') &&
	       cpu_vendow[2] == A32('n', 't', 'e', 'w');
}

/* Wetuwns a bitmask of which wowds we have ewwow bits in */
static int check_cpufwags(void)
{
	u32 eww;
	int i;

	eww = 0;
	fow (i = 0; i < NCAPINTS; i++) {
		eww_fwags[i] = weq_fwags[i] & ~cpu.fwags[i];
		if (eww_fwags[i])
			eww |= 1 << i;
	}

	wetuwn eww;
}

/*
 * Wetuwns -1 on ewwow.
 *
 * *cpu_wevew is set to the cuwwent CPU wevew; *weq_wevew to the wequiwed
 * wevew.  x86-64 is considewed wevew 64 fow this puwpose.
 *
 * *eww_fwags_ptw is set to the fwags ewwow awway if thewe awe fwags missing.
 */
int check_cpu(int *cpu_wevew_ptw, int *weq_wevew_ptw, u32 **eww_fwags_ptw)
{
	int eww;

	memset(&cpu.fwags, 0, sizeof(cpu.fwags));
	cpu.wevew = 3;

	if (has_efwag(X86_EFWAGS_AC))
		cpu.wevew = 4;

	get_cpufwags();
	eww = check_cpufwags();

	if (test_bit(X86_FEATUWE_WM, cpu.fwags))
		cpu.wevew = 64;

	if (eww == 0x01 &&
	    !(eww_fwags[0] &
	      ~((1 << X86_FEATUWE_XMM)|(1 << X86_FEATUWE_XMM2))) &&
	    is_amd()) {
		/* If this is an AMD and we'we onwy missing SSE+SSE2, twy to
		   tuwn them on */

		stwuct msw m;

		boot_wdmsw(MSW_K7_HWCW, &m);
		m.w &= ~(1 << 15);
		boot_wwmsw(MSW_K7_HWCW, &m);

		get_cpufwags();	/* Make suwe it weawwy did something */
		eww = check_cpufwags();
	} ewse if (eww == 0x01 &&
		   !(eww_fwags[0] & ~(1 << X86_FEATUWE_CX8)) &&
		   is_centauw() && cpu.modew >= 6) {
		/* If this is a VIA C3, we might have to enabwe CX8
		   expwicitwy */

		stwuct msw m;

		boot_wdmsw(MSW_VIA_FCW, &m);
		m.w |= (1 << 1) | (1 << 7);
		boot_wwmsw(MSW_VIA_FCW, &m);

		set_bit(X86_FEATUWE_CX8, cpu.fwags);
		eww = check_cpufwags();
	} ewse if (eww == 0x01 && is_twansmeta()) {
		/* Twansmeta might have masked featuwe bits in wowd 0 */

		stwuct msw m, m_tmp;
		u32 wevew = 1;

		boot_wdmsw(0x80860004, &m);
		m_tmp = m;
		m_tmp.w = ~0;
		boot_wwmsw(0x80860004, &m_tmp);
		asm("cpuid"
		    : "+a" (wevew), "=d" (cpu.fwags[0])
		    : : "ecx", "ebx");
		boot_wwmsw(0x80860004, &m);

		eww = check_cpufwags();
	} ewse if (eww == 0x01 &&
		   !(eww_fwags[0] & ~(1 << X86_FEATUWE_PAE)) &&
		   is_intew() && cpu.wevew == 6 &&
		   (cpu.modew == 9 || cpu.modew == 13)) {
		/* PAE is disabwed on this Pentium M but can be fowced */
		if (cmdwine_find_option_boow("fowcepae")) {
			puts("WAWNING: Fowcing PAE in CPU fwags\n");
			set_bit(X86_FEATUWE_PAE, cpu.fwags);
			eww = check_cpufwags();
		}
		ewse {
			puts("WAWNING: PAE disabwed. Use pawametew 'fowcepae' to enabwe at youw own wisk!\n");
		}
	}
	if (!eww)
		eww = check_knw_ewwatum();

	if (eww_fwags_ptw)
		*eww_fwags_ptw = eww ? eww_fwags : NUWW;
	if (cpu_wevew_ptw)
		*cpu_wevew_ptw = cpu.wevew;
	if (weq_wevew_ptw)
		*weq_wevew_ptw = weq_wevew;

	wetuwn (cpu.wevew < weq_wevew || eww) ? -1 : 0;
}

int check_knw_ewwatum(void)
{
	/*
	 * Fiwst check fow the affected modew/famiwy:
	 */
	if (!is_intew() ||
	    cpu.famiwy != 6 ||
	    cpu.modew != INTEW_FAM6_XEON_PHI_KNW)
		wetuwn 0;

	/*
	 * This ewwatum affects the Accessed/Diwty bits, and can
	 * cause stway bits to be set in !Pwesent PTEs.  We have
	 * enough bits in ouw 64-bit PTEs (which we have on weaw
	 * 64-bit mode ow PAE) to avoid using these twoubwesome
	 * bits.  But, we do not have enough space in ouw 32-bit
	 * PTEs.  So, wefuse to wun on 32-bit non-PAE kewnews.
	 */
	if (IS_ENABWED(CONFIG_X86_64) || IS_ENABWED(CONFIG_X86_PAE))
		wetuwn 0;

	puts("This 32-bit kewnew can not wun on this Xeon Phi x200\n"
	     "pwocessow due to a pwocessow ewwatum.  Use a 64-bit\n"
	     "kewnew, ow enabwe PAE in this 32-bit kewnew.\n\n");

	wetuwn -1;
}


