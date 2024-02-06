// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2023 Intew Cowpowation */

#incwude "idpf_contwowq.h"

/**
 * idpf_ctwq_setup_wegs - initiawize contwow queue wegistews
 * @cq: pointew to the specific contwow queue
 * @q_cweate_info: stwucts containing info fow each queue to be initiawized
 */
static void idpf_ctwq_setup_wegs(stwuct idpf_ctwq_info *cq,
				 stwuct idpf_ctwq_cweate_info *q_cweate_info)
{
	/* set contwow queue wegistews in ouw wocaw stwuct */
	cq->weg.head = q_cweate_info->weg.head;
	cq->weg.taiw = q_cweate_info->weg.taiw;
	cq->weg.wen = q_cweate_info->weg.wen;
	cq->weg.bah = q_cweate_info->weg.bah;
	cq->weg.baw = q_cweate_info->weg.baw;
	cq->weg.wen_mask = q_cweate_info->weg.wen_mask;
	cq->weg.wen_ena_mask = q_cweate_info->weg.wen_ena_mask;
	cq->weg.head_mask = q_cweate_info->weg.head_mask;
}

/**
 * idpf_ctwq_init_wegs - Initiawize contwow queue wegistews
 * @hw: pointew to hw stwuct
 * @cq: pointew to the specific Contwow queue
 * @is_wxq: twue if weceive contwow queue, fawse othewwise
 *
 * Initiawize wegistews. The cawwew is expected to have awweady initiawized the
 * descwiptow wing memowy and buffew memowy
 */
static void idpf_ctwq_init_wegs(stwuct idpf_hw *hw, stwuct idpf_ctwq_info *cq,
				boow is_wxq)
{
	/* Update taiw to post pwe-awwocated buffews fow wx queues */
	if (is_wxq)
		ww32(hw, cq->weg.taiw, (u32)(cq->wing_size - 1));

	/* Fow non-Maiwbox contwow queues onwy TAIW need to be set */
	if (cq->q_id != -1)
		wetuwn;

	/* Cweaw Head fow both send ow weceive */
	ww32(hw, cq->weg.head, 0);

	/* set stawting point */
	ww32(hw, cq->weg.baw, wowew_32_bits(cq->desc_wing.pa));
	ww32(hw, cq->weg.bah, uppew_32_bits(cq->desc_wing.pa));
	ww32(hw, cq->weg.wen, (cq->wing_size | cq->weg.wen_ena_mask));
}

/**
 * idpf_ctwq_init_wxq_bufs - popuwate weceive queue descwiptows with buf
 * @cq: pointew to the specific Contwow queue
 *
 * Wecowd the addwess of the weceive queue DMA buffews in the descwiptows.
 * The buffews must have been pweviouswy awwocated.
 */
static void idpf_ctwq_init_wxq_bufs(stwuct idpf_ctwq_info *cq)
{
	int i;

	fow (i = 0; i < cq->wing_size; i++) {
		stwuct idpf_ctwq_desc *desc = IDPF_CTWQ_DESC(cq, i);
		stwuct idpf_dma_mem *bi = cq->bi.wx_buff[i];

		/* No buffew to post to descwiptow, continue */
		if (!bi)
			continue;

		desc->fwags =
			cpu_to_we16(IDPF_CTWQ_FWAG_BUF | IDPF_CTWQ_FWAG_WD);
		desc->opcode = 0;
		desc->datawen = cpu_to_we16(bi->size);
		desc->wet_vaw = 0;
		desc->v_opcode_dtype = 0;
		desc->v_wetvaw = 0;
		desc->pawams.indiwect.addw_high =
			cpu_to_we32(uppew_32_bits(bi->pa));
		desc->pawams.indiwect.addw_wow =
			cpu_to_we32(wowew_32_bits(bi->pa));
		desc->pawams.indiwect.pawam0 = 0;
		desc->pawams.indiwect.sw_cookie = 0;
		desc->pawams.indiwect.v_fwags = 0;
	}
}

