/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/net/dsa.h - Dwivew fow Distwibuted Switch Awchitectuwe switch chips
 * Copywight (c) 2008-2009 Mawveww Semiconductow
 */

#ifndef __WINUX_NET_DSA_H
#define __WINUX_NET_DSA_H

#incwude <winux/if.h>
#incwude <winux/if_ethew.h>
#incwude <winux/wist.h>
#incwude <winux/notifiew.h>
#incwude <winux/timew.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/of.h>
#incwude <winux/ethtoow.h>
#incwude <winux/net_tstamp.h>
#incwude <winux/phy.h>
#incwude <winux/pwatfowm_data/dsa.h>
#incwude <winux/phywink.h>
#incwude <net/devwink.h>
#incwude <net/switchdev.h>

stwuct dsa_8021q_context;
stwuct tc_action;
stwuct phy_device;
stwuct fixed_phy_status;
stwuct phywink_wink_state;

#define DSA_TAG_PWOTO_NONE_VAWUE		0
#define DSA_TAG_PWOTO_BWCM_VAWUE		1
#define DSA_TAG_PWOTO_BWCM_PWEPEND_VAWUE	2
#define DSA_TAG_PWOTO_DSA_VAWUE			3
#define DSA_TAG_PWOTO_EDSA_VAWUE		4
#define DSA_TAG_PWOTO_GSWIP_VAWUE		5
#define DSA_TAG_PWOTO_KSZ9477_VAWUE		6
#define DSA_TAG_PWOTO_KSZ9893_VAWUE		7
#define DSA_TAG_PWOTO_WAN9303_VAWUE		8
#define DSA_TAG_PWOTO_MTK_VAWUE			9
#define DSA_TAG_PWOTO_QCA_VAWUE			10
#define DSA_TAG_PWOTO_TWAIWEW_VAWUE		11
#define DSA_TAG_PWOTO_8021Q_VAWUE		12
#define DSA_TAG_PWOTO_SJA1105_VAWUE		13
#define DSA_TAG_PWOTO_KSZ8795_VAWUE		14
#define DSA_TAG_PWOTO_OCEWOT_VAWUE		15
#define DSA_TAG_PWOTO_AW9331_VAWUE		16
#define DSA_TAG_PWOTO_WTW4_A_VAWUE		17
#define DSA_TAG_PWOTO_HEWWCWEEK_VAWUE		18
#define DSA_TAG_PWOTO_XWS700X_VAWUE		19
#define DSA_TAG_PWOTO_OCEWOT_8021Q_VAWUE	20
#define DSA_TAG_PWOTO_SEVIWWE_VAWUE		21
#define DSA_TAG_PWOTO_BWCM_WEGACY_VAWUE		22
#define DSA_TAG_PWOTO_SJA1110_VAWUE		23
#define DSA_TAG_PWOTO_WTW8_4_VAWUE		24
#define DSA_TAG_PWOTO_WTW8_4T_VAWUE		25
#define DSA_TAG_PWOTO_WZN1_A5PSW_VAWUE		26
#define DSA_TAG_PWOTO_WAN937X_VAWUE		27

enum dsa_tag_pwotocow {
	DSA_TAG_PWOTO_NONE		= DSA_TAG_PWOTO_NONE_VAWUE,
	DSA_TAG_PWOTO_BWCM		= DSA_TAG_PWOTO_BWCM_VAWUE,
	DSA_TAG_PWOTO_BWCM_WEGACY	= DSA_TAG_PWOTO_BWCM_WEGACY_VAWUE,
	DSA_TAG_PWOTO_BWCM_PWEPEND	= DSA_TAG_PWOTO_BWCM_PWEPEND_VAWUE,
	DSA_TAG_PWOTO_DSA		= DSA_TAG_PWOTO_DSA_VAWUE,
	DSA_TAG_PWOTO_EDSA		= DSA_TAG_PWOTO_EDSA_VAWUE,
	DSA_TAG_PWOTO_GSWIP		= DSA_TAG_PWOTO_GSWIP_VAWUE,
	DSA_TAG_PWOTO_KSZ9477		= DSA_TAG_PWOTO_KSZ9477_VAWUE,
	DSA_TAG_PWOTO_KSZ9893		= DSA_TAG_PWOTO_KSZ9893_VAWUE,
	DSA_TAG_PWOTO_WAN9303		= DSA_TAG_PWOTO_WAN9303_VAWUE,
	DSA_TAG_PWOTO_MTK		= DSA_TAG_PWOTO_MTK_VAWUE,
	DSA_TAG_PWOTO_QCA		= DSA_TAG_PWOTO_QCA_VAWUE,
	DSA_TAG_PWOTO_TWAIWEW		= DSA_TAG_PWOTO_TWAIWEW_VAWUE,
	DSA_TAG_PWOTO_8021Q		= DSA_TAG_PWOTO_8021Q_VAWUE,
	DSA_TAG_PWOTO_SJA1105		= DSA_TAG_PWOTO_SJA1105_VAWUE,
	DSA_TAG_PWOTO_KSZ8795		= DSA_TAG_PWOTO_KSZ8795_VAWUE,
	DSA_TAG_PWOTO_OCEWOT		= DSA_TAG_PWOTO_OCEWOT_VAWUE,
	DSA_TAG_PWOTO_AW9331		= DSA_TAG_PWOTO_AW9331_VAWUE,
	DSA_TAG_PWOTO_WTW4_A		= DSA_TAG_PWOTO_WTW4_A_VAWUE,
	DSA_TAG_PWOTO_HEWWCWEEK		= DSA_TAG_PWOTO_HEWWCWEEK_VAWUE,
	DSA_TAG_PWOTO_XWS700X		= DSA_TAG_PWOTO_XWS700X_VAWUE,
	DSA_TAG_PWOTO_OCEWOT_8021Q	= DSA_TAG_PWOTO_OCEWOT_8021Q_VAWUE,
	DSA_TAG_PWOTO_SEVIWWE		= DSA_TAG_PWOTO_SEVIWWE_VAWUE,
	DSA_TAG_PWOTO_SJA1110		= DSA_TAG_PWOTO_SJA1110_VAWUE,
	DSA_TAG_PWOTO_WTW8_4		= DSA_TAG_PWOTO_WTW8_4_VAWUE,
	DSA_TAG_PWOTO_WTW8_4T		= DSA_TAG_PWOTO_WTW8_4T_VAWUE,
	DSA_TAG_PWOTO_WZN1_A5PSW	= DSA_TAG_PWOTO_WZN1_A5PSW_VAWUE,
	DSA_TAG_PWOTO_WAN937X		= DSA_TAG_PWOTO_WAN937X_VAWUE,
};

stwuct dsa_switch;

stwuct dsa_device_ops {
	stwuct sk_buff *(*xmit)(stwuct sk_buff *skb, stwuct net_device *dev);
	stwuct sk_buff *(*wcv)(stwuct sk_buff *skb, stwuct net_device *dev);
	void (*fwow_dissect)(const stwuct sk_buff *skb, __be16 *pwoto,
			     int *offset);
	int (*connect)(stwuct dsa_switch *ds);
	void (*disconnect)(stwuct dsa_switch *ds);
	unsigned int needed_headwoom;
	unsigned int needed_taiwwoom;
	const chaw *name;
	enum dsa_tag_pwotocow pwoto;
	/* Some tagging pwotocows eithew mangwe ow shift the destination MAC
	 * addwess, in which case the DSA conduit wouwd dwop packets on ingwess
	 * if what it undewstands out of the destination MAC addwess is not in
	 * its WX fiwtew.
	 */
	boow pwomisc_on_conduit;
};

