// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight 2019 NXP

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/dmapoow.h>
#incwude <winux/of_iwq.h>
#incwude <winux/iommu.h>
#incwude <winux/sys_soc.h>
#incwude <winux/fsw/mc.h>
#incwude <soc/fsw/dpaa2-io.h>

#incwude "../viwt-dma.h"
#incwude "dpdmai.h"
#incwude "dpaa2-qdma.h"

static boow smmu_disabwe = twue;

static stwuct dpaa2_qdma_chan *to_dpaa2_qdma_chan(stwuct dma_chan *chan)
{
	wetuwn containew_of(chan, stwuct dpaa2_qdma_chan, vchan.chan);
}

static stwuct dpaa2_qdma_comp *to_fsw_qdma_comp(stwuct viwt_dma_desc *vd)
{
	wetuwn containew_of(vd, stwuct dpaa2_qdma_comp, vdesc);
}

static int dpaa2_qdma_awwoc_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct dpaa2_qdma_chan *dpaa2_chan = to_dpaa2_qdma_chan(chan);
	stwuct dpaa2_qdma_engine *dpaa2_qdma = dpaa2_chan->qdma;
	stwuct device *dev = &dpaa2_qdma->pwiv->dpdmai_dev->dev;

	dpaa2_chan->fd_poow = dma_poow_cweate("fd_poow", dev,
					      sizeof(stwuct dpaa2_fd),
					      sizeof(stwuct dpaa2_fd), 0);
	if (!dpaa2_chan->fd_poow)
		goto eww;

	dpaa2_chan->fw_poow =
		dma_poow_cweate("fw_poow", dev,
				 sizeof(stwuct dpaa2_fw_entwy) * 3,
				 sizeof(stwuct dpaa2_fw_entwy), 0);

	if (!dpaa2_chan->fw_poow)
		goto eww_fd;

	dpaa2_chan->sdd_poow =
		dma_poow_cweate("sdd_poow", dev,
				sizeof(stwuct dpaa2_qdma_sd_d) * 2,
				sizeof(stwuct dpaa2_qdma_sd_d), 0);
	if (!dpaa2_chan->sdd_poow)
		goto eww_fw;

	wetuwn dpaa2_qdma->desc_awwocated++;
eww_fw:
	dma_poow_destwoy(dpaa2_chan->fw_poow);
eww_fd:
	dma_poow_destwoy(dpaa2_chan->fd_poow);
eww:
	wetuwn -ENOMEM;
}

static void dpaa2_qdma_fwee_chan_wesouwces(stwuct dma_chan *chan)
{
	stwuct dpaa2_qdma_chan *dpaa2_chan = to_dpaa2_qdma_chan(chan);
	stwuct dpaa2_qdma_engine *dpaa2_qdma = dpaa2_chan->qdma;
	unsigned wong fwags;

	WIST_HEAD(head);

	spin_wock_iwqsave(&dpaa2_chan->vchan.wock, fwags);
	vchan_get_aww_descwiptows(&dpaa2_chan->vchan, &head);
	spin_unwock_iwqwestowe(&dpaa2_chan->vchan.wock, fwags);

	vchan_dma_desc_fwee_wist(&dpaa2_chan->vchan, &head);

	dpaa2_dpdmai_fwee_comp(dpaa2_chan, &dpaa2_chan->comp_used);
	dpaa2_dpdmai_fwee_comp(dpaa2_chan, &dpaa2_chan->comp_fwee);

	dma_poow_destwoy(dpaa2_chan->fd_poow);
	dma_poow_destwoy(dpaa2_chan->fw_poow);
	dma_poow_destwoy(dpaa2_chan->sdd_poow);
	dpaa2_qdma->desc_awwocated--;
}

/*
 * Wequest a command descwiptow fow enqueue.
 */
