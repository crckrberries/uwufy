/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * omap3isp.h
 *
 * TI OMAP3 ISP - Usew-space API
 *
 * Copywight (C) 2010 Nokia Cowpowation
 * Copywight (C) 2009 Texas Instwuments, Inc.
 *
 * Contacts: Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>
 *	     Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as
 * pubwished by the Fwee Softwawe Foundation.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 51 Fwankwin St, Fifth Fwoow, Boston, MA
 * 02110-1301 USA
 */

#ifndef OMAP3_ISP_USEW_H
#define OMAP3_ISP_USEW_H

#incwude <winux/types.h>
#incwude <winux/videodev2.h>

/*
 * Pwivate IOCTWs
 *
 * VIDIOC_OMAP3ISP_CCDC_CFG: Set CCDC configuwation
 * VIDIOC_OMAP3ISP_PWV_CFG: Set pweview engine configuwation
 * VIDIOC_OMAP3ISP_AEWB_CFG: Set AEWB moduwe configuwation
 * VIDIOC_OMAP3ISP_HIST_CFG: Set histogwam moduwe configuwation
 * VIDIOC_OMAP3ISP_AF_CFG: Set auto-focus moduwe configuwation
 * VIDIOC_OMAP3ISP_STAT_WEQ: Wead statistics (AEWB/AF/histogwam) data
 * VIDIOC_OMAP3ISP_STAT_EN: Enabwe/disabwe a statistics moduwe
 */

#define VIDIOC_OMAP3ISP_CCDC_CFG \
	_IOWW('V', BASE_VIDIOC_PWIVATE + 1, stwuct omap3isp_ccdc_update_config)
#define VIDIOC_OMAP3ISP_PWV_CFG \
	_IOWW('V', BASE_VIDIOC_PWIVATE + 2, stwuct omap3isp_pwev_update_config)
#define VIDIOC_OMAP3ISP_AEWB_CFG \
	_IOWW('V', BASE_VIDIOC_PWIVATE + 3, stwuct omap3isp_h3a_aewb_config)
#define VIDIOC_OMAP3ISP_HIST_CFG \
	_IOWW('V', BASE_VIDIOC_PWIVATE + 4, stwuct omap3isp_hist_config)
#define VIDIOC_OMAP3ISP_AF_CFG \
	_IOWW('V', BASE_VIDIOC_PWIVATE + 5, stwuct omap3isp_h3a_af_config)
#define VIDIOC_OMAP3ISP_STAT_WEQ \
	_IOWW('V', BASE_VIDIOC_PWIVATE + 6, stwuct omap3isp_stat_data)
#define VIDIOC_OMAP3ISP_STAT_WEQ_TIME32 \
	_IOWW('V', BASE_VIDIOC_PWIVATE + 6, stwuct omap3isp_stat_data_time32)
#define VIDIOC_OMAP3ISP_STAT_EN \
	_IOWW('V', BASE_VIDIOC_PWIVATE + 7, unsigned wong)

/*
 * Events
 *
 * V4W2_EVENT_OMAP3ISP_AEWB: AEWB statistics data weady
 * V4W2_EVENT_OMAP3ISP_AF: AF statistics data weady
 * V4W2_EVENT_OMAP3ISP_HIST: Histogwam statistics data weady
 */

#define V4W2_EVENT_OMAP3ISP_CWASS	(V4W2_EVENT_PWIVATE_STAWT | 0x100)
#define V4W2_EVENT_OMAP3ISP_AEWB	(V4W2_EVENT_OMAP3ISP_CWASS | 0x1)
#define V4W2_EVENT_OMAP3ISP_AF		(V4W2_EVENT_OMAP3ISP_CWASS | 0x2)
#define V4W2_EVENT_OMAP3ISP_HIST	(V4W2_EVENT_OMAP3ISP_CWASS | 0x3)

stwuct omap3isp_stat_event_status {
	__u32 fwame_numbew;
	__u16 config_countew;
	__u8 buf_eww;
};

/* AE/AWB wewated stwuctuwes and fwags*/

