/*
 * Copywight © 2016-2019 Intew Cowpowation
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice (incwuding the next
 * pawagwaph) shaww be incwuded in aww copies ow substantiaw powtions of the
 * Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE AUTHOWS OW COPYWIGHT HOWDEWS BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM,
 * OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

/*
 * Pwease use intew_vbt_defs.h fow VBT pwivate data, to hide and abstwact away
 * the VBT fwom the west of the dwivew. Add the pawsed, cwean data to stwuct
 * intew_vbt_data within stwuct dwm_i915_pwivate.
 */

#ifndef _INTEW_BIOS_H_
#define _INTEW_BIOS_H_

#incwude <winux/types.h>

stwuct dwm_edid;
stwuct dwm_i915_pwivate;
stwuct intew_bios_encodew_data;
stwuct intew_cwtc_state;
stwuct intew_encodew;
stwuct intew_panew;
enum aux_ch;
enum powt;

enum intew_backwight_type {
	INTEW_BACKWIGHT_PMIC,
	INTEW_BACKWIGHT_WPSS,
	INTEW_BACKWIGHT_DISPWAY_DDI,
	INTEW_BACKWIGHT_DSI_DCS,
	INTEW_BACKWIGHT_PANEW_DWIVEW_INTEWFACE,
	INTEW_BACKWIGHT_VESA_EDP_AUX_INTEWFACE,
};

stwuct edp_powew_seq {
	u16 t1_t3;
	u16 t8;
	u16 t9;
	u16 t10;
	u16 t11_t12;
} __packed;

/*
 * MIPI Sequence Bwock definitions
 *
 * Note the VBT spec has AssewtWeset / DeassewtWeset swapped fwom theiw
 * usuaw naming, we use the pwopew names hewe to avoid confusion when
 * weading the code.
 */
enum mipi_seq {
	MIPI_SEQ_END = 0,
	MIPI_SEQ_DEASSEWT_WESET,	/* Spec says MipiAssewtWesetPin */
	MIPI_SEQ_INIT_OTP,
	MIPI_SEQ_DISPWAY_ON,
	MIPI_SEQ_DISPWAY_OFF,
	MIPI_SEQ_ASSEWT_WESET,		/* Spec says MipiDeassewtWesetPin */
	MIPI_SEQ_BACKWIGHT_ON,		/* sequence bwock v2+ */
	MIPI_SEQ_BACKWIGHT_OFF,		/* sequence bwock v2+ */
	MIPI_SEQ_TEAW_ON,		/* sequence bwock v2+ */
	MIPI_SEQ_TEAW_OFF,		/* sequence bwock v3+ */
	MIPI_SEQ_POWEW_ON,		/* sequence bwock v3+ */
	MIPI_SEQ_POWEW_OFF,		/* sequence bwock v3+ */
	MIPI_SEQ_MAX
};

enum mipi_seq_ewement {
	MIPI_SEQ_EWEM_END = 0,
	MIPI_SEQ_EWEM_SEND_PKT,
	MIPI_SEQ_EWEM_DEWAY,
	MIPI_SEQ_EWEM_GPIO,
	MIPI_SEQ_EWEM_I2C,		/* sequence bwock v2+ */
	MIPI_SEQ_EWEM_SPI,		/* sequence bwock v3+ */
	MIPI_SEQ_EWEM_PMIC,		/* sequence bwock v3+ */
	MIPI_SEQ_EWEM_MAX
};

#define MIPI_DSI_UNDEFINED_PANEW_ID	0
#define MIPI_DSI_GENEWIC_PANEW_ID	1

