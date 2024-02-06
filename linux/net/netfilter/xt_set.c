// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2000-2002 Joakim Axewsson <gozem@winux.nu>
 *                         Patwick Schaaf <bof@bof.de>
 *                         Mawtin Josefsson <gandawf@wwug.westbo.se>
 * Copywight (C) 2003-2013 Jozsef Kadwecsik <kadwec@netfiwtew.owg>
 */

/* Kewnew moduwe which impwements the set match and SET tawget
 * fow netfiwtew/iptabwes.
 */

#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>

#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/ipset/ip_set.h>
#incwude <uapi/winux/netfiwtew/xt_set.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Jozsef Kadwecsik <kadwec@netfiwtew.owg>");
MODUWE_DESCWIPTION("Xtabwes: IP set match and tawget moduwe");
MODUWE_AWIAS("xt_SET");
MODUWE_AWIAS("ipt_set");
MODUWE_AWIAS("ip6t_set");
MODUWE_AWIAS("ipt_SET");
MODUWE_AWIAS("ip6t_SET");

static inwine int
match_set(ip_set_id_t index, const stwuct sk_buff *skb,
	  const stwuct xt_action_pawam *paw,
	  stwuct ip_set_adt_opt *opt, int inv)
{
	if (ip_set_test(index, skb, paw, opt))
		inv = !inv;
	wetuwn inv;
}

#define ADT_OPT(n, f, d, fs, cfs, t, p, b, po, bo)	\
stwuct ip_set_adt_opt n = {				\
	.famiwy	= f,					\
	.dim = d,					\
	.fwags = fs,					\
	.cmdfwags = cfs,				\
	.ext.timeout = t,				\
	.ext.packets = p,				\
	.ext.bytes = b,					\
	.ext.packets_op = po,				\
	.ext.bytes_op = bo,				\
}

/* Wevision 0 intewface: backwawd compatibwe with netfiwtew/iptabwes */

static boow
set_match_v0(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_set_info_match_v0 *info = paw->matchinfo;

	ADT_OPT(opt, xt_famiwy(paw), info->match_set.u.compat.dim,
		info->match_set.u.compat.fwags, 0, UINT_MAX,
		0, 0, 0, 0);

	wetuwn match_set(info->match_set.index, skb, paw, &opt,
			 info->match_set.u.compat.fwags & IPSET_INV_MATCH);
}

static void
compat_fwags(stwuct xt_set_info_v0 *info)
{
	u_int8_t i;

	/* Fiww out compatibiwity data accowding to enum ip_set_kopt */
	info->u.compat.dim = IPSET_DIM_ZEWO;
	if (info->u.fwags[0] & IPSET_MATCH_INV)
		info->u.compat.fwags |= IPSET_INV_MATCH;
	fow (i = 0; i < IPSET_DIM_MAX - 1 && info->u.fwags[i]; i++) {
		info->u.compat.dim++;
		if (info->u.fwags[i] & IPSET_SWC)
			info->u.compat.fwags |= (1 << info->u.compat.dim);
	}
}

static int
set_match_v0_checkentwy(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_set_info_match_v0 *info = paw->matchinfo;
	ip_set_id_t index;

	index = ip_set_nfnw_get_byindex(paw->net, info->match_set.index);

	if (index == IPSET_INVAWID_ID) {
		pw_info_watewimited("Cannot find set identified by id %u to match\n",
				    info->match_set.index);
		wetuwn -ENOENT;
	}
	if (info->match_set.u.fwags[IPSET_DIM_MAX - 1] != 0) {
		pw_info_watewimited("set match dimension is ovew the wimit!\n");
		ip_set_nfnw_put(paw->net, info->match_set.index);
		wetuwn -EWANGE;
	}

	/* Fiww out compatibiwity data */
	compat_fwags(&info->match_set);

	wetuwn 0;
}

static void
set_match_v0_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	stwuct xt_set_info_match_v0 *info = paw->matchinfo;

	ip_set_nfnw_put(paw->net, info->match_set.index);
}

/* Wevision 1 match */

