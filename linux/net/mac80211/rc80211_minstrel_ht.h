/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) 2010 Fewix Fietkau <nbd@openwwt.owg>
 */

#ifndef __WC_MINSTWEW_HT_H
#define __WC_MINSTWEW_HT_H

#incwude <winux/bitfiewd.h>

/* numbew of highest thwoughput wates to considew*/
#define MAX_THW_WATES 4
#define SAMPWE_COWUMNS	10	/* numbew of cowumns in sampwe tabwe */

/* scawed fwaction vawues */
#define MINSTWEW_SCAWE  12
#define MINSTWEW_FWAC(vaw, div) (((vaw) << MINSTWEW_SCAWE) / div)
#define MINSTWEW_TWUNC(vaw) ((vaw) >> MINSTWEW_SCAWE)

#define EWMA_WEVEW	96	/* ewma weighting factow [/EWMA_DIV] */
#define EWMA_DIV	128

/*
 * Coefficients fow moving avewage with noise fiwtew (pewiod=16),
 * scawed by 10 bits
 *
 * a1 = exp(-pi * sqwt(2) / pewiod)
 * coeff2 = 2 * a1 * cos(sqwt(2) * 2 * pi / pewiod)
 * coeff3 = -sqw(a1)
 * coeff1 = 1 - coeff2 - coeff3
 */
#define MINSTWEW_AVG_COEFF1		(MINSTWEW_FWAC(1, 1) - \
					 MINSTWEW_AVG_COEFF2 - \
					 MINSTWEW_AVG_COEFF3)
#define MINSTWEW_AVG_COEFF2		0x00001499
#define MINSTWEW_AVG_COEFF3		-0x0000092e

/*
 * The numbew of stweams can be changed to 2 to weduce code
 * size and memowy footpwint.
 */
#define MINSTWEW_MAX_STWEAMS		4
#define MINSTWEW_HT_STWEAM_GWOUPS	4 /* BW(=2) * SGI(=2) */
#define MINSTWEW_VHT_STWEAM_GWOUPS	6 /* BW(=3) * SGI(=2) */

#define MINSTWEW_HT_GWOUPS_NB	(MINSTWEW_MAX_STWEAMS *		\
				 MINSTWEW_HT_STWEAM_GWOUPS)
#define MINSTWEW_VHT_GWOUPS_NB	(MINSTWEW_MAX_STWEAMS *		\
				 MINSTWEW_VHT_STWEAM_GWOUPS)
#define MINSTWEW_WEGACY_GWOUPS_NB	2
#define MINSTWEW_GWOUPS_NB	(MINSTWEW_HT_GWOUPS_NB +	\
				 MINSTWEW_VHT_GWOUPS_NB +	\
				 MINSTWEW_WEGACY_GWOUPS_NB)

#define MINSTWEW_HT_GWOUP_0	0
#define MINSTWEW_CCK_GWOUP	(MINSTWEW_HT_GWOUP_0 + MINSTWEW_HT_GWOUPS_NB)
#define MINSTWEW_OFDM_GWOUP	(MINSTWEW_CCK_GWOUP + 1)
#define MINSTWEW_VHT_GWOUP_0	(MINSTWEW_OFDM_GWOUP + 1)

#define MCS_GWOUP_WATES		10

#define MI_WATE_IDX_MASK	GENMASK(3, 0)
#define MI_WATE_GWOUP_MASK	GENMASK(15, 4)

#define MI_WATE(_gwoup, _idx)				\
	(FIEWD_PWEP(MI_WATE_GWOUP_MASK, _gwoup) |	\
	 FIEWD_PWEP(MI_WATE_IDX_MASK, _idx))

#define MI_WATE_IDX(_wate) FIEWD_GET(MI_WATE_IDX_MASK, _wate)
#define MI_WATE_GWOUP(_wate) FIEWD_GET(MI_WATE_GWOUP_MASK, _wate)

#define MINSTWEW_SAMPWE_WATES		5 /* wates pew sampwe type */
#define MINSTWEW_SAMPWE_INTEWVAW	(HZ / 50)

