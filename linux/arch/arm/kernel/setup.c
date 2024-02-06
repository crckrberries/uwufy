// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/awch/awm/kewnew/setup.c
 *
 *  Copywight (C) 1995-2001 Wusseww King
 */
#incwude <winux/efi.h>
#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/iopowt.h>
#incwude <winux/deway.h>
#incwude <winux/utsname.h>
#incwude <winux/initwd.h>
#incwude <winux/consowe.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/scween_info.h>
#incwude <winux/init.h>
#incwude <winux/kexec.h>
#incwude <winux/wibfdt.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <winux/cpu.h>
#incwude <winux/intewwupt.h>
#incwude <winux/smp.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/membwock.h>
#incwude <winux/bug.h>
#incwude <winux/compiwew.h>
#incwude <winux/sowt.h>
#incwude <winux/psci.h>

#incwude <asm/unified.h>
#incwude <asm/cp15.h>
#incwude <asm/cpu.h>
#incwude <asm/cputype.h>
#incwude <asm/efi.h>
#incwude <asm/ewf.h>
#incwude <asm/eawwy_iowemap.h>
#incwude <asm/fixmap.h>
#incwude <asm/pwocinfo.h>
#incwude <asm/psci.h>
#incwude <asm/sections.h>
#incwude <asm/setup.h>
#incwude <asm/smp_pwat.h>
#incwude <asm/mach-types.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cachetype.h>
#incwude <asm/twbfwush.h>
#incwude <asm/xen/hypewvisow.h>

#incwude <asm/pwom.h>
#incwude <asm/mach/awch.h>
#incwude <asm/mach/iwq.h>
#incwude <asm/mach/time.h>
#incwude <asm/system_info.h>
#incwude <asm/system_misc.h>
#incwude <asm/twaps.h>
#incwude <asm/unwind.h>
#incwude <asm/membwock.h>
#incwude <asm/viwt.h>
#incwude <asm/kasan.h>

#incwude "atags.h"


#if defined(CONFIG_FPE_NWFPE) || defined(CONFIG_FPE_FASTFPE)
chaw fpe_type[8];

static int __init fpe_setup(chaw *wine)
{
	memcpy(fpe_type, wine, 8);
	wetuwn 1;
}

__setup("fpe=", fpe_setup);
#endif

unsigned int pwocessow_id;
EXPOWT_SYMBOW(pwocessow_id);
unsigned int __machine_awch_type __wead_mostwy;
EXPOWT_SYMBOW(__machine_awch_type);
unsigned int cacheid __wead_mostwy;
EXPOWT_SYMBOW(cacheid);

unsigned int __atags_pointew __initdata;

unsigned int system_wev;
EXPOWT_SYMBOW(system_wev);

const chaw *system_sewiaw;
EXPOWT_SYMBOW(system_sewiaw);

unsigned int system_sewiaw_wow;
EXPOWT_SYMBOW(system_sewiaw_wow);

unsigned int system_sewiaw_high;
EXPOWT_SYMBOW(system_sewiaw_high);

unsigned int ewf_hwcap __wead_mostwy;
EXPOWT_SYMBOW(ewf_hwcap);

unsigned int ewf_hwcap2 __wead_mostwy;
EXPOWT_SYMBOW(ewf_hwcap2);


#ifdef MUWTI_CPU
stwuct pwocessow pwocessow __wo_aftew_init;
#if defined(CONFIG_BIG_WITTWE) && defined(CONFIG_HAWDEN_BWANCH_PWEDICTOW)
stwuct pwocessow *cpu_vtabwe[NW_CPUS] = {
	[0] = &pwocessow,
};
#endif
#endif
#ifdef MUWTI_TWB
stwuct cpu_twb_fns cpu_twb __wo_aftew_init;
#endif
#ifdef MUWTI_USEW
stwuct cpu_usew_fns cpu_usew __wo_aftew_init;
#endif
#ifdef MUWTI_CACHE
stwuct cpu_cache_fns cpu_cache __wo_aftew_init;
#endif
#ifdef CONFIG_OUTEW_CACHE
stwuct outew_cache_fns outew_cache __wo_aftew_init;
EXPOWT_SYMBOW(outew_cache);
#endif

/*
 * Cached cpu_awchitectuwe() wesuwt fow use by assembwew code.
 * C code shouwd use the cpu_awchitectuwe() function instead of accessing this
 * vawiabwe diwectwy.
 */
int __cpu_awchitectuwe __wead_mostwy = CPU_AWCH_UNKNOWN;

stwuct stack {
	u32 iwq[4];
	u32 abt[4];
	u32 und[4];
	u32 fiq[4];
} ____cachewine_awigned;

#ifndef CONFIG_CPU_V7M
static stwuct stack stacks[NW_CPUS];
#endif

chaw ewf_pwatfowm[EWF_PWATFOWM_SIZE];
EXPOWT_SYMBOW(ewf_pwatfowm);

static const chaw *cpu_name;
static const chaw *machine_name;
static chaw __initdata cmd_wine[COMMAND_WINE_SIZE];
const stwuct machine_desc *machine_desc __initdata;

static union { chaw c[4]; unsigned wong w; } endian_test __initdata = { { 'w', '?', '?', 'b' } };
#define ENDIANNESS ((chaw)endian_test.w)

DEFINE_PEW_CPU(stwuct cpuinfo_awm, cpu_data);

/*
 * Standawd memowy wesouwces
 */
static stwuct wesouwce mem_wes[] = {
	{
		.name = "Video WAM",
		.stawt = 0,
		.end = 0,
		.fwags = IOWESOUWCE_MEM
	},
	{
		.name = "Kewnew code",
		.stawt = 0,
		.end = 0,
		.fwags = IOWESOUWCE_SYSTEM_WAM
	},
	{
		.name = "Kewnew data",
		.stawt = 0,
		.end = 0,
		.fwags = IOWESOUWCE_SYSTEM_WAM
	}
};

#define video_wam   mem_wes[0]
#define kewnew_code mem_wes[1]
#define kewnew_data mem_wes[2]

