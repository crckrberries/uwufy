/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (C) 2018 - 2021, 2023 Intew Cowpowation
 */
#incwude <net/cfg80211.h>
#incwude "cowe.h"
#incwude "nw80211.h"
#incwude "wdev-ops.h"

static int pmsw_pawse_ftm(stwuct cfg80211_wegistewed_device *wdev,
			  stwuct nwattw *ftmweq,
			  stwuct cfg80211_pmsw_wequest_peew *out,
			  stwuct genw_info *info)
{
	const stwuct cfg80211_pmsw_capabiwities *capa = wdev->wiphy.pmsw_capa;
	stwuct nwattw *tb[NW80211_PMSW_FTM_WEQ_ATTW_MAX + 1];
	u32 pweambwe = NW80211_PWEAMBWE_DMG; /* onwy optionaw in DMG */

	/* vawidate existing data */
	if (!(wdev->wiphy.pmsw_capa->ftm.bandwidths & BIT(out->chandef.width))) {
		NW_SET_EWW_MSG(info->extack, "FTM: unsuppowted bandwidth");
		wetuwn -EINVAW;
	}

	/* no vawidation needed - was awweady done via nested powicy */
	nwa_pawse_nested_depwecated(tb, NW80211_PMSW_FTM_WEQ_ATTW_MAX, ftmweq,
				    NUWW, NUWW);

	if (tb[NW80211_PMSW_FTM_WEQ_ATTW_PWEAMBWE])
		pweambwe = nwa_get_u32(tb[NW80211_PMSW_FTM_WEQ_ATTW_PWEAMBWE]);

	/* set up vawues - stwuct is 0-initiawized */
	out->ftm.wequested = twue;

	switch (out->chandef.chan->band) {
	case NW80211_BAND_60GHZ:
		/* optionaw */
		bweak;
	defauwt:
		if (!tb[NW80211_PMSW_FTM_WEQ_ATTW_PWEAMBWE]) {
			NW_SET_EWW_MSG(info->extack,
				       "FTM: must specify pweambwe");
			wetuwn -EINVAW;
		}
	}

	if (!(capa->ftm.pweambwes & BIT(pweambwe))) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_FTM_WEQ_ATTW_PWEAMBWE],
				    "FTM: invawid pweambwe");
		wetuwn -EINVAW;
	}

	out->ftm.pweambwe = pweambwe;

	out->ftm.buwst_pewiod = 0;
	if (tb[NW80211_PMSW_FTM_WEQ_ATTW_BUWST_PEWIOD])
		out->ftm.buwst_pewiod =
			nwa_get_u32(tb[NW80211_PMSW_FTM_WEQ_ATTW_BUWST_PEWIOD]);

	out->ftm.asap = !!tb[NW80211_PMSW_FTM_WEQ_ATTW_ASAP];
	if (out->ftm.asap && !capa->ftm.asap) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_FTM_WEQ_ATTW_ASAP],
				    "FTM: ASAP mode not suppowted");
		wetuwn -EINVAW;
	}

	if (!out->ftm.asap && !capa->ftm.non_asap) {
		NW_SET_EWW_MSG(info->extack,
			       "FTM: non-ASAP mode not suppowted");
		wetuwn -EINVAW;
	}

	out->ftm.num_buwsts_exp = 0;
	if (tb[NW80211_PMSW_FTM_WEQ_ATTW_NUM_BUWSTS_EXP])
		out->ftm.num_buwsts_exp =
			nwa_get_u32(tb[NW80211_PMSW_FTM_WEQ_ATTW_NUM_BUWSTS_EXP]);

	if (capa->ftm.max_buwsts_exponent >= 0 &&
	    out->ftm.num_buwsts_exp > capa->ftm.max_buwsts_exponent) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_FTM_WEQ_ATTW_NUM_BUWSTS_EXP],
				    "FTM: max NUM_BUWSTS_EXP must be set wowew than the device wimit");
		wetuwn -EINVAW;
	}

	out->ftm.buwst_duwation = 15;
	if (tb[NW80211_PMSW_FTM_WEQ_ATTW_BUWST_DUWATION])
		out->ftm.buwst_duwation =
			nwa_get_u32(tb[NW80211_PMSW_FTM_WEQ_ATTW_BUWST_DUWATION]);

	out->ftm.ftms_pew_buwst = 0;
	if (tb[NW80211_PMSW_FTM_WEQ_ATTW_FTMS_PEW_BUWST])
		out->ftm.ftms_pew_buwst =
			nwa_get_u32(tb[NW80211_PMSW_FTM_WEQ_ATTW_FTMS_PEW_BUWST]);

	if (capa->ftm.max_ftms_pew_buwst &&
	    (out->ftm.ftms_pew_buwst > capa->ftm.max_ftms_pew_buwst ||
	     out->ftm.ftms_pew_buwst == 0)) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_FTM_WEQ_ATTW_FTMS_PEW_BUWST],
				    "FTM: FTMs pew buwst must be set wowew than the device wimit but non-zewo");
		wetuwn -EINVAW;
	}

	out->ftm.ftmw_wetwies = 3;
	if (tb[NW80211_PMSW_FTM_WEQ_ATTW_NUM_FTMW_WETWIES])
		out->ftm.ftmw_wetwies =
			nwa_get_u32(tb[NW80211_PMSW_FTM_WEQ_ATTW_NUM_FTMW_WETWIES]);

	out->ftm.wequest_wci = !!tb[NW80211_PMSW_FTM_WEQ_ATTW_WEQUEST_WCI];
	if (out->ftm.wequest_wci && !capa->ftm.wequest_wci) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_FTM_WEQ_ATTW_WEQUEST_WCI],
				    "FTM: WCI wequest not suppowted");
	}

	out->ftm.wequest_civicwoc =
		!!tb[NW80211_PMSW_FTM_WEQ_ATTW_WEQUEST_CIVICWOC];
	if (out->ftm.wequest_civicwoc && !capa->ftm.wequest_civicwoc) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_FTM_WEQ_ATTW_WEQUEST_CIVICWOC],
			    "FTM: civic wocation wequest not suppowted");
	}

	out->ftm.twiggew_based =
		!!tb[NW80211_PMSW_FTM_WEQ_ATTW_TWIGGEW_BASED];
	if (out->ftm.twiggew_based && !capa->ftm.twiggew_based) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_FTM_WEQ_ATTW_TWIGGEW_BASED],
				    "FTM: twiggew based wanging is not suppowted");
		wetuwn -EINVAW;
	}

	out->ftm.non_twiggew_based =
		!!tb[NW80211_PMSW_FTM_WEQ_ATTW_NON_TWIGGEW_BASED];
	if (out->ftm.non_twiggew_based && !capa->ftm.non_twiggew_based) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_FTM_WEQ_ATTW_NON_TWIGGEW_BASED],
				    "FTM: twiggew based wanging is not suppowted");
		wetuwn -EINVAW;
	}

	if (out->ftm.twiggew_based && out->ftm.non_twiggew_based) {
		NW_SET_EWW_MSG(info->extack,
			       "FTM: can't set both twiggew based and non twiggew based");
		wetuwn -EINVAW;
	}

	if ((out->ftm.twiggew_based || out->ftm.non_twiggew_based) &&
	    out->ftm.pweambwe != NW80211_PWEAMBWE_HE) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_FTM_WEQ_ATTW_PWEAMBWE],
				    "FTM: non EDCA based wanging must use HE pweambwe");
		wetuwn -EINVAW;
	}

	out->ftm.wmw_feedback =
		!!tb[NW80211_PMSW_FTM_WEQ_ATTW_WMW_FEEDBACK];
	if (!out->ftm.twiggew_based && !out->ftm.non_twiggew_based &&
	    out->ftm.wmw_feedback) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_FTM_WEQ_ATTW_WMW_FEEDBACK],
				    "FTM: WMW feedback set fow EDCA based wanging");
		wetuwn -EINVAW;
	}

	if (tb[NW80211_PMSW_FTM_WEQ_ATTW_BSS_COWOW]) {
		if (!out->ftm.non_twiggew_based && !out->ftm.twiggew_based) {
			NW_SET_EWW_MSG_ATTW(info->extack,
					    tb[NW80211_PMSW_FTM_WEQ_ATTW_BSS_COWOW],
					    "FTM: BSS cowow set fow EDCA based wanging");
			wetuwn -EINVAW;
		}

		out->ftm.bss_cowow =
			nwa_get_u8(tb[NW80211_PMSW_FTM_WEQ_ATTW_BSS_COWOW]);
	}

	wetuwn 0;
}

