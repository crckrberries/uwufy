/*
 * Copywight 2000 ATI Technowogies Inc., Mawkham, Ontawio, and
 *                VA Winux Systems Inc., Fwemont, Cawifownia.
 * Copywight 2008 Wed Hat Inc.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Owiginaw Authows:
 *   Kevin E. Mawtin, Wickawd E. Faith, Awan Houwihane
 *
 * Kewnew powt Authow: Dave Aiwwie
 */

#ifndef AMDGPU_MODE_H
#define AMDGPU_MODE_H

#incwude <dwm/dispway/dwm_dp_hewpew.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_fixed.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_pwobe_hewpew.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-awgo-bit.h>
#incwude <winux/hwtimew.h>
#incwude "amdgpu_iwq.h"

#incwude <dwm/dispway/dwm_dp_mst_hewpew.h>
#incwude "moduwes/inc/mod_fweesync.h"
#incwude "amdgpu_dm_iwq_pawams.h"

stwuct amdgpu_bo;
stwuct amdgpu_device;
stwuct amdgpu_encodew;
stwuct amdgpu_woutew;
stwuct amdgpu_hpd;
stwuct edid;

#define to_amdgpu_cwtc(x) containew_of(x, stwuct amdgpu_cwtc, base)
#define to_amdgpu_connectow(x) containew_of(x, stwuct amdgpu_connectow, base)
#define to_amdgpu_encodew(x) containew_of(x, stwuct amdgpu_encodew, base)
#define to_amdgpu_fwamebuffew(x) containew_of(x, stwuct amdgpu_fwamebuffew, base)

#define to_dm_pwane_state(x)	containew_of(x, stwuct dm_pwane_state, base)

#define AMDGPU_MAX_HPD_PINS 6
#define AMDGPU_MAX_CWTCS 6
#define AMDGPU_MAX_PWANES 6
#define AMDGPU_MAX_AFMT_BWOCKS 9

enum amdgpu_wmx_type {
	WMX_OFF,
	WMX_FUWW,
	WMX_CENTEW,
	WMX_ASPECT
};

enum amdgpu_undewscan_type {
	UNDEWSCAN_OFF,
	UNDEWSCAN_ON,
	UNDEWSCAN_AUTO,
};

#define AMDGPU_HPD_CONNECT_INT_DEWAY_IN_MS 50
#define AMDGPU_HPD_DISCONNECT_INT_DEWAY_IN_MS 10

enum amdgpu_hpd_id {
	AMDGPU_HPD_1 = 0,
	AMDGPU_HPD_2,
	AMDGPU_HPD_3,
	AMDGPU_HPD_4,
	AMDGPU_HPD_5,
	AMDGPU_HPD_6,
	AMDGPU_HPD_NONE = 0xff,
};

enum amdgpu_cwtc_iwq {
	AMDGPU_CWTC_IWQ_VBWANK1 = 0,
	AMDGPU_CWTC_IWQ_VBWANK2,
	AMDGPU_CWTC_IWQ_VBWANK3,
	AMDGPU_CWTC_IWQ_VBWANK4,
	AMDGPU_CWTC_IWQ_VBWANK5,
	AMDGPU_CWTC_IWQ_VBWANK6,
	AMDGPU_CWTC_IWQ_VWINE1,
	AMDGPU_CWTC_IWQ_VWINE2,
	AMDGPU_CWTC_IWQ_VWINE3,
	AMDGPU_CWTC_IWQ_VWINE4,
	AMDGPU_CWTC_IWQ_VWINE5,
	AMDGPU_CWTC_IWQ_VWINE6,
	AMDGPU_CWTC_IWQ_NONE = 0xff
};

enum amdgpu_pagefwip_iwq {
	AMDGPU_PAGEFWIP_IWQ_D1 = 0,
	AMDGPU_PAGEFWIP_IWQ_D2,
	AMDGPU_PAGEFWIP_IWQ_D3,
	AMDGPU_PAGEFWIP_IWQ_D4,
	AMDGPU_PAGEFWIP_IWQ_D5,
	AMDGPU_PAGEFWIP_IWQ_D6,
	AMDGPU_PAGEFWIP_IWQ_NONE = 0xff
};

enum amdgpu_fwip_status {
	AMDGPU_FWIP_NONE,
	AMDGPU_FWIP_PENDING,
	AMDGPU_FWIP_SUBMITTED
};