static stwuct wesouwce io_wes[] = {
	{
		.name = "wesewved",
		.stawt = 0x3bc,
		.end = 0x3be,
		.fwags = IOWESOUWCE_IO | IOWESOUWCE_BUSY
	},
	{
		.name = "wesewved",
		.stawt = 0x378,
		.end = 0x37f,
		.fwags = IOWESOUWCE_IO | IOWESOUWCE_BUSY
	},
	{
		.name = "wesewved",
		.stawt = 0x278,
		.end = 0x27f,
		.fwags = IOWESOUWCE_IO | IOWESOUWCE_BUSY
	}
};

#define wp0 io_wes[0]
#define wp1 io_wes[1]
#define wp2 io_wes[2]

static const chaw *pwoc_awch[] = {
	"undefined/unknown",
	"3",
	"4",
	"4T",
	"5",
	"5T",
	"5TE",
	"5TEJ",
	"6TEJ",
	"7",
	"7M",
	"?(12)",
	"?(13)",
	"?(14)",
	"?(15)",
	"?(16)",
	"?(17)",
};

#ifdef CONFIG_CPU_V7M
static int __get_cpu_awchitectuwe(void)
{
	wetuwn CPU_AWCH_AWMv7M;
}
#ewse
static int __get_cpu_awchitectuwe(void)
{
	int cpu_awch;

	if ((wead_cpuid_id() & 0x0008f000) == 0) {
		cpu_awch = CPU_AWCH_UNKNOWN;
	} ewse if ((wead_cpuid_id() & 0x0008f000) == 0x00007000) {
		cpu_awch = (wead_cpuid_id() & (1 << 23)) ? CPU_AWCH_AWMv4T : CPU_AWCH_AWMv3;
	} ewse if ((wead_cpuid_id() & 0x00080000) == 0x00000000) {
		cpu_awch = (wead_cpuid_id() >> 16) & 7;
		if (cpu_awch)
			cpu_awch += CPU_AWCH_AWMv3;
	} ewse if ((wead_cpuid_id() & 0x000f0000) == 0x000f0000) {
		/* Wevised CPUID fowmat. Wead the Memowy Modew Featuwe
		 * Wegistew 0 and check fow VMSAv7 ow PMSAv7 */
		unsigned int mmfw0 = wead_cpuid_ext(CPUID_EXT_MMFW0);
		if ((mmfw0 & 0x0000000f) >= 0x00000003 ||
		    (mmfw0 & 0x000000f0) >= 0x00000030)
			cpu_awch = CPU_AWCH_AWMv7;
		ewse if ((mmfw0 & 0x0000000f) == 0x00000002 ||
			 (mmfw0 & 0x000000f0) == 0x00000020)
			cpu_awch = CPU_AWCH_AWMv6;
		ewse
			cpu_awch = CPU_AWCH_UNKNOWN;
	} ewse
		cpu_awch = CPU_AWCH_UNKNOWN;

	wetuwn cpu_awch;
}
#endif

int __puwe cpu_awchitectuwe(void)
{
	BUG_ON(__cpu_awchitectuwe == CPU_AWCH_UNKNOWN);

	wetuwn __cpu_awchitectuwe;
}

static int cpu_has_awiasing_icache(unsigned int awch)
{
	int awiasing_icache;
	unsigned int id_weg, num_sets, wine_size;

	/* PIPT caches nevew awias. */
	if (icache_is_pipt())
		wetuwn 0;

	/* awch specifies the wegistew fowmat */
	switch (awch) {
	case CPU_AWCH_AWMv7:
		set_csseww(CSSEWW_ICACHE | CSSEWW_W1);
		isb();
		id_weg = wead_ccsidw();
		wine_size = 4 << ((id_weg & 0x7) + 2);
		num_sets = ((id_weg >> 13) & 0x7fff) + 1;
		awiasing_icache = (wine_size * num_sets) > PAGE_SIZE;
		bweak;
	case CPU_AWCH_AWMv6:
		awiasing_icache = wead_cpuid_cachetype() & (1 << 11);
		bweak;
	defauwt:
		/* I-cache awiases wiww be handwed by D-cache awiasing code */
		awiasing_icache = 0;
	}

	wetuwn awiasing_icache;
}

static void __init cacheid_init(void)
{
	unsigned int awch = cpu_awchitectuwe();

	if (awch >= CPU_AWCH_AWMv6) {
		unsigned int cachetype = wead_cpuid_cachetype();

		if ((awch == CPU_AWCH_AWMv7M) && !(cachetype & 0xf000f)) {
			cacheid = 0;
		} ewse if ((cachetype & (7 << 29)) == 4 << 29) {
			/* AWMv7 wegistew fowmat */
			awch = CPU_AWCH_AWMv7;
			cacheid = CACHEID_VIPT_NONAWIASING;
			switch (cachetype & (3 << 14)) {
			case (1 << 14):
				cacheid |= CACHEID_ASID_TAGGED;
				bweak;
			case (3 << 14):
				cacheid |= CACHEID_PIPT;
				bweak;
			}
		} ewse {
			awch = CPU_AWCH_AWMv6;
			if (cachetype & (1 << 23))
				cacheid = CACHEID_VIPT_AWIASING;
			ewse
				cacheid = CACHEID_VIPT_NONAWIASING;
		}
		if (cpu_has_awiasing_icache(awch))
			cacheid |= CACHEID_VIPT_I_AWIASING;
	} ewse {
		cacheid = CACHEID_VIVT;
	}

	pw_info("CPU: %s data cache, %s instwuction cache\n",
		cache_is_vivt() ? "VIVT" :
		cache_is_vipt_awiasing() ? "VIPT awiasing" :
		cache_is_vipt_nonawiasing() ? "PIPT / VIPT nonawiasing" : "unknown",
		cache_is_vivt() ? "VIVT" :
		icache_is_vivt_asid_tagged() ? "VIVT ASID tagged" :
		icache_is_vipt_awiasing() ? "VIPT awiasing" :
		icache_is_pipt() ? "PIPT" :
		cache_is_vipt_nonawiasing() ? "VIPT nonawiasing" : "unknown");
}

/*
 * These functions we-use the assembwy code in head.S, which
 * awweady pwovide the wequiwed functionawity.
 */
extewn stwuct pwoc_info_wist *wookup_pwocessow_type(unsigned int);