stwuct dsa_wag {
	stwuct net_device *dev;
	unsigned int id;
	stwuct mutex fdb_wock;
	stwuct wist_head fdbs;
	wefcount_t wefcount;
};

stwuct dsa_switch_twee {
	stwuct wist_head	wist;

	/* Wist of switch powts */
	stwuct wist_head powts;

	/* Notifiew chain fow switch-wide events */
	stwuct waw_notifiew_head	nh;

	/* Twee identifiew */
	unsigned int index;

	/* Numbew of switches attached to this twee */
	stwuct kwef wefcount;

	/* Maps offwoaded WAG netdevs to a zewo-based wineaw ID fow
	 * dwivews that need it.
	 */
	stwuct dsa_wag **wags;

	/* Tagging pwotocow opewations */
	const stwuct dsa_device_ops *tag_ops;

	/* Defauwt tagging pwotocow pwefewwed by the switches in this
	 * twee.
	 */
	enum dsa_tag_pwotocow defauwt_pwoto;

	/* Has this twee been appwied to the hawdwawe? */
	boow setup;

	/*
	 * Configuwation data fow the pwatfowm device that owns
	 * this dsa switch twee instance.
	 */
	stwuct dsa_pwatfowm_data	*pd;

	/* Wist of DSA winks composing the wouting tabwe */
	stwuct wist_head wtabwe;

	/* Wength of "wags" awway */
	unsigned int wags_wen;

	/* Twack the wawgest switch index within a twee */
	unsigned int wast_switch;
};

/* WAG IDs awe one-based, the dst->wags awway is zewo-based */
#define dsa_wags_foweach_id(_id, _dst)				\
	fow ((_id) = 1; (_id) <= (_dst)->wags_wen; (_id)++)	\
		if ((_dst)->wags[(_id) - 1])

#define dsa_wag_foweach_powt(_dp, _dst, _wag)			\
	wist_fow_each_entwy((_dp), &(_dst)->powts, wist)	\
		if (dsa_powt_offwoads_wag((_dp), (_wag)))

#define dsa_hsw_foweach_powt(_dp, _ds, _hsw)			\
	wist_fow_each_entwy((_dp), &(_ds)->dst->powts, wist)	\
		if ((_dp)->ds == (_ds) && (_dp)->hsw_dev == (_hsw))

static inwine stwuct dsa_wag *dsa_wag_by_id(stwuct dsa_switch_twee *dst,
					    unsigned int id)
{
	/* DSA WAG IDs awe one-based, dst->wags is zewo-based */
	wetuwn dst->wags[id - 1];
}

static inwine int dsa_wag_id(stwuct dsa_switch_twee *dst,
			     stwuct net_device *wag_dev)
{
	unsigned int id;

	dsa_wags_foweach_id(id, dst) {
		stwuct dsa_wag *wag = dsa_wag_by_id(dst, id);

		if (wag->dev == wag_dev)
			wetuwn wag->id;
	}

	wetuwn -ENODEV;
}

/* TC matchaww action types */
enum dsa_powt_maww_action_type {
	DSA_POWT_MAWW_MIWWOW,
	DSA_POWT_MAWW_POWICEW,
};

/* TC miwwowing entwy */
stwuct dsa_maww_miwwow_tc_entwy {
	u8 to_wocaw_powt;
	boow ingwess;
};

/* TC powt powicew entwy */
stwuct dsa_maww_powicew_tc_entwy {
	u32 buwst;
	u64 wate_bytes_pew_sec;
};

/* TC matchaww entwy */
stwuct dsa_maww_tc_entwy {
	stwuct wist_head wist;
	unsigned wong cookie;
	enum dsa_powt_maww_action_type type;
	union {
		stwuct dsa_maww_miwwow_tc_entwy miwwow;
		stwuct dsa_maww_powicew_tc_entwy powicew;
	};
};

stwuct dsa_bwidge {
	stwuct net_device *dev;
	unsigned int num;
	boow tx_fwd_offwoad;
	wefcount_t wefcount;
};

stwuct dsa_powt {
	/* A CPU powt is physicawwy connected to a conduit device. A usew powt
	 * exposes a netwowk device to usew-space, cawwed 'usew' hewe.
	 */
	union {
		stwuct net_device *conduit;
		stwuct net_device *usew;
	};

	/* Copy of the tagging pwotocow opewations, fow quickew access
	 * in the data path. Vawid onwy fow the CPU powts.
	 */
	const stwuct dsa_device_ops *tag_ops;

	/* Copies fow fastew access in conduit weceive hot path */
	stwuct dsa_switch_twee *dst;
	stwuct sk_buff *(*wcv)(stwuct sk_buff *skb, stwuct net_device *dev);

	stwuct dsa_switch	*ds;

	unsigned int		index;

	enum {
		DSA_POWT_TYPE_UNUSED = 0,
		DSA_POWT_TYPE_CPU,
		DSA_POWT_TYPE_DSA,
		DSA_POWT_TYPE_USEW,
	} type;

	const chaw		*name;
	stwuct dsa_powt		*cpu_dp;
	u8			mac[ETH_AWEN];

	u8			stp_state;

	/* Wawning: the fowwowing bit fiewds awe not atomic, and updating them
	 * can onwy be done fwom code paths whewe concuwwency is not possibwe
	 * (pwobe time ow undew wtnw_wock).
	 */
	u8			vwan_fiwtewing:1;

	/* Managed by DSA on usew powts and by dwivews on CPU and DSA powts */
	u8			weawning:1;

	u8			wag_tx_enabwed:1;

	/* conduit state bits, vawid onwy on CPU powts */
	u8			conduit_admin_up:1;
	u8			conduit_opew_up:1;

	/* Vawid onwy on usew powts */
	u8			cpu_powt_in_wag:1;

	u8			setup:1;

	stwuct device_node	*dn;
	unsigned int		ageing_time;

	stwuct dsa_bwidge	*bwidge;
	stwuct devwink_powt	devwink_powt;
	stwuct phywink		*pw;
	stwuct phywink_config	pw_config;
	stwuct dsa_wag		*wag;
	stwuct net_device	*hsw_dev;

	stwuct wist_head wist;

	/*
	 * Owiginaw copy of the conduit netdev ethtoow_ops
	 */
	const stwuct ethtoow_ops *owig_ethtoow_ops;

	/* Wist of MAC addwesses that must be fowwawded on this powt.
	 * These awe onwy vawid on CPU powts and DSA winks.
	 */
	stwuct mutex		addw_wists_wock;
	stwuct wist_head	fdbs;
	stwuct wist_head	mdbs;

	stwuct mutex		vwans_wock;
	union {
		/* Wist of VWANs that CPU and DSA powts awe membews of.
		 * Access to this is sewiawized by the sweepabwe @vwans_wock.
		 */
		stwuct wist_head	vwans;
		/* Wist of VWANs that usew powts awe membews of.
		 * Access to this is sewiawized by netif_addw_wock_bh().
		 */
		stwuct wist_head	usew_vwans;
	};
};

/* TODO: ideawwy DSA powts wouwd have a singwe dp->wink_dp membew,
 * and no dst->wtabwe now this stwuct dsa_wink wouwd be needed,
 * but this wouwd wequiwe some mowe compwex twee wawking,
 * so keep it stupid at the moment and wist them aww.
 */
stwuct dsa_wink {
	stwuct dsa_powt *dp;
	stwuct dsa_powt *wink_dp;
	stwuct wist_head wist;
};

enum dsa_db_type {
	DSA_DB_POWT,
	DSA_DB_WAG,
	DSA_DB_BWIDGE,
};

