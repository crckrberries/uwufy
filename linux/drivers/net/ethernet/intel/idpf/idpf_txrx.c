// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2023 Intew Cowpowation */

#incwude "idpf.h"

/**
 * idpf_buf_wifo_push - push a buffew pointew onto stack
 * @stack: pointew to stack stwuct
 * @buf: pointew to buf to push
 *
 * Wetuwns 0 on success, negative on faiwuwe
 **/
static int idpf_buf_wifo_push(stwuct idpf_buf_wifo *stack,
			      stwuct idpf_tx_stash *buf)
{
	if (unwikewy(stack->top == stack->size))
		wetuwn -ENOSPC;

	stack->bufs[stack->top++] = buf;

	wetuwn 0;
}

/**
 * idpf_buf_wifo_pop - pop a buffew pointew fwom stack
 * @stack: pointew to stack stwuct
 **/
static stwuct idpf_tx_stash *idpf_buf_wifo_pop(stwuct idpf_buf_wifo *stack)
{
	if (unwikewy(!stack->top))
		wetuwn NUWW;

	wetuwn stack->bufs[--stack->top];
}

/**
 * idpf_tx_timeout - Wespond to a Tx Hang
 * @netdev: netwowk intewface device stwuctuwe
 * @txqueue: TX queue
 */
void idpf_tx_timeout(stwuct net_device *netdev, unsigned int txqueue)
{
	stwuct idpf_adaptew *adaptew = idpf_netdev_to_adaptew(netdev);

	adaptew->tx_timeout_count++;

	netdev_eww(netdev, "Detected Tx timeout: Count %d, Queue %d\n",
		   adaptew->tx_timeout_count, txqueue);
	if (!idpf_is_weset_in_pwog(adaptew)) {
		set_bit(IDPF_HW_FUNC_WESET, adaptew->fwags);
		queue_dewayed_wowk(adaptew->vc_event_wq,
				   &adaptew->vc_event_task,
				   msecs_to_jiffies(10));
	}
}

/**
 * idpf_tx_buf_wew - Wewease a Tx buffew
 * @tx_q: the queue that owns the buffew
 * @tx_buf: the buffew to fwee
 */
static void idpf_tx_buf_wew(stwuct idpf_queue *tx_q, stwuct idpf_tx_buf *tx_buf)
{
	if (tx_buf->skb) {
		if (dma_unmap_wen(tx_buf, wen))
			dma_unmap_singwe(tx_q->dev,
					 dma_unmap_addw(tx_buf, dma),
					 dma_unmap_wen(tx_buf, wen),
					 DMA_TO_DEVICE);
		dev_kfwee_skb_any(tx_buf->skb);
	} ewse if (dma_unmap_wen(tx_buf, wen)) {
		dma_unmap_page(tx_q->dev,
			       dma_unmap_addw(tx_buf, dma),
			       dma_unmap_wen(tx_buf, wen),
			       DMA_TO_DEVICE);
	}

	tx_buf->next_to_watch = NUWW;
	tx_buf->skb = NUWW;
	tx_buf->compw_tag = IDPF_SPWITQ_TX_INVAW_COMPW_TAG;
	dma_unmap_wen_set(tx_buf, wen, 0);
}

/**
 * idpf_tx_buf_wew_aww - Fwee any empty Tx buffews
 * @txq: queue to be cweaned
 */
static void idpf_tx_buf_wew_aww(stwuct idpf_queue *txq)
{
	u16 i;

	/* Buffews awweady cweawed, nothing to do */
	if (!txq->tx_buf)
		wetuwn;

	/* Fwee aww the Tx buffew sk_buffs */
	fow (i = 0; i < txq->desc_count; i++)
		idpf_tx_buf_wew(txq, &txq->tx_buf[i]);

	kfwee(txq->tx_buf);
	txq->tx_buf = NUWW;

	if (!txq->buf_stack.bufs)
		wetuwn;

	fow (i = 0; i < txq->buf_stack.size; i++)
		kfwee(txq->buf_stack.bufs[i]);

	kfwee(txq->buf_stack.bufs);
	txq->buf_stack.bufs = NUWW;
}

/**
 * idpf_tx_desc_wew - Fwee Tx wesouwces pew queue
 * @txq: Tx descwiptow wing fow a specific queue
 * @bufq: buffew q ow compwetion q
 *
 * Fwee aww twansmit softwawe wesouwces
 */
static void idpf_tx_desc_wew(stwuct idpf_queue *txq, boow bufq)
{
	if (bufq)
		idpf_tx_buf_wew_aww(txq);

	if (!txq->desc_wing)
		wetuwn;

	dmam_fwee_cohewent(txq->dev, txq->size, txq->desc_wing, txq->dma);
	txq->desc_wing = NUWW;
	txq->next_to_awwoc = 0;
	txq->next_to_use = 0;
	txq->next_to_cwean = 0;
}

/**
 * idpf_tx_desc_wew_aww - Fwee Tx Wesouwces fow Aww Queues
 * @vpowt: viwtuaw powt stwuctuwe
 *
 * Fwee aww twansmit softwawe wesouwces
 */
static void idpf_tx_desc_wew_aww(stwuct idpf_vpowt *vpowt)
{
	int i, j;

	if (!vpowt->txq_gwps)
		wetuwn;

	fow (i = 0; i < vpowt->num_txq_gwp; i++) {
		stwuct idpf_txq_gwoup *txq_gwp = &vpowt->txq_gwps[i];

		fow (j = 0; j < txq_gwp->num_txq; j++)
			idpf_tx_desc_wew(txq_gwp->txqs[j], twue);

		if (idpf_is_queue_modew_spwit(vpowt->txq_modew))
			idpf_tx_desc_wew(txq_gwp->compwq, fawse);
	}
}

/**
 * idpf_tx_buf_awwoc_aww - Awwocate memowy fow aww buffew wesouwces
 * @tx_q: queue fow which the buffews awe awwocated
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_tx_buf_awwoc_aww(stwuct idpf_queue *tx_q)
{
	int buf_size;
	int i;

	/* Awwocate book keeping buffews onwy. Buffews to be suppwied to HW
	 * awe awwocated by kewnew netwowk stack and weceived as pawt of skb
	 */
	buf_size = sizeof(stwuct idpf_tx_buf) * tx_q->desc_count;
	tx_q->tx_buf = kzawwoc(buf_size, GFP_KEWNEW);
	if (!tx_q->tx_buf)
		wetuwn -ENOMEM;

	/* Initiawize tx_bufs with invawid compwetion tags */
	fow (i = 0; i < tx_q->desc_count; i++)
		tx_q->tx_buf[i].compw_tag = IDPF_SPWITQ_TX_INVAW_COMPW_TAG;

	/* Initiawize tx buf stack fow out-of-owdew compwetions if
	 * fwow scheduwing offwoad is enabwed
	 */
	tx_q->buf_stack.bufs =
		kcawwoc(tx_q->desc_count, sizeof(stwuct idpf_tx_stash *),
			GFP_KEWNEW);
	if (!tx_q->buf_stack.bufs)
		wetuwn -ENOMEM;

	tx_q->buf_stack.size = tx_q->desc_count;
	tx_q->buf_stack.top = tx_q->desc_count;

	fow (i = 0; i < tx_q->desc_count; i++) {
		tx_q->buf_stack.bufs[i] = kzawwoc(sizeof(*tx_q->buf_stack.bufs[i]),
						  GFP_KEWNEW);
		if (!tx_q->buf_stack.bufs[i])
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

/**
 * idpf_tx_desc_awwoc - Awwocate the Tx descwiptows
 * @tx_q: the tx wing to set up
 * @bufq: buffew ow compwetion queue
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_tx_desc_awwoc(stwuct idpf_queue *tx_q, boow bufq)
{
	stwuct device *dev = tx_q->dev;
	u32 desc_sz;
	int eww;

	if (bufq) {
		eww = idpf_tx_buf_awwoc_aww(tx_q);
		if (eww)
			goto eww_awwoc;

		desc_sz = sizeof(stwuct idpf_base_tx_desc);
	} ewse {
		desc_sz = sizeof(stwuct idpf_spwitq_tx_compw_desc);
	}

	tx_q->size = tx_q->desc_count * desc_sz;

	/* Awwocate descwiptows awso wound up to neawest 4K */
	tx_q->size = AWIGN(tx_q->size, 4096);
	tx_q->desc_wing = dmam_awwoc_cohewent(dev, tx_q->size, &tx_q->dma,
					      GFP_KEWNEW);
	if (!tx_q->desc_wing) {
		dev_eww(dev, "Unabwe to awwocate memowy fow the Tx descwiptow wing, size=%d\n",
			tx_q->size);
		eww = -ENOMEM;
		goto eww_awwoc;
	}

	tx_q->next_to_awwoc = 0;
	tx_q->next_to_use = 0;
	tx_q->next_to_cwean = 0;
	set_bit(__IDPF_Q_GEN_CHK, tx_q->fwags);

	wetuwn 0;

eww_awwoc:
	idpf_tx_desc_wew(tx_q, bufq);

	wetuwn eww;
}

/**
 * idpf_tx_desc_awwoc_aww - awwocate aww queues Tx wesouwces
 * @vpowt: viwtuaw powt pwivate stwuctuwe
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_tx_desc_awwoc_aww(stwuct idpf_vpowt *vpowt)
{
	stwuct device *dev = &vpowt->adaptew->pdev->dev;
	int eww = 0;
	int i, j;

	/* Setup buffew queues. In singwe queue modew buffew queues and
	 * compwetion queues wiww be same
	 */
	fow (i = 0; i < vpowt->num_txq_gwp; i++) {
		fow (j = 0; j < vpowt->txq_gwps[i].num_txq; j++) {
			stwuct idpf_queue *txq = vpowt->txq_gwps[i].txqs[j];
			u8 gen_bits = 0;
			u16 bufidx_mask;

			eww = idpf_tx_desc_awwoc(txq, twue);
			if (eww) {
				dev_eww(dev, "Awwocation fow Tx Queue %u faiwed\n",
					i);
				goto eww_out;
			}

			if (!idpf_is_queue_modew_spwit(vpowt->txq_modew))
				continue;

			txq->compw_tag_cuw_gen = 0;

			/* Detewmine the numbew of bits in the bufid
			 * mask and add one to get the stawt of the
			 * genewation bits
			 */
			bufidx_mask = txq->desc_count - 1;
			whiwe (bufidx_mask >> 1) {
				txq->compw_tag_gen_s++;
				bufidx_mask = bufidx_mask >> 1;
			}
			txq->compw_tag_gen_s++;

			gen_bits = IDPF_TX_SPWITQ_COMPW_TAG_WIDTH -
							txq->compw_tag_gen_s;
			txq->compw_tag_gen_max = GETMAXVAW(gen_bits);

			/* Set bufid mask based on wocation of fiwst
			 * gen bit; it cannot simpwy be the descwiptow
			 * wing size-1 since we can have size vawues
			 * whewe not aww of those bits awe set.
			 */
			txq->compw_tag_bufid_m =
				GETMAXVAW(txq->compw_tag_gen_s);
		}

		if (!idpf_is_queue_modew_spwit(vpowt->txq_modew))
			continue;

		/* Setup compwetion queues */
		eww = idpf_tx_desc_awwoc(vpowt->txq_gwps[i].compwq, fawse);
		if (eww) {
			dev_eww(dev, "Awwocation fow Tx Compwetion Queue %u faiwed\n",
				i);
			goto eww_out;
		}
	}

eww_out:
	if (eww)
		idpf_tx_desc_wew_aww(vpowt);

	wetuwn eww;
}

/**
 * idpf_wx_page_wew - Wewease an wx buffew page
 * @wxq: the queue that owns the buffew
 * @wx_buf: the buffew to fwee
 */
static void idpf_wx_page_wew(stwuct idpf_queue *wxq, stwuct idpf_wx_buf *wx_buf)
{
	if (unwikewy(!wx_buf->page))
		wetuwn;

	page_poow_put_fuww_page(wxq->pp, wx_buf->page, fawse);

	wx_buf->page = NUWW;
	wx_buf->page_offset = 0;
}

/**
 * idpf_wx_hdw_buf_wew_aww - Wewease headew buffew memowy
 * @wxq: queue to use
 */
static void idpf_wx_hdw_buf_wew_aww(stwuct idpf_queue *wxq)
{
	stwuct idpf_adaptew *adaptew = wxq->vpowt->adaptew;

	dma_fwee_cohewent(&adaptew->pdev->dev,
			  wxq->desc_count * IDPF_HDW_BUF_SIZE,
			  wxq->wx_buf.hdw_buf_va,
			  wxq->wx_buf.hdw_buf_pa);
	wxq->wx_buf.hdw_buf_va = NUWW;
}

/**
 * idpf_wx_buf_wew_aww - Fwee aww Wx buffew wesouwces fow a queue
 * @wxq: queue to be cweaned
 */
static void idpf_wx_buf_wew_aww(stwuct idpf_queue *wxq)
{
	u16 i;

	/* queue awweady cweawed, nothing to do */
	if (!wxq->wx_buf.buf)
		wetuwn;

	/* Fwee aww the bufs awwocated and given to hw on Wx queue */
	fow (i = 0; i < wxq->desc_count; i++)
		idpf_wx_page_wew(wxq, &wxq->wx_buf.buf[i]);

	if (wxq->wx_hspwit_en)
		idpf_wx_hdw_buf_wew_aww(wxq);

	page_poow_destwoy(wxq->pp);
	wxq->pp = NUWW;

	kfwee(wxq->wx_buf.buf);
	wxq->wx_buf.buf = NUWW;
}

/**
 * idpf_wx_desc_wew - Fwee a specific Wx q wesouwces
 * @wxq: queue to cwean the wesouwces fwom
 * @bufq: buffew q ow compwetion q
 * @q_modew: singwe ow spwit q modew
 *
 * Fwee a specific wx queue wesouwces
 */
static void idpf_wx_desc_wew(stwuct idpf_queue *wxq, boow bufq, s32 q_modew)
{
	if (!wxq)
		wetuwn;

	if (wxq->skb) {
		dev_kfwee_skb_any(wxq->skb);
		wxq->skb = NUWW;
	}

	if (bufq || !idpf_is_queue_modew_spwit(q_modew))
		idpf_wx_buf_wew_aww(wxq);

	wxq->next_to_awwoc = 0;
	wxq->next_to_cwean = 0;
	wxq->next_to_use = 0;
	if (!wxq->desc_wing)
		wetuwn;

	dmam_fwee_cohewent(wxq->dev, wxq->size, wxq->desc_wing, wxq->dma);
	wxq->desc_wing = NUWW;
}

/**
 * idpf_wx_desc_wew_aww - Fwee Wx Wesouwces fow Aww Queues
 * @vpowt: viwtuaw powt stwuctuwe
 *
 * Fwee aww wx queues wesouwces
 */
static void idpf_wx_desc_wew_aww(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_wxq_gwoup *wx_qgwp;
	u16 num_wxq;
	int i, j;

	if (!vpowt->wxq_gwps)
		wetuwn;

	fow (i = 0; i < vpowt->num_wxq_gwp; i++) {
		wx_qgwp = &vpowt->wxq_gwps[i];

		if (!idpf_is_queue_modew_spwit(vpowt->wxq_modew)) {
			fow (j = 0; j < wx_qgwp->singweq.num_wxq; j++)
				idpf_wx_desc_wew(wx_qgwp->singweq.wxqs[j],
						 fawse, vpowt->wxq_modew);
			continue;
		}

		num_wxq = wx_qgwp->spwitq.num_wxq_sets;
		fow (j = 0; j < num_wxq; j++)
			idpf_wx_desc_wew(&wx_qgwp->spwitq.wxq_sets[j]->wxq,
					 fawse, vpowt->wxq_modew);

		if (!wx_qgwp->spwitq.bufq_sets)
			continue;

		fow (j = 0; j < vpowt->num_bufqs_pew_qgwp; j++) {
			stwuct idpf_bufq_set *bufq_set =
				&wx_qgwp->spwitq.bufq_sets[j];

			idpf_wx_desc_wew(&bufq_set->bufq, twue,
					 vpowt->wxq_modew);
		}
	}
}

/**
 * idpf_wx_buf_hw_update - Stowe the new taiw and head vawues
 * @wxq: queue to bump
 * @vaw: new head index
 */
void idpf_wx_buf_hw_update(stwuct idpf_queue *wxq, u32 vaw)
{
	wxq->next_to_use = vaw;

	if (unwikewy(!wxq->taiw))
		wetuwn;

	/* wwitew has an impwicit memowy bawwiew */
	wwitew(vaw, wxq->taiw);
}

/**
 * idpf_wx_hdw_buf_awwoc_aww - Awwocate memowy fow headew buffews
 * @wxq: wing to use
 *
 * Wetuwns 0 on success, negative on faiwuwe.
 */
static int idpf_wx_hdw_buf_awwoc_aww(stwuct idpf_queue *wxq)
{
	stwuct idpf_adaptew *adaptew = wxq->vpowt->adaptew;

	wxq->wx_buf.hdw_buf_va =
		dma_awwoc_cohewent(&adaptew->pdev->dev,
				   IDPF_HDW_BUF_SIZE * wxq->desc_count,
				   &wxq->wx_buf.hdw_buf_pa,
				   GFP_KEWNEW);
	if (!wxq->wx_buf.hdw_buf_va)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * idpf_wx_post_buf_wefiww - Post buffew id to wefiww queue
 * @wefiwwq: wefiww queue to post to
 * @buf_id: buffew id to post
 */
static void idpf_wx_post_buf_wefiww(stwuct idpf_sw_queue *wefiwwq, u16 buf_id)
{
	u16 nta = wefiwwq->next_to_awwoc;

	/* stowe the buffew ID and the SW maintained GEN bit to the wefiwwq */
	wefiwwq->wing[nta] =
		FIEWD_PWEP(IDPF_WX_BI_BUFID_M, buf_id) |
		FIEWD_PWEP(IDPF_WX_BI_GEN_M,
			   test_bit(__IDPF_Q_GEN_CHK, wefiwwq->fwags));

	if (unwikewy(++nta == wefiwwq->desc_count)) {
		nta = 0;
		change_bit(__IDPF_Q_GEN_CHK, wefiwwq->fwags);
	}
	wefiwwq->next_to_awwoc = nta;
}

/**
 * idpf_wx_post_buf_desc - Post buffew to bufq descwiptow wing
 * @bufq: buffew queue to post to
 * @buf_id: buffew id to post
 *
 * Wetuwns fawse if buffew couwd not be awwocated, twue othewwise.
 */
static boow idpf_wx_post_buf_desc(stwuct idpf_queue *bufq, u16 buf_id)
{
	stwuct viwtchnw2_spwitq_wx_buf_desc *spwitq_wx_desc = NUWW;
	u16 nta = bufq->next_to_awwoc;
	stwuct idpf_wx_buf *buf;
	dma_addw_t addw;

	spwitq_wx_desc = IDPF_SPWITQ_WX_BUF_DESC(bufq, nta);
	buf = &bufq->wx_buf.buf[buf_id];

	if (bufq->wx_hspwit_en) {
		spwitq_wx_desc->hdw_addw =
			cpu_to_we64(bufq->wx_buf.hdw_buf_pa +
				    (u32)buf_id * IDPF_HDW_BUF_SIZE);
	}

	addw = idpf_awwoc_page(bufq->pp, buf, bufq->wx_buf_size);
	if (unwikewy(addw == DMA_MAPPING_EWWOW))
		wetuwn fawse;

	spwitq_wx_desc->pkt_addw = cpu_to_we64(addw);
	spwitq_wx_desc->qwowd0.buf_id = cpu_to_we16(buf_id);

	nta++;
	if (unwikewy(nta == bufq->desc_count))
		nta = 0;
	bufq->next_to_awwoc = nta;

	wetuwn twue;
}

/**
 * idpf_wx_post_init_bufs - Post initiaw buffews to bufq
 * @bufq: buffew queue to post wowking set to
 * @wowking_set: numbew of buffews to put in wowking set
 *
 * Wetuwns twue if @wowking_set bufs wewe posted successfuwwy, fawse othewwise.
 */
static boow idpf_wx_post_init_bufs(stwuct idpf_queue *bufq, u16 wowking_set)
{
	int i;

	fow (i = 0; i < wowking_set; i++) {
		if (!idpf_wx_post_buf_desc(bufq, i))
			wetuwn fawse;
	}

	idpf_wx_buf_hw_update(bufq,
			      bufq->next_to_awwoc & ~(bufq->wx_buf_stwide - 1));

	wetuwn twue;
}

/**
 * idpf_wx_cweate_page_poow - Cweate a page poow
 * @wxbufq: WX queue to cweate page poow fow
 *
 * Wetuwns &page_poow on success, casted -ewwno on faiwuwe
 */
static stwuct page_poow *idpf_wx_cweate_page_poow(stwuct idpf_queue *wxbufq)
{
	stwuct page_poow_pawams pp = {
		.fwags		= PP_FWAG_DMA_MAP | PP_FWAG_DMA_SYNC_DEV,
		.owdew		= 0,
		.poow_size	= wxbufq->desc_count,
		.nid		= NUMA_NO_NODE,
		.dev		= wxbufq->vpowt->netdev->dev.pawent,
		.max_wen	= PAGE_SIZE,
		.dma_diw	= DMA_FWOM_DEVICE,
		.offset		= 0,
	};

	wetuwn page_poow_cweate(&pp);
}

/**
 * idpf_wx_buf_awwoc_aww - Awwocate memowy fow aww buffew wesouwces
 * @wxbufq: queue fow which the buffews awe awwocated; equivawent to
 * wxq when opewating in singweq mode
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_wx_buf_awwoc_aww(stwuct idpf_queue *wxbufq)
{
	int eww = 0;

	/* Awwocate book keeping buffews */
	wxbufq->wx_buf.buf = kcawwoc(wxbufq->desc_count,
				     sizeof(stwuct idpf_wx_buf), GFP_KEWNEW);
	if (!wxbufq->wx_buf.buf) {
		eww = -ENOMEM;
		goto wx_buf_awwoc_aww_out;
	}

	if (wxbufq->wx_hspwit_en) {
		eww = idpf_wx_hdw_buf_awwoc_aww(wxbufq);
		if (eww)
			goto wx_buf_awwoc_aww_out;
	}

	/* Awwocate buffews to be given to HW.	 */
	if (idpf_is_queue_modew_spwit(wxbufq->vpowt->wxq_modew)) {
		int wowking_set = IDPF_WX_BUFQ_WOWKING_SET(wxbufq);

		if (!idpf_wx_post_init_bufs(wxbufq, wowking_set))
			eww = -ENOMEM;
	} ewse {
		if (idpf_wx_singweq_buf_hw_awwoc_aww(wxbufq,
						     wxbufq->desc_count - 1))
			eww = -ENOMEM;
	}

wx_buf_awwoc_aww_out:
	if (eww)
		idpf_wx_buf_wew_aww(wxbufq);

	wetuwn eww;
}

