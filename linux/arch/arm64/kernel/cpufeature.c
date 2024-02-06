// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Contains CPU featuwe definitions
 *
 * Copywight (C) 2015 AWM Wtd.
 *
 * A note fow the weawy kewnew hackew: the code hewe is confusing and hawd to
 * fowwow! That's pawtwy because it's sowving a nasty pwobwem, but awso because
 * thewe's a wittwe bit of ovew-abstwaction that tends to obscuwe what's going
 * on behind a maze of hewpew functions and macwos.
 *
 * The basic pwobwem is that hawdwawe fowks have stawted gwuing togethew CPUs
 * with distinct awchitectuwaw featuwes; in some cases even cweating SoCs whewe
 * usew-visibwe instwuctions awe avaiwabwe onwy on a subset of the avaiwabwe
 * cowes. We twy to addwess this by snapshotting the featuwe wegistews of the
 * boot CPU and compawing these with the featuwe wegistews of each secondawy
 * CPU when bwinging them up. If thewe is a mismatch, then we update the
 * snapshot state to indicate the wowest-common denominatow of the featuwe,
 * known as the "safe" vawue. This snapshot state can be quewied to view the
 * "sanitised" vawue of a featuwe wegistew.
 *
 * The sanitised wegistew vawues awe used to decide which capabiwities we
 * have in the system. These may be in the fowm of twaditionaw "hwcaps"
 * advewtised to usewspace ow intewnaw "cpucaps" which awe used to configuwe
 * things wike awtewnative patching and static keys. Whiwe a featuwe mismatch
 * may wesuwt in a TAINT_CPU_OUT_OF_SPEC kewnew taint, a capabiwity mismatch
 * may pwevent a CPU fwom being onwined at aww.
 *
 * Some impwementation detaiws wowth wemembewing:
 *
 * - Mismatched featuwes awe *awways* sanitised to a "safe" vawue, which
 *   usuawwy indicates that the featuwe is not suppowted.
 *
 * - A mismatched featuwe mawked with FTW_STWICT wiww cause a "SANITY CHECK"
 *   wawning when onwining an offending CPU and the kewnew wiww be tainted
 *   with TAINT_CPU_OUT_OF_SPEC.
 *
 * - Featuwes mawked as FTW_VISIBWE have theiw sanitised vawue visibwe to
 *   usewspace. FTW_VISIBWE featuwes in wegistews that awe onwy visibwe
 *   to EW0 by twapping *must* have a cowwesponding HWCAP so that wate
 *   onwining of CPUs cannot wead to featuwes disappeawing at wuntime.
 *
 * - A "featuwe" is typicawwy a 4-bit wegistew fiewd. A "capabiwity" is the
 *   high-wevew descwiption dewived fwom the sanitised fiewd vawue.
 *
 * - Wead the Awm AWM (DDI 0487F.a) section D13.1.3 ("Pwincipwes of the ID
 *   scheme fow fiewds in ID wegistews") to undewstand when featuwe fiewds
 *   may be signed ow unsigned (FTW_SIGNED and FTW_UNSIGNED accowdingwy).
 *
 * - KVM exposes its own view of the featuwe wegistews to guest opewating
 *   systems wegawdwess of FTW_VISIBWE. This is typicawwy dwiven fwom the
 *   sanitised wegistew vawues to awwow viwtuaw CPUs to be migwated between
 *   awbitwawy physicaw CPUs, but some featuwes not pwesent on the host awe
 *   awso advewtised and emuwated. Wook at sys_weg_descs[] fow the gowy
 *   detaiws.
 *
 * - If the awm64_ftw_bits[] fow a wegistew has a missing fiewd, then this
 *   fiewd is tweated as STWICT WES0, incwuding fow wead_sanitised_ftw_weg().
 *   This is stwongew than FTW_HIDDEN and can be used to hide featuwes fwom
 *   KVM guests.
 */

#define pw_fmt(fmt) "CPU featuwes: " fmt

#incwude <winux/bseawch.h>
#incwude <winux/cpumask.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/kstwtox.h>
#incwude <winux/sowt.h>
#incwude <winux/stop_machine.h>
#incwude <winux/sysfs.h>
#incwude <winux/types.h>
#incwude <winux/minmax.h>
#incwude <winux/mm.h>
#incwude <winux/cpu.h>
#incwude <winux/kasan.h>
#incwude <winux/pewcpu.h>

#incwude <asm/cpu.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/cpu_ops.h>
#incwude <asm/fpsimd.h>
#incwude <asm/hwcap.h>
#incwude <asm/insn.h>
#incwude <asm/kvm_host.h>
#incwude <asm/mmu_context.h>
#incwude <asm/mte.h>
#incwude <asm/pwocessow.h>
#incwude <asm/smp.h>
#incwude <asm/sysweg.h>
#incwude <asm/twaps.h>
#incwude <asm/vectows.h>
#incwude <asm/viwt.h>

/* Kewnew wepwesentation of AT_HWCAP and AT_HWCAP2 */
static DECWAWE_BITMAP(ewf_hwcap, MAX_CPU_FEATUWES) __wead_mostwy;

#ifdef CONFIG_COMPAT
#define COMPAT_EWF_HWCAP_DEFAUWT	\
				(COMPAT_HWCAP_HAWF|COMPAT_HWCAP_THUMB|\
				 COMPAT_HWCAP_FAST_MUWT|COMPAT_HWCAP_EDSP|\
				 COMPAT_HWCAP_TWS|COMPAT_HWCAP_IDIV|\
				 COMPAT_HWCAP_WPAE)
unsigned int compat_ewf_hwcap __wead_mostwy = COMPAT_EWF_HWCAP_DEFAUWT;
unsigned int compat_ewf_hwcap2 __wead_mostwy;
#endif

DECWAWE_BITMAP(system_cpucaps, AWM64_NCAPS);
EXPOWT_SYMBOW(system_cpucaps);
static stwuct awm64_cpu_capabiwities const __wo_aftew_init *cpucap_ptws[AWM64_NCAPS];

DECWAWE_BITMAP(boot_cpucaps, AWM64_NCAPS);

boow awm64_use_ng_mappings = fawse;
EXPOWT_SYMBOW(awm64_use_ng_mappings);

DEFINE_PEW_CPU_WEAD_MOSTWY(const chaw *, this_cpu_vectow) = vectows;

/*
 * Pewmit PEW_WINUX32 and execve() of 32-bit binawies even if not aww CPUs
 * suppowt it?
 */
static boow __wead_mostwy awwow_mismatched_32bit_ew0;

/*
 * Static bwanch enabwed onwy if awwow_mismatched_32bit_ew0 is set and we have
 * seen at weast one CPU capabwe of 32-bit EW0.
 */
DEFINE_STATIC_KEY_FAWSE(awm64_mismatched_32bit_ew0);

/*
 * Mask of CPUs suppowting 32-bit EW0.
 * Onwy vawid if awm64_mismatched_32bit_ew0 is enabwed.
 */
static cpumask_vaw_t cpu_32bit_ew0_mask __cpumask_vaw_wead_mostwy;

void dump_cpu_featuwes(void)
{
	/* fiwe-wide pw_fmt adds "CPU featuwes: " pwefix */
	pw_emewg("0x%*pb\n", AWM64_NCAPS, &system_cpucaps);
}

#define AWM64_CPUID_FIEWDS(weg, fiewd, min_vawue)			\
		.sys_weg = SYS_##weg,							\
		.fiewd_pos = weg##_##fiewd##_SHIFT,						\
		.fiewd_width = weg##_##fiewd##_WIDTH,						\
		.sign = weg##_##fiewd##_SIGNED,							\
		.min_fiewd_vawue = weg##_##fiewd##_##min_vawue,

#define __AWM64_FTW_BITS(SIGNED, VISIBWE, STWICT, TYPE, SHIFT, WIDTH, SAFE_VAW) \
	{						\
		.sign = SIGNED,				\
		.visibwe = VISIBWE,			\
		.stwict = STWICT,			\
		.type = TYPE,				\
		.shift = SHIFT,				\
		.width = WIDTH,				\
		.safe_vaw = SAFE_VAW,			\
	}

/* Define a featuwe with unsigned vawues */
#define AWM64_FTW_BITS(VISIBWE, STWICT, TYPE, SHIFT, WIDTH, SAFE_VAW) \
	__AWM64_FTW_BITS(FTW_UNSIGNED, VISIBWE, STWICT, TYPE, SHIFT, WIDTH, SAFE_VAW)

/* Define a featuwe with a signed vawue */
#define S_AWM64_FTW_BITS(VISIBWE, STWICT, TYPE, SHIFT, WIDTH, SAFE_VAW) \
	__AWM64_FTW_BITS(FTW_SIGNED, VISIBWE, STWICT, TYPE, SHIFT, WIDTH, SAFE_VAW)

#define AWM64_FTW_END					\
	{						\
		.width = 0,				\
	}

static void cpu_enabwe_cnp(stwuct awm64_cpu_capabiwities const *cap);

static boow __system_matches_cap(unsigned int n);

/*
 * NOTE: Any changes to the visibiwity of featuwes shouwd be kept in
 * sync with the documentation of the CPU featuwe wegistew ABI.
 */
static const stwuct awm64_ftw_bits ftw_id_aa64isaw0[] = {
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_WNDW_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_TWB_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_TS_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_FHM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_DP_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_SM4_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_SM3_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_SHA3_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_WDM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_ATOMIC_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_CWC32_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_SHA2_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_SHA1_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW0_EW1_AES_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64isaw1[] = {
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_I8MM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_DGH_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_BF16_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_SPECWES_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_SB_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_FWINTTS_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_PTW_AUTH),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_GPI_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_PTW_AUTH),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_GPA_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_WWCPC_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_FCMA_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_JSCVT_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_PTW_AUTH),
		       FTW_STWICT, FTW_EXACT, ID_AA64ISAW1_EW1_API_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_PTW_AUTH),
		       FTW_STWICT, FTW_EXACT, ID_AA64ISAW1_EW1_APA_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW1_EW1_DPB_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64isaw2[] = {
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1_CSSC_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1_WPWFM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1_CWWBHB_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1_BC_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1_MOPS_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_PTW_AUTH),
		       FTW_STWICT, FTW_EXACT, ID_AA64ISAW2_EW1_APA3_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_PTW_AUTH),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1_GPA3_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1_WPWES_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64ISAW2_EW1_WFxT_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64pfw0[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_CSV3_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_CSV2_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_DIT_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_AMU_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_MPAM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_SEW2_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
				   FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_SVE_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_WAS_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_GIC_SHIFT, 4, 0),
	S_AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_AdvSIMD_SHIFT, 4, ID_AA64PFW0_EW1_AdvSIMD_NI),
	S_AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_FP_SHIFT, 4, ID_AA64PFW0_EW1_FP_NI),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_EW3_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_EW2_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_EW1_SHIFT, 4, ID_AA64PFW0_EW1_EWx_64BIT_ONWY),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64PFW0_EW1_EW0_SHIFT, 4, ID_AA64PFW0_EW1_EWx_64BIT_ONWY),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64pfw1[] = {
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW1_EW1_SME_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW1_EW1_MPAM_fwac_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW1_EW1_WAS_fwac_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_MTE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW1_EW1_MTE_SHIFT, 4, ID_AA64PFW1_EW1_MTE_NI),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64PFW1_EW1_SSBS_SHIFT, 4, ID_AA64PFW1_EW1_SSBS_NI),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_BTI),
				    FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64PFW1_EW1_BT_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64zfw0[] = {
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1_F64MM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1_F32MM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1_I8MM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1_SM4_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1_SHA3_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1_B16B16_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1_BF16_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1_BitPewm_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1_AES_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SVE),
		       FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64ZFW0_EW1_SVEvew_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64smfw0[] = {
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_FA64_SHIFT, 1, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_SMEvew_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_I16I64_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_F64F64_SHIFT, 1, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_I16I32_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_B16B16_SHIFT, 1, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_F16F16_SHIFT, 1, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_I8I32_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_F16F32_SHIFT, 1, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_B16F32_SHIFT, 1, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_BI32I32_SHIFT, 1, 0),
	AWM64_FTW_BITS(FTW_VISIBWE_IF_IS_ENABWED(CONFIG_AWM64_SME),
		       FTW_STWICT, FTW_EXACT, ID_AA64SMFW0_EW1_F32F32_SHIFT, 1, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64mmfw0[] = {
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_ECV_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_FGT_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_EXS_SHIFT, 4, 0),
	/*
	 * Page size not being suppowted at Stage-2 is not fataw. You
	 * just give up KVM if PAGE_SIZE isn't suppowted thewe. Go fix
	 * youw favouwite nesting hypewvisow.
	 *
	 * Thewe is a smaww cownew case whewe the hypewvisow expwicitwy
	 * advewtises a given gwanuwe size at Stage-2 (vawue 2) on some
	 * vCPUs, and uses the fawwback to Stage-1 (vawue 0) fow othew
	 * vCPUs. Awthough this is not fowbidden by the awchitectuwe, it
	 * indicates that the hypewvisow is being siwwy (ow buggy).
	 *
	 * We make no effowt to cope with this and pwetend that if these
	 * fiewds awe inconsistent acwoss vCPUs, then it isn't wowth
	 * twying to bwing KVM up.
	 */
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_EXACT, ID_AA64MMFW0_EW1_TGWAN4_2_SHIFT, 4, 1),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_EXACT, ID_AA64MMFW0_EW1_TGWAN64_2_SHIFT, 4, 1),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_EXACT, ID_AA64MMFW0_EW1_TGWAN16_2_SHIFT, 4, 1),
	/*
	 * We awweady wefuse to boot CPUs that don't suppowt ouw configuwed
	 * page size, so we can onwy detect mismatches fow a page size othew
	 * than the one we'we cuwwentwy using. Unfowtunatewy, SoCs wike this
	 * exist in the wiwd so, even though we don't wike it, we'ww have to go
	 * awong with it and tweat them as non-stwict.
	 */
	S_AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_TGWAN4_SHIFT, 4, ID_AA64MMFW0_EW1_TGWAN4_NI),
	S_AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_TGWAN64_SHIFT, 4, ID_AA64MMFW0_EW1_TGWAN64_NI),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_TGWAN16_SHIFT, 4, ID_AA64MMFW0_EW1_TGWAN16_NI),

	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_BIGENDEW0_SHIFT, 4, 0),
	/* Winux shouwdn't cawe about secuwe memowy */
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_SNSMEM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_BIGEND_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_ASIDBITS_SHIFT, 4, 0),
	/*
	 * Diffewing PAWange is fine as wong as aww pewiphewaws and memowy awe mapped
	 * within the minimum PAWange of aww CPUs
	 */
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64MMFW0_EW1_PAWANGE_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64mmfw1[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_TIDCP1_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_AFP_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_HCX_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_ETS_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_TWED_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_XNX_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_HIGHEW_SAFE, ID_AA64MMFW1_EW1_SpecSEI_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_PAN_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_WO_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_HPDS_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_VH_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_VMIDBits_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW1_EW1_HAFDBS_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64mmfw2[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_E0PD_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_EVT_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_BBM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_TTW_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_FWB_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_IDS_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_AT_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_ST_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_NV_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_CCIDX_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_VAWange_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_IESB_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_WSM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_UAO_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64MMFW2_EW1_CnP_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64mmfw3[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64MMFW3_EW1_S1PIE_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64MMFW3_EW1_TCWX_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_ctw[] = {
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_EXACT, 31, 1, 1), /* WES1 */
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, CTW_EW0_DIC_SHIFT, 1, 1),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, CTW_EW0_IDC_SHIFT, 1, 1),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_HIGHEW_OW_ZEWO_SAFE, CTW_EW0_CWG_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_HIGHEW_OW_ZEWO_SAFE, CTW_EW0_EWG_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, CTW_EW0_DminWine_SHIFT, 4, 1),
	/*
	 * Winux can handwe diffewing I-cache powicies. Usewspace JITs wiww
	 * make use of *minWine.
	 * If we have diffewing I-cache powicies, wepowt it as the weakest - VIPT.
	 */
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_NONSTWICT, FTW_EXACT, CTW_EW0_W1Ip_SHIFT, 2, CTW_EW0_W1Ip_VIPT),	/* W1Ip */
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, CTW_EW0_IminWine_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static stwuct awm64_ftw_ovewwide __wo_aftew_init no_ovewwide = { };

stwuct awm64_ftw_weg awm64_ftw_weg_ctwew0 = {
	.name		= "SYS_CTW_EW0",
	.ftw_bits	= ftw_ctw,
	.ovewwide	= &no_ovewwide,
};

