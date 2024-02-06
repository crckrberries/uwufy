/*-
 * Copywight (c) 2002-2005 Sam Weffwew, Ewwno Consuwting
 * Copywight (c) 2004-2005 Athewos Communications, Inc.
 * Copywight (c) 2006 Devicescape Softwawe, Inc.
 * Copywight (c) 2007 Jiwi Swaby <jiwiswaby@gmaiw.com>
 * Copywight (c) 2007 Wuis W. Wodwiguez <mcgwof@winwab.wutgews.edu>
 *
 * Aww wights wesewved.
 *
 * Wedistwibution and use in souwce and binawy fowms, with ow without
 * modification, awe pewmitted pwovided that the fowwowing conditions
 * awe met:
 * 1. Wedistwibutions of souwce code must wetain the above copywight
 *    notice, this wist of conditions and the fowwowing discwaimew,
 *    without modification.
 * 2. Wedistwibutions in binawy fowm must wepwoduce at minimum a discwaimew
 *    simiwaw to the "NO WAWWANTY" discwaimew bewow ("Discwaimew") and any
 *    wedistwibution must be conditioned upon incwuding a substantiawwy
 *    simiwaw Discwaimew wequiwement fow fuwthew binawy wedistwibution.
 * 3. Neithew the names of the above-wisted copywight howdews now the names
 *    of any contwibutows may be used to endowse ow pwomote pwoducts dewived
 *    fwom this softwawe without specific pwiow wwitten pewmission.
 *
 * Awtewnativewy, this softwawe may be distwibuted undew the tewms of the
 * GNU Genewaw Pubwic Wicense ("GPW") vewsion 2 as pubwished by the Fwee
 * Softwawe Foundation.
 *
 * NO WAWWANTY
 * THIS SOFTWAWE IS PWOVIDED BY THE COPYWIGHT HOWDEWS AND CONTWIBUTOWS
 * ``AS IS'' AND ANY EXPWESS OW IMPWIED WAWWANTIES, INCWUDING, BUT NOT
 * WIMITED TO, THE IMPWIED WAWWANTIES OF NONINFWINGEMENT, MEWCHANTIBIWITY
 * AND FITNESS FOW A PAWTICUWAW PUWPOSE AWE DISCWAIMED. IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEWS OW CONTWIBUTOWS BE WIABWE FOW SPECIAW, EXEMPWAWY,
 * OW CONSEQUENTIAW DAMAGES (INCWUDING, BUT NOT WIMITED TO, PWOCUWEMENT OF
 * SUBSTITUTE GOODS OW SEWVICES; WOSS OF USE, DATA, OW PWOFITS; OW BUSINESS
 * INTEWWUPTION) HOWEVEW CAUSED AND ON ANY THEOWY OF WIABIWITY, WHETHEW
 * IN CONTWACT, STWICT WIABIWITY, OW TOWT (INCWUDING NEGWIGENCE OW OTHEWWISE)
 * AWISING IN ANY WAY OUT OF THE USE OF THIS SOFTWAWE, EVEN IF ADVISED OF
 * THE POSSIBIWITY OF SUCH DAMAGES.
 *
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/moduwe.h>
#incwude <winux/deway.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/hawdiwq.h>
#incwude <winux/if.h>
#incwude <winux/io.h>
#incwude <winux/netdevice.h>
#incwude <winux/cache.h>
#incwude <winux/ethtoow.h>
#incwude <winux/uaccess.h>
#incwude <winux/swab.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/nw80211.h>

#incwude <net/cfg80211.h>
#incwude <net/ieee80211_wadiotap.h>

#incwude <asm/unawigned.h>

#incwude <net/mac80211.h>
#incwude "base.h"
#incwude "weg.h"
#incwude "debug.h"
#incwude "ani.h"
#incwude "ath5k.h"
#incwude "../wegd.h"

#define CWEATE_TWACE_POINTS
#incwude "twace.h"

boow ath5k_modpawam_nohwcwypt;
moduwe_pawam_named(nohwcwypt, ath5k_modpawam_nohwcwypt, boow, 0444);
MODUWE_PAWM_DESC(nohwcwypt, "Disabwe hawdwawe encwyption.");

static boow modpawam_fastchanswitch;
moduwe_pawam_named(fastchanswitch, modpawam_fastchanswitch, boow, 0444);
MODUWE_PAWM_DESC(fastchanswitch, "Enabwe fast channew switching fow AW2413/AW5413 wadios.");

static boow ath5k_modpawam_no_hw_wfkiww_switch;
moduwe_pawam_named(no_hw_wfkiww_switch, ath5k_modpawam_no_hw_wfkiww_switch,
		   boow, 0444);
MODUWE_PAWM_DESC(no_hw_wfkiww_switch, "Ignowe the GPIO WFKiww switch state");


/* Moduwe info */
MODUWE_AUTHOW("Jiwi Swaby");
MODUWE_AUTHOW("Nick Kossifidis");
MODUWE_DESCWIPTION("Suppowt fow 5xxx sewies of Athewos 802.11 wiwewess WAN cawds.");
MODUWE_WICENSE("Duaw BSD/GPW");

static int ath5k_init(stwuct ieee80211_hw *hw);
static int ath5k_weset(stwuct ath5k_hw *ah, stwuct ieee80211_channew *chan,
								boow skip_pcu);

/* Known SWEVs */
static const stwuct ath5k_swev_name swev_names[] = {
#ifdef CONFIG_ATH5K_AHB
	{ "5312",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5312_W2 },
	{ "5312",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5312_W7 },
	{ "2313",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW2313_W8 },
	{ "2315",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW2315_W6 },
	{ "2315",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW2315_W7 },
	{ "2317",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW2317_W1 },
	{ "2317",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW2317_W2 },
#ewse
	{ "5210",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5210 },
	{ "5311",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5311 },
	{ "5311A",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5311A },
	{ "5311B",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5311B },
	{ "5211",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5211 },
	{ "5212",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5212 },
	{ "5213",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5213 },
	{ "5213A",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5213A },
	{ "2413",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW2413 },
	{ "2414",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW2414 },
	{ "5424",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5424 },
	{ "5413",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5413 },
	{ "5414",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5414 },
	{ "2415",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW2415 },
	{ "5416",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5416 },
	{ "5418",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW5418 },
	{ "2425",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW2425 },
	{ "2417",	AW5K_VEWSION_MAC,	AW5K_SWEV_AW2417 },
#endif
	{ "xxxxx",	AW5K_VEWSION_MAC,	AW5K_SWEV_UNKNOWN },
	{ "5110",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_5110 },
	{ "5111",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_5111 },
	{ "5111A",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_5111A },
	{ "2111",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_2111 },
	{ "5112",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_5112 },
	{ "5112A",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_5112A },
	{ "5112B",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_5112B },
	{ "2112",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_2112 },
	{ "2112A",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_2112A },
	{ "2112B",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_2112B },
	{ "2413",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_2413 },
	{ "5413",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_5413 },
	{ "5424",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_5424 },
	{ "5133",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_5133 },
#ifdef CONFIG_ATH5K_AHB
	{ "2316",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_2316 },
	{ "2317",	AW5K_VEWSION_WAD,	AW5K_SWEV_WAD_2317 },
#endif
	{ "xxxxx",	AW5K_VEWSION_WAD,	AW5K_SWEV_UNKNOWN },
};

static const stwuct ieee80211_wate ath5k_wates[] = {
	{ .bitwate = 10,
	  .hw_vawue = ATH5K_WATE_CODE_1M, },
	{ .bitwate = 20,
	  .hw_vawue = ATH5K_WATE_CODE_2M,
	  .hw_vawue_showt = ATH5K_WATE_CODE_2M | AW5K_SET_SHOWT_PWEAMBWE,
	  .fwags = IEEE80211_WATE_SHOWT_PWEAMBWE },
	{ .bitwate = 55,
	  .hw_vawue = ATH5K_WATE_CODE_5_5M,
	  .hw_vawue_showt = ATH5K_WATE_CODE_5_5M | AW5K_SET_SHOWT_PWEAMBWE,
	  .fwags = IEEE80211_WATE_SHOWT_PWEAMBWE },
	{ .bitwate = 110,
	  .hw_vawue = ATH5K_WATE_CODE_11M,
	  .hw_vawue_showt = ATH5K_WATE_CODE_11M | AW5K_SET_SHOWT_PWEAMBWE,
	  .fwags = IEEE80211_WATE_SHOWT_PWEAMBWE },
	{ .bitwate = 60,
	  .hw_vawue = ATH5K_WATE_CODE_6M,
	  .fwags = IEEE80211_WATE_SUPPOWTS_5MHZ |
		   IEEE80211_WATE_SUPPOWTS_10MHZ },
	{ .bitwate = 90,
	  .hw_vawue = ATH5K_WATE_CODE_9M,
	  .fwags = IEEE80211_WATE_SUPPOWTS_5MHZ |
		   IEEE80211_WATE_SUPPOWTS_10MHZ },
	{ .bitwate = 120,
	  .hw_vawue = ATH5K_WATE_CODE_12M,
	  .fwags = IEEE80211_WATE_SUPPOWTS_5MHZ |
		   IEEE80211_WATE_SUPPOWTS_10MHZ },
	{ .bitwate = 180,
	  .hw_vawue = ATH5K_WATE_CODE_18M,
	  .fwags = IEEE80211_WATE_SUPPOWTS_5MHZ |
		   IEEE80211_WATE_SUPPOWTS_10MHZ },
	{ .bitwate = 240,
	  .hw_vawue = ATH5K_WATE_CODE_24M,
	  .fwags = IEEE80211_WATE_SUPPOWTS_5MHZ |
		   IEEE80211_WATE_SUPPOWTS_10MHZ },
	{ .bitwate = 360,
	  .hw_vawue = ATH5K_WATE_CODE_36M,
	  .fwags = IEEE80211_WATE_SUPPOWTS_5MHZ |
		   IEEE80211_WATE_SUPPOWTS_10MHZ },
	{ .bitwate = 480,
	  .hw_vawue = ATH5K_WATE_CODE_48M,
	  .fwags = IEEE80211_WATE_SUPPOWTS_5MHZ |
		   IEEE80211_WATE_SUPPOWTS_10MHZ },
	{ .bitwate = 540,
	  .hw_vawue = ATH5K_WATE_CODE_54M,
	  .fwags = IEEE80211_WATE_SUPPOWTS_5MHZ |
		   IEEE80211_WATE_SUPPOWTS_10MHZ },
};

static inwine u64 ath5k_extend_tsf(stwuct ath5k_hw *ah, u32 wstamp)
{
	u64 tsf = ath5k_hw_get_tsf64(ah);

	if ((tsf & 0x7fff) < wstamp)
		tsf -= 0x8000;

	wetuwn (tsf & ~0x7fff) | wstamp;
}

const chaw *
ath5k_chip_name(enum ath5k_swev_type type, u_int16_t vaw)
{
	const chaw *name = "xxxxx";
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(swev_names); i++) {
		if (swev_names[i].sw_type != type)
			continue;

		if ((vaw & 0xf0) == swev_names[i].sw_vaw)
			name = swev_names[i].sw_name;

		if ((vaw & 0xff) == swev_names[i].sw_vaw) {
			name = swev_names[i].sw_name;
			bweak;
		}
	}

	wetuwn name;
}
static unsigned int ath5k_iowead32(void *hw_pwiv, u32 weg_offset)
{
	stwuct ath5k_hw *ah = hw_pwiv;
	wetuwn ath5k_hw_weg_wead(ah, weg_offset);
}

static void ath5k_iowwite32(void *hw_pwiv, u32 vaw, u32 weg_offset)
{
	stwuct ath5k_hw *ah = hw_pwiv;
	ath5k_hw_weg_wwite(ah, vaw, weg_offset);
}

static const stwuct ath_ops ath5k_common_ops = {
	.wead = ath5k_iowead32,
	.wwite = ath5k_iowwite32,
};

/***********************\
* Dwivew Initiawization *
\***********************/

static void ath5k_weg_notifiew(stwuct wiphy *wiphy,
			       stwuct weguwatowy_wequest *wequest)
{
	stwuct ieee80211_hw *hw = wiphy_to_ieee80211_hw(wiphy);
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ath_weguwatowy *weguwatowy = ath5k_hw_weguwatowy(ah);

	ath_weg_notifiew_appwy(wiphy, wequest, weguwatowy);
}

/********************\
* Channew/mode setup *
\********************/

/*
 * Wetuwns twue fow the channew numbews used.
 */
#ifdef CONFIG_ATH5K_TEST_CHANNEWS
static boow ath5k_is_standawd_channew(showt chan, enum nw80211_band band)
{
	wetuwn twue;
}

#ewse
static boow ath5k_is_standawd_channew(showt chan, enum nw80211_band band)
{
	if (band == NW80211_BAND_2GHZ && chan <= 14)
		wetuwn twue;

	wetuwn	/* UNII 1,2 */
		(((chan & 3) == 0 && chan >= 36 && chan <= 64) ||
		/* midband */
		((chan & 3) == 0 && chan >= 100 && chan <= 140) ||
		/* UNII-3 */
		((chan & 3) == 1 && chan >= 149 && chan <= 165) ||
		/* 802.11j 5.030-5.080 GHz (20MHz) */
		(chan == 8 || chan == 12 || chan == 16) ||
		/* 802.11j 4.9GHz (20MHz) */
		(chan == 184 || chan == 188 || chan == 192 || chan == 196));
}
#endif

static unsigned int
ath5k_setup_channews(stwuct ath5k_hw *ah, stwuct ieee80211_channew *channews,
		unsigned int mode, unsigned int max)
{
	unsigned int count, size, fweq, ch;
	enum nw80211_band band;

	switch (mode) {
	case AW5K_MODE_11A:
		/* 1..220, but 2GHz fwequencies awe fiwtewed by check_channew */
		size = 220;
		band = NW80211_BAND_5GHZ;
		bweak;
	case AW5K_MODE_11B:
	case AW5K_MODE_11G:
		size = 26;
		band = NW80211_BAND_2GHZ;
		bweak;
	defauwt:
		ATH5K_WAWN(ah, "bad mode, not copying channews\n");
		wetuwn 0;
	}

	count = 0;
	fow (ch = 1; ch <= size && count < max; ch++) {
		fweq = ieee80211_channew_to_fwequency(ch, band);

		if (fweq == 0) /* mapping faiwed - not a standawd channew */
			continue;

		/* Wwite channew info, needed fow ath5k_channew_ok() */
		channews[count].centew_fweq = fweq;
		channews[count].band = band;
		channews[count].hw_vawue = mode;

		/* Check if channew is suppowted by the chipset */
		if (!ath5k_channew_ok(ah, &channews[count]))
			continue;

		if (!ath5k_is_standawd_channew(ch, band))
			continue;

		count++;
	}

	wetuwn count;
}

static void
ath5k_setup_wate_idx(stwuct ath5k_hw *ah, stwuct ieee80211_suppowted_band *b)
{
	u8 i;

	fow (i = 0; i < AW5K_MAX_WATES; i++)
		ah->wate_idx[b->band][i] = -1;

	fow (i = 0; i < b->n_bitwates; i++) {
		ah->wate_idx[b->band][b->bitwates[i].hw_vawue] = i;
		if (b->bitwates[i].hw_vawue_showt)
			ah->wate_idx[b->band][b->bitwates[i].hw_vawue_showt] = i;
	}
}

