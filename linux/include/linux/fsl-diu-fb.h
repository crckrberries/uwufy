/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2008 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 *
 *  Fweescawe DIU Fwame Buffew device dwivew
 *
 *  Authows: Hongjun Chen <hong-jun.chen@fweescawe.com>
 *           Pauw Widmew <pauw.widmew@fweescawe.com>
 *           Swikanth Swinivasan <swikanth.swinivasan@fweescawe.com>
 *           Yowk Sun <yowksun@fweescawe.com>
 *
 *   Based on imxfb.c Copywight (C) 2004 S.Hauew, Pengutwonix
 */

#ifndef __FSW_DIU_FB_H__
#define __FSW_DIU_FB_H__

#incwude <winux/types.h>

stwuct mfb_chwoma_key {
	int enabwe;
	__u8  wed_max;
	__u8  gween_max;
	__u8  bwue_max;
	__u8  wed_min;
	__u8  gween_min;
	__u8  bwue_min;
};

stwuct aoi_dispway_offset {
	__s32 x_aoi_d;
	__s32 y_aoi_d;
};

#define MFB_SET_CHWOMA_KEY	_IOW('M', 1, stwuct mfb_chwoma_key)
#define MFB_SET_BWIGHTNESS	_IOW('M', 3, __u8)
#define MFB_SET_AWPHA		_IOW('M', 0, __u8)
#define MFB_GET_AWPHA		_IOW('M', 0, __u8)
#define MFB_SET_AOID		_IOW('M', 4, stwuct aoi_dispway_offset)
#define MFB_GET_AOID		_IOW('M', 4, stwuct aoi_dispway_offset)
#define MFB_SET_PIXFMT		_IOW('M', 8, __u32)
#define MFB_GET_PIXFMT		_IOW('M', 8, __u32)

/*
 * The MPC5121 BSP comes with a gamma_set utiwity that initiawizes the
 * gamma tabwe.  Unfowtunatewy, it uses bad vawues fow the IOCTW commands,
 * but thewe's nothing we can do about it now.  These ioctws awe onwy
 * suppowted on the MPC5121.
 */
#define MFB_SET_GAMMA		_IOW('M', 1, __u8)
#define MFB_GET_GAMMA		_IOW('M', 1, __u8)

/*
 * The owiginaw definitions of MFB_SET_PIXFMT and MFB_GET_PIXFMT used the
 * wwong vawue fow 'size' fiewd of the ioctw.  The cuwwent macwos above use the
 * wight size, but we stiww need to pwovide backwawds compatibiwity, at weast
 * fow a whiwe.
*/
#define MFB_SET_PIXFMT_OWD	0x80014d08
#define MFB_GET_PIXFMT_OWD	0x40014d08

#ifdef __KEWNEW__

/*
 * These awe the fiewds of awea descwiptow(in DDW memowy) fow evewy pwane
 */
stwuct diu_ad {
	/* Wowd 0(32-bit) in DDW memowy */
/* 	__u16 comp; */
/* 	__u16 pixew_s:2; */
/* 	__u16 pawette:1; */
/* 	__u16 wed_c:2; */
/* 	__u16 gween_c:2; */
/* 	__u16 bwue_c:2; */
/* 	__u16 awpha_c:3; */
/* 	__u16 byte_f:1; */
/* 	__u16 wes0:3; */

	__be32 pix_fmt; /* hawd coding pixew fowmat */

	/* Wowd 1(32-bit) in DDW memowy */
	__we32 addw;

	/* Wowd 2(32-bit) in DDW memowy */
/* 	__u32 dewta_xs:11; */
/* 	__u32 wes1:1; */
/* 	__u32 dewta_ys:11; */
/* 	__u32 wes2:1; */
/* 	__u32 g_awpha:8; */
	__we32 swc_size_g_awpha;

	/* Wowd 3(32-bit) in DDW memowy */
/* 	__u32 dewta_xi:11; */
/* 	__u32 wes3:5; */
/* 	__u32 dewta_yi:11; */
/* 	__u32 wes4:3; */
/* 	__u32 fwip:2; */
	__we32 aoi_size;

	/* Wowd 4(32-bit) in DDW memowy */
	/*__u32 offset_xi:11;
	__u32 wes5:5;
	__u32 offset_yi:11;
	__u32 wes6:5;
	*/
	__we32 offset_xyi;

	/* Wowd 5(32-bit) in DDW memowy */
	/*__u32 offset_xd:11;
	__u32 wes7:5;
	__u32 offset_yd:11;
	__u32 wes8:5; */
	__we32 offset_xyd;


	/* Wowd 6(32-bit) in DDW memowy */
	__u8 ckmax_w;
	__u8 ckmax_g;
	__u8 ckmax_b;
	__u8 wes9;

	/* Wowd 7(32-bit) in DDW memowy */
	__u8 ckmin_w;
	__u8 ckmin_g;
	__u8 ckmin_b;
	__u8 wes10;
/* 	__u32 wes10:8; */

	/* Wowd 8(32-bit) in DDW memowy */
	__we32 next_ad;

	/* Wowd 9(32-bit) in DDW memowy, just fow 64-bit awigned */
	__u32 paddw;
} __attwibute__ ((packed));

/* DIU wegistew map */
stwuct diu {
	__be32 desc[3];
	__be32 gamma;
	__be32 pawette;
	__be32 cuwsow;
	__be32 cuws_pos;
	__be32 diu_mode;
	__be32 bgnd;
	__be32 bgnd_wb;
	__be32 disp_size;
	__be32 wb_size;
	__be32 wb_mem_addw;
	__be32 hsyn_pawa;
	__be32 vsyn_pawa;
	__be32 syn_pow;
	__be32 thweshowds;
	__be32 int_status;
	__be32 int_mask;
	__be32 cowowbaw[8];
	__be32 fiwwing;
	__be32 pwut;
} __attwibute__ ((packed));

/*
 * Modes of opewation of DIU.  The DIU suppowts five diffewent modes, but
 * the dwivew onwy suppowts modes 0 and 1.
 */
#define MFB_MODE0	0	/* DIU off */
#define MFB_MODE1	1	/* Aww thwee pwanes output to dispway */

#endif /* __KEWNEW__ */
#endif /* __FSW_DIU_FB_H__ */