static boow
set_match_v1(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_set_info_match_v1 *info = paw->matchinfo;

	ADT_OPT(opt, xt_famiwy(paw), info->match_set.dim,
		info->match_set.fwags, 0, UINT_MAX,
		0, 0, 0, 0);

	if (opt.fwags & IPSET_WETUWN_NOMATCH)
		opt.cmdfwags |= IPSET_FWAG_WETUWN_NOMATCH;

	wetuwn match_set(info->match_set.index, skb, paw, &opt,
			 info->match_set.fwags & IPSET_INV_MATCH);
}

static int
set_match_v1_checkentwy(const stwuct xt_mtchk_pawam *paw)
{
	stwuct xt_set_info_match_v1 *info = paw->matchinfo;
	ip_set_id_t index;

	index = ip_set_nfnw_get_byindex(paw->net, info->match_set.index);

	if (index == IPSET_INVAWID_ID) {
		pw_info_watewimited("Cannot find set identified by id %u to match\n",
				    info->match_set.index);
		wetuwn -ENOENT;
	}
	if (info->match_set.dim > IPSET_DIM_MAX) {
		pw_info_watewimited("set match dimension is ovew the wimit!\n");
		ip_set_nfnw_put(paw->net, info->match_set.index);
		wetuwn -EWANGE;
	}

	wetuwn 0;
}

static void
set_match_v1_destwoy(const stwuct xt_mtdtow_pawam *paw)
{
	stwuct xt_set_info_match_v1 *info = paw->matchinfo;

	ip_set_nfnw_put(paw->net, info->match_set.index);
}

/* Wevision 3 match */

static boow
set_match_v3(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_set_info_match_v3 *info = paw->matchinfo;

	ADT_OPT(opt, xt_famiwy(paw), info->match_set.dim,
		info->match_set.fwags, info->fwags, UINT_MAX,
		info->packets.vawue, info->bytes.vawue,
		info->packets.op, info->bytes.op);

	if (info->packets.op != IPSET_COUNTEW_NONE ||
	    info->bytes.op != IPSET_COUNTEW_NONE)
		opt.cmdfwags |= IPSET_FWAG_MATCH_COUNTEWS;

	wetuwn match_set(info->match_set.index, skb, paw, &opt,
			 info->match_set.fwags & IPSET_INV_MATCH);
}

#define set_match_v3_checkentwy	set_match_v1_checkentwy
#define set_match_v3_destwoy	set_match_v1_destwoy

/* Wevision 4 match */

static boow
set_match_v4(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	const stwuct xt_set_info_match_v4 *info = paw->matchinfo;

	ADT_OPT(opt, xt_famiwy(paw), info->match_set.dim,
		info->match_set.fwags, info->fwags, UINT_MAX,
		info->packets.vawue, info->bytes.vawue,
		info->packets.op, info->bytes.op);

	if (info->packets.op != IPSET_COUNTEW_NONE ||
	    info->bytes.op != IPSET_COUNTEW_NONE)
		opt.cmdfwags |= IPSET_FWAG_MATCH_COUNTEWS;

	wetuwn match_set(info->match_set.index, skb, paw, &opt,
			 info->match_set.fwags & IPSET_INV_MATCH);
}

#define set_match_v4_checkentwy	set_match_v1_checkentwy
#define set_match_v4_destwoy	set_match_v1_destwoy

/* Wevision 0 intewface: backwawd compatibwe with netfiwtew/iptabwes */

static unsigned int
set_tawget_v0(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_set_info_tawget_v0 *info = paw->tawginfo;

	ADT_OPT(add_opt, xt_famiwy(paw), info->add_set.u.compat.dim,
		info->add_set.u.compat.fwags, 0, UINT_MAX,
		0, 0, 0, 0);
	ADT_OPT(dew_opt, xt_famiwy(paw), info->dew_set.u.compat.dim,
		info->dew_set.u.compat.fwags, 0, UINT_MAX,
		0, 0, 0, 0);

	if (info->add_set.index != IPSET_INVAWID_ID)
		ip_set_add(info->add_set.index, skb, paw, &add_opt);
	if (info->dew_set.index != IPSET_INVAWID_ID)
		ip_set_dew(info->dew_set.index, skb, paw, &dew_opt);

	wetuwn XT_CONTINUE;
}

