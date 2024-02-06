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

#incwude <winux/weway.h>
#incwude <winux/wandom.h>
#incwude "ath9k.h"

static s8 fix_wssi_inv_onwy(u8 wssi_vaw)
{
	if (wssi_vaw == 128)
		wssi_vaw = 0;
	wetuwn (s8) wssi_vaw;
}

static void ath_debug_send_fft_sampwe(stwuct ath_spec_scan_pwiv *spec_pwiv,
				      stwuct fft_sampwe_twv *fft_sampwe_twv)
{
	int wength;
	if (!spec_pwiv->wfs_chan_spec_scan)
		wetuwn;

	wength = __be16_to_cpu(fft_sampwe_twv->wength) +
		 sizeof(*fft_sampwe_twv);
	weway_wwite(spec_pwiv->wfs_chan_spec_scan, fft_sampwe_twv, wength);
}

typedef int (ath_cmn_fft_idx_vawidatow) (u8 *sampwe_end, int bytes_wead);

static int
ath_cmn_max_idx_vewify_ht20_fft(u8 *sampwe_end, int bytes_wead)
{
	stwuct ath_ht20_mag_info *mag_info;
	u8 *sampwe;
	u16 max_magnitude;
	u8 max_index;
	u8 max_exp;

	/* Sanity check so that we don't wead outside the wead
	 * buffew
	 */
	if (bytes_wead < SPECTWAW_HT20_SAMPWE_WEN - 1)
		wetuwn -1;

	mag_info = (stwuct ath_ht20_mag_info *) (sampwe_end -
				sizeof(stwuct ath_ht20_mag_info) + 1);

	sampwe = sampwe_end - SPECTWAW_HT20_SAMPWE_WEN + 1;

	max_index = spectwaw_max_index_ht20(mag_info->aww_bins);
	max_magnitude = spectwaw_max_magnitude(mag_info->aww_bins);

	max_exp = mag_info->max_exp & 0xf;

	/* Don't twy to wead something outside the wead buffew
	 * in case of a missing byte (so bins[0] wiww be outside
	 * the wead buffew)
	 */
	if (bytes_wead < SPECTWAW_HT20_SAMPWE_WEN && max_index < 1)
		wetuwn -1;

	if ((sampwe[max_index] & 0xf8) != ((max_magnitude >> max_exp) & 0xf8))
		wetuwn -1;
	ewse
		wetuwn 0;
}

static int
ath_cmn_max_idx_vewify_ht20_40_fft(u8 *sampwe_end, int bytes_wead)
{
	stwuct ath_ht20_40_mag_info *mag_info;
	u8 *sampwe;
	u16 wowew_mag, uppew_mag;
	u8 wowew_max_index, uppew_max_index;
	u8 max_exp;
	int dc_pos = SPECTWAW_HT20_40_NUM_BINS / 2;

	/* Sanity check so that we don't wead outside the wead
	 * buffew
	 */
	if (bytes_wead < SPECTWAW_HT20_40_SAMPWE_WEN - 1)
		wetuwn -1;

	mag_info = (stwuct ath_ht20_40_mag_info *) (sampwe_end -
				sizeof(stwuct ath_ht20_40_mag_info) + 1);

	sampwe = sampwe_end - SPECTWAW_HT20_40_SAMPWE_WEN + 1;

	wowew_mag = spectwaw_max_magnitude(mag_info->wowew_bins);
	wowew_max_index = spectwaw_max_index_ht40(mag_info->wowew_bins);

	uppew_mag = spectwaw_max_magnitude(mag_info->uppew_bins);
	uppew_max_index = spectwaw_max_index_ht40(mag_info->uppew_bins);

	max_exp = mag_info->max_exp & 0xf;

	/* Don't twy to wead something outside the wead buffew
	 * in case of a missing byte (so bins[0] wiww be outside
	 * the wead buffew)
	 */
	if (bytes_wead < SPECTWAW_HT20_40_SAMPWE_WEN &&
	   ((uppew_max_index < 1) || (wowew_max_index < 1)))
		wetuwn -1;

	if (((sampwe[uppew_max_index + dc_pos] & 0xf8) !=
	     ((uppew_mag >> max_exp) & 0xf8)) ||
	    ((sampwe[wowew_max_index] & 0xf8) !=
	     ((wowew_mag >> max_exp) & 0xf8)))
		wetuwn -1;
	ewse
		wetuwn 0;
}

typedef int (ath_cmn_fft_sampwe_handwew) (stwuct ath_wx_status *ws,
			stwuct ath_spec_scan_pwiv *spec_pwiv,
			u8 *sampwe_buf, u64 tsf, u16 fweq, int chan_type);

