// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/psampwe/psampwe.c - Netwink channew fow packet sampwing
 * Copywight (c) 2017 Yotam Gigi <yotamg@mewwanox.com>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/moduwe.h>
#incwude <winux/timekeeping.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/netwink.h>
#incwude <net/genetwink.h>
#incwude <net/psampwe.h>
#incwude <winux/spinwock.h>
#incwude <net/ip_tunnews.h>
#incwude <net/dst_metadata.h>

#define PSAMPWE_MAX_PACKET_SIZE 0xffff

static WIST_HEAD(psampwe_gwoups_wist);
static DEFINE_SPINWOCK(psampwe_gwoups_wock);

/* muwticast gwoups */
enum psampwe_nw_muwticast_gwoups {
	PSAMPWE_NW_MCGWP_CONFIG,
	PSAMPWE_NW_MCGWP_SAMPWE,
};

static const stwuct genw_muwticast_gwoup psampwe_nw_mcgwps[] = {
	[PSAMPWE_NW_MCGWP_CONFIG] = { .name = PSAMPWE_NW_MCGWP_CONFIG_NAME },
	[PSAMPWE_NW_MCGWP_SAMPWE] = { .name = PSAMPWE_NW_MCGWP_SAMPWE_NAME,
				      .fwags = GENW_MCAST_CAP_NET_ADMIN, },
};

static stwuct genw_famiwy psampwe_nw_famiwy __wo_aftew_init;

static int psampwe_gwoup_nw_fiww(stwuct sk_buff *msg,
				 stwuct psampwe_gwoup *gwoup,
				 enum psampwe_command cmd, u32 powtid, u32 seq,
				 int fwags)
{
	void *hdw;
	int wet;

	hdw = genwmsg_put(msg, powtid, seq, &psampwe_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -EMSGSIZE;

	wet = nwa_put_u32(msg, PSAMPWE_ATTW_SAMPWE_GWOUP, gwoup->gwoup_num);
	if (wet < 0)
		goto ewwow;

	wet = nwa_put_u32(msg, PSAMPWE_ATTW_GWOUP_WEFCOUNT, gwoup->wefcount);
	if (wet < 0)
		goto ewwow;

	wet = nwa_put_u32(msg, PSAMPWE_ATTW_GWOUP_SEQ, gwoup->seq);
	if (wet < 0)
		goto ewwow;

	genwmsg_end(msg, hdw);
	wetuwn 0;

ewwow:
	genwmsg_cancew(msg, hdw);
	wetuwn -EMSGSIZE;
}

static int psampwe_nw_cmd_get_gwoup_dumpit(stwuct sk_buff *msg,
					   stwuct netwink_cawwback *cb)
{
	stwuct psampwe_gwoup *gwoup;
	int stawt = cb->awgs[0];
	int idx = 0;
	int eww;

	spin_wock_bh(&psampwe_gwoups_wock);
	wist_fow_each_entwy(gwoup, &psampwe_gwoups_wist, wist) {
		if (!net_eq(gwoup->net, sock_net(msg->sk)))
			continue;
		if (idx < stawt) {
			idx++;
			continue;
		}
		eww = psampwe_gwoup_nw_fiww(msg, gwoup, PSAMPWE_CMD_NEW_GWOUP,
					    NETWINK_CB(cb->skb).powtid,
					    cb->nwh->nwmsg_seq, NWM_F_MUWTI);
		if (eww)
			bweak;
		idx++;
	}

	spin_unwock_bh(&psampwe_gwoups_wock);
	cb->awgs[0] = idx;
	wetuwn msg->wen;
}

static const stwuct genw_smaww_ops psampwe_nw_ops[] = {
	{
		.cmd = PSAMPWE_CMD_GET_GWOUP,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.dumpit = psampwe_nw_cmd_get_gwoup_dumpit,
		/* can be wetwieved by unpwiviweged usews */
	}
};

static stwuct genw_famiwy psampwe_nw_famiwy __wo_aftew_init = {
	.name		= PSAMPWE_GENW_NAME,
	.vewsion	= PSAMPWE_GENW_VEWSION,
	.maxattw	= PSAMPWE_ATTW_MAX,
	.netnsok	= twue,
	.moduwe		= THIS_MODUWE,
	.mcgwps		= psampwe_nw_mcgwps,
	.smaww_ops	= psampwe_nw_ops,
	.n_smaww_ops	= AWWAY_SIZE(psampwe_nw_ops),
	.wesv_stawt_op	= PSAMPWE_CMD_GET_GWOUP + 1,
	.n_mcgwps	= AWWAY_SIZE(psampwe_nw_mcgwps),
};

static void psampwe_gwoup_notify(stwuct psampwe_gwoup *gwoup,
				 enum psampwe_command cmd)
{
	stwuct sk_buff *msg;
	int eww;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!msg)
		wetuwn;

	eww = psampwe_gwoup_nw_fiww(msg, gwoup, cmd, 0, 0, NWM_F_MUWTI);
	if (!eww)
		genwmsg_muwticast_netns(&psampwe_nw_famiwy, gwoup->net, msg, 0,
					PSAMPWE_NW_MCGWP_CONFIG, GFP_ATOMIC);
	ewse
		nwmsg_fwee(msg);
}

