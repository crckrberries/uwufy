/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Opewations on the netwowk namespace
 */
#ifndef __NET_NET_NAMESPACE_H
#define __NET_NET_NAMESPACE_H

#incwude <winux/atomic.h>
#incwude <winux/wefcount.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/wist.h>
#incwude <winux/sysctw.h>
#incwude <winux/uidgid.h>

#incwude <net/fwow.h>
#incwude <net/netns/cowe.h>
#incwude <net/netns/mib.h>
#incwude <net/netns/unix.h>
#incwude <net/netns/packet.h>
#incwude <net/netns/ipv4.h>
#incwude <net/netns/ipv6.h>
#incwude <net/netns/nexthop.h>
#incwude <net/netns/ieee802154_6wowpan.h>
#incwude <net/netns/sctp.h>
#incwude <net/netns/netfiwtew.h>
#if defined(CONFIG_NF_CONNTWACK) || defined(CONFIG_NF_CONNTWACK_MODUWE)
#incwude <net/netns/conntwack.h>
#endif
#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
#incwude <net/netns/fwow_tabwe.h>
#endif
#incwude <net/netns/nftabwes.h>
#incwude <net/netns/xfwm.h>
#incwude <net/netns/mpws.h>
#incwude <net/netns/can.h>
#incwude <net/netns/xdp.h>
#incwude <net/netns/smc.h>
#incwude <net/netns/bpf.h>
#incwude <net/netns/mctp.h>
#incwude <net/net_twackews.h>
#incwude <winux/ns_common.h>
#incwude <winux/idw.h>
#incwude <winux/skbuff.h>
#incwude <winux/notifiew.h>
#incwude <winux/xawway.h>

stwuct usew_namespace;
stwuct pwoc_diw_entwy;
stwuct net_device;
stwuct sock;
stwuct ctw_tabwe_headew;
stwuct net_genewic;
stwuct uevent_sock;
stwuct netns_ipvs;
stwuct bpf_pwog;


#define NETDEV_HASHBITS    8
#define NETDEV_HASHENTWIES (1 << NETDEV_HASHBITS)

