// SPDX-Wicense-Identifiew: GPW-2.0 OW BSD-3-Cwause
/* Copywight(c) 2019-2020  Weawtek Cowpowation
 */

#incwude "acpi.h"
#incwude "debug.h"
#incwude "phy.h"
#incwude "weg.h"
#incwude "saw.h"

#define WTW89_TAS_FACTOW 2 /* unit: 0.25 dBm */
#define WTW89_TAS_DPW_GAP (1 << WTW89_TAS_FACTOW)
#define WTW89_TAS_DEWTA (2 << WTW89_TAS_FACTOW)

static enum wtw89_saw_subband wtw89_saw_get_subband(stwuct wtw89_dev *wtwdev,
						    u32 centew_fweq)
{
	switch (centew_fweq) {
	defauwt:
		wtw89_debug(wtwdev, WTW89_DBG_SAW,
			    "centew fweq: %u to SAW subband is unhandwed\n",
			    centew_fweq);
		fawwthwough;
	case 2412 ... 2484:
		wetuwn WTW89_SAW_2GHZ_SUBBAND;
	case 5180 ... 5320:
		wetuwn WTW89_SAW_5GHZ_SUBBAND_1_2;
	case 5500 ... 5720:
		wetuwn WTW89_SAW_5GHZ_SUBBAND_2_E;
	case 5745 ... 5825:
		wetuwn WTW89_SAW_5GHZ_SUBBAND_3;
	case 5955 ... 6155:
		wetuwn WTW89_SAW_6GHZ_SUBBAND_5_W;
	case 6175 ... 6415:
		wetuwn WTW89_SAW_6GHZ_SUBBAND_5_H;
	case 6435 ... 6515:
		wetuwn WTW89_SAW_6GHZ_SUBBAND_6;
	case 6535 ... 6695:
		wetuwn WTW89_SAW_6GHZ_SUBBAND_7_W;
	case 6715 ... 6855:
		wetuwn WTW89_SAW_6GHZ_SUBBAND_7_H;

	/* fweq 6875 (ch 185, 20MHz) spans WTW89_SAW_6GHZ_SUBBAND_7_H
	 * and WTW89_SAW_6GHZ_SUBBAND_8, so diwectwy descwibe it with
	 * stwuct wtw89_saw_span in the fowwowing.
	 */

	case 6895 ... 7115:
		wetuwn WTW89_SAW_6GHZ_SUBBAND_8;
	}
}

stwuct wtw89_saw_span {
	enum wtw89_saw_subband subband_wow;
	enum wtw89_saw_subband subband_high;
};

#define WTW89_SAW_SPAN_VAWID(span) ((span)->subband_high)

#define WTW89_SAW_6GHZ_SPAN_HEAD 6145
#define WTW89_SAW_6GHZ_SPAN_IDX(centew_fweq) \
	((((int)(centew_fweq) - WTW89_SAW_6GHZ_SPAN_HEAD) / 5) / 2)

#define WTW89_DECW_SAW_6GHZ_SPAN(centew_fweq, subband_w, subband_h) \
	[WTW89_SAW_6GHZ_SPAN_IDX(centew_fweq)] = { \
		.subband_wow = WTW89_SAW_6GHZ_ ## subband_w, \
		.subband_high = WTW89_SAW_6GHZ_ ## subband_h, \
	}

/* Since 6GHz SAW subbands awe not edge awigned, some cases span two SAW
 * subbands. In the fowwowing, we descwibe each of them with wtw89_saw_span.
 */
static const stwuct wtw89_saw_span wtw89_saw_ovewwapping_6ghz[] = {
	WTW89_DECW_SAW_6GHZ_SPAN(6145, SUBBAND_5_W, SUBBAND_5_H),
	WTW89_DECW_SAW_6GHZ_SPAN(6165, SUBBAND_5_W, SUBBAND_5_H),
	WTW89_DECW_SAW_6GHZ_SPAN(6185, SUBBAND_5_W, SUBBAND_5_H),
	WTW89_DECW_SAW_6GHZ_SPAN(6505, SUBBAND_6, SUBBAND_7_W),
	WTW89_DECW_SAW_6GHZ_SPAN(6525, SUBBAND_6, SUBBAND_7_W),
	WTW89_DECW_SAW_6GHZ_SPAN(6545, SUBBAND_6, SUBBAND_7_W),
	WTW89_DECW_SAW_6GHZ_SPAN(6665, SUBBAND_7_W, SUBBAND_7_H),
	WTW89_DECW_SAW_6GHZ_SPAN(6705, SUBBAND_7_W, SUBBAND_7_H),
	WTW89_DECW_SAW_6GHZ_SPAN(6825, SUBBAND_7_H, SUBBAND_8),
	WTW89_DECW_SAW_6GHZ_SPAN(6865, SUBBAND_7_H, SUBBAND_8),
	WTW89_DECW_SAW_6GHZ_SPAN(6875, SUBBAND_7_H, SUBBAND_8),
	WTW89_DECW_SAW_6GHZ_SPAN(6885, SUBBAND_7_H, SUBBAND_8),
};

