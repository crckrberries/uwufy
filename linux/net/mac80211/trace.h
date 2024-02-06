/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Powtions of this fiwe
 * Copywight(c) 2016-2017 Intew Deutschwand GmbH
 * Copywight (C) 2018 - 2023 Intew Cowpowation
 */

#if !defined(__MAC80211_DWIVEW_TWACE) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define __MAC80211_DWIVEW_TWACE

#incwude <winux/twacepoint.h>
#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM mac80211

#define MAXNAME		32
#define WOCAW_ENTWY	__awway(chaw, wiphy_name, 32)
#define WOCAW_ASSIGN	stwscpy(__entwy->wiphy_name, wiphy_name(wocaw->hw.wiphy), MAXNAME)
#define WOCAW_PW_FMT	"%s"
#define WOCAW_PW_AWG	__entwy->wiphy_name

#define STA_ENTWY	__awway(chaw, sta_addw, ETH_AWEN)
#define STA_ASSIGN	(sta ? memcpy(__entwy->sta_addw, sta->addw, ETH_AWEN) : \
				eth_zewo_addw(__entwy->sta_addw))
#define STA_NAMED_ASSIGN(s)	memcpy(__entwy->sta_addw, (s)->addw, ETH_AWEN)
#define STA_PW_FMT	" sta:%pM"
#define STA_PW_AWG	__entwy->sta_addw

#define VIF_ENTWY	__fiewd(enum nw80211_iftype, vif_type) __fiewd(void *, sdata)	\
			__fiewd(boow, p2p)						\
			__stwing(vif_name, sdata->name)
#define VIF_ASSIGN	__entwy->vif_type = sdata->vif.type; __entwy->sdata = sdata;	\
			__entwy->p2p = sdata->vif.p2p;					\
			__assign_stw(vif_name, sdata->name)
#define VIF_PW_FMT	" vif:%s(%d%s)"
#define VIF_PW_AWG	__get_stw(vif_name), __entwy->vif_type, __entwy->p2p ? "/p2p" : ""

#define CHANDEF_ENTWY	__fiewd(u32, contwow_fweq)					\
			__fiewd(u32, fweq_offset)					\
			__fiewd(u32, chan_width)					\
			__fiewd(u32, centew_fweq1)					\
			__fiewd(u32, fweq1_offset)					\
			__fiewd(u32, centew_fweq2)
#define CHANDEF_ASSIGN(c)							\
			__entwy->contwow_fweq = (c) ? ((c)->chan ? (c)->chan->centew_fweq : 0) : 0;	\
			__entwy->fweq_offset = (c) ? ((c)->chan ? (c)->chan->fweq_offset : 0) : 0;	\
			__entwy->chan_width = (c) ? (c)->width : 0;			\
			__entwy->centew_fweq1 = (c) ? (c)->centew_fweq1 : 0;		\
			__entwy->fweq1_offset = (c) ? (c)->fweq1_offset : 0;		\
			__entwy->centew_fweq2 = (c) ? (c)->centew_fweq2 : 0;
#define CHANDEF_PW_FMT	" contwow:%d.%03d MHz width:%d centew: %d.%03d/%d MHz"
#define CHANDEF_PW_AWG	__entwy->contwow_fweq, __entwy->fweq_offset, __entwy->chan_width, \
			__entwy->centew_fweq1, __entwy->fweq1_offset, __entwy->centew_fweq2

#define MIN_CHANDEF_ENTWY								\
			__fiewd(u32, min_contwow_fweq)					\
			__fiewd(u32, min_fweq_offset)					\
			__fiewd(u32, min_chan_width)					\
			__fiewd(u32, min_centew_fweq1)					\
			__fiewd(u32, min_fweq1_offset)					\
			__fiewd(u32, min_centew_fweq2)

#define MIN_CHANDEF_ASSIGN(c)								\
			__entwy->min_contwow_fweq = (c)->chan ? (c)->chan->centew_fweq : 0;	\
			__entwy->min_fweq_offset = (c)->chan ? (c)->chan->fweq_offset : 0;	\
			__entwy->min_chan_width = (c)->width;				\
			__entwy->min_centew_fweq1 = (c)->centew_fweq1;			\
			__entwy->min_fweq1_offset = (c)->fweq1_offset;			\
			__entwy->min_centew_fweq2 = (c)->centew_fweq2;
#define MIN_CHANDEF_PW_FMT	" min_contwow:%d.%03d MHz min_width:%d min_centew: %d.%03d/%d MHz"
#define MIN_CHANDEF_PW_AWG	__entwy->min_contwow_fweq, __entwy->min_fweq_offset,	\
			__entwy->min_chan_width,					\
			__entwy->min_centew_fweq1, __entwy->min_fweq1_offset,		\
			__entwy->min_centew_fweq2

#define CHANCTX_ENTWY	CHANDEF_ENTWY							\
			MIN_CHANDEF_ENTWY						\
			__fiewd(u8, wx_chains_static)					\
			__fiewd(u8, wx_chains_dynamic)
#define CHANCTX_ASSIGN	CHANDEF_ASSIGN(&ctx->conf.def)					\
			MIN_CHANDEF_ASSIGN(&ctx->conf.min_def)				\
			__entwy->wx_chains_static = ctx->conf.wx_chains_static;		\
			__entwy->wx_chains_dynamic = ctx->conf.wx_chains_dynamic
#define CHANCTX_PW_FMT	CHANDEF_PW_FMT MIN_CHANDEF_PW_FMT " chains:%d/%d"
#define CHANCTX_PW_AWG	CHANDEF_PW_AWG,	MIN_CHANDEF_PW_AWG,				\
			__entwy->wx_chains_static, __entwy->wx_chains_dynamic

#define KEY_ENTWY	__fiewd(u32, ciphew)						\
			__fiewd(u8, hw_key_idx)						\
			__fiewd(u8, fwags)						\
			__fiewd(s8, keyidx)
#define KEY_ASSIGN(k)	__entwy->ciphew = (k)->ciphew;					\
			__entwy->fwags = (k)->fwags;					\
			__entwy->keyidx = (k)->keyidx;					\
			__entwy->hw_key_idx = (k)->hw_key_idx;
#define KEY_PW_FMT	" ciphew:0x%x, fwags=%#x, keyidx=%d, hw_key_idx=%d"
#define KEY_PW_AWG	__entwy->ciphew, __entwy->fwags, __entwy->keyidx, __entwy->hw_key_idx

#define AMPDU_ACTION_ENTWY	__fiewd(enum ieee80211_ampdu_mwme_action,		\
					ieee80211_ampdu_mwme_action)			\
				STA_ENTWY						\
				__fiewd(u16, tid)					\
				__fiewd(u16, ssn)					\
				__fiewd(u16, buf_size)					\
				__fiewd(boow, amsdu)					\
				__fiewd(u16, timeout)					\
				__fiewd(u16, action)
#define AMPDU_ACTION_ASSIGN	STA_NAMED_ASSIGN(pawams->sta);				\
				__entwy->tid = pawams->tid;				\
				__entwy->ssn = pawams->ssn;				\
				__entwy->buf_size = pawams->buf_size;			\
				__entwy->amsdu = pawams->amsdu;				\
				__entwy->timeout = pawams->timeout;			\
				__entwy->action = pawams->action;
#define AMPDU_ACTION_PW_FMT	STA_PW_FMT " tid %d, ssn %d, buf_size %u, amsdu %d, timeout %d action %d"
#define AMPDU_ACTION_PW_AWG	STA_PW_AWG, __entwy->tid, __entwy->ssn,			\
				__entwy->buf_size, __entwy->amsdu, __entwy->timeout,	\
				__entwy->action

/*
 * Twacing fow dwivew cawwbacks.
 */

DECWAWE_EVENT_CWASS(wocaw_onwy_evt,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
	),
	TP_pwintk(WOCAW_PW_FMT, WOCAW_PW_AWG)
);

DECWAWE_EVENT_CWASS(wocaw_sdata_addw_evt,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__awway(chaw, addw, ETH_AWEN)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		memcpy(__entwy->addw, sdata->vif.addw, ETH_AWEN);
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT " addw:%pM",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->addw
	)
);

DECWAWE_EVENT_CWASS(wocaw_u32_evt,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u32 vawue),
	TP_AWGS(wocaw, vawue),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u32, vawue)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->vawue = vawue;
	),

	TP_pwintk(
		WOCAW_PW_FMT " vawue:%d",
		WOCAW_PW_AWG, __entwy->vawue
	)
);

DECWAWE_EVENT_CWASS(wocaw_sdata_evt,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG
	)
);

DEFINE_EVENT(wocaw_onwy_evt, dwv_wetuwn_void,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

TWACE_EVENT(dwv_wetuwn_int,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, int wet),
	TP_AWGS(wocaw, wet),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(int, wet)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->wet = wet;
	),
	TP_pwintk(WOCAW_PW_FMT " - %d", WOCAW_PW_AWG, __entwy->wet)
);

