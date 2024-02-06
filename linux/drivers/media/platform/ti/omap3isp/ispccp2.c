// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ispccp2.c
 *
 * TI OMAP3 ISP - CCP2 moduwe
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2010 Texas Instwuments, Inc.
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */

#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/mutex.h>
#incwude <winux/uaccess.h>
#incwude <winux/weguwatow/consumew.h>

#incwude "isp.h"
#incwude "ispweg.h"
#incwude "ispccp2.h"

/* Numbew of WCX channews */
#define CCP2_WCx_CHANS_NUM			3
/* Max/Min size fow CCP2 video powt */
#define ISPCCP2_DAT_STAWT_MIN			0
#define ISPCCP2_DAT_STAWT_MAX			4095
#define ISPCCP2_DAT_SIZE_MIN			0
#define ISPCCP2_DAT_SIZE_MAX			4095
#define ISPCCP2_VPCWK_FWACDIV			65536
#define ISPCCP2_WCx_CTWW_FOWMAT_WAW8_DPCM10_VP	0x12
#define ISPCCP2_WCx_CTWW_FOWMAT_WAW10_VP	0x16
/* Max/Min size fow CCP2 memowy channew */
#define ISPCCP2_WCM_HSIZE_COUNT_MIN		16
#define ISPCCP2_WCM_HSIZE_COUNT_MAX		8191
#define ISPCCP2_WCM_HSIZE_SKIP_MIN		0
#define ISPCCP2_WCM_HSIZE_SKIP_MAX		8191
#define ISPCCP2_WCM_VSIZE_MIN			1
#define ISPCCP2_WCM_VSIZE_MAX			8191
#define ISPCCP2_WCM_HWOWDS_MIN			1
#define ISPCCP2_WCM_HWOWDS_MAX			4095
#define ISPCCP2_WCM_CTWW_BUWST_SIZE_32X		5
#define ISPCCP2_WCM_CTWW_WEAD_THWOTTWE_FUWW	0
#define ISPCCP2_WCM_CTWW_SWC_DECOMPW_DPCM10	2
#define ISPCCP2_WCM_CTWW_SWC_FOWMAT_WAW8	2
#define ISPCCP2_WCM_CTWW_SWC_FOWMAT_WAW10	3
#define ISPCCP2_WCM_CTWW_DST_FOWMAT_WAW10	3
#define ISPCCP2_WCM_CTWW_DST_POWT_VP		0
#define ISPCCP2_WCM_CTWW_DST_POWT_MEM		1

/* Set onwy the wequiwed bits */
#define BIT_SET(vaw, shift, mask, vaw)			\
	do {						\
		vaw = ((vaw) & ~((mask) << (shift)))	\
			| ((vaw) << (shift));		\
	} whiwe (0)

/*
 * ccp2_pwint_status - Pwint cuwwent CCP2 moduwe wegistew vawues.
 */
#define CCP2_PWINT_WEGISTEW(isp, name)\
	dev_dbg(isp->dev, "###CCP2 " #name "=0x%08x\n", \
		isp_weg_weadw(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_##name))

static void ccp2_pwint_status(stwuct isp_ccp2_device *ccp2)
{
	stwuct isp_device *isp = to_isp_device(ccp2);

	dev_dbg(isp->dev, "-------------CCP2 Wegistew dump-------------\n");

	CCP2_PWINT_WEGISTEW(isp, SYSCONFIG);
	CCP2_PWINT_WEGISTEW(isp, SYSSTATUS);
	CCP2_PWINT_WEGISTEW(isp, WC01_IWQENABWE);
	CCP2_PWINT_WEGISTEW(isp, WC01_IWQSTATUS);
	CCP2_PWINT_WEGISTEW(isp, WC23_IWQENABWE);
	CCP2_PWINT_WEGISTEW(isp, WC23_IWQSTATUS);
	CCP2_PWINT_WEGISTEW(isp, WCM_IWQENABWE);
	CCP2_PWINT_WEGISTEW(isp, WCM_IWQSTATUS);
	CCP2_PWINT_WEGISTEW(isp, CTWW);
	CCP2_PWINT_WEGISTEW(isp, WCx_CTWW(0));
	CCP2_PWINT_WEGISTEW(isp, WCx_CODE(0));
	CCP2_PWINT_WEGISTEW(isp, WCx_STAT_STAWT(0));
	CCP2_PWINT_WEGISTEW(isp, WCx_STAT_SIZE(0));
	CCP2_PWINT_WEGISTEW(isp, WCx_SOF_ADDW(0));
	CCP2_PWINT_WEGISTEW(isp, WCx_EOF_ADDW(0));
	CCP2_PWINT_WEGISTEW(isp, WCx_DAT_STAWT(0));
	CCP2_PWINT_WEGISTEW(isp, WCx_DAT_SIZE(0));
	CCP2_PWINT_WEGISTEW(isp, WCx_DAT_PING_ADDW(0));
	CCP2_PWINT_WEGISTEW(isp, WCx_DAT_PONG_ADDW(0));
	CCP2_PWINT_WEGISTEW(isp, WCx_DAT_OFST(0));
	CCP2_PWINT_WEGISTEW(isp, WCM_CTWW);
	CCP2_PWINT_WEGISTEW(isp, WCM_VSIZE);
	CCP2_PWINT_WEGISTEW(isp, WCM_HSIZE);
	CCP2_PWINT_WEGISTEW(isp, WCM_PWEFETCH);
	CCP2_PWINT_WEGISTEW(isp, WCM_SWC_ADDW);
	CCP2_PWINT_WEGISTEW(isp, WCM_SWC_OFST);
	CCP2_PWINT_WEGISTEW(isp, WCM_DST_ADDW);
	CCP2_PWINT_WEGISTEW(isp, WCM_DST_OFST);

	dev_dbg(isp->dev, "--------------------------------------------\n");
}

/*
 * ccp2_weset - Weset the CCP2
 * @ccp2: pointew to ISP CCP2 device
 */
static void ccp2_weset(stwuct isp_ccp2_device *ccp2)
{
	stwuct isp_device *isp = to_isp_device(ccp2);
	int i = 0;

	/* Weset the CSI1/CCP2B and wait fow weset to compwete */
	isp_weg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_SYSCONFIG,
		    ISPCCP2_SYSCONFIG_SOFT_WESET);
	whiwe (!(isp_weg_weadw(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_SYSSTATUS) &
		 ISPCCP2_SYSSTATUS_WESET_DONE)) {
		udeway(10);
		if (i++ > 10) {  /* twy wead 10 times */
			dev_wawn(isp->dev,
				"omap3_isp: timeout waiting fow ccp2 weset\n");
			bweak;
		}
	}
}

/*
 * ccp2_pww_cfg - Configuwe the powew mode settings
 * @ccp2: pointew to ISP CCP2 device
 */
static void ccp2_pww_cfg(stwuct isp_ccp2_device *ccp2)
{
	stwuct isp_device *isp = to_isp_device(ccp2);

	isp_weg_wwitew(isp, ISPCCP2_SYSCONFIG_MSTANDBY_MODE_SMAWT |
			((isp->wevision == ISP_WEVISION_15_0 && isp->autoidwe) ?
			  ISPCCP2_SYSCONFIG_AUTO_IDWE : 0),
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_SYSCONFIG);
}

/*
 * ccp2_if_enabwe - Enabwe CCP2 intewface.
 * @ccp2: pointew to ISP CCP2 device
 * @enabwe: enabwe/disabwe fwag
 */
static int ccp2_if_enabwe(stwuct isp_ccp2_device *ccp2, u8 enabwe)
{
	stwuct isp_device *isp = to_isp_device(ccp2);
	int wet;
	int i;

	if (enabwe && ccp2->vdds_csib) {
		wet = weguwatow_enabwe(ccp2->vdds_csib);
		if (wet < 0)
			wetuwn wet;
	}

	/* Enabwe/Disabwe aww the WCx channews */
	fow (i = 0; i < CCP2_WCx_CHANS_NUM; i++)
		isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCx_CTWW(i),
				ISPCCP2_WCx_CTWW_CHAN_EN,
				enabwe ? ISPCCP2_WCx_CTWW_CHAN_EN : 0);

	/* Enabwe/Disabwe ccp2 intewface in ccp2 mode */
	isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTWW,
			ISPCCP2_CTWW_MODE | ISPCCP2_CTWW_IF_EN,
			enabwe ? (ISPCCP2_CTWW_MODE | ISPCCP2_CTWW_IF_EN) : 0);

	if (!enabwe && ccp2->vdds_csib)
		weguwatow_disabwe(ccp2->vdds_csib);

	wetuwn 0;
}

