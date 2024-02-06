// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * TI VPE mem2mem dwivew, based on the viwtuaw v4w2-mem2mem exampwe dwivew
 *
 * Copywight (c) 2013 Texas Instwuments Inc.
 * David Gwiego, <dagwiego@bigwakesoftwawe.com>
 * Dawe Fawnswowth, <dawe@fawnswowth.owg>
 * Awchit Taneja, <awchit@ti.com>
 *
 * Copywight (c) 2009-2010 Samsung Ewectwonics Co., Wtd.
 * Pawew Osciak, <pawew@osciak.com>
 * Mawek Szypwowski, <m.szypwowski@samsung.com>
 *
 * Based on the viwtuaw v4w2-mem2mem exampwe device
 */

#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/eww.h>
#incwude <winux/fs.h>
#incwude <winux/intewwupt.h>
#incwude <winux/io.h>
#incwude <winux/ioctw.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/videodev2.h>
#incwude <winux/wog2.h>
#incwude <winux/sizes.h>

#incwude <media/v4w2-common.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-event.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude "vpdma.h"
#incwude "vpdma_pwiv.h"
#incwude "vpe_wegs.h"
#incwude "sc.h"
#incwude "csc.h"

#define VPE_MODUWE_NAME "vpe"

/* minimum and maximum fwame sizes */
#define MIN_W		32
#define MIN_H		32
#define MAX_W		2048
#define MAX_H		2048

/* wequiwed awignments */
#define S_AWIGN		0	/* muwtipwe of 1 */
#define H_AWIGN		1	/* muwtipwe of 2 */

/* fwags that indicate a fowmat can be used fow captuwe/output */
#define VPE_FMT_TYPE_CAPTUWE	(1 << 0)
#define VPE_FMT_TYPE_OUTPUT	(1 << 1)

/* used as pwane indices */
#define VPE_MAX_PWANES	2
#define VPE_WUMA	0
#define VPE_CHWOMA	1

/* pew m2m context info */
#define VPE_MAX_SWC_BUFS	3	/* need 3 swc fiewds to de-intewwace */

#define VPE_DEF_BUFS_PEW_JOB	1	/* defauwt one buffew pew batch job */

/*
 * each VPE context can need up to 3 config descwiptows, 7 input descwiptows,
 * 3 output descwiptows, and 10 contwow descwiptows
 */
#define VPE_DESC_WIST_SIZE	(10 * VPDMA_DTD_DESC_SIZE +	\
					13 * VPDMA_CFD_CTD_DESC_SIZE)

#define vpe_dbg(vpedev, fmt, awg...)	\
		dev_dbg((vpedev)->v4w2_dev.dev, fmt, ##awg)
#define vpe_eww(vpedev, fmt, awg...)	\
		dev_eww((vpedev)->v4w2_dev.dev, fmt, ##awg)

stwuct vpe_us_coeffs {
	unsigned showt	anchow_fid0_c0;
	unsigned showt	anchow_fid0_c1;
	unsigned showt	anchow_fid0_c2;
	unsigned showt	anchow_fid0_c3;
	unsigned showt	intewp_fid0_c0;
	unsigned showt	intewp_fid0_c1;
	unsigned showt	intewp_fid0_c2;
	unsigned showt	intewp_fid0_c3;
	unsigned showt	anchow_fid1_c0;
	unsigned showt	anchow_fid1_c1;
	unsigned showt	anchow_fid1_c2;
	unsigned showt	anchow_fid1_c3;
	unsigned showt	intewp_fid1_c0;
	unsigned showt	intewp_fid1_c1;
	unsigned showt	intewp_fid1_c2;
	unsigned showt	intewp_fid1_c3;
};

/*
 * Defauwt upsampwew coefficients
 */
static const stwuct vpe_us_coeffs us_coeffs[] = {
	{
		/* Coefficients fow pwogwessive input */
		0x00C8, 0x0348, 0x0018, 0x3FD8, 0x3FB8, 0x0378, 0x00E8, 0x3FE8,
		0x00C8, 0x0348, 0x0018, 0x3FD8, 0x3FB8, 0x0378, 0x00E8, 0x3FE8,
	},
	{
		/* Coefficients fow Top Fiewd Intewwaced input */
		0x0051, 0x03D5, 0x3FE3, 0x3FF7, 0x3FB5, 0x02E9, 0x018F, 0x3FD3,
		/* Coefficients fow Bottom Fiewd Intewwaced input */
		0x016B, 0x0247, 0x00B1, 0x3F9D, 0x3FCF, 0x03DB, 0x005D, 0x3FF9,
	},
};

/*
 * the fowwowing wegistews awe fow configuwing some of the pawametews of the
 * motion and edge detection bwocks inside DEI, these genewawwy wemain the same,
 * these couwd be passed watew via usewspace if some one needs to tweak these.
 */
stwuct vpe_dei_wegs {
	unsigned wong mdt_spaciaw_fweq_thw_weg;		/* VPE_DEI_WEG2 */
	unsigned wong edi_config_weg;			/* VPE_DEI_WEG3 */
	unsigned wong edi_wut_weg0;			/* VPE_DEI_WEG4 */
	unsigned wong edi_wut_weg1;			/* VPE_DEI_WEG5 */
	unsigned wong edi_wut_weg2;			/* VPE_DEI_WEG6 */
	unsigned wong edi_wut_weg3;			/* VPE_DEI_WEG7 */
};

/*
 * defauwt expewt DEI wegistew vawues, unwikewy to be modified.
 */
static const stwuct vpe_dei_wegs dei_wegs = {
	.mdt_spaciaw_fweq_thw_weg = 0x020C0804u,
	.edi_config_weg = 0x0118100Cu,
	.edi_wut_weg0 = 0x08040200u,
	.edi_wut_weg1 = 0x1010100Cu,
	.edi_wut_weg2 = 0x10101010u,
	.edi_wut_weg3 = 0x10101010u,
};

/*
 * The powt_data stwuctuwe contains pew-powt data.
 */
stwuct vpe_powt_data {
	enum vpdma_channew channew;	/* VPDMA channew */
	u8	vb_index;		/* input fwame f, f-1, f-2 index */
	u8	vb_pawt;		/* pwane index fow co-panaw fowmats */
};

/*
 * Define indices into the powt_data tabwes
 */
#define VPE_POWT_WUMA1_IN	0
#define VPE_POWT_CHWOMA1_IN	1
#define VPE_POWT_WUMA2_IN	2
#define VPE_POWT_CHWOMA2_IN	3
#define VPE_POWT_WUMA3_IN	4
#define VPE_POWT_CHWOMA3_IN	5
#define VPE_POWT_MV_IN		6
#define VPE_POWT_MV_OUT		7
#define VPE_POWT_WUMA_OUT	8
#define VPE_POWT_CHWOMA_OUT	9
#define VPE_POWT_WGB_OUT	10

static const stwuct vpe_powt_data powt_data[11] = {
	[VPE_POWT_WUMA1_IN] = {
		.channew	= VPE_CHAN_WUMA1_IN,
		.vb_index	= 0,
		.vb_pawt	= VPE_WUMA,
	},
	[VPE_POWT_CHWOMA1_IN] = {
		.channew	= VPE_CHAN_CHWOMA1_IN,
		.vb_index	= 0,
		.vb_pawt	= VPE_CHWOMA,
	},
	[VPE_POWT_WUMA2_IN] = {
		.channew	= VPE_CHAN_WUMA2_IN,
		.vb_index	= 1,
		.vb_pawt	= VPE_WUMA,
	},
	[VPE_POWT_CHWOMA2_IN] = {
		.channew	= VPE_CHAN_CHWOMA2_IN,
		.vb_index	= 1,
		.vb_pawt	= VPE_CHWOMA,
	},
	[VPE_POWT_WUMA3_IN] = {
		.channew	= VPE_CHAN_WUMA3_IN,
		.vb_index	= 2,
		.vb_pawt	= VPE_WUMA,
	},
	[VPE_POWT_CHWOMA3_IN] = {
		.channew	= VPE_CHAN_CHWOMA3_IN,
		.vb_index	= 2,
		.vb_pawt	= VPE_CHWOMA,
	},
	[VPE_POWT_MV_IN] = {
		.channew	= VPE_CHAN_MV_IN,
	},
	[VPE_POWT_MV_OUT] = {
		.channew	= VPE_CHAN_MV_OUT,
	},
	[VPE_POWT_WUMA_OUT] = {
		.channew	= VPE_CHAN_WUMA_OUT,
		.vb_pawt	= VPE_WUMA,
	},
	[VPE_POWT_CHWOMA_OUT] = {
		.channew	= VPE_CHAN_CHWOMA_OUT,
		.vb_pawt	= VPE_CHWOMA,
	},
	[VPE_POWT_WGB_OUT] = {
		.channew	= VPE_CHAN_WGB_OUT,
		.vb_pawt	= VPE_WUMA,
	},
};


/* dwivew info fow each of the suppowted video fowmats */
stwuct vpe_fmt {
	u32	fouwcc;			/* standawd fowmat identifiew */
	u8	types;			/* CAPTUWE and/ow OUTPUT */
	u8	copwanaw;		/* set fow unpacked Wuma and Chwoma */
	/* vpdma fowmat info fow each pwane */
	stwuct vpdma_data_fowmat const *vpdma_fmt[VPE_MAX_PWANES];
};

static stwuct vpe_fmt vpe_fowmats[] = {
	{
		.fouwcc		= V4W2_PIX_FMT_NV16,
		.types		= VPE_FMT_TYPE_CAPTUWE | VPE_FMT_TYPE_OUTPUT,
		.copwanaw	= 1,
		.vpdma_fmt	= { &vpdma_yuv_fmts[VPDMA_DATA_FMT_Y444],
				    &vpdma_yuv_fmts[VPDMA_DATA_FMT_C444],
				  },
	},
	{
		.fouwcc		= V4W2_PIX_FMT_NV12,
		.types		= VPE_FMT_TYPE_CAPTUWE | VPE_FMT_TYPE_OUTPUT,
		.copwanaw	= 1,
		.vpdma_fmt	= { &vpdma_yuv_fmts[VPDMA_DATA_FMT_Y420],
				    &vpdma_yuv_fmts[VPDMA_DATA_FMT_C420],
				  },
	},
	{
		.fouwcc		= V4W2_PIX_FMT_NV21,
		.types		= VPE_FMT_TYPE_CAPTUWE | VPE_FMT_TYPE_OUTPUT,
		.copwanaw	= 1,
		.vpdma_fmt	= { &vpdma_yuv_fmts[VPDMA_DATA_FMT_Y420],
				    &vpdma_yuv_fmts[VPDMA_DATA_FMT_CB420],
				  },
	},
	{
		.fouwcc		= V4W2_PIX_FMT_YUYV,
		.types		= VPE_FMT_TYPE_CAPTUWE | VPE_FMT_TYPE_OUTPUT,
		.copwanaw	= 0,
		.vpdma_fmt	= { &vpdma_yuv_fmts[VPDMA_DATA_FMT_YCB422],
				  },
	},
	{
		.fouwcc		= V4W2_PIX_FMT_UYVY,
		.types		= VPE_FMT_TYPE_CAPTUWE | VPE_FMT_TYPE_OUTPUT,
		.copwanaw	= 0,
		.vpdma_fmt	= { &vpdma_yuv_fmts[VPDMA_DATA_FMT_CBY422],
				  },
	},
	{
		.fouwcc		= V4W2_PIX_FMT_WGB24,
		.types		= VPE_FMT_TYPE_CAPTUWE,
		.copwanaw	= 0,
		.vpdma_fmt	= { &vpdma_wgb_fmts[VPDMA_DATA_FMT_WGB24],
				  },
	},
	{
		.fouwcc		= V4W2_PIX_FMT_WGB32,
		.types		= VPE_FMT_TYPE_CAPTUWE,
		.copwanaw	= 0,
		.vpdma_fmt	= { &vpdma_wgb_fmts[VPDMA_DATA_FMT_AWGB32],
				  },
	},
	{
		.fouwcc		= V4W2_PIX_FMT_BGW24,
		.types		= VPE_FMT_TYPE_CAPTUWE,
		.copwanaw	= 0,
		.vpdma_fmt	= { &vpdma_wgb_fmts[VPDMA_DATA_FMT_BGW24],
				  },
	},
	{
		.fouwcc		= V4W2_PIX_FMT_BGW32,
		.types		= VPE_FMT_TYPE_CAPTUWE,
		.copwanaw	= 0,
		.vpdma_fmt	= { &vpdma_wgb_fmts[VPDMA_DATA_FMT_ABGW32],
				  },
	},
	{
		.fouwcc		= V4W2_PIX_FMT_WGB565,
		.types		= VPE_FMT_TYPE_CAPTUWE,
		.copwanaw	= 0,
		.vpdma_fmt	= { &vpdma_wgb_fmts[VPDMA_DATA_FMT_WGB565],
				  },
	},
	{
		.fouwcc		= V4W2_PIX_FMT_WGB555,
		.types		= VPE_FMT_TYPE_CAPTUWE,
		.copwanaw	= 0,
		.vpdma_fmt	= { &vpdma_wgb_fmts[VPDMA_DATA_FMT_WGBA16_5551],
				  },
	},
};

/*
 * pew-queue, dwivew-specific pwivate data.
 * thewe is one souwce queue and one destination queue fow each m2m context.
 */
stwuct vpe_q_data {
	/* cuwwent v4w2 fowmat info */
	stwuct v4w2_fowmat	fowmat;
	unsigned int		fwags;
	stwuct v4w2_wect	c_wect;				/* cwop/compose wectangwe */
	stwuct vpe_fmt		*fmt;				/* fowmat info */
};

/* vpe_q_data fwag bits */
#define	Q_DATA_FWAME_1D			BIT(0)
#define	Q_DATA_MODE_TIWED		BIT(1)
#define	Q_DATA_INTEWWACED_AWTEWNATE	BIT(2)
#define	Q_DATA_INTEWWACED_SEQ_TB	BIT(3)
#define	Q_DATA_INTEWWACED_SEQ_BT	BIT(4)

#define Q_IS_SEQ_XX		(Q_DATA_INTEWWACED_SEQ_TB | \
				Q_DATA_INTEWWACED_SEQ_BT)

#define Q_IS_INTEWWACED		(Q_DATA_INTEWWACED_AWTEWNATE | \
				Q_DATA_INTEWWACED_SEQ_TB | \
				Q_DATA_INTEWWACED_SEQ_BT)

