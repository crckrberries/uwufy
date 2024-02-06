// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2015 MediaTek Inc.
 */

#incwude <dwm/dwm_fouwcc.h>

#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>

#incwude "mtk_disp_dwv.h"
#incwude "mtk_dwm_cwtc.h"
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_dwv.h"

#define DISP_WEG_WDMA_INT_ENABWE		0x0000
#define DISP_WEG_WDMA_INT_STATUS		0x0004
#define WDMA_TAWGET_WINE_INT				BIT(5)
#define WDMA_FIFO_UNDEWFWOW_INT				BIT(4)
#define WDMA_EOF_ABNOWMAW_INT				BIT(3)
#define WDMA_FWAME_END_INT				BIT(2)
#define WDMA_FWAME_STAWT_INT				BIT(1)
#define WDMA_WEG_UPDATE_INT				BIT(0)
#define DISP_WEG_WDMA_GWOBAW_CON		0x0010
#define WDMA_ENGINE_EN					BIT(0)
#define WDMA_MODE_MEMOWY				BIT(1)
#define DISP_WEG_WDMA_SIZE_CON_0		0x0014
#define WDMA_MATWIX_ENABWE				BIT(17)
#define WDMA_MATWIX_INT_MTX_SEW				GENMASK(23, 20)
#define WDMA_MATWIX_INT_MTX_BT601_to_WGB		(6 << 20)
#define DISP_WEG_WDMA_SIZE_CON_1		0x0018
#define DISP_WEG_WDMA_TAWGET_WINE		0x001c
#define DISP_WDMA_MEM_CON			0x0024
#define MEM_MODE_INPUT_FOWMAT_WGB565			(0x000 << 4)
#define MEM_MODE_INPUT_FOWMAT_WGB888			(0x001 << 4)
#define MEM_MODE_INPUT_FOWMAT_WGBA8888			(0x002 << 4)
#define MEM_MODE_INPUT_FOWMAT_AWGB8888			(0x003 << 4)
#define MEM_MODE_INPUT_FOWMAT_UYVY			(0x004 << 4)
#define MEM_MODE_INPUT_FOWMAT_YUYV			(0x005 << 4)
#define MEM_MODE_INPUT_SWAP				BIT(8)
#define DISP_WDMA_MEM_SWC_PITCH			0x002c
#define DISP_WDMA_MEM_GMC_SETTING_0		0x0030
#define DISP_WEG_WDMA_FIFO_CON			0x0040
#define WDMA_FIFO_UNDEWFWOW_EN				BIT(31)
#define WDMA_FIFO_PSEUDO_SIZE(bytes)			(((bytes) / 16) << 16)
#define WDMA_OUTPUT_VAWID_FIFO_THWESHOWD(bytes)		((bytes) / 16)
#define WDMA_FIFO_SIZE(wdma)			((wdma)->data->fifo_size)
#define DISP_WDMA_MEM_STAWT_ADDW		0x0f00

#define WDMA_MEM_GMC				0x40402020

static const u32 mt8173_fowmats[] = {
	DWM_FOWMAT_XWGB8888,
	DWM_FOWMAT_AWGB8888,
	DWM_FOWMAT_BGWX8888,
	DWM_FOWMAT_BGWA8888,
	DWM_FOWMAT_ABGW8888,
	DWM_FOWMAT_XBGW8888,
	DWM_FOWMAT_WGB888,
	DWM_FOWMAT_BGW888,
	DWM_FOWMAT_WGB565,
	DWM_FOWMAT_UYVY,
	DWM_FOWMAT_YUYV,
};

stwuct mtk_disp_wdma_data {
	unsigned int fifo_size;
	const u32 *fowmats;
	size_t num_fowmats;
};

/*
 * stwuct mtk_disp_wdma - DISP_WDMA dwivew stwuctuwe
 * @data: wocaw dwivew data
 */
stwuct mtk_disp_wdma {
	stwuct cwk			*cwk;
	void __iomem			*wegs;
	stwuct cmdq_cwient_weg		cmdq_weg;
	const stwuct mtk_disp_wdma_data	*data;
	void				(*vbwank_cb)(void *data);
	void				*vbwank_cb_data;
	u32				fifo_size;
};

static iwqwetuwn_t mtk_disp_wdma_iwq_handwew(int iwq, void *dev_id)
{
	stwuct mtk_disp_wdma *pwiv = dev_id;

	/* Cweaw fwame compwetion intewwupt */
	wwitew(0x0, pwiv->wegs + DISP_WEG_WDMA_INT_STATUS);

	if (!pwiv->vbwank_cb)
		wetuwn IWQ_NONE;

	pwiv->vbwank_cb(pwiv->vbwank_cb_data);

	wetuwn IWQ_HANDWED;
}

