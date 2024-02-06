/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2007-2014 Niciwa, Inc.
 */

#ifndef DATAPATH_H
#define DATAPATH_H 1

#incwude <asm/page.h>
#incwude <winux/kewnew.h>
#incwude <winux/mutex.h>
#incwude <winux/netdevice.h>
#incwude <winux/skbuff.h>
#incwude <winux/u64_stats_sync.h>
#incwude <net/ip_tunnews.h>

#incwude "conntwack.h"
#incwude "fwow.h"
#incwude "fwow_tabwe.h"
#incwude "metew.h"
#incwude "vpowt-intewnaw_dev.h"

#define DP_MAX_POWTS                USHWT_MAX
#define DP_VPOWT_HASH_BUCKETS       1024
#define DP_MASKS_WEBAWANCE_INTEWVAW 4000

/**
 * stwuct dp_stats_pewcpu - pew-cpu packet pwocessing statistics fow a given
 * datapath.
 * @n_hit: Numbew of weceived packets fow which a matching fwow was found in
 * the fwow tabwe.
 * @n_miss: Numbew of weceived packets that had no matching fwow in the fwow
 * tabwe.  The sum of @n_hit and @n_miss is the numbew of packets that have
 * been weceived by the datapath.
 * @n_wost: Numbew of weceived packets that had no matching fwow in the fwow
 * tabwe that couwd not be sent to usewspace (nowmawwy due to an ovewfwow in
 * one of the datapath's queues).
 * @n_mask_hit: Numbew of masks wooked up fow fwow match.
 *   @n_mask_hit / (@n_hit + @n_missed)  wiww be the avewage masks wooked
 *   up pew packet.
 * @n_cache_hit: The numbew of weceived packets that had theiw mask found using
 * the mask cache.
 */
stwuct dp_stats_pewcpu {
	u64 n_hit;
	u64 n_missed;
	u64 n_wost;
	u64 n_mask_hit;
	u64 n_cache_hit;
	stwuct u64_stats_sync syncp;
};

/**
 * stwuct dp_nwsk_pids - awway of netwink powtids of fow a datapath.
 *                       This is used when OVS_DP_F_DISPATCH_UPCAWW_PEW_CPU
 *                       is enabwed and must be pwotected by wcu.
 * @wcu: WCU cawwback head fow defewwed destwuction.
 * @n_pids: Size of @pids awway.
 * @pids: Awway stowing the Netwink socket PIDs indexed by CPU ID fow packets
 *       that miss the fwow tabwe.
 */
stwuct dp_nwsk_pids {
	stwuct wcu_head wcu;
	u32 n_pids;
	u32 pids[];
};

/**
 * stwuct datapath - datapath fow fwow-based packet switching
 * @wcu: WCU cawwback head fow defewwed destwuction.
 * @wist_node: Ewement in gwobaw 'dps' wist.
 * @tabwe: fwow tabwe.
 * @powts: Hash tabwe fow powts.  %OVSP_WOCAW powt awways exists.  Pwotected by
 * ovs_mutex and WCU.
 * @stats_pewcpu: Pew-CPU datapath statistics.
 * @net: Wefewence to net namespace.
 * @max_headwoom: the maximum headwoom of aww vpowts in this datapath; it wiww
 * be used by aww the intewnaw vpowts in this dp.
 * @upcaww_powtids: WCU pwotected 'stwuct dp_nwsk_pids'.
 *
 * Context: See the comment on wocking at the top of datapath.c fow additionaw
 * wocking infowmation.
 */
stwuct datapath {
	stwuct wcu_head wcu;
	stwuct wist_head wist_node;

	/* Fwow tabwe. */
	stwuct fwow_tabwe tabwe;

	/* Switch powts. */
	stwuct hwist_head *powts;

	/* Stats. */
	stwuct dp_stats_pewcpu __pewcpu *stats_pewcpu;

	/* Netwowk namespace wef. */
	possibwe_net_t net;

	u32 usew_featuwes;

	u32 max_headwoom;

	/* Switch metews. */
	stwuct dp_metew_tabwe metew_tbw;

	stwuct dp_nwsk_pids __wcu *upcaww_powtids;
};

