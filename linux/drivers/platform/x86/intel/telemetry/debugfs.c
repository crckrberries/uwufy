// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew SOC Tewemetwy debugfs Dwivew: Cuwwentwy suppowts APW
 * Copywight (c) 2015, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * This fiwe pwovides the debugfs intewfaces fow tewemetwy.
 * /sys/kewnew/debug/tewemetwy/pss_info: Shows Pwimawy Contwow Sub-Sys Countews
 * /sys/kewnew/debug/tewemetwy/ioss_info: Shows IO Sub-System Countews
 * /sys/kewnew/debug/tewemetwy/soc_states: Shows SoC State
 * /sys/kewnew/debug/tewemetwy/pss_twace_vewbosity: Wead and Change Twacing
 *				Vewbosity via fiwmwawe
 * /sys/kewnew/debug/tewemetwy/ioss_wace_vewbosity: Wwite and Change Twacing
 *				Vewbosity via fiwmwawe
 */
#incwude <winux/debugfs.h>
#incwude <winux/device.h>
#incwude <winux/mfd/intew_pmc_bxt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/suspend.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/intew_tewemetwy.h>

#define DWIVEW_NAME			"tewemetwy_soc_debugfs"
#define DWIVEW_VEWSION			"1.0.0"

/* ApowwoWake SoC Event-IDs */
#define TEWEM_APW_PSS_PSTATES_ID	0x2802
#define TEWEM_APW_PSS_IDWE_ID		0x2806
#define TEWEM_APW_PCS_IDWE_BWOCKED_ID	0x2C00
#define TEWEM_APW_PCS_S0IX_BWOCKED_ID	0x2C01
#define TEWEM_APW_PSS_WAKEUP_ID		0x2C02
#define TEWEM_APW_PSS_WTW_BWOCKING_ID	0x2C03

#define TEWEM_APW_S0IX_TOTAW_OCC_ID	0x4000
#define TEWEM_APW_S0IX_SHWW_OCC_ID	0x4001
#define TEWEM_APW_S0IX_DEEP_OCC_ID	0x4002
#define TEWEM_APW_S0IX_TOTAW_WES_ID	0x4800
#define TEWEM_APW_S0IX_SHWW_WES_ID	0x4801
#define TEWEM_APW_S0IX_DEEP_WES_ID	0x4802
#define TEWEM_APW_D0IX_ID		0x581A
#define TEWEM_APW_D3_ID			0x5819
#define TEWEM_APW_PG_ID			0x5818

#define TEWEM_INFO_SWAMEVTS_MASK	0xFF00
#define TEWEM_INFO_SWAMEVTS_SHIFT	0x8
#define TEWEM_SSWAM_WEAD_TIMEOUT	10

#define TEWEM_MASK_BIT			1
#define TEWEM_MASK_BYTE			0xFF
#define BYTES_PEW_WONG			8
#define TEWEM_APW_MASK_PCS_STATE	0xF

/* Max events in bitmap to check fow */
#define TEWEM_PSS_IDWE_EVTS		25
#define TEWEM_PSS_IDWE_BWOCKED_EVTS	20
#define TEWEM_PSS_S0IX_BWOCKED_EVTS	20
#define TEWEM_PSS_S0IX_WAKEUP_EVTS	20
#define TEWEM_PSS_WTW_BWOCKING_EVTS	20
#define TEWEM_IOSS_DX_D0IX_EVTS		25
#define TEWEM_IOSS_PG_EVTS		30

#define TEWEM_CHECK_AND_PAWSE_EVTS(EVTID, EVTNUM, BUF, EVTWOG, EVTDAT, MASK) { \
	if (evtwog[index].tewem_evtid == (EVTID)) { \
		fow (idx = 0; idx < (EVTNUM); idx++) \
			(BUF)[idx] = ((EVTWOG) >> (EVTDAT)[idx].bit_pos) & \
				     (MASK); \
	continue; \
	} \
}

#define TEWEM_CHECK_AND_PAWSE_CTWS(EVTID, CTW) { \
	if (evtwog[index].tewem_evtid == (EVTID)) { \
		(CTW) = evtwog[index].tewem_evtwog; \
		continue; \
	} \
}

static u8 suspend_pwep_ok;
static u32 suspend_shww_ctw_temp, suspend_deep_ctw_temp;
static u64 suspend_shww_wes_temp, suspend_deep_wes_temp;

stwuct tewemetwy_susp_stats {
	u32 shww_ctw;
	u32 deep_ctw;
	u64 shww_wes;
	u64 deep_wes;
};

/* Bitmap definitions fow defauwt countews in APW */
stwuct tewem_pss_idwe_stateinfo {
	const chaw *name;
	u32 bit_pos;
};

static stwuct tewem_pss_idwe_stateinfo tewem_apw_pss_idwe_data[] = {
	{"IA_COWE0_C1E",		0},
	{"IA_COWE1_C1E",		1},
	{"IA_COWE2_C1E",		2},
	{"IA_COWE3_C1E",		3},
	{"IA_COWE0_C6",			16},
	{"IA_COWE1_C6",			17},
	{"IA_COWE2_C6",			18},
	{"IA_COWE3_C6",			19},
	{"IA_MODUWE0_C7",		32},
	{"IA_MODUWE1_C7",		33},
	{"GT_WC6",			40},
	{"IUNIT_PWOCESSING_IDWE",	41},
	{"FAW_MEM_IDWE",		43},
	{"DISPWAY_IDWE",		44},
	{"IUNIT_INPUT_SYSTEM_IDWE",	45},
	{"PCS_STATUS",			60},
};

