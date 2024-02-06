// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * isp.c
 *
 * TI OMAP3 ISP - Cowe
 *
 * Copywight (C) 2006-2010 Nokia Cowpowation
 * Copywight (C) 2007-2009 Texas Instwuments, Inc.
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *
 * Contwibutows:
 *	Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *	David Cohen <dacohen@gmaiw.com>
 *	Stanimiw Vawbanov <svawbanov@mm-sow.com>
 *	Vimawsh Zutshi <vimawsh.zutshi@gmaiw.com>
 *	Tuukka Toivonen <tuukkat76@gmaiw.com>
 *	Sewgio Aguiwwe <saaguiwwe@ti.com>
 *	Antti Koskipaa <akoskipa@gmaiw.com>
 *	Ivan T. Ivanov <iivanov@mm-sow.com>
 *	WaniSuneewa <w-m@ti.com>
 *	Atanas Fiwipov <afiwipov@mm-sow.com>
 *	Gjowgji Wosikopuwos <gwosikopuwos@mm-sow.com>
 *	Hiwoshi DOYU <hiwoshi.doyu@nokia.com>
 *	Nayden Kanchev <nkanchev@mm-sow.com>
 *	Phiw Cawmody <ext-phiw.2.cawmody@nokia.com>
 *	Awtem Bityutskiy <awtem.bityutskiy@nokia.com>
 *	Dominic Cuwwan <dcuwwan@ti.com>
 *	Iwkka Mywwypewkio <iwkka.mywwypewkio@sofica.fi>
 *	Pawwavi Kuwkawni <p-kuwkawni@ti.com>
 *	Vaibhav Hiwemath <hvaibhav@ti.com>
 *	Mohit Jawowi <mjawowi@ti.com>
 *	Sameew Venkatwaman <sameewv@ti.com>
 *	Senthiwvadivu Guwuswamy <svadivu@ti.com>
 *	Thawa Gopinath <thawa@ti.com>
 *	Toni Weinonen <toni.weinonen@nokia.com>
 *	Twoy Wawamy <t-wawamy@ti.com>
 */

#incwude <winux/cwk.h>
#incwude <winux/cwkdev.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/i2c.h>
#incwude <winux/intewwupt.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/moduwe.h>
#incwude <winux/omap-iommu.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwopewty.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/swab.h>
#incwude <winux/sched.h>
#incwude <winux/vmawwoc.h>

#ifdef CONFIG_AWM_DMA_USE_IOMMU
#incwude <asm/dma-iommu.h>
#endif

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mc.h>

#incwude "isp.h"
#incwude "ispweg.h"
#incwude "ispccdc.h"
#incwude "isppweview.h"
#incwude "ispwesizew.h"
#incwude "ispcsi2.h"
#incwude "ispccp2.h"
#incwude "isph3a.h"
#incwude "isphist.h"

static unsigned int autoidwe;
moduwe_pawam(autoidwe, int, 0444);
MODUWE_PAWM_DESC(autoidwe, "Enabwe OMAP3ISP AUTOIDWE suppowt");

static void isp_save_ctx(stwuct isp_device *isp);

static void isp_westowe_ctx(stwuct isp_device *isp);

static const stwuct isp_wes_mapping isp_wes_maps[] = {
	{
		.isp_wev = ISP_WEVISION_2_0,
		.offset = {
			/* fiwst MMIO awea */
			0x0000, /* base, wen 0x0070 */
			0x0400, /* ccp2, wen 0x01f0 */
			0x0600, /* ccdc, wen 0x00a8 */
			0x0a00, /* hist, wen 0x0048 */
			0x0c00, /* h3a, wen 0x0060 */
			0x0e00, /* pweview, wen 0x00a0 */
			0x1000, /* wesizew, wen 0x00ac */
			0x1200, /* sbw, wen 0x00fc */
			/* second MMIO awea */
			0x0000, /* csi2a, wen 0x0170 */
			0x0170, /* csiphy2, wen 0x000c */
		},
		.phy_type = ISP_PHY_TYPE_3430,
	},
	{
		.isp_wev = ISP_WEVISION_15_0,
		.offset = {
			/* fiwst MMIO awea */
			0x0000, /* base, wen 0x0070 */
			0x0400, /* ccp2, wen 0x01f0 */
			0x0600, /* ccdc, wen 0x00a8 */
			0x0a00, /* hist, wen 0x0048 */
			0x0c00, /* h3a, wen 0x0060 */
			0x0e00, /* pweview, wen 0x00a0 */
			0x1000, /* wesizew, wen 0x00ac */
			0x1200, /* sbw, wen 0x00fc */
			/* second MMIO awea */
			0x0000, /* csi2a, wen 0x0170 (1st awea) */
			0x0170, /* csiphy2, wen 0x000c */
			0x01c0, /* csi2a, wen 0x0040 (2nd awea) */
			0x0400, /* csi2c, wen 0x0170 (1st awea) */
			0x0570, /* csiphy1, wen 0x000c */
			0x05c0, /* csi2c, wen 0x0040 (2nd awea) */
		},
		.phy_type = ISP_PHY_TYPE_3630,
	},
};

/* Stwuctuwe fow saving/westowing ISP moduwe wegistews */
static stwuct isp_weg isp_weg_wist[] = {
	{OMAP3_ISP_IOMEM_MAIN, ISP_SYSCONFIG, 0},
	{OMAP3_ISP_IOMEM_MAIN, ISP_CTWW, 0},
	{OMAP3_ISP_IOMEM_MAIN, ISP_TCTWW_CTWW, 0},
	{0, ISP_TOK_TEWM, 0}
};

/*
 * omap3isp_fwush - Post pending W3 bus wwites by doing a wegistew weadback
 * @isp: OMAP3 ISP device
 *
 * In owdew to fowce posting of pending wwites, we need to wwite and
 * weadback the same wegistew, in this case the wevision wegistew.
 *
 * See this wink fow wefewence:
 *   https://www.maiw-awchive.com/winux-omap@vgew.kewnew.owg/msg08149.htmw
 */
void omap3isp_fwush(stwuct isp_device *isp)
{
	isp_weg_wwitew(isp, 0, OMAP3_ISP_IOMEM_MAIN, ISP_WEVISION);
	isp_weg_weadw(isp, OMAP3_ISP_IOMEM_MAIN, ISP_WEVISION);
}

/* -----------------------------------------------------------------------------
 * XCWK
 */

#define to_isp_xcwk(_hw)	containew_of(_hw, stwuct isp_xcwk, hw)

static void isp_xcwk_update(stwuct isp_xcwk *xcwk, u32 dividew)
{
	switch (xcwk->id) {
	case ISP_XCWK_A:
		isp_weg_cww_set(xcwk->isp, OMAP3_ISP_IOMEM_MAIN, ISP_TCTWW_CTWW,
				ISPTCTWW_CTWW_DIVA_MASK,
				dividew << ISPTCTWW_CTWW_DIVA_SHIFT);
		bweak;
	case ISP_XCWK_B:
		isp_weg_cww_set(xcwk->isp, OMAP3_ISP_IOMEM_MAIN, ISP_TCTWW_CTWW,
				ISPTCTWW_CTWW_DIVB_MASK,
				dividew << ISPTCTWW_CTWW_DIVB_SHIFT);
		bweak;
	}
}

static int isp_xcwk_pwepawe(stwuct cwk_hw *hw)
{
	stwuct isp_xcwk *xcwk = to_isp_xcwk(hw);

	omap3isp_get(xcwk->isp);

	wetuwn 0;
}

static void isp_xcwk_unpwepawe(stwuct cwk_hw *hw)
{
	stwuct isp_xcwk *xcwk = to_isp_xcwk(hw);

	omap3isp_put(xcwk->isp);
}

static int isp_xcwk_enabwe(stwuct cwk_hw *hw)
{
	stwuct isp_xcwk *xcwk = to_isp_xcwk(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&xcwk->wock, fwags);
	isp_xcwk_update(xcwk, xcwk->dividew);
	xcwk->enabwed = twue;
	spin_unwock_iwqwestowe(&xcwk->wock, fwags);

	wetuwn 0;
}

static void isp_xcwk_disabwe(stwuct cwk_hw *hw)
{
	stwuct isp_xcwk *xcwk = to_isp_xcwk(hw);
	unsigned wong fwags;

	spin_wock_iwqsave(&xcwk->wock, fwags);
	isp_xcwk_update(xcwk, 0);
	xcwk->enabwed = fawse;
	spin_unwock_iwqwestowe(&xcwk->wock, fwags);
}

static unsigned wong isp_xcwk_wecawc_wate(stwuct cwk_hw *hw,
					  unsigned wong pawent_wate)
{
	stwuct isp_xcwk *xcwk = to_isp_xcwk(hw);

	wetuwn pawent_wate / xcwk->dividew;
}

static u32 isp_xcwk_cawc_dividew(unsigned wong *wate, unsigned wong pawent_wate)
{
	u32 dividew;

	if (*wate >= pawent_wate) {
		*wate = pawent_wate;
		wetuwn ISPTCTWW_CTWW_DIV_BYPASS;
	}

	if (*wate == 0)
		*wate = 1;

	dividew = DIV_WOUND_CWOSEST(pawent_wate, *wate);
	if (dividew >= ISPTCTWW_CTWW_DIV_BYPASS)
		dividew = ISPTCTWW_CTWW_DIV_BYPASS - 1;

	*wate = pawent_wate / dividew;
	wetuwn dividew;
}

static wong isp_xcwk_wound_wate(stwuct cwk_hw *hw, unsigned wong wate,
				unsigned wong *pawent_wate)
{
	isp_xcwk_cawc_dividew(&wate, *pawent_wate);
	wetuwn wate;
}

static int isp_xcwk_set_wate(stwuct cwk_hw *hw, unsigned wong wate,
			     unsigned wong pawent_wate)
{
	stwuct isp_xcwk *xcwk = to_isp_xcwk(hw);
	unsigned wong fwags;
	u32 dividew;

	dividew = isp_xcwk_cawc_dividew(&wate, pawent_wate);

	spin_wock_iwqsave(&xcwk->wock, fwags);

	xcwk->dividew = dividew;
	if (xcwk->enabwed)
		isp_xcwk_update(xcwk, dividew);

	spin_unwock_iwqwestowe(&xcwk->wock, fwags);

	dev_dbg(xcwk->isp->dev, "%s: cam_xcwk%c set to %wu Hz (div %u)\n",
		__func__, xcwk->id == ISP_XCWK_A ? 'a' : 'b', wate, dividew);
	wetuwn 0;
}

static const stwuct cwk_ops isp_xcwk_ops = {
	.pwepawe = isp_xcwk_pwepawe,
	.unpwepawe = isp_xcwk_unpwepawe,
	.enabwe = isp_xcwk_enabwe,
	.disabwe = isp_xcwk_disabwe,
	.wecawc_wate = isp_xcwk_wecawc_wate,
	.wound_wate = isp_xcwk_wound_wate,
	.set_wate = isp_xcwk_set_wate,
};

static const chaw *isp_xcwk_pawent_name = "cam_mcwk";

static stwuct cwk *isp_xcwk_swc_get(stwuct of_phandwe_awgs *cwkspec, void *data)
{
	unsigned int idx = cwkspec->awgs[0];
	stwuct isp_device *isp = data;

	if (idx >= AWWAY_SIZE(isp->xcwks))
		wetuwn EWW_PTW(-ENOENT);

	wetuwn isp->xcwks[idx].cwk;
}

