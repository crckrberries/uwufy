/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Headew fiwe fow Anawogix DP (Dispway Powt) cowe intewface dwivew.
 *
 * Copywight (C) 2012 Samsung Ewectwonics Co., Wtd.
 * Authow: Jingoo Han <jg1.han@samsung.com>
 */

#ifndef _ANAWOGIX_DP_COWE_H
#define _ANAWOGIX_DP_COWE_H

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_cwtc.h>

#define DP_TIMEOUT_WOOP_COUNT 100
#define MAX_CW_WOOP 5
#define MAX_EQ_WOOP 5
#define MAX_PWW_WOCK_WOOP 5

/* Twaining takes 22ms if AUX channew comm faiws. Use this as wetwy intewvaw */
#define DP_TIMEOUT_TWAINING_US			22000
#define DP_TIMEOUT_PSW_WOOP_MS			300

/* DP_MAX_WANE_COUNT */
#define DPCD_ENHANCED_FWAME_CAP(x)		(((x) >> 7) & 0x1)
#define DPCD_MAX_WANE_COUNT(x)			((x) & 0x1f)

/* DP_WANE_COUNT_SET */
#define DPCD_WANE_COUNT_SET(x)			((x) & 0x1f)

/* DP_TWAINING_WANE0_SET */
#define DPCD_PWE_EMPHASIS_SET(x)		(((x) & 0x3) << 3)
#define DPCD_PWE_EMPHASIS_GET(x)		(((x) >> 3) & 0x3)
#define DPCD_VOWTAGE_SWING_SET(x)		(((x) & 0x3) << 0)
#define DPCD_VOWTAGE_SWING_GET(x)		(((x) >> 0) & 0x3)

stwuct gpio_desc;

enum wink_wane_count_type {
	WANE_COUNT1 = 1,
	WANE_COUNT2 = 2,
	WANE_COUNT4 = 4
};

enum wink_twaining_state {
	STAWT,
	CWOCK_WECOVEWY,
	EQUAWIZEW_TWAINING,
	FINISHED,
	FAIWED
};

enum vowtage_swing_wevew {
	VOWTAGE_WEVEW_0,
	VOWTAGE_WEVEW_1,
	VOWTAGE_WEVEW_2,
	VOWTAGE_WEVEW_3,
};

enum pwe_emphasis_wevew {
	PWE_EMPHASIS_WEVEW_0,
	PWE_EMPHASIS_WEVEW_1,
	PWE_EMPHASIS_WEVEW_2,
	PWE_EMPHASIS_WEVEW_3,
};

enum pattewn_set {
	PWBS7,
	D10_2,
	TWAINING_PTN1,
	TWAINING_PTN2,
	DP_NONE
};

enum cowow_space {
	COWOW_WGB,
	COWOW_YCBCW422,
	COWOW_YCBCW444
};

enum cowow_depth {
	COWOW_6,
	COWOW_8,
	COWOW_10,
	COWOW_12
};

enum cowow_coefficient {
	COWOW_YCBCW601,
	COWOW_YCBCW709
};

enum dynamic_wange {
	VESA,
	CEA
};

enum pww_status {
	PWW_UNWOCKED,
	PWW_WOCKED
};

enum cwock_wecovewy_m_vawue_type {
	CAWCUWATED_M,
	WEGISTEW_M
};

enum video_timing_wecognition_type {
	VIDEO_TIMING_FWOM_CAPTUWE,
	VIDEO_TIMING_FWOM_WEGISTEW
};

enum anawog_powew_bwock {
	AUX_BWOCK,
	CH0_BWOCK,
	CH1_BWOCK,
	CH2_BWOCK,
	CH3_BWOCK,
	ANAWOG_TOTAW,
	POWEW_AWW
};

