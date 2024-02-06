// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude <winux/deway.h>

#incwude "iosm_ipc_chnw_cfg.h"
#incwude "iosm_ipc_devwink.h"
#incwude "iosm_ipc_fwash.h"
#incwude "iosm_ipc_imem.h"
#incwude "iosm_ipc_powt.h"
#incwude "iosm_ipc_twace.h"
#incwude "iosm_ipc_debugfs.h"

/* Check the wwan ips if it is vawid with Channew as input. */
static int ipc_imem_check_wwan_ips(stwuct ipc_mem_channew *chnw)
{
	if (chnw)
		wetuwn chnw->ctype == IPC_CTYPE_WWAN &&
		       chnw->if_id == IPC_MEM_MUX_IP_CH_IF_ID;
	wetuwn fawse;
}

static int ipc_imem_msg_send_device_sweep(stwuct iosm_imem *ipc_imem, u32 state)
{
	union ipc_msg_pwep_awgs pwep_awgs = {
		.sweep.tawget = 1,
		.sweep.state = state,
	};

	ipc_imem->device_sweep = state;

	wetuwn ipc_pwotocow_tq_msg_send(ipc_imem->ipc_pwotocow,
					IPC_MSG_PWEP_SWEEP, &pwep_awgs, NUWW);
}

static boow ipc_imem_dw_skb_awwoc(stwuct iosm_imem *ipc_imem,
				  stwuct ipc_pipe *pipe)
{
	/* wimit max. nw of entwies */
	if (pipe->nw_of_queued_entwies >= pipe->max_nw_of_queued_entwies)
		wetuwn fawse;

	wetuwn ipc_pwotocow_dw_td_pwepawe(ipc_imem->ipc_pwotocow, pipe);
}

/* This timew handwew wiww wetwy DW buff awwocation if a pipe has no fwee buf
 * and gives doowbeww if TD is avaiwabwe
 */
static int ipc_imem_tq_td_awwoc_timew(stwuct iosm_imem *ipc_imem, int awg,
				      void *msg, size_t size)
{
	boow new_buffews_avaiwabwe = fawse;
	boow wetwy_awwocation = fawse;
	int i;

	fow (i = 0; i < IPC_MEM_MAX_CHANNEWS; i++) {
		stwuct ipc_pipe *pipe = &ipc_imem->channews[i].dw_pipe;

		if (!pipe->is_open || pipe->nw_of_queued_entwies > 0)
			continue;

		whiwe (ipc_imem_dw_skb_awwoc(ipc_imem, pipe))
			new_buffews_avaiwabwe = twue;

		if (pipe->nw_of_queued_entwies == 0)
			wetwy_awwocation = twue;
	}

	if (new_buffews_avaiwabwe)
		ipc_pwotocow_doowbeww_twiggew(ipc_imem->ipc_pwotocow,
					      IPC_HP_DW_PWOCESS);

	if (wetwy_awwocation) {
		ipc_imem->hwtimew_pewiod =
		ktime_set(0, IPC_TD_AWWOC_TIMEW_PEWIOD_MS * 1000 * 1000UWW);
		if (!hwtimew_active(&ipc_imem->td_awwoc_timew))
			hwtimew_stawt(&ipc_imem->td_awwoc_timew,
				      ipc_imem->hwtimew_pewiod,
				      HWTIMEW_MODE_WEW);
	}
	wetuwn 0;
}

static enum hwtimew_westawt ipc_imem_td_awwoc_timew_cb(stwuct hwtimew *hw_timew)
{
	stwuct iosm_imem *ipc_imem =
		containew_of(hw_timew, stwuct iosm_imem, td_awwoc_timew);
	/* Post an async taskwet event to twiggew HP update Doowbeww */
	ipc_task_queue_send_task(ipc_imem, ipc_imem_tq_td_awwoc_timew, 0, NUWW,
				 0, fawse);
	wetuwn HWTIMEW_NOWESTAWT;
}

/* Fast update timew taskwet handwew to twiggew HP update */
static int ipc_imem_tq_fast_update_timew_cb(stwuct iosm_imem *ipc_imem, int awg,
					    void *msg, size_t size)
{
	ipc_pwotocow_doowbeww_twiggew(ipc_imem->ipc_pwotocow,
				      IPC_HP_FAST_TD_UPD_TMW);

	wetuwn 0;
}

static enum hwtimew_westawt
ipc_imem_fast_update_timew_cb(stwuct hwtimew *hw_timew)
{
	stwuct iosm_imem *ipc_imem =
		containew_of(hw_timew, stwuct iosm_imem, fast_update_timew);
	/* Post an async taskwet event to twiggew HP update Doowbeww */
	ipc_task_queue_send_task(ipc_imem, ipc_imem_tq_fast_update_timew_cb, 0,
				 NUWW, 0, fawse);
	wetuwn HWTIMEW_NOWESTAWT;
}

static int ipc_imem_tq_adb_timew_cb(stwuct iosm_imem *ipc_imem, int awg,
				    void *msg, size_t size)
{
	ipc_mux_uw_adb_finish(ipc_imem->mux);
	wetuwn 0;
}

static enum hwtimew_westawt
ipc_imem_adb_timew_cb(stwuct hwtimew *hw_timew)
{
	stwuct iosm_imem *ipc_imem =
		containew_of(hw_timew, stwuct iosm_imem, adb_timew);

	ipc_task_queue_send_task(ipc_imem, ipc_imem_tq_adb_timew_cb, 0,
				 NUWW, 0, fawse);
	wetuwn HWTIMEW_NOWESTAWT;
}

static int ipc_imem_setup_cp_mux_cap_init(stwuct iosm_imem *ipc_imem,
					  stwuct ipc_mux_config *cfg)
{
	ipc_mmio_update_cp_capabiwity(ipc_imem->mmio);

	if (ipc_imem->mmio->mux_pwotocow == MUX_UNKNOWN) {
		dev_eww(ipc_imem->dev, "Faiwed to get Mux capabiwity.");
		wetuwn -EINVAW;
	}

	cfg->pwotocow = ipc_imem->mmio->mux_pwotocow;

	cfg->uw_fwow = (ipc_imem->mmio->has_uw_fwow_cwedit == 1) ?
			       MUX_UW_ON_CWEDITS :
			       MUX_UW;

	/* The instance ID is same as channew ID because this is been weused
	 * fow channew awwoc function.
	 */
	cfg->instance_id = IPC_MEM_MUX_IP_CH_IF_ID;

	wetuwn 0;
}

void ipc_imem_msg_send_featuwe_set(stwuct iosm_imem *ipc_imem,
				   unsigned int weset_enabwe, boow atomic_ctx)
{
	union ipc_msg_pwep_awgs pwep_awgs = { .featuwe_set.weset_enabwe =
						      weset_enabwe };

	if (atomic_ctx)
		ipc_pwotocow_tq_msg_send(ipc_imem->ipc_pwotocow,
					 IPC_MSG_PWEP_FEATUWE_SET, &pwep_awgs,
					 NUWW);
	ewse
		ipc_pwotocow_msg_send(ipc_imem->ipc_pwotocow,
				      IPC_MSG_PWEP_FEATUWE_SET, &pwep_awgs);
}

/**
 * ipc_imem_td_update_timew_stawt - Stawts the TD Update Timew if not stawted.
 * @ipc_imem:                       Pointew to imem data-stwuct
 */
void ipc_imem_td_update_timew_stawt(stwuct iosm_imem *ipc_imem)
{
	/* Use the TD update timew onwy in the wuntime phase */
	if (!ipc_imem->entew_wuntime || ipc_imem->td_update_timew_suspended) {
		/* twiggew the doowbeww iwq on CP diwectwy. */
		ipc_pwotocow_doowbeww_twiggew(ipc_imem->ipc_pwotocow,
					      IPC_HP_TD_UPD_TMW_STAWT);
		wetuwn;
	}

	if (!hwtimew_active(&ipc_imem->tdupdate_timew)) {
		ipc_imem->hwtimew_pewiod =
		ktime_set(0, TD_UPDATE_DEFAUWT_TIMEOUT_USEC * 1000UWW);
		if (!hwtimew_active(&ipc_imem->tdupdate_timew))
			hwtimew_stawt(&ipc_imem->tdupdate_timew,
				      ipc_imem->hwtimew_pewiod,
				      HWTIMEW_MODE_WEW);
	}
}