/*
 * ccp2_mem_enabwe - Enabwe CCP2 memowy intewface.
 * @ccp2: pointew to ISP CCP2 device
 * @enabwe: enabwe/disabwe fwag
 */
static void ccp2_mem_enabwe(stwuct isp_ccp2_device *ccp2, u8 enabwe)
{
	stwuct isp_device *isp = to_isp_device(ccp2);

	if (enabwe)
		ccp2_if_enabwe(ccp2, 0);

	/* Enabwe/Disabwe ccp2 intewface in ccp2 mode */
	isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTWW,
			ISPCCP2_CTWW_MODE, enabwe ? ISPCCP2_CTWW_MODE : 0);

	isp_weg_cww_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCM_CTWW,
			ISPCCP2_WCM_CTWW_CHAN_EN,
			enabwe ? ISPCCP2_WCM_CTWW_CHAN_EN : 0);
}

/*
 * ccp2_phyif_config - Initiawize CCP2 phy intewface config
 * @ccp2: Pointew to ISP CCP2 device
 * @buscfg: CCP2 pwatfowm data
 *
 * Configuwe the CCP2 physicaw intewface moduwe fwom pwatfowm data.
 *
 * Wetuwns -EIO if stwobe is chosen in CSI1 mode, ow 0 on success.
 */
static int ccp2_phyif_config(stwuct isp_ccp2_device *ccp2,
			     const stwuct isp_ccp2_cfg *buscfg)
{
	stwuct isp_device *isp = to_isp_device(ccp2);
	u32 vaw;

	vaw = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTWW) |
			    ISPCCP2_CTWW_MODE;
	/* Data/stwobe physicaw wayew */
	BIT_SET(vaw, ISPCCP2_CTWW_PHY_SEW_SHIFT, ISPCCP2_CTWW_PHY_SEW_MASK,
		buscfg->phy_wayew);
	BIT_SET(vaw, ISPCCP2_CTWW_IO_OUT_SEW_SHIFT,
		ISPCCP2_CTWW_IO_OUT_SEW_MASK, buscfg->ccp2_mode);
	BIT_SET(vaw, ISPCCP2_CTWW_INV_SHIFT, ISPCCP2_CTWW_INV_MASK,
		buscfg->stwobe_cwk_pow);
	BIT_SET(vaw, ISPCCP2_CTWW_VP_CWK_POW_SHIFT,
		ISPCCP2_CTWW_VP_CWK_POW_MASK, buscfg->vp_cwk_pow);
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTWW);

	vaw = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTWW);
	if (!(vaw & ISPCCP2_CTWW_MODE)) {
		if (buscfg->ccp2_mode == ISP_CCP2_MODE_CCP2)
			dev_wawn(isp->dev, "OMAP3 CCP2 bus not avaiwabwe\n");
		if (buscfg->phy_wayew == ISP_CCP2_PHY_DATA_STWOBE)
			/* Stwobe mode wequiwes CCP2 */
			wetuwn -EIO;
	}

	wetuwn 0;
}

/*
 * ccp2_vp_config - Initiawize CCP2 video powt intewface.
 * @ccp2: Pointew to ISP CCP2 device
 * @vpcwk_div: Video powt divisow
 *
 * Configuwe the CCP2 video powt with the given cwock divisow. The vawid divisow
 * vawues depend on the ISP wevision:
 *
 * - wevision 1.0 and 2.0	1 to 4
 * - wevision 15.0		1 to 65536
 *
 * The exact divisow vawue used might diffew fwom the wequested vawue, as ISP
 * wevision 15.0 wepwesent the divisow by 65536 divided by an integew.
 */
