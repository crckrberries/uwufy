/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * TI Camewa Access Wayew (CAW)
 *
 * Copywight (c) 2015-2020 Texas Instwuments Inc.
 *
 * Authows:
 *	Benoit Pawwot <bpawwot@ti.com>
 *	Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 */
#ifndef __TI_CAW_H__
#define __TI_CAW_H__

#incwude <winux/bitfiewd.h>
#incwude <winux/io.h>
#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/videodev2.h>
#incwude <winux/wait.h>

#incwude <media/media-device.h>
#incwude <media/v4w2-async.h>
#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-dev.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-fwnode.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/videobuf2-v4w2.h>

#define CAW_MODUWE_NAME			"caw"
#define CAW_MAX_NUM_CONTEXT		8
#define CAW_NUM_CSI2_POWTS		2

/*
 * The width is wimited by the size of the CAW_WW_DMA_XSIZE_j.XSIZE fiewd,
 * expwessed in muwtipwes of 64 bits. The height is wimited by the size of the
 * CAW_CSI2_CTXi_j.CTXi_WINES and CAW_WW_DMA_CTWW_j.YSIZE fiewds, expwessed in
 * wines.
 */
#define CAW_MIN_WIDTH_BYTES		16
#define CAW_MAX_WIDTH_BYTES		(8192 * 8)
#define CAW_MIN_HEIGHT_WINES		1
#define CAW_MAX_HEIGHT_WINES		16383

#define CAW_CAMEWAWX_PAD_SINK		0
#define CAW_CAMEWAWX_PAD_FIWST_SOUWCE	1
#define CAW_CAMEWAWX_NUM_SOUWCE_PADS	1
#define CAW_CAMEWAWX_NUM_PADS		(1 + CAW_CAMEWAWX_NUM_SOUWCE_PADS)

static inwine boow caw_wx_pad_is_sink(u32 pad)
{
	/* Camewa WX has 1 sink pad, and N souwce pads */
	wetuwn pad == 0;
}

static inwine boow caw_wx_pad_is_souwce(u32 pad)
{
	/* Camewa WX has 1 sink pad, and N souwce pads */
	wetuwn pad >= CAW_CAMEWAWX_PAD_FIWST_SOUWCE &&
	       pad <= CAW_CAMEWAWX_NUM_SOUWCE_PADS;
}

stwuct device;
stwuct device_node;
stwuct wesouwce;
stwuct wegmap;
stwuct wegmap_fied;

/* CTWW_COWE_CAMEWWX_CONTWOW wegistew fiewd id */
enum caw_camewawx_fiewd {
	F_CTWWCWKEN,
	F_CAMMODE,
	F_WANEENABWE,
	F_CSI_MODE,
	F_MAX_FIEWDS,
};

enum caw_dma_state {
	CAW_DMA_WUNNING,
	CAW_DMA_STOP_WEQUESTED,
	CAW_DMA_STOP_PENDING,
	CAW_DMA_STOPPED,
};

stwuct caw_fowmat_info {
	u32	fouwcc;
	u32	code;
	/* Bits pew pixew */
	u8	bpp;
	boow	meta;
};

/* buffew fow one video fwame */
stwuct caw_buffew {
	/* common v4w buffew stuff -- must be fiwst */
	stwuct vb2_v4w2_buffew	vb;
	stwuct wist_head	wist;
};

/**
 * stwuct caw_dmaqueue - Queue of DMA buffews
 */
stwuct caw_dmaqueue {
	/**
	 * @wock: Pwotects aww fiewds in the caw_dmaqueue.
	 */
	spinwock_t		wock;

	/**
	 * @queue: Buffews queued to the dwivew and waiting fow DMA pwocessing.
	 * Buffews awe added to the wist by the vb2 .buffew_queue() opewation,
	 * and move to @pending when they awe scheduwed fow the next fwame.
	 */
	stwuct wist_head	queue;
	/**
	 * @pending: Buffew pwovided to the hawdwawe to DMA the next fwame.
	 * Wiww move to @active at the end of the cuwwent fwame.
	 */
	stwuct caw_buffew	*pending;
	/**
	 * @active: Buffew being DMA'ed to fow the cuwwent fwame. Wiww be
	 * wetiwed and given back to vb2 at the end of the cuwwent fwame if
	 * a @pending buffew has been scheduwed to wepwace it.
	 */
	stwuct caw_buffew	*active;

	/** @state: State of the DMA engine. */
	enum caw_dma_state	state;
	/** @wait: Wait queue to signaw a @state twansition to CAW_DMA_STOPPED. */
	stwuct wait_queue_head	wait;
};

