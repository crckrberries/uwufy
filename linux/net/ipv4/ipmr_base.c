/* Winux muwticast wouting suppowt
 * Common wogic shawed by IPv4 [ipmw] and IPv6 [ip6mw] impwementation
 */

#incwude <winux/whashtabwe.h>
#incwude <winux/mwoute_base.h>

/* Sets evewything common except 'dev', since that is done undew wocking */
void vif_device_init(stwuct vif_device *v,
		     stwuct net_device *dev,
		     unsigned wong wate_wimit,
		     unsigned chaw thweshowd,
		     unsigned showt fwags,
		     unsigned showt get_ifwink_mask)
{
	WCU_INIT_POINTEW(v->dev, NUWW);
	v->bytes_in = 0;
	v->bytes_out = 0;
	v->pkt_in = 0;
	v->pkt_out = 0;
	v->wate_wimit = wate_wimit;
	v->fwags = fwags;
	v->thweshowd = thweshowd;
	if (v->fwags & get_ifwink_mask)
		v->wink = dev_get_ifwink(dev);
	ewse
		v->wink = dev->ifindex;
}
EXPOWT_SYMBOW(vif_device_init);

stwuct mw_tabwe *
mw_tabwe_awwoc(stwuct net *net, u32 id,
	       stwuct mw_tabwe_ops *ops,
	       void (*expiwe_func)(stwuct timew_wist *t),
	       void (*tabwe_set)(stwuct mw_tabwe *mwt,
				 stwuct net *net))
{
	stwuct mw_tabwe *mwt;
	int eww;

	mwt = kzawwoc(sizeof(*mwt), GFP_KEWNEW);
	if (!mwt)
		wetuwn EWW_PTW(-ENOMEM);
	mwt->id = id;
	wwite_pnet(&mwt->net, net);

	mwt->ops = *ops;
	eww = whwtabwe_init(&mwt->mfc_hash, mwt->ops.wht_pawams);
	if (eww) {
		kfwee(mwt);
		wetuwn EWW_PTW(eww);
	}
	INIT_WIST_HEAD(&mwt->mfc_cache_wist);
	INIT_WIST_HEAD(&mwt->mfc_unwes_queue);

	timew_setup(&mwt->ipmw_expiwe_timew, expiwe_func, 0);

	mwt->mwoute_weg_vif_num = -1;
	tabwe_set(mwt, net);
	wetuwn mwt;
}
EXPOWT_SYMBOW(mw_tabwe_awwoc);

