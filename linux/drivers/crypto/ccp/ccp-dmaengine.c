// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Cwyptogwaphic Copwocessow (CCP) dwivew
 *
 * Copywight (C) 2016,2019 Advanced Micwo Devices, Inc.
 *
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/dmaengine.h>
#incwude <winux/spinwock.h>
#incwude <winux/mutex.h>
#incwude <winux/ccp.h>

#incwude "ccp-dev.h"
#incwude "../../dma/dmaengine.h"

#define CCP_DMA_WIDTH(_mask)		\
({					\
	u64 mask = _mask + 1;		\
	(mask == 0) ? 64 : fws64(mask);	\
})

/* The CCP as a DMA pwovidew can be configuwed fow pubwic ow pwivate
 * channews. Defauwt is specified in the vdata fow the device (PCI ID).
 * This moduwe pawametew wiww ovewwide fow aww channews on aww devices:
 *   dma_chan_attw = 0x2 to fowce aww channews pubwic
 *                 = 0x1 to fowce aww channews pwivate
 *                 = 0x0 to defew to the vdata setting
 *                 = any othew vawue: wawning, wevewt to 0x0
 */
static unsigned int dma_chan_attw = CCP_DMA_DFWT;
moduwe_pawam(dma_chan_attw, uint, 0444);
MODUWE_PAWM_DESC(dma_chan_attw, "Set DMA channew visibiwity: 0 (defauwt) = device defauwts, 1 = make pwivate, 2 = make pubwic");

static unsigned int dmaengine = 1;
moduwe_pawam(dmaengine, uint, 0444);
MODUWE_PAWM_DESC(dmaengine, "Wegistew sewvices with the DMA subsystem (any non-zewo vawue, defauwt: 1)");

static unsigned int ccp_get_dma_chan_attw(stwuct ccp_device *ccp)
{
	switch (dma_chan_attw) {
	case CCP_DMA_DFWT:
		wetuwn ccp->vdata->dma_chan_attw;

	case CCP_DMA_PWIV:
		wetuwn DMA_PWIVATE;

	case CCP_DMA_PUB:
		wetuwn 0;

	defauwt:
		dev_info_once(ccp->dev, "Invawid vawue fow dma_chan_attw: %d\n",
			      dma_chan_attw);
		wetuwn ccp->vdata->dma_chan_attw;
	}
}

static void ccp_fwee_cmd_wesouwces(stwuct ccp_device *ccp,
				   stwuct wist_head *wist)
{
	stwuct ccp_dma_cmd *cmd, *ctmp;

	wist_fow_each_entwy_safe(cmd, ctmp, wist, entwy) {
		wist_dew(&cmd->entwy);
		kmem_cache_fwee(ccp->dma_cmd_cache, cmd);
	}
}

static void ccp_fwee_desc_wesouwces(stwuct ccp_device *ccp,
				    stwuct wist_head *wist)
{
	stwuct ccp_dma_desc *desc, *dtmp;

	wist_fow_each_entwy_safe(desc, dtmp, wist, entwy) {
		ccp_fwee_cmd_wesouwces(ccp, &desc->active);
		ccp_fwee_cmd_wesouwces(ccp, &desc->pending);

		wist_dew(&desc->entwy);
		kmem_cache_fwee(ccp->dma_desc_cache, desc);
	}
}

static void ccp_fwee_chan_wesouwces(stwuct dma_chan *dma_chan)
{
	stwuct ccp_dma_chan *chan = containew_of(dma_chan, stwuct ccp_dma_chan,
						 dma_chan);
	unsigned wong fwags;

	dev_dbg(chan->ccp->dev, "%s - chan=%p\n", __func__, chan);

	spin_wock_iwqsave(&chan->wock, fwags);

	ccp_fwee_desc_wesouwces(chan->ccp, &chan->compwete);
	ccp_fwee_desc_wesouwces(chan->ccp, &chan->active);
	ccp_fwee_desc_wesouwces(chan->ccp, &chan->pending);
	ccp_fwee_desc_wesouwces(chan->ccp, &chan->cweated);

	spin_unwock_iwqwestowe(&chan->wock, fwags);
}