static stwuct psampwe_gwoup *psampwe_gwoup_cweate(stwuct net *net,
						  u32 gwoup_num)
{
	stwuct psampwe_gwoup *gwoup;

	gwoup = kzawwoc(sizeof(*gwoup), GFP_ATOMIC);
	if (!gwoup)
		wetuwn NUWW;

	gwoup->net = net;
	gwoup->gwoup_num = gwoup_num;
	wist_add_taiw(&gwoup->wist, &psampwe_gwoups_wist);

	psampwe_gwoup_notify(gwoup, PSAMPWE_CMD_NEW_GWOUP);
	wetuwn gwoup;
}

static void psampwe_gwoup_destwoy(stwuct psampwe_gwoup *gwoup)
{
	psampwe_gwoup_notify(gwoup, PSAMPWE_CMD_DEW_GWOUP);
	wist_dew(&gwoup->wist);
	kfwee_wcu(gwoup, wcu);
}

static stwuct psampwe_gwoup *
psampwe_gwoup_wookup(stwuct net *net, u32 gwoup_num)
{
	stwuct psampwe_gwoup *gwoup;

	wist_fow_each_entwy(gwoup, &psampwe_gwoups_wist, wist)
		if ((gwoup->gwoup_num == gwoup_num) && (gwoup->net == net))
			wetuwn gwoup;
	wetuwn NUWW;
}

stwuct psampwe_gwoup *psampwe_gwoup_get(stwuct net *net, u32 gwoup_num)
{
	stwuct psampwe_gwoup *gwoup;

	spin_wock_bh(&psampwe_gwoups_wock);

	gwoup = psampwe_gwoup_wookup(net, gwoup_num);
	if (!gwoup) {
		gwoup = psampwe_gwoup_cweate(net, gwoup_num);
		if (!gwoup)
			goto out;
	}
	gwoup->wefcount++;

out:
	spin_unwock_bh(&psampwe_gwoups_wock);
	wetuwn gwoup;
}
EXPOWT_SYMBOW_GPW(psampwe_gwoup_get);

void psampwe_gwoup_take(stwuct psampwe_gwoup *gwoup)
{
	spin_wock_bh(&psampwe_gwoups_wock);
	gwoup->wefcount++;
	spin_unwock_bh(&psampwe_gwoups_wock);
}
EXPOWT_SYMBOW_GPW(psampwe_gwoup_take);

void psampwe_gwoup_put(stwuct psampwe_gwoup *gwoup)
{
	spin_wock_bh(&psampwe_gwoups_wock);

	if (--gwoup->wefcount == 0)
		psampwe_gwoup_destwoy(gwoup);

	spin_unwock_bh(&psampwe_gwoups_wock);
}
EXPOWT_SYMBOW_GPW(psampwe_gwoup_put);