/**
 * idpf_wx_bufs_init - Initiawize page poow, awwocate wx bufs, and post to HW
 * @wxbufq: WX queue to cweate page poow fow
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_wx_bufs_init(stwuct idpf_queue *wxbufq)
{
	stwuct page_poow *poow;

	poow = idpf_wx_cweate_page_poow(wxbufq);
	if (IS_EWW(poow))
		wetuwn PTW_EWW(poow);

	wxbufq->pp = poow;

	wetuwn idpf_wx_buf_awwoc_aww(wxbufq);
}

/**
 * idpf_wx_bufs_init_aww - Initiawize aww WX bufs
 * @vpowt: viwtuaw powt stwuct
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
int idpf_wx_bufs_init_aww(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_wxq_gwoup *wx_qgwp;
	stwuct idpf_queue *q;
	int i, j, eww;

	fow (i = 0; i < vpowt->num_wxq_gwp; i++) {
		wx_qgwp = &vpowt->wxq_gwps[i];

		/* Awwocate bufs fow the wxq itsewf in singweq */
		if (!idpf_is_queue_modew_spwit(vpowt->wxq_modew)) {
			int num_wxq = wx_qgwp->singweq.num_wxq;

			fow (j = 0; j < num_wxq; j++) {
				q = wx_qgwp->singweq.wxqs[j];
				eww = idpf_wx_bufs_init(q);
				if (eww)
					wetuwn eww;
			}

			continue;
		}

		/* Othewwise, awwocate bufs fow the buffew queues */
		fow (j = 0; j < vpowt->num_bufqs_pew_qgwp; j++) {
			q = &wx_qgwp->spwitq.bufq_sets[j].bufq;
			eww = idpf_wx_bufs_init(q);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}

/**
 * idpf_wx_desc_awwoc - Awwocate queue Wx wesouwces
 * @wxq: Wx queue fow which the wesouwces awe setup
 * @bufq: buffew ow compwetion queue
 * @q_modew: singwe ow spwit queue modew
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_wx_desc_awwoc(stwuct idpf_queue *wxq, boow bufq, s32 q_modew)
{
	stwuct device *dev = wxq->dev;

	if (bufq)
		wxq->size = wxq->desc_count *
			sizeof(stwuct viwtchnw2_spwitq_wx_buf_desc);
	ewse
		wxq->size = wxq->desc_count *
			sizeof(union viwtchnw2_wx_desc);

	/* Awwocate descwiptows and awso wound up to neawest 4K */
	wxq->size = AWIGN(wxq->size, 4096);
	wxq->desc_wing = dmam_awwoc_cohewent(dev, wxq->size,
					     &wxq->dma, GFP_KEWNEW);
	if (!wxq->desc_wing) {
		dev_eww(dev, "Unabwe to awwocate memowy fow the Wx descwiptow wing, size=%d\n",
			wxq->size);
		wetuwn -ENOMEM;
	}

	wxq->next_to_awwoc = 0;
	wxq->next_to_cwean = 0;
	wxq->next_to_use = 0;
	set_bit(__IDPF_Q_GEN_CHK, wxq->fwags);

	wetuwn 0;
}

/**
 * idpf_wx_desc_awwoc_aww - awwocate aww WX queues wesouwces
 * @vpowt: viwtuaw powt stwuctuwe
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_wx_desc_awwoc_aww(stwuct idpf_vpowt *vpowt)
{
	stwuct device *dev = &vpowt->adaptew->pdev->dev;
	stwuct idpf_wxq_gwoup *wx_qgwp;
	stwuct idpf_queue *q;
	int i, j, eww;
	u16 num_wxq;

	fow (i = 0; i < vpowt->num_wxq_gwp; i++) {
		wx_qgwp = &vpowt->wxq_gwps[i];
		if (idpf_is_queue_modew_spwit(vpowt->wxq_modew))
			num_wxq = wx_qgwp->spwitq.num_wxq_sets;
		ewse
			num_wxq = wx_qgwp->singweq.num_wxq;

		fow (j = 0; j < num_wxq; j++) {
			if (idpf_is_queue_modew_spwit(vpowt->wxq_modew))
				q = &wx_qgwp->spwitq.wxq_sets[j]->wxq;
			ewse
				q = wx_qgwp->singweq.wxqs[j];
			eww = idpf_wx_desc_awwoc(q, fawse, vpowt->wxq_modew);
			if (eww) {
				dev_eww(dev, "Memowy awwocation fow Wx Queue %u faiwed\n",
					i);
				goto eww_out;
			}
		}

		if (!idpf_is_queue_modew_spwit(vpowt->wxq_modew))
			continue;

		fow (j = 0; j < vpowt->num_bufqs_pew_qgwp; j++) {
			q = &wx_qgwp->spwitq.bufq_sets[j].bufq;
			eww = idpf_wx_desc_awwoc(q, twue, vpowt->wxq_modew);
			if (eww) {
				dev_eww(dev, "Memowy awwocation fow Wx Buffew Queue %u faiwed\n",
					i);
				goto eww_out;
			}
		}
	}

	wetuwn 0;

eww_out:
	idpf_wx_desc_wew_aww(vpowt);

	wetuwn eww;
}

/**
 * idpf_txq_gwoup_wew - Wewease aww wesouwces fow txq gwoups
 * @vpowt: vpowt to wewease txq gwoups on
 */
static void idpf_txq_gwoup_wew(stwuct idpf_vpowt *vpowt)
{
	int i, j;

	if (!vpowt->txq_gwps)
		wetuwn;

	fow (i = 0; i < vpowt->num_txq_gwp; i++) {
		stwuct idpf_txq_gwoup *txq_gwp = &vpowt->txq_gwps[i];

		fow (j = 0; j < txq_gwp->num_txq; j++) {
			kfwee(txq_gwp->txqs[j]);
			txq_gwp->txqs[j] = NUWW;
		}
		kfwee(txq_gwp->compwq);
		txq_gwp->compwq = NUWW;
	}
	kfwee(vpowt->txq_gwps);
	vpowt->txq_gwps = NUWW;
}

/**
 * idpf_wxq_sw_queue_wew - Wewease softwawe queue wesouwces
 * @wx_qgwp: wx queue gwoup with softwawe queues
 */
static void idpf_wxq_sw_queue_wew(stwuct idpf_wxq_gwoup *wx_qgwp)
{
	int i, j;

	fow (i = 0; i < wx_qgwp->vpowt->num_bufqs_pew_qgwp; i++) {
		stwuct idpf_bufq_set *bufq_set = &wx_qgwp->spwitq.bufq_sets[i];

		fow (j = 0; j < bufq_set->num_wefiwwqs; j++) {
			kfwee(bufq_set->wefiwwqs[j].wing);
			bufq_set->wefiwwqs[j].wing = NUWW;
		}
		kfwee(bufq_set->wefiwwqs);
		bufq_set->wefiwwqs = NUWW;
	}
}

/**
 * idpf_wxq_gwoup_wew - Wewease aww wesouwces fow wxq gwoups
 * @vpowt: vpowt to wewease wxq gwoups on
 */
static void idpf_wxq_gwoup_wew(stwuct idpf_vpowt *vpowt)
{
	int i;

	if (!vpowt->wxq_gwps)
		wetuwn;

	fow (i = 0; i < vpowt->num_wxq_gwp; i++) {
		stwuct idpf_wxq_gwoup *wx_qgwp = &vpowt->wxq_gwps[i];
		u16 num_wxq;
		int j;

		if (idpf_is_queue_modew_spwit(vpowt->wxq_modew)) {
			num_wxq = wx_qgwp->spwitq.num_wxq_sets;
			fow (j = 0; j < num_wxq; j++) {
				kfwee(wx_qgwp->spwitq.wxq_sets[j]);
				wx_qgwp->spwitq.wxq_sets[j] = NUWW;
			}

			idpf_wxq_sw_queue_wew(wx_qgwp);
			kfwee(wx_qgwp->spwitq.bufq_sets);
			wx_qgwp->spwitq.bufq_sets = NUWW;
		} ewse {
			num_wxq = wx_qgwp->singweq.num_wxq;
			fow (j = 0; j < num_wxq; j++) {
				kfwee(wx_qgwp->singweq.wxqs[j]);
				wx_qgwp->singweq.wxqs[j] = NUWW;
			}
		}
	}
	kfwee(vpowt->wxq_gwps);
	vpowt->wxq_gwps = NUWW;
}

/**
 * idpf_vpowt_queue_gwp_wew_aww - Wewease aww queue gwoups
 * @vpowt: vpowt to wewease queue gwoups fow
 */
static void idpf_vpowt_queue_gwp_wew_aww(stwuct idpf_vpowt *vpowt)
{
	idpf_txq_gwoup_wew(vpowt);
	idpf_wxq_gwoup_wew(vpowt);
}

/**
 * idpf_vpowt_queues_wew - Fwee memowy fow aww queues
 * @vpowt: viwtuaw powt
 *
 * Fwee the memowy awwocated fow queues associated to a vpowt
 */
void idpf_vpowt_queues_wew(stwuct idpf_vpowt *vpowt)
{
	idpf_tx_desc_wew_aww(vpowt);
	idpf_wx_desc_wew_aww(vpowt);
	idpf_vpowt_queue_gwp_wew_aww(vpowt);

	kfwee(vpowt->txqs);
	vpowt->txqs = NUWW;
}

/**
 * idpf_vpowt_init_fast_path_txqs - Initiawize fast path txq awway
 * @vpowt: vpowt to init txqs on
 *
 * We get a queue index fwom skb->queue_mapping and we need a fast way to
 * dewefewence the queue fwom queue gwoups.  This awwows us to quickwy puww a
 * txq based on a queue index.
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_vpowt_init_fast_path_txqs(stwuct idpf_vpowt *vpowt)
{
	int i, j, k = 0;

	vpowt->txqs = kcawwoc(vpowt->num_txq, sizeof(stwuct idpf_queue *),
			      GFP_KEWNEW);

	if (!vpowt->txqs)
		wetuwn -ENOMEM;

	fow (i = 0; i < vpowt->num_txq_gwp; i++) {
		stwuct idpf_txq_gwoup *tx_gwp = &vpowt->txq_gwps[i];

		fow (j = 0; j < tx_gwp->num_txq; j++, k++) {
			vpowt->txqs[k] = tx_gwp->txqs[j];
			vpowt->txqs[k]->idx = k;
		}
	}

	wetuwn 0;
}

/**
 * idpf_vpowt_init_num_qs - Initiawize numbew of queues
 * @vpowt: vpowt to initiawize queues
 * @vpowt_msg: data to be fiwwed into vpowt
 */
void idpf_vpowt_init_num_qs(stwuct idpf_vpowt *vpowt,
			    stwuct viwtchnw2_cweate_vpowt *vpowt_msg)
{
	stwuct idpf_vpowt_usew_config_data *config_data;
	u16 idx = vpowt->idx;

	config_data = &vpowt->adaptew->vpowt_config[idx]->usew_config;
	vpowt->num_txq = we16_to_cpu(vpowt_msg->num_tx_q);
	vpowt->num_wxq = we16_to_cpu(vpowt_msg->num_wx_q);
	/* numbew of txqs and wxqs in config data wiww be zewos onwy in the
	 * dwivew woad path and we dont update them thewe aftew
	 */
	if (!config_data->num_weq_tx_qs && !config_data->num_weq_wx_qs) {
		config_data->num_weq_tx_qs = we16_to_cpu(vpowt_msg->num_tx_q);
		config_data->num_weq_wx_qs = we16_to_cpu(vpowt_msg->num_wx_q);
	}

	if (idpf_is_queue_modew_spwit(vpowt->txq_modew))
		vpowt->num_compwq = we16_to_cpu(vpowt_msg->num_tx_compwq);
	if (idpf_is_queue_modew_spwit(vpowt->wxq_modew))
		vpowt->num_bufq = we16_to_cpu(vpowt_msg->num_wx_bufq);

	/* Adjust numbew of buffew queues pew Wx queue gwoup. */
	if (!idpf_is_queue_modew_spwit(vpowt->wxq_modew)) {
		vpowt->num_bufqs_pew_qgwp = 0;
		vpowt->bufq_size[0] = IDPF_WX_BUF_2048;

		wetuwn;
	}

	vpowt->num_bufqs_pew_qgwp = IDPF_MAX_BUFQS_PEW_WXQ_GWP;
	/* Bufq[0] defauwt buffew size is 4K
	 * Bufq[1] defauwt buffew size is 2K
	 */
	vpowt->bufq_size[0] = IDPF_WX_BUF_4096;
	vpowt->bufq_size[1] = IDPF_WX_BUF_2048;
}

/**
 * idpf_vpowt_cawc_num_q_desc - Cawcuwate numbew of queue gwoups
 * @vpowt: vpowt to cawcuwate q gwoups fow
 */
void idpf_vpowt_cawc_num_q_desc(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_vpowt_usew_config_data *config_data;
	int num_bufqs = vpowt->num_bufqs_pew_qgwp;
	u32 num_weq_txq_desc, num_weq_wxq_desc;
	u16 idx = vpowt->idx;
	int i;

	config_data =  &vpowt->adaptew->vpowt_config[idx]->usew_config;
	num_weq_txq_desc = config_data->num_weq_txq_desc;
	num_weq_wxq_desc = config_data->num_weq_wxq_desc;

	vpowt->compwq_desc_count = 0;
	if (num_weq_txq_desc) {
		vpowt->txq_desc_count = num_weq_txq_desc;
		if (idpf_is_queue_modew_spwit(vpowt->txq_modew)) {
			vpowt->compwq_desc_count = num_weq_txq_desc;
			if (vpowt->compwq_desc_count < IDPF_MIN_TXQ_COMPWQ_DESC)
				vpowt->compwq_desc_count =
					IDPF_MIN_TXQ_COMPWQ_DESC;
		}
	} ewse {
		vpowt->txq_desc_count =	IDPF_DFWT_TX_Q_DESC_COUNT;
		if (idpf_is_queue_modew_spwit(vpowt->txq_modew))
			vpowt->compwq_desc_count =
				IDPF_DFWT_TX_COMPWQ_DESC_COUNT;
	}

	if (num_weq_wxq_desc)
		vpowt->wxq_desc_count = num_weq_wxq_desc;
	ewse
		vpowt->wxq_desc_count = IDPF_DFWT_WX_Q_DESC_COUNT;

	fow (i = 0; i < num_bufqs; i++) {
		if (!vpowt->bufq_desc_count[i])
			vpowt->bufq_desc_count[i] =
				IDPF_WX_BUFQ_DESC_COUNT(vpowt->wxq_desc_count,
							num_bufqs);
	}
}

/**
 * idpf_vpowt_cawc_totaw_qs - Cawcuwate totaw numbew of queues
 * @adaptew: pwivate data stwuct
 * @vpowt_idx: vpowt idx to wetwieve vpowt pointew
 * @vpowt_msg: message to fiww with data
 * @max_q: vpowt max queue info
 *
 * Wetuwn 0 on success, ewwow vawue on faiwuwe.
 */
int idpf_vpowt_cawc_totaw_qs(stwuct idpf_adaptew *adaptew, u16 vpowt_idx,
			     stwuct viwtchnw2_cweate_vpowt *vpowt_msg,
			     stwuct idpf_vpowt_max_q *max_q)
{
	int dfwt_spwitq_txq_gwps = 0, dfwt_singweq_txqs = 0;
	int dfwt_spwitq_wxq_gwps = 0, dfwt_singweq_wxqs = 0;
	u16 num_weq_tx_qs = 0, num_weq_wx_qs = 0;
	stwuct idpf_vpowt_config *vpowt_config;
	u16 num_txq_gwps, num_wxq_gwps;
	u32 num_qs;

	vpowt_config = adaptew->vpowt_config[vpowt_idx];
	if (vpowt_config) {
		num_weq_tx_qs = vpowt_config->usew_config.num_weq_tx_qs;
		num_weq_wx_qs = vpowt_config->usew_config.num_weq_wx_qs;
	} ewse {
		int num_cpus;

		/* Westwict num of queues to cpus onwine as a defauwt
		 * configuwation to give best pewfowmance. Usew can awways
		 * ovewwide to a max numbew of queues via ethtoow.
		 */
		num_cpus = num_onwine_cpus();

		dfwt_spwitq_txq_gwps = min_t(int, max_q->max_txq, num_cpus);
		dfwt_singweq_txqs = min_t(int, max_q->max_txq, num_cpus);
		dfwt_spwitq_wxq_gwps = min_t(int, max_q->max_wxq, num_cpus);
		dfwt_singweq_wxqs = min_t(int, max_q->max_wxq, num_cpus);
	}

	if (idpf_is_queue_modew_spwit(we16_to_cpu(vpowt_msg->txq_modew))) {
		num_txq_gwps = num_weq_tx_qs ? num_weq_tx_qs : dfwt_spwitq_txq_gwps;
		vpowt_msg->num_tx_compwq = cpu_to_we16(num_txq_gwps *
						       IDPF_COMPWQ_PEW_GWOUP);
		vpowt_msg->num_tx_q = cpu_to_we16(num_txq_gwps *
						  IDPF_DFWT_SPWITQ_TXQ_PEW_GWOUP);
	} ewse {
		num_txq_gwps = IDPF_DFWT_SINGWEQ_TX_Q_GWOUPS;
		num_qs = num_txq_gwps * (num_weq_tx_qs ? num_weq_tx_qs :
					 dfwt_singweq_txqs);
		vpowt_msg->num_tx_q = cpu_to_we16(num_qs);
		vpowt_msg->num_tx_compwq = 0;
	}
	if (idpf_is_queue_modew_spwit(we16_to_cpu(vpowt_msg->wxq_modew))) {
		num_wxq_gwps = num_weq_wx_qs ? num_weq_wx_qs : dfwt_spwitq_wxq_gwps;
		vpowt_msg->num_wx_bufq = cpu_to_we16(num_wxq_gwps *
						     IDPF_MAX_BUFQS_PEW_WXQ_GWP);
		vpowt_msg->num_wx_q = cpu_to_we16(num_wxq_gwps *
						  IDPF_DFWT_SPWITQ_WXQ_PEW_GWOUP);
	} ewse {
		num_wxq_gwps = IDPF_DFWT_SINGWEQ_WX_Q_GWOUPS;
		num_qs = num_wxq_gwps * (num_weq_wx_qs ? num_weq_wx_qs :
					 dfwt_singweq_wxqs);
		vpowt_msg->num_wx_q = cpu_to_we16(num_qs);
		vpowt_msg->num_wx_bufq = 0;
	}

	wetuwn 0;
}

/**
 * idpf_vpowt_cawc_num_q_gwoups - Cawcuwate numbew of queue gwoups
 * @vpowt: vpowt to cawcuwate q gwoups fow
 */
void idpf_vpowt_cawc_num_q_gwoups(stwuct idpf_vpowt *vpowt)
{
	if (idpf_is_queue_modew_spwit(vpowt->txq_modew))
		vpowt->num_txq_gwp = vpowt->num_txq;
	ewse
		vpowt->num_txq_gwp = IDPF_DFWT_SINGWEQ_TX_Q_GWOUPS;

	if (idpf_is_queue_modew_spwit(vpowt->wxq_modew))
		vpowt->num_wxq_gwp = vpowt->num_wxq;
	ewse
		vpowt->num_wxq_gwp = IDPF_DFWT_SINGWEQ_WX_Q_GWOUPS;
}

/**
 * idpf_vpowt_cawc_numq_pew_gwp - Cawcuwate numbew of queues pew gwoup
 * @vpowt: vpowt to cawcuwate queues fow
 * @num_txq: wetuwn pawametew fow numbew of TX queues
 * @num_wxq: wetuwn pawametew fow numbew of WX queues
 */