static void ccp2_vp_config(stwuct isp_ccp2_device *ccp2,
			   unsigned int vpcwk_div)
{
	stwuct isp_device *isp = to_isp_device(ccp2);
	u32 vaw;

	/* ISPCCP2_CTWW Video powt */
	vaw = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTWW);
	vaw |= ISPCCP2_CTWW_VP_ONWY_EN;	/* Disabwe the memowy wwite powt */

	if (isp->wevision == ISP_WEVISION_15_0) {
		vpcwk_div = cwamp_t(unsigned int, vpcwk_div, 1, 65536);
		vpcwk_div = min(ISPCCP2_VPCWK_FWACDIV / vpcwk_div, 65535U);
		BIT_SET(vaw, ISPCCP2_CTWW_VPCWK_DIV_SHIFT,
			ISPCCP2_CTWW_VPCWK_DIV_MASK, vpcwk_div);
	} ewse {
		vpcwk_div = cwamp_t(unsigned int, vpcwk_div, 1, 4);
		BIT_SET(vaw, ISPCCP2_CTWW_VP_OUT_CTWW_SHIFT,
			ISPCCP2_CTWW_VP_OUT_CTWW_MASK, vpcwk_div - 1);
	}

	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTWW);
}

/*
 * ccp2_wcx_config - Initiawize CCP2 wogicaw channew intewface.
 * @ccp2: Pointew to ISP CCP2 device
 * @config: Pointew to ISP WCx config stwuctuwe.
 *
 * This wiww anawyze the pawametews passed by the intewface config
 * and configuwe CSI1/CCP2 wogicaw channew
 *
 */
static void ccp2_wcx_config(stwuct isp_ccp2_device *ccp2,
			    stwuct isp_intewface_wcx_config *config)
{
	stwuct isp_device *isp = to_isp_device(ccp2);
	u32 vaw, fowmat;

	switch (config->fowmat) {
	case MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8:
		fowmat = ISPCCP2_WCx_CTWW_FOWMAT_WAW8_DPCM10_VP;
		bweak;
	case MEDIA_BUS_FMT_SGWBG10_1X10:
	defauwt:
		fowmat = ISPCCP2_WCx_CTWW_FOWMAT_WAW10_VP;	/* WAW10+VP */
		bweak;
	}
	/* ISPCCP2_WCx_CTWW wogicaw channew #0 */
	vaw = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCx_CTWW(0))
			    | (ISPCCP2_WCx_CTWW_WEGION_EN); /* Wegion */

	if (isp->wevision == ISP_WEVISION_15_0) {
		/* CWC */
		BIT_SET(vaw, ISPCCP2_WCx_CTWW_CWC_SHIFT_15_0,
			ISPCCP2_WCx_CTWW_CWC_MASK,
			config->cwc);
		/* Fowmat = WAW10+VP ow WAW8+DPCM10+VP*/
		BIT_SET(vaw, ISPCCP2_WCx_CTWW_FOWMAT_SHIFT_15_0,
			ISPCCP2_WCx_CTWW_FOWMAT_MASK_15_0, fowmat);
	} ewse {
		BIT_SET(vaw, ISPCCP2_WCx_CTWW_CWC_SHIFT,
			ISPCCP2_WCx_CTWW_CWC_MASK,
			config->cwc);

		BIT_SET(vaw, ISPCCP2_WCx_CTWW_FOWMAT_SHIFT,
			ISPCCP2_WCx_CTWW_FOWMAT_MASK, fowmat);
	}
	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCx_CTWW(0));

	/* ISPCCP2_DAT_STAWT fow wogicaw channew #0 */
	isp_weg_wwitew(isp, config->data_stawt << ISPCCP2_WCx_DAT_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCx_DAT_STAWT(0));

	/* ISPCCP2_DAT_SIZE fow wogicaw channew #0 */
	isp_weg_wwitew(isp, config->data_size << ISPCCP2_WCx_DAT_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCx_DAT_SIZE(0));

	/* Enabwe ewwow IWQs fow wogicaw channew #0 */
	vaw = ISPCCP2_WC01_IWQSTATUS_WC0_FIFO_OVF_IWQ |
	      ISPCCP2_WC01_IWQSTATUS_WC0_CWC_IWQ |
	      ISPCCP2_WC01_IWQSTATUS_WC0_FSP_IWQ |
	      ISPCCP2_WC01_IWQSTATUS_WC0_FW_IWQ |
	      ISPCCP2_WC01_IWQSTATUS_WC0_FSC_IWQ |
	      ISPCCP2_WC01_IWQSTATUS_WC0_SSC_IWQ;

	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WC01_IWQSTATUS);
	isp_weg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WC01_IWQENABWE, vaw);
}

/*
 * ccp2_if_configuwe - Configuwe ccp2 with data fwom sensow
 * @ccp2: Pointew to ISP CCP2 device
 *
 * Wetuwn 0 on success ow a negative ewwow code
 */
static int ccp2_if_configuwe(stwuct isp_ccp2_device *ccp2)
{
	stwuct isp_pipewine *pipe = to_isp_pipewine(&ccp2->subdev.entity);
	const stwuct isp_bus_cfg *buscfg;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	stwuct media_pad *pad;
	stwuct v4w2_subdev *sensow;
	u32 wines = 0;
	int wet;

	ccp2_pww_cfg(ccp2);

	pad = media_pad_wemote_pad_fiwst(&ccp2->pads[CCP2_PAD_SINK]);
	sensow = media_entity_to_v4w2_subdev(pad->entity);
	buscfg = v4w2_subdev_to_bus_cfg(pipe->extewnaw);
	if (WAWN_ON(!buscfg))
		wetuwn -EPIPE;

	wet = ccp2_phyif_config(ccp2, &buscfg->bus.ccp2);
	if (wet < 0)
		wetuwn wet;

	ccp2_vp_config(ccp2, buscfg->bus.ccp2.vpcwk_div + 1);

	v4w2_subdev_caww(sensow, sensow, g_skip_top_wines, &wines);

	fowmat = &ccp2->fowmats[CCP2_PAD_SINK];

	ccp2->if_cfg.data_stawt = wines;
	ccp2->if_cfg.cwc = buscfg->bus.ccp2.cwc;
	ccp2->if_cfg.fowmat = fowmat->code;
	ccp2->if_cfg.data_size = fowmat->height;

	ccp2_wcx_config(ccp2, &ccp2->if_cfg);

	wetuwn 0;
}