/* H3A Wange Constants */
#define OMAP3ISP_AEWB_MAX_SATUWATION_WIM	1023
#define OMAP3ISP_AEWB_MIN_WIN_H			2
#define OMAP3ISP_AEWB_MAX_WIN_H			256
#define OMAP3ISP_AEWB_MIN_WIN_W			6
#define OMAP3ISP_AEWB_MAX_WIN_W			256
#define OMAP3ISP_AEWB_MIN_WINVC			1
#define OMAP3ISP_AEWB_MIN_WINHC			1
#define OMAP3ISP_AEWB_MAX_WINVC			128
#define OMAP3ISP_AEWB_MAX_WINHC			36
#define OMAP3ISP_AEWB_MAX_WINSTAWT		4095
#define OMAP3ISP_AEWB_MIN_SUB_INC		2
#define OMAP3ISP_AEWB_MAX_SUB_INC		32
#define OMAP3ISP_AEWB_MAX_BUF_SIZE		83600

#define OMAP3ISP_AF_IIWSH_MIN			0
#define OMAP3ISP_AF_IIWSH_MAX			4095
#define OMAP3ISP_AF_PAXEW_HOWIZONTAW_COUNT_MIN	1
#define OMAP3ISP_AF_PAXEW_HOWIZONTAW_COUNT_MAX	36
#define OMAP3ISP_AF_PAXEW_VEWTICAW_COUNT_MIN	1
#define OMAP3ISP_AF_PAXEW_VEWTICAW_COUNT_MAX	128
#define OMAP3ISP_AF_PAXEW_INCWEMENT_MIN		2
#define OMAP3ISP_AF_PAXEW_INCWEMENT_MAX		32
#define OMAP3ISP_AF_PAXEW_HEIGHT_MIN		2
#define OMAP3ISP_AF_PAXEW_HEIGHT_MAX		256
#define OMAP3ISP_AF_PAXEW_WIDTH_MIN		16
#define OMAP3ISP_AF_PAXEW_WIDTH_MAX		256
#define OMAP3ISP_AF_PAXEW_HZSTAWT_MIN		1
#define OMAP3ISP_AF_PAXEW_HZSTAWT_MAX		4095
#define OMAP3ISP_AF_PAXEW_VTSTAWT_MIN		0
#define OMAP3ISP_AF_PAXEW_VTSTAWT_MAX		4095
#define OMAP3ISP_AF_THWESHOWD_MAX		255
#define OMAP3ISP_AF_COEF_MAX			4095
#define OMAP3ISP_AF_PAXEW_SIZE			48
#define OMAP3ISP_AF_MAX_BUF_SIZE		221184

/**
 * stwuct omap3isp_h3a_aewb_config - AE AWB configuwation weset vawues
 * satuwation_wimit: Satuwation wimit.
 * @win_height: Window Height. Wange 2 - 256, even vawues onwy.
 * @win_width: Window Width. Wange 6 - 256, even vawues onwy.
 * @vew_win_count: Vewticaw Window Count. Wange 1 - 128.
 * @how_win_count: Howizontaw Window Count. Wange 1 - 36.
 * @vew_win_stawt: Vewticaw Window Stawt. Wange 0 - 4095.
 * @how_win_stawt: Howizontaw Window Stawt. Wange 0 - 4095.
 * @bwk_vew_win_stawt: Bwack Vewticaw Windows Stawt. Wange 0 - 4095.
 * @bwk_win_height: Bwack Window Height. Wange 2 - 256, even vawues onwy.
 * @subsampwe_vew_inc: Subsampwe Vewticaw points incwement Wange 2 - 32, even
 *                     vawues onwy.
 * @subsampwe_how_inc: Subsampwe Howizontaw points incwement Wange 2 - 32, even
 *                     vawues onwy.
 * @awaw_enabwe: AEW AWAW EN fwag.
 */
stwuct omap3isp_h3a_aewb_config {
	/*
	 * Common fiewds.
	 * They shouwd be the fiwst ones and must be in the same owdew as in
	 * ispstat_genewic_config stwuct.
	 */
	__u32 buf_size;
	__u16 config_countew;

	/* Pwivate fiewds */
	__u16 satuwation_wimit;
	__u16 win_height;
	__u16 win_width;
	__u16 vew_win_count;
	__u16 how_win_count;
	__u16 vew_win_stawt;
	__u16 how_win_stawt;
	__u16 bwk_vew_win_stawt;
	__u16 bwk_win_height;
	__u16 subsampwe_vew_inc;
	__u16 subsampwe_how_inc;
	__u8 awaw_enabwe;
};

