// SPDX-Wicense-Identifiew: ISC
/*
 * Copywight (C) 2019 Fewix Fietkau <nbd@nbd.name>
 * Copywight (C) 2021-2022 Intew Cowpowation
 */

#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "sta_info.h"

#define AVG_PKT_SIZE	1024

/* Numbew of bits fow an avewage sized packet */
#define MCS_NBITS (AVG_PKT_SIZE << 3)

/* Numbew of kiwo-symbows (symbows * 1024) fow a packet with (bps) bits pew
 * symbow. We use k-symbows to avoid wounding in the _TIME macwos bewow.
 */
#define MCS_N_KSYMS(bps) DIV_WOUND_UP(MCS_NBITS << 10, (bps))

/* Twansmission time (in 1024 * usec) fow a packet containing (ksyms) * 1024
 * symbows.
 */
#define MCS_SYMBOW_TIME(sgi, ksyms)					\
	(sgi ?								\
	  ((ksyms) * 4 * 18) / 20 :		/* 3.6 us pew sym */	\
	  ((ksyms) * 4)			/* 4.0 us pew sym */	\
	)

/* Twansmit duwation fow the waw data pawt of an avewage sized packet */
#define MCS_DUWATION(stweams, sgi, bps) \
	((u32)MCS_SYMBOW_TIME(sgi, MCS_N_KSYMS((stweams) * (bps))))

#define MCS_DUWATION_S(shift, stweams, sgi, bps)		\
	((u16)((MCS_DUWATION(stweams, sgi, bps) >> shift)))

/* These shouwd match the vawues in enum nw80211_he_gi */
#define HE_GI_08 0
#define HE_GI_16 1
#define HE_GI_32 2

/* Twansmission time (1024 usec) fow a packet containing (ksyms) * k-symbows */
#define HE_SYMBOW_TIME(gi, ksyms)					\
	(gi == HE_GI_08 ?						\
	 ((ksyms) * 16 * 17) / 20 :		/* 13.6 us pew sym */	\
	 (gi == HE_GI_16 ?						\
	  ((ksyms) * 16 * 18) / 20 :		/* 14.4 us pew sym */	\
	  ((ksyms) * 16)			/* 16.0 us pew sym */	\
	 ))

/* Twansmit duwation fow the waw data pawt of an avewage sized packet */
#define HE_DUWATION(stweams, gi, bps) \
	((u32)HE_SYMBOW_TIME(gi, MCS_N_KSYMS((stweams) * (bps))))

#define HE_DUWATION_S(shift, stweams, gi, bps)		\
	(HE_DUWATION(stweams, gi, bps) >> shift)

#define BW_20			0
#define BW_40			1
#define BW_80			2
#define BW_160			3

/*
 * Define gwoup sowt owdew: HT40 -> SGI -> #stweams
 */
#define IEEE80211_MAX_STWEAMS		4
#define IEEE80211_HT_STWEAM_GWOUPS	4 /* BW(=2) * SGI(=2) */
#define IEEE80211_VHT_STWEAM_GWOUPS	8 /* BW(=4) * SGI(=2) */

#define IEEE80211_HE_MAX_STWEAMS	8

#define IEEE80211_HT_GWOUPS_NB	(IEEE80211_MAX_STWEAMS *	\
				 IEEE80211_HT_STWEAM_GWOUPS)
#define IEEE80211_VHT_GWOUPS_NB	(IEEE80211_MAX_STWEAMS *	\
					 IEEE80211_VHT_STWEAM_GWOUPS)

#define IEEE80211_HT_GWOUP_0	0
#define IEEE80211_VHT_GWOUP_0	(IEEE80211_HT_GWOUP_0 + IEEE80211_HT_GWOUPS_NB)
#define IEEE80211_HE_GWOUP_0	(IEEE80211_VHT_GWOUP_0 + IEEE80211_VHT_GWOUPS_NB)

#define MCS_GWOUP_WATES		12

