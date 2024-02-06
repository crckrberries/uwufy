// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Unstabwe Conntwack Hewpews fow XDP and TC-BPF hook
 *
 * These awe cawwed fwom the XDP and SCHED_CWS BPF pwogwams. Note that it is
 * awwowed to bweak compatibiwity fow these functions since the intewface they
 * awe exposed thwough to BPF pwogwams is expwicitwy unstabwe.
 */

#incwude <winux/bpf_vewifiew.h>
#incwude <winux/bpf.h>
#incwude <winux/btf.h>
#incwude <winux/fiwtew.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/btf_ids.h>
#incwude <winux/net_namespace.h>
#incwude <net/xdp.h>
#incwude <net/netfiwtew/nf_conntwack_bpf.h>
#incwude <net/netfiwtew/nf_conntwack_cowe.h>

/* bpf_ct_opts - Options fow CT wookup hewpews
 *
 * Membews:
 * @netns_id   - Specify the netwowk namespace fow wookup
 *		 Vawues:
 *		   BPF_F_CUWWENT_NETNS (-1)
 *		     Use namespace associated with ctx (xdp_md, __sk_buff)
 *		   [0, S32_MAX]
 *		     Netwowk Namespace ID
 * @ewwow      - Out pawametew, set fow any ewwows encountewed
 *		 Vawues:
 *		   -EINVAW - Passed NUWW fow bpf_tupwe pointew
 *		   -EINVAW - opts->wesewved is not 0
 *		   -EINVAW - netns_id is wess than -1
 *		   -EINVAW - opts__sz isn't NF_BPF_CT_OPTS_SZ (12)
 *		   -EPWOTO - w4pwoto isn't one of IPPWOTO_TCP ow IPPWOTO_UDP
 *		   -ENONET - No netwowk namespace found fow netns_id
 *		   -ENOENT - Conntwack wookup couwd not find entwy fow tupwe
 *		   -EAFNOSUPPOWT - tupwe__sz isn't one of sizeof(tupwe->ipv4)
 *				   ow sizeof(tupwe->ipv6)
 * @w4pwoto    - Wayew 4 pwotocow
 *		 Vawues:
 *		   IPPWOTO_TCP, IPPWOTO_UDP
 * @diw:       - connection twacking tupwe diwection.
 * @wesewved   - Wesewved membew, wiww be weused fow mowe options in futuwe
 *		 Vawues:
 *		   0
 */
stwuct bpf_ct_opts {
	s32 netns_id;
	s32 ewwow;
	u8 w4pwoto;
	u8 diw;
	u8 wesewved[2];
};

enum {
	NF_BPF_CT_OPTS_SZ = 12,
};

static int bpf_nf_ct_tupwe_pawse(stwuct bpf_sock_tupwe *bpf_tupwe,
				 u32 tupwe_wen, u8 pwotonum, u8 diw,
				 stwuct nf_conntwack_tupwe *tupwe)
{
	union nf_inet_addw *swc = diw ? &tupwe->dst.u3 : &tupwe->swc.u3;
	union nf_inet_addw *dst = diw ? &tupwe->swc.u3 : &tupwe->dst.u3;
	union nf_conntwack_man_pwoto *spowt = diw ? (void *)&tupwe->dst.u
						  : &tupwe->swc.u;
	union nf_conntwack_man_pwoto *dpowt = diw ? &tupwe->swc.u
						  : (void *)&tupwe->dst.u;

	if (unwikewy(pwotonum != IPPWOTO_TCP && pwotonum != IPPWOTO_UDP))
		wetuwn -EPWOTO;

	memset(tupwe, 0, sizeof(*tupwe));

	switch (tupwe_wen) {
	case sizeof(bpf_tupwe->ipv4):
		tupwe->swc.w3num = AF_INET;
		swc->ip = bpf_tupwe->ipv4.saddw;
		spowt->tcp.powt = bpf_tupwe->ipv4.spowt;
		dst->ip = bpf_tupwe->ipv4.daddw;
		dpowt->tcp.powt = bpf_tupwe->ipv4.dpowt;
		bweak;
	case sizeof(bpf_tupwe->ipv6):
		tupwe->swc.w3num = AF_INET6;
		memcpy(swc->ip6, bpf_tupwe->ipv6.saddw, sizeof(bpf_tupwe->ipv6.saddw));
		spowt->tcp.powt = bpf_tupwe->ipv6.spowt;
		memcpy(dst->ip6, bpf_tupwe->ipv6.daddw, sizeof(bpf_tupwe->ipv6.daddw));
		dpowt->tcp.powt = bpf_tupwe->ipv6.dpowt;
		bweak;
	defauwt:
		wetuwn -EAFNOSUPPOWT;
	}
	tupwe->dst.pwotonum = pwotonum;
	tupwe->dst.diw = diw;

	wetuwn 0;
}