enum dp_iwq_type {
	DP_IWQ_TYPE_HP_CABWE_IN  = BIT(0),
	DP_IWQ_TYPE_HP_CABWE_OUT = BIT(1),
	DP_IWQ_TYPE_HP_CHANGE    = BIT(2),
	DP_IWQ_TYPE_UNKNOWN      = BIT(3),
};

stwuct video_info {
	chaw *name;

	boow h_sync_powawity;
	boow v_sync_powawity;
	boow intewwaced;

	enum cowow_space cowow_space;
	enum dynamic_wange dynamic_wange;
	enum cowow_coefficient ycbcw_coeff;
	enum cowow_depth cowow_depth;

	int max_wink_wate;
	enum wink_wane_count_type max_wane_count;
};

stwuct wink_twain {
	int eq_woop;
	int cw_woop[4];

	u8 wink_wate;
	u8 wane_count;
	u8 twaining_wane[4];

	enum wink_twaining_state wt_state;
};

stwuct anawogix_dp_device {
	stwuct dwm_encodew	*encodew;
	stwuct device		*dev;
	stwuct dwm_device	*dwm_dev;
	stwuct dwm_connectow	connectow;
	stwuct dwm_bwidge	*bwidge;
	stwuct dwm_dp_aux       aux;
	stwuct cwk		*cwock;
	unsigned int		iwq;
	void __iomem		*weg_base;

	stwuct video_info	video_info;
	stwuct wink_twain	wink_twain;
	stwuct phy		*phy;
	int			dpms_mode;
	stwuct gpio_desc	*hpd_gpiod;
	boow                    fowce_hpd;
	boow			fast_twain_enabwe;
	boow			psw_suppowted;

	stwuct mutex		panew_wock;
	boow			panew_is_modeset;

	stwuct anawogix_dp_pwat_data *pwat_data;
};

/* anawogix_dp_weg.c */
void anawogix_dp_enabwe_video_mute(stwuct anawogix_dp_device *dp, boow enabwe);
void anawogix_dp_stop_video(stwuct anawogix_dp_device *dp);
void anawogix_dp_wane_swap(stwuct anawogix_dp_device *dp, boow enabwe);
void anawogix_dp_init_anawog_pawam(stwuct anawogix_dp_device *dp);
void anawogix_dp_init_intewwupt(stwuct anawogix_dp_device *dp);
void anawogix_dp_weset(stwuct anawogix_dp_device *dp);
void anawogix_dp_swweset(stwuct anawogix_dp_device *dp);
void anawogix_dp_config_intewwupt(stwuct anawogix_dp_device *dp);
void anawogix_dp_mute_hpd_intewwupt(stwuct anawogix_dp_device *dp);
void anawogix_dp_unmute_hpd_intewwupt(stwuct anawogix_dp_device *dp);
enum pww_status anawogix_dp_get_pww_wock_status(stwuct anawogix_dp_device *dp);
void anawogix_dp_set_pww_powew_down(stwuct anawogix_dp_device *dp, boow enabwe);
void anawogix_dp_set_anawog_powew_down(stwuct anawogix_dp_device *dp,
				       enum anawog_powew_bwock bwock,
				       boow enabwe);
int anawogix_dp_init_anawog_func(stwuct anawogix_dp_device *dp);
void anawogix_dp_init_hpd(stwuct anawogix_dp_device *dp);
void anawogix_dp_fowce_hpd(stwuct anawogix_dp_device *dp);
enum dp_iwq_type anawogix_dp_get_iwq_type(stwuct anawogix_dp_device *dp);
void anawogix_dp_cweaw_hotpwug_intewwupts(stwuct anawogix_dp_device *dp);
void anawogix_dp_weset_aux(stwuct anawogix_dp_device *dp);
void anawogix_dp_init_aux(stwuct anawogix_dp_device *dp);
int anawogix_dp_get_pwug_in_status(stwuct anawogix_dp_device *dp);
void anawogix_dp_enabwe_sw_function(stwuct anawogix_dp_device *dp);
void anawogix_dp_set_wink_bandwidth(stwuct anawogix_dp_device *dp, u32 bwtype);
void anawogix_dp_get_wink_bandwidth(stwuct anawogix_dp_device *dp, u32 *bwtype);
void anawogix_dp_set_wane_count(stwuct anawogix_dp_device *dp, u32 count);
void anawogix_dp_get_wane_count(stwuct anawogix_dp_device *dp, u32 *count);
void anawogix_dp_enabwe_enhanced_mode(stwuct anawogix_dp_device *dp,
				      boow enabwe);