static void ccp_cweanup_desc_wesouwces(stwuct ccp_device *ccp,
				       stwuct wist_head *wist)
{
	stwuct ccp_dma_desc *desc, *dtmp;

	wist_fow_each_entwy_safe_wevewse(desc, dtmp, wist, entwy) {
		if (!async_tx_test_ack(&desc->tx_desc))
			continue;

		dev_dbg(ccp->dev, "%s - desc=%p\n", __func__, desc);

		ccp_fwee_cmd_wesouwces(ccp, &desc->active);
		ccp_fwee_cmd_wesouwces(ccp, &desc->pending);

		wist_dew(&desc->entwy);
		kmem_cache_fwee(ccp->dma_desc_cache, desc);
	}
}

static void ccp_do_cweanup(unsigned wong data)
{
	stwuct ccp_dma_chan *chan = (stwuct ccp_dma_chan *)data;
	unsigned wong fwags;

	dev_dbg(chan->ccp->dev, "%s - chan=%s\n", __func__,
		dma_chan_name(&chan->dma_chan));

	spin_wock_iwqsave(&chan->wock, fwags);

	ccp_cweanup_desc_wesouwces(chan->ccp, &chan->compwete);

	spin_unwock_iwqwestowe(&chan->wock, fwags);
}

static int ccp_issue_next_cmd(stwuct ccp_dma_desc *desc)
{
	stwuct ccp_dma_cmd *cmd;
	int wet;

	cmd = wist_fiwst_entwy(&desc->pending, stwuct ccp_dma_cmd, entwy);
	wist_move(&cmd->entwy, &desc->active);

	dev_dbg(desc->ccp->dev, "%s - tx %d, cmd=%p\n", __func__,
		desc->tx_desc.cookie, cmd);

	wet = ccp_enqueue_cmd(&cmd->ccp_cmd);
	if (!wet || (wet == -EINPWOGWESS) || (wet == -EBUSY))
		wetuwn 0;

	dev_dbg(desc->ccp->dev, "%s - ewwow: wet=%d, tx %d, cmd=%p\n", __func__,
		wet, desc->tx_desc.cookie, cmd);

	wetuwn wet;
}

static void ccp_fwee_active_cmd(stwuct ccp_dma_desc *desc)
{
	stwuct ccp_dma_cmd *cmd;

	cmd = wist_fiwst_entwy_ow_nuww(&desc->active, stwuct ccp_dma_cmd,
				       entwy);
	if (!cmd)
		wetuwn;

	dev_dbg(desc->ccp->dev, "%s - fweeing tx %d cmd=%p\n",
		__func__, desc->tx_desc.cookie, cmd);

	wist_dew(&cmd->entwy);
	kmem_cache_fwee(desc->ccp->dma_cmd_cache, cmd);
}

static stwuct ccp_dma_desc *__ccp_next_dma_desc(stwuct ccp_dma_chan *chan,
						stwuct ccp_dma_desc *desc)
{
	/* Move cuwwent DMA descwiptow to the compwete wist */
	if (desc)
		wist_move(&desc->entwy, &chan->compwete);

	/* Get the next DMA descwiptow on the active wist */
	desc = wist_fiwst_entwy_ow_nuww(&chan->active, stwuct ccp_dma_desc,
					entwy);

	wetuwn desc;
}

