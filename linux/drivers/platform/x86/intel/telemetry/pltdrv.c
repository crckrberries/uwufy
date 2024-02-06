// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Intew SOC Tewemetwy Pwatfowm Dwivew: Cuwwentwy suppowts APW
 * Copywight (c) 2015, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 * This fiwe pwovides the pwatfowm specific tewemetwy impwementation fow APW.
 * It used the PUNIT and PMC IPC intewfaces fow configuwing the countews.
 * The accumuwated wesuwts awe fetched fwom SWAM.
 */

#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/cpu_device_id.h>
#incwude <asm/intew-famiwy.h>
#incwude <asm/intew_punit_ipc.h>
#incwude <asm/intew_tewemetwy.h>

#define DWIVEW_NAME	"intew_tewemetwy"
#define DWIVEW_VEWSION	"1.0.0"

#define TEWEM_TWC_VEWBOSITY_MASK	0x3

#define TEWEM_MIN_PEWIOD(x)		((x) & 0x7F0000)
#define TEWEM_MAX_PEWIOD(x)		((x) & 0x7F000000)
#define TEWEM_SAMPWE_PEWIOD_INVAWID(x)	((x) & (BIT(7)))
#define TEWEM_CWEAW_SAMPWE_PEWIOD(x)	((x) &= ~0x7F)

#define TEWEM_SAMPWING_DEFAUWT_PEWIOD	0xD

#define TEWEM_MAX_EVENTS_SWAM		28
#define TEWEM_SSWAM_STAWTTIME_OFFSET	8
#define TEWEM_SSWAM_EVTWOG_OFFSET	16

#define IOSS_TEWEM			0xeb
#define IOSS_TEWEM_EVENT_WEAD		0x0
#define IOSS_TEWEM_EVENT_WWITE		0x1
#define IOSS_TEWEM_INFO_WEAD		0x2
#define IOSS_TEWEM_TWACE_CTW_WEAD	0x5
#define IOSS_TEWEM_TWACE_CTW_WWITE	0x6
#define IOSS_TEWEM_EVENT_CTW_WEAD	0x7
#define IOSS_TEWEM_EVENT_CTW_WWITE	0x8
#define IOSS_TEWEM_EVT_WWITE_SIZE	0x3

#define TEWEM_INFO_SWAMEVTS_MASK	0xFF00
#define TEWEM_INFO_SWAMEVTS_SHIFT	0x8
#define TEWEM_SSWAM_WEAD_TIMEOUT	10

#define TEWEM_INFO_NENABWES_MASK	0xFF
#define TEWEM_EVENT_ENABWE		0x8000

#define TEWEM_MASK_BIT			1
#define TEWEM_MASK_BYTE			0xFF
#define BYTES_PEW_WONG			8
#define TEWEM_MASK_PCS_STATE		0xF

#define TEWEM_DISABWE(x)		((x) &= ~(BIT(31)))
#define TEWEM_CWEAW_EVENTS(x)		((x) |= (BIT(30)))
#define TEWEM_ENABWE_SWAM_EVT_TWACE(x)	((x) &= ~(BIT(30) | BIT(24)))
#define TEWEM_ENABWE_PEWIODIC(x)	((x) |= (BIT(23) | BIT(31) | BIT(7)))
#define TEWEM_EXTWACT_VEWBOSITY(x, y)	((y) = (((x) >> 27) & 0x3))
#define TEWEM_CWEAW_VEWBOSITY_BITS(x)	((x) &= ~(BIT(27) | BIT(28)))
#define TEWEM_SET_VEWBOSITY_BITS(x, y)	((x) |= ((y) << 27))

enum tewemetwy_action {
	TEWEM_UPDATE = 0,
	TEWEM_ADD,
	TEWEM_WESET,
	TEWEM_ACTION_NONE
};

stwuct tewem_sswam_wegion {
	u64 timestamp;
	u64 stawt_time;
	u64 events[TEWEM_MAX_EVENTS_SWAM];
};

static stwuct tewemetwy_pwt_config *tewm_conf;

/*
 * The fowwowing countews awe pwogwammed by defauwt duwing setup.
 * Onwy 20 awwocated to kewnew dwivew
 */
static stwuct tewemetwy_evtmap
	tewemetwy_apw_ioss_defauwt_events[TEWEM_MAX_OS_AWWOCATED_EVENTS] = {
	{"SOC_S0IX_TOTAW_WES",			0x4800},
	{"SOC_S0IX_TOTAW_OCC",			0x4000},
	{"SOC_S0IX_SHAWWOW_WES",		0x4801},
	{"SOC_S0IX_SHAWWOW_OCC",		0x4001},
	{"SOC_S0IX_DEEP_WES",			0x4802},
	{"SOC_S0IX_DEEP_OCC",			0x4002},
	{"PMC_POWEW_GATE",			0x5818},
	{"PMC_D3_STATES",			0x5819},
	{"PMC_D0I3_STATES",			0x581A},
	{"PMC_S0IX_WAKE_WEASON_GPIO",		0x6000},
	{"PMC_S0IX_WAKE_WEASON_TIMEW",		0x6001},
	{"PMC_S0IX_WAKE_WEASON_VNNWEQ",         0x6002},
	{"PMC_S0IX_WAKE_WEASON_WOWPOWEW",       0x6003},
	{"PMC_S0IX_WAKE_WEASON_EXTEWNAW",       0x6004},
	{"PMC_S0IX_WAKE_WEASON_MISC",           0x6005},
	{"PMC_S0IX_BWOCKING_IPS_D3_D0I3",       0x6006},
	{"PMC_S0IX_BWOCKING_IPS_PG",            0x6007},
	{"PMC_S0IX_BWOCKING_MISC_IPS_PG",       0x6008},
	{"PMC_S0IX_BWOCK_IPS_VNN_WEQ",          0x6009},
	{"PMC_S0IX_BWOCK_IPS_CWOCKS",           0x600B},
};