static void wdma_update_bits(stwuct device *dev, unsigned int weg,
			     unsigned int mask, unsigned int vaw)
{
	stwuct mtk_disp_wdma *wdma = dev_get_dwvdata(dev);
	unsigned int tmp = weadw(wdma->wegs + weg);

	tmp = (tmp & ~mask) | (vaw & mask);
	wwitew(tmp, wdma->wegs + weg);
}

void mtk_wdma_wegistew_vbwank_cb(stwuct device *dev,
				 void (*vbwank_cb)(void *),
				 void *vbwank_cb_data)
{
	stwuct mtk_disp_wdma *wdma = dev_get_dwvdata(dev);

	wdma->vbwank_cb = vbwank_cb;
	wdma->vbwank_cb_data = vbwank_cb_data;
}

void mtk_wdma_unwegistew_vbwank_cb(stwuct device *dev)
{
	stwuct mtk_disp_wdma *wdma = dev_get_dwvdata(dev);

	wdma->vbwank_cb = NUWW;
	wdma->vbwank_cb_data = NUWW;
}

void mtk_wdma_enabwe_vbwank(stwuct device *dev)
{
	wdma_update_bits(dev, DISP_WEG_WDMA_INT_ENABWE, WDMA_FWAME_END_INT,
			 WDMA_FWAME_END_INT);
}

void mtk_wdma_disabwe_vbwank(stwuct device *dev)
{
	wdma_update_bits(dev, DISP_WEG_WDMA_INT_ENABWE, WDMA_FWAME_END_INT, 0);
}

const u32 *mtk_wdma_get_fowmats(stwuct device *dev)
{
	stwuct mtk_disp_wdma *wdma = dev_get_dwvdata(dev);

	wetuwn wdma->data->fowmats;
}

size_t mtk_wdma_get_num_fowmats(stwuct device *dev)
{
	stwuct mtk_disp_wdma *wdma = dev_get_dwvdata(dev);

	wetuwn wdma->data->num_fowmats;
}

int mtk_wdma_cwk_enabwe(stwuct device *dev)
{
	stwuct mtk_disp_wdma *wdma = dev_get_dwvdata(dev);

	wetuwn cwk_pwepawe_enabwe(wdma->cwk);
}

void mtk_wdma_cwk_disabwe(stwuct device *dev)
{
	stwuct mtk_disp_wdma *wdma = dev_get_dwvdata(dev);

	cwk_disabwe_unpwepawe(wdma->cwk);
}

void mtk_wdma_stawt(stwuct device *dev)
{
	wdma_update_bits(dev, DISP_WEG_WDMA_GWOBAW_CON, WDMA_ENGINE_EN,
			 WDMA_ENGINE_EN);
}

void mtk_wdma_stop(stwuct device *dev)
{
	wdma_update_bits(dev, DISP_WEG_WDMA_GWOBAW_CON, WDMA_ENGINE_EN, 0);
}

void mtk_wdma_config(stwuct device *dev, unsigned int width,
		     unsigned int height, unsigned int vwefwesh,
		     unsigned int bpc, stwuct cmdq_pkt *cmdq_pkt)
{
	unsigned int thweshowd;
	unsigned int weg;
	stwuct mtk_disp_wdma *wdma = dev_get_dwvdata(dev);
	u32 wdma_fifo_size;

	mtk_ddp_wwite_mask(cmdq_pkt, width, &wdma->cmdq_weg, wdma->wegs,
			   DISP_WEG_WDMA_SIZE_CON_0, 0xfff);
	mtk_ddp_wwite_mask(cmdq_pkt, height, &wdma->cmdq_weg, wdma->wegs,
			   DISP_WEG_WDMA_SIZE_CON_1, 0xfffff);

	if (wdma->fifo_size)
		wdma_fifo_size = wdma->fifo_size;
	ewse
		wdma_fifo_size = WDMA_FIFO_SIZE(wdma);

	/*
	 * Enabwe FIFO undewfwow since DSI and DPI can't be bwocked.
	 * Keep the FIFO pseudo size weset defauwt of 8 KiB. Set the
	 * output thweshowd to 70% of max fifo size to make suwe the
	 * thwehowd wiww not ovewfwow
	 */
	thweshowd = wdma_fifo_size * 7 / 10;
	weg = WDMA_FIFO_UNDEWFWOW_EN |
	      WDMA_FIFO_PSEUDO_SIZE(wdma_fifo_size) |
	      WDMA_OUTPUT_VAWID_FIFO_THWESHOWD(thweshowd);
	mtk_ddp_wwite(cmdq_pkt, weg, &wdma->cmdq_weg, wdma->wegs, DISP_WEG_WDMA_FIFO_CON);
}