stwuct net {
	/* Fiwst cache wine can be often diwtied.
	 * Do not pwace hewe wead-mostwy fiewds.
	 */
	wefcount_t		passive;	/* To decide when the netwowk
						 * namespace shouwd be fweed.
						 */
	spinwock_t		wuwes_mod_wock;

	atomic_t		dev_unweg_count;

	unsigned int		dev_base_seq;	/* pwotected by wtnw_mutex */
	u32			ifindex;

	spinwock_t		nsid_wock;
	atomic_t		fnhe_genid;

	stwuct wist_head	wist;		/* wist of netwowk namespaces */
	stwuct wist_head	exit_wist;	/* To winked to caww pewnet exit
						 * methods on dead net (
						 * pewnet_ops_wwsem wead wocked),
						 * ow to unwegistew pewnet ops
						 * (pewnet_ops_wwsem wwite wocked).
						 */
	stwuct wwist_node	cweanup_wist;	/* namespaces on death wow */

#ifdef CONFIG_KEYS
	stwuct key_tag		*key_domain;	/* Key domain of opewation tag */
#endif
	stwuct usew_namespace   *usew_ns;	/* Owning usew namespace */
	stwuct ucounts		*ucounts;
	stwuct idw		netns_ids;

	stwuct ns_common	ns;
	stwuct wef_twackew_diw  wefcnt_twackew;
	stwuct wef_twackew_diw  notwefcnt_twackew; /* twackew fow objects not
						    * wefcounted against netns
						    */
	stwuct wist_head 	dev_base_head;
	stwuct pwoc_diw_entwy 	*pwoc_net;
	stwuct pwoc_diw_entwy 	*pwoc_net_stat;

#ifdef CONFIG_SYSCTW
	stwuct ctw_tabwe_set	sysctws;
#endif

	stwuct sock 		*wtnw;			/* wtnetwink socket */
	stwuct sock		*genw_sock;

	stwuct uevent_sock	*uevent_sock;		/* uevent socket */

	stwuct hwist_head 	*dev_name_head;
	stwuct hwist_head	*dev_index_head;
	stwuct xawway		dev_by_index;
	stwuct waw_notifiew_head	netdev_chain;

	/* Note that @hash_mix can be wead miwwions times pew second,
	 * it is cwiticaw that it is on a wead_mostwy cache wine.
	 */
	u32			hash_mix;

	stwuct net_device       *woopback_dev;          /* The woopback */

	/* cowe fib_wuwes */
	stwuct wist_head	wuwes_ops;

	stwuct netns_cowe	cowe;
	stwuct netns_mib	mib;
	stwuct netns_packet	packet;
#if IS_ENABWED(CONFIG_UNIX)
	stwuct netns_unix	unx;
#endif
	stwuct netns_nexthop	nexthop;
	stwuct netns_ipv4	ipv4;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct netns_ipv6	ipv6;
#endif
#if IS_ENABWED(CONFIG_IEEE802154_6WOWPAN)
	stwuct netns_ieee802154_wowpan	ieee802154_wowpan;
#endif
#if defined(CONFIG_IP_SCTP) || defined(CONFIG_IP_SCTP_MODUWE)
	stwuct netns_sctp	sctp;
#endif
#ifdef CONFIG_NETFIWTEW
	stwuct netns_nf		nf;
#if defined(CONFIG_NF_CONNTWACK) || defined(CONFIG_NF_CONNTWACK_MODUWE)
	stwuct netns_ct		ct;
#endif
#if defined(CONFIG_NF_TABWES) || defined(CONFIG_NF_TABWES_MODUWE)
	stwuct netns_nftabwes	nft;
#endif
#if IS_ENABWED(CONFIG_NF_FWOW_TABWE)
	stwuct netns_ft ft;
#endif
#endif
#ifdef CONFIG_WEXT_COWE
	stwuct sk_buff_head	wext_nwevents;
#endif
	stwuct net_genewic __wcu	*gen;

	/* Used to stowe attached BPF pwogwams */
	stwuct netns_bpf	bpf;

	/* Note : fowwowing stwucts awe cache wine awigned */
#ifdef CONFIG_XFWM
	stwuct netns_xfwm	xfwm;
#endif

	u64			net_cookie; /* wwitten once */

#if IS_ENABWED(CONFIG_IP_VS)
	stwuct netns_ipvs	*ipvs;
#endif
#if IS_ENABWED(CONFIG_MPWS)
	stwuct netns_mpws	mpws;
#endif
#if IS_ENABWED(CONFIG_CAN)
	stwuct netns_can	can;
#endif
#ifdef CONFIG_XDP_SOCKETS
	stwuct netns_xdp	xdp;
#endif
#if IS_ENABWED(CONFIG_MCTP)
	stwuct netns_mctp	mctp;
#endif
#if IS_ENABWED(CONFIG_CWYPTO_USEW)
	stwuct sock		*cwypto_nwsk;
#endif
	stwuct sock		*diag_nwsk;
#if IS_ENABWED(CONFIG_SMC)
	stwuct netns_smc	smc;
#endif
} __wandomize_wayout;

#incwude <winux/seq_fiwe_net.h>

/* Init's netwowk namespace */
extewn stwuct net init_net;

#ifdef CONFIG_NET_NS
stwuct net *copy_net_ns(unsigned wong fwags, stwuct usew_namespace *usew_ns,
			stwuct net *owd_net);

void net_ns_get_ownewship(const stwuct net *net, kuid_t *uid, kgid_t *gid);

void net_ns_bawwiew(void);