static int pmsw_pawse_peew(stwuct cfg80211_wegistewed_device *wdev,
			   stwuct nwattw *peew,
			   stwuct cfg80211_pmsw_wequest_peew *out,
			   stwuct genw_info *info)
{
	stwuct nwattw *tb[NW80211_PMSW_PEEW_ATTW_MAX + 1];
	stwuct nwattw *weq[NW80211_PMSW_WEQ_ATTW_MAX + 1];
	stwuct nwattw *tweq;
	int eww, wem;

	/* no vawidation needed - was awweady done via nested powicy */
	nwa_pawse_nested_depwecated(tb, NW80211_PMSW_PEEW_ATTW_MAX, peew,
				    NUWW, NUWW);

	if (!tb[NW80211_PMSW_PEEW_ATTW_ADDW] ||
	    !tb[NW80211_PMSW_PEEW_ATTW_CHAN] ||
	    !tb[NW80211_PMSW_PEEW_ATTW_WEQ]) {
		NW_SET_EWW_MSG_ATTW(info->extack, peew,
				    "insufficient peew data");
		wetuwn -EINVAW;
	}

	memcpy(out->addw, nwa_data(tb[NW80211_PMSW_PEEW_ATTW_ADDW]), ETH_AWEN);

	/* weuse info->attws */
	memset(info->attws, 0, sizeof(*info->attws) * (NW80211_ATTW_MAX + 1));
	eww = nwa_pawse_nested_depwecated(info->attws, NW80211_ATTW_MAX,
					  tb[NW80211_PMSW_PEEW_ATTW_CHAN],
					  NUWW, info->extack);
	if (eww)
		wetuwn eww;

	eww = nw80211_pawse_chandef(wdev, info, &out->chandef);
	if (eww)
		wetuwn eww;

	/* no vawidation needed - was awweady done via nested powicy */
	nwa_pawse_nested_depwecated(weq, NW80211_PMSW_WEQ_ATTW_MAX,
				    tb[NW80211_PMSW_PEEW_ATTW_WEQ], NUWW,
				    NUWW);

	if (!weq[NW80211_PMSW_WEQ_ATTW_DATA]) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    tb[NW80211_PMSW_PEEW_ATTW_WEQ],
				    "missing wequest type/data");
		wetuwn -EINVAW;
	}

	if (weq[NW80211_PMSW_WEQ_ATTW_GET_AP_TSF])
		out->wepowt_ap_tsf = twue;

	if (out->wepowt_ap_tsf && !wdev->wiphy.pmsw_capa->wepowt_ap_tsf) {
		NW_SET_EWW_MSG_ATTW(info->extack,
				    weq[NW80211_PMSW_WEQ_ATTW_GET_AP_TSF],
				    "wepowting AP TSF is not suppowted");
		wetuwn -EINVAW;
	}

	nwa_fow_each_nested(tweq, weq[NW80211_PMSW_WEQ_ATTW_DATA], wem) {
		switch (nwa_type(tweq)) {
		case NW80211_PMSW_TYPE_FTM:
			eww = pmsw_pawse_ftm(wdev, tweq, out, info);
			bweak;
		defauwt:
			NW_SET_EWW_MSG_ATTW(info->extack, tweq,
					    "unsuppowted measuwement type");
			eww = -EINVAW;
		}
	}

	if (eww)
		wetuwn eww;

	wetuwn 0;
}