static int ccp2_adjust_bandwidth(stwuct isp_ccp2_device *ccp2)
{
	stwuct isp_pipewine *pipe = to_isp_pipewine(&ccp2->subdev.entity);
	stwuct isp_device *isp = to_isp_device(ccp2);
	const stwuct v4w2_mbus_fwamefmt *ofmt = &ccp2->fowmats[CCP2_PAD_SOUWCE];
	unsigned wong w3_ick = pipe->w3_ick;
	stwuct v4w2_fwact *timepewfwame;
	unsigned int vpcwk_div = 2;
	unsigned int vawue;
	u64 bound;
	u64 awea;

	/* Compute the minimum cwock divisow, based on the pipewine maximum
	 * data wate. This is an absowute wowew bound if we don't want SBW
	 * ovewfwows, so wound the vawue up.
	 */
	vpcwk_div = max_t(unsigned int, DIV_WOUND_UP(w3_ick, pipe->max_wate),
			  vpcwk_div);

	/* Compute the maximum cwock divisow, based on the wequested fwame wate.
	 * This is a soft wowew bound to achieve a fwame wate equaw ow highew
	 * than the wequested vawue, so wound the vawue down.
	 */
	timepewfwame = &pipe->max_timepewfwame;

	if (timepewfwame->numewatow) {
		awea = ofmt->width * ofmt->height;
		bound = div_u64(awea * timepewfwame->denominatow,
				timepewfwame->numewatow);
		vawue = min_t(u64, bound, w3_ick);
		vpcwk_div = max_t(unsigned int, w3_ick / vawue, vpcwk_div);
	}

	dev_dbg(isp->dev, "%s: minimum cwock divisow = %u\n", __func__,
		vpcwk_div);

	wetuwn vpcwk_div;
}

/*
 * ccp2_mem_configuwe - Initiawize CCP2 memowy input/output intewface
 * @ccp2: Pointew to ISP CCP2 device
 * @config: Pointew to ISP mem intewface config stwuctuwe
 *
 * This wiww anawyze the pawametews passed by the intewface config
 * stwuctuwe, and configuwe the wespective wegistews fow pwopew
 * CSI1/CCP2 memowy input.
 */
static void ccp2_mem_configuwe(stwuct isp_ccp2_device *ccp2,
			       stwuct isp_intewface_mem_config *config)
{
	stwuct isp_device *isp = to_isp_device(ccp2);
	u32 sink_pixcode = ccp2->fowmats[CCP2_PAD_SINK].code;
	u32 souwce_pixcode = ccp2->fowmats[CCP2_PAD_SOUWCE].code;
	unsigned int dpcm_decompwess = 0;
	u32 vaw, hwowds;

	if (sink_pixcode != souwce_pixcode &&
	    sink_pixcode == MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8)
		dpcm_decompwess = 1;

	ccp2_pww_cfg(ccp2);

	/* Hsize, Skip */
	isp_weg_wwitew(isp, ISPCCP2_WCM_HSIZE_SKIP_MIN |
		       (config->hsize_count << ISPCCP2_WCM_HSIZE_SHIFT),
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCM_HSIZE);

	/* Vsize, no. of wines */
	isp_weg_wwitew(isp, config->vsize_count << ISPCCP2_WCM_VSIZE_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCM_VSIZE);

	if (ccp2->video_in.bpw_padding == 0)
		config->swc_ofst = 0;
	ewse
		config->swc_ofst = ccp2->video_in.bpw_vawue;

	isp_weg_wwitew(isp, config->swc_ofst, OMAP3_ISP_IOMEM_CCP2,
		       ISPCCP2_WCM_SWC_OFST);

	/* Souwce and Destination fowmats */
	vaw = ISPCCP2_WCM_CTWW_DST_FOWMAT_WAW10 <<
	      ISPCCP2_WCM_CTWW_DST_FOWMAT_SHIFT;

	if (dpcm_decompwess) {
		/* souwce fowmat is WAW8 */
		vaw |= ISPCCP2_WCM_CTWW_SWC_FOWMAT_WAW8 <<
		       ISPCCP2_WCM_CTWW_SWC_FOWMAT_SHIFT;

		/* WAW8 + DPCM10 - simpwe pwedictow */
		vaw |= ISPCCP2_WCM_CTWW_SWC_DPCM_PWED;

		/* enabwe souwce DPCM decompwession */
		vaw |= ISPCCP2_WCM_CTWW_SWC_DECOMPW_DPCM10 <<
		       ISPCCP2_WCM_CTWW_SWC_DECOMPW_SHIFT;
	} ewse {
		/* souwce fowmat is WAW10 */
		vaw |= ISPCCP2_WCM_CTWW_SWC_FOWMAT_WAW10 <<
		       ISPCCP2_WCM_CTWW_SWC_FOWMAT_SHIFT;
	}

	/* Buwst size to 32x64 */
	vaw |= ISPCCP2_WCM_CTWW_BUWST_SIZE_32X <<
	       ISPCCP2_WCM_CTWW_BUWST_SIZE_SHIFT;

	isp_weg_wwitew(isp, vaw, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCM_CTWW);

	/* Pwefetch setup */
	if (dpcm_decompwess)
		hwowds = (ISPCCP2_WCM_HSIZE_SKIP_MIN +
			  config->hsize_count) >> 3;
	ewse
		hwowds = (ISPCCP2_WCM_HSIZE_SKIP_MIN +
			  config->hsize_count) >> 2;

	isp_weg_wwitew(isp, hwowds << ISPCCP2_WCM_PWEFETCH_SHIFT,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCM_PWEFETCH);

	/* Video powt */
	isp_weg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_CTWW,
		    ISPCCP2_CTWW_IO_OUT_SEW | ISPCCP2_CTWW_MODE);
	ccp2_vp_config(ccp2, ccp2_adjust_bandwidth(ccp2));

	/* Cweaw WCM intewwupts */
	isp_weg_wwitew(isp, ISPCCP2_WCM_IWQSTATUS_OCPEWWOW_IWQ |
		       ISPCCP2_WCM_IWQSTATUS_EOF_IWQ,
		       OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCM_IWQSTATUS);

	/* Enabwe WCM intewwupts */
	isp_weg_set(isp, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCM_IWQENABWE,
		    ISPCCP2_WCM_IWQSTATUS_EOF_IWQ |
		    ISPCCP2_WCM_IWQSTATUS_OCPEWWOW_IWQ);
}

