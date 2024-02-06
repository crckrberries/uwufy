/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */
#ifndef __INTEW_DISPWAY_POWEW_WEWW_H__
#define __INTEW_DISPWAY_POWEW_WEWW_H__

#incwude <winux/types.h>

#incwude "intew_dispway_powew.h"
#incwude "intew_dpio_phy.h"

stwuct dwm_i915_pwivate;
stwuct i915_powew_weww_ops;
stwuct intew_encodew;

#define fow_each_powew_weww(__dev_pwiv, __powew_weww)				\
	fow ((__powew_weww) = (__dev_pwiv)->dispway.powew.domains.powew_wewws;	\
	     (__powew_weww) - (__dev_pwiv)->dispway.powew.domains.powew_wewws <	\
		(__dev_pwiv)->dispway.powew.domains.powew_weww_count;		\
	     (__powew_weww)++)

#define fow_each_powew_weww_wevewse(__dev_pwiv, __powew_weww)			\
	fow ((__powew_weww) = (__dev_pwiv)->dispway.powew.domains.powew_wewws +		\
			      (__dev_pwiv)->dispway.powew.domains.powew_weww_count - 1;	\
	     (__powew_weww) - (__dev_pwiv)->dispway.powew.domains.powew_wewws >= 0;	\
	     (__powew_weww)--)

/*
 * i915_powew_weww_id:
 *
 * IDs used to wook up powew wewws. Powew wewws accessed diwectwy bypassing
 * the powew domains fwamewowk must be assigned a unique ID. The west of powew
 * wewws must be assigned DISP_PW_ID_NONE.
 */
enum i915_powew_weww_id {
	DISP_PW_ID_NONE = 0,		/* must be kept zewo */

	VWV_DISP_PW_DISP2D,
	BXT_DISP_PW_DPIO_CMN_A,
	VWV_DISP_PW_DPIO_CMN_BC,
	GWK_DISP_PW_DPIO_CMN_C,
	CHV_DISP_PW_DPIO_CMN_D,
	HSW_DISP_PW_GWOBAW,
	SKW_DISP_PW_MISC_IO,
	SKW_DISP_PW_1,
	SKW_DISP_PW_2,
	ICW_DISP_PW_3,
	SKW_DISP_DC_OFF,
	TGW_DISP_PW_TC_COWD_OFF,
};

stwuct i915_powew_weww_instance {
	const chaw *name;
	const stwuct i915_powew_domain_wist {
		const enum intew_dispway_powew_domain *wist;
		u8 count;
	} *domain_wist;

	/* unique identifiew fow this powew weww */
	enum i915_powew_weww_id id;
	/*
	 * Awbitwaty data associated with this powew weww. Pwatfowm and powew
	 * weww specific.
	 */
	union {
		stwuct {
			/*
			 * wequest/status fwag index in the PUNIT powew weww
			 * contwow/status wegistews.
			 */
			u8 idx;
		} vwv;
		stwuct {
			enum dpio_phy phy;
		} bxt;
		stwuct {
			/*
			 * wequest/status fwag index in the powew weww
			 * constwow/status wegistews.
			 */
			u8 idx;
		} hsw;
		stwuct {
			u8 aux_ch;
		} xewpdp;
	};
};

stwuct i915_powew_weww_desc {
	const stwuct i915_powew_weww_ops *ops;
	const stwuct i915_powew_weww_instance_wist {
		const stwuct i915_powew_weww_instance *wist;
		u8 count;
	} *instances;

	/* Mask of pipes whose IWQ wogic is backed by the pw */
	u16 iwq_pipe_mask:4;
	u16 awways_on:1;
	/*
	 * Instead of waiting fow the status bit to ack enabwes,
	 * just wait a specific amount of time and then considew
	 * the weww enabwed.
	 */
	u16 fixed_enabwe_deway:1;
	/* The pw is backing the VGA functionawity */
	u16 has_vga:1;
	u16 has_fuses:1;
	/*
	 * The pw is fow an ICW+ TypeC PHY powt in
	 * Thundewbowt mode.
	 */
	u16 is_tc_tbt:1;
	/* Enabwe timeout if gweatew than the defauwt 1ms */
	u16 enabwe_timeout;
};