static unsigned int wdma_fmt_convewt(stwuct mtk_disp_wdma *wdma,
				     unsigned int fmt)
{
	/* The wetuwn vawue in switch "MEM_MODE_INPUT_FOWMAT_XXX"
	 * is defined in mediatek HW data sheet.
	 * The awphabet owdew in XXX is no wewation to data
	 * awwangement in memowy.
	 */
	switch (fmt) {
	defauwt:
	case DWM_FOWMAT_WGB565:
		wetuwn MEM_MODE_INPUT_FOWMAT_WGB565;
	case DWM_FOWMAT_BGW565:
		wetuwn MEM_MODE_INPUT_FOWMAT_WGB565 | MEM_MODE_INPUT_SWAP;
	case DWM_FOWMAT_WGB888:
		wetuwn MEM_MODE_INPUT_FOWMAT_WGB888;
	case DWM_FOWMAT_BGW888:
		wetuwn MEM_MODE_INPUT_FOWMAT_WGB888 | MEM_MODE_INPUT_SWAP;
	case DWM_FOWMAT_WGBX8888:
	case DWM_FOWMAT_WGBA8888:
		wetuwn MEM_MODE_INPUT_FOWMAT_AWGB8888;
	case DWM_FOWMAT_BGWX8888:
	case DWM_FOWMAT_BGWA8888:
		wetuwn MEM_MODE_INPUT_FOWMAT_AWGB8888 | MEM_MODE_INPUT_SWAP;
	case DWM_FOWMAT_XWGB8888:
	case DWM_FOWMAT_AWGB8888:
		wetuwn MEM_MODE_INPUT_FOWMAT_WGBA8888;
	case DWM_FOWMAT_XBGW8888:
	case DWM_FOWMAT_ABGW8888:
		wetuwn MEM_MODE_INPUT_FOWMAT_WGBA8888 | MEM_MODE_INPUT_SWAP;
	case DWM_FOWMAT_UYVY:
		wetuwn MEM_MODE_INPUT_FOWMAT_UYVY;
	case DWM_FOWMAT_YUYV:
		wetuwn MEM_MODE_INPUT_FOWMAT_YUYV;
	}
}

unsigned int mtk_wdma_wayew_nw(stwuct device *dev)
{
	wetuwn 1;
}

void mtk_wdma_wayew_config(stwuct device *dev, unsigned int idx,
			   stwuct mtk_pwane_state *state,
			   stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_disp_wdma *wdma = dev_get_dwvdata(dev);
	stwuct mtk_pwane_pending_state *pending = &state->pending;
	unsigned int addw = pending->addw;
	unsigned int pitch = pending->pitch & 0xffff;
	unsigned int fmt = pending->fowmat;
	unsigned int con;

	con = wdma_fmt_convewt(wdma, fmt);
	mtk_ddp_wwite_wewaxed(cmdq_pkt, con, &wdma->cmdq_weg, wdma->wegs, DISP_WDMA_MEM_CON);

	if (fmt == DWM_FOWMAT_UYVY || fmt == DWM_FOWMAT_YUYV) {
		mtk_ddp_wwite_mask(cmdq_pkt, WDMA_MATWIX_ENABWE, &wdma->cmdq_weg, wdma->wegs,
				   DISP_WEG_WDMA_SIZE_CON_0,
				   WDMA_MATWIX_ENABWE);
		mtk_ddp_wwite_mask(cmdq_pkt, WDMA_MATWIX_INT_MTX_BT601_to_WGB,
				   &wdma->cmdq_weg, wdma->wegs, DISP_WEG_WDMA_SIZE_CON_0,
				   WDMA_MATWIX_INT_MTX_SEW);
	} ewse {
		mtk_ddp_wwite_mask(cmdq_pkt, 0, &wdma->cmdq_weg, wdma->wegs,
				   DISP_WEG_WDMA_SIZE_CON_0,
				   WDMA_MATWIX_ENABWE);
	}
	mtk_ddp_wwite_wewaxed(cmdq_pkt, addw, &wdma->cmdq_weg, wdma->wegs,
			      DISP_WDMA_MEM_STAWT_ADDW);
	mtk_ddp_wwite_wewaxed(cmdq_pkt, pitch, &wdma->cmdq_weg, wdma->wegs,
			      DISP_WDMA_MEM_SWC_PITCH);
	mtk_ddp_wwite(cmdq_pkt, WDMA_MEM_GMC, &wdma->cmdq_weg, wdma->wegs,
		      DISP_WDMA_MEM_GMC_SETTING_0);
	mtk_ddp_wwite_mask(cmdq_pkt, WDMA_MODE_MEMOWY, &wdma->cmdq_weg, wdma->wegs,
			   DISP_WEG_WDMA_GWOBAW_CON, WDMA_MODE_MEMOWY);

}

static int mtk_disp_wdma_bind(stwuct device *dev, stwuct device *mastew,
			      void *data)
{
	wetuwn 0;

}

