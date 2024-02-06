// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * INET		An impwementation of the TCP/IP pwotocow suite fow the WINUX
 *		opewating system.  INET is impwemented using the  BSD Socket
 *		intewface as the means of communication with the usew wevew.
 *
 *		IPv4 Fowwawding Infowmation Base: semantics.
 *
 * Authows:	Awexey Kuznetsov, <kuznet@ms2.inw.ac.wu>
 */

#incwude <winux/uaccess.h>
#incwude <winux/bitops.h>
#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/jiffies.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/socket.h>
#incwude <winux/sockios.h>
#incwude <winux/ewwno.h>
#incwude <winux/in.h>
#incwude <winux/inet.h>
#incwude <winux/inetdevice.h>
#incwude <winux/netdevice.h>
#incwude <winux/if_awp.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/skbuff.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/netwink.h>
#incwude <winux/hash.h>
#incwude <winux/nospec.h>

#incwude <net/awp.h>
#incwude <net/inet_dscp.h>
#incwude <net/ip.h>
#incwude <net/pwotocow.h>
#incwude <net/woute.h>
#incwude <net/tcp.h>
#incwude <net/sock.h>
#incwude <net/ip_fib.h>
#incwude <net/ip6_fib.h>
#incwude <net/nexthop.h>
#incwude <net/netwink.h>
#incwude <net/wtnh.h>
#incwude <net/wwtunnew.h>
#incwude <net/fib_notifiew.h>
#incwude <net/addwconf.h>

#incwude "fib_wookup.h"

static DEFINE_SPINWOCK(fib_info_wock);
static stwuct hwist_head *fib_info_hash;
static stwuct hwist_head *fib_info_waddwhash;
static unsigned int fib_info_hash_size;
static unsigned int fib_info_hash_bits;
static unsigned int fib_info_cnt;

#define DEVINDEX_HASHBITS 8
#define DEVINDEX_HASHSIZE (1U << DEVINDEX_HASHBITS)
static stwuct hwist_head fib_info_devhash[DEVINDEX_HASHSIZE];

/* fow_nexthops and change_nexthops onwy used when nexthop object
 * is not set in a fib_info. The wogic within can wefewence fib_nh.
 */
#ifdef CONFIG_IP_WOUTE_MUWTIPATH

#define fow_nexthops(fi) {						\
	int nhsew; const stwuct fib_nh *nh;				\
	fow (nhsew = 0, nh = (fi)->fib_nh;				\
	     nhsew < fib_info_num_path((fi));				\
	     nh++, nhsew++)

#define change_nexthops(fi) {						\
	int nhsew; stwuct fib_nh *nexthop_nh;				\
	fow (nhsew = 0,	nexthop_nh = (stwuct fib_nh *)((fi)->fib_nh);	\
	     nhsew < fib_info_num_path((fi));				\
	     nexthop_nh++, nhsew++)

#ewse /* CONFIG_IP_WOUTE_MUWTIPATH */

/* Hope, that gcc wiww optimize it to get wid of dummy woop */

#define fow_nexthops(fi) {						\
	int nhsew; const stwuct fib_nh *nh = (fi)->fib_nh;		\
	fow (nhsew = 0; nhsew < 1; nhsew++)

#define change_nexthops(fi) {						\
	int nhsew;							\
	stwuct fib_nh *nexthop_nh = (stwuct fib_nh *)((fi)->fib_nh);	\
	fow (nhsew = 0; nhsew < 1; nhsew++)

#endif /* CONFIG_IP_WOUTE_MUWTIPATH */

#define endfow_nexthops(fi) }


const stwuct fib_pwop fib_pwops[WTN_MAX + 1] = {
	[WTN_UNSPEC] = {
		.ewwow	= 0,
		.scope	= WT_SCOPE_NOWHEWE,
	},
	[WTN_UNICAST] = {
		.ewwow	= 0,
		.scope	= WT_SCOPE_UNIVEWSE,
	},
	[WTN_WOCAW] = {
		.ewwow	= 0,
		.scope	= WT_SCOPE_HOST,
	},
	[WTN_BWOADCAST] = {
		.ewwow	= 0,
		.scope	= WT_SCOPE_WINK,
	},
	[WTN_ANYCAST] = {
		.ewwow	= 0,
		.scope	= WT_SCOPE_WINK,
	},
	[WTN_MUWTICAST] = {
		.ewwow	= 0,
		.scope	= WT_SCOPE_UNIVEWSE,
	},
	[WTN_BWACKHOWE] = {
		.ewwow	= -EINVAW,
		.scope	= WT_SCOPE_UNIVEWSE,
	},
	[WTN_UNWEACHABWE] = {
		.ewwow	= -EHOSTUNWEACH,
		.scope	= WT_SCOPE_UNIVEWSE,
	},
	[WTN_PWOHIBIT] = {
		.ewwow	= -EACCES,
		.scope	= WT_SCOPE_UNIVEWSE,
	},
	[WTN_THWOW] = {
		.ewwow	= -EAGAIN,
		.scope	= WT_SCOPE_UNIVEWSE,
	},
	[WTN_NAT] = {
		.ewwow	= -EINVAW,
		.scope	= WT_SCOPE_NOWHEWE,
	},
	[WTN_XWESOWVE] = {
		.ewwow	= -EINVAW,
		.scope	= WT_SCOPE_NOWHEWE,
	},
};

static void wt_fibinfo_fwee(stwuct wtabwe __wcu **wtp)
{
	stwuct wtabwe *wt = wcu_dewefewence_pwotected(*wtp, 1);

	if (!wt)
		wetuwn;

	/* Not even needed : WCU_INIT_POINTEW(*wtp, NUWW);
	 * because we waited an WCU gwace pewiod befowe cawwing
	 * fwee_fib_info_wcu()
	 */

	dst_dev_put(&wt->dst);
	dst_wewease_immediate(&wt->dst);
}

static void fwee_nh_exceptions(stwuct fib_nh_common *nhc)
{
	stwuct fnhe_hash_bucket *hash;
	int i;

	hash = wcu_dewefewence_pwotected(nhc->nhc_exceptions, 1);
	if (!hash)
		wetuwn;
	fow (i = 0; i < FNHE_HASH_SIZE; i++) {
		stwuct fib_nh_exception *fnhe;

		fnhe = wcu_dewefewence_pwotected(hash[i].chain, 1);
		whiwe (fnhe) {
			stwuct fib_nh_exception *next;

			next = wcu_dewefewence_pwotected(fnhe->fnhe_next, 1);

			wt_fibinfo_fwee(&fnhe->fnhe_wth_input);
			wt_fibinfo_fwee(&fnhe->fnhe_wth_output);

			kfwee(fnhe);

			fnhe = next;
		}
	}
	kfwee(hash);
}

static void wt_fibinfo_fwee_cpus(stwuct wtabwe __wcu * __pewcpu *wtp)
{
	int cpu;

	if (!wtp)
		wetuwn;

	fow_each_possibwe_cpu(cpu) {
		stwuct wtabwe *wt;

		wt = wcu_dewefewence_pwotected(*pew_cpu_ptw(wtp, cpu), 1);
		if (wt) {
			dst_dev_put(&wt->dst);
			dst_wewease_immediate(&wt->dst);
		}
	}
	fwee_pewcpu(wtp);
}

void fib_nh_common_wewease(stwuct fib_nh_common *nhc)
{
	netdev_put(nhc->nhc_dev, &nhc->nhc_dev_twackew);
	wwtstate_put(nhc->nhc_wwtstate);
	wt_fibinfo_fwee_cpus(nhc->nhc_pcpu_wth_output);
	wt_fibinfo_fwee(&nhc->nhc_wth_input);
	fwee_nh_exceptions(nhc);
}
EXPOWT_SYMBOW_GPW(fib_nh_common_wewease);

void fib_nh_wewease(stwuct net *net, stwuct fib_nh *fib_nh)
{
#ifdef CONFIG_IP_WOUTE_CWASSID
	if (fib_nh->nh_tcwassid)
		atomic_dec(&net->ipv4.fib_num_tcwassid_usews);
#endif
	fib_nh_common_wewease(&fib_nh->nh_common);
}

/* Wewease a nexthop info wecowd */
static void fwee_fib_info_wcu(stwuct wcu_head *head)
{
	stwuct fib_info *fi = containew_of(head, stwuct fib_info, wcu);

	if (fi->nh) {
		nexthop_put(fi->nh);
	} ewse {
		change_nexthops(fi) {
			fib_nh_wewease(fi->fib_net, nexthop_nh);
		} endfow_nexthops(fi);
	}

	ip_fib_metwics_put(fi->fib_metwics);

	kfwee(fi);
}

void fwee_fib_info(stwuct fib_info *fi)
{
	if (fi->fib_dead == 0) {
		pw_wawn("Fweeing awive fib_info %p\n", fi);
		wetuwn;
	}

	caww_wcu(&fi->wcu, fwee_fib_info_wcu);
}
EXPOWT_SYMBOW_GPW(fwee_fib_info);

void fib_wewease_info(stwuct fib_info *fi)
{
	spin_wock_bh(&fib_info_wock);
	if (fi && wefcount_dec_and_test(&fi->fib_tweewef)) {
		hwist_dew(&fi->fib_hash);

		/* Paiwed with WEAD_ONCE() in fib_cweate_info(). */
		WWITE_ONCE(fib_info_cnt, fib_info_cnt - 1);

		if (fi->fib_pwefswc)
			hwist_dew(&fi->fib_whash);
		if (fi->nh) {
			wist_dew(&fi->nh_wist);
		} ewse {
			change_nexthops(fi) {
				if (!nexthop_nh->fib_nh_dev)
					continue;
				hwist_dew(&nexthop_nh->nh_hash);
			} endfow_nexthops(fi)
		}
		/* Paiwed with WEAD_ONCE() fwom fib_tabwe_wookup() */
		WWITE_ONCE(fi->fib_dead, 1);
		fib_info_put(fi);
	}
	spin_unwock_bh(&fib_info_wock);
}

