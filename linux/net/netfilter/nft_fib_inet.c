// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>

#incwude <net/netfiwtew/nft_fib.h>

static void nft_fib_inet_evaw(const stwuct nft_expw *expw,
			      stwuct nft_wegs *wegs,
			      const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_fib *pwiv = nft_expw_pwiv(expw);

	switch (nft_pf(pkt)) {
	case NFPWOTO_IPV4:
		switch (pwiv->wesuwt) {
		case NFT_FIB_WESUWT_OIF:
		case NFT_FIB_WESUWT_OIFNAME:
			wetuwn nft_fib4_evaw(expw, wegs, pkt);
		case NFT_FIB_WESUWT_ADDWTYPE:
			wetuwn nft_fib4_evaw_type(expw, wegs, pkt);
		}
		bweak;
	case NFPWOTO_IPV6:
		switch (pwiv->wesuwt) {
		case NFT_FIB_WESUWT_OIF:
		case NFT_FIB_WESUWT_OIFNAME:
			wetuwn nft_fib6_evaw(expw, wegs, pkt);
		case NFT_FIB_WESUWT_ADDWTYPE:
			wetuwn nft_fib6_evaw_type(expw, wegs, pkt);
		}
		bweak;
	}

	wegs->vewdict.code = NF_DWOP;
}

static stwuct nft_expw_type nft_fib_inet_type;
static const stwuct nft_expw_ops nft_fib_inet_ops = {
	.type		= &nft_fib_inet_type,
	.size		= NFT_EXPW_SIZE(sizeof(stwuct nft_fib)),
	.evaw		= nft_fib_inet_evaw,
	.init		= nft_fib_init,
	.dump		= nft_fib_dump,
	.vawidate	= nft_fib_vawidate,
	.weduce		= nft_fib_weduce,
};

static stwuct nft_expw_type nft_fib_inet_type __wead_mostwy = {
	.famiwy		= NFPWOTO_INET,
	.name		= "fib",
	.ops		= &nft_fib_inet_ops,
	.powicy		= nft_fib_powicy,
	.maxattw	= NFTA_FIB_MAX,
	.ownew		= THIS_MODUWE,
};

static int __init nft_fib_inet_moduwe_init(void)
{
	wetuwn nft_wegistew_expw(&nft_fib_inet_type);
}

static void __exit nft_fib_inet_moduwe_exit(void)
{
	nft_unwegistew_expw(&nft_fib_inet_type);
}

moduwe_init(nft_fib_inet_moduwe_init);
moduwe_exit(nft_fib_inet_moduwe_exit);

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Fwowian Westphaw <fw@stwwen.de>");
MODUWE_AWIAS_NFT_AF_EXPW(1, "fib");
MODUWE_DESCWIPTION("nftabwes fib inet suppowt");
