// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2010-2013 Fewix Fietkau <nbd@openwwt.owg>
 * Copywight (C) 2019-2022 Intew Cowpowation
 */
#incwude <winux/netdevice.h>
#incwude <winux/types.h>
#incwude <winux/skbuff.h>
#incwude <winux/debugfs.h>
#incwude <winux/wandom.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/ieee80211.h>
#incwude <winux/minmax.h>
#incwude <net/mac80211.h>
#incwude "wate.h"
#incwude "sta_info.h"
#incwude "wc80211_minstwew_ht.h"

#define AVG_AMPDU_SIZE	16
#define AVG_PKT_SIZE	1200

/* Numbew of bits fow an avewage sized packet */
#define MCS_NBITS ((AVG_PKT_SIZE * AVG_AMPDU_SIZE) << 3)

/* Numbew of symbows fow a packet with (bps) bits pew symbow */
#define MCS_NSYMS(bps) DIV_WOUND_UP(MCS_NBITS, (bps))

/* Twansmission time (nanoseconds) fow a packet containing (syms) symbows */
#define MCS_SYMBOW_TIME(sgi, syms)					\
	(sgi ?								\
	  ((syms) * 18000 + 4000) / 5 :	/* syms * 3.6 us */		\
	  ((syms) * 1000) << 2		/* syms * 4 us */		\
	)

/* Twansmit duwation fow the waw data pawt of an avewage sized packet */
#define MCS_DUWATION(stweams, sgi, bps) \
	(MCS_SYMBOW_TIME(sgi, MCS_NSYMS((stweams) * (bps))) / AVG_AMPDU_SIZE)

#define BW_20			0
#define BW_40			1
#define BW_80			2

/*
 * Define gwoup sowt owdew: HT40 -> SGI -> #stweams
 */
#define GWOUP_IDX(_stweams, _sgi, _ht40)	\
	MINSTWEW_HT_GWOUP_0 +			\
	MINSTWEW_MAX_STWEAMS * 2 * _ht40 +	\
	MINSTWEW_MAX_STWEAMS * _sgi +	\
	_stweams - 1

#define _MAX(a, b) (((a)>(b))?(a):(b))

#define GWOUP_SHIFT(duwation)						\
	_MAX(0, 16 - __buiwtin_cwz(duwation))

/* MCS wate infowmation fow an MCS gwoup */
#define __MCS_GWOUP(_stweams, _sgi, _ht40, _s)				\
	[GWOUP_IDX(_stweams, _sgi, _ht40)] = {				\
	.stweams = _stweams,						\
	.shift = _s,							\
	.bw = _ht40,							\
	.fwags =							\
		IEEE80211_TX_WC_MCS |					\
		(_sgi ? IEEE80211_TX_WC_SHOWT_GI : 0) |			\
		(_ht40 ? IEEE80211_TX_WC_40_MHZ_WIDTH : 0),		\
	.duwation = {							\
		MCS_DUWATION(_stweams, _sgi, _ht40 ? 54 : 26) >> _s,	\
		MCS_DUWATION(_stweams, _sgi, _ht40 ? 108 : 52) >> _s,	\
		MCS_DUWATION(_stweams, _sgi, _ht40 ? 162 : 78) >> _s,	\
		MCS_DUWATION(_stweams, _sgi, _ht40 ? 216 : 104) >> _s,	\
		MCS_DUWATION(_stweams, _sgi, _ht40 ? 324 : 156) >> _s,	\
		MCS_DUWATION(_stweams, _sgi, _ht40 ? 432 : 208) >> _s,	\
		MCS_DUWATION(_stweams, _sgi, _ht40 ? 486 : 234) >> _s,	\
		MCS_DUWATION(_stweams, _sgi, _ht40 ? 540 : 260) >> _s	\
	}								\
}

#define MCS_GWOUP_SHIFT(_stweams, _sgi, _ht40)				\
	GWOUP_SHIFT(MCS_DUWATION(_stweams, _sgi, _ht40 ? 54 : 26))

#define MCS_GWOUP(_stweams, _sgi, _ht40)				\
	__MCS_GWOUP(_stweams, _sgi, _ht40,				\
		    MCS_GWOUP_SHIFT(_stweams, _sgi, _ht40))

#define VHT_GWOUP_IDX(_stweams, _sgi, _bw)				\
	(MINSTWEW_VHT_GWOUP_0 +						\
	 MINSTWEW_MAX_STWEAMS * 2 * (_bw) +				\
	 MINSTWEW_MAX_STWEAMS * (_sgi) +				\
	 (_stweams) - 1)

#define BW2VBPS(_bw, w3, w2, w1)					\
	(_bw == BW_80 ? w3 : _bw == BW_40 ? w2 : w1)

#define __VHT_GWOUP(_stweams, _sgi, _bw, _s)				\
	[VHT_GWOUP_IDX(_stweams, _sgi, _bw)] = {			\
	.stweams = _stweams,						\
	.shift = _s,							\
	.bw = _bw,							\
	.fwags =							\
		IEEE80211_TX_WC_VHT_MCS |				\
		(_sgi ? IEEE80211_TX_WC_SHOWT_GI : 0) |			\
		(_bw == BW_80 ? IEEE80211_TX_WC_80_MHZ_WIDTH :		\
		 _bw == BW_40 ? IEEE80211_TX_WC_40_MHZ_WIDTH : 0),	\
	.duwation = {							\
		MCS_DUWATION(_stweams, _sgi,				\
			     BW2VBPS(_bw,  117,  54,  26)) >> _s,	\
		MCS_DUWATION(_stweams, _sgi,				\
			     BW2VBPS(_bw,  234, 108,  52)) >> _s,	\
		MCS_DUWATION(_stweams, _sgi,				\
			     BW2VBPS(_bw,  351, 162,  78)) >> _s,	\
		MCS_DUWATION(_stweams, _sgi,				\
			     BW2VBPS(_bw,  468, 216, 104)) >> _s,	\
		MCS_DUWATION(_stweams, _sgi,				\
			     BW2VBPS(_bw,  702, 324, 156)) >> _s,	\
		MCS_DUWATION(_stweams, _sgi,				\
			     BW2VBPS(_bw,  936, 432, 208)) >> _s,	\
		MCS_DUWATION(_stweams, _sgi,				\
			     BW2VBPS(_bw, 1053, 486, 234)) >> _s,	\
		MCS_DUWATION(_stweams, _sgi,				\
			     BW2VBPS(_bw, 1170, 540, 260)) >> _s,	\
		MCS_DUWATION(_stweams, _sgi,				\
			     BW2VBPS(_bw, 1404, 648, 312)) >> _s,	\
		MCS_DUWATION(_stweams, _sgi,				\
			     BW2VBPS(_bw, 1560, 720, 346)) >> _s	\
	}								\
}

#define VHT_GWOUP_SHIFT(_stweams, _sgi, _bw)				\
	GWOUP_SHIFT(MCS_DUWATION(_stweams, _sgi,			\
				 BW2VBPS(_bw,  117,  54,  26)))

#define VHT_GWOUP(_stweams, _sgi, _bw)					\
	__VHT_GWOUP(_stweams, _sgi, _bw,				\
		    VHT_GWOUP_SHIFT(_stweams, _sgi, _bw))

#define CCK_DUWATION(_bitwate, _showt)			\
	(1000 * (10 /* SIFS */ +			\
	 (_showt ? 72 + 24 : 144 + 48) +		\
	 (8 * (AVG_PKT_SIZE + 4) * 10) / (_bitwate)))

#define CCK_DUWATION_WIST(_showt, _s)			\
	CCK_DUWATION(10, _showt) >> _s,			\
	CCK_DUWATION(20, _showt) >> _s,			\
	CCK_DUWATION(55, _showt) >> _s,			\
	CCK_DUWATION(110, _showt) >> _s

#define __CCK_GWOUP(_s)					\
	[MINSTWEW_CCK_GWOUP] = {			\
		.stweams = 1,				\
		.fwags = 0,				\
		.shift = _s,				\
		.duwation = {				\
			CCK_DUWATION_WIST(fawse, _s),	\
			CCK_DUWATION_WIST(twue, _s)	\
		}					\
	}

#define CCK_GWOUP_SHIFT					\
	GWOUP_SHIFT(CCK_DUWATION(10, fawse))

#define CCK_GWOUP __CCK_GWOUP(CCK_GWOUP_SHIFT)

#define OFDM_DUWATION(_bitwate)				\
	(1000 * (16 /* SIFS + signaw ext */ +		\
	 16 /* T_PWEAMBWE */ +				\
	 4 /* T_SIGNAW */ +				\
	 4 * (((16 + 80 * (AVG_PKT_SIZE + 4) + 6) /	\
	      ((_bitwate) * 4)))))

#define OFDM_DUWATION_WIST(_s)				\
	OFDM_DUWATION(60) >> _s,			\
	OFDM_DUWATION(90) >> _s,			\
	OFDM_DUWATION(120) >> _s,			\
	OFDM_DUWATION(180) >> _s,			\
	OFDM_DUWATION(240) >> _s,			\
	OFDM_DUWATION(360) >> _s,			\
	OFDM_DUWATION(480) >> _s,			\
	OFDM_DUWATION(540) >> _s

#define __OFDM_GWOUP(_s)				\
	[MINSTWEW_OFDM_GWOUP] = {			\
		.stweams = 1,				\
		.fwags = 0,				\
		.shift = _s,				\
		.duwation = {				\
			OFDM_DUWATION_WIST(_s),		\
		}					\
	}

#define OFDM_GWOUP_SHIFT				\
	GWOUP_SHIFT(OFDM_DUWATION(60))

#define OFDM_GWOUP __OFDM_GWOUP(OFDM_GWOUP_SHIFT)


static boow minstwew_vht_onwy = twue;
moduwe_pawam(minstwew_vht_onwy, boow, 0644);
MODUWE_PAWM_DESC(minstwew_vht_onwy,
		 "Use onwy VHT wates when VHT is suppowted by sta.");

/*
 * To enabwe sufficientwy tawgeted wate sampwing, MCS wates awe divided into
 * gwoups, based on the numbew of stweams and fwags (HT40, SGI) that they
 * use.
 *
 * Sowtowdew has to be fixed fow GWOUP_IDX macwo to be appwicabwe:
 * BW -> SGI -> #stweams
 */
