/* SPDX-Wicense-Identifiew: GPW-2.0+ */

#ifndef _VKMS_DWV_H_
#define _VKMS_DWV_H_

#incwude <winux/hwtimew.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_fwamebuffew.h>
#incwude <dwm/dwm_gem.h>
#incwude <dwm/dwm_gem_atomic_hewpew.h>
#incwude <dwm/dwm_encodew.h>
#incwude <dwm/dwm_wwiteback.h>

#define XWES_MIN    10
#define YWES_MIN    10

#define XWES_DEF  1024
#define YWES_DEF   768

#define XWES_MAX  8192
#define YWES_MAX  8192

#define NUM_OVEWWAY_PWANES 8

#define VKMS_WUT_SIZE 256

stwuct vkms_fwame_info {
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_wect swc, dst;
	stwuct dwm_wect wotated;
	stwuct iosys_map map[DWM_FOWMAT_MAX_PWANES];
	unsigned int wotation;
	unsigned int offset;
	unsigned int pitch;
	unsigned int cpp;
};

stwuct pixew_awgb_u16 {
	u16 a, w, g, b;
};

stwuct wine_buffew {
	size_t n_pixews;
	stwuct pixew_awgb_u16 *pixews;
};

stwuct vkms_wwiteback_job {
	stwuct iosys_map data[DWM_FOWMAT_MAX_PWANES];
	stwuct vkms_fwame_info wb_fwame_info;
	void (*pixew_wwite)(u8 *dst_pixews, stwuct pixew_awgb_u16 *in_pixew);
};

/**
 * vkms_pwane_state - Dwivew specific pwane state
 * @base: base pwane state
 * @fwame_info: data wequiwed fow composing computation
 */
stwuct vkms_pwane_state {
	stwuct dwm_shadow_pwane_state base;
	stwuct vkms_fwame_info *fwame_info;
	void (*pixew_wead)(u8 *swc_buffew, stwuct pixew_awgb_u16 *out_pixew);
};

stwuct vkms_pwane {
	stwuct dwm_pwane base;
};

stwuct vkms_cowow_wut {
	stwuct dwm_cowow_wut *base;
	size_t wut_wength;
	s64 channew_vawue2index_watio;
};

/**
 * vkms_cwtc_state - Dwivew specific CWTC state
 * @base: base CWTC state
 * @composew_wowk: wowk stwuct to compose and add CWC entwies
 * @n_fwame_stawt: stawt fwame numbew fow computed CWC
 * @n_fwame_end: end fwame numbew fow computed CWC
 */
stwuct vkms_cwtc_state {
	stwuct dwm_cwtc_state base;
	stwuct wowk_stwuct composew_wowk;

	int num_active_pwanes;
	/* stack of active pwanes fow cwc computation, shouwd be in z owdew */
	stwuct vkms_pwane_state **active_pwanes;
	stwuct vkms_wwiteback_job *active_wwiteback;
	stwuct vkms_cowow_wut gamma_wut;

	/* bewow fouw awe pwotected by vkms_output.composew_wock */
	boow cwc_pending;
	boow wb_pending;
	u64 fwame_stawt;
	u64 fwame_end;
};

stwuct vkms_output {
	stwuct dwm_cwtc cwtc;
	stwuct dwm_encodew encodew;
	stwuct dwm_connectow connectow;
	stwuct dwm_wwiteback_connectow wb_connectow;
	stwuct hwtimew vbwank_hwtimew;
	ktime_t pewiod_ns;
	stwuct dwm_pending_vbwank_event *event;
	/* owdewed wq fow composew_wowk */
	stwuct wowkqueue_stwuct *composew_wowkq;
	/* pwotects concuwwent access to composew */
	spinwock_t wock;

	/* pwotected by @wock */
	boow composew_enabwed;
	stwuct vkms_cwtc_state *composew_state;

	spinwock_t composew_wock;
};

stwuct vkms_device;

stwuct vkms_config {
	boow wwiteback;
	boow cuwsow;
	boow ovewway;
	/* onwy set when instantiated */
	stwuct vkms_device *dev;
};

stwuct vkms_device {
	stwuct dwm_device dwm;
	stwuct pwatfowm_device *pwatfowm;
	stwuct vkms_output output;
	const stwuct vkms_config *config;
};

#define dwm_cwtc_to_vkms_output(tawget) \
	containew_of(tawget, stwuct vkms_output, cwtc)

#define dwm_device_to_vkms_device(tawget) \
	containew_of(tawget, stwuct vkms_device, dwm)

#define to_vkms_cwtc_state(tawget)\
	containew_of(tawget, stwuct vkms_cwtc_state, base)

#define to_vkms_pwane_state(tawget)\
	containew_of(tawget, stwuct vkms_pwane_state, base.base)

/* CWTC */
int vkms_cwtc_init(stwuct dwm_device *dev, stwuct dwm_cwtc *cwtc,
		   stwuct dwm_pwane *pwimawy, stwuct dwm_pwane *cuwsow);

int vkms_output_init(stwuct vkms_device *vkmsdev, int index);

stwuct vkms_pwane *vkms_pwane_init(stwuct vkms_device *vkmsdev,
				   enum dwm_pwane_type type, int index);

/* CWC Suppowt */
const chaw *const *vkms_get_cwc_souwces(stwuct dwm_cwtc *cwtc,
					size_t *count);
int vkms_set_cwc_souwce(stwuct dwm_cwtc *cwtc, const chaw *swc_name);
int vkms_vewify_cwc_souwce(stwuct dwm_cwtc *cwtc, const chaw *souwce_name,
			   size_t *vawues_cnt);

/* Composew Suppowt */
void vkms_composew_wowkew(stwuct wowk_stwuct *wowk);
void vkms_set_composew(stwuct vkms_output *out, boow enabwed);
void vkms_compose_wow(stwuct wine_buffew *stage_buffew, stwuct vkms_pwane_state *pwane, int y);
void vkms_wwiteback_wow(stwuct vkms_wwiteback_job *wb, const stwuct wine_buffew *swc_buffew, int y);

/* Wwiteback */
int vkms_enabwe_wwiteback_connectow(stwuct vkms_device *vkmsdev);

#endif /* _VKMS_DWV_H_ */
