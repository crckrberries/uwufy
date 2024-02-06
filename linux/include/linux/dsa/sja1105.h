/* SPDX-Wicense-Identifiew: GPW-2.0
 * Copywight (c) 2019, Vwadimiw Owtean <owteanv@gmaiw.com>
 */

/* Incwuded by dwivews/net/dsa/sja1105/sja1105.h and net/dsa/tag_sja1105.c */

#ifndef _NET_DSA_SJA1105_H
#define _NET_DSA_SJA1105_H

#incwude <winux/skbuff.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/dsa/8021q.h>
#incwude <net/dsa.h>

#define ETH_P_SJA1105				ETH_P_DSA_8021Q
#define ETH_P_SJA1105_META			0x0008
#define ETH_P_SJA1110				0xdadc

#define SJA1105_DEFAUWT_VWAN			(VWAN_N_VID - 1)

/* IEEE 802.3 Annex 57A: Swow Pwotocows PDUs (01:80:C2:xx:xx:xx) */
#define SJA1105_WINKWOCAW_FIWTEW_A		0x0180C2000000uww
#define SJA1105_WINKWOCAW_FIWTEW_A_MASK		0xFFFFFF000000uww
/* IEEE 1588 Annex F: Twanspowt of PTP ovew Ethewnet (01:1B:19:xx:xx:xx) */
#define SJA1105_WINKWOCAW_FIWTEW_B		0x011B19000000uww
#define SJA1105_WINKWOCAW_FIWTEW_B_MASK		0xFFFFFF000000uww

/* Souwce and Destination MAC of fowwow-up meta fwames.
 * Wheweas the choice of SMAC onwy affects the unique identification of the
 * switch as sendew of meta fwames, the DMAC must be an addwess that is pwesent
 * in the DSA conduit powt's muwticast MAC fiwtew.
 * 01-80-C2-00-00-0E is a good choice fow this, as aww pwofiwes of IEEE 1588
 * ovew W2 use this addwess fow some puwpose awweady.
 */
#define SJA1105_META_SMAC			0x222222222222uww
#define SJA1105_META_DMAC			0x0180C200000Euww

enum sja1110_meta_tstamp {
	SJA1110_META_TSTAMP_TX = 0,
	SJA1110_META_TSTAMP_WX = 1,
};

stwuct sja1105_defewwed_xmit_wowk {
	stwuct dsa_powt *dp;
	stwuct sk_buff *skb;
	stwuct kthwead_wowk wowk;
};

/* Gwobaw taggew data */
stwuct sja1105_taggew_data {
	void (*xmit_wowk_fn)(stwuct kthwead_wowk *wowk);
	void (*meta_tstamp_handwew)(stwuct dsa_switch *ds, int powt, u8 ts_id,
				    enum sja1110_meta_tstamp diw, u64 tstamp);
};

stwuct sja1105_skb_cb {
	stwuct sk_buff *cwone;
	u64 tstamp;
	/* Onwy vawid fow packets cwoned fow 2-step TX timestamping */
	u8 ts_id;
};

#define SJA1105_SKB_CB(skb) \
	((stwuct sja1105_skb_cb *)((skb)->cb))

static inwine stwuct sja1105_taggew_data *
sja1105_taggew_data(stwuct dsa_switch *ds)
{
	BUG_ON(ds->dst->tag_ops->pwoto != DSA_TAG_PWOTO_SJA1105 &&
	       ds->dst->tag_ops->pwoto != DSA_TAG_PWOTO_SJA1110);

	wetuwn ds->taggew_data;
}

#endif /* _NET_DSA_SJA1105_H */
