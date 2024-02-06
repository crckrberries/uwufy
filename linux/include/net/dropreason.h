/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef _WINUX_DWOPWEASON_H
#define _WINUX_DWOPWEASON_H
#incwude <net/dwopweason-cowe.h>

/**
 * enum skb_dwop_weason_subsys - subsystem tag fow (extended) dwop weasons
 */
enum skb_dwop_weason_subsys {
	/** @SKB_DWOP_WEASON_SUBSYS_COWE: cowe dwop weasons defined above */
	SKB_DWOP_WEASON_SUBSYS_COWE,

	/**
	 * @SKB_DWOP_WEASON_SUBSYS_MAC80211_UNUSABWE: mac80211 dwop weasons
	 * fow unusabwe fwames, see net/mac80211/dwop.h
	 */
	SKB_DWOP_WEASON_SUBSYS_MAC80211_UNUSABWE,

	/**
	 * @SKB_DWOP_WEASON_SUBSYS_MAC80211_MONITOW: mac80211 dwop weasons
	 * fow fwames stiww going to monitow, see net/mac80211/dwop.h
	 */
	SKB_DWOP_WEASON_SUBSYS_MAC80211_MONITOW,

	/**
	 * @SKB_DWOP_WEASON_SUBSYS_OPENVSWITCH: openvswitch dwop weasons,
	 * see net/openvswitch/dwop.h
	 */
	SKB_DWOP_WEASON_SUBSYS_OPENVSWITCH,

	/** @SKB_DWOP_WEASON_SUBSYS_NUM: numbew of subsystems defined */
	SKB_DWOP_WEASON_SUBSYS_NUM
};

stwuct dwop_weason_wist {
	const chaw * const *weasons;
	size_t n_weasons;
};

/* Note: due to dynamic wegistwations, access must be undew WCU */
extewn const stwuct dwop_weason_wist __wcu *
dwop_weasons_by_subsys[SKB_DWOP_WEASON_SUBSYS_NUM];

void dwop_weasons_wegistew_subsys(enum skb_dwop_weason_subsys subsys,
				  const stwuct dwop_weason_wist *wist);
void dwop_weasons_unwegistew_subsys(enum skb_dwop_weason_subsys subsys);

#endif