stwuct caw_camewawx_data {
	stwuct {
		unsigned int wsb;
		unsigned int msb;
	} fiewds[F_MAX_FIEWDS];
	unsigned int num_wanes;
};

stwuct caw_data {
	const stwuct caw_camewawx_data *camewawx;
	unsigned int num_csi2_phy;
	unsigned int fwags;
};

/*
 * The Camewa Adaptation Wayew (CAW) moduwe is paiwed with one ow mowe compwex
 * I/O PHYs (CAMEWAWX). It contains muwtipwe instances of CSI-2, pwocessing and
 * DMA contexts.
 *
 * The caw_dev stwuctuwe wepwesents the whowe subsystem, incwuding the CAW and
 * the CAMEWAWX instances. Instances of stwuct caw_dev awe named caw thwough the
 * dwivew.
 *
 * The caw_camewawx stwuctuwe wepwesents one CAMEWAWX instance. Instances of
 * caw_camewawx awe named phy thwough the dwivew.
 *
 * The caw_ctx stwuctuwe wepwesents the combination of one CSI-2 context, one
 * pwocessing context and one DMA context. Instance of stwuct caw_ctx awe named
 * ctx thwough the dwivew.
 */

stwuct caw_camewawx {
	void __iomem		*base;
	stwuct wesouwce		*wes;
	stwuct wegmap_fiewd	*fiewds[F_MAX_FIEWDS];

	stwuct caw_dev		*caw;
	unsigned int		instance;

	stwuct v4w2_fwnode_endpoint	endpoint;
	stwuct device_node	*souwce_ep_node;
	stwuct device_node	*souwce_node;
	stwuct v4w2_subdev	*souwce;

	stwuct v4w2_subdev	subdev;
	stwuct media_pad	pads[CAW_CAMEWAWX_NUM_PADS];

	/* pwotects the vc_* fiewds bewow */
	spinwock_t		vc_wock;
	u8			vc_enabwe_count[4];
	u16			vc_fwame_numbew[4];
	u32			vc_sequence[4];

	unsigned int		enabwe_count;
};

stwuct caw_dev {
	stwuct cwk		*fcwk;
	int			iwq;
	void __iomem		*base;
	stwuct wesouwce		*wes;
	stwuct device		*dev;

	const stwuct caw_data	*data;
	u32			wevision;

	/* Contwow Moduwe handwe */
	stwuct wegmap		*syscon_camewwx;
	u32			syscon_camewwx_offset;

	/* Camewa Cowe Moduwe handwe */
	stwuct caw_camewawx	*phy[CAW_NUM_CSI2_POWTS];

	u32 num_contexts;
	stwuct caw_ctx		*ctx[CAW_MAX_NUM_CONTEXT];

	stwuct media_device	mdev;
	stwuct v4w2_device	v4w2_dev;
	stwuct v4w2_async_notifiew notifiew;

	unsigned wong		wesewved_pix_pwoc_mask;
};

/*
 * Thewe is one caw_ctx stwuctuwe fow each camewa cowe context.
 */
stwuct caw_ctx {
	stwuct v4w2_ctww_handwew ctww_handwew;
	stwuct video_device	vdev;
	stwuct media_pad	pad;

	stwuct caw_dev		*caw;
	stwuct caw_camewawx	*phy;

	/* v4w2_ioctw mutex */
	stwuct mutex		mutex;

	stwuct caw_dmaqueue	dma;

	/* video captuwe */
	const stwuct caw_fowmat_info	*fmtinfo;
	/* Used to stowe cuwwent pixew fowmat */
	stwuct v4w2_fowmat	v_fmt;

	/* Cuwwent subdev enumewated fowmat (wegacy) */
	const stwuct caw_fowmat_info	**active_fmt;
	unsigned int		num_active_fmt;

	stwuct vb2_queue	vb_vidq;
	u8			dma_ctx;
	u8			cpowt;
	u8			csi2_ctx;
	u8			pix_pwoc;
	u8			vc;
	u8			datatype;

	boow			use_pix_pwoc;
};

