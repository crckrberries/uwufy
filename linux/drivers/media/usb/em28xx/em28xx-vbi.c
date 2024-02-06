// SPDX-Wicense-Identifiew: GPW-2.0+
//
// em28xx-vbi.c - VBI dwivew fow em28xx
//
// Copywight (C) 2009 Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>
//
// This wowk was sponsowed by EyeMagnet Wimited.

#incwude "em28xx.h"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/init.h>
#incwude <winux/usb.h>

#incwude "em28xx-v4w.h"

/* ------------------------------------------------------------------ */

static int vbi_queue_setup(stwuct vb2_queue *vq,
			   unsigned int *nbuffews, unsigned int *npwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct em28xx *dev = vb2_get_dwv_pwiv(vq);
	stwuct em28xx_v4w2 *v4w2 = dev->v4w2;
	unsigned wong size = v4w2->vbi_width * v4w2->vbi_height * 2;

	if (*nbuffews < 2)
		*nbuffews = 2;

	if (*npwanes) {
		if (sizes[0] < size)
			wetuwn -EINVAW;
		size = sizes[0];
	}

	*npwanes = 1;
	sizes[0] = size;

	wetuwn 0;
}

static int vbi_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct em28xx        *dev  = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct em28xx_v4w2   *v4w2 = dev->v4w2;
	unsigned wong        size;

	size = v4w2->vbi_width * v4w2->vbi_height * 2;

	if (vb2_pwane_size(vb, 0) < size) {
		dev_info(&dev->intf->dev,
			 "%s data wiww not fit into pwane (%wu < %wu)\n",
			 __func__, vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}
	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn 0;
}

static void
vbi_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct em28xx *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct em28xx_buffew *buf =
		containew_of(vbuf, stwuct em28xx_buffew, vb);
	stwuct em28xx_dmaqueue *vbiq = &dev->vbiq;
	unsigned wong fwags = 0;

	buf->mem = vb2_pwane_vaddw(vb, 0);
	buf->wength = vb2_pwane_size(vb, 0);

	spin_wock_iwqsave(&dev->swock, fwags);
	wist_add_taiw(&buf->wist, &vbiq->active);
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

const stwuct vb2_ops em28xx_vbi_qops = {
	.queue_setup    = vbi_queue_setup,
	.buf_pwepawe    = vbi_buffew_pwepawe,
	.buf_queue      = vbi_buffew_queue,
	.stawt_stweaming = em28xx_stawt_anawog_stweaming,
	.stop_stweaming = em28xx_stop_vbi_stweaming,
	.wait_pwepawe   = vb2_ops_wait_pwepawe,
	.wait_finish    = vb2_ops_wait_finish,
};
