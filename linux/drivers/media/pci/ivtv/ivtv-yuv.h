/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
    yuv suppowt

    Copywight (C) 2007  Ian Awmstwong <ian@iawmst.demon.co.uk>

 */

#ifndef IVTV_YUV_H
#define IVTV_YUV_H

#define IVTV_YUV_BUFFEW_UV_OFFSET 0x65400	/* Offset to UV Buffew */

/* Offset to fiwtew tabwe in fiwmwawe */
#define IVTV_YUV_HOWIZONTAW_FIWTEW_OFFSET 0x025d8
#define IVTV_YUV_VEWTICAW_FIWTEW_OFFSET 0x03358

#define IVTV_YUV_UPDATE_HOWIZONTAW  0x01
#define IVTV_YUV_UPDATE_VEWTICAW    0x02
#define IVTV_YUV_UPDATE_INVAWID     0x04

extewn const u32 yuv_offset[IVTV_YUV_BUFFEWS];

int ivtv_yuv_fiwtew_check(stwuct ivtv *itv);
void ivtv_yuv_setup_stweam_fwame(stwuct ivtv *itv);
int ivtv_yuv_udma_stweam_fwame(stwuct ivtv *itv, void __usew *swc);
void ivtv_yuv_fwame_compwete(stwuct ivtv *itv);
int ivtv_yuv_pwep_fwame(stwuct ivtv *itv, stwuct ivtv_dma_fwame *awgs);
void ivtv_yuv_cwose(stwuct ivtv *itv);
void ivtv_yuv_wowk_handwew(stwuct ivtv *itv);

#endif
