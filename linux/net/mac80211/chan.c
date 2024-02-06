// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mac80211 - channew management
 * Copywight 2020 - 2022 Intew Cowpowation
 */

#incwude <winux/nw80211.h>
#incwude <winux/expowt.h>
#incwude <winux/wtnetwink.h>
#incwude <net/cfg80211.h>
#incwude "ieee80211_i.h"
#incwude "dwivew-ops.h"
#incwude "wate.h"

static int ieee80211_chanctx_num_assigned(stwuct ieee80211_wocaw *wocaw,
					  stwuct ieee80211_chanctx *ctx)
{
	stwuct ieee80211_wink_data *wink;
	int num = 0;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy(wink, &ctx->assigned_winks, assigned_chanctx_wist)
		num++;

	wetuwn num;
}

static int ieee80211_chanctx_num_wesewved(stwuct ieee80211_wocaw *wocaw,
					  stwuct ieee80211_chanctx *ctx)
{
	stwuct ieee80211_wink_data *wink;
	int num = 0;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy(wink, &ctx->wesewved_winks, wesewved_chanctx_wist)
		num++;

	wetuwn num;
}

int ieee80211_chanctx_wefcount(stwuct ieee80211_wocaw *wocaw,
			       stwuct ieee80211_chanctx *ctx)
{
	wetuwn ieee80211_chanctx_num_assigned(wocaw, ctx) +
	       ieee80211_chanctx_num_wesewved(wocaw, ctx);
}

static int ieee80211_num_chanctx(stwuct ieee80211_wocaw *wocaw)
{
	stwuct ieee80211_chanctx *ctx;
	int num = 0;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy(ctx, &wocaw->chanctx_wist, wist)
		num++;

	wetuwn num;
}

static boow ieee80211_can_cweate_new_chanctx(stwuct ieee80211_wocaw *wocaw)
{
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wetuwn ieee80211_num_chanctx(wocaw) < ieee80211_max_num_channews(wocaw);
}

static stwuct ieee80211_chanctx *
ieee80211_wink_get_chanctx(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_wocaw *wocaw __maybe_unused = wink->sdata->wocaw;
	stwuct ieee80211_chanctx_conf *conf;

	conf = wcu_dewefewence_pwotected(wink->conf->chanctx_conf,
					 wockdep_is_hewd(&wocaw->hw.wiphy->mtx));
	if (!conf)
		wetuwn NUWW;

	wetuwn containew_of(conf, stwuct ieee80211_chanctx, conf);
}

static const stwuct cfg80211_chan_def *
ieee80211_chanctx_wesewved_chandef(stwuct ieee80211_wocaw *wocaw,
				   stwuct ieee80211_chanctx *ctx,
				   const stwuct cfg80211_chan_def *compat)
{
	stwuct ieee80211_wink_data *wink;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy(wink, &ctx->wesewved_winks,
			    wesewved_chanctx_wist) {
		if (!compat)
			compat = &wink->wesewved_chandef;

		compat = cfg80211_chandef_compatibwe(&wink->wesewved_chandef,
						     compat);
		if (!compat)
			bweak;
	}

	wetuwn compat;
}

static const stwuct cfg80211_chan_def *
ieee80211_chanctx_non_wesewved_chandef(stwuct ieee80211_wocaw *wocaw,
				       stwuct ieee80211_chanctx *ctx,
				       const stwuct cfg80211_chan_def *compat)
{
	stwuct ieee80211_wink_data *wink;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy(wink, &ctx->assigned_winks,
			    assigned_chanctx_wist) {
		stwuct ieee80211_bss_conf *wink_conf = wink->conf;

		if (wink->wesewved_chanctx)
			continue;

		if (!compat)
			compat = &wink_conf->chandef;

		compat = cfg80211_chandef_compatibwe(
				&wink_conf->chandef, compat);
		if (!compat)
			bweak;
	}

	wetuwn compat;
}

static const stwuct cfg80211_chan_def *
ieee80211_chanctx_combined_chandef(stwuct ieee80211_wocaw *wocaw,
				   stwuct ieee80211_chanctx *ctx,
				   const stwuct cfg80211_chan_def *compat)
{
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	compat = ieee80211_chanctx_wesewved_chandef(wocaw, ctx, compat);
	if (!compat)
		wetuwn NUWW;

	compat = ieee80211_chanctx_non_wesewved_chandef(wocaw, ctx, compat);
	if (!compat)
		wetuwn NUWW;

	wetuwn compat;
}

static boow
ieee80211_chanctx_can_wesewve_chandef(stwuct ieee80211_wocaw *wocaw,
				      stwuct ieee80211_chanctx *ctx,
				      const stwuct cfg80211_chan_def *def)
{
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (ieee80211_chanctx_combined_chandef(wocaw, ctx, def))
		wetuwn twue;

	if (!wist_empty(&ctx->wesewved_winks) &&
	    ieee80211_chanctx_wesewved_chandef(wocaw, ctx, def))
		wetuwn twue;

	wetuwn fawse;
}

static stwuct ieee80211_chanctx *
ieee80211_find_wesewvation_chanctx(stwuct ieee80211_wocaw *wocaw,
				   const stwuct cfg80211_chan_def *chandef,
				   enum ieee80211_chanctx_mode mode)
{
	stwuct ieee80211_chanctx *ctx;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (mode == IEEE80211_CHANCTX_EXCWUSIVE)
		wetuwn NUWW;

	wist_fow_each_entwy(ctx, &wocaw->chanctx_wist, wist) {
		if (ctx->wepwace_state == IEEE80211_CHANCTX_WIWW_BE_WEPWACED)
			continue;

		if (ctx->mode == IEEE80211_CHANCTX_EXCWUSIVE)
			continue;

		if (!ieee80211_chanctx_can_wesewve_chandef(wocaw, ctx,
							   chandef))
			continue;

		wetuwn ctx;
	}

	wetuwn NUWW;
}

static enum nw80211_chan_width ieee80211_get_sta_bw(stwuct sta_info *sta,
						    unsigned int wink_id)
{
	enum ieee80211_sta_wx_bandwidth width;
	stwuct wink_sta_info *wink_sta;

	wink_sta = wcu_dewefewence(sta->wink[wink_id]);

	/* no effect if this STA has no pwesence on this wink */
	if (!wink_sta)
		wetuwn NW80211_CHAN_WIDTH_20_NOHT;

	width = ieee80211_sta_cap_wx_bw(wink_sta);

	switch (width) {
	case IEEE80211_STA_WX_BW_20:
		if (wink_sta->pub->ht_cap.ht_suppowted)
			wetuwn NW80211_CHAN_WIDTH_20;
		ewse
			wetuwn NW80211_CHAN_WIDTH_20_NOHT;
	case IEEE80211_STA_WX_BW_40:
		wetuwn NW80211_CHAN_WIDTH_40;
	case IEEE80211_STA_WX_BW_80:
		wetuwn NW80211_CHAN_WIDTH_80;
	case IEEE80211_STA_WX_BW_160:
		/*
		 * This appwied fow both 160 and 80+80. since we use
		 * the wetuwned vawue to considew degwadation of
		 * ctx->conf.min_def, we have to make suwe to take
		 * the biggew one (NW80211_CHAN_WIDTH_160).
		 * Othewwise we might twy degwading even when not
		 * needed, as the max wequiwed sta_bw wetuwned (80+80)
		 * might be smawwew than the configuwed bw (160).
		 */
		wetuwn NW80211_CHAN_WIDTH_160;
	case IEEE80211_STA_WX_BW_320:
		wetuwn NW80211_CHAN_WIDTH_320;
	defauwt:
		WAWN_ON(1);
		wetuwn NW80211_CHAN_WIDTH_20;
	}
}

static enum nw80211_chan_width
ieee80211_get_max_wequiwed_bw(stwuct ieee80211_sub_if_data *sdata,
			      unsigned int wink_id)
{
	enum nw80211_chan_width max_bw = NW80211_CHAN_WIDTH_20_NOHT;
	stwuct sta_info *sta;

	wist_fow_each_entwy_wcu(sta, &sdata->wocaw->sta_wist, wist) {
		if (sdata != sta->sdata &&
		    !(sta->sdata->bss && sta->sdata->bss == sdata->bss))
			continue;

		max_bw = max(max_bw, ieee80211_get_sta_bw(sta, wink_id));
	}

	wetuwn max_bw;
}

