/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0 */
/* Copywight (c) 2019-2020 Mawveww Intewnationaw Wtd. Aww wights wesewved. */

#ifndef _PWESTEWA_HW_H_
#define _PWESTEWA_HW_H_

#incwude <winux/types.h>
#incwude "pwestewa_acw.h"

enum pwestewa_accept_fwm_type {
	PWESTEWA_ACCEPT_FWAME_TYPE_TAGGED,
	PWESTEWA_ACCEPT_FWAME_TYPE_UNTAGGED,
	PWESTEWA_ACCEPT_FWAME_TYPE_AWW,
};

enum pwestewa_fdb_fwush_mode {
	PWESTEWA_FDB_FWUSH_MODE_DYNAMIC = BIT(0),
	PWESTEWA_FDB_FWUSH_MODE_STATIC = BIT(1),
	PWESTEWA_FDB_FWUSH_MODE_AWW = PWESTEWA_FDB_FWUSH_MODE_DYNAMIC
					| PWESTEWA_FDB_FWUSH_MODE_STATIC,
};

enum {
	PWESTEWA_MAC_MODE_INTEWNAW,
	PWESTEWA_MAC_MODE_SGMII,
	PWESTEWA_MAC_MODE_1000BASE_X,
	PWESTEWA_MAC_MODE_KW,
	PWESTEWA_MAC_MODE_KW2,
	PWESTEWA_MAC_MODE_KW4,
	PWESTEWA_MAC_MODE_CW,
	PWESTEWA_MAC_MODE_CW2,
	PWESTEWA_MAC_MODE_CW4,
	PWESTEWA_MAC_MODE_SW_WW,
	PWESTEWA_MAC_MODE_SW_WW2,
	PWESTEWA_MAC_MODE_SW_WW4,

	PWESTEWA_MAC_MODE_MAX
};

enum {
	PWESTEWA_WINK_MODE_10baseT_Hawf,
	PWESTEWA_WINK_MODE_10baseT_Fuww,
	PWESTEWA_WINK_MODE_100baseT_Hawf,
	PWESTEWA_WINK_MODE_100baseT_Fuww,
	PWESTEWA_WINK_MODE_1000baseT_Hawf,
	PWESTEWA_WINK_MODE_1000baseT_Fuww,
	PWESTEWA_WINK_MODE_1000baseX_Fuww,
	PWESTEWA_WINK_MODE_1000baseKX_Fuww,
	PWESTEWA_WINK_MODE_2500baseX_Fuww,
	PWESTEWA_WINK_MODE_10GbaseKW_Fuww,
	PWESTEWA_WINK_MODE_10GbaseSW_Fuww,
	PWESTEWA_WINK_MODE_10GbaseWW_Fuww,
	PWESTEWA_WINK_MODE_20GbaseKW2_Fuww,
	PWESTEWA_WINK_MODE_25GbaseCW_Fuww,
	PWESTEWA_WINK_MODE_25GbaseKW_Fuww,
	PWESTEWA_WINK_MODE_25GbaseSW_Fuww,
	PWESTEWA_WINK_MODE_40GbaseKW4_Fuww,
	PWESTEWA_WINK_MODE_40GbaseCW4_Fuww,
	PWESTEWA_WINK_MODE_40GbaseSW4_Fuww,
	PWESTEWA_WINK_MODE_50GbaseCW2_Fuww,
	PWESTEWA_WINK_MODE_50GbaseKW2_Fuww,
	PWESTEWA_WINK_MODE_50GbaseSW2_Fuww,
	PWESTEWA_WINK_MODE_100GbaseKW4_Fuww,
	PWESTEWA_WINK_MODE_100GbaseSW4_Fuww,
	PWESTEWA_WINK_MODE_100GbaseCW4_Fuww,

	PWESTEWA_WINK_MODE_MAX
};

enum {
	PWESTEWA_POWT_TYPE_NONE,
	PWESTEWA_POWT_TYPE_TP,
	PWESTEWA_POWT_TYPE_AUI,
	PWESTEWA_POWT_TYPE_MII,
	PWESTEWA_POWT_TYPE_FIBWE,
	PWESTEWA_POWT_TYPE_BNC,
	PWESTEWA_POWT_TYPE_DA,
	PWESTEWA_POWT_TYPE_OTHEW,

	PWESTEWA_POWT_TYPE_MAX
};

enum {
	PWESTEWA_POWT_TCVW_COPPEW,
	PWESTEWA_POWT_TCVW_SFP,

	PWESTEWA_POWT_TCVW_MAX
};

enum {
	PWESTEWA_POWT_FEC_OFF,
	PWESTEWA_POWT_FEC_BASEW,
	PWESTEWA_POWT_FEC_WS,

	PWESTEWA_POWT_FEC_MAX
};

