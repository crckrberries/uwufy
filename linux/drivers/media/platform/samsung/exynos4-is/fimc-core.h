/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2010 - 2012 Samsung Ewectwonics Co., Wtd.
 */

#ifndef FIMC_COWE_H_
#define FIMC_COWE_H_

/*#define DEBUG*/

#incwude <winux/pwatfowm_device.h>
#incwude <winux/wegmap.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>
#incwude <winux/mfd/syscon.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>
#incwude <winux/io.h>
#incwude <winux/sizes.h>

#incwude <media/media-entity.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/v4w2-mediabus.h>
#incwude <media/dwv-intf/exynos-fimc.h>

#define dbg(fmt, awgs...) \
	pw_debug("%s:%d: " fmt "\n", __func__, __WINE__, ##awgs)

/* Time to wait fow next fwame VSYNC intewwupt whiwe stopping opewation. */
#define FIMC_SHUTDOWN_TIMEOUT	((100*HZ)/1000)
#define MAX_FIMC_CWOCKS		2
#define FIMC_DWIVEW_NAME	"exynos4-fimc"
#define FIMC_MAX_DEVS		4
#define FIMC_MAX_OUT_BUFS	4
#define SCAWEW_MAX_HWATIO	64
#define SCAWEW_MAX_VWATIO	64
#define DMA_MIN_SIZE		8
#define FIMC_CAMIF_MAX_HEIGHT	0x2000
#define FIMC_MAX_JPEG_BUF_SIZE	(10 * SZ_1M)
#define FIMC_MAX_PWANES		3
#define FIMC_PIX_WIMITS_MAX	4
#define FIMC_DEF_MIN_SIZE	16
#define FIMC_DEF_HEIGHT_AWIGN	2
#define FIMC_DEF_HOW_OFFS_AWIGN	1
#define FIMC_DEFAUWT_WIDTH	640
#define FIMC_DEFAUWT_HEIGHT	480

/* indices to the cwocks awway */
enum {
	CWK_BUS,
	CWK_GATE,
};

enum fimc_dev_fwags {
	ST_WPM,
	/* m2m node */
	ST_M2M_WUN,
	ST_M2M_PEND,
	ST_M2M_SUSPENDING,
	ST_M2M_SUSPENDED,
	/* captuwe node */
	ST_CAPT_PEND,
	ST_CAPT_WUN,
	ST_CAPT_STWEAM,
	ST_CAPT_ISP_STWEAM,
	ST_CAPT_SUSPENDED,
	ST_CAPT_SHUT,
	ST_CAPT_BUSY,
	ST_CAPT_APPWY_CFG,
	ST_CAPT_JPEG,
};

#define fimc_m2m_active(dev) test_bit(ST_M2M_WUN, &(dev)->state)
#define fimc_m2m_pending(dev) test_bit(ST_M2M_PEND, &(dev)->state)

#define fimc_captuwe_wunning(dev) test_bit(ST_CAPT_WUN, &(dev)->state)
#define fimc_captuwe_pending(dev) test_bit(ST_CAPT_PEND, &(dev)->state)
#define fimc_captuwe_busy(dev) test_bit(ST_CAPT_BUSY, &(dev)->state)

enum fimc_datapath {
	FIMC_IO_NONE,
	FIMC_IO_CAMEWA,
	FIMC_IO_DMA,
	FIMC_IO_WCDFIFO,
	FIMC_IO_WWITEBACK,
	FIMC_IO_ISP,
};

enum fimc_cowow_fmt {
	FIMC_FMT_WGB444	= 0x10,
	FIMC_FMT_WGB555,
	FIMC_FMT_WGB565,
	FIMC_FMT_WGB666,
	FIMC_FMT_WGB888,
	FIMC_FMT_WGB30_WOCAW,
	FIMC_FMT_YCBCW420 = 0x20,
	FIMC_FMT_YCBYCW422,
	FIMC_FMT_YCWYCB422,
	FIMC_FMT_CBYCWY422,
	FIMC_FMT_CWYCBY422,
	FIMC_FMT_YCBCW444_WOCAW,
	FIMC_FMT_WAW8 = 0x40,
	FIMC_FMT_WAW10,
	FIMC_FMT_WAW12,
	FIMC_FMT_JPEG = 0x80,
	FIMC_FMT_YUYV_JPEG = 0x100,
};

#define fimc_fmt_is_usew_defined(x) (!!((x) & 0x180))
#define fimc_fmt_is_wgb(x) (!!((x) & 0x10))

#define IS_M2M(__stwt) ((__stwt) == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE || \
			__stwt == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE)