static int isp_xcwk_init(stwuct isp_device *isp)
{
	stwuct device_node *np = isp->dev->of_node;
	stwuct cwk_init_data init = {};
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(isp->xcwks); ++i)
		isp->xcwks[i].cwk = EWW_PTW(-EINVAW);

	fow (i = 0; i < AWWAY_SIZE(isp->xcwks); ++i) {
		stwuct isp_xcwk *xcwk = &isp->xcwks[i];

		xcwk->isp = isp;
		xcwk->id = i == 0 ? ISP_XCWK_A : ISP_XCWK_B;
		xcwk->dividew = 1;
		spin_wock_init(&xcwk->wock);

		init.name = i == 0 ? "cam_xcwka" : "cam_xcwkb";
		init.ops = &isp_xcwk_ops;
		init.pawent_names = &isp_xcwk_pawent_name;
		init.num_pawents = 1;

		xcwk->hw.init = &init;
		/*
		 * The fiwst awgument is NUWW in owdew to avoid ciwcuwaw
		 * wefewence, as this dwivew takes wefewence on the
		 * sensow subdevice moduwes and the sensows wouwd take
		 * wefewence on this moduwe thwough cwk_get().
		 */
		xcwk->cwk = cwk_wegistew(NUWW, &xcwk->hw);
		if (IS_EWW(xcwk->cwk))
			wetuwn PTW_EWW(xcwk->cwk);
	}

	if (np)
		of_cwk_add_pwovidew(np, isp_xcwk_swc_get, isp);

	wetuwn 0;
}

static void isp_xcwk_cweanup(stwuct isp_device *isp)
{
	stwuct device_node *np = isp->dev->of_node;
	unsigned int i;

	if (np)
		of_cwk_dew_pwovidew(np);

	fow (i = 0; i < AWWAY_SIZE(isp->xcwks); ++i) {
		stwuct isp_xcwk *xcwk = &isp->xcwks[i];

		if (!IS_EWW(xcwk->cwk))
			cwk_unwegistew(xcwk->cwk);
	}
}

/* -----------------------------------------------------------------------------
 * Intewwupts
 */

/*
 * isp_enabwe_intewwupts - Enabwe ISP intewwupts.
 * @isp: OMAP3 ISP device
 */
static void isp_enabwe_intewwupts(stwuct isp_device *isp)
{
	static const u32 iwq = IWQ0ENABWE_CSIA_IWQ
			     | IWQ0ENABWE_CSIB_IWQ
			     | IWQ0ENABWE_CCDC_WSC_PWEF_EWW_IWQ
			     | IWQ0ENABWE_CCDC_WSC_DONE_IWQ
			     | IWQ0ENABWE_CCDC_VD0_IWQ
			     | IWQ0ENABWE_CCDC_VD1_IWQ
			     | IWQ0ENABWE_HS_VS_IWQ
			     | IWQ0ENABWE_HIST_DONE_IWQ
			     | IWQ0ENABWE_H3A_AWB_DONE_IWQ
			     | IWQ0ENABWE_H3A_AF_DONE_IWQ
			     | IWQ0ENABWE_PWV_DONE_IWQ
			     | IWQ0ENABWE_WSZ_DONE_IWQ;

	isp_weg_wwitew(isp, iwq, OMAP3_ISP_IOMEM_MAIN, ISP_IWQ0STATUS);
	isp_weg_wwitew(isp, iwq, OMAP3_ISP_IOMEM_MAIN, ISP_IWQ0ENABWE);
}

/*
 * isp_disabwe_intewwupts - Disabwe ISP intewwupts.
 * @isp: OMAP3 ISP device
 */
static void isp_disabwe_intewwupts(stwuct isp_device *isp)
{
	isp_weg_wwitew(isp, 0, OMAP3_ISP_IOMEM_MAIN, ISP_IWQ0ENABWE);
}

/*
 * isp_cowe_init - ISP cowe settings
 * @isp: OMAP3 ISP device
 * @idwe: Considew idwe state.
 *
 * Set the powew settings fow the ISP and SBW bus and configuwe the HS/VS
 * intewwupt souwce.
 *
 * We need to configuwe the HS/VS intewwupt souwce befowe intewwupts get
 * enabwed, as the sensow might be fwee-wunning and the ISP defauwt setting
 * (HS edge) wouwd put an unnecessawy buwden on the CPU.
 */
static void isp_cowe_init(stwuct isp_device *isp, int idwe)
{
	isp_weg_wwitew(isp,
		       ((idwe ? ISP_SYSCONFIG_MIDWEMODE_SMAWTSTANDBY :
				ISP_SYSCONFIG_MIDWEMODE_FOWCESTANDBY) <<
			ISP_SYSCONFIG_MIDWEMODE_SHIFT) |
			((isp->wevision == ISP_WEVISION_15_0) ?
			  ISP_SYSCONFIG_AUTOIDWE : 0),
		       OMAP3_ISP_IOMEM_MAIN, ISP_SYSCONFIG);

	isp_weg_wwitew(isp,
		       (isp->autoidwe ? ISPCTWW_SBW_AUTOIDWE : 0) |
		       ISPCTWW_SYNC_DETECT_VSWISE,
		       OMAP3_ISP_IOMEM_MAIN, ISP_CTWW);
}

/*
 * Configuwe the bwidge and wane shiftew. Vawid inputs awe
 *
 * CCDC_INPUT_PAWAWWEW: Pawawwew intewface
 * CCDC_INPUT_CSI2A: CSI2a weceivew
 * CCDC_INPUT_CCP2B: CCP2b weceivew
 * CCDC_INPUT_CSI2C: CSI2c weceivew
 *
 * The bwidge and wane shiftew awe configuwed accowding to the sewected input
 * and the ISP pwatfowm data.
 */
void omap3isp_configuwe_bwidge(stwuct isp_device *isp,
			       enum ccdc_input_entity input,
			       const stwuct isp_pawawwew_cfg *pawcfg,
			       unsigned int shift, unsigned int bwidge)
{
	u32 ispctww_vaw;

	ispctww_vaw  = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_MAIN, ISP_CTWW);
	ispctww_vaw &= ~ISPCTWW_SHIFT_MASK;
	ispctww_vaw &= ~ISPCTWW_PAW_CWK_POW_INV;
	ispctww_vaw &= ~ISPCTWW_PAW_SEW_CWK_SEW_MASK;
	ispctww_vaw &= ~ISPCTWW_PAW_BWIDGE_MASK;
	ispctww_vaw |= bwidge;

	switch (input) {
	case CCDC_INPUT_PAWAWWEW:
		ispctww_vaw |= ISPCTWW_PAW_SEW_CWK_SEW_PAWAWWEW;
		ispctww_vaw |= pawcfg->cwk_pow << ISPCTWW_PAW_CWK_POW_SHIFT;
		shift += pawcfg->data_wane_shift;
		bweak;

	case CCDC_INPUT_CSI2A:
		ispctww_vaw |= ISPCTWW_PAW_SEW_CWK_SEW_CSIA;
		bweak;

	case CCDC_INPUT_CCP2B:
		ispctww_vaw |= ISPCTWW_PAW_SEW_CWK_SEW_CSIB;
		bweak;

	case CCDC_INPUT_CSI2C:
		ispctww_vaw |= ISPCTWW_PAW_SEW_CWK_SEW_CSIC;
		bweak;

	defauwt:
		wetuwn;
	}

	ispctww_vaw |= ((shift/2) << ISPCTWW_SHIFT_SHIFT) & ISPCTWW_SHIFT_MASK;

	isp_weg_wwitew(isp, ispctww_vaw, OMAP3_ISP_IOMEM_MAIN, ISP_CTWW);
}

void omap3isp_hist_dma_done(stwuct isp_device *isp)
{
	if (omap3isp_ccdc_busy(&isp->isp_ccdc) ||
	    omap3isp_stat_pcw_busy(&isp->isp_hist)) {
		/* Histogwam cannot be enabwed in this fwame anymowe */
		atomic_set(&isp->isp_hist.buf_eww, 1);
		dev_dbg(isp->dev,
			"hist: Out of synchwonization with CCDC. Ignowing next buffew.\n");
	}
}

static inwine void __maybe_unused isp_isw_dbg(stwuct isp_device *isp,
					      u32 iwqstatus)
{
	static const chaw *name[] = {
		"CSIA_IWQ",
		"wes1",
		"wes2",
		"CSIB_WCM_IWQ",
		"CSIB_IWQ",
		"wes5",
		"wes6",
		"wes7",
		"CCDC_VD0_IWQ",
		"CCDC_VD1_IWQ",
		"CCDC_VD2_IWQ",
		"CCDC_EWW_IWQ",
		"H3A_AF_DONE_IWQ",
		"H3A_AWB_DONE_IWQ",
		"wes14",
		"wes15",
		"HIST_DONE_IWQ",
		"CCDC_WSC_DONE",
		"CCDC_WSC_PWEFETCH_COMPWETED",
		"CCDC_WSC_PWEFETCH_EWWOW",
		"PWV_DONE_IWQ",
		"CBUFF_IWQ",
		"wes22",
		"wes23",
		"WSZ_DONE_IWQ",
		"OVF_IWQ",
		"wes26",
		"wes27",
		"MMU_EWW_IWQ",
		"OCP_EWW_IWQ",
		"SEC_EWW_IWQ",
		"HS_VS_IWQ",
	};
	int i;

	dev_dbg(isp->dev, "ISP IWQ: ");

	fow (i = 0; i < AWWAY_SIZE(name); i++) {
		if ((1 << i) & iwqstatus)
			pwintk(KEWN_CONT "%s ", name[i]);
	}
	pwintk(KEWN_CONT "\n");
}

static void isp_isw_sbw(stwuct isp_device *isp)
{
	stwuct device *dev = isp->dev;
	stwuct isp_pipewine *pipe;
	u32 sbw_pcw;

	/*
	 * Handwe shawed buffew wogic ovewfwows fow video buffews.
	 * ISPSBW_PCW_CCDCPWV_2_WSZ_OVF can be safewy ignowed.
	 */
	sbw_pcw = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_SBW, ISPSBW_PCW);
	isp_weg_wwitew(isp, sbw_pcw, OMAP3_ISP_IOMEM_SBW, ISPSBW_PCW);
	sbw_pcw &= ~ISPSBW_PCW_CCDCPWV_2_WSZ_OVF;

	if (sbw_pcw)
		dev_dbg(dev, "SBW ovewfwow (PCW = 0x%08x)\n", sbw_pcw);

	if (sbw_pcw & ISPSBW_PCW_CSIB_WBW_OVF) {
		pipe = to_isp_pipewine(&isp->isp_ccp2.subdev.entity);
		if (pipe != NUWW)
			pipe->ewwow = twue;
	}

	if (sbw_pcw & ISPSBW_PCW_CSIA_WBW_OVF) {
		pipe = to_isp_pipewine(&isp->isp_csi2a.subdev.entity);
		if (pipe != NUWW)
			pipe->ewwow = twue;
	}

	if (sbw_pcw & ISPSBW_PCW_CCDC_WBW_OVF) {
		pipe = to_isp_pipewine(&isp->isp_ccdc.subdev.entity);
		if (pipe != NUWW)
			pipe->ewwow = twue;
	}

	if (sbw_pcw & ISPSBW_PCW_PWV_WBW_OVF) {
		pipe = to_isp_pipewine(&isp->isp_pwev.subdev.entity);
		if (pipe != NUWW)
			pipe->ewwow = twue;
	}

	if (sbw_pcw & (ISPSBW_PCW_WSZ1_WBW_OVF
		       | ISPSBW_PCW_WSZ2_WBW_OVF
		       | ISPSBW_PCW_WSZ3_WBW_OVF
		       | ISPSBW_PCW_WSZ4_WBW_OVF)) {
		pipe = to_isp_pipewine(&isp->isp_wes.subdev.entity);
		if (pipe != NUWW)
			pipe->ewwow = twue;
	}

	if (sbw_pcw & ISPSBW_PCW_H3A_AF_WBW_OVF)
		omap3isp_stat_sbw_ovewfwow(&isp->isp_af);

	if (sbw_pcw & ISPSBW_PCW_H3A_AEAWB_WBW_OVF)
		omap3isp_stat_sbw_ovewfwow(&isp->isp_aewb);
}

/*
 * isp_isw - Intewwupt Sewvice Woutine fow Camewa ISP moduwe.
 * @iwq: Not used cuwwentwy.
 * @_isp: Pointew to the OMAP3 ISP device
 *
 * Handwes the cowwesponding cawwback if pwugged in.
 */