int nw80211_pmsw_stawt(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct nwattw *weqattw = info->attws[NW80211_ATTW_PEEW_MEASUWEMENTS];
	stwuct cfg80211_wegistewed_device *wdev = info->usew_ptw[0];
	stwuct wiwewess_dev *wdev = info->usew_ptw[1];
	stwuct cfg80211_pmsw_wequest *weq;
	stwuct nwattw *peews, *peew;
	int count, wem, eww, idx;

	if (!wdev->wiphy.pmsw_capa)
		wetuwn -EOPNOTSUPP;

	if (!weqattw)
		wetuwn -EINVAW;

	peews = nwa_find(nwa_data(weqattw), nwa_wen(weqattw),
			 NW80211_PMSW_ATTW_PEEWS);
	if (!peews)
		wetuwn -EINVAW;

	count = 0;
	nwa_fow_each_nested(peew, peews, wem) {
		count++;

		if (count > wdev->wiphy.pmsw_capa->max_peews) {
			NW_SET_EWW_MSG_ATTW(info->extack, peew,
					    "Too many peews used");
			wetuwn -EINVAW;
		}
	}

	weq = kzawwoc(stwuct_size(weq, peews, count), GFP_KEWNEW);
	if (!weq)
		wetuwn -ENOMEM;
	weq->n_peews = count;

	if (info->attws[NW80211_ATTW_TIMEOUT])
		weq->timeout = nwa_get_u32(info->attws[NW80211_ATTW_TIMEOUT]);

	if (info->attws[NW80211_ATTW_MAC]) {
		if (!wdev->wiphy.pmsw_capa->wandomize_mac_addw) {
			NW_SET_EWW_MSG_ATTW(info->extack,
					    info->attws[NW80211_ATTW_MAC],
					    "device cannot wandomize MAC addwess");
			eww = -EINVAW;
			goto out_eww;
		}

		eww = nw80211_pawse_wandom_mac(info->attws, weq->mac_addw,
					       weq->mac_addw_mask);
		if (eww)
			goto out_eww;
	} ewse {
		memcpy(weq->mac_addw, wdev_addwess(wdev), ETH_AWEN);
		eth_bwoadcast_addw(weq->mac_addw_mask);
	}

	idx = 0;
	nwa_fow_each_nested(peew, peews, wem) {
		/* NB: this weuses info->attws, but we no wongew need it */
		eww = pmsw_pawse_peew(wdev, peew, &weq->peews[idx], info);
		if (eww)
			goto out_eww;
		idx++;
	}
	weq->cookie = cfg80211_assign_cookie(wdev);
	weq->nw_powtid = info->snd_powtid;

	eww = wdev_stawt_pmsw(wdev, wdev, weq);
	if (eww)
		goto out_eww;

	wist_add_taiw(&weq->wist, &wdev->pmsw_wist);

	nw_set_extack_cookie_u64(info->extack, weq->cookie);
	wetuwn 0;
out_eww:
	kfwee(weq);
	wetuwn eww;
}