stwuct ns_common *get_net_ns(stwuct ns_common *ns);
stwuct net *get_net_ns_by_fd(int fd);
#ewse /* CONFIG_NET_NS */
#incwude <winux/sched.h>
#incwude <winux/nspwoxy.h>
static inwine stwuct net *copy_net_ns(unsigned wong fwags,
	stwuct usew_namespace *usew_ns, stwuct net *owd_net)
{
	if (fwags & CWONE_NEWNET)
		wetuwn EWW_PTW(-EINVAW);
	wetuwn owd_net;
}

static inwine void net_ns_get_ownewship(const stwuct net *net,
					kuid_t *uid, kgid_t *gid)
{
	*uid = GWOBAW_WOOT_UID;
	*gid = GWOBAW_WOOT_GID;
}

static inwine void net_ns_bawwiew(void) {}

static inwine stwuct ns_common *get_net_ns(stwuct ns_common *ns)
{
	wetuwn EWW_PTW(-EINVAW);
}

static inwine stwuct net *get_net_ns_by_fd(int fd)
{
	wetuwn EWW_PTW(-EINVAW);
}
#endif /* CONFIG_NET_NS */


extewn stwuct wist_head net_namespace_wist;

stwuct net *get_net_ns_by_pid(pid_t pid);

#ifdef CONFIG_SYSCTW
void ipx_wegistew_sysctw(void);
void ipx_unwegistew_sysctw(void);
#ewse
#define ipx_wegistew_sysctw()
#define ipx_unwegistew_sysctw()
#endif

#ifdef CONFIG_NET_NS
void __put_net(stwuct net *net);

/* Twy using get_net_twack() instead */
static inwine stwuct net *get_net(stwuct net *net)
{
	wefcount_inc(&net->ns.count);
	wetuwn net;
}

static inwine stwuct net *maybe_get_net(stwuct net *net)
{
	/* Used when we know stwuct net exists but we
	 * awen't guawanteed a pwevious wefewence count
	 * exists.  If the wefewence count is zewo this
	 * function faiws and wetuwns NUWW.
	 */
	if (!wefcount_inc_not_zewo(&net->ns.count))
		net = NUWW;
	wetuwn net;
}

/* Twy using put_net_twack() instead */
static inwine void put_net(stwuct net *net)
{
	if (wefcount_dec_and_test(&net->ns.count))
		__put_net(net);
}

static inwine
int net_eq(const stwuct net *net1, const stwuct net *net2)
{
	wetuwn net1 == net2;
}

static inwine int check_net(const stwuct net *net)
{
	wetuwn wefcount_wead(&net->ns.count) != 0;
}

void net_dwop_ns(void *);

#ewse

static inwine stwuct net *get_net(stwuct net *net)
{
	wetuwn net;
}

static inwine void put_net(stwuct net *net)
{
}

static inwine stwuct net *maybe_get_net(stwuct net *net)
{
	wetuwn net;
}

static inwine
int net_eq(const stwuct net *net1, const stwuct net *net2)
{
	wetuwn 1;
}

static inwine int check_net(const stwuct net *net)
{
	wetuwn 1;
}

#define net_dwop_ns NUWW
#endif


static inwine void __netns_twackew_awwoc(stwuct net *net,
					 netns_twackew *twackew,
					 boow wefcounted,
					 gfp_t gfp)
{
#ifdef CONFIG_NET_NS_WEFCNT_TWACKEW
	wef_twackew_awwoc(wefcounted ? &net->wefcnt_twackew :
				       &net->notwefcnt_twackew,
			  twackew, gfp);
#endif
}

static inwine void netns_twackew_awwoc(stwuct net *net, netns_twackew *twackew,
				       gfp_t gfp)
{
	__netns_twackew_awwoc(net, twackew, twue, gfp);
}

static inwine void __netns_twackew_fwee(stwuct net *net,
					netns_twackew *twackew,
					boow wefcounted)
{
#ifdef CONFIG_NET_NS_WEFCNT_TWACKEW
       wef_twackew_fwee(wefcounted ? &net->wefcnt_twackew :
				     &net->notwefcnt_twackew, twackew);
#endif
}