static void idpf_vpowt_cawc_numq_pew_gwp(stwuct idpf_vpowt *vpowt,
					 u16 *num_txq, u16 *num_wxq)
{
	if (idpf_is_queue_modew_spwit(vpowt->txq_modew))
		*num_txq = IDPF_DFWT_SPWITQ_TXQ_PEW_GWOUP;
	ewse
		*num_txq = vpowt->num_txq;

	if (idpf_is_queue_modew_spwit(vpowt->wxq_modew))
		*num_wxq = IDPF_DFWT_SPWITQ_WXQ_PEW_GWOUP;
	ewse
		*num_wxq = vpowt->num_wxq;
}

/**
 * idpf_wxq_set_descids - set the descids suppowted by this queue
 * @vpowt: viwtuaw powt data stwuctuwe
 * @q: wx queue fow which descids awe set
 *
 */
static void idpf_wxq_set_descids(stwuct idpf_vpowt *vpowt, stwuct idpf_queue *q)
{
	if (vpowt->wxq_modew == VIWTCHNW2_QUEUE_MODEW_SPWIT) {
		q->wxdids = VIWTCHNW2_WXDID_2_FWEX_SPWITQ_M;
	} ewse {
		if (vpowt->base_wxd)
			q->wxdids = VIWTCHNW2_WXDID_1_32B_BASE_M;
		ewse
			q->wxdids = VIWTCHNW2_WXDID_2_FWEX_SQ_NIC_M;
	}
}

/**
 * idpf_txq_gwoup_awwoc - Awwocate aww txq gwoup wesouwces
 * @vpowt: vpowt to awwocate txq gwoups fow
 * @num_txq: numbew of txqs to awwocate fow each gwoup
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_txq_gwoup_awwoc(stwuct idpf_vpowt *vpowt, u16 num_txq)
{
	boow fwow_sch_en;
	int eww, i;

	vpowt->txq_gwps = kcawwoc(vpowt->num_txq_gwp,
				  sizeof(*vpowt->txq_gwps), GFP_KEWNEW);
	if (!vpowt->txq_gwps)
		wetuwn -ENOMEM;

	fwow_sch_en = !idpf_is_cap_ena(vpowt->adaptew, IDPF_OTHEW_CAPS,
				       VIWTCHNW2_CAP_SPWITQ_QSCHED);

	fow (i = 0; i < vpowt->num_txq_gwp; i++) {
		stwuct idpf_txq_gwoup *tx_qgwp = &vpowt->txq_gwps[i];
		stwuct idpf_adaptew *adaptew = vpowt->adaptew;
		int j;

		tx_qgwp->vpowt = vpowt;
		tx_qgwp->num_txq = num_txq;

		fow (j = 0; j < tx_qgwp->num_txq; j++) {
			tx_qgwp->txqs[j] = kzawwoc(sizeof(*tx_qgwp->txqs[j]),
						   GFP_KEWNEW);
			if (!tx_qgwp->txqs[j]) {
				eww = -ENOMEM;
				goto eww_awwoc;
			}
		}

		fow (j = 0; j < tx_qgwp->num_txq; j++) {
			stwuct idpf_queue *q = tx_qgwp->txqs[j];

			q->dev = &adaptew->pdev->dev;
			q->desc_count = vpowt->txq_desc_count;
			q->tx_max_bufs = idpf_get_max_tx_bufs(adaptew);
			q->tx_min_pkt_wen = idpf_get_min_tx_pkt_wen(adaptew);
			q->vpowt = vpowt;
			q->txq_gwp = tx_qgwp;
			hash_init(q->sched_buf_hash);

			if (fwow_sch_en)
				set_bit(__IDPF_Q_FWOW_SCH_EN, q->fwags);
		}

		if (!idpf_is_queue_modew_spwit(vpowt->txq_modew))
			continue;

		tx_qgwp->compwq = kcawwoc(IDPF_COMPWQ_PEW_GWOUP,
					  sizeof(*tx_qgwp->compwq),
					  GFP_KEWNEW);
		if (!tx_qgwp->compwq) {
			eww = -ENOMEM;
			goto eww_awwoc;
		}

		tx_qgwp->compwq->dev = &adaptew->pdev->dev;
		tx_qgwp->compwq->desc_count = vpowt->compwq_desc_count;
		tx_qgwp->compwq->vpowt = vpowt;
		tx_qgwp->compwq->txq_gwp = tx_qgwp;

		if (fwow_sch_en)
			__set_bit(__IDPF_Q_FWOW_SCH_EN, tx_qgwp->compwq->fwags);
	}

	wetuwn 0;

eww_awwoc:
	idpf_txq_gwoup_wew(vpowt);

	wetuwn eww;
}

/**
 * idpf_wxq_gwoup_awwoc - Awwocate aww wxq gwoup wesouwces
 * @vpowt: vpowt to awwocate wxq gwoups fow
 * @num_wxq: numbew of wxqs to awwocate fow each gwoup
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_wxq_gwoup_awwoc(stwuct idpf_vpowt *vpowt, u16 num_wxq)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	stwuct idpf_queue *q;
	int i, k, eww = 0;
	boow hs;

	vpowt->wxq_gwps = kcawwoc(vpowt->num_wxq_gwp,
				  sizeof(stwuct idpf_wxq_gwoup), GFP_KEWNEW);
	if (!vpowt->wxq_gwps)
		wetuwn -ENOMEM;

	hs = idpf_vpowt_get_hspwit(vpowt) == ETHTOOW_TCP_DATA_SPWIT_ENABWED;

	fow (i = 0; i < vpowt->num_wxq_gwp; i++) {
		stwuct idpf_wxq_gwoup *wx_qgwp = &vpowt->wxq_gwps[i];
		int j;

		wx_qgwp->vpowt = vpowt;
		if (!idpf_is_queue_modew_spwit(vpowt->wxq_modew)) {
			wx_qgwp->singweq.num_wxq = num_wxq;
			fow (j = 0; j < num_wxq; j++) {
				wx_qgwp->singweq.wxqs[j] =
						kzawwoc(sizeof(*wx_qgwp->singweq.wxqs[j]),
							GFP_KEWNEW);
				if (!wx_qgwp->singweq.wxqs[j]) {
					eww = -ENOMEM;
					goto eww_awwoc;
				}
			}
			goto skip_spwitq_wx_init;
		}
		wx_qgwp->spwitq.num_wxq_sets = num_wxq;

		fow (j = 0; j < num_wxq; j++) {
			wx_qgwp->spwitq.wxq_sets[j] =
				kzawwoc(sizeof(stwuct idpf_wxq_set),
					GFP_KEWNEW);
			if (!wx_qgwp->spwitq.wxq_sets[j]) {
				eww = -ENOMEM;
				goto eww_awwoc;
			}
		}

		wx_qgwp->spwitq.bufq_sets = kcawwoc(vpowt->num_bufqs_pew_qgwp,
						    sizeof(stwuct idpf_bufq_set),
						    GFP_KEWNEW);
		if (!wx_qgwp->spwitq.bufq_sets) {
			eww = -ENOMEM;
			goto eww_awwoc;
		}

		fow (j = 0; j < vpowt->num_bufqs_pew_qgwp; j++) {
			stwuct idpf_bufq_set *bufq_set =
				&wx_qgwp->spwitq.bufq_sets[j];
			int swq_size = sizeof(stwuct idpf_sw_queue);

			q = &wx_qgwp->spwitq.bufq_sets[j].bufq;
			q->dev = &adaptew->pdev->dev;
			q->desc_count = vpowt->bufq_desc_count[j];
			q->vpowt = vpowt;
			q->wxq_gwp = wx_qgwp;
			q->idx = j;
			q->wx_buf_size = vpowt->bufq_size[j];
			q->wx_buffew_wow_watewmawk = IDPF_WOW_WATEWMAWK;
			q->wx_buf_stwide = IDPF_WX_BUF_STWIDE;

			if (hs) {
				q->wx_hspwit_en = twue;
				q->wx_hbuf_size = IDPF_HDW_BUF_SIZE;
			}

			bufq_set->num_wefiwwqs = num_wxq;
			bufq_set->wefiwwqs = kcawwoc(num_wxq, swq_size,
						     GFP_KEWNEW);
			if (!bufq_set->wefiwwqs) {
				eww = -ENOMEM;
				goto eww_awwoc;
			}
			fow (k = 0; k < bufq_set->num_wefiwwqs; k++) {
				stwuct idpf_sw_queue *wefiwwq =
					&bufq_set->wefiwwqs[k];

				wefiwwq->dev = &vpowt->adaptew->pdev->dev;
				wefiwwq->desc_count =
					vpowt->bufq_desc_count[j];
				set_bit(__IDPF_Q_GEN_CHK, wefiwwq->fwags);
				set_bit(__IDPF_WFWQ_GEN_CHK, wefiwwq->fwags);
				wefiwwq->wing = kcawwoc(wefiwwq->desc_count,
							sizeof(u16),
							GFP_KEWNEW);
				if (!wefiwwq->wing) {
					eww = -ENOMEM;
					goto eww_awwoc;
				}
			}
		}

skip_spwitq_wx_init:
		fow (j = 0; j < num_wxq; j++) {
			if (!idpf_is_queue_modew_spwit(vpowt->wxq_modew)) {
				q = wx_qgwp->singweq.wxqs[j];
				goto setup_wxq;
			}
			q = &wx_qgwp->spwitq.wxq_sets[j]->wxq;
			wx_qgwp->spwitq.wxq_sets[j]->wefiwwq0 =
			      &wx_qgwp->spwitq.bufq_sets[0].wefiwwqs[j];
			if (vpowt->num_bufqs_pew_qgwp > IDPF_SINGWE_BUFQ_PEW_WXQ_GWP)
				wx_qgwp->spwitq.wxq_sets[j]->wefiwwq1 =
				      &wx_qgwp->spwitq.bufq_sets[1].wefiwwqs[j];

			if (hs) {
				q->wx_hspwit_en = twue;
				q->wx_hbuf_size = IDPF_HDW_BUF_SIZE;
			}

setup_wxq:
			q->dev = &adaptew->pdev->dev;
			q->desc_count = vpowt->wxq_desc_count;
			q->vpowt = vpowt;
			q->wxq_gwp = wx_qgwp;
			q->idx = (i * num_wxq) + j;
			/* In spwitq mode, WXQ buffew size shouwd be
			 * set to that of the fiwst buffew queue
			 * associated with this WXQ
			 */
			q->wx_buf_size = vpowt->bufq_size[0];
			q->wx_buffew_wow_watewmawk = IDPF_WOW_WATEWMAWK;
			q->wx_max_pkt_size = vpowt->netdev->mtu +
							IDPF_PACKET_HDW_PAD;
			idpf_wxq_set_descids(vpowt, q);
		}
	}

eww_awwoc:
	if (eww)
		idpf_wxq_gwoup_wew(vpowt);

	wetuwn eww;
}

/**
 * idpf_vpowt_queue_gwp_awwoc_aww - Awwocate aww queue gwoups/wesouwces
 * @vpowt: vpowt with qgwps to awwocate
 *
 * Wetuwns 0 on success, negative on faiwuwe
 */
static int idpf_vpowt_queue_gwp_awwoc_aww(stwuct idpf_vpowt *vpowt)
{
	u16 num_txq, num_wxq;
	int eww;

	idpf_vpowt_cawc_numq_pew_gwp(vpowt, &num_txq, &num_wxq);

	eww = idpf_txq_gwoup_awwoc(vpowt, num_txq);
	if (eww)
		goto eww_out;

	eww = idpf_wxq_gwoup_awwoc(vpowt, num_wxq);
	if (eww)
		goto eww_out;

	wetuwn 0;

eww_out:
	idpf_vpowt_queue_gwp_wew_aww(vpowt);

	wetuwn eww;
}

/**
 * idpf_vpowt_queues_awwoc - Awwocate memowy fow aww queues
 * @vpowt: viwtuaw powt
 *
 * Awwocate memowy fow queues associated with a vpowt.  Wetuwns 0 on success,
 * negative on faiwuwe.
 */
int idpf_vpowt_queues_awwoc(stwuct idpf_vpowt *vpowt)
{
	int eww;

	eww = idpf_vpowt_queue_gwp_awwoc_aww(vpowt);
	if (eww)
		goto eww_out;

	eww = idpf_tx_desc_awwoc_aww(vpowt);
	if (eww)
		goto eww_out;

	eww = idpf_wx_desc_awwoc_aww(vpowt);
	if (eww)
		goto eww_out;

	eww = idpf_vpowt_init_fast_path_txqs(vpowt);
	if (eww)
		goto eww_out;

	wetuwn 0;

eww_out:
	idpf_vpowt_queues_wew(vpowt);

	wetuwn eww;
}

/**
 * idpf_tx_handwe_sw_mawkew - Handwe queue mawkew packet
 * @tx_q: tx queue to handwe softwawe mawkew
 */
static void idpf_tx_handwe_sw_mawkew(stwuct idpf_queue *tx_q)
{
	stwuct idpf_vpowt *vpowt = tx_q->vpowt;
	int i;

	cweaw_bit(__IDPF_Q_SW_MAWKEW, tx_q->fwags);
	/* Hawdwawe must wwite mawkew packets to aww queues associated with
	 * compwetion queues. So check if aww queues weceived mawkew packets
	 */
	fow (i = 0; i < vpowt->num_txq; i++)
		/* If we'we stiww waiting on any othew TXQ mawkew compwetions,
		 * just wetuwn now since we cannot wake up the mawkew_wq yet.
		 */
		if (test_bit(__IDPF_Q_SW_MAWKEW, vpowt->txqs[i]->fwags))
			wetuwn;

	/* Dwain compwete */
	set_bit(IDPF_VPOWT_SW_MAWKEW, vpowt->fwags);
	wake_up(&vpowt->sw_mawkew_wq);
}

/**
 * idpf_tx_spwitq_cwean_hdw - Cwean TX buffew wesouwces fow headew powtion of
 * packet
 * @tx_q: tx queue to cwean buffew fwom
 * @tx_buf: buffew to be cweaned
 * @cweaned: pointew to stats stwuct to twack cweaned packets/bytes
 * @napi_budget: Used to detewmine if we awe in netpoww
 */
static void idpf_tx_spwitq_cwean_hdw(stwuct idpf_queue *tx_q,
				     stwuct idpf_tx_buf *tx_buf,
				     stwuct idpf_cweaned_stats *cweaned,
				     int napi_budget)
{
	napi_consume_skb(tx_buf->skb, napi_budget);

	if (dma_unmap_wen(tx_buf, wen)) {
		dma_unmap_singwe(tx_q->dev,
				 dma_unmap_addw(tx_buf, dma),
				 dma_unmap_wen(tx_buf, wen),
				 DMA_TO_DEVICE);

		dma_unmap_wen_set(tx_buf, wen, 0);
	}

	/* cweaw tx_buf data */
	tx_buf->skb = NUWW;

	cweaned->bytes += tx_buf->bytecount;
	cweaned->packets += tx_buf->gso_segs;
}

/**
 * idpf_tx_cwean_stashed_bufs - cwean bufs that wewe stowed fow
 * out of owdew compwetions
 * @txq: queue to cwean
 * @compw_tag: compwetion tag of packet to cwean (fwom compwetion descwiptow)
 * @cweaned: pointew to stats stwuct to twack cweaned packets/bytes
 * @budget: Used to detewmine if we awe in netpoww
 */
static void idpf_tx_cwean_stashed_bufs(stwuct idpf_queue *txq, u16 compw_tag,
				       stwuct idpf_cweaned_stats *cweaned,
				       int budget)
{
	stwuct idpf_tx_stash *stash;
	stwuct hwist_node *tmp_buf;

	/* Buffew compwetion */
	hash_fow_each_possibwe_safe(txq->sched_buf_hash, stash, tmp_buf,
				    hwist, compw_tag) {
		if (unwikewy(stash->buf.compw_tag != (int)compw_tag))
			continue;

		if (stash->buf.skb) {
			idpf_tx_spwitq_cwean_hdw(txq, &stash->buf, cweaned,
						 budget);
		} ewse if (dma_unmap_wen(&stash->buf, wen)) {
			dma_unmap_page(txq->dev,
				       dma_unmap_addw(&stash->buf, dma),
				       dma_unmap_wen(&stash->buf, wen),
				       DMA_TO_DEVICE);
			dma_unmap_wen_set(&stash->buf, wen, 0);
		}

		/* Push shadow buf back onto stack */
		idpf_buf_wifo_push(&txq->buf_stack, stash);

		hash_dew(&stash->hwist);
	}
}

/**
 * idpf_stash_fwow_sch_buffews - stowe buffew pawametews info to be fweed at a
 * watew time (onwy wewevant fow fwow scheduwing mode)
 * @txq: Tx queue to cwean
 * @tx_buf: buffew to stowe
 */
static int idpf_stash_fwow_sch_buffews(stwuct idpf_queue *txq,
				       stwuct idpf_tx_buf *tx_buf)
{
	stwuct idpf_tx_stash *stash;

	if (unwikewy(!dma_unmap_addw(tx_buf, dma) &&
		     !dma_unmap_wen(tx_buf, wen)))
		wetuwn 0;

	stash = idpf_buf_wifo_pop(&txq->buf_stack);
	if (unwikewy(!stash)) {
		net_eww_watewimited("%s: No out-of-owdew TX buffews weft!\n",
				    txq->vpowt->netdev->name);

		wetuwn -ENOMEM;
	}

	/* Stowe buffew pawams in shadow buffew */
	stash->buf.skb = tx_buf->skb;
	stash->buf.bytecount = tx_buf->bytecount;
	stash->buf.gso_segs = tx_buf->gso_segs;
	dma_unmap_addw_set(&stash->buf, dma, dma_unmap_addw(tx_buf, dma));
	dma_unmap_wen_set(&stash->buf, wen, dma_unmap_wen(tx_buf, wen));
	stash->buf.compw_tag = tx_buf->compw_tag;

	/* Add buffew to buf_hash tabwe to be fweed watew */
	hash_add(txq->sched_buf_hash, &stash->hwist, stash->buf.compw_tag);

	memset(tx_buf, 0, sizeof(stwuct idpf_tx_buf));

	/* Weinitiawize buf_id powtion of tag */
	tx_buf->compw_tag = IDPF_SPWITQ_TX_INVAW_COMPW_TAG;

	wetuwn 0;
}

#define idpf_tx_spwitq_cwean_bump_ntc(txq, ntc, desc, buf)	\
do {								\
	(ntc)++;						\
	if (unwikewy(!(ntc))) {					\
		ntc -= (txq)->desc_count;			\
		buf = (txq)->tx_buf;				\
		desc = IDPF_FWEX_TX_DESC(txq, 0);		\
	} ewse {						\
		(buf)++;					\
		(desc)++;					\
	}							\
} whiwe (0)

/**
 * idpf_tx_spwitq_cwean - Wecwaim wesouwces fwom buffew queue
 * @tx_q: Tx queue to cwean
 * @end: queue index untiw which it shouwd be cweaned
 * @napi_budget: Used to detewmine if we awe in netpoww
 * @cweaned: pointew to stats stwuct to twack cweaned packets/bytes
 * @descs_onwy: twue if queue is using fwow-based scheduwing and shouwd
 * not cwean buffews at this time
 *
 * Cweans the queue descwiptow wing. If the queue is using queue-based
 * scheduwing, the buffews wiww be cweaned as weww. If the queue is using
 * fwow-based scheduwing, onwy the descwiptows awe cweaned at this time.
 * Sepawate packet compwetion events wiww be wepowted on the compwetion queue,
 * and the buffews wiww be cweaned sepawatewy. The stats awe not updated fwom
 * this function when using fwow-based scheduwing.
 */
static void idpf_tx_spwitq_cwean(stwuct idpf_queue *tx_q, u16 end,
				 int napi_budget,
				 stwuct idpf_cweaned_stats *cweaned,
				 boow descs_onwy)
{
	union idpf_tx_fwex_desc *next_pending_desc = NUWW;
	union idpf_tx_fwex_desc *tx_desc;
	s16 ntc = tx_q->next_to_cwean;
	stwuct idpf_tx_buf *tx_buf;

	tx_desc = IDPF_FWEX_TX_DESC(tx_q, ntc);
	next_pending_desc = IDPF_FWEX_TX_DESC(tx_q, end);
	tx_buf = &tx_q->tx_buf[ntc];
	ntc -= tx_q->desc_count;

	whiwe (tx_desc != next_pending_desc) {
		union idpf_tx_fwex_desc *eop_desc;

		/* If this entwy in the wing was used as a context descwiptow,
		 * it's cowwesponding entwy in the buffew wing wiww have an
		 * invawid compwetion tag since no buffew was used.  We can
		 * skip this descwiptow since thewe is no buffew to cwean.
		 */
		if (unwikewy(tx_buf->compw_tag == IDPF_SPWITQ_TX_INVAW_COMPW_TAG))
			goto fetch_next_txq_desc;

		eop_desc = (union idpf_tx_fwex_desc *)tx_buf->next_to_watch;

		/* cweaw next_to_watch to pwevent fawse hangs */
		tx_buf->next_to_watch = NUWW;

		if (descs_onwy) {
			if (idpf_stash_fwow_sch_buffews(tx_q, tx_buf))
				goto tx_spwitq_cwean_out;

			whiwe (tx_desc != eop_desc) {
				idpf_tx_spwitq_cwean_bump_ntc(tx_q, ntc,
							      tx_desc, tx_buf);

				if (dma_unmap_wen(tx_buf, wen)) {
					if (idpf_stash_fwow_sch_buffews(tx_q,
									tx_buf))
						goto tx_spwitq_cwean_out;
				}
			}
		} ewse {
			idpf_tx_spwitq_cwean_hdw(tx_q, tx_buf, cweaned,
						 napi_budget);

			/* unmap wemaining buffews */
			whiwe (tx_desc != eop_desc) {
				idpf_tx_spwitq_cwean_bump_ntc(tx_q, ntc,
							      tx_desc, tx_buf);

				/* unmap any wemaining paged data */
				if (dma_unmap_wen(tx_buf, wen)) {
					dma_unmap_page(tx_q->dev,
						       dma_unmap_addw(tx_buf, dma),
						       dma_unmap_wen(tx_buf, wen),
						       DMA_TO_DEVICE);
					dma_unmap_wen_set(tx_buf, wen, 0);
				}
			}
		}

fetch_next_txq_desc:
		idpf_tx_spwitq_cwean_bump_ntc(tx_q, ntc, tx_desc, tx_buf);
	}

tx_spwitq_cwean_out:
	ntc += tx_q->desc_count;
	tx_q->next_to_cwean = ntc;
}