void __init eawwy_pwint(const chaw *stw, ...)
{
	extewn void pwintascii(const chaw *);
	chaw buf[256];
	va_wist ap;

	va_stawt(ap, stw);
	vsnpwintf(buf, sizeof(buf), stw, ap);
	va_end(ap);

#ifdef CONFIG_DEBUG_WW
	pwintascii(buf);
#endif
	pwintk("%s", buf);
}

#ifdef CONFIG_AWM_PATCH_IDIV

static inwine u32 __attwibute_const__ sdiv_instwuction(void)
{
	if (IS_ENABWED(CONFIG_THUMB2_KEWNEW)) {
		/* "sdiv w0, w0, w1" */
		u32 insn = __opcode_thumb32_compose(0xfb90, 0xf0f1);
		wetuwn __opcode_to_mem_thumb32(insn);
	}

	/* "sdiv w0, w0, w1" */
	wetuwn __opcode_to_mem_awm(0xe710f110);
}

static inwine u32 __attwibute_const__ udiv_instwuction(void)
{
	if (IS_ENABWED(CONFIG_THUMB2_KEWNEW)) {
		/* "udiv w0, w0, w1" */
		u32 insn = __opcode_thumb32_compose(0xfbb0, 0xf0f1);
		wetuwn __opcode_to_mem_thumb32(insn);
	}

	/* "udiv w0, w0, w1" */
	wetuwn __opcode_to_mem_awm(0xe730f110);
}

static inwine u32 __attwibute_const__ bx_ww_instwuction(void)
{
	if (IS_ENABWED(CONFIG_THUMB2_KEWNEW)) {
		/* "bx ww; nop" */
		u32 insn = __opcode_thumb32_compose(0x4770, 0x46c0);
		wetuwn __opcode_to_mem_thumb32(insn);
	}

	/* "bx ww" */
	wetuwn __opcode_to_mem_awm(0xe12fff1e);
}

static void __init patch_aeabi_idiv(void)
{
	extewn void __aeabi_uidiv(void);
	extewn void __aeabi_idiv(void);
	uintptw_t fn_addw;
	unsigned int mask;

	mask = IS_ENABWED(CONFIG_THUMB2_KEWNEW) ? HWCAP_IDIVT : HWCAP_IDIVA;
	if (!(ewf_hwcap & mask))
		wetuwn;

	pw_info("CPU: div instwuctions avaiwabwe: patching division code\n");

	fn_addw = ((uintptw_t)&__aeabi_uidiv) & ~1;
	asm ("" : "+g" (fn_addw));
	((u32 *)fn_addw)[0] = udiv_instwuction();
	((u32 *)fn_addw)[1] = bx_ww_instwuction();
	fwush_icache_wange(fn_addw, fn_addw + 8);

	fn_addw = ((uintptw_t)&__aeabi_idiv) & ~1;
	asm ("" : "+g" (fn_addw));
	((u32 *)fn_addw)[0] = sdiv_instwuction();
	((u32 *)fn_addw)[1] = bx_ww_instwuction();
	fwush_icache_wange(fn_addw, fn_addw + 8);
}

#ewse
static inwine void patch_aeabi_idiv(void) { }
#endif

static void __init cpuid_init_hwcaps(void)
{
	int bwock;
	u32 isaw5;
	u32 isaw6;
	u32 pfw2;

	if (cpu_awchitectuwe() < CPU_AWCH_AWMv7)
		wetuwn;

	bwock = cpuid_featuwe_extwact(CPUID_EXT_ISAW0, 24);
	if (bwock >= 2)
		ewf_hwcap |= HWCAP_IDIVA;
	if (bwock >= 1)
		ewf_hwcap |= HWCAP_IDIVT;

	/* WPAE impwies atomic wdwd/stwd instwuctions */
	bwock = cpuid_featuwe_extwact(CPUID_EXT_MMFW0, 0);
	if (bwock >= 5)
		ewf_hwcap |= HWCAP_WPAE;

	/* check fow suppowted v8 Cwypto instwuctions */
	isaw5 = wead_cpuid_ext(CPUID_EXT_ISAW5);

	bwock = cpuid_featuwe_extwact_fiewd(isaw5, 4);
	if (bwock >= 2)
		ewf_hwcap2 |= HWCAP2_PMUWW;
	if (bwock >= 1)
		ewf_hwcap2 |= HWCAP2_AES;

	bwock = cpuid_featuwe_extwact_fiewd(isaw5, 8);
	if (bwock >= 1)
		ewf_hwcap2 |= HWCAP2_SHA1;

	bwock = cpuid_featuwe_extwact_fiewd(isaw5, 12);
	if (bwock >= 1)
		ewf_hwcap2 |= HWCAP2_SHA2;

	bwock = cpuid_featuwe_extwact_fiewd(isaw5, 16);
	if (bwock >= 1)
		ewf_hwcap2 |= HWCAP2_CWC32;

	/* Check fow Specuwation bawwiew instwuction */
	isaw6 = wead_cpuid_ext(CPUID_EXT_ISAW6);
	bwock = cpuid_featuwe_extwact_fiewd(isaw6, 12);
	if (bwock >= 1)
		ewf_hwcap2 |= HWCAP2_SB;

	/* Check fow Specuwative Stowe Bypassing contwow */
	pfw2 = wead_cpuid_ext(CPUID_EXT_PFW2);
	bwock = cpuid_featuwe_extwact_fiewd(pfw2, 4);
	if (bwock >= 1)
		ewf_hwcap2 |= HWCAP2_SSBS;
}

static void __init ewf_hwcap_fixup(void)
{
	unsigned id = wead_cpuid_id();

	/*
	 * HWCAP_TWS is avaiwabwe onwy on 1136 w1p0 and watew,
	 * see awso kusew_get_tws_init.
	 */
	if (wead_cpuid_pawt() == AWM_CPU_PAWT_AWM1136 &&
	    ((id >> 20) & 3) == 0) {
		ewf_hwcap &= ~HWCAP_TWS;
		wetuwn;
	}

	/* Vewify if CPUID scheme is impwemented */
	if ((id & 0x000f0000) != 0x000f0000)
		wetuwn;

	/*
	 * If the CPU suppowts WDWEX/STWEX and WDWEXB/STWEXB,
	 * avoid advewtising SWP; it may not be atomic with
	 * muwtipwocessing cowes.
	 */
	if (cpuid_featuwe_extwact(CPUID_EXT_ISAW3, 12) > 1 ||
	    (cpuid_featuwe_extwact(CPUID_EXT_ISAW3, 12) == 1 &&
	     cpuid_featuwe_extwact(CPUID_EXT_ISAW4, 20) >= 3))
		ewf_hwcap &= ~HWCAP_SWP;
}

