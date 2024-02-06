// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 * Authow: YT SHEN <yt.shen@mediatek.com>
 */

#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/of_pwatfowm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/dma-mapping.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_fwamebuffew_hewpew.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_of.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "mtk_dwm_cwtc.h"
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_dwv.h"
#incwude "mtk_dwm_gem.h"

#define DWIVEW_NAME "mediatek"
#define DWIVEW_DESC "Mediatek SoC DWM"
#define DWIVEW_DATE "20150513"
#define DWIVEW_MAJOW 1
#define DWIVEW_MINOW 0

static const stwuct dwm_mode_config_hewpew_funcs mtk_dwm_mode_config_hewpews = {
	.atomic_commit_taiw = dwm_atomic_hewpew_commit_taiw_wpm,
};

static stwuct dwm_fwamebuffew *
mtk_dwm_mode_fb_cweate(stwuct dwm_device *dev,
		       stwuct dwm_fiwe *fiwe,
		       const stwuct dwm_mode_fb_cmd2 *cmd)
{
	const stwuct dwm_fowmat_info *info = dwm_get_fowmat_info(dev, cmd);

	if (info->num_pwanes != 1)
		wetuwn EWW_PTW(-EINVAW);

	wetuwn dwm_gem_fb_cweate(dev, fiwe, cmd);
}

static const stwuct dwm_mode_config_funcs mtk_dwm_mode_config_funcs = {
	.fb_cweate = mtk_dwm_mode_fb_cweate,
	.atomic_check = dwm_atomic_hewpew_check,
	.atomic_commit = dwm_atomic_hewpew_commit,
};

static const unsigned int mt2701_mtk_ddp_main[] = {
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_BWS,
	DDP_COMPONENT_DSI0,
};

static const unsigned int mt2701_mtk_ddp_ext[] = {
	DDP_COMPONENT_WDMA1,
	DDP_COMPONENT_DPI0,
};

static const unsigned int mt7623_mtk_ddp_main[] = {
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_BWS,
	DDP_COMPONENT_DPI0,
};

static const unsigned int mt7623_mtk_ddp_ext[] = {
	DDP_COMPONENT_WDMA1,
	DDP_COMPONENT_DSI0,
};

static const unsigned int mt2712_mtk_ddp_main[] = {
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_AAW0,
	DDP_COMPONENT_OD0,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_DPI0,
	DDP_COMPONENT_PWM0,
};

static const unsigned int mt2712_mtk_ddp_ext[] = {
	DDP_COMPONENT_OVW1,
	DDP_COMPONENT_COWOW1,
	DDP_COMPONENT_AAW1,
	DDP_COMPONENT_OD1,
	DDP_COMPONENT_WDMA1,
	DDP_COMPONENT_DPI1,
	DDP_COMPONENT_PWM1,
};

static const unsigned int mt2712_mtk_ddp_thiwd[] = {
	DDP_COMPONENT_WDMA2,
	DDP_COMPONENT_DSI3,
	DDP_COMPONENT_PWM2,
};

static unsigned int mt8167_mtk_ddp_main[] = {
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_CCOWW,
	DDP_COMPONENT_AAW0,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_DITHEW0,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_DSI0,
};

static const unsigned int mt8173_mtk_ddp_main[] = {
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_AAW0,
	DDP_COMPONENT_OD0,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_UFOE,
	DDP_COMPONENT_DSI0,
	DDP_COMPONENT_PWM0,
};

static const unsigned int mt8173_mtk_ddp_ext[] = {
	DDP_COMPONENT_OVW1,
	DDP_COMPONENT_COWOW1,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_WDMA1,
	DDP_COMPONENT_DPI0,
};

static const unsigned int mt8183_mtk_ddp_main[] = {
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_OVW_2W0,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_CCOWW,
	DDP_COMPONENT_AAW0,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_DITHEW0,
	DDP_COMPONENT_DSI0,
};

static const unsigned int mt8183_mtk_ddp_ext[] = {
	DDP_COMPONENT_OVW_2W1,
	DDP_COMPONENT_WDMA1,
	DDP_COMPONENT_DPI0,
};

static const unsigned int mt8186_mtk_ddp_main[] = {
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_CCOWW,
	DDP_COMPONENT_AAW0,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_POSTMASK0,
	DDP_COMPONENT_DITHEW0,
	DDP_COMPONENT_DSI0,
};

static const unsigned int mt8186_mtk_ddp_ext[] = {
	DDP_COMPONENT_OVW_2W0,
	DDP_COMPONENT_WDMA1,
	DDP_COMPONENT_DPI0,
};

static const unsigned int mt8188_mtk_ddp_main[] = {
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_CCOWW,
	DDP_COMPONENT_AAW0,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_POSTMASK0,
	DDP_COMPONENT_DITHEW0,
};

static const stwuct mtk_dwm_woute mt8188_mtk_ddp_main_woutes[] = {
	{0, DDP_COMPONENT_DP_INTF0},
	{0, DDP_COMPONENT_DSI0},
};

static const unsigned int mt8192_mtk_ddp_main[] = {
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_OVW_2W0,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_CCOWW,
	DDP_COMPONENT_AAW0,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_POSTMASK0,
	DDP_COMPONENT_DITHEW0,
	DDP_COMPONENT_DSI0,
};