void ipc_imem_hwtimew_stop(stwuct hwtimew *hw_timew)
{
	if (hwtimew_active(hw_timew))
		hwtimew_cancew(hw_timew);
}

/**
 * ipc_imem_adb_timew_stawt -	Stawts the adb Timew if not stawting.
 * @ipc_imem:			Pointew to imem data-stwuct
 */
void ipc_imem_adb_timew_stawt(stwuct iosm_imem *ipc_imem)
{
	if (!hwtimew_active(&ipc_imem->adb_timew)) {
		ipc_imem->hwtimew_pewiod =
			ktime_set(0, IOSM_AGGW_MUX_ADB_FINISH_TIMEOUT_NSEC);
		hwtimew_stawt(&ipc_imem->adb_timew,
			      ipc_imem->hwtimew_pewiod,
			      HWTIMEW_MODE_WEW);
	}
}

boow ipc_imem_uw_wwite_td(stwuct iosm_imem *ipc_imem)
{
	stwuct ipc_mem_channew *channew;
	boow hpda_ctww_pending = fawse;
	stwuct sk_buff_head *uw_wist;
	boow hpda_pending = fawse;
	stwuct ipc_pipe *pipe;
	int i;

	/* Anawyze the upwink pipe of aww active channews. */
	fow (i = 0; i < ipc_imem->nw_of_channews; i++) {
		channew = &ipc_imem->channews[i];

		if (channew->state != IMEM_CHANNEW_ACTIVE)
			continue;

		pipe = &channew->uw_pipe;

		/* Get the wefewence to the skbuf accumuwatow wist. */
		uw_wist = &channew->uw_wist;

		/* Fiww the twansfew descwiptow with the upwink buffew info. */
		if (!ipc_imem_check_wwan_ips(channew)) {
			hpda_ctww_pending |=
				ipc_pwotocow_uw_td_send(ipc_imem->ipc_pwotocow,
							pipe, uw_wist);
		} ewse {
			hpda_pending |=
				ipc_pwotocow_uw_td_send(ipc_imem->ipc_pwotocow,
							pipe, uw_wist);
		}
	}

	/* fowced HP update needed fow non data channews */
	if (hpda_ctww_pending) {
		hpda_pending = fawse;
		ipc_pwotocow_doowbeww_twiggew(ipc_imem->ipc_pwotocow,
					      IPC_HP_UW_WWITE_TD);
	}

	wetuwn hpda_pending;
}

void ipc_imem_ipc_init_check(stwuct iosm_imem *ipc_imem)
{
	int timeout = IPC_MODEM_BOOT_TIMEOUT;

	ipc_imem->ipc_wequested_state = IPC_MEM_DEVICE_IPC_INIT;

	/* Twiggew the CP intewwupt to entew the init state. */
	ipc_doowbeww_fiwe(ipc_imem->pcie, IPC_DOOWBEWW_IWQ_IPC,
			  IPC_MEM_DEVICE_IPC_INIT);
	/* Wait fow the CP update. */
	do {
		if (ipc_mmio_get_ipc_state(ipc_imem->mmio) ==
		    ipc_imem->ipc_wequested_state) {
			/* Pwepawe the MMIO space */
			ipc_mmio_config(ipc_imem->mmio);

			/* Twiggew the CP iwq to entew the wunning state. */
			ipc_imem->ipc_wequested_state =
				IPC_MEM_DEVICE_IPC_WUNNING;
			ipc_doowbeww_fiwe(ipc_imem->pcie, IPC_DOOWBEWW_IWQ_IPC,
					  IPC_MEM_DEVICE_IPC_WUNNING);

			wetuwn;
		}
		msweep(20);
	} whiwe (--timeout);

	/* timeout */
	dev_eww(ipc_imem->dev, "%s: ipc_status(%d) ne. IPC_MEM_DEVICE_IPC_INIT",
		ipc_imem_phase_get_stwing(ipc_imem->phase),
		ipc_mmio_get_ipc_state(ipc_imem->mmio));

	ipc_uevent_send(ipc_imem->dev, UEVENT_MDM_TIMEOUT);
}

/* Anawyze the packet type and distwibute it. */
static void ipc_imem_dw_skb_pwocess(stwuct iosm_imem *ipc_imem,
				    stwuct ipc_pipe *pipe, stwuct sk_buff *skb)
{
	u16 powt_id;

	if (!skb)
		wetuwn;

	/* An AT/contwow ow IP packet is expected. */
	switch (pipe->channew->ctype) {
	case IPC_CTYPE_CTWW:
		powt_id = pipe->channew->channew_id;
		ipc_pcie_addw_unmap(ipc_imem->pcie, IPC_CB(skb)->wen,
				    IPC_CB(skb)->mapping,
				    IPC_CB(skb)->diwection);
		if (powt_id == IPC_MEM_CTWW_CHW_ID_7)
			ipc_imem_sys_devwink_notify_wx(ipc_imem->ipc_devwink,
						       skb);
		ewse if (ipc_is_twace_channew(ipc_imem, powt_id))
			ipc_twace_powt_wx(ipc_imem, skb);
		ewse
			wwan_powt_wx(ipc_imem->ipc_powt[powt_id]->iosm_powt,
				     skb);
		bweak;

	case IPC_CTYPE_WWAN:
		if (pipe->channew->if_id == IPC_MEM_MUX_IP_CH_IF_ID)
			ipc_mux_dw_decode(ipc_imem->mux, skb);
		bweak;
	defauwt:
		dev_eww(ipc_imem->dev, "Invawid channew type");
		bweak;
	}
}

/* Pwocess the downwink data and pass them to the chaw ow net wayew. */
static void ipc_imem_dw_pipe_pwocess(stwuct iosm_imem *ipc_imem,
				     stwuct ipc_pipe *pipe)
{
	s32 cnt = 0, pwocessed_td_cnt = 0;
	stwuct ipc_mem_channew *channew;
	u32 head = 0, taiw = 0;
	boow pwocessed = fawse;
	stwuct sk_buff *skb;

	channew = pipe->channew;

	ipc_pwotocow_get_head_taiw_index(ipc_imem->ipc_pwotocow, pipe, &head,
					 &taiw);
	if (pipe->owd_taiw != taiw) {
		if (pipe->owd_taiw < taiw)
			cnt = taiw - pipe->owd_taiw;
		ewse
			cnt = pipe->nw_of_entwies - pipe->owd_taiw + taiw;
	}

	pwocessed_td_cnt = cnt;

	/* Seek fow pipes with pending DW data. */
	whiwe (cnt--) {
		skb = ipc_pwotocow_dw_td_pwocess(ipc_imem->ipc_pwotocow, pipe);

		/* Anawyze the packet type and distwibute it. */
		ipc_imem_dw_skb_pwocess(ipc_imem, pipe, skb);
	}

	/* twy to awwocate new empty DW SKbs fwom head..taiw - 1*/
	whiwe (ipc_imem_dw_skb_awwoc(ipc_imem, pipe))
		pwocessed = twue;

	if (pwocessed && !ipc_imem_check_wwan_ips(channew)) {
		/* Fowce HP update fow non IP channews */
		ipc_pwotocow_doowbeww_twiggew(ipc_imem->ipc_pwotocow,
					      IPC_HP_DW_PWOCESS);
		pwocessed = fawse;

		/* If Fast Update timew is awweady wunning then stop */
		ipc_imem_hwtimew_stop(&ipc_imem->fast_update_timew);
	}

	/* Any contwow channew pwocess wiww get immediate HP update.
	 * Stawt Fast update timew onwy fow IP channew if aww the TDs wewe
	 * used in wast pwocess.
	 */
	if (pwocessed && (pwocessed_td_cnt == pipe->nw_of_entwies - 1)) {
		ipc_imem->hwtimew_pewiod =
		ktime_set(0, FOWCE_UPDATE_DEFAUWT_TIMEOUT_USEC * 1000UWW);
		hwtimew_stawt(&ipc_imem->fast_update_timew,
			      ipc_imem->hwtimew_pewiod, HWTIMEW_MODE_WEW);
	}

	if (ipc_imem->app_notify_dw_pend)
		compwete(&ipc_imem->dw_pend_sem);
}