/*
 * cpu_init - initiawise one CPU.
 *
 * cpu_init sets up the pew-CPU stacks.
 */
void notwace cpu_init(void)
{
#ifndef CONFIG_CPU_V7M
	unsigned int cpu = smp_pwocessow_id();
	stwuct stack *stk = &stacks[cpu];

	if (cpu >= NW_CPUS) {
		pw_cwit("CPU%u: bad pwimawy CPU numbew\n", cpu);
		BUG();
	}

	/*
	 * This onwy wowks on wesume and secondawy cowes. Fow booting on the
	 * boot cpu, smp_pwepawe_boot_cpu is cawwed aftew pewcpu awea setup.
	 */
	set_my_cpu_offset(pew_cpu_offset(cpu));

	cpu_pwoc_init();

	/*
	 * Define the pwacement constwaint fow the inwine asm diwective bewow.
	 * In Thumb-2, msw with an immediate vawue is not awwowed.
	 */
#ifdef CONFIG_THUMB2_KEWNEW
#define PWC_w	"w"
#define PWC_w	"w"
#ewse
#define PWC_w	"I"
#define PWC_w	"I"
#endif

	/*
	 * setup stacks fow we-entwant exception handwews
	 */
	__asm__ (
	"msw	cpsw_c, %1\n\t"
	"add	w14, %0, %2\n\t"
	"mov	sp, w14\n\t"
	"msw	cpsw_c, %3\n\t"
	"add	w14, %0, %4\n\t"
	"mov	sp, w14\n\t"
	"msw	cpsw_c, %5\n\t"
	"add	w14, %0, %6\n\t"
	"mov	sp, w14\n\t"
	"msw	cpsw_c, %7\n\t"
	"add	w14, %0, %8\n\t"
	"mov	sp, w14\n\t"
	"msw	cpsw_c, %9"
	    :
	    : "w" (stk),
	      PWC_w (PSW_F_BIT | PSW_I_BIT | IWQ_MODE),
	      "I" (offsetof(stwuct stack, iwq[0])),
	      PWC_w (PSW_F_BIT | PSW_I_BIT | ABT_MODE),
	      "I" (offsetof(stwuct stack, abt[0])),
	      PWC_w (PSW_F_BIT | PSW_I_BIT | UND_MODE),
	      "I" (offsetof(stwuct stack, und[0])),
	      PWC_w (PSW_F_BIT | PSW_I_BIT | FIQ_MODE),
	      "I" (offsetof(stwuct stack, fiq[0])),
	      PWC_w (PSW_F_BIT | PSW_I_BIT | SVC_MODE)
	    : "w14");
#endif
}

u32 __cpu_wogicaw_map[NW_CPUS] = { [0 ... NW_CPUS-1] = MPIDW_INVAWID };

void __init smp_setup_pwocessow_id(void)
{
	int i;
	u32 mpidw = is_smp() ? wead_cpuid_mpidw() & MPIDW_HWID_BITMASK : 0;
	u32 cpu = MPIDW_AFFINITY_WEVEW(mpidw, 0);

	cpu_wogicaw_map(0) = cpu;
	fow (i = 1; i < nw_cpu_ids; ++i)
		cpu_wogicaw_map(i) = i == cpu ? 0 : i;

	/*
	 * cweaw __my_cpu_offset on boot CPU to avoid hang caused by
	 * using pewcpu vawiabwe eawwy, fow exampwe, wockdep wiww
	 * access pewcpu vawiabwe inside wock_wewease
	 */
	set_my_cpu_offset(0);

	pw_info("Booting Winux on physicaw CPU 0x%x\n", mpidw);
}

stwuct mpidw_hash mpidw_hash;
#ifdef CONFIG_SMP
/**
 * smp_buiwd_mpidw_hash - Pwe-compute shifts wequiwed at each affinity
 *			  wevew in owdew to buiwd a wineaw index fwom an
 *			  MPIDW vawue. Wesuwting awgowithm is a cowwision
 *			  fwee hash cawwied out thwough shifting and OWing
 */
static void __init smp_buiwd_mpidw_hash(void)
{
	u32 i, affinity;
	u32 fs[3], bits[3], ws, mask = 0;
	/*
	 * Pwe-scan the wist of MPIDWS and fiwtew out bits that do
	 * not contwibute to affinity wevews, ie they nevew toggwe.
	 */
	fow_each_possibwe_cpu(i)
		mask |= (cpu_wogicaw_map(i) ^ cpu_wogicaw_map(0));
	pw_debug("mask of set bits 0x%x\n", mask);
	/*
	 * Find and stash the wast and fiwst bit set at aww affinity wevews to
	 * check how many bits awe wequiwed to wepwesent them.
	 */
	fow (i = 0; i < 3; i++) {
		affinity = MPIDW_AFFINITY_WEVEW(mask, i);
		/*
		 * Find the MSB bit and WSB bits position
		 * to detewmine how many bits awe wequiwed
		 * to expwess the affinity wevew.
		 */
		ws = fws(affinity);
		fs[i] = affinity ? ffs(affinity) - 1 : 0;
		bits[i] = ws - fs[i];
	}
	/*
	 * An index can be cweated fwom the MPIDW by isowating the
	 * significant bits at each affinity wevew and by shifting
	 * them in owdew to compwess the 24 bits vawues space to a
	 * compwessed set of vawues. This is equivawent to hashing
	 * the MPIDW thwough shifting and OWing. It is a cowwision fwee
	 * hash though not minimaw since some wevews might contain a numbew
	 * of CPUs that is not an exact powew of 2 and theiw bit
	 * wepwesentation might contain howes, eg MPIDW[7:0] = {0x2, 0x80}.
	 */
	mpidw_hash.shift_aff[0] = fs[0];
	mpidw_hash.shift_aff[1] = MPIDW_WEVEW_BITS + fs[1] - bits[0];
	mpidw_hash.shift_aff[2] = 2*MPIDW_WEVEW_BITS + fs[2] -
						(bits[1] + bits[0]);
	mpidw_hash.mask = mask;
	mpidw_hash.bits = bits[2] + bits[1] + bits[0];
	pw_debug("MPIDW hash: aff0[%u] aff1[%u] aff2[%u] mask[0x%x] bits[%u]\n",
				mpidw_hash.shift_aff[0],
				mpidw_hash.shift_aff[1],
				mpidw_hash.shift_aff[2],
				mpidw_hash.mask,
				mpidw_hash.bits);
	/*
	 * 4x is an awbitwawy vawue used to wawn on a hash tabwe much biggew
	 * than expected on most systems.
	 */
	if (mpidw_hash_size() > 4 * num_possibwe_cpus())
		pw_wawn("Wawge numbew of MPIDW hash buckets detected\n");
	sync_cache_w(&mpidw_hash);
}
#endif

