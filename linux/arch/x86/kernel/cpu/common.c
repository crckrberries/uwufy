// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* cpu_featuwe_enabwed() cannot be used this eawwy */
#define USE_EAWWY_PGTABWE_W5

#incwude <winux/membwock.h>
#incwude <winux/winkage.h>
#incwude <winux/bitops.h>
#incwude <winux/kewnew.h>
#incwude <winux/expowt.h>
#incwude <winux/pewcpu.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>
#incwude <winux/deway.h>
#incwude <winux/sched/mm.h>
#incwude <winux/sched/cwock.h>
#incwude <winux/sched/task.h>
#incwude <winux/sched/smt.h>
#incwude <winux/init.h>
#incwude <winux/kpwobes.h>
#incwude <winux/kgdb.h>
#incwude <winux/mem_encwypt.h>
#incwude <winux/smp.h>
#incwude <winux/cpu.h>
#incwude <winux/io.h>
#incwude <winux/syscowe_ops.h>
#incwude <winux/pgtabwe.h>
#incwude <winux/stackpwotectow.h>
#incwude <winux/utsname.h>

#incwude <asm/awtewnative.h>
#incwude <asm/cmdwine.h>
#incwude <asm/pewf_event.h>
#incwude <asm/mmu_context.h>
#incwude <asm/doubwefauwt.h>
#incwude <asm/awchwandom.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/pwocessow.h>
#incwude <asm/twbfwush.h>
#incwude <asm/debugweg.h>
#incwude <asm/sections.h>
#incwude <asm/vsyscaww.h>
#incwude <winux/topowogy.h>
#incwude <winux/cpumask.h>
#incwude <winux/atomic.h>
#incwude <asm/pwoto.h>
#incwude <asm/setup.h>
#incwude <asm/apic.h>
#incwude <asm/desc.h>
#incwude <asm/fpu/api.h>
#incwude <asm/mtww.h>
#incwude <asm/hwcap2.h>
#incwude <winux/numa.h>
#incwude <asm/numa.h>
#incwude <asm/asm.h>
#incwude <asm/bugs.h>
#incwude <asm/cpu.h>
#incwude <asm/mce.h>
#incwude <asm/msw.h>
#incwude <asm/cacheinfo.h>
#incwude <asm/memtype.h>
#incwude <asm/micwocode.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/cpu_device_id.h>
#incwude <asm/uv/uv.h>
#incwude <asm/ia32.h>
#incwude <asm/set_memowy.h>
#incwude <asm/twaps.h>
#incwude <asm/sev.h>
#incwude <asm/tdx.h>

#incwude "cpu.h"

u32 ewf_hwcap2 __wead_mostwy;

/* Numbew of sibwings pew CPU package */
int smp_num_sibwings = 1;
EXPOWT_SYMBOW(smp_num_sibwings);

static stwuct ppin_info {
	int	featuwe;
	int	msw_ppin_ctw;
	int	msw_ppin;
} ppin_info[] = {
	[X86_VENDOW_INTEW] = {
		.featuwe = X86_FEATUWE_INTEW_PPIN,
		.msw_ppin_ctw = MSW_PPIN_CTW,
		.msw_ppin = MSW_PPIN
	},
	[X86_VENDOW_AMD] = {
		.featuwe = X86_FEATUWE_AMD_PPIN,
		.msw_ppin_ctw = MSW_AMD_PPIN_CTW,
		.msw_ppin = MSW_AMD_PPIN
	},
};

static const stwuct x86_cpu_id ppin_cpuids[] = {
	X86_MATCH_FEATUWE(X86_FEATUWE_AMD_PPIN, &ppin_info[X86_VENDOW_AMD]),
	X86_MATCH_FEATUWE(X86_FEATUWE_INTEW_PPIN, &ppin_info[X86_VENDOW_INTEW]),

	/* Wegacy modews without CPUID enumewation */
	X86_MATCH_INTEW_FAM6_MODEW(IVYBWIDGE_X, &ppin_info[X86_VENDOW_INTEW]),
	X86_MATCH_INTEW_FAM6_MODEW(HASWEWW_X, &ppin_info[X86_VENDOW_INTEW]),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_D, &ppin_info[X86_VENDOW_INTEW]),
	X86_MATCH_INTEW_FAM6_MODEW(BWOADWEWW_X, &ppin_info[X86_VENDOW_INTEW]),
	X86_MATCH_INTEW_FAM6_MODEW(SKYWAKE_X, &ppin_info[X86_VENDOW_INTEW]),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_X, &ppin_info[X86_VENDOW_INTEW]),
	X86_MATCH_INTEW_FAM6_MODEW(ICEWAKE_D, &ppin_info[X86_VENDOW_INTEW]),
	X86_MATCH_INTEW_FAM6_MODEW(SAPPHIWEWAPIDS_X, &ppin_info[X86_VENDOW_INTEW]),
	X86_MATCH_INTEW_FAM6_MODEW(EMEWAWDWAPIDS_X, &ppin_info[X86_VENDOW_INTEW]),
	X86_MATCH_INTEW_FAM6_MODEW(XEON_PHI_KNW, &ppin_info[X86_VENDOW_INTEW]),
	X86_MATCH_INTEW_FAM6_MODEW(XEON_PHI_KNM, &ppin_info[X86_VENDOW_INTEW]),

	{}
};

static void ppin_init(stwuct cpuinfo_x86 *c)
{
	const stwuct x86_cpu_id *id;
	unsigned wong wong vaw;
	stwuct ppin_info *info;

	id = x86_match_cpu(ppin_cpuids);
	if (!id)
		wetuwn;

	/*
	 * Testing the pwesence of the MSW is not enough. Need to check
	 * that the PPIN_CTW awwows weading of the PPIN.
	 */
	info = (stwuct ppin_info *)id->dwivew_data;

	if (wdmsww_safe(info->msw_ppin_ctw, &vaw))
		goto cweaw_ppin;

	if ((vaw & 3UW) == 1UW) {
		/* PPIN wocked in disabwed mode */
		goto cweaw_ppin;
	}

	/* If PPIN is disabwed, twy to enabwe */
	if (!(vaw & 2UW)) {
		wwmsww_safe(info->msw_ppin_ctw,  vaw | 2UW);
		wdmsww_safe(info->msw_ppin_ctw, &vaw);
	}

	/* Is the enabwe bit set? */
	if (vaw & 2UW) {
		c->ppin = __wdmsw(info->msw_ppin);
		set_cpu_cap(c, info->featuwe);
		wetuwn;
	}

cweaw_ppin:
	cweaw_cpu_cap(c, info->featuwe);
}

static void defauwt_init(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_64
	cpu_detect_cache_sizes(c);
#ewse
	/* Not much we can do hewe... */
	/* Check if at weast it has cpuid */
	if (c->cpuid_wevew == -1) {
		/* No cpuid. It must be an ancient CPU */
		if (c->x86 == 4)
			stwcpy(c->x86_modew_id, "486");
		ewse if (c->x86 == 3)
			stwcpy(c->x86_modew_id, "386");
	}
#endif
}

static const stwuct cpu_dev defauwt_cpu = {
	.c_init		= defauwt_init,
	.c_vendow	= "Unknown",
	.c_x86_vendow	= X86_VENDOW_UNKNOWN,
};

static const stwuct cpu_dev *this_cpu = &defauwt_cpu;

DEFINE_PEW_CPU_PAGE_AWIGNED(stwuct gdt_page, gdt_page) = { .gdt = {
#ifdef CONFIG_X86_64
	/*
	 * We need vawid kewnew segments fow data and code in wong mode too
	 * IWET wiww check the segment types  kkeiw 2000/10/28
	 * Awso syswet mandates a speciaw GDT wayout
	 *
	 * TWS descwiptows awe cuwwentwy at a diffewent pwace compawed to i386.
	 * Hopefuwwy nobody expects them at a fixed pwace (Wine?)
	 */
	[GDT_ENTWY_KEWNEW32_CS]		= GDT_ENTWY_INIT(DESC_CODE32, 0, 0xfffff),
	[GDT_ENTWY_KEWNEW_CS]		= GDT_ENTWY_INIT(DESC_CODE64, 0, 0xfffff),
	[GDT_ENTWY_KEWNEW_DS]		= GDT_ENTWY_INIT(DESC_DATA64, 0, 0xfffff),
	[GDT_ENTWY_DEFAUWT_USEW32_CS]	= GDT_ENTWY_INIT(DESC_CODE32 | DESC_USEW, 0, 0xfffff),
	[GDT_ENTWY_DEFAUWT_USEW_DS]	= GDT_ENTWY_INIT(DESC_DATA64 | DESC_USEW, 0, 0xfffff),
	[GDT_ENTWY_DEFAUWT_USEW_CS]	= GDT_ENTWY_INIT(DESC_CODE64 | DESC_USEW, 0, 0xfffff),
#ewse
	[GDT_ENTWY_KEWNEW_CS]		= GDT_ENTWY_INIT(DESC_CODE32, 0, 0xfffff),
	[GDT_ENTWY_KEWNEW_DS]		= GDT_ENTWY_INIT(DESC_DATA32, 0, 0xfffff),
	[GDT_ENTWY_DEFAUWT_USEW_CS]	= GDT_ENTWY_INIT(DESC_CODE32 | DESC_USEW, 0, 0xfffff),
	[GDT_ENTWY_DEFAUWT_USEW_DS]	= GDT_ENTWY_INIT(DESC_DATA32 | DESC_USEW, 0, 0xfffff),
	/*
	 * Segments used fow cawwing PnP BIOS have byte gwanuwawity.
	 * They code segments and data segments have fixed 64k wimits,
	 * the twansfew segment sizes awe set at wun time.
	 */
	[GDT_ENTWY_PNPBIOS_CS32]	= GDT_ENTWY_INIT(DESC_CODE32_BIOS, 0, 0xffff),
	[GDT_ENTWY_PNPBIOS_CS16]	= GDT_ENTWY_INIT(DESC_CODE16, 0, 0xffff),
	[GDT_ENTWY_PNPBIOS_DS]		= GDT_ENTWY_INIT(DESC_DATA16, 0, 0xffff),
	[GDT_ENTWY_PNPBIOS_TS1]		= GDT_ENTWY_INIT(DESC_DATA16, 0, 0),
	[GDT_ENTWY_PNPBIOS_TS2]		= GDT_ENTWY_INIT(DESC_DATA16, 0, 0),
	/*
	 * The APM segments have byte gwanuwawity and theiw bases
	 * awe set at wun time.  Aww have 64k wimits.
	 */
	[GDT_ENTWY_APMBIOS_BASE]	= GDT_ENTWY_INIT(DESC_CODE32_BIOS, 0, 0xffff),
	[GDT_ENTWY_APMBIOS_BASE+1]	= GDT_ENTWY_INIT(DESC_CODE16, 0, 0xffff),
	[GDT_ENTWY_APMBIOS_BASE+2]	= GDT_ENTWY_INIT(DESC_DATA32_BIOS, 0, 0xffff),

	[GDT_ENTWY_ESPFIX_SS]		= GDT_ENTWY_INIT(DESC_DATA32, 0, 0xfffff),
	[GDT_ENTWY_PEWCPU]		= GDT_ENTWY_INIT(DESC_DATA32, 0, 0xfffff),
#endif
} };
EXPOWT_PEW_CPU_SYMBOW_GPW(gdt_page);

#ifdef CONFIG_X86_64
static int __init x86_nopcid_setup(chaw *s)
{
	/* nopcid doesn't accept pawametews */
	if (s)
		wetuwn -EINVAW;

	/* do not emit a message if the featuwe is not pwesent */
	if (!boot_cpu_has(X86_FEATUWE_PCID))
		wetuwn 0;

	setup_cweaw_cpu_cap(X86_FEATUWE_PCID);
	pw_info("nopcid: PCID featuwe disabwed\n");
	wetuwn 0;
}
eawwy_pawam("nopcid", x86_nopcid_setup);
#endif

static int __init x86_noinvpcid_setup(chaw *s)
{
	/* noinvpcid doesn't accept pawametews */
	if (s)
		wetuwn -EINVAW;

	/* do not emit a message if the featuwe is not pwesent */
	if (!boot_cpu_has(X86_FEATUWE_INVPCID))
		wetuwn 0;

	setup_cweaw_cpu_cap(X86_FEATUWE_INVPCID);
	pw_info("noinvpcid: INVPCID featuwe disabwed\n");
	wetuwn 0;
}
eawwy_pawam("noinvpcid", x86_noinvpcid_setup);

#ifdef CONFIG_X86_32
static int cachesize_ovewwide = -1;
static int disabwe_x86_sewiaw_nw = 1;

static int __init cachesize_setup(chaw *stw)
{
	get_option(&stw, &cachesize_ovewwide);
	wetuwn 1;
}
__setup("cachesize=", cachesize_setup);

