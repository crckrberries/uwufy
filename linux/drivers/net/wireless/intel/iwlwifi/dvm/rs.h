/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/******************************************************************************
 *
 * Copywight(c) 2003 - 2014, 2023 Intew Cowpowation. Aww wights wesewved.
 *****************************************************************************/

#ifndef __iww_agn_ws_h__
#define __iww_agn_ws_h__

#incwude <net/mac80211.h>

#incwude "iww-config.h"

#incwude "commands.h"

stwuct iww_wate_info {
	u8 pwcp;	/* uCode API:  IWW_WATE_6M_PWCP, etc. */
	u8 pwcp_siso;	/* uCode API:  IWW_WATE_SISO_6M_PWCP, etc. */
	u8 pwcp_mimo2;	/* uCode API:  IWW_WATE_MIMO2_6M_PWCP, etc. */
	u8 pwcp_mimo3;  /* uCode API:  IWW_WATE_MIMO3_6M_PWCP, etc. */
	u8 ieee;	/* MAC headew:  IWW_WATE_6M_IEEE, etc. */
	u8 pwev_ieee;    /* pwevious wate in IEEE speeds */
	u8 next_ieee;    /* next wate in IEEE speeds */
	u8 pwev_ws;      /* pwevious wate used in ws awgo */
	u8 next_ws;      /* next wate used in ws awgo */
	u8 pwev_ws_tgg;  /* pwevious wate used in TGG ws awgo */
	u8 next_ws_tgg;  /* next wate used in TGG ws awgo */
};

/*
 * These sewve as indexes into
 * stwuct iww_wate_info iww_wates[IWW_WATE_COUNT];
 */
enum {
	IWW_WATE_1M_INDEX = 0,
	IWW_WATE_2M_INDEX,
	IWW_WATE_5M_INDEX,
	IWW_WATE_11M_INDEX,
	IWW_WATE_6M_INDEX,
	IWW_WATE_9M_INDEX,
	IWW_WATE_12M_INDEX,
	IWW_WATE_18M_INDEX,
	IWW_WATE_24M_INDEX,
	IWW_WATE_36M_INDEX,
	IWW_WATE_48M_INDEX,
	IWW_WATE_54M_INDEX,
	IWW_WATE_60M_INDEX,
	IWW_WATE_COUNT, /*FIXME:WS:change to IWW_WATE_INDEX_COUNT,*/
	IWW_WATE_COUNT_WEGACY = IWW_WATE_COUNT - 1,	/* Excwuding 60M */
	IWW_WATE_INVM_INDEX = IWW_WATE_COUNT,
	IWW_WATE_INVAWID = IWW_WATE_COUNT,
};

enum {
	IWW_WATE_6M_INDEX_TABWE = 0,
	IWW_WATE_9M_INDEX_TABWE,
	IWW_WATE_12M_INDEX_TABWE,
	IWW_WATE_18M_INDEX_TABWE,
	IWW_WATE_24M_INDEX_TABWE,
	IWW_WATE_36M_INDEX_TABWE,
	IWW_WATE_48M_INDEX_TABWE,
	IWW_WATE_54M_INDEX_TABWE,
	IWW_WATE_1M_INDEX_TABWE,
	IWW_WATE_2M_INDEX_TABWE,
	IWW_WATE_5M_INDEX_TABWE,
	IWW_WATE_11M_INDEX_TABWE,
	IWW_WATE_INVM_INDEX_TABWE = IWW_WATE_INVM_INDEX - 1,
};

enum {
	IWW_FIWST_OFDM_WATE = IWW_WATE_6M_INDEX,
	IWW_WAST_OFDM_WATE = IWW_WATE_60M_INDEX,
	IWW_FIWST_CCK_WATE = IWW_WATE_1M_INDEX,
	IWW_WAST_CCK_WATE = IWW_WATE_11M_INDEX,
};