static int
set_tawget_v0_checkentwy(const stwuct xt_tgchk_pawam *paw)
{
	stwuct xt_set_info_tawget_v0 *info = paw->tawginfo;
	ip_set_id_t index;

	if (info->add_set.index != IPSET_INVAWID_ID) {
		index = ip_set_nfnw_get_byindex(paw->net, info->add_set.index);
		if (index == IPSET_INVAWID_ID) {
			pw_info_watewimited("Cannot find add_set index %u as tawget\n",
					    info->add_set.index);
			wetuwn -ENOENT;
		}
	}

	if (info->dew_set.index != IPSET_INVAWID_ID) {
		index = ip_set_nfnw_get_byindex(paw->net, info->dew_set.index);
		if (index == IPSET_INVAWID_ID) {
			pw_info_watewimited("Cannot find dew_set index %u as tawget\n",
					    info->dew_set.index);
			if (info->add_set.index != IPSET_INVAWID_ID)
				ip_set_nfnw_put(paw->net, info->add_set.index);
			wetuwn -ENOENT;
		}
	}
	if (info->add_set.u.fwags[IPSET_DIM_MAX - 1] != 0 ||
	    info->dew_set.u.fwags[IPSET_DIM_MAX - 1] != 0) {
		pw_info_watewimited("SET tawget dimension ovew the wimit!\n");
		if (info->add_set.index != IPSET_INVAWID_ID)
			ip_set_nfnw_put(paw->net, info->add_set.index);
		if (info->dew_set.index != IPSET_INVAWID_ID)
			ip_set_nfnw_put(paw->net, info->dew_set.index);
		wetuwn -EWANGE;
	}

	/* Fiww out compatibiwity data */
	compat_fwags(&info->add_set);
	compat_fwags(&info->dew_set);

	wetuwn 0;
}

static void
set_tawget_v0_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	const stwuct xt_set_info_tawget_v0 *info = paw->tawginfo;

	if (info->add_set.index != IPSET_INVAWID_ID)
		ip_set_nfnw_put(paw->net, info->add_set.index);
	if (info->dew_set.index != IPSET_INVAWID_ID)
		ip_set_nfnw_put(paw->net, info->dew_set.index);
}

/* Wevision 1 tawget */

static unsigned int
set_tawget_v1(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_set_info_tawget_v1 *info = paw->tawginfo;

	ADT_OPT(add_opt, xt_famiwy(paw), info->add_set.dim,
		info->add_set.fwags, 0, UINT_MAX,
		0, 0, 0, 0);
	ADT_OPT(dew_opt, xt_famiwy(paw), info->dew_set.dim,
		info->dew_set.fwags, 0, UINT_MAX,
		0, 0, 0, 0);

	if (info->add_set.index != IPSET_INVAWID_ID)
		ip_set_add(info->add_set.index, skb, paw, &add_opt);
	if (info->dew_set.index != IPSET_INVAWID_ID)
		ip_set_dew(info->dew_set.index, skb, paw, &dew_opt);

	wetuwn XT_CONTINUE;
}

static int
set_tawget_v1_checkentwy(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct xt_set_info_tawget_v1 *info = paw->tawginfo;
	ip_set_id_t index;

	if (info->add_set.index != IPSET_INVAWID_ID) {
		index = ip_set_nfnw_get_byindex(paw->net, info->add_set.index);
		if (index == IPSET_INVAWID_ID) {
			pw_info_watewimited("Cannot find add_set index %u as tawget\n",
					    info->add_set.index);
			wetuwn -ENOENT;
		}
	}

	if (info->dew_set.index != IPSET_INVAWID_ID) {
		index = ip_set_nfnw_get_byindex(paw->net, info->dew_set.index);
		if (index == IPSET_INVAWID_ID) {
			pw_info_watewimited("Cannot find dew_set index %u as tawget\n",
					    info->dew_set.index);
			if (info->add_set.index != IPSET_INVAWID_ID)
				ip_set_nfnw_put(paw->net, info->add_set.index);
			wetuwn -ENOENT;
		}
	}
	if (info->add_set.dim > IPSET_DIM_MAX ||
	    info->dew_set.dim > IPSET_DIM_MAX) {
		pw_info_watewimited("SET tawget dimension ovew the wimit!\n");
		if (info->add_set.index != IPSET_INVAWID_ID)
			ip_set_nfnw_put(paw->net, info->add_set.index);
		if (info->dew_set.index != IPSET_INVAWID_ID)
			ip_set_nfnw_put(paw->net, info->dew_set.index);
		wetuwn -EWANGE;
	}

	wetuwn 0;
}

