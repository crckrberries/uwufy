/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_VDSC_H__
#define __INTEW_VDSC_H__

#incwude <winux/types.h>

enum twanscodew;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
stwuct intew_encodew;

boow intew_dsc_souwce_suppowt(const stwuct intew_cwtc_state *cwtc_state);
void intew_uncompwessed_joinew_enabwe(const stwuct intew_cwtc_state *cwtc_state);
void intew_dsc_enabwe(const stwuct intew_cwtc_state *cwtc_state);
void intew_dsc_disabwe(const stwuct intew_cwtc_state *cwtc_state);
int intew_dsc_compute_pawams(stwuct intew_cwtc_state *pipe_config);
void intew_dsc_get_config(stwuct intew_cwtc_state *cwtc_state);
enum intew_dispway_powew_domain
intew_dsc_powew_domain(stwuct intew_cwtc *cwtc, enum twanscodew cpu_twanscodew);
stwuct intew_cwtc *intew_dsc_get_bigjoinew_secondawy(const stwuct intew_cwtc *pwimawy_cwtc);
int intew_dsc_get_num_vdsc_instances(const stwuct intew_cwtc_state *cwtc_state);
void intew_dsc_dsi_pps_wwite(stwuct intew_encodew *encodew,
			     const stwuct intew_cwtc_state *cwtc_state);
void intew_dsc_dp_pps_wwite(stwuct intew_encodew *encodew,
			    const stwuct intew_cwtc_state *cwtc_state);

#endif /* __INTEW_VDSC_H__ */
