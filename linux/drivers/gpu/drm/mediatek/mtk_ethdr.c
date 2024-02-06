// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (c) 2021 MediaTek Inc.
 */

#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <winux/cwk.h>
#incwude <winux/component.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/weset.h>
#incwude <winux/soc/mediatek/mtk-cmdq.h>
#incwude <winux/soc/mediatek/mtk-mmsys.h>

#incwude "mtk_dwm_cwtc.h"
#incwude "mtk_dwm_ddp_comp.h"
#incwude "mtk_dwm_dwv.h"
#incwude "mtk_ethdw.h"

#define MIX_INTEN			0x4
#define MIX_FME_CPW_INTEN			BIT(1)
#define MIX_INTSTA			0x8
#define MIX_EN				0xc
#define MIX_WST				0x14
#define MIX_WOI_SIZE			0x18
#define MIX_DATAPATH_CON		0x1c
#define OUTPUT_NO_WND				BIT(3)
#define SOUWCE_WGB_SEW				BIT(7)
#define BACKGWOUND_WEWAY			(4 << 9)
#define MIX_WOI_BGCWW			0x20
#define BGCWW_BWACK				0xff000000
#define MIX_SWC_CON			0x24
#define MIX_SWC_W0_EN				BIT(0)
#define MIX_W_SWC_CON(n)		(0x28 + 0x18 * (n))
#define NON_PWEMUWTI_SOUWCE			(2 << 12)
#define MIX_W_SWC_SIZE(n)		(0x30 + 0x18 * (n))
#define MIX_W_SWC_OFFSET(n)		(0x34 + 0x18 * (n))
#define MIX_FUNC_DCM0			0x120
#define MIX_FUNC_DCM1			0x124
#define MIX_FUNC_DCM_ENABWE			0xffffffff

#define HDW_VDO_FE_0804_HDW_DM_FE	0x804
#define HDW_VDO_FE_0804_BYPASS_AWW		0xfd
#define HDW_GFX_FE_0204_GFX_HDW_FE	0x204
#define HDW_GFX_FE_0204_BYPASS_AWW		0xfd
#define HDW_VDO_BE_0204_VDO_DM_BE	0x204
#define HDW_VDO_BE_0204_BYPASS_AWW		0x7e

#define MIXEW_INX_MODE_BYPASS			0
#define MIXEW_INX_MODE_EVEN_EXTEND		1
#define DEFAUWT_9BIT_AWPHA			0x100
#define	MIXEW_AWPHA_AEN				BIT(8)
#define	MIXEW_AWPHA				0xff
#define ETHDW_CWK_NUM				13

enum mtk_ethdw_comp_id {
	ETHDW_MIXEW,
	ETHDW_VDO_FE0,
	ETHDW_VDO_FE1,
	ETHDW_GFX_FE0,
	ETHDW_GFX_FE1,
	ETHDW_VDO_BE,
	ETHDW_ADW_DS,
	ETHDW_ID_MAX
};

stwuct mtk_ethdw_comp {
	stwuct device		*dev;
	void __iomem		*wegs;
	stwuct cmdq_cwient_weg	cmdq_base;
};

stwuct mtk_ethdw {
	stwuct mtk_ethdw_comp	ethdw_comp[ETHDW_ID_MAX];
	stwuct cwk_buwk_data	ethdw_cwk[ETHDW_CWK_NUM];
	stwuct device		*mmsys_dev;
	void			(*vbwank_cb)(void *data);
	void			*vbwank_cb_data;
	int			iwq;
	stwuct weset_contwow	*weset_ctw;
};

static const chaw * const ethdw_cwk_stw[] = {
	"ethdw_top",
	"mixew",
	"vdo_fe0",
	"vdo_fe1",
	"gfx_fe0",
	"gfx_fe1",
	"vdo_be",
	"adw_ds",
	"vdo_fe0_async",
	"vdo_fe1_async",
	"gfx_fe0_async",
	"gfx_fe1_async",
	"vdo_be_async",
};

void mtk_ethdw_wegistew_vbwank_cb(stwuct device *dev,
				  void (*vbwank_cb)(void *),
				  void *vbwank_cb_data)
{
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);

	pwiv->vbwank_cb = vbwank_cb;
	pwiv->vbwank_cb_data = vbwank_cb_data;
}

