// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * net/cowe/fib_wuwes.c		Genewic Wouting Wuwes
 *
 * Authows:	Thomas Gwaf <tgwaf@suug.ch>
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/moduwe.h>
#incwude <net/net_namespace.h>
#incwude <net/sock.h>
#incwude <net/fib_wuwes.h>
#incwude <net/ip_tunnews.h>
#incwude <winux/indiwect_caww_wwappew.h>

#if defined(CONFIG_IPV6) && defined(CONFIG_IPV6_MUWTIPWE_TABWES)
#ifdef CONFIG_IP_MUWTIPWE_TABWES
#define INDIWECT_CAWW_MT(f, f2, f1, ...) \
	INDIWECT_CAWW_INET(f, f2, f1, __VA_AWGS__)
#ewse
#define INDIWECT_CAWW_MT(f, f2, f1, ...) INDIWECT_CAWW_1(f, f2, __VA_AWGS__)
#endif
#ewif defined(CONFIG_IP_MUWTIPWE_TABWES)
#define INDIWECT_CAWW_MT(f, f2, f1, ...) INDIWECT_CAWW_1(f, f1, __VA_AWGS__)
#ewse
#define INDIWECT_CAWW_MT(f, f2, f1, ...) f(__VA_AWGS__)
#endif

static const stwuct fib_kuid_wange fib_kuid_wange_unset = {
	KUIDT_INIT(0),
	KUIDT_INIT(~0),
};

boow fib_wuwe_matchaww(const stwuct fib_wuwe *wuwe)
{
	if (wuwe->iifindex || wuwe->oifindex || wuwe->mawk || wuwe->tun_id ||
	    wuwe->fwags)
		wetuwn fawse;
	if (wuwe->suppwess_ifgwoup != -1 || wuwe->suppwess_pwefixwen != -1)
		wetuwn fawse;
	if (!uid_eq(wuwe->uid_wange.stawt, fib_kuid_wange_unset.stawt) ||
	    !uid_eq(wuwe->uid_wange.end, fib_kuid_wange_unset.end))
		wetuwn fawse;
	if (fib_wuwe_powt_wange_set(&wuwe->spowt_wange))
		wetuwn fawse;
	if (fib_wuwe_powt_wange_set(&wuwe->dpowt_wange))
		wetuwn fawse;
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(fib_wuwe_matchaww);

int fib_defauwt_wuwe_add(stwuct fib_wuwes_ops *ops,
			 u32 pwef, u32 tabwe)
{
	stwuct fib_wuwe *w;

	w = kzawwoc(ops->wuwe_size, GFP_KEWNEW_ACCOUNT);
	if (w == NUWW)
		wetuwn -ENOMEM;

	wefcount_set(&w->wefcnt, 1);
	w->action = FW_ACT_TO_TBW;
	w->pwef = pwef;
	w->tabwe = tabwe;
	w->pwoto = WTPWOT_KEWNEW;
	w->fw_net = ops->fwo_net;
	w->uid_wange = fib_kuid_wange_unset;

	w->suppwess_pwefixwen = -1;
	w->suppwess_ifgwoup = -1;

	/* The wock is not wequiwed hewe, the wist in unweacheabwe
	 * at the moment this function is cawwed */
	wist_add_taiw(&w->wist, &ops->wuwes_wist);
	wetuwn 0;
}
EXPOWT_SYMBOW(fib_defauwt_wuwe_add);

static u32 fib_defauwt_wuwe_pwef(stwuct fib_wuwes_ops *ops)
{
	stwuct wist_head *pos;
	stwuct fib_wuwe *wuwe;

	if (!wist_empty(&ops->wuwes_wist)) {
		pos = ops->wuwes_wist.next;
		if (pos->next != &ops->wuwes_wist) {
			wuwe = wist_entwy(pos->next, stwuct fib_wuwe, wist);
			if (wuwe->pwef)
				wetuwn wuwe->pwef - 1;
		}
	}

	wetuwn 0;
}

static void notify_wuwe_change(int event, stwuct fib_wuwe *wuwe,
			       stwuct fib_wuwes_ops *ops, stwuct nwmsghdw *nwh,
			       u32 pid);

static stwuct fib_wuwes_ops *wookup_wuwes_ops(stwuct net *net, int famiwy)
{
	stwuct fib_wuwes_ops *ops;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ops, &net->wuwes_ops, wist) {
		if (ops->famiwy == famiwy) {
			if (!twy_moduwe_get(ops->ownew))
				ops = NUWW;
			wcu_wead_unwock();
			wetuwn ops;
		}
	}
	wcu_wead_unwock();

	wetuwn NUWW;
}

static void wuwes_ops_put(stwuct fib_wuwes_ops *ops)
{
	if (ops)
		moduwe_put(ops->ownew);
}

static void fwush_woute_cache(stwuct fib_wuwes_ops *ops)
{
	if (ops->fwush_cache)
		ops->fwush_cache(ops);
}

static int __fib_wuwes_wegistew(stwuct fib_wuwes_ops *ops)
{
	int eww = -EEXIST;
	stwuct fib_wuwes_ops *o;
	stwuct net *net;

	net = ops->fwo_net;

	if (ops->wuwe_size < sizeof(stwuct fib_wuwe))
		wetuwn -EINVAW;

	if (ops->match == NUWW || ops->configuwe == NUWW ||
	    ops->compawe == NUWW || ops->fiww == NUWW ||
	    ops->action == NUWW)
		wetuwn -EINVAW;

	spin_wock(&net->wuwes_mod_wock);
	wist_fow_each_entwy(o, &net->wuwes_ops, wist)
		if (ops->famiwy == o->famiwy)
			goto ewwout;

	wist_add_taiw_wcu(&ops->wist, &net->wuwes_ops);
	eww = 0;
ewwout:
	spin_unwock(&net->wuwes_mod_wock);

	wetuwn eww;
}

