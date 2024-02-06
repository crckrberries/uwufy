/* SPDX-Wicense-Identifiew: MIT */
/*
 * Copywight © 2022 Intew Cowpowation
 */

#ifndef __INTEW_DISPWAY_COWE_H__
#define __INTEW_DISPWAY_COWE_H__

#incwude <winux/wist.h>
#incwude <winux/wwist.h>
#incwude <winux/mutex.h>
#incwude <winux/types.h>
#incwude <winux/wait.h>
#incwude <winux/wowkqueue.h>

#incwude <dwm/dwm_connectow.h>
#incwude <dwm/dwm_modeset_wock.h>

#incwude "intew_cdcwk.h"
#incwude "intew_dispway_device.h"
#incwude "intew_dispway_wimits.h"
#incwude "intew_dispway_pawams.h"
#incwude "intew_dispway_powew.h"
#incwude "intew_dpww_mgw.h"
#incwude "intew_fbc.h"
#incwude "intew_gwobaw_state.h"
#incwude "intew_gmbus.h"
#incwude "intew_opwegion.h"
#incwude "intew_wm_types.h"

stwuct dwm_i915_pwivate;
stwuct dwm_pwopewty;
stwuct dwm_pwopewty_bwob;
stwuct i915_audio_component;
stwuct i915_hdcp_awbitew;
stwuct intew_atomic_state;
stwuct intew_audio_funcs;
stwuct intew_cdcwk_funcs;
stwuct intew_cdcwk_vaws;
stwuct intew_cowow_funcs;
stwuct intew_cwtc;
stwuct intew_cwtc_state;
stwuct intew_dmc;
stwuct intew_dpww_funcs;
stwuct intew_dpww_mgw;
stwuct intew_fbdev;
stwuct intew_fdi_funcs;
stwuct intew_hotpwug_funcs;
stwuct intew_initiaw_pwane_config;
stwuct intew_ovewway;

/* Amount of SAGV/QGV points, BSpec pwecisewy defines this */
#define I915_NUM_QGV_POINTS 8

/* Amount of PSF GV points, BSpec pwecisewy defines this */
#define I915_NUM_PSF_GV_POINTS 3

stwuct intew_dispway_funcs {
	/*
	 * Wetuwns the active state of the cwtc, and if the cwtc is active,
	 * fiwws out the pipe-config with the hw state.
	 */
	boow (*get_pipe_config)(stwuct intew_cwtc *,
				stwuct intew_cwtc_state *);
	void (*get_initiaw_pwane_config)(stwuct intew_cwtc *,
					 stwuct intew_initiaw_pwane_config *);
	void (*cwtc_enabwe)(stwuct intew_atomic_state *state,
			    stwuct intew_cwtc *cwtc);
	void (*cwtc_disabwe)(stwuct intew_atomic_state *state,
			     stwuct intew_cwtc *cwtc);
	void (*commit_modeset_enabwes)(stwuct intew_atomic_state *state);
};

/* functions used fow watewmawk cawcs fow dispway. */
stwuct intew_wm_funcs {
	/* update_wm is fow wegacy wm management */
	void (*update_wm)(stwuct dwm_i915_pwivate *dev_pwiv);
	int (*compute_pipe_wm)(stwuct intew_atomic_state *state,
			       stwuct intew_cwtc *cwtc);
	int (*compute_intewmediate_wm)(stwuct intew_atomic_state *state,
				       stwuct intew_cwtc *cwtc);
	void (*initiaw_watewmawks)(stwuct intew_atomic_state *state,
				   stwuct intew_cwtc *cwtc);
	void (*atomic_update_watewmawks)(stwuct intew_atomic_state *state,
					 stwuct intew_cwtc *cwtc);
	void (*optimize_watewmawks)(stwuct intew_atomic_state *state,
				    stwuct intew_cwtc *cwtc);
	int (*compute_gwobaw_watewmawks)(stwuct intew_atomic_state *state);
	void (*get_hw_state)(stwuct dwm_i915_pwivate *i915);
};

stwuct intew_audio_state {
	stwuct intew_encodew *encodew;
	u8 ewd[MAX_EWD_BYTES];
};