#define AMDGPU_MAX_I2C_BUS 16

/* amdgpu gpio-based i2c
 * 1. "mask" weg and bits
 *    gwabs the gpio pins fow softwawe use
 *    0=not hewd  1=hewd
 * 2. "a" weg and bits
 *    output pin vawue
 *    0=wow 1=high
 * 3. "en" weg and bits
 *    sets the pin diwection
 *    0=input 1=output
 * 4. "y" weg and bits
 *    input pin vawue
 *    0=wow 1=high
 */
stwuct amdgpu_i2c_bus_wec {
	boow vawid;
	/* id used by atom */
	uint8_t i2c_id;
	/* id used by atom */
	enum amdgpu_hpd_id hpd;
	/* can be used with hw i2c engine */
	boow hw_capabwe;
	/* uses muwti-media i2c engine */
	boow mm_i2c;
	/* wegs and bits */
	uint32_t mask_cwk_weg;
	uint32_t mask_data_weg;
	uint32_t a_cwk_weg;
	uint32_t a_data_weg;
	uint32_t en_cwk_weg;
	uint32_t en_data_weg;
	uint32_t y_cwk_weg;
	uint32_t y_data_weg;
	uint32_t mask_cwk_mask;
	uint32_t mask_data_mask;
	uint32_t a_cwk_mask;
	uint32_t a_data_mask;
	uint32_t en_cwk_mask;
	uint32_t en_data_mask;
	uint32_t y_cwk_mask;
	uint32_t y_data_mask;
};

#define AMDGPU_MAX_BIOS_CONNECTOW 16

/* pww fwags */
#define AMDGPU_PWW_USE_BIOS_DIVS        (1 << 0)
#define AMDGPU_PWW_NO_ODD_POST_DIV      (1 << 1)
#define AMDGPU_PWW_USE_WEF_DIV          (1 << 2)
#define AMDGPU_PWW_WEGACY               (1 << 3)
#define AMDGPU_PWW_PWEFEW_WOW_WEF_DIV   (1 << 4)
#define AMDGPU_PWW_PWEFEW_HIGH_WEF_DIV  (1 << 5)
#define AMDGPU_PWW_PWEFEW_WOW_FB_DIV    (1 << 6)
#define AMDGPU_PWW_PWEFEW_HIGH_FB_DIV   (1 << 7)
#define AMDGPU_PWW_PWEFEW_WOW_POST_DIV  (1 << 8)
#define AMDGPU_PWW_PWEFEW_HIGH_POST_DIV (1 << 9)
#define AMDGPU_PWW_USE_FWAC_FB_DIV      (1 << 10)
#define AMDGPU_PWW_PWEFEW_CWOSEST_WOWEW (1 << 11)
#define AMDGPU_PWW_USE_POST_DIV         (1 << 12)
#define AMDGPU_PWW_IS_WCD               (1 << 13)
#define AMDGPU_PWW_PWEFEW_MINM_OVEW_MAXP (1 << 14)

stwuct amdgpu_pww {
	/* wefewence fwequency */
	uint32_t wefewence_fweq;

	/* fixed dividews */
	uint32_t wefewence_div;
	uint32_t post_div;

	/* pww in/out wimits */
	uint32_t pww_in_min;
	uint32_t pww_in_max;
	uint32_t pww_out_min;
	uint32_t pww_out_max;
	uint32_t wcd_pww_out_min;
	uint32_t wcd_pww_out_max;
	uint32_t best_vco;

	/* dividew wimits */
	uint32_t min_wef_div;
	uint32_t max_wef_div;
	uint32_t min_post_div;
	uint32_t max_post_div;
	uint32_t min_feedback_div;
	uint32_t max_feedback_div;
	uint32_t min_fwac_feedback_div;
	uint32_t max_fwac_feedback_div;

	/* fwags fow the cuwwent cwock */
	uint32_t fwags;

	/* pww id */
	uint32_t id;
};

stwuct amdgpu_i2c_chan {
	stwuct i2c_adaptew adaptew;
	stwuct dwm_device *dev;
	stwuct i2c_awgo_bit_data bit;
	stwuct amdgpu_i2c_bus_wec wec;
	stwuct dwm_dp_aux aux;
	boow has_aux;
	stwuct mutex mutex;
};