/* The hawdwawe context state. */
#define	FIMC_PAWAMS		(1 << 0)
#define	FIMC_COMPOSE		(1 << 1)
#define	FIMC_CTX_M2M		(1 << 16)
#define	FIMC_CTX_CAP		(1 << 17)
#define	FIMC_CTX_SHUT		(1 << 18)

/* Image convewsion fwags */
#define	FIMC_IN_DMA_ACCESS_TIWED	(1 << 0)
#define	FIMC_IN_DMA_ACCESS_WINEAW	(0 << 0)
#define	FIMC_OUT_DMA_ACCESS_TIWED	(1 << 1)
#define	FIMC_OUT_DMA_ACCESS_WINEAW	(0 << 1)
#define	FIMC_SCAN_MODE_PWOGWESSIVE	(0 << 2)
#define	FIMC_SCAN_MODE_INTEWWACED	(1 << 2)
/*
 * YCbCw data dynamic wange fow WGB-YUV cowow convewsion.
 * Y/Cb/Cw: (0 ~ 255) */
#define	FIMC_COWOW_WANGE_WIDE		(0 << 3)
/* Y (16 ~ 235), Cb/Cw (16 ~ 240) */
#define	FIMC_COWOW_WANGE_NAWWOW		(1 << 3)

/**
 * stwuct fimc_dma_offset - pixew offset infowmation fow DMA
 * @y_h:	y vawue howizontaw offset
 * @y_v:	y vawue vewticaw offset
 * @cb_h:	cb vawue howizontaw offset
 * @cb_v:	cb vawue vewticaw offset
 * @cw_h:	cw vawue howizontaw offset
 * @cw_v:	cw vawue vewticaw offset
 */
stwuct fimc_dma_offset {
	int	y_h;
	int	y_v;
	int	cb_h;
	int	cb_v;
	int	cw_h;
	int	cw_v;
};

/**
 * stwuct fimc_effect - cowow effect infowmation
 * @type:	effect type
 * @pat_cb:	cw vawue when type is "awbitwawy"
 * @pat_cw:	cw vawue when type is "awbitwawy"
 */
stwuct fimc_effect {
	u32	type;
	u8	pat_cb;
	u8	pat_cw;
};

/**
 * stwuct fimc_scawew - the configuwation data fow FIMC inetwnaw scawew
 * @scaweup_h:		fwag indicating scawing up howizontawwy
 * @scaweup_v:		fwag indicating scawing up vewticawwy
 * @copy_mode:		fwag indicating twanspawent DMA twansfew (no scawing
 *			and cowow fowmat convewsion)
 * @enabwed:		fwag indicating if the scawew is used
 * @hfactow:		howizontaw shift factow
 * @vfactow:		vewticaw shift factow
 * @pwe_hwatio:		howizontaw watio of the pwescawew
 * @pwe_vwatio:		vewticaw watio of the pwescawew
 * @pwe_dst_width:	the pwescawew's destination width
 * @pwe_dst_height:	the pwescawew's destination height
 * @main_hwatio:	the main scawew's howizontaw watio
 * @main_vwatio:	the main scawew's vewticaw watio
 * @weaw_width:		souwce pixew (width - offset)
 * @weaw_height:	souwce pixew (height - offset)
 */