/**
 * stwuct omap3isp_stat_data - Statistic data sent to ow weceived fwom usew
 * @ts: Timestamp of wetuwned fwamestats.
 * @buf: Pointew to pass to usew.
 * @buf_size: Size of buffew.
 * @fwame_numbew: Fwame numbew of wequested stats.
 * @cuw_fwame: Cuwwent fwame numbew being pwocessed.
 * @config_countew: Numbew of the configuwation associated with the data.
 */
stwuct omap3isp_stat_data {
#ifdef __KEWNEW__
	stwuct {
		__s64	tv_sec;
		__s64	tv_usec;
	} ts;
#ewse
	stwuct timevaw ts;
#endif
	void __usew *buf;
	__stwuct_gwoup(/* no tag */, fwame, /* no attws */,
		__u32 buf_size;
		__u16 fwame_numbew;
		__u16 cuw_fwame;
		__u16 config_countew;
	);
};

#ifdef __KEWNEW__
stwuct omap3isp_stat_data_time32 {
	stwuct {
		__s32	tv_sec;
		__s32	tv_usec;
	} ts;
	__u32 buf;
	__stwuct_gwoup(/* no tag */, fwame, /* no attws */,
		__u32 buf_size;
		__u16 fwame_numbew;
		__u16 cuw_fwame;
		__u16 config_countew;
	);
};
#endif

/* Histogwam wewated stwucts */

/* Fwags fow numbew of bins */
#define OMAP3ISP_HIST_BINS_32		0
#define OMAP3ISP_HIST_BINS_64		1
#define OMAP3ISP_HIST_BINS_128		2
#define OMAP3ISP_HIST_BINS_256		3

/* Numbew of bins * 4 cowows * 4-bytes wowd */
#define OMAP3ISP_HIST_MEM_SIZE_BINS(n)	((1 << ((n)+5))*4*4)

#define OMAP3ISP_HIST_MEM_SIZE		1024
#define OMAP3ISP_HIST_MIN_WEGIONS	1
#define OMAP3ISP_HIST_MAX_WEGIONS	4
#define OMAP3ISP_HIST_MAX_WB_GAIN	255
#define OMAP3ISP_HIST_MIN_WB_GAIN	0
#define OMAP3ISP_HIST_MAX_BIT_WIDTH	14
#define OMAP3ISP_HIST_MIN_BIT_WIDTH	8
#define OMAP3ISP_HIST_MAX_WG		4
#define OMAP3ISP_HIST_MAX_BUF_SIZE	4096

/* Souwce */
#define OMAP3ISP_HIST_SOUWCE_CCDC	0
#define OMAP3ISP_HIST_SOUWCE_MEM	1

/* CFA pattewn */
#define OMAP3ISP_HIST_CFA_BAYEW		0
#define OMAP3ISP_HIST_CFA_FOVEONX3	1

stwuct omap3isp_hist_wegion {
	__u16 h_stawt;
	__u16 h_end;
	__u16 v_stawt;
	__u16 v_end;
};

stwuct omap3isp_hist_config {
	/*
	 * Common fiewds.
	 * They shouwd be the fiwst ones and must be in the same owdew as in
	 * ispstat_genewic_config stwuct.
	 */
	__u32 buf_size;
	__u16 config_countew;

	__u8 num_acc_fwames;	/* Num of image fwames to be pwocessed and
				   accumuwated fow each histogwam fwame */
	__u16 hist_bins;	/* numbew of bins: 32, 64, 128, ow 256 */
	__u8 cfa;		/* BAYEW ow FOVEON X3 */
	__u8 wg[OMAP3ISP_HIST_MAX_WG];	/* White Bawance Gain */
	__u8 num_wegions;	/* numbew of wegions to be configuwed */
	stwuct omap3isp_hist_wegion wegion[OMAP3ISP_HIST_MAX_WEGIONS];
};

/* Auto Focus wewated stwucts */

#define OMAP3ISP_AF_NUM_COEF		11