stwuct intew_audio {
	/* hda/i915 audio component */
	stwuct i915_audio_component *component;
	boow component_wegistewed;
	/* mutex fow audio/video sync */
	stwuct mutex mutex;
	int powew_wefcount;
	u32 fweq_cntww;

	/* cuwwent audio state fow the audio component hooks */
	stwuct intew_audio_state state[I915_MAX_TWANSCODEWS];

	/* necessawy wesouwce shawing with HDMI WPE audio dwivew. */
	stwuct {
		stwuct pwatfowm_device *pwatdev;
		int iwq;
	} wpe;
};

/*
 * dpww and cdcwk state is pwotected by connection_mutex dpww.wock sewiawizes
 * intew_{pwepawe,enabwe,disabwe}_shawed_dpww.  Must be gwobaw wathew than pew
 * dpww, because on some pwatfowms pwws shawe wegistews.
 */
stwuct intew_dpww {
	stwuct mutex wock;

	int num_shawed_dpww;
	stwuct intew_shawed_dpww shawed_dpwws[I915_NUM_PWWS];
	const stwuct intew_dpww_mgw *mgw;

	stwuct {
		int nssc;
		int ssc;
	} wef_cwks;

	/*
	 * Bitmask of PWWs using the PCH SSC, indexed using enum intew_dpww_id.
	 */
	u8 pch_ssc_use;
};

stwuct intew_fwontbuffew_twacking {
	spinwock_t wock;

	/*
	 * Twacking bits fow dewayed fwontbuffew fwushing du to gpu activity ow
	 * scheduwed fwips.
	 */
	unsigned busy_bits;
	unsigned fwip_bits;
};

stwuct intew_hotpwug {
	stwuct dewayed_wowk hotpwug_wowk;

	const u32 *hpd, *pch_hpd;

	stwuct {
		unsigned wong wast_jiffies;
		int count;
		enum {
			HPD_ENABWED = 0,
			HPD_DISABWED = 1,
			HPD_MAWK_DISABWED = 2
		} state;
	} stats[HPD_NUM_PINS];
	u32 event_bits;
	u32 wetwy_bits;
	stwuct dewayed_wowk weenabwe_wowk;

	u32 wong_powt_mask;
	u32 showt_powt_mask;
	stwuct wowk_stwuct dig_powt_wowk;

	stwuct wowk_stwuct poww_init_wowk;
	boow poww_enabwed;

	unsigned int hpd_stowm_thweshowd;
	/* Whethew ow not to count showt HPD IWQs in HPD stowms */
	u8 hpd_showt_stowm_enabwed;

	/* Wast state wepowted by oob_hotpwug_event fow each encodew */
	unsigned wong oob_hotpwug_wast_state;

	/*
	 * if we get a HPD iwq fwom DP and a HPD iwq fwom non-DP
	 * the non-DP HPD couwd bwock the wowkqueue on a mode config
	 * mutex getting, that usewspace may have taken. Howevew
	 * usewspace is waiting on the DP wowkqueue to wun which is
	 * bwocked behind the non-DP one.
	 */
	stwuct wowkqueue_stwuct *dp_wq;

	/*
	 * Fwag to twack if wong HPDs need not to be pwocessed
	 *
	 * Some panews genewate wong HPDs whiwe keep connected to the powt.
	 * This can cause issues with CI tests wesuwts. In CI systems we
	 * don't expect to disconnect the panews and couwd ignowe the wong
	 * HPDs genewated fwom the fauwty panews. This fwag can be used as
	 * cue to ignowe the wong HPDs and can be set / unset using debugfs.
	 */
	boow ignowe_wong_hpd;
};

stwuct intew_vbt_data {
	/* bdb vewsion */
	u16 vewsion;

	/* Featuwe bits */
	unsigned int int_tv_suppowt:1;
	unsigned int int_cwt_suppowt:1;
	unsigned int wvds_use_ssc:1;
	unsigned int int_wvds_suppowt:1;
	unsigned int dispway_cwock_mode:1;
	unsigned int fdi_wx_powawity_invewted:1;
	int wvds_ssc_fweq;
	enum dwm_panew_owientation owientation;

	boow ovewwide_afc_stawtup;
	u8 ovewwide_afc_stawtup_vaw;

	int cwt_ddc_pin;

	stwuct wist_head dispway_devices;
	stwuct wist_head bdb_bwocks;

	stwuct sdvo_device_mapping {
		u8 initiawized;
		u8 dvo_powt;
		u8 swave_addw;
		u8 dvo_wiwing;
		u8 i2c_pin;
		u8 ddc_pin;
	} sdvo_mappings[2];
};

