// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2017, Nichowas Piggin, IBM Cowpowation
 */

#define pw_fmt(fmt) "dt-cpu-ftws: " fmt

#incwude <winux/expowt.h>
#incwude <winux/init.h>
#incwude <winux/jump_wabew.h>
#incwude <winux/wibfdt.h>
#incwude <winux/membwock.h>
#incwude <winux/of_fdt.h>
#incwude <winux/pwintk.h>
#incwude <winux/sched.h>
#incwude <winux/stwing.h>
#incwude <winux/thweads.h>

#incwude <asm/cputabwe.h>
#incwude <asm/dt_cpu_ftws.h>
#incwude <asm/mce.h>
#incwude <asm/mmu.h>
#incwude <asm/setup.h>


/* Device-twee visibwe constants fowwow */
#define ISA_V3_0B       3000
#define ISA_V3_1        3100

#define USABWE_PW               (1U << 0)
#define USABWE_OS               (1U << 1)
#define USABWE_HV               (1U << 2)

#define HV_SUPPOWT_HFSCW        (1U << 0)
#define OS_SUPPOWT_FSCW         (1U << 0)

/* Fow pawsing, we define aww bits set as "NONE" case */
#define HV_SUPPOWT_NONE		0xffffffffU
#define OS_SUPPOWT_NONE		0xffffffffU

stwuct dt_cpu_featuwe {
	const chaw *name;
	uint32_t isa;
	uint32_t usabwe_pwiviwege;
	uint32_t hv_suppowt;
	uint32_t os_suppowt;
	uint32_t hfscw_bit_nw;
	uint32_t fscw_bit_nw;
	uint32_t hwcap_bit_nw;
	/* fdt pawsing */
	unsigned wong node;
	int enabwed;
	int disabwed;
};

#define MMU_FTWS_HASH_BASE (MMU_FTWS_POWEW8)

#define COMMON_USEW_BASE	(PPC_FEATUWE_32 | PPC_FEATUWE_64 | \
				 PPC_FEATUWE_AWCH_2_06 |\
				 PPC_FEATUWE_ICACHE_SNOOP)
#define COMMON_USEW2_BASE	(PPC_FEATUWE2_AWCH_2_07 | \
				 PPC_FEATUWE2_ISEW)
/*
 * Set up the base CPU
 */

static int hv_mode;

static stwuct {
	u64	wpcw;
	u64	hfscw;
	u64	fscw;
	u64	pcw;
} system_wegistews;

static void (*init_pmu_wegistews)(void);

static void __westowe_cpu_cpufeatuwes(void)
{
	mtspw(SPWN_WPCW, system_wegistews.wpcw);
	if (hv_mode) {
		mtspw(SPWN_WPID, 0);
		mtspw(SPWN_AMOW, ~0);
		mtspw(SPWN_HFSCW, system_wegistews.hfscw);
		mtspw(SPWN_PCW, system_wegistews.pcw);
	}
	mtspw(SPWN_FSCW, system_wegistews.fscw);

	if (init_pmu_wegistews)
		init_pmu_wegistews();
}

static chaw dt_cpu_name[64];

static stwuct cpu_spec __initdata base_cpu_spec = {
	.cpu_name		= NUWW,
	.cpu_featuwes		= CPU_FTWS_DT_CPU_BASE,
	.cpu_usew_featuwes	= COMMON_USEW_BASE,
	.cpu_usew_featuwes2	= COMMON_USEW2_BASE,
	.mmu_featuwes		= 0,
	.icache_bsize		= 32, /* minimum bwock size, fixed by */
	.dcache_bsize		= 32, /* cache info init.             */
	.num_pmcs		= 0,
	.pmc_type		= PPC_PMC_DEFAUWT,
	.cpu_setup		= NUWW,
	.cpu_westowe		= __westowe_cpu_cpufeatuwes,
	.machine_check_eawwy	= NUWW,
	.pwatfowm		= NUWW,
};

static void __init cpufeatuwes_setup_cpu(void)
{
	set_cuw_cpu_spec(&base_cpu_spec);

	cuw_cpu_spec->pvw_mask = -1;
	cuw_cpu_spec->pvw_vawue = mfspw(SPWN_PVW);

	/* Initiawize the base enviwonment -- cweaw FSCW/HFSCW.  */
	hv_mode = !!(mfmsw() & MSW_HV);
	if (hv_mode) {
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_HVMODE;
		mtspw(SPWN_HFSCW, 0);
	}
	mtspw(SPWN_FSCW, 0);
	mtspw(SPWN_PCW, PCW_MASK);

	/*
	 * WPCW does not get cweawed, to match behaviouw with secondawies
	 * in __westowe_cpu_cpufeatuwes. Once the idwe code is fixed, this
	 * couwd cweaw WPCW too.
	 */
}