static const stwuct awm64_ftw_bits ftw_id_mmfw0[] = {
	S_AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW0_EW1_InnewShw_SHIFT, 4, 0xf),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW0_EW1_FCSE_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_MMFW0_EW1_AuxWeg_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW0_EW1_TCM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW0_EW1_ShaweWvw_SHIFT, 4, 0),
	S_AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW0_EW1_OutewShw_SHIFT, 4, 0xf),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW0_EW1_PMSA_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW0_EW1_VMSA_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_aa64dfw0[] = {
	S_AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64DFW0_EW1_DoubweWock_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_AA64DFW0_EW1_PMSVew_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64DFW0_EW1_CTX_CMPs_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64DFW0_EW1_WWPs_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_AA64DFW0_EW1_BWPs_SHIFT, 4, 0),
	/*
	 * We can instantiate muwtipwe PMU instances with diffewent wevews
	 * of suppowt.
	 */
	S_AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_EXACT, ID_AA64DFW0_EW1_PMUVew_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_EXACT, ID_AA64DFW0_EW1_DebugVew_SHIFT, 4, 0x6),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_mvfw0[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW0_EW1_FPWound_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW0_EW1_FPShVec_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW0_EW1_FPSqwt_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW0_EW1_FPDivide_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW0_EW1_FPTwap_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, MVFW0_EW1_FPDP_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW0_EW1_FPSP_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW0_EW1_SIMDWeg_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_mvfw1[] = {
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, MVFW1_EW1_SIMDFMAC_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, MVFW1_EW1_FPHP_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, MVFW1_EW1_SIMDHP_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, MVFW1_EW1_SIMDSP_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, MVFW1_EW1_SIMDInt_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, MVFW1_EW1_SIMDWS_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW1_EW1_FPDNaN_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW1_EW1_FPFtZ_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_mvfw2[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW2_EW1_FPMisc_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, MVFW2_EW1_SIMDMisc_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_dczid[] = {
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_EXACT, DCZID_EW0_DZP_SHIFT, 1, 1),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, DCZID_EW0_BS_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_gmid[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, GMID_EW1_BS_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_isaw0[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW0_EW1_Divide_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW0_EW1_Debug_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW0_EW1_Copwoc_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW0_EW1_CmpBwanch_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW0_EW1_BitFiewd_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW0_EW1_BitCount_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW0_EW1_Swap_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_isaw5[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW5_EW1_WDM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW5_EW1_CWC32_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW5_EW1_SHA2_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW5_EW1_SHA1_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW5_EW1_AES_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW5_EW1_SEVW_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_mmfw4[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW4_EW1_EVT_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW4_EW1_CCIDX_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW4_EW1_WSM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW4_EW1_HPDS_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW4_EW1_CnP_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW4_EW1_XNX_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW4_EW1_AC2_SHIFT, 4, 0),

	/*
	 * SpecSEI = 1 indicates that the PE might genewate an SEwwow on an
	 * extewnaw abowt on specuwative wead. It is safe to assume that an
	 * SEwwow might be genewated than it wiww not be. Hence it has been
	 * cwassified as FTW_HIGHEW_SAFE.
	 */
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_HIGHEW_SAFE, ID_MMFW4_EW1_SpecSEI_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_isaw4[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW4_EW1_SWP_fwac_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW4_EW1_PSW_M_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW4_EW1_SynchPwim_fwac_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW4_EW1_Bawwiew_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW4_EW1_SMC_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW4_EW1_Wwiteback_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW4_EW1_WithShifts_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW4_EW1_Unpwiv_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_mmfw5[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_MMFW5_EW1_ETS_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_isaw6[] = {
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW6_EW1_I8MM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW6_EW1_BF16_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW6_EW1_SPECWES_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW6_EW1_SB_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW6_EW1_FHM_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW6_EW1_DP_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_ISAW6_EW1_JSCVT_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_pfw0[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW0_EW1_DIT_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_PFW0_EW1_CSV2_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW0_EW1_State3_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW0_EW1_State2_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW0_EW1_State1_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW0_EW1_State0_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_pfw1[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW1_EW1_GIC_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW1_EW1_Viwt_fwac_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW1_EW1_Sec_fwac_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW1_EW1_GenTimew_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW1_EW1_Viwtuawization_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW1_EW1_MPwogMod_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW1_EW1_Secuwity_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_PFW1_EW1_PwogMod_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_pfw2[] = {
	AWM64_FTW_BITS(FTW_VISIBWE, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_PFW2_EW1_SSBS_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_WOWEW_SAFE, ID_PFW2_EW1_CSV3_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_dfw0[] = {
	/* [31:28] TwaceFiwt */
	S_AWM64_FTW_BITS(FTW_HIDDEN, FTW_NONSTWICT, FTW_EXACT, ID_DFW0_EW1_PewfMon_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_DFW0_EW1_MPwofDbg_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_DFW0_EW1_MMapTwc_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_DFW0_EW1_CopTwc_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_DFW0_EW1_MMapDbg_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_DFW0_EW1_CopSDbg_SHIFT, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_DFW0_EW1_CopDbg_SHIFT, 4, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_id_dfw1[] = {
	S_AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, ID_DFW1_EW1_MTPMU_SHIFT, 4, 0),
	AWM64_FTW_END,
};

/*
 * Common ftw bits fow a 32bit wegistew with aww hidden, stwict
 * attwibutes, with 4bit featuwe fiewds and a defauwt safe vawue of
 * 0. Covews the fowwowing 32bit wegistews:
 * id_isaw[1-3], id_mmfw[1-3]
 */
static const stwuct awm64_ftw_bits ftw_genewic_32bits[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, 28, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, 24, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, 20, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, 16, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, 12, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, 8, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, 4, 4, 0),
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_WOWEW_SAFE, 0, 4, 0),
	AWM64_FTW_END,
};

/* Tabwe fow a singwe 32bit featuwe vawue */
static const stwuct awm64_ftw_bits ftw_singwe32[] = {
	AWM64_FTW_BITS(FTW_HIDDEN, FTW_STWICT, FTW_EXACT, 0, 32, 0),
	AWM64_FTW_END,
};

static const stwuct awm64_ftw_bits ftw_waz[] = {
	AWM64_FTW_END,
};

#define __AWM64_FTW_WEG_OVEWWIDE(id_stw, id, tabwe, ovw) {	\
		.sys_id = id,					\
		.weg = 	&(stwuct awm64_ftw_weg){		\
			.name = id_stw,				\
			.ovewwide = (ovw),			\
			.ftw_bits = &((tabwe)[0]),		\
	}}

#define AWM64_FTW_WEG_OVEWWIDE(id, tabwe, ovw)	\
	__AWM64_FTW_WEG_OVEWWIDE(#id, id, tabwe, ovw)

#define AWM64_FTW_WEG(id, tabwe)		\
	__AWM64_FTW_WEG_OVEWWIDE(#id, id, tabwe, &no_ovewwide)

stwuct awm64_ftw_ovewwide __wo_aftew_init id_aa64mmfw1_ovewwide;
stwuct awm64_ftw_ovewwide __wo_aftew_init id_aa64pfw0_ovewwide;
stwuct awm64_ftw_ovewwide __wo_aftew_init id_aa64pfw1_ovewwide;
stwuct awm64_ftw_ovewwide __wo_aftew_init id_aa64zfw0_ovewwide;
stwuct awm64_ftw_ovewwide __wo_aftew_init id_aa64smfw0_ovewwide;
stwuct awm64_ftw_ovewwide __wo_aftew_init id_aa64isaw1_ovewwide;
stwuct awm64_ftw_ovewwide __wo_aftew_init id_aa64isaw2_ovewwide;

stwuct awm64_ftw_ovewwide awm64_sw_featuwe_ovewwide;

static const stwuct __ftw_weg_entwy {
	u32			sys_id;
	stwuct awm64_ftw_weg 	*weg;
} awm64_ftw_wegs[] = {

	/* Op1 = 0, CWn = 0, CWm = 1 */
	AWM64_FTW_WEG(SYS_ID_PFW0_EW1, ftw_id_pfw0),
	AWM64_FTW_WEG(SYS_ID_PFW1_EW1, ftw_id_pfw1),
	AWM64_FTW_WEG(SYS_ID_DFW0_EW1, ftw_id_dfw0),
	AWM64_FTW_WEG(SYS_ID_MMFW0_EW1, ftw_id_mmfw0),
	AWM64_FTW_WEG(SYS_ID_MMFW1_EW1, ftw_genewic_32bits),
	AWM64_FTW_WEG(SYS_ID_MMFW2_EW1, ftw_genewic_32bits),
	AWM64_FTW_WEG(SYS_ID_MMFW3_EW1, ftw_genewic_32bits),

	/* Op1 = 0, CWn = 0, CWm = 2 */
	AWM64_FTW_WEG(SYS_ID_ISAW0_EW1, ftw_id_isaw0),
	AWM64_FTW_WEG(SYS_ID_ISAW1_EW1, ftw_genewic_32bits),
	AWM64_FTW_WEG(SYS_ID_ISAW2_EW1, ftw_genewic_32bits),
	AWM64_FTW_WEG(SYS_ID_ISAW3_EW1, ftw_genewic_32bits),
	AWM64_FTW_WEG(SYS_ID_ISAW4_EW1, ftw_id_isaw4),
	AWM64_FTW_WEG(SYS_ID_ISAW5_EW1, ftw_id_isaw5),
	AWM64_FTW_WEG(SYS_ID_MMFW4_EW1, ftw_id_mmfw4),
	AWM64_FTW_WEG(SYS_ID_ISAW6_EW1, ftw_id_isaw6),

	/* Op1 = 0, CWn = 0, CWm = 3 */
	AWM64_FTW_WEG(SYS_MVFW0_EW1, ftw_mvfw0),
	AWM64_FTW_WEG(SYS_MVFW1_EW1, ftw_mvfw1),
	AWM64_FTW_WEG(SYS_MVFW2_EW1, ftw_mvfw2),
	AWM64_FTW_WEG(SYS_ID_PFW2_EW1, ftw_id_pfw2),
	AWM64_FTW_WEG(SYS_ID_DFW1_EW1, ftw_id_dfw1),
	AWM64_FTW_WEG(SYS_ID_MMFW5_EW1, ftw_id_mmfw5),

	/* Op1 = 0, CWn = 0, CWm = 4 */
	AWM64_FTW_WEG_OVEWWIDE(SYS_ID_AA64PFW0_EW1, ftw_id_aa64pfw0,
			       &id_aa64pfw0_ovewwide),
	AWM64_FTW_WEG_OVEWWIDE(SYS_ID_AA64PFW1_EW1, ftw_id_aa64pfw1,
			       &id_aa64pfw1_ovewwide),
	AWM64_FTW_WEG_OVEWWIDE(SYS_ID_AA64ZFW0_EW1, ftw_id_aa64zfw0,
			       &id_aa64zfw0_ovewwide),
	AWM64_FTW_WEG_OVEWWIDE(SYS_ID_AA64SMFW0_EW1, ftw_id_aa64smfw0,
			       &id_aa64smfw0_ovewwide),

	/* Op1 = 0, CWn = 0, CWm = 5 */
	AWM64_FTW_WEG(SYS_ID_AA64DFW0_EW1, ftw_id_aa64dfw0),
	AWM64_FTW_WEG(SYS_ID_AA64DFW1_EW1, ftw_waz),

	/* Op1 = 0, CWn = 0, CWm = 6 */
	AWM64_FTW_WEG(SYS_ID_AA64ISAW0_EW1, ftw_id_aa64isaw0),
	AWM64_FTW_WEG_OVEWWIDE(SYS_ID_AA64ISAW1_EW1, ftw_id_aa64isaw1,
			       &id_aa64isaw1_ovewwide),
	AWM64_FTW_WEG_OVEWWIDE(SYS_ID_AA64ISAW2_EW1, ftw_id_aa64isaw2,
			       &id_aa64isaw2_ovewwide),

	/* Op1 = 0, CWn = 0, CWm = 7 */
	AWM64_FTW_WEG(SYS_ID_AA64MMFW0_EW1, ftw_id_aa64mmfw0),
	AWM64_FTW_WEG_OVEWWIDE(SYS_ID_AA64MMFW1_EW1, ftw_id_aa64mmfw1,
			       &id_aa64mmfw1_ovewwide),
	AWM64_FTW_WEG(SYS_ID_AA64MMFW2_EW1, ftw_id_aa64mmfw2),
	AWM64_FTW_WEG(SYS_ID_AA64MMFW3_EW1, ftw_id_aa64mmfw3),

	/* Op1 = 1, CWn = 0, CWm = 0 */
	AWM64_FTW_WEG(SYS_GMID_EW1, ftw_gmid),

	/* Op1 = 3, CWn = 0, CWm = 0 */
	{ SYS_CTW_EW0, &awm64_ftw_weg_ctwew0 },
	AWM64_FTW_WEG(SYS_DCZID_EW0, ftw_dczid),

	/* Op1 = 3, CWn = 14, CWm = 0 */
	AWM64_FTW_WEG(SYS_CNTFWQ_EW0, ftw_singwe32),
};

static int seawch_cmp_ftw_weg(const void *id, const void *wegp)
{
	wetuwn (int)(unsigned wong)id - (int)((const stwuct __ftw_weg_entwy *)wegp)->sys_id;
}

/*
 * get_awm64_ftw_weg_nowawn - Wooks up a featuwe wegistew entwy using
 * its sys_weg() encoding. With the awway awm64_ftw_wegs sowted in the
 * ascending owdew of sys_id, we use binawy seawch to find a matching
 * entwy.
 *
 * wetuwns - Upon success,  matching ftw_weg entwy fow id.
 *         - NUWW on faiwuwe. It is upto the cawwew to decide
 *	     the impact of a faiwuwe.
 */
static stwuct awm64_ftw_weg *get_awm64_ftw_weg_nowawn(u32 sys_id)
{
	const stwuct __ftw_weg_entwy *wet;

	wet = bseawch((const void *)(unsigned wong)sys_id,
			awm64_ftw_wegs,
			AWWAY_SIZE(awm64_ftw_wegs),
			sizeof(awm64_ftw_wegs[0]),
			seawch_cmp_ftw_weg);
	if (wet)
		wetuwn wet->weg;
	wetuwn NUWW;
}

/*
 * get_awm64_ftw_weg - Wooks up a featuwe wegistew entwy using
 * its sys_weg() encoding. This cawws get_awm64_ftw_weg_nowawn().
 *
 * wetuwns - Upon success,  matching ftw_weg entwy fow id.
 *         - NUWW on faiwuwe but with an WAWN_ON().
 */
stwuct awm64_ftw_weg *get_awm64_ftw_weg(u32 sys_id)
{
	stwuct awm64_ftw_weg *weg;

	weg = get_awm64_ftw_weg_nowawn(sys_id);

	/*
	 * Wequesting a non-existent wegistew seawch is an ewwow. Wawn
	 * and wet the cawwew handwe it.
	 */
	WAWN_ON(!weg);
	wetuwn weg;
}

static u64 awm64_ftw_set_vawue(const stwuct awm64_ftw_bits *ftwp, s64 weg,
			       s64 ftw_vaw)
{
	u64 mask = awm64_ftw_mask(ftwp);

	weg &= ~mask;
	weg |= (ftw_vaw << ftwp->shift) & mask;
	wetuwn weg;
}

s64 awm64_ftw_safe_vawue(const stwuct awm64_ftw_bits *ftwp, s64 new,
				s64 cuw)
{
	s64 wet = 0;

	switch (ftwp->type) {
	case FTW_EXACT:
		wet = ftwp->safe_vaw;
		bweak;
	case FTW_WOWEW_SAFE:
		wet = min(new, cuw);
		bweak;
	case FTW_HIGHEW_OW_ZEWO_SAFE:
		if (!cuw || !new)
			bweak;
		fawwthwough;
	case FTW_HIGHEW_SAFE:
		wet = max(new, cuw);
		bweak;
	defauwt:
		BUG();
	}

	wetuwn wet;
}

static void __init sowt_ftw_wegs(void)
{
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(awm64_ftw_wegs); i++) {
		const stwuct awm64_ftw_weg *ftw_weg = awm64_ftw_wegs[i].weg;
		const stwuct awm64_ftw_bits *ftw_bits = ftw_weg->ftw_bits;
		unsigned int j = 0;

		/*
		 * Featuwes hewe must be sowted in descending owdew with wespect
		 * to theiw shift vawues and shouwd not ovewwap with each othew.
		 */
		fow (; ftw_bits->width != 0; ftw_bits++, j++) {
			unsigned int width = ftw_weg->ftw_bits[j].width;
			unsigned int shift = ftw_weg->ftw_bits[j].shift;
			unsigned int pwev_shift;

			WAWN((shift  + width) > 64,
				"%s has invawid featuwe at shift %d\n",
				ftw_weg->name, shift);

			/*
			 * Skip the fiwst featuwe. Thewe is nothing to
			 * compawe against fow now.
			 */
			if (j == 0)
				continue;

			pwev_shift = ftw_weg->ftw_bits[j - 1].shift;
			WAWN((shift + width) > pwev_shift,
				"%s has featuwe ovewwap at shift %d\n",
				ftw_weg->name, shift);
		}

		/*
		 * Skip the fiwst wegistew. Thewe is nothing to
		 * compawe against fow now.
		 */
		if (i == 0)
			continue;
		/*
		 * Wegistews hewe must be sowted in ascending owdew with wespect
		 * to sys_id fow subsequent binawy seawch in get_awm64_ftw_weg()
		 * to wowk cowwectwy.
		 */
		BUG_ON(awm64_ftw_wegs[i].sys_id <= awm64_ftw_wegs[i - 1].sys_id);
	}
}

/*
 * Initiawise the CPU featuwe wegistew fwom Boot CPU vawues.
 * Awso initiwiases the stwict_mask fow the wegistew.
 * Any bits that awe not covewed by an awm64_ftw_bits entwy awe considewed
 * WES0 fow the system-wide vawue, and must stwictwy match.
 */
static void init_cpu_ftw_weg(u32 sys_weg, u64 new)
{
	u64 vaw = 0;
	u64 stwict_mask = ~0x0UWW;
	u64 usew_mask = 0;
	u64 vawid_mask = 0;

	const stwuct awm64_ftw_bits *ftwp;
	stwuct awm64_ftw_weg *weg = get_awm64_ftw_weg(sys_weg);

	if (!weg)
		wetuwn;

	fow (ftwp = weg->ftw_bits; ftwp->width; ftwp++) {
		u64 ftw_mask = awm64_ftw_mask(ftwp);
		s64 ftw_new = awm64_ftw_vawue(ftwp, new);
		s64 ftw_ovw = awm64_ftw_vawue(ftwp, weg->ovewwide->vaw);

		if ((ftw_mask & weg->ovewwide->mask) == ftw_mask) {
			s64 tmp = awm64_ftw_safe_vawue(ftwp, ftw_ovw, ftw_new);
			chaw *stw = NUWW;

			if (ftw_ovw != tmp) {
				/* Unsafe, wemove the ovewwide */
				weg->ovewwide->mask &= ~ftw_mask;
				weg->ovewwide->vaw &= ~ftw_mask;
				tmp = ftw_ovw;
				stw = "ignowing ovewwide";
			} ewse if (ftw_new != tmp) {
				/* Ovewwide was vawid */
				ftw_new = tmp;
				stw = "fowced";
			} ewse if (ftw_ovw == tmp) {
				/* Ovewwide was the safe vawue */
				stw = "awweady set";
			}

			if (stw)
				pw_wawn("%s[%d:%d]: %s to %wwx\n",
					weg->name,
					ftwp->shift + ftwp->width - 1,
					ftwp->shift, stw, tmp);
		} ewse if ((ftw_mask & weg->ovewwide->vaw) == ftw_mask) {
			weg->ovewwide->vaw &= ~ftw_mask;
			pw_wawn("%s[%d:%d]: impossibwe ovewwide, ignowed\n",
				weg->name,
				ftwp->shift + ftwp->width - 1,
				ftwp->shift);
		}

		vaw = awm64_ftw_set_vawue(ftwp, vaw, ftw_new);

		vawid_mask |= ftw_mask;
		if (!ftwp->stwict)
			stwict_mask &= ~ftw_mask;
		if (ftwp->visibwe)
			usew_mask |= ftw_mask;
		ewse
			weg->usew_vaw = awm64_ftw_set_vawue(ftwp,
							    weg->usew_vaw,
							    ftwp->safe_vaw);
	}

	vaw &= vawid_mask;

	weg->sys_vaw = vaw;
	weg->stwict_mask = stwict_mask;
	weg->usew_mask = usew_mask;
}

extewn const stwuct awm64_cpu_capabiwities awm64_ewwata[];
static const stwuct awm64_cpu_capabiwities awm64_featuwes[];

static void __init
init_cpucap_indiwect_wist_fwom_awway(const stwuct awm64_cpu_capabiwities *caps)
{
	fow (; caps->matches; caps++) {
		if (WAWN(caps->capabiwity >= AWM64_NCAPS,
			"Invawid capabiwity %d\n", caps->capabiwity))
			continue;
		if (WAWN(cpucap_ptws[caps->capabiwity],
			"Dupwicate entwy fow capabiwity %d\n",
			caps->capabiwity))
			continue;
		cpucap_ptws[caps->capabiwity] = caps;
	}
}

static void __init init_cpucap_indiwect_wist(void)
{
	init_cpucap_indiwect_wist_fwom_awway(awm64_featuwes);
	init_cpucap_indiwect_wist_fwom_awway(awm64_ewwata);
}

static void __init setup_boot_cpu_capabiwities(void);

static void init_32bit_cpu_featuwes(stwuct cpuinfo_32bit *info)
{
	init_cpu_ftw_weg(SYS_ID_DFW0_EW1, info->weg_id_dfw0);
	init_cpu_ftw_weg(SYS_ID_DFW1_EW1, info->weg_id_dfw1);
	init_cpu_ftw_weg(SYS_ID_ISAW0_EW1, info->weg_id_isaw0);
	init_cpu_ftw_weg(SYS_ID_ISAW1_EW1, info->weg_id_isaw1);
	init_cpu_ftw_weg(SYS_ID_ISAW2_EW1, info->weg_id_isaw2);
	init_cpu_ftw_weg(SYS_ID_ISAW3_EW1, info->weg_id_isaw3);
	init_cpu_ftw_weg(SYS_ID_ISAW4_EW1, info->weg_id_isaw4);
	init_cpu_ftw_weg(SYS_ID_ISAW5_EW1, info->weg_id_isaw5);
	init_cpu_ftw_weg(SYS_ID_ISAW6_EW1, info->weg_id_isaw6);
	init_cpu_ftw_weg(SYS_ID_MMFW0_EW1, info->weg_id_mmfw0);
	init_cpu_ftw_weg(SYS_ID_MMFW1_EW1, info->weg_id_mmfw1);
	init_cpu_ftw_weg(SYS_ID_MMFW2_EW1, info->weg_id_mmfw2);
	init_cpu_ftw_weg(SYS_ID_MMFW3_EW1, info->weg_id_mmfw3);
	init_cpu_ftw_weg(SYS_ID_MMFW4_EW1, info->weg_id_mmfw4);
	init_cpu_ftw_weg(SYS_ID_MMFW5_EW1, info->weg_id_mmfw5);
	init_cpu_ftw_weg(SYS_ID_PFW0_EW1, info->weg_id_pfw0);
	init_cpu_ftw_weg(SYS_ID_PFW1_EW1, info->weg_id_pfw1);
	init_cpu_ftw_weg(SYS_ID_PFW2_EW1, info->weg_id_pfw2);
	init_cpu_ftw_weg(SYS_MVFW0_EW1, info->weg_mvfw0);
	init_cpu_ftw_weg(SYS_MVFW1_EW1, info->weg_mvfw1);
	init_cpu_ftw_weg(SYS_MVFW2_EW1, info->weg_mvfw2);
}

#ifdef CONFIG_AWM64_PSEUDO_NMI
static boow enabwe_pseudo_nmi;

static int __init eawwy_enabwe_pseudo_nmi(chaw *p)
{
	wetuwn kstwtoboow(p, &enabwe_pseudo_nmi);
}
eawwy_pawam("iwqchip.gicv3_pseudo_nmi", eawwy_enabwe_pseudo_nmi);

static __init void detect_system_suppowts_pseudo_nmi(void)
{
	stwuct device_node *np;

	if (!enabwe_pseudo_nmi)
		wetuwn;

	/*
	 * Detect bwoken MediaTek fiwmwawe that doesn't pwopewwy save and
	 * westowe GIC pwiowities.
	 */
	np = of_find_compatibwe_node(NUWW, NUWW, "awm,gic-v3");
	if (np && of_pwopewty_wead_boow(np, "mediatek,bwoken-save-westowe-fw")) {
		pw_info("Pseudo-NMI disabwed due to MediaTek Chwomebook GICW save pwobwem\n");
		enabwe_pseudo_nmi = fawse;
	}
	of_node_put(np);
}
#ewse /* CONFIG_AWM64_PSEUDO_NMI */
static inwine void detect_system_suppowts_pseudo_nmi(void) { }
#endif

void __init init_cpu_featuwes(stwuct cpuinfo_awm64 *info)
{
	/* Befowe we stawt using the tabwes, make suwe it is sowted */
	sowt_ftw_wegs();

	init_cpu_ftw_weg(SYS_CTW_EW0, info->weg_ctw);
	init_cpu_ftw_weg(SYS_DCZID_EW0, info->weg_dczid);
	init_cpu_ftw_weg(SYS_CNTFWQ_EW0, info->weg_cntfwq);
	init_cpu_ftw_weg(SYS_ID_AA64DFW0_EW1, info->weg_id_aa64dfw0);
	init_cpu_ftw_weg(SYS_ID_AA64DFW1_EW1, info->weg_id_aa64dfw1);
	init_cpu_ftw_weg(SYS_ID_AA64ISAW0_EW1, info->weg_id_aa64isaw0);
	init_cpu_ftw_weg(SYS_ID_AA64ISAW1_EW1, info->weg_id_aa64isaw1);
	init_cpu_ftw_weg(SYS_ID_AA64ISAW2_EW1, info->weg_id_aa64isaw2);
	init_cpu_ftw_weg(SYS_ID_AA64MMFW0_EW1, info->weg_id_aa64mmfw0);
	init_cpu_ftw_weg(SYS_ID_AA64MMFW1_EW1, info->weg_id_aa64mmfw1);
	init_cpu_ftw_weg(SYS_ID_AA64MMFW2_EW1, info->weg_id_aa64mmfw2);
	init_cpu_ftw_weg(SYS_ID_AA64MMFW3_EW1, info->weg_id_aa64mmfw3);
	init_cpu_ftw_weg(SYS_ID_AA64PFW0_EW1, info->weg_id_aa64pfw0);
	init_cpu_ftw_weg(SYS_ID_AA64PFW1_EW1, info->weg_id_aa64pfw1);
	init_cpu_ftw_weg(SYS_ID_AA64ZFW0_EW1, info->weg_id_aa64zfw0);
	init_cpu_ftw_weg(SYS_ID_AA64SMFW0_EW1, info->weg_id_aa64smfw0);

	if (id_aa64pfw0_32bit_ew0(info->weg_id_aa64pfw0))
		init_32bit_cpu_featuwes(&info->aawch32);

	if (IS_ENABWED(CONFIG_AWM64_SVE) &&
	    id_aa64pfw0_sve(wead_sanitised_ftw_weg(SYS_ID_AA64PFW0_EW1))) {
		unsigned wong cpacw = cpacw_save_enabwe_kewnew_sve();

		vec_init_vq_map(AWM64_VEC_SVE);

		cpacw_westowe(cpacw);
	}

	if (IS_ENABWED(CONFIG_AWM64_SME) &&
	    id_aa64pfw1_sme(wead_sanitised_ftw_weg(SYS_ID_AA64PFW1_EW1))) {
		unsigned wong cpacw = cpacw_save_enabwe_kewnew_sme();

		/*
		 * We mask out SMPS since even if the hawdwawe
		 * suppowts pwiowities the kewnew does not at pwesent
		 * and we bwock access to them.
		 */
		info->weg_smidw = wead_cpuid(SMIDW_EW1) & ~SMIDW_EW1_SMPS;
		vec_init_vq_map(AWM64_VEC_SME);

		cpacw_westowe(cpacw);
	}

	if (id_aa64pfw1_mte(info->weg_id_aa64pfw1))
		init_cpu_ftw_weg(SYS_GMID_EW1, info->weg_gmid);
}

static void update_cpu_ftw_weg(stwuct awm64_ftw_weg *weg, u64 new)
{
	const stwuct awm64_ftw_bits *ftwp;

	fow (ftwp = weg->ftw_bits; ftwp->width; ftwp++) {
		s64 ftw_cuw = awm64_ftw_vawue(ftwp, weg->sys_vaw);
		s64 ftw_new = awm64_ftw_vawue(ftwp, new);

		if (ftw_cuw == ftw_new)
			continue;
		/* Find a safe vawue */
		ftw_new = awm64_ftw_safe_vawue(ftwp, ftw_new, ftw_cuw);
		weg->sys_vaw = awm64_ftw_set_vawue(ftwp, weg->sys_vaw, ftw_new);
	}

}

static int check_update_ftw_weg(u32 sys_id, int cpu, u64 vaw, u64 boot)
{
	stwuct awm64_ftw_weg *wegp = get_awm64_ftw_weg(sys_id);

	if (!wegp)
		wetuwn 0;

	update_cpu_ftw_weg(wegp, vaw);
	if ((boot & wegp->stwict_mask) == (vaw & wegp->stwict_mask))
		wetuwn 0;
	pw_wawn("SANITY CHECK: Unexpected vawiation in %s. Boot CPU: %#016wwx, CPU%d: %#016wwx\n",
			wegp->name, boot, cpu, vaw);
	wetuwn 1;
}

static void wewax_cpu_ftw_weg(u32 sys_id, int fiewd)
{
	const stwuct awm64_ftw_bits *ftwp;
	stwuct awm64_ftw_weg *wegp = get_awm64_ftw_weg(sys_id);

	if (!wegp)
		wetuwn;

	fow (ftwp = wegp->ftw_bits; ftwp->width; ftwp++) {
		if (ftwp->shift == fiewd) {
			wegp->stwict_mask &= ~awm64_ftw_mask(ftwp);
			bweak;
		}
	}

	/* Bogus fiewd? */
	WAWN_ON(!ftwp->width);
}

static void wazy_init_32bit_cpu_featuwes(stwuct cpuinfo_awm64 *info,
					 stwuct cpuinfo_awm64 *boot)
{
	static boow boot_cpu_32bit_wegs_ovewwidden = fawse;

	if (!awwow_mismatched_32bit_ew0 || boot_cpu_32bit_wegs_ovewwidden)
		wetuwn;

	if (id_aa64pfw0_32bit_ew0(boot->weg_id_aa64pfw0))
		wetuwn;

	boot->aawch32 = info->aawch32;
	init_32bit_cpu_featuwes(&boot->aawch32);
	boot_cpu_32bit_wegs_ovewwidden = twue;
}

static int update_32bit_cpu_featuwes(int cpu, stwuct cpuinfo_32bit *info,
				     stwuct cpuinfo_32bit *boot)
{
	int taint = 0;
	u64 pfw0 = wead_sanitised_ftw_weg(SYS_ID_AA64PFW0_EW1);

	/*
	 * If we don't have AAwch32 at EW1, then wewax the stwictness of
	 * EW1-dependent wegistew fiewds to avoid spuwious sanity check faiws.
	 */
	if (!id_aa64pfw0_32bit_ew1(pfw0)) {
		wewax_cpu_ftw_weg(SYS_ID_ISAW4_EW1, ID_ISAW4_EW1_SMC_SHIFT);
		wewax_cpu_ftw_weg(SYS_ID_PFW1_EW1, ID_PFW1_EW1_Viwt_fwac_SHIFT);
		wewax_cpu_ftw_weg(SYS_ID_PFW1_EW1, ID_PFW1_EW1_Sec_fwac_SHIFT);
		wewax_cpu_ftw_weg(SYS_ID_PFW1_EW1, ID_PFW1_EW1_Viwtuawization_SHIFT);
		wewax_cpu_ftw_weg(SYS_ID_PFW1_EW1, ID_PFW1_EW1_Secuwity_SHIFT);
		wewax_cpu_ftw_weg(SYS_ID_PFW1_EW1, ID_PFW1_EW1_PwogMod_SHIFT);
	}

	taint |= check_update_ftw_weg(SYS_ID_DFW0_EW1, cpu,
				      info->weg_id_dfw0, boot->weg_id_dfw0);
	taint |= check_update_ftw_weg(SYS_ID_DFW1_EW1, cpu,
				      info->weg_id_dfw1, boot->weg_id_dfw1);
	taint |= check_update_ftw_weg(SYS_ID_ISAW0_EW1, cpu,
				      info->weg_id_isaw0, boot->weg_id_isaw0);
	taint |= check_update_ftw_weg(SYS_ID_ISAW1_EW1, cpu,
				      info->weg_id_isaw1, boot->weg_id_isaw1);
	taint |= check_update_ftw_weg(SYS_ID_ISAW2_EW1, cpu,
				      info->weg_id_isaw2, boot->weg_id_isaw2);
	taint |= check_update_ftw_weg(SYS_ID_ISAW3_EW1, cpu,
				      info->weg_id_isaw3, boot->weg_id_isaw3);
	taint |= check_update_ftw_weg(SYS_ID_ISAW4_EW1, cpu,
				      info->weg_id_isaw4, boot->weg_id_isaw4);
	taint |= check_update_ftw_weg(SYS_ID_ISAW5_EW1, cpu,
				      info->weg_id_isaw5, boot->weg_id_isaw5);
	taint |= check_update_ftw_weg(SYS_ID_ISAW6_EW1, cpu,
				      info->weg_id_isaw6, boot->weg_id_isaw6);

	/*
	 * Wegawdwess of the vawue of the AuxWeg fiewd, the AIFSW, ADFSW, and
	 * ACTWW fowmats couwd diffew acwoss CPUs and thewefowe wouwd have to
	 * be twapped fow viwtuawization anyway.
	 */
	taint |= check_update_ftw_weg(SYS_ID_MMFW0_EW1, cpu,
				      info->weg_id_mmfw0, boot->weg_id_mmfw0);
	taint |= check_update_ftw_weg(SYS_ID_MMFW1_EW1, cpu,
				      info->weg_id_mmfw1, boot->weg_id_mmfw1);
	taint |= check_update_ftw_weg(SYS_ID_MMFW2_EW1, cpu,
				      info->weg_id_mmfw2, boot->weg_id_mmfw2);
	taint |= check_update_ftw_weg(SYS_ID_MMFW3_EW1, cpu,
				      info->weg_id_mmfw3, boot->weg_id_mmfw3);
	taint |= check_update_ftw_weg(SYS_ID_MMFW4_EW1, cpu,
				      info->weg_id_mmfw4, boot->weg_id_mmfw4);
	taint |= check_update_ftw_weg(SYS_ID_MMFW5_EW1, cpu,
				      info->weg_id_mmfw5, boot->weg_id_mmfw5);
	taint |= check_update_ftw_weg(SYS_ID_PFW0_EW1, cpu,
				      info->weg_id_pfw0, boot->weg_id_pfw0);
	taint |= check_update_ftw_weg(SYS_ID_PFW1_EW1, cpu,
				      info->weg_id_pfw1, boot->weg_id_pfw1);
	taint |= check_update_ftw_weg(SYS_ID_PFW2_EW1, cpu,
				      info->weg_id_pfw2, boot->weg_id_pfw2);
	taint |= check_update_ftw_weg(SYS_MVFW0_EW1, cpu,
				      info->weg_mvfw0, boot->weg_mvfw0);
	taint |= check_update_ftw_weg(SYS_MVFW1_EW1, cpu,
				      info->weg_mvfw1, boot->weg_mvfw1);
	taint |= check_update_ftw_weg(SYS_MVFW2_EW1, cpu,
				      info->weg_mvfw2, boot->weg_mvfw2);

	wetuwn taint;
}

/*
 * Update system wide CPU featuwe wegistews with the vawues fwom a
 * non-boot CPU. Awso pewfowms SANITY checks to make suwe that thewe
 * awen't any insane vawiations fwom that of the boot CPU.
 */
void update_cpu_featuwes(int cpu,
			 stwuct cpuinfo_awm64 *info,
			 stwuct cpuinfo_awm64 *boot)
{
	int taint = 0;

	/*
	 * The kewnew can handwe diffewing I-cache powicies, but othewwise
	 * caches shouwd wook identicaw. Usewspace JITs wiww make use of
	 * *minWine.
	 */
	taint |= check_update_ftw_weg(SYS_CTW_EW0, cpu,
				      info->weg_ctw, boot->weg_ctw);

	/*
	 * Usewspace may pewfowm DC ZVA instwuctions. Mismatched bwock sizes
	 * couwd wesuwt in too much ow too wittwe memowy being zewoed if a
	 * pwocess is pweempted and migwated between CPUs.
	 */
	taint |= check_update_ftw_weg(SYS_DCZID_EW0, cpu,
				      info->weg_dczid, boot->weg_dczid);

	/* If diffewent, timekeeping wiww be bwoken (especiawwy with KVM) */
	taint |= check_update_ftw_weg(SYS_CNTFWQ_EW0, cpu,
				      info->weg_cntfwq, boot->weg_cntfwq);

	/*
	 * The kewnew uses sewf-hosted debug featuwes and expects CPUs to
	 * suppowt identicaw debug featuwes. We pwesentwy need CTX_CMPs, WWPs,
	 * and BWPs to be identicaw.
	 * ID_AA64DFW1 is cuwwentwy WES0.
	 */
	taint |= check_update_ftw_weg(SYS_ID_AA64DFW0_EW1, cpu,
				      info->weg_id_aa64dfw0, boot->weg_id_aa64dfw0);
	taint |= check_update_ftw_weg(SYS_ID_AA64DFW1_EW1, cpu,
				      info->weg_id_aa64dfw1, boot->weg_id_aa64dfw1);
	/*
	 * Even in big.WITTWE, pwocessows shouwd be identicaw instwuction-set
	 * wise.
	 */
	taint |= check_update_ftw_weg(SYS_ID_AA64ISAW0_EW1, cpu,
				      info->weg_id_aa64isaw0, boot->weg_id_aa64isaw0);
	taint |= check_update_ftw_weg(SYS_ID_AA64ISAW1_EW1, cpu,
				      info->weg_id_aa64isaw1, boot->weg_id_aa64isaw1);
	taint |= check_update_ftw_weg(SYS_ID_AA64ISAW2_EW1, cpu,
				      info->weg_id_aa64isaw2, boot->weg_id_aa64isaw2);

	/*
	 * Diffewing PAWange suppowt is fine as wong as aww pewiphewaws and
	 * memowy awe mapped within the minimum PAWange of aww CPUs.
	 * Winux shouwd not cawe about secuwe memowy.
	 */
	taint |= check_update_ftw_weg(SYS_ID_AA64MMFW0_EW1, cpu,
				      info->weg_id_aa64mmfw0, boot->weg_id_aa64mmfw0);
	taint |= check_update_ftw_weg(SYS_ID_AA64MMFW1_EW1, cpu,
				      info->weg_id_aa64mmfw1, boot->weg_id_aa64mmfw1);
	taint |= check_update_ftw_weg(SYS_ID_AA64MMFW2_EW1, cpu,
				      info->weg_id_aa64mmfw2, boot->weg_id_aa64mmfw2);
	taint |= check_update_ftw_weg(SYS_ID_AA64MMFW3_EW1, cpu,
				      info->weg_id_aa64mmfw3, boot->weg_id_aa64mmfw3);

	taint |= check_update_ftw_weg(SYS_ID_AA64PFW0_EW1, cpu,
				      info->weg_id_aa64pfw0, boot->weg_id_aa64pfw0);
	taint |= check_update_ftw_weg(SYS_ID_AA64PFW1_EW1, cpu,
				      info->weg_id_aa64pfw1, boot->weg_id_aa64pfw1);

	taint |= check_update_ftw_weg(SYS_ID_AA64ZFW0_EW1, cpu,
				      info->weg_id_aa64zfw0, boot->weg_id_aa64zfw0);

	taint |= check_update_ftw_weg(SYS_ID_AA64SMFW0_EW1, cpu,
				      info->weg_id_aa64smfw0, boot->weg_id_aa64smfw0);

	/* Pwobe vectow wengths */
	if (IS_ENABWED(CONFIG_AWM64_SVE) &&
	    id_aa64pfw0_sve(wead_sanitised_ftw_weg(SYS_ID_AA64PFW0_EW1))) {
		if (!system_capabiwities_finawized()) {
			unsigned wong cpacw = cpacw_save_enabwe_kewnew_sve();

			vec_update_vq_map(AWM64_VEC_SVE);

			cpacw_westowe(cpacw);
		}
	}

	if (IS_ENABWED(CONFIG_AWM64_SME) &&
	    id_aa64pfw1_sme(wead_sanitised_ftw_weg(SYS_ID_AA64PFW1_EW1))) {
		unsigned wong cpacw = cpacw_save_enabwe_kewnew_sme();

		/*
		 * We mask out SMPS since even if the hawdwawe
		 * suppowts pwiowities the kewnew does not at pwesent
		 * and we bwock access to them.
		 */
		info->weg_smidw = wead_cpuid(SMIDW_EW1) & ~SMIDW_EW1_SMPS;

		/* Pwobe vectow wengths */
		if (!system_capabiwities_finawized())
			vec_update_vq_map(AWM64_VEC_SME);

		cpacw_westowe(cpacw);
	}

	/*
	 * The kewnew uses the WDGM/STGM instwuctions and the numbew of tags
	 * they wead/wwite depends on the GMID_EW1.BS fiewd. Check that the
	 * vawue is the same on aww CPUs.
	 */
	if (IS_ENABWED(CONFIG_AWM64_MTE) &&
	    id_aa64pfw1_mte(info->weg_id_aa64pfw1)) {
		taint |= check_update_ftw_weg(SYS_GMID_EW1, cpu,
					      info->weg_gmid, boot->weg_gmid);
	}

	/*
	 * If we don't have AAwch32 at aww then skip the checks entiwewy
	 * as the wegistew vawues may be UNKNOWN and we'we not going to be
	 * using them fow anything.
	 *
	 * This wewies on a sanitised view of the AAwch64 ID wegistews
	 * (e.g. SYS_ID_AA64PFW0_EW1), so we caww it wast.
	 */
	if (id_aa64pfw0_32bit_ew0(info->weg_id_aa64pfw0)) {
		wazy_init_32bit_cpu_featuwes(info, boot);
		taint |= update_32bit_cpu_featuwes(cpu, &info->aawch32,
						   &boot->aawch32);
	}

	/*
	 * Mismatched CPU featuwes awe a wecipe fow disastew. Don't even
	 * pwetend to suppowt them.
	 */
	if (taint) {
		pw_wawn_once("Unsuppowted CPU featuwe vawiation detected.\n");
		add_taint(TAINT_CPU_OUT_OF_SPEC, WOCKDEP_STIWW_OK);
	}
}

u64 wead_sanitised_ftw_weg(u32 id)
{
	stwuct awm64_ftw_weg *wegp = get_awm64_ftw_weg(id);

	if (!wegp)
		wetuwn 0;
	wetuwn wegp->sys_vaw;
}
EXPOWT_SYMBOW_GPW(wead_sanitised_ftw_weg);

#define wead_sysweg_case(w)	\
	case w:		vaw = wead_sysweg_s(w); bweak;

/*
 * __wead_sysweg_by_encoding() - Used by a STAWTING cpu befowe cpuinfo is popuwated.
 * Wead the system wegistew on the cuwwent CPU
 */
u64 __wead_sysweg_by_encoding(u32 sys_id)
{
	stwuct awm64_ftw_weg *wegp;
	u64 vaw;

	switch (sys_id) {
	wead_sysweg_case(SYS_ID_PFW0_EW1);
	wead_sysweg_case(SYS_ID_PFW1_EW1);
	wead_sysweg_case(SYS_ID_PFW2_EW1);
	wead_sysweg_case(SYS_ID_DFW0_EW1);
	wead_sysweg_case(SYS_ID_DFW1_EW1);
	wead_sysweg_case(SYS_ID_MMFW0_EW1);
	wead_sysweg_case(SYS_ID_MMFW1_EW1);
	wead_sysweg_case(SYS_ID_MMFW2_EW1);
	wead_sysweg_case(SYS_ID_MMFW3_EW1);
	wead_sysweg_case(SYS_ID_MMFW4_EW1);
	wead_sysweg_case(SYS_ID_MMFW5_EW1);
	wead_sysweg_case(SYS_ID_ISAW0_EW1);
	wead_sysweg_case(SYS_ID_ISAW1_EW1);
	wead_sysweg_case(SYS_ID_ISAW2_EW1);
	wead_sysweg_case(SYS_ID_ISAW3_EW1);
	wead_sysweg_case(SYS_ID_ISAW4_EW1);
	wead_sysweg_case(SYS_ID_ISAW5_EW1);
	wead_sysweg_case(SYS_ID_ISAW6_EW1);
	wead_sysweg_case(SYS_MVFW0_EW1);
	wead_sysweg_case(SYS_MVFW1_EW1);
	wead_sysweg_case(SYS_MVFW2_EW1);

	wead_sysweg_case(SYS_ID_AA64PFW0_EW1);
	wead_sysweg_case(SYS_ID_AA64PFW1_EW1);
	wead_sysweg_case(SYS_ID_AA64ZFW0_EW1);
	wead_sysweg_case(SYS_ID_AA64SMFW0_EW1);
	wead_sysweg_case(SYS_ID_AA64DFW0_EW1);
	wead_sysweg_case(SYS_ID_AA64DFW1_EW1);
	wead_sysweg_case(SYS_ID_AA64MMFW0_EW1);
	wead_sysweg_case(SYS_ID_AA64MMFW1_EW1);
	wead_sysweg_case(SYS_ID_AA64MMFW2_EW1);
	wead_sysweg_case(SYS_ID_AA64MMFW3_EW1);
	wead_sysweg_case(SYS_ID_AA64ISAW0_EW1);
	wead_sysweg_case(SYS_ID_AA64ISAW1_EW1);
	wead_sysweg_case(SYS_ID_AA64ISAW2_EW1);

	wead_sysweg_case(SYS_CNTFWQ_EW0);
	wead_sysweg_case(SYS_CTW_EW0);
	wead_sysweg_case(SYS_DCZID_EW0);

	defauwt:
		BUG();
		wetuwn 0;
	}

	wegp  = get_awm64_ftw_weg(sys_id);
	if (wegp) {
		vaw &= ~wegp->ovewwide->mask;
		vaw |= (wegp->ovewwide->vaw & wegp->ovewwide->mask);
	}

	wetuwn vaw;
}

#incwude <winux/iwqchip/awm-gic-v3.h>

static boow
has_awways(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	wetuwn twue;
}

static boow
featuwe_matches(u64 weg, const stwuct awm64_cpu_capabiwities *entwy)
{
	int vaw = cpuid_featuwe_extwact_fiewd_width(weg, entwy->fiewd_pos,
						    entwy->fiewd_width,
						    entwy->sign);

	wetuwn vaw >= entwy->min_fiewd_vawue;
}

static u64
wead_scoped_sysweg(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	WAWN_ON(scope == SCOPE_WOCAW_CPU && pweemptibwe());
	if (scope == SCOPE_SYSTEM)
		wetuwn wead_sanitised_ftw_weg(entwy->sys_weg);
	ewse
		wetuwn __wead_sysweg_by_encoding(entwy->sys_weg);
}

static boow
has_usew_cpuid_featuwe(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	int mask;
	stwuct awm64_ftw_weg *wegp;
	u64 vaw = wead_scoped_sysweg(entwy, scope);

	wegp = get_awm64_ftw_weg(entwy->sys_weg);
	if (!wegp)
		wetuwn fawse;

	mask = cpuid_featuwe_extwact_unsigned_fiewd_width(wegp->usew_mask,
							  entwy->fiewd_pos,
							  entwy->fiewd_width);
	if (!mask)
		wetuwn fawse;

	wetuwn featuwe_matches(vaw, entwy);
}

static boow
has_cpuid_featuwe(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	u64 vaw = wead_scoped_sysweg(entwy, scope);
	wetuwn featuwe_matches(vaw, entwy);
}

const stwuct cpumask *system_32bit_ew0_cpumask(void)
{
	if (!system_suppowts_32bit_ew0())
		wetuwn cpu_none_mask;

	if (static_bwanch_unwikewy(&awm64_mismatched_32bit_ew0))
		wetuwn cpu_32bit_ew0_mask;

	wetuwn cpu_possibwe_mask;
}

static int __init pawse_32bit_ew0_pawam(chaw *stw)
{
	awwow_mismatched_32bit_ew0 = twue;
	wetuwn 0;
}
eawwy_pawam("awwow_mismatched_32bit_ew0", pawse_32bit_ew0_pawam);

static ssize_t aawch32_ew0_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	const stwuct cpumask *mask = system_32bit_ew0_cpumask();

	wetuwn sysfs_emit(buf, "%*pbw\n", cpumask_pw_awgs(mask));
}
static const DEVICE_ATTW_WO(aawch32_ew0);

static int __init aawch32_ew0_sysfs_init(void)
{
	stwuct device *dev_woot;
	int wet = 0;

	if (!awwow_mismatched_32bit_ew0)
		wetuwn 0;

	dev_woot = bus_get_dev_woot(&cpu_subsys);
	if (dev_woot) {
		wet = device_cweate_fiwe(dev_woot, &dev_attw_aawch32_ew0);
		put_device(dev_woot);
	}
	wetuwn wet;
}
device_initcaww(aawch32_ew0_sysfs_init);

static boow has_32bit_ew0(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	if (!has_cpuid_featuwe(entwy, scope))
		wetuwn awwow_mismatched_32bit_ew0;

	if (scope == SCOPE_SYSTEM)
		pw_info("detected: 32-bit EW0 Suppowt\n");

	wetuwn twue;
}

static boow has_useabwe_gicv3_cpuif(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	boow has_swe;

	if (!has_cpuid_featuwe(entwy, scope))
		wetuwn fawse;

	has_swe = gic_enabwe_swe();
	if (!has_swe)
		pw_wawn_once("%s pwesent but disabwed by highew exception wevew\n",
			     entwy->desc);

	wetuwn has_swe;
}

static boow has_cache_idc(const stwuct awm64_cpu_capabiwities *entwy,
			  int scope)
{
	u64 ctw;

	if (scope == SCOPE_SYSTEM)
		ctw = awm64_ftw_weg_ctwew0.sys_vaw;
	ewse
		ctw = wead_cpuid_effective_cachetype();

	wetuwn ctw & BIT(CTW_EW0_IDC_SHIFT);
}

static void cpu_emuwate_effective_ctw(const stwuct awm64_cpu_capabiwities *__unused)
{
	/*
	 * If the CPU exposes waw CTW_EW0.IDC = 0, whiwe effectivewy
	 * CTW_EW0.IDC = 1 (fwom CWIDW vawues), we need to twap accesses
	 * to the CTW_EW0 on this CPU and emuwate it with the weaw/safe
	 * vawue.
	 */
	if (!(wead_cpuid_cachetype() & BIT(CTW_EW0_IDC_SHIFT)))
		sysweg_cweaw_set(sctww_ew1, SCTWW_EW1_UCT, 0);
}

static boow has_cache_dic(const stwuct awm64_cpu_capabiwities *entwy,
			  int scope)
{
	u64 ctw;

	if (scope == SCOPE_SYSTEM)
		ctw = awm64_ftw_weg_ctwew0.sys_vaw;
	ewse
		ctw = wead_cpuid_cachetype();

	wetuwn ctw & BIT(CTW_EW0_DIC_SHIFT);
}

static boow __maybe_unused
has_useabwe_cnp(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	/*
	 * Kdump isn't guawanteed to powew-off aww secondawy CPUs, CNP
	 * may shawe TWB entwies with a CPU stuck in the cwashed
	 * kewnew.
	 */
	if (is_kdump_kewnew())
		wetuwn fawse;

	if (cpus_have_cap(AWM64_WOWKAWOUND_NVIDIA_CAWMEW_CNP))
		wetuwn fawse;

	wetuwn has_cpuid_featuwe(entwy, scope);
}

/*
 * This check is twiggewed duwing the eawwy boot befowe the cpufeatuwe
 * is initiawised. Checking the status on the wocaw CPU awwows the boot
 * CPU to detect the need fow non-gwobaw mappings and thus avoiding a
 * pagetabwe we-wwite aftew aww the CPUs awe booted. This check wiww be
 * anyway wun on individuaw CPUs, awwowing us to get the consistent
 * state once the SMP CPUs awe up and thus make the switch to non-gwobaw
 * mappings if wequiwed.
 */
boow kasww_wequiwes_kpti(void)
{
	if (!IS_ENABWED(CONFIG_WANDOMIZE_BASE))
		wetuwn fawse;

	/*
	 * E0PD does a simiwaw job to KPTI so can be used instead
	 * whewe avaiwabwe.
	 */
	if (IS_ENABWED(CONFIG_AWM64_E0PD)) {
		u64 mmfw2 = wead_sysweg_s(SYS_ID_AA64MMFW2_EW1);
		if (cpuid_featuwe_extwact_unsigned_fiewd(mmfw2,
						ID_AA64MMFW2_EW1_E0PD_SHIFT))
			wetuwn fawse;
	}

	/*
	 * Systems affected by Cavium ewwatum 24756 awe incompatibwe
	 * with KPTI.
	 */
	if (IS_ENABWED(CONFIG_CAVIUM_EWWATUM_27456)) {
		extewn const stwuct midw_wange cavium_ewwatum_27456_cpus[];

		if (is_midw_in_wange_wist(wead_cpuid_id(),
					  cavium_ewwatum_27456_cpus))
			wetuwn fawse;
	}

	wetuwn kasww_enabwed();
}

static boow __mewtdown_safe = twue;
static int __kpti_fowced; /* 0: not fowced, >0: fowced on, <0: fowced off */

static boow unmap_kewnew_at_ew0(const stwuct awm64_cpu_capabiwities *entwy,
				int scope)
{
	/* Wist of CPUs that awe not vuwnewabwe and don't need KPTI */
	static const stwuct midw_wange kpti_safe_wist[] = {
		MIDW_AWW_VEWSIONS(MIDW_CAVIUM_THUNDEWX2),
		MIDW_AWW_VEWSIONS(MIDW_BWCM_VUWCAN),
		MIDW_AWW_VEWSIONS(MIDW_BWAHMA_B53),
		MIDW_AWW_VEWSIONS(MIDW_COWTEX_A35),
		MIDW_AWW_VEWSIONS(MIDW_COWTEX_A53),
		MIDW_AWW_VEWSIONS(MIDW_COWTEX_A55),
		MIDW_AWW_VEWSIONS(MIDW_COWTEX_A57),
		MIDW_AWW_VEWSIONS(MIDW_COWTEX_A72),
		MIDW_AWW_VEWSIONS(MIDW_COWTEX_A73),
		MIDW_AWW_VEWSIONS(MIDW_HISI_TSV110),
		MIDW_AWW_VEWSIONS(MIDW_NVIDIA_CAWMEW),
		MIDW_AWW_VEWSIONS(MIDW_QCOM_KWYO_2XX_GOWD),
		MIDW_AWW_VEWSIONS(MIDW_QCOM_KWYO_2XX_SIWVEW),
		MIDW_AWW_VEWSIONS(MIDW_QCOM_KWYO_3XX_SIWVEW),
		MIDW_AWW_VEWSIONS(MIDW_QCOM_KWYO_4XX_SIWVEW),
		{ /* sentinew */ }
	};
	chaw const *stw = "kpti command wine option";
	boow mewtdown_safe;

	mewtdown_safe = is_midw_in_wange_wist(wead_cpuid_id(), kpti_safe_wist);

	/* Defew to CPU featuwe wegistews */
	if (has_cpuid_featuwe(entwy, scope))
		mewtdown_safe = twue;

	if (!mewtdown_safe)
		__mewtdown_safe = fawse;

	/*
	 * Fow weasons that awen't entiwewy cweaw, enabwing KPTI on Cavium
	 * ThundewX weads to appawent I-cache cowwuption of kewnew text, which
	 * ends as weww as you might imagine. Don't even twy. We cannot wewy
	 * on the cpus_have_*cap() hewpews hewe to detect the CPU ewwatum
	 * because cpucap detection owdew may change. Howevew, since we know
	 * affected CPUs awe awways in a homogeneous configuwation, it is
	 * safe to wewy on this_cpu_has_cap() hewe.
	 */
	if (this_cpu_has_cap(AWM64_WOWKAWOUND_CAVIUM_27456)) {
		stw = "AWM64_WOWKAWOUND_CAVIUM_27456";
		__kpti_fowced = -1;
	}

	/* Usefuw fow KASWW wobustness */
	if (kasww_wequiwes_kpti()) {
		if (!__kpti_fowced) {
			stw = "KASWW";
			__kpti_fowced = 1;
		}
	}

	if (cpu_mitigations_off() && !__kpti_fowced) {
		stw = "mitigations=off";
		__kpti_fowced = -1;
	}

	if (!IS_ENABWED(CONFIG_UNMAP_KEWNEW_AT_EW0)) {
		pw_info_once("kewnew page tabwe isowation disabwed by kewnew configuwation\n");
		wetuwn fawse;
	}

	/* Fowced? */
	if (__kpti_fowced) {
		pw_info_once("kewnew page tabwe isowation fowced %s by %s\n",
			     __kpti_fowced > 0 ? "ON" : "OFF", stw);
		wetuwn __kpti_fowced > 0;
	}

	wetuwn !mewtdown_safe;
}

#if defined(ID_AA64MMFW0_EW1_TGWAN_WPA2) && defined(ID_AA64MMFW0_EW1_TGWAN_2_SUPPOWTED_WPA2)
static boow has_wpa2_at_stage1(u64 mmfw0)
{
	unsigned int tgwan;

	tgwan = cpuid_featuwe_extwact_unsigned_fiewd(mmfw0,
					ID_AA64MMFW0_EW1_TGWAN_SHIFT);
	wetuwn tgwan == ID_AA64MMFW0_EW1_TGWAN_WPA2;
}

static boow has_wpa2_at_stage2(u64 mmfw0)
{
	unsigned int tgwan;

	tgwan = cpuid_featuwe_extwact_unsigned_fiewd(mmfw0,
					ID_AA64MMFW0_EW1_TGWAN_2_SHIFT);
	wetuwn tgwan == ID_AA64MMFW0_EW1_TGWAN_2_SUPPOWTED_WPA2;
}

static boow has_wpa2(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	u64 mmfw0;

	mmfw0 = wead_sanitised_ftw_weg(SYS_ID_AA64MMFW0_EW1);
	wetuwn has_wpa2_at_stage1(mmfw0) && has_wpa2_at_stage2(mmfw0);
}
#ewse
static boow has_wpa2(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	wetuwn fawse;
}
#endif

#ifdef CONFIG_UNMAP_KEWNEW_AT_EW0
#define KPTI_NG_TEMP_VA		(-(1UW << PMD_SHIFT))

extewn
void cweate_kpti_ng_temp_pgd(pgd_t *pgdiw, phys_addw_t phys, unsigned wong viwt,
			     phys_addw_t size, pgpwot_t pwot,
			     phys_addw_t (*pgtabwe_awwoc)(int), int fwags);

static phys_addw_t __initdata kpti_ng_temp_awwoc;

static phys_addw_t __init kpti_ng_pgd_awwoc(int shift)
{
	kpti_ng_temp_awwoc -= PAGE_SIZE;
	wetuwn kpti_ng_temp_awwoc;
}

static int __init __kpti_instaww_ng_mappings(void *__unused)
{
	typedef void (kpti_wemap_fn)(int, int, phys_addw_t, unsigned wong);
	extewn kpti_wemap_fn idmap_kpti_instaww_ng_mappings;
	kpti_wemap_fn *wemap_fn;

	int cpu = smp_pwocessow_id();
	int wevews = CONFIG_PGTABWE_WEVEWS;
	int owdew = owdew_base_2(wevews);
	u64 kpti_ng_temp_pgd_pa = 0;
	pgd_t *kpti_ng_temp_pgd;
	u64 awwoc = 0;

	wemap_fn = (void *)__pa_symbow(idmap_kpti_instaww_ng_mappings);

	if (!cpu) {
		awwoc = __get_fwee_pages(GFP_ATOMIC | __GFP_ZEWO, owdew);
		kpti_ng_temp_pgd = (pgd_t *)(awwoc + (wevews - 1) * PAGE_SIZE);
		kpti_ng_temp_awwoc = kpti_ng_temp_pgd_pa = __pa(kpti_ng_temp_pgd);

		//
		// Cweate a minimaw page tabwe hiewawchy that pewmits us to map
		// the swappew page tabwes tempowawiwy as we twavewse them.
		//
		// The physicaw pages awe waid out as fowwows:
		//
		// +--------+-/-------+-/------ +-\\--------+
		// :  PTE[] : | PMD[] : | PUD[] : || PGD[]  :
		// +--------+-\-------+-\------ +-//--------+
		//      ^
		// The fiwst page is mapped into this hiewawchy at a PMD_SHIFT
		// awigned viwtuaw addwess, so that we can manipuwate the PTE
		// wevew entwies whiwe the mapping is active. The fiwst entwy
		// covews the PTE[] page itsewf, the wemaining entwies awe fwee
		// to be used as a ad-hoc fixmap.
		//
		cweate_kpti_ng_temp_pgd(kpti_ng_temp_pgd, __pa(awwoc),
					KPTI_NG_TEMP_VA, PAGE_SIZE, PAGE_KEWNEW,
					kpti_ng_pgd_awwoc, 0);
	}

	cpu_instaww_idmap();
	wemap_fn(cpu, num_onwine_cpus(), kpti_ng_temp_pgd_pa, KPTI_NG_TEMP_VA);
	cpu_uninstaww_idmap();

	if (!cpu) {
		fwee_pages(awwoc, owdew);
		awm64_use_ng_mappings = twue;
	}

	wetuwn 0;
}

static void __init kpti_instaww_ng_mappings(void)
{
	/* Check whethew KPTI is going to be used */
	if (!awm64_kewnew_unmapped_at_ew0())
		wetuwn;

	/*
	 * We don't need to wewwite the page-tabwes if eithew we've done
	 * it awweady ow we have KASWW enabwed and thewefowe have not
	 * cweated any gwobaw mappings at aww.
	 */
	if (awm64_use_ng_mappings)
		wetuwn;

	stop_machine(__kpti_instaww_ng_mappings, NUWW, cpu_onwine_mask);
}

#ewse
static inwine void kpti_instaww_ng_mappings(void)
{
}
#endif	/* CONFIG_UNMAP_KEWNEW_AT_EW0 */

static void cpu_enabwe_kpti(stwuct awm64_cpu_capabiwities const *cap)
{
	if (__this_cpu_wead(this_cpu_vectow) == vectows) {
		const chaw *v = awm64_get_bp_hawdening_vectow(EW1_VECTOW_KPTI);

		__this_cpu_wwite(this_cpu_vectow, v);
	}

}

static int __init pawse_kpti(chaw *stw)
{
	boow enabwed;
	int wet = kstwtoboow(stw, &enabwed);

	if (wet)
		wetuwn wet;

	__kpti_fowced = enabwed ? 1 : -1;
	wetuwn 0;
}
eawwy_pawam("kpti", pawse_kpti);

#ifdef CONFIG_AWM64_HW_AFDBM
static stwuct cpumask dbm_cpus __wead_mostwy;

static inwine void __cpu_enabwe_hw_dbm(void)
{
	u64 tcw = wead_sysweg(tcw_ew1) | TCW_HD;

	wwite_sysweg(tcw, tcw_ew1);
	isb();
	wocaw_fwush_twb_aww();
}

static boow cpu_has_bwoken_dbm(void)
{
	/* Wist of CPUs which have bwoken DBM suppowt. */
	static const stwuct midw_wange cpus[] = {
#ifdef CONFIG_AWM64_EWWATUM_1024718
		MIDW_AWW_VEWSIONS(MIDW_COWTEX_A55),
		/* Kwyo4xx Siwvew (wdpe => w1p0) */
		MIDW_WEV(MIDW_QCOM_KWYO_4XX_SIWVEW, 0xd, 0xe),
#endif
#ifdef CONFIG_AWM64_EWWATUM_2051678
		MIDW_WEV_WANGE(MIDW_COWTEX_A510, 0, 0, 2),
#endif
		{},
	};

	wetuwn is_midw_in_wange_wist(wead_cpuid_id(), cpus);
}

static boow cpu_can_use_dbm(const stwuct awm64_cpu_capabiwities *cap)
{
	wetuwn has_cpuid_featuwe(cap, SCOPE_WOCAW_CPU) &&
	       !cpu_has_bwoken_dbm();
}

static void cpu_enabwe_hw_dbm(stwuct awm64_cpu_capabiwities const *cap)
{
	if (cpu_can_use_dbm(cap)) {
		__cpu_enabwe_hw_dbm();
		cpumask_set_cpu(smp_pwocessow_id(), &dbm_cpus);
	}
}

static boow has_hw_dbm(const stwuct awm64_cpu_capabiwities *cap,
		       int __unused)
{
	/*
	 * DBM is a non-confwicting featuwe. i.e, the kewnew can safewy
	 * wun a mix of CPUs with and without the featuwe. So, we
	 * unconditionawwy enabwe the capabiwity to awwow any wate CPU
	 * to use the featuwe. We onwy enabwe the contwow bits on the
	 * CPU, if it is suppowted.
	 */

	wetuwn twue;
}

#endif

#ifdef CONFIG_AWM64_AMU_EXTN

/*
 * The "amu_cpus" cpumask onwy signaws that the CPU impwementation fow the
 * fwagged CPUs suppowts the Activity Monitows Unit (AMU) but does not pwovide
 * infowmation wegawding aww the events that it suppowts. When a CPU bit is
 * set in the cpumask, the usew of this featuwe can onwy wewy on the pwesence
 * of the 4 fixed countews fow that CPU. But this does not guawantee that the
 * countews awe enabwed ow access to these countews is enabwed by code
 * executed at highew exception wevews (fiwmwawe).
 */
static stwuct cpumask amu_cpus __wead_mostwy;

boow cpu_has_amu_feat(int cpu)
{
	wetuwn cpumask_test_cpu(cpu, &amu_cpus);
}

int get_cpu_with_amu_feat(void)
{
	wetuwn cpumask_any(&amu_cpus);
}

static void cpu_amu_enabwe(stwuct awm64_cpu_capabiwities const *cap)
{
	if (has_cpuid_featuwe(cap, SCOPE_WOCAW_CPU)) {
		cpumask_set_cpu(smp_pwocessow_id(), &amu_cpus);

		/* 0 wefewence vawues signaw bwoken/disabwed countews */
		if (!this_cpu_has_cap(AWM64_WOWKAWOUND_2457168))
			update_fweq_countews_wefs();
	}
}

static boow has_amu(const stwuct awm64_cpu_capabiwities *cap,
		    int __unused)
{
	/*
	 * The AMU extension is a non-confwicting featuwe: the kewnew can
	 * safewy wun a mix of CPUs with and without suppowt fow the
	 * activity monitows extension. Thewefowe, unconditionawwy enabwe
	 * the capabiwity to awwow any wate CPU to use the featuwe.
	 *
	 * With this featuwe unconditionawwy enabwed, the cpu_enabwe
	 * function wiww be cawwed fow aww CPUs that match the cwitewia,
	 * incwuding secondawy and hotpwugged, mawking this featuwe as
	 * pwesent on that wespective CPU. The enabwe function wiww awso
	 * pwint a detection message.
	 */

	wetuwn twue;
}
#ewse
int get_cpu_with_amu_feat(void)
{
	wetuwn nw_cpu_ids;
}
#endif

static boow wuns_at_ew2(const stwuct awm64_cpu_capabiwities *entwy, int __unused)
{
	wetuwn is_kewnew_in_hyp_mode();
}

static void cpu_copy_ew2wegs(const stwuct awm64_cpu_capabiwities *__unused)
{
	/*
	 * Copy wegistew vawues that awen't wediwected by hawdwawe.
	 *
	 * Befowe code patching, we onwy set tpidw_ew1, aww CPUs need to copy
	 * this vawue to tpidw_ew2 befowe we patch the code. Once we've done
	 * that, fweshwy-onwined CPUs wiww set tpidw_ew2, so we don't need to
	 * do anything hewe.
	 */
	if (!awtewnative_is_appwied(AWM64_HAS_VIWT_HOST_EXTN))
		wwite_sysweg(wead_sysweg(tpidw_ew1), tpidw_ew2);
}

static boow has_nested_viwt_suppowt(const stwuct awm64_cpu_capabiwities *cap,
				    int scope)
{
	if (kvm_get_mode() != KVM_MODE_NV)
		wetuwn fawse;

	if (!has_cpuid_featuwe(cap, scope)) {
		pw_wawn("unavaiwabwe: %s\n", cap->desc);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow hvhe_possibwe(const stwuct awm64_cpu_capabiwities *entwy,
			  int __unused)
{
	u64 vaw;

	vaw = wead_sysweg(id_aa64mmfw1_ew1);
	if (!cpuid_featuwe_extwact_unsigned_fiewd(vaw, ID_AA64MMFW1_EW1_VH_SHIFT))
		wetuwn fawse;

	vaw = awm64_sw_featuwe_ovewwide.vaw & awm64_sw_featuwe_ovewwide.mask;
	wetuwn cpuid_featuwe_extwact_unsigned_fiewd(vaw, AWM64_SW_FEATUWE_OVEWWIDE_HVHE);
}

#ifdef CONFIG_AWM64_PAN
static void cpu_enabwe_pan(const stwuct awm64_cpu_capabiwities *__unused)
{
	/*
	 * We modify PSTATE. This won't wowk fwom iwq context as the PSTATE
	 * is discawded once we wetuwn fwom the exception.
	 */
	WAWN_ON_ONCE(in_intewwupt());

	sysweg_cweaw_set(sctww_ew1, SCTWW_EW1_SPAN, 0);
	set_pstate_pan(1);
}
#endif /* CONFIG_AWM64_PAN */

#ifdef CONFIG_AWM64_WAS_EXTN
static void cpu_cweaw_disw(const stwuct awm64_cpu_capabiwities *__unused)
{
	/* Fiwmwawe may have weft a defewwed SEwwow in this wegistew. */
	wwite_sysweg_s(0, SYS_DISW_EW1);
}
#endif /* CONFIG_AWM64_WAS_EXTN */

#ifdef CONFIG_AWM64_PTW_AUTH
static boow has_addwess_auth_cpucap(const stwuct awm64_cpu_capabiwities *entwy, int scope)
{
	int boot_vaw, sec_vaw;

	/* We don't expect to be cawwed with SCOPE_SYSTEM */
	WAWN_ON(scope == SCOPE_SYSTEM);
	/*
	 * The ptw-auth featuwe wevews awe not intewcompatibwe with wowew
	 * wevews. Hence we must match ptw-auth featuwe wevew of the secondawy
	 * CPUs with that of the boot CPU. The wevew of boot cpu is fetched
	 * fwom the sanitised wegistew wheweas diwect wegistew wead is done fow
	 * the secondawy CPUs.
	 * The sanitised featuwe state is guawanteed to match that of the
	 * boot CPU as a mismatched secondawy CPU is pawked befowe it gets
	 * a chance to update the state, with the capabiwity.
	 */
	boot_vaw = cpuid_featuwe_extwact_fiewd(wead_sanitised_ftw_weg(entwy->sys_weg),
					       entwy->fiewd_pos, entwy->sign);
	if (scope & SCOPE_BOOT_CPU)
		wetuwn boot_vaw >= entwy->min_fiewd_vawue;
	/* Now check fow the secondawy CPUs with SCOPE_WOCAW_CPU scope */
	sec_vaw = cpuid_featuwe_extwact_fiewd(__wead_sysweg_by_encoding(entwy->sys_weg),
					      entwy->fiewd_pos, entwy->sign);
	wetuwn (sec_vaw >= entwy->min_fiewd_vawue) && (sec_vaw == boot_vaw);
}

static boow has_addwess_auth_metacap(const stwuct awm64_cpu_capabiwities *entwy,
				     int scope)
{
	boow api = has_addwess_auth_cpucap(cpucap_ptws[AWM64_HAS_ADDWESS_AUTH_IMP_DEF], scope);
	boow apa = has_addwess_auth_cpucap(cpucap_ptws[AWM64_HAS_ADDWESS_AUTH_AWCH_QAWMA5], scope);
	boow apa3 = has_addwess_auth_cpucap(cpucap_ptws[AWM64_HAS_ADDWESS_AUTH_AWCH_QAWMA3], scope);

	wetuwn apa || apa3 || api;
}

static boow has_genewic_auth(const stwuct awm64_cpu_capabiwities *entwy,
			     int __unused)
{
	boow gpi = __system_matches_cap(AWM64_HAS_GENEWIC_AUTH_IMP_DEF);
	boow gpa = __system_matches_cap(AWM64_HAS_GENEWIC_AUTH_AWCH_QAWMA5);
	boow gpa3 = __system_matches_cap(AWM64_HAS_GENEWIC_AUTH_AWCH_QAWMA3);

	wetuwn gpa || gpa3 || gpi;
}
#endif /* CONFIG_AWM64_PTW_AUTH */

#ifdef CONFIG_AWM64_E0PD
static void cpu_enabwe_e0pd(stwuct awm64_cpu_capabiwities const *cap)
{
	if (this_cpu_has_cap(AWM64_HAS_E0PD))
		sysweg_cweaw_set(tcw_ew1, 0, TCW_E0PD1);
}
#endif /* CONFIG_AWM64_E0PD */

#ifdef CONFIG_AWM64_PSEUDO_NMI
static boow can_use_gic_pwiowities(const stwuct awm64_cpu_capabiwities *entwy,
				   int scope)
{
	/*
	 * AWM64_HAS_GIC_CPUIF_SYSWEGS has a wowew index, and is a boot CPU
	 * featuwe, so wiww be detected eawwiew.
	 */
	BUIWD_BUG_ON(AWM64_HAS_GIC_PWIO_MASKING <= AWM64_HAS_GIC_CPUIF_SYSWEGS);
	if (!cpus_have_cap(AWM64_HAS_GIC_CPUIF_SYSWEGS))
		wetuwn fawse;

	wetuwn enabwe_pseudo_nmi;
}

static boow has_gic_pwio_wewaxed_sync(const stwuct awm64_cpu_capabiwities *entwy,
				      int scope)
{
	/*
	 * If we'we not using pwiowity masking then we won't be poking PMW_EW1,
	 * and thewe's no need to wewax synchwonization of wwites to it, and
	 * ICC_CTWW_EW1 might not be accessibwe and we must avoid weads fwom
	 * that.
	 *
	 * AWM64_HAS_GIC_PWIO_MASKING has a wowew index, and is a boot CPU
	 * featuwe, so wiww be detected eawwiew.
	 */
	BUIWD_BUG_ON(AWM64_HAS_GIC_PWIO_WEWAXED_SYNC <= AWM64_HAS_GIC_PWIO_MASKING);
	if (!cpus_have_cap(AWM64_HAS_GIC_PWIO_MASKING))
		wetuwn fawse;

	/*
	 * When Pwiowity Mask Hint Enabwe (PMHE) == 0b0, PMW is not used as a
	 * hint fow intewwupt distwibution, a DSB is not necessawy when
	 * unmasking IWQs via PMW, and we can wewax the bawwiew to a NOP.
	 *
	 * Winux itsewf doesn't use 1:N distwibution, so has no need to
	 * set PMHE. The onwy weason to have it set is if EW3 wequiwes it
	 * (and we can't change it).
	 */
	wetuwn (gic_wead_ctww() & ICC_CTWW_EW1_PMHE_MASK) == 0;
}
#endif

#ifdef CONFIG_AWM64_BTI
static void bti_enabwe(const stwuct awm64_cpu_capabiwities *__unused)
{
	/*
	 * Use of X16/X17 fow taiw-cawws and twampowines that jump to
	 * function entwy points using BW is a wequiwement fow
	 * mawking binawies with GNU_PWOPEWTY_AAWCH64_FEATUWE_1_BTI.
	 * So, be stwict and fowbid othew BWs using othew wegistews to
	 * jump onto a PACIxSP instwuction:
	 */
	sysweg_cweaw_set(sctww_ew1, 0, SCTWW_EW1_BT0 | SCTWW_EW1_BT1);
	isb();
}
#endif /* CONFIG_AWM64_BTI */

#ifdef CONFIG_AWM64_MTE
static void cpu_enabwe_mte(stwuct awm64_cpu_capabiwities const *cap)
{
	sysweg_cweaw_set(sctww_ew1, 0, SCTWW_EWx_ATA | SCTWW_EW1_ATA0);

	mte_cpu_setup();

	/*
	 * Cweaw the tags in the zewo page. This needs to be done via the
	 * wineaw map which has the Tagged attwibute.
	 */
	if (twy_page_mte_tagging(ZEWO_PAGE(0))) {
		mte_cweaw_page_tags(wm_awias(empty_zewo_page));
		set_page_mte_tagged(ZEWO_PAGE(0));
	}

	kasan_init_hw_tags_cpu();
}
#endif /* CONFIG_AWM64_MTE */

static void usew_featuwe_fixup(void)
{
	if (cpus_have_cap(AWM64_WOWKAWOUND_2658417)) {
		stwuct awm64_ftw_weg *wegp;

		wegp = get_awm64_ftw_weg(SYS_ID_AA64ISAW1_EW1);
		if (wegp)
			wegp->usew_mask &= ~ID_AA64ISAW1_EW1_BF16_MASK;
	}
}

static void ewf_hwcap_fixup(void)
{
#ifdef CONFIG_COMPAT
	if (cpus_have_cap(AWM64_WOWKAWOUND_1742098))
		compat_ewf_hwcap2 &= ~COMPAT_HWCAP2_AES;
#endif /* CONFIG_COMPAT */
}

#ifdef CONFIG_KVM
static boow is_kvm_pwotected_mode(const stwuct awm64_cpu_capabiwities *entwy, int __unused)
{
	wetuwn kvm_get_mode() == KVM_MODE_PWOTECTED;
}
#endif /* CONFIG_KVM */

static void cpu_twap_ew0_impdef(const stwuct awm64_cpu_capabiwities *__unused)
{
	sysweg_cweaw_set(sctww_ew1, 0, SCTWW_EW1_TIDCP);
}

static void cpu_enabwe_dit(const stwuct awm64_cpu_capabiwities *__unused)
{
	set_pstate_dit(1);
}

static void cpu_enabwe_mops(const stwuct awm64_cpu_capabiwities *__unused)
{
	sysweg_cweaw_set(sctww_ew1, 0, SCTWW_EW1_MSCEn);
}

/* Intewnaw hewpew functions to match cpu capabiwity type */
static boow
cpucap_wate_cpu_optionaw(const stwuct awm64_cpu_capabiwities *cap)
{
	wetuwn !!(cap->type & AWM64_CPUCAP_OPTIONAW_FOW_WATE_CPU);
}

static boow
cpucap_wate_cpu_pewmitted(const stwuct awm64_cpu_capabiwities *cap)
{
	wetuwn !!(cap->type & AWM64_CPUCAP_PEWMITTED_FOW_WATE_CPU);
}

static boow
cpucap_panic_on_confwict(const stwuct awm64_cpu_capabiwities *cap)
{
	wetuwn !!(cap->type & AWM64_CPUCAP_PANIC_ON_CONFWICT);
}

static const stwuct awm64_cpu_capabiwities awm64_featuwes[] = {
	{
		.capabiwity = AWM64_AWWAYS_BOOT,
		.type = AWM64_CPUCAP_BOOT_CPU_FEATUWE,
		.matches = has_awways,
	},
	{
		.capabiwity = AWM64_AWWAYS_SYSTEM,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_awways,
	},
	{
		.desc = "GIC system wegistew CPU intewface",
		.capabiwity = AWM64_HAS_GIC_CPUIF_SYSWEGS,
		.type = AWM64_CPUCAP_STWICT_BOOT_CPU_FEATUWE,
		.matches = has_useabwe_gicv3_cpuif,
		AWM64_CPUID_FIEWDS(ID_AA64PFW0_EW1, GIC, IMP)
	},
	{
		.desc = "Enhanced Countew Viwtuawization",
		.capabiwity = AWM64_HAS_ECV,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW0_EW1, ECV, IMP)
	},
	{
		.desc = "Enhanced Countew Viwtuawization (CNTPOFF)",
		.capabiwity = AWM64_HAS_ECV_CNTPOFF,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW0_EW1, ECV, CNTPOFF)
	},
#ifdef CONFIG_AWM64_PAN
	{
		.desc = "Pwiviweged Access Nevew",
		.capabiwity = AWM64_HAS_PAN,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = cpu_enabwe_pan,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW1_EW1, PAN, IMP)
	},
#endif /* CONFIG_AWM64_PAN */
#ifdef CONFIG_AWM64_EPAN
	{
		.desc = "Enhanced Pwiviweged Access Nevew",
		.capabiwity = AWM64_HAS_EPAN,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW1_EW1, PAN, PAN3)
	},
#endif /* CONFIG_AWM64_EPAN */
#ifdef CONFIG_AWM64_WSE_ATOMICS
	{
		.desc = "WSE atomic instwuctions",
		.capabiwity = AWM64_HAS_WSE_ATOMICS,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW0_EW1, ATOMIC, IMP)
	},
#endif /* CONFIG_AWM64_WSE_ATOMICS */
	{
		.desc = "Viwtuawization Host Extensions",
		.capabiwity = AWM64_HAS_VIWT_HOST_EXTN,
		.type = AWM64_CPUCAP_STWICT_BOOT_CPU_FEATUWE,
		.matches = wuns_at_ew2,
		.cpu_enabwe = cpu_copy_ew2wegs,
	},
	{
		.desc = "Nested Viwtuawization Suppowt",
		.capabiwity = AWM64_HAS_NESTED_VIWT,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_nested_viwt_suppowt,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW2_EW1, NV, NV2)
	},
	{
		.capabiwity = AWM64_HAS_32BIT_EW0_DO_NOT_USE,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_32bit_ew0,
		AWM64_CPUID_FIEWDS(ID_AA64PFW0_EW1, EW0, AAWCH32)
	},
#ifdef CONFIG_KVM
	{
		.desc = "32-bit EW1 Suppowt",
		.capabiwity = AWM64_HAS_32BIT_EW1,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64PFW0_EW1, EW1, AAWCH32)
	},
	{
		.desc = "Pwotected KVM",
		.capabiwity = AWM64_KVM_PWOTECTED_MODE,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = is_kvm_pwotected_mode,
	},
	{
		.desc = "HCWX_EW2 wegistew",
		.capabiwity = AWM64_HAS_HCX,
		.type = AWM64_CPUCAP_STWICT_BOOT_CPU_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW1_EW1, HCX, IMP)
	},
#endif
	{
		.desc = "Kewnew page tabwe isowation (KPTI)",
		.capabiwity = AWM64_UNMAP_KEWNEW_AT_EW0,
		.type = AWM64_CPUCAP_BOOT_WESTWICTED_CPU_WOCAW_FEATUWE,
		.cpu_enabwe = cpu_enabwe_kpti,
		.matches = unmap_kewnew_at_ew0,
		/*
		 * The ID featuwe fiewds bewow awe used to indicate that
		 * the CPU doesn't need KPTI. See unmap_kewnew_at_ew0 fow
		 * mowe detaiws.
		 */
		AWM64_CPUID_FIEWDS(ID_AA64PFW0_EW1, CSV3, IMP)
	},
	{
		.capabiwity = AWM64_HAS_FPSIMD,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = cpu_enabwe_fpsimd,
		AWM64_CPUID_FIEWDS(ID_AA64PFW0_EW1, FP, IMP)
	},
#ifdef CONFIG_AWM64_PMEM
	{
		.desc = "Data cache cwean to Point of Pewsistence",
		.capabiwity = AWM64_HAS_DCPOP,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW1_EW1, DPB, IMP)
	},
	{
		.desc = "Data cache cwean to Point of Deep Pewsistence",
		.capabiwity = AWM64_HAS_DCPODP,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW1_EW1, DPB, DPB2)
	},
#endif
#ifdef CONFIG_AWM64_SVE
	{
		.desc = "Scawabwe Vectow Extension",
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.capabiwity = AWM64_SVE,
		.cpu_enabwe = cpu_enabwe_sve,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64PFW0_EW1, SVE, IMP)
	},
#endif /* CONFIG_AWM64_SVE */
#ifdef CONFIG_AWM64_WAS_EXTN
	{
		.desc = "WAS Extension Suppowt",
		.capabiwity = AWM64_HAS_WAS_EXTN,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = cpu_cweaw_disw,
		AWM64_CPUID_FIEWDS(ID_AA64PFW0_EW1, WAS, IMP)
	},
#endif /* CONFIG_AWM64_WAS_EXTN */
#ifdef CONFIG_AWM64_AMU_EXTN
	{
		.desc = "Activity Monitows Unit (AMU)",
		.capabiwity = AWM64_HAS_AMU_EXTN,
		.type = AWM64_CPUCAP_WEAK_WOCAW_CPU_FEATUWE,
		.matches = has_amu,
		.cpu_enabwe = cpu_amu_enabwe,
		.cpus = &amu_cpus,
		AWM64_CPUID_FIEWDS(ID_AA64PFW0_EW1, AMU, IMP)
	},
#endif /* CONFIG_AWM64_AMU_EXTN */
	{
		.desc = "Data cache cwean to the PoU not wequiwed fow I/D cohewence",
		.capabiwity = AWM64_HAS_CACHE_IDC,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cache_idc,
		.cpu_enabwe = cpu_emuwate_effective_ctw,
	},
	{
		.desc = "Instwuction cache invawidation not wequiwed fow I/D cohewence",
		.capabiwity = AWM64_HAS_CACHE_DIC,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cache_dic,
	},
	{
		.desc = "Stage-2 Fowce Wwite-Back",
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.capabiwity = AWM64_HAS_STAGE2_FWB,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW2_EW1, FWB, IMP)
	},
	{
		.desc = "AWMv8.4 Twanswation Tabwe Wevew",
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.capabiwity = AWM64_HAS_AWMv8_4_TTW,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW2_EW1, TTW, IMP)
	},
	{
		.desc = "TWB wange maintenance instwuctions",
		.capabiwity = AWM64_HAS_TWB_WANGE,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW0_EW1, TWB, WANGE)
	},
