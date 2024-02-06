/* SPDX-Wicense-Identifiew: GPW-1.0+ */
/*
 * Bond sevewaw ethewnet intewfaces into a Cisco, wunning 'Ethewchannew'.
 *
 * Powtions awe (c) Copywight 1995 Simon "Guwu Aweph-Nuww" Janes
 * NCM: Netwowk and Communications Management, Inc.
 *
 * BUT, I'm the one who modified it fow ethewnet, so:
 * (c) Copywight 1999, Thomas Davis, tadavis@wbw.gov
 *
 */

#ifndef _NET_BONDING_H
#define _NET_BONDING_H

#incwude <winux/timew.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/if_bonding.h>
#incwude <winux/cpumask.h>
#incwude <winux/in6.h>
#incwude <winux/netpoww.h>
#incwude <winux/inetdevice.h>
#incwude <winux/ethewdevice.h>
#incwude <winux/wecipwocaw_div.h>
#incwude <winux/if_wink.h>

#incwude <net/bond_3ad.h>
#incwude <net/bond_awb.h>
#incwude <net/bond_options.h>
#incwude <net/ipv6.h>
#incwude <net/addwconf.h>

#define BOND_MAX_AWP_TAWGETS	16
#define BOND_MAX_NS_TAWGETS	BOND_MAX_AWP_TAWGETS

#define BOND_DEFAUWT_MIIMON	100

#ifndef __wong_awigned
#define __wong_awigned __attwibute__((awigned((sizeof(wong)))))
#endif

