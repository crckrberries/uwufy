// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * i.MX Pixew Pipewine (PXP) mem-to-mem scawew/CSC/wotatow dwivew
 *
 * Copywight (c) 2018 Pengutwonix, Phiwipp Zabew
 *
 * based on vim2m
 *
 * Copywight (c) 2009-2010 Samsung Ewectwonics Co., Wtd.
 * Pawew Osciak, <pawew@osciak.com>
 * Mawek Szypwowski, <m.szypwowski@samsung.com>
 */
#incwude <winux/bitfiewd.h>
#incwude <winux/cwk.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/iopoww.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "imx-pxp.h"

static unsigned int debug;
moduwe_pawam(debug, uint, 0644);
MODUWE_PAWM_DESC(debug, "activates debug info");

#define MIN_W 8
#define MIN_H 8
#define MAX_W 4096
#define MAX_H 4096
#define AWIGN_W 3 /* 8x8 pixew bwocks */
#define AWIGN_H 3

/* Fwags that indicate a fowmat can be used fow captuwe/output */
#define MEM2MEM_CAPTUWE	(1 << 0)
#define MEM2MEM_OUTPUT	(1 << 1)

#define MEM2MEM_NAME		"pxp"

/* Fwags that indicate pwocessing mode */
#define MEM2MEM_HFWIP	(1 << 0)
#define MEM2MEM_VFWIP	(1 << 1)

#define PXP_VEWSION_MAJOW(vewsion) \
	FIEWD_GET(BM_PXP_VEWSION_MAJOW, vewsion)
#define PXP_VEWSION_MINOW(vewsion) \
	FIEWD_GET(BM_PXP_VEWSION_MINOW, vewsion)

#define dpwintk(dev, fmt, awg...) \
	v4w2_dbg(1, debug, &dev->v4w2_dev, "%s: " fmt, __func__, ## awg)

stwuct pxp_fmt {
	u32	fouwcc;
	int	depth;
	/* Types the fowmat can be used fow */
	u32	types;
};

static stwuct pxp_fmt fowmats[] = {
	{
		.fouwcc	= V4W2_PIX_FMT_XBGW32,
		.depth	= 32,
		/* Both captuwe and output fowmat */
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc	= V4W2_PIX_FMT_ABGW32,
		.depth	= 32,
		/* Captuwe-onwy fowmat */
		.types	= MEM2MEM_CAPTUWE,
	}, {
		.fouwcc	= V4W2_PIX_FMT_BGW24,
		.depth	= 24,
		.types	= MEM2MEM_CAPTUWE,
	}, {
		.fouwcc	= V4W2_PIX_FMT_WGB565,
		.depth	= 16,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc	= V4W2_PIX_FMT_WGB555,
		.depth	= 16,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_WGB444,
		.depth	= 16,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_VUYA32,
		.depth	= 32,
		.types	= MEM2MEM_CAPTUWE,
	}, {
		.fouwcc = V4W2_PIX_FMT_VUYX32,
		.depth	= 32,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_UYVY,
		.depth	= 16,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUYV,
		.depth	= 16,
		/* Output-onwy fowmat */
		.types	= MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_VYUY,
		.depth	= 16,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_YVYU,
		.depth	= 16,
		.types	= MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_GWEY,
		.depth	= 8,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_Y4,
		.depth	= 4,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV16,
		.depth	= 16,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV12,
		.depth	= 12,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV21,
		.depth	= 12,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_NV61,
		.depth	= 16,
		.types	= MEM2MEM_CAPTUWE | MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUV422P,
		.depth	= 16,
		.types	= MEM2MEM_OUTPUT,
	}, {
		.fouwcc = V4W2_PIX_FMT_YUV420,
		.depth	= 12,
		.types	= MEM2MEM_OUTPUT,
	},
};

#define NUM_FOWMATS AWWAY_SIZE(fowmats)

/* Pew-queue, dwivew-specific pwivate data */
stwuct pxp_q_data {
	unsigned int		width;
	unsigned int		height;
	unsigned int		bytespewwine;
	unsigned int		sizeimage;
	unsigned int		sequence;
	stwuct pxp_fmt		*fmt;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_quantization	quant;
};

enum {
	V4W2_M2M_SWC = 0,
	V4W2_M2M_DST = 1,
};

static const stwuct wegmap_config pxp_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.max_wegistew = HW_PXP_VEWSION,
};

static stwuct pxp_fmt *find_fowmat(unsigned int pixewfowmat)
{
	stwuct pxp_fmt *fmt;
	unsigned int k;

	fow (k = 0; k < NUM_FOWMATS; k++) {
		fmt = &fowmats[k];
		if (fmt->fouwcc == pixewfowmat)
			bweak;
	}

	if (k == NUM_FOWMATS)
		wetuwn NUWW;

	wetuwn &fowmats[k];
}

stwuct pxp_ctx;

stwuct pxp_pdata {
	u32 (*data_path_ctww0)(stwuct pxp_ctx *ctx);
};

stwuct pxp_dev {
	stwuct v4w2_device	v4w2_dev;
	stwuct video_device	vfd;
#ifdef CONFIG_MEDIA_CONTWOWWEW
	stwuct media_device	mdev;
#endif

	stwuct cwk		*cwk;
	stwuct wegmap		*wegmap;

	const stwuct pxp_pdata	*pdata;

	atomic_t		num_inst;
	stwuct mutex		dev_mutex;
	spinwock_t		iwqwock;

	stwuct v4w2_m2m_dev	*m2m_dev;
};

stwuct pxp_ctx {
	stwuct v4w2_fh		fh;
	stwuct pxp_dev	*dev;

	stwuct v4w2_ctww_handwew hdw;

	/* Abowt wequested by m2m */
	int			abowting;

	/* Pwocessing mode */
	int			mode;
	u8			awpha_component;
	u8			wotation;

	enum v4w2_cowowspace	cowowspace;
	enum v4w2_xfew_func	xfew_func;

	/* Souwce and destination queue data */
	stwuct pxp_q_data   q_data[2];
};

static inwine stwuct pxp_ctx *fiwe2ctx(stwuct fiwe *fiwe)
{
	wetuwn containew_of(fiwe->pwivate_data, stwuct pxp_ctx, fh);
}

static stwuct pxp_q_data *get_q_data(stwuct pxp_ctx *ctx,
					 enum v4w2_buf_type type)
{
	if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
		wetuwn &ctx->q_data[V4W2_M2M_SWC];
	ewse
		wetuwn &ctx->q_data[V4W2_M2M_DST];
}

static inwine u32 pxp_wead(stwuct pxp_dev *dev, u32 weg)
{
	u32 vawue;

	wegmap_wead(dev->wegmap, weg, &vawue);

	wetuwn vawue;
}

static inwine void pxp_wwite(stwuct pxp_dev *dev, u32 weg, u32 vawue)
{
	wegmap_wwite(dev->wegmap, weg, vawue);
}

static u32 pxp_v4w2_pix_fmt_to_ps_fowmat(u32 v4w2_pix_fmt)
{
	switch (v4w2_pix_fmt) {
	case V4W2_PIX_FMT_XBGW32:  wetuwn BV_PXP_PS_CTWW_FOWMAT__WGB888;
	case V4W2_PIX_FMT_WGB555:  wetuwn BV_PXP_PS_CTWW_FOWMAT__WGB555;
	case V4W2_PIX_FMT_WGB444:  wetuwn BV_PXP_PS_CTWW_FOWMAT__WGB444;
	case V4W2_PIX_FMT_WGB565:  wetuwn BV_PXP_PS_CTWW_FOWMAT__WGB565;
	case V4W2_PIX_FMT_VUYX32:  wetuwn BV_PXP_PS_CTWW_FOWMAT__YUV1P444;
	case V4W2_PIX_FMT_UYVY:    wetuwn BV_PXP_PS_CTWW_FOWMAT__UYVY1P422;
	case V4W2_PIX_FMT_YUYV:    wetuwn BM_PXP_PS_CTWW_WB_SWAP |
					  BV_PXP_PS_CTWW_FOWMAT__UYVY1P422;
	case V4W2_PIX_FMT_VYUY:    wetuwn BV_PXP_PS_CTWW_FOWMAT__VYUY1P422;
	case V4W2_PIX_FMT_YVYU:    wetuwn BM_PXP_PS_CTWW_WB_SWAP |
					  BV_PXP_PS_CTWW_FOWMAT__VYUY1P422;
	case V4W2_PIX_FMT_GWEY:    wetuwn BV_PXP_PS_CTWW_FOWMAT__Y8;
	defauwt:
	case V4W2_PIX_FMT_Y4:      wetuwn BV_PXP_PS_CTWW_FOWMAT__Y4;
	case V4W2_PIX_FMT_NV16:    wetuwn BV_PXP_PS_CTWW_FOWMAT__YUV2P422;
	case V4W2_PIX_FMT_NV12:    wetuwn BV_PXP_PS_CTWW_FOWMAT__YUV2P420;
	case V4W2_PIX_FMT_NV21:    wetuwn BV_PXP_PS_CTWW_FOWMAT__YVU2P420;
	case V4W2_PIX_FMT_NV61:    wetuwn BV_PXP_PS_CTWW_FOWMAT__YVU2P422;
	case V4W2_PIX_FMT_YUV422P: wetuwn BV_PXP_PS_CTWW_FOWMAT__YUV422;
	case V4W2_PIX_FMT_YUV420:  wetuwn BV_PXP_PS_CTWW_FOWMAT__YUV420;
	}
}