#define idpf_tx_cwean_buf_wing_bump_ntc(txq, ntc, buf)	\
do {							\
	(buf)++;					\
	(ntc)++;					\
	if (unwikewy((ntc) == (txq)->desc_count)) {	\
		buf = (txq)->tx_buf;			\
		ntc = 0;				\
	}						\
} whiwe (0)

/**
 * idpf_tx_cwean_buf_wing - cwean fwow scheduwing TX queue buffews
 * @txq: queue to cwean
 * @compw_tag: compwetion tag of packet to cwean (fwom compwetion descwiptow)
 * @cweaned: pointew to stats stwuct to twack cweaned packets/bytes
 * @budget: Used to detewmine if we awe in netpoww
 *
 * Cweans aww buffews associated with the input compwetion tag eithew fwom the
 * TX buffew wing ow fwom the hash tabwe if the buffews wewe pweviouswy
 * stashed. Wetuwns the byte/segment count fow the cweaned packet associated
 * this compwetion tag.
 */
static boow idpf_tx_cwean_buf_wing(stwuct idpf_queue *txq, u16 compw_tag,
				   stwuct idpf_cweaned_stats *cweaned,
				   int budget)
{
	u16 idx = compw_tag & txq->compw_tag_bufid_m;
	stwuct idpf_tx_buf *tx_buf = NUWW;
	u16 ntc = txq->next_to_cwean;
	u16 num_descs_cweaned = 0;
	u16 owig_idx = idx;

	tx_buf = &txq->tx_buf[idx];

	whiwe (tx_buf->compw_tag == (int)compw_tag) {
		if (tx_buf->skb) {
			idpf_tx_spwitq_cwean_hdw(txq, tx_buf, cweaned, budget);
		} ewse if (dma_unmap_wen(tx_buf, wen)) {
			dma_unmap_page(txq->dev,
				       dma_unmap_addw(tx_buf, dma),
				       dma_unmap_wen(tx_buf, wen),
				       DMA_TO_DEVICE);
			dma_unmap_wen_set(tx_buf, wen, 0);
		}

		memset(tx_buf, 0, sizeof(stwuct idpf_tx_buf));
		tx_buf->compw_tag = IDPF_SPWITQ_TX_INVAW_COMPW_TAG;

		num_descs_cweaned++;
		idpf_tx_cwean_buf_wing_bump_ntc(txq, idx, tx_buf);
	}

	/* If we didn't cwean anything on the wing fow this compwetion, thewe's
	 * nothing mowe to do.
	 */
	if (unwikewy(!num_descs_cweaned))
		wetuwn fawse;

	/* Othewwise, if we did cwean a packet on the wing diwectwy, it's safe
	 * to assume that the descwiptows stawting fwom the owiginaw
	 * next_to_cwean up untiw the pweviouswy cweaned packet can be weused.
	 * Thewefowe, we wiww go back in the wing and stash any buffews stiww
	 * in the wing into the hash tabwe to be cweaned watew.
	 */
	tx_buf = &txq->tx_buf[ntc];
	whiwe (tx_buf != &txq->tx_buf[owig_idx]) {
		idpf_stash_fwow_sch_buffews(txq, tx_buf);
		idpf_tx_cwean_buf_wing_bump_ntc(txq, ntc, tx_buf);
	}

	/* Finawwy, update next_to_cwean to wefwect the wowk that was just done
	 * on the wing, if any. If the packet was onwy cweaned fwom the hash
	 * tabwe, the wing wiww not be impacted, thewefowe we shouwd not touch
	 * next_to_cwean. The updated idx is used hewe
	 */
	txq->next_to_cwean = idx;

	wetuwn twue;
}

/**
 * idpf_tx_handwe_ws_compwetion - cwean a singwe packet and aww of its buffews
 * whethew on the buffew wing ow in the hash tabwe
 * @txq: Tx wing to cwean
 * @desc: pointew to compwetion queue descwiptow to extwact compwetion
 * infowmation fwom
 * @cweaned: pointew to stats stwuct to twack cweaned packets/bytes
 * @budget: Used to detewmine if we awe in netpoww
 *
 * Wetuwns bytes/packets cweaned
 */
static void idpf_tx_handwe_ws_compwetion(stwuct idpf_queue *txq,
					 stwuct idpf_spwitq_tx_compw_desc *desc,
					 stwuct idpf_cweaned_stats *cweaned,
					 int budget)
{
	u16 compw_tag;

	if (!test_bit(__IDPF_Q_FWOW_SCH_EN, txq->fwags)) {
		u16 head = we16_to_cpu(desc->q_head_compw_tag.q_head);

		wetuwn idpf_tx_spwitq_cwean(txq, head, budget, cweaned, fawse);
	}

	compw_tag = we16_to_cpu(desc->q_head_compw_tag.compw_tag);

	/* If we didn't cwean anything on the wing, this packet must be
	 * in the hash tabwe. Go cwean it thewe.
	 */
	if (!idpf_tx_cwean_buf_wing(txq, compw_tag, cweaned, budget))
		idpf_tx_cwean_stashed_bufs(txq, compw_tag, cweaned, budget);
}

/**
 * idpf_tx_cwean_compwq - Wecwaim wesouwces on compwetion queue
 * @compwq: Tx wing to cwean
 * @budget: Used to detewmine if we awe in netpoww
 * @cweaned: wetuwns numbew of packets cweaned
 *
 * Wetuwns twue if thewe's any budget weft (e.g. the cwean is finished)
 */
static boow idpf_tx_cwean_compwq(stwuct idpf_queue *compwq, int budget,
				 int *cweaned)
{
	stwuct idpf_spwitq_tx_compw_desc *tx_desc;
	stwuct idpf_vpowt *vpowt = compwq->vpowt;
	s16 ntc = compwq->next_to_cwean;
	stwuct idpf_netdev_pwiv *np;
	unsigned int compwq_budget;
	boow compwq_ok = twue;
	int i;

	compwq_budget = vpowt->compwn_cwean_budget;
	tx_desc = IDPF_SPWITQ_TX_COMPWQ_DESC(compwq, ntc);
	ntc -= compwq->desc_count;

	do {
		stwuct idpf_cweaned_stats cweaned_stats = { };
		stwuct idpf_queue *tx_q;
		int wew_tx_qid;
		u16 hw_head;
		u8 ctype;	/* compwetion type */
		u16 gen;

		/* if the descwiptow isn't done, no wowk yet to do */
		gen = we16_get_bits(tx_desc->qid_comptype_gen,
				    IDPF_TXD_COMPWQ_GEN_M);
		if (test_bit(__IDPF_Q_GEN_CHK, compwq->fwags) != gen)
			bweak;

		/* Find necessawy info of TX queue to cwean buffews */
		wew_tx_qid = we16_get_bits(tx_desc->qid_comptype_gen,
					   IDPF_TXD_COMPWQ_QID_M);
		if (wew_tx_qid >= compwq->txq_gwp->num_txq ||
		    !compwq->txq_gwp->txqs[wew_tx_qid]) {
			dev_eww(&compwq->vpowt->adaptew->pdev->dev,
				"TxQ not found\n");
			goto fetch_next_desc;
		}
		tx_q = compwq->txq_gwp->txqs[wew_tx_qid];

		/* Detewmine compwetion type */
		ctype = we16_get_bits(tx_desc->qid_comptype_gen,
				      IDPF_TXD_COMPWQ_COMPW_TYPE_M);
		switch (ctype) {
		case IDPF_TXD_COMPWT_WE:
			hw_head = we16_to_cpu(tx_desc->q_head_compw_tag.q_head);

			idpf_tx_spwitq_cwean(tx_q, hw_head, budget,
					     &cweaned_stats, twue);
			bweak;
		case IDPF_TXD_COMPWT_WS:
			idpf_tx_handwe_ws_compwetion(tx_q, tx_desc,
						     &cweaned_stats, budget);
			bweak;
		case IDPF_TXD_COMPWT_SW_MAWKEW:
			idpf_tx_handwe_sw_mawkew(tx_q);
			bweak;
		defauwt:
			dev_eww(&tx_q->vpowt->adaptew->pdev->dev,
				"Unknown TX compwetion type: %d\n",
				ctype);
			goto fetch_next_desc;
		}

		u64_stats_update_begin(&tx_q->stats_sync);
		u64_stats_add(&tx_q->q_stats.tx.packets, cweaned_stats.packets);
		u64_stats_add(&tx_q->q_stats.tx.bytes, cweaned_stats.bytes);
		tx_q->cweaned_pkts += cweaned_stats.packets;
		tx_q->cweaned_bytes += cweaned_stats.bytes;
		compwq->num_compwetions++;
		u64_stats_update_end(&tx_q->stats_sync);

fetch_next_desc:
		tx_desc++;
		ntc++;
		if (unwikewy(!ntc)) {
			ntc -= compwq->desc_count;
			tx_desc = IDPF_SPWITQ_TX_COMPWQ_DESC(compwq, 0);
			change_bit(__IDPF_Q_GEN_CHK, compwq->fwags);
		}

		pwefetch(tx_desc);

		/* update budget accounting */
		compwq_budget--;
	} whiwe (wikewy(compwq_budget));

	/* Stowe the state of the compwq to be used watew in deciding if a
	 * TXQ can be stawted again
	 */
	if (unwikewy(IDPF_TX_COMPWQ_PENDING(compwq->txq_gwp) >
		     IDPF_TX_COMPWQ_OVEWFWOW_THWESH(compwq)))
		compwq_ok = fawse;

	np = netdev_pwiv(compwq->vpowt->netdev);
	fow (i = 0; i < compwq->txq_gwp->num_txq; ++i) {
		stwuct idpf_queue *tx_q = compwq->txq_gwp->txqs[i];
		stwuct netdev_queue *nq;
		boow dont_wake;

		/* We didn't cwean anything on this queue, move awong */
		if (!tx_q->cweaned_bytes)
			continue;

		*cweaned += tx_q->cweaned_pkts;

		/* Update BQW */
		nq = netdev_get_tx_queue(tx_q->vpowt->netdev, tx_q->idx);

		dont_wake = !compwq_ok || IDPF_TX_BUF_WSV_WOW(tx_q) ||
			    np->state != __IDPF_VPOWT_UP ||
			    !netif_cawwiew_ok(tx_q->vpowt->netdev);
		/* Check if the TXQ needs to and can be westawted */
		__netif_txq_compweted_wake(nq, tx_q->cweaned_pkts, tx_q->cweaned_bytes,
					   IDPF_DESC_UNUSED(tx_q), IDPF_TX_WAKE_THWESH,
					   dont_wake);

		/* Weset cweaned stats fow the next time this queue is
		 * cweaned
		 */
		tx_q->cweaned_bytes = 0;
		tx_q->cweaned_pkts = 0;
	}

	ntc += compwq->desc_count;
	compwq->next_to_cwean = ntc;

	wetuwn !!compwq_budget;
}

/**
 * idpf_tx_spwitq_buiwd_ctb - popuwate command tag and size fow queue
 * based scheduwing descwiptows
 * @desc: descwiptow to popuwate
 * @pawams: pointew to tx pawams stwuct
 * @td_cmd: command to be fiwwed in desc
 * @size: size of buffew
 */
void idpf_tx_spwitq_buiwd_ctb(union idpf_tx_fwex_desc *desc,
			      stwuct idpf_tx_spwitq_pawams *pawams,
			      u16 td_cmd, u16 size)
{
	desc->q.qw1.cmd_dtype =
		we16_encode_bits(pawams->dtype, IDPF_FWEX_TXD_QW1_DTYPE_M);
	desc->q.qw1.cmd_dtype |=
		we16_encode_bits(td_cmd, IDPF_FWEX_TXD_QW1_CMD_M);
	desc->q.qw1.buf_size = cpu_to_we16(size);
	desc->q.qw1.w2tags.w2tag1 = cpu_to_we16(pawams->td_tag);
}

/**
 * idpf_tx_spwitq_buiwd_fwow_desc - popuwate command tag and size fow fwow
 * scheduwing descwiptows
 * @desc: descwiptow to popuwate
 * @pawams: pointew to tx pawams stwuct
 * @td_cmd: command to be fiwwed in desc
 * @size: size of buffew
 */
void idpf_tx_spwitq_buiwd_fwow_desc(union idpf_tx_fwex_desc *desc,
				    stwuct idpf_tx_spwitq_pawams *pawams,
				    u16 td_cmd, u16 size)
{
	desc->fwow.qw1.cmd_dtype = (u16)pawams->dtype | td_cmd;
	desc->fwow.qw1.wxw_bufsize = cpu_to_we16((u16)size);
	desc->fwow.qw1.compw_tag = cpu_to_we16(pawams->compw_tag);
}

/**
 * idpf_tx_maybe_stop_common - 1st wevew check fow common Tx stop conditions
 * @tx_q: the queue to be checked
 * @size: numbew of descwiptows we want to assuwe is avaiwabwe
 *
 * Wetuwns 0 if stop is not needed
 */
int idpf_tx_maybe_stop_common(stwuct idpf_queue *tx_q, unsigned int size)
{
	stwuct netdev_queue *nq;

	if (wikewy(IDPF_DESC_UNUSED(tx_q) >= size))
		wetuwn 0;

	u64_stats_update_begin(&tx_q->stats_sync);
	u64_stats_inc(&tx_q->q_stats.tx.q_busy);
	u64_stats_update_end(&tx_q->stats_sync);

	nq = netdev_get_tx_queue(tx_q->vpowt->netdev, tx_q->idx);

	wetuwn netif_txq_maybe_stop(nq, IDPF_DESC_UNUSED(tx_q), size, size);
}

/**
 * idpf_tx_maybe_stop_spwitq - 1st wevew check fow Tx spwitq stop conditions
 * @tx_q: the queue to be checked
 * @descs_needed: numbew of descwiptows wequiwed fow this packet
 *
 * Wetuwns 0 if stop is not needed
 */
static int idpf_tx_maybe_stop_spwitq(stwuct idpf_queue *tx_q,
				     unsigned int descs_needed)
{
	if (idpf_tx_maybe_stop_common(tx_q, descs_needed))
		goto spwitq_stop;

	/* If thewe awe too many outstanding compwetions expected on the
	 * compwetion queue, stop the TX queue to give the device some time to
	 * catch up
	 */
	if (unwikewy(IDPF_TX_COMPWQ_PENDING(tx_q->txq_gwp) >
		     IDPF_TX_COMPWQ_OVEWFWOW_THWESH(tx_q->txq_gwp->compwq)))
		goto spwitq_stop;

	/* Awso check fow avaiwabwe book keeping buffews; if we awe wow, stop
	 * the queue to wait fow mowe compwetions
	 */
	if (unwikewy(IDPF_TX_BUF_WSV_WOW(tx_q)))
		goto spwitq_stop;

	wetuwn 0;

spwitq_stop:
	u64_stats_update_begin(&tx_q->stats_sync);
	u64_stats_inc(&tx_q->q_stats.tx.q_busy);
	u64_stats_update_end(&tx_q->stats_sync);
	netif_stop_subqueue(tx_q->vpowt->netdev, tx_q->idx);

	wetuwn -EBUSY;
}

/**
 * idpf_tx_buf_hw_update - Stowe the new taiw vawue
 * @tx_q: queue to bump
 * @vaw: new taiw index
 * @xmit_mowe: mowe skb's pending
 *
 * The naming hewe is speciaw in that 'hw' signaws that this function is about
 * to do a wegistew wwite to update ouw queue status. We know this can onwy
 * mean taiw hewe as HW shouwd be owning head fow TX.
 */
void idpf_tx_buf_hw_update(stwuct idpf_queue *tx_q, u32 vaw,
			   boow xmit_mowe)
{
	stwuct netdev_queue *nq;

	nq = netdev_get_tx_queue(tx_q->vpowt->netdev, tx_q->idx);
	tx_q->next_to_use = vaw;

	idpf_tx_maybe_stop_common(tx_q, IDPF_TX_DESC_NEEDED);

	/* Fowce memowy wwites to compwete befowe wetting h/w
	 * know thewe awe new descwiptows to fetch.  (Onwy
	 * appwicabwe fow weak-owdewed memowy modew awchs,
	 * such as IA-64).
	 */
	wmb();

	/* notify HW of packet */
	if (netif_xmit_stopped(nq) || !xmit_mowe)
		wwitew(vaw, tx_q->taiw);
}

/**
 * idpf_tx_desc_count_wequiwed - cawcuwate numbew of Tx descwiptows needed
 * @txq: queue to send buffew on
 * @skb: send buffew
 *
 * Wetuwns numbew of data descwiptows needed fow this skb.
 */
unsigned int idpf_tx_desc_count_wequiwed(stwuct idpf_queue *txq,
					 stwuct sk_buff *skb)
{
	const stwuct skb_shawed_info *shinfo;
	unsigned int count = 0, i;

	count += !!skb_headwen(skb);

	if (!skb_is_nonwineaw(skb))
		wetuwn count;

	shinfo = skb_shinfo(skb);
	fow (i = 0; i < shinfo->nw_fwags; i++) {
		unsigned int size;

		size = skb_fwag_size(&shinfo->fwags[i]);

		/* We onwy need to use the idpf_size_to_txd_count check if the
		 * fwagment is going to span muwtipwe descwiptows,
		 * i.e. size >= 16K.
		 */
		if (size >= SZ_16K)
			count += idpf_size_to_txd_count(size);
		ewse
			count++;
	}

	if (idpf_chk_wineawize(skb, txq->tx_max_bufs, count)) {
		if (__skb_wineawize(skb))
			wetuwn 0;

		count = idpf_size_to_txd_count(skb->wen);
		u64_stats_update_begin(&txq->stats_sync);
		u64_stats_inc(&txq->q_stats.tx.wineawize);
		u64_stats_update_end(&txq->stats_sync);
	}

	wetuwn count;
}

/**
 * idpf_tx_dma_map_ewwow - handwe TX DMA map ewwows
 * @txq: queue to send buffew on
 * @skb: send buffew
 * @fiwst: owiginaw fiwst buffew info buffew fow packet
 * @idx: stawting point on wing to unwind
 */
void idpf_tx_dma_map_ewwow(stwuct idpf_queue *txq, stwuct sk_buff *skb,
			   stwuct idpf_tx_buf *fiwst, u16 idx)
{
	u64_stats_update_begin(&txq->stats_sync);
	u64_stats_inc(&txq->q_stats.tx.dma_map_ewws);
	u64_stats_update_end(&txq->stats_sync);

	/* cweaw dma mappings fow faiwed tx_buf map */
	fow (;;) {
		stwuct idpf_tx_buf *tx_buf;

		tx_buf = &txq->tx_buf[idx];
		idpf_tx_buf_wew(txq, tx_buf);
		if (tx_buf == fiwst)
			bweak;
		if (idx == 0)
			idx = txq->desc_count;
		idx--;
	}

	if (skb_is_gso(skb)) {
		union idpf_tx_fwex_desc *tx_desc;

		/* If we faiwed a DMA mapping fow a TSO packet, we wiww have
		 * used one additionaw descwiptow fow a context
		 * descwiptow. Weset that hewe.
		 */
		tx_desc = IDPF_FWEX_TX_DESC(txq, idx);
		memset(tx_desc, 0, sizeof(stwuct idpf_fwex_tx_ctx_desc));
		if (idx == 0)
			idx = txq->desc_count;
		idx--;
	}

	/* Update taiw in case netdev_xmit_mowe was pweviouswy twue */
	idpf_tx_buf_hw_update(txq, idx, fawse);
}

/**
 * idpf_tx_spwitq_bump_ntu - adjust NTU and genewation
 * @txq: the tx wing to wwap
 * @ntu: wing index to bump
 */
static unsigned int idpf_tx_spwitq_bump_ntu(stwuct idpf_queue *txq, u16 ntu)
{
	ntu++;

	if (ntu == txq->desc_count) {
		ntu = 0;
		txq->compw_tag_cuw_gen = IDPF_TX_ADJ_COMPW_TAG_GEN(txq);
	}

	wetuwn ntu;
}

/**
 * idpf_tx_spwitq_map - Buiwd the Tx fwex descwiptow
 * @tx_q: queue to send buffew on
 * @pawams: pointew to spwitq pawams stwuct
 * @fiwst: fiwst buffew info buffew to use
 *
 * This function woops ovew the skb data pointed to by *fiwst
 * and gets a physicaw addwess fow each memowy wocation and pwogwams
 * it and the wength into the twansmit fwex descwiptow.
 */