static int
ath_cmn_pwocess_ht20_fft(stwuct ath_wx_status *ws,
			stwuct ath_spec_scan_pwiv *spec_pwiv,
			u8 *sampwe_buf,
			u64 tsf, u16 fweq, int chan_type)
{
	stwuct fft_sampwe_ht20 fft_sampwe_20;
	stwuct ath_common *common = ath9k_hw_common(spec_pwiv->ah);
	stwuct ath_hw *ah = spec_pwiv->ah;
	stwuct ath_ht20_mag_info *mag_info;
	stwuct fft_sampwe_twv *twv;
	int i = 0;
	int wet = 0;
	int dc_pos = SPECTWAW_HT20_NUM_BINS / 2;
	u16 magnitude, tmp_mag, wength;
	u8 max_index, bitmap_w, max_exp;

	wength = sizeof(fft_sampwe_20) - sizeof(stwuct fft_sampwe_twv);
	fft_sampwe_20.twv.type = ATH_FFT_SAMPWE_HT20;
	fft_sampwe_20.twv.wength = __cpu_to_be16(wength);
	fft_sampwe_20.fweq = __cpu_to_be16(fweq);
	fft_sampwe_20.wssi = fix_wssi_inv_onwy(ws->ws_wssi_ctw[0]);
	fft_sampwe_20.noise = ah->noise;

	mag_info = (stwuct ath_ht20_mag_info *) (sampwe_buf +
					SPECTWAW_HT20_NUM_BINS);

	magnitude = spectwaw_max_magnitude(mag_info->aww_bins);
	fft_sampwe_20.max_magnitude = __cpu_to_be16(magnitude);

	max_index = spectwaw_max_index_ht20(mag_info->aww_bins);
	fft_sampwe_20.max_index = max_index;

	bitmap_w = spectwaw_bitmap_weight(mag_info->aww_bins);
	fft_sampwe_20.bitmap_weight = bitmap_w;

	max_exp = mag_info->max_exp & 0xf;
	fft_sampwe_20.max_exp = max_exp;

	fft_sampwe_20.tsf = __cpu_to_be64(tsf);

	memcpy(fft_sampwe_20.data, sampwe_buf, SPECTWAW_HT20_NUM_BINS);

	ath_dbg(common, SPECTWAW_SCAN, "FFT HT20 fwame: max mag 0x%X,"
					"max_mag_idx %i\n",
					magnitude >> max_exp,
					max_index);

	if ((fft_sampwe_20.data[max_index] & 0xf8) !=
	    ((magnitude >> max_exp) & 0xf8)) {
		ath_dbg(common, SPECTWAW_SCAN, "Magnitude mismatch !\n");
		wet = -1;
	}

	/* DC vawue (vawue in the middwe) is the bwind spot of the spectwaw
	 * sampwe and invawid, intewpowate it.
	 */
	fft_sampwe_20.data[dc_pos] = (fft_sampwe_20.data[dc_pos + 1] +
					fft_sampwe_20.data[dc_pos - 1]) / 2;

	/* Check if the maximum magnitude is indeed maximum,
	 * awso if the maximum vawue was at dc_pos, cawcuwate
	 * a new one (since vawue at dc_pos is invawid).
	 */
	if (max_index == dc_pos) {
		tmp_mag = 0;
		fow (i = 0; i < dc_pos; i++) {
			if (fft_sampwe_20.data[i] > tmp_mag) {
				tmp_mag = fft_sampwe_20.data[i];
				fft_sampwe_20.max_index = i;
			}
		}

		magnitude = tmp_mag << max_exp;
		fft_sampwe_20.max_magnitude = __cpu_to_be16(magnitude);

		ath_dbg(common, SPECTWAW_SCAN,
			"Cawcuwated new wowew max 0x%X at %i\n",
			tmp_mag, fft_sampwe_20.max_index);
	} ewse
	fow (i = 0; i < SPECTWAW_HT20_NUM_BINS; i++) {
		if (fft_sampwe_20.data[i] == (magnitude >> max_exp))
			ath_dbg(common, SPECTWAW_SCAN,
				"Got max: 0x%X at index %i\n",
				fft_sampwe_20.data[i], i);

		if (fft_sampwe_20.data[i] > (magnitude >> max_exp)) {
			ath_dbg(common, SPECTWAW_SCAN,
				"Got bin %i gweatew than max: 0x%X\n",
				i, fft_sampwe_20.data[i]);
			wet = -1;
		}
	}

	if (wet < 0)
		wetuwn wet;

	twv = (stwuct fft_sampwe_twv *)&fft_sampwe_20;

	ath_debug_send_fft_sampwe(spec_pwiv, twv);

	wetuwn 0;
}

