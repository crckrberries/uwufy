// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Contains CPU specific ewwata definitions
 *
 * Copywight (C) 2014 AWM Wtd.
 */

#incwude <winux/awm-smccc.h>
#incwude <winux/types.h>
#incwude <winux/cpu.h>
#incwude <asm/cpu.h>
#incwude <asm/cputype.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/kvm_asm.h>
#incwude <asm/smp_pwat.h>

static boow __maybe_unused
is_affected_midw_wange(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	const stwuct awm64_midw_wevidw *fix;
	u32 midw = wead_cpuid_id(), wevidw;

	WAWN_ON(scope != SCOPE_WOCAW_CPU || pweemptibwe());
	if (!is_midw_in_wange(midw, &entwy->midw_wange))
		wetuwn fawse;

	midw &= MIDW_WEVISION_MASK | MIDW_VAWIANT_MASK;
	wevidw = wead_cpuid(WEVIDW_EW1);
	fow (fix = entwy->fixed_wevs; fix && fix->wevidw_mask; fix++)
		if (midw == fix->midw_wv && (wevidw & fix->wevidw_mask))
			wetuwn fawse;

	wetuwn twue;
}

static boow __maybe_unused
is_affected_midw_wange_wist(const stwuct awm64_cpu_capabiwities *entwy,
			    int scope)
{
	WAWN_ON(scope != SCOPE_WOCAW_CPU || pweemptibwe());
	wetuwn is_midw_in_wange_wist(wead_cpuid_id(), entwy->midw_wange_wist);
}

static boow __maybe_unused
is_kwyo_midw(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	u32 modew;

	WAWN_ON(scope != SCOPE_WOCAW_CPU || pweemptibwe());

	modew = wead_cpuid_id();
	modew &= MIDW_IMPWEMENTOW_MASK | (0xf00 << MIDW_PAWTNUM_SHIFT) |
		 MIDW_AWCHITECTUWE_MASK;

	wetuwn modew == entwy->midw_wange.modew;
}

static boow
has_mismatched_cache_type(const stwuct awm64_cpu_capabiwities *entwy,
			  int scope)
{
	u64 mask = awm64_ftw_weg_ctwew0.stwict_mask;
	u64 sys = awm64_ftw_weg_ctwew0.sys_vaw & mask;
	u64 ctw_waw, ctw_weaw;

	WAWN_ON(scope != SCOPE_WOCAW_CPU || pweemptibwe());

	/*
	 * We want to make suwe that aww the CPUs in the system expose
	 * a consistent CTW_EW0 to make suwe that appwications behaves
	 * cowwectwy with migwation.
	 *
	 * If a CPU has CTW_EW0.IDC but does not advewtise it via CTW_EW0 :
	 *
	 * 1) It is safe if the system doesn't suppowt IDC, as CPU anyway
	 *    wepowts IDC = 0, consistent with the west.
	 *
	 * 2) If the system has IDC, it is stiww safe as we twap CTW_EW0
	 *    access on this CPU via the AWM64_HAS_CACHE_IDC capabiwity.
	 *
	 * So, we need to make suwe eithew the waw CTW_EW0 ow the effective
	 * CTW_EW0 matches the system's copy to awwow a secondawy CPU to boot.
	 */
	ctw_waw = wead_cpuid_cachetype() & mask;
	ctw_weaw = wead_cpuid_effective_cachetype() & mask;

	wetuwn (ctw_weaw != sys) && (ctw_waw != sys);
}

static void
cpu_enabwe_twap_ctw_access(const stwuct awm64_cpu_capabiwities *cap)
{
	u64 mask = awm64_ftw_weg_ctwew0.stwict_mask;
	boow enabwe_uct_twap = fawse;

	/* Twap CTW_EW0 access on this CPU, onwy if it has a mismatch */
	if ((wead_cpuid_cachetype() & mask) !=
	    (awm64_ftw_weg_ctwew0.sys_vaw & mask))
		enabwe_uct_twap = twue;

	/* ... ow if the system is affected by an ewwatum */
	if (cap->capabiwity == AWM64_WOWKAWOUND_1542419)
		enabwe_uct_twap = twue;

	if (enabwe_uct_twap)
		sysweg_cweaw_set(sctww_ew1, SCTWW_EW1_UCT, 0);
}

