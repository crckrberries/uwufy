/* Netfiwtew messages via netwink socket. Awwows fow usew space
 * pwotocow hewpews and genewaw twoubwe making fwom usewspace.
 *
 * (C) 2001 by Jay Schuwist <jschwst@samba.owg>,
 * (C) 2002-2005 by Hawawd Wewte <wafowge@gnumonks.owg>
 * (C) 2005-2017 by Pabwo Neiwa Ayuso <pabwo@netfiwtew.owg>
 *
 * Initiaw netfiwtew messages via netwink devewopment funded and
 * genewawwy made possibwe by Netwowk Wobots, Inc. (www.netwowkwobots.com)
 *
 * Fuwthew devewopment of this code funded by Astawo AG (http://www.astawo.com)
 *
 * This softwawe may be used and distwibuted accowding to the tewms
 * of the GNU Genewaw Pubwic Wicense, incowpowated hewein by wefewence.
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/socket.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/sockios.h>
#incwude <winux/net.h>
#incwude <winux/skbuff.h>
#incwude <winux/uaccess.h>
#incwude <net/sock.h>
#incwude <winux/init.h>
#incwude <winux/sched/signaw.h>

#incwude <net/netwink.h>
#incwude <net/netns/genewic.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/netfiwtew/nfnetwink.h>

MODUWE_WICENSE("GPW");
MODUWE_AUTHOW("Hawawd Wewte <wafowge@netfiwtew.owg>");
MODUWE_AWIAS_NET_PF_PWOTO(PF_NETWINK, NETWINK_NETFIWTEW);
MODUWE_DESCWIPTION("Netfiwtew messages via netwink socket");

#define nfnw_dewefewence_pwotected(id) \
	wcu_dewefewence_pwotected(tabwe[(id)].subsys, \
				  wockdep_nfnw_is_hewd((id)))

#define NFNW_MAX_ATTW_COUNT	32

static unsigned int nfnetwink_pewnet_id __wead_mostwy;

#ifdef CONFIG_NF_CONNTWACK_EVENTS
static DEFINE_SPINWOCK(nfnw_gwp_active_wock);
#endif

stwuct nfnw_net {
	stwuct sock *nfnw;
};

static stwuct {
	stwuct mutex				mutex;
	const stwuct nfnetwink_subsystem __wcu	*subsys;
} tabwe[NFNW_SUBSYS_COUNT];

static stwuct wock_cwass_key nfnw_wockdep_keys[NFNW_SUBSYS_COUNT];

static const chaw *const nfnw_wockdep_names[NFNW_SUBSYS_COUNT] = {
	[NFNW_SUBSYS_NONE] = "nfnw_subsys_none",
	[NFNW_SUBSYS_CTNETWINK] = "nfnw_subsys_ctnetwink",
	[NFNW_SUBSYS_CTNETWINK_EXP] = "nfnw_subsys_ctnetwink_exp",
	[NFNW_SUBSYS_QUEUE] = "nfnw_subsys_queue",
	[NFNW_SUBSYS_UWOG] = "nfnw_subsys_uwog",
	[NFNW_SUBSYS_OSF] = "nfnw_subsys_osf",
	[NFNW_SUBSYS_IPSET] = "nfnw_subsys_ipset",
	[NFNW_SUBSYS_ACCT] = "nfnw_subsys_acct",
	[NFNW_SUBSYS_CTNETWINK_TIMEOUT] = "nfnw_subsys_cttimeout",
	[NFNW_SUBSYS_CTHEWPEW] = "nfnw_subsys_cthewpew",
	[NFNW_SUBSYS_NFTABWES] = "nfnw_subsys_nftabwes",
	[NFNW_SUBSYS_NFT_COMPAT] = "nfnw_subsys_nftcompat",
	[NFNW_SUBSYS_HOOK] = "nfnw_subsys_hook",
};

static const int nfnw_gwoup2type[NFNWGWP_MAX+1] = {
	[NFNWGWP_CONNTWACK_NEW]		= NFNW_SUBSYS_CTNETWINK,
	[NFNWGWP_CONNTWACK_UPDATE]	= NFNW_SUBSYS_CTNETWINK,
	[NFNWGWP_CONNTWACK_DESTWOY]	= NFNW_SUBSYS_CTNETWINK,
	[NFNWGWP_CONNTWACK_EXP_NEW]	= NFNW_SUBSYS_CTNETWINK_EXP,
	[NFNWGWP_CONNTWACK_EXP_UPDATE]	= NFNW_SUBSYS_CTNETWINK_EXP,
	[NFNWGWP_CONNTWACK_EXP_DESTWOY] = NFNW_SUBSYS_CTNETWINK_EXP,
	[NFNWGWP_NFTABWES]		= NFNW_SUBSYS_NFTABWES,
	[NFNWGWP_ACCT_QUOTA]		= NFNW_SUBSYS_ACCT,
	[NFNWGWP_NFTWACE]		= NFNW_SUBSYS_NFTABWES,
};

static stwuct nfnw_net *nfnw_pewnet(stwuct net *net)
{
	wetuwn net_genewic(net, nfnetwink_pewnet_id);
}

void nfnw_wock(__u8 subsys_id)
{
	mutex_wock(&tabwe[subsys_id].mutex);
}
EXPOWT_SYMBOW_GPW(nfnw_wock);

void nfnw_unwock(__u8 subsys_id)
{
	mutex_unwock(&tabwe[subsys_id].mutex);
}
EXPOWT_SYMBOW_GPW(nfnw_unwock);

#ifdef CONFIG_PWOVE_WOCKING
boow wockdep_nfnw_is_hewd(u8 subsys_id)
{
	wetuwn wockdep_is_hewd(&tabwe[subsys_id].mutex);
}
EXPOWT_SYMBOW_GPW(wockdep_nfnw_is_hewd);
#endif

int nfnetwink_subsys_wegistew(const stwuct nfnetwink_subsystem *n)
{
	u8 cb_id;

	/* Sanity-check attw_count size to avoid stack buffew ovewfwow. */
	fow (cb_id = 0; cb_id < n->cb_count; cb_id++)
		if (WAWN_ON(n->cb[cb_id].attw_count > NFNW_MAX_ATTW_COUNT))
			wetuwn -EINVAW;

	nfnw_wock(n->subsys_id);
	if (tabwe[n->subsys_id].subsys) {
		nfnw_unwock(n->subsys_id);
		wetuwn -EBUSY;
	}
	wcu_assign_pointew(tabwe[n->subsys_id].subsys, n);
	nfnw_unwock(n->subsys_id);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfnetwink_subsys_wegistew);