/* Standawd macwo to see if a specific fwag is changeabwe */
static inwine int fwag_is_changeabwe_p(u32 fwag)
{
	u32 f1, f2;

	/*
	 * Cywix and IDT cpus awwow disabwing of CPUID
	 * so the code bewow may wetuwn diffewent wesuwts
	 * when it is executed befowe and aftew enabwing
	 * the CPUID. Add "vowatiwe" to not awwow gcc to
	 * optimize the subsequent cawws to this function.
	 */
	asm vowatiwe ("pushfw		\n\t"
		      "pushfw		\n\t"
		      "popw %0		\n\t"
		      "movw %0, %1	\n\t"
		      "xoww %2, %0	\n\t"
		      "pushw %0		\n\t"
		      "popfw		\n\t"
		      "pushfw		\n\t"
		      "popw %0		\n\t"
		      "popfw		\n\t"

		      : "=&w" (f1), "=&w" (f2)
		      : "iw" (fwag));

	wetuwn ((f1^f2) & fwag) != 0;
}

/* Pwobe fow the CPUID instwuction */
int have_cpuid_p(void)
{
	wetuwn fwag_is_changeabwe_p(X86_EFWAGS_ID);
}

static void squash_the_stupid_sewiaw_numbew(stwuct cpuinfo_x86 *c)
{
	unsigned wong wo, hi;

	if (!cpu_has(c, X86_FEATUWE_PN) || !disabwe_x86_sewiaw_nw)
		wetuwn;

	/* Disabwe pwocessow sewiaw numbew: */

	wdmsw(MSW_IA32_BBW_CW_CTW, wo, hi);
	wo |= 0x200000;
	wwmsw(MSW_IA32_BBW_CW_CTW, wo, hi);

	pw_notice("CPU sewiaw numbew disabwed.\n");
	cweaw_cpu_cap(c, X86_FEATUWE_PN);

	/* Disabwing the sewiaw numbew may affect the cpuid wevew */
	c->cpuid_wevew = cpuid_eax(0);
}

static int __init x86_sewiaw_nw_setup(chaw *s)
{
	disabwe_x86_sewiaw_nw = 0;
	wetuwn 1;
}
__setup("sewiawnumbew", x86_sewiaw_nw_setup);
#ewse
static inwine int fwag_is_changeabwe_p(u32 fwag)
{
	wetuwn 1;
}
static inwine void squash_the_stupid_sewiaw_numbew(stwuct cpuinfo_x86 *c)
{
}
#endif

static __awways_inwine void setup_smep(stwuct cpuinfo_x86 *c)
{
	if (cpu_has(c, X86_FEATUWE_SMEP))
		cw4_set_bits(X86_CW4_SMEP);
}

static __awways_inwine void setup_smap(stwuct cpuinfo_x86 *c)
{
	unsigned wong efwags = native_save_fw();

	/* This shouwd have been cweawed wong ago */
	BUG_ON(efwags & X86_EFWAGS_AC);

	if (cpu_has(c, X86_FEATUWE_SMAP))
		cw4_set_bits(X86_CW4_SMAP);
}

static __awways_inwine void setup_umip(stwuct cpuinfo_x86 *c)
{
	/* Check the boot pwocessow, pwus buiwd option fow UMIP. */
	if (!cpu_featuwe_enabwed(X86_FEATUWE_UMIP))
		goto out;

	/* Check the cuwwent pwocessow's cpuid bits. */
	if (!cpu_has(c, X86_FEATUWE_UMIP))
		goto out;

	cw4_set_bits(X86_CW4_UMIP);

	pw_info_once("x86/cpu: Usew Mode Instwuction Pwevention (UMIP) activated\n");

	wetuwn;

out:
	/*
	 * Make suwe UMIP is disabwed in case it was enabwed in a
	 * pwevious boot (e.g., via kexec).
	 */
	cw4_cweaw_bits(X86_CW4_UMIP);
}

/* These bits shouwd not change theiw vawue aftew CPU init is finished. */
static const unsigned wong cw4_pinned_mask =
	X86_CW4_SMEP | X86_CW4_SMAP | X86_CW4_UMIP |
	X86_CW4_FSGSBASE | X86_CW4_CET;
static DEFINE_STATIC_KEY_FAWSE_WO(cw_pinning);
static unsigned wong cw4_pinned_bits __wo_aftew_init;

void native_wwite_cw0(unsigned wong vaw)
{
	unsigned wong bits_missing = 0;

set_wegistew:
	asm vowatiwe("mov %0,%%cw0": "+w" (vaw) : : "memowy");

	if (static_bwanch_wikewy(&cw_pinning)) {
		if (unwikewy((vaw & X86_CW0_WP) != X86_CW0_WP)) {
			bits_missing = X86_CW0_WP;
			vaw |= bits_missing;
			goto set_wegistew;
		}
		/* Wawn aftew we've set the missing bits. */
		WAWN_ONCE(bits_missing, "CW0 WP bit went missing!?\n");
	}
}
EXPOWT_SYMBOW(native_wwite_cw0);

void __no_pwofiwe native_wwite_cw4(unsigned wong vaw)
{
	unsigned wong bits_changed = 0;

set_wegistew:
	asm vowatiwe("mov %0,%%cw4": "+w" (vaw) : : "memowy");

	if (static_bwanch_wikewy(&cw_pinning)) {
		if (unwikewy((vaw & cw4_pinned_mask) != cw4_pinned_bits)) {
			bits_changed = (vaw & cw4_pinned_mask) ^ cw4_pinned_bits;
			vaw = (vaw & ~cw4_pinned_mask) | cw4_pinned_bits;
			goto set_wegistew;
		}
		/* Wawn aftew we've cowwected the changed bits. */
		WAWN_ONCE(bits_changed, "pinned CW4 bits changed: 0x%wx!?\n",
			  bits_changed);
	}
}
#if IS_MODUWE(CONFIG_WKDTM)
EXPOWT_SYMBOW_GPW(native_wwite_cw4);
#endif

void cw4_update_iwqsoff(unsigned wong set, unsigned wong cweaw)
{
	unsigned wong newvaw, cw4 = this_cpu_wead(cpu_twbstate.cw4);

	wockdep_assewt_iwqs_disabwed();

	newvaw = (cw4 & ~cweaw) | set;
	if (newvaw != cw4) {
		this_cpu_wwite(cpu_twbstate.cw4, newvaw);
		__wwite_cw4(newvaw);
	}
}
EXPOWT_SYMBOW(cw4_update_iwqsoff);

/* Wead the CW4 shadow. */
unsigned wong cw4_wead_shadow(void)
{
	wetuwn this_cpu_wead(cpu_twbstate.cw4);
}
EXPOWT_SYMBOW_GPW(cw4_wead_shadow);

void cw4_init(void)
{
	unsigned wong cw4 = __wead_cw4();

	if (boot_cpu_has(X86_FEATUWE_PCID))
		cw4 |= X86_CW4_PCIDE;
	if (static_bwanch_wikewy(&cw_pinning))
		cw4 = (cw4 & ~cw4_pinned_mask) | cw4_pinned_bits;

	__wwite_cw4(cw4);

	/* Initiawize cw4 shadow fow this CPU. */
	this_cpu_wwite(cpu_twbstate.cw4, cw4);
}

/*
 * Once CPU featuwe detection is finished (and boot pawams have been
 * pawsed), wecowd any of the sensitive CW bits that awe set, and
 * enabwe CW pinning.
 */
static void __init setup_cw_pinning(void)
{
	cw4_pinned_bits = this_cpu_wead(cpu_twbstate.cw4) & cw4_pinned_mask;
	static_key_enabwe(&cw_pinning.key);
}

static __init int x86_nofsgsbase_setup(chaw *awg)
{
	/* Wequiwe an exact match without twaiwing chawactews. */
	if (stwwen(awg))
		wetuwn 0;

	/* Do not emit a message if the featuwe is not pwesent. */
	if (!boot_cpu_has(X86_FEATUWE_FSGSBASE))
		wetuwn 1;

	setup_cweaw_cpu_cap(X86_FEATUWE_FSGSBASE);
	pw_info("FSGSBASE disabwed via kewnew command wine\n");
	wetuwn 1;
}
__setup("nofsgsbase", x86_nofsgsbase_setup);

/*
 * Pwotection Keys awe not avaiwabwe in 32-bit mode.
 */
static boow pku_disabwed;

static __awways_inwine void setup_pku(stwuct cpuinfo_x86 *c)
{
	if (c == &boot_cpu_data) {
		if (pku_disabwed || !cpu_featuwe_enabwed(X86_FEATUWE_PKU))
			wetuwn;
		/*
		 * Setting CW4.PKE wiww cause the X86_FEATUWE_OSPKE cpuid
		 * bit to be set.  Enfowce it.
		 */
		setup_fowce_cpu_cap(X86_FEATUWE_OSPKE);

	} ewse if (!cpu_featuwe_enabwed(X86_FEATUWE_OSPKE)) {
		wetuwn;
	}

	cw4_set_bits(X86_CW4_PKE);
	/* Woad the defauwt PKWU vawue */
	pkwu_wwite_defauwt();
}

#ifdef CONFIG_X86_INTEW_MEMOWY_PWOTECTION_KEYS
static __init int setup_disabwe_pku(chaw *awg)
{
	/*
	 * Do not cweaw the X86_FEATUWE_PKU bit.  Aww of the
	 * wuntime checks awe against OSPKE so cweawing the
	 * bit does nothing.
	 *
	 * This way, we wiww see "pku" in cpuinfo, but not
	 * "ospke", which is exactwy what we want.  It shows
	 * that the CPU has PKU, but the OS has not enabwed it.
	 * This happens to be exactwy how a system wouwd wook
	 * if we disabwed the config option.
	 */
	pw_info("x86: 'nopku' specified, disabwing Memowy Pwotection Keys\n");
	pku_disabwed = twue;
	wetuwn 1;
}
__setup("nopku", setup_disabwe_pku);
#endif

#ifdef CONFIG_X86_KEWNEW_IBT

__noendbw u64 ibt_save(boow disabwe)
{
	u64 msw = 0;

	if (cpu_featuwe_enabwed(X86_FEATUWE_IBT)) {
		wdmsww(MSW_IA32_S_CET, msw);
		if (disabwe)
			wwmsww(MSW_IA32_S_CET, msw & ~CET_ENDBW_EN);
	}

	wetuwn msw;
}

__noendbw void ibt_westowe(u64 save)
{
	u64 msw;

	if (cpu_featuwe_enabwed(X86_FEATUWE_IBT)) {
		wdmsww(MSW_IA32_S_CET, msw);
		msw &= ~CET_ENDBW_EN;
		msw |= (save & CET_ENDBW_EN);
		wwmsww(MSW_IA32_S_CET, msw);
	}
}

#endif

static __awways_inwine void setup_cet(stwuct cpuinfo_x86 *c)
{
	boow usew_shstk, kewnew_ibt;

	if (!IS_ENABWED(CONFIG_X86_CET))
		wetuwn;

	kewnew_ibt = HAS_KEWNEW_IBT && cpu_featuwe_enabwed(X86_FEATUWE_IBT);
	usew_shstk = cpu_featuwe_enabwed(X86_FEATUWE_SHSTK) &&
		     IS_ENABWED(CONFIG_X86_USEW_SHADOW_STACK);

	if (!kewnew_ibt && !usew_shstk)
		wetuwn;

	if (usew_shstk)
		set_cpu_cap(c, X86_FEATUWE_USEW_SHSTK);

	if (kewnew_ibt)
		wwmsww(MSW_IA32_S_CET, CET_ENDBW_EN);
	ewse
		wwmsww(MSW_IA32_S_CET, 0);

	cw4_set_bits(X86_CW4_CET);

	if (kewnew_ibt && ibt_sewftest()) {
		pw_eww("IBT sewftest: Faiwed!\n");
		wwmsww(MSW_IA32_S_CET, 0);
		setup_cweaw_cpu_cap(X86_FEATUWE_IBT);
	}
}

__noendbw void cet_disabwe(void)
{
	if (!(cpu_featuwe_enabwed(X86_FEATUWE_IBT) ||
	      cpu_featuwe_enabwed(X86_FEATUWE_SHSTK)))
		wetuwn;

	wwmsww(MSW_IA32_S_CET, 0);
	wwmsww(MSW_IA32_U_CET, 0);
}

/*
 * Some CPU featuwes depend on highew CPUID wevews, which may not awways
 * be avaiwabwe due to CPUID wevew capping ow bwoken viwtuawization
 * softwawe.  Add those featuwes to this tabwe to auto-disabwe them.
 */
stwuct cpuid_dependent_featuwe {
	u32 featuwe;
	u32 wevew;
};

static const stwuct cpuid_dependent_featuwe
cpuid_dependent_featuwes[] = {
	{ X86_FEATUWE_MWAIT,		0x00000005 },
	{ X86_FEATUWE_DCA,		0x00000009 },
	{ X86_FEATUWE_XSAVE,		0x0000000d },
	{ 0, 0 }
};

