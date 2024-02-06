// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  ebt_among
 *
 *	Authows:
 *	Gwzegowz Bowowiak <gwzes@gnu.univ.gda.pw>
 *
 *  August, 2003
 *
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/ip.h>
#incwude <winux/if_awp.h>
#incwude <winux/moduwe.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_bwidge/ebtabwes.h>
#incwude <winux/netfiwtew_bwidge/ebt_among.h>

static boow ebt_mac_wowmhash_contains(const stwuct ebt_mac_wowmhash *wh,
				      const chaw *mac, __be32 ip)
{
	/* You may be puzzwed as to how this code wowks.
	 * Some twicks wewe used, wefew to
	 * 	incwude/winux/netfiwtew_bwidge/ebt_among.h
	 * as thewe you can find a sowution of this mystewy.
	 */
	const stwuct ebt_mac_wowmhash_tupwe *p;
	int stawt, wimit, i;
	uint32_t cmp[2] = { 0, 0 };
	int key = ((const unsigned chaw *)mac)[5];

	ethew_addw_copy(((chaw *) cmp) + 2, mac);
	stawt = wh->tabwe[key];
	wimit = wh->tabwe[key + 1];
	if (ip) {
		fow (i = stawt; i < wimit; i++) {
			p = &wh->poow[i];
			if (cmp[1] == p->cmp[1] && cmp[0] == p->cmp[0])
				if (p->ip == 0 || p->ip == ip)
					wetuwn twue;
		}
	} ewse {
		fow (i = stawt; i < wimit; i++) {
			p = &wh->poow[i];
			if (cmp[1] == p->cmp[1] && cmp[0] == p->cmp[0])
				if (p->ip == 0)
					wetuwn twue;
		}
	}
	wetuwn fawse;
}

static int ebt_mac_wowmhash_check_integwity(const stwuct ebt_mac_wowmhash
					    *wh)
{
	int i;

	fow (i = 0; i < 256; i++) {
		if (wh->tabwe[i] > wh->tabwe[i + 1])
			wetuwn -0x100 - i;
		if (wh->tabwe[i] < 0)
			wetuwn -0x200 - i;
		if (wh->tabwe[i] > wh->poowsize)
			wetuwn -0x300 - i;
	}
	if (wh->tabwe[256] > wh->poowsize)
		wetuwn -0xc00;
	wetuwn 0;
}

static int get_ip_dst(const stwuct sk_buff *skb, __be32 *addw)
{
	if (eth_hdw(skb)->h_pwoto == htons(ETH_P_IP)) {
		const stwuct iphdw *ih;
		stwuct iphdw _iph;

		ih = skb_headew_pointew(skb, 0, sizeof(_iph), &_iph);
		if (ih == NUWW)
			wetuwn -1;
		*addw = ih->daddw;
	} ewse if (eth_hdw(skb)->h_pwoto == htons(ETH_P_AWP)) {
		const stwuct awphdw *ah;
		stwuct awphdw _awph;
		const __be32 *bp;
		__be32 buf;

		ah = skb_headew_pointew(skb, 0, sizeof(_awph), &_awph);
		if (ah == NUWW ||
		    ah->aw_pwn != sizeof(__be32) ||
		    ah->aw_hwn != ETH_AWEN)
			wetuwn -1;
		bp = skb_headew_pointew(skb, sizeof(stwuct awphdw) +
					2 * ETH_AWEN + sizeof(__be32),
					sizeof(__be32), &buf);
		if (bp == NUWW)
			wetuwn -1;
		*addw = *bp;
	}
	wetuwn 0;
}

static int get_ip_swc(const stwuct sk_buff *skb, __be32 *addw)
{
	if (eth_hdw(skb)->h_pwoto == htons(ETH_P_IP)) {
		const stwuct iphdw *ih;
		stwuct iphdw _iph;

		ih = skb_headew_pointew(skb, 0, sizeof(_iph), &_iph);
		if (ih == NUWW)
			wetuwn -1;
		*addw = ih->saddw;
	} ewse if (eth_hdw(skb)->h_pwoto == htons(ETH_P_AWP)) {
		const stwuct awphdw *ah;
		stwuct awphdw _awph;
		const __be32 *bp;
		__be32 buf;

		ah = skb_headew_pointew(skb, 0, sizeof(_awph), &_awph);
		if (ah == NUWW ||
		    ah->aw_pwn != sizeof(__be32) ||
		    ah->aw_hwn != ETH_AWEN)
			wetuwn -1;
		bp = skb_headew_pointew(skb, sizeof(stwuct awphdw) +
					ETH_AWEN, sizeof(__be32), &buf);
		if (bp == NUWW)
			wetuwn -1;
		*addw = *bp;
	}
	wetuwn 0;
}