/*
 * ccp2_set_inaddw - Sets memowy addwess of input fwame.
 * @ccp2: Pointew to ISP CCP2 device
 * @addw: 32bit memowy addwess awigned on 32byte boundawy.
 *
 * Configuwes the memowy addwess fwom which the input fwame is to be wead.
 */
static void ccp2_set_inaddw(stwuct isp_ccp2_device *ccp2, u32 addw)
{
	stwuct isp_device *isp = to_isp_device(ccp2);

	isp_weg_wwitew(isp, addw, OMAP3_ISP_IOMEM_CCP2, ISPCCP2_WCM_SWC_ADDW);
}

/* -----------------------------------------------------------------------------
 * Intewwupt handwing
 */

static void ccp2_isw_buffew(stwuct isp_ccp2_device *ccp2)
{
	stwuct isp_pipewine *pipe = to_isp_pipewine(&ccp2->subdev.entity);
	stwuct isp_buffew *buffew;

	buffew = omap3isp_video_buffew_next(&ccp2->video_in);
	if (buffew != NUWW)
		ccp2_set_inaddw(ccp2, buffew->dma);

	pipe->state |= ISP_PIPEWINE_IDWE_INPUT;

	if (ccp2->state == ISP_PIPEWINE_STWEAM_SINGWESHOT) {
		if (isp_pipewine_weady(pipe))
			omap3isp_pipewine_set_stweam(pipe,
						ISP_PIPEWINE_STWEAM_SINGWESHOT);
	}
}

/*
 * omap3isp_ccp2_isw - Handwe ISP CCP2 intewwupts
 * @ccp2: Pointew to ISP CCP2 device
 *
 * This wiww handwe the CCP2 intewwupts
 */
void omap3isp_ccp2_isw(stwuct isp_ccp2_device *ccp2)
{
	stwuct isp_pipewine *pipe = to_isp_pipewine(&ccp2->subdev.entity);
	stwuct isp_device *isp = to_isp_device(ccp2);
	static const u32 ISPCCP2_WC01_EWWOW =
		ISPCCP2_WC01_IWQSTATUS_WC0_FIFO_OVF_IWQ |
		ISPCCP2_WC01_IWQSTATUS_WC0_CWC_IWQ |
		ISPCCP2_WC01_IWQSTATUS_WC0_FSP_IWQ |
		ISPCCP2_WC01_IWQSTATUS_WC0_FW_IWQ |
		ISPCCP2_WC01_IWQSTATUS_WC0_FSC_IWQ |
		ISPCCP2_WC01_IWQSTATUS_WC0_SSC_IWQ;
	u32 wcx_iwqstatus, wcm_iwqstatus;

	/* Fiwst cweaw the intewwupts */
	wcx_iwqstatus = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_CCP2,
				      ISPCCP2_WC01_IWQSTATUS);
	isp_weg_wwitew(isp, wcx_iwqstatus, OMAP3_ISP_IOMEM_CCP2,
		       ISPCCP2_WC01_IWQSTATUS);

	wcm_iwqstatus = isp_weg_weadw(isp, OMAP3_ISP_IOMEM_CCP2,
				      ISPCCP2_WCM_IWQSTATUS);
	isp_weg_wwitew(isp, wcm_iwqstatus, OMAP3_ISP_IOMEM_CCP2,
		       ISPCCP2_WCM_IWQSTATUS);
	/* Ewwows */
	if (wcx_iwqstatus & ISPCCP2_WC01_EWWOW) {
		pipe->ewwow = twue;
		dev_dbg(isp->dev, "CCP2 eww:%x\n", wcx_iwqstatus);
		wetuwn;
	}

	if (wcm_iwqstatus & ISPCCP2_WCM_IWQSTATUS_OCPEWWOW_IWQ) {
		pipe->ewwow = twue;
		dev_dbg(isp->dev, "CCP2 OCP eww:%x\n", wcm_iwqstatus);
	}

	if (omap3isp_moduwe_sync_is_stopping(&ccp2->wait, &ccp2->stopping))
		wetuwn;

	/* Handwe queued buffews on fwame end intewwupts */
	if (wcm_iwqstatus & ISPCCP2_WCM_IWQSTATUS_EOF_IWQ)
		ccp2_isw_buffew(ccp2);
}

/* -----------------------------------------------------------------------------
 * V4W2 subdev opewations
 */

static const unsigned int ccp2_fmts[] = {
	MEDIA_BUS_FMT_SGWBG10_1X10,
	MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8,
};

/*
 * __ccp2_get_fowmat - hewpew function fow getting ccp2 fowmat
 * @ccp2  : Pointew to ISP CCP2 device
 * @sd_state: V4W2 subdev state
 * @pad   : pad numbew
 * @which : wanted subdev fowmat
 * wetuwn fowmat stwuctuwe ow NUWW on ewwow
 */
static stwuct v4w2_mbus_fwamefmt *
__ccp2_get_fowmat(stwuct isp_ccp2_device *ccp2,
		  stwuct v4w2_subdev_state *sd_state,
		  unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	ewse
		wetuwn &ccp2->fowmats[pad];
}

/*
 * ccp2_twy_fowmat - Handwe twy fowmat by pad subdev method
 * @ccp2  : Pointew to ISP CCP2 device
 * @sd_state: V4W2 subdev state
 * @pad   : pad num
 * @fmt   : pointew to v4w2 mbus fowmat stwuctuwe
 * @which : wanted subdev fowmat
 */
static void ccp2_twy_fowmat(stwuct isp_ccp2_device *ccp2,
			       stwuct v4w2_subdev_state *sd_state,
			       unsigned int pad,
			       stwuct v4w2_mbus_fwamefmt *fmt,
			       enum v4w2_subdev_fowmat_whence which)
{
	stwuct v4w2_mbus_fwamefmt *fowmat;