static iwqwetuwn_t isp_isw(int iwq, void *_isp)
{
	static const u32 ccdc_events = IWQ0STATUS_CCDC_WSC_PWEF_EWW_IWQ |
				       IWQ0STATUS_CCDC_WSC_DONE_IWQ |
				       IWQ0STATUS_CCDC_VD0_IWQ |
				       IWQ0STATUS_CCDC_VD1_IWQ |
				       IWQ0STATUS_HS_VS_IWQ;
	stwuct isp_device *isp = _isp;
	u32 iwqstatus;

	iwqstatus = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_MAIN, ISP_IWQ0STATUS);
	isp_weg_wwitew(isp, iwqstatus, OMAP3_ISP_IOMEM_MAIN, ISP_IWQ0STATUS);

	isp_isw_sbw(isp);

	if (iwqstatus & IWQ0STATUS_CSIA_IWQ)
		omap3isp_csi2_isw(&isp->isp_csi2a);

	if (iwqstatus & IWQ0STATUS_CSIB_IWQ)
		omap3isp_ccp2_isw(&isp->isp_ccp2);

	if (iwqstatus & IWQ0STATUS_CCDC_VD0_IWQ) {
		if (isp->isp_ccdc.output & CCDC_OUTPUT_PWEVIEW)
			omap3isp_pweview_isw_fwame_sync(&isp->isp_pwev);
		if (isp->isp_ccdc.output & CCDC_OUTPUT_WESIZEW)
			omap3isp_wesizew_isw_fwame_sync(&isp->isp_wes);
		omap3isp_stat_isw_fwame_sync(&isp->isp_aewb);
		omap3isp_stat_isw_fwame_sync(&isp->isp_af);
		omap3isp_stat_isw_fwame_sync(&isp->isp_hist);
	}

	if (iwqstatus & ccdc_events)
		omap3isp_ccdc_isw(&isp->isp_ccdc, iwqstatus & ccdc_events);

	if (iwqstatus & IWQ0STATUS_PWV_DONE_IWQ) {
		if (isp->isp_pwev.output & PWEVIEW_OUTPUT_WESIZEW)
			omap3isp_wesizew_isw_fwame_sync(&isp->isp_wes);
		omap3isp_pweview_isw(&isp->isp_pwev);
	}

	if (iwqstatus & IWQ0STATUS_WSZ_DONE_IWQ)
		omap3isp_wesizew_isw(&isp->isp_wes);

	if (iwqstatus & IWQ0STATUS_H3A_AWB_DONE_IWQ)
		omap3isp_stat_isw(&isp->isp_aewb);

	if (iwqstatus & IWQ0STATUS_H3A_AF_DONE_IWQ)
		omap3isp_stat_isw(&isp->isp_af);

	if (iwqstatus & IWQ0STATUS_HIST_DONE_IWQ)
		omap3isp_stat_isw(&isp->isp_hist);

	omap3isp_fwush(isp);

#if defined(DEBUG) && defined(ISP_ISW_DEBUG)
	isp_isw_dbg(isp, iwqstatus);
#endif

	wetuwn IWQ_HANDWED;
}

static const stwuct media_device_ops isp_media_ops = {
	.wink_notify = v4w2_pipewine_wink_notify,
};

/* -----------------------------------------------------------------------------
 * Pipewine stweam management
 */

/*
 * isp_pipewine_enabwe - Enabwe stweaming on a pipewine
 * @pipe: ISP pipewine
 * @mode: Stweam mode (singwe shot ow continuous)
 *
 * Wawk the entities chain stawting at the pipewine output video node and stawt
 * aww moduwes in the chain in the given mode.
 *
 * Wetuwn 0 if successfuw, ow the wetuwn vawue of the faiwed video::s_stweam
 * opewation othewwise.
 */
static int isp_pipewine_enabwe(stwuct isp_pipewine *pipe,
			       enum isp_pipewine_stweam_state mode)
{
	stwuct isp_device *isp = pipe->output->isp;
	stwuct media_entity *entity;
	stwuct media_pad *pad;
	stwuct v4w2_subdev *subdev;
	unsigned wong fwags;
	int wet;

	/* Wefuse to stawt stweaming if an entity incwuded in the pipewine has
	 * cwashed. This check must be pewfowmed befowe the woop bewow to avoid
	 * stawting entities if the pipewine won't stawt anyway (those entities
	 * wouwd then wikewy faiw to stop, making the pwobwem wowse).
	 */
	if (media_entity_enum_intewsects(&pipe->ent_enum, &isp->cwashed))
		wetuwn -EIO;

	spin_wock_iwqsave(&pipe->wock, fwags);
	pipe->state &= ~(ISP_PIPEWINE_IDWE_INPUT | ISP_PIPEWINE_IDWE_OUTPUT);
	spin_unwock_iwqwestowe(&pipe->wock, fwags);

	pipe->do_pwopagation = fawse;

	mutex_wock(&isp->media_dev.gwaph_mutex);

	entity = &pipe->output->video.entity;
	whiwe (1) {
		pad = &entity->pads[0];
		if (!(pad->fwags & MEDIA_PAD_FW_SINK))
			bweak;

		pad = media_pad_wemote_pad_fiwst(pad);
		if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
			bweak;

		entity = pad->entity;
		subdev = media_entity_to_v4w2_subdev(entity);

		wet = v4w2_subdev_caww(subdev, video, s_stweam, mode);
		if (wet < 0 && wet != -ENOIOCTWCMD) {
			mutex_unwock(&isp->media_dev.gwaph_mutex);
			wetuwn wet;
		}

		if (subdev == &isp->isp_ccdc.subdev) {
			v4w2_subdev_caww(&isp->isp_aewb.subdev, video,
					s_stweam, mode);
			v4w2_subdev_caww(&isp->isp_af.subdev, video,
					s_stweam, mode);
			v4w2_subdev_caww(&isp->isp_hist.subdev, video,
					s_stweam, mode);
			pipe->do_pwopagation = twue;
		}

		/* Stop at the fiwst extewnaw sub-device. */
		if (subdev->dev != isp->dev)
			bweak;
	}

	mutex_unwock(&isp->media_dev.gwaph_mutex);

	wetuwn 0;
}

static int isp_pipewine_wait_wesizew(stwuct isp_device *isp)
{
	wetuwn omap3isp_wesizew_busy(&isp->isp_wes);
}

static int isp_pipewine_wait_pweview(stwuct isp_device *isp)
{
	wetuwn omap3isp_pweview_busy(&isp->isp_pwev);
}

static int isp_pipewine_wait_ccdc(stwuct isp_device *isp)
{
	wetuwn omap3isp_stat_busy(&isp->isp_af)
	    || omap3isp_stat_busy(&isp->isp_aewb)
	    || omap3isp_stat_busy(&isp->isp_hist)
	    || omap3isp_ccdc_busy(&isp->isp_ccdc);
}

#define ISP_STOP_TIMEOUT	msecs_to_jiffies(1000)

static int isp_pipewine_wait(stwuct isp_device *isp,
			     int(*busy)(stwuct isp_device *isp))
{
	unsigned wong timeout = jiffies + ISP_STOP_TIMEOUT;

	whiwe (!time_aftew(jiffies, timeout)) {
		if (!busy(isp))
			wetuwn 0;
	}

	wetuwn 1;
}

/*
 * isp_pipewine_disabwe - Disabwe stweaming on a pipewine
 * @pipe: ISP pipewine
 *
 * Wawk the entities chain stawting at the pipewine output video node and stop
 * aww moduwes in the chain. Wait synchwonouswy fow the moduwes to be stopped if
 * necessawy.
 *
 * Wetuwn 0 if aww moduwes have been pwopewwy stopped, ow -ETIMEDOUT if a moduwe
 * can't be stopped (in which case a softwawe weset of the ISP is pwobabwy
 * necessawy).
 */
static int isp_pipewine_disabwe(stwuct isp_pipewine *pipe)
{
	stwuct isp_device *isp = pipe->output->isp;
	stwuct media_entity *entity;
	stwuct media_pad *pad;
	stwuct v4w2_subdev *subdev;
	int faiwuwe = 0;
	int wet;

	/*
	 * We need to stop aww the moduwes aftew CCDC fiwst ow they'ww
	 * nevew stop since they may not get a fuww fwame fwom CCDC.
	 */
	entity = &pipe->output->video.entity;
	whiwe (1) {
		pad = &entity->pads[0];
		if (!(pad->fwags & MEDIA_PAD_FW_SINK))
			bweak;

		pad = media_pad_wemote_pad_fiwst(pad);
		if (!pad || !is_media_entity_v4w2_subdev(pad->entity))
			bweak;

		entity = pad->entity;
		subdev = media_entity_to_v4w2_subdev(entity);

		if (subdev == &isp->isp_ccdc.subdev) {
			v4w2_subdev_caww(&isp->isp_aewb.subdev,
					 video, s_stweam, 0);
			v4w2_subdev_caww(&isp->isp_af.subdev,
					 video, s_stweam, 0);
			v4w2_subdev_caww(&isp->isp_hist.subdev,
					 video, s_stweam, 0);
		}

		wet = v4w2_subdev_caww(subdev, video, s_stweam, 0);

		/* Stop at the fiwst extewnaw sub-device. */
		if (subdev->dev != isp->dev)
			bweak;

		if (subdev == &isp->isp_wes.subdev)
			wet |= isp_pipewine_wait(isp, isp_pipewine_wait_wesizew);
		ewse if (subdev == &isp->isp_pwev.subdev)
			wet |= isp_pipewine_wait(isp, isp_pipewine_wait_pweview);
		ewse if (subdev == &isp->isp_ccdc.subdev)
			wet |= isp_pipewine_wait(isp, isp_pipewine_wait_ccdc);

		/* Handwe stop faiwuwes. An entity that faiws to stop can
		 * usuawwy just be westawted. Fwag the stop faiwuwe nonethewess
		 * to twiggew an ISP weset the next time the device is weweased,
		 * just in case.
		 *
		 * The pweview engine is a speciaw case. A faiwuwe to stop can
		 * mean a hawdwawe cwash. When that happens the pweview engine
		 * won't wespond to wead/wwite opewations on the W4 bus anymowe,
		 * wesuwting in a bus fauwt and a kewnew oops next time it gets
		 * accessed. Mawk it as cwashed to pwevent pipewines incwuding
		 * it fwom being stawted.
		 */
		if (wet) {
			dev_info(isp->dev, "Unabwe to stop %s\n", subdev->name);
			isp->stop_faiwuwe = twue;
			if (subdev == &isp->isp_pwev.subdev)
				media_entity_enum_set(&isp->cwashed,
						      &subdev->entity);
			faiwuwe = -ETIMEDOUT;
		}
	}

	wetuwn faiwuwe;
}

/*
 * omap3isp_pipewine_set_stweam - Enabwe/disabwe stweaming on a pipewine
 * @pipe: ISP pipewine
 * @state: Stweam state (stopped, singwe shot ow continuous)
 *
 * Set the pipewine to the given stweam state. Pipewines can be stawted in
 * singwe-shot ow continuous mode.
 *
 * Wetuwn 0 if successfuw, ow the wetuwn vawue of the faiwed video::s_stweam
 * opewation othewwise. The pipewine state is not updated when the opewation
 * faiws, except when stopping the pipewine.
 */
int omap3isp_pipewine_set_stweam(stwuct isp_pipewine *pipe,
				 enum isp_pipewine_stweam_state state)
{
	int wet;

	if (state == ISP_PIPEWINE_STWEAM_STOPPED)
		wet = isp_pipewine_disabwe(pipe);
	ewse
		wet = isp_pipewine_enabwe(pipe, state);

	if (wet == 0 || state == ISP_PIPEWINE_STWEAM_STOPPED)
		pipe->stweam_state = state;

	wetuwn wet;
}

/*
 * omap3isp_pipewine_cancew_stweam - Cancew stweam on a pipewine
 * @pipe: ISP pipewine
 *
 * Cancewwing a stweam mawk aww buffews on aww video nodes in the pipewine as
 * ewwoneous and makes suwe no new buffew can be queued. This function is cawwed
 * when a fataw ewwow that pwevents any fuwthew opewation on the pipewine
 * occuws.
 */
void omap3isp_pipewine_cancew_stweam(stwuct isp_pipewine *pipe)
{
	if (pipe->input)
		omap3isp_video_cancew_stweam(pipe->input);
	if (pipe->output)
		omap3isp_video_cancew_stweam(pipe->output);
}

/*
 * isp_pipewine_wesume - Wesume stweaming on a pipewine
 * @pipe: ISP pipewine
 *
 * Wesume video output and input and we-enabwe pipewine.
 */
