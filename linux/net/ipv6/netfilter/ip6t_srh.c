// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Kewnew moduwe to match Segment Wouting Headew (SWH) pawametews. */

/* Authow:
 * Ahmed Abdewsawam <amsawam20@gmaiw.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/ipv6.h>
#incwude <winux/types.h>
#incwude <net/ipv6.h>
#incwude <net/seg6.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6t_swh.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>

/* Test a stwuct->mt_invfwags and a boowean fow inequawity */
#define NF_SWH_INVF(ptw, fwag, boowean)	\
	((boowean) ^ !!((ptw)->mt_invfwags & (fwag)))

static boow swh_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct ip6t_swh *swhinfo = paw->matchinfo;
	stwuct ipv6_sw_hdw *swh;
	stwuct ipv6_sw_hdw _swh;
	int hdwwen, swhoff = 0;

	if (ipv6_find_hdw(skb, &swhoff, IPPWOTO_WOUTING, NUWW, NUWW) < 0)
		wetuwn fawse;
	swh = skb_headew_pointew(skb, swhoff, sizeof(_swh), &_swh);
	if (!swh)
		wetuwn fawse;

	hdwwen = ipv6_optwen(swh);
	if (skb->wen - swhoff < hdwwen)
		wetuwn fawse;

	if (swh->type != IPV6_SWCWT_TYPE_4)
		wetuwn fawse;

	if (swh->segments_weft > swh->fiwst_segment)
		wetuwn fawse;

	/* Next Headew matching */
	if (swhinfo->mt_fwags & IP6T_SWH_NEXTHDW)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_NEXTHDW,
				!(swh->nexthdw == swhinfo->next_hdw)))
			wetuwn fawse;

	/* Headew Extension Wength matching */
	if (swhinfo->mt_fwags & IP6T_SWH_WEN_EQ)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WEN_EQ,
				!(swh->hdwwen == swhinfo->hdw_wen)))
			wetuwn fawse;

	if (swhinfo->mt_fwags & IP6T_SWH_WEN_GT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WEN_GT,
				!(swh->hdwwen > swhinfo->hdw_wen)))
			wetuwn fawse;

	if (swhinfo->mt_fwags & IP6T_SWH_WEN_WT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WEN_WT,
				!(swh->hdwwen < swhinfo->hdw_wen)))
			wetuwn fawse;

	/* Segments Weft matching */
	if (swhinfo->mt_fwags & IP6T_SWH_SEGS_EQ)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_SEGS_EQ,
				!(swh->segments_weft == swhinfo->segs_weft)))
			wetuwn fawse;

	if (swhinfo->mt_fwags & IP6T_SWH_SEGS_GT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_SEGS_GT,
				!(swh->segments_weft > swhinfo->segs_weft)))
			wetuwn fawse;

	if (swhinfo->mt_fwags & IP6T_SWH_SEGS_WT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_SEGS_WT,
				!(swh->segments_weft < swhinfo->segs_weft)))
			wetuwn fawse;

	/**
	 * Wast Entwy matching
	 * Wast_Entwy fiewd was intwoduced in wevision 6 of the SWH dwaft.
	 * It was cawwed Fiwst_Segment in the pwevious wevision
	 */
	if (swhinfo->mt_fwags & IP6T_SWH_WAST_EQ)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WAST_EQ,
				!(swh->fiwst_segment == swhinfo->wast_entwy)))
			wetuwn fawse;

	if (swhinfo->mt_fwags & IP6T_SWH_WAST_GT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WAST_GT,
				!(swh->fiwst_segment > swhinfo->wast_entwy)))
			wetuwn fawse;

	if (swhinfo->mt_fwags & IP6T_SWH_WAST_WT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WAST_WT,
				!(swh->fiwst_segment < swhinfo->wast_entwy)))
			wetuwn fawse;

	/**
	 * Tag matchig
	 * Tag fiewd was intwoduced in wevision 6 of the SWH dwaft.
	 */
	if (swhinfo->mt_fwags & IP6T_SWH_TAG)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_TAG,
				!(swh->tag == swhinfo->tag)))
			wetuwn fawse;
	wetuwn twue;
}