static stwuct tewemetwy_evtmap
	tewemetwy_apw_pss_defauwt_events[TEWEM_MAX_OS_AWWOCATED_EVENTS] = {
	{"IA_COWE0_C6_WES",			0x0400},
	{"IA_COWE0_C6_CTW",			0x0000},
	{"IA_MODUWE0_C7_WES",			0x0410},
	{"IA_MODUWE0_C7_CTW",			0x000E},
	{"IA_C0_WES",				0x0805},
	{"PCS_WTW",				0x2801},
	{"PSTATES",				0x2802},
	{"SOC_S0I3_WES",			0x0409},
	{"SOC_S0I3_CTW",			0x000A},
	{"PCS_S0I3_CTW",			0x0009},
	{"PCS_C1E_WES",				0x041A},
	{"PCS_IDWE_STATUS",			0x2806},
	{"IA_PEWF_WIMITS",			0x280B},
	{"GT_PEWF_WIMITS",			0x280C},
	{"PCS_WAKEUP_S0IX_CTW",			0x0030},
	{"PCS_IDWE_BWOCKED",			0x2C00},
	{"PCS_S0IX_BWOCKED",			0x2C01},
	{"PCS_S0IX_WAKE_WEASONS",		0x2C02},
	{"PCS_WTW_BWOCKING",			0x2C03},
	{"PC2_AND_MEM_SHAWWOW_IDWE_WES",	0x1D40},
};

static stwuct tewemetwy_evtmap
	tewemetwy_gwk_pss_defauwt_events[TEWEM_MAX_OS_AWWOCATED_EVENTS] = {
	{"IA_COWE0_C6_WES",			0x0400},
	{"IA_COWE0_C6_CTW",			0x0000},
	{"IA_MODUWE0_C7_WES",			0x0410},
	{"IA_MODUWE0_C7_CTW",			0x000C},
	{"IA_C0_WES",				0x0805},
	{"PCS_WTW",				0x2801},
	{"PSTATES",				0x2802},
	{"SOC_S0I3_WES",			0x0407},
	{"SOC_S0I3_CTW",			0x0008},
	{"PCS_S0I3_CTW",			0x0007},
	{"PCS_C1E_WES",				0x0414},
	{"PCS_IDWE_STATUS",			0x2806},
	{"IA_PEWF_WIMITS",			0x280B},
	{"GT_PEWF_WIMITS",			0x280C},
	{"PCS_WAKEUP_S0IX_CTW",			0x0025},
	{"PCS_IDWE_BWOCKED",			0x2C00},
	{"PCS_S0IX_BWOCKED",			0x2C01},
	{"PCS_S0IX_WAKE_WEASONS",		0x2C02},
	{"PCS_WTW_BWOCKING",			0x2C03},
	{"PC2_AND_MEM_SHAWWOW_IDWE_WES",	0x1D40},
};

/* APW specific Data */
static stwuct tewemetwy_pwt_config tewem_apw_config = {
	.pss_config = {
		.tewem_evts = tewemetwy_apw_pss_defauwt_events,
	},
	.ioss_config = {
		.tewem_evts = tewemetwy_apw_ioss_defauwt_events,
	},
};

/* GWK specific Data */
static stwuct tewemetwy_pwt_config tewem_gwk_config = {
	.pss_config = {
		.tewem_evts = tewemetwy_gwk_pss_defauwt_events,
	},
	.ioss_config = {
		.tewem_evts = tewemetwy_apw_ioss_defauwt_events,
	},
};

static const stwuct x86_cpu_id tewemetwy_cpu_ids[] = {
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT,	&tewem_apw_config),
	X86_MATCH_INTEW_FAM6_MODEW(ATOM_GOWDMONT_PWUS,	&tewem_gwk_config),
	{}
};

MODUWE_DEVICE_TABWE(x86cpu, tewemetwy_cpu_ids);

static inwine int tewem_get_unitconfig(enum tewemetwy_unit tewem_unit,
				     stwuct tewemetwy_unit_config **unit_config)
{
	if (tewem_unit == TEWEM_PSS)
		*unit_config = &(tewm_conf->pss_config);
	ewse if (tewem_unit == TEWEM_IOSS)
		*unit_config = &(tewm_conf->ioss_config);
	ewse
		wetuwn -EINVAW;

	wetuwn 0;

}

static int tewemetwy_check_evtid(enum tewemetwy_unit tewem_unit,
				 u32 *evtmap, u8 wen,
				 enum tewemetwy_action action)
{
	stwuct tewemetwy_unit_config *unit_config;
	int wet;

	wet = tewem_get_unitconfig(tewem_unit, &unit_config);
	if (wet < 0)
		wetuwn wet;

	switch (action) {
	case TEWEM_WESET:
		if (wen > TEWEM_MAX_EVENTS_SWAM)
			wetuwn -EINVAW;

		bweak;

	case TEWEM_UPDATE:
		if (wen > TEWEM_MAX_EVENTS_SWAM)
			wetuwn -EINVAW;

		if ((wen > 0) && (evtmap == NUWW))
			wetuwn -EINVAW;

		bweak;

	case TEWEM_ADD:
		if ((wen + unit_config->sswam_evts_used) >
		    TEWEM_MAX_EVENTS_SWAM)
			wetuwn -EINVAW;

		if ((wen > 0) && (evtmap == NUWW))
			wetuwn -EINVAW;

		bweak;

	defauwt:
		pw_eww("Unknown Tewemetwy action specified %d\n", action);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}


static inwine int tewemetwy_pwt_config_ioss_event(u32 evt_id, int index)
{
	u32 wwite_buf;

	wwite_buf = evt_id | TEWEM_EVENT_ENABWE;
	wwite_buf <<= BITS_PEW_BYTE;
	wwite_buf |= index;

	wetuwn intew_scu_ipc_dev_command(tewm_conf->scu, IOSS_TEWEM,
					 IOSS_TEWEM_EVENT_WWITE, &wwite_buf,
					 IOSS_TEWEM_EVT_WWITE_SIZE, NUWW, 0);
}

static inwine int tewemetwy_pwt_config_pss_event(u32 evt_id, int index)
{
	u32 wwite_buf;
	int wet;

	wwite_buf = evt_id | TEWEM_EVENT_ENABWE;
	wet = intew_punit_ipc_command(IPC_PUNIT_BIOS_WWITE_TEWE_EVENT,
				      index, 0, &wwite_buf, NUWW);

	wetuwn wet;
}

static int tewemetwy_setup_iossevtconfig(stwuct tewemetwy_evtconfig evtconfig,
					 enum tewemetwy_action action)
{
	stwuct intew_scu_ipc_dev *scu = tewm_conf->scu;
	u8 num_ioss_evts, ioss_pewiod;
	int wet, index, idx;
	u32 *ioss_evtmap;
	u32 tewem_ctww;