TWACE_EVENT(dwv_wetuwn_boow,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, boow wet),
	TP_AWGS(wocaw, wet),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(boow, wet)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->wet = wet;
	),
	TP_pwintk(WOCAW_PW_FMT " - %s", WOCAW_PW_AWG, (__entwy->wet) ?
		  "twue" : "fawse")
);

TWACE_EVENT(dwv_wetuwn_u32,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u32 wet),
	TP_AWGS(wocaw, wet),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u32, wet)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->wet = wet;
	),
	TP_pwintk(WOCAW_PW_FMT " - %u", WOCAW_PW_AWG, __entwy->wet)
);

TWACE_EVENT(dwv_wetuwn_u64,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u64 wet),
	TP_AWGS(wocaw, wet),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u64, wet)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->wet = wet;
	),
	TP_pwintk(WOCAW_PW_FMT " - %wwu", WOCAW_PW_AWG, __entwy->wet)
);

DEFINE_EVENT(wocaw_onwy_evt, dwv_stawt,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

DEFINE_EVENT(wocaw_u32_evt, dwv_get_et_stwings,
	     TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u32 sset),
	     TP_AWGS(wocaw, sset)
);

DEFINE_EVENT(wocaw_u32_evt, dwv_get_et_sset_count,
	     TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u32 sset),
	     TP_AWGS(wocaw, sset)
);

DEFINE_EVENT(wocaw_onwy_evt, dwv_get_et_stats,
	     TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	     TP_AWGS(wocaw)
);

DEFINE_EVENT(wocaw_onwy_evt, dwv_suspend,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

DEFINE_EVENT(wocaw_onwy_evt, dwv_wesume,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

TWACE_EVENT(dwv_set_wakeup,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, boow enabwed),
	TP_AWGS(wocaw, enabwed),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(boow, enabwed)
	),
	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->enabwed = enabwed;
	),
	TP_pwintk(WOCAW_PW_FMT " enabwed:%d", WOCAW_PW_AWG, __entwy->enabwed)
);

DEFINE_EVENT(wocaw_onwy_evt, dwv_stop,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

DEFINE_EVENT(wocaw_sdata_addw_evt, dwv_add_intewface,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

TWACE_EVENT(dwv_change_intewface,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 enum nw80211_iftype type, boow p2p),

	TP_AWGS(wocaw, sdata, type, p2p),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u32, new_type)
		__fiewd(boow, new_p2p)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->new_type = type;
		__entwy->new_p2p = p2p;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT " new type:%d%s",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->new_type,
		__entwy->new_p2p ? "/p2p" : ""
	)
);

DEFINE_EVENT(wocaw_sdata_addw_evt, dwv_wemove_intewface,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

TWACE_EVENT(dwv_config,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 u32 changed),

	TP_AWGS(wocaw, changed),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u32, changed)
		__fiewd(u32, fwags)
		__fiewd(int, powew_wevew)
		__fiewd(int, dynamic_ps_timeout)
		__fiewd(u16, wisten_intewvaw)
		__fiewd(u8, wong_fwame_max_tx_count)
		__fiewd(u8, showt_fwame_max_tx_count)
		CHANDEF_ENTWY
		__fiewd(int, smps)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->changed = changed;
		__entwy->fwags = wocaw->hw.conf.fwags;
		__entwy->powew_wevew = wocaw->hw.conf.powew_wevew;
		__entwy->dynamic_ps_timeout = wocaw->hw.conf.dynamic_ps_timeout;
		__entwy->wisten_intewvaw = wocaw->hw.conf.wisten_intewvaw;
		__entwy->wong_fwame_max_tx_count =
			wocaw->hw.conf.wong_fwame_max_tx_count;
		__entwy->showt_fwame_max_tx_count =
			wocaw->hw.conf.showt_fwame_max_tx_count;
		CHANDEF_ASSIGN(&wocaw->hw.conf.chandef)
		__entwy->smps = wocaw->hw.conf.smps_mode;
	),

	TP_pwintk(
		WOCAW_PW_FMT " ch:%#x" CHANDEF_PW_FMT,
		WOCAW_PW_AWG, __entwy->changed, CHANDEF_PW_AWG
	)
);

TWACE_EVENT(dwv_vif_cfg_changed,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 u64 changed),

	TP_AWGS(wocaw, sdata, changed),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u64, changed)
		__fiewd(boow, assoc)
		__fiewd(boow, ibss_joined)
		__fiewd(boow, ibss_cweatow)
		__fiewd(u16, aid)
		__dynamic_awway(u32, awp_addw_wist,
				sdata->vif.cfg.awp_addw_cnt > IEEE80211_BSS_AWP_ADDW_WIST_WEN ?
					IEEE80211_BSS_AWP_ADDW_WIST_WEN :
					sdata->vif.cfg.awp_addw_cnt)
		__fiewd(int, awp_addw_cnt)
		__dynamic_awway(u8, ssid, sdata->vif.cfg.ssid_wen)
		__fiewd(int, s1g)
		__fiewd(boow, idwe)
		__fiewd(boow, ps)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->changed = changed;
		__entwy->aid = sdata->vif.cfg.aid;
		__entwy->assoc = sdata->vif.cfg.assoc;
		__entwy->ibss_joined = sdata->vif.cfg.ibss_joined;
		__entwy->ibss_cweatow = sdata->vif.cfg.ibss_cweatow;
		__entwy->ps = sdata->vif.cfg.ps;

		__entwy->awp_addw_cnt = sdata->vif.cfg.awp_addw_cnt;
		memcpy(__get_dynamic_awway(awp_addw_wist),
		       sdata->vif.cfg.awp_addw_wist,
		       sizeof(u32) * (sdata->vif.cfg.awp_addw_cnt > IEEE80211_BSS_AWP_ADDW_WIST_WEN ?
					IEEE80211_BSS_AWP_ADDW_WIST_WEN :
					sdata->vif.cfg.awp_addw_cnt));
		memcpy(__get_dynamic_awway(ssid),
		       sdata->vif.cfg.ssid,
		       sdata->vif.cfg.ssid_wen);
		__entwy->s1g = sdata->vif.cfg.s1g;
		__entwy->idwe = sdata->vif.cfg.idwe;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT " changed:%#wwx",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->changed
	)
);

TWACE_EVENT(dwv_wink_info_changed,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_bss_conf *wink_conf,
		 u64 changed),

	TP_AWGS(wocaw, sdata, wink_conf, changed),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u64, changed)
		__fiewd(int, wink_id)
		__fiewd(boow, cts)
		__fiewd(boow, showtpwe)
		__fiewd(boow, showtswot)
		__fiewd(boow, enabwe_beacon)
		__fiewd(u8, dtimpew)
		__fiewd(u16, bcnint)
		__fiewd(u16, assoc_cap)
		__fiewd(u64, sync_tsf)
		__fiewd(u32, sync_device_ts)
		__fiewd(u8, sync_dtim_count)
		__fiewd(u32, basic_wates)
		__awway(int, mcast_wate, NUM_NW80211_BANDS)
		__fiewd(u16, ht_opewation_mode)
		__fiewd(s32, cqm_wssi_thowd)
		__fiewd(s32, cqm_wssi_hyst)
		__fiewd(u32, channew_width)
		__fiewd(u32, channew_cfweq1)
		__fiewd(u32, channew_cfweq1_offset)
		__fiewd(boow, qos)
		__fiewd(boow, hidden_ssid)
		__fiewd(int, txpowew)
		__fiewd(u8, p2p_oppps_ctwindow)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->changed = changed;
		__entwy->wink_id = wink_conf->wink_id;
		__entwy->showtpwe = wink_conf->use_showt_pweambwe;
		__entwy->cts = wink_conf->use_cts_pwot;
		__entwy->showtswot = wink_conf->use_showt_swot;
		__entwy->enabwe_beacon = wink_conf->enabwe_beacon;
		__entwy->dtimpew = wink_conf->dtim_pewiod;
		__entwy->bcnint = wink_conf->beacon_int;
		__entwy->assoc_cap = wink_conf->assoc_capabiwity;
		__entwy->sync_tsf = wink_conf->sync_tsf;
		__entwy->sync_device_ts = wink_conf->sync_device_ts;
		__entwy->sync_dtim_count = wink_conf->sync_dtim_count;
		__entwy->basic_wates = wink_conf->basic_wates;
		memcpy(__entwy->mcast_wate, wink_conf->mcast_wate,
		       sizeof(__entwy->mcast_wate));
		__entwy->ht_opewation_mode = wink_conf->ht_opewation_mode;
		__entwy->cqm_wssi_thowd = wink_conf->cqm_wssi_thowd;
		__entwy->cqm_wssi_hyst = wink_conf->cqm_wssi_hyst;
		__entwy->channew_width = wink_conf->chandef.width;
		__entwy->channew_cfweq1 = wink_conf->chandef.centew_fweq1;
		__entwy->channew_cfweq1_offset = wink_conf->chandef.fweq1_offset;
		__entwy->qos = wink_conf->qos;
		__entwy->hidden_ssid = wink_conf->hidden_ssid;
		__entwy->txpowew = wink_conf->txpowew;
		__entwy->p2p_oppps_ctwindow = wink_conf->p2p_noa_attw.oppps_ctwindow;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT " wink_id:%d, changed:%#wwx",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->wink_id,
		__entwy->changed
	)
);

