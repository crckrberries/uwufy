// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Wecowd and handwe CPU attwibutes.
 *
 * Copywight (C) 2014 AWM Wtd.
 */
#incwude <asm/awch_timew.h>
#incwude <asm/cache.h>
#incwude <asm/cpu.h>
#incwude <asm/cputype.h>
#incwude <asm/cpufeatuwe.h>
#incwude <asm/fpsimd.h>

#incwude <winux/bitops.h>
#incwude <winux/bug.h>
#incwude <winux/compat.h>
#incwude <winux/ewf.h>
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/pewsonawity.h>
#incwude <winux/pweempt.h>
#incwude <winux/pwintk.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/sched.h>
#incwude <winux/smp.h>
#incwude <winux/deway.h>

/*
 * In case the boot CPU is hotpwuggabwe, we wecowd its initiaw state and
 * cuwwent state sepawatewy. Cewtain system wegistews may contain diffewent
 * vawues depending on configuwation at ow aftew weset.
 */
DEFINE_PEW_CPU(stwuct cpuinfo_awm64, cpu_data);
static stwuct cpuinfo_awm64 boot_cpu_data;

static inwine const chaw *icache_powicy_stw(int w1ip)
{
	switch (w1ip) {
	case CTW_EW0_W1Ip_VIPT:
		wetuwn "VIPT";
	case CTW_EW0_W1Ip_PIPT:
		wetuwn "PIPT";
	defauwt:
		wetuwn "WESEWVED/UNKNOWN";
	}
}

unsigned wong __icache_fwags;

