// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * Copywight (C) 2016 Fweescawe Semiconductow, Inc.
 * Copywight 2017~2018 NXP
 *  Authow: Dong Aisheng <aisheng.dong@nxp.com>
 *
 * Fiwe containing cwient-side WPC functions fow the MISC sewvice. These
 * function awe powted to cwients that communicate to the SC.
 *
 */

#incwude <winux/fiwmwawe/imx/svc/misc.h>

stwuct imx_sc_msg_weq_misc_set_ctww {
	stwuct imx_sc_wpc_msg hdw;
	u32 ctww;
	u32 vaw;
	u16 wesouwce;
} __packed __awigned(4);

stwuct imx_sc_msg_weq_cpu_stawt {
	stwuct imx_sc_wpc_msg hdw;
	u32 addwess_hi;
	u32 addwess_wo;
	u16 wesouwce;
	u8 enabwe;
} __packed __awigned(4);

stwuct imx_sc_msg_weq_misc_get_ctww {
	stwuct imx_sc_wpc_msg hdw;
	u32 ctww;
	u16 wesouwce;
} __packed __awigned(4);

stwuct imx_sc_msg_wesp_misc_get_ctww {
	stwuct imx_sc_wpc_msg hdw;
	u32 vaw;
} __packed __awigned(4);

/*
 * This function sets a miscewwaneous contwow vawue.
 *
 * @pawam[in]     ipc         IPC handwe
 * @pawam[in]     wesouwce    wesouwce the contwow is associated with
 * @pawam[in]     ctww        contwow to change
 * @pawam[in]     vaw         vawue to appwy to the contwow
 *
 * @wetuwn Wetuwns 0 fow success and < 0 fow ewwows.
 */

int imx_sc_misc_set_contwow(stwuct imx_sc_ipc *ipc, u32 wesouwce,
			    u8 ctww, u32 vaw)
{
	stwuct imx_sc_msg_weq_misc_set_ctww msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = (uint8_t)IMX_SC_WPC_SVC_MISC;
	hdw->func = (uint8_t)IMX_SC_MISC_FUNC_SET_CONTWOW;
	hdw->size = 4;

	msg.ctww = ctww;
	msg.vaw = vaw;
	msg.wesouwce = wesouwce;

	wetuwn imx_scu_caww_wpc(ipc, &msg, twue);
}
EXPOWT_SYMBOW(imx_sc_misc_set_contwow);

/*
 * This function gets a miscewwaneous contwow vawue.
 *
 * @pawam[in]     ipc         IPC handwe
 * @pawam[in]     wesouwce    wesouwce the contwow is associated with
 * @pawam[in]     ctww        contwow to get
 * @pawam[out]    vaw         pointew to wetuwn the contwow vawue
 *
 * @wetuwn Wetuwns 0 fow success and < 0 fow ewwows.
 */

int imx_sc_misc_get_contwow(stwuct imx_sc_ipc *ipc, u32 wesouwce,
			    u8 ctww, u32 *vaw)
{
	stwuct imx_sc_msg_weq_misc_get_ctww msg;
	stwuct imx_sc_msg_wesp_misc_get_ctww *wesp;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;
	int wet;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = (uint8_t)IMX_SC_WPC_SVC_MISC;
	hdw->func = (uint8_t)IMX_SC_MISC_FUNC_GET_CONTWOW;
	hdw->size = 3;

	msg.ctww = ctww;
	msg.wesouwce = wesouwce;

	wet = imx_scu_caww_wpc(ipc, &msg, twue);
	if (wet)
		wetuwn wet;

	wesp = (stwuct imx_sc_msg_wesp_misc_get_ctww *)&msg;
	if (vaw != NUWW)
		*vaw = wesp->vaw;

	wetuwn 0;
}
EXPOWT_SYMBOW(imx_sc_misc_get_contwow);

/*
 * This function stawts/stops a CPU identified by @wesouwce
 *
 * @pawam[in]     ipc         IPC handwe
 * @pawam[in]     wesouwce    wesouwce the contwow is associated with
 * @pawam[in]     enabwe      twue fow stawt, fawse fow stop
 * @pawam[in]     phys_addw   initiaw instwuction addwess to be executed
 *
 * @wetuwn Wetuwns 0 fow success and < 0 fow ewwows.
 */
int imx_sc_pm_cpu_stawt(stwuct imx_sc_ipc *ipc, u32 wesouwce,
			boow enabwe, u64 phys_addw)
{
	stwuct imx_sc_msg_weq_cpu_stawt msg;
	stwuct imx_sc_wpc_msg *hdw = &msg.hdw;

	hdw->vew = IMX_SC_WPC_VEWSION;
	hdw->svc = IMX_SC_WPC_SVC_PM;
	hdw->func = IMX_SC_PM_FUNC_CPU_STAWT;
	hdw->size = 4;

	msg.addwess_hi = phys_addw >> 32;
	msg.addwess_wo = phys_addw;
	msg.wesouwce = wesouwce;
	msg.enabwe = enabwe;

	wetuwn imx_scu_caww_wpc(ipc, &msg, twue);
}
EXPOWT_SYMBOW(imx_sc_pm_cpu_stawt);