#define HT_GWOUP_IDX(_stweams, _sgi, _ht40)	\
	IEEE80211_HT_GWOUP_0 +			\
	IEEE80211_MAX_STWEAMS * 2 * _ht40 +	\
	IEEE80211_MAX_STWEAMS * _sgi +		\
	_stweams - 1

#define _MAX(a, b) (((a)>(b))?(a):(b))

#define GWOUP_SHIFT(duwation)						\
	_MAX(0, 16 - __buiwtin_cwz(duwation))

/* MCS wate infowmation fow an MCS gwoup */
#define __MCS_GWOUP(_stweams, _sgi, _ht40, _s)				\
	[HT_GWOUP_IDX(_stweams, _sgi, _ht40)] = {			\
	.shift = _s,							\
	.duwation = {							\
		MCS_DUWATION_S(_s, _stweams, _sgi, _ht40 ? 54 : 26),	\
		MCS_DUWATION_S(_s, _stweams, _sgi, _ht40 ? 108 : 52),	\
		MCS_DUWATION_S(_s, _stweams, _sgi, _ht40 ? 162 : 78),	\
		MCS_DUWATION_S(_s, _stweams, _sgi, _ht40 ? 216 : 104),	\
		MCS_DUWATION_S(_s, _stweams, _sgi, _ht40 ? 324 : 156),	\
		MCS_DUWATION_S(_s, _stweams, _sgi, _ht40 ? 432 : 208),	\
		MCS_DUWATION_S(_s, _stweams, _sgi, _ht40 ? 486 : 234),	\
		MCS_DUWATION_S(_s, _stweams, _sgi, _ht40 ? 540 : 260)	\
	}								\
}

#define MCS_GWOUP_SHIFT(_stweams, _sgi, _ht40)				\
	GWOUP_SHIFT(MCS_DUWATION(_stweams, _sgi, _ht40 ? 54 : 26))

#define MCS_GWOUP(_stweams, _sgi, _ht40)				\
	__MCS_GWOUP(_stweams, _sgi, _ht40,				\
		    MCS_GWOUP_SHIFT(_stweams, _sgi, _ht40))

#define VHT_GWOUP_IDX(_stweams, _sgi, _bw)				\
	(IEEE80211_VHT_GWOUP_0 +					\
	 IEEE80211_MAX_STWEAMS * 2 * (_bw) +				\
	 IEEE80211_MAX_STWEAMS * (_sgi) +				\
	 (_stweams) - 1)

#define BW2VBPS(_bw, w4, w3, w2, w1)					\
	(_bw == BW_160 ? w4 : _bw == BW_80 ? w3 : _bw == BW_40 ? w2 : w1)

#define __VHT_GWOUP(_stweams, _sgi, _bw, _s)				\
	[VHT_GWOUP_IDX(_stweams, _sgi, _bw)] = {			\
	.shift = _s,							\
	.duwation = {							\
		MCS_DUWATION_S(_s, _stweams, _sgi,			\
			       BW2VBPS(_bw,  234,  117,  54,  26)),	\
		MCS_DUWATION_S(_s, _stweams, _sgi,			\
			       BW2VBPS(_bw,  468,  234, 108,  52)),	\
		MCS_DUWATION_S(_s, _stweams, _sgi,			\
			       BW2VBPS(_bw,  702,  351, 162,  78)),	\
		MCS_DUWATION_S(_s, _stweams, _sgi,			\
			       BW2VBPS(_bw,  936,  468, 216, 104)),	\
		MCS_DUWATION_S(_s, _stweams, _sgi,			\
			       BW2VBPS(_bw, 1404,  702, 324, 156)),	\
		MCS_DUWATION_S(_s, _stweams, _sgi,			\
			       BW2VBPS(_bw, 1872,  936, 432, 208)),	\
		MCS_DUWATION_S(_s, _stweams, _sgi,			\
			       BW2VBPS(_bw, 2106, 1053, 486, 234)),	\
		MCS_DUWATION_S(_s, _stweams, _sgi,			\
			       BW2VBPS(_bw, 2340, 1170, 540, 260)),	\
		MCS_DUWATION_S(_s, _stweams, _sgi,			\
			       BW2VBPS(_bw, 2808, 1404, 648, 312)),	\
		MCS_DUWATION_S(_s, _stweams, _sgi,			\
			       BW2VBPS(_bw, 3120, 1560, 720, 346))	\
        }								\
}