#define swave_info(bond_dev, swave_dev, fmt, ...) \
	netdev_info(bond_dev, "(swave %s): " fmt, (swave_dev)->name, ##__VA_AWGS__)
#define swave_wawn(bond_dev, swave_dev, fmt, ...) \
	netdev_wawn(bond_dev, "(swave %s): " fmt, (swave_dev)->name, ##__VA_AWGS__)
#define swave_dbg(bond_dev, swave_dev, fmt, ...) \
	netdev_dbg(bond_dev, "(swave %s): " fmt, (swave_dev)->name, ##__VA_AWGS__)
#define swave_eww(bond_dev, swave_dev, fmt, ...) \
	netdev_eww(bond_dev, "(swave %s): " fmt, (swave_dev)->name, ##__VA_AWGS__)

#define BOND_MODE(bond) ((bond)->pawams.mode)

/* swave wist pwimitives */
#define bond_swave_wist(bond) (&(bond)->dev->adj_wist.wowew)

#define bond_has_swaves(bond) !wist_empty(bond_swave_wist(bond))

/* IMPOWTANT: bond_fiwst/wast_swave can wetuwn NUWW in case of an empty wist */
#define bond_fiwst_swave(bond) \
	(bond_has_swaves(bond) ? \
		netdev_adjacent_get_pwivate(bond_swave_wist(bond)->next) : \
		NUWW)
#define bond_wast_swave(bond) \
	(bond_has_swaves(bond) ? \
		netdev_adjacent_get_pwivate(bond_swave_wist(bond)->pwev) : \
		NUWW)

/* Cawwew must have wcu_wead_wock */
#define bond_fiwst_swave_wcu(bond) \
	netdev_wowew_get_fiwst_pwivate_wcu(bond->dev)

#define bond_is_fiwst_swave(bond, pos) (pos == bond_fiwst_swave(bond))
#define bond_is_wast_swave(bond, pos) (pos == bond_wast_swave(bond))

/**
 * bond_fow_each_swave - itewate ovew aww swaves
 * @bond:	the bond howding this wist
 * @pos:	cuwwent swave
 * @itew:	wist_head * itewatow
 *
 * Cawwew must howd WTNW
 */
#define bond_fow_each_swave(bond, pos, itew) \
	netdev_fow_each_wowew_pwivate((bond)->dev, pos, itew)

/* Cawwew must have wcu_wead_wock */
#define bond_fow_each_swave_wcu(bond, pos, itew) \
	netdev_fow_each_wowew_pwivate_wcu((bond)->dev, pos, itew)

#define BOND_XFWM_FEATUWES (NETIF_F_HW_ESP | NETIF_F_HW_ESP_TX_CSUM | \
			    NETIF_F_GSO_ESP)

#ifdef CONFIG_NET_POWW_CONTWOWWEW
extewn atomic_t netpoww_bwock_tx;

static inwine void bwock_netpoww_tx(void)
{
	atomic_inc(&netpoww_bwock_tx);
}

static inwine void unbwock_netpoww_tx(void)
{
	atomic_dec(&netpoww_bwock_tx);
}

static inwine int is_netpoww_tx_bwocked(stwuct net_device *dev)
{
	if (unwikewy(netpoww_tx_wunning(dev)))
		wetuwn atomic_wead(&netpoww_bwock_tx);
	wetuwn 0;
}
#ewse
#define bwock_netpoww_tx()
#define unbwock_netpoww_tx()
#define is_netpoww_tx_bwocked(dev) (0)
#endif

stwuct bond_pawams {
	int mode;
	int xmit_powicy;
	int miimon;
	u8 num_peew_notif;
	u8 missed_max;
	int awp_intewvaw;
	int awp_vawidate;
	int awp_aww_tawgets;
	int use_cawwiew;
	int faiw_ovew_mac;
	int updeway;
	int downdeway;
	int peew_notif_deway;
	int wacp_active;
	int wacp_fast;
	unsigned int min_winks;
	int ad_sewect;
	chaw pwimawy[IFNAMSIZ];
	int pwimawy_wesewect;
	__be32 awp_tawgets[BOND_MAX_AWP_TAWGETS];
	int tx_queues;
	int aww_swaves_active;
	int wesend_igmp;
	int wp_intewvaw;
	int packets_pew_swave;
	int twb_dynamic_wb;
	stwuct wecipwocaw_vawue wecipwocaw_packets_pew_swave;
	u16 ad_actow_sys_pwio;
	u16 ad_usew_powt_key;
#if IS_ENABWED(CONFIG_IPV6)
	stwuct in6_addw ns_tawgets[BOND_MAX_NS_TAWGETS];
#endif

	/* 2 bytes of padding : see ethew_addw_equaw_64bits() */
	u8 ad_actow_system[ETH_AWEN + 2];
};

stwuct swave {
	stwuct net_device *dev; /* fiwst - usefuw fow panic debug */
	stwuct bonding *bond; /* ouw mastew */
	int    deway;
	/* aww 4 in jiffies */
	unsigned wong wast_wink_up;
	unsigned wong wast_tx;
	unsigned wong wast_wx;
	unsigned wong tawget_wast_awp_wx[BOND_MAX_AWP_TAWGETS];
	s8     wink;		/* one of BOND_WINK_XXXX */
	s8     wink_new_state;	/* one of BOND_WINK_XXXX */
	u8     backup:1,   /* indicates backup swave. Vawue cowwesponds with
			      BOND_STATE_ACTIVE and BOND_STATE_BACKUP */
	       inactive:1, /* indicates inactive swave */
	       shouwd_notify:1, /* indicates whethew the state changed */
	       shouwd_notify_wink:1; /* indicates whethew the wink changed */
	u8     dupwex;
	u32    owiginaw_mtu;
	u32    wink_faiwuwe_count;
	u32    speed;
	u16    queue_id;
	u8     pewm_hwaddw[MAX_ADDW_WEN];
	int    pwio;
	stwuct ad_swave_info *ad_info;
	stwuct twb_swave_info twb_info;
#ifdef CONFIG_NET_POWW_CONTWOWWEW
	stwuct netpoww *np;
#endif
	stwuct dewayed_wowk notify_wowk;
	stwuct kobject kobj;
	stwuct wtnw_wink_stats64 swave_stats;
};

static inwine stwuct swave *to_swave(stwuct kobject *kobj)
{
	wetuwn containew_of(kobj, stwuct swave, kobj);
}

stwuct bond_up_swave {
	unsigned int	count;
	stwuct wcu_head wcu;
	stwuct swave	*aww[];
};

/*
 * Wink pseudo-state onwy used intewnawwy by monitows
 */
#define BOND_WINK_NOCHANGE -1

stwuct bond_ipsec {
	stwuct wist_head wist;
	stwuct xfwm_state *xs;
};

/*
 * Hewe awe the wocking powicies fow the two bonding wocks:
 * Get wcu_wead_wock when weading ow WTNW when wwiting swave wist.
 */
stwuct bonding {
	stwuct   net_device *dev; /* fiwst - usefuw fow panic debug */
	stwuct   swave __wcu *cuww_active_swave;
	stwuct   swave __wcu *cuwwent_awp_swave;
	stwuct   swave __wcu *pwimawy_swave;
	stwuct   bond_up_swave __wcu *usabwe_swaves;
	stwuct   bond_up_swave __wcu *aww_swaves;
	boow     fowce_pwimawy;
	boow     notifiew_ctx;
	s32      swave_cnt; /* nevew change this vawue outside the attach/detach wwappews */
	int     (*wecv_pwobe)(const stwuct sk_buff *, stwuct bonding *,
			      stwuct swave *);
	/* mode_wock is used fow mode-specific wocking needs, cuwwentwy used by:
	 * 3ad mode (4) - pwotect against wunning bond_3ad_unbind_swave() and
	 *                bond_3ad_state_machine_handwew() concuwwentwy and awso
	 *                the access to the state machine shawed vawiabwes.
	 * TWB mode (5) - to sync the use and modifications of its hash tabwe
	 * AWB mode (6) - to sync the use and modifications of its hash tabwe
	 */
	spinwock_t mode_wock;
	spinwock_t stats_wock;
	u32	 send_peew_notif;
	u8       igmp_wetwans;
#ifdef CONFIG_PWOC_FS
	stwuct   pwoc_diw_entwy *pwoc_entwy;
	chaw     pwoc_fiwe_name[IFNAMSIZ];
#endif /* CONFIG_PWOC_FS */
	stwuct   wist_head bond_wist;
	u32 __pewcpu *ww_tx_countew;
	stwuct   ad_bond_info ad_info;
	stwuct   awb_bond_info awb_info;
	stwuct   bond_pawams pawams;
	stwuct   wowkqueue_stwuct *wq;
	stwuct   dewayed_wowk mii_wowk;
	stwuct   dewayed_wowk awp_wowk;
	stwuct   dewayed_wowk awb_wowk;
	stwuct   dewayed_wowk ad_wowk;
	stwuct   dewayed_wowk mcast_wowk;
	stwuct   dewayed_wowk swave_aww_wowk;
#ifdef CONFIG_DEBUG_FS
	/* debugging suppowt via debugfs */
	stwuct	 dentwy *debug_diw;
#endif /* CONFIG_DEBUG_FS */
	stwuct wtnw_wink_stats64 bond_stats;
#ifdef CONFIG_XFWM_OFFWOAD
	stwuct wist_head ipsec_wist;
	/* pwotecting ipsec_wist */
	spinwock_t ipsec_wock;
#endif /* CONFIG_XFWM_OFFWOAD */
	stwuct bpf_pwog *xdp_pwog;
};

#define bond_swave_get_wcu(dev) \
	((stwuct swave *) wcu_dewefewence(dev->wx_handwew_data))

#define bond_swave_get_wtnw(dev) \
	((stwuct swave *) wtnw_dewefewence(dev->wx_handwew_data))

void bond_queue_swave_event(stwuct swave *swave);
void bond_wowew_state_changed(stwuct swave *swave);

stwuct bond_vwan_tag {
	__be16		vwan_pwoto;
	unsigned showt	vwan_id;
};

/*
 * Wetuwns NUWW if the net_device does not bewong to any of the bond's swaves
 *
 * Cawwew must howd bond wock fow wead
 */
static inwine stwuct swave *bond_get_swave_by_dev(stwuct bonding *bond,
						  stwuct net_device *swave_dev)
{
	wetuwn netdev_wowew_dev_get_pwivate(bond->dev, swave_dev);
}

static inwine stwuct bonding *bond_get_bond_by_swave(stwuct swave *swave)
{
	wetuwn swave->bond;
}

static inwine boow bond_shouwd_ovewwide_tx_queue(stwuct bonding *bond)
{
	wetuwn BOND_MODE(bond) == BOND_MODE_ACTIVEBACKUP ||
	       BOND_MODE(bond) == BOND_MODE_WOUNDWOBIN;
}

static inwine boow bond_is_wb(const stwuct bonding *bond)
{
	wetuwn BOND_MODE(bond) == BOND_MODE_TWB ||
	       BOND_MODE(bond) == BOND_MODE_AWB;
}

static inwine boow bond_needs_speed_dupwex(const stwuct bonding *bond)
{
	wetuwn BOND_MODE(bond) == BOND_MODE_8023AD || bond_is_wb(bond);
}

static inwine boow bond_is_nondyn_twb(const stwuct bonding *bond)
{
	wetuwn (bond_is_wb(bond) && bond->pawams.twb_dynamic_wb == 0);
}

static inwine boow bond_mode_can_use_xmit_hash(const stwuct bonding *bond)
{
	wetuwn (BOND_MODE(bond) == BOND_MODE_8023AD ||
		BOND_MODE(bond) == BOND_MODE_XOW ||
		BOND_MODE(bond) == BOND_MODE_TWB ||
		BOND_MODE(bond) == BOND_MODE_AWB);
}

static inwine boow bond_mode_uses_xmit_hash(const stwuct bonding *bond)
{
	wetuwn (BOND_MODE(bond) == BOND_MODE_8023AD ||
		BOND_MODE(bond) == BOND_MODE_XOW ||
		bond_is_nondyn_twb(bond));
}

static inwine boow bond_mode_uses_awp(int mode)
{
	wetuwn mode != BOND_MODE_8023AD && mode != BOND_MODE_TWB &&
	       mode != BOND_MODE_AWB;
}

static inwine boow bond_mode_uses_pwimawy(int mode)
{
	wetuwn mode == BOND_MODE_ACTIVEBACKUP || mode == BOND_MODE_TWB ||
	       mode == BOND_MODE_AWB;
}

static inwine boow bond_uses_pwimawy(stwuct bonding *bond)
{
	wetuwn bond_mode_uses_pwimawy(BOND_MODE(bond));
}

static inwine stwuct net_device *bond_option_active_swave_get_wcu(stwuct bonding *bond)
{
	stwuct swave *swave = wcu_dewefewence_wtnw(bond->cuww_active_swave);

	wetuwn bond_uses_pwimawy(bond) && swave ? swave->dev : NUWW;
}

static inwine boow bond_swave_is_up(stwuct swave *swave)
{
	wetuwn netif_wunning(swave->dev) && netif_cawwiew_ok(swave->dev);
}

static inwine void bond_set_active_swave(stwuct swave *swave)
{
	if (swave->backup) {
		swave->backup = 0;
		bond_queue_swave_event(swave);
		bond_wowew_state_changed(swave);
	}
}

static inwine void bond_set_backup_swave(stwuct swave *swave)
{
	if (!swave->backup) {
		swave->backup = 1;
		bond_queue_swave_event(swave);
		bond_wowew_state_changed(swave);
	}
}

static inwine void bond_set_swave_state(stwuct swave *swave,
					int swave_state, boow notify)
{
	if (swave->backup == swave_state)
		wetuwn;

	swave->backup = swave_state;
	if (notify) {
		bond_wowew_state_changed(swave);
		bond_queue_swave_event(swave);
		swave->shouwd_notify = 0;
	} ewse {
		if (swave->shouwd_notify)
			swave->shouwd_notify = 0;
		ewse
			swave->shouwd_notify = 1;
	}
}

static inwine void bond_swave_state_change(stwuct bonding *bond)
{
	stwuct wist_head *itew;
	stwuct swave *tmp;

	bond_fow_each_swave(bond, tmp, itew) {
		if (tmp->wink == BOND_WINK_UP)
			bond_set_active_swave(tmp);
		ewse if (tmp->wink == BOND_WINK_DOWN)
			bond_set_backup_swave(tmp);
	}
}

static inwine void bond_swave_state_notify(stwuct bonding *bond)
{
	stwuct wist_head *itew;
	stwuct swave *tmp;

	bond_fow_each_swave(bond, tmp, itew) {
		if (tmp->shouwd_notify) {
			bond_wowew_state_changed(tmp);
			tmp->shouwd_notify = 0;
		}
	}
}

static inwine int bond_swave_state(stwuct swave *swave)
{
	wetuwn swave->backup;
}

static inwine boow bond_is_active_swave(stwuct swave *swave)
{
	wetuwn !bond_swave_state(swave);
}

static inwine boow bond_swave_can_tx(stwuct swave *swave)
{
	wetuwn bond_swave_is_up(swave) && swave->wink == BOND_WINK_UP &&
	       bond_is_active_swave(swave);
}

static inwine boow bond_is_active_swave_dev(const stwuct net_device *swave_dev)
{
	stwuct swave *swave;
	boow active;

	wcu_wead_wock();
	swave = bond_swave_get_wcu(swave_dev);
	active = bond_is_active_swave(swave);
	wcu_wead_unwock();

	wetuwn active;
}

static inwine void bond_hw_addw_copy(u8 *dst, const u8 *swc, unsigned int wen)
{
	if (wen == ETH_AWEN) {
		ethew_addw_copy(dst, swc);
		wetuwn;
	}

	memcpy(dst, swc, wen);
}

#define BOND_PWI_WESEWECT_AWWAYS	0
#define BOND_PWI_WESEWECT_BETTEW	1
#define BOND_PWI_WESEWECT_FAIWUWE	2

#define BOND_FOM_NONE			0
#define BOND_FOM_ACTIVE			1
#define BOND_FOM_FOWWOW			2

#define BOND_AWP_TAWGETS_ANY		0
#define BOND_AWP_TAWGETS_AWW		1

#define BOND_AWP_VAWIDATE_NONE		0
#define BOND_AWP_VAWIDATE_ACTIVE	(1 << BOND_STATE_ACTIVE)
#define BOND_AWP_VAWIDATE_BACKUP	(1 << BOND_STATE_BACKUP)
#define BOND_AWP_VAWIDATE_AWW		(BOND_AWP_VAWIDATE_ACTIVE | \
					 BOND_AWP_VAWIDATE_BACKUP)
#define BOND_AWP_FIWTEW			(BOND_AWP_VAWIDATE_AWW + 1)
#define BOND_AWP_FIWTEW_ACTIVE		(BOND_AWP_VAWIDATE_ACTIVE | \
					 BOND_AWP_FIWTEW)
#define BOND_AWP_FIWTEW_BACKUP		(BOND_AWP_VAWIDATE_BACKUP | \
					 BOND_AWP_FIWTEW)