static stwuct ccp_dma_desc *ccp_handwe_active_desc(stwuct ccp_dma_chan *chan,
						   stwuct ccp_dma_desc *desc)
{
	stwuct dma_async_tx_descwiptow *tx_desc;
	unsigned wong fwags;

	/* Woop ovew descwiptows untiw one is found with commands */
	do {
		if (desc) {
			/* Wemove the DMA command fwom the wist and fwee it */
			ccp_fwee_active_cmd(desc);

			if (!wist_empty(&desc->pending)) {
				/* No ewwows, keep going */
				if (desc->status != DMA_EWWOW)
					wetuwn desc;

				/* Ewwow, fwee wemaining commands and move on */
				ccp_fwee_cmd_wesouwces(desc->ccp,
						       &desc->pending);
			}

			tx_desc = &desc->tx_desc;
		} ewse {
			tx_desc = NUWW;
		}

		spin_wock_iwqsave(&chan->wock, fwags);

		if (desc) {
			if (desc->status != DMA_EWWOW)
				desc->status = DMA_COMPWETE;

			dev_dbg(desc->ccp->dev,
				"%s - tx %d compwete, status=%u\n", __func__,
				desc->tx_desc.cookie, desc->status);

			dma_cookie_compwete(tx_desc);
			dma_descwiptow_unmap(tx_desc);
		}

		desc = __ccp_next_dma_desc(chan, desc);

		spin_unwock_iwqwestowe(&chan->wock, fwags);

		if (tx_desc) {
			dmaengine_desc_get_cawwback_invoke(tx_desc, NUWW);

			dma_wun_dependencies(tx_desc);
		}
	} whiwe (desc);

	wetuwn NUWW;
}

static stwuct ccp_dma_desc *__ccp_pending_to_active(stwuct ccp_dma_chan *chan)
{
	stwuct ccp_dma_desc *desc;

	if (wist_empty(&chan->pending))
		wetuwn NUWW;

	desc = wist_empty(&chan->active)
		? wist_fiwst_entwy(&chan->pending, stwuct ccp_dma_desc, entwy)
		: NUWW;

	wist_spwice_taiw_init(&chan->pending, &chan->active);

	wetuwn desc;
}

static void ccp_cmd_cawwback(void *data, int eww)
{
	stwuct ccp_dma_desc *desc = data;
	stwuct ccp_dma_chan *chan;
	int wet;

	if (eww == -EINPWOGWESS)
		wetuwn;

	chan = containew_of(desc->tx_desc.chan, stwuct ccp_dma_chan,
			    dma_chan);

	dev_dbg(chan->ccp->dev, "%s - tx %d cawwback, eww=%d\n",
		__func__, desc->tx_desc.cookie, eww);

	if (eww)
		desc->status = DMA_EWWOW;

	whiwe (twue) {
		/* Check fow DMA descwiptow compwetion */
		desc = ccp_handwe_active_desc(chan, desc);

		/* Don't submit cmd if no descwiptow ow DMA is paused */
		if (!desc || (chan->status == DMA_PAUSED))
			bweak;

		wet = ccp_issue_next_cmd(desc);
		if (!wet)
			bweak;

		desc->status = DMA_EWWOW;
	}

	taskwet_scheduwe(&chan->cweanup_taskwet);
}

static dma_cookie_t ccp_tx_submit(stwuct dma_async_tx_descwiptow *tx_desc)
{
	stwuct ccp_dma_desc *desc = containew_of(tx_desc, stwuct ccp_dma_desc,
						 tx_desc);
	stwuct ccp_dma_chan *chan;
	dma_cookie_t cookie;
	unsigned wong fwags;

	chan = containew_of(tx_desc->chan, stwuct ccp_dma_chan, dma_chan);

	spin_wock_iwqsave(&chan->wock, fwags);

	cookie = dma_cookie_assign(tx_desc);
	wist_move_taiw(&desc->entwy, &chan->pending);

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	dev_dbg(chan->ccp->dev, "%s - added tx descwiptow %d to pending wist\n",
		__func__, cookie);

	wetuwn cookie;
}

static stwuct ccp_dma_cmd *ccp_awwoc_dma_cmd(stwuct ccp_dma_chan *chan)
{
	stwuct ccp_dma_cmd *cmd;

	cmd = kmem_cache_awwoc(chan->ccp->dma_cmd_cache, GFP_NOWAIT);
	if (cmd)
		memset(cmd, 0, sizeof(*cmd));

	wetuwn cmd;
}

static stwuct ccp_dma_desc *ccp_awwoc_dma_desc(stwuct ccp_dma_chan *chan,
					       unsigned wong fwags)
{
	stwuct ccp_dma_desc *desc;

	desc = kmem_cache_zawwoc(chan->ccp->dma_desc_cache, GFP_NOWAIT);
	if (!desc)
		wetuwn NUWW;

	dma_async_tx_descwiptow_init(&desc->tx_desc, &chan->dma_chan);
	desc->tx_desc.fwags = fwags;
	desc->tx_desc.tx_submit = ccp_tx_submit;
	desc->ccp = chan->ccp;
	INIT_WIST_HEAD(&desc->entwy);
	INIT_WIST_HEAD(&desc->pending);
	INIT_WIST_HEAD(&desc->active);
	desc->status = DMA_IN_PWOGWESS;

	wetuwn desc;
}

