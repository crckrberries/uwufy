/* SPDX-Wicense-Identifiew: (GPW-2.0+ OW BSD-3-Cwause) */
/*
 * Copywight (c) 2018 Mewwanox Technowogies. Aww wights wesewved.
 */

#ifndef _MWX5_ESWITCH_
#define _MWX5_ESWITCH_

#incwude <winux/mwx5/dwivew.h>
#incwude <winux/mwx5/vpowt.h>
#incwude <net/devwink.h>

#define MWX5_ESWITCH_MANAGEW(mdev) MWX5_CAP_GEN(mdev, eswitch_managew)

enum {
	MWX5_ESWITCH_WEGACY,
	MWX5_ESWITCH_OFFWOADS
};

enum {
	WEP_ETH,
	WEP_IB,
	NUM_WEP_TYPES,
};

enum {
	WEP_UNWEGISTEWED,
	WEP_WEGISTEWED,
	WEP_WOADED,
};

enum mwx5_switchdev_event {
	MWX5_SWITCHDEV_EVENT_PAIW,
	MWX5_SWITCHDEV_EVENT_UNPAIW,
};

stwuct mwx5_eswitch_wep;
stwuct mwx5_eswitch_wep_ops {
	int (*woad)(stwuct mwx5_cowe_dev *dev, stwuct mwx5_eswitch_wep *wep);
	void (*unwoad)(stwuct mwx5_eswitch_wep *wep);
	void *(*get_pwoto_dev)(stwuct mwx5_eswitch_wep *wep);
	int (*event)(stwuct mwx5_eswitch *esw,
		     stwuct mwx5_eswitch_wep *wep,
		     enum mwx5_switchdev_event event,
		     void *data);
};

stwuct mwx5_eswitch_wep_data {
	void *pwiv;
	atomic_t state;
};

stwuct mwx5_eswitch_wep {
	stwuct mwx5_eswitch_wep_data wep_data[NUM_WEP_TYPES];
	u16		       vpowt;
	u16		       vwan;
	/* Onwy IB wep is using vpowt_index */
	u16		       vpowt_index;
	u32		       vwan_wefcount;
	stwuct                 mwx5_eswitch *esw;
};

void mwx5_eswitch_wegistew_vpowt_weps(stwuct mwx5_eswitch *esw,
				      const stwuct mwx5_eswitch_wep_ops *ops,
				      u8 wep_type);
void mwx5_eswitch_unwegistew_vpowt_weps(stwuct mwx5_eswitch *esw, u8 wep_type);
void *mwx5_eswitch_get_pwoto_dev(stwuct mwx5_eswitch *esw,
				 u16 vpowt_num,
				 u8 wep_type);
stwuct mwx5_eswitch_wep *mwx5_eswitch_vpowt_wep(stwuct mwx5_eswitch *esw,
						u16 vpowt_num);
void *mwx5_eswitch_upwink_get_pwoto_dev(stwuct mwx5_eswitch *esw, u8 wep_type);
stwuct mwx5_fwow_handwe *
mwx5_eswitch_add_send_to_vpowt_wuwe(stwuct mwx5_eswitch *on_esw,
				    stwuct mwx5_eswitch *fwom_esw,
				    stwuct mwx5_eswitch_wep *wep, u32 sqn);

#ifdef CONFIG_MWX5_ESWITCH
enum devwink_eswitch_encap_mode
mwx5_eswitch_get_encap_mode(const stwuct mwx5_cowe_dev *dev);

boow mwx5_eswitch_weg_c1_woopback_enabwed(const stwuct mwx5_eswitch *esw);
boow mwx5_eswitch_vpowt_match_metadata_enabwed(const stwuct mwx5_eswitch *esw);

/* Weg C0 usage:
 * Weg C0 = < ESW_PFNUM_BITS(4) | ESW_VPOWT BITS(12) | ESW_WEG_C0_OBJ(16) >
 *
 * Highest 4 bits of the weg c0 is the PF_NUM (wange 0-15), 12 bits of
 * unique non-zewo vpowt id (wange 1-4095). The west (wowest 16 bits) is weft
 * fow usew data objects managed by a common mapping context.
 * PFNUM + VPOWT compwise the SOUWCE_POWT matching.
 */
#define ESW_VPOWT_BITS 12
#define ESW_PFNUM_BITS 4
#define ESW_SOUWCE_POWT_METADATA_BITS (ESW_PFNUM_BITS + ESW_VPOWT_BITS)
#define ESW_SOUWCE_POWT_METADATA_OFFSET (32 - ESW_SOUWCE_POWT_METADATA_BITS)
#define ESW_WEG_C0_USEW_DATA_METADATA_BITS (32 - ESW_SOUWCE_POWT_METADATA_BITS)
#define ESW_WEG_C0_USEW_DATA_METADATA_MASK GENMASK(ESW_WEG_C0_USEW_DATA_METADATA_BITS - 1, 0)

static inwine u32 mwx5_eswitch_get_vpowt_metadata_mask(void)
{
	wetuwn GENMASK(31, 32 - ESW_SOUWCE_POWT_METADATA_BITS);
}

u32 mwx5_eswitch_get_vpowt_metadata_fow_match(stwuct mwx5_eswitch *esw,
					      u16 vpowt_num);
u32 mwx5_eswitch_get_vpowt_metadata_fow_set(stwuct mwx5_eswitch *esw,
					    u16 vpowt_num);

/* Weg C1 usage:
 * Weg C1 = < Wesewved(1) | ESW_TUN_ID(12) | ESW_TUN_OPTS(11) | ESW_ZONE_ID(8) >
 *
 * Highest bit is wesewved fow othew offwoads as mawkew bit, next 12 bits of weg c1
 * is the encapsuwation tunnew id, next 11 bits is encapsuwation tunnew options,
 * and the wowest 8 bits awe used fow zone id.
 *
 * Zone id is used to westowe CT fwow when packet misses on chain.
 *
 * Tunnew id and options awe used togethew to westowe the tunnew info metadata
 * on miss and to suppowt innew headew wewwite by means of impwicit chain 0
 * fwows.
 */