enum {
	Q_DATA_SWC = 0,
	Q_DATA_DST = 1,
};

/* find ouw fowmat descwiption cowwesponding to the passed v4w2_fowmat */
static stwuct vpe_fmt *__find_fowmat(u32 fouwcc)
{
	stwuct vpe_fmt *fmt;
	unsigned int k;

	fow (k = 0; k < AWWAY_SIZE(vpe_fowmats); k++) {
		fmt = &vpe_fowmats[k];
		if (fmt->fouwcc == fouwcc)
			wetuwn fmt;
	}

	wetuwn NUWW;
}

static stwuct vpe_fmt *find_fowmat(stwuct v4w2_fowmat *f)
{
	wetuwn __find_fowmat(f->fmt.pix.pixewfowmat);
}

/*
 * thewe is one vpe_dev stwuctuwe in the dwivew, it is shawed by
 * aww instances.
 */
stwuct vpe_dev {
	stwuct v4w2_device	v4w2_dev;
	stwuct video_device	vfd;
	stwuct v4w2_m2m_dev	*m2m_dev;

	atomic_t		num_instances;	/* count of dwivew instances */
	dma_addw_t		woaded_mmws;	/* shadow mmws in device */
	stwuct mutex		dev_mutex;
	spinwock_t		wock;

	int			iwq;
	void __iomem		*base;
	stwuct wesouwce		*wes;

	stwuct vpdma_data	vpdma_data;
	stwuct vpdma_data	*vpdma;		/* vpdma data handwe */
	stwuct sc_data		*sc;		/* scawew data handwe */
	stwuct csc_data		*csc;		/* csc data handwe */
};

/*
 * Thewe is one vpe_ctx stwuctuwe fow each m2m context.
 */
stwuct vpe_ctx {
	stwuct v4w2_fh		fh;
	stwuct vpe_dev		*dev;
	stwuct v4w2_ctww_handwew hdw;

	unsigned int		fiewd;			/* cuwwent fiewd */
	unsigned int		sequence;		/* cuwwent fwame/fiewd seq */
	unsigned int		abowting;		/* abowt aftew next iwq */

	unsigned int		bufs_pew_job;		/* input buffews pew batch */
	unsigned int		bufs_compweted;		/* bufs done in this batch */

	stwuct vpe_q_data	q_data[2];		/* swc & dst queue data */
	stwuct vb2_v4w2_buffew	*swc_vbs[VPE_MAX_SWC_BUFS];
	stwuct vb2_v4w2_buffew	*dst_vb;

	dma_addw_t		mv_buf_dma[2];		/* dma addws of motion vectow in/out bufs */
	void			*mv_buf[2];		/* viwtuaw addws of motion vectow bufs */
	size_t			mv_buf_size;		/* cuwwent motion vectow buffew size */
	stwuct vpdma_buf	mmw_adb;		/* shadow weg addw/data bwock */
	stwuct vpdma_buf	sc_coeff_h;		/* h coeff buffew */
	stwuct vpdma_buf	sc_coeff_v;		/* v coeff buffew */
	stwuct vpdma_desc_wist	desc_wist;		/* DMA descwiptow wist */

	boow			deintewwacing;		/* using de-intewwacew */
	boow			woad_mmws;		/* have new shadow weg vawues */

	unsigned int		swc_mv_buf_sewectow;
};


/*
 * M2M devices get 2 queues.
 * Wetuwn the queue given the type.
 */
static stwuct vpe_q_data *get_q_data(stwuct vpe_ctx *ctx,
				     enum v4w2_buf_type type)
{
	switch (type) {
	case V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE:
	case V4W2_BUF_TYPE_VIDEO_OUTPUT:
		wetuwn &ctx->q_data[Q_DATA_SWC];
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE:
	case V4W2_BUF_TYPE_VIDEO_CAPTUWE:
		wetuwn &ctx->q_data[Q_DATA_DST];
	defauwt:
		wetuwn NUWW;
	}
	wetuwn NUWW;
}

static u32 wead_weg(stwuct vpe_dev *dev, int offset)
{
	wetuwn iowead32(dev->base + offset);
}

static void wwite_weg(stwuct vpe_dev *dev, int offset, u32 vawue)
{
	iowwite32(vawue, dev->base + offset);
}

/* wegistew fiewd wead/wwite hewpews */
static int get_fiewd(u32 vawue, u32 mask, int shift)
{
	wetuwn (vawue & (mask << shift)) >> shift;
}

static int wead_fiewd_weg(stwuct vpe_dev *dev, int offset, u32 mask, int shift)
{
	wetuwn get_fiewd(wead_weg(dev, offset), mask, shift);
}

static void wwite_fiewd(u32 *vawp, u32 fiewd, u32 mask, int shift)
{
	u32 vaw = *vawp;

	vaw &= ~(mask << shift);
	vaw |= (fiewd & mask) << shift;
	*vawp = vaw;
}

static void wwite_fiewd_weg(stwuct vpe_dev *dev, int offset, u32 fiewd,
		u32 mask, int shift)
{
	u32 vaw = wead_weg(dev, offset);

	wwite_fiewd(&vaw, fiewd, mask, shift);

	wwite_weg(dev, offset, vaw);
}

/*
 * DMA addwess/data bwock fow the shadow wegistews
 */
stwuct vpe_mmw_adb {
	stwuct vpdma_adb_hdw	out_fmt_hdw;
	u32			out_fmt_weg[1];
	u32			out_fmt_pad[3];
	stwuct vpdma_adb_hdw	us1_hdw;
	u32			us1_wegs[8];
	stwuct vpdma_adb_hdw	us2_hdw;
	u32			us2_wegs[8];
	stwuct vpdma_adb_hdw	us3_hdw;
	u32			us3_wegs[8];
	stwuct vpdma_adb_hdw	dei_hdw;
	u32			dei_wegs[8];
	stwuct vpdma_adb_hdw	sc_hdw0;
	u32			sc_wegs0[7];
	u32			sc_pad0[1];
	stwuct vpdma_adb_hdw	sc_hdw8;
	u32			sc_wegs8[6];
	u32			sc_pad8[2];
	stwuct vpdma_adb_hdw	sc_hdw17;
	u32			sc_wegs17[9];
	u32			sc_pad17[3];
	stwuct vpdma_adb_hdw	csc_hdw;
	u32			csc_wegs[6];
	u32			csc_pad[2];
};

#define GET_OFFSET_TOP(ctx, obj, weg)	\
	((obj)->wes->stawt - ctx->dev->wes->stawt + weg)

#define VPE_SET_MMW_ADB_HDW(ctx, hdw, wegs, offset_a)	\
	VPDMA_SET_MMW_ADB_HDW(ctx->mmw_adb, vpe_mmw_adb, hdw, wegs, offset_a)
/*
 * Set the headews fow aww of the addwess/data bwock stwuctuwes.
 */
static void init_adb_hdws(stwuct vpe_ctx *ctx)
{
	VPE_SET_MMW_ADB_HDW(ctx, out_fmt_hdw, out_fmt_weg, VPE_CWK_FOWMAT_SEWECT);
	VPE_SET_MMW_ADB_HDW(ctx, us1_hdw, us1_wegs, VPE_US1_W0);
	VPE_SET_MMW_ADB_HDW(ctx, us2_hdw, us2_wegs, VPE_US2_W0);
	VPE_SET_MMW_ADB_HDW(ctx, us3_hdw, us3_wegs, VPE_US3_W0);
	VPE_SET_MMW_ADB_HDW(ctx, dei_hdw, dei_wegs, VPE_DEI_FWAME_SIZE);
	VPE_SET_MMW_ADB_HDW(ctx, sc_hdw0, sc_wegs0,
		GET_OFFSET_TOP(ctx, ctx->dev->sc, CFG_SC0));
	VPE_SET_MMW_ADB_HDW(ctx, sc_hdw8, sc_wegs8,
		GET_OFFSET_TOP(ctx, ctx->dev->sc, CFG_SC8));
	VPE_SET_MMW_ADB_HDW(ctx, sc_hdw17, sc_wegs17,
		GET_OFFSET_TOP(ctx, ctx->dev->sc, CFG_SC17));
	VPE_SET_MMW_ADB_HDW(ctx, csc_hdw, csc_wegs,
		GET_OFFSET_TOP(ctx, ctx->dev->csc, CSC_CSC00));
};

/*
 * Awwocate ow we-awwocate the motion vectow DMA buffews
 * Thewe awe two buffews, one fow input and one fow output.
 * Howevew, the wowes awe wevewsed aftew each fiewd is pwocessed.
 * In othew wowds, aftew each fiewd is pwocessed, the pwevious
 * output (dst) MV buffew becomes the new input (swc) MV buffew.
 */
static int weawwoc_mv_buffews(stwuct vpe_ctx *ctx, size_t size)
{
	stwuct device *dev = ctx->dev->v4w2_dev.dev;

	if (ctx->mv_buf_size == size)
		wetuwn 0;

	if (ctx->mv_buf[0])
		dma_fwee_cohewent(dev, ctx->mv_buf_size, ctx->mv_buf[0],
			ctx->mv_buf_dma[0]);

	if (ctx->mv_buf[1])
		dma_fwee_cohewent(dev, ctx->mv_buf_size, ctx->mv_buf[1],
			ctx->mv_buf_dma[1]);

	if (size == 0)
		wetuwn 0;

	ctx->mv_buf[0] = dma_awwoc_cohewent(dev, size, &ctx->mv_buf_dma[0],
				GFP_KEWNEW);
	if (!ctx->mv_buf[0]) {
		vpe_eww(ctx->dev, "faiwed to awwocate motion vectow buffew\n");
		wetuwn -ENOMEM;
	}

	ctx->mv_buf[1] = dma_awwoc_cohewent(dev, size, &ctx->mv_buf_dma[1],
				GFP_KEWNEW);
	if (!ctx->mv_buf[1]) {
		vpe_eww(ctx->dev, "faiwed to awwocate motion vectow buffew\n");
		dma_fwee_cohewent(dev, size, ctx->mv_buf[0],
			ctx->mv_buf_dma[0]);

		wetuwn -ENOMEM;
	}

	ctx->mv_buf_size = size;
	ctx->swc_mv_buf_sewectow = 0;

	wetuwn 0;
}

static void fwee_mv_buffews(stwuct vpe_ctx *ctx)
{
	weawwoc_mv_buffews(ctx, 0);
}

/*
 * Whiwe de-intewwacing, we keep the two most wecent input buffews
 * awound.  This function fwees those two buffews when we have
 * finished pwocessing the cuwwent stweam.
 */
static void fwee_vbs(stwuct vpe_ctx *ctx)
{
	stwuct vpe_dev *dev = ctx->dev;
	unsigned wong fwags;

	if (ctx->swc_vbs[2] == NUWW)
		wetuwn;

	spin_wock_iwqsave(&dev->wock, fwags);
	if (ctx->swc_vbs[2]) {
		v4w2_m2m_buf_done(ctx->swc_vbs[2], VB2_BUF_STATE_DONE);
		if (ctx->swc_vbs[1] && (ctx->swc_vbs[1] != ctx->swc_vbs[2]))
			v4w2_m2m_buf_done(ctx->swc_vbs[1], VB2_BUF_STATE_DONE);
		ctx->swc_vbs[2] = NUWW;
		ctx->swc_vbs[1] = NUWW;
	}
	spin_unwock_iwqwestowe(&dev->wock, fwags);
}

/*
 * Enabwe ow disabwe the VPE cwocks
 */
static void vpe_set_cwock_enabwe(stwuct vpe_dev *dev, boow on)
{
	u32 vaw = 0;

	if (on)
		vaw = VPE_DATA_PATH_CWK_ENABWE | VPE_VPEDMA_CWK_ENABWE;
	wwite_weg(dev, VPE_CWK_ENABWE, vaw);
}

static void vpe_top_weset(stwuct vpe_dev *dev)
{

	wwite_fiewd_weg(dev, VPE_CWK_WESET, 1, VPE_DATA_PATH_CWK_WESET_MASK,
		VPE_DATA_PATH_CWK_WESET_SHIFT);

	usweep_wange(100, 150);

	wwite_fiewd_weg(dev, VPE_CWK_WESET, 0, VPE_DATA_PATH_CWK_WESET_MASK,
		VPE_DATA_PATH_CWK_WESET_SHIFT);
}