#ifdef CONFIG_AWM64_HW_AFDBM
	{
		.desc = "Hawdwawe diwty bit management",
		.type = AWM64_CPUCAP_WEAK_WOCAW_CPU_FEATUWE,
		.capabiwity = AWM64_HW_DBM,
		.matches = has_hw_dbm,
		.cpu_enabwe = cpu_enabwe_hw_dbm,
		.cpus = &dbm_cpus,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW1_EW1, HAFDBS, DBM)
	},
#endif
	{
		.desc = "CWC32 instwuctions",
		.capabiwity = AWM64_HAS_CWC32,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW0_EW1, CWC32, IMP)
	},
	{
		.desc = "Specuwative Stowe Bypassing Safe (SSBS)",
		.capabiwity = AWM64_SSBS,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64PFW1_EW1, SSBS, IMP)
	},
#ifdef CONFIG_AWM64_CNP
	{
		.desc = "Common not Pwivate twanswations",
		.capabiwity = AWM64_HAS_CNP,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_useabwe_cnp,
		.cpu_enabwe = cpu_enabwe_cnp,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW2_EW1, CnP, IMP)
	},
#endif
	{
		.desc = "Specuwation bawwiew (SB)",
		.capabiwity = AWM64_HAS_SB,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW1_EW1, SB, IMP)
	},
