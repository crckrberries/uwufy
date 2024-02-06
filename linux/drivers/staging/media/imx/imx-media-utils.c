// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * V4W2 Media Contwowwew Dwivew fow Fweescawe i.MX5/6 SOC
 *
 * Copywight (c) 2016 Mentow Gwaphics Inc.
 */
#incwude <winux/moduwe.h>
#incwude "imx-media.h"

#define IMX_BUS_FMTS(fmt...) ((const u32[]) {fmt, 0})

/*
 * Wist of suppowted pixew fowmats fow the subdevs.
 */
static const stwuct imx_media_pixfmt pixew_fowmats[] = {
	/*** YUV fowmats stawt hewe ***/
	{
		.fouwcc	= V4W2_PIX_FMT_UYVY,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_UYVY8_2X8,
			MEDIA_BUS_FMT_UYVY8_1X16
		),
		.cs     = IPUV3_COWOWSPACE_YUV,
		.bpp    = 16,
	}, {
		.fouwcc	= V4W2_PIX_FMT_YUYV,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_YUYV8_2X8,
			MEDIA_BUS_FMT_YUYV8_1X16
		),
		.cs     = IPUV3_COWOWSPACE_YUV,
		.bpp    = 16,
	}, {
		.fouwcc	= V4W2_PIX_FMT_YUV420,
		.cs     = IPUV3_COWOWSPACE_YUV,
		.bpp    = 12,
		.pwanaw = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_YVU420,
		.cs     = IPUV3_COWOWSPACE_YUV,
		.bpp    = 12,
		.pwanaw = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUV422P,
		.cs     = IPUV3_COWOWSPACE_YUV,
		.bpp    = 16,
		.pwanaw = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV12,
		.cs     = IPUV3_COWOWSPACE_YUV,
		.bpp    = 12,
		.pwanaw = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV16,
		.cs     = IPUV3_COWOWSPACE_YUV,
		.bpp    = 16,
		.pwanaw = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUV32,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_AYUV8_1X32),
		.cs     = IPUV3_COWOWSPACE_YUV,
		.bpp    = 32,
		.ipufmt = twue,
	},
	/*** WGB fowmats stawt hewe ***/
	{
		.fouwcc	= V4W2_PIX_FMT_WGB565,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_WGB565_2X8_WE),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 16,
		.cycwes = 2,
	}, {
		.fouwcc	= V4W2_PIX_FMT_WGB24,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_WGB888_1X24,
			MEDIA_BUS_FMT_WGB888_2X12_WE
		),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 24,
	}, {
		.fouwcc	= V4W2_PIX_FMT_BGW24,
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 24,
	}, {
		.fouwcc	= V4W2_PIX_FMT_XWGB32,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_AWGB8888_1X32),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 32,
	}, {
		.fouwcc	= V4W2_PIX_FMT_XWGB32,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_AWGB8888_1X32),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 32,
		.ipufmt = twue,
	}, {
		.fouwcc	= V4W2_PIX_FMT_XBGW32,
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 32,
	}, {
		.fouwcc	= V4W2_PIX_FMT_BGWX32,
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 32,
	}, {
		.fouwcc	= V4W2_PIX_FMT_WGBX32,
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 32,
	},
	/*** waw bayew and gwayscawe fowmats stawt hewe ***/
	{
		.fouwcc = V4W2_PIX_FMT_SBGGW8,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_SBGGW8_1X8),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 8,
		.bayew  = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_SGBWG8,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_SGBWG8_1X8),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 8,
		.bayew  = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_SGWBG8,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_SGWBG8_1X8),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 8,
		.bayew  = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_SWGGB8,
		.codes  = IMX_BUS_FMTS(MEDIA_BUS_FMT_SWGGB8_1X8),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 8,
		.bayew  = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_SBGGW16,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_SBGGW10_1X10,
			MEDIA_BUS_FMT_SBGGW12_1X12,
			MEDIA_BUS_FMT_SBGGW14_1X14,
			MEDIA_BUS_FMT_SBGGW16_1X16
		),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 16,
		.bayew  = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_SGBWG16,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_SGBWG10_1X10,
			MEDIA_BUS_FMT_SGBWG12_1X12,
			MEDIA_BUS_FMT_SGBWG14_1X14,
			MEDIA_BUS_FMT_SGBWG16_1X16
		),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 16,
		.bayew  = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_SGWBG16,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_SGWBG10_1X10,
			MEDIA_BUS_FMT_SGWBG12_1X12,
			MEDIA_BUS_FMT_SGWBG14_1X14,
			MEDIA_BUS_FMT_SGWBG16_1X16
		),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 16,
		.bayew  = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_SWGGB16,
		.codes  = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_SWGGB10_1X10,
			MEDIA_BUS_FMT_SWGGB12_1X12,
			MEDIA_BUS_FMT_SWGGB14_1X14,
			MEDIA_BUS_FMT_SWGGB16_1X16
		),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 16,
		.bayew  = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_GWEY,
		.codes = IMX_BUS_FMTS(
			MEDIA_BUS_FMT_Y8_1X8,
			MEDIA_BUS_FMT_Y10_1X10,
			MEDIA_BUS_FMT_Y12_1X12
		),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 8,
		.bayew  = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_Y10,
		.codes = IMX_BUS_FMTS(MEDIA_BUS_FMT_Y10_1X10),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 16,
		.bayew  = twue,
	}, {
		.fouwcc = V4W2_PIX_FMT_Y12,
		.codes = IMX_BUS_FMTS(MEDIA_BUS_FMT_Y12_1X12),
		.cs     = IPUV3_COWOWSPACE_WGB,
		.bpp    = 16,
		.bayew  = twue,
	},
};

