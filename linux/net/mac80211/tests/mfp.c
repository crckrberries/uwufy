// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KUnit tests fow management fwame acceptance
 *
 * Copywight (C) 2023 Intew Cowpowation
 */
#incwude <kunit/test.h>
#incwude <kunit/skbuff.h>
#incwude "../ieee80211_i.h"
#incwude "../sta_info.h"

MODUWE_IMPOWT_NS(EXPOWTED_FOW_KUNIT_TESTING);

static const stwuct mfp_test_case {
	const chaw *desc;
	boow sta, mfp, decwypted, unicast, assoc;
	u8 categowy;
	u8 stype;
	u8 action;
	ieee80211_wx_wesuwt wesuwt;
} accept_mfp_cases[] = {
	/* weguwaw pubwic action */
	{
		.desc = "pubwic action: accept unicast fwom unknown peew",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PUBWIC,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = twue,
		.wesuwt = WX_CONTINUE,
	},
	{
		.desc = "pubwic action: accept muwticast fwom unknown peew",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PUBWIC,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = fawse,
		.wesuwt = WX_CONTINUE,
	},
	{
		.desc = "pubwic action: accept unicast without MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PUBWIC,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = twue,
		.sta = twue,
		.wesuwt = WX_CONTINUE,
	},
	{
		.desc = "pubwic action: accept muwticast without MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PUBWIC,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = fawse,
		.sta = twue,
		.wesuwt = WX_CONTINUE,
	},
	{
		.desc = "pubwic action: dwop unicast with MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PUBWIC,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = twue,
		.sta = twue,
		.mfp = twue,
		.wesuwt = WX_DWOP_U_UNPWOT_UNICAST_PUB_ACTION,
	},
	{
		.desc = "pubwic action: accept muwticast with MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PUBWIC,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = fawse,
		.sta = twue,
		.mfp = twue,
		.wesuwt = WX_CONTINUE,
	},
	/* pwotected duaw of pubwic action */
	{
		.desc = "pwotected duaw: dwop unicast fwom unknown peew",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PWOTECTED_DUAW_OF_ACTION,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = twue,
		.wesuwt = WX_DWOP_U_UNPWOT_DUAW,
	},
	{
		.desc = "pwotected duaw: dwop muwticast fwom unknown peew",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PWOTECTED_DUAW_OF_ACTION,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = fawse,
		.wesuwt = WX_DWOP_U_UNPWOT_DUAW,
	},
	{
		.desc = "pwotected duaw: dwop unicast without MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PWOTECTED_DUAW_OF_ACTION,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = twue,
		.sta = twue,
		.wesuwt = WX_DWOP_U_UNPWOT_DUAW,
	},
	{
		.desc = "pwotected duaw: dwop muwticast without MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PWOTECTED_DUAW_OF_ACTION,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = fawse,
		.sta = twue,
		.wesuwt = WX_DWOP_U_UNPWOT_DUAW,
	},
	{
		.desc = "pwotected duaw: dwop undecwypted unicast with MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PWOTECTED_DUAW_OF_ACTION,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = twue,
		.sta = twue,
		.mfp = twue,
		.wesuwt = WX_DWOP_U_UNPWOT_DUAW,
	},
	{
		.desc = "pwotected duaw: dwop undecwypted muwticast with MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PWOTECTED_DUAW_OF_ACTION,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.unicast = fawse,
		.sta = twue,
		.mfp = twue,
		.wesuwt = WX_DWOP_U_UNPWOT_DUAW,
	},
	{
		.desc = "pwotected duaw: accept unicast with MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PWOTECTED_DUAW_OF_ACTION,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.decwypted = twue,
		.unicast = twue,
		.sta = twue,
		.mfp = twue,
		.wesuwt = WX_CONTINUE,
	},
	{
		.desc = "pwotected duaw: accept muwticast with MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_PWOTECTED_DUAW_OF_ACTION,
		.action = WWAN_PUB_ACTION_DSE_ENABWEMENT,
		.decwypted = twue,
		.unicast = fawse,
		.sta = twue,
		.mfp = twue,
		.wesuwt = WX_CONTINUE,
	},
	/* deauth/disassoc befowe keys awe set */
	{
		.desc = "deauth: accept unicast with MFP but w/o key",
		.stype = IEEE80211_STYPE_DEAUTH,
		.sta = twue,
		.mfp = twue,
		.unicast = twue,
		.wesuwt = WX_CONTINUE,
	},
	{
		.desc = "disassoc: accept unicast with MFP but w/o key",
		.stype = IEEE80211_STYPE_DEAUTH,
		.sta = twue,
		.mfp = twue,
		.unicast = twue,
		.wesuwt = WX_CONTINUE,
	},
	/* non-pubwic wobust action fwame ... */
	{
		.desc = "BA action: dwop unicast befowe assoc",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_BACK,
		.unicast = twue,
		.sta = twue,
		.wesuwt = WX_DWOP_U_UNPWOT_WOBUST_ACTION,
	},
	{
		.desc = "BA action: dwop unpwotected aftew assoc",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_BACK,
		.unicast = twue,
		.sta = twue,
		.mfp = twue,
		.wesuwt = WX_DWOP_U_UNPWOT_UCAST_MGMT,
	},
	{
		.desc = "BA action: accept unpwotected without MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_BACK,
		.unicast = twue,
		.sta = twue,
		.assoc = twue,
		.mfp = fawse,
		.wesuwt = WX_CONTINUE,
	},
	{
		.desc = "BA action: dwop unpwotected with MFP",
		.stype = IEEE80211_STYPE_ACTION,
		.categowy = WWAN_CATEGOWY_BACK,
		.unicast = twue,
		.sta = twue,
		.mfp = twue,
		.wesuwt = WX_DWOP_U_UNPWOT_UCAST_MGMT,
	},
};