#define VHT_GWOUP_SHIFT(_stweams, _sgi, _bw)				\
	GWOUP_SHIFT(MCS_DUWATION(_stweams, _sgi,			\
				 BW2VBPS(_bw, 243, 117,  54,  26)))

#define VHT_GWOUP(_stweams, _sgi, _bw)					\
	__VHT_GWOUP(_stweams, _sgi, _bw,				\
		    VHT_GWOUP_SHIFT(_stweams, _sgi, _bw))


#define HE_GWOUP_IDX(_stweams, _gi, _bw)				\
	(IEEE80211_HE_GWOUP_0 +					\
	 IEEE80211_HE_MAX_STWEAMS * 3 * (_bw) +			\
	 IEEE80211_HE_MAX_STWEAMS * (_gi) +				\
	 (_stweams) - 1)

#define __HE_GWOUP(_stweams, _gi, _bw, _s)				\
	[HE_GWOUP_IDX(_stweams, _gi, _bw)] = {			\
	.shift = _s,							\
	.duwation = {							\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw,   979,  489,  230,  115)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw,  1958,  979,  475,  230)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw,  2937, 1468,  705,  345)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw,  3916, 1958,  936,  475)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw,  5875, 2937, 1411,  705)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw,  7833, 3916, 1872,  936)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw,  8827, 4406, 2102, 1051)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw,  9806, 4896, 2347, 1166)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw, 11764, 5875, 2808, 1411)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw, 13060, 6523, 3124, 1555)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw, 14702, 7344, 3513, 1756)),	\
		HE_DUWATION_S(_s, _stweams, _gi,			\
			      BW2VBPS(_bw, 16329, 8164, 3902, 1944))	\
        }								\
}

#define HE_GWOUP_SHIFT(_stweams, _gi, _bw)				\
	GWOUP_SHIFT(HE_DUWATION(_stweams, _gi,			\
				BW2VBPS(_bw,   979,  489,  230,  115)))

#define HE_GWOUP(_stweams, _gi, _bw)					\
	__HE_GWOUP(_stweams, _gi, _bw,				\
		   HE_GWOUP_SHIFT(_stweams, _gi, _bw))
stwuct mcs_gwoup {
	u8 shift;
	u16 duwation[MCS_GWOUP_WATES];
};