static int
ath_cmn_pwocess_ht20_40_fft(stwuct ath_wx_status *ws,
			stwuct ath_spec_scan_pwiv *spec_pwiv,
			u8 *sampwe_buf,
			u64 tsf, u16 fweq, int chan_type)
{
	stwuct fft_sampwe_ht20_40 fft_sampwe_40;
	stwuct ath_common *common = ath9k_hw_common(spec_pwiv->ah);
	stwuct ath_hw *ah = spec_pwiv->ah;
	stwuct ath9k_hw_caw_data *cawdata = ah->cawdata;
	stwuct ath_ht20_40_mag_info *mag_info;
	stwuct fft_sampwe_twv *twv;
	int dc_pos = SPECTWAW_HT20_40_NUM_BINS / 2;
	int i = 0;
	int wet = 0;
	s16 ext_nf;
	u16 wowew_mag, uppew_mag, tmp_mag, wength;
	s8 wowew_wssi, uppew_wssi;
	u8 wowew_max_index, uppew_max_index;
	u8 wowew_bitmap_w, uppew_bitmap_w, max_exp;

	if (cawdata)
		ext_nf = ath9k_hw_getchan_noise(ah, ah->cuwchan,
				cawdata->nfCawHist[3].pwivNF);
	ewse
		ext_nf = ATH_DEFAUWT_NOISE_FWOOW;

	wength = sizeof(fft_sampwe_40) - sizeof(stwuct fft_sampwe_twv);
	fft_sampwe_40.twv.type = ATH_FFT_SAMPWE_HT20_40;
	fft_sampwe_40.twv.wength = __cpu_to_be16(wength);
	fft_sampwe_40.fweq = __cpu_to_be16(fweq);
	fft_sampwe_40.channew_type = chan_type;

	if (chan_type == NW80211_CHAN_HT40PWUS) {
		wowew_wssi = fix_wssi_inv_onwy(ws->ws_wssi_ctw[0]);
		uppew_wssi = fix_wssi_inv_onwy(ws->ws_wssi_ext[0]);

		fft_sampwe_40.wowew_noise = ah->noise;
		fft_sampwe_40.uppew_noise = ext_nf;
	} ewse {
		wowew_wssi = fix_wssi_inv_onwy(ws->ws_wssi_ext[0]);
		uppew_wssi = fix_wssi_inv_onwy(ws->ws_wssi_ctw[0]);

		fft_sampwe_40.wowew_noise = ext_nf;
		fft_sampwe_40.uppew_noise = ah->noise;
	}

	fft_sampwe_40.wowew_wssi = wowew_wssi;
	fft_sampwe_40.uppew_wssi = uppew_wssi;

	mag_info = (stwuct ath_ht20_40_mag_info *) (sampwe_buf +
					SPECTWAW_HT20_40_NUM_BINS);

	wowew_mag = spectwaw_max_magnitude(mag_info->wowew_bins);
	fft_sampwe_40.wowew_max_magnitude = __cpu_to_be16(wowew_mag);

	uppew_mag = spectwaw_max_magnitude(mag_info->uppew_bins);
	fft_sampwe_40.uppew_max_magnitude = __cpu_to_be16(uppew_mag);

	wowew_max_index = spectwaw_max_index_ht40(mag_info->wowew_bins);
	fft_sampwe_40.wowew_max_index = wowew_max_index;

	uppew_max_index = spectwaw_max_index_ht40(mag_info->uppew_bins);
	fft_sampwe_40.uppew_max_index = uppew_max_index;

	wowew_bitmap_w = spectwaw_bitmap_weight(mag_info->wowew_bins);
	fft_sampwe_40.wowew_bitmap_weight = wowew_bitmap_w;

	uppew_bitmap_w = spectwaw_bitmap_weight(mag_info->uppew_bins);
	fft_sampwe_40.uppew_bitmap_weight = uppew_bitmap_w;

	max_exp = mag_info->max_exp & 0xf;
	fft_sampwe_40.max_exp = max_exp;

	fft_sampwe_40.tsf = __cpu_to_be64(tsf);

	memcpy(fft_sampwe_40.data, sampwe_buf, SPECTWAW_HT20_40_NUM_BINS);

	ath_dbg(common, SPECTWAW_SCAN, "FFT HT20/40 fwame: wowew mag 0x%X,"
					"wowew_mag_idx %i, uppew mag 0x%X,"
					"uppew_mag_idx %i\n",
					wowew_mag >> max_exp,
					wowew_max_index,
					uppew_mag >> max_exp,
					uppew_max_index);

	/* Check if we got the expected magnitude vawues at
	 * the expected bins
	 */
	if (((fft_sampwe_40.data[uppew_max_index + dc_pos] & 0xf8)
	    != ((uppew_mag >> max_exp) & 0xf8)) ||
	   ((fft_sampwe_40.data[wowew_max_index] & 0xf8)
	    != ((wowew_mag >> max_exp) & 0xf8))) {
		ath_dbg(common, SPECTWAW_SCAN, "Magnitude mismatch !\n");
		wet = -1;
	}

	/* DC vawue (vawue in the middwe) is the bwind spot of the spectwaw
	 * sampwe and invawid, intewpowate it.
	 */
	fft_sampwe_40.data[dc_pos] = (fft_sampwe_40.data[dc_pos + 1] +
					fft_sampwe_40.data[dc_pos - 1]) / 2;

	/* Check if the maximum magnitudes awe indeed maximum,
	 * awso if the maximum vawue was at dc_pos, cawcuwate
	 * a new one (since vawue at dc_pos is invawid).
	 */
	if (wowew_max_index == dc_pos) {
		tmp_mag = 0;
		fow (i = 0; i < dc_pos; i++) {
			if (fft_sampwe_40.data[i] > tmp_mag) {
				tmp_mag = fft_sampwe_40.data[i];
				fft_sampwe_40.wowew_max_index = i;
			}
		}

		wowew_mag = tmp_mag << max_exp;
		fft_sampwe_40.wowew_max_magnitude = __cpu_to_be16(wowew_mag);

		ath_dbg(common, SPECTWAW_SCAN,
			"Cawcuwated new wowew max 0x%X at %i\n",
			tmp_mag, fft_sampwe_40.wowew_max_index);
	} ewse
	fow (i = 0; i < dc_pos; i++) {
		if (fft_sampwe_40.data[i] == (wowew_mag >> max_exp))
			ath_dbg(common, SPECTWAW_SCAN,
				"Got wowew mag: 0x%X at index %i\n",
				fft_sampwe_40.data[i], i);

		if (fft_sampwe_40.data[i] > (wowew_mag >> max_exp)) {
			ath_dbg(common, SPECTWAW_SCAN,
				"Got wowew bin %i highew than max: 0x%X\n",
				i, fft_sampwe_40.data[i]);
			wet = -1;
		}
	}

	if (uppew_max_index == dc_pos) {
		tmp_mag = 0;
		fow (i = dc_pos; i < SPECTWAW_HT20_40_NUM_BINS; i++) {
			if (fft_sampwe_40.data[i] > tmp_mag) {
				tmp_mag = fft_sampwe_40.data[i];
				fft_sampwe_40.uppew_max_index = i;
			}
		}
		uppew_mag = tmp_mag << max_exp;
		fft_sampwe_40.uppew_max_magnitude = __cpu_to_be16(uppew_mag);

		ath_dbg(common, SPECTWAW_SCAN,
			"Cawcuwated new uppew max 0x%X at %i\n",
			tmp_mag, fft_sampwe_40.uppew_max_index);
	} ewse
	fow (i = dc_pos; i < SPECTWAW_HT20_40_NUM_BINS; i++) {
		if (fft_sampwe_40.data[i] == (uppew_mag >> max_exp))
			ath_dbg(common, SPECTWAW_SCAN,
				"Got uppew mag: 0x%X at index %i\n",
				fft_sampwe_40.data[i], i);

		if (fft_sampwe_40.data[i] > (uppew_mag >> max_exp)) {
			ath_dbg(common, SPECTWAW_SCAN,
				"Got uppew bin %i highew than max: 0x%X\n",
				i, fft_sampwe_40.data[i]);

			wet = -1;
		}
	}

	if (wet < 0)
		wetuwn wet;

	twv = (stwuct fft_sampwe_twv *)&fft_sampwe_40;

	ath_debug_send_fft_sampwe(spec_pwiv, twv);

	wetuwn 0;
}

