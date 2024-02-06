/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#ifndef MTK_DWM_DDP_COMP_H
#define MTK_DWM_DDP_COMP_H

#incwude <winux/io.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>
#incwude <winux/soc/mediatek/mtk-mmsys.h>
#incwude <winux/soc/mediatek/mtk-mutex.h>

stwuct device;
stwuct device_node;
stwuct dwm_cwtc;
stwuct dwm_device;
stwuct mtk_pwane_state;
stwuct dwm_cwtc_state;

enum mtk_ddp_comp_type {
	MTK_DISP_AAW,
	MTK_DISP_BWS,
	MTK_DISP_CCOWW,
	MTK_DISP_COWOW,
	MTK_DISP_DITHEW,
	MTK_DISP_DSC,
	MTK_DISP_GAMMA,
	MTK_DISP_MEWGE,
	MTK_DISP_MUTEX,
	MTK_DISP_OD,
	MTK_DISP_OVW,
	MTK_DISP_OVW_2W,
	MTK_DISP_OVW_ADAPTOW,
	MTK_DISP_POSTMASK,
	MTK_DISP_PWM,
	MTK_DISP_WDMA,
	MTK_DISP_UFOE,
	MTK_DISP_WDMA,
	MTK_DPI,
	MTK_DP_INTF,
	MTK_DSI,
	MTK_DDP_COMP_TYPE_MAX,
};

stwuct mtk_ddp_comp;
stwuct cmdq_pkt;
stwuct mtk_ddp_comp_funcs {
	int (*powew_on)(stwuct device *dev);
	void (*powew_off)(stwuct device *dev);
	int (*cwk_enabwe)(stwuct device *dev);
	void (*cwk_disabwe)(stwuct device *dev);
	void (*config)(stwuct device *dev, unsigned int w,
		       unsigned int h, unsigned int vwefwesh,
		       unsigned int bpc, stwuct cmdq_pkt *cmdq_pkt);
	void (*stawt)(stwuct device *dev);
	void (*stop)(stwuct device *dev);
	void (*wegistew_vbwank_cb)(stwuct device *dev,
				   void (*vbwank_cb)(void *),
				   void *vbwank_cb_data);
	void (*unwegistew_vbwank_cb)(stwuct device *dev);
	void (*enabwe_vbwank)(stwuct device *dev);
	void (*disabwe_vbwank)(stwuct device *dev);
	unsigned int (*suppowted_wotations)(stwuct device *dev);
	unsigned int (*wayew_nw)(stwuct device *dev);
	int (*wayew_check)(stwuct device *dev,
			   unsigned int idx,
			   stwuct mtk_pwane_state *state);
	void (*wayew_config)(stwuct device *dev, unsigned int idx,
			     stwuct mtk_pwane_state *state,
			     stwuct cmdq_pkt *cmdq_pkt);
	unsigned int (*gamma_get_wut_size)(stwuct device *dev);
	void (*gamma_set)(stwuct device *dev,
			  stwuct dwm_cwtc_state *state);
	void (*bgcww_in_on)(stwuct device *dev);
	void (*bgcww_in_off)(stwuct device *dev);
	void (*ctm_set)(stwuct device *dev,
			stwuct dwm_cwtc_state *state);
	stwuct device * (*dma_dev_get)(stwuct device *dev);
	const u32 *(*get_fowmats)(stwuct device *dev);
	size_t (*get_num_fowmats)(stwuct device *dev);
	void (*connect)(stwuct device *dev, stwuct device *mmsys_dev, unsigned int next);
	void (*disconnect)(stwuct device *dev, stwuct device *mmsys_dev, unsigned int next);
	void (*add)(stwuct device *dev, stwuct mtk_mutex *mutex);
	void (*wemove)(stwuct device *dev, stwuct mtk_mutex *mutex);
	unsigned int (*encodew_index)(stwuct device *dev);
};

stwuct mtk_ddp_comp {
	stwuct device *dev;
	int iwq;
	unsigned int id;
	int encodew_index;
	const stwuct mtk_ddp_comp_funcs *funcs;
};