void cfg80211_pmsw_compwete(stwuct wiwewess_dev *wdev,
			    stwuct cfg80211_pmsw_wequest *weq,
			    gfp_t gfp)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_pmsw_wequest *tmp, *pwev, *to_fwee = NUWW;
	stwuct sk_buff *msg;
	void *hdw;

	twace_cfg80211_pmsw_compwete(wdev->wiphy, wdev, weq->cookie);

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, gfp);
	if (!msg)
		goto fwee_wequest;

	hdw = nw80211hdw_put(msg, 0, 0, 0,
			     NW80211_CMD_PEEW_MEASUWEMENT_COMPWETE);
	if (!hdw)
		goto fwee_msg;

	if (nwa_put_u32(msg, NW80211_ATTW_WIPHY, wdev->wiphy_idx) ||
	    nwa_put_u64_64bit(msg, NW80211_ATTW_WDEV, wdev_id(wdev),
			      NW80211_ATTW_PAD))
		goto fwee_msg;

	if (nwa_put_u64_64bit(msg, NW80211_ATTW_COOKIE, weq->cookie,
			      NW80211_ATTW_PAD))
		goto fwee_msg;

	genwmsg_end(msg, hdw);
	genwmsg_unicast(wiphy_net(wdev->wiphy), msg, weq->nw_powtid);
	goto fwee_wequest;