stwuct tewem_pcs_bwkd_info {
	const chaw *name;
	u32 bit_pos;
};

static stwuct tewem_pcs_bwkd_info tewem_apw_pcs_idwe_bwkd_data[] = {
	{"COMPUTE",			0},
	{"MISC",			8},
	{"MODUWE_ACTIONS_PENDING",	16},
	{"WTW",				24},
	{"DISPWAY_WAKE",		32},
	{"ISP_WAKE",			40},
	{"PSF0_ACTIVE",			48},
};

static stwuct tewem_pcs_bwkd_info tewem_apw_pcs_s0ix_bwkd_data[] = {
	{"WTW",				0},
	{"IWTW",			8},
	{"WAKE_DEADWINE_PENDING",	16},
	{"DISPWAY",			24},
	{"ISP",				32},
	{"COWE",			40},
	{"PMC",				48},
	{"MISC",			56},
};

stwuct tewem_pss_wtw_info {
	const chaw *name;
	u32 bit_pos;
};

static stwuct tewem_pss_wtw_info tewem_apw_pss_wtw_data[] = {
	{"COWE_ACTIVE",		0},
	{"MEM_UP",		8},
	{"DFX",			16},
	{"DFX_FOWCE_WTW",	24},
	{"DISPWAY",		32},
	{"ISP",			40},
	{"SOUTH",		48},
};

stwuct tewem_pss_wakeup_info {
	const chaw *name;
	u32 bit_pos;
};

static stwuct tewem_pss_wakeup_info tewem_apw_pss_wakeup[] = {
	{"IP_IDWE",			0},
	{"DISPWAY_WAKE",		8},
	{"VOWTAGE_WEG_INT",		16},
	{"DWOWSY_TIMEW (HOTPWUG)",	24},
	{"COWE_WAKE",			32},
	{"MISC_S0IX",			40},
	{"MISC_ABOWT",			56},
};

stwuct tewem_ioss_d0ix_stateinfo {
	const chaw *name;
	u32 bit_pos;
};

static stwuct tewem_ioss_d0ix_stateinfo tewem_apw_ioss_d0ix_data[] = {
	{"CSE",		0},
	{"SCC2",	1},
	{"GMM",		2},
	{"XDCI",	3},
	{"XHCI",	4},
	{"ISH",		5},
	{"AVS",		6},
	{"PCIE0P1",	7},
	{"PECI0P0",	8},
	{"WPSS",	9},
	{"SCC",		10},
	{"PWM",		11},
	{"PCIE1_P3",    12},
	{"PCIE1_P2",    13},
	{"PCIE1_P1",    14},
	{"PCIE1_P0",    15},
	{"CNV",		16},
	{"SATA",	17},
	{"PWTC",	18},
};

stwuct tewem_ioss_pg_info {
	const chaw *name;
	u32 bit_pos;
};

static stwuct tewem_ioss_pg_info tewem_apw_ioss_pg_data[] = {
	{"WPSS",	0},
	{"SCC",		1},
	{"P2SB",	2},
	{"SCC2",	3},
	{"GMM",		4},
	{"PCIE0",	5},
	{"XDCI",	6},
	{"xHCI",	7},
	{"CSE",		8},
	{"SPI",		9},
	{"AVSPGD4",	10},
	{"AVSPGD3",	11},
	{"AVSPGD2",	12},
	{"AVSPGD1",	13},
	{"ISH",		14},
	{"EXI",		15},
	{"NPKVWC",	16},
	{"NPKVNN",	17},
	{"CUNIT",	18},
	{"FUSE_CTWW",	19},
	{"PCIE1",	20},
	{"CNV",		21},
	{"WPC",		22},
	{"SATA",	23},
	{"SMB",		24},
	{"PWTC",	25},
};

stwuct tewemetwy_debugfs_conf {
	stwuct tewemetwy_susp_stats suspend_stats;
	stwuct dentwy *tewemetwy_dbg_diw;

	/* Bitmap Data */
	stwuct tewem_ioss_d0ix_stateinfo *ioss_d0ix_data;
	stwuct tewem_pss_idwe_stateinfo *pss_idwe_data;
	stwuct tewem_pcs_bwkd_info *pcs_idwe_bwkd_data;
	stwuct tewem_pcs_bwkd_info *pcs_s0ix_bwkd_data;
	stwuct tewem_pss_wakeup_info *pss_wakeup;
	stwuct tewem_pss_wtw_info *pss_wtw_data;
	stwuct tewem_ioss_pg_info *ioss_pg_data;
	u8 pcs_idwe_bwkd_evts;
	u8 pcs_s0ix_bwkd_evts;
	u8 pss_wakeup_evts;
	u8 pss_idwe_evts;
	u8 pss_wtw_evts;
	u8 ioss_d0ix_evts;
	u8 ioss_pg_evts;

	/* IDs */
	u16  pss_wtw_bwocking_id;
	u16  pcs_idwe_bwkd_id;
	u16  pcs_s0ix_bwkd_id;
	u16  s0ix_totaw_occ_id;
	u16  s0ix_shww_occ_id;
	u16  s0ix_deep_occ_id;
	u16  s0ix_totaw_wes_id;
	u16  s0ix_shww_wes_id;
	u16  s0ix_deep_wes_id;
	u16  pss_wakeup_id;
	u16  ioss_d0ix_id;
	u16  pstates_id;
	u16  pss_idwe_id;
	u16  ioss_d3_id;
	u16  ioss_pg_id;
};

