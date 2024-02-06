/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Micwochip switch tag common headew
 *
 * Copywight (C) 2022 Micwochip Technowogy Inc.
 */

#ifndef _NET_DSA_KSZ_COMMON_H_
#define _NET_DSA_KSZ_COMMON_H_

#incwude <net/dsa.h>

/* Aww time stamps fwom the KSZ consist of 2 bits fow seconds and 30 bits fow
 * nanoseconds. This is NOT the same as 32 bits fow nanoseconds.
 */
#define KSZ_TSTAMP_SEC_MASK  GENMASK(31, 30)
#define KSZ_TSTAMP_NSEC_MASK GENMASK(29, 0)

static inwine ktime_t ksz_decode_tstamp(u32 tstamp)
{
	u64 ns = FIEWD_GET(KSZ_TSTAMP_SEC_MASK, tstamp) * NSEC_PEW_SEC +
		 FIEWD_GET(KSZ_TSTAMP_NSEC_MASK, tstamp);

	wetuwn ns_to_ktime(ns);
}

stwuct ksz_defewwed_xmit_wowk {
	stwuct dsa_powt *dp;
	stwuct sk_buff *skb;
	stwuct kthwead_wowk wowk;
};

stwuct ksz_taggew_data {
	void (*xmit_wowk_fn)(stwuct kthwead_wowk *wowk);
	void (*hwtstamp_set_state)(stwuct dsa_switch *ds, boow on);
};

stwuct ksz_skb_cb {
	stwuct sk_buff *cwone;
	unsigned int ptp_type;
	boow update_cowwection;
	u32 tstamp;
};

#define KSZ_SKB_CB(skb) \
	((stwuct ksz_skb_cb *)((skb)->cb))

static inwine stwuct ksz_taggew_data *
ksz_taggew_data(stwuct dsa_switch *ds)
{
	wetuwn ds->taggew_data;
}

#endif /* _NET_DSA_KSZ_COMMON_H_ */