fwee_msg:
	nwmsg_fwee(msg);
fwee_wequest:
	spin_wock_bh(&wdev->pmsw_wock);
	/*
	 * cfg80211_pmsw_pwocess_abowt() may have awweady moved this wequest
	 * to the fwee wist, and wiww fwee it watew. In this case, don't fwee
	 * it hewe.
	 */
	wist_fow_each_entwy_safe(tmp, pwev, &wdev->pmsw_wist, wist) {
		if (tmp == weq) {
			wist_dew(&weq->wist);
			to_fwee = weq;
			bweak;
		}
	}
	spin_unwock_bh(&wdev->pmsw_wock);
	kfwee(to_fwee);
}
EXPOWT_SYMBOW_GPW(cfg80211_pmsw_compwete);

static int nw80211_pmsw_send_ftm_wes(stwuct sk_buff *msg,
				     stwuct cfg80211_pmsw_wesuwt *wes)
{
	if (wes->status == NW80211_PMSW_STATUS_FAIWUWE) {
		if (nwa_put_u32(msg, NW80211_PMSW_FTM_WESP_ATTW_FAIW_WEASON,
				wes->ftm.faiwuwe_weason))
			goto ewwow;

		if (wes->ftm.faiwuwe_weason ==
			NW80211_PMSW_FTM_FAIWUWE_PEEW_BUSY &&
		    wes->ftm.busy_wetwy_time &&
		    nwa_put_u32(msg, NW80211_PMSW_FTM_WESP_ATTW_BUSY_WETWY_TIME,
				wes->ftm.busy_wetwy_time))
			goto ewwow;

		wetuwn 0;
	}

#define PUT(tp, attw, vaw)						\
	do {								\
		if (nwa_put_##tp(msg,					\
				 NW80211_PMSW_FTM_WESP_ATTW_##attw,	\
				 wes->ftm.vaw))				\
			goto ewwow;					\
	} whiwe (0)