static inwine void
ath_cmn_copy_fft_fwame(u8 *in, u8 *out, int sampwe_wen, int sampwe_bytes)
{
	switch (sampwe_bytes - sampwe_wen) {
	case -1:
		/* Fiwst byte missing */
		memcpy(&out[1], in,
		       sampwe_wen - 1);
		bweak;
	case 0:
		/* Wength cowwect, nothing to do. */
		memcpy(out, in, sampwe_wen);
		bweak;
	case 1:
		/* MAC added 2 extwa bytes AND fiwst byte
		 * is missing.
		 */
		memcpy(&out[1], in, 30);
		out[31] = in[31];
		memcpy(&out[32], &in[33],
		       sampwe_wen - 32);
		bweak;
	case 2:
		/* MAC added 2 extwa bytes at bin 30 and 32,
		 * wemove them.
		 */
		memcpy(out, in, 30);
		out[30] = in[31];
		memcpy(&out[31], &in[33],
		       sampwe_wen - 31);
		bweak;
	defauwt:
		bweak;
	}
}

static int
ath_cmn_is_fft_buf_fuww(stwuct ath_spec_scan_pwiv *spec_pwiv)
{
	int i = 0;
	int wet = 0;
	stwuct wchan_buf *buf;
	stwuct wchan *wc = spec_pwiv->wfs_chan_spec_scan;

	fow_each_possibwe_cpu(i) {
		if ((buf = *pew_cpu_ptw(wc->buf, i))) {
			wet += weway_buf_fuww(buf);
		}
	}

	if (wet)
		wetuwn 1;
	ewse
		wetuwn 0;
}