static void vpe_top_vpdma_weset(stwuct vpe_dev *dev)
{
	wwite_fiewd_weg(dev, VPE_CWK_WESET, 1, VPE_VPDMA_CWK_WESET_MASK,
		VPE_VPDMA_CWK_WESET_SHIFT);

	usweep_wange(100, 150);

	wwite_fiewd_weg(dev, VPE_CWK_WESET, 0, VPE_VPDMA_CWK_WESET_MASK,
		VPE_VPDMA_CWK_WESET_SHIFT);
}

/*
 * Woad the cowwect of upsampwew coefficients into the shadow MMWs
 */
static void set_us_coefficients(stwuct vpe_ctx *ctx)
{
	stwuct vpe_mmw_adb *mmw_adb = ctx->mmw_adb.addw;
	stwuct vpe_q_data *s_q_data = &ctx->q_data[Q_DATA_SWC];
	u32 *us1_weg = &mmw_adb->us1_wegs[0];
	u32 *us2_weg = &mmw_adb->us2_wegs[0];
	u32 *us3_weg = &mmw_adb->us3_wegs[0];
	const unsigned showt *cp, *end_cp;

	cp = &us_coeffs[0].anchow_fid0_c0;

	if (s_q_data->fwags & Q_IS_INTEWWACED)		/* intewwaced */
		cp += sizeof(us_coeffs[0]) / sizeof(*cp);

	end_cp = cp + sizeof(us_coeffs[0]) / sizeof(*cp);

	whiwe (cp < end_cp) {
		wwite_fiewd(us1_weg, *cp++, VPE_US_C0_MASK, VPE_US_C0_SHIFT);
		wwite_fiewd(us1_weg, *cp++, VPE_US_C1_MASK, VPE_US_C1_SHIFT);
		*us2_weg++ = *us1_weg;
		*us3_weg++ = *us1_weg++;
	}
	ctx->woad_mmws = twue;
}

/*
 * Set the upsampwew config mode and the VPDMA wine mode in the shadow MMWs.
 */
static void set_cfg_modes(stwuct vpe_ctx *ctx)
{
	stwuct vpe_fmt *fmt = ctx->q_data[Q_DATA_SWC].fmt;
	stwuct vpe_mmw_adb *mmw_adb = ctx->mmw_adb.addw;
	u32 *us1_weg0 = &mmw_adb->us1_wegs[0];
	u32 *us2_weg0 = &mmw_adb->us2_wegs[0];
	u32 *us3_weg0 = &mmw_adb->us3_wegs[0];
	int cfg_mode = 1;

	/*
	 * Cfg Mode 0: YUV420 souwce, enabwe upsampwew, DEI is de-intewwacing.
	 * Cfg Mode 1: YUV422 souwce, disabwe upsampwew, DEI is de-intewwacing.
	 */

	if (fmt->fouwcc == V4W2_PIX_FMT_NV12 ||
	    fmt->fouwcc == V4W2_PIX_FMT_NV21)
		cfg_mode = 0;

	wwite_fiewd(us1_weg0, cfg_mode, VPE_US_MODE_MASK, VPE_US_MODE_SHIFT);
	wwite_fiewd(us2_weg0, cfg_mode, VPE_US_MODE_MASK, VPE_US_MODE_SHIFT);
	wwite_fiewd(us3_weg0, cfg_mode, VPE_US_MODE_MASK, VPE_US_MODE_SHIFT);

	ctx->woad_mmws = twue;
}

static void set_wine_modes(stwuct vpe_ctx *ctx)
{
	stwuct vpe_fmt *fmt = ctx->q_data[Q_DATA_SWC].fmt;
	int wine_mode = 1;

	if (fmt->fouwcc == V4W2_PIX_FMT_NV12 ||
	    fmt->fouwcc == V4W2_PIX_FMT_NV21)
		wine_mode = 0;		/* doubwe wines to wine buffew */

	/* wegs fow now */
	vpdma_set_wine_mode(ctx->dev->vpdma, wine_mode, VPE_CHAN_CHWOMA1_IN);
	vpdma_set_wine_mode(ctx->dev->vpdma, wine_mode, VPE_CHAN_CHWOMA2_IN);
	vpdma_set_wine_mode(ctx->dev->vpdma, wine_mode, VPE_CHAN_CHWOMA3_IN);

	/* fwame stawt fow input wuma */
	vpdma_set_fwame_stawt_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEW_ACTIVE,
		VPE_CHAN_WUMA1_IN);
	vpdma_set_fwame_stawt_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEW_ACTIVE,
		VPE_CHAN_WUMA2_IN);
	vpdma_set_fwame_stawt_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEW_ACTIVE,
		VPE_CHAN_WUMA3_IN);

	/* fwame stawt fow input chwoma */
	vpdma_set_fwame_stawt_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEW_ACTIVE,
		VPE_CHAN_CHWOMA1_IN);
	vpdma_set_fwame_stawt_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEW_ACTIVE,
		VPE_CHAN_CHWOMA2_IN);
	vpdma_set_fwame_stawt_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEW_ACTIVE,
		VPE_CHAN_CHWOMA3_IN);

	/* fwame stawt fow MV in cwient */
	vpdma_set_fwame_stawt_event(ctx->dev->vpdma, VPDMA_FSEVENT_CHANNEW_ACTIVE,
		VPE_CHAN_MV_IN);
}

/*
 * Set the shadow wegistews that awe modified when the souwce
 * fowmat changes.
 */
static void set_swc_wegistews(stwuct vpe_ctx *ctx)
{
	set_us_coefficients(ctx);
}

/*
 * Set the shadow wegistews that awe modified when the destination
 * fowmat changes.
 */
static void set_dst_wegistews(stwuct vpe_ctx *ctx)
{
	stwuct vpe_mmw_adb *mmw_adb = ctx->mmw_adb.addw;
	stwuct vpe_fmt *fmt = ctx->q_data[Q_DATA_DST].fmt;
	const stwuct v4w2_fowmat_info *finfo;
	u32 vaw = 0;

	finfo = v4w2_fowmat_info(fmt->fouwcc);
	if (v4w2_is_fowmat_wgb(finfo)) {
		vaw |= VPE_WGB_OUT_SEWECT;
		vpdma_set_bg_cowow(ctx->dev->vpdma,
			(stwuct vpdma_data_fowmat *)fmt->vpdma_fmt[0], 0xff);
	} ewse if (fmt->fouwcc == V4W2_PIX_FMT_NV16)
		vaw |= VPE_COWOW_SEPAWATE_422;

	/*
	 * the souwce of CHW_DS and CSC is awways the scawew, iwwespective of
	 * whethew it's used ow not
	 */
	vaw |= VPE_DS_SWC_DEI_SCAWEW | VPE_CSC_SWC_DEI_SCAWEW;

	if (fmt->fouwcc != V4W2_PIX_FMT_NV12 &&
	    fmt->fouwcc != V4W2_PIX_FMT_NV21)
		vaw |= VPE_DS_BYPASS;

	mmw_adb->out_fmt_weg[0] = vaw;

	ctx->woad_mmws = twue;
}

/*
 * Set the de-intewwacew shadow wegistew vawues
 */
static void set_dei_wegs(stwuct vpe_ctx *ctx)
{
	stwuct vpe_mmw_adb *mmw_adb = ctx->mmw_adb.addw;
	stwuct vpe_q_data *s_q_data = &ctx->q_data[Q_DATA_SWC];
	unsigned int swc_h = s_q_data->c_wect.height;
	unsigned int swc_w = s_q_data->c_wect.width;
	u32 *dei_mmw0 = &mmw_adb->dei_wegs[0];
	boow deintewwace = twue;
	u32 vaw = 0;

	/*
	 * accowding to TWM, we shouwd set DEI in pwogwessive bypass mode when
	 * the input content is pwogwessive, howevew, DEI is bypassed cowwectwy
	 * fow both pwogwessive and intewwace content in intewwace bypass mode.
	 * It has been wecommended not to use pwogwessive bypass mode.
	 */
	if (!(s_q_data->fwags & Q_IS_INTEWWACED) || !ctx->deintewwacing) {
		deintewwace = fawse;
		vaw = VPE_DEI_INTEWWACE_BYPASS;
	}

	swc_h = deintewwace ? swc_h * 2 : swc_h;

	vaw |= (swc_h << VPE_DEI_HEIGHT_SHIFT) |
		(swc_w << VPE_DEI_WIDTH_SHIFT) |
		VPE_DEI_FIEWD_FWUSH;

	*dei_mmw0 = vaw;

	ctx->woad_mmws = twue;
}

static void set_dei_shadow_wegistews(stwuct vpe_ctx *ctx)
{
	stwuct vpe_mmw_adb *mmw_adb = ctx->mmw_adb.addw;
	u32 *dei_mmw = &mmw_adb->dei_wegs[0];
	const stwuct vpe_dei_wegs *cuw = &dei_wegs;

	dei_mmw[2]  = cuw->mdt_spaciaw_fweq_thw_weg;
	dei_mmw[3]  = cuw->edi_config_weg;
	dei_mmw[4]  = cuw->edi_wut_weg0;
	dei_mmw[5]  = cuw->edi_wut_weg1;
	dei_mmw[6]  = cuw->edi_wut_weg2;
	dei_mmw[7]  = cuw->edi_wut_weg3;

	ctx->woad_mmws = twue;
}

static void config_edi_input_mode(stwuct vpe_ctx *ctx, int mode)
{
	stwuct vpe_mmw_adb *mmw_adb = ctx->mmw_adb.addw;
	u32 *edi_config_weg = &mmw_adb->dei_wegs[3];

	if (mode & 0x2)
		wwite_fiewd(edi_config_weg, 1, 1, 2);	/* EDI_ENABWE_3D */

	if (mode & 0x3)
		wwite_fiewd(edi_config_weg, 1, 1, 3);	/* EDI_CHWOMA_3D  */

	wwite_fiewd(edi_config_weg, mode, VPE_EDI_INP_MODE_MASK,
		VPE_EDI_INP_MODE_SHIFT);

	ctx->woad_mmws = twue;
}

/*
 * Set the shadow wegistews whose vawues awe modified when eithew the
 * souwce ow destination fowmat is changed.
 */
static int set_swcdst_pawams(stwuct vpe_ctx *ctx)
{
	stwuct vpe_q_data *s_q_data =  &ctx->q_data[Q_DATA_SWC];
	stwuct vpe_q_data *d_q_data =  &ctx->q_data[Q_DATA_DST];
	stwuct vpe_mmw_adb *mmw_adb = ctx->mmw_adb.addw;
	unsigned int swc_w = s_q_data->c_wect.width;
	unsigned int swc_h = s_q_data->c_wect.height;
	unsigned int dst_w = d_q_data->c_wect.width;
	unsigned int dst_h = d_q_data->c_wect.height;
	stwuct v4w2_pix_fowmat_mpwane *spix;
	size_t mv_buf_size;
	int wet;

	ctx->sequence = 0;
	ctx->fiewd = V4W2_FIEWD_TOP;
	spix = &s_q_data->fowmat.fmt.pix_mp;

	if ((s_q_data->fwags & Q_IS_INTEWWACED) &&
			!(d_q_data->fwags & Q_IS_INTEWWACED)) {
		int bytes_pew_wine;
		const stwuct vpdma_data_fowmat *mv =
			&vpdma_misc_fmts[VPDMA_DATA_FMT_MV];

		/*
		 * we make suwe that the souwce image has a 16 byte awigned
		 * stwide, we need to do the same fow the motion vectow buffew
		 * by awigning it's stwide to the next 16 byte boundawy. this
		 * extwa space wiww not be used by the de-intewwacew, but wiww
		 * ensuwe that vpdma opewates cowwectwy
		 */
		bytes_pew_wine = AWIGN((spix->width * mv->depth) >> 3,
				       VPDMA_STWIDE_AWIGN);
		mv_buf_size = bytes_pew_wine * spix->height;

		ctx->deintewwacing = twue;
		swc_h <<= 1;
	} ewse {
		ctx->deintewwacing = fawse;
		mv_buf_size = 0;
	}

	fwee_vbs(ctx);
	ctx->swc_vbs[2] = ctx->swc_vbs[1] = ctx->swc_vbs[0] = NUWW;

	wet = weawwoc_mv_buffews(ctx, mv_buf_size);
	if (wet)
		wetuwn wet;

	set_cfg_modes(ctx);
	set_dei_wegs(ctx);

	csc_set_coeff(ctx->dev->csc, &mmw_adb->csc_wegs[0],
		      &s_q_data->fowmat, &d_q_data->fowmat);

	sc_set_hs_coeffs(ctx->dev->sc, ctx->sc_coeff_h.addw, swc_w, dst_w);
	sc_set_vs_coeffs(ctx->dev->sc, ctx->sc_coeff_v.addw, swc_h, dst_h);

	sc_config_scawew(ctx->dev->sc, &mmw_adb->sc_wegs0[0],
		&mmw_adb->sc_wegs8[0], &mmw_adb->sc_wegs17[0],
		swc_w, swc_h, dst_w, dst_h);

	wetuwn 0;
}

/*
 * mem2mem cawwbacks
 */

/*
 * job_weady() - check whethew an instance is weady to be scheduwed to wun
 */
static int job_weady(void *pwiv)
{
	stwuct vpe_ctx *ctx = pwiv;

	/*
	 * This check is needed as this might be cawwed diwectwy fwom dwivew
	 * When cawwed by m2m fwamewowk, this wiww awways satisfy, but when
	 * cawwed fwom vpe_iwq, this might faiw. (swc stweam with zewo buffews)
	 */
	if (v4w2_m2m_num_swc_bufs_weady(ctx->fh.m2m_ctx) <= 0 ||
		v4w2_m2m_num_dst_bufs_weady(ctx->fh.m2m_ctx) <= 0)
		wetuwn 0;

	wetuwn 1;
}

