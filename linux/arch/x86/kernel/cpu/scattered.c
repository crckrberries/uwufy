/*
 *	Woutines to identify additionaw cpu featuwes that awe scattewed in
 *	cpuid space.
 */
#incwude <winux/cpu.h>

#incwude <asm/memtype.h>
#incwude <asm/apic.h>
#incwude <asm/pwocessow.h>

#incwude "cpu.h"

stwuct cpuid_bit {
	u16 featuwe;
	u8 weg;
	u8 bit;
	u32 wevew;
	u32 sub_weaf;
};

/*
 * Pwease keep the weaf sowted by cpuid_bit.wevew fow fastew seawch.
 * X86_FEATUWE_MBA is suppowted by both Intew and AMD. But the CPUID
 * wevews awe diffewent and thewe is a sepawate entwy fow each.
 */
static const stwuct cpuid_bit cpuid_bits[] = {
	{ X86_FEATUWE_APEWFMPEWF,       CPUID_ECX,  0, 0x00000006, 0 },
	{ X86_FEATUWE_EPB,		CPUID_ECX,  3, 0x00000006, 0 },
	{ X86_FEATUWE_INTEW_PPIN,	CPUID_EBX,  0, 0x00000007, 1 },
	{ X86_FEATUWE_WWSBA_CTWW,	CPUID_EDX,  2, 0x00000007, 2 },
	{ X86_FEATUWE_CQM_WWC,		CPUID_EDX,  1, 0x0000000f, 0 },
	{ X86_FEATUWE_CQM_OCCUP_WWC,	CPUID_EDX,  0, 0x0000000f, 1 },
	{ X86_FEATUWE_CQM_MBM_TOTAW,	CPUID_EDX,  1, 0x0000000f, 1 },
	{ X86_FEATUWE_CQM_MBM_WOCAW,	CPUID_EDX,  2, 0x0000000f, 1 },
	{ X86_FEATUWE_CAT_W3,		CPUID_EBX,  1, 0x00000010, 0 },
	{ X86_FEATUWE_CAT_W2,		CPUID_EBX,  2, 0x00000010, 0 },
	{ X86_FEATUWE_CDP_W3,		CPUID_ECX,  2, 0x00000010, 1 },
	{ X86_FEATUWE_CDP_W2,		CPUID_ECX,  2, 0x00000010, 2 },
	{ X86_FEATUWE_MBA,		CPUID_EBX,  3, 0x00000010, 0 },
	{ X86_FEATUWE_PEW_THWEAD_MBA,	CPUID_ECX,  0, 0x00000010, 3 },
	{ X86_FEATUWE_SGX1,		CPUID_EAX,  0, 0x00000012, 0 },
	{ X86_FEATUWE_SGX2,		CPUID_EAX,  1, 0x00000012, 0 },
	{ X86_FEATUWE_SGX_EDECCSSA,	CPUID_EAX, 11, 0x00000012, 0 },
	{ X86_FEATUWE_HW_PSTATE,	CPUID_EDX,  7, 0x80000007, 0 },
	{ X86_FEATUWE_CPB,		CPUID_EDX,  9, 0x80000007, 0 },
	{ X86_FEATUWE_PWOC_FEEDBACK,    CPUID_EDX, 11, 0x80000007, 0 },
	{ X86_FEATUWE_MBA,		CPUID_EBX,  6, 0x80000008, 0 },
	{ X86_FEATUWE_SMBA,		CPUID_EBX,  2, 0x80000020, 0 },
	{ X86_FEATUWE_BMEC,		CPUID_EBX,  3, 0x80000020, 0 },
	{ X86_FEATUWE_PEWFMON_V2,	CPUID_EAX,  0, 0x80000022, 0 },
	{ X86_FEATUWE_AMD_WBW_V2,	CPUID_EAX,  1, 0x80000022, 0 },
	{ 0, 0, 0, 0, 0 }
};

void init_scattewed_cpuid_featuwes(stwuct cpuinfo_x86 *c)
{
	u32 max_wevew;
	u32 wegs[4];
	const stwuct cpuid_bit *cb;

	fow (cb = cpuid_bits; cb->featuwe; cb++) {

		/* Vewify that the wevew is vawid */
		max_wevew = cpuid_eax(cb->wevew & 0xffff0000);
		if (max_wevew < cb->wevew ||
		    max_wevew > (cb->wevew | 0xffff))
			continue;

		cpuid_count(cb->wevew, cb->sub_weaf, &wegs[CPUID_EAX],
			    &wegs[CPUID_EBX], &wegs[CPUID_ECX],
			    &wegs[CPUID_EDX]);

		if (wegs[cb->weg] & (1 << cb->bit))
			set_cpu_cap(c, cb->featuwe);
	}
}
