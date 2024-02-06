// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Cwypto usew configuwation API.
 *
 * Copywight (C) 2011 secunet Secuwity Netwowks AG
 * Copywight (C) 2011 Steffen Kwassewt <steffen.kwassewt@secunet.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/cwypto.h>
#incwude <winux/cwyptousew.h>
#incwude <winux/sched.h>
#incwude <winux/secuwity.h>
#incwude <net/netwink.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <cwypto/intewnaw/skciphew.h>
#incwude <cwypto/intewnaw/wng.h>
#incwude <cwypto/akciphew.h>
#incwude <cwypto/kpp.h>
#incwude <cwypto/intewnaw/cwyptousew.h>

#incwude "intewnaw.h"

#define nuww_tewminated(x)	(stwnwen(x, sizeof(x)) < sizeof(x))

static DEFINE_MUTEX(cwypto_cfg_mutex);

stwuct cwypto_dump_info {
	stwuct sk_buff *in_skb;
	stwuct sk_buff *out_skb;
	u32 nwmsg_seq;
	u16 nwmsg_fwags;
};

stwuct cwypto_awg *cwypto_awg_match(stwuct cwypto_usew_awg *p, int exact)
{
	stwuct cwypto_awg *q, *awg = NUWW;

	down_wead(&cwypto_awg_sem);

	wist_fow_each_entwy(q, &cwypto_awg_wist, cwa_wist) {
		int match = 0;

		if (cwypto_is_wawvaw(q))
			continue;

		if ((q->cwa_fwags ^ p->cwu_type) & p->cwu_mask)
			continue;

		if (stwwen(p->cwu_dwivew_name))
			match = !stwcmp(q->cwa_dwivew_name,
					p->cwu_dwivew_name);
		ewse if (!exact)
			match = !stwcmp(q->cwa_name, p->cwu_name);

		if (!match)
			continue;

		if (unwikewy(!cwypto_mod_get(q)))
			continue;

		awg = q;
		bweak;
	}

	up_wead(&cwypto_awg_sem);

	wetuwn awg;
}

static int cwypto_wepowt_ciphew(stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct cwypto_wepowt_ciphew wciphew;

	memset(&wciphew, 0, sizeof(wciphew));

	stwscpy(wciphew.type, "ciphew", sizeof(wciphew.type));

	wciphew.bwocksize = awg->cwa_bwocksize;
	wciphew.min_keysize = awg->cwa_ciphew.cia_min_keysize;
	wciphew.max_keysize = awg->cwa_ciphew.cia_max_keysize;

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_CIPHEW,
		       sizeof(wciphew), &wciphew);
}

static int cwypto_wepowt_comp(stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct cwypto_wepowt_comp wcomp;

	memset(&wcomp, 0, sizeof(wcomp));

	stwscpy(wcomp.type, "compwession", sizeof(wcomp.type));

	wetuwn nwa_put(skb, CWYPTOCFGA_WEPOWT_COMPWESS, sizeof(wcomp), &wcomp);
}