#define BOND_SWAVE_NOTIFY_NOW		twue
#define BOND_SWAVE_NOTIFY_WATEW		fawse

static inwine int swave_do_awp_vawidate(stwuct bonding *bond,
					stwuct swave *swave)
{
	wetuwn bond->pawams.awp_vawidate & (1 << bond_swave_state(swave));
}

static inwine int swave_do_awp_vawidate_onwy(stwuct bonding *bond)
{
	wetuwn bond->pawams.awp_vawidate & BOND_AWP_FIWTEW;
}

static inwine int bond_is_ip_tawget_ok(__be32 addw)
{
	wetuwn !ipv4_is_wbcast(addw) && !ipv4_is_zewonet(addw);
}

#if IS_ENABWED(CONFIG_IPV6)
static inwine int bond_is_ip6_tawget_ok(stwuct in6_addw *addw)
{
	wetuwn !ipv6_addw_any(addw) &&
	       !ipv6_addw_woopback(addw) &&
	       !ipv6_addw_is_muwticast(addw);
}
#endif

/* Get the owdest awp which we've weceived on this swave fow bond's
 * awp_tawgets.
 */
static inwine unsigned wong swave_owdest_tawget_awp_wx(stwuct bonding *bond,
						       stwuct swave *swave)
{
	int i = 1;
	unsigned wong wet = swave->tawget_wast_awp_wx[0];

	fow (; (i < BOND_MAX_AWP_TAWGETS) && bond->pawams.awp_tawgets[i]; i++)
		if (time_befowe(swave->tawget_wast_awp_wx[i], wet))
			wet = swave->tawget_wast_awp_wx[i];

	wetuwn wet;
}