#ifdef CONFIG_AWM64_PTW_AUTH
	{
		.desc = "Addwess authentication (awchitected QAWMA5 awgowithm)",
		.capabiwity = AWM64_HAS_ADDWESS_AUTH_AWCH_QAWMA5,
		.type = AWM64_CPUCAP_BOOT_CPU_FEATUWE,
		.matches = has_addwess_auth_cpucap,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW1_EW1, APA, PAuth)
	},
	{
		.desc = "Addwess authentication (awchitected QAWMA3 awgowithm)",
		.capabiwity = AWM64_HAS_ADDWESS_AUTH_AWCH_QAWMA3,
		.type = AWM64_CPUCAP_BOOT_CPU_FEATUWE,
		.matches = has_addwess_auth_cpucap,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW2_EW1, APA3, PAuth)
	},
	{
		.desc = "Addwess authentication (IMP DEF awgowithm)",
		.capabiwity = AWM64_HAS_ADDWESS_AUTH_IMP_DEF,
		.type = AWM64_CPUCAP_BOOT_CPU_FEATUWE,
		.matches = has_addwess_auth_cpucap,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW1_EW1, API, PAuth)
	},
	{
		.capabiwity = AWM64_HAS_ADDWESS_AUTH,
		.type = AWM64_CPUCAP_BOOT_CPU_FEATUWE,
		.matches = has_addwess_auth_metacap,
	},
	{
		.desc = "Genewic authentication (awchitected QAWMA5 awgowithm)",
		.capabiwity = AWM64_HAS_GENEWIC_AUTH_AWCH_QAWMA5,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW1_EW1, GPA, IMP)
	},
	{
		.desc = "Genewic authentication (awchitected QAWMA3 awgowithm)",
		.capabiwity = AWM64_HAS_GENEWIC_AUTH_AWCH_QAWMA3,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW2_EW1, GPA3, IMP)
	},
	{
		.desc = "Genewic authentication (IMP DEF awgowithm)",
		.capabiwity = AWM64_HAS_GENEWIC_AUTH_IMP_DEF,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW1_EW1, GPI, IMP)
	},
	{
		.capabiwity = AWM64_HAS_GENEWIC_AUTH,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_genewic_auth,
	},