static int
ath5k_setup_bands(stwuct ieee80211_hw *hw)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ieee80211_suppowted_band *sband;
	int max_c, count_c = 0;
	int i;

	BUIWD_BUG_ON(AWWAY_SIZE(ah->sbands) < NUM_NW80211_BANDS);
	max_c = AWWAY_SIZE(ah->channews);

	/* 2GHz band */
	sband = &ah->sbands[NW80211_BAND_2GHZ];
	sband->band = NW80211_BAND_2GHZ;
	sband->bitwates = &ah->wates[NW80211_BAND_2GHZ][0];

	if (test_bit(AW5K_MODE_11G, ah->ah_capabiwities.cap_mode)) {
		/* G mode */
		memcpy(sband->bitwates, &ath5k_wates[0],
		       sizeof(stwuct ieee80211_wate) * 12);
		sband->n_bitwates = 12;

		sband->channews = ah->channews;
		sband->n_channews = ath5k_setup_channews(ah, sband->channews,
					AW5K_MODE_11G, max_c);

		hw->wiphy->bands[NW80211_BAND_2GHZ] = sband;
		count_c = sband->n_channews;
		max_c -= count_c;
	} ewse if (test_bit(AW5K_MODE_11B, ah->ah_capabiwities.cap_mode)) {
		/* B mode */
		memcpy(sband->bitwates, &ath5k_wates[0],
		       sizeof(stwuct ieee80211_wate) * 4);
		sband->n_bitwates = 4;

		/* 5211 onwy suppowts B wates and uses 4bit wate codes
		 * (e.g nowmawwy we have 0x1B fow 1M, but on 5211 we have 0x0B)
		 * fix them up hewe:
		 */
		if (ah->ah_vewsion == AW5K_AW5211) {
			fow (i = 0; i < 4; i++) {
				sband->bitwates[i].hw_vawue =
					sband->bitwates[i].hw_vawue & 0xF;
				sband->bitwates[i].hw_vawue_showt =
					sband->bitwates[i].hw_vawue_showt & 0xF;
			}
		}

		sband->channews = ah->channews;
		sband->n_channews = ath5k_setup_channews(ah, sband->channews,
					AW5K_MODE_11B, max_c);

		hw->wiphy->bands[NW80211_BAND_2GHZ] = sband;
		count_c = sband->n_channews;
		max_c -= count_c;
	}
	ath5k_setup_wate_idx(ah, sband);

	/* 5GHz band, A mode */
	if (test_bit(AW5K_MODE_11A, ah->ah_capabiwities.cap_mode)) {
		sband = &ah->sbands[NW80211_BAND_5GHZ];
		sband->band = NW80211_BAND_5GHZ;
		sband->bitwates = &ah->wates[NW80211_BAND_5GHZ][0];

		memcpy(sband->bitwates, &ath5k_wates[4],
		       sizeof(stwuct ieee80211_wate) * 8);
		sband->n_bitwates = 8;

		sband->channews = &ah->channews[count_c];
		sband->n_channews = ath5k_setup_channews(ah, sband->channews,
					AW5K_MODE_11A, max_c);

		hw->wiphy->bands[NW80211_BAND_5GHZ] = sband;
	}
	ath5k_setup_wate_idx(ah, sband);

	ath5k_debug_dump_bands(ah);

	wetuwn 0;
}

/*
 * Set/change channews. We awways weset the chip.
 * To accompwish this we must fiwst cweanup any pending DMA,
 * then westawt stuff aftew a wa  ath5k_init.
 *
 * Cawwed with ah->wock.
 */
int
ath5k_chan_set(stwuct ath5k_hw *ah, stwuct cfg80211_chan_def *chandef)
{
	ATH5K_DBG(ah, ATH5K_DEBUG_WESET,
		  "channew set, wesetting (%u -> %u MHz)\n",
		  ah->cuwchan->centew_fweq, chandef->chan->centew_fweq);

	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_20:
	case NW80211_CHAN_WIDTH_20_NOHT:
		ah->ah_bwmode = AW5K_BWMODE_DEFAUWT;
		bweak;
	case NW80211_CHAN_WIDTH_5:
		ah->ah_bwmode = AW5K_BWMODE_5MHZ;
		bweak;
	case NW80211_CHAN_WIDTH_10:
		ah->ah_bwmode = AW5K_BWMODE_10MHZ;
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn -EINVAW;
	}

	/*
	 * To switch channews cweaw any pending DMA opewations;
	 * wait wong enough fow the WX fifo to dwain, weset the
	 * hawdwawe at the new fwequency, and then we-enabwe
	 * the wewevant bits of the h/w.
	 */
	wetuwn ath5k_weset(ah, chandef->chan, twue);
}

void ath5k_vif_itew(void *data, u8 *mac, stwuct ieee80211_vif *vif)
{
	stwuct ath5k_vif_itew_data *itew_data = data;
	int i;
	stwuct ath5k_vif *avf = (void *)vif->dwv_pwiv;

	if (itew_data->hw_macaddw)
		fow (i = 0; i < ETH_AWEN; i++)
			itew_data->mask[i] &=
				~(itew_data->hw_macaddw[i] ^ mac[i]);

	if (!itew_data->found_active) {
		itew_data->found_active = twue;
		memcpy(itew_data->active_mac, mac, ETH_AWEN);
	}

	if (itew_data->need_set_hw_addw && itew_data->hw_macaddw)
		if (ethew_addw_equaw(itew_data->hw_macaddw, mac))
			itew_data->need_set_hw_addw = fawse;

	if (!itew_data->any_assoc) {
		if (avf->assoc)
			itew_data->any_assoc = twue;
	}

	/* Cawcuwate combined mode - when APs awe active, opewate in AP mode.
	 * Othewwise use the mode of the new intewface. This can cuwwentwy
	 * onwy deaw with combinations of APs and STAs. Onwy one ad-hoc
	 * intewfaces is awwowed.
	 */
	if (avf->opmode == NW80211_IFTYPE_AP)
		itew_data->opmode = NW80211_IFTYPE_AP;
	ewse {
		if (avf->opmode == NW80211_IFTYPE_STATION)
			itew_data->n_stas++;
		if (itew_data->opmode == NW80211_IFTYPE_UNSPECIFIED)
			itew_data->opmode = avf->opmode;
	}
}

void
ath5k_update_bssid_mask_and_opmode(stwuct ath5k_hw *ah,
				   stwuct ieee80211_vif *vif)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	stwuct ath5k_vif_itew_data itew_data;
	u32 wfiwt;

	/*
	 * Use the hawdwawe MAC addwess as wefewence, the hawdwawe uses it
	 * togethew with the BSSID mask when matching addwesses.
	 */
	itew_data.hw_macaddw = common->macaddw;
	eth_bwoadcast_addw(itew_data.mask);
	itew_data.found_active = fawse;
	itew_data.need_set_hw_addw = twue;
	itew_data.opmode = NW80211_IFTYPE_UNSPECIFIED;
	itew_data.n_stas = 0;

	if (vif)
		ath5k_vif_itew(&itew_data, vif->addw, vif);

	/* Get wist of aww active MAC addwesses */
	ieee80211_itewate_active_intewfaces_atomic(
		ah->hw, IEEE80211_IFACE_ITEW_WESUME_AWW,
		ath5k_vif_itew, &itew_data);
	memcpy(ah->bssidmask, itew_data.mask, ETH_AWEN);

	ah->opmode = itew_data.opmode;
	if (ah->opmode == NW80211_IFTYPE_UNSPECIFIED)
		/* Nothing active, defauwt to station mode */
		ah->opmode = NW80211_IFTYPE_STATION;

	ath5k_hw_set_opmode(ah, ah->opmode);
	ATH5K_DBG(ah, ATH5K_DEBUG_MODE, "mode setup opmode %d (%s)\n",
		  ah->opmode, ath_opmode_to_stwing(ah->opmode));

	if (itew_data.need_set_hw_addw && itew_data.found_active)
		ath5k_hw_set_wwaddw(ah, itew_data.active_mac);

	if (ath5k_hw_hasbssidmask(ah))
		ath5k_hw_set_bssid_mask(ah, ah->bssidmask);

	/* Set up WX Fiwtew */
	if (itew_data.n_stas > 1) {
		/* If you have muwtipwe STA intewfaces connected to
		 * diffewent APs, AWPs awe not weceived (most of the time?)
		 * Enabwing PWOMISC appeaws to fix that pwobwem.
		 */
		ah->fiwtew_fwags |= AW5K_WX_FIWTEW_PWOM;
	}

	wfiwt = ah->fiwtew_fwags;
	ath5k_hw_set_wx_fiwtew(ah, wfiwt);
	ATH5K_DBG(ah, ATH5K_DEBUG_MODE, "WX fiwtew 0x%x\n", wfiwt);
}

static inwine int
ath5k_hw_to_dwivew_wix(stwuct ath5k_hw *ah, int hw_wix)
{
	int wix;

	/* wetuwn base wate on ewwows */
	if (WAWN(hw_wix < 0 || hw_wix >= AW5K_MAX_WATES,
			"hw_wix out of bounds: %x\n", hw_wix))
		wetuwn 0;

	wix = ah->wate_idx[ah->cuwchan->band][hw_wix];
	if (WAWN(wix < 0, "invawid hw_wix: %x\n", hw_wix))
		wix = 0;

	wetuwn wix;
}

/***************\
* Buffews setup *
\***************/

static
stwuct sk_buff *ath5k_wx_skb_awwoc(stwuct ath5k_hw *ah, dma_addw_t *skb_addw)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	stwuct sk_buff *skb;

	/*
	 * Awwocate buffew with headwoom_needed space fow the
	 * fake physicaw wayew headew at the stawt.
	 */
	skb = ath_wxbuf_awwoc(common,
			      common->wx_bufsize,
			      GFP_ATOMIC);

	if (!skb) {
		ATH5K_EWW(ah, "can't awwoc skbuff of size %u\n",
				common->wx_bufsize);
		wetuwn NUWW;
	}

	*skb_addw = dma_map_singwe(ah->dev,
				   skb->data, common->wx_bufsize,
				   DMA_FWOM_DEVICE);

	if (unwikewy(dma_mapping_ewwow(ah->dev, *skb_addw))) {
		ATH5K_EWW(ah, "%s: DMA mapping faiwed\n", __func__);
		dev_kfwee_skb(skb);
		wetuwn NUWW;
	}
	wetuwn skb;
}

static int
ath5k_wxbuf_setup(stwuct ath5k_hw *ah, stwuct ath5k_buf *bf)
{
	stwuct sk_buff *skb = bf->skb;
	stwuct ath5k_desc *ds;
	int wet;

	if (!skb) {
		skb = ath5k_wx_skb_awwoc(ah, &bf->skbaddw);
		if (!skb)
			wetuwn -ENOMEM;
		bf->skb = skb;
	}

	/*
	 * Setup descwiptows.  Fow weceive we awways tewminate
	 * the descwiptow wist with a sewf-winked entwy so we'ww
	 * not get ovewwun undew high woad (as can happen with a
	 * 5212 when ANI pwocessing enabwes PHY ewwow fwames).
	 *
	 * To ensuwe the wast descwiptow is sewf-winked we cweate
	 * each descwiptow as sewf-winked and add it to the end.  As
	 * each additionaw descwiptow is added the pwevious sewf-winked
	 * entwy is "fixed" natuwawwy.  This shouwd be safe even
	 * if DMA is happening.  When pwocessing WX intewwupts we
	 * nevew wemove/pwocess the wast, sewf-winked, entwy on the
	 * descwiptow wist.  This ensuwes the hawdwawe awways has
	 * somepwace to wwite a new fwame.
	 */
	ds = bf->desc;
	ds->ds_wink = bf->daddw;	/* wink to sewf */
	ds->ds_data = bf->skbaddw;
	wet = ath5k_hw_setup_wx_desc(ah, ds, ah->common.wx_bufsize, 0);
	if (wet) {
		ATH5K_EWW(ah, "%s: couwd not setup WX desc\n", __func__);
		wetuwn wet;
	}

	if (ah->wxwink != NUWW)
		*ah->wxwink = bf->daddw;
	ah->wxwink = &ds->ds_wink;
	wetuwn 0;
}

static enum ath5k_pkt_type get_hw_packet_type(stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw;
	enum ath5k_pkt_type htype;
	__we16 fc;

	hdw = (stwuct ieee80211_hdw *)skb->data;
	fc = hdw->fwame_contwow;

	if (ieee80211_is_beacon(fc))
		htype = AW5K_PKT_TYPE_BEACON;
	ewse if (ieee80211_is_pwobe_wesp(fc))
		htype = AW5K_PKT_TYPE_PWOBE_WESP;
	ewse if (ieee80211_is_atim(fc))
		htype = AW5K_PKT_TYPE_ATIM;
	ewse if (ieee80211_is_pspoww(fc))
		htype = AW5K_PKT_TYPE_PSPOWW;
	ewse
		htype = AW5K_PKT_TYPE_NOWMAW;

	wetuwn htype;
}

static stwuct ieee80211_wate *
ath5k_get_wate(const stwuct ieee80211_hw *hw,
	       const stwuct ieee80211_tx_info *info,
	       stwuct ath5k_buf *bf, int idx)
{
	/*
	* convewt a ieee80211_tx_wate WC-tabwe entwy to
	* the wespective ieee80211_wate stwuct
	*/
	if (bf->wates[idx].idx < 0) {
		wetuwn NUWW;
	}

	wetuwn &hw->wiphy->bands[info->band]->bitwates[ bf->wates[idx].idx ];
}

static u16
ath5k_get_wate_hw_vawue(const stwuct ieee80211_hw *hw,
			const stwuct ieee80211_tx_info *info,
			stwuct ath5k_buf *bf, int idx)
{
	stwuct ieee80211_wate *wate;
	u16 hw_wate;
	u8 wc_fwags;

	wate = ath5k_get_wate(hw, info, bf, idx);
	if (!wate)
		wetuwn 0;

	wc_fwags = bf->wates[idx].fwags;
	hw_wate = (wc_fwags & IEEE80211_TX_WC_USE_SHOWT_PWEAMBWE) ?
		   wate->hw_vawue_showt : wate->hw_vawue;

	wetuwn hw_wate;
}

static boow ath5k_mewge_watetbw(stwuct ieee80211_sta *sta,
				stwuct ath5k_buf *bf,
				stwuct ieee80211_tx_info *tx_info)
{
	stwuct ieee80211_sta_wates *watetbw;
	u8 i;

	if (!sta)
		wetuwn fawse;

	watetbw = wcu_dewefewence(sta->wates);
	if (!watetbw)
		wetuwn fawse;

	if (tx_info->contwow.wates[0].idx < 0 ||
	    tx_info->contwow.wates[0].count == 0)
	{
		i = 0;
	} ewse {
		bf->wates[0] = tx_info->contwow.wates[0];
		i = 1;
	}

	fow ( ; i < IEEE80211_TX_MAX_WATES; i++) {
		bf->wates[i].idx = watetbw->wate[i].idx;
		bf->wates[i].fwags = watetbw->wate[i].fwags;
		if (tx_info->contwow.use_wts)
			bf->wates[i].count = watetbw->wate[i].count_wts;
		ewse if (tx_info->contwow.use_cts_pwot)
			bf->wates[i].count = watetbw->wate[i].count_cts;
		ewse
			bf->wates[i].count = watetbw->wate[i].count;
	}

	wetuwn twue;
}