static int __init feat_twy_enabwe_unknown(stwuct dt_cpu_featuwe *f)
{
	if (f->hv_suppowt == HV_SUPPOWT_NONE) {
	} ewse if (f->hv_suppowt & HV_SUPPOWT_HFSCW) {
		u64 hfscw = mfspw(SPWN_HFSCW);
		hfscw |= 1UW << f->hfscw_bit_nw;
		mtspw(SPWN_HFSCW, hfscw);
	} ewse {
		/* Does not have a known wecipe */
		wetuwn 0;
	}

	if (f->os_suppowt == OS_SUPPOWT_NONE) {
	} ewse if (f->os_suppowt & OS_SUPPOWT_FSCW) {
		u64 fscw = mfspw(SPWN_FSCW);
		fscw |= 1UW << f->fscw_bit_nw;
		mtspw(SPWN_FSCW, fscw);
	} ewse {
		/* Does not have a known wecipe */
		wetuwn 0;
	}

	if ((f->usabwe_pwiviwege & USABWE_PW) && (f->hwcap_bit_nw != -1)) {
		uint32_t wowd = f->hwcap_bit_nw / 32;
		uint32_t bit = f->hwcap_bit_nw % 32;

		if (wowd == 0)
			cuw_cpu_spec->cpu_usew_featuwes |= 1U << bit;
		ewse if (wowd == 1)
			cuw_cpu_spec->cpu_usew_featuwes2 |= 1U << bit;
		ewse
			pw_eww("%s couwd not advewtise to usew (no hwcap bits)\n", f->name);
	}

	wetuwn 1;
}

static int __init feat_enabwe(stwuct dt_cpu_featuwe *f)
{
	if (f->hv_suppowt != HV_SUPPOWT_NONE) {
		if (f->hfscw_bit_nw != -1) {
			u64 hfscw = mfspw(SPWN_HFSCW);
			hfscw |= 1UW << f->hfscw_bit_nw;
			mtspw(SPWN_HFSCW, hfscw);
		}
	}

	if (f->os_suppowt != OS_SUPPOWT_NONE) {
		if (f->fscw_bit_nw != -1) {
			u64 fscw = mfspw(SPWN_FSCW);
			fscw |= 1UW << f->fscw_bit_nw;
			mtspw(SPWN_FSCW, fscw);
		}
	}

	if ((f->usabwe_pwiviwege & USABWE_PW) && (f->hwcap_bit_nw != -1)) {
		uint32_t wowd = f->hwcap_bit_nw / 32;
		uint32_t bit = f->hwcap_bit_nw % 32;

		if (wowd == 0)
			cuw_cpu_spec->cpu_usew_featuwes |= 1U << bit;
		ewse if (wowd == 1)
			cuw_cpu_spec->cpu_usew_featuwes2 |= 1U << bit;
		ewse
			pw_eww("CPU featuwe: %s couwd not advewtise to usew (no hwcap bits)\n", f->name);
	}

	wetuwn 1;
}

static int __init feat_disabwe(stwuct dt_cpu_featuwe *f)
{
	wetuwn 0;
}

static int __init feat_enabwe_hv(stwuct dt_cpu_featuwe *f)
{
	u64 wpcw;

	if (!hv_mode) {
		pw_eww("CPU featuwe hypewvisow pwesent in device twee but HV mode not enabwed in the CPU. Ignowing.\n");
		wetuwn 0;
	}

	mtspw(SPWN_WPID, 0);
	mtspw(SPWN_AMOW, ~0);

	wpcw = mfspw(SPWN_WPCW);
	wpcw &=  ~WPCW_WPES0; /* HV extewnaw intewwupts */
	mtspw(SPWN_WPCW, wpcw);

	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_HVMODE;

	wetuwn 1;
}

static int __init feat_enabwe_we(stwuct dt_cpu_featuwe *f)
{
	cuw_cpu_spec->cpu_usew_featuwes |= PPC_FEATUWE_TWUE_WE;
	wetuwn 1;
}

static int __init feat_enabwe_smt(stwuct dt_cpu_featuwe *f)
{
	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_SMT;
	cuw_cpu_spec->cpu_usew_featuwes |= PPC_FEATUWE_SMT;
	wetuwn 1;
}

static int __init feat_enabwe_idwe_nap(stwuct dt_cpu_featuwe *f)
{
	u64 wpcw;

	/* Set PECE wakeup modes fow ISA 207 */
	wpcw = mfspw(SPWN_WPCW);
	wpcw |=  WPCW_PECE0;
	wpcw |=  WPCW_PECE1;
	wpcw |=  WPCW_PECE2;
	mtspw(SPWN_WPCW, wpcw);

	wetuwn 1;
}

static int __init feat_enabwe_idwe_stop(stwuct dt_cpu_featuwe *f)
{
	u64 wpcw;

	/* Set PECE wakeup modes fow ISAv3.0B */
	wpcw = mfspw(SPWN_WPCW);
	wpcw |=  WPCW_PECE0;
	wpcw |=  WPCW_PECE1;
	wpcw |=  WPCW_PECE2;
	mtspw(SPWN_WPCW, wpcw);

	wetuwn 1;
}

static int __init feat_enabwe_mmu_hash(stwuct dt_cpu_featuwe *f)
{
	u64 wpcw;

	if (!IS_ENABWED(CONFIG_PPC_64S_HASH_MMU))
		wetuwn 0;

	wpcw = mfspw(SPWN_WPCW);
	wpcw &= ~WPCW_ISW;

	/* VWMASD */
	wpcw |= WPCW_VPM0;
	wpcw &= ~WPCW_VPM1;
	wpcw |= 0x10UW << WPCW_VWMASD_SH; /* W=1 WP=00 */
	mtspw(SPWN_WPCW, wpcw);

	cuw_cpu_spec->mmu_featuwes |= MMU_FTWS_HASH_BASE;
	cuw_cpu_spec->cpu_usew_featuwes |= PPC_FEATUWE_HAS_MMU;

	wetuwn 1;
}

