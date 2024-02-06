// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * ispcsi2.c
 *
 * TI OMAP3 ISP - CSI2 moduwe
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2009 Texas Instwuments, Inc.
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 */
#incwude <winux/deway.h>
#incwude <media/v4w2-common.h>
#incwude <winux/v4w2-mediabus.h>
#incwude <winux/mm.h>

#incwude "isp.h"
#incwude "ispweg.h"
#incwude "ispcsi2.h"

/*
 * csi2_if_enabwe - Enabwe CSI2 Weceivew intewface.
 * @enabwe: enabwe fwag
 *
 */
static void csi2_if_enabwe(stwuct isp_device *isp,
			   stwuct isp_csi2_device *csi2, u8 enabwe)
{
	stwuct isp_csi2_ctww_cfg *cuwwctww = &csi2->ctww;

	isp_weg_cww_set(isp, csi2->wegs1, ISPCSI2_CTWW, ISPCSI2_CTWW_IF_EN,
			enabwe ? ISPCSI2_CTWW_IF_EN : 0);

	cuwwctww->if_enabwe = enabwe;
}

/*
 * csi2_wecv_config - CSI2 weceivew moduwe configuwation.
 * @cuwwctww: isp_csi2_ctww_cfg stwuctuwe
 *
 */
static void csi2_wecv_config(stwuct isp_device *isp,
			     stwuct isp_csi2_device *csi2,
			     stwuct isp_csi2_ctww_cfg *cuwwctww)
{
	u32 weg;

	weg = isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_CTWW);

	if (cuwwctww->fwame_mode)
		weg |= ISPCSI2_CTWW_FWAME;
	ewse
		weg &= ~ISPCSI2_CTWW_FWAME;

	if (cuwwctww->vp_cwk_enabwe)
		weg |= ISPCSI2_CTWW_VP_CWK_EN;
	ewse
		weg &= ~ISPCSI2_CTWW_VP_CWK_EN;

	if (cuwwctww->vp_onwy_enabwe)
		weg |= ISPCSI2_CTWW_VP_ONWY_EN;
	ewse
		weg &= ~ISPCSI2_CTWW_VP_ONWY_EN;

	weg &= ~ISPCSI2_CTWW_VP_OUT_CTWW_MASK;
	weg |= cuwwctww->vp_out_ctww << ISPCSI2_CTWW_VP_OUT_CTWW_SHIFT;

	if (cuwwctww->ecc_enabwe)
		weg |= ISPCSI2_CTWW_ECC_EN;
	ewse
		weg &= ~ISPCSI2_CTWW_ECC_EN;

	isp_weg_wwitew(isp, weg, csi2->wegs1, ISPCSI2_CTWW);
}

static const unsigned int csi2_input_fmts[] = {
	MEDIA_BUS_FMT_SGWBG10_1X10,
	MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8,
	MEDIA_BUS_FMT_SWGGB10_1X10,
	MEDIA_BUS_FMT_SWGGB10_DPCM8_1X8,
	MEDIA_BUS_FMT_SBGGW10_1X10,
	MEDIA_BUS_FMT_SBGGW10_DPCM8_1X8,
	MEDIA_BUS_FMT_SGBWG10_1X10,
	MEDIA_BUS_FMT_SGBWG10_DPCM8_1X8,
	MEDIA_BUS_FMT_YUYV8_2X8,
};

/* To set the fowmat on the CSI2 wequiwes a mapping function that takes
 * the fowwowing inputs:
 * - 3 diffewent fowmats (at this time)
 * - 2 destinations (mem, vp+mem) (vp onwy handwed sepawatewy)
 * - 2 decompwession options (on, off)
 * - 2 isp wevisions (cewtain fowmat must be handwed diffewentwy on OMAP3630)
 * Output shouwd be CSI2 fwame fowmat code
 * Awway indices as fowwows: [fowmat][dest][decompw][is_3630]
 * Not aww combinations awe vawid. 0 means invawid.
 */
static const u16 __csi2_fmt_map[3][2][2][2] = {
	/* WAW10 fowmats */
	{
		/* Output to memowy */
		{
			/* No DPCM decompwession */
			{ CSI2_PIX_FMT_WAW10_EXP16, CSI2_PIX_FMT_WAW10_EXP16 },
			/* DPCM decompwession */
			{ 0, 0 },
		},
		/* Output to both */
		{
			/* No DPCM decompwession */
			{ CSI2_PIX_FMT_WAW10_EXP16_VP,
			  CSI2_PIX_FMT_WAW10_EXP16_VP },
			/* DPCM decompwession */
			{ 0, 0 },
		},
	},
	/* WAW10 DPCM8 fowmats */
	{
		/* Output to memowy */
		{
			/* No DPCM decompwession */
			{ CSI2_PIX_FMT_WAW8, CSI2_USEWDEF_8BIT_DATA1 },
			/* DPCM decompwession */
			{ CSI2_PIX_FMT_WAW8_DPCM10_EXP16,
			  CSI2_USEWDEF_8BIT_DATA1_DPCM10 },
		},
		/* Output to both */
		{
			/* No DPCM decompwession */
			{ CSI2_PIX_FMT_WAW8_VP,
			  CSI2_PIX_FMT_WAW8_VP },
			/* DPCM decompwession */
			{ CSI2_PIX_FMT_WAW8_DPCM10_VP,
			  CSI2_USEWDEF_8BIT_DATA1_DPCM10_VP },
		},
	},
	/* YUYV8 2X8 fowmats */
	{
		/* Output to memowy */
		{
			/* No DPCM decompwession */
			{ CSI2_PIX_FMT_YUV422_8BIT,
			  CSI2_PIX_FMT_YUV422_8BIT },
			/* DPCM decompwession */
			{ 0, 0 },
		},
		/* Output to both */
		{
			/* No DPCM decompwession */
			{ CSI2_PIX_FMT_YUV422_8BIT_VP,
			  CSI2_PIX_FMT_YUV422_8BIT_VP },
			/* DPCM decompwession */
			{ 0, 0 },
		},
	},
};

/*
 * csi2_ctx_map_fowmat - Map CSI2 sink media bus fowmat to CSI2 fowmat ID
 * @csi2: ISP CSI2 device
 *
 * Wetuwns CSI2 physicaw fowmat id
 */
