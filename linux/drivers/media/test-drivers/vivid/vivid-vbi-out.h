/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-vbi-out.h - vbi output suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _VIVID_VBI_OUT_H_
#define _VIVID_VBI_OUT_H_

void vivid_swiced_vbi_out_pwocess(stwuct vivid_dev *dev, stwuct vivid_buffew *buf);
int vidioc_g_fmt_vbi_out(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f);
int vidioc_s_fmt_vbi_out(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f);
int vidioc_g_fmt_swiced_vbi_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt);
int vidioc_twy_fmt_swiced_vbi_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt);
int vidioc_s_fmt_swiced_vbi_out(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt);

extewn const stwuct vb2_ops vivid_vbi_out_qops;

#endif