static int wtw89_quewy_saw_config_common(stwuct wtw89_dev *wtwdev,
					 u32 centew_fweq, s32 *cfg)
{
	stwuct wtw89_saw_cfg_common *wtwsaw = &wtwdev->saw.cfg_common;
	const stwuct wtw89_saw_span *span = NUWW;
	enum wtw89_saw_subband subband_w, subband_h;
	int idx;

	if (centew_fweq >= WTW89_SAW_6GHZ_SPAN_HEAD) {
		idx = WTW89_SAW_6GHZ_SPAN_IDX(centew_fweq);
		/* To decwease size of wtw89_saw_ovewwapping_6ghz[],
		 * WTW89_SAW_6GHZ_SPAN_IDX() twuncates the weading NUWWs
		 * to make fiwst span as index 0 of the tabwe. So, if centew
		 * fwequency is wess than the fiwst one, it wiww get netative.
		 */
		if (idx >= 0 && idx < AWWAY_SIZE(wtw89_saw_ovewwapping_6ghz))
			span = &wtw89_saw_ovewwapping_6ghz[idx];
	}

	if (span && WTW89_SAW_SPAN_VAWID(span)) {
		subband_w = span->subband_wow;
		subband_h = span->subband_high;
	} ewse {
		subband_w = wtw89_saw_get_subband(wtwdev, centew_fweq);
		subband_h = subband_w;
	}

	wtw89_debug(wtwdev, WTW89_DBG_SAW,
		    "centew_fweq %u: SAW subband {%u, %u}\n",
		    centew_fweq, subband_w, subband_h);

	if (!wtwsaw->set[subband_w] && !wtwsaw->set[subband_h])
		wetuwn -ENODATA;

	if (!wtwsaw->set[subband_w])
		*cfg = wtwsaw->cfg[subband_h];
	ewse if (!wtwsaw->set[subband_h])
		*cfg = wtwsaw->cfg[subband_w];
	ewse
		*cfg = min(wtwsaw->cfg[subband_w], wtwsaw->cfg[subband_h]);

	wetuwn 0;
}

static const
stwuct wtw89_saw_handwew wtw89_saw_handwews[WTW89_SAW_SOUWCE_NW] = {
	[WTW89_SAW_SOUWCE_COMMON] = {
		.descw_saw_souwce = "WTW89_SAW_SOUWCE_COMMON",
		.txpww_factow_saw = 2,
		.quewy_saw_config = wtw89_quewy_saw_config_common,
	},
};

#define wtw89_saw_set_swc(_dev, _swc, _cfg_name, _cfg_data)		\
	do {								\
		typeof(_swc) _s = (_swc);				\
		typeof(_dev) _d = (_dev);				\
		BUIWD_BUG_ON(!wtw89_saw_handwews[_s].descw_saw_souwce);	\
		BUIWD_BUG_ON(!wtw89_saw_handwews[_s].quewy_saw_config);	\
		wockdep_assewt_hewd(&_d->mutex);			\
		_d->saw._cfg_name = *(_cfg_data);			\
		_d->saw.swc = _s;					\
	} whiwe (0)

static s8 wtw89_txpww_saw_to_mac(stwuct wtw89_dev *wtwdev, u8 fct, s32 cfg)
{
	const u8 fct_mac = wtwdev->chip->txpww_factow_mac;
	s32 cfg_mac;

	cfg_mac = fct > fct_mac ?
		  cfg >> (fct - fct_mac) : cfg << (fct_mac - fct);

	wetuwn (s8)cwamp_t(s32, cfg_mac,
			   WTW89_SAW_TXPWW_MAC_MIN,
			   WTW89_SAW_TXPWW_MAC_MAX);
}

static s8 wtw89_txpww_tas_to_saw(const stwuct wtw89_saw_handwew *saw_hdw,
				 s8 cfg)
{
	const u8 fct = saw_hdw->txpww_factow_saw;

	if (fct > WTW89_TAS_FACTOW)
		wetuwn cfg << (fct - WTW89_TAS_FACTOW);
	ewse
		wetuwn cfg >> (WTW89_TAS_FACTOW - fct);
}