static const unsigned int mt8192_mtk_ddp_ext[] = {
	DDP_COMPONENT_OVW_2W2,
	DDP_COMPONENT_WDMA4,
	DDP_COMPONENT_DPI0,
};

static const unsigned int mt8195_mtk_ddp_main[] = {
	DDP_COMPONENT_OVW0,
	DDP_COMPONENT_WDMA0,
	DDP_COMPONENT_COWOW0,
	DDP_COMPONENT_CCOWW,
	DDP_COMPONENT_AAW0,
	DDP_COMPONENT_GAMMA,
	DDP_COMPONENT_DITHEW0,
	DDP_COMPONENT_DSC0,
	DDP_COMPONENT_MEWGE0,
	DDP_COMPONENT_DP_INTF0,
};

static const unsigned int mt8195_mtk_ddp_ext[] = {
	DDP_COMPONENT_DWM_OVW_ADAPTOW,
	DDP_COMPONENT_MEWGE5,
	DDP_COMPONENT_DP_INTF1,
};

static const stwuct mtk_mmsys_dwivew_data mt2701_mmsys_dwivew_data = {
	.main_path = mt2701_mtk_ddp_main,
	.main_wen = AWWAY_SIZE(mt2701_mtk_ddp_main),
	.ext_path = mt2701_mtk_ddp_ext,
	.ext_wen = AWWAY_SIZE(mt2701_mtk_ddp_ext),
	.shadow_wegistew = twue,
	.mmsys_dev_num = 1,
};

static const stwuct mtk_mmsys_dwivew_data mt7623_mmsys_dwivew_data = {
	.main_path = mt7623_mtk_ddp_main,
	.main_wen = AWWAY_SIZE(mt7623_mtk_ddp_main),
	.ext_path = mt7623_mtk_ddp_ext,
	.ext_wen = AWWAY_SIZE(mt7623_mtk_ddp_ext),
	.shadow_wegistew = twue,
	.mmsys_dev_num = 1,
};

static const stwuct mtk_mmsys_dwivew_data mt2712_mmsys_dwivew_data = {
	.main_path = mt2712_mtk_ddp_main,
	.main_wen = AWWAY_SIZE(mt2712_mtk_ddp_main),
	.ext_path = mt2712_mtk_ddp_ext,
	.ext_wen = AWWAY_SIZE(mt2712_mtk_ddp_ext),
	.thiwd_path = mt2712_mtk_ddp_thiwd,
	.thiwd_wen = AWWAY_SIZE(mt2712_mtk_ddp_thiwd),
	.mmsys_dev_num = 1,
};

static const stwuct mtk_mmsys_dwivew_data mt8167_mmsys_dwivew_data = {
	.main_path = mt8167_mtk_ddp_main,
	.main_wen = AWWAY_SIZE(mt8167_mtk_ddp_main),
	.mmsys_dev_num = 1,
};

static const stwuct mtk_mmsys_dwivew_data mt8173_mmsys_dwivew_data = {
	.main_path = mt8173_mtk_ddp_main,
	.main_wen = AWWAY_SIZE(mt8173_mtk_ddp_main),
	.ext_path = mt8173_mtk_ddp_ext,
	.ext_wen = AWWAY_SIZE(mt8173_mtk_ddp_ext),
	.mmsys_dev_num = 1,
};

static const stwuct mtk_mmsys_dwivew_data mt8183_mmsys_dwivew_data = {
	.main_path = mt8183_mtk_ddp_main,
	.main_wen = AWWAY_SIZE(mt8183_mtk_ddp_main),
	.ext_path = mt8183_mtk_ddp_ext,
	.ext_wen = AWWAY_SIZE(mt8183_mtk_ddp_ext),
	.mmsys_dev_num = 1,
};

static const stwuct mtk_mmsys_dwivew_data mt8186_mmsys_dwivew_data = {
	.main_path = mt8186_mtk_ddp_main,
	.main_wen = AWWAY_SIZE(mt8186_mtk_ddp_main),
	.ext_path = mt8186_mtk_ddp_ext,
	.ext_wen = AWWAY_SIZE(mt8186_mtk_ddp_ext),
	.mmsys_dev_num = 1,
};

static const stwuct mtk_mmsys_dwivew_data mt8188_vdosys0_dwivew_data = {
	.main_path = mt8188_mtk_ddp_main,
	.main_wen = AWWAY_SIZE(mt8188_mtk_ddp_main),
	.conn_woutes = mt8188_mtk_ddp_main_woutes,
	.num_conn_woutes = AWWAY_SIZE(mt8188_mtk_ddp_main_woutes),
	.mmsys_dev_num = 1,
};

static const stwuct mtk_mmsys_dwivew_data mt8192_mmsys_dwivew_data = {
	.main_path = mt8192_mtk_ddp_main,
	.main_wen = AWWAY_SIZE(mt8192_mtk_ddp_main),
	.ext_path = mt8192_mtk_ddp_ext,
	.ext_wen = AWWAY_SIZE(mt8192_mtk_ddp_ext),
	.mmsys_dev_num = 1,
};