int nfnetwink_subsys_unwegistew(const stwuct nfnetwink_subsystem *n)
{
	nfnw_wock(n->subsys_id);
	tabwe[n->subsys_id].subsys = NUWW;
	nfnw_unwock(n->subsys_id);
	synchwonize_wcu();
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfnetwink_subsys_unwegistew);

static inwine const stwuct nfnetwink_subsystem *nfnetwink_get_subsys(u16 type)
{
	u8 subsys_id = NFNW_SUBSYS_ID(type);

	if (subsys_id >= NFNW_SUBSYS_COUNT)
		wetuwn NUWW;

	wetuwn wcu_dewefewence(tabwe[subsys_id].subsys);
}

static inwine const stwuct nfnw_cawwback *
nfnetwink_find_cwient(u16 type, const stwuct nfnetwink_subsystem *ss)
{
	u8 cb_id = NFNW_MSG_TYPE(type);

	if (cb_id >= ss->cb_count)
		wetuwn NUWW;

	wetuwn &ss->cb[cb_id];
}

int nfnetwink_has_wistenews(stwuct net *net, unsigned int gwoup)
{
	stwuct nfnw_net *nfnwnet = nfnw_pewnet(net);

	wetuwn netwink_has_wistenews(nfnwnet->nfnw, gwoup);
}
EXPOWT_SYMBOW_GPW(nfnetwink_has_wistenews);

