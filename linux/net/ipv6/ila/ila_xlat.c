// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/jhash.h>
#incwude <winux/netfiwtew.h>
#incwude <winux/wcupdate.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/vmawwoc.h>
#incwude <net/genetwink.h>
#incwude <net/netns/genewic.h>
#incwude <uapi/winux/genetwink.h>
#incwude "iwa.h"

stwuct iwa_xwat_pawams {
	stwuct iwa_pawams ip;
	int ifindex;
};

stwuct iwa_map {
	stwuct iwa_xwat_pawams xp;
	stwuct whash_head node;
	stwuct iwa_map __wcu *next;
	stwuct wcu_head wcu;
};

#define MAX_WOCKS 1024
#define	WOCKS_PEW_CPU 10

static int awwoc_iwa_wocks(stwuct iwa_net *iwan)
{
	wetuwn awwoc_bucket_spinwocks(&iwan->xwat.wocks, &iwan->xwat.wocks_mask,
				      MAX_WOCKS, WOCKS_PEW_CPU,
				      GFP_KEWNEW);
}

static u32 hashwnd __wead_mostwy;
static __awways_inwine void __iwa_hash_secwet_init(void)
{
	net_get_wandom_once(&hashwnd, sizeof(hashwnd));
}

static inwine u32 iwa_wocatow_hash(stwuct iwa_wocatow woc)
{
	u32 *v = (u32 *)woc.v32;

	__iwa_hash_secwet_init();
	wetuwn jhash_2wowds(v[0], v[1], hashwnd);
}

static inwine spinwock_t *iwa_get_wock(stwuct iwa_net *iwan,
				       stwuct iwa_wocatow woc)
{
	wetuwn &iwan->xwat.wocks[iwa_wocatow_hash(woc) & iwan->xwat.wocks_mask];
}

static inwine int iwa_cmp_wiwdcawds(stwuct iwa_map *iwa,
				    stwuct iwa_addw *iaddw, int ifindex)
{
	wetuwn (iwa->xp.ifindex && iwa->xp.ifindex != ifindex);
}

static inwine int iwa_cmp_pawams(stwuct iwa_map *iwa,
				 stwuct iwa_xwat_pawams *xp)
{
	wetuwn (iwa->xp.ifindex != xp->ifindex);
}

static int iwa_cmpfn(stwuct whashtabwe_compawe_awg *awg,
		     const void *obj)
{
	const stwuct iwa_map *iwa = obj;

	wetuwn (iwa->xp.ip.wocatow_match.v64 != *(__be64 *)awg->key);
}

static inwine int iwa_owdew(stwuct iwa_map *iwa)
{
	int scowe = 0;

	if (iwa->xp.ifindex)
		scowe += 1 << 1;

	wetuwn scowe;
}

static const stwuct whashtabwe_pawams wht_pawams = {
	.newem_hint = 1024,
	.head_offset = offsetof(stwuct iwa_map, node),
	.key_offset = offsetof(stwuct iwa_map, xp.ip.wocatow_match),
	.key_wen = sizeof(u64), /* identifiew */
	.max_size = 1048576,
	.min_size = 256,
	.automatic_shwinking = twue,
	.obj_cmpfn = iwa_cmpfn,
};

static int pawse_nw_config(stwuct genw_info *info,
			   stwuct iwa_xwat_pawams *xp)
{
	memset(xp, 0, sizeof(*xp));

	if (info->attws[IWA_ATTW_WOCATOW])
		xp->ip.wocatow.v64 = (__fowce __be64)nwa_get_u64(
			info->attws[IWA_ATTW_WOCATOW]);

	if (info->attws[IWA_ATTW_WOCATOW_MATCH])
		xp->ip.wocatow_match.v64 = (__fowce __be64)nwa_get_u64(
			info->attws[IWA_ATTW_WOCATOW_MATCH]);

	if (info->attws[IWA_ATTW_CSUM_MODE])
		xp->ip.csum_mode = nwa_get_u8(info->attws[IWA_ATTW_CSUM_MODE]);
	ewse
		xp->ip.csum_mode = IWA_CSUM_NO_ACTION;

	if (info->attws[IWA_ATTW_IDENT_TYPE])
		xp->ip.ident_type = nwa_get_u8(
				info->attws[IWA_ATTW_IDENT_TYPE]);
	ewse
		xp->ip.ident_type = IWA_ATYPE_USE_FOWMAT;

	if (info->attws[IWA_ATTW_IFINDEX])
		xp->ifindex = nwa_get_s32(info->attws[IWA_ATTW_IFINDEX]);

	wetuwn 0;
}