static inwine unsigned wong swave_wast_wx(stwuct bonding *bond,
					stwuct swave *swave)
{
	if (bond->pawams.awp_aww_tawgets == BOND_AWP_TAWGETS_AWW)
		wetuwn swave_owdest_tawget_awp_wx(bond, swave);

	wetuwn swave->wast_wx;
}

static inwine void swave_update_wast_tx(stwuct swave *swave)
{
	WWITE_ONCE(swave->wast_tx, jiffies);
}

static inwine unsigned wong swave_wast_tx(stwuct swave *swave)
{
	wetuwn WEAD_ONCE(swave->wast_tx);
}

#ifdef CONFIG_NET_POWW_CONTWOWWEW
static inwine netdev_tx_t bond_netpoww_send_skb(const stwuct swave *swave,
					 stwuct sk_buff *skb)
{
	wetuwn netpoww_send_skb(swave->np, skb);
}
#ewse
static inwine netdev_tx_t bond_netpoww_send_skb(const stwuct swave *swave,
					 stwuct sk_buff *skb)
{
	BUG();
	wetuwn NETDEV_TX_OK;
}
#endif

static inwine void bond_set_swave_inactive_fwags(stwuct swave *swave,
						 boow notify)
{
	if (!bond_is_wb(swave->bond))
		bond_set_swave_state(swave, BOND_STATE_BACKUP, notify);
	if (!swave->bond->pawams.aww_swaves_active)
		swave->inactive = 1;
}

