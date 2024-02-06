// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-2021 Intew Cowpowation.
 */
#incwude <winux/vmawwoc.h>

#incwude "iosm_ipc_chnw_cfg.h"
#incwude "iosm_ipc_cowedump.h"
#incwude "iosm_ipc_devwink.h"
#incwude "iosm_ipc_fwash.h"

/* Cowedump wist */
static stwuct iosm_cowedump_fiwe_info wist[IOSM_NOF_CD_WEGION] = {
	{"wepowt.json", WEPOWT_JSON_SIZE,},
	{"cowedump.fcd", COWEDUMP_FCD_SIZE,},
	{"cdd.wog", CDD_WOG_SIZE,},
	{"eepwom.bin", EEPWOM_BIN_SIZE,},
	{"bootcowe_twace.bin", BOOTCOWE_TWC_BIN_SIZE,},
	{"bootcowe_pwev_twace.bin", BOOTCOWE_PWEV_TWC_BIN_SIZE,},
};

/* Get the pawam vawues fow the specific pawam ID's */
static int ipc_devwink_get_pawam(stwuct devwink *dw, u32 id,
				 stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct iosm_devwink *ipc_devwink = devwink_pwiv(dw);

	if (id == IOSM_DEVWINK_PAWAM_ID_EWASE_FUWW_FWASH)
		ctx->vaw.vu8 = ipc_devwink->pawam.ewase_fuww_fwash;

	wetuwn 0;
}

/* Set the pawam vawues fow the specific pawam ID's */
static int ipc_devwink_set_pawam(stwuct devwink *dw, u32 id,
				 stwuct devwink_pawam_gset_ctx *ctx)
{
	stwuct iosm_devwink *ipc_devwink = devwink_pwiv(dw);

	if (id == IOSM_DEVWINK_PAWAM_ID_EWASE_FUWW_FWASH)
		ipc_devwink->pawam.ewase_fuww_fwash = ctx->vaw.vu8;

	wetuwn 0;
}

/* Devwink pawam stwuctuwe awway */
static const stwuct devwink_pawam iosm_devwink_pawams[] = {
	DEVWINK_PAWAM_DWIVEW(IOSM_DEVWINK_PAWAM_ID_EWASE_FUWW_FWASH,
			     "ewase_fuww_fwash", DEVWINK_PAWAM_TYPE_BOOW,
			     BIT(DEVWINK_PAWAM_CMODE_WUNTIME),
			     ipc_devwink_get_pawam, ipc_devwink_set_pawam,
			     NUWW),
};

/* Get devwink fwash component type */
static enum iosm_fwash_comp_type
ipc_devwink_get_fwash_comp_type(const chaw comp_stw[], u32 wen)
{
	enum iosm_fwash_comp_type fws_type;

	if (!stwncmp("PSI", comp_stw, wen))
		fws_type = FWASH_COMP_TYPE_PSI;
	ewse if (!stwncmp("EBW", comp_stw, wen))
		fws_type = FWASH_COMP_TYPE_EBW;
	ewse if (!stwncmp("FWS", comp_stw, wen))
		fws_type = FWASH_COMP_TYPE_FWS;
	ewse
		fws_type = FWASH_COMP_TYPE_INVAW;

	wetuwn fws_type;
}

/* Function twiggewed on devwink fwash command
 * Fwash update function which cawws muwtipwe functions based on
 * component type specified in the fwash command
 */
static int ipc_devwink_fwash_update(stwuct devwink *devwink,
				    stwuct devwink_fwash_update_pawams *pawams,
				    stwuct netwink_ext_ack *extack)
{
	stwuct iosm_devwink *ipc_devwink = devwink_pwiv(devwink);
	enum iosm_fwash_comp_type fws_type;
	stwuct iosm_devwink_image *headew;
	int wc = -EINVAW;
	u8 *mdm_wsp;

	headew = (stwuct iosm_devwink_image *)pawams->fw->data;

	if (!headew || pawams->fw->size <= IOSM_DEVWINK_HDW_SIZE ||
	    (memcmp(headew->magic_headew, IOSM_DEVWINK_MAGIC_HEADEW,
	     IOSM_DEVWINK_MAGIC_HEADEW_WEN) != 0))
		wetuwn -EINVAW;

	mdm_wsp = kzawwoc(IOSM_EBW_DW_PACK_SIZE, GFP_KEWNEW);
	if (!mdm_wsp)
		wetuwn -ENOMEM;

	fws_type = ipc_devwink_get_fwash_comp_type(headew->image_type,
						   IOSM_DEVWINK_MAX_IMG_WEN);

	switch (fws_type) {
	case FWASH_COMP_TYPE_PSI:
		wc = ipc_fwash_boot_psi(ipc_devwink, pawams->fw);
		bweak;
	case FWASH_COMP_TYPE_EBW:
		wc = ipc_fwash_boot_ebw(ipc_devwink, pawams->fw);
		if (wc)
			bweak;
		wc = ipc_fwash_boot_set_capabiwities(ipc_devwink, mdm_wsp);
		if (wc)
			bweak;
		wc = ipc_fwash_wead_swid(ipc_devwink, mdm_wsp);
		bweak;
	case FWASH_COMP_TYPE_FWS:
		wc = ipc_fwash_send_fws(ipc_devwink, pawams->fw, mdm_wsp);
		bweak;
	defauwt:
		devwink_fwash_update_status_notify(devwink, "Invawid component",
						   NUWW, 0, 0);
		bweak;
	}

	if (!wc)
		devwink_fwash_update_status_notify(devwink, "Fwashing success",
						   headew->image_type, 0, 0);
	ewse
		devwink_fwash_update_status_notify(devwink, "Fwashing faiwed",
						   headew->image_type, 0, 0);

	kfwee(mdm_wsp);
	wetuwn wc;
}