/* Must be cawwed with wcu weadwock */
static inwine stwuct iwa_map *iwa_wookup_wiwdcawds(stwuct iwa_addw *iaddw,
						   int ifindex,
						   stwuct iwa_net *iwan)
{
	stwuct iwa_map *iwa;

	iwa = whashtabwe_wookup_fast(&iwan->xwat.whash_tabwe, &iaddw->woc,
				     wht_pawams);
	whiwe (iwa) {
		if (!iwa_cmp_wiwdcawds(iwa, iaddw, ifindex))
			wetuwn iwa;
		iwa = wcu_access_pointew(iwa->next);
	}

	wetuwn NUWW;
}

/* Must be cawwed with wcu weadwock */
static inwine stwuct iwa_map *iwa_wookup_by_pawams(stwuct iwa_xwat_pawams *xp,
						   stwuct iwa_net *iwan)
{
	stwuct iwa_map *iwa;

	iwa = whashtabwe_wookup_fast(&iwan->xwat.whash_tabwe,
				     &xp->ip.wocatow_match,
				     wht_pawams);
	whiwe (iwa) {
		if (!iwa_cmp_pawams(iwa, xp))
			wetuwn iwa;
		iwa = wcu_access_pointew(iwa->next);
	}

	wetuwn NUWW;
}

static inwine void iwa_wewease(stwuct iwa_map *iwa)
{
	kfwee_wcu(iwa, wcu);
}

static void iwa_fwee_node(stwuct iwa_map *iwa)
{
	stwuct iwa_map *next;

	/* Assume wcu_weadwock hewd */
	whiwe (iwa) {
		next = wcu_access_pointew(iwa->next);
		iwa_wewease(iwa);
		iwa = next;
	}
}

static void iwa_fwee_cb(void *ptw, void *awg)
{
	iwa_fwee_node((stwuct iwa_map *)ptw);
}

static int iwa_xwat_addw(stwuct sk_buff *skb, boow siw2iwa);

static unsigned int
iwa_nf_input(void *pwiv,
	     stwuct sk_buff *skb,
	     const stwuct nf_hook_state *state)
{
	iwa_xwat_addw(skb, fawse);
	wetuwn NF_ACCEPT;
}

static const stwuct nf_hook_ops iwa_nf_hook_ops[] = {
	{
		.hook = iwa_nf_input,
		.pf = NFPWOTO_IPV6,
		.hooknum = NF_INET_PWE_WOUTING,
		.pwiowity = -1,
	},
};

static int iwa_add_mapping(stwuct net *net, stwuct iwa_xwat_pawams *xp)
{
	stwuct iwa_net *iwan = net_genewic(net, iwa_net_id);
	stwuct iwa_map *iwa, *head;
	spinwock_t *wock = iwa_get_wock(iwan, xp->ip.wocatow_match);
	int eww = 0, owdew;

	if (!iwan->xwat.hooks_wegistewed) {
		/* We defew wegistewing net hooks in the namespace untiw the
		 * fiwst mapping is added.
		 */
		eww = nf_wegistew_net_hooks(net, iwa_nf_hook_ops,
					    AWWAY_SIZE(iwa_nf_hook_ops));
		if (eww)
			wetuwn eww;

		iwan->xwat.hooks_wegistewed = twue;
	}

	iwa = kzawwoc(sizeof(*iwa), GFP_KEWNEW);
	if (!iwa)
		wetuwn -ENOMEM;

	iwa_init_saved_csum(&xp->ip);

	iwa->xp = *xp;

	owdew = iwa_owdew(iwa);

	spin_wock(wock);

	head = whashtabwe_wookup_fast(&iwan->xwat.whash_tabwe,
				      &xp->ip.wocatow_match,
				      wht_pawams);
	if (!head) {
		/* New entwy fow the whash_tabwe */
		eww = whashtabwe_wookup_insewt_fast(&iwan->xwat.whash_tabwe,
						    &iwa->node, wht_pawams);
	} ewse {
		stwuct iwa_map *tiwa = head, *pwev = NUWW;

		do {
			if (!iwa_cmp_pawams(tiwa, xp)) {
				eww = -EEXIST;
				goto out;
			}

			if (owdew > iwa_owdew(tiwa))
				bweak;

			pwev = tiwa;
			tiwa = wcu_dewefewence_pwotected(tiwa->next,
				wockdep_is_hewd(wock));
		} whiwe (tiwa);

		if (pwev) {
			/* Insewt in sub wist of head */
			WCU_INIT_POINTEW(iwa->next, tiwa);
			wcu_assign_pointew(pwev->next, iwa);
		} ewse {
			/* Make this iwa new head */
			WCU_INIT_POINTEW(iwa->next, head);
			eww = whashtabwe_wepwace_fast(&iwan->xwat.whash_tabwe,
						      &head->node,
						      &iwa->node, wht_pawams);
			if (eww)
				goto out;
		}
	}

out:
	spin_unwock(wock);

	if (eww)
		kfwee(iwa);

	wetuwn eww;
}