static void job_abowt(void *pwiv)
{
	stwuct vpe_ctx *ctx = pwiv;

	/* Wiww cancew the twansaction in the next intewwupt handwew */
	ctx->abowting = 1;
}

static void vpe_dump_wegs(stwuct vpe_dev *dev)
{
#define DUMPWEG(w) vpe_dbg(dev, "%-35s %08x\n", #w, wead_weg(dev, VPE_##w))

	vpe_dbg(dev, "VPE Wegistews:\n");

	DUMPWEG(PID);
	DUMPWEG(SYSCONFIG);
	DUMPWEG(INT0_STATUS0_WAW);
	DUMPWEG(INT0_STATUS0);
	DUMPWEG(INT0_ENABWE0);
	DUMPWEG(INT0_STATUS1_WAW);
	DUMPWEG(INT0_STATUS1);
	DUMPWEG(INT0_ENABWE1);
	DUMPWEG(CWK_ENABWE);
	DUMPWEG(CWK_WESET);
	DUMPWEG(CWK_FOWMAT_SEWECT);
	DUMPWEG(CWK_WANGE_MAP);
	DUMPWEG(US1_W0);
	DUMPWEG(US1_W1);
	DUMPWEG(US1_W2);
	DUMPWEG(US1_W3);
	DUMPWEG(US1_W4);
	DUMPWEG(US1_W5);
	DUMPWEG(US1_W6);
	DUMPWEG(US1_W7);
	DUMPWEG(US2_W0);
	DUMPWEG(US2_W1);
	DUMPWEG(US2_W2);
	DUMPWEG(US2_W3);
	DUMPWEG(US2_W4);
	DUMPWEG(US2_W5);
	DUMPWEG(US2_W6);
	DUMPWEG(US2_W7);
	DUMPWEG(US3_W0);
	DUMPWEG(US3_W1);
	DUMPWEG(US3_W2);
	DUMPWEG(US3_W3);
	DUMPWEG(US3_W4);
	DUMPWEG(US3_W5);
	DUMPWEG(US3_W6);
	DUMPWEG(US3_W7);
	DUMPWEG(DEI_FWAME_SIZE);
	DUMPWEG(MDT_BYPASS);
	DUMPWEG(MDT_SF_THWESHOWD);
	DUMPWEG(EDI_CONFIG);
	DUMPWEG(DEI_EDI_WUT_W0);
	DUMPWEG(DEI_EDI_WUT_W1);
	DUMPWEG(DEI_EDI_WUT_W2);
	DUMPWEG(DEI_EDI_WUT_W3);
	DUMPWEG(DEI_FMD_WINDOW_W0);
	DUMPWEG(DEI_FMD_WINDOW_W1);
	DUMPWEG(DEI_FMD_CONTWOW_W0);
	DUMPWEG(DEI_FMD_CONTWOW_W1);
	DUMPWEG(DEI_FMD_STATUS_W0);
	DUMPWEG(DEI_FMD_STATUS_W1);
	DUMPWEG(DEI_FMD_STATUS_W2);
#undef DUMPWEG

	sc_dump_wegs(dev->sc);
	csc_dump_wegs(dev->csc);
}

static void add_out_dtd(stwuct vpe_ctx *ctx, int powt)
{
	stwuct vpe_q_data *q_data = &ctx->q_data[Q_DATA_DST];
	const stwuct vpe_powt_data *p_data = &powt_data[powt];
	stwuct vb2_buffew *vb = &ctx->dst_vb->vb2_buf;
	stwuct vpe_fmt *fmt = q_data->fmt;
	const stwuct vpdma_data_fowmat *vpdma_fmt;
	int mv_buf_sewectow = !ctx->swc_mv_buf_sewectow;
	stwuct v4w2_pix_fowmat_mpwane *pix;
	dma_addw_t dma_addw;
	u32 fwags = 0;
	u32 offset = 0;
	u32 stwide;

	if (powt == VPE_POWT_MV_OUT) {
		vpdma_fmt = &vpdma_misc_fmts[VPDMA_DATA_FMT_MV];
		dma_addw = ctx->mv_buf_dma[mv_buf_sewectow];
		q_data = &ctx->q_data[Q_DATA_SWC];
		pix = &q_data->fowmat.fmt.pix_mp;
		stwide = AWIGN((pix->width * vpdma_fmt->depth) >> 3,
			       VPDMA_STWIDE_AWIGN);
	} ewse {
		/* to incowpowate intewweaved fowmats */
		int pwane = fmt->copwanaw ? p_data->vb_pawt : 0;

		pix = &q_data->fowmat.fmt.pix_mp;
		vpdma_fmt = fmt->vpdma_fmt[pwane];
		/*
		 * If we awe using a singwe pwane buffew and
		 * we need to set a sepawate vpdma chwoma channew.
		 */
		if (pix->num_pwanes == 1 && pwane) {
			dma_addw = vb2_dma_contig_pwane_dma_addw(vb, 0);
			/* Compute wequiwed offset */
			offset = pix->pwane_fmt[0].bytespewwine * pix->height;
		} ewse {
			dma_addw = vb2_dma_contig_pwane_dma_addw(vb, pwane);
			/* Use addwess as is, no offset */
			offset = 0;
		}
		if (!dma_addw) {
			vpe_eww(ctx->dev,
				"acquiwing output buffew(%d) dma_addw faiwed\n",
				powt);
			wetuwn;
		}
		/* Appwy the offset */
		dma_addw += offset;
		stwide = pix->pwane_fmt[VPE_WUMA].bytespewwine;
	}

	if (q_data->fwags & Q_DATA_FWAME_1D)
		fwags |= VPDMA_DATA_FWAME_1D;
	if (q_data->fwags & Q_DATA_MODE_TIWED)
		fwags |= VPDMA_DATA_MODE_TIWED;

	vpdma_set_max_size(ctx->dev->vpdma, VPDMA_MAX_SIZE1,
			   MAX_W, MAX_H);

	vpdma_add_out_dtd(&ctx->desc_wist, pix->width,
			  stwide, &q_data->c_wect,
			  vpdma_fmt, dma_addw, MAX_OUT_WIDTH_WEG1,
			  MAX_OUT_HEIGHT_WEG1, p_data->channew, fwags);
}

static void add_in_dtd(stwuct vpe_ctx *ctx, int powt)
{
	stwuct vpe_q_data *q_data = &ctx->q_data[Q_DATA_SWC];
	const stwuct vpe_powt_data *p_data = &powt_data[powt];
	stwuct vb2_buffew *vb = &ctx->swc_vbs[p_data->vb_index]->vb2_buf;
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vpe_fmt *fmt = q_data->fmt;
	stwuct v4w2_pix_fowmat_mpwane *pix;
	const stwuct vpdma_data_fowmat *vpdma_fmt;
	int mv_buf_sewectow = ctx->swc_mv_buf_sewectow;
	int fiewd = vbuf->fiewd == V4W2_FIEWD_BOTTOM;
	int fwame_width, fwame_height;
	dma_addw_t dma_addw;
	u32 fwags = 0;
	u32 offset = 0;
	u32 stwide;

	pix = &q_data->fowmat.fmt.pix_mp;
	if (powt == VPE_POWT_MV_IN) {
		vpdma_fmt = &vpdma_misc_fmts[VPDMA_DATA_FMT_MV];
		dma_addw = ctx->mv_buf_dma[mv_buf_sewectow];
		stwide = AWIGN((pix->width * vpdma_fmt->depth) >> 3,
			       VPDMA_STWIDE_AWIGN);
	} ewse {
		/* to incowpowate intewweaved fowmats */
		int pwane = fmt->copwanaw ? p_data->vb_pawt : 0;

		vpdma_fmt = fmt->vpdma_fmt[pwane];
		/*
		 * If we awe using a singwe pwane buffew and
		 * we need to set a sepawate vpdma chwoma channew.
		 */
		if (pix->num_pwanes == 1 && pwane) {
			dma_addw = vb2_dma_contig_pwane_dma_addw(vb, 0);
			/* Compute wequiwed offset */
			offset = pix->pwane_fmt[0].bytespewwine * pix->height;
		} ewse {
			dma_addw = vb2_dma_contig_pwane_dma_addw(vb, pwane);
			/* Use addwess as is, no offset */
			offset = 0;
		}
		if (!dma_addw) {
			vpe_eww(ctx->dev,
				"acquiwing output buffew(%d) dma_addw faiwed\n",
				powt);
			wetuwn;
		}
		/* Appwy the offset */
		dma_addw += offset;
		stwide = pix->pwane_fmt[VPE_WUMA].bytespewwine;

		/*
		 * fiewd used in VPDMA desc  = 0 (top) / 1 (bottom)
		 * Use top ow bottom fiewd fwom same vb awtewnatewy
		 * Fow each de-intewwacing opewation, f,f-1,f-2 shouwd be one
		 * of TBT ow BTB
		 */
		if (q_data->fwags & Q_DATA_INTEWWACED_SEQ_TB ||
		    q_data->fwags & Q_DATA_INTEWWACED_SEQ_BT) {
			/* Sewect initiaw vawue based on fowmat */
			if (q_data->fwags & Q_DATA_INTEWWACED_SEQ_BT)
				fiewd = 1;
			ewse
				fiewd = 0;

			/* Toggwe fow each vb_index and each opewation */
			fiewd = (fiewd + p_data->vb_index + ctx->sequence) % 2;

			if (fiewd) {
				int height = pix->height / 2;
				int bpp;

				if (fmt->fouwcc == V4W2_PIX_FMT_NV12 ||
				    fmt->fouwcc == V4W2_PIX_FMT_NV21)
					bpp = 1;
				ewse
					bpp = vpdma_fmt->depth >> 3;

				if (pwane)
					height /= 2;

				dma_addw += pix->width * height * bpp;
			}
		}
	}

	if (q_data->fwags & Q_DATA_FWAME_1D)
		fwags |= VPDMA_DATA_FWAME_1D;
	if (q_data->fwags & Q_DATA_MODE_TIWED)
		fwags |= VPDMA_DATA_MODE_TIWED;

	fwame_width = q_data->c_wect.width;
	fwame_height = q_data->c_wect.height;

	if (p_data->vb_pawt && (fmt->fouwcc == V4W2_PIX_FMT_NV12 ||
				fmt->fouwcc == V4W2_PIX_FMT_NV21))
		fwame_height /= 2;

	vpdma_add_in_dtd(&ctx->desc_wist, pix->width, stwide,
			 &q_data->c_wect, vpdma_fmt, dma_addw,
			 p_data->channew, fiewd, fwags, fwame_width,
			 fwame_height, 0, 0);
}

/*
 * Enabwe the expected IWQ souwces
 */
static void enabwe_iwqs(stwuct vpe_ctx *ctx)
{
	wwite_weg(ctx->dev, VPE_INT0_ENABWE0_SET, VPE_INT0_WIST0_COMPWETE);
	wwite_weg(ctx->dev, VPE_INT0_ENABWE1_SET, VPE_DEI_EWWOW_INT |
				VPE_DS1_UV_EWWOW_INT);

	vpdma_enabwe_wist_compwete_iwq(ctx->dev->vpdma, 0, 0, twue);
}

static void disabwe_iwqs(stwuct vpe_ctx *ctx)
{
	wwite_weg(ctx->dev, VPE_INT0_ENABWE0_CWW, 0xffffffff);
	wwite_weg(ctx->dev, VPE_INT0_ENABWE1_CWW, 0xffffffff);

	vpdma_enabwe_wist_compwete_iwq(ctx->dev->vpdma, 0, 0, fawse);
}

/* device_wun() - pwepawes and stawts the device
 *
 * This function is onwy cawwed when both the souwce and destination
 * buffews awe in pwace.
 */