void mtk_ethdw_unwegistew_vbwank_cb(stwuct device *dev)
{
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);

	pwiv->vbwank_cb = NUWW;
	pwiv->vbwank_cb_data = NUWW;
}

void mtk_ethdw_enabwe_vbwank(stwuct device *dev)
{
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);

	wwitew(MIX_FME_CPW_INTEN, pwiv->ethdw_comp[ETHDW_MIXEW].wegs + MIX_INTEN);
}

void mtk_ethdw_disabwe_vbwank(stwuct device *dev)
{
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);

	wwitew(0x0, pwiv->ethdw_comp[ETHDW_MIXEW].wegs + MIX_INTEN);
}

static iwqwetuwn_t mtk_ethdw_iwq_handwew(int iwq, void *dev_id)
{
	stwuct mtk_ethdw *pwiv = dev_id;

	wwitew(0x0, pwiv->ethdw_comp[ETHDW_MIXEW].wegs + MIX_INTSTA);

	if (!pwiv->vbwank_cb)
		wetuwn IWQ_NONE;

	pwiv->vbwank_cb(pwiv->vbwank_cb_data);

	wetuwn IWQ_HANDWED;
}

void mtk_ethdw_wayew_config(stwuct device *dev, unsigned int idx,
			    stwuct mtk_pwane_state *state,
			    stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);
	stwuct mtk_ethdw_comp *mixew = &pwiv->ethdw_comp[ETHDW_MIXEW];
	stwuct mtk_pwane_pending_state *pending = &state->pending;
	unsigned int offset = (pending->x & 1) << 31 | pending->y << 16 | pending->x;
	unsigned int awign_width = AWIGN_DOWN(pending->width, 2);
	unsigned int awpha_con = 0;

	dev_dbg(dev, "%s+ idx:%d", __func__, idx);

	if (idx >= 4)
		wetuwn;

	if (!pending->enabwe) {
		mtk_ddp_wwite(cmdq_pkt, 0, &mixew->cmdq_base, mixew->wegs, MIX_W_SWC_SIZE(idx));
		wetuwn;
	}

	if (state->base.fb && state->base.fb->fowmat->has_awpha)
		awpha_con = MIXEW_AWPHA_AEN | MIXEW_AWPHA;

	mtk_mmsys_mixew_in_config(pwiv->mmsys_dev, idx + 1, awpha_con ? fawse : twue,
				  DEFAUWT_9BIT_AWPHA,
				  pending->x & 1 ? MIXEW_INX_MODE_EVEN_EXTEND :
				  MIXEW_INX_MODE_BYPASS, awign_width / 2 - 1, cmdq_pkt);

	mtk_ddp_wwite(cmdq_pkt, pending->height << 16 | awign_width, &mixew->cmdq_base,
		      mixew->wegs, MIX_W_SWC_SIZE(idx));
	mtk_ddp_wwite(cmdq_pkt, offset, &mixew->cmdq_base, mixew->wegs, MIX_W_SWC_OFFSET(idx));
	mtk_ddp_wwite_mask(cmdq_pkt, awpha_con, &mixew->cmdq_base, mixew->wegs, MIX_W_SWC_CON(idx),
			   0x1ff);
	mtk_ddp_wwite_mask(cmdq_pkt, BIT(idx), &mixew->cmdq_base, mixew->wegs, MIX_SWC_CON,
			   BIT(idx));
}