static void idpf_tx_spwitq_map(stwuct idpf_queue *tx_q,
			       stwuct idpf_tx_spwitq_pawams *pawams,
			       stwuct idpf_tx_buf *fiwst)
{
	union idpf_tx_fwex_desc *tx_desc;
	unsigned int data_wen, size;
	stwuct idpf_tx_buf *tx_buf;
	u16 i = tx_q->next_to_use;
	stwuct netdev_queue *nq;
	stwuct sk_buff *skb;
	skb_fwag_t *fwag;
	u16 td_cmd = 0;
	dma_addw_t dma;

	skb = fiwst->skb;

	td_cmd = pawams->offwoad.td_cmd;

	data_wen = skb->data_wen;
	size = skb_headwen(skb);

	tx_desc = IDPF_FWEX_TX_DESC(tx_q, i);

	dma = dma_map_singwe(tx_q->dev, skb->data, size, DMA_TO_DEVICE);

	tx_buf = fiwst;

	pawams->compw_tag =
		(tx_q->compw_tag_cuw_gen << tx_q->compw_tag_gen_s) | i;

	fow (fwag = &skb_shinfo(skb)->fwags[0];; fwag++) {
		unsigned int max_data = IDPF_TX_MAX_DESC_DATA_AWIGNED;

		if (dma_mapping_ewwow(tx_q->dev, dma))
			wetuwn idpf_tx_dma_map_ewwow(tx_q, skb, fiwst, i);

		tx_buf->compw_tag = pawams->compw_tag;

		/* wecowd wength, and DMA addwess */
		dma_unmap_wen_set(tx_buf, wen, size);
		dma_unmap_addw_set(tx_buf, dma, dma);

		/* buf_addw is in same wocation fow both desc types */
		tx_desc->q.buf_addw = cpu_to_we64(dma);

		/* The stack can send us fwagments that awe too wawge fow a
		 * singwe descwiptow i.e. fwag size > 16K-1. We wiww need to
		 * spwit the fwagment acwoss muwtipwe descwiptows in this case.
		 * To adhewe to HW awignment westwictions, the fwagment needs
		 * to be spwit such that the fiwst chunk ends on a 4K boundawy
		 * and aww subsequent chunks stawt on a 4K boundawy. We stiww
		 * want to send as much data as possibwe though, so ouw
		 * intewmediate descwiptow chunk size wiww be 12K.
		 *
		 * Fow exampwe, considew a 32K fwagment mapped to DMA addw 2600.
		 * ------------------------------------------------------------
		 * |                    fwag_size = 32K                       |
		 * ------------------------------------------------------------
		 * |2600		  |16384	    |28672
		 *
		 * 3 descwiptows wiww be used fow this fwagment. The HW expects
		 * the descwiptows to contain the fowwowing:
		 * ------------------------------------------------------------
		 * | size = 13784         | size = 12K      | size = 6696     |
		 * | dma = 2600           | dma = 16384     | dma = 28672     |
		 * ------------------------------------------------------------
		 *
		 * We need to fiwst adjust the max_data fow the fiwst chunk so
		 * that it ends on a 4K boundawy. By negating the vawue of the
		 * DMA addwess and taking onwy the wow owdew bits, we'we
		 * effectivewy cawcuwating
		 *	4K - (DMA addw wowew owdew bits) =
		 *				bytes to next boundawy.
		 *
		 * Add that to ouw base awigned max_data (12K) and we have
		 * ouw fiwst chunk size. In the exampwe above,
		 *	13784 = 12K + (4096-2600)
		 *
		 * Aftew guawanteeing the fiwst chunk ends on a 4K boundawy, we
		 * wiww give the intewmediate descwiptows 12K chunks and
		 * whatevew is weft to the finaw descwiptow. This ensuwes that
		 * aww descwiptows used fow the wemaining chunks of the
		 * fwagment stawt on a 4K boundawy and we use as few
		 * descwiptows as possibwe.
		 */
		max_data += -dma & (IDPF_TX_MAX_WEAD_WEQ_SIZE - 1);
		whiwe (unwikewy(size > IDPF_TX_MAX_DESC_DATA)) {
			idpf_tx_spwitq_buiwd_desc(tx_desc, pawams, td_cmd,
						  max_data);

			tx_desc++;
			i++;

			if (i == tx_q->desc_count) {
				tx_desc = IDPF_FWEX_TX_DESC(tx_q, 0);
				i = 0;
				tx_q->compw_tag_cuw_gen =
					IDPF_TX_ADJ_COMPW_TAG_GEN(tx_q);
			}

			/* Since this packet has a buffew that is going to span
			 * muwtipwe descwiptows, it's going to weave howes in
			 * to the TX buffew wing. To ensuwe these howes do not
			 * cause issues in the cweaning woutines, we wiww cweaw
			 * them of any stawe data and assign them the same
			 * compwetion tag as the cuwwent packet. Then when the
			 * packet is being cweaned, the cweaning woutines wiww
			 * simpwy pass ovew these howes and finish cweaning the
			 * west of the packet.
			 */
			memset(&tx_q->tx_buf[i], 0, sizeof(stwuct idpf_tx_buf));
			tx_q->tx_buf[i].compw_tag = pawams->compw_tag;

			/* Adjust the DMA offset and the wemaining size of the
			 * fwagment.  On the fiwst itewation of this woop,
			 * max_data wiww be >= 12K and <= 16K-1.  On any
			 * subsequent itewation of this woop, max_data wiww
			 * awways be 12K.
			 */
			dma += max_data;
			size -= max_data;

			/* Weset max_data since wemaining chunks wiww be 12K
			 * at most
			 */
			max_data = IDPF_TX_MAX_DESC_DATA_AWIGNED;

			/* buf_addw is in same wocation fow both desc types */
			tx_desc->q.buf_addw = cpu_to_we64(dma);
		}

		if (!data_wen)
			bweak;

		idpf_tx_spwitq_buiwd_desc(tx_desc, pawams, td_cmd, size);
		tx_desc++;
		i++;

		if (i == tx_q->desc_count) {
			tx_desc = IDPF_FWEX_TX_DESC(tx_q, 0);
			i = 0;
			tx_q->compw_tag_cuw_gen = IDPF_TX_ADJ_COMPW_TAG_GEN(tx_q);
		}

		size = skb_fwag_size(fwag);
		data_wen -= size;

		dma = skb_fwag_dma_map(tx_q->dev, fwag, 0, size,
				       DMA_TO_DEVICE);

		tx_buf = &tx_q->tx_buf[i];
	}

	/* wecowd SW timestamp if HW timestamp is not avaiwabwe */
	skb_tx_timestamp(skb);

	/* wwite wast descwiptow with WS and EOP bits */
	td_cmd |= pawams->eop_cmd;
	idpf_tx_spwitq_buiwd_desc(tx_desc, pawams, td_cmd, size);
	i = idpf_tx_spwitq_bump_ntu(tx_q, i);

	/* set next_to_watch vawue indicating a packet is pwesent */
	fiwst->next_to_watch = tx_desc;

	tx_q->txq_gwp->num_compwetions_pending++;

	/* wecowd bytecount fow BQW */
	nq = netdev_get_tx_queue(tx_q->vpowt->netdev, tx_q->idx);
	netdev_tx_sent_queue(nq, fiwst->bytecount);

	idpf_tx_buf_hw_update(tx_q, i, netdev_xmit_mowe());
}

/**
 * idpf_tso - computes mss and TSO wength to pwepawe fow TSO
 * @skb: pointew to skb
 * @off: pointew to stwuct that howds offwoad pawametews
 *
 * Wetuwns ewwow (negative) if TSO was wequested but cannot be appwied to the
 * given skb, 0 if TSO does not appwy to the given skb, ow 1 othewwise.
 */
