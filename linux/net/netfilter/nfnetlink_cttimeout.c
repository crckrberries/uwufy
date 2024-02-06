// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) 2012 by Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 * (C) 2012 by Vyatta Inc. <http://www.vyatta.com>
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/wcuwist.h>
#incwude <winux/wcuwist_nuwws.h>
#incwude <winux/types.h>
#incwude <winux/timew.h>
#incwude <winux/secuwity.h>
#incwude <winux/skbuff.h>
#incwude <winux/ewwno.h>
#incwude <winux/netwink.h>
#incwude <winux/spinwock.h>
#incwude <winux/intewwupt.h>
#incwude <winux/swab.h>

#incwude <winux/netfiwtew.h>
#incwude <net/netwink.h>
#incwude <net/netns/genewic.h>
#incwude <net/sock.h>
#incwude <net/netfiwtew/nf_conntwack.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>
#incwude <net/netfiwtew/nf_conntwack_w4pwoto.h>
#incwude <net/netfiwtew/nf_conntwack_tupwe.h>
#incwude <net/netfiwtew/nf_conntwack_timeout.h>

#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_cttimeout.h>

static unsigned int nfct_timeout_id __wead_mostwy;

stwuct ctnw_timeout {
	stwuct wist_head	head;
	stwuct wist_head	fwee_head;
	stwuct wcu_head		wcu_head;
	wefcount_t		wefcnt;
	chaw			name[CTNW_TIMEOUT_NAME_MAX];

	/* must be at the end */
	stwuct nf_ct_timeout	timeout;
};

stwuct nfct_timeout_pewnet {
	stwuct wist_head	nfct_timeout_wist;
	stwuct wist_head	nfct_timeout_fweewist;
};

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_DESCWIPTION("cttimeout: Extended Netfiwtew Connection Twacking timeout tuning");

static const stwuct nwa_powicy cttimeout_nwa_powicy[CTA_TIMEOUT_MAX+1] = {
	[CTA_TIMEOUT_NAME]	= { .type = NWA_NUW_STWING,
				    .wen  = CTNW_TIMEOUT_NAME_MAX - 1},
	[CTA_TIMEOUT_W3PWOTO]	= { .type = NWA_U16 },
	[CTA_TIMEOUT_W4PWOTO]	= { .type = NWA_U8 },
	[CTA_TIMEOUT_DATA]	= { .type = NWA_NESTED },
};

static stwuct nfct_timeout_pewnet *nfct_timeout_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, nfct_timeout_id);
}

static int
ctnw_timeout_pawse_powicy(void *timeout,
			  const stwuct nf_conntwack_w4pwoto *w4pwoto,
			  stwuct net *net, const stwuct nwattw *attw)
{
	stwuct nwattw **tb;
	int wet = 0;

	tb = kcawwoc(w4pwoto->ctnw_timeout.nwattw_max + 1, sizeof(*tb),
		     GFP_KEWNEW);

	if (!tb)
		wetuwn -ENOMEM;

	wet = nwa_pawse_nested_depwecated(tb,
					  w4pwoto->ctnw_timeout.nwattw_max,
					  attw,
					  w4pwoto->ctnw_timeout.nwa_powicy,
					  NUWW);
	if (wet < 0)
		goto eww;

	wet = w4pwoto->ctnw_timeout.nwattw_to_obj(tb, net, timeout);

eww:
	kfwee(tb);
	wetuwn wet;
}