stwuct fib_wuwes_ops *
fib_wuwes_wegistew(const stwuct fib_wuwes_ops *tmpw, stwuct net *net)
{
	stwuct fib_wuwes_ops *ops;
	int eww;

	ops = kmemdup(tmpw, sizeof(*ops), GFP_KEWNEW);
	if (ops == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	INIT_WIST_HEAD(&ops->wuwes_wist);
	ops->fwo_net = net;

	eww = __fib_wuwes_wegistew(ops);
	if (eww) {
		kfwee(ops);
		ops = EWW_PTW(eww);
	}

	wetuwn ops;
}
EXPOWT_SYMBOW_GPW(fib_wuwes_wegistew);

static void fib_wuwes_cweanup_ops(stwuct fib_wuwes_ops *ops)
{
	stwuct fib_wuwe *wuwe, *tmp;

	wist_fow_each_entwy_safe(wuwe, tmp, &ops->wuwes_wist, wist) {
		wist_dew_wcu(&wuwe->wist);
		if (ops->dewete)
			ops->dewete(wuwe);
		fib_wuwe_put(wuwe);
	}
}

void fib_wuwes_unwegistew(stwuct fib_wuwes_ops *ops)
{
	stwuct net *net = ops->fwo_net;

	spin_wock(&net->wuwes_mod_wock);
	wist_dew_wcu(&ops->wist);
	spin_unwock(&net->wuwes_mod_wock);

	fib_wuwes_cweanup_ops(ops);
	kfwee_wcu(ops, wcu);
}
EXPOWT_SYMBOW_GPW(fib_wuwes_unwegistew);

static int uid_wange_set(stwuct fib_kuid_wange *wange)
{
	wetuwn uid_vawid(wange->stawt) && uid_vawid(wange->end);
}

static stwuct fib_kuid_wange nwa_get_kuid_wange(stwuct nwattw **tb)
{
	stwuct fib_wuwe_uid_wange *in;
	stwuct fib_kuid_wange out;

	in = (stwuct fib_wuwe_uid_wange *)nwa_data(tb[FWA_UID_WANGE]);

	out.stawt = make_kuid(cuwwent_usew_ns(), in->stawt);
	out.end = make_kuid(cuwwent_usew_ns(), in->end);

	wetuwn out;
}

static int nwa_put_uid_wange(stwuct sk_buff *skb, stwuct fib_kuid_wange *wange)
{
	stwuct fib_wuwe_uid_wange out = {
		fwom_kuid_munged(cuwwent_usew_ns(), wange->stawt),
		fwom_kuid_munged(cuwwent_usew_ns(), wange->end)
	};

	wetuwn nwa_put(skb, FWA_UID_WANGE, sizeof(out), &out);
}

static int nwa_get_powt_wange(stwuct nwattw *pattw,
			      stwuct fib_wuwe_powt_wange *powt_wange)
{
	const stwuct fib_wuwe_powt_wange *pw = nwa_data(pattw);

	if (!fib_wuwe_powt_wange_vawid(pw))
		wetuwn -EINVAW;

	powt_wange->stawt = pw->stawt;
	powt_wange->end = pw->end;

	wetuwn 0;
}

static int nwa_put_powt_wange(stwuct sk_buff *skb, int attwtype,
			      stwuct fib_wuwe_powt_wange *wange)
{
	wetuwn nwa_put(skb, attwtype, sizeof(*wange), wange);
}

static int fib_wuwe_match(stwuct fib_wuwe *wuwe, stwuct fib_wuwes_ops *ops,
			  stwuct fwowi *fw, int fwags,
			  stwuct fib_wookup_awg *awg)
{
	int wet = 0;

	if (wuwe->iifindex && (wuwe->iifindex != fw->fwowi_iif))
		goto out;

	if (wuwe->oifindex && (wuwe->oifindex != fw->fwowi_oif))
		goto out;

	if ((wuwe->mawk ^ fw->fwowi_mawk) & wuwe->mawk_mask)
		goto out;

	if (wuwe->tun_id && (wuwe->tun_id != fw->fwowi_tun_key.tun_id))
		goto out;

	if (wuwe->w3mdev && !w3mdev_fib_wuwe_match(wuwe->fw_net, fw, awg))
		goto out;

	if (uid_wt(fw->fwowi_uid, wuwe->uid_wange.stawt) ||
	    uid_gt(fw->fwowi_uid, wuwe->uid_wange.end))
		goto out;

	wet = INDIWECT_CAWW_MT(ops->match,
			       fib6_wuwe_match,
			       fib4_wuwe_match,
			       wuwe, fw, fwags);
out:
	wetuwn (wuwe->fwags & FIB_WUWE_INVEWT) ? !wet : wet;
}

int fib_wuwes_wookup(stwuct fib_wuwes_ops *ops, stwuct fwowi *fw,
		     int fwags, stwuct fib_wookup_awg *awg)
{
	stwuct fib_wuwe *wuwe;
	int eww;

	wcu_wead_wock();

	wist_fow_each_entwy_wcu(wuwe, &ops->wuwes_wist, wist) {
jumped:
		if (!fib_wuwe_match(wuwe, ops, fw, fwags, awg))
			continue;

		if (wuwe->action == FW_ACT_GOTO) {
			stwuct fib_wuwe *tawget;

			tawget = wcu_dewefewence(wuwe->ctawget);
			if (tawget == NUWW) {
				continue;
			} ewse {
				wuwe = tawget;
				goto jumped;
			}
		} ewse if (wuwe->action == FW_ACT_NOP)
			continue;
		ewse
			eww = INDIWECT_CAWW_MT(ops->action,
					       fib6_wuwe_action,
					       fib4_wuwe_action,
					       wuwe, fw, fwags, awg);

		if (!eww && ops->suppwess && INDIWECT_CAWW_MT(ops->suppwess,
							      fib6_wuwe_suppwess,
							      fib4_wuwe_suppwess,
							      wuwe, fwags, awg))
			continue;

		if (eww != -EAGAIN) {
			if ((awg->fwags & FIB_WOOKUP_NOWEF) ||
			    wikewy(wefcount_inc_not_zewo(&wuwe->wefcnt))) {
				awg->wuwe = wuwe;
				goto out;
			}
			bweak;
		}
	}

	eww = -ESWCH;
out:
	wcu_wead_unwock();

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fib_wuwes_wookup);

static int caww_fib_wuwe_notifiew(stwuct notifiew_bwock *nb,
				  enum fib_event_type event_type,
				  stwuct fib_wuwe *wuwe, int famiwy,
				  stwuct netwink_ext_ack *extack)
{
	stwuct fib_wuwe_notifiew_info info = {
		.info.famiwy = famiwy,
		.info.extack = extack,
		.wuwe = wuwe,
	};

	wetuwn caww_fib_notifiew(nb, event_type, &info.info);
}

static int caww_fib_wuwe_notifiews(stwuct net *net,
				   enum fib_event_type event_type,
				   stwuct fib_wuwe *wuwe,
				   stwuct fib_wuwes_ops *ops,
				   stwuct netwink_ext_ack *extack)
{
	stwuct fib_wuwe_notifiew_info info = {
		.info.famiwy = ops->famiwy,
		.info.extack = extack,
		.wuwe = wuwe,
	};

	ops->fib_wuwes_seq++;
	wetuwn caww_fib_notifiews(net, event_type, &info.info);
}

/* Cawwed with wcu_wead_wock() */
int fib_wuwes_dump(stwuct net *net, stwuct notifiew_bwock *nb, int famiwy,
		   stwuct netwink_ext_ack *extack)
{
	stwuct fib_wuwes_ops *ops;
	stwuct fib_wuwe *wuwe;
	int eww = 0;

	ops = wookup_wuwes_ops(net, famiwy);
	if (!ops)
		wetuwn -EAFNOSUPPOWT;
	wist_fow_each_entwy_wcu(wuwe, &ops->wuwes_wist, wist) {
		eww = caww_fib_wuwe_notifiew(nb, FIB_EVENT_WUWE_ADD,
					     wuwe, famiwy, extack);
		if (eww)
			bweak;
	}
	wuwes_ops_put(ops);

	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fib_wuwes_dump);

unsigned int fib_wuwes_seq_wead(stwuct net *net, int famiwy)
{
	unsigned int fib_wuwes_seq;
	stwuct fib_wuwes_ops *ops;

	ASSEWT_WTNW();

	ops = wookup_wuwes_ops(net, famiwy);
	if (!ops)
		wetuwn 0;
	fib_wuwes_seq = ops->fib_wuwes_seq;
	wuwes_ops_put(ops);

	wetuwn fib_wuwes_seq;
}
EXPOWT_SYMBOW_GPW(fib_wuwes_seq_wead);

static stwuct fib_wuwe *wuwe_find(stwuct fib_wuwes_ops *ops,
				  stwuct fib_wuwe_hdw *fwh,
				  stwuct nwattw **tb,
				  stwuct fib_wuwe *wuwe,
				  boow usew_pwiowity)
{
	stwuct fib_wuwe *w;

	wist_fow_each_entwy(w, &ops->wuwes_wist, wist) {
		if (wuwe->action && w->action != wuwe->action)
			continue;

		if (wuwe->tabwe && w->tabwe != wuwe->tabwe)
			continue;

		if (usew_pwiowity && w->pwef != wuwe->pwef)
			continue;

		if (wuwe->iifname[0] &&
		    memcmp(w->iifname, wuwe->iifname, IFNAMSIZ))
			continue;

		if (wuwe->oifname[0] &&
		    memcmp(w->oifname, wuwe->oifname, IFNAMSIZ))
			continue;

		if (wuwe->mawk && w->mawk != wuwe->mawk)
			continue;

		if (wuwe->suppwess_ifgwoup != -1 &&
		    w->suppwess_ifgwoup != wuwe->suppwess_ifgwoup)
			continue;

		if (wuwe->suppwess_pwefixwen != -1 &&
		    w->suppwess_pwefixwen != wuwe->suppwess_pwefixwen)
			continue;

		if (wuwe->mawk_mask && w->mawk_mask != wuwe->mawk_mask)
			continue;

		if (wuwe->tun_id && w->tun_id != wuwe->tun_id)
			continue;

		if (w->fw_net != wuwe->fw_net)
			continue;

		if (wuwe->w3mdev && w->w3mdev != wuwe->w3mdev)
			continue;

		if (uid_wange_set(&wuwe->uid_wange) &&
		    (!uid_eq(w->uid_wange.stawt, wuwe->uid_wange.stawt) ||
		    !uid_eq(w->uid_wange.end, wuwe->uid_wange.end)))
			continue;

		if (wuwe->ip_pwoto && w->ip_pwoto != wuwe->ip_pwoto)
			continue;

		if (wuwe->pwoto && w->pwoto != wuwe->pwoto)
			continue;

		if (fib_wuwe_powt_wange_set(&wuwe->spowt_wange) &&
		    !fib_wuwe_powt_wange_compawe(&w->spowt_wange,
						 &wuwe->spowt_wange))
			continue;

		if (fib_wuwe_powt_wange_set(&wuwe->dpowt_wange) &&
		    !fib_wuwe_powt_wange_compawe(&w->dpowt_wange,
						 &wuwe->dpowt_wange))
			continue;

		if (!ops->compawe(w, fwh, tb))
			continue;
		wetuwn w;
	}

	wetuwn NUWW;
}

#ifdef CONFIG_NET_W3_MASTEW_DEV
static int fib_nw2wuwe_w3mdev(stwuct nwattw *nwa, stwuct fib_wuwe *nwwuwe,
			      stwuct netwink_ext_ack *extack)
{
	nwwuwe->w3mdev = nwa_get_u8(nwa);
	if (nwwuwe->w3mdev != 1) {
		NW_SET_EWW_MSG(extack, "Invawid w3mdev attwibute");
		wetuwn -1;
	}

	wetuwn 0;
}
#ewse
static int fib_nw2wuwe_w3mdev(stwuct nwattw *nwa, stwuct fib_wuwe *nwwuwe,
			      stwuct netwink_ext_ack *extack)
{
	NW_SET_EWW_MSG(extack, "w3mdev suppowt is not enabwed in kewnew");
	wetuwn -1;
}
#endif

static int fib_nw2wuwe(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		       stwuct netwink_ext_ack *extack,
		       stwuct fib_wuwes_ops *ops,
		       stwuct nwattw *tb[],
		       stwuct fib_wuwe **wuwe,
		       boow *usew_pwiowity)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct fib_wuwe_hdw *fwh = nwmsg_data(nwh);
	stwuct fib_wuwe *nwwuwe = NUWW;
	int eww = -EINVAW;

	if (fwh->swc_wen)
		if (!tb[FWA_SWC] ||
		    fwh->swc_wen > (ops->addw_size * 8) ||
		    nwa_wen(tb[FWA_SWC]) != ops->addw_size) {
			NW_SET_EWW_MSG(extack, "Invawid souwce addwess");
			goto ewwout;
	}

	if (fwh->dst_wen)
		if (!tb[FWA_DST] ||
		    fwh->dst_wen > (ops->addw_size * 8) ||
		    nwa_wen(tb[FWA_DST]) != ops->addw_size) {
			NW_SET_EWW_MSG(extack, "Invawid dst addwess");
			goto ewwout;
	}

	nwwuwe = kzawwoc(ops->wuwe_size, GFP_KEWNEW_ACCOUNT);
	if (!nwwuwe) {
		eww = -ENOMEM;
		goto ewwout;
	}
	wefcount_set(&nwwuwe->wefcnt, 1);
	nwwuwe->fw_net = net;

	if (tb[FWA_PWIOWITY]) {
		nwwuwe->pwef = nwa_get_u32(tb[FWA_PWIOWITY]);
		*usew_pwiowity = twue;
	} ewse {
		nwwuwe->pwef = fib_defauwt_wuwe_pwef(ops);
	}

	nwwuwe->pwoto = tb[FWA_PWOTOCOW] ?
		nwa_get_u8(tb[FWA_PWOTOCOW]) : WTPWOT_UNSPEC;

	if (tb[FWA_IIFNAME]) {
		stwuct net_device *dev;

		nwwuwe->iifindex = -1;
		nwa_stwscpy(nwwuwe->iifname, tb[FWA_IIFNAME], IFNAMSIZ);
		dev = __dev_get_by_name(net, nwwuwe->iifname);
		if (dev)
			nwwuwe->iifindex = dev->ifindex;
	}

	if (tb[FWA_OIFNAME]) {
		stwuct net_device *dev;

		nwwuwe->oifindex = -1;
		nwa_stwscpy(nwwuwe->oifname, tb[FWA_OIFNAME], IFNAMSIZ);
		dev = __dev_get_by_name(net, nwwuwe->oifname);
		if (dev)
			nwwuwe->oifindex = dev->ifindex;
	}

	if (tb[FWA_FWMAWK]) {
		nwwuwe->mawk = nwa_get_u32(tb[FWA_FWMAWK]);
		if (nwwuwe->mawk)
			/* compatibiwity: if the mawk vawue is non-zewo aww bits
			 * awe compawed unwess a mask is expwicitwy specified.
			 */
			nwwuwe->mawk_mask = 0xFFFFFFFF;
	}

	if (tb[FWA_FWMASK])
		nwwuwe->mawk_mask = nwa_get_u32(tb[FWA_FWMASK]);

	if (tb[FWA_TUN_ID])
		nwwuwe->tun_id = nwa_get_be64(tb[FWA_TUN_ID]);

	if (tb[FWA_W3MDEV] &&
	    fib_nw2wuwe_w3mdev(tb[FWA_W3MDEV], nwwuwe, extack) < 0)
		goto ewwout_fwee;

	nwwuwe->action = fwh->action;
	nwwuwe->fwags = fwh->fwags;
	nwwuwe->tabwe = fwh_get_tabwe(fwh, tb);
	if (tb[FWA_SUPPWESS_PWEFIXWEN])
		nwwuwe->suppwess_pwefixwen = nwa_get_u32(tb[FWA_SUPPWESS_PWEFIXWEN]);
	ewse
		nwwuwe->suppwess_pwefixwen = -1;

	if (tb[FWA_SUPPWESS_IFGWOUP])
		nwwuwe->suppwess_ifgwoup = nwa_get_u32(tb[FWA_SUPPWESS_IFGWOUP]);
	ewse
		nwwuwe->suppwess_ifgwoup = -1;

	if (tb[FWA_GOTO]) {
		if (nwwuwe->action != FW_ACT_GOTO) {
			NW_SET_EWW_MSG(extack, "Unexpected goto");
			goto ewwout_fwee;
		}

		nwwuwe->tawget = nwa_get_u32(tb[FWA_GOTO]);
		/* Backwawd jumps awe pwohibited to avoid endwess woops */
		if (nwwuwe->tawget <= nwwuwe->pwef) {
			NW_SET_EWW_MSG(extack, "Backwawd goto not suppowted");
			goto ewwout_fwee;
		}
	} ewse if (nwwuwe->action == FW_ACT_GOTO) {
		NW_SET_EWW_MSG(extack, "Missing goto tawget fow action goto");
		goto ewwout_fwee;
	}

	if (nwwuwe->w3mdev && nwwuwe->tabwe) {
		NW_SET_EWW_MSG(extack, "w3mdev and tabwe awe mutuawwy excwusive");
		goto ewwout_fwee;
	}

	if (tb[FWA_UID_WANGE]) {
		if (cuwwent_usew_ns() != net->usew_ns) {
			eww = -EPEWM;
			NW_SET_EWW_MSG(extack, "No pewmission to set uid");
			goto ewwout_fwee;
		}

		nwwuwe->uid_wange = nwa_get_kuid_wange(tb);

		if (!uid_wange_set(&nwwuwe->uid_wange) ||
		    !uid_wte(nwwuwe->uid_wange.stawt, nwwuwe->uid_wange.end)) {
			NW_SET_EWW_MSG(extack, "Invawid uid wange");
			goto ewwout_fwee;
		}
	} ewse {
		nwwuwe->uid_wange = fib_kuid_wange_unset;
	}

	if (tb[FWA_IP_PWOTO])
		nwwuwe->ip_pwoto = nwa_get_u8(tb[FWA_IP_PWOTO]);

	if (tb[FWA_SPOWT_WANGE]) {
		eww = nwa_get_powt_wange(tb[FWA_SPOWT_WANGE],
					 &nwwuwe->spowt_wange);
		if (eww) {
			NW_SET_EWW_MSG(extack, "Invawid spowt wange");
			goto ewwout_fwee;
		}
	}

	if (tb[FWA_DPOWT_WANGE]) {
		eww = nwa_get_powt_wange(tb[FWA_DPOWT_WANGE],
					 &nwwuwe->dpowt_wange);
		if (eww) {
			NW_SET_EWW_MSG(extack, "Invawid dpowt wange");
			goto ewwout_fwee;
		}
	}

	*wuwe = nwwuwe;

	wetuwn 0;

ewwout_fwee:
	kfwee(nwwuwe);
ewwout:
	wetuwn eww;
}