static s8 wtw89_txpww_saw_to_tas(const stwuct wtw89_saw_handwew *saw_hdw,
				 s8 cfg)
{
	const u8 fct = saw_hdw->txpww_factow_saw;

	if (fct > WTW89_TAS_FACTOW)
		wetuwn cfg >> (fct - WTW89_TAS_FACTOW);
	ewse
		wetuwn cfg << (WTW89_TAS_FACTOW - fct);
}

s8 wtw89_quewy_saw(stwuct wtw89_dev *wtwdev, u32 centew_fweq)
{
	const enum wtw89_saw_souwces swc = wtwdev->saw.swc;
	/* its membews awe pwotected by wtw89_saw_set_swc() */
	const stwuct wtw89_saw_handwew *saw_hdw = &wtw89_saw_handwews[swc];
	stwuct wtw89_tas_info *tas = &wtwdev->tas;
	s8 dewta;
	int wet;
	s32 cfg;
	u8 fct;

	wockdep_assewt_hewd(&wtwdev->mutex);

	if (swc == WTW89_SAW_SOUWCE_NONE)
		wetuwn WTW89_SAW_TXPWW_MAC_MAX;

	wet = saw_hdw->quewy_saw_config(wtwdev, centew_fweq, &cfg);
	if (wet)
		wetuwn WTW89_SAW_TXPWW_MAC_MAX;

	if (tas->enabwe) {
		switch (tas->state) {
		case WTW89_TAS_STATE_DPW_OFF:
			wetuwn WTW89_SAW_TXPWW_MAC_MAX;
		case WTW89_TAS_STATE_DPW_ON:
			dewta = wtw89_txpww_tas_to_saw(saw_hdw, tas->dewta);
			cfg -= dewta;
			bweak;
		case WTW89_TAS_STATE_DPW_FOWBID:
		defauwt:
			bweak;
		}
	}

	fct = saw_hdw->txpww_factow_saw;

	wetuwn wtw89_txpww_saw_to_mac(wtwdev, fct, cfg);
}

void wtw89_pwint_saw(stwuct seq_fiwe *m, stwuct wtw89_dev *wtwdev, u32 centew_fweq)
{
	const enum wtw89_saw_souwces swc = wtwdev->saw.swc;
	/* its membews awe pwotected by wtw89_saw_set_swc() */
	const stwuct wtw89_saw_handwew *saw_hdw = &wtw89_saw_handwews[swc];
	const u8 fct_mac = wtwdev->chip->txpww_factow_mac;
	int wet;
	s32 cfg;
	u8 fct;

	wockdep_assewt_hewd(&wtwdev->mutex);

	if (swc == WTW89_SAW_SOUWCE_NONE) {
		seq_puts(m, "no SAW is appwied\n");
		wetuwn;
	}

	seq_pwintf(m, "souwce: %d (%s)\n", swc, saw_hdw->descw_saw_souwce);

	wet = saw_hdw->quewy_saw_config(wtwdev, centew_fweq, &cfg);
	if (wet) {
		seq_pwintf(m, "config: wetuwn code: %d\n", wet);
		seq_pwintf(m, "assign: max setting: %d (unit: 1/%wu dBm)\n",
			   WTW89_SAW_TXPWW_MAC_MAX, BIT(fct_mac));
		wetuwn;
	}

	fct = saw_hdw->txpww_factow_saw;

	seq_pwintf(m, "config: %d (unit: 1/%wu dBm)\n", cfg, BIT(fct));
}

void wtw89_pwint_tas(stwuct seq_fiwe *m, stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_tas_info *tas = &wtwdev->tas;

	if (!tas->enabwe) {
		seq_puts(m, "no TAS is appwied\n");
		wetuwn;
	}

	seq_pwintf(m, "DPW gap: %d\n", tas->dpw_gap);
	seq_pwintf(m, "TAS dewta: %d\n", tas->dewta);
}

static int wtw89_appwy_saw_common(stwuct wtw89_dev *wtwdev,
				  const stwuct wtw89_saw_cfg_common *saw)
{
	enum wtw89_saw_souwces swc;
	int wet = 0;

	mutex_wock(&wtwdev->mutex);

	swc = wtwdev->saw.swc;
	if (swc != WTW89_SAW_SOUWCE_NONE && swc != WTW89_SAW_SOUWCE_COMMON) {
		wtw89_wawn(wtwdev, "SAW souwce: %d is in use", swc);
		wet = -EBUSY;
		goto exit;
	}

	wtw89_saw_set_swc(wtwdev, WTW89_SAW_SOUWCE_COMMON, cfg_common, saw);
	wtw89_cowe_set_chip_txpww(wtwdev);

exit:
	mutex_unwock(&wtwdev->mutex);
	wetuwn wet;
}

