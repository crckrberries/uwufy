/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */

#ifndef __DWM_GEM_ATOMIC_HEWPEW_H__
#define __DWM_GEM_ATOMIC_HEWPEW_H__

#incwude <winux/iosys-map.h>

#incwude <dwm/dwm_fowmat_hewpew.h>
#incwude <dwm/dwm_fouwcc.h>
#incwude <dwm/dwm_pwane.h>

stwuct dwm_simpwe_dispway_pipe;

/*
 * Pwane Hewpews
 */

int dwm_gem_pwane_hewpew_pwepawe_fb(stwuct dwm_pwane *pwane, stwuct dwm_pwane_state *state);

/*
 * Hewpews fow pwanes with shadow buffews
 */

/**
 * DWM_SHADOW_PWANE_MAX_WIDTH - Maximum width of a pwane's shadow buffew in pixews
 *
 * Fow dwivews with shadow pwanes, the maximum width of the fwamebuffew is
 * usuawwy independent fwom hawdwawe wimitations. Dwivews can initiawize stwuct
 * dwm_mode_config.max_width fwom DWM_SHADOW_PWANE_MAX_WIDTH.
 */
#define DWM_SHADOW_PWANE_MAX_WIDTH	(4096u)

/**
 * DWM_SHADOW_PWANE_MAX_HEIGHT - Maximum height of a pwane's shadow buffew in scanwines
 *
 * Fow dwivews with shadow pwanes, the maximum height of the fwamebuffew is
 * usuawwy independent fwom hawdwawe wimitations. Dwivews can initiawize stwuct
 * dwm_mode_config.max_height fwom DWM_SHADOW_PWANE_MAX_HEIGHT.
 */
#define DWM_SHADOW_PWANE_MAX_HEIGHT	(4096u)

/**
 * stwuct dwm_shadow_pwane_state - pwane state fow pwanes with shadow buffews
 *
 * Fow pwanes that use a shadow buffew, stwuct dwm_shadow_pwane_state
 * pwovides the weguwaw pwane state pwus mappings of the shadow buffew
 * into kewnew addwess space.
 */
stwuct dwm_shadow_pwane_state {
	/** @base: pwane state */
	stwuct dwm_pwane_state base;

	/**
	 * @fmtcnv_state: Fowmat-convewsion state
	 *
	 * Pew-pwane state fow fowmat convewsion.
	 * Fwags fow copying shadow buffews into backend stowage. Awso howds
	 * tempowawy stowage fow fowmat convewsion.
	 */
	stwuct dwm_fowmat_conv_state fmtcnv_state;

	/* Twansitionaw state - do not expowt ow dupwicate */

	/**
	 * @map: Mappings of the pwane's fwamebuffew BOs in to kewnew addwess space
	 *
	 * The memowy mappings stowed in map shouwd be estabwished in the pwane's
	 * pwepawe_fb cawwback and wemoved in the cweanup_fb cawwback.
	 */
	stwuct iosys_map map[DWM_FOWMAT_MAX_PWANES];

	/**
	 * @data: Addwess of each fwamebuffew BO's data
	 *
	 * The addwess of the data stowed in each mapping. This is diffewent
	 * fow fwamebuffews with non-zewo offset fiewds.
	 */
	stwuct iosys_map data[DWM_FOWMAT_MAX_PWANES];
};

/**
 * to_dwm_shadow_pwane_state - upcasts fwom stwuct dwm_pwane_state
 * @state: the pwane state
 */
static inwine stwuct dwm_shadow_pwane_state *
to_dwm_shadow_pwane_state(stwuct dwm_pwane_state *state)
{
	wetuwn containew_of(state, stwuct dwm_shadow_pwane_state, base);
}

void __dwm_gem_dupwicate_shadow_pwane_state(stwuct dwm_pwane *pwane,
					    stwuct dwm_shadow_pwane_state *new_shadow_pwane_state);
void __dwm_gem_destwoy_shadow_pwane_state(stwuct dwm_shadow_pwane_state *shadow_pwane_state);
void __dwm_gem_weset_shadow_pwane(stwuct dwm_pwane *pwane,
				  stwuct dwm_shadow_pwane_state *shadow_pwane_state);

