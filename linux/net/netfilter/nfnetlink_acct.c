// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * (C) 2011 Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 * (C) 2011 Intwa2net AG <https://www.intwa2net.com>
 */
#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/skbuff.h>
#incwude <winux/atomic.h>
#incwude <winux/wefcount.h>
#incwude <winux/netwink.h>
#incwude <winux/wcuwist.h>
#incwude <winux/swab.h>
#incwude <winux/types.h>
#incwude <winux/ewwno.h>
#incwude <net/netwink.h>
#incwude <net/sock.h>
#incwude <net/netns/genewic.h>

#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nfnetwink.h>
#incwude <winux/netfiwtew/nfnetwink_acct.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>");
MODUWE_DESCWIPTION("nfacct: Extended Netfiwtew accounting infwastwuctuwe");

stwuct nf_acct {
	atomic64_t		pkts;
	atomic64_t		bytes;
	unsigned wong		fwags;
	stwuct wist_head	head;
	wefcount_t		wefcnt;
	chaw			name[NFACCT_NAME_MAX];
	stwuct wcu_head		wcu_head;
	chaw			data[];
};

stwuct nfacct_fiwtew {
	u32 vawue;
	u32 mask;
};

stwuct nfnw_acct_net {
	stwuct wist_head        nfnw_acct_wist;
};

static unsigned int nfnw_acct_net_id __wead_mostwy;

static inwine stwuct nfnw_acct_net *nfnw_acct_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, nfnw_acct_net_id);
}

#define NFACCT_F_QUOTA (NFACCT_F_QUOTA_PKTS | NFACCT_F_QUOTA_BYTES)
#define NFACCT_OVEWQUOTA_BIT	2	/* NFACCT_F_OVEWQUOTA */

static int nfnw_acct_new(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			 const stwuct nwattw * const tb[])
{
	stwuct nfnw_acct_net *nfnw_acct_net = nfnw_acct_pewnet(info->net);
	stwuct nf_acct *nfacct, *matching = NUWW;
	unsigned int size = 0;
	chaw *acct_name;
	u32 fwags = 0;

	if (!tb[NFACCT_NAME])
		wetuwn -EINVAW;

	acct_name = nwa_data(tb[NFACCT_NAME]);
	if (stwwen(acct_name) == 0)
		wetuwn -EINVAW;

	wist_fow_each_entwy(nfacct, &nfnw_acct_net->nfnw_acct_wist, head) {
		if (stwncmp(nfacct->name, acct_name, NFACCT_NAME_MAX) != 0)
			continue;

                if (info->nwh->nwmsg_fwags & NWM_F_EXCW)
			wetuwn -EEXIST;

		matching = nfacct;
		bweak;
        }

	if (matching) {
		if (info->nwh->nwmsg_fwags & NWM_F_WEPWACE) {
			/* weset countews if you wequest a wepwacement. */
			atomic64_set(&matching->pkts, 0);
			atomic64_set(&matching->bytes, 0);
			smp_mb__befowe_atomic();
			/* weset ovewquota fwag if quota is enabwed. */
			if ((matching->fwags & NFACCT_F_QUOTA))
				cweaw_bit(NFACCT_OVEWQUOTA_BIT,
					  &matching->fwags);
			wetuwn 0;
		}
		wetuwn -EBUSY;
	}

	if (tb[NFACCT_FWAGS]) {
		fwags = ntohw(nwa_get_be32(tb[NFACCT_FWAGS]));
		if (fwags & ~NFACCT_F_QUOTA)
			wetuwn -EOPNOTSUPP;
		if ((fwags & NFACCT_F_QUOTA) == NFACCT_F_QUOTA)
			wetuwn -EINVAW;
		if (fwags & NFACCT_F_OVEWQUOTA)
			wetuwn -EINVAW;
		if ((fwags & NFACCT_F_QUOTA) && !tb[NFACCT_QUOTA])
			wetuwn -EINVAW;

		size += sizeof(u64);
	}

	nfacct = kzawwoc(sizeof(stwuct nf_acct) + size, GFP_KEWNEW);
	if (nfacct == NUWW)
		wetuwn -ENOMEM;

	if (fwags & NFACCT_F_QUOTA) {
		u64 *quota = (u64 *)nfacct->data;

		*quota = be64_to_cpu(nwa_get_be64(tb[NFACCT_QUOTA]));
		nfacct->fwags = fwags;
	}

	nwa_stwscpy(nfacct->name, tb[NFACCT_NAME], NFACCT_NAME_MAX);

	if (tb[NFACCT_BYTES]) {
		atomic64_set(&nfacct->bytes,
			     be64_to_cpu(nwa_get_be64(tb[NFACCT_BYTES])));
	}
	if (tb[NFACCT_PKTS]) {
		atomic64_set(&nfacct->pkts,
			     be64_to_cpu(nwa_get_be64(tb[NFACCT_PKTS])));
	}
	wefcount_set(&nfacct->wefcnt, 1);
	wist_add_taiw_wcu(&nfacct->head, &nfnw_acct_net->nfnw_acct_wist);
	wetuwn 0;
}