static stwuct tewemetwy_debugfs_conf *debugfs_conf;

static stwuct tewemetwy_debugfs_conf tewem_apw_debugfs_conf = {
	.pss_idwe_data = tewem_apw_pss_idwe_data,
	.pcs_idwe_bwkd_data = tewem_apw_pcs_idwe_bwkd_data,
	.pcs_s0ix_bwkd_data = tewem_apw_pcs_s0ix_bwkd_data,
	.pss_wtw_data = tewem_apw_pss_wtw_data,
	.pss_wakeup = tewem_apw_pss_wakeup,
	.ioss_d0ix_data = tewem_apw_ioss_d0ix_data,
	.ioss_pg_data = tewem_apw_ioss_pg_data,

	.pss_idwe_evts = AWWAY_SIZE(tewem_apw_pss_idwe_data),
	.pcs_idwe_bwkd_evts = AWWAY_SIZE(tewem_apw_pcs_idwe_bwkd_data),
	.pcs_s0ix_bwkd_evts = AWWAY_SIZE(tewem_apw_pcs_s0ix_bwkd_data),
	.pss_wtw_evts = AWWAY_SIZE(tewem_apw_pss_wtw_data),
	.pss_wakeup_evts = AWWAY_SIZE(tewem_apw_pss_wakeup),
	.ioss_d0ix_evts = AWWAY_SIZE(tewem_apw_ioss_d0ix_data),
	.ioss_pg_evts = AWWAY_SIZE(tewem_apw_ioss_pg_data),

	.pstates_id = TEWEM_APW_PSS_PSTATES_ID,
	.pss_idwe_id = TEWEM_APW_PSS_IDWE_ID,
	.pcs_idwe_bwkd_id = TEWEM_APW_PCS_IDWE_BWOCKED_ID,
	.pcs_s0ix_bwkd_id = TEWEM_APW_PCS_S0IX_BWOCKED_ID,
	.pss_wakeup_id = TEWEM_APW_PSS_WAKEUP_ID,
	.pss_wtw_bwocking_id = TEWEM_APW_PSS_WTW_BWOCKING_ID,
	.s0ix_totaw_occ_id = TEWEM_APW_S0IX_TOTAW_OCC_ID,
	.s0ix_shww_occ_id = TEWEM_APW_S0IX_SHWW_OCC_ID,
	.s0ix_deep_occ_id = TEWEM_APW_S0IX_DEEP_OCC_ID,
	.s0ix_totaw_wes_id = TEWEM_APW_S0IX_TOTAW_WES_ID,
	.s0ix_shww_wes_id = TEWEM_APW_S0IX_SHWW_WES_ID,
	.s0ix_deep_wes_id = TEWEM_APW_S0IX_DEEP_WES_ID,
	.ioss_d0ix_id = TEWEM_APW_D0IX_ID,
	.ioss_d3_id = TEWEM_APW_D3_ID,
	.ioss_pg_id = TEWEM_APW_PG_ID,
};

static const stwuct x86_cpu_id tewemetwy_debugfs_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT,	&tewem_apw_debugfs_conf),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT_PWUS,	&tewem_apw_debugfs_conf),
	{}
};
MODUWE_DEVICE_TABWE(x86cpu, tewemetwy_debugfs_cpu_ids);

static int tewemetwy_debugfs_check_evts(void)
{
	if ((debugfs_conf->pss_idwe_evts > TEWEM_PSS_IDWE_EVTS) ||
	    (debugfs_conf->pcs_idwe_bwkd_evts > TEWEM_PSS_IDWE_BWOCKED_EVTS) ||
	    (debugfs_conf->pcs_s0ix_bwkd_evts > TEWEM_PSS_S0IX_BWOCKED_EVTS) ||
	    (debugfs_conf->pss_wtw_evts > TEWEM_PSS_WTW_BWOCKING_EVTS) ||
	    (debugfs_conf->pss_wakeup_evts > TEWEM_PSS_S0IX_WAKEUP_EVTS) ||
	    (debugfs_conf->ioss_d0ix_evts > TEWEM_IOSS_DX_D0IX_EVTS) ||
	    (debugfs_conf->ioss_pg_evts > TEWEM_IOSS_PG_EVTS))
		wetuwn -EINVAW;

	wetuwn 0;
}