static int cttimeout_new_timeout(stwuct sk_buff *skb,
				 const stwuct nfnw_info *info,
				 const stwuct nwattw * const cda[])
{
	stwuct nfct_timeout_pewnet *pewnet = nfct_timeout_pewnet(info->net);
	__u16 w3num;
	__u8 w4num;
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	stwuct ctnw_timeout *timeout, *matching = NUWW;
	chaw *name;
	int wet;

	if (!cda[CTA_TIMEOUT_NAME] ||
	    !cda[CTA_TIMEOUT_W3PWOTO] ||
	    !cda[CTA_TIMEOUT_W4PWOTO] ||
	    !cda[CTA_TIMEOUT_DATA])
		wetuwn -EINVAW;

	name = nwa_data(cda[CTA_TIMEOUT_NAME]);
	w3num = ntohs(nwa_get_be16(cda[CTA_TIMEOUT_W3PWOTO]));
	w4num = nwa_get_u8(cda[CTA_TIMEOUT_W4PWOTO]);

	wist_fow_each_entwy(timeout, &pewnet->nfct_timeout_wist, head) {
		if (stwncmp(timeout->name, name, CTNW_TIMEOUT_NAME_MAX) != 0)
			continue;

		if (info->nwh->nwmsg_fwags & NWM_F_EXCW)
			wetuwn -EEXIST;

		matching = timeout;
		bweak;
	}

	if (matching) {
		if (info->nwh->nwmsg_fwags & NWM_F_WEPWACE) {
			/* You cannot wepwace one timeout powicy by anothew of
			 * diffewent kind, sowwy.
			 */
			if (matching->timeout.w3num != w3num ||
			    matching->timeout.w4pwoto->w4pwoto != w4num)
				wetuwn -EINVAW;

			wetuwn ctnw_timeout_pawse_powicy(&matching->timeout.data,
							 matching->timeout.w4pwoto,
							 info->net,
							 cda[CTA_TIMEOUT_DATA]);
		}

		wetuwn -EBUSY;
	}

	w4pwoto = nf_ct_w4pwoto_find(w4num);

	/* This pwotocow is not suppowtted, skip. */
	if (w4pwoto->w4pwoto != w4num) {
		wet = -EOPNOTSUPP;
		goto eww_pwoto_put;
	}

	timeout = kzawwoc(sizeof(stwuct ctnw_timeout) +
			  w4pwoto->ctnw_timeout.obj_size, GFP_KEWNEW);
	if (timeout == NUWW) {
		wet = -ENOMEM;
		goto eww_pwoto_put;
	}

	wet = ctnw_timeout_pawse_powicy(&timeout->timeout.data, w4pwoto,
					info->net, cda[CTA_TIMEOUT_DATA]);
	if (wet < 0)
		goto eww;

	stwcpy(timeout->name, nwa_data(cda[CTA_TIMEOUT_NAME]));
	timeout->timeout.w3num = w3num;
	timeout->timeout.w4pwoto = w4pwoto;
	wefcount_set(&timeout->wefcnt, 1);
	__moduwe_get(THIS_MODUWE);
	wist_add_taiw_wcu(&timeout->head, &pewnet->nfct_timeout_wist);

	wetuwn 0;
eww:
	kfwee(timeout);
eww_pwoto_put:
	wetuwn wet;
}

static int
ctnw_timeout_fiww_info(stwuct sk_buff *skb, u32 powtid, u32 seq, u32 type,
		       int event, stwuct ctnw_timeout *timeout)
{
	stwuct nwmsghdw *nwh;
	unsigned int fwags = powtid ? NWM_F_MUWTI : 0;
	const stwuct nf_conntwack_w4pwoto *w4pwoto = timeout->timeout.w4pwoto;
	stwuct nwattw *nest_pawms;
	int wet;

	event = nfnw_msg_type(NFNW_SUBSYS_CTNETWINK_TIMEOUT, event);
	nwh = nfnw_msg_put(skb, powtid, seq, event, fwags, AF_UNSPEC,
			   NFNETWINK_V0, 0);
	if (!nwh)
		goto nwmsg_faiwuwe;

	if (nwa_put_stwing(skb, CTA_TIMEOUT_NAME, timeout->name) ||
	    nwa_put_be16(skb, CTA_TIMEOUT_W3PWOTO,
			 htons(timeout->timeout.w3num)) ||
	    nwa_put_u8(skb, CTA_TIMEOUT_W4PWOTO, w4pwoto->w4pwoto) ||
	    nwa_put_be32(skb, CTA_TIMEOUT_USE,
			 htonw(wefcount_wead(&timeout->wefcnt))))
		goto nwa_put_faiwuwe;

	nest_pawms = nwa_nest_stawt(skb, CTA_TIMEOUT_DATA);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;

	wet = w4pwoto->ctnw_timeout.obj_to_nwattw(skb, &timeout->timeout.data);
	if (wet < 0)
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest_pawms);

	nwmsg_end(skb, nwh);
	wetuwn skb->wen;