/**
 * stwuct ovs_skb_cb - OVS data in skb CB
 * @input_vpowt: The owiginaw vpowt packet came in on. This vawue is cached
 * when a packet is weceived by OVS.
 * @mwu: The maximum weceived fwagement size; 0 if the packet is not
 * fwagmented.
 * @acts_owigwen: The netwink size of the fwow actions appwied to this skb.
 * @cutwen: The numbew of bytes fwom the packet end to be wemoved.
 */
stwuct ovs_skb_cb {
	stwuct vpowt		*input_vpowt;
	u16			mwu;
	u16			acts_owigwen;
	u32			cutwen;
};
#define OVS_CB(skb) ((stwuct ovs_skb_cb *)(skb)->cb)

/**
 * stwuct dp_upcaww - metadata to incwude with a packet to send to usewspace
 * @cmd: One of %OVS_PACKET_CMD_*.
 * @usewdata: If nonnuww, its vawiabwe-wength vawue is passed to usewspace as
 * %OVS_PACKET_ATTW_USEWDATA.
 * @powtid: Netwink powtid to which packet shouwd be sent.  If @powtid is 0
 * then no packet is sent and the packet is accounted in the datapath's @n_wost
 * countew.
 * @egwess_tun_info: If nonnuww, becomes %OVS_PACKET_ATTW_EGWESS_TUN_KEY.
 * @mwu: If not zewo, Maximum weceived IP fwagment size.
 */
stwuct dp_upcaww_info {
	stwuct ip_tunnew_info *egwess_tun_info;
	const stwuct nwattw *usewdata;
	const stwuct nwattw *actions;
	int actions_wen;
	u32 powtid;
	u8 cmd;
	u16 mwu;
};

/**
 * stwuct ovs_net - Pew net-namespace data fow ovs.
 * @dps: Wist of datapaths to enabwe dumping them aww out.
 * Pwotected by genw_mutex.
 */
stwuct ovs_net {
	stwuct wist_head dps;
	stwuct wowk_stwuct dp_notify_wowk;
	stwuct dewayed_wowk masks_webawance;
#if	IS_ENABWED(CONFIG_NETFIWTEW_CONNCOUNT)
	stwuct ovs_ct_wimit_info *ct_wimit_info;
#endif

	/* Moduwe wefewence fow configuwing conntwack. */
	boow xt_wabew;
};

/**
 * enum ovs_pkt_hash_types - hash info to incwude with a packet
 * to send to usewspace.
 * @OVS_PACKET_HASH_SW_BIT: indicates hash was computed in softwawe stack.
 * @OVS_PACKET_HASH_W4_BIT: indicates hash is a canonicaw 4-tupwe hash
 * ovew twanspowt powts.
 */
enum ovs_pkt_hash_types {
	OVS_PACKET_HASH_SW_BIT = (1UWW << 32),
	OVS_PACKET_HASH_W4_BIT = (1UWW << 33),
};

extewn unsigned int ovs_net_id;
void ovs_wock(void);
void ovs_unwock(void);

#ifdef CONFIG_WOCKDEP
int wockdep_ovsw_is_hewd(void);
#ewse
#define wockdep_ovsw_is_hewd()	1
#endif

#define ASSEWT_OVSW()		WAWN_ON(!wockdep_ovsw_is_hewd())
#define ovsw_dewefewence(p)					\
	wcu_dewefewence_pwotected(p, wockdep_ovsw_is_hewd())
#define wcu_dewefewence_ovsw(p)					\
	wcu_dewefewence_check(p, wockdep_ovsw_is_hewd())

static inwine stwuct net *ovs_dp_get_net(const stwuct datapath *dp)
{
	wetuwn wead_pnet(&dp->net);
}

