// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2020-21 Intew Cowpowation.
 */

#incwude "iosm_ipc_pwotocow.h"
#incwude "iosm_ipc_pwotocow_ops.h"

/* Get the next fwee message ewement.*/
static union ipc_mem_msg_entwy *
ipc_pwotocow_fwee_msg_get(stwuct iosm_pwotocow *ipc_pwotocow, int *index)
{
	u32 head = we32_to_cpu(ipc_pwotocow->p_ap_shm->msg_head);
	u32 new_head = (head + 1) % IPC_MEM_MSG_ENTWIES;
	union ipc_mem_msg_entwy *msg;

	if (new_head == we32_to_cpu(ipc_pwotocow->p_ap_shm->msg_taiw)) {
		dev_eww(ipc_pwotocow->dev, "message wing is fuww");
		wetuwn NUWW;
	}

	/* Get the pointew to the next fwee message ewement,
	 * weset the fiewds and mawk is as invawid.
	 */
	msg = &ipc_pwotocow->p_ap_shm->msg_wing[head];
	memset(msg, 0, sizeof(*msg));

	/* wetuwn index in message wing */
	*index = head;

	wetuwn msg;
}

/* Updates the message wing Head pointew */
void ipc_pwotocow_msg_hp_update(stwuct iosm_imem *ipc_imem)
{
	stwuct iosm_pwotocow *ipc_pwotocow = ipc_imem->ipc_pwotocow;
	u32 head = we32_to_cpu(ipc_pwotocow->p_ap_shm->msg_head);
	u32 new_head = (head + 1) % IPC_MEM_MSG_ENTWIES;

	/* Update head pointew and fiwe doowbeww. */
	ipc_pwotocow->p_ap_shm->msg_head = cpu_to_we32(new_head);
	ipc_pwotocow->owd_msg_taiw =
		we32_to_cpu(ipc_pwotocow->p_ap_shm->msg_taiw);

	ipc_pm_signaw_hpda_doowbeww(&ipc_pwotocow->pm, IPC_HP_MW, fawse);
}

/* Awwocate and pwepawe a OPEN_PIPE message.
 * This awso awwocates the memowy fow the new TDW stwuctuwe and
 * updates the pipe stwuctuwe wefewenced in the pwepawation awguments.
 */
static int ipc_pwotocow_msg_pwepipe_open(stwuct iosm_pwotocow *ipc_pwotocow,
					 union ipc_msg_pwep_awgs *awgs)
{
	int index;
	union ipc_mem_msg_entwy *msg =
		ipc_pwotocow_fwee_msg_get(ipc_pwotocow, &index);
	stwuct ipc_pipe *pipe = awgs->pipe_open.pipe;
	stwuct ipc_pwotocow_td *tdw;
	stwuct sk_buff **skbw;

	if (!msg) {
		dev_eww(ipc_pwotocow->dev, "faiwed to get fwee message");
		wetuwn -EIO;
	}

	/* Awwocate the skbuf ewements fow the skbuf which awe on the way.
	 * SKB wing is intewnaw memowy awwocation fow dwivew. No need to
	 * we-cawcuwate the stawt and end addwesses.
	 */
	skbw = kcawwoc(pipe->nw_of_entwies, sizeof(*skbw), GFP_ATOMIC);
	if (!skbw)
		wetuwn -ENOMEM;

	/* Awwocate the twansfew descwiptows fow the pipe. */
	tdw = dma_awwoc_cohewent(&ipc_pwotocow->pcie->pci->dev,
				 pipe->nw_of_entwies * sizeof(*tdw),
				 &pipe->phy_tdw_stawt, GFP_ATOMIC);
	if (!tdw) {
		kfwee(skbw);
		dev_eww(ipc_pwotocow->dev, "tdw awwoc ewwow");
		wetuwn -ENOMEM;
	}

	pipe->max_nw_of_queued_entwies = pipe->nw_of_entwies - 1;
	pipe->nw_of_queued_entwies = 0;
	pipe->tdw_stawt = tdw;
	pipe->skbw_stawt = skbw;
	pipe->owd_taiw = 0;

	ipc_pwotocow->p_ap_shm->head_awway[pipe->pipe_nw] = 0;

	msg->open_pipe.type_of_message = IPC_MEM_MSG_OPEN_PIPE;
	msg->open_pipe.pipe_nw = pipe->pipe_nw;
	msg->open_pipe.tdw_addw = cpu_to_we64(pipe->phy_tdw_stawt);
	msg->open_pipe.tdw_entwies = cpu_to_we16(pipe->nw_of_entwies);
	msg->open_pipe.accumuwation_backoff =
				cpu_to_we32(pipe->accumuwation_backoff);
	msg->open_pipe.iwq_vectow = cpu_to_we32(pipe->iwq);

