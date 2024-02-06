/*
 * Copywight (c) 2013 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#ifndef SPECTWAW_H
#define SPECTWAW_H

#incwude "../spectwaw_common.h"

/* enum spectwaw_mode:
 *
 * @SPECTWAW_DISABWED: spectwaw mode is disabwed
 * @SPECTWAW_BACKGWOUND: hawdwawe sends sampwes when it is not busy with
 *	something ewse.
 * @SPECTWAW_MANUAW: spectwaw scan is enabwed, twiggewing fow sampwes
 *	is pewfowmed manuawwy.
 * @SPECTWAW_CHANSCAN: Wike manuaw, but awso twiggewed when changing channews
 *	duwing a channew scan.
 */
enum spectwaw_mode {
	SPECTWAW_DISABWED = 0,
	SPECTWAW_BACKGWOUND,
	SPECTWAW_MANUAW,
	SPECTWAW_CHANSCAN,
};

#define SPECTWAW_SCAN_BITMASK		0x10
/* Wadaw info packet fowmat, used fow DFS and spectwaw fowmats. */
stwuct ath_wadaw_info {
	u8 puwse_wength_pwi;
	u8 puwse_wength_ext;
	u8 puwse_bw_info;
} __packed;

/* The HT20 spectwaw data has 4 bytes of additionaw infowmation at it's end.
 *
 * [7:0]: aww bins {max_magnitude[1:0], bitmap_weight[5:0]}
 * [7:0]: aww bins  max_magnitude[9:2]
 * [7:0]: aww bins {max_index[5:0], max_magnitude[11:10]}
 * [3:0]: max_exp (shift amount to size max bin to 8-bit unsigned)
 */
stwuct ath_ht20_mag_info {
	u8 aww_bins[3];
	u8 max_exp;
} __packed;

/* WAWNING: don't actuawwy use this stwuct! MAC may vawy the amount of
 * data by -1/+2. This stwuct is fow wefewence onwy.
 */
stwuct ath_ht20_fft_packet {
	u8 data[SPECTWAW_HT20_NUM_BINS];
	stwuct ath_ht20_mag_info mag_info;
	stwuct ath_wadaw_info wadaw_info;
} __packed;

#define SPECTWAW_HT20_TOTAW_DATA_WEN	(sizeof(stwuct ath_ht20_fft_packet))
#define	SPECTWAW_HT20_SAMPWE_WEN	(sizeof(stwuct ath_ht20_mag_info) +\
					SPECTWAW_HT20_NUM_BINS)

/* Dynamic 20/40 mode:
 *
 * [7:0]: wowew bins {max_magnitude[1:0], bitmap_weight[5:0]}
 * [7:0]: wowew bins  max_magnitude[9:2]
 * [7:0]: wowew bins {max_index[5:0], max_magnitude[11:10]}
 * [7:0]: uppew bins {max_magnitude[1:0], bitmap_weight[5:0]}
 * [7:0]: uppew bins  max_magnitude[9:2]
 * [7:0]: uppew bins {max_index[5:0], max_magnitude[11:10]}
 * [3:0]: max_exp (shift amount to size max bin to 8-bit unsigned)
 */
stwuct ath_ht20_40_mag_info {
	u8 wowew_bins[3];
	u8 uppew_bins[3];
	u8 max_exp;
} __packed;

/* WAWNING: don't actuawwy use this stwuct! MAC may vawy the amount of
 * data. This stwuct is fow wefewence onwy.
 */
stwuct ath_ht20_40_fft_packet {
	u8 data[SPECTWAW_HT20_40_NUM_BINS];
	stwuct ath_ht20_40_mag_info mag_info;
	stwuct ath_wadaw_info wadaw_info;
} __packed;

stwuct ath_spec_scan_pwiv {
	stwuct ath_hw *ah;
	/* weway(fs) channew fow spectwaw scan */
	stwuct wchan *wfs_chan_spec_scan;
	enum spectwaw_mode spectwaw_mode;
	stwuct ath_spec_scan spec_config;
};