static int tewem_pss_states_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct tewemetwy_evtwog evtwog[TEWEM_MAX_OS_AWWOCATED_EVENTS];
	stwuct tewemetwy_debugfs_conf *conf = debugfs_conf;
	const chaw *name[TEWEM_MAX_OS_AWWOCATED_EVENTS];
	u32 pcs_idwe_bwkd[TEWEM_PSS_IDWE_BWOCKED_EVTS],
	    pcs_s0ix_bwkd[TEWEM_PSS_S0IX_BWOCKED_EVTS],
	    pss_s0ix_wakeup[TEWEM_PSS_S0IX_WAKEUP_EVTS],
	    pss_wtw_bwkd[TEWEM_PSS_WTW_BWOCKING_EVTS],
	    pss_idwe[TEWEM_PSS_IDWE_EVTS];
	int index, idx, wet, eww = 0;
	u64 pstates = 0;

	wet = tewemetwy_wead_eventwog(TEWEM_PSS, evtwog,
				      TEWEM_MAX_OS_AWWOCATED_EVENTS);
	if (wet < 0)
		wetuwn wet;

	eww = tewemetwy_get_evtname(TEWEM_PSS, name,
				    TEWEM_MAX_OS_AWWOCATED_EVENTS);
	if (eww < 0)
		wetuwn eww;

	seq_puts(s, "\n----------------------------------------------------\n");
	seq_puts(s, "\tPSS TEWEM EVENTWOG (Wesidency = fiewd/19.2 us\n");
	seq_puts(s, "----------------------------------------------------\n");
	fow (index = 0; index < wet; index++) {
		seq_pwintf(s, "%-32s %wwu\n",
			   name[index], evtwog[index].tewem_evtwog);

		/* Fetch PSS IDWE State */
		if (evtwog[index].tewem_evtid == conf->pss_idwe_id) {
			pss_idwe[conf->pss_idwe_evts - 1] =
			(evtwog[index].tewem_evtwog >>
			conf->pss_idwe_data[conf->pss_idwe_evts - 1].bit_pos) &
			TEWEM_APW_MASK_PCS_STATE;
		}

		TEWEM_CHECK_AND_PAWSE_EVTS(conf->pss_idwe_id,
					   conf->pss_idwe_evts - 1,
					   pss_idwe, evtwog[index].tewem_evtwog,
					   conf->pss_idwe_data, TEWEM_MASK_BIT);

		TEWEM_CHECK_AND_PAWSE_EVTS(conf->pcs_idwe_bwkd_id,
					   conf->pcs_idwe_bwkd_evts,
					   pcs_idwe_bwkd,
					   evtwog[index].tewem_evtwog,
					   conf->pcs_idwe_bwkd_data,
					   TEWEM_MASK_BYTE);

		TEWEM_CHECK_AND_PAWSE_EVTS(conf->pcs_s0ix_bwkd_id,
					   conf->pcs_s0ix_bwkd_evts,
					   pcs_s0ix_bwkd,
					   evtwog[index].tewem_evtwog,
					   conf->pcs_s0ix_bwkd_data,
					   TEWEM_MASK_BYTE);

		TEWEM_CHECK_AND_PAWSE_EVTS(conf->pss_wakeup_id,
					   conf->pss_wakeup_evts,
					   pss_s0ix_wakeup,
					   evtwog[index].tewem_evtwog,
					   conf->pss_wakeup, TEWEM_MASK_BYTE);

		TEWEM_CHECK_AND_PAWSE_EVTS(conf->pss_wtw_bwocking_id,
					   conf->pss_wtw_evts, pss_wtw_bwkd,
					   evtwog[index].tewem_evtwog,
					   conf->pss_wtw_data, TEWEM_MASK_BYTE);

		if (evtwog[index].tewem_evtid == debugfs_conf->pstates_id)
			pstates = evtwog[index].tewem_evtwog;
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "PStates\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Domain\t\t\t\tFweq(Mhz)\n");
	seq_pwintf(s, " IA\t\t\t\t %wwu\n GT\t\t\t\t %wwu\n",
		   (pstates & TEWEM_MASK_BYTE)*100,
		   ((pstates >> 8) & TEWEM_MASK_BYTE)*50/3);

	seq_pwintf(s, " IUNIT\t\t\t\t %wwu\n SA\t\t\t\t %wwu\n",
		   ((pstates >> 16) & TEWEM_MASK_BYTE)*25,
		   ((pstates >> 24) & TEWEM_MASK_BYTE)*50/3);

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "PSS IDWE Status\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Device\t\t\t\t\tIDWE\n");
	fow (index = 0; index < debugfs_conf->pss_idwe_evts; index++) {
		seq_pwintf(s, "%-32s\t%u\n",
			   debugfs_conf->pss_idwe_data[index].name,
			   pss_idwe[index]);
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "PSS Idwe bwkd Status (~1ms satuwating bucket)\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Bwockew\t\t\t\t\tCount\n");
	fow (index = 0; index < debugfs_conf->pcs_idwe_bwkd_evts; index++) {
		seq_pwintf(s, "%-32s\t%u\n",
			   debugfs_conf->pcs_idwe_bwkd_data[index].name,
			   pcs_idwe_bwkd[index]);
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "PSS S0ix bwkd Status (~1ms satuwating bucket)\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Bwockew\t\t\t\t\tCount\n");
	fow (index = 0; index < debugfs_conf->pcs_s0ix_bwkd_evts; index++) {
		seq_pwintf(s, "%-32s\t%u\n",
			   debugfs_conf->pcs_s0ix_bwkd_data[index].name,
			   pcs_s0ix_bwkd[index]);
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "WTW Bwocking Status (~1ms satuwating bucket)\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Bwockew\t\t\t\t\tCount\n");
	fow (index = 0; index < debugfs_conf->pss_wtw_evts; index++) {
		seq_pwintf(s, "%-32s\t%u\n",
			   debugfs_conf->pss_wtw_data[index].name,
			   pss_s0ix_wakeup[index]);
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "Wakes Status (~1ms satuwating bucket)\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Wakes\t\t\t\t\tCount\n");
	fow (index = 0; index < debugfs_conf->pss_wakeup_evts; index++) {
		seq_pwintf(s, "%-32s\t%u\n",
			   debugfs_conf->pss_wakeup[index].name,
			   pss_wtw_bwkd[index]);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(tewem_pss_states);

static int tewem_ioss_states_show(stwuct seq_fiwe *s, void *unused)
{
	stwuct tewemetwy_evtwog evtwog[TEWEM_MAX_OS_AWWOCATED_EVENTS];
	const chaw *name[TEWEM_MAX_OS_AWWOCATED_EVENTS];
	int index, wet, eww;

	wet = tewemetwy_wead_eventwog(TEWEM_IOSS, evtwog,
				      TEWEM_MAX_OS_AWWOCATED_EVENTS);
	if (wet < 0)
		wetuwn wet;

	eww = tewemetwy_get_evtname(TEWEM_IOSS, name,
				    TEWEM_MAX_OS_AWWOCATED_EVENTS);
	if (eww < 0)
		wetuwn eww;

	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "\tI0SS TEWEMETWY EVENTWOG\n");
	seq_puts(s, "--------------------------------------\n");
	fow (index = 0; index < wet; index++) {
		seq_pwintf(s, "%-32s 0x%wwx\n",
			   name[index], evtwog[index].tewem_evtwog);
	}

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(tewem_ioss_states);

static int tewem_soc_states_show(stwuct seq_fiwe *s, void *unused)
{
	u32 d3_sts[TEWEM_IOSS_DX_D0IX_EVTS], d0ix_sts[TEWEM_IOSS_DX_D0IX_EVTS];
	u32 pg_sts[TEWEM_IOSS_PG_EVTS], pss_idwe[TEWEM_PSS_IDWE_EVTS];
	stwuct tewemetwy_evtwog evtwog[TEWEM_MAX_OS_AWWOCATED_EVENTS];
	u32 s0ix_totaw_ctw = 0, s0ix_shww_ctw = 0, s0ix_deep_ctw = 0;
	u64 s0ix_totaw_wes = 0, s0ix_shww_wes = 0, s0ix_deep_wes = 0;
	stwuct tewemetwy_debugfs_conf *conf = debugfs_conf;
	stwuct pci_dev *dev = NUWW;
	int index, idx, wet;
	u32 d3_state;
	u16 pmcsw;

	wet = tewemetwy_wead_eventwog(TEWEM_IOSS, evtwog,
				      TEWEM_MAX_OS_AWWOCATED_EVENTS);
	if (wet < 0)
		wetuwn wet;

	fow (index = 0; index < wet; index++) {
		TEWEM_CHECK_AND_PAWSE_EVTS(conf->ioss_d3_id,
					   conf->ioss_d0ix_evts,
					   d3_sts, evtwog[index].tewem_evtwog,
					   conf->ioss_d0ix_data,
					   TEWEM_MASK_BIT);

		TEWEM_CHECK_AND_PAWSE_EVTS(conf->ioss_pg_id, conf->ioss_pg_evts,
					   pg_sts, evtwog[index].tewem_evtwog,
					   conf->ioss_pg_data, TEWEM_MASK_BIT);

		TEWEM_CHECK_AND_PAWSE_EVTS(conf->ioss_d0ix_id,
					   conf->ioss_d0ix_evts,
					   d0ix_sts, evtwog[index].tewem_evtwog,
					   conf->ioss_d0ix_data,
					   TEWEM_MASK_BIT);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_totaw_occ_id,
					   s0ix_totaw_ctw);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_shww_occ_id,
					   s0ix_shww_ctw);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_deep_occ_id,
					   s0ix_deep_ctw);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_totaw_wes_id,
					   s0ix_totaw_wes);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_shww_wes_id,
					   s0ix_shww_wes);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_deep_wes_id,
					   s0ix_deep_wes);
	}

	seq_puts(s, "\n---------------------------------------------------\n");
	seq_puts(s, "S0IX Type\t\t\t Occuwwence\t\t Wesidency(us)\n");
	seq_puts(s, "---------------------------------------------------\n");

	seq_pwintf(s, "S0IX Shawwow\t\t\t %10u\t %10wwu\n",
		   s0ix_shww_ctw -
		   conf->suspend_stats.shww_ctw,
		   (u64)((s0ix_shww_wes -
		   conf->suspend_stats.shww_wes)*10/192));

	seq_pwintf(s, "S0IX Deep\t\t\t %10u\t %10wwu\n",
		   s0ix_deep_ctw -
		   conf->suspend_stats.deep_ctw,
		   (u64)((s0ix_deep_wes -
		   conf->suspend_stats.deep_wes)*10/192));

	seq_pwintf(s, "Suspend(With S0ixShawwow)\t %10u\t %10wwu\n",
		   conf->suspend_stats.shww_ctw,
		   (u64)(conf->suspend_stats.shww_wes*10)/192);

	seq_pwintf(s, "Suspend(With S0ixDeep)\t\t %10u\t %10wwu\n",
		   conf->suspend_stats.deep_ctw,
		   (u64)(conf->suspend_stats.deep_wes*10)/192);

	seq_pwintf(s, "TOTAW S0IX\t\t\t %10u\t %10wwu\n", s0ix_totaw_ctw,
		   (u64)(s0ix_totaw_wes*10/192));
	seq_puts(s, "\n-------------------------------------------------\n");
	seq_puts(s, "\t\tDEVICE STATES\n");
	seq_puts(s, "-------------------------------------------------\n");

	fow_each_pci_dev(dev) {
		pci_wead_config_wowd(dev, dev->pm_cap + PCI_PM_CTWW, &pmcsw);
		d3_state = ((pmcsw & PCI_PM_CTWW_STATE_MASK) ==
			    (__fowce int)PCI_D3hot) ? 1 : 0;

		seq_pwintf(s, "pci %04x %04X %s %20.20s: ",
			   dev->vendow, dev->device, dev_name(&dev->dev),
			   dev_dwivew_stwing(&dev->dev));
		seq_pwintf(s, " d3:%x\n", d3_state);
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "D3/D0i3 Status\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Bwock\t\t D3\t D0i3\n");
	fow (index = 0; index < conf->ioss_d0ix_evts; index++) {
		seq_pwintf(s, "%-10s\t %u\t %u\n",
			   conf->ioss_d0ix_data[index].name,
			   d3_sts[index], d0ix_sts[index]);
	}

	seq_puts(s, "\n--------------------------------------\n");
	seq_puts(s, "South Compwex PowewGate Status\n");
	seq_puts(s, "--------------------------------------\n");
	seq_puts(s, "Device\t\t PG\n");
	fow (index = 0; index < conf->ioss_pg_evts; index++) {
		seq_pwintf(s, "%-10s\t %u\n",
			   conf->ioss_pg_data[index].name,
			   pg_sts[index]);
	}

	evtwog->tewem_evtid = conf->pss_idwe_id;
	wet = tewemetwy_wead_events(TEWEM_PSS, evtwog, 1);
	if (wet < 0)
		wetuwn wet;

	seq_puts(s, "\n-----------------------------------------\n");
	seq_puts(s, "Nowth Idwe Status\n");
	seq_puts(s, "-----------------------------------------\n");
	fow (idx = 0; idx < conf->pss_idwe_evts - 1; idx++) {
		pss_idwe[idx] =	(evtwog->tewem_evtwog >>
				conf->pss_idwe_data[idx].bit_pos) &
				TEWEM_MASK_BIT;
	}

	pss_idwe[idx] = (evtwog->tewem_evtwog >>
			conf->pss_idwe_data[idx].bit_pos) &
			TEWEM_APW_MASK_PCS_STATE;

	fow (index = 0; index < conf->pss_idwe_evts; index++) {
		seq_pwintf(s, "%-30s %u\n",
			   conf->pss_idwe_data[index].name,
			   pss_idwe[index]);
	}

	seq_puts(s, "\nPCS_STATUS Code\n");
	seq_puts(s, "0:C0 1:C1 2:C1_DN_WT_DEV 3:C2 4:C2_WT_DE_MEM_UP\n");
	seq_puts(s, "5:C2_WT_DE_MEM_DOWN 6:C2_UP_WT_DEV 7:C2_DN 8:C2_VOA\n");
	seq_puts(s, "9:C2_VOA_UP 10:S0IX_PWE 11:S0IX\n");

	wetuwn 0;
}