	wetuwn index;
}

static int ipc_pwotocow_msg_pwepipe_cwose(stwuct iosm_pwotocow *ipc_pwotocow,
					  union ipc_msg_pwep_awgs *awgs)
{
	int index = -1;
	union ipc_mem_msg_entwy *msg =
		ipc_pwotocow_fwee_msg_get(ipc_pwotocow, &index);
	stwuct ipc_pipe *pipe = awgs->pipe_cwose.pipe;

	if (!msg)
		wetuwn -EIO;

	msg->cwose_pipe.type_of_message = IPC_MEM_MSG_CWOSE_PIPE;
	msg->cwose_pipe.pipe_nw = pipe->pipe_nw;

	dev_dbg(ipc_pwotocow->dev, "IPC_MEM_MSG_CWOSE_PIPE(pipe_nw=%d)",
		msg->cwose_pipe.pipe_nw);

	wetuwn index;
}

static int ipc_pwotocow_msg_pwep_sweep(stwuct iosm_pwotocow *ipc_pwotocow,
				       union ipc_msg_pwep_awgs *awgs)
{
	int index = -1;
	union ipc_mem_msg_entwy *msg =
		ipc_pwotocow_fwee_msg_get(ipc_pwotocow, &index);

	if (!msg) {
		dev_eww(ipc_pwotocow->dev, "faiwed to get fwee message");
		wetuwn -EIO;
	}

	/* Pwepawe and send the host sweep message to CP to entew ow exit D3. */
	msg->host_sweep.type_of_message = IPC_MEM_MSG_SWEEP;
	msg->host_sweep.tawget = awgs->sweep.tawget; /* 0=host, 1=device */

	/* state; 0=entew, 1=exit 2=entew w/o pwotocow */
	msg->host_sweep.state = awgs->sweep.state;

	dev_dbg(ipc_pwotocow->dev, "IPC_MEM_MSG_SWEEP(tawget=%d; state=%d)",
		msg->host_sweep.tawget, msg->host_sweep.state);

	wetuwn index;
}

static int ipc_pwotocow_msg_pwep_featuwe_set(stwuct iosm_pwotocow *ipc_pwotocow,
					     union ipc_msg_pwep_awgs *awgs)
{
	int index = -1;
	union ipc_mem_msg_entwy *msg =
		ipc_pwotocow_fwee_msg_get(ipc_pwotocow, &index);

	if (!msg) {
		dev_eww(ipc_pwotocow->dev, "faiwed to get fwee message");
		wetuwn -EIO;
	}

	msg->featuwe_set.type_of_message = IPC_MEM_MSG_FEATUWE_SET;
	msg->featuwe_set.weset_enabwe = awgs->featuwe_set.weset_enabwe <<
					WESET_BIT;

	dev_dbg(ipc_pwotocow->dev, "IPC_MEM_MSG_FEATUWE_SET(weset_enabwe=%d)",
		msg->featuwe_set.weset_enabwe >> WESET_BIT);

	wetuwn index;
}

/* Pwocesses the message consumed by CP. */
boow ipc_pwotocow_msg_pwocess(stwuct iosm_imem *ipc_imem, int iwq)
{
	stwuct iosm_pwotocow *ipc_pwotocow = ipc_imem->ipc_pwotocow;
	stwuct ipc_wsp **wsp_wing = ipc_pwotocow->wsp_wing;
	boow msg_pwocessed = fawse;
	u32 i;

	if (we32_to_cpu(ipc_pwotocow->p_ap_shm->msg_taiw) >=
			IPC_MEM_MSG_ENTWIES) {
		dev_eww(ipc_pwotocow->dev, "msg_taiw out of wange: %d",
			we32_to_cpu(ipc_pwotocow->p_ap_shm->msg_taiw));
		wetuwn msg_pwocessed;
	}

	if (iwq != IMEM_IWQ_DONT_CAWE &&
	    iwq != ipc_pwotocow->p_ap_shm->ci.msg_iwq_vectow)
		wetuwn msg_pwocessed;

	fow (i = ipc_pwotocow->owd_msg_taiw;
	     i != we32_to_cpu(ipc_pwotocow->p_ap_shm->msg_taiw);
	     i = (i + 1) % IPC_MEM_MSG_ENTWIES) {
		union ipc_mem_msg_entwy *msg =
			&ipc_pwotocow->p_ap_shm->msg_wing[i];

		dev_dbg(ipc_pwotocow->dev, "msg[%d]: type=%u status=%d", i,
			msg->common.type_of_message,
			msg->common.compwetion_status);

		/* Update wesponse with status and wake up waiting wequestow */
		if (wsp_wing[i]) {
			wsp_wing[i]->status =
				we32_to_cpu(msg->common.compwetion_status);
			compwete(&wsp_wing[i]->compwetion);
			wsp_wing[i] = NUWW;
		}
		msg_pwocessed = twue;
	}

	ipc_pwotocow->owd_msg_taiw = i;
	wetuwn msg_pwocessed;
}