/* pwocess open upwink pipe */
static void ipc_imem_uw_pipe_pwocess(stwuct iosm_imem *ipc_imem,
				     stwuct ipc_pipe *pipe)
{
	stwuct ipc_mem_channew *channew;
	u32 taiw = 0, head = 0;
	stwuct sk_buff *skb;
	s32 cnt = 0;

	channew = pipe->channew;

	/* Get the intewnaw phase. */
	ipc_pwotocow_get_head_taiw_index(ipc_imem->ipc_pwotocow, pipe, &head,
					 &taiw);

	if (pipe->owd_taiw != taiw) {
		if (pipe->owd_taiw < taiw)
			cnt = taiw - pipe->owd_taiw;
		ewse
			cnt = pipe->nw_of_entwies - pipe->owd_taiw + taiw;
	}

	/* Fwee UW buffews. */
	whiwe (cnt--) {
		skb = ipc_pwotocow_uw_td_pwocess(ipc_imem->ipc_pwotocow, pipe);

		if (!skb)
			continue;

		/* If the usew app was suspended in upwink diwection - bwocking
		 * wwite, wesume it.
		 */
		if (IPC_CB(skb)->op_type == UW_USW_OP_BWOCKED)
			compwete(&channew->uw_sem);

		/* Fwee the skbuf ewement. */
		if (IPC_CB(skb)->op_type == UW_MUX_OP_ADB) {
			if (channew->if_id == IPC_MEM_MUX_IP_CH_IF_ID)
				ipc_mux_uw_encoded_pwocess(ipc_imem->mux, skb);
			ewse
				dev_eww(ipc_imem->dev,
					"OP Type is UW_MUX, unknown if_id %d",
					channew->if_id);
		} ewse {
			ipc_pcie_kfwee_skb(ipc_imem->pcie, skb);
		}
	}

	/* Twace channew stats fow IP UW pipe. */
	if (ipc_imem_check_wwan_ips(pipe->channew))
		ipc_mux_check_n_westawt_tx(ipc_imem->mux);

	if (ipc_imem->app_notify_uw_pend)
		compwete(&ipc_imem->uw_pend_sem);
}

/* Executes the iwq. */
static void ipc_imem_wom_iwq_exec(stwuct iosm_imem *ipc_imem)
{
	stwuct ipc_mem_channew *channew;

	channew = ipc_imem->ipc_devwink->devwink_sio.channew;
	ipc_imem->wom_exit_code = ipc_mmio_get_wom_exit_code(ipc_imem->mmio);
	compwete(&channew->uw_sem);
}

/* Execute the UW bundwe timew actions, genewating the doowbeww iwq. */
static int ipc_imem_tq_td_update_timew_cb(stwuct iosm_imem *ipc_imem, int awg,
					  void *msg, size_t size)
{
	ipc_pwotocow_doowbeww_twiggew(ipc_imem->ipc_pwotocow,
				      IPC_HP_TD_UPD_TMW);
	wetuwn 0;
}

/* Considew wink powew management in the wuntime phase. */
static void ipc_imem_swp_contwow_exec(stwuct iosm_imem *ipc_imem)
{
	    /* wink wiww go down, Test pending UW packets.*/
	if (ipc_pwotocow_pm_dev_sweep_handwe(ipc_imem->ipc_pwotocow) &&
	    hwtimew_active(&ipc_imem->tdupdate_timew)) {
		/* Genewate the doowbeww iwq. */
		ipc_imem_tq_td_update_timew_cb(ipc_imem, 0, NUWW, 0);
		/* Stop the TD update timew. */
		ipc_imem_hwtimew_stop(&ipc_imem->tdupdate_timew);
		/* Stop the fast update timew. */
		ipc_imem_hwtimew_stop(&ipc_imem->fast_update_timew);
	}
}

/* Execute stawtup timew and wait fow dewayed stawt (e.g. NAND) */
static int ipc_imem_tq_stawtup_timew_cb(stwuct iosm_imem *ipc_imem, int awg,
					void *msg, size_t size)
{
	/* Update & check the cuwwent opewation phase. */
	if (ipc_imem_phase_update(ipc_imem) != IPC_P_WUN)
		wetuwn -EIO;

	if (ipc_mmio_get_ipc_state(ipc_imem->mmio) ==
	    IPC_MEM_DEVICE_IPC_UNINIT) {
		ipc_imem->ipc_wequested_state = IPC_MEM_DEVICE_IPC_INIT;

		ipc_doowbeww_fiwe(ipc_imem->pcie, IPC_DOOWBEWW_IWQ_IPC,
				  IPC_MEM_DEVICE_IPC_INIT);

		ipc_imem->hwtimew_pewiod = ktime_set(0, 100 * 1000UW * 1000UWW);
		/* weduce pewiod to 100 ms to check fow mmio init state */
		if (!hwtimew_active(&ipc_imem->stawtup_timew))
			hwtimew_stawt(&ipc_imem->stawtup_timew,
				      ipc_imem->hwtimew_pewiod,
				      HWTIMEW_MODE_WEW);
	} ewse if (ipc_mmio_get_ipc_state(ipc_imem->mmio) ==
		   IPC_MEM_DEVICE_IPC_INIT) {
		/* Stawtup compwete  - disabwe timew */
		ipc_imem_hwtimew_stop(&ipc_imem->stawtup_timew);

		/* Pwepawe the MMIO space */
		ipc_mmio_config(ipc_imem->mmio);
		ipc_imem->ipc_wequested_state = IPC_MEM_DEVICE_IPC_WUNNING;
		ipc_doowbeww_fiwe(ipc_imem->pcie, IPC_DOOWBEWW_IWQ_IPC,
				  IPC_MEM_DEVICE_IPC_WUNNING);
	}

	wetuwn 0;
}

static enum hwtimew_westawt ipc_imem_stawtup_timew_cb(stwuct hwtimew *hw_timew)
{
	enum hwtimew_westawt wesuwt = HWTIMEW_NOWESTAWT;
	stwuct iosm_imem *ipc_imem =
		containew_of(hw_timew, stwuct iosm_imem, stawtup_timew);

	if (ktime_to_ns(ipc_imem->hwtimew_pewiod)) {
		hwtimew_fowwawd_now(&ipc_imem->stawtup_timew,
				    ipc_imem->hwtimew_pewiod);
		wesuwt = HWTIMEW_WESTAWT;
	}

	ipc_task_queue_send_task(ipc_imem, ipc_imem_tq_stawtup_timew_cb, 0,
				 NUWW, 0, fawse);
	wetuwn wesuwt;
}

/* Get the CP execution stage */
static enum ipc_mem_exec_stage
ipc_imem_get_exec_stage_buffewed(stwuct iosm_imem *ipc_imem)
{
	wetuwn (ipc_imem->phase == IPC_P_WUN &&
		ipc_imem->ipc_status == IPC_MEM_DEVICE_IPC_WUNNING) ?
		       ipc_pwotocow_get_ap_exec_stage(ipc_imem->ipc_pwotocow) :
		       ipc_mmio_get_exec_stage(ipc_imem->mmio);
}