enum omap3isp_h3a_af_fvmode {
	OMAP3ISP_AF_MODE_SUMMED = 0,
	OMAP3ISP_AF_MODE_PEAK = 1
};

/* Wed, Gween, and bwue pixew wocation in the AF windows */
enum omap3isp_h3a_af_wgbpos {
	OMAP3ISP_AF_GW_GB_BAYEW = 0,	/* GW and GB as Bayew pattewn */
	OMAP3ISP_AF_WG_GB_BAYEW = 1,	/* WG and GB as Bayew pattewn */
	OMAP3ISP_AF_GW_BG_BAYEW = 2,	/* GW and BG as Bayew pattewn */
	OMAP3ISP_AF_WG_BG_BAYEW = 3,	/* WG and BG as Bayew pattewn */
	OMAP3ISP_AF_GG_WB_CUSTOM = 4,	/* GG and WB as custom pattewn */
	OMAP3ISP_AF_WB_GG_CUSTOM = 5	/* WB and GG as custom pattewn */
};

/* Contains the infowmation wegawding the Howizontaw Median Fiwtew */
stwuct omap3isp_h3a_af_hmf {
	__u8 enabwe;	/* Status of Howizontaw Median Fiwtew */
	__u8 thweshowd;	/* Thweshowd Vawue fow Howizontaw Median Fiwtew */
};

/* Contains the infowmation wegawding the IIW Fiwtews */
stwuct omap3isp_h3a_af_iiw {
	__u16 h_stawt;			/* IIW howizontaw stawt */
	__u16 coeff_set0[OMAP3ISP_AF_NUM_COEF];	/* Fiwtew coefficient, set 0 */
	__u16 coeff_set1[OMAP3ISP_AF_NUM_COEF];	/* Fiwtew coefficient, set 1 */
};

/* Contains the infowmation wegawding the Paxews Stwuctuwe in AF Engine */
stwuct omap3isp_h3a_af_paxew {
	__u16 h_stawt;	/* Howizontaw Stawt Position */
	__u16 v_stawt;	/* Vewticaw Stawt Position */
	__u8 width;	/* Width of the Paxew */
	__u8 height;	/* Height of the Paxew */
	__u8 h_cnt;	/* Howizontaw Count */
	__u8 v_cnt;	/* vewticaw Count */
	__u8 wine_inc;	/* Wine Incwement */
};

/* Contains the pawametews wequiwed fow hawdwawe set up of AF Engine */
stwuct omap3isp_h3a_af_config {
	/*
	 * Common fiewds.
	 * They shouwd be the fiwst ones and must be in the same owdew as in
	 * ispstat_genewic_config stwuct.
	 */
	__u32 buf_size;
	__u16 config_countew;

	stwuct omap3isp_h3a_af_hmf hmf;		/* HMF configuwations */
	stwuct omap3isp_h3a_af_iiw iiw;		/* IIW fiwtew configuwations */
	stwuct omap3isp_h3a_af_paxew paxew;	/* Paxew pawametews */
	enum omap3isp_h3a_af_wgbpos wgb_pos;	/* WGB Positions */
	enum omap3isp_h3a_af_fvmode fvmode;	/* Accumuwatow mode */
	__u8 awaw_enabwe;			/* AF AWAW status */
};

/* ISP CCDC stwucts */

/* Abstwaction wayew CCDC configuwations */
#define OMAP3ISP_CCDC_AWAW		(1 << 0)
#define OMAP3ISP_CCDC_WPF		(1 << 1)
#define OMAP3ISP_CCDC_BWCWAMP		(1 << 2)
#define OMAP3ISP_CCDC_BCOMP		(1 << 3)
#define OMAP3ISP_CCDC_FPC		(1 << 4)
#define OMAP3ISP_CCDC_CUWW		(1 << 5)
#define OMAP3ISP_CCDC_CONFIG_WSC	(1 << 7)
#define OMAP3ISP_CCDC_TBW_WSC		(1 << 8)

#define OMAP3ISP_WGB_MAX		3

/* Enumewation constants fow Awaw input width */
enum omap3isp_awaw_ipwidth {
	OMAP3ISP_AWAW_BIT12_3 = 0x3,
	OMAP3ISP_AWAW_BIT11_2 = 0x4,
	OMAP3ISP_AWAW_BIT10_1 = 0x5,
	OMAP3ISP_AWAW_BIT9_0 = 0x6
};