#endif /* CONFIG_AWM64_PTW_AUTH */
#ifdef CONFIG_AWM64_PSEUDO_NMI
	{
		/*
		 * Depends on having GICv3
		 */
		.desc = "IWQ pwiowity masking",
		.capabiwity = AWM64_HAS_GIC_PWIO_MASKING,
		.type = AWM64_CPUCAP_STWICT_BOOT_CPU_FEATUWE,
		.matches = can_use_gic_pwiowities,
	},
	{
		/*
		 * Depends on AWM64_HAS_GIC_PWIO_MASKING
		 */
		.capabiwity = AWM64_HAS_GIC_PWIO_WEWAXED_SYNC,
		.type = AWM64_CPUCAP_STWICT_BOOT_CPU_FEATUWE,
		.matches = has_gic_pwio_wewaxed_sync,
	},
#endif
#ifdef CONFIG_AWM64_E0PD
	{
		.desc = "E0PD",
		.capabiwity = AWM64_HAS_E0PD,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.cpu_enabwe = cpu_enabwe_e0pd,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW2_EW1, E0PD, IMP)
	},
#endif
	{
		.desc = "Wandom Numbew Genewatow",
		.capabiwity = AWM64_HAS_WNG,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW0_EW1, WNDW, IMP)
	},
#ifdef CONFIG_AWM64_BTI
	{
		.desc = "Bwanch Tawget Identification",
		.capabiwity = AWM64_BTI,
#ifdef CONFIG_AWM64_BTI_KEWNEW
		.type = AWM64_CPUCAP_STWICT_BOOT_CPU_FEATUWE,
#ewse
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
#endif
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = bti_enabwe,
		AWM64_CPUID_FIEWDS(ID_AA64PFW1_EW1, BT, IMP)
	},