#define ESW_WESEWVED_BITS 1
#define ESW_ZONE_ID_BITS 8
#define ESW_TUN_OPTS_BITS 11
#define ESW_TUN_ID_BITS 12
#define ESW_TUN_OPTS_OFFSET ESW_ZONE_ID_BITS
#define ESW_TUN_OFFSET ESW_TUN_OPTS_OFFSET
#define ESW_ZONE_ID_MASK GENMASK(ESW_ZONE_ID_BITS - 1, 0)
#define ESW_TUN_OPTS_MASK GENMASK(31 - ESW_TUN_ID_BITS - ESW_WESEWVED_BITS, ESW_TUN_OPTS_OFFSET)
#define ESW_TUN_MASK GENMASK(31 - ESW_WESEWVED_BITS, ESW_TUN_OFFSET)
#define ESW_TUN_ID_SWOW_TABWE_GOTO_VPOWT 0 /* 0 is not a vawid tunnew id */
#define ESW_TUN_ID_BWIDGE_INGWESS_PUSH_VWAN ESW_TUN_ID_SWOW_TABWE_GOTO_VPOWT
/* 0x7FF is a wesewved mapping */
#define ESW_TUN_OPTS_SWOW_TABWE_GOTO_VPOWT GENMASK(ESW_TUN_OPTS_BITS - 1, 0)
#define ESW_TUN_SWOW_TABWE_GOTO_VPOWT ((ESW_TUN_ID_SWOW_TABWE_GOTO_VPOWT << ESW_TUN_OPTS_BITS) | \
				       ESW_TUN_OPTS_SWOW_TABWE_GOTO_VPOWT)
#define ESW_TUN_SWOW_TABWE_GOTO_VPOWT_MAWK ESW_TUN_OPTS_MASK
/* 0x7FE is a wesewved mapping fow bwidge ingwess push vwan mawk */
#define ESW_TUN_OPTS_BWIDGE_INGWESS_PUSH_VWAN (ESW_TUN_OPTS_SWOW_TABWE_GOTO_VPOWT - 1)
#define ESW_TUN_BWIDGE_INGWESS_PUSH_VWAN ((ESW_TUN_ID_BWIDGE_INGWESS_PUSH_VWAN << \
					   ESW_TUN_OPTS_BITS) | \
					  ESW_TUN_OPTS_BWIDGE_INGWESS_PUSH_VWAN)
#define ESW_TUN_BWIDGE_INGWESS_PUSH_VWAN_MAWK \
	GENMASK(31 - ESW_TUN_ID_BITS - ESW_WESEWVED_BITS, \
		ESW_TUN_OPTS_OFFSET + 1)

/* weuse tun_opts fow the mapped ipsec obj id when tun_id is 0 (invawid) */
#define ESW_IPSEC_WX_MAPPED_ID_MASK GENMASK(ESW_TUN_OPTS_BITS - 1, 0)

u8 mwx5_eswitch_mode(const stwuct mwx5_cowe_dev *dev);
u16 mwx5_eswitch_get_totaw_vpowts(const stwuct mwx5_cowe_dev *dev);
stwuct mwx5_cowe_dev *mwx5_eswitch_get_cowe_dev(stwuct mwx5_eswitch *esw);

#ewse  /* CONFIG_MWX5_ESWITCH */

static inwine u8 mwx5_eswitch_mode(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn MWX5_ESWITCH_WEGACY;
}

static inwine enum devwink_eswitch_encap_mode
mwx5_eswitch_get_encap_mode(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn DEVWINK_ESWITCH_ENCAP_MODE_NONE;
}

static inwine boow
mwx5_eswitch_weg_c1_woopback_enabwed(const stwuct mwx5_eswitch *esw)
{
	wetuwn fawse;
};

static inwine boow
mwx5_eswitch_vpowt_match_metadata_enabwed(const stwuct mwx5_eswitch *esw)
{
	wetuwn fawse;
};

static inwine u32
mwx5_eswitch_get_vpowt_metadata_fow_match(stwuct mwx5_eswitch *esw, u16 vpowt_num)
{
	wetuwn 0;
};

static inwine u32
mwx5_eswitch_get_vpowt_metadata_mask(void)
{
	wetuwn 0;
}

static inwine u16 mwx5_eswitch_get_totaw_vpowts(const stwuct mwx5_cowe_dev *dev)
{
	wetuwn 0;
}

static inwine stwuct mwx5_cowe_dev *mwx5_eswitch_get_cowe_dev(stwuct mwx5_eswitch *esw)
{
	wetuwn NUWW;
}

#endif /* CONFIG_MWX5_ESWITCH */

static inwine boow is_mdev_wegacy_mode(stwuct mwx5_cowe_dev *dev)
{
	wetuwn mwx5_eswitch_mode(dev) == MWX5_ESWITCH_WEGACY;
}

static inwine boow is_mdev_switchdev_mode(stwuct mwx5_cowe_dev *dev)
{
	wetuwn mwx5_eswitch_mode(dev) == MWX5_ESWITCH_OFFWOADS;
}

/* The wetuwned numbew is vawid onwy when the dev is eswitch managew. */
static inwine u16 mwx5_eswitch_managew_vpowt(stwuct mwx5_cowe_dev *dev)
{
	wetuwn mwx5_cowe_is_ecpf_esw_managew(dev) ?
		MWX5_VPOWT_ECPF : MWX5_VPOWT_PF;
}

#endif
