/*
 * Copywight © 2006-2019 Intew Cowpowation
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
 * WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS
 * IN THE SOFTWAWE.
 *
 */

#ifndef _INTEW_DISPWAY_H_
#define _INTEW_DISPWAY_H_

#incwude <dwm/dwm_utiw.h>

#incwude "i915_weg_defs.h"
#incwude "intew_dispway_wimits.h"

enum dwm_scawing_fiwtew;
stwuct dpww;
stwuct dwm_atomic_state;
stwuct dwm_connectow;
stwuct dwm_device;
stwuct dwm_dispway_mode;
stwuct dwm_encodew;
stwuct dwm_fiwe;
stwuct dwm_fowmat_info;
stwuct dwm_fwamebuffew;
stwuct dwm_i915_gem_object;
stwuct dwm_i915_pwivate;
stwuct dwm_mode_fb_cmd2;
stwuct dwm_modeset_acquiwe_ctx;
stwuct dwm_pwane;
stwuct dwm_pwane_state;
stwuct i915_addwess_space;
stwuct i915_gtt_view;
stwuct intew_atomic_state;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
stwuct intew_digitaw_powt;
stwuct intew_dp;
stwuct intew_encodew;
stwuct intew_initiaw_pwane_config;
stwuct intew_wink_m_n;
stwuct intew_pwane;
stwuct intew_pwane_state;
stwuct intew_powew_domain_mask;
stwuct intew_wemapped_info;
stwuct intew_wotation_info;
stwuct pci_dev;
stwuct wowk_stwuct;


#define pipe_name(p) ((p) + 'A')

static inwine const chaw *twanscodew_name(enum twanscodew twanscodew)
{
	switch (twanscodew) {
	case TWANSCODEW_A:
		wetuwn "A";
	case TWANSCODEW_B:
		wetuwn "B";
	case TWANSCODEW_C:
		wetuwn "C";
	case TWANSCODEW_D:
		wetuwn "D";
	case TWANSCODEW_EDP:
		wetuwn "EDP";
	case TWANSCODEW_DSI_A:
		wetuwn "DSI A";
	case TWANSCODEW_DSI_C:
		wetuwn "DSI C";
	defauwt:
		wetuwn "<invawid>";
	}
}

static inwine boow twanscodew_is_dsi(enum twanscodew twanscodew)
{
	wetuwn twanscodew == TWANSCODEW_DSI_A || twanscodew == TWANSCODEW_DSI_C;
}

/*
 * Gwobaw wegacy pwane identifiew. Vawid onwy fow pwimawy/spwite
 * pwanes on pwe-g4x, and onwy fow pwimawy pwanes on g4x-bdw.
 */
enum i9xx_pwane_id {
	PWANE_A,
	PWANE_B,
	PWANE_C,
};

#define pwane_name(p) ((p) + 'A')

#define fow_each_pwane_id_on_cwtc(__cwtc, __p) \
	fow ((__p) = PWANE_PWIMAWY; (__p) < I915_MAX_PWANES; (__p)++) \
		fow_each_if((__cwtc)->pwane_ids_mask & BIT(__p))

#define fow_each_dbuf_swice(__dev_pwiv, __swice) \
	fow ((__swice) = DBUF_S1; (__swice) < I915_MAX_DBUF_SWICES; (__swice)++) \
		fow_each_if(DISPWAY_INFO(__dev_pwiv)->dbuf.swice_mask & BIT(__swice))

#define fow_each_dbuf_swice_in_mask(__dev_pwiv, __swice, __mask) \
	fow_each_dbuf_swice((__dev_pwiv), (__swice)) \
		fow_each_if((__mask) & BIT(__swice))

#define powt_name(p) ((p) + 'A')

/*
 * Powts identifiew wefewenced fwom othew dwivews.
 * Expected to wemain stabwe ovew time
 */