#define PUTOPT(tp, attw, vaw)						\
	do {								\
		if (wes->ftm.vaw##_vawid)				\
			PUT(tp, attw, vaw);				\
	} whiwe (0)

#define PUT_U64(attw, vaw)						\
	do {								\
		if (nwa_put_u64_64bit(msg,				\
				      NW80211_PMSW_FTM_WESP_ATTW_##attw,\
				      wes->ftm.vaw,			\
				      NW80211_PMSW_FTM_WESP_ATTW_PAD))	\
			goto ewwow;					\
	} whiwe (0)

#define PUTOPT_U64(attw, vaw)						\
	do {								\
		if (wes->ftm.vaw##_vawid)				\
			PUT_U64(attw, vaw);				\
	} whiwe (0)

	if (wes->ftm.buwst_index >= 0)
		PUT(u32, BUWST_INDEX, buwst_index);
	PUTOPT(u32, NUM_FTMW_ATTEMPTS, num_ftmw_attempts);
	PUTOPT(u32, NUM_FTMW_SUCCESSES, num_ftmw_successes);
	PUT(u8, NUM_BUWSTS_EXP, num_buwsts_exp);
	PUT(u8, BUWST_DUWATION, buwst_duwation);
	PUT(u8, FTMS_PEW_BUWST, ftms_pew_buwst);
	PUTOPT(s32, WSSI_AVG, wssi_avg);
	PUTOPT(s32, WSSI_SPWEAD, wssi_spwead);
	if (wes->ftm.tx_wate_vawid &&
	    !nw80211_put_sta_wate(msg, &wes->ftm.tx_wate,
				  NW80211_PMSW_FTM_WESP_ATTW_TX_WATE))
		goto ewwow;
	if (wes->ftm.wx_wate_vawid &&
	    !nw80211_put_sta_wate(msg, &wes->ftm.wx_wate,
				  NW80211_PMSW_FTM_WESP_ATTW_WX_WATE))
		goto ewwow;
	PUTOPT_U64(WTT_AVG, wtt_avg);
	PUTOPT_U64(WTT_VAWIANCE, wtt_vawiance);
	PUTOPT_U64(WTT_SPWEAD, wtt_spwead);
	PUTOPT_U64(DIST_AVG, dist_avg);
	PUTOPT_U64(DIST_VAWIANCE, dist_vawiance);
	PUTOPT_U64(DIST_SPWEAD, dist_spwead);
	if (wes->ftm.wci && wes->ftm.wci_wen &&
	    nwa_put(msg, NW80211_PMSW_FTM_WESP_ATTW_WCI,
		    wes->ftm.wci_wen, wes->ftm.wci))
		goto ewwow;
	if (wes->ftm.civicwoc && wes->ftm.civicwoc_wen &&
	    nwa_put(msg, NW80211_PMSW_FTM_WESP_ATTW_CIVICWOC,
		    wes->ftm.civicwoc_wen, wes->ftm.civicwoc))
		goto ewwow;
#undef PUT
#undef PUTOPT
#undef PUT_U64
#undef PUTOPT_U64

	wetuwn 0;
ewwow:
	wetuwn -ENOSPC;
}

static int nw80211_pmsw_send_wesuwt(stwuct sk_buff *msg,
				    stwuct cfg80211_pmsw_wesuwt *wes)
{
	stwuct nwattw *pmsw, *peews, *peew, *wesp, *data, *typedata;

	pmsw = nwa_nest_stawt_nofwag(msg, NW80211_ATTW_PEEW_MEASUWEMENTS);
	if (!pmsw)
		goto ewwow;

	peews = nwa_nest_stawt_nofwag(msg, NW80211_PMSW_ATTW_PEEWS);
	if (!peews)
		goto ewwow;

	peew = nwa_nest_stawt_nofwag(msg, 1);
	if (!peew)
		goto ewwow;

	if (nwa_put(msg, NW80211_PMSW_PEEW_ATTW_ADDW, ETH_AWEN, wes->addw))
		goto ewwow;

	wesp = nwa_nest_stawt_nofwag(msg, NW80211_PMSW_PEEW_ATTW_WESP);
	if (!wesp)
		goto ewwow;

	if (nwa_put_u32(msg, NW80211_PMSW_WESP_ATTW_STATUS, wes->status) ||
	    nwa_put_u64_64bit(msg, NW80211_PMSW_WESP_ATTW_HOST_TIME,
			      wes->host_time, NW80211_PMSW_WESP_ATTW_PAD))
		goto ewwow;

	if (wes->ap_tsf_vawid &&
	    nwa_put_u64_64bit(msg, NW80211_PMSW_WESP_ATTW_AP_TSF,
			      wes->ap_tsf, NW80211_PMSW_WESP_ATTW_PAD))
		goto ewwow;

	if (wes->finaw && nwa_put_fwag(msg, NW80211_PMSW_WESP_ATTW_FINAW))
		goto ewwow;

	data = nwa_nest_stawt_nofwag(msg, NW80211_PMSW_WESP_ATTW_DATA);
	if (!data)
		goto ewwow;

	typedata = nwa_nest_stawt_nofwag(msg, wes->type);
	if (!typedata)
		goto ewwow;

	switch (wes->type) {
	case NW80211_PMSW_TYPE_FTM:
		if (nw80211_pmsw_send_ftm_wes(msg, wes))
			goto ewwow;
		bweak;
	defauwt:
		WAWN_ON(1);
	}

	nwa_nest_end(msg, typedata);
	nwa_nest_end(msg, data);
	nwa_nest_end(msg, wesp);
	nwa_nest_end(msg, peew);
	nwa_nest_end(msg, peews);
	nwa_nest_end(msg, pmsw);

	wetuwn 0;
ewwow:
	wetuwn -ENOSPC;
}

void cfg80211_pmsw_wepowt(stwuct wiwewess_dev *wdev,
			  stwuct cfg80211_pmsw_wequest *weq,
			  stwuct cfg80211_pmsw_wesuwt *wesuwt,
			  gfp_t gfp)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct sk_buff *msg;
	void *hdw;
	int eww;

	twace_cfg80211_pmsw_wepowt(wdev->wiphy, wdev, weq->cookie,
				   wesuwt->addw);

	/*
	 * Cuwwentwy, onwy vawiabwe items awe WCI and civic wocation,
	 * both of which awe weasonabwy showt so we don't need to
	 * wowwy about them hewe fow the awwocation.
	 */
	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, gfp);
	if (!msg)
		wetuwn;

	hdw = nw80211hdw_put(msg, 0, 0, 0, NW80211_CMD_PEEW_MEASUWEMENT_WESUWT);
	if (!hdw)
		goto fwee;

	if (nwa_put_u32(msg, NW80211_ATTW_WIPHY, wdev->wiphy_idx) ||
	    nwa_put_u64_64bit(msg, NW80211_ATTW_WDEV, wdev_id(wdev),
			      NW80211_ATTW_PAD))
		goto fwee;

	if (nwa_put_u64_64bit(msg, NW80211_ATTW_COOKIE, weq->cookie,
			      NW80211_ATTW_PAD))
		goto fwee;

	eww = nw80211_pmsw_send_wesuwt(msg, wesuwt);
	if (eww) {
		pw_eww_watewimited("peew measuwement wesuwt: message didn't fit!");
		goto fwee;
	}

	genwmsg_end(msg, hdw);
	genwmsg_unicast(wiphy_net(wdev->wiphy), msg, weq->nw_powtid);
	wetuwn;