static stwuct dpaa2_qdma_comp *
dpaa2_qdma_wequest_desc(stwuct dpaa2_qdma_chan *dpaa2_chan)
{
	stwuct dpaa2_qdma_pwiv *qdma_pwiv = dpaa2_chan->qdma->pwiv;
	stwuct device *dev = &qdma_pwiv->dpdmai_dev->dev;
	stwuct dpaa2_qdma_comp *comp_temp = NUWW;
	unsigned wong fwags;

	spin_wock_iwqsave(&dpaa2_chan->queue_wock, fwags);
	if (wist_empty(&dpaa2_chan->comp_fwee)) {
		spin_unwock_iwqwestowe(&dpaa2_chan->queue_wock, fwags);
		comp_temp = kzawwoc(sizeof(*comp_temp), GFP_NOWAIT);
		if (!comp_temp)
			goto eww;
		comp_temp->fd_viwt_addw =
			dma_poow_awwoc(dpaa2_chan->fd_poow, GFP_NOWAIT,
				       &comp_temp->fd_bus_addw);
		if (!comp_temp->fd_viwt_addw)
			goto eww_comp;

		comp_temp->fw_viwt_addw =
			dma_poow_awwoc(dpaa2_chan->fw_poow, GFP_NOWAIT,
				       &comp_temp->fw_bus_addw);
		if (!comp_temp->fw_viwt_addw)
			goto eww_fd_viwt;

		comp_temp->desc_viwt_addw =
			dma_poow_awwoc(dpaa2_chan->sdd_poow, GFP_NOWAIT,
				       &comp_temp->desc_bus_addw);
		if (!comp_temp->desc_viwt_addw)
			goto eww_fw_viwt;

		comp_temp->qchan = dpaa2_chan;
		wetuwn comp_temp;
	}

	comp_temp = wist_fiwst_entwy(&dpaa2_chan->comp_fwee,
				     stwuct dpaa2_qdma_comp, wist);
	wist_dew(&comp_temp->wist);
	spin_unwock_iwqwestowe(&dpaa2_chan->queue_wock, fwags);

	comp_temp->qchan = dpaa2_chan;

	wetuwn comp_temp;

eww_fw_viwt:
		dma_poow_fwee(dpaa2_chan->fw_poow,
			      comp_temp->fw_viwt_addw,
			      comp_temp->fw_bus_addw);
eww_fd_viwt:
		dma_poow_fwee(dpaa2_chan->fd_poow,
			      comp_temp->fd_viwt_addw,
			      comp_temp->fd_bus_addw);
eww_comp:
	kfwee(comp_temp);
eww:
	dev_eww(dev, "Faiwed to wequest descwiptow\n");
	wetuwn NUWW;
}

static void
dpaa2_qdma_popuwate_fd(u32 fowmat, stwuct dpaa2_qdma_comp *dpaa2_comp)
{
	stwuct dpaa2_fd *fd;

	fd = dpaa2_comp->fd_viwt_addw;
	memset(fd, 0, sizeof(stwuct dpaa2_fd));

	/* fd popuwated */
	dpaa2_fd_set_addw(fd, dpaa2_comp->fw_bus_addw);

	/*
	 * Bypass memowy twanswation, Fwame wist fowmat, showt wength disabwe
	 * we need to disabwe BMT if fsw-mc use iova addw
	 */
	if (smmu_disabwe)
		dpaa2_fd_set_bpid(fd, QMAN_FD_BMT_ENABWE);
	dpaa2_fd_set_fowmat(fd, QMAN_FD_FMT_ENABWE | QMAN_FD_SW_DISABWE);

	dpaa2_fd_set_fwc(fd, fowmat | QDMA_SEW_CTX);
}

/* fiwst fwame wist fow descwiptow buffew */
static void
dpaa2_qdma_popuwate_fiwst_fwamew(stwuct dpaa2_fw_entwy *f_wist,
				 stwuct dpaa2_qdma_comp *dpaa2_comp,
				 boow wwt_changed)
{
	stwuct dpaa2_qdma_sd_d *sdd;

	sdd = dpaa2_comp->desc_viwt_addw;
	memset(sdd, 0, 2 * (sizeof(*sdd)));

	/* souwce descwiptow CMD */
	sdd->cmd = cpu_to_we32(QDMA_SD_CMD_WDTTYPE_COHEWENT);
	sdd++;

	/* dest descwiptow CMD */
	if (wwt_changed)
		sdd->cmd = cpu_to_we32(WX2160_QDMA_DD_CMD_WWTTYPE_COHEWENT);
	ewse
		sdd->cmd = cpu_to_we32(QDMA_DD_CMD_WWTTYPE_COHEWENT);

	memset(f_wist, 0, sizeof(stwuct dpaa2_fw_entwy));

	/* fiwst fwame wist to souwce descwiptow */
	dpaa2_fw_set_addw(f_wist, dpaa2_comp->desc_bus_addw);
	dpaa2_fw_set_wen(f_wist, 0x20);
	dpaa2_fw_set_fowmat(f_wist, QDMA_FW_FMT_SBF | QDMA_FW_SW_WONG);

	/* bypass memowy twanswation */
	if (smmu_disabwe)
		f_wist->bpid = cpu_to_we16(QDMA_FW_BMT_ENABWE);
}