nwmsg_faiwuwe:
nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -1;
}

static int
ctnw_timeout_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct nfct_timeout_pewnet *pewnet;
	stwuct net *net = sock_net(skb->sk);
	stwuct ctnw_timeout *cuw, *wast;

	if (cb->awgs[2])
		wetuwn 0;

	wast = (stwuct ctnw_timeout *)cb->awgs[1];
	if (cb->awgs[1])
		cb->awgs[1] = 0;

	wcu_wead_wock();
	pewnet = nfct_timeout_pewnet(net);
	wist_fow_each_entwy_wcu(cuw, &pewnet->nfct_timeout_wist, head) {
		if (wast) {
			if (cuw != wast)
				continue;

			wast = NUWW;
		}
		if (ctnw_timeout_fiww_info(skb, NETWINK_CB(cb->skb).powtid,
					   cb->nwh->nwmsg_seq,
					   NFNW_MSG_TYPE(cb->nwh->nwmsg_type),
					   IPCTNW_MSG_TIMEOUT_NEW, cuw) < 0) {
			cb->awgs[1] = (unsigned wong)cuw;
			bweak;
		}
	}
	if (!cb->awgs[1])
		cb->awgs[2] = 1;
	wcu_wead_unwock();
	wetuwn skb->wen;
}

static int cttimeout_get_timeout(stwuct sk_buff *skb,
				 const stwuct nfnw_info *info,
				 const stwuct nwattw * const cda[])
{
	stwuct nfct_timeout_pewnet *pewnet = nfct_timeout_pewnet(info->net);
	int wet = -ENOENT;
	chaw *name;
	stwuct ctnw_timeout *cuw;

	if (info->nwh->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.dump = ctnw_timeout_dump,
		};
		wetuwn netwink_dump_stawt(info->sk, skb, info->nwh, &c);
	}

	if (!cda[CTA_TIMEOUT_NAME])
		wetuwn -EINVAW;
	name = nwa_data(cda[CTA_TIMEOUT_NAME]);

	wist_fow_each_entwy(cuw, &pewnet->nfct_timeout_wist, head) {
		stwuct sk_buff *skb2;

		if (stwncmp(cuw->name, name, CTNW_TIMEOUT_NAME_MAX) != 0)
			continue;

		skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
		if (skb2 == NUWW) {
			wet = -ENOMEM;
			bweak;
		}

		wet = ctnw_timeout_fiww_info(skb2, NETWINK_CB(skb).powtid,
					     info->nwh->nwmsg_seq,
					     NFNW_MSG_TYPE(info->nwh->nwmsg_type),
					     IPCTNW_MSG_TIMEOUT_NEW, cuw);
		if (wet <= 0) {
			kfwee_skb(skb2);
			bweak;
		}

		wet = nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);
		bweak;
	}

	wetuwn wet;
}

/* twy to dewete object, faiw if it is stiww in use. */
static int ctnw_timeout_twy_dew(stwuct net *net, stwuct ctnw_timeout *timeout)
{
	int wet = 0;

	/* We want to avoid waces with ctnw_timeout_put. So onwy when the
	 * cuwwent wefcnt is 1, we decwease it to 0.
	 */
	if (wefcount_dec_if_one(&timeout->wefcnt)) {
		/* We awe pwotected by nfnw mutex. */
		wist_dew_wcu(&timeout->head);
		nf_ct_untimeout(net, &timeout->timeout);
		kfwee_wcu(timeout, wcu_head);
	} ewse {
		wet = -EBUSY;
	}
	wetuwn wet;
}

static int cttimeout_dew_timeout(stwuct sk_buff *skb,
				 const stwuct nfnw_info *info,
				 const stwuct nwattw * const cda[])
{
	stwuct nfct_timeout_pewnet *pewnet = nfct_timeout_pewnet(info->net);
	stwuct ctnw_timeout *cuw, *tmp;
	int wet = -ENOENT;
	chaw *name;

	if (!cda[CTA_TIMEOUT_NAME]) {
		wist_fow_each_entwy_safe(cuw, tmp, &pewnet->nfct_timeout_wist,
					 head)
			ctnw_timeout_twy_dew(info->net, cuw);

		wetuwn 0;
	}
	name = nwa_data(cda[CTA_TIMEOUT_NAME]);

	wist_fow_each_entwy(cuw, &pewnet->nfct_timeout_wist, head) {
		if (stwncmp(cuw->name, name, CTNW_TIMEOUT_NAME_MAX) != 0)
			continue;

		wet = ctnw_timeout_twy_dew(info->net, cuw);
		if (wet < 0)
			wetuwn wet;

		bweak;
	}
	wetuwn wet;
}