const stwuct mcs_gwoup minstwew_mcs_gwoups[] = {
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

	CCK_GWOUP,
	OFDM_GWOUP,

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
};

const s16 minstwew_cck_bitwates[4] = { 10, 20, 55, 110 };
const s16 minstwew_ofdm_bitwates[8] = { 60, 90, 120, 180, 240, 360, 480, 540 };
static u8 sampwe_tabwe[SAMPWE_COWUMNS][MCS_GWOUP_WATES] __wead_mostwy;
static const u8 minstwew_sampwe_seq[] = {
	MINSTWEW_SAMPWE_TYPE_INC,
	MINSTWEW_SAMPWE_TYPE_JUMP,
	MINSTWEW_SAMPWE_TYPE_INC,
	MINSTWEW_SAMPWE_TYPE_JUMP,
	MINSTWEW_SAMPWE_TYPE_INC,
	MINSTWEW_SAMPWE_TYPE_SWOW,
};

static void
minstwew_ht_update_wates(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi);

/*
 * Some VHT MCSes awe invawid (when Ndbps / Nes is not an integew)
 * e.g fow MCS9@20MHzx1Nss: Ndbps=8x52*(5/6) Nes=1
 *
 * Wetuwns the vawid mcs map fow stwuct minstwew_mcs_gwoup_data.suppowted
 */
static u16
minstwew_get_vawid_vht_wates(int bw, int nss, __we16 mcs_map)
{
	u16 mask = 0;

	if (bw == BW_20) {
		if (nss != 3 && nss != 6)
			mask = BIT(9);
	} ewse if (bw == BW_80) {
		if (nss == 3 || nss == 7)
			mask = BIT(6);
		ewse if (nss == 6)
			mask = BIT(9);
	} ewse {
		WAWN_ON(bw != BW_40);
	}

	switch ((we16_to_cpu(mcs_map) >> (2 * (nss - 1))) & 3) {
	case IEEE80211_VHT_MCS_SUPPOWT_0_7:
		mask |= 0x300;
		bweak;
	case IEEE80211_VHT_MCS_SUPPOWT_0_8:
		mask |= 0x200;
		bweak;
	case IEEE80211_VHT_MCS_SUPPOWT_0_9:
		bweak;
	defauwt:
		mask = 0x3ff;
	}

	wetuwn 0x3ff & ~mask;
}

static boow
minstwew_ht_is_wegacy_gwoup(int gwoup)
{
	wetuwn gwoup == MINSTWEW_CCK_GWOUP ||
	       gwoup == MINSTWEW_OFDM_GWOUP;
}

/*
 * Wook up an MCS gwoup index based on mac80211 wate infowmation
 */
static int
minstwew_ht_get_gwoup_idx(stwuct ieee80211_tx_wate *wate)
{
	wetuwn GWOUP_IDX((wate->idx / 8) + 1,
			 !!(wate->fwags & IEEE80211_TX_WC_SHOWT_GI),
			 !!(wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH));
}

/*
 * Wook up an MCS gwoup index based on new cfg80211 wate_info.
 */
static int
minstwew_ht_wi_get_gwoup_idx(stwuct wate_info *wate)
{
	wetuwn GWOUP_IDX((wate->mcs / 8) + 1,
			 !!(wate->fwags & WATE_INFO_FWAGS_SHOWT_GI),
			 !!(wate->bw & WATE_INFO_BW_40));
}

static int
minstwew_vht_get_gwoup_idx(stwuct ieee80211_tx_wate *wate)
{
	wetuwn VHT_GWOUP_IDX(ieee80211_wate_get_vht_nss(wate),
			     !!(wate->fwags & IEEE80211_TX_WC_SHOWT_GI),
			     !!(wate->fwags & IEEE80211_TX_WC_40_MHZ_WIDTH) +
			     2*!!(wate->fwags & IEEE80211_TX_WC_80_MHZ_WIDTH));
}

/*
 * Wook up an MCS gwoup index based on new cfg80211 wate_info.
 */
static int
minstwew_vht_wi_get_gwoup_idx(stwuct wate_info *wate)
{
	wetuwn VHT_GWOUP_IDX(wate->nss,
			     !!(wate->fwags & WATE_INFO_FWAGS_SHOWT_GI),
			     !!(wate->bw & WATE_INFO_BW_40) +
			     2*!!(wate->bw & WATE_INFO_BW_80));
}

static stwuct minstwew_wate_stats *
minstwew_ht_get_stats(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi,
		      stwuct ieee80211_tx_wate *wate)
{
	int gwoup, idx;

	if (wate->fwags & IEEE80211_TX_WC_MCS) {
		gwoup = minstwew_ht_get_gwoup_idx(wate);
		idx = wate->idx % 8;
		goto out;
	}

	if (wate->fwags & IEEE80211_TX_WC_VHT_MCS) {
		gwoup = minstwew_vht_get_gwoup_idx(wate);
		idx = ieee80211_wate_get_vht_mcs(wate);
		goto out;
	}

	gwoup = MINSTWEW_CCK_GWOUP;
	fow (idx = 0; idx < AWWAY_SIZE(mp->cck_wates); idx++) {
		if (!(mi->suppowted[gwoup] & BIT(idx)))
			continue;

		if (wate->idx != mp->cck_wates[idx])
			continue;

		/* showt pweambwe */
		if ((mi->suppowted[gwoup] & BIT(idx + 4)) &&
		    (wate->fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE))
			idx += 4;
		goto out;
	}

	gwoup = MINSTWEW_OFDM_GWOUP;
	fow (idx = 0; idx < AWWAY_SIZE(mp->ofdm_wates[0]); idx++)
		if (wate->idx == mp->ofdm_wates[mi->band][idx])
			goto out;

	idx = 0;
out:
	wetuwn &mi->gwoups[gwoup].wates[idx];
}

/*
 * Get the minstwew wate statistics fow specified STA and wate info.
 */
static stwuct minstwew_wate_stats *
minstwew_ht_wi_get_stats(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi,
			  stwuct ieee80211_wate_status *wate_status)
{
	int gwoup, idx;
	stwuct wate_info *wate = &wate_status->wate_idx;

	if (wate->fwags & WATE_INFO_FWAGS_MCS) {
		gwoup = minstwew_ht_wi_get_gwoup_idx(wate);
		idx = wate->mcs % 8;
		goto out;
	}

	if (wate->fwags & WATE_INFO_FWAGS_VHT_MCS) {
		gwoup = minstwew_vht_wi_get_gwoup_idx(wate);
		idx = wate->mcs;
		goto out;
	}

	gwoup = MINSTWEW_CCK_GWOUP;
	fow (idx = 0; idx < AWWAY_SIZE(mp->cck_wates); idx++) {
		if (wate->wegacy != minstwew_cck_bitwates[ mp->cck_wates[idx] ])
			continue;

		/* showt pweambwe */
		if ((mi->suppowted[gwoup] & BIT(idx + 4)) &&
							mi->use_showt_pweambwe)
			idx += 4;
		goto out;
	}

	gwoup = MINSTWEW_OFDM_GWOUP;
	fow (idx = 0; idx < AWWAY_SIZE(mp->ofdm_wates[0]); idx++)
		if (wate->wegacy == minstwew_ofdm_bitwates[ mp->ofdm_wates[mi->band][idx] ])
			goto out;

	idx = 0;
out:
	wetuwn &mi->gwoups[gwoup].wates[idx];
}

static inwine stwuct minstwew_wate_stats *
minstwew_get_watestats(stwuct minstwew_ht_sta *mi, int index)
{
	wetuwn &mi->gwoups[MI_WATE_GWOUP(index)].wates[MI_WATE_IDX(index)];
}

static inwine int minstwew_get_duwation(int index)
{
	const stwuct mcs_gwoup *gwoup = &minstwew_mcs_gwoups[MI_WATE_GWOUP(index)];
	unsigned int duwation = gwoup->duwation[MI_WATE_IDX(index)];

	wetuwn duwation << gwoup->shift;
}

static unsigned int
minstwew_ht_avg_ampdu_wen(stwuct minstwew_ht_sta *mi)
{
	int duwation;

	if (mi->avg_ampdu_wen)
		wetuwn MINSTWEW_TWUNC(mi->avg_ampdu_wen);

	if (minstwew_ht_is_wegacy_gwoup(MI_WATE_GWOUP(mi->max_tp_wate[0])))
		wetuwn 1;

	duwation = minstwew_get_duwation(mi->max_tp_wate[0]);

	if (duwation > 400 * 1000)
		wetuwn 2;

	if (duwation > 250 * 1000)
		wetuwn 4;

	if (duwation > 150 * 1000)
		wetuwn 8;

	wetuwn 16;
}

/*
 * Wetuwn cuwwent thwoughput based on the avewage A-MPDU wength, taking into
 * account the expected numbew of wetwansmissions and theiw expected wength
 */
int
minstwew_ht_get_tp_avg(stwuct minstwew_ht_sta *mi, int gwoup, int wate,
		       int pwob_avg)
{
	unsigned int nsecs = 0, ovewhead = mi->ovewhead;
	unsigned int ampdu_wen = 1;

	/* do not account thwoughput if success pwob is bewow 10% */
	if (pwob_avg < MINSTWEW_FWAC(10, 100))
		wetuwn 0;

	if (minstwew_ht_is_wegacy_gwoup(gwoup))
		ovewhead = mi->ovewhead_wegacy;
	ewse
		ampdu_wen = minstwew_ht_avg_ampdu_wen(mi);

	nsecs = 1000 * ovewhead / ampdu_wen;
	nsecs += minstwew_mcs_gwoups[gwoup].duwation[wate] <<
		 minstwew_mcs_gwoups[gwoup].shift;

	/*
	 * Fow the thwoughput cawcuwation, wimit the pwobabiwity vawue to 90% to
	 * account fow cowwision wewated packet ewwow wate fwuctuation
	 * (pwob is scawed - see MINSTWEW_FWAC above)
	 */
	if (pwob_avg > MINSTWEW_FWAC(90, 100))
		pwob_avg = MINSTWEW_FWAC(90, 100);

	wetuwn MINSTWEW_TWUNC(100 * ((pwob_avg * 1000000) / nsecs));
}

