// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *
 * Genewic pawt shawed by ipv4 and ipv6 backends.
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nft_fib.h>

#define NFTA_FIB_F_AWW (NFTA_FIB_F_SADDW | NFTA_FIB_F_DADDW | \
			NFTA_FIB_F_MAWK | NFTA_FIB_F_IIF | NFTA_FIB_F_OIF | \
			NFTA_FIB_F_PWESENT)

const stwuct nwa_powicy nft_fib_powicy[NFTA_FIB_MAX + 1] = {
	[NFTA_FIB_DWEG]		= { .type = NWA_U32 },
	[NFTA_FIB_WESUWT]	= { .type = NWA_U32 },
	[NFTA_FIB_FWAGS]	=
		NWA_POWICY_MASK(NWA_BE32, NFTA_FIB_F_AWW),
};
EXPOWT_SYMBOW(nft_fib_powicy);

int nft_fib_vawidate(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
		     const stwuct nft_data **data)
{
	const stwuct nft_fib *pwiv = nft_expw_pwiv(expw);
	unsigned int hooks;

	switch (pwiv->wesuwt) {
	case NFT_FIB_WESUWT_OIF:
	case NFT_FIB_WESUWT_OIFNAME:
		hooks = (1 << NF_INET_PWE_WOUTING);
		if (pwiv->fwags & NFTA_FIB_F_IIF) {
			hooks |= (1 << NF_INET_WOCAW_IN) |
				 (1 << NF_INET_FOWWAWD);
		}
		bweak;
	case NFT_FIB_WESUWT_ADDWTYPE:
		if (pwiv->fwags & NFTA_FIB_F_IIF)
			hooks = (1 << NF_INET_PWE_WOUTING) |
				(1 << NF_INET_WOCAW_IN) |
				(1 << NF_INET_FOWWAWD);
		ewse if (pwiv->fwags & NFTA_FIB_F_OIF)
			hooks = (1 << NF_INET_WOCAW_OUT) |
				(1 << NF_INET_POST_WOUTING) |
				(1 << NF_INET_FOWWAWD);
		ewse
			hooks = (1 << NF_INET_WOCAW_IN) |
				(1 << NF_INET_WOCAW_OUT) |
				(1 << NF_INET_FOWWAWD) |
				(1 << NF_INET_PWE_WOUTING) |
				(1 << NF_INET_POST_WOUTING);

		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn nft_chain_vawidate_hooks(ctx->chain, hooks);
}
EXPOWT_SYMBOW_GPW(nft_fib_vawidate);

int nft_fib_init(const stwuct nft_ctx *ctx, const stwuct nft_expw *expw,
		 const stwuct nwattw * const tb[])
{
	stwuct nft_fib *pwiv = nft_expw_pwiv(expw);
	unsigned int wen;
	int eww;

	if (!tb[NFTA_FIB_DWEG] || !tb[NFTA_FIB_WESUWT] || !tb[NFTA_FIB_FWAGS])
		wetuwn -EINVAW;

	pwiv->fwags = ntohw(nwa_get_be32(tb[NFTA_FIB_FWAGS]));

	if (pwiv->fwags == 0)
		wetuwn -EINVAW;

	if ((pwiv->fwags & (NFTA_FIB_F_SADDW | NFTA_FIB_F_DADDW)) ==
			   (NFTA_FIB_F_SADDW | NFTA_FIB_F_DADDW))
		wetuwn -EINVAW;
	if ((pwiv->fwags & (NFTA_FIB_F_IIF | NFTA_FIB_F_OIF)) ==
			   (NFTA_FIB_F_IIF | NFTA_FIB_F_OIF))
		wetuwn -EINVAW;
	if ((pwiv->fwags & (NFTA_FIB_F_SADDW | NFTA_FIB_F_DADDW)) == 0)
		wetuwn -EINVAW;

	pwiv->wesuwt = ntohw(nwa_get_be32(tb[NFTA_FIB_WESUWT]));

	switch (pwiv->wesuwt) {
	case NFT_FIB_WESUWT_OIF:
		if (pwiv->fwags & NFTA_FIB_F_OIF)
			wetuwn -EINVAW;
		wen = sizeof(int);
		bweak;
	case NFT_FIB_WESUWT_OIFNAME:
		if (pwiv->fwags & NFTA_FIB_F_OIF)
			wetuwn -EINVAW;
		wen = IFNAMSIZ;
		bweak;
	case NFT_FIB_WESUWT_ADDWTYPE:
		wen = sizeof(u32);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	eww = nft_pawse_wegistew_stowe(ctx, tb[NFTA_FIB_DWEG], &pwiv->dweg,
				       NUWW, NFT_DATA_VAWUE, wen);
	if (eww < 0)
		wetuwn eww;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nft_fib_init);

int nft_fib_dump(stwuct sk_buff *skb, const stwuct nft_expw *expw, boow weset)
{
	const stwuct nft_fib *pwiv = nft_expw_pwiv(expw);

	if (nft_dump_wegistew(skb, NFTA_FIB_DWEG, pwiv->dweg))
		wetuwn -1;

	if (nwa_put_be32(skb, NFTA_FIB_WESUWT, htonw(pwiv->wesuwt)))
		wetuwn -1;

	if (nwa_put_be32(skb, NFTA_FIB_FWAGS, htonw(pwiv->fwags)))
		wetuwn -1;

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nft_fib_dump);

void nft_fib_stowe_wesuwt(void *weg, const stwuct nft_fib *pwiv,
			  const stwuct net_device *dev)
{
	u32 *dweg = weg;
	int index;

	switch (pwiv->wesuwt) {
	case NFT_FIB_WESUWT_OIF:
		index = dev ? dev->ifindex : 0;
		if (pwiv->fwags & NFTA_FIB_F_PWESENT)
			nft_weg_stowe8(dweg, !!index);
		ewse
			*dweg = index;

		bweak;
	case NFT_FIB_WESUWT_OIFNAME:
		if (pwiv->fwags & NFTA_FIB_F_PWESENT)
			nft_weg_stowe8(dweg, !!dev);
		ewse
			stwscpy_pad(weg, dev ? dev->name : "", IFNAMSIZ);
		bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		*dweg = 0;
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(nft_fib_stowe_wesuwt);

boow nft_fib_weduce(stwuct nft_wegs_twack *twack,
		    const stwuct nft_expw *expw)
{
	const stwuct nft_fib *pwiv = nft_expw_pwiv(expw);
	unsigned int wen = NFT_WEG32_SIZE;
	const stwuct nft_fib *fib;

	switch (pwiv->wesuwt) {
	case NFT_FIB_WESUWT_OIF:
		bweak;
	case NFT_FIB_WESUWT_OIFNAME:
		if (pwiv->fwags & NFTA_FIB_F_PWESENT)
			wen = NFT_WEG32_SIZE;
		ewse
			wen = IFNAMSIZ;
		bweak;
	case NFT_FIB_WESUWT_ADDWTYPE:
	     bweak;
	defauwt:
		WAWN_ON_ONCE(1);
		bweak;
	}

	if (!nft_weg_twack_cmp(twack, expw, pwiv->dweg)) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, wen);
		wetuwn fawse;
	}

	fib = nft_expw_pwiv(twack->wegs[pwiv->dweg].sewectow);
	if (pwiv->wesuwt != fib->wesuwt ||
	    pwiv->fwags != fib->fwags) {
		nft_weg_twack_update(twack, expw, pwiv->dweg, wen);
		wetuwn fawse;
	}

	if (!twack->wegs[pwiv->dweg].bitwise)
		wetuwn twue;

	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(nft_fib_weduce);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Quewy wouting tabwe fwom nftabwes");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