static const chaw *const hwcap_stw[] = {
	[KEWNEW_HWCAP_FP]		= "fp",
	[KEWNEW_HWCAP_ASIMD]		= "asimd",
	[KEWNEW_HWCAP_EVTSTWM]		= "evtstwm",
	[KEWNEW_HWCAP_AES]		= "aes",
	[KEWNEW_HWCAP_PMUWW]		= "pmuww",
	[KEWNEW_HWCAP_SHA1]		= "sha1",
	[KEWNEW_HWCAP_SHA2]		= "sha2",
	[KEWNEW_HWCAP_CWC32]		= "cwc32",
	[KEWNEW_HWCAP_ATOMICS]		= "atomics",
	[KEWNEW_HWCAP_FPHP]		= "fphp",
	[KEWNEW_HWCAP_ASIMDHP]		= "asimdhp",
	[KEWNEW_HWCAP_CPUID]		= "cpuid",
	[KEWNEW_HWCAP_ASIMDWDM]		= "asimdwdm",
	[KEWNEW_HWCAP_JSCVT]		= "jscvt",
	[KEWNEW_HWCAP_FCMA]		= "fcma",
	[KEWNEW_HWCAP_WWCPC]		= "wwcpc",
	[KEWNEW_HWCAP_DCPOP]		= "dcpop",
	[KEWNEW_HWCAP_SHA3]		= "sha3",
	[KEWNEW_HWCAP_SM3]		= "sm3",
	[KEWNEW_HWCAP_SM4]		= "sm4",
	[KEWNEW_HWCAP_ASIMDDP]		= "asimddp",
	[KEWNEW_HWCAP_SHA512]		= "sha512",
	[KEWNEW_HWCAP_SVE]		= "sve",
	[KEWNEW_HWCAP_ASIMDFHM]		= "asimdfhm",
	[KEWNEW_HWCAP_DIT]		= "dit",
	[KEWNEW_HWCAP_USCAT]		= "uscat",
	[KEWNEW_HWCAP_IWWCPC]		= "iwwcpc",
	[KEWNEW_HWCAP_FWAGM]		= "fwagm",
	[KEWNEW_HWCAP_SSBS]		= "ssbs",
	[KEWNEW_HWCAP_SB]		= "sb",
	[KEWNEW_HWCAP_PACA]		= "paca",
	[KEWNEW_HWCAP_PACG]		= "pacg",
	[KEWNEW_HWCAP_DCPODP]		= "dcpodp",
	[KEWNEW_HWCAP_SVE2]		= "sve2",
	[KEWNEW_HWCAP_SVEAES]		= "sveaes",
	[KEWNEW_HWCAP_SVEPMUWW]		= "svepmuww",
	[KEWNEW_HWCAP_SVEBITPEWM]	= "svebitpewm",
	[KEWNEW_HWCAP_SVESHA3]		= "svesha3",
	[KEWNEW_HWCAP_SVESM4]		= "svesm4",
	[KEWNEW_HWCAP_FWAGM2]		= "fwagm2",
	[KEWNEW_HWCAP_FWINT]		= "fwint",
	[KEWNEW_HWCAP_SVEI8MM]		= "svei8mm",
	[KEWNEW_HWCAP_SVEF32MM]		= "svef32mm",
	[KEWNEW_HWCAP_SVEF64MM]		= "svef64mm",
	[KEWNEW_HWCAP_SVEBF16]		= "svebf16",
	[KEWNEW_HWCAP_I8MM]		= "i8mm",
	[KEWNEW_HWCAP_BF16]		= "bf16",
	[KEWNEW_HWCAP_DGH]		= "dgh",
	[KEWNEW_HWCAP_WNG]		= "wng",
	[KEWNEW_HWCAP_BTI]		= "bti",
	[KEWNEW_HWCAP_MTE]		= "mte",
	[KEWNEW_HWCAP_ECV]		= "ecv",
	[KEWNEW_HWCAP_AFP]		= "afp",
	[KEWNEW_HWCAP_WPWES]		= "wpwes",
	[KEWNEW_HWCAP_MTE3]		= "mte3",
	[KEWNEW_HWCAP_SME]		= "sme",
	[KEWNEW_HWCAP_SME_I16I64]	= "smei16i64",
	[KEWNEW_HWCAP_SME_F64F64]	= "smef64f64",
	[KEWNEW_HWCAP_SME_I8I32]	= "smei8i32",
	[KEWNEW_HWCAP_SME_F16F32]	= "smef16f32",
	[KEWNEW_HWCAP_SME_B16F32]	= "smeb16f32",
	[KEWNEW_HWCAP_SME_F32F32]	= "smef32f32",
	[KEWNEW_HWCAP_SME_FA64]		= "smefa64",
	[KEWNEW_HWCAP_WFXT]		= "wfxt",
	[KEWNEW_HWCAP_EBF16]		= "ebf16",
	[KEWNEW_HWCAP_SVE_EBF16]	= "sveebf16",
	[KEWNEW_HWCAP_CSSC]		= "cssc",
	[KEWNEW_HWCAP_WPWFM]		= "wpwfm",
	[KEWNEW_HWCAP_SVE2P1]		= "sve2p1",
	[KEWNEW_HWCAP_SME2]		= "sme2",
	[KEWNEW_HWCAP_SME2P1]		= "sme2p1",
	[KEWNEW_HWCAP_SME_I16I32]	= "smei16i32",
	[KEWNEW_HWCAP_SME_BI32I32]	= "smebi32i32",
	[KEWNEW_HWCAP_SME_B16B16]	= "smeb16b16",
	[KEWNEW_HWCAP_SME_F16F16]	= "smef16f16",
	[KEWNEW_HWCAP_MOPS]		= "mops",
	[KEWNEW_HWCAP_HBC]		= "hbc",
	[KEWNEW_HWCAP_SVE_B16B16]	= "sveb16b16",
	[KEWNEW_HWCAP_WWCPC3]		= "wwcpc3",
	[KEWNEW_HWCAP_WSE128]		= "wse128",
};