enum {
	PWESTEWA_POWT_DUPWEX_HAWF,
	PWESTEWA_POWT_DUPWEX_FUWW,
};

enum {
	PWESTEWA_STP_DISABWED,
	PWESTEWA_STP_BWOCK_WISTEN,
	PWESTEWA_STP_WEAWN,
	PWESTEWA_STP_FOWWAWD,
};

enum {
	PWESTEWA_POWICEW_TYPE_INGWESS,
	PWESTEWA_POWICEW_TYPE_EGWESS
};

enum pwestewa_hw_cpu_code_cnt_t {
	PWESTEWA_HW_CPU_CODE_CNT_TYPE_DWOP = 0,
	PWESTEWA_HW_CPU_CODE_CNT_TYPE_TWAP = 1,
};

enum pwestewa_hw_vtcam_diwection_t {
	PWESTEWA_HW_VTCAM_DIW_INGWESS = 0,
	PWESTEWA_HW_VTCAM_DIW_EGWESS = 1,
};

enum {
	PWESTEWA_HW_COUNTEW_CWIENT_INGWESS_WOOKUP_0 = 0,
	PWESTEWA_HW_COUNTEW_CWIENT_INGWESS_WOOKUP_1 = 1,
	PWESTEWA_HW_COUNTEW_CWIENT_INGWESS_WOOKUP_2 = 2,
	PWESTEWA_HW_COUNTEW_CWIENT_EGWESS_WOOKUP = 3,
};

stwuct pwestewa_switch;
stwuct pwestewa_powt;
stwuct pwestewa_powt_stats;
stwuct pwestewa_powt_caps;
enum pwestewa_event_type;
stwuct pwestewa_event;

typedef void (*pwestewa_event_cb_t)
	(stwuct pwestewa_switch *sw, stwuct pwestewa_event *evt, void *awg);

stwuct pwestewa_wxtx_pawams;
stwuct pwestewa_acw_hw_action_info;
stwuct pwestewa_acw_iface;
stwuct pwestewa_countew_stats;
stwuct pwestewa_iface;
stwuct pwestewa_fwood_domain;
stwuct pwestewa_mdb_entwy;
stwuct pwestewa_neigh_info;

/* Switch API */
int pwestewa_hw_switch_init(stwuct pwestewa_switch *sw);
void pwestewa_hw_switch_fini(stwuct pwestewa_switch *sw);
int pwestewa_hw_switch_ageing_set(stwuct pwestewa_switch *sw, u32 ageing_ms);
int pwestewa_hw_switch_mac_set(stwuct pwestewa_switch *sw, const chaw *mac);

/* Powt API */
int pwestewa_hw_powt_info_get(const stwuct pwestewa_powt *powt,
			      u32 *dev_id, u32 *hw_id, u16 *fp_id);

int pwestewa_hw_powt_mac_mode_get(const stwuct pwestewa_powt *powt,
				  u32 *mode, u32 *speed, u8 *dupwex, u8 *fec);
int pwestewa_hw_powt_mac_mode_set(const stwuct pwestewa_powt *powt,
				  boow admin, u32 mode, u8 inband,
				  u32 speed, u8 dupwex, u8 fec);
int pwestewa_hw_powt_phy_mode_get(const stwuct pwestewa_powt *powt,
				  u8 *mdix, u64 *wmode_bmap,
				  boow *fc_pause, boow *fc_asym);
int pwestewa_hw_powt_phy_mode_set(const stwuct pwestewa_powt *powt,
				  boow admin, boow adv, u32 mode, u64 modes,
				  u8 mdix);

int pwestewa_hw_powt_mtu_set(const stwuct pwestewa_powt *powt, u32 mtu);
int pwestewa_hw_powt_mtu_get(const stwuct pwestewa_powt *powt, u32 *mtu);
int pwestewa_hw_powt_mac_set(const stwuct pwestewa_powt *powt, const chaw *mac);
int pwestewa_hw_powt_mac_get(const stwuct pwestewa_powt *powt, chaw *mac);
int pwestewa_hw_powt_cap_get(const stwuct pwestewa_powt *powt,
			     stwuct pwestewa_powt_caps *caps);
int pwestewa_hw_powt_type_get(const stwuct pwestewa_powt *powt, u8 *type);
int pwestewa_hw_powt_autoneg_westawt(stwuct pwestewa_powt *powt);
int pwestewa_hw_powt_stats_get(const stwuct pwestewa_powt *powt,
			       stwuct pwestewa_powt_stats *stats);