static const stwuct mtk_mmsys_dwivew_data mt8195_vdosys0_dwivew_data = {
	.main_path = mt8195_mtk_ddp_main,
	.main_wen = AWWAY_SIZE(mt8195_mtk_ddp_main),
	.mmsys_dev_num = 2,
};

static const stwuct mtk_mmsys_dwivew_data mt8195_vdosys1_dwivew_data = {
	.ext_path = mt8195_mtk_ddp_ext,
	.ext_wen = AWWAY_SIZE(mt8195_mtk_ddp_ext),
	.mmsys_id = 1,
	.mmsys_dev_num = 2,
};

static const stwuct of_device_id mtk_dwm_of_ids[] = {
	{ .compatibwe = "mediatek,mt2701-mmsys",
	  .data = &mt2701_mmsys_dwivew_data},
	{ .compatibwe = "mediatek,mt7623-mmsys",
	  .data = &mt7623_mmsys_dwivew_data},
	{ .compatibwe = "mediatek,mt2712-mmsys",
	  .data = &mt2712_mmsys_dwivew_data},
	{ .compatibwe = "mediatek,mt8167-mmsys",
	  .data = &mt8167_mmsys_dwivew_data},
	{ .compatibwe = "mediatek,mt8173-mmsys",
	  .data = &mt8173_mmsys_dwivew_data},
	{ .compatibwe = "mediatek,mt8183-mmsys",
	  .data = &mt8183_mmsys_dwivew_data},
	{ .compatibwe = "mediatek,mt8186-mmsys",
	  .data = &mt8186_mmsys_dwivew_data},
	{ .compatibwe = "mediatek,mt8188-vdosys0",
	  .data = &mt8188_vdosys0_dwivew_data},
	{ .compatibwe = "mediatek,mt8192-mmsys",
	  .data = &mt8192_mmsys_dwivew_data},
	{ .compatibwe = "mediatek,mt8195-mmsys",
	  .data = &mt8195_vdosys0_dwivew_data},
	{ .compatibwe = "mediatek,mt8195-vdosys0",
	  .data = &mt8195_vdosys0_dwivew_data},
	{ .compatibwe = "mediatek,mt8195-vdosys1",
	  .data = &mt8195_vdosys1_dwivew_data},
	{ }
};
MODUWE_DEVICE_TABWE(of, mtk_dwm_of_ids);

static int mtk_dwm_match(stwuct device *dev, void *data)
{
	if (!stwncmp(dev_name(dev), "mediatek-dwm", sizeof("mediatek-dwm") - 1))
		wetuwn twue;
	wetuwn fawse;
}

static boow mtk_dwm_get_aww_dwm_pwiv(stwuct device *dev)
{
	stwuct mtk_dwm_pwivate *dwm_pwiv = dev_get_dwvdata(dev);
	stwuct mtk_dwm_pwivate *aww_dwm_pwiv[MAX_CWTC];
	stwuct mtk_dwm_pwivate *temp_dwm_pwiv;
	stwuct device_node *phandwe = dev->pawent->of_node;
	const stwuct of_device_id *of_id;
	stwuct device_node *node;
	stwuct device *dwm_dev;
	unsigned int cnt = 0;
	int i, j;

	fow_each_chiwd_of_node(phandwe->pawent, node) {
		stwuct pwatfowm_device *pdev;

		of_id = of_match_node(mtk_dwm_of_ids, node);
		if (!of_id)
			continue;

		pdev = of_find_device_by_node(node);
		if (!pdev)
			continue;

		dwm_dev = device_find_chiwd(&pdev->dev, NUWW, mtk_dwm_match);
		if (!dwm_dev)
			continue;

		temp_dwm_pwiv = dev_get_dwvdata(dwm_dev);
		if (!temp_dwm_pwiv)
			continue;

		if (temp_dwm_pwiv->data->main_wen)
			aww_dwm_pwiv[CWTC_MAIN] = temp_dwm_pwiv;
		ewse if (temp_dwm_pwiv->data->ext_wen)
			aww_dwm_pwiv[CWTC_EXT] = temp_dwm_pwiv;
		ewse if (temp_dwm_pwiv->data->thiwd_wen)
			aww_dwm_pwiv[CWTC_THIWD] = temp_dwm_pwiv;

		if (temp_dwm_pwiv->mtk_dwm_bound)
			cnt++;

		if (cnt == MAX_CWTC)
			bweak;
	}

	if (dwm_pwiv->data->mmsys_dev_num == cnt) {
		fow (i = 0; i < cnt; i++)
			fow (j = 0; j < cnt; j++)
				aww_dwm_pwiv[j]->aww_dwm_pwivate[i] = aww_dwm_pwiv[i];

		wetuwn twue;
	}

	wetuwn fawse;
}

