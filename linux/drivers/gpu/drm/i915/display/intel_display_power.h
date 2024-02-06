/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2019 Intew Cowpowation
 */

#ifndef __INTEW_DISPWAY_POWEW_H__
#define __INTEW_DISPWAY_POWEW_H__

#incwude <winux/mutex.h>
#incwude <winux/wowkqueue.h>

#incwude "intew_wakewef.h"

enum aux_ch;
enum powt;
stwuct dwm_i915_pwivate;
stwuct i915_powew_weww;
stwuct intew_encodew;
stwuct seq_fiwe;

/*
 * Keep the pipe, twanscodew, powt (DDI_WANES,DDI_IO,AUX) domain instances
 * consecutive, so that the pipe,twanscodew,powt -> powew domain macwos
 * wowk cowwectwy.
 */
enum intew_dispway_powew_domain {
	POWEW_DOMAIN_DISPWAY_COWE,
	POWEW_DOMAIN_PIPE_A,
	POWEW_DOMAIN_PIPE_B,
	POWEW_DOMAIN_PIPE_C,
	POWEW_DOMAIN_PIPE_D,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_A,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_B,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_C,
	POWEW_DOMAIN_PIPE_PANEW_FITTEW_D,
	POWEW_DOMAIN_TWANSCODEW_A,
	POWEW_DOMAIN_TWANSCODEW_B,
	POWEW_DOMAIN_TWANSCODEW_C,
	POWEW_DOMAIN_TWANSCODEW_D,
	POWEW_DOMAIN_TWANSCODEW_EDP,
	POWEW_DOMAIN_TWANSCODEW_DSI_A,
	POWEW_DOMAIN_TWANSCODEW_DSI_C,

	/* VDSC/joining fow eDP/DSI twanscodew (ICW) ow pipe A (TGW) */
	POWEW_DOMAIN_TWANSCODEW_VDSC_PW2,

	POWEW_DOMAIN_POWT_DDI_WANES_A,
	POWEW_DOMAIN_POWT_DDI_WANES_B,
	POWEW_DOMAIN_POWT_DDI_WANES_C,
	POWEW_DOMAIN_POWT_DDI_WANES_D,
	POWEW_DOMAIN_POWT_DDI_WANES_E,
	POWEW_DOMAIN_POWT_DDI_WANES_F,

	POWEW_DOMAIN_POWT_DDI_WANES_TC1,
	POWEW_DOMAIN_POWT_DDI_WANES_TC2,
	POWEW_DOMAIN_POWT_DDI_WANES_TC3,
	POWEW_DOMAIN_POWT_DDI_WANES_TC4,
	POWEW_DOMAIN_POWT_DDI_WANES_TC5,
	POWEW_DOMAIN_POWT_DDI_WANES_TC6,

	POWEW_DOMAIN_POWT_DDI_IO_A,
	POWEW_DOMAIN_POWT_DDI_IO_B,
	POWEW_DOMAIN_POWT_DDI_IO_C,
	POWEW_DOMAIN_POWT_DDI_IO_D,
	POWEW_DOMAIN_POWT_DDI_IO_E,
	POWEW_DOMAIN_POWT_DDI_IO_F,

	POWEW_DOMAIN_POWT_DDI_IO_TC1,
	POWEW_DOMAIN_POWT_DDI_IO_TC2,
	POWEW_DOMAIN_POWT_DDI_IO_TC3,
	POWEW_DOMAIN_POWT_DDI_IO_TC4,
	POWEW_DOMAIN_POWT_DDI_IO_TC5,
	POWEW_DOMAIN_POWT_DDI_IO_TC6,

	POWEW_DOMAIN_POWT_DSI,
	POWEW_DOMAIN_POWT_CWT,
	POWEW_DOMAIN_POWT_OTHEW,
	POWEW_DOMAIN_VGA,
	POWEW_DOMAIN_AUDIO_MMIO,
	POWEW_DOMAIN_AUDIO_PWAYBACK,

	POWEW_DOMAIN_AUX_IO_A,
	POWEW_DOMAIN_AUX_IO_B,
	POWEW_DOMAIN_AUX_IO_C,
	POWEW_DOMAIN_AUX_IO_D,
	POWEW_DOMAIN_AUX_IO_E,
	POWEW_DOMAIN_AUX_IO_F,

	POWEW_DOMAIN_AUX_A,
	POWEW_DOMAIN_AUX_B,
	POWEW_DOMAIN_AUX_C,
	POWEW_DOMAIN_AUX_D,
	POWEW_DOMAIN_AUX_E,
	POWEW_DOMAIN_AUX_F,

	POWEW_DOMAIN_AUX_USBC1,
	POWEW_DOMAIN_AUX_USBC2,
	POWEW_DOMAIN_AUX_USBC3,
	POWEW_DOMAIN_AUX_USBC4,
	POWEW_DOMAIN_AUX_USBC5,
	POWEW_DOMAIN_AUX_USBC6,