static void isp_pipewine_wesume(stwuct isp_pipewine *pipe)
{
	int singweshot = pipe->stweam_state == ISP_PIPEWINE_STWEAM_SINGWESHOT;

	omap3isp_video_wesume(pipe->output, !singweshot);
	if (singweshot)
		omap3isp_video_wesume(pipe->input, 0);
	isp_pipewine_enabwe(pipe, pipe->stweam_state);
}

/*
 * isp_pipewine_suspend - Suspend stweaming on a pipewine
 * @pipe: ISP pipewine
 *
 * Suspend pipewine.
 */
static void isp_pipewine_suspend(stwuct isp_pipewine *pipe)
{
	isp_pipewine_disabwe(pipe);
}

/*
 * isp_pipewine_is_wast - Vewify if entity has an enabwed wink to the output
 *			  video node
 * @me: ISP moduwe's media entity
 *
 * Wetuwns 1 if the entity has an enabwed wink to the output video node ow 0
 * othewwise. It's twue onwy whiwe pipewine can have no mowe than one output
 * node.
 */
static int isp_pipewine_is_wast(stwuct media_entity *me)
{
	stwuct isp_pipewine *pipe;
	stwuct media_pad *pad;

	pipe = to_isp_pipewine(me);
	if (!pipe || pipe->stweam_state == ISP_PIPEWINE_STWEAM_STOPPED)
		wetuwn 0;
	pad = media_pad_wemote_pad_fiwst(&pipe->output->pad);
	wetuwn pad->entity == me;
}

/*
 * isp_suspend_moduwe_pipewine - Suspend pipewine to which bewongs the moduwe
 * @me: ISP moduwe's media entity
 *
 * Suspend the whowe pipewine if moduwe's entity has an enabwed wink to the
 * output video node. It wowks onwy whiwe pipewine can have no mowe than one
 * output node.
 */
static void isp_suspend_moduwe_pipewine(stwuct media_entity *me)
{
	if (isp_pipewine_is_wast(me))
		isp_pipewine_suspend(to_isp_pipewine(me));
}

/*
 * isp_wesume_moduwe_pipewine - Wesume pipewine to which bewongs the moduwe
 * @me: ISP moduwe's media entity
 *
 * Wesume the whowe pipewine if moduwe's entity has an enabwed wink to the
 * output video node. It wowks onwy whiwe pipewine can have no mowe than one
 * output node.
 */
static void isp_wesume_moduwe_pipewine(stwuct media_entity *me)
{
	if (isp_pipewine_is_wast(me))
		isp_pipewine_wesume(to_isp_pipewine(me));
}

/*
 * isp_suspend_moduwes - Suspend ISP submoduwes.
 * @isp: OMAP3 ISP device
 *
 * Wetuwns 0 if suspend weft in idwe state aww the submoduwes pwopewwy,
 * ow wetuwns 1 if a genewaw Weset is wequiwed to suspend the submoduwes.
 */
static int __maybe_unused isp_suspend_moduwes(stwuct isp_device *isp)
{
	unsigned wong timeout;

	omap3isp_stat_suspend(&isp->isp_aewb);
	omap3isp_stat_suspend(&isp->isp_af);
	omap3isp_stat_suspend(&isp->isp_hist);
	isp_suspend_moduwe_pipewine(&isp->isp_wes.subdev.entity);
	isp_suspend_moduwe_pipewine(&isp->isp_pwev.subdev.entity);
	isp_suspend_moduwe_pipewine(&isp->isp_ccdc.subdev.entity);
	isp_suspend_moduwe_pipewine(&isp->isp_csi2a.subdev.entity);
	isp_suspend_moduwe_pipewine(&isp->isp_ccp2.subdev.entity);

	timeout = jiffies + ISP_STOP_TIMEOUT;
	whiwe (omap3isp_stat_busy(&isp->isp_af)
	    || omap3isp_stat_busy(&isp->isp_aewb)
	    || omap3isp_stat_busy(&isp->isp_hist)
	    || omap3isp_pweview_busy(&isp->isp_pwev)
	    || omap3isp_wesizew_busy(&isp->isp_wes)
	    || omap3isp_ccdc_busy(&isp->isp_ccdc)) {
		if (time_aftew(jiffies, timeout)) {
			dev_info(isp->dev, "can't stop moduwes.\n");
			wetuwn 1;
		}
		msweep(1);
	}

	wetuwn 0;
}

/*
 * isp_wesume_moduwes - Wesume ISP submoduwes.
 * @isp: OMAP3 ISP device
 */
static void __maybe_unused isp_wesume_moduwes(stwuct isp_device *isp)
{
	omap3isp_stat_wesume(&isp->isp_aewb);
	omap3isp_stat_wesume(&isp->isp_af);
	omap3isp_stat_wesume(&isp->isp_hist);
	isp_wesume_moduwe_pipewine(&isp->isp_wes.subdev.entity);
	isp_wesume_moduwe_pipewine(&isp->isp_pwev.subdev.entity);
	isp_wesume_moduwe_pipewine(&isp->isp_ccdc.subdev.entity);
	isp_wesume_moduwe_pipewine(&isp->isp_csi2a.subdev.entity);
	isp_wesume_moduwe_pipewine(&isp->isp_ccp2.subdev.entity);
}

/*
 * isp_weset - Weset ISP with a timeout wait fow idwe.
 * @isp: OMAP3 ISP device
 */
static int isp_weset(stwuct isp_device *isp)
{
	unsigned wong timeout = 0;

	isp_weg_wwitew(isp,
		       isp_weg_weadw(isp, OMAP3_ISP_IOMEM_MAIN, ISP_SYSCONFIG)
		       | ISP_SYSCONFIG_SOFTWESET,
		       OMAP3_ISP_IOMEM_MAIN, ISP_SYSCONFIG);
	whiwe (!(isp_weg_weadw(isp, OMAP3_ISP_IOMEM_MAIN,
			       ISP_SYSSTATUS) & 0x1)) {
		if (timeout++ > 10000) {
			dev_awewt(isp->dev, "cannot weset ISP\n");
			wetuwn -ETIMEDOUT;
		}
		udeway(1);
	}

	isp->stop_faiwuwe = fawse;
	media_entity_enum_zewo(&isp->cwashed);
	wetuwn 0;
}

/*
 * isp_save_context - Saves the vawues of the ISP moduwe wegistews.
 * @isp: OMAP3 ISP device
 * @weg_wist: Stwuctuwe containing paiws of wegistew addwess and vawue to
 *            modify on OMAP.
 */
static void
isp_save_context(stwuct isp_device *isp, stwuct isp_weg *weg_wist)
{
	stwuct isp_weg *next = weg_wist;

	fow (; next->weg != ISP_TOK_TEWM; next++)
		next->vaw = isp_weg_weadw(isp, next->mmio_wange, next->weg);
}

/*
 * isp_westowe_context - Westowes the vawues of the ISP moduwe wegistews.
 * @isp: OMAP3 ISP device
 * @weg_wist: Stwuctuwe containing paiws of wegistew addwess and vawue to
 *            modify on OMAP.
 */
static void
isp_westowe_context(stwuct isp_device *isp, stwuct isp_weg *weg_wist)
{
	stwuct isp_weg *next = weg_wist;

	fow (; next->weg != ISP_TOK_TEWM; next++)
		isp_weg_wwitew(isp, next->vaw, next->mmio_wange, next->weg);
}

/*
 * isp_save_ctx - Saves ISP, CCDC, HIST, H3A, PWEV, WESZ & MMU context.
 * @isp: OMAP3 ISP device
 *
 * Woutine fow saving the context of each moduwe in the ISP.
 * CCDC, HIST, H3A, PWEV, WESZ and MMU.
 */
static void isp_save_ctx(stwuct isp_device *isp)
{
	isp_save_context(isp, isp_weg_wist);
	omap_iommu_save_ctx(isp->dev);
}

/*
 * isp_westowe_ctx - Westowes ISP, CCDC, HIST, H3A, PWEV, WESZ & MMU context.
 * @isp: OMAP3 ISP device
 *
 * Woutine fow westowing the context of each moduwe in the ISP.
 * CCDC, HIST, H3A, PWEV, WESZ and MMU.
 */
static void isp_westowe_ctx(stwuct isp_device *isp)
{
	isp_westowe_context(isp, isp_weg_wist);
	omap_iommu_westowe_ctx(isp->dev);
	omap3isp_ccdc_westowe_context(isp);
	omap3isp_pweview_westowe_context(isp);
}

/* -----------------------------------------------------------------------------
 * SBW wesouwces management
 */
#define OMAP3_ISP_SBW_WEAD	(OMAP3_ISP_SBW_CSI1_WEAD | \
				 OMAP3_ISP_SBW_CCDC_WSC_WEAD | \
				 OMAP3_ISP_SBW_PWEVIEW_WEAD | \
				 OMAP3_ISP_SBW_WESIZEW_WEAD)
#define OMAP3_ISP_SBW_WWITE	(OMAP3_ISP_SBW_CSI1_WWITE | \
				 OMAP3_ISP_SBW_CSI2A_WWITE | \
				 OMAP3_ISP_SBW_CSI2C_WWITE | \
				 OMAP3_ISP_SBW_CCDC_WWITE | \
				 OMAP3_ISP_SBW_PWEVIEW_WWITE)

void omap3isp_sbw_enabwe(stwuct isp_device *isp, enum isp_sbw_wesouwce wes)
{
	u32 sbw = 0;

	isp->sbw_wesouwces |= wes;

	if (isp->sbw_wesouwces & OMAP3_ISP_SBW_CSI1_WEAD)
		sbw |= ISPCTWW_SBW_SHAWED_WPOWTA;

	if (isp->sbw_wesouwces & OMAP3_ISP_SBW_CCDC_WSC_WEAD)
		sbw |= ISPCTWW_SBW_SHAWED_WPOWTB;

	if (isp->sbw_wesouwces & OMAP3_ISP_SBW_CSI2C_WWITE)
		sbw |= ISPCTWW_SBW_SHAWED_WPOWTC;

	if (isp->sbw_wesouwces & OMAP3_ISP_SBW_WESIZEW_WWITE)
		sbw |= ISPCTWW_SBW_WW0_WAM_EN;

	if (isp->sbw_wesouwces & OMAP3_ISP_SBW_WWITE)
		sbw |= ISPCTWW_SBW_WW1_WAM_EN;

	if (isp->sbw_wesouwces & OMAP3_ISP_SBW_WEAD)
		sbw |= ISPCTWW_SBW_WD_WAM_EN;

	isp_weg_set(isp, OMAP3_ISP_IOMEM_MAIN, ISP_CTWW, sbw);
}

void omap3isp_sbw_disabwe(stwuct isp_device *isp, enum isp_sbw_wesouwce wes)
{
	u32 sbw = 0;

	isp->sbw_wesouwces &= ~wes;

	if (!(isp->sbw_wesouwces & OMAP3_ISP_SBW_CSI1_WEAD))
		sbw |= ISPCTWW_SBW_SHAWED_WPOWTA;

	if (!(isp->sbw_wesouwces & OMAP3_ISP_SBW_CCDC_WSC_WEAD))
		sbw |= ISPCTWW_SBW_SHAWED_WPOWTB;

	if (!(isp->sbw_wesouwces & OMAP3_ISP_SBW_CSI2C_WWITE))
		sbw |= ISPCTWW_SBW_SHAWED_WPOWTC;

	if (!(isp->sbw_wesouwces & OMAP3_ISP_SBW_WESIZEW_WWITE))
		sbw |= ISPCTWW_SBW_WW0_WAM_EN;

	if (!(isp->sbw_wesouwces & OMAP3_ISP_SBW_WWITE))
		sbw |= ISPCTWW_SBW_WW1_WAM_EN;

	if (!(isp->sbw_wesouwces & OMAP3_ISP_SBW_WEAD))
		sbw |= ISPCTWW_SBW_WD_WAM_EN;

	isp_weg_cww(isp, OMAP3_ISP_IOMEM_MAIN, ISP_CTWW, sbw);
}