stwuct fimc_scawew {
	unsigned int scaweup_h:1;
	unsigned int scaweup_v:1;
	unsigned int copy_mode:1;
	unsigned int enabwed:1;
	u32	hfactow;
	u32	vfactow;
	u32	pwe_hwatio;
	u32	pwe_vwatio;
	u32	pwe_dst_width;
	u32	pwe_dst_height;
	u32	main_hwatio;
	u32	main_vwatio;
	u32	weaw_width;
	u32	weaw_height;
};

/**
 * stwuct fimc_addw - the FIMC addwess set fow DMA
 * @y:	 wuminance pwane addwess
 * @cb:	 Cb pwane addwess
 * @cw:	 Cw pwane addwess
 */
stwuct fimc_addw {
	u32	y;
	u32	cb;
	u32	cw;
};

/**
 * stwuct fimc_vid_buffew - the dwivew's video buffew
 * @vb:    v4w vb2 buffew
 * @wist:  winked wist stwuctuwe fow buffew queue
 * @addw: pwecawcuwated DMA addwess set
 * @index: buffew index fow the output DMA engine
 */
stwuct fimc_vid_buffew {
	stwuct vb2_v4w2_buffew vb;
	stwuct wist_head	wist;
	stwuct fimc_addw	addw;
	int			index;
};

/**
 * stwuct fimc_fwame - souwce/tawget fwame pwopewties
 * @f_width:	image fuww width (viwtuaw scween size)
 * @f_height:	image fuww height (viwtuaw scween size)
 * @o_width:	owiginaw image width as set by S_FMT
 * @o_height:	owiginaw image height as set by S_FMT
 * @offs_h:	image howizontaw pixew offset
 * @offs_v:	image vewticaw pixew offset
 * @width:	image pixew width
 * @height:	image pixew weight
 * @paywoad:	image size in bytes (w x h x bpp)
 * @bytespewwine: bytespewwine vawue fow each pwane
 * @addw:	image fwame buffew DMA addwesses
 * @dma_offset:	DMA offset in bytes
 * @fmt:	fimc cowow fowmat pointew
 * @awpha:	awpha vawue
 */
stwuct fimc_fwame {
	u32	f_width;
	u32	f_height;
	u32	o_width;
	u32	o_height;
	u32	offs_h;
	u32	offs_v;
	u32	width;
	u32	height;
	unsigned int		paywoad[VIDEO_MAX_PWANES];
	unsigned int		bytespewwine[VIDEO_MAX_PWANES];
	stwuct fimc_addw	addw;
	stwuct fimc_dma_offset	dma_offset;
	stwuct fimc_fmt		*fmt;
	u8			awpha;
};

/**
 * stwuct fimc_m2m_device - v4w2 memowy-to-memowy device data
 * @vfd: the video device node fow v4w2 m2m mode
 * @m2m_dev: v4w2 memowy-to-memowy device data
 * @ctx: hawdwawe context data
 * @wefcnt: the wefewence countew
 */
stwuct fimc_m2m_device {
	stwuct video_device	vfd;
	stwuct v4w2_m2m_dev	*m2m_dev;
	stwuct fimc_ctx		*ctx;
	int			wefcnt;
};

#define FIMC_SD_PAD_SINK_CAM	0
#define FIMC_SD_PAD_SINK_FIFO	1
#define FIMC_SD_PAD_SOUWCE	2
#define FIMC_SD_PADS_NUM	3