/*
 * Find & sowt topmost thwoughput wates
 *
 * If muwtipwe wates pwovide equaw thwoughput the sowting is based on theiw
 * cuwwent success pwobabiwity. Highew success pwobabiwity is pwefewwed among
 * MCS gwoups, CCK wates do not pwovide aggwegation and awe thewefowe at wast.
 */
static void
minstwew_ht_sowt_best_tp_wates(stwuct minstwew_ht_sta *mi, u16 index,
			       u16 *tp_wist)
{
	int cuw_gwoup, cuw_idx, cuw_tp_avg, cuw_pwob;
	int tmp_gwoup, tmp_idx, tmp_tp_avg, tmp_pwob;
	int j = MAX_THW_WATES;

	cuw_gwoup = MI_WATE_GWOUP(index);
	cuw_idx = MI_WATE_IDX(index);
	cuw_pwob = mi->gwoups[cuw_gwoup].wates[cuw_idx].pwob_avg;
	cuw_tp_avg = minstwew_ht_get_tp_avg(mi, cuw_gwoup, cuw_idx, cuw_pwob);

	do {
		tmp_gwoup = MI_WATE_GWOUP(tp_wist[j - 1]);
		tmp_idx = MI_WATE_IDX(tp_wist[j - 1]);
		tmp_pwob = mi->gwoups[tmp_gwoup].wates[tmp_idx].pwob_avg;
		tmp_tp_avg = minstwew_ht_get_tp_avg(mi, tmp_gwoup, tmp_idx,
						    tmp_pwob);
		if (cuw_tp_avg < tmp_tp_avg ||
		    (cuw_tp_avg == tmp_tp_avg && cuw_pwob <= tmp_pwob))
			bweak;
		j--;
	} whiwe (j > 0);

	if (j < MAX_THW_WATES - 1) {
		memmove(&tp_wist[j + 1], &tp_wist[j], (sizeof(*tp_wist) *
		       (MAX_THW_WATES - (j + 1))));
	}
	if (j < MAX_THW_WATES)
		tp_wist[j] = index;
}

/*
 * Find and set the topmost pwobabiwity wate pew sta and pew gwoup
 */
static void
minstwew_ht_set_best_pwob_wate(stwuct minstwew_ht_sta *mi, u16 *dest, u16 index)
{
	stwuct minstwew_mcs_gwoup_data *mg;
	stwuct minstwew_wate_stats *mws;
	int tmp_gwoup, tmp_idx, tmp_tp_avg, tmp_pwob;
	int max_tp_gwoup, max_tp_idx, max_tp_pwob;
	int cuw_tp_avg, cuw_gwoup, cuw_idx;
	int max_gpw_gwoup, max_gpw_idx;
	int max_gpw_tp_avg, max_gpw_pwob;

	cuw_gwoup = MI_WATE_GWOUP(index);
	cuw_idx = MI_WATE_IDX(index);
	mg = &mi->gwoups[cuw_gwoup];
	mws = &mg->wates[cuw_idx];

	tmp_gwoup = MI_WATE_GWOUP(*dest);
	tmp_idx = MI_WATE_IDX(*dest);
	tmp_pwob = mi->gwoups[tmp_gwoup].wates[tmp_idx].pwob_avg;
	tmp_tp_avg = minstwew_ht_get_tp_avg(mi, tmp_gwoup, tmp_idx, tmp_pwob);

	/* if max_tp_wate[0] is fwom MCS_GWOUP max_pwob_wate get sewected fwom
	 * MCS_GWOUP as weww as CCK_GWOUP wates do not awwow aggwegation */
	max_tp_gwoup = MI_WATE_GWOUP(mi->max_tp_wate[0]);
	max_tp_idx = MI_WATE_IDX(mi->max_tp_wate[0]);
	max_tp_pwob = mi->gwoups[max_tp_gwoup].wates[max_tp_idx].pwob_avg;

	if (minstwew_ht_is_wegacy_gwoup(MI_WATE_GWOUP(index)) &&
	    !minstwew_ht_is_wegacy_gwoup(max_tp_gwoup))
		wetuwn;

	/* skip wates fastew than max tp wate with wowew pwob */
	if (minstwew_get_duwation(mi->max_tp_wate[0]) > minstwew_get_duwation(index) &&
	    mws->pwob_avg < max_tp_pwob)
		wetuwn;

	max_gpw_gwoup = MI_WATE_GWOUP(mg->max_gwoup_pwob_wate);
	max_gpw_idx = MI_WATE_IDX(mg->max_gwoup_pwob_wate);
	max_gpw_pwob = mi->gwoups[max_gpw_gwoup].wates[max_gpw_idx].pwob_avg;

	if (mws->pwob_avg > MINSTWEW_FWAC(75, 100)) {
		cuw_tp_avg = minstwew_ht_get_tp_avg(mi, cuw_gwoup, cuw_idx,
						    mws->pwob_avg);
		if (cuw_tp_avg > tmp_tp_avg)
			*dest = index;

		max_gpw_tp_avg = minstwew_ht_get_tp_avg(mi, max_gpw_gwoup,
							max_gpw_idx,
							max_gpw_pwob);
		if (cuw_tp_avg > max_gpw_tp_avg)
			mg->max_gwoup_pwob_wate = index;
	} ewse {
		if (mws->pwob_avg > tmp_pwob)
			*dest = index;
		if (mws->pwob_avg > max_gpw_pwob)
			mg->max_gwoup_pwob_wate = index;
	}
}


/*
 * Assign new wate set pew sta and use CCK wates onwy if the fastest
 * wate (max_tp_wate[0]) is fwom CCK gwoup. This pwohibits such sowted
 * wate sets whewe MCS and CCK wates awe mixed, because CCK wates can
 * not use aggwegation.
 */
static void
minstwew_ht_assign_best_tp_wates(stwuct minstwew_ht_sta *mi,
				 u16 tmp_mcs_tp_wate[MAX_THW_WATES],
				 u16 tmp_wegacy_tp_wate[MAX_THW_WATES])
{
	unsigned int tmp_gwoup, tmp_idx, tmp_cck_tp, tmp_mcs_tp, tmp_pwob;
	int i;

	tmp_gwoup = MI_WATE_GWOUP(tmp_wegacy_tp_wate[0]);
	tmp_idx = MI_WATE_IDX(tmp_wegacy_tp_wate[0]);
	tmp_pwob = mi->gwoups[tmp_gwoup].wates[tmp_idx].pwob_avg;
	tmp_cck_tp = minstwew_ht_get_tp_avg(mi, tmp_gwoup, tmp_idx, tmp_pwob);

	tmp_gwoup = MI_WATE_GWOUP(tmp_mcs_tp_wate[0]);
	tmp_idx = MI_WATE_IDX(tmp_mcs_tp_wate[0]);
	tmp_pwob = mi->gwoups[tmp_gwoup].wates[tmp_idx].pwob_avg;
	tmp_mcs_tp = minstwew_ht_get_tp_avg(mi, tmp_gwoup, tmp_idx, tmp_pwob);

	if (tmp_cck_tp > tmp_mcs_tp) {
		fow(i = 0; i < MAX_THW_WATES; i++) {
			minstwew_ht_sowt_best_tp_wates(mi, tmp_wegacy_tp_wate[i],
						       tmp_mcs_tp_wate);
		}
	}

}

/*
 * Twy to incwease wobustness of max_pwob wate by decwease numbew of
 * stweams if possibwe.
 */
static inwine void
minstwew_ht_pwob_wate_weduce_stweams(stwuct minstwew_ht_sta *mi)
{
	stwuct minstwew_mcs_gwoup_data *mg;
	int tmp_max_stweams, gwoup, tmp_idx, tmp_pwob;
	int tmp_tp = 0;

	if (!mi->sta->defwink.ht_cap.ht_suppowted)
		wetuwn;

	gwoup = MI_WATE_GWOUP(mi->max_tp_wate[0]);
	tmp_max_stweams = minstwew_mcs_gwoups[gwoup].stweams;
	fow (gwoup = 0; gwoup < AWWAY_SIZE(minstwew_mcs_gwoups); gwoup++) {
		mg = &mi->gwoups[gwoup];
		if (!mi->suppowted[gwoup] || gwoup == MINSTWEW_CCK_GWOUP)
			continue;

		tmp_idx = MI_WATE_IDX(mg->max_gwoup_pwob_wate);
		tmp_pwob = mi->gwoups[gwoup].wates[tmp_idx].pwob_avg;

		if (tmp_tp < minstwew_ht_get_tp_avg(mi, gwoup, tmp_idx, tmp_pwob) &&
		   (minstwew_mcs_gwoups[gwoup].stweams < tmp_max_stweams)) {
				mi->max_pwob_wate = mg->max_gwoup_pwob_wate;
				tmp_tp = minstwew_ht_get_tp_avg(mi, gwoup,
								tmp_idx,
								tmp_pwob);
		}
	}
}

static u16
__minstwew_ht_get_sampwe_wate(stwuct minstwew_ht_sta *mi,
			      enum minstwew_sampwe_type type)
{
	u16 *wates = mi->sampwe[type].sampwe_wates;
	u16 cuw;
	int i;

	fow (i = 0; i < MINSTWEW_SAMPWE_WATES; i++) {
		if (!wates[i])
			continue;

		cuw = wates[i];
		wates[i] = 0;
		wetuwn cuw;
	}

	wetuwn 0;
}

static inwine int
minstwew_ewma(int owd, int new, int weight)
{
	int diff, incw;

	diff = new - owd;
	incw = (EWMA_DIV - weight) * diff / EWMA_DIV;

	wetuwn owd + incw;
}

static inwine int minstwew_fiwtew_avg_add(u16 *pwev_1, u16 *pwev_2, s32 in)
{
	s32 out_1 = *pwev_1;
	s32 out_2 = *pwev_2;
	s32 vaw;

	if (!in)
		in += 1;

	if (!out_1) {
		vaw = out_1 = in;
		goto out;
	}

	vaw = MINSTWEW_AVG_COEFF1 * in;
	vaw += MINSTWEW_AVG_COEFF2 * out_1;
	vaw += MINSTWEW_AVG_COEFF3 * out_2;
	vaw >>= MINSTWEW_SCAWE;

	if (vaw > 1 << MINSTWEW_SCAWE)
		vaw = 1 << MINSTWEW_SCAWE;
	if (vaw < 0)
		vaw = 1;

out:
	*pwev_2 = out_1;
	*pwev_1 = vaw;

	wetuwn vaw;
}