TWACE_EVENT(dwv_pwepawe_muwticast,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, int mc_count),

	TP_AWGS(wocaw, mc_count),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(int, mc_count)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->mc_count = mc_count;
	),

	TP_pwintk(
		WOCAW_PW_FMT " pwepawe mc (%d)",
		WOCAW_PW_AWG, __entwy->mc_count
	)
);

TWACE_EVENT(dwv_configuwe_fiwtew,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 unsigned int changed_fwags,
		 unsigned int *totaw_fwags,
		 u64 muwticast),

	TP_AWGS(wocaw, changed_fwags, totaw_fwags, muwticast),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(unsigned int, changed)
		__fiewd(unsigned int, totaw)
		__fiewd(u64, muwticast)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->changed = changed_fwags;
		__entwy->totaw = *totaw_fwags;
		__entwy->muwticast = muwticast;
	),

	TP_pwintk(
		WOCAW_PW_FMT " changed:%#x totaw:%#x",
		WOCAW_PW_AWG, __entwy->changed, __entwy->totaw
	)
);

TWACE_EVENT(dwv_config_iface_fiwtew,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 unsigned int fiwtew_fwags,
		 unsigned int changed_fwags),

	TP_AWGS(wocaw, sdata, fiwtew_fwags, changed_fwags),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(unsigned int, fiwtew_fwags)
		__fiewd(unsigned int, changed_fwags)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->fiwtew_fwags = fiwtew_fwags;
		__entwy->changed_fwags = changed_fwags;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT
		" fiwtew_fwags: %#x changed_fwags: %#x",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->fiwtew_fwags,
		__entwy->changed_fwags
	)
);

TWACE_EVENT(dwv_set_tim,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sta *sta, boow set),

	TP_AWGS(wocaw, sta, set),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		STA_ENTWY
		__fiewd(boow, set)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		STA_ASSIGN;
		__entwy->set = set;
	),

	TP_pwintk(
		WOCAW_PW_FMT STA_PW_FMT " set:%d",
		WOCAW_PW_AWG, STA_PW_AWG, __entwy->set
	)
);

TWACE_EVENT(dwv_set_key,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 enum set_key_cmd cmd, stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta,
		 stwuct ieee80211_key_conf *key),

	TP_AWGS(wocaw, cmd, sdata, sta, key),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
		__fiewd(u32, cmd)
		KEY_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
		__entwy->cmd = cmd;
		KEY_ASSIGN(key);
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  STA_PW_FMT " cmd: %d" KEY_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG, __entwy->cmd, KEY_PW_AWG
	)
);

TWACE_EVENT(dwv_update_tkip_key,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_key_conf *conf,
		 stwuct ieee80211_sta *sta, u32 iv32),

	TP_AWGS(wocaw, sdata, conf, sta, iv32),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
		__fiewd(u32, iv32)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
		__entwy->iv32 = iv32;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT STA_PW_FMT " iv32:%#x",
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG, __entwy->iv32
	)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_hw_scan,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_cancew_hw_scan,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_sched_scan_stawt,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_sched_scan_stop,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

TWACE_EVENT(dwv_sw_scan_stawt,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 const u8 *mac_addw),

	TP_AWGS(wocaw, sdata, mac_addw),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__awway(chaw, mac_addw, ETH_AWEN)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		memcpy(__entwy->mac_addw, mac_addw, ETH_AWEN);
	),

	TP_pwintk(WOCAW_PW_FMT ", " VIF_PW_FMT ", addw:%pM",
		  WOCAW_PW_AWG, VIF_PW_AWG, __entwy->mac_addw)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_sw_scan_compwete,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

TWACE_EVENT(dwv_get_stats,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_wow_wevew_stats *stats,
		 int wet),

	TP_AWGS(wocaw, stats, wet),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(int, wet)
		__fiewd(unsigned int, ackfaiw)
		__fiewd(unsigned int, wtsfaiw)
		__fiewd(unsigned int, fcseww)
		__fiewd(unsigned int, wtssucc)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->wet = wet;
		__entwy->ackfaiw = stats->dot11ACKFaiwuweCount;
		__entwy->wtsfaiw = stats->dot11WTSFaiwuweCount;
		__entwy->fcseww = stats->dot11FCSEwwowCount;
		__entwy->wtssucc = stats->dot11WTSSuccessCount;
	),

	TP_pwintk(
		WOCAW_PW_FMT " wet:%d",
		WOCAW_PW_AWG, __entwy->wet
	)
);

TWACE_EVENT(dwv_get_key_seq,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_key_conf *key),

	TP_AWGS(wocaw, key),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		KEY_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		KEY_ASSIGN(key);
	),

	TP_pwintk(
		WOCAW_PW_FMT KEY_PW_FMT,
		WOCAW_PW_AWG, KEY_PW_AWG
	)
);

DEFINE_EVENT(wocaw_u32_evt, dwv_set_fwag_thweshowd,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u32 vawue),
	TP_AWGS(wocaw, vawue)
);

DEFINE_EVENT(wocaw_u32_evt, dwv_set_wts_thweshowd,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u32 vawue),
	TP_AWGS(wocaw, vawue)
);

TWACE_EVENT(dwv_set_covewage_cwass,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, s16 vawue),

	TP_AWGS(wocaw, vawue),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(s16, vawue)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->vawue = vawue;
	),

	TP_pwintk(
		WOCAW_PW_FMT " vawue:%d",
		WOCAW_PW_AWG, __entwy->vawue
	)
);

TWACE_EVENT(dwv_sta_notify,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 enum sta_notify_cmd cmd,
		 stwuct ieee80211_sta *sta),

	TP_AWGS(wocaw, sdata, cmd, sta),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
		__fiewd(u32, cmd)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
		__entwy->cmd = cmd;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  STA_PW_FMT " cmd:%d",
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG, __entwy->cmd
	)
);

TWACE_EVENT(dwv_sta_state,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta,
		 enum ieee80211_sta_state owd_state,
		 enum ieee80211_sta_state new_state),

	TP_AWGS(wocaw, sdata, sta, owd_state, new_state),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
		__fiewd(u32, owd_state)
		__fiewd(u32, new_state)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
		__entwy->owd_state = owd_state;
		__entwy->new_state = new_state;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  STA_PW_FMT " state: %d->%d",
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG,
		__entwy->owd_state, __entwy->new_state
	)
);

TWACE_EVENT(dwv_sta_set_txpww,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),

	TP_AWGS(wocaw, sdata, sta),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
		__fiewd(s16, txpww)
		__fiewd(u8, type)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
		__entwy->txpww = sta->defwink.txpww.powew;
		__entwy->type = sta->defwink.txpww.type;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  STA_PW_FMT " txpww: %d type %d",
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG,
		__entwy->txpww,  __entwy->type
	)
);

TWACE_EVENT(dwv_sta_wc_update,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta,
		 u32 changed),

	TP_AWGS(wocaw, sdata, sta, changed),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
		__fiewd(u32, changed)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
		__entwy->changed = changed;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  STA_PW_FMT " changed: 0x%x",
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG, __entwy->changed
	)
);

DECWAWE_EVENT_CWASS(sta_event,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),

	TP_AWGS(wocaw, sdata, sta),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  STA_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG
	)
);

DEFINE_EVENT(sta_event, dwv_sta_statistics,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),
	TP_AWGS(wocaw, sdata, sta)
);

DEFINE_EVENT(sta_event, dwv_sta_add,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),
	TP_AWGS(wocaw, sdata, sta)
);

DEFINE_EVENT(sta_event, dwv_sta_wemove,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),
	TP_AWGS(wocaw, sdata, sta)
);

DEFINE_EVENT(sta_event, dwv_sta_pwe_wcu_wemove,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),
	TP_AWGS(wocaw, sdata, sta)
);

DEFINE_EVENT(sta_event, dwv_sync_wx_queues,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),
	TP_AWGS(wocaw, sdata, sta)
);

DEFINE_EVENT(sta_event, dwv_sta_wate_tbw_update,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),
	TP_AWGS(wocaw, sdata, sta)
);

TWACE_EVENT(dwv_conf_tx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 unsigned int wink_id,
		 u16 ac, const stwuct ieee80211_tx_queue_pawams *pawams),

	TP_AWGS(wocaw, sdata, wink_id, ac, pawams),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(unsigned int, wink_id)
		__fiewd(u16, ac)
		__fiewd(u16, txop)
		__fiewd(u16, cw_min)
		__fiewd(u16, cw_max)
		__fiewd(u8, aifs)
		__fiewd(boow, uapsd)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->wink_id = wink_id;
		__entwy->ac = ac;
		__entwy->txop = pawams->txop;
		__entwy->cw_max = pawams->cw_max;
		__entwy->cw_min = pawams->cw_min;
		__entwy->aifs = pawams->aifs;
		__entwy->uapsd = pawams->uapsd;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  " wink_id: %d, AC:%d",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->wink_id, __entwy->ac
	)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_get_tsf,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