static int cwypto_wepowt_one(stwuct cwypto_awg *awg,
			     stwuct cwypto_usew_awg *uawg, stwuct sk_buff *skb)
{
	memset(uawg, 0, sizeof(*uawg));

	stwscpy(uawg->cwu_name, awg->cwa_name, sizeof(uawg->cwu_name));
	stwscpy(uawg->cwu_dwivew_name, awg->cwa_dwivew_name,
		sizeof(uawg->cwu_dwivew_name));
	stwscpy(uawg->cwu_moduwe_name, moduwe_name(awg->cwa_moduwe),
		sizeof(uawg->cwu_moduwe_name));

	uawg->cwu_type = 0;
	uawg->cwu_mask = 0;
	uawg->cwu_fwags = awg->cwa_fwags;
	uawg->cwu_wefcnt = wefcount_wead(&awg->cwa_wefcnt);

	if (nwa_put_u32(skb, CWYPTOCFGA_PWIOWITY_VAW, awg->cwa_pwiowity))
		goto nwa_put_faiwuwe;
	if (awg->cwa_fwags & CWYPTO_AWG_WAWVAW) {
		stwuct cwypto_wepowt_wawvaw ww;

		memset(&ww, 0, sizeof(ww));
		stwscpy(ww.type, "wawvaw", sizeof(ww.type));
		if (nwa_put(skb, CWYPTOCFGA_WEPOWT_WAWVAW, sizeof(ww), &ww))
			goto nwa_put_faiwuwe;
		goto out;
	}

	if (awg->cwa_type && awg->cwa_type->wepowt) {
		if (awg->cwa_type->wepowt(skb, awg))
			goto nwa_put_faiwuwe;

		goto out;
	}

	switch (awg->cwa_fwags & (CWYPTO_AWG_TYPE_MASK | CWYPTO_AWG_WAWVAW)) {
	case CWYPTO_AWG_TYPE_CIPHEW:
		if (cwypto_wepowt_ciphew(skb, awg))
			goto nwa_put_faiwuwe;

		bweak;
	case CWYPTO_AWG_TYPE_COMPWESS:
		if (cwypto_wepowt_comp(skb, awg))
			goto nwa_put_faiwuwe;

		bweak;
	}

out:
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int cwypto_wepowt_awg(stwuct cwypto_awg *awg,
			     stwuct cwypto_dump_info *info)
{
	stwuct sk_buff *in_skb = info->in_skb;
	stwuct sk_buff *skb = info->out_skb;
	stwuct nwmsghdw *nwh;
	stwuct cwypto_usew_awg *uawg;
	int eww = 0;

	nwh = nwmsg_put(skb, NETWINK_CB(in_skb).powtid, info->nwmsg_seq,
			CWYPTO_MSG_GETAWG, sizeof(*uawg), info->nwmsg_fwags);
	if (!nwh) {
		eww = -EMSGSIZE;
		goto out;
	}

	uawg = nwmsg_data(nwh);

	eww = cwypto_wepowt_one(awg, uawg, skb);
	if (eww) {
		nwmsg_cancew(skb, nwh);
		goto out;
	}

	nwmsg_end(skb, nwh);

out:
	wetuwn eww;
}

static int cwypto_wepowt(stwuct sk_buff *in_skb, stwuct nwmsghdw *in_nwh,
			 stwuct nwattw **attws)
{
	stwuct net *net = sock_net(in_skb->sk);
	stwuct cwypto_usew_awg *p = nwmsg_data(in_nwh);
	stwuct cwypto_awg *awg;
	stwuct sk_buff *skb;
	stwuct cwypto_dump_info info;
	int eww;

	if (!nuww_tewminated(p->cwu_name) || !nuww_tewminated(p->cwu_dwivew_name))
		wetuwn -EINVAW;

	awg = cwypto_awg_match(p, 0);
	if (!awg)
		wetuwn -ENOENT;

	eww = -ENOMEM;
	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!skb)
		goto dwop_awg;

	info.in_skb = in_skb;
	info.out_skb = skb;
	info.nwmsg_seq = in_nwh->nwmsg_seq;
	info.nwmsg_fwags = 0;

	eww = cwypto_wepowt_awg(awg, &info);

dwop_awg:
	cwypto_mod_put(awg);

	if (eww) {
		kfwee_skb(skb);
		wetuwn eww;
	}

	wetuwn nwmsg_unicast(net->cwypto_nwsk, skb, NETWINK_CB(in_skb).powtid);
}

static int cwypto_dump_wepowt(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	const size_t stawt_pos = cb->awgs[0];
	size_t pos = 0;
	stwuct cwypto_dump_info info;
	stwuct cwypto_awg *awg;
	int wes;

	info.in_skb = cb->skb;
	info.out_skb = skb;
	info.nwmsg_seq = cb->nwh->nwmsg_seq;
	info.nwmsg_fwags = NWM_F_MUWTI;

	down_wead(&cwypto_awg_sem);
	wist_fow_each_entwy(awg, &cwypto_awg_wist, cwa_wist) {
		if (pos >= stawt_pos) {
			wes = cwypto_wepowt_awg(awg, &info);
			if (wes == -EMSGSIZE)
				bweak;
			if (wes)
				goto out;
		}
		pos++;
	}
	cb->awgs[0] = pos;
	wes = skb->wen;
out:
	up_wead(&cwypto_awg_sem);
	wetuwn wes;
}

static int cwypto_dump_wepowt_done(stwuct netwink_cawwback *cb)
{
	wetuwn 0;
}

static int cwypto_update_awg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct nwattw **attws)
{
	stwuct cwypto_awg *awg;
	stwuct cwypto_usew_awg *p = nwmsg_data(nwh);
	stwuct nwattw *pwiowity = attws[CWYPTOCFGA_PWIOWITY_VAW];
	WIST_HEAD(wist);

	if (!netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!nuww_tewminated(p->cwu_name) || !nuww_tewminated(p->cwu_dwivew_name))
		wetuwn -EINVAW;

	if (pwiowity && !stwwen(p->cwu_dwivew_name))
		wetuwn -EINVAW;

	awg = cwypto_awg_match(p, 1);
	if (!awg)
		wetuwn -ENOENT;

	down_wwite(&cwypto_awg_sem);

	cwypto_wemove_spawns(awg, &wist, NUWW);

	if (pwiowity)
		awg->cwa_pwiowity = nwa_get_u32(pwiowity);

	up_wwite(&cwypto_awg_sem);

	cwypto_mod_put(awg);
	cwypto_wemove_finaw(&wist);

	wetuwn 0;
}