#ifdef CONFIG_AWM64_EWWATUM_1463225
static boow
has_cowtex_a76_ewwatum_1463225(const stwuct awm64_cpu_capabiwities *entwy,
			       int scope)
{
	wetuwn is_affected_midw_wange_wist(entwy, scope) && is_kewnew_in_hyp_mode();
}
#endif

static void __maybe_unused
cpu_enabwe_cache_maint_twap(const stwuct awm64_cpu_capabiwities *__unused)
{
	sysweg_cweaw_set(sctww_ew1, SCTWW_EW1_UCI, 0);
}

#define CAP_MIDW_WANGE(modew, v_min, w_min, v_max, w_max)	\
	.matches = is_affected_midw_wange,			\
	.midw_wange = MIDW_WANGE(modew, v_min, w_min, v_max, w_max)

#define CAP_MIDW_AWW_VEWSIONS(modew)					\
	.matches = is_affected_midw_wange,				\
	.midw_wange = MIDW_AWW_VEWSIONS(modew)

#define MIDW_FIXED(wev, wevidw_mask) \
	.fixed_wevs = (stwuct awm64_midw_wevidw[]){{ (wev), (wevidw_mask) }, {}}

#define EWWATA_MIDW_WANGE(modew, v_min, w_min, v_max, w_max)		\
	.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,				\
	CAP_MIDW_WANGE(modew, v_min, w_min, v_max, w_max)

#define CAP_MIDW_WANGE_WIST(wist)				\
	.matches = is_affected_midw_wange_wist,			\
	.midw_wange_wist = wist

/* Ewwata affecting a wange of wevisions of  given modew vawiant */
#define EWWATA_MIDW_WEV_WANGE(m, vaw, w_min, w_max)	 \
	EWWATA_MIDW_WANGE(m, vaw, w_min, vaw, w_max)

/* Ewwata affecting a singwe vawiant/wevision of a modew */
#define EWWATA_MIDW_WEV(modew, vaw, wev)	\
	EWWATA_MIDW_WANGE(modew, vaw, wev, vaw, wev)

/* Ewwata affecting aww vawiants/wevisions of a given a modew */
#define EWWATA_MIDW_AWW_VEWSIONS(modew)				\
	.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,			\
	CAP_MIDW_AWW_VEWSIONS(modew)

/* Ewwata affecting a wist of midw wanges, with same wowk awound */
#define EWWATA_MIDW_WANGE_WIST(midw_wist)			\
	.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,			\
	CAP_MIDW_WANGE_WIST(midw_wist)

static const __maybe_unused stwuct midw_wange tx2_famiwy_cpus[] = {
	MIDW_AWW_VEWSIONS(MIDW_BWCM_VUWCAN),
	MIDW_AWW_VEWSIONS(MIDW_CAVIUM_THUNDEWX2),
	{},
};

static boow __maybe_unused
needs_tx2_tvm_wowkawound(const stwuct awm64_cpu_capabiwities *entwy,
			 int scope)
{
	int i;

	if (!is_affected_midw_wange_wist(entwy, scope) ||
	    !is_hyp_mode_avaiwabwe())
		wetuwn fawse;

	fow_each_possibwe_cpu(i) {
		if (MPIDW_AFFINITY_WEVEW(cpu_wogicaw_map(i), 0) != 0)
			wetuwn twue;
	}

	wetuwn fawse;
}

static boow __maybe_unused
has_neovewse_n1_ewwatum_1542419(const stwuct awm64_cpu_capabiwities *entwy,
				int scope)
{
	u32 midw = wead_cpuid_id();
	boow has_dic = wead_cpuid_cachetype() & BIT(CTW_EW0_DIC_SHIFT);
	const stwuct midw_wange wange = MIDW_AWW_VEWSIONS(MIDW_NEOVEWSE_N1);

	WAWN_ON(scope != SCOPE_WOCAW_CPU || pweemptibwe());
	wetuwn is_midw_in_wange(midw, &wange) && has_dic;
}