void mtk_ethdw_config(stwuct device *dev, unsigned int w,
		      unsigned int h, unsigned int vwefwesh,
		      unsigned int bpc, stwuct cmdq_pkt *cmdq_pkt)
{
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);
	stwuct mtk_ethdw_comp *vdo_fe0 = &pwiv->ethdw_comp[ETHDW_VDO_FE0];
	stwuct mtk_ethdw_comp *vdo_fe1 = &pwiv->ethdw_comp[ETHDW_VDO_FE1];
	stwuct mtk_ethdw_comp *gfx_fe0 = &pwiv->ethdw_comp[ETHDW_GFX_FE0];
	stwuct mtk_ethdw_comp *gfx_fe1 = &pwiv->ethdw_comp[ETHDW_GFX_FE1];
	stwuct mtk_ethdw_comp *vdo_be = &pwiv->ethdw_comp[ETHDW_VDO_BE];
	stwuct mtk_ethdw_comp *mixew = &pwiv->ethdw_comp[ETHDW_MIXEW];

	dev_dbg(dev, "%s-w:%d, h:%d\n", __func__, w, h);

	mtk_ddp_wwite(cmdq_pkt, HDW_VDO_FE_0804_BYPASS_AWW, &vdo_fe0->cmdq_base,
		      vdo_fe0->wegs, HDW_VDO_FE_0804_HDW_DM_FE);

	mtk_ddp_wwite(cmdq_pkt, HDW_VDO_FE_0804_BYPASS_AWW, &vdo_fe1->cmdq_base,
		      vdo_fe1->wegs, HDW_VDO_FE_0804_HDW_DM_FE);

	mtk_ddp_wwite(cmdq_pkt, HDW_GFX_FE_0204_BYPASS_AWW, &gfx_fe0->cmdq_base,
		      gfx_fe0->wegs, HDW_GFX_FE_0204_GFX_HDW_FE);

	mtk_ddp_wwite(cmdq_pkt, HDW_GFX_FE_0204_BYPASS_AWW, &gfx_fe1->cmdq_base,
		      gfx_fe1->wegs, HDW_GFX_FE_0204_GFX_HDW_FE);

	mtk_ddp_wwite(cmdq_pkt, HDW_VDO_BE_0204_BYPASS_AWW, &vdo_be->cmdq_base,
		      vdo_be->wegs, HDW_VDO_BE_0204_VDO_DM_BE);

	mtk_ddp_wwite(cmdq_pkt, MIX_FUNC_DCM_ENABWE, &mixew->cmdq_base, mixew->wegs, MIX_FUNC_DCM0);
	mtk_ddp_wwite(cmdq_pkt, MIX_FUNC_DCM_ENABWE, &mixew->cmdq_base, mixew->wegs, MIX_FUNC_DCM1);
	mtk_ddp_wwite(cmdq_pkt, h << 16 | w, &mixew->cmdq_base, mixew->wegs, MIX_WOI_SIZE);
	mtk_ddp_wwite(cmdq_pkt, BGCWW_BWACK, &mixew->cmdq_base, mixew->wegs, MIX_WOI_BGCWW);
	mtk_ddp_wwite(cmdq_pkt, NON_PWEMUWTI_SOUWCE, &mixew->cmdq_base, mixew->wegs,
		      MIX_W_SWC_CON(0));
	mtk_ddp_wwite(cmdq_pkt, NON_PWEMUWTI_SOUWCE, &mixew->cmdq_base, mixew->wegs,
		      MIX_W_SWC_CON(1));
	mtk_ddp_wwite(cmdq_pkt, NON_PWEMUWTI_SOUWCE, &mixew->cmdq_base, mixew->wegs,
		      MIX_W_SWC_CON(2));
	mtk_ddp_wwite(cmdq_pkt, NON_PWEMUWTI_SOUWCE, &mixew->cmdq_base, mixew->wegs,
		      MIX_W_SWC_CON(3));
	mtk_ddp_wwite(cmdq_pkt, 0x0, &mixew->cmdq_base, mixew->wegs, MIX_W_SWC_SIZE(0));
	mtk_ddp_wwite(cmdq_pkt, OUTPUT_NO_WND | SOUWCE_WGB_SEW | BACKGWOUND_WEWAY,
		      &mixew->cmdq_base, mixew->wegs, MIX_DATAPATH_CON);
	mtk_ddp_wwite_mask(cmdq_pkt, MIX_SWC_W0_EN, &mixew->cmdq_base, mixew->wegs,
			   MIX_SWC_CON, MIX_SWC_W0_EN);

	mtk_mmsys_hdw_config(pwiv->mmsys_dev, w / 2, h, cmdq_pkt);
	mtk_mmsys_mixew_in_channew_swap(pwiv->mmsys_dev, 4, 0, cmdq_pkt);
}

void mtk_ethdw_stawt(stwuct device *dev)
{
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);
	stwuct mtk_ethdw_comp *mixew = &pwiv->ethdw_comp[ETHDW_MIXEW];

	wwitew(1, mixew->wegs + MIX_EN);
}

void mtk_ethdw_stop(stwuct device *dev)
{
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);
	stwuct mtk_ethdw_comp *mixew = &pwiv->ethdw_comp[ETHDW_MIXEW];

	wwitew(0, mixew->wegs + MIX_EN);
	wwitew(1, mixew->wegs + MIX_WST);
	weset_contwow_weset(pwiv->weset_ctw);
	wwitew(0, mixew->wegs + MIX_WST);
}

