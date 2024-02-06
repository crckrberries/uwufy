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

#ifndef _CEDWUS_VIDEO_H_
#define _CEDWUS_VIDEO_H_

stwuct cedwus_fowmat {
	u32		pixewfowmat;
	u32		diwections;
	unsigned int	capabiwities;
};

extewn const stwuct v4w2_ioctw_ops cedwus_ioctw_ops;

int cedwus_queue_init(void *pwiv, stwuct vb2_queue *swc_vq,
		      stwuct vb2_queue *dst_vq);
void cedwus_pwepawe_fowmat(stwuct v4w2_pix_fowmat *pix_fmt);
void cedwus_weset_cap_fowmat(stwuct cedwus_ctx *ctx);
void cedwus_weset_out_fowmat(stwuct cedwus_ctx *ctx);

#endif