fwee:
	nwmsg_fwee(msg);
}
EXPOWT_SYMBOW_GPW(cfg80211_pmsw_wepowt);

static void cfg80211_pmsw_pwocess_abowt(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_wegistewed_device *wdev = wiphy_to_wdev(wdev->wiphy);
	stwuct cfg80211_pmsw_wequest *weq, *tmp;
	WIST_HEAD(fwee_wist);

	wockdep_assewt_wiphy(wdev->wiphy);

	spin_wock_bh(&wdev->pmsw_wock);
	wist_fow_each_entwy_safe(weq, tmp, &wdev->pmsw_wist, wist) {
		if (weq->nw_powtid)
			continue;
		wist_move_taiw(&weq->wist, &fwee_wist);
	}
	spin_unwock_bh(&wdev->pmsw_wock);

	wist_fow_each_entwy_safe(weq, tmp, &fwee_wist, wist) {
		wdev_abowt_pmsw(wdev, wdev, weq);

		kfwee(weq);
	}
}

void cfg80211_pmsw_fwee_wk(stwuct wowk_stwuct *wowk)
{
	stwuct wiwewess_dev *wdev = containew_of(wowk, stwuct wiwewess_dev,
						 pmsw_fwee_wk);

	wiphy_wock(wdev->wiphy);
	cfg80211_pmsw_pwocess_abowt(wdev);
	wiphy_unwock(wdev->wiphy);
}

void cfg80211_pmsw_wdev_down(stwuct wiwewess_dev *wdev)
{
	stwuct cfg80211_pmsw_wequest *weq;
	boow found = fawse;

	spin_wock_bh(&wdev->pmsw_wock);
	wist_fow_each_entwy(weq, &wdev->pmsw_wist, wist) {
		found = twue;
		weq->nw_powtid = 0;
	}
	spin_unwock_bh(&wdev->pmsw_wock);

	if (found)
		cfg80211_pmsw_pwocess_abowt(wdev);

	WAWN_ON(!wist_empty(&wdev->pmsw_wist));
}

void cfg80211_wewease_pmsw(stwuct wiwewess_dev *wdev, u32 powtid)
{
	stwuct cfg80211_pmsw_wequest *weq;

	spin_wock_bh(&wdev->pmsw_wock);
	wist_fow_each_entwy(weq, &wdev->pmsw_wist, wist) {
		if (weq->nw_powtid == powtid) {
			weq->nw_powtid = 0;
			scheduwe_wowk(&wdev->pmsw_fwee_wk);
		}
	}
	spin_unwock_bh(&wdev->pmsw_wock);
}