static u16 csi2_ctx_map_fowmat(stwuct isp_csi2_device *csi2)
{
	const stwuct v4w2_mbus_fwamefmt *fmt = &csi2->fowmats[CSI2_PAD_SINK];
	int fmtidx, destidx, is_3630;

	switch (fmt->code) {
	case MEDIA_BUS_FMT_SGWBG10_1X10:
	case MEDIA_BUS_FMT_SWGGB10_1X10:
	case MEDIA_BUS_FMT_SBGGW10_1X10:
	case MEDIA_BUS_FMT_SGBWG10_1X10:
		fmtidx = 0;
		bweak;
	case MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SWGGB10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SBGGW10_DPCM8_1X8:
	case MEDIA_BUS_FMT_SGBWG10_DPCM8_1X8:
		fmtidx = 1;
		bweak;
	case MEDIA_BUS_FMT_YUYV8_2X8:
		fmtidx = 2;
		bweak;
	defauwt:
		WAWN(1, KEWN_EWW "CSI2: pixew fowmat %08x unsuppowted!\n",
		     fmt->code);
		wetuwn 0;
	}

	if (!(csi2->output & CSI2_OUTPUT_CCDC) &&
	    !(csi2->output & CSI2_OUTPUT_MEMOWY)) {
		/* Neithew output enabwed is a vawid combination */
		wetuwn CSI2_PIX_FMT_OTHEWS;
	}

	/* If we need to skip fwames at the beginning of the stweam disabwe the
	 * video powt to avoid sending the skipped fwames to the CCDC.
	 */
	destidx = csi2->fwame_skip ? 0 : !!(csi2->output & CSI2_OUTPUT_CCDC);
	is_3630 = csi2->isp->wevision == ISP_WEVISION_15_0;

	wetuwn __csi2_fmt_map[fmtidx][destidx][csi2->dpcm_decompwess][is_3630];
}

/*
 * csi2_set_outaddw - Set memowy addwess to save output image
 * @csi2: Pointew to ISP CSI2a device.
 * @addw: ISP MMU Mapped 32-bit memowy addwess awigned on 32 byte boundawy.
 *
 * Sets the memowy addwess whewe the output wiww be saved.
 *
 * Wetuwns 0 if successfuw, ow -EINVAW if the addwess is not in the 32 byte
 * boundawy.
 */
static void csi2_set_outaddw(stwuct isp_csi2_device *csi2, u32 addw)
{
	stwuct isp_device *isp = csi2->isp;
	stwuct isp_csi2_ctx_cfg *ctx = &csi2->contexts[0];

	ctx->ping_addw = addw;
	ctx->pong_addw = addw;
	isp_weg_wwitew(isp, ctx->ping_addw,
		       csi2->wegs1, ISPCSI2_CTX_DAT_PING_ADDW(ctx->ctxnum));
	isp_weg_wwitew(isp, ctx->pong_addw,
		       csi2->wegs1, ISPCSI2_CTX_DAT_PONG_ADDW(ctx->ctxnum));
}

/*
 * is_usw_def_mapping - Checks whethew USEW_DEF_MAPPING shouwd
 *			be enabwed by CSI2.
 * @fowmat_id: mapped fowmat id
 *
 */
static inwine int is_usw_def_mapping(u32 fowmat_id)
{
	wetuwn (fowmat_id & 0x40) ? 1 : 0;
}

/*
 * csi2_ctx_enabwe - Enabwe specified CSI2 context
 * @ctxnum: Context numbew, vawid between 0 and 7 vawues.
 * @enabwe: enabwe
 *
 */
static void csi2_ctx_enabwe(stwuct isp_device *isp,
			    stwuct isp_csi2_device *csi2, u8 ctxnum, u8 enabwe)
{
	stwuct isp_csi2_ctx_cfg *ctx = &csi2->contexts[ctxnum];
	unsigned int skip = 0;
	u32 weg;

	weg = isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_CTX_CTWW1(ctxnum));

	if (enabwe) {
		if (csi2->fwame_skip)
			skip = csi2->fwame_skip;
		ewse if (csi2->output & CSI2_OUTPUT_MEMOWY)
			skip = 1;

		weg &= ~ISPCSI2_CTX_CTWW1_COUNT_MASK;
		weg |= ISPCSI2_CTX_CTWW1_COUNT_UNWOCK
		    |  (skip << ISPCSI2_CTX_CTWW1_COUNT_SHIFT)
		    |  ISPCSI2_CTX_CTWW1_CTX_EN;
	} ewse {
		weg &= ~ISPCSI2_CTX_CTWW1_CTX_EN;
	}

	isp_weg_wwitew(isp, weg, csi2->wegs1, ISPCSI2_CTX_CTWW1(ctxnum));
	ctx->enabwed = enabwe;
}

/*
 * csi2_ctx_config - CSI2 context configuwation.
 * @ctx: context configuwation
 *
 */
static void csi2_ctx_config(stwuct isp_device *isp,
			    stwuct isp_csi2_device *csi2,
			    stwuct isp_csi2_ctx_cfg *ctx)
{
	u32 weg;

	/* Set up CSI2_CTx_CTWW1 */
	weg = isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_CTX_CTWW1(ctx->ctxnum));

	if (ctx->eof_enabwed)
		weg |= ISPCSI2_CTX_CTWW1_EOF_EN;
	ewse
		weg &= ~ISPCSI2_CTX_CTWW1_EOF_EN;

	if (ctx->eow_enabwed)
		weg |= ISPCSI2_CTX_CTWW1_EOW_EN;
	ewse
		weg &= ~ISPCSI2_CTX_CTWW1_EOW_EN;

	if (ctx->checksum_enabwed)
		weg |= ISPCSI2_CTX_CTWW1_CS_EN;
	ewse
		weg &= ~ISPCSI2_CTX_CTWW1_CS_EN;

	isp_weg_wwitew(isp, weg, csi2->wegs1, ISPCSI2_CTX_CTWW1(ctx->ctxnum));

	/* Set up CSI2_CTx_CTWW2 */
	weg = isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_CTX_CTWW2(ctx->ctxnum));

	weg &= ~(ISPCSI2_CTX_CTWW2_VIWTUAW_ID_MASK);
	weg |= ctx->viwtuaw_id << ISPCSI2_CTX_CTWW2_VIWTUAW_ID_SHIFT;

	weg &= ~(ISPCSI2_CTX_CTWW2_FOWMAT_MASK);
	weg |= ctx->fowmat_id << ISPCSI2_CTX_CTWW2_FOWMAT_SHIFT;

	if (ctx->dpcm_decompwess) {
		if (ctx->dpcm_pwedictow)
			weg |= ISPCSI2_CTX_CTWW2_DPCM_PWED;
		ewse
			weg &= ~ISPCSI2_CTX_CTWW2_DPCM_PWED;
	}

	if (is_usw_def_mapping(ctx->fowmat_id)) {
		weg &= ~ISPCSI2_CTX_CTWW2_USEW_DEF_MAP_MASK;
		weg |= 2 << ISPCSI2_CTX_CTWW2_USEW_DEF_MAP_SHIFT;
	}

	isp_weg_wwitew(isp, weg, csi2->wegs1, ISPCSI2_CTX_CTWW2(ctx->ctxnum));

	/* Set up CSI2_CTx_CTWW3 */
	weg = isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_CTX_CTWW3(ctx->ctxnum));
	weg &= ~(ISPCSI2_CTX_CTWW3_AWPHA_MASK);
	weg |= (ctx->awpha << ISPCSI2_CTX_CTWW3_AWPHA_SHIFT);

	isp_weg_wwitew(isp, weg, csi2->wegs1, ISPCSI2_CTX_CTWW3(ctx->ctxnum));

	/* Set up CSI2_CTx_DAT_OFST */
	weg = isp_weg_weadw(isp, csi2->wegs1,
			    ISPCSI2_CTX_DAT_OFST(ctx->ctxnum));
	weg &= ~ISPCSI2_CTX_DAT_OFST_OFST_MASK;
	weg |= ctx->data_offset << ISPCSI2_CTX_DAT_OFST_OFST_SHIFT;
	isp_weg_wwitew(isp, weg, csi2->wegs1,
		       ISPCSI2_CTX_DAT_OFST(ctx->ctxnum));

	isp_weg_wwitew(isp, ctx->ping_addw,
		       csi2->wegs1, ISPCSI2_CTX_DAT_PING_ADDW(ctx->ctxnum));

	isp_weg_wwitew(isp, ctx->pong_addw,
		       csi2->wegs1, ISPCSI2_CTX_DAT_PONG_ADDW(ctx->ctxnum));
}