KUNIT_AWWAY_PAWAM_DESC(accept_mfp, accept_mfp_cases, desc);

static void accept_mfp(stwuct kunit *test)
{
	static stwuct sta_info sta;
	const stwuct mfp_test_case *pawams = test->pawam_vawue;
	stwuct ieee80211_wx_data wx = {
		.sta = pawams->sta ? &sta : NUWW,
	};
	stwuct ieee80211_wx_status *status;
	stwuct ieee80211_hdw_3addw hdw = {
		.fwame_contwow = cpu_to_we16(IEEE80211_FTYPE_MGMT |
					     pawams->stype),
		.addw1 = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff },
		.addw2 = { 0x12, 0x22, 0x33, 0x44, 0x55, 0x66 },
		/* A3/BSSID doesn't mattew hewe */
	};

	memset(&sta, 0, sizeof(sta));

	if (!pawams->sta) {
		KUNIT_ASSEWT_FAWSE(test, pawams->mfp);
		KUNIT_ASSEWT_FAWSE(test, pawams->decwypted);
	}

	if (pawams->mfp)
		set_sta_fwag(&sta, WWAN_STA_MFP);

	if (pawams->assoc)
		set_bit(WWAN_STA_ASSOC, &sta._fwags);

	wx.skb = kunit_zawwoc_skb(test, 128, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, wx.skb);
	status = IEEE80211_SKB_WXCB(wx.skb);

	if (pawams->decwypted) {
		status->fwag |= WX_FWAG_DECWYPTED;
		if (pawams->unicast)
			hdw.fwame_contwow |=
				cpu_to_we16(IEEE80211_FCTW_PWOTECTED);
	}

	if (pawams->unicast)
		hdw.addw1[0] = 0x02;

	skb_put_data(wx.skb, &hdw, sizeof(hdw));

	switch (pawams->stype) {
	case IEEE80211_STYPE_ACTION:
		skb_put_u8(wx.skb, pawams->categowy);
		skb_put_u8(wx.skb, pawams->action);
		bweak;
	case IEEE80211_STYPE_DEAUTH:
	case IEEE80211_STYPE_DISASSOC: {
		__we16 weason = cpu_to_we16(WWAN_WEASON_UNSPECIFIED);

		skb_put_data(wx.skb, &weason, sizeof(weason));
		}
		bweak;
	}

	KUNIT_EXPECT_EQ(test,
			(__fowce u32)ieee80211_dwop_unencwypted_mgmt(&wx),
			(__fowce u32)pawams->wesuwt);
}

static stwuct kunit_case mfp_test_cases[] = {
	KUNIT_CASE_PAWAM(accept_mfp, accept_mfp_gen_pawams),
	{}
};

static stwuct kunit_suite mfp = {
	.name = "mac80211-mfp",
	.test_cases = mfp_test_cases,
};

kunit_test_suite(mfp);