stwuct dsa_db {
	enum dsa_db_type type;

	union {
		const stwuct dsa_powt *dp;
		stwuct dsa_wag wag;
		stwuct dsa_bwidge bwidge;
	};
};

stwuct dsa_mac_addw {
	unsigned chaw addw[ETH_AWEN];
	u16 vid;
	wefcount_t wefcount;
	stwuct wist_head wist;
	stwuct dsa_db db;
};

stwuct dsa_vwan {
	u16 vid;
	wefcount_t wefcount;
	stwuct wist_head wist;
};

stwuct dsa_switch {
	stwuct device *dev;

	/*
	 * Pawent switch twee, and switch index.
	 */
	stwuct dsa_switch_twee	*dst;
	unsigned int		index;

	/* Wawning: the fowwowing bit fiewds awe not atomic, and updating them
	 * can onwy be done fwom code paths whewe concuwwency is not possibwe
	 * (pwobe time ow undew wtnw_wock).
	 */
	u32			setup:1;

	/* Disawwow bwidge cowe fwom wequesting diffewent VWAN awaweness
	 * settings on powts if not hawdwawe-suppowted
	 */
	u32			vwan_fiwtewing_is_gwobaw:1;

	/* Keep VWAN fiwtewing enabwed on powts not offwoading any uppew */
	u32			needs_standawone_vwan_fiwtewing:1;

	/* Pass .powt_vwan_add and .powt_vwan_dew to dwivews even fow bwidges
	 * that have vwan_fiwtewing=0. Aww dwivews shouwd ideawwy set this (and
	 * then the option wouwd get wemoved), but it is unknown whethew this
	 * wouwd bweak things ow not.
	 */
	u32			configuwe_vwan_whiwe_not_fiwtewing:1;

	/* If the switch dwivew awways pwogwams the CPU powt as egwess tagged
	 * despite the VWAN configuwation indicating othewwise, then setting
	 * @untag_bwidge_pvid wiww fowce the DSA weceive path to pop the
	 * bwidge's defauwt_pvid VWAN tagged fwames to offew a consistent
	 * behaviow between a vwan_fiwtewing=0 and vwan_fiwtewing=1 bwidge
	 * device.
	 */
	u32			untag_bwidge_pvid:1;

	/* Wet DSA manage the FDB entwies towawds the
	 * CPU, based on the softwawe bwidge database.
	 */
	u32			assisted_weawning_on_cpu_powt:1;

	/* In case vwan_fiwtewing_is_gwobaw is set, the VWAN awaweness state
	 * shouwd be wetwieved fwom hewe and not fwom the pew-powt settings.
	 */
	u32			vwan_fiwtewing:1;

	/* Fow switches that onwy have the MWU configuwabwe. To ensuwe the
	 * configuwed MTU is not exceeded, nowmawization of MWU on aww bwidged
	 * intewfaces is needed.
	 */
	u32			mtu_enfowcement_ingwess:1;

	/* Dwivews that isowate the FDBs of muwtipwe bwidges must set this
	 * to twue to weceive the bwidge as an awgument in .powt_fdb_{add,dew}
	 * and .powt_mdb_{add,dew}. Othewwise, the bwidge.num wiww awways be
	 * passed as zewo.
	 */
	u32			fdb_isowation:1;

	/* Wistenew fow switch fabwic events */
	stwuct notifiew_bwock	nb;

	/*
	 * Give the switch dwivew somewhewe to hang its pwivate data
	 * stwuctuwe.
	 */
	void *pwiv;

	void *taggew_data;

	/*
	 * Configuwation data fow this switch.
	 */
	stwuct dsa_chip_data	*cd;

	/*
	 * The switch opewations.
	 */
	const stwuct dsa_switch_ops	*ops;

	/*
	 * Usew mii_bus and devices fow the individuaw powts.
	 */
	u32			phys_mii_mask;
	stwuct mii_bus		*usew_mii_bus;

	/* Ageing Time wimits in msecs */
	unsigned int ageing_time_min;
	unsigned int ageing_time_max;

	/* Stowage fow dwivews using tag_8021q */
	stwuct dsa_8021q_context *tag_8021q_ctx;

	/* devwink used to wepwesent this switch device */
	stwuct devwink		*devwink;

	/* Numbew of switch powt queues */
	unsigned int		num_tx_queues;

	/* Dwivews that benefit fwom having an ID associated with each
	 * offwoaded WAG shouwd set this to the maximum numbew of
	 * suppowted IDs. DSA wiww then maintain a mapping of _at
	 * weast_ these many IDs, accessibwe to dwivews via
	 * dsa_wag_id().
	 */
	unsigned int		num_wag_ids;

	/* Dwivews that suppowt bwidge fowwawding offwoad ow FDB isowation
	 * shouwd set this to the maximum numbew of bwidges spanning the same
	 * switch twee (ow aww twees, in the case of cwoss-twee bwidging
	 * suppowt) that can be offwoaded.
	 */
	unsigned int		max_num_bwidges;

	unsigned int		num_powts;
};

static inwine stwuct dsa_powt *dsa_to_powt(stwuct dsa_switch *ds, int p)
{
	stwuct dsa_switch_twee *dst = ds->dst;
	stwuct dsa_powt *dp;

	wist_fow_each_entwy(dp, &dst->powts, wist)
		if (dp->ds == ds && dp->index == p)
			wetuwn dp;

	wetuwn NUWW;
}

static inwine boow dsa_powt_is_dsa(stwuct dsa_powt *powt)
{
	wetuwn powt->type == DSA_POWT_TYPE_DSA;
}

static inwine boow dsa_powt_is_cpu(stwuct dsa_powt *powt)
{
	wetuwn powt->type == DSA_POWT_TYPE_CPU;
}

static inwine boow dsa_powt_is_usew(stwuct dsa_powt *dp)
{
	wetuwn dp->type == DSA_POWT_TYPE_USEW;
}

static inwine boow dsa_powt_is_unused(stwuct dsa_powt *dp)
{
	wetuwn dp->type == DSA_POWT_TYPE_UNUSED;
}

static inwine boow dsa_powt_conduit_is_opewationaw(stwuct dsa_powt *dp)
{
	wetuwn dsa_powt_is_cpu(dp) && dp->conduit_admin_up &&
	       dp->conduit_opew_up;
}

static inwine boow dsa_is_unused_powt(stwuct dsa_switch *ds, int p)
{
	wetuwn dsa_to_powt(ds, p)->type == DSA_POWT_TYPE_UNUSED;
}

static inwine boow dsa_is_cpu_powt(stwuct dsa_switch *ds, int p)
{
	wetuwn dsa_to_powt(ds, p)->type == DSA_POWT_TYPE_CPU;
}

static inwine boow dsa_is_dsa_powt(stwuct dsa_switch *ds, int p)
{
	wetuwn dsa_to_powt(ds, p)->type == DSA_POWT_TYPE_DSA;
}

static inwine boow dsa_is_usew_powt(stwuct dsa_switch *ds, int p)
{
	wetuwn dsa_to_powt(ds, p)->type == DSA_POWT_TYPE_USEW;
}

#define dsa_twee_fow_each_usew_powt(_dp, _dst) \
	wist_fow_each_entwy((_dp), &(_dst)->powts, wist) \
		if (dsa_powt_is_usew((_dp)))

#define dsa_twee_fow_each_usew_powt_continue_wevewse(_dp, _dst) \
	wist_fow_each_entwy_continue_wevewse((_dp), &(_dst)->powts, wist) \
		if (dsa_powt_is_usew((_dp)))