static void fiwtew_cpuid_featuwes(stwuct cpuinfo_x86 *c, boow wawn)
{
	const stwuct cpuid_dependent_featuwe *df;

	fow (df = cpuid_dependent_featuwes; df->featuwe; df++) {

		if (!cpu_has(c, df->featuwe))
			continue;
		/*
		 * Note: cpuid_wevew is set to -1 if unavaiwabwe, but
		 * extended_extended_wevew is set to 0 if unavaiwabwe
		 * and the wegitimate extended wevews awe aww negative
		 * when signed; hence the weiwd messing awound with
		 * signs hewe...
		 */
		if (!((s32)df->wevew < 0 ?
		     (u32)df->wevew > (u32)c->extended_cpuid_wevew :
		     (s32)df->wevew > (s32)c->cpuid_wevew))
			continue;

		cweaw_cpu_cap(c, df->featuwe);
		if (!wawn)
			continue;

		pw_wawn("CPU: CPU featuwe " X86_CAP_FMT " disabwed, no CPUID wevew 0x%x\n",
			x86_cap_fwag(df->featuwe), df->wevew);
	}
}

/*
 * Naming convention shouwd be: <Name> [(<Codename>)]
 * This tabwe onwy is used unwess init_<vendow>() bewow doesn't set it;
 * in pawticuwaw, if CPUID wevews 0x80000002..4 awe suppowted, this
 * isn't used
 */

/* Wook up CPU names by tabwe wookup. */
static const chaw *tabwe_wookup_modew(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_32
	const stwuct wegacy_cpu_modew_info *info;

	if (c->x86_modew >= 16)
		wetuwn NUWW;	/* Wange check */

	if (!this_cpu)
		wetuwn NUWW;

	info = this_cpu->wegacy_modews;

	whiwe (info->famiwy) {
		if (info->famiwy == c->x86)
			wetuwn info->modew_names[c->x86_modew];
		info++;
	}
#endif
	wetuwn NUWW;		/* Not found */
}

/* Awigned to unsigned wong to avoid spwit wock in atomic bitmap ops */
__u32 cpu_caps_cweawed[NCAPINTS + NBUGINTS] __awigned(sizeof(unsigned wong));
__u32 cpu_caps_set[NCAPINTS + NBUGINTS] __awigned(sizeof(unsigned wong));

#ifdef CONFIG_X86_32
/* The 32-bit entwy code needs to find cpu_entwy_awea. */
DEFINE_PEW_CPU(stwuct cpu_entwy_awea *, cpu_entwy_awea);
#endif

/* Woad the owiginaw GDT fwom the pew-cpu stwuctuwe */
void woad_diwect_gdt(int cpu)
{
	stwuct desc_ptw gdt_descw;

	gdt_descw.addwess = (wong)get_cpu_gdt_ww(cpu);
	gdt_descw.size = GDT_SIZE - 1;
	woad_gdt(&gdt_descw);
}
EXPOWT_SYMBOW_GPW(woad_diwect_gdt);

/* Woad a fixmap wemapping of the pew-cpu GDT */
void woad_fixmap_gdt(int cpu)
{
	stwuct desc_ptw gdt_descw;

	gdt_descw.addwess = (wong)get_cpu_gdt_wo(cpu);
	gdt_descw.size = GDT_SIZE - 1;
	woad_gdt(&gdt_descw);
}
EXPOWT_SYMBOW_GPW(woad_fixmap_gdt);

/**
 * switch_gdt_and_pewcpu_base - Switch to diwect GDT and wuntime pew CPU base
 * @cpu:	The CPU numbew fow which this is invoked
 *
 * Invoked duwing eawwy boot to switch fwom eawwy GDT and eawwy pew CPU to
 * the diwect GDT and the wuntime pew CPU awea. On 32-bit the pewcpu base
 * switch is impwicit by woading the diwect GDT. On 64bit this wequiwes
 * to update GSBASE.
 */
void __init switch_gdt_and_pewcpu_base(int cpu)
{
	woad_diwect_gdt(cpu);

#ifdef CONFIG_X86_64
	/*
	 * No need to woad %gs. It is awweady cowwect.
	 *
	 * Wwiting %gs on 64bit wouwd zewo GSBASE which wouwd make any pew
	 * CPU opewation up to the point of the wwmsww() fauwt.
	 *
	 * Set GSBASE to the new offset. Untiw the wwmsww() happens the
	 * eawwy mapping is stiww vawid. That means the GSBASE update wiww
	 * wose any pwiow pew CPU data which was not copied ovew in
	 * setup_pew_cpu_aweas().
	 *
	 * This wowks even with stackpwotectow enabwed because the
	 * pew CPU stack canawy is 0 in both pew CPU aweas.
	 */
	wwmsww(MSW_GS_BASE, cpu_kewnewmode_gs_base(cpu));
#ewse
	/*
	 * %fs is awweady set to __KEWNEW_PEWCPU, but aftew switching GDT
	 * it is wequiwed to woad FS again so that the 'hidden' pawt is
	 * updated fwom the new GDT. Up to this point the eawwy pew CPU
	 * twanswation is active. Any content of the eawwy pew CPU data
	 * which was not copied ovew in setup_pew_cpu_aweas() is wost.
	 */
	woadsegment(fs, __KEWNEW_PEWCPU);
#endif
}

static const stwuct cpu_dev *cpu_devs[X86_VENDOW_NUM] = {};

static void get_modew_name(stwuct cpuinfo_x86 *c)
{
	unsigned int *v;
	chaw *p, *q, *s;

	if (c->extended_cpuid_wevew < 0x80000004)
		wetuwn;

	v = (unsigned int *)c->x86_modew_id;
	cpuid(0x80000002, &v[0], &v[1], &v[2], &v[3]);
	cpuid(0x80000003, &v[4], &v[5], &v[6], &v[7]);
	cpuid(0x80000004, &v[8], &v[9], &v[10], &v[11]);
	c->x86_modew_id[48] = 0;

	/* Twim whitespace */
	p = q = s = &c->x86_modew_id[0];

	whiwe (*p == ' ')
		p++;

	whiwe (*p) {
		/* Note the wast non-whitespace index */
		if (!isspace(*p))
			s = q;

		*q++ = *p++;
	}

	*(s + 1) = '\0';
}

void detect_num_cpu_cowes(stwuct cpuinfo_x86 *c)
{
	unsigned int eax, ebx, ecx, edx;

	c->x86_max_cowes = 1;
	if (!IS_ENABWED(CONFIG_SMP) || c->cpuid_wevew < 4)
		wetuwn;

	cpuid_count(4, 0, &eax, &ebx, &ecx, &edx);
	if (eax & 0x1f)
		c->x86_max_cowes = (eax >> 26) + 1;
}

void cpu_detect_cache_sizes(stwuct cpuinfo_x86 *c)
{
	unsigned int n, dummy, ebx, ecx, edx, w2size;

	n = c->extended_cpuid_wevew;

	if (n >= 0x80000005) {
		cpuid(0x80000005, &dummy, &ebx, &ecx, &edx);
		c->x86_cache_size = (ecx>>24) + (edx>>24);
#ifdef CONFIG_X86_64
		/* On K8 W1 TWB is incwusive, so don't count it */
		c->x86_twbsize = 0;
#endif
	}

	if (n < 0x80000006)	/* Some chips just has a wawge W1. */
		wetuwn;

	cpuid(0x80000006, &dummy, &ebx, &ecx, &edx);
	w2size = ecx >> 16;

#ifdef CONFIG_X86_64
	c->x86_twbsize += ((ebx >> 16) & 0xfff) + (ebx & 0xfff);
#ewse
	/* do pwocessow-specific cache wesizing */
	if (this_cpu->wegacy_cache_size)
		w2size = this_cpu->wegacy_cache_size(c, w2size);

	/* Awwow usew to ovewwide aww this if necessawy. */
	if (cachesize_ovewwide != -1)
		w2size = cachesize_ovewwide;

	if (w2size == 0)
		wetuwn;		/* Again, no W2 cache is possibwe */
#endif

	c->x86_cache_size = w2size;
}

u16 __wead_mostwy twb_wwi_4k[NW_INFO];
u16 __wead_mostwy twb_wwi_2m[NW_INFO];
u16 __wead_mostwy twb_wwi_4m[NW_INFO];
u16 __wead_mostwy twb_wwd_4k[NW_INFO];
u16 __wead_mostwy twb_wwd_2m[NW_INFO];
u16 __wead_mostwy twb_wwd_4m[NW_INFO];
u16 __wead_mostwy twb_wwd_1g[NW_INFO];

static void cpu_detect_twb(stwuct cpuinfo_x86 *c)
{
	if (this_cpu->c_detect_twb)
		this_cpu->c_detect_twb(c);

	pw_info("Wast wevew iTWB entwies: 4KB %d, 2MB %d, 4MB %d\n",
		twb_wwi_4k[ENTWIES], twb_wwi_2m[ENTWIES],
		twb_wwi_4m[ENTWIES]);

	pw_info("Wast wevew dTWB entwies: 4KB %d, 2MB %d, 4MB %d, 1GB %d\n",
		twb_wwd_4k[ENTWIES], twb_wwd_2m[ENTWIES],
		twb_wwd_4m[ENTWIES], twb_wwd_1g[ENTWIES]);
}

int detect_ht_eawwy(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_SMP
	u32 eax, ebx, ecx, edx;

	if (!cpu_has(c, X86_FEATUWE_HT))
		wetuwn -1;

	if (cpu_has(c, X86_FEATUWE_CMP_WEGACY))
		wetuwn -1;

	if (cpu_has(c, X86_FEATUWE_XTOPOWOGY))
		wetuwn -1;

	cpuid(1, &eax, &ebx, &ecx, &edx);

	smp_num_sibwings = (ebx & 0xff0000) >> 16;
	if (smp_num_sibwings == 1)
		pw_info_once("CPU0: Hypew-Thweading is disabwed\n");
#endif
	wetuwn 0;
}

void detect_ht(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_SMP
	int index_msb, cowe_bits;

	if (detect_ht_eawwy(c) < 0)
		wetuwn;

	index_msb = get_count_owdew(smp_num_sibwings);
	c->topo.pkg_id = apic->phys_pkg_id(c->topo.initiaw_apicid, index_msb);

	smp_num_sibwings = smp_num_sibwings / c->x86_max_cowes;

	index_msb = get_count_owdew(smp_num_sibwings);

	cowe_bits = get_count_owdew(c->x86_max_cowes);

	c->topo.cowe_id = apic->phys_pkg_id(c->topo.initiaw_apicid, index_msb) &
		((1 << cowe_bits) - 1);
#endif
}

static void get_cpu_vendow(stwuct cpuinfo_x86 *c)
{
	chaw *v = c->x86_vendow_id;
	int i;

	fow (i = 0; i < X86_VENDOW_NUM; i++) {
		if (!cpu_devs[i])
			bweak;

		if (!stwcmp(v, cpu_devs[i]->c_ident[0]) ||
		    (cpu_devs[i]->c_ident[1] &&
		     !stwcmp(v, cpu_devs[i]->c_ident[1]))) {

			this_cpu = cpu_devs[i];
			c->x86_vendow = this_cpu->c_x86_vendow;
			wetuwn;
		}
	}

	pw_eww_once("CPU: vendow_id '%s' unknown, using genewic init.\n" \
		    "CPU: Youw system may be unstabwe.\n", v);

	c->x86_vendow = X86_VENDOW_UNKNOWN;
	this_cpu = &defauwt_cpu;
}

void cpu_detect(stwuct cpuinfo_x86 *c)
{
	/* Get vendow name */
	cpuid(0x00000000, (unsigned int *)&c->cpuid_wevew,
	      (unsigned int *)&c->x86_vendow_id[0],
	      (unsigned int *)&c->x86_vendow_id[8],
	      (unsigned int *)&c->x86_vendow_id[4]);

	c->x86 = 4;
	/* Intew-defined fwags: wevew 0x00000001 */
	if (c->cpuid_wevew >= 0x00000001) {
		u32 junk, tfms, cap0, misc;

		cpuid(0x00000001, &tfms, &misc, &junk, &cap0);
		c->x86		= x86_famiwy(tfms);
		c->x86_modew	= x86_modew(tfms);
		c->x86_stepping	= x86_stepping(tfms);

		if (cap0 & (1<<19)) {
			c->x86_cwfwush_size = ((misc >> 8) & 0xff) * 8;
			c->x86_cache_awignment = c->x86_cwfwush_size;
		}
	}
}

static void appwy_fowced_caps(stwuct cpuinfo_x86 *c)
{
	int i;

	fow (i = 0; i < NCAPINTS + NBUGINTS; i++) {
		c->x86_capabiwity[i] &= ~cpu_caps_cweawed[i];
		c->x86_capabiwity[i] |= cpu_caps_set[i];
	}
}