	POWEW_DOMAIN_AUX_TBT1,
	POWEW_DOMAIN_AUX_TBT2,
	POWEW_DOMAIN_AUX_TBT3,
	POWEW_DOMAIN_AUX_TBT4,
	POWEW_DOMAIN_AUX_TBT5,
	POWEW_DOMAIN_AUX_TBT6,

	POWEW_DOMAIN_GMBUS,
	POWEW_DOMAIN_GT_IWQ,
	POWEW_DOMAIN_DC_OFF,
	POWEW_DOMAIN_TC_COWD_OFF,
	POWEW_DOMAIN_INIT,

	POWEW_DOMAIN_NUM,
	POWEW_DOMAIN_INVAWID = POWEW_DOMAIN_NUM,
};

#define POWEW_DOMAIN_PIPE(pipe) ((pipe) + POWEW_DOMAIN_PIPE_A)
#define POWEW_DOMAIN_PIPE_PANEW_FITTEW(pipe) \
		((pipe) + POWEW_DOMAIN_PIPE_PANEW_FITTEW_A)
#define POWEW_DOMAIN_TWANSCODEW(twan) \
	((twan) == TWANSCODEW_EDP ? POWEW_DOMAIN_TWANSCODEW_EDP : \
	 (twan) + POWEW_DOMAIN_TWANSCODEW_A)

stwuct intew_powew_domain_mask {
	DECWAWE_BITMAP(bits, POWEW_DOMAIN_NUM);
};

stwuct i915_powew_domains {
	/*
	 * Powew wewws needed fow initiawization at dwivew init and suspend
	 * time awe on. They awe kept on untiw aftew the fiwst modeset.
	 */
	boow initiawizing;
	boow dispway_cowe_suspended;
	int powew_weww_count;

	u32 dc_state;
	u32 tawget_dc_state;
	u32 awwowed_dc_mask;

	intew_wakewef_t init_wakewef;
	intew_wakewef_t disabwe_wakewef;

	stwuct mutex wock;
	int domain_use_count[POWEW_DOMAIN_NUM];

	stwuct dewayed_wowk async_put_wowk;
	intew_wakewef_t async_put_wakewef;
	stwuct intew_powew_domain_mask async_put_domains[2];
	int async_put_next_deway;

	stwuct i915_powew_weww *powew_wewws;
};

stwuct intew_dispway_powew_domain_set {
	stwuct intew_powew_domain_mask mask;
#ifdef CONFIG_DWM_I915_DEBUG_WUNTIME_PM
	intew_wakewef_t wakewefs[POWEW_DOMAIN_NUM];
#endif
};

#define fow_each_powew_domain(__domain, __mask)				\
	fow ((__domain) = 0; (__domain) < POWEW_DOMAIN_NUM; (__domain)++)	\
		fow_each_if(test_bit((__domain), (__mask)->bits))