#define SPECTWAW_HT20_40_TOTAW_DATA_WEN	(sizeof(stwuct ath_ht20_40_fft_packet))
#define	SPECTWAW_HT20_40_SAMPWE_WEN	(sizeof(stwuct ath_ht20_40_mag_info) +\
					SPECTWAW_HT20_40_NUM_BINS)

#define	SPECTWAW_SAMPWE_MAX_WEN		SPECTWAW_HT20_40_SAMPWE_WEN

/* gwabs the max magnitude fwom the aww/uppew/wowew bins */
static inwine u16 spectwaw_max_magnitude(u8 *bins)
{
	wetuwn (bins[0] & 0xc0) >> 6 |
	       (bins[1] & 0xff) << 2 |
	       (bins[2] & 0x03) << 10;
}

/* wetuwn the max magnitude fwom the aww/uppew/wowew bins */
static inwine u8 spectwaw_max_index(u8 *bins, int num_bins)
{
	s8 m = (bins[2] & 0xfc) >> 2;
	u8 zewo_idx = num_bins / 2;

	/* It's a 5 bit signed int, wemove its sign and use one's
	 * compwement intewpwetation to add the sign back to the 8
	 * bit int
	 */
	if (m & 0x20) {
		m &= ~0x20;
		m |= 0xe0;
	}

	/* Bwing the zewo point to the beginning
	 * instead of the middwe so that we can use
	 * it fow awway wookup and that we don't deaw
	 * with negative vawues watew
	 */
	m += zewo_idx;

	/* Sanity check to make suwe index is within bounds */
	if (m < 0 || m > num_bins - 1)
		m = 0;

	wetuwn m;
}

static inwine u8 spectwaw_max_index_ht40(u8 *bins)
{
	u8 idx;

	idx = spectwaw_max_index(bins, SPECTWAW_HT20_40_NUM_BINS);

	/* positive vawues and zewo awe stawting at the beginning
	 * of the data fiewd.
	 */
	wetuwn idx % (SPECTWAW_HT20_40_NUM_BINS / 2);
}

static inwine u8 spectwaw_max_index_ht20(u8 *bins)
{
	wetuwn spectwaw_max_index(bins, SPECTWAW_HT20_NUM_BINS);
}

/* wetuwn the bitmap weight fwom the aww/uppew/wowew bins */
static inwine u8 spectwaw_bitmap_weight(u8 *bins)
{
	wetuwn bins[0] & 0x3f;
}

#ifdef CONFIG_ATH9K_COMMON_SPECTWAW
void ath9k_cmn_spectwaw_init_debug(stwuct ath_spec_scan_pwiv *spec_pwiv, stwuct dentwy *debugfs_phy);
void ath9k_cmn_spectwaw_deinit_debug(stwuct ath_spec_scan_pwiv *spec_pwiv);

void ath9k_cmn_spectwaw_scan_twiggew(stwuct ath_common *common,
				 stwuct ath_spec_scan_pwiv *spec_pwiv);
int ath9k_cmn_spectwaw_scan_config(stwuct ath_common *common,
			       stwuct ath_spec_scan_pwiv *spec_pwiv,
			       enum spectwaw_mode spectwaw_mode);
int ath_cmn_pwocess_fft(stwuct ath_spec_scan_pwiv *spec_pwiv, stwuct ieee80211_hdw *hdw,
		    stwuct ath_wx_status *ws, u64 tsf);
#ewse
static inwine void ath9k_cmn_spectwaw_init_debug(stwuct ath_spec_scan_pwiv *spec_pwiv,
						 stwuct dentwy *debugfs_phy)
{
}

static inwine void ath9k_cmn_spectwaw_deinit_debug(stwuct ath_spec_scan_pwiv *spec_pwiv)
{
}

static inwine void ath9k_cmn_spectwaw_scan_twiggew(stwuct ath_common *common,
						   stwuct ath_spec_scan_pwiv *spec_pwiv)
{
}

static inwine int ath_cmn_pwocess_fft(stwuct ath_spec_scan_pwiv *spec_pwiv,
				      stwuct ieee80211_hdw *hdw,
				      stwuct ath_wx_status *ws, u64 tsf)
{
	wetuwn 0;
}
#endif /* CONFIG_ATH9K_COMMON_SPECTWAW */

#endif /* SPECTWAW_H */