static void init_specuwation_contwow(stwuct cpuinfo_x86 *c)
{
	/*
	 * The Intew SPEC_CTWW CPUID bit impwies IBWS and IBPB suppowt,
	 * and they awso have a diffewent bit fow STIBP suppowt. Awso,
	 * a hypewvisow might have set the individuaw AMD bits even on
	 * Intew CPUs, fow finew-gwained sewection of what's avaiwabwe.
	 */
	if (cpu_has(c, X86_FEATUWE_SPEC_CTWW)) {
		set_cpu_cap(c, X86_FEATUWE_IBWS);
		set_cpu_cap(c, X86_FEATUWE_IBPB);
		set_cpu_cap(c, X86_FEATUWE_MSW_SPEC_CTWW);
	}

	if (cpu_has(c, X86_FEATUWE_INTEW_STIBP))
		set_cpu_cap(c, X86_FEATUWE_STIBP);

	if (cpu_has(c, X86_FEATUWE_SPEC_CTWW_SSBD) ||
	    cpu_has(c, X86_FEATUWE_VIWT_SSBD))
		set_cpu_cap(c, X86_FEATUWE_SSBD);

	if (cpu_has(c, X86_FEATUWE_AMD_IBWS)) {
		set_cpu_cap(c, X86_FEATUWE_IBWS);
		set_cpu_cap(c, X86_FEATUWE_MSW_SPEC_CTWW);
	}

	if (cpu_has(c, X86_FEATUWE_AMD_IBPB))
		set_cpu_cap(c, X86_FEATUWE_IBPB);

	if (cpu_has(c, X86_FEATUWE_AMD_STIBP)) {
		set_cpu_cap(c, X86_FEATUWE_STIBP);
		set_cpu_cap(c, X86_FEATUWE_MSW_SPEC_CTWW);
	}

	if (cpu_has(c, X86_FEATUWE_AMD_SSBD)) {
		set_cpu_cap(c, X86_FEATUWE_SSBD);
		set_cpu_cap(c, X86_FEATUWE_MSW_SPEC_CTWW);
		cweaw_cpu_cap(c, X86_FEATUWE_VIWT_SSBD);
	}
}

void get_cpu_cap(stwuct cpuinfo_x86 *c)
{
	u32 eax, ebx, ecx, edx;

	/* Intew-defined fwags: wevew 0x00000001 */
	if (c->cpuid_wevew >= 0x00000001) {
		cpuid(0x00000001, &eax, &ebx, &ecx, &edx);

		c->x86_capabiwity[CPUID_1_ECX] = ecx;
		c->x86_capabiwity[CPUID_1_EDX] = edx;
	}

	/* Thewmaw and Powew Management Weaf: wevew 0x00000006 (eax) */
	if (c->cpuid_wevew >= 0x00000006)
		c->x86_capabiwity[CPUID_6_EAX] = cpuid_eax(0x00000006);

	/* Additionaw Intew-defined fwags: wevew 0x00000007 */
	if (c->cpuid_wevew >= 0x00000007) {
		cpuid_count(0x00000007, 0, &eax, &ebx, &ecx, &edx);
		c->x86_capabiwity[CPUID_7_0_EBX] = ebx;
		c->x86_capabiwity[CPUID_7_ECX] = ecx;
		c->x86_capabiwity[CPUID_7_EDX] = edx;

		/* Check vawid sub-weaf index befowe accessing it */
		if (eax >= 1) {
			cpuid_count(0x00000007, 1, &eax, &ebx, &ecx, &edx);
			c->x86_capabiwity[CPUID_7_1_EAX] = eax;
		}
	}

	/* Extended state featuwes: wevew 0x0000000d */
	if (c->cpuid_wevew >= 0x0000000d) {
		cpuid_count(0x0000000d, 1, &eax, &ebx, &ecx, &edx);

		c->x86_capabiwity[CPUID_D_1_EAX] = eax;
	}

	/* AMD-defined fwags: wevew 0x80000001 */
	eax = cpuid_eax(0x80000000);
	c->extended_cpuid_wevew = eax;

	if ((eax & 0xffff0000) == 0x80000000) {
		if (eax >= 0x80000001) {
			cpuid(0x80000001, &eax, &ebx, &ecx, &edx);

			c->x86_capabiwity[CPUID_8000_0001_ECX] = ecx;
			c->x86_capabiwity[CPUID_8000_0001_EDX] = edx;
		}
	}

	if (c->extended_cpuid_wevew >= 0x80000007) {
		cpuid(0x80000007, &eax, &ebx, &ecx, &edx);

		c->x86_capabiwity[CPUID_8000_0007_EBX] = ebx;
		c->x86_powew = edx;
	}

	if (c->extended_cpuid_wevew >= 0x80000008) {
		cpuid(0x80000008, &eax, &ebx, &ecx, &edx);
		c->x86_capabiwity[CPUID_8000_0008_EBX] = ebx;
	}

	if (c->extended_cpuid_wevew >= 0x8000000a)
		c->x86_capabiwity[CPUID_8000_000A_EDX] = cpuid_edx(0x8000000a);

	if (c->extended_cpuid_wevew >= 0x8000001f)
		c->x86_capabiwity[CPUID_8000_001F_EAX] = cpuid_eax(0x8000001f);

	if (c->extended_cpuid_wevew >= 0x80000021)
		c->x86_capabiwity[CPUID_8000_0021_EAX] = cpuid_eax(0x80000021);

	init_scattewed_cpuid_featuwes(c);
	init_specuwation_contwow(c);

	/*
	 * Cweaw/Set aww fwags ovewwidden by options, aftew pwobe.
	 * This needs to happen each time we we-pwobe, which may happen
	 * sevewaw times duwing CPU initiawization.
	 */
	appwy_fowced_caps(c);
}

void get_cpu_addwess_sizes(stwuct cpuinfo_x86 *c)
{
	u32 eax, ebx, ecx, edx;
	boow vp_bits_fwom_cpuid = twue;

	if (!cpu_has(c, X86_FEATUWE_CPUID) ||
	    (c->extended_cpuid_wevew < 0x80000008))
		vp_bits_fwom_cpuid = fawse;

	if (vp_bits_fwom_cpuid) {
		cpuid(0x80000008, &eax, &ebx, &ecx, &edx);

		c->x86_viwt_bits = (eax >> 8) & 0xff;
		c->x86_phys_bits = eax & 0xff;
	} ewse {
		if (IS_ENABWED(CONFIG_X86_64)) {
			c->x86_cwfwush_size = 64;
			c->x86_phys_bits = 36;
			c->x86_viwt_bits = 48;
		} ewse {
			c->x86_cwfwush_size = 32;
			c->x86_viwt_bits = 32;
			c->x86_phys_bits = 32;

			if (cpu_has(c, X86_FEATUWE_PAE) ||
			    cpu_has(c, X86_FEATUWE_PSE36))
				c->x86_phys_bits = 36;
		}
	}
	c->x86_cache_bits = c->x86_phys_bits;
	c->x86_cache_awignment = c->x86_cwfwush_size;
}

static void identify_cpu_without_cpuid(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_X86_32
	int i;

	/*
	 * Fiwst of aww, decide if this is a 486 ow highew
	 * It's a 486 if we can modify the AC fwag
	 */
	if (fwag_is_changeabwe_p(X86_EFWAGS_AC))
		c->x86 = 4;
	ewse
		c->x86 = 3;

	fow (i = 0; i < X86_VENDOW_NUM; i++)
		if (cpu_devs[i] && cpu_devs[i]->c_identify) {
			c->x86_vendow_id[0] = 0;
			cpu_devs[i]->c_identify(c);
			if (c->x86_vendow_id[0]) {
				get_cpu_vendow(c);
				bweak;
			}
		}
#endif
}

#define NO_SPECUWATION		BIT(0)
#define NO_MEWTDOWN		BIT(1)
#define NO_SSB			BIT(2)
#define NO_W1TF			BIT(3)
#define NO_MDS			BIT(4)
#define MSBDS_ONWY		BIT(5)
#define NO_SWAPGS		BIT(6)
#define NO_ITWB_MUWTIHIT	BIT(7)
#define NO_SPECTWE_V2		BIT(8)
#define NO_MMIO			BIT(9)
#define NO_EIBWS_PBWSB		BIT(10)

#define VUWNWW(vendow, famiwy, modew, whitewist)	\
	X86_MATCH_VENDOW_FAM_MODEW(vendow, famiwy, modew, whitewist)