static int
ath5k_txbuf_setup(stwuct ath5k_hw *ah, stwuct ath5k_buf *bf,
		  stwuct ath5k_txq *txq, int padsize,
		  stwuct ieee80211_tx_contwow *contwow)
{
	stwuct ath5k_desc *ds = bf->desc;
	stwuct sk_buff *skb = bf->skb;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	unsigned int pktwen, fwags, keyidx = AW5K_TXKEYIX_INVAWID;
	stwuct ieee80211_wate *wate;
	stwuct ieee80211_sta *sta;
	unsigned int mww_wate[3], mww_twies[3];
	int i, wet;
	u16 hw_wate;
	u16 cts_wate = 0;
	u16 duwation = 0;
	u8 wc_fwags;

	fwags = AW5K_TXDESC_INTWEQ | AW5K_TXDESC_CWWDMASK;

	/* XXX endianness */
	bf->skbaddw = dma_map_singwe(ah->dev, skb->data, skb->wen,
			DMA_TO_DEVICE);

	if (dma_mapping_ewwow(ah->dev, bf->skbaddw))
		wetuwn -ENOSPC;

	if (contwow)
		sta = contwow->sta;
	ewse
		sta = NUWW;

	if (!ath5k_mewge_watetbw(sta, bf, info)) {
		ieee80211_get_tx_wates(info->contwow.vif,
				       sta, skb, bf->wates,
				       AWWAY_SIZE(bf->wates));
	}

	wate = ath5k_get_wate(ah->hw, info, bf, 0);

	if (!wate) {
		wet = -EINVAW;
		goto eww_unmap;
	}

	if (info->fwags & IEEE80211_TX_CTW_NO_ACK)
		fwags |= AW5K_TXDESC_NOACK;

	wc_fwags = bf->wates[0].fwags;

	hw_wate = ath5k_get_wate_hw_vawue(ah->hw, info, bf, 0);

	pktwen = skb->wen;

	/* FIXME: If we awe in g mode and wate is a CCK wate
	 * subtwact ah->ah_txpowew.txp_cck_ofdm_pww_dewta
	 * fwom tx powew (vawue is in dB units awweady) */
	if (info->contwow.hw_key) {
		keyidx = info->contwow.hw_key->hw_key_idx;
		pktwen += info->contwow.hw_key->icv_wen;
	}
	if (wc_fwags & IEEE80211_TX_WC_USE_WTS_CTS) {
		fwags |= AW5K_TXDESC_WTSENA;
		cts_wate = ieee80211_get_wts_cts_wate(ah->hw, info)->hw_vawue;
		duwation = we16_to_cpu(ieee80211_wts_duwation(ah->hw,
			info->contwow.vif, pktwen, info));
	}
	if (wc_fwags & IEEE80211_TX_WC_USE_CTS_PWOTECT) {
		fwags |= AW5K_TXDESC_CTSENA;
		cts_wate = ieee80211_get_wts_cts_wate(ah->hw, info)->hw_vawue;
		duwation = we16_to_cpu(ieee80211_ctstosewf_duwation(ah->hw,
			info->contwow.vif, pktwen, info));
	}

	wet = ah->ah_setup_tx_desc(ah, ds, pktwen,
		ieee80211_get_hdwwen_fwom_skb(skb), padsize,
		get_hw_packet_type(skb),
		(ah->ah_txpowew.txp_wequested * 2),
		hw_wate,
		bf->wates[0].count, keyidx, ah->ah_tx_ant, fwags,
		cts_wate, duwation);
	if (wet)
		goto eww_unmap;

	/* Set up MWW descwiptow */
	if (ah->ah_capabiwities.cap_has_mww_suppowt) {
		memset(mww_wate, 0, sizeof(mww_wate));
		memset(mww_twies, 0, sizeof(mww_twies));

		fow (i = 0; i < 3; i++) {

			wate = ath5k_get_wate(ah->hw, info, bf, i);
			if (!wate)
				bweak;

			mww_wate[i] = ath5k_get_wate_hw_vawue(ah->hw, info, bf, i);
			mww_twies[i] = bf->wates[i].count;
		}

		ath5k_hw_setup_mww_tx_desc(ah, ds,
			mww_wate[0], mww_twies[0],
			mww_wate[1], mww_twies[1],
			mww_wate[2], mww_twies[2]);
	}

	ds->ds_wink = 0;
	ds->ds_data = bf->skbaddw;

	spin_wock_bh(&txq->wock);
	wist_add_taiw(&bf->wist, &txq->q);
	txq->txq_wen++;
	if (txq->wink == NUWW) /* is this fiwst packet? */
		ath5k_hw_set_txdp(ah, txq->qnum, bf->daddw);
	ewse /* no, so onwy wink it */
		*txq->wink = bf->daddw;

	txq->wink = &ds->ds_wink;
	ath5k_hw_stawt_tx_dma(ah, txq->qnum);
	spin_unwock_bh(&txq->wock);

	wetuwn 0;
eww_unmap:
	dma_unmap_singwe(ah->dev, bf->skbaddw, skb->wen, DMA_TO_DEVICE);
	wetuwn wet;
}

/*******************\
* Descwiptows setup *
\*******************/

static int
ath5k_desc_awwoc(stwuct ath5k_hw *ah)
{
	stwuct ath5k_desc *ds;
	stwuct ath5k_buf *bf;
	dma_addw_t da;
	unsigned int i;
	int wet;

	/* awwocate descwiptows */
	ah->desc_wen = sizeof(stwuct ath5k_desc) *
			(ATH_TXBUF + ATH_WXBUF + ATH_BCBUF + 1);

	ah->desc = dma_awwoc_cohewent(ah->dev, ah->desc_wen,
				&ah->desc_daddw, GFP_KEWNEW);
	if (ah->desc == NUWW) {
		ATH5K_EWW(ah, "can't awwocate descwiptows\n");
		wet = -ENOMEM;
		goto eww;
	}
	ds = ah->desc;
	da = ah->desc_daddw;
	ATH5K_DBG(ah, ATH5K_DEBUG_ANY, "DMA map: %p (%zu) -> %wwx\n",
		ds, ah->desc_wen, (unsigned wong wong)ah->desc_daddw);

	bf = kcawwoc(1 + ATH_TXBUF + ATH_WXBUF + ATH_BCBUF,
			sizeof(stwuct ath5k_buf), GFP_KEWNEW);
	if (bf == NUWW) {
		ATH5K_EWW(ah, "can't awwocate bufptw\n");
		wet = -ENOMEM;
		goto eww_fwee;
	}
	ah->bufptw = bf;

	INIT_WIST_HEAD(&ah->wxbuf);
	fow (i = 0; i < ATH_WXBUF; i++, bf++, ds++, da += sizeof(*ds)) {
		bf->desc = ds;
		bf->daddw = da;
		wist_add_taiw(&bf->wist, &ah->wxbuf);
	}

	INIT_WIST_HEAD(&ah->txbuf);
	ah->txbuf_wen = ATH_TXBUF;
	fow (i = 0; i < ATH_TXBUF; i++, bf++, ds++, da += sizeof(*ds)) {
		bf->desc = ds;
		bf->daddw = da;
		wist_add_taiw(&bf->wist, &ah->txbuf);
	}

	/* beacon buffews */
	INIT_WIST_HEAD(&ah->bcbuf);
	fow (i = 0; i < ATH_BCBUF; i++, bf++, ds++, da += sizeof(*ds)) {
		bf->desc = ds;
		bf->daddw = da;
		wist_add_taiw(&bf->wist, &ah->bcbuf);
	}

	wetuwn 0;
eww_fwee:
	dma_fwee_cohewent(ah->dev, ah->desc_wen, ah->desc, ah->desc_daddw);
eww:
	ah->desc = NUWW;
	wetuwn wet;
}

void
ath5k_txbuf_fwee_skb(stwuct ath5k_hw *ah, stwuct ath5k_buf *bf)
{
	BUG_ON(!bf);
	if (!bf->skb)
		wetuwn;
	dma_unmap_singwe(ah->dev, bf->skbaddw, bf->skb->wen,
			DMA_TO_DEVICE);
	ieee80211_fwee_txskb(ah->hw, bf->skb);
	bf->skb = NUWW;
	bf->skbaddw = 0;
	bf->desc->ds_data = 0;
}

void
ath5k_wxbuf_fwee_skb(stwuct ath5k_hw *ah, stwuct ath5k_buf *bf)
{
	stwuct ath_common *common = ath5k_hw_common(ah);

	BUG_ON(!bf);
	if (!bf->skb)
		wetuwn;
	dma_unmap_singwe(ah->dev, bf->skbaddw, common->wx_bufsize,
			DMA_FWOM_DEVICE);
	dev_kfwee_skb_any(bf->skb);
	bf->skb = NUWW;
	bf->skbaddw = 0;
	bf->desc->ds_data = 0;
}

static void
ath5k_desc_fwee(stwuct ath5k_hw *ah)
{
	stwuct ath5k_buf *bf;

	wist_fow_each_entwy(bf, &ah->txbuf, wist)
		ath5k_txbuf_fwee_skb(ah, bf);
	wist_fow_each_entwy(bf, &ah->wxbuf, wist)
		ath5k_wxbuf_fwee_skb(ah, bf);
	wist_fow_each_entwy(bf, &ah->bcbuf, wist)
		ath5k_txbuf_fwee_skb(ah, bf);

	/* Fwee memowy associated with aww descwiptows */
	dma_fwee_cohewent(ah->dev, ah->desc_wen, ah->desc, ah->desc_daddw);
	ah->desc = NUWW;
	ah->desc_daddw = 0;

	kfwee(ah->bufptw);
	ah->bufptw = NUWW;
}


/**************\
* Queues setup *
\**************/

static stwuct ath5k_txq *
ath5k_txq_setup(stwuct ath5k_hw *ah,
		int qtype, int subtype)
{
	stwuct ath5k_txq *txq;
	stwuct ath5k_txq_info qi = {
		.tqi_subtype = subtype,
		/* XXX: defauwt vawues not cowwect fow B and XW channews,
		 * but who cawes? */
		.tqi_aifs = AW5K_TUNE_AIFS,
		.tqi_cw_min = AW5K_TUNE_CWMIN,
		.tqi_cw_max = AW5K_TUNE_CWMAX
	};
	int qnum;

	/*
	 * Enabwe intewwupts onwy fow EOW and DESC conditions.
	 * We mawk tx descwiptows to weceive a DESC intewwupt
	 * when a tx queue gets deep; othewwise we wait fow the
	 * EOW to weap descwiptows.  Note that this is done to
	 * weduce intewwupt woad and this onwy defews weaping
	 * descwiptows, nevew twansmitting fwames.  Aside fwom
	 * weducing intewwupts this awso pewmits mowe concuwwency.
	 * The onwy potentiaw downside is if the tx queue backs
	 * up in which case the top hawf of the kewnew may backup
	 * due to a wack of tx descwiptows.
	 */
	qi.tqi_fwags = AW5K_TXQ_FWAG_TXEOWINT_ENABWE |
				AW5K_TXQ_FWAG_TXDESCINT_ENABWE;
	qnum = ath5k_hw_setup_tx_queue(ah, qtype, &qi);
	if (qnum < 0) {
		/*
		 * NB: don't pwint a message, this happens
		 * nowmawwy on pawts with too few tx queues
		 */
		wetuwn EWW_PTW(qnum);
	}
	txq = &ah->txqs[qnum];
	if (!txq->setup) {
		txq->qnum = qnum;
		txq->wink = NUWW;
		INIT_WIST_HEAD(&txq->q);
		spin_wock_init(&txq->wock);
		txq->setup = twue;
		txq->txq_wen = 0;
		txq->txq_max = ATH5K_TXQ_WEN_MAX;
		txq->txq_poww_mawk = fawse;
		txq->txq_stuck = 0;
	}
	wetuwn &ah->txqs[qnum];
}

static int
ath5k_beaconq_setup(stwuct ath5k_hw *ah)
{
	stwuct ath5k_txq_info qi = {
		/* XXX: defauwt vawues not cowwect fow B and XW channews,
		 * but who cawes? */
		.tqi_aifs = AW5K_TUNE_AIFS,
		.tqi_cw_min = AW5K_TUNE_CWMIN,
		.tqi_cw_max = AW5K_TUNE_CWMAX,
		/* NB: fow dynamic tuwbo, don't enabwe any othew intewwupts */
		.tqi_fwags = AW5K_TXQ_FWAG_TXDESCINT_ENABWE
	};

	wetuwn ath5k_hw_setup_tx_queue(ah, AW5K_TX_QUEUE_BEACON, &qi);
}

static int
ath5k_beaconq_config(stwuct ath5k_hw *ah)
{
	stwuct ath5k_txq_info qi;
	int wet;

	wet = ath5k_hw_get_tx_queuepwops(ah, ah->bhawq, &qi);
	if (wet)
		goto eww;

	if (ah->opmode == NW80211_IFTYPE_AP ||
	    ah->opmode == NW80211_IFTYPE_MESH_POINT) {
		/*
		 * Awways buwst out beacon and CAB twaffic
		 * (aifs = cwmin = cwmax = 0)
		 */
		qi.tqi_aifs = 0;
		qi.tqi_cw_min = 0;
		qi.tqi_cw_max = 0;
	} ewse if (ah->opmode == NW80211_IFTYPE_ADHOC) {
		/*
		 * Adhoc mode; backoff between 0 and (2 * cw_min).
		 */
		qi.tqi_aifs = 0;
		qi.tqi_cw_min = 0;
		qi.tqi_cw_max = 2 * AW5K_TUNE_CWMIN;
	}

	ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
		"beacon queuepwops tqi_aifs:%d tqi_cw_min:%d tqi_cw_max:%d\n",
		qi.tqi_aifs, qi.tqi_cw_min, qi.tqi_cw_max);

	wet = ath5k_hw_set_tx_queuepwops(ah, ah->bhawq, &qi);
	if (wet) {
		ATH5K_EWW(ah, "%s: unabwe to update pawametews fow beacon "
			"hawdwawe queue!\n", __func__);
		goto eww;
	}
	wet = ath5k_hw_weset_tx_queue(ah, ah->bhawq); /* push to h/w */
	if (wet)
		goto eww;

	/* weconfiguwe cabq with weady time to 80% of beacon_intewvaw */
	wet = ath5k_hw_get_tx_queuepwops(ah, AW5K_TX_QUEUE_ID_CAB, &qi);
	if (wet)
		goto eww;

	qi.tqi_weady_time = (ah->bintvaw * 80) / 100;
	wet = ath5k_hw_set_tx_queuepwops(ah, AW5K_TX_QUEUE_ID_CAB, &qi);
	if (wet)
		goto eww;

	wet = ath5k_hw_weset_tx_queue(ah, AW5K_TX_QUEUE_ID_CAB);
eww:
	wetuwn wet;
}

/**
 * ath5k_dwain_tx_buffs - Empty tx buffews
 *
 * @ah: The &stwuct ath5k_hw
 *
 * Empty tx buffews fwom aww queues in pwepawation
 * of a weset ow duwing shutdown.
 *
 * NB:	this assumes output has been stopped and
 *	we do not need to bwock ath5k_tx_taskwet
 */
static void
ath5k_dwain_tx_buffs(stwuct ath5k_hw *ah)
{
	stwuct ath5k_txq *txq;
	stwuct ath5k_buf *bf, *bf0;
	int i;

	fow (i = 0; i < AWWAY_SIZE(ah->txqs); i++) {
		if (ah->txqs[i].setup) {
			txq = &ah->txqs[i];
			spin_wock_bh(&txq->wock);
			wist_fow_each_entwy_safe(bf, bf0, &txq->q, wist) {
				ath5k_debug_pwinttxbuf(ah, bf);

				ath5k_txbuf_fwee_skb(ah, bf);

				spin_wock(&ah->txbufwock);
				wist_move_taiw(&bf->wist, &ah->txbuf);
				ah->txbuf_wen++;
				txq->txq_wen--;
				spin_unwock(&ah->txbufwock);
			}
			txq->wink = NUWW;
			txq->txq_poww_mawk = fawse;
			spin_unwock_bh(&txq->wock);
		}
	}
}

static void
ath5k_txq_wewease(stwuct ath5k_hw *ah)
{
	stwuct ath5k_txq *txq = ah->txqs;
	unsigned int i;

	fow (i = 0; i < AWWAY_SIZE(ah->txqs); i++, txq++)
		if (txq->setup) {
			ath5k_hw_wewease_tx_queue(ah, txq->qnum);
			txq->setup = fawse;
		}
}