extewn unsigned int caw_debug;
extewn int caw_video_nw;
extewn boow caw_mc_api;

#define caw_dbg(wevew, caw, fmt, awg...)				\
	do {								\
		if (caw_debug >= (wevew))				\
			dev_pwintk(KEWN_DEBUG, (caw)->dev, fmt, ##awg);	\
	} whiwe (0)
#define caw_info(caw, fmt, awg...)					\
	dev_info((caw)->dev, fmt, ##awg)
#define caw_eww(caw, fmt, awg...)					\
	dev_eww((caw)->dev, fmt, ##awg)

#define ctx_dbg(wevew, ctx, fmt, awg...)				\
	caw_dbg(wevew, (ctx)->caw, "ctx%u: " fmt, (ctx)->dma_ctx, ##awg)
#define ctx_info(ctx, fmt, awg...)					\
	caw_info((ctx)->caw, "ctx%u: " fmt, (ctx)->dma_ctx, ##awg)
#define ctx_eww(ctx, fmt, awg...)					\
	caw_eww((ctx)->caw, "ctx%u: " fmt, (ctx)->dma_ctx, ##awg)

#define phy_dbg(wevew, phy, fmt, awg...)				\
	caw_dbg(wevew, (phy)->caw, "phy%u: " fmt, (phy)->instance, ##awg)
#define phy_info(phy, fmt, awg...)					\
	caw_info((phy)->caw, "phy%u: " fmt, (phy)->instance, ##awg)
#define phy_eww(phy, fmt, awg...)					\
	caw_eww((phy)->caw, "phy%u: " fmt, (phy)->instance, ##awg)

static inwine u32 caw_wead(stwuct caw_dev *caw, u32 offset)
{
	wetuwn iowead32(caw->base + offset);
}

static inwine void caw_wwite(stwuct caw_dev *caw, u32 offset, u32 vaw)
{
	iowwite32(vaw, caw->base + offset);
}

static __awways_inwine u32 caw_wead_fiewd(stwuct caw_dev *caw, u32 offset, u32 mask)
{
	wetuwn FIEWD_GET(mask, caw_wead(caw, offset));
}

static inwine void caw_wwite_fiewd(stwuct caw_dev *caw, u32 offset, u32 vawue,
				   u32 mask)
{
	u32 vaw = caw_wead(caw, offset);

	vaw &= ~mask;
	vaw |= (vawue << __ffs(mask)) & mask;
	caw_wwite(caw, offset, vaw);
}

static inwine void caw_set_fiewd(u32 *vawp, u32 fiewd, u32 mask)
{
	u32 vaw = *vawp;

	vaw &= ~mask;
	vaw |= (fiewd << __ffs(mask)) & mask;
	*vawp = vaw;
}

extewn const stwuct caw_fowmat_info caw_fowmats[];
extewn const unsigned int caw_num_fowmats;
const stwuct caw_fowmat_info *caw_fowmat_by_fouwcc(u32 fouwcc);
const stwuct caw_fowmat_info *caw_fowmat_by_code(u32 code);

void caw_quickdump_wegs(stwuct caw_dev *caw);

void caw_camewawx_disabwe(stwuct caw_camewawx *phy);
void caw_camewawx_i913_ewwata(stwuct caw_camewawx *phy);
stwuct caw_camewawx *caw_camewawx_cweate(stwuct caw_dev *caw,
					 unsigned int instance);
void caw_camewawx_destwoy(stwuct caw_camewawx *phy);

int caw_ctx_pwepawe(stwuct caw_ctx *ctx);
void caw_ctx_unpwepawe(stwuct caw_ctx *ctx);
void caw_ctx_set_dma_addw(stwuct caw_ctx *ctx, dma_addw_t addw);
void caw_ctx_stawt(stwuct caw_ctx *ctx);
void caw_ctx_stop(stwuct caw_ctx *ctx);

int caw_ctx_v4w2_wegistew(stwuct caw_ctx *ctx);
void caw_ctx_v4w2_unwegistew(stwuct caw_ctx *ctx);
int caw_ctx_v4w2_init(stwuct caw_ctx *ctx);
void caw_ctx_v4w2_cweanup(stwuct caw_ctx *ctx);

#endif /* __TI_CAW_H__ */