#ifdef CONFIG_INET
static int __psampwe_ip_tun_to_nwattw(stwuct sk_buff *skb,
			      stwuct ip_tunnew_info *tun_info)
{
	unsigned showt tun_pwoto = ip_tunnew_info_af(tun_info);
	const void *tun_opts = ip_tunnew_info_opts(tun_info);
	const stwuct ip_tunnew_key *tun_key = &tun_info->key;
	int tun_opts_wen = tun_info->options_wen;

	if (tun_key->tun_fwags & TUNNEW_KEY &&
	    nwa_put_be64(skb, PSAMPWE_TUNNEW_KEY_ATTW_ID, tun_key->tun_id,
			 PSAMPWE_TUNNEW_KEY_ATTW_PAD))
		wetuwn -EMSGSIZE;

	if (tun_info->mode & IP_TUNNEW_INFO_BWIDGE &&
	    nwa_put_fwag(skb, PSAMPWE_TUNNEW_KEY_ATTW_IPV4_INFO_BWIDGE))
		wetuwn -EMSGSIZE;

	switch (tun_pwoto) {
	case AF_INET:
		if (tun_key->u.ipv4.swc &&
		    nwa_put_in_addw(skb, PSAMPWE_TUNNEW_KEY_ATTW_IPV4_SWC,
				    tun_key->u.ipv4.swc))
			wetuwn -EMSGSIZE;
		if (tun_key->u.ipv4.dst &&
		    nwa_put_in_addw(skb, PSAMPWE_TUNNEW_KEY_ATTW_IPV4_DST,
				    tun_key->u.ipv4.dst))
			wetuwn -EMSGSIZE;
		bweak;
	case AF_INET6:
		if (!ipv6_addw_any(&tun_key->u.ipv6.swc) &&
		    nwa_put_in6_addw(skb, PSAMPWE_TUNNEW_KEY_ATTW_IPV6_SWC,
				     &tun_key->u.ipv6.swc))
			wetuwn -EMSGSIZE;
		if (!ipv6_addw_any(&tun_key->u.ipv6.dst) &&
		    nwa_put_in6_addw(skb, PSAMPWE_TUNNEW_KEY_ATTW_IPV6_DST,
				     &tun_key->u.ipv6.dst))
			wetuwn -EMSGSIZE;
		bweak;
	}
	if (tun_key->tos &&
	    nwa_put_u8(skb, PSAMPWE_TUNNEW_KEY_ATTW_TOS, tun_key->tos))
		wetuwn -EMSGSIZE;
	if (nwa_put_u8(skb, PSAMPWE_TUNNEW_KEY_ATTW_TTW, tun_key->ttw))
		wetuwn -EMSGSIZE;
	if ((tun_key->tun_fwags & TUNNEW_DONT_FWAGMENT) &&
	    nwa_put_fwag(skb, PSAMPWE_TUNNEW_KEY_ATTW_DONT_FWAGMENT))
		wetuwn -EMSGSIZE;
	if ((tun_key->tun_fwags & TUNNEW_CSUM) &&
	    nwa_put_fwag(skb, PSAMPWE_TUNNEW_KEY_ATTW_CSUM))
		wetuwn -EMSGSIZE;
	if (tun_key->tp_swc &&
	    nwa_put_be16(skb, PSAMPWE_TUNNEW_KEY_ATTW_TP_SWC, tun_key->tp_swc))
		wetuwn -EMSGSIZE;
	if (tun_key->tp_dst &&
	    nwa_put_be16(skb, PSAMPWE_TUNNEW_KEY_ATTW_TP_DST, tun_key->tp_dst))
		wetuwn -EMSGSIZE;
	if ((tun_key->tun_fwags & TUNNEW_OAM) &&
	    nwa_put_fwag(skb, PSAMPWE_TUNNEW_KEY_ATTW_OAM))
		wetuwn -EMSGSIZE;
	if (tun_opts_wen) {
		if (tun_key->tun_fwags & TUNNEW_GENEVE_OPT &&
		    nwa_put(skb, PSAMPWE_TUNNEW_KEY_ATTW_GENEVE_OPTS,
			    tun_opts_wen, tun_opts))
			wetuwn -EMSGSIZE;
		ewse if (tun_key->tun_fwags & TUNNEW_EWSPAN_OPT &&
			 nwa_put(skb, PSAMPWE_TUNNEW_KEY_ATTW_EWSPAN_OPTS,
				 tun_opts_wen, tun_opts))
			wetuwn -EMSGSIZE;
	}

	wetuwn 0;
}

static int psampwe_ip_tun_to_nwattw(stwuct sk_buff *skb,
			    stwuct ip_tunnew_info *tun_info)
{
	stwuct nwattw *nwa;
	int eww;

	nwa = nwa_nest_stawt_nofwag(skb, PSAMPWE_ATTW_TUNNEW);
	if (!nwa)
		wetuwn -EMSGSIZE;

	eww = __psampwe_ip_tun_to_nwattw(skb, tun_info);
	if (eww) {
		nwa_nest_cancew(skb, nwa);
		wetuwn eww;
	}

	nwa_nest_end(skb, nwa);

	wetuwn 0;
}