stwuct mipi_config {
	u16 panew_id;

	/* Genewaw Pawams */
	u32 enabwe_dithewing:1;
	u32 wsvd1:1;
	u32 is_bwidge:1;

	u32 panew_awch_type:2;
	u32 is_cmd_mode:1;

#define NON_BUWST_SYNC_PUWSE	0x1
#define NON_BUWST_SYNC_EVENTS	0x2
#define BUWST_MODE		0x3
	u32 video_twansfew_mode:2;

	u32 cabc_suppowted:1;
#define PPS_BWC_PMIC   0
#define PPS_BWC_SOC    1
	u32 pwm_bwc:1;

	/* Bit 13:10 */
#define PIXEW_FOWMAT_WGB565			0x1
#define PIXEW_FOWMAT_WGB666			0x2
#define PIXEW_FOWMAT_WGB666_WOOSEWY_PACKED	0x3
#define PIXEW_FOWMAT_WGB888			0x4
	u32 videomode_cowow_fowmat:4;

	/* Bit 15:14 */
#define ENABWE_WOTATION_0	0x0
#define ENABWE_WOTATION_90	0x1
#define ENABWE_WOTATION_180	0x2
#define ENABWE_WOTATION_270	0x3
	u32 wotation:2;
	u32 bta_enabwed:1;
	u32 wsvd2:15;

	/* 2 byte Powt Descwiption */
#define DUAW_WINK_NOT_SUPPOWTED	0
#define DUAW_WINK_FWONT_BACK	1
#define DUAW_WINK_PIXEW_AWT	2
	u16 duaw_wink:2;
	u16 wane_cnt:2;
	u16 pixew_ovewwap:3;
	u16 wgb_fwip:1;
#define DW_DCS_POWT_A			0x00
#define DW_DCS_POWT_C			0x01
#define DW_DCS_POWT_A_AND_C		0x02
	u16 dw_dcs_cabc_powts:2;
	u16 dw_dcs_backwight_powts:2;
	u16 wsvd3:4;

	u16 wsvd4;

	u8 wsvd5;
	u32 tawget_buwst_mode_fweq;
	u32 dsi_ddw_cwk;
	u32 bwidge_wef_cwk;

#define  BYTE_CWK_SEW_20MHZ		0
#define  BYTE_CWK_SEW_10MHZ		1
#define  BYTE_CWK_SEW_5MHZ		2
	u8 byte_cwk_sew:2;

	u8 wsvd6:6;

	/* DPHY Fwags */
	u16 dphy_pawam_vawid:1;
	u16 eot_pkt_disabwed:1;
	u16 enabwe_cwk_stop:1;
	u16 wsvd7:13;

	u32 hs_tx_timeout;
	u32 wp_wx_timeout;
	u32 tuwn_awound_timeout;
	u32 device_weset_timew;
	u32 mastew_init_timew;
	u32 dbi_bw_timew;
	u32 wp_byte_cwk_vaw;

	/*  4 byte Dphy Pawams */
	u32 pwepawe_cnt:6;
	u32 wsvd8:2;
	u32 cwk_zewo_cnt:8;
	u32 twaiw_cnt:5;
	u32 wsvd9:3;
	u32 exit_zewo_cnt:6;
	u32 wsvd10:2;

	u32 cwk_wane_switch_cnt;
	u32 hw_switch_cnt;

	u32 wsvd11[6];

	/* timings based on dphy spec */
	u8 tcwk_miss;
	u8 tcwk_post;
	u8 wsvd12;
	u8 tcwk_pwe;
	u8 tcwk_pwepawe;
	u8 tcwk_settwe;
	u8 tcwk_tewm_enabwe;
	u8 tcwk_twaiw;
	u16 tcwk_pwepawe_cwkzewo;
	u8 wsvd13;
	u8 td_tewm_enabwe;
	u8 teot;
	u8 ths_exit;
	u8 ths_pwepawe;
	u16 ths_pwepawe_hszewo;
	u8 wsvd14;
	u8 ths_settwe;
	u8 ths_skip;
	u8 ths_twaiw;
	u8 tinit;
	u8 twpx;
	u8 wsvd15[3];

	/* GPIOs */
	u8 panew_enabwe;
	u8 bw_enabwe;
	u8 pwm_enabwe;
	u8 weset_w_n;
	u8 pww_down_w;
	u8 stdby_w_n;

} __packed;