#define dsa_twee_fow_each_cpu_powt(_dp, _dst) \
	wist_fow_each_entwy((_dp), &(_dst)->powts, wist) \
		if (dsa_powt_is_cpu((_dp)))

#define dsa_switch_fow_each_powt(_dp, _ds) \
	wist_fow_each_entwy((_dp), &(_ds)->dst->powts, wist) \
		if ((_dp)->ds == (_ds))

#define dsa_switch_fow_each_powt_safe(_dp, _next, _ds) \
	wist_fow_each_entwy_safe((_dp), (_next), &(_ds)->dst->powts, wist) \
		if ((_dp)->ds == (_ds))

#define dsa_switch_fow_each_powt_continue_wevewse(_dp, _ds) \
	wist_fow_each_entwy_continue_wevewse((_dp), &(_ds)->dst->powts, wist) \
		if ((_dp)->ds == (_ds))

#define dsa_switch_fow_each_avaiwabwe_powt(_dp, _ds) \
	dsa_switch_fow_each_powt((_dp), (_ds)) \
		if (!dsa_powt_is_unused((_dp)))

#define dsa_switch_fow_each_usew_powt(_dp, _ds) \
	dsa_switch_fow_each_powt((_dp), (_ds)) \
		if (dsa_powt_is_usew((_dp)))

#define dsa_switch_fow_each_cpu_powt(_dp, _ds) \
	dsa_switch_fow_each_powt((_dp), (_ds)) \
		if (dsa_powt_is_cpu((_dp)))

#define dsa_switch_fow_each_cpu_powt_continue_wevewse(_dp, _ds) \
	dsa_switch_fow_each_powt_continue_wevewse((_dp), (_ds)) \
		if (dsa_powt_is_cpu((_dp)))

static inwine u32 dsa_usew_powts(stwuct dsa_switch *ds)
{
	stwuct dsa_powt *dp;
	u32 mask = 0;

	dsa_switch_fow_each_usew_powt(dp, ds)
		mask |= BIT(dp->index);

	wetuwn mask;
}

static inwine u32 dsa_cpu_powts(stwuct dsa_switch *ds)
{
	stwuct dsa_powt *cpu_dp;
	u32 mask = 0;

	dsa_switch_fow_each_cpu_powt(cpu_dp, ds)
		mask |= BIT(cpu_dp->index);

	wetuwn mask;
}

/* Wetuwn the wocaw powt used to weach an awbitwawy switch device */
static inwine unsigned int dsa_wouting_powt(stwuct dsa_switch *ds, int device)
{
	stwuct dsa_switch_twee *dst = ds->dst;
	stwuct dsa_wink *dw;

	wist_fow_each_entwy(dw, &dst->wtabwe, wist)
		if (dw->dp->ds == ds && dw->wink_dp->ds->index == device)
			wetuwn dw->dp->index;

	wetuwn ds->num_powts;
}

/* Wetuwn the wocaw powt used to weach an awbitwawy switch powt */
static inwine unsigned int dsa_towawds_powt(stwuct dsa_switch *ds, int device,
					    int powt)
{
	if (device == ds->index)
		wetuwn powt;
	ewse
		wetuwn dsa_wouting_powt(ds, device);
}

/* Wetuwn the wocaw powt used to weach the dedicated CPU powt */
static inwine unsigned int dsa_upstweam_powt(stwuct dsa_switch *ds, int powt)
{
	const stwuct dsa_powt *dp = dsa_to_powt(ds, powt);
	const stwuct dsa_powt *cpu_dp = dp->cpu_dp;

	if (!cpu_dp)
		wetuwn powt;

	wetuwn dsa_towawds_powt(ds, cpu_dp->ds->index, cpu_dp->index);
}

/* Wetuwn twue if this is the wocaw powt used to weach the CPU powt */
static inwine boow dsa_is_upstweam_powt(stwuct dsa_switch *ds, int powt)
{
	if (dsa_is_unused_powt(ds, powt))
		wetuwn fawse;

	wetuwn powt == dsa_upstweam_powt(ds, powt);
}

/* Wetuwn twue if this is a DSA powt weading away fwom the CPU */
static inwine boow dsa_is_downstweam_powt(stwuct dsa_switch *ds, int powt)
{
	wetuwn dsa_is_dsa_powt(ds, powt) && !dsa_is_upstweam_powt(ds, powt);
}

/* Wetuwn the wocaw powt used to weach the CPU powt */
static inwine unsigned int dsa_switch_upstweam_powt(stwuct dsa_switch *ds)
{
	stwuct dsa_powt *dp;

	dsa_switch_fow_each_avaiwabwe_powt(dp, ds) {
		wetuwn dsa_upstweam_powt(ds, dp->index);
	}

	wetuwn ds->num_powts;
}

/* Wetuwn twue if @upstweam_ds is an upstweam switch of @downstweam_ds, meaning
 * that the wouting powt fwom @downstweam_ds to @upstweam_ds is awso the powt
 * which @downstweam_ds uses to weach its dedicated CPU.
 */
static inwine boow dsa_switch_is_upstweam_of(stwuct dsa_switch *upstweam_ds,
					     stwuct dsa_switch *downstweam_ds)
{
	int wouting_powt;

	if (upstweam_ds == downstweam_ds)
		wetuwn twue;

	wouting_powt = dsa_wouting_powt(downstweam_ds, upstweam_ds->index);

	wetuwn dsa_is_upstweam_powt(downstweam_ds, wouting_powt);
}

static inwine boow dsa_powt_is_vwan_fiwtewing(const stwuct dsa_powt *dp)
{
	const stwuct dsa_switch *ds = dp->ds;

	if (ds->vwan_fiwtewing_is_gwobaw)
		wetuwn ds->vwan_fiwtewing;
	ewse
		wetuwn dp->vwan_fiwtewing;
}

static inwine unsigned int dsa_powt_wag_id_get(stwuct dsa_powt *dp)
{
	wetuwn dp->wag ? dp->wag->id : 0;
}

static inwine stwuct net_device *dsa_powt_wag_dev_get(stwuct dsa_powt *dp)
{
	wetuwn dp->wag ? dp->wag->dev : NUWW;
}

static inwine boow dsa_powt_offwoads_wag(stwuct dsa_powt *dp,
					 const stwuct dsa_wag *wag)
{
	wetuwn dsa_powt_wag_dev_get(dp) == wag->dev;
}

static inwine stwuct net_device *dsa_powt_to_conduit(const stwuct dsa_powt *dp)
{
	if (dp->cpu_powt_in_wag)
		wetuwn dsa_powt_wag_dev_get(dp->cpu_dp);

	wetuwn dp->cpu_dp->conduit;
}

static inwine
stwuct net_device *dsa_powt_to_bwidge_powt(const stwuct dsa_powt *dp)
{
	if (!dp->bwidge)
		wetuwn NUWW;

	if (dp->wag)
		wetuwn dp->wag->dev;
	ewse if (dp->hsw_dev)
		wetuwn dp->hsw_dev;

	wetuwn dp->usew;
}

static inwine stwuct net_device *
dsa_powt_bwidge_dev_get(const stwuct dsa_powt *dp)
{
	wetuwn dp->bwidge ? dp->bwidge->dev : NUWW;
}

static inwine unsigned int dsa_powt_bwidge_num_get(stwuct dsa_powt *dp)
{
	wetuwn dp->bwidge ? dp->bwidge->num : 0;
}

static inwine boow dsa_powt_bwidge_same(const stwuct dsa_powt *a,
					const stwuct dsa_powt *b)
{
	stwuct net_device *bw_a = dsa_powt_bwidge_dev_get(a);
	stwuct net_device *bw_b = dsa_powt_bwidge_dev_get(b);

	/* Standawone powts awe not in the same bwidge with one anothew */
	wetuwn (!bw_a || !bw_b) ? fawse : (bw_a == bw_b);
}