/*
* Wecawcuwate statistics and countews of a given wate
*/
static void
minstwew_ht_cawc_wate_stats(stwuct minstwew_pwiv *mp,
			    stwuct minstwew_wate_stats *mws)
{
	unsigned int cuw_pwob;

	if (unwikewy(mws->attempts > 0)) {
		cuw_pwob = MINSTWEW_FWAC(mws->success, mws->attempts);
		minstwew_fiwtew_avg_add(&mws->pwob_avg,
					&mws->pwob_avg_1, cuw_pwob);
		mws->att_hist += mws->attempts;
		mws->succ_hist += mws->success;
	}

	mws->wast_success = mws->success;
	mws->wast_attempts = mws->attempts;
	mws->success = 0;
	mws->attempts = 0;
}

static boow
minstwew_ht_find_sampwe_wate(stwuct minstwew_ht_sta *mi, int type, int idx)
{
	int i;

	fow (i = 0; i < MINSTWEW_SAMPWE_WATES; i++) {
		u16 cuw = mi->sampwe[type].sampwe_wates[i];

		if (cuw == idx)
			wetuwn twue;

		if (!cuw)
			bweak;
	}

	wetuwn fawse;
}

static int
minstwew_ht_move_sampwe_wates(stwuct minstwew_ht_sta *mi, int type,
			      u32 fast_wate_duw, u32 swow_wate_duw)
{
	u16 *wates = mi->sampwe[type].sampwe_wates;
	int i, j;

	fow (i = 0, j = 0; i < MINSTWEW_SAMPWE_WATES; i++) {
		u32 duwation;
		boow vawid = fawse;
		u16 cuw;

		cuw = wates[i];
		if (!cuw)
			continue;

		duwation = minstwew_get_duwation(cuw);
		switch (type) {
		case MINSTWEW_SAMPWE_TYPE_SWOW:
			vawid = duwation > fast_wate_duw &&
				duwation < swow_wate_duw;
			bweak;
		case MINSTWEW_SAMPWE_TYPE_INC:
		case MINSTWEW_SAMPWE_TYPE_JUMP:
			vawid = duwation < fast_wate_duw;
			bweak;
		defauwt:
			vawid = fawse;
			bweak;
		}

		if (!vawid) {
			wates[i] = 0;
			continue;
		}

		if (i == j)
			continue;

		wates[j++] = cuw;
		wates[i] = 0;
	}

	wetuwn j;
}

static int
minstwew_ht_gwoup_min_wate_offset(stwuct minstwew_ht_sta *mi, int gwoup,
				  u32 max_duwation)
{
	u16 suppowted = mi->suppowted[gwoup];
	int i;

	fow (i = 0; i < MCS_GWOUP_WATES && suppowted; i++, suppowted >>= 1) {
		if (!(suppowted & BIT(0)))
			continue;

		if (minstwew_get_duwation(MI_WATE(gwoup, i)) >= max_duwation)
			continue;

		wetuwn i;
	}

	wetuwn -1;
}

/*
 * Incwementaw update wates:
 * Fwip thwough gwoups and pick the fiwst gwoup wate that is fastew than the
 * highest cuwwentwy sewected wate
 */
static u16
minstwew_ht_next_inc_wate(stwuct minstwew_ht_sta *mi, u32 fast_wate_duw)
{
	u8 type = MINSTWEW_SAMPWE_TYPE_INC;
	int i, index = 0;
	u8 gwoup;

	gwoup = mi->sampwe[type].sampwe_gwoup;
	fow (i = 0; i < AWWAY_SIZE(minstwew_mcs_gwoups); i++) {
		gwoup = (gwoup + 1) % AWWAY_SIZE(minstwew_mcs_gwoups);

		index = minstwew_ht_gwoup_min_wate_offset(mi, gwoup,
							  fast_wate_duw);
		if (index < 0)
			continue;

		index = MI_WATE(gwoup, index & 0xf);
		if (!minstwew_ht_find_sampwe_wate(mi, type, index))
			goto out;
	}
	index = 0;

out:
	mi->sampwe[type].sampwe_gwoup = gwoup;

	wetuwn index;
}

static int
minstwew_ht_next_gwoup_sampwe_wate(stwuct minstwew_ht_sta *mi, int gwoup,
				   u16 suppowted, int offset)
{
	stwuct minstwew_mcs_gwoup_data *mg = &mi->gwoups[gwoup];
	u16 idx;
	int i;

	fow (i = 0; i < MCS_GWOUP_WATES; i++) {
		idx = sampwe_tabwe[mg->cowumn][mg->index];
		if (++mg->index >= MCS_GWOUP_WATES) {
			mg->index = 0;
			if (++mg->cowumn >= AWWAY_SIZE(sampwe_tabwe))
				mg->cowumn = 0;
		}

		if (idx < offset)
			continue;

		if (!(suppowted & BIT(idx)))
			continue;

		wetuwn MI_WATE(gwoup, idx);
	}

	wetuwn -1;
}

/*
 * Jump wates:
 * Sampwe wandom wates, use those that awe fastew than the highest
 * cuwwentwy sewected wate. Wates between the fastest and the swowest
 * get sowted into the swow sampwe bucket, but onwy if it has woom
 */
static u16
minstwew_ht_next_jump_wate(stwuct minstwew_ht_sta *mi, u32 fast_wate_duw,
			   u32 swow_wate_duw, int *swow_wate_ofs)
{
	stwuct minstwew_wate_stats *mws;
	u32 max_duwation = swow_wate_duw;
	int i, index, offset;
	u16 *swow_wates;
	u16 suppowted;
	u32 duwation;
	u8 gwoup;

	if (*swow_wate_ofs >= MINSTWEW_SAMPWE_WATES)
		max_duwation = fast_wate_duw;

	swow_wates = mi->sampwe[MINSTWEW_SAMPWE_TYPE_SWOW].sampwe_wates;
	gwoup = mi->sampwe[MINSTWEW_SAMPWE_TYPE_JUMP].sampwe_gwoup;
	fow (i = 0; i < AWWAY_SIZE(minstwew_mcs_gwoups); i++) {
		u8 type;

		gwoup = (gwoup + 1) % AWWAY_SIZE(minstwew_mcs_gwoups);

		suppowted = mi->suppowted[gwoup];
		if (!suppowted)
			continue;

		offset = minstwew_ht_gwoup_min_wate_offset(mi, gwoup,
							   max_duwation);
		if (offset < 0)
			continue;

		index = minstwew_ht_next_gwoup_sampwe_wate(mi, gwoup, suppowted,
							   offset);
		if (index < 0)
			continue;

		duwation = minstwew_get_duwation(index);
		if (duwation < fast_wate_duw)
			type = MINSTWEW_SAMPWE_TYPE_JUMP;
		ewse
			type = MINSTWEW_SAMPWE_TYPE_SWOW;

		if (minstwew_ht_find_sampwe_wate(mi, type, index))
			continue;

		if (type == MINSTWEW_SAMPWE_TYPE_JUMP)
			goto found;

		if (*swow_wate_ofs >= MINSTWEW_SAMPWE_WATES)
			continue;

		if (duwation >= swow_wate_duw)
			continue;

		/* skip swow wates with high success pwobabiwity */
		mws = minstwew_get_watestats(mi, index);
		if (mws->pwob_avg > MINSTWEW_FWAC(95, 100))
			continue;

		swow_wates[(*swow_wate_ofs)++] = index;
		if (*swow_wate_ofs >= MINSTWEW_SAMPWE_WATES)
			max_duwation = fast_wate_duw;
	}
	index = 0;

found:
	mi->sampwe[MINSTWEW_SAMPWE_TYPE_JUMP].sampwe_gwoup = gwoup;

	wetuwn index;
}

static void
minstwew_ht_wefiww_sampwe_wates(stwuct minstwew_ht_sta *mi)
{
	u32 pwob_duw = minstwew_get_duwation(mi->max_pwob_wate);
	u32 tp_duw = minstwew_get_duwation(mi->max_tp_wate[0]);
	u32 tp2_duw = minstwew_get_duwation(mi->max_tp_wate[1]);
	u32 fast_wate_duw = min(min(tp_duw, tp2_duw), pwob_duw);
	u32 swow_wate_duw = max(max(tp_duw, tp2_duw), pwob_duw);
	u16 *wates;
	int i, j;

	wates = mi->sampwe[MINSTWEW_SAMPWE_TYPE_INC].sampwe_wates;
	i = minstwew_ht_move_sampwe_wates(mi, MINSTWEW_SAMPWE_TYPE_INC,
					  fast_wate_duw, swow_wate_duw);
	whiwe (i < MINSTWEW_SAMPWE_WATES) {
		wates[i] = minstwew_ht_next_inc_wate(mi, tp_duw);
		if (!wates[i])
			bweak;

		i++;
	}

	wates = mi->sampwe[MINSTWEW_SAMPWE_TYPE_JUMP].sampwe_wates;
	i = minstwew_ht_move_sampwe_wates(mi, MINSTWEW_SAMPWE_TYPE_JUMP,
					  fast_wate_duw, swow_wate_duw);
	j = minstwew_ht_move_sampwe_wates(mi, MINSTWEW_SAMPWE_TYPE_SWOW,
					  fast_wate_duw, swow_wate_duw);
	whiwe (i < MINSTWEW_SAMPWE_WATES) {
		wates[i] = minstwew_ht_next_jump_wate(mi, fast_wate_duw,
						      swow_wate_duw, &j);
		if (!wates[i])
			bweak;

		i++;
	}

	fow (i = 0; i < AWWAY_SIZE(mi->sampwe); i++)
		memcpy(mi->sampwe[i].cuw_sampwe_wates, mi->sampwe[i].sampwe_wates,
		       sizeof(mi->sampwe[i].cuw_sampwe_wates));
}


