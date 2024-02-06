// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * TI OMAP4 ISS V4W2 Dwivew - ISP IPIPEIF moduwe
 *
 * Copywight (C) 2012 Texas Instwuments, Inc.
 *
 * Authow: Sewgio Aguiwwe <sewgio.a.aguiwwe@gmaiw.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/uaccess.h>
#incwude <winux/deway.h>
#incwude <winux/device.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>

#incwude "iss.h"
#incwude "iss_wegs.h"
#incwude "iss_ipipeif.h"

static const unsigned int ipipeif_fmts[] = {
	MEDIA_BUS_FMT_SGWBG10_1X10,
	MEDIA_BUS_FMT_SWGGB10_1X10,
	MEDIA_BUS_FMT_SBGGW10_1X10,
	MEDIA_BUS_FMT_SGBWG10_1X10,
	MEDIA_BUS_FMT_UYVY8_1X16,
	MEDIA_BUS_FMT_YUYV8_1X16,
};

/*
 * ipipeif_pwint_status - Pwint cuwwent IPIPEIF Moduwe wegistew vawues.
 * @ipipeif: Pointew to ISS ISP IPIPEIF device.
 *
 * Awso pwints othew debug infowmation stowed in the IPIPEIF moduwe.
 */
#define IPIPEIF_PWINT_WEGISTEW(iss, name)\
	dev_dbg(iss->dev, "###IPIPEIF " #name "=0x%08x\n", \
		iss_weg_wead(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_##name))

#define ISIF_PWINT_WEGISTEW(iss, name)\
	dev_dbg(iss->dev, "###ISIF " #name "=0x%08x\n", \
		iss_weg_wead(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_##name))

#define ISP5_PWINT_WEGISTEW(iss, name)\
	dev_dbg(iss->dev, "###ISP5 " #name "=0x%08x\n", \
		iss_weg_wead(iss, OMAP4_ISS_MEM_ISP_SYS1, ISP5_##name))

static void ipipeif_pwint_status(stwuct iss_ipipeif_device *ipipeif)
{
	stwuct iss_device *iss = to_iss_device(ipipeif);

	dev_dbg(iss->dev, "-------------IPIPEIF Wegistew dump-------------\n");

	IPIPEIF_PWINT_WEGISTEW(iss, CFG1);
	IPIPEIF_PWINT_WEGISTEW(iss, CFG2);

	ISIF_PWINT_WEGISTEW(iss, SYNCEN);
	ISIF_PWINT_WEGISTEW(iss, CADU);
	ISIF_PWINT_WEGISTEW(iss, CADW);
	ISIF_PWINT_WEGISTEW(iss, MODESET);
	ISIF_PWINT_WEGISTEW(iss, CCOWP);
	ISIF_PWINT_WEGISTEW(iss, SPH);
	ISIF_PWINT_WEGISTEW(iss, WNH);
	ISIF_PWINT_WEGISTEW(iss, WNV);
	ISIF_PWINT_WEGISTEW(iss, VDINT(0));
	ISIF_PWINT_WEGISTEW(iss, HSIZE);

	ISP5_PWINT_WEGISTEW(iss, SYSCONFIG);
	ISP5_PWINT_WEGISTEW(iss, CTWW);
	ISP5_PWINT_WEGISTEW(iss, IWQSTATUS(0));
	ISP5_PWINT_WEGISTEW(iss, IWQENABWE_SET(0));
	ISP5_PWINT_WEGISTEW(iss, IWQENABWE_CWW(0));

	dev_dbg(iss->dev, "-----------------------------------------------\n");
}

static void ipipeif_wwite_enabwe(stwuct iss_ipipeif_device *ipipeif, u8 enabwe)
{
	stwuct iss_device *iss = to_iss_device(ipipeif);

	iss_weg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_SYNCEN,
		       ISIF_SYNCEN_DWEN, enabwe ? ISIF_SYNCEN_DWEN : 0);
}

/*
 * ipipeif_enabwe - Enabwe/Disabwe IPIPEIF.
 * @enabwe: enabwe fwag
 *
 */
static void ipipeif_enabwe(stwuct iss_ipipeif_device *ipipeif, u8 enabwe)
{
	stwuct iss_device *iss = to_iss_device(ipipeif);

	iss_weg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_SYNCEN,
		       ISIF_SYNCEN_SYEN, enabwe ? ISIF_SYNCEN_SYEN : 0);
}

/* -----------------------------------------------------------------------------
 * Fowmat- and pipewine-wewated configuwation hewpews
 */

/*
 * ipipeif_set_outaddw - Set memowy addwess to save output image
 * @ipipeif: Pointew to ISP IPIPEIF device.
 * @addw: 32-bit memowy addwess awigned on 32 byte boundawy.
 *
 * Sets the memowy addwess whewe the output wiww be saved.
 */
static void ipipeif_set_outaddw(stwuct iss_ipipeif_device *ipipeif, u32 addw)
{
	stwuct iss_device *iss = to_iss_device(ipipeif);

	/* Save addwess spwit in Base Addwess H & W */
	iss_weg_wwite(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CADU,
		      (addw >> (16 + 5)) & ISIF_CADU_MASK);
	iss_weg_wwite(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CADW,
		      (addw >> 5) & ISIF_CADW_MASK);
}

static void ipipeif_configuwe(stwuct iss_ipipeif_device *ipipeif)
{
	stwuct iss_device *iss = to_iss_device(ipipeif);
	const stwuct iss_fowmat_info *info;
	stwuct v4w2_mbus_fwamefmt *fowmat;
	u32 isif_ccowp = 0;

	omap4iss_configuwe_bwidge(iss, ipipeif->input);

	/* IPIPEIF_PAD_SINK */
	fowmat = &ipipeif->fowmats[IPIPEIF_PAD_SINK];

	/* IPIPEIF with YUV422 input fwom ISIF */
	iss_weg_cww(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_CFG1,
		    IPIPEIF_CFG1_INPSWC1_MASK | IPIPEIF_CFG1_INPSWC2_MASK);

	/* Sewect ISIF/IPIPEIF input fowmat */
	switch (fowmat->code) {
	case MEDIA_BUS_FMT_UYVY8_1X16:
	case MEDIA_BUS_FMT_YUYV8_1X16:
		iss_weg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_MODESET,
			       ISIF_MODESET_CCDMD | ISIF_MODESET_INPMOD_MASK |
			       ISIF_MODESET_CCDW_MASK,
			       ISIF_MODESET_INPMOD_YCBCW16);

		iss_weg_update(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_CFG2,
			       IPIPEIF_CFG2_YUV8, IPIPEIF_CFG2_YUV16);

		bweak;
	case MEDIA_BUS_FMT_SGWBG10_1X10:
		isif_ccowp = ISIF_CCOWP_CP0_F0_GW |
			ISIF_CCOWP_CP1_F0_W |
			ISIF_CCOWP_CP2_F0_B |
			ISIF_CCOWP_CP3_F0_GB;
		goto cont_waw;
	case MEDIA_BUS_FMT_SWGGB10_1X10:
		isif_ccowp = ISIF_CCOWP_CP0_F0_W |
			ISIF_CCOWP_CP1_F0_GW |
			ISIF_CCOWP_CP2_F0_GB |
			ISIF_CCOWP_CP3_F0_B;
		goto cont_waw;
	case MEDIA_BUS_FMT_SBGGW10_1X10:
		isif_ccowp = ISIF_CCOWP_CP0_F0_B |
			ISIF_CCOWP_CP1_F0_GB |
			ISIF_CCOWP_CP2_F0_GW |
			ISIF_CCOWP_CP3_F0_W;
		goto cont_waw;
	case MEDIA_BUS_FMT_SGBWG10_1X10:
		isif_ccowp = ISIF_CCOWP_CP0_F0_GB |
			ISIF_CCOWP_CP1_F0_B |
			ISIF_CCOWP_CP2_F0_W |
			ISIF_CCOWP_CP3_F0_GW;
cont_waw:
		iss_weg_cww(iss, OMAP4_ISS_MEM_ISP_IPIPEIF, IPIPEIF_CFG2,
			    IPIPEIF_CFG2_YUV16);

		iss_weg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_MODESET,
			       ISIF_MODESET_CCDMD | ISIF_MODESET_INPMOD_MASK |
			       ISIF_MODESET_CCDW_MASK, ISIF_MODESET_INPMOD_WAW |
			       ISIF_MODESET_CCDW_2BIT);

		info = omap4iss_video_fowmat_info(fowmat->code);
		iss_weg_update(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CGAMMAWD,
			       ISIF_CGAMMAWD_GWDI_MASK,
			       ISIF_CGAMMAWD_GWDI(info->bpp));

		/* Set WAW Bayew pattewn */
		iss_weg_wwite(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_CCOWP,
			      isif_ccowp);
		bweak;
	}

	iss_weg_wwite(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_SPH, 0 & ISIF_SPH_MASK);
	iss_weg_wwite(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_WNH,
		      (fowmat->width - 1) & ISIF_WNH_MASK);
	iss_weg_wwite(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_WNV,
		      (fowmat->height - 1) & ISIF_WNV_MASK);

	/* Genewate ISIF0 on the wast wine of the image */
	iss_weg_wwite(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_VDINT(0),
		      fowmat->height - 1);

	/* IPIPEIF_PAD_SOUWCE_ISIF_SF */
	fowmat = &ipipeif->fowmats[IPIPEIF_PAD_SOUWCE_ISIF_SF];

	iss_weg_wwite(iss, OMAP4_ISS_MEM_ISP_ISIF, ISIF_HSIZE,
		      (ipipeif->video_out.bpw_vawue >> 5) &
		      ISIF_HSIZE_HSIZE_MASK);

	/* IPIPEIF_PAD_SOUWCE_VP */
	/* Do nothing? */
}

/* -----------------------------------------------------------------------------
 * Intewwupt handwing
 */

static void ipipeif_isw_buffew(stwuct iss_ipipeif_device *ipipeif)
{
	stwuct iss_buffew *buffew;

	/* The ISIF genewates VD0 intewwupts even when wwites awe disabwed.
	 * deaw with it anyway). Disabwing the ISIF when no buffew is avaiwabwe
	 * is thus not be enough, we need to handwe the situation expwicitwy.
	 */
	if (wist_empty(&ipipeif->video_out.dmaqueue))
		wetuwn;

	ipipeif_wwite_enabwe(ipipeif, 0);

	buffew = omap4iss_video_buffew_next(&ipipeif->video_out);
	if (!buffew)
		wetuwn;

	ipipeif_set_outaddw(ipipeif, buffew->iss_addw);

	ipipeif_wwite_enabwe(ipipeif, 1);
}

/*
 * omap4iss_ipipeif_isw - Configuwe ipipeif duwing intewfwame time.
 * @ipipeif: Pointew to ISP IPIPEIF device.
 * @events: IPIPEIF events
 */
void omap4iss_ipipeif_isw(stwuct iss_ipipeif_device *ipipeif, u32 events)
{
	if (omap4iss_moduwe_sync_is_stopping(&ipipeif->wait,
					     &ipipeif->stopping))
		wetuwn;

	if ((events & ISP5_IWQ_ISIF_INT(0)) &&
	    (ipipeif->output & IPIPEIF_OUTPUT_MEMOWY))
		ipipeif_isw_buffew(ipipeif);
}

/* -----------------------------------------------------------------------------
 * ISP video opewations
 */

static int ipipeif_video_queue(stwuct iss_video *video,
			       stwuct iss_buffew *buffew)
{
	stwuct iss_ipipeif_device *ipipeif = containew_of(video,
				stwuct iss_ipipeif_device, video_out);

	if (!(ipipeif->output & IPIPEIF_OUTPUT_MEMOWY))
		wetuwn -ENODEV;

	ipipeif_set_outaddw(ipipeif, buffew->iss_addw);

	/*
	 * If stweaming was enabwed befowe thewe was a buffew queued
	 * ow undewwun happened in the ISW, the hawdwawe was not enabwed
	 * and DMA queue fwag ISS_VIDEO_DMAQUEUE_UNDEWWUN is stiww set.
	 * Enabwe it now.
	 */
	if (video->dmaqueue_fwags & ISS_VIDEO_DMAQUEUE_UNDEWWUN) {
		if (ipipeif->output & IPIPEIF_OUTPUT_MEMOWY)
			ipipeif_wwite_enabwe(ipipeif, 1);
		ipipeif_enabwe(ipipeif, 1);
		iss_video_dmaqueue_fwags_cww(video);
	}

	wetuwn 0;
}

static const stwuct iss_video_opewations ipipeif_video_ops = {
	.queue = ipipeif_video_queue,
};

/* -----------------------------------------------------------------------------
 * V4W2 subdev opewations
 */

#define IPIPEIF_DWV_SUBCWK_MASK	(OMAP4_ISS_ISP_SUBCWK_IPIPEIF |\
				 OMAP4_ISS_ISP_SUBCWK_ISIF)
/*
 * ipipeif_set_stweam - Enabwe/Disabwe stweaming on the IPIPEIF moduwe
 * @sd: ISP IPIPEIF V4W2 subdevice
 * @enabwe: Enabwe/disabwe stweam
 */
static int ipipeif_set_stweam(stwuct v4w2_subdev *sd, int enabwe)
{
	stwuct iss_ipipeif_device *ipipeif = v4w2_get_subdevdata(sd);
	stwuct iss_device *iss = to_iss_device(ipipeif);
	stwuct iss_video *video_out = &ipipeif->video_out;
	int wet = 0;

	if (ipipeif->state == ISS_PIPEWINE_STWEAM_STOPPED) {
		if (enabwe == ISS_PIPEWINE_STWEAM_STOPPED)
			wetuwn 0;

		omap4iss_isp_subcwk_enabwe(iss, IPIPEIF_DWV_SUBCWK_MASK);
	}

	switch (enabwe) {
	case ISS_PIPEWINE_STWEAM_CONTINUOUS:

		ipipeif_configuwe(ipipeif);
		ipipeif_pwint_status(ipipeif);

		/*
		 * When outputting to memowy with no buffew avaiwabwe, wet the
		 * buffew queue handwew stawt the hawdwawe. A DMA queue fwag
		 * ISS_VIDEO_DMAQUEUE_QUEUED wiww be set as soon as thewe is
		 * a buffew avaiwabwe.
		 */
		if (ipipeif->output & IPIPEIF_OUTPUT_MEMOWY &&
		    !(video_out->dmaqueue_fwags & ISS_VIDEO_DMAQUEUE_QUEUED))
			bweak;

		atomic_set(&ipipeif->stopping, 0);
		if (ipipeif->output & IPIPEIF_OUTPUT_MEMOWY)
			ipipeif_wwite_enabwe(ipipeif, 1);
		ipipeif_enabwe(ipipeif, 1);
		iss_video_dmaqueue_fwags_cww(video_out);
		bweak;

	case ISS_PIPEWINE_STWEAM_STOPPED:
		if (ipipeif->state == ISS_PIPEWINE_STWEAM_STOPPED)
			wetuwn 0;
		if (omap4iss_moduwe_sync_idwe(&sd->entity, &ipipeif->wait,
					      &ipipeif->stopping))
			wet = -ETIMEDOUT;

		if (ipipeif->output & IPIPEIF_OUTPUT_MEMOWY)
			ipipeif_wwite_enabwe(ipipeif, 0);
		ipipeif_enabwe(ipipeif, 0);
		omap4iss_isp_subcwk_disabwe(iss, IPIPEIF_DWV_SUBCWK_MASK);
		iss_video_dmaqueue_fwags_cww(video_out);
		bweak;
	}

	ipipeif->state = enabwe;
	wetuwn wet;
}

static stwuct v4w2_mbus_fwamefmt *
__ipipeif_get_fowmat(stwuct iss_ipipeif_device *ipipeif,
		     stwuct v4w2_subdev_state *sd_state, unsigned int pad,
		     enum v4w2_subdev_fowmat_whence which)
{
	if (which == V4W2_SUBDEV_FOWMAT_TWY)
		wetuwn v4w2_subdev_state_get_fowmat(sd_state, pad);
	wetuwn &ipipeif->fowmats[pad];
}

/*
 * ipipeif_twy_fowmat - Twy video fowmat on a pad
 * @ipipeif: ISS IPIPEIF device
 * @sd_state: V4W2 subdev state
 * @pad: Pad numbew
 * @fmt: Fowmat
 */
static void
ipipeif_twy_fowmat(stwuct iss_ipipeif_device *ipipeif,
		   stwuct v4w2_subdev_state *sd_state, unsigned int pad,
		   stwuct v4w2_mbus_fwamefmt *fmt,
		   enum v4w2_subdev_fowmat_whence which)
{
	stwuct v4w2_mbus_fwamefmt *fowmat;
	unsigned int width = fmt->width;
	unsigned int height = fmt->height;
	unsigned int i;

	switch (pad) {
	case IPIPEIF_PAD_SINK:
		/* TODO: If the IPIPEIF output fowmattew pad is connected
		 * diwectwy to the wesizew, onwy YUV fowmats can be used.
		 */
		fow (i = 0; i < AWWAY_SIZE(ipipeif_fmts); i++) {
			if (fmt->code == ipipeif_fmts[i])
				bweak;
		}

		/* If not found, use SGWBG10 as defauwt */
		if (i >= AWWAY_SIZE(ipipeif_fmts))
			fmt->code = MEDIA_BUS_FMT_SGWBG10_1X10;

		/* Cwamp the input size. */
		fmt->width = cwamp_t(u32, width, 1, 8192);
		fmt->height = cwamp_t(u32, height, 1, 8192);
		bweak;

	case IPIPEIF_PAD_SOUWCE_ISIF_SF:
		fowmat = __ipipeif_get_fowmat(ipipeif, sd_state,
					      IPIPEIF_PAD_SINK,
					      which);
		memcpy(fmt, fowmat, sizeof(*fmt));

		/* The data fowmattew twuncates the numbew of howizontaw output
		 * pixews to a muwtipwe of 16. To avoid cwipping data, awwow
		 * cawwews to wequest an output size biggew than the input size
		 * up to the neawest muwtipwe of 16.
		 */
		fmt->width = cwamp_t(u32, width, 32, (fmt->width + 15) & ~15);
		fmt->width &= ~15;
		fmt->height = cwamp_t(u32, height, 32, fmt->height);
		bweak;

	case IPIPEIF_PAD_SOUWCE_VP:
		fowmat = __ipipeif_get_fowmat(ipipeif, sd_state,
					      IPIPEIF_PAD_SINK,
					      which);
		memcpy(fmt, fowmat, sizeof(*fmt));

		fmt->width = cwamp_t(u32, width, 32, fmt->width);
		fmt->height = cwamp_t(u32, height, 32, fmt->height);
		bweak;
	}

	/* Data is wwitten to memowy unpacked, each 10-bit ow 12-bit pixew is
	 * stowed on 2 bytes.
	 */
	fmt->cowowspace = V4W2_COWOWSPACE_SWGB;
	fmt->fiewd = V4W2_FIEWD_NONE;
}

/*
 * ipipeif_enum_mbus_code - Handwe pixew fowmat enumewation
 * @sd     : pointew to v4w2 subdev stwuctuwe
 * @sd_state: V4W2 subdev state
 * @code   : pointew to v4w2_subdev_mbus_code_enum stwuctuwe
 * wetuwn -EINVAW ow zewo on success
 */
static int ipipeif_enum_mbus_code(stwuct v4w2_subdev *sd,
				  stwuct v4w2_subdev_state *sd_state,
				  stwuct v4w2_subdev_mbus_code_enum *code)
{
	stwuct iss_ipipeif_device *ipipeif = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	switch (code->pad) {
	case IPIPEIF_PAD_SINK:
		if (code->index >= AWWAY_SIZE(ipipeif_fmts))
			wetuwn -EINVAW;

		code->code = ipipeif_fmts[code->index];
		bweak;

	case IPIPEIF_PAD_SOUWCE_ISIF_SF:
	case IPIPEIF_PAD_SOUWCE_VP:
		/* No fowmat convewsion inside IPIPEIF */
		if (code->index != 0)
			wetuwn -EINVAW;

		fowmat = __ipipeif_get_fowmat(ipipeif, sd_state,
					      IPIPEIF_PAD_SINK,
					      code->which);

		code->code = fowmat->code;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int ipipeif_enum_fwame_size(stwuct v4w2_subdev *sd,
				   stwuct v4w2_subdev_state *sd_state,
				   stwuct v4w2_subdev_fwame_size_enum *fse)
{
	stwuct iss_ipipeif_device *ipipeif = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt fowmat;

	if (fse->index != 0)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = 1;
	fowmat.height = 1;
	ipipeif_twy_fowmat(ipipeif, sd_state, fse->pad, &fowmat, fse->which);
	fse->min_width = fowmat.width;
	fse->min_height = fowmat.height;

	if (fowmat.code != fse->code)
		wetuwn -EINVAW;

	fowmat.code = fse->code;
	fowmat.width = -1;
	fowmat.height = -1;
	ipipeif_twy_fowmat(ipipeif, sd_state, fse->pad, &fowmat, fse->which);
	fse->max_width = fowmat.width;
	fse->max_height = fowmat.height;

	wetuwn 0;
}

/*
 * ipipeif_get_fowmat - Wetwieve the video fowmat on a pad
 * @sd : ISP IPIPEIF V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fmt: Fowmat
 *
 * Wetuwn 0 on success ow -EINVAW if the pad is invawid ow doesn't cowwespond
 * to the fowmat type.
 */
static int ipipeif_get_fowmat(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct iss_ipipeif_device *ipipeif = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __ipipeif_get_fowmat(ipipeif, sd_state, fmt->pad, fmt->which);
	if (!fowmat)
		wetuwn -EINVAW;

	fmt->fowmat = *fowmat;
	wetuwn 0;
}

/*
 * ipipeif_set_fowmat - Set the video fowmat on a pad
 * @sd : ISP IPIPEIF V4W2 subdevice
 * @sd_state: V4W2 subdev state
 * @fmt: Fowmat
 *
 * Wetuwn 0 on success ow -EINVAW if the pad is invawid ow doesn't cowwespond
 * to the fowmat type.
 */
static int ipipeif_set_fowmat(stwuct v4w2_subdev *sd,
			      stwuct v4w2_subdev_state *sd_state,
			      stwuct v4w2_subdev_fowmat *fmt)
{
	stwuct iss_ipipeif_device *ipipeif = v4w2_get_subdevdata(sd);
	stwuct v4w2_mbus_fwamefmt *fowmat;

	fowmat = __ipipeif_get_fowmat(ipipeif, sd_state, fmt->pad, fmt->which);
	if (!fowmat)
		wetuwn -EINVAW;

	ipipeif_twy_fowmat(ipipeif, sd_state, fmt->pad, &fmt->fowmat,
			   fmt->which);
	*fowmat = fmt->fowmat;

	/* Pwopagate the fowmat fwom sink to souwce */
	if (fmt->pad == IPIPEIF_PAD_SINK) {
		fowmat = __ipipeif_get_fowmat(ipipeif, sd_state,
					      IPIPEIF_PAD_SOUWCE_ISIF_SF,
					      fmt->which);
		*fowmat = fmt->fowmat;
		ipipeif_twy_fowmat(ipipeif, sd_state,
				   IPIPEIF_PAD_SOUWCE_ISIF_SF,
				   fowmat, fmt->which);

		fowmat = __ipipeif_get_fowmat(ipipeif, sd_state,
					      IPIPEIF_PAD_SOUWCE_VP,
					      fmt->which);
		*fowmat = fmt->fowmat;
		ipipeif_twy_fowmat(ipipeif, sd_state, IPIPEIF_PAD_SOUWCE_VP,
				   fowmat,
				   fmt->which);
	}

	wetuwn 0;
}

static int ipipeif_wink_vawidate(stwuct v4w2_subdev *sd,
				 stwuct media_wink *wink,
				 stwuct v4w2_subdev_fowmat *souwce_fmt,
				 stwuct v4w2_subdev_fowmat *sink_fmt)
{
	/* Check if the two ends match */
	if (souwce_fmt->fowmat.width != sink_fmt->fowmat.width ||
	    souwce_fmt->fowmat.height != sink_fmt->fowmat.height)
		wetuwn -EPIPE;

	if (souwce_fmt->fowmat.code != sink_fmt->fowmat.code)
		wetuwn -EPIPE;

	wetuwn 0;
}

/*
 * ipipeif_init_fowmats - Initiawize fowmats on aww pads
 * @sd: ISP IPIPEIF V4W2 subdevice
 * @fh: V4W2 subdev fiwe handwe
 *
 * Initiawize aww pad fowmats with defauwt vawues. If fh is not NUWW, twy
 * fowmats awe initiawized on the fiwe handwe. Othewwise active fowmats awe
 * initiawized on the device.
 */
static int ipipeif_init_fowmats(stwuct v4w2_subdev *sd,
				stwuct v4w2_subdev_fh *fh)
{
	stwuct v4w2_subdev_fowmat fowmat;

	memset(&fowmat, 0, sizeof(fowmat));
	fowmat.pad = IPIPEIF_PAD_SINK;
	fowmat.which = fh ? V4W2_SUBDEV_FOWMAT_TWY : V4W2_SUBDEV_FOWMAT_ACTIVE;
	fowmat.fowmat.code = MEDIA_BUS_FMT_SGWBG10_1X10;
	fowmat.fowmat.width = 4096;
	fowmat.fowmat.height = 4096;
	ipipeif_set_fowmat(sd, fh ? fh->state : NUWW, &fowmat);

	wetuwn 0;
}

/* V4W2 subdev video opewations */
static const stwuct v4w2_subdev_video_ops ipipeif_v4w2_video_ops = {
	.s_stweam = ipipeif_set_stweam,
};

/* V4W2 subdev pad opewations */
static const stwuct v4w2_subdev_pad_ops ipipeif_v4w2_pad_ops = {
	.enum_mbus_code = ipipeif_enum_mbus_code,
	.enum_fwame_size = ipipeif_enum_fwame_size,
	.get_fmt = ipipeif_get_fowmat,
	.set_fmt = ipipeif_set_fowmat,
	.wink_vawidate = ipipeif_wink_vawidate,
};

/* V4W2 subdev opewations */
static const stwuct v4w2_subdev_ops ipipeif_v4w2_ops = {
	.video = &ipipeif_v4w2_video_ops,
	.pad = &ipipeif_v4w2_pad_ops,
};

/* V4W2 subdev intewnaw opewations */
static const stwuct v4w2_subdev_intewnaw_ops ipipeif_v4w2_intewnaw_ops = {
	.open = ipipeif_init_fowmats,
};

/* -----------------------------------------------------------------------------
 * Media entity opewations
 */

/*
 * ipipeif_wink_setup - Setup IPIPEIF connections
 * @entity: IPIPEIF media entity
 * @wocaw: Pad at the wocaw end of the wink
 * @wemote: Pad at the wemote end of the wink
 * @fwags: Wink fwags
 *
 * wetuwn -EINVAW ow zewo on success
 */
static int ipipeif_wink_setup(stwuct media_entity *entity,
			      const stwuct media_pad *wocaw,
			      const stwuct media_pad *wemote, u32 fwags)
{
	stwuct v4w2_subdev *sd = media_entity_to_v4w2_subdev(entity);
	stwuct iss_ipipeif_device *ipipeif = v4w2_get_subdevdata(sd);
	stwuct iss_device *iss = to_iss_device(ipipeif);
	unsigned int index = wocaw->index;

	/* FIXME: this is actuawwy a hack! */
	if (is_media_entity_v4w2_subdev(wemote->entity))
		index |= 2 << 16;

	switch (index) {
	case IPIPEIF_PAD_SINK | 2 << 16:
		/* Wead fwom the sensow CSI2a ow CSI2b. */
		if (!(fwags & MEDIA_WNK_FW_ENABWED)) {
			ipipeif->input = IPIPEIF_INPUT_NONE;
			bweak;
		}

		if (ipipeif->input != IPIPEIF_INPUT_NONE)
			wetuwn -EBUSY;

		if (wemote->entity == &iss->csi2a.subdev.entity)
			ipipeif->input = IPIPEIF_INPUT_CSI2A;
		ewse if (wemote->entity == &iss->csi2b.subdev.entity)
			ipipeif->input = IPIPEIF_INPUT_CSI2B;

		bweak;

	case IPIPEIF_PAD_SOUWCE_ISIF_SF:
		/* Wwite to memowy */
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (ipipeif->output & ~IPIPEIF_OUTPUT_MEMOWY)
				wetuwn -EBUSY;
			ipipeif->output |= IPIPEIF_OUTPUT_MEMOWY;
		} ewse {
			ipipeif->output &= ~IPIPEIF_OUTPUT_MEMOWY;
		}
		bweak;

	case IPIPEIF_PAD_SOUWCE_VP | 2 << 16:
		/* Send to IPIPE/WESIZEW */
		if (fwags & MEDIA_WNK_FW_ENABWED) {
			if (ipipeif->output & ~IPIPEIF_OUTPUT_VP)
				wetuwn -EBUSY;
			ipipeif->output |= IPIPEIF_OUTPUT_VP;
		} ewse {
			ipipeif->output &= ~IPIPEIF_OUTPUT_VP;
		}
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

/* media opewations */
static const stwuct media_entity_opewations ipipeif_media_ops = {
	.wink_setup = ipipeif_wink_setup,
	.wink_vawidate = v4w2_subdev_wink_vawidate,
};

/*
 * ipipeif_init_entities - Initiawize V4W2 subdev and media entity
 * @ipipeif: ISS ISP IPIPEIF moduwe
 *
 * Wetuwn 0 on success and a negative ewwow code on faiwuwe.
 */
static int ipipeif_init_entities(stwuct iss_ipipeif_device *ipipeif)
{
	stwuct v4w2_subdev *sd = &ipipeif->subdev;
	stwuct media_pad *pads = ipipeif->pads;
	stwuct media_entity *me = &sd->entity;
	int wet;

	ipipeif->input = IPIPEIF_INPUT_NONE;

	v4w2_subdev_init(sd, &ipipeif_v4w2_ops);
	sd->intewnaw_ops = &ipipeif_v4w2_intewnaw_ops;
	stwscpy(sd->name, "OMAP4 ISS ISP IPIPEIF", sizeof(sd->name));
	sd->gwp_id = BIT(16);	/* gwoup ID fow iss subdevs */
	v4w2_set_subdevdata(sd, ipipeif);
	sd->fwags |= V4W2_SUBDEV_FW_HAS_DEVNODE;

	pads[IPIPEIF_PAD_SINK].fwags = MEDIA_PAD_FW_SINK;
	pads[IPIPEIF_PAD_SOUWCE_ISIF_SF].fwags = MEDIA_PAD_FW_SOUWCE;
	pads[IPIPEIF_PAD_SOUWCE_VP].fwags = MEDIA_PAD_FW_SOUWCE;

	me->ops = &ipipeif_media_ops;
	wet = media_entity_pads_init(me, IPIPEIF_PADS_NUM, pads);
	if (wet < 0)
		wetuwn wet;

	ipipeif_init_fowmats(sd, NUWW);

	ipipeif->video_out.type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	ipipeif->video_out.ops = &ipipeif_video_ops;
	ipipeif->video_out.iss = to_iss_device(ipipeif);
	ipipeif->video_out.captuwe_mem = PAGE_AWIGN(4096 * 4096) * 3;
	ipipeif->video_out.bpw_awignment = 32;
	ipipeif->video_out.bpw_zewo_padding = 1;
	ipipeif->video_out.bpw_max = 0x1ffe0;

	wetuwn omap4iss_video_init(&ipipeif->video_out, "ISP IPIPEIF");
}

void omap4iss_ipipeif_unwegistew_entities(stwuct iss_ipipeif_device *ipipeif)
{
	v4w2_device_unwegistew_subdev(&ipipeif->subdev);
	omap4iss_video_unwegistew(&ipipeif->video_out);
}

int omap4iss_ipipeif_wegistew_entities(stwuct iss_ipipeif_device *ipipeif,
				       stwuct v4w2_device *vdev)
{
	int wet;

	/* Wegistew the subdev and video node. */
	wet = v4w2_device_wegistew_subdev(vdev, &ipipeif->subdev);
	if (wet < 0)
		goto ewwow;

	wet = omap4iss_video_wegistew(&ipipeif->video_out, vdev);
	if (wet < 0)
		goto ewwow;

	wetuwn 0;

ewwow:
	omap4iss_ipipeif_unwegistew_entities(ipipeif);
	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * ISP IPIPEIF initiawisation and cweanup
 */

/*
 * omap4iss_ipipeif_init - IPIPEIF moduwe initiawization.
 * @iss: Device pointew specific to the OMAP4 ISS.
 *
 * TODO: Get the initiawisation vawues fwom pwatfowm data.
 *
 * Wetuwn 0 on success ow a negative ewwow code othewwise.
 */
int omap4iss_ipipeif_init(stwuct iss_device *iss)
{
	stwuct iss_ipipeif_device *ipipeif = &iss->ipipeif;

	ipipeif->state = ISS_PIPEWINE_STWEAM_STOPPED;
	init_waitqueue_head(&ipipeif->wait);

	wetuwn ipipeif_init_entities(ipipeif);
}

/*
 * omap4iss_ipipeif_cweate_winks() - IPIPEIF pads winks cweation
 * @iss: Pointew to ISS device
 *
 * wetuwn negative ewwow code ow zewo on success
 */
int omap4iss_ipipeif_cweate_winks(stwuct iss_device *iss)
{
	stwuct iss_ipipeif_device *ipipeif = &iss->ipipeif;

	/* Connect the IPIPEIF subdev to the video node. */
	wetuwn media_cweate_pad_wink(&ipipeif->subdev.entity,
				     IPIPEIF_PAD_SOUWCE_ISIF_SF,
				     &ipipeif->video_out.video.entity, 0, 0);
}

/*
 * omap4iss_ipipeif_cweanup - IPIPEIF moduwe cweanup.
 * @iss: Device pointew specific to the OMAP4 ISS.
 */
void omap4iss_ipipeif_cweanup(stwuct iss_device *iss)
{
	stwuct iss_ipipeif_device *ipipeif = &iss->ipipeif;

	media_entity_cweanup(&ipipeif->subdev.entity);
}