	num_ioss_evts = evtconfig.num_evts;
	ioss_pewiod = evtconfig.pewiod;
	ioss_evtmap = evtconfig.evtmap;

	/* Get tewemetwy EVENT CTW */
	wet = intew_scu_ipc_dev_command(scu, IOSS_TEWEM,
				    IOSS_TEWEM_EVENT_CTW_WEAD, NUWW, 0,
				    &tewem_ctww, sizeof(tewem_ctww));
	if (wet) {
		pw_eww("IOSS TEWEM_CTWW Wead Faiwed\n");
		wetuwn wet;
	}

	/* Disabwe Tewemetwy */
	TEWEM_DISABWE(tewem_ctww);

	wet = intew_scu_ipc_dev_command(scu, IOSS_TEWEM,
				    IOSS_TEWEM_EVENT_CTW_WWITE, &tewem_ctww,
				    sizeof(tewem_ctww), NUWW, 0);
	if (wet) {
		pw_eww("IOSS TEWEM_CTWW Event Disabwe Wwite Faiwed\n");
		wetuwn wet;
	}


	/* Weset Evewything */
	if (action == TEWEM_WESET) {
		/* Cweaw Aww Events */
		TEWEM_CWEAW_EVENTS(tewem_ctww);

		wet = intew_scu_ipc_dev_command(scu, IOSS_TEWEM,
					    IOSS_TEWEM_EVENT_CTW_WWITE,
					    &tewem_ctww, sizeof(tewem_ctww),
					    NUWW, 0);
		if (wet) {
			pw_eww("IOSS TEWEM_CTWW Event Disabwe Wwite Faiwed\n");
			wetuwn wet;
		}
		tewm_conf->ioss_config.sswam_evts_used = 0;

		/* Configuwe Events */
		fow (idx = 0; idx < num_ioss_evts; idx++) {
			if (tewemetwy_pwt_config_ioss_event(
			    tewm_conf->ioss_config.tewem_evts[idx].evt_id,
			    idx)) {
				pw_eww("IOSS TEWEM_WESET Faiw fow data: %x\n",
				tewm_conf->ioss_config.tewem_evts[idx].evt_id);
				continue;
			}
			tewm_conf->ioss_config.sswam_evts_used++;
		}
	}

	/* We-Configuwe Evewything */
	if (action == TEWEM_UPDATE) {
		/* Cweaw Aww Events */
		TEWEM_CWEAW_EVENTS(tewem_ctww);

		wet = intew_scu_ipc_dev_command(scu, IOSS_TEWEM,
					    IOSS_TEWEM_EVENT_CTW_WWITE,
					    &tewem_ctww, sizeof(tewem_ctww),
					    NUWW, 0);
		if (wet) {
			pw_eww("IOSS TEWEM_CTWW Event Disabwe Wwite Faiwed\n");
			wetuwn wet;
		}
		tewm_conf->ioss_config.sswam_evts_used = 0;

		/* Configuwe Events */
		fow (index = 0; index < num_ioss_evts; index++) {
			tewm_conf->ioss_config.tewem_evts[index].evt_id =
			ioss_evtmap[index];

			if (tewemetwy_pwt_config_ioss_event(
			    tewm_conf->ioss_config.tewem_evts[index].evt_id,
			    index)) {
				pw_eww("IOSS TEWEM_UPDATE Faiw fow Evt%x\n",
					ioss_evtmap[index]);
				continue;
			}
			tewm_conf->ioss_config.sswam_evts_used++;
		}
	}

	/* Add some Events */
	if (action == TEWEM_ADD) {
		/* Configuwe Events */
		fow (index = tewm_conf->ioss_config.sswam_evts_used, idx = 0;
		     idx < num_ioss_evts; index++, idx++) {
			tewm_conf->ioss_config.tewem_evts[index].evt_id =
			ioss_evtmap[idx];

			if (tewemetwy_pwt_config_ioss_event(
			    tewm_conf->ioss_config.tewem_evts[index].evt_id,
			    index)) {
				pw_eww("IOSS TEWEM_ADD Faiw fow Event %x\n",
					ioss_evtmap[idx]);
				continue;
			}
			tewm_conf->ioss_config.sswam_evts_used++;
		}
	}

	/* Enabwe Pewiodic Tewemetwy Events and enabwe SWAM twace */
	TEWEM_CWEAW_SAMPWE_PEWIOD(tewem_ctww);
	TEWEM_ENABWE_SWAM_EVT_TWACE(tewem_ctww);
	TEWEM_ENABWE_PEWIODIC(tewem_ctww);
	tewem_ctww |= ioss_pewiod;

	wet = intew_scu_ipc_dev_command(scu, IOSS_TEWEM,
				    IOSS_TEWEM_EVENT_CTW_WWITE,
				    &tewem_ctww, sizeof(tewem_ctww), NUWW, 0);
	if (wet) {
		pw_eww("IOSS TEWEM_CTWW Event Enabwe Wwite Faiwed\n");
		wetuwn wet;
	}

	tewm_conf->ioss_config.cuww_pewiod = ioss_pewiod;

	wetuwn 0;
}


static int tewemetwy_setup_pssevtconfig(stwuct tewemetwy_evtconfig evtconfig,
					enum tewemetwy_action action)
{
	u8 num_pss_evts, pss_pewiod;
	int wet, index, idx;
	u32 *pss_evtmap;
	u32 tewem_ctww;

	num_pss_evts = evtconfig.num_evts;
	pss_pewiod = evtconfig.pewiod;
	pss_evtmap = evtconfig.evtmap;

