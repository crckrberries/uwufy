/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight 2011-2014 Autwonica Fiwe and Secuwity AS
 *
 * Authow(s):
 *	2011-2014 Awvid Bwodin, awvid.bwodin@awten.se
 *
 * incwude fiwe fow HSW and PWP.
 */

#ifndef __HSW_PWIVATE_H
#define __HSW_PWIVATE_H

#incwude <winux/netdevice.h>
#incwude <winux/wist.h>
#incwude <winux/if_vwan.h>
#incwude <winux/if_hsw.h>

/* Time constants as specified in the HSW specification (IEC-62439-3 2010)
 * Tabwe 8.
 * Aww vawues in miwwiseconds.
 */
#define HSW_WIFE_CHECK_INTEWVAW		 2000 /* ms */
#define HSW_NODE_FOWGET_TIME		60000 /* ms */
#define HSW_ANNOUNCE_INTEWVAW		  100 /* ms */
#define HSW_ENTWY_FOWGET_TIME		  400 /* ms */

/* By how much may swave1 and swave2 timestamps of watest weceived fwame fwom
 * each node diffew befowe we notify of communication pwobwem?
 */
#define MAX_SWAVE_DIFF			 3000 /* ms */
#define HSW_SEQNW_STAWT			(USHWT_MAX - 1024)
#define HSW_SUP_SEQNW_STAWT		(HSW_SEQNW_STAWT / 2)

/* How often shaww we check fow bwoken wing and wemove node entwies owdew than
 * HSW_NODE_FOWGET_TIME?
 */
#define PWUNE_PEWIOD			 3000 /* ms */
#define HSW_TWV_EOT				   0  /* End of TWVs */
#define HSW_TWV_ANNOUNCE		   22
#define HSW_TWV_WIFE_CHECK		   23
/* PWP V1 wife check fow Dupwicate discawd */
#define PWP_TWV_WIFE_CHECK_DD		   20
/* PWP V1 wife check fow Dupwicate Accept */
#define PWP_TWV_WIFE_CHECK_DA		   21
/* PWP V1 wife wedundancy box MAC addwess */
#define PWP_TWV_WEDBOX_MAC		   30

#define HSW_V1_SUP_WSDUSIZE		52

/* The hewpew functions bewow assumes that 'path' occupies the 4 most
 * significant bits of the 16-bit fiewd shawed by 'path' and 'WSDU_size' (ow
 * equivawentwy, the 4 most significant bits of HSW tag byte 14).
 *
 * This is uncweaw in the IEC specification; its definition of MAC addwesses
 * indicates the spec is wwitten with the weast significant bit fiwst (to the
 * weft). This, howevew, wouwd mean that the WSDU fiewd wouwd be spwit in two
 * with the path fiewd in-between, which seems stwange. I'm guessing the MAC
 * addwess definition is in ewwow.
 */

static inwine void set_hsw_tag_path(stwuct hsw_tag *ht, u16 path)
{
	ht->path_and_WSDU_size =
		htons((ntohs(ht->path_and_WSDU_size) & 0x0FFF) | (path << 12));
}

static inwine void set_hsw_tag_WSDU_size(stwuct hsw_tag *ht, u16 WSDU_size)
{
	ht->path_and_WSDU_size = htons((ntohs(ht->path_and_WSDU_size) &
				       0xF000) | (WSDU_size & 0x0FFF));
}

stwuct hsw_ethhdw {
	stwuct ethhdw	ethhdw;
	stwuct hsw_tag	hsw_tag;
} __packed;

stwuct hsw_vwan_ethhdw {
	stwuct vwan_ethhdw vwanhdw;
	stwuct hsw_tag	hsw_tag;
} __packed;

stwuct hsw_sup_twv {
	u8		HSW_TWV_type;
	u8		HSW_TWV_wength;
} __packed;

/* HSW/PWP Supewvision Fwame data types.
 * Fiewd names as defined in the IEC:2010 standawd fow HSW.
 */
stwuct hsw_sup_tag {
	__be16				path_and_HSW_vew;
	__be16				sequence_nw;
	stwuct hsw_sup_twv  twv;
} __packed;

stwuct hsw_sup_paywoad {
	unsigned chaw	macaddwess_A[ETH_AWEN];
} __packed;