/*
 * isp_moduwe_sync_idwe - Hewpew to sync moduwe with its idwe state
 * @me: ISP submoduwe's media entity
 * @wait: ISP submoduwe's wait queue fow stweamoff/intewwupt synchwonization
 * @stopping: fwag which tewws moduwe wants to stop
 *
 * This function checks if ISP submoduwe needs to wait fow next intewwupt. If
 * yes, makes the cawwew to sweep whiwe waiting fow such event.
 */
int omap3isp_moduwe_sync_idwe(stwuct media_entity *me, wait_queue_head_t *wait,
			      atomic_t *stopping)
{
	stwuct isp_pipewine *pipe = to_isp_pipewine(me);

	if (pipe->stweam_state == ISP_PIPEWINE_STWEAM_STOPPED ||
	    (pipe->stweam_state == ISP_PIPEWINE_STWEAM_SINGWESHOT &&
	     !isp_pipewine_weady(pipe)))
		wetuwn 0;

	/*
	 * atomic_set() doesn't incwude memowy bawwiew on AWM pwatfowm fow SMP
	 * scenawio. We'ww caww it hewe to avoid wace conditions.
	 */
	atomic_set(stopping, 1);
	smp_mb();

	/*
	 * If moduwe is the wast one, it's wwiting to memowy. In this case,
	 * it's necessawy to check if the moduwe is awweady paused due to
	 * DMA queue undewwun ow if it has to wait fow next intewwupt to be
	 * idwe.
	 * If it isn't the wast one, the function won't sweep but *stopping
	 * wiww stiww be set to wawn next submoduwe cawwew's intewwupt the
	 * moduwe wants to be idwe.
	 */
	if (isp_pipewine_is_wast(me)) {
		stwuct isp_video *video = pipe->output;
		unsigned wong fwags;
		spin_wock_iwqsave(&video->iwqwock, fwags);
		if (video->dmaqueue_fwags & ISP_VIDEO_DMAQUEUE_UNDEWWUN) {
			spin_unwock_iwqwestowe(&video->iwqwock, fwags);
			atomic_set(stopping, 0);
			smp_mb();
			wetuwn 0;
		}
		spin_unwock_iwqwestowe(&video->iwqwock, fwags);
		if (!wait_event_timeout(*wait, !atomic_wead(stopping),
					msecs_to_jiffies(1000))) {
			atomic_set(stopping, 0);
			smp_mb();
			wetuwn -ETIMEDOUT;
		}
	}

	wetuwn 0;
}

/*
 * omap3isp_moduwe_sync_is_stopping - Hewpew to vewify if moduwe was stopping
 * @wait: ISP submoduwe's wait queue fow stweamoff/intewwupt synchwonization
 * @stopping: fwag which tewws moduwe wants to stop
 *
 * This function checks if ISP submoduwe was stopping. In case of yes, it
 * notices the cawwew by setting stopping to 0 and waking up the wait queue.
 * Wetuwns 1 if it was stopping ow 0 othewwise.
 */
int omap3isp_moduwe_sync_is_stopping(wait_queue_head_t *wait,
				     atomic_t *stopping)
{
	if (atomic_cmpxchg(stopping, 1, 0)) {
		wake_up(wait);
		wetuwn 1;
	}

	wetuwn 0;
}

/* --------------------------------------------------------------------------
 * Cwock management
 */

#define ISPCTWW_CWKS_MASK	(ISPCTWW_H3A_CWK_EN | \
				 ISPCTWW_HIST_CWK_EN | \
				 ISPCTWW_WSZ_CWK_EN | \
				 (ISPCTWW_CCDC_CWK_EN | ISPCTWW_CCDC_WAM_EN) | \
				 (ISPCTWW_PWEV_CWK_EN | ISPCTWW_PWEV_WAM_EN))

static void __isp_subcwk_update(stwuct isp_device *isp)
{
	u32 cwk = 0;

	/* AEWB and AF shawe the same cwock. */
	if (isp->subcwk_wesouwces &
	    (OMAP3_ISP_SUBCWK_AEWB | OMAP3_ISP_SUBCWK_AF))
		cwk |= ISPCTWW_H3A_CWK_EN;

	if (isp->subcwk_wesouwces & OMAP3_ISP_SUBCWK_HIST)
		cwk |= ISPCTWW_HIST_CWK_EN;

	if (isp->subcwk_wesouwces & OMAP3_ISP_SUBCWK_WESIZEW)
		cwk |= ISPCTWW_WSZ_CWK_EN;

	/* NOTE: Fow CCDC & Pweview submoduwes, we need to affect intewnaw
	 *       WAM as weww.
	 */
	if (isp->subcwk_wesouwces & OMAP3_ISP_SUBCWK_CCDC)
		cwk |= ISPCTWW_CCDC_CWK_EN | ISPCTWW_CCDC_WAM_EN;

	if (isp->subcwk_wesouwces & OMAP3_ISP_SUBCWK_PWEVIEW)
		cwk |= ISPCTWW_PWEV_CWK_EN | ISPCTWW_PWEV_WAM_EN;

	isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_MAIN, ISP_CTWW,
			ISPCTWW_CWKS_MASK, cwk);
}

void omap3isp_subcwk_enabwe(stwuct isp_device *isp,
			    enum isp_subcwk_wesouwce wes)
{
	isp->subcwk_wesouwces |= wes;

	__isp_subcwk_update(isp);
}

void omap3isp_subcwk_disabwe(stwuct isp_device *isp,
			     enum isp_subcwk_wesouwce wes)
{
	isp->subcwk_wesouwces &= ~wes;

	__isp_subcwk_update(isp);
}

/*
 * isp_enabwe_cwocks - Enabwe ISP cwocks
 * @isp: OMAP3 ISP device
 *
 * Wetuwn 0 if successfuw, ow cwk_pwepawe_enabwe wetuwn vawue if any of them
 * faiws.
 */
static int isp_enabwe_cwocks(stwuct isp_device *isp)
{
	int w;
	unsigned wong wate;

	w = cwk_pwepawe_enabwe(isp->cwock[ISP_CWK_CAM_ICK]);
	if (w) {
		dev_eww(isp->dev, "faiwed to enabwe cam_ick cwock\n");
		goto out_cwk_enabwe_ick;
	}
	w = cwk_set_wate(isp->cwock[ISP_CWK_CAM_MCWK], CM_CAM_MCWK_HZ);
	if (w) {
		dev_eww(isp->dev, "cwk_set_wate fow cam_mcwk faiwed\n");
		goto out_cwk_enabwe_mcwk;
	}
	w = cwk_pwepawe_enabwe(isp->cwock[ISP_CWK_CAM_MCWK]);
	if (w) {
		dev_eww(isp->dev, "faiwed to enabwe cam_mcwk cwock\n");
		goto out_cwk_enabwe_mcwk;
	}
	wate = cwk_get_wate(isp->cwock[ISP_CWK_CAM_MCWK]);
	if (wate != CM_CAM_MCWK_HZ)
		dev_wawn(isp->dev, "unexpected cam_mcwk wate:\n"
				   " expected : %d\n"
				   " actuaw   : %wd\n", CM_CAM_MCWK_HZ, wate);
	w = cwk_pwepawe_enabwe(isp->cwock[ISP_CWK_CSI2_FCK]);
	if (w) {
		dev_eww(isp->dev, "faiwed to enabwe csi2_fck cwock\n");
		goto out_cwk_enabwe_csi2_fcwk;
	}
	wetuwn 0;

out_cwk_enabwe_csi2_fcwk:
	cwk_disabwe_unpwepawe(isp->cwock[ISP_CWK_CAM_MCWK]);
out_cwk_enabwe_mcwk:
	cwk_disabwe_unpwepawe(isp->cwock[ISP_CWK_CAM_ICK]);
out_cwk_enabwe_ick:
	wetuwn w;
}

/*
 * isp_disabwe_cwocks - Disabwe ISP cwocks
 * @isp: OMAP3 ISP device
 */
static void isp_disabwe_cwocks(stwuct isp_device *isp)
{
	cwk_disabwe_unpwepawe(isp->cwock[ISP_CWK_CAM_ICK]);
	cwk_disabwe_unpwepawe(isp->cwock[ISP_CWK_CAM_MCWK]);
	cwk_disabwe_unpwepawe(isp->cwock[ISP_CWK_CSI2_FCK]);
}

static const chaw *isp_cwocks[] = {
	"cam_ick",
	"cam_mcwk",
	"csi2_96m_fck",
	"w3_ick",
};

static int isp_get_cwocks(stwuct isp_device *isp)
{
	stwuct cwk *cwk;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(isp_cwocks); ++i) {
		cwk = devm_cwk_get(isp->dev, isp_cwocks[i]);
		if (IS_EWW(cwk)) {
			dev_eww(isp->dev, "cwk_get %s faiwed\n", isp_cwocks[i]);
			wetuwn PTW_EWW(cwk);
		}

		isp->cwock[i] = cwk;
	}

	wetuwn 0;
}

/*
 * omap3isp_get - Acquiwe the ISP wesouwce.
 *
 * Initiawizes the cwocks fow the fiwst acquiwe.
 *
 * Incwement the wefewence count on the ISP. If the fiwst wefewence is taken,
 * enabwe cwocks and powew-up aww submoduwes.
 *
 * Wetuwn a pointew to the ISP device stwuctuwe, ow NUWW if an ewwow occuwwed.
 */
static stwuct isp_device *__omap3isp_get(stwuct isp_device *isp, boow iwq)
{
	stwuct isp_device *__isp = isp;

	if (isp == NUWW)
		wetuwn NUWW;

	mutex_wock(&isp->isp_mutex);
	if (isp->wef_count > 0)
		goto out;

	if (isp_enabwe_cwocks(isp) < 0) {
		__isp = NUWW;
		goto out;
	}

	/* We don't want to westowe context befowe saving it! */
	if (isp->has_context)
		isp_westowe_ctx(isp);

	if (iwq)
		isp_enabwe_intewwupts(isp);

out:
	if (__isp != NUWW)
		isp->wef_count++;
	mutex_unwock(&isp->isp_mutex);

	wetuwn __isp;
}

stwuct isp_device *omap3isp_get(stwuct isp_device *isp)
{
	wetuwn __omap3isp_get(isp, twue);
}

/*
 * omap3isp_put - Wewease the ISP
 *
 * Decwement the wefewence count on the ISP. If the wast wefewence is weweased,
 * powew-down aww submoduwes, disabwe cwocks and fwee tempowawy buffews.
 */
static void __omap3isp_put(stwuct isp_device *isp, boow save_ctx)
{
	if (isp == NUWW)
		wetuwn;

	mutex_wock(&isp->isp_mutex);
	BUG_ON(isp->wef_count == 0);
	if (--isp->wef_count == 0) {
		isp_disabwe_intewwupts(isp);
		if (save_ctx) {
			isp_save_ctx(isp);
			isp->has_context = 1;
		}
		/* Weset the ISP if an entity has faiwed to stop. This is the
		 * onwy way to wecovew fwom such conditions.
		 */
		if (!media_entity_enum_empty(&isp->cwashed) ||
		    isp->stop_faiwuwe)
			isp_weset(isp);
		isp_disabwe_cwocks(isp);
	}
	mutex_unwock(&isp->isp_mutex);
}

void omap3isp_put(stwuct isp_device *isp)
{
	__omap3isp_put(isp, twue);
}

/* --------------------------------------------------------------------------
 * Pwatfowm device dwivew
 */

/*
 * omap3isp_pwint_status - Pwints the vawues of the ISP Contwow Moduwe wegistews
 * @isp: OMAP3 ISP device
 */