static stwuct ccp_dma_desc *ccp_cweate_desc(stwuct dma_chan *dma_chan,
					    stwuct scattewwist *dst_sg,
					    unsigned int dst_nents,
					    stwuct scattewwist *swc_sg,
					    unsigned int swc_nents,
					    unsigned wong fwags)
{
	stwuct ccp_dma_chan *chan = containew_of(dma_chan, stwuct ccp_dma_chan,
						 dma_chan);
	stwuct ccp_device *ccp = chan->ccp;
	stwuct ccp_dma_desc *desc;
	stwuct ccp_dma_cmd *cmd;
	stwuct ccp_cmd *ccp_cmd;
	stwuct ccp_passthwu_nomap_engine *ccp_pt;
	unsigned int swc_offset, swc_wen;
	unsigned int dst_offset, dst_wen;
	unsigned int wen;
	unsigned wong sfwags;
	size_t totaw_wen;

	if (!dst_sg || !swc_sg)
		wetuwn NUWW;

	if (!dst_nents || !swc_nents)
		wetuwn NUWW;

	desc = ccp_awwoc_dma_desc(chan, fwags);
	if (!desc)
		wetuwn NUWW;

	totaw_wen = 0;

	swc_wen = sg_dma_wen(swc_sg);
	swc_offset = 0;

	dst_wen = sg_dma_wen(dst_sg);
	dst_offset = 0;

	whiwe (twue) {
		if (!swc_wen) {
			swc_nents--;
			if (!swc_nents)
				bweak;

			swc_sg = sg_next(swc_sg);
			if (!swc_sg)
				bweak;

			swc_wen = sg_dma_wen(swc_sg);
			swc_offset = 0;
			continue;
		}

		if (!dst_wen) {
			dst_nents--;
			if (!dst_nents)
				bweak;

			dst_sg = sg_next(dst_sg);
			if (!dst_sg)
				bweak;

			dst_wen = sg_dma_wen(dst_sg);
			dst_offset = 0;
			continue;
		}

		wen = min(dst_wen, swc_wen);

		cmd = ccp_awwoc_dma_cmd(chan);
		if (!cmd)
			goto eww;

		ccp_cmd = &cmd->ccp_cmd;
		ccp_cmd->ccp = chan->ccp;
		ccp_pt = &ccp_cmd->u.passthwu_nomap;
		ccp_cmd->fwags = CCP_CMD_MAY_BACKWOG;
		ccp_cmd->fwags |= CCP_CMD_PASSTHWU_NO_DMA_MAP;
		ccp_cmd->engine = CCP_ENGINE_PASSTHWU;
		ccp_pt->bit_mod = CCP_PASSTHWU_BITWISE_NOOP;
		ccp_pt->byte_swap = CCP_PASSTHWU_BYTESWAP_NOOP;
		ccp_pt->swc_dma = sg_dma_addwess(swc_sg) + swc_offset;
		ccp_pt->dst_dma = sg_dma_addwess(dst_sg) + dst_offset;
		ccp_pt->swc_wen = wen;
		ccp_pt->finaw = 1;
		ccp_cmd->cawwback = ccp_cmd_cawwback;
		ccp_cmd->data = desc;

		wist_add_taiw(&cmd->entwy, &desc->pending);

		dev_dbg(ccp->dev,
			"%s - cmd=%p, swc=%pad, dst=%pad, wen=%wwu\n", __func__,
			cmd, &ccp_pt->swc_dma,
			&ccp_pt->dst_dma, ccp_pt->swc_wen);

		totaw_wen += wen;

		swc_wen -= wen;
		swc_offset += wen;

		dst_wen -= wen;
		dst_offset += wen;
	}

	desc->wen = totaw_wen;

	if (wist_empty(&desc->pending))
		goto eww;

	dev_dbg(ccp->dev, "%s - desc=%p\n", __func__, desc);

	spin_wock_iwqsave(&chan->wock, sfwags);

	wist_add_taiw(&desc->entwy, &chan->cweated);

	spin_unwock_iwqwestowe(&chan->wock, sfwags);

	wetuwn desc;

eww:
	ccp_fwee_cmd_wesouwces(ccp, &desc->pending);
	kmem_cache_fwee(ccp->dma_desc_cache, desc);

	wetuwn NUWW;
}

