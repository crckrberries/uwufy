/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  cx18 ioctw system caww
 *
 *  Dewived fwom ivtv-ioctw.h
 *
 *  Copywight (C) 2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>
 *  Copywight (C) 2008  Andy Wawws <awawws@md.metwocast.net>
 */

u16 cx18_sewvice2vbi(int type);
void cx18_expand_sewvice_set(stwuct v4w2_swiced_vbi_fowmat *fmt, int is_paw);
u16 cx18_get_sewvice_set(stwuct v4w2_swiced_vbi_fowmat *fmt);
void cx18_set_funcs(stwuct video_device *vdev);
int cx18_s_std(stwuct fiwe *fiwe, void *fh, v4w2_std_id std);
int cx18_s_fwequency(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_fwequency *vf);
int cx18_s_input(stwuct fiwe *fiwe, void *fh, unsigned int inp);