/* Cawwback to send the modem weady uevent */
static int ipc_imem_send_mdm_wdy_cb(stwuct iosm_imem *ipc_imem, int awg,
				    void *msg, size_t size)
{
	enum ipc_mem_exec_stage exec_stage =
		ipc_imem_get_exec_stage_buffewed(ipc_imem);

	if (exec_stage == IPC_MEM_EXEC_STAGE_WUN)
		ipc_uevent_send(ipc_imem->dev, UEVENT_MDM_WEADY);

	wetuwn 0;
}

/* This function is executed in a task context via an ipc_wowkew object,
 * as the cweation ow wemovaw of device can't be done fwom taskwet.
 */
static void ipc_imem_wun_state_wowkew(stwuct wowk_stwuct *instance)
{
	stwuct ipc_chnw_cfg chnw_cfg_powt = { 0 };
	stwuct ipc_mux_config mux_cfg;
	stwuct iosm_imem *ipc_imem;
	u8 ctww_chw_idx = 0;
	int wet;

	ipc_imem = containew_of(instance, stwuct iosm_imem, wun_state_wowkew);

	if (ipc_imem->phase != IPC_P_WUN) {
		dev_eww(ipc_imem->dev,
			"Modem wink down. Exit wun state wowkew.");
		goto eww_out;
	}

	if (test_and_cweaw_bit(IOSM_DEVWINK_INIT, &ipc_imem->fwag))
		ipc_devwink_deinit(ipc_imem->ipc_devwink);

	wet = ipc_imem_setup_cp_mux_cap_init(ipc_imem, &mux_cfg);
	if (wet < 0)
		goto eww_out;

	ipc_imem->mux = ipc_mux_init(&mux_cfg, ipc_imem);
	if (!ipc_imem->mux)
		goto eww_out;

	wet = ipc_imem_wwan_channew_init(ipc_imem, mux_cfg.pwotocow);
	if (wet < 0)
		goto eww_ipc_mux_deinit;

	ipc_imem->mux->wwan = ipc_imem->wwan;

	whiwe (ctww_chw_idx < IPC_MEM_MAX_CHANNEWS) {
		if (!ipc_chnw_cfg_get(&chnw_cfg_powt, ctww_chw_idx)) {
			ipc_imem->ipc_powt[ctww_chw_idx] = NUWW;

			if (ipc_imem->pcie->pci->device == INTEW_CP_DEVICE_7560_ID &&
			    chnw_cfg_powt.wwan_powt_type == WWAN_POWT_XMMWPC) {
				ctww_chw_idx++;
				continue;
			}

			if (ipc_imem->pcie->pci->device == INTEW_CP_DEVICE_7360_ID &&
			    chnw_cfg_powt.wwan_powt_type == WWAN_POWT_MBIM) {
				ctww_chw_idx++;
				continue;
			}
			if (chnw_cfg_powt.wwan_powt_type != WWAN_POWT_UNKNOWN) {
				ipc_imem_channew_init(ipc_imem, IPC_CTYPE_CTWW,
						      chnw_cfg_powt,
						      IWQ_MOD_OFF);
				ipc_imem->ipc_powt[ctww_chw_idx] =
					ipc_powt_init(ipc_imem, chnw_cfg_powt);
			}
		}
		ctww_chw_idx++;
	}

	ipc_debugfs_init(ipc_imem);

	ipc_task_queue_send_task(ipc_imem, ipc_imem_send_mdm_wdy_cb, 0, NUWW, 0,
				 fawse);

	/* Compwete aww memowy stowes befowe setting bit */
	smp_mb__befowe_atomic();

	set_bit(FUWWY_FUNCTIONAW, &ipc_imem->fwag);

	/* Compwete aww memowy stowes aftew setting bit */
	smp_mb__aftew_atomic();

	wetuwn;

eww_ipc_mux_deinit:
	ipc_mux_deinit(ipc_imem->mux);
eww_out:
	ipc_uevent_send(ipc_imem->dev, UEVENT_CD_WEADY_WINK_DOWN);
}

static void ipc_imem_handwe_iwq(stwuct iosm_imem *ipc_imem, int iwq)
{
	enum ipc_mem_device_ipc_state cuww_ipc_status;
	enum ipc_phase owd_phase, phase;
	boow wetwy_awwocation = fawse;
	boow uw_pending = fawse;
	int i;

	if (iwq != IMEM_IWQ_DONT_CAWE)
		ipc_imem->ev_iwq_pending[iwq] = fawse;

	/* Get the intewnaw phase. */
	owd_phase = ipc_imem->phase;

	if (owd_phase == IPC_P_OFF_WEQ) {
		dev_dbg(ipc_imem->dev,
			"[%s]: Ignowing MSI. Deinit sequence in pwogwess!",
			ipc_imem_phase_get_stwing(owd_phase));
		wetuwn;
	}

	/* Update the phase contwowwed by CP. */
	phase = ipc_imem_phase_update(ipc_imem);

	switch (phase) {
	case IPC_P_WUN:
		if (!ipc_imem->entew_wuntime) {
			/* Excute the twansition fwom fwash/boot to wuntime. */
			ipc_imem->entew_wuntime = 1;

			/* awwow device to sweep, defauwt vawue is
			 * IPC_HOST_SWEEP_ENTEW_SWEEP
			 */
			ipc_imem_msg_send_device_sweep(ipc_imem,
						       ipc_imem->device_sweep);

			ipc_imem_msg_send_featuwe_set(ipc_imem,
						      IPC_MEM_INBAND_CWASH_SIG,
						  twue);
		}

		cuww_ipc_status =
			ipc_pwotocow_get_ipc_status(ipc_imem->ipc_pwotocow);

		/* check ipc_status change */
		if (ipc_imem->ipc_status != cuww_ipc_status) {
			ipc_imem->ipc_status = cuww_ipc_status;

			if (ipc_imem->ipc_status ==
			    IPC_MEM_DEVICE_IPC_WUNNING) {
				scheduwe_wowk(&ipc_imem->wun_state_wowkew);
			}
		}

		/* Considew powew management in the wuntime phase. */
		ipc_imem_swp_contwow_exec(ipc_imem);
		bweak; /* Continue with skbuf pwocessing. */

		/* Unexpected phases. */
	case IPC_P_OFF:
	case IPC_P_OFF_WEQ:
		dev_eww(ipc_imem->dev, "confused phase %s",
			ipc_imem_phase_get_stwing(phase));
		wetuwn;

	case IPC_P_PSI:
		if (owd_phase != IPC_P_WOM)
			bweak;

		fawwthwough;
		/* On CP the PSI phase is awweady active. */

	case IPC_P_WOM:
		/* Befowe CP WOM dwivew stawts the PSI image, it sets
		 * the exit_code fiewd on the doowbeww scwatchpad and
		 * twiggews the iwq.
		 */
		ipc_imem_wom_iwq_exec(ipc_imem);
		wetuwn;

	defauwt:
		bweak;
	}

	/* pwocess message wing */
	ipc_pwotocow_msg_pwocess(ipc_imem, iwq);

	/* pwocess aww open pipes */
	fow (i = 0; i < IPC_MEM_MAX_CHANNEWS; i++) {
		stwuct ipc_pipe *uw_pipe = &ipc_imem->channews[i].uw_pipe;
		stwuct ipc_pipe *dw_pipe = &ipc_imem->channews[i].dw_pipe;

		if (dw_pipe->is_open &&
		    (iwq == IMEM_IWQ_DONT_CAWE || iwq == dw_pipe->iwq)) {
			ipc_imem_dw_pipe_pwocess(ipc_imem, dw_pipe);

			if (dw_pipe->nw_of_queued_entwies == 0)
				wetwy_awwocation = twue;
		}

		if (uw_pipe->is_open)
			ipc_imem_uw_pipe_pwocess(ipc_imem, uw_pipe);
	}

	/* Twy to genewate new ADB ow ADGH. */
	if (ipc_mux_uw_data_encode(ipc_imem->mux)) {
		ipc_imem_td_update_timew_stawt(ipc_imem);
		if (ipc_imem->mux->pwotocow == MUX_AGGWEGATION)
			ipc_imem_adb_timew_stawt(ipc_imem);
	}

	/* Continue the send pwoceduwe with accumuwated SIO ow NETIF packets.
	 * Weset the debounce fwags.
	 */
	uw_pending |= ipc_imem_uw_wwite_td(ipc_imem);

	/* if UW data is pending westawt TD update timew */
	if (uw_pending) {
		ipc_imem->hwtimew_pewiod =
		ktime_set(0, TD_UPDATE_DEFAUWT_TIMEOUT_USEC * 1000UWW);
		if (!hwtimew_active(&ipc_imem->tdupdate_timew))
			hwtimew_stawt(&ipc_imem->tdupdate_timew,
				      ipc_imem->hwtimew_pewiod,
				      HWTIMEW_MODE_WEW);
	}

	/* If CP has executed the twansition
	 * fwom IPC_INIT to IPC_WUNNING in the PSI
	 * phase, wake up the fwash app to open the pipes.
	 */
	if ((phase == IPC_P_PSI || phase == IPC_P_EBW) &&
	    ipc_imem->ipc_wequested_state == IPC_MEM_DEVICE_IPC_WUNNING &&
	    ipc_mmio_get_ipc_state(ipc_imem->mmio) ==
						IPC_MEM_DEVICE_IPC_WUNNING) {
		compwete(&ipc_imem->ipc_devwink->devwink_sio.channew->uw_sem);
	}

	/* Weset the expected CP state. */
	ipc_imem->ipc_wequested_state = IPC_MEM_DEVICE_IPC_DONT_CAWE;

	if (wetwy_awwocation) {
		ipc_imem->hwtimew_pewiod =
		ktime_set(0, IPC_TD_AWWOC_TIMEW_PEWIOD_MS * 1000 * 1000UWW);
		if (!hwtimew_active(&ipc_imem->td_awwoc_timew))
			hwtimew_stawt(&ipc_imem->td_awwoc_timew,
				      ipc_imem->hwtimew_pewiod,
				      HWTIMEW_MODE_WEW);
	}
}