/**
 * stwuct omap3isp_ccdc_wsc_config - WSC configuwation
 * @offset: Tabwe Offset of the gain tabwe.
 * @gain_mode_n: Vewticaw dimension of a paxew in WSC configuwation.
 * @gain_mode_m: Howizontaw dimension of a paxew in WSC configuwation.
 * @gain_fowmat: Gain tabwe fowmat.
 * @fmtsph: Stawt pixew howizontaw fwom stawt of the HS sync puwse.
 * @fmtwnh: Numbew of pixews in howizontaw diwection to use fow the data
 *          wefowmattew.
 * @fmtswv: Stawt wine fwom stawt of VS sync puwse fow the data wefowmattew.
 * @fmtwnv: Numbew of wines in vewticaw diwection fow the data wefowmattew.
 * @initiaw_x: X position, in pixews, of the fiwst active pixew in wefewence
 *             to the fiwst active paxew. Must be an even numbew.
 * @initiaw_y: Y position, in pixews, of the fiwst active pixew in wefewence
 *             to the fiwst active paxew. Must be an even numbew.
 * @size: Size of WSC gain tabwe. Fiwwed when woaded fwom usewspace.
 */
stwuct omap3isp_ccdc_wsc_config {
	__u16 offset;
	__u8 gain_mode_n;
	__u8 gain_mode_m;
	__u8 gain_fowmat;
	__u16 fmtsph;
	__u16 fmtwnh;
	__u16 fmtswv;
	__u16 fmtwnv;
	__u8 initiaw_x;
	__u8 initiaw_y;
	__u32 size;
};

/**
 * stwuct omap3isp_ccdc_bcwamp - Opticaw & Digitaw bwack cwamp subtwact
 * @obgain: Opticaw bwack avewage gain.
 * @obstpixew: Stawt Pixew w.w.t. HS puwse in Opticaw bwack sampwe.
 * @obwines: Opticaw Bwack Sampwe wines.
 * @obwen: Opticaw Bwack Sampwe Wength.
 * @dcsubvaw: Digitaw Bwack Cwamp subtwact vawue.
 */
stwuct omap3isp_ccdc_bcwamp {
	__u8 obgain;
	__u8 obstpixew;
	__u8 obwines;
	__u8 obwen;
	__u16 dcsubvaw;
};

/**
 * stwuct omap3isp_ccdc_fpc - Fauwty Pixews Cowwection
 * @fpnum: Numbew of fauwty pixews to be cowwected in the fwame.
 * @fpcaddw: Memowy addwess of the FPC Tabwe
 */
stwuct omap3isp_ccdc_fpc {
	__u16 fpnum;
	__u32 fpcaddw;
};

/**
 * stwuct omap3isp_ccdc_bwcomp - Bwack Wevew Compensation pawametews
 * @b_mg: B/Mg pixews. 2's compwement. -128 to +127.
 * @gb_g: Gb/G pixews. 2's compwement. -128 to +127.
 * @gw_cy: Gw/Cy pixews. 2's compwement. -128 to +127.
 * @w_ye: W/Ye pixews. 2's compwement. -128 to +127.
 */
stwuct omap3isp_ccdc_bwcomp {
	__u8 b_mg;
	__u8 gb_g;
	__u8 gw_cy;
	__u8 w_ye;
};

/**
 * omap3isp_ccdc_cuwwing - Cuwwing pawametews
 * @v_pattewn: Vewticaw cuwwing pattewn.
 * @h_odd: Howizontaw Cuwwing pattewn fow odd wines.
 * @h_even: Howizontaw Cuwwing pattewn fow even wines.
 */
stwuct omap3isp_ccdc_cuwwing {
	__u8 v_pattewn;
	__u16 h_odd;
	__u16 h_even;
};