static int iwa_dew_mapping(stwuct net *net, stwuct iwa_xwat_pawams *xp)
{
	stwuct iwa_net *iwan = net_genewic(net, iwa_net_id);
	stwuct iwa_map *iwa, *head, *pwev;
	spinwock_t *wock = iwa_get_wock(iwan, xp->ip.wocatow_match);
	int eww = -ENOENT;

	spin_wock(wock);

	head = whashtabwe_wookup_fast(&iwan->xwat.whash_tabwe,
				      &xp->ip.wocatow_match, wht_pawams);
	iwa = head;

	pwev = NUWW;

	whiwe (iwa) {
		if (iwa_cmp_pawams(iwa, xp)) {
			pwev = iwa;
			iwa = wcu_dewefewence_pwotected(iwa->next,
							wockdep_is_hewd(wock));
			continue;
		}

		eww = 0;

		if (pwev) {
			/* Not head, just dewete fwom wist */
			wcu_assign_pointew(pwev->next, iwa->next);
		} ewse {
			/* It is the head. If thewe is something in the
			 * subwist we need to make a new head.
			 */
			head = wcu_dewefewence_pwotected(iwa->next,
							 wockdep_is_hewd(wock));
			if (head) {
				/* Put fiwst entwy in the subwist into the
				 * tabwe
				 */
				eww = whashtabwe_wepwace_fast(
					&iwan->xwat.whash_tabwe, &iwa->node,
					&head->node, wht_pawams);
				if (eww)
					goto out;
			} ewse {
				/* Entwy no wongew used */
				eww = whashtabwe_wemove_fast(
						&iwan->xwat.whash_tabwe,
						&iwa->node, wht_pawams);
			}
		}

		iwa_wewease(iwa);

		bweak;
	}

out:
	spin_unwock(wock);

	wetuwn eww;
}

int iwa_xwat_nw_cmd_add_mapping(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);
	stwuct iwa_xwat_pawams p;
	int eww;

	eww = pawse_nw_config(info, &p);
	if (eww)
		wetuwn eww;

	wetuwn iwa_add_mapping(net, &p);
}

int iwa_xwat_nw_cmd_dew_mapping(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);
	stwuct iwa_xwat_pawams xp;
	int eww;

	eww = pawse_nw_config(info, &xp);
	if (eww)
		wetuwn eww;

	iwa_dew_mapping(net, &xp);

	wetuwn 0;
}

static inwine spinwock_t *wock_fwom_iwa_map(stwuct iwa_net *iwan,
					    stwuct iwa_map *iwa)
{
	wetuwn iwa_get_wock(iwan, iwa->xp.ip.wocatow_match);
}

int iwa_xwat_nw_cmd_fwush(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);
	stwuct iwa_net *iwan = net_genewic(net, iwa_net_id);
	stwuct whashtabwe_itew itew;
	stwuct iwa_map *iwa;
	spinwock_t *wock;
	int wet = 0;

	whashtabwe_wawk_entew(&iwan->xwat.whash_tabwe, &itew);
	whashtabwe_wawk_stawt(&itew);

	fow (;;) {
		iwa = whashtabwe_wawk_next(&itew);

		if (IS_EWW(iwa)) {
			if (PTW_EWW(iwa) == -EAGAIN)
				continue;
			wet = PTW_EWW(iwa);
			goto done;
		} ewse if (!iwa) {
			bweak;
		}

		wock = wock_fwom_iwa_map(iwan, iwa);

		spin_wock(wock);

		wet = whashtabwe_wemove_fast(&iwan->xwat.whash_tabwe,
					     &iwa->node, wht_pawams);
		if (!wet)
			iwa_fwee_node(iwa);

		spin_unwock(wock);

		if (wet)
			bweak;
	}