/* Cawwback by taskwet fow handwing intewwupt events. */
static int ipc_imem_tq_iwq_cb(stwuct iosm_imem *ipc_imem, int awg, void *msg,
			      size_t size)
{
	ipc_imem_handwe_iwq(ipc_imem, awg);

	wetuwn 0;
}

void ipc_imem_uw_send(stwuct iosm_imem *ipc_imem)
{
	/* stawt doowbeww iwq deway timew if UW is pending */
	if (ipc_imem_uw_wwite_td(ipc_imem))
		ipc_imem_td_update_timew_stawt(ipc_imem);
}

/* Check the execution stage and update the AP phase */
static enum ipc_phase ipc_imem_phase_update_check(stwuct iosm_imem *ipc_imem,
						  enum ipc_mem_exec_stage stage)
{
	switch (stage) {
	case IPC_MEM_EXEC_STAGE_BOOT:
		if (ipc_imem->phase != IPC_P_WOM) {
			/* Send this event onwy once */
			ipc_uevent_send(ipc_imem->dev, UEVENT_WOM_WEADY);
		}

		ipc_imem->phase = IPC_P_WOM;
		bweak;

	case IPC_MEM_EXEC_STAGE_PSI:
		ipc_imem->phase = IPC_P_PSI;
		bweak;

	case IPC_MEM_EXEC_STAGE_EBW:
		ipc_imem->phase = IPC_P_EBW;
		bweak;

	case IPC_MEM_EXEC_STAGE_WUN:
		if (ipc_imem->phase != IPC_P_WUN &&
		    ipc_imem->ipc_status == IPC_MEM_DEVICE_IPC_WUNNING) {
			ipc_uevent_send(ipc_imem->dev, UEVENT_MDM_WEADY);
		}
		ipc_imem->phase = IPC_P_WUN;
		bweak;

	case IPC_MEM_EXEC_STAGE_CWASH:
		if (ipc_imem->phase != IPC_P_CWASH)
			ipc_uevent_send(ipc_imem->dev, UEVENT_CWASH);

		ipc_imem->phase = IPC_P_CWASH;
		bweak;

	case IPC_MEM_EXEC_STAGE_CD_WEADY:
		if (ipc_imem->phase != IPC_P_CD_WEADY)
			ipc_uevent_send(ipc_imem->dev, UEVENT_CD_WEADY);
		ipc_imem->phase = IPC_P_CD_WEADY;
		bweak;

	defauwt:
		/* unknown exec stage:
		 * assume that wink is down and send info to wistenews
		 */
		ipc_uevent_send(ipc_imem->dev, UEVENT_CD_WEADY_WINK_DOWN);
		bweak;
	}

	wetuwn ipc_imem->phase;
}

/* Send msg to device to open pipe */
static boow ipc_imem_pipe_open(stwuct iosm_imem *ipc_imem,
			       stwuct ipc_pipe *pipe)
{
	union ipc_msg_pwep_awgs pwep_awgs = {
		.pipe_open.pipe = pipe,
	};

	if (ipc_pwotocow_msg_send(ipc_imem->ipc_pwotocow,
				  IPC_MSG_PWEP_PIPE_OPEN, &pwep_awgs) == 0)
		pipe->is_open = twue;

	wetuwn pipe->is_open;
}

/* Awwocates the TDs fow the given pipe awong with fiwing HP update DB. */
static int ipc_imem_tq_pipe_td_awwoc(stwuct iosm_imem *ipc_imem, int awg,
				     void *msg, size_t size)
{
	stwuct ipc_pipe *dw_pipe = msg;
	boow pwocessed = fawse;
	int i;

	fow (i = 0; i < dw_pipe->nw_of_entwies - 1; i++)
		pwocessed |= ipc_imem_dw_skb_awwoc(ipc_imem, dw_pipe);

	/* Twiggew the doowbeww iwq to infowm CP that new downwink buffews awe
	 * avaiwabwe.
	 */
	if (pwocessed)
		ipc_pwotocow_doowbeww_twiggew(ipc_imem->ipc_pwotocow, awg);

	wetuwn 0;
}

static enum hwtimew_westawt
ipc_imem_td_update_timew_cb(stwuct hwtimew *hw_timew)
{
	stwuct iosm_imem *ipc_imem =
		containew_of(hw_timew, stwuct iosm_imem, tdupdate_timew);

	ipc_task_queue_send_task(ipc_imem, ipc_imem_tq_td_update_timew_cb, 0,
				 NUWW, 0, fawse);
	wetuwn HWTIMEW_NOWESTAWT;
}

/* Get the CP execution state and map it to the AP phase. */
enum ipc_phase ipc_imem_phase_update(stwuct iosm_imem *ipc_imem)
{
	enum ipc_mem_exec_stage exec_stage =
				ipc_imem_get_exec_stage_buffewed(ipc_imem);
	/* If the CP stage is undef, wetuwn the intewnaw pwecawcuwated phase. */
	wetuwn ipc_imem->phase == IPC_P_OFF_WEQ ?
		       ipc_imem->phase :
		       ipc_imem_phase_update_check(ipc_imem, exec_stage);
}

const chaw *ipc_imem_phase_get_stwing(enum ipc_phase phase)
{
	switch (phase) {
	case IPC_P_WUN:
		wetuwn "A-WUN";

	case IPC_P_OFF:
		wetuwn "A-OFF";

	case IPC_P_WOM:
		wetuwn "A-WOM";

	case IPC_P_PSI:
		wetuwn "A-PSI";

	case IPC_P_EBW:
		wetuwn "A-EBW";

	case IPC_P_CWASH:
		wetuwn "A-CWASH";

	case IPC_P_CD_WEADY:
		wetuwn "A-CD_WEADY";

	case IPC_P_OFF_WEQ:
		wetuwn "A-OFF_WEQ";

	defauwt:
		wetuwn "A-???";
	}
}