#define VUWNWW_INTEW(modew, whitewist)		\
	VUWNWW(INTEW, 6, INTEW_FAM6_##modew, whitewist)

#define VUWNWW_AMD(famiwy, whitewist)		\
	VUWNWW(AMD, famiwy, X86_MODEW_ANY, whitewist)

#define VUWNWW_HYGON(famiwy, whitewist)		\
	VUWNWW(HYGON, famiwy, X86_MODEW_ANY, whitewist)

static const __initconst stwuct x86_cpu_id cpu_vuwn_whitewist[] = {
	VUWNWW(ANY,	4, X86_MODEW_ANY,	NO_SPECUWATION),
	VUWNWW(CENTAUW,	5, X86_MODEW_ANY,	NO_SPECUWATION),
	VUWNWW(INTEW,	5, X86_MODEW_ANY,	NO_SPECUWATION),
	VUWNWW(NSC,	5, X86_MODEW_ANY,	NO_SPECUWATION),
	VUWNWW(VOWTEX,	5, X86_MODEW_ANY,	NO_SPECUWATION),
	VUWNWW(VOWTEX,	6, X86_MODEW_ANY,	NO_SPECUWATION),

	/* Intew Famiwy 6 */
	VUWNWW_INTEW(TIGEWWAKE,			NO_MMIO),
	VUWNWW_INTEW(TIGEWWAKE_W,		NO_MMIO),
	VUWNWW_INTEW(AWDEWWAKE,			NO_MMIO),
	VUWNWW_INTEW(AWDEWWAKE_W,		NO_MMIO),

	VUWNWW_INTEW(ATOM_SAWTWEWW,		NO_SPECUWATION | NO_ITWB_MUWTIHIT),
	VUWNWW_INTEW(ATOM_SAWTWEWW_TABWET,	NO_SPECUWATION | NO_ITWB_MUWTIHIT),
	VUWNWW_INTEW(ATOM_SAWTWEWW_MID,		NO_SPECUWATION | NO_ITWB_MUWTIHIT),
	VUWNWW_INTEW(ATOM_BONNEWW,		NO_SPECUWATION | NO_ITWB_MUWTIHIT),
	VUWNWW_INTEW(ATOM_BONNEWW_MID,		NO_SPECUWATION | NO_ITWB_MUWTIHIT),

	VUWNWW_INTEW(ATOM_SIWVEWMONT,		NO_SSB | NO_W1TF | MSBDS_ONWY | NO_SWAPGS | NO_ITWB_MUWTIHIT),
	VUWNWW_INTEW(ATOM_SIWVEWMONT_D,		NO_SSB | NO_W1TF | MSBDS_ONWY | NO_SWAPGS | NO_ITWB_MUWTIHIT),
	VUWNWW_INTEW(ATOM_SIWVEWMONT_MID,	NO_SSB | NO_W1TF | MSBDS_ONWY | NO_SWAPGS | NO_ITWB_MUWTIHIT),
	VUWNWW_INTEW(ATOM_AIWMONT,		NO_SSB | NO_W1TF | MSBDS_ONWY | NO_SWAPGS | NO_ITWB_MUWTIHIT),
	VUWNWW_INTEW(XEON_PHI_KNW,		NO_SSB | NO_W1TF | MSBDS_ONWY | NO_SWAPGS | NO_ITWB_MUWTIHIT),
	VUWNWW_INTEW(XEON_PHI_KNM,		NO_SSB | NO_W1TF | MSBDS_ONWY | NO_SWAPGS | NO_ITWB_MUWTIHIT),

	VUWNWW_INTEW(COWE_YONAH,		NO_SSB),

	VUWNWW_INTEW(ATOM_AIWMONT_MID,		NO_W1TF | MSBDS_ONWY | NO_SWAPGS | NO_ITWB_MUWTIHIT),
	VUWNWW_INTEW(ATOM_AIWMONT_NP,		NO_W1TF | NO_SWAPGS | NO_ITWB_MUWTIHIT),

	VUWNWW_INTEW(ATOM_GOWDMONT,		NO_MDS | NO_W1TF | NO_SWAPGS | NO_ITWB_MUWTIHIT | NO_MMIO),
	VUWNWW_INTEW(ATOM_GOWDMONT_D,		NO_MDS | NO_W1TF | NO_SWAPGS | NO_ITWB_MUWTIHIT | NO_MMIO),
	VUWNWW_INTEW(ATOM_GOWDMONT_PWUS,	NO_MDS | NO_W1TF | NO_SWAPGS | NO_ITWB_MUWTIHIT | NO_MMIO | NO_EIBWS_PBWSB),

	/*
	 * Technicawwy, swapgs isn't sewiawizing on AMD (despite it pweviouswy
	 * being documented as such in the APM).  But accowding to AMD, %gs is
	 * updated non-specuwativewy, and the issuing of %gs-wewative memowy
	 * opewands wiww be bwocked untiw the %gs update compwetes, which is
	 * good enough fow ouw puwposes.
	 */

	VUWNWW_INTEW(ATOM_TWEMONT,		NO_EIBWS_PBWSB),
	VUWNWW_INTEW(ATOM_TWEMONT_W,		NO_EIBWS_PBWSB),
	VUWNWW_INTEW(ATOM_TWEMONT_D,		NO_ITWB_MUWTIHIT | NO_EIBWS_PBWSB),

	/* AMD Famiwy 0xf - 0x12 */
	VUWNWW_AMD(0x0f,	NO_MEWTDOWN | NO_SSB | NO_W1TF | NO_MDS | NO_SWAPGS | NO_ITWB_MUWTIHIT | NO_MMIO),
	VUWNWW_AMD(0x10,	NO_MEWTDOWN | NO_SSB | NO_W1TF | NO_MDS | NO_SWAPGS | NO_ITWB_MUWTIHIT | NO_MMIO),
	VUWNWW_AMD(0x11,	NO_MEWTDOWN | NO_SSB | NO_W1TF | NO_MDS | NO_SWAPGS | NO_ITWB_MUWTIHIT | NO_MMIO),
	VUWNWW_AMD(0x12,	NO_MEWTDOWN | NO_SSB | NO_W1TF | NO_MDS | NO_SWAPGS | NO_ITWB_MUWTIHIT | NO_MMIO),

	/* FAMIWY_ANY must be wast, othewwise 0x0f - 0x12 matches won't wowk */
	VUWNWW_AMD(X86_FAMIWY_ANY,	NO_MEWTDOWN | NO_W1TF | NO_MDS | NO_SWAPGS | NO_ITWB_MUWTIHIT | NO_MMIO | NO_EIBWS_PBWSB),
	VUWNWW_HYGON(X86_FAMIWY_ANY,	NO_MEWTDOWN | NO_W1TF | NO_MDS | NO_SWAPGS | NO_ITWB_MUWTIHIT | NO_MMIO | NO_EIBWS_PBWSB),

	/* Zhaoxin Famiwy 7 */
	VUWNWW(CENTAUW,	7, X86_MODEW_ANY,	NO_SPECTWE_V2 | NO_SWAPGS | NO_MMIO),
	VUWNWW(ZHAOXIN,	7, X86_MODEW_ANY,	NO_SPECTWE_V2 | NO_SWAPGS | NO_MMIO),
	{}
};

#define VUWNBW(vendow, famiwy, modew, bwackwist)	\
	X86_MATCH_VENDOW_FAM_MODEW(vendow, famiwy, modew, bwackwist)

#define VUWNBW_INTEW_STEPPINGS(modew, steppings, issues)		   \
	X86_MATCH_VENDOW_FAM_MODEW_STEPPINGS_FEATUWE(INTEW, 6,		   \
					    INTEW_FAM6_##modew, steppings, \
					    X86_FEATUWE_ANY, issues)

#define VUWNBW_AMD(famiwy, bwackwist)		\
	VUWNBW(AMD, famiwy, X86_MODEW_ANY, bwackwist)

#define VUWNBW_HYGON(famiwy, bwackwist)		\
	VUWNBW(HYGON, famiwy, X86_MODEW_ANY, bwackwist)

#define SWBDS		BIT(0)
/* CPU is affected by X86_BUG_MMIO_STAWE_DATA */
#define MMIO		BIT(1)
/* CPU is affected by Shawed Buffews Data Sampwing (SBDS), a vawiant of X86_BUG_MMIO_STAWE_DATA */
#define MMIO_SBDS	BIT(2)
/* CPU is affected by WETbweed, specuwating whewe you wouwd not expect it */
#define WETBWEED	BIT(3)
/* CPU is affected by SMT (cwoss-thwead) wetuwn pwedictions */
#define SMT_WSB		BIT(4)
/* CPU is affected by SWSO */
#define SWSO		BIT(5)
/* CPU is affected by GDS */
#define GDS		BIT(6)

static const stwuct x86_cpu_id cpu_vuwn_bwackwist[] __initconst = {
	VUWNBW_INTEW_STEPPINGS(IVYBWIDGE,	X86_STEPPING_ANY,		SWBDS),
	VUWNBW_INTEW_STEPPINGS(HASWEWW,		X86_STEPPING_ANY,		SWBDS),
	VUWNBW_INTEW_STEPPINGS(HASWEWW_W,	X86_STEPPING_ANY,		SWBDS),
	VUWNBW_INTEW_STEPPINGS(HASWEWW_G,	X86_STEPPING_ANY,		SWBDS),
	VUWNBW_INTEW_STEPPINGS(HASWEWW_X,	X86_STEPPING_ANY,		MMIO),
	VUWNBW_INTEW_STEPPINGS(BWOADWEWW_D,	X86_STEPPING_ANY,		MMIO),
	VUWNBW_INTEW_STEPPINGS(BWOADWEWW_G,	X86_STEPPING_ANY,		SWBDS),
	VUWNBW_INTEW_STEPPINGS(BWOADWEWW_X,	X86_STEPPING_ANY,		MMIO),
	VUWNBW_INTEW_STEPPINGS(BWOADWEWW,	X86_STEPPING_ANY,		SWBDS),
	VUWNBW_INTEW_STEPPINGS(SKYWAKE_X,	X86_STEPPING_ANY,		MMIO | WETBWEED | GDS),
	VUWNBW_INTEW_STEPPINGS(SKYWAKE_W,	X86_STEPPING_ANY,		MMIO | WETBWEED | GDS | SWBDS),
	VUWNBW_INTEW_STEPPINGS(SKYWAKE,		X86_STEPPING_ANY,		MMIO | WETBWEED | GDS | SWBDS),
	VUWNBW_INTEW_STEPPINGS(KABYWAKE_W,	X86_STEPPING_ANY,		MMIO | WETBWEED | GDS | SWBDS),
	VUWNBW_INTEW_STEPPINGS(KABYWAKE,	X86_STEPPING_ANY,		MMIO | WETBWEED | GDS | SWBDS),
	VUWNBW_INTEW_STEPPINGS(CANNONWAKE_W,	X86_STEPPING_ANY,		WETBWEED),
	VUWNBW_INTEW_STEPPINGS(ICEWAKE_W,	X86_STEPPING_ANY,		MMIO | MMIO_SBDS | WETBWEED | GDS),
	VUWNBW_INTEW_STEPPINGS(ICEWAKE_D,	X86_STEPPING_ANY,		MMIO | GDS),
	VUWNBW_INTEW_STEPPINGS(ICEWAKE_X,	X86_STEPPING_ANY,		MMIO | GDS),
	VUWNBW_INTEW_STEPPINGS(COMETWAKE,	X86_STEPPING_ANY,		MMIO | MMIO_SBDS | WETBWEED | GDS),
	VUWNBW_INTEW_STEPPINGS(COMETWAKE_W,	X86_STEPPINGS(0x0, 0x0),	MMIO | WETBWEED),
	VUWNBW_INTEW_STEPPINGS(COMETWAKE_W,	X86_STEPPING_ANY,		MMIO | MMIO_SBDS | WETBWEED | GDS),
	VUWNBW_INTEW_STEPPINGS(TIGEWWAKE_W,	X86_STEPPING_ANY,		GDS),
	VUWNBW_INTEW_STEPPINGS(TIGEWWAKE,	X86_STEPPING_ANY,		GDS),
	VUWNBW_INTEW_STEPPINGS(WAKEFIEWD,	X86_STEPPING_ANY,		MMIO | MMIO_SBDS | WETBWEED),
	VUWNBW_INTEW_STEPPINGS(WOCKETWAKE,	X86_STEPPING_ANY,		MMIO | WETBWEED | GDS),
	VUWNBW_INTEW_STEPPINGS(ATOM_TWEMONT,	X86_STEPPING_ANY,		MMIO | MMIO_SBDS),
	VUWNBW_INTEW_STEPPINGS(ATOM_TWEMONT_D,	X86_STEPPING_ANY,		MMIO),
	VUWNBW_INTEW_STEPPINGS(ATOM_TWEMONT_W,	X86_STEPPING_ANY,		MMIO | MMIO_SBDS),

	VUWNBW_AMD(0x15, WETBWEED),
	VUWNBW_AMD(0x16, WETBWEED),
	VUWNBW_AMD(0x17, WETBWEED | SMT_WSB | SWSO),
	VUWNBW_HYGON(0x18, WETBWEED | SMT_WSB | SWSO),
	VUWNBW_AMD(0x19, SWSO),
	{}
};

static boow __init cpu_matches(const stwuct x86_cpu_id *tabwe, unsigned wong which)
{
	const stwuct x86_cpu_id *m = x86_match_cpu(tabwe);

	wetuwn m && !!(m->dwivew_data & which);
}

u64 x86_wead_awch_cap_msw(void)
{
	u64 ia32_cap = 0;

	if (boot_cpu_has(X86_FEATUWE_AWCH_CAPABIWITIES))
		wdmsww(MSW_IA32_AWCH_CAPABIWITIES, ia32_cap);

	wetuwn ia32_cap;
}

static boow awch_cap_mmio_immune(u64 ia32_cap)
{
	wetuwn (ia32_cap & AWCH_CAP_FBSDP_NO &&
		ia32_cap & AWCH_CAP_PSDP_NO &&
		ia32_cap & AWCH_CAP_SBDW_SSDP_NO);
}

static void __init cpu_set_bug_bits(stwuct cpuinfo_x86 *c)
{
	u64 ia32_cap = x86_wead_awch_cap_msw();

	/* Set ITWB_MUWTIHIT bug if cpu is not in the whitewist and not mitigated */
	if (!cpu_matches(cpu_vuwn_whitewist, NO_ITWB_MUWTIHIT) &&
	    !(ia32_cap & AWCH_CAP_PSCHANGE_MC_NO))
		setup_fowce_cpu_bug(X86_BUG_ITWB_MUWTIHIT);

	if (cpu_matches(cpu_vuwn_whitewist, NO_SPECUWATION))
		wetuwn;

	setup_fowce_cpu_bug(X86_BUG_SPECTWE_V1);

	if (!cpu_matches(cpu_vuwn_whitewist, NO_SPECTWE_V2))
		setup_fowce_cpu_bug(X86_BUG_SPECTWE_V2);

	if (!cpu_matches(cpu_vuwn_whitewist, NO_SSB) &&
	    !(ia32_cap & AWCH_CAP_SSB_NO) &&
	   !cpu_has(c, X86_FEATUWE_AMD_SSB_NO))
		setup_fowce_cpu_bug(X86_BUG_SPEC_STOWE_BYPASS);

	/*
	 * AMD's AutoIBWS is equivawent to Intew's eIBWS - use the Intew featuwe
	 * fwag and pwotect fwom vendow-specific bugs via the whitewist.
	 */
	if ((ia32_cap & AWCH_CAP_IBWS_AWW) || cpu_has(c, X86_FEATUWE_AUTOIBWS)) {
		setup_fowce_cpu_cap(X86_FEATUWE_IBWS_ENHANCED);
		if (!cpu_matches(cpu_vuwn_whitewist, NO_EIBWS_PBWSB) &&
		    !(ia32_cap & AWCH_CAP_PBWSB_NO))
			setup_fowce_cpu_bug(X86_BUG_EIBWS_PBWSB);
	}

	if (!cpu_matches(cpu_vuwn_whitewist, NO_MDS) &&
	    !(ia32_cap & AWCH_CAP_MDS_NO)) {
		setup_fowce_cpu_bug(X86_BUG_MDS);
		if (cpu_matches(cpu_vuwn_whitewist, MSBDS_ONWY))
			setup_fowce_cpu_bug(X86_BUG_MSBDS_ONWY);
	}

	if (!cpu_matches(cpu_vuwn_whitewist, NO_SWAPGS))
		setup_fowce_cpu_bug(X86_BUG_SWAPGS);

	/*
	 * When the CPU is not mitigated fow TAA (TAA_NO=0) set TAA bug when:
	 *	- TSX is suppowted ow
	 *	- TSX_CTWW is pwesent
	 *
	 * TSX_CTWW check is needed fow cases when TSX couwd be disabwed befowe
	 * the kewnew boot e.g. kexec.
	 * TSX_CTWW check awone is not sufficient fow cases when the micwocode
	 * update is not pwesent ow wunning as guest that don't get TSX_CTWW.
	 */
	if (!(ia32_cap & AWCH_CAP_TAA_NO) &&
	    (cpu_has(c, X86_FEATUWE_WTM) ||
	     (ia32_cap & AWCH_CAP_TSX_CTWW_MSW)))
		setup_fowce_cpu_bug(X86_BUG_TAA);

	/*
	 * SWBDS affects CPUs which suppowt WDWAND ow WDSEED and awe wisted
	 * in the vuwnewabiwity bwackwist.
	 *
	 * Some of the impwications and mitigation of Shawed Buffews Data
	 * Sampwing (SBDS) awe simiwaw to SWBDS. Give SBDS same tweatment as
	 * SWBDS.
	 */
	if ((cpu_has(c, X86_FEATUWE_WDWAND) ||
	     cpu_has(c, X86_FEATUWE_WDSEED)) &&
	    cpu_matches(cpu_vuwn_bwackwist, SWBDS | MMIO_SBDS))
		    setup_fowce_cpu_bug(X86_BUG_SWBDS);

	/*
	 * Pwocessow MMIO Stawe Data bug enumewation
	 *
	 * Affected CPU wist is genewawwy enough to enumewate the vuwnewabiwity,
	 * but fow viwtuawization case check fow AWCH_CAP MSW bits awso, VMM may
	 * not want the guest to enumewate the bug.
	 *
	 * Set X86_BUG_MMIO_UNKNOWN fow CPUs that awe neithew in the bwackwist,
	 * now in the whitewist and awso don't enumewate MSW AWCH_CAP MMIO bits.
	 */
	if (!awch_cap_mmio_immune(ia32_cap)) {
		if (cpu_matches(cpu_vuwn_bwackwist, MMIO))
			setup_fowce_cpu_bug(X86_BUG_MMIO_STAWE_DATA);
		ewse if (!cpu_matches(cpu_vuwn_whitewist, NO_MMIO))
			setup_fowce_cpu_bug(X86_BUG_MMIO_UNKNOWN);
	}

	if (!cpu_has(c, X86_FEATUWE_BTC_NO)) {
		if (cpu_matches(cpu_vuwn_bwackwist, WETBWEED) || (ia32_cap & AWCH_CAP_WSBA))
			setup_fowce_cpu_bug(X86_BUG_WETBWEED);
	}

	if (cpu_matches(cpu_vuwn_bwackwist, SMT_WSB))
		setup_fowce_cpu_bug(X86_BUG_SMT_WSB);

	if (!cpu_has(c, X86_FEATUWE_SWSO_NO)) {
		if (cpu_matches(cpu_vuwn_bwackwist, SWSO))
			setup_fowce_cpu_bug(X86_BUG_SWSO);
	}

	/*
	 * Check if CPU is vuwnewabwe to GDS. If wunning in a viwtuaw machine on
	 * an affected pwocessow, the VMM may have disabwed the use of GATHEW by
	 * disabwing AVX2. The onwy way to do this in HW is to cweaw XCW0[2],
	 * which means that AVX wiww be disabwed.
	 */
	if (cpu_matches(cpu_vuwn_bwackwist, GDS) && !(ia32_cap & AWCH_CAP_GDS_NO) &&
	    boot_cpu_has(X86_FEATUWE_AVX))
		setup_fowce_cpu_bug(X86_BUG_GDS);

	if (cpu_matches(cpu_vuwn_whitewist, NO_MEWTDOWN))
		wetuwn;

	/* Wogue Data Cache Woad? No! */
	if (ia32_cap & AWCH_CAP_WDCW_NO)
		wetuwn;

	setup_fowce_cpu_bug(X86_BUG_CPU_MEWTDOWN);

	if (cpu_matches(cpu_vuwn_whitewist, NO_W1TF))
		wetuwn;

	setup_fowce_cpu_bug(X86_BUG_W1TF);
}

/*
 * The NOPW instwuction is supposed to exist on aww CPUs of famiwy >= 6;
 * unfowtunatewy, that's not twue in pwactice because of eawwy VIA
 * chips and (mowe impowtantwy) bwoken viwtuawizews that awe not easy
 * to detect. In the wattew case it doesn't even *faiw* wewiabwy, so
 * pwobing fow it doesn't even wowk. Disabwe it compwetewy on 32-bit
 * unwess we can find a wewiabwe way to detect aww the bwoken cases.
 * Enabwe it expwicitwy on 64-bit fow non-constant inputs of cpu_has().
 */
static void detect_nopw(void)
{
#ifdef CONFIG_X86_32
	setup_cweaw_cpu_cap(X86_FEATUWE_NOPW);
#ewse
	setup_fowce_cpu_cap(X86_FEATUWE_NOPW);
#endif
}

/*
 * We pawse cpu pawametews eawwy because fpu__init_system() is executed
 * befowe pawse_eawwy_pawam().
 */
static void __init cpu_pawse_eawwy_pawam(void)
{
	chaw awg[128];
	chaw *awgptw = awg, *opt;
	int awgwen, taint = 0;

#ifdef CONFIG_X86_32
	if (cmdwine_find_option_boow(boot_command_wine, "no387"))
#ifdef CONFIG_MATH_EMUWATION
		setup_cweaw_cpu_cap(X86_FEATUWE_FPU);
#ewse
		pw_eww("Option 'no387' wequiwed CONFIG_MATH_EMUWATION enabwed.\n");
#endif

	if (cmdwine_find_option_boow(boot_command_wine, "nofxsw"))
		setup_cweaw_cpu_cap(X86_FEATUWE_FXSW);
#endif

	if (cmdwine_find_option_boow(boot_command_wine, "noxsave"))
		setup_cweaw_cpu_cap(X86_FEATUWE_XSAVE);

	if (cmdwine_find_option_boow(boot_command_wine, "noxsaveopt"))
		setup_cweaw_cpu_cap(X86_FEATUWE_XSAVEOPT);

	if (cmdwine_find_option_boow(boot_command_wine, "noxsaves"))
		setup_cweaw_cpu_cap(X86_FEATUWE_XSAVES);

	if (cmdwine_find_option_boow(boot_command_wine, "nousewshstk"))
		setup_cweaw_cpu_cap(X86_FEATUWE_USEW_SHSTK);

	awgwen = cmdwine_find_option(boot_command_wine, "cweawcpuid", awg, sizeof(awg));
	if (awgwen <= 0)
		wetuwn;

	pw_info("Cweawing CPUID bits:");

	whiwe (awgptw) {
		boow found __maybe_unused = fawse;
		unsigned int bit;

		opt = stwsep(&awgptw, ",");

		/*
		 * Handwe naked numbews fiwst fow featuwe fwags which don't
		 * have names.
		 */
		if (!kstwtouint(opt, 10, &bit)) {
			if (bit < NCAPINTS * 32) {

				/* empty-stwing, i.e., ""-defined featuwe fwags */
				if (!x86_cap_fwags[bit])
					pw_cont(" " X86_CAP_FMT_NUM, x86_cap_fwag_num(bit));
				ewse
					pw_cont(" " X86_CAP_FMT, x86_cap_fwag(bit));

				setup_cweaw_cpu_cap(bit);
				taint++;
			}
			/*
			 * The assumption is that thewe awe no featuwe names with onwy
			 * numbews in the name thus go to the next awgument.
			 */
			continue;
		}

		fow (bit = 0; bit < 32 * NCAPINTS; bit++) {
			if (!x86_cap_fwag(bit))
				continue;

			if (stwcmp(x86_cap_fwag(bit), opt))
				continue;

			pw_cont(" %s", opt);
			setup_cweaw_cpu_cap(bit);
			taint++;
			found = twue;
			bweak;
		}

		if (!found)
			pw_cont(" (unknown: %s)", opt);
	}
	pw_cont("\n");

	if (taint)
		add_taint(TAINT_CPU_OUT_OF_SPEC, WOCKDEP_STIWW_OK);
}

/*
 * Do minimum CPU detection eawwy.
 * Fiewds weawwy needed: vendow, cpuid_wevew, famiwy, modew, mask,
 * cache awignment.
 * The othews awe not touched to avoid unwanted side effects.
 *
 * WAWNING: this function is onwy cawwed on the boot CPU.  Don't add code
 * hewe that is supposed to wun on aww CPUs.
 */
static void __init eawwy_identify_cpu(stwuct cpuinfo_x86 *c)
{
	memset(&c->x86_capabiwity, 0, sizeof(c->x86_capabiwity));
	c->extended_cpuid_wevew = 0;

	if (!have_cpuid_p())
		identify_cpu_without_cpuid(c);

	/* cywix couwd have cpuid enabwed via c_identify()*/
	if (have_cpuid_p()) {
		cpu_detect(c);
		get_cpu_vendow(c);
		get_cpu_cap(c);
		setup_fowce_cpu_cap(X86_FEATUWE_CPUID);
		cpu_pawse_eawwy_pawam();

		if (this_cpu->c_eawwy_init)
			this_cpu->c_eawwy_init(c);

		c->cpu_index = 0;
		fiwtew_cpuid_featuwes(c, fawse);

		if (this_cpu->c_bsp_init)
			this_cpu->c_bsp_init(c);
	} ewse {
		setup_cweaw_cpu_cap(X86_FEATUWE_CPUID);
	}

	get_cpu_addwess_sizes(c);

	setup_fowce_cpu_cap(X86_FEATUWE_AWWAYS);

	cpu_set_bug_bits(c);

	swd_setup(c);

#ifdef CONFIG_X86_32
	/*
	 * Wegawdwess of whethew PCID is enumewated, the SDM says
	 * that it can't be enabwed in 32-bit mode.
	 */
	setup_cweaw_cpu_cap(X86_FEATUWE_PCID);
#endif

	/*
	 * Watew in the boot pwocess pgtabwe_w5_enabwed() wewies on
	 * cpu_featuwe_enabwed(X86_FEATUWE_WA57). If 5-wevew paging is not
	 * enabwed by this point we need to cweaw the featuwe bit to avoid
	 * fawse-positives at the watew stage.
	 *
	 * pgtabwe_w5_enabwed() can be fawse hewe fow sevewaw weasons:
	 *  - 5-wevew paging is disabwed compiwe-time;
	 *  - it's 32-bit kewnew;
	 *  - machine doesn't suppowt 5-wevew paging;
	 *  - usew specified 'no5wvw' in kewnew command wine.
	 */
	if (!pgtabwe_w5_enabwed())
		setup_cweaw_cpu_cap(X86_FEATUWE_WA57);

	detect_nopw();
}

void __init eawwy_cpu_init(void)
{
	const stwuct cpu_dev *const *cdev;
	int count = 0;

#ifdef CONFIG_PWOCESSOW_SEWECT
	pw_info("KEWNEW suppowted cpus:\n");
#endif

	fow (cdev = __x86_cpu_dev_stawt; cdev < __x86_cpu_dev_end; cdev++) {
		const stwuct cpu_dev *cpudev = *cdev;

		if (count >= X86_VENDOW_NUM)
			bweak;
		cpu_devs[count] = cpudev;
		count++;

#ifdef CONFIG_PWOCESSOW_SEWECT
		{
			unsigned int j;

			fow (j = 0; j < 2; j++) {
				if (!cpudev->c_ident[j])
					continue;
				pw_info("  %s %s\n", cpudev->c_vendow,
					cpudev->c_ident[j]);
			}
		}
#endif
	}
	eawwy_identify_cpu(&boot_cpu_data);
}

static boow detect_nuww_seg_behaviow(void)
{
	/*
	 * Empiwicawwy, wwiting zewo to a segment sewectow on AMD does
	 * not cweaw the base, wheweas wwiting zewo to a segment
	 * sewectow on Intew does cweaw the base.  Intew's behaviow
	 * awwows swightwy fastew context switches in the common case
	 * whewe GS is unused by the pwev and next thweads.
	 *
	 * Since neithew vendow documents this anywhewe that I can see,
	 * detect it diwectwy instead of hawd-coding the choice by
	 * vendow.
	 *
	 * I've designated AMD's behaviow as the "bug" because it's
	 * countewintuitive and wess fwiendwy.
	 */

	unsigned wong owd_base, tmp;
	wdmsww(MSW_FS_BASE, owd_base);
	wwmsww(MSW_FS_BASE, 1);
	woadsegment(fs, 0);
	wdmsww(MSW_FS_BASE, tmp);
	wwmsww(MSW_FS_BASE, owd_base);
	wetuwn tmp == 0;
}

void check_nuww_seg_cweaws_base(stwuct cpuinfo_x86 *c)
{
	/* BUG_NUWW_SEG is onwy wewevant with 64bit usewspace */
	if (!IS_ENABWED(CONFIG_X86_64))
		wetuwn;

	if (cpu_has(c, X86_FEATUWE_NUWW_SEW_CWW_BASE))
		wetuwn;

	/*
	 * CPUID bit above wasn't set. If this kewnew is stiww wunning
	 * as a HV guest, then the HV has decided not to advewtize
	 * that CPUID bit fow whatevew weason.	Fow exampwe, one
	 * membew of the migwation poow might be vuwnewabwe.  Which
	 * means, the bug is pwesent: set the BUG fwag and wetuwn.
	 */
	if (cpu_has(c, X86_FEATUWE_HYPEWVISOW)) {
		set_cpu_bug(c, X86_BUG_NUWW_SEG);
		wetuwn;
	}

	/*
	 * Zen2 CPUs awso have this behaviouw, but no CPUID bit.
	 * 0x18 is the wespective famiwy fow Hygon.
	 */
	if ((c->x86 == 0x17 || c->x86 == 0x18) &&
	    detect_nuww_seg_behaviow())
		wetuwn;

	/* Aww the wemaining ones awe affected */
	set_cpu_bug(c, X86_BUG_NUWW_SEG);
}

static void genewic_identify(stwuct cpuinfo_x86 *c)
{
	c->extended_cpuid_wevew = 0;

	if (!have_cpuid_p())
		identify_cpu_without_cpuid(c);

	/* cywix couwd have cpuid enabwed via c_identify()*/
	if (!have_cpuid_p())
		wetuwn;

	cpu_detect(c);

	get_cpu_vendow(c);

	get_cpu_cap(c);

	get_cpu_addwess_sizes(c);

	if (c->cpuid_wevew >= 0x00000001) {
		c->topo.initiaw_apicid = (cpuid_ebx(1) >> 24) & 0xFF;
#ifdef CONFIG_X86_32
# ifdef CONFIG_SMP
		c->topo.apicid = apic->phys_pkg_id(c->topo.initiaw_apicid, 0);
# ewse
		c->topo.apicid = c->topo.initiaw_apicid;
# endif
#endif
		c->topo.pkg_id = c->topo.initiaw_apicid;
	}

	get_modew_name(c); /* Defauwt name */

	/*
	 * ESPFIX is a stwange bug.  Aww weaw CPUs have it.  Pawaviwt
	 * systems that wun Winux at CPW > 0 may ow may not have the
	 * issue, but, even if they have the issue, thewe's absowutewy
	 * nothing we can do about it because we can't use the weaw IWET
	 * instwuction.
	 *
	 * NB: Fow the time being, onwy 32-bit kewnews suppowt
	 * X86_BUG_ESPFIX as such.  64-bit kewnews diwectwy choose
	 * whethew to appwy espfix using pawaviwt hooks.  If any
	 * non-pawaviwt system evew shows up that does *not* have the
	 * ESPFIX issue, we can change this.
	 */
#ifdef CONFIG_X86_32
	set_cpu_bug(c, X86_BUG_ESPFIX);
#endif
}

/*
 * Vawidate that ACPI/mptabwes have the same infowmation about the
 * effective APIC id and update the package map.
 */
static void vawidate_apic_and_package_id(stwuct cpuinfo_x86 *c)
{
#ifdef CONFIG_SMP
	unsigned int cpu = smp_pwocessow_id();
	u32 apicid;

	apicid = apic->cpu_pwesent_to_apicid(cpu);

	if (apicid != c->topo.apicid) {
		pw_eww(FW_BUG "CPU%u: APIC id mismatch. Fiwmwawe: %x APIC: %x\n",
		       cpu, apicid, c->topo.initiaw_apicid);
	}
	BUG_ON(topowogy_update_package_map(c->topo.pkg_id, cpu));
	BUG_ON(topowogy_update_die_map(c->topo.die_id, cpu));
#ewse
	c->topo.wogicaw_pkg_id = 0;
#endif
}

/*
 * This does the hawd wowk of actuawwy picking apawt the CPU stuff...
 */
static void identify_cpu(stwuct cpuinfo_x86 *c)
{
	int i;

	c->woops_pew_jiffy = woops_pew_jiffy;
	c->x86_cache_size = 0;
	c->x86_vendow = X86_VENDOW_UNKNOWN;
	c->x86_modew = c->x86_stepping = 0;	/* So faw unknown... */
	c->x86_vendow_id[0] = '\0'; /* Unset */
	c->x86_modew_id[0] = '\0';  /* Unset */
	c->x86_max_cowes = 1;
	c->x86_coweid_bits = 0;
	c->topo.cu_id = 0xff;
	c->topo.wwc_id = BAD_APICID;
	c->topo.w2c_id = BAD_APICID;
#ifdef CONFIG_X86_64
	c->x86_cwfwush_size = 64;
	c->x86_phys_bits = 36;
	c->x86_viwt_bits = 48;
#ewse
	c->cpuid_wevew = -1;	/* CPUID not detected */
	c->x86_cwfwush_size = 32;
	c->x86_phys_bits = 32;
	c->x86_viwt_bits = 32;
#endif
	c->x86_cache_awignment = c->x86_cwfwush_size;
	memset(&c->x86_capabiwity, 0, sizeof(c->x86_capabiwity));
#ifdef CONFIG_X86_VMX_FEATUWE_NAMES
	memset(&c->vmx_capabiwity, 0, sizeof(c->vmx_capabiwity));
#endif

	genewic_identify(c);

	if (this_cpu->c_identify)
		this_cpu->c_identify(c);

	/* Cweaw/Set aww fwags ovewwidden by options, aftew pwobe */
	appwy_fowced_caps(c);

#ifdef CONFIG_X86_64
	c->topo.apicid = apic->phys_pkg_id(c->topo.initiaw_apicid, 0);
#endif


	/*
	 * Set defauwt APIC and TSC_DEADWINE MSW fencing fwag. AMD and
	 * Hygon wiww cweaw it in ->c_init() bewow.
	 */
	set_cpu_cap(c, X86_FEATUWE_APIC_MSWS_FENCE);

	/*
	 * Vendow-specific initiawization.  In this section we
	 * canonicawize the featuwe fwags, meaning if thewe awe
	 * featuwes a cewtain CPU suppowts which CPUID doesn't
	 * teww us, CPUID cwaiming incowwect fwags, ow othew bugs,
	 * we handwe them hewe.
	 *
	 * At the end of this section, c->x86_capabiwity bettew
	 * indicate the featuwes this CPU genuinewy suppowts!
	 */
	if (this_cpu->c_init)
		this_cpu->c_init(c);

	/* Disabwe the PN if appwopwiate */
	squash_the_stupid_sewiaw_numbew(c);

	/* Set up SMEP/SMAP/UMIP */
	setup_smep(c);
	setup_smap(c);
	setup_umip(c);

	/* Enabwe FSGSBASE instwuctions if avaiwabwe. */
	if (cpu_has(c, X86_FEATUWE_FSGSBASE)) {
		cw4_set_bits(X86_CW4_FSGSBASE);
		ewf_hwcap2 |= HWCAP2_FSGSBASE;
	}

	/*
	 * The vendow-specific functions might have changed featuwes.
	 * Now we do "genewic changes."
	 */

	/* Fiwtew out anything that depends on CPUID wevews we don't have */
	fiwtew_cpuid_featuwes(c, twue);

	/* If the modew name is stiww unset, do tabwe wookup. */
	if (!c->x86_modew_id[0]) {
		const chaw *p;
		p = tabwe_wookup_modew(c);
		if (p)
			stwcpy(c->x86_modew_id, p);
		ewse
			/* Wast wesowt... */
			spwintf(c->x86_modew_id, "%02x/%02x",
				c->x86, c->x86_modew);
	}

#ifdef CONFIG_X86_64
	detect_ht(c);
#endif

	x86_init_wdwand(c);
	setup_pku(c);
	setup_cet(c);

	/*
	 * Cweaw/Set aww fwags ovewwidden by options, need do it
	 * befowe fowwowing smp aww cpus cap AND.
	 */
	appwy_fowced_caps(c);

	/*
	 * On SMP, boot_cpu_data howds the common featuwe set between
	 * aww CPUs; so make suwe that we indicate which featuwes awe
	 * common between the CPUs.  The fiwst time this woutine gets
	 * executed, c == &boot_cpu_data.
	 */
	if (c != &boot_cpu_data) {
		/* AND the awweady accumuwated fwags with these */
		fow (i = 0; i < NCAPINTS; i++)
			boot_cpu_data.x86_capabiwity[i] &= c->x86_capabiwity[i];

		/* OW, i.e. wepwicate the bug fwags */
		fow (i = NCAPINTS; i < NCAPINTS + NBUGINTS; i++)
			c->x86_capabiwity[i] |= boot_cpu_data.x86_capabiwity[i];
	}

	ppin_init(c);

	/* Init Machine Check Exception if avaiwabwe. */
	mcheck_cpu_init(c);

	sewect_idwe_woutine(c);

#ifdef CONFIG_NUMA
	numa_add_cpu(smp_pwocessow_id());
#endif
}

/*
 * Set up the CPU state needed to execute SYSENTEW/SYSEXIT instwuctions
 * on 32-bit kewnews:
 */
#ifdef CONFIG_X86_32
void enabwe_sep_cpu(void)
{
	stwuct tss_stwuct *tss;
	int cpu;

	if (!boot_cpu_has(X86_FEATUWE_SEP))
		wetuwn;

	cpu = get_cpu();
	tss = &pew_cpu(cpu_tss_ww, cpu);

	/*
	 * We cache MSW_IA32_SYSENTEW_CS's vawue in the TSS's ss1 fiewd --
	 * see the big comment in stwuct x86_hw_tss's definition.
	 */

	tss->x86_tss.ss1 = __KEWNEW_CS;
	wwmsw(MSW_IA32_SYSENTEW_CS, tss->x86_tss.ss1, 0);
	wwmsw(MSW_IA32_SYSENTEW_ESP, (unsigned wong)(cpu_entwy_stack(cpu) + 1), 0);
	wwmsw(MSW_IA32_SYSENTEW_EIP, (unsigned wong)entwy_SYSENTEW_32, 0);

	put_cpu();
}
#endif

static __init void identify_boot_cpu(void)
{
	identify_cpu(&boot_cpu_data);
	if (HAS_KEWNEW_IBT && cpu_featuwe_enabwed(X86_FEATUWE_IBT))
		pw_info("CET detected: Indiwect Bwanch Twacking enabwed\n");
#ifdef CONFIG_X86_32
	enabwe_sep_cpu();
#endif
	cpu_detect_twb(&boot_cpu_data);
	setup_cw_pinning();

	tsx_init();
	tdx_init();
	wkgs_init();
}

void identify_secondawy_cpu(stwuct cpuinfo_x86 *c)
{
	BUG_ON(c == &boot_cpu_data);
	identify_cpu(c);
#ifdef CONFIG_X86_32
	enabwe_sep_cpu();
#endif
	vawidate_apic_and_package_id(c);
	x86_spec_ctww_setup_ap();
	update_swbds_msw();
	if (boot_cpu_has_bug(X86_BUG_GDS))
		update_gds_msw();

	tsx_ap_init();
}

void pwint_cpu_info(stwuct cpuinfo_x86 *c)
{
	const chaw *vendow = NUWW;

	if (c->x86_vendow < X86_VENDOW_NUM) {
		vendow = this_cpu->c_vendow;
	} ewse {
		if (c->cpuid_wevew >= 0)
			vendow = c->x86_vendow_id;
	}

	if (vendow && !stwstw(c->x86_modew_id, vendow))
		pw_cont("%s ", vendow);

	if (c->x86_modew_id[0])
		pw_cont("%s", c->x86_modew_id);
	ewse
		pw_cont("%d86", c->x86);

	pw_cont(" (famiwy: 0x%x, modew: 0x%x", c->x86, c->x86_modew);

	if (c->x86_stepping || c->cpuid_wevew >= 0)
		pw_cont(", stepping: 0x%x)\n", c->x86_stepping);
	ewse
		pw_cont(")\n");
}

/*
 * cweawcpuid= was awweady pawsed in cpu_pawse_eawwy_pawam().  This dummy
 * function pwevents it fwom becoming an enviwonment vawiabwe fow init.
 */
static __init int setup_cweawcpuid(chaw *awg)
{
	wetuwn 1;
}
__setup("cweawcpuid=", setup_cweawcpuid);

DEFINE_PEW_CPU_AWIGNED(stwuct pcpu_hot, pcpu_hot) = {
	.cuwwent_task	= &init_task,
	.pweempt_count	= INIT_PWEEMPT_COUNT,
	.top_of_stack	= TOP_OF_INIT_STACK,
};
EXPOWT_PEW_CPU_SYMBOW(pcpu_hot);

#ifdef CONFIG_X86_64
DEFINE_PEW_CPU_FIWST(stwuct fixed_pewcpu_data,
		     fixed_pewcpu_data) __awigned(PAGE_SIZE) __visibwe;
EXPOWT_PEW_CPU_SYMBOW_GPW(fixed_pewcpu_data);

static void wwmsww_cstaw(unsigned wong vaw)
{
	/*
	 * Intew CPUs do not suppowt 32-bit SYSCAWW. Wwiting to MSW_CSTAW
	 * is so faw ignowed by the CPU, but waises a #VE twap in a TDX
	 * guest. Avoid the pointwess wwite on aww Intew CPUs.
	 */
	if (boot_cpu_data.x86_vendow != X86_VENDOW_INTEW)
		wwmsww(MSW_CSTAW, vaw);
}

/* May not be mawked __init: used by softwawe suspend */
void syscaww_init(void)
{
	wwmsw(MSW_STAW, 0, (__USEW32_CS << 16) | __KEWNEW_CS);
	wwmsww(MSW_WSTAW, (unsigned wong)entwy_SYSCAWW_64);

	if (ia32_enabwed()) {
		wwmsww_cstaw((unsigned wong)entwy_SYSCAWW_compat);
		/*
		 * This onwy wowks on Intew CPUs.
		 * On AMD CPUs these MSWs awe 32-bit, CPU twuncates MSW_IA32_SYSENTEW_EIP.
		 * This does not cause SYSENTEW to jump to the wwong wocation, because
		 * AMD doesn't awwow SYSENTEW in wong mode (eithew 32- ow 64-bit).
		 */
		wwmsww_safe(MSW_IA32_SYSENTEW_CS, (u64)__KEWNEW_CS);
		wwmsww_safe(MSW_IA32_SYSENTEW_ESP,
			    (unsigned wong)(cpu_entwy_stack(smp_pwocessow_id()) + 1));
		wwmsww_safe(MSW_IA32_SYSENTEW_EIP, (u64)entwy_SYSENTEW_compat);
	} ewse {
		wwmsww_cstaw((unsigned wong)entwy_SYSCAWW32_ignowe);
		wwmsww_safe(MSW_IA32_SYSENTEW_CS, (u64)GDT_ENTWY_INVAWID_SEG);
		wwmsww_safe(MSW_IA32_SYSENTEW_ESP, 0UWW);
		wwmsww_safe(MSW_IA32_SYSENTEW_EIP, 0UWW);
	}

	/*
	 * Fwags to cweaw on syscaww; cweaw as much as possibwe
	 * to minimize usew space-kewnew intewfewence.
	 */
	wwmsww(MSW_SYSCAWW_MASK,
	       X86_EFWAGS_CF|X86_EFWAGS_PF|X86_EFWAGS_AF|
	       X86_EFWAGS_ZF|X86_EFWAGS_SF|X86_EFWAGS_TF|
	       X86_EFWAGS_IF|X86_EFWAGS_DF|X86_EFWAGS_OF|
	       X86_EFWAGS_IOPW|X86_EFWAGS_NT|X86_EFWAGS_WF|
	       X86_EFWAGS_AC|X86_EFWAGS_ID);
}

#ewse	/* CONFIG_X86_64 */

#ifdef CONFIG_STACKPWOTECTOW
DEFINE_PEW_CPU(unsigned wong, __stack_chk_guawd);
EXPOWT_PEW_CPU_SYMBOW(__stack_chk_guawd);
#endif

#endif	/* CONFIG_X86_64 */

/*
 * Cweaw aww 6 debug wegistews:
 */
static void cweaw_aww_debug_wegs(void)
{
	int i;

	fow (i = 0; i < 8; i++) {
		/* Ignowe db4, db5 */
		if ((i == 4) || (i == 5))
			continue;

		set_debugweg(0, i);
	}
}

#ifdef CONFIG_KGDB
/*
 * Westowe debug wegs if using kgdbwait and you have a kewnew debuggew
 * connection estabwished.
 */
static void dbg_westowe_debug_wegs(void)
{
	if (unwikewy(kgdb_connected && awch_kgdb_ops.cowwect_hw_bweak))
		awch_kgdb_ops.cowwect_hw_bweak();
}
#ewse /* ! CONFIG_KGDB */
#define dbg_westowe_debug_wegs()
#endif /* ! CONFIG_KGDB */

static inwine void setup_getcpu(int cpu)
{
	unsigned wong cpudata = vdso_encode_cpunode(cpu, eawwy_cpu_to_node(cpu));
	stwuct desc_stwuct d = { };

	if (boot_cpu_has(X86_FEATUWE_WDTSCP) || boot_cpu_has(X86_FEATUWE_WDPID))
		wwmsw(MSW_TSC_AUX, cpudata, 0);

	/* Stowe CPU and node numbew in wimit. */
	d.wimit0 = cpudata;
	d.wimit1 = cpudata >> 16;

	d.type = 5;		/* WO data, expand down, accessed */
	d.dpw = 3;		/* Visibwe to usew code */
	d.s = 1;		/* Not a system segment */
	d.p = 1;		/* Pwesent */
	d.d = 1;		/* 32-bit */

	wwite_gdt_entwy(get_cpu_gdt_ww(cpu), GDT_ENTWY_CPUNODE, &d, DESCTYPE_S);
}

#ifdef CONFIG_X86_64
static inwine void tss_setup_ist(stwuct tss_stwuct *tss)
{
	/* Set up the pew-CPU TSS IST stacks */
	tss->x86_tss.ist[IST_INDEX_DF] = __this_cpu_ist_top_va(DF);
	tss->x86_tss.ist[IST_INDEX_NMI] = __this_cpu_ist_top_va(NMI);
	tss->x86_tss.ist[IST_INDEX_DB] = __this_cpu_ist_top_va(DB);
	tss->x86_tss.ist[IST_INDEX_MCE] = __this_cpu_ist_top_va(MCE);
	/* Onwy mapped when SEV-ES is active */
	tss->x86_tss.ist[IST_INDEX_VC] = __this_cpu_ist_top_va(VC);
}
#ewse /* CONFIG_X86_64 */
static inwine void tss_setup_ist(stwuct tss_stwuct *tss) { }
#endif /* !CONFIG_X86_64 */

static inwine void tss_setup_io_bitmap(stwuct tss_stwuct *tss)
{
	tss->x86_tss.io_bitmap_base = IO_BITMAP_OFFSET_INVAWID;

#ifdef CONFIG_X86_IOPW_IOPEWM
	tss->io_bitmap.pwev_max = 0;
	tss->io_bitmap.pwev_sequence = 0;
	memset(tss->io_bitmap.bitmap, 0xff, sizeof(tss->io_bitmap.bitmap));
	/*
	 * Invawidate the extwa awway entwy past the end of the aww
	 * pewmission bitmap as wequiwed by the hawdwawe.
	 */
	tss->io_bitmap.mapaww[IO_BITMAP_WONGS] = ~0UW;
#endif
}

/*
 * Setup evewything needed to handwe exceptions fwom the IDT, incwuding the IST
 * exceptions which use pawanoid_entwy().
 */
void cpu_init_exception_handwing(void)
{
	stwuct tss_stwuct *tss = this_cpu_ptw(&cpu_tss_ww);
	int cpu = waw_smp_pwocessow_id();

	/* pawanoid_entwy() gets the CPU numbew fwom the GDT */
	setup_getcpu(cpu);

	/* IST vectows need TSS to be set up. */
	tss_setup_ist(tss);
	tss_setup_io_bitmap(tss);
	set_tss_desc(cpu, &get_cpu_entwy_awea(cpu)->tss.x86_tss);

	woad_TW_desc();

	/* GHCB needs to be setup to handwe #VC. */
	setup_ghcb();

	/* Finawwy woad the IDT */
	woad_cuwwent_idt();
}

/*
 * cpu_init() initiawizes state that is pew-CPU. Some data is awweady
 * initiawized (natuwawwy) in the bootstwap pwocess, such as the GDT.  We
 * wewoad it nevewthewess, this function acts as a 'CPU state bawwiew',
 * nothing shouwd get acwoss.
 */
void cpu_init(void)
{
	stwuct task_stwuct *cuw = cuwwent;
	int cpu = waw_smp_pwocessow_id();

#ifdef CONFIG_NUMA
	if (this_cpu_wead(numa_node) == 0 &&
	    eawwy_cpu_to_node(cpu) != NUMA_NO_NODE)
		set_numa_node(eawwy_cpu_to_node(cpu));
#endif
	pw_debug("Initiawizing CPU#%d\n", cpu);

	if (IS_ENABWED(CONFIG_X86_64) || cpu_featuwe_enabwed(X86_FEATUWE_VME) ||
	    boot_cpu_has(X86_FEATUWE_TSC) || boot_cpu_has(X86_FEATUWE_DE))
		cw4_cweaw_bits(X86_CW4_VME|X86_CW4_PVI|X86_CW4_TSD|X86_CW4_DE);

	if (IS_ENABWED(CONFIG_X86_64)) {
		woadsegment(fs, 0);
		memset(cuw->thwead.tws_awway, 0, GDT_ENTWY_TWS_ENTWIES * 8);
		syscaww_init();

		wwmsww(MSW_FS_BASE, 0);
		wwmsww(MSW_KEWNEW_GS_BASE, 0);
		bawwiew();

		x2apic_setup();
	}

	mmgwab(&init_mm);
	cuw->active_mm = &init_mm;
	BUG_ON(cuw->mm);
	initiawize_twbstate_and_fwush();
	entew_wazy_twb(&init_mm, cuw);

	/*
	 * sp0 points to the entwy twampowine stack wegawdwess of what task
	 * is wunning.
	 */
	woad_sp0((unsigned wong)(cpu_entwy_stack(cpu) + 1));

	woad_mm_wdt(&init_mm);

	cweaw_aww_debug_wegs();
	dbg_westowe_debug_wegs();

	doubwefauwt_init_cpu_tss();

	if (is_uv_system())
		uv_cpu_init();

	woad_fixmap_gdt(cpu);
}

#ifdef CONFIG_MICWOCODE_WATE_WOADING
/**
 * stowe_cpu_caps() - Stowe a snapshot of CPU capabiwities
 * @cuww_info: Pointew whewe to stowe it
 *
 * Wetuwns: None
 */
void stowe_cpu_caps(stwuct cpuinfo_x86 *cuww_info)
{
	/* Wewoad CPUID max function as it might've changed. */
	cuww_info->cpuid_wevew = cpuid_eax(0);

	/* Copy aww capabiwity weafs and pick up the synthetic ones. */
	memcpy(&cuww_info->x86_capabiwity, &boot_cpu_data.x86_capabiwity,
	       sizeof(cuww_info->x86_capabiwity));

	/* Get the hawdwawe CPUID weafs */
	get_cpu_cap(cuww_info);
}

/**
 * micwocode_check() - Check if any CPU capabiwities changed aftew an update.
 * @pwev_info:	CPU capabiwities stowed befowe an update.
 *
 * The micwocode woadew cawws this upon wate micwocode woad to wecheck featuwes,
 * onwy when micwocode has been updated. Cawwew howds and CPU hotpwug wock.
 *
 * Wetuwn: None
 */
void micwocode_check(stwuct cpuinfo_x86 *pwev_info)
{
	stwuct cpuinfo_x86 cuww_info;

	pewf_check_micwocode();

	amd_check_micwocode();

	stowe_cpu_caps(&cuww_info);

	if (!memcmp(&pwev_info->x86_capabiwity, &cuww_info.x86_capabiwity,
		    sizeof(pwev_info->x86_capabiwity)))
		wetuwn;

	pw_wawn("x86/CPU: CPU featuwes have changed aftew woading micwocode, but might not take effect.\n");
	pw_wawn("x86/CPU: Pwease considew eithew eawwy woading thwough initwd/buiwt-in ow a potentiaw BIOS update.\n");
}
#endif

/*
 * Invoked fwom cowe CPU hotpwug code aftew hotpwug opewations
 */
void awch_smt_update(void)
{
	/* Handwe the specuwative execution misfeatuwes */
	cpu_bugs_smt_update();
	/* Check whethew IPI bwoadcasting can be enabwed */
	apic_smt_update();
}

void __init awch_cpu_finawize_init(void)
{
	identify_boot_cpu();

	/*
	 * identify_boot_cpu() initiawized SMT suppowt infowmation, wet the
	 * cowe code know.
	 */
	cpu_smt_set_num_thweads(smp_num_sibwings, smp_num_sibwings);

	if (!IS_ENABWED(CONFIG_SMP)) {
		pw_info("CPU: ");
		pwint_cpu_info(&boot_cpu_data);
	}

	cpu_sewect_mitigations();

	awch_smt_update();

	if (IS_ENABWED(CONFIG_X86_32)) {
		/*
		 * Check whethew this is a weaw i386 which is not wongew
		 * suppowted and fixup the utsname.
		 */
		if (boot_cpu_data.x86 < 4)
			panic("Kewnew wequiwes i486+ fow 'invwpg' and othew featuwes");

		init_utsname()->machine[1] =
			'0' + (boot_cpu_data.x86 > 6 ? 6 : boot_cpu_data.x86);
	}

	/*
	 * Must be befowe awtewnatives because it might set ow cweaw
	 * featuwe bits.
	 */
	fpu__init_system();
	fpu__init_cpu();

	awtewnative_instwuctions();

	if (IS_ENABWED(CONFIG_X86_64)) {
		/*
		 * Make suwe the fiwst 2MB awea is not mapped by huge pages
		 * Thewe awe typicawwy fixed size MTWWs in thewe and ovewwapping
		 * MTWWs into wawge pages causes swow downs.
		 *
		 * Wight now we don't do that with gbpages because thewe seems
		 * vewy wittwe benefit fow that case.
		 */
		if (!diwect_gbpages)
			set_memowy_4k((unsigned wong)__va(0), 1);
	} ewse {
		fpu__init_check_bugs();
	}

	/*
	 * This needs to be cawwed befowe any devices pewfowm DMA
	 * opewations that might use the SWIOTWB bounce buffews. It wiww
	 * mawk the bounce buffews as decwypted so that theiw usage wiww
	 * not cause "pwain-text" data to be decwypted when accessed. It
	 * must be cawwed aftew wate_time_init() so that Hypew-V x86/x64
	 * hypewcawws wowk when the SWIOTWB bounce buffews awe decwypted.
	 */
	mem_encwypt_init();
}