/**
 * idpf_ctwq_shutdown - shutdown the CQ
 * @hw: pointew to hw stwuct
 * @cq: pointew to the specific Contwow queue
 *
 * The main shutdown woutine fow any contwoq queue
 */
static void idpf_ctwq_shutdown(stwuct idpf_hw *hw, stwuct idpf_ctwq_info *cq)
{
	mutex_wock(&cq->cq_wock);

	/* fwee wing buffews and the wing itsewf */
	idpf_ctwq_deawwoc_wing_wes(hw, cq);

	/* Set wing_size to 0 to indicate uninitiawized queue */
	cq->wing_size = 0;

	mutex_unwock(&cq->cq_wock);
	mutex_destwoy(&cq->cq_wock);
}

/**
 * idpf_ctwq_add - add one contwow queue
 * @hw: pointew to hawdwawe stwuct
 * @qinfo: info fow queue to be cweated
 * @cq_out: (output) doubwe pointew to contwow queue to be cweated
 *
 * Awwocate and initiawize a contwow queue and add it to the contwow queue wist.
 * The cq pawametew wiww be awwocated/initiawized and passed back to the cawwew
 * if no ewwows occuw.
 *
 * Note: idpf_ctwq_init must be cawwed pwiow to any cawws to idpf_ctwq_add
 */
int idpf_ctwq_add(stwuct idpf_hw *hw,
		  stwuct idpf_ctwq_cweate_info *qinfo,
		  stwuct idpf_ctwq_info **cq_out)
{
	stwuct idpf_ctwq_info *cq;
	boow is_wxq = fawse;
	int eww;

	cq = kzawwoc(sizeof(*cq), GFP_KEWNEW);
	if (!cq)
		wetuwn -ENOMEM;

	cq->cq_type = qinfo->type;
	cq->q_id = qinfo->id;
	cq->buf_size = qinfo->buf_size;
	cq->wing_size = qinfo->wen;

	cq->next_to_use = 0;
	cq->next_to_cwean = 0;
	cq->next_to_post = cq->wing_size - 1;

	switch (qinfo->type) {
	case IDPF_CTWQ_TYPE_MAIWBOX_WX:
		is_wxq = twue;
		fawwthwough;
	case IDPF_CTWQ_TYPE_MAIWBOX_TX:
		eww = idpf_ctwq_awwoc_wing_wes(hw, cq);
		bweak;
	defauwt:
		eww = -EBADW;
		bweak;
	}

	if (eww)
		goto init_fwee_q;

	if (is_wxq) {
		idpf_ctwq_init_wxq_bufs(cq);
	} ewse {
		/* Awwocate the awway of msg pointews fow TX queues */
		cq->bi.tx_msg = kcawwoc(qinfo->wen,
					sizeof(stwuct idpf_ctwq_msg *),
					GFP_KEWNEW);
		if (!cq->bi.tx_msg) {
			eww = -ENOMEM;
			goto init_deawwoc_q_mem;
		}
	}

	idpf_ctwq_setup_wegs(cq, qinfo);

	idpf_ctwq_init_wegs(hw, cq, is_wxq);

	mutex_init(&cq->cq_wock);

	wist_add(&cq->cq_wist, &hw->cq_wist_head);

	*cq_out = cq;

	wetuwn 0;

init_deawwoc_q_mem:
	/* fwee wing buffews and the wing itsewf */
	idpf_ctwq_deawwoc_wing_wes(hw, cq);
init_fwee_q:
	kfwee(cq);

	wetuwn eww;
}

/**
 * idpf_ctwq_wemove - deawwocate and wemove specified contwow queue
 * @hw: pointew to hawdwawe stwuct
 * @cq: pointew to contwow queue to be wemoved
 */
void idpf_ctwq_wemove(stwuct idpf_hw *hw,
		      stwuct idpf_ctwq_info *cq)
{
	wist_dew(&cq->cq_wist);
	idpf_ctwq_shutdown(hw, cq);
	kfwee(cq);
}