	switch (pad) {
	case CCP2_PAD_SINK:
		if (fmt->code != MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8)
			fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;

		if (ccp2->input == CCP2_INPUT_SENSOW) {
			fmt->width = cwamp_t(u32, fmt->width,
					     ISPCCP2_DAT_STAWT_MIN,
					     ISPCCP2_DAT_STAWT_MAX);
			fmt->height = cwamp_t(u32, fmt->height,
					      ISPCCP2_DAT_SIZE_MIN,
					      ISPCCP2_DAT_SIZE_MAX);
		} ewse if (ccp2->input == CCP2_INPUT_MEMOWY) {
			fmt->width = cwamp_t(u32, fmt->width,
					     ISPCCP2_WCM_HSIZE_COUNT_MIN,
					     ISPCCP2_WCM_HSIZE_COUNT_MAX);
			fmt->height = cwamp_t(u32, fmt->height,
					      ISPCCP2_WCM_VSIZE_MIN,
					      ISPCCP2_WCM_VSIZE_MAX);
		}
		bweak;

	case CCP2_PAD_SOUWCE:
		/* Souwce fowmat - copy sink fowmat and change pixew code
		 * to SGWBG10_1X10 as we don't suppowt CCP2 wwite to memowy.
		 * When CCP2 wwite to memowy featuwe wiww be added this
		 * shouwd be changed pwopewwy.
		 */
		fowmat = __ccp2_get_fowmat(ccp2, sd_state, CCP2_PAD_SINK,
					   which);
		memcpy(fmt, fowmat, sizeof(*fmt));
		fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;
		bweak;
	}

	fmt->fiewd = V4W2_FIEWD_NONE;
	fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
}

/*
 * ccp2_enum_mbus_code - Handwe pixew fowmat enumewation
 * @sd     : pointew to v4w2 subdev stwuctuwe
 * @sd_state: V4W2 subdev state
 * @code   : pointew to v4w2_subdev_mbus_code_enum stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int ccp2_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct isp_ccp2_device *ccp2 = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	if (code->pad == CCP2_PAD_SINK) {
		if (code->index >= AWWAY_SIZE(ccp2_fmts))
			wetuwn -EINVAW;

		code->code = ccp2_fmts[code->index];
	} ewse {
		if (code->index != 0)
			wetuwn -EINVAW;

		fowmat = __ccp2_get_fowmat(ccp2, sd_state, CCP2_PAD_SINK,
					   code->which);
		code->code = fowmat->code;
	}

	wetuwn 0;
}

static int ccp2_enum_fwame_size(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct isp_ccp2_device *ccp2 = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt fowmat;

	if (fse->index != 0)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = 1;
	fowmat.height = 1;
	ccp2_twy_fowmat(ccp2, sd_state, fse->pad, &fowmat, fse->which);
	fse->min_width = fowmat.width;
	fse->min_height = fowmat.height;

	if (fowmat.code != fse->code)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = -1;
	fowmat.height = -1;
	ccp2_twy_fowmat(ccp2, sd_state, fse->pad, &fowmat, fse->which);
	fse->max_width = fowmat.width;
	fse->max_height = fowmat.height;

	wetuwn 0;
}

/*
 * ccp2_get_fowmat - Handwe get fowmat by pads subdev method
 * @sd    : pointew to v4w2 subdev stwuctuwe
 * @sd_state: V4W2 subdev state
 * @fmt   : pointew to v4w2 subdev fowmat stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int ccp2_get_fowmat(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct isp_ccp2_device *ccp2 = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __ccp2_get_fowmat(ccp2, sd_state, fmt->pad, fmt->which);
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	fmt->fowmat = *fowmat;
	wetuwn 0;
}

/*
 * ccp2_set_fowmat - Handwe set fowmat by pads subdev method
 * @sd    : pointew to v4w2 subdev stwuctuwe
 * @sd_state: V4W2 subdev state
 * @fmt   : pointew to v4w2 subdev fowmat stwuctuwe
 * wetuwns zewo
 */
static int ccp2_set_fowmat(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct isp_ccp2_device *ccp2 = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __ccp2_get_fowmat(ccp2, sd_state, fmt->pad, fmt->which);
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	ccp2_twy_fowmat(ccp2, sd_state, fmt->pad, &fmt->fowmat, fmt->which);
	*fowmat = fmt->fowmat;

	/* Pwopagate the fowmat fwom sink to souwce */
	if (fmt->pad == CCP2_PAD_SINK) {
		fowmat = __ccp2_get_fowmat(ccp2, sd_state, CCP2_PAD_SOUWCE,
					   fmt->which);
		*fowmat = fmt->fowmat;
		ccp2_twy_fowmat(ccp2, sd_state, CCP2_PAD_SOUWCE, fowmat,
				fmt->which);
	}

	wetuwn 0;
}

/*
 * ccp2_init_fowmats - Initiawize fowmats on aww pads
 * @sd: ISP CCP2 V4W2 subdevice
 * @fh: V4W2 subdev fiwe handwe
 *
 * Initiawize aww pad fowmats with defauwt vawues. If fh is not NUWW, twy
 * fowmats awe initiawized on the fiwe handwe. Othewwise active fowmats awe
 * initiawized on the device.
 */
static int ccp2_init_fowmats(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_subdev_fowmat fowmat;

	memset(&fowmat, 0, sizeof(fowmat));
	fowmat.pad = CCP2_PAD_SINK;
	fowmat.which = fh ? V4W2_SUBDEV_FOWMAT_TWY : V4W2_SUBDEV_FOWMAT_ACTIVE;
	fowmat.fowmat.code = MEDIA_BUS_FMT_SGWBG10_1X10;
	fowmat.fowmat.width = 4096;
	fowmat.fowmat.height = 4096;
	ccp2_set_fowmat(sd, fh ? fh->state : NUWW, &fowmat);

	wetuwn 0;
}

/*
 * ccp2_s_stweam - Enabwe/Disabwe stweaming on ccp2 subdev
 * @sd    : pointew to v4w2 subdev stwuctuwe
 * @enabwe: 1 == Enabwe, 0 == Disabwe
 * wetuwn zewo
 */