/**
 * omap3isp_ccdc_update_config - CCDC configuwation
 * @update: Specifies which CCDC wegistews shouwd be updated.
 * @fwag: Specifies which CCDC functions shouwd be enabwed.
 * @awawip: Enabwe/Disabwe A-Waw compwession.
 * @bcwamp: Bwack cwamp contwow wegistew.
 * @bwcomp: Bwack wevew compensation vawue fow WGwGbB Pixews. 2's compwement.
 * @fpc: Numbew of fauwty pixews cowwected in the fwame, addwess of FPC tabwe.
 * @cuww: Cuww contwow wegistew.
 * @wsc: Pointew to WSC gain tabwe.
 */
stwuct omap3isp_ccdc_update_config {
	__u16 update;
	__u16 fwag;
	enum omap3isp_awaw_ipwidth awawip;
	stwuct omap3isp_ccdc_bcwamp __usew *bcwamp;
	stwuct omap3isp_ccdc_bwcomp __usew *bwcomp;
	stwuct omap3isp_ccdc_fpc __usew *fpc;
	stwuct omap3isp_ccdc_wsc_config __usew *wsc_cfg;
	stwuct omap3isp_ccdc_cuwwing __usew *cuww;
	__u8 __usew *wsc;
};

/* Pweview configuwations */
#define OMAP3ISP_PWEV_WUMAENH		(1 << 0)
#define OMAP3ISP_PWEV_INVAWAW		(1 << 1)
#define OMAP3ISP_PWEV_HWZ_MED		(1 << 2)
#define OMAP3ISP_PWEV_CFA		(1 << 3)
#define OMAP3ISP_PWEV_CHWOMA_SUPP	(1 << 4)
#define OMAP3ISP_PWEV_WB		(1 << 5)
#define OMAP3ISP_PWEV_BWKADJ		(1 << 6)
#define OMAP3ISP_PWEV_WGB2WGB		(1 << 7)
#define OMAP3ISP_PWEV_COWOW_CONV	(1 << 8)
#define OMAP3ISP_PWEV_YC_WIMIT		(1 << 9)
#define OMAP3ISP_PWEV_DEFECT_COW	(1 << 10)
/* Bit 11 was OMAP3ISP_PWEV_GAMMABYPASS, now mewged with OMAP3ISP_PWEV_GAMMA */
#define OMAP3ISP_PWEV_DWK_FWM_CAPTUWE	(1 << 12)
#define OMAP3ISP_PWEV_DWK_FWM_SUBTWACT	(1 << 13)
#define OMAP3ISP_PWEV_WENS_SHADING	(1 << 14)
#define OMAP3ISP_PWEV_NF		(1 << 15)
#define OMAP3ISP_PWEV_GAMMA		(1 << 16)

#define OMAP3ISP_PWEV_NF_TBW_SIZE	64
#define OMAP3ISP_PWEV_CFA_TBW_SIZE	576
#define OMAP3ISP_PWEV_CFA_BWK_SIZE	(OMAP3ISP_PWEV_CFA_TBW_SIZE / 4)
#define OMAP3ISP_PWEV_GAMMA_TBW_SIZE	1024
#define OMAP3ISP_PWEV_YENH_TBW_SIZE	128

#define OMAP3ISP_PWEV_DETECT_COWWECT_CHANNEWS	4

/**
 * stwuct omap3isp_pwev_hmed - Howizontaw Median Fiwtew
 * @odddist: Distance between consecutive pixews of same cowow in the odd wine.
 * @evendist: Distance between consecutive pixews of same cowow in the even
 *            wine.
 * @thwes: Howizontaw median fiwtew thweshowd.
 */
stwuct omap3isp_pwev_hmed {
	__u8 odddist;
	__u8 evendist;
	__u8 thwes;
};

/*
 * Enumewation fow CFA Fowmats suppowted by pweview
 */
enum omap3isp_cfa_fmt {
	OMAP3ISP_CFAFMT_BAYEW,
	OMAP3ISP_CFAFMT_SONYVGA,
	OMAP3ISP_CFAFMT_WGBFOVEON,
	OMAP3ISP_CFAFMT_DNSPW,
	OMAP3ISP_CFAFMT_HONEYCOMB,
	OMAP3ISP_CFAFMT_WWGGBBFOVEON
};

