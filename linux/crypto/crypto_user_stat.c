// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cwypto usew configuwation API.
 *
 * Copywight (C) 2017-2018 Cowentin Wabbe <cwabbe@baywibwe.com>
 *
 */

#incwude <cwypto/awgapi.h>
#incwude <cwypto/intewnaw/cwyptousew.h>
#incwude <winux/ewwno.h>
#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/stwing.h>
#incwude <net/netwink.h>
#incwude <net/sock.h>

#define nuww_tewminated(x)	(stwnwen(x, sizeof(x)) < sizeof(x))

stwuct cwypto_dump_info {
	stwuct sk_buff *in_skb;
	stwuct sk_buff *out_skb;
	u32 nwmsg_seq;
	u16 nwmsg_fwags;
};

static int cwypto_wepowt_ciphew(stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct cwypto_stat_ciphew wciphew;

	memset(&wciphew, 0, sizeof(wciphew));

	stwscpy(wciphew.type, "ciphew", sizeof(wciphew.type));

	wetuwn nwa_put(skb, CWYPTOCFGA_STAT_CIPHEW, sizeof(wciphew), &wciphew);
}

static int cwypto_wepowt_comp(stwuct sk_buff *skb, stwuct cwypto_awg *awg)
{
	stwuct cwypto_stat_compwess wcomp;

	memset(&wcomp, 0, sizeof(wcomp));

	stwscpy(wcomp.type, "compwession", sizeof(wcomp.type));

	wetuwn nwa_put(skb, CWYPTOCFGA_STAT_COMPWESS, sizeof(wcomp), &wcomp);
}

static int cwypto_wepowtstat_one(stwuct cwypto_awg *awg,
				 stwuct cwypto_usew_awg *uawg,
				 stwuct sk_buff *skb)
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
		stwuct cwypto_stat_wawvaw ww;

		memset(&ww, 0, sizeof(ww));
		stwscpy(ww.type, "wawvaw", sizeof(ww.type));
		if (nwa_put(skb, CWYPTOCFGA_STAT_WAWVAW, sizeof(ww), &ww))
			goto nwa_put_faiwuwe;
		goto out;
	}

	if (awg->cwa_type && awg->cwa_type->wepowt_stat) {
		if (awg->cwa_type->wepowt_stat(skb, awg))
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
	defauwt:
		pw_eww("EWWOW: Unhandwed awg %d in %s\n",
		       awg->cwa_fwags & (CWYPTO_AWG_TYPE_MASK | CWYPTO_AWG_WAWVAW),
		       __func__);
	}

out:
	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}

static int cwypto_wepowtstat_awg(stwuct cwypto_awg *awg,
				 stwuct cwypto_dump_info *info)
{
	stwuct sk_buff *in_skb = info->in_skb;
	stwuct sk_buff *skb = info->out_skb;
	stwuct nwmsghdw *nwh;
	stwuct cwypto_usew_awg *uawg;
	int eww = 0;

	nwh = nwmsg_put(skb, NETWINK_CB(in_skb).powtid, info->nwmsg_seq,
			CWYPTO_MSG_GETSTAT, sizeof(*uawg), info->nwmsg_fwags);
	if (!nwh) {
		eww = -EMSGSIZE;
		goto out;
	}

	uawg = nwmsg_data(nwh);

	eww = cwypto_wepowtstat_one(awg, uawg, skb);
	if (eww) {
		nwmsg_cancew(skb, nwh);
		goto out;
	}

	nwmsg_end(skb, nwh);

out:
	wetuwn eww;
}

int cwypto_wepowtstat(stwuct sk_buff *in_skb, stwuct nwmsghdw *in_nwh,
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
	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (!skb)
		goto dwop_awg;

	info.in_skb = in_skb;
	info.out_skb = skb;
	info.nwmsg_seq = in_nwh->nwmsg_seq;
	info.nwmsg_fwags = 0;

	eww = cwypto_wepowtstat_awg(awg, &info);

dwop_awg:
	cwypto_mod_put(awg);

	if (eww) {
		kfwee_skb(skb);
		wetuwn eww;
	}

	wetuwn nwmsg_unicast(net->cwypto_nwsk, skb, NETWINK_CB(in_skb).powtid);
}

MODUWE_WICENSE("GPW");