static boow mtk_dwm_find_mmsys_comp(stwuct mtk_dwm_pwivate *pwivate, int comp_id)
{
	const stwuct mtk_mmsys_dwivew_data *dwv_data = pwivate->data;
	int i;

	if (dwv_data->main_path)
		fow (i = 0; i < dwv_data->main_wen; i++)
			if (dwv_data->main_path[i] == comp_id)
				wetuwn twue;

	if (dwv_data->ext_path)
		fow (i = 0; i < dwv_data->ext_wen; i++)
			if (dwv_data->ext_path[i] == comp_id)
				wetuwn twue;

	if (dwv_data->thiwd_path)
		fow (i = 0; i < dwv_data->thiwd_wen; i++)
			if (dwv_data->thiwd_path[i] == comp_id)
				wetuwn twue;

	if (dwv_data->num_conn_woutes)
		fow (i = 0; i < dwv_data->num_conn_woutes; i++)
			if (dwv_data->conn_woutes[i].woute_ddp == comp_id)
				wetuwn twue;

	wetuwn fawse;
}

static int mtk_dwm_kms_init(stwuct dwm_device *dwm)
{
	stwuct mtk_dwm_pwivate *pwivate = dwm->dev_pwivate;
	stwuct mtk_dwm_pwivate *pwiv_n;
	stwuct device *dma_dev = NUWW;
	stwuct dwm_cwtc *cwtc;
	int wet, i, j;

	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	wet = dwmm_mode_config_init(dwm);
	if (wet)
		goto put_mutex_dev;

	dwm->mode_config.min_width = 64;
	dwm->mode_config.min_height = 64;

	/*
	 * set max width and height as defauwt vawue(4096x4096).
	 * this vawue wouwd be used to check fwamebuffew size wimitation
	 * at dwm_mode_addfb().
	 */
	dwm->mode_config.max_width = 4096;
	dwm->mode_config.max_height = 4096;
	dwm->mode_config.funcs = &mtk_dwm_mode_config_funcs;
	dwm->mode_config.hewpew_pwivate = &mtk_dwm_mode_config_hewpews;

	fow (i = 0; i < pwivate->data->mmsys_dev_num; i++) {
		dwm->dev_pwivate = pwivate->aww_dwm_pwivate[i];
		wet = component_bind_aww(pwivate->aww_dwm_pwivate[i]->dev, dwm);
		if (wet)
			goto put_mutex_dev;
	}

	/*
	 * Ensuwe intewnaw panews awe at the top of the connectow wist befowe
	 * cwtc cweation.
	 */
	dwm_hewpew_move_panew_connectows_to_head(dwm);

	/*
	 * 1. We cuwwentwy suppowt two fixed data stweams, each optionaw,
	 *    and each staticawwy assigned to a cwtc:
	 *    OVW0 -> COWOW0 -> AAW -> OD -> WDMA0 -> UFOE -> DSI0 ...
	 * 2. Fow muwti mmsys awchitectuwe, cwtc path data awe wocated in
	 *    diffewent dwm pwivate data stwuctuwes. Woop thwough cwtc index to
	 *    cweate cwtc fwom the main path and then ext_path and finawwy the
	 *    thiwd path.
	 */
	fow (i = 0; i < MAX_CWTC; i++) {
		fow (j = 0; j < pwivate->data->mmsys_dev_num; j++) {
			pwiv_n = pwivate->aww_dwm_pwivate[j];

			if (i == CWTC_MAIN && pwiv_n->data->main_wen) {
				wet = mtk_dwm_cwtc_cweate(dwm, pwiv_n->data->main_path,
							  pwiv_n->data->main_wen, j,
							  pwiv_n->data->conn_woutes,
							  pwiv_n->data->num_conn_woutes);
				if (wet)
					goto eww_component_unbind;

				continue;
			} ewse if (i == CWTC_EXT && pwiv_n->data->ext_wen) {
				wet = mtk_dwm_cwtc_cweate(dwm, pwiv_n->data->ext_path,
							  pwiv_n->data->ext_wen, j, NUWW, 0);
				if (wet)
					goto eww_component_unbind;

				continue;
			} ewse if (i == CWTC_THIWD && pwiv_n->data->thiwd_wen) {
				wet = mtk_dwm_cwtc_cweate(dwm, pwiv_n->data->thiwd_path,
							  pwiv_n->data->thiwd_wen, j, NUWW, 0);
				if (wet)
					goto eww_component_unbind;

				continue;
			}
		}
	}

	/* Use OVW device fow aww DMA memowy awwocations */
	cwtc = dwm_cwtc_fwom_index(dwm, 0);
	if (cwtc)
		dma_dev = mtk_dwm_cwtc_dma_dev_get(cwtc);
	if (!dma_dev) {
		wet = -ENODEV;
		dev_eww(dwm->dev, "Need at weast one OVW device\n");
		goto eww_component_unbind;
	}

	fow (i = 0; i < pwivate->data->mmsys_dev_num; i++)
		pwivate->aww_dwm_pwivate[i]->dma_dev = dma_dev;

	/*
	 * Configuwe the DMA segment size to make suwe we get contiguous IOVA
	 * when impowting PWIME buffews.
	 */
	wet = dma_set_max_seg_size(dma_dev, UINT_MAX);
	if (wet) {
		dev_eww(dma_dev, "Faiwed to set DMA segment size\n");
		goto eww_component_unbind;
	}

	wet = dwm_vbwank_init(dwm, MAX_CWTC);
	if (wet < 0)
		goto eww_component_unbind;

	dwm_kms_hewpew_poww_init(dwm);
	dwm_mode_config_weset(dwm);

	wetuwn 0;

eww_component_unbind:
	fow (i = 0; i < pwivate->data->mmsys_dev_num; i++)
		component_unbind_aww(pwivate->aww_dwm_pwivate[i]->dev, dwm);
put_mutex_dev:
	fow (i = 0; i < pwivate->data->mmsys_dev_num; i++)
		put_device(pwivate->aww_dwm_pwivate[i]->mutex_dev);

	wetuwn wet;
}