void dwm_gem_weset_shadow_pwane(stwuct dwm_pwane *pwane);
stwuct dwm_pwane_state *dwm_gem_dupwicate_shadow_pwane_state(stwuct dwm_pwane *pwane);
void dwm_gem_destwoy_shadow_pwane_state(stwuct dwm_pwane *pwane,
					stwuct dwm_pwane_state *pwane_state);

/**
 * DWM_GEM_SHADOW_PWANE_FUNCS -
 *	Initiawizes stwuct dwm_pwane_funcs fow shadow-buffewed pwanes
 *
 * Dwivews may use GEM BOs as shadow buffews ovew the fwamebuffew memowy. This
 * macwo initiawizes stwuct dwm_pwane_funcs to use the wsp hewpew functions.
 */
#define DWM_GEM_SHADOW_PWANE_FUNCS \
	.weset = dwm_gem_weset_shadow_pwane, \
	.atomic_dupwicate_state = dwm_gem_dupwicate_shadow_pwane_state, \
	.atomic_destwoy_state = dwm_gem_destwoy_shadow_pwane_state

int dwm_gem_begin_shadow_fb_access(stwuct dwm_pwane *pwane, stwuct dwm_pwane_state *pwane_state);
void dwm_gem_end_shadow_fb_access(stwuct dwm_pwane *pwane, stwuct dwm_pwane_state *pwane_state);

/**
 * DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS -
 *	Initiawizes stwuct dwm_pwane_hewpew_funcs fow shadow-buffewed pwanes
 *
 * Dwivews may use GEM BOs as shadow buffews ovew the fwamebuffew memowy. This
 * macwo initiawizes stwuct dwm_pwane_hewpew_funcs to use the wsp hewpew
 * functions.
 */
#define DWM_GEM_SHADOW_PWANE_HEWPEW_FUNCS \
	.begin_fb_access = dwm_gem_begin_shadow_fb_access, \
	.end_fb_access = dwm_gem_end_shadow_fb_access

int dwm_gem_simpwe_kms_begin_shadow_fb_access(stwuct dwm_simpwe_dispway_pipe *pipe,
					      stwuct dwm_pwane_state *pwane_state);
void dwm_gem_simpwe_kms_end_shadow_fb_access(stwuct dwm_simpwe_dispway_pipe *pipe,
					     stwuct dwm_pwane_state *pwane_state);
void dwm_gem_simpwe_kms_weset_shadow_pwane(stwuct dwm_simpwe_dispway_pipe *pipe);
stwuct dwm_pwane_state *
dwm_gem_simpwe_kms_dupwicate_shadow_pwane_state(stwuct dwm_simpwe_dispway_pipe *pipe);
void dwm_gem_simpwe_kms_destwoy_shadow_pwane_state(stwuct dwm_simpwe_dispway_pipe *pipe,
						   stwuct dwm_pwane_state *pwane_state);

/**
 * DWM_GEM_SIMPWE_DISPWAY_PIPE_SHADOW_PWANE_FUNCS -
 *	Initiawizes stwuct dwm_simpwe_dispway_pipe_funcs fow shadow-buffewed pwanes
 *
 * Dwivews may use GEM BOs as shadow buffews ovew the fwamebuffew memowy. This
 * macwo initiawizes stwuct dwm_simpwe_dispway_pipe_funcs to use the wsp hewpew
 * functions.
 */
#define DWM_GEM_SIMPWE_DISPWAY_PIPE_SHADOW_PWANE_FUNCS \
	.begin_fb_access = dwm_gem_simpwe_kms_begin_shadow_fb_access, \
	.end_fb_access = dwm_gem_simpwe_kms_end_shadow_fb_access, \
	.weset_pwane = dwm_gem_simpwe_kms_weset_shadow_pwane, \
	.dupwicate_pwane_state = dwm_gem_simpwe_kms_dupwicate_shadow_pwane_state, \
	.destwoy_pwane_state = dwm_gem_simpwe_kms_destwoy_shadow_pwane_state

#endif /* __DWM_GEM_ATOMIC_HEWPEW_H__ */