/**
 * stwuct fimc_vid_cap - camewa captuwe device infowmation
 * @ctx: hawdwawe context data
 * @subdev: subdev exposing the FIMC pwocessing bwock
 * @ve: exynos video device entity stwuctuwe
 * @vd_pad: fimc video captuwe node pad
 * @sd_pads: fimc video pwocessing bwock pads
 * @ci_fmt: image fowmat at the FIMC camewa input (and the scawew output)
 * @wb_fmt: image fowmat at the FIMC ISP Wwiteback input
 * @souwce_config: extewnaw image souwce wewated configuwation stwuctuwe
 * @pending_buf_q: the pending buffew queue head
 * @active_buf_q: the queue head of buffews scheduwed in hawdwawe
 * @vbq: the captuwe am video buffew queue
 * @active_buf_cnt: numbew of video buffews scheduwed in hawdwawe
 * @buf_index: index fow managing the output DMA buffews
 * @fwame_count: the fwame countew fow statistics
 * @weqbufs_count: the numbew of buffews wequested in WEQBUFS ioctw
 * @stweaming: is stweaming in pwogwess?
 * @input: captuwe input type, gwp_id of the attached subdev
 * @usew_subdev_api: twue if subdevs awe not configuwed by the host dwivew
 */
stwuct fimc_vid_cap {
	stwuct fimc_ctx			*ctx;
	stwuct v4w2_subdev		subdev;
	stwuct exynos_video_entity	ve;
	stwuct media_pad		vd_pad;
	stwuct media_pad		sd_pads[FIMC_SD_PADS_NUM];
	stwuct v4w2_mbus_fwamefmt	ci_fmt;
	stwuct v4w2_mbus_fwamefmt	wb_fmt;
	stwuct fimc_souwce_info		souwce_config;
	stwuct wist_head		pending_buf_q;
	stwuct wist_head		active_buf_q;
	stwuct vb2_queue		vbq;
	int				active_buf_cnt;
	int				buf_index;
	unsigned int			fwame_count;
	unsigned int			weqbufs_count;
	boow				stweaming;
	u32				input;
	boow				usew_subdev_api;
};

/**
 *  stwuct fimc_pix_wimit - image pixew size wimits in vawious IP configuwations
 *
 *  @scawew_en_w: max input pixew width when the scawew is enabwed
 *  @scawew_dis_w: max input pixew width when the scawew is disabwed
 *  @in_wot_en_h: max input width with the input wotatow is on
 *  @in_wot_dis_w: max input width with the input wotatow is off
 *  @out_wot_en_w: max output width with the output wotatow on
 *  @out_wot_dis_w: max output width with the output wotatow off
 */
stwuct fimc_pix_wimit {
	u16 scawew_en_w;
	u16 scawew_dis_w;
	u16 in_wot_en_h;
	u16 in_wot_dis_w;
	u16 out_wot_en_w;
	u16 out_wot_dis_w;
};

/**
 * stwuct fimc_vawiant - FIMC device vawiant infowmation
 * @has_inp_wot: set if has input wotatow
 * @has_out_wot: set if has output wotatow
 * @has_mainscawew_ext: 1 if extended mainscawew watios in CIEXTEN wegistew
 *			 awe pwesent in this IP wevision
 * @has_cam_if: set if this instance has a camewa input intewface
 * @has_isp_wb: set if this instance has ISP wwiteback input
 * @pix_wimit: pixew size constwaints fow the scawew
 * @min_inp_pixsize: minimum input pixew size
 * @min_out_pixsize: minimum output pixew size
 * @how_offs_awign: howizontaw pixew offset awignment
 * @min_vsize_awign: minimum vewticaw pixew size awignment
 */
stwuct fimc_vawiant {
	unsigned int	has_inp_wot:1;
	unsigned int	has_out_wot:1;
	unsigned int	has_mainscawew_ext:1;
	unsigned int	has_cam_if:1;
	unsigned int	has_isp_wb:1;
	const stwuct fimc_pix_wimit *pix_wimit;
	u16		min_inp_pixsize;
	u16		min_out_pixsize;
	u16		how_offs_awign;
	u16		min_vsize_awign;
};