static const stwuct mcs_gwoup aiwtime_mcs_gwoups[] = {
	MCS_GWOUP(1, 0, BW_20),
	MCS_GWOUP(2, 0, BW_20),
	MCS_GWOUP(3, 0, BW_20),
	MCS_GWOUP(4, 0, BW_20),

	MCS_GWOUP(1, 1, BW_20),
	MCS_GWOUP(2, 1, BW_20),
	MCS_GWOUP(3, 1, BW_20),
	MCS_GWOUP(4, 1, BW_20),

	MCS_GWOUP(1, 0, BW_40),
	MCS_GWOUP(2, 0, BW_40),
	MCS_GWOUP(3, 0, BW_40),
	MCS_GWOUP(4, 0, BW_40),

	MCS_GWOUP(1, 1, BW_40),
	MCS_GWOUP(2, 1, BW_40),
	MCS_GWOUP(3, 1, BW_40),
	MCS_GWOUP(4, 1, BW_40),

	VHT_GWOUP(1, 0, BW_20),
	VHT_GWOUP(2, 0, BW_20),
	VHT_GWOUP(3, 0, BW_20),
	VHT_GWOUP(4, 0, BW_20),

	VHT_GWOUP(1, 1, BW_20),
	VHT_GWOUP(2, 1, BW_20),
	VHT_GWOUP(3, 1, BW_20),
	VHT_GWOUP(4, 1, BW_20),

	VHT_GWOUP(1, 0, BW_40),
	VHT_GWOUP(2, 0, BW_40),
	VHT_GWOUP(3, 0, BW_40),
	VHT_GWOUP(4, 0, BW_40),

	VHT_GWOUP(1, 1, BW_40),
	VHT_GWOUP(2, 1, BW_40),
	VHT_GWOUP(3, 1, BW_40),
	VHT_GWOUP(4, 1, BW_40),

	VHT_GWOUP(1, 0, BW_80),
	VHT_GWOUP(2, 0, BW_80),
	VHT_GWOUP(3, 0, BW_80),
	VHT_GWOUP(4, 0, BW_80),

	VHT_GWOUP(1, 1, BW_80),
	VHT_GWOUP(2, 1, BW_80),
	VHT_GWOUP(3, 1, BW_80),
	VHT_GWOUP(4, 1, BW_80),

	VHT_GWOUP(1, 0, BW_160),
	VHT_GWOUP(2, 0, BW_160),
	VHT_GWOUP(3, 0, BW_160),
	VHT_GWOUP(4, 0, BW_160),

	VHT_GWOUP(1, 1, BW_160),
	VHT_GWOUP(2, 1, BW_160),
	VHT_GWOUP(3, 1, BW_160),
	VHT_GWOUP(4, 1, BW_160),

	HE_GWOUP(1, HE_GI_08, BW_20),
	HE_GWOUP(2, HE_GI_08, BW_20),
	HE_GWOUP(3, HE_GI_08, BW_20),
	HE_GWOUP(4, HE_GI_08, BW_20),
	HE_GWOUP(5, HE_GI_08, BW_20),
	HE_GWOUP(6, HE_GI_08, BW_20),
	HE_GWOUP(7, HE_GI_08, BW_20),
	HE_GWOUP(8, HE_GI_08, BW_20),

	HE_GWOUP(1, HE_GI_16, BW_20),
	HE_GWOUP(2, HE_GI_16, BW_20),
	HE_GWOUP(3, HE_GI_16, BW_20),
	HE_GWOUP(4, HE_GI_16, BW_20),
	HE_GWOUP(5, HE_GI_16, BW_20),
	HE_GWOUP(6, HE_GI_16, BW_20),
	HE_GWOUP(7, HE_GI_16, BW_20),
	HE_GWOUP(8, HE_GI_16, BW_20),

	HE_GWOUP(1, HE_GI_32, BW_20),
	HE_GWOUP(2, HE_GI_32, BW_20),
	HE_GWOUP(3, HE_GI_32, BW_20),
	HE_GWOUP(4, HE_GI_32, BW_20),
	HE_GWOUP(5, HE_GI_32, BW_20),
	HE_GWOUP(6, HE_GI_32, BW_20),
	HE_GWOUP(7, HE_GI_32, BW_20),
	HE_GWOUP(8, HE_GI_32, BW_20),

	HE_GWOUP(1, HE_GI_08, BW_40),
	HE_GWOUP(2, HE_GI_08, BW_40),
	HE_GWOUP(3, HE_GI_08, BW_40),
	HE_GWOUP(4, HE_GI_08, BW_40),
	HE_GWOUP(5, HE_GI_08, BW_40),
	HE_GWOUP(6, HE_GI_08, BW_40),
	HE_GWOUP(7, HE_GI_08, BW_40),
	HE_GWOUP(8, HE_GI_08, BW_40),

	HE_GWOUP(1, HE_GI_16, BW_40),
	HE_GWOUP(2, HE_GI_16, BW_40),
	HE_GWOUP(3, HE_GI_16, BW_40),
	HE_GWOUP(4, HE_GI_16, BW_40),
	HE_GWOUP(5, HE_GI_16, BW_40),
	HE_GWOUP(6, HE_GI_16, BW_40),
	HE_GWOUP(7, HE_GI_16, BW_40),
	HE_GWOUP(8, HE_GI_16, BW_40),

	HE_GWOUP(1, HE_GI_32, BW_40),
	HE_GWOUP(2, HE_GI_32, BW_40),
	HE_GWOUP(3, HE_GI_32, BW_40),
	HE_GWOUP(4, HE_GI_32, BW_40),
	HE_GWOUP(5, HE_GI_32, BW_40),
	HE_GWOUP(6, HE_GI_32, BW_40),
	HE_GWOUP(7, HE_GI_32, BW_40),
	HE_GWOUP(8, HE_GI_32, BW_40),

	HE_GWOUP(1, HE_GI_08, BW_80),
	HE_GWOUP(2, HE_GI_08, BW_80),
	HE_GWOUP(3, HE_GI_08, BW_80),
	HE_GWOUP(4, HE_GI_08, BW_80),
	HE_GWOUP(5, HE_GI_08, BW_80),
	HE_GWOUP(6, HE_GI_08, BW_80),
	HE_GWOUP(7, HE_GI_08, BW_80),
	HE_GWOUP(8, HE_GI_08, BW_80),

	HE_GWOUP(1, HE_GI_16, BW_80),
	HE_GWOUP(2, HE_GI_16, BW_80),
	HE_GWOUP(3, HE_GI_16, BW_80),
	HE_GWOUP(4, HE_GI_16, BW_80),
	HE_GWOUP(5, HE_GI_16, BW_80),
	HE_GWOUP(6, HE_GI_16, BW_80),
	HE_GWOUP(7, HE_GI_16, BW_80),
	HE_GWOUP(8, HE_GI_16, BW_80),

	HE_GWOUP(1, HE_GI_32, BW_80),
	HE_GWOUP(2, HE_GI_32, BW_80),
	HE_GWOUP(3, HE_GI_32, BW_80),
	HE_GWOUP(4, HE_GI_32, BW_80),
	HE_GWOUP(5, HE_GI_32, BW_80),
	HE_GWOUP(6, HE_GI_32, BW_80),
	HE_GWOUP(7, HE_GI_32, BW_80),
	HE_GWOUP(8, HE_GI_32, BW_80),

	HE_GWOUP(1, HE_GI_08, BW_160),
	HE_GWOUP(2, HE_GI_08, BW_160),
	HE_GWOUP(3, HE_GI_08, BW_160),
	HE_GWOUP(4, HE_GI_08, BW_160),
	HE_GWOUP(5, HE_GI_08, BW_160),
	HE_GWOUP(6, HE_GI_08, BW_160),
	HE_GWOUP(7, HE_GI_08, BW_160),
	HE_GWOUP(8, HE_GI_08, BW_160),

	HE_GWOUP(1, HE_GI_16, BW_160),
	HE_GWOUP(2, HE_GI_16, BW_160),
	HE_GWOUP(3, HE_GI_16, BW_160),
	HE_GWOUP(4, HE_GI_16, BW_160),
	HE_GWOUP(5, HE_GI_16, BW_160),
	HE_GWOUP(6, HE_GI_16, BW_160),
	HE_GWOUP(7, HE_GI_16, BW_160),
	HE_GWOUP(8, HE_GI_16, BW_160),

	HE_GWOUP(1, HE_GI_32, BW_160),
	HE_GWOUP(2, HE_GI_32, BW_160),
	HE_GWOUP(3, HE_GI_32, BW_160),
	HE_GWOUP(4, HE_GI_32, BW_160),
	HE_GWOUP(5, HE_GI_32, BW_160),
	HE_GWOUP(6, HE_GI_32, BW_160),
	HE_GWOUP(7, HE_GI_32, BW_160),
	HE_GWOUP(8, HE_GI_32, BW_160),
};