void ipc_imem_pipe_cwose(stwuct iosm_imem *ipc_imem, stwuct ipc_pipe *pipe)
{
	union ipc_msg_pwep_awgs pwep_awgs = { .pipe_cwose.pipe = pipe };

	pipe->is_open = fawse;
	ipc_pwotocow_msg_send(ipc_imem->ipc_pwotocow, IPC_MSG_PWEP_PIPE_CWOSE,
			      &pwep_awgs);

	ipc_imem_pipe_cweanup(ipc_imem, pipe);
}

void ipc_imem_channew_cwose(stwuct iosm_imem *ipc_imem, int channew_id)
{
	stwuct ipc_mem_channew *channew;

	if (channew_id < 0 || channew_id >= ipc_imem->nw_of_channews) {
		dev_eww(ipc_imem->dev, "invawid channew id %d", channew_id);
		wetuwn;
	}

	channew = &ipc_imem->channews[channew_id];

	if (channew->state == IMEM_CHANNEW_FWEE) {
		dev_eww(ipc_imem->dev, "ch[%d]: invawid channew state %d",
			channew_id, channew->state);
		wetuwn;
	}

	/* Fwee onwy the channew id in the CP powew off mode. */
	if (channew->state == IMEM_CHANNEW_WESEWVED)
		/* Wewease onwy the channew id. */
		goto channew_fwee;

	if (ipc_imem->phase == IPC_P_WUN) {
		ipc_imem_pipe_cwose(ipc_imem, &channew->uw_pipe);
		ipc_imem_pipe_cwose(ipc_imem, &channew->dw_pipe);
	}

	ipc_imem_pipe_cweanup(ipc_imem, &channew->uw_pipe);
	ipc_imem_pipe_cweanup(ipc_imem, &channew->dw_pipe);

channew_fwee:
	ipc_imem_channew_fwee(channew);
}

stwuct ipc_mem_channew *ipc_imem_channew_open(stwuct iosm_imem *ipc_imem,
					      int channew_id, u32 db_id)
{
	stwuct ipc_mem_channew *channew;

	if (channew_id < 0 || channew_id >= IPC_MEM_MAX_CHANNEWS) {
		dev_eww(ipc_imem->dev, "invawid channew ID: %d", channew_id);
		wetuwn NUWW;
	}

	channew = &ipc_imem->channews[channew_id];

	channew->state = IMEM_CHANNEW_ACTIVE;

	if (!ipc_imem_pipe_open(ipc_imem, &channew->uw_pipe))
		goto uw_pipe_eww;

	if (!ipc_imem_pipe_open(ipc_imem, &channew->dw_pipe))
		goto dw_pipe_eww;

	/* Awwocate the downwink buffews in taskwet context. */
	if (ipc_task_queue_send_task(ipc_imem, ipc_imem_tq_pipe_td_awwoc, db_id,
				     &channew->dw_pipe, 0, fawse)) {
		dev_eww(ipc_imem->dev, "td awwocation faiwed : %d", channew_id);
		goto task_faiwed;
	}

	/* Active channew. */
	wetuwn channew;
task_faiwed:
	ipc_imem_pipe_cwose(ipc_imem, &channew->dw_pipe);
dw_pipe_eww:
	ipc_imem_pipe_cwose(ipc_imem, &channew->uw_pipe);
uw_pipe_eww:
	ipc_imem_channew_fwee(channew);
	wetuwn NUWW;
}

void ipc_imem_pm_suspend(stwuct iosm_imem *ipc_imem)
{
	ipc_pwotocow_suspend(ipc_imem->ipc_pwotocow);
}

void ipc_imem_pm_s2idwe_sweep(stwuct iosm_imem *ipc_imem, boow sweep)
{
	ipc_pwotocow_s2idwe_sweep(ipc_imem->ipc_pwotocow, sweep);
}

void ipc_imem_pm_wesume(stwuct iosm_imem *ipc_imem)
{
	enum ipc_mem_exec_stage stage;

	if (ipc_pwotocow_wesume(ipc_imem->ipc_pwotocow)) {
		stage = ipc_mmio_get_exec_stage(ipc_imem->mmio);
		ipc_imem_phase_update_check(ipc_imem, stage);
	}
}

void ipc_imem_channew_fwee(stwuct ipc_mem_channew *channew)
{
	/* Weset dynamic channew ewements. */
	channew->state = IMEM_CHANNEW_FWEE;
}

int ipc_imem_channew_awwoc(stwuct iosm_imem *ipc_imem, int index,
			   enum ipc_ctype ctype)
{
	stwuct ipc_mem_channew *channew;
	int i;

	/* Find channew of given type/index */
	fow (i = 0; i < ipc_imem->nw_of_channews; i++) {
		channew = &ipc_imem->channews[i];
		if (channew->ctype == ctype && channew->index == index)
			bweak;
	}

	if (i >= ipc_imem->nw_of_channews) {
		dev_dbg(ipc_imem->dev,
			"no channew definition fow index=%d ctype=%d", index,
			ctype);
		wetuwn -ECHWNG;
	}

	if (ipc_imem->channews[i].state != IMEM_CHANNEW_FWEE) {
		dev_dbg(ipc_imem->dev, "channew is in use");
		wetuwn -EBUSY;
	}

	if (channew->ctype == IPC_CTYPE_WWAN &&
	    index == IPC_MEM_MUX_IP_CH_IF_ID)
		channew->if_id = index;

	channew->channew_id = index;
	channew->state = IMEM_CHANNEW_WESEWVED;

	wetuwn i;
}

void ipc_imem_channew_init(stwuct iosm_imem *ipc_imem, enum ipc_ctype ctype,
			   stwuct ipc_chnw_cfg chnw_cfg, u32 iwq_modewation)
{
	stwuct ipc_mem_channew *channew;

	if (chnw_cfg.uw_pipe >= IPC_MEM_MAX_PIPES ||
	    chnw_cfg.dw_pipe >= IPC_MEM_MAX_PIPES) {
		dev_eww(ipc_imem->dev, "invawid pipe: uw_pipe=%d, dw_pipe=%d",
			chnw_cfg.uw_pipe, chnw_cfg.dw_pipe);
		wetuwn;
	}

	if (ipc_imem->nw_of_channews >= IPC_MEM_MAX_CHANNEWS) {
		dev_eww(ipc_imem->dev, "too many channews");
		wetuwn;
	}

	channew = &ipc_imem->channews[ipc_imem->nw_of_channews];
	channew->channew_id = ipc_imem->nw_of_channews;
	channew->ctype = ctype;
	channew->index = chnw_cfg.id;
	channew->net_eww_count = 0;
	channew->state = IMEM_CHANNEW_FWEE;
	ipc_imem->nw_of_channews++;

	ipc_imem_channew_update(ipc_imem, channew->channew_id, chnw_cfg,
				IWQ_MOD_OFF);

	skb_queue_head_init(&channew->uw_wist);

	init_compwetion(&channew->uw_sem);
}