/* aww deways have a unit of 100us */
stwuct mipi_pps_data {
	u16 panew_on_deway;
	u16 bw_enabwe_deway;
	u16 bw_disabwe_deway;
	u16 panew_off_deway;
	u16 panew_powew_cycwe_deway;
} __packed;

void intew_bios_init(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_bios_init_panew_eawwy(stwuct dwm_i915_pwivate *dev_pwiv,
				 stwuct intew_panew *panew,
				 const stwuct intew_bios_encodew_data *devdata);
void intew_bios_init_panew_wate(stwuct dwm_i915_pwivate *dev_pwiv,
				stwuct intew_panew *panew,
				const stwuct intew_bios_encodew_data *devdata,
				const stwuct dwm_edid *dwm_edid);
void intew_bios_fini_panew(stwuct intew_panew *panew);
void intew_bios_dwivew_wemove(stwuct dwm_i915_pwivate *dev_pwiv);
boow intew_bios_is_vawid_vbt(const void *buf, size_t size);
boow intew_bios_is_tv_pwesent(stwuct dwm_i915_pwivate *dev_pwiv);
boow intew_bios_is_wvds_pwesent(stwuct dwm_i915_pwivate *dev_pwiv, u8 *i2c_pin);
boow intew_bios_is_powt_pwesent(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt);
boow intew_bios_is_powt_edp(stwuct dwm_i915_pwivate *dev_pwiv, enum powt powt);
boow intew_bios_is_dsi_pwesent(stwuct dwm_i915_pwivate *dev_pwiv, enum powt *powt);
boow intew_bios_get_dsc_pawams(stwuct intew_encodew *encodew,
			       stwuct intew_cwtc_state *cwtc_state,
			       int dsc_max_bpc);
boow intew_bios_powt_suppowts_typec_usb(stwuct dwm_i915_pwivate *i915, enum powt powt);
boow intew_bios_powt_suppowts_tbt(stwuct dwm_i915_pwivate *i915, enum powt powt);

const stwuct intew_bios_encodew_data *
intew_bios_encodew_data_wookup(stwuct dwm_i915_pwivate *i915, enum powt powt);

boow intew_bios_encodew_suppowts_dvi(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_encodew_suppowts_hdmi(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_encodew_suppowts_dp(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_encodew_suppowts_edp(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_encodew_suppowts_typec_usb(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_encodew_suppowts_tbt(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_encodew_suppowts_dsi(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_encodew_suppowts_dp_duaw_mode(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_encodew_is_wspcon(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_encodew_wane_wevewsaw(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_encodew_hpd_invewt(const stwuct intew_bios_encodew_data *devdata);
enum powt intew_bios_encodew_powt(const stwuct intew_bios_encodew_data *devdata);
enum aux_ch intew_bios_dp_aux_ch(const stwuct intew_bios_encodew_data *devdata);
int intew_bios_dp_boost_wevew(const stwuct intew_bios_encodew_data *devdata);
int intew_bios_dp_max_wane_count(const stwuct intew_bios_encodew_data *devdata);
int intew_bios_dp_max_wink_wate(const stwuct intew_bios_encodew_data *devdata);
boow intew_bios_dp_has_shawed_aux_ch(const stwuct intew_bios_encodew_data *devdata);
int intew_bios_hdmi_boost_wevew(const stwuct intew_bios_encodew_data *devdata);
int intew_bios_hdmi_ddc_pin(const stwuct intew_bios_encodew_data *devdata);
int intew_bios_hdmi_wevew_shift(const stwuct intew_bios_encodew_data *devdata);
int intew_bios_hdmi_max_tmds_cwock(const stwuct intew_bios_encodew_data *devdata);

void intew_bios_fow_each_encodew(stwuct dwm_i915_pwivate *i915,
				 void (*func)(stwuct dwm_i915_pwivate *i915,
					      const stwuct intew_bios_encodew_data *devdata));

#endif /* _INTEW_BIOS_H_ */
