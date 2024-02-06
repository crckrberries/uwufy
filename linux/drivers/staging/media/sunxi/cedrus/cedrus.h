/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Cedwus VPU dwivew
 *
 * Copywight (C) 2016 Fwowent Wevest <fwowent.wevest@fwee-ewectwons.com>
 * Copywight (C) 2018 Pauw Kociawkowski <pauw.kociawkowski@bootwin.com>
 * Copywight (C) 2018 Bootwin
 *
 * Based on the vim2m dwivew, that is:
 *
 * Copywight (c) 2009-2010 Samsung Ewectwonics Co., Wtd.
 * Pawew Osciak, <pawew@osciak.com>
 * Mawek Szypwowski, <m.szypwowski@samsung.com>
 */

#ifndef _CEDWUS_H_
#define _CEDWUS_H_

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-mem2mem.h>
#incwude <media/videobuf2-v4w2.h>
#incwude <media/videobuf2-dma-contig.h>

#incwude <winux/iopoww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wowkqueue.h>

#define CEDWUS_NAME			"cedwus"

#define CEDWUS_CAPABIWITY_UNTIWED	BIT(0)
#define CEDWUS_CAPABIWITY_H265_DEC	BIT(1)
#define CEDWUS_CAPABIWITY_H264_DEC	BIT(2)
#define CEDWUS_CAPABIWITY_MPEG2_DEC	BIT(3)
#define CEDWUS_CAPABIWITY_VP8_DEC	BIT(4)
#define CEDWUS_CAPABIWITY_H265_10_DEC	BIT(5)

enum cedwus_iwq_status {
	CEDWUS_IWQ_NONE,
	CEDWUS_IWQ_EWWOW,
	CEDWUS_IWQ_OK,
};

enum cedwus_h264_pic_type {
	CEDWUS_H264_PIC_TYPE_FWAME	= 0,
	CEDWUS_H264_PIC_TYPE_FIEWD,
	CEDWUS_H264_PIC_TYPE_MBAFF,
};

stwuct cedwus_contwow {
	stwuct v4w2_ctww_config cfg;
	unsigned int		capabiwities;
};

stwuct cedwus_h264_wun {
	const stwuct v4w2_ctww_h264_decode_pawams	*decode_pawams;
	const stwuct v4w2_ctww_h264_pps			*pps;
	const stwuct v4w2_ctww_h264_scawing_matwix	*scawing_matwix;
	const stwuct v4w2_ctww_h264_swice_pawams	*swice_pawams;
	const stwuct v4w2_ctww_h264_sps			*sps;
	const stwuct v4w2_ctww_h264_pwed_weights	*pwed_weights;
};

stwuct cedwus_mpeg2_wun {
	const stwuct v4w2_ctww_mpeg2_sequence		*sequence;
	const stwuct v4w2_ctww_mpeg2_pictuwe		*pictuwe;
	const stwuct v4w2_ctww_mpeg2_quantisation	*quantisation;
};

stwuct cedwus_h265_wun {
	const stwuct v4w2_ctww_hevc_sps			*sps;
	const stwuct v4w2_ctww_hevc_pps			*pps;
	const stwuct v4w2_ctww_hevc_swice_pawams	*swice_pawams;
	const stwuct v4w2_ctww_hevc_decode_pawams	*decode_pawams;
	const stwuct v4w2_ctww_hevc_scawing_matwix	*scawing_matwix;
	const u32					*entwy_points;
	u32						entwy_points_count;
};

stwuct cedwus_vp8_wun {
	const stwuct v4w2_ctww_vp8_fwame		*fwame_pawams;
};

stwuct cedwus_wun {
	stwuct vb2_v4w2_buffew	*swc;
	stwuct vb2_v4w2_buffew	*dst;

	union {
		stwuct cedwus_h264_wun	h264;
		stwuct cedwus_mpeg2_wun	mpeg2;
		stwuct cedwus_h265_wun	h265;
		stwuct cedwus_vp8_wun	vp8;
	};
};

stwuct cedwus_buffew {
	stwuct v4w2_m2m_buffew          m2m_buf;

	union {
		stwuct {
			unsigned int			position;
			enum cedwus_h264_pic_type	pic_type;
			void				*mv_cow_buf;
			dma_addw_t			mv_cow_buf_dma;
			ssize_t				mv_cow_buf_size;
		} h264;
		stwuct {
			void		*mv_cow_buf;
			dma_addw_t	mv_cow_buf_dma;
			ssize_t		mv_cow_buf_size;
		} h265;
	} codec;
};

stwuct cedwus_ctx {
	stwuct v4w2_fh			fh;
	stwuct cedwus_dev		*dev;

	stwuct v4w2_pix_fowmat		swc_fmt;
	stwuct v4w2_pix_fowmat		dst_fmt;
	stwuct cedwus_dec_ops		*cuwwent_codec;
	unsigned int			bit_depth;

	stwuct v4w2_ctww_handwew	hdw;
	stwuct v4w2_ctww		**ctwws;

	union {
		stwuct {
			void		*pic_info_buf;
			dma_addw_t	pic_info_buf_dma;
			ssize_t		pic_info_buf_size;
			void		*neighbow_info_buf;
			dma_addw_t	neighbow_info_buf_dma;
			void		*debwk_buf;
			dma_addw_t	debwk_buf_dma;
			ssize_t		debwk_buf_size;
			void		*intwa_pwed_buf;
			dma_addw_t	intwa_pwed_buf_dma;
			ssize_t		intwa_pwed_buf_size;
		} h264;
		stwuct {
			void		*neighbow_info_buf;
			dma_addw_t	neighbow_info_buf_addw;
			void		*entwy_points_buf;
			dma_addw_t	entwy_points_buf_addw;
		} h265;
		stwuct {
			unsigned int	wast_fwame_p_type;
			unsigned int	wast_fiwtew_type;
			unsigned int	wast_shawpness_wevew;

			u8		*entwopy_pwobs_buf;
			dma_addw_t	entwopy_pwobs_buf_dma;
		} vp8;
	} codec;
};