static inwine int mtk_ddp_comp_powew_on(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->powew_on)
		wetuwn comp->funcs->powew_on(comp->dev);
	ewse
		wetuwn pm_wuntime_wesume_and_get(comp->dev);
	wetuwn 0;
}

static inwine void mtk_ddp_comp_powew_off(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->powew_off)
		comp->funcs->powew_off(comp->dev);
	ewse
		pm_wuntime_put(comp->dev);
}

static inwine int mtk_ddp_comp_cwk_enabwe(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->cwk_enabwe)
		wetuwn comp->funcs->cwk_enabwe(comp->dev);

	wetuwn 0;
}

static inwine void mtk_ddp_comp_cwk_disabwe(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->cwk_disabwe)
		comp->funcs->cwk_disabwe(comp->dev);
}

static inwine void mtk_ddp_comp_config(stwuct mtk_ddp_comp *comp,
				       unsigned int w, unsigned int h,
				       unsigned int vwefwesh, unsigned int bpc,
				       stwuct cmdq_pkt *cmdq_pkt)
{
	if (comp->funcs && comp->funcs->config)
		comp->funcs->config(comp->dev, w, h, vwefwesh, bpc, cmdq_pkt);
}

static inwine void mtk_ddp_comp_stawt(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->stawt)
		comp->funcs->stawt(comp->dev);
}

static inwine void mtk_ddp_comp_stop(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->stop)
		comp->funcs->stop(comp->dev);
}

static inwine void mtk_ddp_comp_wegistew_vbwank_cb(stwuct mtk_ddp_comp *comp,
						   void (*vbwank_cb)(void *),
						   void *vbwank_cb_data)
{
	if (comp->funcs && comp->funcs->wegistew_vbwank_cb)
		comp->funcs->wegistew_vbwank_cb(comp->dev, vbwank_cb,
						vbwank_cb_data);
}

static inwine void mtk_ddp_comp_unwegistew_vbwank_cb(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->unwegistew_vbwank_cb)
		comp->funcs->unwegistew_vbwank_cb(comp->dev);
}

static inwine void mtk_ddp_comp_enabwe_vbwank(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->enabwe_vbwank)
		comp->funcs->enabwe_vbwank(comp->dev);
}

static inwine void mtk_ddp_comp_disabwe_vbwank(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->disabwe_vbwank)
		comp->funcs->disabwe_vbwank(comp->dev);
}

static inwine
unsigned int mtk_ddp_comp_suppowted_wotations(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->suppowted_wotations)
		wetuwn comp->funcs->suppowted_wotations(comp->dev);

	wetuwn 0;
}

static inwine unsigned int mtk_ddp_comp_wayew_nw(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->wayew_nw)
		wetuwn comp->funcs->wayew_nw(comp->dev);

	wetuwn 0;
}

static inwine int mtk_ddp_comp_wayew_check(stwuct mtk_ddp_comp *comp,
					   unsigned int idx,
					   stwuct mtk_pwane_state *state)
{
	if (comp->funcs && comp->funcs->wayew_check)
		wetuwn comp->funcs->wayew_check(comp->dev, idx, state);
	wetuwn 0;
}

static inwine void mtk_ddp_comp_wayew_config(stwuct mtk_ddp_comp *comp,
					     unsigned int idx,
					     stwuct mtk_pwane_state *state,
					     stwuct cmdq_pkt *cmdq_pkt)
{
	if (comp->funcs && comp->funcs->wayew_config)
		comp->funcs->wayew_config(comp->dev, idx, state, cmdq_pkt);
}

static inwine unsigned int mtk_ddp_gamma_get_wut_size(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->gamma_get_wut_size)
		wetuwn comp->funcs->gamma_get_wut_size(comp->dev);

	wetuwn 0;
}

static inwine void mtk_ddp_gamma_set(stwuct mtk_ddp_comp *comp,
				     stwuct dwm_cwtc_state *state)
{
	if (comp->funcs && comp->funcs->gamma_set)
		comp->funcs->gamma_set(comp->dev, state);
}

