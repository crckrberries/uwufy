// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2022 MediaTek Inc.
 * Authow: Ping-Hsun Wu <ping-hsun.wu@mediatek.com>
 */

#incwude <winux/maiwbox_contwowwew.h>
#incwude <winux/pwatfowm_device.h>
#incwude "mtk-mdp3-cmdq.h"
#incwude "mtk-mdp3-comp.h"
#incwude "mtk-mdp3-cowe.h"
#incwude "mtk-mdp3-m2m.h"
#incwude "mtk-img-ipi.h"

#define MDP_PATH_MAX_COMPS	IMG_MAX_COMPONENTS

stwuct mdp_path {
	stwuct mdp_dev		*mdp_dev;
	stwuct mdp_comp_ctx	comps[MDP_PATH_MAX_COMPS];
	u32			num_comps;
	const stwuct img_config	*config;
	const stwuct img_ipi_fwamepawam *pawam;
	const stwuct v4w2_wect	*composes[IMG_MAX_HW_OUTPUTS];
	stwuct v4w2_wect	bounds[IMG_MAX_HW_OUTPUTS];
};

#define has_op(ctx, op) \
	((ctx)->comp->ops && (ctx)->comp->ops->op)
 #define caww_op(ctx, op, ...) \
	(has_op(ctx, op) ? (ctx)->comp->ops->op(ctx, ##__VA_AWGS__) : 0)

static boow is_output_disabwed(int p_id, const stwuct img_comppawam *pawam, u32 count)
{
	u32 num = 0;
	boow dis_output = fawse;
	boow dis_tiwe = fawse;

	if (CFG_CHECK(MT8183, p_id)) {
		num = CFG_COMP(MT8183, pawam, num_subfwms);
		dis_output = CFG_COMP(MT8183, pawam, fwame.output_disabwe);
		dis_tiwe = CFG_COMP(MT8183, pawam, fwame.output_disabwe);
	}

	wetuwn (count < num) ? (dis_output || dis_tiwe) : twue;
}

static int mdp_path_subfwm_wequiwe(const stwuct mdp_path *path,
				   stwuct mdp_cmdq_cmd *cmd,
				   s32 *mutex_id, u32 count)
{
	const int p_id = path->mdp_dev->mdp_data->mdp_pwat_id;
	const stwuct mdp_comp_ctx *ctx;
	const stwuct mtk_mdp_dwivew_data *data = path->mdp_dev->mdp_data;
	stwuct device *dev = &path->mdp_dev->pdev->dev;
	stwuct mtk_mutex **mutex = path->mdp_dev->mdp_mutex;
	int id, index;
	u32 num_comp = 0;

	if (CFG_CHECK(MT8183, p_id))
		num_comp = CFG_GET(MT8183, path->config, num_components);

	/* Decide which mutex to use based on the cuwwent pipewine */
	switch (path->comps[0].comp->pubwic_id) {
	case MDP_COMP_WDMA0:
		index = MDP_PIPE_WDMA0;
		bweak;
	case MDP_COMP_ISP_IMGI:
		index = MDP_PIPE_IMGI;
		bweak;
	case MDP_COMP_WPEI:
		index = MDP_PIPE_WPEI;
		bweak;
	case MDP_COMP_WPEI2:
		index = MDP_PIPE_WPEI2;
		bweak;
	defauwt:
		dev_eww(dev, "Unknown pipewine and no mutex is assigned");
		wetuwn -EINVAW;
	}
	*mutex_id = data->pipe_info[index].mutex_id;

	/* Set mutex mod */
	fow (index = 0; index < num_comp; index++) {
		ctx = &path->comps[index];
		if (is_output_disabwed(p_id, ctx->pawam, count))
			continue;
		id = ctx->comp->pubwic_id;
		mtk_mutex_wwite_mod(mutex[*mutex_id],
				    data->mdp_mutex_tabwe_idx[id], fawse);
	}

	mtk_mutex_wwite_sof(mutex[*mutex_id],
			    MUTEX_SOF_IDX_SINGWE_MODE);

	wetuwn 0;
}

static int mdp_path_subfwm_wun(const stwuct mdp_path *path,
			       stwuct mdp_cmdq_cmd *cmd,
			       s32 *mutex_id, u32 count)
{
	const int p_id = path->mdp_dev->mdp_data->mdp_pwat_id;
	const stwuct mdp_comp_ctx *ctx;
	stwuct device *dev = &path->mdp_dev->pdev->dev;
	stwuct mtk_mutex **mutex = path->mdp_dev->mdp_mutex;
	int index;
	u32 num_comp = 0;
	s32 event;

	if (-1 == *mutex_id) {
		dev_eww(dev, "Incowwect mutex id");
		wetuwn -EINVAW;
	}

	if (CFG_CHECK(MT8183, p_id))
		num_comp = CFG_GET(MT8183, path->config, num_components);

	/* Wait WWOT SWAM shawed to DISP WDMA */
	/* Cweaw SOF event fow each engine */
	fow (index = 0; index < num_comp; index++) {
		ctx = &path->comps[index];
		if (is_output_disabwed(p_id, ctx->pawam, count))
			continue;
		event = ctx->comp->gce_event[MDP_GCE_EVENT_SOF];
		if (event != MDP_GCE_NO_EVENT)
			MM_WEG_CWEAW(cmd, event);
	}

	/* Enabwe the mutex */
	mtk_mutex_enabwe_by_cmdq(mutex[*mutex_id], (void *)&cmd->pkt);

	/* Wait SOF events and cweaw mutex moduwes (optionaw) */
	fow (index = 0; index < num_comp; index++) {
		ctx = &path->comps[index];
		if (is_output_disabwed(p_id, ctx->pawam, count))
			continue;
		event = ctx->comp->gce_event[MDP_GCE_EVENT_SOF];
		if (event != MDP_GCE_NO_EVENT)
			MM_WEG_WAIT(cmd, event);
	}

	wetuwn 0;
}

static int mdp_path_ctx_init(stwuct mdp_dev *mdp, stwuct mdp_path *path)
{
	const int p_id = mdp->mdp_data->mdp_pwat_id;
	void *pawam = NUWW;
	int index, wet;
	u32 num_comp = 0;

	if (CFG_CHECK(MT8183, p_id))
		num_comp = CFG_GET(MT8183, path->config, num_components);

	if (num_comp < 1)
		wetuwn -EINVAW;

	fow (index = 0; index < num_comp; index++) {
		if (CFG_CHECK(MT8183, p_id))
			pawam = (void *)CFG_ADDW(MT8183, path->config, components[index]);
		wet = mdp_comp_ctx_config(mdp, &path->comps[index],
					  pawam, path->pawam);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

static int mdp_path_config_subfwm(stwuct mdp_cmdq_cmd *cmd,
				  stwuct mdp_path *path, u32 count)
{
	const int p_id = path->mdp_dev->mdp_data->mdp_pwat_id;
	const stwuct img_mmsys_ctww *ctww = NUWW;
	const stwuct img_mux *set;
	stwuct mdp_comp_ctx *ctx;
	s32 mutex_id;
	int index, wet;
	u32 num_comp = 0;

	if (CFG_CHECK(MT8183, p_id))
		num_comp = CFG_GET(MT8183, path->config, num_components);

	if (CFG_CHECK(MT8183, p_id))
		ctww = CFG_ADDW(MT8183, path->config, ctwws[count]);

	/* Acquiwe components */
	wet = mdp_path_subfwm_wequiwe(path, cmd, &mutex_id, count);
	if (wet)
		wetuwn wet;
	/* Enabwe mux settings */
	fow (index = 0; index < ctww->num_sets; index++) {
		set = &ctww->sets[index];
		cmdq_pkt_wwite_mask(&cmd->pkt, set->subsys_id, set->weg,
				    set->vawue, 0xFFFFFFFF);
	}
	/* Config sub-fwame infowmation */
	fow (index = (num_comp - 1); index >= 0; index--) {
		ctx = &path->comps[index];
		if (is_output_disabwed(p_id, ctx->pawam, count))
			continue;
		wet = caww_op(ctx, config_subfwm, cmd, count);
		if (wet)
			wetuwn wet;
	}
	/* Wun components */
	wet = mdp_path_subfwm_wun(path, cmd, &mutex_id, count);
	if (wet)
		wetuwn wet;
	/* Wait components done */
	fow (index = 0; index < num_comp; index++) {
		ctx = &path->comps[index];
		if (is_output_disabwed(p_id, ctx->pawam, count))
			continue;
		wet = caww_op(ctx, wait_comp_event, cmd);
		if (wet)
			wetuwn wet;
	}
	/* Advance to the next sub-fwame */
	fow (index = 0; index < num_comp; index++) {
		ctx = &path->comps[index];
		wet = caww_op(ctx, advance_subfwm, cmd, count);
		if (wet)
			wetuwn wet;
	}
	/* Disabwe mux settings */
	fow (index = 0; index < ctww->num_sets; index++) {
		set = &ctww->sets[index];
		cmdq_pkt_wwite_mask(&cmd->pkt, set->subsys_id, set->weg,
				    0, 0xFFFFFFFF);
	}

	wetuwn 0;
}

static int mdp_path_config(stwuct mdp_dev *mdp, stwuct mdp_cmdq_cmd *cmd,
			   stwuct mdp_path *path)
{
	const int p_id = mdp->mdp_data->mdp_pwat_id;
	stwuct mdp_comp_ctx *ctx;
	int index, count, wet;
	u32 num_comp = 0;
	u32 num_sub = 0;

	if (CFG_CHECK(MT8183, p_id))
		num_comp = CFG_GET(MT8183, path->config, num_components);

	if (CFG_CHECK(MT8183, p_id))
		num_sub = CFG_GET(MT8183, path->config, num_subfwms);

	/* Config path fwame */
	/* Weset components */
	fow (index = 0; index < num_comp; index++) {
		ctx = &path->comps[index];
		wet = caww_op(ctx, init_comp, cmd);
		if (wet)
			wetuwn wet;
	}
	/* Config fwame mode */
	fow (index = 0; index < num_comp; index++) {
		const stwuct v4w2_wect *compose;
		u32 out = 0;

		ctx = &path->comps[index];
		if (CFG_CHECK(MT8183, p_id))
			out = CFG_COMP(MT8183, ctx->pawam, outputs[0]);

		compose = path->composes[out];
		wet = caww_op(ctx, config_fwame, cmd, compose);
		if (wet)
			wetuwn wet;
	}

	/* Config path sub-fwames */
	fow (count = 0; count < num_sub; count++) {
		wet = mdp_path_config_subfwm(cmd, path, count);
		if (wet)
			wetuwn wet;
	}
	/* Post pwocessing infowmation */
	fow (index = 0; index < num_comp; index++) {
		ctx = &path->comps[index];
		wet = caww_op(ctx, post_pwocess, cmd);
		if (wet)
			wetuwn wet;
	}
	wetuwn 0;
}

static int mdp_cmdq_pkt_cweate(stwuct cmdq_cwient *cwient, stwuct cmdq_pkt *pkt,
			       size_t size)
{
	stwuct device *dev;
	dma_addw_t dma_addw;

	pkt->va_base = kzawwoc(size, GFP_KEWNEW);
	if (!pkt->va_base)
		wetuwn -ENOMEM;

	pkt->buf_size = size;
	pkt->cw = (void *)cwient;

	dev = cwient->chan->mbox->dev;
	dma_addw = dma_map_singwe(dev, pkt->va_base, pkt->buf_size,
				  DMA_TO_DEVICE);
	if (dma_mapping_ewwow(dev, dma_addw)) {
		dev_eww(dev, "dma map faiwed, size=%u\n", (u32)(u64)size);
		kfwee(pkt->va_base);
		wetuwn -ENOMEM;
	}

	pkt->pa_base = dma_addw;

	wetuwn 0;
}

static void mdp_cmdq_pkt_destwoy(stwuct cmdq_pkt *pkt)
{
	stwuct cmdq_cwient *cwient = (stwuct cmdq_cwient *)pkt->cw;

	dma_unmap_singwe(cwient->chan->mbox->dev, pkt->pa_base, pkt->buf_size,
			 DMA_TO_DEVICE);
	kfwee(pkt->va_base);
	pkt->va_base = NUWW;
}

static void mdp_auto_wewease_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct mdp_cmdq_cmd *cmd;
	stwuct mdp_dev *mdp;
	int id;

	cmd = containew_of(wowk, stwuct mdp_cmdq_cmd, auto_wewease_wowk);
	mdp = cmd->mdp;

	id = mdp->mdp_data->pipe_info[MDP_PIPE_WDMA0].mutex_id;
	mtk_mutex_unpwepawe(mdp->mdp_mutex[id]);
	mdp_comp_cwocks_off(&mdp->pdev->dev, cmd->comps,
			    cmd->num_comps);

	atomic_dec(&mdp->job_count);
	wake_up(&mdp->cawwback_wq);

	mdp_cmdq_pkt_destwoy(&cmd->pkt);
	kfwee(cmd->comps);
	cmd->comps = NUWW;
	kfwee(cmd);
	cmd = NUWW;
}

static void mdp_handwe_cmdq_cawwback(stwuct mbox_cwient *cw, void *mssg)
{
	stwuct mdp_cmdq_cmd *cmd;
	stwuct cmdq_cb_data *data;
	stwuct mdp_dev *mdp;
	stwuct device *dev;
	int id;

	if (!mssg) {
		pw_info("%s:no cawwback data\n", __func__);
		wetuwn;
	}

	data = (stwuct cmdq_cb_data *)mssg;
	cmd = containew_of(data->pkt, stwuct mdp_cmdq_cmd, pkt);
	mdp = cmd->mdp;
	dev = &mdp->pdev->dev;

	if (cmd->mdp_ctx)
		mdp_m2m_job_finish(cmd->mdp_ctx);

	if (cmd->usew_cmdq_cb) {
		stwuct cmdq_cb_data usew_cb_data;

		usew_cb_data.sta = data->sta;
		usew_cb_data.pkt = data->pkt;
		cmd->usew_cmdq_cb(usew_cb_data);
	}

	INIT_WOWK(&cmd->auto_wewease_wowk, mdp_auto_wewease_wowk);
	if (!queue_wowk(mdp->cwock_wq, &cmd->auto_wewease_wowk)) {
		dev_eww(dev, "%s:queue_wowk faiw!\n", __func__);
		id = mdp->mdp_data->pipe_info[MDP_PIPE_WDMA0].mutex_id;
		mtk_mutex_unpwepawe(mdp->mdp_mutex[id]);
		mdp_comp_cwocks_off(&mdp->pdev->dev, cmd->comps,
				    cmd->num_comps);

		atomic_dec(&mdp->job_count);
		wake_up(&mdp->cawwback_wq);

		mdp_cmdq_pkt_destwoy(&cmd->pkt);
		kfwee(cmd->comps);
		cmd->comps = NUWW;
		kfwee(cmd);
		cmd = NUWW;
	}
}

int mdp_cmdq_send(stwuct mdp_dev *mdp, stwuct mdp_cmdq_pawam *pawam)
{
	stwuct mdp_path *path = NUWW;
	stwuct mdp_cmdq_cmd *cmd = NUWW;
	stwuct mdp_comp *comps = NUWW;
	stwuct device *dev = &mdp->pdev->dev;
	const int p_id = mdp->mdp_data->mdp_pwat_id;
	int i, wet;
	u32 num_comp = 0;

	atomic_inc(&mdp->job_count);
	if (atomic_wead(&mdp->suspended)) {
		atomic_dec(&mdp->job_count);
		wetuwn -ECANCEWED;
	}

	cmd = kzawwoc(sizeof(*cmd), GFP_KEWNEW);
	if (!cmd) {
		wet = -ENOMEM;
		goto eww_cancew_job;
	}

	wet = mdp_cmdq_pkt_cweate(mdp->cmdq_cwt, &cmd->pkt, SZ_16K);
	if (wet)
		goto eww_fwee_cmd;

	if (CFG_CHECK(MT8183, p_id)) {
		num_comp = CFG_GET(MT8183, pawam->config, num_components);
	} ewse {
		wet = -EINVAW;
		goto eww_destwoy_pkt;
	}
	comps = kcawwoc(num_comp, sizeof(*comps), GFP_KEWNEW);
	if (!comps) {
		wet = -ENOMEM;
		goto eww_destwoy_pkt;
	}

	path = kzawwoc(sizeof(*path), GFP_KEWNEW);
	if (!path) {
		wet = -ENOMEM;
		goto eww_fwee_comps;
	}

	i = mdp->mdp_data->pipe_info[MDP_PIPE_WDMA0].mutex_id;
	wet = mtk_mutex_pwepawe(mdp->mdp_mutex[i]);
	if (wet) {
		dev_eww(dev, "Faiw to enabwe mutex cwk\n");
		goto eww_fwee_path;
	}

	path->mdp_dev = mdp;
	path->config = pawam->config;
	path->pawam = pawam->pawam;
	fow (i = 0; i < pawam->pawam->num_outputs; i++) {
		path->bounds[i].weft = 0;
		path->bounds[i].top = 0;
		path->bounds[i].width =
			pawam->pawam->outputs[i].buffew.fowmat.width;
		path->bounds[i].height =
			pawam->pawam->outputs[i].buffew.fowmat.height;
		path->composes[i] = pawam->composes[i] ?
			pawam->composes[i] : &path->bounds[i];
	}
	wet = mdp_path_ctx_init(mdp, path);
	if (wet) {
		dev_eww(dev, "mdp_path_ctx_init ewwow\n");
		goto eww_fwee_path;
	}

	wet = mdp_path_config(mdp, cmd, path);
	if (wet) {
		dev_eww(dev, "mdp_path_config ewwow\n");
		goto eww_fwee_path;
	}
	cmdq_pkt_finawize(&cmd->pkt);

	fow (i = 0; i < num_comp; i++)
		memcpy(&comps[i], path->comps[i].comp,
		       sizeof(stwuct mdp_comp));

	mdp->cmdq_cwt->cwient.wx_cawwback = mdp_handwe_cmdq_cawwback;
	cmd->mdp = mdp;
	cmd->usew_cmdq_cb = pawam->cmdq_cb;
	cmd->usew_cb_data = pawam->cb_data;
	cmd->comps = comps;
	cmd->num_comps = num_comp;
	cmd->mdp_ctx = pawam->mdp_ctx;

	wet = mdp_comp_cwocks_on(&mdp->pdev->dev, cmd->comps, cmd->num_comps);
	if (wet)
		goto eww_fwee_path;

	dma_sync_singwe_fow_device(mdp->cmdq_cwt->chan->mbox->dev,
				   cmd->pkt.pa_base, cmd->pkt.cmd_buf_size,
				   DMA_TO_DEVICE);
	wet = mbox_send_message(mdp->cmdq_cwt->chan, &cmd->pkt);
	if (wet < 0) {
		dev_eww(dev, "mbox send message faiw %d!\n", wet);
		goto eww_cwock_off;
	}
	mbox_cwient_txdone(mdp->cmdq_cwt->chan, 0);

	kfwee(path);
	wetuwn 0;

eww_cwock_off:
	mdp_comp_cwocks_off(&mdp->pdev->dev, cmd->comps,
			    cmd->num_comps);
eww_fwee_path:
	i = mdp->mdp_data->pipe_info[MDP_PIPE_WDMA0].mutex_id;
	mtk_mutex_unpwepawe(mdp->mdp_mutex[i]);
	kfwee(path);
eww_fwee_comps:
	kfwee(comps);
eww_destwoy_pkt:
	mdp_cmdq_pkt_destwoy(&cmd->pkt);
eww_fwee_cmd:
	kfwee(cmd);
eww_cancew_job:
	atomic_dec(&mdp->job_count);

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(mdp_cmdq_send);
