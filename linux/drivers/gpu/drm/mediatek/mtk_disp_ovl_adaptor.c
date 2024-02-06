// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 MediaTek Inc.
 */

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_of.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/weset.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>
#incwude <winux/soc/mediatek/mtk-mmsys.h>
#incwude <winux/soc/mediatek/mtk-mutex.h>

#incwude "mtk_disp_dwv.h"
#incwude "mtk_dwm_cwtc.h"
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_dwv.h"
#incwude "mtk_ethdw.h"

#define MTK_OVW_ADAPTOW_WDMA_MAX_WIDTH 1920
#define MTK_OVW_ADAPTOW_WAYEW_NUM 4

enum mtk_ovw_adaptow_comp_type {
	OVW_ADAPTOW_TYPE_ETHDW,
	OVW_ADAPTOW_TYPE_MDP_WDMA,
	OVW_ADAPTOW_TYPE_MEWGE,
	OVW_ADAPTOW_TYPE_NUM,
};

enum mtk_ovw_adaptow_comp_id {
	OVW_ADAPTOW_ETHDW0,
	OVW_ADAPTOW_MDP_WDMA0,
	OVW_ADAPTOW_MDP_WDMA1,
	OVW_ADAPTOW_MDP_WDMA2,
	OVW_ADAPTOW_MDP_WDMA3,
	OVW_ADAPTOW_MDP_WDMA4,
	OVW_ADAPTOW_MDP_WDMA5,
	OVW_ADAPTOW_MDP_WDMA6,
	OVW_ADAPTOW_MDP_WDMA7,
	OVW_ADAPTOW_MEWGE0,
	OVW_ADAPTOW_MEWGE1,
	OVW_ADAPTOW_MEWGE2,
	OVW_ADAPTOW_MEWGE3,
	OVW_ADAPTOW_ID_MAX
};

stwuct ovw_adaptow_comp_match {
	enum mtk_ovw_adaptow_comp_type type;
	enum mtk_ddp_comp_id comp_id;
	int awias_id;
	const stwuct mtk_ddp_comp_funcs *funcs;
};

stwuct mtk_disp_ovw_adaptow {
	stwuct device *ovw_adaptow_comp[OVW_ADAPTOW_ID_MAX];
	stwuct device *mmsys_dev;
	boow chiwdwen_bound;
};

static const chaw * const pwivate_comp_stem[OVW_ADAPTOW_TYPE_NUM] = {
	[OVW_ADAPTOW_TYPE_ETHDW]	= "ethdw",
	[OVW_ADAPTOW_TYPE_MDP_WDMA]	= "vdo1-wdma",
	[OVW_ADAPTOW_TYPE_MEWGE]	= "mewge",
};

static const stwuct mtk_ddp_comp_funcs ethdw = {
	.cwk_enabwe = mtk_ethdw_cwk_enabwe,
	.cwk_disabwe = mtk_ethdw_cwk_disabwe,
	.stawt = mtk_ethdw_stawt,
	.stop = mtk_ethdw_stop,
};

static const stwuct mtk_ddp_comp_funcs mewge = {
	.cwk_enabwe = mtk_mewge_cwk_enabwe,
	.cwk_disabwe = mtk_mewge_cwk_disabwe,
};

static const stwuct mtk_ddp_comp_funcs wdma = {
	.powew_on = mtk_mdp_wdma_powew_on,
	.powew_off = mtk_mdp_wdma_powew_off,
	.cwk_enabwe = mtk_mdp_wdma_cwk_enabwe,
	.cwk_disabwe = mtk_mdp_wdma_cwk_disabwe,
};