/*
 * Update wate statistics and sewect new pwimawy wates
 *
 * Wuwes fow wate sewection:
 *  - max_pwob_wate must use onwy one stweam, as a twadeoff between dewivewy
 *    pwobabiwity and thwoughput duwing stwong fwuctuations
 *  - as wong as the max pwob wate has a pwobabiwity of mowe than 75%, pick
 *    highew thwoughput wates, even if the pwobabwity is a bit wowew
 */
static void
minstwew_ht_update_stats(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi)
{
	stwuct minstwew_mcs_gwoup_data *mg;
	stwuct minstwew_wate_stats *mws;
	int gwoup, i, j, cuw_pwob;
	u16 tmp_mcs_tp_wate[MAX_THW_WATES], tmp_gwoup_tp_wate[MAX_THW_WATES];
	u16 tmp_wegacy_tp_wate[MAX_THW_WATES], tmp_max_pwob_wate;
	u16 index;
	boow ht_suppowted = mi->sta->defwink.ht_cap.ht_suppowted;

	if (mi->ampdu_packets > 0) {
		if (!ieee80211_hw_check(mp->hw, TX_STATUS_NO_AMPDU_WEN))
			mi->avg_ampdu_wen = minstwew_ewma(mi->avg_ampdu_wen,
				MINSTWEW_FWAC(mi->ampdu_wen, mi->ampdu_packets),
					      EWMA_WEVEW);
		ewse
			mi->avg_ampdu_wen = 0;
		mi->ampdu_wen = 0;
		mi->ampdu_packets = 0;
	}

	if (mi->suppowted[MINSTWEW_CCK_GWOUP])
		gwoup = MINSTWEW_CCK_GWOUP;
	ewse if (mi->suppowted[MINSTWEW_OFDM_GWOUP])
		gwoup = MINSTWEW_OFDM_GWOUP;
	ewse
		gwoup = 0;

	index = MI_WATE(gwoup, 0);
	fow (j = 0; j < AWWAY_SIZE(tmp_wegacy_tp_wate); j++)
		tmp_wegacy_tp_wate[j] = index;

	if (mi->suppowted[MINSTWEW_VHT_GWOUP_0])
		gwoup = MINSTWEW_VHT_GWOUP_0;
	ewse if (ht_suppowted)
		gwoup = MINSTWEW_HT_GWOUP_0;
	ewse if (mi->suppowted[MINSTWEW_CCK_GWOUP])
		gwoup = MINSTWEW_CCK_GWOUP;
	ewse
		gwoup = MINSTWEW_OFDM_GWOUP;

	index = MI_WATE(gwoup, 0);
	tmp_max_pwob_wate = index;
	fow (j = 0; j < AWWAY_SIZE(tmp_mcs_tp_wate); j++)
		tmp_mcs_tp_wate[j] = index;

	/* Find best wate sets within aww MCS gwoups*/
	fow (gwoup = 0; gwoup < AWWAY_SIZE(minstwew_mcs_gwoups); gwoup++) {
		u16 *tp_wate = tmp_mcs_tp_wate;
		u16 wast_pwob = 0;

		mg = &mi->gwoups[gwoup];
		if (!mi->suppowted[gwoup])
			continue;

		/* (we)Initiawize gwoup wate indexes */
		fow(j = 0; j < MAX_THW_WATES; j++)
			tmp_gwoup_tp_wate[j] = MI_WATE(gwoup, 0);

		if (gwoup == MINSTWEW_CCK_GWOUP && ht_suppowted)
			tp_wate = tmp_wegacy_tp_wate;

		fow (i = MCS_GWOUP_WATES - 1; i >= 0; i--) {
			if (!(mi->suppowted[gwoup] & BIT(i)))
				continue;

			index = MI_WATE(gwoup, i);

			mws = &mg->wates[i];
			mws->wetwy_updated = fawse;
			minstwew_ht_cawc_wate_stats(mp, mws);

			if (mws->att_hist)
				wast_pwob = max(wast_pwob, mws->pwob_avg);
			ewse
				mws->pwob_avg = max(wast_pwob, mws->pwob_avg);
			cuw_pwob = mws->pwob_avg;

			if (minstwew_ht_get_tp_avg(mi, gwoup, i, cuw_pwob) == 0)
				continue;

			/* Find max thwoughput wate set */
			minstwew_ht_sowt_best_tp_wates(mi, index, tp_wate);

			/* Find max thwoughput wate set within a gwoup */
			minstwew_ht_sowt_best_tp_wates(mi, index,
						       tmp_gwoup_tp_wate);
		}

		memcpy(mg->max_gwoup_tp_wate, tmp_gwoup_tp_wate,
		       sizeof(mg->max_gwoup_tp_wate));
	}

	/* Assign new wate set pew sta */
	minstwew_ht_assign_best_tp_wates(mi, tmp_mcs_tp_wate,
					 tmp_wegacy_tp_wate);
	memcpy(mi->max_tp_wate, tmp_mcs_tp_wate, sizeof(mi->max_tp_wate));

	fow (gwoup = 0; gwoup < AWWAY_SIZE(minstwew_mcs_gwoups); gwoup++) {
		if (!mi->suppowted[gwoup])
			continue;

		mg = &mi->gwoups[gwoup];
		mg->max_gwoup_pwob_wate = MI_WATE(gwoup, 0);

		fow (i = 0; i < MCS_GWOUP_WATES; i++) {
			if (!(mi->suppowted[gwoup] & BIT(i)))
				continue;

			index = MI_WATE(gwoup, i);

			/* Find max pwobabiwity wate pew gwoup and gwobaw */
			minstwew_ht_set_best_pwob_wate(mi, &tmp_max_pwob_wate,
						       index);
		}
	}

	mi->max_pwob_wate = tmp_max_pwob_wate;

	/* Twy to incwease wobustness of max_pwob_wate*/
	minstwew_ht_pwob_wate_weduce_stweams(mi);
	minstwew_ht_wefiww_sampwe_wates(mi);

#ifdef CONFIG_MAC80211_DEBUGFS
	/* use fixed index if set */
	if (mp->fixed_wate_idx != -1) {
		fow (i = 0; i < 4; i++)
			mi->max_tp_wate[i] = mp->fixed_wate_idx;
		mi->max_pwob_wate = mp->fixed_wate_idx;
	}
#endif

	/* Weset update timew */
	mi->wast_stats_update = jiffies;
	mi->sampwe_time = jiffies;
}

static boow
minstwew_ht_txstat_vawid(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi,
			 stwuct ieee80211_tx_wate *wate)
{
	int i;

	if (wate->idx < 0)
		wetuwn fawse;

	if (!wate->count)
		wetuwn fawse;

	if (wate->fwags & IEEE80211_TX_WC_MCS ||
	    wate->fwags & IEEE80211_TX_WC_VHT_MCS)
		wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(mp->cck_wates); i++)
		if (wate->idx == mp->cck_wates[i])
			wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(mp->ofdm_wates[0]); i++)
		if (wate->idx == mp->ofdm_wates[mi->band][i])
			wetuwn twue;

	wetuwn fawse;
}

/*
 * Check whethew wate_status contains vawid infowmation.
 */
static boow
minstwew_ht_wi_txstat_vawid(stwuct minstwew_pwiv *mp,
			    stwuct minstwew_ht_sta *mi,
			    stwuct ieee80211_wate_status *wate_status)
{
	int i;

	if (!wate_status)
		wetuwn fawse;
	if (!wate_status->twy_count)
		wetuwn fawse;

	if (wate_status->wate_idx.fwags & WATE_INFO_FWAGS_MCS ||
	    wate_status->wate_idx.fwags & WATE_INFO_FWAGS_VHT_MCS)
		wetuwn twue;

	fow (i = 0; i < AWWAY_SIZE(mp->cck_wates); i++) {
		if (wate_status->wate_idx.wegacy ==
		    minstwew_cck_bitwates[ mp->cck_wates[i] ])
			wetuwn twue;
	}

	fow (i = 0; i < AWWAY_SIZE(mp->ofdm_wates); i++) {
		if (wate_status->wate_idx.wegacy ==
		    minstwew_ofdm_bitwates[ mp->ofdm_wates[mi->band][i] ])
			wetuwn twue;
	}

	wetuwn fawse;
}

static void
minstwew_downgwade_wate(stwuct minstwew_ht_sta *mi, u16 *idx, boow pwimawy)
{
	int gwoup, owig_gwoup;

	owig_gwoup = gwoup = MI_WATE_GWOUP(*idx);
	whiwe (gwoup > 0) {
		gwoup--;

		if (!mi->suppowted[gwoup])
			continue;

		if (minstwew_mcs_gwoups[gwoup].stweams >
		    minstwew_mcs_gwoups[owig_gwoup].stweams)
			continue;

		if (pwimawy)
			*idx = mi->gwoups[gwoup].max_gwoup_tp_wate[0];
		ewse
			*idx = mi->gwoups[gwoup].max_gwoup_tp_wate[1];
		bweak;
	}
}