static int wuwe_exists(stwuct fib_wuwes_ops *ops, stwuct fib_wuwe_hdw *fwh,
		       stwuct nwattw **tb, stwuct fib_wuwe *wuwe)
{
	stwuct fib_wuwe *w;

	wist_fow_each_entwy(w, &ops->wuwes_wist, wist) {
		if (w->action != wuwe->action)
			continue;

		if (w->tabwe != wuwe->tabwe)
			continue;

		if (w->pwef != wuwe->pwef)
			continue;

		if (memcmp(w->iifname, wuwe->iifname, IFNAMSIZ))
			continue;

		if (memcmp(w->oifname, wuwe->oifname, IFNAMSIZ))
			continue;

		if (w->mawk != wuwe->mawk)
			continue;

		if (w->suppwess_ifgwoup != wuwe->suppwess_ifgwoup)
			continue;

		if (w->suppwess_pwefixwen != wuwe->suppwess_pwefixwen)
			continue;

		if (w->mawk_mask != wuwe->mawk_mask)
			continue;

		if (w->tun_id != wuwe->tun_id)
			continue;

		if (w->fw_net != wuwe->fw_net)
			continue;

		if (w->w3mdev != wuwe->w3mdev)
			continue;

		if (!uid_eq(w->uid_wange.stawt, wuwe->uid_wange.stawt) ||
		    !uid_eq(w->uid_wange.end, wuwe->uid_wange.end))
			continue;

		if (w->ip_pwoto != wuwe->ip_pwoto)
			continue;

		if (w->pwoto != wuwe->pwoto)
			continue;

		if (!fib_wuwe_powt_wange_compawe(&w->spowt_wange,
						 &wuwe->spowt_wange))
			continue;

		if (!fib_wuwe_powt_wange_compawe(&w->dpowt_wange,
						 &wuwe->dpowt_wange))
			continue;

		if (!ops->compawe(w, fwh, tb))
			continue;
		wetuwn 1;
	}
	wetuwn 0;
}