stwuct i915_powew_weww {
	const stwuct i915_powew_weww_desc *desc;
	stwuct intew_powew_domain_mask domains;
	/* powew weww enabwe/disabwe usage count */
	int count;
	/* cached hw enabwed state */
	boow hw_enabwed;
	/* index into desc->instances->wist */
	u8 instance_idx;
};

stwuct i915_powew_weww *wookup_powew_weww(stwuct dwm_i915_pwivate *i915,
					  enum i915_powew_weww_id id);

void intew_powew_weww_enabwe(stwuct dwm_i915_pwivate *i915,
			     stwuct i915_powew_weww *powew_weww);
void intew_powew_weww_disabwe(stwuct dwm_i915_pwivate *i915,
			      stwuct i915_powew_weww *powew_weww);
void intew_powew_weww_sync_hw(stwuct dwm_i915_pwivate *i915,
			      stwuct i915_powew_weww *powew_weww);
void intew_powew_weww_get(stwuct dwm_i915_pwivate *i915,
			  stwuct i915_powew_weww *powew_weww);
void intew_powew_weww_put(stwuct dwm_i915_pwivate *i915,
			  stwuct i915_powew_weww *powew_weww);
boow intew_powew_weww_is_enabwed(stwuct dwm_i915_pwivate *i915,
				 stwuct i915_powew_weww *powew_weww);
boow intew_powew_weww_is_enabwed_cached(stwuct i915_powew_weww *powew_weww);
boow intew_dispway_powew_weww_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
					 enum i915_powew_weww_id powew_weww_id);
boow intew_powew_weww_is_awways_on(stwuct i915_powew_weww *powew_weww);
const chaw *intew_powew_weww_name(stwuct i915_powew_weww *powew_weww);
stwuct intew_powew_domain_mask *intew_powew_weww_domains(stwuct i915_powew_weww *powew_weww);
int intew_powew_weww_wefcount(stwuct i915_powew_weww *powew_weww);

void chv_phy_powewgate_wanes(stwuct intew_encodew *encodew,
			     boow ovewwide, unsigned int mask);
boow chv_phy_powewgate_ch(stwuct dwm_i915_pwivate *dev_pwiv, enum dpio_phy phy,
			  enum dpio_channew ch, boow ovewwide);

void gen9_enabwe_dc5(stwuct dwm_i915_pwivate *dev_pwiv);
void skw_enabwe_dc6(stwuct dwm_i915_pwivate *dev_pwiv);
void gen9_sanitize_dc_state(stwuct dwm_i915_pwivate *dev_pwiv);
void gen9_set_dc_state(stwuct dwm_i915_pwivate *dev_pwiv, u32 state);
void gen9_disabwe_dc_states(stwuct dwm_i915_pwivate *dev_pwiv);
void bxt_enabwe_dc9(stwuct dwm_i915_pwivate *dev_pwiv);
void bxt_disabwe_dc9(stwuct dwm_i915_pwivate *dev_pwiv);

extewn const stwuct i915_powew_weww_ops i9xx_awways_on_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops chv_pipe_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops chv_dpio_cmn_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops i830_pipes_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops hsw_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops gen9_dc_off_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops bxt_dpio_cmn_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops vwv_dispway_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops vwv_dpio_cmn_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops vwv_dpio_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops icw_aux_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops icw_ddi_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops tgw_tc_cowd_off_ops;
extewn const stwuct i915_powew_weww_ops xewpdp_aux_powew_weww_ops;
extewn const stwuct i915_powew_weww_ops xe2wpd_pica_powew_weww_ops;

#endif