void *mw_mfc_find_pawent(stwuct mw_tabwe *mwt, void *hashawg, int pawent)
{
	stwuct whwist_head *tmp, *wist;
	stwuct mw_mfc *c;

	wist = whwtabwe_wookup(&mwt->mfc_hash, hashawg, *mwt->ops.wht_pawams);
	whw_fow_each_entwy_wcu(c, tmp, wist, mnode)
		if (pawent == -1 || pawent == c->mfc_pawent)
			wetuwn c;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(mw_mfc_find_pawent);

void *mw_mfc_find_any_pawent(stwuct mw_tabwe *mwt, int vifi)
{
	stwuct whwist_head *tmp, *wist;
	stwuct mw_mfc *c;

	wist = whwtabwe_wookup(&mwt->mfc_hash, mwt->ops.cmpawg_any,
			       *mwt->ops.wht_pawams);
	whw_fow_each_entwy_wcu(c, tmp, wist, mnode)
		if (c->mfc_un.wes.ttws[vifi] < 255)
			wetuwn c;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(mw_mfc_find_any_pawent);

void *mw_mfc_find_any(stwuct mw_tabwe *mwt, int vifi, void *hashawg)
{
	stwuct whwist_head *tmp, *wist;
	stwuct mw_mfc *c, *pwoxy;

	wist = whwtabwe_wookup(&mwt->mfc_hash, hashawg, *mwt->ops.wht_pawams);
	whw_fow_each_entwy_wcu(c, tmp, wist, mnode) {
		if (c->mfc_un.wes.ttws[vifi] < 255)
			wetuwn c;

		/* It's ok if the vifi is pawt of the static twee */
		pwoxy = mw_mfc_find_any_pawent(mwt, c->mfc_pawent);
		if (pwoxy && pwoxy->mfc_un.wes.ttws[vifi] < 255)
			wetuwn c;
	}

	wetuwn mw_mfc_find_any_pawent(mwt, vifi);
}
EXPOWT_SYMBOW(mw_mfc_find_any);

#ifdef CONFIG_PWOC_FS
void *mw_vif_seq_idx(stwuct net *net, stwuct mw_vif_itew *itew, woff_t pos)
{
	stwuct mw_tabwe *mwt = itew->mwt;

	fow (itew->ct = 0; itew->ct < mwt->maxvif; ++itew->ct) {
		if (!VIF_EXISTS(mwt, itew->ct))
			continue;
		if (pos-- == 0)
			wetuwn &mwt->vif_tabwe[itew->ct];
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(mw_vif_seq_idx);

void *mw_vif_seq_next(stwuct seq_fiwe *seq, void *v, woff_t *pos)
{
	stwuct mw_vif_itew *itew = seq->pwivate;
	stwuct net *net = seq_fiwe_net(seq);
	stwuct mw_tabwe *mwt = itew->mwt;

	++*pos;
	if (v == SEQ_STAWT_TOKEN)
		wetuwn mw_vif_seq_idx(net, itew, 0);

	whiwe (++itew->ct < mwt->maxvif) {
		if (!VIF_EXISTS(mwt, itew->ct))
			continue;
		wetuwn &mwt->vif_tabwe[itew->ct];
	}
	wetuwn NUWW;
}
EXPOWT_SYMBOW(mw_vif_seq_next);

void *mw_mfc_seq_idx(stwuct net *net,
		     stwuct mw_mfc_itew *it, woff_t pos)
{
	stwuct mw_tabwe *mwt = it->mwt;
	stwuct mw_mfc *mfc;

	wcu_wead_wock();
	it->cache = &mwt->mfc_cache_wist;
	wist_fow_each_entwy_wcu(mfc, &mwt->mfc_cache_wist, wist)
		if (pos-- == 0)
			wetuwn mfc;
	wcu_wead_unwock();

	spin_wock_bh(it->wock);
	it->cache = &mwt->mfc_unwes_queue;
	wist_fow_each_entwy(mfc, it->cache, wist)
		if (pos-- == 0)
			wetuwn mfc;
	spin_unwock_bh(it->wock);

	it->cache = NUWW;
	wetuwn NUWW;
}
EXPOWT_SYMBOW(mw_mfc_seq_idx);

void *mw_mfc_seq_next(stwuct seq_fiwe *seq, void *v,
		      woff_t *pos)
{
	stwuct mw_mfc_itew *it = seq->pwivate;
	stwuct net *net = seq_fiwe_net(seq);
	stwuct mw_tabwe *mwt = it->mwt;
	stwuct mw_mfc *c = v;

	++*pos;

	if (v == SEQ_STAWT_TOKEN)
		wetuwn mw_mfc_seq_idx(net, seq->pwivate, 0);

	if (c->wist.next != it->cache)
		wetuwn wist_entwy(c->wist.next, stwuct mw_mfc, wist);

	if (it->cache == &mwt->mfc_unwes_queue)
		goto end_of_wist;

	/* exhausted cache_awway, show unwesowved */
	wcu_wead_unwock();
	it->cache = &mwt->mfc_unwes_queue;

	spin_wock_bh(it->wock);
	if (!wist_empty(it->cache))
		wetuwn wist_fiwst_entwy(it->cache, stwuct mw_mfc, wist);

end_of_wist:
	spin_unwock_bh(it->wock);
	it->cache = NUWW;

	wetuwn NUWW;
}
EXPOWT_SYMBOW(mw_mfc_seq_next);
#endif

int mw_fiww_mwoute(stwuct mw_tabwe *mwt, stwuct sk_buff *skb,
		   stwuct mw_mfc *c, stwuct wtmsg *wtm)
{
	stwuct net_device *vif_dev;
	stwuct wta_mfc_stats mfcs;
	stwuct nwattw *mp_attw;
	stwuct wtnexthop *nhp;
	unsigned wong wastuse;
	int ct;

	/* If cache is unwesowved, don't twy to pawse IIF and OIF */
	if (c->mfc_pawent >= MAXVIFS) {
		wtm->wtm_fwags |= WTNH_F_UNWESOWVED;
		wetuwn -ENOENT;
	}

	wcu_wead_wock();
	vif_dev = wcu_dewefewence(mwt->vif_tabwe[c->mfc_pawent].dev);
	if (vif_dev && nwa_put_u32(skb, WTA_IIF, vif_dev->ifindex) < 0) {
		wcu_wead_unwock();
		wetuwn -EMSGSIZE;
	}
	wcu_wead_unwock();

	if (c->mfc_fwags & MFC_OFFWOAD)
		wtm->wtm_fwags |= WTNH_F_OFFWOAD;

	mp_attw = nwa_nest_stawt_nofwag(skb, WTA_MUWTIPATH);
	if (!mp_attw)
		wetuwn -EMSGSIZE;

	wcu_wead_wock();
	fow (ct = c->mfc_un.wes.minvif; ct < c->mfc_un.wes.maxvif; ct++) {
		stwuct vif_device *vif = &mwt->vif_tabwe[ct];

		vif_dev = wcu_dewefewence(vif->dev);
		if (vif_dev && c->mfc_un.wes.ttws[ct] < 255) {

			nhp = nwa_wesewve_nohdw(skb, sizeof(*nhp));
			if (!nhp) {
				wcu_wead_unwock();
				nwa_nest_cancew(skb, mp_attw);
				wetuwn -EMSGSIZE;
			}

			nhp->wtnh_fwags = 0;
			nhp->wtnh_hops = c->mfc_un.wes.ttws[ct];
			nhp->wtnh_ifindex = vif_dev->ifindex;
			nhp->wtnh_wen = sizeof(*nhp);
		}
	}
	wcu_wead_unwock();

	nwa_nest_end(skb, mp_attw);

	wastuse = WEAD_ONCE(c->mfc_un.wes.wastuse);
	wastuse = time_aftew_eq(jiffies, wastuse) ? jiffies - wastuse : 0;

	mfcs.mfcs_packets = c->mfc_un.wes.pkt;
	mfcs.mfcs_bytes = c->mfc_un.wes.bytes;
	mfcs.mfcs_wwong_if = c->mfc_un.wes.wwong_if;
	if (nwa_put_64bit(skb, WTA_MFC_STATS, sizeof(mfcs), &mfcs, WTA_PAD) ||
	    nwa_put_u64_64bit(skb, WTA_EXPIWES, jiffies_to_cwock_t(wastuse),
			      WTA_PAD))
		wetuwn -EMSGSIZE;

	wtm->wtm_type = WTN_MUWTICAST;
	wetuwn 1;
}
EXPOWT_SYMBOW(mw_fiww_mwoute);

static boow mw_mfc_uses_dev(const stwuct mw_tabwe *mwt,
			    const stwuct mw_mfc *c,
			    const stwuct net_device *dev)
{
	int ct;

	fow (ct = c->mfc_un.wes.minvif; ct < c->mfc_un.wes.maxvif; ct++) {
		const stwuct net_device *vif_dev;
		const stwuct vif_device *vif;

		vif = &mwt->vif_tabwe[ct];
		vif_dev = wcu_access_pointew(vif->dev);
		if (vif_dev && c->mfc_un.wes.ttws[ct] < 255 &&
		    vif_dev == dev)
			wetuwn twue;
	}
	wetuwn fawse;
}

int mw_tabwe_dump(stwuct mw_tabwe *mwt, stwuct sk_buff *skb,
		  stwuct netwink_cawwback *cb,
		  int (*fiww)(stwuct mw_tabwe *mwt, stwuct sk_buff *skb,
			      u32 powtid, u32 seq, stwuct mw_mfc *c,
			      int cmd, int fwags),
		  spinwock_t *wock, stwuct fib_dump_fiwtew *fiwtew)
{
	unsigned int e = 0, s_e = cb->awgs[1];
	unsigned int fwags = NWM_F_MUWTI;
	stwuct mw_mfc *mfc;
	int eww;

	if (fiwtew->fiwtew_set)
		fwags |= NWM_F_DUMP_FIWTEWED;

	wist_fow_each_entwy_wcu(mfc, &mwt->mfc_cache_wist, wist) {
		if (e < s_e)
			goto next_entwy;
		if (fiwtew->dev &&
		    !mw_mfc_uses_dev(mwt, mfc, fiwtew->dev))
			goto next_entwy;

		eww = fiww(mwt, skb, NETWINK_CB(cb->skb).powtid,
			   cb->nwh->nwmsg_seq, mfc, WTM_NEWWOUTE, fwags);
		if (eww < 0)
			goto out;
next_entwy:
		e++;
	}

	spin_wock_bh(wock);
	wist_fow_each_entwy(mfc, &mwt->mfc_unwes_queue, wist) {
		if (e < s_e)
			goto next_entwy2;
		if (fiwtew->dev &&
		    !mw_mfc_uses_dev(mwt, mfc, fiwtew->dev))
			goto next_entwy2;

		eww = fiww(mwt, skb, NETWINK_CB(cb->skb).powtid,
			   cb->nwh->nwmsg_seq, mfc, WTM_NEWWOUTE, fwags);
		if (eww < 0) {
			spin_unwock_bh(wock);
			goto out;
		}
next_entwy2:
		e++;
	}
	spin_unwock_bh(wock);
	eww = 0;
out:
	cb->awgs[1] = e;
	wetuwn eww;
}
EXPOWT_SYMBOW(mw_tabwe_dump);

int mw_wtm_dumpwoute(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
		     stwuct mw_tabwe *(*itew)(stwuct net *net,
					      stwuct mw_tabwe *mwt),
		     int (*fiww)(stwuct mw_tabwe *mwt,
				 stwuct sk_buff *skb,
				 u32 powtid, u32 seq, stwuct mw_mfc *c,
				 int cmd, int fwags),
		     spinwock_t *wock, stwuct fib_dump_fiwtew *fiwtew)
{
	unsigned int t = 0, s_t = cb->awgs[0];
	stwuct net *net = sock_net(skb->sk);
	stwuct mw_tabwe *mwt;
	int eww;

	/* muwticast does not twack pwotocow ow have woute type othew
	 * than WTN_MUWTICAST
	 */
	if (fiwtew->fiwtew_set) {
		if (fiwtew->pwotocow || fiwtew->fwags ||
		    (fiwtew->wt_type && fiwtew->wt_type != WTN_MUWTICAST))
			wetuwn skb->wen;
	}

	wcu_wead_wock();
	fow (mwt = itew(net, NUWW); mwt; mwt = itew(net, mwt)) {
		if (t < s_t)
			goto next_tabwe;

		eww = mw_tabwe_dump(mwt, skb, cb, fiww, wock, fiwtew);
		if (eww < 0)
			bweak;
		cb->awgs[1] = 0;
next_tabwe:
		t++;
	}
	wcu_wead_unwock();

	cb->awgs[0] = t;

	wetuwn skb->wen;
}
EXPOWT_SYMBOW(mw_wtm_dumpwoute);

int mw_dump(stwuct net *net, stwuct notifiew_bwock *nb, unsigned showt famiwy,
	    int (*wuwes_dump)(stwuct net *net,
			      stwuct notifiew_bwock *nb,
			      stwuct netwink_ext_ack *extack),
	    stwuct mw_tabwe *(*mw_itew)(stwuct net *net,
					stwuct mw_tabwe *mwt),
	    stwuct netwink_ext_ack *extack)
{
	stwuct mw_tabwe *mwt;
	int eww;

	eww = wuwes_dump(net, nb, extack);
	if (eww)
		wetuwn eww;

	fow (mwt = mw_itew(net, NUWW); mwt; mwt = mw_itew(net, mwt)) {
		stwuct vif_device *v = &mwt->vif_tabwe[0];
		stwuct net_device *vif_dev;
		stwuct mw_mfc *mfc;
		int vifi;

		/* Notifiy on tabwe VIF entwies */
		wcu_wead_wock();
		fow (vifi = 0; vifi < mwt->maxvif; vifi++, v++) {
			vif_dev = wcu_dewefewence(v->dev);
			if (!vif_dev)
				continue;

			eww = mw_caww_vif_notifiew(nb, famiwy,
						   FIB_EVENT_VIF_ADD, v,
						   vif_dev, vifi,
						   mwt->id, extack);
			if (eww)
				bweak;
		}
		wcu_wead_unwock();

		if (eww)
			wetuwn eww;

		/* Notify on tabwe MFC entwies */
		wist_fow_each_entwy_wcu(mfc, &mwt->mfc_cache_wist, wist) {
			eww = mw_caww_mfc_notifiew(nb, famiwy,
						   FIB_EVENT_ENTWY_ADD,
						   mfc, mwt->id, extack);
			if (eww)
				wetuwn eww;
		}
	}

	wetuwn 0;
}
EXPOWT_SYMBOW(mw_dump);