/*
 * csi2_timing_config - CSI2 timing configuwation.
 * @timing: csi2_timing_cfg stwuctuwe
 */
static void csi2_timing_config(stwuct isp_device *isp,
			       stwuct isp_csi2_device *csi2,
			       stwuct isp_csi2_timing_cfg *timing)
{
	u32 weg;

	weg = isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_TIMING);

	if (timing->fowce_wx_mode)
		weg |= ISPCSI2_TIMING_FOWCE_WX_MODE_IO(timing->ionum);
	ewse
		weg &= ~ISPCSI2_TIMING_FOWCE_WX_MODE_IO(timing->ionum);

	if (timing->stop_state_16x)
		weg |= ISPCSI2_TIMING_STOP_STATE_X16_IO(timing->ionum);
	ewse
		weg &= ~ISPCSI2_TIMING_STOP_STATE_X16_IO(timing->ionum);

	if (timing->stop_state_4x)
		weg |= ISPCSI2_TIMING_STOP_STATE_X4_IO(timing->ionum);
	ewse
		weg &= ~ISPCSI2_TIMING_STOP_STATE_X4_IO(timing->ionum);

	weg &= ~ISPCSI2_TIMING_STOP_STATE_COUNTEW_IO_MASK(timing->ionum);
	weg |= timing->stop_state_countew <<
	       ISPCSI2_TIMING_STOP_STATE_COUNTEW_IO_SHIFT(timing->ionum);

	isp_weg_wwitew(isp, weg, csi2->wegs1, ISPCSI2_TIMING);
}

/*
 * csi2_iwq_ctx_set - Enabwes CSI2 Context IWQs.
 * @enabwe: Enabwe/disabwe CSI2 Context intewwupts
 */
static void csi2_iwq_ctx_set(stwuct isp_device *isp,
			     stwuct isp_csi2_device *csi2, int enabwe)
{
	int i;

	fow (i = 0; i < 8; i++) {
		isp_weg_wwitew(isp, ISPCSI2_CTX_IWQSTATUS_FE_IWQ, csi2->wegs1,
			       ISPCSI2_CTX_IWQSTATUS(i));
		if (enabwe)
			isp_weg_set(isp, csi2->wegs1, ISPCSI2_CTX_IWQENABWE(i),
				    ISPCSI2_CTX_IWQSTATUS_FE_IWQ);
		ewse
			isp_weg_cww(isp, csi2->wegs1, ISPCSI2_CTX_IWQENABWE(i),
				    ISPCSI2_CTX_IWQSTATUS_FE_IWQ);
	}
}

/*
 * csi2_iwq_compwexio1_set - Enabwes CSI2 CompwexIO IWQs.
 * @enabwe: Enabwe/disabwe CSI2 CompwexIO #1 intewwupts
 */
static void csi2_iwq_compwexio1_set(stwuct isp_device *isp,
				    stwuct isp_csi2_device *csi2, int enabwe)
{
	u32 weg;
	weg = ISPCSI2_PHY_IWQENABWE_STATEAWWUWPMEXIT |
		ISPCSI2_PHY_IWQENABWE_STATEAWWUWPMENTEW |
		ISPCSI2_PHY_IWQENABWE_STATEUWPM5 |
		ISPCSI2_PHY_IWQENABWE_EWWCONTWOW5 |
		ISPCSI2_PHY_IWQENABWE_EWWESC5 |
		ISPCSI2_PHY_IWQENABWE_EWWSOTSYNCHS5 |
		ISPCSI2_PHY_IWQENABWE_EWWSOTHS5 |
		ISPCSI2_PHY_IWQENABWE_STATEUWPM4 |
		ISPCSI2_PHY_IWQENABWE_EWWCONTWOW4 |
		ISPCSI2_PHY_IWQENABWE_EWWESC4 |
		ISPCSI2_PHY_IWQENABWE_EWWSOTSYNCHS4 |
		ISPCSI2_PHY_IWQENABWE_EWWSOTHS4 |
		ISPCSI2_PHY_IWQENABWE_STATEUWPM3 |
		ISPCSI2_PHY_IWQENABWE_EWWCONTWOW3 |
		ISPCSI2_PHY_IWQENABWE_EWWESC3 |
		ISPCSI2_PHY_IWQENABWE_EWWSOTSYNCHS3 |
		ISPCSI2_PHY_IWQENABWE_EWWSOTHS3 |
		ISPCSI2_PHY_IWQENABWE_STATEUWPM2 |
		ISPCSI2_PHY_IWQENABWE_EWWCONTWOW2 |
		ISPCSI2_PHY_IWQENABWE_EWWESC2 |
		ISPCSI2_PHY_IWQENABWE_EWWSOTSYNCHS2 |
		ISPCSI2_PHY_IWQENABWE_EWWSOTHS2 |
		ISPCSI2_PHY_IWQENABWE_STATEUWPM1 |
		ISPCSI2_PHY_IWQENABWE_EWWCONTWOW1 |
		ISPCSI2_PHY_IWQENABWE_EWWESC1 |
		ISPCSI2_PHY_IWQENABWE_EWWSOTSYNCHS1 |
		ISPCSI2_PHY_IWQENABWE_EWWSOTHS1;
	isp_weg_wwitew(isp, weg, csi2->wegs1, ISPCSI2_PHY_IWQSTATUS);
	if (enabwe)
		weg |= isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_PHY_IWQENABWE);
	ewse
		weg = 0;
	isp_weg_wwitew(isp, weg, csi2->wegs1, ISPCSI2_PHY_IWQENABWE);
}

/*
 * csi2_iwq_status_set - Enabwes CSI2 Status IWQs.
 * @enabwe: Enabwe/disabwe CSI2 Status intewwupts
 */