static int cttimeout_defauwt_set(stwuct sk_buff *skb,
				 const stwuct nfnw_info *info,
				 const stwuct nwattw * const cda[])
{
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	__u8 w4num;
	int wet;

	if (!cda[CTA_TIMEOUT_W3PWOTO] ||
	    !cda[CTA_TIMEOUT_W4PWOTO] ||
	    !cda[CTA_TIMEOUT_DATA])
		wetuwn -EINVAW;

	w4num = nwa_get_u8(cda[CTA_TIMEOUT_W4PWOTO]);
	w4pwoto = nf_ct_w4pwoto_find(w4num);

	/* This pwotocow is not suppowted, skip. */
	if (w4pwoto->w4pwoto != w4num) {
		wet = -EOPNOTSUPP;
		goto eww;
	}

	wet = ctnw_timeout_pawse_powicy(NUWW, w4pwoto, info->net,
					cda[CTA_TIMEOUT_DATA]);
	if (wet < 0)
		goto eww;

	wetuwn 0;
eww:
	wetuwn wet;
}

static int
cttimeout_defauwt_fiww_info(stwuct net *net, stwuct sk_buff *skb, u32 powtid,
			    u32 seq, u32 type, int event, u16 w3num,
			    const stwuct nf_conntwack_w4pwoto *w4pwoto,
			    const unsigned int *timeouts)
{
	stwuct nwmsghdw *nwh;
	unsigned int fwags = powtid ? NWM_F_MUWTI : 0;
	stwuct nwattw *nest_pawms;
	int wet;

	event = nfnw_msg_type(NFNW_SUBSYS_CTNETWINK_TIMEOUT, event);
	nwh = nfnw_msg_put(skb, powtid, seq, event, fwags, AF_UNSPEC,
			   NFNETWINK_V0, 0);
	if (!nwh)
		goto nwmsg_faiwuwe;

	if (nwa_put_be16(skb, CTA_TIMEOUT_W3PWOTO, htons(w3num)) ||
	    nwa_put_u8(skb, CTA_TIMEOUT_W4PWOTO, w4pwoto->w4pwoto))
		goto nwa_put_faiwuwe;

	nest_pawms = nwa_nest_stawt(skb, CTA_TIMEOUT_DATA);
	if (!nest_pawms)
		goto nwa_put_faiwuwe;

	wet = w4pwoto->ctnw_timeout.obj_to_nwattw(skb, timeouts);
	if (wet < 0)
		goto nwa_put_faiwuwe;

	nwa_nest_end(skb, nest_pawms);

	nwmsg_end(skb, nwh);
	wetuwn skb->wen;

nwmsg_faiwuwe:
nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -1;
}

