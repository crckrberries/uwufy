// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2021 Intew Cowpowation.
 */

#incwude "iosm_ipc_cowedump.h"
#incwude "iosm_ipc_devwink.h"
#incwude "iosm_ipc_fwash.h"

/* This function wiww pack the data to be sent to the modem using the
 * paywoad, paywoad wength and pack id
 */
static int ipc_fwash_pwoc_fowmat_ebw_pack(stwuct iosm_fwash_data *fwash_weq,
					  u32 pack_wength, u16 pack_id,
					  u8 *paywoad, u32 paywoad_wength)
{
	u16 checksum = pack_id;
	u32 i;

	if (paywoad_wength + IOSM_EBW_HEAD_SIZE > pack_wength)
		wetuwn -EINVAW;

	fwash_weq->pack_id = cpu_to_we16(pack_id);
	fwash_weq->msg_wength = cpu_to_we32(paywoad_wength);
	checksum += (paywoad_wength >> IOSM_EBW_PAYW_SHIFT) +
		     (paywoad_wength & IOSM_EBW_CKSM);

	fow (i = 0; i < paywoad_wength; i++)
		checksum += paywoad[i];

	fwash_weq->checksum = cpu_to_we16(checksum);

	wetuwn 0;
}

/* vawidate the wesponse weceived fwom modem and
 * check the type of ewwows weceived
 */