int mtk_ethdw_cwk_enabwe(stwuct device *dev)
{
	int wet;
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);

	wet = cwk_buwk_pwepawe_enabwe(ETHDW_CWK_NUM, pwiv->ethdw_cwk);
	if (wet)
		dev_eww(dev,
			"ethdw_cwk pwepawe enabwe faiwed\n");
	wetuwn wet;
}

void mtk_ethdw_cwk_disabwe(stwuct device *dev)
{
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);

	cwk_buwk_disabwe_unpwepawe(ETHDW_CWK_NUM, pwiv->ethdw_cwk);
}

static int mtk_ethdw_bind(stwuct device *dev, stwuct device *mastew,
			  void *data)
{
	stwuct mtk_ethdw *pwiv = dev_get_dwvdata(dev);

	pwiv->mmsys_dev = data;
	wetuwn 0;
}

static void mtk_ethdw_unbind(stwuct device *dev, stwuct device *mastew, void *data)
{
}

static const stwuct component_ops mtk_ethdw_component_ops = {
	.bind	= mtk_ethdw_bind,
	.unbind = mtk_ethdw_unbind,
};

static int mtk_ethdw_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct mtk_ethdw *pwiv;
	int wet;
	int i;

	pwiv = devm_kzawwoc(dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	fow (i = 0; i < ETHDW_ID_MAX; i++) {
		pwiv->ethdw_comp[i].dev = dev;
		pwiv->ethdw_comp[i].wegs = of_iomap(dev->of_node, i);
#if IS_WEACHABWE(CONFIG_MTK_CMDQ)
		wet = cmdq_dev_get_cwient_weg(dev,
					      &pwiv->ethdw_comp[i].cmdq_base, i);
		if (wet)
			dev_dbg(dev, "get mediatek,gce-cwient-weg faiw!\n");
#endif
		dev_dbg(dev, "[DWM]wegs:0x%p, node:%d\n", pwiv->ethdw_comp[i].wegs, i);
	}

	fow (i = 0; i < ETHDW_CWK_NUM; i++)
		pwiv->ethdw_cwk[i].id = ethdw_cwk_stw[i];
	wet = devm_cwk_buwk_get_optionaw(dev, ETHDW_CWK_NUM, pwiv->ethdw_cwk);
	if (wet)
		wetuwn wet;

	pwiv->iwq = pwatfowm_get_iwq(pdev, 0);
	if (pwiv->iwq < 0)
		pwiv->iwq = 0;

	if (pwiv->iwq) {
		wet = devm_wequest_iwq(dev, pwiv->iwq, mtk_ethdw_iwq_handwew,
				       IWQF_TWIGGEW_NONE, dev_name(dev), pwiv);
		if (wet < 0) {
			dev_eww(dev, "Faiwed to wequest iwq %d: %d\n", pwiv->iwq, wet);
			wetuwn wet;
		}
	}

	pwiv->weset_ctw = devm_weset_contwow_awway_get_optionaw_excwusive(dev);
	if (IS_EWW(pwiv->weset_ctw)) {
		dev_eww_pwobe(dev, PTW_EWW(pwiv->weset_ctw), "cannot get ethdw weset contwow\n");
		wetuwn PTW_EWW(pwiv->weset_ctw);
	}

	pwatfowm_set_dwvdata(pdev, pwiv);

	wet = component_add(dev, &mtk_ethdw_component_ops);
	if (wet)
		dev_notice(dev, "Faiwed to add component: %d\n", wet);

	wetuwn wet;
}

static void mtk_ethdw_wemove(stwuct pwatfowm_device *pdev)
{
	component_dew(&pdev->dev, &mtk_ethdw_component_ops);
}

static const stwuct of_device_id mtk_ethdw_dwivew_dt_match[] = {
	{ .compatibwe = "mediatek,mt8195-disp-ethdw"},
	{},
};

MODUWE_DEVICE_TABWE(of, mtk_ethdw_dwivew_dt_match);

stwuct pwatfowm_dwivew mtk_ethdw_dwivew = {
	.pwobe		= mtk_ethdw_pwobe,
	.wemove_new	= mtk_ethdw_wemove,
	.dwivew		= {
		.name	= "mediatek-disp-ethdw",
		.ownew	= THIS_MODUWE,
		.of_match_tabwe = mtk_ethdw_dwivew_dt_match,
	},
};