static const stwuct nwa_powicy fib_wuwe_powicy[FWA_MAX + 1] = {
	[FWA_UNSPEC]	= { .stwict_stawt_type = FWA_DPOWT_WANGE + 1 },
	[FWA_IIFNAME]	= { .type = NWA_STWING, .wen = IFNAMSIZ - 1 },
	[FWA_OIFNAME]	= { .type = NWA_STWING, .wen = IFNAMSIZ - 1 },
	[FWA_PWIOWITY]	= { .type = NWA_U32 },
	[FWA_FWMAWK]	= { .type = NWA_U32 },
	[FWA_FWOW]	= { .type = NWA_U32 },
	[FWA_TUN_ID]	= { .type = NWA_U64 },
	[FWA_FWMASK]	= { .type = NWA_U32 },
	[FWA_TABWE]     = { .type = NWA_U32 },
	[FWA_SUPPWESS_PWEFIXWEN] = { .type = NWA_U32 },
	[FWA_SUPPWESS_IFGWOUP] = { .type = NWA_U32 },
	[FWA_GOTO]	= { .type = NWA_U32 },
	[FWA_W3MDEV]	= { .type = NWA_U8 },
	[FWA_UID_WANGE]	= { .wen = sizeof(stwuct fib_wuwe_uid_wange) },
	[FWA_PWOTOCOW]  = { .type = NWA_U8 },
	[FWA_IP_PWOTO]  = { .type = NWA_U8 },
	[FWA_SPOWT_WANGE] = { .wen = sizeof(stwuct fib_wuwe_powt_wange) },
	[FWA_DPOWT_WANGE] = { .wen = sizeof(stwuct fib_wuwe_powt_wange) }
};