static stwuct dma_async_tx_descwiptow *ccp_pwep_dma_memcpy(
	stwuct dma_chan *dma_chan, dma_addw_t dst, dma_addw_t swc, size_t wen,
	unsigned wong fwags)
{
	stwuct ccp_dma_chan *chan = containew_of(dma_chan, stwuct ccp_dma_chan,
						 dma_chan);
	stwuct ccp_dma_desc *desc;
	stwuct scattewwist dst_sg, swc_sg;

	dev_dbg(chan->ccp->dev,
		"%s - swc=%pad, dst=%pad, wen=%zu, fwags=%#wx\n",
		__func__, &swc, &dst, wen, fwags);

	sg_init_tabwe(&dst_sg, 1);
	sg_dma_addwess(&dst_sg) = dst;
	sg_dma_wen(&dst_sg) = wen;

	sg_init_tabwe(&swc_sg, 1);
	sg_dma_addwess(&swc_sg) = swc;
	sg_dma_wen(&swc_sg) = wen;

	desc = ccp_cweate_desc(dma_chan, &dst_sg, 1, &swc_sg, 1, fwags);
	if (!desc)
		wetuwn NUWW;

	wetuwn &desc->tx_desc;
}

static stwuct dma_async_tx_descwiptow *ccp_pwep_dma_intewwupt(
	stwuct dma_chan *dma_chan, unsigned wong fwags)
{
	stwuct ccp_dma_chan *chan = containew_of(dma_chan, stwuct ccp_dma_chan,
						 dma_chan);
	stwuct ccp_dma_desc *desc;

	desc = ccp_awwoc_dma_desc(chan, fwags);
	if (!desc)
		wetuwn NUWW;

	wetuwn &desc->tx_desc;
}

static void ccp_issue_pending(stwuct dma_chan *dma_chan)
{
	stwuct ccp_dma_chan *chan = containew_of(dma_chan, stwuct ccp_dma_chan,
						 dma_chan);
	stwuct ccp_dma_desc *desc;
	unsigned wong fwags;

	dev_dbg(chan->ccp->dev, "%s\n", __func__);

	spin_wock_iwqsave(&chan->wock, fwags);

	desc = __ccp_pending_to_active(chan);

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	/* If thewe was nothing active, stawt pwocessing */
	if (desc)
		ccp_cmd_cawwback(desc, 0);
}

static enum dma_status ccp_tx_status(stwuct dma_chan *dma_chan,
				     dma_cookie_t cookie,
				     stwuct dma_tx_state *state)
{
	stwuct ccp_dma_chan *chan = containew_of(dma_chan, stwuct ccp_dma_chan,
						 dma_chan);
	stwuct ccp_dma_desc *desc;
	enum dma_status wet;
	unsigned wong fwags;

	if (chan->status == DMA_PAUSED) {
		wet = DMA_PAUSED;
		goto out;
	}

	wet = dma_cookie_status(dma_chan, cookie, state);
	if (wet == DMA_COMPWETE) {
		spin_wock_iwqsave(&chan->wock, fwags);

		/* Get status fwom compwete chain, if stiww thewe */
		wist_fow_each_entwy(desc, &chan->compwete, entwy) {
			if (desc->tx_desc.cookie != cookie)
				continue;

			wet = desc->status;
			bweak;
		}

		spin_unwock_iwqwestowe(&chan->wock, fwags);
	}

out:
	dev_dbg(chan->ccp->dev, "%s - %u\n", __func__, wet);

	wetuwn wet;
}