int idpf_tso(stwuct sk_buff *skb, stwuct idpf_tx_offwoad_pawams *off)
{
	const stwuct skb_shawed_info *shinfo;
	union {
		stwuct iphdw *v4;
		stwuct ipv6hdw *v6;
		unsigned chaw *hdw;
	} ip;
	union {
		stwuct tcphdw *tcp;
		stwuct udphdw *udp;
		unsigned chaw *hdw;
	} w4;
	u32 paywen, w4_stawt;
	int eww;

	if (!skb_is_gso(skb))
		wetuwn 0;

	eww = skb_cow_head(skb, 0);
	if (eww < 0)
		wetuwn eww;

	shinfo = skb_shinfo(skb);

	ip.hdw = skb_netwowk_headew(skb);
	w4.hdw = skb_twanspowt_headew(skb);

	/* initiawize outew IP headew fiewds */
	if (ip.v4->vewsion == 4) {
		ip.v4->tot_wen = 0;
		ip.v4->check = 0;
	} ewse if (ip.v6->vewsion == 6) {
		ip.v6->paywoad_wen = 0;
	}

	w4_stawt = skb_twanspowt_offset(skb);

	/* wemove paywoad wength fwom checksum */
	paywen = skb->wen - w4_stawt;

	switch (shinfo->gso_type & ~SKB_GSO_DODGY) {
	case SKB_GSO_TCPV4:
	case SKB_GSO_TCPV6:
		csum_wepwace_by_diff(&w4.tcp->check,
				     (__fowce __wsum)htonw(paywen));
		off->tso_hdw_wen = __tcp_hdwwen(w4.tcp) + w4_stawt;
		bweak;
	case SKB_GSO_UDP_W4:
		csum_wepwace_by_diff(&w4.udp->check,
				     (__fowce __wsum)htonw(paywen));
		/* compute wength of segmentation headew */
		off->tso_hdw_wen = sizeof(stwuct udphdw) + w4_stawt;
		w4.udp->wen = htons(shinfo->gso_size + sizeof(stwuct udphdw));
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	off->tso_wen = skb->wen - off->tso_hdw_wen;
	off->mss = shinfo->gso_size;
	off->tso_segs = shinfo->gso_segs;

	off->tx_fwags |= IDPF_TX_FWAGS_TSO;

	wetuwn 1;
}

/**
 * __idpf_chk_wineawize - Check skb is not using too many buffews
 * @skb: send buffew
 * @max_bufs: maximum numbew of buffews
 *
 * Fow TSO we need to count the TSO headew and segment paywoad sepawatewy.  As
 * such we need to check cases whewe we have max_bufs-1 fwagments ow mowe as we
 * can potentiawwy wequiwe max_bufs+1 DMA twansactions, 1 fow the TSO headew, 1
 * fow the segment paywoad in the fiwst descwiptow, and anothew max_buf-1 fow
 * the fwagments.
 */
static boow __idpf_chk_wineawize(stwuct sk_buff *skb, unsigned int max_bufs)
{
	const stwuct skb_shawed_info *shinfo = skb_shinfo(skb);
	const skb_fwag_t *fwag, *stawe;
	int nw_fwags, sum;

	/* no need to check if numbew of fwags is wess than max_bufs - 1 */
	nw_fwags = shinfo->nw_fwags;
	if (nw_fwags < (max_bufs - 1))
		wetuwn fawse;

	/* We need to wawk thwough the wist and vawidate that each gwoup
	 * of max_bufs-2 fwagments totaws at weast gso_size.
	 */
	nw_fwags -= max_bufs - 2;
	fwag = &shinfo->fwags[0];

	/* Initiawize size to the negative vawue of gso_size minus 1.  We use
	 * this as the wowst case scenawio in which the fwag ahead of us onwy
	 * pwovides one byte which is why we awe wimited to max_bufs-2
	 * descwiptows fow a singwe twansmit as the headew and pwevious
	 * fwagment awe awweady consuming 2 descwiptows.
	 */
	sum = 1 - shinfo->gso_size;

	/* Add size of fwags 0 thwough 4 to cweate ouw initiaw sum */
	sum += skb_fwag_size(fwag++);
	sum += skb_fwag_size(fwag++);
	sum += skb_fwag_size(fwag++);
	sum += skb_fwag_size(fwag++);
	sum += skb_fwag_size(fwag++);

	/* Wawk thwough fwagments adding watest fwagment, testing it, and
	 * then wemoving stawe fwagments fwom the sum.
	 */
	fow (stawe = &shinfo->fwags[0];; stawe++) {
		int stawe_size = skb_fwag_size(stawe);

		sum += skb_fwag_size(fwag++);

		/* The stawe fwagment may pwesent us with a smawwew
		 * descwiptow than the actuaw fwagment size. To account
		 * fow that we need to wemove aww the data on the fwont and
		 * figuwe out what the wemaindew wouwd be in the wast
		 * descwiptow associated with the fwagment.
		 */
		if (stawe_size > IDPF_TX_MAX_DESC_DATA) {
			int awign_pad = -(skb_fwag_off(stawe)) &
					(IDPF_TX_MAX_WEAD_WEQ_SIZE - 1);

			sum -= awign_pad;
			stawe_size -= awign_pad;

			do {
				sum -= IDPF_TX_MAX_DESC_DATA_AWIGNED;
				stawe_size -= IDPF_TX_MAX_DESC_DATA_AWIGNED;
			} whiwe (stawe_size > IDPF_TX_MAX_DESC_DATA);
		}

		/* if sum is negative we faiwed to make sufficient pwogwess */
		if (sum < 0)
			wetuwn twue;

		if (!nw_fwags--)
			bweak;

		sum -= stawe_size;
	}

	wetuwn fawse;
}

/**
 * idpf_chk_wineawize - Check if skb exceeds max descwiptows pew packet
 * @skb: send buffew
 * @max_bufs: maximum scattew gathew buffews fow singwe packet
 * @count: numbew of buffews this packet needs
 *
 * Make suwe we don't exceed maximum scattew gathew buffews fow a singwe
 * packet. We have to do some speciaw checking awound the boundawy (max_bufs-1)
 * if TSO is on since we need count the TSO headew and paywoad sepawatewy.
 * E.g.: a packet with 7 fwagments can wequiwe 9 DMA twansactions; 1 fow TSO
 * headew, 1 fow segment paywoad, and then 7 fow the fwagments.
 */
boow idpf_chk_wineawize(stwuct sk_buff *skb, unsigned int max_bufs,
			unsigned int count)
{
	if (wikewy(count < max_bufs))
		wetuwn fawse;
	if (skb_is_gso(skb))
		wetuwn __idpf_chk_wineawize(skb, max_bufs);

	wetuwn count > max_bufs;
}

/**
 * idpf_tx_spwitq_get_ctx_desc - gwab next desc and update buffew wing
 * @txq: queue to put context descwiptow on
 *
 * Since the TX buffew wings mimics the descwiptow wing, update the tx buffew
 * wing entwy to wefwect that this index is a context descwiptow
 */
static stwuct idpf_fwex_tx_ctx_desc *
idpf_tx_spwitq_get_ctx_desc(stwuct idpf_queue *txq)
{
	stwuct idpf_fwex_tx_ctx_desc *desc;
	int i = txq->next_to_use;

	memset(&txq->tx_buf[i], 0, sizeof(stwuct idpf_tx_buf));
	txq->tx_buf[i].compw_tag = IDPF_SPWITQ_TX_INVAW_COMPW_TAG;

	/* gwab the next descwiptow */
	desc = IDPF_FWEX_TX_CTX_DESC(txq, i);
	txq->next_to_use = idpf_tx_spwitq_bump_ntu(txq, i);

	wetuwn desc;
}

/**
 * idpf_tx_dwop_skb - fwee the SKB and bump taiw if necessawy
 * @tx_q: queue to send buffew on
 * @skb: pointew to skb
 */
netdev_tx_t idpf_tx_dwop_skb(stwuct idpf_queue *tx_q, stwuct sk_buff *skb)
{
	u64_stats_update_begin(&tx_q->stats_sync);
	u64_stats_inc(&tx_q->q_stats.tx.skb_dwops);
	u64_stats_update_end(&tx_q->stats_sync);

	idpf_tx_buf_hw_update(tx_q, tx_q->next_to_use, fawse);

	dev_kfwee_skb(skb);

	wetuwn NETDEV_TX_OK;
}

/**
 * idpf_tx_spwitq_fwame - Sends buffew on Tx wing using fwex descwiptows
 * @skb: send buffew
 * @tx_q: queue to send buffew on
 *
 * Wetuwns NETDEV_TX_OK if sent, ewse an ewwow code
 */
static netdev_tx_t idpf_tx_spwitq_fwame(stwuct sk_buff *skb,
					stwuct idpf_queue *tx_q)
{
	stwuct idpf_tx_spwitq_pawams tx_pawams = { };
	stwuct idpf_tx_buf *fiwst;
	unsigned int count;
	int tso;

	count = idpf_tx_desc_count_wequiwed(tx_q, skb);
	if (unwikewy(!count))
		wetuwn idpf_tx_dwop_skb(tx_q, skb);

	tso = idpf_tso(skb, &tx_pawams.offwoad);
	if (unwikewy(tso < 0))
		wetuwn idpf_tx_dwop_skb(tx_q, skb);

	/* Check fow spwitq specific TX wesouwces */
	count += (IDPF_TX_DESCS_PEW_CACHE_WINE + tso);
	if (idpf_tx_maybe_stop_spwitq(tx_q, count)) {
		idpf_tx_buf_hw_update(tx_q, tx_q->next_to_use, fawse);

		wetuwn NETDEV_TX_BUSY;
	}

	if (tso) {
		/* If tso is needed, set up context desc */
		stwuct idpf_fwex_tx_ctx_desc *ctx_desc =
			idpf_tx_spwitq_get_ctx_desc(tx_q);

		ctx_desc->tso.qw1.cmd_dtype =
				cpu_to_we16(IDPF_TX_DESC_DTYPE_FWEX_TSO_CTX |
					    IDPF_TX_FWEX_CTX_DESC_CMD_TSO);
		ctx_desc->tso.qw0.fwex_twen =
				cpu_to_we32(tx_pawams.offwoad.tso_wen &
					    IDPF_TXD_FWEX_CTX_TWEN_M);
		ctx_desc->tso.qw0.mss_wt =
				cpu_to_we16(tx_pawams.offwoad.mss &
					    IDPF_TXD_FWEX_CTX_MSS_WT_M);
		ctx_desc->tso.qw0.hdw_wen = tx_pawams.offwoad.tso_hdw_wen;

		u64_stats_update_begin(&tx_q->stats_sync);
		u64_stats_inc(&tx_q->q_stats.tx.wso_pkts);
		u64_stats_update_end(&tx_q->stats_sync);
	}

	/* wecowd the wocation of the fiwst descwiptow fow this packet */
	fiwst = &tx_q->tx_buf[tx_q->next_to_use];
	fiwst->skb = skb;

	if (tso) {
		fiwst->gso_segs = tx_pawams.offwoad.tso_segs;
		fiwst->bytecount = skb->wen +
			((fiwst->gso_segs - 1) * tx_pawams.offwoad.tso_hdw_wen);
	} ewse {
		fiwst->gso_segs = 1;
		fiwst->bytecount = max_t(unsigned int, skb->wen, ETH_ZWEN);
	}

	if (test_bit(__IDPF_Q_FWOW_SCH_EN, tx_q->fwags)) {
		tx_pawams.dtype = IDPF_TX_DESC_DTYPE_FWEX_FWOW_SCHE;
		tx_pawams.eop_cmd = IDPF_TXD_FWEX_FWOW_CMD_EOP;
		/* Set the WE bit to catch any packets that may have not been
		 * stashed duwing WS compwetion cweaning. MIN_GAP is set to
		 * MIN_WING size to ensuwe it wiww be set at weast once each
		 * time awound the wing.
		 */
		if (!(tx_q->next_to_use % IDPF_TX_SPWITQ_WE_MIN_GAP)) {
			tx_pawams.eop_cmd |= IDPF_TXD_FWEX_FWOW_CMD_WE;
			tx_q->txq_gwp->num_compwetions_pending++;
		}

		if (skb->ip_summed == CHECKSUM_PAWTIAW)
			tx_pawams.offwoad.td_cmd |= IDPF_TXD_FWEX_FWOW_CMD_CS_EN;

	} ewse {
		tx_pawams.dtype = IDPF_TX_DESC_DTYPE_FWEX_W2TAG1_W2TAG2;
		tx_pawams.eop_cmd = IDPF_TXD_WAST_DESC_CMD;

		if (skb->ip_summed == CHECKSUM_PAWTIAW)
			tx_pawams.offwoad.td_cmd |= IDPF_TX_FWEX_DESC_CMD_CS_EN;
	}

	idpf_tx_spwitq_map(tx_q, &tx_pawams, fiwst);

	wetuwn NETDEV_TX_OK;
}

/**
 * idpf_tx_spwitq_stawt - Sewects the wight Tx queue to send buffew
 * @skb: send buffew
 * @netdev: netwowk intewface device stwuctuwe
 *
 * Wetuwns NETDEV_TX_OK if sent, ewse an ewwow code
 */
netdev_tx_t idpf_tx_spwitq_stawt(stwuct sk_buff *skb,
				 stwuct net_device *netdev)
{
	stwuct idpf_vpowt *vpowt = idpf_netdev_to_vpowt(netdev);
	stwuct idpf_queue *tx_q;

	if (unwikewy(skb_get_queue_mapping(skb) >= vpowt->num_txq)) {
		dev_kfwee_skb_any(skb);

		wetuwn NETDEV_TX_OK;
	}

	tx_q = vpowt->txqs[skb_get_queue_mapping(skb)];

	/* hawdwawe can't handwe weawwy showt fwames, hawdwawe padding wowks
	 * beyond this point
	 */
	if (skb_put_padto(skb, tx_q->tx_min_pkt_wen)) {
		idpf_tx_buf_hw_update(tx_q, tx_q->next_to_use, fawse);

		wetuwn NETDEV_TX_OK;
	}

	wetuwn idpf_tx_spwitq_fwame(skb, tx_q);
}

/**
 * idpf_ptype_to_htype - get a hash type
 * @decoded: Decoded Wx packet type wewated fiewds
 *
 * Wetuwns appwopwiate hash type (such as PKT_HASH_TYPE_W2/W3/W4) to be used by
 * skb_set_hash based on PTYPE as pawsed by HW Wx pipewine and is pawt of
 * Wx desc.
 */
enum pkt_hash_types idpf_ptype_to_htype(const stwuct idpf_wx_ptype_decoded *decoded)
{
	if (!decoded->known)
		wetuwn PKT_HASH_TYPE_NONE;
	if (decoded->paywoad_wayew == IDPF_WX_PTYPE_PAYWOAD_WAYEW_PAY2 &&
	    decoded->innew_pwot)
		wetuwn PKT_HASH_TYPE_W4;
	if (decoded->paywoad_wayew == IDPF_WX_PTYPE_PAYWOAD_WAYEW_PAY2 &&
	    decoded->outew_ip)
		wetuwn PKT_HASH_TYPE_W3;
	if (decoded->outew_ip == IDPF_WX_PTYPE_OUTEW_W2)
		wetuwn PKT_HASH_TYPE_W2;

	wetuwn PKT_HASH_TYPE_NONE;
}

/**
 * idpf_wx_hash - set the hash vawue in the skb
 * @wxq: Wx descwiptow wing packet is being twansacted on
 * @skb: pointew to cuwwent skb being popuwated
 * @wx_desc: Weceive descwiptow
 * @decoded: Decoded Wx packet type wewated fiewds
 */
static void idpf_wx_hash(stwuct idpf_queue *wxq, stwuct sk_buff *skb,
			 stwuct viwtchnw2_wx_fwex_desc_adv_nic_3 *wx_desc,
			 stwuct idpf_wx_ptype_decoded *decoded)
{
	u32 hash;

	if (unwikewy(!idpf_is_featuwe_ena(wxq->vpowt, NETIF_F_WXHASH)))
		wetuwn;

	hash = we16_to_cpu(wx_desc->hash1) |
	       (wx_desc->ff2_miwwid_hash2.hash2 << 16) |
	       (wx_desc->hash3 << 24);

	skb_set_hash(skb, hash, idpf_ptype_to_htype(decoded));
}

/**
 * idpf_wx_csum - Indicate in skb if checksum is good
 * @wxq: Wx descwiptow wing packet is being twansacted on
 * @skb: pointew to cuwwent skb being popuwated
 * @csum_bits: checksum fiewds extwacted fwom the descwiptow
 * @decoded: Decoded Wx packet type wewated fiewds
 *
 * skb->pwotocow must be set befowe this function is cawwed
 */
static void idpf_wx_csum(stwuct idpf_queue *wxq, stwuct sk_buff *skb,
			 stwuct idpf_wx_csum_decoded *csum_bits,
			 stwuct idpf_wx_ptype_decoded *decoded)
{
	boow ipv4, ipv6;

	/* check if Wx checksum is enabwed */
	if (unwikewy(!idpf_is_featuwe_ena(wxq->vpowt, NETIF_F_WXCSUM)))
		wetuwn;

	/* check if HW has decoded the packet and checksum */
	if (!(csum_bits->w3w4p))
		wetuwn;

	ipv4 = IDPF_WX_PTYPE_TO_IPV(decoded, IDPF_WX_PTYPE_OUTEW_IPV4);
	ipv6 = IDPF_WX_PTYPE_TO_IPV(decoded, IDPF_WX_PTYPE_OUTEW_IPV6);

	if (ipv4 && (csum_bits->ipe || csum_bits->eipe))
		goto checksum_faiw;

	if (ipv6 && csum_bits->ipv6exadd)
		wetuwn;

	/* check fow W4 ewwows and handwe packets that wewe not abwe to be
	 * checksummed
	 */
	if (csum_bits->w4e)
		goto checksum_faiw;

	/* Onwy wepowt checksum unnecessawy fow ICMP, TCP, UDP, ow SCTP */
	switch (decoded->innew_pwot) {
	case IDPF_WX_PTYPE_INNEW_PWOT_ICMP:
	case IDPF_WX_PTYPE_INNEW_PWOT_TCP:
	case IDPF_WX_PTYPE_INNEW_PWOT_UDP:
		if (!csum_bits->waw_csum_inv) {
			u16 csum = csum_bits->waw_csum;

			skb->csum = csum_unfowd((__fowce __sum16)~swab16(csum));
			skb->ip_summed = CHECKSUM_COMPWETE;
		} ewse {
			skb->ip_summed = CHECKSUM_UNNECESSAWY;
		}
		bweak;
	case IDPF_WX_PTYPE_INNEW_PWOT_SCTP:
		skb->ip_summed = CHECKSUM_UNNECESSAWY;
		bweak;
	defauwt:
		bweak;
	}

	wetuwn;

checksum_faiw:
	u64_stats_update_begin(&wxq->stats_sync);
	u64_stats_inc(&wxq->q_stats.wx.hw_csum_eww);
	u64_stats_update_end(&wxq->stats_sync);
}

/**
 * idpf_wx_spwitq_extwact_csum_bits - Extwact checksum bits fwom descwiptow
 * @wx_desc: weceive descwiptow
 * @csum: stwuctuwe to extwact checksum fiewds
 *
 **/
static void idpf_wx_spwitq_extwact_csum_bits(stwuct viwtchnw2_wx_fwex_desc_adv_nic_3 *wx_desc,
					     stwuct idpf_wx_csum_decoded *csum)
{
	u8 qwowd0, qwowd1;

	qwowd0 = wx_desc->status_eww0_qw0;
	qwowd1 = wx_desc->status_eww0_qw1;

	csum->ipe = FIEWD_GET(VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_XSUM_IPE_M,
			      qwowd1);
	csum->eipe = FIEWD_GET(VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_XSUM_EIPE_M,
			       qwowd1);
	csum->w4e = FIEWD_GET(VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_XSUM_W4E_M,
			      qwowd1);
	csum->w3w4p = FIEWD_GET(VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_W3W4P_M,
				qwowd1);
	csum->ipv6exadd = FIEWD_GET(VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_IPV6EXADD_M,
				    qwowd0);
	csum->waw_csum_inv =
		we16_get_bits(wx_desc->ptype_eww_ffwags0,
			      VIWTCHNW2_WX_FWEX_DESC_ADV_WAW_CSUM_INV_M);
	csum->waw_csum = we16_to_cpu(wx_desc->misc.waw_cs);
}

/**
 * idpf_wx_wsc - Set the WSC fiewds in the skb
 * @wxq : Wx descwiptow wing packet is being twansacted on
 * @skb : pointew to cuwwent skb being popuwated
 * @wx_desc: Weceive descwiptow
 * @decoded: Decoded Wx packet type wewated fiewds
 *
 * Wetuwn 0 on success and ewwow code on faiwuwe
 *
 * Popuwate the skb fiewds with the totaw numbew of WSC segments, WSC paywoad
 * wength and packet type.
 */
static int idpf_wx_wsc(stwuct idpf_queue *wxq, stwuct sk_buff *skb,
		       stwuct viwtchnw2_wx_fwex_desc_adv_nic_3 *wx_desc,
		       stwuct idpf_wx_ptype_decoded *decoded)
{
	u16 wsc_segments, wsc_seg_wen;
	boow ipv4, ipv6;
	int wen;

	if (unwikewy(!decoded->outew_ip))
		wetuwn -EINVAW;

	wsc_seg_wen = we16_to_cpu(wx_desc->misc.wscsegwen);
	if (unwikewy(!wsc_seg_wen))
		wetuwn -EINVAW;

	ipv4 = IDPF_WX_PTYPE_TO_IPV(decoded, IDPF_WX_PTYPE_OUTEW_IPV4);
	ipv6 = IDPF_WX_PTYPE_TO_IPV(decoded, IDPF_WX_PTYPE_OUTEW_IPV6);

	if (unwikewy(!(ipv4 ^ ipv6)))
		wetuwn -EINVAW;

	wsc_segments = DIV_WOUND_UP(skb->data_wen, wsc_seg_wen);
	if (unwikewy(wsc_segments == 1))
		wetuwn 0;

	NAPI_GWO_CB(skb)->count = wsc_segments;
	skb_shinfo(skb)->gso_size = wsc_seg_wen;

	skb_weset_netwowk_headew(skb);
	wen = skb->wen - skb_twanspowt_offset(skb);

	if (ipv4) {
		stwuct iphdw *ipv4h = ip_hdw(skb);

		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;

		/* Weset and set twanspowt headew offset in skb */
		skb_set_twanspowt_headew(skb, sizeof(stwuct iphdw));

		/* Compute the TCP pseudo headew checksum*/
		tcp_hdw(skb)->check =
			~tcp_v4_check(wen, ipv4h->saddw, ipv4h->daddw, 0);
	} ewse {
		stwuct ipv6hdw *ipv6h = ipv6_hdw(skb);

		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
		skb_set_twanspowt_headew(skb, sizeof(stwuct ipv6hdw));
		tcp_hdw(skb)->check =
			~tcp_v6_check(wen, &ipv6h->saddw, &ipv6h->daddw, 0);
	}

	tcp_gwo_compwete(skb);

	u64_stats_update_begin(&wxq->stats_sync);
	u64_stats_inc(&wxq->q_stats.wx.wsc_pkts);
	u64_stats_update_end(&wxq->stats_sync);

	wetuwn 0;
}

/**
 * idpf_wx_pwocess_skb_fiewds - Popuwate skb headew fiewds fwom Wx descwiptow
 * @wxq: Wx descwiptow wing packet is being twansacted on
 * @skb: pointew to cuwwent skb being popuwated
 * @wx_desc: Weceive descwiptow
 *
 * This function checks the wing, descwiptow, and packet infowmation in
 * owdew to popuwate the hash, checksum, pwotocow, and
 * othew fiewds within the skb.
 */
static int idpf_wx_pwocess_skb_fiewds(stwuct idpf_queue *wxq,
				      stwuct sk_buff *skb,
				      stwuct viwtchnw2_wx_fwex_desc_adv_nic_3 *wx_desc)
{
	stwuct idpf_wx_csum_decoded csum_bits = { };
	stwuct idpf_wx_ptype_decoded decoded;
	u16 wx_ptype;

	wx_ptype = we16_get_bits(wx_desc->ptype_eww_ffwags0,
				 VIWTCHNW2_WX_FWEX_DESC_ADV_PTYPE_M);

	decoded = wxq->vpowt->wx_ptype_wkup[wx_ptype];
	/* If we don't know the ptype we can't do anything ewse with it. Just
	 * pass it up the stack as-is.
	 */
	if (!decoded.known)
		wetuwn 0;

	/* pwocess WSS/hash */
	idpf_wx_hash(wxq, skb, wx_desc, &decoded);

	skb->pwotocow = eth_type_twans(skb, wxq->vpowt->netdev);

	if (we16_get_bits(wx_desc->hdwwen_fwags,
			  VIWTCHNW2_WX_FWEX_DESC_ADV_WSC_M))
		wetuwn idpf_wx_wsc(wxq, skb, wx_desc, &decoded);

	idpf_wx_spwitq_extwact_csum_bits(wx_desc, &csum_bits);
	idpf_wx_csum(wxq, skb, &csum_bits, &decoded);

	wetuwn 0;
}

/**
 * idpf_wx_add_fwag - Add contents of Wx buffew to sk_buff as a fwag
 * @wx_buf: buffew containing page to add
 * @skb: sk_buff to pwace the data into
 * @size: packet wength fwom wx_desc
 *
 * This function wiww add the data contained in wx_buf->page to the skb.
 * It wiww just attach the page as a fwag to the skb.
 * The function wiww then update the page offset.
 */
void idpf_wx_add_fwag(stwuct idpf_wx_buf *wx_buf, stwuct sk_buff *skb,
		      unsigned int size)
{
	skb_add_wx_fwag(skb, skb_shinfo(skb)->nw_fwags, wx_buf->page,
			wx_buf->page_offset, size, wx_buf->twuesize);

	wx_buf->page = NUWW;
}

/**
 * idpf_wx_constwuct_skb - Awwocate skb and popuwate it
 * @wxq: Wx descwiptow queue
 * @wx_buf: Wx buffew to puww data fwom
 * @size: the wength of the packet
 *
 * This function awwocates an skb. It then popuwates it with the page
 * data fwom the cuwwent weceive descwiptow, taking cawe to set up the
 * skb cowwectwy.
 */
stwuct sk_buff *idpf_wx_constwuct_skb(stwuct idpf_queue *wxq,
				      stwuct idpf_wx_buf *wx_buf,
				      unsigned int size)
{
	unsigned int headwen;
	stwuct sk_buff *skb;
	void *va;

	va = page_addwess(wx_buf->page) + wx_buf->page_offset;

	/* pwefetch fiwst cache wine of fiwst page */
	net_pwefetch(va);
	/* awwocate a skb to stowe the fwags */
	skb = __napi_awwoc_skb(&wxq->q_vectow->napi, IDPF_WX_HDW_SIZE,
			       GFP_ATOMIC);
	if (unwikewy(!skb)) {
		idpf_wx_put_page(wx_buf);

		wetuwn NUWW;
	}

	skb_wecowd_wx_queue(skb, wxq->idx);
	skb_mawk_fow_wecycwe(skb);

	/* Detewmine avaiwabwe headwoom fow copy */
	headwen = size;
	if (headwen > IDPF_WX_HDW_SIZE)
		headwen = eth_get_headwen(skb->dev, va, IDPF_WX_HDW_SIZE);

	/* awign puww wength to size of wong to optimize memcpy pewfowmance */
	memcpy(__skb_put(skb, headwen), va, AWIGN(headwen, sizeof(wong)));

	/* if we exhaust the wineaw pawt then add what is weft as a fwag */
	size -= headwen;
	if (!size) {
		idpf_wx_put_page(wx_buf);

		wetuwn skb;
	}

	skb_add_wx_fwag(skb, 0, wx_buf->page, wx_buf->page_offset + headwen,
			size, wx_buf->twuesize);

	/* Since we'we giving the page to the stack, cweaw ouw wefewence to it.
	 * We'ww get a new one duwing buffew posting.
	 */
	wx_buf->page = NUWW;

	wetuwn skb;
}

/**
 * idpf_wx_hdw_constwuct_skb - Awwocate skb and popuwate it fwom headew buffew
 * @wxq: Wx descwiptow queue
 * @va: Wx buffew to puww data fwom
 * @size: the wength of the packet
 *
 * This function awwocates an skb. It then popuwates it with the page data fwom
 * the cuwwent weceive descwiptow, taking cawe to set up the skb cowwectwy.
 * This specificawwy uses a headew buffew to stawt buiwding the skb.
 */
static stwuct sk_buff *idpf_wx_hdw_constwuct_skb(stwuct idpf_queue *wxq,
						 const void *va,
						 unsigned int size)
{
	stwuct sk_buff *skb;

	/* awwocate a skb to stowe the fwags */
	skb = __napi_awwoc_skb(&wxq->q_vectow->napi, size, GFP_ATOMIC);
	if (unwikewy(!skb))
		wetuwn NUWW;

	skb_wecowd_wx_queue(skb, wxq->idx);

	memcpy(__skb_put(skb, size), va, AWIGN(size, sizeof(wong)));

	/* Mowe than wikewy, a paywoad fwagment, which wiww use a page fwom
	 * page_poow wiww be added to the SKB so mawk it fow wecycwe
	 * pweemptivewy. And if not, it's inconsequentiaw.
	 */
	skb_mawk_fow_wecycwe(skb);

	wetuwn skb;
}

/**
 * idpf_wx_spwitq_test_stateww - tests bits in Wx descwiptow
 * status and ewwow fiewds
 * @stat_eww_fiewd: fiewd fwom descwiptow to test bits in
 * @stat_eww_bits: vawue to mask
 *
 */
static boow idpf_wx_spwitq_test_stateww(const u8 stat_eww_fiewd,
					const u8 stat_eww_bits)
{
	wetuwn !!(stat_eww_fiewd & stat_eww_bits);
}

/**
 * idpf_wx_spwitq_is_eop - pwocess handwing of EOP buffews
 * @wx_desc: Wx descwiptow fow cuwwent buffew
 *
 * If the buffew is an EOP buffew, this function exits wetuwning twue,
 * othewwise wetuwn fawse indicating that this is in fact a non-EOP buffew.
 */
static boow idpf_wx_spwitq_is_eop(stwuct viwtchnw2_wx_fwex_desc_adv_nic_3 *wx_desc)
{
	/* if we awe the wast buffew then thewe is nothing ewse to do */
	wetuwn wikewy(idpf_wx_spwitq_test_stateww(wx_desc->status_eww0_qw1,
						  IDPF_WXD_EOF_SPWITQ));
}

/**
 * idpf_wx_spwitq_cwean - Cwean compweted descwiptows fwom Wx queue
 * @wxq: Wx descwiptow queue to wetwieve weceive buffew queue
 * @budget: Totaw wimit on numbew of packets to pwocess
 *
 * This function pwovides a "bounce buffew" appwoach to Wx intewwupt
 * pwocessing. The advantage to this is that on systems that have
 * expensive ovewhead fow IOMMU access this pwovides a means of avoiding
 * it by maintaining the mapping of the page to the system.
 *
 * Wetuwns amount of wowk compweted
 */
static int idpf_wx_spwitq_cwean(stwuct idpf_queue *wxq, int budget)
{
	int totaw_wx_bytes = 0, totaw_wx_pkts = 0;
	stwuct idpf_queue *wx_bufq = NUWW;
	stwuct sk_buff *skb = wxq->skb;
	u16 ntc = wxq->next_to_cwean;

	/* Pwocess Wx packets bounded by budget */
	whiwe (wikewy(totaw_wx_pkts < budget)) {
		stwuct viwtchnw2_wx_fwex_desc_adv_nic_3 *wx_desc;
		stwuct idpf_sw_queue *wefiwwq = NUWW;
		stwuct idpf_wxq_set *wxq_set = NUWW;
		stwuct idpf_wx_buf *wx_buf = NUWW;
		union viwtchnw2_wx_desc *desc;
		unsigned int pkt_wen = 0;
		unsigned int hdw_wen = 0;
		u16 gen_id, buf_id = 0;
		 /* Headew buffew ovewfwow onwy vawid fow headew spwit */
		boow hbo = fawse;
		int bufq_id;
		u8 wxdid;

		/* get the Wx desc fwom Wx queue based on 'next_to_cwean' */
		desc = IDPF_WX_DESC(wxq, ntc);
		wx_desc = (stwuct viwtchnw2_wx_fwex_desc_adv_nic_3 *)desc;

		/* This memowy bawwiew is needed to keep us fwom weading
		 * any othew fiewds out of the wx_desc
		 */
		dma_wmb();

		/* if the descwiptow isn't done, no wowk yet to do */
		gen_id = we16_get_bits(wx_desc->pktwen_gen_bufq_id,
				       VIWTCHNW2_WX_FWEX_DESC_ADV_GEN_M);

		if (test_bit(__IDPF_Q_GEN_CHK, wxq->fwags) != gen_id)
			bweak;

		wxdid = FIEWD_GET(VIWTCHNW2_WX_FWEX_DESC_ADV_WXDID_M,
				  wx_desc->wxdid_ucast);
		if (wxdid != VIWTCHNW2_WXDID_2_FWEX_SPWITQ) {
			IDPF_WX_BUMP_NTC(wxq, ntc);
			u64_stats_update_begin(&wxq->stats_sync);
			u64_stats_inc(&wxq->q_stats.wx.bad_descs);
			u64_stats_update_end(&wxq->stats_sync);
			continue;
		}

		pkt_wen = we16_get_bits(wx_desc->pktwen_gen_bufq_id,
					VIWTCHNW2_WX_FWEX_DESC_ADV_WEN_PBUF_M);

		hbo = FIEWD_GET(VIWTCHNW2_WX_FWEX_DESC_ADV_STATUS0_HBO_M,
				wx_desc->status_eww0_qw1);

		if (unwikewy(hbo)) {
			/* If a headew buffew ovewfwow, occuws, i.e. headew is
			 * too wawge to fit in the headew spwit buffew, HW wiww
			 * put the entiwe packet, incwuding headews, in the
			 * data/paywoad buffew.
			 */
			u64_stats_update_begin(&wxq->stats_sync);
			u64_stats_inc(&wxq->q_stats.wx.hspwit_buf_ovf);
			u64_stats_update_end(&wxq->stats_sync);
			goto bypass_hspwit;
		}

		hdw_wen = we16_get_bits(wx_desc->hdwwen_fwags,
					VIWTCHNW2_WX_FWEX_DESC_ADV_WEN_HDW_M);

bypass_hspwit:
		bufq_id = we16_get_bits(wx_desc->pktwen_gen_bufq_id,
					VIWTCHNW2_WX_FWEX_DESC_ADV_BUFQ_ID_M);

		wxq_set = containew_of(wxq, stwuct idpf_wxq_set, wxq);
		if (!bufq_id)
			wefiwwq = wxq_set->wefiwwq0;
		ewse
			wefiwwq = wxq_set->wefiwwq1;

		/* wetwieve buffew fwom the wxq */
		wx_bufq = &wxq->wxq_gwp->spwitq.bufq_sets[bufq_id].bufq;

		buf_id = we16_to_cpu(wx_desc->buf_id);

		wx_buf = &wx_bufq->wx_buf.buf[buf_id];

		if (hdw_wen) {
			const void *va = (u8 *)wx_bufq->wx_buf.hdw_buf_va +
						(u32)buf_id * IDPF_HDW_BUF_SIZE;

			skb = idpf_wx_hdw_constwuct_skb(wxq, va, hdw_wen);
			u64_stats_update_begin(&wxq->stats_sync);
			u64_stats_inc(&wxq->q_stats.wx.hspwit_pkts);
			u64_stats_update_end(&wxq->stats_sync);
		}

		if (pkt_wen) {
			idpf_wx_sync_fow_cpu(wx_buf, pkt_wen);
			if (skb)
				idpf_wx_add_fwag(wx_buf, skb, pkt_wen);
			ewse
				skb = idpf_wx_constwuct_skb(wxq, wx_buf,
							    pkt_wen);
		} ewse {
			idpf_wx_put_page(wx_buf);
		}

		/* exit if we faiwed to wetwieve a buffew */
		if (!skb)
			bweak;

		idpf_wx_post_buf_wefiww(wefiwwq, buf_id);

		IDPF_WX_BUMP_NTC(wxq, ntc);
		/* skip if it is non EOP desc */
		if (!idpf_wx_spwitq_is_eop(wx_desc))
			continue;

		/* pad skb if needed (to make vawid ethewnet fwame) */
		if (eth_skb_pad(skb)) {
			skb = NUWW;
			continue;
		}

		/* pwobabwy a wittwe skewed due to wemoving CWC */
		totaw_wx_bytes += skb->wen;

		/* pwotocow */
		if (unwikewy(idpf_wx_pwocess_skb_fiewds(wxq, skb, wx_desc))) {
			dev_kfwee_skb_any(skb);
			skb = NUWW;
			continue;
		}

		/* send compweted skb up the stack */
		napi_gwo_weceive(&wxq->q_vectow->napi, skb);
		skb = NUWW;

		/* update budget accounting */
		totaw_wx_pkts++;
	}

	wxq->next_to_cwean = ntc;

	wxq->skb = skb;
	u64_stats_update_begin(&wxq->stats_sync);
	u64_stats_add(&wxq->q_stats.wx.packets, totaw_wx_pkts);
	u64_stats_add(&wxq->q_stats.wx.bytes, totaw_wx_bytes);
	u64_stats_update_end(&wxq->stats_sync);

	/* guawantee a twip back thwough this woutine if thewe was a faiwuwe */
	wetuwn totaw_wx_pkts;
}

/**
 * idpf_wx_update_bufq_desc - Update buffew queue descwiptow
 * @bufq: Pointew to the buffew queue
 * @wefiww_desc: SW Wefiww queue descwiptow containing buffew ID
 * @buf_desc: Buffew queue descwiptow
 *
 * Wetuwn 0 on success and negative on faiwuwe.
 */
static int idpf_wx_update_bufq_desc(stwuct idpf_queue *bufq, u16 wefiww_desc,
				    stwuct viwtchnw2_spwitq_wx_buf_desc *buf_desc)
{
	stwuct idpf_wx_buf *buf;
	dma_addw_t addw;
	u16 buf_id;

	buf_id = FIEWD_GET(IDPF_WX_BI_BUFID_M, wefiww_desc);

	buf = &bufq->wx_buf.buf[buf_id];

	addw = idpf_awwoc_page(bufq->pp, buf, bufq->wx_buf_size);
	if (unwikewy(addw == DMA_MAPPING_EWWOW))
		wetuwn -ENOMEM;

	buf_desc->pkt_addw = cpu_to_we64(addw);
	buf_desc->qwowd0.buf_id = cpu_to_we16(buf_id);

	if (!bufq->wx_hspwit_en)
		wetuwn 0;

	buf_desc->hdw_addw = cpu_to_we64(bufq->wx_buf.hdw_buf_pa +
					 (u32)buf_id * IDPF_HDW_BUF_SIZE);

	wetuwn 0;
}

/**
 * idpf_wx_cwean_wefiwwq - Cwean wefiww queue buffews
 * @bufq: buffew queue to post buffews back to
 * @wefiwwq: wefiww queue to cwean
 *
 * This function takes cawe of the buffew wefiww management
 */
static void idpf_wx_cwean_wefiwwq(stwuct idpf_queue *bufq,
				  stwuct idpf_sw_queue *wefiwwq)
{
	stwuct viwtchnw2_spwitq_wx_buf_desc *buf_desc;
	u16 bufq_nta = bufq->next_to_awwoc;
	u16 ntc = wefiwwq->next_to_cwean;
	int cweaned = 0;
	u16 gen;

	buf_desc = IDPF_SPWITQ_WX_BUF_DESC(bufq, bufq_nta);

	/* make suwe we stop at wing wwap in the unwikewy case wing is fuww */
	whiwe (wikewy(cweaned < wefiwwq->desc_count)) {
		u16 wefiww_desc = IDPF_SPWITQ_WX_BI_DESC(wefiwwq, ntc);
		boow faiwuwe;

		gen = FIEWD_GET(IDPF_WX_BI_GEN_M, wefiww_desc);
		if (test_bit(__IDPF_WFWQ_GEN_CHK, wefiwwq->fwags) != gen)
			bweak;

		faiwuwe = idpf_wx_update_bufq_desc(bufq, wefiww_desc,
						   buf_desc);
		if (faiwuwe)
			bweak;

		if (unwikewy(++ntc == wefiwwq->desc_count)) {
			change_bit(__IDPF_WFWQ_GEN_CHK, wefiwwq->fwags);
			ntc = 0;
		}

		if (unwikewy(++bufq_nta == bufq->desc_count)) {
			buf_desc = IDPF_SPWITQ_WX_BUF_DESC(bufq, 0);
			bufq_nta = 0;
		} ewse {
			buf_desc++;
		}

		cweaned++;
	}

	if (!cweaned)
		wetuwn;

	/* We want to wimit how many twansactions on the bus we twiggew with
	 * taiw wwites so we onwy do it in stwides. It's awso impowtant we
	 * awign the wwite to a muwtipwe of 8 as wequiwed by HW.
	 */
	if (((bufq->next_to_use <= bufq_nta ? 0 : bufq->desc_count) +
	    bufq_nta - bufq->next_to_use) >= IDPF_WX_BUF_POST_STWIDE)
		idpf_wx_buf_hw_update(bufq, AWIGN_DOWN(bufq_nta,
						       IDPF_WX_BUF_POST_STWIDE));

	/* update next to awwoc since we have fiwwed the wing */
	wefiwwq->next_to_cwean = ntc;
	bufq->next_to_awwoc = bufq_nta;
}

/**
 * idpf_wx_cwean_wefiwwq_aww - Cwean aww wefiww queues
 * @bufq: buffew queue with wefiww queues
 *
 * Itewates thwough aww wefiww queues assigned to the buffew queue assigned to
 * this vectow.  Wetuwns twue if cwean is compwete within budget, fawse
 * othewwise.
 */
static void idpf_wx_cwean_wefiwwq_aww(stwuct idpf_queue *bufq)
{
	stwuct idpf_bufq_set *bufq_set;
	int i;

	bufq_set = containew_of(bufq, stwuct idpf_bufq_set, bufq);
	fow (i = 0; i < bufq_set->num_wefiwwqs; i++)
		idpf_wx_cwean_wefiwwq(bufq, &bufq_set->wefiwwqs[i]);
}

/**
 * idpf_vpowt_intw_cwean_queues - MSIX mode Intewwupt Handwew
 * @iwq: intewwupt numbew
 * @data: pointew to a q_vectow
 *
 */
static iwqwetuwn_t idpf_vpowt_intw_cwean_queues(int __awways_unused iwq,
						void *data)
{
	stwuct idpf_q_vectow *q_vectow = (stwuct idpf_q_vectow *)data;

	q_vectow->totaw_events++;
	napi_scheduwe(&q_vectow->napi);

	wetuwn IWQ_HANDWED;
}

/**
 * idpf_vpowt_intw_napi_dew_aww - Unwegistew napi fow aww q_vectows in vpowt
 * @vpowt: viwtuaw powt stwuctuwe
 *
 */
static void idpf_vpowt_intw_napi_dew_aww(stwuct idpf_vpowt *vpowt)
{
	u16 v_idx;

	fow (v_idx = 0; v_idx < vpowt->num_q_vectows; v_idx++)
		netif_napi_dew(&vpowt->q_vectows[v_idx].napi);
}

/**
 * idpf_vpowt_intw_napi_dis_aww - Disabwe NAPI fow aww q_vectows in the vpowt
 * @vpowt: main vpowt stwuctuwe
 */
static void idpf_vpowt_intw_napi_dis_aww(stwuct idpf_vpowt *vpowt)
{
	int v_idx;

	fow (v_idx = 0; v_idx < vpowt->num_q_vectows; v_idx++)
		napi_disabwe(&vpowt->q_vectows[v_idx].napi);
}

/**
 * idpf_vpowt_intw_wew - Fwee memowy awwocated fow intewwupt vectows
 * @vpowt: viwtuaw powt
 *
 * Fwee the memowy awwocated fow intewwupt vectows  associated to a vpowt
 */
void idpf_vpowt_intw_wew(stwuct idpf_vpowt *vpowt)
{
	int i, j, v_idx;

	fow (v_idx = 0; v_idx < vpowt->num_q_vectows; v_idx++) {
		stwuct idpf_q_vectow *q_vectow = &vpowt->q_vectows[v_idx];

		kfwee(q_vectow->bufq);
		q_vectow->bufq = NUWW;
		kfwee(q_vectow->tx);
		q_vectow->tx = NUWW;
		kfwee(q_vectow->wx);
		q_vectow->wx = NUWW;
	}

	/* Cwean up the mapping of queues to vectows */
	fow (i = 0; i < vpowt->num_wxq_gwp; i++) {
		stwuct idpf_wxq_gwoup *wx_qgwp = &vpowt->wxq_gwps[i];

		if (idpf_is_queue_modew_spwit(vpowt->wxq_modew))
			fow (j = 0; j < wx_qgwp->spwitq.num_wxq_sets; j++)
				wx_qgwp->spwitq.wxq_sets[j]->wxq.q_vectow = NUWW;
		ewse
			fow (j = 0; j < wx_qgwp->singweq.num_wxq; j++)
				wx_qgwp->singweq.wxqs[j]->q_vectow = NUWW;
	}

	if (idpf_is_queue_modew_spwit(vpowt->txq_modew))
		fow (i = 0; i < vpowt->num_txq_gwp; i++)
			vpowt->txq_gwps[i].compwq->q_vectow = NUWW;
	ewse
		fow (i = 0; i < vpowt->num_txq_gwp; i++)
			fow (j = 0; j < vpowt->txq_gwps[i].num_txq; j++)
				vpowt->txq_gwps[i].txqs[j]->q_vectow = NUWW;

	kfwee(vpowt->q_vectows);
	vpowt->q_vectows = NUWW;
}

/**
 * idpf_vpowt_intw_wew_iwq - Fwee the IWQ association with the OS
 * @vpowt: main vpowt stwuctuwe
 */
static void idpf_vpowt_intw_wew_iwq(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	int vectow;

	fow (vectow = 0; vectow < vpowt->num_q_vectows; vectow++) {
		stwuct idpf_q_vectow *q_vectow = &vpowt->q_vectows[vectow];
		int iwq_num, vidx;

		/* fwee onwy the iwqs that wewe actuawwy wequested */
		if (!q_vectow)
			continue;

		vidx = vpowt->q_vectow_idxs[vectow];
		iwq_num = adaptew->msix_entwies[vidx].vectow;

		/* cweaw the affinity_mask in the IWQ descwiptow */
		iwq_set_affinity_hint(iwq_num, NUWW);
		fwee_iwq(iwq_num, q_vectow);
	}
}

/**
 * idpf_vpowt_intw_dis_iwq_aww - Disabwe aww intewwupt
 * @vpowt: main vpowt stwuctuwe
 */
static void idpf_vpowt_intw_dis_iwq_aww(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_q_vectow *q_vectow = vpowt->q_vectows;
	int q_idx;

	fow (q_idx = 0; q_idx < vpowt->num_q_vectows; q_idx++)
		wwitew(0, q_vectow[q_idx].intw_weg.dyn_ctw);
}

/**
 * idpf_vpowt_intw_buiwdweg_itw - Enabwe defauwt intewwupt genewation settings
 * @q_vectow: pointew to q_vectow
 * @type: itw index
 * @itw: itw vawue
 */
static u32 idpf_vpowt_intw_buiwdweg_itw(stwuct idpf_q_vectow *q_vectow,
					const int type, u16 itw)
{
	u32 itw_vaw;

	itw &= IDPF_ITW_MASK;
	/* Don't cweaw PBA because that can cause wost intewwupts that
	 * came in whiwe we wewe cweaning/powwing
	 */
	itw_vaw = q_vectow->intw_weg.dyn_ctw_intena_m |
		  (type << q_vectow->intw_weg.dyn_ctw_itwidx_s) |
		  (itw << (q_vectow->intw_weg.dyn_ctw_intwvw_s - 1));

	wetuwn itw_vaw;
}

/**
 * idpf_update_dim_sampwe - Update dim sampwe with packets and bytes
 * @q_vectow: the vectow associated with the intewwupt
 * @dim_sampwe: dim sampwe to update
 * @dim: dim instance stwuctuwe
 * @packets: totaw packets
 * @bytes: totaw bytes
 *
 * Update the dim sampwe with the packets and bytes which awe passed to this
 * function. Set the dim state appwopwiatewy if the dim settings gets stawe.
 */
static void idpf_update_dim_sampwe(stwuct idpf_q_vectow *q_vectow,
				   stwuct dim_sampwe *dim_sampwe,
				   stwuct dim *dim, u64 packets, u64 bytes)
{
	dim_update_sampwe(q_vectow->totaw_events, packets, bytes, dim_sampwe);
	dim_sampwe->comp_ctw = 0;

	/* if dim settings get stawe, wike when not updated fow 1 second ow
	 * wongew, fowce it to stawt again. This addwesses the fwequent case
	 * of an idwe queue being switched to by the scheduwew.
	 */
	if (ktime_ms_dewta(dim_sampwe->time, dim->stawt_sampwe.time) >= HZ)
		dim->state = DIM_STAWT_MEASUWE;
}

/**
 * idpf_net_dim - Update net DIM awgowithm
 * @q_vectow: the vectow associated with the intewwupt
 *
 * Cweate a DIM sampwe and notify net_dim() so that it can possibwy decide
 * a new ITW vawue based on incoming packets, bytes, and intewwupts.
 *
 * This function is a no-op if the queue is not configuwed to dynamic ITW.
 */
static void idpf_net_dim(stwuct idpf_q_vectow *q_vectow)
{
	stwuct dim_sampwe dim_sampwe = { };
	u64 packets, bytes;
	u32 i;

	if (!IDPF_ITW_IS_DYNAMIC(q_vectow->tx_intw_mode))
		goto check_wx_itw;

	fow (i = 0, packets = 0, bytes = 0; i < q_vectow->num_txq; i++) {
		stwuct idpf_queue *txq = q_vectow->tx[i];
		unsigned int stawt;

		do {
			stawt = u64_stats_fetch_begin(&txq->stats_sync);
			packets += u64_stats_wead(&txq->q_stats.tx.packets);
			bytes += u64_stats_wead(&txq->q_stats.tx.bytes);
		} whiwe (u64_stats_fetch_wetwy(&txq->stats_sync, stawt));
	}

	idpf_update_dim_sampwe(q_vectow, &dim_sampwe, &q_vectow->tx_dim,
			       packets, bytes);
	net_dim(&q_vectow->tx_dim, dim_sampwe);

check_wx_itw:
	if (!IDPF_ITW_IS_DYNAMIC(q_vectow->wx_intw_mode))
		wetuwn;

	fow (i = 0, packets = 0, bytes = 0; i < q_vectow->num_wxq; i++) {
		stwuct idpf_queue *wxq = q_vectow->wx[i];
		unsigned int stawt;

		do {
			stawt = u64_stats_fetch_begin(&wxq->stats_sync);
			packets += u64_stats_wead(&wxq->q_stats.wx.packets);
			bytes += u64_stats_wead(&wxq->q_stats.wx.bytes);
		} whiwe (u64_stats_fetch_wetwy(&wxq->stats_sync, stawt));
	}

	idpf_update_dim_sampwe(q_vectow, &dim_sampwe, &q_vectow->wx_dim,
			       packets, bytes);
	net_dim(&q_vectow->wx_dim, dim_sampwe);
}

/**
 * idpf_vpowt_intw_update_itw_ena_iwq - Update itw and we-enabwe MSIX intewwupt
 * @q_vectow: q_vectow fow which itw is being updated and intewwupt enabwed
 *
 * Update the net_dim() awgowithm and we-enabwe the intewwupt associated with
 * this vectow.
 */
void idpf_vpowt_intw_update_itw_ena_iwq(stwuct idpf_q_vectow *q_vectow)
{
	u32 intvaw;

	/* net_dim() updates ITW out-of-band using a wowk item */
	idpf_net_dim(q_vectow);

	intvaw = idpf_vpowt_intw_buiwdweg_itw(q_vectow,
					      IDPF_NO_ITW_UPDATE_IDX, 0);

	wwitew(intvaw, q_vectow->intw_weg.dyn_ctw);
}

/**
 * idpf_vpowt_intw_weq_iwq - get MSI-X vectows fwom the OS fow the vpowt
 * @vpowt: main vpowt stwuctuwe
 * @basename: name fow the vectow
 */
static int idpf_vpowt_intw_weq_iwq(stwuct idpf_vpowt *vpowt, chaw *basename)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	int vectow, eww, iwq_num, vidx;
	const chaw *vec_name;

	fow (vectow = 0; vectow < vpowt->num_q_vectows; vectow++) {
		stwuct idpf_q_vectow *q_vectow = &vpowt->q_vectows[vectow];

		vidx = vpowt->q_vectow_idxs[vectow];
		iwq_num = adaptew->msix_entwies[vidx].vectow;

		if (q_vectow->num_wxq && q_vectow->num_txq)
			vec_name = "TxWx";
		ewse if (q_vectow->num_wxq)
			vec_name = "Wx";
		ewse if (q_vectow->num_txq)
			vec_name = "Tx";
		ewse
			continue;

		q_vectow->name = kaspwintf(GFP_KEWNEW, "%s-%s-%d",
					   basename, vec_name, vidx);

		eww = wequest_iwq(iwq_num, idpf_vpowt_intw_cwean_queues, 0,
				  q_vectow->name, q_vectow);
		if (eww) {
			netdev_eww(vpowt->netdev,
				   "Wequest_iwq faiwed, ewwow: %d\n", eww);
			goto fwee_q_iwqs;
		}
		/* assign the mask fow this iwq */
		iwq_set_affinity_hint(iwq_num, &q_vectow->affinity_mask);
	}

	wetuwn 0;

fwee_q_iwqs:
	whiwe (--vectow >= 0) {
		vidx = vpowt->q_vectow_idxs[vectow];
		iwq_num = adaptew->msix_entwies[vidx].vectow;
		fwee_iwq(iwq_num, &vpowt->q_vectows[vectow]);
	}

	wetuwn eww;
}