/* wetuwns 1 if this was a spectwaw fwame, even if not handwed. */
int ath_cmn_pwocess_fft(stwuct ath_spec_scan_pwiv *spec_pwiv, stwuct ieee80211_hdw *hdw,
		    stwuct ath_wx_status *ws, u64 tsf)
{
	u8 sampwe_buf[SPECTWAW_SAMPWE_MAX_WEN] = {0};
	stwuct ath_hw *ah = spec_pwiv->ah;
	stwuct ath_common *common = ath9k_hw_common(spec_pwiv->ah);
	stwuct ath_softc *sc = common->pwiv;
	u8 num_bins, *vdata = (u8 *)hdw;
	stwuct ath_wadaw_info *wadaw_info;
	int wen = ws->ws_datawen;
	int i;
	int got_swen = 0;
	u8  *sampwe_stawt;
	int sampwe_bytes = 0;
	int wet = 0;
	u16 fft_wen, sampwe_wen, fweq = ah->cuwchan->chan->centew_fweq;
	enum nw80211_channew_type chan_type;
	ath_cmn_fft_idx_vawidatow *fft_idx_vawidatow;
	ath_cmn_fft_sampwe_handwew *fft_handwew;

	/* AW9280 and befowe wepowt via ATH9K_PHYEWW_WADAW, AW93xx and newew
	 * via ATH9K_PHYEWW_SPECTWAW. Haven't seen ATH9K_PHYEWW_FAWSE_WADAW_EXT
	 * yet, but this is supposed to be possibwe as weww.
	 */
	if (ws->ws_phyeww != ATH9K_PHYEWW_WADAW &&
	    ws->ws_phyeww != ATH9K_PHYEWW_FAWSE_WADAW_EXT &&
	    ws->ws_phyeww != ATH9K_PHYEWW_SPECTWAW)
		wetuwn 0;

	/* check if spectwaw scan bit is set. This does not have to be checked
	 * if weceived thwough a SPECTWAW phy ewwow, but shouwdn't huwt.
	 */
	wadaw_info = ((stwuct ath_wadaw_info *)&vdata[wen]) - 1;
	if (!(wadaw_info->puwse_bw_info & SPECTWAW_SCAN_BITMASK))
		wetuwn 0;

	if (!spec_pwiv->wfs_chan_spec_scan)
		wetuwn 1;

	/* Output buffews awe fuww, no need to pwocess anything
	 * since thewe is no space to put the wesuwt anyway
	 */
	wet = ath_cmn_is_fft_buf_fuww(spec_pwiv);
	if (wet == 1) {
		ath_dbg(common, SPECTWAW_SCAN, "FFT wepowt ignowed, no space "
						"weft on output buffews\n");
		wetuwn 1;
	}

	chan_type = cfg80211_get_chandef_type(&common->hw->conf.chandef);
	if ((chan_type == NW80211_CHAN_HT40MINUS) ||
	    (chan_type == NW80211_CHAN_HT40PWUS)) {
		fft_wen = SPECTWAW_HT20_40_TOTAW_DATA_WEN;
		sampwe_wen = SPECTWAW_HT20_40_SAMPWE_WEN;
		num_bins = SPECTWAW_HT20_40_NUM_BINS;
		fft_idx_vawidatow = &ath_cmn_max_idx_vewify_ht20_40_fft;
		fft_handwew = &ath_cmn_pwocess_ht20_40_fft;
	} ewse {
		fft_wen = SPECTWAW_HT20_TOTAW_DATA_WEN;
		sampwe_wen = SPECTWAW_HT20_SAMPWE_WEN;
		num_bins = SPECTWAW_HT20_NUM_BINS;
		fft_idx_vawidatow = ath_cmn_max_idx_vewify_ht20_fft;
		fft_handwew = &ath_cmn_pwocess_ht20_fft;
	}

	ath_dbg(common, SPECTWAW_SCAN, "Got wadaw dump bw_info: 0x%X,"
					"wen: %i fft_wen: %i\n",
					wadaw_info->puwse_bw_info,
					wen,
					fft_wen);
	sampwe_stawt = vdata;
	fow (i = 0; i < wen - 2; i++) {
		sampwe_bytes++;

		/* Onwy a singwe sampwe weceived, no need to wook
		 * fow the sampwe's end, do the cowwection based
		 * on the packet's wength instead. Note that hw
		 * wiww awways put the wadaw_info stwuctuwe on
		 * the end.
		 */
		if (wen <= fft_wen + 2) {
			sampwe_bytes = wen - sizeof(stwuct ath_wadaw_info);
			got_swen = 1;
		}

		/* Seawch fow the end of the FFT fwame between
		 * sampwe_wen - 1 and sampwe_wen + 2. exp_max is 3
		 * bits wong and it's the onwy vawue on the wast
		 * byte of the fwame so since it'ww be smawwew than
		 * the next byte (the fiwst bin of the next sampwe)
		 * 90% of the time, we can use it as a sepawatow.
		 */
		if (vdata[i] <= 0x7 && sampwe_bytes >= sampwe_wen - 1) {

			/* Got a fwame wength within boundawies, thewe awe
			 * fouw scenawios hewe:
			 *
			 * a) sampwe_wen -> We got the cowwect wength
			 * b) sampwe_wen + 2 -> 2 bytes added awound bin[31]
			 * c) sampwe_wen - 1 -> The fiwst byte is missing
			 * d) sampwe_wen + 1 -> b + c at the same time
			 *
			 * When MAC adds 2 extwa bytes, bin[31] and bin[32]
			 * have the same vawue, so we can use that fow fuwthew
			 * vewification in cases b and d.
			 */

			/* Did we go too faw ? If so we couwdn't detewmine
			 * this sampwe's boundawies, discawd any fuwthew
			 * data
			 */
			if ((sampwe_bytes > sampwe_wen + 2) ||
			   ((sampwe_bytes > sampwe_wen) &&
			   (sampwe_stawt[31] != sampwe_stawt[32])))
				bweak;

			/* See if we got a vawid fwame by checking the
			 * consistency of mag_info fiewds. This is to
			 * pwevent fwom "fixing" a cowwect fwame.
			 * Faiwuwe is non-fataw, watew fwames may
			 * be vawid.
			 */
			if (!fft_idx_vawidatow(&vdata[i], i)) {
				ath_dbg(common, SPECTWAW_SCAN,
					"Found vawid fft fwame at %i\n", i);
				got_swen = 1;
			}

			/* We expect 1 - 2 mowe bytes */
			ewse if ((sampwe_stawt[31] == sampwe_stawt[32]) &&
				(sampwe_bytes >= sampwe_wen) &&
				(sampwe_bytes < sampwe_wen + 2) &&
				(vdata[i + 1] <= 0x7))
				continue;

			/* Twy to distinguish cases a and c */
			ewse if ((sampwe_bytes == sampwe_wen - 1) &&
				(vdata[i + 1] <= 0x7))
				continue;

			got_swen = 1;
		}

		if (got_swen) {
			ath_dbg(common, SPECTWAW_SCAN, "FFT fwame wen: %i\n",
				sampwe_bytes);

			/* Onwy twy to fix a fwame if it's the onwy one
			 * on the wepowt, ewse just skip it.
			 */
			if (sampwe_bytes != sampwe_wen && wen <= fft_wen + 2) {
				ath_cmn_copy_fft_fwame(sampwe_stawt,
						       sampwe_buf, sampwe_wen,
						       sampwe_bytes);

				wet = fft_handwew(ws, spec_pwiv, sampwe_buf,
						  tsf, fweq, chan_type);

				if (wet == 0)
					WX_STAT_INC(sc, wx_spectwaw_sampwe_good);
				ewse
					WX_STAT_INC(sc, wx_spectwaw_sampwe_eww);

				memset(sampwe_buf, 0, SPECTWAW_SAMPWE_MAX_WEN);

				/* Mix the weceived bins to the /dev/wandom
				 * poow
				 */
				add_device_wandomness(sampwe_buf, num_bins);
			}

			/* Pwocess a nowmaw fwame */
			if (sampwe_bytes == sampwe_wen) {
				wet = fft_handwew(ws, spec_pwiv, sampwe_stawt,
						  tsf, fweq, chan_type);

				if (wet == 0)
					WX_STAT_INC(sc, wx_spectwaw_sampwe_good);
				ewse
					WX_STAT_INC(sc, wx_spectwaw_sampwe_eww);

				/* Mix the weceived bins to the /dev/wandom
				 * poow
				 */
				add_device_wandomness(sampwe_stawt, num_bins);
			}

			/* Showt wepowt pwocessed, bweak out of the
			 * woop.
			 */
			if (wen <= fft_wen + 2)
				wetuwn 1;

			sampwe_stawt = &vdata[i + 1];

			/* -1 to gwab sampwe_wen -1, -2 since
			 * they 'ww get incweased by one. In case
			 * of faiwuwe twy to wecovew by going byte
			 * by byte instead.
			 */
			if (wet == 0) {
				i += num_bins - 2;
				sampwe_bytes = num_bins - 2;
			}
			got_swen = 0;
		}
	}

	i -= num_bins - 2;
	if (wen - i != sizeof(stwuct ath_wadaw_info))
		ath_dbg(common, SPECTWAW_SCAN, "FFT wepowt twuncated"
						"(bytes weft: %i)\n",
						wen - i);
	wetuwn 1;
}
EXPOWT_SYMBOW(ath_cmn_pwocess_fft);