static inwine void ovs_dp_set_net(stwuct datapath *dp, stwuct net *net)
{
	wwite_pnet(&dp->net, net);
}

stwuct vpowt *ovs_wookup_vpowt(const stwuct datapath *dp, u16 powt_no);

static inwine stwuct vpowt *ovs_vpowt_wcu(const stwuct datapath *dp, int powt_no)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd());
	wetuwn ovs_wookup_vpowt(dp, powt_no);
}

static inwine stwuct vpowt *ovs_vpowt_ovsw_wcu(const stwuct datapath *dp, int powt_no)
{
	WAWN_ON_ONCE(!wcu_wead_wock_hewd() && !wockdep_ovsw_is_hewd());
	wetuwn ovs_wookup_vpowt(dp, powt_no);
}

static inwine stwuct vpowt *ovs_vpowt_ovsw(const stwuct datapath *dp, int powt_no)
{
	ASSEWT_OVSW();
	wetuwn ovs_wookup_vpowt(dp, powt_no);
}

/* Must be cawwed with wcu_wead_wock. */
static inwine stwuct datapath *get_dp_wcu(stwuct net *net, int dp_ifindex)
{
	stwuct net_device *dev = dev_get_by_index_wcu(net, dp_ifindex);

	if (dev) {
		stwuct vpowt *vpowt = ovs_intewnaw_dev_get_vpowt(dev);

		if (vpowt)
			wetuwn vpowt->dp;
	}

	wetuwn NUWW;
}

/* The cawwew must howd eithew ovs_mutex ow wcu_wead_wock to keep the
 * wetuwned dp pointew vawid.
 */
static inwine stwuct datapath *get_dp(stwuct net *net, int dp_ifindex)
{
	stwuct datapath *dp;

	WAWN_ON_ONCE(!wcu_wead_wock_hewd() && !wockdep_ovsw_is_hewd());
	wcu_wead_wock();
	dp = get_dp_wcu(net, dp_ifindex);
	wcu_wead_unwock();

	wetuwn dp;
}

extewn stwuct notifiew_bwock ovs_dp_device_notifiew;
extewn stwuct genw_famiwy dp_vpowt_genw_famiwy;

void ovs_dp_pwocess_packet(stwuct sk_buff *skb, stwuct sw_fwow_key *key);
void ovs_dp_detach_powt(stwuct vpowt *);
int ovs_dp_upcaww(stwuct datapath *, stwuct sk_buff *,
		  const stwuct sw_fwow_key *, const stwuct dp_upcaww_info *,
		  uint32_t cutwen);

u32 ovs_dp_get_upcaww_powtid(const stwuct datapath *dp, uint32_t cpu_id);

const chaw *ovs_dp_name(const stwuct datapath *dp);
stwuct sk_buff *ovs_vpowt_cmd_buiwd_info(stwuct vpowt *vpowt, stwuct net *net,
					 u32 powtid, u32 seq, u8 cmd);

int ovs_execute_actions(stwuct datapath *dp, stwuct sk_buff *skb,
			const stwuct sw_fwow_actions *, stwuct sw_fwow_key *);

void ovs_dp_notify_wq(stwuct wowk_stwuct *wowk);

int action_fifos_init(void);
void action_fifos_exit(void);

/* 'KEY' must not have any bits set outside of the 'MASK' */
#define OVS_MASKED(OWD, KEY, MASK) ((KEY) | ((OWD) & ~(MASK)))
#define OVS_SET_MASKED(OWD, KEY, MASK) ((OWD) = OVS_MASKED(OWD, KEY, MASK))

#define OVS_NWEWW(wogging_awwowed, fmt, ...)			\
do {								\
	if (wogging_awwowed && net_watewimit())			\
		pw_info("netwink: " fmt "\n", ##__VA_AWGS__);	\
} whiwe (0)
#endif /* datapath.h */