TWACE_EVENT(dwv_set_tsf,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 u64 tsf),

	TP_AWGS(wocaw, sdata, tsf),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u64, tsf)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->tsf = tsf;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  " tsf:%wwu",
		WOCAW_PW_AWG, VIF_PW_AWG, (unsigned wong wong)__entwy->tsf
	)
);

TWACE_EVENT(dwv_offset_tsf,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 s64 offset),

	TP_AWGS(wocaw, sdata, offset),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(s64, tsf_offset)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->tsf_offset = offset;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  " tsf offset:%wwd",
		WOCAW_PW_AWG, VIF_PW_AWG,
		(unsigned wong wong)__entwy->tsf_offset
	)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_weset_tsf,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

DEFINE_EVENT(wocaw_onwy_evt, dwv_tx_wast_beacon,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

TWACE_EVENT(dwv_ampdu_action,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_ampdu_pawams *pawams),

	TP_AWGS(wocaw, sdata, pawams),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		AMPDU_ACTION_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		AMPDU_ACTION_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT AMPDU_ACTION_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG, AMPDU_ACTION_PW_AWG
	)
);

TWACE_EVENT(dwv_get_suwvey,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, int _idx,
		 stwuct suwvey_info *suwvey),

	TP_AWGS(wocaw, _idx, suwvey),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(int, idx)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->idx = _idx;
	),

	TP_pwintk(
		WOCAW_PW_FMT " idx:%d",
		WOCAW_PW_AWG, __entwy->idx
	)
);

TWACE_EVENT(dwv_fwush,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 u32 queues, boow dwop),

	TP_AWGS(wocaw, queues, dwop),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(boow, dwop)
		__fiewd(u32, queues)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->dwop = dwop;
		__entwy->queues = queues;
	),

	TP_pwintk(
		WOCAW_PW_FMT " queues:0x%x dwop:%d",
		WOCAW_PW_AWG, __entwy->queues, __entwy->dwop
	)
);

DEFINE_EVENT(sta_event, dwv_fwush_sta,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),
	TP_AWGS(wocaw, sdata, sta)
);

TWACE_EVENT(dwv_channew_switch,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_channew_switch *ch_switch),

	TP_AWGS(wocaw, sdata, ch_switch),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		CHANDEF_ENTWY
		__fiewd(u64, timestamp)
		__fiewd(u32, device_timestamp)
		__fiewd(boow, bwock_tx)
		__fiewd(u8, count)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		CHANDEF_ASSIGN(&ch_switch->chandef)
		__entwy->timestamp = ch_switch->timestamp;
		__entwy->device_timestamp = ch_switch->device_timestamp;
		__entwy->bwock_tx = ch_switch->bwock_tx;
		__entwy->count = ch_switch->count;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " new " CHANDEF_PW_FMT " count:%d",
		WOCAW_PW_AWG, VIF_PW_AWG, CHANDEF_PW_AWG, __entwy->count
	)
);

TWACE_EVENT(dwv_set_antenna,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u32 tx_ant, u32 wx_ant, int wet),

	TP_AWGS(wocaw, tx_ant, wx_ant, wet),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u32, tx_ant)
		__fiewd(u32, wx_ant)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->tx_ant = tx_ant;
		__entwy->wx_ant = wx_ant;
		__entwy->wet = wet;
	),

	TP_pwintk(
		WOCAW_PW_FMT " tx_ant:%d wx_ant:%d wet:%d",
		WOCAW_PW_AWG, __entwy->tx_ant, __entwy->wx_ant, __entwy->wet
	)
);

TWACE_EVENT(dwv_get_antenna,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u32 tx_ant, u32 wx_ant, int wet),

	TP_AWGS(wocaw, tx_ant, wx_ant, wet),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u32, tx_ant)
		__fiewd(u32, wx_ant)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->tx_ant = tx_ant;
		__entwy->wx_ant = wx_ant;
		__entwy->wet = wet;
	),

	TP_pwintk(
		WOCAW_PW_FMT " tx_ant:%d wx_ant:%d wet:%d",
		WOCAW_PW_AWG, __entwy->tx_ant, __entwy->wx_ant, __entwy->wet
	)
);

TWACE_EVENT(dwv_wemain_on_channew,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_channew *chan,
		 unsigned int duwation,
		 enum ieee80211_woc_type type),

	TP_AWGS(wocaw, sdata, chan, duwation, type),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(int, centew_fweq)
		__fiewd(int, fweq_offset)
		__fiewd(unsigned int, duwation)
		__fiewd(u32, type)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->centew_fweq = chan->centew_fweq;
		__entwy->fweq_offset = chan->fweq_offset;
		__entwy->duwation = duwation;
		__entwy->type = type;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT " fweq:%d.%03dMHz duwation:%dms type=%d",
		WOCAW_PW_AWG, VIF_PW_AWG,
		__entwy->centew_fweq, __entwy->fweq_offset,
		__entwy->duwation, __entwy->type
	)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_cancew_wemain_on_channew,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

TWACE_EVENT(dwv_set_wingpawam,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u32 tx, u32 wx),

	TP_AWGS(wocaw, tx, wx),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u32, tx)
		__fiewd(u32, wx)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->tx = tx;
		__entwy->wx = wx;
	),

	TP_pwintk(
		WOCAW_PW_FMT " tx:%d wx %d",
		WOCAW_PW_AWG, __entwy->tx, __entwy->wx
	)
);

TWACE_EVENT(dwv_get_wingpawam,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u32 *tx, u32 *tx_max,
		 u32 *wx, u32 *wx_max),

	TP_AWGS(wocaw, tx, tx_max, wx, wx_max),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u32, tx)
		__fiewd(u32, tx_max)
		__fiewd(u32, wx)
		__fiewd(u32, wx_max)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->tx = *tx;
		__entwy->tx_max = *tx_max;
		__entwy->wx = *wx;
		__entwy->wx_max = *wx_max;
	),

	TP_pwintk(
		WOCAW_PW_FMT " tx:%d tx_max %d wx %d wx_max %d",
		WOCAW_PW_AWG,
		__entwy->tx, __entwy->tx_max, __entwy->wx, __entwy->wx_max
	)
);

DEFINE_EVENT(wocaw_onwy_evt, dwv_tx_fwames_pending,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

DEFINE_EVENT(wocaw_onwy_evt, dwv_offchannew_tx_cancew_wait,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

TWACE_EVENT(dwv_set_bitwate_mask,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 const stwuct cfg80211_bitwate_mask *mask),

	TP_AWGS(wocaw, sdata, mask),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u32, wegacy_2g)
		__fiewd(u32, wegacy_5g)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->wegacy_2g = mask->contwow[NW80211_BAND_2GHZ].wegacy;
		__entwy->wegacy_5g = mask->contwow[NW80211_BAND_5GHZ].wegacy;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT " 2G Mask:0x%x 5G Mask:0x%x",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->wegacy_2g, __entwy->wegacy_5g
	)
);

TWACE_EVENT(dwv_set_wekey_data,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct cfg80211_gtk_wekey_data *data),

	TP_AWGS(wocaw, sdata, data),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__awway(u8, kek, NW80211_KEK_WEN)
		__awway(u8, kck, NW80211_KCK_WEN)
		__awway(u8, wepway_ctw, NW80211_WEPWAY_CTW_WEN)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		memcpy(__entwy->kek, data->kek, NW80211_KEK_WEN);
		memcpy(__entwy->kck, data->kck, NW80211_KCK_WEN);
		memcpy(__entwy->wepway_ctw, data->wepway_ctw,
		       NW80211_WEPWAY_CTW_WEN);
	),

	TP_pwintk(WOCAW_PW_FMT VIF_PW_FMT,
		  WOCAW_PW_AWG, VIF_PW_AWG)
);

TWACE_EVENT(dwv_event_cawwback,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 const stwuct ieee80211_event *_event),

	TP_AWGS(wocaw, sdata, _event),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u32, type)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->type = _event->type;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " event:%d",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->type
	)
);

DECWAWE_EVENT_CWASS(wewease_evt,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sta *sta,
		 u16 tids, int num_fwames,
		 enum ieee80211_fwame_wewease_type weason,
		 boow mowe_data),

	TP_AWGS(wocaw, sta, tids, num_fwames, weason, mowe_data),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		STA_ENTWY
		__fiewd(u16, tids)
		__fiewd(int, num_fwames)
		__fiewd(int, weason)
		__fiewd(boow, mowe_data)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		STA_ASSIGN;
		__entwy->tids = tids;
		__entwy->num_fwames = num_fwames;
		__entwy->weason = weason;
		__entwy->mowe_data = mowe_data;
	),

	TP_pwintk(
		WOCAW_PW_FMT STA_PW_FMT
		" TIDs:0x%.4x fwames:%d weason:%d mowe:%d",
		WOCAW_PW_AWG, STA_PW_AWG, __entwy->tids, __entwy->num_fwames,
		__entwy->weason, __entwy->mowe_data
	)
);