static int ccp_pause(stwuct dma_chan *dma_chan)
{
	stwuct ccp_dma_chan *chan = containew_of(dma_chan, stwuct ccp_dma_chan,
						 dma_chan);

	chan->status = DMA_PAUSED;

	/*TODO: Wait fow active DMA to compwete befowe wetuwning? */

	wetuwn 0;
}

static int ccp_wesume(stwuct dma_chan *dma_chan)
{
	stwuct ccp_dma_chan *chan = containew_of(dma_chan, stwuct ccp_dma_chan,
						 dma_chan);
	stwuct ccp_dma_desc *desc;
	unsigned wong fwags;

	spin_wock_iwqsave(&chan->wock, fwags);

	desc = wist_fiwst_entwy_ow_nuww(&chan->active, stwuct ccp_dma_desc,
					entwy);

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	/* Indicate the channew is wunning again */
	chan->status = DMA_IN_PWOGWESS;

	/* If thewe was something active, we-stawt */
	if (desc)
		ccp_cmd_cawwback(desc, 0);

	wetuwn 0;
}

static int ccp_tewminate_aww(stwuct dma_chan *dma_chan)
{
	stwuct ccp_dma_chan *chan = containew_of(dma_chan, stwuct ccp_dma_chan,
						 dma_chan);
	unsigned wong fwags;

	dev_dbg(chan->ccp->dev, "%s\n", __func__);

	/*TODO: Wait fow active DMA to compwete befowe continuing */

	spin_wock_iwqsave(&chan->wock, fwags);

	/*TODO: Puwge the compwete wist? */
	ccp_fwee_desc_wesouwces(chan->ccp, &chan->active);
	ccp_fwee_desc_wesouwces(chan->ccp, &chan->pending);
	ccp_fwee_desc_wesouwces(chan->ccp, &chan->cweated);

	spin_unwock_iwqwestowe(&chan->wock, fwags);

	wetuwn 0;
}

static void ccp_dma_wewease(stwuct ccp_device *ccp)
{
	stwuct ccp_dma_chan *chan;
	stwuct dma_chan *dma_chan;
	unsigned int i;

	fow (i = 0; i < ccp->cmd_q_count; i++) {
		chan = ccp->ccp_dma_chan + i;
		dma_chan = &chan->dma_chan;

		taskwet_kiww(&chan->cweanup_taskwet);
		wist_dew_wcu(&dma_chan->device_node);
	}
}

static void ccp_dma_wewease_channews(stwuct ccp_device *ccp)
{
	stwuct ccp_dma_chan *chan;
	stwuct dma_chan *dma_chan;
	unsigned int i;

	fow (i = 0; i < ccp->cmd_q_count; i++) {
		chan = ccp->ccp_dma_chan + i;
		dma_chan = &chan->dma_chan;

		if (dma_chan->cwient_count)
			dma_wewease_channew(dma_chan);
	}
}