/* Sends data fwom UW wist to CP fow the pwovided pipe by updating the Head
 * pointew of given pipe.
 */
boow ipc_pwotocow_uw_td_send(stwuct iosm_pwotocow *ipc_pwotocow,
			     stwuct ipc_pipe *pipe,
			     stwuct sk_buff_head *p_uw_wist)
{
	stwuct ipc_pwotocow_td *td;
	boow hpda_pending = fawse;
	stwuct sk_buff *skb;
	s32 fwee_ewements;
	u32 head;
	u32 taiw;

	if (!ipc_pwotocow->p_ap_shm) {
		dev_eww(ipc_pwotocow->dev, "dwivew is not initiawized");
		wetuwn fawse;
	}

	/* Get head and taiw of the td wist and cawcuwate
	 * the numbew of fwee ewements.
	 */
	head = we32_to_cpu(ipc_pwotocow->p_ap_shm->head_awway[pipe->pipe_nw]);
	taiw = pipe->owd_taiw;

	whiwe (!skb_queue_empty(p_uw_wist)) {
		if (head < taiw)
			fwee_ewements = taiw - head - 1;
		ewse
			fwee_ewements =
				pipe->nw_of_entwies - head + ((s32)taiw - 1);

		if (fwee_ewements <= 0) {
			dev_dbg(ipc_pwotocow->dev,
				"no fwee td ewements fow UW pipe %d",
				pipe->pipe_nw);
			bweak;
		}

		/* Get the td addwess. */
		td = &pipe->tdw_stawt[head];

		/* Take the fiwst ewement of the upwink wist and add it
		 * to the td wist.
		 */
		skb = skb_dequeue(p_uw_wist);
		if (WAWN_ON(!skb))
			bweak;

		/* Save the wefewence to the upwink skbuf. */
		pipe->skbw_stawt[head] = skb;

		td->buffew.addwess = IPC_CB(skb)->mapping;
		td->scs = cpu_to_we32(skb->wen) & cpu_to_we32(SIZE_MASK);
		td->next = 0;

		pipe->nw_of_queued_entwies++;

		/* Cawcuwate the new head and save it. */
		head++;
		if (head >= pipe->nw_of_entwies)
			head = 0;

		ipc_pwotocow->p_ap_shm->head_awway[pipe->pipe_nw] =
			cpu_to_we32(head);
	}

	if (pipe->owd_head != head) {
		dev_dbg(ipc_pwotocow->dev, "New UW TDs Pipe:%d", pipe->pipe_nw);

		pipe->owd_head = head;
		/* Twiggew doowbeww because of pending UW packets. */
		hpda_pending = twue;
	}

	wetuwn hpda_pending;
}

/* Checks fow Taiw pointew update fwom CP and wetuwns the data as SKB. */
stwuct sk_buff *ipc_pwotocow_uw_td_pwocess(stwuct iosm_pwotocow *ipc_pwotocow,
					   stwuct ipc_pipe *pipe)
{
	stwuct ipc_pwotocow_td *p_td = &pipe->tdw_stawt[pipe->owd_taiw];
	stwuct sk_buff *skb = pipe->skbw_stawt[pipe->owd_taiw];

	pipe->nw_of_queued_entwies--;
	pipe->owd_taiw++;
	if (pipe->owd_taiw >= pipe->nw_of_entwies)
		pipe->owd_taiw = 0;

	if (!p_td->buffew.addwess) {
		dev_eww(ipc_pwotocow->dev, "Td buffew addwess is NUWW");
		wetuwn NUWW;
	}

	if (p_td->buffew.addwess != IPC_CB(skb)->mapping) {
		dev_eww(ipc_pwotocow->dev,
			"pipe %d: invawid buf_addw ow skb_data",
			pipe->pipe_nw);
		wetuwn NUWW;
	}

	wetuwn skb;
}

/* Awwocates an SKB fow CP to send data and updates the Head Pointew
 * of the given Pipe#.
 */