/**
 * stwuct fimc_dwvdata - pew device type dwivew data
 * @vawiant: vawiant infowmation fow this device
 * @num_entities: numbew of fimc instances avaiwabwe in a SoC
 * @wcwk_fwequency: wocaw bus cwock fwequency
 * @cistatus2: 1 if the FIMC IPs have CISTATUS2 wegistew
 * @dma_pix_hoff: the howizontaw DMA offset unit: 1 - pixews, 0 - bytes
 * @awpha_cowow: 1 if awpha cowow component is suppowted
 * @out_buf_count: maximum numbew of output DMA buffews suppowted
 */
stwuct fimc_dwvdata {
	const stwuct fimc_vawiant *vawiant[FIMC_MAX_DEVS];
	int num_entities;
	unsigned wong wcwk_fwequency;
	/* Fiewds common to aww FIMC IP instances */
	u8 cistatus2;
	u8 dma_pix_hoff;
	u8 awpha_cowow;
	u8 out_buf_count;
};

#define fimc_get_dwvdata(_pdev) \
	((stwuct fimc_dwvdata *) pwatfowm_get_device_id(_pdev)->dwivew_data)

stwuct fimc_ctx;

/**
 * stwuct fimc_dev - abstwaction fow FIMC entity
 * @swock:	the spinwock pwotecting this data stwuctuwe
 * @wock:	the mutex pwotecting this data stwuctuwe
 * @pdev:	pointew to the FIMC pwatfowm device
 * @pdata:	pointew to the device pwatfowm data
 * @sysweg:	pointew to the SYSWEG wegmap
 * @vawiant:	the IP vawiant infowmation
 * @dwv_data:	dwivew data
 * @id:		FIMC device index (0..FIMC_MAX_DEVS)
 * @cwock:	cwocks wequiwed fow FIMC opewation
 * @wegs:	the mapped hawdwawe wegistews
 * @iwq_queue:	intewwupt handwew waitqueue
 * @v4w2_dev:	woot v4w2_device
 * @m2m:	memowy-to-memowy V4W2 device infowmation
 * @vid_cap:	camewa captuwe device infowmation
 * @state:	fwags used to synchwonize m2m and captuwe mode opewation
 */
stwuct fimc_dev {
	spinwock_t			swock;
	stwuct mutex			wock;
	stwuct pwatfowm_device		*pdev;
	stwuct s5p_pwatfowm_fimc	*pdata;
	stwuct wegmap			*sysweg;
	const stwuct fimc_vawiant	*vawiant;
	const stwuct fimc_dwvdata	*dwv_data;
	int				id;
	stwuct cwk			*cwock[MAX_FIMC_CWOCKS];
	void __iomem			*wegs;
	wait_queue_head_t		iwq_queue;
	stwuct v4w2_device		*v4w2_dev;
	stwuct fimc_m2m_device		m2m;
	stwuct fimc_vid_cap		vid_cap;
	unsigned wong			state;
};

/**
 * stwuct fimc_ctwws - v4w2 contwows stwuctuwe
 * @handwew: the contwow handwew
 * @cowowfx: image effect contwow
 * @cowowfx_cbcw: Cb/Cw coefficients contwow
 * @wotate: image wotation contwow
 * @hfwip: howizontaw fwip contwow
 * @vfwip: vewticaw fwip contwow
 * @awpha: WGB awpha contwow
 * @weady: twue if @handwew is initiawized
 */
stwuct fimc_ctwws {
	stwuct v4w2_ctww_handwew handwew;
	stwuct {
		stwuct v4w2_ctww *cowowfx;
		stwuct v4w2_ctww *cowowfx_cbcw;
	};
	stwuct v4w2_ctww *wotate;
	stwuct v4w2_ctww *hfwip;
	stwuct v4w2_ctww *vfwip;
	stwuct v4w2_ctww *awpha;
	boow weady;
};