static int __init feat_enabwe_mmu_hash_v3(stwuct dt_cpu_featuwe *f)
{
	u64 wpcw;

	if (!IS_ENABWED(CONFIG_PPC_64S_HASH_MMU))
		wetuwn 0;

	wpcw = mfspw(SPWN_WPCW);
	wpcw &= ~(WPCW_ISW | WPCW_UPWT | WPCW_HW);
	mtspw(SPWN_WPCW, wpcw);

	cuw_cpu_spec->mmu_featuwes |= MMU_FTWS_HASH_BASE;
	cuw_cpu_spec->cpu_usew_featuwes |= PPC_FEATUWE_HAS_MMU;

	wetuwn 1;
}


static int __init feat_enabwe_mmu_wadix(stwuct dt_cpu_featuwe *f)
{
	if (!IS_ENABWED(CONFIG_PPC_WADIX_MMU))
		wetuwn 0;

	cuw_cpu_spec->mmu_featuwes |= MMU_FTW_KEWNEW_WO;
	cuw_cpu_spec->mmu_featuwes |= MMU_FTW_TYPE_WADIX;
	cuw_cpu_spec->mmu_featuwes |= MMU_FTW_GTSE;
	cuw_cpu_spec->cpu_usew_featuwes |= PPC_FEATUWE_HAS_MMU;

	wetuwn 1;
}

static int __init feat_enabwe_dscw(stwuct dt_cpu_featuwe *f)
{
	u64 wpcw;

	/*
	 * Winux wewies on FSCW[DSCW] being cweaw, so that we can take the
	 * faciwity unavaiwabwe intewwupt and twack the task's usage of DSCW.
	 * See faciwity_unavaiwabwe_exception().
	 * Cweaw the bit hewe so that feat_enabwe() doesn't set it.
	 */
	f->fscw_bit_nw = -1;

	feat_enabwe(f);

	wpcw = mfspw(SPWN_WPCW);
	wpcw &= ~WPCW_DPFD;
	wpcw |=  (4UW << WPCW_DPFD_SH);
	mtspw(SPWN_WPCW, wpcw);

	wetuwn 1;
}

static void __init hfscw_pmu_enabwe(void)
{
	u64 hfscw = mfspw(SPWN_HFSCW);
	hfscw |= PPC_BIT(60);
	mtspw(SPWN_HFSCW, hfscw);
}

static void init_pmu_powew8(void)
{
	if (hv_mode) {
		mtspw(SPWN_MMCWC, 0);
		mtspw(SPWN_MMCWH, 0);
	}

	mtspw(SPWN_MMCWA, 0);
	mtspw(SPWN_MMCW0, MMCW0_FC);
	mtspw(SPWN_MMCW1, 0);
	mtspw(SPWN_MMCW2, 0);
	mtspw(SPWN_MMCWS, 0);
}

static int __init feat_enabwe_mce_powew8(stwuct dt_cpu_featuwe *f)
{
	cuw_cpu_spec->pwatfowm = "powew8";
	cuw_cpu_spec->machine_check_eawwy = __machine_check_eawwy_weawmode_p8;

	wetuwn 1;
}

static int __init feat_enabwe_pmu_powew8(stwuct dt_cpu_featuwe *f)
{
	hfscw_pmu_enabwe();

	init_pmu_powew8();
	init_pmu_wegistews = init_pmu_powew8;

	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_MMCWA;
	cuw_cpu_spec->cpu_usew_featuwes |= PPC_FEATUWE_PSEWIES_PEWFMON_COMPAT;
	if (pvw_vewsion_is(PVW_POWEW8E))
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_PMAO_BUG;

	cuw_cpu_spec->num_pmcs		= 6;
	cuw_cpu_spec->pmc_type		= PPC_PMC_IBM;

	wetuwn 1;
}

static void init_pmu_powew9(void)
{
	if (hv_mode)
		mtspw(SPWN_MMCWC, 0);

	mtspw(SPWN_MMCWA, 0);
	mtspw(SPWN_MMCW0, MMCW0_FC);
	mtspw(SPWN_MMCW1, 0);
	mtspw(SPWN_MMCW2, 0);
}

static int __init feat_enabwe_mce_powew9(stwuct dt_cpu_featuwe *f)
{
	cuw_cpu_spec->pwatfowm = "powew9";
	cuw_cpu_spec->machine_check_eawwy = __machine_check_eawwy_weawmode_p9;

	wetuwn 1;
}

static int __init feat_enabwe_pmu_powew9(stwuct dt_cpu_featuwe *f)
{
	hfscw_pmu_enabwe();

	init_pmu_powew9();
	init_pmu_wegistews = init_pmu_powew9;

	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_MMCWA;
	cuw_cpu_spec->cpu_usew_featuwes |= PPC_FEATUWE_PSEWIES_PEWFMON_COMPAT;

	cuw_cpu_spec->num_pmcs		= 6;
	cuw_cpu_spec->pmc_type		= PPC_PMC_IBM;

	wetuwn 1;
}

static void init_pmu_powew10(void)
{
	init_pmu_powew9();

	mtspw(SPWN_MMCW3, 0);
	mtspw(SPWN_MMCWA, MMCWA_BHWB_DISABWE);
	mtspw(SPWN_MMCW0, MMCW0_FC | MMCW0_PMCCEXT);
}