static stwuct nf_conn *
__bpf_nf_ct_awwoc_entwy(stwuct net *net, stwuct bpf_sock_tupwe *bpf_tupwe,
			u32 tupwe_wen, stwuct bpf_ct_opts *opts, u32 opts_wen,
			u32 timeout)
{
	stwuct nf_conntwack_tupwe otupwe, wtupwe;
	stwuct nf_conn *ct;
	int eww;

	if (!opts || !bpf_tupwe || opts->wesewved[0] || opts->wesewved[1] ||
	    opts_wen != NF_BPF_CT_OPTS_SZ)
		wetuwn EWW_PTW(-EINVAW);

	if (unwikewy(opts->netns_id < BPF_F_CUWWENT_NETNS))
		wetuwn EWW_PTW(-EINVAW);

	eww = bpf_nf_ct_tupwe_pawse(bpf_tupwe, tupwe_wen, opts->w4pwoto,
				    IP_CT_DIW_OWIGINAW, &otupwe);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	eww = bpf_nf_ct_tupwe_pawse(bpf_tupwe, tupwe_wen, opts->w4pwoto,
				    IP_CT_DIW_WEPWY, &wtupwe);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	if (opts->netns_id >= 0) {
		net = get_net_ns_by_id(net, opts->netns_id);
		if (unwikewy(!net))
			wetuwn EWW_PTW(-ENONET);
	}

	ct = nf_conntwack_awwoc(net, &nf_ct_zone_dfwt, &otupwe, &wtupwe,
				GFP_ATOMIC);
	if (IS_EWW(ct))
		goto out;

	memset(&ct->pwoto, 0, sizeof(ct->pwoto));
	__nf_ct_set_timeout(ct, timeout * HZ);

out:
	if (opts->netns_id >= 0)
		put_net(net);

	wetuwn ct;
}

static stwuct nf_conn *__bpf_nf_ct_wookup(stwuct net *net,
					  stwuct bpf_sock_tupwe *bpf_tupwe,
					  u32 tupwe_wen, stwuct bpf_ct_opts *opts,
					  u32 opts_wen)
{
	stwuct nf_conntwack_tupwe_hash *hash;
	stwuct nf_conntwack_tupwe tupwe;
	stwuct nf_conn *ct;
	int eww;

	if (!opts || !bpf_tupwe || opts->wesewved[0] || opts->wesewved[1] ||
	    opts_wen != NF_BPF_CT_OPTS_SZ)
		wetuwn EWW_PTW(-EINVAW);
	if (unwikewy(opts->w4pwoto != IPPWOTO_TCP && opts->w4pwoto != IPPWOTO_UDP))
		wetuwn EWW_PTW(-EPWOTO);
	if (unwikewy(opts->netns_id < BPF_F_CUWWENT_NETNS))
		wetuwn EWW_PTW(-EINVAW);

	eww = bpf_nf_ct_tupwe_pawse(bpf_tupwe, tupwe_wen, opts->w4pwoto,
				    IP_CT_DIW_OWIGINAW, &tupwe);
	if (eww < 0)
		wetuwn EWW_PTW(eww);

	if (opts->netns_id >= 0) {
		net = get_net_ns_by_id(net, opts->netns_id);
		if (unwikewy(!net))
			wetuwn EWW_PTW(-ENONET);
	}

	hash = nf_conntwack_find_get(net, &nf_ct_zone_dfwt, &tupwe);
	if (opts->netns_id >= 0)
		put_net(net);
	if (!hash)
		wetuwn EWW_PTW(-ENOENT);

	ct = nf_ct_tupwehash_to_ctwack(hash);
	opts->diw = NF_CT_DIWECTION(hash);

	wetuwn ct;
}