DEFINE_EVENT(wewease_evt, dwv_wewease_buffewed_fwames,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sta *sta,
		 u16 tids, int num_fwames,
		 enum ieee80211_fwame_wewease_type weason,
		 boow mowe_data),

	TP_AWGS(wocaw, sta, tids, num_fwames, weason, mowe_data)
);

DEFINE_EVENT(wewease_evt, dwv_awwow_buffewed_fwames,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sta *sta,
		 u16 tids, int num_fwames,
		 enum ieee80211_fwame_wewease_type weason,
		 boow mowe_data),

	TP_AWGS(wocaw, sta, tids, num_fwames, weason, mowe_data)
);

DECWAWE_EVENT_CWASS(mgd_pwepawe_compwete_tx_evt,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 u16 duwation, u16 subtype, boow success),

	TP_AWGS(wocaw, sdata, duwation, subtype, success),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u32, duwation)
		__fiewd(u16, subtype)
		__fiewd(u8, success)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->duwation = duwation;
		__entwy->subtype = subtype;
		__entwy->success = success;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " duwation: %u, subtype:0x%x, success:%d",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->duwation,
		__entwy->subtype, __entwy->success
	)
);

DEFINE_EVENT(mgd_pwepawe_compwete_tx_evt, dwv_mgd_pwepawe_tx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 u16 duwation, u16 subtype, boow success),

	TP_AWGS(wocaw, sdata, duwation, subtype, success)
);

DEFINE_EVENT(mgd_pwepawe_compwete_tx_evt, dwv_mgd_compwete_tx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 u16 duwation, u16 subtype, boow success),

	TP_AWGS(wocaw, sdata, duwation, subtype, success)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_mgd_pwotect_tdws_discovew,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),

	TP_AWGS(wocaw, sdata)
);

DECWAWE_EVENT_CWASS(wocaw_chanctx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_chanctx *ctx),

	TP_AWGS(wocaw, ctx),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		CHANCTX_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		CHANCTX_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT CHANCTX_PW_FMT,
		WOCAW_PW_AWG, CHANCTX_PW_AWG
	)
);

DEFINE_EVENT(wocaw_chanctx, dwv_add_chanctx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_chanctx *ctx),
	TP_AWGS(wocaw, ctx)
);

DEFINE_EVENT(wocaw_chanctx, dwv_wemove_chanctx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_chanctx *ctx),
	TP_AWGS(wocaw, ctx)
);

TWACE_EVENT(dwv_change_chanctx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_chanctx *ctx,
		 u32 changed),

	TP_AWGS(wocaw, ctx, changed),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		CHANCTX_ENTWY
		__fiewd(u32, changed)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		CHANCTX_ASSIGN;
		__entwy->changed = changed;
	),

	TP_pwintk(
		WOCAW_PW_FMT CHANCTX_PW_FMT " changed:%#x",
		WOCAW_PW_AWG, CHANCTX_PW_AWG, __entwy->changed
	)
);

#if !defined(__TWACE_VIF_ENTWY)
#define __TWACE_VIF_ENTWY
stwuct twace_vif_entwy {
	enum nw80211_iftype vif_type;
	boow p2p;
	chaw vif_name[IFNAMSIZ];
} __packed;

stwuct twace_chandef_entwy {
	u32 contwow_fweq;
	u32 fweq_offset;
	u32 chan_width;
	u32 centew_fweq1;
	u32 fweq1_offset;
	u32 centew_fweq2;
} __packed;

stwuct twace_switch_entwy {
	stwuct twace_vif_entwy vif;
	unsigned int wink_id;
	stwuct twace_chandef_entwy owd_chandef;
	stwuct twace_chandef_entwy new_chandef;
} __packed;

#define SWITCH_ENTWY_ASSIGN(to, fwom) wocaw_vifs[i].to = vifs[i].fwom
#endif

TWACE_EVENT(dwv_switch_vif_chanctx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_vif_chanctx_switch *vifs,
		 int n_vifs, enum ieee80211_chanctx_switch_mode mode),
	    TP_AWGS(wocaw, vifs, n_vifs, mode),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(int, n_vifs)
		__fiewd(u32, mode)
		__dynamic_awway(u8, vifs,
				sizeof(stwuct twace_switch_entwy) * n_vifs)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->n_vifs = n_vifs;
		__entwy->mode = mode;
		{
			stwuct twace_switch_entwy *wocaw_vifs =
				__get_dynamic_awway(vifs);
			int i;

			fow (i = 0; i < n_vifs; i++) {
				stwuct ieee80211_sub_if_data *sdata;

				sdata = containew_of(vifs[i].vif,
						stwuct ieee80211_sub_if_data,
						vif);

				SWITCH_ENTWY_ASSIGN(vif.vif_type, vif->type);
				SWITCH_ENTWY_ASSIGN(vif.p2p, vif->p2p);
				SWITCH_ENTWY_ASSIGN(wink_id, wink_conf->wink_id);
				stwncpy(wocaw_vifs[i].vif.vif_name,
					sdata->name,
					sizeof(wocaw_vifs[i].vif.vif_name));
				SWITCH_ENTWY_ASSIGN(owd_chandef.contwow_fweq,
						owd_ctx->def.chan->centew_fweq);
				SWITCH_ENTWY_ASSIGN(owd_chandef.fweq_offset,
						owd_ctx->def.chan->fweq_offset);
				SWITCH_ENTWY_ASSIGN(owd_chandef.chan_width,
						    owd_ctx->def.width);
				SWITCH_ENTWY_ASSIGN(owd_chandef.centew_fweq1,
						    owd_ctx->def.centew_fweq1);
				SWITCH_ENTWY_ASSIGN(owd_chandef.fweq1_offset,
						    owd_ctx->def.fweq1_offset);
				SWITCH_ENTWY_ASSIGN(owd_chandef.centew_fweq2,
						    owd_ctx->def.centew_fweq2);
				SWITCH_ENTWY_ASSIGN(new_chandef.contwow_fweq,
						new_ctx->def.chan->centew_fweq);
				SWITCH_ENTWY_ASSIGN(new_chandef.fweq_offset,
						new_ctx->def.chan->fweq_offset);
				SWITCH_ENTWY_ASSIGN(new_chandef.chan_width,
						    new_ctx->def.width);
				SWITCH_ENTWY_ASSIGN(new_chandef.centew_fweq1,
						    new_ctx->def.centew_fweq1);
				SWITCH_ENTWY_ASSIGN(new_chandef.fweq1_offset,
						    new_ctx->def.fweq1_offset);
				SWITCH_ENTWY_ASSIGN(new_chandef.centew_fweq2,
						    new_ctx->def.centew_fweq2);
			}
		}
	),

	TP_pwintk(
		WOCAW_PW_FMT " n_vifs:%d mode:%d",
		WOCAW_PW_AWG, __entwy->n_vifs, __entwy->mode
	)
);

DECWAWE_EVENT_CWASS(wocaw_sdata_chanctx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_bss_conf *wink_conf,
		 stwuct ieee80211_chanctx *ctx),

	TP_AWGS(wocaw, sdata, wink_conf, ctx),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		CHANCTX_ENTWY
		__fiewd(unsigned int, wink_id)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		CHANCTX_ASSIGN;
		__entwy->wink_id = wink_conf->wink_id;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " wink_id:%d" CHANCTX_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->wink_id, CHANCTX_PW_AWG
	)
);

DEFINE_EVENT(wocaw_sdata_chanctx, dwv_assign_vif_chanctx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_bss_conf *wink_conf,
		 stwuct ieee80211_chanctx *ctx),
	TP_AWGS(wocaw, sdata, wink_conf, ctx)
);

DEFINE_EVENT(wocaw_sdata_chanctx, dwv_unassign_vif_chanctx,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_bss_conf *wink_conf,
		 stwuct ieee80211_chanctx *ctx),
	TP_AWGS(wocaw, sdata, wink_conf, ctx)
);

TWACE_EVENT(dwv_stawt_ap,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_bss_conf *wink_conf),

	TP_AWGS(wocaw, sdata, wink_conf),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u32, wink_id)
		__fiewd(u8, dtimpew)
		__fiewd(u16, bcnint)
		__dynamic_awway(u8, ssid, sdata->vif.cfg.ssid_wen)
		__fiewd(boow, hidden_ssid)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->wink_id = wink_conf->wink_id;
		__entwy->dtimpew = wink_conf->dtim_pewiod;
		__entwy->bcnint = wink_conf->beacon_int;
		__entwy->hidden_ssid = wink_conf->hidden_ssid;
		memcpy(__get_dynamic_awway(ssid),
		       sdata->vif.cfg.ssid,
		       sdata->vif.cfg.ssid_wen);
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT " wink id %u",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->wink_id
	)
);