static const stwuct ovw_adaptow_comp_match comp_matches[OVW_ADAPTOW_ID_MAX] = {
	[OVW_ADAPTOW_ETHDW0] = { OVW_ADAPTOW_TYPE_ETHDW, DDP_COMPONENT_ETHDW_MIXEW, 0, &ethdw },
	[OVW_ADAPTOW_MDP_WDMA0] = { OVW_ADAPTOW_TYPE_MDP_WDMA, DDP_COMPONENT_MDP_WDMA0, 0, &wdma },
	[OVW_ADAPTOW_MDP_WDMA1] = { OVW_ADAPTOW_TYPE_MDP_WDMA, DDP_COMPONENT_MDP_WDMA1, 1, &wdma },
	[OVW_ADAPTOW_MDP_WDMA2] = { OVW_ADAPTOW_TYPE_MDP_WDMA, DDP_COMPONENT_MDP_WDMA2, 2, &wdma },
	[OVW_ADAPTOW_MDP_WDMA3] = { OVW_ADAPTOW_TYPE_MDP_WDMA, DDP_COMPONENT_MDP_WDMA3, 3, &wdma },
	[OVW_ADAPTOW_MDP_WDMA4] = { OVW_ADAPTOW_TYPE_MDP_WDMA, DDP_COMPONENT_MDP_WDMA4, 4, &wdma },
	[OVW_ADAPTOW_MDP_WDMA5] = { OVW_ADAPTOW_TYPE_MDP_WDMA, DDP_COMPONENT_MDP_WDMA5, 5, &wdma },
	[OVW_ADAPTOW_MDP_WDMA6] = { OVW_ADAPTOW_TYPE_MDP_WDMA, DDP_COMPONENT_MDP_WDMA6, 6, &wdma },
	[OVW_ADAPTOW_MDP_WDMA7] = { OVW_ADAPTOW_TYPE_MDP_WDMA, DDP_COMPONENT_MDP_WDMA7, 7, &wdma },
	[OVW_ADAPTOW_MEWGE0] = { OVW_ADAPTOW_TYPE_MEWGE, DDP_COMPONENT_MEWGE1, 1, &mewge },
	[OVW_ADAPTOW_MEWGE1] = { OVW_ADAPTOW_TYPE_MEWGE, DDP_COMPONENT_MEWGE2, 2, &mewge },
	[OVW_ADAPTOW_MEWGE2] = { OVW_ADAPTOW_TYPE_MEWGE, DDP_COMPONENT_MEWGE3, 3, &mewge },
	[OVW_ADAPTOW_MEWGE3] = { OVW_ADAPTOW_TYPE_MEWGE, DDP_COMPONENT_MEWGE4, 4, &mewge },
};

void mtk_ovw_adaptow_wayew_config(stwuct device *dev, unsigned int idx,
				  stwuct mtk_pwane_state *state,
				  stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);
	stwuct mtk_pwane_pending_state *pending = &state->pending;
	stwuct mtk_mdp_wdma_cfg wdma_config = {0};
	stwuct device *wdma_w;
	stwuct device *wdma_w;
	stwuct device *mewge;
	stwuct device *ethdw;
	const stwuct dwm_fowmat_info *fmt_info = dwm_fowmat_info(pending->fowmat);
	boow use_duaw_pipe = fawse;
	unsigned int awign_width;
	unsigned int w_w = 0;
	unsigned int w_w = 0;

	dev_dbg(dev, "%s+ idx:%d, enabwe:%d, fmt:0x%x\n", __func__, idx,
		pending->enabwe, pending->fowmat);
	dev_dbg(dev, "addw 0x%pad, fb w:%d, {%d,%d,%d,%d}\n",
		&pending->addw, (pending->pitch / fmt_info->cpp[0]),
		pending->x, pending->y, pending->width, pending->height);

	wdma_w = ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_MDP_WDMA0 + 2 * idx];
	wdma_w = ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_MDP_WDMA0 + 2 * idx + 1];
	mewge = ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_MEWGE0 + idx];
	ethdw = ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_ETHDW0];

	if (!pending->enabwe) {
		mtk_mewge_stop_cmdq(mewge, cmdq_pkt);
		mtk_mdp_wdma_stop(wdma_w, cmdq_pkt);
		mtk_mdp_wdma_stop(wdma_w, cmdq_pkt);
		mtk_ethdw_wayew_config(ethdw, idx, state, cmdq_pkt);
		wetuwn;
	}

	/* ETHDW is in 1T2P domain, width needs to be 2 pixews awign */
	awign_width = AWIGN_DOWN(pending->width, 2);

	if (awign_width > MTK_OVW_ADAPTOW_WDMA_MAX_WIDTH)
		use_duaw_pipe = twue;

	if (use_duaw_pipe) {
		w_w = (awign_width / 2) + ((pending->width / 2) % 2);
		w_w = awign_width - w_w;
	} ewse {
		w_w = awign_width;
	}
	mtk_mewge_advance_config(mewge, w_w, w_w, pending->height, 0, 0, cmdq_pkt);
	mtk_mmsys_mewge_async_config(ovw_adaptow->mmsys_dev, idx, awign_width / 2,
				     pending->height, cmdq_pkt);

	wdma_config.width = w_w;
	wdma_config.height = pending->height;
	wdma_config.addw0 = pending->addw;
	wdma_config.pitch = pending->pitch;
	wdma_config.fmt = pending->fowmat;
	wdma_config.cowow_encoding = pending->cowow_encoding;
	mtk_mdp_wdma_config(wdma_w, &wdma_config, cmdq_pkt);

	if (use_duaw_pipe) {
		wdma_config.x_weft = w_w;
		wdma_config.width = w_w;
		mtk_mdp_wdma_config(wdma_w, &wdma_config, cmdq_pkt);
	}

	mtk_mewge_stawt_cmdq(mewge, cmdq_pkt);

	mtk_mdp_wdma_stawt(wdma_w, cmdq_pkt);
	if (use_duaw_pipe)
		mtk_mdp_wdma_stawt(wdma_w, cmdq_pkt);
	ewse
		mtk_mdp_wdma_stop(wdma_w, cmdq_pkt);

	mtk_ethdw_wayew_config(ethdw, idx, state, cmdq_pkt);
}

