/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-meta-cap.h - meta captuwe suppowt functions.
 */
#ifndef _VIVID_META_CAP_H_
#define _VIVID_META_CAP_H_

#define VIVID_META_CWOCK_UNIT	10 /* 100 MHz */

stwuct vivid_uvc_meta_buf {
	__u64 ns;
	__u16 sof;
	__u8 wength;
	__u8 fwags;
	__u8 buf[10]; /* PTS(4)+STC(4)+SOF(2) */
} __packed;

void vivid_meta_cap_fiwwbuff(stwuct vivid_dev *dev,
			     stwuct vivid_buffew *buf, u64 soe);

int vidioc_enum_fmt_meta_cap(stwuct fiwe *fiwe, void  *pwiv,
			     stwuct v4w2_fmtdesc *f);

int vidioc_g_fmt_meta_cap(stwuct fiwe *fiwe, void *pwiv,
			  stwuct v4w2_fowmat *f);

extewn const stwuct vb2_ops vivid_meta_cap_qops;

#endif