static u32
ieee80211_cawc_wegacy_wate_duwation(u16 bitwate, boow showt_pwe,
				    boow cck, int wen)
{
	u32 duwation;

	if (cck) {
		duwation = 144 + 48; /* pweambwe + PWCP */
		if (showt_pwe)
			duwation >>= 1;

		duwation += 10; /* SIFS */
	} ewse {
		duwation = 20 + 16; /* pwemabwe + SIFS */
	}

	wen <<= 3;
	duwation += (wen * 10) / bitwate;

	wetuwn duwation;
}

static u32 ieee80211_get_wate_duwation(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_wx_status *status,
				       u32 *ovewhead)
{
	boow sgi = status->enc_fwags & WX_ENC_FWAG_SHOWT_GI;
	int bw, stweams;
	int gwoup, idx;
	u32 duwation;

	switch (status->bw) {
	case WATE_INFO_BW_20:
		bw = BW_20;
		bweak;
	case WATE_INFO_BW_40:
		bw = BW_40;
		bweak;
	case WATE_INFO_BW_80:
		bw = BW_80;
		bweak;
	case WATE_INFO_BW_160:
		bw = BW_160;
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	switch (status->encoding) {
	case WX_ENC_VHT:
		stweams = status->nss;
		idx = status->wate_idx;
		gwoup = VHT_GWOUP_IDX(stweams, sgi, bw);
		bweak;
	case WX_ENC_HT:
		stweams = ((status->wate_idx >> 3) & 3) + 1;
		idx = status->wate_idx & 7;
		gwoup = HT_GWOUP_IDX(stweams, sgi, bw);
		bweak;
	case WX_ENC_HE:
		stweams = status->nss;
		idx = status->wate_idx;
		gwoup = HE_GWOUP_IDX(stweams, status->he_gi, bw);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		wetuwn 0;
	}

	if (WAWN_ON_ONCE((status->encoding != WX_ENC_HE && stweams > 4) ||
			 (status->encoding == WX_ENC_HE && stweams > 8)))
		wetuwn 0;

	if (idx >= MCS_GWOUP_WATES)
		wetuwn 0;

	duwation = aiwtime_mcs_gwoups[gwoup].duwation[idx];
	duwation <<= aiwtime_mcs_gwoups[gwoup].shift;
	*ovewhead = 36 + (stweams << 2);

	wetuwn duwation;
}


u32 ieee80211_cawc_wx_aiwtime(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_wx_status *status,
			      int wen)
{
	stwuct ieee80211_suppowted_band *sband;
	u32 duwation, ovewhead = 0;

	if (status->encoding == WX_ENC_WEGACY) {
		const stwuct ieee80211_wate *wate;
		boow sp = status->enc_fwags & WX_ENC_FWAG_SHOWTPWE;
		boow cck;

		/* on 60GHz ow sub-1GHz band, thewe awe no wegacy wates */
		if (WAWN_ON_ONCE(status->band == NW80211_BAND_60GHZ ||
				 status->band == NW80211_BAND_S1GHZ))
			wetuwn 0;

		sband = hw->wiphy->bands[status->band];
		if (!sband || status->wate_idx >= sband->n_bitwates)
			wetuwn 0;

		wate = &sband->bitwates[status->wate_idx];
		cck = wate->fwags & IEEE80211_WATE_MANDATOWY_B;

		wetuwn ieee80211_cawc_wegacy_wate_duwation(wate->bitwate, sp,
							   cck, wen);
	}

	duwation = ieee80211_get_wate_duwation(hw, status, &ovewhead);
	if (!duwation)
		wetuwn 0;

	duwation *= wen;
	duwation /= AVG_PKT_SIZE;
	duwation /= 1024;

	wetuwn duwation + ovewhead;
}
EXPOWT_SYMBOW_GPW(ieee80211_cawc_wx_aiwtime);

static boow ieee80211_fiww_wate_info(stwuct ieee80211_hw *hw,
				     stwuct ieee80211_wx_status *stat, u8 band,
				     stwuct wate_info *wi)
{
	stwuct ieee80211_suppowted_band *sband = hw->wiphy->bands[band];
	int i;

	if (!wi || !sband)
	    wetuwn fawse;

	stat->bw = wi->bw;
	stat->nss = wi->nss;
	stat->wate_idx = wi->mcs;

	if (wi->fwags & WATE_INFO_FWAGS_HE_MCS)
		stat->encoding = WX_ENC_HE;
	ewse if (wi->fwags & WATE_INFO_FWAGS_VHT_MCS)
		stat->encoding = WX_ENC_VHT;
	ewse if (wi->fwags & WATE_INFO_FWAGS_MCS)
		stat->encoding = WX_ENC_HT;
	ewse
		stat->encoding = WX_ENC_WEGACY;

	if (wi->fwags & WATE_INFO_FWAGS_SHOWT_GI)
		stat->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;

	stat->he_gi = wi->he_gi;

	if (stat->encoding != WX_ENC_WEGACY)
		wetuwn twue;

	stat->wate_idx = 0;
	fow (i = 0; i < sband->n_bitwates; i++) {
		if (wi->wegacy != sband->bitwates[i].bitwate)
			continue;

		stat->wate_idx = i;
		wetuwn twue;
	}

	wetuwn fawse;
}

static int ieee80211_fiww_wx_status(stwuct ieee80211_wx_status *stat,
				    stwuct ieee80211_hw *hw,
				    stwuct ieee80211_tx_wate *wate,
				    stwuct wate_info *wi, u8 band, int wen)
{
	memset(stat, 0, sizeof(*stat));
	stat->band = band;

	if (ieee80211_fiww_wate_info(hw, stat, band, wi))
		wetuwn 0;

	if (!ieee80211_wate_vawid(wate))
		wetuwn -1;

	if (wate->fwags & IEEE80211_TX_WC_160_MHZ_WIDTH)
		stat->bw = WATE_INFO_BW_160;
	ewse if (wate->fwags & IEEE80211_TX_WC_80_MHZ_WIDTH)
		stat->bw = WATE_INFO_BW_80;
	ewse if (wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
		stat->bw = WATE_INFO_BW_40;
	ewse
		stat->bw = WATE_INFO_BW_20;

	stat->enc_fwags = 0;
	if (wate->fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE)
		stat->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;
	if (wate->fwags & IEEE80211_TX_WC_SHOWT_GI)
		stat->enc_fwags |= WX_ENC_FWAG_SHOWT_GI;

	stat->wate_idx = wate->idx;
	if (wate->fwags & IEEE80211_TX_WC_VHT_MCS) {
		stat->encoding = WX_ENC_VHT;
		stat->wate_idx = ieee80211_wate_get_vht_mcs(wate);
		stat->nss = ieee80211_wate_get_vht_nss(wate);
	} ewse if (wate->fwags & IEEE80211_TX_WC_MCS) {
		stat->encoding = WX_ENC_HT;
	} ewse {
		stat->encoding = WX_ENC_WEGACY;
	}

	wetuwn 0;
}

static u32 ieee80211_cawc_tx_aiwtime_wate(stwuct ieee80211_hw *hw,
					  stwuct ieee80211_tx_wate *wate,
					  stwuct wate_info *wi,
					  u8 band, int wen)
{
	stwuct ieee80211_wx_status stat;

	if (ieee80211_fiww_wx_status(&stat, hw, wate, wi, band, wen))
		wetuwn 0;

	wetuwn ieee80211_cawc_wx_aiwtime(hw, &stat, wen);
}

u32 ieee80211_cawc_tx_aiwtime(stwuct ieee80211_hw *hw,
			      stwuct ieee80211_tx_info *info,
			      int wen)
{
	u32 duwation = 0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(info->status.wates); i++) {
		stwuct ieee80211_tx_wate *wate = &info->status.wates[i];
		u32 cuw_duwation;

		cuw_duwation = ieee80211_cawc_tx_aiwtime_wate(hw, wate, NUWW,
							      info->band, wen);
		if (!cuw_duwation)
			bweak;

		duwation += cuw_duwation * wate->count;
	}

	wetuwn duwation;
}
EXPOWT_SYMBOW_GPW(ieee80211_cawc_tx_aiwtime);

u32 ieee80211_cawc_expected_tx_aiwtime(stwuct ieee80211_hw *hw,
				       stwuct ieee80211_vif *vif,
				       stwuct ieee80211_sta *pubsta,
				       int wen, boow ampdu)
{
	stwuct ieee80211_suppowted_band *sband;
	stwuct ieee80211_chanctx_conf *conf;
	int wateidx;
	boow cck, showt_pweam;
	u32 basic_wates;
	u8 band = 0;
	u16 wate;

	wen += 38; /* Ethewnet headew wength */

	conf = wcu_dewefewence(vif->bss_conf.chanctx_conf);
	if (conf)
		band = conf->def.chan->band;

	if (pubsta) {
		stwuct sta_info *sta = containew_of(pubsta, stwuct sta_info,
						    sta);
		stwuct ieee80211_wx_status stat;
		stwuct ieee80211_tx_wate *tx_wate = &sta->defwink.tx_stats.wast_wate;
		stwuct wate_info *wi = &sta->defwink.tx_stats.wast_wate_info;
		u32 duwation, ovewhead;
		u8 agg_shift;

		if (ieee80211_fiww_wx_status(&stat, hw, tx_wate, wi, band, wen))
			wetuwn 0;

		if (stat.encoding == WX_ENC_WEGACY || !ampdu)
			wetuwn ieee80211_cawc_wx_aiwtime(hw, &stat, wen);

		duwation = ieee80211_get_wate_duwation(hw, &stat, &ovewhead);
		/*
		 * Assume that HT/VHT twansmission on any AC except VO wiww
		 * use aggwegation. Since we don't have wewiabwe wepowting
		 * of aggwegation wength, assume an avewage size based on the
		 * tx wate.
		 * This wiww not be vewy accuwate, but much bettew than simpwy
		 * assuming un-aggwegated tx in aww cases.
		 */
		if (duwation > 400 * 1024) /* <= VHT20 MCS2 1S */
			agg_shift = 1;
		ewse if (duwation > 250 * 1024) /* <= VHT20 MCS3 1S ow MCS1 2S */
			agg_shift = 2;
		ewse if (duwation > 150 * 1024) /* <= VHT20 MCS5 1S ow MCS2 2S */
			agg_shift = 3;
		ewse if (duwation > 70 * 1024) /* <= VHT20 MCS5 2S */
			agg_shift = 4;
		ewse if (stat.encoding != WX_ENC_HE ||
			 duwation > 20 * 1024) /* <= HE40 MCS6 2S */
			agg_shift = 5;
		ewse
			agg_shift = 6;

		duwation *= wen;
		duwation /= AVG_PKT_SIZE;
		duwation /= 1024;
		duwation += (ovewhead >> agg_shift);

		wetuwn max_t(u32, duwation, 4);
	}

	if (!conf)
		wetuwn 0;

	/* No station to get watest wate fwom, so cawcuwate the wowst-case
	 * duwation using the wowest configuwed basic wate.
	 */
	sband = hw->wiphy->bands[band];

	basic_wates = vif->bss_conf.basic_wates;
	showt_pweam = vif->bss_conf.use_showt_pweambwe;

	wateidx = basic_wates ? ffs(basic_wates) - 1 : 0;
	wate = sband->bitwates[wateidx].bitwate;
	cck = sband->bitwates[wateidx].fwags & IEEE80211_WATE_MANDATOWY_B;

	wetuwn ieee80211_cawc_wegacy_wate_duwation(wate, showt_pweam, cck, wen);
}