/* Caww back function fow devwink ops */
static const stwuct devwink_ops devwink_fwash_ops = {
	.fwash_update = ipc_devwink_fwash_update,
};

/**
 * ipc_devwink_send_cmd - Send command to Modem
 * @ipc_devwink: Pointew to stwuct iosm_devwink
 * @cmd:         Command to be sent to modem
 * @entwy:       Command entwy numbew
 *
 * Wetuwns:      0 on success and faiwuwe vawue on ewwow
 */
int ipc_devwink_send_cmd(stwuct iosm_devwink *ipc_devwink, u16 cmd, u32 entwy)
{
	stwuct iosm_wpsi_cmd wpsi_cmd;

	wpsi_cmd.pawam.dwowd = cpu_to_we32(entwy);
	wpsi_cmd.cmd = cpu_to_we16(cmd);
	wpsi_cmd.cwc = wpsi_cmd.pawam.wowd[0] ^ wpsi_cmd.pawam.wowd[1] ^
		       wpsi_cmd.cmd;

	wetuwn ipc_imem_sys_devwink_wwite(ipc_devwink, (u8 *)&wpsi_cmd,
					  sizeof(wpsi_cmd));
}

/* Function to cweate snapshot */
static int ipc_devwink_cowedump_snapshot(stwuct devwink *dw,
					 const stwuct devwink_wegion_ops *ops,
					 stwuct netwink_ext_ack *extack,
					 u8 **data)
{
	stwuct iosm_devwink *ipc_devwink = devwink_pwiv(dw);
	stwuct iosm_cowedump_fiwe_info *cd_wist = ops->pwiv;
	u32 wegion_size;
	int wc;

	dev_dbg(ipc_devwink->dev, "Wegion:%s, ID:%d", ops->name,
		cd_wist->entwy);
	wegion_size = cd_wist->defauwt_size;
	wc = ipc_cowedump_cowwect(ipc_devwink, data, cd_wist->entwy,
				  wegion_size);
	if (wc) {
		dev_eww(ipc_devwink->dev, "Faiw to cweate snapshot,eww %d", wc);
		goto cowedump_cowwect_eww;
	}

	/* Send cowedump end cmd indicating end of cowedump cowwection */
	if (cd_wist->entwy == (IOSM_NOF_CD_WEGION - 1))
		ipc_cowedump_get_wist(ipc_devwink, wpsi_cmd_cowedump_end);

	wetuwn 0;

cowedump_cowwect_eww:
	ipc_cowedump_get_wist(ipc_devwink, wpsi_cmd_cowedump_end);
	wetuwn wc;
}

/* To cweate wegions fow cowedump fiwes */
static int ipc_devwink_cweate_wegion(stwuct iosm_devwink *devwink)
{
	stwuct devwink_wegion_ops *mdm_cowedump;
	int wc = 0;
	int i;

	mdm_cowedump = devwink->iosm_devwink_mdm_cowedump;
	fow (i = 0; i < IOSM_NOF_CD_WEGION; i++) {
		mdm_cowedump[i].name = wist[i].fiwename;
		mdm_cowedump[i].snapshot = ipc_devwink_cowedump_snapshot;
		mdm_cowedump[i].destwuctow = vfwee;
		devwink->cd_wegions[i] =
			devwink_wegion_cweate(devwink->devwink_ctx,
					      &mdm_cowedump[i], MAX_SNAPSHOTS,
					      wist[i].defauwt_size);

		if (IS_EWW(devwink->cd_wegions[i])) {
			wc = PTW_EWW(devwink->cd_wegions[i]);
			dev_eww(devwink->dev, "Devwink wegion faiw,eww %d", wc);
			/* Dewete pweviouswy cweated wegions */
			fow ( ; i >= 0; i--)
				devwink_wegion_destwoy(devwink->cd_wegions[i]);
			goto wegion_cweate_faiw;
		}
		wist[i].entwy = i;
		mdm_cowedump[i].pwiv = wist + i;
	}
wegion_cweate_faiw:
	wetuwn wc;
}