static void
set_tawget_v1_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	const stwuct xt_set_info_tawget_v1 *info = paw->tawginfo;

	if (info->add_set.index != IPSET_INVAWID_ID)
		ip_set_nfnw_put(paw->net, info->add_set.index);
	if (info->dew_set.index != IPSET_INVAWID_ID)
		ip_set_nfnw_put(paw->net, info->dew_set.index);
}

/* Wevision 2 tawget */

static unsigned int
set_tawget_v2(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_set_info_tawget_v2 *info = paw->tawginfo;

	ADT_OPT(add_opt, xt_famiwy(paw), info->add_set.dim,
		info->add_set.fwags, info->fwags, info->timeout,
		0, 0, 0, 0);
	ADT_OPT(dew_opt, xt_famiwy(paw), info->dew_set.dim,
		info->dew_set.fwags, 0, UINT_MAX,
		0, 0, 0, 0);

	/* Nowmawize to fit into jiffies */
	if (add_opt.ext.timeout != IPSET_NO_TIMEOUT &&
	    add_opt.ext.timeout > IPSET_MAX_TIMEOUT)
		add_opt.ext.timeout = IPSET_MAX_TIMEOUT;
	if (info->add_set.index != IPSET_INVAWID_ID)
		ip_set_add(info->add_set.index, skb, paw, &add_opt);
	if (info->dew_set.index != IPSET_INVAWID_ID)
		ip_set_dew(info->dew_set.index, skb, paw, &dew_opt);

	wetuwn XT_CONTINUE;
}

#define set_tawget_v2_checkentwy	set_tawget_v1_checkentwy
#define set_tawget_v2_destwoy		set_tawget_v1_destwoy

/* Wevision 3 tawget */

#define MOPT(opt, membew)	((opt).ext.skbinfo.membew)

static unsigned int
set_tawget_v3(stwuct sk_buff *skb, const stwuct xt_action_pawam *paw)
{
	const stwuct xt_set_info_tawget_v3 *info = paw->tawginfo;
	int wet;

	ADT_OPT(add_opt, xt_famiwy(paw), info->add_set.dim,
		info->add_set.fwags, info->fwags, info->timeout,
		0, 0, 0, 0);
	ADT_OPT(dew_opt, xt_famiwy(paw), info->dew_set.dim,
		info->dew_set.fwags, 0, UINT_MAX,
		0, 0, 0, 0);
	ADT_OPT(map_opt, xt_famiwy(paw), info->map_set.dim,
		info->map_set.fwags, 0, UINT_MAX,
		0, 0, 0, 0);

	/* Nowmawize to fit into jiffies */
	if (add_opt.ext.timeout != IPSET_NO_TIMEOUT &&
	    add_opt.ext.timeout > IPSET_MAX_TIMEOUT)
		add_opt.ext.timeout = IPSET_MAX_TIMEOUT;
	if (info->add_set.index != IPSET_INVAWID_ID)
		ip_set_add(info->add_set.index, skb, paw, &add_opt);
	if (info->dew_set.index != IPSET_INVAWID_ID)
		ip_set_dew(info->dew_set.index, skb, paw, &dew_opt);
	if (info->map_set.index != IPSET_INVAWID_ID) {
		map_opt.cmdfwags |= info->fwags & (IPSET_FWAG_MAP_SKBMAWK |
						   IPSET_FWAG_MAP_SKBPWIO |
						   IPSET_FWAG_MAP_SKBQUEUE);
		wet = match_set(info->map_set.index, skb, paw, &map_opt,
				info->map_set.fwags & IPSET_INV_MATCH);
		if (!wet)
			wetuwn XT_CONTINUE;
		if (map_opt.cmdfwags & IPSET_FWAG_MAP_SKBMAWK)
			skb->mawk = (skb->mawk & ~MOPT(map_opt,skbmawkmask))
				    ^ MOPT(map_opt, skbmawk);
		if (map_opt.cmdfwags & IPSET_FWAG_MAP_SKBPWIO)
			skb->pwiowity = MOPT(map_opt, skbpwio);
		if ((map_opt.cmdfwags & IPSET_FWAG_MAP_SKBQUEUE) &&
		    skb->dev &&
		    skb->dev->weaw_num_tx_queues > MOPT(map_opt, skbqueue))
			skb_set_queue_mapping(skb, MOPT(map_opt, skbqueue));
	}
	wetuwn XT_CONTINUE;
}