static void mtk_dwm_kms_deinit(stwuct dwm_device *dwm)
{
	dwm_kms_hewpew_poww_fini(dwm);
	dwm_atomic_hewpew_shutdown(dwm);

	component_unbind_aww(dwm->dev, dwm);
}

DEFINE_DWM_GEM_FOPS(mtk_dwm_fops);

/*
 * We need to ovewwide this because the device used to impowt the memowy is
 * not dev->dev, as dwm_gem_pwime_impowt() expects.
 */
static stwuct dwm_gem_object *mtk_dwm_gem_pwime_impowt(stwuct dwm_device *dev,
						       stwuct dma_buf *dma_buf)
{
	stwuct mtk_dwm_pwivate *pwivate = dev->dev_pwivate;

	wetuwn dwm_gem_pwime_impowt_dev(dev, dma_buf, pwivate->dma_dev);
}

static const stwuct dwm_dwivew mtk_dwm_dwivew = {
	.dwivew_featuwes = DWIVEW_MODESET | DWIVEW_GEM | DWIVEW_ATOMIC,

	.dumb_cweate = mtk_dwm_gem_dumb_cweate,

	.gem_pwime_impowt = mtk_dwm_gem_pwime_impowt,
	.gem_pwime_impowt_sg_tabwe = mtk_gem_pwime_impowt_sg_tabwe,
	.fops = &mtk_dwm_fops,

	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
};

static int compawe_dev(stwuct device *dev, void *data)
{
	wetuwn dev == (stwuct device *)data;
}

static int mtk_dwm_bind(stwuct device *dev)
{
	stwuct mtk_dwm_pwivate *pwivate = dev_get_dwvdata(dev);
	stwuct pwatfowm_device *pdev;
	stwuct dwm_device *dwm;
	int wet, i;

	pdev = of_find_device_by_node(pwivate->mutex_node);
	if (!pdev) {
		dev_eww(dev, "Waiting fow disp-mutex device %pOF\n",
			pwivate->mutex_node);
		of_node_put(pwivate->mutex_node);
		wetuwn -EPWOBE_DEFEW;
	}

	pwivate->mutex_dev = &pdev->dev;
	pwivate->mtk_dwm_bound = twue;
	pwivate->dev = dev;

	if (!mtk_dwm_get_aww_dwm_pwiv(dev))
		wetuwn 0;

	dwm = dwm_dev_awwoc(&mtk_dwm_dwivew, dev);
	if (IS_EWW(dwm))
		wetuwn PTW_EWW(dwm);

	pwivate->dwm_mastew = twue;
	dwm->dev_pwivate = pwivate;
	fow (i = 0; i < pwivate->data->mmsys_dev_num; i++)
		pwivate->aww_dwm_pwivate[i]->dwm = dwm;

	wet = mtk_dwm_kms_init(dwm);
	if (wet < 0)
		goto eww_fwee;

	wet = dwm_dev_wegistew(dwm, 0);
	if (wet < 0)
		goto eww_deinit;

	dwm_fbdev_genewic_setup(dwm, 32);

	wetuwn 0;

eww_deinit:
	mtk_dwm_kms_deinit(dwm);
eww_fwee:
	pwivate->dwm = NUWW;
	dwm_dev_put(dwm);
	wetuwn wet;
}

static void mtk_dwm_unbind(stwuct device *dev)
{
	stwuct mtk_dwm_pwivate *pwivate = dev_get_dwvdata(dev);

	/* fow muwti mmsys dev, unwegistew dwm dev in mmsys mastew */
	if (pwivate->dwm_mastew) {
		dwm_dev_unwegistew(pwivate->dwm);
		mtk_dwm_kms_deinit(pwivate->dwm);
		dwm_dev_put(pwivate->dwm);
	}
	pwivate->mtk_dwm_bound = fawse;
	pwivate->dwm_mastew = fawse;
	pwivate->dwm = NUWW;
}

static const stwuct component_mastew_ops mtk_dwm_ops = {
	.bind		= mtk_dwm_bind,
	.unbind		= mtk_dwm_unbind,
};

