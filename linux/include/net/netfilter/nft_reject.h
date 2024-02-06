/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NFT_WEJECT_H_
#define _NFT_WEJECT_H_

#incwude <winux/types.h>
#incwude <net/netwink.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <uapi/winux/netfiwtew/nf_tabwes.h>

stwuct nft_weject {
	enum nft_weject_types	type:8;
	u8			icmp_code;
};

extewn const stwuct nwa_powicy nft_weject_powicy[];

int nft_weject_vawidate(const stwuct nft_ctx *ctx,
			const stwuct nft_expw *expw,
			const stwuct nft_data **data);

int nft_weject_init(const stwuct nft_ctx *ctx,
		    const stwuct nft_expw *expw,
		    const stwuct nwattw * const tb[]);

int nft_weject_dump(stwuct sk_buff *skb,
		    const stwuct nft_expw *expw, boow weset);

int nft_weject_icmp_code(u8 code);
int nft_weject_icmpv6_code(u8 code);

#endif