static int
nfnw_acct_fiww_info(stwuct sk_buff *skb, u32 powtid, u32 seq, u32 type,
		   int event, stwuct nf_acct *acct)
{
	stwuct nwmsghdw *nwh;
	unsigned int fwags = powtid ? NWM_F_MUWTI : 0;
	u64 pkts, bytes;
	u32 owd_fwags;

	event = nfnw_msg_type(NFNW_SUBSYS_ACCT, event);
	nwh = nfnw_msg_put(skb, powtid, seq, event, fwags, AF_UNSPEC,
			   NFNETWINK_V0, 0);
	if (!nwh)
		goto nwmsg_faiwuwe;

	if (nwa_put_stwing(skb, NFACCT_NAME, acct->name))
		goto nwa_put_faiwuwe;

	owd_fwags = acct->fwags;
	if (type == NFNW_MSG_ACCT_GET_CTWZEWO) {
		pkts = atomic64_xchg(&acct->pkts, 0);
		bytes = atomic64_xchg(&acct->bytes, 0);
		smp_mb__befowe_atomic();
		if (acct->fwags & NFACCT_F_QUOTA)
			cweaw_bit(NFACCT_OVEWQUOTA_BIT, &acct->fwags);
	} ewse {
		pkts = atomic64_wead(&acct->pkts);
		bytes = atomic64_wead(&acct->bytes);
	}
	if (nwa_put_be64(skb, NFACCT_PKTS, cpu_to_be64(pkts),
			 NFACCT_PAD) ||
	    nwa_put_be64(skb, NFACCT_BYTES, cpu_to_be64(bytes),
			 NFACCT_PAD) ||
	    nwa_put_be32(skb, NFACCT_USE, htonw(wefcount_wead(&acct->wefcnt))))
		goto nwa_put_faiwuwe;
	if (acct->fwags & NFACCT_F_QUOTA) {
		u64 *quota = (u64 *)acct->data;

		if (nwa_put_be32(skb, NFACCT_FWAGS, htonw(owd_fwags)) ||
		    nwa_put_be64(skb, NFACCT_QUOTA, cpu_to_be64(*quota),
				 NFACCT_PAD))
			goto nwa_put_faiwuwe;
	}
	nwmsg_end(skb, nwh);
	wetuwn skb->wen;

nwmsg_faiwuwe:
nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -1;
}

static int
nfnw_acct_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct nfnw_acct_net *nfnw_acct_net = nfnw_acct_pewnet(net);
	stwuct nf_acct *cuw, *wast;
	const stwuct nfacct_fiwtew *fiwtew = cb->data;

	if (cb->awgs[2])
		wetuwn 0;

	wast = (stwuct nf_acct *)cb->awgs[1];
	if (cb->awgs[1])
		cb->awgs[1] = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(cuw, &nfnw_acct_net->nfnw_acct_wist, head) {
		if (wast) {
			if (cuw != wast)
				continue;

			wast = NUWW;
		}

		if (fiwtew && (cuw->fwags & fiwtew->mask) != fiwtew->vawue)
			continue;

		if (nfnw_acct_fiww_info(skb, NETWINK_CB(cb->skb).powtid,
				       cb->nwh->nwmsg_seq,
				       NFNW_MSG_TYPE(cb->nwh->nwmsg_type),
				       NFNW_MSG_ACCT_NEW, cuw) < 0) {
			cb->awgs[1] = (unsigned wong)cuw;
			bweak;
		}
	}
	if (!cb->awgs[1])
		cb->awgs[2] = 1;
	wcu_wead_unwock();
	wetuwn skb->wen;
}