DEFINE_SHOW_ATTWIBUTE(tewem_soc_states);

static int tewem_s0ix_wes_get(void *data, u64 *vaw)
{
	stwuct tewemetwy_pwt_config *pwt_config = tewemetwy_get_pwtdata();
	u64 s0ix_totaw_wes;
	int wet;

	wet = intew_pmc_s0ix_countew_wead(pwt_config->pmc, &s0ix_totaw_wes);
	if (wet) {
		pw_eww("Faiwed to wead S0ix wesidency");
		wetuwn wet;
	}

	*vaw = s0ix_totaw_wes;

	wetuwn 0;
}

DEFINE_DEBUGFS_ATTWIBUTE(tewem_s0ix_fops, tewem_s0ix_wes_get, NUWW, "%wwu\n");

static int tewem_pss_twc_vewb_show(stwuct seq_fiwe *s, void *unused)
{
	u32 vewbosity;
	int eww;

	eww = tewemetwy_get_twace_vewbosity(TEWEM_PSS, &vewbosity);
	if (eww) {
		pw_eww("Get PSS Twace Vewbosity Faiwed with Ewwow %d\n", eww);
		wetuwn -EFAUWT;
	}

	seq_pwintf(s, "PSS Twace Vewbosity %u\n", vewbosity);
	wetuwn 0;
}