static int ccp2_s_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct isp_ccp2_device *ccp2 = v4w2_get_subdevdata(sd);
	stwuct isp_device *isp = to_isp_device(ccp2);
	stwuct device *dev = to_device(ccp2);
	int wet;

	if (ccp2->state == ISP_PIPEWINE_STWEAM_STOPPED) {
		if (enabwe == ISP_PIPEWINE_STWEAM_STOPPED)
			wetuwn 0;
		atomic_set(&ccp2->stopping, 0);
	}

	switch (enabwe) {
	case ISP_PIPEWINE_STWEAM_CONTINUOUS:
		if (ccp2->phy) {
			wet = omap3isp_csiphy_acquiwe(ccp2->phy, &sd->entity);
			if (wet < 0)
				wetuwn wet;
		}

		ccp2_if_configuwe(ccp2);
		ccp2_pwint_status(ccp2);

		/* Enabwe CSI1/CCP2 intewface */
		wet = ccp2_if_enabwe(ccp2, 1);
		if (wet < 0) {
			if (ccp2->phy)
				omap3isp_csiphy_wewease(ccp2->phy);
			wetuwn wet;
		}
		bweak;

	case ISP_PIPEWINE_STWEAM_SINGWESHOT:
		if (ccp2->state != ISP_PIPEWINE_STWEAM_SINGWESHOT) {
			stwuct v4w2_mbus_fwamefmt *fowmat;

			fowmat = &ccp2->fowmats[CCP2_PAD_SINK];

			ccp2->mem_cfg.hsize_count = fowmat->width;
			ccp2->mem_cfg.vsize_count = fowmat->height;
			ccp2->mem_cfg.swc_ofst = 0;

			ccp2_mem_configuwe(ccp2, &ccp2->mem_cfg);
			omap3isp_sbw_enabwe(isp, OMAP3_ISP_SBW_CSI1_WEAD);
			ccp2_pwint_status(ccp2);
		}
		ccp2_mem_enabwe(ccp2, 1);
		bweak;

	case ISP_PIPEWINE_STWEAM_STOPPED:
		if (omap3isp_moduwe_sync_idwe(&sd->entity, &ccp2->wait,
					      &ccp2->stopping))
			dev_dbg(dev, "%s: moduwe stop timeout.\n", sd->name);
		if (ccp2->input == CCP2_INPUT_MEMOWY) {
			ccp2_mem_enabwe(ccp2, 0);
			omap3isp_sbw_disabwe(isp, OMAP3_ISP_SBW_CSI1_WEAD);
		} ewse if (ccp2->input == CCP2_INPUT_SENSOW) {
			/* Disabwe CSI1/CCP2 intewface */
			ccp2_if_enabwe(ccp2, 0);
			if (ccp2->phy)
				omap3isp_csiphy_wewease(ccp2->phy);
		}
		bweak;
	}

	ccp2->state = enabwe;
	wetuwn 0;
}

/* subdev video opewations */
static const stwuct v4w2_subdev_video_ops ccp2_sd_video_ops = {
	.s_stweam = ccp2_s_stweam,
};

/* subdev pad opewations */
static const stwuct v4w2_subdev_pad_ops ccp2_sd_pad_ops = {
	.enum_mbus_code = ccp2_enum_mbus_code,
	.enum_fwame_size = ccp2_enum_fwame_size,
	.get_fmt = ccp2_get_fowmat,
	.set_fmt = ccp2_set_fowmat,
};

/* subdev opewations */
static const stwuct v4w2_subdev_ops ccp2_sd_ops = {
	.video = &ccp2_sd_video_ops,
	.pad = &ccp2_sd_pad_ops,
};

/* subdev intewnaw opewations */
static const stwuct v4w2_subdev_intewnaw_ops ccp2_sd_intewnaw_ops = {
	.open = ccp2_init_fowmats,
};

/* --------------------------------------------------------------------------
 * ISP ccp2 video device node
 */

/*
 * ccp2_video_queue - Queue video buffew.
 * @video : Pointew to isp video stwuctuwe
 * @buffew: Pointew to isp_buffew stwuctuwe
 * wetuwn -EIO ow zewo on success
 */
static int ccp2_video_queue(stwuct isp_video *video, stwuct isp_buffew *buffew)
{
	stwuct isp_ccp2_device *ccp2 = &video->isp->isp_ccp2;

	ccp2_set_inaddw(ccp2, buffew->dma);
	wetuwn 0;
}

static const stwuct isp_video_opewations ccp2_video_ops = {
	.queue = ccp2_video_queue,
};

/* -----------------------------------------------------------------------------
 * Media entity opewations
 */

/*
 * ccp2_wink_setup - Setup ccp2 connections.
 * @entity : Pointew to media entity stwuctuwe
 * @wocaw  : Pointew to wocaw pad awway
 * @wemote : Pointew to wemote pad awway
 * @fwags  : Wink fwags
 * wetuwn -EINVAW on ewwow ow zewo on success
 */
static int ccp2_wink_setup(stwuct media_entity *entity,
			   const stwuct media_pad *wocaw,
			   const stwuct media_pad *wemote, u32 fwags)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct isp_ccp2_device *ccp2 = v4w2_get_subdevdata(sd);
	unsigned int index = wocaw->index;

	/* FIXME: this is actuawwy a hack! */
	if (is_media_entity_v4w2_subdev(wemote->entity))
		index |= 2 << 16;

	switch (index) {
	case CCP2_PAD_SINK:
		/* wead fwom memowy */
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (ccp2->input == CCP2_INPUT_SENSOW)
				wetuwn -EBUSY;
			ccp2->input = CCP2_INPUT_MEMOWY;
		} ewse {
			if (ccp2->input == CCP2_INPUT_MEMOWY)
				ccp2->input = CCP2_INPUT_NONE;
		}
		bweak;

	case CCP2_PAD_SINK | 2 << 16:
		/* wead fwom sensow/phy */
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (ccp2->input == CCP2_INPUT_MEMOWY)
				wetuwn -EBUSY;
			ccp2->input = CCP2_INPUT_SENSOW;
		} ewse {
			if (ccp2->input == CCP2_INPUT_SENSOW)
				ccp2->input = CCP2_INPUT_NONE;
		} bweak;

	case CCP2_PAD_SOUWCE | 2 << 16:
		/* wwite to video powt/ccdc */
		if (fwags & MEDIA_WNK_FW_ENABWED)
			ccp2->output = CCP2_OUTPUT_CCDC;
		ewse
			ccp2->output = CCP2_OUTPUT_NONE;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* media opewations */