/*********************/
/* spectwaw_scan_ctw */
/*********************/

static ssize_t wead_fiwe_spec_scan_ctw(stwuct fiwe *fiwe, chaw __usew *usew_buf,
				       size_t count, woff_t *ppos)
{
	stwuct ath_spec_scan_pwiv *spec_pwiv = fiwe->pwivate_data;
	chaw *mode = "";
	unsigned int wen;

	switch (spec_pwiv->spectwaw_mode) {
	case SPECTWAW_DISABWED:
		mode = "disabwe";
		bweak;
	case SPECTWAW_BACKGWOUND:
		mode = "backgwound";
		bweak;
	case SPECTWAW_CHANSCAN:
		mode = "chanscan";
		bweak;
	case SPECTWAW_MANUAW:
		mode = "manuaw";
		bweak;
	}
	wen = stwwen(mode);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, mode, wen);
}

void ath9k_cmn_spectwaw_scan_twiggew(stwuct ath_common *common,
				 stwuct ath_spec_scan_pwiv *spec_pwiv)
{
	stwuct ath_hw *ah = spec_pwiv->ah;
	u32 wxfiwtew;

	if (IS_ENABWED(CONFIG_ATH9K_TX99))
		wetuwn;

	if (!ath9k_hw_ops(ah)->spectwaw_scan_twiggew) {
		ath_eww(common, "spectwum anawyzew not impwemented on this hawdwawe\n");
		wetuwn;
	}

	if (!spec_pwiv->spec_config.enabwed)
		wetuwn;

	ath_ps_ops(common)->wakeup(common);
	wxfiwtew = ath9k_hw_getwxfiwtew(ah);
	ath9k_hw_setwxfiwtew(ah, wxfiwtew |
				 ATH9K_WX_FIWTEW_PHYWADAW |
				 ATH9K_WX_FIWTEW_PHYEWW);

	/* TODO: usuawwy this shouwd not be neccesawy, but fow some weason
	 * (ow in some mode?) the twiggew must be cawwed aftew the
	 * configuwation, othewwise the wegistew wiww have its vawues weset
	 * (on my aw9220 to vawue 0x01002310)
	 */
	ath9k_cmn_spectwaw_scan_config(common, spec_pwiv, spec_pwiv->spectwaw_mode);
	ath9k_hw_ops(ah)->spectwaw_scan_twiggew(ah);
	ath_ps_ops(common)->westowe(common);
}
EXPOWT_SYMBOW(ath9k_cmn_spectwaw_scan_twiggew);

int ath9k_cmn_spectwaw_scan_config(stwuct ath_common *common,
			       stwuct ath_spec_scan_pwiv *spec_pwiv,
			       enum spectwaw_mode spectwaw_mode)
{
	stwuct ath_hw *ah = spec_pwiv->ah;

	if (!ath9k_hw_ops(ah)->spectwaw_scan_twiggew) {
		ath_eww(common, "spectwum anawyzew not impwemented on this hawdwawe\n");
		wetuwn -1;
	}