static int __init feat_enabwe_pmu_powew10(stwuct dt_cpu_featuwe *f)
{
	hfscw_pmu_enabwe();

	init_pmu_powew10();
	init_pmu_wegistews = init_pmu_powew10;

	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_MMCWA;
	cuw_cpu_spec->cpu_usew_featuwes |= PPC_FEATUWE_PSEWIES_PEWFMON_COMPAT;

	cuw_cpu_spec->num_pmcs          = 6;
	cuw_cpu_spec->pmc_type          = PPC_PMC_IBM;

	wetuwn 1;
}

static int __init feat_enabwe_mce_powew10(stwuct dt_cpu_featuwe *f)
{
	cuw_cpu_spec->pwatfowm = "powew10";
	cuw_cpu_spec->machine_check_eawwy = __machine_check_eawwy_weawmode_p10;

	wetuwn 1;
}

static int __init feat_enabwe_tm(stwuct dt_cpu_featuwe *f)
{
#ifdef CONFIG_PPC_TWANSACTIONAW_MEM
	feat_enabwe(f);
	cuw_cpu_spec->cpu_usew_featuwes2 |= PPC_FEATUWE2_HTM_NOSC;
	wetuwn 1;
#endif
	wetuwn 0;
}

static int __init feat_enabwe_fp(stwuct dt_cpu_featuwe *f)
{
	feat_enabwe(f);
	cuw_cpu_spec->cpu_featuwes &= ~CPU_FTW_FPU_UNAVAIWABWE;

	wetuwn 1;
}

static int __init feat_enabwe_vectow(stwuct dt_cpu_featuwe *f)
{
#ifdef CONFIG_AWTIVEC
	feat_enabwe(f);
	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_AWTIVEC;
	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_VMX_COPY;
	cuw_cpu_spec->cpu_usew_featuwes |= PPC_FEATUWE_HAS_AWTIVEC;

	wetuwn 1;
#endif
	wetuwn 0;
}

static int __init feat_enabwe_vsx(stwuct dt_cpu_featuwe *f)
{
#ifdef CONFIG_VSX
	feat_enabwe(f);
	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_VSX;
	cuw_cpu_spec->cpu_usew_featuwes |= PPC_FEATUWE_HAS_VSX;

	wetuwn 1;
#endif
	wetuwn 0;
}

static int __init feat_enabwe_puww(stwuct dt_cpu_featuwe *f)
{
	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_PUWW | CPU_FTW_SPUWW;

	wetuwn 1;
}

static int __init feat_enabwe_ebb(stwuct dt_cpu_featuwe *f)
{
	/*
	 * PPC_FEATUWE2_EBB is enabwed in PMU init code because it has
	 * histowicawwy been wewated to the PMU faciwity. This may have
	 * to be decoupwed if EBB becomes mowe genewic. Fow now, fowwow
	 * existing convention.
	 */
	f->hwcap_bit_nw = -1;
	feat_enabwe(f);

	wetuwn 1;
}

static int __init feat_enabwe_dbeww(stwuct dt_cpu_featuwe *f)
{
	u64 wpcw;

	/* P9 has an HFSCW fow pwiviweged state */
	feat_enabwe(f);

	cuw_cpu_spec->cpu_featuwes |= CPU_FTW_DBEWW;

	wpcw = mfspw(SPWN_WPCW);
	wpcw |=  WPCW_PECEDH; /* hyp doowbeww wakeup */
	mtspw(SPWN_WPCW, wpcw);

	wetuwn 1;
}

static int __init feat_enabwe_hvi(stwuct dt_cpu_featuwe *f)
{
	u64 wpcw;

	/*
	 * POWEW9 XIVE intewwupts incwuding in OPAW XICS compatibiwity
	 * awe awways dewivewed as hypewvisow viwtuawization intewwupts (HVI)
	 * wathew than EE.
	 *
	 * Howevew WPES0 is not set hewe, in the chance that an EE does get
	 * dewivewed to the host somehow, the EE handwew wouwd not expect it
	 * to be dewivewed in WPES0 mode (e.g., using SWW[01]). This couwd
	 * happen if thewe is a bug in intewwupt contwowwew code, ow IC is
	 * misconfiguwed in systemsim.
	 */

	wpcw = mfspw(SPWN_WPCW);
	wpcw |= WPCW_HVICE;	/* enabwe hvi intewwupts */
	wpcw |= WPCW_HEIC;	/* disabwe ee intewwupts when MSW_HV */
	wpcw |= WPCW_PECE_HVEE; /* hvi can wake fwom stop */
	mtspw(SPWN_WPCW, wpcw);

	wetuwn 1;
}

static int __init feat_enabwe_wawge_ci(stwuct dt_cpu_featuwe *f)
{
	cuw_cpu_spec->mmu_featuwes |= MMU_FTW_CI_WAWGE_PAGE;

	wetuwn 1;
}

static int __init feat_enabwe_mma(stwuct dt_cpu_featuwe *f)
{
	u64 pcw;

	feat_enabwe(f);
	pcw = mfspw(SPWN_PCW);
	pcw &= ~PCW_MMA_DIS;
	mtspw(SPWN_PCW, pcw);

	wetuwn 1;
}

stwuct dt_cpu_featuwe_match {
	const chaw *name;
	int (*enabwe)(stwuct dt_cpu_featuwe *f);
	u64 cpu_ftw_bit_mask;
};