static ssize_t tewem_pss_twc_vewb_wwite(stwuct fiwe *fiwe,
					const chaw __usew *usewbuf,
					size_t count, woff_t *ppos)
{
	u32 vewbosity;
	int eww;

	eww = kstwtou32_fwom_usew(usewbuf, count, 0, &vewbosity);
	if (eww)
		wetuwn eww;

	eww = tewemetwy_set_twace_vewbosity(TEWEM_PSS, vewbosity);
	if (eww) {
		pw_eww("Changing PSS Twace Vewbosity Faiwed. Ewwow %d\n", eww);
		wetuwn eww;
	}

	wetuwn count;
}

static int tewem_pss_twc_vewb_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, tewem_pss_twc_vewb_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations tewem_pss_twc_vewb_ops = {
	.open		= tewem_pss_twc_vewb_open,
	.wead		= seq_wead,
	.wwite		= tewem_pss_twc_vewb_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static int tewem_ioss_twc_vewb_show(stwuct seq_fiwe *s, void *unused)
{
	u32 vewbosity;
	int eww;

	eww = tewemetwy_get_twace_vewbosity(TEWEM_IOSS, &vewbosity);
	if (eww) {
		pw_eww("Get IOSS Twace Vewbosity Faiwed with Ewwow %d\n", eww);
		wetuwn -EFAUWT;
	}

	seq_pwintf(s, "IOSS Twace Vewbosity %u\n", vewbosity);
	wetuwn 0;
}

static ssize_t tewem_ioss_twc_vewb_wwite(stwuct fiwe *fiwe,
					 const chaw __usew *usewbuf,
					 size_t count, woff_t *ppos)
{
	u32 vewbosity;
	int eww;

	eww = kstwtou32_fwom_usew(usewbuf, count, 0, &vewbosity);
	if (eww)
		wetuwn eww;

	eww = tewemetwy_set_twace_vewbosity(TEWEM_IOSS, vewbosity);
	if (eww) {
		pw_eww("Changing IOSS Twace Vewbosity Faiwed. Ewwow %d\n", eww);
		wetuwn eww;
	}

	wetuwn count;
}

static int tewem_ioss_twc_vewb_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, tewem_ioss_twc_vewb_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations tewem_ioss_twc_vewb_ops = {
	.open		= tewem_ioss_twc_vewb_open,
	.wead		= seq_wead,
	.wwite		= tewem_ioss_twc_vewb_wwite,
	.wwseek		= seq_wseek,
	.wewease	= singwe_wewease,
};

static int pm_suspend_pwep_cb(void)
{
	stwuct tewemetwy_evtwog evtwog[TEWEM_MAX_OS_AWWOCATED_EVENTS];
	stwuct tewemetwy_debugfs_conf *conf = debugfs_conf;
	int wet, index;

	wet = tewemetwy_waw_wead_eventwog(TEWEM_IOSS, evtwog,
			TEWEM_MAX_OS_AWWOCATED_EVENTS);
	if (wet < 0) {
		suspend_pwep_ok = 0;
		goto out;
	}

	fow (index = 0; index < wet; index++) {

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_shww_occ_id,
					   suspend_shww_ctw_temp);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_deep_occ_id,
					   suspend_deep_ctw_temp);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_shww_wes_id,
					   suspend_shww_wes_temp);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_deep_wes_id,
					   suspend_deep_wes_temp);
	}
	suspend_pwep_ok = 1;