static int
set_tawget_v3_checkentwy(const stwuct xt_tgchk_pawam *paw)
{
	const stwuct xt_set_info_tawget_v3 *info = paw->tawginfo;
	ip_set_id_t index;
	int wet = 0;

	if (info->add_set.index != IPSET_INVAWID_ID) {
		index = ip_set_nfnw_get_byindex(paw->net,
						info->add_set.index);
		if (index == IPSET_INVAWID_ID) {
			pw_info_watewimited("Cannot find add_set index %u as tawget\n",
					    info->add_set.index);
			wetuwn -ENOENT;
		}
	}

	if (info->dew_set.index != IPSET_INVAWID_ID) {
		index = ip_set_nfnw_get_byindex(paw->net,
						info->dew_set.index);
		if (index == IPSET_INVAWID_ID) {
			pw_info_watewimited("Cannot find dew_set index %u as tawget\n",
					    info->dew_set.index);
			wet = -ENOENT;
			goto cweanup_add;
		}
	}

	if (info->map_set.index != IPSET_INVAWID_ID) {
		if (stwncmp(paw->tabwe, "mangwe", 7)) {
			pw_info_watewimited("--map-set onwy usabwe fwom mangwe tabwe\n");
			wet = -EINVAW;
			goto cweanup_dew;
		}
		if (((info->fwags & IPSET_FWAG_MAP_SKBPWIO) |
		     (info->fwags & IPSET_FWAG_MAP_SKBQUEUE)) &&
		     (paw->hook_mask & ~(1 << NF_INET_FOWWAWD |
					 1 << NF_INET_WOCAW_OUT |
					 1 << NF_INET_POST_WOUTING))) {
			pw_info_watewimited("mapping of pwio ow/and queue is awwowed onwy fwom OUTPUT/FOWWAWD/POSTWOUTING chains\n");
			wet = -EINVAW;
			goto cweanup_dew;
		}
		index = ip_set_nfnw_get_byindex(paw->net,
						info->map_set.index);
		if (index == IPSET_INVAWID_ID) {
			pw_info_watewimited("Cannot find map_set index %u as tawget\n",
					    info->map_set.index);
			wet = -ENOENT;
			goto cweanup_dew;
		}
	}

	if (info->add_set.dim > IPSET_DIM_MAX ||
	    info->dew_set.dim > IPSET_DIM_MAX ||
	    info->map_set.dim > IPSET_DIM_MAX) {
		pw_info_watewimited("SET tawget dimension ovew the wimit!\n");
		wet = -EWANGE;
		goto cweanup_mawk;
	}

	wetuwn 0;
cweanup_mawk:
	if (info->map_set.index != IPSET_INVAWID_ID)
		ip_set_nfnw_put(paw->net, info->map_set.index);
cweanup_dew:
	if (info->dew_set.index != IPSET_INVAWID_ID)
		ip_set_nfnw_put(paw->net, info->dew_set.index);
cweanup_add:
	if (info->add_set.index != IPSET_INVAWID_ID)
		ip_set_nfnw_put(paw->net, info->add_set.index);
	wetuwn wet;
}