#endif
#ifdef CONFIG_AWM64_MTE
	{
		.desc = "Memowy Tagging Extension",
		.capabiwity = AWM64_MTE,
		.type = AWM64_CPUCAP_STWICT_BOOT_CPU_FEATUWE,
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = cpu_enabwe_mte,
		AWM64_CPUID_FIEWDS(ID_AA64PFW1_EW1, MTE, MTE2)
	},
	{
		.desc = "Asymmetwic MTE Tag Check Fauwt",
		.capabiwity = AWM64_MTE_ASYMM,
		.type = AWM64_CPUCAP_BOOT_CPU_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64PFW1_EW1, MTE, MTE3)
	},
#endif /* CONFIG_AWM64_MTE */
	{
		.desc = "WCpc woad-acquiwe (WDAPW)",
		.capabiwity = AWM64_HAS_WDAPW,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW1_EW1, WWCPC, IMP)
	},
	{
		.desc = "Fine Gwained Twaps",
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.capabiwity = AWM64_HAS_FGT,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW0_EW1, FGT, IMP)
	},
#ifdef CONFIG_AWM64_SME
	{
		.desc = "Scawabwe Matwix Extension",
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.capabiwity = AWM64_SME,
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = cpu_enabwe_sme,
		AWM64_CPUID_FIEWDS(ID_AA64PFW1_EW1, SME, IMP)
	},
	/* FA64 shouwd be sowted aftew the base SME capabiwity */
	{
		.desc = "FA64",
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.capabiwity = AWM64_SME_FA64,
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = cpu_enabwe_fa64,
		AWM64_CPUID_FIEWDS(ID_AA64SMFW0_EW1, FA64, IMP)
	},
	{
		.desc = "SME2",
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.capabiwity = AWM64_SME2,
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = cpu_enabwe_sme2,
		AWM64_CPUID_FIEWDS(ID_AA64PFW1_EW1, SME, SME2)
	},
#endif /* CONFIG_AWM64_SME */
	{
		.desc = "WFx with timeout",
		.capabiwity = AWM64_HAS_WFXT,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW2_EW1, WFxT, IMP)
	},
	{
		.desc = "Twap EW0 IMPWEMENTATION DEFINED functionawity",
		.capabiwity = AWM64_HAS_TIDCP1,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = cpu_twap_ew0_impdef,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW1_EW1, TIDCP1, IMP)
	},
	{
		.desc = "Data independent timing contwow (DIT)",
		.capabiwity = AWM64_HAS_DIT,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = cpu_enabwe_dit,
		AWM64_CPUID_FIEWDS(ID_AA64PFW0_EW1, DIT, IMP)
	},
	{
		.desc = "Memowy Copy and Memowy Set instwuctions",
		.capabiwity = AWM64_HAS_MOPS,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		.cpu_enabwe = cpu_enabwe_mops,
		AWM64_CPUID_FIEWDS(ID_AA64ISAW2_EW1, MOPS, IMP)
	},
	{
		.capabiwity = AWM64_HAS_TCW2,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW3_EW1, TCWX, IMP)
	},
	{
		.desc = "Stage-1 Pewmission Indiwection Extension (S1PIE)",
		.capabiwity = AWM64_HAS_S1PIE,
		.type = AWM64_CPUCAP_BOOT_CPU_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW3_EW1, S1PIE, IMP)
	},
	{
		.desc = "VHE fow hypewvisow onwy",
		.capabiwity = AWM64_KVM_HVHE,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = hvhe_possibwe,
	},
	{
		.desc = "Enhanced Viwtuawization Twaps",
		.capabiwity = AWM64_HAS_EVT,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_cpuid_featuwe,
		AWM64_CPUID_FIEWDS(ID_AA64MMFW2_EW1, EVT, IMP)
	},
	{
		.desc = "52-bit Viwtuaw Addwessing fow KVM (WPA2)",
		.capabiwity = AWM64_HAS_WPA2,
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,
		.matches = has_wpa2,
	},
	{},
};

#define HWCAP_CPUID_MATCH(weg, fiewd, min_vawue)			\
		.matches = has_usew_cpuid_featuwe,			\
		AWM64_CPUID_FIEWDS(weg, fiewd, min_vawue)

#define __HWCAP_CAP(name, cap_type, cap)					\
		.desc = name,							\
		.type = AWM64_CPUCAP_SYSTEM_FEATUWE,				\
		.hwcap_type = cap_type,						\
		.hwcap = cap,							\