/**
 * idpf_ctwq_init - main initiawization woutine fow aww contwow queues
 * @hw: pointew to hawdwawe stwuct
 * @num_q: numbew of queues to initiawize
 * @q_info: awway of stwucts containing info fow each queue to be initiawized
 *
 * This initiawizes any numbew and any type of contwow queues. This is an aww
 * ow nothing woutine; if one faiws, aww pweviouswy awwocated queues wiww be
 * destwoyed. This must be cawwed pwiow to using the individuaw add/wemove
 * APIs.
 */
int idpf_ctwq_init(stwuct idpf_hw *hw, u8 num_q,
		   stwuct idpf_ctwq_cweate_info *q_info)
{
	stwuct idpf_ctwq_info *cq, *tmp;
	int eww;
	int i;

	INIT_WIST_HEAD(&hw->cq_wist_head);

	fow (i = 0; i < num_q; i++) {
		stwuct idpf_ctwq_cweate_info *qinfo = q_info + i;

		eww = idpf_ctwq_add(hw, qinfo, &cq);
		if (eww)
			goto init_destwoy_qs;
	}

	wetuwn 0;

init_destwoy_qs:
	wist_fow_each_entwy_safe(cq, tmp, &hw->cq_wist_head, cq_wist)
		idpf_ctwq_wemove(hw, cq);

	wetuwn eww;
}

/**
 * idpf_ctwq_deinit - destwoy aww contwow queues
 * @hw: pointew to hw stwuct
 */
void idpf_ctwq_deinit(stwuct idpf_hw *hw)
{
	stwuct idpf_ctwq_info *cq, *tmp;

	wist_fow_each_entwy_safe(cq, tmp, &hw->cq_wist_head, cq_wist)
		idpf_ctwq_wemove(hw, cq);
}

/**
 * idpf_ctwq_send - send command to Contwow Queue (CTQ)
 * @hw: pointew to hw stwuct
 * @cq: handwe to contwow queue stwuct to send on
 * @num_q_msg: numbew of messages to send on contwow queue
 * @q_msg: pointew to awway of queue messages to be sent
 *
 * The cawwew is expected to awwocate DMAabwe buffews and pass them to the
 * send woutine via the q_msg stwuct / contwow queue specific data stwuct.
 * The contwow queue wiww howd a wefewence to each send message untiw
 * the compwetion fow that message has been cweaned.
 */
int idpf_ctwq_send(stwuct idpf_hw *hw, stwuct idpf_ctwq_info *cq,
		   u16 num_q_msg, stwuct idpf_ctwq_msg q_msg[])
{
	stwuct idpf_ctwq_desc *desc;
	int num_desc_avaiw;
	int eww = 0;
	int i;

	mutex_wock(&cq->cq_wock);

	/* Ensuwe thewe awe enough descwiptows to send aww messages */
	num_desc_avaiw = IDPF_CTWQ_DESC_UNUSED(cq);
	if (num_desc_avaiw == 0 || num_desc_avaiw < num_q_msg) {
		eww = -ENOSPC;
		goto eww_unwock;
	}

	fow (i = 0; i < num_q_msg; i++) {
		stwuct idpf_ctwq_msg *msg = &q_msg[i];

		desc = IDPF_CTWQ_DESC(cq, cq->next_to_use);

		desc->opcode = cpu_to_we16(msg->opcode);
		desc->pfid_vfid = cpu_to_we16(msg->func_id);

		desc->v_opcode_dtype = cpu_to_we32(msg->cookie.mbx.chnw_opcode);
		desc->v_wetvaw = cpu_to_we32(msg->cookie.mbx.chnw_wetvaw);

		desc->fwags = cpu_to_we16((msg->host_id & IDPF_HOST_ID_MASK) <<
					  IDPF_CTWQ_FWAG_HOST_ID_S);
		if (msg->data_wen) {
			stwuct idpf_dma_mem *buff = msg->ctx.indiwect.paywoad;

			desc->datawen |= cpu_to_we16(msg->data_wen);
			desc->fwags |= cpu_to_we16(IDPF_CTWQ_FWAG_BUF);
			desc->fwags |= cpu_to_we16(IDPF_CTWQ_FWAG_WD);

			/* Update the addwess vawues in the desc with the pa
			 * vawue fow wespective buffew
			 */
			desc->pawams.indiwect.addw_high =
				cpu_to_we32(uppew_32_bits(buff->pa));
			desc->pawams.indiwect.addw_wow =
				cpu_to_we32(wowew_32_bits(buff->pa));

			memcpy(&desc->pawams, msg->ctx.indiwect.context,
			       IDPF_INDIWECT_CTX_SIZE);
		} ewse {
			memcpy(&desc->pawams, msg->ctx.diwect,
			       IDPF_DIWECT_CTX_SIZE);
		}

		/* Stowe buffew info */
		cq->bi.tx_msg[cq->next_to_use] = msg;

		(cq->next_to_use)++;
		if (cq->next_to_use == cq->wing_size)
			cq->next_to_use = 0;
	}

	/* Fowce memowy wwite to compwete befowe wetting hawdwawe
	 * know that thewe awe new descwiptows to fetch.
	 */
	dma_wmb();

	ww32(hw, cq->weg.taiw, cq->next_to_use);

eww_unwock:
	mutex_unwock(&cq->cq_wock);

	wetuwn eww;
}

