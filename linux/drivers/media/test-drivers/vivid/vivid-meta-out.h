/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-meta-out.h - meta output suppowt functions.
 */
#ifndef _VIVID_META_OUT_H_
#define _VIVID_META_OUT_H_

stwuct vivid_meta_out_buf {
	u16	bwightness;
	u16	contwast;
	u16	satuwation;
	s16	hue;
};

void vivid_meta_out_pwocess(stwuct vivid_dev *dev, stwuct vivid_buffew *buf);
int vidioc_enum_fmt_meta_out(stwuct fiwe *fiwe, void  *pwiv,
			     stwuct v4w2_fmtdesc *f);
int vidioc_g_fmt_meta_out(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_fowmat *f);
int vidioc_s_fmt_meta_out(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_fowmat *f);

extewn const stwuct vb2_ops vivid_meta_out_qops;

#endif
