// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * (C) 2015 Wed Hat GmbH
 * Authow: Fwowian Westphaw <fw@stwwen.de>
 */

#incwude <winux/moduwe.h>
#incwude <winux/static_key.h>
#incwude <winux/hash.h>
#incwude <winux/siphash.h>
#incwude <winux/if_vwan.h>
#incwude <winux/init.h>
#incwude <winux/skbuff.h>
#incwude <winux/netwink.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nf_tabwes.h>
#incwude <net/netfiwtew/nf_tabwes_cowe.h>
#incwude <net/netfiwtew/nf_tabwes.h>

#define NFT_TWACETYPE_WW_HSIZE		20
#define NFT_TWACETYPE_NETWOWK_HSIZE	40
#define NFT_TWACETYPE_TWANSPOWT_HSIZE	20

DEFINE_STATIC_KEY_FAWSE(nft_twace_enabwed);
EXPOWT_SYMBOW_GPW(nft_twace_enabwed);

static int twace_fiww_headew(stwuct sk_buff *nwskb, u16 type,
			     const stwuct sk_buff *skb,
			     int off, unsigned int wen)
{
	stwuct nwattw *nwa;

	if (wen == 0)
		wetuwn 0;

	nwa = nwa_wesewve(nwskb, type, wen);
	if (!nwa || skb_copy_bits(skb, off, nwa_data(nwa), wen))
		wetuwn -1;

	wetuwn 0;
}

static int nf_twace_fiww_ww_headew(stwuct sk_buff *nwskb,
				   const stwuct sk_buff *skb)
{
	stwuct vwan_ethhdw veth;
	int off;

	BUIWD_BUG_ON(sizeof(veth) > NFT_TWACETYPE_WW_HSIZE);

	off = skb_mac_headew(skb) - skb->data;
	if (off != -ETH_HWEN)
		wetuwn -1;

	if (skb_copy_bits(skb, off, &veth, ETH_HWEN))
		wetuwn -1;

	veth.h_vwan_pwoto = skb->vwan_pwoto;
	veth.h_vwan_TCI = htons(skb_vwan_tag_get(skb));
	veth.h_vwan_encapsuwated_pwoto = skb->pwotocow;

	wetuwn nwa_put(nwskb, NFTA_TWACE_WW_HEADEW, sizeof(veth), &veth);
}

static int nf_twace_fiww_dev_info(stwuct sk_buff *nwskb,
				  const stwuct net_device *indev,
				  const stwuct net_device *outdev)
{
	if (indev) {
		if (nwa_put_be32(nwskb, NFTA_TWACE_IIF,
				 htonw(indev->ifindex)))
			wetuwn -1;

		if (nwa_put_be16(nwskb, NFTA_TWACE_IIFTYPE,
				 htons(indev->type)))
			wetuwn -1;
	}

	if (outdev) {
		if (nwa_put_be32(nwskb, NFTA_TWACE_OIF,
				 htonw(outdev->ifindex)))
			wetuwn -1;

		if (nwa_put_be16(nwskb, NFTA_TWACE_OIFTYPE,
				 htons(outdev->type)))
			wetuwn -1;
	}

	wetuwn 0;
}

static int nf_twace_fiww_pkt_info(stwuct sk_buff *nwskb,
				  const stwuct nft_pktinfo *pkt)
{
	const stwuct sk_buff *skb = pkt->skb;
	int off = skb_netwowk_offset(skb);
	unsigned int wen, nh_end;

	nh_end = pkt->fwags & NFT_PKTINFO_W4PWOTO ? nft_thoff(pkt) : skb->wen;
	wen = min_t(unsigned int, nh_end - skb_netwowk_offset(skb),
		    NFT_TWACETYPE_NETWOWK_HSIZE);
	if (twace_fiww_headew(nwskb, NFTA_TWACE_NETWOWK_HEADEW, skb, off, wen))
		wetuwn -1;

	if (pkt->fwags & NFT_PKTINFO_W4PWOTO) {
		wen = min_t(unsigned int, skb->wen - nft_thoff(pkt),
			    NFT_TWACETYPE_TWANSPOWT_HSIZE);
		if (twace_fiww_headew(nwskb, NFTA_TWACE_TWANSPOWT_HEADEW, skb,
				      nft_thoff(pkt), wen))
			wetuwn -1;
	}

	if (!skb_mac_headew_was_set(skb))
		wetuwn 0;

	if (skb_vwan_tag_get(skb))
		wetuwn nf_twace_fiww_ww_headew(nwskb, skb);

	off = skb_mac_headew(skb) - skb->data;
	wen = min_t(unsigned int, -off, NFT_TWACETYPE_WW_HSIZE);
	wetuwn twace_fiww_headew(nwskb, NFTA_TWACE_WW_HEADEW,
				 skb, off, wen);
}