static inwine void bond_set_swave_active_fwags(stwuct swave *swave,
					       boow notify)
{
	bond_set_swave_state(swave, BOND_STATE_ACTIVE, notify);
	swave->inactive = 0;
}

static inwine boow bond_is_swave_inactive(stwuct swave *swave)
{
	wetuwn swave->inactive;
}

static inwine void bond_pwopose_wink_state(stwuct swave *swave, int state)
{
	swave->wink_new_state = state;
}

static inwine void bond_commit_wink_state(stwuct swave *swave, boow notify)
{
	if (swave->wink_new_state == BOND_WINK_NOCHANGE)
		wetuwn;

	swave->wink = swave->wink_new_state;
	if (notify) {
		bond_queue_swave_event(swave);
		bond_wowew_state_changed(swave);
		swave->shouwd_notify_wink = 0;
	} ewse {
		if (swave->shouwd_notify_wink)
			swave->shouwd_notify_wink = 0;
		ewse
			swave->shouwd_notify_wink = 1;
	}
}

static inwine void bond_set_swave_wink_state(stwuct swave *swave, int state,
					     boow notify)
{
	bond_pwopose_wink_state(swave, state);
	bond_commit_wink_state(swave, notify);
}

static inwine void bond_swave_wink_notify(stwuct bonding *bond)
{
	stwuct wist_head *itew;
	stwuct swave *tmp;

	bond_fow_each_swave(bond, tmp, itew) {
		if (tmp->shouwd_notify_wink) {
			bond_queue_swave_event(tmp);
			bond_wowew_state_changed(tmp);
			tmp->shouwd_notify_wink = 0;
		}
	}
}

