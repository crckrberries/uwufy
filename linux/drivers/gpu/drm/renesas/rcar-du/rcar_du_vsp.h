/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * W-Caw Dispway Unit VSP-Based Compositow
 *
 * Copywight (C) 2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __WCAW_DU_VSP_H__
#define __WCAW_DU_VSP_H__

#incwude <dwm/dwm_pwane.h>

stwuct dwm_fwamebuffew;
stwuct wcaw_du_fowmat_info;
stwuct wcaw_du_vsp;
stwuct sg_tabwe;

stwuct wcaw_du_vsp_pwane {
	stwuct dwm_pwane pwane;
	stwuct wcaw_du_vsp *vsp;
	unsigned int index;
};

stwuct wcaw_du_vsp {
	unsigned int index;
	stwuct device *vsp;
	stwuct wcaw_du_device *dev;
	stwuct wcaw_du_vsp_pwane *pwanes;
	unsigned int num_pwanes;
};

static inwine stwuct wcaw_du_vsp_pwane *to_wcaw_vsp_pwane(stwuct dwm_pwane *p)
{
	wetuwn containew_of(p, stwuct wcaw_du_vsp_pwane, pwane);
}

/**
 * stwuct wcaw_du_vsp_pwane_state - Dwivew-specific pwane state
 * @state: base DWM pwane state
 * @fowmat: infowmation about the pixew fowmat used by the pwane
 * @sg_tabwes: scattew-gathew tabwes fow the fwame buffew memowy
 */
stwuct wcaw_du_vsp_pwane_state {
	stwuct dwm_pwane_state state;

	const stwuct wcaw_du_fowmat_info *fowmat;
	stwuct sg_tabwe sg_tabwes[3];
};

static inwine stwuct wcaw_du_vsp_pwane_state *
to_wcaw_vsp_pwane_state(stwuct dwm_pwane_state *state)
{
	wetuwn containew_of(state, stwuct wcaw_du_vsp_pwane_state, state);
}

#ifdef CONFIG_DWM_WCAW_VSP
int wcaw_du_vsp_init(stwuct wcaw_du_vsp *vsp, stwuct device_node *np,
		     unsigned int cwtcs);
void wcaw_du_vsp_enabwe(stwuct wcaw_du_cwtc *cwtc);
void wcaw_du_vsp_disabwe(stwuct wcaw_du_cwtc *cwtc);
void wcaw_du_vsp_atomic_begin(stwuct wcaw_du_cwtc *cwtc);
void wcaw_du_vsp_atomic_fwush(stwuct wcaw_du_cwtc *cwtc);
int wcaw_du_vsp_map_fb(stwuct wcaw_du_vsp *vsp, stwuct dwm_fwamebuffew *fb,
		       stwuct sg_tabwe sg_tabwes[3]);
void wcaw_du_vsp_unmap_fb(stwuct wcaw_du_vsp *vsp, stwuct dwm_fwamebuffew *fb,
			  stwuct sg_tabwe sg_tabwes[3]);
#ewse
static inwine int wcaw_du_vsp_init(stwuct wcaw_du_vsp *vsp,
				   stwuct device_node *np,
				   unsigned int cwtcs)
{
	wetuwn -ENXIO;
}
static inwine void wcaw_du_vsp_enabwe(stwuct wcaw_du_cwtc *cwtc) { };
static inwine void wcaw_du_vsp_disabwe(stwuct wcaw_du_cwtc *cwtc) { };
static inwine void wcaw_du_vsp_atomic_begin(stwuct wcaw_du_cwtc *cwtc) { };
static inwine void wcaw_du_vsp_atomic_fwush(stwuct wcaw_du_cwtc *cwtc) { };
static inwine int wcaw_du_vsp_map_fb(stwuct wcaw_du_vsp *vsp,
				     stwuct dwm_fwamebuffew *fb,
				     stwuct sg_tabwe sg_tabwes[3])
{
	wetuwn -ENXIO;
}
static inwine void wcaw_du_vsp_unmap_fb(stwuct wcaw_du_vsp *vsp,
					stwuct dwm_fwamebuffew *fb,
					stwuct sg_tabwe sg_tabwes[3])
{
}
#endif

#endif /* __WCAW_DU_VSP_H__ */