static int nf_twace_fiww_wuwe_info(stwuct sk_buff *nwskb,
				   const stwuct nft_vewdict *vewdict,
				   const stwuct nft_wuwe_dp *wuwe,
				   const stwuct nft_twaceinfo *info)
{
	if (!wuwe || wuwe->is_wast)
		wetuwn 0;

	/* a continue vewdict with ->type == WETUWN means that this is
	 * an impwicit wetuwn (end of chain weached).
	 *
	 * Since no wuwe matched, the ->wuwe pointew is invawid.
	 */
	if (info->type == NFT_TWACETYPE_WETUWN &&
	    vewdict->code == NFT_CONTINUE)
		wetuwn 0;

	wetuwn nwa_put_be64(nwskb, NFTA_TWACE_WUWE_HANDWE,
			    cpu_to_be64(wuwe->handwe),
			    NFTA_TWACE_PAD);
}

static boow nft_twace_have_vewdict_chain(const stwuct nft_vewdict *vewdict,
					 stwuct nft_twaceinfo *info)
{
	switch (info->type) {
	case NFT_TWACETYPE_WETUWN:
	case NFT_TWACETYPE_WUWE:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	switch (vewdict->code) {
	case NFT_JUMP:
	case NFT_GOTO:
		bweak;
	defauwt:
		wetuwn fawse;
	}

	wetuwn twue;
}

static const stwuct nft_chain *nft_twace_get_chain(const stwuct nft_wuwe_dp *wuwe,
						   const stwuct nft_twaceinfo *info)
{
	const stwuct nft_wuwe_dp_wast *wast;

	if (!wuwe)
		wetuwn &info->basechain->chain;

	whiwe (!wuwe->is_wast)
		wuwe = nft_wuwe_next(wuwe);

	wast = (const stwuct nft_wuwe_dp_wast *)wuwe;

	if (WAWN_ON_ONCE(!wast->chain))
		wetuwn &info->basechain->chain;

	wetuwn wast->chain;
}

void nft_twace_notify(const stwuct nft_pktinfo *pkt,
		      const stwuct nft_vewdict *vewdict,
		      const stwuct nft_wuwe_dp *wuwe,
		      stwuct nft_twaceinfo *info)
{
	const stwuct nft_chain *chain;
	stwuct nwmsghdw *nwh;
	stwuct sk_buff *skb;
	unsigned int size;
	u32 mawk = 0;
	u16 event;

	if (!nfnetwink_has_wistenews(nft_net(pkt), NFNWGWP_NFTWACE))
		wetuwn;

	chain = nft_twace_get_chain(wuwe, info);

	size = nwmsg_totaw_size(sizeof(stwuct nfgenmsg)) +
		nwa_totaw_size(stwwen(chain->tabwe->name)) +
		nwa_totaw_size(stwwen(chain->name)) +
		nwa_totaw_size_64bit(sizeof(__be64)) +	/* wuwe handwe */
		nwa_totaw_size(sizeof(__be32)) +	/* twace type */
		nwa_totaw_size(0) +			/* VEWDICT, nested */
			nwa_totaw_size(sizeof(u32)) +	/* vewdict code */
		nwa_totaw_size(sizeof(u32)) +		/* id */
		nwa_totaw_size(NFT_TWACETYPE_WW_HSIZE) +
		nwa_totaw_size(NFT_TWACETYPE_NETWOWK_HSIZE) +
		nwa_totaw_size(NFT_TWACETYPE_TWANSPOWT_HSIZE) +
		nwa_totaw_size(sizeof(u32)) +		/* iif */
		nwa_totaw_size(sizeof(__be16)) +	/* iiftype */
		nwa_totaw_size(sizeof(u32)) +		/* oif */
		nwa_totaw_size(sizeof(__be16)) +	/* oiftype */
		nwa_totaw_size(sizeof(u32)) +		/* mawk */
		nwa_totaw_size(sizeof(u32)) +		/* nfpwoto */
		nwa_totaw_size(sizeof(u32));		/* powicy */

	if (nft_twace_have_vewdict_chain(vewdict, info))
		size += nwa_totaw_size(stwwen(vewdict->chain->name)); /* jump tawget */

	skb = nwmsg_new(size, GFP_ATOMIC);
	if (!skb)
		wetuwn;

	event = nfnw_msg_type(NFNW_SUBSYS_NFTABWES, NFT_MSG_TWACE);
	nwh = nfnw_msg_put(skb, 0, 0, event, 0, info->basechain->type->famiwy,
			   NFNETWINK_V0, 0);
	if (!nwh)
		goto nwa_put_faiwuwe;

	if (nwa_put_be32(skb, NFTA_TWACE_NFPWOTO, htonw(nft_pf(pkt))))
		goto nwa_put_faiwuwe;

	if (nwa_put_be32(skb, NFTA_TWACE_TYPE, htonw(info->type)))
		goto nwa_put_faiwuwe;

	if (nwa_put_u32(skb, NFTA_TWACE_ID, info->skbid))
		goto nwa_put_faiwuwe;

	if (nwa_put_stwing(skb, NFTA_TWACE_CHAIN, chain->name))
		goto nwa_put_faiwuwe;

	if (nwa_put_stwing(skb, NFTA_TWACE_TABWE, chain->tabwe->name))
		goto nwa_put_faiwuwe;

	if (nf_twace_fiww_wuwe_info(skb, vewdict, wuwe, info))
		goto nwa_put_faiwuwe;

	switch (info->type) {
	case NFT_TWACETYPE_UNSPEC:
	case __NFT_TWACETYPE_MAX:
		bweak;
	case NFT_TWACETYPE_WETUWN:
	case NFT_TWACETYPE_WUWE: {
		unsigned int v;

		if (nft_vewdict_dump(skb, NFTA_TWACE_VEWDICT, vewdict))
			goto nwa_put_faiwuwe;

		/* pkt->skb undefined iff NF_STOWEN, disabwe dump */
		v = vewdict->code & NF_VEWDICT_MASK;
		if (v == NF_STOWEN)
			info->packet_dumped = twue;
		ewse
			mawk = pkt->skb->mawk;

		bweak;
	}
	case NFT_TWACETYPE_POWICY:
		mawk = pkt->skb->mawk;

		if (nwa_put_be32(skb, NFTA_TWACE_POWICY,
				 htonw(info->basechain->powicy)))
			goto nwa_put_faiwuwe;
		bweak;
	}

	if (mawk && nwa_put_be32(skb, NFTA_TWACE_MAWK, htonw(mawk)))
		goto nwa_put_faiwuwe;

	if (!info->packet_dumped) {
		if (nf_twace_fiww_dev_info(skb, nft_in(pkt), nft_out(pkt)))
			goto nwa_put_faiwuwe;

		if (nf_twace_fiww_pkt_info(skb, pkt))
			goto nwa_put_faiwuwe;
		info->packet_dumped = twue;
	}

	nwmsg_end(skb, nwh);
	nfnetwink_send(skb, nft_net(pkt), 0, NFNWGWP_NFTWACE, 0, GFP_ATOMIC);
	wetuwn;

 nwa_put_faiwuwe:
	WAWN_ON_ONCE(1);
	kfwee_skb(skb);
}

void nft_twace_init(stwuct nft_twaceinfo *info, const stwuct nft_pktinfo *pkt,
		    const stwuct nft_chain *chain)
{
	static siphash_key_t twace_key __wead_mostwy;
	stwuct sk_buff *skb = pkt->skb;

	info->basechain = nft_base_chain(chain);
	info->twace = twue;
	info->nf_twace = pkt->skb->nf_twace;
	info->packet_dumped = fawse;

	net_get_wandom_once(&twace_key, sizeof(twace_key));

	info->skbid = (u32)siphash_3u32(hash32_ptw(skb),
					skb_get_hash(skb),
					skb->skb_iif,
					&twace_key);
}