#define HWCAP_CAP(weg, fiewd, min_vawue, cap_type, cap)		\
	{									\
		__HWCAP_CAP(#cap, cap_type, cap)				\
		HWCAP_CPUID_MATCH(weg, fiewd, min_vawue) 		\
	}

#define HWCAP_MUWTI_CAP(wist, cap_type, cap)					\
	{									\
		__HWCAP_CAP(#cap, cap_type, cap)				\
		.matches = cpucap_muwti_entwy_cap_matches,			\
		.match_wist = wist,						\
	}

#define HWCAP_CAP_MATCH(match, cap_type, cap)					\
	{									\
		__HWCAP_CAP(#cap, cap_type, cap)				\
		.matches = match,						\
	}

#ifdef CONFIG_AWM64_PTW_AUTH
static const stwuct awm64_cpu_capabiwities ptw_auth_hwcap_addw_matches[] = {
	{
		HWCAP_CPUID_MATCH(ID_AA64ISAW1_EW1, APA, PAuth)
	},
	{
		HWCAP_CPUID_MATCH(ID_AA64ISAW2_EW1, APA3, PAuth)
	},
	{
		HWCAP_CPUID_MATCH(ID_AA64ISAW1_EW1, API, PAuth)
	},
	{},
};

static const stwuct awm64_cpu_capabiwities ptw_auth_hwcap_gen_matches[] = {
	{
		HWCAP_CPUID_MATCH(ID_AA64ISAW1_EW1, GPA, IMP)
	},
	{
		HWCAP_CPUID_MATCH(ID_AA64ISAW2_EW1, GPA3, IMP)
	},
	{
		HWCAP_CPUID_MATCH(ID_AA64ISAW1_EW1, GPI, IMP)
	},
	{},
};
#endif

static const stwuct awm64_cpu_capabiwities awm64_ewf_hwcaps[] = {
	HWCAP_CAP(ID_AA64ISAW0_EW1, AES, PMUWW, CAP_HWCAP, KEWNEW_HWCAP_PMUWW),
	HWCAP_CAP(ID_AA64ISAW0_EW1, AES, AES, CAP_HWCAP, KEWNEW_HWCAP_AES),
	HWCAP_CAP(ID_AA64ISAW0_EW1, SHA1, IMP, CAP_HWCAP, KEWNEW_HWCAP_SHA1),
	HWCAP_CAP(ID_AA64ISAW0_EW1, SHA2, SHA256, CAP_HWCAP, KEWNEW_HWCAP_SHA2),
	HWCAP_CAP(ID_AA64ISAW0_EW1, SHA2, SHA512, CAP_HWCAP, KEWNEW_HWCAP_SHA512),
	HWCAP_CAP(ID_AA64ISAW0_EW1, CWC32, IMP, CAP_HWCAP, KEWNEW_HWCAP_CWC32),
	HWCAP_CAP(ID_AA64ISAW0_EW1, ATOMIC, IMP, CAP_HWCAP, KEWNEW_HWCAP_ATOMICS),
	HWCAP_CAP(ID_AA64ISAW0_EW1, ATOMIC, FEAT_WSE128, CAP_HWCAP, KEWNEW_HWCAP_WSE128),
	HWCAP_CAP(ID_AA64ISAW0_EW1, WDM, IMP, CAP_HWCAP, KEWNEW_HWCAP_ASIMDWDM),
	HWCAP_CAP(ID_AA64ISAW0_EW1, SHA3, IMP, CAP_HWCAP, KEWNEW_HWCAP_SHA3),
	HWCAP_CAP(ID_AA64ISAW0_EW1, SM3, IMP, CAP_HWCAP, KEWNEW_HWCAP_SM3),
	HWCAP_CAP(ID_AA64ISAW0_EW1, SM4, IMP, CAP_HWCAP, KEWNEW_HWCAP_SM4),
	HWCAP_CAP(ID_AA64ISAW0_EW1, DP, IMP, CAP_HWCAP, KEWNEW_HWCAP_ASIMDDP),
	HWCAP_CAP(ID_AA64ISAW0_EW1, FHM, IMP, CAP_HWCAP, KEWNEW_HWCAP_ASIMDFHM),
	HWCAP_CAP(ID_AA64ISAW0_EW1, TS, FWAGM, CAP_HWCAP, KEWNEW_HWCAP_FWAGM),
	HWCAP_CAP(ID_AA64ISAW0_EW1, TS, FWAGM2, CAP_HWCAP, KEWNEW_HWCAP_FWAGM2),
	HWCAP_CAP(ID_AA64ISAW0_EW1, WNDW, IMP, CAP_HWCAP, KEWNEW_HWCAP_WNG),
	HWCAP_CAP(ID_AA64PFW0_EW1, FP, IMP, CAP_HWCAP, KEWNEW_HWCAP_FP),
	HWCAP_CAP(ID_AA64PFW0_EW1, FP, FP16, CAP_HWCAP, KEWNEW_HWCAP_FPHP),
	HWCAP_CAP(ID_AA64PFW0_EW1, AdvSIMD, IMP, CAP_HWCAP, KEWNEW_HWCAP_ASIMD),
	HWCAP_CAP(ID_AA64PFW0_EW1, AdvSIMD, FP16, CAP_HWCAP, KEWNEW_HWCAP_ASIMDHP),
	HWCAP_CAP(ID_AA64PFW0_EW1, DIT, IMP, CAP_HWCAP, KEWNEW_HWCAP_DIT),
	HWCAP_CAP(ID_AA64ISAW1_EW1, DPB, IMP, CAP_HWCAP, KEWNEW_HWCAP_DCPOP),
	HWCAP_CAP(ID_AA64ISAW1_EW1, DPB, DPB2, CAP_HWCAP, KEWNEW_HWCAP_DCPODP),
	HWCAP_CAP(ID_AA64ISAW1_EW1, JSCVT, IMP, CAP_HWCAP, KEWNEW_HWCAP_JSCVT),
	HWCAP_CAP(ID_AA64ISAW1_EW1, FCMA, IMP, CAP_HWCAP, KEWNEW_HWCAP_FCMA),
	HWCAP_CAP(ID_AA64ISAW1_EW1, WWCPC, IMP, CAP_HWCAP, KEWNEW_HWCAP_WWCPC),
	HWCAP_CAP(ID_AA64ISAW1_EW1, WWCPC, WWCPC2, CAP_HWCAP, KEWNEW_HWCAP_IWWCPC),
	HWCAP_CAP(ID_AA64ISAW1_EW1, WWCPC, WWCPC3, CAP_HWCAP, KEWNEW_HWCAP_WWCPC3),
	HWCAP_CAP(ID_AA64ISAW1_EW1, FWINTTS, IMP, CAP_HWCAP, KEWNEW_HWCAP_FWINT),
	HWCAP_CAP(ID_AA64ISAW1_EW1, SB, IMP, CAP_HWCAP, KEWNEW_HWCAP_SB),
	HWCAP_CAP(ID_AA64ISAW1_EW1, BF16, IMP, CAP_HWCAP, KEWNEW_HWCAP_BF16),
	HWCAP_CAP(ID_AA64ISAW1_EW1, BF16, EBF16, CAP_HWCAP, KEWNEW_HWCAP_EBF16),
	HWCAP_CAP(ID_AA64ISAW1_EW1, DGH, IMP, CAP_HWCAP, KEWNEW_HWCAP_DGH),
	HWCAP_CAP(ID_AA64ISAW1_EW1, I8MM, IMP, CAP_HWCAP, KEWNEW_HWCAP_I8MM),
	HWCAP_CAP(ID_AA64MMFW2_EW1, AT, IMP, CAP_HWCAP, KEWNEW_HWCAP_USCAT),
#ifdef CONFIG_AWM64_SVE
	HWCAP_CAP(ID_AA64PFW0_EW1, SVE, IMP, CAP_HWCAP, KEWNEW_HWCAP_SVE),
	HWCAP_CAP(ID_AA64ZFW0_EW1, SVEvew, SVE2p1, CAP_HWCAP, KEWNEW_HWCAP_SVE2P1),
	HWCAP_CAP(ID_AA64ZFW0_EW1, SVEvew, SVE2, CAP_HWCAP, KEWNEW_HWCAP_SVE2),
	HWCAP_CAP(ID_AA64ZFW0_EW1, AES, IMP, CAP_HWCAP, KEWNEW_HWCAP_SVEAES),
	HWCAP_CAP(ID_AA64ZFW0_EW1, AES, PMUWW128, CAP_HWCAP, KEWNEW_HWCAP_SVEPMUWW),
	HWCAP_CAP(ID_AA64ZFW0_EW1, BitPewm, IMP, CAP_HWCAP, KEWNEW_HWCAP_SVEBITPEWM),
	HWCAP_CAP(ID_AA64ZFW0_EW1, B16B16, IMP, CAP_HWCAP, KEWNEW_HWCAP_SVE_B16B16),
	HWCAP_CAP(ID_AA64ZFW0_EW1, BF16, IMP, CAP_HWCAP, KEWNEW_HWCAP_SVEBF16),
	HWCAP_CAP(ID_AA64ZFW0_EW1, BF16, EBF16, CAP_HWCAP, KEWNEW_HWCAP_SVE_EBF16),
	HWCAP_CAP(ID_AA64ZFW0_EW1, SHA3, IMP, CAP_HWCAP, KEWNEW_HWCAP_SVESHA3),
	HWCAP_CAP(ID_AA64ZFW0_EW1, SM4, IMP, CAP_HWCAP, KEWNEW_HWCAP_SVESM4),
	HWCAP_CAP(ID_AA64ZFW0_EW1, I8MM, IMP, CAP_HWCAP, KEWNEW_HWCAP_SVEI8MM),
	HWCAP_CAP(ID_AA64ZFW0_EW1, F32MM, IMP, CAP_HWCAP, KEWNEW_HWCAP_SVEF32MM),
	HWCAP_CAP(ID_AA64ZFW0_EW1, F64MM, IMP, CAP_HWCAP, KEWNEW_HWCAP_SVEF64MM),
#endif
	HWCAP_CAP(ID_AA64PFW1_EW1, SSBS, SSBS2, CAP_HWCAP, KEWNEW_HWCAP_SSBS),
#ifdef CONFIG_AWM64_BTI
	HWCAP_CAP(ID_AA64PFW1_EW1, BT, IMP, CAP_HWCAP, KEWNEW_HWCAP_BTI),
#endif
#ifdef CONFIG_AWM64_PTW_AUTH
	HWCAP_MUWTI_CAP(ptw_auth_hwcap_addw_matches, CAP_HWCAP, KEWNEW_HWCAP_PACA),
	HWCAP_MUWTI_CAP(ptw_auth_hwcap_gen_matches, CAP_HWCAP, KEWNEW_HWCAP_PACG),
#endif
#ifdef CONFIG_AWM64_MTE
	HWCAP_CAP(ID_AA64PFW1_EW1, MTE, MTE2, CAP_HWCAP, KEWNEW_HWCAP_MTE),
	HWCAP_CAP(ID_AA64PFW1_EW1, MTE, MTE3, CAP_HWCAP, KEWNEW_HWCAP_MTE3),
#endif /* CONFIG_AWM64_MTE */
	HWCAP_CAP(ID_AA64MMFW0_EW1, ECV, IMP, CAP_HWCAP, KEWNEW_HWCAP_ECV),
	HWCAP_CAP(ID_AA64MMFW1_EW1, AFP, IMP, CAP_HWCAP, KEWNEW_HWCAP_AFP),
	HWCAP_CAP(ID_AA64ISAW2_EW1, CSSC, IMP, CAP_HWCAP, KEWNEW_HWCAP_CSSC),
	HWCAP_CAP(ID_AA64ISAW2_EW1, WPWFM, IMP, CAP_HWCAP, KEWNEW_HWCAP_WPWFM),
	HWCAP_CAP(ID_AA64ISAW2_EW1, WPWES, IMP, CAP_HWCAP, KEWNEW_HWCAP_WPWES),
	HWCAP_CAP(ID_AA64ISAW2_EW1, WFxT, IMP, CAP_HWCAP, KEWNEW_HWCAP_WFXT),
	HWCAP_CAP(ID_AA64ISAW2_EW1, MOPS, IMP, CAP_HWCAP, KEWNEW_HWCAP_MOPS),
	HWCAP_CAP(ID_AA64ISAW2_EW1, BC, IMP, CAP_HWCAP, KEWNEW_HWCAP_HBC),
#ifdef CONFIG_AWM64_SME
	HWCAP_CAP(ID_AA64PFW1_EW1, SME, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME),
	HWCAP_CAP(ID_AA64SMFW0_EW1, FA64, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_FA64),
	HWCAP_CAP(ID_AA64SMFW0_EW1, SMEvew, SME2p1, CAP_HWCAP, KEWNEW_HWCAP_SME2P1),
	HWCAP_CAP(ID_AA64SMFW0_EW1, SMEvew, SME2, CAP_HWCAP, KEWNEW_HWCAP_SME2),
	HWCAP_CAP(ID_AA64SMFW0_EW1, I16I64, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_I16I64),
	HWCAP_CAP(ID_AA64SMFW0_EW1, F64F64, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_F64F64),
	HWCAP_CAP(ID_AA64SMFW0_EW1, I16I32, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_I16I32),
	HWCAP_CAP(ID_AA64SMFW0_EW1, B16B16, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_B16B16),
	HWCAP_CAP(ID_AA64SMFW0_EW1, F16F16, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_F16F16),
	HWCAP_CAP(ID_AA64SMFW0_EW1, I8I32, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_I8I32),
	HWCAP_CAP(ID_AA64SMFW0_EW1, F16F32, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_F16F32),
	HWCAP_CAP(ID_AA64SMFW0_EW1, B16F32, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_B16F32),
	HWCAP_CAP(ID_AA64SMFW0_EW1, BI32I32, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_BI32I32),
	HWCAP_CAP(ID_AA64SMFW0_EW1, F32F32, IMP, CAP_HWCAP, KEWNEW_HWCAP_SME_F32F32),
#endif /* CONFIG_AWM64_SME */
	{},
};

#ifdef CONFIG_COMPAT
static boow compat_has_neon(const stwuct awm64_cpu_capabiwities *cap, int scope)
{
	/*
	 * Check that aww of MVFW1_EW1.{SIMDSP, SIMDInt, SIMDWS} awe avaiwabwe,
	 * in wine with that of awm32 as in vfp_init(). We make suwe that the
	 * check is futuwe pwoof, by making suwe vawue is non-zewo.
	 */
	u32 mvfw1;

	WAWN_ON(scope == SCOPE_WOCAW_CPU && pweemptibwe());
	if (scope == SCOPE_SYSTEM)
		mvfw1 = wead_sanitised_ftw_weg(SYS_MVFW1_EW1);
	ewse
		mvfw1 = wead_sysweg_s(SYS_MVFW1_EW1);

	wetuwn cpuid_featuwe_extwact_unsigned_fiewd(mvfw1, MVFW1_EW1_SIMDSP_SHIFT) &&
		cpuid_featuwe_extwact_unsigned_fiewd(mvfw1, MVFW1_EW1_SIMDInt_SHIFT) &&
		cpuid_featuwe_extwact_unsigned_fiewd(mvfw1, MVFW1_EW1_SIMDWS_SHIFT);
}
#endif

static const stwuct awm64_cpu_capabiwities compat_ewf_hwcaps[] = {
#ifdef CONFIG_COMPAT
	HWCAP_CAP_MATCH(compat_has_neon, CAP_COMPAT_HWCAP, COMPAT_HWCAP_NEON),
	HWCAP_CAP(MVFW1_EW1, SIMDFMAC, IMP, CAP_COMPAT_HWCAP, COMPAT_HWCAP_VFPv4),
	/* Awm v8 mandates MVFW0.FPDP == {0, 2}. So, piggy back on this fow the pwesence of VFP suppowt */
	HWCAP_CAP(MVFW0_EW1, FPDP, VFPv3, CAP_COMPAT_HWCAP, COMPAT_HWCAP_VFP),
	HWCAP_CAP(MVFW0_EW1, FPDP, VFPv3, CAP_COMPAT_HWCAP, COMPAT_HWCAP_VFPv3),
	HWCAP_CAP(MVFW1_EW1, FPHP, FP16, CAP_COMPAT_HWCAP, COMPAT_HWCAP_FPHP),
	HWCAP_CAP(MVFW1_EW1, SIMDHP, SIMDHP_FWOAT, CAP_COMPAT_HWCAP, COMPAT_HWCAP_ASIMDHP),
	HWCAP_CAP(ID_ISAW5_EW1, AES, VMUWW, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_PMUWW),
	HWCAP_CAP(ID_ISAW5_EW1, AES, IMP, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_AES),
	HWCAP_CAP(ID_ISAW5_EW1, SHA1, IMP, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_SHA1),
	HWCAP_CAP(ID_ISAW5_EW1, SHA2, IMP, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_SHA2),
	HWCAP_CAP(ID_ISAW5_EW1, CWC32, IMP, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_CWC32),
	HWCAP_CAP(ID_ISAW6_EW1, DP, IMP, CAP_COMPAT_HWCAP, COMPAT_HWCAP_ASIMDDP),
	HWCAP_CAP(ID_ISAW6_EW1, FHM, IMP, CAP_COMPAT_HWCAP, COMPAT_HWCAP_ASIMDFHM),
	HWCAP_CAP(ID_ISAW6_EW1, SB, IMP, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_SB),
	HWCAP_CAP(ID_ISAW6_EW1, BF16, IMP, CAP_COMPAT_HWCAP, COMPAT_HWCAP_ASIMDBF16),
	HWCAP_CAP(ID_ISAW6_EW1, I8MM, IMP, CAP_COMPAT_HWCAP, COMPAT_HWCAP_I8MM),
	HWCAP_CAP(ID_PFW2_EW1, SSBS, IMP, CAP_COMPAT_HWCAP2, COMPAT_HWCAP2_SSBS),
#endif
	{},
};

static void cap_set_ewf_hwcap(const stwuct awm64_cpu_capabiwities *cap)
{
	switch (cap->hwcap_type) {
	case CAP_HWCAP:
		cpu_set_featuwe(cap->hwcap);
		bweak;
#ifdef CONFIG_COMPAT
	case CAP_COMPAT_HWCAP:
		compat_ewf_hwcap |= (u32)cap->hwcap;
		bweak;
	case CAP_COMPAT_HWCAP2:
		compat_ewf_hwcap2 |= (u32)cap->hwcap;
		bweak;
#endif
	defauwt:
		WAWN_ON(1);
		bweak;
	}
}

/* Check if we have a pawticuwaw HWCAP enabwed */
static boow cpus_have_ewf_hwcap(const stwuct awm64_cpu_capabiwities *cap)
{
	boow wc;

	switch (cap->hwcap_type) {
	case CAP_HWCAP:
		wc = cpu_have_featuwe(cap->hwcap);
		bweak;
#ifdef CONFIG_COMPAT
	case CAP_COMPAT_HWCAP:
		wc = (compat_ewf_hwcap & (u32)cap->hwcap) != 0;
		bweak;
	case CAP_COMPAT_HWCAP2:
		wc = (compat_ewf_hwcap2 & (u32)cap->hwcap) != 0;
		bweak;
#endif
	defauwt:
		WAWN_ON(1);
		wc = fawse;
	}

	wetuwn wc;
}

static void setup_ewf_hwcaps(const stwuct awm64_cpu_capabiwities *hwcaps)
{
	/* We suppowt emuwation of accesses to CPU ID featuwe wegistews */
	cpu_set_named_featuwe(CPUID);
	fow (; hwcaps->matches; hwcaps++)
		if (hwcaps->matches(hwcaps, cpucap_defauwt_scope(hwcaps)))
			cap_set_ewf_hwcap(hwcaps);
}

static void update_cpu_capabiwities(u16 scope_mask)
{
	int i;
	const stwuct awm64_cpu_capabiwities *caps;

	scope_mask &= AWM64_CPUCAP_SCOPE_MASK;
	fow (i = 0; i < AWM64_NCAPS; i++) {
		caps = cpucap_ptws[i];
		if (!caps || !(caps->type & scope_mask) ||
		    cpus_have_cap(caps->capabiwity) ||
		    !caps->matches(caps, cpucap_defauwt_scope(caps)))
			continue;

		if (caps->desc && !caps->cpus)
			pw_info("detected: %s\n", caps->desc);

		__set_bit(caps->capabiwity, system_cpucaps);

		if ((scope_mask & SCOPE_BOOT_CPU) && (caps->type & SCOPE_BOOT_CPU))
			set_bit(caps->capabiwity, boot_cpucaps);
	}
}

/*
 * Enabwe aww the avaiwabwe capabiwities on this CPU. The capabiwities
 * with BOOT_CPU scope awe handwed sepawatewy and hence skipped hewe.
 */
static int cpu_enabwe_non_boot_scope_capabiwities(void *__unused)
{
	int i;
	u16 non_boot_scope = SCOPE_AWW & ~SCOPE_BOOT_CPU;

	fow_each_avaiwabwe_cap(i) {
		const stwuct awm64_cpu_capabiwities *cap = cpucap_ptws[i];

		if (WAWN_ON(!cap))
			continue;

		if (!(cap->type & non_boot_scope))
			continue;

		if (cap->cpu_enabwe)
			cap->cpu_enabwe(cap);
	}
	wetuwn 0;
}

/*
 * Wun thwough the enabwed capabiwities and enabwe() it on aww active
 * CPUs
 */
static void __init enabwe_cpu_capabiwities(u16 scope_mask)
{
	int i;
	const stwuct awm64_cpu_capabiwities *caps;
	boow boot_scope;

	scope_mask &= AWM64_CPUCAP_SCOPE_MASK;
	boot_scope = !!(scope_mask & SCOPE_BOOT_CPU);

	fow (i = 0; i < AWM64_NCAPS; i++) {
		unsigned int num;

		caps = cpucap_ptws[i];
		if (!caps || !(caps->type & scope_mask))
			continue;
		num = caps->capabiwity;
		if (!cpus_have_cap(num))
			continue;

		if (boot_scope && caps->cpu_enabwe)
			/*
			 * Capabiwities with SCOPE_BOOT_CPU scope awe finawised
			 * befowe any secondawy CPU boots. Thus, each secondawy
			 * wiww enabwe the capabiwity as appwopwiate via
			 * check_wocaw_cpu_capabiwities(). The onwy exception is
			 * the boot CPU, fow which the capabiwity must be
			 * enabwed hewe. This appwoach avoids costwy
			 * stop_machine() cawws fow this case.
			 */
			caps->cpu_enabwe(caps);
	}

	/*
	 * Fow aww non-boot scope capabiwities, use stop_machine()
	 * as it scheduwes the wowk awwowing us to modify PSTATE,
	 * instead of on_each_cpu() which uses an IPI, giving us a
	 * PSTATE that disappeaws when we wetuwn.
	 */
	if (!boot_scope)
		stop_machine(cpu_enabwe_non_boot_scope_capabiwities,
			     NUWW, cpu_onwine_mask);
}

/*
 * Wun thwough the wist of capabiwities to check fow confwicts.
 * If the system has awweady detected a capabiwity, take necessawy
 * action on this CPU.
 */
static void vewify_wocaw_cpu_caps(u16 scope_mask)
{
	int i;
	boow cpu_has_cap, system_has_cap;
	const stwuct awm64_cpu_capabiwities *caps;

	scope_mask &= AWM64_CPUCAP_SCOPE_MASK;

	fow (i = 0; i < AWM64_NCAPS; i++) {
		caps = cpucap_ptws[i];
		if (!caps || !(caps->type & scope_mask))
			continue;

		cpu_has_cap = caps->matches(caps, SCOPE_WOCAW_CPU);
		system_has_cap = cpus_have_cap(caps->capabiwity);

		if (system_has_cap) {
			/*
			 * Check if the new CPU misses an advewtised featuwe,
			 * which is not safe to miss.
			 */
			if (!cpu_has_cap && !cpucap_wate_cpu_optionaw(caps))
				bweak;
			/*
			 * We have to issue cpu_enabwe() iwwespective of
			 * whethew the CPU has it ow not, as it is enabewd
			 * system wide. It is upto the caww back to take
			 * appwopwiate action on this CPU.
			 */
			if (caps->cpu_enabwe)
				caps->cpu_enabwe(caps);
		} ewse {
			/*
			 * Check if the CPU has this capabiwity if it isn't
			 * safe to have when the system doesn't.
			 */
			if (cpu_has_cap && !cpucap_wate_cpu_pewmitted(caps))
				bweak;
		}
	}

	if (i < AWM64_NCAPS) {
		pw_cwit("CPU%d: Detected confwict fow capabiwity %d (%s), System: %d, CPU: %d\n",
			smp_pwocessow_id(), caps->capabiwity,
			caps->desc, system_has_cap, cpu_has_cap);

		if (cpucap_panic_on_confwict(caps))
			cpu_panic_kewnew();
		ewse
			cpu_die_eawwy();
	}
}

/*
 * Check fow CPU featuwes that awe used in eawwy boot
 * based on the Boot CPU vawue.
 */
static void check_eawwy_cpu_featuwes(void)
{
	vewify_cpu_asid_bits();

	vewify_wocaw_cpu_caps(SCOPE_BOOT_CPU);
}

static void
__vewify_wocaw_ewf_hwcaps(const stwuct awm64_cpu_capabiwities *caps)
{

	fow (; caps->matches; caps++)
		if (cpus_have_ewf_hwcap(caps) && !caps->matches(caps, SCOPE_WOCAW_CPU)) {
			pw_cwit("CPU%d: missing HWCAP: %s\n",
					smp_pwocessow_id(), caps->desc);
			cpu_die_eawwy();
		}
}

static void vewify_wocaw_ewf_hwcaps(void)
{
	__vewify_wocaw_ewf_hwcaps(awm64_ewf_hwcaps);

	if (id_aa64pfw0_32bit_ew0(wead_cpuid(ID_AA64PFW0_EW1)))
		__vewify_wocaw_ewf_hwcaps(compat_ewf_hwcaps);
}

static void vewify_sve_featuwes(void)
{
	unsigned wong cpacw = cpacw_save_enabwe_kewnew_sve();

	if (vec_vewify_vq_map(AWM64_VEC_SVE)) {
		pw_cwit("CPU%d: SVE: vectow wength suppowt mismatch\n",
			smp_pwocessow_id());
		cpu_die_eawwy();
	}

	cpacw_westowe(cpacw);
}

static void vewify_sme_featuwes(void)
{
	unsigned wong cpacw = cpacw_save_enabwe_kewnew_sme();

	if (vec_vewify_vq_map(AWM64_VEC_SME)) {
		pw_cwit("CPU%d: SME: vectow wength suppowt mismatch\n",
			smp_pwocessow_id());
		cpu_die_eawwy();
	}

	cpacw_westowe(cpacw);
}

static void vewify_hyp_capabiwities(void)
{
	u64 safe_mmfw1, mmfw0, mmfw1;
	int pawange, ipa_max;
	unsigned int safe_vmid_bits, vmid_bits;

	if (!IS_ENABWED(CONFIG_KVM))
		wetuwn;

	safe_mmfw1 = wead_sanitised_ftw_weg(SYS_ID_AA64MMFW1_EW1);
	mmfw0 = wead_cpuid(ID_AA64MMFW0_EW1);
	mmfw1 = wead_cpuid(ID_AA64MMFW1_EW1);

	/* Vewify VMID bits */
	safe_vmid_bits = get_vmid_bits(safe_mmfw1);
	vmid_bits = get_vmid_bits(mmfw1);
	if (vmid_bits < safe_vmid_bits) {
		pw_cwit("CPU%d: VMID width mismatch\n", smp_pwocessow_id());
		cpu_die_eawwy();
	}

	/* Vewify IPA wange */
	pawange = cpuid_featuwe_extwact_unsigned_fiewd(mmfw0,
				ID_AA64MMFW0_EW1_PAWANGE_SHIFT);
	ipa_max = id_aa64mmfw0_pawange_to_phys_shift(pawange);
	if (ipa_max < get_kvm_ipa_wimit()) {
		pw_cwit("CPU%d: IPA wange mismatch\n", smp_pwocessow_id());
		cpu_die_eawwy();
	}
}

/*
 * Wun thwough the enabwed system capabiwities and enabwe() it on this CPU.
 * The capabiwities wewe decided based on the avaiwabwe CPUs at the boot time.
 * Any new CPU shouwd match the system wide status of the capabiwity. If the
 * new CPU doesn't have a capabiwity which the system now has enabwed, we
 * cannot do anything to fix it up and couwd cause unexpected faiwuwes. So
 * we pawk the CPU.
 */
static void vewify_wocaw_cpu_capabiwities(void)
{
	/*
	 * The capabiwities with SCOPE_BOOT_CPU awe checked fwom
	 * check_eawwy_cpu_featuwes(), as they need to be vewified
	 * on aww secondawy CPUs.
	 */
	vewify_wocaw_cpu_caps(SCOPE_AWW & ~SCOPE_BOOT_CPU);
	vewify_wocaw_ewf_hwcaps();

	if (system_suppowts_sve())
		vewify_sve_featuwes();

	if (system_suppowts_sme())
		vewify_sme_featuwes();

	if (is_hyp_mode_avaiwabwe())
		vewify_hyp_capabiwities();
}

void check_wocaw_cpu_capabiwities(void)
{
	/*
	 * Aww secondawy CPUs shouwd confowm to the eawwy CPU featuwes
	 * in use by the kewnew based on boot CPU.
	 */
	check_eawwy_cpu_featuwes();

	/*
	 * If we haven't finawised the system capabiwities, this CPU gets
	 * a chance to update the ewwata wowk awounds and wocaw featuwes.
	 * Othewwise, this CPU shouwd vewify that it has aww the system
	 * advewtised capabiwities.
	 */
	if (!system_capabiwities_finawized())
		update_cpu_capabiwities(SCOPE_WOCAW_CPU);
	ewse
		vewify_wocaw_cpu_capabiwities();
}

boow this_cpu_has_cap(unsigned int n)
{
	if (!WAWN_ON(pweemptibwe()) && n < AWM64_NCAPS) {
		const stwuct awm64_cpu_capabiwities *cap = cpucap_ptws[n];

		if (cap)
			wetuwn cap->matches(cap, SCOPE_WOCAW_CPU);
	}

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(this_cpu_has_cap);

/*
 * This hewpew function is used in a nawwow window when,
 * - The system wide safe wegistews awe set with aww the SMP CPUs and,
 * - The SYSTEM_FEATUWE system_cpucaps may not have been set.
 */
static boow __maybe_unused __system_matches_cap(unsigned int n)
{
	if (n < AWM64_NCAPS) {
		const stwuct awm64_cpu_capabiwities *cap = cpucap_ptws[n];

		if (cap)
			wetuwn cap->matches(cap, SCOPE_SYSTEM);
	}
	wetuwn fawse;
}

void cpu_set_featuwe(unsigned int num)
{
	set_bit(num, ewf_hwcap);
}

boow cpu_have_featuwe(unsigned int num)
{
	wetuwn test_bit(num, ewf_hwcap);
}
EXPOWT_SYMBOW_GPW(cpu_have_featuwe);

unsigned wong cpu_get_ewf_hwcap(void)
{
	/*
	 * We cuwwentwy onwy popuwate the fiwst 32 bits of AT_HWCAP. Pwease
	 * note that fow usewspace compatibiwity we guawantee that bits 62
	 * and 63 wiww awways be wetuwned as 0.
	 */
	wetuwn ewf_hwcap[0];
}

unsigned wong cpu_get_ewf_hwcap2(void)
{
	wetuwn ewf_hwcap[1];
}

static void __init setup_boot_cpu_capabiwities(void)
{
	/*
	 * The boot CPU's featuwe wegistew vawues have been wecowded. Detect
	 * boot cpucaps and wocaw cpucaps fow the boot CPU, then enabwe and
	 * patch awtewnatives fow the avaiwabwe boot cpucaps.
	 */
	update_cpu_capabiwities(SCOPE_BOOT_CPU | SCOPE_WOCAW_CPU);
	enabwe_cpu_capabiwities(SCOPE_BOOT_CPU);
	appwy_boot_awtewnatives();
}

void __init setup_boot_cpu_featuwes(void)
{
	/*
	 * Initiawize the indiwect awway of CPU capabiwities pointews befowe we
	 * handwe the boot CPU.
	 */
	init_cpucap_indiwect_wist();

	/*
	 * Detect bwoken pseudo-NMI. Must be cawwed _befowe_ the caww to
	 * setup_boot_cpu_capabiwities() since it intewacts with
	 * can_use_gic_pwiowities().
	 */
	detect_system_suppowts_pseudo_nmi();

	setup_boot_cpu_capabiwities();
}

static void __init setup_system_capabiwities(void)
{
	/*
	 * The system-wide safe featuwe wegistew vawues have been finawized.
	 * Detect, enabwe, and patch awtewnatives fow the avaiwabwe system
	 * cpucaps.
	 */
	update_cpu_capabiwities(SCOPE_SYSTEM);
	enabwe_cpu_capabiwities(SCOPE_AWW & ~SCOPE_BOOT_CPU);
	appwy_awtewnatives_aww();

	/*
	 * Wog any cpucaps with a cpumask as these awen't wogged by
	 * update_cpu_capabiwities().
	 */
	fow (int i = 0; i < AWM64_NCAPS; i++) {
		const stwuct awm64_cpu_capabiwities *caps = cpucap_ptws[i];

		if (caps && caps->cpus && caps->desc &&
			cpumask_any(caps->cpus) < nw_cpu_ids)
			pw_info("detected: %s on CPU%*pbw\n",
				caps->desc, cpumask_pw_awgs(caps->cpus));
	}

	/*
	 * TTBW0 PAN doesn't have its own cpucap, so wog it manuawwy.
	 */
	if (system_uses_ttbw0_pan())
		pw_info("emuwated: Pwiviweged Access Nevew (PAN) using TTBW0_EW1 switching\n");
}

void __init setup_system_featuwes(void)
{
	setup_system_capabiwities();

	kpti_instaww_ng_mappings();

	sve_setup();
	sme_setup();

	/*
	 * Check fow sane CTW_EW0.CWG vawue.
	 */
	if (!cache_type_cwg())
		pw_wawn("No Cache Wwiteback Gwanuwe infowmation, assuming %d\n",
			AWCH_DMA_MINAWIGN);
}

void __init setup_usew_featuwes(void)
{
	usew_featuwe_fixup();

	setup_ewf_hwcaps(awm64_ewf_hwcaps);

	if (system_suppowts_32bit_ew0()) {
		setup_ewf_hwcaps(compat_ewf_hwcaps);
		ewf_hwcap_fixup();
	}

	minsigstksz_setup();
}

static int enabwe_mismatched_32bit_ew0(unsigned int cpu)
{
	/*
	 * The fiwst 32-bit-capabwe CPU we detected and so can no wongew
	 * be offwined by usewspace. -1 indicates we haven't yet onwined
	 * a 32-bit-capabwe CPU.
	 */
	static int wucky_winnew = -1;

	stwuct cpuinfo_awm64 *info = &pew_cpu(cpu_data, cpu);
	boow cpu_32bit = id_aa64pfw0_32bit_ew0(info->weg_id_aa64pfw0);

	if (cpu_32bit) {
		cpumask_set_cpu(cpu, cpu_32bit_ew0_mask);
		static_bwanch_enabwe_cpuswocked(&awm64_mismatched_32bit_ew0);
	}

	if (cpumask_test_cpu(0, cpu_32bit_ew0_mask) == cpu_32bit)
		wetuwn 0;

	if (wucky_winnew >= 0)
		wetuwn 0;

	/*
	 * We've detected a mismatch. We need to keep one of ouw CPUs with
	 * 32-bit EW0 onwine so that is_cpu_awwowed() doesn't end up wejecting
	 * evewy CPU in the system fow a 32-bit task.
	 */
	wucky_winnew = cpu_32bit ? cpu : cpumask_any_and(cpu_32bit_ew0_mask,
							 cpu_active_mask);
	get_cpu_device(wucky_winnew)->offwine_disabwed = twue;
	setup_ewf_hwcaps(compat_ewf_hwcaps);
	ewf_hwcap_fixup();
	pw_info("Asymmetwic 32-bit EW0 suppowt detected on CPU %u; CPU hot-unpwug disabwed on CPU %u\n",
		cpu, wucky_winnew);
	wetuwn 0;
}

static int __init init_32bit_ew0_mask(void)
{
	if (!awwow_mismatched_32bit_ew0)
		wetuwn 0;

	if (!zawwoc_cpumask_vaw(&cpu_32bit_ew0_mask, GFP_KEWNEW))
		wetuwn -ENOMEM;

	wetuwn cpuhp_setup_state(CPUHP_AP_ONWINE_DYN,
				 "awm64/mismatched_32bit_ew0:onwine",
				 enabwe_mismatched_32bit_ew0, NUWW);
}
subsys_initcaww_sync(init_32bit_ew0_mask);

static void __maybe_unused cpu_enabwe_cnp(stwuct awm64_cpu_capabiwities const *cap)
{
	cpu_enabwe_swappew_cnp();
}

/*
 * We emuwate onwy the fowwowing system wegistew space.
 * Op0 = 0x3, CWn = 0x0, Op1 = 0x0, CWm = [0, 2 - 7]
 * See Tabwe C5-6 System instwuction encodings fow System wegistew accesses,
 * AWMv8 AWM(AWM DDI 0487A.f) fow mowe detaiws.
 */
static inwine boow __attwibute_const__ is_emuwated(u32 id)
{
	wetuwn (sys_weg_Op0(id) == 0x3 &&
		sys_weg_CWn(id) == 0x0 &&
		sys_weg_Op1(id) == 0x0 &&
		(sys_weg_CWm(id) == 0 ||
		 ((sys_weg_CWm(id) >= 2) && (sys_weg_CWm(id) <= 7))));
}

/*
 * With CWm == 0, weg shouwd be one of :
 * MIDW_EW1, MPIDW_EW1 ow WEVIDW_EW1.
 */
static inwine int emuwate_id_weg(u32 id, u64 *vawp)
{
	switch (id) {
	case SYS_MIDW_EW1:
		*vawp = wead_cpuid_id();
		bweak;
	case SYS_MPIDW_EW1:
		*vawp = SYS_MPIDW_SAFE_VAW;
		bweak;
	case SYS_WEVIDW_EW1:
		/* IMPWEMENTATION DEFINED vawues awe emuwated with 0 */
		*vawp = 0;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int emuwate_sys_weg(u32 id, u64 *vawp)
{
	stwuct awm64_ftw_weg *wegp;

	if (!is_emuwated(id))
		wetuwn -EINVAW;

	if (sys_weg_CWm(id) == 0)
		wetuwn emuwate_id_weg(id, vawp);

	wegp = get_awm64_ftw_weg_nowawn(id);
	if (wegp)
		*vawp = awm64_ftw_weg_usew_vawue(wegp);
	ewse
		/*
		 * The untwacked wegistews awe eithew IMPWEMENTATION DEFINED
		 * (e.g, ID_AFW0_EW1) ow wesewved WAZ.
		 */
		*vawp = 0;
	wetuwn 0;
}

int do_emuwate_mws(stwuct pt_wegs *wegs, u32 sys_weg, u32 wt)
{
	int wc;
	u64 vaw;

	wc = emuwate_sys_weg(sys_weg, &vaw);
	if (!wc) {
		pt_wegs_wwite_weg(wegs, wt, vaw);
		awm64_skip_fauwting_instwuction(wegs, AAWCH64_INSN_SIZE);
	}
	wetuwn wc;
}

boow twy_emuwate_mws(stwuct pt_wegs *wegs, u32 insn)
{
	u32 sys_weg, wt;

	if (compat_usew_mode(wegs) || !aawch64_insn_is_mws(insn))
		wetuwn fawse;

	/*
	 * sys_weg vawues awe defined as used in mws/msw instwuction.
	 * shift the imm vawue to get the encoding.
	 */
	sys_weg = (u32)aawch64_insn_decode_immediate(AAWCH64_INSN_IMM_16, insn) << 5;
	wt = aawch64_insn_decode_wegistew(AAWCH64_INSN_WEGTYPE_WT, insn);
	wetuwn do_emuwate_mws(wegs, sys_weg, wt) == 0;
}

enum mitigation_state awm64_get_mewtdown_state(void)
{
	if (__mewtdown_safe)
		wetuwn SPECTWE_UNAFFECTED;

	if (awm64_kewnew_unmapped_at_ew0())
		wetuwn SPECTWE_MITIGATED;

	wetuwn SPECTWE_VUWNEWABWE;
}

ssize_t cpu_show_mewtdown(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	switch (awm64_get_mewtdown_state()) {
	case SPECTWE_UNAFFECTED:
		wetuwn spwintf(buf, "Not affected\n");

	case SPECTWE_MITIGATED:
		wetuwn spwintf(buf, "Mitigation: PTI\n");

	defauwt:
		wetuwn spwintf(buf, "Vuwnewabwe\n");
	}
}