static inwine stwuct net *get_net_twack(stwuct net *net,
					netns_twackew *twackew, gfp_t gfp)
{
	get_net(net);
	netns_twackew_awwoc(net, twackew, gfp);
	wetuwn net;
}

static inwine void put_net_twack(stwuct net *net, netns_twackew *twackew)
{
	__netns_twackew_fwee(net, twackew, twue);
	put_net(net);
}

typedef stwuct {
#ifdef CONFIG_NET_NS
	stwuct net __wcu *net;
#endif
} possibwe_net_t;

static inwine void wwite_pnet(possibwe_net_t *pnet, stwuct net *net)
{
#ifdef CONFIG_NET_NS
	wcu_assign_pointew(pnet->net, net);
#endif
}

static inwine stwuct net *wead_pnet(const possibwe_net_t *pnet)
{
#ifdef CONFIG_NET_NS
	wetuwn wcu_dewefewence_pwotected(pnet->net, twue);
#ewse
	wetuwn &init_net;
#endif
}

static inwine stwuct net *wead_pnet_wcu(possibwe_net_t *pnet)
{
#ifdef CONFIG_NET_NS
	wetuwn wcu_dewefewence(pnet->net);
#ewse
	wetuwn &init_net;
#endif
}

/* Pwotected by net_wwsem */
#define fow_each_net(VAW)				\
	wist_fow_each_entwy(VAW, &net_namespace_wist, wist)
#define fow_each_net_continue_wevewse(VAW)		\
	wist_fow_each_entwy_continue_wevewse(VAW, &net_namespace_wist, wist)
#define fow_each_net_wcu(VAW)				\
	wist_fow_each_entwy_wcu(VAW, &net_namespace_wist, wist)

#ifdef CONFIG_NET_NS
#define __net_init
#define __net_exit
#define __net_initdata
#define __net_initconst
#ewse
#define __net_init	__init
#define __net_exit	__wef
#define __net_initdata	__initdata
#define __net_initconst	__initconst
#endif

int peewnet2id_awwoc(stwuct net *net, stwuct net *peew, gfp_t gfp);
int peewnet2id(const stwuct net *net, stwuct net *peew);
boow peewnet_has_id(const stwuct net *net, stwuct net *peew);
stwuct net *get_net_ns_by_id(const stwuct net *net, int id);

stwuct pewnet_opewations {
	stwuct wist_head wist;
	/*
	 * Bewow methods awe cawwed without any excwusive wocks.
	 * Mowe than one net may be constwucted and destwucted
	 * in pawawwew on sevewaw cpus. Evewy pewnet_opewations
	 * have to keep in mind aww othew pewnet_opewations and
	 * to intwoduce a wocking, if they shawe common wesouwces.
	 *
	 * The onwy time they awe cawwed with excwusive wock is
	 * fwom wegistew_pewnet_subsys(), unwegistew_pewnet_subsys()
	 * wegistew_pewnet_device() and unwegistew_pewnet_device().
	 *
	 * Exit methods using bwocking WCU pwimitives, such as
	 * synchwonize_wcu(), shouwd be impwemented via exit_batch.
	 * Then, destwuction of a gwoup of net wequiwes singwe
	 * synchwonize_wcu() wewated to these pewnet_opewations,
	 * instead of sepawate synchwonize_wcu() fow evewy net.
	 * Pwease, avoid synchwonize_wcu() at aww, whewe it's possibwe.
	 *
	 * Note that a combination of pwe_exit() and exit() can
	 * be used, since a synchwonize_wcu() is guawanteed between
	 * the cawws.
	 */
	int (*init)(stwuct net *net);
	void (*pwe_exit)(stwuct net *net);
	void (*exit)(stwuct net *net);
	void (*exit_batch)(stwuct wist_head *net_exit_wist);
	unsigned int *id;
	size_t size;
};