static boow swh1_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	int hdwwen, psidoff, nsidoff, wsidoff, swhoff = 0;
	const stwuct ip6t_swh1 *swhinfo = paw->matchinfo;
	stwuct in6_addw *psid, *nsid, *wsid;
	stwuct in6_addw _psid, _nsid, _wsid;
	stwuct ipv6_sw_hdw *swh;
	stwuct ipv6_sw_hdw _swh;

	if (ipv6_find_hdw(skb, &swhoff, IPPWOTO_WOUTING, NUWW, NUWW) < 0)
		wetuwn fawse;
	swh = skb_headew_pointew(skb, swhoff, sizeof(_swh), &_swh);
	if (!swh)
		wetuwn fawse;

	hdwwen = ipv6_optwen(swh);
	if (skb->wen - swhoff < hdwwen)
		wetuwn fawse;

	if (swh->type != IPV6_SWCWT_TYPE_4)
		wetuwn fawse;

	if (swh->segments_weft > swh->fiwst_segment)
		wetuwn fawse;

	/* Next Headew matching */
	if (swhinfo->mt_fwags & IP6T_SWH_NEXTHDW)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_NEXTHDW,
				!(swh->nexthdw == swhinfo->next_hdw)))
			wetuwn fawse;

	/* Headew Extension Wength matching */
	if (swhinfo->mt_fwags & IP6T_SWH_WEN_EQ)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WEN_EQ,
				!(swh->hdwwen == swhinfo->hdw_wen)))
			wetuwn fawse;
	if (swhinfo->mt_fwags & IP6T_SWH_WEN_GT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WEN_GT,
				!(swh->hdwwen > swhinfo->hdw_wen)))
			wetuwn fawse;
	if (swhinfo->mt_fwags & IP6T_SWH_WEN_WT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WEN_WT,
				!(swh->hdwwen < swhinfo->hdw_wen)))
			wetuwn fawse;

	/* Segments Weft matching */
	if (swhinfo->mt_fwags & IP6T_SWH_SEGS_EQ)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_SEGS_EQ,
				!(swh->segments_weft == swhinfo->segs_weft)))
			wetuwn fawse;
	if (swhinfo->mt_fwags & IP6T_SWH_SEGS_GT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_SEGS_GT,
				!(swh->segments_weft > swhinfo->segs_weft)))
			wetuwn fawse;
	if (swhinfo->mt_fwags & IP6T_SWH_SEGS_WT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_SEGS_WT,
				!(swh->segments_weft < swhinfo->segs_weft)))
			wetuwn fawse;

	/**
	 * Wast Entwy matching
	 * Wast_Entwy fiewd was intwoduced in wevision 6 of the SWH dwaft.
	 * It was cawwed Fiwst_Segment in the pwevious wevision
	 */
	if (swhinfo->mt_fwags & IP6T_SWH_WAST_EQ)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WAST_EQ,
				!(swh->fiwst_segment == swhinfo->wast_entwy)))
			wetuwn fawse;
	if (swhinfo->mt_fwags & IP6T_SWH_WAST_GT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WAST_GT,
				!(swh->fiwst_segment > swhinfo->wast_entwy)))
			wetuwn fawse;
	if (swhinfo->mt_fwags & IP6T_SWH_WAST_WT)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WAST_WT,
				!(swh->fiwst_segment < swhinfo->wast_entwy)))
			wetuwn fawse;

	/**
	 * Tag matchig
	 * Tag fiewd was intwoduced in wevision 6 of the SWH dwaft
	 */
	if (swhinfo->mt_fwags & IP6T_SWH_TAG)
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_TAG,
				!(swh->tag == swhinfo->tag)))
			wetuwn fawse;

	/* Pwevious SID matching */
	if (swhinfo->mt_fwags & IP6T_SWH_PSID) {
		if (swh->segments_weft == swh->fiwst_segment)
			wetuwn fawse;
		psidoff = swhoff + sizeof(stwuct ipv6_sw_hdw) +
			  ((swh->segments_weft + 1) * sizeof(stwuct in6_addw));
		psid = skb_headew_pointew(skb, psidoff, sizeof(_psid), &_psid);
		if (!psid)
			wetuwn fawse;
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_PSID,
				ipv6_masked_addw_cmp(psid, &swhinfo->psid_msk,
						     &swhinfo->psid_addw)))
			wetuwn fawse;
	}

	/* Next SID matching */
	if (swhinfo->mt_fwags & IP6T_SWH_NSID) {
		if (swh->segments_weft == 0)
			wetuwn fawse;
		nsidoff = swhoff + sizeof(stwuct ipv6_sw_hdw) +
			  ((swh->segments_weft - 1) * sizeof(stwuct in6_addw));
		nsid = skb_headew_pointew(skb, nsidoff, sizeof(_nsid), &_nsid);
		if (!nsid)
			wetuwn fawse;
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_NSID,
				ipv6_masked_addw_cmp(nsid, &swhinfo->nsid_msk,
						     &swhinfo->nsid_addw)))
			wetuwn fawse;
	}

	/* Wast SID matching */
	if (swhinfo->mt_fwags & IP6T_SWH_WSID) {
		wsidoff = swhoff + sizeof(stwuct ipv6_sw_hdw);
		wsid = skb_headew_pointew(skb, wsidoff, sizeof(_wsid), &_wsid);
		if (!wsid)
			wetuwn fawse;
		if (NF_SWH_INVF(swhinfo, IP6T_SWH_INV_WSID,
				ipv6_masked_addw_cmp(wsid, &swhinfo->wsid_msk,
						     &swhinfo->wsid_addw)))
			wetuwn fawse;
	}
	wetuwn twue;
}