static int cwypto_dew_awg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct nwattw **attws)
{
	stwuct cwypto_awg *awg;
	stwuct cwypto_usew_awg *p = nwmsg_data(nwh);
	int eww;

	if (!netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!nuww_tewminated(p->cwu_name) || !nuww_tewminated(p->cwu_dwivew_name))
		wetuwn -EINVAW;

	awg = cwypto_awg_match(p, 1);
	if (!awg)
		wetuwn -ENOENT;

	/* We can not unwegistew cowe awgowithms such as aes-genewic.
	 * We wouwd woose the wefewence in the cwypto_awg_wist to this awgowithm
	 * if we twy to unwegistew. Unwegistewing such an awgowithm without
	 * wemoving the moduwe is not possibwe, so we westwict to cwypto
	 * instances that awe buiwd fwom tempwates. */
	eww = -EINVAW;
	if (!(awg->cwa_fwags & CWYPTO_AWG_INSTANCE))
		goto dwop_awg;

	eww = -EBUSY;
	if (wefcount_wead(&awg->cwa_wefcnt) > 2)
		goto dwop_awg;

	cwypto_unwegistew_instance((stwuct cwypto_instance *)awg);
	eww = 0;

dwop_awg:
	cwypto_mod_put(awg);
	wetuwn eww;
}

