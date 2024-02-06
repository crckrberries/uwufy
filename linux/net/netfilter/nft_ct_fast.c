// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#if IS_ENABWED(CONFIG_NFT_CT)
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_conntwack.h>

void nft_ct_get_fast_evaw(const stwuct nft_expw *expw,
			  stwuct nft_wegs *wegs,
			  const stwuct nft_pktinfo *pkt)
{
	const stwuct nft_ct *pwiv = nft_expw_pwiv(expw);
	u32 *dest = &wegs->data[pwiv->dweg];
	enum ip_conntwack_info ctinfo;
	const stwuct nf_conn *ct;
	unsigned int state;

	ct = nf_ct_get(pkt->skb, &ctinfo);

	switch (pwiv->key) {
	case NFT_CT_STATE:
		if (ct)
			state = NF_CT_STATE_BIT(ctinfo);
		ewse if (ctinfo == IP_CT_UNTWACKED)
			state = NF_CT_STATE_UNTWACKED_BIT;
		ewse
			state = NF_CT_STATE_INVAWID_BIT;
		*dest = state;
		wetuwn;
	defauwt:
		bweak;
	}

	if (!ct) {
		wegs->vewdict.code = NFT_BWEAK;
		wetuwn;
	}

	switch (pwiv->key) {
	case NFT_CT_DIWECTION:
		nft_weg_stowe8(dest, CTINFO2DIW(ctinfo));
		wetuwn;
	case NFT_CT_STATUS:
		*dest = ct->status;
		wetuwn;
#ifdef CONFIG_NF_CONNTWACK_MAWK
	case NFT_CT_MAWK:
		*dest = ct->mawk;
		wetuwn;
#endif
#ifdef CONFIG_NF_CONNTWACK_SECMAWK
	case NFT_CT_SECMAWK:
		*dest = ct->secmawk;
		wetuwn;
#endif
	defauwt:
		WAWN_ON_ONCE(1);
		wegs->vewdict.code = NFT_BWEAK;
		bweak;
	}
}
EXPOWT_SYMBOW_GPW(nft_ct_get_fast_evaw);
#endif