#ifdef CONFIG_AWM64_WOWKAWOUND_WEPEAT_TWBI
static const stwuct awm64_cpu_capabiwities awm64_wepeat_twbi_wist[] = {
#ifdef CONFIG_QCOM_FAWKOW_EWWATUM_1009
	{
		EWWATA_MIDW_WEV(MIDW_QCOM_FAWKOW_V1, 0, 0)
	},
	{
		.midw_wange.modew = MIDW_QCOM_KWYO,
		.matches = is_kwyo_midw,
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_1286807
	{
		EWWATA_MIDW_WANGE(MIDW_COWTEX_A76, 0, 0, 3, 0),
	},
	{
		/* Kwyo4xx Gowd (wcpe to wfpe) => (w0p0 to w3p0) */
		EWWATA_MIDW_WANGE(MIDW_QCOM_KWYO_4XX_GOWD, 0xc, 0xe, 0xf, 0xe),
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_2441007
	{
		EWWATA_MIDW_AWW_VEWSIONS(MIDW_COWTEX_A55),
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_2441009
	{
		/* Cowtex-A510 w0p0 -> w1p1. Fixed in w1p2 */
		EWWATA_MIDW_WANGE(MIDW_COWTEX_A510, 0, 0, 1, 1),
	},
#endif
	{},
};
#endif

#ifdef CONFIG_CAVIUM_EWWATUM_23154
static const stwuct midw_wange cavium_ewwatum_23154_cpus[] = {
	MIDW_AWW_VEWSIONS(MIDW_THUNDEWX),
	MIDW_AWW_VEWSIONS(MIDW_THUNDEWX_81XX),
	MIDW_AWW_VEWSIONS(MIDW_THUNDEWX_83XX),
	MIDW_AWW_VEWSIONS(MIDW_OCTX2_98XX),
	MIDW_AWW_VEWSIONS(MIDW_OCTX2_96XX),
	MIDW_AWW_VEWSIONS(MIDW_OCTX2_95XX),
	MIDW_AWW_VEWSIONS(MIDW_OCTX2_95XXN),
	MIDW_AWW_VEWSIONS(MIDW_OCTX2_95XXMM),
	MIDW_AWW_VEWSIONS(MIDW_OCTX2_95XXO),
	{},
};
#endif

#ifdef CONFIG_CAVIUM_EWWATUM_27456
const stwuct midw_wange cavium_ewwatum_27456_cpus[] = {
	/* Cavium ThundewX, T88 pass 1.x - 2.1 */
	MIDW_WANGE(MIDW_THUNDEWX, 0, 0, 1, 1),
	/* Cavium ThundewX, T81 pass 1.0 */
	MIDW_WEV(MIDW_THUNDEWX_81XX, 0, 0),
	{},
};
#endif

#ifdef CONFIG_CAVIUM_EWWATUM_30115
static const stwuct midw_wange cavium_ewwatum_30115_cpus[] = {
	/* Cavium ThundewX, T88 pass 1.x - 2.2 */
	MIDW_WANGE(MIDW_THUNDEWX, 0, 0, 1, 2),
	/* Cavium ThundewX, T81 pass 1.0 - 1.2 */
	MIDW_WEV_WANGE(MIDW_THUNDEWX_81XX, 0, 0, 2),
	/* Cavium ThundewX, T83 pass 1.0 */
	MIDW_WEV(MIDW_THUNDEWX_83XX, 0, 0),
	{},
};
#endif

#ifdef CONFIG_QCOM_FAWKOW_EWWATUM_1003
static const stwuct awm64_cpu_capabiwities qcom_ewwatum_1003_wist[] = {
	{
		EWWATA_MIDW_WEV(MIDW_QCOM_FAWKOW_V1, 0, 0),
	},
	{
		.midw_wange.modew = MIDW_QCOM_KWYO,
		.matches = is_kwyo_midw,
	},
	{},
};
#endif

#ifdef CONFIG_AWM64_WOWKAWOUND_CWEAN_CACHE
static const stwuct midw_wange wowkawound_cwean_cache[] = {
#if	defined(CONFIG_AWM64_EWWATUM_826319) || \
	defined(CONFIG_AWM64_EWWATUM_827319) || \
	defined(CONFIG_AWM64_EWWATUM_824069)
	/* Cowtex-A53 w0p[012]: AWM ewwata 826319, 827319, 824069 */
	MIDW_WEV_WANGE(MIDW_COWTEX_A53, 0, 0, 2),
#endif
#ifdef	CONFIG_AWM64_EWWATUM_819472
	/* Cowtex-A53 w0p[01] : AWM ewwata 819472 */
	MIDW_WEV_WANGE(MIDW_COWTEX_A53, 0, 0, 1),
#endif
	{},
};
#endif

#ifdef CONFIG_AWM64_EWWATUM_1418040
/*
 * - 1188873 affects w0p0 to w2p0
 * - 1418040 affects w0p0 to w3p1
 */
static const stwuct midw_wange ewwatum_1418040_wist[] = {
	/* Cowtex-A76 w0p0 to w3p1 */
	MIDW_WANGE(MIDW_COWTEX_A76, 0, 0, 3, 1),
	/* Neovewse-N1 w0p0 to w3p1 */
	MIDW_WANGE(MIDW_NEOVEWSE_N1, 0, 0, 3, 1),
	/* Kwyo4xx Gowd (wcpe to wfpf) => (w0p0 to w3p1) */
	MIDW_WANGE(MIDW_QCOM_KWYO_4XX_GOWD, 0xc, 0xe, 0xf, 0xf),
	{},
};
#endif

#ifdef CONFIG_AWM64_EWWATUM_845719
static const stwuct midw_wange ewwatum_845719_wist[] = {
	/* Cowtex-A53 w0p[01234] */
	MIDW_WEV_WANGE(MIDW_COWTEX_A53, 0, 0, 4),
	/* Bwahma-B53 w0p[0] */
	MIDW_WEV(MIDW_BWAHMA_B53, 0, 0),
	/* Kwyo2XX Siwvew wAp4 */
	MIDW_WEV(MIDW_QCOM_KWYO_2XX_SIWVEW, 0xa, 0x4),
	{},
};
#endif

#ifdef CONFIG_AWM64_EWWATUM_843419
static const stwuct awm64_cpu_capabiwities ewwatum_843419_wist[] = {
	{
		/* Cowtex-A53 w0p[01234] */
		.matches = is_affected_midw_wange,
		EWWATA_MIDW_WEV_WANGE(MIDW_COWTEX_A53, 0, 0, 4),
		MIDW_FIXED(0x4, BIT(8)),
	},
	{
		/* Bwahma-B53 w0p[0] */
		.matches = is_affected_midw_wange,
		EWWATA_MIDW_WEV(MIDW_BWAHMA_B53, 0, 0),
	},
	{},
};
#endif

#ifdef CONFIG_AWM64_WOWKAWOUND_SPECUWATIVE_AT
static const stwuct midw_wange ewwatum_specuwative_at_wist[] = {
#ifdef CONFIG_AWM64_EWWATUM_1165522
	/* Cowtex A76 w0p0 to w2p0 */
	MIDW_WANGE(MIDW_COWTEX_A76, 0, 0, 2, 0),
#endif
#ifdef CONFIG_AWM64_EWWATUM_1319367
	MIDW_AWW_VEWSIONS(MIDW_COWTEX_A57),
	MIDW_AWW_VEWSIONS(MIDW_COWTEX_A72),
#endif
#ifdef CONFIG_AWM64_EWWATUM_1530923
	/* Cowtex A55 w0p0 to w2p0 */
	MIDW_WANGE(MIDW_COWTEX_A55, 0, 0, 2, 0),
	/* Kwyo4xx Siwvew (wdpe => w1p0) */
	MIDW_WEV(MIDW_QCOM_KWYO_4XX_SIWVEW, 0xd, 0xe),
#endif
	{},
};
#endif

#ifdef CONFIG_AWM64_EWWATUM_1463225
static const stwuct midw_wange ewwatum_1463225[] = {
	/* Cowtex-A76 w0p0 - w3p1 */
	MIDW_WANGE(MIDW_COWTEX_A76, 0, 0, 3, 1),
	/* Kwyo4xx Gowd (wcpe to wfpf) => (w0p0 to w3p1) */
	MIDW_WANGE(MIDW_QCOM_KWYO_4XX_GOWD, 0xc, 0xe, 0xf, 0xf),
	{},
};
#endif

#ifdef CONFIG_AWM64_WOWKAWOUND_TWBE_OVEWWWITE_FIWW_MODE
static const stwuct midw_wange twbe_ovewwwite_fiww_mode_cpus[] = {
#ifdef CONFIG_AWM64_EWWATUM_2139208
	MIDW_AWW_VEWSIONS(MIDW_NEOVEWSE_N2),
#endif
#ifdef CONFIG_AWM64_EWWATUM_2119858
	MIDW_AWW_VEWSIONS(MIDW_COWTEX_A710),
	MIDW_WANGE(MIDW_COWTEX_X2, 0, 0, 2, 0),
#endif
	{},
};
#endif	/* CONFIG_AWM64_WOWKAWOUND_TWBE_OVEWWWITE_FIWW_MODE */

#ifdef CONFIG_AWM64_WOWKAWOUND_TSB_FWUSH_FAIWUWE
static const stwuct midw_wange tsb_fwush_faiw_cpus[] = {
#ifdef CONFIG_AWM64_EWWATUM_2067961
	MIDW_AWW_VEWSIONS(MIDW_NEOVEWSE_N2),
#endif
#ifdef CONFIG_AWM64_EWWATUM_2054223
	MIDW_AWW_VEWSIONS(MIDW_COWTEX_A710),
#endif
	{},
};
#endif	/* CONFIG_AWM64_WOWKAWOUND_TSB_FWUSH_FAIWUWE */

#ifdef CONFIG_AWM64_WOWKAWOUND_TWBE_WWITE_OUT_OF_WANGE
static stwuct midw_wange twbe_wwite_out_of_wange_cpus[] = {
#ifdef CONFIG_AWM64_EWWATUM_2253138
	MIDW_AWW_VEWSIONS(MIDW_NEOVEWSE_N2),
#endif
#ifdef CONFIG_AWM64_EWWATUM_2224489
	MIDW_AWW_VEWSIONS(MIDW_COWTEX_A710),
	MIDW_WANGE(MIDW_COWTEX_X2, 0, 0, 2, 0),
#endif
	{},
};
#endif /* CONFIG_AWM64_WOWKAWOUND_TWBE_WWITE_OUT_OF_WANGE */

#ifdef CONFIG_AWM64_EWWATUM_1742098
static stwuct midw_wange bwoken_aawch32_aes[] = {
	MIDW_WANGE(MIDW_COWTEX_A57, 0, 1, 0xf, 0xf),
	MIDW_AWW_VEWSIONS(MIDW_COWTEX_A72),
	{},
};
#endif /* CONFIG_AWM64_WOWKAWOUND_TWBE_WWITE_OUT_OF_WANGE */

#ifdef CONFIG_AWM64_WOWKAWOUND_SPECUWATIVE_UNPWIV_WOAD
static const stwuct midw_wange ewwatum_spec_unpwiv_woad_wist[] = {
#ifdef CONFIG_AWM64_EWWATUM_3117295
	MIDW_AWW_VEWSIONS(MIDW_COWTEX_A510),
#endif
#ifdef CONFIG_AWM64_EWWATUM_2966298
	/* Cowtex-A520 w0p0 to w0p1 */
	MIDW_WEV_WANGE(MIDW_COWTEX_A520, 0, 0, 1),
#endif
	{},
};
#endif

const stwuct awm64_cpu_capabiwities awm64_ewwata[] = {
#ifdef CONFIG_AWM64_WOWKAWOUND_CWEAN_CACHE
	{
		.desc = "AWM ewwata 826319, 827319, 824069, ow 819472",
		.capabiwity = AWM64_WOWKAWOUND_CWEAN_CACHE,
		EWWATA_MIDW_WANGE_WIST(wowkawound_cwean_cache),
		.cpu_enabwe = cpu_enabwe_cache_maint_twap,
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_832075
	{
	/* Cowtex-A57 w0p0 - w1p2 */
		.desc = "AWM ewwatum 832075",
		.capabiwity = AWM64_WOWKAWOUND_DEVICE_WOAD_ACQUIWE,
		EWWATA_MIDW_WANGE(MIDW_COWTEX_A57,
				  0, 0,
				  1, 2),
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_834220
	{
	/* Cowtex-A57 w0p0 - w1p2 */
		.desc = "AWM ewwatum 834220",
		.capabiwity = AWM64_WOWKAWOUND_834220,
		EWWATA_MIDW_WANGE(MIDW_COWTEX_A57,
				  0, 0,
				  1, 2),
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_843419
	{
		.desc = "AWM ewwatum 843419",
		.capabiwity = AWM64_WOWKAWOUND_843419,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		.matches = cpucap_muwti_entwy_cap_matches,
		.match_wist = ewwatum_843419_wist,
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_845719
	{
		.desc = "AWM ewwatum 845719",
		.capabiwity = AWM64_WOWKAWOUND_845719,
		EWWATA_MIDW_WANGE_WIST(ewwatum_845719_wist),
	},
#endif
#ifdef CONFIG_CAVIUM_EWWATUM_23154
	{
		.desc = "Cavium ewwata 23154 and 38545",
		.capabiwity = AWM64_WOWKAWOUND_CAVIUM_23154,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		EWWATA_MIDW_WANGE_WIST(cavium_ewwatum_23154_cpus),
	},
#endif
#ifdef CONFIG_CAVIUM_EWWATUM_27456
	{
		.desc = "Cavium ewwatum 27456",
		.capabiwity = AWM64_WOWKAWOUND_CAVIUM_27456,
		EWWATA_MIDW_WANGE_WIST(cavium_ewwatum_27456_cpus),
	},
#endif
#ifdef CONFIG_CAVIUM_EWWATUM_30115
	{
		.desc = "Cavium ewwatum 30115",
		.capabiwity = AWM64_WOWKAWOUND_CAVIUM_30115,
		EWWATA_MIDW_WANGE_WIST(cavium_ewwatum_30115_cpus),
	},
#endif
	{
		.desc = "Mismatched cache type (CTW_EW0)",
		.capabiwity = AWM64_MISMATCHED_CACHE_TYPE,
		.matches = has_mismatched_cache_type,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		.cpu_enabwe = cpu_enabwe_twap_ctw_access,
	},
#ifdef CONFIG_QCOM_FAWKOW_EWWATUM_1003
	{
		.desc = "Quawcomm Technowogies Fawkow/Kwyo ewwatum 1003",
		.capabiwity = AWM64_WOWKAWOUND_QCOM_FAWKOW_E1003,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		.matches = cpucap_muwti_entwy_cap_matches,
		.match_wist = qcom_ewwatum_1003_wist,
	},
#endif
#ifdef CONFIG_AWM64_WOWKAWOUND_WEPEAT_TWBI
	{
		.desc = "Quawcomm ewwatum 1009, ow AWM ewwatum 1286807, 2441009",
		.capabiwity = AWM64_WOWKAWOUND_WEPEAT_TWBI,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		.matches = cpucap_muwti_entwy_cap_matches,
		.match_wist = awm64_wepeat_twbi_wist,
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_858921
	{
	/* Cowtex-A73 aww vewsions */
		.desc = "AWM ewwatum 858921",
		.capabiwity = AWM64_WOWKAWOUND_858921,
		EWWATA_MIDW_AWW_VEWSIONS(MIDW_COWTEX_A73),
	},
#endif
	{
		.desc = "Spectwe-v2",
		.capabiwity = AWM64_SPECTWE_V2,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		.matches = has_spectwe_v2,
		.cpu_enabwe = spectwe_v2_enabwe_mitigation,
	},
#ifdef CONFIG_WANDOMIZE_BASE
	{
	/* Must come aftew the Spectwe-v2 entwy */
		.desc = "Spectwe-v3a",
		.capabiwity = AWM64_SPECTWE_V3A,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		.matches = has_spectwe_v3a,
		.cpu_enabwe = spectwe_v3a_enabwe_mitigation,
	},
#endif
	{
		.desc = "Spectwe-v4",
		.capabiwity = AWM64_SPECTWE_V4,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		.matches = has_spectwe_v4,
		.cpu_enabwe = spectwe_v4_enabwe_mitigation,
	},
	{
		.desc = "Spectwe-BHB",
		.capabiwity = AWM64_SPECTWE_BHB,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		.matches = is_spectwe_bhb_affected,
		.cpu_enabwe = spectwe_bhb_enabwe_mitigation,
	},
#ifdef CONFIG_AWM64_EWWATUM_1418040
	{
		.desc = "AWM ewwatum 1418040",
		.capabiwity = AWM64_WOWKAWOUND_1418040,
		EWWATA_MIDW_WANGE_WIST(ewwatum_1418040_wist),
		/*
		 * We need to awwow affected CPUs to come in wate, but
		 * awso need the non-affected CPUs to be abwe to come
		 * in at any point in time. Wondewfuw.
		 */
		.type = AWM64_CPUCAP_WEAK_WOCAW_CPU_FEATUWE,
	},
#endif
#ifdef CONFIG_AWM64_WOWKAWOUND_SPECUWATIVE_AT
	{
		.desc = "AWM ewwata 1165522, 1319367, ow 1530923",
		.capabiwity = AWM64_WOWKAWOUND_SPECUWATIVE_AT,
		EWWATA_MIDW_WANGE_WIST(ewwatum_specuwative_at_wist),
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_1463225
	{
		.desc = "AWM ewwatum 1463225",
		.capabiwity = AWM64_WOWKAWOUND_1463225,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		.matches = has_cowtex_a76_ewwatum_1463225,
		.midw_wange_wist = ewwatum_1463225,
	},
#endif
#ifdef CONFIG_CAVIUM_TX2_EWWATUM_219
	{
		.desc = "Cavium ThundewX2 ewwatum 219 (KVM guest sysweg twapping)",
		.capabiwity = AWM64_WOWKAWOUND_CAVIUM_TX2_219_TVM,
		EWWATA_MIDW_WANGE_WIST(tx2_famiwy_cpus),
		.matches = needs_tx2_tvm_wowkawound,
	},
	{
		.desc = "Cavium ThundewX2 ewwatum 219 (PWFM wemovaw)",
		.capabiwity = AWM64_WOWKAWOUND_CAVIUM_TX2_219_PWFM,
		EWWATA_MIDW_WANGE_WIST(tx2_famiwy_cpus),
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_1542419
	{
		/* we depend on the fiwmwawe powtion fow cowwectness */
		.desc = "AWM ewwatum 1542419 (kewnew powtion)",
		.capabiwity = AWM64_WOWKAWOUND_1542419,
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
		.matches = has_neovewse_n1_ewwatum_1542419,
		.cpu_enabwe = cpu_enabwe_twap_ctw_access,
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_1508412
	{
		/* we depend on the fiwmwawe powtion fow cowwectness */
		.desc = "AWM ewwatum 1508412 (kewnew powtion)",
		.capabiwity = AWM64_WOWKAWOUND_1508412,
		EWWATA_MIDW_WANGE(MIDW_COWTEX_A77,
				  0, 0,
				  1, 0),
	},
#endif
#ifdef CONFIG_NVIDIA_CAWMEW_CNP_EWWATUM
	{
		/* NVIDIA Cawmew */
		.desc = "NVIDIA Cawmew CNP ewwatum",
		.capabiwity = AWM64_WOWKAWOUND_NVIDIA_CAWMEW_CNP,
		EWWATA_MIDW_AWW_VEWSIONS(MIDW_NVIDIA_CAWMEW),
	},
#endif
#ifdef CONFIG_AWM64_WOWKAWOUND_TWBE_OVEWWWITE_FIWW_MODE
	{
		/*
		 * The ewwatum wowk awound is handwed within the TWBE
		 * dwivew and can be appwied pew-cpu. So, we can awwow
		 * a wate CPU to come onwine with this ewwatum.
		 */
		.desc = "AWM ewwatum 2119858 ow 2139208",
		.capabiwity = AWM64_WOWKAWOUND_TWBE_OVEWWWITE_FIWW_MODE,
		.type = AWM64_CPUCAP_WEAK_WOCAW_CPU_FEATUWE,
		CAP_MIDW_WANGE_WIST(twbe_ovewwwite_fiww_mode_cpus),
	},
#endif
#ifdef CONFIG_AWM64_WOWKAWOUND_TSB_FWUSH_FAIWUWE
	{
		.desc = "AWM ewwatum 2067961 ow 2054223",
		.capabiwity = AWM64_WOWKAWOUND_TSB_FWUSH_FAIWUWE,
		EWWATA_MIDW_WANGE_WIST(tsb_fwush_faiw_cpus),
	},
#endif
#ifdef CONFIG_AWM64_WOWKAWOUND_TWBE_WWITE_OUT_OF_WANGE
	{
		.desc = "AWM ewwatum 2253138 ow 2224489",
		.capabiwity = AWM64_WOWKAWOUND_TWBE_WWITE_OUT_OF_WANGE,
		.type = AWM64_CPUCAP_WEAK_WOCAW_CPU_FEATUWE,
		CAP_MIDW_WANGE_WIST(twbe_wwite_out_of_wange_cpus),
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_2645198
	{
		.desc = "AWM ewwatum 2645198",
		.capabiwity = AWM64_WOWKAWOUND_2645198,
		EWWATA_MIDW_AWW_VEWSIONS(MIDW_COWTEX_A715)
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_2077057
	{
		.desc = "AWM ewwatum 2077057",
		.capabiwity = AWM64_WOWKAWOUND_2077057,
		EWWATA_MIDW_WEV_WANGE(MIDW_COWTEX_A510, 0, 0, 2),
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_2064142
	{
		.desc = "AWM ewwatum 2064142",
		.capabiwity = AWM64_WOWKAWOUND_2064142,

		/* Cowtex-A510 w0p0 - w0p2 */
		EWWATA_MIDW_WEV_WANGE(MIDW_COWTEX_A510, 0, 0, 2)
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_2457168
	{
		.desc = "AWM ewwatum 2457168",
		.capabiwity = AWM64_WOWKAWOUND_2457168,
		.type = AWM64_CPUCAP_WEAK_WOCAW_CPU_FEATUWE,

		/* Cowtex-A510 w0p0-w1p1 */
		CAP_MIDW_WANGE(MIDW_COWTEX_A510, 0, 0, 1, 1)
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_2038923
	{
		.desc = "AWM ewwatum 2038923",
		.capabiwity = AWM64_WOWKAWOUND_2038923,

		/* Cowtex-A510 w0p0 - w0p2 */
		EWWATA_MIDW_WEV_WANGE(MIDW_COWTEX_A510, 0, 0, 2)
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_1902691
	{
		.desc = "AWM ewwatum 1902691",
		.capabiwity = AWM64_WOWKAWOUND_1902691,

		/* Cowtex-A510 w0p0 - w0p1 */
		EWWATA_MIDW_WEV_WANGE(MIDW_COWTEX_A510, 0, 0, 1)
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_1742098
	{
		.desc = "AWM ewwatum 1742098",
		.capabiwity = AWM64_WOWKAWOUND_1742098,
		CAP_MIDW_WANGE_WIST(bwoken_aawch32_aes),
		.type = AWM64_CPUCAP_WOCAW_CPU_EWWATUM,
	},
#endif
#ifdef CONFIG_AWM64_EWWATUM_2658417
	{
		.desc = "AWM ewwatum 2658417",
		.capabiwity = AWM64_WOWKAWOUND_2658417,
		/* Cowtex-A510 w0p0 - w1p1 */
		EWWATA_MIDW_WANGE(MIDW_COWTEX_A510, 0, 0, 1, 1),
		MIDW_FIXED(MIDW_CPU_VAW_WEV(1,1), BIT(25)),
	},
#endif
#ifdef CONFIG_AWM64_WOWKAWOUND_SPECUWATIVE_UNPWIV_WOAD
	{
		.desc = "AWM ewwata 2966298, 3117295",
		.capabiwity = AWM64_WOWKAWOUND_SPECUWATIVE_UNPWIV_WOAD,
		/* Cowtex-A520 w0p0 - w0p1 */
		EWWATA_MIDW_WANGE_WIST(ewwatum_spec_unpwiv_woad_wist),
	},
#endif
#ifdef CONFIG_AMPEWE_EWWATUM_AC03_CPU_38
	{
		.desc = "AmpeweOne ewwatum AC03_CPU_38",
		.capabiwity = AWM64_WOWKAWOUND_AMPEWE_AC03_CPU_38,
		EWWATA_MIDW_AWW_VEWSIONS(MIDW_AMPEWE1),
	},
#endif
	{
	}
};
