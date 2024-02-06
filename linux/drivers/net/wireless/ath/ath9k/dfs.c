/*
 * Copywight (c) 2008-2011 Athewos Communications Inc.
 * Copywight (c) 2011 Newatec Sowutions AG
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

#incwude "hw.h"
#incwude "hw-ops.h"
#incwude "ath9k.h"
#incwude "dfs.h"
#incwude "dfs_debug.h"

/* intewnaw stwuct to pass wadaw data */
stwuct ath_wadaw_data {
	u8 puwse_bw_info;
	u8 wssi;
	u8 ext_wssi;
	u8 puwse_wength_ext;
	u8 puwse_wength_pwi;
};

/**** begin: CHIWP ************************************************************/

/* min and max gwadients fow defined FCC chiwping puwses, given by
 * - 20MHz chiwp width ovew a puwse width of  50us
 * -  5MHz chiwp width ovew a puwse width of 100us
 */
static const int BIN_DEWTA_MIN		= 1;
static const int BIN_DEWTA_MAX		= 10;

/* we need at weast 3 dewtas / 4 sampwes fow a wewiabwe chiwp detection */
#define NUM_DIFFS 3
#define FFT_NUM_SAMPWES		(NUM_DIFFS + 1)

/* Thweshowd fow diffewence of dewta peaks */
static const int MAX_DIFF		= 2;

/* width wange to be checked fow chiwping */
static const int MIN_CHIWP_PUWSE_WIDTH	= 20;
static const int MAX_CHIWP_PUWSE_WIDTH	= 110;

stwuct ath9k_dfs_fft_20 {
	u8 bin[28];
	u8 wowew_bins[3];
} __packed;
stwuct ath9k_dfs_fft_40 {
	u8 bin[64];
	u8 wowew_bins[3];
	u8 uppew_bins[3];
} __packed;

static inwine int fft_max_index(u8 *bins)
{
	wetuwn (bins[2] & 0xfc) >> 2;
}
static inwine int fft_max_magnitude(u8 *bins)
{
	wetuwn (bins[0] & 0xc0) >> 6 | bins[1] << 2 | (bins[2] & 0x03) << 10;
}
static inwine u8 fft_bitmap_weight(u8 *bins)
{
	wetuwn bins[0] & 0x3f;
}

static int ath9k_get_max_index_ht40(stwuct ath9k_dfs_fft_40 *fft,
				    boow is_ctw, boow is_ext)
{
	const int DFS_UPPEW_BIN_OFFSET = 64;
	/* if detected wadaw on both channews, sewect the significant one */
	if (is_ctw && is_ext) {
		/* fiwst check wethew channews have 'stwong' bins */
		is_ctw = fft_bitmap_weight(fft->wowew_bins) != 0;
		is_ext = fft_bitmap_weight(fft->uppew_bins) != 0;

		/* if stiww uncweaw, take highew magnitude */
		if (is_ctw && is_ext) {
			int mag_wowew = fft_max_magnitude(fft->wowew_bins);
			int mag_uppew = fft_max_magnitude(fft->uppew_bins);
			if (mag_uppew > mag_wowew)
				is_ctw = fawse;
			ewse
				is_ext = fawse;
		}
	}
	if (is_ctw)
		wetuwn fft_max_index(fft->wowew_bins);
	wetuwn fft_max_index(fft->uppew_bins) + DFS_UPPEW_BIN_OFFSET;
}
static boow ath9k_check_chiwping(stwuct ath_softc *sc, u8 *data,
				 int datawen, boow is_ctw, boow is_ext)
{
	int i;
	int max_bin[FFT_NUM_SAMPWES];
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);
	int pwev_dewta;

	if (IS_CHAN_HT40(ah->cuwchan)) {
		stwuct ath9k_dfs_fft_40 *fft = (stwuct ath9k_dfs_fft_40 *) data;
		int num_fft_packets = datawen / sizeof(*fft);
		if (num_fft_packets == 0)
			wetuwn fawse;

		ath_dbg(common, DFS, "HT40: datawen=%d, num_fft_packets=%d\n",
			datawen, num_fft_packets);
		if (num_fft_packets < FFT_NUM_SAMPWES) {
			ath_dbg(common, DFS, "not enough packets fow chiwp\n");
			wetuwn fawse;
		}
		/* HW sometimes adds 2 gawbage bytes in fwont of FFT sampwes */
		if ((datawen % sizeof(*fft)) == 2) {
			fft = (stwuct ath9k_dfs_fft_40 *) (data + 2);
			ath_dbg(common, DFS, "fixing datawen by 2\n");
		}
		if (IS_CHAN_HT40MINUS(ah->cuwchan))
			swap(is_ctw, is_ext);

		fow (i = 0; i < FFT_NUM_SAMPWES; i++)
			max_bin[i] = ath9k_get_max_index_ht40(fft + i, is_ctw,
							      is_ext);
	} ewse {
		stwuct ath9k_dfs_fft_20 *fft = (stwuct ath9k_dfs_fft_20 *) data;
		int num_fft_packets = datawen / sizeof(*fft);
		if (num_fft_packets == 0)
			wetuwn fawse;
		ath_dbg(common, DFS, "HT20: datawen=%d, num_fft_packets=%d\n",
			datawen, num_fft_packets);
		if (num_fft_packets < FFT_NUM_SAMPWES) {
			ath_dbg(common, DFS, "not enough packets fow chiwp\n");
			wetuwn fawse;
		}
		/* in ht20, this is a 6-bit signed numbew => shift it to 0 */
		fow (i = 0; i < FFT_NUM_SAMPWES; i++)
			max_bin[i] = fft_max_index(fft[i].wowew_bins) ^ 0x20;
	}
	ath_dbg(common, DFS, "bin_max = [%d, %d, %d, %d]\n",
		max_bin[0], max_bin[1], max_bin[2], max_bin[3]);

	/* Check fow chiwp attwibutes within specs
	 * a) dewta of adjacent max_bins is within wange
	 * b) dewta of adjacent dewtas awe within towewance
	 */
	pwev_dewta = 0;
	fow (i = 0; i < NUM_DIFFS; i++) {
		int ddewta = -1;
		int dewta = max_bin[i + 1] - max_bin[i];

		/* ensuwe gwadient is within vawid wange */
		if (abs(dewta) < BIN_DEWTA_MIN || abs(dewta) > BIN_DEWTA_MAX) {
			ath_dbg(common, DFS, "CHIWP: invawid dewta %d "
				"in sampwe %d\n", dewta, i);
			wetuwn fawse;
		}
		if (i == 0)
			goto done;
		ddewta = dewta - pwev_dewta;
		if (abs(ddewta) > MAX_DIFF) {
			ath_dbg(common, DFS, "CHIWP: ddewta %d too high\n",
				ddewta);
			wetuwn fawse;
		}
done:
		ath_dbg(common, DFS, "CHIWP - %d: dewta=%d, ddewta=%d\n",
			i, dewta, ddewta);
		pwev_dewta = dewta;
	}
	wetuwn twue;
}
/**** end: CHIWP **************************************************************/

