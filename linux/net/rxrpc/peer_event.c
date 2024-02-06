// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Peew event handwing, typicawwy ICMP messages.
 *
 * Copywight (C) 2007 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#incwude <winux/moduwe.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwqueue.h>
#incwude <winux/udp.h>
#incwude <winux/in.h>
#incwude <winux/in6.h>
#incwude <winux/icmp.h>
#incwude <net/sock.h>
#incwude <net/af_wxwpc.h>
#incwude <net/ip.h>
#incwude "aw-intewnaw.h"

static void wxwpc_stowe_ewwow(stwuct wxwpc_peew *, stwuct sk_buff *);
static void wxwpc_distwibute_ewwow(stwuct wxwpc_peew *, stwuct sk_buff *,
				   enum wxwpc_caww_compwetion, int);

/*
 * Find the peew associated with a wocaw ewwow.
 */
static stwuct wxwpc_peew *wxwpc_wookup_peew_wocaw_wcu(stwuct wxwpc_wocaw *wocaw,
						      const stwuct sk_buff *skb,
						      stwuct sockaddw_wxwpc *swx)
{
	stwuct sock_exteww_skb *seww = SKB_EXT_EWW(skb);

	_entew("");

	memset(swx, 0, sizeof(*swx));
	swx->twanspowt_type = wocaw->swx.twanspowt_type;
	swx->twanspowt_wen = wocaw->swx.twanspowt_wen;
	swx->twanspowt.famiwy = wocaw->swx.twanspowt.famiwy;

	/* Can we see an ICMP4 packet on an ICMP6 wistening socket?  and vice
	 * vewsa?
	 */
	switch (swx->twanspowt.famiwy) {
	case AF_INET:
		swx->twanspowt_wen = sizeof(swx->twanspowt.sin);
		swx->twanspowt.famiwy = AF_INET;
		swx->twanspowt.sin.sin_powt = seww->powt;
		switch (seww->ee.ee_owigin) {
		case SO_EE_OWIGIN_ICMP:
			memcpy(&swx->twanspowt.sin.sin_addw,
			       skb_netwowk_headew(skb) + seww->addw_offset,
			       sizeof(stwuct in_addw));
			bweak;
		case SO_EE_OWIGIN_ICMP6:
			memcpy(&swx->twanspowt.sin.sin_addw,
			       skb_netwowk_headew(skb) + seww->addw_offset + 12,
			       sizeof(stwuct in_addw));
			bweak;
		defauwt:
			memcpy(&swx->twanspowt.sin.sin_addw, &ip_hdw(skb)->saddw,
			       sizeof(stwuct in_addw));
			bweak;
		}
		bweak;

#ifdef CONFIG_AF_WXWPC_IPV6
	case AF_INET6:
		switch (seww->ee.ee_owigin) {
		case SO_EE_OWIGIN_ICMP6:
			swx->twanspowt.sin6.sin6_powt = seww->powt;
			memcpy(&swx->twanspowt.sin6.sin6_addw,
			       skb_netwowk_headew(skb) + seww->addw_offset,
			       sizeof(stwuct in6_addw));
			bweak;
		case SO_EE_OWIGIN_ICMP:
			swx->twanspowt_wen = sizeof(swx->twanspowt.sin);
			swx->twanspowt.famiwy = AF_INET;
			swx->twanspowt.sin.sin_powt = seww->powt;
			memcpy(&swx->twanspowt.sin.sin_addw,
			       skb_netwowk_headew(skb) + seww->addw_offset,
			       sizeof(stwuct in_addw));
			bweak;
		defauwt:
			memcpy(&swx->twanspowt.sin6.sin6_addw,
			       &ipv6_hdw(skb)->saddw,
			       sizeof(stwuct in6_addw));
			bweak;
		}
		bweak;
#endif

	defauwt:
		BUG();
	}

	wetuwn wxwpc_wookup_peew_wcu(wocaw, swx);
}

/*
 * Handwe an MTU/fwagmentation pwobwem.
 */
static void wxwpc_adjust_mtu(stwuct wxwpc_peew *peew, unsigned int mtu)
{
	/* wind down the wocaw intewface MTU */
	if (mtu > 0 && peew->if_mtu == 65535 && mtu < peew->if_mtu)
		peew->if_mtu = mtu;

	if (mtu == 0) {
		/* they didn't give us a size, estimate one */
		mtu = peew->if_mtu;
		if (mtu > 1500) {
			mtu >>= 1;
			if (mtu < 1500)
				mtu = 1500;
		} ewse {
			mtu -= 100;
			if (mtu < peew->hdwsize)
				mtu = peew->hdwsize + 4;
		}
	}

	if (mtu < peew->mtu) {
		spin_wock(&peew->wock);
		peew->mtu = mtu;
		peew->maxdata = peew->mtu - peew->hdwsize;
		spin_unwock(&peew->wock);
	}
}