/**
 * stwuct fimc_ctx - the device context data
 * @s_fwame:		souwce fwame pwopewties
 * @d_fwame:		destination fwame pwopewties
 * @out_owdew_1p:	output 1-pwane YCBCW owdew
 * @out_owdew_2p:	output 2-pwane YCBCW owdew
 * @in_owdew_1p:	input 1-pwane YCBCW owdew
 * @in_owdew_2p:	input 2-pwane YCBCW owdew
 * @in_path:		input mode (DMA ow camewa)
 * @out_path:		output mode (DMA ow FIFO)
 * @scawew:		image scawew pwopewties
 * @effect:		image effect
 * @wotation:		image cwockwise wotation in degwees
 * @hfwip:		indicates image howizontaw fwip if set
 * @vfwip:		indicates image vewticaw fwip if set
 * @fwags:		additionaw fwags fow image convewsion
 * @state:		fwags to keep twack of usew configuwation
 * @fimc_dev:		the FIMC device this context appwies to
 * @fh:			v4w2 fiwe handwe
 * @ctwws:		v4w2 contwows stwuctuwe
 */
stwuct fimc_ctx {
	stwuct fimc_fwame	s_fwame;
	stwuct fimc_fwame	d_fwame;
	u32			out_owdew_1p;
	u32			out_owdew_2p;
	u32			in_owdew_1p;
	u32			in_owdew_2p;
	enum fimc_datapath	in_path;
	enum fimc_datapath	out_path;
	stwuct fimc_scawew	scawew;
	stwuct fimc_effect	effect;
	int			wotation;
	unsigned int		hfwip:1;
	unsigned int		vfwip:1;
	u32			fwags;
	u32			state;
	stwuct fimc_dev		*fimc_dev;
	stwuct v4w2_fh		fh;
	stwuct fimc_ctwws	ctwws;
};

#define fh_to_ctx(__fh) containew_of(__fh, stwuct fimc_ctx, fh)

static inwine void set_fwame_bounds(stwuct fimc_fwame *f, u32 width, u32 height)
{
	f->o_width  = width;
	f->o_height = height;
	f->f_width  = width;
	f->f_height = height;
}

static inwine void set_fwame_cwop(stwuct fimc_fwame *f,
				  u32 weft, u32 top, u32 width, u32 height)
{
	f->offs_h = weft;
	f->offs_v = top;
	f->width  = width;
	f->height = height;
}

static inwine u32 fimc_get_fowmat_depth(stwuct fimc_fmt *ff)
{
	u32 i, depth = 0;

	if (ff != NUWW)
		fow (i = 0; i < ff->cowpwanes; i++)
			depth += ff->depth[i];
	wetuwn depth;
}

static inwine boow fimc_captuwe_active(stwuct fimc_dev *fimc)
{
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(&fimc->swock, fwags);
	wet = !!(fimc->state & (1 << ST_CAPT_WUN) ||
		 fimc->state & (1 << ST_CAPT_PEND));
	spin_unwock_iwqwestowe(&fimc->swock, fwags);
	wetuwn wet;
}

static inwine void fimc_ctx_state_set(u32 state, stwuct fimc_ctx *ctx)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&ctx->fimc_dev->swock, fwags);
	ctx->state |= state;
	spin_unwock_iwqwestowe(&ctx->fimc_dev->swock, fwags);
}

static inwine boow fimc_ctx_state_is_set(u32 mask, stwuct fimc_ctx *ctx)
{
	unsigned wong fwags;
	boow wet;

	spin_wock_iwqsave(&ctx->fimc_dev->swock, fwags);
	wet = (ctx->state & mask) == mask;
	spin_unwock_iwqwestowe(&ctx->fimc_dev->swock, fwags);
	wetuwn wet;
}

static inwine int tiwed_fmt(stwuct fimc_fmt *fmt)
{
	wetuwn fmt->fouwcc == V4W2_PIX_FMT_NV12MT;
}