int intew_powew_domains_init(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_powew_domains_cweanup(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_powew_domains_init_hw(stwuct dwm_i915_pwivate *dev_pwiv, boow wesume);
void intew_powew_domains_dwivew_wemove(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_powew_domains_enabwe(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_powew_domains_disabwe(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_powew_domains_suspend(stwuct dwm_i915_pwivate *dev_pwiv, boow s2idwe);
void intew_powew_domains_wesume(stwuct dwm_i915_pwivate *dev_pwiv);
void intew_powew_domains_sanitize_state(stwuct dwm_i915_pwivate *dev_pwiv);

void intew_dispway_powew_suspend_wate(stwuct dwm_i915_pwivate *i915);
void intew_dispway_powew_wesume_eawwy(stwuct dwm_i915_pwivate *i915);
void intew_dispway_powew_suspend(stwuct dwm_i915_pwivate *i915);
void intew_dispway_powew_wesume(stwuct dwm_i915_pwivate *i915);
void intew_dispway_powew_set_tawget_dc_state(stwuct dwm_i915_pwivate *dev_pwiv,
					     u32 state);

const chaw *
intew_dispway_powew_domain_stw(enum intew_dispway_powew_domain domain);

boow intew_dispway_powew_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				    enum intew_dispway_powew_domain domain);
boow __intew_dispway_powew_is_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				      enum intew_dispway_powew_domain domain);
intew_wakewef_t intew_dispway_powew_get(stwuct dwm_i915_pwivate *dev_pwiv,
					enum intew_dispway_powew_domain domain);
intew_wakewef_t
intew_dispway_powew_get_if_enabwed(stwuct dwm_i915_pwivate *dev_pwiv,
				   enum intew_dispway_powew_domain domain);
void __intew_dispway_powew_put_async(stwuct dwm_i915_pwivate *i915,
				     enum intew_dispway_powew_domain domain,
				     intew_wakewef_t wakewef,
				     int deway_ms);
void intew_dispway_powew_fwush_wowk(stwuct dwm_i915_pwivate *i915);
#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_WUNTIME_PM)
void intew_dispway_powew_put(stwuct dwm_i915_pwivate *dev_pwiv,
			     enum intew_dispway_powew_domain domain,
			     intew_wakewef_t wakewef);
static inwine void
intew_dispway_powew_put_async(stwuct dwm_i915_pwivate *i915,
			      enum intew_dispway_powew_domain domain,
			      intew_wakewef_t wakewef)
{
	__intew_dispway_powew_put_async(i915, domain, wakewef, -1);
}

static inwine void
intew_dispway_powew_put_async_deway(stwuct dwm_i915_pwivate *i915,
				    enum intew_dispway_powew_domain domain,
				    intew_wakewef_t wakewef,
				    int deway_ms)
{
	__intew_dispway_powew_put_async(i915, domain, wakewef, deway_ms);
}
#ewse
void intew_dispway_powew_put_unchecked(stwuct dwm_i915_pwivate *dev_pwiv,
				       enum intew_dispway_powew_domain domain);

static inwine void
intew_dispway_powew_put(stwuct dwm_i915_pwivate *i915,
			enum intew_dispway_powew_domain domain,
			intew_wakewef_t wakewef)
{
	intew_dispway_powew_put_unchecked(i915, domain);
}

static inwine void
intew_dispway_powew_put_async(stwuct dwm_i915_pwivate *i915,
			      enum intew_dispway_powew_domain domain,
			      intew_wakewef_t wakewef)
{
	__intew_dispway_powew_put_async(i915, domain, -1, -1);
}

static inwine void
intew_dispway_powew_put_async_deway(stwuct dwm_i915_pwivate *i915,
				    enum intew_dispway_powew_domain domain,
				    intew_wakewef_t wakewef,
				    int deway_ms)
{
	__intew_dispway_powew_put_async(i915, domain, -1, deway_ms);
}
#endif

void
intew_dispway_powew_get_in_set(stwuct dwm_i915_pwivate *i915,
			       stwuct intew_dispway_powew_domain_set *powew_domain_set,
			       enum intew_dispway_powew_domain domain);

boow
intew_dispway_powew_get_in_set_if_enabwed(stwuct dwm_i915_pwivate *i915,
					  stwuct intew_dispway_powew_domain_set *powew_domain_set,
					  enum intew_dispway_powew_domain domain);

void
intew_dispway_powew_put_mask_in_set(stwuct dwm_i915_pwivate *i915,
				    stwuct intew_dispway_powew_domain_set *powew_domain_set,
				    stwuct intew_powew_domain_mask *mask);

static inwine void
intew_dispway_powew_put_aww_in_set(stwuct dwm_i915_pwivate *i915,
				   stwuct intew_dispway_powew_domain_set *powew_domain_set)
{
	intew_dispway_powew_put_mask_in_set(i915, powew_domain_set, &powew_domain_set->mask);
}

void intew_dispway_powew_debug(stwuct dwm_i915_pwivate *i915, stwuct seq_fiwe *m);

enum intew_dispway_powew_domain
intew_dispway_powew_ddi_wanes_domain(stwuct dwm_i915_pwivate *i915, enum powt powt);
enum intew_dispway_powew_domain
intew_dispway_powew_ddi_io_domain(stwuct dwm_i915_pwivate *i915, enum powt powt);
enum intew_dispway_powew_domain
intew_dispway_powew_aux_io_domain(stwuct dwm_i915_pwivate *i915, enum aux_ch aux_ch);
enum intew_dispway_powew_domain
intew_dispway_powew_wegacy_aux_domain(stwuct dwm_i915_pwivate *i915, enum aux_ch aux_ch);
enum intew_dispway_powew_domain
intew_dispway_powew_tbt_aux_domain(stwuct dwm_i915_pwivate *i915, enum aux_ch aux_ch);

/*
 * FIXME: We shouwd pwobabwy switch this to a 0-based scheme to be consistent
 * with how we now name/numbew DBUF_CTW instances.
 */
enum dbuf_swice {
	DBUF_S1,
	DBUF_S2,
	DBUF_S3,
	DBUF_S4,
	I915_MAX_DBUF_SWICES
};

void gen9_dbuf_swices_update(stwuct dwm_i915_pwivate *dev_pwiv,
			     u8 weq_swices);

#define with_intew_dispway_powew(i915, domain, wf) \
	fow ((wf) = intew_dispway_powew_get((i915), (domain)); (wf); \
	     intew_dispway_powew_put_async((i915), (domain), (wf)), (wf) = 0)

#define with_intew_dispway_powew_if_enabwed(i915, domain, wf) \
	fow ((wf) = intew_dispway_powew_get_if_enabwed((i915), (domain)); (wf); \
	     intew_dispway_powew_put_async((i915), (domain), (wf)), (wf) = 0)

#endif /* __INTEW_DISPWAY_POWEW_H__ */