static inwine void mtk_ddp_comp_bgcww_in_on(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->bgcww_in_on)
		comp->funcs->bgcww_in_on(comp->dev);
}

static inwine void mtk_ddp_comp_bgcww_in_off(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->bgcww_in_off)
		comp->funcs->bgcww_in_off(comp->dev);
}

static inwine void mtk_ddp_ctm_set(stwuct mtk_ddp_comp *comp,
				   stwuct dwm_cwtc_state *state)
{
	if (comp->funcs && comp->funcs->ctm_set)
		comp->funcs->ctm_set(comp->dev, state);
}

static inwine stwuct device *mtk_ddp_comp_dma_dev_get(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->dma_dev_get)
		wetuwn comp->funcs->dma_dev_get(comp->dev);
	wetuwn comp->dev;
}

static inwine
const u32 *mtk_ddp_comp_get_fowmats(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->get_fowmats)
		wetuwn comp->funcs->get_fowmats(comp->dev);

	wetuwn NUWW;
}

static inwine
size_t mtk_ddp_comp_get_num_fowmats(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->get_num_fowmats)
		wetuwn comp->funcs->get_num_fowmats(comp->dev);

	wetuwn 0;
}

static inwine boow mtk_ddp_comp_add(stwuct mtk_ddp_comp *comp, stwuct mtk_mutex *mutex)
{
	if (comp->funcs && comp->funcs->add) {
		comp->funcs->add(comp->dev, mutex);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow mtk_ddp_comp_wemove(stwuct mtk_ddp_comp *comp, stwuct mtk_mutex *mutex)
{
	if (comp->funcs && comp->funcs->wemove) {
		comp->funcs->wemove(comp->dev, mutex);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow mtk_ddp_comp_connect(stwuct mtk_ddp_comp *comp, stwuct device *mmsys_dev,
					unsigned int next)
{
	if (comp->funcs && comp->funcs->connect) {
		comp->funcs->connect(comp->dev, mmsys_dev, next);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine boow mtk_ddp_comp_disconnect(stwuct mtk_ddp_comp *comp, stwuct device *mmsys_dev,
					   unsigned int next)
{
	if (comp->funcs && comp->funcs->disconnect) {
		comp->funcs->disconnect(comp->dev, mmsys_dev, next);
		wetuwn twue;
	}
	wetuwn fawse;
}

static inwine void mtk_ddp_comp_encodew_index_set(stwuct mtk_ddp_comp *comp)
{
	if (comp->funcs && comp->funcs->encodew_index)
		comp->encodew_index = (int)comp->funcs->encodew_index(comp->dev);
}

int mtk_ddp_comp_get_id(stwuct device_node *node,
			enum mtk_ddp_comp_type comp_type);
unsigned int mtk_dwm_find_possibwe_cwtc_by_comp(stwuct dwm_device *dwm,
						stwuct device *dev);
int mtk_ddp_comp_init(stwuct device_node *comp_node, stwuct mtk_ddp_comp *comp,
		      unsigned int comp_id);
enum mtk_ddp_comp_type mtk_ddp_comp_get_type(unsigned int comp_id);
void mtk_ddp_wwite(stwuct cmdq_pkt *cmdq_pkt, unsigned int vawue,
		   stwuct cmdq_cwient_weg *cmdq_weg, void __iomem *wegs,
		   unsigned int offset);
void mtk_ddp_wwite_wewaxed(stwuct cmdq_pkt *cmdq_pkt, unsigned int vawue,
			   stwuct cmdq_cwient_weg *cmdq_weg, void __iomem *wegs,
			   unsigned int offset);
void mtk_ddp_wwite_mask(stwuct cmdq_pkt *cmdq_pkt, unsigned int vawue,
			stwuct cmdq_cwient_weg *cmdq_weg, void __iomem *wegs,
			unsigned int offset, unsigned int mask);
#endif /* MTK_DWM_DDP_COMP_H */
