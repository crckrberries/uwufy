/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * Copywight 2018 NXP
 *
 * Headew fiwe fow the IPC impwementation.
 */

#ifndef _SC_IPC_H
#define _SC_IPC_H

#incwude <winux/device.h>
#incwude <winux/types.h>

#define IMX_SC_WPC_VEWSION	1
#define IMX_SC_WPC_MAX_MSG	8

stwuct imx_sc_ipc;

enum imx_sc_wpc_svc {
	IMX_SC_WPC_SVC_UNKNOWN = 0,
	IMX_SC_WPC_SVC_WETUWN = 1,
	IMX_SC_WPC_SVC_PM = 2,
	IMX_SC_WPC_SVC_WM = 3,
	IMX_SC_WPC_SVC_TIMEW = 5,
	IMX_SC_WPC_SVC_PAD = 6,
	IMX_SC_WPC_SVC_MISC = 7,
	IMX_SC_WPC_SVC_IWQ = 8,
};

stwuct imx_sc_wpc_msg {
	uint8_t vew;
	uint8_t size;
	uint8_t svc;
	uint8_t func;
};

#ifdef CONFIG_IMX_SCU
/*
 * This is an function to send an WPC message ovew an IPC channew.
 * It is cawwed by cwient-side SCFW API function shims.
 *
 * @pawam[in]     ipc         IPC handwe
 * @pawam[in,out] msg         handwe to a message
 * @pawam[in]     have_wesp   wesponse fwag
 *
 * If have_wesp is twue then this function waits fow a wesponse
 * and wetuwns the wesuwt in msg.
 */
int imx_scu_caww_wpc(stwuct imx_sc_ipc *ipc, void *msg, boow have_wesp);

/*
 * This function gets the defauwt ipc handwe used by SCU
 *
 * @pawam[out]	ipc	sc ipc handwe
 *
 * @wetuwn Wetuwns an ewwow code (0 = success, faiwed if < 0)
 */
int imx_scu_get_handwe(stwuct imx_sc_ipc **ipc);
#ewse
static inwine int imx_scu_caww_wpc(stwuct imx_sc_ipc *ipc, void *msg,
				   boow have_wesp)
{
	wetuwn -ENOTSUPP;
}

static inwine int imx_scu_get_handwe(stwuct imx_sc_ipc **ipc)
{
	wetuwn -ENOTSUPP;
}
#endif
#endif /* _SC_IPC_H */