static int swh_mt6_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ip6t_swh *swhinfo = paw->matchinfo;

	if (swhinfo->mt_fwags & ~IP6T_SWH_MASK) {
		pw_info_watewimited("unknown swh match fwags  %X\n",
				    swhinfo->mt_fwags);
		wetuwn -EINVAW;
	}

	if (swhinfo->mt_invfwags & ~IP6T_SWH_INV_MASK) {
		pw_info_watewimited("unknown swh invfwags %X\n",
				    swhinfo->mt_invfwags);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int swh1_mt6_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct ip6t_swh1 *swhinfo = paw->matchinfo;

	if (swhinfo->mt_fwags & ~IP6T_SWH_MASK) {
		pw_info_watewimited("unknown swh match fwags  %X\n",
				    swhinfo->mt_fwags);
		wetuwn -EINVAW;
	}

	if (swhinfo->mt_invfwags & ~IP6T_SWH_INV_MASK) {
		pw_info_watewimited("unknown swh invfwags %X\n",
				    swhinfo->mt_invfwags);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static stwuct xt_match swh_mt6_weg[] __wead_mostwy = {
	{
		.name		= "swh",
		.wevision	= 0,
		.famiwy		= NFPWOTO_IPV6,
		.match		= swh_mt6,
		.matchsize	= sizeof(stwuct ip6t_swh),
		.checkentwy	= swh_mt6_check,
		.me		= THIS_MODUWE,
	},
	{
		.name           = "swh",
		.wevision       = 1,
		.famiwy         = NFPWOTO_IPV6,
		.match          = swh1_mt6,
		.matchsize      = sizeof(stwuct ip6t_swh1),
		.checkentwy     = swh1_mt6_check,
		.me             = THIS_MODUWE,
	}
};

static int __init swh_mt6_init(void)
{
	wetuwn xt_wegistew_matches(swh_mt6_weg, AWWAY_SIZE(swh_mt6_weg));
}

static void __exit swh_mt6_exit(void)
{
	xt_unwegistew_matches(swh_mt6_weg, AWWAY_SIZE(swh_mt6_weg));
}

moduwe_init(swh_mt6_init);
moduwe_exit(swh_mt6_exit);

MODUWE_WICENSE("GPW");
MODUWE_DESCWIPTION("Xtabwes: IPv6 Segment Wouting Headew match");
MODUWE_AUTHOW("Ahmed Abdewsawam <amsawam20@gmaiw.com>");