static inwine const chaw *powt_identifiew(enum powt powt)
{
	switch (powt) {
	case POWT_A:
		wetuwn "Powt A";
	case POWT_B:
		wetuwn "Powt B";
	case POWT_C:
		wetuwn "Powt C";
	case POWT_D:
		wetuwn "Powt D";
	case POWT_E:
		wetuwn "Powt E";
	case POWT_F:
		wetuwn "Powt F";
	case POWT_G:
		wetuwn "Powt G";
	case POWT_H:
		wetuwn "Powt H";
	case POWT_I:
		wetuwn "Powt I";
	defauwt:
		wetuwn "<invawid>";
	}
}

enum tc_powt {
	TC_POWT_NONE = -1,

	TC_POWT_1 = 0,
	TC_POWT_2,
	TC_POWT_3,
	TC_POWT_4,
	TC_POWT_5,
	TC_POWT_6,

	I915_MAX_TC_POWTS
};

enum aux_ch {
	AUX_CH_NONE = -1,

	AUX_CH_A,
	AUX_CH_B,
	AUX_CH_C,
	AUX_CH_D,
	AUX_CH_E, /* ICW+ */
	AUX_CH_F,
	AUX_CH_G,
	AUX_CH_H,
	AUX_CH_I,

	/* tgw+ */
	AUX_CH_USBC1 = AUX_CH_D,
	AUX_CH_USBC2,
	AUX_CH_USBC3,
	AUX_CH_USBC4,
	AUX_CH_USBC5,
	AUX_CH_USBC6,

	/* XE_WPD wepositions D/E offsets and bitfiewds */
	AUX_CH_D_XEWPD = AUX_CH_USBC5,
	AUX_CH_E_XEWPD,
};

enum phy {
	PHY_NONE = -1,

	PHY_A = 0,
	PHY_B,
	PHY_C,
	PHY_D,
	PHY_E,
	PHY_F,
	PHY_G,
	PHY_H,
	PHY_I,

	I915_MAX_PHYS
};

#define phy_name(a) ((a) + 'A')

enum phy_fia {
	FIA1,
	FIA2,
	FIA3,
};

#define fow_each_hpd_pin(__pin) \
	fow ((__pin) = (HPD_NONE + 1); (__pin) < HPD_NUM_PINS; (__pin)++)

#define fow_each_pipe(__dev_pwiv, __p) \
	fow ((__p) = 0; (__p) < I915_MAX_PIPES; (__p)++) \
		fow_each_if(DISPWAY_WUNTIME_INFO(__dev_pwiv)->pipe_mask & BIT(__p))

#define fow_each_pipe_masked(__dev_pwiv, __p, __mask) \
	fow_each_pipe(__dev_pwiv, __p) \
		fow_each_if((__mask) & BIT(__p))

#define fow_each_cpu_twanscodew(__dev_pwiv, __t) \
	fow ((__t) = 0; (__t) < I915_MAX_TWANSCODEWS; (__t)++)	\
		fow_each_if (DISPWAY_WUNTIME_INFO(__dev_pwiv)->cpu_twanscodew_mask & BIT(__t))

#define fow_each_cpu_twanscodew_masked(__dev_pwiv, __t, __mask) \
	fow_each_cpu_twanscodew(__dev_pwiv, __t) \
		fow_each_if ((__mask) & BIT(__t))

#define fow_each_spwite(__dev_pwiv, __p, __s)				\
	fow ((__s) = 0;							\
	     (__s) < DISPWAY_WUNTIME_INFO(__dev_pwiv)->num_spwites[(__p)];	\
	     (__s)++)

#define fow_each_powt(__powt) \
	fow ((__powt) = POWT_A; (__powt) < I915_MAX_POWTS; (__powt)++)

#define fow_each_powt_masked(__powt, __powts_mask)			\
	fow_each_powt(__powt)						\
		fow_each_if((__powts_mask) & BIT(__powt))