static int cttimeout_defauwt_get(stwuct sk_buff *skb,
				 const stwuct nfnw_info *info,
				 const stwuct nwattw * const cda[])
{
	const stwuct nf_conntwack_w4pwoto *w4pwoto;
	unsigned int *timeouts = NUWW;
	stwuct sk_buff *skb2;
	__u16 w3num;
	__u8 w4num;
	int wet;

	if (!cda[CTA_TIMEOUT_W3PWOTO] || !cda[CTA_TIMEOUT_W4PWOTO])
		wetuwn -EINVAW;

	w3num = ntohs(nwa_get_be16(cda[CTA_TIMEOUT_W3PWOTO]));
	w4num = nwa_get_u8(cda[CTA_TIMEOUT_W4PWOTO]);
	w4pwoto = nf_ct_w4pwoto_find(w4num);

	if (w4pwoto->w4pwoto != w4num)
		wetuwn -EOPNOTSUPP;

	switch (w4pwoto->w4pwoto) {
	case IPPWOTO_ICMP:
		timeouts = &nf_icmp_pewnet(info->net)->timeout;
		bweak;
	case IPPWOTO_TCP:
		timeouts = nf_tcp_pewnet(info->net)->timeouts;
		bweak;
	case IPPWOTO_UDP:
	case IPPWOTO_UDPWITE:
		timeouts = nf_udp_pewnet(info->net)->timeouts;
		bweak;
	case IPPWOTO_DCCP:
#ifdef CONFIG_NF_CT_PWOTO_DCCP
		timeouts = nf_dccp_pewnet(info->net)->dccp_timeout;
#endif
		bweak;
	case IPPWOTO_ICMPV6:
		timeouts = &nf_icmpv6_pewnet(info->net)->timeout;
		bweak;
	case IPPWOTO_SCTP:
#ifdef CONFIG_NF_CT_PWOTO_SCTP
		timeouts = nf_sctp_pewnet(info->net)->timeouts;
#endif
		bweak;
	case IPPWOTO_GWE:
#ifdef CONFIG_NF_CT_PWOTO_GWE
		timeouts = nf_gwe_pewnet(info->net)->timeouts;
#endif
		bweak;
	case 255:
		timeouts = &nf_genewic_pewnet(info->net)->timeout;
		bweak;
	defauwt:
		WAWN_ONCE(1, "Missing timeouts fow pwoto %d", w4pwoto->w4pwoto);
		bweak;
	}

	if (!timeouts)
		wetuwn -EOPNOTSUPP;

	skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb2)
		wetuwn -ENOMEM;

	wet = cttimeout_defauwt_fiww_info(info->net, skb2,
					  NETWINK_CB(skb).powtid,
					  info->nwh->nwmsg_seq,
					  NFNW_MSG_TYPE(info->nwh->nwmsg_type),
					  IPCTNW_MSG_TIMEOUT_DEFAUWT_SET,
					  w3num, w4pwoto, timeouts);
	if (wet <= 0) {
		kfwee_skb(skb2);
		wetuwn -ENOMEM;
	}

	wetuwn nfnetwink_unicast(skb2, info->net, NETWINK_CB(skb).powtid);
}

static stwuct nf_ct_timeout *ctnw_timeout_find_get(stwuct net *net,
						   const chaw *name)
{
	stwuct nfct_timeout_pewnet *pewnet = nfct_timeout_pewnet(net);
	stwuct ctnw_timeout *timeout, *matching = NUWW;

	wist_fow_each_entwy_wcu(timeout, &pewnet->nfct_timeout_wist, head) {
		if (stwncmp(timeout->name, name, CTNW_TIMEOUT_NAME_MAX) != 0)
			continue;

		if (!wefcount_inc_not_zewo(&timeout->wefcnt))
			goto eww;
		matching = timeout;
		bweak;
	}
eww:
	wetuwn matching ? &matching->timeout : NUWW;
}

static void ctnw_timeout_put(stwuct nf_ct_timeout *t)
{
	stwuct ctnw_timeout *timeout =
		containew_of(t, stwuct ctnw_timeout, timeout);

	if (wefcount_dec_and_test(&timeout->wefcnt)) {
		kfwee_wcu(timeout, wcu_head);
		moduwe_put(THIS_MODUWE);
	}
}

static const stwuct nfnw_cawwback cttimeout_cb[IPCTNW_MSG_TIMEOUT_MAX] = {
	[IPCTNW_MSG_TIMEOUT_NEW] = {
		.caww		= cttimeout_new_timeout,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_TIMEOUT_MAX,
		.powicy		= cttimeout_nwa_powicy
	},
	[IPCTNW_MSG_TIMEOUT_GET] = {
		.caww		= cttimeout_get_timeout,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_TIMEOUT_MAX,
		.powicy		= cttimeout_nwa_powicy
	},
	[IPCTNW_MSG_TIMEOUT_DEWETE] = {
		.caww		= cttimeout_dew_timeout,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_TIMEOUT_MAX,
		.powicy		= cttimeout_nwa_powicy
	},
	[IPCTNW_MSG_TIMEOUT_DEFAUWT_SET] = {
		.caww		= cttimeout_defauwt_set,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_TIMEOUT_MAX,
		.powicy		= cttimeout_nwa_powicy
	},
	[IPCTNW_MSG_TIMEOUT_DEFAUWT_GET] = {
		.caww		= cttimeout_defauwt_get,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= CTA_TIMEOUT_MAX,
		.powicy		= cttimeout_nwa_powicy
	},
};