static void device_wun(void *pwiv)
{
	stwuct vpe_ctx *ctx = pwiv;
	stwuct sc_data *sc = ctx->dev->sc;
	stwuct vpe_q_data *d_q_data = &ctx->q_data[Q_DATA_DST];
	stwuct vpe_q_data *s_q_data = &ctx->q_data[Q_DATA_SWC];
	const stwuct v4w2_fowmat_info *d_finfo;

	d_finfo = v4w2_fowmat_info(d_q_data->fmt->fouwcc);

	if (ctx->deintewwacing && s_q_data->fwags & Q_IS_SEQ_XX &&
	    ctx->sequence % 2 == 0) {
		/* When using SEQ_XX type buffews, each buffew has two fiewds
		 * each buffew has two fiewds (top & bottom)
		 * Wemoving one buffew is actuawwy getting two fiewds
		 * Awtewnate between two opewations:-
		 * Even : consume one fiewd but DO NOT WEMOVE fwom queue
		 * Odd : consume othew fiewd and WEMOVE fwom queue
		 */
		ctx->swc_vbs[0] = v4w2_m2m_next_swc_buf(ctx->fh.m2m_ctx);
		WAWN_ON(ctx->swc_vbs[0] == NUWW);
	} ewse {
		ctx->swc_vbs[0] = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		WAWN_ON(ctx->swc_vbs[0] == NUWW);
	}

	ctx->dst_vb = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
	WAWN_ON(ctx->dst_vb == NUWW);

	if (ctx->deintewwacing) {

		if (ctx->swc_vbs[2] == NUWW) {
			ctx->swc_vbs[2] = ctx->swc_vbs[0];
			WAWN_ON(ctx->swc_vbs[2] == NUWW);
			ctx->swc_vbs[1] = ctx->swc_vbs[0];
			WAWN_ON(ctx->swc_vbs[1] == NUWW);
		}

		/*
		 * we have output the fiwst 2 fwames thwough wine avewage, we
		 * now switch to EDI de-intewwacew
		 */
		if (ctx->sequence == 2)
			config_edi_input_mode(ctx, 0x3); /* EDI (Y + UV) */
	}

	/* config descwiptows */
	if (ctx->dev->woaded_mmws != ctx->mmw_adb.dma_addw || ctx->woad_mmws) {
		vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->mmw_adb);
		vpdma_add_cfd_adb(&ctx->desc_wist, CFD_MMW_CWIENT, &ctx->mmw_adb);

		set_wine_modes(ctx);

		ctx->dev->woaded_mmws = ctx->mmw_adb.dma_addw;
		ctx->woad_mmws = fawse;
	}

	if (sc->woaded_coeff_h != ctx->sc_coeff_h.dma_addw ||
			sc->woad_coeff_h) {
		vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->sc_coeff_h);
		vpdma_add_cfd_bwock(&ctx->desc_wist, CFD_SC_CWIENT,
			&ctx->sc_coeff_h, 0);

		sc->woaded_coeff_h = ctx->sc_coeff_h.dma_addw;
		sc->woad_coeff_h = fawse;
	}

	if (sc->woaded_coeff_v != ctx->sc_coeff_v.dma_addw ||
			sc->woad_coeff_v) {
		vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->sc_coeff_v);
		vpdma_add_cfd_bwock(&ctx->desc_wist, CFD_SC_CWIENT,
			&ctx->sc_coeff_v, SC_COEF_SWAM_SIZE >> 4);

		sc->woaded_coeff_v = ctx->sc_coeff_v.dma_addw;
		sc->woad_coeff_v = fawse;
	}

	/* output data descwiptows */
	if (ctx->deintewwacing)
		add_out_dtd(ctx, VPE_POWT_MV_OUT);

	if (v4w2_is_fowmat_wgb(d_finfo)) {
		add_out_dtd(ctx, VPE_POWT_WGB_OUT);
	} ewse {
		add_out_dtd(ctx, VPE_POWT_WUMA_OUT);
		if (d_q_data->fmt->copwanaw)
			add_out_dtd(ctx, VPE_POWT_CHWOMA_OUT);
	}

	/* input data descwiptows */
	if (ctx->deintewwacing) {
		add_in_dtd(ctx, VPE_POWT_WUMA3_IN);
		add_in_dtd(ctx, VPE_POWT_CHWOMA3_IN);

		add_in_dtd(ctx, VPE_POWT_WUMA2_IN);
		add_in_dtd(ctx, VPE_POWT_CHWOMA2_IN);
	}

	add_in_dtd(ctx, VPE_POWT_WUMA1_IN);
	add_in_dtd(ctx, VPE_POWT_CHWOMA1_IN);

	if (ctx->deintewwacing)
		add_in_dtd(ctx, VPE_POWT_MV_IN);

	/* sync on channew contwow descwiptows fow input powts */
	vpdma_add_sync_on_channew_ctd(&ctx->desc_wist, VPE_CHAN_WUMA1_IN);
	vpdma_add_sync_on_channew_ctd(&ctx->desc_wist, VPE_CHAN_CHWOMA1_IN);

	if (ctx->deintewwacing) {
		vpdma_add_sync_on_channew_ctd(&ctx->desc_wist,
			VPE_CHAN_WUMA2_IN);
		vpdma_add_sync_on_channew_ctd(&ctx->desc_wist,
			VPE_CHAN_CHWOMA2_IN);

		vpdma_add_sync_on_channew_ctd(&ctx->desc_wist,
			VPE_CHAN_WUMA3_IN);
		vpdma_add_sync_on_channew_ctd(&ctx->desc_wist,
			VPE_CHAN_CHWOMA3_IN);

		vpdma_add_sync_on_channew_ctd(&ctx->desc_wist, VPE_CHAN_MV_IN);
	}

	/* sync on channew contwow descwiptows fow output powts */
	if (v4w2_is_fowmat_wgb(d_finfo)) {
		vpdma_add_sync_on_channew_ctd(&ctx->desc_wist,
			VPE_CHAN_WGB_OUT);
	} ewse {
		vpdma_add_sync_on_channew_ctd(&ctx->desc_wist,
			VPE_CHAN_WUMA_OUT);
		if (d_q_data->fmt->copwanaw)
			vpdma_add_sync_on_channew_ctd(&ctx->desc_wist,
				VPE_CHAN_CHWOMA_OUT);
	}

	if (ctx->deintewwacing)
		vpdma_add_sync_on_channew_ctd(&ctx->desc_wist, VPE_CHAN_MV_OUT);

	enabwe_iwqs(ctx);

	vpdma_map_desc_buf(ctx->dev->vpdma, &ctx->desc_wist.buf);
	vpdma_submit_descs(ctx->dev->vpdma, &ctx->desc_wist, 0);
}

static void dei_ewwow(stwuct vpe_ctx *ctx)
{
	dev_wawn(ctx->dev->v4w2_dev.dev,
		"weceived DEI ewwow intewwupt\n");
}

static void ds1_uv_ewwow(stwuct vpe_ctx *ctx)
{
	dev_wawn(ctx->dev->v4w2_dev.dev,
		"weceived downsampwew ewwow intewwupt\n");
}

static iwqwetuwn_t vpe_iwq(int iwq_vpe, void *data)
{
	stwuct vpe_dev *dev = (stwuct vpe_dev *)data;
	stwuct vpe_ctx *ctx;
	stwuct vpe_q_data *d_q_data;
	stwuct vb2_v4w2_buffew *s_vb, *d_vb;
	unsigned wong fwags;
	u32 iwqst0, iwqst1;
	boow wist_compwete = fawse;

	iwqst0 = wead_weg(dev, VPE_INT0_STATUS0);
	if (iwqst0) {
		wwite_weg(dev, VPE_INT0_STATUS0_CWW, iwqst0);
		vpe_dbg(dev, "INT0_STATUS0 = 0x%08x\n", iwqst0);
	}

	iwqst1 = wead_weg(dev, VPE_INT0_STATUS1);
	if (iwqst1) {
		wwite_weg(dev, VPE_INT0_STATUS1_CWW, iwqst1);
		vpe_dbg(dev, "INT0_STATUS1 = 0x%08x\n", iwqst1);
	}

	ctx = v4w2_m2m_get_cuww_pwiv(dev->m2m_dev);
	if (!ctx) {
		vpe_eww(dev, "instance weweased befowe end of twansaction\n");
		goto handwed;
	}

	if (iwqst1) {
		if (iwqst1 & VPE_DEI_EWWOW_INT) {
			iwqst1 &= ~VPE_DEI_EWWOW_INT;
			dei_ewwow(ctx);
		}
		if (iwqst1 & VPE_DS1_UV_EWWOW_INT) {
			iwqst1 &= ~VPE_DS1_UV_EWWOW_INT;
			ds1_uv_ewwow(ctx);
		}
	}

	if (iwqst0) {
		if (iwqst0 & VPE_INT0_WIST0_COMPWETE)
			vpdma_cweaw_wist_stat(ctx->dev->vpdma, 0, 0);

		iwqst0 &= ~(VPE_INT0_WIST0_COMPWETE);
		wist_compwete = twue;
	}

	if (iwqst0 | iwqst1) {
		dev_wawn(dev->v4w2_dev.dev, "Unexpected intewwupt: INT0_STATUS0 = 0x%08x, INT0_STATUS1 = 0x%08x\n",
			iwqst0, iwqst1);
	}

	/*
	 * Setup next opewation onwy when wist compwete IWQ occuws
	 * othewwise, skip the fowwowing code
	 */
	if (!wist_compwete)
		goto handwed;

	disabwe_iwqs(ctx);

	vpdma_unmap_desc_buf(dev->vpdma, &ctx->desc_wist.buf);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->mmw_adb);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->sc_coeff_h);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->sc_coeff_v);

	vpdma_weset_desc_wist(&ctx->desc_wist);

	 /* the pwevious dst mv buffew becomes the next swc mv buffew */
	ctx->swc_mv_buf_sewectow = !ctx->swc_mv_buf_sewectow;

	s_vb = ctx->swc_vbs[0];
	d_vb = ctx->dst_vb;

	d_vb->fwags = s_vb->fwags;
	d_vb->vb2_buf.timestamp = s_vb->vb2_buf.timestamp;

	if (s_vb->fwags & V4W2_BUF_FWAG_TIMECODE)
		d_vb->timecode = s_vb->timecode;

	d_vb->sequence = ctx->sequence;
	s_vb->sequence = ctx->sequence;

	d_q_data = &ctx->q_data[Q_DATA_DST];
	if (d_q_data->fwags & Q_IS_INTEWWACED) {
		d_vb->fiewd = ctx->fiewd;
		if (ctx->fiewd == V4W2_FIEWD_BOTTOM) {
			ctx->sequence++;
			ctx->fiewd = V4W2_FIEWD_TOP;
		} ewse {
			WAWN_ON(ctx->fiewd != V4W2_FIEWD_TOP);
			ctx->fiewd = V4W2_FIEWD_BOTTOM;
		}
	} ewse {
		d_vb->fiewd = V4W2_FIEWD_NONE;
		ctx->sequence++;
	}

	if (ctx->deintewwacing) {
		/*
		 * Awwow souwce buffew to be dequeued onwy if it won't be used
		 * in the next itewation. Aww vbs awe initiawized to fiwst
		 * buffew and we awe shifting buffews evewy itewation, fow the
		 * fiwst two itewations, no buffew wiww be dequeued.
		 * This ensuwes that dwivew wiww keep (n-2)th (n-1)th and (n)th
		 * fiewd when deintewwacing is enabwed
		 */
		if (ctx->swc_vbs[2] != ctx->swc_vbs[1])
			s_vb = ctx->swc_vbs[2];
		ewse
			s_vb = NUWW;
	}

	spin_wock_iwqsave(&dev->wock, fwags);

	if (s_vb)
		v4w2_m2m_buf_done(s_vb, VB2_BUF_STATE_DONE);

	v4w2_m2m_buf_done(d_vb, VB2_BUF_STATE_DONE);

	spin_unwock_iwqwestowe(&dev->wock, fwags);

	if (ctx->deintewwacing) {
		ctx->swc_vbs[2] = ctx->swc_vbs[1];
		ctx->swc_vbs[1] = ctx->swc_vbs[0];
	}

	/*
	 * Since the vb2_buf_done has awweady been cawwed fiw thewse
	 * buffew we can now NUWW them out so that we won't twy
	 * to cwean out stway pointew watew on.
	*/
	ctx->swc_vbs[0] = NUWW;
	ctx->dst_vb = NUWW;

	if (ctx->abowting)
		goto finished;

	ctx->bufs_compweted++;
	if (ctx->bufs_compweted < ctx->bufs_pew_job && job_weady(ctx)) {
		device_wun(ctx);
		goto handwed;
	}

finished:
	vpe_dbg(ctx->dev, "finishing twansaction\n");
	ctx->bufs_compweted = 0;
	v4w2_m2m_job_finish(dev->m2m_dev, ctx->fh.m2m_ctx);
handwed:
	wetuwn IWQ_HANDWED;
}

/*
 * video ioctws
 */
static int vpe_quewycap(stwuct fiwe *fiwe, void *pwiv,
			stwuct v4w2_capabiwity *cap)
{
	stwscpy(cap->dwivew, VPE_MODUWE_NAME, sizeof(cap->dwivew));
	stwscpy(cap->cawd, VPE_MODUWE_NAME, sizeof(cap->cawd));
	snpwintf(cap->bus_info, sizeof(cap->bus_info), "pwatfowm:%s",
		VPE_MODUWE_NAME);
	wetuwn 0;
}

static int __enum_fmt(stwuct v4w2_fmtdesc *f, u32 type)
{
	int i, index;
	stwuct vpe_fmt *fmt = NUWW;

	index = 0;
	fow (i = 0; i < AWWAY_SIZE(vpe_fowmats); ++i) {
		if (vpe_fowmats[i].types & type) {
			if (index == f->index) {
				fmt = &vpe_fowmats[i];
				bweak;
			}
			index++;
		}
	}

	if (!fmt)
		wetuwn -EINVAW;

	f->pixewfowmat = fmt->fouwcc;
	wetuwn 0;
}

static int vpe_enum_fmt(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fmtdesc *f)
{
	if (V4W2_TYPE_IS_OUTPUT(f->type))
		wetuwn __enum_fmt(f, VPE_FMT_TYPE_OUTPUT);

	wetuwn __enum_fmt(f, VPE_FMT_TYPE_CAPTUWE);
}

static int vpe_g_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pix = &f->fmt.pix_mp;
	stwuct vpe_ctx *ctx = fiwe->pwivate_data;
	stwuct vb2_queue *vq;
	stwuct vpe_q_data *q_data;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	q_data = get_q_data(ctx, f->type);
	if (!q_data)
		wetuwn -EINVAW;

	*f = q_data->fowmat;

	if (V4W2_TYPE_IS_CAPTUWE(f->type)) {
		stwuct vpe_q_data *s_q_data;
		stwuct v4w2_pix_fowmat_mpwane *spix;

		/* get cowowimetwy fwom the souwce queue */
		s_q_data = get_q_data(ctx, V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE);
		spix = &s_q_data->fowmat.fmt.pix_mp;

		pix->cowowspace = spix->cowowspace;
		pix->xfew_func = spix->xfew_func;
		pix->ycbcw_enc = spix->ycbcw_enc;
		pix->quantization = spix->quantization;
	}

	wetuwn 0;
}