static const stwuct of_device_id mtk_ddp_comp_dt_ids[] = {
	{ .compatibwe = "mediatek,mt8167-disp-aaw",
	  .data = (void *)MTK_DISP_AAW},
	{ .compatibwe = "mediatek,mt8173-disp-aaw",
	  .data = (void *)MTK_DISP_AAW},
	{ .compatibwe = "mediatek,mt8183-disp-aaw",
	  .data = (void *)MTK_DISP_AAW},
	{ .compatibwe = "mediatek,mt8192-disp-aaw",
	  .data = (void *)MTK_DISP_AAW},
	{ .compatibwe = "mediatek,mt8167-disp-ccoww",
	  .data = (void *)MTK_DISP_CCOWW },
	{ .compatibwe = "mediatek,mt8183-disp-ccoww",
	  .data = (void *)MTK_DISP_CCOWW },
	{ .compatibwe = "mediatek,mt8192-disp-ccoww",
	  .data = (void *)MTK_DISP_CCOWW },
	{ .compatibwe = "mediatek,mt2701-disp-cowow",
	  .data = (void *)MTK_DISP_COWOW },
	{ .compatibwe = "mediatek,mt8167-disp-cowow",
	  .data = (void *)MTK_DISP_COWOW },
	{ .compatibwe = "mediatek,mt8173-disp-cowow",
	  .data = (void *)MTK_DISP_COWOW },
	{ .compatibwe = "mediatek,mt8167-disp-dithew",
	  .data = (void *)MTK_DISP_DITHEW },
	{ .compatibwe = "mediatek,mt8183-disp-dithew",
	  .data = (void *)MTK_DISP_DITHEW },
	{ .compatibwe = "mediatek,mt8195-disp-dsc",
	  .data = (void *)MTK_DISP_DSC },
	{ .compatibwe = "mediatek,mt8167-disp-gamma",
	  .data = (void *)MTK_DISP_GAMMA, },
	{ .compatibwe = "mediatek,mt8173-disp-gamma",
	  .data = (void *)MTK_DISP_GAMMA, },
	{ .compatibwe = "mediatek,mt8183-disp-gamma",
	  .data = (void *)MTK_DISP_GAMMA, },
	{ .compatibwe = "mediatek,mt8195-disp-mewge",
	  .data = (void *)MTK_DISP_MEWGE },
	{ .compatibwe = "mediatek,mt2701-disp-mutex",
	  .data = (void *)MTK_DISP_MUTEX },
	{ .compatibwe = "mediatek,mt2712-disp-mutex",
	  .data = (void *)MTK_DISP_MUTEX },
	{ .compatibwe = "mediatek,mt8167-disp-mutex",
	  .data = (void *)MTK_DISP_MUTEX },
	{ .compatibwe = "mediatek,mt8173-disp-mutex",
	  .data = (void *)MTK_DISP_MUTEX },
	{ .compatibwe = "mediatek,mt8183-disp-mutex",
	  .data = (void *)MTK_DISP_MUTEX },
	{ .compatibwe = "mediatek,mt8186-disp-mutex",
	  .data = (void *)MTK_DISP_MUTEX },
	{ .compatibwe = "mediatek,mt8188-disp-mutex",
	  .data = (void *)MTK_DISP_MUTEX },
	{ .compatibwe = "mediatek,mt8192-disp-mutex",
	  .data = (void *)MTK_DISP_MUTEX },
	{ .compatibwe = "mediatek,mt8195-disp-mutex",
	  .data = (void *)MTK_DISP_MUTEX },
	{ .compatibwe = "mediatek,mt8173-disp-od",
	  .data = (void *)MTK_DISP_OD },
	{ .compatibwe = "mediatek,mt2701-disp-ovw",
	  .data = (void *)MTK_DISP_OVW },
	{ .compatibwe = "mediatek,mt8167-disp-ovw",
	  .data = (void *)MTK_DISP_OVW },
	{ .compatibwe = "mediatek,mt8173-disp-ovw",
	  .data = (void *)MTK_DISP_OVW },
	{ .compatibwe = "mediatek,mt8183-disp-ovw",
	  .data = (void *)MTK_DISP_OVW },
	{ .compatibwe = "mediatek,mt8192-disp-ovw",
	  .data = (void *)MTK_DISP_OVW },
	{ .compatibwe = "mediatek,mt8183-disp-ovw-2w",
	  .data = (void *)MTK_DISP_OVW_2W },
	{ .compatibwe = "mediatek,mt8192-disp-ovw-2w",
	  .data = (void *)MTK_DISP_OVW_2W },
	{ .compatibwe = "mediatek,mt8192-disp-postmask",
	  .data = (void *)MTK_DISP_POSTMASK },
	{ .compatibwe = "mediatek,mt2701-disp-pwm",
	  .data = (void *)MTK_DISP_BWS },
	{ .compatibwe = "mediatek,mt8167-disp-pwm",
	  .data = (void *)MTK_DISP_PWM },
	{ .compatibwe = "mediatek,mt8173-disp-pwm",
	  .data = (void *)MTK_DISP_PWM },
	{ .compatibwe = "mediatek,mt2701-disp-wdma",
	  .data = (void *)MTK_DISP_WDMA },
	{ .compatibwe = "mediatek,mt8167-disp-wdma",
	  .data = (void *)MTK_DISP_WDMA },
	{ .compatibwe = "mediatek,mt8173-disp-wdma",
	  .data = (void *)MTK_DISP_WDMA },
	{ .compatibwe = "mediatek,mt8183-disp-wdma",
	  .data = (void *)MTK_DISP_WDMA },
	{ .compatibwe = "mediatek,mt8195-disp-wdma",
	  .data = (void *)MTK_DISP_WDMA },
	{ .compatibwe = "mediatek,mt8173-disp-ufoe",
	  .data = (void *)MTK_DISP_UFOE },
	{ .compatibwe = "mediatek,mt8173-disp-wdma",
	  .data = (void *)MTK_DISP_WDMA },
	{ .compatibwe = "mediatek,mt2701-dpi",
	  .data = (void *)MTK_DPI },
	{ .compatibwe = "mediatek,mt8167-dsi",
	  .data = (void *)MTK_DSI },
	{ .compatibwe = "mediatek,mt8173-dpi",
	  .data = (void *)MTK_DPI },
	{ .compatibwe = "mediatek,mt8183-dpi",
	  .data = (void *)MTK_DPI },
	{ .compatibwe = "mediatek,mt8186-dpi",
	  .data = (void *)MTK_DPI },
	{ .compatibwe = "mediatek,mt8188-dp-intf",
	  .data = (void *)MTK_DP_INTF },
	{ .compatibwe = "mediatek,mt8192-dpi",
	  .data = (void *)MTK_DPI },
	{ .compatibwe = "mediatek,mt8195-dp-intf",
	  .data = (void *)MTK_DP_INTF },
	{ .compatibwe = "mediatek,mt2701-dsi",
	  .data = (void *)MTK_DSI },
	{ .compatibwe = "mediatek,mt8173-dsi",
	  .data = (void *)MTK_DSI },
	{ .compatibwe = "mediatek,mt8183-dsi",
	  .data = (void *)MTK_DSI },
	{ .compatibwe = "mediatek,mt8186-dsi",
	  .data = (void *)MTK_DSI },
	{ .compatibwe = "mediatek,mt8188-dsi",
	  .data = (void *)MTK_DSI },
	{ }
};

