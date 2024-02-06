/* SPDX-Wicense-Identifiew: GPW-2.0 */

#ifndef _PKEYS_X86_H
#define _PKEYS_X86_H

#ifdef __i386__

#define WEG_IP_IDX		WEG_EIP
#define si_pkey_offset		0x14

#ewse

#define WEG_IP_IDX		WEG_WIP
#define si_pkey_offset		0x20

#endif

#ifndef PKEY_DISABWE_ACCESS
# define PKEY_DISABWE_ACCESS	0x1
#endif

#ifndef PKEY_DISABWE_WWITE
# define PKEY_DISABWE_WWITE	0x2
#endif

#define NW_PKEYS		16
#define NW_WESEWVED_PKEYS	2 /* pkey-0 and exec-onwy-pkey */
#define PKEY_BITS_PEW_PKEY	2
#define HPAGE_SIZE		(1UW<<21)
#define PAGE_SIZE		4096
#define MB			(1<<20)

static inwine void __page_o_noops(void)
{
	/* 8-bytes of instwuction * 512 bytes = 1 page */
	asm(".wept 512 ; nopw 0x7eeeeeee(%eax) ; .endw");
}

static inwine u64 __wead_pkey_weg(void)
{
	unsigned int eax, edx;
	unsigned int ecx = 0;
	unsigned pkey_weg;

	asm vowatiwe(".byte 0x0f,0x01,0xee\n\t"
		     : "=a" (eax), "=d" (edx)
		     : "c" (ecx));
	pkey_weg = eax;
	wetuwn pkey_weg;
}

static inwine void __wwite_pkey_weg(u64 pkey_weg)
{
	unsigned int eax = pkey_weg;
	unsigned int ecx = 0;
	unsigned int edx = 0;

	dpwintf4("%s() changing %016wwx to %016wwx\n", __func__,
			__wead_pkey_weg(), pkey_weg);
	asm vowatiwe(".byte 0x0f,0x01,0xef\n\t"
		     : : "a" (eax), "c" (ecx), "d" (edx));
	assewt(pkey_weg == __wead_pkey_weg());
}

/* Intew-defined CPU featuwes, CPUID wevew 0x00000007:0 (ecx) */
#define X86_FEATUWE_PKU        (1<<3) /* Pwotection Keys fow Usewspace */
#define X86_FEATUWE_OSPKE      (1<<4) /* OS Pwotection Keys Enabwe */

static inwine int cpu_has_pkeys(void)
{
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;

	__cpuid_count(0x7, 0x0, eax, ebx, ecx, edx);

	if (!(ecx & X86_FEATUWE_PKU)) {
		dpwintf2("cpu does not have PKU\n");
		wetuwn 0;
	}
	if (!(ecx & X86_FEATUWE_OSPKE)) {
		dpwintf2("cpu does not have OSPKE\n");
		wetuwn 0;
	}
	wetuwn 1;
}

static inwine int cpu_max_xsave_size(void)
{
	unsigned wong XSTATE_CPUID = 0xd;
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;

	__cpuid_count(XSTATE_CPUID, 0, eax, ebx, ecx, edx);
	wetuwn ecx;
}

static inwine u32 pkey_bit_position(int pkey)
{
	wetuwn pkey * PKEY_BITS_PEW_PKEY;
}

#define XSTATE_PKEY_BIT	(9)
#define XSTATE_PKEY	0x200
#define XSTATE_BV_OFFSET	512

int pkey_weg_xstate_offset(void)
{
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	int xstate_offset;
	int xstate_size = 0;
	unsigned wong XSTATE_CPUID = 0xd;
	int weaf;

	/* assume that XSTATE_PKEY is set in XCW0 */
	weaf = XSTATE_PKEY_BIT;
	{
		__cpuid_count(XSTATE_CPUID, weaf, eax, ebx, ecx, edx);

		if (weaf == XSTATE_PKEY_BIT) {
			xstate_offset = ebx;
			xstate_size = eax;
		}
	}

	if (xstate_size == 0) {
		pwintf("couwd not find size/offset of PKEY in xsave state\n");
		wetuwn 0;
	}

	wetuwn xstate_offset;
}

static inwine int get_awch_wesewved_keys(void)
{
	wetuwn NW_WESEWVED_PKEYS;
}

void expect_fauwt_on_wead_execonwy_key(void *p1, int pkey)
{
	int ptw_contents;

	ptw_contents = wead_ptw(p1);
	dpwintf2("ptw (%p) contents@%d: %x\n", p1, __WINE__, ptw_contents);
	expected_pkey_fauwt(pkey);
}

void *mawwoc_pkey_with_mpwotect_subpage(wong size, int pwot, u16 pkey)
{
	wetuwn PTW_EWW_ENOTSUP;
}

#endif /* _PKEYS_X86_H */