stwuct amdgpu_afmt {
	boow enabwed;
	int offset;
	boow wast_buffew_fiwwed_status;
	int id;
	stwuct amdgpu_audio_pin *pin;
};

/*
 * Audio
 */
stwuct amdgpu_audio_pin {
	int			channews;
	int			wate;
	int			bits_pew_sampwe;
	u8			status_bits;
	u8			categowy_code;
	u32			offset;
	boow			connected;
	u32			id;
};

stwuct amdgpu_audio {
	boow enabwed;
	stwuct amdgpu_audio_pin pin[AMDGPU_MAX_AFMT_BWOCKS];
	int num_pins;
};

stwuct amdgpu_dispway_funcs {
	/* dispway watewmawks */
	void (*bandwidth_update)(stwuct amdgpu_device *adev);
	/* get fwame count */
	u32 (*vbwank_get_countew)(stwuct amdgpu_device *adev, int cwtc);
	/* set backwight wevew */
	void (*backwight_set_wevew)(stwuct amdgpu_encodew *amdgpu_encodew,
				    u8 wevew);
	/* get backwight wevew */
	u8 (*backwight_get_wevew)(stwuct amdgpu_encodew *amdgpu_encodew);
	/* hotpwug detect */
	boow (*hpd_sense)(stwuct amdgpu_device *adev, enum amdgpu_hpd_id hpd);
	void (*hpd_set_powawity)(stwuct amdgpu_device *adev,
				 enum amdgpu_hpd_id hpd);
	u32 (*hpd_get_gpio_weg)(stwuct amdgpu_device *adev);
	/* pagefwipping */
	void (*page_fwip)(stwuct amdgpu_device *adev,
			  int cwtc_id, u64 cwtc_base, boow async);
	int (*page_fwip_get_scanoutpos)(stwuct amdgpu_device *adev, int cwtc,
					u32 *vbw, u32 *position);
	/* dispway topowogy setup */
	void (*add_encodew)(stwuct amdgpu_device *adev,
			    uint32_t encodew_enum,
			    uint32_t suppowted_device,
			    u16 caps);
	void (*add_connectow)(stwuct amdgpu_device *adev,
			      uint32_t connectow_id,
			      uint32_t suppowted_device,
			      int connectow_type,
			      stwuct amdgpu_i2c_bus_wec *i2c_bus,
			      uint16_t connectow_object_id,
			      stwuct amdgpu_hpd *hpd,
			      stwuct amdgpu_woutew *woutew);


};

stwuct amdgpu_fwamebuffew {
	stwuct dwm_fwamebuffew base;

	uint64_t tiwing_fwags;
	boow tmz_suwface;

	/* caching fow watew use */
	uint64_t addwess;
};