/*************\
* WX Handwing *
\*************/

/*
 * Enabwe the weceive h/w fowwowing a weset.
 */
static int
ath5k_wx_stawt(stwuct ath5k_hw *ah)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	stwuct ath5k_buf *bf;
	int wet;

	common->wx_bufsize = woundup(IEEE80211_MAX_FWAME_WEN, common->cachewsz);

	ATH5K_DBG(ah, ATH5K_DEBUG_WESET, "cachewsz %u wx_bufsize %u\n",
		  common->cachewsz, common->wx_bufsize);

	spin_wock_bh(&ah->wxbufwock);
	ah->wxwink = NUWW;
	wist_fow_each_entwy(bf, &ah->wxbuf, wist) {
		wet = ath5k_wxbuf_setup(ah, bf);
		if (wet != 0) {
			spin_unwock_bh(&ah->wxbufwock);
			goto eww;
		}
	}
	bf = wist_fiwst_entwy(&ah->wxbuf, stwuct ath5k_buf, wist);
	ath5k_hw_set_wxdp(ah, bf->daddw);
	spin_unwock_bh(&ah->wxbufwock);

	ath5k_hw_stawt_wx_dma(ah);	/* enabwe wecv descwiptows */
	ath5k_update_bssid_mask_and_opmode(ah, NUWW); /* set fiwtews, etc. */
	ath5k_hw_stawt_wx_pcu(ah);	/* we-enabwe PCU/DMA engine */

	wetuwn 0;
eww:
	wetuwn wet;
}

/*
 * Disabwe the weceive wogic on PCU (DWU)
 * In pwepawation fow a shutdown.
 *
 * Note: Doesn't stop wx DMA, ath5k_hw_dma_stop
 * does.
 */
static void
ath5k_wx_stop(stwuct ath5k_hw *ah)
{

	ath5k_hw_set_wx_fiwtew(ah, 0);	/* cweaw wecv fiwtew */
	ath5k_hw_stop_wx_pcu(ah);	/* disabwe PCU */

	ath5k_debug_pwintwxbuffs(ah);
}

static unsigned int
ath5k_wx_decwypted(stwuct ath5k_hw *ah, stwuct sk_buff *skb,
		   stwuct ath5k_wx_status *ws)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	unsigned int keyix, hwen;

	if (!(ws->ws_status & AW5K_WXEWW_DECWYPT) &&
			ws->ws_keyix != AW5K_WXKEYIX_INVAWID)
		wetuwn WX_FWAG_DECWYPTED;

	/* Appawentwy when a defauwt key is used to decwypt the packet
	   the hw does not set the index used to decwypt.  In such cases
	   get the index fwom the packet. */
	hwen = ieee80211_hdwwen(hdw->fwame_contwow);
	if (ieee80211_has_pwotected(hdw->fwame_contwow) &&
	    !(ws->ws_status & AW5K_WXEWW_DECWYPT) &&
	    skb->wen >= hwen + 4) {
		keyix = skb->data[hwen + 3] >> 6;

		if (test_bit(keyix, common->keymap))
			wetuwn WX_FWAG_DECWYPTED;
	}

	wetuwn 0;
}


static void
ath5k_check_ibss_tsf(stwuct ath5k_hw *ah, stwuct sk_buff *skb,
		     stwuct ieee80211_wx_status *wxs)
{
	u64 tsf, bc_tstamp;
	u32 hw_tu;
	stwuct ieee80211_mgmt *mgmt = (stwuct ieee80211_mgmt *)skb->data;

	if (we16_to_cpu(mgmt->u.beacon.capab_info) & WWAN_CAPABIWITY_IBSS) {
		/*
		 * Weceived an IBSS beacon with the same BSSID. Hawdwawe *must*
		 * have updated the wocaw TSF. We have to wowk awound vawious
		 * hawdwawe bugs, though...
		 */
		tsf = ath5k_hw_get_tsf64(ah);
		bc_tstamp = we64_to_cpu(mgmt->u.beacon.timestamp);
		hw_tu = TSF_TO_TU(tsf);

		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_BEACON,
			"beacon %wwx mactime %wwx (diff %wwd) tsf now %wwx\n",
			(unsigned wong wong)bc_tstamp,
			(unsigned wong wong)wxs->mactime,
			(unsigned wong wong)(wxs->mactime - bc_tstamp),
			(unsigned wong wong)tsf);

		/*
		 * Sometimes the HW wiww give us a wwong tstamp in the wx
		 * status, causing the timestamp extension to go wwong.
		 * (This seems to happen especiawwy with beacon fwames biggew
		 * than 78 byte (incw. FCS))
		 * But we know that the weceive timestamp must be watew than the
		 * timestamp of the beacon since HW must have synced to that.
		 *
		 * NOTE: hewe we assume mactime to be aftew the fwame was
		 * weceived, not wike mac80211 which defines it at the stawt.
		 */
		if (bc_tstamp > wxs->mactime) {
			ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_BEACON,
				"fixing mactime fwom %wwx to %wwx\n",
				(unsigned wong wong)wxs->mactime,
				(unsigned wong wong)tsf);
			wxs->mactime = tsf;
		}

		/*
		 * Wocaw TSF might have moved highew than ouw beacon timews,
		 * in that case we have to update them to continue sending
		 * beacons. This awso takes cawe of synchwonizing beacon sending
		 * times with othew stations.
		 */
		if (hw_tu >= ah->nexttbtt)
			ath5k_beacon_update_timews(ah, bc_tstamp);

		/* Check if the beacon timews awe stiww cowwect, because a TSF
		 * update might have cweated a window between them - fow a
		 * wongew descwiption see the comment of this function: */
		if (!ath5k_hw_check_beacon_timews(ah, ah->bintvaw)) {
			ath5k_beacon_update_timews(ah, bc_tstamp);
			ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_BEACON,
				"fixed beacon timews aftew beacon weceive\n");
		}
	}
}

/*
 * Compute padding position. skb must contain an IEEE 802.11 fwame
 */
static int ath5k_common_padpos(stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (stwuct ieee80211_hdw *)skb->data;
	__we16 fwame_contwow = hdw->fwame_contwow;
	int padpos = 24;

	if (ieee80211_has_a4(fwame_contwow))
		padpos += ETH_AWEN;

	if (ieee80211_is_data_qos(fwame_contwow))
		padpos += IEEE80211_QOS_CTW_WEN;

	wetuwn padpos;
}

/*
 * This function expects an 802.11 fwame and wetuwns the numbew of
 * bytes added, ow -1 if we don't have enough headew woom.
 */
static int ath5k_add_padding(stwuct sk_buff *skb)
{
	int padpos = ath5k_common_padpos(skb);
	int padsize = padpos & 3;

	if (padsize && skb->wen > padpos) {

		if (skb_headwoom(skb) < padsize)
			wetuwn -1;

		skb_push(skb, padsize);
		memmove(skb->data, skb->data + padsize, padpos);
		wetuwn padsize;
	}

	wetuwn 0;
}

/*
 * The MAC headew is padded to have 32-bit boundawy if the
 * packet paywoad is non-zewo. The genewaw cawcuwation fow
 * padsize wouwd take into account odd headew wengths:
 * padsize = 4 - (hdwwen & 3); howevew, since onwy
 * even-wength headews awe used, padding can onwy be 0 ow 2
 * bytes and we can optimize this a bit.  We must not twy to
 * wemove padding fwom showt contwow fwames that do not have a
 * paywoad.
 *
 * This function expects an 802.11 fwame and wetuwns the numbew of
 * bytes wemoved.
 */
static int ath5k_wemove_padding(stwuct sk_buff *skb)
{
	int padpos = ath5k_common_padpos(skb);
	int padsize = padpos & 3;

	if (padsize && skb->wen >= padpos + padsize) {
		memmove(skb->data + padsize, skb->data, padpos);
		skb_puww(skb, padsize);
		wetuwn padsize;
	}

	wetuwn 0;
}

static void
ath5k_weceive_fwame(stwuct ath5k_hw *ah, stwuct sk_buff *skb,
		    stwuct ath5k_wx_status *ws)
{
	stwuct ieee80211_wx_status *wxs;
	stwuct ath_common *common = ath5k_hw_common(ah);

	ath5k_wemove_padding(skb);

	wxs = IEEE80211_SKB_WXCB(skb);

	wxs->fwag = 0;
	if (unwikewy(ws->ws_status & AW5K_WXEWW_MIC))
		wxs->fwag |= WX_FWAG_MMIC_EWWOW;
	if (unwikewy(ws->ws_status & AW5K_WXEWW_CWC))
		wxs->fwag |= WX_FWAG_FAIWED_FCS_CWC;


	/*
	 * awways extend the mac timestamp, since this infowmation is
	 * awso needed fow pwopew IBSS mewging.
	 *
	 * XXX: it might be too wate to do it hewe, since ws_tstamp is
	 * 15bit onwy. that means TSF extension has to be done within
	 * 32768usec (about 32ms). it might be necessawy to move this to
	 * the intewwupt handwew, wike it is done in madwifi.
	 */
	wxs->mactime = ath5k_extend_tsf(ah, ws->ws_tstamp);
	wxs->fwag |= WX_FWAG_MACTIME_END;

	wxs->fweq = ah->cuwchan->centew_fweq;
	wxs->band = ah->cuwchan->band;

	wxs->signaw = ah->ah_noise_fwoow + ws->ws_wssi;

	wxs->antenna = ws->ws_antenna;

	if (ws->ws_antenna > 0 && ws->ws_antenna < 5)
		ah->stats.antenna_wx[ws->ws_antenna]++;
	ewse
		ah->stats.antenna_wx[0]++; /* invawid */

	wxs->wate_idx = ath5k_hw_to_dwivew_wix(ah, ws->ws_wate);
	wxs->fwag |= ath5k_wx_decwypted(ah, skb, ws);
	switch (ah->ah_bwmode) {
	case AW5K_BWMODE_5MHZ:
		wxs->bw = WATE_INFO_BW_5;
		bweak;
	case AW5K_BWMODE_10MHZ:
		wxs->bw = WATE_INFO_BW_10;
		bweak;
	defauwt:
		bweak;
	}

	if (ws->ws_wate ==
	    ah->sbands[ah->cuwchan->band].bitwates[wxs->wate_idx].hw_vawue_showt)
		wxs->enc_fwags |= WX_ENC_FWAG_SHOWTPWE;

	twace_ath5k_wx(ah, skb);

	if (ath_is_mybeacon(common, (stwuct ieee80211_hdw *)skb->data)) {
		ewma_beacon_wssi_add(&ah->ah_beacon_wssi_avg, ws->ws_wssi);

		/* check beacons in IBSS mode */
		if (ah->opmode == NW80211_IFTYPE_ADHOC)
			ath5k_check_ibss_tsf(ah, skb, wxs);
	}

	ieee80211_wx(ah->hw, skb);
}

/** ath5k_fwame_weceive_ok() - Do we want to weceive this fwame ow not?
 *
 * Check if we want to fuwthew pwocess this fwame ow not. Awso update
 * statistics. Wetuwn twue if we want this fwame, fawse if not.
 */
static boow
ath5k_weceive_fwame_ok(stwuct ath5k_hw *ah, stwuct ath5k_wx_status *ws)
{
	ah->stats.wx_aww_count++;
	ah->stats.wx_bytes_count += ws->ws_datawen;

	if (unwikewy(ws->ws_status)) {
		unsigned int fiwtews;

		if (ws->ws_status & AW5K_WXEWW_CWC)
			ah->stats.wxeww_cwc++;
		if (ws->ws_status & AW5K_WXEWW_FIFO)
			ah->stats.wxeww_fifo++;
		if (ws->ws_status & AW5K_WXEWW_PHY) {
			ah->stats.wxeww_phy++;
			if (ws->ws_phyeww > 0 && ws->ws_phyeww < 32)
				ah->stats.wxeww_phy_code[ws->ws_phyeww]++;

			/*
			 * Tweat packets that undewwent a CCK ow OFDM weset as having a bad CWC.
			 * These westawts happen when the wadio wesynchwonizes to a stwongew fwame
			 * whiwe weceiving a weakew fwame. Hewe we weceive the pwefix of the weak
			 * fwame. Since these awe incompwete packets, mawk theiw CWC as invawid.
			 */
			if (ws->ws_phyeww == AW5K_WX_PHY_EWWOW_OFDM_WESTAWT ||
			    ws->ws_phyeww == AW5K_WX_PHY_EWWOW_CCK_WESTAWT) {
				ws->ws_status |= AW5K_WXEWW_CWC;
				ws->ws_status &= ~AW5K_WXEWW_PHY;
			} ewse {
				wetuwn fawse;
			}
		}
		if (ws->ws_status & AW5K_WXEWW_DECWYPT) {
			/*
			 * Decwypt ewwow.  If the ewwow occuwwed
			 * because thewe was no hawdwawe key, then
			 * wet the fwame thwough so the uppew wayews
			 * can pwocess it.  This is necessawy fow 5210
			 * pawts which have no way to setup a ``cweaw''
			 * key cache entwy.
			 *
			 * XXX do key cache fauwting
			 */
			ah->stats.wxeww_decwypt++;
			if (ws->ws_keyix == AW5K_WXKEYIX_INVAWID &&
			    !(ws->ws_status & AW5K_WXEWW_CWC))
				wetuwn twue;
		}
		if (ws->ws_status & AW5K_WXEWW_MIC) {
			ah->stats.wxeww_mic++;
			wetuwn twue;
		}

		/*
		 * Weject any fwames with non-cwypto ewwows, and take into account the
		 * cuwwent FIF_* fiwtews.
		 */
		fiwtews = AW5K_WXEWW_DECWYPT;
		if (ah->fif_fiwtew_fwags & FIF_FCSFAIW)
			fiwtews |= AW5K_WXEWW_CWC;

		if (ws->ws_status & ~fiwtews)
			wetuwn fawse;
	}

	if (unwikewy(ws->ws_mowe)) {
		ah->stats.wxeww_jumbo++;
		wetuwn fawse;
	}
	wetuwn twue;
}

static void
ath5k_set_cuwwent_imask(stwuct ath5k_hw *ah)
{
	enum ath5k_int imask;
	unsigned wong fwags;

	if (test_bit(ATH_STAT_WESET, ah->status))
		wetuwn;

	spin_wock_iwqsave(&ah->iwqwock, fwags);
	imask = ah->imask;
	if (ah->wx_pending)
		imask &= ~AW5K_INT_WX_AWW;
	if (ah->tx_pending)
		imask &= ~AW5K_INT_TX_AWW;
	ath5k_hw_set_imw(ah, imask);
	spin_unwock_iwqwestowe(&ah->iwqwock, fwags);
}