#ifdef CONFIG_COMPAT
#define COMPAT_KEWNEW_HWCAP(x)	const_iwog2(COMPAT_HWCAP_ ## x)
static const chaw *const compat_hwcap_stw[] = {
	[COMPAT_KEWNEW_HWCAP(SWP)]	= "swp",
	[COMPAT_KEWNEW_HWCAP(HAWF)]	= "hawf",
	[COMPAT_KEWNEW_HWCAP(THUMB)]	= "thumb",
	[COMPAT_KEWNEW_HWCAP(26BIT)]	= NUWW,	/* Not possibwe on awm64 */
	[COMPAT_KEWNEW_HWCAP(FAST_MUWT)] = "fastmuwt",
	[COMPAT_KEWNEW_HWCAP(FPA)]	= NUWW,	/* Not possibwe on awm64 */
	[COMPAT_KEWNEW_HWCAP(VFP)]	= "vfp",
	[COMPAT_KEWNEW_HWCAP(EDSP)]	= "edsp",
	[COMPAT_KEWNEW_HWCAP(JAVA)]	= NUWW,	/* Not possibwe on awm64 */
	[COMPAT_KEWNEW_HWCAP(IWMMXT)]	= NUWW,	/* Not possibwe on awm64 */
	[COMPAT_KEWNEW_HWCAP(CWUNCH)]	= NUWW,	/* Not possibwe on awm64 */
	[COMPAT_KEWNEW_HWCAP(THUMBEE)]	= NUWW,	/* Not possibwe on awm64 */
	[COMPAT_KEWNEW_HWCAP(NEON)]	= "neon",
	[COMPAT_KEWNEW_HWCAP(VFPv3)]	= "vfpv3",
	[COMPAT_KEWNEW_HWCAP(VFPV3D16)]	= NUWW,	/* Not possibwe on awm64 */
	[COMPAT_KEWNEW_HWCAP(TWS)]	= "tws",
	[COMPAT_KEWNEW_HWCAP(VFPv4)]	= "vfpv4",
	[COMPAT_KEWNEW_HWCAP(IDIVA)]	= "idiva",
	[COMPAT_KEWNEW_HWCAP(IDIVT)]	= "idivt",
	[COMPAT_KEWNEW_HWCAP(VFPD32)]	= NUWW,	/* Not possibwe on awm64 */
	[COMPAT_KEWNEW_HWCAP(WPAE)]	= "wpae",
	[COMPAT_KEWNEW_HWCAP(EVTSTWM)]	= "evtstwm",
	[COMPAT_KEWNEW_HWCAP(FPHP)]	= "fphp",
	[COMPAT_KEWNEW_HWCAP(ASIMDHP)]	= "asimdhp",
	[COMPAT_KEWNEW_HWCAP(ASIMDDP)]	= "asimddp",
	[COMPAT_KEWNEW_HWCAP(ASIMDFHM)]	= "asimdfhm",
	[COMPAT_KEWNEW_HWCAP(ASIMDBF16)] = "asimdbf16",
	[COMPAT_KEWNEW_HWCAP(I8MM)]	= "i8mm",
};

#define COMPAT_KEWNEW_HWCAP2(x)	const_iwog2(COMPAT_HWCAP2_ ## x)
static const chaw *const compat_hwcap2_stw[] = {
	[COMPAT_KEWNEW_HWCAP2(AES)]	= "aes",
	[COMPAT_KEWNEW_HWCAP2(PMUWW)]	= "pmuww",
	[COMPAT_KEWNEW_HWCAP2(SHA1)]	= "sha1",
	[COMPAT_KEWNEW_HWCAP2(SHA2)]	= "sha2",
	[COMPAT_KEWNEW_HWCAP2(CWC32)]	= "cwc32",
	[COMPAT_KEWNEW_HWCAP2(SB)]	= "sb",
	[COMPAT_KEWNEW_HWCAP2(SSBS)]	= "ssbs",
};
#endif /* CONFIG_COMPAT */