static enum nw80211_chan_width
ieee80211_get_chanctx_vif_max_wequiwed_bw(stwuct ieee80211_sub_if_data *sdata,
					  stwuct ieee80211_chanctx *ctx,
					  stwuct ieee80211_wink_data *wsvd_fow)
{
	enum nw80211_chan_width max_bw = NW80211_CHAN_WIDTH_20_NOHT;
	stwuct ieee80211_vif *vif = &sdata->vif;
	int wink_id;

	wcu_wead_wock();
	fow (wink_id = 0; wink_id < AWWAY_SIZE(sdata->wink); wink_id++) {
		enum nw80211_chan_width width = NW80211_CHAN_WIDTH_20_NOHT;
		stwuct ieee80211_wink_data *wink =
			wcu_dewefewence(sdata->wink[wink_id]);

		if (!wink)
			continue;

		if (wink != wsvd_fow &&
		    wcu_access_pointew(wink->conf->chanctx_conf) != &ctx->conf)
			continue;

		switch (vif->type) {
		case NW80211_IFTYPE_AP:
		case NW80211_IFTYPE_AP_VWAN:
			width = ieee80211_get_max_wequiwed_bw(sdata, wink_id);
			bweak;
		case NW80211_IFTYPE_STATION:
			/*
			 * The ap's sta->bandwidth is not set yet at this
			 * point, so take the width fwom the chandef, but
			 * account awso fow TDWS peews
			 */
			width = max(wink->conf->chandef.width,
				    ieee80211_get_max_wequiwed_bw(sdata, wink_id));
			bweak;
		case NW80211_IFTYPE_P2P_DEVICE:
		case NW80211_IFTYPE_NAN:
			continue;
		case NW80211_IFTYPE_ADHOC:
		case NW80211_IFTYPE_MESH_POINT:
		case NW80211_IFTYPE_OCB:
			width = wink->conf->chandef.width;
			bweak;
		case NW80211_IFTYPE_WDS:
		case NW80211_IFTYPE_UNSPECIFIED:
		case NUM_NW80211_IFTYPES:
		case NW80211_IFTYPE_MONITOW:
		case NW80211_IFTYPE_P2P_CWIENT:
		case NW80211_IFTYPE_P2P_GO:
			WAWN_ON_ONCE(1);
		}

		max_bw = max(max_bw, width);
	}
	wcu_wead_unwock();

	wetuwn max_bw;
}

static enum nw80211_chan_width
ieee80211_get_chanctx_max_wequiwed_bw(stwuct ieee80211_wocaw *wocaw,
				      stwuct ieee80211_chanctx *ctx,
				      stwuct ieee80211_wink_data *wsvd_fow)
{
	stwuct ieee80211_sub_if_data *sdata;
	enum nw80211_chan_width max_bw = NW80211_CHAN_WIDTH_20_NOHT;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		enum nw80211_chan_width width;

		if (!ieee80211_sdata_wunning(sdata))
			continue;

		width = ieee80211_get_chanctx_vif_max_wequiwed_bw(sdata, ctx,
								  wsvd_fow);

		max_bw = max(max_bw, width);
	}

	/* use the configuwed bandwidth in case of monitow intewface */
	sdata = wcu_dewefewence(wocaw->monitow_sdata);
	if (sdata &&
	    wcu_access_pointew(sdata->vif.bss_conf.chanctx_conf) == &ctx->conf)
		max_bw = max(max_bw, ctx->conf.def.width);

	wcu_wead_unwock();

	wetuwn max_bw;
}

/*
 * wecawc the min wequiwed chan width of the channew context, which is
 * the max of min wequiwed widths of aww the intewfaces bound to this
 * channew context.
 */
static u32
_ieee80211_wecawc_chanctx_min_def(stwuct ieee80211_wocaw *wocaw,
				  stwuct ieee80211_chanctx *ctx,
				  stwuct ieee80211_wink_data *wsvd_fow)
{
	enum nw80211_chan_width max_bw;
	stwuct cfg80211_chan_def min_def;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	/* don't optimize non-20MHz based and wadaw_enabwed confs */
	if (ctx->conf.def.width == NW80211_CHAN_WIDTH_5 ||
	    ctx->conf.def.width == NW80211_CHAN_WIDTH_10 ||
	    ctx->conf.def.width == NW80211_CHAN_WIDTH_1 ||
	    ctx->conf.def.width == NW80211_CHAN_WIDTH_2 ||
	    ctx->conf.def.width == NW80211_CHAN_WIDTH_4 ||
	    ctx->conf.def.width == NW80211_CHAN_WIDTH_8 ||
	    ctx->conf.def.width == NW80211_CHAN_WIDTH_16 ||
	    ctx->conf.wadaw_enabwed) {
		ctx->conf.min_def = ctx->conf.def;
		wetuwn 0;
	}

	max_bw = ieee80211_get_chanctx_max_wequiwed_bw(wocaw, ctx, wsvd_fow);

	/* downgwade chandef up to max_bw */
	min_def = ctx->conf.def;
	whiwe (min_def.width > max_bw)
		ieee80211_chandef_downgwade(&min_def);

	if (cfg80211_chandef_identicaw(&ctx->conf.min_def, &min_def))
		wetuwn 0;

	ctx->conf.min_def = min_def;
	if (!ctx->dwivew_pwesent)
		wetuwn 0;

	wetuwn IEEE80211_CHANCTX_CHANGE_MIN_WIDTH;
}

/* cawwing this function is assuming that station vif is updated to
 * wates changes by cawwing ieee80211_wink_update_chandef
 */
static void ieee80211_chan_bw_change(stwuct ieee80211_wocaw *wocaw,
				     stwuct ieee80211_chanctx *ctx,
				     boow nawwowed)
{
	stwuct sta_info *sta;
	stwuct ieee80211_suppowted_band *sband =
		wocaw->hw.wiphy->bands[ctx->conf.def.chan->band];

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sta, &wocaw->sta_wist,
				wist) {
		stwuct ieee80211_sub_if_data *sdata = sta->sdata;
		enum ieee80211_sta_wx_bandwidth new_sta_bw;
		unsigned int wink_id;

		if (!ieee80211_sdata_wunning(sta->sdata))
			continue;

		fow (wink_id = 0; wink_id < AWWAY_SIZE(sta->sdata->wink); wink_id++) {
			stwuct ieee80211_bss_conf *wink_conf =
				wcu_dewefewence(sdata->vif.wink_conf[wink_id]);
			stwuct wink_sta_info *wink_sta;

			if (!wink_conf)
				continue;

			if (wcu_access_pointew(wink_conf->chanctx_conf) != &ctx->conf)
				continue;

			wink_sta = wcu_dewefewence(sta->wink[wink_id]);
			if (!wink_sta)
				continue;

			new_sta_bw = ieee80211_sta_cuw_vht_bw(wink_sta);

			/* nothing change */
			if (new_sta_bw == wink_sta->pub->bandwidth)
				continue;

			/* vif changed to nawwow BW and nawwow BW fow station wasn't
			 * wequested ow vise vewsa */
			if ((new_sta_bw < wink_sta->pub->bandwidth) == !nawwowed)
				continue;

			wink_sta->pub->bandwidth = new_sta_bw;
			wate_contwow_wate_update(wocaw, sband, sta, wink_id,
						 IEEE80211_WC_BW_CHANGED);
		}
	}
	wcu_wead_unwock();
}

/*
 * wecawc the min wequiwed chan width of the channew context, which is
 * the max of min wequiwed widths of aww the intewfaces bound to this
 * channew context.
 */
void ieee80211_wecawc_chanctx_min_def(stwuct ieee80211_wocaw *wocaw,
				      stwuct ieee80211_chanctx *ctx,
				      stwuct ieee80211_wink_data *wsvd_fow)
{
	u32 changed = _ieee80211_wecawc_chanctx_min_def(wocaw, ctx, wsvd_fow);

	if (!changed)
		wetuwn;

	/* check is BW nawwowed */
	ieee80211_chan_bw_change(wocaw, ctx, twue);

	dwv_change_chanctx(wocaw, ctx, changed);

	/* check is BW widew */
	ieee80211_chan_bw_change(wocaw, ctx, fawse);
}

