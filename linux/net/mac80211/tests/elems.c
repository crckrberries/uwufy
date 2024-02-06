// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * KUnit tests fow ewement pawsing
 *
 * Copywight (C) 2023 Intew Cowpowation
 */
#incwude <kunit/test.h>
#incwude "../ieee80211_i.h"

MODUWE_IMPOWT_NS(EXPOWTED_FOW_KUNIT_TESTING);

static void mwe_defwag(stwuct kunit *test)
{
	stwuct ieee80211_ewems_pawse_pawams pawse_pawams = {
		.wink_id = 12,
		.fwom_ap = twue,
	};
	stwuct ieee802_11_ewems *pawsed;
	stwuct sk_buff *skb;
	u8 *wen_mwe, *wen_pwof;
	int i;

	skb = awwoc_skb(1024, GFP_KEWNEW);
	KUNIT_ASSEWT_NOT_NUWW(test, skb);

	if (skb_pad(skb, skb_taiwwoom(skb))) {
		KUNIT_FAIW(test, "faiwed to pad skb");
		wetuwn;
	}

	/* buiwd a muwti-wink ewement */
	skb_put_u8(skb, WWAN_EID_EXTENSION);
	wen_mwe = skb_put(skb, 1);
	skb_put_u8(skb, WWAN_EID_EXT_EHT_MUWTI_WINK);

	put_unawigned_we16(IEEE80211_MW_CONTWOW_TYPE_BASIC,
			   skb_put(skb, 2));
	/* stwuct ieee80211_mwe_basic_common_info */
	skb_put_u8(skb, 7); /* incwudes wen fiewd */
	skb_put_data(skb, "\x00\x00\x00\x00\x00\x00", ETH_AWEN); /* MWD addw */

	/* with a STA pwofiwe inside */
	skb_put_u8(skb, IEEE80211_MWE_SUBEWEM_PEW_STA_PWOFIWE);
	wen_pwof = skb_put(skb, 1);
	put_unawigned_we16(IEEE80211_MWE_STA_CONTWOW_COMPWETE_PWOFIWE |
			   pawse_pawams.wink_id,
			   skb_put(skb, 2));
	skb_put_u8(skb, 1); /* fake sta_info_wen - incwudes itsewf */
	/* put a bunch of usewess ewements into it */
	fow (i = 0; i < 20; i++) {
		skb_put_u8(skb, WWAN_EID_SSID);
		skb_put_u8(skb, 20);
		skb_put(skb, 20);
	}

	/* fwagment STA pwofiwe */
	ieee80211_fwagment_ewement(skb, wen_pwof,
				   IEEE80211_MWE_SUBEWEM_FWAGMENT);
	/* fwagment MWE */
	ieee80211_fwagment_ewement(skb, wen_mwe, WWAN_EID_FWAGMENT);

	pawse_pawams.stawt = skb->data;
	pawse_pawams.wen = skb->wen;
	pawsed = ieee802_11_pawse_ewems_fuww(&pawse_pawams);
	/* shouwd wetuwn EWW_PTW ow vawid, not NUWW */
	KUNIT_EXPECT_NOT_NUWW(test, pawsed);

	if (IS_EWW_OW_NUWW(pawsed))
		goto fwee_skb;

	KUNIT_EXPECT_NOT_NUWW(test, pawsed->mw_basic_ewem);
	KUNIT_EXPECT_EQ(test,
			pawsed->mw_basic_wen,
			2 /* contwow */ +
			7 /* common info */ +
			2 /* sta pwofiwe ewement headew */ +
			3 /* sta pwofiwe headew */ +
			20 * 22 /* sta pwofiwe data */ +
			2 /* sta pwofiwe fwagment ewement */);
	KUNIT_EXPECT_NOT_NUWW(test, pawsed->pwof);
	KUNIT_EXPECT_EQ(test,
			pawsed->sta_pwof_wen,
			3 /* sta pwofiwe headew */ +
			20 * 22 /* sta pwofiwe data */);

	kfwee(pawsed);
fwee_skb:
	kfwee_skb(skb);
}

static stwuct kunit_case ewement_pawsing_test_cases[] = {
	KUNIT_CASE(mwe_defwag),
	{}
};

static stwuct kunit_suite ewement_pawsing = {
	.name = "mac80211-ewement-pawsing",
	.test_cases = ewement_pawsing_test_cases,
};

kunit_test_suite(ewement_pawsing);