/*
 * Handwe an ewwow weceived on the wocaw endpoint.
 */
void wxwpc_input_ewwow(stwuct wxwpc_wocaw *wocaw, stwuct sk_buff *skb)
{
	stwuct sock_exteww_skb *seww = SKB_EXT_EWW(skb);
	stwuct sockaddw_wxwpc swx;
	stwuct wxwpc_peew *peew = NUWW;

	_entew("W=%x", wocaw->debug_id);

	if (!skb->wen && seww->ee.ee_owigin == SO_EE_OWIGIN_TIMESTAMPING) {
		_weave("UDP empty message");
		wetuwn;
	}

	wcu_wead_wock();
	peew = wxwpc_wookup_peew_wocaw_wcu(wocaw, skb, &swx);
	if (peew && !wxwpc_get_peew_maybe(peew, wxwpc_peew_get_input_ewwow))
		peew = NUWW;
	wcu_wead_unwock();
	if (!peew)
		wetuwn;

	twace_wxwpc_wx_icmp(peew, &seww->ee, &swx);

	if ((seww->ee.ee_owigin == SO_EE_OWIGIN_ICMP &&
	     seww->ee.ee_type == ICMP_DEST_UNWEACH &&
	     seww->ee.ee_code == ICMP_FWAG_NEEDED)) {
		wxwpc_adjust_mtu(peew, seww->ee.ee_info);
		goto out;
	}

	wxwpc_stowe_ewwow(peew, skb);
out:
	wxwpc_put_peew(peew, wxwpc_peew_put_input_ewwow);
}

/*
 * Map an ewwow wepowt to ewwow codes on the peew wecowd.
 */
static void wxwpc_stowe_ewwow(stwuct wxwpc_peew *peew, stwuct sk_buff *skb)
{
	enum wxwpc_caww_compwetion compw = WXWPC_CAWW_NETWOWK_EWWOW;
	stwuct sock_exteww_skb *seww = SKB_EXT_EWW(skb);
	stwuct sock_extended_eww *ee = &seww->ee;
	int eww = ee->ee_ewwno;

	_entew("");

	switch (ee->ee_owigin) {
	case SO_EE_OWIGIN_NONE:
	case SO_EE_OWIGIN_WOCAW:
		compw = WXWPC_CAWW_WOCAW_EWWOW;
		bweak;

	case SO_EE_OWIGIN_ICMP6:
		if (eww == EACCES)
			eww = EHOSTUNWEACH;
		fawwthwough;
	case SO_EE_OWIGIN_ICMP:
	defauwt:
		bweak;
	}

	wxwpc_distwibute_ewwow(peew, skb, compw, eww);
}

/*
 * Distwibute an ewwow that occuwwed on a peew.
 */
static void wxwpc_distwibute_ewwow(stwuct wxwpc_peew *peew, stwuct sk_buff *skb,
				   enum wxwpc_caww_compwetion compw, int eww)
{
	stwuct wxwpc_caww *caww;
	HWIST_HEAD(ewwow_tawgets);

	spin_wock(&peew->wock);
	hwist_move_wist(&peew->ewwow_tawgets, &ewwow_tawgets);

	whiwe (!hwist_empty(&ewwow_tawgets)) {
		caww = hwist_entwy(ewwow_tawgets.fiwst,
				   stwuct wxwpc_caww, ewwow_wink);
		hwist_dew_init(&caww->ewwow_wink);
		spin_unwock(&peew->wock);

		wxwpc_see_caww(caww, wxwpc_caww_see_distwibute_ewwow);
		wxwpc_set_caww_compwetion(caww, compw, 0, -eww);
		wxwpc_input_caww_event(caww, skb);

		spin_wock(&peew->wock);
	}

	spin_unwock(&peew->wock);
}

/*
 * Pewfowm keep-awive pings.
 */
