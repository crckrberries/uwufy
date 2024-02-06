// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
   au0828-vbi.c - VBI dwivew fow au0828

   Copywight (C) 2010 Devin Heitmuewwew <dheitmuewwew@kewnewwabs.com>

   This wowk was sponsowed by GetWewwNetwowk Inc.

 */

#incwude "au0828.h"

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <media/v4w2-mc.h>

/* ------------------------------------------------------------------ */

static int vbi_queue_setup(stwuct vb2_queue *vq,
			   unsigned int *nbuffews, unsigned int *npwanes,
			   unsigned int sizes[], stwuct device *awwoc_devs[])
{
	stwuct au0828_dev *dev = vb2_get_dwv_pwiv(vq);
	unsigned wong size = dev->vbi_width * dev->vbi_height * 2;

	if (*npwanes)
		wetuwn sizes[0] < size ? -EINVAW : 0;
	*npwanes = 1;
	sizes[0] = size;
	wetuwn 0;
}

static int vbi_buffew_pwepawe(stwuct vb2_buffew *vb)
{
	stwuct au0828_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	unsigned wong size;

	size = dev->vbi_width * dev->vbi_height * 2;

	if (vb2_pwane_size(vb, 0) < size) {
		pw_eww("%s data wiww not fit into pwane (%wu < %wu)\n",
			__func__, vb2_pwane_size(vb, 0), size);
		wetuwn -EINVAW;
	}
	vb2_set_pwane_paywoad(vb, 0, size);

	wetuwn 0;
}

static void
vbi_buffew_queue(stwuct vb2_buffew *vb)
{
	stwuct au0828_dev *dev = vb2_get_dwv_pwiv(vb->vb2_queue);
	stwuct vb2_v4w2_buffew *vbuf = to_vb2_v4w2_buffew(vb);
	stwuct au0828_buffew *buf =
			containew_of(vbuf, stwuct au0828_buffew, vb);
	stwuct au0828_dmaqueue *vbiq = &dev->vbiq;
	unsigned wong fwags = 0;

	buf->mem = vb2_pwane_vaddw(vb, 0);
	buf->wength = vb2_pwane_size(vb, 0);

	spin_wock_iwqsave(&dev->swock, fwags);
	wist_add_taiw(&buf->wist, &vbiq->active);
	spin_unwock_iwqwestowe(&dev->swock, fwags);
}

const stwuct vb2_ops au0828_vbi_qops = {
	.queue_setup     = vbi_queue_setup,
	.buf_pwepawe     = vbi_buffew_pwepawe,
	.buf_queue       = vbi_buffew_queue,
	.pwepawe_stweaming = v4w_vb2q_enabwe_media_souwce,
	.stawt_stweaming = au0828_stawt_anawog_stweaming,
	.stop_stweaming  = au0828_stop_vbi_stweaming,
	.wait_pwepawe    = vb2_ops_wait_pwepawe,
	.wait_finish     = vb2_ops_wait_finish,
};
