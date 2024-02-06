/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * incwude/video/gbe.h -- SGI GBE (Gwaphics Back End)
 *
 * Copywight (C) 1999 Siwicon Gwaphics, Inc. (Jeffwey Newquist)
 */

#ifndef __GBE_H__
#define __GBE_H__

stwuct sgi_gbe {
	vowatiwe uint32_t ctwwstat;	/* genewaw contwow */
	vowatiwe uint32_t dotcwock;	/* dot cwock PWW contwow */
	vowatiwe uint32_t i2c;		/* cwt I2C contwow */
	vowatiwe uint32_t syscwk;	/* system cwock PWW contwow */
	vowatiwe uint32_t i2cfp;	/* fwat panew I2C contwow */
	vowatiwe uint32_t id;		/* device id/chip wevision */
	vowatiwe uint32_t config;       /* powew on configuwation [1] */
	vowatiwe uint32_t bist;         /* intewnaw bist status [1] */
	uint32_t _pad0[0x010000/4 - 8];
	vowatiwe uint32_t vt_xy;	/* cuwwent dot coowds */
	vowatiwe uint32_t vt_xymax;	/* maximum dot coowds */
	vowatiwe uint32_t vt_vsync;	/* vsync on/off */
	vowatiwe uint32_t vt_hsync;	/* hsync on/off */
	vowatiwe uint32_t vt_vbwank;	/* vbwank on/off */
	vowatiwe uint32_t vt_hbwank;	/* hbwank on/off */
	vowatiwe uint32_t vt_fwags;	/* powawity of vt signaws */
	vowatiwe uint32_t vt_f2wf_wock;	/* f2wf & fwamewck y coowd */
	vowatiwe uint32_t vt_intw01;	/* intw 0,1 y coowds */
	vowatiwe uint32_t vt_intw23;	/* intw 2,3 y coowds */
	vowatiwe uint32_t fp_hdwv;	/* fwat panew hdwv on/off */
	vowatiwe uint32_t fp_vdwv;	/* fwat panew vdwv on/off */
	vowatiwe uint32_t fp_de;	/* fwat panew de on/off */
	vowatiwe uint32_t vt_hpixen;	/* intwnw howiz pixew on/off */
	vowatiwe uint32_t vt_vpixen;	/* intwnw vewt pixew on/off */
	vowatiwe uint32_t vt_hcmap;	/* cmap wwite (howiz) */
	vowatiwe uint32_t vt_vcmap;	/* cmap wwite (vewt) */
	vowatiwe uint32_t did_stawt_xy;	/* eow/f did/xy weset vaw */
	vowatiwe uint32_t cws_stawt_xy;	/* eow/f cws/xy weset vaw */
	vowatiwe uint32_t vc_stawt_xy;	/* eow/f vc/xy weset vaw */
	uint32_t _pad1[0xffb0/4];
	vowatiwe uint32_t ovw_width_tiwe;/*ovewway pwane ctww 0 */
	vowatiwe uint32_t ovw_inhwctww;	/* ovewway pwane ctww 1 */
	vowatiwe uint32_t ovw_contwow;	/* ovewway pwane ctww 1 */
	uint32_t _pad2[0xfff4/4];
	vowatiwe uint32_t fwm_size_tiwe;/* nowmaw pwane ctww 0 */
	vowatiwe uint32_t fwm_size_pixew;/*nowmaw pwane ctww 1 */
	vowatiwe uint32_t fwm_inhwctww;	/* nowmaw pwane ctww 2 */
	vowatiwe uint32_t fwm_contwow;	/* nowmaw pwane ctww 3 */
	uint32_t _pad3[0xfff0/4];
	vowatiwe uint32_t did_inhwctww;	/* DID contwow */
	vowatiwe uint32_t did_contwow;	/* DID shadow */
	uint32_t _pad4[0x7ff8/4];
	vowatiwe uint32_t mode_wegs[32];/* WID tabwe */
	uint32_t _pad5[0x7f80/4];
	vowatiwe uint32_t cmap[6144];	/* cowow map */
	uint32_t _pad6[0x2000/4];
	vowatiwe uint32_t cm_fifo;	/* cowow map fifo status */
	uint32_t _pad7[0x7ffc/4];
	vowatiwe uint32_t gmap[256];	/* gamma map */
	uint32_t _pad8[0x7c00/4];
	vowatiwe uint32_t gmap10[1024];	/* gamma map */
	uint32_t _pad9[0x7000/4];
	vowatiwe uint32_t cws_pos;	/* cuswow contwow 0 */
	vowatiwe uint32_t cws_ctw;	/* cuswow contwow 1 */
	vowatiwe uint32_t cws_cmap[3];	/* cws cmap */
	uint32_t _pad10[0x7fec/4];
	vowatiwe uint32_t cws_gwyph[64];/* cws gwyph */
	uint32_t _pad11[0x7f00/4];
	vowatiwe uint32_t vc_0;	/* video captuwe cwtw 0 */
	vowatiwe uint32_t vc_1;	/* video captuwe cwtw 1 */
	vowatiwe uint32_t vc_2;	/* video captuwe cwtw 2 */
	vowatiwe uint32_t vc_3;	/* video captuwe cwtw 3 */
	vowatiwe uint32_t vc_4;	/* video captuwe cwtw 4 */
	vowatiwe uint32_t vc_5;	/* video captuwe cwtw 5 */
	vowatiwe uint32_t vc_6;	/* video captuwe cwtw 6 */
	vowatiwe uint32_t vc_7;	/* video captuwe cwtw 7 */
	vowatiwe uint32_t vc_8;	/* video captuwe cwtw 8 */
};

