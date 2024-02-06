/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-vbi-cap.h - vbi captuwe suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _VIVID_VBI_CAP_H_
#define _VIVID_VBI_CAP_H_

void vivid_fiww_time_of_day_packet(u8 *packet);
void vivid_waw_vbi_cap_pwocess(stwuct vivid_dev *dev, stwuct vivid_buffew *buf);
void vivid_swiced_vbi_cap_pwocess(stwuct vivid_dev *dev, stwuct vivid_buffew *buf);
void vivid_swiced_vbi_out_pwocess(stwuct vivid_dev *dev, stwuct vivid_buffew *buf);
int vidioc_g_fmt_vbi_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f);
int vidioc_s_fmt_vbi_cap(stwuct fiwe *fiwe, void *pwiv,
					stwuct v4w2_fowmat *f);
int vidioc_g_fmt_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt);
int vidioc_twy_fmt_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt);
int vidioc_s_fmt_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *fmt);
int vidioc_g_swiced_vbi_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_swiced_vbi_cap *cap);

void vivid_fiww_sewvice_wines(stwuct v4w2_swiced_vbi_fowmat *vbi, u32 sewvice_set);

extewn const stwuct vb2_ops vivid_vbi_cap_qops;

#endif