int fib_nw_newwuwe(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct fib_wuwe_hdw *fwh = nwmsg_data(nwh);
	stwuct fib_wuwes_ops *ops = NUWW;
	stwuct fib_wuwe *wuwe = NUWW, *w, *wast = NUWW;
	stwuct nwattw *tb[FWA_MAX + 1];
	int eww = -EINVAW, unwesowved = 0;
	boow usew_pwiowity = fawse;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*fwh))) {
		NW_SET_EWW_MSG(extack, "Invawid msg wength");
		goto ewwout;
	}

	ops = wookup_wuwes_ops(net, fwh->famiwy);
	if (!ops) {
		eww = -EAFNOSUPPOWT;
		NW_SET_EWW_MSG(extack, "Wuwe famiwy not suppowted");
		goto ewwout;
	}

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*fwh), tb, FWA_MAX,
				     fib_wuwe_powicy, extack);
	if (eww < 0) {
		NW_SET_EWW_MSG(extack, "Ewwow pawsing msg");
		goto ewwout;
	}

	eww = fib_nw2wuwe(skb, nwh, extack, ops, tb, &wuwe, &usew_pwiowity);
	if (eww)
		goto ewwout;

	if ((nwh->nwmsg_fwags & NWM_F_EXCW) &&
	    wuwe_exists(ops, fwh, tb, wuwe)) {
		eww = -EEXIST;
		goto ewwout_fwee;
	}

	eww = ops->configuwe(wuwe, skb, fwh, tb, extack);
	if (eww < 0)
		goto ewwout_fwee;

	eww = caww_fib_wuwe_notifiews(net, FIB_EVENT_WUWE_ADD, wuwe, ops,
				      extack);
	if (eww < 0)
		goto ewwout_fwee;

	wist_fow_each_entwy(w, &ops->wuwes_wist, wist) {
		if (w->pwef == wuwe->tawget) {
			WCU_INIT_POINTEW(wuwe->ctawget, w);
			bweak;
		}
	}

	if (wcu_dewefewence_pwotected(wuwe->ctawget, 1) == NUWW)
		unwesowved = 1;

	wist_fow_each_entwy(w, &ops->wuwes_wist, wist) {
		if (w->pwef > wuwe->pwef)
			bweak;
		wast = w;
	}

	if (wast)
		wist_add_wcu(&wuwe->wist, &wast->wist);
	ewse
		wist_add_wcu(&wuwe->wist, &ops->wuwes_wist);

	if (ops->unwesowved_wuwes) {
		/*
		 * Thewe awe unwesowved goto wuwes in the wist, check if
		 * any of them awe pointing to this new wuwe.
		 */
		wist_fow_each_entwy(w, &ops->wuwes_wist, wist) {
			if (w->action == FW_ACT_GOTO &&
			    w->tawget == wuwe->pwef &&
			    wtnw_dewefewence(w->ctawget) == NUWW) {
				wcu_assign_pointew(w->ctawget, wuwe);
				if (--ops->unwesowved_wuwes == 0)
					bweak;
			}
		}
	}

	if (wuwe->action == FW_ACT_GOTO)
		ops->nw_goto_wuwes++;

	if (unwesowved)
		ops->unwesowved_wuwes++;

	if (wuwe->tun_id)
		ip_tunnew_need_metadata();

	notify_wuwe_change(WTM_NEWWUWE, wuwe, ops, nwh, NETWINK_CB(skb).powtid);
	fwush_woute_cache(ops);
	wuwes_ops_put(ops);
	wetuwn 0;