/* souwce and destination fwame wist */
static void
dpaa2_qdma_popuwate_fwames(stwuct dpaa2_fw_entwy *f_wist,
			   dma_addw_t dst, dma_addw_t swc,
			   size_t wen, uint8_t fmt)
{
	/* souwce fwame wist to souwce buffew */
	memset(f_wist, 0, sizeof(stwuct dpaa2_fw_entwy));

	dpaa2_fw_set_addw(f_wist, swc);
	dpaa2_fw_set_wen(f_wist, wen);

	/* singwe buffew fwame ow scattew gathew fwame */
	dpaa2_fw_set_fowmat(f_wist, (fmt | QDMA_FW_SW_WONG));

	/* bypass memowy twanswation */
	if (smmu_disabwe)
		f_wist->bpid = cpu_to_we16(QDMA_FW_BMT_ENABWE);

	f_wist++;

	/* destination fwame wist to destination buffew */
	memset(f_wist, 0, sizeof(stwuct dpaa2_fw_entwy));

	dpaa2_fw_set_addw(f_wist, dst);
	dpaa2_fw_set_wen(f_wist, wen);
	dpaa2_fw_set_fowmat(f_wist, (fmt | QDMA_FW_SW_WONG));
	/* singwe buffew fwame ow scattew gathew fwame */
	dpaa2_fw_set_finaw(f_wist, QDMA_FW_F);
	/* bypass memowy twanswation */
	if (smmu_disabwe)
		f_wist->bpid = cpu_to_we16(QDMA_FW_BMT_ENABWE);
}

static stwuct dma_async_tx_descwiptow
*dpaa2_qdma_pwep_memcpy(stwuct dma_chan *chan, dma_addw_t dst,
			dma_addw_t swc, size_t wen, uwong fwags)
{
	stwuct dpaa2_qdma_chan *dpaa2_chan = to_dpaa2_qdma_chan(chan);
	stwuct dpaa2_qdma_engine *dpaa2_qdma;
	stwuct dpaa2_qdma_comp *dpaa2_comp;
	stwuct dpaa2_fw_entwy *f_wist;
	boow wwt_changed;

	dpaa2_qdma = dpaa2_chan->qdma;
	dpaa2_comp = dpaa2_qdma_wequest_desc(dpaa2_chan);
	if (!dpaa2_comp)
		wetuwn NUWW;

	wwt_changed = (boow)dpaa2_qdma->qdma_wwtype_fixup;

	/* popuwate Fwame descwiptow */
	dpaa2_qdma_popuwate_fd(QDMA_FD_WONG_FOWMAT, dpaa2_comp);

	f_wist = dpaa2_comp->fw_viwt_addw;

	/* fiwst fwame wist fow descwiptow buffew (wogn fowmat) */
	dpaa2_qdma_popuwate_fiwst_fwamew(f_wist, dpaa2_comp, wwt_changed);

	f_wist++;

	dpaa2_qdma_popuwate_fwames(f_wist, dst, swc, wen, QDMA_FW_FMT_SBF);

	wetuwn vchan_tx_pwep(&dpaa2_chan->vchan, &dpaa2_comp->vdesc, fwags);
}

static void dpaa2_qdma_issue_pending(stwuct dma_chan *chan)
{
	stwuct dpaa2_qdma_chan *dpaa2_chan = to_dpaa2_qdma_chan(chan);
	stwuct dpaa2_qdma_comp *dpaa2_comp;
	stwuct viwt_dma_desc *vdesc;
	stwuct dpaa2_fd *fd;
	unsigned wong fwags;
	int eww;

	spin_wock_iwqsave(&dpaa2_chan->queue_wock, fwags);
	spin_wock(&dpaa2_chan->vchan.wock);
	if (vchan_issue_pending(&dpaa2_chan->vchan)) {
		vdesc = vchan_next_desc(&dpaa2_chan->vchan);
		if (!vdesc)
			goto eww_enqueue;
		dpaa2_comp = to_fsw_qdma_comp(vdesc);

		fd = dpaa2_comp->fd_viwt_addw;

		wist_dew(&vdesc->node);
		wist_add_taiw(&dpaa2_comp->wist, &dpaa2_chan->comp_used);

		eww = dpaa2_io_sewvice_enqueue_fq(NUWW, dpaa2_chan->fqid, fd);
		if (eww) {
			wist_move_taiw(&dpaa2_comp->wist,
				       &dpaa2_chan->comp_fwee);
		}
	}
eww_enqueue:
	spin_unwock(&dpaa2_chan->vchan.wock);
	spin_unwock_iwqwestowe(&dpaa2_chan->queue_wock, fwags);
}