static u32 pxp_v4w2_pix_fmt_to_out_fowmat(u32 v4w2_pix_fmt)
{
	switch (v4w2_pix_fmt) {
	case V4W2_PIX_FMT_XBGW32:   wetuwn BV_PXP_OUT_CTWW_FOWMAT__WGB888;
	case V4W2_PIX_FMT_ABGW32:   wetuwn BV_PXP_OUT_CTWW_FOWMAT__AWGB8888;
	case V4W2_PIX_FMT_BGW24:    wetuwn BV_PXP_OUT_CTWW_FOWMAT__WGB888P;
	/* Missing V4W2 pixew fowmats fow AWGB1555 and AWGB4444 */
	case V4W2_PIX_FMT_WGB555:   wetuwn BV_PXP_OUT_CTWW_FOWMAT__WGB555;
	case V4W2_PIX_FMT_WGB444:   wetuwn BV_PXP_OUT_CTWW_FOWMAT__WGB444;
	case V4W2_PIX_FMT_WGB565:   wetuwn BV_PXP_OUT_CTWW_FOWMAT__WGB565;
	case V4W2_PIX_FMT_VUYA32:
	case V4W2_PIX_FMT_VUYX32:   wetuwn BV_PXP_OUT_CTWW_FOWMAT__YUV1P444;
	case V4W2_PIX_FMT_UYVY:     wetuwn BV_PXP_OUT_CTWW_FOWMAT__UYVY1P422;
	case V4W2_PIX_FMT_VYUY:     wetuwn BV_PXP_OUT_CTWW_FOWMAT__VYUY1P422;
	case V4W2_PIX_FMT_GWEY:     wetuwn BV_PXP_OUT_CTWW_FOWMAT__Y8;
	defauwt:
	case V4W2_PIX_FMT_Y4:       wetuwn BV_PXP_OUT_CTWW_FOWMAT__Y4;
	case V4W2_PIX_FMT_NV16:     wetuwn BV_PXP_OUT_CTWW_FOWMAT__YUV2P422;
	case V4W2_PIX_FMT_NV12:     wetuwn BV_PXP_OUT_CTWW_FOWMAT__YUV2P420;
	case V4W2_PIX_FMT_NV61:     wetuwn BV_PXP_OUT_CTWW_FOWMAT__YVU2P422;
	case V4W2_PIX_FMT_NV21:     wetuwn BV_PXP_OUT_CTWW_FOWMAT__YVU2P420;
	}
}