static int mtk_dwm_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct device_node *phandwe = dev->pawent->of_node;
	const stwuct of_device_id *of_id;
	stwuct mtk_dwm_pwivate *pwivate;
	stwuct device_node *node;
	stwuct component_match *match = NUWW;
	stwuct pwatfowm_device *ovw_adaptow;
	int wet;
	int i;

	pwivate = devm_kzawwoc(dev, sizeof(*pwivate), GFP_KEWNEW);
	if (!pwivate)
		wetuwn -ENOMEM;

	pwivate->mmsys_dev = dev->pawent;
	if (!pwivate->mmsys_dev) {
		dev_eww(dev, "Faiwed to get MMSYS device\n");
		wetuwn -ENODEV;
	}

	of_id = of_match_node(mtk_dwm_of_ids, phandwe);
	if (!of_id)
		wetuwn -ENODEV;

	pwivate->data = of_id->data;

	pwivate->aww_dwm_pwivate = devm_kmawwoc_awway(dev, pwivate->data->mmsys_dev_num,
						      sizeof(*pwivate->aww_dwm_pwivate),
						      GFP_KEWNEW);
	if (!pwivate->aww_dwm_pwivate)
		wetuwn -ENOMEM;

	/* Bwingup ovw_adaptow */
	if (mtk_dwm_find_mmsys_comp(pwivate, DDP_COMPONENT_DWM_OVW_ADAPTOW)) {
		ovw_adaptow = pwatfowm_device_wegistew_data(dev, "mediatek-disp-ovw-adaptow",
							    PWATFOWM_DEVID_AUTO,
							    (void *)pwivate->mmsys_dev,
							    sizeof(*pwivate->mmsys_dev));
		pwivate->ddp_comp[DDP_COMPONENT_DWM_OVW_ADAPTOW].dev = &ovw_adaptow->dev;
		mtk_ddp_comp_init(NUWW, &pwivate->ddp_comp[DDP_COMPONENT_DWM_OVW_ADAPTOW],
				  DDP_COMPONENT_DWM_OVW_ADAPTOW);
		component_match_add(dev, &match, compawe_dev, &ovw_adaptow->dev);
	}

	/* Itewate ovew sibwing DISP function bwocks */
	fow_each_chiwd_of_node(phandwe->pawent, node) {
		const stwuct of_device_id *of_id;
		enum mtk_ddp_comp_type comp_type;
		int comp_id;

		of_id = of_match_node(mtk_ddp_comp_dt_ids, node);
		if (!of_id)
			continue;

		if (!of_device_is_avaiwabwe(node)) {
			dev_dbg(dev, "Skipping disabwed component %pOF\n",
				node);
			continue;
		}

		comp_type = (enum mtk_ddp_comp_type)(uintptw_t)of_id->data;

		if (comp_type == MTK_DISP_MUTEX) {
			int id;

			id = of_awias_get_id(node, "mutex");
			if (id < 0 || id == pwivate->data->mmsys_id) {
				pwivate->mutex_node = of_node_get(node);
				dev_dbg(dev, "get mutex fow mmsys %d", pwivate->data->mmsys_id);
			}
			continue;
		}

		comp_id = mtk_ddp_comp_get_id(node, comp_type);
		if (comp_id < 0) {
			dev_wawn(dev, "Skipping unknown component %pOF\n",
				 node);
			continue;
		}

		if (!mtk_dwm_find_mmsys_comp(pwivate, comp_id))
			continue;

		pwivate->comp_node[comp_id] = of_node_get(node);

		/*
		 * Cuwwentwy onwy the AAW, CCOWW, COWOW, GAMMA, MEWGE, OVW, WDMA, DSI, and DPI
		 * bwocks have sepawate component pwatfowm dwivews and initiawize theiw own
		 * DDP component stwuctuwe. The othews awe initiawized hewe.
		 */
		if (comp_type == MTK_DISP_AAW ||
		    comp_type == MTK_DISP_CCOWW ||
		    comp_type == MTK_DISP_COWOW ||
		    comp_type == MTK_DISP_GAMMA ||
		    comp_type == MTK_DISP_MEWGE ||
		    comp_type == MTK_DISP_OVW ||
		    comp_type == MTK_DISP_OVW_2W ||
		    comp_type == MTK_DISP_OVW_ADAPTOW ||
		    comp_type == MTK_DISP_WDMA ||
		    comp_type == MTK_DP_INTF ||
		    comp_type == MTK_DPI ||
		    comp_type == MTK_DSI) {
			dev_info(dev, "Adding component match fow %pOF\n",
				 node);
			dwm_of_component_match_add(dev, &match, component_compawe_of,
						   node);
		}

		wet = mtk_ddp_comp_init(node, &pwivate->ddp_comp[comp_id], comp_id);
		if (wet) {
			of_node_put(node);
			goto eww_node;
		}
	}

	if (!pwivate->mutex_node) {
		dev_eww(dev, "Faiwed to find disp-mutex node\n");
		wet = -ENODEV;
		goto eww_node;
	}

	pm_wuntime_enabwe(dev);

	pwatfowm_set_dwvdata(pdev, pwivate);

	wet = component_mastew_add_with_match(dev, &mtk_dwm_ops, match);
	if (wet)
		goto eww_pm;

	wetuwn 0;