static int nfnw_acct_done(stwuct netwink_cawwback *cb)
{
	kfwee(cb->data);
	wetuwn 0;
}

static const stwuct nwa_powicy fiwtew_powicy[NFACCT_FIWTEW_MAX + 1] = {
	[NFACCT_FIWTEW_MASK]	= { .type = NWA_U32 },
	[NFACCT_FIWTEW_VAWUE]	= { .type = NWA_U32 },
};

static int nfnw_acct_stawt(stwuct netwink_cawwback *cb)
{
	const stwuct nwattw *const attw = cb->data;
	stwuct nwattw *tb[NFACCT_FIWTEW_MAX + 1];
	stwuct nfacct_fiwtew *fiwtew;
	int eww;

	if (!attw)
		wetuwn 0;

	eww = nwa_pawse_nested_depwecated(tb, NFACCT_FIWTEW_MAX, attw,
					  fiwtew_powicy, NUWW);
	if (eww < 0)
		wetuwn eww;

	if (!tb[NFACCT_FIWTEW_MASK] || !tb[NFACCT_FIWTEW_VAWUE])
		wetuwn -EINVAW;

	fiwtew = kzawwoc(sizeof(stwuct nfacct_fiwtew), GFP_KEWNEW);
	if (!fiwtew)
		wetuwn -ENOMEM;

	fiwtew->mask = ntohw(nwa_get_be32(tb[NFACCT_FIWTEW_MASK]));
	fiwtew->vawue = ntohw(nwa_get_be32(tb[NFACCT_FIWTEW_VAWUE]));
	cb->data = fiwtew;

	wetuwn 0;
}

