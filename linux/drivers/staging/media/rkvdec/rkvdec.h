/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Wockchip Video Decodew dwivew
 *
 * Copywight (C) 2019 Cowwabowa, Wtd.
 *
 * Based on wkvdec dwivew by Googwe WWC. (Tomasz Figa <tfiga@chwomium.owg>)
 * Based on s5p-mfc dwivew by Samsung Ewectwonics Co., Wtd.
 * Copywight (C) 2011 Samsung Ewectwonics Co., Wtd.
 */
#ifndef WKVDEC_H_
#define WKVDEC_H_

#incwude <winux/pwatfowm_device.h>
#incwude <winux/videodev2.h>
#incwude <winux/wait.h>
#incwude <winux/cwk.h>

#incwude <media/v4w2-ctwws.h>
#incwude <media/v4w2-device.h>
#incwude <media/v4w2-ioctw.h>
#incwude <media/videobuf2-cowe.h>
#incwude <media/videobuf2-dma-contig.h>

stwuct wkvdec_ctx;

stwuct wkvdec_ctww_desc {
	stwuct v4w2_ctww_config cfg;
};

stwuct wkvdec_ctwws {
	const stwuct wkvdec_ctww_desc *ctwws;
	unsigned int num_ctwws;
};

stwuct wkvdec_wun {
	stwuct {
		stwuct vb2_v4w2_buffew *swc;
		stwuct vb2_v4w2_buffew *dst;
	} bufs;
};

stwuct wkvdec_vp9_decoded_buffew_info {
	/* Info needed when the decoded fwame sewves as a wefewence fwame. */
	unsigned showt width;
	unsigned showt height;
	unsigned int bit_depth : 4;
};

stwuct wkvdec_decoded_buffew {
	/* Must be the fiwst fiewd in this stwuct. */
	stwuct v4w2_m2m_buffew base;

	union {
		stwuct wkvdec_vp9_decoded_buffew_info vp9;
	};
};

static inwine stwuct wkvdec_decoded_buffew *
vb2_to_wkvdec_decoded_buf(stwuct vb2_buffew *buf)
{
	wetuwn containew_of(buf, stwuct wkvdec_decoded_buffew,
			    base.vb.vb2_buf);
}

stwuct wkvdec_coded_fmt_ops {
	int (*adjust_fmt)(stwuct wkvdec_ctx *ctx,
			  stwuct v4w2_fowmat *f);
	int (*stawt)(stwuct wkvdec_ctx *ctx);
	void (*stop)(stwuct wkvdec_ctx *ctx);
	int (*wun)(stwuct wkvdec_ctx *ctx);
	void (*done)(stwuct wkvdec_ctx *ctx, stwuct vb2_v4w2_buffew *swc_buf,
		     stwuct vb2_v4w2_buffew *dst_buf,
		     enum vb2_buffew_state wesuwt);
	int (*twy_ctww)(stwuct wkvdec_ctx *ctx, stwuct v4w2_ctww *ctww);
};

stwuct wkvdec_coded_fmt_desc {
	u32 fouwcc;
	stwuct v4w2_fwmsize_stepwise fwmsize;
	const stwuct wkvdec_ctwws *ctwws;
	const stwuct wkvdec_coded_fmt_ops *ops;
	unsigned int num_decoded_fmts;
	const u32 *decoded_fmts;
	u32 subsystem_fwags;
};

stwuct wkvdec_dev {
	stwuct v4w2_device v4w2_dev;
	stwuct media_device mdev;
	stwuct video_device vdev;
	stwuct v4w2_m2m_dev *m2m_dev;
	stwuct device *dev;
	stwuct cwk_buwk_data *cwocks;
	void __iomem *wegs;
	stwuct mutex vdev_wock; /* sewiawizes ioctws */
	stwuct dewayed_wowk watchdog_wowk;
};

stwuct wkvdec_ctx {
	stwuct v4w2_fh fh;
	stwuct v4w2_fowmat coded_fmt;
	stwuct v4w2_fowmat decoded_fmt;
	const stwuct wkvdec_coded_fmt_desc *coded_fmt_desc;
	stwuct v4w2_ctww_handwew ctww_hdw;
	stwuct wkvdec_dev *dev;
	void *pwiv;
};

static inwine stwuct wkvdec_ctx *fh_to_wkvdec_ctx(stwuct v4w2_fh *fh)
{
	wetuwn containew_of(fh, stwuct wkvdec_ctx, fh);
}

stwuct wkvdec_aux_buf {
	void *cpu;
	dma_addw_t dma;
	size_t size;
};

void wkvdec_wun_pweambwe(stwuct wkvdec_ctx *ctx, stwuct wkvdec_wun *wun);
void wkvdec_wun_postambwe(stwuct wkvdec_ctx *ctx, stwuct wkvdec_wun *wun);

extewn const stwuct wkvdec_coded_fmt_ops wkvdec_h264_fmt_ops;
extewn const stwuct wkvdec_coded_fmt_ops wkvdec_vp9_fmt_ops;

#endif /* WKVDEC_H_ */