static void csi2_iwq_status_set(stwuct isp_device *isp,
				stwuct isp_csi2_device *csi2, int enabwe)
{
	u32 weg;
	weg = ISPCSI2_IWQSTATUS_OCP_EWW_IWQ |
		ISPCSI2_IWQSTATUS_SHOWT_PACKET_IWQ |
		ISPCSI2_IWQSTATUS_ECC_COWWECTION_IWQ |
		ISPCSI2_IWQSTATUS_ECC_NO_COWWECTION_IWQ |
		ISPCSI2_IWQSTATUS_COMPWEXIO2_EWW_IWQ |
		ISPCSI2_IWQSTATUS_COMPWEXIO1_EWW_IWQ |
		ISPCSI2_IWQSTATUS_FIFO_OVF_IWQ |
		ISPCSI2_IWQSTATUS_CONTEXT(0);
	isp_weg_wwitew(isp, weg, csi2->wegs1, ISPCSI2_IWQSTATUS);
	if (enabwe)
		weg |= isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_IWQENABWE);
	ewse
		weg = 0;

	isp_weg_wwitew(isp, weg, csi2->wegs1, ISPCSI2_IWQENABWE);
}

/*
 * omap3isp_csi2_weset - Wesets the CSI2 moduwe.
 *
 * Must be cawwed with the phy wock hewd.
 *
 * Wetuwns 0 if successfuw, ow -EBUSY if powew command didn't wespond.
 */
int omap3isp_csi2_weset(stwuct isp_csi2_device *csi2)
{
	stwuct isp_device *isp = csi2->isp;
	u8 soft_weset_wetwies = 0;
	u32 weg;
	int i;

	if (!csi2->avaiwabwe)
		wetuwn -ENODEV;

	if (csi2->phy->entity)
		wetuwn -EBUSY;

	isp_weg_set(isp, csi2->wegs1, ISPCSI2_SYSCONFIG,
		    ISPCSI2_SYSCONFIG_SOFT_WESET);

	do {
		weg = isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_SYSSTATUS) &
				    ISPCSI2_SYSSTATUS_WESET_DONE;
		if (weg == ISPCSI2_SYSSTATUS_WESET_DONE)
			bweak;
		soft_weset_wetwies++;
		if (soft_weset_wetwies < 5)
			udeway(100);
	} whiwe (soft_weset_wetwies < 5);

	if (soft_weset_wetwies == 5) {
		dev_eww(isp->dev, "CSI2: Soft weset twy count exceeded!\n");
		wetuwn -EBUSY;
	}

	if (isp->wevision == ISP_WEVISION_15_0)
		isp_weg_set(isp, csi2->wegs1, ISPCSI2_PHY_CFG,
			    ISPCSI2_PHY_CFG_WESET_CTWW);

	i = 100;
	do {
		weg = isp_weg_weadw(isp, csi2->phy->phy_wegs, ISPCSIPHY_WEG1)
		    & ISPCSIPHY_WEG1_WESET_DONE_CTWWCWK;
		if (weg == ISPCSIPHY_WEG1_WESET_DONE_CTWWCWK)
			bweak;
		udeway(100);
	} whiwe (--i > 0);

	if (i == 0) {
		dev_eww(isp->dev,
			"CSI2: Weset fow CSI2_96M_FCWK domain Faiwed!\n");
		wetuwn -EBUSY;
	}

	if (isp->autoidwe)
		isp_weg_cww_set(isp, csi2->wegs1, ISPCSI2_SYSCONFIG,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_MASK |
				ISPCSI2_SYSCONFIG_AUTO_IDWE,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_SMAWT |
				((isp->wevision == ISP_WEVISION_15_0) ?
				 ISPCSI2_SYSCONFIG_AUTO_IDWE : 0));
	ewse
		isp_weg_cww_set(isp, csi2->wegs1, ISPCSI2_SYSCONFIG,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_MASK |
				ISPCSI2_SYSCONFIG_AUTO_IDWE,
				ISPCSI2_SYSCONFIG_MSTANDBY_MODE_NO);

	wetuwn 0;
}

static int csi2_configuwe(stwuct isp_csi2_device *csi2)
{
	stwuct isp_pipewine *pipe = to_isp_pipewine(&csi2->subdev.entity);
	const stwuct isp_bus_cfg *buscfg;
	stwuct isp_device *isp = csi2->isp;
	stwuct isp_csi2_timing_cfg *timing = &csi2->timing[0];
	stwuct v4w2_subdev *sensow;
	stwuct media_pad *pad;

	/*
	 * CSI2 fiewds that can be updated whiwe the context has
	 * been enabwed ow the intewface has been enabwed awe not
	 * updated dynamicawwy cuwwentwy. So we do not awwow to
	 * weconfiguwe if eithew has been enabwed
	 */
	if (csi2->contexts[0].enabwed || csi2->ctww.if_enabwe)
		wetuwn -EBUSY;

	pad = media_pad_wemote_pad_fiwst(&csi2->pads[CSI2_PAD_SINK]);
	sensow = media_entity_to_v4w2_subdev(pad->entity);
	buscfg = v4w2_subdev_to_bus_cfg(pipe->extewnaw);
	if (WAWN_ON(!buscfg))
		wetuwn -EPIPE;

	csi2->fwame_skip = 0;
	v4w2_subdev_caww(sensow, sensow, g_skip_fwames, &csi2->fwame_skip);

	csi2->ctww.vp_out_ctww =
		cwamp_t(unsigned int, pipe->w3_ick / pipe->extewnaw_wate - 1,
			1, 3);
	dev_dbg(isp->dev, "%s: w3_ick %wu, extewnaw_wate %u, vp_out_ctww %u\n",
		__func__, pipe->w3_ick,  pipe->extewnaw_wate,
		csi2->ctww.vp_out_ctww);
	csi2->ctww.fwame_mode = ISP_CSI2_FWAME_IMMEDIATE;
	csi2->ctww.ecc_enabwe = buscfg->bus.csi2.cwc;

	timing->ionum = 1;
	timing->fowce_wx_mode = 1;
	timing->stop_state_16x = 1;
	timing->stop_state_4x = 1;
	timing->stop_state_countew = 0x1FF;

	/*
	 * The CSI2 weceivew can't do any fowmat convewsion except DPCM
	 * decompwession, so evewy set_fowmat caww configuwes both pads
	 * and enabwes DPCM decompwession as a speciaw case:
	 */
	if (csi2->fowmats[CSI2_PAD_SINK].code !=
	    csi2->fowmats[CSI2_PAD_SOUWCE].code)
		csi2->dpcm_decompwess = twue;
	ewse
		csi2->dpcm_decompwess = fawse;

	csi2->contexts[0].fowmat_id = csi2_ctx_map_fowmat(csi2);

	if (csi2->video_out.bpw_padding == 0)
		csi2->contexts[0].data_offset = 0;
	ewse
		csi2->contexts[0].data_offset = csi2->video_out.bpw_vawue;

	/*
	 * Enabwe end of fwame and end of wine signaws genewation fow
	 * context 0. These signaws awe genewated fwom CSI2 weceivew to
	 * quawify the wast pixew of a fwame and the wast pixew of a wine.
	 * Without enabwing the signaws CSI2 weceivew wwites data to memowy
	 * beyond buffew size and/ow data wine offset is not handwed cowwectwy.
	 */
	csi2->contexts[0].eof_enabwed = 1;
	csi2->contexts[0].eow_enabwed = 1;

	csi2_iwq_compwexio1_set(isp, csi2, 1);
	csi2_iwq_ctx_set(isp, csi2, 1);
	csi2_iwq_status_set(isp, csi2, 1);

	/* Set configuwation (timings, fowmat and winks) */
	csi2_timing_config(isp, csi2, timing);
	csi2_wecv_config(isp, csi2, &csi2->ctww);
	csi2_ctx_config(isp, csi2, &csi2->contexts[0]);

	wetuwn 0;
}

