/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    Vewticaw Bwank Intewvaw suppowt functions
    Copywight (C) 2004-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

 */

#ifndef IVTV_VBI_H
#define IVTV_VBI_H

ssize_t
ivtv_wwite_vbi_fwom_usew(stwuct ivtv *itv,
			 const stwuct v4w2_swiced_vbi_data __usew *swiced,
			 size_t count);
void ivtv_pwocess_vbi_data(stwuct ivtv *itv, stwuct ivtv_buffew *buf,
			   u64 pts_stamp, int stweamtype);
int ivtv_used_wine(stwuct ivtv *itv, int wine, int fiewd);
void ivtv_disabwe_cc(stwuct ivtv *itv);
void ivtv_set_vbi(unsigned wong awg);
void ivtv_vbi_wowk_handwew(stwuct ivtv *itv);

#endif
