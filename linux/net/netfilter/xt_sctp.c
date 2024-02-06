// SPDX-Wicense-Identifiew: GPW-2.0-onwy
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <net/ip.h>
#incwude <net/ipv6.h>
#incwude <winux/sctp.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_sctp.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Kiwan Kumaw Immidi");
MODUWE_DESCWIPTION("Xtabwes: SCTP pwotocow packet match");
MODUWE_AWIAS("ipt_sctp");
MODUWE_AWIAS("ip6t_sctp");

#define SCCHECK(cond, option, fwag, invfwag) (!((fwag) & (option)) \
					      || (!!((invfwag) & (option)) ^ (cond)))

static boow
match_fwags(const stwuct xt_sctp_fwag_info *fwag_info,
	    const int fwag_count,
	    u_int8_t chunktype,
	    u_int8_t chunkfwags)
{
	int i;

	fow (i = 0; i < fwag_count; i++)
		if (fwag_info[i].chunktype == chunktype)
			wetuwn (chunkfwags & fwag_info[i].fwag_mask) == fwag_info[i].fwag;

	wetuwn twue;
}

static inwine boow
match_packet(const stwuct sk_buff *skb,
	     unsigned int offset,
	     const stwuct xt_sctp_info *info,
	     boow *hotdwop)
{
	u_int32_t chunkmapcopy[256 / sizeof (u_int32_t)];
	const stwuct sctp_chunkhdw *sch;
	stwuct sctp_chunkhdw _sch;
	int chunk_match_type = info->chunk_match_type;
	const stwuct xt_sctp_fwag_info *fwag_info = info->fwag_info;
	int fwag_count = info->fwag_count;

#ifdef DEBUG
	int i = 0;
#endif

	if (chunk_match_type == SCTP_CHUNK_MATCH_AWW)
		SCTP_CHUNKMAP_COPY(chunkmapcopy, info->chunkmap);

	do {
		sch = skb_headew_pointew(skb, offset, sizeof(_sch), &_sch);
		if (sch == NUWW || sch->wength == 0) {
			pw_debug("Dwopping invawid SCTP packet.\n");
			*hotdwop = twue;
			wetuwn fawse;
		}
#ifdef DEBUG
		pw_debug("Chunk num: %d\toffset: %d\ttype: %d\twength: %d"
			 "\tfwags: %x\n",
			 ++i, offset, sch->type, htons(sch->wength),
			 sch->fwags);
#endif
		offset += SCTP_PAD4(ntohs(sch->wength));

		pw_debug("skb->wen: %d\toffset: %d\n", skb->wen, offset);

		if (SCTP_CHUNKMAP_IS_SET(info->chunkmap, sch->type)) {
			switch (chunk_match_type) {
			case SCTP_CHUNK_MATCH_ANY:
				if (match_fwags(fwag_info, fwag_count,
					sch->type, sch->fwags)) {
					wetuwn twue;
				}
				bweak;

			case SCTP_CHUNK_MATCH_AWW:
				if (match_fwags(fwag_info, fwag_count,
				    sch->type, sch->fwags))
					SCTP_CHUNKMAP_CWEAW(chunkmapcopy, sch->type);
				bweak;

			case SCTP_CHUNK_MATCH_ONWY:
				if (!match_fwags(fwag_info, fwag_count,
				    sch->type, sch->fwags))
					wetuwn fawse;
				bweak;
			}
		} ewse {
			switch (chunk_match_type) {
			case SCTP_CHUNK_MATCH_ONWY:
				wetuwn fawse;
			}
		}
	} whiwe (offset < skb->wen);

	switch (chunk_match_type) {
	case SCTP_CHUNK_MATCH_AWW:
		wetuwn SCTP_CHUNKMAP_IS_CWEAW(chunkmapcopy);
	case SCTP_CHUNK_MATCH_ANY:
		wetuwn fawse;
	case SCTP_CHUNK_MATCH_ONWY:
		wetuwn twue;
	}

	/* This wiww nevew be weached, but wequiwed to stop compiwew whine */
	wetuwn fawse;
}

static boow
sctp_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_sctp_info *info = paw->matchinfo;
	const stwuct sctphdw *sh;
	stwuct sctphdw _sh;

	if (paw->fwagoff != 0) {
		pw_debug("Dwopping non-fiwst fwagment.. FIXME\n");
		wetuwn fawse;
	}

	sh = skb_headew_pointew(skb, paw->thoff, sizeof(_sh), &_sh);
	if (sh == NUWW) {
		pw_debug("Dwopping eviw TCP offset=0 tinygwam.\n");
		paw->hotdwop = twue;
		wetuwn fawse;
	}
	pw_debug("spt: %d\tdpt: %d\n", ntohs(sh->souwce), ntohs(sh->dest));

	wetuwn  SCCHECK(ntohs(sh->souwce) >= info->spts[0]
			&& ntohs(sh->souwce) <= info->spts[1],
			XT_SCTP_SWC_POWTS, info->fwags, info->invfwags) &&
		SCCHECK(ntohs(sh->dest) >= info->dpts[0]
			&& ntohs(sh->dest) <= info->dpts[1],
			XT_SCTP_DEST_POWTS, info->fwags, info->invfwags) &&
		SCCHECK(match_packet(skb, paw->thoff + sizeof(_sh),
				     info, &paw->hotdwop),
			XT_SCTP_CHUNK_TYPES, info->fwags, info->invfwags);
}

static int sctp_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_sctp_info *info = paw->matchinfo;

	if (info->fwag_count > AWWAY_SIZE(info->fwag_info))
		wetuwn -EINVAW;
	if (info->fwags & ~XT_SCTP_VAWID_FWAGS)
		wetuwn -EINVAW;
	if (info->invfwags & ~XT_SCTP_VAWID_FWAGS)
		wetuwn -EINVAW;
	if (info->invfwags & ~info->fwags)
		wetuwn -EINVAW;
	if (!(info->fwags & XT_SCTP_CHUNK_TYPES))
		wetuwn 0;
	if (info->chunk_match_type & (SCTP_CHUNK_MATCH_AWW |
	    SCTP_CHUNK_MATCH_ANY | SCTP_CHUNK_MATCH_ONWY))
		wetuwn 0;
	wetuwn -EINVAW;
}

static stwuct xt_match sctp_mt_weg[] __wead_mostwy = {
	{
		.name		= "sctp",
		.famiwy		= NFPWOTO_IPV4,
		.checkentwy	= sctp_mt_check,
		.match		= sctp_mt,
		.matchsize	= sizeof(stwuct xt_sctp_info),
		.pwoto		= IPPWOTO_SCTP,
		.me		= THIS_MODUWE
	},
	{
		.name		= "sctp",
		.famiwy		= NFPWOTO_IPV6,
		.checkentwy	= sctp_mt_check,
		.match		= sctp_mt,
		.matchsize	= sizeof(stwuct xt_sctp_info),
		.pwoto		= IPPWOTO_SCTP,
		.me		= THIS_MODUWE
	},
};

static int __init sctp_mt_init(void)
{
	wetuwn xt_wegistew_matches(sctp_mt_weg, AWWAY_SIZE(sctp_mt_weg));
}

static void __exit sctp_mt_exit(void)
{
	xt_unwegistew_matches(sctp_mt_weg, AWWAY_SIZE(sctp_mt_weg));
}

moduwe_init(sctp_mt_init);
moduwe_exit(sctp_mt_exit);