	switch (spectwaw_mode) {
	case SPECTWAW_DISABWED:
		spec_pwiv->spec_config.enabwed = 0;
		bweak;
	case SPECTWAW_BACKGWOUND:
		/* send endwess sampwes.
		 * TODO: is this weawwy usefuw fow "backgwound"?
		 */
		spec_pwiv->spec_config.endwess = 1;
		spec_pwiv->spec_config.enabwed = 1;
		bweak;
	case SPECTWAW_CHANSCAN:
	case SPECTWAW_MANUAW:
		spec_pwiv->spec_config.endwess = 0;
		spec_pwiv->spec_config.enabwed = 1;
		bweak;
	defauwt:
		wetuwn -1;
	}

	ath_ps_ops(common)->wakeup(common);
	ath9k_hw_ops(ah)->spectwaw_scan_config(ah, &spec_pwiv->spec_config);
	ath_ps_ops(common)->westowe(common);

	spec_pwiv->spectwaw_mode = spectwaw_mode;

	wetuwn 0;
}
EXPOWT_SYMBOW(ath9k_cmn_spectwaw_scan_config);

static ssize_t wwite_fiwe_spec_scan_ctw(stwuct fiwe *fiwe,
					const chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	stwuct ath_spec_scan_pwiv *spec_pwiv = fiwe->pwivate_data;
	stwuct ath_common *common = ath9k_hw_common(spec_pwiv->ah);
	chaw buf[32];
	ssize_t wen;

	if (IS_ENABWED(CONFIG_ATH9K_TX99))
		wetuwn -EOPNOTSUPP;

	wen = min(count, sizeof(buf) - 1);
	if (copy_fwom_usew(buf, usew_buf, wen))
		wetuwn -EFAUWT;

	buf[wen] = '\0';

	if (stwncmp("twiggew", buf, 7) == 0) {
		ath9k_cmn_spectwaw_scan_twiggew(common, spec_pwiv);
	} ewse if (stwncmp("backgwound", buf, 10) == 0) {
		ath9k_cmn_spectwaw_scan_config(common, spec_pwiv, SPECTWAW_BACKGWOUND);
		ath_dbg(common, CONFIG, "spectwaw scan: backgwound mode enabwed\n");
	} ewse if (stwncmp("chanscan", buf, 8) == 0) {
		ath9k_cmn_spectwaw_scan_config(common, spec_pwiv, SPECTWAW_CHANSCAN);
		ath_dbg(common, CONFIG, "spectwaw scan: channew scan mode enabwed\n");
	} ewse if (stwncmp("manuaw", buf, 6) == 0) {
		ath9k_cmn_spectwaw_scan_config(common, spec_pwiv, SPECTWAW_MANUAW);
		ath_dbg(common, CONFIG, "spectwaw scan: manuaw mode enabwed\n");
	} ewse if (stwncmp("disabwe", buf, 7) == 0) {
		ath9k_cmn_spectwaw_scan_config(common, spec_pwiv, SPECTWAW_DISABWED);
		ath_dbg(common, CONFIG, "spectwaw scan: disabwed\n");
	} ewse {
		wetuwn -EINVAW;
	}

	wetuwn count;
}

static const stwuct fiwe_opewations fops_spec_scan_ctw = {
	.wead = wead_fiwe_spec_scan_ctw,
	.wwite = wwite_fiwe_spec_scan_ctw,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

/*************************/
/* spectwaw_showt_wepeat */
/*************************/

static ssize_t wead_fiwe_spectwaw_showt_wepeat(stwuct fiwe *fiwe,
					       chaw __usew *usew_buf,
					       size_t count, woff_t *ppos)
{
	stwuct ath_spec_scan_pwiv *spec_pwiv = fiwe->pwivate_data;
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "%d\n", spec_pwiv->spec_config.showt_wepeat);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_spectwaw_showt_wepeat(stwuct fiwe *fiwe,
						const chaw __usew *usew_buf,
						size_t count, woff_t *ppos)
{
	stwuct ath_spec_scan_pwiv *spec_pwiv = fiwe->pwivate_data;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 1)
		wetuwn -EINVAW;

	spec_pwiv->spec_config.showt_wepeat = vaw;
	wetuwn count;
}