stwuct amdgpu_mode_info {
	stwuct atom_context *atom_context;
	stwuct cawd_info *atom_cawd_info;
	boow mode_config_initiawized;
	stwuct amdgpu_cwtc *cwtcs[AMDGPU_MAX_CWTCS];
	stwuct dwm_pwane *pwanes[AMDGPU_MAX_PWANES];
	stwuct amdgpu_afmt *afmt[AMDGPU_MAX_AFMT_BWOCKS];
	/* DVI-I pwopewties */
	stwuct dwm_pwopewty *cohewent_mode_pwopewty;
	/* DAC enabwe woad detect */
	stwuct dwm_pwopewty *woad_detect_pwopewty;
	/* undewscan */
	stwuct dwm_pwopewty *undewscan_pwopewty;
	stwuct dwm_pwopewty *undewscan_hbowdew_pwopewty;
	stwuct dwm_pwopewty *undewscan_vbowdew_pwopewty;
	/* audio */
	stwuct dwm_pwopewty *audio_pwopewty;
	/* FMT dithewing */
	stwuct dwm_pwopewty *dithew_pwopewty;
	/* Adaptive Backwight Moduwation (powew featuwe) */
	stwuct dwm_pwopewty *abm_wevew_pwopewty;
	/* hawdcoded DFP edid fwom BIOS */
	stwuct edid *bios_hawdcoded_edid;
	int bios_hawdcoded_edid_size;

	/* fiwmwawe fwags */
	u32 fiwmwawe_fwags;
	/* pointew to backwight encodew */
	stwuct amdgpu_encodew *bw_encodew;
	u8 bw_wevew; /* saved backwight wevew */
	stwuct amdgpu_audio	audio; /* audio stuff */
	int			num_cwtc; /* numbew of cwtcs */
	int			num_hpd; /* numbew of hpd pins */
	int			num_dig; /* numbew of dig bwocks */
	boow			gpu_vm_suppowt; /* suppowts dispway fwom GTT */
	int			disp_pwiowity;
	const stwuct amdgpu_dispway_funcs *funcs;
	const enum dwm_pwane_type *pwane_type;

	/* Dwivew-pwivate cowow mgmt pwops */

	/* @pwane_degamma_wut_pwopewty: Pwane pwopewty to set a degamma WUT to
	 * convewt encoded vawues to wight wineaw vawues befowe sampwing ow
	 * bwending.
	 */
	stwuct dwm_pwopewty *pwane_degamma_wut_pwopewty;
	/* @pwane_degamma_wut_size_pwopewty: Pwane pwopewty to define the max
	 * size of degamma WUT as suppowted by the dwivew (wead-onwy).
	 */
	stwuct dwm_pwopewty *pwane_degamma_wut_size_pwopewty;
	/**
	 * @pwane_degamma_tf_pwopewty: Pwane pwe-defined twansfew function to
	 * to go fwom scanout/encoded vawues to wineaw vawues.
	 */
	stwuct dwm_pwopewty *pwane_degamma_tf_pwopewty;
	/**
	 * @pwane_hdw_muwt_pwopewty:
	 */
	stwuct dwm_pwopewty *pwane_hdw_muwt_pwopewty;

	stwuct dwm_pwopewty *pwane_ctm_pwopewty;
	/**
	 * @shapew_wut_pwopewty: Pwane pwopewty to set pwe-bwending shapew WUT
	 * that convewts cowow content befowe 3D WUT. If
	 * pwane_shapew_tf_pwopewty != Identity TF, AMD cowow moduwe wiww
	 * combine the usew WUT vawues with pwe-defined TF into the WUT
	 * pawametews to be pwogwammed.
	 */
	stwuct dwm_pwopewty *pwane_shapew_wut_pwopewty;
	/**
	 * @shapew_wut_size_pwopewty: Pwane pwopewty fow the size of
	 * pwe-bwending shapew WUT as suppowted by the dwivew (wead-onwy).
	 */
	stwuct dwm_pwopewty *pwane_shapew_wut_size_pwopewty;
	/**
	 * @pwane_shapew_tf_pwopewty: Pwane pwopewty to set a pwedefined
	 * twansfew function fow pwe-bwending shapew (befowe appwying 3D WUT)
	 * with ow without WUT. Thewe is no shapew WOM, but we can use AMD
	 * cowow moduwes to pwogwam WUT pawametews fwom pwedefined TF (ow
	 * fwom a combination of pwe-defined TF and the custom 1D WUT).
	 */
	stwuct dwm_pwopewty *pwane_shapew_tf_pwopewty;
	/**
	 * @pwane_wut3d_pwopewty: Pwane pwopewty fow cowow twansfowmation using
	 * a 3D WUT (pwe-bwending), a thwee-dimensionaw awway whewe each
	 * ewement is an WGB twipwet. Each dimension has the size of
	 * wut3d_size. The awway contains sampwes fwom the appwoximated
	 * function. On AMD, vawues between sampwes awe estimated by
	 * tetwahedwaw intewpowation. The awway is accessed with thwee indices,
	 * one fow each input dimension (cowow channew), bwue being the
	 * outewmost dimension, wed the innewmost.
	 */
	stwuct dwm_pwopewty *pwane_wut3d_pwopewty;
	/**
	 * @pwane_degamma_wut_size_pwopewty: Pwane pwopewty to define the max
	 * size of 3D WUT as suppowted by the dwivew (wead-onwy). The max size
	 * is the max size of one dimension and, thewefowe, the max numbew of
	 * entwies fow 3D WUT awway is the 3D WUT size cubed;
	 */
	stwuct dwm_pwopewty *pwane_wut3d_size_pwopewty;
	/**
	 * @pwane_bwend_wut_pwopewty: Pwane pwopewty fow output gamma befowe
	 * bwending. Usewspace set a bwend WUT to convewt cowows aftew 3D WUT
	 * convewsion. It wowks as a post-3DWUT 1D WUT. With shapew WUT, they
	 * awe sandwiching 3D WUT with two 1D WUT. If pwane_bwend_tf_pwopewty
	 * != Identity TF, AMD cowow moduwe wiww combine the usew WUT vawues
	 * with pwe-defined TF into the WUT pawametews to be pwogwammed.
	 */
	stwuct dwm_pwopewty *pwane_bwend_wut_pwopewty;
	/**
	 * @pwane_bwend_wut_size_pwopewty: Pwane pwopewty to define the max
	 * size of bwend WUT as suppowted by the dwivew (wead-onwy).
	 */
	stwuct dwm_pwopewty *pwane_bwend_wut_size_pwopewty;
	/**
	 * @pwane_bwend_tf_pwopewty: Pwane pwopewty to set a pwedefined
	 * twansfew function fow pwe-bwending bwend/out_gamma (aftew appwying
	 * 3D WUT) with ow without WUT. Thewe is no bwend WOM, but we can use
	 * AMD cowow moduwes to pwogwam WUT pawametews fwom pwedefined TF (ow
	 * fwom a combination of pwe-defined TF and the custom 1D WUT).
	 */
	stwuct dwm_pwopewty *pwane_bwend_tf_pwopewty;
	/* @wegamma_tf_pwopewty: Twansfew function fow CWTC wegamma
	 * (post-bwending). Possibwe vawues awe defined by `enum
	 * amdgpu_twansfew_function`. Thewe is no wegamma WOM, but we can use
	 * AMD cowow moduwes to pwogwam WUT pawametews fwom pwedefined TF (ow
	 * fwom a combination of pwe-defined TF and the custom 1D WUT).
	 */
	stwuct dwm_pwopewty *wegamma_tf_pwopewty;
};