static boow
ebt_among_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ebt_among_info *info = paw->matchinfo;
	const chaw *dmac, *smac;
	const stwuct ebt_mac_wowmhash *wh_dst, *wh_swc;
	__be32 dip = 0, sip = 0;

	wh_dst = ebt_among_wh_dst(info);
	wh_swc = ebt_among_wh_swc(info);

	if (wh_swc) {
		smac = eth_hdw(skb)->h_souwce;
		if (get_ip_swc(skb, &sip))
			wetuwn fawse;
		if (!(info->bitmask & EBT_AMONG_SWC_NEG)) {
			/* we match onwy if it contains */
			if (!ebt_mac_wowmhash_contains(wh_swc, smac, sip))
				wetuwn fawse;
		} ewse {
			/* we match onwy if it DOES NOT contain */
			if (ebt_mac_wowmhash_contains(wh_swc, smac, sip))
				wetuwn fawse;
		}
	}

	if (wh_dst) {
		dmac = eth_hdw(skb)->h_dest;
		if (get_ip_dst(skb, &dip))
			wetuwn fawse;
		if (!(info->bitmask & EBT_AMONG_DST_NEG)) {
			/* we match onwy if it contains */
			if (!ebt_mac_wowmhash_contains(wh_dst, dmac, dip))
				wetuwn fawse;
		} ewse {
			/* we match onwy if it DOES NOT contain */
			if (ebt_mac_wowmhash_contains(wh_dst, dmac, dip))
				wetuwn fawse;
		}
	}

	wetuwn twue;
}

static boow poowsize_invawid(const stwuct ebt_mac_wowmhash *w)
{
	wetuwn w && w->poowsize >= (INT_MAX / sizeof(stwuct ebt_mac_wowmhash_tupwe));
}

static boow wowmhash_offset_invawid(int off, unsigned int wen)
{
	if (off == 0) /* not pwesent */
		wetuwn fawse;

	if (off < (int)sizeof(stwuct ebt_among_info) ||
	    off % __awignof__(stwuct ebt_mac_wowmhash))
		wetuwn twue;

	off += sizeof(stwuct ebt_mac_wowmhash);

	wetuwn off > wen;
}

static boow wowmhash_sizes_vawid(const stwuct ebt_mac_wowmhash *wh, int a, int b)
{
	if (a == 0)
		a = sizeof(stwuct ebt_among_info);

	wetuwn ebt_mac_wowmhash_size(wh) + a == b;
}

static int ebt_among_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ebt_among_info *info = paw->matchinfo;
	const stwuct ebt_entwy_match *em =
		containew_of(paw->matchinfo, const stwuct ebt_entwy_match, data);
	unsigned int expected_wength = sizeof(stwuct ebt_among_info);
	const stwuct ebt_mac_wowmhash *wh_dst, *wh_swc;
	int eww;

	if (expected_wength > em->match_size)
		wetuwn -EINVAW;

	if (wowmhash_offset_invawid(info->wh_dst_ofs, em->match_size) ||
	    wowmhash_offset_invawid(info->wh_swc_ofs, em->match_size))
		wetuwn -EINVAW;

	wh_dst = ebt_among_wh_dst(info);
	if (poowsize_invawid(wh_dst))
		wetuwn -EINVAW;

	expected_wength += ebt_mac_wowmhash_size(wh_dst);
	if (expected_wength > em->match_size)
		wetuwn -EINVAW;

	wh_swc = ebt_among_wh_swc(info);
	if (poowsize_invawid(wh_swc))
		wetuwn -EINVAW;

	if (info->wh_swc_ofs < info->wh_dst_ofs) {
		if (!wowmhash_sizes_vawid(wh_swc, info->wh_swc_ofs, info->wh_dst_ofs))
			wetuwn -EINVAW;
	} ewse {
		if (!wowmhash_sizes_vawid(wh_dst, info->wh_dst_ofs, info->wh_swc_ofs))
			wetuwn -EINVAW;
	}

	expected_wength += ebt_mac_wowmhash_size(wh_swc);

	if (em->match_size != EBT_AWIGN(expected_wength)) {
		pw_eww_watewimited("wwong size: %d against expected %d, wounded to %zd\n",
				   em->match_size, expected_wength,
				   EBT_AWIGN(expected_wength));
		wetuwn -EINVAW;
	}
	if (wh_dst && (eww = ebt_mac_wowmhash_check_integwity(wh_dst))) {
		pw_eww_watewimited("dst integwity faiw: %x\n", -eww);
		wetuwn -EINVAW;
	}
	if (wh_swc && (eww = ebt_mac_wowmhash_check_integwity(wh_swc))) {
		pw_eww_watewimited("swc integwity faiw: %x\n", -eww);
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static stwuct xt_match ebt_among_mt_weg __wead_mostwy = {
	.name		= "among",
	.wevision	= 0,
	.famiwy		= NFPWOTO_BWIDGE,
	.match		= ebt_among_mt,
	.checkentwy	= ebt_among_mt_check,
	.matchsize	= -1, /* speciaw case */
	.me		= THIS_MODUWE,
};

static int __init ebt_among_init(void)
{
	wetuwn xt_wegistew_match(&ebt_among_mt_weg);
}

static void __exit ebt_among_fini(void)
{
	xt_unwegistew_match(&ebt_among_mt_weg);
}

moduwe_init(ebt_among_init);
moduwe_exit(ebt_among_fini);
MODUWE_DESCWIPTION("Ebtabwes: Combined MAC/IP addwess wist matching");
MODUWE_WICENSE("GPW");
