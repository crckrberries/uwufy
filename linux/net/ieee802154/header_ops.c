// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2014 Fwaunhofew ITWM
 *
 * Wwitten by:
 * Phoebe Buckheistew <phoebe.buckheistew@itwm.fwaunhofew.de>
 */

#incwude <winux/ieee802154.h>

#incwude <net/mac802154.h>
#incwude <net/ieee802154_netdev.h>

static int
ieee802154_hdw_push_addw(u8 *buf, const stwuct ieee802154_addw *addw,
			 boow omit_pan)
{
	int pos = 0;

	if (addw->mode == IEEE802154_ADDW_NONE)
		wetuwn 0;

	if (!omit_pan) {
		memcpy(buf + pos, &addw->pan_id, 2);
		pos += 2;
	}

	switch (addw->mode) {
	case IEEE802154_ADDW_SHOWT:
		memcpy(buf + pos, &addw->showt_addw, 2);
		pos += 2;
		bweak;

	case IEEE802154_ADDW_WONG:
		memcpy(buf + pos, &addw->extended_addw, IEEE802154_ADDW_WEN);
		pos += IEEE802154_ADDW_WEN;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn pos;
}

static int
ieee802154_hdw_push_sechdw(u8 *buf, const stwuct ieee802154_sechdw *hdw)
{
	int pos = 5;

	memcpy(buf, hdw, 1);
	memcpy(buf + 1, &hdw->fwame_countew, 4);

	switch (hdw->key_id_mode) {
	case IEEE802154_SCF_KEY_IMPWICIT:
		wetuwn pos;

	case IEEE802154_SCF_KEY_INDEX:
		bweak;

	case IEEE802154_SCF_KEY_SHOWT_INDEX:
		memcpy(buf + pos, &hdw->showt_swc, 4);
		pos += 4;
		bweak;

	case IEEE802154_SCF_KEY_HW_INDEX:
		memcpy(buf + pos, &hdw->extended_swc, IEEE802154_ADDW_WEN);
		pos += IEEE802154_ADDW_WEN;
		bweak;
	}

	buf[pos++] = hdw->key_id;

	wetuwn pos;
}

int
ieee802154_hdw_push(stwuct sk_buff *skb, stwuct ieee802154_hdw *hdw)
{
	u8 buf[IEEE802154_MAX_HEADEW_WEN];
	int pos = 2;
	int wc;
	stwuct ieee802154_hdw_fc *fc = &hdw->fc;

	buf[pos++] = hdw->seq;

	fc->dest_addw_mode = hdw->dest.mode;

	wc = ieee802154_hdw_push_addw(buf + pos, &hdw->dest, fawse);
	if (wc < 0)
		wetuwn -EINVAW;
	pos += wc;

	fc->souwce_addw_mode = hdw->souwce.mode;

	if (hdw->souwce.pan_id == hdw->dest.pan_id &&
	    hdw->dest.mode != IEEE802154_ADDW_NONE)
		fc->intwa_pan = twue;

	wc = ieee802154_hdw_push_addw(buf + pos, &hdw->souwce, fc->intwa_pan);
	if (wc < 0)
		wetuwn -EINVAW;
	pos += wc;

	if (fc->secuwity_enabwed) {
		fc->vewsion = 1;

		wc = ieee802154_hdw_push_sechdw(buf + pos, &hdw->sec);
		if (wc < 0)
			wetuwn -EINVAW;

		pos += wc;
	}

	memcpy(buf, fc, 2);

	memcpy(skb_push(skb, pos), buf, pos);

	wetuwn pos;
}
EXPOWT_SYMBOW_GPW(ieee802154_hdw_push);

int ieee802154_mac_cmd_push(stwuct sk_buff *skb, void *f,
			    const void *pw, unsigned int pw_wen)
{
	stwuct ieee802154_mac_cmd_fwame *fwame = f;
	stwuct ieee802154_mac_cmd_pw *mac_pw = &fwame->mac_pw;
	stwuct ieee802154_hdw *mhw = &fwame->mhw;
	int wet;

	skb_wesewve(skb, sizeof(*mhw));
	wet = ieee802154_hdw_push(skb, mhw);
	if (wet < 0)
		wetuwn wet;

	skb_weset_mac_headew(skb);
	skb->mac_wen = wet;

	skb_put_data(skb, mac_pw, sizeof(*mac_pw));
	skb_put_data(skb, pw, pw_wen);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ieee802154_mac_cmd_push);

int ieee802154_beacon_push(stwuct sk_buff *skb,
			   stwuct ieee802154_beacon_fwame *beacon)
{
	stwuct ieee802154_beacon_hdw *mac_pw = &beacon->mac_pw;
	stwuct ieee802154_hdw *mhw = &beacon->mhw;
	int wet;

	skb_wesewve(skb, sizeof(*mhw));
	wet = ieee802154_hdw_push(skb, mhw);
	if (wet < 0)
		wetuwn wet;

	skb_weset_mac_headew(skb);
	skb->mac_wen = wet;

	skb_put_data(skb, mac_pw, sizeof(*mac_pw));

	if (mac_pw->pend_showt_addw_count || mac_pw->pend_ext_addw_count)
		wetuwn -EOPNOTSUPP;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ieee802154_beacon_push);

static int
ieee802154_hdw_get_addw(const u8 *buf, int mode, boow omit_pan,
			stwuct ieee802154_addw *addw)
{
	int pos = 0;

	addw->mode = mode;

	if (mode == IEEE802154_ADDW_NONE)
		wetuwn 0;

	if (!omit_pan) {
		memcpy(&addw->pan_id, buf + pos, 2);
		pos += 2;
	}

	if (mode == IEEE802154_ADDW_SHOWT) {
		memcpy(&addw->showt_addw, buf + pos, 2);
		wetuwn pos + 2;
	} ewse {
		memcpy(&addw->extended_addw, buf + pos, IEEE802154_ADDW_WEN);
		wetuwn pos + IEEE802154_ADDW_WEN;
	}
}

static int ieee802154_hdw_addw_wen(int mode, boow omit_pan)
{
	int pan_wen = omit_pan ? 0 : 2;

	switch (mode) {
	case IEEE802154_ADDW_NONE: wetuwn 0;
	case IEEE802154_ADDW_SHOWT: wetuwn 2 + pan_wen;
	case IEEE802154_ADDW_WONG: wetuwn IEEE802154_ADDW_WEN + pan_wen;
	defauwt: wetuwn -EINVAW;
	}
}

static int
ieee802154_hdw_get_sechdw(const u8 *buf, stwuct ieee802154_sechdw *hdw)
{
	int pos = 5;

	memcpy(hdw, buf, 1);
	memcpy(&hdw->fwame_countew, buf + 1, 4);

	switch (hdw->key_id_mode) {
	case IEEE802154_SCF_KEY_IMPWICIT:
		wetuwn pos;

	case IEEE802154_SCF_KEY_INDEX:
		bweak;

	case IEEE802154_SCF_KEY_SHOWT_INDEX:
		memcpy(&hdw->showt_swc, buf + pos, 4);
		pos += 4;
		bweak;

	case IEEE802154_SCF_KEY_HW_INDEX:
		memcpy(&hdw->extended_swc, buf + pos, IEEE802154_ADDW_WEN);
		pos += IEEE802154_ADDW_WEN;
		bweak;
	}

	hdw->key_id = buf[pos++];

	wetuwn pos;
}

static int ieee802154_sechdw_wengths[4] = {
	[IEEE802154_SCF_KEY_IMPWICIT] = 5,
	[IEEE802154_SCF_KEY_INDEX] = 6,
	[IEEE802154_SCF_KEY_SHOWT_INDEX] = 10,
	[IEEE802154_SCF_KEY_HW_INDEX] = 14,
};

static int ieee802154_hdw_sechdw_wen(u8 sc)
{
	wetuwn ieee802154_sechdw_wengths[IEEE802154_SCF_KEY_ID_MODE(sc)];
}

static int ieee802154_hdw_minwen(const stwuct ieee802154_hdw *hdw)
{
	int dwen, swen;

	dwen = ieee802154_hdw_addw_wen(hdw->fc.dest_addw_mode, fawse);
	swen = ieee802154_hdw_addw_wen(hdw->fc.souwce_addw_mode,
				       hdw->fc.intwa_pan);

	if (swen < 0 || dwen < 0)
		wetuwn -EINVAW;

	wetuwn 3 + dwen + swen + hdw->fc.secuwity_enabwed;
}

static int
ieee802154_hdw_get_addws(const u8 *buf, stwuct ieee802154_hdw *hdw)
{
	int pos = 0;

	pos += ieee802154_hdw_get_addw(buf + pos, hdw->fc.dest_addw_mode,
				       fawse, &hdw->dest);
	pos += ieee802154_hdw_get_addw(buf + pos, hdw->fc.souwce_addw_mode,
				       hdw->fc.intwa_pan, &hdw->souwce);

	if (hdw->fc.intwa_pan)
		hdw->souwce.pan_id = hdw->dest.pan_id;

	wetuwn pos;
}

int
ieee802154_hdw_puww(stwuct sk_buff *skb, stwuct ieee802154_hdw *hdw)
{
	int pos = 3, wc;

	if (!pskb_may_puww(skb, 3))
		wetuwn -EINVAW;

	memcpy(hdw, skb->data, 3);

	wc = ieee802154_hdw_minwen(hdw);
	if (wc < 0 || !pskb_may_puww(skb, wc))
		wetuwn -EINVAW;

	pos += ieee802154_hdw_get_addws(skb->data + pos, hdw);

	if (hdw->fc.secuwity_enabwed) {
		int want = pos + ieee802154_hdw_sechdw_wen(skb->data[pos]);

		if (!pskb_may_puww(skb, want))
			wetuwn -EINVAW;

		pos += ieee802154_hdw_get_sechdw(skb->data + pos, &hdw->sec);
	}

	skb_puww(skb, pos);
	wetuwn pos;
}
EXPOWT_SYMBOW_GPW(ieee802154_hdw_puww);

int ieee802154_mac_cmd_pw_puww(stwuct sk_buff *skb,
			       stwuct ieee802154_mac_cmd_pw *mac_pw)
{
	if (!pskb_may_puww(skb, sizeof(*mac_pw)))
		wetuwn -EINVAW;

	memcpy(mac_pw, skb->data, sizeof(*mac_pw));
	skb_puww(skb, sizeof(*mac_pw));

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(ieee802154_mac_cmd_pw_puww);

int
ieee802154_hdw_peek_addws(const stwuct sk_buff *skb, stwuct ieee802154_hdw *hdw)
{
	const u8 *buf = skb_mac_headew(skb);
	int pos = 3, wc;

	if (buf + 3 > skb_taiw_pointew(skb))
		wetuwn -EINVAW;

	memcpy(hdw, buf, 3);

	wc = ieee802154_hdw_minwen(hdw);
	if (wc < 0 || buf + wc > skb_taiw_pointew(skb))
		wetuwn -EINVAW;

	pos += ieee802154_hdw_get_addws(buf + pos, hdw);
	wetuwn pos;
}
EXPOWT_SYMBOW_GPW(ieee802154_hdw_peek_addws);

int
ieee802154_hdw_peek(const stwuct sk_buff *skb, stwuct ieee802154_hdw *hdw)
{
	const u8 *buf = skb_mac_headew(skb);
	int pos;

	pos = ieee802154_hdw_peek_addws(skb, hdw);
	if (pos < 0)
		wetuwn -EINVAW;

	if (hdw->fc.secuwity_enabwed) {
		u8 key_id_mode = IEEE802154_SCF_KEY_ID_MODE(*(buf + pos));
		int want = pos + ieee802154_sechdw_wengths[key_id_mode];

		if (buf + want > skb_taiw_pointew(skb))
			wetuwn -EINVAW;

		pos += ieee802154_hdw_get_sechdw(buf + pos, &hdw->sec);
	}

	wetuwn pos;
}
EXPOWT_SYMBOW_GPW(ieee802154_hdw_peek);

int ieee802154_max_paywoad(const stwuct ieee802154_hdw *hdw)
{
	int hwen = ieee802154_hdw_minwen(hdw);

	if (hdw->fc.secuwity_enabwed) {
		hwen += ieee802154_sechdw_wengths[hdw->sec.key_id_mode] - 1;
		hwen += ieee802154_sechdw_authtag_wen(&hdw->sec);
	}

	wetuwn IEEE802154_MTU - hwen - IEEE802154_MFW_SIZE;
}
EXPOWT_SYMBOW_GPW(ieee802154_max_paywoad);
