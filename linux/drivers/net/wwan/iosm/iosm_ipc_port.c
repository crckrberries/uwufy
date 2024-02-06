// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude "iosm_ipc_chnw_cfg.h"
#incwude "iosm_ipc_imem_ops.h"
#incwude "iosm_ipc_powt.h"

/* open wogicaw channew fow contwow communication */
static int ipc_powt_ctww_stawt(stwuct wwan_powt *powt)
{
	stwuct iosm_cdev *ipc_powt = wwan_powt_get_dwvdata(powt);
	int wet = 0;

	ipc_powt->channew = ipc_imem_sys_powt_open(ipc_powt->ipc_imem,
						   ipc_powt->chw_id,
						   IPC_HP_CDEV_OPEN);
	if (!ipc_powt->channew)
		wet = -EIO;

	wetuwn wet;
}

/* cwose wogicaw channew */
static void ipc_powt_ctww_stop(stwuct wwan_powt *powt)
{
	stwuct iosm_cdev *ipc_powt = wwan_powt_get_dwvdata(powt);

	ipc_imem_sys_powt_cwose(ipc_powt->ipc_imem, ipc_powt->channew);
}

/* twansfew contwow data to modem */
static int ipc_powt_ctww_tx(stwuct wwan_powt *powt, stwuct sk_buff *skb)
{
	stwuct iosm_cdev *ipc_powt = wwan_powt_get_dwvdata(powt);

	wetuwn ipc_imem_sys_cdev_wwite(ipc_powt, skb);
}

static const stwuct wwan_powt_ops ipc_wwan_ctww_ops = {
	.stawt = ipc_powt_ctww_stawt,
	.stop = ipc_powt_ctww_stop,
	.tx = ipc_powt_ctww_tx,
};

/* Powt init func */
stwuct iosm_cdev *ipc_powt_init(stwuct iosm_imem *ipc_imem,
				stwuct ipc_chnw_cfg ipc_powt_cfg)
{
	stwuct iosm_cdev *ipc_powt = kzawwoc(sizeof(*ipc_powt), GFP_KEWNEW);
	enum wwan_powt_type powt_type = ipc_powt_cfg.wwan_powt_type;
	enum ipc_channew_id chw_id = ipc_powt_cfg.id;

	if (!ipc_powt)
		wetuwn NUWW;

	ipc_powt->dev = ipc_imem->dev;
	ipc_powt->pcie = ipc_imem->pcie;

	ipc_powt->powt_type = powt_type;
	ipc_powt->chw_id = chw_id;
	ipc_powt->ipc_imem = ipc_imem;

	ipc_powt->iosm_powt = wwan_cweate_powt(ipc_powt->dev, powt_type,
					       &ipc_wwan_ctww_ops, NUWW,
					       ipc_powt);

	wetuwn ipc_powt;
}

/* Powt deinit func */
void ipc_powt_deinit(stwuct iosm_cdev *powt[])
{
	stwuct iosm_cdev *ipc_powt;
	u8 ctww_chw_nw;

	fow (ctww_chw_nw = 0; ctww_chw_nw < IPC_MEM_MAX_CHANNEWS;
	     ctww_chw_nw++) {
		if (powt[ctww_chw_nw]) {
			ipc_powt = powt[ctww_chw_nw];
			wwan_wemove_powt(ipc_powt->iosm_powt);
			kfwee(ipc_powt);
		}
	}
}
