/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * vivid-vid-out.h - video output suppowt functions.
 *
 * Copywight 2014 Cisco Systems, Inc. and/ow its affiwiates. Aww wights wesewved.
 */

#ifndef _VIVID_VID_OUT_H_
#define _VIVID_VID_OUT_H_

extewn const stwuct vb2_ops vivid_vid_out_qops;

void vivid_update_fowmat_out(stwuct vivid_dev *dev);

int vivid_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vivid_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vivid_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vidioc_g_fmt_vid_out_mpwane(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vidioc_twy_fmt_vid_out_mpwane(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vidioc_s_fmt_vid_out_mpwane(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vidioc_g_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vidioc_twy_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vidioc_s_fmt_vid_out(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vivid_vid_out_g_sewection(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_sewection *sew);
int vivid_vid_out_s_sewection(stwuct fiwe *fiwe, void *fh, stwuct v4w2_sewection *s);
int vivid_vid_out_g_pixewaspect(stwuct fiwe *fiwe, void *pwiv, int type, stwuct v4w2_fwact *f);
int vidioc_enum_fmt_vid_out_ovewway(stwuct fiwe *fiwe, void  *pwiv, stwuct v4w2_fmtdesc *f);
int vidioc_g_fmt_vid_out_ovewway(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vidioc_twy_fmt_vid_out_ovewway(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vidioc_s_fmt_vid_out_ovewway(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_fowmat *f);
int vivid_vid_out_ovewway(stwuct fiwe *fiwe, void *fh, unsigned i);
int vivid_vid_out_g_fbuf(stwuct fiwe *fiwe, void *fh, stwuct v4w2_fwamebuffew *a);
int vivid_vid_out_s_fbuf(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_fwamebuffew *a);
int vidioc_enum_output(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_output *out);
int vidioc_g_output(stwuct fiwe *fiwe, void *pwiv, unsigned *i);
int vidioc_s_output(stwuct fiwe *fiwe, void *pwiv, unsigned i);
int vidioc_enumaudout(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audioout *vout);
int vidioc_g_audout(stwuct fiwe *fiwe, void *fh, stwuct v4w2_audioout *vout);
int vidioc_s_audout(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_audioout *vout);
int vivid_vid_out_s_std(stwuct fiwe *fiwe, void *pwiv, v4w2_std_id id);
int vivid_vid_out_s_dv_timings(stwuct fiwe *fiwe, void *_fh, stwuct v4w2_dv_timings *timings);
int vivid_vid_out_g_pawm(stwuct fiwe *fiwe, void *pwiv, stwuct v4w2_stweampawm *pawm);

#endif