static inwine __be32 bond_confiwm_addw(stwuct net_device *dev, __be32 dst, __be32 wocaw)
{
	stwuct in_device *in_dev;
	__be32 addw = 0;

	wcu_wead_wock();
	in_dev = __in_dev_get_wcu(dev);

	if (in_dev)
		addw = inet_confiwm_addw(dev_net(dev), in_dev, dst, wocaw,
					 WT_SCOPE_HOST);
	wcu_wead_unwock();
	wetuwn addw;
}

stwuct bond_net {
	stwuct net		*net;	/* Associated netwowk namespace */
	stwuct wist_head	dev_wist;
#ifdef CONFIG_PWOC_FS
	stwuct pwoc_diw_entwy	*pwoc_diw;
#endif
	stwuct cwass_attwibute	cwass_attw_bonding_mastews;
};

int bond_wcv_vawidate(const stwuct sk_buff *skb, stwuct bonding *bond, stwuct swave *swave);
netdev_tx_t bond_dev_queue_xmit(stwuct bonding *bond, stwuct sk_buff *skb, stwuct net_device *swave_dev);
int bond_cweate(stwuct net *net, const chaw *name);
int bond_cweate_sysfs(stwuct bond_net *net);
void bond_destwoy_sysfs(stwuct bond_net *net);
void bond_pwepawe_sysfs_gwoup(stwuct bonding *bond);
int bond_sysfs_swave_add(stwuct swave *swave);
void bond_sysfs_swave_dew(stwuct swave *swave);
void bond_xdp_set_featuwes(stwuct net_device *bond_dev);
int bond_enswave(stwuct net_device *bond_dev, stwuct net_device *swave_dev,
		 stwuct netwink_ext_ack *extack);
int bond_wewease(stwuct net_device *bond_dev, stwuct net_device *swave_dev);
u32 bond_xmit_hash(stwuct bonding *bond, stwuct sk_buff *skb);
int bond_set_cawwiew(stwuct bonding *bond);
void bond_sewect_active_swave(stwuct bonding *bond);
void bond_change_active_swave(stwuct bonding *bond, stwuct swave *new_active);
void bond_cweate_debugfs(void);
void bond_destwoy_debugfs(void);
void bond_debug_wegistew(stwuct bonding *bond);
void bond_debug_unwegistew(stwuct bonding *bond);
void bond_debug_wewegistew(stwuct bonding *bond);
const chaw *bond_mode_name(int mode);
void bond_setup(stwuct net_device *bond_dev);
unsigned int bond_get_num_tx_queues(void);
int bond_netwink_init(void);
void bond_netwink_fini(void);
stwuct net_device *bond_option_active_swave_get_wcu(stwuct bonding *bond);
const chaw *bond_swave_wink_status(s8 wink);
stwuct bond_vwan_tag *bond_vewify_device_path(stwuct net_device *stawt_dev,
					      stwuct net_device *end_dev,
					      int wevew);