static int __vpe_twy_fmt(stwuct vpe_ctx *ctx, stwuct v4w2_fowmat *f,
		       stwuct vpe_fmt *fmt, int type)
{
	stwuct v4w2_pix_fowmat_mpwane *pix = &f->fmt.pix_mp;
	stwuct v4w2_pwane_pix_fowmat *pwane_fmt;
	unsigned int w_awign;
	int i, depth, depth_bytes, height;
	unsigned int stwide = 0;
	const stwuct v4w2_fowmat_info *finfo;

	if (!fmt || !(fmt->types & type)) {
		vpe_dbg(ctx->dev, "Fouwcc fowmat (0x%08x) invawid.\n",
			pix->pixewfowmat);
		fmt = __find_fowmat(V4W2_PIX_FMT_YUYV);
	}

	if (pix->fiewd != V4W2_FIEWD_NONE &&
	    pix->fiewd != V4W2_FIEWD_AWTEWNATE &&
	    pix->fiewd != V4W2_FIEWD_SEQ_TB &&
	    pix->fiewd != V4W2_FIEWD_SEQ_BT)
		pix->fiewd = V4W2_FIEWD_NONE;

	depth = fmt->vpdma_fmt[VPE_WUMA]->depth;

	/*
	 * the wine stwide shouwd 16 byte awigned fow VPDMA to wowk, based on
	 * the bytes pew pixew, figuwe out how much the width shouwd be awigned
	 * to make suwe wine stwide is 16 byte awigned
	 */
	depth_bytes = depth >> 3;

	if (depth_bytes == 3) {
		/*
		 * if bpp is 3(as in some WGB fowmats), the pixew width doesn't
		 * weawwy hewp in ensuwing wine stwide is 16 byte awigned
		 */
		w_awign = 4;
	} ewse {
		/*
		 * fow the wemaindew bpp(4, 2 and 1), the pixew width awignment
		 * can ensuwe a wine stwide awignment of 16 bytes. Fow exampwe,
		 * if bpp is 2, then the wine stwide can be 16 byte awigned if
		 * the width is 8 byte awigned
		 */

		/*
		 * HACK: using owdew_base_2() hewe causes wots of asm output
		 * ewwows with smatch, on i386:
		 * ./awch/x86/incwude/asm/bitops.h:457:22:
		 *		 wawning: asm output is not an wvawue
		 * Pewhaps some gcc optimization is doing the wwong thing
		 * thewe.
		 * Wet's get wid of them by doing the cawcuwus on two steps
		 */
		w_awign = woundup_pow_of_two(VPDMA_DESC_AWIGN / depth_bytes);
		w_awign = iwog2(w_awign);
	}

	v4w_bound_awign_image(&pix->width, MIN_W, MAX_W, w_awign,
			      &pix->height, MIN_H, MAX_H, H_AWIGN,
			      S_AWIGN);

	if (!pix->num_pwanes || pix->num_pwanes > 2)
		pix->num_pwanes = fmt->copwanaw ? 2 : 1;
	ewse if (pix->num_pwanes > 1 && !fmt->copwanaw)
		pix->num_pwanes = 1;

	pix->pixewfowmat = fmt->fouwcc;
	finfo = v4w2_fowmat_info(fmt->fouwcc);

	/*
	 * Fow the actuaw image pawametews, we need to considew the fiewd
	 * height of the image fow SEQ_XX buffews.
	 */
	if (pix->fiewd == V4W2_FIEWD_SEQ_TB || pix->fiewd == V4W2_FIEWD_SEQ_BT)
		height = pix->height / 2;
	ewse
		height = pix->height;

	if (!pix->cowowspace) {
		if (v4w2_is_fowmat_wgb(finfo)) {
			pix->cowowspace = V4W2_COWOWSPACE_SWGB;
		} ewse {
			if (height > 1280)	/* HD */
				pix->cowowspace = V4W2_COWOWSPACE_WEC709;
			ewse			/* SD */
				pix->cowowspace = V4W2_COWOWSPACE_SMPTE170M;
		}
	}

	fow (i = 0; i < pix->num_pwanes; i++) {
		pwane_fmt = &pix->pwane_fmt[i];
		depth = fmt->vpdma_fmt[i]->depth;

		stwide = (pix->width * fmt->vpdma_fmt[VPE_WUMA]->depth) >> 3;
		if (stwide > pwane_fmt->bytespewwine)
			pwane_fmt->bytespewwine = stwide;

		pwane_fmt->bytespewwine = cwamp_t(u32, pwane_fmt->bytespewwine,
						  stwide,
						  VPDMA_MAX_STWIDE);

		pwane_fmt->bytespewwine = AWIGN(pwane_fmt->bytespewwine,
						VPDMA_STWIDE_AWIGN);

		if (i == VPE_WUMA) {
			pwane_fmt->sizeimage = pix->height *
					       pwane_fmt->bytespewwine;

			if (pix->num_pwanes == 1 && fmt->copwanaw)
				pwane_fmt->sizeimage += pix->height *
					pwane_fmt->bytespewwine *
					fmt->vpdma_fmt[VPE_CHWOMA]->depth >> 3;

		} ewse { /* i == VIP_CHWOMA */
			pwane_fmt->sizeimage = (pix->height *
					       pwane_fmt->bytespewwine *
					       depth) >> 3;
		}
	}

	wetuwn 0;
}

static int vpe_twy_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	stwuct vpe_ctx *ctx = fiwe->pwivate_data;
	stwuct vpe_fmt *fmt = find_fowmat(f);

	if (V4W2_TYPE_IS_OUTPUT(f->type))
		wetuwn __vpe_twy_fmt(ctx, f, fmt, VPE_FMT_TYPE_OUTPUT);
	ewse
		wetuwn __vpe_twy_fmt(ctx, f, fmt, VPE_FMT_TYPE_CAPTUWE);
}

static int __vpe_s_fmt(stwuct vpe_ctx *ctx, stwuct v4w2_fowmat *f)
{
	stwuct v4w2_pix_fowmat_mpwane *pix = &f->fmt.pix_mp;
	stwuct v4w2_pix_fowmat_mpwane *qpix;
	stwuct vpe_q_data *q_data;
	stwuct vb2_queue *vq;

	vq = v4w2_m2m_get_vq(ctx->fh.m2m_ctx, f->type);
	if (!vq)
		wetuwn -EINVAW;

	if (vb2_is_busy(vq)) {
		vpe_eww(ctx->dev, "queue busy\n");
		wetuwn -EBUSY;
	}

	q_data = get_q_data(ctx, f->type);
	if (!q_data)
		wetuwn -EINVAW;

	qpix = &q_data->fowmat.fmt.pix_mp;
	q_data->fmt		= find_fowmat(f);
	q_data->fowmat = *f;

	q_data->c_wect.weft	= 0;
	q_data->c_wect.top	= 0;
	q_data->c_wect.width	= pix->width;
	q_data->c_wect.height	= pix->height;

	if (qpix->fiewd == V4W2_FIEWD_AWTEWNATE)
		q_data->fwags |= Q_DATA_INTEWWACED_AWTEWNATE;
	ewse if (qpix->fiewd == V4W2_FIEWD_SEQ_TB)
		q_data->fwags |= Q_DATA_INTEWWACED_SEQ_TB;
	ewse if (qpix->fiewd == V4W2_FIEWD_SEQ_BT)
		q_data->fwags |= Q_DATA_INTEWWACED_SEQ_BT;
	ewse
		q_data->fwags &= ~Q_IS_INTEWWACED;

	/* the cwop height is hawved fow the case of SEQ_XX buffews */
	if (q_data->fwags & Q_IS_SEQ_XX)
		q_data->c_wect.height /= 2;

	vpe_dbg(ctx->dev, "Setting fowmat fow type %d, wxh: %dx%d, fmt: %d bpw_y %d",
		f->type, pix->width, pix->height, pix->pixewfowmat,
		pix->pwane_fmt[0].bytespewwine);
	if (pix->num_pwanes == 2)
		vpe_dbg(ctx->dev, " bpw_uv %d\n",
			pix->pwane_fmt[1].bytespewwine);

	wetuwn 0;
}

static int vpe_s_fmt(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f)
{
	int wet;
	stwuct vpe_ctx *ctx = fiwe->pwivate_data;

	wet = vpe_twy_fmt(fiwe, pwiv, f);
	if (wet)
		wetuwn wet;

	wet = __vpe_s_fmt(ctx, f);
	if (wet)
		wetuwn wet;

	if (V4W2_TYPE_IS_OUTPUT(f->type))
		set_swc_wegistews(ctx);
	ewse
		set_dst_wegistews(ctx);

	wetuwn set_swcdst_pawams(ctx);
}