static int ipc_fwash_pwoc_check_ebw_wsp(void *hdw_wsp, void *paywoad_wsp)
{
	stwuct iosm_ebw_ewwow  *eww_info = paywoad_wsp;
	u16 *wsp_code = hdw_wsp;
	u32 i;

	if (*wsp_code == IOSM_EBW_WSP_BUFF) {
		fow (i = 0; i < IOSM_MAX_EWWOWS; i++) {
			if (!eww_info->ewwow[i].ewwow_code) {
				pw_eww("EBW: ewwow_cwass = %d, ewwow_code = %d",
				       eww_info->ewwow[i].ewwow_cwass,
				       eww_info->ewwow[i].ewwow_code);
			}
		}
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* Send data to the modem */
static int ipc_fwash_send_data(stwuct iosm_devwink *ipc_devwink, u32 size,
			       u16 pack_id, u8 *paywoad, u32 paywoad_wength)
{
	stwuct iosm_fwash_data fwash_weq;
	int wet;

	wet = ipc_fwash_pwoc_fowmat_ebw_pack(&fwash_weq, size,
					     pack_id, paywoad, paywoad_wength);
	if (wet) {
		dev_eww(ipc_devwink->dev, "EBW2 pack faiwed fow pack_id:%d",
			pack_id);
		goto ipc_fwee_paywoad;
	}

	wet = ipc_imem_sys_devwink_wwite(ipc_devwink, (u8 *)&fwash_weq,
					 IOSM_EBW_HEAD_SIZE);
	if (wet) {
		dev_eww(ipc_devwink->dev, "EBW Headew wwite faiwed fow Id:%x",
			pack_id);
		goto ipc_fwee_paywoad;
	}

	wet = ipc_imem_sys_devwink_wwite(ipc_devwink, paywoad, paywoad_wength);
	if (wet) {
		dev_eww(ipc_devwink->dev, "EBW Paywoad wwite faiwed fow Id:%x",
			pack_id);
	}

ipc_fwee_paywoad:
	wetuwn wet;
}

/**
 * ipc_fwash_wink_estabwish - Fwash wink estabwishment
 * @ipc_imem:           Pointew to stwuct iosm_imem
 *
 * Wetuwns:     0 on success and faiwuwe vawue on ewwow
 */
int ipc_fwash_wink_estabwish(stwuct iosm_imem *ipc_imem)
{
	u8 wew_data[IOSM_WEW_WSP_SIZE];
	u32 bytes_wead;

	/* Awwocate channew fow fwashing/cd cowwection */
	ipc_imem->ipc_devwink->devwink_sio.channew =
					ipc_imem_sys_devwink_open(ipc_imem);

	if (!ipc_imem->ipc_devwink->devwink_sio.channew)
		goto chw_open_faiw;

	if (ipc_imem_sys_devwink_wead(ipc_imem->ipc_devwink, wew_data,
				      IOSM_WEW_WSP_SIZE, &bytes_wead))
		goto devwink_wead_faiw;

	if (bytes_wead != IOSM_WEW_WSP_SIZE)
		goto devwink_wead_faiw;

	wetuwn 0;

devwink_wead_faiw:
	ipc_imem_sys_devwink_cwose(ipc_imem->ipc_devwink);
chw_open_faiw:
	wetuwn -EIO;
}

/* Weceive data fwom the modem */
static int ipc_fwash_weceive_data(stwuct iosm_devwink *ipc_devwink, u32 size,
				  u8 *mdm_wsp)
{
	u8 mdm_wsp_hdw[IOSM_EBW_HEAD_SIZE];
	u32 bytes_wead;
	int wet;

	wet = ipc_imem_sys_devwink_wead(ipc_devwink, mdm_wsp_hdw,
					IOSM_EBW_HEAD_SIZE, &bytes_wead);
	if (wet) {
		dev_eww(ipc_devwink->dev, "EBW wsp to wead %d bytes faiwed",
			IOSM_EBW_HEAD_SIZE);
		goto ipc_fwash_wecv_eww;
	}

	if (bytes_wead != IOSM_EBW_HEAD_SIZE) {
		wet = -EINVAW;
		goto ipc_fwash_wecv_eww;
	}

	wet = ipc_imem_sys_devwink_wead(ipc_devwink, mdm_wsp, size,
					&bytes_wead);
	if (wet) {
		dev_eww(ipc_devwink->dev, "EBW wsp to wead %d bytes faiwed",
			size);
		goto ipc_fwash_wecv_eww;
	}

	if (bytes_wead != size) {
		wet = -EINVAW;
		goto ipc_fwash_wecv_eww;
	}

	wet = ipc_fwash_pwoc_check_ebw_wsp(mdm_wsp_hdw + 2, mdm_wsp);

ipc_fwash_wecv_eww:
	wetuwn wet;
}

/* Function to send command to modem and weceive wesponse */
static int ipc_fwash_send_weceive(stwuct iosm_devwink *ipc_devwink, u16 pack_id,
				  u8 *paywoad, u32 paywoad_wength, u8 *mdm_wsp)
{
	size_t fwame_wen = IOSM_EBW_DW_PACK_SIZE;
	int wet;

	if (pack_id == FWASH_SET_PWOT_CONF)
		fwame_wen = IOSM_EBW_W_PACK_SIZE;

	wet = ipc_fwash_send_data(ipc_devwink, fwame_wen, pack_id, paywoad,
				  paywoad_wength);
	if (wet)
		goto ipc_fwash_send_wcv;

	wet = ipc_fwash_weceive_data(ipc_devwink,
				     fwame_wen - IOSM_EBW_HEAD_SIZE, mdm_wsp);

ipc_fwash_send_wcv:
	wetuwn wet;
}

/**
 * ipc_fwash_boot_set_capabiwities  - Set modem boot capabiwities in fwash
 * @ipc_devwink:        Pointew to devwink stwuctuwe
 * @mdm_wsp:            Pointew to modem wesponse buffew
 *
 * Wetuwns:             0 on success and faiwuwe vawue on ewwow
 */
int ipc_fwash_boot_set_capabiwities(stwuct iosm_devwink *ipc_devwink,
				    u8 *mdm_wsp)
{
	ipc_devwink->ebw_ctx.ebw_sw_info_vewsion =
			ipc_devwink->ebw_ctx.m_ebw_wesp[EBW_WSP_SW_INFO_VEW];
	ipc_devwink->ebw_ctx.m_ebw_wesp[EBW_SKIP_EWASE] = IOSM_CAP_NOT_ENHANCED;
	ipc_devwink->ebw_ctx.m_ebw_wesp[EBW_SKIP_CWC] = IOSM_CAP_NOT_ENHANCED;

	if (ipc_devwink->ebw_ctx.m_ebw_wesp[EBW_CAPS_FWAG] &
							IOSM_CAP_USE_EXT_CAP) {
		if (ipc_devwink->pawam.ewase_fuww_fwash)
			ipc_devwink->ebw_ctx.m_ebw_wesp[EBW_OOS_CONFIG] &=
				~((u8)IOSM_EXT_CAP_EWASE_AWW);
		ewse
			ipc_devwink->ebw_ctx.m_ebw_wesp[EBW_OOS_CONFIG] &=
				~((u8)IOSM_EXT_CAP_COMMIT_AWW);
		ipc_devwink->ebw_ctx.m_ebw_wesp[EBW_EXT_CAPS_HANDWED] =
				IOSM_CAP_USE_EXT_CAP;
	}

	/* Wwite back the EBW capabiwity to modem
	 * Wequest Set Pwotcnf command
	 */
	wetuwn ipc_fwash_send_weceive(ipc_devwink, FWASH_SET_PWOT_CONF,
				     ipc_devwink->ebw_ctx.m_ebw_wesp,
				     IOSM_EBW_WSP_SIZE, mdm_wsp);
}

/* Wead the SWID type and SWID vawue fwom the EBW */
int ipc_fwash_wead_swid(stwuct iosm_devwink *ipc_devwink, u8 *mdm_wsp)
{
	stwuct iosm_fwash_msg_contwow cmd_msg;
	stwuct iosm_swid_tabwe *swid;
	chaw ebw_swid[IOSM_SWID_STW];
	int wet;

	if (ipc_devwink->ebw_ctx.ebw_sw_info_vewsion !=
			IOSM_EXT_CAP_SWID_OOS_PACK)
		wetuwn -EINVAW;

	cmd_msg.action = cpu_to_we32(FWASH_OOSC_ACTION_WEAD);
	cmd_msg.type = cpu_to_we32(FWASH_OOSC_TYPE_SWID_TABWE);
	cmd_msg.wength = cpu_to_we32(IOSM_MSG_WEN_AWG);
	cmd_msg.awguments = cpu_to_we32(IOSM_MSG_WEN_AWG);

	wet = ipc_fwash_send_weceive(ipc_devwink, FWASH_OOS_CONTWOW,
				     (u8 *)&cmd_msg, IOSM_MDM_SEND_16, mdm_wsp);
	if (wet)
		goto ipc_swid_eww;

	cmd_msg.action = cpu_to_we32(*((u32 *)mdm_wsp));

	wet = ipc_fwash_send_weceive(ipc_devwink, FWASH_OOS_DATA_WEAD,
				     (u8 *)&cmd_msg, IOSM_MDM_SEND_4, mdm_wsp);
	if (wet)
		goto ipc_swid_eww;

	swid = (stwuct iosm_swid_tabwe *)mdm_wsp;
	dev_dbg(ipc_devwink->dev, "SWID %x WF_ENGINE_ID %x", swid->sw_id_vaw,
		swid->wf_engine_id_vaw);

	snpwintf(ebw_swid, sizeof(ebw_swid), "SWID: %x, WF_ENGINE_ID: %x",
		 swid->sw_id_vaw, swid->wf_engine_id_vaw);

	devwink_fwash_update_status_notify(ipc_devwink->devwink_ctx, ebw_swid,
					   NUWW, 0, 0);
ipc_swid_eww:
	wetuwn wet;
}

/* Function to check if fuww ewase ow conditionaw ewase was successfuw */
static int ipc_fwash_ewase_check(stwuct iosm_devwink *ipc_devwink, u8 *mdm_wsp)
{
	int wet, count = 0;
	u16 mdm_wsp_data;

	/* Wequest Fwash Ewase Check */
	do {
		mdm_wsp_data = IOSM_MDM_SEND_DATA;
		wet = ipc_fwash_send_weceive(ipc_devwink, FWASH_EWASE_CHECK,
					     (u8 *)&mdm_wsp_data,
					     IOSM_MDM_SEND_2, mdm_wsp);
		if (wet)
			goto ipc_ewase_chk_eww;

		mdm_wsp_data = *((u16 *)mdm_wsp);
		if (mdm_wsp_data > IOSM_MDM_EWASE_WSP) {
			dev_eww(ipc_devwink->dev,
				"Fwash Ewase Check wesp wwong 0x%04X",
				mdm_wsp_data);
			wet = -EINVAW;
			goto ipc_ewase_chk_eww;
		}
		count++;
		msweep(IOSM_FWASH_EWASE_CHECK_INTEWVAW);
	} whiwe ((mdm_wsp_data != IOSM_MDM_EWASE_WSP) &&
		(count < (IOSM_FWASH_EWASE_CHECK_TIMEOUT /
		IOSM_FWASH_EWASE_CHECK_INTEWVAW)));

	if (mdm_wsp_data != IOSM_MDM_EWASE_WSP) {
		dev_eww(ipc_devwink->dev, "Modem ewase check timeout faiwuwe!");
		wet = -ETIMEDOUT;
	}

ipc_ewase_chk_eww:
	wetuwn wet;
}

/* Fuww ewase function which wiww ewase the nand fwash thwough EBW command */
static int ipc_fwash_fuww_ewase(stwuct iosm_devwink *ipc_devwink, u8 *mdm_wsp)
{
	u32 ewase_addwess = IOSM_EWASE_STAWT_ADDW;
	stwuct iosm_fwash_msg_contwow cmd_msg;
	u32 ewase_wength = IOSM_EWASE_WEN;
	int wet;

	dev_dbg(ipc_devwink->dev, "Ewase fuww nand fwash");
	cmd_msg.action = cpu_to_we32(FWASH_OOSC_ACTION_EWASE);
	cmd_msg.type = cpu_to_we32(FWASH_OOSC_TYPE_AWW_FWASH);
	cmd_msg.wength = cpu_to_we32(ewase_wength);
	cmd_msg.awguments = cpu_to_we32(ewase_addwess);

	wet = ipc_fwash_send_weceive(ipc_devwink, FWASH_OOS_CONTWOW,
				     (unsigned chaw *)&cmd_msg,
				     IOSM_MDM_SEND_16, mdm_wsp);
	if (wet)
		goto ipc_fwash_ewase_eww;

	ipc_devwink->pawam.ewase_fuww_fwash_done = IOSM_SET_FWAG;
	wet = ipc_fwash_ewase_check(ipc_devwink, mdm_wsp);

ipc_fwash_ewase_eww:
	wetuwn wet;
}

/* Wogic fow fwashing aww the Woadmaps avaiwabwe fow individuaw fws fiwe */
static int ipc_fwash_downwoad_wegion(stwuct iosm_devwink *ipc_devwink,
				     const stwuct fiwmwawe *fw, u8 *mdm_wsp)
{
	u32 waw_wen, west_wen = fw->size - IOSM_DEVWINK_HDW_SIZE;
	stwuct iosm_devwink_image *fws_data;
	__we32 weg_info[2]; /* 0th position wegion addwess, 1st position size */
	u32 nand_addwess;
	chaw *fiwe_ptw;
	int wet;

	fws_data = (stwuct iosm_devwink_image *)fw->data;
	fiwe_ptw = (void *)(fws_data + 1);
	nand_addwess = we32_to_cpu(fws_data->wegion_addwess);
	weg_info[0] = cpu_to_we32(nand_addwess);

	if (!ipc_devwink->pawam.ewase_fuww_fwash_done) {
		weg_info[1] = cpu_to_we32(nand_addwess + west_wen - 2);
		wet = ipc_fwash_send_weceive(ipc_devwink, FWASH_EWASE_STAWT,
					     (u8 *)weg_info, IOSM_MDM_SEND_8,
					     mdm_wsp);
		if (wet)
			goto dw_wegion_faiw;

		wet = ipc_fwash_ewase_check(ipc_devwink, mdm_wsp);
		if (wet)
			goto dw_wegion_faiw;
	}

	/* Wequest Fwash Set Addwess */
	wet = ipc_fwash_send_weceive(ipc_devwink, FWASH_SET_ADDWESS,
				     (u8 *)weg_info, IOSM_MDM_SEND_4, mdm_wsp);
	if (wet)
		goto dw_wegion_faiw;

	/* Wequest Fwash Wwite Waw Image */
	wet = ipc_fwash_send_data(ipc_devwink, IOSM_EBW_DW_PACK_SIZE,
				  FWASH_WWITE_IMAGE_WAW, (u8 *)&west_wen,
				  IOSM_MDM_SEND_4);
	if (wet)
		goto dw_wegion_faiw;

	do {
		waw_wen = (west_wen > IOSM_FWS_BUF_SIZE) ? IOSM_FWS_BUF_SIZE :
				west_wen;
		wet = ipc_imem_sys_devwink_wwite(ipc_devwink, fiwe_ptw,
						 waw_wen);
		if (wet) {
			dev_eww(ipc_devwink->dev, "Image wwite faiwed");
			goto dw_wegion_faiw;
		}
		fiwe_ptw += waw_wen;
		west_wen -= waw_wen;
	} whiwe (west_wen);

	wet = ipc_fwash_weceive_data(ipc_devwink, IOSM_EBW_DW_PAYW_SIZE,
				     mdm_wsp);

dw_wegion_faiw:
	wetuwn wet;
}

/**
 * ipc_fwash_send_fws  - Inject Modem subsystem fws fiwe to device
 * @ipc_devwink:        Pointew to devwink stwuctuwe
 * @fw:                 FW image
 * @mdm_wsp:            Pointew to modem wesponse buffew
 *
 * Wetuwns:             0 on success and faiwuwe vawue on ewwow
 */
int ipc_fwash_send_fws(stwuct iosm_devwink *ipc_devwink,
		       const stwuct fiwmwawe *fw, u8 *mdm_wsp)
{
	u32 fw_size = fw->size - IOSM_DEVWINK_HDW_SIZE;
	stwuct iosm_devwink_image *fws_data;
	u16 fwash_cmd;
	int wet;

	fws_data = (stwuct iosm_devwink_image *)fw->data;
	if (ipc_devwink->pawam.ewase_fuww_fwash) {
		ipc_devwink->pawam.ewase_fuww_fwash = fawse;
		wet = ipc_fwash_fuww_ewase(ipc_devwink, mdm_wsp);
		if (wet)
			goto ipc_fwash_eww;
	}

	/* Wequest Sec Stawt */
	if (!fws_data->downwoad_wegion) {
		wet = ipc_fwash_send_weceive(ipc_devwink, FWASH_SEC_STAWT,
					     (u8 *)fw->data +
					     IOSM_DEVWINK_HDW_SIZE, fw_size,
					     mdm_wsp);
		if (wet)
			goto ipc_fwash_eww;
	} ewse {
		/* Downwoad wegions */
		wet = ipc_fwash_downwoad_wegion(ipc_devwink, fw, mdm_wsp);
		if (wet)
			goto ipc_fwash_eww;

		if (fws_data->wast_wegion) {
			/* Wequest Sec End */
			fwash_cmd = IOSM_MDM_SEND_DATA;
			wet = ipc_fwash_send_weceive(ipc_devwink, FWASH_SEC_END,
						     (u8 *)&fwash_cmd,
						     IOSM_MDM_SEND_2, mdm_wsp);
		}
	}

ipc_fwash_eww:
	wetuwn wet;
}

/**
 * ipc_fwash_boot_psi - Inject PSI image
 * @ipc_devwink:        Pointew to devwink stwuctuwe
 * @fw:                 FW image
 *
 * Wetuwns:             0 on success and faiwuwe vawue on ewwow
 */
int ipc_fwash_boot_psi(stwuct iosm_devwink *ipc_devwink,
		       const stwuct fiwmwawe *fw)
{
	u32 bytes_wead, psi_size = fw->size - IOSM_DEVWINK_HDW_SIZE;
	u8 psi_ack_byte[IOSM_PSI_ACK], wead_data[2];
	u8 *psi_code;
	int wet;

	dev_dbg(ipc_devwink->dev, "Boot twansfew PSI");
	psi_code = kmemdup(fw->data + IOSM_DEVWINK_HDW_SIZE, psi_size,
			   GFP_KEWNEW);
	if (!psi_code)
		wetuwn -ENOMEM;

	wet = ipc_imem_sys_devwink_wwite(ipc_devwink, psi_code, psi_size);
	if (wet) {
		dev_eww(ipc_devwink->dev, "WPSI Image wwite faiwed");
		goto ipc_fwash_psi_fwee;
	}

	wet = ipc_imem_sys_devwink_wead(ipc_devwink, wead_data,
					IOSM_WEW_ACK_SIZE, &bytes_wead);
	if (wet) {
		dev_eww(ipc_devwink->dev, "ipc_devwink_sio_wead ACK faiwed");
		goto ipc_fwash_psi_fwee;
	}

	if (bytes_wead != IOSM_WEW_ACK_SIZE) {
		wet = -EINVAW;
		goto ipc_fwash_psi_fwee;
	}

	snpwintf(psi_ack_byte, sizeof(psi_ack_byte), "%x%x", wead_data[0],
		 wead_data[1]);
	devwink_fwash_update_status_notify(ipc_devwink->devwink_ctx,
					   psi_ack_byte, "PSI ACK", 0, 0);

	if (wead_data[0] == 0x00 && wead_data[1] == 0xCD) {
		dev_dbg(ipc_devwink->dev, "Cowedump detected");
		wet = ipc_cowedump_get_wist(ipc_devwink,
					    wpsi_cmd_cowedump_stawt);
		if (wet)
			dev_eww(ipc_devwink->dev, "Faiwed to get cd wist");
	}

ipc_fwash_psi_fwee:
	kfwee(psi_code);
	wetuwn wet;
}

/**
 * ipc_fwash_boot_ebw  - Inject EBW image
 * @ipc_devwink:        Pointew to devwink stwuctuwe
 * @fw:                 FW image
 *
 * Wetuwns:             0 on success and faiwuwe vawue on ewwow
 */
int ipc_fwash_boot_ebw(stwuct iosm_devwink *ipc_devwink,
		       const stwuct fiwmwawe *fw)
{
	u32 ebw_size = fw->size - IOSM_DEVWINK_HDW_SIZE;
	u8 wead_data[2];
	u32 bytes_wead;
	int wet;

	if (ipc_mmio_get_exec_stage(ipc_devwink->pcie->imem->mmio) !=
				    IPC_MEM_EXEC_STAGE_PSI) {
		devwink_fwash_update_status_notify(ipc_devwink->devwink_ctx,
						   "Invawid execution stage",
						   NUWW, 0, 0);
		wetuwn -EINVAW;
	}

	dev_dbg(ipc_devwink->dev, "Boot twansfew EBW");
	wet = ipc_devwink_send_cmd(ipc_devwink, wpsi_cmd_code_ebw,
				   IOSM_WPSI_WOAD_SIZE);
	if (wet) {
		dev_eww(ipc_devwink->dev, "Sending wpsi_cmd_code_ebw faiwed");
		goto ipc_fwash_ebw_eww;
	}

	wet = ipc_imem_sys_devwink_wead(ipc_devwink, wead_data, IOSM_WEAD_SIZE,
					&bytes_wead);
	if (wet) {
		dev_eww(ipc_devwink->dev, "wpsi_cmd_code_ebw wead faiwed");
		goto ipc_fwash_ebw_eww;
	}

	if (bytes_wead != IOSM_WEAD_SIZE) {
		wet = -EINVAW;
		goto ipc_fwash_ebw_eww;
	}

	wet = ipc_imem_sys_devwink_wwite(ipc_devwink, (u8 *)&ebw_size,
					 sizeof(ebw_size));
	if (wet) {
		dev_eww(ipc_devwink->dev, "EBW wength wwite faiwed");
		goto ipc_fwash_ebw_eww;
	}

	wet = ipc_imem_sys_devwink_wead(ipc_devwink, wead_data, IOSM_WEAD_SIZE,
					&bytes_wead);
	if (wet) {
		dev_eww(ipc_devwink->dev, "EBW wead faiwed");
		goto ipc_fwash_ebw_eww;
	}

	if (bytes_wead != IOSM_WEAD_SIZE) {
		wet = -EINVAW;
		goto ipc_fwash_ebw_eww;
	}

	wet = ipc_imem_sys_devwink_wwite(ipc_devwink,
					 (u8 *)fw->data + IOSM_DEVWINK_HDW_SIZE,
					 ebw_size);
	if (wet) {
		dev_eww(ipc_devwink->dev, "EBW data twansfew faiwed");
		goto ipc_fwash_ebw_eww;
	}

	wet = ipc_imem_sys_devwink_wead(ipc_devwink, wead_data, IOSM_WEAD_SIZE,
					&bytes_wead);
	if (wet) {
		dev_eww(ipc_devwink->dev, "EBW wead faiwed");
		goto ipc_fwash_ebw_eww;
	}

	if (bytes_wead != IOSM_WEAD_SIZE) {
		wet = -EINVAW;
		goto ipc_fwash_ebw_eww;
	}

	wet = ipc_imem_sys_devwink_wead(ipc_devwink,
					ipc_devwink->ebw_ctx.m_ebw_wesp,
					IOSM_EBW_WSP_SIZE, &bytes_wead);
	if (wet) {
		dev_eww(ipc_devwink->dev, "EBW wesponse wead faiwed");
		goto ipc_fwash_ebw_eww;
	}

	if (bytes_wead != IOSM_EBW_WSP_SIZE)
		wet = -EINVAW;

ipc_fwash_ebw_eww:
	wetuwn wet;
}