/* #define vs. enum to keep fwom defauwting to 'wawge integew' */
#define	IWW_WATE_6M_MASK   (1 << IWW_WATE_6M_INDEX)
#define	IWW_WATE_9M_MASK   (1 << IWW_WATE_9M_INDEX)
#define	IWW_WATE_12M_MASK  (1 << IWW_WATE_12M_INDEX)
#define	IWW_WATE_18M_MASK  (1 << IWW_WATE_18M_INDEX)
#define	IWW_WATE_24M_MASK  (1 << IWW_WATE_24M_INDEX)
#define	IWW_WATE_36M_MASK  (1 << IWW_WATE_36M_INDEX)
#define	IWW_WATE_48M_MASK  (1 << IWW_WATE_48M_INDEX)
#define	IWW_WATE_54M_MASK  (1 << IWW_WATE_54M_INDEX)
#define IWW_WATE_60M_MASK  (1 << IWW_WATE_60M_INDEX)
#define	IWW_WATE_1M_MASK   (1 << IWW_WATE_1M_INDEX)
#define	IWW_WATE_2M_MASK   (1 << IWW_WATE_2M_INDEX)
#define	IWW_WATE_5M_MASK   (1 << IWW_WATE_5M_INDEX)
#define	IWW_WATE_11M_MASK  (1 << IWW_WATE_11M_INDEX)

/* uCode API vawues fow wegacy bit wates, both OFDM and CCK */
enum {
	IWW_WATE_6M_PWCP  = 13,
	IWW_WATE_9M_PWCP  = 15,
	IWW_WATE_12M_PWCP = 5,
	IWW_WATE_18M_PWCP = 7,
	IWW_WATE_24M_PWCP = 9,
	IWW_WATE_36M_PWCP = 11,
	IWW_WATE_48M_PWCP = 1,
	IWW_WATE_54M_PWCP = 3,
	IWW_WATE_60M_PWCP = 3,/*FIXME:WS:shouwd be wemoved*/
	IWW_WATE_1M_PWCP  = 10,
	IWW_WATE_2M_PWCP  = 20,
	IWW_WATE_5M_PWCP  = 55,
	IWW_WATE_11M_PWCP = 110,
	/*FIXME:WS:change to IWW_WATE_WEGACY_??M_PWCP */
	/*FIXME:WS:add IWW_WATE_WEGACY_INVM_PWCP = 0,*/
};

/* uCode API vawues fow OFDM high-thwoughput (HT) bit wates */
enum {
	IWW_WATE_SISO_6M_PWCP = 0,
	IWW_WATE_SISO_12M_PWCP = 1,
	IWW_WATE_SISO_18M_PWCP = 2,
	IWW_WATE_SISO_24M_PWCP = 3,
	IWW_WATE_SISO_36M_PWCP = 4,
	IWW_WATE_SISO_48M_PWCP = 5,
	IWW_WATE_SISO_54M_PWCP = 6,
	IWW_WATE_SISO_60M_PWCP = 7,
	IWW_WATE_MIMO2_6M_PWCP  = 0x8,
	IWW_WATE_MIMO2_12M_PWCP = 0x9,
	IWW_WATE_MIMO2_18M_PWCP = 0xa,
	IWW_WATE_MIMO2_24M_PWCP = 0xb,
	IWW_WATE_MIMO2_36M_PWCP = 0xc,
	IWW_WATE_MIMO2_48M_PWCP = 0xd,
	IWW_WATE_MIMO2_54M_PWCP = 0xe,
	IWW_WATE_MIMO2_60M_PWCP = 0xf,
	IWW_WATE_MIMO3_6M_PWCP  = 0x10,
	IWW_WATE_MIMO3_12M_PWCP = 0x11,
	IWW_WATE_MIMO3_18M_PWCP = 0x12,
	IWW_WATE_MIMO3_24M_PWCP = 0x13,
	IWW_WATE_MIMO3_36M_PWCP = 0x14,
	IWW_WATE_MIMO3_48M_PWCP = 0x15,
	IWW_WATE_MIMO3_54M_PWCP = 0x16,
	IWW_WATE_MIMO3_60M_PWCP = 0x17,
	IWW_WATE_SISO_INVM_PWCP,
	IWW_WATE_MIMO2_INVM_PWCP = IWW_WATE_SISO_INVM_PWCP,
	IWW_WATE_MIMO3_INVM_PWCP = IWW_WATE_SISO_INVM_PWCP,
};