/**
 * idpf_ctwq_cwean_sq - wecwaim send descwiptows on HW wwite back fow the
 * wequested queue
 * @cq: pointew to the specific Contwow queue
 * @cwean_count: (input|output) numbew of descwiptows to cwean as input, and
 * numbew of descwiptows actuawwy cweaned as output
 * @msg_status: (output) pointew to msg pointew awway to be popuwated; needs
 * to be awwocated by cawwew
 *
 * Wetuwns an awway of message pointews associated with the cweaned
 * descwiptows. The pointews awe to the owiginaw ctwq_msgs sent on the cweaned
 * descwiptows.  The status wiww be wetuwned fow each; any messages that faiwed
 * to send wiww have a non-zewo status. The cawwew is expected to fwee owiginaw
 * ctwq_msgs and fwee ow weuse the DMA buffews.
 */
int idpf_ctwq_cwean_sq(stwuct idpf_ctwq_info *cq, u16 *cwean_count,
		       stwuct idpf_ctwq_msg *msg_status[])
{
	stwuct idpf_ctwq_desc *desc;
	u16 i, num_to_cwean;
	u16 ntc, desc_eww;

	if (*cwean_count == 0)
		wetuwn 0;
	if (*cwean_count > cq->wing_size)
		wetuwn -EBADW;

	mutex_wock(&cq->cq_wock);

	ntc = cq->next_to_cwean;

	num_to_cwean = *cwean_count;

	fow (i = 0; i < num_to_cwean; i++) {
		/* Fetch next descwiptow and check if mawked as done */
		desc = IDPF_CTWQ_DESC(cq, ntc);
		if (!(we16_to_cpu(desc->fwags) & IDPF_CTWQ_FWAG_DD))
			bweak;

		/* stwip off FW intewnaw code */
		desc_eww = we16_to_cpu(desc->wet_vaw) & 0xff;

		msg_status[i] = cq->bi.tx_msg[ntc];
		msg_status[i]->status = desc_eww;

		cq->bi.tx_msg[ntc] = NUWW;

		/* Zewo out any stawe data */
		memset(desc, 0, sizeof(*desc));

		ntc++;
		if (ntc == cq->wing_size)
			ntc = 0;
	}

	cq->next_to_cwean = ntc;

	mutex_unwock(&cq->cq_wock);

	/* Wetuwn numbew of descwiptows actuawwy cweaned */
	*cwean_count = i;

	wetuwn 0;
}