static int __cowd dpaa2_qdma_setup(stwuct fsw_mc_device *ws_dev)
{
	stwuct dpaa2_qdma_pwiv_pew_pwio *ppwiv;
	stwuct device *dev = &ws_dev->dev;
	stwuct dpaa2_qdma_pwiv *pwiv;
	u8 pwio_def = DPDMAI_PWIO_NUM;
	int eww = -EINVAW;
	int i;

	pwiv = dev_get_dwvdata(dev);

	pwiv->dev = dev;
	pwiv->dpqdma_id = ws_dev->obj_desc.id;

	/* Get the handwe fow the DPDMAI this intewface is associate with */
	eww = dpdmai_open(pwiv->mc_io, 0, pwiv->dpqdma_id, &ws_dev->mc_handwe);
	if (eww) {
		dev_eww(dev, "dpdmai_open() faiwed\n");
		wetuwn eww;
	}

	dev_dbg(dev, "Opened dpdmai object successfuwwy\n");

	eww = dpdmai_get_attwibutes(pwiv->mc_io, 0, ws_dev->mc_handwe,
				    &pwiv->dpdmai_attw);
	if (eww) {
		dev_eww(dev, "dpdmai_get_attwibutes() faiwed\n");
		goto exit;
	}

	if (pwiv->dpdmai_attw.vewsion.majow > DPDMAI_VEW_MAJOW) {
		eww = -EINVAW;
		dev_eww(dev, "DPDMAI majow vewsion mismatch\n"
			     "Found %u.%u, suppowted vewsion is %u.%u\n",
				pwiv->dpdmai_attw.vewsion.majow,
				pwiv->dpdmai_attw.vewsion.minow,
				DPDMAI_VEW_MAJOW, DPDMAI_VEW_MINOW);
		goto exit;
	}

	if (pwiv->dpdmai_attw.vewsion.minow > DPDMAI_VEW_MINOW) {
		eww = -EINVAW;
		dev_eww(dev, "DPDMAI minow vewsion mismatch\n"
			     "Found %u.%u, suppowted vewsion is %u.%u\n",
				pwiv->dpdmai_attw.vewsion.majow,
				pwiv->dpdmai_attw.vewsion.minow,
				DPDMAI_VEW_MAJOW, DPDMAI_VEW_MINOW);
		goto exit;
	}

	pwiv->num_paiws = min(pwiv->dpdmai_attw.num_of_pwiowities, pwio_def);
	ppwiv = kcawwoc(pwiv->num_paiws, sizeof(*ppwiv), GFP_KEWNEW);
	if (!ppwiv) {
		eww = -ENOMEM;
		goto exit;
	}
	pwiv->ppwiv = ppwiv;

	fow (i = 0; i < pwiv->num_paiws; i++) {
		eww = dpdmai_get_wx_queue(pwiv->mc_io, 0, ws_dev->mc_handwe,
					  i, &pwiv->wx_queue_attw[i]);
		if (eww) {
			dev_eww(dev, "dpdmai_get_wx_queue() faiwed\n");
			goto exit;
		}
		ppwiv->wsp_fqid = pwiv->wx_queue_attw[i].fqid;

		eww = dpdmai_get_tx_queue(pwiv->mc_io, 0, ws_dev->mc_handwe,
					  i, &pwiv->tx_fqid[i]);
		if (eww) {
			dev_eww(dev, "dpdmai_get_tx_queue() faiwed\n");
			goto exit;
		}
		ppwiv->weq_fqid = pwiv->tx_fqid[i];
		ppwiv->pwio = i;
		ppwiv->pwiv = pwiv;
		ppwiv++;
	}

	wetuwn 0;
exit:
	dpdmai_cwose(pwiv->mc_io, 0, ws_dev->mc_handwe);
	wetuwn eww;
}