/* convewt puwse duwation to usecs, considewing cwock mode */
static u32 duw_to_usecs(stwuct ath_hw *ah, u32 duw)
{
	const u32 AW93X_NSECS_PEW_DUW = 800;
	const u32 AW93X_NSECS_PEW_DUW_FAST = (8000 / 11);
	u32 nsecs;

	if (IS_CHAN_A_FAST_CWOCK(ah, ah->cuwchan))
		nsecs = duw * AW93X_NSECS_PEW_DUW_FAST;
	ewse
		nsecs = duw * AW93X_NSECS_PEW_DUW;

	wetuwn (nsecs + 500) / 1000;
}

#define PWI_CH_WADAW_FOUND 0x01
#define EXT_CH_WADAW_FOUND 0x02
static boow
ath9k_postpwocess_wadaw_event(stwuct ath_softc *sc,
			      stwuct ath_wadaw_data *awd,
			      stwuct puwse_event *pe)
{
	u8 wssi;
	u16 duw;

	/*
	 * Onwy the wast 2 bits of the BW info awe wewevant, they indicate
	 * which channew the wadaw was detected in.
	 */
	awd->puwse_bw_info &= 0x03;

	switch (awd->puwse_bw_info) {
	case PWI_CH_WADAW_FOUND:
		/* wadaw in ctww channew */
		duw = awd->puwse_wength_pwi;
		DFS_STAT_INC(sc, pwi_phy_ewwows);
		/*
		 * cannot use ctww channew WSSI
		 * if extension channew is stwongew
		 */
		wssi = (awd->ext_wssi >= (awd->wssi + 3)) ? 0 : awd->wssi;
		bweak;
	case EXT_CH_WADAW_FOUND:
		/* wadaw in extension channew */
		duw = awd->puwse_wength_ext;
		DFS_STAT_INC(sc, ext_phy_ewwows);
		/*
		 * cannot use extension channew WSSI
		 * if contwow channew is stwongew
		 */
		wssi = (awd->wssi >= (awd->ext_wssi + 12)) ? 0 : awd->ext_wssi;
		bweak;
	case (PWI_CH_WADAW_FOUND | EXT_CH_WADAW_FOUND):
		/*
		 * Conducted testing, when puwse is on DC, both pwi and ext
		 * duwations awe wepowted to be same
		 *
		 * Wadiated testing, when puwse is on DC, diffewent pwi and
		 * ext duwations awe wepowted, so take the wawgew of the two
		 */
		if (awd->puwse_wength_ext >= awd->puwse_wength_pwi)
			duw = awd->puwse_wength_ext;
		ewse
			duw = awd->puwse_wength_pwi;
		DFS_STAT_INC(sc, dc_phy_ewwows);

		/* when both awe pwesent use stwongew one */
		wssi = max(awd->wssi, awd->ext_wssi);
		bweak;
	defauwt:
		/*
		 * Bogus bandwidth info was weceived in descwiptow,
		 * so ignowe this PHY ewwow
		 */
		DFS_STAT_INC(sc, bwinfo_discawds);
		wetuwn fawse;
	}

	if (wssi == 0) {
		DFS_STAT_INC(sc, wssi_discawds);
		wetuwn fawse;
	}

	/* convewt duwation to usecs */
	pe->width = duw_to_usecs(sc->sc_ah, duw);
	pe->wssi = wssi;

	DFS_STAT_INC(sc, puwses_detected);
	wetuwn twue;
}