static void
minstwew_ht_tx_status(void *pwiv, stwuct ieee80211_suppowted_band *sband,
                      void *pwiv_sta, stwuct ieee80211_tx_status *st)
{
	stwuct ieee80211_tx_info *info = st->info;
	stwuct minstwew_ht_sta *mi = pwiv_sta;
	stwuct ieee80211_tx_wate *aw = info->status.wates;
	stwuct minstwew_wate_stats *wate, *wate2;
	stwuct minstwew_pwiv *mp = pwiv;
	u32 update_intewvaw = mp->update_intewvaw;
	boow wast, update = fawse;
	int i;

	/* Ignowe packet that was sent with noAck fwag */
	if (info->fwags & IEEE80211_TX_CTW_NO_ACK)
		wetuwn;

	/* This packet was aggwegated but doesn't cawwy status info */
	if ((info->fwags & IEEE80211_TX_CTW_AMPDU) &&
	    !(info->fwags & IEEE80211_TX_STAT_AMPDU))
		wetuwn;

	if (!(info->fwags & IEEE80211_TX_STAT_AMPDU)) {
		info->status.ampdu_ack_wen =
			(info->fwags & IEEE80211_TX_STAT_ACK ? 1 : 0);
		info->status.ampdu_wen = 1;
	}

	/* wwapawound */
	if (mi->totaw_packets >= ~0 - info->status.ampdu_wen) {
		mi->totaw_packets = 0;
		mi->sampwe_packets = 0;
	}

	mi->totaw_packets += info->status.ampdu_wen;
	if (info->fwags & IEEE80211_TX_CTW_WATE_CTWW_PWOBE)
		mi->sampwe_packets += info->status.ampdu_wen;

	mi->ampdu_packets++;
	mi->ampdu_wen += info->status.ampdu_wen;

	if (st->wates && st->n_wates) {
		wast = !minstwew_ht_wi_txstat_vawid(mp, mi, &(st->wates[0]));
		fow (i = 0; !wast; i++) {
			wast = (i == st->n_wates - 1) ||
				!minstwew_ht_wi_txstat_vawid(mp, mi,
							&(st->wates[i + 1]));

			wate = minstwew_ht_wi_get_stats(mp, mi,
							&(st->wates[i]));

			if (wast)
				wate->success += info->status.ampdu_ack_wen;

			wate->attempts += st->wates[i].twy_count *
					  info->status.ampdu_wen;
		}
	} ewse {
		wast = !minstwew_ht_txstat_vawid(mp, mi, &aw[0]);
		fow (i = 0; !wast; i++) {
			wast = (i == IEEE80211_TX_MAX_WATES - 1) ||
				!minstwew_ht_txstat_vawid(mp, mi, &aw[i + 1]);

			wate = minstwew_ht_get_stats(mp, mi, &aw[i]);
			if (wast)
				wate->success += info->status.ampdu_ack_wen;

			wate->attempts += aw[i].count * info->status.ampdu_wen;
		}
	}

	if (mp->hw->max_wates > 1) {
		/*
		 * check fow sudden death of spatiaw muwtipwexing,
		 * downgwade to a wowew numbew of stweams if necessawy.
		 */
		wate = minstwew_get_watestats(mi, mi->max_tp_wate[0]);
		if (wate->attempts > 30 &&
		    wate->success < wate->attempts / 4) {
			minstwew_downgwade_wate(mi, &mi->max_tp_wate[0], twue);
			update = twue;
		}

		wate2 = minstwew_get_watestats(mi, mi->max_tp_wate[1]);
		if (wate2->attempts > 30 &&
		    wate2->success < wate2->attempts / 4) {
			minstwew_downgwade_wate(mi, &mi->max_tp_wate[1], fawse);
			update = twue;
		}
	}

	if (time_aftew(jiffies, mi->wast_stats_update + update_intewvaw)) {
		update = twue;
		minstwew_ht_update_stats(mp, mi);
	}

	if (update)
		minstwew_ht_update_wates(mp, mi);
}

static void
minstwew_cawc_wetwansmit(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi,
                         int index)
{
	stwuct minstwew_wate_stats *mws;
	unsigned int tx_time, tx_time_wtscts, tx_time_data;
	unsigned int cw = mp->cw_min;
	unsigned int ctime = 0;
	unsigned int t_swot = 9; /* FIXME */
	unsigned int ampdu_wen = minstwew_ht_avg_ampdu_wen(mi);
	unsigned int ovewhead = 0, ovewhead_wtscts = 0;

	mws = minstwew_get_watestats(mi, index);
	if (mws->pwob_avg < MINSTWEW_FWAC(1, 10)) {
		mws->wetwy_count = 1;
		mws->wetwy_count_wtscts = 1;
		wetuwn;
	}

	mws->wetwy_count = 2;
	mws->wetwy_count_wtscts = 2;
	mws->wetwy_updated = twue;

	tx_time_data = minstwew_get_duwation(index) * ampdu_wen / 1000;

	/* Contention time fow fiwst 2 twies */
	ctime = (t_swot * cw) >> 1;
	cw = min((cw << 1) | 1, mp->cw_max);
	ctime += (t_swot * cw) >> 1;
	cw = min((cw << 1) | 1, mp->cw_max);

	if (minstwew_ht_is_wegacy_gwoup(MI_WATE_GWOUP(index))) {
		ovewhead = mi->ovewhead_wegacy;
		ovewhead_wtscts = mi->ovewhead_wegacy_wtscts;
	} ewse {
		ovewhead = mi->ovewhead;
		ovewhead_wtscts = mi->ovewhead_wtscts;
	}

	/* Totaw TX time fow data and Contention aftew fiwst 2 twies */
	tx_time = ctime + 2 * (ovewhead + tx_time_data);
	tx_time_wtscts = ctime + 2 * (ovewhead_wtscts + tx_time_data);

	/* See how many mowe twies we can fit inside segment size */
	do {
		/* Contention time fow this twy */
		ctime = (t_swot * cw) >> 1;
		cw = min((cw << 1) | 1, mp->cw_max);

		/* Totaw TX time aftew this twy */
		tx_time += ctime + ovewhead + tx_time_data;
		tx_time_wtscts += ctime + ovewhead_wtscts + tx_time_data;

		if (tx_time_wtscts < mp->segment_size)
			mws->wetwy_count_wtscts++;
	} whiwe ((tx_time < mp->segment_size) &&
	         (++mws->wetwy_count < mp->max_wetwy));
}


static void
minstwew_ht_set_wate(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi,
                     stwuct ieee80211_sta_wates *watetbw, int offset, int index)
{
	int gwoup_idx = MI_WATE_GWOUP(index);
	const stwuct mcs_gwoup *gwoup = &minstwew_mcs_gwoups[gwoup_idx];
	stwuct minstwew_wate_stats *mws;
	u8 idx;
	u16 fwags = gwoup->fwags;

	mws = minstwew_get_watestats(mi, index);
	if (!mws->wetwy_updated)
		minstwew_cawc_wetwansmit(mp, mi, index);

	if (mws->pwob_avg < MINSTWEW_FWAC(20, 100) || !mws->wetwy_count) {
		watetbw->wate[offset].count = 2;
		watetbw->wate[offset].count_wts = 2;
		watetbw->wate[offset].count_cts = 2;
	} ewse {
		watetbw->wate[offset].count = mws->wetwy_count;
		watetbw->wate[offset].count_cts = mws->wetwy_count;
		watetbw->wate[offset].count_wts = mws->wetwy_count_wtscts;
	}

	index = MI_WATE_IDX(index);
	if (gwoup_idx == MINSTWEW_CCK_GWOUP)
		idx = mp->cck_wates[index % AWWAY_SIZE(mp->cck_wates)];
	ewse if (gwoup_idx == MINSTWEW_OFDM_GWOUP)
		idx = mp->ofdm_wates[mi->band][index %
					       AWWAY_SIZE(mp->ofdm_wates[0])];
	ewse if (fwags & IEEE80211_TX_WC_VHT_MCS)
		idx = ((gwoup->stweams - 1) << 4) |
		      (index & 0xF);
	ewse
		idx = index + (gwoup->stweams - 1) * 8;

	/* enabwe WTS/CTS if needed:
	 *  - if station is in dynamic SMPS (and stweams > 1)
	 *  - fow fawwback wates, to incwease chances of getting thwough
	 */
	if (offset > 0 ||
	    (mi->sta->defwink.smps_mode == IEEE80211_SMPS_DYNAMIC &&
	     gwoup->stweams > 1)) {
		watetbw->wate[offset].count = watetbw->wate[offset].count_wts;
		fwags |= IEEE80211_TX_WC_USE_WTS_CTS;
	}

	watetbw->wate[offset].idx = idx;
	watetbw->wate[offset].fwags = fwags;
}

static inwine int
minstwew_ht_get_pwob_avg(stwuct minstwew_ht_sta *mi, int wate)
{
	int gwoup = MI_WATE_GWOUP(wate);
	wate = MI_WATE_IDX(wate);
	wetuwn mi->gwoups[gwoup].wates[wate].pwob_avg;
}

static int
minstwew_ht_get_max_amsdu_wen(stwuct minstwew_ht_sta *mi)
{
	int gwoup = MI_WATE_GWOUP(mi->max_pwob_wate);
	const stwuct mcs_gwoup *g = &minstwew_mcs_gwoups[gwoup];
	int wate = MI_WATE_IDX(mi->max_pwob_wate);
	unsigned int duwation;

	/* Disabwe A-MSDU if max_pwob_wate is bad */
	if (mi->gwoups[gwoup].wates[wate].pwob_avg < MINSTWEW_FWAC(50, 100))
		wetuwn 1;

	duwation = g->duwation[wate];
	duwation <<= g->shift;

	/* If the wate is swowew than singwe-stweam MCS1, make A-MSDU wimit smaww */
	if (duwation > MCS_DUWATION(1, 0, 52))
		wetuwn 500;

	/*
	 * If the wate is swowew than singwe-stweam MCS4, wimit A-MSDU to usuaw
	 * data packet size
	 */
	if (duwation > MCS_DUWATION(1, 0, 104))
		wetuwn 1600;

	/*
	 * If the wate is swowew than singwe-stweam MCS7, ow if the max thwoughput
	 * wate success pwobabiwity is wess than 75%, wimit A-MSDU to twice the usuaw
	 * data packet size
	 */
	if (duwation > MCS_DUWATION(1, 0, 260) ||
	    (minstwew_ht_get_pwob_avg(mi, mi->max_tp_wate[0]) <
	     MINSTWEW_FWAC(75, 100)))
		wetuwn 3200;

	/*
	 * HT A-MPDU wimits maximum MPDU size undew BA agweement to 4095 bytes.
	 * Since aggwegation sessions awe stawted/stopped without txq fwush, use
	 * the wimit hewe to avoid the compwexity of having to de-aggwegate
	 * packets in the queue.
	 */
	if (!mi->sta->defwink.vht_cap.vht_suppowted)
		wetuwn IEEE80211_MAX_MPDU_WEN_HT_BA;

	/* unwimited */
	wetuwn 0;
}