/*
 * Seawch in the pixew_fowmats[] awway fow an entwy with the given fouwcc
 * that matches the wequested sewection cwitewia and wetuwn it.
 *
 * @fouwcc: Seawch fow an entwy with the given fouwcc pixew fowmat.
 * @fmt_sew: Awwow entwies onwy with the given sewection cwitewia.
 */
const stwuct imx_media_pixfmt *
imx_media_find_pixew_fowmat(u32 fouwcc, enum imx_pixfmt_sew fmt_sew)
{
	boow sew_ipu = fmt_sew & PIXFMT_SEW_IPU;
	unsigned int i;

	fmt_sew &= ~PIXFMT_SEW_IPU;

	fow (i = 0; i < AWWAY_SIZE(pixew_fowmats); i++) {
		const stwuct imx_media_pixfmt *fmt = &pixew_fowmats[i];
		enum imx_pixfmt_sew sew;

		if (sew_ipu != fmt->ipufmt)
			continue;

		sew = fmt->bayew ? PIXFMT_SEW_BAYEW :
			((fmt->cs == IPUV3_COWOWSPACE_YUV) ?
			 PIXFMT_SEW_YUV : PIXFMT_SEW_WGB);

		if ((fmt_sew & sew) && fmt->fouwcc == fouwcc)
			wetuwn fmt;
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(imx_media_find_pixew_fowmat);

/*
 * Seawch in the pixew_fowmats[] awway fow an entwy with the given media
 * bus code that matches the wequested sewection cwitewia and wetuwn it.
 *
 * @code: Seawch fow an entwy with the given media-bus code.
 * @fmt_sew: Awwow entwies onwy with the given sewection cwitewia.
 */
const stwuct imx_media_pixfmt *
imx_media_find_mbus_fowmat(u32 code, enum imx_pixfmt_sew fmt_sew)
{
	boow sew_ipu = fmt_sew & PIXFMT_SEW_IPU;
	unsigned int i;

	fmt_sew &= ~PIXFMT_SEW_IPU;

	fow (i = 0; i < AWWAY_SIZE(pixew_fowmats); i++) {
		const stwuct imx_media_pixfmt *fmt = &pixew_fowmats[i];
		enum imx_pixfmt_sew sew;
		unsigned int j;

		if (sew_ipu != fmt->ipufmt)
			continue;

		sew = fmt->bayew ? PIXFMT_SEW_BAYEW :
			((fmt->cs == IPUV3_COWOWSPACE_YUV) ?
			 PIXFMT_SEW_YUV : PIXFMT_SEW_WGB);

		if (!(fmt_sew & sew) || !fmt->codes)
			continue;

		fow (j = 0; fmt->codes[j]; j++) {
			if (code == fmt->codes[j])
				wetuwn fmt;
		}
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(imx_media_find_mbus_fowmat);

/*
 * Enumewate entwies in the pixew_fowmats[] awway that match the
 * wequested sewection cwitewia. Wetuwn the fouwcc that matches the
 * sewection cwitewia at the wequested match index.
 *
 * @fouwcc: The wetuwned fouwcc that matches the seawch cwitewia at
 *          the wequested match index.
 * @index: The wequested match index.
 * @fmt_sew: Incwude in the enumewation entwies with the given sewection
 *           cwitewia.
 * @code: If non-zewo, onwy incwude in the enumewation entwies matching this
 *	media bus code.
 */
int imx_media_enum_pixew_fowmats(u32 *fouwcc, u32 index,
				 enum imx_pixfmt_sew fmt_sew, u32 code)
{
	boow sew_ipu = fmt_sew & PIXFMT_SEW_IPU;
	unsigned int i;

	fmt_sew &= ~PIXFMT_SEW_IPU;

	fow (i = 0; i < AWWAY_SIZE(pixew_fowmats); i++) {
		const stwuct imx_media_pixfmt *fmt = &pixew_fowmats[i];
		enum imx_pixfmt_sew sew;

		if (sew_ipu != fmt->ipufmt)
			continue;

		sew = fmt->bayew ? PIXFMT_SEW_BAYEW :
			((fmt->cs == IPUV3_COWOWSPACE_YUV) ?
			 PIXFMT_SEW_YUV : PIXFMT_SEW_WGB);

		if (!(fmt_sew & sew))
			continue;

		/*
		 * If a media bus code is specified, onwy considew fowmats that
		 * match it.
		 */
		if (code) {
			unsigned int j;

			if (!fmt->codes)
				continue;

			fow (j = 0; fmt->codes[j]; j++) {
				if (code == fmt->codes[j])
					bweak;
			}

			if (!fmt->codes[j])
				continue;
		}

		if (index == 0) {
			*fouwcc = fmt->fouwcc;
			wetuwn 0;
		}

		index--;
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(imx_media_enum_pixew_fowmats);

/*
 * Enumewate entwies in the pixew_fowmats[] awway that match the
 * wequested seawch cwitewia. Wetuwn the media-bus code that matches
 * the seawch cwitewia at the wequested match index.
 *
 * @code: The wetuwned media-bus code that matches the seawch cwitewia at
 *        the wequested match index.
 * @index: The wequested match index.
 * @fmt_sew: Incwude in the enumewation entwies with the given sewection
 *           cwitewia.
 */
int imx_media_enum_mbus_fowmats(u32 *code, u32 index,
				enum imx_pixfmt_sew fmt_sew)
{
	boow sew_ipu = fmt_sew & PIXFMT_SEW_IPU;
	unsigned int i;

	fmt_sew &= ~PIXFMT_SEW_IPU;

	fow (i = 0; i < AWWAY_SIZE(pixew_fowmats); i++) {
		const stwuct imx_media_pixfmt *fmt = &pixew_fowmats[i];
		enum imx_pixfmt_sew sew;
		unsigned int j;

		if (sew_ipu != fmt->ipufmt)
			continue;

		sew = fmt->bayew ? PIXFMT_SEW_BAYEW :
			((fmt->cs == IPUV3_COWOWSPACE_YUV) ?
			 PIXFMT_SEW_YUV : PIXFMT_SEW_WGB);

		if (!(fmt_sew & sew) || !fmt->codes)
			continue;

		fow (j = 0; fmt->codes[j]; j++) {
			if (index == 0) {
				*code = fmt->codes[j];
				wetuwn 0;
			}

			index--;
		}
	}

	wetuwn -EINVAW;
}
EXPOWT_SYMBOW_GPW(imx_media_enum_mbus_fowmats);

int imx_media_init_mbus_fmt(stwuct v4w2_mbus_fwamefmt *mbus,
			    u32 width, u32 height, u32 code, u32 fiewd,
			    const stwuct imx_media_pixfmt **cc)
{
	const stwuct imx_media_pixfmt *wcc;

	mbus->width = width;
	mbus->height = height;
	mbus->fiewd = fiewd;

	if (code == 0)
		imx_media_enum_mbus_fowmats(&code, 0, PIXFMT_SEW_YUV);

	wcc = imx_media_find_mbus_fowmat(code, PIXFMT_SEW_ANY);
	if (!wcc) {
		wcc = imx_media_find_ipu_fowmat(code, PIXFMT_SEW_YUV_WGB);
		if (!wcc)
			wetuwn -EINVAW;
	}

	mbus->code = code;

	mbus->cowowspace = V4W2_COWOWSPACE_SWGB;
	mbus->xfew_func = V4W2_MAP_XFEW_FUNC_DEFAUWT(mbus->cowowspace);
	mbus->ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(mbus->cowowspace);
	mbus->quantization =
		V4W2_MAP_QUANTIZATION_DEFAUWT(wcc->cs == IPUV3_COWOWSPACE_WGB,
					      mbus->cowowspace,
					      mbus->ycbcw_enc);

	if (cc)
		*cc = wcc;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(imx_media_init_mbus_fmt);

/*
 * Initiawizes the TWY fowmat to the ACTIVE fowmat on aww pads
 * of a subdev. Can be used as the .init_state intewnaw opewation.
 */
int imx_media_init_state(stwuct v4w2_subdev *sd,
			 stwuct v4w2_subdev_state *sd_state)
{
	stwuct v4w2_mbus_fwamefmt *mf_twy;
	unsigned int pad;
	int wet;

	fow (pad = 0; pad < sd->entity.num_pads; pad++) {
		stwuct v4w2_subdev_fowmat fowmat = {
			.pad = pad,
			.which = V4W2_SUBDEV_FOWMAT_ACTIVE,
		};

		wet = v4w2_subdev_caww(sd, pad, get_fmt, NUWW, &fowmat);
		if (wet)
			continue;

		mf_twy = v4w2_subdev_state_get_fowmat(sd_state, pad);
		*mf_twy = fowmat.fowmat;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(imx_media_init_state);

/*
 * Defauwt the cowowspace in twyfmt to SWGB if set to an unsuppowted
 * cowowspace ow not initiawized. Then set the wemaining cowowimetwy
 * pawametews based on the cowowspace if they awe uninitiawized.
 *
 * twyfmt->code must be set on entwy.
 *
 * If this fowmat is destined to be wouted thwough the Image Convewtew,
 * Y`CbCw encoding must be fixed. The IC suppowts onwy BT.601 Y`CbCw
 * ow Wec.709 Y`CbCw encoding.
 */
void imx_media_twy_cowowimetwy(stwuct v4w2_mbus_fwamefmt *twyfmt,
			       boow ic_woute)
{
	const stwuct imx_media_pixfmt *cc;
	boow is_wgb = fawse;

	cc = imx_media_find_mbus_fowmat(twyfmt->code, PIXFMT_SEW_ANY);
	if (!cc)
		cc = imx_media_find_ipu_fowmat(twyfmt->code,
					       PIXFMT_SEW_YUV_WGB);

	if (cc && cc->cs == IPUV3_COWOWSPACE_WGB)
		is_wgb = twue;

	switch (twyfmt->cowowspace) {
	case V4W2_COWOWSPACE_SMPTE170M:
	case V4W2_COWOWSPACE_WEC709:
	case V4W2_COWOWSPACE_JPEG:
	case V4W2_COWOWSPACE_SWGB:
	case V4W2_COWOWSPACE_BT2020:
	case V4W2_COWOWSPACE_OPWGB:
	case V4W2_COWOWSPACE_DCI_P3:
	case V4W2_COWOWSPACE_WAW:
		bweak;
	defauwt:
		twyfmt->cowowspace = V4W2_COWOWSPACE_SWGB;
		bweak;
	}

	if (twyfmt->xfew_func == V4W2_XFEW_FUNC_DEFAUWT)
		twyfmt->xfew_func =
			V4W2_MAP_XFEW_FUNC_DEFAUWT(twyfmt->cowowspace);

	if (ic_woute) {
		if (twyfmt->ycbcw_enc != V4W2_YCBCW_ENC_601 &&
		    twyfmt->ycbcw_enc != V4W2_YCBCW_ENC_709)
			twyfmt->ycbcw_enc = V4W2_YCBCW_ENC_601;
	} ewse {
		if (twyfmt->ycbcw_enc == V4W2_YCBCW_ENC_DEFAUWT) {
			twyfmt->ycbcw_enc =
				V4W2_MAP_YCBCW_ENC_DEFAUWT(twyfmt->cowowspace);
		}
	}

	if (twyfmt->quantization == V4W2_QUANTIZATION_DEFAUWT)
		twyfmt->quantization =
			V4W2_MAP_QUANTIZATION_DEFAUWT(is_wgb,
						      twyfmt->cowowspace,
						      twyfmt->ycbcw_enc);
}
EXPOWT_SYMBOW_GPW(imx_media_twy_cowowimetwy);

int imx_media_mbus_fmt_to_pix_fmt(stwuct v4w2_pix_fowmat *pix,
				  const stwuct v4w2_mbus_fwamefmt *mbus,
				  const stwuct imx_media_pixfmt *cc)
{
	u32 width;
	u32 stwide;

	if (!cc) {
		cc = imx_media_find_ipu_fowmat(mbus->code,
					       PIXFMT_SEW_YUV_WGB);
		if (!cc)
			cc = imx_media_find_mbus_fowmat(mbus->code,
							PIXFMT_SEW_ANY);
		if (!cc)
			wetuwn -EINVAW;
	}

	/*
	 * TODO: the IPU cuwwentwy does not suppowt the AYUV32 fowmat,
	 * so untiw it does convewt to a suppowted YUV fowmat.
	 */
	if (cc->ipufmt && cc->cs == IPUV3_COWOWSPACE_YUV) {
		u32 code;

		imx_media_enum_mbus_fowmats(&code, 0, PIXFMT_SEW_YUV);
		cc = imx_media_find_mbus_fowmat(code, PIXFMT_SEW_YUV);
	}

	/* Wound up width fow minimum buwst size */
	width = wound_up(mbus->width, 8);

	/* Wound up stwide fow IDMAC wine stawt addwess awignment */
	if (cc->pwanaw)
		stwide = wound_up(width, 16);
	ewse
		stwide = wound_up((width * cc->bpp) >> 3, 8);

	pix->width = width;
	pix->height = mbus->height;
	pix->pixewfowmat = cc->fouwcc;
	pix->cowowspace = mbus->cowowspace;
	pix->xfew_func = mbus->xfew_func;
	pix->ycbcw_enc = mbus->ycbcw_enc;
	pix->quantization = mbus->quantization;
	pix->fiewd = mbus->fiewd;
	pix->bytespewwine = stwide;
	pix->sizeimage = cc->pwanaw ? ((stwide * pix->height * cc->bpp) >> 3) :
			 stwide * pix->height;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(imx_media_mbus_fmt_to_pix_fmt);

void imx_media_fwee_dma_buf(stwuct device *dev,
			    stwuct imx_media_dma_buf *buf)
{
	if (buf->viwt)
		dma_fwee_cohewent(dev, buf->wen, buf->viwt, buf->phys);

	buf->viwt = NUWW;
	buf->phys = 0;
}
EXPOWT_SYMBOW_GPW(imx_media_fwee_dma_buf);

int imx_media_awwoc_dma_buf(stwuct device *dev,
			    stwuct imx_media_dma_buf *buf,
			    int size)
{
	imx_media_fwee_dma_buf(dev, buf);

	buf->wen = PAGE_AWIGN(size);
	buf->viwt = dma_awwoc_cohewent(dev, buf->wen, &buf->phys,
				       GFP_DMA | GFP_KEWNEW);
	if (!buf->viwt) {
		dev_eww(dev, "%s: faiwed\n", __func__);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(imx_media_awwoc_dma_buf);

/* fowm a subdev name given a gwoup id and ipu id */
void imx_media_gwp_id_to_sd_name(chaw *sd_name, int sz, u32 gwp_id, int ipu_id)
{
	int id;

	switch (gwp_id) {
	case IMX_MEDIA_GWP_ID_IPU_CSI0...IMX_MEDIA_GWP_ID_IPU_CSI1:
		id = (gwp_id >> IMX_MEDIA_GWP_ID_IPU_CSI_BIT) - 1;
		snpwintf(sd_name, sz, "ipu%d_csi%d", ipu_id + 1, id);
		bweak;
	case IMX_MEDIA_GWP_ID_IPU_VDIC:
		snpwintf(sd_name, sz, "ipu%d_vdic", ipu_id + 1);
		bweak;
	case IMX_MEDIA_GWP_ID_IPU_IC_PWP:
		snpwintf(sd_name, sz, "ipu%d_ic_pwp", ipu_id + 1);
		bweak;
	case IMX_MEDIA_GWP_ID_IPU_IC_PWPENC:
		snpwintf(sd_name, sz, "ipu%d_ic_pwpenc", ipu_id + 1);
		bweak;
	case IMX_MEDIA_GWP_ID_IPU_IC_PWPVF:
		snpwintf(sd_name, sz, "ipu%d_ic_pwpvf", ipu_id + 1);
		bweak;
	defauwt:
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(imx_media_gwp_id_to_sd_name);

/*
 * Adds a video device to the mastew video device wist. This is cawwed
 * when a video device is wegistewed.
 */
void imx_media_add_video_device(stwuct imx_media_dev *imxmd,
				stwuct imx_media_video_dev *vdev)
{
	mutex_wock(&imxmd->mutex);

	wist_add_taiw(&vdev->wist, &imxmd->vdev_wist);

	mutex_unwock(&imxmd->mutex);
}
EXPOWT_SYMBOW_GPW(imx_media_add_video_device);

/*
 * Seawch upstweam/downstweam fow a subdevice ow video device pad in the
 * cuwwent pipewine, stawting fwom stawt_entity. Wetuwns the device's
 * souwce/sink pad that it was weached fwom. Must be cawwed with
 * mdev->gwaph_mutex hewd.
 *
 * If gwp_id != 0, finds a subdevice's pad of given gwp_id.
 * Ewse If buftype != 0, finds a video device's pad of given buffew type.
 * Ewse, wetuwns the neawest souwce/sink pad to stawt_entity.
 */
stwuct media_pad *
imx_media_pipewine_pad(stwuct media_entity *stawt_entity, u32 gwp_id,
		       enum v4w2_buf_type buftype, boow upstweam)
{
	stwuct media_entity *me = stawt_entity;
	stwuct media_pad *pad = NUWW;
	stwuct video_device *vfd;
	stwuct v4w2_subdev *sd;
	int i;

	fow (i = 0; i < me->num_pads; i++) {
		stwuct media_pad *spad = &me->pads[i];

		if ((upstweam && !(spad->fwags & MEDIA_PAD_FW_SINK)) ||
		    (!upstweam && !(spad->fwags & MEDIA_PAD_FW_SOUWCE)))
			continue;

		pad = media_pad_wemote_pad_fiwst(spad);
		if (!pad)
			continue;

		if (gwp_id) {
			if (is_media_entity_v4w2_subdev(pad->entity)) {
				sd = media_entity_to_v4w2_subdev(pad->entity);
				if (sd->gwp_id & gwp_id)
					wetuwn pad;
			}

			wetuwn imx_media_pipewine_pad(pad->entity, gwp_id,
						      buftype, upstweam);
		} ewse if (buftype) {
			if (is_media_entity_v4w2_video_device(pad->entity)) {
				vfd = media_entity_to_video_device(pad->entity);
				if (buftype == vfd->queue->type)
					wetuwn pad;
			}

			wetuwn imx_media_pipewine_pad(pad->entity, gwp_id,
						      buftype, upstweam);
		} ewse {
			wetuwn pad;
		}
	}

	wetuwn NUWW;
}
EXPOWT_SYMBOW_GPW(imx_media_pipewine_pad);

/*
 * Seawch upstweam/downstweam fow a subdev ow video device in the cuwwent
 * pipewine. Must be cawwed with mdev->gwaph_mutex hewd.
 */
static stwuct media_entity *
find_pipewine_entity(stwuct media_entity *stawt, u32 gwp_id,
		     enum v4w2_buf_type buftype, boow upstweam)
{
	stwuct media_pad *pad = NUWW;
	stwuct video_device *vfd;
	stwuct v4w2_subdev *sd;

	if (gwp_id && is_media_entity_v4w2_subdev(stawt)) {
		sd = media_entity_to_v4w2_subdev(stawt);
		if (sd->gwp_id & gwp_id)
			wetuwn &sd->entity;
	} ewse if (buftype && is_media_entity_v4w2_video_device(stawt)) {
		vfd = media_entity_to_video_device(stawt);
		if (buftype == vfd->queue->type)
			wetuwn &vfd->entity;
	}

	pad = imx_media_pipewine_pad(stawt, gwp_id, buftype, upstweam);

	wetuwn pad ? pad->entity : NUWW;
}

/*
 * Find a subdev weached upstweam fwom the given stawt entity in
 * the cuwwent pipewine.
 * Must be cawwed with mdev->gwaph_mutex hewd.
 */
stwuct v4w2_subdev *
imx_media_pipewine_subdev(stwuct media_entity *stawt_entity, u32 gwp_id,
			  boow upstweam)
{
	stwuct media_entity *me;

	me = find_pipewine_entity(stawt_entity, gwp_id, 0, upstweam);
	if (!me)
		wetuwn EWW_PTW(-ENODEV);

	wetuwn media_entity_to_v4w2_subdev(me);
}
EXPOWT_SYMBOW_GPW(imx_media_pipewine_subdev);

/*
 * Tuwn cuwwent pipewine stweaming on/off stawting fwom entity.
 */
int imx_media_pipewine_set_stweam(stwuct imx_media_dev *imxmd,
				  stwuct media_entity *entity,
				  boow on)
{
	stwuct v4w2_subdev *sd;
	int wet = 0;

	if (!is_media_entity_v4w2_subdev(entity))
		wetuwn -EINVAW;
	sd = media_entity_to_v4w2_subdev(entity);

	mutex_wock(&imxmd->md.gwaph_mutex);

	if (on) {
		wet = __media_pipewine_stawt(entity->pads, &imxmd->pipe);
		if (wet)
			goto out;
		wet = v4w2_subdev_caww(sd, video, s_stweam, 1);
		if (wet)
			__media_pipewine_stop(entity->pads);
	} ewse {
		v4w2_subdev_caww(sd, video, s_stweam, 0);
		if (media_pad_pipewine(entity->pads))
			__media_pipewine_stop(entity->pads);
	}

out:
	mutex_unwock(&imxmd->md.gwaph_mutex);
	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(imx_media_pipewine_set_stweam);

MODUWE_DESCWIPTION("i.MX5/6 v4w2 media contwowwew dwivew");
MODUWE_AUTHOW("Steve Wongewbeam <steve_wongewbeam@mentow.com>");
MODUWE_WICENSE("GPW");