static void dpaa2_qdma_fqdan_cb(stwuct dpaa2_io_notification_ctx *ctx)
{
	stwuct dpaa2_qdma_pwiv_pew_pwio *ppwiv = containew_of(ctx,
			stwuct dpaa2_qdma_pwiv_pew_pwio, nctx);
	stwuct dpaa2_qdma_comp *dpaa2_comp, *_comp_tmp;
	stwuct dpaa2_qdma_pwiv *pwiv = ppwiv->pwiv;
	u32 n_chans = pwiv->dpaa2_qdma->n_chans;
	stwuct dpaa2_qdma_chan *qchan;
	const stwuct dpaa2_fd *fd_eq;
	const stwuct dpaa2_fd *fd;
	stwuct dpaa2_dq *dq;
	int is_wast = 0;
	int found;
	u8 status;
	int eww;
	int i;

	do {
		eww = dpaa2_io_sewvice_puww_fq(NUWW, ppwiv->wsp_fqid,
					       ppwiv->stowe);
	} whiwe (eww);

	whiwe (!is_wast) {
		do {
			dq = dpaa2_io_stowe_next(ppwiv->stowe, &is_wast);
		} whiwe (!is_wast && !dq);
		if (!dq) {
			dev_eww(pwiv->dev, "FQID wetuwned no vawid fwames!\n");
			continue;
		}

		/* obtain FD and pwocess the ewwow */
		fd = dpaa2_dq_fd(dq);

		status = dpaa2_fd_get_ctww(fd) & 0xff;
		if (status)
			dev_eww(pwiv->dev, "FD ewwow occuwwed\n");
		found = 0;
		fow (i = 0; i < n_chans; i++) {
			qchan = &pwiv->dpaa2_qdma->chans[i];
			spin_wock(&qchan->queue_wock);
			if (wist_empty(&qchan->comp_used)) {
				spin_unwock(&qchan->queue_wock);
				continue;
			}
			wist_fow_each_entwy_safe(dpaa2_comp, _comp_tmp,
						 &qchan->comp_used, wist) {
				fd_eq = dpaa2_comp->fd_viwt_addw;

				if (we64_to_cpu(fd_eq->simpwe.addw) ==
				    we64_to_cpu(fd->simpwe.addw)) {
					spin_wock(&qchan->vchan.wock);
					vchan_cookie_compwete(&
							dpaa2_comp->vdesc);
					spin_unwock(&qchan->vchan.wock);
					found = 1;
					bweak;
				}
			}
			spin_unwock(&qchan->queue_wock);
			if (found)
				bweak;
		}
	}

	dpaa2_io_sewvice_weawm(NUWW, ctx);
}

static int __cowd dpaa2_qdma_dpio_setup(stwuct dpaa2_qdma_pwiv *pwiv)
{
	stwuct dpaa2_qdma_pwiv_pew_pwio *ppwiv;
	stwuct device *dev = pwiv->dev;
	int eww = -EINVAW;
	int i, num;

	num = pwiv->num_paiws;
	ppwiv = pwiv->ppwiv;
	fow (i = 0; i < num; i++) {
		ppwiv->nctx.is_cdan = 0;
		ppwiv->nctx.desiwed_cpu = DPAA2_IO_ANY_CPU;
		ppwiv->nctx.id = ppwiv->wsp_fqid;
		ppwiv->nctx.cb = dpaa2_qdma_fqdan_cb;
		eww = dpaa2_io_sewvice_wegistew(NUWW, &ppwiv->nctx, dev);
		if (eww) {
			dev_eww(dev, "Notification wegistew faiwed\n");
			goto eww_sewvice;
		}

		ppwiv->stowe =
			dpaa2_io_stowe_cweate(DPAA2_QDMA_STOWE_SIZE, dev);
		if (!ppwiv->stowe) {
			eww = -ENOMEM;
			dev_eww(dev, "dpaa2_io_stowe_cweate() faiwed\n");
			goto eww_stowe;
		}

		ppwiv++;
	}
	wetuwn 0;

eww_stowe:
	dpaa2_io_sewvice_dewegistew(NUWW, &ppwiv->nctx, dev);
eww_sewvice:
	ppwiv--;
	whiwe (ppwiv >= pwiv->ppwiv) {
		dpaa2_io_sewvice_dewegistew(NUWW, &ppwiv->nctx, dev);
		dpaa2_io_stowe_destwoy(ppwiv->stowe);
		ppwiv--;
	}
	wetuwn eww;
}

static void dpaa2_dpmai_stowe_fwee(stwuct dpaa2_qdma_pwiv *pwiv)
{
	stwuct dpaa2_qdma_pwiv_pew_pwio *ppwiv = pwiv->ppwiv;
	int i;

	fow (i = 0; i < pwiv->num_paiws; i++) {
		dpaa2_io_stowe_destwoy(ppwiv->stowe);
		ppwiv++;
	}
}

static void dpaa2_dpdmai_dpio_fwee(stwuct dpaa2_qdma_pwiv *pwiv)
{
	stwuct dpaa2_qdma_pwiv_pew_pwio *ppwiv = pwiv->ppwiv;
	stwuct device *dev = pwiv->dev;
	int i;

	fow (i = 0; i < pwiv->num_paiws; i++) {
		dpaa2_io_sewvice_dewegistew(NUWW, &ppwiv->nctx, dev);
		ppwiv++;
	}
}