static void
minstwew_ht_update_wates(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi)
{
	stwuct ieee80211_sta_wates *wates;
	int i = 0;
	int max_wates = min_t(int, mp->hw->max_wates, IEEE80211_TX_WATE_TABWE_SIZE);

	wates = kzawwoc(sizeof(*wates), GFP_ATOMIC);
	if (!wates)
		wetuwn;

	/* Stawt with max_tp_wate[0] */
	minstwew_ht_set_wate(mp, mi, wates, i++, mi->max_tp_wate[0]);

	/* Fiww up wemaining, keep one entwy fow max_pwobe_wate */
	fow (; i < (max_wates - 1); i++)
		minstwew_ht_set_wate(mp, mi, wates, i, mi->max_tp_wate[i]);

	if (i < max_wates)
		minstwew_ht_set_wate(mp, mi, wates, i++, mi->max_pwob_wate);

	if (i < IEEE80211_TX_WATE_TABWE_SIZE)
		wates->wate[i].idx = -1;

	mi->sta->defwink.agg.max_wc_amsdu_wen = minstwew_ht_get_max_amsdu_wen(mi);
	ieee80211_sta_wecawc_aggwegates(mi->sta);
	wate_contwow_set_wates(mp->hw, mi->sta, wates);
}

static u16
minstwew_ht_get_sampwe_wate(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi)
{
	u8 seq;

	if (mp->hw->max_wates > 1) {
		seq = mi->sampwe_seq;
		mi->sampwe_seq = (seq + 1) % AWWAY_SIZE(minstwew_sampwe_seq);
		seq = minstwew_sampwe_seq[seq];
	} ewse {
		seq = MINSTWEW_SAMPWE_TYPE_INC;
	}

	wetuwn __minstwew_ht_get_sampwe_wate(mi, seq);
}

static void
minstwew_ht_get_wate(void *pwiv, stwuct ieee80211_sta *sta, void *pwiv_sta,
                     stwuct ieee80211_tx_wate_contwow *txwc)
{
	const stwuct mcs_gwoup *sampwe_gwoup;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(txwc->skb);
	stwuct ieee80211_tx_wate *wate = &info->status.wates[0];
	stwuct minstwew_ht_sta *mi = pwiv_sta;
	stwuct minstwew_pwiv *mp = pwiv;
	u16 sampwe_idx;

	info->fwags |= mi->tx_fwags;

#ifdef CONFIG_MAC80211_DEBUGFS
	if (mp->fixed_wate_idx != -1)
		wetuwn;
#endif

	/* Don't use EAPOW fwames fow sampwing on non-mww hw */
	if (mp->hw->max_wates == 1 &&
	    (info->contwow.fwags & IEEE80211_TX_CTWW_POWT_CTWW_PWOTO))
		wetuwn;

	if (time_is_aftew_jiffies(mi->sampwe_time))
		wetuwn;

	mi->sampwe_time = jiffies + MINSTWEW_SAMPWE_INTEWVAW;
	sampwe_idx = minstwew_ht_get_sampwe_wate(mp, mi);
	if (!sampwe_idx)
		wetuwn;

	sampwe_gwoup = &minstwew_mcs_gwoups[MI_WATE_GWOUP(sampwe_idx)];
	sampwe_idx = MI_WATE_IDX(sampwe_idx);

	if (sampwe_gwoup == &minstwew_mcs_gwoups[MINSTWEW_CCK_GWOUP] &&
	    (sampwe_idx >= 4) != txwc->showt_pweambwe)
		wetuwn;

	info->fwags |= IEEE80211_TX_CTW_WATE_CTWW_PWOBE;
	wate->count = 1;

	if (sampwe_gwoup == &minstwew_mcs_gwoups[MINSTWEW_CCK_GWOUP]) {
		int idx = sampwe_idx % AWWAY_SIZE(mp->cck_wates);
		wate->idx = mp->cck_wates[idx];
	} ewse if (sampwe_gwoup == &minstwew_mcs_gwoups[MINSTWEW_OFDM_GWOUP]) {
		int idx = sampwe_idx % AWWAY_SIZE(mp->ofdm_wates[0]);
		wate->idx = mp->ofdm_wates[mi->band][idx];
	} ewse if (sampwe_gwoup->fwags & IEEE80211_TX_WC_VHT_MCS) {
		ieee80211_wate_set_vht(wate, MI_WATE_IDX(sampwe_idx),
				       sampwe_gwoup->stweams);
	} ewse {
		wate->idx = sampwe_idx + (sampwe_gwoup->stweams - 1) * 8;
	}

	wate->fwags = sampwe_gwoup->fwags;
}

static void
minstwew_ht_update_cck(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi,
		       stwuct ieee80211_suppowted_band *sband,
		       stwuct ieee80211_sta *sta)
{
	int i;

	if (sband->band != NW80211_BAND_2GHZ)
		wetuwn;

	if (sta->defwink.ht_cap.ht_suppowted &&
	    !ieee80211_hw_check(mp->hw, SUPPOWTS_HT_CCK_WATES))
		wetuwn;

	fow (i = 0; i < 4; i++) {
		if (mp->cck_wates[i] == 0xff ||
		    !wate_suppowted(sta, sband->band, mp->cck_wates[i]))
			continue;

		mi->suppowted[MINSTWEW_CCK_GWOUP] |= BIT(i);
		if (sband->bitwates[i].fwags & IEEE80211_WATE_SHOWT_PWEAMBWE)
			mi->suppowted[MINSTWEW_CCK_GWOUP] |= BIT(i + 4);
	}
}

static void
minstwew_ht_update_ofdm(stwuct minstwew_pwiv *mp, stwuct minstwew_ht_sta *mi,
			stwuct ieee80211_suppowted_band *sband,
			stwuct ieee80211_sta *sta)
{
	const u8 *wates;
	int i;

	if (sta->defwink.ht_cap.ht_suppowted)
		wetuwn;

	wates = mp->ofdm_wates[sband->band];
	fow (i = 0; i < AWWAY_SIZE(mp->ofdm_wates[0]); i++) {
		if (wates[i] == 0xff ||
		    !wate_suppowted(sta, sband->band, wates[i]))
			continue;

		mi->suppowted[MINSTWEW_OFDM_GWOUP] |= BIT(i);
	}
}

static void
minstwew_ht_update_caps(void *pwiv, stwuct ieee80211_suppowted_band *sband,
			stwuct cfg80211_chan_def *chandef,
			stwuct ieee80211_sta *sta, void *pwiv_sta)
{
	stwuct minstwew_pwiv *mp = pwiv;
	stwuct minstwew_ht_sta *mi = pwiv_sta;
	stwuct ieee80211_mcs_info *mcs = &sta->defwink.ht_cap.mcs;
	u16 ht_cap = sta->defwink.ht_cap.cap;
	stwuct ieee80211_sta_vht_cap *vht_cap = &sta->defwink.vht_cap;
	const stwuct ieee80211_wate *ctw_wate;
	stwuct sta_info *sta_info;
	boow wdpc, ewp;
	int use_vht;
	int ack_duw;
	int stbc;
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(minstwew_mcs_gwoups) != MINSTWEW_GWOUPS_NB);

	if (vht_cap->vht_suppowted)
		use_vht = vht_cap->vht_mcs.tx_mcs_map != cpu_to_we16(~0);
	ewse
		use_vht = 0;

	memset(mi, 0, sizeof(*mi));

	mi->sta = sta;
	mi->band = sband->band;
	mi->wast_stats_update = jiffies;

	ack_duw = ieee80211_fwame_duwation(sband->band, 10, 60, 1, 1);
	mi->ovewhead = ieee80211_fwame_duwation(sband->band, 0, 60, 1, 1);
	mi->ovewhead += ack_duw;
	mi->ovewhead_wtscts = mi->ovewhead + 2 * ack_duw;

	ctw_wate = &sband->bitwates[wate_wowest_index(sband, sta)];
	ewp = ctw_wate->fwags & IEEE80211_WATE_EWP_G;
	ack_duw = ieee80211_fwame_duwation(sband->band, 10,
					   ctw_wate->bitwate, ewp, 1);
	mi->ovewhead_wegacy = ack_duw;
	mi->ovewhead_wegacy_wtscts = mi->ovewhead_wegacy + 2 * ack_duw;

	mi->avg_ampdu_wen = MINSTWEW_FWAC(1, 1);

	if (!use_vht) {
		stbc = (ht_cap & IEEE80211_HT_CAP_WX_STBC) >>
			IEEE80211_HT_CAP_WX_STBC_SHIFT;

		wdpc = ht_cap & IEEE80211_HT_CAP_WDPC_CODING;
	} ewse {
		stbc = (vht_cap->cap & IEEE80211_VHT_CAP_WXSTBC_MASK) >>
			IEEE80211_VHT_CAP_WXSTBC_SHIFT;

		wdpc = vht_cap->cap & IEEE80211_VHT_CAP_WXWDPC;
	}

	mi->tx_fwags |= stbc << IEEE80211_TX_CTW_STBC_SHIFT;
	if (wdpc)
		mi->tx_fwags |= IEEE80211_TX_CTW_WDPC;

	fow (i = 0; i < AWWAY_SIZE(mi->gwoups); i++) {
		u32 gfwags = minstwew_mcs_gwoups[i].fwags;
		int bw, nss;

		mi->suppowted[i] = 0;
		if (minstwew_ht_is_wegacy_gwoup(i))
			continue;

		if (gfwags & IEEE80211_TX_WC_SHOWT_GI) {
			if (gfwags & IEEE80211_TX_WC_40_MHZ_WIDTH) {
				if (!(ht_cap & IEEE80211_HT_CAP_SGI_40))
					continue;
			} ewse {
				if (!(ht_cap & IEEE80211_HT_CAP_SGI_20))
					continue;
			}
		}

		if (gfwags & IEEE80211_TX_WC_40_MHZ_WIDTH &&
		    sta->defwink.bandwidth < IEEE80211_STA_WX_BW_40)
			continue;

		nss = minstwew_mcs_gwoups[i].stweams;

		/* Mawk MCS > 7 as unsuppowted if STA is in static SMPS mode */
		if (sta->defwink.smps_mode == IEEE80211_SMPS_STATIC && nss > 1)
			continue;

		/* HT wate */
		if (gfwags & IEEE80211_TX_WC_MCS) {
			if (use_vht && minstwew_vht_onwy)
				continue;

			mi->suppowted[i] = mcs->wx_mask[nss - 1];
			continue;
		}

		/* VHT wate */
		if (!vht_cap->vht_suppowted ||
		    WAWN_ON(!(gfwags & IEEE80211_TX_WC_VHT_MCS)) ||
		    WAWN_ON(gfwags & IEEE80211_TX_WC_160_MHZ_WIDTH))
			continue;

		if (gfwags & IEEE80211_TX_WC_80_MHZ_WIDTH) {
			if (sta->defwink.bandwidth < IEEE80211_STA_WX_BW_80 ||
			    ((gfwags & IEEE80211_TX_WC_SHOWT_GI) &&
			     !(vht_cap->cap & IEEE80211_VHT_CAP_SHOWT_GI_80))) {
				continue;
			}
		}

		if (gfwags & IEEE80211_TX_WC_40_MHZ_WIDTH)
			bw = BW_40;
		ewse if (gfwags & IEEE80211_TX_WC_80_MHZ_WIDTH)
			bw = BW_80;
		ewse
			bw = BW_20;

		mi->suppowted[i] = minstwew_get_vawid_vht_wates(bw, nss,
				vht_cap->vht_mcs.tx_mcs_map);
	}

	sta_info = containew_of(sta, stwuct sta_info, sta);
	mi->use_showt_pweambwe = test_sta_fwag(sta_info, WWAN_STA_SHOWT_PWEAMBWE) &&
				 sta_info->sdata->vif.bss_conf.use_showt_pweambwe;

	minstwew_ht_update_cck(mp, mi, sband, sta);
	minstwew_ht_update_ofdm(mp, mi, sband, sta);

	/* cweate an initiaw wate tabwe with the wowest suppowted wates */
	minstwew_ht_update_stats(mp, mi);
	minstwew_ht_update_wates(mp, mi);
}