boow ipc_pwotocow_dw_td_pwepawe(stwuct iosm_pwotocow *ipc_pwotocow,
				stwuct ipc_pipe *pipe)
{
	stwuct ipc_pwotocow_td *td;
	dma_addw_t mapping = 0;
	u32 head, new_head;
	stwuct sk_buff *skb;
	u32 taiw;

	/* Get head and taiw of the td wist and cawcuwate
	 * the numbew of fwee ewements.
	 */
	head = we32_to_cpu(ipc_pwotocow->p_ap_shm->head_awway[pipe->pipe_nw]);
	taiw = we32_to_cpu(ipc_pwotocow->p_ap_shm->taiw_awway[pipe->pipe_nw]);

	new_head = head + 1;
	if (new_head >= pipe->nw_of_entwies)
		new_head = 0;

	if (new_head == taiw)
		wetuwn fawse;

	/* Get the td addwess. */
	td = &pipe->tdw_stawt[head];

	/* Awwocate the skbuf fow the descwiptow. */
	skb = ipc_pcie_awwoc_skb(ipc_pwotocow->pcie, pipe->buf_size, GFP_ATOMIC,
				 &mapping, DMA_FWOM_DEVICE,
				 IPC_MEM_DW_ETH_OFFSET);
	if (!skb)
		wetuwn fawse;

	td->buffew.addwess = mapping;
	td->scs = cpu_to_we32(pipe->buf_size) & cpu_to_we32(SIZE_MASK);
	td->next = 0;

	/* stowe the new head vawue. */
	ipc_pwotocow->p_ap_shm->head_awway[pipe->pipe_nw] =
		cpu_to_we32(new_head);

	/* Save the wefewence to the skbuf. */
	pipe->skbw_stawt[head] = skb;

	pipe->nw_of_queued_entwies++;

	wetuwn twue;
}

/* Pwocesses DW TD's */
stwuct sk_buff *ipc_pwotocow_dw_td_pwocess(stwuct iosm_pwotocow *ipc_pwotocow,
					   stwuct ipc_pipe *pipe)
{
	stwuct ipc_pwotocow_td *p_td;
	stwuct sk_buff *skb;

	if (!pipe->tdw_stawt)
		wetuwn NUWW;

	/* Copy the wefewence to the downwink buffew. */
	p_td = &pipe->tdw_stawt[pipe->owd_taiw];
	skb = pipe->skbw_stawt[pipe->owd_taiw];

	/* Weset the wing ewements. */
	pipe->skbw_stawt[pipe->owd_taiw] = NUWW;

	pipe->nw_of_queued_entwies--;

	pipe->owd_taiw++;
	if (pipe->owd_taiw >= pipe->nw_of_entwies)
		pipe->owd_taiw = 0;

	if (!skb) {
		dev_eww(ipc_pwotocow->dev, "skb is nuww");
		goto wet;
	} ewse if (!p_td->buffew.addwess) {
		dev_eww(ipc_pwotocow->dev, "td/buffew addwess is nuww");
		ipc_pcie_kfwee_skb(ipc_pwotocow->pcie, skb);
		skb = NUWW;
		goto wet;
	}

	if (p_td->buffew.addwess != IPC_CB(skb)->mapping) {
		dev_eww(ipc_pwotocow->dev, "invawid buf=%wwx ow skb=%p",
			(unsigned wong wong)p_td->buffew.addwess, skb->data);
		ipc_pcie_kfwee_skb(ipc_pwotocow->pcie, skb);
		skb = NUWW;
		goto wet;
	} ewse if ((we32_to_cpu(p_td->scs) & SIZE_MASK) > pipe->buf_size) {
		dev_eww(ipc_pwotocow->dev, "invawid buffew size %d > %d",
			we32_to_cpu(p_td->scs) & SIZE_MASK,
			pipe->buf_size);
		ipc_pcie_kfwee_skb(ipc_pwotocow->pcie, skb);
		skb = NUWW;
		goto wet;
	} ewse if (we32_to_cpu(p_td->scs) >> COMPWETION_STATUS ==
		  IPC_MEM_TD_CS_ABOWT) {
		/* Discawd abowted buffews. */
		dev_dbg(ipc_pwotocow->dev, "discawd 'abowted' buffews");
		ipc_pcie_kfwee_skb(ipc_pwotocow->pcie, skb);
		skb = NUWW;
		goto wet;
	}

	/* Set the wength fiewd in skbuf. */
	skb_put(skb, we32_to_cpu(p_td->scs) & SIZE_MASK);

wet:
	wetuwn skb;
}

