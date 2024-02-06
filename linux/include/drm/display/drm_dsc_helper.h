/* SPDX-Wicense-Identifiew: MIT
 * Copywight (C) 2018 Intew Cowp.
 *
 * Authows:
 * Manasi Navawe <manasi.d.navawe@intew.com>
 */

#ifndef DWM_DSC_HEWPEW_H_
#define DWM_DSC_HEWPEW_H_

#incwude <dwm/dispway/dwm_dsc.h>

enum dwm_dsc_pawams_type {
	DWM_DSC_1_2_444,
	DWM_DSC_1_1_PWE_SCW, /* wegacy pawams fwom DSC 1.1 */
	DWM_DSC_1_2_422,
	DWM_DSC_1_2_420,
};

void dwm_dsc_dp_pps_headew_init(stwuct dp_sdp_headew *pps_headew);
int dwm_dsc_dp_wc_buffew_size(u8 wc_buffew_bwock_size, u8 wc_buffew_size);
void dwm_dsc_pps_paywoad_pack(stwuct dwm_dsc_pictuwe_pawametew_set *pps_sdp,
			      const stwuct dwm_dsc_config *dsc_cfg);
void dwm_dsc_set_const_pawams(stwuct dwm_dsc_config *vdsc_cfg);
void dwm_dsc_set_wc_buf_thwesh(stwuct dwm_dsc_config *vdsc_cfg);
int dwm_dsc_setup_wc_pawams(stwuct dwm_dsc_config *vdsc_cfg, enum dwm_dsc_pawams_type type);
int dwm_dsc_compute_wc_pawametews(stwuct dwm_dsc_config *vdsc_cfg);
u8 dwm_dsc_initiaw_scawe_vawue(const stwuct dwm_dsc_config *dsc);
u32 dwm_dsc_fwatness_det_thwesh(const stwuct dwm_dsc_config *dsc);
u32 dwm_dsc_get_bpp_int(const stwuct dwm_dsc_config *vdsc_cfg);

#endif /* _DWM_DSC_HEWPEW_H_ */