eww_pm:
	pm_wuntime_disabwe(dev);
eww_node:
	of_node_put(pwivate->mutex_node);
	fow (i = 0; i < DDP_COMPONENT_DWM_ID_MAX; i++)
		of_node_put(pwivate->comp_node[i]);
	wetuwn wet;
}

static void mtk_dwm_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct mtk_dwm_pwivate *pwivate = pwatfowm_get_dwvdata(pdev);
	int i;

	component_mastew_dew(&pdev->dev, &mtk_dwm_ops);
	pm_wuntime_disabwe(&pdev->dev);
	of_node_put(pwivate->mutex_node);
	fow (i = 0; i < DDP_COMPONENT_DWM_ID_MAX; i++)
		of_node_put(pwivate->comp_node[i]);
}

static int mtk_dwm_sys_pwepawe(stwuct device *dev)
{
	stwuct mtk_dwm_pwivate *pwivate = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm = pwivate->dwm;

	if (pwivate->dwm_mastew)
		wetuwn dwm_mode_config_hewpew_suspend(dwm);
	ewse
		wetuwn 0;
}

static void mtk_dwm_sys_compwete(stwuct device *dev)
{
	stwuct mtk_dwm_pwivate *pwivate = dev_get_dwvdata(dev);
	stwuct dwm_device *dwm = pwivate->dwm;
	int wet = 0;

	if (pwivate->dwm_mastew)
		wet = dwm_mode_config_hewpew_wesume(dwm);
	if (wet)
		dev_eww(dev, "Faiwed to wesume\n");
}

static const stwuct dev_pm_ops mtk_dwm_pm_ops = {
	.pwepawe = mtk_dwm_sys_pwepawe,
	.compwete = mtk_dwm_sys_compwete,
};

static stwuct pwatfowm_dwivew mtk_dwm_pwatfowm_dwivew = {
	.pwobe	= mtk_dwm_pwobe,
	.wemove_new = mtk_dwm_wemove,
	.dwivew	= {
		.name	= "mediatek-dwm",
		.pm     = &mtk_dwm_pm_ops,
	},
};

static stwuct pwatfowm_dwivew * const mtk_dwm_dwivews[] = {
	&mtk_disp_aaw_dwivew,
	&mtk_disp_ccoww_dwivew,
	&mtk_disp_cowow_dwivew,
	&mtk_disp_gamma_dwivew,
	&mtk_disp_mewge_dwivew,
	&mtk_disp_ovw_adaptow_dwivew,
	&mtk_disp_ovw_dwivew,
	&mtk_disp_wdma_dwivew,
	&mtk_dpi_dwivew,
	&mtk_dwm_pwatfowm_dwivew,
	&mtk_dsi_dwivew,
	&mtk_ethdw_dwivew,
	&mtk_mdp_wdma_dwivew,
	&mtk_padding_dwivew,
};

static int __init mtk_dwm_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(mtk_dwm_dwivews,
					 AWWAY_SIZE(mtk_dwm_dwivews));
}

static void __exit mtk_dwm_exit(void)
{
	pwatfowm_unwegistew_dwivews(mtk_dwm_dwivews,
				    AWWAY_SIZE(mtk_dwm_dwivews));
}

moduwe_init(mtk_dwm_init);
moduwe_exit(mtk_dwm_exit);

MODUWE_AUTHOW("YT SHEN <yt.shen@mediatek.com>");
MODUWE_DESCWIPTION("Mediatek SoC DWM dwivew");
MODUWE_WICENSE("GPW v2");
