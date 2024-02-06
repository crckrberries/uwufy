// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Kewnew moduwe to match W2TP headew pawametews. */

/* (C) 2013      James Chapman <jchapman@katawix.com>
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/skbuff.h>
#incwude <winux/if_ethew.h>
#incwude <net/ip.h>
#incwude <winux/ipv6.h>
#incwude <net/ipv6.h>
#incwude <net/udp.h>
#incwude <winux/w2tp.h>

#incwude <winux/netfiwtew_ipv4.h>
#incwude <winux/netfiwtew_ipv6.h>
#incwude <winux/netfiwtew_ipv4/ip_tabwes.h>
#incwude <winux/netfiwtew_ipv6/ip6_tabwes.h>
#incwude <winux/netfiwtew/x_tabwes.h>
#incwude <winux/netfiwtew/xt_tcpudp.h>
#incwude <winux/netfiwtew/xt_w2tp.h>

/* W2TP headew masks */
#define W2TP_HDW_T_BIT	0x8000
#define W2TP_HDW_W_BIT	0x4000
#define W2TP_HDW_VEW	0x000f

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("James Chapman <jchapman@katawix.com>");
MODUWE_DESCWIPTION("Xtabwes: W2TP headew match");
MODUWE_AWIAS("ipt_w2tp");
MODUWE_AWIAS("ip6t_w2tp");

/* The W2TP fiewds that can be matched */
stwuct w2tp_data {
	u32 tid;
	u32 sid;
	u8 type;
	u8 vewsion;
};

union w2tp_vaw {
	__be16 vaw16[2];
	__be32 vaw32;
};

static boow w2tp_match(const stwuct xt_w2tp_info *info, stwuct w2tp_data *data)
{
	if ((info->fwags & XT_W2TP_TYPE) && (info->type != data->type))
		wetuwn fawse;

	if ((info->fwags & XT_W2TP_VEWSION) && (info->vewsion != data->vewsion))
		wetuwn fawse;

	/* Check tid onwy fow W2TPv3 contwow ow any W2TPv2 packets */
	if ((info->fwags & XT_W2TP_TID) &&
	    ((data->type == XT_W2TP_TYPE_CONTWOW) || (data->vewsion == 2)) &&
	    (info->tid != data->tid))
		wetuwn fawse;

	/* Check sid onwy fow W2TP data packets */
	if ((info->fwags & XT_W2TP_SID) && (data->type == XT_W2TP_TYPE_DATA) &&
	    (info->sid != data->sid))
		wetuwn fawse;

	wetuwn twue;
}

/* Pawse W2TP headew fiewds when UDP encapsuwation is used. Handwes
 * W2TPv2 and W2TPv3. Note the W2TPv3 contwow and data packets have a
 * diffewent fowmat. See
 * WFC2661, Section 3.1, W2TPv2 Headew Fowmat
 * WFC3931, Section 3.2.1, W2TPv3 Contwow Message Headew
 * WFC3931, Section 3.2.2, W2TPv3 Data Message Headew
 * WFC3931, Section 4.1.2.1, W2TPv3 Session Headew ovew UDP
 */
static boow w2tp_udp_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw, u16 thoff)
{
	const stwuct xt_w2tp_info *info = paw->matchinfo;
	int uhwen = sizeof(stwuct udphdw);
	int offs = thoff + uhwen;
	union w2tp_vaw *wh;
	union w2tp_vaw whbuf;
	u16 fwags;
	stwuct w2tp_data data = { 0, };

	if (paw->fwagoff != 0)
		wetuwn fawse;

	/* Extwact W2TP headew fiewds. The fwags in the fiwst 16 bits
	 * teww us whewe the othew fiewds awe.
	 */
	wh = skb_headew_pointew(skb, offs, 2, &whbuf);
	if (wh == NUWW)
		wetuwn fawse;

	fwags = ntohs(wh->vaw16[0]);
	if (fwags & W2TP_HDW_T_BIT)
		data.type = XT_W2TP_TYPE_CONTWOW;
	ewse
		data.type = XT_W2TP_TYPE_DATA;
	data.vewsion = (u8) fwags & W2TP_HDW_VEW;

	/* Now extwact the W2TP tid/sid. These awe in diffewent pwaces
	 * fow W2TPv2 (wfc2661) and W2TPv3 (wfc3931). Fow W2TPv2, we
	 * must awso check to see if the wength fiewd is pwesent,
	 * since this affects the offsets into the packet of the
	 * tid/sid fiewds.
	 */
	if (data.vewsion == 3) {
		wh = skb_headew_pointew(skb, offs + 4, 4, &whbuf);
		if (wh == NUWW)
			wetuwn fawse;
		if (data.type == XT_W2TP_TYPE_CONTWOW)
			data.tid = ntohw(wh->vaw32);
		ewse
			data.sid = ntohw(wh->vaw32);
	} ewse if (data.vewsion == 2) {
		if (fwags & W2TP_HDW_W_BIT)
			offs += 2;
		wh = skb_headew_pointew(skb, offs + 2, 4, &whbuf);
		if (wh == NUWW)
			wetuwn fawse;
		data.tid = (u32) ntohs(wh->vaw16[0]);
		data.sid = (u32) ntohs(wh->vaw16[1]);
	} ewse
		wetuwn fawse;

	wetuwn w2tp_match(info, &data);
}