TWACE_EVENT(dwv_stop_ap,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_bss_conf *wink_conf),

	TP_AWGS(wocaw, sdata, wink_conf),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u32, wink_id)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->wink_id = wink_conf->wink_id;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT " wink id %u",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->wink_id
	)
);

TWACE_EVENT(dwv_weconfig_compwete,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 enum ieee80211_weconfig_type weconfig_type),
	TP_AWGS(wocaw, weconfig_type),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u8, weconfig_type)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->weconfig_type = weconfig_type;
	),

	TP_pwintk(
		WOCAW_PW_FMT  " weconfig_type:%d",
		WOCAW_PW_AWG, __entwy->weconfig_type
	)

);

#if IS_ENABWED(CONFIG_IPV6)
DEFINE_EVENT(wocaw_sdata_evt, dwv_ipv6_addw_change,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);
#endif

TWACE_EVENT(dwv_join_ibss,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_bss_conf *info),

	TP_AWGS(wocaw, sdata, info),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u8, dtimpew)
		__fiewd(u16, bcnint)
		__dynamic_awway(u8, ssid, sdata->vif.cfg.ssid_wen)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->dtimpew = info->dtim_pewiod;
		__entwy->bcnint = info->beacon_int;
		memcpy(__get_dynamic_awway(ssid),
		       sdata->vif.cfg.ssid,
		       sdata->vif.cfg.ssid_wen);
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG
	)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_weave_ibss,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

TWACE_EVENT(dwv_get_expected_thwoughput,
	TP_PWOTO(stwuct ieee80211_sta *sta),

	TP_AWGS(sta),

	TP_STWUCT__entwy(
		STA_ENTWY
	),

	TP_fast_assign(
		STA_ASSIGN;
	),

	TP_pwintk(
		STA_PW_FMT, STA_PW_AWG
	)
);

TWACE_EVENT(dwv_stawt_nan,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct cfg80211_nan_conf *conf),

	TP_AWGS(wocaw, sdata, conf),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u8, mastew_pwef)
		__fiewd(u8, bands)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->mastew_pwef = conf->mastew_pwef;
		__entwy->bands = conf->bands;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT
		", mastew pwefewence: %u, bands: 0x%0x",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->mastew_pwef,
		__entwy->bands
	)
);

TWACE_EVENT(dwv_stop_nan,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),

	TP_AWGS(wocaw, sdata),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG
	)
);

TWACE_EVENT(dwv_nan_change_conf,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct cfg80211_nan_conf *conf,
		 u32 changes),

	TP_AWGS(wocaw, sdata, conf, changes),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u8, mastew_pwef)
		__fiewd(u8, bands)
		__fiewd(u32, changes)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->mastew_pwef = conf->mastew_pwef;
		__entwy->bands = conf->bands;
		__entwy->changes = changes;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT
		", mastew pwefewence: %u, bands: 0x%0x, changes: 0x%x",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->mastew_pwef,
		__entwy->bands, __entwy->changes
	)
);

TWACE_EVENT(dwv_add_nan_func,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 const stwuct cfg80211_nan_func *func),

	TP_AWGS(wocaw, sdata, func),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u8, type)
		__fiewd(u8, inst_id)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->type = func->type;
		__entwy->inst_id = func->instance_id;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT
		", type: %u, inst_id: %u",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->type, __entwy->inst_id
	)
);

TWACE_EVENT(dwv_dew_nan_func,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 u8 instance_id),

	TP_AWGS(wocaw, sdata, instance_id),
	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u8, instance_id)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->instance_id = instance_id;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT
		", instance_id: %u",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->instance_id
	)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_stawt_pmsw,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_abowt_pmsw,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

TWACE_EVENT(dwv_set_defauwt_unicast_key,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 int key_idx),

	TP_AWGS(wocaw, sdata, key_idx),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(int, key_idx)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->key_idx = key_idx;
	),

	TP_pwintk(WOCAW_PW_FMT VIF_PW_FMT " key_idx:%d",
		  WOCAW_PW_AWG, VIF_PW_AWG, __entwy->key_idx)
);

TWACE_EVENT(dwv_channew_switch_beacon,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct cfg80211_chan_def *chandef),

	TP_AWGS(wocaw, sdata, chandef),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		CHANDEF_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		CHANDEF_ASSIGN(chandef);
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " channew switch to " CHANDEF_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG, CHANDEF_PW_AWG
	)
);

TWACE_EVENT(dwv_pwe_channew_switch,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_channew_switch *ch_switch),

	TP_AWGS(wocaw, sdata, ch_switch),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		CHANDEF_ENTWY
		__fiewd(u64, timestamp)
		__fiewd(u32, device_timestamp)
		__fiewd(boow, bwock_tx)
		__fiewd(u8, count)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		CHANDEF_ASSIGN(&ch_switch->chandef)
		__entwy->timestamp = ch_switch->timestamp;
		__entwy->device_timestamp = ch_switch->device_timestamp;
		__entwy->bwock_tx = ch_switch->bwock_tx;
		__entwy->count = ch_switch->count;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " pwepawe channew switch to "
		CHANDEF_PW_FMT  " count:%d bwock_tx:%d timestamp:%wwu",
		WOCAW_PW_AWG, VIF_PW_AWG, CHANDEF_PW_AWG, __entwy->count,
		__entwy->bwock_tx, __entwy->timestamp
	)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_post_channew_switch,
	     TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		      stwuct ieee80211_sub_if_data *sdata),
	     TP_AWGS(wocaw, sdata)
);

DEFINE_EVENT(wocaw_sdata_evt, dwv_abowt_channew_switch,
	     TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		      stwuct ieee80211_sub_if_data *sdata),
	     TP_AWGS(wocaw, sdata)
);

TWACE_EVENT(dwv_channew_switch_wx_beacon,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_channew_switch *ch_switch),

	TP_AWGS(wocaw, sdata, ch_switch),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		CHANDEF_ENTWY
		__fiewd(u64, timestamp)
		__fiewd(u32, device_timestamp)
		__fiewd(boow, bwock_tx)
		__fiewd(u8, count)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		CHANDEF_ASSIGN(&ch_switch->chandef)
		__entwy->timestamp = ch_switch->timestamp;
		__entwy->device_timestamp = ch_switch->device_timestamp;
		__entwy->bwock_tx = ch_switch->bwock_tx;
		__entwy->count = ch_switch->count;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT
		" weceived a channew switch beacon to "
		CHANDEF_PW_FMT  " count:%d bwock_tx:%d timestamp:%wwu",
		WOCAW_PW_AWG, VIF_PW_AWG, CHANDEF_PW_AWG, __entwy->count,
		__entwy->bwock_tx, __entwy->timestamp
	)
);

TWACE_EVENT(dwv_get_txpowew,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 int dbm, int wet),

	TP_AWGS(wocaw, sdata, dbm, wet),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(int, dbm)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->dbm = dbm;
		__entwy->wet = wet;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " dbm:%d wet:%d",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->dbm, __entwy->wet
	)
);

TWACE_EVENT(dwv_tdws_channew_switch,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta, u8 opew_cwass,
		 stwuct cfg80211_chan_def *chandef),

	TP_AWGS(wocaw, sdata, sta, opew_cwass, chandef),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
		__fiewd(u8, opew_cwass)
		CHANDEF_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
		__entwy->opew_cwass = opew_cwass;
		CHANDEF_ASSIGN(chandef)
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " tdws channew switch to"
		CHANDEF_PW_FMT  " opew_cwass:%d " STA_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG, CHANDEF_PW_AWG, __entwy->opew_cwass,
		STA_PW_AWG
	)
);

TWACE_EVENT(dwv_tdws_cancew_channew_switch,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),

	TP_AWGS(wocaw, sdata, sta),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT
		" tdws cancew channew switch with " STA_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG
	)
);

TWACE_EVENT(dwv_tdws_wecv_channew_switch,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_tdws_ch_sw_pawams *pawams),

	TP_AWGS(wocaw, sdata, pawams),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u8, action_code)
		STA_ENTWY
		CHANDEF_ENTWY
		__fiewd(u32, status)
		__fiewd(boow, peew_initiatow)
		__fiewd(u32, timestamp)
		__fiewd(u16, switch_time)
		__fiewd(u16, switch_timeout)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_NAMED_ASSIGN(pawams->sta);
		CHANDEF_ASSIGN(pawams->chandef)
		__entwy->peew_initiatow = pawams->sta->tdws_initiatow;
		__entwy->action_code = pawams->action_code;
		__entwy->status = pawams->status;
		__entwy->timestamp = pawams->timestamp;
		__entwy->switch_time = pawams->switch_time;
		__entwy->switch_timeout = pawams->switch_timeout;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " weceived tdws channew switch packet"
		" action:%d status:%d time:%d switch time:%d switch"
		" timeout:%d initiatow: %d chan:" CHANDEF_PW_FMT STA_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->action_code, __entwy->status,
		__entwy->timestamp, __entwy->switch_time,
		__entwy->switch_timeout, __entwy->peew_initiatow,
		CHANDEF_PW_AWG, STA_PW_AWG
	)
);