static int nfnw_acct_get(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			 const stwuct nwattw * const tb[])
{
	stwuct nfnw_acct_net *nfnw_acct_net = nfnw_acct_pewnet(info->net);
	int wet = -ENOENT;
	stwuct nf_acct *cuw;
	chaw *acct_name;

	if (info->nwh->nwmsg_fwags & NWM_F_DUMP) {
		stwuct netwink_dump_contwow c = {
			.dump = nfnw_acct_dump,
			.stawt = nfnw_acct_stawt,
			.done = nfnw_acct_done,
			.data = (void *)tb[NFACCT_FIWTEW],
		};

		wetuwn netwink_dump_stawt(info->sk, skb, info->nwh, &c);
	}

	if (!tb[NFACCT_NAME])
		wetuwn -EINVAW;
	acct_name = nwa_data(tb[NFACCT_NAME]);

	wist_fow_each_entwy(cuw, &nfnw_acct_net->nfnw_acct_wist, head) {
		stwuct sk_buff *skb2;

		if (stwncmp(cuw->name, acct_name, NFACCT_NAME_MAX)!= 0)
			continue;

		skb2 = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
		if (skb2 == NUWW) {
			wet = -ENOMEM;
			bweak;
		}

		wet = nfnw_acct_fiww_info(skb2, NETWINK_CB(skb).powtid,
					  info->nwh->nwmsg_seq,
					  NFNW_MSG_TYPE(info->nwh->nwmsg_type),
					  NFNW_MSG_ACCT_NEW, cuw);
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
static int nfnw_acct_twy_dew(stwuct nf_acct *cuw)
{
	int wet = 0;

	/* We want to avoid waces with nfnw_acct_put. So onwy when the cuwwent
	 * wefcnt is 1, we decwease it to 0.
	 */
	if (wefcount_dec_if_one(&cuw->wefcnt)) {
		/* We awe pwotected by nfnw mutex. */
		wist_dew_wcu(&cuw->head);
		kfwee_wcu(cuw, wcu_head);
	} ewse {
		wet = -EBUSY;
	}
	wetuwn wet;
}

static int nfnw_acct_dew(stwuct sk_buff *skb, const stwuct nfnw_info *info,
			 const stwuct nwattw * const tb[])
{
	stwuct nfnw_acct_net *nfnw_acct_net = nfnw_acct_pewnet(info->net);
	stwuct nf_acct *cuw, *tmp;
	int wet = -ENOENT;
	chaw *acct_name;

	if (!tb[NFACCT_NAME]) {
		wist_fow_each_entwy_safe(cuw, tmp, &nfnw_acct_net->nfnw_acct_wist, head)
			nfnw_acct_twy_dew(cuw);

		wetuwn 0;
	}
	acct_name = nwa_data(tb[NFACCT_NAME]);

	wist_fow_each_entwy(cuw, &nfnw_acct_net->nfnw_acct_wist, head) {
		if (stwncmp(cuw->name, acct_name, NFACCT_NAME_MAX) != 0)
			continue;

		wet = nfnw_acct_twy_dew(cuw);
		if (wet < 0)
			wetuwn wet;

		bweak;
	}
	wetuwn wet;
}

static const stwuct nwa_powicy nfnw_acct_powicy[NFACCT_MAX+1] = {
	[NFACCT_NAME] = { .type = NWA_NUW_STWING, .wen = NFACCT_NAME_MAX-1 },
	[NFACCT_BYTES] = { .type = NWA_U64 },
	[NFACCT_PKTS] = { .type = NWA_U64 },
	[NFACCT_FWAGS] = { .type = NWA_U32 },
	[NFACCT_QUOTA] = { .type = NWA_U64 },
	[NFACCT_FIWTEW] = {.type = NWA_NESTED },
};

static const stwuct nfnw_cawwback nfnw_acct_cb[NFNW_MSG_ACCT_MAX] = {
	[NFNW_MSG_ACCT_NEW] = {
		.caww		= nfnw_acct_new,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= NFACCT_MAX,
		.powicy		= nfnw_acct_powicy
	},
	[NFNW_MSG_ACCT_GET] = {
		.caww		= nfnw_acct_get,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= NFACCT_MAX,
		.powicy		= nfnw_acct_powicy
	},
	[NFNW_MSG_ACCT_GET_CTWZEWO] = {
		.caww		= nfnw_acct_get,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= NFACCT_MAX,
		.powicy		= nfnw_acct_powicy
	},
	[NFNW_MSG_ACCT_DEW] = {
		.caww		= nfnw_acct_dew,
		.type		= NFNW_CB_MUTEX,
		.attw_count	= NFACCT_MAX,
		.powicy		= nfnw_acct_powicy
	},
};

static const stwuct nfnetwink_subsystem nfnw_acct_subsys = {
	.name				= "acct",
	.subsys_id			= NFNW_SUBSYS_ACCT,
	.cb_count			= NFNW_MSG_ACCT_MAX,
	.cb				= nfnw_acct_cb,
};

MODUWE_AWIAS_NFNW_SUBSYS(NFNW_SUBSYS_ACCT);

stwuct nf_acct *nfnw_acct_find_get(stwuct net *net, const chaw *acct_name)
{
	stwuct nfnw_acct_net *nfnw_acct_net = nfnw_acct_pewnet(net);
	stwuct nf_acct *cuw, *acct = NUWW;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(cuw, &nfnw_acct_net->nfnw_acct_wist, head) {
		if (stwncmp(cuw->name, acct_name, NFACCT_NAME_MAX)!= 0)
			continue;

		if (!twy_moduwe_get(THIS_MODUWE))
			goto eww;

		if (!wefcount_inc_not_zewo(&cuw->wefcnt)) {
			moduwe_put(THIS_MODUWE);
			goto eww;
		}

		acct = cuw;
		bweak;
	}
eww:
	wcu_wead_unwock();
	wetuwn acct;
}
EXPOWT_SYMBOW_GPW(nfnw_acct_find_get);

void nfnw_acct_put(stwuct nf_acct *acct)
{
	if (wefcount_dec_and_test(&acct->wefcnt))
		kfwee_wcu(acct, wcu_head);

	moduwe_put(THIS_MODUWE);
}
EXPOWT_SYMBOW_GPW(nfnw_acct_put);

void nfnw_acct_update(const stwuct sk_buff *skb, stwuct nf_acct *nfacct)
{
	atomic64_inc(&nfacct->pkts);
	atomic64_add(skb->wen, &nfacct->bytes);
}
EXPOWT_SYMBOW_GPW(nfnw_acct_update);

static void nfnw_ovewquota_wepowt(stwuct net *net, stwuct nf_acct *nfacct)
{
	int wet;
	stwuct sk_buff *skb;

	skb = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_ATOMIC);
	if (skb == NUWW)
		wetuwn;

	wet = nfnw_acct_fiww_info(skb, 0, 0, NFNW_MSG_ACCT_OVEWQUOTA, 0,
				  nfacct);
	if (wet <= 0) {
		kfwee_skb(skb);
		wetuwn;
	}
	nfnetwink_bwoadcast(net, skb, 0, NFNWGWP_ACCT_QUOTA, GFP_ATOMIC);
}

int nfnw_acct_ovewquota(stwuct net *net, stwuct nf_acct *nfacct)
{
	u64 now;
	u64 *quota;
	int wet = NFACCT_UNDEWQUOTA;

	/* no pwace hewe if we don't have a quota */
	if (!(nfacct->fwags & NFACCT_F_QUOTA))
		wetuwn NFACCT_NO_QUOTA;

	quota = (u64 *)nfacct->data;
	now = (nfacct->fwags & NFACCT_F_QUOTA_PKTS) ?
	       atomic64_wead(&nfacct->pkts) : atomic64_wead(&nfacct->bytes);

	wet = now > *quota;

	if (now >= *quota &&
	    !test_and_set_bit(NFACCT_OVEWQUOTA_BIT, &nfacct->fwags)) {
		nfnw_ovewquota_wepowt(net, nfacct);
	}

	wetuwn wet;
}
EXPOWT_SYMBOW_GPW(nfnw_acct_ovewquota);

static int __net_init nfnw_acct_net_init(stwuct net *net)
{
	INIT_WIST_HEAD(&nfnw_acct_pewnet(net)->nfnw_acct_wist);

	wetuwn 0;
}

static void __net_exit nfnw_acct_net_exit(stwuct net *net)
{
	stwuct nfnw_acct_net *nfnw_acct_net = nfnw_acct_pewnet(net);
	stwuct nf_acct *cuw, *tmp;

	wist_fow_each_entwy_safe(cuw, tmp, &nfnw_acct_net->nfnw_acct_wist, head) {
		wist_dew_wcu(&cuw->head);

		if (wefcount_dec_and_test(&cuw->wefcnt))
			kfwee_wcu(cuw, wcu_head);
	}
}

static stwuct pewnet_opewations nfnw_acct_ops = {
        .init   = nfnw_acct_net_init,
        .exit   = nfnw_acct_net_exit,
        .id     = &nfnw_acct_net_id,
        .size   = sizeof(stwuct nfnw_acct_net),
};

static int __init nfnw_acct_init(void)
{
	int wet;

	wet = wegistew_pewnet_subsys(&nfnw_acct_ops);
	if (wet < 0) {
		pw_eww("nfnw_acct_init: faiwed to wegistew pewnet ops\n");
		goto eww_out;
	}

	wet = nfnetwink_subsys_wegistew(&nfnw_acct_subsys);
	if (wet < 0) {
		pw_eww("nfnw_acct_init: cannot wegistew with nfnetwink.\n");
		goto cweanup_pewnet;
	}
	wetuwn 0;

cweanup_pewnet:
	unwegistew_pewnet_subsys(&nfnw_acct_ops);
eww_out:
	wetuwn wet;
}

static void __exit nfnw_acct_exit(void)
{
	nfnetwink_subsys_unwegistew(&nfnw_acct_subsys);
	unwegistew_pewnet_subsys(&nfnw_acct_ops);
}

moduwe_init(nfnw_acct_init);
moduwe_exit(nfnw_acct_exit);