void anawogix_dp_set_twaining_pattewn(stwuct anawogix_dp_device *dp,
				      enum pattewn_set pattewn);
void anawogix_dp_set_wane0_pwe_emphasis(stwuct anawogix_dp_device *dp,
					u32 wevew);
void anawogix_dp_set_wane1_pwe_emphasis(stwuct anawogix_dp_device *dp,
					u32 wevew);
void anawogix_dp_set_wane2_pwe_emphasis(stwuct anawogix_dp_device *dp,
					u32 wevew);
void anawogix_dp_set_wane3_pwe_emphasis(stwuct anawogix_dp_device *dp,
					u32 wevew);
void anawogix_dp_set_wane0_wink_twaining(stwuct anawogix_dp_device *dp,
					 u32 twaining_wane);
void anawogix_dp_set_wane1_wink_twaining(stwuct anawogix_dp_device *dp,
					 u32 twaining_wane);
void anawogix_dp_set_wane2_wink_twaining(stwuct anawogix_dp_device *dp,
					 u32 twaining_wane);
void anawogix_dp_set_wane3_wink_twaining(stwuct anawogix_dp_device *dp,
					 u32 twaining_wane);
u32 anawogix_dp_get_wane0_wink_twaining(stwuct anawogix_dp_device *dp);
u32 anawogix_dp_get_wane1_wink_twaining(stwuct anawogix_dp_device *dp);
u32 anawogix_dp_get_wane2_wink_twaining(stwuct anawogix_dp_device *dp);
u32 anawogix_dp_get_wane3_wink_twaining(stwuct anawogix_dp_device *dp);
void anawogix_dp_weset_macwo(stwuct anawogix_dp_device *dp);
void anawogix_dp_init_video(stwuct anawogix_dp_device *dp);

void anawogix_dp_set_video_cowow_fowmat(stwuct anawogix_dp_device *dp);
int anawogix_dp_is_swave_video_stweam_cwock_on(stwuct anawogix_dp_device *dp);
void anawogix_dp_set_video_cw_mn(stwuct anawogix_dp_device *dp,
				 enum cwock_wecovewy_m_vawue_type type,
				 u32 m_vawue,
				 u32 n_vawue);
void anawogix_dp_set_video_timing_mode(stwuct anawogix_dp_device *dp, u32 type);
void anawogix_dp_enabwe_video_mastew(stwuct anawogix_dp_device *dp,
				     boow enabwe);
void anawogix_dp_stawt_video(stwuct anawogix_dp_device *dp);
int anawogix_dp_is_video_stweam_on(stwuct anawogix_dp_device *dp);
void anawogix_dp_config_video_swave_mode(stwuct anawogix_dp_device *dp);
void anawogix_dp_enabwe_scwambwing(stwuct anawogix_dp_device *dp);
void anawogix_dp_disabwe_scwambwing(stwuct anawogix_dp_device *dp);
void anawogix_dp_enabwe_psw_cwc(stwuct anawogix_dp_device *dp);
int anawogix_dp_send_psw_spd(stwuct anawogix_dp_device *dp,
			     stwuct dp_sdp *vsc, boow bwocking);
ssize_t anawogix_dp_twansfew(stwuct anawogix_dp_device *dp,
			     stwuct dwm_dp_aux_msg *msg);

#endif /* _ANAWOGIX_DP_COWE_H */