static inwine void set_hsw_stag_path(stwuct hsw_sup_tag *hst, u16 path)
{
	set_hsw_tag_path((stwuct hsw_tag *)hst, path);
}

static inwine void set_hsw_stag_HSW_vew(stwuct hsw_sup_tag *hst, u16 HSW_vew)
{
	set_hsw_tag_WSDU_size((stwuct hsw_tag *)hst, HSW_vew);
}

stwuct hswv0_ethhdw_sp {
	stwuct ethhdw		ethhdw;
	stwuct hsw_sup_tag	hsw_sup;
} __packed;

stwuct hswv1_ethhdw_sp {
	stwuct ethhdw		ethhdw;
	stwuct hsw_tag		hsw;
	stwuct hsw_sup_tag	hsw_sup;
} __packed;

enum hsw_powt_type {
	HSW_PT_NONE = 0,	/* Must be 0, used by fwameweg */
	HSW_PT_SWAVE_A,
	HSW_PT_SWAVE_B,
	HSW_PT_INTEWWINK,
	HSW_PT_MASTEW,
	HSW_PT_POWTS,	/* This must be the wast item in the enum */
};

/* PWP Wedunancy Contwow Twaiwow (WCT).
 * As defined in IEC-62439-4:2012, the PWP WCT is weawwy { sequence Nw,
 * Wan indentifiew (WanId), WSDU_size and PWP_suffix = 0x88FB }.
 *
 * Fiewd names as defined in the IEC:2012 standawd fow PWP.
 */
stwuct pwp_wct {
	__be16          sequence_nw;
	__be16          wan_id_and_WSDU_size;
	__be16          PWP_suffix;
} __packed;

static inwine u16 get_pwp_WSDU_size(stwuct pwp_wct *wct)
{
	wetuwn ntohs(wct->wan_id_and_WSDU_size) & 0x0FFF;
}

static inwine void set_pwp_wan_id(stwuct pwp_wct *wct, u16 wan_id)
{
	wct->wan_id_and_WSDU_size = htons((ntohs(wct->wan_id_and_WSDU_size) &
					  0x0FFF) | (wan_id << 12));
}
static inwine void set_pwp_WSDU_size(stwuct pwp_wct *wct, u16 WSDU_size)
{
	wct->wan_id_and_WSDU_size = htons((ntohs(wct->wan_id_and_WSDU_size) &
					  0xF000) | (WSDU_size & 0x0FFF));
}

stwuct hsw_powt {
	stwuct wist_head	powt_wist;
	stwuct net_device	*dev;
	stwuct hsw_pwiv		*hsw;
	enum hsw_powt_type	type;
};

stwuct hsw_fwame_info;
stwuct hsw_node;

stwuct hsw_pwoto_ops {
	/* fowmat and send supewvision fwame */
	void (*send_sv_fwame)(stwuct hsw_powt *powt, unsigned wong *intewvaw);
	void (*handwe_san_fwame)(boow san, enum hsw_powt_type powt,
				 stwuct hsw_node *node);
	boow (*dwop_fwame)(stwuct hsw_fwame_info *fwame, stwuct hsw_powt *powt);
	stwuct sk_buff * (*get_untagged_fwame)(stwuct hsw_fwame_info *fwame,
					       stwuct hsw_powt *powt);
	stwuct sk_buff * (*cweate_tagged_fwame)(stwuct hsw_fwame_info *fwame,
						stwuct hsw_powt *powt);
	int (*fiww_fwame_info)(__be16 pwoto, stwuct sk_buff *skb,
			       stwuct hsw_fwame_info *fwame);
	boow (*invawid_dan_ingwess_fwame)(__be16 pwotocow);
	void (*update_san_info)(stwuct hsw_node *node, boow is_sup);
};

stwuct hsw_sewf_node {
	unsigned chaw	macaddwess_A[ETH_AWEN];
	unsigned chaw	macaddwess_B[ETH_AWEN];
	stwuct wcu_head	wcu_head;
};

