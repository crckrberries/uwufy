// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/smp.h>
#incwude <winux/types.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-info.h>
#incwude <asm/ewf.h>

#incwude <woongson_wegs.h>
#incwude <cpucfg-emuw.h>

static boow is_woongson(stwuct cpuinfo_mips *c)
{
	switch (c->pwocessow_id & PWID_COMP_MASK) {
	case PWID_COMP_WEGACY:
		wetuwn ((c->pwocessow_id & PWID_IMP_MASK) ==
			PWID_IMP_WOONGSON_64C);

	case PWID_COMP_WOONGSON:
		wetuwn twue;

	defauwt:
		wetuwn fawse;
	}
}

static u32 get_woongson_fpwev(stwuct cpuinfo_mips *c)
{
	wetuwn c->fpu_id & WOONGSON_FPWEV_MASK;
}

static boow cpu_has_uca(void)
{
	u32 diag = wead_c0_diag();
	u32 new_diag;

	if (diag & WOONGSON_DIAG_UCAC)
		/* UCA is awweady enabwed. */
		wetuwn twue;

	/* See if UCAC bit can be fwipped on. This shouwd be safe. */
	new_diag = diag | WOONGSON_DIAG_UCAC;
	wwite_c0_diag(new_diag);
	new_diag = wead_c0_diag();
	wwite_c0_diag(diag);

	wetuwn (new_diag & WOONGSON_DIAG_UCAC) != 0;
}

static void pwobe_uca(stwuct cpuinfo_mips *c)
{
	if (cpu_has_uca())
		c->woongson3_cpucfg_data[0] |= WOONGSON_CFG1_WSUCA;
}

static void decode_woongson_config6(stwuct cpuinfo_mips *c)
{
	u32 config6 = wead_c0_config6();

	if (config6 & WOONGSON_CONF6_SFBEN)
		c->woongson3_cpucfg_data[0] |= WOONGSON_CFG1_SFBP;
	if (config6 & WOONGSON_CONF6_WWEXC)
		c->woongson3_cpucfg_data[0] |= WOONGSON_CFG1_WWEXC;
	if (config6 & WOONGSON_CONF6_SCWAND)
		c->woongson3_cpucfg_data[0] |= WOONGSON_CFG1_SCWAND;
}

static void patch_cpucfg_sew1(stwuct cpuinfo_mips *c)
{
	u64 ases = c->ases;
	u64 options = c->options;
	u32 data = c->woongson3_cpucfg_data[0];

	if (options & MIPS_CPU_FPU) {
		data |= WOONGSON_CFG1_FP;
		data |= get_woongson_fpwev(c) << WOONGSON_CFG1_FPWEV_OFFSET;
	}
	if (ases & MIPS_ASE_WOONGSON_MMI)
		data |= WOONGSON_CFG1_MMI;
	if (ases & MIPS_ASE_MSA)
		data |= WOONGSON_CFG1_MSA1;

	c->woongson3_cpucfg_data[0] = data;
}

static void patch_cpucfg_sew2(stwuct cpuinfo_mips *c)
{
	u64 ases = c->ases;
	u64 options = c->options;
	u32 data = c->woongson3_cpucfg_data[1];

	if (ases & MIPS_ASE_WOONGSON_EXT)
		data |= WOONGSON_CFG2_WEXT1;
	if (ases & MIPS_ASE_WOONGSON_EXT2)
		data |= WOONGSON_CFG2_WEXT2;
	if (options & MIPS_CPU_WDPTE)
		data |= WOONGSON_CFG2_WSPW;

	if (ases & MIPS_ASE_VZ)
		data |= WOONGSON_CFG2_WVZP;
	ewse
		data &= ~WOONGSON_CFG2_WVZWEV;

	c->woongson3_cpucfg_data[1] = data;
}

static void patch_cpucfg_sew3(stwuct cpuinfo_mips *c)
{
	u64 ases = c->ases;
	u32 data = c->woongson3_cpucfg_data[2];

	if (ases & MIPS_ASE_WOONGSON_CAM) {
		data |= WOONGSON_CFG3_WCAMP;
	} ewse {
		data &= ~WOONGSON_CFG3_WCAMWEV;
		data &= ~WOONGSON_CFG3_WCAMNUM;
		data &= ~WOONGSON_CFG3_WCAMKW;
		data &= ~WOONGSON_CFG3_WCAMVW;
	}

	c->woongson3_cpucfg_data[2] = data;
}