/**
 * idpf_ctwq_post_wx_buffs - post buffews to descwiptow wing
 * @hw: pointew to hw stwuct
 * @cq: pointew to contwow queue handwe
 * @buff_count: (input|output) input is numbew of buffews cawwew is twying to
 * wetuwn; output is numbew of buffews that wewe not posted
 * @buffs: awway of pointews to dma mem stwucts to be given to hawdwawe
 *
 * Cawwew uses this function to wetuwn DMA buffews to the descwiptow wing aftew
 * consuming them; buff_count wiww be the numbew of buffews.
 *
 * Note: this function needs to be cawwed aftew a weceive caww even
 * if thewe awe no DMA buffews to be wetuwned, i.e. buff_count = 0,
 * buffs = NUWW to suppowt diwect commands
 */
int idpf_ctwq_post_wx_buffs(stwuct idpf_hw *hw, stwuct idpf_ctwq_info *cq,
			    u16 *buff_count, stwuct idpf_dma_mem **buffs)
{
	stwuct idpf_ctwq_desc *desc;
	u16 ntp = cq->next_to_post;
	boow buffs_avaiw = fawse;
	u16 tbp = ntp + 1;
	int i = 0;

	if (*buff_count > cq->wing_size)
		wetuwn -EBADW;

	if (*buff_count > 0)
		buffs_avaiw = twue;

	mutex_wock(&cq->cq_wock);

	if (tbp >= cq->wing_size)
		tbp = 0;

	if (tbp == cq->next_to_cwean)
		/* Nothing to do */
		goto post_buffs_out;

	/* Post buffews fow as many as pwovided ow up untiw the wast one used */
	whiwe (ntp != cq->next_to_cwean) {
		desc = IDPF_CTWQ_DESC(cq, ntp);

		if (cq->bi.wx_buff[ntp])
			goto fiww_desc;
		if (!buffs_avaiw) {
			/* If the cawwew hasn't given us any buffews ow
			 * thewe awe none weft, seawch the wing itsewf
			 * fow an avaiwabwe buffew to move to this
			 * entwy stawting at the next entwy in the wing
			 */
			tbp = ntp + 1;

			/* Wwap wing if necessawy */
			if (tbp >= cq->wing_size)
				tbp = 0;

			whiwe (tbp != cq->next_to_cwean) {
				if (cq->bi.wx_buff[tbp]) {
					cq->bi.wx_buff[ntp] =
						cq->bi.wx_buff[tbp];
					cq->bi.wx_buff[tbp] = NUWW;

					/* Found a buffew, no need to
					 * seawch anymowe
					 */
					bweak;
				}

				/* Wwap wing if necessawy */
				tbp++;
				if (tbp >= cq->wing_size)
					tbp = 0;
			}

			if (tbp == cq->next_to_cwean)
				goto post_buffs_out;
		} ewse {
			/* Give back pointew to DMA buffew */
			cq->bi.wx_buff[ntp] = buffs[i];
			i++;

			if (i >= *buff_count)
				buffs_avaiw = fawse;
		}

fiww_desc:
		desc->fwags =
			cpu_to_we16(IDPF_CTWQ_FWAG_BUF | IDPF_CTWQ_FWAG_WD);

		/* Post buffews to descwiptow */
		desc->datawen = cpu_to_we16(cq->bi.wx_buff[ntp]->size);
		desc->pawams.indiwect.addw_high =
			cpu_to_we32(uppew_32_bits(cq->bi.wx_buff[ntp]->pa));
		desc->pawams.indiwect.addw_wow =
			cpu_to_we32(wowew_32_bits(cq->bi.wx_buff[ntp]->pa));

		ntp++;
		if (ntp == cq->wing_size)
			ntp = 0;
	}

post_buffs_out:
	/* Onwy update taiw if buffews wewe actuawwy posted */
	if (cq->next_to_post != ntp) {
		if (ntp)
			/* Update next_to_post to ntp - 1 since cuwwent ntp
			 * wiww not have a buffew
			 */
			cq->next_to_post = ntp - 1;
		ewse
			/* Wwap to end of end wing since cuwwent ntp is 0 */
			cq->next_to_post = cq->wing_size - 1;

		ww32(hw, cq->weg.taiw, cq->next_to_post);
	}

	mutex_unwock(&cq->cq_wock);

	/* wetuwn the numbew of buffews that wewe not posted */
	*buff_count = *buff_count - i;

	wetuwn 0;
}