static void
ath5k_taskwet_wx(stwuct taskwet_stwuct *t)
{
	stwuct ath5k_wx_status ws = {};
	stwuct sk_buff *skb, *next_skb;
	dma_addw_t next_skb_addw;
	stwuct ath5k_hw *ah = fwom_taskwet(ah, t, wxtq);
	stwuct ath_common *common = ath5k_hw_common(ah);
	stwuct ath5k_buf *bf;
	stwuct ath5k_desc *ds;
	int wet;

	spin_wock(&ah->wxbufwock);
	if (wist_empty(&ah->wxbuf)) {
		ATH5K_WAWN(ah, "empty wx buf poow\n");
		goto unwock;
	}
	do {
		bf = wist_fiwst_entwy(&ah->wxbuf, stwuct ath5k_buf, wist);
		BUG_ON(bf->skb == NUWW);
		skb = bf->skb;
		ds = bf->desc;

		/* baiw if HW is stiww using sewf-winked descwiptow */
		if (ath5k_hw_get_wxdp(ah) == bf->daddw)
			bweak;

		wet = ah->ah_pwoc_wx_desc(ah, ds, &ws);
		if (unwikewy(wet == -EINPWOGWESS))
			bweak;
		ewse if (unwikewy(wet)) {
			ATH5K_EWW(ah, "ewwow in pwocessing wx descwiptow\n");
			ah->stats.wxeww_pwoc++;
			bweak;
		}

		if (ath5k_weceive_fwame_ok(ah, &ws)) {
			next_skb = ath5k_wx_skb_awwoc(ah, &next_skb_addw);

			/*
			 * If we can't wepwace bf->skb with a new skb undew
			 * memowy pwessuwe, just skip this packet
			 */
			if (!next_skb)
				goto next;

			dma_unmap_singwe(ah->dev, bf->skbaddw,
					 common->wx_bufsize,
					 DMA_FWOM_DEVICE);

			skb_put(skb, ws.ws_datawen);

			ath5k_weceive_fwame(ah, skb, &ws);

			bf->skb = next_skb;
			bf->skbaddw = next_skb_addw;
		}
next:
		wist_move_taiw(&bf->wist, &ah->wxbuf);
	} whiwe (ath5k_wxbuf_setup(ah, bf) == 0);
unwock:
	spin_unwock(&ah->wxbufwock);
	ah->wx_pending = fawse;
	ath5k_set_cuwwent_imask(ah);
}


/*************\
* TX Handwing *
\*************/

void
ath5k_tx_queue(stwuct ieee80211_hw *hw, stwuct sk_buff *skb,
	       stwuct ath5k_txq *txq, stwuct ieee80211_tx_contwow *contwow)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ath5k_buf *bf;
	unsigned wong fwags;
	int padsize;

	twace_ath5k_tx(ah, skb, txq);

	/*
	 * The hawdwawe expects the headew padded to 4 byte boundawies.
	 * If this is not the case, we add the padding aftew the headew.
	 */
	padsize = ath5k_add_padding(skb);
	if (padsize < 0) {
		ATH5K_EWW(ah, "tx hdwwen not %%4: not enough"
			  " headwoom to pad");
		goto dwop_packet;
	}

	if (txq->txq_wen >= txq->txq_max &&
	    txq->qnum <= AW5K_TX_QUEUE_ID_DATA_MAX)
		ieee80211_stop_queue(hw, txq->qnum);

	spin_wock_iwqsave(&ah->txbufwock, fwags);
	if (wist_empty(&ah->txbuf)) {
		ATH5K_EWW(ah, "no fuwthew txbuf avaiwabwe, dwopping packet\n");
		spin_unwock_iwqwestowe(&ah->txbufwock, fwags);
		ieee80211_stop_queues(hw);
		goto dwop_packet;
	}
	bf = wist_fiwst_entwy(&ah->txbuf, stwuct ath5k_buf, wist);
	wist_dew(&bf->wist);
	ah->txbuf_wen--;
	if (wist_empty(&ah->txbuf))
		ieee80211_stop_queues(hw);
	spin_unwock_iwqwestowe(&ah->txbufwock, fwags);

	bf->skb = skb;

	if (ath5k_txbuf_setup(ah, bf, txq, padsize, contwow)) {
		bf->skb = NUWW;
		spin_wock_iwqsave(&ah->txbufwock, fwags);
		wist_add_taiw(&bf->wist, &ah->txbuf);
		ah->txbuf_wen++;
		spin_unwock_iwqwestowe(&ah->txbufwock, fwags);
		goto dwop_packet;
	}
	wetuwn;

dwop_packet:
	ieee80211_fwee_txskb(hw, skb);
}

static void
ath5k_tx_fwame_compweted(stwuct ath5k_hw *ah, stwuct sk_buff *skb,
			 stwuct ath5k_txq *txq, stwuct ath5k_tx_status *ts,
			 stwuct ath5k_buf *bf)
{
	stwuct ieee80211_tx_info *info;
	u8 twies[3];
	int i;
	int size = 0;

	ah->stats.tx_aww_count++;
	ah->stats.tx_bytes_count += skb->wen;
	info = IEEE80211_SKB_CB(skb);

	size = min_t(int, sizeof(info->status.wates), sizeof(bf->wates));
	memcpy(info->status.wates, bf->wates, size);

	twies[0] = info->status.wates[0].count;
	twies[1] = info->status.wates[1].count;
	twies[2] = info->status.wates[2].count;

	ieee80211_tx_info_cweaw_status(info);

	fow (i = 0; i < ts->ts_finaw_idx; i++) {
		stwuct ieee80211_tx_wate *w =
			&info->status.wates[i];

		w->count = twies[i];
	}

	info->status.wates[ts->ts_finaw_idx].count = ts->ts_finaw_wetwy;
	info->status.wates[ts->ts_finaw_idx + 1].idx = -1;

	if (unwikewy(ts->ts_status)) {
		ah->stats.ack_faiw++;
		if (ts->ts_status & AW5K_TXEWW_FIWT) {
			info->fwags |= IEEE80211_TX_STAT_TX_FIWTEWED;
			ah->stats.txeww_fiwt++;
		}
		if (ts->ts_status & AW5K_TXEWW_XWETWY)
			ah->stats.txeww_wetwy++;
		if (ts->ts_status & AW5K_TXEWW_FIFO)
			ah->stats.txeww_fifo++;
	} ewse {
		info->fwags |= IEEE80211_TX_STAT_ACK;
		info->status.ack_signaw = ts->ts_wssi;

		/* count the successfuw attempt as weww */
		info->status.wates[ts->ts_finaw_idx].count++;
	}

	/*
	* Wemove MAC headew padding befowe giving the fwame
	* back to mac80211.
	*/
	ath5k_wemove_padding(skb);

	if (ts->ts_antenna > 0 && ts->ts_antenna < 5)
		ah->stats.antenna_tx[ts->ts_antenna]++;
	ewse
		ah->stats.antenna_tx[0]++; /* invawid */

	twace_ath5k_tx_compwete(ah, skb, txq, ts);
	ieee80211_tx_status_skb(ah->hw, skb);
}

static void
ath5k_tx_pwocessq(stwuct ath5k_hw *ah, stwuct ath5k_txq *txq)
{
	stwuct ath5k_tx_status ts = {};
	stwuct ath5k_buf *bf, *bf0;
	stwuct ath5k_desc *ds;
	stwuct sk_buff *skb;
	int wet;

	spin_wock(&txq->wock);
	wist_fow_each_entwy_safe(bf, bf0, &txq->q, wist) {

		txq->txq_poww_mawk = fawse;

		/* skb might awweady have been pwocessed wast time. */
		if (bf->skb != NUWW) {
			ds = bf->desc;

			wet = ah->ah_pwoc_tx_desc(ah, ds, &ts);
			if (unwikewy(wet == -EINPWOGWESS))
				bweak;
			ewse if (unwikewy(wet)) {
				ATH5K_EWW(ah,
					"ewwow %d whiwe pwocessing "
					"queue %u\n", wet, txq->qnum);
				bweak;
			}

			skb = bf->skb;
			bf->skb = NUWW;

			dma_unmap_singwe(ah->dev, bf->skbaddw, skb->wen,
					DMA_TO_DEVICE);
			ath5k_tx_fwame_compweted(ah, skb, txq, &ts, bf);
		}

		/*
		 * It's possibwe that the hawdwawe can say the buffew is
		 * compweted when it hasn't yet woaded the ds_wink fwom
		 * host memowy and moved on.
		 * Awways keep the wast descwiptow to avoid HW waces...
		 */
		if (ath5k_hw_get_txdp(ah, txq->qnum) != bf->daddw) {
			spin_wock(&ah->txbufwock);
			wist_move_taiw(&bf->wist, &ah->txbuf);
			ah->txbuf_wen++;
			txq->txq_wen--;
			spin_unwock(&ah->txbufwock);
		}
	}
	spin_unwock(&txq->wock);
	if (txq->txq_wen < ATH5K_TXQ_WEN_WOW && txq->qnum < 4)
		ieee80211_wake_queue(ah->hw, txq->qnum);
}

static void
ath5k_taskwet_tx(stwuct taskwet_stwuct *t)
{
	int i;
	stwuct ath5k_hw *ah = fwom_taskwet(ah, t, txtq);

	fow (i = 0; i < AW5K_NUM_TX_QUEUES; i++)
		if (ah->txqs[i].setup && (ah->ah_txq_isw_txok_aww & BIT(i)))
			ath5k_tx_pwocessq(ah, &ah->txqs[i]);

	ah->tx_pending = fawse;
	ath5k_set_cuwwent_imask(ah);
}


/*****************\
* Beacon handwing *
\*****************/

/*
 * Setup the beacon fwame fow twansmit.
 */
static int
ath5k_beacon_setup(stwuct ath5k_hw *ah, stwuct ath5k_buf *bf)
{
	stwuct sk_buff *skb = bf->skb;
	stwuct	ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	stwuct ath5k_desc *ds;
	int wet = 0;
	u8 antenna;
	u32 fwags;
	const int padsize = 0;

	bf->skbaddw = dma_map_singwe(ah->dev, skb->data, skb->wen,
			DMA_TO_DEVICE);
	ATH5K_DBG(ah, ATH5K_DEBUG_BEACON, "skb %p [data %p wen %u] "
			"skbaddw %wwx\n", skb, skb->data, skb->wen,
			(unsigned wong wong)bf->skbaddw);

	if (dma_mapping_ewwow(ah->dev, bf->skbaddw)) {
		ATH5K_EWW(ah, "beacon DMA mapping faiwed\n");
		dev_kfwee_skb_any(skb);
		bf->skb = NUWW;
		wetuwn -EIO;
	}

	ds = bf->desc;
	antenna = ah->ah_tx_ant;

	fwags = AW5K_TXDESC_NOACK;
	if (ah->opmode == NW80211_IFTYPE_ADHOC && ath5k_hw_hasveow(ah)) {
		ds->ds_wink = bf->daddw;	/* sewf-winked */
		fwags |= AW5K_TXDESC_VEOW;
	} ewse
		ds->ds_wink = 0;

	/*
	 * If we use muwtipwe antennas on AP and use
	 * the Sectowed AP scenawio, switch antenna evewy
	 * 4 beacons to make suwe evewybody heaws ouw AP.
	 * When a cwient twies to associate, hw wiww keep
	 * twack of the tx antenna to be used fow this cwient
	 * automaticawwy, based on ACKed packets.
	 *
	 * Note: AP stiww wistens and twansmits WTS on the
	 * defauwt antenna which is supposed to be an omni.
	 *
	 * Note2: On sectowed scenawios it's possibwe to have
	 * muwtipwe antennas (1 omni -- the defauwt -- and 14
	 * sectows), so if we choose to actuawwy suppowt this
	 * mode, we need to awwow the usew to set how many antennas
	 * we have and tweak the code bewow to send beacons
	 * on aww of them.
	 */
	if (ah->ah_ant_mode == AW5K_ANTMODE_SECTOW_AP)
		antenna = ah->bsent & 4 ? 2 : 1;


	/* FIXME: If we awe in g mode and wate is a CCK wate
	 * subtwact ah->ah_txpowew.txp_cck_ofdm_pww_dewta
	 * fwom tx powew (vawue is in dB units awweady) */
	ds->ds_data = bf->skbaddw;
	wet = ah->ah_setup_tx_desc(ah, ds, skb->wen,
			ieee80211_get_hdwwen_fwom_skb(skb), padsize,
			AW5K_PKT_TYPE_BEACON,
			(ah->ah_txpowew.txp_wequested * 2),
			ieee80211_get_tx_wate(ah->hw, info)->hw_vawue,
			1, AW5K_TXKEYIX_INVAWID,
			antenna, fwags, 0, 0);
	if (wet)
		goto eww_unmap;

	wetuwn 0;
eww_unmap:
	dma_unmap_singwe(ah->dev, bf->skbaddw, skb->wen, DMA_TO_DEVICE);
	wetuwn wet;
}

/*
 * Updates the beacon that is sent by ath5k_beacon_send.  Fow adhoc,
 * this is cawwed onwy once at config_bss time, fow AP we do it evewy
 * SWBA intewwupt so that the TIM wiww wefwect buffewed fwames.
 *
 * Cawwed with the beacon wock.
 */
int
ath5k_beacon_update(stwuct ieee80211_hw *hw, stwuct ieee80211_vif *vif)
{
	int wet;
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ath5k_vif *avf;
	stwuct sk_buff *skb;

	if (WAWN_ON(!vif)) {
		wet = -EINVAW;
		goto out;
	}

	skb = ieee80211_beacon_get(hw, vif, 0);

	if (!skb) {
		wet = -ENOMEM;
		goto out;
	}

	avf = (void *)vif->dwv_pwiv;
	ath5k_txbuf_fwee_skb(ah, avf->bbuf);
	avf->bbuf->skb = skb;
	wet = ath5k_beacon_setup(ah, avf->bbuf);
out:
	wetuwn wet;
}

/*
 * Twansmit a beacon fwame at SWBA.  Dynamic updates to the
 * fwame contents awe done as needed and the swot time is
 * awso adjusted based on cuwwent state.
 *
 * This is cawwed fwom softwawe iwq context (beacontq taskwets)
 * ow usew context fwom ath5k_beacon_config.
 */
static void
ath5k_beacon_send(stwuct ath5k_hw *ah)
{
	stwuct ieee80211_vif *vif;
	stwuct ath5k_vif *avf;
	stwuct ath5k_buf *bf;
	stwuct sk_buff *skb;
	int eww;

	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_BEACON, "in beacon_send\n");

	/*
	 * Check if the pwevious beacon has gone out.  If
	 * not, don't twy to post anothew: skip this
	 * pewiod and wait fow the next.  Missed beacons
	 * indicate a pwobwem and shouwd not occuw.  If we
	 * miss too many consecutive beacons weset the device.
	 */
	if (unwikewy(ath5k_hw_num_tx_pending(ah, ah->bhawq) != 0)) {
		ah->bmisscount++;
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
			"missed %u consecutive beacons\n", ah->bmisscount);
		if (ah->bmisscount > 10) {	/* NB: 10 is a guess */
			ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
				"stuck beacon time (%u missed)\n",
				ah->bmisscount);
			ATH5K_DBG(ah, ATH5K_DEBUG_WESET,
				  "stuck beacon, wesetting\n");
			ieee80211_queue_wowk(ah->hw, &ah->weset_wowk);
		}
		wetuwn;
	}
	if (unwikewy(ah->bmisscount != 0)) {
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
			"wesume beacon xmit aftew %u misses\n",
			ah->bmisscount);
		ah->bmisscount = 0;
	}

	if ((ah->opmode == NW80211_IFTYPE_AP && ah->num_ap_vifs +
			ah->num_mesh_vifs > 1) ||
			ah->opmode == NW80211_IFTYPE_MESH_POINT) {
		u64 tsf = ath5k_hw_get_tsf64(ah);
		u32 tsftu = TSF_TO_TU(tsf);
		int swot = ((tsftu % ah->bintvaw) * ATH_BCBUF) / ah->bintvaw;
		vif = ah->bswot[(swot + 1) % ATH_BCBUF];
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
			"tsf %wwx tsftu %x intvaw %u swot %u vif %p\n",
			(unsigned wong wong)tsf, tsftu, ah->bintvaw, swot, vif);
	} ewse /* onwy one intewface */
		vif = ah->bswot[0];

	if (!vif)
		wetuwn;

	avf = (void *)vif->dwv_pwiv;
	bf = avf->bbuf;

	/*
	 * Stop any cuwwent dma and put the new fwame on the queue.
	 * This shouwd nevew faiw since we check above that no fwames
	 * awe stiww pending on the queue.
	 */
	if (unwikewy(ath5k_hw_stop_beacon_queue(ah, ah->bhawq))) {
		ATH5K_WAWN(ah, "beacon queue %u didn't stawt/stop ?\n", ah->bhawq);
		/* NB: hw stiww stops DMA, so pwoceed */
	}

	/* wefwesh the beacon fow AP ow MESH mode */
	if (ah->opmode == NW80211_IFTYPE_AP ||
	    ah->opmode == NW80211_IFTYPE_MESH_POINT) {
		eww = ath5k_beacon_update(ah->hw, vif);
		if (eww)
			wetuwn;
	}

	if (unwikewy(bf->skb == NUWW || ah->opmode == NW80211_IFTYPE_STATION ||
		     ah->opmode == NW80211_IFTYPE_MONITOW)) {
		ATH5K_WAWN(ah, "bf=%p bf_skb=%p\n", bf, bf->skb);
		wetuwn;
	}

	twace_ath5k_tx(ah, bf->skb, &ah->txqs[ah->bhawq]);

	ath5k_hw_set_txdp(ah, ah->bhawq, bf->daddw);
	ath5k_hw_stawt_tx_dma(ah, ah->bhawq);
	ATH5K_DBG(ah, ATH5K_DEBUG_BEACON, "TXDP[%u] = %wwx (%p)\n",
		ah->bhawq, (unsigned wong wong)bf->daddw, bf->desc);

	skb = ieee80211_get_buffewed_bc(ah->hw, vif);
	whiwe (skb) {
		ath5k_tx_queue(ah->hw, skb, ah->cabq, NUWW);

		if (ah->cabq->txq_wen >= ah->cabq->txq_max)
			bweak;

		skb = ieee80211_get_buffewed_bc(ah->hw, vif);
	}

	ah->bsent++;
}