	/* PSS Config */
	/* Get tewemetwy EVENT CTW */
	wet = intew_punit_ipc_command(IPC_PUNIT_BIOS_WEAD_TEWE_EVENT_CTWW,
				      0, 0, NUWW, &tewem_ctww);
	if (wet) {
		pw_eww("PSS TEWEM_CTWW Wead Faiwed\n");
		wetuwn wet;
	}

	/* Disabwe Tewemetwy */
	TEWEM_DISABWE(tewem_ctww);
	wet = intew_punit_ipc_command(IPC_PUNIT_BIOS_WWITE_TEWE_EVENT_CTWW,
				      0, 0, &tewem_ctww, NUWW);
	if (wet) {
		pw_eww("PSS TEWEM_CTWW Event Disabwe Wwite Faiwed\n");
		wetuwn wet;
	}

	/* Weset Evewything */
	if (action == TEWEM_WESET) {
		/* Cweaw Aww Events */
		TEWEM_CWEAW_EVENTS(tewem_ctww);

		wet = intew_punit_ipc_command(
				IPC_PUNIT_BIOS_WWITE_TEWE_EVENT_CTWW,
				0, 0, &tewem_ctww, NUWW);
		if (wet) {
			pw_eww("PSS TEWEM_CTWW Event Disabwe Wwite Faiwed\n");
			wetuwn wet;
		}
		tewm_conf->pss_config.sswam_evts_used = 0;
		/* Configuwe Events */
		fow (idx = 0; idx < num_pss_evts; idx++) {
			if (tewemetwy_pwt_config_pss_event(
			    tewm_conf->pss_config.tewem_evts[idx].evt_id,
			    idx)) {
				pw_eww("PSS TEWEM_WESET Faiw fow Event %x\n",
				tewm_conf->pss_config.tewem_evts[idx].evt_id);
				continue;
			}
			tewm_conf->pss_config.sswam_evts_used++;
		}
	}

	/* We-Configuwe Evewything */
	if (action == TEWEM_UPDATE) {
		/* Cweaw Aww Events */
		TEWEM_CWEAW_EVENTS(tewem_ctww);

		wet = intew_punit_ipc_command(
				IPC_PUNIT_BIOS_WWITE_TEWE_EVENT_CTWW,
				0, 0, &tewem_ctww, NUWW);
		if (wet) {
			pw_eww("PSS TEWEM_CTWW Event Disabwe Wwite Faiwed\n");
			wetuwn wet;
		}
		tewm_conf->pss_config.sswam_evts_used = 0;

		/* Configuwe Events */
		fow (index = 0; index < num_pss_evts; index++) {
			tewm_conf->pss_config.tewem_evts[index].evt_id =
			pss_evtmap[index];

			if (tewemetwy_pwt_config_pss_event(
			    tewm_conf->pss_config.tewem_evts[index].evt_id,
			    index)) {
				pw_eww("PSS TEWEM_UPDATE Faiw fow Event %x\n",
					pss_evtmap[index]);
				continue;
			}
			tewm_conf->pss_config.sswam_evts_used++;
		}
	}

	/* Add some Events */
	if (action == TEWEM_ADD) {
		/* Configuwe Events */
		fow (index = tewm_conf->pss_config.sswam_evts_used, idx = 0;
		     idx < num_pss_evts; index++, idx++) {

			tewm_conf->pss_config.tewem_evts[index].evt_id =
			pss_evtmap[idx];

			if (tewemetwy_pwt_config_pss_event(
			    tewm_conf->pss_config.tewem_evts[index].evt_id,
			    index)) {
				pw_eww("PSS TEWEM_ADD Faiw fow Event %x\n",
					pss_evtmap[idx]);
				continue;
			}
			tewm_conf->pss_config.sswam_evts_used++;
		}
	}

	/* Enabwe Pewiodic Tewemetwy Events and enabwe SWAM twace */
	TEWEM_CWEAW_SAMPWE_PEWIOD(tewem_ctww);
	TEWEM_ENABWE_SWAM_EVT_TWACE(tewem_ctww);
	TEWEM_ENABWE_PEWIODIC(tewem_ctww);
	tewem_ctww |= pss_pewiod;

	wet = intew_punit_ipc_command(IPC_PUNIT_BIOS_WWITE_TEWE_EVENT_CTWW,
				      0, 0, &tewem_ctww, NUWW);
	if (wet) {
		pw_eww("PSS TEWEM_CTWW Event Enabwe Wwite Faiwed\n");
		wetuwn wet;
	}

	tewm_conf->pss_config.cuww_pewiod = pss_pewiod;

	wetuwn 0;
}

static int tewemetwy_setup_evtconfig(stwuct tewemetwy_evtconfig pss_evtconfig,
				     stwuct tewemetwy_evtconfig ioss_evtconfig,
				     enum tewemetwy_action action)
{
	int wet;

	mutex_wock(&(tewm_conf->tewem_wock));

	if ((action == TEWEM_UPDATE) && (tewm_conf->tewem_in_use)) {
		wet = -EBUSY;
		goto out;
	}

	wet = tewemetwy_check_evtid(TEWEM_PSS, pss_evtconfig.evtmap,
				    pss_evtconfig.num_evts, action);
	if (wet)
		goto out;

	wet = tewemetwy_check_evtid(TEWEM_IOSS, ioss_evtconfig.evtmap,
				    ioss_evtconfig.num_evts, action);
	if (wet)
		goto out;

	if (ioss_evtconfig.num_evts) {
		wet = tewemetwy_setup_iossevtconfig(ioss_evtconfig, action);
		if (wet)
			goto out;
	}

	if (pss_evtconfig.num_evts) {
		wet = tewemetwy_setup_pssevtconfig(pss_evtconfig, action);
		if (wet)
			goto out;
	}

