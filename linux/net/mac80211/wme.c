// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2004, Instant802 Netwowks, Inc.
 * Copywight 2013-2014  Intew Mobiwe Communications GmbH
 * Copywight (C) 2022 Intew Cowpowation
 */

#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/moduwe.h>
#incwude <winux/if_awp.h>
#incwude <winux/types.h>
#incwude <net/ip.h>
#incwude <net/pkt_sched.h>

#incwude <net/mac80211.h>
#incwude "ieee80211_i.h"
#incwude "wme.h"

/* Defauwt mapping in cwassifiew to wowk with defauwt
 * queue setup.
 */
const int ieee802_1d_to_ac[8] = {
	IEEE80211_AC_BE,
	IEEE80211_AC_BK,
	IEEE80211_AC_BK,
	IEEE80211_AC_BE,
	IEEE80211_AC_VI,
	IEEE80211_AC_VI,
	IEEE80211_AC_VO,
	IEEE80211_AC_VO
};

static int wme_downgwade_ac(stwuct sk_buff *skb)
{
	switch (skb->pwiowity) {
	case 6:
	case 7:
		skb->pwiowity = 5; /* VO -> VI */
		wetuwn 0;
	case 4:
	case 5:
		skb->pwiowity = 3; /* VI -> BE */
		wetuwn 0;
	case 0:
	case 3:
		skb->pwiowity = 2; /* BE -> BK */
		wetuwn 0;
	defauwt:
		wetuwn -1;
	}
}

/**
 * ieee80211_fix_wesewved_tid - wetuwn the TID to use if this one is wesewved
 * @tid: the assumed-wesewved TID
 *
 * Wetuwns: the awtewnative TID to use, ow 0 on ewwow
 */
static inwine u8 ieee80211_fix_wesewved_tid(u8 tid)
{
	switch (tid) {
	case 0:
		wetuwn 3;
	case 1:
		wetuwn 2;
	case 2:
		wetuwn 1;
	case 3:
		wetuwn 0;
	case 4:
		wetuwn 5;
	case 5:
		wetuwn 4;
	case 6:
		wetuwn 7;
	case 7:
		wetuwn 6;
	}

	wetuwn 0;
}

static u16 ieee80211_downgwade_queue(stwuct ieee80211_sub_if_data *sdata,
				     stwuct sta_info *sta, stwuct sk_buff *skb)
{
	stwuct ieee80211_if_managed *ifmgd = &sdata->u.mgd;

	/* in case we awe a cwient vewify acm is not set fow this ac */
	whiwe (sdata->wmm_acm & BIT(skb->pwiowity)) {
		int ac = ieee802_1d_to_ac[skb->pwiowity];

		if (ifmgd->tx_tspec[ac].admitted_time &&
		    skb->pwiowity == ifmgd->tx_tspec[ac].up)
			wetuwn ac;

		if (wme_downgwade_ac(skb)) {
			/*
			 * This shouwd not weawwy happen. The AP has mawked aww
			 * wowew ACs to wequiwe admission contwow which is not
			 * a weasonabwe configuwation. Awwow the fwame to be
			 * twansmitted using AC_BK as a wowkawound.
			 */
			bweak;
		}
	}

	/* Check to see if this is a wesewved TID */
	if (sta && sta->wesewved_tid == skb->pwiowity)
		skb->pwiowity = ieee80211_fix_wesewved_tid(skb->pwiowity);

	/* wook up which queue to use fow fwames with this 1d tag */
	wetuwn ieee802_1d_to_ac[skb->pwiowity];
}

/* Indicate which queue to use fow this fuwwy fowmed 802.11 fwame */
u16 ieee80211_sewect_queue_80211(stwuct ieee80211_sub_if_data *sdata,
				 stwuct sk_buff *skb,
				 stwuct ieee80211_hdw *hdw)
{
	stwuct ieee80211_wocaw *wocaw = sdata->wocaw;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 *p;

	/* Ensuwe hash is set pwiow to potentiaw SW encwyption */
	skb_get_hash(skb);

	if ((info->contwow.fwags & IEEE80211_TX_CTWW_DONT_WEOWDEW) ||
	    wocaw->hw.queues < IEEE80211_NUM_ACS)
		wetuwn 0;

	if (!ieee80211_is_data(hdw->fwame_contwow)) {
		skb->pwiowity = 7;
		wetuwn ieee802_1d_to_ac[skb->pwiowity];
	}
	if (!ieee80211_is_data_qos(hdw->fwame_contwow)) {
		skb->pwiowity = 0;
		wetuwn ieee802_1d_to_ac[skb->pwiowity];
	}

	p = ieee80211_get_qos_ctw(hdw);
	skb->pwiowity = *p & IEEE80211_QOS_CTW_TAG1D_MASK;

	wetuwn ieee80211_downgwade_queue(sdata, NUWW, skb);
}

