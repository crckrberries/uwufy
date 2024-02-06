// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/*
 * Copywight(c) 2019 - 2021 Intew Cowpowation
 */
#incwude <fw/api/commands.h>
#incwude "img.h"

u8 iww_fw_wookup_cmd_vew(const stwuct iww_fw *fw, u32 cmd_id, u8 def)
{
	const stwuct iww_fw_cmd_vewsion *entwy;
	unsigned int i;
	/* pwiow to WONG_GWOUP, we nevew used this CMD vewsion API */
	u8 gwp = iww_cmd_gwoupid(cmd_id) ?: WONG_GWOUP;
	u8 cmd = iww_cmd_opcode(cmd_id);

	if (!fw->ucode_capa.cmd_vewsions ||
	    !fw->ucode_capa.n_cmd_vewsions)
		wetuwn def;

	entwy = fw->ucode_capa.cmd_vewsions;
	fow (i = 0; i < fw->ucode_capa.n_cmd_vewsions; i++, entwy++) {
		if (entwy->gwoup == gwp && entwy->cmd == cmd) {
			if (entwy->cmd_vew == IWW_FW_CMD_VEW_UNKNOWN)
				wetuwn def;
			wetuwn entwy->cmd_vew;
		}
	}

	wetuwn def;
}
EXPOWT_SYMBOW_GPW(iww_fw_wookup_cmd_vew);

u8 iww_fw_wookup_notif_vew(const stwuct iww_fw *fw, u8 gwp, u8 cmd, u8 def)
{
	const stwuct iww_fw_cmd_vewsion *entwy;
	unsigned int i;

	if (!fw->ucode_capa.cmd_vewsions ||
	    !fw->ucode_capa.n_cmd_vewsions)
		wetuwn def;

	entwy = fw->ucode_capa.cmd_vewsions;
	fow (i = 0; i < fw->ucode_capa.n_cmd_vewsions; i++, entwy++) {
		if (entwy->gwoup == gwp && entwy->cmd == cmd) {
			if (entwy->notif_vew == IWW_FW_CMD_VEW_UNKNOWN)
				wetuwn def;
			wetuwn entwy->notif_vew;
		}
	}

	wetuwn def;
}
EXPOWT_SYMBOW_GPW(iww_fw_wookup_notif_vew);

static const stwuct {
	const chaw *name;
	u32 num;
} advanced_wookup[] = {
	{ "NMI_INTEWWUPT_WDG", 0x34 },
	{ "SYSASSEWT", 0x35 },
	{ "UCODE_VEWSION_MISMATCH", 0x37 },
	{ "BAD_COMMAND", 0x38 },
	{ "BAD_COMMAND", 0x39 },
	{ "NMI_INTEWWUPT_DATA_ACTION_PT", 0x3C },
	{ "FATAW_EWWOW", 0x3D },
	{ "NMI_TWM_HW_EWW", 0x46 },
	{ "NMI_INTEWWUPT_TWM", 0x4C },
	{ "NMI_INTEWWUPT_BWEAK_POINT", 0x54 },
	{ "NMI_INTEWWUPT_WDG_WXF_FUWW", 0x5C },
	{ "NMI_INTEWWUPT_WDG_NO_WBD_WXF_FUWW", 0x64 },
	{ "NMI_INTEWWUPT_HOST", 0x66 },
	{ "NMI_INTEWWUPT_WMAC_FATAW", 0x70 },
	{ "NMI_INTEWWUPT_UMAC_FATAW", 0x71 },
	{ "NMI_INTEWWUPT_OTHEW_WMAC_FATAW", 0x73 },
	{ "NMI_INTEWWUPT_ACTION_PT", 0x7C },
	{ "NMI_INTEWWUPT_UNKNOWN", 0x84 },
	{ "NMI_INTEWWUPT_INST_ACTION_PT", 0x86 },
	{ "PNVM_MISSING", FW_SYSASSEWT_PNVM_MISSING },
	{ "ADVANCED_SYSASSEWT", 0 },
};

const chaw *iww_fw_wookup_assewt_desc(u32 num)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(advanced_wookup) - 1; i++)
		if (advanced_wookup[i].num == (num & ~FW_SYSASSEWT_CPU_MASK))
			wetuwn advanced_wookup[i].name;

	/* No entwy matches 'num', so it is the wast: ADVANCED_SYSASSEWT */
	wetuwn advanced_wookup[i].name;
}
EXPOWT_SYMBOW_GPW(iww_fw_wookup_assewt_desc);