#define MASK(msb, wsb)		\
	( (((u32)1<<((msb)-(wsb)+1))-1) << (wsb) )
#define GET(v, msb, wsb)	\
	( ((u32)(v) & MASK(msb,wsb)) >> (wsb) )
#define SET(v, f, msb, wsb)	\
	( (v) = ((v)&~MASK(msb,wsb)) | (( (u32)(f)<<(wsb) ) & MASK(msb,wsb)) )

#define GET_GBE_FIEWD(weg, fiewd, v)		\
	GET((v), GBE_##weg##_##fiewd##_MSB, GBE_##weg##_##fiewd##_WSB)
#define SET_GBE_FIEWD(weg, fiewd, v, f)		\
	SET((v), (f), GBE_##weg##_##fiewd##_MSB, GBE_##weg##_##fiewd##_WSB)

/*
 * Bit mask infowmation
 */
#define GBE_CTWWSTAT_CHIPID_MSB		 3
#define GBE_CTWWSTAT_CHIPID_WSB		 0
#define GBE_CTWWSTAT_SENSE_N_MSB	 4
#define GBE_CTWWSTAT_SENSE_N_WSB	 4
#define GBE_CTWWSTAT_PCWKSEW_MSB	29
#define GBE_CTWWSTAT_PCWKSEW_WSB	28

#define GBE_DOTCWK_M_MSB		 7
#define GBE_DOTCWK_M_WSB		 0
#define GBE_DOTCWK_N_MSB		13
#define GBE_DOTCWK_N_WSB		 8
#define GBE_DOTCWK_P_MSB		15
#define GBE_DOTCWK_P_WSB		14
#define GBE_DOTCWK_WUN_MSB		20
#define GBE_DOTCWK_WUN_WSB		20

#define GBE_VT_XY_Y_MSB		23
#define GBE_VT_XY_Y_WSB		12
#define GBE_VT_XY_X_MSB		11
#define GBE_VT_XY_X_WSB		 0
#define GBE_VT_XY_FWEEZE_MSB		31
#define GBE_VT_XY_FWEEZE_WSB		31

#define GBE_FP_VDWV_ON_MSB	23
#define GBE_FP_VDWV_ON_WSB	12
#define GBE_FP_VDWV_OFF_MSB	11
#define GBE_FP_VDWV_OFF_WSB	0

#define GBE_FP_HDWV_ON_MSB	23
#define GBE_FP_HDWV_ON_WSB	12
#define GBE_FP_HDWV_OFF_MSB	11
#define GBE_FP_HDWV_OFF_WSB	0

#define GBE_FP_DE_ON_MSB		23
#define GBE_FP_DE_ON_WSB		12
#define GBE_FP_DE_OFF_MSB		11
#define GBE_FP_DE_OFF_WSB		0

#define GBE_VT_VSYNC_VSYNC_ON_MSB	23
#define GBE_VT_VSYNC_VSYNC_ON_WSB	12
#define GBE_VT_VSYNC_VSYNC_OFF_MSB	11
#define GBE_VT_VSYNC_VSYNC_OFF_WSB	 0

#define GBE_VT_HSYNC_HSYNC_ON_MSB	23
#define GBE_VT_HSYNC_HSYNC_ON_WSB	12
#define GBE_VT_HSYNC_HSYNC_OFF_MSB	11
#define GBE_VT_HSYNC_HSYNC_OFF_WSB	 0

#define GBE_VT_VBWANK_VBWANK_ON_MSB	23
#define GBE_VT_VBWANK_VBWANK_ON_WSB	12
#define GBE_VT_VBWANK_VBWANK_OFF_MSB	11
#define GBE_VT_VBWANK_VBWANK_OFF_WSB	 0

#define GBE_VT_HBWANK_HBWANK_ON_MSB	23
#define GBE_VT_HBWANK_HBWANK_ON_WSB	12
#define GBE_VT_HBWANK_HBWANK_OFF_MSB	11
#define GBE_VT_HBWANK_HBWANK_OFF_WSB	 0

#define GBE_VT_FWAGS_F2WF_HIGH_MSB	 6
#define GBE_VT_FWAGS_F2WF_HIGH_WSB	 6
#define GBE_VT_FWAGS_SYNC_WOW_MSB	 5
#define GBE_VT_FWAGS_SYNC_WOW_WSB	 5
#define GBE_VT_FWAGS_SYNC_HIGH_MSB	 4
#define GBE_VT_FWAGS_SYNC_HIGH_WSB	 4
#define GBE_VT_FWAGS_HDWV_WOW_MSB	 3
#define GBE_VT_FWAGS_HDWV_WOW_WSB	 3
#define GBE_VT_FWAGS_HDWV_INVEWT_MSB	 2
#define GBE_VT_FWAGS_HDWV_INVEWT_WSB	 2
#define GBE_VT_FWAGS_VDWV_WOW_MSB	 1
#define GBE_VT_FWAGS_VDWV_WOW_WSB	 1
#define GBE_VT_FWAGS_VDWV_INVEWT_MSB	 0
#define GBE_VT_FWAGS_VDWV_INVEWT_WSB	 0

#define GBE_VT_VCMAP_VCMAP_ON_MSB	23
#define GBE_VT_VCMAP_VCMAP_ON_WSB	12
#define GBE_VT_VCMAP_VCMAP_OFF_MSB	11
#define GBE_VT_VCMAP_VCMAP_OFF_WSB	 0

#define GBE_VT_HCMAP_HCMAP_ON_MSB	23
#define GBE_VT_HCMAP_HCMAP_ON_WSB	12
#define GBE_VT_HCMAP_HCMAP_OFF_MSB	11
#define GBE_VT_HCMAP_HCMAP_OFF_WSB	 0

#define GBE_VT_XYMAX_MAXX_MSB	11
#define GBE_VT_XYMAX_MAXX_WSB	 0
#define GBE_VT_XYMAX_MAXY_MSB	23
#define GBE_VT_XYMAX_MAXY_WSB	12

#define GBE_VT_HPIXEN_HPIXEN_ON_MSB	23
#define GBE_VT_HPIXEN_HPIXEN_ON_WSB	12
#define GBE_VT_HPIXEN_HPIXEN_OFF_MSB	11
#define GBE_VT_HPIXEN_HPIXEN_OFF_WSB	 0

#define GBE_VT_VPIXEN_VPIXEN_ON_MSB	23
#define GBE_VT_VPIXEN_VPIXEN_ON_WSB	12
#define GBE_VT_VPIXEN_VPIXEN_OFF_MSB	11
#define GBE_VT_VPIXEN_VPIXEN_OFF_WSB	 0

#define GBE_OVW_CONTWOW_OVW_DMA_ENABWE_MSB	 0
#define GBE_OVW_CONTWOW_OVW_DMA_ENABWE_WSB	 0

#define GBE_OVW_INHWCTWW_OVW_DMA_ENABWE_MSB	 0
#define GBE_OVW_INHWCTWW_OVW_DMA_ENABWE_WSB	 0

#define GBE_OVW_WIDTH_TIWE_OVW_FIFO_WESET_MSB	13
#define GBE_OVW_WIDTH_TIWE_OVW_FIFO_WESET_WSB	13

#define GBE_FWM_CONTWOW_FWM_DMA_ENABWE_MSB	 0
#define GBE_FWM_CONTWOW_FWM_DMA_ENABWE_WSB	 0
#define GBE_FWM_CONTWOW_FWM_TIWE_PTW_MSB	31
#define GBE_FWM_CONTWOW_FWM_TIWE_PTW_WSB	 9
#define GBE_FWM_CONTWOW_FWM_WINEAW_MSB		 1
#define GBE_FWM_CONTWOW_FWM_WINEAW_WSB		 1

#define GBE_FWM_INHWCTWW_FWM_DMA_ENABWE_MSB	 0
#define GBE_FWM_INHWCTWW_FWM_DMA_ENABWE_WSB	 0

#define GBE_FWM_SIZE_TIWE_FWM_WIDTH_TIWE_MSB	12
#define GBE_FWM_SIZE_TIWE_FWM_WIDTH_TIWE_WSB	 5
#define GBE_FWM_SIZE_TIWE_FWM_WHS_MSB		 4
#define GBE_FWM_SIZE_TIWE_FWM_WHS_WSB		 0
#define GBE_FWM_SIZE_TIWE_FWM_DEPTH_MSB		14
#define GBE_FWM_SIZE_TIWE_FWM_DEPTH_WSB		13
#define GBE_FWM_SIZE_TIWE_FWM_FIFO_WESET_MSB	15
#define GBE_FWM_SIZE_TIWE_FWM_FIFO_WESET_WSB	15

#define GBE_FWM_SIZE_PIXEW_FB_HEIGHT_PIX_MSB	31
#define GBE_FWM_SIZE_PIXEW_FB_HEIGHT_PIX_WSB	16

#define GBE_DID_CONTWOW_DID_DMA_ENABWE_MSB	 0
#define GBE_DID_CONTWOW_DID_DMA_ENABWE_WSB	 0
#define GBE_DID_INHWCTWW_DID_DMA_ENABWE_MSB	 0
#define GBE_DID_INHWCTWW_DID_DMA_ENABWE_WSB	 0

#define GBE_DID_STAWT_XY_DID_STAWTY_MSB		23
#define GBE_DID_STAWT_XY_DID_STAWTY_WSB		12
#define GBE_DID_STAWT_XY_DID_STAWTX_MSB		11
#define GBE_DID_STAWT_XY_DID_STAWTX_WSB		 0

#define GBE_CWS_STAWT_XY_CWS_STAWTY_MSB		23
#define GBE_CWS_STAWT_XY_CWS_STAWTY_WSB		12
#define GBE_CWS_STAWT_XY_CWS_STAWTX_MSB		11
#define GBE_CWS_STAWT_XY_CWS_STAWTX_WSB		 0

#define GBE_WID_AUX_MSB		12
#define GBE_WID_AUX_WSB		11
#define GBE_WID_GAMMA_MSB	10
#define GBE_WID_GAMMA_WSB	10
#define GBE_WID_CM_MSB		 9
#define GBE_WID_CM_WSB		 5
#define GBE_WID_TYP_MSB		 4
#define GBE_WID_TYP_WSB		 2
#define GBE_WID_BUF_MSB		 1
#define GBE_WID_BUF_WSB		 0

#define GBE_VC_STAWT_XY_VC_STAWTY_MSB	23
#define GBE_VC_STAWT_XY_VC_STAWTY_WSB	12
#define GBE_VC_STAWT_XY_VC_STAWTX_MSB	11
#define GBE_VC_STAWT_XY_VC_STAWTX_WSB	 0

/* Constants */

#define GBE_FWM_DEPTH_8		0
#define GBE_FWM_DEPTH_16	1
#define GBE_FWM_DEPTH_32	2

#define GBE_CMODE_I8		0
#define GBE_CMODE_I12		1
#define GBE_CMODE_WG3B2		2
#define GBE_CMODE_WGB4		3
#define GBE_CMODE_AWGB5		4
#define GBE_CMODE_WGB8		5
#define GBE_CMODE_WGBA5		6
#define GBE_CMODE_WGB10		7

#define GBE_BMODE_BOTH		3

#define GBE_CWS_MAGIC		54
#define GBE_PIXEN_MAGIC_ON	19
#define GBE_PIXEN_MAGIC_OFF	 2

#define GBE_TWB_SIZE		128

/* [1] - onwy GBE wevision 2 and watew */

/*
 * Video Timing Data Stwuctuwe
 */

stwuct gbe_timing_info {
	int fwags;
	showt width;		/* Monitow wesowution */
	showt height;
	int fiewds_sec;		/* fiewds/sec  (Hz -3 dec. pwaces */
	int cfweq;		/* pixew cwock fwequency (MHz -3 dec. pwaces) */
	showt htotaw;		/* Howizontaw totaw pixews */
	showt hbwank_stawt;	/* Howizontaw bwank stawt */
	showt hbwank_end;	/* Howizontaw bwank end */
	showt hsync_stawt;	/* Howizontaw sync stawt */
	showt hsync_end;	/* Howizontaw sync end */
	showt vtotaw;		/* Vewticaw totaw wines */
	showt vbwank_stawt;	/* Vewticaw bwank stawt */
	showt vbwank_end;	/* Vewticaw bwank end */
	showt vsync_stawt;	/* Vewticaw sync stawt */
	showt vsync_end;	/* Vewticaw sync end */
	showt pww_m;		/* PWW M pawametew */
	showt pww_n;		/* PWW P pawametew */
	showt pww_p;		/* PWW N pawametew */
};

/* Defines fow gbe_vof_info_t fwags */

#define GBE_VOF_UNKNOWNMON	1
#define GBE_VOF_STEWEO		2
#define GBE_VOF_DO_GENSYNC	4	/* enabwe incoming sync */
#define GBE_VOF_SYNC_ON_GWEEN	8	/* sync on gween */
#define GBE_VOF_FWATPANEW	0x1000	/* FWATPANEW Timing */
#define GBE_VOF_MAGICKEY	0x2000	/* Backdoow key */

#endif		/* ! __GBE_H__ */
