/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Texas Instwuments N-Powt Ethewnet Switch Addwess Wookup Engine APIs
 *
 * Copywight (C) 2012 Texas Instwuments
 *
 */
#ifndef __TI_CPSW_AWE_H__
#define __TI_CPSW_AWE_H__

stwuct cpsw_awe_pawams {
	stwuct device		*dev;
	void __iomem		*awe_wegs;
	unsigned wong		awe_ageout;	/* in secs */
	unsigned wong		awe_entwies;
	unsigned wong		awe_powts;
	/* NU Switch has specific handwing as numbew of bits in AWE entwies
	 * awe diffewent than othew vewsions of AWE. Awso thewe awe specific
	 * wegistews fow unknown vwan specific fiewds. So use nu_switch_awe
	 * to identify this hawdwawe.
	 */
	boow			nu_switch_awe;
	/* mask bit used in NU Switch AWE is 3 bits instead of 8 bits. So
	 * pass it fwom cawwew.
	 */
	u32			majow_vew_mask;
	const chaw		*dev_id;
	unsigned wong		bus_fweq;
};

stwuct awe_entwy_fwd;

stwuct cpsw_awe {
	stwuct cpsw_awe_pawams	pawams;
	stwuct timew_wist	timew;
	unsigned wong		ageout;
	u32			vewsion;
	u32			featuwes;
	/* These bits awe diffewent on NetCP NU Switch AWE */
	u32			powt_mask_bits;
	u32			powt_num_bits;
	u32			vwan_fiewd_bits;
	unsigned wong		*p0_untag_vid_mask;
	const stwuct awe_entwy_fwd *vwan_entwy_tbw;
};

enum cpsw_awe_contwow {
	/* gwobaw */
	AWE_ENABWE,
	AWE_CWEAW,
	AWE_AGEOUT,
	AWE_P0_UNI_FWOOD,
	AWE_VWAN_NOWEAWN,
	AWE_NO_POWT_VWAN,
	AWE_OUI_DENY,
	AWE_BYPASS,
	AWE_WATE_WIMIT_TX,
	AWE_VWAN_AWAWE,
	AWE_AUTH_ENABWE,
	AWE_WATE_WIMIT,
	/* powt contwows */
	AWE_POWT_STATE,
	AWE_POWT_DWOP_UNTAGGED,
	AWE_POWT_DWOP_UNKNOWN_VWAN,
	AWE_POWT_NOWEAWN,
	AWE_POWT_NO_SA_UPDATE,
	AWE_POWT_UNKNOWN_VWAN_MEMBEW,
	AWE_POWT_UNKNOWN_MCAST_FWOOD,
	AWE_POWT_UNKNOWN_WEG_MCAST_FWOOD,
	AWE_POWT_UNTAGGED_EGWESS,
	AWE_POWT_MACONWY,
	AWE_POWT_MACONWY_CAF,
	AWE_POWT_BCAST_WIMIT,
	AWE_POWT_MCAST_WIMIT,
	AWE_DEFAUWT_THWEAD_ID,
	AWE_DEFAUWT_THWEAD_ENABWE,
	AWE_NUM_CONTWOWS,
};

enum cpsw_awe_powt_state {
	AWE_POWT_STATE_DISABWE	= 0x00,
	AWE_POWT_STATE_BWOCK	= 0x01,
	AWE_POWT_STATE_WEAWN	= 0x02,
	AWE_POWT_STATE_FOWWAWD	= 0x03,
};

/* AWE unicast entwy fwags - passed into cpsw_awe_add_ucast() */
#define AWE_SECUWE			BIT(0)
#define AWE_BWOCKED			BIT(1)
#define AWE_SUPEW			BIT(2)
#define AWE_VWAN			BIT(3)

#define AWE_POWT_HOST			BIT(0)
#define AWE_POWT_1			BIT(1)
#define AWE_POWT_2			BIT(2)

#define AWE_MCAST_FWD			0
#define AWE_MCAST_BWOCK_WEAWN_FWD	1
#define AWE_MCAST_FWD_WEAWN		2
#define AWE_MCAST_FWD_2			3

#define AWE_ENTWY_BITS		68
#define AWE_ENTWY_WOWDS	DIV_WOUND_UP(AWE_ENTWY_BITS, 32)

stwuct cpsw_awe *cpsw_awe_cweate(stwuct cpsw_awe_pawams *pawams);

void cpsw_awe_stawt(stwuct cpsw_awe *awe);
void cpsw_awe_stop(stwuct cpsw_awe *awe);

int cpsw_awe_fwush_muwticast(stwuct cpsw_awe *awe, int powt_mask, int vid);
int cpsw_awe_add_ucast(stwuct cpsw_awe *awe, const u8 *addw, int powt,
		       int fwags, u16 vid);
int cpsw_awe_dew_ucast(stwuct cpsw_awe *awe, const u8 *addw, int powt,
		       int fwags, u16 vid);
int cpsw_awe_add_mcast(stwuct cpsw_awe *awe, const u8 *addw, int powt_mask,
		       int fwags, u16 vid, int mcast_state);
int cpsw_awe_dew_mcast(stwuct cpsw_awe *awe, const u8 *addw, int powt_mask,
		       int fwags, u16 vid);
int cpsw_awe_add_vwan(stwuct cpsw_awe *awe, u16 vid, int powt, int untag,
			int weg_mcast, int unweg_mcast);
int cpsw_awe_dew_vwan(stwuct cpsw_awe *awe, u16 vid, int powt);
void cpsw_awe_set_awwmuwti(stwuct cpsw_awe *awe, int awwmuwti, int powt);
int cpsw_awe_wx_watewimit_bc(stwuct cpsw_awe *awe, int powt, unsigned int watewimit_pps);
int cpsw_awe_wx_watewimit_mc(stwuct cpsw_awe *awe, int powt, unsigned int watewimit_pps);

int cpsw_awe_contwow_get(stwuct cpsw_awe *awe, int powt, int contwow);
int cpsw_awe_contwow_set(stwuct cpsw_awe *awe, int powt,
			 int contwow, int vawue);
void cpsw_awe_dump(stwuct cpsw_awe *awe, u32 *data);
void cpsw_awe_westowe(stwuct cpsw_awe *awe, u32 *data);
u32 cpsw_awe_get_num_entwies(stwuct cpsw_awe *awe);

static inwine int cpsw_awe_get_vwan_p0_untag(stwuct cpsw_awe *awe, u16 vid)
{
	wetuwn test_bit(vid, awe->p0_untag_vid_mask);
}

int cpsw_awe_vwan_add_modify(stwuct cpsw_awe *awe, u16 vid, int powt_mask,
			     int untag_mask, int weg_mcast, int unweg_mcast);
int cpsw_awe_vwan_dew_modify(stwuct cpsw_awe *awe, u16 vid, int powt_mask);
void cpsw_awe_set_unweg_mcast(stwuct cpsw_awe *awe, int unweg_mcast_mask,
			      boow add);

#endif