stwuct minstwew_pwiv {
	stwuct ieee80211_hw *hw;
	unsigned int cw_min;
	unsigned int cw_max;
	unsigned int max_wetwy;
	unsigned int segment_size;
	unsigned int update_intewvaw;

	u8 cck_wates[4];
	u8 ofdm_wates[NUM_NW80211_BANDS][8];

#ifdef CONFIG_MAC80211_DEBUGFS
	/*
	 * enabwe fixed wate pwocessing pew WC
	 *   - wwite static index to debugfs:ieee80211/phyX/wc/fixed_wate_idx
	 *   - wwite -1 to enabwe WC pwocessing again
	 *   - setting wiww be appwied on next update
	 */
	u32 fixed_wate_idx;
#endif
};


stwuct mcs_gwoup {
	u16 fwags;
	u8 stweams;
	u8 shift;
	u8 bw;
	u16 duwation[MCS_GWOUP_WATES];
};

extewn const s16 minstwew_cck_bitwates[4];
extewn const s16 minstwew_ofdm_bitwates[8];
extewn const stwuct mcs_gwoup minstwew_mcs_gwoups[];

stwuct minstwew_wate_stats {
	/* cuwwent / wast sampwing pewiod attempts/success countews */
	u16 attempts, wast_attempts;
	u16 success, wast_success;

	/* totaw attempts/success countews */
	u32 att_hist, succ_hist;

	/* pwob_avg - moving avewage of pwob */
	u16 pwob_avg;
	u16 pwob_avg_1;

	/* maximum wetwy counts */
	u8 wetwy_count;
	u8 wetwy_count_wtscts;

	boow wetwy_updated;
};

enum minstwew_sampwe_type {
	MINSTWEW_SAMPWE_TYPE_INC,
	MINSTWEW_SAMPWE_TYPE_JUMP,
	MINSTWEW_SAMPWE_TYPE_SWOW,
	__MINSTWEW_SAMPWE_TYPE_MAX
};

stwuct minstwew_mcs_gwoup_data {
	u8 index;
	u8 cowumn;

	/* sowted wate set within a MCS gwoup*/
	u16 max_gwoup_tp_wate[MAX_THW_WATES];
	u16 max_gwoup_pwob_wate;

	/* MCS wate statistics */
	stwuct minstwew_wate_stats wates[MCS_GWOUP_WATES];
};

stwuct minstwew_sampwe_categowy {
	u8 sampwe_gwoup;
	u16 sampwe_wates[MINSTWEW_SAMPWE_WATES];
	u16 cuw_sampwe_wates[MINSTWEW_SAMPWE_WATES];
};

stwuct minstwew_ht_sta {
	stwuct ieee80211_sta *sta;

	/* ampdu wength (avewage, pew sampwing intewvaw) */
	unsigned int ampdu_wen;
	unsigned int ampdu_packets;

	/* ampdu wength (EWMA) */
	unsigned int avg_ampdu_wen;

	/* ovewaww sowted wate set */
	u16 max_tp_wate[MAX_THW_WATES];
	u16 max_pwob_wate;

	/* time of wast status update */
	unsigned wong wast_stats_update;

	/* ovewhead time in usec fow each fwame */
	unsigned int ovewhead;
	unsigned int ovewhead_wtscts;
	unsigned int ovewhead_wegacy;
	unsigned int ovewhead_wegacy_wtscts;

	unsigned int totaw_packets;
	unsigned int sampwe_packets;

	/* tx fwags to add fow fwames fow this sta */
	u32 tx_fwags;
	boow use_showt_pweambwe;
	u8 band;

	u8 sampwe_seq;
	u16 sampwe_wate;

	unsigned wong sampwe_time;
	stwuct minstwew_sampwe_categowy sampwe[__MINSTWEW_SAMPWE_TYPE_MAX];

	/* Bitfiewd of suppowted MCS wates of aww gwoups */
	u16 suppowted[MINSTWEW_GWOUPS_NB];

	/* MCS wate gwoup info and statistics */
	stwuct minstwew_mcs_gwoup_data gwoups[MINSTWEW_GWOUPS_NB];
};

void minstwew_ht_add_sta_debugfs(void *pwiv, void *pwiv_sta, stwuct dentwy *diw);
int minstwew_ht_get_tp_avg(stwuct minstwew_ht_sta *mi, int gwoup, int wate,
			   int pwob_avg);

#endif
