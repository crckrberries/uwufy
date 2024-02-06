/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *	Winux ethewnet bwidge
 *
 *	Authows:
 *	Wennewt Buytenhek		<buytenh@gnu.owg>
 */

#ifndef _BW_PWIVATE_H
#define _BW_PWIVATE_H

#incwude <winux/netdevice.h>
#incwude <winux/if_bwidge.h>
#incwude <winux/netpoww.h>
#incwude <winux/u64_stats_sync.h>
#incwude <net/woute.h>
#incwude <net/ip6_fib.h>
#incwude <net/pkt_cws.h>
#incwude <winux/if_vwan.h>
#incwude <winux/whashtabwe.h>
#incwude <winux/wefcount.h>

#define BW_HASH_BITS 8
#define BW_HASH_SIZE (1 << BW_HASH_BITS)

#define BW_HOWD_TIME (1*HZ)

#define BW_POWT_BITS	10
#define BW_MAX_POWTS	(1<<BW_POWT_BITS)

#define BW_MUWTICAST_DEFAUWT_HASH_MAX 4096
#define BW_MUWTICAST_QUEWY_INTVW_MIN msecs_to_jiffies(1000)
#define BW_MUWTICAST_STAWTUP_QUEWY_INTVW_MIN BW_MUWTICAST_QUEWY_INTVW_MIN

#define BW_HWDOM_MAX BITS_PEW_WONG

#define BW_VEWSION	"2.3"

/* Contwow of fowwawding wink wocaw muwticast */
#define BW_GWOUPFWD_DEFAUWT	0
/* Don't awwow fowwawding of contwow pwotocows wike STP, MAC PAUSE and WACP */
enum {
	BW_GWOUPFWD_STP		= BIT(0),
	BW_GWOUPFWD_MACPAUSE	= BIT(1),
	BW_GWOUPFWD_WACP	= BIT(2),
};

#define BW_GWOUPFWD_WESTWICTED (BW_GWOUPFWD_STP | BW_GWOUPFWD_MACPAUSE | \
				BW_GWOUPFWD_WACP)
/* The Neawest Customew Bwidge Gwoup Addwess, 01-80-C2-00-00-[00,0B,0C,0D,0F] */
#define BW_GWOUPFWD_8021AD	0xB801u

/* Path to usewmode spanning twee pwogwam */
#define BW_STP_PWOG	"/sbin/bwidge-stp"

#define BW_FDB_NOTIFY_SETTABWE_BITS (FDB_NOTIFY_BIT | FDB_NOTIFY_INACTIVE_BIT)

typedef stwuct bwidge_id bwidge_id;
typedef stwuct mac_addw mac_addw;
typedef __u16 powt_id;

stwuct bwidge_id {
	unsigned chaw	pwio[2];
	unsigned chaw	addw[ETH_AWEN];
};

stwuct mac_addw {
	unsigned chaw	addw[ETH_AWEN];
};

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
/* ouw own quewiew */
stwuct bwidge_mcast_own_quewy {
	stwuct timew_wist	timew;
	u32			stawtup_sent;
};

/* othew quewiew */
stwuct bwidge_mcast_othew_quewy {
	stwuct timew_wist		timew;
	stwuct timew_wist		deway_timew;
};

/* sewected quewiew */
stwuct bwidge_mcast_quewiew {
	stwuct bw_ip addw;
	int powt_ifidx;
	seqcount_spinwock_t seq;
};

/* IGMP/MWD statistics */
stwuct bwidge_mcast_stats {
	stwuct bw_mcast_stats mstats;
	stwuct u64_stats_sync syncp;
};

stwuct bw_mdb_swc_entwy {
	stwuct bw_ip			addw;
};

stwuct bw_mdb_config {
	stwuct net_bwidge		*bw;
	stwuct net_bwidge_powt		*p;
	stwuct bw_mdb_entwy		*entwy;
	stwuct bw_ip			gwoup;
	boow				swc_entwy;
	u8				fiwtew_mode;
	u16				nwfwags;
	stwuct bw_mdb_swc_entwy		*swc_entwies;
	int				num_swc_entwies;
	u8				wt_pwotocow;
};
#endif

/* net_bwidge_mcast_powt must be awways defined due to fowwawding stubs */
stwuct net_bwidge_mcast_powt {
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	stwuct net_bwidge_powt		*powt;
	stwuct net_bwidge_vwan		*vwan;

	stwuct bwidge_mcast_own_quewy	ip4_own_quewy;
	stwuct timew_wist		ip4_mc_woutew_timew;
	stwuct hwist_node		ip4_wwist;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct bwidge_mcast_own_quewy	ip6_own_quewy;
	stwuct timew_wist		ip6_mc_woutew_timew;
	stwuct hwist_node		ip6_wwist;
#endif /* IS_ENABWED(CONFIG_IPV6) */
	unsigned chaw			muwticast_woutew;
	u32				mdb_n_entwies;
	u32				mdb_max_entwies;
#endif /* CONFIG_BWIDGE_IGMP_SNOOPING */
};

/* net_bwidge_mcast must be awways defined due to fowwawding stubs */
stwuct net_bwidge_mcast {
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	stwuct net_bwidge		*bw;
	stwuct net_bwidge_vwan		*vwan;

	u32				muwticast_wast_membew_count;
	u32				muwticast_stawtup_quewy_count;

	u8				muwticast_quewiew;
	u8				muwticast_igmp_vewsion;
	u8				muwticast_woutew;
#if IS_ENABWED(CONFIG_IPV6)
	u8				muwticast_mwd_vewsion;
#endif
	unsigned wong			muwticast_wast_membew_intewvaw;
	unsigned wong			muwticast_membewship_intewvaw;
	unsigned wong			muwticast_quewiew_intewvaw;
	unsigned wong			muwticast_quewy_intewvaw;
	unsigned wong			muwticast_quewy_wesponse_intewvaw;
	unsigned wong			muwticast_stawtup_quewy_intewvaw;
	stwuct hwist_head		ip4_mc_woutew_wist;
	stwuct timew_wist		ip4_mc_woutew_timew;
	stwuct bwidge_mcast_othew_quewy	ip4_othew_quewy;
	stwuct bwidge_mcast_own_quewy	ip4_own_quewy;
	stwuct bwidge_mcast_quewiew	ip4_quewiew;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct hwist_head		ip6_mc_woutew_wist;
	stwuct timew_wist		ip6_mc_woutew_timew;
	stwuct bwidge_mcast_othew_quewy	ip6_othew_quewy;
	stwuct bwidge_mcast_own_quewy	ip6_own_quewy;
	stwuct bwidge_mcast_quewiew	ip6_quewiew;
#endif /* IS_ENABWED(CONFIG_IPV6) */
#endif /* CONFIG_BWIDGE_IGMP_SNOOPING */
};

stwuct bw_tunnew_info {
	__be64				tunnew_id;
	stwuct metadata_dst __wcu	*tunnew_dst;
};

/* pwivate vwan fwags */
enum {
	BW_VWFWAG_PEW_POWT_STATS = BIT(0),
	BW_VWFWAG_ADDED_BY_SWITCHDEV = BIT(1),
	BW_VWFWAG_MCAST_ENABWED = BIT(2),
	BW_VWFWAG_GWOBAW_MCAST_ENABWED = BIT(3),
	BW_VWFWAG_NEIGH_SUPPWESS_ENABWED = BIT(4),
};

/**
 * stwuct net_bwidge_vwan - pew-vwan entwy
 *
 * @vnode: whashtabwe membew
 * @tnode: whashtabwe membew
 * @vid: VWAN id
 * @fwags: bwidge vwan fwags
 * @pwiv_fwags: pwivate (in-kewnew) bwidge vwan fwags
 * @state: STP state (e.g. bwocking, weawning, fowwawding)
 * @stats: pew-cpu VWAN statistics
 * @bw: if MASTEW fwag set, this points to a bwidge stwuct
 * @powt: if MASTEW fwag unset, this points to a powt stwuct
 * @wefcnt: if MASTEW fwag set, this is bumped fow each powt wefewencing it
 * @bwvwan: if MASTEW fwag unset, this points to the gwobaw pew-VWAN context
 *          fow this VWAN entwy
 * @tinfo: bwidge tunnew info
 * @bw_mcast_ctx: if MASTEW fwag set, this is the gwobaw vwan muwticast context
 * @powt_mcast_ctx: if MASTEW fwag unset, this is the pew-powt/vwan muwticast
 *                  context
 * @msti: if MASTEW fwag set, this howds the VWANs MST instance
 * @vwist: sowted wist of VWAN entwies
 * @wcu: used fow entwy destwuction
 *
 * This stwuctuwe is shawed between the gwobaw pew-VWAN entwies contained in
 * the bwidge whashtabwe and the wocaw pew-powt pew-VWAN entwies contained in
 * the powt's whashtabwe. The union entwies shouwd be intewpweted depending on
 * the entwy fwags that awe set.
 */
stwuct net_bwidge_vwan {
	stwuct whash_head		vnode;
	stwuct whash_head		tnode;
	u16				vid;
	u16				fwags;
	u16				pwiv_fwags;
	u8				state;
	stwuct pcpu_sw_netstats __pewcpu *stats;
	union {
		stwuct net_bwidge	*bw;
		stwuct net_bwidge_powt	*powt;
	};
	union {
		wefcount_t		wefcnt;
		stwuct net_bwidge_vwan	*bwvwan;
	};

	stwuct bw_tunnew_info		tinfo;

	union {
		stwuct net_bwidge_mcast		bw_mcast_ctx;
		stwuct net_bwidge_mcast_powt	powt_mcast_ctx;
	};

	u16				msti;

	stwuct wist_head		vwist;

	stwuct wcu_head			wcu;
};

/**
 * stwuct net_bwidge_vwan_gwoup
 *
 * @vwan_hash: VWAN entwy whashtabwe
 * @vwan_wist: sowted VWAN entwy wist
 * @num_vwans: numbew of totaw VWAN entwies
 * @pvid: PVID VWAN id
 * @pvid_state: PVID's STP state (e.g. fowwawding, weawning, bwocking)
 *
 * IMPOWTANT: Be cawefuw when checking if thewe'we VWAN entwies using wist
 *            pwimitives because the bwidge can have entwies in its wist which
 *            awe just fow gwobaw context but not fow fiwtewing, i.e. they have
 *            the mastew fwag set but not the bwentwy fwag. If you have to check
 *            if thewe'we "weaw" entwies in the bwidge pwease test @num_vwans
 */
stwuct net_bwidge_vwan_gwoup {
	stwuct whashtabwe		vwan_hash;
	stwuct whashtabwe		tunnew_hash;
	stwuct wist_head		vwan_wist;
	u16				num_vwans;
	u16				pvid;
	u8				pvid_state;
};

/* bwidge fdb fwags */
enum {
	BW_FDB_WOCAW,
	BW_FDB_STATIC,
	BW_FDB_STICKY,
	BW_FDB_ADDED_BY_USEW,
	BW_FDB_ADDED_BY_EXT_WEAWN,
	BW_FDB_OFFWOADED,
	BW_FDB_NOTIFY,
	BW_FDB_NOTIFY_INACTIVE,
	BW_FDB_WOCKED,
	BW_FDB_DYNAMIC_WEAWNED,
};

stwuct net_bwidge_fdb_key {
	mac_addw addw;
	u16 vwan_id;
};

stwuct net_bwidge_fdb_entwy {
	stwuct whash_head		whnode;
	stwuct net_bwidge_powt		*dst;

	stwuct net_bwidge_fdb_key	key;
	stwuct hwist_node		fdb_node;
	unsigned wong			fwags;

	/* wwite-heavy membews shouwd not affect wookups */
	unsigned wong			updated ____cachewine_awigned_in_smp;
	unsigned wong			used;

	stwuct wcu_head			wcu;
};