TWACE_EVENT(dwv_wake_tx_queue,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct txq_info *txq),

	TP_AWGS(wocaw, sdata, txq),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
		__fiewd(u8, ac)
		__fiewd(u8, tid)
	),

	TP_fast_assign(
		stwuct ieee80211_sta *sta = txq->txq.sta;

		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
		__entwy->ac = txq->txq.ac;
		__entwy->tid = txq->txq.tid;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  STA_PW_FMT " ac:%d tid:%d",
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG, __entwy->ac, __entwy->tid
	)
);

TWACE_EVENT(dwv_get_ftm_wespondew_stats,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct cfg80211_ftm_wespondew_stats *ftm_stats),

	TP_AWGS(wocaw, sdata, ftm_stats),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT,
		WOCAW_PW_AWG, VIF_PW_AWG
	)
);

DEFINE_EVENT(wocaw_sdata_addw_evt, dwv_update_vif_offwoad,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

DECWAWE_EVENT_CWASS(sta_fwag_evt,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta, boow enabwed),

	TP_AWGS(wocaw, sdata, sta, enabwed),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
		__fiewd(boow, enabwed)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
		__entwy->enabwed = enabwed;
	),

	TP_pwintk(
		WOCAW_PW_FMT  VIF_PW_FMT  STA_PW_FMT " enabwed:%d",
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG, __entwy->enabwed
	)
);

DEFINE_EVENT(sta_fwag_evt, dwv_sta_set_4addw,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta, boow enabwed),

	TP_AWGS(wocaw, sdata, sta, enabwed)
);

DEFINE_EVENT(sta_fwag_evt, dwv_sta_set_decap_offwoad,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta, boow enabwed),

	TP_AWGS(wocaw, sdata, sta, enabwed)
);

TWACE_EVENT(dwv_add_twt_setup,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sta *sta,
		 stwuct ieee80211_twt_setup *twt,
		 stwuct ieee80211_twt_pawams *twt_agwt),

	TP_AWGS(wocaw, sta, twt, twt_agwt),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		STA_ENTWY
		__fiewd(u8, diawog_token)
		__fiewd(u8, contwow)
		__fiewd(__we16, weq_type)
		__fiewd(__we64, twt)
		__fiewd(u8, duwation)
		__fiewd(__we16, mantissa)
		__fiewd(u8, channew)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		STA_ASSIGN;
		__entwy->diawog_token = twt->diawog_token;
		__entwy->contwow = twt->contwow;
		__entwy->weq_type = twt_agwt->weq_type;
		__entwy->twt = twt_agwt->twt;
		__entwy->duwation = twt_agwt->min_twt_duw;
		__entwy->mantissa = twt_agwt->mantissa;
		__entwy->channew = twt_agwt->channew;
	),

	TP_pwintk(
		WOCAW_PW_FMT STA_PW_FMT
		" token:%d contwow:0x%02x weq_type:0x%04x"
		" twt:%wwu duwation:%d mantissa:%d channew:%d",
		WOCAW_PW_AWG, STA_PW_AWG, __entwy->diawog_token,
		__entwy->contwow, we16_to_cpu(__entwy->weq_type),
		we64_to_cpu(__entwy->twt), __entwy->duwation,
		we16_to_cpu(__entwy->mantissa), __entwy->channew
	)
);

TWACE_EVENT(dwv_twt_teawdown_wequest,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sta *sta, u8 fwowid),

	TP_AWGS(wocaw, sta, fwowid),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		STA_ENTWY
		__fiewd(u8, fwowid)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		STA_ASSIGN;
		__entwy->fwowid = fwowid;
	),

	TP_pwintk(
		WOCAW_PW_FMT STA_PW_FMT " fwowid:%d",
		WOCAW_PW_AWG, STA_PW_AWG, __entwy->fwowid
	)
);

DEFINE_EVENT(sta_event, dwv_net_fiww_fowwawd_path,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta),
	TP_AWGS(wocaw, sdata, sta)
);

TWACE_EVENT(dwv_net_setup_tc,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 u8 type),

	TP_AWGS(wocaw, sdata, type),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u8, type)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->type = type;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " type:%d\n",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->type
	)
);

TWACE_EVENT(dwv_can_activate_winks,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 u16 active_winks),

	TP_AWGS(wocaw, sdata, active_winks),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u16, active_winks)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->active_winks = active_winks;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " wequested active_winks:0x%04x\n",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->active_winks
	)
);

TWACE_EVENT(dwv_change_vif_winks,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 u16 owd_winks, u16 new_winks),

	TP_AWGS(wocaw, sdata, owd_winks, new_winks),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		__fiewd(u16, owd_winks)
		__fiewd(u16, new_winks)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		__entwy->owd_winks = owd_winks;
		__entwy->new_winks = new_winks;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT " owd_winks:0x%04x, new_winks:0x%04x\n",
		WOCAW_PW_AWG, VIF_PW_AWG, __entwy->owd_winks, __entwy->new_winks
	)
);

TWACE_EVENT(dwv_change_sta_winks,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata,
		 stwuct ieee80211_sta *sta,
		 u16 owd_winks, u16 new_winks),

	TP_AWGS(wocaw, sdata, sta, owd_winks, new_winks),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		VIF_ENTWY
		STA_ENTWY
		__fiewd(u16, owd_winks)
		__fiewd(u16, new_winks)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		VIF_ASSIGN;
		STA_ASSIGN;
		__entwy->owd_winks = owd_winks;
		__entwy->new_winks = new_winks;
	),

	TP_pwintk(
		WOCAW_PW_FMT VIF_PW_FMT STA_PW_FMT " owd_winks:0x%04x, new_winks:0x%04x\n",
		WOCAW_PW_AWG, VIF_PW_AWG, STA_PW_AWG,
		__entwy->owd_winks, __entwy->new_winks
	)
);

/*
 * Twacing fow API cawws that dwivews caww.
 */

TWACE_EVENT(api_stawt_tx_ba_session,
	TP_PWOTO(stwuct ieee80211_sta *sta, u16 tid),

	TP_AWGS(sta, tid),

	TP_STWUCT__entwy(
		STA_ENTWY
		__fiewd(u16, tid)
	),

	TP_fast_assign(
		STA_ASSIGN;
		__entwy->tid = tid;
	),

	TP_pwintk(
		STA_PW_FMT " tid:%d",
		STA_PW_AWG, __entwy->tid
	)
);

TWACE_EVENT(api_stawt_tx_ba_cb,
	TP_PWOTO(stwuct ieee80211_sub_if_data *sdata, const u8 *wa, u16 tid),

	TP_AWGS(sdata, wa, tid),

	TP_STWUCT__entwy(
		VIF_ENTWY
		__awway(u8, wa, ETH_AWEN)
		__fiewd(u16, tid)
	),

	TP_fast_assign(
		VIF_ASSIGN;
		memcpy(__entwy->wa, wa, ETH_AWEN);
		__entwy->tid = tid;
	),

	TP_pwintk(
		VIF_PW_FMT " wa:%pM tid:%d",
		VIF_PW_AWG, __entwy->wa, __entwy->tid
	)
);

TWACE_EVENT(api_stop_tx_ba_session,
	TP_PWOTO(stwuct ieee80211_sta *sta, u16 tid),

	TP_AWGS(sta, tid),

	TP_STWUCT__entwy(
		STA_ENTWY
		__fiewd(u16, tid)
	),

	TP_fast_assign(
		STA_ASSIGN;
		__entwy->tid = tid;
	),

	TP_pwintk(
		STA_PW_FMT " tid:%d",
		STA_PW_AWG, __entwy->tid
	)
);

TWACE_EVENT(api_stop_tx_ba_cb,
	TP_PWOTO(stwuct ieee80211_sub_if_data *sdata, const u8 *wa, u16 tid),

	TP_AWGS(sdata, wa, tid),

	TP_STWUCT__entwy(
		VIF_ENTWY
		__awway(u8, wa, ETH_AWEN)
		__fiewd(u16, tid)
	),

	TP_fast_assign(
		VIF_ASSIGN;
		memcpy(__entwy->wa, wa, ETH_AWEN);
		__entwy->tid = tid;
	),

	TP_pwintk(
		VIF_PW_FMT " wa:%pM tid:%d",
		VIF_PW_AWG, __entwy->wa, __entwy->tid
	)
);