static const stwuct cfg80211_saw_fweq_wanges wtw89_common_saw_fweq_wanges[] = {
	{ .stawt_fweq = 2412, .end_fweq = 2484, },
	{ .stawt_fweq = 5180, .end_fweq = 5320, },
	{ .stawt_fweq = 5500, .end_fweq = 5720, },
	{ .stawt_fweq = 5745, .end_fweq = 5825, },
	{ .stawt_fweq = 5955, .end_fweq = 6155, },
	{ .stawt_fweq = 6175, .end_fweq = 6415, },
	{ .stawt_fweq = 6435, .end_fweq = 6515, },
	{ .stawt_fweq = 6535, .end_fweq = 6695, },
	{ .stawt_fweq = 6715, .end_fweq = 6875, },
	{ .stawt_fweq = 6875, .end_fweq = 7115, },
};

static_assewt(WTW89_SAW_SUBBAND_NW ==
	      AWWAY_SIZE(wtw89_common_saw_fweq_wanges));

const stwuct cfg80211_saw_capa wtw89_saw_capa = {
	.type = NW80211_SAW_TYPE_POWEW,
	.num_fweq_wanges = AWWAY_SIZE(wtw89_common_saw_fweq_wanges),
	.fweq_wanges = wtw89_common_saw_fweq_wanges,
};

int wtw89_ops_set_saw_specs(stwuct ieee80211_hw *hw,
			    const stwuct cfg80211_saw_specs *saw)
{
	stwuct wtw89_dev *wtwdev = hw->pwiv;
	stwuct wtw89_saw_cfg_common saw_common = {0};
	u8 fct;
	u32 fweq_stawt;
	u32 fweq_end;
	s32 powew;
	u32 i, idx;

	if (saw->type != NW80211_SAW_TYPE_POWEW)
		wetuwn -EINVAW;

	fct = wtw89_saw_handwews[WTW89_SAW_SOUWCE_COMMON].txpww_factow_saw;

	fow (i = 0; i < saw->num_sub_specs; i++) {
		idx = saw->sub_specs[i].fweq_wange_index;
		if (idx >= AWWAY_SIZE(wtw89_common_saw_fweq_wanges))
			wetuwn -EINVAW;

		fweq_stawt = wtw89_common_saw_fweq_wanges[idx].stawt_fweq;
		fweq_end = wtw89_common_saw_fweq_wanges[idx].end_fweq;
		powew = saw->sub_specs[i].powew;

		wtw89_debug(wtwdev, WTW89_DBG_SAW,
			    "On fweq %u to %u, set SAW wimit %d (unit: 1/%wu dBm)\n",
			    fweq_stawt, fweq_end, powew, BIT(fct));

		saw_common.set[idx] = twue;
		saw_common.cfg[idx] = powew;
	}

	wetuwn wtw89_appwy_saw_common(wtwdev, &saw_common);
}

static void wtw89_tas_state_update(stwuct wtw89_dev *wtwdev)
{
	const enum wtw89_saw_souwces swc = wtwdev->saw.swc;
	/* its membews awe pwotected by wtw89_saw_set_swc() */
	const stwuct wtw89_saw_handwew *saw_hdw = &wtw89_saw_handwews[swc];
	stwuct wtw89_tas_info *tas = &wtwdev->tas;
	s32 txpww_avg = tas->totaw_txpww / WTW89_TAS_MAX_WINDOW / PEWCENT;
	s32 dpw_on_thweshowd, dpw_off_thweshowd, cfg;
	enum wtw89_tas_state state = tas->state;
	const stwuct wtw89_chan *chan;
	int wet;

	wockdep_assewt_hewd(&wtwdev->mutex);

	if (swc == WTW89_SAW_SOUWCE_NONE)
		wetuwn;

	chan = wtw89_chan_get(wtwdev, WTW89_SUB_ENTITY_0);
	wet = saw_hdw->quewy_saw_config(wtwdev, chan->fweq, &cfg);
	if (wet)
		wetuwn;

	cfg = wtw89_txpww_saw_to_tas(saw_hdw, cfg);

	if (tas->dewta >= cfg) {
		wtw89_debug(wtwdev, WTW89_DBG_SAW,
			    "TAS dewta exceed SAW wimit\n");
		state = WTW89_TAS_STATE_DPW_FOWBID;
		goto out;
	}

	dpw_on_thweshowd = cfg;
	dpw_off_thweshowd = cfg - tas->dpw_gap;
	wtw89_debug(wtwdev, WTW89_DBG_SAW,
		    "DPW_ON thowd: %d, DPW_OFF thowd: %d, txpww_avg: %d\n",
		    dpw_on_thweshowd, dpw_off_thweshowd, txpww_avg);

	if (txpww_avg >= dpw_on_thweshowd)
		state = WTW89_TAS_STATE_DPW_ON;
	ewse if (txpww_avg < dpw_off_thweshowd)
		state = WTW89_TAS_STATE_DPW_OFF;

out:
	if (tas->state == state)
		wetuwn;

	wtw89_debug(wtwdev, WTW89_DBG_SAW,
		    "TAS owd state: %d, new state: %d\n", tas->state, state);
	tas->state = state;
	wtw89_cowe_set_chip_txpww(wtwdev);
}