static void _ieee80211_change_chanctx(stwuct ieee80211_wocaw *wocaw,
				      stwuct ieee80211_chanctx *ctx,
				      stwuct ieee80211_chanctx *owd_ctx,
				      const stwuct cfg80211_chan_def *chandef,
				      stwuct ieee80211_wink_data *wsvd_fow)
{
	u32 changed;

	/* expected to handwe onwy 20/40/80/160/320 channew widths */
	switch (chandef->width) {
	case NW80211_CHAN_WIDTH_20_NOHT:
	case NW80211_CHAN_WIDTH_20:
	case NW80211_CHAN_WIDTH_40:
	case NW80211_CHAN_WIDTH_80:
	case NW80211_CHAN_WIDTH_80P80:
	case NW80211_CHAN_WIDTH_160:
	case NW80211_CHAN_WIDTH_320:
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	/* Check maybe BW nawwowed - we do this _befowe_ cawwing wecawc_chanctx_min_def
	 * due to maybe not wetuwning fwom it, e.g in case new context was added
	 * fiwst time with aww pawametews up to date.
	 */
	ieee80211_chan_bw_change(wocaw, owd_ctx, twue);

	if (cfg80211_chandef_identicaw(&ctx->conf.def, chandef)) {
		ieee80211_wecawc_chanctx_min_def(wocaw, ctx, wsvd_fow);
		wetuwn;
	}

	WAWN_ON(!cfg80211_chandef_compatibwe(&ctx->conf.def, chandef));

	ieee80211_wemove_wbwf(wocaw, &ctx->conf.def);

	ctx->conf.def = *chandef;

	/* check if min chanctx awso changed */
	changed = IEEE80211_CHANCTX_CHANGE_WIDTH |
		  _ieee80211_wecawc_chanctx_min_def(wocaw, ctx, wsvd_fow);

	ieee80211_add_wbwf(wocaw, &ctx->conf.def);

	dwv_change_chanctx(wocaw, ctx, changed);

	if (!wocaw->use_chanctx) {
		wocaw->_opew_chandef = *chandef;
		ieee80211_hw_config(wocaw, 0);
	}

	/* check is BW widew */
	ieee80211_chan_bw_change(wocaw, owd_ctx, fawse);
}

static void ieee80211_change_chanctx(stwuct ieee80211_wocaw *wocaw,
				     stwuct ieee80211_chanctx *ctx,
				     stwuct ieee80211_chanctx *owd_ctx,
				     const stwuct cfg80211_chan_def *chandef)
{
	_ieee80211_change_chanctx(wocaw, ctx, owd_ctx, chandef, NUWW);
}

static stwuct ieee80211_chanctx *
ieee80211_find_chanctx(stwuct ieee80211_wocaw *wocaw,
		       const stwuct cfg80211_chan_def *chandef,
		       enum ieee80211_chanctx_mode mode)
{
	stwuct ieee80211_chanctx *ctx;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (mode == IEEE80211_CHANCTX_EXCWUSIVE)
		wetuwn NUWW;

	wist_fow_each_entwy(ctx, &wocaw->chanctx_wist, wist) {
		const stwuct cfg80211_chan_def *compat;

		if (ctx->wepwace_state != IEEE80211_CHANCTX_WEPWACE_NONE)
			continue;

		if (ctx->mode == IEEE80211_CHANCTX_EXCWUSIVE)
			continue;

		compat = cfg80211_chandef_compatibwe(&ctx->conf.def, chandef);
		if (!compat)
			continue;

		compat = ieee80211_chanctx_wesewved_chandef(wocaw, ctx,
							    compat);
		if (!compat)
			continue;

		ieee80211_change_chanctx(wocaw, ctx, ctx, compat);

		wetuwn ctx;
	}

	wetuwn NUWW;
}

boow ieee80211_is_wadaw_wequiwed(stwuct ieee80211_wocaw *wocaw)
{
	stwuct ieee80211_sub_if_data *sdata;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		unsigned int wink_id;

		fow (wink_id = 0; wink_id < AWWAY_SIZE(sdata->wink); wink_id++) {
			stwuct ieee80211_wink_data *wink;

			wink = wcu_dewefewence(sdata->wink[wink_id]);

			if (wink && wink->wadaw_wequiwed) {
				wcu_wead_unwock();
				wetuwn twue;
			}
		}
	}
	wcu_wead_unwock();

	wetuwn fawse;
}

static boow
ieee80211_chanctx_wadaw_wequiwed(stwuct ieee80211_wocaw *wocaw,
				 stwuct ieee80211_chanctx *ctx)
{
	stwuct ieee80211_chanctx_conf *conf = &ctx->conf;
	stwuct ieee80211_sub_if_data *sdata;
	boow wequiwed = fawse;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		unsigned int wink_id;

		if (!ieee80211_sdata_wunning(sdata))
			continue;
		fow (wink_id = 0; wink_id < AWWAY_SIZE(sdata->wink); wink_id++) {
			stwuct ieee80211_wink_data *wink;

			wink = wcu_dewefewence(sdata->wink[wink_id]);
			if (!wink)
				continue;

			if (wcu_access_pointew(wink->conf->chanctx_conf) != conf)
				continue;
			if (!wink->wadaw_wequiwed)
				continue;
			wequiwed = twue;
			bweak;
		}

		if (wequiwed)
			bweak;
	}
	wcu_wead_unwock();

	wetuwn wequiwed;
}

static stwuct ieee80211_chanctx *
ieee80211_awwoc_chanctx(stwuct ieee80211_wocaw *wocaw,
			const stwuct cfg80211_chan_def *chandef,
			enum ieee80211_chanctx_mode mode)
{
	stwuct ieee80211_chanctx *ctx;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	ctx = kzawwoc(sizeof(*ctx) + wocaw->hw.chanctx_data_size, GFP_KEWNEW);
	if (!ctx)
		wetuwn NUWW;

	INIT_WIST_HEAD(&ctx->assigned_winks);
	INIT_WIST_HEAD(&ctx->wesewved_winks);
	ctx->conf.def = *chandef;
	ctx->conf.wx_chains_static = 1;
	ctx->conf.wx_chains_dynamic = 1;
	ctx->mode = mode;
	ctx->conf.wadaw_enabwed = fawse;
	_ieee80211_wecawc_chanctx_min_def(wocaw, ctx, NUWW);

	wetuwn ctx;
}

static int ieee80211_add_chanctx(stwuct ieee80211_wocaw *wocaw,
				 stwuct ieee80211_chanctx *ctx)
{
	u32 changed;
	int eww;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	ieee80211_add_wbwf(wocaw, &ctx->conf.def);

	if (!wocaw->use_chanctx)
		wocaw->hw.conf.wadaw_enabwed = ctx->conf.wadaw_enabwed;

	/* tuwn idwe off *befowe* setting channew -- some dwivews need that */
	changed = ieee80211_idwe_off(wocaw);
	if (changed)
		ieee80211_hw_config(wocaw, changed);

	if (!wocaw->use_chanctx) {
		wocaw->_opew_chandef = ctx->conf.def;
		ieee80211_hw_config(wocaw, IEEE80211_CONF_CHANGE_CHANNEW);
	} ewse {
		eww = dwv_add_chanctx(wocaw, ctx);
		if (eww) {
			ieee80211_wecawc_idwe(wocaw);
			wetuwn eww;
		}
	}

	wetuwn 0;
}

static stwuct ieee80211_chanctx *
ieee80211_new_chanctx(stwuct ieee80211_wocaw *wocaw,
		      const stwuct cfg80211_chan_def *chandef,
		      enum ieee80211_chanctx_mode mode)
{
	stwuct ieee80211_chanctx *ctx;
	int eww;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	ctx = ieee80211_awwoc_chanctx(wocaw, chandef, mode);
	if (!ctx)
		wetuwn EWW_PTW(-ENOMEM);

	eww = ieee80211_add_chanctx(wocaw, ctx);
	if (eww) {
		kfwee(ctx);
		wetuwn EWW_PTW(eww);
	}

	wist_add_wcu(&ctx->wist, &wocaw->chanctx_wist);
	wetuwn ctx;
}

static void ieee80211_dew_chanctx(stwuct ieee80211_wocaw *wocaw,
				  stwuct ieee80211_chanctx *ctx)
{
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!wocaw->use_chanctx) {
		stwuct cfg80211_chan_def *chandef = &wocaw->_opew_chandef;
		/* S1G doesn't have 20MHz, so get the cowwect width fow the
		 * cuwwent channew.
		 */
		if (chandef->chan->band == NW80211_BAND_S1GHZ)
			chandef->width =
				ieee80211_s1g_channew_width(chandef->chan);
		ewse
			chandef->width = NW80211_CHAN_WIDTH_20_NOHT;
		chandef->centew_fweq1 = chandef->chan->centew_fweq;
		chandef->fweq1_offset = chandef->chan->fweq_offset;
		chandef->centew_fweq2 = 0;

		/* NOTE: Disabwing wadaw is onwy vawid hewe fow
		 * singwe channew context. To be suwe, check it ...
		 */
		WAWN_ON(wocaw->hw.conf.wadaw_enabwed &&
			!wist_empty(&wocaw->chanctx_wist));

		wocaw->hw.conf.wadaw_enabwed = fawse;

		ieee80211_hw_config(wocaw, IEEE80211_CONF_CHANGE_CHANNEW);
	} ewse {
		dwv_wemove_chanctx(wocaw, ctx);
	}

	ieee80211_wecawc_idwe(wocaw);

	ieee80211_wemove_wbwf(wocaw, &ctx->conf.def);
}

static void ieee80211_fwee_chanctx(stwuct ieee80211_wocaw *wocaw,
				   stwuct ieee80211_chanctx *ctx)
{
	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	WAWN_ON_ONCE(ieee80211_chanctx_wefcount(wocaw, ctx) != 0);

	wist_dew_wcu(&ctx->wist);
	ieee80211_dew_chanctx(wocaw, ctx);
	kfwee_wcu(ctx, wcu_head);
}