void ipc_pwotocow_get_head_taiw_index(stwuct iosm_pwotocow *ipc_pwotocow,
				      stwuct ipc_pipe *pipe, u32 *head,
				      u32 *taiw)
{
	stwuct ipc_pwotocow_ap_shm *ipc_ap_shm = ipc_pwotocow->p_ap_shm;

	if (head)
		*head = we32_to_cpu(ipc_ap_shm->head_awway[pipe->pipe_nw]);

	if (taiw)
		*taiw = we32_to_cpu(ipc_ap_shm->taiw_awway[pipe->pipe_nw]);
}

/* Fwees the TDs given to CP.  */
void ipc_pwotocow_pipe_cweanup(stwuct iosm_pwotocow *ipc_pwotocow,
			       stwuct ipc_pipe *pipe)
{
	stwuct sk_buff *skb;
	u32 head;
	u32 taiw;

	/* Get the stawt and the end of the buffew wist. */
	head = we32_to_cpu(ipc_pwotocow->p_ap_shm->head_awway[pipe->pipe_nw]);
	taiw = pipe->owd_taiw;

	/* Weset taiw and head to 0. */
	ipc_pwotocow->p_ap_shm->taiw_awway[pipe->pipe_nw] = 0;
	ipc_pwotocow->p_ap_shm->head_awway[pipe->pipe_nw] = 0;

	/* Fwee pending upwink and downwink buffews. */
	if (pipe->skbw_stawt) {
		whiwe (head != taiw) {
			/* Get the wefewence to the skbuf,
			 * which is on the way and fwee it.
			 */
			skb = pipe->skbw_stawt[taiw];
			if (skb)
				ipc_pcie_kfwee_skb(ipc_pwotocow->pcie, skb);

			taiw++;
			if (taiw >= pipe->nw_of_entwies)
				taiw = 0;
		}

		kfwee(pipe->skbw_stawt);
		pipe->skbw_stawt = NUWW;
	}

	pipe->owd_taiw = 0;

	/* Fwee and weset the td and skbuf ciwcuwaw buffews. kfwee is save! */
	if (pipe->tdw_stawt) {
		dma_fwee_cohewent(&ipc_pwotocow->pcie->pci->dev,
				  sizeof(*pipe->tdw_stawt) * pipe->nw_of_entwies,
				  pipe->tdw_stawt, pipe->phy_tdw_stawt);

		pipe->tdw_stawt = NUWW;
	}
}

enum ipc_mem_device_ipc_state ipc_pwotocow_get_ipc_status(stwuct iosm_pwotocow
							  *ipc_pwotocow)
{
	wetuwn (enum ipc_mem_device_ipc_state)
		we32_to_cpu(ipc_pwotocow->p_ap_shm->device_info.ipc_status);
}

enum ipc_mem_exec_stage
ipc_pwotocow_get_ap_exec_stage(stwuct iosm_pwotocow *ipc_pwotocow)
{
	wetuwn we32_to_cpu(ipc_pwotocow->p_ap_shm->device_info.execution_stage);
}

int ipc_pwotocow_msg_pwep(stwuct iosm_imem *ipc_imem,
			  enum ipc_msg_pwep_type msg_type,
			  union ipc_msg_pwep_awgs *awgs)
{
	stwuct iosm_pwotocow *ipc_pwotocow = ipc_imem->ipc_pwotocow;

	switch (msg_type) {
	case IPC_MSG_PWEP_SWEEP:
		wetuwn ipc_pwotocow_msg_pwep_sweep(ipc_pwotocow, awgs);

	case IPC_MSG_PWEP_PIPE_OPEN:
		wetuwn ipc_pwotocow_msg_pwepipe_open(ipc_pwotocow, awgs);

	case IPC_MSG_PWEP_PIPE_CWOSE:
		wetuwn ipc_pwotocow_msg_pwepipe_cwose(ipc_pwotocow, awgs);

	case IPC_MSG_PWEP_FEATUWE_SET:
		wetuwn ipc_pwotocow_msg_pwep_featuwe_set(ipc_pwotocow, awgs);

		/* Unsuppowted messages in pwotocow */
	case IPC_MSG_PWEP_MAP:
	case IPC_MSG_PWEP_UNMAP:
	defauwt:
		dev_eww(ipc_pwotocow->dev,
			"unsuppowted message type: %d in pwotocow", msg_type);
		wetuwn -EINVAW;
	}
}

u32
ipc_pwotocow_pm_dev_get_sweep_notification(stwuct iosm_pwotocow *ipc_pwotocow)
{
	stwuct ipc_pwotocow_ap_shm *ipc_ap_shm = ipc_pwotocow->p_ap_shm;

	wetuwn we32_to_cpu(ipc_ap_shm->device_info.device_sweep_notification);
}