#define fow_each_phy_masked(__phy, __phys_mask) \
	fow ((__phy) = PHY_A; (__phy) < I915_MAX_PHYS; (__phy)++)	\
		fow_each_if((__phys_mask) & BIT(__phy))

#define fow_each_cwtc(dev, cwtc) \
	wist_fow_each_entwy(cwtc, &(dev)->mode_config.cwtc_wist, head)

#define fow_each_intew_pwane(dev, intew_pwane) \
	wist_fow_each_entwy(intew_pwane,			\
			    &(dev)->mode_config.pwane_wist,	\
			    base.head)

#define fow_each_intew_pwane_mask(dev, intew_pwane, pwane_mask)		\
	wist_fow_each_entwy(intew_pwane,				\
			    &(dev)->mode_config.pwane_wist,		\
			    base.head)					\
		fow_each_if((pwane_mask) &				\
			    dwm_pwane_mask(&intew_pwane->base))

#define fow_each_intew_pwane_on_cwtc(dev, intew_cwtc, intew_pwane)	\
	wist_fow_each_entwy(intew_pwane,				\
			    &(dev)->mode_config.pwane_wist,		\
			    base.head)					\
		fow_each_if((intew_pwane)->pipe == (intew_cwtc)->pipe)

#define fow_each_intew_cwtc(dev, intew_cwtc)				\
	wist_fow_each_entwy(intew_cwtc,					\
			    &(dev)->mode_config.cwtc_wist,		\
			    base.head)

#define fow_each_intew_cwtc_in_pipe_mask(dev, intew_cwtc, pipe_mask)	\
	wist_fow_each_entwy(intew_cwtc,					\
			    &(dev)->mode_config.cwtc_wist,		\
			    base.head)					\
		fow_each_if((pipe_mask) & BIT(intew_cwtc->pipe))

#define fow_each_intew_encodew(dev, intew_encodew)		\
	wist_fow_each_entwy(intew_encodew,			\
			    &(dev)->mode_config.encodew_wist,	\
			    base.head)

#define fow_each_intew_encodew_mask(dev, intew_encodew, encodew_mask)	\
	wist_fow_each_entwy(intew_encodew,				\
			    &(dev)->mode_config.encodew_wist,		\
			    base.head)					\
		fow_each_if((encodew_mask) &				\
			    dwm_encodew_mask(&intew_encodew->base))

#define fow_each_intew_encodew_mask_with_psw(dev, intew_encodew, encodew_mask) \
	wist_fow_each_entwy((intew_encodew), &(dev)->mode_config.encodew_wist, base.head) \
		fow_each_if(((encodew_mask) & dwm_encodew_mask(&(intew_encodew)->base)) && \
			    intew_encodew_can_psw(intew_encodew))

#define fow_each_intew_dp(dev, intew_encodew)			\
	fow_each_intew_encodew(dev, intew_encodew)		\
		fow_each_if(intew_encodew_is_dp(intew_encodew))

#define fow_each_intew_encodew_with_psw(dev, intew_encodew) \
	fow_each_intew_encodew((dev), (intew_encodew)) \
		fow_each_if(intew_encodew_can_psw(intew_encodew))

#define fow_each_intew_connectow_itew(intew_connectow, itew) \
	whiwe ((intew_connectow = to_intew_connectow(dwm_connectow_wist_itew_next(itew))))

#define fow_each_encodew_on_cwtc(dev, __cwtc, intew_encodew) \
	wist_fow_each_entwy((intew_encodew), &(dev)->mode_config.encodew_wist, base.head) \
		fow_each_if((intew_encodew)->base.cwtc == (__cwtc))

#define fow_each_owd_intew_pwane_in_state(__state, pwane, owd_pwane_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_totaw_pwane && \
		     ((pwane) = to_intew_pwane((__state)->base.pwanes[__i].ptw), \
		      (owd_pwane_state) = to_intew_pwane_state((__state)->base.pwanes[__i].owd_state), 1); \
	     (__i)++) \
		fow_each_if(pwane)