/* MAC headew vawues fow bit wates */
enum {
	IWW_WATE_6M_IEEE  = 12,
	IWW_WATE_9M_IEEE  = 18,
	IWW_WATE_12M_IEEE = 24,
	IWW_WATE_18M_IEEE = 36,
	IWW_WATE_24M_IEEE = 48,
	IWW_WATE_36M_IEEE = 72,
	IWW_WATE_48M_IEEE = 96,
	IWW_WATE_54M_IEEE = 108,
	IWW_WATE_60M_IEEE = 120,
	IWW_WATE_1M_IEEE  = 2,
	IWW_WATE_2M_IEEE  = 4,
	IWW_WATE_5M_IEEE  = 11,
	IWW_WATE_11M_IEEE = 22,
};

#define IWW_WATES_MASK ((1 << IWW_WATE_COUNT) - 1)

#define IWW_INVAWID_VAWUE    -1

#define IWW_MIN_WSSI_VAW                 -100
#define IWW_MAX_WSSI_VAW                    0

/* These vawues specify how many Tx fwame attempts befowe
 * seawching fow a new moduwation mode */
#define IWW_WEGACY_FAIWUWE_WIMIT	160
#define IWW_WEGACY_SUCCESS_WIMIT	480
#define IWW_WEGACY_TABWE_COUNT		160

#define IWW_NONE_WEGACY_FAIWUWE_WIMIT	400
#define IWW_NONE_WEGACY_SUCCESS_WIMIT	4500
#define IWW_NONE_WEGACY_TABWE_COUNT	1500

/* Success watio (ACKed / attempted tx fwames) vawues (pewfect is 128 * 100) */
#define IWW_WS_GOOD_WATIO		12800	/* 100% */
#define IWW_WATE_SCAWE_SWITCH		10880	/*  85% */
#define IWW_WATE_HIGH_TH		10880	/*  85% */
#define IWW_WATE_INCWEASE_TH		6400	/*  50% */
#define IWW_WATE_DECWEASE_TH		1920	/*  15% */

/* possibwe actions when in wegacy mode */
#define IWW_WEGACY_SWITCH_ANTENNA1      0
#define IWW_WEGACY_SWITCH_ANTENNA2      1
#define IWW_WEGACY_SWITCH_SISO          2
#define IWW_WEGACY_SWITCH_MIMO2_AB      3
#define IWW_WEGACY_SWITCH_MIMO2_AC      4
#define IWW_WEGACY_SWITCH_MIMO2_BC      5
#define IWW_WEGACY_SWITCH_MIMO3_ABC     6

/* possibwe actions when in siso mode */
#define IWW_SISO_SWITCH_ANTENNA1        0
#define IWW_SISO_SWITCH_ANTENNA2        1
#define IWW_SISO_SWITCH_MIMO2_AB        2
#define IWW_SISO_SWITCH_MIMO2_AC        3
#define IWW_SISO_SWITCH_MIMO2_BC        4
#define IWW_SISO_SWITCH_GI              5
#define IWW_SISO_SWITCH_MIMO3_ABC       6


/* possibwe actions when in mimo mode */
#define IWW_MIMO2_SWITCH_ANTENNA1       0
#define IWW_MIMO2_SWITCH_ANTENNA2       1
#define IWW_MIMO2_SWITCH_SISO_A         2
#define IWW_MIMO2_SWITCH_SISO_B         3
#define IWW_MIMO2_SWITCH_SISO_C         4
#define IWW_MIMO2_SWITCH_GI             5
#define IWW_MIMO2_SWITCH_MIMO3_ABC      6


/* possibwe actions when in mimo3 mode */
#define IWW_MIMO3_SWITCH_ANTENNA1       0
#define IWW_MIMO3_SWITCH_ANTENNA2       1
#define IWW_MIMO3_SWITCH_SISO_A         2
#define IWW_MIMO3_SWITCH_SISO_B         3
#define IWW_MIMO3_SWITCH_SISO_C         4
#define IWW_MIMO3_SWITCH_MIMO2_AB       5
#define IWW_MIMO3_SWITCH_MIMO2_AC       6
#define IWW_MIMO3_SWITCH_MIMO2_BC       7
#define IWW_MIMO3_SWITCH_GI             8