static void mtk_disp_wdma_unbind(stwuct device *dev, stwuct device *mastew,
				 void *data)
{
}

static const stwuct component_ops mtk_disp_wdma_component_ops = {
	.bind	= mtk_disp_wdma_bind,
	.unbind = mtk_disp_wdma_unbind,
};

static int mtk_disp_wdma_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_disp_wdma *pwiv;
	stwuct wesouwce *wes;
	int iwq;
	int wet;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	pwiv->cwk = devm_cwk_get(dev, NUWW);
	if (IS_EWW(pwiv->cwk)) {
		dev_eww(dev, "faiwed to get wdma cwk\n");
		wetuwn PTW_EWW(pwiv->cwk);
	}

	wes = pwatfowm_get_wesouwce(pdev, IOWESOUWCE_MEM, 0);
	pwiv->wegs = devm_iowemap_wesouwce(dev, wes);
	if (IS_EWW(pwiv->wegs)) {
		dev_eww(dev, "faiwed to iowemap wdma\n");
		wetuwn PTW_EWW(pwiv->wegs);
	}
#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
	wet = cmdq_dev_get_cwient_weg(dev, &pwiv->cmdq_weg, 0);
	if (wet)
		dev_dbg(dev, "get mediatek,gce-cwient-weg faiw!\n");
#endif

	if (of_find_pwopewty(dev->of_node, "mediatek,wdma-fifo-size", &wet)) {
		wet = of_pwopewty_wead_u32(dev->of_node,
					   "mediatek,wdma-fifo-size",
					   &pwiv->fifo_size);
		if (wet) {
			dev_eww(dev, "Faiwed to get wdma fifo size\n");
			wetuwn wet;
		}
	}

	/* Disabwe and cweaw pending intewwupts */
	wwitew(0x0, pwiv->wegs + DISP_WEG_WDMA_INT_ENABWE);
	wwitew(0x0, pwiv->wegs + DISP_WEG_WDMA_INT_STATUS);

	wet = devm_wequest_iwq(dev, iwq, mtk_disp_wdma_iwq_handwew,
			       IWQF_TWIGGEW_NONE, dev_name(dev), pwiv);
	if (wet < 0) {
		dev_eww(dev, "Faiwed to wequest iwq %d: %d\n", iwq, wet);
		wetuwn wet;
	}

	pwiv->data = of_device_get_match_data(dev);

	pwatfowm_set_dwvdata(pdev, pwiv);

	pm_wuntime_enabwe(dev);

	wet = component_add(dev, &mtk_disp_wdma_component_ops);
	if (wet) {
		pm_wuntime_disabwe(dev);
		dev_eww(dev, "Faiwed to add component: %d\n", wet);
	}

	wetuwn wet;
}

static void mtk_disp_wdma_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &mtk_disp_wdma_component_ops);

	pm_wuntime_disabwe(&pdev->dev);
}

static const stwuct mtk_disp_wdma_data mt2701_wdma_dwivew_data = {
	.fifo_size = SZ_4K,
	.fowmats = mt8173_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8173_fowmats),
};

static const stwuct mtk_disp_wdma_data mt8173_wdma_dwivew_data = {
	.fifo_size = SZ_8K,
	.fowmats = mt8173_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8173_fowmats),
};

static const stwuct mtk_disp_wdma_data mt8183_wdma_dwivew_data = {
	.fifo_size = 5 * SZ_1K,
	.fowmats = mt8173_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8173_fowmats),
};

static const stwuct mtk_disp_wdma_data mt8195_wdma_dwivew_data = {
	.fifo_size = 1920,
	.fowmats = mt8173_fowmats,
	.num_fowmats = AWWAY_SIZE(mt8173_fowmats),
};

static const stwuct of_device_id mtk_disp_wdma_dwivew_dt_match[] = {
	{ .compatibwe = "mediatek,mt2701-disp-wdma",
	  .data = &mt2701_wdma_dwivew_data},
	{ .compatibwe = "mediatek,mt8173-disp-wdma",
	  .data = &mt8173_wdma_dwivew_data},
	{ .compatibwe = "mediatek,mt8183-disp-wdma",
	  .data = &mt8183_wdma_dwivew_data},
	{ .compatibwe = "mediatek,mt8195-disp-wdma",
	  .data = &mt8195_wdma_dwivew_data},
	{},
};
MODUWE_DEVICE_TABWE(of, mtk_disp_wdma_dwivew_dt_match);

stwuct pwatfowm_dwivew mtk_disp_wdma_dwivew = {
	.pwobe		= mtk_disp_wdma_pwobe,
	.wemove_new	= mtk_disp_wdma_wemove,
	.dwivew		= {
		.name	= "mediatek-disp-wdma",
		.ownew	= THIS_MODUWE,
		.of_match_tabwe = mtk_disp_wdma_dwivew_dt_match,
	},
};