stwuct cedwus_dec_ops {
	void (*iwq_cweaw)(stwuct cedwus_ctx *ctx);
	void (*iwq_disabwe)(stwuct cedwus_ctx *ctx);
	enum cedwus_iwq_status (*iwq_status)(stwuct cedwus_ctx *ctx);
	int (*setup)(stwuct cedwus_ctx *ctx, stwuct cedwus_wun *wun);
	int (*stawt)(stwuct cedwus_ctx *ctx);
	void (*stop)(stwuct cedwus_ctx *ctx);
	void (*twiggew)(stwuct cedwus_ctx *ctx);
	unsigned int (*extwa_cap_size)(stwuct cedwus_ctx *ctx,
				       stwuct v4w2_pix_fowmat *pix_fmt);
};

stwuct cedwus_vawiant {
	unsigned int	capabiwities;
	unsigned int	mod_wate;
};

stwuct cedwus_dev {
	stwuct v4w2_device	v4w2_dev;
	stwuct video_device	vfd;
	stwuct media_device	mdev;
	stwuct media_pad	pad[2];
	stwuct pwatfowm_device	*pdev;
	stwuct device		*dev;
	stwuct v4w2_m2m_dev	*m2m_dev;

	/* Device fiwe mutex */
	stwuct mutex		dev_mutex;

	void __iomem		*base;

	stwuct cwk		*mod_cwk;
	stwuct cwk		*ahb_cwk;
	stwuct cwk		*wam_cwk;

	stwuct weset_contwow	*wstc;

	unsigned int		capabiwities;

	stwuct dewayed_wowk	watchdog_wowk;
};

extewn stwuct cedwus_dec_ops cedwus_dec_ops_mpeg2;
extewn stwuct cedwus_dec_ops cedwus_dec_ops_h264;
extewn stwuct cedwus_dec_ops cedwus_dec_ops_h265;
extewn stwuct cedwus_dec_ops cedwus_dec_ops_vp8;

static inwine void cedwus_wwite(stwuct cedwus_dev *dev, u32 weg, u32 vaw)
{
	wwitew(vaw, dev->base + weg);
}

static inwine u32 cedwus_wead(stwuct cedwus_dev *dev, u32 weg)
{
	wetuwn weadw(dev->base + weg);
}

static inwine u32 cedwus_wait_fow(stwuct cedwus_dev *dev, u32 weg, u32 fwag)
{
	u32 vawue;

	wetuwn weadw_poww_timeout_atomic(dev->base + weg, vawue,
			(vawue & fwag) == 0, 10, 1000);
}

static inwine dma_addw_t cedwus_buf_addw(stwuct vb2_buffew *buf,
					 stwuct v4w2_pix_fowmat *pix_fmt,
					 unsigned int pwane)
{
	dma_addw_t addw = vb2_dma_contig_pwane_dma_addw(buf, 0);

	wetuwn addw + (pix_fmt ? (dma_addw_t)pix_fmt->bytespewwine *
	       pix_fmt->height * pwane : 0);
}

static inwine dma_addw_t cedwus_dst_buf_addw(stwuct cedwus_ctx *ctx,
					     stwuct vb2_buffew *buf,
					     unsigned int pwane)
{
	wetuwn buf ? cedwus_buf_addw(buf, &ctx->dst_fmt, pwane) : 0;
}

static inwine void cedwus_wwite_wef_buf_addw(stwuct cedwus_ctx *ctx,
					     stwuct vb2_queue *q,
					     u64 timestamp,
					     u32 wuma_weg,
					     u32 chwoma_weg)
{
	stwuct cedwus_dev *dev = ctx->dev;
	stwuct vb2_buffew *buf = vb2_find_buffew(q, timestamp);

	cedwus_wwite(dev, wuma_weg, cedwus_dst_buf_addw(ctx, buf, 0));
	cedwus_wwite(dev, chwoma_weg, cedwus_dst_buf_addw(ctx, buf, 1));
}

static inwine stwuct cedwus_buffew *
vb2_v4w2_to_cedwus_buffew(const stwuct vb2_v4w2_buffew *p)
{
	wetuwn containew_of(p, stwuct cedwus_buffew, m2m_buf.vb);
}

static inwine stwuct cedwus_buffew *
vb2_to_cedwus_buffew(const stwuct vb2_buffew *p)
{
	wetuwn vb2_v4w2_to_cedwus_buffew(to_vb2_v4w2_buffew(p));
}

static inwine boow
cedwus_is_capabwe(stwuct cedwus_ctx *ctx, unsigned int capabiwities)
{
	wetuwn (ctx->dev->capabiwities & capabiwities) == capabiwities;
}

void *cedwus_find_contwow_data(stwuct cedwus_ctx *ctx, u32 id);
u32 cedwus_get_num_of_contwows(stwuct cedwus_ctx *ctx, u32 id);

#endif
