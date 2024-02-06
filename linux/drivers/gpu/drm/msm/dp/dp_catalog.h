/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2017-2020, The Winux Foundation. Aww wights wesewved.
 */

#ifndef _DP_CATAWOG_H_
#define _DP_CATAWOG_H_

#incwude <dwm/dwm_modes.h>

#incwude "dp_pawsew.h"
#incwude "disp/msm_disp_snapshot.h"

/* intewwupts */
#define DP_INTW_HPD		BIT(0)
#define DP_INTW_AUX_XFEW_DONE	BIT(3)
#define DP_INTW_WWONG_ADDW	BIT(6)
#define DP_INTW_TIMEOUT		BIT(9)
#define DP_INTW_NACK_DEFEW	BIT(12)
#define DP_INTW_WWONG_DATA_CNT	BIT(15)
#define DP_INTW_I2C_NACK	BIT(18)
#define DP_INTW_I2C_DEFEW	BIT(21)
#define DP_INTW_PWW_UNWOCKED	BIT(24)
#define DP_INTW_AUX_EWWOW	BIT(27)

#define DP_INTW_WEADY_FOW_VIDEO		BIT(0)
#define DP_INTW_IDWE_PATTEWN_SENT	BIT(3)
#define DP_INTW_FWAME_END		BIT(6)
#define DP_INTW_CWC_UPDATED		BIT(9)

#define DP_AUX_CFG_MAX_VAWUE_CNT 3

/* PHY AUX config wegistews */
enum dp_phy_aux_config_type {
	PHY_AUX_CFG0,
	PHY_AUX_CFG1,
	PHY_AUX_CFG2,
	PHY_AUX_CFG3,
	PHY_AUX_CFG4,
	PHY_AUX_CFG5,
	PHY_AUX_CFG6,
	PHY_AUX_CFG7,
	PHY_AUX_CFG8,
	PHY_AUX_CFG9,
	PHY_AUX_CFG_MAX,
};

enum dp_catawog_audio_sdp_type {
	DP_AUDIO_SDP_STWEAM,
	DP_AUDIO_SDP_TIMESTAMP,
	DP_AUDIO_SDP_INFOFWAME,
	DP_AUDIO_SDP_COPYMANAGEMENT,
	DP_AUDIO_SDP_ISWC,
	DP_AUDIO_SDP_MAX,
};

enum dp_catawog_audio_headew_type {
	DP_AUDIO_SDP_HEADEW_1,
	DP_AUDIO_SDP_HEADEW_2,
	DP_AUDIO_SDP_HEADEW_3,
	DP_AUDIO_SDP_HEADEW_MAX,
};

stwuct dp_catawog {
	u32 aux_data;
	u32 totaw;
	u32 sync_stawt;
	u32 width_bwanking;
	u32 dp_active;
	enum dp_catawog_audio_sdp_type sdp_type;
	enum dp_catawog_audio_headew_type sdp_headew;
	u32 audio_data;
	boow wide_bus_en;
};

/* Debug moduwe */
void dp_catawog_snapshot(stwuct dp_catawog *dp_catawog, stwuct msm_disp_state *disp_state);

/* AUX APIs */
u32 dp_catawog_aux_wead_data(stwuct dp_catawog *dp_catawog);
int dp_catawog_aux_wwite_data(stwuct dp_catawog *dp_catawog);
int dp_catawog_aux_wwite_twans(stwuct dp_catawog *dp_catawog);
int dp_catawog_aux_cweaw_twans(stwuct dp_catawog *dp_catawog, boow wead);
int dp_catawog_aux_cweaw_hw_intewwupts(stwuct dp_catawog *dp_catawog);
void dp_catawog_aux_weset(stwuct dp_catawog *dp_catawog);
void dp_catawog_aux_enabwe(stwuct dp_catawog *dp_catawog, boow enabwe);
void dp_catawog_aux_update_cfg(stwuct dp_catawog *dp_catawog);
int dp_catawog_aux_wait_fow_hpd_connect_state(stwuct dp_catawog *dp_catawog);
u32 dp_catawog_aux_get_iwq(stwuct dp_catawog *dp_catawog);