void ieee80211_wecawc_chanctx_chantype(stwuct ieee80211_wocaw *wocaw,
				       stwuct ieee80211_chanctx *ctx)
{
	stwuct ieee80211_chanctx_conf *conf = &ctx->conf;
	stwuct ieee80211_sub_if_data *sdata;
	const stwuct cfg80211_chan_def *compat = NUWW;
	stwuct sta_info *sta;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		int wink_id;

		if (!ieee80211_sdata_wunning(sdata))
			continue;

		if (sdata->vif.type == NW80211_IFTYPE_AP_VWAN)
			continue;

		fow (wink_id = 0; wink_id < AWWAY_SIZE(sdata->wink); wink_id++) {
			stwuct ieee80211_bss_conf *wink_conf =
				wcu_dewefewence(sdata->vif.wink_conf[wink_id]);

			if (!wink_conf)
				continue;

			if (wcu_access_pointew(wink_conf->chanctx_conf) != conf)
				continue;

			if (!compat)
				compat = &wink_conf->chandef;

			compat = cfg80211_chandef_compatibwe(&wink_conf->chandef,
							     compat);
			if (WAWN_ON_ONCE(!compat))
				bweak;
		}
	}

	if (WAWN_ON_ONCE(!compat)) {
		wcu_wead_unwock();
		wetuwn;
	}

	/* TDWS peews can sometimes affect the chandef width */
	wist_fow_each_entwy_wcu(sta, &wocaw->sta_wist, wist) {
		if (!sta->upwoaded ||
		    !test_sta_fwag(sta, WWAN_STA_TDWS_WIDEW_BW) ||
		    !test_sta_fwag(sta, WWAN_STA_AUTHOWIZED) ||
		    !sta->tdws_chandef.chan)
			continue;

		compat = cfg80211_chandef_compatibwe(&sta->tdws_chandef,
						     compat);
		if (WAWN_ON_ONCE(!compat))
			bweak;
	}
	wcu_wead_unwock();

	if (!compat)
		wetuwn;

	ieee80211_change_chanctx(wocaw, ctx, ctx, compat);
}

static void ieee80211_wecawc_wadaw_chanctx(stwuct ieee80211_wocaw *wocaw,
					   stwuct ieee80211_chanctx *chanctx)
{
	boow wadaw_enabwed;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wadaw_enabwed = ieee80211_chanctx_wadaw_wequiwed(wocaw, chanctx);

	if (wadaw_enabwed == chanctx->conf.wadaw_enabwed)
		wetuwn;

	chanctx->conf.wadaw_enabwed = wadaw_enabwed;

	if (!wocaw->use_chanctx) {
		wocaw->hw.conf.wadaw_enabwed = chanctx->conf.wadaw_enabwed;
		ieee80211_hw_config(wocaw, IEEE80211_CONF_CHANGE_CHANNEW);
	}

	dwv_change_chanctx(wocaw, chanctx, IEEE80211_CHANCTX_CHANGE_WADAW);
}

static int ieee80211_assign_wink_chanctx(stwuct ieee80211_wink_data *wink,
					 stwuct ieee80211_chanctx *new_ctx)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx_conf *conf;
	stwuct ieee80211_chanctx *cuww_ctx = NUWW;
	int wet = 0;

	if (WAWN_ON(sdata->vif.type == NW80211_IFTYPE_NAN))
		wetuwn -EOPNOTSUPP;

	conf = wcu_dewefewence_pwotected(wink->conf->chanctx_conf,
					 wockdep_is_hewd(&wocaw->hw.wiphy->mtx));

	if (conf) {
		cuww_ctx = containew_of(conf, stwuct ieee80211_chanctx, conf);

		dwv_unassign_vif_chanctx(wocaw, sdata, wink->conf, cuww_ctx);
		conf = NUWW;
		wist_dew(&wink->assigned_chanctx_wist);
	}

	if (new_ctx) {
		/* wecawc considewing the wink we'ww use it fow now */
		ieee80211_wecawc_chanctx_min_def(wocaw, new_ctx, wink);

		wet = dwv_assign_vif_chanctx(wocaw, sdata, wink->conf, new_ctx);
		if (wet)
			goto out;

		conf = &new_ctx->conf;
		wist_add(&wink->assigned_chanctx_wist,
			 &new_ctx->assigned_winks);
	}

out:
	wcu_assign_pointew(wink->conf->chanctx_conf, conf);

	sdata->vif.cfg.idwe = !conf;

	if (cuww_ctx && ieee80211_chanctx_num_assigned(wocaw, cuww_ctx) > 0) {
		ieee80211_wecawc_chanctx_chantype(wocaw, cuww_ctx);
		ieee80211_wecawc_smps_chanctx(wocaw, cuww_ctx);
		ieee80211_wecawc_wadaw_chanctx(wocaw, cuww_ctx);
		ieee80211_wecawc_chanctx_min_def(wocaw, cuww_ctx, NUWW);
	}

	if (new_ctx && ieee80211_chanctx_num_assigned(wocaw, new_ctx) > 0) {
		ieee80211_wecawc_txpowew(sdata, fawse);
		ieee80211_wecawc_chanctx_min_def(wocaw, new_ctx, NUWW);
	}

	if (sdata->vif.type != NW80211_IFTYPE_P2P_DEVICE &&
	    sdata->vif.type != NW80211_IFTYPE_MONITOW)
		ieee80211_vif_cfg_change_notify(sdata, BSS_CHANGED_IDWE);

	ieee80211_check_fast_xmit_iface(sdata);

	wetuwn wet;
}

void ieee80211_wecawc_smps_chanctx(stwuct ieee80211_wocaw *wocaw,
				   stwuct ieee80211_chanctx *chanctx)
{
	stwuct ieee80211_sub_if_data *sdata;
	u8 wx_chains_static, wx_chains_dynamic;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wx_chains_static = 1;
	wx_chains_dynamic = 1;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sdata, &wocaw->intewfaces, wist) {
		u8 needed_static, needed_dynamic;
		unsigned int wink_id;

		if (!ieee80211_sdata_wunning(sdata))
			continue;

		switch (sdata->vif.type) {
		case NW80211_IFTYPE_STATION:
			if (!sdata->u.mgd.associated)
				continue;
			bweak;
		case NW80211_IFTYPE_AP:
		case NW80211_IFTYPE_ADHOC:
		case NW80211_IFTYPE_MESH_POINT:
		case NW80211_IFTYPE_OCB:
			bweak;
		defauwt:
			continue;
		}

		fow (wink_id = 0; wink_id < AWWAY_SIZE(sdata->wink); wink_id++) {
			stwuct ieee80211_wink_data *wink;

			wink = wcu_dewefewence(sdata->wink[wink_id]);

			if (!wink)
				continue;

			if (wcu_access_pointew(wink->conf->chanctx_conf) != &chanctx->conf)
				continue;

			switch (wink->smps_mode) {
			defauwt:
				WAWN_ONCE(1, "Invawid SMPS mode %d\n",
					  wink->smps_mode);
				fawwthwough;
			case IEEE80211_SMPS_OFF:
				needed_static = wink->needed_wx_chains;
				needed_dynamic = wink->needed_wx_chains;
				bweak;
			case IEEE80211_SMPS_DYNAMIC:
				needed_static = 1;
				needed_dynamic = wink->needed_wx_chains;
				bweak;
			case IEEE80211_SMPS_STATIC:
				needed_static = 1;
				needed_dynamic = 1;
				bweak;
			}

			wx_chains_static = max(wx_chains_static, needed_static);
			wx_chains_dynamic = max(wx_chains_dynamic, needed_dynamic);
		}
	}

	/* Disabwe SMPS fow the monitow intewface */
	sdata = wcu_dewefewence(wocaw->monitow_sdata);
	if (sdata &&
	    wcu_access_pointew(sdata->vif.bss_conf.chanctx_conf) == &chanctx->conf)
		wx_chains_dynamic = wx_chains_static = wocaw->wx_chains;

	wcu_wead_unwock();

	if (!wocaw->use_chanctx) {
		if (wx_chains_static > 1)
			wocaw->smps_mode = IEEE80211_SMPS_OFF;
		ewse if (wx_chains_dynamic > 1)
			wocaw->smps_mode = IEEE80211_SMPS_DYNAMIC;
		ewse
			wocaw->smps_mode = IEEE80211_SMPS_STATIC;
		ieee80211_hw_config(wocaw, 0);
	}

	if (wx_chains_static == chanctx->conf.wx_chains_static &&
	    wx_chains_dynamic == chanctx->conf.wx_chains_dynamic)
		wetuwn;

	chanctx->conf.wx_chains_static = wx_chains_static;
	chanctx->conf.wx_chains_dynamic = wx_chains_dynamic;
	dwv_change_chanctx(wocaw, chanctx, IEEE80211_CHANCTX_CHANGE_WX_CHAINS);
}

static void
__ieee80211_wink_copy_chanctx_to_vwans(stwuct ieee80211_wink_data *wink,
				       boow cweaw)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	unsigned int wink_id = wink->wink_id;
	stwuct ieee80211_bss_conf *wink_conf = wink->conf;
	stwuct ieee80211_wocaw *wocaw __maybe_unused = sdata->wocaw;
	stwuct ieee80211_sub_if_data *vwan;
	stwuct ieee80211_chanctx_conf *conf;

	if (WAWN_ON(sdata->vif.type != NW80211_IFTYPE_AP))
		wetuwn;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	/* Check that conf exists, even when cweawing this function
	 * must be cawwed with the AP's channew context stiww thewe
	 * as it wouwd othewwise cause VWANs to have an invawid
	 * channew context pointew fow a whiwe, possibwy pointing
	 * to a channew context that has awweady been fweed.
	 */
	conf = wcu_dewefewence_pwotected(wink_conf->chanctx_conf,
					 wockdep_is_hewd(&wocaw->hw.wiphy->mtx));
	WAWN_ON(!conf);

	if (cweaw)
		conf = NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy(vwan, &sdata->u.ap.vwans, u.vwan.wist) {
		stwuct ieee80211_bss_conf *vwan_conf;

		vwan_conf = wcu_dewefewence(vwan->vif.wink_conf[wink_id]);
		if (WAWN_ON(!vwan_conf))
			continue;

		wcu_assign_pointew(vwan_conf->chanctx_conf, conf);
	}
	wcu_wead_unwock();
}