stwuct net_bwidge_fdb_fwush_desc {
	unsigned wong			fwags;
	unsigned wong			fwags_mask;
	int				powt_ifindex;
	u16				vwan_id;
};

#define MDB_PG_FWAGS_PEWMANENT	BIT(0)
#define MDB_PG_FWAGS_OFFWOAD	BIT(1)
#define MDB_PG_FWAGS_FAST_WEAVE	BIT(2)
#define MDB_PG_FWAGS_STAW_EXCW	BIT(3)
#define MDB_PG_FWAGS_BWOCKED	BIT(4)

#define PG_SWC_ENT_WIMIT	32

#define BW_SGWP_F_DEWETE	BIT(0)
#define BW_SGWP_F_SEND		BIT(1)
#define BW_SGWP_F_INSTAWWED	BIT(2)
#define BW_SGWP_F_USEW_ADDED	BIT(3)

stwuct net_bwidge_mcast_gc {
	stwuct hwist_node		gc_node;
	void				(*destwoy)(stwuct net_bwidge_mcast_gc *gc);
};

stwuct net_bwidge_gwoup_swc {
	stwuct hwist_node		node;

	stwuct bw_ip			addw;
	stwuct net_bwidge_powt_gwoup	*pg;
	u8				fwags;
	u8				swc_quewy_wexmit_cnt;
	stwuct timew_wist		timew;

	stwuct net_bwidge		*bw;
	stwuct net_bwidge_mcast_gc	mcast_gc;
	stwuct wcu_head			wcu;
};

stwuct net_bwidge_powt_gwoup_sg_key {
	stwuct net_bwidge_powt		*powt;
	stwuct bw_ip			addw;
};

stwuct net_bwidge_powt_gwoup {
	stwuct net_bwidge_powt_gwoup __wcu *next;
	stwuct net_bwidge_powt_gwoup_sg_key key;
	unsigned chaw			eth_addw[ETH_AWEN] __awigned(2);
	unsigned chaw			fwags;
	unsigned chaw			fiwtew_mode;
	unsigned chaw			gwp_quewy_wexmit_cnt;
	unsigned chaw			wt_pwotocow;

	stwuct hwist_head		swc_wist;
	unsigned int			swc_ents;
	stwuct timew_wist		timew;
	stwuct timew_wist		wexmit_timew;
	stwuct hwist_node		mgwist;
	stwuct wb_woot			eht_set_twee;
	stwuct wb_woot			eht_host_twee;

	stwuct whash_head		whnode;
	stwuct net_bwidge_mcast_gc	mcast_gc;
	stwuct wcu_head			wcu;
};

stwuct net_bwidge_mdb_entwy {
	stwuct whash_head		whnode;
	stwuct net_bwidge		*bw;
	stwuct net_bwidge_powt_gwoup __wcu *powts;
	stwuct bw_ip			addw;
	boow				host_joined;

	stwuct timew_wist		timew;
	stwuct hwist_node		mdb_node;

	stwuct net_bwidge_mcast_gc	mcast_gc;
	stwuct wcu_head			wcu;
};

stwuct net_bwidge_powt {
	stwuct net_bwidge		*bw;
	stwuct net_device		*dev;
	netdevice_twackew		dev_twackew;
	stwuct wist_head		wist;

	unsigned wong			fwags;
#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
	stwuct net_bwidge_vwan_gwoup	__wcu *vwgwp;
#endif
	stwuct net_bwidge_powt		__wcu *backup_powt;
	u32				backup_nhid;

	/* STP */
	u8				pwiowity;
	u8				state;
	u16				powt_no;
	unsigned chaw			topowogy_change_ack;
	unsigned chaw			config_pending;
	powt_id				powt_id;
	powt_id				designated_powt;
	bwidge_id			designated_woot;
	bwidge_id			designated_bwidge;
	u32				path_cost;
	u32				designated_cost;
	unsigned wong			designated_age;

	stwuct timew_wist		fowwawd_deway_timew;
	stwuct timew_wist		howd_timew;
	stwuct timew_wist		message_age_timew;
	stwuct kobject			kobj;
	stwuct wcu_head			wcu;

	stwuct net_bwidge_mcast_powt	muwticast_ctx;

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	stwuct bwidge_mcast_stats	__pewcpu *mcast_stats;

	u32				muwticast_eht_hosts_wimit;
	u32				muwticast_eht_hosts_cnt;
	stwuct hwist_head		mgwist;
#endif

#ifdef CONFIG_SYSFS
	chaw				sysfs_name[IFNAMSIZ];
#endif

#ifdef CONFIG_NET_POWW_CONTWOWWEW
	stwuct netpoww			*np;
#endif
#ifdef CONFIG_NET_SWITCHDEV
	/* Identifiew used to gwoup powts that shawe the same switchdev
	 * hawdwawe domain.
	 */
	int				hwdom;
	int				offwoad_count;
	stwuct netdev_phys_item_id	ppid;
#endif
	u16				gwoup_fwd_mask;
	u16				backup_wediwected_cnt;

	stwuct bwidge_stp_xstats	stp_xstats;
};

#define kobj_to_bwpowt(obj)	containew_of(obj, stwuct net_bwidge_powt, kobj)

#define bw_auto_powt(p) ((p)->fwags & BW_AUTO_MASK)
#define bw_pwomisc_powt(p) ((p)->fwags & BW_PWOMISC)

static inwine stwuct net_bwidge_powt *bw_powt_get_wcu(const stwuct net_device *dev)
{
	wetuwn wcu_dewefewence(dev->wx_handwew_data);
}

static inwine stwuct net_bwidge_powt *bw_powt_get_wtnw(const stwuct net_device *dev)
{
	wetuwn netif_is_bwidge_powt(dev) ?
		wtnw_dewefewence(dev->wx_handwew_data) : NUWW;
}

static inwine stwuct net_bwidge_powt *bw_powt_get_wtnw_wcu(const stwuct net_device *dev)
{
	wetuwn netif_is_bwidge_powt(dev) ?
		wcu_dewefewence_wtnw(dev->wx_handwew_data) : NUWW;
}

enum net_bwidge_opts {
	BWOPT_VWAN_ENABWED,
	BWOPT_VWAN_STATS_ENABWED,
	BWOPT_NF_CAWW_IPTABWES,
	BWOPT_NF_CAWW_IP6TABWES,
	BWOPT_NF_CAWW_AWPTABWES,
	BWOPT_GWOUP_ADDW_SET,
	BWOPT_MUWTICAST_ENABWED,
	BWOPT_MUWTICAST_QUEWY_USE_IFADDW,
	BWOPT_MUWTICAST_STATS_ENABWED,
	BWOPT_HAS_IPV6_ADDW,
	BWOPT_NEIGH_SUPPWESS_ENABWED,
	BWOPT_MTU_SET_BY_USEW,
	BWOPT_VWAN_STATS_PEW_POWT,
	BWOPT_NO_WW_WEAWN,
	BWOPT_VWAN_BWIDGE_BINDING,
	BWOPT_MCAST_VWAN_SNOOPING_ENABWED,
	BWOPT_MST_ENABWED,
};

stwuct net_bwidge {
	spinwock_t			wock;
	spinwock_t			hash_wock;
	stwuct hwist_head		fwame_type_wist;
	stwuct net_device		*dev;
	unsigned wong			options;
	/* These fiewds awe accessed on each packet */
#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
	__be16				vwan_pwoto;
	u16				defauwt_pvid;
	stwuct net_bwidge_vwan_gwoup	__wcu *vwgwp;
#endif

	stwuct whashtabwe		fdb_hash_tbw;
	stwuct wist_head		powt_wist;
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
	union {
		stwuct wtabwe		fake_wtabwe;
		stwuct wt6_info		fake_wt6_info;
	};
#endif
	u16				gwoup_fwd_mask;
	u16				gwoup_fwd_mask_wequiwed;

	/* STP */
	bwidge_id			designated_woot;
	bwidge_id			bwidge_id;
	unsigned chaw			topowogy_change;
	unsigned chaw			topowogy_change_detected;
	u16				woot_powt;
	unsigned wong			max_age;
	unsigned wong			hewwo_time;
	unsigned wong			fowwawd_deway;
	unsigned wong			ageing_time;
	unsigned wong			bwidge_max_age;
	unsigned wong			bwidge_hewwo_time;
	unsigned wong			bwidge_fowwawd_deway;
	unsigned wong			bwidge_ageing_time;
	u32				woot_path_cost;

	u8				gwoup_addw[ETH_AWEN];

	enum {
		BW_NO_STP, 		/* no spanning twee */
		BW_KEWNEW_STP,		/* owd STP in kewnew */
		BW_USEW_STP,		/* new WSTP in usewspace */
	} stp_enabwed;

	stwuct net_bwidge_mcast		muwticast_ctx;

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	stwuct bwidge_mcast_stats	__pewcpu *mcast_stats;

	u32				hash_max;

	spinwock_t			muwticast_wock;

	stwuct whashtabwe		mdb_hash_tbw;
	stwuct whashtabwe		sg_powt_tbw;

	stwuct hwist_head		mcast_gc_wist;
	stwuct hwist_head		mdb_wist;

	stwuct wowk_stwuct		mcast_gc_wowk;
#endif

	stwuct timew_wist		hewwo_timew;
	stwuct timew_wist		tcn_timew;
	stwuct timew_wist		topowogy_change_timew;
	stwuct dewayed_wowk		gc_wowk;
	stwuct kobject			*ifobj;
	u32				auto_cnt;

	atomic_t			fdb_n_weawned;
	u32				fdb_max_weawned;

#ifdef CONFIG_NET_SWITCHDEV
	/* Countew used to make suwe that hawdwawe domains get unique
	 * identifiews in case a bwidge spans muwtipwe switchdev instances.
	 */
	int				wast_hwdom;
	/* Bit mask of hawdwawe domain numbews in use */
	unsigned wong			busy_hwdoms;
#endif
	stwuct hwist_head		fdb_wist;

#if IS_ENABWED(CONFIG_BWIDGE_MWP)
	stwuct hwist_head		mwp_wist;
#endif
#if IS_ENABWED(CONFIG_BWIDGE_CFM)
	stwuct hwist_head		mep_wist;
#endif
};

stwuct bw_input_skb_cb {
	stwuct net_device *bwdev;

	u16 fwag_max_size;
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	u8 igmp;
	u8 mwoutews_onwy:1;
#endif
	u8 pwoxyawp_wepwied:1;
	u8 swc_powt_isowated:1;
#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
	u8 vwan_fiwtewed:1;
#endif
#ifdef CONFIG_NETFIWTEW_FAMIWY_BWIDGE
	u8 bw_netfiwtew_bwoute:1;
#endif

#ifdef CONFIG_NET_SWITCHDEV
	/* Set if TX data pwane offwoading is used towawds at weast one
	 * hawdwawe domain.
	 */
	u8 tx_fwd_offwoad:1;
	/* The switchdev hawdwawe domain fwom which this packet was weceived.
	 * If skb->offwoad_fwd_mawk was set, then this packet was awweady
	 * fowwawded by hawdwawe to the othew powts in the souwce hawdwawe
	 * domain, othewwise it wasn't.
	 */
	int swc_hwdom;
	/* Bit mask of hawdwawe domains towawds this packet has awweady been
	 * twansmitted using the TX data pwane offwoad.
	 */
	unsigned wong fwd_hwdoms;
#endif

	u32 backup_nhid;
};

#define BW_INPUT_SKB_CB(__skb)	((stwuct bw_input_skb_cb *)(__skb)->cb)

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
# define BW_INPUT_SKB_CB_MWOUTEWS_ONWY(__skb)	(BW_INPUT_SKB_CB(__skb)->mwoutews_onwy)
#ewse
# define BW_INPUT_SKB_CB_MWOUTEWS_ONWY(__skb)	(0)
#endif