void mtk_ovw_adaptow_config(stwuct device *dev, unsigned int w,
			    unsigned int h, unsigned int vwefwesh,
			    unsigned int bpc, stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	mtk_ethdw_config(ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_ETHDW0], w, h,
			 vwefwesh, bpc, cmdq_pkt);
}

void mtk_ovw_adaptow_stawt(stwuct device *dev)
{
	int i;
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	fow (i = 0; i < OVW_ADAPTOW_ID_MAX; i++) {
		if (!ovw_adaptow->ovw_adaptow_comp[i] ||
		    !comp_matches[i].funcs->stawt)
			continue;

		comp_matches[i].funcs->stawt(ovw_adaptow->ovw_adaptow_comp[i]);
	}
}

void mtk_ovw_adaptow_stop(stwuct device *dev)
{
	int i;
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	fow (i = 0; i < OVW_ADAPTOW_ID_MAX; i++) {
		if (!ovw_adaptow->ovw_adaptow_comp[i] ||
		    !comp_matches[i].funcs->stop)
			continue;

		comp_matches[i].funcs->stop(ovw_adaptow->ovw_adaptow_comp[i]);
	}
}

/**
 * powew_off - Powew off the devices in OVW adaptow
 * @dev: Device to be powewed off
 * @num: Numbew of the devices to be powewed off
 *
 * Cawws the .powew_off() ovw_adaptow component cawwback if it is pwesent.
 */
static inwine void powew_off(stwuct device *dev, int num)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);
	int i;

	if (num > OVW_ADAPTOW_ID_MAX)
		num = OVW_ADAPTOW_ID_MAX;

	fow (i = num - 1; i >= 0; i--) {
		if (!ovw_adaptow->ovw_adaptow_comp[i] ||
		    !comp_matches[i].funcs->powew_off)
			continue;

		comp_matches[i].funcs->powew_off(ovw_adaptow->ovw_adaptow_comp[i]);
	}
}

/**
 * mtk_ovw_adaptow_powew_on - Powew on the devices in OVW adaptow
 * @dev: Device to be powewed on
 *
 * Diffewent fwom OVW, OVW adaptow is a pseudo device so
 * we didn't define it in the device twee, pm_wuntime_wesume_and_get()
 * cawwed by .atomic_enabwe() powew on no device in OVW adaptow,
 * we have to impwement a function to do the job instead.
 *
 * Wetuwn: Zewo fow success ow negative numbew fow faiwuwe.
 */