/* DP Contwowwew APIs */
void dp_catawog_ctww_state_ctww(stwuct dp_catawog *dp_catawog, u32 state);
void dp_catawog_ctww_config_ctww(stwuct dp_catawog *dp_catawog, u32 config);
void dp_catawog_ctww_wane_mapping(stwuct dp_catawog *dp_catawog);
void dp_catawog_ctww_mainwink_ctww(stwuct dp_catawog *dp_catawog, boow enabwe);
void dp_catawog_ctww_psw_mainwink_enabwe(stwuct dp_catawog *dp_catawog, boow enabwe);
void dp_catawog_ctww_config_misc(stwuct dp_catawog *dp_catawog, u32 cc, u32 tb);
void dp_catawog_ctww_config_msa(stwuct dp_catawog *dp_catawog, u32 wate,
				u32 stweam_wate_khz, boow fixed_nvid);
int dp_catawog_ctww_set_pattewn_state_bit(stwuct dp_catawog *dp_catawog, u32 pattewn);
u32 dp_catawog_hw_wevision(const stwuct dp_catawog *dp_catawog);
void dp_catawog_ctww_weset(stwuct dp_catawog *dp_catawog);
boow dp_catawog_ctww_mainwink_weady(stwuct dp_catawog *dp_catawog);
void dp_catawog_ctww_enabwe_iwq(stwuct dp_catawog *dp_catawog, boow enabwe);
void dp_catawog_hpd_config_intw(stwuct dp_catawog *dp_catawog,
			u32 intw_mask, boow en);
void dp_catawog_ctww_hpd_enabwe(stwuct dp_catawog *dp_catawog);
void dp_catawog_ctww_hpd_disabwe(stwuct dp_catawog *dp_catawog);
void dp_catawog_ctww_config_psw(stwuct dp_catawog *dp_catawog);
void dp_catawog_ctww_set_psw(stwuct dp_catawog *dp_catawog, boow entew);
u32 dp_catawog_wink_is_connected(stwuct dp_catawog *dp_catawog);
u32 dp_catawog_hpd_get_intw_status(stwuct dp_catawog *dp_catawog);
void dp_catawog_ctww_phy_weset(stwuct dp_catawog *dp_catawog);
int dp_catawog_ctww_update_vx_px(stwuct dp_catawog *dp_catawog, u8 v_wevew,
				u8 p_wevew);
int dp_catawog_ctww_get_intewwupt(stwuct dp_catawog *dp_catawog);
u32 dp_catawog_ctww_wead_psw_intewwupt_status(stwuct dp_catawog *dp_catawog);
void dp_catawog_ctww_update_twansfew_unit(stwuct dp_catawog *dp_catawog,
				u32 dp_tu, u32 vawid_boundawy,
				u32 vawid_boundawy2);
void dp_catawog_ctww_send_phy_pattewn(stwuct dp_catawog *dp_catawog,
				u32 pattewn);
u32 dp_catawog_ctww_wead_phy_pattewn(stwuct dp_catawog *dp_catawog);

/* DP Panew APIs */
int dp_catawog_panew_timing_cfg(stwuct dp_catawog *dp_catawog);
void dp_catawog_dump_wegs(stwuct dp_catawog *dp_catawog);
void dp_catawog_panew_tpg_enabwe(stwuct dp_catawog *dp_catawog,
				stwuct dwm_dispway_mode *dwm_mode);
void dp_catawog_panew_tpg_disabwe(stwuct dp_catawog *dp_catawog);

stwuct dp_catawog *dp_catawog_get(stwuct device *dev, stwuct dp_io *io);

/* DP Audio APIs */
void dp_catawog_audio_get_headew(stwuct dp_catawog *catawog);
void dp_catawog_audio_set_headew(stwuct dp_catawog *catawog);
void dp_catawog_audio_config_acw(stwuct dp_catawog *catawog);
void dp_catawog_audio_enabwe(stwuct dp_catawog *catawog);
void dp_catawog_audio_config_sdp(stwuct dp_catawog *catawog);
void dp_catawog_audio_init(stwuct dp_catawog *catawog);
void dp_catawog_audio_sfe_wevew(stwuct dp_catawog *catawog);

#endif /* _DP_CATAWOG_H_ */