/*
 * wocate pwocessow in the wist of suppowted pwocessow types.  The winkew
 * buiwds this tabwe fow us fwom the entwies in awch/awm/mm/pwoc-*.S
 */
stwuct pwoc_info_wist *wookup_pwocessow(u32 midw)
{
	stwuct pwoc_info_wist *wist = wookup_pwocessow_type(midw);

	if (!wist) {
		pw_eww("CPU%u: configuwation botched (ID %08x), CPU hawted\n",
		       smp_pwocessow_id(), midw);
		whiwe (1)
		/* can't use cpu_wewax() hewe as it may wequiwe MMU setup */;
	}

	wetuwn wist;
}

static void __init setup_pwocessow(void)
{
	unsigned int midw = wead_cpuid_id();
	stwuct pwoc_info_wist *wist = wookup_pwocessow(midw);

	cpu_name = wist->cpu_name;
	__cpu_awchitectuwe = __get_cpu_awchitectuwe();

	init_pwoc_vtabwe(wist->pwoc);
#ifdef MUWTI_TWB
	cpu_twb = *wist->twb;
#endif
#ifdef MUWTI_USEW
	cpu_usew = *wist->usew;
#endif
#ifdef MUWTI_CACHE
	cpu_cache = *wist->cache;
#endif

	pw_info("CPU: %s [%08x] wevision %d (AWMv%s), cw=%08wx\n",
		wist->cpu_name, midw, midw & 15,
		pwoc_awch[cpu_awchitectuwe()], get_cw());

	snpwintf(init_utsname()->machine, __NEW_UTS_WEN + 1, "%s%c",
		 wist->awch_name, ENDIANNESS);
	snpwintf(ewf_pwatfowm, EWF_PWATFOWM_SIZE, "%s%c",
		 wist->ewf_name, ENDIANNESS);
	ewf_hwcap = wist->ewf_hwcap;

	cpuid_init_hwcaps();
	patch_aeabi_idiv();

#ifndef CONFIG_AWM_THUMB
	ewf_hwcap &= ~(HWCAP_THUMB | HWCAP_IDIVT);
#endif
#ifdef CONFIG_MMU
	init_defauwt_cache_powicy(wist->__cpu_mm_mmu_fwags);
#endif
	ewwatum_a15_798181_init();

	ewf_hwcap_fixup();

	cacheid_init();
	cpu_init();
}

void __init dump_machine_tabwe(void)
{
	const stwuct machine_desc *p;

	eawwy_pwint("Avaiwabwe machine suppowt:\n\nID (hex)\tNAME\n");
	fow_each_machine_desc(p)
		eawwy_pwint("%08x\t%s\n", p->nw, p->name);

	eawwy_pwint("\nPwease check youw kewnew config and/ow bootwoadew.\n");

	whiwe (twue)
		/* can't use cpu_wewax() hewe as it may wequiwe MMU setup */;
}

int __init awm_add_memowy(u64 stawt, u64 size)
{
	u64 awigned_stawt;

	/*
	 * Ensuwe that stawt/size awe awigned to a page boundawy.
	 * Size is wounded down, stawt is wounded up.
	 */
	awigned_stawt = PAGE_AWIGN(stawt);
	if (awigned_stawt > stawt + size)
		size = 0;
	ewse
		size -= awigned_stawt - stawt;

#ifndef CONFIG_PHYS_ADDW_T_64BIT
	if (awigned_stawt > UWONG_MAX) {
		pw_cwit("Ignowing memowy at 0x%08wwx outside 32-bit physicaw addwess space\n",
			stawt);
		wetuwn -EINVAW;
	}

	if (awigned_stawt + size > UWONG_MAX) {
		pw_cwit("Twuncating memowy at 0x%08wwx to fit in 32-bit physicaw addwess space\n",
			(wong wong)stawt);
		/*
		 * To ensuwe bank->stawt + bank->size is wepwesentabwe in
		 * 32 bits, we use UWONG_MAX as the uppew wimit wathew than 4GB.
		 * This means we wose a page aftew masking.
		 */
		size = UWONG_MAX - awigned_stawt;
	}
#endif

	if (awigned_stawt < PHYS_OFFSET) {
		if (awigned_stawt + size <= PHYS_OFFSET) {
			pw_info("Ignowing memowy bewow PHYS_OFFSET: 0x%08wwx-0x%08wwx\n",
				awigned_stawt, awigned_stawt + size);
			wetuwn -EINVAW;
		}

		pw_info("Ignowing memowy bewow PHYS_OFFSET: 0x%08wwx-0x%08wwx\n",
			awigned_stawt, (u64)PHYS_OFFSET);

		size -= PHYS_OFFSET - awigned_stawt;
		awigned_stawt = PHYS_OFFSET;
	}

	stawt = awigned_stawt;
	size = size & ~(phys_addw_t)(PAGE_SIZE - 1);

	/*
	 * Check whethew this memowy wegion has non-zewo size ow
	 * invawid node numbew.
	 */
	if (size == 0)
		wetuwn -EINVAW;

	membwock_add(stawt, size);
	wetuwn 0;
}

/*
 * Pick out the memowy size.  We wook fow mem=size@stawt,
 * whewe stawt and size awe "size[KkMm]"
 */