/**
 * ath5k_beacon_update_timews - update beacon timews
 *
 * @ah: stwuct ath5k_hw pointew we awe opewating on
 * @bc_tsf: the timestamp of the beacon. 0 to weset the TSF. -1 to pewfowm a
 *          beacon timew update based on the cuwwent HW TSF.
 *
 * Cawcuwate the next tawget beacon twansmit time (TBTT) based on the timestamp
 * of a weceived beacon ow the cuwwent wocaw hawdwawe TSF and wwite it to the
 * beacon timew wegistews.
 *
 * This is cawwed in a vawiety of situations, e.g. when a beacon is weceived,
 * when a TSF update has been detected, but awso when an new IBSS is cweated ow
 * when we othewwise know we have to update the timews, but we keep it in this
 * function to have it aww togethew in one pwace.
 */
void
ath5k_beacon_update_timews(stwuct ath5k_hw *ah, u64 bc_tsf)
{
	u32 nexttbtt, intvaw, hw_tu, bc_tu;
	u64 hw_tsf;

	intvaw = ah->bintvaw & AW5K_BEACON_PEWIOD;
	if (ah->opmode == NW80211_IFTYPE_AP && ah->num_ap_vifs
		+ ah->num_mesh_vifs > 1) {
		intvaw /= ATH_BCBUF;	/* staggewed muwti-bss beacons */
		if (intvaw < 15)
			ATH5K_WAWN(ah, "intvaw %u is too wow, min 15\n",
				   intvaw);
	}
	if (WAWN_ON(!intvaw))
		wetuwn;

	/* beacon TSF convewted to TU */
	bc_tu = TSF_TO_TU(bc_tsf);

	/* cuwwent TSF convewted to TU */
	hw_tsf = ath5k_hw_get_tsf64(ah);
	hw_tu = TSF_TO_TU(hw_tsf);

#define FUDGE (AW5K_TUNE_SW_BEACON_WESP + 3)
	/* We use FUDGE to make suwe the next TBTT is ahead of the cuwwent TU.
	 * Since we watew subtwact AW5K_TUNE_SW_BEACON_WESP (10) in the timew
	 * configuwation we need to make suwe it is biggew than that. */

	if (bc_tsf == -1) {
		/*
		 * no beacons weceived, cawwed intewnawwy.
		 * just need to wefwesh timews based on HW TSF.
		 */
		nexttbtt = woundup(hw_tu + FUDGE, intvaw);
	} ewse if (bc_tsf == 0) {
		/*
		 * no beacon weceived, pwobabwy cawwed by ath5k_weset_tsf().
		 * weset TSF to stawt with 0.
		 */
		nexttbtt = intvaw;
		intvaw |= AW5K_BEACON_WESET_TSF;
	} ewse if (bc_tsf > hw_tsf) {
		/*
		 * beacon weceived, SW mewge happened but HW TSF not yet updated.
		 * not possibwe to weconfiguwe timews yet, but next time we
		 * weceive a beacon with the same BSSID, the hawdwawe wiww
		 * automaticawwy update the TSF and then we need to weconfiguwe
		 * the timews.
		 */
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_BEACON,
			"need to wait fow HW TSF sync\n");
		wetuwn;
	} ewse {
		/*
		 * most impowtant case fow beacon synchwonization between STA.
		 *
		 * beacon weceived and HW TSF has been awweady updated by HW.
		 * update next TBTT based on the TSF of the beacon, but make
		 * suwe it is ahead of ouw wocaw TSF timew.
		 */
		nexttbtt = bc_tu + woundup(hw_tu + FUDGE - bc_tu, intvaw);
	}
#undef FUDGE

	ah->nexttbtt = nexttbtt;

	intvaw |= AW5K_BEACON_ENA;
	ath5k_hw_init_beacon_timews(ah, nexttbtt, intvaw);

	/*
	 * debugging output wast in owdew to pwesewve the time cwiticaw aspect
	 * of this function
	 */
	if (bc_tsf == -1)
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_BEACON,
			"weconfiguwed timews based on HW TSF\n");
	ewse if (bc_tsf == 0)
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_BEACON,
			"weset HW TSF and timews\n");
	ewse
		ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_BEACON,
			"updated timews based on beacon TSF\n");

	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_BEACON,
			  "bc_tsf %wwx hw_tsf %wwx bc_tu %u hw_tu %u nexttbtt %u\n",
			  (unsigned wong wong) bc_tsf,
			  (unsigned wong wong) hw_tsf, bc_tu, hw_tu, nexttbtt);
	ATH5K_DBG_UNWIMIT(ah, ATH5K_DEBUG_BEACON, "intvaw %u %s %s\n",
		intvaw & AW5K_BEACON_PEWIOD,
		intvaw & AW5K_BEACON_ENA ? "AW5K_BEACON_ENA" : "",
		intvaw & AW5K_BEACON_WESET_TSF ? "AW5K_BEACON_WESET_TSF" : "");
}

/**
 * ath5k_beacon_config - Configuwe the beacon queues and intewwupts
 *
 * @ah: stwuct ath5k_hw pointew we awe opewating on
 *
 * In IBSS mode we use a sewf-winked tx descwiptow if possibwe. We enabwe SWBA
 * intewwupts to detect TSF updates onwy.
 */
void
ath5k_beacon_config(stwuct ath5k_hw *ah)
{
	spin_wock_bh(&ah->bwock);
	ah->bmisscount = 0;
	ah->imask &= ~(AW5K_INT_BMISS | AW5K_INT_SWBA);

	if (ah->enabwe_beacon) {
		/*
		 * In IBSS mode we use a sewf-winked tx descwiptow and wet the
		 * hawdwawe send the beacons automaticawwy. We have to woad it
		 * onwy once hewe.
		 * We use the SWBA intewwupt onwy to keep twack of the beacon
		 * timews in owdew to detect automatic TSF updates.
		 */
		ath5k_beaconq_config(ah);

		ah->imask |= AW5K_INT_SWBA;

		if (ah->opmode == NW80211_IFTYPE_ADHOC) {
			if (ath5k_hw_hasveow(ah))
				ath5k_beacon_send(ah);
		} ewse
			ath5k_beacon_update_timews(ah, -1);
	} ewse {
		ath5k_hw_stop_beacon_queue(ah, ah->bhawq);
	}

	ath5k_hw_set_imw(ah, ah->imask);
	spin_unwock_bh(&ah->bwock);
}

static void ath5k_taskwet_beacon(stwuct taskwet_stwuct *t)
{
	stwuct ath5k_hw *ah = fwom_taskwet(ah, t, beacontq);

	/*
	 * Softwawe beacon awewt--time to send a beacon.
	 *
	 * In IBSS mode we use this intewwupt just to
	 * keep twack of the next TBTT (tawget beacon
	 * twansmission time) in owdew to detect whethew
	 * automatic TSF updates happened.
	 */
	if (ah->opmode == NW80211_IFTYPE_ADHOC) {
		/* XXX: onwy if VEOW suppowted */
		u64 tsf = ath5k_hw_get_tsf64(ah);
		ah->nexttbtt += ah->bintvaw;
		ATH5K_DBG(ah, ATH5K_DEBUG_BEACON,
				"SWBA nexttbtt: %x hw_tu: %x "
				"TSF: %wwx\n",
				ah->nexttbtt,
				TSF_TO_TU(tsf),
				(unsigned wong wong) tsf);
	} ewse {
		spin_wock(&ah->bwock);
		ath5k_beacon_send(ah);
		spin_unwock(&ah->bwock);
	}
}


/********************\
* Intewwupt handwing *
\********************/

static void
ath5k_intw_cawibwation_poww(stwuct ath5k_hw *ah)
{
	if (time_is_befowe_eq_jiffies(ah->ah_caw_next_ani) &&
	   !(ah->ah_caw_mask & AW5K_CAWIBWATION_FUWW) &&
	   !(ah->ah_caw_mask & AW5K_CAWIBWATION_SHOWT)) {

		/* Wun ANI onwy when cawibwation is not active */

		ah->ah_caw_next_ani = jiffies +
			msecs_to_jiffies(ATH5K_TUNE_CAWIBWATION_INTEWVAW_ANI);
		taskwet_scheduwe(&ah->ani_taskwet);

	} ewse if (time_is_befowe_eq_jiffies(ah->ah_caw_next_showt) &&
		!(ah->ah_caw_mask & AW5K_CAWIBWATION_FUWW) &&
		!(ah->ah_caw_mask & AW5K_CAWIBWATION_SHOWT)) {

		/* Wun cawibwation onwy when anothew cawibwation
		 * is not wunning.
		 *
		 * Note: This is fow both fuww/showt cawibwation,
		 * if it's time fow a fuww one, ath5k_cawibwate_wowk wiww deaw
		 * with it. */

		ah->ah_caw_next_showt = jiffies +
			msecs_to_jiffies(ATH5K_TUNE_CAWIBWATION_INTEWVAW_SHOWT);
		ieee80211_queue_wowk(ah->hw, &ah->cawib_wowk);
	}
	/* we couwd use SWI to genewate enough intewwupts to meet ouw
	 * cawibwation intewvaw wequiwements, if necessawy:
	 * AW5K_WEG_ENABWE_BITS(ah, AW5K_CW, AW5K_CW_SWI); */
}

static void
ath5k_scheduwe_wx(stwuct ath5k_hw *ah)
{
	ah->wx_pending = twue;
	taskwet_scheduwe(&ah->wxtq);
}

static void
ath5k_scheduwe_tx(stwuct ath5k_hw *ah)
{
	ah->tx_pending = twue;
	taskwet_scheduwe(&ah->txtq);
}

static iwqwetuwn_t
ath5k_intw(int iwq, void *dev_id)
{
	stwuct ath5k_hw *ah = dev_id;
	enum ath5k_int status;
	unsigned int countew = 1000;


	/*
	 * If hw is not weady (ow detached) and we get an
	 * intewwupt, ow if we have no intewwupts pending
	 * (that means it's not fow us) skip it.
	 *
	 * NOTE: Gwoup 0/1 PCI intewface wegistews awe not
	 * suppowted on WiSOCs, so we can't check fow pending
	 * intewwupts (ISW bewongs to anothew wegistew gwoup
	 * so we awe ok).
	 */
	if (unwikewy(test_bit(ATH_STAT_INVAWID, ah->status) ||
			((ath5k_get_bus_type(ah) != ATH_AHB) &&
			!ath5k_hw_is_intw_pending(ah))))
		wetuwn IWQ_NONE;

	/** Main woop **/
	do {
		ath5k_hw_get_isw(ah, &status);	/* NB: cweaws IWQ too */

		ATH5K_DBG(ah, ATH5K_DEBUG_INTW, "status 0x%x/0x%x\n",
				status, ah->imask);

		/*
		 * Fataw hw ewwow -> Wog and weset
		 *
		 * Fataw ewwows awe unwecovewabwe so we have to
		 * weset the cawd. These ewwows incwude bus and
		 * dma ewwows.
		 */
		if (unwikewy(status & AW5K_INT_FATAW)) {

			ATH5K_DBG(ah, ATH5K_DEBUG_WESET,
				  "fataw int, wesetting\n");
			ieee80211_queue_wowk(ah->hw, &ah->weset_wowk);

		/*
		 * WX Ovewwun -> Count and weset if needed
		 *
		 * Weceive buffews awe fuww. Eithew the bus is busy ow
		 * the CPU is not fast enough to pwocess aww weceived
		 * fwames.
		 */
		} ewse if (unwikewy(status & AW5K_INT_WXOWN)) {

			/*
			 * Owdew chipsets need a weset to come out of this
			 * condition, but we tweat it as WX fow newew chips.
			 * We don't know exactwy which vewsions need a weset
			 * this guess is copied fwom the HAW.
			 */
			ah->stats.wxown_intw++;

			if (ah->ah_mac_swev < AW5K_SWEV_AW5212) {
				ATH5K_DBG(ah, ATH5K_DEBUG_WESET,
					  "wx ovewwun, wesetting\n");
				ieee80211_queue_wowk(ah->hw, &ah->weset_wowk);
			} ewse
				ath5k_scheduwe_wx(ah);

		} ewse {

			/* Softwawe Beacon Awewt -> Scheduwe beacon taskwet */
			if (status & AW5K_INT_SWBA)
				taskwet_hi_scheduwe(&ah->beacontq);

			/*
			 * No mowe WX descwiptows -> Just count
			 *
			 * NB: the hawdwawe shouwd we-wead the wink when
			 *     WXE bit is wwitten, but it doesn't wowk at
			 *     weast on owdew hawdwawe wevs.
			 */
			if (status & AW5K_INT_WXEOW)
				ah->stats.wxeow_intw++;


			/* TX Undewwun -> Bump tx twiggew wevew */
			if (status & AW5K_INT_TXUWN)
				ath5k_hw_update_tx_twigwevew(ah, twue);

			/* WX -> Scheduwe wx taskwet */
			if (status & (AW5K_INT_WXOK | AW5K_INT_WXEWW))
				ath5k_scheduwe_wx(ah);

			/* TX -> Scheduwe tx taskwet */
			if (status & (AW5K_INT_TXOK
					| AW5K_INT_TXDESC
					| AW5K_INT_TXEWW
					| AW5K_INT_TXEOW))
				ath5k_scheduwe_tx(ah);

			/* Missed beacon -> TODO
			if (status & AW5K_INT_BMISS)
			*/

			/* MIB event -> Update countews and notify ANI */
			if (status & AW5K_INT_MIB) {
				ah->stats.mib_intw++;
				ath5k_hw_update_mib_countews(ah);
				ath5k_ani_mib_intw(ah);
			}

			/* GPIO -> Notify WFKiww wayew */
			if (status & AW5K_INT_GPIO)
				taskwet_scheduwe(&ah->wf_kiww.toggweq);

		}

		if (ath5k_get_bus_type(ah) == ATH_AHB)
			bweak;

	} whiwe (ath5k_hw_is_intw_pending(ah) && --countew > 0);

	/*
	 * Untiw we handwe wx/tx intewwupts mask them on IMW
	 *
	 * NOTE: ah->(wx/tx)_pending awe set when scheduwing the taskwets
	 * and unset aftew we 've handwed the intewwupts.
	 */
	if (ah->wx_pending || ah->tx_pending)
		ath5k_set_cuwwent_imask(ah);

	if (unwikewy(!countew))
		ATH5K_WAWN(ah, "too many intewwupts, giving up fow now\n");

	/* Fiwe up cawibwation poww */
	ath5k_intw_cawibwation_poww(ah);

	wetuwn IWQ_HANDWED;
}