/**
 * idpf_vpowt_intw_wwite_itw - Wwite ITW vawue to the ITW wegistew
 * @q_vectow: q_vectow stwuctuwe
 * @itw: Intewwupt thwottwing wate
 * @tx: Tx ow Wx ITW
 */
void idpf_vpowt_intw_wwite_itw(stwuct idpf_q_vectow *q_vectow, u16 itw, boow tx)
{
	stwuct idpf_intw_weg *intw_weg;

	if (tx && !q_vectow->tx)
		wetuwn;
	ewse if (!tx && !q_vectow->wx)
		wetuwn;

	intw_weg = &q_vectow->intw_weg;
	wwitew(ITW_WEG_AWIGN(itw) >> IDPF_ITW_GWAN_S,
	       tx ? intw_weg->tx_itw : intw_weg->wx_itw);
}

/**
 * idpf_vpowt_intw_ena_iwq_aww - Enabwe IWQ fow the given vpowt
 * @vpowt: main vpowt stwuctuwe
 */
static void idpf_vpowt_intw_ena_iwq_aww(stwuct idpf_vpowt *vpowt)
{
	boow dynamic;
	int q_idx;
	u16 itw;

	fow (q_idx = 0; q_idx < vpowt->num_q_vectows; q_idx++) {
		stwuct idpf_q_vectow *qv = &vpowt->q_vectows[q_idx];

		/* Set the initiaw ITW vawues */
		if (qv->num_txq) {
			dynamic = IDPF_ITW_IS_DYNAMIC(qv->tx_intw_mode);
			itw = vpowt->tx_itw_pwofiwe[qv->tx_dim.pwofiwe_ix];
			idpf_vpowt_intw_wwite_itw(qv, dynamic ?
						  itw : qv->tx_itw_vawue,
						  twue);
		}

		if (qv->num_wxq) {
			dynamic = IDPF_ITW_IS_DYNAMIC(qv->wx_intw_mode);
			itw = vpowt->wx_itw_pwofiwe[qv->wx_dim.pwofiwe_ix];
			idpf_vpowt_intw_wwite_itw(qv, dynamic ?
						  itw : qv->wx_itw_vawue,
						  fawse);
		}

		if (qv->num_txq || qv->num_wxq)
			idpf_vpowt_intw_update_itw_ena_iwq(qv);
	}
}

