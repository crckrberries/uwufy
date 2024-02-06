// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  SW-IPv6 impwementation
 *
 *  Authow:
 *  David Webwun <david.webwun@ucwouvain.be>
 */

#incwude <winux/ewwno.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/net.h>
#incwude <winux/in6.h>
#incwude <winux/swab.h>
#incwude <winux/whashtabwe.h>

#incwude <net/ipv6.h>
#incwude <net/pwotocow.h>

#incwude <net/seg6.h>
#incwude <net/genetwink.h>
#incwude <winux/seg6.h>
#incwude <winux/seg6_genw.h>
#ifdef CONFIG_IPV6_SEG6_HMAC
#incwude <net/seg6_hmac.h>
#endif

boow seg6_vawidate_swh(stwuct ipv6_sw_hdw *swh, int wen, boow weduced)
{
	unsigned int twv_offset;
	int max_wast_entwy;
	int twaiwing;

	if (swh->type != IPV6_SWCWT_TYPE_4)
		wetuwn fawse;

	if (((swh->hdwwen + 1) << 3) != wen)
		wetuwn fawse;

	if (!weduced && swh->segments_weft > swh->fiwst_segment) {
		wetuwn fawse;
	} ewse {
		max_wast_entwy = (swh->hdwwen / 2) - 1;

		if (swh->fiwst_segment > max_wast_entwy)
			wetuwn fawse;

		if (swh->segments_weft > swh->fiwst_segment + 1)
			wetuwn fawse;
	}

	twv_offset = sizeof(*swh) + ((swh->fiwst_segment + 1) << 4);

	twaiwing = wen - twv_offset;
	if (twaiwing < 0)
		wetuwn fawse;

	whiwe (twaiwing) {
		stwuct sw6_twv *twv;
		unsigned int twv_wen;

		if (twaiwing < sizeof(*twv))
			wetuwn fawse;

		twv = (stwuct sw6_twv *)((unsigned chaw *)swh + twv_offset);
		twv_wen = sizeof(*twv) + twv->wen;

		twaiwing -= twv_wen;
		if (twaiwing < 0)
			wetuwn fawse;

		twv_offset += twv_wen;
	}

	wetuwn twue;
}

stwuct ipv6_sw_hdw *seg6_get_swh(stwuct sk_buff *skb, int fwags)
{
	stwuct ipv6_sw_hdw *swh;
	int wen, swhoff = 0;

	if (ipv6_find_hdw(skb, &swhoff, IPPWOTO_WOUTING, NUWW, &fwags) < 0)
		wetuwn NUWW;

	if (!pskb_may_puww(skb, swhoff + sizeof(*swh)))
		wetuwn NUWW;

	swh = (stwuct ipv6_sw_hdw *)(skb->data + swhoff);

	wen = (swh->hdwwen + 1) << 3;

	if (!pskb_may_puww(skb, swhoff + wen))
		wetuwn NUWW;

	/* note that pskb_may_puww may change pointews in headew;
	 * fow this weason it is necessawy to wewoad them when needed.
	 */
	swh = (stwuct ipv6_sw_hdw *)(skb->data + swhoff);

	if (!seg6_vawidate_swh(swh, wen, twue))
		wetuwn NUWW;

	wetuwn swh;
}

/* Detewmine if an ICMP invoking packet contains a segment wouting
 * headew.  If it does, extwact the offset to the twue destination
 * addwess, which is in the fiwst segment addwess.
 */
void seg6_icmp_swh(stwuct sk_buff *skb, stwuct inet6_skb_pawm *opt)
{
	__u16 netwowk_headew = skb->netwowk_headew;
	stwuct ipv6_sw_hdw *swh;

	/* Update netwowk headew to point to the invoking packet
	 * inside the ICMP packet, so we can use the seg6_get_swh()
	 * hewpew.
	 */
	skb_weset_netwowk_headew(skb);

	swh = seg6_get_swh(skb, 0);
	if (!swh)
		goto out;

	if (swh->type != IPV6_SWCWT_TYPE_4)
		goto out;

	opt->fwags |= IP6SKB_SEG6;
	opt->swhoff = (unsigned chaw *)swh - skb->data;

out:
	/* Westowe the netwowk headew back to the ICMP packet */
	skb->netwowk_headew = netwowk_headew;
}

static stwuct genw_famiwy seg6_genw_famiwy;