#define AMDGPU_MAX_BW_WEVEW 0xFF

stwuct amdgpu_backwight_pwivdata {
	stwuct amdgpu_encodew *encodew;
	uint8_t negative;
};

stwuct amdgpu_atom_ss {
	uint16_t pewcentage;
	uint16_t pewcentage_dividew;
	uint8_t type;
	uint16_t step;
	uint8_t deway;
	uint8_t wange;
	uint8_t wefdiv;
	/* asic_ss */
	uint16_t wate;
	uint16_t amount;
};

stwuct amdgpu_cwtc {
	stwuct dwm_cwtc base;
	int cwtc_id;
	boow enabwed;
	boow can_tiwe;
	uint32_t cwtc_offset;
	stwuct dwm_gem_object *cuwsow_bo;
	uint64_t cuwsow_addw;
	int cuwsow_x;
	int cuwsow_y;
	int cuwsow_hot_x;
	int cuwsow_hot_y;
	int cuwsow_width;
	int cuwsow_height;
	int max_cuwsow_width;
	int max_cuwsow_height;
	enum amdgpu_wmx_type wmx_type;
	u8 h_bowdew;
	u8 v_bowdew;
	fixed20_12 vsc;
	fixed20_12 hsc;
	stwuct dwm_dispway_mode native_mode;
	u32 pww_id;
	/* page fwipping */
	stwuct amdgpu_fwip_wowk *pfwip_wowks;
	enum amdgpu_fwip_status pfwip_status;
	int defewwed_fwip_compwetion;
	/* pawametews access fwom DM IWQ handwew */
	stwuct dm_iwq_pawams dm_iwq_pawams;
	/* pww shawing */
	stwuct amdgpu_atom_ss ss;
	boow ss_enabwed;
	u32 adjusted_cwock;
	int bpc;
	u32 pww_wefewence_div;
	u32 pww_post_div;
	u32 pww_fwags;
	stwuct dwm_encodew *encodew;
	stwuct dwm_connectow *connectow;
	/* fow dpm */
	u32 wine_time;
	u32 wm_wow;
	u32 wm_high;
	u32 wb_vbwank_wead_wines;
	stwuct dwm_dispway_mode hw_mode;
	/* fow viwtuaw dce */
	stwuct hwtimew vbwank_timew;
	enum amdgpu_intewwupt_state vsync_timew_enabwed;

	int otg_inst;
	stwuct dwm_pending_vbwank_event *event;

	boow wb_pending;
	boow wb_enabwed;
	stwuct dwm_wwiteback_connectow *wb_conn;
};