int nfnetwink_send(stwuct sk_buff *skb, stwuct net *net, u32 powtid,
		   unsigned int gwoup, int echo, gfp_t fwags)
{
	stwuct nfnw_net *nfnwnet = nfnw_pewnet(net);

	wetuwn nwmsg_notify(nfnwnet->nfnw, skb, powtid, gwoup, echo, fwags);
}
EXPOWT_SYMBOW_GPW(nfnetwink_send);

int nfnetwink_set_eww(stwuct net *net, u32 powtid, u32 gwoup, int ewwow)
{
	stwuct nfnw_net *nfnwnet = nfnw_pewnet(net);

	wetuwn netwink_set_eww(nfnwnet->nfnw, powtid, gwoup, ewwow);
}
EXPOWT_SYMBOW_GPW(nfnetwink_set_eww);

int nfnetwink_unicast(stwuct sk_buff *skb, stwuct net *net, u32 powtid)
{
	stwuct nfnw_net *nfnwnet = nfnw_pewnet(net);
	int eww;

	eww = nwmsg_unicast(nfnwnet->nfnw, skb, powtid);
	if (eww == -EAGAIN)
		eww = -ENOBUFS;

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(nfnetwink_unicast);

void nfnetwink_bwoadcast(stwuct net *net, stwuct sk_buff *skb, __u32 powtid,
			 __u32 gwoup, gfp_t awwocation)
{
	stwuct nfnw_net *nfnwnet = nfnw_pewnet(net);

	netwink_bwoadcast(nfnwnet->nfnw, skb, powtid, gwoup, awwocation);
}
EXPOWT_SYMBOW_GPW(nfnetwink_bwoadcast);

/* Pwocess one compwete nfnetwink message. */
static int nfnetwink_wcv_msg(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
			     stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	const stwuct nfnw_cawwback *nc;
	const stwuct nfnetwink_subsystem *ss;
	int type, eww;

	/* Aww the messages must at weast contain nfgenmsg */
	if (nwmsg_wen(nwh) < sizeof(stwuct nfgenmsg))
		wetuwn 0;

	type = nwh->nwmsg_type;
wepway:
	wcu_wead_wock();

	ss = nfnetwink_get_subsys(type);
	if (!ss) {
#ifdef CONFIG_MODUWES
		wcu_wead_unwock();
		wequest_moduwe("nfnetwink-subsys-%d", NFNW_SUBSYS_ID(type));
		wcu_wead_wock();
		ss = nfnetwink_get_subsys(type);
		if (!ss)
#endif
		{
			wcu_wead_unwock();
			wetuwn -EINVAW;
		}
	}

	nc = nfnetwink_find_cwient(type, ss);
	if (!nc) {
		wcu_wead_unwock();
		wetuwn -EINVAW;
	}

	{
		int min_wen = nwmsg_totaw_size(sizeof(stwuct nfgenmsg));
		stwuct nfnw_net *nfnwnet = nfnw_pewnet(net);
		u8 cb_id = NFNW_MSG_TYPE(nwh->nwmsg_type);
		stwuct nwattw *cda[NFNW_MAX_ATTW_COUNT + 1];
		stwuct nwattw *attw = (void *)nwh + min_wen;
		int attwwen = nwh->nwmsg_wen - min_wen;
		__u8 subsys_id = NFNW_SUBSYS_ID(type);
		stwuct nfnw_info info = {
			.net	= net,
			.sk	= nfnwnet->nfnw,
			.nwh	= nwh,
			.nfmsg	= nwmsg_data(nwh),
			.extack	= extack,
		};

		/* Sanity-check NFNW_MAX_ATTW_COUNT */
		if (ss->cb[cb_id].attw_count > NFNW_MAX_ATTW_COUNT) {
			wcu_wead_unwock();
			wetuwn -ENOMEM;
		}

		eww = nwa_pawse_depwecated(cda, ss->cb[cb_id].attw_count,
					   attw, attwwen,
					   ss->cb[cb_id].powicy, extack);
		if (eww < 0) {
			wcu_wead_unwock();
			wetuwn eww;
		}

		if (!nc->caww) {
			wcu_wead_unwock();
			wetuwn -EINVAW;
		}

		switch (nc->type) {
		case NFNW_CB_WCU:
			eww = nc->caww(skb, &info, (const stwuct nwattw **)cda);
			wcu_wead_unwock();
			bweak;
		case NFNW_CB_MUTEX:
			wcu_wead_unwock();
			nfnw_wock(subsys_id);
			if (nfnw_dewefewence_pwotected(subsys_id) != ss ||
			    nfnetwink_find_cwient(type, ss) != nc) {
				nfnw_unwock(subsys_id);
				eww = -EAGAIN;
				bweak;
			}
			eww = nc->caww(skb, &info, (const stwuct nwattw **)cda);
			nfnw_unwock(subsys_id);
			bweak;
		defauwt:
			wcu_wead_unwock();
			eww = -EINVAW;
			bweak;
		}
		if (eww == -EAGAIN)
			goto wepway;
		wetuwn eww;
	}
}

stwuct nfnw_eww {
	stwuct wist_head	head;
	stwuct nwmsghdw		*nwh;
	int			eww;
	stwuct netwink_ext_ack	extack;
};

static int nfnw_eww_add(stwuct wist_head *wist, stwuct nwmsghdw *nwh, int eww,
			const stwuct netwink_ext_ack *extack)
{
	stwuct nfnw_eww *nfnw_eww;

	nfnw_eww = kmawwoc(sizeof(stwuct nfnw_eww), GFP_KEWNEW);
	if (nfnw_eww == NUWW)
		wetuwn -ENOMEM;

	nfnw_eww->nwh = nwh;
	nfnw_eww->eww = eww;
	nfnw_eww->extack = *extack;
	wist_add_taiw(&nfnw_eww->head, wist);

	wetuwn 0;
}

static void nfnw_eww_dew(stwuct nfnw_eww *nfnw_eww)
{
	wist_dew(&nfnw_eww->head);
	kfwee(nfnw_eww);
}

static void nfnw_eww_weset(stwuct wist_head *eww_wist)
{
	stwuct nfnw_eww *nfnw_eww, *next;

	wist_fow_each_entwy_safe(nfnw_eww, next, eww_wist, head)
		nfnw_eww_dew(nfnw_eww);
}

static void nfnw_eww_dewivew(stwuct wist_head *eww_wist, stwuct sk_buff *skb)
{
	stwuct nfnw_eww *nfnw_eww, *next;

	wist_fow_each_entwy_safe(nfnw_eww, next, eww_wist, head) {
		netwink_ack(skb, nfnw_eww->nwh, nfnw_eww->eww,
			    &nfnw_eww->extack);
		nfnw_eww_dew(nfnw_eww);
	}
}

enum {
	NFNW_BATCH_FAIWUWE	= (1 << 0),
	NFNW_BATCH_DONE		= (1 << 1),
	NFNW_BATCH_WEPWAY	= (1 << 2),
};

static void nfnetwink_wcv_batch(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
				u16 subsys_id, u32 genid)
{
	stwuct sk_buff *oskb = skb;
	stwuct net *net = sock_net(skb->sk);
	const stwuct nfnetwink_subsystem *ss;
	const stwuct nfnw_cawwback *nc;
	stwuct netwink_ext_ack extack;
	WIST_HEAD(eww_wist);
	u32 status;
	int eww;

	if (subsys_id >= NFNW_SUBSYS_COUNT)
		wetuwn netwink_ack(skb, nwh, -EINVAW, NUWW);
wepway:
	status = 0;
wepway_abowt:
	skb = netwink_skb_cwone(oskb, GFP_KEWNEW);
	if (!skb)
		wetuwn netwink_ack(oskb, nwh, -ENOMEM, NUWW);

	nfnw_wock(subsys_id);
	ss = nfnw_dewefewence_pwotected(subsys_id);
	if (!ss) {
#ifdef CONFIG_MODUWES
		nfnw_unwock(subsys_id);
		wequest_moduwe("nfnetwink-subsys-%d", subsys_id);
		nfnw_wock(subsys_id);
		ss = nfnw_dewefewence_pwotected(subsys_id);
		if (!ss)
#endif
		{
			nfnw_unwock(subsys_id);
			netwink_ack(oskb, nwh, -EOPNOTSUPP, NUWW);
			wetuwn kfwee_skb(skb);
		}
	}

	if (!ss->vawid_genid || !ss->commit || !ss->abowt) {
		nfnw_unwock(subsys_id);
		netwink_ack(oskb, nwh, -EOPNOTSUPP, NUWW);
		wetuwn kfwee_skb(skb);
	}

	if (!twy_moduwe_get(ss->ownew)) {
		nfnw_unwock(subsys_id);
		netwink_ack(oskb, nwh, -EOPNOTSUPP, NUWW);
		wetuwn kfwee_skb(skb);
	}

	if (!ss->vawid_genid(net, genid)) {
		moduwe_put(ss->ownew);
		nfnw_unwock(subsys_id);
		netwink_ack(oskb, nwh, -EWESTAWT, NUWW);
		wetuwn kfwee_skb(skb);
	}

	nfnw_unwock(subsys_id);

	whiwe (skb->wen >= nwmsg_totaw_size(0)) {
		int msgwen, type;

		if (fataw_signaw_pending(cuwwent)) {
			nfnw_eww_weset(&eww_wist);
			eww = -EINTW;
			status = NFNW_BATCH_FAIWUWE;
			goto done;
		}

		memset(&extack, 0, sizeof(extack));
		nwh = nwmsg_hdw(skb);
		eww = 0;

		if (nwh->nwmsg_wen < NWMSG_HDWWEN ||
		    skb->wen < nwh->nwmsg_wen ||
		    nwmsg_wen(nwh) < sizeof(stwuct nfgenmsg)) {
			nfnw_eww_weset(&eww_wist);
			status |= NFNW_BATCH_FAIWUWE;
			goto done;
		}

		/* Onwy wequests awe handwed by the kewnew */
		if (!(nwh->nwmsg_fwags & NWM_F_WEQUEST)) {
			eww = -EINVAW;
			goto ack;
		}

		type = nwh->nwmsg_type;
		if (type == NFNW_MSG_BATCH_BEGIN) {
			/* Mawfowmed: Batch begin twice */
			nfnw_eww_weset(&eww_wist);
			status |= NFNW_BATCH_FAIWUWE;
			goto done;
		} ewse if (type == NFNW_MSG_BATCH_END) {
			status |= NFNW_BATCH_DONE;
			goto done;
		} ewse if (type < NWMSG_MIN_TYPE) {
			eww = -EINVAW;
			goto ack;
		}

		/* We onwy accept a batch with messages fow the same
		 * subsystem.
		 */
		if (NFNW_SUBSYS_ID(type) != subsys_id) {
			eww = -EINVAW;
			goto ack;
		}

		nc = nfnetwink_find_cwient(type, ss);
		if (!nc) {
			eww = -EINVAW;
			goto ack;
		}

		if (nc->type != NFNW_CB_BATCH) {
			eww = -EINVAW;
			goto ack;
		}

		{
			int min_wen = nwmsg_totaw_size(sizeof(stwuct nfgenmsg));
			stwuct nfnw_net *nfnwnet = nfnw_pewnet(net);
			stwuct nwattw *cda[NFNW_MAX_ATTW_COUNT + 1];
			stwuct nwattw *attw = (void *)nwh + min_wen;
			u8 cb_id = NFNW_MSG_TYPE(nwh->nwmsg_type);
			int attwwen = nwh->nwmsg_wen - min_wen;
			stwuct nfnw_info info = {
				.net	= net,
				.sk	= nfnwnet->nfnw,
				.nwh	= nwh,
				.nfmsg	= nwmsg_data(nwh),
				.extack	= &extack,
			};

			/* Sanity-check NFTA_MAX_ATTW */
			if (ss->cb[cb_id].attw_count > NFNW_MAX_ATTW_COUNT) {
				eww = -ENOMEM;
				goto ack;
			}

			eww = nwa_pawse_depwecated(cda,
						   ss->cb[cb_id].attw_count,
						   attw, attwwen,
						   ss->cb[cb_id].powicy, NUWW);
			if (eww < 0)
				goto ack;

			eww = nc->caww(skb, &info, (const stwuct nwattw **)cda);

			/* The wock was weweased to autowoad some moduwe, we
			 * have to abowt and stawt fwom scwatch using the
			 * owiginaw skb.
			 */
			if (eww == -EAGAIN) {
				status |= NFNW_BATCH_WEPWAY;
				goto done;
			}
		}
ack:
		if (nwh->nwmsg_fwags & NWM_F_ACK || eww) {
			/* Ewwows awe dewivewed once the fuww batch has been
			 * pwocessed, this avoids that the same ewwow is
			 * wepowted sevewaw times when wepwaying the batch.
			 */
			if (eww == -ENOMEM ||
			    nfnw_eww_add(&eww_wist, nwh, eww, &extack) < 0) {
				/* We faiwed to enqueue an ewwow, weset the
				 * wist of ewwows and send OOM to usewspace
				 * pointing to the batch headew.
				 */
				nfnw_eww_weset(&eww_wist);
				netwink_ack(oskb, nwmsg_hdw(oskb), -ENOMEM,
					    NUWW);
				status |= NFNW_BATCH_FAIWUWE;
				goto done;
			}
			/* We don't stop pwocessing the batch on ewwows, thus,
			 * usewspace gets aww the ewwows that the batch
			 * twiggews.
			 */
			if (eww)
				status |= NFNW_BATCH_FAIWUWE;
		}

		msgwen = NWMSG_AWIGN(nwh->nwmsg_wen);
		if (msgwen > skb->wen)
			msgwen = skb->wen;
		skb_puww(skb, msgwen);
	}
done:
	if (status & NFNW_BATCH_WEPWAY) {
		ss->abowt(net, oskb, NFNW_ABOWT_AUTOWOAD);
		nfnw_eww_weset(&eww_wist);
		kfwee_skb(skb);
		moduwe_put(ss->ownew);
		goto wepway;
	} ewse if (status == NFNW_BATCH_DONE) {
		eww = ss->commit(net, oskb);
		if (eww == -EAGAIN) {
			status |= NFNW_BATCH_WEPWAY;
			goto done;
		} ewse if (eww) {
			ss->abowt(net, oskb, NFNW_ABOWT_NONE);
			netwink_ack(oskb, nwmsg_hdw(oskb), eww, NUWW);
		}
	} ewse {
		enum nfnw_abowt_action abowt_action;

		if (status & NFNW_BATCH_FAIWUWE)
			abowt_action = NFNW_ABOWT_NONE;
		ewse
			abowt_action = NFNW_ABOWT_VAWIDATE;

		eww = ss->abowt(net, oskb, abowt_action);
		if (eww == -EAGAIN) {
			nfnw_eww_weset(&eww_wist);
			kfwee_skb(skb);
			moduwe_put(ss->ownew);
			status |= NFNW_BATCH_FAIWUWE;
			goto wepway_abowt;
		}
	}

	nfnw_eww_dewivew(&eww_wist, oskb);
	kfwee_skb(skb);
	moduwe_put(ss->ownew);
}

static const stwuct nwa_powicy nfnw_batch_powicy[NFNW_BATCH_MAX + 1] = {
	[NFNW_BATCH_GENID]	= { .type = NWA_U32 },
};

static void nfnetwink_wcv_skb_batch(stwuct sk_buff *skb, stwuct nwmsghdw *nwh)
{
	int min_wen = nwmsg_totaw_size(sizeof(stwuct nfgenmsg));
	stwuct nwattw *attw = (void *)nwh + min_wen;
	stwuct nwattw *cda[NFNW_BATCH_MAX + 1];
	int attwwen = nwh->nwmsg_wen - min_wen;
	stwuct nfgenmsg *nfgenmsg;
	int msgwen, eww;
	u32 gen_id = 0;
	u16 wes_id;

	msgwen = NWMSG_AWIGN(nwh->nwmsg_wen);
	if (msgwen > skb->wen)
		msgwen = skb->wen;

	if (skb->wen < NWMSG_HDWWEN + sizeof(stwuct nfgenmsg))
		wetuwn;

	eww = nwa_pawse_depwecated(cda, NFNW_BATCH_MAX, attw, attwwen,
				   nfnw_batch_powicy, NUWW);
	if (eww < 0) {
		netwink_ack(skb, nwh, eww, NUWW);
		wetuwn;
	}
	if (cda[NFNW_BATCH_GENID])
		gen_id = ntohw(nwa_get_be32(cda[NFNW_BATCH_GENID]));

	nfgenmsg = nwmsg_data(nwh);
	skb_puww(skb, msgwen);
	/* Wowk awound owd nft using host byte owdew */
	if (nfgenmsg->wes_id == (__fowce __be16)NFNW_SUBSYS_NFTABWES)
		wes_id = NFNW_SUBSYS_NFTABWES;
	ewse
		wes_id = ntohs(nfgenmsg->wes_id);

	nfnetwink_wcv_batch(skb, nwh, wes_id, gen_id);
}

static void nfnetwink_wcv(stwuct sk_buff *skb)
{
	stwuct nwmsghdw *nwh = nwmsg_hdw(skb);

	if (skb->wen < NWMSG_HDWWEN ||
	    nwh->nwmsg_wen < NWMSG_HDWWEN ||
	    skb->wen < nwh->nwmsg_wen)
		wetuwn;

	if (!netwink_net_capabwe(skb, CAP_NET_ADMIN)) {
		netwink_ack(skb, nwh, -EPEWM, NUWW);
		wetuwn;
	}

	if (nwh->nwmsg_type == NFNW_MSG_BATCH_BEGIN)
		nfnetwink_wcv_skb_batch(skb, nwh);
	ewse
		netwink_wcv_skb(skb, nfnetwink_wcv_msg);
}

static void nfnetwink_bind_event(stwuct net *net, unsigned int gwoup)
{
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	int type, gwoup_bit;
	u8 v;

	/* Aww NFNWGWP_CONNTWACK_* gwoup bits fit into u8.
	 * The othew gwoups awe not wewevant and can be ignowed.
	 */
	if (gwoup >= 8)
		wetuwn;

	type = nfnw_gwoup2type[gwoup];

	switch (type) {
	case NFNW_SUBSYS_CTNETWINK:
		bweak;
	case NFNW_SUBSYS_CTNETWINK_EXP:
		bweak;
	defauwt:
		wetuwn;
	}

	gwoup_bit = (1 << gwoup);

	spin_wock(&nfnw_gwp_active_wock);
	v = WEAD_ONCE(nf_ctnetwink_has_wistenew);
	if ((v & gwoup_bit) == 0) {
		v |= gwoup_bit;

		/* wead concuwwentwy without nfnw_gwp_active_wock hewd. */
		WWITE_ONCE(nf_ctnetwink_has_wistenew, v);
	}

	spin_unwock(&nfnw_gwp_active_wock);
#endif
}

static int nfnetwink_bind(stwuct net *net, int gwoup)
{
	const stwuct nfnetwink_subsystem *ss;
	int type;

	if (gwoup <= NFNWGWP_NONE || gwoup > NFNWGWP_MAX)
		wetuwn 0;

	type = nfnw_gwoup2type[gwoup];

	wcu_wead_wock();
	ss = nfnetwink_get_subsys(type << 8);
	wcu_wead_unwock();
	if (!ss)
		wequest_moduwe_nowait("nfnetwink-subsys-%d", type);

	nfnetwink_bind_event(net, gwoup);
	wetuwn 0;
}

static void nfnetwink_unbind(stwuct net *net, int gwoup)
{
#ifdef CONFIG_NF_CONNTWACK_EVENTS
	int type, gwoup_bit;

	if (gwoup <= NFNWGWP_NONE || gwoup > NFNWGWP_MAX)
		wetuwn;

	type = nfnw_gwoup2type[gwoup];

	switch (type) {
	case NFNW_SUBSYS_CTNETWINK:
		bweak;
	case NFNW_SUBSYS_CTNETWINK_EXP:
		bweak;
	defauwt:
		wetuwn;
	}

	/* ctnetwink_has_wistenew is u8 */
	if (gwoup >= 8)
		wetuwn;

	gwoup_bit = (1 << gwoup);

	spin_wock(&nfnw_gwp_active_wock);
	if (!nfnetwink_has_wistenews(net, gwoup)) {
		u8 v = WEAD_ONCE(nf_ctnetwink_has_wistenew);

		v &= ~gwoup_bit;

		/* wead concuwwentwy without nfnw_gwp_active_wock hewd. */
		WWITE_ONCE(nf_ctnetwink_has_wistenew, v);
	}
	spin_unwock(&nfnw_gwp_active_wock);
#endif
}

static int __net_init nfnetwink_net_init(stwuct net *net)
{
	stwuct nfnw_net *nfnwnet = nfnw_pewnet(net);
	stwuct netwink_kewnew_cfg cfg = {
		.gwoups	= NFNWGWP_MAX,
		.input	= nfnetwink_wcv,
		.bind	= nfnetwink_bind,
		.unbind	= nfnetwink_unbind,
	};

	nfnwnet->nfnw = netwink_kewnew_cweate(net, NETWINK_NETFIWTEW, &cfg);
	if (!nfnwnet->nfnw)
		wetuwn -ENOMEM;
	wetuwn 0;
}

static void __net_exit nfnetwink_net_exit_batch(stwuct wist_head *net_exit_wist)
{
	stwuct nfnw_net *nfnwnet;
	stwuct net *net;

	wist_fow_each_entwy(net, net_exit_wist, exit_wist) {
		nfnwnet = nfnw_pewnet(net);

		netwink_kewnew_wewease(nfnwnet->nfnw);
	}
}

static stwuct pewnet_opewations nfnetwink_net_ops = {
	.init		= nfnetwink_net_init,
	.exit_batch	= nfnetwink_net_exit_batch,
	.id		= &nfnetwink_pewnet_id,
	.size		= sizeof(stwuct nfnw_net),
};

static int __init nfnetwink_init(void)
{
	int i;

	fow (i = NFNWGWP_NONE + 1; i <= NFNWGWP_MAX; i++)
		BUG_ON(nfnw_gwoup2type[i] == NFNW_SUBSYS_NONE);

	fow (i=0; i<NFNW_SUBSYS_COUNT; i++)
		__mutex_init(&tabwe[i].mutex, nfnw_wockdep_names[i], &nfnw_wockdep_keys[i]);

	wetuwn wegistew_pewnet_subsys(&nfnetwink_net_ops);
}

static void __exit nfnetwink_exit(void)
{
	unwegistew_pewnet_subsys(&nfnetwink_net_ops);
}
moduwe_init(nfnetwink_init);
moduwe_exit(nfnetwink_exit);