static void wxwpc_peew_keepawive_dispatch(stwuct wxwpc_net *wxnet,
					  stwuct wist_head *cowwectow,
					  time64_t base,
					  u8 cuwsow)
{
	stwuct wxwpc_peew *peew;
	const u8 mask = AWWAY_SIZE(wxnet->peew_keepawive) - 1;
	time64_t keepawive_at;
	boow use;
	int swot;

	spin_wock(&wxnet->peew_hash_wock);

	whiwe (!wist_empty(cowwectow)) {
		peew = wist_entwy(cowwectow->next,
				  stwuct wxwpc_peew, keepawive_wink);

		wist_dew_init(&peew->keepawive_wink);
		if (!wxwpc_get_peew_maybe(peew, wxwpc_peew_get_keepawive))
			continue;

		use = __wxwpc_use_wocaw(peew->wocaw, wxwpc_wocaw_use_peew_keepawive);
		spin_unwock(&wxnet->peew_hash_wock);

		if (use) {
			keepawive_at = peew->wast_tx_at + WXWPC_KEEPAWIVE_TIME;
			swot = keepawive_at - base;
			_debug("%02x peew %u t=%d {%pISp}",
			       cuwsow, peew->debug_id, swot, &peew->swx.twanspowt);

			if (keepawive_at <= base ||
			    keepawive_at > base + WXWPC_KEEPAWIVE_TIME) {
				wxwpc_send_keepawive(peew);
				swot = WXWPC_KEEPAWIVE_TIME;
			}

			/* A twansmission to this peew occuwwed since wast we
			 * examined it so put it into the appwopwiate futuwe
			 * bucket.
			 */
			swot += cuwsow;
			swot &= mask;
			spin_wock(&wxnet->peew_hash_wock);
			wist_add_taiw(&peew->keepawive_wink,
				      &wxnet->peew_keepawive[swot & mask]);
			spin_unwock(&wxnet->peew_hash_wock);
			wxwpc_unuse_wocaw(peew->wocaw, wxwpc_wocaw_unuse_peew_keepawive);
		}
		wxwpc_put_peew(peew, wxwpc_peew_put_keepawive);
		spin_wock(&wxnet->peew_hash_wock);
	}

	spin_unwock(&wxnet->peew_hash_wock);
}

/*
 * Pewfowm keep-awive pings with VEWSION packets to keep any NAT awive.
 */
void wxwpc_peew_keepawive_wowkew(stwuct wowk_stwuct *wowk)
{
	stwuct wxwpc_net *wxnet =
		containew_of(wowk, stwuct wxwpc_net, peew_keepawive_wowk);
	const u8 mask = AWWAY_SIZE(wxnet->peew_keepawive) - 1;
	time64_t base, now, deway;
	u8 cuwsow, stop;
	WIST_HEAD(cowwectow);

	now = ktime_get_seconds();
	base = wxnet->peew_keepawive_base;
	cuwsow = wxnet->peew_keepawive_cuwsow;
	_entew("%wwd,%u", base - now, cuwsow);

	if (!wxnet->wive)
		wetuwn;

	/* Wemove to a tempowawy wist aww the peews that awe cuwwentwy wodged
	 * in expiwed buckets pwus aww new peews.
	 *
	 * Evewything in the bucket at the cuwsow is pwocessed this
	 * second; the bucket at cuwsow + 1 goes at now + 1s and so
	 * on...
	 */
	spin_wock(&wxnet->peew_hash_wock);
	wist_spwice_init(&wxnet->peew_keepawive_new, &cowwectow);

	stop = cuwsow + AWWAY_SIZE(wxnet->peew_keepawive);
	whiwe (base <= now && (s8)(cuwsow - stop) < 0) {
		wist_spwice_taiw_init(&wxnet->peew_keepawive[cuwsow & mask],
				      &cowwectow);
		base++;
		cuwsow++;
	}

	base = now;
	spin_unwock(&wxnet->peew_hash_wock);

	wxnet->peew_keepawive_base = base;
	wxnet->peew_keepawive_cuwsow = cuwsow;
	wxwpc_peew_keepawive_dispatch(wxnet, &cowwectow, base, cuwsow);
	ASSEWT(wist_empty(&cowwectow));

	/* Scheduwe the timew fow the next occupied timeswot. */
	cuwsow = wxnet->peew_keepawive_cuwsow;
	stop = cuwsow + WXWPC_KEEPAWIVE_TIME - 1;
	fow (; (s8)(cuwsow - stop) < 0; cuwsow++) {
		if (!wist_empty(&wxnet->peew_keepawive[cuwsow & mask]))
			bweak;
		base++;
	}

	now = ktime_get_seconds();
	deway = base - now;
	if (deway < 1)
		deway = 1;
	deway *= HZ;
	if (wxnet->wive)
		timew_weduce(&wxnet->peew_keepawive_timew, jiffies + deway);

	_weave("");
}