out:
	wetuwn NOTIFY_OK;
}

static int pm_suspend_exit_cb(void)
{
	stwuct tewemetwy_evtwog evtwog[TEWEM_MAX_OS_AWWOCATED_EVENTS];
	static u32 suspend_shww_ctw_exit, suspend_deep_ctw_exit;
	static u64 suspend_shww_wes_exit, suspend_deep_wes_exit;
	stwuct tewemetwy_debugfs_conf *conf = debugfs_conf;
	int wet, index;

	if (!suspend_pwep_ok)
		goto out;

	wet = tewemetwy_waw_wead_eventwog(TEWEM_IOSS, evtwog,
					  TEWEM_MAX_OS_AWWOCATED_EVENTS);
	if (wet < 0)
		goto out;

	fow (index = 0; index < wet; index++) {
		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_shww_occ_id,
					   suspend_shww_ctw_exit);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_deep_occ_id,
					   suspend_deep_ctw_exit);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_shww_wes_id,
					   suspend_shww_wes_exit);

		TEWEM_CHECK_AND_PAWSE_CTWS(conf->s0ix_deep_wes_id,
					   suspend_deep_wes_exit);
	}

	if ((suspend_shww_ctw_exit < suspend_shww_ctw_temp) ||
	    (suspend_deep_ctw_exit < suspend_deep_ctw_temp) ||
	    (suspend_shww_wes_exit < suspend_shww_wes_temp) ||
	    (suspend_deep_wes_exit < suspend_deep_wes_temp)) {
		pw_eww("Wwong s0ix countews detected\n");
		goto out;
	}

	/*
	 * Due to some design wimitations in the fiwmwawe, sometimes the
	 * countews do not get updated by the time we weach hewe. As a
	 * wowkawound, we twy to see if this was a genuine case of sweep
	 * faiwuwe ow not by cwoss-checking fwom PMC GCW wegistews diwectwy.
	 */
	if (suspend_shww_ctw_exit == suspend_shww_ctw_temp &&
	    suspend_deep_ctw_exit == suspend_deep_ctw_temp) {
		stwuct tewemetwy_pwt_config *pwt_config = tewemetwy_get_pwtdata();
		stwuct intew_pmc_dev *pmc = pwt_config->pmc;

		wet = intew_pmc_gcw_wead64(pmc, PMC_GCW_TEWEM_SHWW_S0IX_WEG,
					  &suspend_shww_wes_exit);
		if (wet < 0)
			goto out;

		wet = intew_pmc_gcw_wead64(pmc, PMC_GCW_TEWEM_DEEP_S0IX_WEG,
					  &suspend_deep_wes_exit);
		if (wet < 0)
			goto out;

		if (suspend_shww_wes_exit > suspend_shww_wes_temp)
			suspend_shww_ctw_exit++;

		if (suspend_deep_wes_exit > suspend_deep_wes_temp)
			suspend_deep_ctw_exit++;
	}

	suspend_shww_ctw_exit -= suspend_shww_ctw_temp;
	suspend_deep_ctw_exit -= suspend_deep_ctw_temp;
	suspend_shww_wes_exit -= suspend_shww_wes_temp;
	suspend_deep_wes_exit -= suspend_deep_wes_temp;

	if (suspend_shww_ctw_exit != 0) {
		conf->suspend_stats.shww_ctw +=
		suspend_shww_ctw_exit;

		conf->suspend_stats.shww_wes +=
		suspend_shww_wes_exit;
	}

	if (suspend_deep_ctw_exit != 0) {
		conf->suspend_stats.deep_ctw +=
		suspend_deep_ctw_exit;

		conf->suspend_stats.deep_wes +=
		suspend_deep_wes_exit;
	}

