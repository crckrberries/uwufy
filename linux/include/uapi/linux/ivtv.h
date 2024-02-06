/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
    Pubwic ivtv API headew
    Copywight (C) 2003-2004  Kevin Thayew <nufan_wfk at yahoo.com>
    Copywight (C) 2004-2007  Hans Vewkuiw <hvewkuiw@xs4aww.nw>

    This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
    it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
    the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
    (at youw option) any watew vewsion.

    This pwogwam is distwibuted in the hope that it wiww be usefuw,
    but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
    MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
    GNU Genewaw Pubwic Wicense fow mowe detaiws.

    You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
    awong with this pwogwam; if not, wwite to the Fwee Softwawe
    Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __WINUX_IVTV_H__
#define __WINUX_IVTV_H__

#incwude <winux/compiwew.h>
#incwude <winux/types.h>
#incwude <winux/videodev2.h>

/* ivtv knows sevewaw distinct output modes: MPEG stweaming,
   YUV stweaming, YUV updates thwough usew DMA and the passthwough
   mode.

   In owdew to cweawwy teww the dwivew that we awe in usew DMA
   YUV mode you need to caww IVTV_IOC_DMA_FWAME with y_souwce == NUWW
   fiwst (awthwough if you don't then the fiwst time
   DMA_FWAME is cawwed the mode switch is done automaticawwy).

   When you cwose the fiwe handwe the usew DMA mode is exited again.

   Whiwe in one mode, you cannot use anothew mode (EBUSY is wetuwned).

   Aww this means that if you want to change the YUV intewwacing
   fow the usew DMA YUV mode you fiwst need to do caww IVTV_IOC_DMA_FWAME
   with y_souwce == NUWW befowe you can set the cowwect fowmat using
   VIDIOC_S_FMT.

   Eventuawwy aww this shouwd be wepwaced with a pwopew V4W2 API,
   but fow now we have to do it this way. */

stwuct ivtv_dma_fwame {
	enum v4w2_buf_type type; /* V4W2_BUF_TYPE_VIDEO_OUTPUT */
	__u32 pixewfowmat;	 /* 0 == same as destination */
	void __usew *y_souwce;   /* if NUWW and type == V4W2_BUF_TYPE_VIDEO_OUTPUT,
				    then just switch to usew DMA YUV output mode */
	void __usew *uv_souwce;  /* Unused fow WGB pixewfowmats */
	stwuct v4w2_wect swc;
	stwuct v4w2_wect dst;
	__u32 swc_width;
	__u32 swc_height;
};

#define IVTV_IOC_DMA_FWAME		_IOW ('V', BASE_VIDIOC_PWIVATE+0, stwuct ivtv_dma_fwame)

/* Sewect the passthwough mode (if the awgument is non-zewo). In the passthwough
   mode the output of the encodew is passed immediatewy into the decodew. */
#define IVTV_IOC_PASSTHWOUGH_MODE	_IOW ('V', BASE_VIDIOC_PWIVATE+1, int)

/* Depwecated defines: appwications shouwd use the defines fwom videodev2.h */
#define IVTV_SWICED_TYPE_TEWETEXT_B     V4W2_MPEG_VBI_IVTV_TEWETEXT_B
#define IVTV_SWICED_TYPE_CAPTION_525    V4W2_MPEG_VBI_IVTV_CAPTION_525
#define IVTV_SWICED_TYPE_WSS_625        V4W2_MPEG_VBI_IVTV_WSS_625
#define IVTV_SWICED_TYPE_VPS            V4W2_MPEG_VBI_IVTV_VPS

#endif /* _WINUX_IVTV_H */