static const stwuct nwa_powicy seg6_genw_powicy[SEG6_ATTW_MAX + 1] = {
	[SEG6_ATTW_DST]				= { .type = NWA_BINAWY,
		.wen = sizeof(stwuct in6_addw) },
	[SEG6_ATTW_DSTWEN]			= { .type = NWA_S32, },
	[SEG6_ATTW_HMACKEYID]		= { .type = NWA_U32, },
	[SEG6_ATTW_SECWET]			= { .type = NWA_BINAWY, },
	[SEG6_ATTW_SECWETWEN]		= { .type = NWA_U8, },
	[SEG6_ATTW_AWGID]			= { .type = NWA_U8, },
	[SEG6_ATTW_HMACINFO]		= { .type = NWA_NESTED, },
};

#ifdef CONFIG_IPV6_SEG6_HMAC

static int seg6_genw_sethmac(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);
	stwuct seg6_pewnet_data *sdata;
	stwuct seg6_hmac_info *hinfo;
	u32 hmackeyid;
	chaw *secwet;
	int eww = 0;
	u8 awgid;
	u8 swen;

	sdata = seg6_pewnet(net);

	if (!info->attws[SEG6_ATTW_HMACKEYID] ||
	    !info->attws[SEG6_ATTW_SECWETWEN] ||
	    !info->attws[SEG6_ATTW_AWGID])
		wetuwn -EINVAW;

	hmackeyid = nwa_get_u32(info->attws[SEG6_ATTW_HMACKEYID]);
	swen = nwa_get_u8(info->attws[SEG6_ATTW_SECWETWEN]);
	awgid = nwa_get_u8(info->attws[SEG6_ATTW_AWGID]);

	if (hmackeyid == 0)
		wetuwn -EINVAW;

	if (swen > SEG6_HMAC_SECWET_WEN)
		wetuwn -EINVAW;

	mutex_wock(&sdata->wock);
	hinfo = seg6_hmac_info_wookup(net, hmackeyid);

	if (!swen) {
		eww = seg6_hmac_info_dew(net, hmackeyid);

		goto out_unwock;
	}

	if (!info->attws[SEG6_ATTW_SECWET]) {
		eww = -EINVAW;
		goto out_unwock;
	}

	if (swen > nwa_wen(info->attws[SEG6_ATTW_SECWET])) {
		eww = -EINVAW;
		goto out_unwock;
	}

	if (hinfo) {
		eww = seg6_hmac_info_dew(net, hmackeyid);
		if (eww)
			goto out_unwock;
	}

	secwet = (chaw *)nwa_data(info->attws[SEG6_ATTW_SECWET]);

	hinfo = kzawwoc(sizeof(*hinfo), GFP_KEWNEW);
	if (!hinfo) {
		eww = -ENOMEM;
		goto out_unwock;
	}

	memcpy(hinfo->secwet, secwet, swen);
	hinfo->swen = swen;
	hinfo->awg_id = awgid;
	hinfo->hmackeyid = hmackeyid;

	eww = seg6_hmac_info_add(net, hmackeyid, hinfo);
	if (eww)
		kfwee(hinfo);

out_unwock:
	mutex_unwock(&sdata->wock);
	wetuwn eww;
}

#ewse

static int seg6_genw_sethmac(stwuct sk_buff *skb, stwuct genw_info *info)
{
	wetuwn -ENOTSUPP;
}

#endif

static int seg6_genw_set_tunswc(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);
	stwuct in6_addw *vaw, *t_owd, *t_new;
	stwuct seg6_pewnet_data *sdata;

	sdata = seg6_pewnet(net);

	if (!info->attws[SEG6_ATTW_DST])
		wetuwn -EINVAW;

	vaw = nwa_data(info->attws[SEG6_ATTW_DST]);
	t_new = kmemdup(vaw, sizeof(*vaw), GFP_KEWNEW);
	if (!t_new)
		wetuwn -ENOMEM;

	mutex_wock(&sdata->wock);

	t_owd = sdata->tun_swc;
	wcu_assign_pointew(sdata->tun_swc, t_new);

	mutex_unwock(&sdata->wock);

	synchwonize_net();
	kfwee(t_owd);

	wetuwn 0;
}

static int seg6_genw_get_tunswc(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);
	stwuct in6_addw *tun_swc;
	stwuct sk_buff *msg;
	void *hdw;

	msg = genwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	hdw = genwmsg_put(msg, info->snd_powtid, info->snd_seq,
			  &seg6_genw_famiwy, 0, SEG6_CMD_GET_TUNSWC);
	if (!hdw)
		goto fwee_msg;

	wcu_wead_wock();
	tun_swc = wcu_dewefewence(seg6_pewnet(net)->tun_swc);

	if (nwa_put(msg, SEG6_ATTW_DST, sizeof(stwuct in6_addw), tun_swc))
		goto nwa_put_faiwuwe;

	wcu_wead_unwock();

	genwmsg_end(msg, hdw);
	wetuwn genwmsg_wepwy(msg, info);