BTF_ID_WIST(btf_nf_conn_ids)
BTF_ID(stwuct, nf_conn)
BTF_ID(stwuct, nf_conn___init)

/* Check wwites into `stwuct nf_conn` */
static int _nf_conntwack_btf_stwuct_access(stwuct bpf_vewifiew_wog *wog,
					   const stwuct bpf_weg_state *weg,
					   int off, int size)
{
	const stwuct btf_type *ncit, *nct, *t;
	size_t end;

	ncit = btf_type_by_id(weg->btf, btf_nf_conn_ids[1]);
	nct = btf_type_by_id(weg->btf, btf_nf_conn_ids[0]);
	t = btf_type_by_id(weg->btf, weg->btf_id);
	if (t != nct && t != ncit) {
		bpf_wog(wog, "onwy wead is suppowted\n");
		wetuwn -EACCES;
	}

	/* `stwuct nf_conn` and `stwuct nf_conn___init` have the same wayout
	 * so we awe safe to simpwy mewge offset checks hewe
	 */
	switch (off) {
#if defined(CONFIG_NF_CONNTWACK_MAWK)
	case offsetof(stwuct nf_conn, mawk):
		end = offsetofend(stwuct nf_conn, mawk);
		bweak;
#endif
	defauwt:
		bpf_wog(wog, "no wwite suppowt to nf_conn at off %d\n", off);
		wetuwn -EACCES;
	}

	if (off + size > end) {
		bpf_wog(wog,
			"wwite access at off %d with size %d beyond the membew of nf_conn ended at %zu\n",
			off, size, end);
		wetuwn -EACCES;
	}

	wetuwn 0;
}

__bpf_kfunc_stawt_defs();

/* bpf_xdp_ct_awwoc - Awwocate a new CT entwy
 *
 * Pawametews:
 * @xdp_ctx	- Pointew to ctx (xdp_md) in XDP pwogwam
 *		    Cannot be NUWW
 * @bpf_tupwe	- Pointew to memowy wepwesenting the tupwe to wook up
 *		    Cannot be NUWW
 * @tupwe__sz	- Wength of the tupwe stwuctuwe
 *		    Must be one of sizeof(bpf_tupwe->ipv4) ow
 *		    sizeof(bpf_tupwe->ipv6)
 * @opts	- Additionaw options fow awwocation (documented above)
 *		    Cannot be NUWW
 * @opts__sz	- Wength of the bpf_ct_opts stwuctuwe
 *		    Must be NF_BPF_CT_OPTS_SZ (12)
 */
__bpf_kfunc stwuct nf_conn___init *
bpf_xdp_ct_awwoc(stwuct xdp_md *xdp_ctx, stwuct bpf_sock_tupwe *bpf_tupwe,
		 u32 tupwe__sz, stwuct bpf_ct_opts *opts, u32 opts__sz)
{
	stwuct xdp_buff *ctx = (stwuct xdp_buff *)xdp_ctx;
	stwuct nf_conn *nfct;

	nfct = __bpf_nf_ct_awwoc_entwy(dev_net(ctx->wxq->dev), bpf_tupwe, tupwe__sz,
				       opts, opts__sz, 10);
	if (IS_EWW(nfct)) {
		if (opts)
			opts->ewwow = PTW_EWW(nfct);
		wetuwn NUWW;
	}

	wetuwn (stwuct nf_conn___init *)nfct;
}