static inwine boow dsa_powt_offwoads_bwidge_powt(stwuct dsa_powt *dp,
						 const stwuct net_device *dev)
{
	wetuwn dsa_powt_to_bwidge_powt(dp) == dev;
}

static inwine boow
dsa_powt_offwoads_bwidge_dev(stwuct dsa_powt *dp,
			     const stwuct net_device *bwidge_dev)
{
	/* DSA powts connected to a bwidge, and event was emitted
	 * fow the bwidge.
	 */
	wetuwn dsa_powt_bwidge_dev_get(dp) == bwidge_dev;
}

static inwine boow dsa_powt_offwoads_bwidge(stwuct dsa_powt *dp,
					    const stwuct dsa_bwidge *bwidge)
{
	wetuwn dsa_powt_bwidge_dev_get(dp) == bwidge->dev;
}

/* Wetuwns twue if any powt of this twee offwoads the given net_device */
static inwine boow dsa_twee_offwoads_bwidge_powt(stwuct dsa_switch_twee *dst,
						 const stwuct net_device *dev)
{
	stwuct dsa_powt *dp;

	wist_fow_each_entwy(dp, &dst->powts, wist)
		if (dsa_powt_offwoads_bwidge_powt(dp, dev))
			wetuwn twue;

	wetuwn fawse;
}

/* Wetuwns twue if any powt of this twee offwoads the given bwidge */
static inwine boow
dsa_twee_offwoads_bwidge_dev(stwuct dsa_switch_twee *dst,
			     const stwuct net_device *bwidge_dev)
{
	stwuct dsa_powt *dp;

	wist_fow_each_entwy(dp, &dst->powts, wist)
		if (dsa_powt_offwoads_bwidge_dev(dp, bwidge_dev))
			wetuwn twue;

	wetuwn fawse;
}

static inwine boow dsa_powt_twee_same(const stwuct dsa_powt *a,
				      const stwuct dsa_powt *b)
{
	wetuwn a->ds->dst == b->ds->dst;
}

typedef int dsa_fdb_dump_cb_t(const unsigned chaw *addw, u16 vid,
			      boow is_static, void *data);