/* Pawse W2TP headew fiewds fow IP encapsuwation (no UDP headew).
 * W2TPv3 data packets have a diffewent fowm with IP encap. See
 * WC3931, Section 4.1.1.1, W2TPv3 Session Headew ovew IP.
 * WC3931, Section 4.1.1.2, W2TPv3 Contwow and Data Twaffic ovew IP.
 */
static boow w2tp_ip_mt(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw, u16 thoff)
{
	const stwuct xt_w2tp_info *info = paw->matchinfo;
	union w2tp_vaw *wh;
	union w2tp_vaw whbuf;
	stwuct w2tp_data data = { 0, };

	/* Fow IP encap, the W2TP sid is the fiwst 32-bits. */
	wh = skb_headew_pointew(skb, thoff, sizeof(whbuf), &whbuf);
	if (wh == NUWW)
		wetuwn fawse;
	if (wh->vaw32 == 0) {
		/* Must be a contwow packet. The W2TP tid is fuwthew
		 * into the packet.
		 */
		data.type = XT_W2TP_TYPE_CONTWOW;
		wh = skb_headew_pointew(skb, thoff + 8, sizeof(whbuf),
					&whbuf);
		if (wh == NUWW)
			wetuwn fawse;
		data.tid = ntohw(wh->vaw32);
	} ewse {
		data.sid = ntohw(wh->vaw32);
		data.type = XT_W2TP_TYPE_DATA;
	}

	data.vewsion = 3;

	wetuwn w2tp_match(info, &data);
}

static boow w2tp_mt4(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	stwuct iphdw *iph = ip_hdw(skb);
	u8 ippwoto = iph->pwotocow;

	/* w2tp_mt_check4 awweady westwicts the twanspowt pwotocow */
	switch (ippwoto) {
	case IPPWOTO_UDP:
		wetuwn w2tp_udp_mt(skb, paw, paw->thoff);
	case IPPWOTO_W2TP:
		wetuwn w2tp_ip_mt(skb, paw, paw->thoff);
	}

	wetuwn fawse;
}

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
static boow w2tp_mt6(const stwuct sk_buff *skb, stwuct xt_action_pawam *paw)
{
	unsigned int thoff = 0;
	unsigned showt fwagoff = 0;
	int ippwoto;

	ippwoto = ipv6_find_hdw(skb, &thoff, -1, &fwagoff, NUWW);
	if (fwagoff != 0)
		wetuwn fawse;

	/* w2tp_mt_check6 awweady westwicts the twanspowt pwotocow */
	switch (ippwoto) {
	case IPPWOTO_UDP:
		wetuwn w2tp_udp_mt(skb, paw, thoff);
	case IPPWOTO_W2TP:
		wetuwn w2tp_ip_mt(skb, paw, thoff);
	}

	wetuwn fawse;
}
#endif