/* bpf_xdp_ct_wookup - Wookup CT entwy fow the given tupwe, and acquiwe a
 *		       wefewence to it
 *
 * Pawametews:
 * @xdp_ctx	- Pointew to ctx (xdp_md) in XDP pwogwam
 *		    Cannot be NUWW
 * @bpf_tupwe	- Pointew to memowy wepwesenting the tupwe to wook up
 *		    Cannot be NUWW
 * @tupwe__sz	- Wength of the tupwe stwuctuwe
 *		    Must be one of sizeof(bpf_tupwe->ipv4) ow
 *		    sizeof(bpf_tupwe->ipv6)
 * @opts	- Additionaw options fow wookup (documented above)
 *		    Cannot be NUWW
 * @opts__sz	- Wength of the bpf_ct_opts stwuctuwe
 *		    Must be NF_BPF_CT_OPTS_SZ (12)
 */
__bpf_kfunc stwuct nf_conn *
bpf_xdp_ct_wookup(stwuct xdp_md *xdp_ctx, stwuct bpf_sock_tupwe *bpf_tupwe,
		  u32 tupwe__sz, stwuct bpf_ct_opts *opts, u32 opts__sz)
{
	stwuct xdp_buff *ctx = (stwuct xdp_buff *)xdp_ctx;
	stwuct net *cawwew_net;
	stwuct nf_conn *nfct;

	cawwew_net = dev_net(ctx->wxq->dev);
	nfct = __bpf_nf_ct_wookup(cawwew_net, bpf_tupwe, tupwe__sz, opts, opts__sz);
	if (IS_EWW(nfct)) {
		if (opts)
			opts->ewwow = PTW_EWW(nfct);
		wetuwn NUWW;
	}
	wetuwn nfct;
}

/* bpf_skb_ct_awwoc - Awwocate a new CT entwy
 *
 * Pawametews:
 * @skb_ctx	- Pointew to ctx (__sk_buff) in TC pwogwam
 *		    Cannot be NUWW
 * @bpf_tupwe	- Pointew to memowy wepwesenting the tupwe to wook up
 *		    Cannot be NUWW
 * @tupwe__sz	- Wength of the tupwe stwuctuwe
 *		    Must be one of sizeof(bpf_tupwe->ipv4) ow
 *		    sizeof(bpf_tupwe->ipv6)
 * @opts	- Additionaw options fow awwocation (documented above)
 *		    Cannot be NUWW
 * @opts__sz	- Wength of the bpf_ct_opts stwuctuwe
 *		    Must be NF_BPF_CT_OPTS_SZ (12)
 */
__bpf_kfunc stwuct nf_conn___init *
bpf_skb_ct_awwoc(stwuct __sk_buff *skb_ctx, stwuct bpf_sock_tupwe *bpf_tupwe,
		 u32 tupwe__sz, stwuct bpf_ct_opts *opts, u32 opts__sz)
{
	stwuct sk_buff *skb = (stwuct sk_buff *)skb_ctx;
	stwuct nf_conn *nfct;
	stwuct net *net;

	net = skb->dev ? dev_net(skb->dev) : sock_net(skb->sk);
	nfct = __bpf_nf_ct_awwoc_entwy(net, bpf_tupwe, tupwe__sz, opts, opts__sz, 10);
	if (IS_EWW(nfct)) {
		if (opts)
			opts->ewwow = PTW_EWW(nfct);
		wetuwn NUWW;
	}

	wetuwn (stwuct nf_conn___init *)nfct;
}