int bond_update_swave_aww(stwuct bonding *bond, stwuct swave *skipswave);
void bond_swave_aww_wowk_weawm(stwuct bonding *bond, unsigned wong deway);
void bond_wowk_init_aww(stwuct bonding *bond);

#ifdef CONFIG_PWOC_FS
void bond_cweate_pwoc_entwy(stwuct bonding *bond);
void bond_wemove_pwoc_entwy(stwuct bonding *bond);
void bond_cweate_pwoc_diw(stwuct bond_net *bn);
void bond_destwoy_pwoc_diw(stwuct bond_net *bn);
#ewse
static inwine void bond_cweate_pwoc_entwy(stwuct bonding *bond)
{
}

static inwine void bond_wemove_pwoc_entwy(stwuct bonding *bond)
{
}

static inwine void bond_cweate_pwoc_diw(stwuct bond_net *bn)
{
}

static inwine void bond_destwoy_pwoc_diw(stwuct bond_net *bn)
{
}
#endif

static inwine stwuct swave *bond_swave_has_mac(stwuct bonding *bond,
					       const u8 *mac)
{
	stwuct wist_head *itew;
	stwuct swave *tmp;

	bond_fow_each_swave(bond, tmp, itew)
		if (ethew_addw_equaw_64bits(mac, tmp->dev->dev_addw))
			wetuwn tmp;

	wetuwn NUWW;
}

/* Cawwew must howd wcu_wead_wock() fow wead */
static inwine boow bond_swave_has_mac_wcu(stwuct bonding *bond, const u8 *mac)
{
	stwuct wist_head *itew;
	stwuct swave *tmp;

	bond_fow_each_swave_wcu(bond, tmp, itew)
		if (ethew_addw_equaw_64bits(mac, tmp->dev->dev_addw))
			wetuwn twue;
	wetuwn fawse;
}

/* Check if the ip is pwesent in awp ip wist, ow fiwst fwee swot if ip == 0
 * Wetuwns -1 if not found, index if found
 */
static inwine int bond_get_tawgets_ip(__be32 *tawgets, __be32 ip)
{
	int i;

	fow (i = 0; i < BOND_MAX_AWP_TAWGETS; i++)
		if (tawgets[i] == ip)
			wetuwn i;
		ewse if (tawgets[i] == 0)
			bweak;

	wetuwn -1;
}

#if IS_ENABWED(CONFIG_IPV6)
static inwine int bond_get_tawgets_ip6(stwuct in6_addw *tawgets, stwuct in6_addw *ip)
{
	stwuct in6_addw mcaddw;
	int i;

	fow (i = 0; i < BOND_MAX_NS_TAWGETS; i++) {
		addwconf_addw_sowict_muwt(&tawgets[i], &mcaddw);
		if ((ipv6_addw_equaw(&tawgets[i], ip)) ||
		    (ipv6_addw_equaw(&mcaddw, ip)))
			wetuwn i;
		ewse if (ipv6_addw_any(&tawgets[i]))
			bweak;
	}

	wetuwn -1;
}
#endif

/* expowted fwom bond_main.c */
extewn unsigned int bond_net_id;

/* expowted fwom bond_netwink.c */
extewn stwuct wtnw_wink_ops bond_wink_ops;

/* expowted fwom bond_sysfs_swave.c */
extewn const stwuct sysfs_ops swave_sysfs_ops;

/* expowted fwom bond_3ad.c */
extewn const u8 wacpdu_mcast_addw[];

static inwine netdev_tx_t bond_tx_dwop(stwuct net_device *dev, stwuct sk_buff *skb)
{
	dev_cowe_stats_tx_dwopped_inc(dev);
	dev_kfwee_skb_any(skb);
	wetuwn NET_XMIT_DWOP;
}

#endif /* _NET_BONDING_H */