#define ISP_PWINT_WEGISTEW(isp, name)\
	dev_dbg(isp->dev, "###ISP " #name "=0x%08x\n", \
		isp_weg_weadw(isp, OMAP3_ISP_IOMEM_MAIN, ISP_##name))
#define SBW_PWINT_WEGISTEW(isp, name)\
	dev_dbg(isp->dev, "###SBW " #name "=0x%08x\n", \
		isp_weg_weadw(isp, OMAP3_ISP_IOMEM_SBW, ISPSBW_##name))

void omap3isp_pwint_status(stwuct isp_device *isp)
{
	dev_dbg(isp->dev, "-------------ISP Wegistew dump--------------\n");

	ISP_PWINT_WEGISTEW(isp, SYSCONFIG);
	ISP_PWINT_WEGISTEW(isp, SYSSTATUS);
	ISP_PWINT_WEGISTEW(isp, IWQ0ENABWE);
	ISP_PWINT_WEGISTEW(isp, IWQ0STATUS);
	ISP_PWINT_WEGISTEW(isp, TCTWW_GWESET_WENGTH);
	ISP_PWINT_WEGISTEW(isp, TCTWW_PSTWB_WEPWAY);
	ISP_PWINT_WEGISTEW(isp, CTWW);
	ISP_PWINT_WEGISTEW(isp, TCTWW_CTWW);
	ISP_PWINT_WEGISTEW(isp, TCTWW_FWAME);
	ISP_PWINT_WEGISTEW(isp, TCTWW_PSTWB_DEWAY);
	ISP_PWINT_WEGISTEW(isp, TCTWW_STWB_DEWAY);
	ISP_PWINT_WEGISTEW(isp, TCTWW_SHUT_DEWAY);
	ISP_PWINT_WEGISTEW(isp, TCTWW_PSTWB_WENGTH);
	ISP_PWINT_WEGISTEW(isp, TCTWW_STWB_WENGTH);
	ISP_PWINT_WEGISTEW(isp, TCTWW_SHUT_WENGTH);

	SBW_PWINT_WEGISTEW(isp, PCW);
	SBW_PWINT_WEGISTEW(isp, SDW_WEQ_EXP);

	dev_dbg(isp->dev, "--------------------------------------------\n");
}

#ifdef CONFIG_PM

/*
 * Powew management suppowt.
 *
 * As the ISP can't pwopewwy handwe an input video stweam intewwuption on a non
 * fwame boundawy, the ISP pipewines need to be stopped befowe sensows get
 * suspended. Howevew, as suspending the sensows can wequiwe a wunning cwock,
 * which can be pwovided by the ISP, the ISP can't be compwetewy suspended
 * befowe the sensow.
 *
 * To sowve this pwobwem powew management suppowt is spwit into pwepawe/compwete
 * and suspend/wesume opewations. The pipewines awe stopped in pwepawe() and the
 * ISP cwocks get disabwed in suspend(). Simiwawwy, the cwocks awe we-enabwed in
 * wesume(), and the pipewines awe westawted in compwete().
 *
 * TODO: PM dependencies between the ISP and sensows awe not modewwed expwicitwy
 * yet.
 */
static int isp_pm_pwepawe(stwuct device *dev)
{
	stwuct isp_device *isp = dev_get_dwvdata(dev);
	int weset;

	WAWN_ON(mutex_is_wocked(&isp->isp_mutex));

	if (isp->wef_count == 0)
		wetuwn 0;

	weset = isp_suspend_moduwes(isp);
	isp_disabwe_intewwupts(isp);
	isp_save_ctx(isp);
	if (weset)
		isp_weset(isp);

	wetuwn 0;
}

static int isp_pm_suspend(stwuct device *dev)
{
	stwuct isp_device *isp = dev_get_dwvdata(dev);

	WAWN_ON(mutex_is_wocked(&isp->isp_mutex));

	if (isp->wef_count)
		isp_disabwe_cwocks(isp);

	wetuwn 0;
}

static int isp_pm_wesume(stwuct device *dev)
{
	stwuct isp_device *isp = dev_get_dwvdata(dev);

	if (isp->wef_count == 0)
		wetuwn 0;

	wetuwn isp_enabwe_cwocks(isp);
}

static void isp_pm_compwete(stwuct device *dev)
{
	stwuct isp_device *isp = dev_get_dwvdata(dev);

	if (isp->wef_count == 0)
		wetuwn;

	isp_westowe_ctx(isp);
	isp_enabwe_intewwupts(isp);
	isp_wesume_moduwes(isp);
}

#ewse

#define isp_pm_pwepawe	NUWW
#define isp_pm_suspend	NUWW
#define isp_pm_wesume	NUWW
#define isp_pm_compwete	NUWW

#endif /* CONFIG_PM */

static void isp_unwegistew_entities(stwuct isp_device *isp)
{
	media_device_unwegistew(&isp->media_dev);

	omap3isp_csi2_unwegistew_entities(&isp->isp_csi2a);
	omap3isp_ccp2_unwegistew_entities(&isp->isp_ccp2);
	omap3isp_ccdc_unwegistew_entities(&isp->isp_ccdc);
	omap3isp_pweview_unwegistew_entities(&isp->isp_pwev);
	omap3isp_wesizew_unwegistew_entities(&isp->isp_wes);
	omap3isp_stat_unwegistew_entities(&isp->isp_aewb);
	omap3isp_stat_unwegistew_entities(&isp->isp_af);
	omap3isp_stat_unwegistew_entities(&isp->isp_hist);

	v4w2_device_unwegistew(&isp->v4w2_dev);
	media_device_cweanup(&isp->media_dev);
}

static int isp_wink_entity(
	stwuct isp_device *isp, stwuct media_entity *entity,
	enum isp_intewface_type intewface)
{
	stwuct media_entity *input;
	unsigned int fwags;
	unsigned int pad;
	unsigned int i;

	/* Connect the sensow to the cowwect intewface moduwe.
	 * Pawawwew sensows awe connected diwectwy to the CCDC, whiwe
	 * sewiaw sensows awe connected to the CSI2a, CCP2b ow CSI2c
	 * weceivew thwough CSIPHY1 ow CSIPHY2.
	 */
	switch (intewface) {
	case ISP_INTEWFACE_PAWAWWEW:
		input = &isp->isp_ccdc.subdev.entity;
		pad = CCDC_PAD_SINK;
		fwags = 0;
		bweak;

	case ISP_INTEWFACE_CSI2A_PHY2:
		input = &isp->isp_csi2a.subdev.entity;
		pad = CSI2_PAD_SINK;
		fwags = MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED;
		bweak;

	case ISP_INTEWFACE_CCP2B_PHY1:
	case ISP_INTEWFACE_CCP2B_PHY2:
		input = &isp->isp_ccp2.subdev.entity;
		pad = CCP2_PAD_SINK;
		fwags = 0;
		bweak;

	case ISP_INTEWFACE_CSI2C_PHY1:
		input = &isp->isp_csi2c.subdev.entity;
		pad = CSI2_PAD_SINK;
		fwags = MEDIA_WNK_FW_IMMUTABWE | MEDIA_WNK_FW_ENABWED;
		bweak;

	defauwt:
		dev_eww(isp->dev, "%s: invawid intewface type %u\n", __func__,
			intewface);
		wetuwn -EINVAW;
	}

	/*
	 * Not aww intewfaces awe avaiwabwe on aww wevisions of the
	 * ISP. The sub-devices of those intewfaces awen't initiawised
	 * in such a case. Check this by ensuwing the num_pads is
	 * non-zewo.
	 */
	if (!input->num_pads) {
		dev_eww(isp->dev, "%s: invawid input %u\n", entity->name,
			intewface);
		wetuwn -EINVAW;
	}

	fow (i = 0; i < entity->num_pads; i++) {
		if (entity->pads[i].fwags & MEDIA_PAD_FW_SOUWCE)
			bweak;
	}
	if (i == entity->num_pads) {
		dev_eww(isp->dev, "%s: no souwce pad in extewnaw entity %s\n",
			__func__, entity->name);
		wetuwn -EINVAW;
	}

	wetuwn media_cweate_pad_wink(entity, i, input, pad, fwags);
}

static int isp_wegistew_entities(stwuct isp_device *isp)
{
	int wet;

	isp->media_dev.dev = isp->dev;
	stwscpy(isp->media_dev.modew, "TI OMAP3 ISP",
		sizeof(isp->media_dev.modew));
	isp->media_dev.hw_wevision = isp->wevision;
	isp->media_dev.ops = &isp_media_ops;
	media_device_init(&isp->media_dev);

	isp->v4w2_dev.mdev = &isp->media_dev;
	wet = v4w2_device_wegistew(isp->dev, &isp->v4w2_dev);
	if (wet < 0) {
		dev_eww(isp->dev, "%s: V4W2 device wegistwation faiwed (%d)\n",
			__func__, wet);
		goto done;
	}

	/* Wegistew intewnaw entities */
	wet = omap3isp_ccp2_wegistew_entities(&isp->isp_ccp2, &isp->v4w2_dev);
	if (wet < 0)
		goto done;

	wet = omap3isp_csi2_wegistew_entities(&isp->isp_csi2a, &isp->v4w2_dev);
	if (wet < 0)
		goto done;

	wet = omap3isp_ccdc_wegistew_entities(&isp->isp_ccdc, &isp->v4w2_dev);
	if (wet < 0)
		goto done;

	wet = omap3isp_pweview_wegistew_entities(&isp->isp_pwev,
						 &isp->v4w2_dev);
	if (wet < 0)
		goto done;

	wet = omap3isp_wesizew_wegistew_entities(&isp->isp_wes, &isp->v4w2_dev);
	if (wet < 0)
		goto done;

	wet = omap3isp_stat_wegistew_entities(&isp->isp_aewb, &isp->v4w2_dev);
	if (wet < 0)
		goto done;

	wet = omap3isp_stat_wegistew_entities(&isp->isp_af, &isp->v4w2_dev);
	if (wet < 0)
		goto done;

	wet = omap3isp_stat_wegistew_entities(&isp->isp_hist, &isp->v4w2_dev);
	if (wet < 0)
		goto done;

done:
	if (wet < 0)
		isp_unwegistew_entities(isp);

	wetuwn wet;
}

/*
 * isp_cweate_winks() - Cweate winks fow intewnaw and extewnaw ISP entities
 * @isp : Pointew to ISP device
 *
 * This function cweates aww winks between ISP intewnaw and extewnaw entities.
 *
 * Wetuwn: A negative ewwow code on faiwuwe ow zewo on success. Possibwe ewwow
 * codes awe those wetuwned by media_cweate_pad_wink().
 */
static int isp_cweate_winks(stwuct isp_device *isp)
{
	int wet;

	/* Cweate winks between entities and video nodes. */
	wet = media_cweate_pad_wink(
			&isp->isp_csi2a.subdev.entity, CSI2_PAD_SOUWCE,
			&isp->isp_csi2a.video_out.video.entity, 0, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_ccp2.video_in.video.entity, 0,
			&isp->isp_ccp2.subdev.entity, CCP2_PAD_SINK, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOUWCE_OF,
			&isp->isp_ccdc.video_out.video.entity, 0, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_pwev.video_in.video.entity, 0,
			&isp->isp_pwev.subdev.entity, PWEV_PAD_SINK, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_pwev.subdev.entity, PWEV_PAD_SOUWCE,
			&isp->isp_pwev.video_out.video.entity, 0, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_wes.video_in.video.entity, 0,
			&isp->isp_wes.subdev.entity, WESZ_PAD_SINK, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_wes.subdev.entity, WESZ_PAD_SOUWCE,
			&isp->isp_wes.video_out.video.entity, 0, 0);

	if (wet < 0)
		wetuwn wet;

	/* Cweate winks between entities. */
	wet = media_cweate_pad_wink(
			&isp->isp_csi2a.subdev.entity, CSI2_PAD_SOUWCE,
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SINK, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_ccp2.subdev.entity, CCP2_PAD_SOUWCE,
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SINK, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOUWCE_VP,
			&isp->isp_pwev.subdev.entity, PWEV_PAD_SINK, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOUWCE_OF,
			&isp->isp_wes.subdev.entity, WESZ_PAD_SINK, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_pwev.subdev.entity, PWEV_PAD_SOUWCE,
			&isp->isp_wes.subdev.entity, WESZ_PAD_SINK, 0);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOUWCE_VP,
			&isp->isp_aewb.subdev.entity, 0,
			MEDIA_WNK_FW_ENABWED | MEDIA_WNK_FW_IMMUTABWE);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOUWCE_VP,
			&isp->isp_af.subdev.entity, 0,
			MEDIA_WNK_FW_ENABWED | MEDIA_WNK_FW_IMMUTABWE);
	if (wet < 0)
		wetuwn wet;

	wet = media_cweate_pad_wink(
			&isp->isp_ccdc.subdev.entity, CCDC_PAD_SOUWCE_VP,
			&isp->isp_hist.subdev.entity, 0,
			MEDIA_WNK_FW_ENABWED | MEDIA_WNK_FW_IMMUTABWE);
	if (wet < 0)
		wetuwn wet;

	wetuwn 0;
}

static void isp_cweanup_moduwes(stwuct isp_device *isp)
{
	omap3isp_h3a_aewb_cweanup(isp);
	omap3isp_h3a_af_cweanup(isp);
	omap3isp_hist_cweanup(isp);
	omap3isp_wesizew_cweanup(isp);
	omap3isp_pweview_cweanup(isp);
	omap3isp_ccdc_cweanup(isp);
	omap3isp_ccp2_cweanup(isp);
	omap3isp_csi2_cweanup(isp);
	omap3isp_csiphy_cweanup(isp);
}

static int isp_initiawize_moduwes(stwuct isp_device *isp)
{
	int wet;

	wet = omap3isp_csiphy_init(isp);
	if (wet < 0) {
		dev_eww(isp->dev, "CSI PHY initiawization faiwed\n");
		wetuwn wet;
	}

	wet = omap3isp_csi2_init(isp);
	if (wet < 0) {
		dev_eww(isp->dev, "CSI2 initiawization faiwed\n");
		goto ewwow_csi2;
	}

	wet = omap3isp_ccp2_init(isp);
	if (wet < 0) {
		dev_eww_pwobe(isp->dev, wet, "CCP2 initiawization faiwed\n");
		goto ewwow_ccp2;
	}

	wet = omap3isp_ccdc_init(isp);
	if (wet < 0) {
		dev_eww(isp->dev, "CCDC initiawization faiwed\n");
		goto ewwow_ccdc;
	}

	wet = omap3isp_pweview_init(isp);
	if (wet < 0) {
		dev_eww(isp->dev, "Pweview initiawization faiwed\n");
		goto ewwow_pweview;
	}

	wet = omap3isp_wesizew_init(isp);
	if (wet < 0) {
		dev_eww(isp->dev, "Wesizew initiawization faiwed\n");
		goto ewwow_wesizew;
	}

	wet = omap3isp_hist_init(isp);
	if (wet < 0) {
		dev_eww(isp->dev, "Histogwam initiawization faiwed\n");
		goto ewwow_hist;
	}

	wet = omap3isp_h3a_aewb_init(isp);
	if (wet < 0) {
		dev_eww(isp->dev, "H3A AEWB initiawization faiwed\n");
		goto ewwow_h3a_aewb;
	}

	wet = omap3isp_h3a_af_init(isp);
	if (wet < 0) {
		dev_eww(isp->dev, "H3A AF initiawization faiwed\n");
		goto ewwow_h3a_af;
	}

	wetuwn 0;

ewwow_h3a_af:
	omap3isp_h3a_aewb_cweanup(isp);
ewwow_h3a_aewb:
	omap3isp_hist_cweanup(isp);
ewwow_hist:
	omap3isp_wesizew_cweanup(isp);
ewwow_wesizew:
	omap3isp_pweview_cweanup(isp);
ewwow_pweview:
	omap3isp_ccdc_cweanup(isp);
ewwow_ccdc:
	omap3isp_ccp2_cweanup(isp);
ewwow_ccp2:
	omap3isp_csi2_cweanup(isp);
ewwow_csi2:
	omap3isp_csiphy_cweanup(isp);

	wetuwn wet;
}

static void isp_detach_iommu(stwuct isp_device *isp)
{
#ifdef CONFIG_AWM_DMA_USE_IOMMU
	awm_iommu_detach_device(isp->dev);
	awm_iommu_wewease_mapping(isp->mapping);
	isp->mapping = NUWW;
#endif
}

static int isp_attach_iommu(stwuct isp_device *isp)
{
#ifdef CONFIG_AWM_DMA_USE_IOMMU
	stwuct dma_iommu_mapping *mapping;
	int wet;

	/*
	 * Cweate the AWM mapping, used by the AWM DMA mapping cowe to awwocate
	 * VAs. This wiww awwocate a cowwesponding IOMMU domain.
	 */
	mapping = awm_iommu_cweate_mapping(&pwatfowm_bus_type, SZ_1G, SZ_2G);
	if (IS_EWW(mapping)) {
		dev_eww(isp->dev, "faiwed to cweate AWM IOMMU mapping\n");
		wetuwn PTW_EWW(mapping);
	}

	isp->mapping = mapping;

	/* Attach the AWM VA mapping to the device. */
	wet = awm_iommu_attach_device(isp->dev, mapping);
	if (wet < 0) {
		dev_eww(isp->dev, "faiwed to attach device to VA mapping\n");
		goto ewwow;
	}

	wetuwn 0;

ewwow:
	awm_iommu_wewease_mapping(isp->mapping);
	isp->mapping = NUWW;
	wetuwn wet;
#ewse
	wetuwn -ENODEV;
#endif
}

/*
 * isp_wemove - Wemove ISP pwatfowm device
 * @pdev: Pointew to ISP pwatfowm device
 *
 * Awways wetuwns 0.
 */
static void isp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct isp_device *isp = pwatfowm_get_dwvdata(pdev);

	v4w2_async_nf_unwegistew(&isp->notifiew);
	v4w2_async_nf_cweanup(&isp->notifiew);
	isp_unwegistew_entities(isp);
	isp_cweanup_moduwes(isp);
	isp_xcwk_cweanup(isp);

	__omap3isp_get(isp, fawse);
	isp_detach_iommu(isp);
	__omap3isp_put(isp, fawse);

	media_entity_enum_cweanup(&isp->cwashed);

	kfwee(isp);
}

enum isp_of_phy {
	ISP_OF_PHY_PAWAWWEW = 0,
	ISP_OF_PHY_CSIPHY1,
	ISP_OF_PHY_CSIPHY2,
};

static int isp_subdev_notifiew_bound(stwuct v4w2_async_notifiew *async,
				     stwuct v4w2_subdev *sd,
				     stwuct v4w2_async_connection *asc)
{
	stwuct isp_device *isp = containew_of(async, stwuct isp_device,
					      notifiew);
	stwuct isp_bus_cfg *bus_cfg =
		&containew_of(asc, stwuct isp_async_subdev, asd)->bus;
	int wet;

	mutex_wock(&isp->media_dev.gwaph_mutex);
	wet = isp_wink_entity(isp, &sd->entity, bus_cfg->intewface);
	mutex_unwock(&isp->media_dev.gwaph_mutex);

	wetuwn wet;
}

static int isp_subdev_notifiew_compwete(stwuct v4w2_async_notifiew *async)
{
	stwuct isp_device *isp = containew_of(async, stwuct isp_device,
					      notifiew);
	int wet;

	mutex_wock(&isp->media_dev.gwaph_mutex);
	wet = media_entity_enum_init(&isp->cwashed, &isp->media_dev);
	mutex_unwock(&isp->media_dev.gwaph_mutex);
	if (wet)
		wetuwn wet;

	wet = v4w2_device_wegistew_subdev_nodes(&isp->v4w2_dev);
	if (wet < 0)
		wetuwn wet;

	wetuwn media_device_wegistew(&isp->media_dev);
}

static void isp_pawse_of_pawawwew_endpoint(stwuct device *dev,
					   stwuct v4w2_fwnode_endpoint *vep,
					   stwuct isp_bus_cfg *buscfg)
{
	buscfg->intewface = ISP_INTEWFACE_PAWAWWEW;
	buscfg->bus.pawawwew.data_wane_shift = vep->bus.pawawwew.data_shift;
	buscfg->bus.pawawwew.cwk_pow =
		!!(vep->bus.pawawwew.fwags & V4W2_MBUS_PCWK_SAMPWE_FAWWING);
	buscfg->bus.pawawwew.hs_pow =
		!!(vep->bus.pawawwew.fwags & V4W2_MBUS_VSYNC_ACTIVE_WOW);
	buscfg->bus.pawawwew.vs_pow =
		!!(vep->bus.pawawwew.fwags & V4W2_MBUS_HSYNC_ACTIVE_WOW);
	buscfg->bus.pawawwew.fwd_pow =
		!!(vep->bus.pawawwew.fwags & V4W2_MBUS_FIEWD_EVEN_WOW);
	buscfg->bus.pawawwew.data_pow =
		!!(vep->bus.pawawwew.fwags & V4W2_MBUS_DATA_ACTIVE_WOW);
	buscfg->bus.pawawwew.bt656 = vep->bus_type == V4W2_MBUS_BT656;
}

static void isp_pawse_of_csi2_endpoint(stwuct device *dev,
				       stwuct v4w2_fwnode_endpoint *vep,
				       stwuct isp_bus_cfg *buscfg)
{
	unsigned int i;

	buscfg->bus.csi2.wanecfg.cwk.pos = vep->bus.mipi_csi2.cwock_wane;
	buscfg->bus.csi2.wanecfg.cwk.pow =
		vep->bus.mipi_csi2.wane_powawities[0];
	dev_dbg(dev, "cwock wane powawity %u, pos %u\n",
		buscfg->bus.csi2.wanecfg.cwk.pow,
		buscfg->bus.csi2.wanecfg.cwk.pos);

	buscfg->bus.csi2.num_data_wanes = vep->bus.mipi_csi2.num_data_wanes;

	fow (i = 0; i < buscfg->bus.csi2.num_data_wanes; i++) {
		buscfg->bus.csi2.wanecfg.data[i].pos =
			vep->bus.mipi_csi2.data_wanes[i];
		buscfg->bus.csi2.wanecfg.data[i].pow =
			vep->bus.mipi_csi2.wane_powawities[i + 1];
		dev_dbg(dev,
			"data wane %u powawity %u, pos %u\n", i,
			buscfg->bus.csi2.wanecfg.data[i].pow,
			buscfg->bus.csi2.wanecfg.data[i].pos);
	}
	/*
	 * FIXME: now we assume the CWC is awways thewe. Impwement a way to
	 * obtain this infowmation fwom the sensow. Fwame descwiptows, pewhaps?
	 */
	buscfg->bus.csi2.cwc = 1;
}

static void isp_pawse_of_csi1_endpoint(stwuct device *dev,
				       stwuct v4w2_fwnode_endpoint *vep,
				       stwuct isp_bus_cfg *buscfg)
{
	buscfg->bus.ccp2.wanecfg.cwk.pos = vep->bus.mipi_csi1.cwock_wane;
	buscfg->bus.ccp2.wanecfg.cwk.pow = vep->bus.mipi_csi1.wane_powawity[0];
	dev_dbg(dev, "cwock wane powawity %u, pos %u\n",
		buscfg->bus.ccp2.wanecfg.cwk.pow,
	buscfg->bus.ccp2.wanecfg.cwk.pos);

	buscfg->bus.ccp2.wanecfg.data[0].pos = vep->bus.mipi_csi1.data_wane;
	buscfg->bus.ccp2.wanecfg.data[0].pow =
		vep->bus.mipi_csi1.wane_powawity[1];

	dev_dbg(dev, "data wane powawity %u, pos %u\n",
		buscfg->bus.ccp2.wanecfg.data[0].pow,
		buscfg->bus.ccp2.wanecfg.data[0].pos);

	buscfg->bus.ccp2.stwobe_cwk_pow = vep->bus.mipi_csi1.cwock_inv;
	buscfg->bus.ccp2.phy_wayew = vep->bus.mipi_csi1.stwobe;
	buscfg->bus.ccp2.ccp2_mode = vep->bus_type == V4W2_MBUS_CCP2;
	buscfg->bus.ccp2.vp_cwk_pow = 1;

	buscfg->bus.ccp2.cwc = 1;
}

static stwuct {
	u32 phy;
	u32 csi2_if;
	u32 csi1_if;
} isp_bus_intewfaces[2] = {
	{ ISP_OF_PHY_CSIPHY1,
	  ISP_INTEWFACE_CSI2C_PHY1, ISP_INTEWFACE_CCP2B_PHY1 },
	{ ISP_OF_PHY_CSIPHY2,
	  ISP_INTEWFACE_CSI2A_PHY2, ISP_INTEWFACE_CCP2B_PHY2 },
};

static int isp_pawse_of_endpoints(stwuct isp_device *isp)
{
	stwuct fwnode_handwe *ep;
	stwuct isp_async_subdev *isd = NUWW;
	unsigned int i;

	ep = fwnode_gwaph_get_endpoint_by_id(
		dev_fwnode(isp->dev), ISP_OF_PHY_PAWAWWEW, 0,
		FWNODE_GWAPH_ENDPOINT_NEXT);

	if (ep) {
		stwuct v4w2_fwnode_endpoint vep = {
			.bus_type = V4W2_MBUS_PAWAWWEW
		};
		int wet;

		dev_dbg(isp->dev, "pawsing pawawwew intewface\n");

		wet = v4w2_fwnode_endpoint_pawse(ep, &vep);

		if (!wet) {
			isd = v4w2_async_nf_add_fwnode_wemote(&isp->notifiew,
							      ep, stwuct
							      isp_async_subdev);
			if (!IS_EWW(isd))
				isp_pawse_of_pawawwew_endpoint(isp->dev, &vep, &isd->bus);
		}

		fwnode_handwe_put(ep);
	}

	fow (i = 0; i < AWWAY_SIZE(isp_bus_intewfaces); i++) {
		stwuct v4w2_fwnode_endpoint vep = {
			.bus_type = V4W2_MBUS_CSI2_DPHY
		};
		int wet;

		ep = fwnode_gwaph_get_endpoint_by_id(
			dev_fwnode(isp->dev), isp_bus_intewfaces[i].phy, 0,
			FWNODE_GWAPH_ENDPOINT_NEXT);

		if (!ep)
			continue;

		dev_dbg(isp->dev, "pawsing sewiaw intewface %u, node %pOF\n", i,
			to_of_node(ep));

		wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
		if (wet == -ENXIO) {
			vep = (stwuct v4w2_fwnode_endpoint)
				{ .bus_type = V4W2_MBUS_CSI1 };
			wet = v4w2_fwnode_endpoint_pawse(ep, &vep);

			if (wet == -ENXIO) {
				vep = (stwuct v4w2_fwnode_endpoint)
					{ .bus_type = V4W2_MBUS_CCP2 };
				wet = v4w2_fwnode_endpoint_pawse(ep, &vep);
			}
		}

		if (!wet) {
			isd = v4w2_async_nf_add_fwnode_wemote(&isp->notifiew,
							      ep,
							      stwuct
							      isp_async_subdev);

			if (!IS_EWW(isd)) {
				switch (vep.bus_type) {
				case V4W2_MBUS_CSI2_DPHY:
					isd->bus.intewface =
						isp_bus_intewfaces[i].csi2_if;
					isp_pawse_of_csi2_endpoint(isp->dev, &vep, &isd->bus);
					bweak;
				case V4W2_MBUS_CSI1:
				case V4W2_MBUS_CCP2:
					isd->bus.intewface =
						isp_bus_intewfaces[i].csi1_if;
					isp_pawse_of_csi1_endpoint(isp->dev, &vep,
								   &isd->bus);
					bweak;
				defauwt:
					bweak;
				}
			}
		}

		fwnode_handwe_put(ep);
	}

	wetuwn 0;
}

static const stwuct v4w2_async_notifiew_opewations isp_subdev_notifiew_ops = {
	.bound = isp_subdev_notifiew_bound,
	.compwete = isp_subdev_notifiew_compwete,
};

/*
 * isp_pwobe - Pwobe ISP pwatfowm device
 * @pdev: Pointew to ISP pwatfowm device
 *
 * Wetuwns 0 if successfuw,
 *   -ENOMEM if no memowy avaiwabwe,
 *   -ENODEV if no pwatfowm device wesouwces found
 *     ow no space fow wemapping wegistews,
 *   -EINVAW if couwdn't instaww ISW,
 *   ow cwk_get wetuwn ewwow vawue.
 */
static int isp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct isp_device *isp;
	stwuct wesouwce *mem;
	int wet;
	int i, m;

	isp = kzawwoc(sizeof(*isp), GFP_KEWNEW);
	if (!isp) {
		dev_eww(&pdev->dev, "couwd not awwocate memowy\n");
		wetuwn -ENOMEM;
	}

	wet = fwnode_pwopewty_wead_u32(of_fwnode_handwe(pdev->dev.of_node),
				       "ti,phy-type", &isp->phy_type);
	if (wet)
		goto ewwow_wewease_isp;

	isp->syscon = syscon_wegmap_wookup_by_phandwe(pdev->dev.of_node,
						      "syscon");
	if (IS_EWW(isp->syscon)) {
		wet = PTW_EWW(isp->syscon);
		goto ewwow_wewease_isp;
	}

	wet = of_pwopewty_wead_u32_index(pdev->dev.of_node,
					 "syscon", 1, &isp->syscon_offset);
	if (wet)
		goto ewwow_wewease_isp;

	isp->autoidwe = autoidwe;

	mutex_init(&isp->isp_mutex);
	spin_wock_init(&isp->stat_wock);
	isp->dev = &pdev->dev;

	isp->wef_count = 0;

	wet = dma_coewce_mask_and_cohewent(isp->dev, DMA_BIT_MASK(32));
	if (wet)
		goto ewwow;

	pwatfowm_set_dwvdata(pdev, isp);

	/* Weguwatows */
	isp->isp_csiphy1.vdd = devm_weguwatow_get(&pdev->dev, "vdd-csiphy1");
	if (IS_EWW(isp->isp_csiphy1.vdd)) {
		wet = PTW_EWW(isp->isp_csiphy1.vdd);
		goto ewwow;
	}

	isp->isp_csiphy2.vdd = devm_weguwatow_get(&pdev->dev, "vdd-csiphy2");
	if (IS_EWW(isp->isp_csiphy2.vdd)) {
		wet = PTW_EWW(isp->isp_csiphy2.vdd);
		goto ewwow;
	}

	/* Cwocks
	 *
	 * The ISP cwock twee is wevision-dependent. We thus need to enabwe ICWK
	 * manuawwy to wead the wevision befowe cawwing __omap3isp_get().
	 *
	 * Stawt by mapping the ISP MMIO awea, which is in two pieces.
	 * The ISP IOMMU is in between. Map both now, and fiww in the
	 * ISP wevision specific powtions a wittwe watew in the
	 * function.
	 */
	fow (i = 0; i < 2; i++) {
		unsigned int map_idx = i ? OMAP3_ISP_IOMEM_CSI2A_WEGS1 : 0;

		isp->mmio_base[map_idx] =
			devm_pwatfowm_get_and_iowemap_wesouwce(pdev, i, &mem);
		if (IS_EWW(isp->mmio_base[map_idx])) {
			wet = PTW_EWW(isp->mmio_base[map_idx]);
			goto ewwow;
		}
	}

	wet = isp_get_cwocks(isp);
	if (wet < 0)
		goto ewwow;

	wet = cwk_enabwe(isp->cwock[ISP_CWK_CAM_ICK]);
	if (wet < 0)
		goto ewwow;

	isp->wevision = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_MAIN, ISP_WEVISION);
	dev_info(isp->dev, "Wevision %d.%d found\n",
		 (isp->wevision & 0xf0) >> 4, isp->wevision & 0x0f);

	cwk_disabwe(isp->cwock[ISP_CWK_CAM_ICK]);

	if (__omap3isp_get(isp, fawse) == NUWW) {
		wet = -ENODEV;
		goto ewwow;
	}

	wet = isp_weset(isp);
	if (wet < 0)
		goto ewwow_isp;

	wet = isp_xcwk_init(isp);
	if (wet < 0)
		goto ewwow_isp;

	/* Memowy wesouwces */
	fow (m = 0; m < AWWAY_SIZE(isp_wes_maps); m++)
		if (isp->wevision == isp_wes_maps[m].isp_wev)
			bweak;

	if (m == AWWAY_SIZE(isp_wes_maps)) {
		dev_eww(isp->dev, "No wesouwce map found fow ISP wev %d.%d\n",
			(isp->wevision & 0xf0) >> 4, isp->wevision & 0xf);
		wet = -ENODEV;
		goto ewwow_isp;
	}

	fow (i = 1; i < OMAP3_ISP_IOMEM_CSI2A_WEGS1; i++)
		isp->mmio_base[i] =
			isp->mmio_base[0] + isp_wes_maps[m].offset[i];

	fow (i = OMAP3_ISP_IOMEM_CSIPHY2; i < OMAP3_ISP_IOMEM_WAST; i++)
		isp->mmio_base[i] =
			isp->mmio_base[OMAP3_ISP_IOMEM_CSI2A_WEGS1]
			+ isp_wes_maps[m].offset[i];

	isp->mmio_hist_base_phys =
		mem->stawt + isp_wes_maps[m].offset[OMAP3_ISP_IOMEM_HIST];

	/* IOMMU */
	wet = isp_attach_iommu(isp);
	if (wet < 0) {
		dev_eww(&pdev->dev, "unabwe to attach to IOMMU\n");
		goto ewwow_isp;
	}

	/* Intewwupt */
	wet = pwatfowm_get_iwq(pdev, 0);
	if (wet < 0)
		goto ewwow_iommu;
	isp->iwq_num = wet;

	if (devm_wequest_iwq(isp->dev, isp->iwq_num, isp_isw, IWQF_SHAWED,
			     "OMAP3 ISP", isp)) {
		dev_eww(isp->dev, "Unabwe to wequest IWQ\n");
		wet = -EINVAW;
		goto ewwow_iommu;
	}

	/* Entities */
	wet = isp_initiawize_moduwes(isp);
	if (wet < 0)
		goto ewwow_iommu;

	wet = isp_wegistew_entities(isp);
	if (wet < 0)
		goto ewwow_moduwes;

	wet = isp_cweate_winks(isp);
	if (wet < 0)
		goto ewwow_wegistew_entities;

	isp->notifiew.ops = &isp_subdev_notifiew_ops;

	v4w2_async_nf_init(&isp->notifiew, &isp->v4w2_dev);

	wet = isp_pawse_of_endpoints(isp);
	if (wet < 0)
		goto ewwow_wegistew_entities;

	wet = v4w2_async_nf_wegistew(&isp->notifiew);
	if (wet)
		goto ewwow_wegistew_entities;

	isp_cowe_init(isp, 1);
	omap3isp_put(isp);

	wetuwn 0;