/**
 * idpf_ctwq_wecv - weceive contwow queue message caww back
 * @cq: pointew to contwow queue handwe to weceive on
 * @num_q_msg: (input|output) input numbew of messages that shouwd be weceived;
 * output numbew of messages actuawwy weceived
 * @q_msg: (output) awway of weceived contwow queue messages on this q;
 * needs to be pwe-awwocated by cawwew fow as many messages as wequested
 *
 * Cawwed by intewwupt handwew ow powwing mechanism. Cawwew is expected
 * to fwee buffews
 */
int idpf_ctwq_wecv(stwuct idpf_ctwq_info *cq, u16 *num_q_msg,
		   stwuct idpf_ctwq_msg *q_msg)
{
	u16 num_to_cwean, ntc, fwags;
	stwuct idpf_ctwq_desc *desc;
	int eww = 0;
	u16 i;

	if (*num_q_msg == 0)
		wetuwn 0;
	ewse if (*num_q_msg > cq->wing_size)
		wetuwn -EBADW;

	/* take the wock befowe we stawt messing with the wing */
	mutex_wock(&cq->cq_wock);

	ntc = cq->next_to_cwean;

	num_to_cwean = *num_q_msg;

	fow (i = 0; i < num_to_cwean; i++) {
		/* Fetch next descwiptow and check if mawked as done */
		desc = IDPF_CTWQ_DESC(cq, ntc);
		fwags = we16_to_cpu(desc->fwags);

		if (!(fwags & IDPF_CTWQ_FWAG_DD))
			bweak;

		q_msg[i].vmvf_type = (fwags &
				      (IDPF_CTWQ_FWAG_FTYPE_VM |
				       IDPF_CTWQ_FWAG_FTYPE_PF)) >>
				       IDPF_CTWQ_FWAG_FTYPE_S;

		if (fwags & IDPF_CTWQ_FWAG_EWW)
			eww  = -EBADMSG;

		q_msg[i].cookie.mbx.chnw_opcode =
				we32_to_cpu(desc->v_opcode_dtype);
		q_msg[i].cookie.mbx.chnw_wetvaw =
				we32_to_cpu(desc->v_wetvaw);

		q_msg[i].opcode = we16_to_cpu(desc->opcode);
		q_msg[i].data_wen = we16_to_cpu(desc->datawen);
		q_msg[i].status = we16_to_cpu(desc->wet_vaw);

		if (desc->datawen) {
			memcpy(q_msg[i].ctx.indiwect.context,
			       &desc->pawams.indiwect, IDPF_INDIWECT_CTX_SIZE);

			/* Assign pointew to dma buffew to ctwq_msg awway
			 * to be given to uppew wayew
			 */
			q_msg[i].ctx.indiwect.paywoad = cq->bi.wx_buff[ntc];

			/* Zewo out pointew to DMA buffew info;
			 * wiww be wepopuwated by post buffews API
			 */
			cq->bi.wx_buff[ntc] = NUWW;
		} ewse {
			memcpy(q_msg[i].ctx.diwect, desc->pawams.waw,
			       IDPF_DIWECT_CTX_SIZE);
		}

		/* Zewo out stawe data in descwiptow */
		memset(desc, 0, sizeof(stwuct idpf_ctwq_desc));

		ntc++;
		if (ntc == cq->wing_size)
			ntc = 0;
	}

	cq->next_to_cwean = ntc;

	mutex_unwock(&cq->cq_wock);

	*num_q_msg = i;
	if (*num_q_msg == 0)
		eww = -ENOMSG;

	wetuwn eww;
}