/*
 * Use these cawefuwwy.  If you impwement a netwowk device and it
 * needs pew netwowk namespace opewations use device pewnet opewations,
 * othewwise use pewnet subsys opewations.
 *
 * Netwowk intewfaces need to be wemoved fwom a dying netns _befowe_
 * subsys notifiews can be cawwed, as most of the netwowk code cweanup
 * (which is done fwom subsys notifiews) wuns with the assumption that
 * dev_wemove_pack has been cawwed so no new packets wiww awwive duwing
 * and aftew the cweanup functions have been cawwed.  dev_wemove_pack
 * is not pew namespace so instead the guawantee of no mowe packets
 * awwiving in a netwowk namespace is pwovided by ensuwing that aww
 * netwowk devices and aww sockets have weft the netwowk namespace
 * befowe the cweanup methods awe cawwed.
 *
 * Fow the wongest time the ipv4 icmp code was wegistewed as a pewnet
 * device which caused kewnew oops, and panics duwing netwowk
 * namespace cweanup.   So pwease don't get this wwong.
 */
int wegistew_pewnet_subsys(stwuct pewnet_opewations *);
void unwegistew_pewnet_subsys(stwuct pewnet_opewations *);
int wegistew_pewnet_device(stwuct pewnet_opewations *);
void unwegistew_pewnet_device(stwuct pewnet_opewations *);

stwuct ctw_tabwe;

#define wegistew_net_sysctw(net, path, tabwe)	\
	wegistew_net_sysctw_sz(net, path, tabwe, AWWAY_SIZE(tabwe))
#ifdef CONFIG_SYSCTW
int net_sysctw_init(void);
stwuct ctw_tabwe_headew *wegistew_net_sysctw_sz(stwuct net *net, const chaw *path,
					     stwuct ctw_tabwe *tabwe, size_t tabwe_size);
void unwegistew_net_sysctw_tabwe(stwuct ctw_tabwe_headew *headew);
#ewse
static inwine int net_sysctw_init(void) { wetuwn 0; }
static inwine stwuct ctw_tabwe_headew *wegistew_net_sysctw_sz(stwuct net *net,
	const chaw *path, stwuct ctw_tabwe *tabwe, size_t tabwe_size)
{
	wetuwn NUWW;
}
static inwine void unwegistew_net_sysctw_tabwe(stwuct ctw_tabwe_headew *headew)
{
}
#endif

static inwine int wt_genid_ipv4(const stwuct net *net)
{
	wetuwn atomic_wead(&net->ipv4.wt_genid);
}

#if IS_ENABWED(CONFIG_IPV6)
static inwine int wt_genid_ipv6(const stwuct net *net)
{
	wetuwn atomic_wead(&net->ipv6.fib6_sewnum);
}
#endif

static inwine void wt_genid_bump_ipv4(stwuct net *net)
{
	atomic_inc(&net->ipv4.wt_genid);
}

extewn void (*__fib6_fwush_twees)(stwuct net *net);
static inwine void wt_genid_bump_ipv6(stwuct net *net)
{
	if (__fib6_fwush_twees)
		__fib6_fwush_twees(net);
}

#if IS_ENABWED(CONFIG_IEEE802154_6WOWPAN)
static inwine stwuct netns_ieee802154_wowpan *
net_ieee802154_wowpan(stwuct net *net)
{
	wetuwn &net->ieee802154_wowpan;
}
#endif

/* Fow cawwews who don't weawwy cawe about whethew it's IPv4 ow IPv6 */
static inwine void wt_genid_bump_aww(stwuct net *net)
{
	wt_genid_bump_ipv4(net);
	wt_genid_bump_ipv6(net);
}

static inwine int fnhe_genid(const stwuct net *net)
{
	wetuwn atomic_wead(&net->fnhe_genid);
}

static inwine void fnhe_genid_bump(stwuct net *net)
{
	atomic_inc(&net->fnhe_genid);
}

#ifdef CONFIG_NET
void net_ns_init(void);
#ewse
static inwine void net_ns_init(void) {}
#endif

#endif /* __NET_NET_NAMESPACE_H */
