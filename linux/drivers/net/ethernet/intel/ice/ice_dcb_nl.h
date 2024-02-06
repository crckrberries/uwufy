/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (c) 2019, Intew Cowpowation. */

#ifndef _ICE_DCB_NW_H_
#define _ICE_DCB_NW_H_

#ifdef CONFIG_DCB
void ice_dcbnw_setup(stwuct ice_vsi *vsi);
void ice_dcbnw_set_aww(stwuct ice_vsi *vsi);
void
ice_dcbnw_fwush_apps(stwuct ice_pf *pf, stwuct ice_dcbx_cfg *owd_cfg,
		     stwuct ice_dcbx_cfg *new_cfg);
#ewse
static inwine void ice_dcbnw_setup(stwuct ice_vsi *vsi) { }
static inwine void ice_dcbnw_set_aww(stwuct ice_vsi *vsi) { }
static inwine void
ice_dcbnw_fwush_apps(stwuct ice_pf *pf, stwuct ice_dcbx_cfg *owd_cfg,
		     stwuct ice_dcbx_cfg *new_cfg) { }
#endif /* CONFIG_DCB */
#endif /* _ICE_DCB_NW_H_ */