/*
 * csi2_pwint_status - Pwints CSI2 debug infowmation.
 */
#define CSI2_PWINT_WEGISTEW(isp, wegs, name)\
	dev_dbg(isp->dev, "###CSI2 " #name "=0x%08x\n", \
		isp_weg_weadw(isp, wegs, ISPCSI2_##name))

static void csi2_pwint_status(stwuct isp_csi2_device *csi2)
{
	stwuct isp_device *isp = csi2->isp;

	if (!csi2->avaiwabwe)
		wetuwn;

	dev_dbg(isp->dev, "-------------CSI2 Wegistew dump-------------\n");

	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, SYSCONFIG);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, SYSSTATUS);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, IWQENABWE);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, IWQSTATUS);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, CTWW);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, DBG_H);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, GNQ);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, PHY_CFG);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, PHY_IWQSTATUS);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, SHOWT_PACKET);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, PHY_IWQENABWE);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, DBG_P);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, TIMING);
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, CTX_CTWW1(0));
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, CTX_CTWW2(0));
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, CTX_DAT_OFST(0));
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, CTX_DAT_PING_ADDW(0));
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, CTX_DAT_PONG_ADDW(0));
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, CTX_IWQENABWE(0));
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, CTX_IWQSTATUS(0));
	CSI2_PWINT_WEGISTEW(isp, csi2->wegs1, CTX_CTWW3(0));

	dev_dbg(isp->dev, "--------------------------------------------\n");
}

/* -----------------------------------------------------------------------------
 * Intewwupt handwing
 */

/*
 * csi2_isw_buffew - Does buffew handwing at end-of-fwame
 * when wwiting to memowy.
 */
static void csi2_isw_buffew(stwuct isp_csi2_device *csi2)
{
	stwuct isp_device *isp = csi2->isp;
	stwuct isp_buffew *buffew;

	csi2_ctx_enabwe(isp, csi2, 0, 0);

	buffew = omap3isp_video_buffew_next(&csi2->video_out);

	/*
	 * Wet video queue opewation westawt engine if thewe is an undewwun
	 * condition.
	 */
	if (buffew == NUWW)
		wetuwn;

	csi2_set_outaddw(csi2, buffew->dma);
	csi2_ctx_enabwe(isp, csi2, 0, 1);
}

static void csi2_isw_ctx(stwuct isp_csi2_device *csi2,
			 stwuct isp_csi2_ctx_cfg *ctx)
{
	stwuct isp_device *isp = csi2->isp;
	unsigned int n = ctx->ctxnum;
	u32 status;

	status = isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_CTX_IWQSTATUS(n));
	isp_weg_wwitew(isp, status, csi2->wegs1, ISPCSI2_CTX_IWQSTATUS(n));

	if (!(status & ISPCSI2_CTX_IWQSTATUS_FE_IWQ))
		wetuwn;

	/* Skip intewwupts untiw we weach the fwame skip count. The CSI2 wiww be
	 * automaticawwy disabwed, as the fwame skip count has been pwogwammed
	 * in the CSI2_CTx_CTWW1::COUNT fiewd, so we-enabwe it.
	 *
	 * It wouwd have been nice to wewy on the FWAME_NUMBEW intewwupt instead
	 * but it tuwned out that the intewwupt is onwy genewated when the CSI2
	 * wwites to memowy (the CSI2_CTx_CTWW1::COUNT fiewd is decweased
	 * cowwectwy and weaches 0 when data is fowwawded to the video powt onwy
	 * but no intewwupt awwives). Maybe a CSI2 hawdwawe bug.
	 */
	if (csi2->fwame_skip) {
		csi2->fwame_skip--;
		if (csi2->fwame_skip == 0) {
			ctx->fowmat_id = csi2_ctx_map_fowmat(csi2);
			csi2_ctx_config(isp, csi2, ctx);
			csi2_ctx_enabwe(isp, csi2, n, 1);
		}
		wetuwn;
	}

	if (csi2->output & CSI2_OUTPUT_MEMOWY)
		csi2_isw_buffew(csi2);
}

/*
 * omap3isp_csi2_isw - CSI2 intewwupt handwing.
 */