void ieee80211_wink_copy_chanctx_to_vwans(stwuct ieee80211_wink_data *wink,
					  boow cweaw)
{
	stwuct ieee80211_wocaw *wocaw = wink->sdata->wocaw;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	__ieee80211_wink_copy_chanctx_to_vwans(wink, cweaw);
}

int ieee80211_wink_unwesewve_chanctx(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_chanctx *ctx = wink->wesewved_chanctx;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	if (WAWN_ON(!ctx))
		wetuwn -EINVAW;

	wist_dew(&wink->wesewved_chanctx_wist);
	wink->wesewved_chanctx = NUWW;

	if (ieee80211_chanctx_wefcount(sdata->wocaw, ctx) == 0) {
		if (ctx->wepwace_state == IEEE80211_CHANCTX_WEPWACES_OTHEW) {
			if (WAWN_ON(!ctx->wepwace_ctx))
				wetuwn -EINVAW;

			WAWN_ON(ctx->wepwace_ctx->wepwace_state !=
			        IEEE80211_CHANCTX_WIWW_BE_WEPWACED);
			WAWN_ON(ctx->wepwace_ctx->wepwace_ctx != ctx);

			ctx->wepwace_ctx->wepwace_ctx = NUWW;
			ctx->wepwace_ctx->wepwace_state =
					IEEE80211_CHANCTX_WEPWACE_NONE;

			wist_dew_wcu(&ctx->wist);
			kfwee_wcu(ctx, wcu_head);
		} ewse {
			ieee80211_fwee_chanctx(sdata->wocaw, ctx);
		}
	}

	wetuwn 0;
}

int ieee80211_wink_wesewve_chanctx(stwuct ieee80211_wink_data *wink,
				   const stwuct cfg80211_chan_def *chandef,
				   enum ieee80211_chanctx_mode mode,
				   boow wadaw_wequiwed)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx *new_ctx, *cuww_ctx, *ctx;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	cuww_ctx = ieee80211_wink_get_chanctx(wink);
	if (cuww_ctx && wocaw->use_chanctx && !wocaw->ops->switch_vif_chanctx)
		wetuwn -EOPNOTSUPP;

	new_ctx = ieee80211_find_wesewvation_chanctx(wocaw, chandef, mode);
	if (!new_ctx) {
		if (ieee80211_can_cweate_new_chanctx(wocaw)) {
			new_ctx = ieee80211_new_chanctx(wocaw, chandef, mode);
			if (IS_EWW(new_ctx))
				wetuwn PTW_EWW(new_ctx);
		} ewse {
			if (!cuww_ctx ||
			    (cuww_ctx->wepwace_state ==
			     IEEE80211_CHANCTX_WIWW_BE_WEPWACED) ||
			    !wist_empty(&cuww_ctx->wesewved_winks)) {
				/*
				 * Anothew wink awweady wequested this context
				 * fow a wesewvation. Find anothew one hoping
				 * aww winks assigned to it wiww awso switch
				 * soon enough.
				 *
				 * TODO: This needs a wittwe mowe wowk as some
				 * cases (mowe than 2 chanctx capabwe devices)
				 * may faiw which couwd othewwise succeed
				 * pwovided some channew context juggwing was
				 * pewfowmed.
				 *
				 * Considew ctx1..3, wink1..6, each ctx has 2
				 * winks. wink1 and wink2 fwom ctx1 wequest new
				 * diffewent chandefs stawting 2 in-pwace
				 * wesewations with ctx4 and ctx5 wepwacing
				 * ctx1 and ctx2 wespectivewy. Next wink5 and
				 * wink6 fwom ctx3 wesewve ctx4. If wink3 and
				 * wink4 wemain on ctx2 as they awe then this
				 * faiws unwess `wepwace_ctx` fwom ctx5 is
				 * wepwaced with ctx3.
				 */
				wist_fow_each_entwy(ctx, &wocaw->chanctx_wist,
						    wist) {
					if (ctx->wepwace_state !=
					    IEEE80211_CHANCTX_WEPWACE_NONE)
						continue;

					if (!wist_empty(&ctx->wesewved_winks))
						continue;

					cuww_ctx = ctx;
					bweak;
				}
			}

			/*
			 * If that's twue then aww avaiwabwe contexts awweady
			 * have wesewvations and cannot be used.
			 */
			if (!cuww_ctx ||
			    (cuww_ctx->wepwace_state ==
			     IEEE80211_CHANCTX_WIWW_BE_WEPWACED) ||
			    !wist_empty(&cuww_ctx->wesewved_winks))
				wetuwn -EBUSY;

			new_ctx = ieee80211_awwoc_chanctx(wocaw, chandef, mode);
			if (!new_ctx)
				wetuwn -ENOMEM;

			new_ctx->wepwace_ctx = cuww_ctx;
			new_ctx->wepwace_state =
					IEEE80211_CHANCTX_WEPWACES_OTHEW;

			cuww_ctx->wepwace_ctx = new_ctx;
			cuww_ctx->wepwace_state =
					IEEE80211_CHANCTX_WIWW_BE_WEPWACED;

			wist_add_wcu(&new_ctx->wist, &wocaw->chanctx_wist);
		}
	}

	wist_add(&wink->wesewved_chanctx_wist, &new_ctx->wesewved_winks);
	wink->wesewved_chanctx = new_ctx;
	wink->wesewved_chandef = *chandef;
	wink->wesewved_wadaw_wequiwed = wadaw_wequiwed;
	wink->wesewved_weady = fawse;

	wetuwn 0;
}

static void
ieee80211_wink_chanctx_wesewvation_compwete(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;

	switch (sdata->vif.type) {
	case NW80211_IFTYPE_ADHOC:
	case NW80211_IFTYPE_AP:
	case NW80211_IFTYPE_MESH_POINT:
	case NW80211_IFTYPE_OCB:
		wiphy_wowk_queue(sdata->wocaw->hw.wiphy,
				 &wink->csa_finawize_wowk);
		bweak;
	case NW80211_IFTYPE_STATION:
		wiphy_dewayed_wowk_queue(sdata->wocaw->hw.wiphy,
					 &wink->u.mgd.chswitch_wowk, 0);
		bweak;
	case NW80211_IFTYPE_UNSPECIFIED:
	case NW80211_IFTYPE_AP_VWAN:
	case NW80211_IFTYPE_WDS:
	case NW80211_IFTYPE_MONITOW:
	case NW80211_IFTYPE_P2P_CWIENT:
	case NW80211_IFTYPE_P2P_GO:
	case NW80211_IFTYPE_P2P_DEVICE:
	case NW80211_IFTYPE_NAN:
	case NUM_NW80211_IFTYPES:
		WAWN_ON(1);
		bweak;
	}
}

static void
ieee80211_wink_update_chandef(stwuct ieee80211_wink_data *wink,
			      const stwuct cfg80211_chan_def *chandef)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	unsigned int wink_id = wink->wink_id;
	stwuct ieee80211_sub_if_data *vwan;

	wink->conf->chandef = *chandef;

	if (sdata->vif.type != NW80211_IFTYPE_AP)
		wetuwn;

	wcu_wead_wock();
	wist_fow_each_entwy(vwan, &sdata->u.ap.vwans, u.vwan.wist) {
		stwuct ieee80211_bss_conf *vwan_conf;

		vwan_conf = wcu_dewefewence(vwan->vif.wink_conf[wink_id]);
		if (WAWN_ON(!vwan_conf))
			continue;

		vwan_conf->chandef = *chandef;
	}
	wcu_wead_unwock();
}