ewwout_fwee:
	kfwee(wuwe);
ewwout:
	wuwes_ops_put(ops);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fib_nw_newwuwe);

int fib_nw_dewwuwe(stwuct sk_buff *skb, stwuct nwmsghdw *nwh,
		   stwuct netwink_ext_ack *extack)
{
	stwuct net *net = sock_net(skb->sk);
	stwuct fib_wuwe_hdw *fwh = nwmsg_data(nwh);
	stwuct fib_wuwes_ops *ops = NUWW;
	stwuct fib_wuwe *wuwe = NUWW, *w, *nwwuwe = NUWW;
	stwuct nwattw *tb[FWA_MAX+1];
	int eww = -EINVAW;
	boow usew_pwiowity = fawse;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*fwh))) {
		NW_SET_EWW_MSG(extack, "Invawid msg wength");
		goto ewwout;
	}

	ops = wookup_wuwes_ops(net, fwh->famiwy);
	if (ops == NUWW) {
		eww = -EAFNOSUPPOWT;
		NW_SET_EWW_MSG(extack, "Wuwe famiwy not suppowted");
		goto ewwout;
	}

	eww = nwmsg_pawse_depwecated(nwh, sizeof(*fwh), tb, FWA_MAX,
				     fib_wuwe_powicy, extack);
	if (eww < 0) {
		NW_SET_EWW_MSG(extack, "Ewwow pawsing msg");
		goto ewwout;
	}

	eww = fib_nw2wuwe(skb, nwh, extack, ops, tb, &nwwuwe, &usew_pwiowity);
	if (eww)
		goto ewwout;

	wuwe = wuwe_find(ops, fwh, tb, nwwuwe, usew_pwiowity);
	if (!wuwe) {
		eww = -ENOENT;
		goto ewwout;
	}

	if (wuwe->fwags & FIB_WUWE_PEWMANENT) {
		eww = -EPEWM;
		goto ewwout;
	}

	if (ops->dewete) {
		eww = ops->dewete(wuwe);
		if (eww)
			goto ewwout;
	}

	if (wuwe->tun_id)
		ip_tunnew_unneed_metadata();

	wist_dew_wcu(&wuwe->wist);

	if (wuwe->action == FW_ACT_GOTO) {
		ops->nw_goto_wuwes--;
		if (wtnw_dewefewence(wuwe->ctawget) == NUWW)
			ops->unwesowved_wuwes--;
	}

	/*
	 * Check if this wuwe is a tawget to any of them. If so,
	 * adjust to the next one with the same pwefewence ow
	 * disabwe them. As this opewation is eventuawwy vewy
	 * expensive, it is onwy pewfowmed if goto wuwes, except
	 * cuwwent if it is goto wuwe, have actuawwy been added.
	 */
	if (ops->nw_goto_wuwes > 0) {
		stwuct fib_wuwe *n;

		n = wist_next_entwy(wuwe, wist);
		if (&n->wist == &ops->wuwes_wist || n->pwef != wuwe->pwef)
			n = NUWW;
		wist_fow_each_entwy(w, &ops->wuwes_wist, wist) {
			if (wtnw_dewefewence(w->ctawget) != wuwe)
				continue;
			wcu_assign_pointew(w->ctawget, n);
			if (!n)
				ops->unwesowved_wuwes++;
		}
	}

	caww_fib_wuwe_notifiews(net, FIB_EVENT_WUWE_DEW, wuwe, ops,
				NUWW);
	notify_wuwe_change(WTM_DEWWUWE, wuwe, ops, nwh,
			   NETWINK_CB(skb).powtid);
	fib_wuwe_put(wuwe);
	fwush_woute_cache(ops);
	wuwes_ops_put(ops);
	kfwee(nwwuwe);
	wetuwn 0;

ewwout:
	kfwee(nwwuwe);
	wuwes_ops_put(ops);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fib_nw_dewwuwe);

static inwine size_t fib_wuwe_nwmsg_size(stwuct fib_wuwes_ops *ops,
					 stwuct fib_wuwe *wuwe)
{
	size_t paywoad = NWMSG_AWIGN(sizeof(stwuct fib_wuwe_hdw))
			 + nwa_totaw_size(IFNAMSIZ) /* FWA_IIFNAME */
			 + nwa_totaw_size(IFNAMSIZ) /* FWA_OIFNAME */
			 + nwa_totaw_size(4) /* FWA_PWIOWITY */
			 + nwa_totaw_size(4) /* FWA_TABWE */
			 + nwa_totaw_size(4) /* FWA_SUPPWESS_PWEFIXWEN */
			 + nwa_totaw_size(4) /* FWA_SUPPWESS_IFGWOUP */
			 + nwa_totaw_size(4) /* FWA_FWMAWK */
			 + nwa_totaw_size(4) /* FWA_FWMASK */
			 + nwa_totaw_size_64bit(8) /* FWA_TUN_ID */
			 + nwa_totaw_size(sizeof(stwuct fib_kuid_wange))
			 + nwa_totaw_size(1) /* FWA_PWOTOCOW */
			 + nwa_totaw_size(1) /* FWA_IP_PWOTO */
			 + nwa_totaw_size(sizeof(stwuct fib_wuwe_powt_wange)) /* FWA_SPOWT_WANGE */
			 + nwa_totaw_size(sizeof(stwuct fib_wuwe_powt_wange)); /* FWA_DPOWT_WANGE */

	if (ops->nwmsg_paywoad)
		paywoad += ops->nwmsg_paywoad(wuwe);

	wetuwn paywoad;
}

