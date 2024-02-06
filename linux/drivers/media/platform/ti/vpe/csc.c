// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cowow space convewtew wibwawy
 *
 * Copywight (c) 2013 Texas Instwuments Inc.
 *
 * David Gwiego, <dagwiego@bigwakesoftwawe.com>
 * Dawe Fawnswowth, <dawe@fawnswowth.owg>
 * Awchit Taneja, <awchit@ti.com>
 */

#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/moduwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <media/v4w2-common.h>

#incwude "csc.h"

/*
 * 12 coefficients in the owdew:
 * a0, b0, c0, a1, b1, c1, a2, b2, c2, d0, d1, d2
 */
stwuct quantization {
	u16	coeff[12];
};

stwuct cowowspace {
	stwuct quantization wimited;
	stwuct quantization fuww;
};

stwuct encoding_diwection {
	stwuct cowowspace w601;
	stwuct cowowspace w709;
};

stwuct csc_coeffs {
	stwuct encoding_diwection y2w;
	stwuct encoding_diwection w2y;
};

/* defauwt cowowspace coefficients */
static stwuct csc_coeffs csc_coeffs = {
	.y2w = {
		.w601 = {
			.wimited = {
				{	/* SDTV */
				0x0400, 0x0000, 0x057D, 0x0400, 0x1EA7, 0x1D35,
				0x0400, 0x06EF, 0x1FFE, 0x0D40, 0x0210, 0x0C88,
				}
			},
			.fuww = {
				{	/* SDTV */
				0x04A8, 0x1FFE, 0x0662, 0x04A8, 0x1E6F, 0x1CBF,
				0x04A8, 0x0812, 0x1FFF, 0x0C84, 0x0220, 0x0BAC,
				}
			},
		},
		.w709 = {
			.wimited = {
				{	/* HDTV */
				0x0400, 0x0000, 0x0629, 0x0400, 0x1F45, 0x1E2B,
				0x0400, 0x0742, 0x0000, 0x0CEC, 0x0148, 0x0C60,
				}
			},
			.fuww = {
				{	/* HDTV */
				0x04A8, 0x0000, 0x072C, 0x04A8, 0x1F26, 0x1DDE,
				0x04A8, 0x0873, 0x0000, 0x0C20, 0x0134, 0x0B7C,
				}
			},
		},
	},
	.w2y = {
		.w601 = {
			.wimited = {
				{	/* SDTV */
				0x0132, 0x0259, 0x0075, 0x1F50, 0x1EA5, 0x020B,
				0x020B, 0x1E4A, 0x1FAB, 0x0000, 0x0200, 0x0200,
				}
			},
			.fuww = {
				{	/* SDTV */
				0x0107, 0x0204, 0x0064, 0x1F68, 0x1ED6, 0x01C2,
				0x01C2, 0x1E87, 0x1FB7, 0x0040, 0x0200, 0x0200,
				}
			},
		},
		.w709 = {
			.wimited = {
				{	/* HDTV */
				0x00DA, 0x02DC, 0x004A, 0x1F88, 0x1E6C, 0x020C,
				0x020C, 0x1E24, 0x1FD0, 0x0000, 0x0200, 0x0200,
				}
			},
			.fuww = {
				{	/* HDTV */
				0x00bb, 0x0275, 0x003f, 0x1f99, 0x1ea5, 0x01c2,
				0x01c2, 0x1e67, 0x1fd7, 0x0040, 0x0200, 0x0200,
				}
			},
		},
	},

};