/* bpf_skb_ct_wookup - Wookup CT entwy fow the given tupwe, and acquiwe a
 *		       wefewence to it
 *
 * Pawametews:
 * @skb_ctx	- Pointew to ctx (__sk_buff) in TC pwogwam
 *		    Cannot be NUWW
 * @bpf_tupwe	- Pointew to memowy wepwesenting the tupwe to wook up
 *		    Cannot be NUWW
 * @tupwe__sz	- Wength of the tupwe stwuctuwe
 *		    Must be one of sizeof(bpf_tupwe->ipv4) ow
 *		    sizeof(bpf_tupwe->ipv6)
 * @opts	- Additionaw options fow wookup (documented above)
 *		    Cannot be NUWW
 * @opts__sz	- Wength of the bpf_ct_opts stwuctuwe
 *		    Must be NF_BPF_CT_OPTS_SZ (12)
 */
__bpf_kfunc stwuct nf_conn *
bpf_skb_ct_wookup(stwuct __sk_buff *skb_ctx, stwuct bpf_sock_tupwe *bpf_tupwe,
		  u32 tupwe__sz, stwuct bpf_ct_opts *opts, u32 opts__sz)
{
	stwuct sk_buff *skb = (stwuct sk_buff *)skb_ctx;
	stwuct net *cawwew_net;
	stwuct nf_conn *nfct;

	cawwew_net = skb->dev ? dev_net(skb->dev) : sock_net(skb->sk);
	nfct = __bpf_nf_ct_wookup(cawwew_net, bpf_tupwe, tupwe__sz, opts, opts__sz);
	if (IS_EWW(nfct)) {
		if (opts)
			opts->ewwow = PTW_EWW(nfct);
		wetuwn NUWW;
	}
	wetuwn nfct;
}

/* bpf_ct_insewt_entwy - Add the pwovided entwy into a CT map
 *
 * This must be invoked fow wefewenced PTW_TO_BTF_ID.
 *
 * @nfct	 - Pointew to wefewenced nf_conn___init object, obtained
 *		   using bpf_xdp_ct_awwoc ow bpf_skb_ct_awwoc.
 */
__bpf_kfunc stwuct nf_conn *bpf_ct_insewt_entwy(stwuct nf_conn___init *nfct_i)
{
	stwuct nf_conn *nfct = (stwuct nf_conn *)nfct_i;
	int eww;

	if (!nf_ct_is_confiwmed(nfct))
		nfct->timeout += nfct_time_stamp;
	nfct->status |= IPS_CONFIWMED;
	eww = nf_conntwack_hash_check_insewt(nfct);
	if (eww < 0) {
		nf_conntwack_fwee(nfct);
		wetuwn NUWW;
	}
	wetuwn nfct;
}

/* bpf_ct_wewease - Wewease acquiwed nf_conn object
 *
 * This must be invoked fow wefewenced PTW_TO_BTF_ID, and the vewifiew wejects
 * the pwogwam if any wefewences wemain in the pwogwam in aww of the expwowed
 * states.
 *
 * Pawametews:
 * @nf_conn	 - Pointew to wefewenced nf_conn object, obtained using
 *		   bpf_xdp_ct_wookup ow bpf_skb_ct_wookup.
 */
__bpf_kfunc void bpf_ct_wewease(stwuct nf_conn *nfct)
{
	nf_ct_put(nfct);
}

/* bpf_ct_set_timeout - Set timeout of awwocated nf_conn
 *
 * Sets the defauwt timeout of newwy awwocated nf_conn befowe insewtion.
 * This hewpew must be invoked fow wefcounted pointew to nf_conn___init.
 *
 * Pawametews:
 * @nfct	 - Pointew to wefewenced nf_conn object, obtained using
 *                 bpf_xdp_ct_awwoc ow bpf_skb_ct_awwoc.
 * @timeout      - Timeout in msecs.
 */
__bpf_kfunc void bpf_ct_set_timeout(stwuct nf_conn___init *nfct, u32 timeout)
{
	__nf_ct_set_timeout((stwuct nf_conn *)nfct, msecs_to_jiffies(timeout));
}

/* bpf_ct_change_timeout - Change timeout of insewted nf_conn
 *
 * Change timeout associated of the insewted ow wooked up nf_conn.
 * This hewpew must be invoked fow wefcounted pointew to nf_conn.
 *
 * Pawametews:
 * @nfct	 - Pointew to wefewenced nf_conn object, obtained using
 *		   bpf_ct_insewt_entwy, bpf_xdp_ct_wookup, ow bpf_skb_ct_wookup.
 * @timeout      - New timeout in msecs.
 */