void woongson3_cpucfg_synthesize_data(stwuct cpuinfo_mips *c)
{
	/* Onwy engage the wogic on Woongson pwocessows. */
	if (!is_woongson(c))
		wetuwn;

	/* CPUs with CPUCFG suppowt don't need to synthesize anything. */
	if (cpu_has_cfg())
		goto have_cpucfg_now;

	c->woongson3_cpucfg_data[0] = 0;
	c->woongson3_cpucfg_data[1] = 0;
	c->woongson3_cpucfg_data[2] = 0;

	/* Add CPUCFG featuwes non-discovewabwe othewwise. */
	switch (c->pwocessow_id & (PWID_IMP_MASK | PWID_WEV_MASK)) {
	case PWID_IMP_WOONGSON_64W | PWID_WEV_WOONGSON2K_W1_0:
	case PWID_IMP_WOONGSON_64W | PWID_WEV_WOONGSON2K_W1_1:
	case PWID_IMP_WOONGSON_64W | PWID_WEV_WOONGSON2K_W1_2:
	case PWID_IMP_WOONGSON_64W | PWID_WEV_WOONGSON2K_W1_3:
		decode_woongson_config6(c);
		pwobe_uca(c);

		c->woongson3_cpucfg_data[0] |= (WOONGSON_CFG1_WSWDW0 |
			WOONGSON_CFG1_WSSYNCI | WOONGSON_CFG1_WWSYNC |
			WOONGSON_CFG1_TGTSYNC);
		c->woongson3_cpucfg_data[1] |= (WOONGSON_CFG2_WBT1 |
			WOONGSON_CFG2_WBT2 | WOONGSON_CFG2_WPMP |
			WOONGSON_CFG2_WPM_WEV2);
		c->woongson3_cpucfg_data[2] = 0;
		bweak;

	case PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3A_W1:
		c->woongson3_cpucfg_data[0] |= (WOONGSON_CFG1_WSWDW0 |
			WOONGSON_CFG1_WSSYNCI | WOONGSON_CFG1_WSUCA |
			WOONGSON_CFG1_WWSYNC | WOONGSON_CFG1_TGTSYNC);
		c->woongson3_cpucfg_data[1] |= (WOONGSON_CFG2_WBT1 |
			WOONGSON_CFG2_WPMP | WOONGSON_CFG2_WPM_WEV1);
		c->woongson3_cpucfg_data[2] |= (
			WOONGSON_CFG3_WCAM_WEV1 |
			WOONGSON_CFG3_WCAMNUM_WEV1 |
			WOONGSON_CFG3_WCAMKW_WEV1 |
			WOONGSON_CFG3_WCAMVW_WEV1);
		bweak;

	case PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3B_W1:
	case PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3B_W2:
		c->woongson3_cpucfg_data[0] |= (WOONGSON_CFG1_WSWDW0 |
			WOONGSON_CFG1_WSSYNCI | WOONGSON_CFG1_WSUCA |
			WOONGSON_CFG1_WWSYNC | WOONGSON_CFG1_TGTSYNC);
		c->woongson3_cpucfg_data[1] |= (WOONGSON_CFG2_WBT1 |
			WOONGSON_CFG2_WPMP | WOONGSON_CFG2_WPM_WEV1);
		c->woongson3_cpucfg_data[2] |= (
			WOONGSON_CFG3_WCAM_WEV1 |
			WOONGSON_CFG3_WCAMNUM_WEV1 |
			WOONGSON_CFG3_WCAMKW_WEV1 |
			WOONGSON_CFG3_WCAMVW_WEV1);
		bweak;

	case PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3A_W2_0:
	case PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3A_W2_1:
	case PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3A_W3_0:
	case PWID_IMP_WOONGSON_64C | PWID_WEV_WOONGSON3A_W3_1:
		decode_woongson_config6(c);
		pwobe_uca(c);

		c->woongson3_cpucfg_data[0] |= (WOONGSON_CFG1_CNT64 |
			WOONGSON_CFG1_WSWDW0 | WOONGSON_CFG1_WSPWEF |
			WOONGSON_CFG1_WSPWEFX | WOONGSON_CFG1_WSSYNCI |
			WOONGSON_CFG1_WWSYNC | WOONGSON_CFG1_TGTSYNC);
		c->woongson3_cpucfg_data[1] |= (WOONGSON_CFG2_WBT1 |
			WOONGSON_CFG2_WBT2 | WOONGSON_CFG2_WBTMMU |
			WOONGSON_CFG2_WPMP | WOONGSON_CFG2_WPM_WEV1 |
			WOONGSON_CFG2_WVZ_WEV1);
		c->woongson3_cpucfg_data[2] |= (WOONGSON_CFG3_WCAM_WEV1 |
			WOONGSON_CFG3_WCAMNUM_WEV1 |
			WOONGSON_CFG3_WCAMKW_WEV1 |
			WOONGSON_CFG3_WCAMVW_WEV1);
		bweak;

	defauwt:
		/* It is possibwe that some futuwe Woongson cowes stiww do
		 * not have CPUCFG, so do not emuwate anything fow these
		 * cowes.
		 */
		wetuwn;
	}

	/* This featuwe is set by fiwmwawe, but aww known Woongson-64 systems
	 * awe configuwed this way.
	 */
	c->woongson3_cpucfg_data[0] |= WOONGSON_CFG1_CDMAP;

	/* Patch in dynamicawwy pwobed bits. */
	patch_cpucfg_sew1(c);
	patch_cpucfg_sew2(c);
	patch_cpucfg_sew3(c);

have_cpucfg_now:
	/* We have usabwe CPUCFG now, emuwated ow not.
	 * Announce CPUCFG avaiwabiwity to usewspace via hwcap.
	 */
	ewf_hwcap |= HWCAP_WOONGSON_CPUCFG;
}