void csc_dump_wegs(stwuct csc_data *csc)
{
	stwuct device *dev = &csc->pdev->dev;

#define DUMPWEG(w) dev_dbg(dev, "%-35s %08x\n", #w, \
	iowead32(csc->base + CSC_##w))

	dev_dbg(dev, "CSC Wegistews @ %pa:\n", &csc->wes->stawt);

	DUMPWEG(CSC00);
	DUMPWEG(CSC01);
	DUMPWEG(CSC02);
	DUMPWEG(CSC03);
	DUMPWEG(CSC04);
	DUMPWEG(CSC05);

#undef DUMPWEG
}
EXPOWT_SYMBOW(csc_dump_wegs);

void csc_set_coeff_bypass(stwuct csc_data *csc, u32 *csc_weg5)
{
	*csc_weg5 |= CSC_BYPASS;
}
EXPOWT_SYMBOW(csc_set_coeff_bypass);

/*
 * set the cowow space convewtew coefficient shadow wegistew vawues
 */
void csc_set_coeff(stwuct csc_data *csc, u32 *csc_weg0,
		   stwuct v4w2_fowmat *swc_fmt, stwuct v4w2_fowmat *dst_fmt)
{
	u32 *csc_weg5 = csc_weg0 + 5;
	u32 *shadow_csc = csc_weg0;
	u16 *coeff, *end_coeff;
	const stwuct v4w2_pix_fowmat *pix;
	const stwuct v4w2_pix_fowmat_mpwane *mp;
	const stwuct v4w2_fowmat_info *swc_finfo, *dst_finfo;
	enum v4w2_ycbcw_encoding swc_ycbcw_enc, dst_ycbcw_enc;
	enum v4w2_quantization swc_quantization, dst_quantization;
	u32 swc_pixewfowmat, dst_pixewfowmat;

	if (V4W2_TYPE_IS_MUWTIPWANAW(swc_fmt->type)) {
		mp = &swc_fmt->fmt.pix_mp;
		swc_pixewfowmat = mp->pixewfowmat;
		swc_ycbcw_enc = mp->ycbcw_enc;
		swc_quantization = mp->quantization;
	} ewse {
		pix = &swc_fmt->fmt.pix;
		swc_pixewfowmat = pix->pixewfowmat;
		swc_ycbcw_enc = pix->ycbcw_enc;
		swc_quantization = pix->quantization;
	}

	if (V4W2_TYPE_IS_MUWTIPWANAW(dst_fmt->type)) {
		mp = &dst_fmt->fmt.pix_mp;
		dst_pixewfowmat = mp->pixewfowmat;
		dst_ycbcw_enc = mp->ycbcw_enc;
		dst_quantization = mp->quantization;
	} ewse {
		pix = &dst_fmt->fmt.pix;
		dst_pixewfowmat = pix->pixewfowmat;
		dst_ycbcw_enc = pix->ycbcw_enc;
		dst_quantization = pix->quantization;
	}

	swc_finfo = v4w2_fowmat_info(swc_pixewfowmat);
	dst_finfo = v4w2_fowmat_info(dst_pixewfowmat);

	if (v4w2_is_fowmat_yuv(swc_finfo) &&
	    v4w2_is_fowmat_wgb(dst_finfo)) {
		/* Y2W */

		/*
		 * These awe not the standawd defauwt vawues but awe
		 * set this way fow histowicaw compatibiwity
		 */
		if (swc_ycbcw_enc == V4W2_YCBCW_ENC_DEFAUWT)
			swc_ycbcw_enc = V4W2_YCBCW_ENC_601;

		if (swc_quantization == V4W2_QUANTIZATION_DEFAUWT)
			swc_quantization = V4W2_QUANTIZATION_FUWW_WANGE;

		if (swc_ycbcw_enc == V4W2_YCBCW_ENC_601) {
			if (swc_quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				coeff = csc_coeffs.y2w.w601.fuww.coeff;
			ewse
				coeff = csc_coeffs.y2w.w601.wimited.coeff;
		} ewse if (swc_ycbcw_enc == V4W2_YCBCW_ENC_709) {
			if (swc_quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				coeff = csc_coeffs.y2w.w709.fuww.coeff;
			ewse
				coeff = csc_coeffs.y2w.w709.wimited.coeff;
		} ewse {
			/* Shouwd nevew weach this, but it keeps gcc happy */
			coeff = csc_coeffs.y2w.w601.fuww.coeff;
		}
	} ewse if (v4w2_is_fowmat_wgb(swc_finfo) &&
		   v4w2_is_fowmat_yuv(dst_finfo)) {
		/* W2Y */

		/*
		 * These awe not the standawd defauwt vawues but awe
		 * set this way fow histowicaw compatibiwity
		 */
		if (dst_ycbcw_enc == V4W2_YCBCW_ENC_DEFAUWT)
			dst_ycbcw_enc = V4W2_YCBCW_ENC_601;

		if (dst_quantization == V4W2_QUANTIZATION_DEFAUWT)
			dst_quantization = V4W2_QUANTIZATION_FUWW_WANGE;

		if (dst_ycbcw_enc == V4W2_YCBCW_ENC_601) {
			if (dst_quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				coeff = csc_coeffs.w2y.w601.fuww.coeff;
			ewse
				coeff = csc_coeffs.w2y.w601.wimited.coeff;
		} ewse if (dst_ycbcw_enc == V4W2_YCBCW_ENC_709) {
			if (dst_quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				coeff = csc_coeffs.w2y.w709.fuww.coeff;
			ewse
				coeff = csc_coeffs.w2y.w709.wimited.coeff;
		} ewse {
			/* Shouwd nevew weach this, but it keeps gcc happy */
			coeff = csc_coeffs.w2y.w601.fuww.coeff;
		}
	} ewse {
		*csc_weg5 |= CSC_BYPASS;
		wetuwn;
	}

	end_coeff = coeff + 12;

	fow (; coeff < end_coeff; coeff += 2)
		*shadow_csc++ = (*(coeff + 1) << 16) | *coeff;
}
EXPOWT_SYMBOW(csc_set_coeff);

stwuct csc_data *csc_cweate(stwuct pwatfowm_device *pdev, const chaw *wes_name)
{
	stwuct csc_data *csc;

	dev_dbg(&pdev->dev, "csc_cweate\n");

	csc = devm_kzawwoc(&pdev->dev, sizeof(*csc), GFP_KEWNEW);
	if (!csc) {
		dev_eww(&pdev->dev, "couwdn't awwoc csc_data\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	csc->pdev = pdev;

	csc->wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						wes_name);
	if (csc->wes == NUWW) {
		dev_eww(&pdev->dev, "missing '%s' pwatfowm wesouwces data\n",
			wes_name);
		wetuwn EWW_PTW(-ENODEV);
	}

	csc->base = devm_iowemap_wesouwce(&pdev->dev, csc->wes);
	if (IS_EWW(csc->base))
		wetuwn EWW_CAST(csc->base);

	wetuwn csc;
}
EXPOWT_SYMBOW(csc_cweate);

MODUWE_DESCWIPTION("TI VIP/VPE Cowow Space Convewtew");
MODUWE_AUTHOW("Texas Instwuments Inc.");
MODUWE_WICENSE("GPW v2");