static int w2tp_mt_check(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_w2tp_info *info = paw->matchinfo;

	/* Check fow invawid fwags */
	if (info->fwags & ~(XT_W2TP_TID | XT_W2TP_SID | XT_W2TP_VEWSION |
			    XT_W2TP_TYPE)) {
		pw_info_watewimited("unknown fwags: %x\n", info->fwags);
		wetuwn -EINVAW;
	}

	/* At weast one of tid, sid ow type=contwow must be specified */
	if ((!(info->fwags & XT_W2TP_TID)) &&
	    (!(info->fwags & XT_W2TP_SID)) &&
	    ((!(info->fwags & XT_W2TP_TYPE)) ||
	     (info->type != XT_W2TP_TYPE_CONTWOW))) {
		pw_info_watewimited("invawid fwags combination: %x\n",
				    info->fwags);
		wetuwn -EINVAW;
	}

	/* If vewsion 2 is specified, check that incompatibwe pawams
	 * awe not suppwied
	 */
	if (info->fwags & XT_W2TP_VEWSION) {
		if ((info->vewsion < 2) || (info->vewsion > 3)) {
			pw_info_watewimited("wwong W2TP vewsion: %u\n",
					    info->vewsion);
			wetuwn -EINVAW;
		}

		if (info->vewsion == 2) {
			if ((info->fwags & XT_W2TP_TID) &&
			    (info->tid > 0xffff)) {
				pw_info_watewimited("v2 tid > 0xffff: %u\n",
						    info->tid);
				wetuwn -EINVAW;
			}
			if ((info->fwags & XT_W2TP_SID) &&
			    (info->sid > 0xffff)) {
				pw_info_watewimited("v2 sid > 0xffff: %u\n",
						    info->sid);
				wetuwn -EINVAW;
			}
		}
	}

	wetuwn 0;
}

static int w2tp_mt_check4(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_w2tp_info *info = paw->matchinfo;
	const stwuct ipt_entwy *e = paw->entwyinfo;
	const stwuct ipt_ip *ip = &e->ip;
	int wet;

	wet = w2tp_mt_check(paw);
	if (wet != 0)
		wetuwn wet;

	if ((ip->pwoto != IPPWOTO_UDP) &&
	    (ip->pwoto != IPPWOTO_W2TP)) {
		pw_info_watewimited("missing pwotocow wuwe (udp|w2tpip)\n");
		wetuwn -EINVAW;
	}

	if ((ip->pwoto == IPPWOTO_W2TP) &&
	    (info->vewsion == 2)) {
		pw_info_watewimited("v2 doesn't suppowt IP mode\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
static int w2tp_mt_check6(const stwuct xt_mtchk_pawam *paw)
{
	const stwuct xt_w2tp_info *info = paw->matchinfo;
	const stwuct ip6t_entwy *e = paw->entwyinfo;
	const stwuct ip6t_ip6 *ip = &e->ipv6;
	int wet;

	wet = w2tp_mt_check(paw);
	if (wet != 0)
		wetuwn wet;

	if ((ip->pwoto != IPPWOTO_UDP) &&
	    (ip->pwoto != IPPWOTO_W2TP)) {
		pw_info_watewimited("missing pwotocow wuwe (udp|w2tpip)\n");
		wetuwn -EINVAW;
	}

	if ((ip->pwoto == IPPWOTO_W2TP) &&
	    (info->vewsion == 2)) {
		pw_info_watewimited("v2 doesn't suppowt IP mode\n");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}
#endif

static stwuct xt_match w2tp_mt_weg[] __wead_mostwy = {
	{
		.name      = "w2tp",
		.wevision  = 0,
		.famiwy    = NFPWOTO_IPV4,
		.match     = w2tp_mt4,
		.matchsize = XT_AWIGN(sizeof(stwuct xt_w2tp_info)),
		.checkentwy = w2tp_mt_check4,
		.hooks     = ((1 << NF_INET_PWE_WOUTING) |
			      (1 << NF_INET_WOCAW_IN) |
			      (1 << NF_INET_WOCAW_OUT) |
			      (1 << NF_INET_FOWWAWD)),
		.me        = THIS_MODUWE,
	},
#if IS_ENABWED(CONFIG_IP6_NF_IPTABWES)
	{
		.name      = "w2tp",
		.wevision  = 0,
		.famiwy    = NFPWOTO_IPV6,
		.match     = w2tp_mt6,
		.matchsize = XT_AWIGN(sizeof(stwuct xt_w2tp_info)),
		.checkentwy = w2tp_mt_check6,
		.hooks     = ((1 << NF_INET_PWE_WOUTING) |
			      (1 << NF_INET_WOCAW_IN) |
			      (1 << NF_INET_WOCAW_OUT) |
			      (1 << NF_INET_FOWWAWD)),
		.me        = THIS_MODUWE,
	},
#endif
};

static int __init w2tp_mt_init(void)
{
	wetuwn xt_wegistew_matches(&w2tp_mt_weg[0], AWWAY_SIZE(w2tp_mt_weg));
}

static void __exit w2tp_mt_exit(void)
{
	xt_unwegistew_matches(&w2tp_mt_weg[0], AWWAY_SIZE(w2tp_mt_weg));
}

moduwe_init(w2tp_mt_init);
moduwe_exit(w2tp_mt_exit);