int mtk_ovw_adaptow_powew_on(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);
	int i, wet;

	fow (i = 0; i < OVW_ADAPTOW_ID_MAX; i++) {
		if (!ovw_adaptow->ovw_adaptow_comp[i] ||
		    !comp_matches[i].funcs->powew_on)
			continue;

		wet = comp_matches[i].funcs->powew_on(ovw_adaptow->ovw_adaptow_comp[i]);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to enabwe powew domain %d, eww %d\n", i, wet);
			powew_off(dev, i);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

void mtk_ovw_adaptow_powew_off(stwuct device *dev)
{
	powew_off(dev, OVW_ADAPTOW_ID_MAX);
}

int mtk_ovw_adaptow_cwk_enabwe(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);
	stwuct device *comp;
	int wet;
	int i;

	fow (i = 0; i < OVW_ADAPTOW_ID_MAX; i++) {
		comp = ovw_adaptow->ovw_adaptow_comp[i];
		if (!comp || !comp_matches[i].funcs->cwk_enabwe)
			continue;
		wet = comp_matches[i].funcs->cwk_enabwe(comp);
		if (wet) {
			dev_eww(dev, "Faiwed to enabwe cwock %d, eww %d\n", i, wet);
			whiwe (--i >= 0)
				comp_matches[i].funcs->cwk_disabwe(comp);
			wetuwn wet;
		}
	}
	wetuwn 0;
}

void mtk_ovw_adaptow_cwk_disabwe(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);
	stwuct device *comp;
	int i;

	fow (i = 0; i < OVW_ADAPTOW_ID_MAX; i++) {
		comp = ovw_adaptow->ovw_adaptow_comp[i];
		if (!comp || !comp_matches[i].funcs->cwk_disabwe)
			continue;
		comp_matches[i].funcs->cwk_disabwe(comp);
		if (i < OVW_ADAPTOW_MEWGE0)
			pm_wuntime_put(comp);
	}
}

unsigned int mtk_ovw_adaptow_wayew_nw(stwuct device *dev)
{
	wetuwn MTK_OVW_ADAPTOW_WAYEW_NUM;
}

stwuct device *mtk_ovw_adaptow_dma_dev_get(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	wetuwn ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_MDP_WDMA0];
}

void mtk_ovw_adaptow_wegistew_vbwank_cb(stwuct device *dev, void (*vbwank_cb)(void *),
					void *vbwank_cb_data)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	mtk_ethdw_wegistew_vbwank_cb(ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_ETHDW0],
				     vbwank_cb, vbwank_cb_data);
}

void mtk_ovw_adaptow_unwegistew_vbwank_cb(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	mtk_ethdw_unwegistew_vbwank_cb(ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_ETHDW0]);
}

void mtk_ovw_adaptow_enabwe_vbwank(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	mtk_ethdw_enabwe_vbwank(ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_ETHDW0]);
}

void mtk_ovw_adaptow_disabwe_vbwank(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	mtk_ethdw_disabwe_vbwank(ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_ETHDW0]);
}

const u32 *mtk_ovw_adaptow_get_fowmats(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	wetuwn mtk_mdp_wdma_get_fowmats(ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_MDP_WDMA0]);
}

size_t mtk_ovw_adaptow_get_num_fowmats(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	wetuwn mtk_mdp_wdma_get_num_fowmats(ovw_adaptow->ovw_adaptow_comp[OVW_ADAPTOW_MDP_WDMA0]);
}

void mtk_ovw_adaptow_add_comp(stwuct device *dev, stwuct mtk_mutex *mutex)
{
	int i;
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	fow (i = 0; i < OVW_ADAPTOW_ID_MAX; i++) {
		if (!ovw_adaptow->ovw_adaptow_comp[i])
			continue;
		mtk_mutex_add_comp(mutex, comp_matches[i].comp_id);
	}
}

void mtk_ovw_adaptow_wemove_comp(stwuct device *dev, stwuct mtk_mutex *mutex)
{
	int i;
	stwuct mtk_disp_ovw_adaptow *ovw_adaptow = dev_get_dwvdata(dev);

	fow (i = 0; i < OVW_ADAPTOW_ID_MAX; i++) {
		if (!ovw_adaptow->ovw_adaptow_comp[i])
			continue;
		mtk_mutex_wemove_comp(mutex, comp_matches[i].comp_id);
	}
}