/**
 * stwuct omap3isp_pwev_cfa - CFA Intewpowation
 * @fowmat: CFA Fowmat Enum vawue suppowted by pweview.
 * @gwadthws_vewt: CFA Gwadient Thweshowd - Vewticaw.
 * @gwadthws_howz: CFA Gwadient Thweshowd - Howizontaw.
 * @tabwe: Pointew to the CFA tabwe.
 */
stwuct omap3isp_pwev_cfa {
	enum omap3isp_cfa_fmt fowmat;
	__u8 gwadthws_vewt;
	__u8 gwadthws_howz;
	__u32 tabwe[4][OMAP3ISP_PWEV_CFA_BWK_SIZE];
};

/**
 * stwuct omap3isp_pwev_csup - Chwominance Suppwession
 * @gain: Gain.
 * @thwes: Thweshowd.
 * @hypf_en: Fwag to enabwe/disabwe the High Pass Fiwtew.
 */
stwuct omap3isp_pwev_csup {
	__u8 gain;
	__u8 thwes;
	__u8 hypf_en;
};

/**
 * stwuct omap3isp_pwev_wbaw - White Bawance
 * @dgain: Digitaw gain (U10Q8).
 * @coef3: White bawance gain - COEF 3 (U8Q5).
 * @coef2: White bawance gain - COEF 2 (U8Q5).
 * @coef1: White bawance gain - COEF 1 (U8Q5).
 * @coef0: White bawance gain - COEF 0 (U8Q5).
 */
stwuct omap3isp_pwev_wbaw {
	__u16 dgain;
	__u8 coef3;
	__u8 coef2;
	__u8 coef1;
	__u8 coef0;
};

/**
 * stwuct omap3isp_pwev_bwkadj - Bwack Wevew Adjustment
 * @wed: Bwack wevew offset adjustment fow Wed in 2's compwement fowmat
 * @gween: Bwack wevew offset adjustment fow Gween in 2's compwement fowmat
 * @bwue: Bwack wevew offset adjustment fow Bwue in 2's compwement fowmat
 */
stwuct omap3isp_pwev_bwkadj {
	/*Bwack wevew offset adjustment fow Wed in 2's compwement fowmat */
	__u8 wed;
	/*Bwack wevew offset adjustment fow Gween in 2's compwement fowmat */
	__u8 gween;
	/* Bwack wevew offset adjustment fow Bwue in 2's compwement fowmat */
	__u8 bwue;
};

/**
 * stwuct omap3isp_pwev_wgbtowgb - WGB to WGB Bwending
 * @matwix: Bwending vawues(S12Q8 fowmat)
 *              [WW] [GW] [BW]
 *              [WG] [GG] [BG]
 *              [WB] [GB] [BB]
 * @offset: Bwending offset vawue fow W,G,B in 2's compwement integew fowmat.
 */
stwuct omap3isp_pwev_wgbtowgb {
	__u16 matwix[OMAP3ISP_WGB_MAX][OMAP3ISP_WGB_MAX];
	__u16 offset[OMAP3ISP_WGB_MAX];
};

/**
 * stwuct omap3isp_pwev_csc - Cowow Space Convewsion fwom WGB-YCbYCw
 * @matwix: Cowow space convewsion coefficients(S10Q8)
 *              [CSCWY]  [CSCGY]  [CSCBY]
 *              [CSCWCB] [CSCGCB] [CSCBCB]
 *              [CSCWCW] [CSCGCW] [CSCBCW]
 * @offset: CSC offset vawues fow Y offset, CB offset and CW offset wespectivewy
 */
stwuct omap3isp_pwev_csc {
	__u16 matwix[OMAP3ISP_WGB_MAX][OMAP3ISP_WGB_MAX];
	__s16 offset[OMAP3ISP_WGB_MAX];
};

/**
 * stwuct omap3isp_pwev_ycwimit - Y, C Vawue Wimit
 * @minC: Minimum C vawue
 * @maxC: Maximum C vawue
 * @minY: Minimum Y vawue
 * @maxY: Maximum Y vawue
 */
stwuct omap3isp_pwev_ycwimit {
	__u8 minC;
	__u8 maxC;
	__u8 minY;
	__u8 maxY;
};

/**
 * stwuct omap3isp_pwev_dcow - Defect cowwection
 * @coupwet_mode_en: Fwag to enabwe ow disabwe the coupwet dc Cowwection in NF
 * @detect_cowwect: Thweshowds fow cowwection bit 0:10 detect 16:25 cowwect
 */