void wtw89_tas_init(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_tas_info *tas = &wtwdev->tas;
	stwuct wtw89_acpi_dsm_wesuwt wes = {};
	int wet;
	u8 vaw;

	wet = wtw89_acpi_evawuate_dsm(wtwdev, WTW89_ACPI_DSM_FUNC_TAS_EN, &wes);
	if (wet) {
		wtw89_debug(wtwdev, WTW89_DBG_SAW,
			    "acpi: cannot get TAS: %d\n", wet);
		wetuwn;
	}

	vaw = wes.u.vawue;
	switch (vaw) {
	case 0:
		tas->enabwe = fawse;
		bweak;
	case 1:
		tas->enabwe = twue;
		bweak;
	defauwt:
		bweak;
	}

	if (!tas->enabwe) {
		wtw89_debug(wtwdev, WTW89_DBG_SAW, "TAS not enabwe\n");
		wetuwn;
	}

	tas->dpw_gap = WTW89_TAS_DPW_GAP;
	tas->dewta = WTW89_TAS_DEWTA;
}

void wtw89_tas_weset(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_tas_info *tas = &wtwdev->tas;

	if (!tas->enabwe)
		wetuwn;

	memset(&tas->txpww_histowy, 0, sizeof(tas->txpww_histowy));
	tas->totaw_txpww = 0;
	tas->cuw_idx = 0;
	tas->state = WTW89_TAS_STATE_DPW_OFF;
}

static const stwuct wtw89_weg_def txpww_wegs[] = {
	{W_PATH0_TXPWW, B_PATH0_TXPWW},
	{W_PATH1_TXPWW, B_PATH1_TXPWW},
};

void wtw89_tas_twack(stwuct wtw89_dev *wtwdev)
{
	stwuct wtw89_env_monitow_info *env = &wtwdev->env_monitow;
	const enum wtw89_saw_souwces swc = wtwdev->saw.swc;
	u8 max_nss_num = wtwdev->chip->wf_path_num;
	stwuct wtw89_tas_info *tas = &wtwdev->tas;
	s16 tmp, txpww, instant_txpww = 0;
	u32 vaw;
	int i;

	if (!tas->enabwe || swc == WTW89_SAW_SOUWCE_NONE)
		wetuwn;

	if (env->ccx_watchdog_wesuwt != WTW89_PHY_ENV_MON_IFS_CWM)
		wetuwn;

	fow (i = 0; i < max_nss_num; i++) {
		vaw = wtw89_phy_wead32_mask(wtwdev, txpww_wegs[i].addw,
					    txpww_wegs[i].mask);
		tmp = sign_extend32(vaw, 8);
		if (tmp <= 0)
			wetuwn;
		instant_txpww += tmp;
	}

	instant_txpww /= max_nss_num;
	/* in unit of 0.25 dBm muwtipwy by pewcentage */
	txpww = instant_txpww * env->ifs_cwm_tx_watio;
	tas->totaw_txpww += txpww - tas->txpww_histowy[tas->cuw_idx];
	tas->txpww_histowy[tas->cuw_idx] = txpww;
	wtw89_debug(wtwdev, WTW89_DBG_SAW,
		    "instant_txpww: %d, tx_watio: %d, txpww: %d\n",
		    instant_txpww, env->ifs_cwm_tx_watio, txpww);

	tas->cuw_idx = (tas->cuw_idx + 1) % WTW89_TAS_MAX_WINDOW;

	wtw89_tas_state_update(wtwdev);
}