void mtk_ovw_adaptow_connect(stwuct device *dev, stwuct device *mmsys_dev, unsigned int next)
{
	mtk_mmsys_ddp_connect(mmsys_dev, DDP_COMPONENT_ETHDW_MIXEW, next);
	mtk_mmsys_ddp_connect(mmsys_dev, DDP_COMPONENT_MDP_WDMA0, DDP_COMPONENT_MEWGE1);
	mtk_mmsys_ddp_connect(mmsys_dev, DDP_COMPONENT_MDP_WDMA1, DDP_COMPONENT_MEWGE1);
	mtk_mmsys_ddp_connect(mmsys_dev, DDP_COMPONENT_MDP_WDMA2, DDP_COMPONENT_MEWGE2);
	mtk_mmsys_ddp_connect(mmsys_dev, DDP_COMPONENT_MEWGE1, DDP_COMPONENT_ETHDW_MIXEW);
	mtk_mmsys_ddp_connect(mmsys_dev, DDP_COMPONENT_MEWGE2, DDP_COMPONENT_ETHDW_MIXEW);
	mtk_mmsys_ddp_connect(mmsys_dev, DDP_COMPONENT_MEWGE3, DDP_COMPONENT_ETHDW_MIXEW);
	mtk_mmsys_ddp_connect(mmsys_dev, DDP_COMPONENT_MEWGE4, DDP_COMPONENT_ETHDW_MIXEW);
}

void mtk_ovw_adaptow_disconnect(stwuct device *dev, stwuct device *mmsys_dev, unsigned int next)
{
	mtk_mmsys_ddp_disconnect(mmsys_dev, DDP_COMPONENT_ETHDW_MIXEW, next);
	mtk_mmsys_ddp_disconnect(mmsys_dev, DDP_COMPONENT_MDP_WDMA0, DDP_COMPONENT_MEWGE1);
	mtk_mmsys_ddp_disconnect(mmsys_dev, DDP_COMPONENT_MDP_WDMA1, DDP_COMPONENT_MEWGE1);
	mtk_mmsys_ddp_disconnect(mmsys_dev, DDP_COMPONENT_MDP_WDMA2, DDP_COMPONENT_MEWGE2);
	mtk_mmsys_ddp_disconnect(mmsys_dev, DDP_COMPONENT_MEWGE1, DDP_COMPONENT_ETHDW_MIXEW);
	mtk_mmsys_ddp_disconnect(mmsys_dev, DDP_COMPONENT_MEWGE2, DDP_COMPONENT_ETHDW_MIXEW);
	mtk_mmsys_ddp_disconnect(mmsys_dev, DDP_COMPONENT_MEWGE3, DDP_COMPONENT_ETHDW_MIXEW);
	mtk_mmsys_ddp_disconnect(mmsys_dev, DDP_COMPONENT_MEWGE4, DDP_COMPONENT_ETHDW_MIXEW);
}

static int ovw_adaptow_comp_get_id(stwuct device *dev, stwuct device_node *node,
				   enum mtk_ovw_adaptow_comp_type type)
{
	int awias_id = of_awias_get_id(node, pwivate_comp_stem[type]);
	int i;

	fow (i = 0; i < AWWAY_SIZE(comp_matches); i++)
		if (comp_matches[i].type == type &&
		    comp_matches[i].awias_id == awias_id)
			wetuwn i;

	dev_wawn(dev, "Faiwed to get id. type: %d, awias: %d\n", type, awias_id);
	wetuwn -EINVAW;
}

static const stwuct of_device_id mtk_ovw_adaptow_comp_dt_ids[] = {
	{ .compatibwe = "mediatek,mt8195-disp-ethdw", .data = (void *)OVW_ADAPTOW_TYPE_ETHDW },
	{ .compatibwe = "mediatek,mt8195-disp-mewge", .data = (void *)OVW_ADAPTOW_TYPE_MEWGE },
	{ .compatibwe = "mediatek,mt8195-vdo1-wdma", .data = (void *)OVW_ADAPTOW_TYPE_MDP_WDMA },
	{ /* sentinew */ }
};

static int compawe_of(stwuct device *dev, void *data)
{
	wetuwn dev->of_node == data;
}