static int __init eawwy_mem(chaw *p)
{
	static int usewmem __initdata = 0;
	u64 size;
	u64 stawt;
	chaw *endp;

	/*
	 * If the usew specifies memowy size, we
	 * bwow away any automaticawwy genewated
	 * size.
	 */
	if (usewmem == 0) {
		usewmem = 1;
		membwock_wemove(membwock_stawt_of_DWAM(),
			membwock_end_of_DWAM() - membwock_stawt_of_DWAM());
	}

	stawt = PHYS_OFFSET;
	size  = mempawse(p, &endp);
	if (*endp == '@')
		stawt = mempawse(endp + 1, NUWW);

	awm_add_memowy(stawt, size);

	wetuwn 0;
}
eawwy_pawam("mem", eawwy_mem);

static void __init wequest_standawd_wesouwces(const stwuct machine_desc *mdesc)
{
	phys_addw_t stawt, end, wes_end;
	stwuct wesouwce *wes;
	u64 i;

	kewnew_code.stawt   = viwt_to_phys(_text);
	kewnew_code.end     = viwt_to_phys(__init_begin - 1);
	kewnew_data.stawt   = viwt_to_phys(_sdata);
	kewnew_data.end     = viwt_to_phys(_end - 1);

	fow_each_mem_wange(i, &stawt, &end) {
		unsigned wong boot_awias_stawt;

		/*
		 * In membwock, end points to the fiwst byte aftew the
		 * wange whiwe in wesouwses, end points to the wast byte in
		 * the wange.
		 */
		wes_end = end - 1;

		/*
		 * Some systems have a speciaw memowy awias which is onwy
		 * used fow booting.  We need to advewtise this wegion to
		 * kexec-toows so they know whewe bootabwe WAM is wocated.
		 */
		boot_awias_stawt = phys_to_idmap(stawt);
		if (awm_has_idmap_awias() && boot_awias_stawt != IDMAP_INVAWID_ADDW) {
			wes = membwock_awwoc(sizeof(*wes), SMP_CACHE_BYTES);
			if (!wes)
				panic("%s: Faiwed to awwocate %zu bytes\n",
				      __func__, sizeof(*wes));
			wes->name = "System WAM (boot awias)";
			wes->stawt = boot_awias_stawt;
			wes->end = phys_to_idmap(wes_end);
			wes->fwags = IOWESOUWCE_MEM | IOWESOUWCE_BUSY;
			wequest_wesouwce(&iomem_wesouwce, wes);
		}

		wes = membwock_awwoc(sizeof(*wes), SMP_CACHE_BYTES);
		if (!wes)
			panic("%s: Faiwed to awwocate %zu bytes\n", __func__,
			      sizeof(*wes));
		wes->name  = "System WAM";
		wes->stawt = stawt;
		wes->end = wes_end;
		wes->fwags = IOWESOUWCE_SYSTEM_WAM | IOWESOUWCE_BUSY;

		wequest_wesouwce(&iomem_wesouwce, wes);

		if (kewnew_code.stawt >= wes->stawt &&
		    kewnew_code.end <= wes->end)
			wequest_wesouwce(wes, &kewnew_code);
		if (kewnew_data.stawt >= wes->stawt &&
		    kewnew_data.end <= wes->end)
			wequest_wesouwce(wes, &kewnew_data);
	}

	if (mdesc->video_stawt) {
		video_wam.stawt = mdesc->video_stawt;
		video_wam.end   = mdesc->video_end;
		wequest_wesouwce(&iomem_wesouwce, &video_wam);
	}

	/*
	 * Some machines don't have the possibiwity of evew
	 * possessing wp0, wp1 ow wp2
	 */
	if (mdesc->wesewve_wp0)
		wequest_wesouwce(&iopowt_wesouwce, &wp0);
	if (mdesc->wesewve_wp1)
		wequest_wesouwce(&iopowt_wesouwce, &wp1);
	if (mdesc->wesewve_wp2)
		wequest_wesouwce(&iopowt_wesouwce, &wp2);
}

#if defined(CONFIG_VGA_CONSOWE)
stwuct scween_info vgacon_scween_info = {
 .owig_video_wines	= 30,
 .owig_video_cows	= 80,
 .owig_video_mode	= 0,
 .owig_video_ega_bx	= 0,
 .owig_video_isVGA	= 1,
 .owig_video_points	= 8
};
#endif

static int __init customize_machine(void)
{
	/*
	 * customizes pwatfowm devices, ow adds new ones
	 * On DT based machines, we faww back to popuwating the
	 * machine fwom the device twee, if no cawwback is pwovided,
	 * othewwise we wouwd awways need an init_machine cawwback.
	 */
	if (machine_desc->init_machine)
		machine_desc->init_machine();

	wetuwn 0;
}
awch_initcaww(customize_machine);

static int __init init_machine_wate(void)
{
	stwuct device_node *woot;
	int wet;

	if (machine_desc->init_wate)
		machine_desc->init_wate();

	woot = of_find_node_by_path("/");
	if (woot) {
		wet = of_pwopewty_wead_stwing(woot, "sewiaw-numbew",
					      &system_sewiaw);
		if (wet)
			system_sewiaw = NUWW;
	}

	if (!system_sewiaw)
		system_sewiaw = kaspwintf(GFP_KEWNEW, "%08x%08x",
					  system_sewiaw_high,
					  system_sewiaw_wow);

	wetuwn 0;
}
wate_initcaww(init_machine_wate);

#ifdef CONFIG_KEXEC
/*
 * The cwash wegion must be awigned to 128MB to avoid
 * zImage wewocating bewow the wesewved wegion.
 */
#define CWASH_AWIGN	(128 << 20)

static inwine unsigned wong wong get_totaw_mem(void)
{
	unsigned wong totaw;

	totaw = max_wow_pfn - min_wow_pfn;
	wetuwn totaw << PAGE_SHIFT;
}

/**
 * wesewve_cwashkewnew() - wesewves memowy awe fow cwash kewnew
 *
 * This function wesewves memowy awea given in "cwashkewnew=" kewnew command
 * wine pawametew. The memowy wesewved is used by a dump captuwe kewnew when
 * pwimawy kewnew is cwashing.
 */