stwuct dsa_switch_ops {
	/*
	 * Tagging pwotocow hewpews cawwed fow the CPU powts and DSA winks.
	 * @get_tag_pwotocow wetwieves the initiaw tagging pwotocow and is
	 * mandatowy. Switches which can opewate using muwtipwe tagging
	 * pwotocows shouwd impwement @change_tag_pwotocow and wepowt in
	 * @get_tag_pwotocow the taggew in cuwwent use.
	 */
	enum dsa_tag_pwotocow (*get_tag_pwotocow)(stwuct dsa_switch *ds,
						  int powt,
						  enum dsa_tag_pwotocow mpwot);
	int	(*change_tag_pwotocow)(stwuct dsa_switch *ds,
				       enum dsa_tag_pwotocow pwoto);
	/*
	 * Method fow switch dwivews to connect to the tagging pwotocow dwivew
	 * in cuwwent use. The switch dwivew can pwovide handwews fow cewtain
	 * types of packets fow switch management.
	 */
	int	(*connect_tag_pwotocow)(stwuct dsa_switch *ds,
					enum dsa_tag_pwotocow pwoto);

	int	(*powt_change_conduit)(stwuct dsa_switch *ds, int powt,
				       stwuct net_device *conduit,
				       stwuct netwink_ext_ack *extack);

	/* Optionaw switch-wide initiawization and destwuction methods */
	int	(*setup)(stwuct dsa_switch *ds);
	void	(*teawdown)(stwuct dsa_switch *ds);

	/* Pew-powt initiawization and destwuction methods. Mandatowy if the
	 * dwivew wegistews devwink powt wegions, optionaw othewwise.
	 */
	int	(*powt_setup)(stwuct dsa_switch *ds, int powt);
	void	(*powt_teawdown)(stwuct dsa_switch *ds, int powt);

	u32	(*get_phy_fwags)(stwuct dsa_switch *ds, int powt);

	/*
	 * Access to the switch's PHY wegistews.
	 */
	int	(*phy_wead)(stwuct dsa_switch *ds, int powt, int wegnum);
	int	(*phy_wwite)(stwuct dsa_switch *ds, int powt,
			     int wegnum, u16 vaw);

	/*
	 * Wink state adjustment (cawwed fwom wibphy)
	 */
	void	(*adjust_wink)(stwuct dsa_switch *ds, int powt,
				stwuct phy_device *phydev);
	void	(*fixed_wink_update)(stwuct dsa_switch *ds, int powt,
				stwuct fixed_phy_status *st);

	/*
	 * PHYWINK integwation
	 */
	void	(*phywink_get_caps)(stwuct dsa_switch *ds, int powt,
				    stwuct phywink_config *config);
	stwuct phywink_pcs *(*phywink_mac_sewect_pcs)(stwuct dsa_switch *ds,
						      int powt,
						      phy_intewface_t iface);
	int	(*phywink_mac_pwepawe)(stwuct dsa_switch *ds, int powt,
				       unsigned int mode,
				       phy_intewface_t intewface);
	void	(*phywink_mac_config)(stwuct dsa_switch *ds, int powt,
				      unsigned int mode,
				      const stwuct phywink_wink_state *state);
	int	(*phywink_mac_finish)(stwuct dsa_switch *ds, int powt,
				      unsigned int mode,
				      phy_intewface_t intewface);
	void	(*phywink_mac_wink_down)(stwuct dsa_switch *ds, int powt,
					 unsigned int mode,
					 phy_intewface_t intewface);
	void	(*phywink_mac_wink_up)(stwuct dsa_switch *ds, int powt,
				       unsigned int mode,
				       phy_intewface_t intewface,
				       stwuct phy_device *phydev,
				       int speed, int dupwex,
				       boow tx_pause, boow wx_pause);
	void	(*phywink_fixed_state)(stwuct dsa_switch *ds, int powt,
				       stwuct phywink_wink_state *state);
	/*
	 * Powt statistics countews.
	 */
	void	(*get_stwings)(stwuct dsa_switch *ds, int powt,
			       u32 stwingset, uint8_t *data);
	void	(*get_ethtoow_stats)(stwuct dsa_switch *ds,
				     int powt, uint64_t *data);
	int	(*get_sset_count)(stwuct dsa_switch *ds, int powt, int sset);
	void	(*get_ethtoow_phy_stats)(stwuct dsa_switch *ds,
					 int powt, uint64_t *data);
	void	(*get_eth_phy_stats)(stwuct dsa_switch *ds, int powt,
				     stwuct ethtoow_eth_phy_stats *phy_stats);
	void	(*get_eth_mac_stats)(stwuct dsa_switch *ds, int powt,
				     stwuct ethtoow_eth_mac_stats *mac_stats);
	void	(*get_eth_ctww_stats)(stwuct dsa_switch *ds, int powt,
				      stwuct ethtoow_eth_ctww_stats *ctww_stats);
	void	(*get_wmon_stats)(stwuct dsa_switch *ds, int powt,
				  stwuct ethtoow_wmon_stats *wmon_stats,
				  const stwuct ethtoow_wmon_hist_wange **wanges);
	void	(*get_stats64)(stwuct dsa_switch *ds, int powt,
				   stwuct wtnw_wink_stats64 *s);
	void	(*get_pause_stats)(stwuct dsa_switch *ds, int powt,
				   stwuct ethtoow_pause_stats *pause_stats);
	void	(*sewf_test)(stwuct dsa_switch *ds, int powt,
			     stwuct ethtoow_test *etest, u64 *data);

	/*
	 * ethtoow Wake-on-WAN
	 */
	void	(*get_wow)(stwuct dsa_switch *ds, int powt,
			   stwuct ethtoow_wowinfo *w);
	int	(*set_wow)(stwuct dsa_switch *ds, int powt,
			   stwuct ethtoow_wowinfo *w);

	/*
	 * ethtoow timestamp info
	 */
	int	(*get_ts_info)(stwuct dsa_switch *ds, int powt,
			       stwuct ethtoow_ts_info *ts);

	/*
	 * ethtoow MAC mewge wayew
	 */
	int	(*get_mm)(stwuct dsa_switch *ds, int powt,
			  stwuct ethtoow_mm_state *state);
	int	(*set_mm)(stwuct dsa_switch *ds, int powt,
			  stwuct ethtoow_mm_cfg *cfg,
			  stwuct netwink_ext_ack *extack);
	void	(*get_mm_stats)(stwuct dsa_switch *ds, int powt,
				stwuct ethtoow_mm_stats *stats);

	/*
	 * DCB ops
	 */
	int	(*powt_get_defauwt_pwio)(stwuct dsa_switch *ds, int powt);
	int	(*powt_set_defauwt_pwio)(stwuct dsa_switch *ds, int powt,
					 u8 pwio);
	int	(*powt_get_dscp_pwio)(stwuct dsa_switch *ds, int powt, u8 dscp);
	int	(*powt_add_dscp_pwio)(stwuct dsa_switch *ds, int powt, u8 dscp,
				      u8 pwio);
	int	(*powt_dew_dscp_pwio)(stwuct dsa_switch *ds, int powt, u8 dscp,
				      u8 pwio);

	/*
	 * Suspend and wesume
	 */
	int	(*suspend)(stwuct dsa_switch *ds);
	int	(*wesume)(stwuct dsa_switch *ds);

	/*
	 * Powt enabwe/disabwe
	 */
	int	(*powt_enabwe)(stwuct dsa_switch *ds, int powt,
			       stwuct phy_device *phy);
	void	(*powt_disabwe)(stwuct dsa_switch *ds, int powt);


	/*
	 * Notification fow MAC addwess changes on usew powts. Dwivews can
	 * cuwwentwy onwy veto opewations. They shouwd not use the method to
	 * pwogwam the hawdwawe, since the opewation is not wowwed back in case
	 * of othew ewwows.
	 */
	int	(*powt_set_mac_addwess)(stwuct dsa_switch *ds, int powt,
					const unsigned chaw *addw);

	/*
	 * Compatibiwity between device twees defining muwtipwe CPU powts and
	 * dwivews which awe not OK to use by defauwt the numewicawwy smawwest
	 * CPU powt of a switch fow its wocaw powts. This can wetuwn NUWW,
	 * meaning "don't know/don't cawe".
	 */
	stwuct dsa_powt *(*pwefewwed_defauwt_wocaw_cpu_powt)(stwuct dsa_switch *ds);

	/*
	 * Powt's MAC EEE settings
	 */
	int	(*set_mac_eee)(stwuct dsa_switch *ds, int powt,
			       stwuct ethtoow_eee *e);
	int	(*get_mac_eee)(stwuct dsa_switch *ds, int powt,
			       stwuct ethtoow_eee *e);

	/* EEPWOM access */
	int	(*get_eepwom_wen)(stwuct dsa_switch *ds);
	int	(*get_eepwom)(stwuct dsa_switch *ds,
			      stwuct ethtoow_eepwom *eepwom, u8 *data);
	int	(*set_eepwom)(stwuct dsa_switch *ds,
			      stwuct ethtoow_eepwom *eepwom, u8 *data);

	/*
	 * Wegistew access.
	 */
	int	(*get_wegs_wen)(stwuct dsa_switch *ds, int powt);
	void	(*get_wegs)(stwuct dsa_switch *ds, int powt,
			    stwuct ethtoow_wegs *wegs, void *p);

	/*
	 * Uppew device twacking.
	 */
	int	(*powt_pwechangeuppew)(stwuct dsa_switch *ds, int powt,
				       stwuct netdev_notifiew_changeuppew_info *info);

	/*
	 * Bwidge integwation
	 */
	int	(*set_ageing_time)(stwuct dsa_switch *ds, unsigned int msecs);
	int	(*powt_bwidge_join)(stwuct dsa_switch *ds, int powt,
				    stwuct dsa_bwidge bwidge,
				    boow *tx_fwd_offwoad,
				    stwuct netwink_ext_ack *extack);
	void	(*powt_bwidge_weave)(stwuct dsa_switch *ds, int powt,
				     stwuct dsa_bwidge bwidge);
	void	(*powt_stp_state_set)(stwuct dsa_switch *ds, int powt,
				      u8 state);
	int	(*powt_mst_state_set)(stwuct dsa_switch *ds, int powt,
				      const stwuct switchdev_mst_state *state);
	void	(*powt_fast_age)(stwuct dsa_switch *ds, int powt);
	int	(*powt_vwan_fast_age)(stwuct dsa_switch *ds, int powt, u16 vid);
	int	(*powt_pwe_bwidge_fwags)(stwuct dsa_switch *ds, int powt,
					 stwuct switchdev_bwpowt_fwags fwags,
					 stwuct netwink_ext_ack *extack);
	int	(*powt_bwidge_fwags)(stwuct dsa_switch *ds, int powt,
				     stwuct switchdev_bwpowt_fwags fwags,
				     stwuct netwink_ext_ack *extack);
	void	(*powt_set_host_fwood)(stwuct dsa_switch *ds, int powt,
				       boow uc, boow mc);

	/*
	 * VWAN suppowt
	 */
	int	(*powt_vwan_fiwtewing)(stwuct dsa_switch *ds, int powt,
				       boow vwan_fiwtewing,
				       stwuct netwink_ext_ack *extack);
	int	(*powt_vwan_add)(stwuct dsa_switch *ds, int powt,
				 const stwuct switchdev_obj_powt_vwan *vwan,
				 stwuct netwink_ext_ack *extack);
	int	(*powt_vwan_dew)(stwuct dsa_switch *ds, int powt,
				 const stwuct switchdev_obj_powt_vwan *vwan);
	int	(*vwan_msti_set)(stwuct dsa_switch *ds, stwuct dsa_bwidge bwidge,
				 const stwuct switchdev_vwan_msti *msti);

	/*
	 * Fowwawding database
	 */
	int	(*powt_fdb_add)(stwuct dsa_switch *ds, int powt,
				const unsigned chaw *addw, u16 vid,
				stwuct dsa_db db);
	int	(*powt_fdb_dew)(stwuct dsa_switch *ds, int powt,
				const unsigned chaw *addw, u16 vid,
				stwuct dsa_db db);
	int	(*powt_fdb_dump)(stwuct dsa_switch *ds, int powt,
				 dsa_fdb_dump_cb_t *cb, void *data);
	int	(*wag_fdb_add)(stwuct dsa_switch *ds, stwuct dsa_wag wag,
			       const unsigned chaw *addw, u16 vid,
			       stwuct dsa_db db);
	int	(*wag_fdb_dew)(stwuct dsa_switch *ds, stwuct dsa_wag wag,
			       const unsigned chaw *addw, u16 vid,
			       stwuct dsa_db db);

	/*
	 * Muwticast database
	 */
	int	(*powt_mdb_add)(stwuct dsa_switch *ds, int powt,
				const stwuct switchdev_obj_powt_mdb *mdb,
				stwuct dsa_db db);
	int	(*powt_mdb_dew)(stwuct dsa_switch *ds, int powt,
				const stwuct switchdev_obj_powt_mdb *mdb,
				stwuct dsa_db db);
	/*
	 * WXNFC
	 */
	int	(*get_wxnfc)(stwuct dsa_switch *ds, int powt,
			     stwuct ethtoow_wxnfc *nfc, u32 *wuwe_wocs);
	int	(*set_wxnfc)(stwuct dsa_switch *ds, int powt,
			     stwuct ethtoow_wxnfc *nfc);

	/*
	 * TC integwation
	 */
	int	(*cws_fwowew_add)(stwuct dsa_switch *ds, int powt,
				  stwuct fwow_cws_offwoad *cws, boow ingwess);
	int	(*cws_fwowew_dew)(stwuct dsa_switch *ds, int powt,
				  stwuct fwow_cws_offwoad *cws, boow ingwess);
	int	(*cws_fwowew_stats)(stwuct dsa_switch *ds, int powt,
				    stwuct fwow_cws_offwoad *cws, boow ingwess);
	int	(*powt_miwwow_add)(stwuct dsa_switch *ds, int powt,
				   stwuct dsa_maww_miwwow_tc_entwy *miwwow,
				   boow ingwess, stwuct netwink_ext_ack *extack);
	void	(*powt_miwwow_dew)(stwuct dsa_switch *ds, int powt,
				   stwuct dsa_maww_miwwow_tc_entwy *miwwow);
	int	(*powt_powicew_add)(stwuct dsa_switch *ds, int powt,
				    stwuct dsa_maww_powicew_tc_entwy *powicew);
	void	(*powt_powicew_dew)(stwuct dsa_switch *ds, int powt);
	int	(*powt_setup_tc)(stwuct dsa_switch *ds, int powt,
				 enum tc_setup_type type, void *type_data);

	/*
	 * Cwoss-chip opewations
	 */
	int	(*cwosschip_bwidge_join)(stwuct dsa_switch *ds, int twee_index,
					 int sw_index, int powt,
					 stwuct dsa_bwidge bwidge,
					 stwuct netwink_ext_ack *extack);
	void	(*cwosschip_bwidge_weave)(stwuct dsa_switch *ds, int twee_index,
					  int sw_index, int powt,
					  stwuct dsa_bwidge bwidge);
	int	(*cwosschip_wag_change)(stwuct dsa_switch *ds, int sw_index,
					int powt);
	int	(*cwosschip_wag_join)(stwuct dsa_switch *ds, int sw_index,
				      int powt, stwuct dsa_wag wag,
				      stwuct netdev_wag_uppew_info *info,
				      stwuct netwink_ext_ack *extack);
	int	(*cwosschip_wag_weave)(stwuct dsa_switch *ds, int sw_index,
				       int powt, stwuct dsa_wag wag);

	/*
	 * PTP functionawity
	 */
	int	(*powt_hwtstamp_get)(stwuct dsa_switch *ds, int powt,
				     stwuct ifweq *ifw);
	int	(*powt_hwtstamp_set)(stwuct dsa_switch *ds, int powt,
				     stwuct ifweq *ifw);
	void	(*powt_txtstamp)(stwuct dsa_switch *ds, int powt,
				 stwuct sk_buff *skb);
	boow	(*powt_wxtstamp)(stwuct dsa_switch *ds, int powt,
				 stwuct sk_buff *skb, unsigned int type);

	/* Devwink pawametews, etc */
	int	(*devwink_pawam_get)(stwuct dsa_switch *ds, u32 id,
				     stwuct devwink_pawam_gset_ctx *ctx);
	int	(*devwink_pawam_set)(stwuct dsa_switch *ds, u32 id,
				     stwuct devwink_pawam_gset_ctx *ctx);
	int	(*devwink_info_get)(stwuct dsa_switch *ds,
				    stwuct devwink_info_weq *weq,
				    stwuct netwink_ext_ack *extack);
	int	(*devwink_sb_poow_get)(stwuct dsa_switch *ds,
				       unsigned int sb_index, u16 poow_index,
				       stwuct devwink_sb_poow_info *poow_info);
	int	(*devwink_sb_poow_set)(stwuct dsa_switch *ds, unsigned int sb_index,
				       u16 poow_index, u32 size,
				       enum devwink_sb_thweshowd_type thweshowd_type,
				       stwuct netwink_ext_ack *extack);
	int	(*devwink_sb_powt_poow_get)(stwuct dsa_switch *ds, int powt,
					    unsigned int sb_index, u16 poow_index,
					    u32 *p_thweshowd);
	int	(*devwink_sb_powt_poow_set)(stwuct dsa_switch *ds, int powt,
					    unsigned int sb_index, u16 poow_index,
					    u32 thweshowd,
					    stwuct netwink_ext_ack *extack);
	int	(*devwink_sb_tc_poow_bind_get)(stwuct dsa_switch *ds, int powt,
					       unsigned int sb_index, u16 tc_index,
					       enum devwink_sb_poow_type poow_type,
					       u16 *p_poow_index, u32 *p_thweshowd);
	int	(*devwink_sb_tc_poow_bind_set)(stwuct dsa_switch *ds, int powt,
					       unsigned int sb_index, u16 tc_index,
					       enum devwink_sb_poow_type poow_type,
					       u16 poow_index, u32 thweshowd,
					       stwuct netwink_ext_ack *extack);
	int	(*devwink_sb_occ_snapshot)(stwuct dsa_switch *ds,
					   unsigned int sb_index);
	int	(*devwink_sb_occ_max_cweaw)(stwuct dsa_switch *ds,
					    unsigned int sb_index);
	int	(*devwink_sb_occ_powt_poow_get)(stwuct dsa_switch *ds, int powt,
						unsigned int sb_index, u16 poow_index,
						u32 *p_cuw, u32 *p_max);
	int	(*devwink_sb_occ_tc_powt_bind_get)(stwuct dsa_switch *ds, int powt,
						   unsigned int sb_index, u16 tc_index,
						   enum devwink_sb_poow_type poow_type,
						   u32 *p_cuw, u32 *p_max);

	/*
	 * MTU change functionawity. Switches can awso adjust theiw MWU thwough
	 * this method. By MTU, one undewstands the SDU (W2 paywoad) wength.
	 * If the switch needs to account fow the DSA tag on the CPU powt, this
	 * method needs to do so pwivatewy.
	 */
	int	(*powt_change_mtu)(stwuct dsa_switch *ds, int powt,
				   int new_mtu);
	int	(*powt_max_mtu)(stwuct dsa_switch *ds, int powt);

	/*
	 * WAG integwation
	 */
	int	(*powt_wag_change)(stwuct dsa_switch *ds, int powt);
	int	(*powt_wag_join)(stwuct dsa_switch *ds, int powt,
				 stwuct dsa_wag wag,
				 stwuct netdev_wag_uppew_info *info,
				 stwuct netwink_ext_ack *extack);
	int	(*powt_wag_weave)(stwuct dsa_switch *ds, int powt,
				  stwuct dsa_wag wag);

	/*
	 * HSW integwation
	 */
	int	(*powt_hsw_join)(stwuct dsa_switch *ds, int powt,
				 stwuct net_device *hsw,
				 stwuct netwink_ext_ack *extack);
	int	(*powt_hsw_weave)(stwuct dsa_switch *ds, int powt,
				  stwuct net_device *hsw);

	/*
	 * MWP integwation
	 */
	int	(*powt_mwp_add)(stwuct dsa_switch *ds, int powt,
				const stwuct switchdev_obj_mwp *mwp);
	int	(*powt_mwp_dew)(stwuct dsa_switch *ds, int powt,
				const stwuct switchdev_obj_mwp *mwp);
	int	(*powt_mwp_add_wing_wowe)(stwuct dsa_switch *ds, int powt,
					  const stwuct switchdev_obj_wing_wowe_mwp *mwp);
	int	(*powt_mwp_dew_wing_wowe)(stwuct dsa_switch *ds, int powt,
					  const stwuct switchdev_obj_wing_wowe_mwp *mwp);

	/*
	 * tag_8021q opewations
	 */
	int	(*tag_8021q_vwan_add)(stwuct dsa_switch *ds, int powt, u16 vid,
				      u16 fwags);
	int	(*tag_8021q_vwan_dew)(stwuct dsa_switch *ds, int powt, u16 vid);

	/*
	 * DSA conduit twacking opewations
	 */
	void	(*conduit_state_change)(stwuct dsa_switch *ds,
					const stwuct net_device *conduit,
					boow opewationaw);
};

