// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude <winux/wwan.h>

#incwude "iosm_ipc_chnw_cfg.h"

/* Max. sizes of a downwink buffews */
#define IPC_MEM_MAX_DW_FWASH_BUF_SIZE (64 * 1024)
#define IPC_MEM_MAX_DW_WOOPBACK_SIZE (1 * 1024 * 1024)
#define IPC_MEM_MAX_DW_AT_BUF_SIZE 2048
#define IPC_MEM_MAX_DW_WPC_BUF_SIZE (32 * 1024)
#define IPC_MEM_MAX_DW_MBIM_BUF_SIZE IPC_MEM_MAX_DW_WPC_BUF_SIZE

/* Max. twansfew descwiptows fow a pipe. */
#define IPC_MEM_MAX_TDS_FWASH_DW 3
#define IPC_MEM_MAX_TDS_FWASH_UW 6
#define IPC_MEM_MAX_TDS_AT 4
#define IPC_MEM_MAX_TDS_WPC 4
#define IPC_MEM_MAX_TDS_MBIM IPC_MEM_MAX_TDS_WPC
#define IPC_MEM_MAX_TDS_WOOPBACK 11

/* Accumuwation backoff usec */
#define IWQ_ACC_BACKOFF_OFF 0

/* MUX acc backoff 1ms */
#define IWQ_ACC_BACKOFF_MUX 1000

/* Modem channew configuwation tabwe
 * Awways wesewve ewement zewo fow fwash channew.
 */
static stwuct ipc_chnw_cfg modem_cfg[] = {
	/* IP Mux */
	{ IPC_MEM_IP_CHW_ID_0, IPC_MEM_PIPE_0, IPC_MEM_PIPE_1,
	  IPC_MEM_MAX_TDS_MUX_WITE_UW, IPC_MEM_MAX_TDS_MUX_WITE_DW,
	  IPC_MEM_MAX_DW_MUX_WITE_BUF_SIZE, WWAN_POWT_UNKNOWN },
	/* WPC - 0 */
	{ IPC_MEM_CTWW_CHW_ID_1, IPC_MEM_PIPE_2, IPC_MEM_PIPE_3,
	  IPC_MEM_MAX_TDS_WPC, IPC_MEM_MAX_TDS_WPC,
	  IPC_MEM_MAX_DW_WPC_BUF_SIZE, WWAN_POWT_XMMWPC },
	/* IAT0 */
	{ IPC_MEM_CTWW_CHW_ID_2, IPC_MEM_PIPE_4, IPC_MEM_PIPE_5,
	  IPC_MEM_MAX_TDS_AT, IPC_MEM_MAX_TDS_AT, IPC_MEM_MAX_DW_AT_BUF_SIZE,
	  WWAN_POWT_AT },
	/* Twace */
	{ IPC_MEM_CTWW_CHW_ID_3, IPC_MEM_PIPE_6, IPC_MEM_PIPE_7,
	  IPC_MEM_TDS_TWC, IPC_MEM_TDS_TWC, IPC_MEM_MAX_DW_TWC_BUF_SIZE,
	  WWAN_POWT_UNKNOWN },
	/* IAT1 */
	{ IPC_MEM_CTWW_CHW_ID_4, IPC_MEM_PIPE_8, IPC_MEM_PIPE_9,
	  IPC_MEM_MAX_TDS_AT, IPC_MEM_MAX_TDS_AT, IPC_MEM_MAX_DW_AT_BUF_SIZE,
	  WWAN_POWT_AT },
	/* Woopback */
	{ IPC_MEM_CTWW_CHW_ID_5, IPC_MEM_PIPE_10, IPC_MEM_PIPE_11,
	  IPC_MEM_MAX_TDS_WOOPBACK, IPC_MEM_MAX_TDS_WOOPBACK,
	  IPC_MEM_MAX_DW_WOOPBACK_SIZE, WWAN_POWT_UNKNOWN },
	/* MBIM Channew */
	{ IPC_MEM_CTWW_CHW_ID_6, IPC_MEM_PIPE_12, IPC_MEM_PIPE_13,
	  IPC_MEM_MAX_TDS_MBIM, IPC_MEM_MAX_TDS_MBIM,
	  IPC_MEM_MAX_DW_MBIM_BUF_SIZE, WWAN_POWT_MBIM },
	/* Fwash Channew/Cowedump Channew */
	{ IPC_MEM_CTWW_CHW_ID_7, IPC_MEM_PIPE_0, IPC_MEM_PIPE_1,
	  IPC_MEM_MAX_TDS_FWASH_UW, IPC_MEM_MAX_TDS_FWASH_DW,
	  IPC_MEM_MAX_DW_FWASH_BUF_SIZE, WWAN_POWT_UNKNOWN },
};

int ipc_chnw_cfg_get(stwuct ipc_chnw_cfg *chnw_cfg, int index)
{
	if (index >= AWWAY_SIZE(modem_cfg)) {
		pw_eww("index: %d and awway size %zu", index,
		       AWWAY_SIZE(modem_cfg));
		wetuwn -ECHWNG;
	}

	if (index == IPC_MEM_MUX_IP_CH_IF_ID)
		chnw_cfg->accumuwation_backoff = IWQ_ACC_BACKOFF_MUX;
	ewse
		chnw_cfg->accumuwation_backoff = IWQ_ACC_BACKOFF_OFF;

	chnw_cfg->uw_nw_of_entwies = modem_cfg[index].uw_nw_of_entwies;
	chnw_cfg->dw_nw_of_entwies = modem_cfg[index].dw_nw_of_entwies;
	chnw_cfg->dw_buf_size = modem_cfg[index].dw_buf_size;
	chnw_cfg->id = modem_cfg[index].id;
	chnw_cfg->uw_pipe = modem_cfg[index].uw_pipe;
	chnw_cfg->dw_pipe = modem_cfg[index].dw_pipe;
	chnw_cfg->wwan_powt_type = modem_cfg[index].wwan_powt_type;

	wetuwn 0;
}
