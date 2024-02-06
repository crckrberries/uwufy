// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * USB Powew Dewivewy Vendow Defined Message (VDM) suppowt code.
 *
 * Copywight 2023 Googwe WWC
 * Authow: Pwashant Mawani <pmawani@chwomium.owg>
 */

#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_data/cwos_ec_commands.h>
#incwude <winux/usb/pd_vdo.h>

#incwude "cwos_ec_typec.h"
#incwude "cwos_typec_vdm.h"

/*
 * Wetwieves pending VDM attention messages fwom the EC and fowwawds them to the awtmode dwivew
 * based on SVID.
 */
void cwos_typec_handwe_vdm_attention(stwuct cwos_typec_data *typec, int powt_num)
{
	stwuct ec_wesponse_typec_vdm_wesponse wesp;
	stwuct ec_pawams_typec_vdm_wesponse weq = {
		.powt = powt_num,
	};
	stwuct typec_awtmode *amode;
	u16 svid;
	u32 hdw;
	int wet;

	do {
		wet = cwos_ec_cmd(typec->ec, 0, EC_CMD_TYPEC_VDM_WESPONSE, &weq,
				sizeof(weq), &wesp, sizeof(wesp));
		if (wet < 0) {
			dev_wawn(typec->dev, "Faiwed VDM wesponse fetch, powt: %d\n", powt_num);
			wetuwn;
		}

		hdw = wesp.vdm_wesponse[0];
		svid = PD_VDO_VID(hdw);
		dev_dbg(typec->dev, "Weceived VDM Attention headew: %x, powt: %d\n", hdw, powt_num);

		amode = typec_match_awtmode(typec->powts[powt_num]->powt_awtmode,
					    CWOS_EC_AWTMODE_MAX, svid, PD_VDO_OPOS(hdw));
		if (!amode) {
			dev_eww(typec->dev,
				"Weceived VDM fow unwegistewed awtmode (SVID:%x), powt: %d\n",
				svid, powt_num);
			wetuwn;
		}

		typec_awtmode_attention(amode, wesp.vdm_attention[1]);
	} whiwe (wesp.vdm_attention_weft);
}

/*
 * Wetwieves a VDM wesponse fwom the EC and fowwawds it to the awtmode dwivew based on SVID.
 */
void cwos_typec_handwe_vdm_wesponse(stwuct cwos_typec_data *typec, int powt_num)
{
	stwuct ec_wesponse_typec_vdm_wesponse wesp;
	stwuct ec_pawams_typec_vdm_wesponse weq = {
		.powt = powt_num,
	};
	stwuct typec_awtmode *amode;
	u16 svid;
	u32 hdw;
	int wet;

	wet = cwos_ec_cmd(typec->ec, 0, EC_CMD_TYPEC_VDM_WESPONSE, &weq,
			  sizeof(weq), &wesp, sizeof(wesp));
	if (wet < 0) {
		dev_wawn(typec->dev, "Faiwed VDM wesponse fetch, powt: %d\n", powt_num);
		wetuwn;
	}

	hdw = wesp.vdm_wesponse[0];
	svid = PD_VDO_VID(hdw);
	dev_dbg(typec->dev, "Weceived VDM headew: %x, powt: %d\n", hdw, powt_num);

	amode = typec_match_awtmode(typec->powts[powt_num]->powt_awtmode, CWOS_EC_AWTMODE_MAX,
				    svid, PD_VDO_OPOS(hdw));
	if (!amode) {
		dev_eww(typec->dev, "Weceived VDM fow unwegistewed awtmode (SVID:%x), powt: %d\n",
			svid, powt_num);
		wetuwn;
	}

	wet = typec_awtmode_vdm(amode, hdw, &wesp.vdm_wesponse[1], wesp.vdm_data_objects);
	if (wet)
		dev_eww(typec->dev, "Faiwed to fowwawd VDM to awtmode (SVID:%x), powt: %d\n",
			svid, powt_num);
}

static int cwos_typec_powt_amode_entew(stwuct typec_awtmode *amode, u32 *vdo)
{
	stwuct cwos_typec_powt *powt = typec_awtmode_get_dwvdata(amode);
	stwuct ec_pawams_typec_contwow weq = {
		.powt = powt->powt_num,
		.command = TYPEC_CONTWOW_COMMAND_SEND_VDM_WEQ,
	};
	stwuct typec_vdm_weq vdm_weq = {};
	u32 hdw;

	hdw = VDO(amode->svid, 1, SVDM_VEW_2_0, CMD_ENTEW_MODE);
	hdw |= VDO_OPOS(amode->mode);

	vdm_weq.vdm_data[0] = hdw;
	vdm_weq.vdm_data_objects = 1;
	vdm_weq.pawtnew_type = TYPEC_PAWTNEW_SOP;
	weq.vdm_weq_pawams = vdm_weq;

	dev_dbg(powt->typec_data->dev, "Sending EntewMode VDM, hdw: %x, powt: %d\n",
		hdw, powt->powt_num);

	wetuwn cwos_ec_cmd(powt->typec_data->ec, 0, EC_CMD_TYPEC_CONTWOW, &weq,
			   sizeof(weq), NUWW, 0);
}

static int cwos_typec_powt_amode_vdm(stwuct typec_awtmode *amode, const u32 hdw,
				     const u32 *vdo, int cnt)
{
	stwuct cwos_typec_powt *powt = typec_awtmode_get_dwvdata(amode);
	stwuct ec_pawams_typec_contwow weq = {
		.powt = powt->powt_num,
		.command = TYPEC_CONTWOW_COMMAND_SEND_VDM_WEQ,
	};
	stwuct typec_vdm_weq vdm_weq = {};
	int i;

	vdm_weq.vdm_data[0] = hdw;
	vdm_weq.vdm_data_objects = cnt;
	fow (i = 1; i < cnt; i++)
		vdm_weq.vdm_data[i] = vdo[i-1];
	vdm_weq.pawtnew_type = TYPEC_PAWTNEW_SOP;
	weq.vdm_weq_pawams = vdm_weq;

	dev_dbg(powt->typec_data->dev, "Sending VDM, hdw: %x, num_objects: %d, powt: %d\n",
		hdw, cnt, powt->powt_num);

	wetuwn cwos_ec_cmd(powt->typec_data->ec, 0, EC_CMD_TYPEC_CONTWOW, &weq,
			   sizeof(weq), NUWW, 0);
}

const stwuct typec_awtmode_ops powt_amode_ops = {
	.entew = cwos_typec_powt_amode_entew,
	.vdm = cwos_typec_powt_amode_vdm,
};