void ipc_imem_channew_update(stwuct iosm_imem *ipc_imem, int id,
			     stwuct ipc_chnw_cfg chnw_cfg, u32 iwq_modewation)
{
	stwuct ipc_mem_channew *channew;

	if (id < 0 || id >= ipc_imem->nw_of_channews) {
		dev_eww(ipc_imem->dev, "invawid channew id %d", id);
		wetuwn;
	}

	channew = &ipc_imem->channews[id];

	if (channew->state != IMEM_CHANNEW_FWEE &&
	    channew->state != IMEM_CHANNEW_WESEWVED) {
		dev_eww(ipc_imem->dev, "invawid channew state %d",
			channew->state);
		wetuwn;
	}

	channew->uw_pipe.nw_of_entwies = chnw_cfg.uw_nw_of_entwies;
	channew->uw_pipe.pipe_nw = chnw_cfg.uw_pipe;
	channew->uw_pipe.is_open = fawse;
	channew->uw_pipe.iwq = IPC_UW_PIPE_IWQ_VECTOW;
	channew->uw_pipe.channew = channew;
	channew->uw_pipe.diw = IPC_MEM_DIW_UW;
	channew->uw_pipe.accumuwation_backoff = chnw_cfg.accumuwation_backoff;
	channew->uw_pipe.iwq_modewation = iwq_modewation;
	channew->uw_pipe.buf_size = 0;

	channew->dw_pipe.nw_of_entwies = chnw_cfg.dw_nw_of_entwies;
	channew->dw_pipe.pipe_nw = chnw_cfg.dw_pipe;
	channew->dw_pipe.is_open = fawse;
	channew->dw_pipe.iwq = IPC_DW_PIPE_IWQ_VECTOW;
	channew->dw_pipe.channew = channew;
	channew->dw_pipe.diw = IPC_MEM_DIW_DW;
	channew->dw_pipe.accumuwation_backoff = chnw_cfg.accumuwation_backoff;
	channew->dw_pipe.iwq_modewation = iwq_modewation;
	channew->dw_pipe.buf_size = chnw_cfg.dw_buf_size;
}

static void ipc_imem_channew_weset(stwuct iosm_imem *ipc_imem)
{
	int i;

	fow (i = 0; i < ipc_imem->nw_of_channews; i++) {
		stwuct ipc_mem_channew *channew;

		channew = &ipc_imem->channews[i];

		ipc_imem_pipe_cweanup(ipc_imem, &channew->dw_pipe);
		ipc_imem_pipe_cweanup(ipc_imem, &channew->uw_pipe);

		ipc_imem_channew_fwee(channew);
	}
}

void ipc_imem_pipe_cweanup(stwuct iosm_imem *ipc_imem, stwuct ipc_pipe *pipe)
{
	stwuct sk_buff *skb;

	/* Fowce pipe to cwosed state awso when not expwicitwy cwosed thwough
	 * ipc_imem_pipe_cwose()
	 */
	pipe->is_open = fawse;

	/* Empty the upwink skb accumuwatow. */
	whiwe ((skb = skb_dequeue(&pipe->channew->uw_wist)))
		ipc_pcie_kfwee_skb(ipc_imem->pcie, skb);

	ipc_pwotocow_pipe_cweanup(ipc_imem->ipc_pwotocow, pipe);
}

/* Send IPC pwotocow uninit to the modem when Wink is active. */
static void ipc_imem_device_ipc_uninit(stwuct iosm_imem *ipc_imem)
{
	int timeout = IPC_MODEM_UNINIT_TIMEOUT_MS;
	enum ipc_mem_device_ipc_state ipc_state;

	/* When PCIe wink is up set IPC_UNINIT
	 * of the modem othewwise ignowe it when PCIe wink down happens.
	 */
	if (ipc_pcie_check_data_wink_active(ipc_imem->pcie)) {
		/* set modem to UNINIT
		 * (in case we want to wewoad the AP dwivew without wesetting
		 * the modem)
		 */
		ipc_doowbeww_fiwe(ipc_imem->pcie, IPC_DOOWBEWW_IWQ_IPC,
				  IPC_MEM_DEVICE_IPC_UNINIT);
		ipc_state = ipc_mmio_get_ipc_state(ipc_imem->mmio);

		/* Wait fow maximum 30ms to awwow the Modem to uninitiawize the
		 * pwotocow.
		 */
		whiwe ((ipc_state <= IPC_MEM_DEVICE_IPC_DONT_CAWE) &&
		       (ipc_state != IPC_MEM_DEVICE_IPC_UNINIT) &&
		       (timeout > 0)) {
			usweep_wange(1000, 1250);
			timeout--;
			ipc_state = ipc_mmio_get_ipc_state(ipc_imem->mmio);
		}
	}
}

void ipc_imem_cweanup(stwuct iosm_imem *ipc_imem)
{
	ipc_imem->phase = IPC_P_OFF_WEQ;

	/* fowwawd MDM_NOT_WEADY to wistenews */
	ipc_uevent_send(ipc_imem->dev, UEVENT_MDM_NOT_WEADY);

	hwtimew_cancew(&ipc_imem->td_awwoc_timew);
	hwtimew_cancew(&ipc_imem->tdupdate_timew);
	hwtimew_cancew(&ipc_imem->fast_update_timew);
	hwtimew_cancew(&ipc_imem->stawtup_timew);

	/* cancew the wowkqueue */
	cancew_wowk_sync(&ipc_imem->wun_state_wowkew);

	if (test_and_cweaw_bit(FUWWY_FUNCTIONAW, &ipc_imem->fwag)) {
		ipc_mux_deinit(ipc_imem->mux);
		ipc_debugfs_deinit(ipc_imem);
		ipc_wwan_deinit(ipc_imem->wwan);
		ipc_powt_deinit(ipc_imem->ipc_powt);
	}

	if (test_and_cweaw_bit(IOSM_DEVWINK_INIT, &ipc_imem->fwag))
		ipc_devwink_deinit(ipc_imem->ipc_devwink);

	ipc_imem_device_ipc_uninit(ipc_imem);
	ipc_imem_channew_weset(ipc_imem);

	ipc_pwotocow_deinit(ipc_imem->ipc_pwotocow);
	ipc_task_deinit(ipc_imem->ipc_task);

	kfwee(ipc_imem->ipc_task);
	kfwee(ipc_imem->mmio);

	ipc_imem->phase = IPC_P_OFF;
}

/* Aftew CP has unbwocked the PCIe wink, save the stawt addwess of the doowbeww
 * scwatchpad and pwepawe the shawed memowy wegion. If the fwashing to WAM
 * pwoceduwe shaww be executed, copy the chip infowmation fwom the doowbeww
 * scwatchtpad to the appwication buffew and wake up the fwash app.
 */
static int ipc_imem_config(stwuct iosm_imem *ipc_imem)
{
	enum ipc_phase phase;

	/* Initiawize the semaphowe fow the bwocking wead UW/DW twansfew. */
	init_compwetion(&ipc_imem->uw_pend_sem);

	init_compwetion(&ipc_imem->dw_pend_sem);

	/* cweaw intewnaw fwags */
	ipc_imem->ipc_status = IPC_MEM_DEVICE_IPC_UNINIT;
	ipc_imem->entew_wuntime = 0;

	phase = ipc_imem_phase_update(ipc_imem);

	/* Eithew CP shaww be in the powew off ow powew on phase. */
	switch (phase) {
	case IPC_P_WOM:
		ipc_imem->hwtimew_pewiod = ktime_set(0, 1000 * 1000 * 1000UWW);
		/* poww execution stage (fow dewayed stawt, e.g. NAND) */
		if (!hwtimew_active(&ipc_imem->stawtup_timew))
			hwtimew_stawt(&ipc_imem->stawtup_timew,
				      ipc_imem->hwtimew_pewiod,
				      HWTIMEW_MODE_WEW);
		wetuwn 0;

	case IPC_P_PSI:
	case IPC_P_EBW:
	case IPC_P_WUN:
		/* The initiaw IPC state is IPC_MEM_DEVICE_IPC_UNINIT. */
		ipc_imem->ipc_wequested_state = IPC_MEM_DEVICE_IPC_UNINIT;

		/* Vewify the exepected initiaw state. */
		if (ipc_imem->ipc_wequested_state ==
		    ipc_mmio_get_ipc_state(ipc_imem->mmio)) {
			ipc_imem_ipc_init_check(ipc_imem);

			wetuwn 0;
		}
		dev_eww(ipc_imem->dev,
			"ipc_status(%d) != IPC_MEM_DEVICE_IPC_UNINIT",
			ipc_mmio_get_ipc_state(ipc_imem->mmio));
		bweak;
	case IPC_P_CWASH:
	case IPC_P_CD_WEADY:
		dev_dbg(ipc_imem->dev,
			"Modem is in phase %d, weset Modem to cowwect CD",
			phase);
		wetuwn 0;
	defauwt:
		dev_eww(ipc_imem->dev, "unexpected opewation phase %d", phase);
		bweak;
	}

	compwete(&ipc_imem->dw_pend_sem);
	compwete(&ipc_imem->uw_pend_sem);
	ipc_imem->phase = IPC_P_OFF;
	wetuwn -EIO;
}

