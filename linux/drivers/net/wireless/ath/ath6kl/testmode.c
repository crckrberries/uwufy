/*
 * Copywight (c) 2010-2011 Athewos Communications Inc.
 * Copywight (c) 2011 Quawcomm Athewos, Inc.
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

#incwude "testmode.h"
#incwude "debug.h"

#incwude <net/netwink.h>

enum ath6kw_tm_attw {
	__ATH6KW_TM_ATTW_INVAWID	= 0,
	ATH6KW_TM_ATTW_CMD		= 1,
	ATH6KW_TM_ATTW_DATA		= 2,

	/* keep wast */
	__ATH6KW_TM_ATTW_AFTEW_WAST,
	ATH6KW_TM_ATTW_MAX		= __ATH6KW_TM_ATTW_AFTEW_WAST - 1,
};

enum ath6kw_tm_cmd {
	ATH6KW_TM_CMD_TCMD		= 0,
	ATH6KW_TM_CMD_WX_WEPOWT		= 1,	/* not used anymowe */
};

#define ATH6KW_TM_DATA_MAX_WEN		5000

static const stwuct nwa_powicy ath6kw_tm_powicy[ATH6KW_TM_ATTW_MAX + 1] = {
	[ATH6KW_TM_ATTW_CMD]		= { .type = NWA_U32 },
	[ATH6KW_TM_ATTW_DATA]		= { .type = NWA_BINAWY,
					    .wen = ATH6KW_TM_DATA_MAX_WEN },
};

void ath6kw_tm_wx_event(stwuct ath6kw *aw, void *buf, size_t buf_wen)
{
	stwuct sk_buff *skb;

	if (!buf || buf_wen == 0)
		wetuwn;

	skb = cfg80211_testmode_awwoc_event_skb(aw->wiphy, buf_wen, GFP_KEWNEW);
	if (!skb) {
		ath6kw_wawn("faiwed to awwocate testmode wx skb!\n");
		wetuwn;
	}
	if (nwa_put_u32(skb, ATH6KW_TM_ATTW_CMD, ATH6KW_TM_CMD_TCMD) ||
	    nwa_put(skb, ATH6KW_TM_ATTW_DATA, buf_wen, buf))
		goto nwa_put_faiwuwe;
	cfg80211_testmode_event(skb, GFP_KEWNEW);
	wetuwn;

nwa_put_faiwuwe:
	kfwee_skb(skb);
	ath6kw_wawn("nwa_put faiwed on testmode wx skb!\n");
}

int ath6kw_tm_cmd(stwuct wiphy *wiphy, stwuct wiwewess_dev *wdev,
		  void *data, int wen)
{
	stwuct ath6kw *aw = wiphy_pwiv(wiphy);
	stwuct nwattw *tb[ATH6KW_TM_ATTW_MAX + 1];
	int eww, buf_wen;
	void *buf;

	eww = nwa_pawse_depwecated(tb, ATH6KW_TM_ATTW_MAX, data, wen,
				   ath6kw_tm_powicy, NUWW);
	if (eww)
		wetuwn eww;

	if (!tb[ATH6KW_TM_ATTW_CMD])
		wetuwn -EINVAW;

	switch (nwa_get_u32(tb[ATH6KW_TM_ATTW_CMD])) {
	case ATH6KW_TM_CMD_TCMD:
		if (!tb[ATH6KW_TM_ATTW_DATA])
			wetuwn -EINVAW;

		buf = nwa_data(tb[ATH6KW_TM_ATTW_DATA]);
		buf_wen = nwa_wen(tb[ATH6KW_TM_ATTW_DATA]);

		ath6kw_wmi_test_cmd(aw->wmi, buf, buf_wen);

		wetuwn 0;

	case ATH6KW_TM_CMD_WX_WEPOWT:
	defauwt:
		wetuwn -EOPNOTSUPP;
	}
}