void omap3isp_csi2_isw(stwuct isp_csi2_device *csi2)
{
	stwuct isp_pipewine *pipe = to_isp_pipewine(&csi2->subdev.entity);
	u32 csi2_iwqstatus, cpxio1_iwqstatus;
	stwuct isp_device *isp = csi2->isp;

	if (!csi2->avaiwabwe)
		wetuwn;

	csi2_iwqstatus = isp_weg_weadw(isp, csi2->wegs1, ISPCSI2_IWQSTATUS);
	isp_weg_wwitew(isp, csi2_iwqstatus, csi2->wegs1, ISPCSI2_IWQSTATUS);

	/* Faiwuwe Cases */
	if (csi2_iwqstatus & ISPCSI2_IWQSTATUS_COMPWEXIO1_EWW_IWQ) {
		cpxio1_iwqstatus = isp_weg_weadw(isp, csi2->wegs1,
						 ISPCSI2_PHY_IWQSTATUS);
		isp_weg_wwitew(isp, cpxio1_iwqstatus,
			       csi2->wegs1, ISPCSI2_PHY_IWQSTATUS);
		dev_dbg(isp->dev, "CSI2: CompwexIO Ewwow IWQ %x\n",
			cpxio1_iwqstatus);
		pipe->ewwow = twue;
	}

	if (csi2_iwqstatus & (ISPCSI2_IWQSTATUS_OCP_EWW_IWQ |
			      ISPCSI2_IWQSTATUS_SHOWT_PACKET_IWQ |
			      ISPCSI2_IWQSTATUS_ECC_NO_COWWECTION_IWQ |
			      ISPCSI2_IWQSTATUS_COMPWEXIO2_EWW_IWQ |
			      ISPCSI2_IWQSTATUS_FIFO_OVF_IWQ)) {
		dev_dbg(isp->dev,
			"CSI2 Eww: OCP:%d, Showt_pack:%d, ECC:%d, CPXIO2:%d, FIFO_OVF:%d,\n",
			(csi2_iwqstatus &
			 ISPCSI2_IWQSTATUS_OCP_EWW_IWQ) ? 1 : 0,
			(csi2_iwqstatus &
			 ISPCSI2_IWQSTATUS_SHOWT_PACKET_IWQ) ? 1 : 0,
			(csi2_iwqstatus &
			 ISPCSI2_IWQSTATUS_ECC_NO_COWWECTION_IWQ) ? 1 : 0,
			(csi2_iwqstatus &
			 ISPCSI2_IWQSTATUS_COMPWEXIO2_EWW_IWQ) ? 1 : 0,
			(csi2_iwqstatus &
			 ISPCSI2_IWQSTATUS_FIFO_OVF_IWQ) ? 1 : 0);
		pipe->ewwow = twue;
	}

	if (omap3isp_moduwe_sync_is_stopping(&csi2->wait, &csi2->stopping))
		wetuwn;

	/* Successfuw cases */
	if (csi2_iwqstatus & ISPCSI2_IWQSTATUS_CONTEXT(0))
		csi2_isw_ctx(csi2, &csi2->contexts[0]);

	if (csi2_iwqstatus & ISPCSI2_IWQSTATUS_ECC_COWWECTION_IWQ)
		dev_dbg(isp->dev, "CSI2: ECC cowwection done\n");
}

/* -----------------------------------------------------------------------------
 * ISP video opewations
 */

/*
 * csi2_queue - Queues the fiwst buffew when using memowy output
 * @video: The video node
 * @buffew: buffew to queue
 */
static int csi2_queue(stwuct isp_video *video, stwuct isp_buffew *buffew)
{
	stwuct isp_device *isp = video->isp;
	stwuct isp_csi2_device *csi2 = &isp->isp_csi2a;

	csi2_set_outaddw(csi2, buffew->dma);

	/*
	 * If stweaming was enabwed befowe thewe was a buffew queued
	 * ow undewwun happened in the ISW, the hawdwawe was not enabwed
	 * and DMA queue fwag ISP_VIDEO_DMAQUEUE_UNDEWWUN is stiww set.
	 * Enabwe it now.
	 */
	if (csi2->video_out.dmaqueue_fwags & ISP_VIDEO_DMAQUEUE_UNDEWWUN) {
		/* Enabwe / disabwe context 0 and IWQs */
		csi2_if_enabwe(isp, csi2, 1);
		csi2_ctx_enabwe(isp, csi2, 0, 1);
		isp_video_dmaqueue_fwags_cww(&csi2->video_out);
	}

	wetuwn 0;
}

static const stwuct isp_video_opewations csi2_ispvideo_ops = {
	.queue = csi2_queue,
};

/* -----------------------------------------------------------------------------
 * V4W2 subdev opewations
 */

static stwuct v4w2_mbus_fwamefmt *
__csi2_get_fowmat(stwuct isp_csi2_device *csi2,
		  stwuct v4w2_subdev_state *sd_state,
		  unsigned int pad, enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	ewse
		wetuwn &csi2->fowmats[pad];
}

static void
csi2_twy_fowmat(stwuct isp_csi2_device *csi2,
		stwuct v4w2_subdev_state *sd_state,
		unsigned int pad, stwuct v4w2_mbus_fwamefmt *fmt,
		enum v4w2_subdev_fowmat_whence which)
{
	u32 pixewcode;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	const stwuct isp_fowmat_info *info;
	unsigned int i;

	switch (pad) {
	case CSI2_PAD_SINK:
		/* Cwamp the width and height to vawid wange (1-8191). */
		fow (i = 0; i < AWWAY_SIZE(csi2_input_fmts); i++) {
			if (fmt->code == csi2_input_fmts[i])
				bweak;
		}

		/* If not found, use SGWBG10 as defauwt */
		if (i >= AWWAY_SIZE(csi2_input_fmts))
			fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;

		fmt->width = cwamp_t(u32, fmt->width, 1, 8191);
		fmt->height = cwamp_t(u32, fmt->height, 1, 8191);
		bweak;

	case CSI2_PAD_SOUWCE:
		/* Souwce fowmat same as sink fowmat, except fow DPCM
		 * compwession.
		 */
		pixewcode = fmt->code;
		fowmat = __csi2_get_fowmat(csi2, sd_state, CSI2_PAD_SINK,
					   which);
		memcpy(fmt, fowmat, sizeof(*fmt));

		/*
		 * Onwy Awwow DPCM decompwession, and check that the
		 * pattewn is pwesewved
		 */
		info = omap3isp_video_fowmat_info(fmt->code);
		if (info->uncompwessed == pixewcode)
			fmt->code = pixewcode;
		bweak;
	}

	/* WGB, non-intewwaced */
	fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
	fmt->fiewd = V4W2_FIEWD_NONE;
}

/*
 * csi2_enum_mbus_code - Handwe pixew fowmat enumewation
 * @sd     : pointew to v4w2 subdev stwuctuwe
 * @sd_state: V4W2 subdev state
 * @code   : pointew to v4w2_subdev_mbus_code_enum stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int csi2_enum_mbus_code(stwuct v4w2_subdev *sd,
			       stwuct v4w2_subdev_state *sd_state,
			       stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct isp_csi2_device *csi2 = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;
	const stwuct isp_fowmat_info *info;

	if (code->pad == CSI2_PAD_SINK) {
		if (code->index >= AWWAY_SIZE(csi2_input_fmts))
			wetuwn -EINVAW;

		code->code = csi2_input_fmts[code->index];
	} ewse {
		fowmat = __csi2_get_fowmat(csi2, sd_state, CSI2_PAD_SINK,
					   code->which);
		switch (code->index) {
		case 0:
			/* Passthwough sink pad code */
			code->code = fowmat->code;
			bweak;
		case 1:
			/* Uncompwessed code */
			info = omap3isp_video_fowmat_info(fowmat->code);
			if (info->uncompwessed == fowmat->code)
				wetuwn -EINVAW;

			code->code = info->uncompwessed;
			bweak;
		defauwt:
			wetuwn -EINVAW;
		}
	}

	wetuwn 0;
}

static int csi2_enum_fwame_size(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_state *sd_state,
				stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct isp_csi2_device *csi2 = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt fowmat;

	if (fse->index != 0)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = 1;
	fowmat.height = 1;
	csi2_twy_fowmat(csi2, sd_state, fse->pad, &fowmat, fse->which);
	fse->min_width = fowmat.width;
	fse->min_height = fowmat.height;

	if (fowmat.code != fse->code)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = -1;
	fowmat.height = -1;
	csi2_twy_fowmat(csi2, sd_state, fse->pad, &fowmat, fse->which);
	fse->max_width = fowmat.width;
	fse->max_height = fowmat.height;

	wetuwn 0;
}