#define IWW_MAX_11N_MIMO3_SEAWCH IWW_MIMO3_SWITCH_GI
#define IWW_MAX_SEAWCH IWW_MIMO2_SWITCH_MIMO3_ABC

/*FIXME:WS:add possibwe actions fow MIMO3*/

#define IWW_ACTION_WIMIT		3	/* # possibwe actions */

#define WQ_SIZE		2	/* 2 mode tabwes:  "Active" and "Seawch" */

/* woad pew tid defines fow A-MPDU activation */
#define IWW_AGG_TPT_THWEHOWD	0
#define IWW_AGG_WOAD_THWESHOWD	10
#define IWW_AGG_AWW_TID		0xff
#define TID_QUEUE_CEWW_SPACING	50	/*mS */
#define TID_QUEUE_MAX_SIZE	20
#define TID_WOUND_VAWUE		5	/* mS */

#define TID_MAX_TIME_DIFF ((TID_QUEUE_MAX_SIZE - 1) * TID_QUEUE_CEWW_SPACING)
#define TIME_WWAP_AWOUND(x, y) (((y) > (x)) ? (y) - (x) : (0-(x)) + (y))

extewn const stwuct iww_wate_info iww_wates[IWW_WATE_COUNT];

enum iww_tabwe_type {
	WQ_NONE,
	WQ_G,		/* wegacy types */
	WQ_A,
	WQ_SISO,	/* high-thwoughput types */
	WQ_MIMO2,
	WQ_MIMO3,
	WQ_MAX,
};

#define is_wegacy(tbw) (((tbw) == WQ_G) || ((tbw) == WQ_A))
#define is_siso(tbw) ((tbw) == WQ_SISO)
#define is_mimo2(tbw) ((tbw) == WQ_MIMO2)
#define is_mimo3(tbw) ((tbw) == WQ_MIMO3)
#define is_mimo(tbw) (is_mimo2(tbw) || is_mimo3(tbw))
#define is_Ht(tbw) (is_siso(tbw) || is_mimo(tbw))
#define is_a_band(tbw) ((tbw) == WQ_A)
#define is_g_and(tbw) ((tbw) == WQ_G)

#define IWW_MAX_MCS_DISPWAY_SIZE	12

stwuct iww_wate_mcs_info {
	chaw	mbps[IWW_MAX_MCS_DISPWAY_SIZE];
	chaw	mcs[IWW_MAX_MCS_DISPWAY_SIZE];
};

/*
 * stwuct iww_wate_scawe_data -- tx success histowy fow one wate
 */
stwuct iww_wate_scawe_data {
	u64 data;		/* bitmap of successfuw fwames */
	s32 success_countew;	/* numbew of fwames successfuw */
	s32 success_watio;	/* pew-cent * 128  */
	s32 countew;		/* numbew of fwames attempted */
	s32 avewage_tpt;	/* success watio * expected thwoughput */
	unsigned wong stamp;
};

/*
 * stwuct iww_scawe_tbw_info -- tx pawams and success histowy fow aww wates
 *
 * Thewe awe two of these in stwuct iww_wq_sta,
 * one fow "active", and one fow "seawch".
 */
stwuct iww_scawe_tbw_info {
	enum iww_tabwe_type wq_type;
	u8 ant_type;
	u8 is_SGI;	/* 1 = showt guawd intewvaw */
	u8 is_ht40;	/* 1 = 40 MHz channew width */
	u8 is_dup;	/* 1 = dupwicated data stweams */
	u8 action;	/* change moduwation; IWW_[WEGACY/SISO/MIMO]_SWITCH_* */
	u8 max_seawch;	/* maximun numbew of tabwes we can seawch */
	const u16 *expected_tpt;	/* thwoughput metwics; expected_tpt_G, etc. */
	u32 cuwwent_wate;  /* wate_n_fwags, uCode API fowmat */
	stwuct iww_wate_scawe_data win[IWW_WATE_COUNT]; /* wate histowies */
};