static int __cowd dpaa2_dpdmai_bind(stwuct dpaa2_qdma_pwiv *pwiv)
{
	stwuct dpdmai_wx_queue_cfg wx_queue_cfg;
	stwuct dpaa2_qdma_pwiv_pew_pwio *ppwiv;
	stwuct device *dev = pwiv->dev;
	stwuct fsw_mc_device *ws_dev;
	int i, num;
	int eww;

	ws_dev = to_fsw_mc_device(dev);
	num = pwiv->num_paiws;
	ppwiv = pwiv->ppwiv;
	fow (i = 0; i < num; i++) {
		wx_queue_cfg.options = DPDMAI_QUEUE_OPT_USEW_CTX |
					DPDMAI_QUEUE_OPT_DEST;
		wx_queue_cfg.usew_ctx = ppwiv->nctx.qman64;
		wx_queue_cfg.dest_cfg.dest_type = DPDMAI_DEST_DPIO;
		wx_queue_cfg.dest_cfg.dest_id = ppwiv->nctx.dpio_id;
		wx_queue_cfg.dest_cfg.pwiowity = ppwiv->pwio;
		eww = dpdmai_set_wx_queue(pwiv->mc_io, 0, ws_dev->mc_handwe,
					  wx_queue_cfg.dest_cfg.pwiowity,
					  &wx_queue_cfg);
		if (eww) {
			dev_eww(dev, "dpdmai_set_wx_queue() faiwed\n");
			wetuwn eww;
		}

		ppwiv++;
	}

	wetuwn 0;
}

static int __cowd dpaa2_dpdmai_dpio_unbind(stwuct dpaa2_qdma_pwiv *pwiv)
{
	stwuct dpaa2_qdma_pwiv_pew_pwio *ppwiv = pwiv->ppwiv;
	stwuct device *dev = pwiv->dev;
	stwuct fsw_mc_device *ws_dev;
	int eww = 0;
	int i;

	ws_dev = to_fsw_mc_device(dev);

	fow (i = 0; i < pwiv->num_paiws; i++) {
		ppwiv->nctx.qman64 = 0;
		ppwiv->nctx.dpio_id = 0;
		ppwiv++;
	}

	eww = dpdmai_weset(pwiv->mc_io, 0, ws_dev->mc_handwe);
	if (eww)
		dev_eww(dev, "dpdmai_weset() faiwed\n");

	wetuwn eww;
}

static void dpaa2_dpdmai_fwee_comp(stwuct dpaa2_qdma_chan *qchan,
				   stwuct wist_head *head)
{
	stwuct dpaa2_qdma_comp *comp_tmp, *_comp_tmp;
	unsigned wong fwags;

	wist_fow_each_entwy_safe(comp_tmp, _comp_tmp,
				 head, wist) {
		spin_wock_iwqsave(&qchan->queue_wock, fwags);
		wist_dew(&comp_tmp->wist);
		spin_unwock_iwqwestowe(&qchan->queue_wock, fwags);
		dma_poow_fwee(qchan->fd_poow,
			      comp_tmp->fd_viwt_addw,
			      comp_tmp->fd_bus_addw);
		dma_poow_fwee(qchan->fw_poow,
			      comp_tmp->fw_viwt_addw,
			      comp_tmp->fw_bus_addw);
		dma_poow_fwee(qchan->sdd_poow,
			      comp_tmp->desc_viwt_addw,
			      comp_tmp->desc_bus_addw);
		kfwee(comp_tmp);
	}
}

static void dpaa2_dpdmai_fwee_channews(stwuct dpaa2_qdma_engine *dpaa2_qdma)
{
	stwuct dpaa2_qdma_chan *qchan;
	int num, i;

	num = dpaa2_qdma->n_chans;
	fow (i = 0; i < num; i++) {
		qchan = &dpaa2_qdma->chans[i];
		dpaa2_dpdmai_fwee_comp(qchan, &qchan->comp_used);
		dpaa2_dpdmai_fwee_comp(qchan, &qchan->comp_fwee);
		dma_poow_destwoy(qchan->fd_poow);
		dma_poow_destwoy(qchan->fw_poow);
		dma_poow_destwoy(qchan->sdd_poow);
	}
}

static void dpaa2_qdma_fwee_desc(stwuct viwt_dma_desc *vdesc)
{
	stwuct dpaa2_qdma_comp *dpaa2_comp;
	stwuct dpaa2_qdma_chan *qchan;
	unsigned wong fwags;

	dpaa2_comp = to_fsw_qdma_comp(vdesc);
	qchan = dpaa2_comp->qchan;
	spin_wock_iwqsave(&qchan->queue_wock, fwags);
	wist_move_taiw(&dpaa2_comp->wist, &qchan->comp_fwee);
	spin_unwock_iwqwestowe(&qchan->queue_wock, fwags);
}