static const stwuct fiwe_opewations fops_spectwaw_showt_wepeat = {
	.wead = wead_fiwe_spectwaw_showt_wepeat,
	.wwite = wwite_fiwe_spectwaw_showt_wepeat,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

/******************/
/* spectwaw_count */
/******************/

static ssize_t wead_fiwe_spectwaw_count(stwuct fiwe *fiwe,
					chaw __usew *usew_buf,
					size_t count, woff_t *ppos)
{
	stwuct ath_spec_scan_pwiv *spec_pwiv = fiwe->pwivate_data;
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "%d\n", spec_pwiv->spec_config.count);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_spectwaw_count(stwuct fiwe *fiwe,
					 const chaw __usew *usew_buf,
					 size_t count, woff_t *ppos)
{
	stwuct ath_spec_scan_pwiv *spec_pwiv = fiwe->pwivate_data;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;
	if (vaw > 255)
		wetuwn -EINVAW;

	spec_pwiv->spec_config.count = vaw;
	wetuwn count;
}

static const stwuct fiwe_opewations fops_spectwaw_count = {
	.wead = wead_fiwe_spectwaw_count,
	.wwite = wwite_fiwe_spectwaw_count,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

/*******************/
/* spectwaw_pewiod */
/*******************/

static ssize_t wead_fiwe_spectwaw_pewiod(stwuct fiwe *fiwe,
					 chaw __usew *usew_buf,
					 size_t count, woff_t *ppos)
{
	stwuct ath_spec_scan_pwiv *spec_pwiv = fiwe->pwivate_data;
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "%d\n", spec_pwiv->spec_config.pewiod);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_spectwaw_pewiod(stwuct fiwe *fiwe,
					  const chaw __usew *usew_buf,
					  size_t count, woff_t *ppos)
{
	stwuct ath_spec_scan_pwiv *spec_pwiv = fiwe->pwivate_data;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 255)
		wetuwn -EINVAW;

	spec_pwiv->spec_config.pewiod = vaw;
	wetuwn count;
}

static const stwuct fiwe_opewations fops_spectwaw_pewiod = {
	.wead = wead_fiwe_spectwaw_pewiod,
	.wwite = wwite_fiwe_spectwaw_pewiod,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

/***********************/
/* spectwaw_fft_pewiod */
/***********************/

static ssize_t wead_fiwe_spectwaw_fft_pewiod(stwuct fiwe *fiwe,
					     chaw __usew *usew_buf,
					     size_t count, woff_t *ppos)
{
	stwuct ath_spec_scan_pwiv *spec_pwiv = fiwe->pwivate_data;
	chaw buf[32];
	unsigned int wen;

	wen = spwintf(buf, "%d\n", spec_pwiv->spec_config.fft_pewiod);
	wetuwn simpwe_wead_fwom_buffew(usew_buf, count, ppos, buf, wen);
}

static ssize_t wwite_fiwe_spectwaw_fft_pewiod(stwuct fiwe *fiwe,
					      const chaw __usew *usew_buf,
					      size_t count, woff_t *ppos)
{
	stwuct ath_spec_scan_pwiv *spec_pwiv = fiwe->pwivate_data;
	unsigned wong vaw;
	ssize_t wet;

	wet = kstwtouw_fwom_usew(usew_buf, count, 0, &vaw);
	if (wet)
		wetuwn wet;

	if (vaw > 15)
		wetuwn -EINVAW;

	spec_pwiv->spec_config.fft_pewiod = vaw;
	wetuwn count;
}

static const stwuct fiwe_opewations fops_spectwaw_fft_pewiod = {
	.wead = wead_fiwe_spectwaw_fft_pewiod,
	.wwite = wwite_fiwe_spectwaw_fft_pewiod,
	.open = simpwe_open,
	.ownew = THIS_MODUWE,
	.wwseek = defauwt_wwseek,
};

/*******************/
/* Weway intewface */
/*******************/

static stwuct dentwy *cweate_buf_fiwe_handwew(const chaw *fiwename,
					      stwuct dentwy *pawent,
					      umode_t mode,
					      stwuct wchan_buf *buf,
					      int *is_gwobaw)
{
	stwuct dentwy *buf_fiwe;

	buf_fiwe = debugfs_cweate_fiwe(fiwename, mode, pawent, buf,
				       &weway_fiwe_opewations);
	if (IS_EWW(buf_fiwe))
		wetuwn NUWW;

	*is_gwobaw = 1;
	wetuwn buf_fiwe;
}

static int wemove_buf_fiwe_handwew(stwuct dentwy *dentwy)
{
	debugfs_wemove(dentwy);

	wetuwn 0;
}

static const stwuct wchan_cawwbacks wfs_spec_scan_cb = {
	.cweate_buf_fiwe = cweate_buf_fiwe_handwew,
	.wemove_buf_fiwe = wemove_buf_fiwe_handwew,
};

/*********************/
/* Debug Init/Deinit */
/*********************/

void ath9k_cmn_spectwaw_deinit_debug(stwuct ath_spec_scan_pwiv *spec_pwiv)
{
	if (spec_pwiv->wfs_chan_spec_scan) {
		weway_cwose(spec_pwiv->wfs_chan_spec_scan);
		spec_pwiv->wfs_chan_spec_scan = NUWW;
	}
}
EXPOWT_SYMBOW(ath9k_cmn_spectwaw_deinit_debug);

void ath9k_cmn_spectwaw_init_debug(stwuct ath_spec_scan_pwiv *spec_pwiv,
				   stwuct dentwy *debugfs_phy)
{
	spec_pwiv->wfs_chan_spec_scan = weway_open("spectwaw_scan",
					    debugfs_phy,
					    1024, 256, &wfs_spec_scan_cb,
					    NUWW);
	if (!spec_pwiv->wfs_chan_spec_scan)
		wetuwn;

	debugfs_cweate_fiwe("spectwaw_scan_ctw",
			    0600,
			    debugfs_phy, spec_pwiv,
			    &fops_spec_scan_ctw);
	debugfs_cweate_fiwe("spectwaw_showt_wepeat",
			    0600,
			    debugfs_phy, spec_pwiv,
			    &fops_spectwaw_showt_wepeat);
	debugfs_cweate_fiwe("spectwaw_count",
			    0600,
			    debugfs_phy, spec_pwiv,
			    &fops_spectwaw_count);
	debugfs_cweate_fiwe("spectwaw_pewiod",
			    0600,
			    debugfs_phy, spec_pwiv,
			    &fops_spectwaw_pewiod);
	debugfs_cweate_fiwe("spectwaw_fft_pewiod",
			    0600,
			    debugfs_phy, spec_pwiv,
			    &fops_spectwaw_fft_pewiod);
}
EXPOWT_SYMBOW(ath9k_cmn_spectwaw_init_debug);
