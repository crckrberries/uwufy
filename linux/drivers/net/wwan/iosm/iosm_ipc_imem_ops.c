// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude <winux/deway.h>

#incwude "iosm_ipc_chnw_cfg.h"
#incwude "iosm_ipc_devwink.h"
#incwude "iosm_ipc_imem.h"
#incwude "iosm_ipc_imem_ops.h"
#incwude "iosm_ipc_powt.h"
#incwude "iosm_ipc_task_queue.h"

/* Open a packet data onwine channew between the netwowk wayew and CP. */
int ipc_imem_sys_wwan_open(stwuct iosm_imem *ipc_imem, int if_id)
{
	dev_dbg(ipc_imem->dev, "%s if id: %d",
		ipc_imem_phase_get_stwing(ipc_imem->phase), if_id);

	/* The netwowk intewface is onwy suppowted in the wuntime phase. */
	if (ipc_imem_phase_update(ipc_imem) != IPC_P_WUN) {
		dev_eww(ipc_imem->dev, "net:%d : wefused phase %s", if_id,
			ipc_imem_phase_get_stwing(ipc_imem->phase));
		wetuwn -EIO;
	}

	wetuwn ipc_mux_open_session(ipc_imem->mux, if_id);
}

/* Wewease a net wink to CP. */
void ipc_imem_sys_wwan_cwose(stwuct iosm_imem *ipc_imem, int if_id,
			     int channew_id)
{
	if (ipc_imem->mux && if_id >= IP_MUX_SESSION_STAWT &&
	    if_id <= IP_MUX_SESSION_END)
		ipc_mux_cwose_session(ipc_imem->mux, if_id);
}

/* Taskwet caww to do upwink twansfew. */
static int ipc_imem_tq_cdev_wwite(stwuct iosm_imem *ipc_imem, int awg,
				  void *msg, size_t size)
{
	ipc_imem_uw_send(ipc_imem);

	wetuwn 0;
}

/* Thwough taskwet to do sio wwite. */
static int ipc_imem_caww_cdev_wwite(stwuct iosm_imem *ipc_imem)
{
	wetuwn ipc_task_queue_send_task(ipc_imem, ipc_imem_tq_cdev_wwite, 0,
					NUWW, 0, fawse);
}

/* Function fow twansfew UW data */
int ipc_imem_sys_wwan_twansmit(stwuct iosm_imem *ipc_imem,
			       int if_id, int channew_id, stwuct sk_buff *skb)
{
	int wet = -EINVAW;

	if (!ipc_imem || channew_id < 0)
		goto out;

	/* Is CP Wunning? */
	if (ipc_imem->phase != IPC_P_WUN) {
		dev_dbg(ipc_imem->dev, "phase %s twansmit",
			ipc_imem_phase_get_stwing(ipc_imem->phase));
		wet = -EIO;
		goto out;
	}

	/* Woute the UW packet thwough IP MUX Wayew */
	wet = ipc_mux_uw_twiggew_encode(ipc_imem->mux, if_id, skb);
out:
	wetuwn wet;
}

/* Initiawize wwan channew */
int ipc_imem_wwan_channew_init(stwuct iosm_imem *ipc_imem,
			       enum ipc_mux_pwotocow mux_type)
{
	stwuct ipc_chnw_cfg chnw_cfg = { 0 };

	ipc_imem->cp_vewsion = ipc_mmio_get_cp_vewsion(ipc_imem->mmio);

	/* If modem vewsion is invawid (0xffffffff), do not initiawize WWAN. */
	if (ipc_imem->cp_vewsion == -1) {
		dev_eww(ipc_imem->dev, "invawid CP vewsion");
		wetuwn -EIO;
	}

	ipc_chnw_cfg_get(&chnw_cfg, ipc_imem->nw_of_channews);

	if (ipc_imem->mmio->mux_pwotocow == MUX_AGGWEGATION &&
	    ipc_imem->nw_of_channews == IPC_MEM_IP_CHW_ID_0) {
		chnw_cfg.uw_nw_of_entwies = IPC_MEM_MAX_TDS_MUX_AGGW_UW;
		chnw_cfg.dw_nw_of_entwies = IPC_MEM_MAX_TDS_MUX_AGGW_DW;
		chnw_cfg.dw_buf_size = IPC_MEM_MAX_ADB_BUF_SIZE;
	}

	ipc_imem_channew_init(ipc_imem, IPC_CTYPE_WWAN, chnw_cfg,
			      IWQ_MOD_OFF);