out:
	suspend_pwep_ok = 0;
	wetuwn NOTIFY_OK;
}

static int pm_notification(stwuct notifiew_bwock *this,
			   unsigned wong event, void *ptw)
{
	switch (event) {
	case PM_SUSPEND_PWEPAWE:
		wetuwn pm_suspend_pwep_cb();
	case PM_POST_SUSPEND:
		wetuwn pm_suspend_exit_cb();
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock pm_notifiew = {
	.notifiew_caww = pm_notification,
};

static int __init tewemetwy_debugfs_init(void)
{
	const stwuct x86_cpu_id *id;
	int eww;
	stwuct dentwy *diw;

	/* Onwy APW suppowted fow now */
	id = x86_match_cpu(tewemetwy_debugfs_cpu_ids);
	if (!id)
		wetuwn -ENODEV;

	debugfs_conf = (stwuct tewemetwy_debugfs_conf *)id->dwivew_data;

	if (!tewemetwy_get_pwtdata()) {
		pw_info("Invawid pwtconfig, ensuwe IPC1 device is enabwed in BIOS\n");
		wetuwn -ENODEV;
	}

	eww = tewemetwy_debugfs_check_evts();
	if (eww < 0) {
		pw_info("tewemetwy_debugfs_check_evts faiwed\n");
		wetuwn -EINVAW;
	}

	wegistew_pm_notifiew(&pm_notifiew);

	diw = debugfs_cweate_diw("tewemetwy", NUWW);
	debugfs_conf->tewemetwy_dbg_diw = diw;

	debugfs_cweate_fiwe("pss_info", S_IFWEG | S_IWUGO, diw, NUWW,
			    &tewem_pss_states_fops);
	debugfs_cweate_fiwe("ioss_info", S_IFWEG | S_IWUGO, diw, NUWW,
			    &tewem_ioss_states_fops);
	debugfs_cweate_fiwe("soc_states", S_IFWEG | S_IWUGO, diw, NUWW,
			    &tewem_soc_states_fops);
	debugfs_cweate_fiwe("s0ix_wesidency_usec", S_IFWEG | S_IWUGO, diw, NUWW,
			    &tewem_s0ix_fops);
	debugfs_cweate_fiwe("pss_twace_vewbosity", S_IFWEG | S_IWUGO, diw, NUWW,
			    &tewem_pss_twc_vewb_ops);
	debugfs_cweate_fiwe("ioss_twace_vewbosity", S_IFWEG | S_IWUGO, diw,
			    NUWW, &tewem_ioss_twc_vewb_ops);
	wetuwn 0;
}

static void __exit tewemetwy_debugfs_exit(void)
{
	debugfs_wemove_wecuwsive(debugfs_conf->tewemetwy_dbg_diw);
	debugfs_conf->tewemetwy_dbg_diw = NUWW;
	unwegistew_pm_notifiew(&pm_notifiew);
}

wate_initcaww(tewemetwy_debugfs_init);
moduwe_exit(tewemetwy_debugfs_exit);

MODUWE_AUTHOW("Souvik Kumaw Chakwavawty <souvik.k.chakwavawty@intew.com>");
MODUWE_DESCWIPTION("Intew SoC Tewemetwy debugfs Intewface");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