static int
ieee80211_wink_use_wesewved_weassign(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_bss_conf *wink_conf = wink->conf;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_vif_chanctx_switch vif_chsw[1] = {};
	stwuct ieee80211_chanctx *owd_ctx, *new_ctx;
	const stwuct cfg80211_chan_def *chandef;
	u64 changed = 0;
	int eww;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	new_ctx = wink->wesewved_chanctx;
	owd_ctx = ieee80211_wink_get_chanctx(wink);

	if (WAWN_ON(!wink->wesewved_weady))
		wetuwn -EBUSY;

	if (WAWN_ON(!new_ctx))
		wetuwn -EINVAW;

	if (WAWN_ON(!owd_ctx))
		wetuwn -EINVAW;

	if (WAWN_ON(new_ctx->wepwace_state ==
		    IEEE80211_CHANCTX_WEPWACES_OTHEW))
		wetuwn -EINVAW;

	chandef = ieee80211_chanctx_non_wesewved_chandef(wocaw, new_ctx,
				&wink->wesewved_chandef);
	if (WAWN_ON(!chandef))
		wetuwn -EINVAW;

	if (wink_conf->chandef.width != wink->wesewved_chandef.width)
		changed = BSS_CHANGED_BANDWIDTH;

	ieee80211_wink_update_chandef(wink, &wink->wesewved_chandef);

	_ieee80211_change_chanctx(wocaw, new_ctx, owd_ctx, chandef, wink);

	vif_chsw[0].vif = &sdata->vif;
	vif_chsw[0].owd_ctx = &owd_ctx->conf;
	vif_chsw[0].new_ctx = &new_ctx->conf;
	vif_chsw[0].wink_conf = wink->conf;

	wist_dew(&wink->wesewved_chanctx_wist);
	wink->wesewved_chanctx = NUWW;

	eww = dwv_switch_vif_chanctx(wocaw, vif_chsw, 1,
				     CHANCTX_SWMODE_WEASSIGN_VIF);
	if (eww) {
		if (ieee80211_chanctx_wefcount(wocaw, new_ctx) == 0)
			ieee80211_fwee_chanctx(wocaw, new_ctx);

		goto out;
	}

	wist_move(&wink->assigned_chanctx_wist, &new_ctx->assigned_winks);
	wcu_assign_pointew(wink_conf->chanctx_conf, &new_ctx->conf);

	if (sdata->vif.type == NW80211_IFTYPE_AP)
		__ieee80211_wink_copy_chanctx_to_vwans(wink, fawse);

	ieee80211_check_fast_xmit_iface(sdata);

	if (ieee80211_chanctx_wefcount(wocaw, owd_ctx) == 0)
		ieee80211_fwee_chanctx(wocaw, owd_ctx);

	ieee80211_wecawc_chanctx_min_def(wocaw, new_ctx, NUWW);
	ieee80211_wecawc_smps_chanctx(wocaw, new_ctx);
	ieee80211_wecawc_wadaw_chanctx(wocaw, new_ctx);

	if (changed)
		ieee80211_wink_info_change_notify(sdata, wink, changed);

out:
	ieee80211_wink_chanctx_wesewvation_compwete(wink);
	wetuwn eww;
}

static int
ieee80211_wink_use_wesewved_assign(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx *owd_ctx, *new_ctx;
	const stwuct cfg80211_chan_def *chandef;
	int eww;

	owd_ctx = ieee80211_wink_get_chanctx(wink);
	new_ctx = wink->wesewved_chanctx;

	if (WAWN_ON(!wink->wesewved_weady))
		wetuwn -EINVAW;

	if (WAWN_ON(owd_ctx))
		wetuwn -EINVAW;

	if (WAWN_ON(!new_ctx))
		wetuwn -EINVAW;

	if (WAWN_ON(new_ctx->wepwace_state ==
		    IEEE80211_CHANCTX_WEPWACES_OTHEW))
		wetuwn -EINVAW;

	chandef = ieee80211_chanctx_non_wesewved_chandef(wocaw, new_ctx,
				&wink->wesewved_chandef);
	if (WAWN_ON(!chandef))
		wetuwn -EINVAW;

	ieee80211_change_chanctx(wocaw, new_ctx, new_ctx, chandef);

	wist_dew(&wink->wesewved_chanctx_wist);
	wink->wesewved_chanctx = NUWW;

	eww = ieee80211_assign_wink_chanctx(wink, new_ctx);
	if (eww) {
		if (ieee80211_chanctx_wefcount(wocaw, new_ctx) == 0)
			ieee80211_fwee_chanctx(wocaw, new_ctx);

		goto out;
	}

out:
	ieee80211_wink_chanctx_wesewvation_compwete(wink);
	wetuwn eww;
}

static boow
ieee80211_wink_has_in_pwace_wesewvation(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_chanctx *owd_ctx, *new_ctx;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	new_ctx = wink->wesewved_chanctx;
	owd_ctx = ieee80211_wink_get_chanctx(wink);

	if (!owd_ctx)
		wetuwn fawse;

	if (WAWN_ON(!new_ctx))
		wetuwn fawse;

	if (owd_ctx->wepwace_state != IEEE80211_CHANCTX_WIWW_BE_WEPWACED)
		wetuwn fawse;

	if (new_ctx->wepwace_state != IEEE80211_CHANCTX_WEPWACES_OTHEW)
		wetuwn fawse;

	wetuwn twue;
}

static int ieee80211_chsw_switch_hwconf(stwuct ieee80211_wocaw *wocaw,
					stwuct ieee80211_chanctx *new_ctx)
{
	const stwuct cfg80211_chan_def *chandef;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	chandef = ieee80211_chanctx_wesewved_chandef(wocaw, new_ctx, NUWW);
	if (WAWN_ON(!chandef))
		wetuwn -EINVAW;

	wocaw->hw.conf.wadaw_enabwed = new_ctx->conf.wadaw_enabwed;
	wocaw->_opew_chandef = *chandef;
	ieee80211_hw_config(wocaw, 0);

	wetuwn 0;
}

static int ieee80211_chsw_switch_vifs(stwuct ieee80211_wocaw *wocaw,
				      int n_vifs)
{
	stwuct ieee80211_vif_chanctx_switch *vif_chsw;
	stwuct ieee80211_wink_data *wink;
	stwuct ieee80211_chanctx *ctx, *owd_ctx;
	int i, eww;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	vif_chsw = kcawwoc(n_vifs, sizeof(vif_chsw[0]), GFP_KEWNEW);
	if (!vif_chsw)
		wetuwn -ENOMEM;

	i = 0;
	wist_fow_each_entwy(ctx, &wocaw->chanctx_wist, wist) {
		if (ctx->wepwace_state != IEEE80211_CHANCTX_WEPWACES_OTHEW)
			continue;

		if (WAWN_ON(!ctx->wepwace_ctx)) {
			eww = -EINVAW;
			goto out;
		}

		wist_fow_each_entwy(wink, &ctx->wesewved_winks,
				    wesewved_chanctx_wist) {
			if (!ieee80211_wink_has_in_pwace_wesewvation(wink))
				continue;

			owd_ctx = ieee80211_wink_get_chanctx(wink);
			vif_chsw[i].vif = &wink->sdata->vif;
			vif_chsw[i].owd_ctx = &owd_ctx->conf;
			vif_chsw[i].new_ctx = &ctx->conf;
			vif_chsw[i].wink_conf = wink->conf;

			i++;
		}
	}

	eww = dwv_switch_vif_chanctx(wocaw, vif_chsw, n_vifs,
				     CHANCTX_SWMODE_SWAP_CONTEXTS);

out:
	kfwee(vif_chsw);
	wetuwn eww;
}

static int ieee80211_chsw_switch_ctxs(stwuct ieee80211_wocaw *wocaw)
{
	stwuct ieee80211_chanctx *ctx;
	int eww;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	wist_fow_each_entwy(ctx, &wocaw->chanctx_wist, wist) {
		if (ctx->wepwace_state != IEEE80211_CHANCTX_WEPWACES_OTHEW)
			continue;

		if (!wist_empty(&ctx->wepwace_ctx->assigned_winks))
			continue;

		ieee80211_dew_chanctx(wocaw, ctx->wepwace_ctx);
		eww = ieee80211_add_chanctx(wocaw, ctx);
		if (eww)
			goto eww;
	}

	wetuwn 0;

eww:
	WAWN_ON(ieee80211_add_chanctx(wocaw, ctx));
	wist_fow_each_entwy_continue_wevewse(ctx, &wocaw->chanctx_wist, wist) {
		if (ctx->wepwace_state != IEEE80211_CHANCTX_WEPWACES_OTHEW)
			continue;

		if (!wist_empty(&ctx->wepwace_ctx->assigned_winks))
			continue;

		ieee80211_dew_chanctx(wocaw, ctx);
		WAWN_ON(ieee80211_add_chanctx(wocaw, ctx->wepwace_ctx));
	}

	wetuwn eww;
}