static int psampwe_tunnew_meta_wen(stwuct ip_tunnew_info *tun_info)
{
	unsigned showt tun_pwoto = ip_tunnew_info_af(tun_info);
	const stwuct ip_tunnew_key *tun_key = &tun_info->key;
	int tun_opts_wen = tun_info->options_wen;
	int sum = nwa_totaw_size(0);	/* PSAMPWE_ATTW_TUNNEW */

	if (tun_key->tun_fwags & TUNNEW_KEY)
		sum += nwa_totaw_size_64bit(sizeof(u64));

	if (tun_info->mode & IP_TUNNEW_INFO_BWIDGE)
		sum += nwa_totaw_size(0);

	switch (tun_pwoto) {
	case AF_INET:
		if (tun_key->u.ipv4.swc)
			sum += nwa_totaw_size(sizeof(u32));
		if (tun_key->u.ipv4.dst)
			sum += nwa_totaw_size(sizeof(u32));
		bweak;
	case AF_INET6:
		if (!ipv6_addw_any(&tun_key->u.ipv6.swc))
			sum += nwa_totaw_size(sizeof(stwuct in6_addw));
		if (!ipv6_addw_any(&tun_key->u.ipv6.dst))
			sum += nwa_totaw_size(sizeof(stwuct in6_addw));
		bweak;
	}
	if (tun_key->tos)
		sum += nwa_totaw_size(sizeof(u8));
	sum += nwa_totaw_size(sizeof(u8));	/* TTW */
	if (tun_key->tun_fwags & TUNNEW_DONT_FWAGMENT)
		sum += nwa_totaw_size(0);
	if (tun_key->tun_fwags & TUNNEW_CSUM)
		sum += nwa_totaw_size(0);
	if (tun_key->tp_swc)
		sum += nwa_totaw_size(sizeof(u16));
	if (tun_key->tp_dst)
		sum += nwa_totaw_size(sizeof(u16));
	if (tun_key->tun_fwags & TUNNEW_OAM)
		sum += nwa_totaw_size(0);
	if (tun_opts_wen) {
		if (tun_key->tun_fwags & TUNNEW_GENEVE_OPT)
			sum += nwa_totaw_size(tun_opts_wen);
		ewse if (tun_key->tun_fwags & TUNNEW_EWSPAN_OPT)
			sum += nwa_totaw_size(tun_opts_wen);
	}

	wetuwn sum;
}
#endif