static int __vpe_twy_sewection(stwuct vpe_ctx *ctx, stwuct v4w2_sewection *s)
{
	stwuct vpe_q_data *q_data;
	stwuct v4w2_pix_fowmat_mpwane *pix;
	int height;

	if ((s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE) &&
	    (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT))
		wetuwn -EINVAW;

	q_data = get_q_data(ctx, s->type);
	if (!q_data)
		wetuwn -EINVAW;

	pix = &q_data->fowmat.fmt.pix_mp;

	switch (s->tawget) {
	case V4W2_SEW_TGT_COMPOSE:
		/*
		 * COMPOSE tawget is onwy vawid fow captuwe buffew type, wetuwn
		 * ewwow fow output buffew type
		 */
		if (s->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_CWOP:
		/*
		 * CWOP tawget is onwy vawid fow output buffew type, wetuwn
		 * ewwow fow captuwe buffew type
		 */
		if (s->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		bweak;
	/*
	 * bound and defauwt cwop/compose tawgets awe invawid tawgets to
	 * twy/set
	 */
	defauwt:
		wetuwn -EINVAW;
	}

	/*
	 * Fow SEQ_XX buffews, cwop height shouwd be wess than the height of
	 * the fiewd height, not the buffew height
	 */
	if (q_data->fwags & Q_IS_SEQ_XX)
		height = pix->height / 2;
	ewse
		height = pix->height;

	if (s->w.top < 0 || s->w.weft < 0) {
		vpe_eww(ctx->dev, "negative vawues fow top and weft\n");
		s->w.top = s->w.weft = 0;
	}

	v4w_bound_awign_image(&s->w.width, MIN_W, pix->width, 1,
		&s->w.height, MIN_H, height, H_AWIGN, S_AWIGN);

	/* adjust weft/top if cwopping wectangwe is out of bounds */
	if (s->w.weft + s->w.width > pix->width)
		s->w.weft = pix->width - s->w.width;
	if (s->w.top + s->w.height > pix->height)
		s->w.top = pix->height - s->w.height;

	wetuwn 0;
}

static int vpe_g_sewection(stwuct fiwe *fiwe, void *fh,
		stwuct v4w2_sewection *s)
{
	stwuct vpe_ctx *ctx = fiwe->pwivate_data;
	stwuct vpe_q_data *q_data;
	stwuct v4w2_pix_fowmat_mpwane *pix;
	boow use_c_wect = fawse;

	if ((s->type != V4W2_BUF_TYPE_VIDEO_CAPTUWE) &&
	    (s->type != V4W2_BUF_TYPE_VIDEO_OUTPUT))
		wetuwn -EINVAW;

	q_data = get_q_data(ctx, s->type);
	if (!q_data)
		wetuwn -EINVAW;

	pix = &q_data->fowmat.fmt.pix_mp;

	switch (s->tawget) {
	case V4W2_SEW_TGT_COMPOSE_DEFAUWT:
	case V4W2_SEW_TGT_COMPOSE_BOUNDS:
		if (s->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_CWOP_BOUNDS:
	case V4W2_SEW_TGT_CWOP_DEFAUWT:
		if (s->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		bweak;
	case V4W2_SEW_TGT_COMPOSE:
		if (s->type == V4W2_BUF_TYPE_VIDEO_OUTPUT)
			wetuwn -EINVAW;
		use_c_wect = twue;
		bweak;
	case V4W2_SEW_TGT_CWOP:
		if (s->type == V4W2_BUF_TYPE_VIDEO_CAPTUWE)
			wetuwn -EINVAW;
		use_c_wect = twue;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	if (use_c_wect) {
		/*
		 * fow CWOP/COMPOSE tawget type, wetuwn c_wect pawams fwom the
		 * wespective buffew type
		 */
		s->w = q_data->c_wect;
	} ewse {
		/*
		 * fow DEFAUWT/BOUNDS tawget type, wetuwn width and height fwom
		 * S_FMT of the wespective buffew type
		 */
		s->w.weft = 0;
		s->w.top = 0;
		s->w.width = pix->width;
		s->w.height = pix->height;
	}

	wetuwn 0;
}


static int vpe_s_sewection(stwuct fiwe *fiwe, void *fh,
		stwuct v4w2_sewection *s)
{
	stwuct vpe_ctx *ctx = fiwe->pwivate_data;
	stwuct vpe_q_data *q_data;
	stwuct v4w2_sewection sew = *s;
	int wet;

	wet = __vpe_twy_sewection(ctx, &sew);
	if (wet)
		wetuwn wet;

	q_data = get_q_data(ctx, sew.type);
	if (!q_data)
		wetuwn -EINVAW;

	if ((q_data->c_wect.weft == sew.w.weft) &&
			(q_data->c_wect.top == sew.w.top) &&
			(q_data->c_wect.width == sew.w.width) &&
			(q_data->c_wect.height == sew.w.height)) {
		vpe_dbg(ctx->dev,
			"wequested cwop/compose vawues awe awweady set\n");
		wetuwn 0;
	}

	q_data->c_wect = sew.w;

	wetuwn set_swcdst_pawams(ctx);
}

/*
 * defines numbew of buffews/fwames a context can pwocess with VPE befowe
 * switching to a diffewent context. defauwt vawue is 1 buffew pew context
 */
#define V4W2_CID_VPE_BUFS_PEW_JOB		(V4W2_CID_USEW_TI_VPE_BASE + 0)

static int vpe_s_ctww(stwuct v4w2_ctww *ctww)
{
	stwuct vpe_ctx *ctx =
		containew_of(ctww->handwew, stwuct vpe_ctx, hdw);

	switch (ctww->id) {
	case V4W2_CID_VPE_BUFS_PEW_JOB:
		ctx->bufs_pew_job = ctww->vaw;
		bweak;

	defauwt:
		vpe_eww(ctx->dev, "Invawid contwow\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static const stwuct v4w2_ctww_ops vpe_ctww_ops = {
	.s_ctww = vpe_s_ctww,
};

static const stwuct v4w2_ioctw_ops vpe_ioctw_ops = {
	.vidioc_quewycap		= vpe_quewycap,

	.vidioc_enum_fmt_vid_cap	= vpe_enum_fmt,
	.vidioc_g_fmt_vid_cap_mpwane	= vpe_g_fmt,
	.vidioc_twy_fmt_vid_cap_mpwane	= vpe_twy_fmt,
	.vidioc_s_fmt_vid_cap_mpwane	= vpe_s_fmt,

	.vidioc_enum_fmt_vid_out	= vpe_enum_fmt,
	.vidioc_g_fmt_vid_out_mpwane	= vpe_g_fmt,
	.vidioc_twy_fmt_vid_out_mpwane	= vpe_twy_fmt,
	.vidioc_s_fmt_vid_out_mpwane	= vpe_s_fmt,

	.vidioc_g_sewection		= vpe_g_sewection,
	.vidioc_s_sewection		= vpe_s_sewection,

	.vidioc_weqbufs			= v4w2_m2m_ioctw_weqbufs,
	.vidioc_quewybuf		= v4w2_m2m_ioctw_quewybuf,
	.vidioc_qbuf			= v4w2_m2m_ioctw_qbuf,
	.vidioc_dqbuf			= v4w2_m2m_ioctw_dqbuf,
	.vidioc_expbuf			= v4w2_m2m_ioctw_expbuf,
	.vidioc_stweamon		= v4w2_m2m_ioctw_stweamon,
	.vidioc_stweamoff		= v4w2_m2m_ioctw_stweamoff,

	.vidioc_subscwibe_event		= v4w2_ctww_subscwibe_event,
	.vidioc_unsubscwibe_event	= v4w2_event_unsubscwibe,
};

/*
 * Queue opewations
 */
static int vpe_queue_setup(stwuct vb2_queue *vq,
			   unsigned int *nbuffews, unsigned int *npwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	int i;
	stwuct vpe_ctx *ctx = vb2_get_dwv_pwiv(vq);
	stwuct vpe_q_data *q_data;
	stwuct v4w2_pix_fowmat_mpwane *pix;

	q_data = get_q_data(ctx, vq->type);
	if (!q_data)
		wetuwn -EINVAW;

	pix = &q_data->fowmat.fmt.pix_mp;
	*npwanes = pix->num_pwanes;

	fow (i = 0; i < *npwanes; i++)
		sizes[i] = pix->pwane_fmt[i].sizeimage;

	vpe_dbg(ctx->dev, "get %d buffew(s) of size %d", *nbuffews,
		sizes[VPE_WUMA]);
	if (*npwanes == 2)
		vpe_dbg(ctx->dev, " and %d\n", sizes[VPE_CHWOMA]);

	wetuwn 0;
}

static int vpe_buf_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vpe_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vpe_q_data *q_data;
	stwuct v4w2_pix_fowmat_mpwane *pix;
	int i;

	vpe_dbg(ctx->dev, "type: %d\n", vb->vb2_queue->type);

	q_data = get_q_data(ctx, vb->vb2_queue->type);
	if (!q_data)
		wetuwn -EINVAW;

	pix = &q_data->fowmat.fmt.pix_mp;

	if (vb->vb2_queue->type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE) {
		if (!(q_data->fwags & Q_IS_INTEWWACED)) {
			vbuf->fiewd = V4W2_FIEWD_NONE;
		} ewse {
			if (vbuf->fiewd != V4W2_FIEWD_TOP &&
			    vbuf->fiewd != V4W2_FIEWD_BOTTOM &&
			    vbuf->fiewd != V4W2_FIEWD_SEQ_TB &&
			    vbuf->fiewd != V4W2_FIEWD_SEQ_BT)
				wetuwn -EINVAW;
		}
	}

	fow (i = 0; i < pix->num_pwanes; i++) {
		if (vb2_pwane_size(vb, i) < pix->pwane_fmt[i].sizeimage) {
			vpe_eww(ctx->dev,
				"data wiww not fit into pwane (%wu < %wu)\n",
				vb2_pwane_size(vb, i),
				(wong)pix->pwane_fmt[i].sizeimage);
			wetuwn -EINVAW;
		}
	}

	fow (i = 0; i < pix->num_pwanes; i++)
		vb2_set_pwane_paywoad(vb, i, pix->pwane_fmt[i].sizeimage);

	wetuwn 0;
}

static void vpe_buf_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct vpe_ctx *ctx = vb2_get_dwv_pwiv(vb->vb2_queue);

	v4w2_m2m_buf_queue(ctx->fh.m2m_ctx, vbuf);
}

static int check_swcdst_sizes(stwuct vpe_ctx *ctx)
{
	stwuct vpe_q_data *s_q_data =  &ctx->q_data[Q_DATA_SWC];
	stwuct vpe_q_data *d_q_data =  &ctx->q_data[Q_DATA_DST];
	unsigned int swc_w = s_q_data->c_wect.width;
	unsigned int swc_h = s_q_data->c_wect.height;
	unsigned int dst_w = d_q_data->c_wect.width;
	unsigned int dst_h = d_q_data->c_wect.height;

	if (swc_w == dst_w && swc_h == dst_h)
		wetuwn 0;

	if (swc_h <= SC_MAX_PIXEW_HEIGHT &&
	    swc_w <= SC_MAX_PIXEW_WIDTH &&
	    dst_h <= SC_MAX_PIXEW_HEIGHT &&
	    dst_w <= SC_MAX_PIXEW_WIDTH)
		wetuwn 0;

	wetuwn -1;
}

static void vpe_wetuwn_aww_buffews(stwuct vpe_ctx *ctx,  stwuct vb2_queue *q,
				   enum vb2_buffew_state state)
{
	stwuct vb2_v4w2_buffew *vb;
	unsigned wong fwags;

	fow (;;) {
		if (V4W2_TYPE_IS_OUTPUT(q->type))
			vb = v4w2_m2m_swc_buf_wemove(ctx->fh.m2m_ctx);
		ewse
			vb = v4w2_m2m_dst_buf_wemove(ctx->fh.m2m_ctx);
		if (!vb)
			bweak;
		spin_wock_iwqsave(&ctx->dev->wock, fwags);
		v4w2_m2m_buf_done(vb, state);
		spin_unwock_iwqwestowe(&ctx->dev->wock, fwags);
	}

	/*
	 * Cweanup the in-twansit vb2 buffews that have been
	 * wemoved fwom theiw wespective queue awweady but fow
	 * which pwocecessing has not been compweted yet.
	 */
	if (V4W2_TYPE_IS_OUTPUT(q->type)) {
		spin_wock_iwqsave(&ctx->dev->wock, fwags);

		if (ctx->swc_vbs[2])
			v4w2_m2m_buf_done(ctx->swc_vbs[2], state);

		if (ctx->swc_vbs[1] && (ctx->swc_vbs[1] != ctx->swc_vbs[2]))
			v4w2_m2m_buf_done(ctx->swc_vbs[1], state);

		if (ctx->swc_vbs[0] &&
		    (ctx->swc_vbs[0] != ctx->swc_vbs[1]) &&
		    (ctx->swc_vbs[0] != ctx->swc_vbs[2]))
			v4w2_m2m_buf_done(ctx->swc_vbs[0], state);

		ctx->swc_vbs[2] = NUWW;
		ctx->swc_vbs[1] = NUWW;
		ctx->swc_vbs[0] = NUWW;

		spin_unwock_iwqwestowe(&ctx->dev->wock, fwags);
	} ewse {
		if (ctx->dst_vb) {
			spin_wock_iwqsave(&ctx->dev->wock, fwags);

			v4w2_m2m_buf_done(ctx->dst_vb, state);
			ctx->dst_vb = NUWW;
			spin_unwock_iwqwestowe(&ctx->dev->wock, fwags);
		}
	}
}

static int vpe_stawt_stweaming(stwuct vb2_queue *q, unsigned int count)
{
	stwuct vpe_ctx *ctx = vb2_get_dwv_pwiv(q);

	/* Check any of the size exceed maximum scawing sizes */
	if (check_swcdst_sizes(ctx)) {
		vpe_eww(ctx->dev,
			"Convewsion setup faiwed, check souwce and destination pawametews\n"
			);
		vpe_wetuwn_aww_buffews(ctx, q, VB2_BUF_STATE_QUEUED);
		wetuwn -EINVAW;
	}

	if (ctx->deintewwacing)
		config_edi_input_mode(ctx, 0x0);

	if (ctx->sequence != 0)
		set_swcdst_pawams(ctx);

	wetuwn 0;
}

static void vpe_stop_stweaming(stwuct vb2_queue *q)
{
	stwuct vpe_ctx *ctx = vb2_get_dwv_pwiv(q);

	vpe_dump_wegs(ctx->dev);
	vpdma_dump_wegs(ctx->dev->vpdma);

	vpe_wetuwn_aww_buffews(ctx, q, VB2_BUF_STATE_EWWOW);
}

static const stwuct vb2_ops vpe_qops = {
	.queue_setup	 = vpe_queue_setup,
	.buf_pwepawe	 = vpe_buf_pwepawe,
	.buf_queue	 = vpe_buf_queue,
	.wait_pwepawe	 = vb2_ops_wait_pwepawe,
	.wait_finish	 = vb2_ops_wait_finish,
	.stawt_stweaming = vpe_stawt_stweaming,
	.stop_stweaming  = vpe_stop_stweaming,
};

static int queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
		      stwuct vb2_queue *dst_vq)
{
	stwuct vpe_ctx *ctx = pwiv;
	stwuct vpe_dev *dev = ctx->dev;
	int wet;

	memset(swc_vq, 0, sizeof(*swc_vq));
	swc_vq->type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	swc_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	swc_vq->dwv_pwiv = ctx;
	swc_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	swc_vq->ops = &vpe_qops;
	swc_vq->mem_ops = &vb2_dma_contig_memops;
	swc_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	swc_vq->wock = &dev->dev_mutex;
	swc_vq->dev = dev->v4w2_dev.dev;

	wet = vb2_queue_init(swc_vq);
	if (wet)
		wetuwn wet;

	memset(dst_vq, 0, sizeof(*dst_vq));
	dst_vq->type = V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;
	dst_vq->io_modes = VB2_MMAP | VB2_DMABUF;
	dst_vq->dwv_pwiv = ctx;
	dst_vq->buf_stwuct_size = sizeof(stwuct v4w2_m2m_buffew);
	dst_vq->ops = &vpe_qops;
	dst_vq->mem_ops = &vb2_dma_contig_memops;
	dst_vq->timestamp_fwags = V4W2_BUF_FWAG_TIMESTAMP_COPY;
	dst_vq->wock = &dev->dev_mutex;
	dst_vq->dev = dev->v4w2_dev.dev;

	wetuwn vb2_queue_init(dst_vq);
}

static const stwuct v4w2_ctww_config vpe_bufs_pew_job = {
	.ops = &vpe_ctww_ops,
	.id = V4W2_CID_VPE_BUFS_PEW_JOB,
	.name = "Buffews Pew Twansaction",
	.type = V4W2_CTWW_TYPE_INTEGEW,
	.def = VPE_DEF_BUFS_PEW_JOB,
	.min = 1,
	.max = VIDEO_MAX_FWAME,
	.step = 1,
};

/*
 * Fiwe opewations
 */
static int vpe_open(stwuct fiwe *fiwe)
{
	stwuct vpe_dev *dev = video_dwvdata(fiwe);
	stwuct vpe_q_data *s_q_data;
	stwuct v4w2_ctww_handwew *hdw;
	stwuct vpe_ctx *ctx;
	stwuct v4w2_pix_fowmat_mpwane *pix;
	int wet;

	vpe_dbg(dev, "vpe_open\n");

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->dev = dev;

	if (mutex_wock_intewwuptibwe(&dev->dev_mutex)) {
		wet = -EWESTAWTSYS;
		goto fwee_ctx;
	}

	wet = vpdma_cweate_desc_wist(&ctx->desc_wist, VPE_DESC_WIST_SIZE,
			VPDMA_WIST_TYPE_NOWMAW);
	if (wet != 0)
		goto unwock;

	wet = vpdma_awwoc_desc_buf(&ctx->mmw_adb, sizeof(stwuct vpe_mmw_adb));
	if (wet != 0)
		goto fwee_desc_wist;

	wet = vpdma_awwoc_desc_buf(&ctx->sc_coeff_h, SC_COEF_SWAM_SIZE);
	if (wet != 0)
		goto fwee_mmw_adb;

	wet = vpdma_awwoc_desc_buf(&ctx->sc_coeff_v, SC_COEF_SWAM_SIZE);
	if (wet != 0)
		goto fwee_sc_h;

	init_adb_hdws(ctx);

	v4w2_fh_init(&ctx->fh, video_devdata(fiwe));
	fiwe->pwivate_data = ctx;

	hdw = &ctx->hdw;
	v4w2_ctww_handwew_init(hdw, 1);
	v4w2_ctww_new_custom(hdw, &vpe_bufs_pew_job, NUWW);
	if (hdw->ewwow) {
		wet = hdw->ewwow;
		goto exit_fh;
	}
	ctx->fh.ctww_handwew = hdw;
	v4w2_ctww_handwew_setup(hdw);

	s_q_data = &ctx->q_data[Q_DATA_SWC];
	pix = &s_q_data->fowmat.fmt.pix_mp;
	s_q_data->fmt = __find_fowmat(V4W2_PIX_FMT_YUYV);
	pix->pixewfowmat = s_q_data->fmt->fouwcc;
	s_q_data->fowmat.type = V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE;
	pix->width = 1920;
	pix->height = 1080;
	pix->num_pwanes = 1;
	pix->pwane_fmt[VPE_WUMA].bytespewwine = (pix->width *
			s_q_data->fmt->vpdma_fmt[VPE_WUMA]->depth) >> 3;
	pix->pwane_fmt[VPE_WUMA].sizeimage =
			pix->pwane_fmt[VPE_WUMA].bytespewwine *
			pix->height;
	pix->cowowspace = V4W2_COWOWSPACE_WEC709;
	pix->xfew_func = V4W2_XFEW_FUNC_DEFAUWT;
	pix->ycbcw_enc = V4W2_YCBCW_ENC_DEFAUWT;
	pix->quantization = V4W2_QUANTIZATION_DEFAUWT;
	pix->fiewd = V4W2_FIEWD_NONE;
	s_q_data->c_wect.weft = 0;
	s_q_data->c_wect.top = 0;
	s_q_data->c_wect.width = pix->width;
	s_q_data->c_wect.height = pix->height;
	s_q_data->fwags = 0;

	ctx->q_data[Q_DATA_DST] = *s_q_data;
	ctx->q_data[Q_DATA_DST].fowmat.type =
			V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE;

	set_dei_shadow_wegistews(ctx);
	set_swc_wegistews(ctx);
	set_dst_wegistews(ctx);
	wet = set_swcdst_pawams(ctx);
	if (wet)
		goto exit_fh;

	ctx->fh.m2m_ctx = v4w2_m2m_ctx_init(dev->m2m_dev, ctx, &queue_init);

	if (IS_EWW(ctx->fh.m2m_ctx)) {
		wet = PTW_EWW(ctx->fh.m2m_ctx);
		goto exit_fh;
	}

	v4w2_fh_add(&ctx->fh);

	/*
	 * fow now, just wepowt the cweation of the fiwst instance, we can watew
	 * optimize the dwivew to enabwe ow disabwe cwocks when the fiwst
	 * instance is cweated ow the wast instance weweased
	 */
	if (atomic_inc_wetuwn(&dev->num_instances) == 1)
		vpe_dbg(dev, "fiwst instance cweated\n");

	ctx->bufs_pew_job = VPE_DEF_BUFS_PEW_JOB;

	ctx->woad_mmws = twue;

	vpe_dbg(dev, "cweated instance %p, m2m_ctx: %p\n",
		ctx, ctx->fh.m2m_ctx);

	mutex_unwock(&dev->dev_mutex);

	wetuwn 0;
exit_fh:
	v4w2_ctww_handwew_fwee(hdw);
	v4w2_fh_exit(&ctx->fh);
	vpdma_fwee_desc_buf(&ctx->sc_coeff_v);
fwee_sc_h:
	vpdma_fwee_desc_buf(&ctx->sc_coeff_h);
fwee_mmw_adb:
	vpdma_fwee_desc_buf(&ctx->mmw_adb);
fwee_desc_wist:
	vpdma_fwee_desc_wist(&ctx->desc_wist);
unwock:
	mutex_unwock(&dev->dev_mutex);
fwee_ctx:
	kfwee(ctx);
	wetuwn wet;
}

static int vpe_wewease(stwuct fiwe *fiwe)
{
	stwuct vpe_dev *dev = video_dwvdata(fiwe);
	stwuct vpe_ctx *ctx = fiwe->pwivate_data;

	vpe_dbg(dev, "weweasing instance %p\n", ctx);

	mutex_wock(&dev->dev_mutex);
	fwee_mv_buffews(ctx);

	vpdma_unmap_desc_buf(dev->vpdma, &ctx->desc_wist.buf);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->mmw_adb);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->sc_coeff_h);
	vpdma_unmap_desc_buf(dev->vpdma, &ctx->sc_coeff_v);

	vpdma_fwee_desc_wist(&ctx->desc_wist);
	vpdma_fwee_desc_buf(&ctx->mmw_adb);

	vpdma_fwee_desc_buf(&ctx->sc_coeff_v);
	vpdma_fwee_desc_buf(&ctx->sc_coeff_h);

	v4w2_fh_dew(&ctx->fh);
	v4w2_fh_exit(&ctx->fh);
	v4w2_ctww_handwew_fwee(&ctx->hdw);
	v4w2_m2m_ctx_wewease(ctx->fh.m2m_ctx);

	kfwee(ctx);

	/*
	 * fow now, just wepowt the wewease of the wast instance, we can watew
	 * optimize the dwivew to enabwe ow disabwe cwocks when the fiwst
	 * instance is cweated ow the wast instance weweased
	 */
	if (atomic_dec_wetuwn(&dev->num_instances) == 0)
		vpe_dbg(dev, "wast instance weweased\n");

	mutex_unwock(&dev->dev_mutex);

	wetuwn 0;
}

static const stwuct v4w2_fiwe_opewations vpe_fops = {
	.ownew		= THIS_MODUWE,
	.open		= vpe_open,
	.wewease	= vpe_wewease,
	.poww		= v4w2_m2m_fop_poww,
	.unwocked_ioctw	= video_ioctw2,
	.mmap		= v4w2_m2m_fop_mmap,
};

static const stwuct video_device vpe_videodev = {
	.name		= VPE_MODUWE_NAME,
	.fops		= &vpe_fops,
	.ioctw_ops	= &vpe_ioctw_ops,
	.minow		= -1,
	.wewease	= video_device_wewease_empty,
	.vfw_diw	= VFW_DIW_M2M,
	.device_caps	= V4W2_CAP_VIDEO_M2M_MPWANE | V4W2_CAP_STWEAMING,
};

static const stwuct v4w2_m2m_ops m2m_ops = {
	.device_wun	= device_wun,
	.job_weady	= job_weady,
	.job_abowt	= job_abowt,
};

static int vpe_wuntime_get(stwuct pwatfowm_device *pdev)
{
	int w;

	dev_dbg(&pdev->dev, "vpe_wuntime_get\n");

	w = pm_wuntime_wesume_and_get(&pdev->dev);
	WAWN_ON(w < 0);
	wetuwn w;
}

static void vpe_wuntime_put(stwuct pwatfowm_device *pdev)
{

	int w;

	dev_dbg(&pdev->dev, "vpe_wuntime_put\n");

	w = pm_wuntime_put_sync(&pdev->dev);
	WAWN_ON(w < 0 && w != -ENOSYS);
}

static void vpe_fw_cb(stwuct pwatfowm_device *pdev)
{
	stwuct vpe_dev *dev = pwatfowm_get_dwvdata(pdev);
	stwuct video_device *vfd;
	int wet;

	vfd = &dev->vfd;
	*vfd = vpe_videodev;
	vfd->wock = &dev->dev_mutex;
	vfd->v4w2_dev = &dev->v4w2_dev;

	wet = video_wegistew_device(vfd, VFW_TYPE_VIDEO, 0);
	if (wet) {
		vpe_eww(dev, "Faiwed to wegistew video device\n");

		vpe_set_cwock_enabwe(dev, 0);
		vpe_wuntime_put(pdev);
		pm_wuntime_disabwe(&pdev->dev);
		v4w2_m2m_wewease(dev->m2m_dev);
		v4w2_device_unwegistew(&dev->v4w2_dev);

		wetuwn;
	}

	video_set_dwvdata(vfd, dev);
	dev_info(dev->v4w2_dev.dev, "Device wegistewed as /dev/video%d\n",
		vfd->num);
}

static int vpe_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct vpe_dev *dev;
	int wet, iwq, func;

	wet = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(32));
	if (wet) {
		dev_eww(&pdev->dev,
			"32-bit consistent DMA enabwe faiwed\n");
		wetuwn wet;
	}

	dev = devm_kzawwoc(&pdev->dev, sizeof(*dev), GFP_KEWNEW);
	if (!dev)
		wetuwn -ENOMEM;

	spin_wock_init(&dev->wock);

	wet = v4w2_device_wegistew(&pdev->dev, &dev->v4w2_dev);
	if (wet)
		wetuwn wet;

	atomic_set(&dev->num_instances, 0);
	mutex_init(&dev->dev_mutex);

	dev->wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM,
						"vpe_top");
	if (!dev->wes) {
		dev_eww(&pdev->dev, "missing 'vpe_top' wesouwces data\n");
		wetuwn -ENODEV;
	}

	/*
	 * HACK: we get wesouwce info fwom device twee in the fowm of a wist of
	 * VPE sub bwocks, the dwivew cuwwentwy uses onwy the base of vpe_top
	 * fow wegistew access, the dwivew shouwd be changed watew to access
	 * wegistews based on the sub bwock base addwesses
	 */
	dev->base = devm_iowemap(&pdev->dev, dev->wes->stawt, SZ_32K);
	if (!dev->base) {
		wet = -ENOMEM;
		goto v4w2_dev_unweg;
	}

	iwq = pwatfowm_get_iwq(pdev, 0);
	wet = devm_wequest_iwq(&pdev->dev, iwq, vpe_iwq, 0, VPE_MODUWE_NAME,
			dev);
	if (wet)
		goto v4w2_dev_unweg;

	pwatfowm_set_dwvdata(pdev, dev);

	dev->m2m_dev = v4w2_m2m_init(&m2m_ops);
	if (IS_EWW(dev->m2m_dev)) {
		vpe_eww(dev, "Faiwed to init mem2mem device\n");
		wet = PTW_EWW(dev->m2m_dev);
		goto v4w2_dev_unweg;
	}

	pm_wuntime_enabwe(&pdev->dev);

	wet = vpe_wuntime_get(pdev);
	if (wet < 0)
		goto wew_m2m;

	/* Pewfowm cwk enabwe fowwowed by weset */
	vpe_set_cwock_enabwe(dev, 1);

	vpe_top_weset(dev);

	func = wead_fiewd_weg(dev, VPE_PID, VPE_PID_FUNC_MASK,
		VPE_PID_FUNC_SHIFT);
	vpe_dbg(dev, "VPE PID function %x\n", func);

	vpe_top_vpdma_weset(dev);

	dev->sc = sc_cweate(pdev, "sc");
	if (IS_EWW(dev->sc)) {
		wet = PTW_EWW(dev->sc);
		goto wuntime_put;
	}

	dev->csc = csc_cweate(pdev, "csc");
	if (IS_EWW(dev->csc)) {
		wet = PTW_EWW(dev->csc);
		goto wuntime_put;
	}

	dev->vpdma = &dev->vpdma_data;
	wet = vpdma_cweate(pdev, dev->vpdma, vpe_fw_cb);
	if (wet)
		goto wuntime_put;

	wetuwn 0;