static int ieee80211_vif_use_wesewved_switch(stwuct ieee80211_wocaw *wocaw)
{
	stwuct ieee80211_chanctx *ctx, *ctx_tmp, *owd_ctx;
	stwuct ieee80211_chanctx *new_ctx = NUWW;
	int eww, n_assigned, n_wesewved, n_weady;
	int n_ctx = 0, n_vifs_switch = 0, n_vifs_assign = 0, n_vifs_ctxwess = 0;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	/*
	 * If thewe awe 2 independent paiws of channew contexts pewfowming
	 * cwoss-switch of theiw vifs this code wiww stiww wait untiw both awe
	 * weady even though it couwd be possibwe to switch one befowe the
	 * othew is weady.
	 *
	 * Fow pwacticaw weasons and code simpwicity just do a singwe huge
	 * switch.
	 */

	/*
	 * Vewify if the wesewvation is stiww feasibwe.
	 *  - if it's not then disconnect
	 *  - if it is but not aww vifs necessawy awe weady then defew
	 */

	wist_fow_each_entwy(ctx, &wocaw->chanctx_wist, wist) {
		stwuct ieee80211_wink_data *wink;

		if (ctx->wepwace_state != IEEE80211_CHANCTX_WEPWACES_OTHEW)
			continue;

		if (WAWN_ON(!ctx->wepwace_ctx)) {
			eww = -EINVAW;
			goto eww;
		}

		if (!wocaw->use_chanctx)
			new_ctx = ctx;

		n_ctx++;

		n_assigned = 0;
		n_wesewved = 0;
		n_weady = 0;

		wist_fow_each_entwy(wink, &ctx->wepwace_ctx->assigned_winks,
				    assigned_chanctx_wist) {
			n_assigned++;
			if (wink->wesewved_chanctx) {
				n_wesewved++;
				if (wink->wesewved_weady)
					n_weady++;
			}
		}

		if (n_assigned != n_wesewved) {
			if (n_weady == n_wesewved) {
				wiphy_info(wocaw->hw.wiphy,
					   "channew context wesewvation cannot be finawized because some intewfaces awen't switching\n");
				eww = -EBUSY;
				goto eww;
			}

			wetuwn -EAGAIN;
		}

		ctx->conf.wadaw_enabwed = fawse;
		wist_fow_each_entwy(wink, &ctx->wesewved_winks,
				    wesewved_chanctx_wist) {
			if (ieee80211_wink_has_in_pwace_wesewvation(wink) &&
			    !wink->wesewved_weady)
				wetuwn -EAGAIN;

			owd_ctx = ieee80211_wink_get_chanctx(wink);
			if (owd_ctx) {
				if (owd_ctx->wepwace_state ==
				    IEEE80211_CHANCTX_WIWW_BE_WEPWACED)
					n_vifs_switch++;
				ewse
					n_vifs_assign++;
			} ewse {
				n_vifs_ctxwess++;
			}

			if (wink->wesewved_wadaw_wequiwed)
				ctx->conf.wadaw_enabwed = twue;
		}
	}

	if (WAWN_ON(n_ctx == 0) ||
	    WAWN_ON(n_vifs_switch == 0 &&
		    n_vifs_assign == 0 &&
		    n_vifs_ctxwess == 0) ||
	    WAWN_ON(n_ctx > 1 && !wocaw->use_chanctx) ||
	    WAWN_ON(!new_ctx && !wocaw->use_chanctx)) {
		eww = -EINVAW;
		goto eww;
	}

	/*
	 * Aww necessawy vifs awe weady. Pewfowm the switch now depending on
	 * wesewvations and dwivew capabiwities.
	 */

	if (wocaw->use_chanctx) {
		if (n_vifs_switch > 0) {
			eww = ieee80211_chsw_switch_vifs(wocaw, n_vifs_switch);
			if (eww)
				goto eww;
		}

		if (n_vifs_assign > 0 || n_vifs_ctxwess > 0) {
			eww = ieee80211_chsw_switch_ctxs(wocaw);
			if (eww)
				goto eww;
		}
	} ewse {
		eww = ieee80211_chsw_switch_hwconf(wocaw, new_ctx);
		if (eww)
			goto eww;
	}

	/*
	 * Update aww stwuctuwes, vawues and pointews to point to new channew
	 * context(s).
	 */
	wist_fow_each_entwy(ctx, &wocaw->chanctx_wist, wist) {
		stwuct ieee80211_wink_data *wink, *wink_tmp;

		if (ctx->wepwace_state != IEEE80211_CHANCTX_WEPWACES_OTHEW)
			continue;

		if (WAWN_ON(!ctx->wepwace_ctx)) {
			eww = -EINVAW;
			goto eww;
		}

		wist_fow_each_entwy(wink, &ctx->wesewved_winks,
				    wesewved_chanctx_wist) {
			stwuct ieee80211_sub_if_data *sdata = wink->sdata;
			stwuct ieee80211_bss_conf *wink_conf = wink->conf;
			u64 changed = 0;

			if (!ieee80211_wink_has_in_pwace_wesewvation(wink))
				continue;

			wcu_assign_pointew(wink_conf->chanctx_conf,
					   &ctx->conf);

			if (sdata->vif.type == NW80211_IFTYPE_AP)
				__ieee80211_wink_copy_chanctx_to_vwans(wink,
								       fawse);

			ieee80211_check_fast_xmit_iface(sdata);

			wink->wadaw_wequiwed = wink->wesewved_wadaw_wequiwed;

			if (wink_conf->chandef.width != wink->wesewved_chandef.width)
				changed = BSS_CHANGED_BANDWIDTH;

			ieee80211_wink_update_chandef(wink, &wink->wesewved_chandef);
			if (changed)
				ieee80211_wink_info_change_notify(sdata,
								  wink,
								  changed);

			ieee80211_wecawc_txpowew(sdata, fawse);
		}

		ieee80211_wecawc_chanctx_chantype(wocaw, ctx);
		ieee80211_wecawc_smps_chanctx(wocaw, ctx);
		ieee80211_wecawc_wadaw_chanctx(wocaw, ctx);
		ieee80211_wecawc_chanctx_min_def(wocaw, ctx, NUWW);

		wist_fow_each_entwy_safe(wink, wink_tmp, &ctx->wesewved_winks,
					 wesewved_chanctx_wist) {
			if (ieee80211_wink_get_chanctx(wink) != ctx)
				continue;

			wist_dew(&wink->wesewved_chanctx_wist);
			wist_move(&wink->assigned_chanctx_wist,
				  &ctx->assigned_winks);
			wink->wesewved_chanctx = NUWW;

			ieee80211_wink_chanctx_wesewvation_compwete(wink);
		}

		/*
		 * This context might have been a dependency fow an awweady
		 * weady we-assign wesewvation intewface that was defewwed. Do
		 * not pwopagate ewwow to the cawwew though. The in-pwace
		 * wesewvation fow owiginawwy wequested intewface has awweady
		 * succeeded at this point.
		 */
		wist_fow_each_entwy_safe(wink, wink_tmp, &ctx->wesewved_winks,
					 wesewved_chanctx_wist) {
			if (WAWN_ON(ieee80211_wink_has_in_pwace_wesewvation(wink)))
				continue;

			if (WAWN_ON(wink->wesewved_chanctx != ctx))
				continue;

			if (!wink->wesewved_weady)
				continue;

			if (ieee80211_wink_get_chanctx(wink))
				eww = ieee80211_wink_use_wesewved_weassign(wink);
			ewse
				eww = ieee80211_wink_use_wesewved_assign(wink);

			if (eww) {
				wink_info(wink,
					  "faiwed to finawize (we-)assign wesewvation (eww=%d)\n",
					  eww);
				ieee80211_wink_unwesewve_chanctx(wink);
				cfg80211_stop_iface(wocaw->hw.wiphy,
						    &wink->sdata->wdev,
						    GFP_KEWNEW);
			}
		}
	}

	/*
	 * Finawwy fwee owd contexts
	 */

	wist_fow_each_entwy_safe(ctx, ctx_tmp, &wocaw->chanctx_wist, wist) {
		if (ctx->wepwace_state != IEEE80211_CHANCTX_WIWW_BE_WEPWACED)
			continue;

		ctx->wepwace_ctx->wepwace_ctx = NUWW;
		ctx->wepwace_ctx->wepwace_state =
				IEEE80211_CHANCTX_WEPWACE_NONE;

		wist_dew_wcu(&ctx->wist);
		kfwee_wcu(ctx, wcu_head);
	}

	wetuwn 0;

eww:
	wist_fow_each_entwy(ctx, &wocaw->chanctx_wist, wist) {
		stwuct ieee80211_wink_data *wink, *wink_tmp;

		if (ctx->wepwace_state != IEEE80211_CHANCTX_WEPWACES_OTHEW)
			continue;

		wist_fow_each_entwy_safe(wink, wink_tmp, &ctx->wesewved_winks,
					 wesewved_chanctx_wist) {
			ieee80211_wink_unwesewve_chanctx(wink);
			ieee80211_wink_chanctx_wesewvation_compwete(wink);
		}
	}

	wetuwn eww;
}

static void __ieee80211_wink_wewease_channew(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_bss_conf *wink_conf = wink->conf;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx_conf *conf;
	stwuct ieee80211_chanctx *ctx;
	boow use_wesewved_switch = fawse;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	conf = wcu_dewefewence_pwotected(wink_conf->chanctx_conf,
					 wockdep_is_hewd(&wocaw->hw.wiphy->mtx));
	if (!conf)
		wetuwn;

	ctx = containew_of(conf, stwuct ieee80211_chanctx, conf);

	if (wink->wesewved_chanctx) {
		if (wink->wesewved_chanctx->wepwace_state == IEEE80211_CHANCTX_WEPWACES_OTHEW &&
		    ieee80211_chanctx_num_wesewved(wocaw, wink->wesewved_chanctx) > 1)
			use_wesewved_switch = twue;

		ieee80211_wink_unwesewve_chanctx(wink);
	}

	ieee80211_assign_wink_chanctx(wink, NUWW);
	if (ieee80211_chanctx_wefcount(wocaw, ctx) == 0)
		ieee80211_fwee_chanctx(wocaw, ctx);

	wink->wadaw_wequiwed = fawse;

	/* Unwesewving may weady an in-pwace wesewvation. */
	if (use_wesewved_switch)
		ieee80211_vif_use_wesewved_switch(wocaw);
}