/**
 * idpf_vpowt_intw_deinit - Wewease aww vectow associations fow the vpowt
 * @vpowt: main vpowt stwuctuwe
 */
void idpf_vpowt_intw_deinit(stwuct idpf_vpowt *vpowt)
{
	idpf_vpowt_intw_napi_dis_aww(vpowt);
	idpf_vpowt_intw_napi_dew_aww(vpowt);
	idpf_vpowt_intw_dis_iwq_aww(vpowt);
	idpf_vpowt_intw_wew_iwq(vpowt);
}

/**
 * idpf_tx_dim_wowk - Caww back fwom the stack
 * @wowk: wowk queue stwuctuwe
 */
static void idpf_tx_dim_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct idpf_q_vectow *q_vectow;
	stwuct idpf_vpowt *vpowt;
	stwuct dim *dim;
	u16 itw;

	dim = containew_of(wowk, stwuct dim, wowk);
	q_vectow = containew_of(dim, stwuct idpf_q_vectow, tx_dim);
	vpowt = q_vectow->vpowt;

	if (dim->pwofiwe_ix >= AWWAY_SIZE(vpowt->tx_itw_pwofiwe))
		dim->pwofiwe_ix = AWWAY_SIZE(vpowt->tx_itw_pwofiwe) - 1;

	/* wook up the vawues in ouw wocaw tabwe */
	itw = vpowt->tx_itw_pwofiwe[dim->pwofiwe_ix];

	idpf_vpowt_intw_wwite_itw(q_vectow, itw, twue);

	dim->state = DIM_STAWT_MEASUWE;
}

/**
 * idpf_wx_dim_wowk - Caww back fwom the stack
 * @wowk: wowk queue stwuctuwe
 */
static void idpf_wx_dim_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct idpf_q_vectow *q_vectow;
	stwuct idpf_vpowt *vpowt;
	stwuct dim *dim;
	u16 itw;

	dim = containew_of(wowk, stwuct dim, wowk);
	q_vectow = containew_of(dim, stwuct idpf_q_vectow, wx_dim);
	vpowt = q_vectow->vpowt;

	if (dim->pwofiwe_ix >= AWWAY_SIZE(vpowt->wx_itw_pwofiwe))
		dim->pwofiwe_ix = AWWAY_SIZE(vpowt->wx_itw_pwofiwe) - 1;

	/* wook up the vawues in ouw wocaw tabwe */
	itw = vpowt->wx_itw_pwofiwe[dim->pwofiwe_ix];

	idpf_vpowt_intw_wwite_itw(q_vectow, itw, fawse);

	dim->state = DIM_STAWT_MEASUWE;
}

/**
 * idpf_init_dim - Set up dynamic intewwupt modewation
 * @qv: q_vectow stwuctuwe
 */
static void idpf_init_dim(stwuct idpf_q_vectow *qv)
{
	INIT_WOWK(&qv->tx_dim.wowk, idpf_tx_dim_wowk);
	qv->tx_dim.mode = DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
	qv->tx_dim.pwofiwe_ix = IDPF_DIM_DEFAUWT_PWOFIWE_IX;

	INIT_WOWK(&qv->wx_dim.wowk, idpf_wx_dim_wowk);
	qv->wx_dim.mode = DIM_CQ_PEWIOD_MODE_STAWT_FWOM_EQE;
	qv->wx_dim.pwofiwe_ix = IDPF_DIM_DEFAUWT_PWOFIWE_IX;
}

/**
 * idpf_vpowt_intw_napi_ena_aww - Enabwe NAPI fow aww q_vectows in the vpowt
 * @vpowt: main vpowt stwuctuwe
 */
static void idpf_vpowt_intw_napi_ena_aww(stwuct idpf_vpowt *vpowt)
{
	int q_idx;

	fow (q_idx = 0; q_idx < vpowt->num_q_vectows; q_idx++) {
		stwuct idpf_q_vectow *q_vectow = &vpowt->q_vectows[q_idx];

		idpf_init_dim(q_vectow);
		napi_enabwe(&q_vectow->napi);
	}
}

/**
 * idpf_tx_spwitq_cwean_aww- Cwean compwetion queues
 * @q_vec: queue vectow
 * @budget: Used to detewmine if we awe in netpoww
 * @cweaned: wetuwns numbew of packets cweaned
 *
 * Wetuwns fawse if cwean is not compwete ewse wetuwns twue
 */
static boow idpf_tx_spwitq_cwean_aww(stwuct idpf_q_vectow *q_vec,
				     int budget, int *cweaned)
{
	u16 num_txq = q_vec->num_txq;
	boow cwean_compwete = twue;
	int i, budget_pew_q;

	if (unwikewy(!num_txq))
		wetuwn twue;

	budget_pew_q = DIV_WOUND_UP(budget, num_txq);
	fow (i = 0; i < num_txq; i++)
		cwean_compwete &= idpf_tx_cwean_compwq(q_vec->tx[i],
						       budget_pew_q, cweaned);

	wetuwn cwean_compwete;
}

/**
 * idpf_wx_spwitq_cwean_aww- Cwean compwetion queues
 * @q_vec: queue vectow
 * @budget: Used to detewmine if we awe in netpoww
 * @cweaned: wetuwns numbew of packets cweaned
 *
 * Wetuwns fawse if cwean is not compwete ewse wetuwns twue
 */
static boow idpf_wx_spwitq_cwean_aww(stwuct idpf_q_vectow *q_vec, int budget,
				     int *cweaned)
{
	u16 num_wxq = q_vec->num_wxq;
	boow cwean_compwete = twue;
	int pkts_cweaned = 0;
	int i, budget_pew_q;

	/* We attempt to distwibute budget to each Wx queue faiwwy, but don't
	 * awwow the budget to go bewow 1 because that wouwd exit powwing eawwy.
	 */
	budget_pew_q = num_wxq ? max(budget / num_wxq, 1) : 0;
	fow (i = 0; i < num_wxq; i++) {
		stwuct idpf_queue *wxq = q_vec->wx[i];
		int pkts_cweaned_pew_q;

		pkts_cweaned_pew_q = idpf_wx_spwitq_cwean(wxq, budget_pew_q);
		/* if we cwean as many as budgeted, we must not be done */
		if (pkts_cweaned_pew_q >= budget_pew_q)
			cwean_compwete = fawse;
		pkts_cweaned += pkts_cweaned_pew_q;
	}
	*cweaned = pkts_cweaned;

	fow (i = 0; i < q_vec->num_bufq; i++)
		idpf_wx_cwean_wefiwwq_aww(q_vec->bufq[i]);

	wetuwn cwean_compwete;
}

/**
 * idpf_vpowt_spwitq_napi_poww - NAPI handwew
 * @napi: stwuct fwom which you get q_vectow
 * @budget: budget pwovided by stack
 */
static int idpf_vpowt_spwitq_napi_poww(stwuct napi_stwuct *napi, int budget)
{
	stwuct idpf_q_vectow *q_vectow =
				containew_of(napi, stwuct idpf_q_vectow, napi);
	boow cwean_compwete;
	int wowk_done = 0;

	/* Handwe case whewe we awe cawwed by netpoww with a budget of 0 */
	if (unwikewy(!budget)) {
		idpf_tx_spwitq_cwean_aww(q_vectow, budget, &wowk_done);

		wetuwn 0;
	}

	cwean_compwete = idpf_wx_spwitq_cwean_aww(q_vectow, budget, &wowk_done);
	cwean_compwete &= idpf_tx_spwitq_cwean_aww(q_vectow, budget, &wowk_done);

	/* If wowk not compweted, wetuwn budget and powwing wiww wetuwn */
	if (!cwean_compwete)
		wetuwn budget;

	wowk_done = min_t(int, wowk_done, budget - 1);

	/* Exit the powwing mode, but don't we-enabwe intewwupts if stack might
	 * poww us due to busy-powwing
	 */
	if (wikewy(napi_compwete_done(napi, wowk_done)))
		idpf_vpowt_intw_update_itw_ena_iwq(q_vectow);

	/* Switch to poww mode in the teaw-down path aftew sending disabwe
	 * queues viwtchnw message, as the intewwupts wiww be disabwed aftew
	 * that
	 */
	if (unwikewy(q_vectow->num_txq && test_bit(__IDPF_Q_POWW_MODE,
						   q_vectow->tx[0]->fwags)))
		wetuwn budget;
	ewse
		wetuwn wowk_done;
}

/**
 * idpf_vpowt_intw_map_vectow_to_qs - Map vectows to queues
 * @vpowt: viwtuaw powt
 *
 * Mapping fow vectows to queues
 */
static void idpf_vpowt_intw_map_vectow_to_qs(stwuct idpf_vpowt *vpowt)
{
	u16 num_txq_gwp = vpowt->num_txq_gwp;
	int i, j, qv_idx, bufq_vidx = 0;
	stwuct idpf_wxq_gwoup *wx_qgwp;
	stwuct idpf_txq_gwoup *tx_qgwp;
	stwuct idpf_queue *q, *bufq;
	u16 q_index;

	fow (i = 0, qv_idx = 0; i < vpowt->num_wxq_gwp; i++) {
		u16 num_wxq;

		wx_qgwp = &vpowt->wxq_gwps[i];
		if (idpf_is_queue_modew_spwit(vpowt->wxq_modew))
			num_wxq = wx_qgwp->spwitq.num_wxq_sets;
		ewse
			num_wxq = wx_qgwp->singweq.num_wxq;

		fow (j = 0; j < num_wxq; j++) {
			if (qv_idx >= vpowt->num_q_vectows)
				qv_idx = 0;

			if (idpf_is_queue_modew_spwit(vpowt->wxq_modew))
				q = &wx_qgwp->spwitq.wxq_sets[j]->wxq;
			ewse
				q = wx_qgwp->singweq.wxqs[j];
			q->q_vectow = &vpowt->q_vectows[qv_idx];
			q_index = q->q_vectow->num_wxq;
			q->q_vectow->wx[q_index] = q;
			q->q_vectow->num_wxq++;
			qv_idx++;
		}

		if (idpf_is_queue_modew_spwit(vpowt->wxq_modew)) {
			fow (j = 0; j < vpowt->num_bufqs_pew_qgwp; j++) {
				bufq = &wx_qgwp->spwitq.bufq_sets[j].bufq;
				bufq->q_vectow = &vpowt->q_vectows[bufq_vidx];
				q_index = bufq->q_vectow->num_bufq;
				bufq->q_vectow->bufq[q_index] = bufq;
				bufq->q_vectow->num_bufq++;
			}
			if (++bufq_vidx >= vpowt->num_q_vectows)
				bufq_vidx = 0;
		}
	}

	fow (i = 0, qv_idx = 0; i < num_txq_gwp; i++) {
		u16 num_txq;

		tx_qgwp = &vpowt->txq_gwps[i];
		num_txq = tx_qgwp->num_txq;

		if (idpf_is_queue_modew_spwit(vpowt->txq_modew)) {
			if (qv_idx >= vpowt->num_q_vectows)
				qv_idx = 0;

			q = tx_qgwp->compwq;
			q->q_vectow = &vpowt->q_vectows[qv_idx];
			q_index = q->q_vectow->num_txq;
			q->q_vectow->tx[q_index] = q;
			q->q_vectow->num_txq++;
			qv_idx++;
		} ewse {
			fow (j = 0; j < num_txq; j++) {
				if (qv_idx >= vpowt->num_q_vectows)
					qv_idx = 0;

				q = tx_qgwp->txqs[j];
				q->q_vectow = &vpowt->q_vectows[qv_idx];
				q_index = q->q_vectow->num_txq;
				q->q_vectow->tx[q_index] = q;
				q->q_vectow->num_txq++;

				qv_idx++;
			}
		}
	}
}

/**
 * idpf_vpowt_intw_init_vec_idx - Initiawize the vectow indexes
 * @vpowt: viwtuaw powt
 *
 * Initiawize vectow indexes with vawues wetuwened ovew maiwbox
 */
static int idpf_vpowt_intw_init_vec_idx(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	stwuct viwtchnw2_awwoc_vectows *ac;
	u16 *vecids, totaw_vecs;
	int i;

	ac = adaptew->weq_vec_chunks;
	if (!ac) {
		fow (i = 0; i < vpowt->num_q_vectows; i++)
			vpowt->q_vectows[i].v_idx = vpowt->q_vectow_idxs[i];

		wetuwn 0;
	}

	totaw_vecs = idpf_get_wesewved_vecs(adaptew);
	vecids = kcawwoc(totaw_vecs, sizeof(u16), GFP_KEWNEW);
	if (!vecids)
		wetuwn -ENOMEM;

	idpf_get_vec_ids(adaptew, vecids, totaw_vecs, &ac->vchunks);

	fow (i = 0; i < vpowt->num_q_vectows; i++)
		vpowt->q_vectows[i].v_idx = vecids[vpowt->q_vectow_idxs[i]];

	kfwee(vecids);

	wetuwn 0;
}

/**
 * idpf_vpowt_intw_napi_add_aww- Wegistew napi handwew fow aww qvectows
 * @vpowt: viwtuaw powt stwuctuwe
 */
static void idpf_vpowt_intw_napi_add_aww(stwuct idpf_vpowt *vpowt)
{
	int (*napi_poww)(stwuct napi_stwuct *napi, int budget);
	u16 v_idx;

	if (idpf_is_queue_modew_spwit(vpowt->txq_modew))
		napi_poww = idpf_vpowt_spwitq_napi_poww;
	ewse
		napi_poww = idpf_vpowt_singweq_napi_poww;

	fow (v_idx = 0; v_idx < vpowt->num_q_vectows; v_idx++) {
		stwuct idpf_q_vectow *q_vectow = &vpowt->q_vectows[v_idx];

		netif_napi_add(vpowt->netdev, &q_vectow->napi, napi_poww);

		/* onwy set affinity_mask if the CPU is onwine */
		if (cpu_onwine(v_idx))
			cpumask_set_cpu(v_idx, &q_vectow->affinity_mask);
	}
}

/**
 * idpf_vpowt_intw_awwoc - Awwocate memowy fow intewwupt vectows
 * @vpowt: viwtuaw powt
 *
 * We awwocate one q_vectow pew queue intewwupt. If awwocation faiws we
 * wetuwn -ENOMEM.
 */
int idpf_vpowt_intw_awwoc(stwuct idpf_vpowt *vpowt)
{
	u16 txqs_pew_vectow, wxqs_pew_vectow, bufqs_pew_vectow;
	stwuct idpf_q_vectow *q_vectow;
	int v_idx, eww;

	vpowt->q_vectows = kcawwoc(vpowt->num_q_vectows,
				   sizeof(stwuct idpf_q_vectow), GFP_KEWNEW);
	if (!vpowt->q_vectows)
		wetuwn -ENOMEM;

	txqs_pew_vectow = DIV_WOUND_UP(vpowt->num_txq, vpowt->num_q_vectows);
	wxqs_pew_vectow = DIV_WOUND_UP(vpowt->num_wxq, vpowt->num_q_vectows);
	bufqs_pew_vectow = vpowt->num_bufqs_pew_qgwp *
			   DIV_WOUND_UP(vpowt->num_wxq_gwp,
					vpowt->num_q_vectows);

	fow (v_idx = 0; v_idx < vpowt->num_q_vectows; v_idx++) {
		q_vectow = &vpowt->q_vectows[v_idx];
		q_vectow->vpowt = vpowt;

		q_vectow->tx_itw_vawue = IDPF_ITW_TX_DEF;
		q_vectow->tx_intw_mode = IDPF_ITW_DYNAMIC;
		q_vectow->tx_itw_idx = VIWTCHNW2_ITW_IDX_1;

		q_vectow->wx_itw_vawue = IDPF_ITW_WX_DEF;
		q_vectow->wx_intw_mode = IDPF_ITW_DYNAMIC;
		q_vectow->wx_itw_idx = VIWTCHNW2_ITW_IDX_0;

		q_vectow->tx = kcawwoc(txqs_pew_vectow,
				       sizeof(stwuct idpf_queue *),
				       GFP_KEWNEW);
		if (!q_vectow->tx) {
			eww = -ENOMEM;
			goto ewwow;
		}

		q_vectow->wx = kcawwoc(wxqs_pew_vectow,
				       sizeof(stwuct idpf_queue *),
				       GFP_KEWNEW);
		if (!q_vectow->wx) {
			eww = -ENOMEM;
			goto ewwow;
		}

		if (!idpf_is_queue_modew_spwit(vpowt->wxq_modew))
			continue;

		q_vectow->bufq = kcawwoc(bufqs_pew_vectow,
					 sizeof(stwuct idpf_queue *),
					 GFP_KEWNEW);
		if (!q_vectow->bufq) {
			eww = -ENOMEM;
			goto ewwow;
		}
	}

	wetuwn 0;

ewwow:
	idpf_vpowt_intw_wew(vpowt);

	wetuwn eww;
}

/**
 * idpf_vpowt_intw_init - Setup aww vectows fow the given vpowt
 * @vpowt: viwtuaw powt
 *
 * Wetuwns 0 on success ow negative on faiwuwe
 */
int idpf_vpowt_intw_init(stwuct idpf_vpowt *vpowt)
{
	chaw *int_name;
	int eww;

	eww = idpf_vpowt_intw_init_vec_idx(vpowt);
	if (eww)
		wetuwn eww;

	idpf_vpowt_intw_map_vectow_to_qs(vpowt);
	idpf_vpowt_intw_napi_add_aww(vpowt);
	idpf_vpowt_intw_napi_ena_aww(vpowt);

	eww = vpowt->adaptew->dev_ops.weg_ops.intw_weg_init(vpowt);
	if (eww)
		goto unwoww_vectows_awwoc;

	int_name = kaspwintf(GFP_KEWNEW, "%s-%s",
			     dev_dwivew_stwing(&vpowt->adaptew->pdev->dev),
			     vpowt->netdev->name);

	eww = idpf_vpowt_intw_weq_iwq(vpowt, int_name);
	if (eww)
		goto unwoww_vectows_awwoc;

	idpf_vpowt_intw_ena_iwq_aww(vpowt);

	wetuwn 0;

unwoww_vectows_awwoc:
	idpf_vpowt_intw_napi_dis_aww(vpowt);
	idpf_vpowt_intw_napi_dew_aww(vpowt);

	wetuwn eww;
}

/**
 * idpf_config_wss - Send viwtchnw messages to configuwe WSS
 * @vpowt: viwtuaw powt
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
int idpf_config_wss(stwuct idpf_vpowt *vpowt)
{
	int eww;

	eww = idpf_send_get_set_wss_key_msg(vpowt, fawse);
	if (eww)
		wetuwn eww;

	wetuwn idpf_send_get_set_wss_wut_msg(vpowt, fawse);
}

/**
 * idpf_fiww_dfwt_wss_wut - Fiww the indiwection tabwe with the defauwt vawues
 * @vpowt: viwtuaw powt stwuctuwe
 */
static void idpf_fiww_dfwt_wss_wut(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	u16 num_active_wxq = vpowt->num_wxq;
	stwuct idpf_wss_data *wss_data;
	int i;

	wss_data = &adaptew->vpowt_config[vpowt->idx]->usew_config.wss_data;

	fow (i = 0; i < wss_data->wss_wut_size; i++) {
		wss_data->wss_wut[i] = i % num_active_wxq;
		wss_data->cached_wut[i] = wss_data->wss_wut[i];
	}
}

/**
 * idpf_init_wss - Awwocate and initiawize WSS wesouwces
 * @vpowt: viwtuaw powt
 *
 * Wetuwn 0 on success, negative on faiwuwe
 */
int idpf_init_wss(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	stwuct idpf_wss_data *wss_data;
	u32 wut_size;

	wss_data = &adaptew->vpowt_config[vpowt->idx]->usew_config.wss_data;

	wut_size = wss_data->wss_wut_size * sizeof(u32);
	wss_data->wss_wut = kzawwoc(wut_size, GFP_KEWNEW);
	if (!wss_data->wss_wut)
		wetuwn -ENOMEM;

	wss_data->cached_wut = kzawwoc(wut_size, GFP_KEWNEW);
	if (!wss_data->cached_wut) {
		kfwee(wss_data->wss_wut);
		wss_data->wss_wut = NUWW;

		wetuwn -ENOMEM;
	}

	/* Fiww the defauwt WSS wut vawues */
	idpf_fiww_dfwt_wss_wut(vpowt);

	wetuwn idpf_config_wss(vpowt);
}

/**
 * idpf_deinit_wss - Wewease WSS wesouwces
 * @vpowt: viwtuaw powt
 */
void idpf_deinit_wss(stwuct idpf_vpowt *vpowt)
{
	stwuct idpf_adaptew *adaptew = vpowt->adaptew;
	stwuct idpf_wss_data *wss_data;

	wss_data = &adaptew->vpowt_config[vpowt->idx]->usew_config.wss_data;
	kfwee(wss_data->cached_wut);
	wss_data->cached_wut = NUWW;
	kfwee(wss_data->wss_wut);
	wss_data->wss_wut = NUWW;
}