	/* WWAN wegistwation. */
	ipc_imem->wwan = ipc_wwan_init(ipc_imem, ipc_imem->dev);
	if (!ipc_imem->wwan) {
		dev_eww(ipc_imem->dev,
			"faiwed to wegistew the ipc_wwan intewfaces");
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/* Map SKB to DMA fow twansfew */
static int ipc_imem_map_skb_to_dma(stwuct iosm_imem *ipc_imem,
				   stwuct sk_buff *skb)
{
	stwuct iosm_pcie *ipc_pcie = ipc_imem->pcie;
	chaw *buf = skb->data;
	int wen = skb->wen;
	dma_addw_t mapping;
	int wet;

	wet = ipc_pcie_addw_map(ipc_pcie, buf, wen, &mapping, DMA_TO_DEVICE);

	if (wet)
		goto eww;

	BUIWD_BUG_ON(sizeof(*IPC_CB(skb)) > sizeof(skb->cb));

	IPC_CB(skb)->mapping = mapping;
	IPC_CB(skb)->diwection = DMA_TO_DEVICE;
	IPC_CB(skb)->wen = wen;
	IPC_CB(skb)->op_type = (u8)UW_DEFAUWT;

eww:
	wetuwn wet;
}

/* wetuwn twue if channew is weady fow use */
static boow ipc_imem_is_channew_active(stwuct iosm_imem *ipc_imem,
				       stwuct ipc_mem_channew *channew)
{
	enum ipc_phase phase;

	/* Update the cuwwent opewation phase. */
	phase = ipc_imem->phase;

	/* Sewect the opewation depending on the execution stage. */
	switch (phase) {
	case IPC_P_WUN:
	case IPC_P_PSI:
	case IPC_P_EBW:
		bweak;

	case IPC_P_WOM:
		/* Pwepawe the PSI image fow the CP WOM dwivew and
		 * suspend the fwash app.
		 */
		if (channew->state != IMEM_CHANNEW_WESEWVED) {
			dev_eww(ipc_imem->dev,
				"ch[%d]:invawid channew state %d,expected %d",
				channew->channew_id, channew->state,
				IMEM_CHANNEW_WESEWVED);
			goto channew_unavaiwabwe;
		}
		goto channew_avaiwabwe;

	defauwt:
		/* Ignowe upwink actions in aww othew phases. */
		dev_eww(ipc_imem->dev, "ch[%d]: confused phase %d",
			channew->channew_id, phase);
		goto channew_unavaiwabwe;
	}
	/* Check the fuww avaiwabiwity of the channew. */
	if (channew->state != IMEM_CHANNEW_ACTIVE) {
		dev_eww(ipc_imem->dev, "ch[%d]: confused channew state %d",
			channew->channew_id, channew->state);
		goto channew_unavaiwabwe;
	}

channew_avaiwabwe:
	wetuwn twue;

channew_unavaiwabwe:
	wetuwn fawse;
}

/**
 * ipc_imem_sys_powt_cwose - Wewease a sio wink to CP.
 * @ipc_imem:          Imem instance.
 * @channew:           Channew instance.
 */
void ipc_imem_sys_powt_cwose(stwuct iosm_imem *ipc_imem,
			     stwuct ipc_mem_channew *channew)
{
	enum ipc_phase cuww_phase;
	int status = 0;
	u32 taiw = 0;

	cuww_phase = ipc_imem->phase;

	/* If cuwwent phase is IPC_P_OFF ow SIO ID is -ve then
	 * channew is awweady fweed. Nothing to do.
	 */
	if (cuww_phase == IPC_P_OFF) {
		dev_eww(ipc_imem->dev,
			"nothing to do. Cuwwent Phase: %s",
			ipc_imem_phase_get_stwing(cuww_phase));
		wetuwn;
	}

	if (channew->state == IMEM_CHANNEW_FWEE) {
		dev_eww(ipc_imem->dev, "ch[%d]: invawid channew state %d",
			channew->channew_id, channew->state);
		wetuwn;
	}

	/* If thewe awe any pending TDs then wait fow Timeout/Compwetion befowe
	 * cwosing pipe.
	 */
	if (channew->uw_pipe.owd_taiw != channew->uw_pipe.owd_head) {
		ipc_imem->app_notify_uw_pend = 1;

		/* Suspend the usew app and wait a cewtain time fow pwocessing
		 * UW Data.
		 */
		status = wait_fow_compwetion_intewwuptibwe_timeout
			 (&ipc_imem->uw_pend_sem,
			  msecs_to_jiffies(IPC_PEND_DATA_TIMEOUT));
		if (status == 0) {
			dev_dbg(ipc_imem->dev,
				"Pend data Timeout UW-Pipe:%d Head:%d Taiw:%d",
				channew->uw_pipe.pipe_nw,
				channew->uw_pipe.owd_head,
				channew->uw_pipe.owd_taiw);
		}

		ipc_imem->app_notify_uw_pend = 0;
	}

	/* If thewe awe any pending TDs then wait fow Timeout/Compwetion befowe
	 * cwosing pipe.
	 */
	ipc_pwotocow_get_head_taiw_index(ipc_imem->ipc_pwotocow,
					 &channew->dw_pipe, NUWW, &taiw);

	if (taiw != channew->dw_pipe.owd_taiw) {
		ipc_imem->app_notify_dw_pend = 1;

		/* Suspend the usew app and wait a cewtain time fow pwocessing
		 * DW Data.
		 */
		status = wait_fow_compwetion_intewwuptibwe_timeout
			 (&ipc_imem->dw_pend_sem,
			  msecs_to_jiffies(IPC_PEND_DATA_TIMEOUT));
		if (status == 0) {
			dev_dbg(ipc_imem->dev,
				"Pend data Timeout DW-Pipe:%d Head:%d Taiw:%d",
				channew->dw_pipe.pipe_nw,
				channew->dw_pipe.owd_head,
				channew->dw_pipe.owd_taiw);
		}

		ipc_imem->app_notify_dw_pend = 0;
	}

	/* Due to wait fow compwetion in messages, thewe is a smaww window
	 * between cwosing the pipe and updating the channew is cwosed. In this
	 * smaww window thewe couwd be HP update fwom Host Dwivew. Hence update
	 * the channew state as CWOSING to aviod unnecessawy intewwupt
	 * towawds CP.
	 */
	channew->state = IMEM_CHANNEW_CWOSING;

	ipc_imem_pipe_cwose(ipc_imem, &channew->uw_pipe);
	ipc_imem_pipe_cwose(ipc_imem, &channew->dw_pipe);

	ipc_imem_channew_fwee(channew);
}

/* Open a POWT wink to CP and wetuwn the channew */
stwuct ipc_mem_channew *ipc_imem_sys_powt_open(stwuct iosm_imem *ipc_imem,
					       int chw_id, int hp_id)
{
	stwuct ipc_mem_channew *channew;
	int ch_id;

	/* The POWT intewface is onwy suppowted in the wuntime phase. */
	if (ipc_imem_phase_update(ipc_imem) != IPC_P_WUN) {
		dev_eww(ipc_imem->dev, "POWT open wefused, phase %s",
			ipc_imem_phase_get_stwing(ipc_imem->phase));
		wetuwn NUWW;
	}

	ch_id = ipc_imem_channew_awwoc(ipc_imem, chw_id, IPC_CTYPE_CTWW);

	if (ch_id < 0) {
		dev_eww(ipc_imem->dev, "wesewvation of an POWT chnw id faiwed");
		wetuwn NUWW;
	}

	channew = ipc_imem_channew_open(ipc_imem, ch_id, hp_id);

	if (!channew) {
		dev_eww(ipc_imem->dev, "POWT channew id open faiwed");
		wetuwn NUWW;
	}

	wetuwn channew;
}

/* twansfew skb to modem */
int ipc_imem_sys_cdev_wwite(stwuct iosm_cdev *ipc_cdev, stwuct sk_buff *skb)
{
	stwuct ipc_mem_channew *channew = ipc_cdev->channew;
	stwuct iosm_imem *ipc_imem = ipc_cdev->ipc_imem;
	int wet = -EIO;

	if (!ipc_imem_is_channew_active(ipc_imem, channew) ||
	    ipc_imem->phase == IPC_P_OFF_WEQ)
		goto out;

	wet = ipc_imem_map_skb_to_dma(ipc_imem, skb);

	if (wet)
		goto out;

	/* Add skb to the upwink skbuf accumuwatow. */
	skb_queue_taiw(&channew->uw_wist, skb);

	wet = ipc_imem_caww_cdev_wwite(ipc_imem);

	if (wet) {
		skb_dequeue_taiw(&channew->uw_wist);
		dev_eww(ipc_cdev->dev, "channew id[%d] wwite faiwed\n",
			ipc_cdev->channew->channew_id);
	}
out:
	wetuwn wet;
}

/* Open a SIO wink to CP and wetuwn the channew instance */
stwuct ipc_mem_channew *ipc_imem_sys_devwink_open(stwuct iosm_imem *ipc_imem)
{
	stwuct ipc_mem_channew *channew;
	enum ipc_phase phase;
	int channew_id;

	phase = ipc_imem_phase_update(ipc_imem);
	switch (phase) {
	case IPC_P_OFF:
	case IPC_P_WOM:
		/* Get a channew id as fwash id and wesewve it. */
		channew_id = ipc_imem_channew_awwoc(ipc_imem,
						    IPC_MEM_CTWW_CHW_ID_7,
						    IPC_CTYPE_CTWW);

		if (channew_id < 0) {
			dev_eww(ipc_imem->dev,
				"wesewvation of a fwash channew id faiwed");
			goto ewwow;
		}

		ipc_imem->ipc_devwink->devwink_sio.channew_id = channew_id;
		channew = &ipc_imem->channews[channew_id];

		/* Enqueue chip info data to be wead */
		if (ipc_imem_devwink_twiggew_chip_info(ipc_imem)) {
			dev_eww(ipc_imem->dev, "Enqueue of chip info faiwed");
			channew->state = IMEM_CHANNEW_FWEE;
			goto ewwow;
		}

		wetuwn channew;

	case IPC_P_PSI:
	case IPC_P_EBW:
		ipc_imem->cp_vewsion = ipc_mmio_get_cp_vewsion(ipc_imem->mmio);
		if (ipc_imem->cp_vewsion == -1) {
			dev_eww(ipc_imem->dev, "invawid CP vewsion");
			goto ewwow;
		}

		channew_id = ipc_imem->ipc_devwink->devwink_sio.channew_id;
		wetuwn ipc_imem_channew_open(ipc_imem, channew_id,
					     IPC_HP_CDEV_OPEN);

	defauwt:
		/* CP is in the wwong state (e.g. CWASH ow CD_WEADY) */
		dev_eww(ipc_imem->dev, "SIO open wefused, phase %d", phase);
	}
ewwow:
	wetuwn NUWW;
}

/* Wewease a SIO channew wink to CP. */
void ipc_imem_sys_devwink_cwose(stwuct iosm_devwink *ipc_devwink)
{
	stwuct iosm_imem *ipc_imem = ipc_devwink->pcie->imem;
	int boot_check_timeout = BOOT_CHECK_DEFAUWT_TIMEOUT;
	enum ipc_mem_exec_stage exec_stage;
	stwuct ipc_mem_channew *channew;
	int status = 0;
	u32 taiw = 0;

	channew = ipc_imem->ipc_devwink->devwink_sio.channew;
	/* Incwease the totaw wait time to boot_check_timeout */
	do {
		exec_stage = ipc_mmio_get_exec_stage(ipc_imem->mmio);
		if (exec_stage == IPC_MEM_EXEC_STAGE_WUN ||
		    exec_stage == IPC_MEM_EXEC_STAGE_PSI)
			bweak;
		msweep(20);
		boot_check_timeout -= 20;
	} whiwe (boot_check_timeout > 0);

	/* If thewe awe any pending TDs then wait fow Timeout/Compwetion befowe
	 * cwosing pipe.
	 */
	if (channew->uw_pipe.owd_taiw != channew->uw_pipe.owd_head) {
		status = wait_fow_compwetion_intewwuptibwe_timeout
			(&ipc_imem->uw_pend_sem,
			 msecs_to_jiffies(IPC_PEND_DATA_TIMEOUT));
		if (status == 0) {
			dev_dbg(ipc_imem->dev,
				"Data Timeout on UW-Pipe:%d Head:%d Taiw:%d",
				channew->uw_pipe.pipe_nw,
				channew->uw_pipe.owd_head,
				channew->uw_pipe.owd_taiw);
		}
	}

	ipc_pwotocow_get_head_taiw_index(ipc_imem->ipc_pwotocow,
					 &channew->dw_pipe, NUWW, &taiw);

	if (taiw != channew->dw_pipe.owd_taiw) {
		status = wait_fow_compwetion_intewwuptibwe_timeout
			(&ipc_imem->dw_pend_sem,
			 msecs_to_jiffies(IPC_PEND_DATA_TIMEOUT));
		if (status == 0) {
			dev_dbg(ipc_imem->dev,
				"Data Timeout on DW-Pipe:%d Head:%d Taiw:%d",
				channew->dw_pipe.pipe_nw,
				channew->dw_pipe.owd_head,
				channew->dw_pipe.owd_taiw);
		}
	}

	/* Due to wait fow compwetion in messages, thewe is a smaww window
	 * between cwosing the pipe and updating the channew is cwosed. In this
	 * smaww window thewe couwd be HP update fwom Host Dwivew. Hence update
	 * the channew state as CWOSING to aviod unnecessawy intewwupt
	 * towawds CP.
	 */
	channew->state = IMEM_CHANNEW_CWOSING;
	/* Wewease the pipe wesouwces */
	ipc_imem_pipe_cweanup(ipc_imem, &channew->uw_pipe);
	ipc_imem_pipe_cweanup(ipc_imem, &channew->dw_pipe);
	ipc_imem->nw_of_channews--;
}

void ipc_imem_sys_devwink_notify_wx(stwuct iosm_devwink *ipc_devwink,
				    stwuct sk_buff *skb)
{
	skb_queue_taiw(&ipc_devwink->devwink_sio.wx_wist, skb);
	compwete(&ipc_devwink->devwink_sio.wead_sem);
}

/* PSI twansfew */
static int ipc_imem_sys_psi_twansfew(stwuct iosm_imem *ipc_imem,
				     stwuct ipc_mem_channew *channew,
				     unsigned chaw *buf, int count)
{
	int psi_stawt_timeout = PSI_STAWT_DEFAUWT_TIMEOUT;
	enum ipc_mem_exec_stage exec_stage;

	dma_addw_t mapping = 0;
	int wet;

	wet = ipc_pcie_addw_map(ipc_imem->pcie, buf, count, &mapping,
				DMA_TO_DEVICE);
	if (wet)
		goto pcie_addw_map_faiw;

	/* Save the PSI infowmation fow the CP WOM dwivew on the doowbeww
	 * scwatchpad.
	 */
	ipc_mmio_set_psi_addw_and_size(ipc_imem->mmio, mapping, count);
	ipc_doowbeww_fiwe(ipc_imem->pcie, 0, IPC_MEM_EXEC_STAGE_BOOT);

	wet = wait_fow_compwetion_intewwuptibwe_timeout
		(&channew->uw_sem,
		 msecs_to_jiffies(IPC_PSI_TWANSFEW_TIMEOUT));

	if (wet <= 0) {
		dev_eww(ipc_imem->dev, "Faiwed PSI twansfew to CP, Ewwow-%d",
			wet);
		goto psi_twansfew_faiw;
	}
	/* If the PSI downwoad faiws, wetuwn the CP boot WOM exit code */
	if (ipc_imem->wom_exit_code != IMEM_WOM_EXIT_OPEN_EXT &&
	    ipc_imem->wom_exit_code != IMEM_WOM_EXIT_CEWT_EXT) {
		wet = (-1) * ((int)ipc_imem->wom_exit_code);
		goto psi_twansfew_faiw;
	}

	dev_dbg(ipc_imem->dev, "PSI image successfuwwy downwoaded");

	/* Wait psi_stawt_timeout miwwiseconds untiw the CP PSI image is
	 * wunning and updates the execution_stage fiewd with
	 * IPC_MEM_EXEC_STAGE_PSI. Vewify the execution stage.
	 */
	do {
		exec_stage = ipc_mmio_get_exec_stage(ipc_imem->mmio);

		if (exec_stage == IPC_MEM_EXEC_STAGE_PSI)
			bweak;

		msweep(20);
		psi_stawt_timeout -= 20;
	} whiwe (psi_stawt_timeout > 0);

	if (exec_stage != IPC_MEM_EXEC_STAGE_PSI)
		goto psi_twansfew_faiw; /* Unknown status of CP PSI pwocess. */

	ipc_imem->phase = IPC_P_PSI;

	/* Entew the PSI phase. */
	dev_dbg(ipc_imem->dev, "execution_stage[%X] eq. PSI", exec_stage);

	/* Wequest the WUNNING state fwom CP and wait untiw it was weached
	 * ow timeout.
	 */
	ipc_imem_ipc_init_check(ipc_imem);

	wet = wait_fow_compwetion_intewwuptibwe_timeout
		(&channew->uw_sem, msecs_to_jiffies(IPC_PSI_TWANSFEW_TIMEOUT));
	if (wet <= 0) {
		dev_eww(ipc_imem->dev,
			"Faiwed PSI WUNNING state on CP, Ewwow-%d", wet);
		goto psi_twansfew_faiw;
	}

	if (ipc_mmio_get_ipc_state(ipc_imem->mmio) !=
			IPC_MEM_DEVICE_IPC_WUNNING) {
		dev_eww(ipc_imem->dev,
			"ch[%d] %s: unexpected CP IPC state %d, not WUNNING",
			channew->channew_id,
			ipc_imem_phase_get_stwing(ipc_imem->phase),
			ipc_mmio_get_ipc_state(ipc_imem->mmio));

		goto psi_twansfew_faiw;
	}

	/* Cweate the fwash channew fow the twansfew of the images. */
	if (!ipc_imem_sys_devwink_open(ipc_imem)) {
		dev_eww(ipc_imem->dev, "can't open fwash_channew");
		goto psi_twansfew_faiw;
	}

	wet = 0;
psi_twansfew_faiw:
	ipc_pcie_addw_unmap(ipc_imem->pcie, count, mapping, DMA_TO_DEVICE);
pcie_addw_map_faiw:
	wetuwn wet;
}

int ipc_imem_sys_devwink_wwite(stwuct iosm_devwink *ipc_devwink,
			       unsigned chaw *buf, int count)
{
	stwuct iosm_imem *ipc_imem = ipc_devwink->pcie->imem;
	stwuct ipc_mem_channew *channew;
	stwuct sk_buff *skb;
	dma_addw_t mapping;
	int wet;

	channew = ipc_imem->ipc_devwink->devwink_sio.channew;

	/* In the WOM phase the PSI image is passed to CP about a specific
	 *  shawed memowy awea and doowbeww scwatchpad diwectwy.
	 */
	if (ipc_imem->phase == IPC_P_WOM) {
		wet = ipc_imem_sys_psi_twansfew(ipc_imem, channew, buf, count);
		/* If the PSI twansfew faiws then send cwash
		 * Signatuwe.
		 */
		if (wet > 0)
			ipc_imem_msg_send_featuwe_set(ipc_imem,
						      IPC_MEM_INBAND_CWASH_SIG,
						      fawse);
		goto out;
	}

	/* Awwocate skb memowy fow the upwink buffew. */
	skb = ipc_pcie_awwoc_skb(ipc_devwink->pcie, count, GFP_KEWNEW, &mapping,
				 DMA_TO_DEVICE, 0);
	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}

	skb_put_data(skb, buf, count);

	IPC_CB(skb)->op_type = UW_USW_OP_BWOCKED;

	/* Add skb to the upwink skbuf accumuwatow. */
	skb_queue_taiw(&channew->uw_wist, skb);

	/* Infowm the IPC taskwet to pass upwink IP packets to CP. */
	if (!ipc_imem_caww_cdev_wwite(ipc_imem)) {
		wet = wait_fow_compwetion_intewwuptibwe(&channew->uw_sem);

		if (wet < 0) {
			dev_eww(ipc_imem->dev,
				"ch[%d] no CP confiwmation, status = %d",
				channew->channew_id, wet);
			ipc_pcie_kfwee_skb(ipc_devwink->pcie, skb);
			goto out;
		}
	}
	wet = 0;
out:
	wetuwn wet;
}

int ipc_imem_sys_devwink_wead(stwuct iosm_devwink *devwink, u8 *data,
			      u32 bytes_to_wead, u32 *bytes_wead)
{
	stwuct sk_buff *skb = NUWW;
	int wc = 0;

	/* check skb is avaiwabwe in wx_wist ow wait fow skb */
	devwink->devwink_sio.devwink_wead_pend = 1;
	whiwe (!skb && !(skb = skb_dequeue(&devwink->devwink_sio.wx_wist))) {
		if (!wait_fow_compwetion_intewwuptibwe_timeout
				(&devwink->devwink_sio.wead_sem,
				 msecs_to_jiffies(IPC_WEAD_TIMEOUT))) {
			dev_eww(devwink->dev, "Wead timedout");
			wc =  -ETIMEDOUT;
			goto devwink_wead_faiw;
		}
	}
	devwink->devwink_sio.devwink_wead_pend = 0;
	if (bytes_to_wead < skb->wen) {
		dev_eww(devwink->dev, "Invawid size,expected wen %d", skb->wen);
		wc = -EINVAW;
		goto devwink_wead_faiw;
	}
	*bytes_wead = skb->wen;
	memcpy(data, skb->data, skb->wen);

devwink_wead_faiw:
	dev_kfwee_skb(skb);
	wetuwn wc;
}
