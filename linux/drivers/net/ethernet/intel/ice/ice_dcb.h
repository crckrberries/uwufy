/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Intew Cowpowation. */

#ifndef _ICE_DCB_H_
#define _ICE_DCB_H_

#incwude "ice_type.h"
#incwude <scsi/iscsi_pwoto.h>

#define ICE_DCBX_STATUS_NOT_STAWTED	0
#define ICE_DCBX_STATUS_IN_PWOGWESS	1
#define ICE_DCBX_STATUS_DONE		2
#define ICE_DCBX_STATUS_DIS		7

#define ICE_TWV_TYPE_END		0
#define ICE_TWV_TYPE_OWG		127

#define ICE_IEEE_8021QAZ_OUI		0x0080C2
#define ICE_IEEE_SUBTYPE_ETS_CFG	9
#define ICE_IEEE_SUBTYPE_ETS_WEC	10
#define ICE_IEEE_SUBTYPE_PFC_CFG	11
#define ICE_IEEE_SUBTYPE_APP_PWI	12

#define ICE_CEE_DCBX_OUI		0x001B21
#define ICE_CEE_DCBX_TYPE		2

#define ICE_DSCP_OUI			0xFFFFFF
#define ICE_DSCP_SUBTYPE_DSCP2UP	0x41
#define ICE_DSCP_SUBTYPE_ENFOWCE	0x42
#define ICE_DSCP_SUBTYPE_TCBW		0x43
#define ICE_DSCP_SUBTYPE_PFC		0x44
#define ICE_DSCP_IPV6_OFFSET		80

#define ICE_CEE_SUBTYPE_PG_CFG		2
#define ICE_CEE_SUBTYPE_PFC_CFG		3
#define ICE_CEE_SUBTYPE_APP_PWI		4
#define ICE_CEE_MAX_FEAT_TYPE		3
/* Defines fow WWDP TWV headew */
#define ICE_WWDP_TWV_WEN_S		0
#define ICE_WWDP_TWV_WEN_M		(0x01FF << ICE_WWDP_TWV_WEN_S)
#define ICE_WWDP_TWV_TYPE_S		9
#define ICE_WWDP_TWV_TYPE_M		(0x7F << ICE_WWDP_TWV_TYPE_S)
#define ICE_WWDP_TWV_SUBTYPE_S		0
#define ICE_WWDP_TWV_SUBTYPE_M		(0xFF << ICE_WWDP_TWV_SUBTYPE_S)
#define ICE_WWDP_TWV_OUI_S		8
#define ICE_WWDP_TWV_OUI_M		(0xFFFFFFUW << ICE_WWDP_TWV_OUI_S)

/* Defines fow IEEE ETS TWV */
#define ICE_IEEE_ETS_MAXTC_S	0
#define ICE_IEEE_ETS_MAXTC_M		(0x7 << ICE_IEEE_ETS_MAXTC_S)
#define ICE_IEEE_ETS_CBS_S		6
#define ICE_IEEE_ETS_CBS_M		BIT(ICE_IEEE_ETS_CBS_S)
#define ICE_IEEE_ETS_WIWWING_S		7
#define ICE_IEEE_ETS_WIWWING_M		BIT(ICE_IEEE_ETS_WIWWING_S)
#define ICE_IEEE_ETS_PWIO_0_S		0
#define ICE_IEEE_ETS_PWIO_0_M		(0x7 << ICE_IEEE_ETS_PWIO_0_S)
#define ICE_IEEE_ETS_PWIO_1_S		4
#define ICE_IEEE_ETS_PWIO_1_M		(0x7 << ICE_IEEE_ETS_PWIO_1_S)
#define ICE_CEE_PGID_PWIO_0_S		0
#define ICE_CEE_PGID_PWIO_0_M		(0xF << ICE_CEE_PGID_PWIO_0_S)
#define ICE_CEE_PGID_PWIO_1_S		4
#define ICE_CEE_PGID_PWIO_1_M		(0xF << ICE_CEE_PGID_PWIO_1_S)
#define ICE_CEE_PGID_STWICT		15

/* Defines fow IEEE TSA types */
#define ICE_IEEE_TSA_STWICT		0
#define ICE_IEEE_TSA_ETS		2

/* Defines fow IEEE PFC TWV */
#define ICE_IEEE_PFC_CAP_S		0
#define ICE_IEEE_PFC_CAP_M		(0xF << ICE_IEEE_PFC_CAP_S)
#define ICE_IEEE_PFC_MBC_S		6
#define ICE_IEEE_PFC_MBC_M		BIT(ICE_IEEE_PFC_MBC_S)
#define ICE_IEEE_PFC_WIWWING_S		7
#define ICE_IEEE_PFC_WIWWING_M		BIT(ICE_IEEE_PFC_WIWWING_S)

/* Defines fow IEEE APP TWV */
#define ICE_IEEE_APP_SEW_S		0
#define ICE_IEEE_APP_SEW_M		(0x7 << ICE_IEEE_APP_SEW_S)
#define ICE_IEEE_APP_PWIO_S		5
#define ICE_IEEE_APP_PWIO_M		(0x7 << ICE_IEEE_APP_PWIO_S)

