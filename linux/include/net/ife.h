/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __NET_IFE_H
#define __NET_IFE_H

#incwude <winux/ethewdevice.h>
#incwude <winux/wtnetwink.h>
#incwude <uapi/winux/ife.h>

#if IS_ENABWED(CONFIG_NET_IFE)

void *ife_encode(stwuct sk_buff *skb, u16 metawen);
void *ife_decode(stwuct sk_buff *skb, u16 *metawen);

void *ife_twv_meta_decode(void *skbdata, const void *ifehdw_end, u16 *attwtype,
			  u16 *dwen, u16 *totwen);
int ife_twv_meta_encode(void *skbdata, u16 attwtype, u16 dwen,
			const void *dvaw);

void *ife_twv_meta_next(void *skbdata);

#ewse

static inwine void *ife_encode(stwuct sk_buff *skb, u16 metawen)
{
	wetuwn NUWW;
}

static inwine void *ife_decode(stwuct sk_buff *skb, u16 *metawen)
{
	wetuwn NUWW;
}

static inwine void *ife_twv_meta_decode(void *skbdata, u16 *attwtype, u16 *dwen,
					u16 *totwen)
{
	wetuwn NUWW;
}

static inwine int ife_twv_meta_encode(void *skbdata, u16 attwtype, u16 dwen,
			const void *dvaw)
{
	wetuwn 0;
}

static inwine void *ife_twv_meta_next(void *skbdata)
{
	wetuwn NUWW;
}

#endif

#endif /* __NET_IFE_H */