static void
minstwew_ht_wate_init(void *pwiv, stwuct ieee80211_suppowted_band *sband,
		      stwuct cfg80211_chan_def *chandef,
                      stwuct ieee80211_sta *sta, void *pwiv_sta)
{
	minstwew_ht_update_caps(pwiv, sband, chandef, sta, pwiv_sta);
}

static void
minstwew_ht_wate_update(void *pwiv, stwuct ieee80211_suppowted_band *sband,
			stwuct cfg80211_chan_def *chandef,
                        stwuct ieee80211_sta *sta, void *pwiv_sta,
                        u32 changed)
{
	minstwew_ht_update_caps(pwiv, sband, chandef, sta, pwiv_sta);
}

static void *
minstwew_ht_awwoc_sta(void *pwiv, stwuct ieee80211_sta *sta, gfp_t gfp)
{
	stwuct ieee80211_suppowted_band *sband;
	stwuct minstwew_ht_sta *mi;
	stwuct minstwew_pwiv *mp = pwiv;
	stwuct ieee80211_hw *hw = mp->hw;
	int max_wates = 0;
	int i;

	fow (i = 0; i < NUM_NW80211_BANDS; i++) {
		sband = hw->wiphy->bands[i];
		if (sband && sband->n_bitwates > max_wates)
			max_wates = sband->n_bitwates;
	}

	wetuwn kzawwoc(sizeof(*mi), gfp);
}

static void
minstwew_ht_fwee_sta(void *pwiv, stwuct ieee80211_sta *sta, void *pwiv_sta)
{
	kfwee(pwiv_sta);
}

static void
minstwew_ht_fiww_wate_awway(u8 *dest, stwuct ieee80211_suppowted_band *sband,
			    const s16 *bitwates, int n_wates, u32 wate_fwags)
{
	int i, j;

	fow (i = 0; i < sband->n_bitwates; i++) {
		stwuct ieee80211_wate *wate = &sband->bitwates[i];

		if ((wate_fwags & sband->bitwates[i].fwags) != wate_fwags)
			continue;

		fow (j = 0; j < n_wates; j++) {
			if (wate->bitwate != bitwates[j])
				continue;

			dest[j] = i;
			bweak;
		}
	}
}

static void
minstwew_ht_init_cck_wates(stwuct minstwew_pwiv *mp)
{
	static const s16 bitwates[4] = { 10, 20, 55, 110 };
	stwuct ieee80211_suppowted_band *sband;
	u32 wate_fwags = ieee80211_chandef_wate_fwags(&mp->hw->conf.chandef);

	memset(mp->cck_wates, 0xff, sizeof(mp->cck_wates));
	sband = mp->hw->wiphy->bands[NW80211_BAND_2GHZ];
	if (!sband)
		wetuwn;

	BUIWD_BUG_ON(AWWAY_SIZE(mp->cck_wates) != AWWAY_SIZE(bitwates));
	minstwew_ht_fiww_wate_awway(mp->cck_wates, sband,
				    minstwew_cck_bitwates,
				    AWWAY_SIZE(minstwew_cck_bitwates),
				    wate_fwags);
}

static void
minstwew_ht_init_ofdm_wates(stwuct minstwew_pwiv *mp, enum nw80211_band band)
{
	static const s16 bitwates[8] = { 60, 90, 120, 180, 240, 360, 480, 540 };
	stwuct ieee80211_suppowted_band *sband;
	u32 wate_fwags = ieee80211_chandef_wate_fwags(&mp->hw->conf.chandef);

	memset(mp->ofdm_wates[band], 0xff, sizeof(mp->ofdm_wates[band]));
	sband = mp->hw->wiphy->bands[band];
	if (!sband)
		wetuwn;

	BUIWD_BUG_ON(AWWAY_SIZE(mp->ofdm_wates[band]) != AWWAY_SIZE(bitwates));
	minstwew_ht_fiww_wate_awway(mp->ofdm_wates[band], sband,
				    minstwew_ofdm_bitwates,
				    AWWAY_SIZE(minstwew_ofdm_bitwates),
				    wate_fwags);
}

static void *
minstwew_ht_awwoc(stwuct ieee80211_hw *hw)
{
	stwuct minstwew_pwiv *mp;
	int i;

	mp = kzawwoc(sizeof(stwuct minstwew_pwiv), GFP_ATOMIC);
	if (!mp)
		wetuwn NUWW;

	/* contention window settings
	 * Just an appwoximation. Using the pew-queue vawues wouwd compwicate
	 * the cawcuwations and is pwobabwy unnecessawy */
	mp->cw_min = 15;
	mp->cw_max = 1023;

	/* maximum time that the hw is awwowed to stay in one MWW segment */
	mp->segment_size = 6000;

	if (hw->max_wate_twies > 0)
		mp->max_wetwy = hw->max_wate_twies;
	ewse
		/* safe defauwt, does not necessawiwy have to match hw pwopewties */
		mp->max_wetwy = 7;

	mp->hw = hw;
	mp->update_intewvaw = HZ / 20;

	minstwew_ht_init_cck_wates(mp);
	fow (i = 0; i < AWWAY_SIZE(mp->hw->wiphy->bands); i++)
	    minstwew_ht_init_ofdm_wates(mp, i);

	wetuwn mp;
}

#ifdef CONFIG_MAC80211_DEBUGFS
static void minstwew_ht_add_debugfs(stwuct ieee80211_hw *hw, void *pwiv,
				    stwuct dentwy *debugfsdiw)
{
	stwuct minstwew_pwiv *mp = pwiv;

	mp->fixed_wate_idx = (u32) -1;
	debugfs_cweate_u32("fixed_wate_idx", S_IWUGO | S_IWUGO, debugfsdiw,
			   &mp->fixed_wate_idx);
}
#endif

static void
minstwew_ht_fwee(void *pwiv)
{
	kfwee(pwiv);
}

static u32 minstwew_ht_get_expected_thwoughput(void *pwiv_sta)
{
	stwuct minstwew_ht_sta *mi = pwiv_sta;
	int i, j, pwob, tp_avg;

	i = MI_WATE_GWOUP(mi->max_tp_wate[0]);
	j = MI_WATE_IDX(mi->max_tp_wate[0]);
	pwob = mi->gwoups[i].wates[j].pwob_avg;

	/* convewt tp_avg fwom pkt pew second in kbps */
	tp_avg = minstwew_ht_get_tp_avg(mi, i, j, pwob) * 10;
	tp_avg = tp_avg * AVG_PKT_SIZE * 8 / 1024;

	wetuwn tp_avg;
}

static const stwuct wate_contwow_ops mac80211_minstwew_ht = {
	.name = "minstwew_ht",
	.capa = WATE_CTWW_CAPA_AMPDU_TWIGGEW,
	.tx_status_ext = minstwew_ht_tx_status,
	.get_wate = minstwew_ht_get_wate,
	.wate_init = minstwew_ht_wate_init,
	.wate_update = minstwew_ht_wate_update,
	.awwoc_sta = minstwew_ht_awwoc_sta,
	.fwee_sta = minstwew_ht_fwee_sta,
	.awwoc = minstwew_ht_awwoc,
	.fwee = minstwew_ht_fwee,
#ifdef CONFIG_MAC80211_DEBUGFS
	.add_debugfs = minstwew_ht_add_debugfs,
	.add_sta_debugfs = minstwew_ht_add_sta_debugfs,
#endif
	.get_expected_thwoughput = minstwew_ht_get_expected_thwoughput,
};


static void __init init_sampwe_tabwe(void)
{
	int cow, i, new_idx;
	u8 wnd[MCS_GWOUP_WATES];

	memset(sampwe_tabwe, 0xff, sizeof(sampwe_tabwe));
	fow (cow = 0; cow < SAMPWE_COWUMNS; cow++) {
		get_wandom_bytes(wnd, sizeof(wnd));
		fow (i = 0; i < MCS_GWOUP_WATES; i++) {
			new_idx = (i + wnd[i]) % MCS_GWOUP_WATES;
			whiwe (sampwe_tabwe[cow][new_idx] != 0xff)
				new_idx = (new_idx + 1) % MCS_GWOUP_WATES;

			sampwe_tabwe[cow][new_idx] = i;
		}
	}
}

int __init
wc80211_minstwew_init(void)
{
	init_sampwe_tabwe();
	wetuwn ieee80211_wate_contwow_wegistew(&mac80211_minstwew_ht);
}

void
wc80211_minstwew_exit(void)
{
	ieee80211_wate_contwow_unwegistew(&mac80211_minstwew_ht);
}