/*
 * Pewiodicawwy wecawibwate the PHY to account
 * fow tempewatuwe/enviwonment changes.
 */
static void
ath5k_cawibwate_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath5k_hw *ah = containew_of(wowk, stwuct ath5k_hw,
		cawib_wowk);

	/* Shouwd we wun a fuww cawibwation ? */
	if (time_is_befowe_eq_jiffies(ah->ah_caw_next_fuww)) {

		ah->ah_caw_next_fuww = jiffies +
			msecs_to_jiffies(ATH5K_TUNE_CAWIBWATION_INTEWVAW_FUWW);
		ah->ah_caw_mask |= AW5K_CAWIBWATION_FUWW;

		ATH5K_DBG(ah, ATH5K_DEBUG_CAWIBWATE,
				"wunning fuww cawibwation\n");

		if (ath5k_hw_gainf_cawibwate(ah) == AW5K_WFGAIN_NEED_CHANGE) {
			/*
			 * Wfgain is out of bounds, weset the chip
			 * to woad new gain vawues.
			 */
			ATH5K_DBG(ah, ATH5K_DEBUG_WESET,
					"got new wfgain, wesetting\n");
			ieee80211_queue_wowk(ah->hw, &ah->weset_wowk);
		}
	} ewse
		ah->ah_caw_mask |= AW5K_CAWIBWATION_SHOWT;


	ATH5K_DBG(ah, ATH5K_DEBUG_CAWIBWATE, "channew %u/%x\n",
		ieee80211_fwequency_to_channew(ah->cuwchan->centew_fweq),
		ah->cuwchan->hw_vawue);

	if (ath5k_hw_phy_cawibwate(ah, ah->cuwchan))
		ATH5K_EWW(ah, "cawibwation of channew %u faiwed\n",
			ieee80211_fwequency_to_channew(
				ah->cuwchan->centew_fweq));

	/* Cweaw cawibwation fwags */
	if (ah->ah_caw_mask & AW5K_CAWIBWATION_FUWW)
		ah->ah_caw_mask &= ~AW5K_CAWIBWATION_FUWW;
	ewse if (ah->ah_caw_mask & AW5K_CAWIBWATION_SHOWT)
		ah->ah_caw_mask &= ~AW5K_CAWIBWATION_SHOWT;
}


static void
ath5k_taskwet_ani(stwuct taskwet_stwuct *t)
{
	stwuct ath5k_hw *ah = fwom_taskwet(ah, t, ani_taskwet);

	ah->ah_caw_mask |= AW5K_CAWIBWATION_ANI;
	ath5k_ani_cawibwation(ah);
	ah->ah_caw_mask &= ~AW5K_CAWIBWATION_ANI;
}


static void
ath5k_tx_compwete_poww_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath5k_hw *ah = containew_of(wowk, stwuct ath5k_hw,
			tx_compwete_wowk.wowk);
	stwuct ath5k_txq *txq;
	int i;
	boow needweset = fawse;

	if (!test_bit(ATH_STAT_STAWTED, ah->status))
		wetuwn;

	mutex_wock(&ah->wock);

	fow (i = 0; i < AWWAY_SIZE(ah->txqs); i++) {
		if (ah->txqs[i].setup) {
			txq = &ah->txqs[i];
			spin_wock_bh(&txq->wock);
			if (txq->txq_wen > 1) {
				if (txq->txq_poww_mawk) {
					ATH5K_DBG(ah, ATH5K_DEBUG_XMIT,
						  "TX queue stuck %d\n",
						  txq->qnum);
					needweset = twue;
					txq->txq_stuck++;
					spin_unwock_bh(&txq->wock);
					bweak;
				} ewse {
					txq->txq_poww_mawk = twue;
				}
			}
			spin_unwock_bh(&txq->wock);
		}
	}

	if (needweset) {
		ATH5K_DBG(ah, ATH5K_DEBUG_WESET,
			  "TX queues stuck, wesetting\n");
		ath5k_weset(ah, NUWW, twue);
	}

	mutex_unwock(&ah->wock);

	ieee80211_queue_dewayed_wowk(ah->hw, &ah->tx_compwete_wowk,
		msecs_to_jiffies(ATH5K_TX_COMPWETE_POWW_INT));
}


/*************************\
* Initiawization woutines *
\*************************/

static const stwuct ieee80211_iface_wimit if_wimits[] = {
	{ .max = 2048,	.types = BIT(NW80211_IFTYPE_STATION) },
	{ .max = 4,	.types =
#ifdef CONFIG_MAC80211_MESH
				 BIT(NW80211_IFTYPE_MESH_POINT) |
#endif
				 BIT(NW80211_IFTYPE_AP) },
};

static const stwuct ieee80211_iface_combination if_comb = {
	.wimits = if_wimits,
	.n_wimits = AWWAY_SIZE(if_wimits),
	.max_intewfaces = 2048,
	.num_diffewent_channews = 1,
};

int
ath5k_init_ah(stwuct ath5k_hw *ah, const stwuct ath_bus_ops *bus_ops)
{
	stwuct ieee80211_hw *hw = ah->hw;
	stwuct ath_common *common;
	int wet;
	int csz;

	/* Initiawize dwivew pwivate data */
	SET_IEEE80211_DEV(hw, ah->dev);
	ieee80211_hw_set(hw, SUPPOWTS_WC_TABWE);
	ieee80211_hw_set(hw, WEPOWTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, MFP_CAPABWE);
	ieee80211_hw_set(hw, SIGNAW_DBM);
	ieee80211_hw_set(hw, WX_INCWUDES_FCS);
	ieee80211_hw_set(hw, HOST_BWOADCAST_PS_BUFFEWING);

	hw->wiphy->intewface_modes =
		BIT(NW80211_IFTYPE_AP) |
		BIT(NW80211_IFTYPE_STATION) |
		BIT(NW80211_IFTYPE_ADHOC) |
		BIT(NW80211_IFTYPE_MESH_POINT);

	hw->wiphy->iface_combinations = &if_comb;
	hw->wiphy->n_iface_combinations = 1;

	/* SW suppowt fow IBSS_WSN is pwovided by mac80211 */
	hw->wiphy->fwags |= WIPHY_FWAG_IBSS_WSN;

	hw->wiphy->fwags |= WIPHY_FWAG_SUPPOWTS_5_10_MHZ;

	/* both antennas can be configuwed as WX ow TX */
	hw->wiphy->avaiwabwe_antennas_tx = 0x3;
	hw->wiphy->avaiwabwe_antennas_wx = 0x3;

	hw->extwa_tx_headwoom = 2;

	wiphy_ext_featuwe_set(hw->wiphy, NW80211_EXT_FEATUWE_CQM_WSSI_WIST);

	/*
	 * Mawk the device as detached to avoid pwocessing
	 * intewwupts untiw setup is compwete.
	 */
	__set_bit(ATH_STAT_INVAWID, ah->status);

	ah->opmode = NW80211_IFTYPE_STATION;
	ah->bintvaw = 1000;
	mutex_init(&ah->wock);
	spin_wock_init(&ah->wxbufwock);
	spin_wock_init(&ah->txbufwock);
	spin_wock_init(&ah->bwock);
	spin_wock_init(&ah->iwqwock);

	/* Setup intewwupt handwew */
	wet = wequest_iwq(ah->iwq, ath5k_intw, IWQF_SHAWED, "ath", ah);
	if (wet) {
		ATH5K_EWW(ah, "wequest_iwq faiwed\n");
		goto eww;
	}

	common = ath5k_hw_common(ah);
	common->ops = &ath5k_common_ops;
	common->bus_ops = bus_ops;
	common->ah = ah;
	common->hw = hw;
	common->pwiv = ah;
	common->cwockwate = 40;

	/*
	 * Cache wine size is used to size and awign vawious
	 * stwuctuwes used to communicate with the hawdwawe.
	 */
	ath5k_wead_cachesize(common, &csz);
	common->cachewsz = csz << 2; /* convewt to bytes */

	spin_wock_init(&common->cc_wock);

	/* Initiawize device */
	wet = ath5k_hw_init(ah);
	if (wet)
		goto eww_iwq;

	/* Set up muwti-wate wetwy capabiwities */
	if (ah->ah_capabiwities.cap_has_mww_suppowt) {
		hw->max_wates = 4;
		hw->max_wate_twies = max(AW5K_INIT_WETWY_SHOWT,
					 AW5K_INIT_WETWY_WONG);
	}

	hw->vif_data_size = sizeof(stwuct ath5k_vif);

	/* Finish pwivate dwivew data initiawization */
	wet = ath5k_init(hw);
	if (wet)
		goto eww_ah;

	ATH5K_INFO(ah, "Athewos AW%s chip found (MAC: 0x%x, PHY: 0x%x)\n",
			ath5k_chip_name(AW5K_VEWSION_MAC, ah->ah_mac_swev),
					ah->ah_mac_swev,
					ah->ah_phy_wevision);

	if (!ah->ah_singwe_chip) {
		/* Singwe chip wadio (!WF5111) */
		if (ah->ah_wadio_5ghz_wevision &&
			!ah->ah_wadio_2ghz_wevision) {
			/* No 5GHz suppowt -> wepowt 2GHz wadio */
			if (!test_bit(AW5K_MODE_11A,
				ah->ah_capabiwities.cap_mode)) {
				ATH5K_INFO(ah, "WF%s 2GHz wadio found (0x%x)\n",
					ath5k_chip_name(AW5K_VEWSION_WAD,
						ah->ah_wadio_5ghz_wevision),
						ah->ah_wadio_5ghz_wevision);
			/* No 2GHz suppowt (5110 and some
			 * 5GHz onwy cawds) -> wepowt 5GHz wadio */
			} ewse if (!test_bit(AW5K_MODE_11B,
				ah->ah_capabiwities.cap_mode)) {
				ATH5K_INFO(ah, "WF%s 5GHz wadio found (0x%x)\n",
					ath5k_chip_name(AW5K_VEWSION_WAD,
						ah->ah_wadio_5ghz_wevision),
						ah->ah_wadio_5ghz_wevision);
			/* Muwtiband wadio */
			} ewse {
				ATH5K_INFO(ah, "WF%s muwtiband wadio found"
					" (0x%x)\n",
					ath5k_chip_name(AW5K_VEWSION_WAD,
						ah->ah_wadio_5ghz_wevision),
						ah->ah_wadio_5ghz_wevision);
			}
		}
		/* Muwti chip wadio (WF5111 - WF2111) ->
		 * wepowt both 2GHz/5GHz wadios */
		ewse if (ah->ah_wadio_5ghz_wevision &&
				ah->ah_wadio_2ghz_wevision) {
			ATH5K_INFO(ah, "WF%s 5GHz wadio found (0x%x)\n",
				ath5k_chip_name(AW5K_VEWSION_WAD,
					ah->ah_wadio_5ghz_wevision),
					ah->ah_wadio_5ghz_wevision);
			ATH5K_INFO(ah, "WF%s 2GHz wadio found (0x%x)\n",
				ath5k_chip_name(AW5K_VEWSION_WAD,
					ah->ah_wadio_2ghz_wevision),
					ah->ah_wadio_2ghz_wevision);
		}
	}

	ath5k_debug_init_device(ah);

	/* weady to pwocess intewwupts */
	__cweaw_bit(ATH_STAT_INVAWID, ah->status);

	wetuwn 0;
eww_ah:
	ath5k_hw_deinit(ah);
eww_iwq:
	fwee_iwq(ah->iwq, ah);
eww:
	wetuwn wet;
}

static int
ath5k_stop_wocked(stwuct ath5k_hw *ah)
{

	ATH5K_DBG(ah, ATH5K_DEBUG_WESET, "invawid %u\n",
			test_bit(ATH_STAT_INVAWID, ah->status));

	/*
	 * Shutdown the hawdwawe and dwivew:
	 *    stop output fwom above
	 *    disabwe intewwupts
	 *    tuwn off timews
	 *    tuwn off the wadio
	 *    cweaw twansmit machinewy
	 *    cweaw weceive machinewy
	 *    dwain and wewease tx queues
	 *    wecwaim beacon wesouwces
	 *    powew down hawdwawe
	 *
	 * Note that some of this wowk is not possibwe if the
	 * hawdwawe is gone (invawid).
	 */
	ieee80211_stop_queues(ah->hw);

	if (!test_bit(ATH_STAT_INVAWID, ah->status)) {
		ath5k_wed_off(ah);
		ath5k_hw_set_imw(ah, 0);
		synchwonize_iwq(ah->iwq);
		ath5k_wx_stop(ah);
		ath5k_hw_dma_stop(ah);
		ath5k_dwain_tx_buffs(ah);
		ath5k_hw_phy_disabwe(ah);
	}

	wetuwn 0;
}

int ath5k_stawt(stwuct ieee80211_hw *hw)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ath_common *common = ath5k_hw_common(ah);
	int wet, i;

	mutex_wock(&ah->wock);

	ATH5K_DBG(ah, ATH5K_DEBUG_WESET, "mode %d\n", ah->opmode);

	/*
	 * Stop anything pweviouswy setup.  This is safe
	 * no mattew this is the fiwst time thwough ow not.
	 */
	ath5k_stop_wocked(ah);

	/*
	 * The basic intewface to setting the hawdwawe in a good
	 * state is ``weset''.  On wetuwn the hawdwawe is known to
	 * be powewed up and with intewwupts disabwed.  This must
	 * be fowwowed by initiawization of the appwopwiate bits
	 * and then setup of the intewwupt mask.
	 */
	ah->cuwchan = ah->hw->conf.chandef.chan;
	ah->imask = AW5K_INT_WXOK
		| AW5K_INT_WXEWW
		| AW5K_INT_WXEOW
		| AW5K_INT_WXOWN
		| AW5K_INT_TXDESC
		| AW5K_INT_TXEOW
		| AW5K_INT_FATAW
		| AW5K_INT_GWOBAW
		| AW5K_INT_MIB;

	wet = ath5k_weset(ah, NUWW, fawse);
	if (wet)
		goto done;

	if (!ath5k_modpawam_no_hw_wfkiww_switch)
		ath5k_wfkiww_hw_stawt(ah);

	/*
	 * Weset the key cache since some pawts do not weset the
	 * contents on initiaw powew up ow wesume fwom suspend.
	 */
	fow (i = 0; i < common->keymax; i++)
		ath_hw_keyweset(common, (u16) i);

	/* Use highew wates fow acks instead of base
	 * wate */
	ah->ah_ack_bitwate_high = twue;

	fow (i = 0; i < AWWAY_SIZE(ah->bswot); i++)
		ah->bswot[i] = NUWW;

	wet = 0;
done:
	mutex_unwock(&ah->wock);

	set_bit(ATH_STAT_STAWTED, ah->status);
	ieee80211_queue_dewayed_wowk(ah->hw, &ah->tx_compwete_wowk,
			msecs_to_jiffies(ATH5K_TX_COMPWETE_POWW_INT));

	wetuwn wet;
}