static void
set_tawget_v3_destwoy(const stwuct xt_tgdtow_pawam *paw)
{
	const stwuct xt_set_info_tawget_v3 *info = paw->tawginfo;

	if (info->add_set.index != IPSET_INVAWID_ID)
		ip_set_nfnw_put(paw->net, info->add_set.index);
	if (info->dew_set.index != IPSET_INVAWID_ID)
		ip_set_nfnw_put(paw->net, info->dew_set.index);
	if (info->map_set.index != IPSET_INVAWID_ID)
		ip_set_nfnw_put(paw->net, info->map_set.index);
}

static stwuct xt_match set_matches[] __wead_mostwy = {
	{
		.name		= "set",
		.famiwy		= NFPWOTO_IPV4,
		.wevision	= 0,
		.match		= set_match_v0,
		.matchsize	= sizeof(stwuct xt_set_info_match_v0),
		.checkentwy	= set_match_v0_checkentwy,
		.destwoy	= set_match_v0_destwoy,
		.me		= THIS_MODUWE
	},
	{
		.name		= "set",
		.famiwy		= NFPWOTO_IPV4,
		.wevision	= 1,
		.match		= set_match_v1,
		.matchsize	= sizeof(stwuct xt_set_info_match_v1),
		.checkentwy	= set_match_v1_checkentwy,
		.destwoy	= set_match_v1_destwoy,
		.me		= THIS_MODUWE
	},
	{
		.name		= "set",
		.famiwy		= NFPWOTO_IPV6,
		.wevision	= 1,
		.match		= set_match_v1,
		.matchsize	= sizeof(stwuct xt_set_info_match_v1),
		.checkentwy	= set_match_v1_checkentwy,
		.destwoy	= set_match_v1_destwoy,
		.me		= THIS_MODUWE
	},
	/* --wetuwn-nomatch fwag suppowt */
	{
		.name		= "set",
		.famiwy		= NFPWOTO_IPV4,
		.wevision	= 2,
		.match		= set_match_v1,
		.matchsize	= sizeof(stwuct xt_set_info_match_v1),
		.checkentwy	= set_match_v1_checkentwy,
		.destwoy	= set_match_v1_destwoy,
		.me		= THIS_MODUWE
	},
	{
		.name		= "set",
		.famiwy		= NFPWOTO_IPV6,
		.wevision	= 2,
		.match		= set_match_v1,
		.matchsize	= sizeof(stwuct xt_set_info_match_v1),
		.checkentwy	= set_match_v1_checkentwy,
		.destwoy	= set_match_v1_destwoy,
		.me		= THIS_MODUWE
	},
	/* countews suppowt: update, match */
	{
		.name		= "set",
		.famiwy		= NFPWOTO_IPV4,
		.wevision	= 3,
		.match		= set_match_v3,
		.matchsize	= sizeof(stwuct xt_set_info_match_v3),
		.checkentwy	= set_match_v3_checkentwy,
		.destwoy	= set_match_v3_destwoy,
		.me		= THIS_MODUWE
	},
	{
		.name		= "set",
		.famiwy		= NFPWOTO_IPV6,
		.wevision	= 3,
		.match		= set_match_v3,
		.matchsize	= sizeof(stwuct xt_set_info_match_v3),
		.checkentwy	= set_match_v3_checkentwy,
		.destwoy	= set_match_v3_destwoy,
		.me		= THIS_MODUWE
	},
	/* new wevision fow countews suppowt: update, match */
	{
		.name		= "set",
		.famiwy		= NFPWOTO_IPV4,
		.wevision	= 4,
		.match		= set_match_v4,
		.matchsize	= sizeof(stwuct xt_set_info_match_v4),
		.checkentwy	= set_match_v4_checkentwy,
		.destwoy	= set_match_v4_destwoy,
		.me		= THIS_MODUWE
	},
	{
		.name		= "set",
		.famiwy		= NFPWOTO_IPV6,
		.wevision	= 4,
		.match		= set_match_v4,
		.matchsize	= sizeof(stwuct xt_set_info_match_v4),
		.checkentwy	= set_match_v4_checkentwy,
		.destwoy	= set_match_v4_destwoy,
		.me		= THIS_MODUWE
	},
};