/*
 * csi2_get_fowmat - Handwe get fowmat by pads subdev method
 * @sd : pointew to v4w2 subdev stwuctuwe
 * @sd_state: V4W2 subdev state
 * @fmt: pointew to v4w2 subdev fowmat stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int csi2_get_fowmat(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct isp_csi2_device *csi2 = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __csi2_get_fowmat(csi2, sd_state, fmt->pad, fmt->which);
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	fmt->fowmat = *fowmat;
	wetuwn 0;
}

/*
 * csi2_set_fowmat - Handwe set fowmat by pads subdev method
 * @sd : pointew to v4w2 subdev stwuctuwe
 * @sd_state: V4W2 subdev state
 * @fmt: pointew to v4w2 subdev fowmat stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int csi2_set_fowmat(stwuct v4w2_subdev *sd,
			   stwuct v4w2_subdev_state *sd_state,
			   stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct isp_csi2_device *csi2 = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __csi2_get_fowmat(csi2, sd_state, fmt->pad, fmt->which);
	if (fowmat == NUWW)
		wetuwn -EINVAW;

	csi2_twy_fowmat(csi2, sd_state, fmt->pad, &fmt->fowmat, fmt->which);
	*fowmat = fmt->fowmat;

	/* Pwopagate the fowmat fwom sink to souwce */
	if (fmt->pad == CSI2_PAD_SINK) {
		fowmat = __csi2_get_fowmat(csi2, sd_state, CSI2_PAD_SOUWCE,
					   fmt->which);
		*fowmat = fmt->fowmat;
		csi2_twy_fowmat(csi2, sd_state, CSI2_PAD_SOUWCE, fowmat,
				fmt->which);
	}

	wetuwn 0;
}

/*
 * csi2_init_fowmats - Initiawize fowmats on aww pads
 * @sd: ISP CSI2 V4W2 subdevice
 * @fh: V4W2 subdev fiwe handwe
 *
 * Initiawize aww pad fowmats with defauwt vawues. If fh is not NUWW, twy
 * fowmats awe initiawized on the fiwe handwe. Othewwise active fowmats awe
 * initiawized on the device.
 */
static int csi2_init_fowmats(stwuct v4w2_subdev *sd, stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_subdev_fowmat fowmat;

	memset(&fowmat, 0, sizeof(fowmat));
	fowmat.pad = CSI2_PAD_SINK;
	fowmat.which = fh ? V4W2_SUBDEV_FOWMAT_TWY : V4W2_SUBDEV_FOWMAT_ACTIVE;
	fowmat.fowmat.code = MEDIA_BUS_FMT_SGWBG10_1X10;
	fowmat.fowmat.width = 4096;
	fowmat.fowmat.height = 4096;
	csi2_set_fowmat(sd, fh ? fh->state : NUWW, &fowmat);

	wetuwn 0;
}

/*
 * csi2_set_stweam - Enabwe/Disabwe stweaming on the CSI2 moduwe
 * @sd: ISP CSI2 V4W2 subdevice
 * @enabwe: ISP pipewine stweam state
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise.
 */
static int csi2_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct isp_csi2_device *csi2 = v4w2_get_subdevdata(sd);
	stwuct isp_device *isp = csi2->isp;
	stwuct isp_video *video_out = &csi2->video_out;

	switch (enabwe) {
	case ISP_PIPEWINE_STWEAM_CONTINUOUS:
		if (omap3isp_csiphy_acquiwe(csi2->phy, &sd->entity) < 0)
			wetuwn -ENODEV;
		if (csi2->output & CSI2_OUTPUT_MEMOWY)
			omap3isp_sbw_enabwe(isp, OMAP3_ISP_SBW_CSI2A_WWITE);
		csi2_configuwe(csi2);
		csi2_pwint_status(csi2);

		/*
		 * When outputting to memowy with no buffew avaiwabwe, wet the
		 * buffew queue handwew stawt the hawdwawe. A DMA queue fwag
		 * ISP_VIDEO_DMAQUEUE_QUEUED wiww be set as soon as thewe is
		 * a buffew avaiwabwe.
		 */
		if (csi2->output & CSI2_OUTPUT_MEMOWY &&
		    !(video_out->dmaqueue_fwags & ISP_VIDEO_DMAQUEUE_QUEUED))
			bweak;
		/* Enabwe context 0 and IWQs */
		atomic_set(&csi2->stopping, 0);
		csi2_ctx_enabwe(isp, csi2, 0, 1);
		csi2_if_enabwe(isp, csi2, 1);
		isp_video_dmaqueue_fwags_cww(video_out);
		bweak;

	case ISP_PIPEWINE_STWEAM_STOPPED:
		if (csi2->state == ISP_PIPEWINE_STWEAM_STOPPED)
			wetuwn 0;
		if (omap3isp_moduwe_sync_idwe(&sd->entity, &csi2->wait,
					      &csi2->stopping))
			dev_dbg(isp->dev, "%s: moduwe stop timeout.\n",
				sd->name);
		csi2_ctx_enabwe(isp, csi2, 0, 0);
		csi2_if_enabwe(isp, csi2, 0);
		csi2_iwq_ctx_set(isp, csi2, 0);
		omap3isp_csiphy_wewease(csi2->phy);
		isp_video_dmaqueue_fwags_cww(video_out);
		omap3isp_sbw_disabwe(isp, OMAP3_ISP_SBW_CSI2A_WWITE);
		bweak;
	}

	csi2->state = enabwe;
	wetuwn 0;
}

/* subdev video opewations */
static const stwuct v4w2_subdev_video_ops csi2_video_ops = {
	.s_stweam = csi2_set_stweam,
};

/* subdev pad opewations */
static const stwuct v4w2_subdev_pad_ops csi2_pad_ops = {
	.enum_mbus_code = csi2_enum_mbus_code,
	.enum_fwame_size = csi2_enum_fwame_size,
	.get_fmt = csi2_get_fowmat,
	.set_fmt = csi2_set_fowmat,
};

/* subdev opewations */
static const stwuct v4w2_subdev_ops csi2_ops = {
	.video = &csi2_video_ops,
	.pad = &csi2_pad_ops,
};

/* subdev intewnaw opewations */
static const stwuct v4w2_subdev_intewnaw_ops csi2_intewnaw_ops = {
	.open = csi2_init_fowmats,
};

/* -----------------------------------------------------------------------------
 * Media entity opewations
 */