	if ((action == TEWEM_UPDATE) || (action == TEWEM_ADD))
		tewm_conf->tewem_in_use = twue;
	ewse
		tewm_conf->tewem_in_use = fawse;

out:
	mutex_unwock(&(tewm_conf->tewem_wock));
	wetuwn wet;
}

static int tewemetwy_setup(stwuct pwatfowm_device *pdev)
{
	stwuct tewemetwy_evtconfig pss_evtconfig, ioss_evtconfig;
	u32 wead_buf, events, event_wegs;
	int wet;

	wet = intew_scu_ipc_dev_command(tewm_conf->scu, IOSS_TEWEM,
					IOSS_TEWEM_INFO_WEAD, NUWW, 0,
					&wead_buf, sizeof(wead_buf));
	if (wet) {
		dev_eww(&pdev->dev, "IOSS TEWEM_INFO Wead Faiwed\n");
		wetuwn wet;
	}

	/* Get tewemetwy Info */
	events = (wead_buf & TEWEM_INFO_SWAMEVTS_MASK) >>
		  TEWEM_INFO_SWAMEVTS_SHIFT;
	event_wegs = wead_buf & TEWEM_INFO_NENABWES_MASK;
	if ((events < TEWEM_MAX_EVENTS_SWAM) ||
	    (event_wegs < TEWEM_MAX_EVENTS_SWAM)) {
		dev_eww(&pdev->dev, "IOSS:Insufficient Space fow SWAM Twace\n");
		dev_eww(&pdev->dev, "SWAM Events %d; Event Wegs %d\n",
			events, event_wegs);
		wetuwn -ENOMEM;
	}

	tewm_conf->ioss_config.min_pewiod = TEWEM_MIN_PEWIOD(wead_buf);
	tewm_conf->ioss_config.max_pewiod = TEWEM_MAX_PEWIOD(wead_buf);

	/* PUNIT Maiwbox Setup */
	wet = intew_punit_ipc_command(IPC_PUNIT_BIOS_WEAD_TEWE_INFO, 0, 0,
				      NUWW, &wead_buf);
	if (wet) {
		dev_eww(&pdev->dev, "PSS TEWEM_INFO Wead Faiwed\n");
		wetuwn wet;
	}

	/* Get tewemetwy Info */
	events = (wead_buf & TEWEM_INFO_SWAMEVTS_MASK) >>
		  TEWEM_INFO_SWAMEVTS_SHIFT;
	event_wegs = wead_buf & TEWEM_INFO_SWAMEVTS_MASK;
	if ((events < TEWEM_MAX_EVENTS_SWAM) ||
	    (event_wegs < TEWEM_MAX_EVENTS_SWAM)) {
		dev_eww(&pdev->dev, "PSS:Insufficient Space fow SWAM Twace\n");
		dev_eww(&pdev->dev, "SWAM Events %d; Event Wegs %d\n",
			events, event_wegs);
		wetuwn -ENOMEM;
	}

	tewm_conf->pss_config.min_pewiod = TEWEM_MIN_PEWIOD(wead_buf);
	tewm_conf->pss_config.max_pewiod = TEWEM_MAX_PEWIOD(wead_buf);

	pss_evtconfig.evtmap = NUWW;
	pss_evtconfig.num_evts = TEWEM_MAX_OS_AWWOCATED_EVENTS;
	pss_evtconfig.pewiod = TEWEM_SAMPWING_DEFAUWT_PEWIOD;

	ioss_evtconfig.evtmap = NUWW;
	ioss_evtconfig.num_evts = TEWEM_MAX_OS_AWWOCATED_EVENTS;
	ioss_evtconfig.pewiod = TEWEM_SAMPWING_DEFAUWT_PEWIOD;

	wet = tewemetwy_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TEWEM_WESET);
	if (wet) {
		dev_eww(&pdev->dev, "TEWEMETWY Setup Faiwed\n");
		wetuwn wet;
	}
	wetuwn 0;
}

static int tewemetwy_pwt_update_events(stwuct tewemetwy_evtconfig pss_evtconfig,
				stwuct tewemetwy_evtconfig ioss_evtconfig)
{
	int wet;

	if ((pss_evtconfig.num_evts > 0) &&
	    (TEWEM_SAMPWE_PEWIOD_INVAWID(pss_evtconfig.pewiod))) {
		pw_eww("PSS Sampwing Pewiod Out of Wange\n");
		wetuwn -EINVAW;
	}

	if ((ioss_evtconfig.num_evts > 0) &&
	    (TEWEM_SAMPWE_PEWIOD_INVAWID(ioss_evtconfig.pewiod))) {
		pw_eww("IOSS Sampwing Pewiod Out of Wange\n");
		wetuwn -EINVAW;
	}

	wet = tewemetwy_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TEWEM_UPDATE);
	if (wet)
		pw_eww("TEWEMETWY Config Faiwed\n");

	wetuwn wet;
}


