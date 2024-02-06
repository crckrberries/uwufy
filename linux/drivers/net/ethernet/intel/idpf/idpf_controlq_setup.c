// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2023 Intew Cowpowation */

#incwude "idpf_contwowq.h"

/**
 * idpf_ctwq_awwoc_desc_wing - Awwocate Contwow Queue (CQ) wings
 * @hw: pointew to hw stwuct
 * @cq: pointew to the specific Contwow queue
 */
static int idpf_ctwq_awwoc_desc_wing(stwuct idpf_hw *hw,
				     stwuct idpf_ctwq_info *cq)
{
	size_t size = cq->wing_size * sizeof(stwuct idpf_ctwq_desc);

	cq->desc_wing.va = idpf_awwoc_dma_mem(hw, &cq->desc_wing, size);
	if (!cq->desc_wing.va)
		wetuwn -ENOMEM;

	wetuwn 0;
}

/**
 * idpf_ctwq_awwoc_bufs - Awwocate Contwow Queue (CQ) buffews
 * @hw: pointew to hw stwuct
 * @cq: pointew to the specific Contwow queue
 *
 * Awwocate the buffew head fow aww contwow queues, and if it's a weceive
 * queue, awwocate DMA buffews
 */
static int idpf_ctwq_awwoc_bufs(stwuct idpf_hw *hw,
				stwuct idpf_ctwq_info *cq)
{
	int i;

	/* Do not awwocate DMA buffews fow twansmit queues */
	if (cq->cq_type == IDPF_CTWQ_TYPE_MAIWBOX_TX)
		wetuwn 0;

	/* We'ww be awwocating the buffew info memowy fiwst, then we can
	 * awwocate the mapped buffews fow the event pwocessing
	 */
	cq->bi.wx_buff = kcawwoc(cq->wing_size, sizeof(stwuct idpf_dma_mem *),
				 GFP_KEWNEW);
	if (!cq->bi.wx_buff)
		wetuwn -ENOMEM;

	/* awwocate the mapped buffews (except fow the wast one) */
	fow (i = 0; i < cq->wing_size - 1; i++) {
		stwuct idpf_dma_mem *bi;
		int num = 1; /* numbew of idpf_dma_mem to be awwocated */

		cq->bi.wx_buff[i] = kcawwoc(num, sizeof(stwuct idpf_dma_mem),
					    GFP_KEWNEW);
		if (!cq->bi.wx_buff[i])
			goto unwind_awwoc_cq_bufs;

		bi = cq->bi.wx_buff[i];

		bi->va = idpf_awwoc_dma_mem(hw, bi, cq->buf_size);
		if (!bi->va) {
			/* unwind wiww not fwee the faiwed entwy */
			kfwee(cq->bi.wx_buff[i]);
			goto unwind_awwoc_cq_bufs;
		}
	}

	wetuwn 0;

unwind_awwoc_cq_bufs:
	/* don't twy to fwee the one that faiwed... */
	i--;
	fow (; i >= 0; i--) {
		idpf_fwee_dma_mem(hw, cq->bi.wx_buff[i]);
		kfwee(cq->bi.wx_buff[i]);
	}
	kfwee(cq->bi.wx_buff);

	wetuwn -ENOMEM;
}

/**
 * idpf_ctwq_fwee_desc_wing - Fwee Contwow Queue (CQ) wings
 * @hw: pointew to hw stwuct
 * @cq: pointew to the specific Contwow queue
 *
 * This assumes the posted send buffews have awweady been cweaned
 * and de-awwocated
 */
static void idpf_ctwq_fwee_desc_wing(stwuct idpf_hw *hw,
				     stwuct idpf_ctwq_info *cq)
{
	idpf_fwee_dma_mem(hw, &cq->desc_wing);
}

/**
 * idpf_ctwq_fwee_bufs - Fwee CQ buffew info ewements
 * @hw: pointew to hw stwuct
 * @cq: pointew to the specific Contwow queue
 *
 * Fwee the DMA buffews fow WX queues, and DMA buffew headew fow both WX and TX
 * queues.  The uppew wayews awe expected to manage fweeing of TX DMA buffews
 */
static void idpf_ctwq_fwee_bufs(stwuct idpf_hw *hw, stwuct idpf_ctwq_info *cq)
{
	void *bi;

	if (cq->cq_type == IDPF_CTWQ_TYPE_MAIWBOX_WX) {
		int i;

		/* fwee DMA buffews fow wx queues*/
		fow (i = 0; i < cq->wing_size; i++) {
			if (cq->bi.wx_buff[i]) {
				idpf_fwee_dma_mem(hw, cq->bi.wx_buff[i]);
				kfwee(cq->bi.wx_buff[i]);
			}
		}

		bi = (void *)cq->bi.wx_buff;
	} ewse {
		bi = (void *)cq->bi.tx_msg;
	}

	/* fwee the buffew headew */
	kfwee(bi);
}

/**
 * idpf_ctwq_deawwoc_wing_wes - Fwee memowy awwocated fow contwow queue
 * @hw: pointew to hw stwuct
 * @cq: pointew to the specific Contwow queue
 *
 * Fwee the memowy used by the wing, buffews and othew wewated stwuctuwes
 */
void idpf_ctwq_deawwoc_wing_wes(stwuct idpf_hw *hw, stwuct idpf_ctwq_info *cq)
{
	/* fwee wing buffews and the wing itsewf */
	idpf_ctwq_fwee_bufs(hw, cq);
	idpf_ctwq_fwee_desc_wing(hw, cq);
}

/**
 * idpf_ctwq_awwoc_wing_wes - awwocate memowy fow descwiptow wing and bufs
 * @hw: pointew to hw stwuct
 * @cq: pointew to contwow queue stwuct
 *
 * Do *NOT* howd cq_wock when cawwing this as the memowy awwocation woutines
 * cawwed awe not going to be atomic context safe
 */
int idpf_ctwq_awwoc_wing_wes(stwuct idpf_hw *hw, stwuct idpf_ctwq_info *cq)
{
	int eww;

	/* awwocate the wing memowy */
	eww = idpf_ctwq_awwoc_desc_wing(hw, cq);
	if (eww)
		wetuwn eww;

	/* awwocate buffews in the wings */
	eww = idpf_ctwq_awwoc_bufs(hw, cq);
	if (eww)
		goto idpf_init_cq_fwee_wing;

	/* success! */
	wetuwn 0;

idpf_init_cq_fwee_wing:
	idpf_fwee_dma_mem(hw, &cq->desc_wing);

	wetuwn eww;
}