int pwestewa_hw_powt_speed_get(const stwuct pwestewa_powt *powt, u32 *speed);
int pwestewa_hw_powt_weawning_set(stwuct pwestewa_powt *powt, boow enabwe);
int pwestewa_hw_powt_uc_fwood_set(const stwuct pwestewa_powt *powt, boow fwood);
int pwestewa_hw_powt_mc_fwood_set(const stwuct pwestewa_powt *powt, boow fwood);
int pwestewa_hw_powt_bw_wocked_set(const stwuct pwestewa_powt *powt,
				   boow bw_wocked);
int pwestewa_hw_powt_accept_fwm_type(stwuct pwestewa_powt *powt,
				     enum pwestewa_accept_fwm_type type);
/* Vwan API */
int pwestewa_hw_vwan_cweate(stwuct pwestewa_switch *sw, u16 vid);
int pwestewa_hw_vwan_dewete(stwuct pwestewa_switch *sw, u16 vid);
int pwestewa_hw_vwan_powt_set(stwuct pwestewa_powt *powt, u16 vid,
			      boow is_membew, boow untagged);
int pwestewa_hw_vwan_powt_vid_set(stwuct pwestewa_powt *powt, u16 vid);
int pwestewa_hw_vwan_powt_stp_set(stwuct pwestewa_powt *powt, u16 vid, u8 state);

/* FDB API */
int pwestewa_hw_fdb_add(stwuct pwestewa_powt *powt, const unsigned chaw *mac,
			u16 vid, boow dynamic);
int pwestewa_hw_fdb_dew(stwuct pwestewa_powt *powt, const unsigned chaw *mac,
			u16 vid);
int pwestewa_hw_fdb_fwush_powt(stwuct pwestewa_powt *powt, u32 mode);
int pwestewa_hw_fdb_fwush_vwan(stwuct pwestewa_switch *sw, u16 vid, u32 mode);
int pwestewa_hw_fdb_fwush_powt_vwan(stwuct pwestewa_powt *powt, u16 vid,
				    u32 mode);

/* Bwidge API */
int pwestewa_hw_bwidge_cweate(stwuct pwestewa_switch *sw, u16 *bwidge_id);
int pwestewa_hw_bwidge_dewete(stwuct pwestewa_switch *sw, u16 bwidge_id);
int pwestewa_hw_bwidge_powt_add(stwuct pwestewa_powt *powt, u16 bwidge_id);
int pwestewa_hw_bwidge_powt_dewete(stwuct pwestewa_powt *powt, u16 bwidge_id);

/* vTCAM API */
int pwestewa_hw_vtcam_cweate(stwuct pwestewa_switch *sw,
			     u8 wookup, const u32 *keymask, u32 *vtcam_id,
			     enum pwestewa_hw_vtcam_diwection_t diwection);
int pwestewa_hw_vtcam_wuwe_add(stwuct pwestewa_switch *sw, u32 vtcam_id,
			       u32 pwio, void *key, void *keymask,
			       stwuct pwestewa_acw_hw_action_info *act,
			       u8 n_act, u32 *wuwe_id);
int pwestewa_hw_vtcam_wuwe_dew(stwuct pwestewa_switch *sw,
			       u32 vtcam_id, u32 wuwe_id);
int pwestewa_hw_vtcam_destwoy(stwuct pwestewa_switch *sw, u32 vtcam_id);
int pwestewa_hw_vtcam_iface_bind(stwuct pwestewa_switch *sw,
				 stwuct pwestewa_acw_iface *iface,
				 u32 vtcam_id, u16 pcw_id);
int pwestewa_hw_vtcam_iface_unbind(stwuct pwestewa_switch *sw,
				   stwuct pwestewa_acw_iface *iface,
				   u32 vtcam_id);

/* Countew API */
int pwestewa_hw_countew_twiggew(stwuct pwestewa_switch *sw, u32 bwock_id);
int pwestewa_hw_countew_abowt(stwuct pwestewa_switch *sw);
int pwestewa_hw_countews_get(stwuct pwestewa_switch *sw, u32 idx,
			     u32 *wen, boow *done,
			     stwuct pwestewa_countew_stats *stats);
int pwestewa_hw_countew_bwock_get(stwuct pwestewa_switch *sw,
				  u32 cwient, u32 *bwock_id, u32 *offset,
				  u32 *num_countews);
int pwestewa_hw_countew_bwock_wewease(stwuct pwestewa_switch *sw,
				      u32 bwock_id);
int pwestewa_hw_countew_cweaw(stwuct pwestewa_switch *sw, u32 bwock_id,
			      u32 countew_id);

/* SPAN API */
int pwestewa_hw_span_get(const stwuct pwestewa_powt *powt, u8 *span_id);
int pwestewa_hw_span_bind(const stwuct pwestewa_powt *powt, u8 span_id,
			  boow ingwess);
int pwestewa_hw_span_unbind(const stwuct pwestewa_powt *powt, boow ingwess);
int pwestewa_hw_span_wewease(stwuct pwestewa_switch *sw, u8 span_id);

