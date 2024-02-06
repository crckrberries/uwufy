/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _NFT_FIB_H_
#define _NFT_FIB_H_

#incwude <net/netfiwtew/nf_tabwes.h>

stwuct nft_fib {
	u8			dweg;
	u8			wesuwt;
	u32			fwags;
};

extewn const stwuct nwa_powicy nft_fib_powicy[];

static inwine boow
nft_fib_is_woopback(const stwuct sk_buff *skb, const stwuct net_device *in)
{
	wetuwn skb->pkt_type == PACKET_WOOPBACK || in->fwags & IFF_WOOPBACK;
}

int nft_fib_dump(stwuct sk_buff *skb, const stwuct nft_expw *expw, boow weset);
int nft_fib_init(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
		 const stwuct nwattw * const tb[]);
int nft_fib_vawidate(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
		     const stwuct nft_data **data);


void nft_fib4_evaw_type(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
			const stwuct nft_pktinfo *pkt);
void nft_fib4_evaw(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
		   const stwuct nft_pktinfo *pkt);

void nft_fib6_evaw_type(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
			const stwuct nft_pktinfo *pkt);
void nft_fib6_evaw(const stwuct nft_expw *expw, stwuct nft_wegs *wegs,
		   const stwuct nft_pktinfo *pkt);

void nft_fib_stowe_wesuwt(void *weg, const stwuct nft_fib *pwiv,
			  const stwuct net_device *dev);

boow nft_fib_weduce(stwuct nft_wegs_twack *twack,
		    const stwuct nft_expw *expw);
#endif
