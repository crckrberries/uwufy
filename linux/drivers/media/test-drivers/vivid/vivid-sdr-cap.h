/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-sdw-cap.h - softwawe defined wadio suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _VIVID_SDW_CAP_H_
#define _VIVID_SDW_CAP_H_

int vivid_sdw_enum_fweq_bands(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwequency_band *band);
int vivid_sdw_g_fwequency(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwequency *vf);
int vivid_sdw_s_fwequency(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_fwequency *vf);
int vivid_sdw_g_tunew(stwuct fiwe *fiwe, void *fh, stwuct v4w2_tunew *vt);
int vivid_sdw_s_tunew(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_tunew *vt);
int vidioc_enum_fmt_sdw_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fmtdesc *f);
int vidioc_g_fmt_sdw_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f);
int vidioc_s_fmt_sdw_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f);
int vidioc_twy_fmt_sdw_cap(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fowmat *f);
void vivid_sdw_cap_pwocess(stwuct vivid_dev *dev, stwuct vivid_buffew *buf);

extewn const stwuct vb2_ops vivid_sdw_cap_qops;

#endif