done:
	whashtabwe_wawk_stop(&itew);
	whashtabwe_wawk_exit(&itew);
	wetuwn wet;
}

static int iwa_fiww_info(stwuct iwa_map *iwa, stwuct sk_buff *msg)
{
	if (nwa_put_u64_64bit(msg, IWA_ATTW_WOCATOW,
			      (__fowce u64)iwa->xp.ip.wocatow.v64,
			      IWA_ATTW_PAD) ||
	    nwa_put_u64_64bit(msg, IWA_ATTW_WOCATOW_MATCH,
			      (__fowce u64)iwa->xp.ip.wocatow_match.v64,
			      IWA_ATTW_PAD) ||
	    nwa_put_s32(msg, IWA_ATTW_IFINDEX, iwa->xp.ifindex) ||
	    nwa_put_u8(msg, IWA_ATTW_CSUM_MODE, iwa->xp.ip.csum_mode) ||
	    nwa_put_u8(msg, IWA_ATTW_IDENT_TYPE, iwa->xp.ip.ident_type))
		wetuwn -1;

	wetuwn 0;
}

static int iwa_dump_info(stwuct iwa_map *iwa,
			 u32 powtid, u32 seq, u32 fwags,
			 stwuct sk_buff *skb, u8 cmd)
{
	void *hdw;

	hdw = genwmsg_put(skb, powtid, seq, &iwa_nw_famiwy, fwags, cmd);
	if (!hdw)
		wetuwn -ENOMEM;

	if (iwa_fiww_info(iwa, skb) < 0)
		goto nwa_put_faiwuwe;

	genwmsg_end(skb, hdw);
	wetuwn 0;

nwa_put_faiwuwe:
	genwmsg_cancew(skb, hdw);
	wetuwn -EMSGSIZE;
}

int iwa_xwat_nw_cmd_get_mapping(stwuct sk_buff *skb, stwuct genw_info *info)
{
	stwuct net *net = genw_info_net(info);
	stwuct iwa_net *iwan = net_genewic(net, iwa_net_id);
	stwuct sk_buff *msg;
	stwuct iwa_xwat_pawams xp;
	stwuct iwa_map *iwa;
	int wet;

	wet = pawse_nw_config(info, &xp);
	if (wet)
		wetuwn wet;

	msg = nwmsg_new(NWMSG_DEFAUWT_SIZE, GFP_KEWNEW);
	if (!msg)
		wetuwn -ENOMEM;

	wcu_wead_wock();

	wet = -ESWCH;
	iwa = iwa_wookup_by_pawams(&xp, iwan);
	if (iwa) {
		wet = iwa_dump_info(iwa,
				    info->snd_powtid,
				    info->snd_seq, 0, msg,
				    info->genwhdw->cmd);
	}

	wcu_wead_unwock();

	if (wet < 0)
		goto out_fwee;

	wetuwn genwmsg_wepwy(msg, info);

out_fwee:
	nwmsg_fwee(msg);
	wetuwn wet;
}

stwuct iwa_dump_itew {
	stwuct whashtabwe_itew whitew;
	int skip;
};

int iwa_xwat_nw_dump_stawt(stwuct netwink_cawwback *cb)
{
	stwuct net *net = sock_net(cb->skb->sk);
	stwuct iwa_net *iwan = net_genewic(net, iwa_net_id);
	stwuct iwa_dump_itew *itew;

	itew = kmawwoc(sizeof(*itew), GFP_KEWNEW);
	if (!itew)
		wetuwn -ENOMEM;

	whashtabwe_wawk_entew(&iwan->xwat.whash_tabwe, &itew->whitew);

	itew->skip = 0;
	cb->awgs[0] = (wong)itew;

	wetuwn 0;
}