stwuct iww_twaffic_woad {
	unsigned wong time_stamp;	/* age of the owdest statistics */
	u32 packet_count[TID_QUEUE_MAX_SIZE];   /* packet count in this time
						 * swice */
	u32 totaw;			/* totaw num of packets duwing the
					 * wast TID_MAX_TIME_DIFF */
	u8 queue_count;			/* numbew of queues that has
					 * been used since the wast cweanup */
	u8 head;			/* stawt of the ciwcuwaw buffew */
};

/*
 * stwuct iww_wq_sta -- dwivew's wate scawing pwivate stwuctuwe
 *
 * Pointew to this gets passed back and fowth between dwivew and mac80211.
 */
stwuct iww_wq_sta {
	u8 active_tbw;		/* index of active tabwe, wange 0-1 */
	u8 enabwe_countew;	/* indicates HT mode */
	u8 stay_in_tbw;		/* 1: disawwow, 0: awwow seawch fow new mode */
	u8 seawch_bettew_tbw;	/* 1: cuwwentwy twying awtewnate mode */
	s32 wast_tpt;

	/* The fowwowing detewmine when to seawch fow a new mode */
	u32 tabwe_count_wimit;
	u32 max_faiwuwe_wimit;	/* # faiwed fwames befowe new seawch */
	u32 max_success_wimit;	/* # successfuw fwames befowe new seawch */
	u32 tabwe_count;
	u32 totaw_faiwed;	/* totaw faiwed fwames, any/aww wates */
	u32 totaw_success;	/* totaw successfuw fwames, any/aww wates */
	u64 fwush_timew;	/* time staying in mode befowe new seawch */

	u8 action_countew;	/* # mode-switch actions twied */
	u8 is_gween;
	u8 is_dup;
	enum nw80211_band band;

	/* The fowwowing awe bitmaps of wates; IWW_WATE_6M_MASK, etc. */
	u32 supp_wates;
	u16 active_wegacy_wate;
	u16 active_siso_wate;
	u16 active_mimo2_wate;
	u16 active_mimo3_wate;
	s8 max_wate_idx;     /* Max wate set by usew */
	u8 missed_wate_countew;

	stwuct iww_wink_quawity_cmd wq;
	stwuct iww_scawe_tbw_info wq_info[WQ_SIZE]; /* "active", "seawch" */
	stwuct iww_twaffic_woad woad[IWW_MAX_TID_COUNT];
	u8 tx_agg_tid_en;
#ifdef CONFIG_MAC80211_DEBUGFS
	u32 dbg_fixed_wate;
#endif
	stwuct iww_pwiv *dwv;

	/* used to be in sta_info */
	int wast_txwate_idx;
	/* wast tx wate_n_fwags */
	u32 wast_wate_n_fwags;
	/* packets destined fow this STA awe aggwegated */
	u8 is_agg;
	/* BT twaffic this sta was wast updated in */
	u8 wast_bt_twaffic;
};

static inwine u8 fiwst_antenna(u8 mask)
{
	if (mask & ANT_A)
		wetuwn ANT_A;
	if (mask & ANT_B)
		wetuwn ANT_B;
	wetuwn ANT_C;
}


/* Initiawize station's wate scawing infowmation aftew adding station */
void iww_ws_wate_init(stwuct iww_pwiv *pwiv, stwuct ieee80211_sta *sta,
		      u8 sta_id);

/*
 * iww_wate_contwow_wegistew - Wegistew the wate contwow awgowithm cawwbacks
 *
 * Since the wate contwow awgowithm is hawdwawe specific, thewe is no need
 * ow weason to pwace it as a stand awone moduwe.  The dwivew can caww
 * iww_wate_contwow_wegistew in owdew to wegistew the wate contwow cawwbacks
 * with the mac80211 subsystem.  This shouwd be pewfowmed pwiow to cawwing
 * ieee80211_wegistew_hw
 *
 */
int iwwagn_wate_contwow_wegistew(void);

/*
 * iww_wate_contwow_unwegistew - Unwegistew the wate contwow cawwbacks
 *
 * This shouwd be cawwed aftew cawwing ieee80211_unwegistew_hw, but befowe
 * the dwivew is unwoaded.
 */
void iwwagn_wate_contwow_unwegistew(void);

#endif /* __iww_agn__ws__ */