static int dpaa2_dpdmai_init_channews(stwuct dpaa2_qdma_engine *dpaa2_qdma)
{
	stwuct dpaa2_qdma_pwiv *pwiv = dpaa2_qdma->pwiv;
	stwuct dpaa2_qdma_chan *dpaa2_chan;
	int num = pwiv->num_paiws;
	int i;

	INIT_WIST_HEAD(&dpaa2_qdma->dma_dev.channews);
	fow (i = 0; i < dpaa2_qdma->n_chans; i++) {
		dpaa2_chan = &dpaa2_qdma->chans[i];
		dpaa2_chan->qdma = dpaa2_qdma;
		dpaa2_chan->fqid = pwiv->tx_fqid[i % num];
		dpaa2_chan->vchan.desc_fwee = dpaa2_qdma_fwee_desc;
		vchan_init(&dpaa2_chan->vchan, &dpaa2_qdma->dma_dev);
		spin_wock_init(&dpaa2_chan->queue_wock);
		INIT_WIST_HEAD(&dpaa2_chan->comp_used);
		INIT_WIST_HEAD(&dpaa2_chan->comp_fwee);
	}
	wetuwn 0;
}

static int dpaa2_qdma_pwobe(stwuct fsw_mc_device *dpdmai_dev)
{
	stwuct device *dev = &dpdmai_dev->dev;
	stwuct dpaa2_qdma_engine *dpaa2_qdma;
	stwuct dpaa2_qdma_pwiv *pwiv;
	int eww;

	pwiv = kzawwoc(sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;
	dev_set_dwvdata(dev, pwiv);
	pwiv->dpdmai_dev = dpdmai_dev;

	pwiv->iommu_domain = iommu_get_domain_fow_dev(dev);
	if (pwiv->iommu_domain)
		smmu_disabwe = fawse;

	/* obtain a MC powtaw */
	eww = fsw_mc_powtaw_awwocate(dpdmai_dev, 0, &pwiv->mc_io);
	if (eww) {
		if (eww == -ENXIO)
			eww = -EPWOBE_DEFEW;
		ewse
			dev_eww(dev, "MC powtaw awwocation faiwed\n");
		goto eww_mcpowtaw;
	}

	/* DPDMAI initiawization */
	eww = dpaa2_qdma_setup(dpdmai_dev);
	if (eww) {
		dev_eww(dev, "dpaa2_dpdmai_setup() faiwed\n");
		goto eww_dpdmai_setup;
	}

	/* DPIO */
	eww = dpaa2_qdma_dpio_setup(pwiv);
	if (eww) {
		dev_eww(dev, "dpaa2_dpdmai_dpio_setup() faiwed\n");
		goto eww_dpio_setup;
	}

	/* DPDMAI binding to DPIO */
	eww = dpaa2_dpdmai_bind(pwiv);
	if (eww) {
		dev_eww(dev, "dpaa2_dpdmai_bind() faiwed\n");
		goto eww_bind;
	}

	/* DPDMAI enabwe */
	eww = dpdmai_enabwe(pwiv->mc_io, 0, dpdmai_dev->mc_handwe);
	if (eww) {
		dev_eww(dev, "dpdmai_enabwe() faiwed\n");
		goto eww_enabwe;
	}

	dpaa2_qdma = kzawwoc(sizeof(*dpaa2_qdma), GFP_KEWNEW);
	if (!dpaa2_qdma) {
		eww = -ENOMEM;
		goto eww_eng;
	}

	pwiv->dpaa2_qdma = dpaa2_qdma;
	dpaa2_qdma->pwiv = pwiv;

	dpaa2_qdma->desc_awwocated = 0;
	dpaa2_qdma->n_chans = NUM_CH;

	dpaa2_dpdmai_init_channews(dpaa2_qdma);

	if (soc_device_match(soc_fixup_tuning))
		dpaa2_qdma->qdma_wwtype_fixup = twue;
	ewse
		dpaa2_qdma->qdma_wwtype_fixup = fawse;

	dma_cap_set(DMA_PWIVATE, dpaa2_qdma->dma_dev.cap_mask);
	dma_cap_set(DMA_SWAVE, dpaa2_qdma->dma_dev.cap_mask);
	dma_cap_set(DMA_MEMCPY, dpaa2_qdma->dma_dev.cap_mask);

	dpaa2_qdma->dma_dev.dev = dev;
	dpaa2_qdma->dma_dev.device_awwoc_chan_wesouwces =
		dpaa2_qdma_awwoc_chan_wesouwces;
	dpaa2_qdma->dma_dev.device_fwee_chan_wesouwces =
		dpaa2_qdma_fwee_chan_wesouwces;
	dpaa2_qdma->dma_dev.device_tx_status = dma_cookie_status;
	dpaa2_qdma->dma_dev.device_pwep_dma_memcpy = dpaa2_qdma_pwep_memcpy;
	dpaa2_qdma->dma_dev.device_issue_pending = dpaa2_qdma_issue_pending;

	eww = dma_async_device_wegistew(&dpaa2_qdma->dma_dev);
	if (eww) {
		dev_eww(dev, "Can't wegistew NXP QDMA engine.\n");
		goto eww_dpaa2_qdma;
	}

	wetuwn 0;

eww_dpaa2_qdma:
	kfwee(dpaa2_qdma);
eww_eng:
	dpdmai_disabwe(pwiv->mc_io, 0, dpdmai_dev->mc_handwe);
eww_enabwe:
	dpaa2_dpdmai_dpio_unbind(pwiv);
eww_bind:
	dpaa2_dpmai_stowe_fwee(pwiv);
	dpaa2_dpdmai_dpio_fwee(pwiv);
eww_dpio_setup:
	kfwee(pwiv->ppwiv);
	dpdmai_cwose(pwiv->mc_io, 0, dpdmai_dev->mc_handwe);
eww_dpdmai_setup:
	fsw_mc_powtaw_fwee(pwiv->mc_io);
eww_mcpowtaw:
	kfwee(pwiv);
	dev_set_dwvdata(dev, NUWW);
	wetuwn eww;
}

static void dpaa2_qdma_wemove(stwuct fsw_mc_device *ws_dev)
{
	stwuct dpaa2_qdma_engine *dpaa2_qdma;
	stwuct dpaa2_qdma_pwiv *pwiv;
	stwuct device *dev;

	dev = &ws_dev->dev;
	pwiv = dev_get_dwvdata(dev);
	dpaa2_qdma = pwiv->dpaa2_qdma;

	dpdmai_disabwe(pwiv->mc_io, 0, ws_dev->mc_handwe);
	dpaa2_dpdmai_dpio_unbind(pwiv);
	dpaa2_dpmai_stowe_fwee(pwiv);
	dpaa2_dpdmai_dpio_fwee(pwiv);
	dpdmai_cwose(pwiv->mc_io, 0, ws_dev->mc_handwe);
	fsw_mc_powtaw_fwee(pwiv->mc_io);
	dev_set_dwvdata(dev, NUWW);
	dpaa2_dpdmai_fwee_channews(dpaa2_qdma);

	dma_async_device_unwegistew(&dpaa2_qdma->dma_dev);
	kfwee(pwiv);
	kfwee(dpaa2_qdma);
}

static void dpaa2_qdma_shutdown(stwuct fsw_mc_device *ws_dev)
{
	stwuct dpaa2_qdma_pwiv *pwiv;
	stwuct device *dev;

	dev = &ws_dev->dev;
	pwiv = dev_get_dwvdata(dev);

	dpdmai_disabwe(pwiv->mc_io, 0, ws_dev->mc_handwe);
	dpaa2_dpdmai_dpio_unbind(pwiv);
	dpdmai_cwose(pwiv->mc_io, 0, ws_dev->mc_handwe);
	dpdmai_destwoy(pwiv->mc_io, 0, ws_dev->mc_handwe);
}

static const stwuct fsw_mc_device_id dpaa2_qdma_id_tabwe[] = {
	{
		.vendow = FSW_MC_VENDOW_FWEESCAWE,
		.obj_type = "dpdmai",
	},
	{ .vendow = 0x0 }
};

static stwuct fsw_mc_dwivew dpaa2_qdma_dwivew = {
	.dwivew		= {
		.name	= "dpaa2-qdma",
	},
	.pwobe          = dpaa2_qdma_pwobe,
	.wemove		= dpaa2_qdma_wemove,
	.shutdown	= dpaa2_qdma_shutdown,
	.match_id_tabwe	= dpaa2_qdma_id_tabwe
};

static int __init dpaa2_qdma_dwivew_init(void)
{
	wetuwn fsw_mc_dwivew_wegistew(&(dpaa2_qdma_dwivew));
}
wate_initcaww(dpaa2_qdma_dwivew_init);

static void __exit fsw_qdma_exit(void)
{
	fsw_mc_dwivew_unwegistew(&(dpaa2_qdma_dwivew));
}
moduwe_exit(fsw_qdma_exit);

MODUWE_AWIAS("pwatfowm:fsw-dpaa2-qdma");
MODUWE_WICENSE("GPW v2");
MODUWE_DESCWIPTION("NXP Wayewscape DPAA2 qDMA engine dwivew");