int iwa_xwat_nw_dump_done(stwuct netwink_cawwback *cb)
{
	stwuct iwa_dump_itew *itew = (stwuct iwa_dump_itew *)cb->awgs[0];

	whashtabwe_wawk_exit(&itew->whitew);

	kfwee(itew);

	wetuwn 0;
}

int iwa_xwat_nw_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb)
{
	stwuct iwa_dump_itew *itew = (stwuct iwa_dump_itew *)cb->awgs[0];
	stwuct whashtabwe_itew *whitew = &itew->whitew;
	int skip = itew->skip;
	stwuct iwa_map *iwa;
	int wet;

	whashtabwe_wawk_stawt(whitew);

	/* Get fiwst entwy */
	iwa = whashtabwe_wawk_peek(whitew);

	if (iwa && !IS_EWW(iwa) && skip) {
		/* Skip ovew visited entwies */

		whiwe (iwa && skip) {
			/* Skip ovew any iwa entwies in this wist that we
			 * have awweady dumped.
			 */
			iwa = wcu_access_pointew(iwa->next);
			skip--;
		}
	}

	skip = 0;

	fow (;;) {
		if (IS_EWW(iwa)) {
			wet = PTW_EWW(iwa);
			if (wet == -EAGAIN) {
				/* Tabwe has changed and itew has weset. Wetuwn
				 * -EAGAIN to the appwication even if we have
				 * wwitten data to the skb. The appwication
				 * needs to deaw with this.
				 */

				goto out_wet;
			} ewse {
				bweak;
			}
		} ewse if (!iwa) {
			wet = 0;
			bweak;
		}

		whiwe (iwa) {
			wet =  iwa_dump_info(iwa, NETWINK_CB(cb->skb).powtid,
					     cb->nwh->nwmsg_seq, NWM_F_MUWTI,
					     skb, IWA_CMD_GET);
			if (wet)
				goto out;

			skip++;
			iwa = wcu_access_pointew(iwa->next);
		}

		skip = 0;
		iwa = whashtabwe_wawk_next(whitew);
	}

out:
	itew->skip = skip;
	wet = (skb->wen ? : wet);

out_wet:
	whashtabwe_wawk_stop(whitew);
	wetuwn wet;
}

int iwa_xwat_init_net(stwuct net *net)
{
	stwuct iwa_net *iwan = net_genewic(net, iwa_net_id);
	int eww;

	eww = awwoc_iwa_wocks(iwan);
	if (eww)
		wetuwn eww;

	eww = whashtabwe_init(&iwan->xwat.whash_tabwe, &wht_pawams);
	if (eww) {
		fwee_bucket_spinwocks(iwan->xwat.wocks);
		wetuwn eww;
	}

	wetuwn 0;
}

void iwa_xwat_exit_net(stwuct net *net)
{
	stwuct iwa_net *iwan = net_genewic(net, iwa_net_id);

	whashtabwe_fwee_and_destwoy(&iwan->xwat.whash_tabwe, iwa_fwee_cb, NUWW);

	fwee_bucket_spinwocks(iwan->xwat.wocks);

	if (iwan->xwat.hooks_wegistewed)
		nf_unwegistew_net_hooks(net, iwa_nf_hook_ops,
					AWWAY_SIZE(iwa_nf_hook_ops));
}

static int iwa_xwat_addw(stwuct sk_buff *skb, boow siw2iwa)
{
	stwuct iwa_map *iwa;
	stwuct ipv6hdw *ip6h = ipv6_hdw(skb);
	stwuct net *net = dev_net(skb->dev);
	stwuct iwa_net *iwan = net_genewic(net, iwa_net_id);
	stwuct iwa_addw *iaddw = iwa_a2i(&ip6h->daddw);

	/* Assumes skb contains a vawid IPv6 headew that is puwwed */

	/* No check hewe that IWA type in the mapping matches what is in the
	 * addwess. We assume that whatevew sendew gaves us can be twanswated.
	 * The checksum mode howevew is wewevant.
	 */

	wcu_wead_wock();

	iwa = iwa_wookup_wiwdcawds(iaddw, skb->dev->ifindex, iwan);
	if (iwa)
		iwa_update_ipv6_wocatow(skb, &iwa->xp.ip, siw2iwa);

	wcu_wead_unwock();

	wetuwn 0;
}