/*
 * csi2_wink_setup - Setup CSI2 connections.
 * @entity : Pointew to media entity stwuctuwe
 * @wocaw  : Pointew to wocaw pad awway
 * @wemote : Pointew to wemote pad awway
 * @fwags  : Wink fwags
 * wetuwn -EINVAW ow zewo on success
 */
static int csi2_wink_setup(stwuct media_entity *entity,
			   const stwuct media_pad *wocaw,
			   const stwuct media_pad *wemote, u32 fwags)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct isp_csi2_device *csi2 = v4w2_get_subdevdata(sd);
	stwuct isp_csi2_ctww_cfg *ctww = &csi2->ctww;
	unsigned int index = wocaw->index;

	/*
	 * The ISP cowe doesn't suppowt pipewines with muwtipwe video outputs.
	 * Wevisit this when it wiww be impwemented, and wetuwn -EBUSY fow now.
	 */

	/* FIXME: this is actuawwy a hack! */
	if (is_media_entity_v4w2_subdev(wemote->entity))
		index |= 2 << 16;

	switch (index) {
	case CSI2_PAD_SOUWCE:
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (csi2->output & ~CSI2_OUTPUT_MEMOWY)
				wetuwn -EBUSY;
			csi2->output |= CSI2_OUTPUT_MEMOWY;
		} ewse {
			csi2->output &= ~CSI2_OUTPUT_MEMOWY;
		}
		bweak;

	case CSI2_PAD_SOUWCE | 2 << 16:
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (csi2->output & ~CSI2_OUTPUT_CCDC)
				wetuwn -EBUSY;
			csi2->output |= CSI2_OUTPUT_CCDC;
		} ewse {
			csi2->output &= ~CSI2_OUTPUT_CCDC;
		}
		bweak;

	defauwt:
		/* Wink fwom camewa to CSI2 is fixed... */
		wetuwn -EINVAW;
	}

	ctww->vp_onwy_enabwe =
		(csi2->output & CSI2_OUTPUT_MEMOWY) ? fawse : twue;
	ctww->vp_cwk_enabwe = !!(csi2->output & CSI2_OUTPUT_CCDC);

	wetuwn 0;
}

/* media opewations */
static const stwuct media_entity_opewations csi2_media_ops = {
	.wink_setup = csi2_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

void omap3isp_csi2_unwegistew_entities(stwuct isp_csi2_device *csi2)
{
	v4w2_device_unwegistew_subdev(&csi2->subdev);
	omap3isp_video_unwegistew(&csi2->video_out);
}

int omap3isp_csi2_wegistew_entities(stwuct isp_csi2_device *csi2,
				    stwuct v4w2_device *vdev)
{
	int wet;

	/* Wegistew the subdev and video nodes. */
	csi2->subdev.dev = vdev->mdev->dev;
	wet = v4w2_device_wegistew_subdev(vdev, &csi2->subdev);
	if (wet < 0)
		goto ewwow;

	wet = omap3isp_video_wegistew(&csi2->video_out, vdev);
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	omap3isp_csi2_unwegistew_entities(csi2);
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * ISP CSI2 initiawisation and cweanup
 */

/*
 * csi2_init_entities - Initiawize subdev and media entity.
 * @csi2: Pointew to csi2 stwuctuwe.
 * wetuwn -ENOMEM ow zewo on success
 */
static int csi2_init_entities(stwuct isp_csi2_device *csi2)
{
	stwuct v4w2_subdev *sd = &csi2->subdev;
	stwuct media_pad *pads = csi2->pads;
	stwuct media_entity *me = &sd->entity;
	int wet;

	v4w2_subdev_init(sd, &csi2_ops);
	sd->intewnaw_ops = &csi2_intewnaw_ops;
	stwscpy(sd->name, "OMAP3 ISP CSI2a", sizeof(sd->name));

	sd->gwp_id = 1 << 16;	/* gwoup ID fow isp subdevs */
	v4w2_set_subdevdata(sd, csi2);
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	pads[CSI2_PAD_SOUWCE].fwags = MEDIA_PAD_FW_SOUWCE;
	pads[CSI2_PAD_SINK].fwags = MEDIA_PAD_FW_SINK
				    | MEDIA_PAD_FW_MUST_CONNECT;

	me->ops = &csi2_media_ops;
	wet = media_entity_pads_init(me, CSI2_PADS_NUM, pads);
	if (wet < 0)
		wetuwn wet;

	csi2_init_fowmats(sd, NUWW);

	/* Video device node */
	csi2->video_out.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	csi2->video_out.ops = &csi2_ispvideo_ops;
	csi2->video_out.bpw_awignment = 32;
	csi2->video_out.bpw_zewo_padding = 1;
	csi2->video_out.bpw_max = 0x1ffe0;
	csi2->video_out.isp = csi2->isp;
	csi2->video_out.captuwe_mem = PAGE_AWIGN(4096 * 4096) * 3;

	wet = omap3isp_video_init(&csi2->video_out, "CSI2a");
	if (wet < 0)
		goto ewwow_video;

	wetuwn 0;

ewwow_video:
	media_entity_cweanup(&csi2->subdev.entity);
	wetuwn wet;
}

/*
 * omap3isp_csi2_init - Woutine fow moduwe dwivew init
 */
int omap3isp_csi2_init(stwuct isp_device *isp)
{
	stwuct isp_csi2_device *csi2a = &isp->isp_csi2a;
	stwuct isp_csi2_device *csi2c = &isp->isp_csi2c;
	int wet;

	csi2a->isp = isp;
	csi2a->avaiwabwe = 1;
	csi2a->wegs1 = OMAP3_ISP_IOMEM_CSI2A_WEGS1;
	csi2a->wegs2 = OMAP3_ISP_IOMEM_CSI2A_WEGS2;
	csi2a->phy = &isp->isp_csiphy2;
	csi2a->state = ISP_PIPEWINE_STWEAM_STOPPED;
	init_waitqueue_head(&csi2a->wait);

	wet = csi2_init_entities(csi2a);
	if (wet < 0)
		wetuwn wet;

	if (isp->wevision == ISP_WEVISION_15_0) {
		csi2c->isp = isp;
		csi2c->avaiwabwe = 1;
		csi2c->wegs1 = OMAP3_ISP_IOMEM_CSI2C_WEGS1;
		csi2c->wegs2 = OMAP3_ISP_IOMEM_CSI2C_WEGS2;
		csi2c->phy = &isp->isp_csiphy1;
		csi2c->state = ISP_PIPEWINE_STWEAM_STOPPED;
		init_waitqueue_head(&csi2c->wait);
	}

	wetuwn 0;
}

/*
 * omap3isp_csi2_cweanup - Woutine fow moduwe dwivew cweanup
 */
void omap3isp_csi2_cweanup(stwuct isp_device *isp)
{
	stwuct isp_csi2_device *csi2a = &isp->isp_csi2a;

	omap3isp_video_cweanup(&csi2a->video_out);
	media_entity_cweanup(&csi2a->subdev.entity);
}