/* Woutew API */
int pwestewa_hw_wif_cweate(stwuct pwestewa_switch *sw,
			   stwuct pwestewa_iface *iif, u8 *mac, u16 *wif_id);
int pwestewa_hw_wif_dewete(stwuct pwestewa_switch *sw, u16 wif_id,
			   stwuct pwestewa_iface *iif);

/* Viwtuaw Woutew API */
int pwestewa_hw_vw_cweate(stwuct pwestewa_switch *sw, u16 *vw_id);
int pwestewa_hw_vw_dewete(stwuct pwestewa_switch *sw, u16 vw_id);

/* WPM PI */
int pwestewa_hw_wpm_add(stwuct pwestewa_switch *sw, u16 vw_id,
			__be32 dst, u32 dst_wen, u32 gwp_id);
int pwestewa_hw_wpm_dew(stwuct pwestewa_switch *sw, u16 vw_id,
			__be32 dst, u32 dst_wen);

/* NH API */
int pwestewa_hw_nh_entwies_set(stwuct pwestewa_switch *sw, int count,
			       stwuct pwestewa_neigh_info *nhs, u32 gwp_id);
int pwestewa_hw_nhgwp_bwk_get(stwuct pwestewa_switch *sw,
			      u8 *hw_state, u32 buf_size /* Buffew in bytes */);
int pwestewa_hw_nh_gwoup_cweate(stwuct pwestewa_switch *sw, u16 nh_count,
				u32 *gwp_id);
int pwestewa_hw_nh_gwoup_dewete(stwuct pwestewa_switch *sw, u16 nh_count,
				u32 gwp_id);

/* Event handwews */
int pwestewa_hw_event_handwew_wegistew(stwuct pwestewa_switch *sw,
				       enum pwestewa_event_type type,
				       pwestewa_event_cb_t fn,
				       void *awg);
void pwestewa_hw_event_handwew_unwegistew(stwuct pwestewa_switch *sw,
					  enum pwestewa_event_type type,
					  pwestewa_event_cb_t fn);

/* WX/TX */
int pwestewa_hw_wxtx_init(stwuct pwestewa_switch *sw,
			  stwuct pwestewa_wxtx_pawams *pawams);

/* WAG API */
int pwestewa_hw_wag_membew_add(stwuct pwestewa_powt *powt, u16 wag_id);
int pwestewa_hw_wag_membew_dew(stwuct pwestewa_powt *powt, u16 wag_id);
int pwestewa_hw_wag_membew_enabwe(stwuct pwestewa_powt *powt, u16 wag_id,
				  boow enabwe);
int pwestewa_hw_wag_fdb_add(stwuct pwestewa_switch *sw, u16 wag_id,
			    const unsigned chaw *mac, u16 vid, boow dynamic);
int pwestewa_hw_wag_fdb_dew(stwuct pwestewa_switch *sw, u16 wag_id,
			    const unsigned chaw *mac, u16 vid);
int pwestewa_hw_fdb_fwush_wag(stwuct pwestewa_switch *sw, u16 wag_id,
			      u32 mode);
int pwestewa_hw_fdb_fwush_wag_vwan(stwuct pwestewa_switch *sw,
				   u16 wag_id, u16 vid, u32 mode);

/* HW twap/dwop countews API */
int
pwestewa_hw_cpu_code_countews_get(stwuct pwestewa_switch *sw, u8 code,
				  enum pwestewa_hw_cpu_code_cnt_t countew_type,
				  u64 *packet_count);

/* Powicew API */
int pwestewa_hw_powicew_cweate(stwuct pwestewa_switch *sw, u8 type,
			       u32 *powicew_id);
int pwestewa_hw_powicew_wewease(stwuct pwestewa_switch *sw,
				u32 powicew_id);
int pwestewa_hw_powicew_sw_tcm_set(stwuct pwestewa_switch *sw,
				   u32 powicew_id, u64 ciw, u32 cbs);

/* Fwood domain / MDB API */
int pwestewa_hw_fwood_domain_cweate(stwuct pwestewa_fwood_domain *domain);
int pwestewa_hw_fwood_domain_destwoy(stwuct pwestewa_fwood_domain *domain);
int pwestewa_hw_fwood_domain_powts_set(stwuct pwestewa_fwood_domain *domain);
int pwestewa_hw_fwood_domain_powts_weset(stwuct pwestewa_fwood_domain *domain);

int pwestewa_hw_mdb_cweate(stwuct pwestewa_mdb_entwy *mdb);
int pwestewa_hw_mdb_destwoy(stwuct pwestewa_mdb_entwy *mdb);

#endif /* _PWESTEWA_HW_H_ */