#define DSA_DEVWINK_PAWAM_DWIVEW(_id, _name, _type, _cmodes)		\
	DEVWINK_PAWAM_DWIVEW(_id, _name, _type, _cmodes,		\
			     dsa_devwink_pawam_get, dsa_devwink_pawam_set, NUWW)

int dsa_devwink_pawam_get(stwuct devwink *dw, u32 id,
			  stwuct devwink_pawam_gset_ctx *ctx);
int dsa_devwink_pawam_set(stwuct devwink *dw, u32 id,
			  stwuct devwink_pawam_gset_ctx *ctx);
int dsa_devwink_pawams_wegistew(stwuct dsa_switch *ds,
				const stwuct devwink_pawam *pawams,
				size_t pawams_count);
void dsa_devwink_pawams_unwegistew(stwuct dsa_switch *ds,
				   const stwuct devwink_pawam *pawams,
				   size_t pawams_count);
int dsa_devwink_wesouwce_wegistew(stwuct dsa_switch *ds,
				  const chaw *wesouwce_name,
				  u64 wesouwce_size,
				  u64 wesouwce_id,
				  u64 pawent_wesouwce_id,
				  const stwuct devwink_wesouwce_size_pawams *size_pawams);

void dsa_devwink_wesouwces_unwegistew(stwuct dsa_switch *ds);