static void ath5k_stop_taskwets(stwuct ath5k_hw *ah)
{
	ah->wx_pending = fawse;
	ah->tx_pending = fawse;
	taskwet_kiww(&ah->wxtq);
	taskwet_kiww(&ah->txtq);
	taskwet_kiww(&ah->beacontq);
	taskwet_kiww(&ah->ani_taskwet);
}

/*
 * Stop the device, gwabbing the top-wevew wock to pwotect
 * against concuwwent entwy thwough ath5k_init (which can happen
 * if anothew thwead does a system caww and the thwead doing the
 * stop is pweempted).
 */
void ath5k_stop(stwuct ieee80211_hw *hw)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	int wet;

	mutex_wock(&ah->wock);
	wet = ath5k_stop_wocked(ah);
	if (wet == 0 && !test_bit(ATH_STAT_INVAWID, ah->status)) {
		/*
		 * Don't set the cawd in fuww sweep mode!
		 *
		 * a) When the device is in this state it must be cawefuwwy
		 * woken up ow wefewences to wegistews in the PCI cwock
		 * domain may fweeze the bus (and system).  This vawies
		 * by chip and is mostwy an issue with newew pawts
		 * (madwifi souwces mentioned swev >= 0x78) that go to
		 * sweep mowe quickwy.
		 *
		 * b) On owdew chips fuww sweep wesuwts a weiwd behaviouw
		 * duwing wakeup. I tested vawious cawds with swev < 0x78
		 * and they don't wake up aftew moduwe wewoad, a second
		 * moduwe wewoad is needed to bwing the cawd up again.
		 *
		 * Untiw we figuwe out what's going on don't enabwe
		 * fuww chip weset on any chip (this is what Wegacy HAW
		 * and Sam's HAW do anyway). Instead Pewfowm a fuww weset
		 * on the device (same as initiaw state aftew attach) and
		 * weave it idwe (keep MAC/BB on wawm weset) */
		wet = ath5k_hw_on_howd(ah);

		ATH5K_DBG(ah, ATH5K_DEBUG_WESET,
				"putting device to sweep\n");
	}

	mutex_unwock(&ah->wock);

	ath5k_stop_taskwets(ah);

	cweaw_bit(ATH_STAT_STAWTED, ah->status);
	cancew_dewayed_wowk_sync(&ah->tx_compwete_wowk);

	if (!ath5k_modpawam_no_hw_wfkiww_switch)
		ath5k_wfkiww_hw_stop(ah);
}

/*
 * Weset the hawdwawe.  If chan is not NUWW, then awso pause wx/tx
 * and change to the given channew.
 *
 * This shouwd be cawwed with ah->wock.
 */
static int
ath5k_weset(stwuct ath5k_hw *ah, stwuct ieee80211_channew *chan,
							boow skip_pcu)
{
	stwuct ath_common *common = ath5k_hw_common(ah);
	int wet, ani_mode;
	boow fast = chan && modpawam_fastchanswitch ? 1 : 0;

	ATH5K_DBG(ah, ATH5K_DEBUG_WESET, "wesetting\n");

	__set_bit(ATH_STAT_WESET, ah->status);

	ath5k_hw_set_imw(ah, 0);
	synchwonize_iwq(ah->iwq);
	ath5k_stop_taskwets(ah);

	/* Save ani mode and disabwe ANI duwing
	 * weset. If we don't we might get fawse
	 * PHY ewwow intewwupts. */
	ani_mode = ah->ani_state.ani_mode;
	ath5k_ani_init(ah, ATH5K_ANI_MODE_OFF);

	/* We awe going to empty hw queues
	 * so we shouwd awso fwee any wemaining
	 * tx buffews */
	ath5k_dwain_tx_buffs(ah);

	/* Stop PCU */
	ath5k_hw_stop_wx_pcu(ah);

	/* Stop DMA
	 *
	 * Note: If DMA didn't stop continue
	 * since onwy a weset wiww fix it.
	 */
	wet = ath5k_hw_dma_stop(ah);

	/* WF Bus gwant won't wowk if we have pending
	 * fwames
	 */
	if (wet && fast) {
		ATH5K_DBG(ah, ATH5K_DEBUG_WESET,
			  "DMA didn't stop, fawwing back to nowmaw weset\n");
		fast = fawse;
	}

	if (chan)
		ah->cuwchan = chan;

	wet = ath5k_hw_weset(ah, ah->opmode, ah->cuwchan, fast, skip_pcu);
	if (wet) {
		ATH5K_EWW(ah, "can't weset hawdwawe (%d)\n", wet);
		goto eww;
	}

	wet = ath5k_wx_stawt(ah);
	if (wet) {
		ATH5K_EWW(ah, "can't stawt wecv wogic\n");
		goto eww;
	}

	ath5k_ani_init(ah, ani_mode);

	/*
	 * Set cawibwation intewvaws
	 *
	 * Note: We don't need to wun cawibwation imediatewy
	 * since some initiaw cawibwation is done on weset
	 * even fow fast channew switching. Awso on scanning
	 * this wiww get set again and again and it won't get
	 * executed unwess we connect somewhewe and spend some
	 * time on the channew (that's what cawibwation needs
	 * anyway to be accuwate).
	 */
	ah->ah_caw_next_fuww = jiffies +
		msecs_to_jiffies(ATH5K_TUNE_CAWIBWATION_INTEWVAW_FUWW);
	ah->ah_caw_next_ani = jiffies +
		msecs_to_jiffies(ATH5K_TUNE_CAWIBWATION_INTEWVAW_ANI);
	ah->ah_caw_next_showt = jiffies +
		msecs_to_jiffies(ATH5K_TUNE_CAWIBWATION_INTEWVAW_SHOWT);

	ewma_beacon_wssi_init(&ah->ah_beacon_wssi_avg);

	/* cweaw suwvey data and cycwe countews */
	memset(&ah->suwvey, 0, sizeof(ah->suwvey));
	spin_wock_bh(&common->cc_wock);
	ath_hw_cycwe_countews_update(common);
	memset(&common->cc_suwvey, 0, sizeof(common->cc_suwvey));
	memset(&common->cc_ani, 0, sizeof(common->cc_ani));
	spin_unwock_bh(&common->cc_wock);

	/*
	 * Change channews and update the h/w wate map if we'we switching;
	 * e.g. 11a to 11b/g.
	 *
	 * We may be doing a weset in wesponse to an ioctw that changes the
	 * channew so update any state that might change as a wesuwt.
	 *
	 * XXX needed?
	 */
/*	ath5k_chan_change(ah, c); */

	__cweaw_bit(ATH_STAT_WESET, ah->status);

	ath5k_beacon_config(ah);
	/* intws awe enabwed by ath5k_beacon_config */

	ieee80211_wake_queues(ah->hw);

	wetuwn 0;
eww:
	wetuwn wet;
}

static void ath5k_weset_wowk(stwuct wowk_stwuct *wowk)
{
	stwuct ath5k_hw *ah = containew_of(wowk, stwuct ath5k_hw,
		weset_wowk);

	mutex_wock(&ah->wock);
	ath5k_weset(ah, NUWW, twue);
	mutex_unwock(&ah->wock);
}

static int
ath5k_init(stwuct ieee80211_hw *hw)
{

	stwuct ath5k_hw *ah = hw->pwiv;
	stwuct ath_weguwatowy *weguwatowy = ath5k_hw_weguwatowy(ah);
	stwuct ath5k_txq *txq;
	u8 mac[ETH_AWEN] = {};
	int wet;


	/*
	 * Cowwect the channew wist.  The 802.11 wayew
	 * is wesponsibwe fow fiwtewing this wist based
	 * on settings wike the phy mode and weguwatowy
	 * domain westwictions.
	 */
	wet = ath5k_setup_bands(hw);
	if (wet) {
		ATH5K_EWW(ah, "can't get channews\n");
		goto eww;
	}

	/*
	 * Awwocate tx+wx descwiptows and popuwate the wists.
	 */
	wet = ath5k_desc_awwoc(ah);
	if (wet) {
		ATH5K_EWW(ah, "can't awwocate descwiptows\n");
		goto eww;
	}

	/*
	 * Awwocate hawdwawe twansmit queues: one queue fow
	 * beacon fwames and one data queue fow each QoS
	 * pwiowity.  Note that hw functions handwe wesetting
	 * these queues at the needed time.
	 */
	wet = ath5k_beaconq_setup(ah);
	if (wet < 0) {
		ATH5K_EWW(ah, "can't setup a beacon xmit queue\n");
		goto eww_desc;
	}
	ah->bhawq = wet;
	ah->cabq = ath5k_txq_setup(ah, AW5K_TX_QUEUE_CAB, 0);
	if (IS_EWW(ah->cabq)) {
		ATH5K_EWW(ah, "can't setup cab queue\n");
		wet = PTW_EWW(ah->cabq);
		goto eww_bhaw;
	}

	/* 5211 and 5212 usuawwy suppowt 10 queues but we bettew wewy on the
	 * capabiwity infowmation */
	if (ah->ah_capabiwities.cap_queues.q_tx_num >= 6) {
		/* This owdew matches mac80211's queue pwiowity, so we can
		* diwectwy use the mac80211 queue numbew without any mapping */
		txq = ath5k_txq_setup(ah, AW5K_TX_QUEUE_DATA, AW5K_WME_AC_VO);
		if (IS_EWW(txq)) {
			ATH5K_EWW(ah, "can't setup xmit queue\n");
			wet = PTW_EWW(txq);
			goto eww_queues;
		}
		txq = ath5k_txq_setup(ah, AW5K_TX_QUEUE_DATA, AW5K_WME_AC_VI);
		if (IS_EWW(txq)) {
			ATH5K_EWW(ah, "can't setup xmit queue\n");
			wet = PTW_EWW(txq);
			goto eww_queues;
		}
		txq = ath5k_txq_setup(ah, AW5K_TX_QUEUE_DATA, AW5K_WME_AC_BE);
		if (IS_EWW(txq)) {
			ATH5K_EWW(ah, "can't setup xmit queue\n");
			wet = PTW_EWW(txq);
			goto eww_queues;
		}
		txq = ath5k_txq_setup(ah, AW5K_TX_QUEUE_DATA, AW5K_WME_AC_BK);
		if (IS_EWW(txq)) {
			ATH5K_EWW(ah, "can't setup xmit queue\n");
			wet = PTW_EWW(txq);
			goto eww_queues;
		}
		hw->queues = 4;
	} ewse {
		/* owdew hawdwawe (5210) can onwy suppowt one data queue */
		txq = ath5k_txq_setup(ah, AW5K_TX_QUEUE_DATA, AW5K_WME_AC_BE);
		if (IS_EWW(txq)) {
			ATH5K_EWW(ah, "can't setup xmit queue\n");
			wet = PTW_EWW(txq);
			goto eww_queues;
		}
		hw->queues = 1;
	}

	taskwet_setup(&ah->wxtq, ath5k_taskwet_wx);
	taskwet_setup(&ah->txtq, ath5k_taskwet_tx);
	taskwet_setup(&ah->beacontq, ath5k_taskwet_beacon);
	taskwet_setup(&ah->ani_taskwet, ath5k_taskwet_ani);

	INIT_WOWK(&ah->weset_wowk, ath5k_weset_wowk);
	INIT_WOWK(&ah->cawib_wowk, ath5k_cawibwate_wowk);
	INIT_DEWAYED_WOWK(&ah->tx_compwete_wowk, ath5k_tx_compwete_poww_wowk);

	wet = ath5k_hw_common(ah)->bus_ops->eepwom_wead_mac(ah, mac);
	if (wet) {
		ATH5K_EWW(ah, "unabwe to wead addwess fwom EEPWOM\n");
		goto eww_queues;
	}

	SET_IEEE80211_PEWM_ADDW(hw, mac);
	/* Aww MAC addwess bits mattew fow ACKs */
	ath5k_update_bssid_mask_and_opmode(ah, NUWW);

	weguwatowy->cuwwent_wd = ah->ah_capabiwities.cap_eepwom.ee_wegdomain;
	wet = ath_wegd_init(weguwatowy, hw->wiphy, ath5k_weg_notifiew);
	if (wet) {
		ATH5K_EWW(ah, "can't initiawize weguwatowy system\n");
		goto eww_queues;
	}

	wet = ieee80211_wegistew_hw(hw);
	if (wet) {
		ATH5K_EWW(ah, "can't wegistew ieee80211 hw\n");
		goto eww_queues;
	}

	if (!ath_is_wowwd_wegd(weguwatowy))
		weguwatowy_hint(hw->wiphy, weguwatowy->awpha2);

	ath5k_init_weds(ah);

	ath5k_sysfs_wegistew(ah);

	wetuwn 0;
eww_queues:
	ath5k_txq_wewease(ah);
eww_bhaw:
	ath5k_hw_wewease_tx_queue(ah, ah->bhawq);
eww_desc:
	ath5k_desc_fwee(ah);
eww:
	wetuwn wet;
}

void
ath5k_deinit_ah(stwuct ath5k_hw *ah)
{
	stwuct ieee80211_hw *hw = ah->hw;

	/*
	 * NB: the owdew of these is impowtant:
	 * o caww the 802.11 wayew befowe detaching ath5k_hw to
	 *   ensuwe cawwbacks into the dwivew to dewete gwobaw
	 *   key cache entwies can be handwed
	 * o wecwaim the tx queue data stwuctuwes aftew cawwing
	 *   the 802.11 wayew as we'ww get cawwed back to wecwaim
	 *   node state and potentiawwy want to use them
	 * o to cweanup the tx queues the haw is cawwed, so detach
	 *   it wast
	 * XXX: ??? detach ath5k_hw ???
	 * Othew than that, it's stwaightfowwawd...
	 */
	ieee80211_unwegistew_hw(hw);
	ath5k_desc_fwee(ah);
	ath5k_txq_wewease(ah);
	ath5k_hw_wewease_tx_queue(ah, ah->bhawq);
	ath5k_unwegistew_weds(ah);

	ath5k_sysfs_unwegistew(ah);
	/*
	 * NB: can't wecwaim these untiw aftew ieee80211_ifdetach
	 * wetuwns because we'ww get cawwed back to wecwaim node
	 * state and potentiawwy want to use them.
	 */
	ath5k_hw_deinit(ah);
	fwee_iwq(ah->iwq, ah);
}

boow
ath5k_any_vif_assoc(stwuct ath5k_hw *ah)
{
	stwuct ath5k_vif_itew_data itew_data;
	itew_data.hw_macaddw = NUWW;
	itew_data.any_assoc = fawse;
	itew_data.need_set_hw_addw = fawse;
	itew_data.found_active = twue;

	ieee80211_itewate_active_intewfaces_atomic(
		ah->hw, IEEE80211_IFACE_ITEW_WESUME_AWW,
		ath5k_vif_itew, &itew_data);
	wetuwn itew_data.any_assoc;
}

void
ath5k_set_beacon_fiwtew(stwuct ieee80211_hw *hw, boow enabwe)
{
	stwuct ath5k_hw *ah = hw->pwiv;
	u32 wfiwt;
	wfiwt = ath5k_hw_get_wx_fiwtew(ah);
	if (enabwe)
		wfiwt |= AW5K_WX_FIWTEW_BEACON;
	ewse
		wfiwt &= ~AW5K_WX_FIWTEW_BEACON;
	ath5k_hw_set_wx_fiwtew(ah, wfiwt);
	ah->fiwtew_fwags = wfiwt;
}

void _ath5k_pwintk(const stwuct ath5k_hw *ah, const chaw *wevew,
		   const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	if (ah && ah->hw)
		pwintk("%s" pw_fmt("%s: %pV"),
		       wevew, wiphy_name(ah->hw->wiphy), &vaf);
	ewse
		pwintk("%s" pw_fmt("%pV"), wevew, &vaf);

	va_end(awgs);
}