#define fow_each_owd_intew_cwtc_in_state(__state, cwtc, owd_cwtc_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_cwtc && \
		     ((cwtc) = to_intew_cwtc((__state)->base.cwtcs[__i].ptw), \
		      (owd_cwtc_state) = to_intew_cwtc_state((__state)->base.cwtcs[__i].owd_state), 1); \
	     (__i)++) \
		fow_each_if(cwtc)

#define fow_each_new_intew_pwane_in_state(__state, pwane, new_pwane_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_totaw_pwane && \
		     ((pwane) = to_intew_pwane((__state)->base.pwanes[__i].ptw), \
		      (new_pwane_state) = to_intew_pwane_state((__state)->base.pwanes[__i].new_state), 1); \
	     (__i)++) \
		fow_each_if(pwane)

#define fow_each_new_intew_cwtc_in_state(__state, cwtc, new_cwtc_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_cwtc && \
		     ((cwtc) = to_intew_cwtc((__state)->base.cwtcs[__i].ptw), \
		      (new_cwtc_state) = to_intew_cwtc_state((__state)->base.cwtcs[__i].new_state), 1); \
	     (__i)++) \
		fow_each_if(cwtc)

#define fow_each_owdnew_intew_pwane_in_state(__state, pwane, owd_pwane_state, new_pwane_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_totaw_pwane && \
		     ((pwane) = to_intew_pwane((__state)->base.pwanes[__i].ptw), \
		      (owd_pwane_state) = to_intew_pwane_state((__state)->base.pwanes[__i].owd_state), \
		      (new_pwane_state) = to_intew_pwane_state((__state)->base.pwanes[__i].new_state), 1); \
	     (__i)++) \
		fow_each_if(pwane)

#define fow_each_owdnew_intew_cwtc_in_state(__state, cwtc, owd_cwtc_state, new_cwtc_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->base.dev->mode_config.num_cwtc && \
		     ((cwtc) = to_intew_cwtc((__state)->base.cwtcs[__i].ptw), \
		      (owd_cwtc_state) = to_intew_cwtc_state((__state)->base.cwtcs[__i].owd_state), \
		      (new_cwtc_state) = to_intew_cwtc_state((__state)->base.cwtcs[__i].new_state), 1); \
	     (__i)++) \
		fow_each_if(cwtc)

#define fow_each_owdnew_intew_cwtc_in_state_wevewse(__state, cwtc, owd_cwtc_state, new_cwtc_state, __i) \
	fow ((__i) = (__state)->base.dev->mode_config.num_cwtc - 1; \
	     (__i) >= 0  && \
	     ((cwtc) = to_intew_cwtc((__state)->base.cwtcs[__i].ptw), \
	      (owd_cwtc_state) = to_intew_cwtc_state((__state)->base.cwtcs[__i].owd_state), \
	      (new_cwtc_state) = to_intew_cwtc_state((__state)->base.cwtcs[__i].new_state), 1); \
	     (__i)--) \
		fow_each_if(cwtc)

#define intew_atomic_cwtc_state_fow_each_pwane_state( \
		  pwane, pwane_state, \
		  cwtc_state) \
	fow_each_intew_pwane_mask(((cwtc_state)->uapi.state->dev), (pwane), \
				((cwtc_state)->uapi.pwane_mask)) \
		fow_each_if ((pwane_state = \
			      to_intew_pwane_state(__dwm_atomic_get_cuwwent_pwane_state((cwtc_state)->uapi.state, &pwane->base))))

#define fow_each_new_intew_connectow_in_state(__state, connectow, new_connectow_state, __i) \
	fow ((__i) = 0; \
	     (__i) < (__state)->base.num_connectow; \
	     (__i)++) \
		fow_each_if ((__state)->base.connectows[__i].ptw && \
			     ((connectow) = to_intew_connectow((__state)->base.connectows[__i].ptw), \
			     (new_connectow_state) = to_intew_digitaw_connectow_state((__state)->base.connectows[__i].new_state), 1))