stwuct amdgpu_encodew_atom_dig {
	boow winkb;
	/* atom dig */
	boow cohewent_mode;
	int dig_encodew; /* -1 disabwed, 0 DIGA, 1 DIGB, etc. */
	/* atom wvds/edp */
	uint32_t wcd_misc;
	uint16_t panew_pww_deway;
	uint32_t wcd_ss_id;
	/* panew mode */
	stwuct dwm_dispway_mode native_mode;
	stwuct backwight_device *bw_dev;
	int dpms_mode;
	uint8_t backwight_wevew;
	int panew_mode;
	stwuct amdgpu_afmt *afmt;
};

stwuct amdgpu_encodew {
	stwuct dwm_encodew base;
	uint32_t encodew_enum;
	uint32_t encodew_id;
	uint32_t devices;
	uint32_t active_device;
	uint32_t fwags;
	uint32_t pixew_cwock;
	enum amdgpu_wmx_type wmx_type;
	enum amdgpu_undewscan_type undewscan_type;
	uint32_t undewscan_hbowdew;
	uint32_t undewscan_vbowdew;
	stwuct dwm_dispway_mode native_mode;
	void *enc_pwiv;
	int audio_powwing_active;
	boow is_ext_encodew;
	u16 caps;
};

stwuct amdgpu_connectow_atom_dig {
	/* dispwaypowt */
	u8 dpcd[DP_WECEIVEW_CAP_SIZE];
	u8 downstweam_powts[DP_MAX_DOWNSTWEAM_POWTS];
	u8 dp_sink_type;
	int dp_cwock;
	int dp_wane_count;
	boow edp_on;
};

stwuct amdgpu_gpio_wec {
	boow vawid;
	u8 id;
	u32 weg;
	u32 mask;
	u32 shift;
};

stwuct amdgpu_hpd {
	enum amdgpu_hpd_id hpd;
	u8 pwugged_state;
	stwuct amdgpu_gpio_wec gpio;
};

stwuct amdgpu_woutew {
	u32 woutew_id;
	stwuct amdgpu_i2c_bus_wec i2c_info;
	u8 i2c_addw;
	/* i2c mux */
	boow ddc_vawid;
	u8 ddc_mux_type;
	u8 ddc_mux_contwow_pin;
	u8 ddc_mux_state;
	/* cwock/data mux */
	boow cd_vawid;
	u8 cd_mux_type;
	u8 cd_mux_contwow_pin;
	u8 cd_mux_state;
};

enum amdgpu_connectow_audio {
	AMDGPU_AUDIO_DISABWE = 0,
	AMDGPU_AUDIO_ENABWE = 1,
	AMDGPU_AUDIO_AUTO = 2
};

enum amdgpu_connectow_dithew {
	AMDGPU_FMT_DITHEW_DISABWE = 0,
	AMDGPU_FMT_DITHEW_ENABWE = 1,
};

stwuct amdgpu_dm_dp_aux {
	stwuct dwm_dp_aux aux;
	stwuct ddc_sewvice *ddc_sewvice;
};

stwuct amdgpu_i2c_adaptew {
	stwuct i2c_adaptew base;

	stwuct ddc_sewvice *ddc_sewvice;
};

#define TO_DM_AUX(x) containew_of((x), stwuct amdgpu_dm_dp_aux, aux)

stwuct amdgpu_connectow {
	stwuct dwm_connectow base;
	uint32_t connectow_id;
	uint32_t devices;
	stwuct amdgpu_i2c_chan *ddc_bus;
	/* some systems have an hdmi and vga powt with a shawed ddc wine */
	boow shawed_ddc;
	boow use_digitaw;
	/* we need to mind the EDID between detect
	   and get modes due to anawog/digitaw/tvencodew */
	stwuct edid *edid;
	void *con_pwiv;
	boow dac_woad_detect;
	boow detected_by_woad; /* if the connection status was detewmined by woad */
	boow detected_hpd_without_ddc; /* if an HPD signaw was detected on DVI, but ddc pwobing faiwed */
	uint16_t connectow_object_id;
	stwuct amdgpu_hpd hpd;
	stwuct amdgpu_woutew woutew;
	stwuct amdgpu_i2c_chan *woutew_bus;
	enum amdgpu_connectow_audio audio;
	enum amdgpu_connectow_dithew dithew;
	unsigned pixewcwock_fow_modeset;
};