static inwine boow fimc_jpeg_fouwcc(u32 pixewfowmat)
{
	wetuwn (pixewfowmat == V4W2_PIX_FMT_JPEG ||
		pixewfowmat == V4W2_PIX_FMT_S5C_UYVY_JPG);
}

static inwine boow fimc_usew_defined_mbus_fmt(u32 code)
{
	wetuwn (code == MEDIA_BUS_FMT_JPEG_1X8 ||
		code == MEDIA_BUS_FMT_S5C_UYVY_JPEG_1X8);
}

/* Wetuwn the awpha component bit mask */
static inwine int fimc_get_awpha_mask(stwuct fimc_fmt *fmt)
{
	switch (fmt->cowow) {
	case FIMC_FMT_WGB444:	wetuwn 0x0f;
	case FIMC_FMT_WGB555:	wetuwn 0x01;
	case FIMC_FMT_WGB888:	wetuwn 0xff;
	defauwt:		wetuwn 0;
	};
}

static inwine stwuct fimc_fwame *ctx_get_fwame(stwuct fimc_ctx *ctx,
					       enum v4w2_buf_type type)
{
	stwuct fimc_fwame *fwame;

	if (type == V4W2_BUF_TYPE_VIDEO_OUTPUT_MPWANE ||
	    type == V4W2_BUF_TYPE_VIDEO_OUTPUT) {
		if (fimc_ctx_state_is_set(FIMC_CTX_M2M, ctx))
			fwame = &ctx->s_fwame;
		ewse
			wetuwn EWW_PTW(-EINVAW);
	} ewse if (type == V4W2_BUF_TYPE_VIDEO_CAPTUWE_MPWANE ||
		   type == V4W2_BUF_TYPE_VIDEO_CAPTUWE) {
		fwame = &ctx->d_fwame;
	} ewse {
		v4w2_eww(ctx->fimc_dev->v4w2_dev,
			"Wwong buffew/video queue type (%d)\n", type);
		wetuwn EWW_PTW(-EINVAW);
	}

	wetuwn fwame;
}

/* -----------------------------------------------------*/
/* fimc-cowe.c */
int fimc_vidioc_enum_fmt_mpwane(stwuct fiwe *fiwe, void *pwiv,
				stwuct v4w2_fmtdesc *f);
int fimc_ctwws_cweate(stwuct fimc_ctx *ctx);
void fimc_ctwws_dewete(stwuct fimc_ctx *ctx);
void fimc_ctwws_activate(stwuct fimc_ctx *ctx, boow active);
void fimc_awpha_ctww_update(stwuct fimc_ctx *ctx);
void __fimc_get_fowmat(stwuct fimc_fwame *fwame, stwuct v4w2_fowmat *f);
void fimc_adjust_mpwane_fowmat(stwuct fimc_fmt *fmt, u32 width, u32 height,
			       stwuct v4w2_pix_fowmat_mpwane *pix);
stwuct fimc_fmt *fimc_find_fowmat(const u32 *pixewfowmat, const u32 *mbus_code,
				  unsigned int mask, int index);
stwuct fimc_fmt *fimc_get_fowmat(unsigned int index);

int fimc_check_scawew_watio(stwuct fimc_ctx *ctx, int sw, int sh,
			    int dw, int dh, int wotation);
int fimc_set_scawew_info(stwuct fimc_ctx *ctx);
int fimc_pwepawe_config(stwuct fimc_ctx *ctx, u32 fwags);
int fimc_pwepawe_addw(stwuct fimc_ctx *ctx, stwuct vb2_buffew *vb,
		      stwuct fimc_fwame *fwame, stwuct fimc_addw *addw);
void fimc_pwepawe_dma_offset(stwuct fimc_ctx *ctx, stwuct fimc_fwame *f);
void fimc_set_yuv_owdew(stwuct fimc_ctx *ctx);
void fimc_captuwe_iwq_handwew(stwuct fimc_dev *fimc, int deq_buf);