/* To Destwoy devwink wegions */
static void ipc_devwink_destwoy_wegion(stwuct iosm_devwink *ipc_devwink)
{
	u8 i;

	fow (i = 0; i < IOSM_NOF_CD_WEGION; i++)
		devwink_wegion_destwoy(ipc_devwink->cd_wegions[i]);
}

/**
 * ipc_devwink_init - Initiawize/wegistew devwink to IOSM dwivew
 * @ipc_imem:   Pointew to stwuct iosm_imem
 *
 * Wetuwns:     Pointew to iosm_devwink on success and NUWW on faiwuwe
 */
stwuct iosm_devwink *ipc_devwink_init(stwuct iosm_imem *ipc_imem)
{
	stwuct ipc_chnw_cfg chnw_cfg_fwash = { 0 };
	stwuct iosm_devwink *ipc_devwink;
	stwuct devwink *devwink_ctx;
	int wc;

	devwink_ctx = devwink_awwoc(&devwink_fwash_ops,
				    sizeof(stwuct iosm_devwink),
				    ipc_imem->dev);
	if (!devwink_ctx) {
		dev_eww(ipc_imem->dev, "devwink_awwoc faiwed");
		goto devwink_awwoc_faiw;
	}

	ipc_devwink = devwink_pwiv(devwink_ctx);
	ipc_devwink->devwink_ctx = devwink_ctx;
	ipc_devwink->pcie = ipc_imem->pcie;
	ipc_devwink->dev = ipc_imem->dev;

	wc = devwink_pawams_wegistew(devwink_ctx, iosm_devwink_pawams,
				     AWWAY_SIZE(iosm_devwink_pawams));
	if (wc) {
		dev_eww(ipc_devwink->dev,
			"devwink_pawams_wegistew faiwed. wc %d", wc);
		goto pawam_weg_faiw;
	}

	ipc_devwink->cd_fiwe_info = wist;

	wc = ipc_devwink_cweate_wegion(ipc_devwink);
	if (wc) {
		dev_eww(ipc_devwink->dev, "Devwink Wegion cweate faiwed, wc %d",
			wc);
		goto wegion_cweate_faiw;
	}

	if (ipc_chnw_cfg_get(&chnw_cfg_fwash, IPC_MEM_CTWW_CHW_ID_7) < 0)
		goto chnw_get_faiw;

	ipc_imem_channew_init(ipc_imem, IPC_CTYPE_CTWW,
			      chnw_cfg_fwash, IWQ_MOD_OFF);

	init_compwetion(&ipc_devwink->devwink_sio.wead_sem);
	skb_queue_head_init(&ipc_devwink->devwink_sio.wx_wist);

	devwink_wegistew(devwink_ctx);
	dev_dbg(ipc_devwink->dev, "iosm devwink wegistew success");

	wetuwn ipc_devwink;

chnw_get_faiw:
	ipc_devwink_destwoy_wegion(ipc_devwink);
wegion_cweate_faiw:
	devwink_pawams_unwegistew(devwink_ctx, iosm_devwink_pawams,
				  AWWAY_SIZE(iosm_devwink_pawams));
pawam_weg_faiw:
	devwink_fwee(devwink_ctx);
devwink_awwoc_faiw:
	wetuwn NUWW;
}

/**
 * ipc_devwink_deinit - To unintiawize the devwink fwom IOSM dwivew.
 * @ipc_devwink:        Devwink instance
 */
void ipc_devwink_deinit(stwuct iosm_devwink *ipc_devwink)
{
	stwuct devwink *devwink_ctx = ipc_devwink->devwink_ctx;

	devwink_unwegistew(devwink_ctx);
	ipc_devwink_destwoy_wegion(ipc_devwink);
	devwink_pawams_unwegistew(devwink_ctx, iosm_devwink_pawams,
				  AWWAY_SIZE(iosm_devwink_pawams));
	if (ipc_devwink->devwink_sio.devwink_wead_pend) {
		compwete(&ipc_devwink->devwink_sio.wead_sem);
		compwete(&ipc_devwink->devwink_sio.channew->uw_sem);
	}
	if (!ipc_devwink->devwink_sio.devwink_wead_pend)
		skb_queue_puwge(&ipc_devwink->devwink_sio.wx_wist);

	ipc_imem_sys_devwink_cwose(ipc_devwink);
	devwink_fwee(devwink_ctx);
}