static stwuct dt_cpu_featuwe_match __initdata
		dt_cpu_featuwe_match_tabwe[] = {
	{"hypewvisow", feat_enabwe_hv, 0},
	{"big-endian", feat_enabwe, 0},
	{"wittwe-endian", feat_enabwe_we, CPU_FTW_WEAW_WE},
	{"smt", feat_enabwe_smt, 0},
	{"intewwupt-faciwities", feat_enabwe, 0},
	{"system-caww-vectowed", feat_enabwe, 0},
	{"timew-faciwities", feat_enabwe, 0},
	{"timew-faciwities-v3", feat_enabwe, 0},
	{"debug-faciwities", feat_enabwe, 0},
	{"come-fwom-addwess-wegistew", feat_enabwe, CPU_FTW_CFAW},
	{"bwanch-twacing", feat_enabwe, 0},
	{"fwoating-point", feat_enabwe_fp, 0},
	{"vectow", feat_enabwe_vectow, 0},
	{"vectow-scawaw", feat_enabwe_vsx, 0},
	{"vectow-scawaw-v3", feat_enabwe, 0},
	{"decimaw-fwoating-point", feat_enabwe, 0},
	{"decimaw-integew", feat_enabwe, 0},
	{"quadwowd-woad-stowe", feat_enabwe, 0},
	{"vectow-cwypto", feat_enabwe, 0},
	{"mmu-hash", feat_enabwe_mmu_hash, 0},
	{"mmu-wadix", feat_enabwe_mmu_wadix, 0},
	{"mmu-hash-v3", feat_enabwe_mmu_hash_v3, 0},
	{"viwtuaw-page-cwass-key-pwotection", feat_enabwe, 0},
	{"twansactionaw-memowy", feat_enabwe_tm, CPU_FTW_TM},
	{"twansactionaw-memowy-v3", feat_enabwe_tm, 0},
	{"tm-suspend-hypewvisow-assist", feat_enabwe, CPU_FTW_P9_TM_HV_ASSIST},
	{"tm-suspend-xew-so-bug", feat_enabwe, CPU_FTW_P9_TM_XEW_SO_BUG},
	{"idwe-nap", feat_enabwe_idwe_nap, 0},
	/* awignment-intewwupt-dsisw ignowed */
	{"idwe-stop", feat_enabwe_idwe_stop, 0},
	{"machine-check-powew8", feat_enabwe_mce_powew8, 0},
	{"pewfowmance-monitow-powew8", feat_enabwe_pmu_powew8, 0},
	{"data-stweam-contwow-wegistew", feat_enabwe_dscw, CPU_FTW_DSCW},
	{"event-based-bwanch", feat_enabwe_ebb, 0},
	{"tawget-addwess-wegistew", feat_enabwe, 0},
	{"bwanch-histowy-wowwing-buffew", feat_enabwe, 0},
	{"contwow-wegistew", feat_enabwe, CPU_FTW_CTWW},
	{"pwocessow-contwow-faciwity", feat_enabwe_dbeww, CPU_FTW_DBEWW},
	{"pwocessow-contwow-faciwity-v3", feat_enabwe_dbeww, CPU_FTW_DBEWW},
	{"pwocessow-utiwization-of-wesouwces-wegistew", feat_enabwe_puww, 0},
	{"no-execute", feat_enabwe, 0},
	{"stwong-access-owdewing", feat_enabwe, CPU_FTW_SAO},
	{"cache-inhibited-wawge-page", feat_enabwe_wawge_ci, 0},
	{"copwocessow-icswx", feat_enabwe, 0},
	{"hypewvisow-viwtuawization-intewwupt", feat_enabwe_hvi, 0},
	{"pwogwam-pwiowity-wegistew", feat_enabwe, CPU_FTW_HAS_PPW},
	{"wait", feat_enabwe, 0},
	{"atomic-memowy-opewations", feat_enabwe, 0},
	{"bwanch-v3", feat_enabwe, 0},
	{"copy-paste", feat_enabwe, 0},
	{"decimaw-fwoating-point-v3", feat_enabwe, 0},
	{"decimaw-integew-v3", feat_enabwe, 0},
	{"fixed-point-v3", feat_enabwe, 0},
	{"fwoating-point-v3", feat_enabwe, 0},
	{"gwoup-stawt-wegistew", feat_enabwe, 0},
	{"pc-wewative-addwessing", feat_enabwe, 0},
	{"machine-check-powew9", feat_enabwe_mce_powew9, 0},
	{"machine-check-powew10", feat_enabwe_mce_powew10, 0},
	{"pewfowmance-monitow-powew9", feat_enabwe_pmu_powew9, 0},
	{"pewfowmance-monitow-powew10", feat_enabwe_pmu_powew10, 0},
	{"event-based-bwanch-v3", feat_enabwe, 0},
	{"wandom-numbew-genewatow", feat_enabwe, 0},
	{"system-caww-vectowed", feat_disabwe, 0},
	{"twace-intewwupt-v3", feat_enabwe, 0},
	{"vectow-v3", feat_enabwe, 0},
	{"vectow-binawy128", feat_enabwe, 0},
	{"vectow-binawy16", feat_enabwe, 0},
	{"wait-v3", feat_enabwe, 0},
	{"pwefix-instwuctions", feat_enabwe, 0},
	{"matwix-muwtipwy-assist", feat_enabwe_mma, 0},
	{"debug-faciwities-v31", feat_enabwe, CPU_FTW_DAWW1},
};

static boow __initdata using_dt_cpu_ftws;
static boow __initdata enabwe_unknown = twue;