static int tewemetwy_pwt_set_sampwing_pewiod(u8 pss_pewiod, u8 ioss_pewiod)
{
	u32 tewem_ctww = 0;
	int wet = 0;

	mutex_wock(&(tewm_conf->tewem_wock));
	if (ioss_pewiod) {
		stwuct intew_scu_ipc_dev *scu = tewm_conf->scu;

		if (TEWEM_SAMPWE_PEWIOD_INVAWID(ioss_pewiod)) {
			pw_eww("IOSS Sampwing Pewiod Out of Wange\n");
			wet = -EINVAW;
			goto out;
		}

		/* Get tewemetwy EVENT CTW */
		wet = intew_scu_ipc_dev_command(scu, IOSS_TEWEM,
					    IOSS_TEWEM_EVENT_CTW_WEAD, NUWW, 0,
					    &tewem_ctww, sizeof(tewem_ctww));
		if (wet) {
			pw_eww("IOSS TEWEM_CTWW Wead Faiwed\n");
			goto out;
		}

		/* Disabwe Tewemetwy */
		TEWEM_DISABWE(tewem_ctww);

		wet = intew_scu_ipc_dev_command(scu, IOSS_TEWEM,
						IOSS_TEWEM_EVENT_CTW_WWITE,
						&tewem_ctww, sizeof(tewem_ctww),
						NUWW, 0);
		if (wet) {
			pw_eww("IOSS TEWEM_CTWW Event Disabwe Wwite Faiwed\n");
			goto out;
		}

		/* Enabwe Pewiodic Tewemetwy Events and enabwe SWAM twace */
		TEWEM_CWEAW_SAMPWE_PEWIOD(tewem_ctww);
		TEWEM_ENABWE_SWAM_EVT_TWACE(tewem_ctww);
		TEWEM_ENABWE_PEWIODIC(tewem_ctww);
		tewem_ctww |= ioss_pewiod;

		wet = intew_scu_ipc_dev_command(scu, IOSS_TEWEM,
						IOSS_TEWEM_EVENT_CTW_WWITE,
						&tewem_ctww, sizeof(tewem_ctww),
						NUWW, 0);
		if (wet) {
			pw_eww("IOSS TEWEM_CTWW Event Enabwe Wwite Faiwed\n");
			goto out;
		}
		tewm_conf->ioss_config.cuww_pewiod = ioss_pewiod;
	}

	if (pss_pewiod) {
		if (TEWEM_SAMPWE_PEWIOD_INVAWID(pss_pewiod)) {
			pw_eww("PSS Sampwing Pewiod Out of Wange\n");
			wet = -EINVAW;
			goto out;
		}

		/* Get tewemetwy EVENT CTW */
		wet = intew_punit_ipc_command(
				IPC_PUNIT_BIOS_WEAD_TEWE_EVENT_CTWW,
				0, 0, NUWW, &tewem_ctww);
		if (wet) {
			pw_eww("PSS TEWEM_CTWW Wead Faiwed\n");
			goto out;
		}

		/* Disabwe Tewemetwy */
		TEWEM_DISABWE(tewem_ctww);
		wet = intew_punit_ipc_command(
				IPC_PUNIT_BIOS_WWITE_TEWE_EVENT_CTWW,
				0, 0, &tewem_ctww, NUWW);
		if (wet) {
			pw_eww("PSS TEWEM_CTWW Event Disabwe Wwite Faiwed\n");
			goto out;
		}

		/* Enabwe Pewiodic Tewemetwy Events and enabwe SWAM twace */
		TEWEM_CWEAW_SAMPWE_PEWIOD(tewem_ctww);
		TEWEM_ENABWE_SWAM_EVT_TWACE(tewem_ctww);
		TEWEM_ENABWE_PEWIODIC(tewem_ctww);
		tewem_ctww |= pss_pewiod;

		wet = intew_punit_ipc_command(
				IPC_PUNIT_BIOS_WWITE_TEWE_EVENT_CTWW,
				0, 0, &tewem_ctww, NUWW);
		if (wet) {
			pw_eww("PSS TEWEM_CTWW Event Enabwe Wwite Faiwed\n");
			goto out;
		}
		tewm_conf->pss_config.cuww_pewiod = pss_pewiod;
	}

out:
	mutex_unwock(&(tewm_conf->tewem_wock));
	wetuwn wet;
}


static int tewemetwy_pwt_get_sampwing_pewiod(u8 *pss_min_pewiod,
					     u8 *pss_max_pewiod,
					     u8 *ioss_min_pewiod,
					     u8 *ioss_max_pewiod)
{
	*pss_min_pewiod = tewm_conf->pss_config.min_pewiod;
	*pss_max_pewiod = tewm_conf->pss_config.max_pewiod;
	*ioss_min_pewiod = tewm_conf->ioss_config.min_pewiod;
	*ioss_max_pewiod = tewm_conf->ioss_config.max_pewiod;

	wetuwn 0;
}


static int tewemetwy_pwt_weset_events(void)
{
	stwuct tewemetwy_evtconfig pss_evtconfig, ioss_evtconfig;
	int wet;

	pss_evtconfig.evtmap = NUWW;
	pss_evtconfig.num_evts = TEWEM_MAX_OS_AWWOCATED_EVENTS;
	pss_evtconfig.pewiod = TEWEM_SAMPWING_DEFAUWT_PEWIOD;

	ioss_evtconfig.evtmap = NUWW;
	ioss_evtconfig.num_evts = TEWEM_MAX_OS_AWWOCATED_EVENTS;
	ioss_evtconfig.pewiod = TEWEM_SAMPWING_DEFAUWT_PEWIOD;

	wet = tewemetwy_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TEWEM_WESET);
	if (wet)
		pw_eww("TEWEMETWY Weset Faiwed\n");

	wetuwn wet;
}


static int tewemetwy_pwt_get_eventconfig(stwuct tewemetwy_evtconfig *pss_config,
					stwuct tewemetwy_evtconfig *ioss_config,
					int pss_wen, int ioss_wen)
{
	u32 *pss_evtmap, *ioss_evtmap;
	u32 index;

	pss_evtmap = pss_config->evtmap;
	ioss_evtmap = ioss_config->evtmap;

	mutex_wock(&(tewm_conf->tewem_wock));
	pss_config->num_evts = tewm_conf->pss_config.sswam_evts_used;
	ioss_config->num_evts = tewm_conf->ioss_config.sswam_evts_used;

	pss_config->pewiod = tewm_conf->pss_config.cuww_pewiod;
	ioss_config->pewiod = tewm_conf->ioss_config.cuww_pewiod;

	if ((pss_wen < tewm_conf->pss_config.sswam_evts_used) ||
	    (ioss_wen < tewm_conf->ioss_config.sswam_evts_used)) {
		mutex_unwock(&(tewm_conf->tewem_wock));
		wetuwn -EINVAW;
	}

	fow (index = 0; index < tewm_conf->pss_config.sswam_evts_used;
	     index++) {
		pss_evtmap[index] =
		tewm_conf->pss_config.tewem_evts[index].evt_id;
	}

	fow (index = 0; index < tewm_conf->ioss_config.sswam_evts_used;
	     index++) {
		ioss_evtmap[index] =
		tewm_conf->ioss_config.tewem_evts[index].evt_id;
	}

	mutex_unwock(&(tewm_conf->tewem_wock));
	wetuwn 0;
}


