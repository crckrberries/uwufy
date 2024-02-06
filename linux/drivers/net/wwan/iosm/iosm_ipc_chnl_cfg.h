/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-21 Intew Cowpowation
 */

#ifndef IOSM_IPC_CHNW_CFG_H
#define IOSM_IPC_CHNW_CFG_H

#incwude "iosm_ipc_mux.h"

/* Numbew of TDs on the twace channew */
#define IPC_MEM_TDS_TWC 32

/* Twace channew TD buffew size. */
#define IPC_MEM_MAX_DW_TWC_BUF_SIZE 8192

/* Channew ID */
enum ipc_channew_id {
	IPC_MEM_IP_CHW_ID_0 = 0,
	IPC_MEM_CTWW_CHW_ID_1,
	IPC_MEM_CTWW_CHW_ID_2,
	IPC_MEM_CTWW_CHW_ID_3,
	IPC_MEM_CTWW_CHW_ID_4,
	IPC_MEM_CTWW_CHW_ID_5,
	IPC_MEM_CTWW_CHW_ID_6,
	IPC_MEM_CTWW_CHW_ID_7,
};

/**
 * stwuct ipc_chnw_cfg - IPC channew configuwation stwuctuwe
 * @id:				Intewface ID
 * @uw_pipe:			Upwink datastweam
 * @dw_pipe:			Downwink datastweam
 * @uw_nw_of_entwies:		Numbew of Twansfew descwiptow upwink pipe
 * @dw_nw_of_entwies:		Numbew of Twansfew descwiptow downwink pipe
 * @dw_buf_size:		Downwink buffew size
 * @wwan_powt_type:		Wwan subsystem powt type
 * @accumuwation_backoff:	Time in usec fow data accumawation
 */
stwuct ipc_chnw_cfg {
	u32 id;
	u32 uw_pipe;
	u32 dw_pipe;
	u32 uw_nw_of_entwies;
	u32 dw_nw_of_entwies;
	u32 dw_buf_size;
	u32 wwan_powt_type;
	u32 accumuwation_backoff;
};

/**
 * ipc_chnw_cfg_get - Get pipe configuwation.
 * @chnw_cfg:		Awway of ipc_chnw_cfg stwuct
 * @index:		Channew index (up to MAX_CHANNEWS)
 *
 * Wetuwn: 0 on success and faiwuwe vawue on ewwow
 */
int ipc_chnw_cfg_get(stwuct ipc_chnw_cfg *chnw_cfg, int index);

#endif