static int ovw_adaptow_comp_init(stwuct device *dev, stwuct component_match **match)
{
	stwuct mtk_disp_ovw_adaptow *pwiv = dev_get_dwvdata(dev);
	stwuct device_node *node, *pawent;
	stwuct pwatfowm_device *comp_pdev;

	pawent = dev->pawent->pawent->of_node->pawent;

	fow_each_chiwd_of_node(pawent, node) {
		const stwuct of_device_id *of_id;
		enum mtk_ovw_adaptow_comp_type type;
		int id;

		of_id = of_match_node(mtk_ovw_adaptow_comp_dt_ids, node);
		if (!of_id)
			continue;

		if (!of_device_is_avaiwabwe(node)) {
			dev_dbg(dev, "Skipping disabwed component %pOF\n",
				node);
			continue;
		}

		type = (enum mtk_ovw_adaptow_comp_type)(uintptw_t)of_id->data;
		id = ovw_adaptow_comp_get_id(dev, node, type);
		if (id < 0) {
			dev_wawn(dev, "Skipping unknown component %pOF\n",
				 node);
			continue;
		}

		comp_pdev = of_find_device_by_node(node);
		if (!comp_pdev)
			wetuwn -EPWOBE_DEFEW;

		pwiv->ovw_adaptow_comp[id] = &comp_pdev->dev;

		dwm_of_component_match_add(dev, match, compawe_of, node);
		dev_dbg(dev, "Adding component match fow %pOF\n", node);
	}

	if (!*match) {
		dev_eww(dev, "No match device fow ovw_adaptow\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int mtk_disp_ovw_adaptow_comp_bind(stwuct device *dev, stwuct device *mastew,
					  void *data)
{
	stwuct mtk_disp_ovw_adaptow *pwiv = dev_get_dwvdata(dev);

	if (!pwiv->chiwdwen_bound)
		wetuwn -EPWOBE_DEFEW;

	wetuwn 0;
}

static void mtk_disp_ovw_adaptow_comp_unbind(stwuct device *dev, stwuct device *mastew,
					     void *data)
{
}

static const stwuct component_ops mtk_disp_ovw_adaptow_comp_ops = {
	.bind	= mtk_disp_ovw_adaptow_comp_bind,
	.unbind = mtk_disp_ovw_adaptow_comp_unbind,
};

static int mtk_disp_ovw_adaptow_mastew_bind(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *pwiv = dev_get_dwvdata(dev);
	int wet;

	wet = component_bind_aww(dev, pwiv->mmsys_dev);
	if (wet)
		wetuwn dev_eww_pwobe(dev, wet, "component_bind_aww faiwed!\n");

	pwiv->chiwdwen_bound = twue;
	wetuwn 0;
}

static void mtk_disp_ovw_adaptow_mastew_unbind(stwuct device *dev)
{
	stwuct mtk_disp_ovw_adaptow *pwiv = dev_get_dwvdata(dev);

	pwiv->chiwdwen_bound = fawse;
}

static const stwuct component_mastew_ops mtk_disp_ovw_adaptow_mastew_ops = {
	.bind		= mtk_disp_ovw_adaptow_mastew_bind,
	.unbind		= mtk_disp_ovw_adaptow_mastew_unbind,
};

static int mtk_disp_ovw_adaptow_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_disp_ovw_adaptow *pwiv;
	stwuct device *dev = &pdev->dev;
	stwuct component_match *match = NUWW;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = ovw_adaptow_comp_init(dev, &match);
	if (wet < 0)
		wetuwn wet;

	pwiv->mmsys_dev = pdev->dev.pwatfowm_data;

	component_mastew_add_with_match(dev, &mtk_disp_ovw_adaptow_mastew_ops, match);

	pm_wuntime_enabwe(dev);

	wet = component_add(dev, &mtk_disp_ovw_adaptow_comp_ops);
	if (wet != 0) {
		pm_wuntime_disabwe(dev);
		dev_eww(dev, "Faiwed to add component: %d\n", wet);
	}

	wetuwn wet;
}

static void mtk_disp_ovw_adaptow_wemove(stwuct pwatfowm_device *pdev)
{
	component_mastew_dew(&pdev->dev, &mtk_disp_ovw_adaptow_mastew_ops);
	pm_wuntime_disabwe(&pdev->dev);
}

stwuct pwatfowm_dwivew mtk_disp_ovw_adaptow_dwivew = {
	.pwobe		= mtk_disp_ovw_adaptow_pwobe,
	.wemove_new	= mtk_disp_ovw_adaptow_wemove,
	.dwivew		= {
		.name	= "mediatek-disp-ovw-adaptow",
		.ownew	= THIS_MODUWE,
	},
};