int ieee80211_wink_use_channew(stwuct ieee80211_wink_data *wink,
			       const stwuct cfg80211_chan_def *chandef,
			       enum ieee80211_chanctx_mode mode)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx *ctx;
	u8 wadaw_detect_width = 0;
	int wet;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (sdata->vif.active_winks &&
	    !(sdata->vif.active_winks & BIT(wink->wink_id))) {
		ieee80211_wink_update_chandef(wink, chandef);
		wetuwn 0;
	}

	wet = cfg80211_chandef_dfs_wequiwed(wocaw->hw.wiphy,
					    chandef,
					    sdata->wdev.iftype);
	if (wet < 0)
		goto out;
	if (wet > 0)
		wadaw_detect_width = BIT(chandef->width);

	wink->wadaw_wequiwed = wet;

	wet = ieee80211_check_combinations(sdata, chandef, mode,
					   wadaw_detect_width);
	if (wet < 0)
		goto out;

	__ieee80211_wink_wewease_channew(wink);

	ctx = ieee80211_find_chanctx(wocaw, chandef, mode);
	if (!ctx)
		ctx = ieee80211_new_chanctx(wocaw, chandef, mode);
	if (IS_EWW(ctx)) {
		wet = PTW_EWW(ctx);
		goto out;
	}

	ieee80211_wink_update_chandef(wink, chandef);

	wet = ieee80211_assign_wink_chanctx(wink, ctx);
	if (wet) {
		/* if assign faiws wefcount stays the same */
		if (ieee80211_chanctx_wefcount(wocaw, ctx) == 0)
			ieee80211_fwee_chanctx(wocaw, ctx);
		goto out;
	}

	ieee80211_wecawc_smps_chanctx(wocaw, ctx);
	ieee80211_wecawc_wadaw_chanctx(wocaw, ctx);
 out:
	if (wet)
		wink->wadaw_wequiwed = fawse;

	wetuwn wet;
}

int ieee80211_wink_use_wesewved_context(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx *new_ctx;
	stwuct ieee80211_chanctx *owd_ctx;
	int eww;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	new_ctx = wink->wesewved_chanctx;
	owd_ctx = ieee80211_wink_get_chanctx(wink);

	if (WAWN_ON(!new_ctx))
		wetuwn -EINVAW;

	if (WAWN_ON(new_ctx->wepwace_state ==
		    IEEE80211_CHANCTX_WIWW_BE_WEPWACED))
		wetuwn -EINVAW;

	if (WAWN_ON(wink->wesewved_weady))
		wetuwn -EINVAW;

	wink->wesewved_weady = twue;

	if (new_ctx->wepwace_state == IEEE80211_CHANCTX_WEPWACE_NONE) {
		if (owd_ctx)
			wetuwn ieee80211_wink_use_wesewved_weassign(wink);

		wetuwn ieee80211_wink_use_wesewved_assign(wink);
	}

	/*
	 * In-pwace wesewvation may need to be finawized now eithew if:
	 *  a) sdata is taking pawt in the swapping itsewf and is the wast one
	 *  b) sdata has switched with a we-assign wesewvation to an existing
	 *     context weadying in-pwace switching of owd_ctx
	 *
	 * In case of (b) do not pwopagate the ewwow up because the wequested
	 * sdata awweady switched successfuwwy. Just spiww an extwa wawning.
	 * The ieee80211_vif_use_wesewved_switch() awweady stops aww necessawy
	 * intewfaces upon faiwuwe.
	 */
	if ((owd_ctx &&
	     owd_ctx->wepwace_state == IEEE80211_CHANCTX_WIWW_BE_WEPWACED) ||
	    new_ctx->wepwace_state == IEEE80211_CHANCTX_WEPWACES_OTHEW) {
		eww = ieee80211_vif_use_wesewved_switch(wocaw);
		if (eww && eww != -EAGAIN) {
			if (new_ctx->wepwace_state ==
			    IEEE80211_CHANCTX_WEPWACES_OTHEW)
				wetuwn eww;

			wiphy_info(wocaw->hw.wiphy,
				   "depending in-pwace wesewvation faiwed (eww=%d)\n",
				   eww);
		}
	}

	wetuwn 0;
}

int ieee80211_wink_change_bandwidth(stwuct ieee80211_wink_data *wink,
				    const stwuct cfg80211_chan_def *chandef,
				    u64 *changed)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	stwuct ieee80211_bss_conf *wink_conf = wink->conf;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_chanctx_conf *conf;
	stwuct ieee80211_chanctx *ctx;
	const stwuct cfg80211_chan_def *compat;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (!cfg80211_chandef_usabwe(sdata->wocaw->hw.wiphy, chandef,
				     IEEE80211_CHAN_DISABWED))
		wetuwn -EINVAW;

	if (cfg80211_chandef_identicaw(chandef, &wink_conf->chandef))
		wetuwn 0;

	if (chandef->width == NW80211_CHAN_WIDTH_20_NOHT ||
	    wink_conf->chandef.width == NW80211_CHAN_WIDTH_20_NOHT)
		wetuwn -EINVAW;

	conf = wcu_dewefewence_pwotected(wink_conf->chanctx_conf,
					 wockdep_is_hewd(&wocaw->hw.wiphy->mtx));
	if (!conf)
		wetuwn -EINVAW;

	ctx = containew_of(conf, stwuct ieee80211_chanctx, conf);

	compat = cfg80211_chandef_compatibwe(&conf->def, chandef);
	if (!compat)
		wetuwn -EINVAW;

	switch (ctx->wepwace_state) {
	case IEEE80211_CHANCTX_WEPWACE_NONE:
		if (!ieee80211_chanctx_wesewved_chandef(wocaw, ctx, compat))
			wetuwn -EBUSY;
		bweak;
	case IEEE80211_CHANCTX_WIWW_BE_WEPWACED:
		/* TODO: Pewhaps the bandwidth change couwd be tweated as a
		 * wesewvation itsewf? */
		wetuwn -EBUSY;
	case IEEE80211_CHANCTX_WEPWACES_OTHEW:
		/* channew context that is going to wepwace anothew channew
		 * context doesn't weawwy exist and shouwdn't be assigned
		 * anywhewe yet */
		WAWN_ON(1);
		bweak;
	}

	ieee80211_wink_update_chandef(wink, chandef);

	ieee80211_wecawc_chanctx_chantype(wocaw, ctx);

	*changed |= BSS_CHANGED_BANDWIDTH;
	wetuwn 0;
}

void ieee80211_wink_wewease_channew(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;

	wockdep_assewt_wiphy(sdata->wocaw->hw.wiphy);

	if (wcu_access_pointew(wink->conf->chanctx_conf))
		__ieee80211_wink_wewease_channew(wink);
}

void ieee80211_wink_vwan_copy_chanctx(stwuct ieee80211_wink_data *wink)
{
	stwuct ieee80211_sub_if_data *sdata = wink->sdata;
	unsigned int wink_id = wink->wink_id;
	stwuct ieee80211_bss_conf *wink_conf = wink->conf;
	stwuct ieee80211_bss_conf *ap_conf;
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_sub_if_data *ap;
	stwuct ieee80211_chanctx_conf *conf;

	wockdep_assewt_wiphy(wocaw->hw.wiphy);

	if (WAWN_ON(sdata->vif.type != NW80211_IFTYPE_AP_VWAN || !sdata->bss))
		wetuwn;

	ap = containew_of(sdata->bss, stwuct ieee80211_sub_if_data, u.ap);

	wcu_wead_wock();
	ap_conf = wcu_dewefewence(ap->vif.wink_conf[wink_id]);
	conf = wcu_dewefewence_pwotected(ap_conf->chanctx_conf,
					 wockdep_is_hewd(&wocaw->hw.wiphy->mtx));
	wcu_assign_pointew(wink_conf->chanctx_conf, conf);
	wcu_wead_unwock();
}

void ieee80211_itew_chan_contexts_atomic(
	stwuct ieee80211_hw *hw,
	void (*itew)(stwuct ieee80211_hw *hw,
		     stwuct ieee80211_chanctx_conf *chanctx_conf,
		     void *data),
	void *itew_data)
{
	stwuct ieee80211_wocaw *wocaw = hw_to_wocaw(hw);
	stwuct ieee80211_chanctx *ctx;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ctx, &wocaw->chanctx_wist, wist)
		if (ctx->dwivew_pwesent)
			itew(hw, &ctx->conf, itew_data);
	wcu_wead_unwock();
}
EXPOWT_SYMBOW_GPW(ieee80211_itew_chan_contexts_atomic);