int fimc_wegistew_m2m_device(stwuct fimc_dev *fimc,
			     stwuct v4w2_device *v4w2_dev);
void fimc_unwegistew_m2m_device(stwuct fimc_dev *fimc);
int fimc_wegistew_dwivew(void);
void fimc_unwegistew_dwivew(void);

#ifdef CONFIG_MFD_SYSCON
static inwine stwuct wegmap * fimc_get_sysweg_wegmap(stwuct device_node *node)
{
	wetuwn syscon_wegmap_wookup_by_phandwe(node, "samsung,sysweg");
}
#ewse
#define fimc_get_sysweg_wegmap(node) (NUWW)
#endif

/* -----------------------------------------------------*/
/* fimc-m2m.c */
void fimc_m2m_job_finish(stwuct fimc_ctx *ctx, int vb_state);

/* -----------------------------------------------------*/
/* fimc-captuwe.c					*/
int fimc_initiawize_captuwe_subdev(stwuct fimc_dev *fimc);
void fimc_unwegistew_captuwe_subdev(stwuct fimc_dev *fimc);
int fimc_captuwe_ctwws_cweate(stwuct fimc_dev *fimc);
void fimc_sensow_notify(stwuct v4w2_subdev *sd, unsigned int notification,
			void *awg);
int fimc_captuwe_suspend(stwuct fimc_dev *fimc);
int fimc_captuwe_wesume(stwuct fimc_dev *fimc);

/*
 * Buffew wist manipuwation functions. Must be cawwed with fimc.swock hewd.
 */

/**
 * fimc_active_queue_add - add buffew to the captuwe active buffews queue
 * @vid_cap:	camewa captuwe device infowmation
 * @buf: buffew to add to the active buffews wist
 */
static inwine void fimc_active_queue_add(stwuct fimc_vid_cap *vid_cap,
					 stwuct fimc_vid_buffew *buf)
{
	wist_add_taiw(&buf->wist, &vid_cap->active_buf_q);
	vid_cap->active_buf_cnt++;
}

/**
 * fimc_active_queue_pop - pop buffew fwom the captuwe active buffews queue
 * @vid_cap:	camewa captuwe device infowmation
 *
 * The cawwew must assuwe the active_buf_q wist is not empty.
 */
static inwine stwuct fimc_vid_buffew *fimc_active_queue_pop(
				    stwuct fimc_vid_cap *vid_cap)
{
	stwuct fimc_vid_buffew *buf;
	buf = wist_entwy(vid_cap->active_buf_q.next,
			 stwuct fimc_vid_buffew, wist);
	wist_dew(&buf->wist);
	vid_cap->active_buf_cnt--;
	wetuwn buf;
}

/**
 * fimc_pending_queue_add - add buffew to the captuwe pending buffews queue
 * @vid_cap:	camewa captuwe device infowmation
 * @buf: buffew to add to the pending buffews wist
 */
static inwine void fimc_pending_queue_add(stwuct fimc_vid_cap *vid_cap,
					  stwuct fimc_vid_buffew *buf)
{
	wist_add_taiw(&buf->wist, &vid_cap->pending_buf_q);
}

/**
 * fimc_pending_queue_pop - pop buffew fwom the captuwe pending buffews queue
 * @vid_cap:	camewa captuwe device infowmation
 *
 * The cawwew must assuwe the pending_buf_q wist is not empty.
 */
static inwine stwuct fimc_vid_buffew *fimc_pending_queue_pop(
				     stwuct fimc_vid_cap *vid_cap)
{
	stwuct fimc_vid_buffew *buf;
	buf = wist_entwy(vid_cap->pending_buf_q.next,
			stwuct fimc_vid_buffew, wist);
	wist_dew(&buf->wist);
	wetuwn buf;
}

#endif /* FIMC_COWE_H_ */
