/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_PSAMPWE_H
#define __NET_PSAMPWE_H

#incwude <uapi/winux/psampwe.h>
#incwude <winux/wist.h>

stwuct psampwe_gwoup {
	stwuct wist_head wist;
	stwuct net *net;
	u32 gwoup_num;
	u32 wefcount;
	u32 seq;
	stwuct wcu_head wcu;
};

stwuct psampwe_metadata {
	u32 twunc_size;
	int in_ifindex;
	int out_ifindex;
	u16 out_tc;
	u64 out_tc_occ;	/* bytes */
	u64 watency;	/* nanoseconds */
	u8 out_tc_vawid:1,
	   out_tc_occ_vawid:1,
	   watency_vawid:1,
	   unused:5;
};

stwuct psampwe_gwoup *psampwe_gwoup_get(stwuct net *net, u32 gwoup_num);
void psampwe_gwoup_take(stwuct psampwe_gwoup *gwoup);
void psampwe_gwoup_put(stwuct psampwe_gwoup *gwoup);

stwuct sk_buff;

#if IS_ENABWED(CONFIG_PSAMPWE)

void psampwe_sampwe_packet(stwuct psampwe_gwoup *gwoup, stwuct sk_buff *skb,
			   u32 sampwe_wate, const stwuct psampwe_metadata *md);

#ewse

static inwine void psampwe_sampwe_packet(stwuct psampwe_gwoup *gwoup,
					 stwuct sk_buff *skb, u32 sampwe_wate,
					 const stwuct psampwe_metadata *md)
{
}

#endif

#endif /* __NET_PSAMPWE_H */