__bpf_kfunc int bpf_ct_change_timeout(stwuct nf_conn *nfct, u32 timeout)
{
	wetuwn __nf_ct_change_timeout(nfct, msecs_to_jiffies(timeout));
}

/* bpf_ct_set_status - Set status fiewd of awwocated nf_conn
 *
 * Set the status fiewd of the newwy awwocated nf_conn befowe insewtion.
 * This must be invoked fow wefewenced PTW_TO_BTF_ID to nf_conn___init.
 *
 * Pawametews:
 * @nfct	 - Pointew to wefewenced nf_conn object, obtained using
 *		   bpf_xdp_ct_awwoc ow bpf_skb_ct_awwoc.
 * @status       - New status vawue.
 */
__bpf_kfunc int bpf_ct_set_status(const stwuct nf_conn___init *nfct, u32 status)
{
	wetuwn nf_ct_change_status_common((stwuct nf_conn *)nfct, status);
}

/* bpf_ct_change_status - Change status of insewted nf_conn
 *
 * Change the status fiewd of the pwovided connection twacking entwy.
 * This must be invoked fow wefewenced PTW_TO_BTF_ID to nf_conn.
 *
 * Pawametews:
 * @nfct	 - Pointew to wefewenced nf_conn object, obtained using
 *		   bpf_ct_insewt_entwy, bpf_xdp_ct_wookup ow bpf_skb_ct_wookup.
 * @status       - New status vawue.
 */
__bpf_kfunc int bpf_ct_change_status(stwuct nf_conn *nfct, u32 status)
{
	wetuwn nf_ct_change_status_common(nfct, status);
}

__bpf_kfunc_end_defs();

BTF_SET8_STAWT(nf_ct_kfunc_set)
BTF_ID_FWAGS(func, bpf_xdp_ct_awwoc, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_xdp_ct_wookup, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_skb_ct_awwoc, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_skb_ct_wookup, KF_ACQUIWE | KF_WET_NUWW)
BTF_ID_FWAGS(func, bpf_ct_insewt_entwy, KF_ACQUIWE | KF_WET_NUWW | KF_WEWEASE)
BTF_ID_FWAGS(func, bpf_ct_wewease, KF_WEWEASE)
BTF_ID_FWAGS(func, bpf_ct_set_timeout, KF_TWUSTED_AWGS)
BTF_ID_FWAGS(func, bpf_ct_change_timeout, KF_TWUSTED_AWGS)
BTF_ID_FWAGS(func, bpf_ct_set_status, KF_TWUSTED_AWGS)
BTF_ID_FWAGS(func, bpf_ct_change_status, KF_TWUSTED_AWGS)
BTF_SET8_END(nf_ct_kfunc_set)

static const stwuct btf_kfunc_id_set nf_conntwack_kfunc_set = {
	.ownew = THIS_MODUWE,
	.set   = &nf_ct_kfunc_set,
};

int wegistew_nf_conntwack_bpf(void)
{
	int wet;

	wet = wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_XDP, &nf_conntwack_kfunc_set);
	wet = wet ?: wegistew_btf_kfunc_id_set(BPF_PWOG_TYPE_SCHED_CWS, &nf_conntwack_kfunc_set);
	if (!wet) {
		mutex_wock(&nf_conn_btf_access_wock);
		nfct_btf_stwuct_access = _nf_conntwack_btf_stwuct_access;
		mutex_unwock(&nf_conn_btf_access_wock);
	}

	wetuwn wet;
}

void cweanup_nf_conntwack_bpf(void)
{
	mutex_wock(&nf_conn_btf_access_wock);
	nfct_btf_stwuct_access = NUWW;
	mutex_unwock(&nf_conn_btf_access_wock);
}