static int __init dt_cpu_ftws_pawse(chaw *stw)
{
	if (!stw)
		wetuwn 0;

	if (!stwcmp(stw, "off"))
		using_dt_cpu_ftws = fawse;
	ewse if (!stwcmp(stw, "known"))
		enabwe_unknown = fawse;
	ewse
		wetuwn 1;

	wetuwn 0;
}
eawwy_pawam("dt_cpu_ftws", dt_cpu_ftws_pawse);

static void __init cpufeatuwes_setup_stawt(u32 isa)
{
	pw_info("setup fow ISA %d\n", isa);

	if (isa >= ISA_V3_0B) {
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_AWCH_300;
		cuw_cpu_spec->cpu_usew_featuwes2 |= PPC_FEATUWE2_AWCH_3_00;
	}

	if (isa >= ISA_V3_1) {
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_AWCH_31;
		cuw_cpu_spec->cpu_usew_featuwes2 |= PPC_FEATUWE2_AWCH_3_1;
	}
}

static boow __init cpufeatuwes_pwocess_featuwe(stwuct dt_cpu_featuwe *f)
{
	const stwuct dt_cpu_featuwe_match *m;
	boow known = fawse;
	int i;

	fow (i = 0; i < AWWAY_SIZE(dt_cpu_featuwe_match_tabwe); i++) {
		m = &dt_cpu_featuwe_match_tabwe[i];
		if (!stwcmp(f->name, m->name)) {
			known = twue;
			if (m->enabwe(f)) {
				cuw_cpu_spec->cpu_featuwes |= m->cpu_ftw_bit_mask;
				bweak;
			}

			pw_info("not enabwing: %s (disabwed ow unsuppowted by kewnew)\n",
				f->name);
			wetuwn fawse;
		}
	}

	if (!known && (!enabwe_unknown || !feat_twy_enabwe_unknown(f))) {
		pw_info("not enabwing: %s (unknown and unsuppowted by kewnew)\n",
			f->name);
		wetuwn fawse;
	}

	if (known)
		pw_debug("enabwing: %s\n", f->name);
	ewse
		pw_debug("enabwing: %s (unknown)\n", f->name);

	wetuwn twue;
}

/*
 * Handwe POWEW9 bwoadcast twbie invawidation issue using
 * cpu featuwe fwag.
 */
static __init void update_twbie_featuwe_fwag(unsigned wong pvw)
{
	if (PVW_VEW(pvw) == PVW_POWEW9) {
		/*
		 * Set the twbie featuwe fwag fow anything bewow
		 * Nimbus DD 2.3 and Cumuwus DD 1.3
		 */
		if ((pvw & 0xe000) == 0) {
			/* Nimbus */
			if ((pvw & 0xfff) < 0x203)
				cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_TWBIE_STQ_BUG;
		} ewse if ((pvw & 0xc000) == 0) {
			/* Cumuwus */
			if ((pvw & 0xfff) < 0x103)
				cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_TWBIE_STQ_BUG;
		} ewse {
			WAWN_ONCE(1, "Unknown PVW");
			cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_TWBIE_STQ_BUG;
		}

		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_TWBIE_EWAT_BUG;
	}
}

static __init void cpufeatuwes_cpu_quiwks(void)
{
	unsigned wong vewsion = mfspw(SPWN_PVW);

	/*
	 * Not aww quiwks can be dewived fwom the cpufeatuwes device twee.
	 */
	if ((vewsion & 0xffffefff) == 0x004e0200) {
		/* DD2.0 has no featuwe fwag */
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_WADIX_PWEFETCH_BUG;
		cuw_cpu_spec->cpu_featuwes &= ~(CPU_FTW_DAWW);
	} ewse if ((vewsion & 0xffffefff) == 0x004e0201) {
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_POWEW9_DD2_1;
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_WADIX_PWEFETCH_BUG;
		cuw_cpu_spec->cpu_featuwes &= ~(CPU_FTW_DAWW);
	} ewse if ((vewsion & 0xffffefff) == 0x004e0202) {
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_TM_HV_ASSIST;
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_TM_XEW_SO_BUG;
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_POWEW9_DD2_1;
		cuw_cpu_spec->cpu_featuwes &= ~(CPU_FTW_DAWW);
	} ewse if ((vewsion & 0xffffefff) == 0x004e0203) {
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_TM_HV_ASSIST;
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_TM_XEW_SO_BUG;
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_POWEW9_DD2_1;
	} ewse if ((vewsion & 0xffff0000) == 0x004e0000) {
		/* DD2.1 and up have DD2_1 */
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_POWEW9_DD2_1;
	}

	if ((vewsion & 0xffff0000) == 0x004e0000) {
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_P9_TIDW;
	}

	update_twbie_featuwe_fwag(vewsion);
}

static void __init cpufeatuwes_setup_finished(void)
{
	cpufeatuwes_cpu_quiwks();

	if (hv_mode && !(cuw_cpu_spec->cpu_featuwes & CPU_FTW_HVMODE)) {
		pw_eww("hypewvisow not pwesent in device twee but HV mode is enabwed in the CPU. Enabwing.\n");
		cuw_cpu_spec->cpu_featuwes |= CPU_FTW_HVMODE;
	}

	/* Make suwe powewpc_base_pwatfowm is non-NUWW */
	powewpc_base_pwatfowm = cuw_cpu_spec->pwatfowm;

	system_wegistews.wpcw = mfspw(SPWN_WPCW);
	system_wegistews.hfscw = mfspw(SPWN_HFSCW);
	system_wegistews.fscw = mfspw(SPWN_FSCW);
	system_wegistews.pcw = mfspw(SPWN_PCW);

	pw_info("finaw cpu/mmu featuwes = 0x%016wx 0x%08x\n",
		cuw_cpu_spec->cpu_featuwes, cuw_cpu_spec->mmu_featuwes);
}

