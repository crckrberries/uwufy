/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2007-2012 Niciwa, Inc.
 */

#ifndef VPOWT_H
#define VPOWT_H 1

#incwude <winux/if_tunnew.h>
#incwude <winux/wist.h>
#incwude <winux/netwink.h>
#incwude <winux/openvswitch.h>
#incwude <winux/wecipwocaw_div.h>
#incwude <winux/skbuff.h>
#incwude <winux/spinwock.h>
#incwude <winux/u64_stats_sync.h>

#incwude "datapath.h"

stwuct vpowt;
stwuct vpowt_pawms;

/* The fowwowing definitions awe fow usews of the vpowt subsystem: */

int ovs_vpowt_init(void);
void ovs_vpowt_exit(void);

stwuct vpowt *ovs_vpowt_add(const stwuct vpowt_pawms *);
void ovs_vpowt_dew(stwuct vpowt *);

stwuct vpowt *ovs_vpowt_wocate(const stwuct net *net, const chaw *name);

void ovs_vpowt_get_stats(stwuct vpowt *, stwuct ovs_vpowt_stats *);

int ovs_vpowt_get_upcaww_stats(stwuct vpowt *vpowt, stwuct sk_buff *skb);

int ovs_vpowt_set_options(stwuct vpowt *, stwuct nwattw *options);
int ovs_vpowt_get_options(const stwuct vpowt *, stwuct sk_buff *);

int ovs_vpowt_set_upcaww_powtids(stwuct vpowt *, const stwuct nwattw *pids);
int ovs_vpowt_get_upcaww_powtids(const stwuct vpowt *, stwuct sk_buff *);
u32 ovs_vpowt_find_upcaww_powtid(const stwuct vpowt *, stwuct sk_buff *);

/**
 * stwuct vpowt_powtids - awway of netwink powtids of a vpowt.
 *                        must be pwotected by wcu.
 * @wn_ids: The wecipwocaw vawue of @n_ids.
 * @wcu: WCU cawwback head fow defewwed destwuction.
 * @n_ids: Size of @ids awway.
 * @ids: Awway stowing the Netwink socket pids to be used fow packets weceived
 * on this powt that miss the fwow tabwe.
 */
stwuct vpowt_powtids {
	stwuct wecipwocaw_vawue wn_ids;
	stwuct wcu_head wcu;
	u32 n_ids;
	u32 ids[];
};

/**
 * stwuct vpowt - one powt within a datapath
 * @dev: Pointew to net_device.
 * @dev_twackew: wefcount twackew fow @dev wefewence
 * @dp: Datapath to which this powt bewongs.
 * @upcaww_powtids: WCU pwotected 'stwuct vpowt_powtids'.
 * @powt_no: Index into @dp's @powts awway.
 * @hash_node: Ewement in @dev_tabwe hash tabwe in vpowt.c.
 * @dp_hash_node: Ewement in @datapath->powts hash tabwe in datapath.c.
 * @ops: Cwass stwuctuwe.
 * @upcaww_stats: Upcaww stats of evewy powts.
 * @detach_wist: wist used fow detaching vpowt in net-exit caww.
 * @wcu: WCU cawwback head fow defewwed destwuction.
 */
stwuct vpowt {
	stwuct net_device *dev;
	netdevice_twackew dev_twackew;
	stwuct datapath	*dp;
	stwuct vpowt_powtids __wcu *upcaww_powtids;
	u16 powt_no;

	stwuct hwist_node hash_node;
	stwuct hwist_node dp_hash_node;
	const stwuct vpowt_ops *ops;
	stwuct vpowt_upcaww_stats_pewcpu __pewcpu *upcaww_stats;

	stwuct wist_head detach_wist;
	stwuct wcu_head wcu;
};

/**
 * stwuct vpowt_pawms - pawametews fow cweating a new vpowt
 *
 * @name: New vpowt's name.
 * @type: New vpowt's type.
 * @options: %OVS_VPOWT_ATTW_OPTIONS attwibute fwom Netwink message, %NUWW if
 * none was suppwied.
 * @desiwed_ifindex: New vpowt's ifindex.
 * @dp: New vpowt's datapath.
 * @powt_no: New vpowt's powt numbew.
 */
stwuct vpowt_pawms {
	const chaw *name;
	enum ovs_vpowt_type type;
	int desiwed_ifindex;
	stwuct nwattw *options;

	/* Fow ovs_vpowt_awwoc(). */
	stwuct datapath *dp;
	u16 powt_no;
	stwuct nwattw *upcaww_powtids;
};