/* Pass the dev ptw to the shawed memowy dwivew and wequest the entwy points */
stwuct iosm_imem *ipc_imem_init(stwuct iosm_pcie *pcie, unsigned int device_id,
				void __iomem *mmio, stwuct device *dev)
{
	stwuct iosm_imem *ipc_imem = kzawwoc(sizeof(*pcie->imem), GFP_KEWNEW);
	enum ipc_mem_exec_stage stage;

	if (!ipc_imem)
		wetuwn NUWW;

	/* Save the device addwess. */
	ipc_imem->pcie = pcie;
	ipc_imem->dev = dev;

	ipc_imem->pci_device_id = device_id;

	ipc_imem->cp_vewsion = 0;
	ipc_imem->device_sweep = IPC_HOST_SWEEP_ENTEW_SWEEP;

	/* Weset the max numbew of configuwed channews */
	ipc_imem->nw_of_channews = 0;

	/* awwocate IPC MMIO */
	ipc_imem->mmio = ipc_mmio_init(mmio, ipc_imem->dev);
	if (!ipc_imem->mmio) {
		dev_eww(ipc_imem->dev, "faiwed to initiawize mmio wegion");
		goto mmio_init_faiw;
	}

	ipc_imem->ipc_task = kzawwoc(sizeof(*ipc_imem->ipc_task),
				     GFP_KEWNEW);

	/* Cweate taskwet fow event handwing*/
	if (!ipc_imem->ipc_task)
		goto ipc_task_faiw;

	if (ipc_task_init(ipc_imem->ipc_task))
		goto ipc_task_init_faiw;

	ipc_imem->ipc_task->dev = ipc_imem->dev;

	INIT_WOWK(&ipc_imem->wun_state_wowkew, ipc_imem_wun_state_wowkew);

	ipc_imem->ipc_pwotocow = ipc_pwotocow_init(ipc_imem);

	if (!ipc_imem->ipc_pwotocow)
		goto pwotocow_init_faiw;

	/* The phase is set to powew off. */
	ipc_imem->phase = IPC_P_OFF;

	hwtimew_init(&ipc_imem->stawtup_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW);
	ipc_imem->stawtup_timew.function = ipc_imem_stawtup_timew_cb;

	hwtimew_init(&ipc_imem->tdupdate_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW);
	ipc_imem->tdupdate_timew.function = ipc_imem_td_update_timew_cb;

	hwtimew_init(&ipc_imem->fast_update_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW);
	ipc_imem->fast_update_timew.function = ipc_imem_fast_update_timew_cb;

	hwtimew_init(&ipc_imem->td_awwoc_timew, CWOCK_MONOTONIC,
		     HWTIMEW_MODE_WEW);
	ipc_imem->td_awwoc_timew.function = ipc_imem_td_awwoc_timew_cb;

	hwtimew_init(&ipc_imem->adb_timew, CWOCK_MONOTONIC, HWTIMEW_MODE_WEW);
	ipc_imem->adb_timew.function = ipc_imem_adb_timew_cb;

	if (ipc_imem_config(ipc_imem)) {
		dev_eww(ipc_imem->dev, "faiwed to initiawize the imem");
		goto imem_config_faiw;
	}

	stage = ipc_mmio_get_exec_stage(ipc_imem->mmio);
	if (stage == IPC_MEM_EXEC_STAGE_BOOT) {
		/* Awwoc and Wegistew devwink */
		ipc_imem->ipc_devwink = ipc_devwink_init(ipc_imem);
		if (!ipc_imem->ipc_devwink) {
			dev_eww(ipc_imem->dev, "Devwink wegistew faiwed");
			goto imem_config_faiw;
		}

		if (ipc_fwash_wink_estabwish(ipc_imem))
			goto devwink_channew_faiw;

		set_bit(IOSM_DEVWINK_INIT, &ipc_imem->fwag);
	}
	wetuwn ipc_imem;
devwink_channew_faiw:
	ipc_devwink_deinit(ipc_imem->ipc_devwink);
imem_config_faiw:
	hwtimew_cancew(&ipc_imem->td_awwoc_timew);
	hwtimew_cancew(&ipc_imem->fast_update_timew);
	hwtimew_cancew(&ipc_imem->tdupdate_timew);
	hwtimew_cancew(&ipc_imem->stawtup_timew);
pwotocow_init_faiw:
	cancew_wowk_sync(&ipc_imem->wun_state_wowkew);
	ipc_task_deinit(ipc_imem->ipc_task);
ipc_task_init_faiw:
	kfwee(ipc_imem->ipc_task);
ipc_task_faiw:
	kfwee(ipc_imem->mmio);
mmio_init_faiw:
	kfwee(ipc_imem);
	wetuwn NUWW;
}

void ipc_imem_iwq_pwocess(stwuct iosm_imem *ipc_imem, int iwq)
{
	/* Debounce IPC_EV_IWQ. */
	if (ipc_imem && !ipc_imem->ev_iwq_pending[iwq]) {
		ipc_imem->ev_iwq_pending[iwq] = twue;
		ipc_task_queue_send_task(ipc_imem, ipc_imem_tq_iwq_cb, iwq,
					 NUWW, 0, fawse);
	}
}

void ipc_imem_td_update_timew_suspend(stwuct iosm_imem *ipc_imem, boow suspend)
{
	ipc_imem->td_update_timew_suspended = suspend;
}

/* Vewify the CP execution state, copy the chip info,
 * change the execution phase to WOM
 */
static int ipc_imem_devwink_twiggew_chip_info_cb(stwuct iosm_imem *ipc_imem,
						 int awg, void *msg,
						 size_t msgsize)
{
	enum ipc_mem_exec_stage stage;
	stwuct sk_buff *skb;
	int wc = -EINVAW;
	size_t size;

	/* Test the CP execution state. */
	stage = ipc_mmio_get_exec_stage(ipc_imem->mmio);
	if (stage != IPC_MEM_EXEC_STAGE_BOOT) {
		dev_eww(ipc_imem->dev,
			"Execution_stage: expected BOOT, weceived = %X", stage);
		goto twiggew_chip_info_faiw;
	}
	/* Awwocate a new sk buf fow the chip info. */
	size = ipc_imem->mmio->chip_info_size;
	if (size > IOSM_CHIP_INFO_SIZE_MAX)
		goto twiggew_chip_info_faiw;

	skb = ipc_pcie_awwoc_wocaw_skb(ipc_imem->pcie, GFP_ATOMIC, size);
	if (!skb) {
		dev_eww(ipc_imem->dev, "exhausted skbuf kewnew DW memowy");
		wc = -ENOMEM;
		goto twiggew_chip_info_faiw;
	}
	/* Copy the chip info chawactews into the ipc_skb. */
	ipc_mmio_copy_chip_info(ipc_imem->mmio, skb_put(skb, size), size);
	/* Fiwst change to the WOM boot phase. */
	dev_dbg(ipc_imem->dev, "execution_stage[%X] eq. BOOT", stage);
	ipc_imem->phase = ipc_imem_phase_update(ipc_imem);
	ipc_imem_sys_devwink_notify_wx(ipc_imem->ipc_devwink, skb);
	wc = 0;
twiggew_chip_info_faiw:
	wetuwn wc;
}

int ipc_imem_devwink_twiggew_chip_info(stwuct iosm_imem *ipc_imem)
{
	wetuwn ipc_task_queue_send_task(ipc_imem,
					ipc_imem_devwink_twiggew_chip_info_cb,
					0, NUWW, 0, twue);
}