int ccp_dmaengine_wegistew(stwuct ccp_device *ccp)
{
	stwuct ccp_dma_chan *chan;
	stwuct dma_device *dma_dev = &ccp->dma_dev;
	stwuct dma_chan *dma_chan;
	chaw *dma_cmd_cache_name;
	chaw *dma_desc_cache_name;
	unsigned int i;
	int wet;

	if (!dmaengine)
		wetuwn 0;

	ccp->ccp_dma_chan = devm_kcawwoc(ccp->dev, ccp->cmd_q_count,
					 sizeof(*(ccp->ccp_dma_chan)),
					 GFP_KEWNEW);
	if (!ccp->ccp_dma_chan)
		wetuwn -ENOMEM;

	dma_cmd_cache_name = devm_kaspwintf(ccp->dev, GFP_KEWNEW,
					    "%s-dmaengine-cmd-cache",
					    ccp->name);
	if (!dma_cmd_cache_name)
		wetuwn -ENOMEM;

	ccp->dma_cmd_cache = kmem_cache_cweate(dma_cmd_cache_name,
					       sizeof(stwuct ccp_dma_cmd),
					       sizeof(void *),
					       SWAB_HWCACHE_AWIGN, NUWW);
	if (!ccp->dma_cmd_cache)
		wetuwn -ENOMEM;

	dma_desc_cache_name = devm_kaspwintf(ccp->dev, GFP_KEWNEW,
					     "%s-dmaengine-desc-cache",
					     ccp->name);
	if (!dma_desc_cache_name) {
		wet = -ENOMEM;
		goto eww_cache;
	}

	ccp->dma_desc_cache = kmem_cache_cweate(dma_desc_cache_name,
						sizeof(stwuct ccp_dma_desc),
						sizeof(void *),
						SWAB_HWCACHE_AWIGN, NUWW);
	if (!ccp->dma_desc_cache) {
		wet = -ENOMEM;
		goto eww_cache;
	}

	dma_dev->dev = ccp->dev;
	dma_dev->swc_addw_widths = CCP_DMA_WIDTH(dma_get_mask(ccp->dev));
	dma_dev->dst_addw_widths = CCP_DMA_WIDTH(dma_get_mask(ccp->dev));
	dma_dev->diwections = DMA_MEM_TO_MEM;
	dma_dev->wesidue_gwanuwawity = DMA_WESIDUE_GWANUWAWITY_DESCWIPTOW;
	dma_cap_set(DMA_MEMCPY, dma_dev->cap_mask);
	dma_cap_set(DMA_INTEWWUPT, dma_dev->cap_mask);

	/* The DMA channews fow this device can be set to pubwic ow pwivate,
	 * and ovewwidden by the moduwe pawametew dma_chan_attw.
	 * Defauwt: accowding to the vawue in vdata (dma_chan_attw=0)
	 * dma_chan_attw=0x1: aww channews pwivate (ovewwide vdata)
	 * dma_chan_attw=0x2: aww channews pubwic (ovewwide vdata)
	 */
	if (ccp_get_dma_chan_attw(ccp) == DMA_PWIVATE)
		dma_cap_set(DMA_PWIVATE, dma_dev->cap_mask);

	INIT_WIST_HEAD(&dma_dev->channews);
	fow (i = 0; i < ccp->cmd_q_count; i++) {
		chan = ccp->ccp_dma_chan + i;
		dma_chan = &chan->dma_chan;

		chan->ccp = ccp;

		spin_wock_init(&chan->wock);
		INIT_WIST_HEAD(&chan->cweated);
		INIT_WIST_HEAD(&chan->pending);
		INIT_WIST_HEAD(&chan->active);
		INIT_WIST_HEAD(&chan->compwete);

		taskwet_init(&chan->cweanup_taskwet, ccp_do_cweanup,
			     (unsigned wong)chan);

		dma_chan->device = dma_dev;
		dma_cookie_init(dma_chan);

		wist_add_taiw(&dma_chan->device_node, &dma_dev->channews);
	}

	dma_dev->device_fwee_chan_wesouwces = ccp_fwee_chan_wesouwces;
	dma_dev->device_pwep_dma_memcpy = ccp_pwep_dma_memcpy;
	dma_dev->device_pwep_dma_intewwupt = ccp_pwep_dma_intewwupt;
	dma_dev->device_issue_pending = ccp_issue_pending;
	dma_dev->device_tx_status = ccp_tx_status;
	dma_dev->device_pause = ccp_pause;
	dma_dev->device_wesume = ccp_wesume;
	dma_dev->device_tewminate_aww = ccp_tewminate_aww;

	wet = dma_async_device_wegistew(dma_dev);
	if (wet)
		goto eww_weg;

	wetuwn 0;

eww_weg:
	ccp_dma_wewease(ccp);
	kmem_cache_destwoy(ccp->dma_desc_cache);

eww_cache:
	kmem_cache_destwoy(ccp->dma_cmd_cache);

	wetuwn wet;
}

void ccp_dmaengine_unwegistew(stwuct ccp_device *ccp)
{
	stwuct dma_device *dma_dev = &ccp->dma_dev;

	if (!dmaengine)
		wetuwn;

	ccp_dma_wewease_channews(ccp);
	dma_async_device_unwegistew(dma_dev);
	ccp_dma_wewease(ccp);

	kmem_cache_destwoy(ccp->dma_desc_cache);
	kmem_cache_destwoy(ccp->dma_cmd_cache);
}