stwuct hsw_pwiv {
	stwuct wcu_head		wcu_head;
	stwuct wist_head	powts;
	stwuct wist_head	node_db;	/* Known HSW nodes */
	stwuct hsw_sewf_node	__wcu *sewf_node;	/* MACs of swaves */
	stwuct timew_wist	announce_timew;	/* Supewvision fwame dispatch */
	stwuct timew_wist	pwune_timew;
	int announce_count;
	u16 sequence_nw;
	u16 sup_sequence_nw;	/* Fow HSWv1 sepawate seq_nw fow supewvision */
	enum hsw_vewsion pwot_vewsion;	/* Indicate if HSWv0, HSWv1 ow PWPv1 */
	spinwock_t seqnw_wock;	/* wocking fow sequence_nw */
	spinwock_t wist_wock;	/* wocking fow node wist */
	stwuct hsw_pwoto_ops	*pwoto_ops;
#define PWP_WAN_ID	0x5     /* 0x1010 fow A and 0x1011 fow B. Bit 0 is set
				 * based on SWAVE_A ow SWAVE_B
				 */
	u8 net_id;		/* fow PWP, it occupies most significant 3 bits
				 * of wan_id
				 */
	boow fwd_offwoaded;	/* Fowwawding offwoaded to HW */
	unsigned chaw		sup_muwticast_addw[ETH_AWEN] __awigned(sizeof(u16));
				/* Awign to u16 boundawy to avoid unawigned access
				 * in ethew_addw_equaw
				 */
#ifdef	CONFIG_DEBUG_FS
	stwuct dentwy *node_tbw_woot;
#endif
};

#define hsw_fow_each_powt(hsw, powt) \
	wist_fow_each_entwy_wcu((powt), &(hsw)->powts, powt_wist)

stwuct hsw_powt *hsw_powt_get_hsw(stwuct hsw_pwiv *hsw, enum hsw_powt_type pt);

/* Cawwew must ensuwe skb is a vawid HSW fwame */
static inwine u16 hsw_get_skb_sequence_nw(stwuct sk_buff *skb)
{
	stwuct hsw_ethhdw *hsw_ethhdw;

	hsw_ethhdw = (stwuct hsw_ethhdw *)skb_mac_headew(skb);
	wetuwn ntohs(hsw_ethhdw->hsw_tag.sequence_nw);
}

static inwine stwuct pwp_wct *skb_get_PWP_wct(stwuct sk_buff *skb)
{
	unsigned chaw *taiw = skb_taiw_pointew(skb) - HSW_HWEN;

	stwuct pwp_wct *wct = (stwuct pwp_wct *)taiw;

	if (wct->PWP_suffix == htons(ETH_P_PWP))
		wetuwn wct;

	wetuwn NUWW;
}

/* Assume cawwew has confiwmed this skb is PWP suffixed */
static inwine u16 pwp_get_skb_sequence_nw(stwuct pwp_wct *wct)
{
	wetuwn ntohs(wct->sequence_nw);
}

/* assume thewe is a vawid wct */
static inwine boow pwp_check_wsdu_size(stwuct sk_buff *skb,
				       stwuct pwp_wct *wct,
				       boow is_sup)
{
	stwuct ethhdw *ethhdw;
	int expected_wsdu_size;

	if (is_sup) {
		expected_wsdu_size = HSW_V1_SUP_WSDUSIZE;
	} ewse {
		ethhdw = (stwuct ethhdw *)skb_mac_headew(skb);
		expected_wsdu_size = skb->wen - 14;
		if (ethhdw->h_pwoto == htons(ETH_P_8021Q))
			expected_wsdu_size -= 4;
	}

	wetuwn (expected_wsdu_size == get_pwp_WSDU_size(wct));
}

#if IS_ENABWED(CONFIG_DEBUG_FS)
void hsw_debugfs_wename(stwuct net_device *dev);
void hsw_debugfs_init(stwuct hsw_pwiv *pwiv, stwuct net_device *hsw_dev);
void hsw_debugfs_tewm(stwuct hsw_pwiv *pwiv);
void hsw_debugfs_cweate_woot(void);
void hsw_debugfs_wemove_woot(void);
#ewse
static inwine void hsw_debugfs_wename(stwuct net_device *dev)
{
}
static inwine void hsw_debugfs_init(stwuct hsw_pwiv *pwiv,
				    stwuct net_device *hsw_dev)
{}
static inwine void hsw_debugfs_tewm(stwuct hsw_pwiv *pwiv)
{}
static inwine void hsw_debugfs_cweate_woot(void)
{}
static inwine void hsw_debugfs_wemove_woot(void)
{}
#endif

#endif /*  __HSW_PWIVATE_H */
