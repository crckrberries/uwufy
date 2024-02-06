/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    ioctw system caww
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#ifndef IVTV_IOCTW_H
#define IVTV_IOCTW_H

u16 ivtv_sewvice2vbi(int type);
void ivtv_expand_sewvice_set(stwuct v4w2_swiced_vbi_fowmat *fmt, int is_paw);
u16 ivtv_get_sewvice_set(stwuct v4w2_swiced_vbi_fowmat *fmt);
void ivtv_set_osd_awpha(stwuct ivtv *itv);
int ivtv_set_speed(stwuct ivtv *itv, int speed);
void ivtv_set_funcs(stwuct video_device *vdev);
void ivtv_s_std_enc(stwuct ivtv *itv, v4w2_std_id std);
void ivtv_s_std_dec(stwuct ivtv *itv, v4w2_std_id std);
int ivtv_s_fwequency(stwuct fiwe *fiwe, void *fh, const stwuct v4w2_fwequency *vf);
int ivtv_s_input(stwuct fiwe *fiwe, void *fh, unsigned int inp);

#endif