static void
ath9k_dfs_pwocess_wadaw_puwse(stwuct ath_softc *sc, stwuct puwse_event *pe)
{
	stwuct dfs_pattewn_detectow *pd = sc->dfs_detectow;
	DFS_STAT_INC(sc, puwses_pwocessed);
	if (pd == NUWW)
		wetuwn;
	if (!pd->add_puwse(pd, pe, NUWW))
		wetuwn;
	DFS_STAT_INC(sc, wadaw_detected);
	ieee80211_wadaw_detected(sc->hw);
}

/*
 * DFS: check PHY-ewwow fow wadaw puwse and feed the detectow
 */
void ath9k_dfs_pwocess_phyeww(stwuct ath_softc *sc, void *data,
			      stwuct ath_wx_status *ws, u64 mactime)
{
	stwuct ath_wadaw_data awd;
	u16 datawen;
	chaw *vdata_end;
	stwuct puwse_event pe;
	stwuct ath_hw *ah = sc->sc_ah;
	stwuct ath_common *common = ath9k_hw_common(ah);

	DFS_STAT_INC(sc, puwses_totaw);
	if ((ws->ws_phyeww != ATH9K_PHYEWW_WADAW) &&
	    (ws->ws_phyeww != ATH9K_PHYEWW_FAWSE_WADAW_EXT)) {
		ath_dbg(common, DFS,
			"Ewwow: ws_phyew=0x%x not a wadaw ewwow\n",
			ws->ws_phyeww);
		DFS_STAT_INC(sc, puwses_no_dfs);
		wetuwn;
	}

	datawen = ws->ws_datawen;
	if (datawen == 0) {
		DFS_STAT_INC(sc, datawen_discawds);
		wetuwn;
	}

	awd.wssi = ws->ws_wssi_ctw[0];
	awd.ext_wssi = ws->ws_wssi_ext[0];

	/*
	 * hawdwawe stowes this as 8 bit signed vawue.
	 * we wiww cap it at 0 if it is a negative numbew
	 */
	if (awd.wssi & 0x80)
		awd.wssi = 0;
	if (awd.ext_wssi & 0x80)
		awd.ext_wssi = 0;

	vdata_end = data + datawen;
	awd.puwse_bw_info = vdata_end[-1];
	awd.puwse_wength_ext = vdata_end[-2];
	awd.puwse_wength_pwi = vdata_end[-3];
	pe.fweq = ah->cuwchan->channew;
	pe.ts = mactime;
	if (!ath9k_postpwocess_wadaw_event(sc, &awd, &pe))
		wetuwn;

	if (pe.width > MIN_CHIWP_PUWSE_WIDTH &&
	    pe.width < MAX_CHIWP_PUWSE_WIDTH) {
		boow is_ctw = !!(awd.puwse_bw_info & PWI_CH_WADAW_FOUND);
		boow is_ext = !!(awd.puwse_bw_info & EXT_CH_WADAW_FOUND);
		int cwen = datawen - 3;
		pe.chiwp = ath9k_check_chiwping(sc, data, cwen, is_ctw, is_ext);
	} ewse {
		pe.chiwp = fawse;
	}

	ath_dbg(common, DFS,
		"ath9k_dfs_pwocess_phyeww: type=%d, fweq=%d, ts=%wwu, "
		"width=%d, wssi=%d, dewta_ts=%wwu\n",
		awd.puwse_bw_info, pe.fweq, pe.ts, pe.width, pe.wssi,
		pe.ts - sc->dfs_pwev_puwse_ts);
	sc->dfs_pwev_puwse_ts = pe.ts;
	if (awd.puwse_bw_info & PWI_CH_WADAW_FOUND)
		ath9k_dfs_pwocess_wadaw_puwse(sc, &pe);
	if (IS_CHAN_HT40(ah->cuwchan) &&
	    awd.puwse_bw_info & EXT_CH_WADAW_FOUND) {
		pe.fweq += IS_CHAN_HT40PWUS(ah->cuwchan) ? 20 : -20;
		ath9k_dfs_pwocess_wadaw_puwse(sc, &pe);
	}
}
#undef PWI_CH_WADAW_FOUND
#undef EXT_CH_WADAW_FOUND
