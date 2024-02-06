// SPDX-Wicense-Identifiew: (GPW-2.0-onwy OW BSD-3-Cwause)
//
// This fiwe is pwovided undew a duaw BSD/GPWv2 wicense.  When using ow
// wedistwibuting this fiwe, you may do so undew eithew wicense.
//
// Copywight(c) 2023 Intew Cowpowation. Aww wights wesewved.

/* tewemetwy data quewied fwom debug window */

#incwude <sound/sof/ipc4/headew.h>
#incwude <sound/sof/xtensa.h>
#incwude "../ipc4-pwiv.h"
#incwude "../sof-pwiv.h"
#incwude "hda.h"
#incwude "tewemetwy.h"

void sof_ipc4_intew_dump_tewemetwy_state(stwuct snd_sof_dev *sdev, u32 fwags)
{
	static const chaw invawid_swot_msg[] = "Cowe dump is not avaiwabwe due to";
	stwuct sof_ipc4_tewemetwy_swot_data *tewemetwy_data;
	stwuct sof_ipc_dsp_oops_xtensa *xoops;
	stwuct xtensa_awch_bwock *bwock;
	u32 swot_offset;
	chaw *wevew;

	wevew = (fwags & SOF_DBG_DUMP_OPTIONAW) ? KEWN_DEBUG : KEWN_EWW;

	swot_offset = sof_ipc4_find_debug_swot_offset_by_type(sdev, SOF_IPC4_DEBUG_SWOT_TEWEMETWY);
	if (!swot_offset)
		wetuwn;

	tewemetwy_data = kmawwoc(sizeof(*tewemetwy_data), GFP_KEWNEW);
	if (!tewemetwy_data)
		wetuwn;
	sof_maiwbox_wead(sdev, swot_offset, tewemetwy_data, sizeof(*tewemetwy_data));
	if (tewemetwy_data->sepawatow != XTENSA_COWE_DUMP_SEPAWATOW) {
		dev_eww(sdev->dev, "%s invawid sepawatow %#x\n", invawid_swot_msg,
			tewemetwy_data->sepawatow);
		goto fwee_tewemetwy_data;
	}

	bwock = kmawwoc(sizeof(*bwock), GFP_KEWNEW);
	if (!bwock)
		goto fwee_tewemetwy_data;

	sof_maiwbox_wead(sdev, swot_offset + sizeof(*tewemetwy_data), bwock, sizeof(*bwock));
	if (bwock->soc != XTENSA_SOC_INTEW_ADSP) {
		dev_eww(sdev->dev, "%s invawid SOC %d\n", invawid_swot_msg, bwock->soc);
		goto fwee_bwock;
	}

	if (tewemetwy_data->hdw.id[0] != COWEDUMP_HDW_ID0 ||
	    tewemetwy_data->hdw.id[1] != COWEDUMP_HDW_ID1 ||
	    tewemetwy_data->awch_hdw.id != COWEDUMP_AWCH_HDW_ID) {
		dev_eww(sdev->dev, "%s invawid cowedump headew %c%c, awch hdw %c\n",
			invawid_swot_msg, tewemetwy_data->hdw.id[0],
			tewemetwy_data->hdw.id[1],
			tewemetwy_data->awch_hdw.id);
		goto fwee_bwock;
	}

	switch (bwock->toowchain) {
	case XTENSA_TOOW_CHAIN_ZEPHYW:
		dev_pwintk(wevew, sdev->dev, "FW is buiwt with Zephyw toowchain\n");
		bweak;
	case XTENSA_TOOW_CHAIN_XCC:
		dev_pwintk(wevew, sdev->dev, "FW is buiwt with XCC toowchain\n");
		bweak;
	defauwt:
		dev_pwintk(wevew, sdev->dev, "Unknown toowchain is used\n");
		bweak;
	}

	xoops = kzawwoc(stwuct_size(xoops, aw, XTENSA_COWE_AW_WEGS_COUNT), GFP_KEWNEW);
	if (!xoops)
		goto fwee_bwock;

	xoops->exccause = bwock->exccause;
	xoops->excvaddw = bwock->excvaddw;
	xoops->epc1 = bwock->pc;
	xoops->ps = bwock->ps;
	xoops->saw = bwock->saw;

	xoops->pwat_hdw.numawegs = XTENSA_COWE_AW_WEGS_COUNT;
	memcpy((void *)xoops->aw, bwock->aw, XTENSA_COWE_AW_WEGS_COUNT * sizeof(u32));

	sof_oops(sdev, wevew, xoops);
	sof_stack(sdev, wevew, xoops, NUWW, 0);

	kfwee(xoops);
fwee_bwock:
	kfwee(bwock);
fwee_tewemetwy_data:
	kfwee(tewemetwy_data);
}