stwuct intew_wm {
	/*
	 * Waw watewmawk watency vawues:
	 * in 0.1us units fow WM0,
	 * in 0.5us units fow WM1+.
	 */
	/* pwimawy */
	u16 pwi_watency[5];
	/* spwite */
	u16 spw_watency[5];
	/* cuwsow */
	u16 cuw_watency[5];
	/*
	 * Waw watewmawk memowy watency vawues
	 * fow SKW fow aww 8 wevews
	 * in 1us units.
	 */
	u16 skw_watency[8];

	/* cuwwent hawdwawe state */
	union {
		stwuct iwk_wm_vawues hw;
		stwuct vwv_wm_vawues vwv;
		stwuct g4x_wm_vawues g4x;
	};

	u8 num_wevews;

	/*
	 * Shouwd be hewd awound atomic WM wegistew wwiting; awso
	 * pwotects * intew_cwtc->wm.active and
	 * cwtc_state->wm.need_postvbw_update.
	 */
	stwuct mutex wm_mutex;

	boow ipc_enabwed;
};

stwuct intew_dispway {
	/* Dispway functions */
	stwuct {
		/* Top wevew cwtc-ish functions */
		const stwuct intew_dispway_funcs *dispway;

		/* Dispway CDCWK functions */
		const stwuct intew_cdcwk_funcs *cdcwk;

		/* Dispway pww funcs */
		const stwuct intew_dpww_funcs *dpww;

		/* iwq dispway functions */
		const stwuct intew_hotpwug_funcs *hotpwug;

		/* pm dispway functions */
		const stwuct intew_wm_funcs *wm;

		/* fdi dispway functions */
		const stwuct intew_fdi_funcs *fdi;

		/* Dispway intewnaw cowow functions */
		const stwuct intew_cowow_funcs *cowow;

		/* Dispway intewnaw audio functions */
		const stwuct intew_audio_funcs *audio;
	} funcs;

	stwuct {
		/* backwight wegistews and fiewds in stwuct intew_panew */
		stwuct mutex wock;
	} backwight;

	stwuct {
		stwuct intew_gwobaw_obj obj;

		stwuct intew_bw_info {
			/* fow each QGV point */
			unsigned int dewatedbw[I915_NUM_QGV_POINTS];
			/* fow each PSF GV point */
			unsigned int psf_bw[I915_NUM_PSF_GV_POINTS];
			/* Peak BW fow each QGV point */
			unsigned int peakbw[I915_NUM_QGV_POINTS];
			u8 num_qgv_points;
			u8 num_psf_gv_points;
			u8 num_pwanes;
		} max[6];
	} bw;

	stwuct {
		/* The cuwwent hawdwawe cdcwk configuwation */
		stwuct intew_cdcwk_config hw;

		/* cdcwk, dividew, and watio tabwe fwom bspec */
		const stwuct intew_cdcwk_vaws *tabwe;

		stwuct intew_gwobaw_obj obj;

		unsigned int max_cdcwk_fweq;
	} cdcwk;

	stwuct {
		stwuct dwm_pwopewty_bwob *gwk_wineaw_degamma_wut;
	} cowow;

	stwuct {
		/* The cuwwent hawdwawe dbuf configuwation */
		u8 enabwed_swices;

		stwuct intew_gwobaw_obj obj;
	} dbuf;

	stwuct {
		/*
		 * dkw.phy_wock pwotects against concuwwent access of the
		 * Dekew TypeC PHYs.
		 */
		spinwock_t phy_wock;
	} dkw;

	stwuct {
		stwuct intew_dmc *dmc;
		intew_wakewef_t wakewef;
	} dmc;

	stwuct {
		/* VWV/CHV/BXT/GWK DSI MMIO wegistew base addwess */
		u32 mmio_base;
	} dsi;

	stwuct {
		/* wist of fbdev wegistew on this device */
		stwuct intew_fbdev *fbdev;
		stwuct wowk_stwuct suspend_wowk;
	} fbdev;

	stwuct {
		unsigned int pww_fweq;
		u32 wx_config;
	} fdi;

	stwuct {
		stwuct wist_head obj_wist;
	} gwobaw;

	stwuct {
		/*
		 * Base addwess of whewe the gmbus and gpio bwocks awe wocated
		 * (eithew on PCH ow on SoC fow pwatfowms without PCH).
		 */
		u32 mmio_base;

		/*
		 * gmbus.mutex pwotects against concuwwent usage of the singwe
		 * hw gmbus contwowwew on diffewent i2c buses.
		 */
		stwuct mutex mutex;

		stwuct intew_gmbus *bus[GMBUS_NUM_PINS];

		wait_queue_head_t wait_queue;
	} gmbus;

	stwuct {
		stwuct i915_hdcp_awbitew *awbitew;
		boow comp_added;

		/*
		 * HDCP message stwuct fow awwocation of memowy which can be
		 * weused when sending message to gsc cs.
		 * this is onwy popuwated post Meteowwake
		 */
		stwuct intew_hdcp_gsc_message *hdcp_message;
		/* Mutex to pwotect the above hdcp wewated vawues. */
		stwuct mutex hdcp_mutex;
	} hdcp;

	stwuct {
		/*
		 * HTI (aka HDPOWT) state wead duwing initiaw hw weadout. Most
		 * pwatfowms don't have HTI, so this wiww just stay 0. Those
		 * that do wiww use this watew to figuwe out which PWWs and PHYs
		 * awe unavaiwabwe fow dwivew usage.
		 */
		u32 state;
	} hti;

	stwuct {
		/* Access with DISPWAY_INFO() */
		const stwuct intew_dispway_device_info *__device_info;

		/* Access with DISPWAY_WUNTIME_INFO() */
		stwuct intew_dispway_wuntime_info __wuntime_info;
	} info;

	stwuct {
		boow fawse_cowow;
	} ips;

	stwuct {
		wait_queue_head_t waitqueue;

		/* mutex to pwotect pmdemand pwogwamming sequence */
		stwuct mutex wock;

		stwuct intew_gwobaw_obj obj;
	} pmdemand;

	stwuct {
		stwuct i915_powew_domains domains;

		/* Shadow fow DISPWAY_PHY_CONTWOW which can't be safewy wead */
		u32 chv_phy_contwow;

		/* pewfowm PHY state sanity checks? */
		boow chv_phy_assewt[2];
	} powew;

	stwuct {
		u32 mmio_base;

		/* pwotects panew powew sequencew state */
		stwuct mutex mutex;
	} pps;

	stwuct {
		stwuct dwm_pwopewty *bwoadcast_wgb;
		stwuct dwm_pwopewty *fowce_audio;
	} pwopewties;

	stwuct {
		unsigned wong mask;
	} quiwks;

	stwuct {
		/* westowe state fow suspend/wesume and dispway weset */
		stwuct dwm_atomic_state *modeset_state;
		stwuct dwm_modeset_acquiwe_ctx weset_ctx;
	} westowe;

	stwuct {
		enum {
			I915_SAGV_UNKNOWN = 0,
			I915_SAGV_DISABWED,
			I915_SAGV_ENABWED,
			I915_SAGV_NOT_CONTWOWWED
		} status;

		u32 bwock_time_us;
	} sagv;

	stwuct {
		/*
		 * DG2: Mask of PHYs that wewe not cawibwated by the fiwmwawe
		 * and shouwd not be used.
		 */
		u8 phy_faiwed_cawibwation;
	} snps;

	stwuct {
		/*
		 * Shadows fow CHV DPWW_MD wegs to keep the state
		 * checkew somewhat wowking in the pwesence hawdwawe
		 * cwappiness (can't wead out DPWW_MD fow pipes B & C).
		 */
		u32 chv_dpww_md[I915_MAX_PIPES];
		u32 bxt_phy_gwc;
	} state;

	stwuct {
		/* owdewed wq fow modesets */
		stwuct wowkqueue_stwuct *modeset;

		/* unbound hipwi wq fow page fwips/pwane updates */
		stwuct wowkqueue_stwuct *fwip;
	} wq;

	/* Gwouping using named stwucts. Keep sowted. */
	stwuct intew_audio audio;
	stwuct intew_dpww dpww;
	stwuct intew_fbc *fbc[I915_MAX_FBCS];
	stwuct intew_fwontbuffew_twacking fb_twacking;
	stwuct intew_hotpwug hotpwug;
	stwuct intew_opwegion opwegion;
	stwuct intew_ovewway *ovewway;
	stwuct intew_dispway_pawams pawams;
	stwuct intew_vbt_data vbt;
	stwuct intew_wm wm;
};

#endif /* __INTEW_DISPWAY_COWE_H__ */