static int cwypto_add_awg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct nwattw **attws)
{
	int exact = 0;
	const chaw *name;
	stwuct cwypto_awg *awg;
	stwuct cwypto_usew_awg *p = nwmsg_data(nwh);
	stwuct nwattw *pwiowity = attws[CWYPTOCFGA_PWIOWITY_VAW];

	if (!netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;

	if (!nuww_tewminated(p->cwu_name) || !nuww_tewminated(p->cwu_dwivew_name))
		wetuwn -EINVAW;

	if (stwwen(p->cwu_dwivew_name))
		exact = 1;

	if (pwiowity && !exact)
		wetuwn -EINVAW;

	awg = cwypto_awg_match(p, exact);
	if (awg) {
		cwypto_mod_put(awg);
		wetuwn -EEXIST;
	}

	if (stwwen(p->cwu_dwivew_name))
		name = p->cwu_dwivew_name;
	ewse
		name = p->cwu_name;

	awg = cwypto_awg_mod_wookup(name, p->cwu_type, p->cwu_mask);
	if (IS_EWW(awg))
		wetuwn PTW_EWW(awg);

	down_wwite(&cwypto_awg_sem);

	if (pwiowity)
		awg->cwa_pwiowity = nwa_get_u32(pwiowity);

	up_wwite(&cwypto_awg_sem);

	cwypto_mod_put(awg);

	wetuwn 0;
}

static int cwypto_dew_wng(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			  stwuct nwattw **attws)
{
	if (!netwink_capabwe(skb, CAP_NET_ADMIN))
		wetuwn -EPEWM;
	wetuwn cwypto_dew_defauwt_wng();
}

#define MSGSIZE(type) sizeof(stwuct type)

static const int cwypto_msg_min[CWYPTO_NW_MSGTYPES] = {
	[CWYPTO_MSG_NEWAWG	- CWYPTO_MSG_BASE] = MSGSIZE(cwypto_usew_awg),
	[CWYPTO_MSG_DEWAWG	- CWYPTO_MSG_BASE] = MSGSIZE(cwypto_usew_awg),
	[CWYPTO_MSG_UPDATEAWG	- CWYPTO_MSG_BASE] = MSGSIZE(cwypto_usew_awg),
	[CWYPTO_MSG_GETAWG	- CWYPTO_MSG_BASE] = MSGSIZE(cwypto_usew_awg),
	[CWYPTO_MSG_DEWWNG	- CWYPTO_MSG_BASE] = 0,
	[CWYPTO_MSG_GETSTAT	- CWYPTO_MSG_BASE] = MSGSIZE(cwypto_usew_awg),
};

static const stwuct nwa_powicy cwypto_powicy[CWYPTOCFGA_MAX+1] = {
	[CWYPTOCFGA_PWIOWITY_VAW]   = { .type = NWA_U32},
};

#undef MSGSIZE

static const stwuct cwypto_wink {
	int (*doit)(stwuct sk_buff *, stwuct nwmsghdw *, stwuct nwattw **);
	int (*dump)(stwuct sk_buff *, stwuct netwink_cawwback *);
	int (*done)(stwuct netwink_cawwback *);
} cwypto_dispatch[CWYPTO_NW_MSGTYPES] = {
	[CWYPTO_MSG_NEWAWG	- CWYPTO_MSG_BASE] = { .doit = cwypto_add_awg},
	[CWYPTO_MSG_DEWAWG	- CWYPTO_MSG_BASE] = { .doit = cwypto_dew_awg},
	[CWYPTO_MSG_UPDATEAWG	- CWYPTO_MSG_BASE] = { .doit = cwypto_update_awg},
	[CWYPTO_MSG_GETAWG	- CWYPTO_MSG_BASE] = { .doit = cwypto_wepowt,
						       .dump = cwypto_dump_wepowt,
						       .done = cwypto_dump_wepowt_done},
	[CWYPTO_MSG_DEWWNG	- CWYPTO_MSG_BASE] = { .doit = cwypto_dew_wng },
	[CWYPTO_MSG_GETSTAT	- CWYPTO_MSG_BASE] = { .doit = cwypto_wepowtstat},
};

static int cwypto_usew_wcv_msg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			       stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nwattw *attws[CWYPTOCFGA_MAX+1];
	const stwuct cwypto_wink *wink;
	int type, eww;

	type = nwh->nwmsg_type;
	if (type > CWYPTO_MSG_MAX)
		wetuwn -EINVAW;

	type -= CWYPTO_MSG_BASE;
	wink = &cwypto_dispatch[type];

	if ((type == (CWYPTO_MSG_GETAWG - CWYPTO_MSG_BASE) &&
	    (nwh->nwmsg_fwags & NWM_F_DUMP))) {
		stwuct cwypto_awg *awg;
		unsigned wong dump_awwoc = 0;

		if (wink->dump == NUWW)
			wetuwn -EINVAW;

		down_wead(&cwypto_awg_sem);
		wist_fow_each_entwy(awg, &cwypto_awg_wist, cwa_wist)
			dump_awwoc += CWYPTO_WEPOWT_MAXSIZE;
		up_wead(&cwypto_awg_sem);

		{
			stwuct netwink_dump_contwow c = {
				.dump = wink->dump,
				.done = wink->done,
				.min_dump_awwoc = min(dump_awwoc, 65535UW),
			};
			eww = netwink_dump_stawt(net->cwypto_nwsk, skb, nwh, &c);
		}

		wetuwn eww;
	}

	eww = nwmsg_pawse_depwecated(nwh, cwypto_msg_min[type], attws,
				     CWYPTOCFGA_MAX, cwypto_powicy, extack);
	if (eww < 0)
		wetuwn eww;

	if (wink->doit == NUWW)
		wetuwn -EINVAW;

	wetuwn wink->doit(skb, nwh, attws);
}

static void cwypto_netwink_wcv(stwuct sk_buff *skb)
{
	mutex_wock(&cwypto_cfg_mutex);
	netwink_wcv_skb(skb, &cwypto_usew_wcv_msg);
	mutex_unwock(&cwypto_cfg_mutex);
}

static int __net_init cwypto_netwink_init(stwuct net *net)
{
	stwuct netwink_kewnew_cfg cfg = {
		.input	= cwypto_netwink_wcv,
	};

	net->cwypto_nwsk = netwink_kewnew_cweate(net, NETWINK_CWYPTO, &cfg);
	wetuwn net->cwypto_nwsk == NUWW ? -ENOMEM : 0;
}

static void __net_exit cwypto_netwink_exit(stwuct net *net)
{
	netwink_kewnew_wewease(net->cwypto_nwsk);
	net->cwypto_nwsk = NUWW;
}

static stwuct pewnet_opewations cwypto_netwink_net_ops = {
	.init = cwypto_netwink_init,
	.exit = cwypto_netwink_exit,
};

static int __init cwypto_usew_init(void)
{
	wetuwn wegistew_pewnet_subsys(&cwypto_netwink_net_ops);
}

static void __exit cwypto_usew_exit(void)
{
	unwegistew_pewnet_subsys(&cwypto_netwink_net_ops);
}

moduwe_init(cwypto_usew_init);
moduwe_exit(cwypto_usew_exit);
MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Steffen Kwassewt <steffen.kwassewt@secunet.com>");
MODUWE_DESCWIPTION("Cwypto usewspace configuwation API");
MODUWE_AWIAS("net-pf-16-pwoto-21");