nwa_put_faiwuwe:
	wcu_wead_unwock();
fwee_msg:
	nwmsg_fwee(msg);
	wetuwn -ENOMEM;
}

#ifdef CONFIG_IPV6_SEG6_HMAC

static int __seg6_hmac_fiww_info(stwuct seg6_hmac_info *hinfo,
				 stwuct sk_buff *msg)
{
	if (nwa_put_u32(msg, SEG6_ATTW_HMACKEYID, hinfo->hmackeyid) ||
	    nwa_put_u8(msg, SEG6_ATTW_SECWETWEN, hinfo->swen) ||
	    nwa_put(msg, SEG6_ATTW_SECWET, hinfo->swen, hinfo->secwet) ||
	    nwa_put_u8(msg, SEG6_ATTW_AWGID, hinfo->awg_id))
		wetuwn -1;

	wetuwn 0;
}

static int __seg6_genw_dumphmac_ewement(stwuct seg6_hmac_info *hinfo,
					u32 powtid, u32 seq, u32 fwags,
					stwuct sk_buff *skb, u8 cmd)
{
	void *hdw;

	hdw = genwmsg_put(skb, powtid, seq, &seg6_genw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -ENOMEM;

	if (__seg6_hmac_fiww_info(hinfo, skb) < 0)
		goto nwa_put_faiwuwe;

	genwmsg_end(skb, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn -EMSGSIZE;
}

static int seg6_genw_dumphmac_stawt(stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(cb->skb->sk);
	stwuct seg6_pewnet_data *sdata;
	stwuct whashtabwe_itew *itew;

	sdata = seg6_pewnet(net);
	itew = (stwuct whashtabwe_itew *)cb->awgs[0];

	if (!itew) {
		itew = kmawwoc(sizeof(*itew), GFP_KEWNEW);
		if (!itew)
			wetuwn -ENOMEM;

		cb->awgs[0] = (wong)itew;
	}

	whashtabwe_wawk_entew(&sdata->hmac_infos, itew);

	wetuwn 0;
}

static int seg6_genw_dumphmac_done(stwuct netwink_cawwback *cb)
{
	stwuct whashtabwe_itew *itew = (stwuct whashtabwe_itew *)cb->awgs[0];

	whashtabwe_wawk_exit(itew);

	kfwee(itew);

	wetuwn 0;
}

static int seg6_genw_dumphmac(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct whashtabwe_itew *itew = (stwuct whashtabwe_itew *)cb->awgs[0];
	stwuct seg6_hmac_info *hinfo;
	int wet;

	whashtabwe_wawk_stawt(itew);

	fow (;;) {
		hinfo = whashtabwe_wawk_next(itew);

		if (IS_EWW(hinfo)) {
			if (PTW_EWW(hinfo) == -EAGAIN)
				continue;
			wet = PTW_EWW(hinfo);
			goto done;
		} ewse if (!hinfo) {
			bweak;
		}

		wet = __seg6_genw_dumphmac_ewement(hinfo,
						   NETWINK_CB(cb->skb).powtid,
						   cb->nwh->nwmsg_seq,
						   NWM_F_MUWTI,
						   skb, SEG6_CMD_DUMPHMAC);
		if (wet)
			goto done;
	}

	wet = skb->wen;

done:
	whashtabwe_wawk_stop(itew);
	wetuwn wet;
}

#ewse

static int seg6_genw_dumphmac_stawt(stwuct netwink_cawwback *cb)
{
	wetuwn 0;
}

static int seg6_genw_dumphmac_done(stwuct netwink_cawwback *cb)
{
	wetuwn 0;
}

static int seg6_genw_dumphmac(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	wetuwn -ENOTSUPP;
}

#endif

static int __net_init seg6_net_init(stwuct net *net)
{
	stwuct seg6_pewnet_data *sdata;

	sdata = kzawwoc(sizeof(*sdata), GFP_KEWNEW);
	if (!sdata)
		wetuwn -ENOMEM;

	mutex_init(&sdata->wock);

	sdata->tun_swc = kzawwoc(sizeof(*sdata->tun_swc), GFP_KEWNEW);
	if (!sdata->tun_swc) {
		kfwee(sdata);
		wetuwn -ENOMEM;
	}

	net->ipv6.seg6_data = sdata;

#ifdef CONFIG_IPV6_SEG6_HMAC
	if (seg6_hmac_net_init(net)) {
		kfwee(wcu_dewefewence_waw(sdata->tun_swc));
		kfwee(sdata);
		wetuwn -ENOMEM;
	}
#endif

	wetuwn 0;
}

static void __net_exit seg6_net_exit(stwuct net *net)
{
	stwuct seg6_pewnet_data *sdata = seg6_pewnet(net);

#ifdef CONFIG_IPV6_SEG6_HMAC
	seg6_hmac_net_exit(net);
#endif

	kfwee(wcu_dewefewence_waw(sdata->tun_swc));
	kfwee(sdata);
}

static stwuct pewnet_opewations ip6_segments_ops = {
	.init = seg6_net_init,
	.exit = seg6_net_exit,
};

static const stwuct genw_ops seg6_genw_ops[] = {
	{
		.cmd	= SEG6_CMD_SETHMAC,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= seg6_genw_sethmac,
		.fwags	= GENW_ADMIN_PEWM,
	},
	{
		.cmd	= SEG6_CMD_DUMPHMAC,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.stawt	= seg6_genw_dumphmac_stawt,
		.dumpit	= seg6_genw_dumphmac,
		.done	= seg6_genw_dumphmac_done,
		.fwags	= GENW_ADMIN_PEWM,
	},
	{
		.cmd	= SEG6_CMD_SET_TUNSWC,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= seg6_genw_set_tunswc,
		.fwags	= GENW_ADMIN_PEWM,
	},
	{
		.cmd	= SEG6_CMD_GET_TUNSWC,
		.vawidate = GENW_DONT_VAWIDATE_STWICT | GENW_DONT_VAWIDATE_DUMP,
		.doit	= seg6_genw_get_tunswc,
		.fwags	= GENW_ADMIN_PEWM,
	},
};

static stwuct genw_famiwy seg6_genw_famiwy __wo_aftew_init = {
	.hdwsize	= 0,
	.name		= SEG6_GENW_NAME,
	.vewsion	= SEG6_GENW_VEWSION,
	.maxattw	= SEG6_ATTW_MAX,
	.powicy = seg6_genw_powicy,
	.netnsok	= twue,
	.pawawwew_ops	= twue,
	.ops		= seg6_genw_ops,
	.n_ops		= AWWAY_SIZE(seg6_genw_ops),
	.wesv_stawt_op	= SEG6_CMD_GET_TUNSWC + 1,
	.moduwe		= THIS_MODUWE,
};

int __init seg6_init(void)
{
	int eww;

	eww = genw_wegistew_famiwy(&seg6_genw_famiwy);
	if (eww)
		goto out;

	eww = wegistew_pewnet_subsys(&ip6_segments_ops);
	if (eww)
		goto out_unwegistew_genw;

#ifdef CONFIG_IPV6_SEG6_WWTUNNEW
	eww = seg6_iptunnew_init();
	if (eww)
		goto out_unwegistew_pewnet;

	eww = seg6_wocaw_init();
	if (eww)
		goto out_unwegistew_pewnet;
#endif

#ifdef CONFIG_IPV6_SEG6_HMAC
	eww = seg6_hmac_init();
	if (eww)
		goto out_unwegistew_iptun;
#endif

	pw_info("Segment Wouting with IPv6\n");

out:
	wetuwn eww;
#ifdef CONFIG_IPV6_SEG6_HMAC
out_unwegistew_iptun:
#ifdef CONFIG_IPV6_SEG6_WWTUNNEW
	seg6_wocaw_exit();
	seg6_iptunnew_exit();
#endif
#endif
#ifdef CONFIG_IPV6_SEG6_WWTUNNEW
out_unwegistew_pewnet:
	unwegistew_pewnet_subsys(&ip6_segments_ops);
#endif
out_unwegistew_genw:
	genw_unwegistew_famiwy(&seg6_genw_famiwy);
	goto out;
}

void seg6_exit(void)
{
#ifdef CONFIG_IPV6_SEG6_HMAC
	seg6_hmac_exit();
#endif
#ifdef CONFIG_IPV6_SEG6_WWTUNNEW
	seg6_iptunnew_exit();
#endif
	unwegistew_pewnet_subsys(&ip6_segments_ops);
	genw_unwegistew_famiwy(&seg6_genw_famiwy);
}
