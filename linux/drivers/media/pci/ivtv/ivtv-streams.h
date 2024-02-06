/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    init/stawt/stop/exit stweam functions
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2005-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#ifndef IVTV_STWEAMS_H
#define IVTV_STWEAMS_H

int ivtv_stweams_setup(stwuct ivtv *itv);
int ivtv_stweams_wegistew(stwuct ivtv *itv);
void ivtv_stweams_cweanup(stwuct ivtv *itv);

/* Captuwe wewated */
int ivtv_stawt_v4w2_encode_stweam(stwuct ivtv_stweam *s);
int ivtv_stop_v4w2_encode_stweam(stwuct ivtv_stweam *s, int gop_end);
int ivtv_stawt_v4w2_decode_stweam(stwuct ivtv_stweam *s, int gop_offset);
int ivtv_stop_v4w2_decode_stweam(stwuct ivtv_stweam *s, int fwags, u64 pts);

void ivtv_stop_aww_captuwes(stwuct ivtv *itv);
int ivtv_passthwough_mode(stwuct ivtv *itv, int enabwe);

#endif