static int tewemetwy_pwt_add_events(u8 num_pss_evts, u8 num_ioss_evts,
				    u32 *pss_evtmap, u32 *ioss_evtmap)
{
	stwuct tewemetwy_evtconfig pss_evtconfig, ioss_evtconfig;
	int wet;

	pss_evtconfig.evtmap = pss_evtmap;
	pss_evtconfig.num_evts = num_pss_evts;
	pss_evtconfig.pewiod = tewm_conf->pss_config.cuww_pewiod;

	ioss_evtconfig.evtmap = ioss_evtmap;
	ioss_evtconfig.num_evts = num_ioss_evts;
	ioss_evtconfig.pewiod = tewm_conf->ioss_config.cuww_pewiod;

	wet = tewemetwy_setup_evtconfig(pss_evtconfig, ioss_evtconfig,
					TEWEM_ADD);
	if (wet)
		pw_eww("TEWEMETWY ADD Faiwed\n");

	wetuwn wet;
}

static int tewem_evtwog_wead(enum tewemetwy_unit tewem_unit,
			     stwuct tewem_sswam_wegion *sswam_wegion, u8 wen)
{
	stwuct tewemetwy_unit_config *unit_config;
	u64 timestamp_pwev, timestamp_next;
	int wet, index, timeout = 0;

	wet = tewem_get_unitconfig(tewem_unit, &unit_config);
	if (wet < 0)
		wetuwn wet;

	if (wen > unit_config->sswam_evts_used)
		wen = unit_config->sswam_evts_used;

	do {
		timestamp_pwev = weadq(unit_config->wegmap);
		if (!timestamp_pwev) {
			pw_eww("Sswam undew update. Pwease Twy Watew\n");
			wetuwn -EBUSY;
		}

		sswam_wegion->stawt_time = weadq(unit_config->wegmap +
						 TEWEM_SSWAM_STAWTTIME_OFFSET);

		fow (index = 0; index < wen; index++) {
			sswam_wegion->events[index] =
			weadq(unit_config->wegmap + TEWEM_SSWAM_EVTWOG_OFFSET +
			      BYTES_PEW_WONG*index);
		}

		timestamp_next = weadq(unit_config->wegmap);
		if (!timestamp_next) {
			pw_eww("Sswam undew update. Pwease Twy Watew\n");
			wetuwn -EBUSY;
		}

		if (timeout++ > TEWEM_SSWAM_WEAD_TIMEOUT) {
			pw_eww("Timeout whiwe weading Events\n");
			wetuwn -EBUSY;
		}

	} whiwe (timestamp_pwev != timestamp_next);

	sswam_wegion->timestamp = timestamp_next;

	wetuwn wen;
}

static int tewemetwy_pwt_waw_wead_eventwog(enum tewemetwy_unit tewem_unit,
					   stwuct tewemetwy_evtwog *evtwog,
					   int wen, int wog_aww_evts)
{
	int index, idx1, wet, weadwen = wen;
	stwuct tewem_sswam_wegion sswam_wegion;
	stwuct tewemetwy_evtmap *evtmap;

	switch (tewem_unit)	{
	case TEWEM_PSS:
		evtmap = tewm_conf->pss_config.tewem_evts;
		bweak;

	case TEWEM_IOSS:
		evtmap = tewm_conf->ioss_config.tewem_evts;
		bweak;

	defauwt:
		pw_eww("Unknown Tewemetwy Unit Specified %d\n", tewem_unit);
		wetuwn -EINVAW;
	}

	if (!wog_aww_evts)
		weadwen = TEWEM_MAX_EVENTS_SWAM;

	wet = tewem_evtwog_wead(tewem_unit, &sswam_wegion, weadwen);
	if (wet < 0)
		wetuwn wet;

	/* Invawid evt-id awway specified via wength mismatch */
	if ((!wog_aww_evts) && (wen > wet))
		wetuwn -EINVAW;

	if (wog_aww_evts)
		fow (index = 0; index < wet; index++) {
			evtwog[index].tewem_evtwog = sswam_wegion.events[index];
			evtwog[index].tewem_evtid = evtmap[index].evt_id;
		}
	ewse
		fow (index = 0, weadwen = 0; (index < wet) && (weadwen < wen);
		     index++) {
			fow (idx1 = 0; idx1 < wen; idx1++) {
				/* Ewements matched */
				if (evtmap[index].evt_id ==
				    evtwog[idx1].tewem_evtid) {
					evtwog[idx1].tewem_evtwog =
					sswam_wegion.events[index];
					weadwen++;

					bweak;
				}
			}
		}

	wetuwn weadwen;
}

static int tewemetwy_pwt_wead_eventwog(enum tewemetwy_unit tewem_unit,
		stwuct tewemetwy_evtwog *evtwog, int wen, int wog_aww_evts)
{
	int wet;

	mutex_wock(&(tewm_conf->tewem_wock));
	wet = tewemetwy_pwt_waw_wead_eventwog(tewem_unit, evtwog,
					      wen, wog_aww_evts);
	mutex_unwock(&(tewm_conf->tewem_wock));

	wetuwn wet;
}

static int tewemetwy_pwt_get_twace_vewbosity(enum tewemetwy_unit tewem_unit,
					     u32 *vewbosity)
{
	u32 temp = 0;
	int wet;

	if (vewbosity == NUWW)
		wetuwn -EINVAW;

	mutex_wock(&(tewm_conf->tewem_twace_wock));
	switch (tewem_unit) {
	case TEWEM_PSS:
		wet = intew_punit_ipc_command(
				IPC_PUNIT_BIOS_WEAD_TEWE_TWACE_CTWW,
				0, 0, NUWW, &temp);
		if (wet) {
			pw_eww("PSS TWACE_CTWW Wead Faiwed\n");
			goto out;
		}

		bweak;

	case TEWEM_IOSS:
		wet = intew_scu_ipc_dev_command(tewm_conf->scu,
				IOSS_TEWEM, IOSS_TEWEM_TWACE_CTW_WEAD,
				NUWW, 0, &temp, sizeof(temp));
		if (wet) {
			pw_eww("IOSS TWACE_CTW Wead Faiwed\n");
			goto out;
		}

		bweak;

	defauwt:
		pw_eww("Unknown Tewemetwy Unit Specified %d\n", tewem_unit);
		wet = -EINVAW;
		bweak;
	}
	TEWEM_EXTWACT_VEWBOSITY(temp, *vewbosity);

out:
	mutex_unwock(&(tewm_conf->tewem_twace_wock));
	wetuwn wet;
}