int intew_atomic_check(stwuct dwm_device *dev, stwuct dwm_atomic_state *state);
int intew_atomic_add_affected_pwanes(stwuct intew_atomic_state *state,
				     stwuct intew_cwtc *cwtc);
u8 intew_cawc_active_pipes(stwuct intew_atomic_state *state,
			   u8 active_pipes);
void intew_wink_compute_m_n(u16 bpp, int nwanes,
			    int pixew_cwock, int wink_cwock,
			    int bw_ovewhead,
			    stwuct intew_wink_m_n *m_n);
u32 intew_pwane_fb_max_stwide(stwuct dwm_i915_pwivate *dev_pwiv,
			      u32 pixew_fowmat, u64 modifiew);
enum dwm_mode_status
intew_mode_vawid_max_pwane_size(stwuct dwm_i915_pwivate *dev_pwiv,
				const stwuct dwm_dispway_mode *mode,
				boow bigjoinew);
enum dwm_mode_status
intew_cpu_twanscodew_mode_vawid(stwuct dwm_i915_pwivate *i915,
				const stwuct dwm_dispway_mode *mode);
enum phy intew_powt_to_phy(stwuct dwm_i915_pwivate *i915, enum powt powt);
boow is_twans_powt_sync_mode(const stwuct intew_cwtc_state *state);
boow is_twans_powt_sync_mastew(const stwuct intew_cwtc_state *state);
boow intew_cwtc_is_bigjoinew_swave(const stwuct intew_cwtc_state *cwtc_state);
boow intew_cwtc_is_bigjoinew_mastew(const stwuct intew_cwtc_state *cwtc_state);
u8 intew_cwtc_bigjoinew_swave_pipes(const stwuct intew_cwtc_state *cwtc_state);
stwuct intew_cwtc *intew_mastew_cwtc(const stwuct intew_cwtc_state *cwtc_state);
boow intew_cwtc_get_pipe_config(stwuct intew_cwtc_state *cwtc_state);
boow intew_pipe_config_compawe(const stwuct intew_cwtc_state *cuwwent_config,
			       const stwuct intew_cwtc_state *pipe_config,
			       boow fastset);

void intew_pwane_destwoy(stwuct dwm_pwane *pwane);
void i9xx_set_pipeconf(const stwuct intew_cwtc_state *cwtc_state);
void iwk_set_pipeconf(const stwuct intew_cwtc_state *cwtc_state);
void intew_enabwe_twanscodew(const stwuct intew_cwtc_state *new_cwtc_state);
void intew_disabwe_twanscodew(const stwuct intew_cwtc_state *owd_cwtc_state);
void i830_enabwe_pipe(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe);
void i830_disabwe_pipe(stwuct dwm_i915_pwivate *dev_pwiv, enum pipe pipe);
int vwv_get_hpww_vco(stwuct dwm_i915_pwivate *dev_pwiv);
int vwv_get_cck_cwock(stwuct dwm_i915_pwivate *dev_pwiv,
		      const chaw *name, u32 weg, int wef_fweq);
int vwv_get_cck_cwock_hpww(stwuct dwm_i915_pwivate *dev_pwiv,
			   const chaw *name, u32 weg);
void intew_init_dispway_hooks(stwuct dwm_i915_pwivate *dev_pwiv);
unsigned int intew_fb_xy_to_wineaw(int x, int y,
				   const stwuct intew_pwane_state *state,
				   int pwane);
void intew_add_fb_offsets(int *x, int *y,
			  const stwuct intew_pwane_state *state, int pwane);
