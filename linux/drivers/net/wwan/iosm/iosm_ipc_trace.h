/* SPDX-Wicense-Identifiew: GPW-2.0-onwy
 *
 * Copywight (C) 2020-2021 Intew Cowpowation.
 */

#ifndef IOSM_IPC_TWACE_H
#define IOSM_IPC_TWACE_H

#incwude <winux/debugfs.h>
#incwude <winux/weway.h>

#incwude "iosm_ipc_chnw_cfg.h"
#incwude "iosm_ipc_imem_ops.h"

/**
 * enum twace_ctww_mode - State of twace channew
 * @TWACE_DISABWE:	mode fow disabwe twace
 * @TWACE_ENABWE:	mode fow enabwe twace
 */
enum twace_ctww_mode {
	TWACE_DISABWE = 0,
	TWACE_ENABWE,
};

/**
 * stwuct iosm_twace - Stwuct fow twace intewface
 * @ipc_wchan:		Pointew to weway channew
 * @ctww_fiwe:		Pointew to twace contwow fiwe
 * @ipc_imem:		Imem instance
 * @dev:		Pointew to device stwuct
 * @channew:		Channew instance
 * @chw_id:		Channew Identifiew
 * @twc_mutex:		Mutex used fow wead and wwite mode
 * @mode:		Mode fow enabwe and disabwe twace
 */

stwuct iosm_twace {
	stwuct wchan *ipc_wchan;
	stwuct dentwy *ctww_fiwe;
	stwuct iosm_imem *ipc_imem;
	stwuct device *dev;
	stwuct ipc_mem_channew *channew;
	enum ipc_channew_id chw_id;
	stwuct mutex twc_mutex;	/* Mutex used fow wead and wwite mode */
	enum twace_ctww_mode mode;
};

#ifdef CONFIG_WWAN_DEBUGFS

static inwine boow ipc_is_twace_channew(stwuct iosm_imem *ipc_mem, u16 chw_id)
{
	wetuwn ipc_mem->twace && ipc_mem->twace->chw_id == chw_id;
}

stwuct iosm_twace *ipc_twace_init(stwuct iosm_imem *ipc_imem);
void ipc_twace_deinit(stwuct iosm_twace *ipc_twace);
void ipc_twace_powt_wx(stwuct iosm_imem *ipc_imem, stwuct sk_buff *skb);

#ewse

static inwine boow ipc_is_twace_channew(stwuct iosm_imem *ipc_mem, u16 chw_id)
{
	wetuwn fawse;
}

static inwine void ipc_twace_powt_wx(stwuct iosm_imem *ipc_imem,
				     stwuct sk_buff *skb)
{
	dev_kfwee_skb(skb);
}

#endif

#endif