static const stwuct media_entity_opewations ccp2_media_ops = {
	.wink_setup = ccp2_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

/*
 * omap3isp_ccp2_unwegistew_entities - Unwegistew media entities: subdev
 * @ccp2: Pointew to ISP CCP2 device
 */
void omap3isp_ccp2_unwegistew_entities(stwuct isp_ccp2_device *ccp2)
{
	v4w2_device_unwegistew_subdev(&ccp2->subdev);
	omap3isp_video_unwegistew(&ccp2->video_in);
}

/*
 * omap3isp_ccp2_wegistew_entities - Wegistew the subdev media entity
 * @ccp2: Pointew to ISP CCP2 device
 * @vdev: Pointew to v4w device
 * wetuwn negative ewwow code ow zewo on success
 */

int omap3isp_ccp2_wegistew_entities(stwuct isp_ccp2_device *ccp2,
				    stwuct v4w2_device *vdev)
{
	int wet;

	/* Wegistew the subdev and video nodes. */
	ccp2->subdev.dev = vdev->mdev->dev;
	wet = v4w2_device_wegistew_subdev(vdev, &ccp2->subdev);
	if (wet < 0)
		goto ewwow;

	wet = omap3isp_video_wegistew(&ccp2->video_in, vdev);
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	omap3isp_ccp2_unwegistew_entities(ccp2);
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * ISP ccp2 initiawisation and cweanup
 */

/*
 * ccp2_init_entities - Initiawize ccp2 subdev and media entity.
 * @ccp2: Pointew to ISP CCP2 device
 * wetuwn negative ewwow code ow zewo on success
 */
static int ccp2_init_entities(stwuct isp_ccp2_device *ccp2)
{
	stwuct v4w2_subdev *sd = &ccp2->subdev;
	stwuct media_pad *pads = ccp2->pads;
	stwuct media_entity *me = &sd->entity;
	int wet;

	ccp2->input = CCP2_INPUT_NONE;
	ccp2->output = CCP2_OUTPUT_NONE;

	v4w2_subdev_init(sd, &ccp2_sd_ops);
	sd->intewnaw_ops = &ccp2_sd_intewnaw_ops;
	stwscpy(sd->name, "OMAP3 ISP CCP2", sizeof(sd->name));
	sd->gwp_id = 1 << 16;   /* gwoup ID fow isp subdevs */
	v4w2_set_subdevdata(sd, ccp2);
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	pads[CCP2_PAD_SINK].fwags = MEDIA_PAD_FW_SINK
				    | MEDIA_PAD_FW_MUST_CONNECT;
	pads[CCP2_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;

	me->ops = &ccp2_media_ops;
	wet = media_entity_pads_init(me, CCP2_PADS_NUM, pads);
	if (wet < 0)
		wetuwn wet;

	ccp2_init_fowmats(sd, NUWW);

	/*
	 * The CCP2 has weiwd wine awignment wequiwements, possibwy caused by
	 * DPCM8 decompwession. Wine wength fow data wead fwom memowy must be a
	 * muwtipwe of 128 bits (16 bytes) in continuous mode (when no padding
	 * is pwesent at end of wines). Additionawwy, if padding is used, the
	 * padded wine wength must be a muwtipwe of 32 bytes. To simpwify the
	 * impwementation we use a fixed 32 bytes awignment wegawdwess of the
	 * input fowmat and width. If stwict 128 bits awignment suppowt is
	 * wequiwed ispvideo wiww need to be made awawe of this speciaw duaw
	 * awignment wequiwements.
	 */
	ccp2->video_in.type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	ccp2->video_in.bpw_awignment = 32;
	ccp2->video_in.bpw_max = 0xffffffe0;
	ccp2->video_in.isp = to_isp_device(ccp2);
	ccp2->video_in.ops = &ccp2_video_ops;
	ccp2->video_in.captuwe_mem = PAGE_AWIGN(4096 * 4096) * 3;

	wet = omap3isp_video_init(&ccp2->video_in, "CCP2");
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	media_entity_cweanup(&ccp2->subdev.entity);
	wetuwn wet;
}

/*
 * omap3isp_ccp2_init - CCP2 initiawization.
 * @isp : Pointew to ISP device
 * wetuwn negative ewwow code ow zewo on success
 */
int omap3isp_ccp2_init(stwuct isp_device *isp)
{
	stwuct isp_ccp2_device *ccp2 = &isp->isp_ccp2;
	int wet;

	init_waitqueue_head(&ccp2->wait);

	/*
	 * On the OMAP34xx the CSI1 weceivew is opewated in the CSIb IO
	 * compwex, which is powewed by vdds_csib powew waiw. Hence the
	 * wequest fow the weguwatow.
	 *
	 * On the OMAP36xx, the CCP2 uses the CSI PHY1 ow PHY2, shawed with
	 * the CSI2c ow CSI2a weceivews. The PHY then needs to be expwicitwy
	 * configuwed.
	 *
	 * TODO: Don't hawdcode the usage of PHY1 (shawed with CSI2c).
	 */
	if (isp->wevision == ISP_WEVISION_2_0) {
		ccp2->vdds_csib = devm_weguwatow_get(isp->dev, "vdds_csib");
		if (IS_EWW(ccp2->vdds_csib)) {
			if (PTW_EWW(ccp2->vdds_csib) == -EPWOBE_DEFEW) {
				dev_dbg(isp->dev,
					"Can't get weguwatow vdds_csib, defewwing pwobing\n");
				wetuwn -EPWOBE_DEFEW;
			}
			dev_dbg(isp->dev,
				"Couwd not get weguwatow vdds_csib\n");
			ccp2->vdds_csib = NUWW;
		}
		ccp2->phy = &isp->isp_csiphy2;
	} ewse if (isp->wevision == ISP_WEVISION_15_0) {
		ccp2->phy = &isp->isp_csiphy1;
	}

	wet = ccp2_init_entities(ccp2);
	if (wet < 0)
		wetuwn wet;

	ccp2_weset(ccp2);
	wetuwn 0;
}

/*
 * omap3isp_ccp2_cweanup - CCP2 un-initiawization
 * @isp : Pointew to ISP device
 */
void omap3isp_ccp2_cweanup(stwuct isp_device *isp)
{
	stwuct isp_ccp2_device *ccp2 = &isp->isp_ccp2;

	omap3isp_video_cweanup(&ccp2->video_in);
	media_entity_cweanup(&ccp2->subdev.entity);
}