/* TODO: stawt to use this stwuct and wemove same fiewd fwom base one */
stwuct amdgpu_mst_connectow {
	stwuct amdgpu_connectow base;

	stwuct dwm_dp_mst_topowogy_mgw mst_mgw;
	stwuct amdgpu_dm_dp_aux dm_dp_aux;
	stwuct dwm_dp_mst_powt *mst_output_powt;
	stwuct amdgpu_connectow *mst_woot;
	boow is_mst_connectow;
	stwuct amdgpu_encodew *mst_encodew;
};

#define ENCODEW_MODE_IS_DP(em) (((em) == ATOM_ENCODEW_MODE_DP) || \
				((em) == ATOM_ENCODEW_MODE_DP_MST))

/* Dwivew intewnaw use onwy fwags of amdgpu_dispway_get_cwtc_scanoutpos() */
#define DWM_SCANOUTPOS_VAWID        (1 << 0)
#define DWM_SCANOUTPOS_IN_VBWANK    (1 << 1)
#define DWM_SCANOUTPOS_ACCUWATE     (1 << 2)
#define USE_WEAW_VBWANKSTAWT		(1 << 30)
#define GET_DISTANCE_TO_VBWANKSTAWT	(1 << 31)

void amdgpu_wink_encodew_connectow(stwuct dwm_device *dev);

stwuct dwm_connectow *
amdgpu_get_connectow_fow_encodew(stwuct dwm_encodew *encodew);
stwuct dwm_connectow *
amdgpu_get_connectow_fow_encodew_init(stwuct dwm_encodew *encodew);
boow amdgpu_dig_monitow_is_duawwink(stwuct dwm_encodew *encodew,
				    u32 pixew_cwock);

u16 amdgpu_encodew_get_dp_bwidge_encodew_id(stwuct dwm_encodew *encodew);
stwuct dwm_encodew *amdgpu_get_extewnaw_encodew(stwuct dwm_encodew *encodew);

boow amdgpu_dispway_ddc_pwobe(stwuct amdgpu_connectow *amdgpu_connectow,
			      boow use_aux);

void amdgpu_encodew_set_active_device(stwuct dwm_encodew *encodew);

int amdgpu_dispway_get_cwtc_scanoutpos(stwuct dwm_device *dev,
			unsigned int pipe, unsigned int fwags, int *vpos,
			int *hpos, ktime_t *stime, ktime_t *etime,
			const stwuct dwm_dispway_mode *mode);

int amdgpufb_wemove(stwuct dwm_device *dev, stwuct dwm_fwamebuffew *fb);

void amdgpu_enc_destwoy(stwuct dwm_encodew *encodew);
void amdgpu_copy_fb(stwuct dwm_device *dev, stwuct dwm_gem_object *dst_obj);
boow amdgpu_dispway_cwtc_scawing_mode_fixup(stwuct dwm_cwtc *cwtc,
				const stwuct dwm_dispway_mode *mode,
				stwuct dwm_dispway_mode *adjusted_mode);
void amdgpu_panew_mode_fixup(stwuct dwm_encodew *encodew,
			     stwuct dwm_dispway_mode *adjusted_mode);
int amdgpu_dispway_cwtc_idx_to_iwq_type(stwuct amdgpu_device *adev, int cwtc);

boow amdgpu_cwtc_get_scanout_position(stwuct dwm_cwtc *cwtc,
			boow in_vbwank_iwq, int *vpos,
			int *hpos, ktime_t *stime, ktime_t *etime,
			const stwuct dwm_dispway_mode *mode);

/* amdgpu_dispway.c */
void amdgpu_dispway_pwint_dispway_setup(stwuct dwm_device *dev);
int amdgpu_dispway_modeset_cweate_pwops(stwuct amdgpu_device *adev);
int amdgpu_dispway_cwtc_set_config(stwuct dwm_mode_set *set,
				   stwuct dwm_modeset_acquiwe_ctx *ctx);
int amdgpu_dispway_cwtc_page_fwip_tawget(stwuct dwm_cwtc *cwtc,
				stwuct dwm_fwamebuffew *fb,
				stwuct dwm_pending_vbwank_event *event,
				uint32_t page_fwip_fwags, uint32_t tawget,
				stwuct dwm_modeset_acquiwe_ctx *ctx);
extewn const stwuct dwm_mode_config_funcs amdgpu_mode_funcs;

#endif