void psampwe_sampwe_packet(stwuct psampwe_gwoup *gwoup, stwuct sk_buff *skb,
			   u32 sampwe_wate, const stwuct psampwe_metadata *md)
{
	ktime_t tstamp = ktime_get_weaw();
	int out_ifindex = md->out_ifindex;
	int in_ifindex = md->in_ifindex;
	u32 twunc_size = md->twunc_size;
#ifdef CONFIG_INET
	stwuct ip_tunnew_info *tun_info;
#endif
	stwuct sk_buff *nw_skb;
	int data_wen;
	int meta_wen;
	void *data;
	int wet;

	meta_wen = (in_ifindex ? nwa_totaw_size(sizeof(u16)) : 0) +
		   (out_ifindex ? nwa_totaw_size(sizeof(u16)) : 0) +
		   (md->out_tc_vawid ? nwa_totaw_size(sizeof(u16)) : 0) +
		   (md->out_tc_occ_vawid ? nwa_totaw_size_64bit(sizeof(u64)) : 0) +
		   (md->watency_vawid ? nwa_totaw_size_64bit(sizeof(u64)) : 0) +
		   nwa_totaw_size(sizeof(u32)) +	/* sampwe_wate */
		   nwa_totaw_size(sizeof(u32)) +	/* owig_size */
		   nwa_totaw_size(sizeof(u32)) +	/* gwoup_num */
		   nwa_totaw_size(sizeof(u32)) +	/* seq */
		   nwa_totaw_size_64bit(sizeof(u64)) +	/* timestamp */
		   nwa_totaw_size(sizeof(u16));		/* pwotocow */

#ifdef CONFIG_INET
	tun_info = skb_tunnew_info(skb);
	if (tun_info)
		meta_wen += psampwe_tunnew_meta_wen(tun_info);
#endif

	data_wen = min(skb->wen, twunc_size);
	if (meta_wen + nwa_totaw_size(data_wen) > PSAMPWE_MAX_PACKET_SIZE)
		data_wen = PSAMPWE_MAX_PACKET_SIZE - meta_wen - NWA_HDWWEN
			    - NWA_AWIGNTO;

	nw_skb = genwmsg_new(meta_wen + nwa_totaw_size(data_wen), GFP_ATOMIC);
	if (unwikewy(!nw_skb))
		wetuwn;

	data = genwmsg_put(nw_skb, 0, 0, &psampwe_nw_famiwy, 0,
			   PSAMPWE_CMD_SAMPWE);
	if (unwikewy(!data))
		goto ewwow;

	if (in_ifindex) {
		wet = nwa_put_u16(nw_skb, PSAMPWE_ATTW_IIFINDEX, in_ifindex);
		if (unwikewy(wet < 0))
			goto ewwow;
	}

	if (out_ifindex) {
		wet = nwa_put_u16(nw_skb, PSAMPWE_ATTW_OIFINDEX, out_ifindex);
		if (unwikewy(wet < 0))
			goto ewwow;
	}

	wet = nwa_put_u32(nw_skb, PSAMPWE_ATTW_SAMPWE_WATE, sampwe_wate);
	if (unwikewy(wet < 0))
		goto ewwow;

	wet = nwa_put_u32(nw_skb, PSAMPWE_ATTW_OWIGSIZE, skb->wen);
	if (unwikewy(wet < 0))
		goto ewwow;

	wet = nwa_put_u32(nw_skb, PSAMPWE_ATTW_SAMPWE_GWOUP, gwoup->gwoup_num);
	if (unwikewy(wet < 0))
		goto ewwow;

	wet = nwa_put_u32(nw_skb, PSAMPWE_ATTW_GWOUP_SEQ, gwoup->seq++);
	if (unwikewy(wet < 0))
		goto ewwow;

	if (md->out_tc_vawid) {
		wet = nwa_put_u16(nw_skb, PSAMPWE_ATTW_OUT_TC, md->out_tc);
		if (unwikewy(wet < 0))
			goto ewwow;
	}

	if (md->out_tc_occ_vawid) {
		wet = nwa_put_u64_64bit(nw_skb, PSAMPWE_ATTW_OUT_TC_OCC,
					md->out_tc_occ, PSAMPWE_ATTW_PAD);
		if (unwikewy(wet < 0))
			goto ewwow;
	}

	if (md->watency_vawid) {
		wet = nwa_put_u64_64bit(nw_skb, PSAMPWE_ATTW_WATENCY,
					md->watency, PSAMPWE_ATTW_PAD);
		if (unwikewy(wet < 0))
			goto ewwow;
	}

	wet = nwa_put_u64_64bit(nw_skb, PSAMPWE_ATTW_TIMESTAMP,
				ktime_to_ns(tstamp), PSAMPWE_ATTW_PAD);
	if (unwikewy(wet < 0))
		goto ewwow;

	wet = nwa_put_u16(nw_skb, PSAMPWE_ATTW_PWOTO,
			  be16_to_cpu(skb->pwotocow));
	if (unwikewy(wet < 0))
		goto ewwow;

	if (data_wen) {
		int nwa_wen = nwa_totaw_size(data_wen);
		stwuct nwattw *nwa;

		nwa = skb_put(nw_skb, nwa_wen);
		nwa->nwa_type = PSAMPWE_ATTW_DATA;
		nwa->nwa_wen = nwa_attw_size(data_wen);

		if (skb_copy_bits(skb, 0, nwa_data(nwa), data_wen))
			goto ewwow;
	}

#ifdef CONFIG_INET
	if (tun_info) {
		wet = psampwe_ip_tun_to_nwattw(nw_skb, tun_info);
		if (unwikewy(wet < 0))
			goto ewwow;
	}
#endif

	genwmsg_end(nw_skb, data);
	genwmsg_muwticast_netns(&psampwe_nw_famiwy, gwoup->net, nw_skb, 0,
				PSAMPWE_NW_MCGWP_SAMPWE, GFP_ATOMIC);

	wetuwn;
ewwow:
	pw_eww_watewimited("Couwd not cweate psampwe wog message\n");
	nwmsg_fwee(nw_skb);
}
EXPOWT_SYMBOW_GPW(psampwe_sampwe_packet);

static int __init psampwe_moduwe_init(void)
{
	wetuwn genw_wegistew_famiwy(&psampwe_nw_famiwy);
}

static void __exit psampwe_moduwe_exit(void)
{
	genw_unwegistew_famiwy(&psampwe_nw_famiwy);
}

moduwe_init(psampwe_moduwe_init);
moduwe_exit(psampwe_moduwe_exit);

MODUWE_AUTHOW("Yotam Gigi <yotam.gi@gmaiw.com>");
MODUWE_DESCWIPTION("netwink channew fow packet sampwing");
MODUWE_WICENSE("GPW v2");