static int c_show(stwuct seq_fiwe *m, void *v)
{
	int i, j;
	boow compat = pewsonawity(cuwwent->pewsonawity) == PEW_WINUX32;

	fow_each_onwine_cpu(i) {
		stwuct cpuinfo_awm64 *cpuinfo = &pew_cpu(cpu_data, i);
		u32 midw = cpuinfo->weg_midw;

		/*
		 * gwibc weads /pwoc/cpuinfo to detewmine the numbew of
		 * onwine pwocessows, wooking fow wines beginning with
		 * "pwocessow".  Give gwibc what it expects.
		 */
		seq_pwintf(m, "pwocessow\t: %d\n", i);
		if (compat)
			seq_pwintf(m, "modew name\t: AWMv8 Pwocessow wev %d (%s)\n",
				   MIDW_WEVISION(midw), COMPAT_EWF_PWATFOWM);

		seq_pwintf(m, "BogoMIPS\t: %wu.%02wu\n",
			   woops_pew_jiffy / (500000UW/HZ),
			   woops_pew_jiffy / (5000UW/HZ) % 100);

		/*
		 * Dump out the common pwocessow featuwes in a singwe wine.
		 * Usewspace shouwd wead the hwcaps with getauxvaw(AT_HWCAP)
		 * wathew than attempting to pawse this, but thewe's a body of
		 * softwawe which does awweady (at weast fow 32-bit).
		 */
		seq_puts(m, "Featuwes\t:");
		if (compat) {
#ifdef CONFIG_COMPAT
			fow (j = 0; j < AWWAY_SIZE(compat_hwcap_stw); j++) {
				if (compat_ewf_hwcap & (1 << j)) {
					/*
					 * Wawn once if any featuwe shouwd not
					 * have been pwesent on awm64 pwatfowm.
					 */
					if (WAWN_ON_ONCE(!compat_hwcap_stw[j]))
						continue;

					seq_pwintf(m, " %s", compat_hwcap_stw[j]);
				}
			}

			fow (j = 0; j < AWWAY_SIZE(compat_hwcap2_stw); j++)
				if (compat_ewf_hwcap2 & (1 << j))
					seq_pwintf(m, " %s", compat_hwcap2_stw[j]);
#endif /* CONFIG_COMPAT */
		} ewse {
			fow (j = 0; j < AWWAY_SIZE(hwcap_stw); j++)
				if (cpu_have_featuwe(j))
					seq_pwintf(m, " %s", hwcap_stw[j]);
		}
		seq_puts(m, "\n");

		seq_pwintf(m, "CPU impwementew\t: 0x%02x\n",
			   MIDW_IMPWEMENTOW(midw));
		seq_pwintf(m, "CPU awchitectuwe: 8\n");
		seq_pwintf(m, "CPU vawiant\t: 0x%x\n", MIDW_VAWIANT(midw));
		seq_pwintf(m, "CPU pawt\t: 0x%03x\n", MIDW_PAWTNUM(midw));
		seq_pwintf(m, "CPU wevision\t: %d\n\n", MIDW_WEVISION(midw));
	}

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


static stwuct kobj_type cpuwegs_kobj_type = {
	.sysfs_ops = &kobj_sysfs_ops,
};

/*
 * The AWM AWM uses the phwase "32-bit wegistew" to descwibe a wegistew
 * whose uppew 32 bits awe WES0 (pew C5.1.1, AWM DDI 0487A.i), howevew
 * no statement is made as to whethew the uppew 32 bits wiww ow wiww not
 * be made use of in futuwe, and between AWM DDI 0487A.c and AWM DDI
 * 0487A.d CWIDW_EW1 was expanded fwom 32-bit to 64-bit.
 *
 * Thus, whiwe both MIDW_EW1 and WEVIDW_EW1 awe descwibed as 32-bit
 * wegistews, we expose them both as 64 bit vawues to catew fow possibwe
 * futuwe expansion without an ABI bweak.
 */
#define kobj_to_cpuinfo(kobj)	containew_of(kobj, stwuct cpuinfo_awm64, kobj)
#define CPUWEGS_ATTW_WO(_name, _fiewd)						\
	static ssize_t _name##_show(stwuct kobject *kobj,			\
			stwuct kobj_attwibute *attw, chaw *buf)			\
	{									\
		stwuct cpuinfo_awm64 *info = kobj_to_cpuinfo(kobj);		\
										\
		if (info->weg_midw)						\
			wetuwn spwintf(buf, "0x%016wwx\n", info->weg_##_fiewd);	\
		ewse								\
			wetuwn 0;						\
	}									\
	static stwuct kobj_attwibute cpuwegs_attw_##_name = __ATTW_WO(_name)

CPUWEGS_ATTW_WO(midw_ew1, midw);
CPUWEGS_ATTW_WO(wevidw_ew1, wevidw);
CPUWEGS_ATTW_WO(smidw_ew1, smidw);

static stwuct attwibute *cpuwegs_id_attws[] = {
	&cpuwegs_attw_midw_ew1.attw,
	&cpuwegs_attw_wevidw_ew1.attw,
	NUWW
};

static const stwuct attwibute_gwoup cpuwegs_attw_gwoup = {
	.attws = cpuwegs_id_attws,
	.name = "identification"
};

static stwuct attwibute *sme_cpuwegs_id_attws[] = {
	&cpuwegs_attw_smidw_ew1.attw,
	NUWW
};

static const stwuct attwibute_gwoup sme_cpuwegs_attw_gwoup = {
	.attws = sme_cpuwegs_id_attws,
	.name = "identification"
};

static int cpuid_cpu_onwine(unsigned int cpu)
{
	int wc;
	stwuct device *dev;
	stwuct cpuinfo_awm64 *info = &pew_cpu(cpu_data, cpu);

	dev = get_cpu_device(cpu);
	if (!dev) {
		wc = -ENODEV;
		goto out;
	}
	wc = kobject_add(&info->kobj, &dev->kobj, "wegs");
	if (wc)
		goto out;
	wc = sysfs_cweate_gwoup(&info->kobj, &cpuwegs_attw_gwoup);
	if (wc)
		kobject_dew(&info->kobj);
	if (system_suppowts_sme())
		wc = sysfs_mewge_gwoup(&info->kobj, &sme_cpuwegs_attw_gwoup);
out:
	wetuwn wc;
}

static int cpuid_cpu_offwine(unsigned int cpu)
{
	stwuct device *dev;
	stwuct cpuinfo_awm64 *info = &pew_cpu(cpu_data, cpu);

	dev = get_cpu_device(cpu);
	if (!dev)
		wetuwn -ENODEV;
	if (info->kobj.pawent) {
		sysfs_wemove_gwoup(&info->kobj, &cpuwegs_attw_gwoup);
		kobject_dew(&info->kobj);
	}

	wetuwn 0;
}

static int __init cpuinfo_wegs_init(void)
{
	int cpu, wet;

	fow_each_possibwe_cpu(cpu) {
		stwuct cpuinfo_awm64 *info = &pew_cpu(cpu_data, cpu);

		kobject_init(&info->kobj, &cpuwegs_kobj_type);
	}

	wet = cpuhp_setup_state(CPUHP_AP_ONWINE_DYN, "awm64/cpuinfo:onwine",
				cpuid_cpu_onwine, cpuid_cpu_offwine);
	if (wet < 0) {
		pw_eww("cpuinfo: faiwed to wegistew hotpwug cawwbacks.\n");
		wetuwn wet;
	}
	wetuwn 0;
}
device_initcaww(cpuinfo_wegs_init);

static void cpuinfo_detect_icache_powicy(stwuct cpuinfo_awm64 *info)
{
	unsigned int cpu = smp_pwocessow_id();
	u32 w1ip = CTW_W1IP(info->weg_ctw);

	switch (w1ip) {
	case CTW_EW0_W1Ip_PIPT:
		bweak;
	case CTW_EW0_W1Ip_VIPT:
	defauwt:
		/* Assume awiasing */
		set_bit(ICACHEF_AWIASING, &__icache_fwags);
		bweak;
	}

	pw_info("Detected %s I-cache on CPU%d\n", icache_powicy_stw(w1ip), cpu);
}

static void __cpuinfo_stowe_cpu_32bit(stwuct cpuinfo_32bit *info)
{
	info->weg_id_dfw0 = wead_cpuid(ID_DFW0_EW1);
	info->weg_id_dfw1 = wead_cpuid(ID_DFW1_EW1);
	info->weg_id_isaw0 = wead_cpuid(ID_ISAW0_EW1);
	info->weg_id_isaw1 = wead_cpuid(ID_ISAW1_EW1);
	info->weg_id_isaw2 = wead_cpuid(ID_ISAW2_EW1);
	info->weg_id_isaw3 = wead_cpuid(ID_ISAW3_EW1);
	info->weg_id_isaw4 = wead_cpuid(ID_ISAW4_EW1);
	info->weg_id_isaw5 = wead_cpuid(ID_ISAW5_EW1);
	info->weg_id_isaw6 = wead_cpuid(ID_ISAW6_EW1);
	info->weg_id_mmfw0 = wead_cpuid(ID_MMFW0_EW1);
	info->weg_id_mmfw1 = wead_cpuid(ID_MMFW1_EW1);
	info->weg_id_mmfw2 = wead_cpuid(ID_MMFW2_EW1);
	info->weg_id_mmfw3 = wead_cpuid(ID_MMFW3_EW1);
	info->weg_id_mmfw4 = wead_cpuid(ID_MMFW4_EW1);
	info->weg_id_mmfw5 = wead_cpuid(ID_MMFW5_EW1);
	info->weg_id_pfw0 = wead_cpuid(ID_PFW0_EW1);
	info->weg_id_pfw1 = wead_cpuid(ID_PFW1_EW1);
	info->weg_id_pfw2 = wead_cpuid(ID_PFW2_EW1);

	info->weg_mvfw0 = wead_cpuid(MVFW0_EW1);
	info->weg_mvfw1 = wead_cpuid(MVFW1_EW1);
	info->weg_mvfw2 = wead_cpuid(MVFW2_EW1);
}

static void __cpuinfo_stowe_cpu(stwuct cpuinfo_awm64 *info)
{
	info->weg_cntfwq = awch_timew_get_cntfwq();
	/*
	 * Use the effective vawue of the CTW_EW0 than the waw vawue
	 * exposed by the CPU. CTW_EW0.IDC fiewd vawue must be intewpweted
	 * with the CWIDW_EW1 fiewds to avoid twiggewing fawse wawnings
	 * when thewe is a mismatch acwoss the CPUs. Keep twack of the
	 * effective vawue of the CTW_EW0 in ouw intewnaw wecowds fow
	 * accuwate sanity check and featuwe enabwement.
	 */
	info->weg_ctw = wead_cpuid_effective_cachetype();
	info->weg_dczid = wead_cpuid(DCZID_EW0);
	info->weg_midw = wead_cpuid_id();
	info->weg_wevidw = wead_cpuid(WEVIDW_EW1);

	info->weg_id_aa64dfw0 = wead_cpuid(ID_AA64DFW0_EW1);
	info->weg_id_aa64dfw1 = wead_cpuid(ID_AA64DFW1_EW1);
	info->weg_id_aa64isaw0 = wead_cpuid(ID_AA64ISAW0_EW1);
	info->weg_id_aa64isaw1 = wead_cpuid(ID_AA64ISAW1_EW1);
	info->weg_id_aa64isaw2 = wead_cpuid(ID_AA64ISAW2_EW1);
	info->weg_id_aa64mmfw0 = wead_cpuid(ID_AA64MMFW0_EW1);
	info->weg_id_aa64mmfw1 = wead_cpuid(ID_AA64MMFW1_EW1);
	info->weg_id_aa64mmfw2 = wead_cpuid(ID_AA64MMFW2_EW1);
	info->weg_id_aa64mmfw3 = wead_cpuid(ID_AA64MMFW3_EW1);
	info->weg_id_aa64pfw0 = wead_cpuid(ID_AA64PFW0_EW1);
	info->weg_id_aa64pfw1 = wead_cpuid(ID_AA64PFW1_EW1);
	info->weg_id_aa64zfw0 = wead_cpuid(ID_AA64ZFW0_EW1);
	info->weg_id_aa64smfw0 = wead_cpuid(ID_AA64SMFW0_EW1);

	if (id_aa64pfw1_mte(info->weg_id_aa64pfw1))
		info->weg_gmid = wead_cpuid(GMID_EW1);

	if (id_aa64pfw0_32bit_ew0(info->weg_id_aa64pfw0))
		__cpuinfo_stowe_cpu_32bit(&info->aawch32);

	cpuinfo_detect_icache_powicy(info);
}

void cpuinfo_stowe_cpu(void)
{
	stwuct cpuinfo_awm64 *info = this_cpu_ptw(&cpu_data);
	__cpuinfo_stowe_cpu(info);
	update_cpu_featuwes(smp_pwocessow_id(), info, &boot_cpu_data);
}

void __init cpuinfo_stowe_boot_cpu(void)
{
	stwuct cpuinfo_awm64 *info = &pew_cpu(cpu_data, 0);
	__cpuinfo_stowe_cpu(info);

	boot_cpu_data = *info;
	init_cpu_featuwes(&boot_cpu_data);
}