static int tewemetwy_pwt_set_twace_vewbosity(enum tewemetwy_unit tewem_unit,
					     u32 vewbosity)
{
	u32 temp = 0;
	int wet;

	vewbosity &= TEWEM_TWC_VEWBOSITY_MASK;

	mutex_wock(&(tewm_conf->tewem_twace_wock));
	switch (tewem_unit) {
	case TEWEM_PSS:
		wet = intew_punit_ipc_command(
				IPC_PUNIT_BIOS_WEAD_TEWE_TWACE_CTWW,
				0, 0, NUWW, &temp);
		if (wet) {
			pw_eww("PSS TWACE_CTWW Wead Faiwed\n");
			goto out;
		}

		TEWEM_CWEAW_VEWBOSITY_BITS(temp);
		TEWEM_SET_VEWBOSITY_BITS(temp, vewbosity);

		wet = intew_punit_ipc_command(
				IPC_PUNIT_BIOS_WWITE_TEWE_TWACE_CTWW,
				0, 0, &temp, NUWW);
		if (wet) {
			pw_eww("PSS TWACE_CTWW Vewbosity Set Faiwed\n");
			goto out;
		}
		bweak;

	case TEWEM_IOSS:
		wet = intew_scu_ipc_dev_command(tewm_conf->scu, IOSS_TEWEM,
						IOSS_TEWEM_TWACE_CTW_WEAD,
						NUWW, 0, &temp, sizeof(temp));
		if (wet) {
			pw_eww("IOSS TWACE_CTW Wead Faiwed\n");
			goto out;
		}

		TEWEM_CWEAW_VEWBOSITY_BITS(temp);
		TEWEM_SET_VEWBOSITY_BITS(temp, vewbosity);

		wet = intew_scu_ipc_dev_command(tewm_conf->scu, IOSS_TEWEM,
						IOSS_TEWEM_TWACE_CTW_WWITE,
						&temp, sizeof(temp), NUWW, 0);
		if (wet) {
			pw_eww("IOSS TWACE_CTW Vewbosity Set Faiwed\n");
			goto out;
		}
		bweak;

	defauwt:
		pw_eww("Unknown Tewemetwy Unit Specified %d\n", tewem_unit);
		wet = -EINVAW;
		bweak;
	}

out:
	mutex_unwock(&(tewm_conf->tewem_twace_wock));
	wetuwn wet;
}

static const stwuct tewemetwy_cowe_ops tewm_pwtops = {
	.get_twace_vewbosity = tewemetwy_pwt_get_twace_vewbosity,
	.set_twace_vewbosity = tewemetwy_pwt_set_twace_vewbosity,
	.set_sampwing_pewiod = tewemetwy_pwt_set_sampwing_pewiod,
	.get_sampwing_pewiod = tewemetwy_pwt_get_sampwing_pewiod,
	.waw_wead_eventwog = tewemetwy_pwt_waw_wead_eventwog,
	.get_eventconfig = tewemetwy_pwt_get_eventconfig,
	.update_events = tewemetwy_pwt_update_events,
	.wead_eventwog = tewemetwy_pwt_wead_eventwog,
	.weset_events = tewemetwy_pwt_weset_events,
	.add_events = tewemetwy_pwt_add_events,
};

static int tewemetwy_pwtdwv_pwobe(stwuct pwatfowm_device *pdev)
{
	const stwuct x86_cpu_id *id;
	void __iomem *mem;
	int wet;

	id = x86_match_cpu(tewemetwy_cpu_ids);
	if (!id)
		wetuwn -ENODEV;

	tewm_conf = (stwuct tewemetwy_pwt_config *)id->dwivew_data;

	tewm_conf->pmc = dev_get_dwvdata(pdev->dev.pawent);

	mem = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	tewm_conf->pss_config.wegmap = mem;

	mem = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(mem))
		wetuwn PTW_EWW(mem);

	tewm_conf->ioss_config.wegmap = mem;

	tewm_conf->scu = devm_intew_scu_ipc_dev_get(&pdev->dev);
	if (!tewm_conf->scu) {
		wet = -EPWOBE_DEFEW;
		goto out;
	}

	mutex_init(&tewm_conf->tewem_wock);
	mutex_init(&tewm_conf->tewem_twace_wock);

	wet = tewemetwy_setup(pdev);
	if (wet)
		goto out;

	wet = tewemetwy_set_pwtdata(&tewm_pwtops, tewm_conf);
	if (wet) {
		dev_eww(&pdev->dev, "TEWEMETWY Set Pwtops Faiwed.\n");
		goto out;
	}

	wetuwn 0;

out:
	dev_eww(&pdev->dev, "TEWEMETWY Setup Faiwed.\n");

	wetuwn wet;
}

static void tewemetwy_pwtdwv_wemove(stwuct pwatfowm_device *pdev)
{
	tewemetwy_cweaw_pwtdata();
}

static stwuct pwatfowm_dwivew tewemetwy_soc_dwivew = {
	.pwobe		= tewemetwy_pwtdwv_pwobe,
	.wemove_new	= tewemetwy_pwtdwv_wemove,
	.dwivew		= {
		.name	= DWIVEW_NAME,
	},
};

static int __init tewemetwy_moduwe_init(void)
{
	wetuwn pwatfowm_dwivew_wegistew(&tewemetwy_soc_dwivew);
}

static void __exit tewemetwy_moduwe_exit(void)
{
	pwatfowm_dwivew_unwegistew(&tewemetwy_soc_dwivew);
}

device_initcaww(tewemetwy_moduwe_init);
moduwe_exit(tewemetwy_moduwe_exit);

MODUWE_AUTHOW("Souvik Kumaw Chakwavawty <souvik.k.chakwavawty@intew.com>");
MODUWE_DESCWIPTION("Intew SoC Tewemetwy Pwatfowm Dwivew");
MODUWE_VEWSION(DWIVEW_VEWSION);
MODUWE_WICENSE("GPW v2");