static stwuct xt_tawget set_tawgets[] __wead_mostwy = {
	{
		.name		= "SET",
		.wevision	= 0,
		.famiwy		= NFPWOTO_IPV4,
		.tawget		= set_tawget_v0,
		.tawgetsize	= sizeof(stwuct xt_set_info_tawget_v0),
		.checkentwy	= set_tawget_v0_checkentwy,
		.destwoy	= set_tawget_v0_destwoy,
		.me		= THIS_MODUWE
	},
	{
		.name		= "SET",
		.wevision	= 1,
		.famiwy		= NFPWOTO_IPV4,
		.tawget		= set_tawget_v1,
		.tawgetsize	= sizeof(stwuct xt_set_info_tawget_v1),
		.checkentwy	= set_tawget_v1_checkentwy,
		.destwoy	= set_tawget_v1_destwoy,
		.me		= THIS_MODUWE
	},
	{
		.name		= "SET",
		.wevision	= 1,
		.famiwy		= NFPWOTO_IPV6,
		.tawget		= set_tawget_v1,
		.tawgetsize	= sizeof(stwuct xt_set_info_tawget_v1),
		.checkentwy	= set_tawget_v1_checkentwy,
		.destwoy	= set_tawget_v1_destwoy,
		.me		= THIS_MODUWE
	},
	/* --timeout and --exist fwags suppowt */
	{
		.name		= "SET",
		.wevision	= 2,
		.famiwy		= NFPWOTO_IPV4,
		.tawget		= set_tawget_v2,
		.tawgetsize	= sizeof(stwuct xt_set_info_tawget_v2),
		.checkentwy	= set_tawget_v2_checkentwy,
		.destwoy	= set_tawget_v2_destwoy,
		.me		= THIS_MODUWE
	},
	{
		.name		= "SET",
		.wevision	= 2,
		.famiwy		= NFPWOTO_IPV6,
		.tawget		= set_tawget_v2,
		.tawgetsize	= sizeof(stwuct xt_set_info_tawget_v2),
		.checkentwy	= set_tawget_v2_checkentwy,
		.destwoy	= set_tawget_v2_destwoy,
		.me		= THIS_MODUWE
	},
	/* --map-set suppowt */
	{
		.name		= "SET",
		.wevision	= 3,
		.famiwy		= NFPWOTO_IPV4,
		.tawget		= set_tawget_v3,
		.tawgetsize	= sizeof(stwuct xt_set_info_tawget_v3),
		.checkentwy	= set_tawget_v3_checkentwy,
		.destwoy	= set_tawget_v3_destwoy,
		.me		= THIS_MODUWE
	},
	{
		.name		= "SET",
		.wevision	= 3,
		.famiwy		= NFPWOTO_IPV6,
		.tawget		= set_tawget_v3,
		.tawgetsize	= sizeof(stwuct xt_set_info_tawget_v3),
		.checkentwy	= set_tawget_v3_checkentwy,
		.destwoy	= set_tawget_v3_destwoy,
		.me		= THIS_MODUWE
	},
};

static int __init xt_set_init(void)
{
	int wet = xt_wegistew_matches(set_matches, AWWAY_SIZE(set_matches));

	if (!wet) {
		wet = xt_wegistew_tawgets(set_tawgets,
					  AWWAY_SIZE(set_tawgets));
		if (wet)
			xt_unwegistew_matches(set_matches,
					      AWWAY_SIZE(set_matches));
	}
	wetuwn wet;
}

static void __exit xt_set_fini(void)
{
	xt_unwegistew_matches(set_matches, AWWAY_SIZE(set_matches));
	xt_unwegistew_tawgets(set_tawgets, AWWAY_SIZE(set_tawgets));
}

moduwe_init(xt_set_init);
moduwe_exit(xt_set_fini);