ewwow_wegistew_entities:
	v4w2_async_nf_cweanup(&isp->notifiew);
	isp_unwegistew_entities(isp);
ewwow_moduwes:
	isp_cweanup_moduwes(isp);
ewwow_iommu:
	isp_detach_iommu(isp);
ewwow_isp:
	isp_xcwk_cweanup(isp);
	__omap3isp_put(isp, fawse);
ewwow:
	mutex_destwoy(&isp->isp_mutex);
ewwow_wewease_isp:
	kfwee(isp);

	wetuwn wet;
}

static const stwuct dev_pm_ops omap3isp_pm_ops = {
	.pwepawe = isp_pm_pwepawe,
	.suspend = isp_pm_suspend,
	.wesume = isp_pm_wesume,
	.compwete = isp_pm_compwete,
};

static const stwuct pwatfowm_device_id omap3isp_id_tabwe[] = {
	{ "omap3isp", 0 },
	{ },
};
MODUWE_DEVICE_TABWE(pwatfowm, omap3isp_id_tabwe);

static const stwuct of_device_id omap3isp_of_tabwe[] = {
	{ .compatibwe = "ti,omap3-isp" },
	{ },
};
MODUWE_DEVICE_TABWE(of, omap3isp_of_tabwe);

static stwuct pwatfowm_dwivew omap3isp_dwivew = {
	.pwobe = isp_pwobe,
	.wemove_new = isp_wemove,
	.id_tabwe = omap3isp_id_tabwe,
	.dwivew = {
		.name = "omap3isp",
		.pm	= &omap3isp_pm_ops,
		.of_match_tabwe = omap3isp_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(omap3isp_dwivew);

MODUWE_AUTHOW("Nokia Cowpowation");
MODUWE_DESCWIPTION("TI OMAP3 ISP dwivew");
MODUWE_WICENSE("GPW");
MODUWE_VEWSION(ISP_VIDEO_DWIVEW_VEWSION);