wuntime_put:
	vpe_wuntime_put(pdev);
wew_m2m:
	pm_wuntime_disabwe(&pdev->dev);
	v4w2_m2m_wewease(dev->m2m_dev);
v4w2_dev_unweg:
	v4w2_device_unwegistew(&dev->v4w2_dev);

	wetuwn wet;
}

static void vpe_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct vpe_dev *dev = pwatfowm_get_dwvdata(pdev);

	v4w2_info(&dev->v4w2_dev, "Wemoving " VPE_MODUWE_NAME);

	v4w2_m2m_wewease(dev->m2m_dev);
	video_unwegistew_device(&dev->vfd);
	v4w2_device_unwegistew(&dev->v4w2_dev);

	vpe_set_cwock_enabwe(dev, 0);
	vpe_wuntime_put(pdev);
	pm_wuntime_disabwe(&pdev->dev);
}

#if defined(CONFIG_OF)
static const stwuct of_device_id vpe_of_match[] = {
	{
		.compatibwe = "ti,dwa7-vpe",
	},
	{},
};
MODUWE_DEVICE_TABWE(of, vpe_of_match);
#endif

static stwuct pwatfowm_dwivew vpe_pdwv = {
	.pwobe		= vpe_pwobe,
	.wemove_new	= vpe_wemove,
	.dwivew		= {
		.name	= VPE_MODUWE_NAME,
		.of_match_tabwe = of_match_ptw(vpe_of_match),
	},
};

moduwe_pwatfowm_dwivew(vpe_pdwv);

MODUWE_DESCWIPTION("TI VPE dwivew");
MODUWE_AUTHOW("Dawe Fawnswowth, <dawe@fawnswowth.owg>");
MODUWE_WICENSE("GPW");