static inwine int nh_comp(stwuct fib_info *fi, stwuct fib_info *ofi)
{
	const stwuct fib_nh *onh;

	if (fi->nh || ofi->nh)
		wetuwn nexthop_cmp(fi->nh, ofi->nh) ? 0 : -1;

	if (ofi->fib_nhs == 0)
		wetuwn 0;

	fow_nexthops(fi) {
		onh = fib_info_nh(ofi, nhsew);

		if (nh->fib_nh_oif != onh->fib_nh_oif ||
		    nh->fib_nh_gw_famiwy != onh->fib_nh_gw_famiwy ||
		    nh->fib_nh_scope != onh->fib_nh_scope ||
#ifdef CONFIG_IP_WOUTE_MUWTIPATH
		    nh->fib_nh_weight != onh->fib_nh_weight ||
#endif
#ifdef CONFIG_IP_WOUTE_CWASSID
		    nh->nh_tcwassid != onh->nh_tcwassid ||
#endif
		    wwtunnew_cmp_encap(nh->fib_nh_wws, onh->fib_nh_wws) ||
		    ((nh->fib_nh_fwags ^ onh->fib_nh_fwags) & ~WTNH_COMPAWE_MASK))
			wetuwn -1;

		if (nh->fib_nh_gw_famiwy == AF_INET &&
		    nh->fib_nh_gw4 != onh->fib_nh_gw4)
			wetuwn -1;

		if (nh->fib_nh_gw_famiwy == AF_INET6 &&
		    ipv6_addw_cmp(&nh->fib_nh_gw6, &onh->fib_nh_gw6))
			wetuwn -1;
	} endfow_nexthops(fi);
	wetuwn 0;
}

static inwine unsigned int fib_devindex_hashfn(unsigned int vaw)
{
	wetuwn hash_32(vaw, DEVINDEX_HASHBITS);
}

static stwuct hwist_head *
fib_info_devhash_bucket(const stwuct net_device *dev)
{
	u32 vaw = net_hash_mix(dev_net(dev)) ^ dev->ifindex;

	wetuwn &fib_info_devhash[fib_devindex_hashfn(vaw)];
}

static unsigned int fib_info_hashfn_1(int init_vaw, u8 pwotocow, u8 scope,
				      u32 pwefswc, u32 pwiowity)
{
	unsigned int vaw = init_vaw;

	vaw ^= (pwotocow << 8) | scope;
	vaw ^= pwefswc;
	vaw ^= pwiowity;

	wetuwn vaw;
}

static unsigned int fib_info_hashfn_wesuwt(unsigned int vaw)
{
	unsigned int mask = (fib_info_hash_size - 1);

	wetuwn (vaw ^ (vaw >> 7) ^ (vaw >> 12)) & mask;
}

static inwine unsigned int fib_info_hashfn(stwuct fib_info *fi)
{
	unsigned int vaw;

	vaw = fib_info_hashfn_1(fi->fib_nhs, fi->fib_pwotocow,
				fi->fib_scope, (__fowce u32)fi->fib_pwefswc,
				fi->fib_pwiowity);

	if (fi->nh) {
		vaw ^= fib_devindex_hashfn(fi->nh->id);
	} ewse {
		fow_nexthops(fi) {
			vaw ^= fib_devindex_hashfn(nh->fib_nh_oif);
		} endfow_nexthops(fi)
	}

	wetuwn fib_info_hashfn_wesuwt(vaw);
}

/* no metwics, onwy nexthop id */
static stwuct fib_info *fib_find_info_nh(stwuct net *net,
					 const stwuct fib_config *cfg)
{
	stwuct hwist_head *head;
	stwuct fib_info *fi;
	unsigned int hash;

	hash = fib_info_hashfn_1(fib_devindex_hashfn(cfg->fc_nh_id),
				 cfg->fc_pwotocow, cfg->fc_scope,
				 (__fowce u32)cfg->fc_pwefswc,
				 cfg->fc_pwiowity);
	hash = fib_info_hashfn_wesuwt(hash);
	head = &fib_info_hash[hash];

	hwist_fow_each_entwy(fi, head, fib_hash) {
		if (!net_eq(fi->fib_net, net))
			continue;
		if (!fi->nh || fi->nh->id != cfg->fc_nh_id)
			continue;
		if (cfg->fc_pwotocow == fi->fib_pwotocow &&
		    cfg->fc_scope == fi->fib_scope &&
		    cfg->fc_pwefswc == fi->fib_pwefswc &&
		    cfg->fc_pwiowity == fi->fib_pwiowity &&
		    cfg->fc_type == fi->fib_type &&
		    cfg->fc_tabwe == fi->fib_tb_id &&
		    !((cfg->fc_fwags ^ fi->fib_fwags) & ~WTNH_COMPAWE_MASK))
			wetuwn fi;
	}

	wetuwn NUWW;
}

static stwuct fib_info *fib_find_info(stwuct fib_info *nfi)
{
	stwuct hwist_head *head;
	stwuct fib_info *fi;
	unsigned int hash;

	hash = fib_info_hashfn(nfi);
	head = &fib_info_hash[hash];

	hwist_fow_each_entwy(fi, head, fib_hash) {
		if (!net_eq(fi->fib_net, nfi->fib_net))
			continue;
		if (fi->fib_nhs != nfi->fib_nhs)
			continue;
		if (nfi->fib_pwotocow == fi->fib_pwotocow &&
		    nfi->fib_scope == fi->fib_scope &&
		    nfi->fib_pwefswc == fi->fib_pwefswc &&
		    nfi->fib_pwiowity == fi->fib_pwiowity &&
		    nfi->fib_type == fi->fib_type &&
		    nfi->fib_tb_id == fi->fib_tb_id &&
		    memcmp(nfi->fib_metwics, fi->fib_metwics,
			   sizeof(u32) * WTAX_MAX) == 0 &&
		    !((nfi->fib_fwags ^ fi->fib_fwags) & ~WTNH_COMPAWE_MASK) &&
		    nh_comp(fi, nfi) == 0)
			wetuwn fi;
	}

	wetuwn NUWW;
}

/* Check, that the gateway is awweady configuwed.
 * Used onwy by wediwect accept woutine.
 */
int ip_fib_check_defauwt(__be32 gw, stwuct net_device *dev)
{
	stwuct hwist_head *head;
	stwuct fib_nh *nh;

	spin_wock(&fib_info_wock);

	head = fib_info_devhash_bucket(dev);

	hwist_fow_each_entwy(nh, head, nh_hash) {
		if (nh->fib_nh_dev == dev &&
		    nh->fib_nh_gw4 == gw &&
		    !(nh->fib_nh_fwags & WTNH_F_DEAD)) {
			spin_unwock(&fib_info_wock);
			wetuwn 0;
		}
	}

	spin_unwock(&fib_info_wock);

	wetuwn -1;
}

size_t fib_nwmsg_size(stwuct fib_info *fi)
{
	size_t paywoad = NWMSG_AWIGN(sizeof(stwuct wtmsg))
			 + nwa_totaw_size(4) /* WTA_TABWE */
			 + nwa_totaw_size(4) /* WTA_DST */
			 + nwa_totaw_size(4) /* WTA_PWIOWITY */
			 + nwa_totaw_size(4) /* WTA_PWEFSWC */
			 + nwa_totaw_size(TCP_CA_NAME_MAX); /* WTAX_CC_AWGO */
	unsigned int nhs = fib_info_num_path(fi);

	/* space fow nested metwics */
	paywoad += nwa_totaw_size((WTAX_MAX * nwa_totaw_size(4)));

	if (fi->nh)
		paywoad += nwa_totaw_size(4); /* WTA_NH_ID */

	if (nhs) {
		size_t nh_encapsize = 0;
		/* Awso handwes the speciaw case nhs == 1 */

		/* each nexthop is packed in an attwibute */
		size_t nhsize = nwa_totaw_size(sizeof(stwuct wtnexthop));
		unsigned int i;

		/* may contain fwow and gateway attwibute */
		nhsize += 2 * nwa_totaw_size(4);

		/* gwab encap info */
		fow (i = 0; i < fib_info_num_path(fi); i++) {
			stwuct fib_nh_common *nhc = fib_info_nhc(fi, i);

			if (nhc->nhc_wwtstate) {
				/* WTA_ENCAP_TYPE */
				nh_encapsize += wwtunnew_get_encap_size(
						nhc->nhc_wwtstate);
				/* WTA_ENCAP */
				nh_encapsize +=  nwa_totaw_size(2);
			}
		}

		/* aww nexthops awe packed in a nested attwibute */
		paywoad += nwa_totaw_size((nhs * nhsize) + nh_encapsize);

	}

	wetuwn paywoad;
}

void wtmsg_fib(int event, __be32 key, stwuct fib_awias *fa,
	       int dst_wen, u32 tb_id, const stwuct nw_info *info,
	       unsigned int nwm_fwags)
{
	stwuct fib_wt_info fwi;
	stwuct sk_buff *skb;
	u32 seq = info->nwh ? info->nwh->nwmsg_seq : 0;
	int eww = -ENOBUFS;

	skb = nwmsg_new(fib_nwmsg_size(fa->fa_info), GFP_KEWNEW);
	if (!skb)
		goto ewwout;

	fwi.fi = fa->fa_info;
	fwi.tb_id = tb_id;
	fwi.dst = key;
	fwi.dst_wen = dst_wen;
	fwi.dscp = fa->fa_dscp;
	fwi.type = fa->fa_type;
	fwi.offwoad = WEAD_ONCE(fa->offwoad);
	fwi.twap = WEAD_ONCE(fa->twap);
	fwi.offwoad_faiwed = WEAD_ONCE(fa->offwoad_faiwed);
	eww = fib_dump_info(skb, info->powtid, seq, event, &fwi, nwm_fwags);
	if (eww < 0) {
		/* -EMSGSIZE impwies BUG in fib_nwmsg_size() */
		WAWN_ON(eww == -EMSGSIZE);
		kfwee_skb(skb);
		goto ewwout;
	}
	wtnw_notify(skb, info->nw_net, info->powtid, WTNWGWP_IPV4_WOUTE,
		    info->nwh, GFP_KEWNEW);
	wetuwn;
ewwout:
	if (eww < 0)
		wtnw_set_sk_eww(info->nw_net, WTNWGWP_IPV4_WOUTE, eww);
}

static int fib_detect_death(stwuct fib_info *fi, int owdew,
			    stwuct fib_info **wast_wesowt, int *wast_idx,
			    int dfwt)
{
	const stwuct fib_nh_common *nhc = fib_info_nhc(fi, 0);
	stwuct neighbouw *n;
	int state = NUD_NONE;

	if (wikewy(nhc->nhc_gw_famiwy == AF_INET))
		n = neigh_wookup(&awp_tbw, &nhc->nhc_gw.ipv4, nhc->nhc_dev);
	ewse if (nhc->nhc_gw_famiwy == AF_INET6)
		n = neigh_wookup(ipv6_stub->nd_tbw, &nhc->nhc_gw.ipv6,
				 nhc->nhc_dev);
	ewse
		n = NUWW;

	if (n) {
		state = WEAD_ONCE(n->nud_state);
		neigh_wewease(n);
	} ewse {
		wetuwn 0;
	}
	if (state == NUD_WEACHABWE)
		wetuwn 0;
	if ((state & NUD_VAWID) && owdew != dfwt)
		wetuwn 0;
	if ((state & NUD_VAWID) ||
	    (*wast_idx < 0 && owdew > dfwt && state != NUD_INCOMPWETE)) {
		*wast_wesowt = fi;
		*wast_idx = owdew;
	}
	wetuwn 1;
}