DEFINE_EVENT(wocaw_onwy_evt, api_westawt_hw,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

TWACE_EVENT(api_beacon_woss,
	TP_PWOTO(stwuct ieee80211_sub_if_data *sdata),

	TP_AWGS(sdata),

	TP_STWUCT__entwy(
		VIF_ENTWY
	),

	TP_fast_assign(
		VIF_ASSIGN;
	),

	TP_pwintk(
		VIF_PW_FMT,
		VIF_PW_AWG
	)
);

TWACE_EVENT(api_connection_woss,
	TP_PWOTO(stwuct ieee80211_sub_if_data *sdata),

	TP_AWGS(sdata),

	TP_STWUCT__entwy(
		VIF_ENTWY
	),

	TP_fast_assign(
		VIF_ASSIGN;
	),

	TP_pwintk(
		VIF_PW_FMT,
		VIF_PW_AWG
	)
);

TWACE_EVENT(api_disconnect,
	TP_PWOTO(stwuct ieee80211_sub_if_data *sdata, boow weconnect),

	TP_AWGS(sdata, weconnect),

	TP_STWUCT__entwy(
		VIF_ENTWY
		__fiewd(int, weconnect)
	),

	TP_fast_assign(
		VIF_ASSIGN;
		__entwy->weconnect = weconnect;
	),

	TP_pwintk(
		VIF_PW_FMT " weconnect:%d",
		VIF_PW_AWG, __entwy->weconnect
	)
);

TWACE_EVENT(api_cqm_wssi_notify,
	TP_PWOTO(stwuct ieee80211_sub_if_data *sdata,
		 enum nw80211_cqm_wssi_thweshowd_event wssi_event,
		 s32 wssi_wevew),

	TP_AWGS(sdata, wssi_event, wssi_wevew),

	TP_STWUCT__entwy(
		VIF_ENTWY
		__fiewd(u32, wssi_event)
		__fiewd(s32, wssi_wevew)
	),

	TP_fast_assign(
		VIF_ASSIGN;
		__entwy->wssi_event = wssi_event;
		__entwy->wssi_wevew = wssi_wevew;
	),

	TP_pwintk(
		VIF_PW_FMT " event:%d wssi:%d",
		VIF_PW_AWG, __entwy->wssi_event, __entwy->wssi_wevew
	)
);

DEFINE_EVENT(wocaw_sdata_evt, api_cqm_beacon_woss_notify,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sub_if_data *sdata),
	TP_AWGS(wocaw, sdata)
);

TWACE_EVENT(api_scan_compweted,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, boow abowted),

	TP_AWGS(wocaw, abowted),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(boow, abowted)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->abowted = abowted;
	),

	TP_pwintk(
		WOCAW_PW_FMT " abowted:%d",
		WOCAW_PW_AWG, __entwy->abowted
	)
);

TWACE_EVENT(api_sched_scan_wesuwts,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),

	TP_AWGS(wocaw),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT, WOCAW_PW_AWG
	)
);

TWACE_EVENT(api_sched_scan_stopped,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),

	TP_AWGS(wocaw),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT, WOCAW_PW_AWG
	)
);

TWACE_EVENT(api_sta_bwock_awake,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sta *sta, boow bwock),

	TP_AWGS(wocaw, sta, bwock),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		STA_ENTWY
		__fiewd(boow, bwock)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		STA_ASSIGN;
		__entwy->bwock = bwock;
	),

	TP_pwintk(
		WOCAW_PW_FMT STA_PW_FMT " bwock:%d",
		WOCAW_PW_AWG, STA_PW_AWG, __entwy->bwock
	)
);

TWACE_EVENT(api_chswitch_done,
	TP_PWOTO(stwuct ieee80211_sub_if_data *sdata, boow success,
		 unsigned int wink_id),

	TP_AWGS(sdata, success, wink_id),

	TP_STWUCT__entwy(
		VIF_ENTWY
		__fiewd(boow, success)
		__fiewd(unsigned int, wink_id)
	),

	TP_fast_assign(
		VIF_ASSIGN;
		__entwy->success = success;
		__entwy->wink_id = wink_id;
	),

	TP_pwintk(
		VIF_PW_FMT " success=%d wink_id=%d",
		VIF_PW_AWG, __entwy->success, __entwy->wink_id
	)
);

DEFINE_EVENT(wocaw_onwy_evt, api_weady_on_channew,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

DEFINE_EVENT(wocaw_onwy_evt, api_wemain_on_channew_expiwed,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),
	TP_AWGS(wocaw)
);

TWACE_EVENT(api_gtk_wekey_notify,
	TP_PWOTO(stwuct ieee80211_sub_if_data *sdata,
		 const u8 *bssid, const u8 *wepway_ctw),

	TP_AWGS(sdata, bssid, wepway_ctw),

	TP_STWUCT__entwy(
		VIF_ENTWY
		__awway(u8, bssid, ETH_AWEN)
		__awway(u8, wepway_ctw, NW80211_WEPWAY_CTW_WEN)
	),

	TP_fast_assign(
		VIF_ASSIGN;
		memcpy(__entwy->bssid, bssid, ETH_AWEN);
		memcpy(__entwy->wepway_ctw, wepway_ctw, NW80211_WEPWAY_CTW_WEN);
	),

	TP_pwintk(VIF_PW_FMT, VIF_PW_AWG)
);

TWACE_EVENT(api_enabwe_wssi_wepowts,
	TP_PWOTO(stwuct ieee80211_sub_if_data *sdata,
		 int wssi_min_thowd, int wssi_max_thowd),

	TP_AWGS(sdata, wssi_min_thowd, wssi_max_thowd),

	TP_STWUCT__entwy(
		VIF_ENTWY
		__fiewd(int, wssi_min_thowd)
		__fiewd(int, wssi_max_thowd)
	),

	TP_fast_assign(
		VIF_ASSIGN;
		__entwy->wssi_min_thowd = wssi_min_thowd;
		__entwy->wssi_max_thowd = wssi_max_thowd;
	),

	TP_pwintk(
		VIF_PW_FMT " wssi_min_thowd =%d, wssi_max_thowd = %d",
		VIF_PW_AWG, __entwy->wssi_min_thowd, __entwy->wssi_max_thowd
	)
);

TWACE_EVENT(api_eosp,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sta *sta),

	TP_AWGS(wocaw, sta),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		STA_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		STA_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT STA_PW_FMT,
		WOCAW_PW_AWG, STA_PW_AWG
	)
);

TWACE_EVENT(api_send_eosp_nuwwfunc,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sta *sta,
		 u8 tid),

	TP_AWGS(wocaw, sta, tid),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		STA_ENTWY
		__fiewd(u8, tid)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		STA_ASSIGN;
		__entwy->tid = tid;
	),

	TP_pwintk(
		WOCAW_PW_FMT STA_PW_FMT " tid:%d",
		WOCAW_PW_AWG, STA_PW_AWG, __entwy->tid
	)
);

TWACE_EVENT(api_sta_set_buffewed,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw,
		 stwuct ieee80211_sta *sta,
		 u8 tid, boow buffewed),

	TP_AWGS(wocaw, sta, tid, buffewed),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		STA_ENTWY
		__fiewd(u8, tid)
		__fiewd(boow, buffewed)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		STA_ASSIGN;
		__entwy->tid = tid;
		__entwy->buffewed = buffewed;
	),

	TP_pwintk(
		WOCAW_PW_FMT STA_PW_FMT " tid:%d buffewed:%d",
		WOCAW_PW_AWG, STA_PW_AWG, __entwy->tid, __entwy->buffewed
	)
);

TWACE_EVENT(api_wadaw_detected,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw),

	TP_AWGS(wocaw),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
	),

	TP_pwintk(
		WOCAW_PW_FMT " wadaw detected",
		WOCAW_PW_AWG
	)
);

/*
 * Twacing fow intewnaw functions
 * (which may awso be cawwed in wesponse to dwivew cawws)
 */

TWACE_EVENT(wake_queue,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u16 queue,
		 enum queue_stop_weason weason),

	TP_AWGS(wocaw, queue, weason),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u16, queue)
		__fiewd(u32, weason)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->queue = queue;
		__entwy->weason = weason;
	),

	TP_pwintk(
		WOCAW_PW_FMT " queue:%d, weason:%d",
		WOCAW_PW_AWG, __entwy->queue, __entwy->weason
	)
);

TWACE_EVENT(stop_queue,
	TP_PWOTO(stwuct ieee80211_wocaw *wocaw, u16 queue,
		 enum queue_stop_weason weason),

	TP_AWGS(wocaw, queue, weason),

	TP_STWUCT__entwy(
		WOCAW_ENTWY
		__fiewd(u16, queue)
		__fiewd(u32, weason)
	),

	TP_fast_assign(
		WOCAW_ASSIGN;
		__entwy->queue = queue;
		__entwy->weason = weason;
	),

	TP_pwintk(
		WOCAW_PW_FMT " queue:%d, weason:%d",
		WOCAW_PW_AWG, __entwy->queue, __entwy->weason
	)
);

#endif /* !__MAC80211_DWIVEW_TWACE || TWACE_HEADEW_MUWTI_WEAD */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace
#incwude <twace/define_twace.h>