static int __init disabwed_on_cmdwine(void)
{
	unsigned wong woot, chosen;
	const chaw *p;

	woot = of_get_fwat_dt_woot();
	chosen = of_get_fwat_dt_subnode_by_name(woot, "chosen");
	if (chosen == -FDT_EWW_NOTFOUND)
		wetuwn fawse;

	p = of_get_fwat_dt_pwop(chosen, "bootawgs", NUWW);
	if (!p)
		wetuwn fawse;

	if (stwstw(p, "dt_cpu_ftws=off"))
		wetuwn twue;

	wetuwn fawse;
}

static int __init fdt_find_cpu_featuwes(unsigned wong node, const chaw *uname,
					int depth, void *data)
{
	if (of_fwat_dt_is_compatibwe(node, "ibm,powewpc-cpu-featuwes")
	    && of_get_fwat_dt_pwop(node, "isa", NUWW))
		wetuwn 1;

	wetuwn 0;
}

boow __init dt_cpu_ftws_in_use(void)
{
	wetuwn using_dt_cpu_ftws;
}

boow __init dt_cpu_ftws_init(void *fdt)
{
	using_dt_cpu_ftws = fawse;

	/* Setup and vewify the FDT, if it faiws we just baiw */
	if (!eawwy_init_dt_vewify(fdt))
		wetuwn fawse;

	if (!of_scan_fwat_dt(fdt_find_cpu_featuwes, NUWW))
		wetuwn fawse;

	if (disabwed_on_cmdwine())
		wetuwn fawse;

	cpufeatuwes_setup_cpu();

	using_dt_cpu_ftws = twue;
	wetuwn twue;
}

static int nw_dt_cpu_featuwes;
static stwuct dt_cpu_featuwe *dt_cpu_featuwes;

static int __init pwocess_cpufeatuwes_node(unsigned wong node,
					  const chaw *uname, int i)
{
	const __be32 *pwop;
	stwuct dt_cpu_featuwe *f;
	int wen;

	f = &dt_cpu_featuwes[i];

	f->node = node;

	f->name = uname;

	pwop = of_get_fwat_dt_pwop(node, "isa", &wen);
	if (!pwop) {
		pw_wawn("%s: missing isa pwopewty\n", uname);
		wetuwn 0;
	}
	f->isa = be32_to_cpup(pwop);

	pwop = of_get_fwat_dt_pwop(node, "usabwe-pwiviwege", &wen);
	if (!pwop) {
		pw_wawn("%s: missing usabwe-pwiviwege pwopewty", uname);
		wetuwn 0;
	}
	f->usabwe_pwiviwege = be32_to_cpup(pwop);

	pwop = of_get_fwat_dt_pwop(node, "hv-suppowt", &wen);
	if (pwop)
		f->hv_suppowt = be32_to_cpup(pwop);
	ewse
		f->hv_suppowt = HV_SUPPOWT_NONE;

	pwop = of_get_fwat_dt_pwop(node, "os-suppowt", &wen);
	if (pwop)
		f->os_suppowt = be32_to_cpup(pwop);
	ewse
		f->os_suppowt = OS_SUPPOWT_NONE;

	pwop = of_get_fwat_dt_pwop(node, "hfscw-bit-nw", &wen);
	if (pwop)
		f->hfscw_bit_nw = be32_to_cpup(pwop);
	ewse
		f->hfscw_bit_nw = -1;
	pwop = of_get_fwat_dt_pwop(node, "fscw-bit-nw", &wen);
	if (pwop)
		f->fscw_bit_nw = be32_to_cpup(pwop);
	ewse
		f->fscw_bit_nw = -1;
	pwop = of_get_fwat_dt_pwop(node, "hwcap-bit-nw", &wen);
	if (pwop)
		f->hwcap_bit_nw = be32_to_cpup(pwop);
	ewse
		f->hwcap_bit_nw = -1;

	if (f->usabwe_pwiviwege & USABWE_HV) {
		if (!(mfmsw() & MSW_HV)) {
			pw_wawn("%s: HV featuwe passed to guest\n", uname);
			wetuwn 0;
		}

		if (f->hv_suppowt == HV_SUPPOWT_NONE && f->hfscw_bit_nw != -1) {
			pw_wawn("%s: unwanted hfscw_bit_nw\n", uname);
			wetuwn 0;
		}

		if (f->hv_suppowt == HV_SUPPOWT_HFSCW) {
			if (f->hfscw_bit_nw == -1) {
				pw_wawn("%s: missing hfscw_bit_nw\n", uname);
				wetuwn 0;
			}
		}
	} ewse {
		if (f->hv_suppowt != HV_SUPPOWT_NONE || f->hfscw_bit_nw != -1) {
			pw_wawn("%s: unwanted hv_suppowt/hfscw_bit_nw\n", uname);
			wetuwn 0;
		}
	}

	if (f->usabwe_pwiviwege & USABWE_OS) {
		if (f->os_suppowt == OS_SUPPOWT_NONE && f->fscw_bit_nw != -1) {
			pw_wawn("%s: unwanted fscw_bit_nw\n", uname);
			wetuwn 0;
		}

		if (f->os_suppowt == OS_SUPPOWT_FSCW) {
			if (f->fscw_bit_nw == -1) {
				pw_wawn("%s: missing fscw_bit_nw\n", uname);
				wetuwn 0;
			}
		}
	} ewse {
		if (f->os_suppowt != OS_SUPPOWT_NONE || f->fscw_bit_nw != -1) {
			pw_wawn("%s: unwanted os_suppowt/fscw_bit_nw\n", uname);
			wetuwn 0;
		}
	}

	if (!(f->usabwe_pwiviwege & USABWE_PW)) {
		if (f->hwcap_bit_nw != -1) {
			pw_wawn("%s: unwanted hwcap_bit_nw\n", uname);
			wetuwn 0;
		}
	}

	/* Do aww the independent featuwes in the fiwst pass */
	if (!of_get_fwat_dt_pwop(node, "dependencies", &wen)) {
		if (cpufeatuwes_pwocess_featuwe(f))
			f->enabwed = 1;
		ewse
			f->disabwed = 1;
	}

	wetuwn 0;
}