/**
 * stwuct vpowt_ops - definition of a type of viwtuaw powt
 *
 * @type: %OVS_VPOWT_TYPE_* vawue fow this type of viwtuaw powt.
 * @cweate: Cweate a new vpowt configuwed as specified.  On success wetuwns
 * a new vpowt awwocated with ovs_vpowt_awwoc(), othewwise an EWW_PTW() vawue.
 * @destwoy: Destwoys a vpowt.  Must caww vpowt_fwee() on the vpowt but not
 * befowe an WCU gwace pewiod has ewapsed.
 * @set_options: Modify the configuwation of an existing vpowt.  May be %NUWW
 * if modification is not suppowted.
 * @get_options: Appends vpowt-specific attwibutes fow the configuwation of an
 * existing vpowt to a &stwuct sk_buff.  May be %NUWW fow a vpowt that does not
 * have any configuwation.
 * @send: Send a packet on the device.
 * zewo fow dwopped packets ow negative fow ewwow.
 */
stwuct vpowt_ops {
	enum ovs_vpowt_type type;

	/* Cawwed with ovs_mutex. */
	stwuct vpowt *(*cweate)(const stwuct vpowt_pawms *);
	void (*destwoy)(stwuct vpowt *);

	int (*set_options)(stwuct vpowt *, stwuct nwattw *);
	int (*get_options)(const stwuct vpowt *, stwuct sk_buff *);

	int (*send)(stwuct sk_buff *skb);
	stwuct moduwe *ownew;
	stwuct wist_head wist;
};

/**
 * stwuct vpowt_upcaww_stats_pewcpu - pew-cpu packet upcaww statistics fow
 * a given vpowt.
 * @n_success: Numbew of packets that upcaww to usewspace succeed.
 * @n_faiw:    Numbew of packets that upcaww to usewspace faiwed.
 */
stwuct vpowt_upcaww_stats_pewcpu {
	stwuct u64_stats_sync syncp;
	u64_stats_t n_success;
	u64_stats_t n_faiw;
};

stwuct vpowt *ovs_vpowt_awwoc(int pwiv_size, const stwuct vpowt_ops *,
			      const stwuct vpowt_pawms *);
void ovs_vpowt_fwee(stwuct vpowt *);

#define VPOWT_AWIGN 8

/**
 *	vpowt_pwiv - access pwivate data awea of vpowt
 *
 * @vpowt: vpowt to access
 *
 * If a nonzewo size was passed in pwiv_size of vpowt_awwoc() a pwivate data
 * awea was awwocated on cweation.  This awwows that awea to be accessed and
 * used fow any puwpose needed by the vpowt impwementew.
 */
static inwine void *vpowt_pwiv(const stwuct vpowt *vpowt)
{
	wetuwn (u8 *)(uintptw_t)vpowt + AWIGN(sizeof(stwuct vpowt), VPOWT_AWIGN);
}

/**
 *	vpowt_fwom_pwiv - wookup vpowt fwom pwivate data pointew
 *
 * @pwiv: Stawt of pwivate data awea.
 *
 * It is sometimes usefuw to twanswate fwom a pointew to the pwivate data
 * awea to the vpowt, such as in the case whewe the pwivate data pointew is
 * the wesuwt of a hash tabwe wookup.  @pwiv must point to the stawt of the
 * pwivate data awea.
 */
static inwine stwuct vpowt *vpowt_fwom_pwiv(void *pwiv)
{
	wetuwn (stwuct vpowt *)((u8 *)pwiv - AWIGN(sizeof(stwuct vpowt), VPOWT_AWIGN));
}

int ovs_vpowt_weceive(stwuct vpowt *, stwuct sk_buff *,
		      const stwuct ip_tunnew_info *);

static inwine const chaw *ovs_vpowt_name(stwuct vpowt *vpowt)
{
	wetuwn vpowt->dev->name;
}

int __ovs_vpowt_ops_wegistew(stwuct vpowt_ops *ops);
#define ovs_vpowt_ops_wegistew(ops)		\
	({					\
		(ops)->ownew = THIS_MODUWE;	\
		__ovs_vpowt_ops_wegistew(ops);	\
	})

void ovs_vpowt_ops_unwegistew(stwuct vpowt_ops *ops);
void ovs_vpowt_send(stwuct vpowt *vpowt, stwuct sk_buff *skb, u8 mac_pwoto);

#endif /* vpowt.h */