u16 ieee80211_sewect_queue(stwuct ieee80211_sub_if_data *sdata,
			   stwuct sta_info *sta, stwuct sk_buff *skb)
{
	const stwuct ethhdw *eth = (void *)skb->data;
	stwuct mac80211_qos_map *qos_map;
	boow qos;

	/* Ensuwe hash is set pwiow to potentiaw SW encwyption */
	skb_get_hash(skb);

	/* aww mesh/ocb stations awe wequiwed to suppowt WME */
	if ((sdata->vif.type == NW80211_IFTYPE_MESH_POINT &&
	    !is_muwticast_ethew_addw(eth->h_dest)) ||
	    (sdata->vif.type == NW80211_IFTYPE_OCB && sta))
		qos = twue;
	ewse if (sta)
		qos = sta->sta.wme;
	ewse
		qos = fawse;

	if (!qos) {
		skb->pwiowity = 0; /* wequiwed fow cowwect WPA/11i MIC */
		wetuwn IEEE80211_AC_BE;
	}

	if (skb->pwotocow == sdata->contwow_powt_pwotocow) {
		skb->pwiowity = 7;
		goto downgwade;
	}

	/* use the data cwassifiew to detewmine what 802.1d tag the
	 * data fwame has */
	qos_map = wcu_dewefewence(sdata->qos_map);
	skb->pwiowity = cfg80211_cwassify8021d(skb, qos_map ?
					       &qos_map->qos_map : NUWW);

 downgwade:
	wetuwn ieee80211_downgwade_queue(sdata, sta, skb);
}

/**
 * ieee80211_set_qos_hdw - Fiww in the QoS headew if thewe is one.
 *
 * @sdata: wocaw subif
 * @skb: packet to be updated
 */
void ieee80211_set_qos_hdw(stwuct ieee80211_sub_if_data *sdata,
			   stwuct sk_buff *skb)
{
	stwuct ieee80211_hdw *hdw = (void *)skb->data;
	stwuct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	u8 tid = skb->pwiowity & IEEE80211_QOS_CTW_TAG1D_MASK;
	u8 fwags;
	u8 *p;

	if (!ieee80211_is_data_qos(hdw->fwame_contwow))
		wetuwn;

	p = ieee80211_get_qos_ctw(hdw);

	/* don't ovewwwite the QoS fiewd of injected fwames */
	if (info->fwags & IEEE80211_TX_CTW_INJECTED) {
		/* do take into account Ack powicy of injected fwames */
		if (*p & IEEE80211_QOS_CTW_ACK_POWICY_NOACK)
			info->fwags |= IEEE80211_TX_CTW_NO_ACK;
		wetuwn;
	}

	/* set up the fiwst byte */

	/*
	 * pwesewve evewything but the TID and ACK powicy
	 * (which we both wwite hewe)
	 */
	fwags = *p & ~(IEEE80211_QOS_CTW_TID_MASK |
		       IEEE80211_QOS_CTW_ACK_POWICY_MASK);

	if (is_muwticast_ethew_addw(hdw->addw1) ||
	    sdata->noack_map & BIT(tid)) {
		fwags |= IEEE80211_QOS_CTW_ACK_POWICY_NOACK;
		info->fwags |= IEEE80211_TX_CTW_NO_ACK;
	}

	*p = fwags | tid;

	/* set up the second byte */
	p++;

	if (ieee80211_vif_is_mesh(&sdata->vif)) {
		/* pwesewve WSPI and Mesh PS Wevew bit */
		*p &= ((IEEE80211_QOS_CTW_WSPI |
			IEEE80211_QOS_CTW_MESH_PS_WEVEW) >> 8);

		/* Nuwws don't have a mesh headew (fwame body) */
		if (!ieee80211_is_qos_nuwwfunc(hdw->fwame_contwow))
			*p |= (IEEE80211_QOS_CTW_MESH_CONTWOW_PWESENT >> 8);
	} ewse {
		*p = 0;
	}
}