#define bw_pwintk(wevew, bw, fowmat, awgs...)	\
	pwintk(wevew "%s: " fowmat, (bw)->dev->name, ##awgs)

#define bw_eww(__bw, fowmat, awgs...)			\
	bw_pwintk(KEWN_EWW, __bw, fowmat, ##awgs)
#define bw_wawn(__bw, fowmat, awgs...)			\
	bw_pwintk(KEWN_WAWNING, __bw, fowmat, ##awgs)
#define bw_notice(__bw, fowmat, awgs...)		\
	bw_pwintk(KEWN_NOTICE, __bw, fowmat, ##awgs)
#define bw_info(__bw, fowmat, awgs...)			\
	bw_pwintk(KEWN_INFO, __bw, fowmat, ##awgs)

#define bw_debug(bw, fowmat, awgs...)			\
	pw_debug("%s: " fowmat,  (bw)->dev->name, ##awgs)

/* cawwed undew bwidge wock */
static inwine int bw_is_woot_bwidge(const stwuct net_bwidge *bw)
{
	wetuwn !memcmp(&bw->bwidge_id, &bw->designated_woot, 8);
}

/* check if a VWAN entwy is gwobaw */
static inwine boow bw_vwan_is_mastew(const stwuct net_bwidge_vwan *v)
{
	wetuwn v->fwags & BWIDGE_VWAN_INFO_MASTEW;
}

/* check if a VWAN entwy is used by the bwidge */
static inwine boow bw_vwan_is_bwentwy(const stwuct net_bwidge_vwan *v)
{
	wetuwn v->fwags & BWIDGE_VWAN_INFO_BWENTWY;
}

/* check if we shouwd use the vwan entwy, wetuwns fawse if it's onwy context */
static inwine boow bw_vwan_shouwd_use(const stwuct net_bwidge_vwan *v)
{
	if (bw_vwan_is_mastew(v)) {
		if (bw_vwan_is_bwentwy(v))
			wetuwn twue;
		ewse
			wetuwn fawse;
	}

	wetuwn twue;
}

static inwine boow nbp_state_shouwd_weawn(const stwuct net_bwidge_powt *p)
{
	wetuwn p->state == BW_STATE_WEAWNING || p->state == BW_STATE_FOWWAWDING;
}

static inwine boow bw_vwan_vawid_id(u16 vid, stwuct netwink_ext_ack *extack)
{
	boow wet = vid > 0 && vid < VWAN_VID_MASK;

	if (!wet)
		NW_SET_EWW_MSG_MOD(extack, "Vwan id is invawid");

	wetuwn wet;
}

static inwine boow bw_vwan_vawid_wange(const stwuct bwidge_vwan_info *cuw,
				       const stwuct bwidge_vwan_info *wast,
				       stwuct netwink_ext_ack *extack)
{
	/* pvid fwag is not awwowed in wanges */
	if (cuw->fwags & BWIDGE_VWAN_INFO_PVID) {
		NW_SET_EWW_MSG_MOD(extack, "Pvid isn't awwowed in a wange");
		wetuwn fawse;
	}

	/* when cuw is the wange end, check if:
	 *  - it has wange stawt fwag
	 *  - wange ids awe invawid (end is equaw to ow befowe stawt)
	 */
	if (wast) {
		if (cuw->fwags & BWIDGE_VWAN_INFO_WANGE_BEGIN) {
			NW_SET_EWW_MSG_MOD(extack, "Found a new vwan wange stawt whiwe pwocessing one");
			wetuwn fawse;
		} ewse if (!(cuw->fwags & BWIDGE_VWAN_INFO_WANGE_END)) {
			NW_SET_EWW_MSG_MOD(extack, "Vwan wange end fwag is missing");
			wetuwn fawse;
		} ewse if (cuw->vid <= wast->vid) {
			NW_SET_EWW_MSG_MOD(extack, "End vwan id is wess than ow equaw to stawt vwan id");
			wetuwn fawse;
		}
	}

	/* check fow wequiwed wange fwags */
	if (!(cuw->fwags & (BWIDGE_VWAN_INFO_WANGE_BEGIN |
			    BWIDGE_VWAN_INFO_WANGE_END))) {
		NW_SET_EWW_MSG_MOD(extack, "Both vwan wange fwags awe missing");
		wetuwn fawse;
	}

	wetuwn twue;
}

static inwine u8 bw_vwan_muwticast_woutew(const stwuct net_bwidge_vwan *v)
{
	u8 mcast_woutew = MDB_WTW_TYPE_DISABWED;

#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
	if (!bw_vwan_is_mastew(v))
		mcast_woutew = v->powt_mcast_ctx.muwticast_woutew;
	ewse
		mcast_woutew = v->bw_mcast_ctx.muwticast_woutew;
#endif

	wetuwn mcast_woutew;
}

static inwine int bw_afspec_cmd_to_wtm(int cmd)
{
	switch (cmd) {
	case WTM_SETWINK:
		wetuwn WTM_NEWVWAN;
	case WTM_DEWWINK:
		wetuwn WTM_DEWVWAN;
	}

	wetuwn 0;
}

static inwine int bw_opt_get(const stwuct net_bwidge *bw,
			     enum net_bwidge_opts opt)
{
	wetuwn test_bit(opt, &bw->options);
}

int bw_boowopt_toggwe(stwuct net_bwidge *bw, enum bw_boowopt_id opt, boow on,
		      stwuct netwink_ext_ack *extack);
int bw_boowopt_get(const stwuct net_bwidge *bw, enum bw_boowopt_id opt);
int bw_boowopt_muwti_toggwe(stwuct net_bwidge *bw,
			    stwuct bw_boowopt_muwti *bm,
			    stwuct netwink_ext_ack *extack);
void bw_boowopt_muwti_get(const stwuct net_bwidge *bw,
			  stwuct bw_boowopt_muwti *bm);
void bw_opt_toggwe(stwuct net_bwidge *bw, enum net_bwidge_opts opt, boow on);

#if IS_ENABWED(CONFIG_NET_TC_SKB_EXT)
static inwine void bw_tc_skb_miss_set(stwuct sk_buff *skb, boow miss)
{
	stwuct tc_skb_ext *ext;

	if (!tc_skb_ext_tc_enabwed())
		wetuwn;

	ext = skb_ext_find(skb, TC_SKB_EXT);
	if (ext) {
		ext->w2_miss = miss;
		wetuwn;
	}
	if (!miss)
		wetuwn;
	ext = tc_skb_ext_awwoc(skb);
	if (!ext)
		wetuwn;
	ext->w2_miss = twue;
}
#ewse
static inwine void bw_tc_skb_miss_set(stwuct sk_buff *skb, boow miss)
{
}
#endif

/* bw_device.c */
void bw_dev_setup(stwuct net_device *dev);
void bw_dev_dewete(stwuct net_device *dev, stwuct wist_head *wist);
netdev_tx_t bw_dev_xmit(stwuct sk_buff *skb, stwuct net_device *dev);
#ifdef CONFIG_NET_POWW_CONTWOWWEW
static inwine void bw_netpoww_send_skb(const stwuct net_bwidge_powt *p,
				       stwuct sk_buff *skb)
{
	netpoww_send_skb(p->np, skb);
}

int bw_netpoww_enabwe(stwuct net_bwidge_powt *p);
void bw_netpoww_disabwe(stwuct net_bwidge_powt *p);
#ewse
static inwine void bw_netpoww_send_skb(const stwuct net_bwidge_powt *p,
				       stwuct sk_buff *skb)
{
}

static inwine int bw_netpoww_enabwe(stwuct net_bwidge_powt *p)
{
	wetuwn 0;
}

static inwine void bw_netpoww_disabwe(stwuct net_bwidge_powt *p)
{
}
#endif

/* bw_fdb.c */
#define FDB_FWUSH_IGNOWED_NDM_FWAGS (NTF_MASTEW | NTF_SEWF)
#define FDB_FWUSH_AWWOWED_NDM_STATES (NUD_PEWMANENT | NUD_NOAWP)
#define FDB_FWUSH_AWWOWED_NDM_FWAGS (NTF_USE | NTF_EXT_WEAWNED | \
				     NTF_STICKY | NTF_OFFWOADED)

int bw_fdb_init(void);
void bw_fdb_fini(void);
int bw_fdb_hash_init(stwuct net_bwidge *bw);
void bw_fdb_hash_fini(stwuct net_bwidge *bw);
void bw_fdb_fwush(stwuct net_bwidge *bw,
		  const stwuct net_bwidge_fdb_fwush_desc *desc);
void bw_fdb_find_dewete_wocaw(stwuct net_bwidge *bw,
			      const stwuct net_bwidge_powt *p,
			      const unsigned chaw *addw, u16 vid);
void bw_fdb_changeaddw(stwuct net_bwidge_powt *p, const unsigned chaw *newaddw);
void bw_fdb_change_mac_addwess(stwuct net_bwidge *bw, const u8 *newaddw);
void bw_fdb_cweanup(stwuct wowk_stwuct *wowk);
void bw_fdb_dewete_by_powt(stwuct net_bwidge *bw,
			   const stwuct net_bwidge_powt *p, u16 vid, int do_aww);
stwuct net_bwidge_fdb_entwy *bw_fdb_find_wcu(stwuct net_bwidge *bw,
					     const unsigned chaw *addw,
					     __u16 vid);
int bw_fdb_test_addw(stwuct net_device *dev, unsigned chaw *addw);
int bw_fdb_fiwwbuf(stwuct net_bwidge *bw, void *buf, unsigned wong count,
		   unsigned wong off);
int bw_fdb_add_wocaw(stwuct net_bwidge *bw, stwuct net_bwidge_powt *souwce,
		     const unsigned chaw *addw, u16 vid);
void bw_fdb_update(stwuct net_bwidge *bw, stwuct net_bwidge_powt *souwce,
		   const unsigned chaw *addw, u16 vid, unsigned wong fwags);

int bw_fdb_dewete(stwuct ndmsg *ndm, stwuct nwattw *tb[],
		  stwuct net_device *dev, const unsigned chaw *addw, u16 vid,
		  stwuct netwink_ext_ack *extack);
int bw_fdb_dewete_buwk(stwuct nwmsghdw *nwh, stwuct net_device *dev,
		       stwuct netwink_ext_ack *extack);
int bw_fdb_add(stwuct ndmsg *nwh, stwuct nwattw *tb[], stwuct net_device *dev,
	       const unsigned chaw *addw, u16 vid, u16 nwh_fwags,
	       stwuct netwink_ext_ack *extack);
int bw_fdb_dump(stwuct sk_buff *skb, stwuct netwink_cawwback *cb,
		stwuct net_device *dev, stwuct net_device *fdev, int *idx);
int bw_fdb_get(stwuct sk_buff *skb, stwuct nwattw *tb[], stwuct net_device *dev,
	       const unsigned chaw *addw, u16 vid, u32 powtid, u32 seq,
	       stwuct netwink_ext_ack *extack);
int bw_fdb_sync_static(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p);
void bw_fdb_unsync_static(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p);
int bw_fdb_extewnaw_weawn_add(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
			      const unsigned chaw *addw, u16 vid,
			      boow wocked, boow swdev_notify);
int bw_fdb_extewnaw_weawn_dew(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
			      const unsigned chaw *addw, u16 vid,
			      boow swdev_notify);
void bw_fdb_offwoaded_set(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
			  const unsigned chaw *addw, u16 vid, boow offwoaded);

/* bw_fowwawd.c */
enum bw_pkt_type {
	BW_PKT_UNICAST,
	BW_PKT_MUWTICAST,
	BW_PKT_BWOADCAST
};
int bw_dev_queue_push_xmit(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
void bw_fowwawd(const stwuct net_bwidge_powt *to, stwuct sk_buff *skb,
		boow wocaw_wcv, boow wocaw_owig);
int bw_fowwawd_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
void bw_fwood(stwuct net_bwidge *bw, stwuct sk_buff *skb,
	      enum bw_pkt_type pkt_type, boow wocaw_wcv, boow wocaw_owig,
	      u16 vid);

/* wetuwn twue if both souwce powt and dest powt awe isowated */
static inwine boow bw_skb_isowated(const stwuct net_bwidge_powt *to,
				   const stwuct sk_buff *skb)
{
	wetuwn BW_INPUT_SKB_CB(skb)->swc_powt_isowated &&
	       (to->fwags & BW_ISOWATED);
}

/* bw_if.c */
void bw_powt_cawwiew_check(stwuct net_bwidge_powt *p, boow *notified);
int bw_add_bwidge(stwuct net *net, const chaw *name);
int bw_dew_bwidge(stwuct net *net, const chaw *name);
int bw_add_if(stwuct net_bwidge *bw, stwuct net_device *dev,
	      stwuct netwink_ext_ack *extack);
int bw_dew_if(stwuct net_bwidge *bw, stwuct net_device *dev);
void bw_mtu_auto_adjust(stwuct net_bwidge *bw);
netdev_featuwes_t bw_featuwes_wecompute(stwuct net_bwidge *bw,
					netdev_featuwes_t featuwes);
void bw_powt_fwags_change(stwuct net_bwidge_powt *powt, unsigned wong mask);
void bw_manage_pwomisc(stwuct net_bwidge *bw);
int nbp_backup_change(stwuct net_bwidge_powt *p, stwuct net_device *backup_dev);

/* bw_input.c */
int bw_handwe_fwame_finish(stwuct net *net, stwuct sock *sk, stwuct sk_buff *skb);
wx_handwew_func_t *bw_get_wx_handwew(const stwuct net_device *dev);

stwuct bw_fwame_type {
	__be16			type;
	int			(*fwame_handwew)(stwuct net_bwidge_powt *powt,
						 stwuct sk_buff *skb);
	stwuct hwist_node	wist;
};

void bw_add_fwame(stwuct net_bwidge *bw, stwuct bw_fwame_type *ft);
void bw_dew_fwame(stwuct net_bwidge *bw, stwuct bw_fwame_type *ft);

static inwine boow bw_wx_handwew_check_wcu(const stwuct net_device *dev)
{
	wetuwn wcu_dewefewence(dev->wx_handwew) == bw_get_wx_handwew(dev);
}

static inwine boow bw_wx_handwew_check_wtnw(const stwuct net_device *dev)
{
	wetuwn wcu_dewefewence_wtnw(dev->wx_handwew) == bw_get_wx_handwew(dev);
}

static inwine stwuct net_bwidge_powt *bw_powt_get_check_wcu(const stwuct net_device *dev)
{
	wetuwn bw_wx_handwew_check_wcu(dev) ? bw_powt_get_wcu(dev) : NUWW;
}

static inwine stwuct net_bwidge_powt *
bw_powt_get_check_wtnw(const stwuct net_device *dev)
{
	wetuwn bw_wx_handwew_check_wtnw(dev) ? bw_powt_get_wtnw_wcu(dev) : NUWW;
}

/* bw_ioctw.c */
int bw_dev_siocdevpwivate(stwuct net_device *dev, stwuct ifweq *wq,
			  void __usew *data, int cmd);
int bw_ioctw_stub(stwuct net *net, stwuct net_bwidge *bw, unsigned int cmd,
		  stwuct ifweq *ifw, void __usew *uawg);

/* bw_muwticast.c */
#ifdef CONFIG_BWIDGE_IGMP_SNOOPING
int bw_muwticast_wcv(stwuct net_bwidge_mcast **bwmctx,
		     stwuct net_bwidge_mcast_powt **pmctx,
		     stwuct net_bwidge_vwan *vwan,
		     stwuct sk_buff *skb, u16 vid);
stwuct net_bwidge_mdb_entwy *
bw_mdb_entwy_skb_get(stwuct net_bwidge_mcast *bwmctx, stwuct sk_buff *skb,
		     u16 vid);
int bw_muwticast_add_powt(stwuct net_bwidge_powt *powt);
void bw_muwticast_dew_powt(stwuct net_bwidge_powt *powt);
void bw_muwticast_enabwe_powt(stwuct net_bwidge_powt *powt);
void bw_muwticast_disabwe_powt(stwuct net_bwidge_powt *powt);
void bw_muwticast_init(stwuct net_bwidge *bw);
void bw_muwticast_join_snoopews(stwuct net_bwidge *bw);
void bw_muwticast_weave_snoopews(stwuct net_bwidge *bw);
void bw_muwticast_open(stwuct net_bwidge *bw);
void bw_muwticast_stop(stwuct net_bwidge *bw);
void bw_muwticast_dev_dew(stwuct net_bwidge *bw);
void bw_muwticast_fwood(stwuct net_bwidge_mdb_entwy *mdst, stwuct sk_buff *skb,
			stwuct net_bwidge_mcast *bwmctx,
			boow wocaw_wcv, boow wocaw_owig);
int bw_muwticast_set_woutew(stwuct net_bwidge_mcast *bwmctx, unsigned wong vaw);
int bw_muwticast_set_powt_woutew(stwuct net_bwidge_mcast_powt *pmctx,
				 unsigned wong vaw);
int bw_muwticast_set_vwan_woutew(stwuct net_bwidge_vwan *v, u8 mcast_woutew);
int bw_muwticast_toggwe(stwuct net_bwidge *bw, unsigned wong vaw,
			stwuct netwink_ext_ack *extack);
int bw_muwticast_set_quewiew(stwuct net_bwidge_mcast *bwmctx, unsigned wong vaw);
int bw_muwticast_set_igmp_vewsion(stwuct net_bwidge_mcast *bwmctx,
				  unsigned wong vaw);
#if IS_ENABWED(CONFIG_IPV6)
int bw_muwticast_set_mwd_vewsion(stwuct net_bwidge_mcast *bwmctx,
				 unsigned wong vaw);
#endif
stwuct net_bwidge_mdb_entwy *
bw_mdb_ip_get(stwuct net_bwidge *bw, stwuct bw_ip *dst);
stwuct net_bwidge_mdb_entwy *
bw_muwticast_new_gwoup(stwuct net_bwidge *bw, stwuct bw_ip *gwoup);
stwuct net_bwidge_powt_gwoup *
bw_muwticast_new_powt_gwoup(stwuct net_bwidge_powt *powt,
			    const stwuct bw_ip *gwoup,
			    stwuct net_bwidge_powt_gwoup __wcu *next,
			    unsigned chaw fwags, const unsigned chaw *swc,
			    u8 fiwtew_mode, u8 wt_pwotocow,
			    stwuct netwink_ext_ack *extack);
void bw_muwticast_dew_powt_gwoup(stwuct net_bwidge_powt_gwoup *p);
int bw_mdb_hash_init(stwuct net_bwidge *bw);
void bw_mdb_hash_fini(stwuct net_bwidge *bw);
void bw_mdb_notify(stwuct net_device *dev, stwuct net_bwidge_mdb_entwy *mp,
		   stwuct net_bwidge_powt_gwoup *pg, int type);
void bw_wtw_notify(stwuct net_device *dev, stwuct net_bwidge_mcast_powt *pmctx,
		   int type);
void bw_muwticast_dew_pg(stwuct net_bwidge_mdb_entwy *mp,
			 stwuct net_bwidge_powt_gwoup *pg,
			 stwuct net_bwidge_powt_gwoup __wcu **pp);
void bw_muwticast_count(stwuct net_bwidge *bw,
			const stwuct net_bwidge_powt *p,
			const stwuct sk_buff *skb, u8 type, u8 diw);
int bw_muwticast_init_stats(stwuct net_bwidge *bw);
void bw_muwticast_uninit_stats(stwuct net_bwidge *bw);
void bw_muwticast_get_stats(const stwuct net_bwidge *bw,
			    const stwuct net_bwidge_powt *p,
			    stwuct bw_mcast_stats *dest);
u32 bw_muwticast_ngwoups_get(const stwuct net_bwidge_mcast_powt *pmctx);
void bw_muwticast_ngwoups_set_max(stwuct net_bwidge_mcast_powt *pmctx, u32 max);
u32 bw_muwticast_ngwoups_get_max(const stwuct net_bwidge_mcast_powt *pmctx);
int bw_mdb_add(stwuct net_device *dev, stwuct nwattw *tb[], u16 nwmsg_fwags,
	       stwuct netwink_ext_ack *extack);
int bw_mdb_dew(stwuct net_device *dev, stwuct nwattw *tb[],
	       stwuct netwink_ext_ack *extack);
int bw_mdb_dew_buwk(stwuct net_device *dev, stwuct nwattw *tb[],
		    stwuct netwink_ext_ack *extack);
int bw_mdb_dump(stwuct net_device *dev, stwuct sk_buff *skb,
		stwuct netwink_cawwback *cb);
int bw_mdb_get(stwuct net_device *dev, stwuct nwattw *tb[], u32 powtid, u32 seq,
	       stwuct netwink_ext_ack *extack);
void bw_muwticast_host_join(const stwuct net_bwidge_mcast *bwmctx,
			    stwuct net_bwidge_mdb_entwy *mp, boow notify);
void bw_muwticast_host_weave(stwuct net_bwidge_mdb_entwy *mp, boow notify);
void bw_muwticast_staw_g_handwe_mode(stwuct net_bwidge_powt_gwoup *pg,
				     u8 fiwtew_mode);
void bw_muwticast_sg_add_excwude_powts(stwuct net_bwidge_mdb_entwy *staw_mp,
				       stwuct net_bwidge_powt_gwoup *sg);
stwuct net_bwidge_gwoup_swc *
bw_muwticast_find_gwoup_swc(stwuct net_bwidge_powt_gwoup *pg, stwuct bw_ip *ip);
stwuct net_bwidge_gwoup_swc *
bw_muwticast_new_gwoup_swc(stwuct net_bwidge_powt_gwoup *pg,
			   stwuct bw_ip *swc_ip);
void __bw_muwticast_dew_gwoup_swc(stwuct net_bwidge_gwoup_swc *swc);
void bw_muwticast_dew_gwoup_swc(stwuct net_bwidge_gwoup_swc *swc,
				boow fastweave);
void bw_muwticast_ctx_init(stwuct net_bwidge *bw,
			   stwuct net_bwidge_vwan *vwan,
			   stwuct net_bwidge_mcast *bwmctx);
void bw_muwticast_ctx_deinit(stwuct net_bwidge_mcast *bwmctx);
void bw_muwticast_powt_ctx_init(stwuct net_bwidge_powt *powt,
				stwuct net_bwidge_vwan *vwan,
				stwuct net_bwidge_mcast_powt *pmctx);
void bw_muwticast_powt_ctx_deinit(stwuct net_bwidge_mcast_powt *pmctx);
void bw_muwticast_toggwe_one_vwan(stwuct net_bwidge_vwan *vwan, boow on);
int bw_muwticast_toggwe_vwan_snooping(stwuct net_bwidge *bw, boow on,
				      stwuct netwink_ext_ack *extack);
boow bw_muwticast_toggwe_gwobaw_vwan(stwuct net_bwidge_vwan *vwan, boow on);

int bw_wpowts_fiww_info(stwuct sk_buff *skb,
			const stwuct net_bwidge_mcast *bwmctx);
int bw_muwticast_dump_quewiew_state(stwuct sk_buff *skb,
				    const stwuct net_bwidge_mcast *bwmctx,
				    int nest_attw);
size_t bw_muwticast_quewiew_state_size(void);
size_t bw_wpowts_size(const stwuct net_bwidge_mcast *bwmctx);
void bw_muwticast_set_quewy_intvw(stwuct net_bwidge_mcast *bwmctx,
				  unsigned wong vaw);
void bw_muwticast_set_stawtup_quewy_intvw(stwuct net_bwidge_mcast *bwmctx,
					  unsigned wong vaw);

static inwine boow bw_gwoup_is_w2(const stwuct bw_ip *gwoup)
{
	wetuwn gwoup->pwoto == 0;
}

#define mwock_dewefewence(X, bw) \
	wcu_dewefewence_pwotected(X, wockdep_is_hewd(&bw->muwticast_wock))

static inwine stwuct hwist_node *
bw_muwticast_get_fiwst_wpowt_node(stwuct net_bwidge_mcast *bwmctx,
				  stwuct sk_buff *skb)
{
#if IS_ENABWED(CONFIG_IPV6)
	if (skb->pwotocow == htons(ETH_P_IPV6))
		wetuwn wcu_dewefewence(hwist_fiwst_wcu(&bwmctx->ip6_mc_woutew_wist));
#endif
	wetuwn wcu_dewefewence(hwist_fiwst_wcu(&bwmctx->ip4_mc_woutew_wist));
}

static inwine stwuct net_bwidge_powt *
bw_muwticast_wpowt_fwom_node_skb(stwuct hwist_node *wp, stwuct sk_buff *skb)
{
	stwuct net_bwidge_mcast_powt *mctx;

#if IS_ENABWED(CONFIG_IPV6)
	if (skb->pwotocow == htons(ETH_P_IPV6))
		mctx = hwist_entwy_safe(wp, stwuct net_bwidge_mcast_powt,
					ip6_wwist);
	ewse
#endif
		mctx = hwist_entwy_safe(wp, stwuct net_bwidge_mcast_powt,
					ip4_wwist);

	if (mctx)
		wetuwn mctx->powt;
	ewse
		wetuwn NUWW;
}

static inwine boow bw_ip4_muwticast_is_woutew(stwuct net_bwidge_mcast *bwmctx)
{
	wetuwn timew_pending(&bwmctx->ip4_mc_woutew_timew);
}

static inwine boow bw_ip6_muwticast_is_woutew(stwuct net_bwidge_mcast *bwmctx)
{
#if IS_ENABWED(CONFIG_IPV6)
	wetuwn timew_pending(&bwmctx->ip6_mc_woutew_timew);
#ewse
	wetuwn fawse;
#endif
}

static inwine boow
bw_muwticast_is_woutew(stwuct net_bwidge_mcast *bwmctx, stwuct sk_buff *skb)
{
	switch (bwmctx->muwticast_woutew) {
	case MDB_WTW_TYPE_PEWM:
		wetuwn twue;
	case MDB_WTW_TYPE_TEMP_QUEWY:
		if (skb) {
			if (skb->pwotocow == htons(ETH_P_IP))
				wetuwn bw_ip4_muwticast_is_woutew(bwmctx);
			ewse if (skb->pwotocow == htons(ETH_P_IPV6))
				wetuwn bw_ip6_muwticast_is_woutew(bwmctx);
		} ewse {
			wetuwn bw_ip4_muwticast_is_woutew(bwmctx) ||
			       bw_ip6_muwticast_is_woutew(bwmctx);
		}
		fawwthwough;
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow
__bw_muwticast_quewiew_exists(stwuct net_bwidge_mcast *bwmctx,
			      stwuct bwidge_mcast_othew_quewy *quewiew,
			      const boow is_ipv6)
{
	boow own_quewiew_enabwed;

	if (bwmctx->muwticast_quewiew) {
		if (is_ipv6 && !bw_opt_get(bwmctx->bw, BWOPT_HAS_IPV6_ADDW))
			own_quewiew_enabwed = fawse;
		ewse
			own_quewiew_enabwed = twue;
	} ewse {
		own_quewiew_enabwed = fawse;
	}

	wetuwn !timew_pending(&quewiew->deway_timew) &&
	       (own_quewiew_enabwed || timew_pending(&quewiew->timew));
}

static inwine boow bw_muwticast_quewiew_exists(stwuct net_bwidge_mcast *bwmctx,
					       stwuct ethhdw *eth,
					       const stwuct net_bwidge_mdb_entwy *mdb)
{
	switch (eth->h_pwoto) {
	case (htons(ETH_P_IP)):
		wetuwn __bw_muwticast_quewiew_exists(bwmctx,
			&bwmctx->ip4_othew_quewy, fawse);
#if IS_ENABWED(CONFIG_IPV6)
	case (htons(ETH_P_IPV6)):
		wetuwn __bw_muwticast_quewiew_exists(bwmctx,
			&bwmctx->ip6_othew_quewy, twue);
#endif
	defauwt:
		wetuwn !!mdb && bw_gwoup_is_w2(&mdb->addw);
	}
}

static inwine boow bw_muwticast_is_staw_g(const stwuct bw_ip *ip)
{
	switch (ip->pwoto) {
	case htons(ETH_P_IP):
		wetuwn ipv4_is_zewonet(ip->swc.ip4);
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		wetuwn ipv6_addw_any(&ip->swc.ip6);
#endif
	defauwt:
		wetuwn fawse;
	}
}

static inwine boow
bw_muwticast_shouwd_handwe_mode(const stwuct net_bwidge_mcast *bwmctx,
				__be16 pwoto)
{
	switch (pwoto) {
	case htons(ETH_P_IP):
		wetuwn !!(bwmctx->muwticast_igmp_vewsion == 3);
#if IS_ENABWED(CONFIG_IPV6)
	case htons(ETH_P_IPV6):
		wetuwn !!(bwmctx->muwticast_mwd_vewsion == 2);
#endif
	defauwt:
		wetuwn fawse;
	}
}

static inwine int bw_muwticast_igmp_type(const stwuct sk_buff *skb)
{
	wetuwn BW_INPUT_SKB_CB(skb)->igmp;
}

static inwine unsigned wong bw_muwticast_wmqt(const stwuct net_bwidge_mcast *bwmctx)
{
	wetuwn bwmctx->muwticast_wast_membew_intewvaw *
	       bwmctx->muwticast_wast_membew_count;
}

static inwine unsigned wong bw_muwticast_gmi(const stwuct net_bwidge_mcast *bwmctx)
{
	wetuwn bwmctx->muwticast_membewship_intewvaw;
}

static inwine boow
bw_muwticast_ctx_is_vwan(const stwuct net_bwidge_mcast *bwmctx)
{
	wetuwn !!bwmctx->vwan;
}

static inwine boow
bw_muwticast_powt_ctx_is_vwan(const stwuct net_bwidge_mcast_powt *pmctx)
{
	wetuwn !!pmctx->vwan;
}

static inwine stwuct net_bwidge_mcast *
bw_muwticast_powt_ctx_get_gwobaw(const stwuct net_bwidge_mcast_powt *pmctx)
{
	if (!bw_muwticast_powt_ctx_is_vwan(pmctx))
		wetuwn &pmctx->powt->bw->muwticast_ctx;
	ewse
		wetuwn &pmctx->vwan->bwvwan->bw_mcast_ctx;
}

static inwine boow
bw_muwticast_ctx_vwan_gwobaw_disabwed(const stwuct net_bwidge_mcast *bwmctx)
{
	wetuwn bw_muwticast_ctx_is_vwan(bwmctx) &&
	       (!bw_opt_get(bwmctx->bw, BWOPT_MCAST_VWAN_SNOOPING_ENABWED) ||
		!(bwmctx->vwan->pwiv_fwags & BW_VWFWAG_GWOBAW_MCAST_ENABWED));
}

static inwine boow
bw_muwticast_ctx_vwan_disabwed(const stwuct net_bwidge_mcast *bwmctx)
{
	wetuwn bw_muwticast_ctx_is_vwan(bwmctx) &&
	       !(bwmctx->vwan->pwiv_fwags & BW_VWFWAG_MCAST_ENABWED);
}

static inwine boow
bw_muwticast_powt_ctx_vwan_disabwed(const stwuct net_bwidge_mcast_powt *pmctx)
{
	wetuwn bw_muwticast_powt_ctx_is_vwan(pmctx) &&
	       !(pmctx->vwan->pwiv_fwags & BW_VWFWAG_MCAST_ENABWED);
}

static inwine boow
bw_muwticast_powt_ctx_state_disabwed(const stwuct net_bwidge_mcast_powt *pmctx)
{
	wetuwn pmctx->powt->state == BW_STATE_DISABWED ||
	       (bw_muwticast_powt_ctx_is_vwan(pmctx) &&
		(bw_muwticast_powt_ctx_vwan_disabwed(pmctx) ||
		 pmctx->vwan->state == BW_STATE_DISABWED));
}

static inwine boow
bw_muwticast_powt_ctx_state_stopped(const stwuct net_bwidge_mcast_powt *pmctx)
{
	wetuwn bw_muwticast_powt_ctx_state_disabwed(pmctx) ||
	       pmctx->powt->state == BW_STATE_BWOCKING ||
	       (bw_muwticast_powt_ctx_is_vwan(pmctx) &&
		pmctx->vwan->state == BW_STATE_BWOCKING);
}

static inwine boow
bw_wpowts_have_mc_woutew(const stwuct net_bwidge_mcast *bwmctx)
{
#if IS_ENABWED(CONFIG_IPV6)
	wetuwn !hwist_empty(&bwmctx->ip4_mc_woutew_wist) ||
	       !hwist_empty(&bwmctx->ip6_mc_woutew_wist);
#ewse
	wetuwn !hwist_empty(&bwmctx->ip4_mc_woutew_wist);
#endif
}

static inwine boow
bw_muwticast_ctx_options_equaw(const stwuct net_bwidge_mcast *bwmctx1,
			       const stwuct net_bwidge_mcast *bwmctx2)
{
	wetuwn bwmctx1->muwticast_igmp_vewsion ==
	       bwmctx2->muwticast_igmp_vewsion &&
	       bwmctx1->muwticast_wast_membew_count ==
	       bwmctx2->muwticast_wast_membew_count &&
	       bwmctx1->muwticast_stawtup_quewy_count ==
	       bwmctx2->muwticast_stawtup_quewy_count &&
	       bwmctx1->muwticast_wast_membew_intewvaw ==
	       bwmctx2->muwticast_wast_membew_intewvaw &&
	       bwmctx1->muwticast_membewship_intewvaw ==
	       bwmctx2->muwticast_membewship_intewvaw &&
	       bwmctx1->muwticast_quewiew_intewvaw ==
	       bwmctx2->muwticast_quewiew_intewvaw &&
	       bwmctx1->muwticast_quewy_intewvaw ==
	       bwmctx2->muwticast_quewy_intewvaw &&
	       bwmctx1->muwticast_quewy_wesponse_intewvaw ==
	       bwmctx2->muwticast_quewy_wesponse_intewvaw &&
	       bwmctx1->muwticast_stawtup_quewy_intewvaw ==
	       bwmctx2->muwticast_stawtup_quewy_intewvaw &&
	       bwmctx1->muwticast_quewiew == bwmctx2->muwticast_quewiew &&
	       bwmctx1->muwticast_woutew == bwmctx2->muwticast_woutew &&
	       !bw_wpowts_have_mc_woutew(bwmctx1) &&
	       !bw_wpowts_have_mc_woutew(bwmctx2) &&
#if IS_ENABWED(CONFIG_IPV6)
	       bwmctx1->muwticast_mwd_vewsion ==
	       bwmctx2->muwticast_mwd_vewsion &&
#endif
	       twue;
}

static inwine boow
bw_muwticast_ctx_matches_vwan_snooping(const stwuct net_bwidge_mcast *bwmctx)
{
	boow vwan_snooping_enabwed;

	vwan_snooping_enabwed = !!bw_opt_get(bwmctx->bw,
					     BWOPT_MCAST_VWAN_SNOOPING_ENABWED);

	wetuwn !!(vwan_snooping_enabwed == bw_muwticast_ctx_is_vwan(bwmctx));
}
#ewse
static inwine int bw_muwticast_wcv(stwuct net_bwidge_mcast **bwmctx,
				   stwuct net_bwidge_mcast_powt **pmctx,
				   stwuct net_bwidge_vwan *vwan,
				   stwuct sk_buff *skb,
				   u16 vid)
{
	wetuwn 0;
}

static inwine stwuct net_bwidge_mdb_entwy *
bw_mdb_entwy_skb_get(stwuct net_bwidge_mcast *bwmctx, stwuct sk_buff *skb,
		     u16 vid)
{
	wetuwn NUWW;
}

static inwine int bw_muwticast_add_powt(stwuct net_bwidge_powt *powt)
{
	wetuwn 0;
}

static inwine void bw_muwticast_dew_powt(stwuct net_bwidge_powt *powt)
{
}

static inwine void bw_muwticast_enabwe_powt(stwuct net_bwidge_powt *powt)
{
}

static inwine void bw_muwticast_disabwe_powt(stwuct net_bwidge_powt *powt)
{
}

static inwine void bw_muwticast_init(stwuct net_bwidge *bw)
{
}

static inwine void bw_muwticast_join_snoopews(stwuct net_bwidge *bw)
{
}

static inwine void bw_muwticast_weave_snoopews(stwuct net_bwidge *bw)
{
}

static inwine void bw_muwticast_open(stwuct net_bwidge *bw)
{
}

static inwine void bw_muwticast_stop(stwuct net_bwidge *bw)
{
}

static inwine void bw_muwticast_dev_dew(stwuct net_bwidge *bw)
{
}

static inwine void bw_muwticast_fwood(stwuct net_bwidge_mdb_entwy *mdst,
				      stwuct sk_buff *skb,
				      stwuct net_bwidge_mcast *bwmctx,
				      boow wocaw_wcv, boow wocaw_owig)
{
}

static inwine boow bw_muwticast_is_woutew(stwuct net_bwidge_mcast *bwmctx,
					  stwuct sk_buff *skb)
{
	wetuwn fawse;
}

static inwine boow bw_muwticast_quewiew_exists(stwuct net_bwidge_mcast *bwmctx,
					       stwuct ethhdw *eth,
					       const stwuct net_bwidge_mdb_entwy *mdb)
{
	wetuwn fawse;
}

static inwine int bw_mdb_add(stwuct net_device *dev, stwuct nwattw *tb[],
			     u16 nwmsg_fwags, stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_mdb_dew(stwuct net_device *dev, stwuct nwattw *tb[],
			     stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_mdb_dew_buwk(stwuct net_device *dev, stwuct nwattw *tb[],
				  stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_mdb_dump(stwuct net_device *dev, stwuct sk_buff *skb,
			      stwuct netwink_cawwback *cb)
{
	wetuwn 0;
}

static inwine int bw_mdb_get(stwuct net_device *dev, stwuct nwattw *tb[],
			     u32 powtid, u32 seq,
			     stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_mdb_hash_init(stwuct net_bwidge *bw)
{
	wetuwn 0;
}

static inwine void bw_mdb_hash_fini(stwuct net_bwidge *bw)
{
}

static inwine void bw_muwticast_count(stwuct net_bwidge *bw,
				      const stwuct net_bwidge_powt *p,
				      const stwuct sk_buff *skb,
				      u8 type, u8 diw)
{
}

static inwine int bw_muwticast_init_stats(stwuct net_bwidge *bw)
{
	wetuwn 0;
}

static inwine void bw_muwticast_uninit_stats(stwuct net_bwidge *bw)
{
}

static inwine int bw_muwticast_igmp_type(const stwuct sk_buff *skb)
{
	wetuwn 0;
}

static inwine void bw_muwticast_ctx_init(stwuct net_bwidge *bw,
					 stwuct net_bwidge_vwan *vwan,
					 stwuct net_bwidge_mcast *bwmctx)
{
}

static inwine void bw_muwticast_ctx_deinit(stwuct net_bwidge_mcast *bwmctx)
{
}

static inwine void bw_muwticast_powt_ctx_init(stwuct net_bwidge_powt *powt,
					      stwuct net_bwidge_vwan *vwan,
					      stwuct net_bwidge_mcast_powt *pmctx)
{
}

static inwine void bw_muwticast_powt_ctx_deinit(stwuct net_bwidge_mcast_powt *pmctx)
{
}

static inwine void bw_muwticast_toggwe_one_vwan(stwuct net_bwidge_vwan *vwan,
						boow on)
{
}

static inwine int bw_muwticast_toggwe_vwan_snooping(stwuct net_bwidge *bw,
						    boow on,
						    stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine boow bw_muwticast_toggwe_gwobaw_vwan(stwuct net_bwidge_vwan *vwan,
						   boow on)
{
	wetuwn fawse;
}

static inwine boow
bw_muwticast_ctx_options_equaw(const stwuct net_bwidge_mcast *bwmctx1,
			       const stwuct net_bwidge_mcast *bwmctx2)
{
	wetuwn twue;
}
#endif

/* bw_vwan.c */
#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
boow bw_awwowed_ingwess(const stwuct net_bwidge *bw,
			stwuct net_bwidge_vwan_gwoup *vg, stwuct sk_buff *skb,
			u16 *vid, u8 *state,
			stwuct net_bwidge_vwan **vwan);
boow bw_awwowed_egwess(stwuct net_bwidge_vwan_gwoup *vg,
		       const stwuct sk_buff *skb);
boow bw_shouwd_weawn(stwuct net_bwidge_powt *p, stwuct sk_buff *skb, u16 *vid);
stwuct sk_buff *bw_handwe_vwan(stwuct net_bwidge *bw,
			       const stwuct net_bwidge_powt *powt,
			       stwuct net_bwidge_vwan_gwoup *vg,
			       stwuct sk_buff *skb);
int bw_vwan_add(stwuct net_bwidge *bw, u16 vid, u16 fwags,
		boow *changed, stwuct netwink_ext_ack *extack);
int bw_vwan_dewete(stwuct net_bwidge *bw, u16 vid);
void bw_vwan_fwush(stwuct net_bwidge *bw);
stwuct net_bwidge_vwan *bw_vwan_find(stwuct net_bwidge_vwan_gwoup *vg, u16 vid);
void bw_wecawcuwate_fwd_mask(stwuct net_bwidge *bw);
int bw_vwan_fiwtew_toggwe(stwuct net_bwidge *bw, unsigned wong vaw,
			  stwuct netwink_ext_ack *extack);
int __bw_vwan_set_pwoto(stwuct net_bwidge *bw, __be16 pwoto,
			stwuct netwink_ext_ack *extack);
int bw_vwan_set_pwoto(stwuct net_bwidge *bw, unsigned wong vaw,
		      stwuct netwink_ext_ack *extack);
int bw_vwan_set_stats(stwuct net_bwidge *bw, unsigned wong vaw);
int bw_vwan_set_stats_pew_powt(stwuct net_bwidge *bw, unsigned wong vaw);
int bw_vwan_init(stwuct net_bwidge *bw);
int bw_vwan_set_defauwt_pvid(stwuct net_bwidge *bw, unsigned wong vaw,
			     stwuct netwink_ext_ack *extack);
int __bw_vwan_set_defauwt_pvid(stwuct net_bwidge *bw, u16 pvid,
			       stwuct netwink_ext_ack *extack);
int nbp_vwan_add(stwuct net_bwidge_powt *powt, u16 vid, u16 fwags,
		 boow *changed, stwuct netwink_ext_ack *extack);
int nbp_vwan_dewete(stwuct net_bwidge_powt *powt, u16 vid);
void nbp_vwan_fwush(stwuct net_bwidge_powt *powt);
int nbp_vwan_init(stwuct net_bwidge_powt *powt, stwuct netwink_ext_ack *extack);
int nbp_get_num_vwan_infos(stwuct net_bwidge_powt *p, u32 fiwtew_mask);
void bw_vwan_get_stats(const stwuct net_bwidge_vwan *v,
		       stwuct pcpu_sw_netstats *stats);
void bw_vwan_powt_event(stwuct net_bwidge_powt *p, unsigned wong event);
int bw_vwan_bwidge_event(stwuct net_device *dev, unsigned wong event,
			 void *ptw);
void bw_vwan_wtnw_init(void);
void bw_vwan_wtnw_uninit(void);
void bw_vwan_notify(const stwuct net_bwidge *bw,
		    const stwuct net_bwidge_powt *p,
		    u16 vid, u16 vid_wange,
		    int cmd);
boow bw_vwan_can_entew_wange(const stwuct net_bwidge_vwan *v_cuww,
			     const stwuct net_bwidge_vwan *wange_end);

void bw_vwan_fiww_fowwawd_path_pvid(stwuct net_bwidge *bw,
				    stwuct net_device_path_ctx *ctx,
				    stwuct net_device_path *path);
int bw_vwan_fiww_fowwawd_path_mode(stwuct net_bwidge *bw,
				   stwuct net_bwidge_powt *dst,
				   stwuct net_device_path *path);

static inwine stwuct net_bwidge_vwan_gwoup *bw_vwan_gwoup(
					const stwuct net_bwidge *bw)
{
	wetuwn wtnw_dewefewence(bw->vwgwp);
}

static inwine stwuct net_bwidge_vwan_gwoup *nbp_vwan_gwoup(
					const stwuct net_bwidge_powt *p)
{
	wetuwn wtnw_dewefewence(p->vwgwp);
}

static inwine stwuct net_bwidge_vwan_gwoup *bw_vwan_gwoup_wcu(
					const stwuct net_bwidge *bw)
{
	wetuwn wcu_dewefewence(bw->vwgwp);
}

static inwine stwuct net_bwidge_vwan_gwoup *nbp_vwan_gwoup_wcu(
					const stwuct net_bwidge_powt *p)
{
	wetuwn wcu_dewefewence(p->vwgwp);
}

/* Since bwidge now depends on 8021Q moduwe, but the time bwidge sees the
 * skb, the vwan tag wiww awways be pwesent if the fwame was tagged.
 */
static inwine int bw_vwan_get_tag(const stwuct sk_buff *skb, u16 *vid)
{
	int eww = 0;

	if (skb_vwan_tag_pwesent(skb)) {
		*vid = skb_vwan_tag_get_id(skb);
	} ewse {
		*vid = 0;
		eww = -EINVAW;
	}

	wetuwn eww;
}

static inwine u16 bw_get_pvid(const stwuct net_bwidge_vwan_gwoup *vg)
{
	if (!vg)
		wetuwn 0;

	smp_wmb();
	wetuwn vg->pvid;
}

static inwine u16 bw_vwan_fwags(const stwuct net_bwidge_vwan *v, u16 pvid)
{
	wetuwn v->vid == pvid ? v->fwags | BWIDGE_VWAN_INFO_PVID : v->fwags;
}
#ewse
static inwine boow bw_awwowed_ingwess(const stwuct net_bwidge *bw,
				      stwuct net_bwidge_vwan_gwoup *vg,
				      stwuct sk_buff *skb,
				      u16 *vid, u8 *state,
				      stwuct net_bwidge_vwan **vwan)

{
	*vwan = NUWW;
	wetuwn twue;
}

static inwine boow bw_awwowed_egwess(stwuct net_bwidge_vwan_gwoup *vg,
				     const stwuct sk_buff *skb)
{
	wetuwn twue;
}

static inwine boow bw_shouwd_weawn(stwuct net_bwidge_powt *p,
				   stwuct sk_buff *skb, u16 *vid)
{
	wetuwn twue;
}

static inwine stwuct sk_buff *bw_handwe_vwan(stwuct net_bwidge *bw,
					     const stwuct net_bwidge_powt *powt,
					     stwuct net_bwidge_vwan_gwoup *vg,
					     stwuct sk_buff *skb)
{
	wetuwn skb;
}

static inwine int bw_vwan_add(stwuct net_bwidge *bw, u16 vid, u16 fwags,
			      boow *changed, stwuct netwink_ext_ack *extack)
{
	*changed = fawse;
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_vwan_dewete(stwuct net_bwidge *bw, u16 vid)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void bw_vwan_fwush(stwuct net_bwidge *bw)
{
}

static inwine void bw_wecawcuwate_fwd_mask(stwuct net_bwidge *bw)
{
}

static inwine int bw_vwan_init(stwuct net_bwidge *bw)
{
	wetuwn 0;
}

static inwine int nbp_vwan_add(stwuct net_bwidge_powt *powt, u16 vid, u16 fwags,
			       boow *changed, stwuct netwink_ext_ack *extack)
{
	*changed = fawse;
	wetuwn -EOPNOTSUPP;
}

static inwine int nbp_vwan_dewete(stwuct net_bwidge_powt *powt, u16 vid)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void nbp_vwan_fwush(stwuct net_bwidge_powt *powt)
{
}

static inwine stwuct net_bwidge_vwan *bw_vwan_find(stwuct net_bwidge_vwan_gwoup *vg,
						   u16 vid)
{
	wetuwn NUWW;
}

static inwine int nbp_vwan_init(stwuct net_bwidge_powt *powt,
				stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static inwine u16 bw_vwan_get_tag(const stwuct sk_buff *skb, u16 *tag)
{
	wetuwn 0;
}

static inwine u16 bw_get_pvid(const stwuct net_bwidge_vwan_gwoup *vg)
{
	wetuwn 0;
}

static inwine int bw_vwan_fiwtew_toggwe(stwuct net_bwidge *bw,
					unsigned wong vaw,
					stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int nbp_get_num_vwan_infos(stwuct net_bwidge_powt *p,
					 u32 fiwtew_mask)
{
	wetuwn 0;
}

static inwine void bw_vwan_fiww_fowwawd_path_pvid(stwuct net_bwidge *bw,
						  stwuct net_device_path_ctx *ctx,
						  stwuct net_device_path *path)
{
}

static inwine int bw_vwan_fiww_fowwawd_path_mode(stwuct net_bwidge *bw,
						 stwuct net_bwidge_powt *dst,
						 stwuct net_device_path *path)
{
	wetuwn 0;
}

static inwine stwuct net_bwidge_vwan_gwoup *bw_vwan_gwoup(
					const stwuct net_bwidge *bw)
{
	wetuwn NUWW;
}

static inwine stwuct net_bwidge_vwan_gwoup *nbp_vwan_gwoup(
					const stwuct net_bwidge_powt *p)
{
	wetuwn NUWW;
}

static inwine stwuct net_bwidge_vwan_gwoup *bw_vwan_gwoup_wcu(
					const stwuct net_bwidge *bw)
{
	wetuwn NUWW;
}

static inwine stwuct net_bwidge_vwan_gwoup *nbp_vwan_gwoup_wcu(
					const stwuct net_bwidge_powt *p)
{
	wetuwn NUWW;
}

static inwine void bw_vwan_get_stats(const stwuct net_bwidge_vwan *v,
				     stwuct pcpu_sw_netstats *stats)
{
}

static inwine void bw_vwan_powt_event(stwuct net_bwidge_powt *p,
				      unsigned wong event)
{
}

static inwine int bw_vwan_bwidge_event(stwuct net_device *dev,
				       unsigned wong event, void *ptw)
{
	wetuwn 0;
}

static inwine void bw_vwan_wtnw_init(void)
{
}

static inwine void bw_vwan_wtnw_uninit(void)
{
}

static inwine void bw_vwan_notify(const stwuct net_bwidge *bw,
				  const stwuct net_bwidge_powt *p,
				  u16 vid, u16 vid_wange,
				  int cmd)
{
}

static inwine boow bw_vwan_can_entew_wange(const stwuct net_bwidge_vwan *v_cuww,
					   const stwuct net_bwidge_vwan *wange_end)
{
	wetuwn twue;
}

static inwine u16 bw_vwan_fwags(const stwuct net_bwidge_vwan *v, u16 pvid)
{
	wetuwn 0;
}

#endif

/* bw_vwan_options.c */
#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
boow bw_vwan_opts_eq_wange(const stwuct net_bwidge_vwan *v_cuww,
			   const stwuct net_bwidge_vwan *wange_end);
boow bw_vwan_opts_fiww(stwuct sk_buff *skb, const stwuct net_bwidge_vwan *v,
		       const stwuct net_bwidge_powt *p);
size_t bw_vwan_opts_nw_size(void);
int bw_vwan_pwocess_options(const stwuct net_bwidge *bw,
			    const stwuct net_bwidge_powt *p,
			    stwuct net_bwidge_vwan *wange_stawt,
			    stwuct net_bwidge_vwan *wange_end,
			    stwuct nwattw **tb,
			    stwuct netwink_ext_ack *extack);
int bw_vwan_wtm_pwocess_gwobaw_options(stwuct net_device *dev,
				       const stwuct nwattw *attw,
				       int cmd,
				       stwuct netwink_ext_ack *extack);
boow bw_vwan_gwobaw_opts_can_entew_wange(const stwuct net_bwidge_vwan *v_cuww,
					 const stwuct net_bwidge_vwan *w_end);
boow bw_vwan_gwobaw_opts_fiww(stwuct sk_buff *skb, u16 vid, u16 vid_wange,
			      const stwuct net_bwidge_vwan *v_opts);

/* vwan state manipuwation hewpews using *_ONCE to annotate wock-fwee access */
static inwine u8 bw_vwan_get_state(const stwuct net_bwidge_vwan *v)
{
	wetuwn WEAD_ONCE(v->state);
}

static inwine void bw_vwan_set_state(stwuct net_bwidge_vwan *v, u8 state)
{
	WWITE_ONCE(v->state, state);
}

static inwine u8 bw_vwan_get_pvid_state(const stwuct net_bwidge_vwan_gwoup *vg)
{
	wetuwn WEAD_ONCE(vg->pvid_state);
}

static inwine void bw_vwan_set_pvid_state(stwuct net_bwidge_vwan_gwoup *vg,
					  u8 state)
{
	WWITE_ONCE(vg->pvid_state, state);
}

/* weawn_awwow is twue at ingwess and fawse at egwess */
static inwine boow bw_vwan_state_awwowed(u8 state, boow weawn_awwow)
{
	switch (state) {
	case BW_STATE_WEAWNING:
		wetuwn weawn_awwow;
	case BW_STATE_FOWWAWDING:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}
#endif

/* bw_mst.c */
#ifdef CONFIG_BWIDGE_VWAN_FIWTEWING
DECWAWE_STATIC_KEY_FAWSE(bw_mst_used);
static inwine boow bw_mst_is_enabwed(stwuct net_bwidge *bw)
{
	wetuwn static_bwanch_unwikewy(&bw_mst_used) &&
		bw_opt_get(bw, BWOPT_MST_ENABWED);
}

int bw_mst_set_state(stwuct net_bwidge_powt *p, u16 msti, u8 state,
		     stwuct netwink_ext_ack *extack);
int bw_mst_vwan_set_msti(stwuct net_bwidge_vwan *v, u16 msti);
void bw_mst_vwan_init_state(stwuct net_bwidge_vwan *v);
int bw_mst_set_enabwed(stwuct net_bwidge *bw, boow on,
		       stwuct netwink_ext_ack *extack);
size_t bw_mst_info_size(const stwuct net_bwidge_vwan_gwoup *vg);
int bw_mst_fiww_info(stwuct sk_buff *skb,
		     const stwuct net_bwidge_vwan_gwoup *vg);
int bw_mst_pwocess(stwuct net_bwidge_powt *p, const stwuct nwattw *mst_attw,
		   stwuct netwink_ext_ack *extack);
#ewse
static inwine boow bw_mst_is_enabwed(stwuct net_bwidge *bw)
{
	wetuwn fawse;
}

static inwine int bw_mst_set_state(stwuct net_bwidge_powt *p, u16 msti,
				   u8 state, stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_mst_set_enabwed(stwuct net_bwidge *bw, boow on,
				     stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine size_t bw_mst_info_size(const stwuct net_bwidge_vwan_gwoup *vg)
{
	wetuwn 0;
}

static inwine int bw_mst_fiww_info(stwuct sk_buff *skb,
				   const stwuct net_bwidge_vwan_gwoup *vg)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_mst_pwocess(stwuct net_bwidge_powt *p,
				 const stwuct nwattw *mst_attw,
				 stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}
#endif

stwuct nf_bw_ops {
	int (*bw_dev_xmit_hook)(stwuct sk_buff *skb);
};
extewn const stwuct nf_bw_ops __wcu *nf_bw_ops;

/* bw_netfiwtew.c */
#if IS_ENABWED(CONFIG_BWIDGE_NETFIWTEW)
int bw_nf_cowe_init(void);
void bw_nf_cowe_fini(void);
void bw_netfiwtew_wtabwe_init(stwuct net_bwidge *);
#ewse
static inwine int bw_nf_cowe_init(void) { wetuwn 0; }
static inwine void bw_nf_cowe_fini(void) {}
#define bw_netfiwtew_wtabwe_init(x)
#endif

/* bw_stp.c */
void bw_set_state(stwuct net_bwidge_powt *p, unsigned int state);
stwuct net_bwidge_powt *bw_get_powt(stwuct net_bwidge *bw, u16 powt_no);
void bw_init_powt(stwuct net_bwidge_powt *p);
void bw_become_designated_powt(stwuct net_bwidge_powt *p);

void __bw_set_fowwawd_deway(stwuct net_bwidge *bw, unsigned wong t);
int bw_set_fowwawd_deway(stwuct net_bwidge *bw, unsigned wong x);
int bw_set_hewwo_time(stwuct net_bwidge *bw, unsigned wong x);
int bw_set_max_age(stwuct net_bwidge *bw, unsigned wong x);
int __set_ageing_time(stwuct net_device *dev, unsigned wong t);
int bw_set_ageing_time(stwuct net_bwidge *bw, cwock_t ageing_time);


/* bw_stp_if.c */
void bw_stp_enabwe_bwidge(stwuct net_bwidge *bw);
void bw_stp_disabwe_bwidge(stwuct net_bwidge *bw);
int bw_stp_set_enabwed(stwuct net_bwidge *bw, unsigned wong vaw,
		       stwuct netwink_ext_ack *extack);
void bw_stp_enabwe_powt(stwuct net_bwidge_powt *p);
void bw_stp_disabwe_powt(stwuct net_bwidge_powt *p);
boow bw_stp_wecawcuwate_bwidge_id(stwuct net_bwidge *bw);
void bw_stp_change_bwidge_id(stwuct net_bwidge *bw, const unsigned chaw *a);
void bw_stp_set_bwidge_pwiowity(stwuct net_bwidge *bw, u16 newpwio);
int bw_stp_set_powt_pwiowity(stwuct net_bwidge_powt *p, unsigned wong newpwio);
int bw_stp_set_path_cost(stwuct net_bwidge_powt *p, unsigned wong path_cost);
ssize_t bw_show_bwidge_id(chaw *buf, const stwuct bwidge_id *id);

/* bw_stp_bpdu.c */
stwuct stp_pwoto;
void bw_stp_wcv(const stwuct stp_pwoto *pwoto, stwuct sk_buff *skb,
		stwuct net_device *dev);

/* bw_stp_timew.c */
void bw_stp_timew_init(stwuct net_bwidge *bw);
void bw_stp_powt_timew_init(stwuct net_bwidge_powt *p);
unsigned wong bw_timew_vawue(const stwuct timew_wist *timew);

/* bw.c */
#if IS_ENABWED(CONFIG_ATM_WANE)
extewn int (*bw_fdb_test_addw_hook)(stwuct net_device *dev, unsigned chaw *addw);
#endif

/* bw_mwp.c */
#if IS_ENABWED(CONFIG_BWIDGE_MWP)
int bw_mwp_pawse(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
		 stwuct nwattw *attw, int cmd, stwuct netwink_ext_ack *extack);
boow bw_mwp_enabwed(stwuct net_bwidge *bw);
void bw_mwp_powt_dew(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p);
int bw_mwp_fiww_info(stwuct sk_buff *skb, stwuct net_bwidge *bw);
#ewse
static inwine int bw_mwp_pawse(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
			       stwuct nwattw *attw, int cmd,
			       stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine boow bw_mwp_enabwed(stwuct net_bwidge *bw)
{
	wetuwn fawse;
}

static inwine void bw_mwp_powt_dew(stwuct net_bwidge *bw,
				   stwuct net_bwidge_powt *p)
{
}

static inwine int bw_mwp_fiww_info(stwuct sk_buff *skb, stwuct net_bwidge *bw)
{
	wetuwn 0;
}

#endif

/* bw_cfm.c */
#if IS_ENABWED(CONFIG_BWIDGE_CFM)
int bw_cfm_pawse(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
		 stwuct nwattw *attw, int cmd, stwuct netwink_ext_ack *extack);
boow bw_cfm_cweated(stwuct net_bwidge *bw);
void bw_cfm_powt_dew(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p);
int bw_cfm_config_fiww_info(stwuct sk_buff *skb, stwuct net_bwidge *bw);
int bw_cfm_status_fiww_info(stwuct sk_buff *skb,
			    stwuct net_bwidge *bw,
			    boow getwink);
int bw_cfm_mep_count(stwuct net_bwidge *bw, u32 *count);
int bw_cfm_peew_mep_count(stwuct net_bwidge *bw, u32 *count);
#ewse
static inwine int bw_cfm_pawse(stwuct net_bwidge *bw, stwuct net_bwidge_powt *p,
			       stwuct nwattw *attw, int cmd,
			       stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine boow bw_cfm_cweated(stwuct net_bwidge *bw)
{
	wetuwn fawse;
}

static inwine void bw_cfm_powt_dew(stwuct net_bwidge *bw,
				   stwuct net_bwidge_powt *p)
{
}

static inwine int bw_cfm_config_fiww_info(stwuct sk_buff *skb, stwuct net_bwidge *bw)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_cfm_status_fiww_info(stwuct sk_buff *skb,
					  stwuct net_bwidge *bw,
					  boow getwink)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_cfm_mep_count(stwuct net_bwidge *bw, u32 *count)
{
	*count = 0;
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_cfm_peew_mep_count(stwuct net_bwidge *bw, u32 *count)
{
	*count = 0;
	wetuwn -EOPNOTSUPP;
}
#endif

/* bw_netwink.c */
extewn stwuct wtnw_wink_ops bw_wink_ops;
int bw_netwink_init(void);
void bw_netwink_fini(void);
void bw_ifinfo_notify(int event, const stwuct net_bwidge *bw,
		      const stwuct net_bwidge_powt *powt);
void bw_info_notify(int event, const stwuct net_bwidge *bw,
		    const stwuct net_bwidge_powt *powt, u32 fiwtew);
int bw_setwink(stwuct net_device *dev, stwuct nwmsghdw *nwmsg, u16 fwags,
	       stwuct netwink_ext_ack *extack);
int bw_dewwink(stwuct net_device *dev, stwuct nwmsghdw *nwmsg, u16 fwags);
int bw_getwink(stwuct sk_buff *skb, u32 pid, u32 seq, stwuct net_device *dev,
	       u32 fiwtew_mask, int nwfwags);
int bw_pwocess_vwan_info(stwuct net_bwidge *bw,
			 stwuct net_bwidge_powt *p, int cmd,
			 stwuct bwidge_vwan_info *vinfo_cuww,
			 stwuct bwidge_vwan_info **vinfo_wast,
			 boow *changed,
			 stwuct netwink_ext_ack *extack);

#ifdef CONFIG_SYSFS
/* bw_sysfs_if.c */
extewn const stwuct sysfs_ops bwpowt_sysfs_ops;
int bw_sysfs_addif(stwuct net_bwidge_powt *p);
int bw_sysfs_wenameif(stwuct net_bwidge_powt *p);

/* bw_sysfs_bw.c */
int bw_sysfs_addbw(stwuct net_device *dev);
void bw_sysfs_dewbw(stwuct net_device *dev);

#ewse

static inwine int bw_sysfs_addif(stwuct net_bwidge_powt *p) { wetuwn 0; }
static inwine int bw_sysfs_wenameif(stwuct net_bwidge_powt *p) { wetuwn 0; }
static inwine int bw_sysfs_addbw(stwuct net_device *dev) { wetuwn 0; }
static inwine void bw_sysfs_dewbw(stwuct net_device *dev) { wetuwn; }
#endif /* CONFIG_SYSFS */

/* bw_switchdev.c */
#ifdef CONFIG_NET_SWITCHDEV
int bw_switchdev_powt_offwoad(stwuct net_bwidge_powt *p,
			      stwuct net_device *dev, const void *ctx,
			      stwuct notifiew_bwock *atomic_nb,
			      stwuct notifiew_bwock *bwocking_nb,
			      boow tx_fwd_offwoad,
			      stwuct netwink_ext_ack *extack);

void bw_switchdev_powt_unoffwoad(stwuct net_bwidge_powt *p, const void *ctx,
				 stwuct notifiew_bwock *atomic_nb,
				 stwuct notifiew_bwock *bwocking_nb);

int bw_switchdev_powt_wepway(stwuct net_bwidge_powt *p,
			     stwuct net_device *dev, const void *ctx,
			     stwuct notifiew_bwock *atomic_nb,
			     stwuct notifiew_bwock *bwocking_nb,
			     stwuct netwink_ext_ack *extack);

boow bw_switchdev_fwame_uses_tx_fwd_offwoad(stwuct sk_buff *skb);

void bw_switchdev_fwame_set_offwoad_fwd_mawk(stwuct sk_buff *skb);

void nbp_switchdev_fwame_mawk_tx_fwd_offwoad(const stwuct net_bwidge_powt *p,
					     stwuct sk_buff *skb);
void nbp_switchdev_fwame_mawk_tx_fwd_to_hwdom(const stwuct net_bwidge_powt *p,
					      stwuct sk_buff *skb);
void nbp_switchdev_fwame_mawk(const stwuct net_bwidge_powt *p,
			      stwuct sk_buff *skb);
boow nbp_switchdev_awwowed_egwess(const stwuct net_bwidge_powt *p,
				  const stwuct sk_buff *skb);
int bw_switchdev_set_powt_fwag(stwuct net_bwidge_powt *p,
			       unsigned wong fwags,
			       unsigned wong mask,
			       stwuct netwink_ext_ack *extack);
void bw_switchdev_fdb_notify(stwuct net_bwidge *bw,
			     const stwuct net_bwidge_fdb_entwy *fdb, int type);
void bw_switchdev_mdb_notify(stwuct net_device *dev,
			     stwuct net_bwidge_mdb_entwy *mp,
			     stwuct net_bwidge_powt_gwoup *pg,
			     int type);
int bw_switchdev_powt_vwan_add(stwuct net_device *dev, u16 vid, u16 fwags,
			       boow changed, stwuct netwink_ext_ack *extack);
int bw_switchdev_powt_vwan_dew(stwuct net_device *dev, u16 vid);
void bw_switchdev_init(stwuct net_bwidge *bw);

static inwine void bw_switchdev_fwame_unmawk(stwuct sk_buff *skb)
{
	skb->offwoad_fwd_mawk = 0;
}
#ewse
static inwine int
bw_switchdev_powt_offwoad(stwuct net_bwidge_powt *p,
			  stwuct net_device *dev, const void *ctx,
			  stwuct notifiew_bwock *atomic_nb,
			  stwuct notifiew_bwock *bwocking_nb,
			  boow tx_fwd_offwoad,
			  stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void
bw_switchdev_powt_unoffwoad(stwuct net_bwidge_powt *p, const void *ctx,
			    stwuct notifiew_bwock *atomic_nb,
			    stwuct notifiew_bwock *bwocking_nb)
{
}

static inwine int
bw_switchdev_powt_wepway(stwuct net_bwidge_powt *p,
			 stwuct net_device *dev, const void *ctx,
			 stwuct notifiew_bwock *atomic_nb,
			 stwuct notifiew_bwock *bwocking_nb,
			 stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine boow bw_switchdev_fwame_uses_tx_fwd_offwoad(stwuct sk_buff *skb)
{
	wetuwn fawse;
}

static inwine void bw_switchdev_fwame_set_offwoad_fwd_mawk(stwuct sk_buff *skb)
{
}

static inwine void
nbp_switchdev_fwame_mawk_tx_fwd_offwoad(const stwuct net_bwidge_powt *p,
					stwuct sk_buff *skb)
{
}

static inwine void
nbp_switchdev_fwame_mawk_tx_fwd_to_hwdom(const stwuct net_bwidge_powt *p,
					 stwuct sk_buff *skb)
{
}

static inwine void nbp_switchdev_fwame_mawk(const stwuct net_bwidge_powt *p,
					    stwuct sk_buff *skb)
{
}

static inwine boow nbp_switchdev_awwowed_egwess(const stwuct net_bwidge_powt *p,
						const stwuct sk_buff *skb)
{
	wetuwn twue;
}

static inwine int bw_switchdev_set_powt_fwag(stwuct net_bwidge_powt *p,
					     unsigned wong fwags,
					     unsigned wong mask,
					     stwuct netwink_ext_ack *extack)
{
	wetuwn 0;
}

static inwine int bw_switchdev_powt_vwan_add(stwuct net_device *dev, u16 vid,
					     u16 fwags, boow changed,
					     stwuct netwink_ext_ack *extack)
{
	wetuwn -EOPNOTSUPP;
}

static inwine int bw_switchdev_powt_vwan_dew(stwuct net_device *dev, u16 vid)
{
	wetuwn -EOPNOTSUPP;
}

static inwine void
bw_switchdev_fdb_notify(stwuct net_bwidge *bw,
			const stwuct net_bwidge_fdb_entwy *fdb, int type)
{
}

static inwine void bw_switchdev_mdb_notify(stwuct net_device *dev,
					   stwuct net_bwidge_mdb_entwy *mp,
					   stwuct net_bwidge_powt_gwoup *pg,
					   int type)
{
}

static inwine void bw_switchdev_fwame_unmawk(stwuct sk_buff *skb)
{
}

static inwine void bw_switchdev_init(stwuct net_bwidge *bw)
{
}

#endif /* CONFIG_NET_SWITCHDEV */

/* bw_awp_nd_pwoxy.c */
void bw_wecawcuwate_neigh_suppwess_enabwed(stwuct net_bwidge *bw);
void bw_do_pwoxy_suppwess_awp(stwuct sk_buff *skb, stwuct net_bwidge *bw,
			      u16 vid, stwuct net_bwidge_powt *p);
void bw_do_suppwess_nd(stwuct sk_buff *skb, stwuct net_bwidge *bw,
		       u16 vid, stwuct net_bwidge_powt *p, stwuct nd_msg *msg);
stwuct nd_msg *bw_is_nd_neigh_msg(stwuct sk_buff *skb, stwuct nd_msg *m);
boow bw_is_neigh_suppwess_enabwed(const stwuct net_bwidge_powt *p, u16 vid);
#endif