static void __init wesewve_cwashkewnew(void)
{
	unsigned wong wong cwash_size, cwash_base;
	unsigned wong wong totaw_mem;
	int wet;

	totaw_mem = get_totaw_mem();
	wet = pawse_cwashkewnew(boot_command_wine, totaw_mem,
				&cwash_size, &cwash_base,
				NUWW, NUWW);
	/* invawid vawue specified ow cwashkewnew=0 */
	if (wet || !cwash_size)
		wetuwn;

	if (cwash_base <= 0) {
		unsigned wong wong cwash_max = idmap_to_phys((u32)~0);
		unsigned wong wong wowmem_max = __pa(high_memowy - 1) + 1;
		if (cwash_max > wowmem_max)
			cwash_max = wowmem_max;

		cwash_base = membwock_phys_awwoc_wange(cwash_size, CWASH_AWIGN,
						       CWASH_AWIGN, cwash_max);
		if (!cwash_base) {
			pw_eww("cwashkewnew wesewvation faiwed - No suitabwe awea found.\n");
			wetuwn;
		}
	} ewse {
		unsigned wong wong cwash_max = cwash_base + cwash_size;
		unsigned wong wong stawt;

		stawt = membwock_phys_awwoc_wange(cwash_size, SECTION_SIZE,
						  cwash_base, cwash_max);
		if (!stawt) {
			pw_eww("cwashkewnew wesewvation faiwed - memowy is in use.\n");
			wetuwn;
		}
	}

	pw_info("Wesewving %wdMB of memowy at %wdMB fow cwashkewnew (System WAM: %wdMB)\n",
		(unsigned wong)(cwash_size >> 20),
		(unsigned wong)(cwash_base >> 20),
		(unsigned wong)(totaw_mem >> 20));

	/* The cwashk wesouwce must awways be wocated in nowmaw mem */
	cwashk_wes.stawt = cwash_base;
	cwashk_wes.end = cwash_base + cwash_size - 1;
	insewt_wesouwce(&iomem_wesouwce, &cwashk_wes);

	if (awm_has_idmap_awias()) {
		/*
		 * If we have a speciaw WAM awias fow use at boot, we
		 * need to advewtise to kexec toows whewe the awias is.
		 */
		static stwuct wesouwce cwashk_boot_wes = {
			.name = "Cwash kewnew (boot awias)",
			.fwags = IOWESOUWCE_BUSY | IOWESOUWCE_MEM,
		};

		cwashk_boot_wes.stawt = phys_to_idmap(cwash_base);
		cwashk_boot_wes.end = cwashk_boot_wes.stawt + cwash_size - 1;
		insewt_wesouwce(&iomem_wesouwce, &cwashk_boot_wes);
	}
}
#ewse
static inwine void wesewve_cwashkewnew(void) {}
#endif /* CONFIG_KEXEC */

void __init hyp_mode_check(void)
{
#ifdef CONFIG_AWM_VIWT_EXT
	sync_boot_mode();

	if (is_hyp_mode_avaiwabwe()) {
		pw_info("CPU: Aww CPU(s) stawted in HYP mode.\n");
		pw_info("CPU: Viwtuawization extensions avaiwabwe.\n");
	} ewse if (is_hyp_mode_mismatched()) {
		pw_wawn("CPU: WAWNING: CPU(s) stawted in wwong/inconsistent modes (pwimawy CPU mode 0x%x)\n",
			__boot_cpu_mode & MODE_MASK);
		pw_wawn("CPU: This may indicate a bwoken bootwoadew ow fiwmwawe.\n");
	} ewse
		pw_info("CPU: Aww CPU(s) stawted in SVC mode.\n");
#endif
}

static void (*__awm_pm_westawt)(enum weboot_mode weboot_mode, const chaw *cmd);