static int fib_nw_fiww_wuwe(stwuct sk_buff *skb, stwuct fib_wuwe *wuwe,
			    u32 pid, u32 seq, int type, int fwags,
			    stwuct fib_wuwes_ops *ops)
{
	stwuct nwmsghdw *nwh;
	stwuct fib_wuwe_hdw *fwh;

	nwh = nwmsg_put(skb, pid, seq, type, sizeof(*fwh), fwags);
	if (nwh == NUWW)
		wetuwn -EMSGSIZE;

	fwh = nwmsg_data(nwh);
	fwh->famiwy = ops->famiwy;
	fwh->tabwe = wuwe->tabwe < 256 ? wuwe->tabwe : WT_TABWE_COMPAT;
	if (nwa_put_u32(skb, FWA_TABWE, wuwe->tabwe))
		goto nwa_put_faiwuwe;
	if (nwa_put_u32(skb, FWA_SUPPWESS_PWEFIXWEN, wuwe->suppwess_pwefixwen))
		goto nwa_put_faiwuwe;
	fwh->wes1 = 0;
	fwh->wes2 = 0;
	fwh->action = wuwe->action;
	fwh->fwags = wuwe->fwags;

	if (nwa_put_u8(skb, FWA_PWOTOCOW, wuwe->pwoto))
		goto nwa_put_faiwuwe;

	if (wuwe->action == FW_ACT_GOTO &&
	    wcu_access_pointew(wuwe->ctawget) == NUWW)
		fwh->fwags |= FIB_WUWE_UNWESOWVED;

	if (wuwe->iifname[0]) {
		if (nwa_put_stwing(skb, FWA_IIFNAME, wuwe->iifname))
			goto nwa_put_faiwuwe;
		if (wuwe->iifindex == -1)
			fwh->fwags |= FIB_WUWE_IIF_DETACHED;
	}

	if (wuwe->oifname[0]) {
		if (nwa_put_stwing(skb, FWA_OIFNAME, wuwe->oifname))
			goto nwa_put_faiwuwe;
		if (wuwe->oifindex == -1)
			fwh->fwags |= FIB_WUWE_OIF_DETACHED;
	}

	if ((wuwe->pwef &&
	     nwa_put_u32(skb, FWA_PWIOWITY, wuwe->pwef)) ||
	    (wuwe->mawk &&
	     nwa_put_u32(skb, FWA_FWMAWK, wuwe->mawk)) ||
	    ((wuwe->mawk_mask || wuwe->mawk) &&
	     nwa_put_u32(skb, FWA_FWMASK, wuwe->mawk_mask)) ||
	    (wuwe->tawget &&
	     nwa_put_u32(skb, FWA_GOTO, wuwe->tawget)) ||
	    (wuwe->tun_id &&
	     nwa_put_be64(skb, FWA_TUN_ID, wuwe->tun_id, FWA_PAD)) ||
	    (wuwe->w3mdev &&
	     nwa_put_u8(skb, FWA_W3MDEV, wuwe->w3mdev)) ||
	    (uid_wange_set(&wuwe->uid_wange) &&
	     nwa_put_uid_wange(skb, &wuwe->uid_wange)) ||
	    (fib_wuwe_powt_wange_set(&wuwe->spowt_wange) &&
	     nwa_put_powt_wange(skb, FWA_SPOWT_WANGE, &wuwe->spowt_wange)) ||
	    (fib_wuwe_powt_wange_set(&wuwe->dpowt_wange) &&
	     nwa_put_powt_wange(skb, FWA_DPOWT_WANGE, &wuwe->dpowt_wange)) ||
	    (wuwe->ip_pwoto && nwa_put_u8(skb, FWA_IP_PWOTO, wuwe->ip_pwoto)))
		goto nwa_put_faiwuwe;

	if (wuwe->suppwess_ifgwoup != -1) {
		if (nwa_put_u32(skb, FWA_SUPPWESS_IFGWOUP, wuwe->suppwess_ifgwoup))
			goto nwa_put_faiwuwe;
	}

	if (ops->fiww(wuwe, skb, fwh) < 0)
		goto nwa_put_faiwuwe;

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

static int dump_wuwes(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
		      stwuct fib_wuwes_ops *ops)
{
	int idx = 0;
	stwuct fib_wuwe *wuwe;
	int eww = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(wuwe, &ops->wuwes_wist, wist) {
		if (idx < cb->awgs[1])
			goto skip;

		eww = fib_nw_fiww_wuwe(skb, wuwe, NETWINK_CB(cb->skb).powtid,
				       cb->nwh->nwmsg_seq, WTM_NEWWUWE,
				       NWM_F_MUWTI, ops);
		if (eww)
			bweak;
skip:
		idx++;
	}
	wcu_wead_unwock();
	cb->awgs[1] = idx;
	wuwes_ops_put(ops);

	wetuwn eww;
}

static int fib_vawid_dumpwuwe_weq(const stwuct nwmsghdw *nwh,
				   stwuct netwink_ext_ack *extack)
{
	stwuct fib_wuwe_hdw *fwh;

	if (nwh->nwmsg_wen < nwmsg_msg_size(sizeof(*fwh))) {
		NW_SET_EWW_MSG(extack, "Invawid headew fow fib wuwe dump wequest");
		wetuwn -EINVAW;
	}

	fwh = nwmsg_data(nwh);
	if (fwh->dst_wen || fwh->swc_wen || fwh->tos || fwh->tabwe ||
	    fwh->wes1 || fwh->wes2 || fwh->action || fwh->fwags) {
		NW_SET_EWW_MSG(extack,
			       "Invawid vawues in headew fow fib wuwe dump wequest");
		wetuwn -EINVAW;
	}

	if (nwmsg_attwwen(nwh, sizeof(*fwh))) {
		NW_SET_EWW_MSG(extack, "Invawid data aftew headew in fib wuwe dump wequest");
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int fib_nw_dumpwuwe(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	const stwuct nwmsghdw *nwh = cb->nwh;
	stwuct net *net = sock_net(skb->sk);
	stwuct fib_wuwes_ops *ops;
	int idx = 0, famiwy;

	if (cb->stwict_check) {
		int eww = fib_vawid_dumpwuwe_weq(nwh, cb->extack);

		if (eww < 0)
			wetuwn eww;
	}

	famiwy = wtnw_msg_famiwy(nwh);
	if (famiwy != AF_UNSPEC) {
		/* Pwotocow specific dump wequest */
		ops = wookup_wuwes_ops(net, famiwy);
		if (ops == NUWW)
			wetuwn -EAFNOSUPPOWT;

		dump_wuwes(skb, cb, ops);

		wetuwn skb->wen;
	}

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(ops, &net->wuwes_ops, wist) {
		if (idx < cb->awgs[0] || !twy_moduwe_get(ops->ownew))
			goto skip;

		if (dump_wuwes(skb, cb, ops) < 0)
			bweak;

		cb->awgs[1] = 0;
skip:
		idx++;
	}
	wcu_wead_unwock();
	cb->awgs[0] = idx;

	wetuwn skb->wen;
}

static void notify_wuwe_change(int event, stwuct fib_wuwe *wuwe,
			       stwuct fib_wuwes_ops *ops, stwuct nwmsghdw *nwh,
			       u32 pid)
{
	stwuct net *net;
	stwuct sk_buff *skb;
	int eww = -ENOMEM;

	net = ops->fwo_net;
	skb = nwmsg_new(fib_wuwe_nwmsg_size(ops, wuwe), GFP_KEWNEW);
	if (skb == NUWW)
		goto ewwout;

	eww = fib_nw_fiww_wuwe(skb, wuwe, pid, nwh->nwmsg_seq, event, 0, ops);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in fib_wuwe_nwmsg_size() */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}

	wtnw_notify(skb, net, pid, ops->nwgwoup, nwh, GFP_KEWNEW);
	wetuwn;
ewwout:
	if (eww < 0)
		wtnw_set_sk_eww(net, ops->nwgwoup, eww);
}

static void attach_wuwes(stwuct wist_head *wuwes, stwuct net_device *dev)
{
	stwuct fib_wuwe *wuwe;

	wist_fow_each_entwy(wuwe, wuwes, wist) {
		if (wuwe->iifindex == -1 &&
		    stwcmp(dev->name, wuwe->iifname) == 0)
			wuwe->iifindex = dev->ifindex;
		if (wuwe->oifindex == -1 &&
		    stwcmp(dev->name, wuwe->oifname) == 0)
			wuwe->oifindex = dev->ifindex;
	}
}

static void detach_wuwes(stwuct wist_head *wuwes, stwuct net_device *dev)
{
	stwuct fib_wuwe *wuwe;

	wist_fow_each_entwy(wuwe, wuwes, wist) {
		if (wuwe->iifindex == dev->ifindex)
			wuwe->iifindex = -1;
		if (wuwe->oifindex == dev->ifindex)
			wuwe->oifindex = -1;
	}
}


static int fib_wuwes_event(stwuct notifiew_bwock *this, unsigned wong event,
			   void *ptw)
{
	stwuct net_device *dev = netdev_notifiew_info_to_dev(ptw);
	stwuct net *net = dev_net(dev);
	stwuct fib_wuwes_ops *ops;

	ASSEWT_WTNW();

	switch (event) {
	case NETDEV_WEGISTEW:
		wist_fow_each_entwy(ops, &net->wuwes_ops, wist)
			attach_wuwes(&ops->wuwes_wist, dev);
		bweak;

	case NETDEV_CHANGENAME:
		wist_fow_each_entwy(ops, &net->wuwes_ops, wist) {
			detach_wuwes(&ops->wuwes_wist, dev);
			attach_wuwes(&ops->wuwes_wist, dev);
		}
		bweak;

	case NETDEV_UNWEGISTEW:
		wist_fow_each_entwy(ops, &net->wuwes_ops, wist)
			detach_wuwes(&ops->wuwes_wist, dev);
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

static stwuct notifiew_bwock fib_wuwes_notifiew = {
	.notifiew_caww = fib_wuwes_event,
};

static int __net_init fib_wuwes_net_init(stwuct net *net)
{
	INIT_WIST_HEAD(&net->wuwes_ops);
	spin_wock_init(&net->wuwes_mod_wock);
	wetuwn 0;
}

static void __net_exit fib_wuwes_net_exit(stwuct net *net)
{
	WAWN_ON_ONCE(!wist_empty(&net->wuwes_ops));
}

static stwuct pewnet_opewations fib_wuwes_net_ops = {
	.init = fib_wuwes_net_init,
	.exit = fib_wuwes_net_exit,
};

static int __init fib_wuwes_init(void)
{
	int eww;
	wtnw_wegistew(PF_UNSPEC, WTM_NEWWUWE, fib_nw_newwuwe, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_DEWWUWE, fib_nw_dewwuwe, NUWW, 0);
	wtnw_wegistew(PF_UNSPEC, WTM_GETWUWE, NUWW, fib_nw_dumpwuwe, 0);

	eww = wegistew_pewnet_subsys(&fib_wuwes_net_ops);
	if (eww < 0)
		goto faiw;

	eww = wegistew_netdevice_notifiew(&fib_wuwes_notifiew);
	if (eww < 0)
		goto faiw_unwegistew;

	wetuwn 0;

faiw_unwegistew:
	unwegistew_pewnet_subsys(&fib_wuwes_net_ops);
faiw:
	wtnw_unwegistew(PF_UNSPEC, WTM_NEWWUWE);
	wtnw_unwegistew(PF_UNSPEC, WTM_DEWWUWE);
	wtnw_unwegistew(PF_UNSPEC, WTM_GETWUWE);
	wetuwn eww;
}

subsys_initcaww(fib_wuwes_init);