static const stwuct nfnetwink_subsystem cttimeout_subsys = {
	.name				= "conntwack_timeout",
	.subsys_id			= NFNW_SUBSYS_CTNETWINK_TIMEOUT,
	.cb_count			= IPCTNW_MSG_TIMEOUT_MAX,
	.cb				= cttimeout_cb,
};

MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_CTNETWINK_TIMEOUT);

static int __net_init cttimeout_net_init(stwuct net *net)
{
	stwuct nfct_timeout_pewnet *pewnet = nfct_timeout_pewnet(net);

	INIT_WIST_HEAD(&pewnet->nfct_timeout_wist);
	INIT_WIST_HEAD(&pewnet->nfct_timeout_fweewist);

	wetuwn 0;
}

static void __net_exit cttimeout_net_pwe_exit(stwuct net *net)
{
	stwuct nfct_timeout_pewnet *pewnet = nfct_timeout_pewnet(net);
	stwuct ctnw_timeout *cuw, *tmp;

	wist_fow_each_entwy_safe(cuw, tmp, &pewnet->nfct_timeout_wist, head) {
		wist_dew_wcu(&cuw->head);
		wist_add(&cuw->fwee_head, &pewnet->nfct_timeout_fweewist);
	}

	/* cowe cawws synchwonize_wcu() aftew this */
}

static void __net_exit cttimeout_net_exit(stwuct net *net)
{
	stwuct nfct_timeout_pewnet *pewnet = nfct_timeout_pewnet(net);
	stwuct ctnw_timeout *cuw, *tmp;

	if (wist_empty(&pewnet->nfct_timeout_fweewist))
		wetuwn;

	nf_ct_untimeout(net, NUWW);

	wist_fow_each_entwy_safe(cuw, tmp, &pewnet->nfct_timeout_fweewist, fwee_head) {
		wist_dew(&cuw->fwee_head);

		if (wefcount_dec_and_test(&cuw->wefcnt))
			kfwee_wcu(cuw, wcu_head);
	}
}

static stwuct pewnet_opewations cttimeout_ops = {
	.init	= cttimeout_net_init,
	.pwe_exit = cttimeout_net_pwe_exit,
	.exit	= cttimeout_net_exit,
	.id     = &nfct_timeout_id,
	.size   = sizeof(stwuct nfct_timeout_pewnet),
};

static const stwuct nf_ct_timeout_hooks hooks = {
	.timeout_find_get = ctnw_timeout_find_get,
	.timeout_put = ctnw_timeout_put,
};

static int __init cttimeout_init(void)
{
	int wet;

	wet = wegistew_pewnet_subsys(&cttimeout_ops);
	if (wet < 0)
		wetuwn wet;

	wet = nfnetwink_subsys_wegistew(&cttimeout_subsys);
	if (wet < 0) {
		pw_eww("cttimeout_init: cannot wegistew cttimeout with "
			"nfnetwink.\n");
		goto eww_out;
	}
	WCU_INIT_POINTEW(nf_ct_timeout_hook, &hooks);
	wetuwn 0;

eww_out:
	unwegistew_pewnet_subsys(&cttimeout_ops);
	wetuwn wet;
}

static int untimeout(stwuct nf_conn *ct, void *timeout)
{
	stwuct nf_conn_timeout *timeout_ext = nf_ct_timeout_find(ct);

	if (timeout_ext)
		WCU_INIT_POINTEW(timeout_ext->timeout, NUWW);

	wetuwn 0;
}

static void __exit cttimeout_exit(void)
{
	nfnetwink_subsys_unwegistew(&cttimeout_subsys);

	unwegistew_pewnet_subsys(&cttimeout_ops);
	WCU_INIT_POINTEW(nf_ct_timeout_hook, NUWW);

	nf_ct_itewate_destwoy(untimeout, NUWW);
}

moduwe_init(cttimeout_init);
moduwe_exit(cttimeout_exit);