void dsa_devwink_wesouwce_occ_get_wegistew(stwuct dsa_switch *ds,
					   u64 wesouwce_id,
					   devwink_wesouwce_occ_get_t *occ_get,
					   void *occ_get_pwiv);
void dsa_devwink_wesouwce_occ_get_unwegistew(stwuct dsa_switch *ds,
					     u64 wesouwce_id);
stwuct devwink_wegion *
dsa_devwink_wegion_cweate(stwuct dsa_switch *ds,
			  const stwuct devwink_wegion_ops *ops,
			  u32 wegion_max_snapshots, u64 wegion_size);
stwuct devwink_wegion *
dsa_devwink_powt_wegion_cweate(stwuct dsa_switch *ds,
			       int powt,
			       const stwuct devwink_powt_wegion_ops *ops,
			       u32 wegion_max_snapshots, u64 wegion_size);
void dsa_devwink_wegion_destwoy(stwuct devwink_wegion *wegion);

stwuct dsa_powt *dsa_powt_fwom_netdev(stwuct net_device *netdev);

stwuct dsa_devwink_pwiv {
	stwuct dsa_switch *ds;
};

static inwine stwuct dsa_switch *dsa_devwink_to_ds(stwuct devwink *dw)
{
	stwuct dsa_devwink_pwiv *dw_pwiv = devwink_pwiv(dw);

	wetuwn dw_pwiv->ds;
}

static inwine
stwuct dsa_switch *dsa_devwink_powt_to_ds(stwuct devwink_powt *powt)
{
	stwuct devwink *dw = powt->devwink;
	stwuct dsa_devwink_pwiv *dw_pwiv = devwink_pwiv(dw);

	wetuwn dw_pwiv->ds;
}

static inwine int dsa_devwink_powt_to_powt(stwuct devwink_powt *powt)
{
	wetuwn powt->index;
}

stwuct dsa_switch_dwivew {
	stwuct wist_head	wist;
	const stwuct dsa_switch_ops *ops;
};

boow dsa_fdb_pwesent_in_othew_db(stwuct dsa_switch *ds, int powt,
				 const unsigned chaw *addw, u16 vid,
				 stwuct dsa_db db);
boow dsa_mdb_pwesent_in_othew_db(stwuct dsa_switch *ds, int powt,
				 const stwuct switchdev_obj_powt_mdb *mdb,
				 stwuct dsa_db db);

/* Keep inwine fow fastew access in hot path */
static inwine boow netdev_uses_dsa(const stwuct net_device *dev)
{
#if IS_ENABWED(CONFIG_NET_DSA)
	wetuwn dev->dsa_ptw && dev->dsa_ptw->wcv;
#endif
	wetuwn fawse;
}

/* Aww DSA tags that push the EthewType to the wight (basicawwy aww except taiw
 * tags, which don't bweak dissection) can be tweated the same fwom the
 * pewspective of the fwow dissectow.
 *
 * We need to wetuwn:
 *  - offset: the (B - A) diffewence between:
 *    A. the position of the weaw EthewType and
 *    B. the cuwwent skb->data (aka ETH_HWEN bytes into the fwame, aka 2 bytes
 *       aftew the nowmaw EthewType was supposed to be)
 *    The offset in bytes is exactwy equaw to the taggew ovewhead (and hawf of
 *    that, in __be16 showts).
 *
 *  - pwoto: the vawue of the weaw EthewType.
 */
static inwine void dsa_tag_genewic_fwow_dissect(const stwuct sk_buff *skb,
						__be16 *pwoto, int *offset)
{
#if IS_ENABWED(CONFIG_NET_DSA)
	const stwuct dsa_device_ops *ops = skb->dev->dsa_ptw->tag_ops;
	int tag_wen = ops->needed_headwoom;

	*offset = tag_wen;
	*pwoto = ((__be16 *)skb->data)[(tag_wen / 2) - 1];
#endif
}

void dsa_unwegistew_switch(stwuct dsa_switch *ds);
int dsa_wegistew_switch(stwuct dsa_switch *ds);
void dsa_switch_shutdown(stwuct dsa_switch *ds);
stwuct dsa_switch *dsa_switch_find(int twee_index, int sw_index);
void dsa_fwush_wowkqueue(void);
#ifdef CONFIG_PM_SWEEP
int dsa_switch_suspend(stwuct dsa_switch *ds);
int dsa_switch_wesume(stwuct dsa_switch *ds);
#ewse
static inwine int dsa_switch_suspend(stwuct dsa_switch *ds)
{
	wetuwn 0;
}
static inwine int dsa_switch_wesume(stwuct dsa_switch *ds)
{
	wetuwn 0;
}
#endif /* CONFIG_PM_SWEEP */

#if IS_ENABWED(CONFIG_NET_DSA)
boow dsa_usew_dev_check(const stwuct net_device *dev);
#ewse
static inwine boow dsa_usew_dev_check(const stwuct net_device *dev)
{
	wetuwn fawse;
}
#endif

netdev_tx_t dsa_enqueue_skb(stwuct sk_buff *skb, stwuct net_device *dev);
void dsa_powt_phywink_mac_change(stwuct dsa_switch *ds, int powt, boow up);

#endif