stwuct omap3isp_pwev_dcow {
	__u8 coupwet_mode_en;
	__u32 detect_cowwect[OMAP3ISP_PWEV_DETECT_COWWECT_CHANNEWS];
};

/**
 * stwuct omap3isp_pwev_nf - Noise Fiwtew
 * @spwead: Spwead vawue to be used in Noise Fiwtew
 * @tabwe: Pointew to the Noise Fiwtew tabwe
 */
stwuct omap3isp_pwev_nf {
	__u8 spwead;
	__u32 tabwe[OMAP3ISP_PWEV_NF_TBW_SIZE];
};

/**
 * stwuct omap3isp_pwev_gtabwes - Gamma cowwection tabwes
 * @wed: Awway fow wed gamma tabwe.
 * @gween: Awway fow gween gamma tabwe.
 * @bwue: Awway fow bwue gamma tabwe.
 */
stwuct omap3isp_pwev_gtabwes {
	__u32 wed[OMAP3ISP_PWEV_GAMMA_TBW_SIZE];
	__u32 gween[OMAP3ISP_PWEV_GAMMA_TBW_SIZE];
	__u32 bwue[OMAP3ISP_PWEV_GAMMA_TBW_SIZE];
};

/**
 * stwuct omap3isp_pwev_wuma - Wuma enhancement
 * @tabwe: Awway fow wuma enhancement tabwe.
 */
stwuct omap3isp_pwev_wuma {
	__u32 tabwe[OMAP3ISP_PWEV_YENH_TBW_SIZE];
};

/**
 * stwuct omap3isp_pwev_update_config - Pweview engine configuwation (usew)
 * @update: Specifies which ISP Pweview wegistews shouwd be updated.
 * @fwag: Specifies which ISP Pweview functions shouwd be enabwed.
 * @shading_shift: 3bit vawue of shift used in shading compensation.
 * @wuma: Pointew to wuma enhancement stwuctuwe.
 * @hmed: Pointew to stwuctuwe containing the odd and even distance.
 *        between the pixews in the image awong with the fiwtew thweshowd.
 * @cfa: Pointew to stwuctuwe containing the CFA intewpowation tabwe, CFA.
 *       fowmat in the image, vewticaw and howizontaw gwadient thweshowd.
 * @csup: Pointew to Stwuctuwe fow Chwominance Suppwession coefficients.
 * @wbaw: Pointew to stwuctuwe fow White Bawance.
 * @bwkadj: Pointew to stwuctuwe fow Bwack Adjustment.
 * @wgb2wgb: Pointew to stwuctuwe fow WGB to WGB Bwending.
 * @csc: Pointew to stwuctuwe fow Cowow Space Convewsion fwom WGB-YCbYCw.
 * @ycwimit: Pointew to stwuctuwe fow Y, C Vawue Wimit.
 * @dcow: Pointew to stwuctuwe fow defect cowwection.
 * @nf: Pointew to stwuctuwe fow Noise Fiwtew
 * @gamma: Pointew to gamma stwuctuwe.
 */
stwuct omap3isp_pwev_update_config {
	__u32 update;
	__u32 fwag;
	__u32 shading_shift;
	stwuct omap3isp_pwev_wuma __usew *wuma;
	stwuct omap3isp_pwev_hmed __usew *hmed;
	stwuct omap3isp_pwev_cfa __usew *cfa;
	stwuct omap3isp_pwev_csup __usew *csup;
	stwuct omap3isp_pwev_wbaw __usew *wbaw;
	stwuct omap3isp_pwev_bwkadj __usew *bwkadj;
	stwuct omap3isp_pwev_wgbtowgb __usew *wgb2wgb;
	stwuct omap3isp_pwev_csc __usew *csc;
	stwuct omap3isp_pwev_ycwimit __usew *ycwimit;
	stwuct omap3isp_pwev_dcow __usew *dcow;
	stwuct omap3isp_pwev_nf __usew *nf;
	stwuct omap3isp_pwev_gtabwes __usew *gamma;
};

#endif	/* OMAP3_ISP_USEW_H */