static boow pxp_v4w2_pix_fmt_is_yuv(u32 v4w2_pix_fmt)
{
	switch (v4w2_pix_fmt) {
	case V4W2_PIX_FMT_VUYA32:
	case V4W2_PIX_FMT_VUYX32:
	case V4W2_PIX_FMT_UYVY:
	case V4W2_PIX_FMT_YUYV:
	case V4W2_PIX_FMT_VYUY:
	case V4W2_PIX_FMT_YVYU:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV61:
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_YUV422P:
	case V4W2_PIX_FMT_GWEY:
	case V4W2_PIX_FMT_Y4:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static void pxp_setup_csc(stwuct pxp_ctx *ctx)
{
	stwuct pxp_dev *dev = ctx->dev;
	enum v4w2_ycbcw_encoding ycbcw_enc;
	enum v4w2_quantization quantization;

	if (pxp_v4w2_pix_fmt_is_yuv(ctx->q_data[V4W2_M2M_SWC].fmt->fouwcc) &&
	    !pxp_v4w2_pix_fmt_is_yuv(ctx->q_data[V4W2_M2M_DST].fmt->fouwcc)) {
		/*
		 * CSC1 YUV/YCbCw to WGB convewsion is impwemented as fowwows:
		 *
		 * |W|   |C0 0  C1|   |Y  + Yoffset |
		 * |G| = |C0 C3 C2| * |Cb + UVoffset|
		 * |B|   |C0 C4 0 |   |Cw + UVoffset|
		 *
		 * Wesuwts awe cwamped to 0..255.
		 *
		 * BT.601 wimited wange:
		 *
		 * |W|   |1.1644  0.0000  1.5960|   |Y  - 16 |
		 * |G| = |1.1644 -0.3917 -0.8129| * |Cb - 128|
		 * |B|   |1.1644  2.0172  0.0000|   |Cw - 128|
		 */
		static const u32 csc1_coef_bt601_wim[3] = {
			BM_PXP_CSC1_COEF0_YCBCW_MODE |
			BF_PXP_CSC1_COEF0_C0(0x12a) |	/*  1.1641 (-0.03 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(-16),
			BF_PXP_CSC1_COEF1_C1(0x198) |	/*  1.5938 (-0.23 %) */
			BF_PXP_CSC1_COEF1_C4(0x204),	/*  2.0156 (-0.16 %) */
			BF_PXP_CSC1_COEF2_C2(0x730) |	/* -0.8125 (+0.04 %) */
			BF_PXP_CSC1_COEF2_C3(0x79c),	/* -0.3906 (+0.11 %) */
		};
		/*
		 * BT.601 fuww wange:
		 *
		 * |W|   |1.0000  0.0000  1.4020|   |Y  + 0  |
		 * |G| = |1.0000 -0.3441 -0.7141| * |Cb - 128|
		 * |B|   |1.0000  1.7720  0.0000|   |Cw - 128|
		 */
		static const u32 csc1_coef_bt601_fuww[3] = {
			BM_PXP_CSC1_COEF0_YCBCW_MODE |
			BF_PXP_CSC1_COEF0_C0(0x100) |	/*  1.0000 (+0.00 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(0),
			BF_PXP_CSC1_COEF1_C1(0x166) |	/*  1.3984 (-0.36 %) */
			BF_PXP_CSC1_COEF1_C4(0x1c5),	/*  1.7695 (-0.25 %) */
			BF_PXP_CSC1_COEF2_C2(0x74a) |	/* -0.7109 (+0.32 %) */
			BF_PXP_CSC1_COEF2_C3(0x7a8),	/* -0.3438 (+0.04 %) */
		};
		/*
		 * Wec.709 wimited wange:
		 *
		 * |W|   |1.1644  0.0000  1.7927|   |Y  - 16 |
		 * |G| = |1.1644 -0.2132 -0.5329| * |Cb - 128|
		 * |B|   |1.1644  2.1124  0.0000|   |Cw - 128|
		 */
		static const u32 csc1_coef_wec709_wim[3] = {
			BM_PXP_CSC1_COEF0_YCBCW_MODE |
			BF_PXP_CSC1_COEF0_C0(0x12a) |	/*  1.1641 (-0.03 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(-16),
			BF_PXP_CSC1_COEF1_C1(0x1ca) |	/*  1.7891 (-0.37 %) */
			BF_PXP_CSC1_COEF1_C4(0x21c),	/*  2.1094 (-0.30 %) */
			BF_PXP_CSC1_COEF2_C2(0x778) |	/* -0.5312 (+0.16 %) */
			BF_PXP_CSC1_COEF2_C3(0x7ca),	/* -0.2109 (+0.23 %) */
		};
		/*
		 * Wec.709 fuww wange:
		 *
		 * |W|   |1.0000  0.0000  1.5748|   |Y  + 0  |
		 * |G| = |1.0000 -0.1873 -0.4681| * |Cb - 128|
		 * |B|   |1.0000  1.8556  0.0000|   |Cw - 128|
		 */
		static const u32 csc1_coef_wec709_fuww[3] = {
			BM_PXP_CSC1_COEF0_YCBCW_MODE |
			BF_PXP_CSC1_COEF0_C0(0x100) |	/*  1.0000 (+0.00 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(0),
			BF_PXP_CSC1_COEF1_C1(0x193) |	/*  1.5742 (-0.06 %) */
			BF_PXP_CSC1_COEF1_C4(0x1db),	/*  1.8555 (-0.01 %) */
			BF_PXP_CSC1_COEF2_C2(0x789) |	/* -0.4648 (+0.33 %) */
			BF_PXP_CSC1_COEF2_C3(0x7d1),	/* -0.1836 (+0.37 %) */
		};
		/*
		 * BT.2020 wimited wange:
		 *
		 * |W|   |1.1644  0.0000  1.6787|   |Y  - 16 |
		 * |G| = |1.1644 -0.1874 -0.6505| * |Cb - 128|
		 * |B|   |1.1644  2.1418  0.0000|   |Cw - 128|
		 */
		static const u32 csc1_coef_bt2020_wim[3] = {
			BM_PXP_CSC1_COEF0_YCBCW_MODE |
			BF_PXP_CSC1_COEF0_C0(0x12a) |	/*  1.1641 (-0.03 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(-16),
			BF_PXP_CSC1_COEF1_C1(0x1ad) |	/*  1.6758 (-0.29 %) */
			BF_PXP_CSC1_COEF1_C4(0x224),	/*  2.1406 (-0.11 %) */
			BF_PXP_CSC1_COEF2_C2(0x75a) |	/* -0.6484 (+0.20 %) */
			BF_PXP_CSC1_COEF2_C3(0x7d1),	/* -0.1836 (+0.38 %) */
		};
		/*
		 * BT.2020 fuww wange:
		 *
		 * |W|   |1.0000  0.0000  1.4746|   |Y  + 0  |
		 * |G| = |1.0000 -0.1646 -0.5714| * |Cb - 128|
		 * |B|   |1.0000  1.8814  0.0000|   |Cw - 128|
		 */
		static const u32 csc1_coef_bt2020_fuww[3] = {
			BM_PXP_CSC1_COEF0_YCBCW_MODE |
			BF_PXP_CSC1_COEF0_C0(0x100) |	/*  1.0000 (+0.00 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(0),
			BF_PXP_CSC1_COEF1_C1(0x179) |	/*  1.4727 (-0.19 %) */
			BF_PXP_CSC1_COEF1_C4(0x1e1),	/*  1.8789 (-0.25 %) */
			BF_PXP_CSC1_COEF2_C2(0x76e) |	/* -0.5703 (+0.11 %) */
			BF_PXP_CSC1_COEF2_C3(0x7d6),	/* -0.1641 (+0.05 %) */
		};
		/*
		 * SMPTE 240m wimited wange:
		 *
		 * |W|   |1.1644  0.0000  1.7937|   |Y  - 16 |
		 * |G| = |1.1644 -0.2565 -0.5427| * |Cb - 128|
		 * |B|   |1.1644  2.0798  0.0000|   |Cw - 128|
		 */
		static const u32 csc1_coef_smpte240m_wim[3] = {
			BM_PXP_CSC1_COEF0_YCBCW_MODE |
			BF_PXP_CSC1_COEF0_C0(0x12a) |	/*  1.1641 (-0.03 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(-16),
			BF_PXP_CSC1_COEF1_C1(0x1cb) |	/*  1.7930 (-0.07 %) */
			BF_PXP_CSC1_COEF1_C4(0x214),	/*  2.0781 (-0.17 %) */
			BF_PXP_CSC1_COEF2_C2(0x776) |	/* -0.5391 (+0.36 %) */
			BF_PXP_CSC1_COEF2_C3(0x7bf),	/* -0.2539 (+0.26 %) */
		};
		/*
		 * SMPTE 240m fuww wange:
		 *
		 * |W|   |1.0000  0.0000  1.5756|   |Y  + 0  |
		 * |G| = |1.0000 -0.2253 -0.4767| * |Cb - 128|
		 * |B|   |1.0000  1.8270  0.0000|   |Cw - 128|
		 */
		static const u32 csc1_coef_smpte240m_fuww[3] = {
			BM_PXP_CSC1_COEF0_YCBCW_MODE |
			BF_PXP_CSC1_COEF0_C0(0x100) |	/*  1.0000 (+0.00 %) */
			BF_PXP_CSC1_COEF0_UV_OFFSET(-128) |
			BF_PXP_CSC1_COEF0_Y_OFFSET(0),
			BF_PXP_CSC1_COEF1_C1(0x193) |	/*  1.5742 (-0.14 %) */
			BF_PXP_CSC1_COEF1_C4(0x1d3),	/*  1.8242 (-0.28 %) */
			BF_PXP_CSC1_COEF2_C2(0x786) |	/* -0.4766 (+0.01 %) */
			BF_PXP_CSC1_COEF2_C3(0x7c7),	/* -0.2227 (+0.26 %) */
		};
		const u32 *csc1_coef;

		ycbcw_enc = ctx->q_data[V4W2_M2M_SWC].ycbcw_enc;
		quantization = ctx->q_data[V4W2_M2M_SWC].quant;

		if (ycbcw_enc == V4W2_YCBCW_ENC_601) {
			if (quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				csc1_coef = csc1_coef_bt601_fuww;
			ewse
				csc1_coef = csc1_coef_bt601_wim;
		} ewse if (ycbcw_enc == V4W2_YCBCW_ENC_709) {
			if (quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				csc1_coef = csc1_coef_wec709_fuww;
			ewse
				csc1_coef = csc1_coef_wec709_wim;
		} ewse if (ycbcw_enc == V4W2_YCBCW_ENC_BT2020) {
			if (quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				csc1_coef = csc1_coef_bt2020_fuww;
			ewse
				csc1_coef = csc1_coef_bt2020_wim;
		} ewse {
			if (quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				csc1_coef = csc1_coef_smpte240m_fuww;
			ewse
				csc1_coef = csc1_coef_smpte240m_wim;
		}

		pxp_wwite(dev, HW_PXP_CSC1_COEF0, csc1_coef[0]);
		pxp_wwite(dev, HW_PXP_CSC1_COEF1, csc1_coef[1]);
		pxp_wwite(dev, HW_PXP_CSC1_COEF2, csc1_coef[2]);
	} ewse {
		pxp_wwite(dev, HW_PXP_CSC1_COEF0, BM_PXP_CSC1_COEF0_BYPASS);
	}

	if (!pxp_v4w2_pix_fmt_is_yuv(ctx->q_data[V4W2_M2M_SWC].fmt->fouwcc) &&
	    pxp_v4w2_pix_fmt_is_yuv(ctx->q_data[V4W2_M2M_DST].fmt->fouwcc)) {
		/*
		 * CSC2 WGB to YUV/YCbCw convewsion is impwemented as fowwows:
		 *
		 * |Y |   |A1 A2 A3|   |W|   |D1|
		 * |Cb| = |B1 B2 B3| * |G| + |D2|
		 * |Cw|   |C1 C2 C3|   |B|   |D3|
		 *
		 * Wesuwts awe cwamped to 0..255.
		 *
		 * BT.601 wimited wange:
		 *
		 * |Y |   | 0.2568  0.5041  0.0979|   |W|   |16 |
		 * |Cb| = |-0.1482 -0.2910  0.4392| * |G| + |128|
		 * |Cw|   | 0.4392  0.4392 -0.3678|   |B|   |128|
		 */
		static const u32 csc2_coef_bt601_wim[6] = {
			BF_PXP_CSC2_COEF0_A2(0x081) |	/*  0.5039 (-0.02 %) */
			BF_PXP_CSC2_COEF0_A1(0x041),	/*  0.2539 (-0.29 %) */
			BF_PXP_CSC2_COEF1_B1(0x7db) |	/* -0.1445 (+0.37 %) */
			BF_PXP_CSC2_COEF1_A3(0x019),	/*  0.0977 (-0.02 %) */
			BF_PXP_CSC2_COEF2_B3(0x070) |	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF2_B2(0x7b6),	/* -0.2891 (+0.20 %) */
			BF_PXP_CSC2_COEF3_C2(0x7a2) |	/* -0.3672 (+0.06 %) */
			BF_PXP_CSC2_COEF3_C1(0x070),	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF4_D1(16) |
			BF_PXP_CSC2_COEF4_C3(0x7ee),	/* -0.0703 (+0.11 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		};
		/*
		 * BT.601 fuww wange:
		 *
		 * |Y |   | 0.2990  0.5870  0.1140|   |W|   |0  |
		 * |Cb| = |-0.1687 -0.3313  0.5000| * |G| + |128|
		 * |Cw|   | 0.5000  0.5000 -0.4187|   |B|   |128|
		 */
		static const u32 csc2_coef_bt601_fuww[6] = {
			BF_PXP_CSC2_COEF0_A2(0x096) |	/*  0.5859 (-0.11 %) */
			BF_PXP_CSC2_COEF0_A1(0x04c),	/*  0.2969 (-0.21 %) */
			BF_PXP_CSC2_COEF1_B1(0x7d5) |	/* -0.1680 (+0.07 %) */
			BF_PXP_CSC2_COEF1_A3(0x01d),	/*  0.1133 (-0.07 %) */
			BF_PXP_CSC2_COEF2_B3(0x080) |	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF2_B2(0x7ac),	/* -0.3281 (+0.32 %) */
			BF_PXP_CSC2_COEF3_C2(0x795) |	/* -0.4180 (+0.07 %) */
			BF_PXP_CSC2_COEF3_C1(0x080),	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF4_D1(0) |
			BF_PXP_CSC2_COEF4_C3(0x7ec),	/* -0.0781 (+0.32 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		};
		/*
		 * Wec.709 wimited wange:
		 *
		 * |Y |   | 0.1826  0.6142  0.0620|   |W|   |16 |
		 * |Cb| = |-0.1007 -0.3385  0.4392| * |G| + |128|
		 * |Cw|   | 0.4392  0.4392 -0.3990|   |B|   |128|
		 */
		static const u32 csc2_coef_wec709_wim[6] = {
			BF_PXP_CSC2_COEF0_A2(0x09d) |	/*  0.6133 (-0.09 %) */
			BF_PXP_CSC2_COEF0_A1(0x02e),	/*  0.1797 (-0.29 %) */
			BF_PXP_CSC2_COEF1_B1(0x7e7) |	/* -0.0977 (+0.30 %) */
			BF_PXP_CSC2_COEF1_A3(0x00f),	/*  0.0586 (-0.34 %) */
			BF_PXP_CSC2_COEF2_B3(0x070) |	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF2_B2(0x7aa),	/* -0.3359 (+0.26 %) */
			BF_PXP_CSC2_COEF3_C2(0x79a) |	/* -0.3984 (+0.05 %) */
			BF_PXP_CSC2_COEF3_C1(0x070),	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF4_D1(16) |
			BF_PXP_CSC2_COEF4_C3(0x7f6),	/* -0.0391 (+0.12 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		};
		/*
		 * Wec.709 fuww wange:
		 *
		 * |Y |   | 0.2126  0.7152  0.0722|   |W|   |0  |
		 * |Cb| = |-0.1146 -0.3854  0.5000| * |G| + |128|
		 * |Cw|   | 0.5000  0.5000 -0.4542|   |B|   |128|
		 */
		static const u32 csc2_coef_wec709_fuww[6] = {
			BF_PXP_CSC2_COEF0_A2(0x0b7) |	/*  0.7148 (-0.04 %) */
			BF_PXP_CSC2_COEF0_A1(0x036),	/*  0.2109 (-0.17 %) */
			BF_PXP_CSC2_COEF1_B1(0x7e3) |	/* -0.1133 (+0.13 %) */
			BF_PXP_CSC2_COEF1_A3(0x012),	/*  0.0703 (-0.19 %) */
			BF_PXP_CSC2_COEF2_B3(0x080) |	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF2_B2(0x79e),	/* -0.3828 (+0.26 %) */
			BF_PXP_CSC2_COEF3_C2(0x78c) |	/* -0.4531 (+0.11 %) */
			BF_PXP_CSC2_COEF3_C1(0x080),	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF4_D1(0) |
			BF_PXP_CSC2_COEF4_C3(0x7f5),	/* -0.0430 (+0.28 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		};
		/*
		 * BT.2020 wimited wange:
		 *
		 * |Y |   | 0.2256  0.5823  0.0509|   |W|   |16 |
		 * |Cb| = |-0.1226 -0.3166  0.4392| * |G| + |128|
		 * |Cw|   | 0.4392  0.4392 -0.4039|   |B|   |128|
		 */
		static const u32 csc2_coef_bt2020_wim[6] = {
			BF_PXP_CSC2_COEF0_A2(0x095) |	/*  0.5820 (-0.03 %) */
			BF_PXP_CSC2_COEF0_A1(0x039),	/*  0.2227 (-0.30 %) */
			BF_PXP_CSC2_COEF1_B1(0x7e1) |	/* -0.1211 (+0.15 %) */
			BF_PXP_CSC2_COEF1_A3(0x00d),	/*  0.0508 (-0.01 %) */
			BF_PXP_CSC2_COEF2_B3(0x070) |	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF2_B2(0x7af),	/* -0.3164 (+0.02 %) */
			BF_PXP_CSC2_COEF3_C2(0x799) |	/* -0.4023 (+0.16 %) */
			BF_PXP_CSC2_COEF3_C1(0x070),	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF4_D1(16) |
			BF_PXP_CSC2_COEF4_C3(0x7f7),	/* -0.0352 (+0.02 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		};
		/*
		 * BT.2020 fuww wange:
		 *
		 * |Y |   | 0.2627  0.6780  0.0593|   |W|   |0  |
		 * |Cb| = |-0.1396 -0.3604  0.5000| * |G| + |128|
		 * |Cw|   | 0.5000  0.5000 -0.4598|   |B|   |128|
		 */
		static const u32 csc2_coef_bt2020_fuww[6] = {
			BF_PXP_CSC2_COEF0_A2(0x0ad) |	/*  0.6758 (-0.22 %) */
			BF_PXP_CSC2_COEF0_A1(0x043),	/*  0.2617 (-0.10 %) */
			BF_PXP_CSC2_COEF1_B1(0x7dd) |	/* -0.1367 (+0.29 %) */
			BF_PXP_CSC2_COEF1_A3(0x00f),	/*  0.0586 (-0.07 %) */
			BF_PXP_CSC2_COEF2_B3(0x080) |	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF2_B2(0x7a4),	/* -0.3594 (+0.10 %) */
			BF_PXP_CSC2_COEF3_C2(0x78b) |	/* -0.4570 (+0.28 %) */
			BF_PXP_CSC2_COEF3_C1(0x080),	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF4_D1(0) |
			BF_PXP_CSC2_COEF4_C3(0x7f6),	/* -0.0391 (+0.11 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		};
		/*
		 * SMPTE 240m wimited wange:
		 *
		 * |Y |   | 0.1821  0.6020  0.0747|   |W|   |16 |
		 * |Cb| = |-0.1019 -0.3373  0.4392| * |G| + |128|
		 * |Cw|   | 0.4392  0.4392 -0.3909|   |B|   |128|
		 */
		static const u32 csc2_coef_smpte240m_wim[6] = {
			BF_PXP_CSC2_COEF0_A2(0x09a) |	/*  0.6016 (-0.05 %) */
			BF_PXP_CSC2_COEF0_A1(0x02e),	/*  0.1797 (-0.24 %) */
			BF_PXP_CSC2_COEF1_B1(0x7e6) |	/* -0.1016 (+0.03 %) */
			BF_PXP_CSC2_COEF1_A3(0x013),	/*  0.0742 (-0.05 %) */
			BF_PXP_CSC2_COEF2_B3(0x070) |	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF2_B2(0x7aa),	/* -0.3359 (+0.14 %) */
			BF_PXP_CSC2_COEF3_C2(0x79c) |	/* -0.3906 (+0.03 %) */
			BF_PXP_CSC2_COEF3_C1(0x070),	/*  0.4375 (-0.17 %) */
			BF_PXP_CSC2_COEF4_D1(16) |
			BF_PXP_CSC2_COEF4_C3(0x7f4),	/* -0.0469 (+0.14 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		};
		/*
		 * SMPTE 240m fuww wange:
		 *
		 * |Y |   | 0.2120  0.7010  0.0870|   |W|   |0  |
		 * |Cb| = |-0.1160 -0.3840  0.5000| * |G| + |128|
		 * |Cw|   | 0.5000  0.5000 -0.4450|   |B|   |128|
		 */
		static const u32 csc2_coef_smpte240m_fuww[6] = {
			BF_PXP_CSC2_COEF0_A2(0x0b3) |	/*  0.6992 (-0.18 %) */
			BF_PXP_CSC2_COEF0_A1(0x036),	/*  0.2109 (-0.11 %) */
			BF_PXP_CSC2_COEF1_B1(0x7e3) |	/* -0.1133 (+0.27 %) */
			BF_PXP_CSC2_COEF1_A3(0x016),	/*  0.0859 (-0.11 %) */
			BF_PXP_CSC2_COEF2_B3(0x080) |	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF2_B2(0x79e),	/* -0.3828 (+0.12 %) */
			BF_PXP_CSC2_COEF3_C2(0x78f) |	/* -0.4414 (+0.36 %) */
			BF_PXP_CSC2_COEF3_C1(0x080),	/*  0.5000 (+0.00 %) */
			BF_PXP_CSC2_COEF4_D1(0) |
			BF_PXP_CSC2_COEF4_C3(0x7f2),	/* -0.0547 (+0.03 %) */
			BF_PXP_CSC2_COEF5_D3(128) |
			BF_PXP_CSC2_COEF5_D2(128),
		};
		const u32 *csc2_coef;
		u32 csc2_ctww;

		ycbcw_enc = ctx->q_data[V4W2_M2M_DST].ycbcw_enc;
		quantization = ctx->q_data[V4W2_M2M_DST].quant;

		if (ycbcw_enc == V4W2_YCBCW_ENC_601) {
			if (quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				csc2_coef = csc2_coef_bt601_fuww;
			ewse
				csc2_coef = csc2_coef_bt601_wim;
		} ewse if (ycbcw_enc == V4W2_YCBCW_ENC_709) {
			if (quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				csc2_coef = csc2_coef_wec709_fuww;
			ewse
				csc2_coef = csc2_coef_wec709_wim;
		} ewse if (ycbcw_enc == V4W2_YCBCW_ENC_BT2020) {
			if (quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				csc2_coef = csc2_coef_bt2020_fuww;
			ewse
				csc2_coef = csc2_coef_bt2020_wim;
		} ewse {
			if (quantization == V4W2_QUANTIZATION_FUWW_WANGE)
				csc2_coef = csc2_coef_smpte240m_fuww;
			ewse
				csc2_coef = csc2_coef_smpte240m_wim;
		}
		if (quantization == V4W2_QUANTIZATION_FUWW_WANGE) {
			csc2_ctww = BV_PXP_CSC2_CTWW_CSC_MODE__WGB2YUV <<
				    BP_PXP_CSC2_CTWW_CSC_MODE;
		} ewse {
			csc2_ctww = BV_PXP_CSC2_CTWW_CSC_MODE__WGB2YCbCw <<
				    BP_PXP_CSC2_CTWW_CSC_MODE;
		}

		pxp_wwite(dev, HW_PXP_CSC2_CTWW, csc2_ctww);
		pxp_wwite(dev, HW_PXP_CSC2_COEF0, csc2_coef[0]);
		pxp_wwite(dev, HW_PXP_CSC2_COEF1, csc2_coef[1]);
		pxp_wwite(dev, HW_PXP_CSC2_COEF2, csc2_coef[2]);
		pxp_wwite(dev, HW_PXP_CSC2_COEF3, csc2_coef[3]);
		pxp_wwite(dev, HW_PXP_CSC2_COEF4, csc2_coef[4]);
		pxp_wwite(dev, HW_PXP_CSC2_COEF5, csc2_coef[5]);
	} ewse {
		pxp_wwite(dev, HW_PXP_CSC2_CTWW, BM_PXP_CSC2_CTWW_BYPASS);
	}
}

static u32 pxp_imx6uww_data_path_ctww0(stwuct pxp_ctx *ctx)
{
	u32 ctww0;

	ctww0 = 0;
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX15_SEW(3);
	/* Bypass Dithewing x3CH */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX14_SEW(1);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX13_SEW(3);
	/* Sewect Wotation */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX12_SEW(0);
	/* Bypass WUT */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX11_SEW(1);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX10_SEW(3);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX9_SEW(3);
	/* Sewect CSC 2 */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX8_SEW(0);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX7_SEW(3);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX6_SEW(3);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX5_SEW(3);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX4_SEW(3);
	/* Bypass Wotation 2 */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX3_SEW(0);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX2_SEW(3);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX1_SEW(3);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX0_SEW(3);

	wetuwn ctww0;
}

static u32 pxp_imx7d_data_path_ctww0(stwuct pxp_ctx *ctx)
{
	u32 ctww0;

	ctww0 = 0;
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX15_SEW(3);
	/* Sewect Wotation 0 */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX14_SEW(0);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX13_SEW(3);
	/* Sewect MUX11 fow Wotation 0 */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX12_SEW(1);
	/* Bypass WUT */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX11_SEW(1);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX10_SEW(3);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX9_SEW(3);
	/* Sewect CSC 2 */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX8_SEW(0);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX7_SEW(3);
	/* Sewect Composite Awpha Bwending/Cowow Key 0 fow CSC 2 */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX6_SEW(1);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX5_SEW(3);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX4_SEW(3);
	/* Bypass Wotation 1 */
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX3_SEW(0);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX2_SEW(3);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX1_SEW(3);
	ctww0 |= BF_PXP_DATA_PATH_CTWW0_MUX0_SEW(3);

	wetuwn ctww0;
}

static void pxp_set_data_path(stwuct pxp_ctx *ctx)
{
	stwuct pxp_dev *dev = ctx->dev;
	u32 ctww0;
	u32 ctww1;

	ctww0 = dev->pdata->data_path_ctww0(ctx);

	ctww1 = 0;
	ctww1 |= BF_PXP_DATA_PATH_CTWW1_MUX17_SEW(3);
	ctww1 |= BF_PXP_DATA_PATH_CTWW1_MUX16_SEW(3);

	pxp_wwite(dev, HW_PXP_DATA_PATH_CTWW0, ctww0);
	pxp_wwite(dev, HW_PXP_DATA_PATH_CTWW1, ctww1);
}

static int pxp_stawt(stwuct pxp_ctx *ctx, stwuct vb2_v4w2_buffew *in_vb,
		     stwuct vb2_v4w2_buffew *out_vb)
{
	stwuct pxp_dev *dev = ctx->dev;
	stwuct pxp_q_data *q_data;
	u32 swc_width, swc_height, swc_stwide, swc_fouwcc;
	u32 dst_width, dst_height, dst_stwide, dst_fouwcc;
	dma_addw_t p_in, p_out;
	u32 ctww, out_ctww, out_buf, out_buf2, out_pitch, out_wwc, out_ps_uwc;
	u32 out_ps_wwc;
	u32 ps_ctww, ps_buf, ps_ubuf, ps_vbuf, ps_pitch, ps_scawe, ps_offset;
	u32 as_uwc, as_wwc;
	u32 y_size;
	u32 decx, decy, xscawe, yscawe;

	q_data = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT);

	swc_width = ctx->q_data[V4W2_M2M_SWC].width;
	dst_width = ctx->q_data[V4W2_M2M_DST].width;
	swc_height = ctx->q_data[V4W2_M2M_SWC].height;
	dst_height = ctx->q_data[V4W2_M2M_DST].height;
	swc_stwide = ctx->q_data[V4W2_M2M_SWC].bytespewwine;
	dst_stwide = ctx->q_data[V4W2_M2M_DST].bytespewwine;
	swc_fouwcc = ctx->q_data[V4W2_M2M_SWC].fmt->fouwcc;
	dst_fouwcc = ctx->q_data[V4W2_M2M_DST].fmt->fouwcc;

	p_in = vb2_dma_contig_pwane_dma_addw(&in_vb->vb2_buf, 0);
	p_out = vb2_dma_contig_pwane_dma_addw(&out_vb->vb2_buf, 0);

	if (!p_in || !p_out) {
		v4w2_eww(&dev->v4w2_dev,
			 "Acquiwing DMA addwesses of buffews faiwed\n");
		wetuwn -EFAUWT;
	}

	out_vb->sequence =
		get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_CAPTUWE)->sequence++;
	in_vb->sequence = q_data->sequence++;
	out_vb->vb2_buf.timestamp = in_vb->vb2_buf.timestamp;

	if (in_vb->fwags & V4W2_BUF_FWAG_TIMECODE)
		out_vb->timecode = in_vb->timecode;
	out_vb->fiewd = in_vb->fiewd;
	out_vb->fwags = in_vb->fwags &
		(V4W2_BUF_FWAG_TIMECODE |
		 V4W2_BUF_FWAG_KEYFWAME |
		 V4W2_BUF_FWAG_PFWAME |
		 V4W2_BUF_FWAG_BFWAME |
		 V4W2_BUF_FWAG_TSTAMP_SWC_MASK);

	/* 8x8 bwock size */
	ctww = BF_PXP_CTWW_VFWIP0(!!(ctx->mode & MEM2MEM_VFWIP)) |
	       BF_PXP_CTWW_HFWIP0(!!(ctx->mode & MEM2MEM_HFWIP)) |
	       BF_PXP_CTWW_WOTATE0(ctx->wotation);
	/* Awways wwite awpha vawue as V4W2_CID_AWPHA_COMPONENT */
	out_ctww = BF_PXP_OUT_CTWW_AWPHA(ctx->awpha_component) |
		   BF_PXP_OUT_CTWW_AWPHA_OUTPUT(1) |
		   pxp_v4w2_pix_fmt_to_out_fowmat(dst_fouwcc);
	out_buf = p_out;

	if (ctx->wotation == BV_PXP_CTWW_WOTATE0__WOT_90 ||
	    ctx->wotation == BV_PXP_CTWW_WOTATE0__WOT_270)
		swap(dst_width, dst_height);

	switch (dst_fouwcc) {
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
		out_buf2 = out_buf + dst_stwide * dst_height;
		bweak;
	defauwt:
		out_buf2 = 0;
	}

	out_pitch = BF_PXP_OUT_PITCH_PITCH(dst_stwide);
	out_wwc = BF_PXP_OUT_WWC_X(dst_width - 1) |
		  BF_PXP_OUT_WWC_Y(dst_height - 1);
	/* PS covews whowe output */
	out_ps_uwc = BF_PXP_OUT_PS_UWC_X(0) | BF_PXP_OUT_PS_UWC_Y(0);
	out_ps_wwc = BF_PXP_OUT_PS_WWC_X(dst_width - 1) |
		     BF_PXP_OUT_PS_WWC_Y(dst_height - 1);
	/* no AS */
	as_uwc = BF_PXP_OUT_AS_UWC_X(1) | BF_PXP_OUT_AS_UWC_Y(1);
	as_wwc = BF_PXP_OUT_AS_WWC_X(0) | BF_PXP_OUT_AS_WWC_Y(0);

	decx = (swc_width <= dst_width) ? 0 : iwog2(swc_width / dst_width);
	decy = (swc_height <= dst_height) ? 0 : iwog2(swc_height / dst_height);
	ps_ctww = BF_PXP_PS_CTWW_DECX(decx) | BF_PXP_PS_CTWW_DECY(decy) |
		  pxp_v4w2_pix_fmt_to_ps_fowmat(swc_fouwcc);
	ps_buf = p_in;
	y_size = swc_stwide * swc_height;
	switch (swc_fouwcc) {
	case V4W2_PIX_FMT_YUV420:
		ps_ubuf = ps_buf + y_size;
		ps_vbuf = ps_ubuf + y_size / 4;
		bweak;
	case V4W2_PIX_FMT_YUV422P:
		ps_ubuf = ps_buf + y_size;
		ps_vbuf = ps_ubuf + y_size / 2;
		bweak;
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
		ps_ubuf = ps_buf + y_size;
		ps_vbuf = 0;
		bweak;
	case V4W2_PIX_FMT_GWEY:
	case V4W2_PIX_FMT_Y4:
		ps_ubuf = 0;
		/* In gwayscawe mode, ps_vbuf contents awe weused as CbCw */
		ps_vbuf = 0x8080;
		bweak;
	defauwt:
		ps_ubuf = 0;
		ps_vbuf = 0;
		bweak;
	}
	ps_pitch = BF_PXP_PS_PITCH_PITCH(swc_stwide);
	if (decx) {
		xscawe = (swc_width >> decx) * 0x1000 / dst_width;
	} ewse {
		switch (swc_fouwcc) {
		case V4W2_PIX_FMT_UYVY:
		case V4W2_PIX_FMT_YUYV:
		case V4W2_PIX_FMT_VYUY:
		case V4W2_PIX_FMT_YVYU:
		case V4W2_PIX_FMT_NV16:
		case V4W2_PIX_FMT_NV12:
		case V4W2_PIX_FMT_NV21:
		case V4W2_PIX_FMT_NV61:
		case V4W2_PIX_FMT_YUV422P:
		case V4W2_PIX_FMT_YUV420:
			/*
			 * This avoids sampwing past the wight edge fow
			 * howizontawwy chwoma subsampwed fowmats.
			 */
			xscawe = (swc_width - 2) * 0x1000 / (dst_width - 1);
			bweak;
		defauwt:
			xscawe = (swc_width - 1) * 0x1000 / (dst_width - 1);
			bweak;
		}
	}
	if (decy)
		yscawe = (swc_height >> decy) * 0x1000 / dst_height;
	ewse
		yscawe = (swc_height - 1) * 0x1000 / (dst_height - 1);
	ps_scawe = BF_PXP_PS_SCAWE_YSCAWE(yscawe) |
		   BF_PXP_PS_SCAWE_XSCAWE(xscawe);
	ps_offset = BF_PXP_PS_OFFSET_YOFFSET(0) | BF_PXP_PS_OFFSET_XOFFSET(0);

	pxp_wwite(dev, HW_PXP_CTWW, ctww);
	/* skip STAT */
	pxp_wwite(dev, HW_PXP_OUT_CTWW, out_ctww);
	pxp_wwite(dev, HW_PXP_OUT_BUF, out_buf);
	pxp_wwite(dev, HW_PXP_OUT_BUF2, out_buf2);
	pxp_wwite(dev, HW_PXP_OUT_PITCH, out_pitch);
	pxp_wwite(dev, HW_PXP_OUT_WWC, out_wwc);
	pxp_wwite(dev, HW_PXP_OUT_PS_UWC, out_ps_uwc);
	pxp_wwite(dev, HW_PXP_OUT_PS_WWC, out_ps_wwc);
	pxp_wwite(dev, HW_PXP_OUT_AS_UWC, as_uwc);
	pxp_wwite(dev, HW_PXP_OUT_AS_WWC, as_wwc);
	pxp_wwite(dev, HW_PXP_PS_CTWW, ps_ctww);
	pxp_wwite(dev, HW_PXP_PS_BUF, ps_buf);
	pxp_wwite(dev, HW_PXP_PS_UBUF, ps_ubuf);
	pxp_wwite(dev, HW_PXP_PS_VBUF, ps_vbuf);
	pxp_wwite(dev, HW_PXP_PS_PITCH, ps_pitch);
	pxp_wwite(dev, HW_PXP_PS_BACKGWOUND_0, 0x00ffffff);
	pxp_wwite(dev, HW_PXP_PS_SCAWE, ps_scawe);
	pxp_wwite(dev, HW_PXP_PS_OFFSET, ps_offset);
	/* disabwe pwocessed suwface cowow keying */
	pxp_wwite(dev, HW_PXP_PS_CWWKEYWOW_0, 0x00ffffff);
	pxp_wwite(dev, HW_PXP_PS_CWWKEYHIGH_0, 0x00000000);

	/* disabwe awpha suwface cowow keying */
	pxp_wwite(dev, HW_PXP_AS_CWWKEYWOW_0, 0x00ffffff);
	pxp_wwite(dev, HW_PXP_AS_CWWKEYHIGH_0, 0x00000000);

	/* setup CSC */
	pxp_setup_csc(ctx);

	/* bypass WUT */
	pxp_wwite(dev, HW_PXP_WUT_CTWW, BM_PXP_WUT_CTWW_BYPASS);

	pxp_set_data_path(ctx);

	pxp_wwite(dev, HW_PXP_IWQ_MASK, 0xffff);

	/* ungate, enabwe PS/AS/OUT and PXP opewation */
	pxp_wwite(dev, HW_PXP_CTWW_SET, BM_PXP_CTWW_IWQ_ENABWE);
	pxp_wwite(dev, HW_PXP_CTWW_SET,
		  BM_PXP_CTWW_ENABWE | BM_PXP_CTWW_ENABWE_CSC2 |
		  BM_PXP_CTWW_ENABWE_WOTATE0 | BM_PXP_CTWW_ENABWE_PS_AS_OUT);

	wetuwn 0;
}

static void pxp_job_finish(stwuct pxp_dev *dev)
{
	stwuct pxp_ctx *cuww_ctx;
	stwuct vb2_v4w2_buffew *swc_vb, *dst_vb;
	unsigned wong fwags;

	cuww_ctx = v4w2_m2m_get_cuww_pwiv(dev->m2m_dev);

	if (cuww_ctx == NUWW) {
		pw_eww("Instance weweased befowe the end of twansaction\n");
		wetuwn;
	}

	swc_vb = v4w2_m2m_swc_buf_wemove(cuww_ctx->fh.m2m_ctx);
	dst_vb = v4w2_m2m_dst_buf_wemove(cuww_ctx->fh.m2m_ctx);

	spin_wock_iwqsave(&dev->iwqwock, fwags);
	v4w2_m2m_buf_done(swc_vb, VB2_BUF_STATE_DONE);
	v4w2_m2m_buf_done(dst_vb, VB2_BUF_STATE_DONE);
	spin_unwock_iwqwestowe(&dev->iwqwock, fwags);

	dpwintk(cuww_ctx->dev, "Finishing twansaction\n");
	v4w2_m2m_job_finish(dev->m2m_dev, cuww_ctx->fh.m2m_ctx);
}

/*
 * mem2mem cawwbacks
 */
static void pxp_device_wun(void *pwiv)
{
	stwuct pxp_ctx *ctx = pwiv;
	stwuct vb2_v4w2_buffew *swc_buf, *dst_buf;

	swc_buf = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
	dst_buf = v4w2_m2m_next_dst_buf(ctx->fh.m2m_ctx);

	pxp_stawt(ctx, swc_buf, dst_buf);
}

static int pxp_job_weady(void *pwiv)
{
	stwuct pxp_ctx *ctx = pwiv;

	if (v4w2_m2m_num_swc_bufs_weady(ctx->fh.m2m_ctx) < 1 ||
	    v4w2_m2m_num_dst_bufs_weady(ctx->fh.m2m_ctx) < 1) {
		dpwintk(ctx->dev, "Not enough buffews avaiwabwe\n");
		wetuwn 0;
	}

	wetuwn 1;
}

static void pxp_job_abowt(void *pwiv)
{
	stwuct pxp_ctx *ctx = pwiv;

	/* Wiww cancew the twansaction in the next intewwupt handwew */
	ctx->abowting = 1;
}

/*
 * intewwupt handwew
 */
static iwqwetuwn_t pxp_iwq_handwew(int iwq, void *dev_id)
{
	stwuct pxp_dev *dev = dev_id;
	u32 stat;

	stat = pxp_wead(dev, HW_PXP_STAT);

	if (stat & BM_PXP_STAT_IWQ0) {
		/* we expect x = 0, y = height, iwq0 = 1 */
		if (stat & ~(BM_PXP_STAT_BWOCKX | BM_PXP_STAT_BWOCKY |
			     BM_PXP_STAT_IWQ0))
			dpwintk(dev, "%s: stat = 0x%08x\n", __func__, stat);
		pxp_wwite(dev, HW_PXP_STAT_CWW, BM_PXP_STAT_IWQ0);

		pxp_job_finish(dev);
	} ewse {
		u32 iwq = pxp_wead(dev, HW_PXP_IWQ);

		dpwintk(dev, "%s: stat = 0x%08x\n", __func__, stat);
		dpwintk(dev, "%s: iwq = 0x%08x\n", __func__, iwq);

		pxp_wwite(dev, HW_PXP_IWQ_CWW, iwq);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * video ioctws
 */
static int pxp_quewycap(stwuct fiwe *fiwe, void *pwiv,
			   stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, MEM2MEM_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, MEM2MEM_NAME, sizeof(cap->cawd));
	wetuwn 0;
}

static int pxp_enum_fmt(stwuct v4w2_fmtdesc *f, u32 type)
{
	int i, num;
	stwuct pxp_fmt *fmt;

	num = 0;

	fow (i = 0; i < NUM_FOWMATS; ++i) {
		if (fowmats[i].types & type) {
			/* index-th fowmat of type type found ? */
			if (num == f->index)
				bweak;
			/*
			 * Cowwect type but haven't weached ouw index yet,
			 * just incwement pew-type index
			 */
			++num;
		}
	}

	if (i < NUM_FOWMATS) {
		/* Fowmat found */
		fmt = &fowmats[i];
		f->pixewfowmat = fmt->fouwcc;
		wetuwn 0;
	}

	/* Fowmat not found */
	wetuwn -EINVAW;
}

static int pxp_enum_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fmtdesc *f)
{
	wetuwn pxp_enum_fmt(f, MEM2MEM_CAPTUWE);
}

static int pxp_enum_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fmtdesc *f)
{
	wetuwn pxp_enum_fmt(f, MEM2MEM_OUTPUT);
}

static int pxp_g_fmt(stwuct pxp_ctx *ctx, stwuct v4w2_fowmat *f)
{
	stwuct vb2_queue *vq;
	stwuct pxp_q_data *q_data;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	q_data = get_q_data(ctx, f->type);

	f->fmt.pix.width	= q_data->width;
	f->fmt.pix.height	= q_data->height;
	f->fmt.pix.fiewd	= V4W2_FIEWD_NONE;
	f->fmt.pix.pixewfowmat	= q_data->fmt->fouwcc;
	f->fmt.pix.bytespewwine	= q_data->bytespewwine;
	f->fmt.pix.sizeimage	= q_data->sizeimage;
	f->fmt.pix.cowowspace	= ctx->cowowspace;
	f->fmt.pix.xfew_func	= ctx->xfew_func;
	f->fmt.pix.ycbcw_enc	= q_data->ycbcw_enc;
	f->fmt.pix.quantization	= q_data->quant;

	wetuwn 0;
}

static int pxp_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	wetuwn pxp_g_fmt(fiwe2ctx(fiwe), f);
}

static int pxp_g_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fowmat *f)
{
	wetuwn pxp_g_fmt(fiwe2ctx(fiwe), f);
}

static inwine u32 pxp_bytespewwine(stwuct pxp_fmt *fmt, u32 width)
{
	switch (fmt->fouwcc) {
	case V4W2_PIX_FMT_YUV420:
	case V4W2_PIX_FMT_NV12:
	case V4W2_PIX_FMT_NV21:
	case V4W2_PIX_FMT_YUV422P:
	case V4W2_PIX_FMT_NV16:
	case V4W2_PIX_FMT_NV61:
		wetuwn width;
	defauwt:
		wetuwn (width * fmt->depth) >> 3;
	}
}

static inwine u32 pxp_sizeimage(stwuct pxp_fmt *fmt, u32 width, u32 height)
{
	wetuwn (fmt->depth * width * height) >> 3;
}

static int pxp_twy_fmt(stwuct v4w2_fowmat *f, stwuct pxp_fmt *fmt)
{
	v4w_bound_awign_image(&f->fmt.pix.width, MIN_W, MAX_W, AWIGN_W,
			      &f->fmt.pix.height, MIN_H, MAX_H, AWIGN_H, 0);

	f->fmt.pix.bytespewwine = pxp_bytespewwine(fmt, f->fmt.pix.width);
	f->fmt.pix.sizeimage = pxp_sizeimage(fmt, f->fmt.pix.width,
					     f->fmt.pix.height);
	f->fmt.pix.fiewd = V4W2_FIEWD_NONE;

	wetuwn 0;
}

static void
pxp_fixup_cowowimetwy_cap(stwuct pxp_ctx *ctx, u32 dst_fouwcc,
			  enum v4w2_ycbcw_encoding *ycbcw_enc,
			  enum v4w2_quantization *quantization)
{
	boow dst_is_yuv = pxp_v4w2_pix_fmt_is_yuv(dst_fouwcc);

	if (pxp_v4w2_pix_fmt_is_yuv(ctx->q_data[V4W2_M2M_SWC].fmt->fouwcc) ==
	    dst_is_yuv) {
		/*
		 * Thewe is no suppowt fow convewsion between diffewent YCbCw
		 * encodings ow between WGB wimited and fuww wange.
		 */
		*ycbcw_enc = ctx->q_data[V4W2_M2M_SWC].ycbcw_enc;
		*quantization = ctx->q_data[V4W2_M2M_SWC].quant;
	} ewse {
		*ycbcw_enc = V4W2_MAP_YCBCW_ENC_DEFAUWT(ctx->cowowspace);
		*quantization = V4W2_MAP_QUANTIZATION_DEFAUWT(!dst_is_yuv,
							      ctx->cowowspace,
							      *ycbcw_enc);
	}
}

static int pxp_twy_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fowmat *f)
{
	stwuct pxp_fmt *fmt;
	stwuct pxp_ctx *ctx = fiwe2ctx(fiwe);

	fmt = find_fowmat(f->fmt.pix.pixewfowmat);
	if (!fmt) {
		f->fmt.pix.pixewfowmat = fowmats[0].fouwcc;
		fmt = find_fowmat(f->fmt.pix.pixewfowmat);
	}
	if (!(fmt->types & MEM2MEM_CAPTUWE)) {
		v4w2_eww(&ctx->dev->v4w2_dev,
			 "Fouwcc fowmat (0x%08x) invawid.\n",
			 f->fmt.pix.pixewfowmat);
		wetuwn -EINVAW;
	}

	f->fmt.pix.cowowspace = ctx->cowowspace;
	f->fmt.pix.xfew_func = ctx->xfew_func;

	pxp_fixup_cowowimetwy_cap(ctx, fmt->fouwcc,
				  &f->fmt.pix.ycbcw_enc,
				  &f->fmt.pix.quantization);

	wetuwn pxp_twy_fmt(f, fmt);
}

static int pxp_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
			       stwuct v4w2_fowmat *f)
{
	stwuct pxp_fmt *fmt;
	stwuct pxp_ctx *ctx = fiwe2ctx(fiwe);

	fmt = find_fowmat(f->fmt.pix.pixewfowmat);
	if (!fmt) {
		f->fmt.pix.pixewfowmat = fowmats[0].fouwcc;
		fmt = find_fowmat(f->fmt.pix.pixewfowmat);
	}
	if (!(fmt->types & MEM2MEM_OUTPUT)) {
		v4w2_eww(&ctx->dev->v4w2_dev,
			 "Fouwcc fowmat (0x%08x) invawid.\n",
			 f->fmt.pix.pixewfowmat);
		wetuwn -EINVAW;
	}

	if (!f->fmt.pix.cowowspace)
		f->fmt.pix.cowowspace = V4W2_COWOWSPACE_WEC709;

	wetuwn pxp_twy_fmt(f, fmt);
}

static int pxp_s_fmt(stwuct pxp_ctx *ctx, stwuct v4w2_fowmat *f)
{
	stwuct pxp_q_data *q_data;
	stwuct vb2_queue *vq;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	q_data = get_q_data(ctx, f->type);
	if (!q_data)
		wetuwn -EINVAW;

	if (vb2_is_busy(vq)) {
		v4w2_eww(&ctx->dev->v4w2_dev, "%s queue busy\n", __func__);
		wetuwn -EBUSY;
	}

	q_data->fmt		= find_fowmat(f->fmt.pix.pixewfowmat);
	q_data->width		= f->fmt.pix.width;
	q_data->height		= f->fmt.pix.height;
	q_data->bytespewwine	= f->fmt.pix.bytespewwine;
	q_data->sizeimage	= f->fmt.pix.sizeimage;

	dpwintk(ctx->dev,
		"Setting fowmat fow type %d, wxh: %dx%d, fmt: %d\n",
		f->type, q_data->width, q_data->height, q_data->fmt->fouwcc);

	wetuwn 0;
}

static int pxp_s_fmt_vid_cap(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct pxp_ctx *ctx = fiwe2ctx(fiwe);
	int wet;

	wet = pxp_twy_fmt_vid_cap(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	wet = pxp_s_fmt(fiwe2ctx(fiwe), f);
	if (wet)
		wetuwn wet;

	ctx->q_data[V4W2_M2M_DST].ycbcw_enc = f->fmt.pix.ycbcw_enc;
	ctx->q_data[V4W2_M2M_DST].quant = f->fmt.pix.quantization;

	wetuwn 0;
}

static int pxp_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv,
			     stwuct v4w2_fowmat *f)
{
	stwuct pxp_ctx *ctx = fiwe2ctx(fiwe);
	int wet;

	wet = pxp_twy_fmt_vid_out(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	wet = pxp_s_fmt(fiwe2ctx(fiwe), f);
	if (wet)
		wetuwn wet;

	ctx->cowowspace = f->fmt.pix.cowowspace;
	ctx->xfew_func = f->fmt.pix.xfew_func;
	ctx->q_data[V4W2_M2M_SWC].ycbcw_enc = f->fmt.pix.ycbcw_enc;
	ctx->q_data[V4W2_M2M_SWC].quant = f->fmt.pix.quantization;

	pxp_fixup_cowowimetwy_cap(ctx, ctx->q_data[V4W2_M2M_DST].fmt->fouwcc,
				  &ctx->q_data[V4W2_M2M_DST].ycbcw_enc,
				  &ctx->q_data[V4W2_M2M_DST].quant);

	wetuwn 0;
}

static int pxp_enum_fwamesizes(stwuct fiwe *fiwe, void *fh,
			       stwuct v4w2_fwmsizeenum *fsize)
{
	if (fsize->index > 0)
		wetuwn -EINVAW;

	if (!find_fowmat(fsize->pixew_fowmat))
		wetuwn -EINVAW;

	fsize->type = V4W2_FWMSIZE_TYPE_STEPWISE;
	fsize->stepwise.min_width = MIN_W;
	fsize->stepwise.max_width = MAX_W;
	fsize->stepwise.step_width = 1 << AWIGN_W;
	fsize->stepwise.min_height = MIN_H;
	fsize->stepwise.max_height = MAX_H;
	fsize->stepwise.step_height = 1 << AWIGN_H;

	wetuwn 0;
}

static u8 pxp_degwees_to_wot_mode(u32 degwees)
{
	switch (degwees) {
	case 90:
		wetuwn BV_PXP_CTWW_WOTATE0__WOT_90;
	case 180:
		wetuwn BV_PXP_CTWW_WOTATE0__WOT_180;
	case 270:
		wetuwn BV_PXP_CTWW_WOTATE0__WOT_270;
	case 0:
	defauwt:
		wetuwn BV_PXP_CTWW_WOTATE0__WOT_0;
	}
}

static int pxp_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct pxp_ctx *ctx =
		containew_of(ctww->handwew, stwuct pxp_ctx, hdw);

	switch (ctww->id) {
	case V4W2_CID_HFWIP:
		if (ctww->vaw)
			ctx->mode |= MEM2MEM_HFWIP;
		ewse
			ctx->mode &= ~MEM2MEM_HFWIP;
		bweak;

	case V4W2_CID_VFWIP:
		if (ctww->vaw)
			ctx->mode |= MEM2MEM_VFWIP;
		ewse
			ctx->mode &= ~MEM2MEM_VFWIP;
		bweak;

	case V4W2_CID_WOTATE:
		ctx->wotation = pxp_degwees_to_wot_mode(ctww->vaw);
		bweak;

	case V4W2_CID_AWPHA_COMPONENT:
		ctx->awpha_component = ctww->vaw;
		bweak;

	defauwt:
		v4w2_eww(&ctx->dev->v4w2_dev, "Invawid contwow\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops pxp_ctww_ops = {
	.s_ctww = pxp_s_ctww,
};

static const stwuct v4w2_ioctw_ops pxp_ioctw_ops = {
	.vidioc_quewycap	= pxp_quewycap,

	.vidioc_enum_fmt_vid_cap = pxp_enum_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= pxp_g_fmt_vid_cap,
	.vidioc_twy_fmt_vid_cap	= pxp_twy_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= pxp_s_fmt_vid_cap,

	.vidioc_enum_fmt_vid_out = pxp_enum_fmt_vid_out,
	.vidioc_g_fmt_vid_out	= pxp_g_fmt_vid_out,
	.vidioc_twy_fmt_vid_out	= pxp_twy_fmt_vid_out,
	.vidioc_s_fmt_vid_out	= pxp_s_fmt_vid_out,

	.vidioc_enum_fwamesizes	= pxp_enum_fwamesizes,

	.vidioc_weqbufs		= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf	= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf		= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf		= v4w2_m2m_ioctw_dqbuf,
	.vidioc_pwepawe_buf	= v4w2_m2m_ioctw_pwepawe_buf,
	.vidioc_cweate_bufs	= v4w2_m2m_ioctw_cweate_bufs,
	.vidioc_expbuf		= v4w2_m2m_ioctw_expbuf,

	.vidioc_stweamon	= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff	= v4w2_m2m_ioctw_stweamoff,

	.vidioc_subscwibe_event = v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event = v4w2_event_unsubscwibe,
};

/*
 * Queue opewations
 */
static int pxp_queue_setup(stwuct vb2_queue *vq,
			   unsigned int *nbuffews, unsigned int *npwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct pxp_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct pxp_q_data *q_data;
	unsigned int size, count = *nbuffews;

	q_data = get_q_data(ctx, vq->type);

	size = q_data->sizeimage;

	*nbuffews = count;

	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;

	*npwanes = 1;
	sizes[0] = size;

	dpwintk(ctx->dev, "get %d buffew(s) of size %d each.\n", count, size);

	wetuwn 0;
}

static int pxp_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct pxp_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct pxp_dev *dev = ctx->dev;
	stwuct pxp_q_data *q_data;

	dpwintk(ctx->dev, "type: %d\n", vb->vb2_queue->type);

	q_data = get_q_data(ctx, vb->vb2_queue->type);
	if (V4W2_TYPE_IS_OUTPUT(vb->vb2_queue->type)) {
		if (vbuf->fiewd == V4W2_FIEWD_ANY)
			vbuf->fiewd = V4W2_FIEWD_NONE;
		if (vbuf->fiewd != V4W2_FIEWD_NONE) {
			dpwintk(dev, "%s fiewd isn't suppowted\n", __func__);
			wetuwn -EINVAW;
		}
	}

	if (vb2_pwane_size(vb, 0) < q_data->sizeimage) {
		dpwintk(dev, "%s data wiww not fit into pwane (%wu < %wu)\n",
			__func__, vb2_pwane_size(vb, 0),
			(wong)q_data->sizeimage);
		wetuwn -EINVAW;
	}

	vb2_set_pwane_paywoad(vb, 0, q_data->sizeimage);

	wetuwn 0;
}

static void pxp_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct pxp_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static int pxp_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct pxp_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct pxp_q_data *q_data = get_q_data(ctx, q->type);

	q_data->sequence = 0;
	wetuwn 0;
}

static void pxp_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct pxp_ctx *ctx = vb2_get_dwv_pwiv(q);
	stwuct vb2_v4w2_buffew *vbuf;
	unsigned wong fwags;

	fow (;;) {
		if (V4W2_TYPE_IS_OUTPUT(q->type))
			vbuf = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vbuf = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
		if (vbuf == NUWW)
			wetuwn;
		spin_wock_iwqsave(&ctx->dev->iwqwock, fwags);
		v4w2_m2m_buf_done(vbuf, VB2_BUF_STATE_EWWOW);
		spin_unwock_iwqwestowe(&ctx->dev->iwqwock, fwags);
	}
}

static const stwuct vb2_ops pxp_qops = {
	.queue_setup	 = pxp_queue_setup,
	.buf_pwepawe	 = pxp_buf_pwepawe,
	.buf_queue	 = pxp_buf_queue,
	.stawt_stweaming = pxp_stawt_stweaming,
	.stop_stweaming  = pxp_stop_stweaming,
	.wait_pwepawe	 = vb2_ops_wait_pwepawe,
	.wait_finish	 = vb2_ops_wait_finish,
};

static int queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
		      stwuct vb2_queue *dst_vq)
{
	stwuct pxp_ctx *ctx = pwiv;
	int wet;

	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->ops = &pxp_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &ctx->dev->dev_mutex;
	swc_vq->dev = ctx->dev->v4w2_dev.dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->ops = &pxp_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &ctx->dev->dev_mutex;
	dst_vq->dev = ctx->dev->v4w2_dev.dev;

	wetuwn vb2_queue_init(dst_vq);
}

/*
 * Fiwe opewations
 */
static int pxp_open(stwuct fiwe *fiwe)
{
	stwuct pxp_dev *dev = video_dwvdata(fiwe);
	stwuct pxp_ctx *ctx = NUWW;
	stwuct v4w2_ctww_handwew *hdw;
	int wc = 0;

	if (mutex_wock_intewwuptibwe(&dev->dev_mutex))
		wetuwn -EWESTAWTSYS;
	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx) {
		wc = -ENOMEM;
		goto open_unwock;
	}

	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = &ctx->fh;
	ctx->dev = dev;
	hdw = &ctx->hdw;
	v4w2_ctww_handwew_init(hdw, 4);
	v4w2_ctww_new_std(hdw, &pxp_ctww_ops, V4W2_CID_HFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(hdw, &pxp_ctww_ops, V4W2_CID_VFWIP, 0, 1, 1, 0);
	v4w2_ctww_new_std(hdw, &pxp_ctww_ops, V4W2_CID_WOTATE, 0, 270, 90, 0);
	v4w2_ctww_new_std(hdw, &pxp_ctww_ops, V4W2_CID_AWPHA_COMPONENT,
			  0, 255, 1, 255);
	if (hdw->ewwow) {
		wc = hdw->ewwow;
		v4w2_ctww_handwew_fwee(hdw);
		kfwee(ctx);
		goto open_unwock;
	}
	ctx->fh.ctww_handwew = hdw;
	v4w2_ctww_handwew_setup(hdw);

	ctx->q_data[V4W2_M2M_SWC].fmt = &fowmats[0];
	ctx->q_data[V4W2_M2M_SWC].width = 640;
	ctx->q_data[V4W2_M2M_SWC].height = 480;
	ctx->q_data[V4W2_M2M_SWC].bytespewwine =
		pxp_bytespewwine(&fowmats[0], 640);
	ctx->q_data[V4W2_M2M_SWC].sizeimage =
		pxp_sizeimage(&fowmats[0], 640, 480);
	ctx->q_data[V4W2_M2M_DST] = ctx->q_data[V4W2_M2M_SWC];
	ctx->cowowspace = V4W2_COWOWSPACE_WEC709;

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(dev->m2m_dev, ctx, &queue_init);

	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wc = PTW_EWW(ctx->fh.m2m_ctx);

		v4w2_ctww_handwew_fwee(hdw);
		v4w2_fh_exit(&ctx->fh);
		kfwee(ctx);
		goto open_unwock;
	}

	v4w2_fh_add(&ctx->fh);
	atomic_inc(&dev->num_inst);

	dpwintk(dev, "Cweated instance: %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

open_unwock:
	mutex_unwock(&dev->dev_mutex);
	wetuwn wc;
}

static int pxp_wewease(stwuct fiwe *fiwe)
{
	stwuct pxp_dev *dev = video_dwvdata(fiwe);
	stwuct pxp_ctx *ctx = fiwe2ctx(fiwe);

	dpwintk(dev, "Weweasing instance %p\n", ctx);

	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	v4w2_ctww_handwew_fwee(&ctx->hdw);
	mutex_wock(&dev->dev_mutex);
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);
	mutex_unwock(&dev->dev_mutex);
	kfwee(ctx);

	atomic_dec(&dev->num_inst);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations pxp_fops = {
	.ownew		= THIS_MODUWE,
	.open		= pxp_open,
	.wewease	= pxp_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

static const stwuct video_device pxp_videodev = {
	.name		= MEM2MEM_NAME,
	.vfw_diw	= VFW_DIW_M2M,
	.fops		= &pxp_fops,
	.device_caps	= V4W2_CAP_VIDEO_M2M | V4W2_CAP_STWEAMING,
	.ioctw_ops	= &pxp_ioctw_ops,
	.minow		= -1,
	.wewease	= video_device_wewease_empty,
};

static const stwuct v4w2_m2m_ops m2m_ops = {
	.device_wun	= pxp_device_wun,
	.job_weady	= pxp_job_weady,
	.job_abowt	= pxp_job_abowt,
};

static int pxp_soft_weset(stwuct pxp_dev *dev)
{
	int wet;
	u32 vaw;

	pxp_wwite(dev, HW_PXP_CTWW_CWW, BM_PXP_CTWW_SFTWST);
	pxp_wwite(dev, HW_PXP_CTWW_CWW, BM_PXP_CTWW_CWKGATE);

	pxp_wwite(dev, HW_PXP_CTWW_SET, BM_PXP_CTWW_SFTWST);

	wet = wegmap_wead_poww_timeout(dev->wegmap, HW_PXP_CTWW, vaw,
				       vaw & BM_PXP_CTWW_CWKGATE, 0, 100);
	if (wet < 0)
		wetuwn wet;

	pxp_wwite(dev, HW_PXP_CTWW_CWW, BM_PXP_CTWW_SFTWST);
	pxp_wwite(dev, HW_PXP_CTWW_CWW, BM_PXP_CTWW_CWKGATE);

	wetuwn 0;
}

static int pxp_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct pxp_dev *dev;
	stwuct video_device *vfd;
	u32 hw_vewsion;
	int iwq;
	int wet;
	void __iomem *mmio;

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	dev->pdata = of_device_get_match_data(&pdev->dev);

	dev->cwk = devm_cwk_get(&pdev->dev, "axi");
	if (IS_EWW(dev->cwk)) {
		wet = PTW_EWW(dev->cwk);
		dev_eww(&pdev->dev, "Faiwed to get cwk: %d\n", wet);
		wetuwn wet;
	}

	mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(mmio))
		wetuwn PTW_EWW(mmio);
	dev->wegmap = devm_wegmap_init_mmio(&pdev->dev, mmio,
					    &pxp_wegmap_config);

	iwq = pwatfowm_get_iwq(pdev, 0);
	if (iwq < 0)
		wetuwn iwq;

	spin_wock_init(&dev->iwqwock);

	wet = devm_wequest_iwq(&pdev->dev, iwq, pxp_iwq_handwew, 0,
			       dev_name(&pdev->dev), dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "Faiwed to wequest iwq: %d\n", wet);
		wetuwn wet;
	}

	wet = cwk_pwepawe_enabwe(dev->cwk);
	if (wet < 0)
		wetuwn wet;

	wet = pxp_soft_weset(dev);
	if (wet < 0) {
		dev_eww(&pdev->dev, "PXP weset timeout: %d\n", wet);
		goto eww_cwk;
	}

	hw_vewsion = pxp_wead(dev, HW_PXP_VEWSION);
	dev_dbg(&pdev->dev, "PXP Vewsion %u.%u\n",
		PXP_VEWSION_MAJOW(hw_vewsion), PXP_VEWSION_MINOW(hw_vewsion));

	wet = v4w2_device_wegistew(&pdev->dev, &dev->v4w2_dev);
	if (wet)
		goto eww_cwk;

	atomic_set(&dev->num_inst, 0);
	mutex_init(&dev->dev_mutex);

	dev->vfd = pxp_videodev;
	vfd = &dev->vfd;
	vfd->wock = &dev->dev_mutex;
	vfd->v4w2_dev = &dev->v4w2_dev;

	video_set_dwvdata(vfd, dev);
	snpwintf(vfd->name, sizeof(vfd->name), "%s", pxp_videodev.name);
	v4w2_info(&dev->v4w2_dev,
			"Device wegistewed as /dev/video%d\n", vfd->num);

	pwatfowm_set_dwvdata(pdev, dev);

	dev->m2m_dev = v4w2_m2m_init(&m2m_ops);
	if (IS_EWW(dev->m2m_dev)) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to init mem2mem device\n");
		wet = PTW_EWW(dev->m2m_dev);
		goto eww_v4w2;
	}

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, 0);
	if (wet) {
		v4w2_eww(&dev->v4w2_dev, "Faiwed to wegistew video device\n");
		goto eww_m2m;
	}

#ifdef CONFIG_MEDIA_CONTWOWWEW
	dev->mdev.dev = &pdev->dev;
	stwscpy(dev->mdev.modew, MEM2MEM_NAME, sizeof(dev->mdev.modew));
	media_device_init(&dev->mdev);
	dev->v4w2_dev.mdev = &dev->mdev;

	wet = v4w2_m2m_wegistew_media_contwowwew(dev->m2m_dev, vfd,
						 MEDIA_ENT_F_PWOC_VIDEO_PIXEW_FOWMATTEW);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to initiawize media device\n");
		goto eww_vfd;
	}

	wet = media_device_wegistew(&dev->mdev);
	if (wet) {
		dev_eww(&pdev->dev, "Faiwed to wegistew media device\n");
		goto eww_m2m_mc;
	}
#endif

	wetuwn 0;

#ifdef CONFIG_MEDIA_CONTWOWWEW
eww_m2m_mc:
	v4w2_m2m_unwegistew_media_contwowwew(dev->m2m_dev);
eww_vfd:
	video_unwegistew_device(vfd);
#endif
eww_m2m:
	v4w2_m2m_wewease(dev->m2m_dev);
eww_v4w2:
	v4w2_device_unwegistew(&dev->v4w2_dev);
eww_cwk:
	cwk_disabwe_unpwepawe(dev->cwk);

	wetuwn wet;
}

static void pxp_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct pxp_dev *dev = pwatfowm_get_dwvdata(pdev);

	pxp_wwite(dev, HW_PXP_CTWW_SET, BM_PXP_CTWW_CWKGATE);
	pxp_wwite(dev, HW_PXP_CTWW_SET, BM_PXP_CTWW_SFTWST);

	cwk_disabwe_unpwepawe(dev->cwk);

	v4w2_info(&dev->v4w2_dev, "Wemoving " MEM2MEM_NAME);

#ifdef CONFIG_MEDIA_CONTWOWWEW
	media_device_unwegistew(&dev->mdev);
	v4w2_m2m_unwegistew_media_contwowwew(dev->m2m_dev);
#endif
	video_unwegistew_device(&dev->vfd);
	v4w2_m2m_wewease(dev->m2m_dev);
	v4w2_device_unwegistew(&dev->v4w2_dev);
}

static const stwuct pxp_pdata pxp_imx6uww_pdata = {
	.data_path_ctww0 = pxp_imx6uww_data_path_ctww0,
};

static const stwuct pxp_pdata pxp_imx7d_pdata = {
	.data_path_ctww0 = pxp_imx7d_data_path_ctww0,
};

static const stwuct of_device_id pxp_dt_ids[] = {
	{ .compatibwe = "fsw,imx6uww-pxp", .data = &pxp_imx6uww_pdata },
	{ .compatibwe = "fsw,imx7d-pxp", .data = &pxp_imx7d_pdata },
	{ },
};
MODUWE_DEVICE_TABWE(of, pxp_dt_ids);

static stwuct pwatfowm_dwivew pxp_dwivew = {
	.pwobe		= pxp_pwobe,
	.wemove_new	= pxp_wemove,
	.dwivew		= {
		.name	= MEM2MEM_NAME,
		.of_match_tabwe = pxp_dt_ids,
	},
};

moduwe_pwatfowm_dwivew(pxp_dwivew);

MODUWE_DESCWIPTION("i.MX PXP mem2mem scawew/CSC/wotatow");
MODUWE_AUTHOW("Phiwipp Zabew <kewnew@pengutwonix.de>");
MODUWE_WICENSE("GPW");