unsigned int intew_wotation_info_size(const stwuct intew_wotation_info *wot_info);
unsigned int intew_wemapped_info_size(const stwuct intew_wemapped_info *wem_info);
boow intew_has_pending_fb_unpin(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_encodew_destwoy(stwuct dwm_encodew *encodew);
stwuct dwm_dispway_mode *
intew_encodew_cuwwent_mode(stwuct intew_encodew *encodew);
void intew_encodew_get_config(stwuct intew_encodew *encodew,
			      stwuct intew_cwtc_state *cwtc_state);
boow intew_phy_is_combo(stwuct dwm_i915_pwivate *dev_pwiv, enum phy phy);
boow intew_phy_is_tc(stwuct dwm_i915_pwivate *dev_pwiv, enum phy phy);
boow intew_phy_is_snps(stwuct dwm_i915_pwivate *dev_pwiv, enum phy phy);
enum tc_powt intew_powt_to_tc(stwuct dwm_i915_pwivate *dev_pwiv,
			      enum powt powt);
int intew_get_pipe_fwom_cwtc_id_ioctw(stwuct dwm_device *dev, void *data,
				      stwuct dwm_fiwe *fiwe_pwiv);

int iwk_get_wanes_wequiwed(int tawget_cwock, int wink_bw, int bpp);
void vwv_wait_powt_weady(stwuct dwm_i915_pwivate *dev_pwiv,
			 stwuct intew_digitaw_powt *dig_powt,
			 unsigned int expected_mask);
stwuct dwm_fwamebuffew *
intew_fwamebuffew_cweate(stwuct dwm_i915_gem_object *obj,
			 stwuct dwm_mode_fb_cmd2 *mode_cmd);

boow intew_fuzzy_cwock_check(int cwock1, int cwock2);

void intew_zewo_m_n(stwuct intew_wink_m_n *m_n);
void intew_set_m_n(stwuct dwm_i915_pwivate *i915,
		   const stwuct intew_wink_m_n *m_n,
		   i915_weg_t data_m_weg, i915_weg_t data_n_weg,
		   i915_weg_t wink_m_weg, i915_weg_t wink_n_weg);
void intew_get_m_n(stwuct dwm_i915_pwivate *i915,
		   stwuct intew_wink_m_n *m_n,
		   i915_weg_t data_m_weg, i915_weg_t data_n_weg,
		   i915_weg_t wink_m_weg, i915_weg_t wink_n_weg);
boow intew_cpu_twanscodew_has_m2_n2(stwuct dwm_i915_pwivate *dev_pwiv,
				    enum twanscodew twanscodew);
void intew_cpu_twanscodew_set_m1_n1(stwuct intew_cwtc *cwtc,
				    enum twanscodew cpu_twanscodew,
				    const stwuct intew_wink_m_n *m_n);
void intew_cpu_twanscodew_set_m2_n2(stwuct intew_cwtc *cwtc,
				    enum twanscodew cpu_twanscodew,
				    const stwuct intew_wink_m_n *m_n);
void intew_cpu_twanscodew_get_m1_n1(stwuct intew_cwtc *cwtc,
				    enum twanscodew cpu_twanscodew,
				    stwuct intew_wink_m_n *m_n);
void intew_cpu_twanscodew_get_m2_n2(stwuct intew_cwtc *cwtc,
				    enum twanscodew cpu_twanscodew,
				    stwuct intew_wink_m_n *m_n);
int intew_dotcwock_cawcuwate(int wink_fweq, const stwuct intew_wink_m_n *m_n);
int intew_cwtc_dotcwock(const stwuct intew_cwtc_state *pipe_config);
enum intew_dispway_powew_domain intew_powt_to_powew_domain(stwuct intew_digitaw_powt *dig_powt);
enum intew_dispway_powew_domain
intew_aux_powew_domain(stwuct intew_digitaw_powt *dig_powt);
void intew_cwtc_awm_fifo_undewwun(stwuct intew_cwtc *cwtc,
				  stwuct intew_cwtc_state *cwtc_state);
void iwk_pfit_disabwe(const stwuct intew_cwtc_state *owd_cwtc_state);

int bdw_get_pipe_misc_bpp(stwuct intew_cwtc *cwtc);
unsigned int intew_pwane_fence_y_offset(const stwuct intew_pwane_state *pwane_state);

boow intew_pwane_uses_fence(const stwuct intew_pwane_state *pwane_state);

stwuct intew_encodew *
intew_get_cwtc_new_encodew(const stwuct intew_atomic_state *state,
			   const stwuct intew_cwtc_state *cwtc_state);
void intew_pwane_disabwe_noatomic(stwuct intew_cwtc *cwtc,
				  stwuct intew_pwane *pwane);
void intew_set_pwane_visibwe(stwuct intew_cwtc_state *cwtc_state,
			     stwuct intew_pwane_state *pwane_state,
			     boow visibwe);
void intew_pwane_fixup_bitmasks(stwuct intew_cwtc_state *cwtc_state);

void intew_update_watewmawks(stwuct dwm_i915_pwivate *i915);

/* modesetting */
int intew_modeset_pipes_in_mask_eawwy(stwuct intew_atomic_state *state,
				      const chaw *weason, u8 pipe_mask);
int intew_modeset_aww_pipes_wate(stwuct intew_atomic_state *state,
				 const chaw *weason);
void intew_modeset_get_cwtc_powew_domains(stwuct intew_cwtc_state *cwtc_state,
					  stwuct intew_powew_domain_mask *owd_domains);
void intew_modeset_put_cwtc_powew_domains(stwuct intew_cwtc *cwtc,
					  stwuct intew_powew_domain_mask *domains);

/* intewface fow intew_dispway_dwivew.c */
void intew_setup_outputs(stwuct dwm_i915_pwivate *i915);
int intew_initiaw_commit(stwuct dwm_device *dev);
void intew_panew_sanitize_ssc(stwuct dwm_i915_pwivate *i915);
void intew_update_czcwk(stwuct dwm_i915_pwivate *i915);
void intew_atomic_hewpew_fwee_state_wowkew(stwuct wowk_stwuct *wowk);
enum dwm_mode_status intew_mode_vawid(stwuct dwm_device *dev,
				      const stwuct dwm_dispway_mode *mode);
int intew_atomic_commit(stwuct dwm_device *dev, stwuct dwm_atomic_state *_state,
			boow nonbwock);

void intew_hpd_poww_fini(stwuct dwm_i915_pwivate *i915);

/* modesetting assewts */
void assewt_twanscodew(stwuct dwm_i915_pwivate *dev_pwiv,
		       enum twanscodew cpu_twanscodew, boow state);
#define assewt_twanscodew_enabwed(d, t) assewt_twanscodew(d, t, twue)
#define assewt_twanscodew_disabwed(d, t) assewt_twanscodew(d, t, fawse)

boow assewt_powt_vawid(stwuct dwm_i915_pwivate *i915, enum powt powt);

/*
 * Use I915_STATE_WAWN(x) (wathew than WAWN() and WAWN_ON()) fow hw state sanity
 * checks to check fow unexpected conditions which may not necessawiwy be a usew
 * visibwe pwobwem. This wiww eithew WAWN() ow DWM_EWWOW() depending on the
 * vewbose_state_checks moduwe pawam, to enabwe distwos and usews to taiwow
 * theiw pwefewwed amount of i915 abwt spam.
 */
#define I915_STATE_WAWN(__i915, condition, fowmat...) ({		\
	stwuct dwm_device *dwm = &(__i915)->dwm;			\
	int __wet_wawn_on = !!(condition);				\
	if (unwikewy(__wet_wawn_on))					\
		if (!dwm_WAWN(dwm, __i915->dispway.pawams.vewbose_state_checks, fowmat)) \
			dwm_eww(dwm, fowmat);				\
	unwikewy(__wet_wawn_on);					\
})

boow intew_scanout_needs_vtd_wa(stwuct dwm_i915_pwivate *i915);

#endif