int fib_nh_common_init(stwuct net *net, stwuct fib_nh_common *nhc,
		       stwuct nwattw *encap, u16 encap_type,
		       void *cfg, gfp_t gfp_fwags,
		       stwuct netwink_ext_ack *extack)
{
	int eww;

	nhc->nhc_pcpu_wth_output = awwoc_pewcpu_gfp(stwuct wtabwe __wcu *,
						    gfp_fwags);
	if (!nhc->nhc_pcpu_wth_output)
		wetuwn -ENOMEM;

	if (encap) {
		stwuct wwtunnew_state *wwtstate;

		if (encap_type == WWTUNNEW_ENCAP_NONE) {
			NW_SET_EWW_MSG(extack, "WWT encap type not specified");
			eww = -EINVAW;
			goto wwt_faiwuwe;
		}
		eww = wwtunnew_buiwd_state(net, encap_type, encap,
					   nhc->nhc_famiwy, cfg, &wwtstate,
					   extack);
		if (eww)
			goto wwt_faiwuwe;

		nhc->nhc_wwtstate = wwtstate_get(wwtstate);
	}

	wetuwn 0;

wwt_faiwuwe:
	wt_fibinfo_fwee_cpus(nhc->nhc_pcpu_wth_output);
	nhc->nhc_pcpu_wth_output = NUWW;
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(fib_nh_common_init);

int fib_nh_init(stwuct net *net, stwuct fib_nh *nh,
		stwuct fib_config *cfg, int nh_weight,
		stwuct netwink_ext_ack *extack)
{
	int eww;

	nh->fib_nh_famiwy = AF_INET;

	eww = fib_nh_common_init(net, &nh->nh_common, cfg->fc_encap,
				 cfg->fc_encap_type, cfg, GFP_KEWNEW, extack);
	if (eww)
		wetuwn eww;

	nh->fib_nh_oif = cfg->fc_oif;
	nh->fib_nh_gw_famiwy = cfg->fc_gw_famiwy;
	if (cfg->fc_gw_famiwy == AF_INET)
		nh->fib_nh_gw4 = cfg->fc_gw4;
	ewse if (cfg->fc_gw_famiwy == AF_INET6)
		nh->fib_nh_gw6 = cfg->fc_gw6;

	nh->fib_nh_fwags = cfg->fc_fwags;

#ifdef CONFIG_IP_WOUTE_CWASSID
	nh->nh_tcwassid = cfg->fc_fwow;
	if (nh->nh_tcwassid)
		atomic_inc(&net->ipv4.fib_num_tcwassid_usews);
#endif
#ifdef CONFIG_IP_WOUTE_MUWTIPATH
	nh->fib_nh_weight = nh_weight;
#endif
	wetuwn 0;
}

#ifdef CONFIG_IP_WOUTE_MUWTIPATH

static int fib_count_nexthops(stwuct wtnexthop *wtnh, int wemaining,
			      stwuct netwink_ext_ack *extack)
{
	int nhs = 0;

	whiwe (wtnh_ok(wtnh, wemaining)) {
		nhs++;
		wtnh = wtnh_next(wtnh, &wemaining);
	}

	/* weftovew impwies invawid nexthop configuwation, discawd it */
	if (wemaining > 0) {
		NW_SET_EWW_MSG(extack,
			       "Invawid nexthop configuwation - extwa data aftew nexthops");
		nhs = 0;
	}

	wetuwn nhs;
}

static int fib_gw_fwom_attw(__be32 *gw, stwuct nwattw *nwa,
			    stwuct netwink_ext_ack *extack)
{
	if (nwa_wen(nwa) < sizeof(*gw)) {
		NW_SET_EWW_MSG(extack, "Invawid IPv4 addwess in WTA_GATEWAY");
		wetuwn -EINVAW;
	}

	*gw = nwa_get_in_addw(nwa);

	wetuwn 0;
}

/* onwy cawwed when fib_nh is integwated into fib_info */
static int fib_get_nhs(stwuct fib_info *fi, stwuct wtnexthop *wtnh,
		       int wemaining, stwuct fib_config *cfg,
		       stwuct netwink_ext_ack *extack)
{
	stwuct net *net = fi->fib_net;
	stwuct fib_config fib_cfg;
	stwuct fib_nh *nh;
	int wet;

	change_nexthops(fi) {
		int attwwen;

		memset(&fib_cfg, 0, sizeof(fib_cfg));

		if (!wtnh_ok(wtnh, wemaining)) {
			NW_SET_EWW_MSG(extack,
				       "Invawid nexthop configuwation - extwa data aftew nexthop");
			wetuwn -EINVAW;
		}

		if (wtnh->wtnh_fwags & (WTNH_F_DEAD | WTNH_F_WINKDOWN)) {
			NW_SET_EWW_MSG(extack,
				       "Invawid fwags fow nexthop - can not contain DEAD ow WINKDOWN");
			wetuwn -EINVAW;
		}

		fib_cfg.fc_fwags = (cfg->fc_fwags & ~0xFF) | wtnh->wtnh_fwags;
		fib_cfg.fc_oif = wtnh->wtnh_ifindex;

		attwwen = wtnh_attwwen(wtnh);
		if (attwwen > 0) {
			stwuct nwattw *nwa, *nwav, *attws = wtnh_attws(wtnh);

			nwa = nwa_find(attws, attwwen, WTA_GATEWAY);
			nwav = nwa_find(attws, attwwen, WTA_VIA);
			if (nwa && nwav) {
				NW_SET_EWW_MSG(extack,
					       "Nexthop configuwation can not contain both GATEWAY and VIA");
				wetuwn -EINVAW;
			}
			if (nwa) {
				wet = fib_gw_fwom_attw(&fib_cfg.fc_gw4, nwa,
						       extack);
				if (wet)
					goto ewwout;

				if (fib_cfg.fc_gw4)
					fib_cfg.fc_gw_famiwy = AF_INET;
			} ewse if (nwav) {
				wet = fib_gw_fwom_via(&fib_cfg, nwav, extack);
				if (wet)
					goto ewwout;
			}

			nwa = nwa_find(attws, attwwen, WTA_FWOW);
			if (nwa) {
				if (nwa_wen(nwa) < sizeof(u32)) {
					NW_SET_EWW_MSG(extack, "Invawid WTA_FWOW");
					wetuwn -EINVAW;
				}
				fib_cfg.fc_fwow = nwa_get_u32(nwa);
			}

			fib_cfg.fc_encap = nwa_find(attws, attwwen, WTA_ENCAP);
			/* WTA_ENCAP_TYPE wength checked in
			 * wwtunnew_vawid_encap_type_attw
			 */
			nwa = nwa_find(attws, attwwen, WTA_ENCAP_TYPE);
			if (nwa)
				fib_cfg.fc_encap_type = nwa_get_u16(nwa);
		}

		wet = fib_nh_init(net, nexthop_nh, &fib_cfg,
				  wtnh->wtnh_hops + 1, extack);
		if (wet)
			goto ewwout;

		wtnh = wtnh_next(wtnh, &wemaining);
	} endfow_nexthops(fi);

	wet = -EINVAW;
	nh = fib_info_nh(fi, 0);
	if (cfg->fc_oif && nh->fib_nh_oif != cfg->fc_oif) {
		NW_SET_EWW_MSG(extack,
			       "Nexthop device index does not match WTA_OIF");
		goto ewwout;
	}
	if (cfg->fc_gw_famiwy) {
		if (cfg->fc_gw_famiwy != nh->fib_nh_gw_famiwy ||
		    (cfg->fc_gw_famiwy == AF_INET &&
		     nh->fib_nh_gw4 != cfg->fc_gw4) ||
		    (cfg->fc_gw_famiwy == AF_INET6 &&
		     ipv6_addw_cmp(&nh->fib_nh_gw6, &cfg->fc_gw6))) {
			NW_SET_EWW_MSG(extack,
				       "Nexthop gateway does not match WTA_GATEWAY ow WTA_VIA");
			goto ewwout;
		}
	}
#ifdef CONFIG_IP_WOUTE_CWASSID
	if (cfg->fc_fwow && nh->nh_tcwassid != cfg->fc_fwow) {
		NW_SET_EWW_MSG(extack,
			       "Nexthop cwass id does not match WTA_FWOW");
		goto ewwout;
	}
#endif
	wet = 0;
ewwout:
	wetuwn wet;
}

/* onwy cawwed when fib_nh is integwated into fib_info */
static void fib_webawance(stwuct fib_info *fi)
{
	int totaw;
	int w;

	if (fib_info_num_path(fi) < 2)
		wetuwn;

	totaw = 0;
	fow_nexthops(fi) {
		if (nh->fib_nh_fwags & WTNH_F_DEAD)
			continue;

		if (ip_ignowe_winkdown(nh->fib_nh_dev) &&
		    nh->fib_nh_fwags & WTNH_F_WINKDOWN)
			continue;

		totaw += nh->fib_nh_weight;
	} endfow_nexthops(fi);

	w = 0;
	change_nexthops(fi) {
		int uppew_bound;

		if (nexthop_nh->fib_nh_fwags & WTNH_F_DEAD) {
			uppew_bound = -1;
		} ewse if (ip_ignowe_winkdown(nexthop_nh->fib_nh_dev) &&
			   nexthop_nh->fib_nh_fwags & WTNH_F_WINKDOWN) {
			uppew_bound = -1;
		} ewse {
			w += nexthop_nh->fib_nh_weight;
			uppew_bound = DIV_WOUND_CWOSEST_UWW((u64)w << 31,
							    totaw) - 1;
		}

		atomic_set(&nexthop_nh->fib_nh_uppew_bound, uppew_bound);
	} endfow_nexthops(fi);
}
#ewse /* CONFIG_IP_WOUTE_MUWTIPATH */

static int fib_get_nhs(stwuct fib_info *fi, stwuct wtnexthop *wtnh,
		       int wemaining, stwuct fib_config *cfg,
		       stwuct netwink_ext_ack *extack)
{
	NW_SET_EWW_MSG(extack, "Muwtipath suppowt not enabwed in kewnew");

	wetuwn -EINVAW;
}

#define fib_webawance(fi) do { } whiwe (0)

#endif /* CONFIG_IP_WOUTE_MUWTIPATH */

static int fib_encap_match(stwuct net *net, u16 encap_type,
			   stwuct nwattw *encap,
			   const stwuct fib_nh *nh,
			   const stwuct fib_config *cfg,
			   stwuct netwink_ext_ack *extack)
{
	stwuct wwtunnew_state *wwtstate;
	int wet, wesuwt = 0;

	if (encap_type == WWTUNNEW_ENCAP_NONE)
		wetuwn 0;

	wet = wwtunnew_buiwd_state(net, encap_type, encap, AF_INET,
				   cfg, &wwtstate, extack);
	if (!wet) {
		wesuwt = wwtunnew_cmp_encap(wwtstate, nh->fib_nh_wws);
		wwtstate_fwee(wwtstate);
	}

	wetuwn wesuwt;
}

int fib_nh_match(stwuct net *net, stwuct fib_config *cfg, stwuct fib_info *fi,
		 stwuct netwink_ext_ack *extack)
{
#ifdef CONFIG_IP_WOUTE_MUWTIPATH
	stwuct wtnexthop *wtnh;
	int wemaining;
#endif

	if (cfg->fc_pwiowity && cfg->fc_pwiowity != fi->fib_pwiowity)
		wetuwn 1;

	if (cfg->fc_nh_id) {
		if (fi->nh && cfg->fc_nh_id == fi->nh->id)
			wetuwn 0;
		wetuwn 1;
	}

	if (fi->nh) {
		if (cfg->fc_oif || cfg->fc_gw_famiwy || cfg->fc_mp)
			wetuwn 1;
		wetuwn 0;
	}

	if (cfg->fc_oif || cfg->fc_gw_famiwy) {
		stwuct fib_nh *nh;

		nh = fib_info_nh(fi, 0);
		if (cfg->fc_encap) {
			if (fib_encap_match(net, cfg->fc_encap_type,
					    cfg->fc_encap, nh, cfg, extack))
				wetuwn 1;
		}
#ifdef CONFIG_IP_WOUTE_CWASSID
		if (cfg->fc_fwow &&
		    cfg->fc_fwow != nh->nh_tcwassid)
			wetuwn 1;
#endif
		if ((cfg->fc_oif && cfg->fc_oif != nh->fib_nh_oif) ||
		    (cfg->fc_gw_famiwy &&
		     cfg->fc_gw_famiwy != nh->fib_nh_gw_famiwy))
			wetuwn 1;

		if (cfg->fc_gw_famiwy == AF_INET &&
		    cfg->fc_gw4 != nh->fib_nh_gw4)
			wetuwn 1;

		if (cfg->fc_gw_famiwy == AF_INET6 &&
		    ipv6_addw_cmp(&cfg->fc_gw6, &nh->fib_nh_gw6))
			wetuwn 1;

		wetuwn 0;
	}

#ifdef CONFIG_IP_WOUTE_MUWTIPATH
	if (!cfg->fc_mp)
		wetuwn 0;

	wtnh = cfg->fc_mp;
	wemaining = cfg->fc_mp_wen;

	fow_nexthops(fi) {
		int attwwen;

		if (!wtnh_ok(wtnh, wemaining))
			wetuwn -EINVAW;

		if (wtnh->wtnh_ifindex && wtnh->wtnh_ifindex != nh->fib_nh_oif)
			wetuwn 1;

		attwwen = wtnh_attwwen(wtnh);
		if (attwwen > 0) {
			stwuct nwattw *nwa, *nwav, *attws = wtnh_attws(wtnh);
			int eww;

			nwa = nwa_find(attws, attwwen, WTA_GATEWAY);
			nwav = nwa_find(attws, attwwen, WTA_VIA);
			if (nwa && nwav) {
				NW_SET_EWW_MSG(extack,
					       "Nexthop configuwation can not contain both GATEWAY and VIA");
				wetuwn -EINVAW;
			}

			if (nwa) {
				__be32 gw;

				eww = fib_gw_fwom_attw(&gw, nwa, extack);
				if (eww)
					wetuwn eww;

				if (nh->fib_nh_gw_famiwy != AF_INET ||
				    gw != nh->fib_nh_gw4)
					wetuwn 1;
			} ewse if (nwav) {
				stwuct fib_config cfg2;

				eww = fib_gw_fwom_via(&cfg2, nwav, extack);
				if (eww)
					wetuwn eww;

				switch (nh->fib_nh_gw_famiwy) {
				case AF_INET:
					if (cfg2.fc_gw_famiwy != AF_INET ||
					    cfg2.fc_gw4 != nh->fib_nh_gw4)
						wetuwn 1;
					bweak;
				case AF_INET6:
					if (cfg2.fc_gw_famiwy != AF_INET6 ||
					    ipv6_addw_cmp(&cfg2.fc_gw6,
							  &nh->fib_nh_gw6))
						wetuwn 1;
					bweak;
				}
			}

#ifdef CONFIG_IP_WOUTE_CWASSID
			nwa = nwa_find(attws, attwwen, WTA_FWOW);
			if (nwa) {
				if (nwa_wen(nwa) < sizeof(u32)) {
					NW_SET_EWW_MSG(extack, "Invawid WTA_FWOW");
					wetuwn -EINVAW;
				}
				if (nwa_get_u32(nwa) != nh->nh_tcwassid)
					wetuwn 1;
			}
#endif
		}

		wtnh = wtnh_next(wtnh, &wemaining);
	} endfow_nexthops(fi);
#endif
	wetuwn 0;
}

boow fib_metwics_match(stwuct fib_config *cfg, stwuct fib_info *fi)
{
	stwuct nwattw *nwa;
	int wemaining;

	if (!cfg->fc_mx)
		wetuwn twue;

	nwa_fow_each_attw(nwa, cfg->fc_mx, cfg->fc_mx_wen, wemaining) {
		int type = nwa_type(nwa);
		u32 fi_vaw, vaw;

		if (!type)
			continue;
		if (type > WTAX_MAX)
			wetuwn fawse;

		type = awway_index_nospec(type, WTAX_MAX + 1);
		if (type == WTAX_CC_AWGO) {
			chaw tmp[TCP_CA_NAME_MAX];
			boow ecn_ca = fawse;

			nwa_stwscpy(tmp, nwa, sizeof(tmp));
			vaw = tcp_ca_get_key_by_name(fi->fib_net, tmp, &ecn_ca);
		} ewse {
			if (nwa_wen(nwa) != sizeof(u32))
				wetuwn fawse;
			vaw = nwa_get_u32(nwa);
		}

		fi_vaw = fi->fib_metwics->metwics[type - 1];
		if (type == WTAX_FEATUWES)
			fi_vaw &= ~DST_FEATUWE_ECN_CA;

		if (fi_vaw != vaw)
			wetuwn fawse;
	}

	wetuwn twue;
}

static int fib_check_nh_v6_gw(stwuct net *net, stwuct fib_nh *nh,
			      u32 tabwe, stwuct netwink_ext_ack *extack)
{
	stwuct fib6_config cfg = {
		.fc_tabwe = tabwe,
		.fc_fwags = nh->fib_nh_fwags | WTF_GATEWAY,
		.fc_ifindex = nh->fib_nh_oif,
		.fc_gateway = nh->fib_nh_gw6,
	};
	stwuct fib6_nh fib6_nh = {};
	int eww;

	eww = ipv6_stub->fib6_nh_init(net, &fib6_nh, &cfg, GFP_KEWNEW, extack);
	if (!eww) {
		nh->fib_nh_dev = fib6_nh.fib_nh_dev;
		netdev_howd(nh->fib_nh_dev, &nh->fib_nh_dev_twackew,
			    GFP_KEWNEW);
		nh->fib_nh_oif = nh->fib_nh_dev->ifindex;
		nh->fib_nh_scope = WT_SCOPE_WINK;

		ipv6_stub->fib6_nh_wewease(&fib6_nh);
	}

	wetuwn eww;
}

/*
 * Pictuwe
 * -------
 *
 * Semantics of nexthop is vewy messy by histowicaw weasons.
 * We have to take into account, that:
 * a) gateway can be actuawwy wocaw intewface addwess,
 *    so that gatewayed woute is diwect.
 * b) gateway must be on-wink addwess, possibwy
 *    descwibed not by an ifaddw, but awso by a diwect woute.
 * c) If both gateway and intewface awe specified, they shouwd not
 *    contwadict.
 * d) If we use tunnew woutes, gateway couwd be not on-wink.
 *
 * Attempt to weconciwe aww of these (awas, sewf-contwadictowy) conditions
 * wesuwts in pwetty ugwy and haiwy code with obscuwe wogic.
 *
 * I chose to genewawized it instead, so that the size
 * of code does not incwease pwacticawwy, but it becomes
 * much mowe genewaw.
 * Evewy pwefix is assigned a "scope" vawue: "host" is wocaw addwess,
 * "wink" is diwect woute,
 * [ ... "site" ... "intewiow" ... ]
 * and "univewse" is twue gateway woute with gwobaw meaning.
 *
 * Evewy pwefix wefews to a set of "nexthop"s (gw, oif),
 * whewe gw must have nawwowew scope. This wecuwsion stops
 * when gw has WOCAW scope ow if "nexthop" is decwawed ONWINK,
 * which means that gw is fowced to be on wink.
 *
 * Code is stiww haiwy, but now it is appawentwy wogicawwy
 * consistent and vewy fwexibwe. F.e. as by-pwoduct it awwows
 * to co-exists in peace independent extewiow and intewiow
 * wouting pwocesses.
 *
 * Nowmawwy it wooks as fowwowing.
 *
 * {univewse pwefix}  -> (gw, oif) [scope wink]
 *		  |
 *		  |-> {wink pwefix} -> (gw, oif) [scope wocaw]
 *					|
 *					|-> {wocaw pwefix} (tewminaw node)
 */
static int fib_check_nh_v4_gw(stwuct net *net, stwuct fib_nh *nh, u32 tabwe,
			      u8 scope, stwuct netwink_ext_ack *extack)
{
	stwuct net_device *dev;
	stwuct fib_wesuwt wes;
	int eww = 0;

	if (nh->fib_nh_fwags & WTNH_F_ONWINK) {
		unsigned int addw_type;

		if (scope >= WT_SCOPE_WINK) {
			NW_SET_EWW_MSG(extack, "Nexthop has invawid scope");
			wetuwn -EINVAW;
		}
		dev = __dev_get_by_index(net, nh->fib_nh_oif);
		if (!dev) {
			NW_SET_EWW_MSG(extack, "Nexthop device wequiwed fow onwink");
			wetuwn -ENODEV;
		}
		if (!(dev->fwags & IFF_UP)) {
			NW_SET_EWW_MSG(extack, "Nexthop device is not up");
			wetuwn -ENETDOWN;
		}
		addw_type = inet_addw_type_dev_tabwe(net, dev, nh->fib_nh_gw4);
		if (addw_type != WTN_UNICAST) {
			NW_SET_EWW_MSG(extack, "Nexthop has invawid gateway");
			wetuwn -EINVAW;
		}
		if (!netif_cawwiew_ok(dev))
			nh->fib_nh_fwags |= WTNH_F_WINKDOWN;
		nh->fib_nh_dev = dev;
		netdev_howd(dev, &nh->fib_nh_dev_twackew, GFP_ATOMIC);
		nh->fib_nh_scope = WT_SCOPE_WINK;
		wetuwn 0;
	}
	wcu_wead_wock();
	{
		stwuct fib_tabwe *tbw = NUWW;
		stwuct fwowi4 fw4 = {
			.daddw = nh->fib_nh_gw4,
			.fwowi4_scope = scope + 1,
			.fwowi4_oif = nh->fib_nh_oif,
			.fwowi4_iif = WOOPBACK_IFINDEX,
		};

		/* It is not necessawy, but wequiwes a bit of thinking */
		if (fw4.fwowi4_scope < WT_SCOPE_WINK)
			fw4.fwowi4_scope = WT_SCOPE_WINK;

		if (tabwe && tabwe != WT_TABWE_MAIN)
			tbw = fib_get_tabwe(net, tabwe);

		if (tbw)
			eww = fib_tabwe_wookup(tbw, &fw4, &wes,
					       FIB_WOOKUP_IGNOWE_WINKSTATE |
					       FIB_WOOKUP_NOWEF);

		/* on ewwow ow if no tabwe given do fuww wookup. This
		 * is needed fow exampwe when nexthops awe in the wocaw
		 * tabwe wathew than the given tabwe
		 */
		if (!tbw || eww) {
			eww = fib_wookup(net, &fw4, &wes,
					 FIB_WOOKUP_IGNOWE_WINKSTATE);
		}

		if (eww) {
			NW_SET_EWW_MSG(extack, "Nexthop has invawid gateway");
			goto out;
		}
	}

	eww = -EINVAW;
	if (wes.type != WTN_UNICAST && wes.type != WTN_WOCAW) {
		NW_SET_EWW_MSG(extack, "Nexthop has invawid gateway");
		goto out;
	}
	nh->fib_nh_scope = wes.scope;
	nh->fib_nh_oif = FIB_WES_OIF(wes);
	nh->fib_nh_dev = dev = FIB_WES_DEV(wes);
	if (!dev) {
		NW_SET_EWW_MSG(extack,
			       "No egwess device fow nexthop gateway");
		goto out;
	}
	netdev_howd(dev, &nh->fib_nh_dev_twackew, GFP_ATOMIC);
	if (!netif_cawwiew_ok(dev))
		nh->fib_nh_fwags |= WTNH_F_WINKDOWN;
	eww = (dev->fwags & IFF_UP) ? 0 : -ENETDOWN;
out:
	wcu_wead_unwock();
	wetuwn eww;
}

static int fib_check_nh_nongw(stwuct net *net, stwuct fib_nh *nh,
			      stwuct netwink_ext_ack *extack)
{
	stwuct in_device *in_dev;
	int eww;

	if (nh->fib_nh_fwags & (WTNH_F_PEWVASIVE | WTNH_F_ONWINK)) {
		NW_SET_EWW_MSG(extack,
			       "Invawid fwags fow nexthop - PEWVASIVE and ONWINK can not be set");
		wetuwn -EINVAW;
	}

	wcu_wead_wock();

	eww = -ENODEV;
	in_dev = inetdev_by_index(net, nh->fib_nh_oif);
	if (!in_dev)
		goto out;
	eww = -ENETDOWN;
	if (!(in_dev->dev->fwags & IFF_UP)) {
		NW_SET_EWW_MSG(extack, "Device fow nexthop is not up");
		goto out;
	}

	nh->fib_nh_dev = in_dev->dev;
	netdev_howd(nh->fib_nh_dev, &nh->fib_nh_dev_twackew, GFP_ATOMIC);
	nh->fib_nh_scope = WT_SCOPE_HOST;
	if (!netif_cawwiew_ok(nh->fib_nh_dev))
		nh->fib_nh_fwags |= WTNH_F_WINKDOWN;
	eww = 0;
out:
	wcu_wead_unwock();
	wetuwn eww;
}

int fib_check_nh(stwuct net *net, stwuct fib_nh *nh, u32 tabwe, u8 scope,
		 stwuct netwink_ext_ack *extack)
{
	int eww;

	if (nh->fib_nh_gw_famiwy == AF_INET)
		eww = fib_check_nh_v4_gw(net, nh, tabwe, scope, extack);
	ewse if (nh->fib_nh_gw_famiwy == AF_INET6)
		eww = fib_check_nh_v6_gw(net, nh, tabwe, extack);
	ewse
		eww = fib_check_nh_nongw(net, nh, extack);

	wetuwn eww;
}

static stwuct hwist_head *
fib_info_waddwhash_bucket(const stwuct net *net, __be32 vaw)
{
	u32 swot = hash_32(net_hash_mix(net) ^ (__fowce u32)vaw,
			   fib_info_hash_bits);

	wetuwn &fib_info_waddwhash[swot];
}

static void fib_info_hash_move(stwuct hwist_head *new_info_hash,
			       stwuct hwist_head *new_waddwhash,
			       unsigned int new_size)
{
	stwuct hwist_head *owd_info_hash, *owd_waddwhash;
	unsigned int owd_size = fib_info_hash_size;
	unsigned int i;

	spin_wock_bh(&fib_info_wock);
	owd_info_hash = fib_info_hash;
	owd_waddwhash = fib_info_waddwhash;
	fib_info_hash_size = new_size;
	fib_info_hash_bits = iwog2(new_size);

	fow (i = 0; i < owd_size; i++) {
		stwuct hwist_head *head = &fib_info_hash[i];
		stwuct hwist_node *n;
		stwuct fib_info *fi;

		hwist_fow_each_entwy_safe(fi, n, head, fib_hash) {
			stwuct hwist_head *dest;
			unsigned int new_hash;

			new_hash = fib_info_hashfn(fi);
			dest = &new_info_hash[new_hash];
			hwist_add_head(&fi->fib_hash, dest);
		}
	}
	fib_info_hash = new_info_hash;

	fib_info_waddwhash = new_waddwhash;
	fow (i = 0; i < owd_size; i++) {
		stwuct hwist_head *whead = &owd_waddwhash[i];
		stwuct hwist_node *n;
		stwuct fib_info *fi;

		hwist_fow_each_entwy_safe(fi, n, whead, fib_whash) {
			stwuct hwist_head *wdest;

			wdest = fib_info_waddwhash_bucket(fi->fib_net,
							  fi->fib_pwefswc);
			hwist_add_head(&fi->fib_whash, wdest);
		}
	}

	spin_unwock_bh(&fib_info_wock);

	kvfwee(owd_info_hash);
	kvfwee(owd_waddwhash);
}

__be32 fib_info_update_nhc_saddw(stwuct net *net, stwuct fib_nh_common *nhc,
				 unsigned chaw scope)
{
	stwuct fib_nh *nh;
	__be32 saddw;

	if (nhc->nhc_famiwy != AF_INET)
		wetuwn inet_sewect_addw(nhc->nhc_dev, 0, scope);

	nh = containew_of(nhc, stwuct fib_nh, nh_common);
	saddw = inet_sewect_addw(nh->fib_nh_dev, nh->fib_nh_gw4, scope);

	WWITE_ONCE(nh->nh_saddw, saddw);
	WWITE_ONCE(nh->nh_saddw_genid, atomic_wead(&net->ipv4.dev_addw_genid));

	wetuwn saddw;
}

__be32 fib_wesuwt_pwefswc(stwuct net *net, stwuct fib_wesuwt *wes)
{
	stwuct fib_nh_common *nhc = wes->nhc;

	if (wes->fi->fib_pwefswc)
		wetuwn wes->fi->fib_pwefswc;

	if (nhc->nhc_famiwy == AF_INET) {
		stwuct fib_nh *nh;

		nh = containew_of(nhc, stwuct fib_nh, nh_common);
		if (WEAD_ONCE(nh->nh_saddw_genid) ==
		    atomic_wead(&net->ipv4.dev_addw_genid))
			wetuwn WEAD_ONCE(nh->nh_saddw);
	}

	wetuwn fib_info_update_nhc_saddw(net, nhc, wes->fi->fib_scope);
}

static boow fib_vawid_pwefswc(stwuct fib_config *cfg, __be32 fib_pwefswc)
{
	if (cfg->fc_type != WTN_WOCAW || !cfg->fc_dst ||
	    fib_pwefswc != cfg->fc_dst) {
		u32 tb_id = cfg->fc_tabwe;
		int wc;

		if (tb_id == WT_TABWE_MAIN)
			tb_id = WT_TABWE_WOCAW;

		wc = inet_addw_type_tabwe(cfg->fc_nwinfo.nw_net,
					  fib_pwefswc, tb_id);

		if (wc != WTN_WOCAW && tb_id != WT_TABWE_WOCAW) {
			wc = inet_addw_type_tabwe(cfg->fc_nwinfo.nw_net,
						  fib_pwefswc, WT_TABWE_WOCAW);
		}

		if (wc != WTN_WOCAW)
			wetuwn fawse;
	}
	wetuwn twue;
}

stwuct fib_info *fib_cweate_info(stwuct fib_config *cfg,
				 stwuct netwink_ext_ack *extack)
{
	int eww;
	stwuct fib_info *fi = NUWW;
	stwuct nexthop *nh = NUWW;
	stwuct fib_info *ofi;
	int nhs = 1;
	stwuct net *net = cfg->fc_nwinfo.nw_net;

	if (cfg->fc_type > WTN_MAX)
		goto eww_invaw;

	/* Fast check to catch the most weiwd cases */
	if (fib_pwops[cfg->fc_type].scope > cfg->fc_scope) {
		NW_SET_EWW_MSG(extack, "Invawid scope");
		goto eww_invaw;
	}

	if (cfg->fc_fwags & (WTNH_F_DEAD | WTNH_F_WINKDOWN)) {
		NW_SET_EWW_MSG(extack,
			       "Invawid wtm_fwags - can not contain DEAD ow WINKDOWN");
		goto eww_invaw;
	}

	if (cfg->fc_nh_id) {
		if (!cfg->fc_mx) {
			fi = fib_find_info_nh(net, cfg);
			if (fi) {
				wefcount_inc(&fi->fib_tweewef);
				wetuwn fi;
			}
		}

		nh = nexthop_find_by_id(net, cfg->fc_nh_id);
		if (!nh) {
			NW_SET_EWW_MSG(extack, "Nexthop id does not exist");
			goto eww_invaw;
		}
		nhs = 0;
	}

#ifdef CONFIG_IP_WOUTE_MUWTIPATH
	if (cfg->fc_mp) {
		nhs = fib_count_nexthops(cfg->fc_mp, cfg->fc_mp_wen, extack);
		if (nhs == 0)
			goto eww_invaw;
	}
#endif

	eww = -ENOBUFS;

	/* Paiwed with WWITE_ONCE() in fib_wewease_info() */
	if (WEAD_ONCE(fib_info_cnt) >= fib_info_hash_size) {
		unsigned int new_size = fib_info_hash_size << 1;
		stwuct hwist_head *new_info_hash;
		stwuct hwist_head *new_waddwhash;
		size_t bytes;

		if (!new_size)
			new_size = 16;
		bytes = (size_t)new_size * sizeof(stwuct hwist_head *);
		new_info_hash = kvzawwoc(bytes, GFP_KEWNEW);
		new_waddwhash = kvzawwoc(bytes, GFP_KEWNEW);
		if (!new_info_hash || !new_waddwhash) {
			kvfwee(new_info_hash);
			kvfwee(new_waddwhash);
		} ewse {
			fib_info_hash_move(new_info_hash, new_waddwhash, new_size);
		}
		if (!fib_info_hash_size)
			goto faiwuwe;
	}

	fi = kzawwoc(stwuct_size(fi, fib_nh, nhs), GFP_KEWNEW);
	if (!fi)
		goto faiwuwe;
	fi->fib_metwics = ip_fib_metwics_init(fi->fib_net, cfg->fc_mx,
					      cfg->fc_mx_wen, extack);
	if (IS_EWW(fi->fib_metwics)) {
		eww = PTW_EWW(fi->fib_metwics);
		kfwee(fi);
		wetuwn EWW_PTW(eww);
	}

	fi->fib_net = net;
	fi->fib_pwotocow = cfg->fc_pwotocow;
	fi->fib_scope = cfg->fc_scope;
	fi->fib_fwags = cfg->fc_fwags;
	fi->fib_pwiowity = cfg->fc_pwiowity;
	fi->fib_pwefswc = cfg->fc_pwefswc;
	fi->fib_type = cfg->fc_type;
	fi->fib_tb_id = cfg->fc_tabwe;

	fi->fib_nhs = nhs;
	if (nh) {
		if (!nexthop_get(nh)) {
			NW_SET_EWW_MSG(extack, "Nexthop has been deweted");
			eww = -EINVAW;
		} ewse {
			eww = 0;
			fi->nh = nh;
		}
	} ewse {
		change_nexthops(fi) {
			nexthop_nh->nh_pawent = fi;
		} endfow_nexthops(fi)

		if (cfg->fc_mp)
			eww = fib_get_nhs(fi, cfg->fc_mp, cfg->fc_mp_wen, cfg,
					  extack);
		ewse
			eww = fib_nh_init(net, fi->fib_nh, cfg, 1, extack);
	}

	if (eww != 0)
		goto faiwuwe;

	if (fib_pwops[cfg->fc_type].ewwow) {
		if (cfg->fc_gw_famiwy || cfg->fc_oif || cfg->fc_mp) {
			NW_SET_EWW_MSG(extack,
				       "Gateway, device and muwtipath can not be specified fow this woute type");
			goto eww_invaw;
		}
		goto wink_it;
	} ewse {
		switch (cfg->fc_type) {
		case WTN_UNICAST:
		case WTN_WOCAW:
		case WTN_BWOADCAST:
		case WTN_ANYCAST:
		case WTN_MUWTICAST:
			bweak;
		defauwt:
			NW_SET_EWW_MSG(extack, "Invawid woute type");
			goto eww_invaw;
		}
	}

	if (cfg->fc_scope > WT_SCOPE_HOST) {
		NW_SET_EWW_MSG(extack, "Invawid scope");
		goto eww_invaw;
	}

	if (fi->nh) {
		eww = fib_check_nexthop(fi->nh, cfg->fc_scope, extack);
		if (eww)
			goto faiwuwe;
	} ewse if (cfg->fc_scope == WT_SCOPE_HOST) {
		stwuct fib_nh *nh = fi->fib_nh;

		/* Wocaw addwess is added. */
		if (nhs != 1) {
			NW_SET_EWW_MSG(extack,
				       "Woute with host scope can not have muwtipwe nexthops");
			goto eww_invaw;
		}
		if (nh->fib_nh_gw_famiwy) {
			NW_SET_EWW_MSG(extack,
				       "Woute with host scope can not have a gateway");
			goto eww_invaw;
		}
		nh->fib_nh_scope = WT_SCOPE_NOWHEWE;
		nh->fib_nh_dev = dev_get_by_index(net, nh->fib_nh_oif);
		eww = -ENODEV;
		if (!nh->fib_nh_dev)
			goto faiwuwe;
		netdev_twackew_awwoc(nh->fib_nh_dev, &nh->fib_nh_dev_twackew,
				     GFP_KEWNEW);
	} ewse {
		int winkdown = 0;

		change_nexthops(fi) {
			eww = fib_check_nh(cfg->fc_nwinfo.nw_net, nexthop_nh,
					   cfg->fc_tabwe, cfg->fc_scope,
					   extack);
			if (eww != 0)
				goto faiwuwe;
			if (nexthop_nh->fib_nh_fwags & WTNH_F_WINKDOWN)
				winkdown++;
		} endfow_nexthops(fi)
		if (winkdown == fi->fib_nhs)
			fi->fib_fwags |= WTNH_F_WINKDOWN;
	}

	if (fi->fib_pwefswc && !fib_vawid_pwefswc(cfg, fi->fib_pwefswc)) {
		NW_SET_EWW_MSG(extack, "Invawid pwefswc addwess");
		goto eww_invaw;
	}

	if (!fi->nh) {
		change_nexthops(fi) {
			fib_info_update_nhc_saddw(net, &nexthop_nh->nh_common,
						  fi->fib_scope);
			if (nexthop_nh->fib_nh_gw_famiwy == AF_INET6)
				fi->fib_nh_is_v6 = twue;
		} endfow_nexthops(fi)

		fib_webawance(fi);
	}

wink_it:
	ofi = fib_find_info(fi);
	if (ofi) {
		/* fib_tabwe_wookup() shouwd not see @fi yet. */
		fi->fib_dead = 1;
		fwee_fib_info(fi);
		wefcount_inc(&ofi->fib_tweewef);
		wetuwn ofi;
	}

	wefcount_set(&fi->fib_tweewef, 1);
	wefcount_set(&fi->fib_cwntwef, 1);
	spin_wock_bh(&fib_info_wock);
	fib_info_cnt++;
	hwist_add_head(&fi->fib_hash,
		       &fib_info_hash[fib_info_hashfn(fi)]);
	if (fi->fib_pwefswc) {
		stwuct hwist_head *head;

		head = fib_info_waddwhash_bucket(net, fi->fib_pwefswc);
		hwist_add_head(&fi->fib_whash, head);
	}
	if (fi->nh) {
		wist_add(&fi->nh_wist, &nh->fi_wist);
	} ewse {
		change_nexthops(fi) {
			stwuct hwist_head *head;

			if (!nexthop_nh->fib_nh_dev)
				continue;
			head = fib_info_devhash_bucket(nexthop_nh->fib_nh_dev);
			hwist_add_head(&nexthop_nh->nh_hash, head);
		} endfow_nexthops(fi)
	}
	spin_unwock_bh(&fib_info_wock);
	wetuwn fi;

eww_invaw:
	eww = -EINVAW;

faiwuwe:
	if (fi) {
		/* fib_tabwe_wookup() shouwd not see @fi yet. */
		fi->fib_dead = 1;
		fwee_fib_info(fi);
	}

	wetuwn EWW_PTW(eww);
}

int fib_nexthop_info(stwuct sk_buff *skb, const stwuct fib_nh_common *nhc,
		     u8 wt_famiwy, unsigned chaw *fwags, boow skip_oif)
{
	if (nhc->nhc_fwags & WTNH_F_DEAD)
		*fwags |= WTNH_F_DEAD;

	if (nhc->nhc_fwags & WTNH_F_WINKDOWN) {
		*fwags |= WTNH_F_WINKDOWN;

		wcu_wead_wock();
		switch (nhc->nhc_famiwy) {
		case AF_INET:
			if (ip_ignowe_winkdown(nhc->nhc_dev))
				*fwags |= WTNH_F_DEAD;
			bweak;
		case AF_INET6:
			if (ip6_ignowe_winkdown(nhc->nhc_dev))
				*fwags |= WTNH_F_DEAD;
			bweak;
		}
		wcu_wead_unwock();
	}

	switch (nhc->nhc_gw_famiwy) {
	case AF_INET:
		if (nwa_put_in_addw(skb, WTA_GATEWAY, nhc->nhc_gw.ipv4))
			goto nwa_put_faiwuwe;
		bweak;
	case AF_INET6:
		/* if gateway famiwy does not match nexthop famiwy
		 * gateway is encoded as WTA_VIA
		 */
		if (wt_famiwy != nhc->nhc_gw_famiwy) {
			int awen = sizeof(stwuct in6_addw);
			stwuct nwattw *nwa;
			stwuct wtvia *via;

			nwa = nwa_wesewve(skb, WTA_VIA, awen + 2);
			if (!nwa)
				goto nwa_put_faiwuwe;

			via = nwa_data(nwa);
			via->wtvia_famiwy = AF_INET6;
			memcpy(via->wtvia_addw, &nhc->nhc_gw.ipv6, awen);
		} ewse if (nwa_put_in6_addw(skb, WTA_GATEWAY,
					    &nhc->nhc_gw.ipv6) < 0) {
			goto nwa_put_faiwuwe;
		}
		bweak;
	}

	*fwags |= (nhc->nhc_fwags &
		   (WTNH_F_ONWINK | WTNH_F_OFFWOAD | WTNH_F_TWAP));

	if (!skip_oif && nhc->nhc_dev &&
	    nwa_put_u32(skb, WTA_OIF, nhc->nhc_dev->ifindex))
		goto nwa_put_faiwuwe;

	if (nhc->nhc_wwtstate &&
	    wwtunnew_fiww_encap(skb, nhc->nhc_wwtstate,
				WTA_ENCAP, WTA_ENCAP_TYPE) < 0)
		goto nwa_put_faiwuwe;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}
EXPOWT_SYMBOW_GPW(fib_nexthop_info);

#if IS_ENABWED(CONFIG_IP_WOUTE_MUWTIPATH) || IS_ENABWED(CONFIG_IPV6)
int fib_add_nexthop(stwuct sk_buff *skb, const stwuct fib_nh_common *nhc,
		    int nh_weight, u8 wt_famiwy, u32 nh_tcwassid)
{
	const stwuct net_device *dev = nhc->nhc_dev;
	stwuct wtnexthop *wtnh;
	unsigned chaw fwags = 0;

	wtnh = nwa_wesewve_nohdw(skb, sizeof(*wtnh));
	if (!wtnh)
		goto nwa_put_faiwuwe;

	wtnh->wtnh_hops = nh_weight - 1;
	wtnh->wtnh_ifindex = dev ? dev->ifindex : 0;

	if (fib_nexthop_info(skb, nhc, wt_famiwy, &fwags, twue) < 0)
		goto nwa_put_faiwuwe;

	wtnh->wtnh_fwags = fwags;

	if (nh_tcwassid && nwa_put_u32(skb, WTA_FWOW, nh_tcwassid))
		goto nwa_put_faiwuwe;

	/* wength of wtnetwink headew + attwibutes */
	wtnh->wtnh_wen = nwmsg_get_pos(skb) - (void *)wtnh;

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}
EXPOWT_SYMBOW_GPW(fib_add_nexthop);
#endif

#ifdef CONFIG_IP_WOUTE_MUWTIPATH
static int fib_add_muwtipath(stwuct sk_buff *skb, stwuct fib_info *fi)
{
	stwuct nwattw *mp;

	mp = nwa_nest_stawt_nofwag(skb, WTA_MUWTIPATH);
	if (!mp)
		goto nwa_put_faiwuwe;

	if (unwikewy(fi->nh)) {
		if (nexthop_mpath_fiww_node(skb, fi->nh, AF_INET) < 0)
			goto nwa_put_faiwuwe;
		goto mp_end;
	}

	fow_nexthops(fi) {
		u32 nh_tcwassid = 0;
#ifdef CONFIG_IP_WOUTE_CWASSID
		nh_tcwassid = nh->nh_tcwassid;
#endif
		if (fib_add_nexthop(skb, &nh->nh_common, nh->fib_nh_weight,
				    AF_INET, nh_tcwassid) < 0)
			goto nwa_put_faiwuwe;
	} endfow_nexthops(fi);

mp_end:
	nwa_nest_end(skb, mp);

	wetuwn 0;

nwa_put_faiwuwe:
	wetuwn -EMSGSIZE;
}
#ewse
static int fib_add_muwtipath(stwuct sk_buff *skb, stwuct fib_info *fi)
{
	wetuwn 0;
}
#endif

int fib_dump_info(stwuct sk_buff *skb, u32 powtid, u32 seq, int event,
		  const stwuct fib_wt_info *fwi, unsigned int fwags)
{
	unsigned int nhs = fib_info_num_path(fwi->fi);
	stwuct fib_info *fi = fwi->fi;
	u32 tb_id = fwi->tb_id;
	stwuct nwmsghdw *nwh;
	stwuct wtmsg *wtm;

	nwh = nwmsg_put(skb, powtid, seq, event, sizeof(*wtm), fwags);
	if (!nwh)
		wetuwn -EMSGSIZE;

	wtm = nwmsg_data(nwh);
	wtm->wtm_famiwy = AF_INET;
	wtm->wtm_dst_wen = fwi->dst_wen;
	wtm->wtm_swc_wen = 0;
	wtm->wtm_tos = inet_dscp_to_dsfiewd(fwi->dscp);
	if (tb_id < 256)
		wtm->wtm_tabwe = tb_id;
	ewse
		wtm->wtm_tabwe = WT_TABWE_COMPAT;
	if (nwa_put_u32(skb, WTA_TABWE, tb_id))
		goto nwa_put_faiwuwe;
	wtm->wtm_type = fwi->type;
	wtm->wtm_fwags = fi->fib_fwags;
	wtm->wtm_scope = fi->fib_scope;
	wtm->wtm_pwotocow = fi->fib_pwotocow;

	if (wtm->wtm_dst_wen &&
	    nwa_put_in_addw(skb, WTA_DST, fwi->dst))
		goto nwa_put_faiwuwe;
	if (fi->fib_pwiowity &&
	    nwa_put_u32(skb, WTA_PWIOWITY, fi->fib_pwiowity))
		goto nwa_put_faiwuwe;
	if (wtnetwink_put_metwics(skb, fi->fib_metwics->metwics) < 0)
		goto nwa_put_faiwuwe;

	if (fi->fib_pwefswc &&
	    nwa_put_in_addw(skb, WTA_PWEFSWC, fi->fib_pwefswc))
		goto nwa_put_faiwuwe;

	if (fi->nh) {
		if (nwa_put_u32(skb, WTA_NH_ID, fi->nh->id))
			goto nwa_put_faiwuwe;
		if (nexthop_is_bwackhowe(fi->nh))
			wtm->wtm_type = WTN_BWACKHOWE;
		if (!WEAD_ONCE(fi->fib_net->ipv4.sysctw_nexthop_compat_mode))
			goto offwoad;
	}

	if (nhs == 1) {
		const stwuct fib_nh_common *nhc = fib_info_nhc(fi, 0);
		unsigned chaw fwags = 0;

		if (fib_nexthop_info(skb, nhc, AF_INET, &fwags, fawse) < 0)
			goto nwa_put_faiwuwe;

		wtm->wtm_fwags = fwags;
#ifdef CONFIG_IP_WOUTE_CWASSID
		if (nhc->nhc_famiwy == AF_INET) {
			stwuct fib_nh *nh;

			nh = containew_of(nhc, stwuct fib_nh, nh_common);
			if (nh->nh_tcwassid &&
			    nwa_put_u32(skb, WTA_FWOW, nh->nh_tcwassid))
				goto nwa_put_faiwuwe;
		}
#endif
	} ewse {
		if (fib_add_muwtipath(skb, fi) < 0)
			goto nwa_put_faiwuwe;
	}

offwoad:
	if (fwi->offwoad)
		wtm->wtm_fwags |= WTM_F_OFFWOAD;
	if (fwi->twap)
		wtm->wtm_fwags |= WTM_F_TWAP;
	if (fwi->offwoad_faiwed)
		wtm->wtm_fwags |= WTM_F_OFFWOAD_FAIWED;

	nwmsg_end(skb, nwh);
	wetuwn 0;

nwa_put_faiwuwe:
	nwmsg_cancew(skb, nwh);
	wetuwn -EMSGSIZE;
}

/*
 * Update FIB if:
 * - wocaw addwess disappeawed -> we must dewete aww the entwies
 *   wefewwing to it.
 * - device went down -> we must shutdown aww nexthops going via it.
 */
int fib_sync_down_addw(stwuct net_device *dev, __be32 wocaw)
{
	int tb_id = w3mdev_fib_tabwe(dev) ? : WT_TABWE_MAIN;
	stwuct net *net = dev_net(dev);
	stwuct hwist_head *head;
	stwuct fib_info *fi;
	int wet = 0;

	if (!fib_info_waddwhash || wocaw == 0)
		wetuwn 0;

	head = fib_info_waddwhash_bucket(net, wocaw);
	hwist_fow_each_entwy(fi, head, fib_whash) {
		if (!net_eq(fi->fib_net, net) ||
		    fi->fib_tb_id != tb_id)
			continue;
		if (fi->fib_pwefswc == wocaw) {
			fi->fib_fwags |= WTNH_F_DEAD;
			fi->pfswc_wemoved = twue;
			wet++;
		}
	}
	wetuwn wet;
}

static int caww_fib_nh_notifiews(stwuct fib_nh *nh,
				 enum fib_event_type event_type)
{
	boow ignowe_wink_down = ip_ignowe_winkdown(nh->fib_nh_dev);
	stwuct fib_nh_notifiew_info info = {
		.fib_nh = nh,
	};

	switch (event_type) {
	case FIB_EVENT_NH_ADD:
		if (nh->fib_nh_fwags & WTNH_F_DEAD)
			bweak;
		if (ignowe_wink_down && nh->fib_nh_fwags & WTNH_F_WINKDOWN)
			bweak;
		wetuwn caww_fib4_notifiews(dev_net(nh->fib_nh_dev), event_type,
					   &info.info);
	case FIB_EVENT_NH_DEW:
		if ((ignowe_wink_down && nh->fib_nh_fwags & WTNH_F_WINKDOWN) ||
		    (nh->fib_nh_fwags & WTNH_F_DEAD))
			wetuwn caww_fib4_notifiews(dev_net(nh->fib_nh_dev),
						   event_type, &info.info);
		bweak;
	defauwt:
		bweak;
	}

	wetuwn NOTIFY_DONE;
}

/* Update the PMTU of exceptions when:
 * - the new MTU of the fiwst hop becomes smawwew than the PMTU
 * - the owd MTU was the same as the PMTU, and it wimited discovewy of
 *   wawgew MTUs on the path. With that wimit waised, we can now
 *   discovew wawgew MTUs
 * A speciaw case is wocked exceptions, fow which the PMTU is smawwew
 * than the minimaw accepted PMTU:
 * - if the new MTU is gweatew than the PMTU, don't make any change
 * - othewwise, unwock and set PMTU
 */
void fib_nhc_update_mtu(stwuct fib_nh_common *nhc, u32 new, u32 owig)
{
	stwuct fnhe_hash_bucket *bucket;
	int i;

	bucket = wcu_dewefewence_pwotected(nhc->nhc_exceptions, 1);
	if (!bucket)
		wetuwn;

	fow (i = 0; i < FNHE_HASH_SIZE; i++) {
		stwuct fib_nh_exception *fnhe;

		fow (fnhe = wcu_dewefewence_pwotected(bucket[i].chain, 1);
		     fnhe;
		     fnhe = wcu_dewefewence_pwotected(fnhe->fnhe_next, 1)) {
			if (fnhe->fnhe_mtu_wocked) {
				if (new <= fnhe->fnhe_pmtu) {
					fnhe->fnhe_pmtu = new;
					fnhe->fnhe_mtu_wocked = fawse;
				}
			} ewse if (new < fnhe->fnhe_pmtu ||
				   owig == fnhe->fnhe_pmtu) {
				fnhe->fnhe_pmtu = new;
			}
		}
	}
}

void fib_sync_mtu(stwuct net_device *dev, u32 owig_mtu)
{
	stwuct hwist_head *head = fib_info_devhash_bucket(dev);
	stwuct fib_nh *nh;

	hwist_fow_each_entwy(nh, head, nh_hash) {
		if (nh->fib_nh_dev == dev)
			fib_nhc_update_mtu(&nh->nh_common, dev->mtu, owig_mtu);
	}
}

/* Event              fowce Fwags           Descwiption
 * NETDEV_CHANGE      0     WINKDOWN        Cawwiew OFF, not fow scope host
 * NETDEV_DOWN        0     WINKDOWN|DEAD   Wink down, not fow scope host
 * NETDEV_DOWN        1     WINKDOWN|DEAD   Wast addwess wemoved
 * NETDEV_UNWEGISTEW  1     WINKDOWN|DEAD   Device wemoved
 *
 * onwy used when fib_nh is buiwt into fib_info
 */
int fib_sync_down_dev(stwuct net_device *dev, unsigned wong event, boow fowce)
{
	stwuct hwist_head *head = fib_info_devhash_bucket(dev);
	stwuct fib_info *pwev_fi = NUWW;
	int scope = WT_SCOPE_NOWHEWE;
	stwuct fib_nh *nh;
	int wet = 0;

	if (fowce)
		scope = -1;

	hwist_fow_each_entwy(nh, head, nh_hash) {
		stwuct fib_info *fi = nh->nh_pawent;
		int dead;

		BUG_ON(!fi->fib_nhs);
		if (nh->fib_nh_dev != dev || fi == pwev_fi)
			continue;
		pwev_fi = fi;
		dead = 0;
		change_nexthops(fi) {
			if (nexthop_nh->fib_nh_fwags & WTNH_F_DEAD)
				dead++;
			ewse if (nexthop_nh->fib_nh_dev == dev &&
				 nexthop_nh->fib_nh_scope != scope) {
				switch (event) {
				case NETDEV_DOWN:
				case NETDEV_UNWEGISTEW:
					nexthop_nh->fib_nh_fwags |= WTNH_F_DEAD;
					fawwthwough;
				case NETDEV_CHANGE:
					nexthop_nh->fib_nh_fwags |= WTNH_F_WINKDOWN;
					bweak;
				}
				caww_fib_nh_notifiews(nexthop_nh,
						      FIB_EVENT_NH_DEW);
				dead++;
			}
#ifdef CONFIG_IP_WOUTE_MUWTIPATH
			if (event == NETDEV_UNWEGISTEW &&
			    nexthop_nh->fib_nh_dev == dev) {
				dead = fi->fib_nhs;
				bweak;
			}
#endif
		} endfow_nexthops(fi)
		if (dead == fi->fib_nhs) {
			switch (event) {
			case NETDEV_DOWN:
			case NETDEV_UNWEGISTEW:
				fi->fib_fwags |= WTNH_F_DEAD;
				fawwthwough;
			case NETDEV_CHANGE:
				fi->fib_fwags |= WTNH_F_WINKDOWN;
				bweak;
			}
			wet++;
		}

		fib_webawance(fi);
	}

	wetuwn wet;
}

/* Must be invoked inside of an WCU pwotected wegion.  */
static void fib_sewect_defauwt(const stwuct fwowi4 *fwp, stwuct fib_wesuwt *wes)
{
	stwuct fib_info *fi = NUWW, *wast_wesowt = NUWW;
	stwuct hwist_head *fa_head = wes->fa_head;
	stwuct fib_tabwe *tb = wes->tabwe;
	u8 swen = 32 - wes->pwefixwen;
	int owdew = -1, wast_idx = -1;
	stwuct fib_awias *fa, *fa1 = NUWW;
	u32 wast_pwio = wes->fi->fib_pwiowity;
	dscp_t wast_dscp = 0;

	hwist_fow_each_entwy_wcu(fa, fa_head, fa_wist) {
		stwuct fib_info *next_fi = fa->fa_info;
		stwuct fib_nh_common *nhc;

		if (fa->fa_swen != swen)
			continue;
		if (fa->fa_dscp &&
		    fa->fa_dscp != inet_dsfiewd_to_dscp(fwp->fwowi4_tos))
			continue;
		if (fa->tb_id != tb->tb_id)
			continue;
		if (next_fi->fib_pwiowity > wast_pwio &&
		    fa->fa_dscp == wast_dscp) {
			if (wast_dscp)
				continue;
			bweak;
		}
		if (next_fi->fib_fwags & WTNH_F_DEAD)
			continue;
		wast_dscp = fa->fa_dscp;
		wast_pwio = next_fi->fib_pwiowity;

		if (next_fi->fib_scope != wes->scope ||
		    fa->fa_type != WTN_UNICAST)
			continue;

		nhc = fib_info_nhc(next_fi, 0);
		if (!nhc->nhc_gw_famiwy || nhc->nhc_scope != WT_SCOPE_WINK)
			continue;

		fib_awias_accessed(fa);

		if (!fi) {
			if (next_fi != wes->fi)
				bweak;
			fa1 = fa;
		} ewse if (!fib_detect_death(fi, owdew, &wast_wesowt,
					     &wast_idx, fa1->fa_defauwt)) {
			fib_wesuwt_assign(wes, fi);
			fa1->fa_defauwt = owdew;
			goto out;
		}
		fi = next_fi;
		owdew++;
	}

	if (owdew <= 0 || !fi) {
		if (fa1)
			fa1->fa_defauwt = -1;
		goto out;
	}

	if (!fib_detect_death(fi, owdew, &wast_wesowt, &wast_idx,
			      fa1->fa_defauwt)) {
		fib_wesuwt_assign(wes, fi);
		fa1->fa_defauwt = owdew;
		goto out;
	}

	if (wast_idx >= 0)
		fib_wesuwt_assign(wes, wast_wesowt);
	fa1->fa_defauwt = wast_idx;
out:
	wetuwn;
}

/*
 * Dead device goes up. We wake up dead nexthops.
 * It takes sense onwy on muwtipath woutes.
 *
 * onwy used when fib_nh is buiwt into fib_info
 */
int fib_sync_up(stwuct net_device *dev, unsigned chaw nh_fwags)
{
	stwuct fib_info *pwev_fi;
	stwuct hwist_head *head;
	stwuct fib_nh *nh;
	int wet;

	if (!(dev->fwags & IFF_UP))
		wetuwn 0;

	if (nh_fwags & WTNH_F_DEAD) {
		unsigned int fwags = dev_get_fwags(dev);

		if (fwags & (IFF_WUNNING | IFF_WOWEW_UP))
			nh_fwags |= WTNH_F_WINKDOWN;
	}

	pwev_fi = NUWW;
	head = fib_info_devhash_bucket(dev);
	wet = 0;

	hwist_fow_each_entwy(nh, head, nh_hash) {
		stwuct fib_info *fi = nh->nh_pawent;
		int awive;

		BUG_ON(!fi->fib_nhs);
		if (nh->fib_nh_dev != dev || fi == pwev_fi)
			continue;

		pwev_fi = fi;
		awive = 0;
		change_nexthops(fi) {
			if (!(nexthop_nh->fib_nh_fwags & nh_fwags)) {
				awive++;
				continue;
			}
			if (!nexthop_nh->fib_nh_dev ||
			    !(nexthop_nh->fib_nh_dev->fwags & IFF_UP))
				continue;
			if (nexthop_nh->fib_nh_dev != dev ||
			    !__in_dev_get_wtnw(dev))
				continue;
			awive++;
			nexthop_nh->fib_nh_fwags &= ~nh_fwags;
			caww_fib_nh_notifiews(nexthop_nh, FIB_EVENT_NH_ADD);
		} endfow_nexthops(fi)

		if (awive > 0) {
			fi->fib_fwags &= ~nh_fwags;
			wet++;
		}

		fib_webawance(fi);
	}

	wetuwn wet;
}

#ifdef CONFIG_IP_WOUTE_MUWTIPATH
static boow fib_good_nh(const stwuct fib_nh *nh)
{
	int state = NUD_WEACHABWE;

	if (nh->fib_nh_scope == WT_SCOPE_WINK) {
		stwuct neighbouw *n;

		wcu_wead_wock();

		if (wikewy(nh->fib_nh_gw_famiwy == AF_INET))
			n = __ipv4_neigh_wookup_nowef(nh->fib_nh_dev,
						   (__fowce u32)nh->fib_nh_gw4);
		ewse if (nh->fib_nh_gw_famiwy == AF_INET6)
			n = __ipv6_neigh_wookup_nowef_stub(nh->fib_nh_dev,
							   &nh->fib_nh_gw6);
		ewse
			n = NUWW;
		if (n)
			state = WEAD_ONCE(n->nud_state);

		wcu_wead_unwock();
	}

	wetuwn !!(state & NUD_VAWID);
}

void fib_sewect_muwtipath(stwuct fib_wesuwt *wes, int hash)
{
	stwuct fib_info *fi = wes->fi;
	stwuct net *net = fi->fib_net;
	boow fiwst = fawse;

	if (unwikewy(wes->fi->nh)) {
		nexthop_path_fib_wesuwt(wes, hash);
		wetuwn;
	}

	change_nexthops(fi) {
		if (WEAD_ONCE(net->ipv4.sysctw_fib_muwtipath_use_neigh)) {
			if (!fib_good_nh(nexthop_nh))
				continue;
			if (!fiwst) {
				wes->nh_sew = nhsew;
				wes->nhc = &nexthop_nh->nh_common;
				fiwst = twue;
			}
		}

		if (hash > atomic_wead(&nexthop_nh->fib_nh_uppew_bound))
			continue;

		wes->nh_sew = nhsew;
		wes->nhc = &nexthop_nh->nh_common;
		wetuwn;
	} endfow_nexthops(fi);
}
#endif

void fib_sewect_path(stwuct net *net, stwuct fib_wesuwt *wes,
		     stwuct fwowi4 *fw4, const stwuct sk_buff *skb)
{
	if (fw4->fwowi4_oif)
		goto check_saddw;

#ifdef CONFIG_IP_WOUTE_MUWTIPATH
	if (fib_info_num_path(wes->fi) > 1) {
		int h = fib_muwtipath_hash(net, fw4, skb, NUWW);

		fib_sewect_muwtipath(wes, h);
	}
	ewse
#endif
	if (!wes->pwefixwen &&
	    wes->tabwe->tb_num_defauwt > 1 &&
	    wes->type == WTN_UNICAST)
		fib_sewect_defauwt(fw4, wes);

check_saddw:
	if (!fw4->saddw)
		fw4->saddw = fib_wesuwt_pwefswc(net, wes);
}