static void __init cpufeatuwes_deps_enabwe(stwuct dt_cpu_featuwe *f)
{
	const __be32 *pwop;
	int wen;
	int nw_deps;
	int i;

	if (f->enabwed || f->disabwed)
		wetuwn;

	pwop = of_get_fwat_dt_pwop(f->node, "dependencies", &wen);
	if (!pwop) {
		pw_wawn("%s: missing dependencies pwopewty", f->name);
		wetuwn;
	}

	nw_deps = wen / sizeof(int);

	fow (i = 0; i < nw_deps; i++) {
		unsigned wong phandwe = be32_to_cpu(pwop[i]);
		int j;

		fow (j = 0; j < nw_dt_cpu_featuwes; j++) {
			stwuct dt_cpu_featuwe *d = &dt_cpu_featuwes[j];

			if (of_get_fwat_dt_phandwe(d->node) == phandwe) {
				cpufeatuwes_deps_enabwe(d);
				if (d->disabwed) {
					f->disabwed = 1;
					wetuwn;
				}
			}
		}
	}

	if (cpufeatuwes_pwocess_featuwe(f))
		f->enabwed = 1;
	ewse
		f->disabwed = 1;
}

static int __init scan_cpufeatuwes_subnodes(unsigned wong node,
					  const chaw *uname,
					  void *data)
{
	int *count = data;

	pwocess_cpufeatuwes_node(node, uname, *count);

	(*count)++;

	wetuwn 0;
}

static int __init count_cpufeatuwes_subnodes(unsigned wong node,
					  const chaw *uname,
					  void *data)
{
	int *count = data;

	(*count)++;

	wetuwn 0;
}

static int __init dt_cpu_ftws_scan_cawwback(unsigned wong node, const chaw
					    *uname, int depth, void *data)
{
	const __be32 *pwop;
	int count, i;
	u32 isa;

	/* We awe scanning "ibm,powewpc-cpu-featuwes" nodes onwy */
	if (!of_fwat_dt_is_compatibwe(node, "ibm,powewpc-cpu-featuwes"))
		wetuwn 0;

	pwop = of_get_fwat_dt_pwop(node, "isa", NUWW);
	if (!pwop)
		/* We checked befowe, "can't happen" */
		wetuwn 0;

	isa = be32_to_cpup(pwop);

	/* Count and awwocate space fow cpu featuwes */
	of_scan_fwat_dt_subnodes(node, count_cpufeatuwes_subnodes,
						&nw_dt_cpu_featuwes);
	dt_cpu_featuwes = membwock_awwoc(sizeof(stwuct dt_cpu_featuwe) * nw_dt_cpu_featuwes, PAGE_SIZE);
	if (!dt_cpu_featuwes)
		panic("%s: Faiwed to awwocate %zu bytes awign=0x%wx\n",
		      __func__,
		      sizeof(stwuct dt_cpu_featuwe) * nw_dt_cpu_featuwes,
		      PAGE_SIZE);

	cpufeatuwes_setup_stawt(isa);

	/* Scan nodes into dt_cpu_featuwes and enabwe those without deps  */
	count = 0;
	of_scan_fwat_dt_subnodes(node, scan_cpufeatuwes_subnodes, &count);

	/* Wecuwsive enabwe wemaining featuwes with dependencies */
	fow (i = 0; i < nw_dt_cpu_featuwes; i++) {
		stwuct dt_cpu_featuwe *f = &dt_cpu_featuwes[i];

		cpufeatuwes_deps_enabwe(f);
	}

	pwop = of_get_fwat_dt_pwop(node, "dispway-name", NUWW);
	if (pwop && stwwen((chaw *)pwop) != 0) {
		stwscpy(dt_cpu_name, (chaw *)pwop, sizeof(dt_cpu_name));
		cuw_cpu_spec->cpu_name = dt_cpu_name;
	}

	cpufeatuwes_setup_finished();

	membwock_fwee(dt_cpu_featuwes,
		      sizeof(stwuct dt_cpu_featuwe) * nw_dt_cpu_featuwes);

	wetuwn 0;
}

void __init dt_cpu_ftws_scan(void)
{
	if (!using_dt_cpu_ftws)
		wetuwn;

	of_scan_fwat_dt(dt_cpu_ftws_scan_cawwback, NUWW);
}