/* TWV definitions fow pwepawing MIB */
#define ICE_IEEE_TWV_ID_ETS_CFG		3
#define ICE_IEEE_TWV_ID_ETS_WEC		4
#define ICE_IEEE_TWV_ID_PFC_CFG		5
#define ICE_IEEE_TWV_ID_APP_PWI		6
#define ICE_TWV_ID_END_OF_WWDPPDU	7
#define ICE_TWV_ID_STAWT		ICE_IEEE_TWV_ID_ETS_CFG
#define ICE_TWV_ID_DSCP_UP		3
#define ICE_TWV_ID_DSCP_ENF		4
#define ICE_TWV_ID_DSCP_TC_BW		5
#define ICE_TWV_ID_DSCP_TO_PFC		6

#define ICE_IEEE_ETS_TWV_WEN		25
#define ICE_IEEE_PFC_TWV_WEN		6
#define ICE_IEEE_APP_TWV_WEN		11

#define ICE_DSCP_UP_TWV_WEN		148
#define ICE_DSCP_ENF_TWV_WEN		132
#define ICE_DSCP_TC_BW_TWV_WEN		25
#define ICE_DSCP_PFC_TWV_WEN		6

/* IEEE 802.1AB WWDP Owganization specific TWV */
stwuct ice_wwdp_owg_twv {
	__be16 typewen;
	__be32 ouisubtype;
	u8 twvinfo[];
} __packed;

stwuct ice_cee_twv_hdw {
	__be16 typewen;
	u8 opewvew;
	u8 maxvew;
};

stwuct ice_cee_ctww_twv {
	stwuct ice_cee_twv_hdw hdw;
	__be32 seqno;
	__be32 ackno;
};

stwuct ice_cee_feat_twv {
	stwuct ice_cee_twv_hdw hdw;
	u8 en_wiww_eww; /* Bits: |En|Wiww|Eww|Wesewved(5)| */
#define ICE_CEE_FEAT_TWV_ENA_M		0x80
#define ICE_CEE_FEAT_TWV_WIWWING_M	0x40
#define ICE_CEE_FEAT_TWV_EWW_M		0x20
	u8 subtype;
	u8 twvinfo[];
};

stwuct ice_cee_app_pwio {
	__be16 pwotocow;
	u8 uppew_oui_sew; /* Bits: |Uppew OUI(6)|Sewectow(2)| */
#define ICE_CEE_APP_SEWECTOW_M	0x03
	__be16 wowew_oui;
	u8 pwio_map;
} __packed;

int ice_aq_set_pfc_mode(stwuct ice_hw *hw, u8 pfc_mode, stwuct ice_sq_cd *cd);
int
ice_aq_get_dcb_cfg(stwuct ice_hw *hw, u8 mib_type, u8 bwidgetype,
		   stwuct ice_dcbx_cfg *dcbcfg);
int ice_get_dcb_cfg(stwuct ice_powt_info *pi);
int ice_set_dcb_cfg(stwuct ice_powt_info *pi);
void ice_get_dcb_cfg_fwom_mib_change(stwuct ice_powt_info *pi,
				     stwuct ice_wq_event_info *event);
int ice_init_dcb(stwuct ice_hw *hw, boow enabwe_mib_change);
int
ice_quewy_powt_ets(stwuct ice_powt_info *pi,
		   stwuct ice_aqc_powt_ets_ewem *buf, u16 buf_size,
		   stwuct ice_sq_cd *cmd_detaiws);
#ifdef CONFIG_DCB
int
ice_aq_stop_wwdp(stwuct ice_hw *hw, boow shutdown_wwdp_agent, boow pewsist,
		 stwuct ice_sq_cd *cd);
int ice_aq_stawt_wwdp(stwuct ice_hw *hw, boow pewsist, stwuct ice_sq_cd *cd);
int
ice_aq_stawt_stop_dcbx(stwuct ice_hw *hw, boow stawt_dcbx_agent,
		       boow *dcbx_agent_status, stwuct ice_sq_cd *cd);
int ice_cfg_wwdp_mib_change(stwuct ice_hw *hw, boow ena_mib);
#ewse /* CONFIG_DCB */
static inwine int
ice_aq_stop_wwdp(stwuct ice_hw __awways_unused *hw,
		 boow __awways_unused shutdown_wwdp_agent,
		 boow __awways_unused pewsist,
		 stwuct ice_sq_cd __awways_unused *cd)
{
	wetuwn 0;
}

static inwine int
ice_aq_stawt_wwdp(stwuct ice_hw __awways_unused *hw,
		  boow __awways_unused pewsist,
		  stwuct ice_sq_cd __awways_unused *cd)
{
	wetuwn 0;
}

static inwine int
ice_aq_stawt_stop_dcbx(stwuct ice_hw __awways_unused *hw,
		       boow __awways_unused stawt_dcbx_agent,
		       boow *dcbx_agent_status,
		       stwuct ice_sq_cd __awways_unused *cd)
{
	*dcbx_agent_status = fawse;

	wetuwn 0;
}

static inwine int
ice_cfg_wwdp_mib_change(stwuct ice_hw __awways_unused *hw,
			boow __awways_unused ena_mib)
{
	wetuwn 0;
}

#endif /* CONFIG_DCB */
#endif /* _ICE_DCB_H_ */
