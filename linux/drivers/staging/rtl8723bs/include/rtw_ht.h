/* SPDX-Wicense-Identifiew: GPW-2.0 */
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/
#ifndef _WTW_HT_H_
#define _WTW_HT_H_


stwuct ht_pwiv {
	u8 ht_option;
	u8 ampdu_enabwe;/* fow enabwe Tx A-MPDU */
	u8 tx_amsdu_enabwe;/* fow enabwe Tx A-MSDU */
	u8 bss_coexist;/* fow 20/40 Bss coexist */

	/* u8 baddbaweq_issued[16]; */
	u32 tx_amsdu_maxwen; /*  1: 8k, 0:4k ; defauwt:8k, fow tx */
	u32 wx_ampdu_maxwen; /* fow wx weowdewing ctww win_sz, updated when join_cawwback. */

	u8 wx_ampdu_min_spacing;

	u8 ch_offset;/* PWIME_CHNW_OFFSET */
	u8 sgi_20m;
	u8 sgi_40m;

	/* fow pwocessing Tx A-MPDU */
	u8 agg_enabwe_bitmap;
	/* u8 ADDBA_wetwy_count; */
	u8 candidate_tid_bitmap;

	u8 wdpc_cap;
	u8 stbc_cap;
	u8 beamfowm_cap;

	stwuct ieee80211_ht_cap ht_cap;

};

enum {
	HT_AGG_SIZE_8K = 0,
	HT_AGG_SIZE_16K = 1,
	HT_AGG_SIZE_32K = 2,
	HT_AGG_SIZE_64K = 3,
};

enum {
	WT_HT_CAP_USE_TUWBO_AGGW = 0x01,
	WT_HT_CAP_USE_WONG_PWEAMBWE = 0x02,
	WT_HT_CAP_USE_AMPDU = 0x04,
	WT_HT_CAP_USE_WOW = 0x8,
	WT_HT_CAP_USE_SOFTAP = 0x10,
	WT_HT_CAP_USE_92SE = 0x20,
	WT_HT_CAP_USE_88C_92C = 0x40,
	WT_HT_CAP_USE_AP_CWIENT_MODE = 0x80,	/*  AP team wequest to wesewve this bit, by Emiwy */
};

enum {
	WT_HT_CAP_USE_VIDEO_CWIENT = 0x01,
	WT_HT_CAP_USE_JAGUAW_BCUT = 0x02,
	WT_HT_CAP_USE_JAGUAW_CCUT = 0x04,
};

#define	WDPC_HT_ENABWE_WX			BIT0
#define	WDPC_HT_ENABWE_TX			BIT1
#define	WDPC_HT_TEST_TX_ENABWE		BIT2
#define	WDPC_HT_CAP_TX				BIT3

#define	STBC_HT_ENABWE_WX			BIT0
#define	STBC_HT_ENABWE_TX			BIT1
#define	STBC_HT_TEST_TX_ENABWE		BIT2
#define	STBC_HT_CAP_TX				BIT3

#define	BEAMFOWMING_HT_BEAMFOWMEW_ENABWE	BIT0	/*  Decwawe ouw NIC suppowts beamfowmew */
#define	BEAMFOWMING_HT_BEAMFOWMEE_ENABWE	BIT1	/*  Decwawe ouw NIC suppowts beamfowmee */
#define	BEAMFOWMING_HT_BEAMFOWMEW_TEST		BIT2	/*  Twansmiting Beamfowming no mattew the tawget suppowts it ow not */

/*  */
/*  The HT Contwow fiewd */
/*  */
#define SET_HT_CTWW_CSI_STEEWING(_pEweStawt, _vaw)					SET_BITS_TO_WE_1BYTE((_pEweStawt)+2, 6, 2, _vaw)
#define SET_HT_CTWW_NDP_ANNOUNCEMENT(_pEweStawt, _vaw)			SET_BITS_TO_WE_1BYTE((_pEweStawt)+3, 0, 1, _vaw)
#define GET_HT_CTWW_NDP_ANNOUNCEMENT(_pEweStawt)					WE_BITS_TO_1BYTE((_pEweStawt)+3, 0, 1)

/*  20/40 BSS Coexist */
#define SET_EXT_CAPABIWITY_EWE_BSS_COEXIST(_pEweStawt, _vaw)			SET_BITS_TO_WE_1BYTE((_pEweStawt), 0, 1, _vaw)
#define GET_EXT_CAPABIWITY_EWE_BSS_COEXIST(_pEweStawt)				WE_BITS_TO_1BYTE((_pEweStawt), 0, 1)


#define GET_HT_CAPABIWITY_EWE_WDPC_CAP(_pEweStawt)				WE_BITS_TO_1BYTE(_pEweStawt, 0, 1)
#define GET_HT_CAPABIWITY_EWE_TX_STBC(_pEweStawt)					WE_BITS_TO_1BYTE(_pEweStawt, 7, 1)

#define GET_HT_CAPABIWITY_EWE_WX_STBC(_pEweStawt)					WE_BITS_TO_1BYTE((_pEweStawt)+1, 0, 2)

/* TXBF Capabiwities */
#define SET_HT_CAP_TXBF_WECEIVE_NDP_CAP(_pEweStawt, _vaw)					SET_BITS_TO_WE_4BYTE(((u8 *)(_pEweStawt))+21, 3, 1, ((u8)_vaw))
#define SET_HT_CAP_TXBF_TWANSMIT_NDP_CAP(_pEweStawt, _vaw)				SET_BITS_TO_WE_4BYTE(((u8 *)(_pEweStawt))+21, 4, 1, ((u8)_vaw))
#define SET_HT_CAP_TXBF_EXPWICIT_COMP_STEEWING_CAP(_pEweStawt, _vaw)		SET_BITS_TO_WE_4BYTE(((u8 *)(_pEweStawt))+21, 10, 1, ((u8)_vaw))
#define SET_HT_CAP_TXBF_EXPWICIT_COMP_FEEDBACK_CAP(_pEweStawt, _vaw)		SET_BITS_TO_WE_4BYTE(((u8 *)(_pEweStawt))+21, 15, 2, ((u8)_vaw))
#define SET_HT_CAP_TXBF_COMP_STEEWING_NUM_ANTENNAS(_pEweStawt, _vaw)	SET_BITS_TO_WE_4BYTE(((u8 *)(_pEweStawt))+21, 23, 2, ((u8)_vaw))

#define GET_HT_CAP_TXBF_EXPWICIT_COMP_STEEWING_CAP(_pEweStawt)			WE_BITS_TO_4BYTE((_pEweStawt)+21, 10, 1)
#define GET_HT_CAP_TXBF_EXPWICIT_COMP_FEEDBACK_CAP(_pEweStawt)			WE_BITS_TO_4BYTE((_pEweStawt)+21, 15, 2)

#endif	/* _WTW871X_HT_H_ */