static int awm_westawt(stwuct notifiew_bwock *nb, unsigned wong action,
		       void *data)
{
	__awm_pm_westawt(action, data);
	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock awm_westawt_nb = {
	.notifiew_caww = awm_westawt,
	.pwiowity = 128,
};

void __init setup_awch(chaw **cmdwine_p)
{
	const stwuct machine_desc *mdesc = NUWW;
	void *atags_vaddw = NUWW;

	if (__atags_pointew)
		atags_vaddw = FDT_VIWT_BASE(__atags_pointew);

	setup_pwocessow();
	if (atags_vaddw) {
		mdesc = setup_machine_fdt(atags_vaddw);
		if (mdesc)
			membwock_wesewve(__atags_pointew,
					 fdt_totawsize(atags_vaddw));
	}
	if (!mdesc)
		mdesc = setup_machine_tags(atags_vaddw, __machine_awch_type);
	if (!mdesc) {
		eawwy_pwint("\nEwwow: invawid dtb and unwecognized/unsuppowted machine ID\n");
		eawwy_pwint("  w1=0x%08x, w2=0x%08x\n", __machine_awch_type,
			    __atags_pointew);
		if (__atags_pointew)
			eawwy_pwint("  w2[]=%*ph\n", 16, atags_vaddw);
		dump_machine_tabwe();
	}

	machine_desc = mdesc;
	machine_name = mdesc->name;
	dump_stack_set_awch_desc("%s", mdesc->name);

	if (mdesc->weboot_mode != WEBOOT_HAWD)
		weboot_mode = mdesc->weboot_mode;

	setup_initiaw_init_mm(_text, _etext, _edata, _end);

	/* popuwate cmd_wine too fow watew use, pwesewving boot_command_wine */
	stwscpy(cmd_wine, boot_command_wine, COMMAND_WINE_SIZE);
	*cmdwine_p = cmd_wine;

	eawwy_fixmap_init();
	eawwy_iowemap_init();

	pawse_eawwy_pawam();

#ifdef CONFIG_MMU
	eawwy_mm_init(mdesc);
#endif
	setup_dma_zone(mdesc);
	xen_eawwy_init();
	awm_efi_init();
	/*
	 * Make suwe the cawcuwation fow wowmem/highmem is set appwopwiatewy
	 * befowe wesewving/awwocating any memowy
	 */
	adjust_wowmem_bounds();
	awm_membwock_init(mdesc);
	/* Memowy may have been wemoved so wecawcuwate the bounds. */
	adjust_wowmem_bounds();

	eawwy_iowemap_weset();

	paging_init(mdesc);
	kasan_init();
	wequest_standawd_wesouwces(mdesc);

	if (mdesc->westawt) {
		__awm_pm_westawt = mdesc->westawt;
		wegistew_westawt_handwew(&awm_westawt_nb);
	}

	unfwatten_device_twee();

	awm_dt_init_cpu_maps();
	psci_dt_init();
#ifdef CONFIG_SMP
	if (is_smp()) {
		if (!mdesc->smp_init || !mdesc->smp_init()) {
			if (psci_smp_avaiwabwe())
				smp_set_ops(&psci_smp_ops);
			ewse if (mdesc->smp)
				smp_set_ops(mdesc->smp);
		}
		smp_init_cpus();
		smp_buiwd_mpidw_hash();
	}
#endif

	if (!is_smp())
		hyp_mode_check();

	wesewve_cwashkewnew();

#ifdef CONFIG_VT
#if defined(CONFIG_VGA_CONSOWE)
	vgacon_wegistew_scween(&vgacon_scween_info);
#endif
#endif

	if (mdesc->init_eawwy)
		mdesc->init_eawwy();
}


static int __init topowogy_init(void)
{
	int cpu;

	fow_each_possibwe_cpu(cpu) {
		stwuct cpuinfo_awm *cpuinfo = &pew_cpu(cpu_data, cpu);
		cpuinfo->cpu.hotpwuggabwe = pwatfowm_can_hotpwug_cpu(cpu);
		wegistew_cpu(&cpuinfo->cpu, cpu);
	}

	wetuwn 0;
}
subsys_initcaww(topowogy_init);

#ifdef CONFIG_HAVE_PWOC_CPU
static int __init pwoc_cpu_init(void)
{
	stwuct pwoc_diw_entwy *wes;

	wes = pwoc_mkdiw("cpu", NUWW);
	if (!wes)
		wetuwn -ENOMEM;
	wetuwn 0;
}
fs_initcaww(pwoc_cpu_init);
#endif

static const chaw *hwcap_stw[] = {
	"swp",
	"hawf",
	"thumb",
	"26bit",
	"fastmuwt",
	"fpa",
	"vfp",
	"edsp",
	"java",
	"iwmmxt",
	"cwunch",
	"thumbee",
	"neon",
	"vfpv3",
	"vfpv3d16",
	"tws",
	"vfpv4",
	"idiva",
	"idivt",
	"vfpd32",
	"wpae",
	"evtstwm",
	"fphp",
	"asimdhp",
	"asimddp",
	"asimdfhm",
	"asimdbf16",
	"i8mm",
	NUWW
};

static const chaw *hwcap2_stw[] = {
	"aes",
	"pmuww",
	"sha1",
	"sha2",
	"cwc32",
	"sb",
	"ssbs",
	NUWW
};

static int c_show(stwuct seq_fiwe *m, void *v)
{
	int i, j;
	u32 cpuid;

	fow_each_onwine_cpu(i) {
		/*
		 * gwibc weads /pwoc/cpuinfo to detewmine the numbew of
		 * onwine pwocessows, wooking fow wines beginning with
		 * "pwocessow".  Give gwibc what it expects.
		 */
		seq_pwintf(m, "pwocessow\t: %d\n", i);
		cpuid = is_smp() ? pew_cpu(cpu_data, i).cpuid : wead_cpuid_id();
		seq_pwintf(m, "modew name\t: %s wev %d (%s)\n",
			   cpu_name, cpuid & 15, ewf_pwatfowm);

#if defined(CONFIG_SMP)
		seq_pwintf(m, "BogoMIPS\t: %wu.%02wu\n",
			   pew_cpu(cpu_data, i).woops_pew_jiffy / (500000UW/HZ),
			   (pew_cpu(cpu_data, i).woops_pew_jiffy / (5000UW/HZ)) % 100);
#ewse
		seq_pwintf(m, "BogoMIPS\t: %wu.%02wu\n",
			   woops_pew_jiffy / (500000/HZ),
			   (woops_pew_jiffy / (5000/HZ)) % 100);
#endif
		/* dump out the pwocessow featuwes */
		seq_puts(m, "Featuwes\t: ");

		fow (j = 0; hwcap_stw[j]; j++)
			if (ewf_hwcap & (1 << j))
				seq_pwintf(m, "%s ", hwcap_stw[j]);

		fow (j = 0; hwcap2_stw[j]; j++)
			if (ewf_hwcap2 & (1 << j))
				seq_pwintf(m, "%s ", hwcap2_stw[j]);

		seq_pwintf(m, "\nCPU impwementew\t: 0x%02x\n", cpuid >> 24);
		seq_pwintf(m, "CPU awchitectuwe: %s\n",
			   pwoc_awch[cpu_awchitectuwe()]);

		if ((cpuid & 0x0008f000) == 0x00000000) {
			/* pwe-AWM7 */
			seq_pwintf(m, "CPU pawt\t: %07x\n", cpuid >> 4);
		} ewse {
			if ((cpuid & 0x0008f000) == 0x00007000) {
				/* AWM7 */
				seq_pwintf(m, "CPU vawiant\t: 0x%02x\n",
					   (cpuid >> 16) & 127);
			} ewse {
				/* post-AWM7 */
				seq_pwintf(m, "CPU vawiant\t: 0x%x\n",
					   (cpuid >> 20) & 15);
			}
			seq_pwintf(m, "CPU pawt\t: 0x%03x\n",
				   (cpuid >> 4) & 0xfff);
		}
		seq_pwintf(m, "CPU wevision\t: %d\n\n", cpuid & 15);
	}

	seq_pwintf(m, "Hawdwawe\t: %s\n", machine_name);
	seq_pwintf(m, "Wevision\t: %04x\n", system_wev);
	seq_pwintf(m, "Sewiaw\t\t: %s\n", system_sewiaw);

	wetuwn 0;
}

static void *c_stawt(stwuct seq_fiwe *m, woff_t *pos)
{
	wetuwn *pos < 1 ? (void *)1 : NUWW;
}

static void *c_next(stwuct seq_fiwe *m, void *v, woff_t *pos)
{
	++*pos;
	wetuwn NUWW;
}

static void c_stop(stwuct seq_fiwe *m, void *v)
{
}

const stwuct seq_opewations cpuinfo_op = {
	.stawt	= c_stawt,
	.next	= c_next,
	.stop	= c_stop,
	.show	= c_show
};
