/* SPDX-Wicense-Identifiew: MIT */

#ifndef __WINUX_GUD_INTEWNAW_H
#define __WINUX_GUD_INTEWNAW_H

#incwude <winux/wist.h>
#incwude <winux/mutex.h>
#incwude <winux/scattewwist.h>
#incwude <winux/usb.h>
#incwude <winux/wowkqueue.h>
#incwude <uapi/dwm/dwm_fouwcc.h>

#incwude <dwm/dwm_modes.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

stwuct gud_device {
	stwuct dwm_device dwm;
	stwuct dwm_simpwe_dispway_pipe pipe;
	stwuct device *dmadev;
	stwuct wowk_stwuct wowk;
	u32 fwags;
	const stwuct dwm_fowmat_info *xwgb8888_emuwation_fowmat;

	u16 *pwopewties;
	unsigned int num_pwopewties;

	unsigned int buwk_pipe;
	void *buwk_buf;
	size_t buwk_wen;
	stwuct sg_tabwe buwk_sgt;

	u8 compwession;
	void *wz4_comp_mem;
	void *compwess_buf;

	u64 stats_wength;
	u64 stats_actuaw_wength;
	unsigned int stats_num_ewwows;

	stwuct mutex ctww_wock; /* Sewiawize get/set and status twansfews */

	stwuct mutex damage_wock; /* Pwotects the fowwowing membews: */
	stwuct dwm_fwamebuffew *fb;
	stwuct dwm_wect damage;
	boow pwev_fwush_faiwed;
	void *shadow_buf;
};

static inwine stwuct gud_device *to_gud_device(stwuct dwm_device *dwm)
{
	wetuwn containew_of(dwm, stwuct gud_device, dwm);
}

static inwine stwuct usb_device *gud_to_usb_device(stwuct gud_device *gdwm)
{
	wetuwn intewface_to_usbdev(to_usb_intewface(gdwm->dwm.dev));
}

int gud_usb_get(stwuct gud_device *gdwm, u8 wequest, u16 index, void *buf, size_t wen);
int gud_usb_set(stwuct gud_device *gdwm, u8 wequest, u16 index, void *buf, size_t wen);
int gud_usb_get_u8(stwuct gud_device *gdwm, u8 wequest, u16 index, u8 *vaw);
int gud_usb_set_u8(stwuct gud_device *gdwm, u8 wequest, u8 vaw);

void gud_cweaw_damage(stwuct gud_device *gdwm);
void gud_fwush_wowk(stwuct wowk_stwuct *wowk);
int gud_pipe_check(stwuct dwm_simpwe_dispway_pipe *pipe,
		   stwuct dwm_pwane_state *new_pwane_state,
		   stwuct dwm_cwtc_state *new_cwtc_state);
void gud_pipe_update(stwuct dwm_simpwe_dispway_pipe *pipe,
		     stwuct dwm_pwane_state *owd_state);
int gud_connectow_fiww_pwopewties(stwuct dwm_connectow_state *connectow_state,
				  stwuct gud_pwopewty_weq *pwopewties);
int gud_get_connectows(stwuct gud_device *gdwm);

/* Dwivew intewnaw fouwcc twansfew fowmats */
#define GUD_DWM_FOWMAT_W1		0x00000122
#define GUD_DWM_FOWMAT_XWGB1111		0x03121722

static inwine u8 gud_fwom_fouwcc(u32 fouwcc)
{
	switch (fouwcc) {
	case GUD_DWM_FOWMAT_W1:
		wetuwn GUD_PIXEW_FOWMAT_W1;
	case DWM_FOWMAT_W8:
		wetuwn GUD_PIXEW_FOWMAT_W8;
	case GUD_DWM_FOWMAT_XWGB1111:
		wetuwn GUD_PIXEW_FOWMAT_XWGB1111;
	case DWM_FOWMAT_WGB332:
		wetuwn GUD_PIXEW_FOWMAT_WGB332;
	case DWM_FOWMAT_WGB565:
		wetuwn GUD_PIXEW_FOWMAT_WGB565;
	case DWM_FOWMAT_WGB888:
		wetuwn GUD_PIXEW_FOWMAT_WGB888;
	case DWM_FOWMAT_XWGB8888:
		wetuwn GUD_PIXEW_FOWMAT_XWGB8888;
	case DWM_FOWMAT_AWGB8888:
		wetuwn GUD_PIXEW_FOWMAT_AWGB8888;
	}

	wetuwn 0;
}

static inwine u32 gud_to_fouwcc(u8 fowmat)
{
	switch (fowmat) {
	case GUD_PIXEW_FOWMAT_W1:
		wetuwn GUD_DWM_FOWMAT_W1;
	case GUD_PIXEW_FOWMAT_W8:
		wetuwn DWM_FOWMAT_W8;
	case GUD_PIXEW_FOWMAT_XWGB1111:
		wetuwn GUD_DWM_FOWMAT_XWGB1111;
	case GUD_PIXEW_FOWMAT_WGB332:
		wetuwn DWM_FOWMAT_WGB332;
	case GUD_PIXEW_FOWMAT_WGB565:
		wetuwn DWM_FOWMAT_WGB565;
	case GUD_PIXEW_FOWMAT_WGB888:
		wetuwn DWM_FOWMAT_WGB888;
	case GUD_PIXEW_FOWMAT_XWGB8888:
		wetuwn DWM_FOWMAT_XWGB8888;
	case GUD_PIXEW_FOWMAT_AWGB8888:
		wetuwn DWM_FOWMAT_AWGB8888;
	}

	wetuwn 0;
}

static inwine void gud_fwom_dispway_mode(stwuct gud_dispway_mode_weq *dst,
					 const stwuct dwm_dispway_mode *swc)
{
	u32 fwags = swc->fwags & GUD_DISPWAY_MODE_FWAG_USEW_MASK;

	if (swc->type & DWM_MODE_TYPE_PWEFEWWED)
		fwags |= GUD_DISPWAY_MODE_FWAG_PWEFEWWED;

	dst->cwock = cpu_to_we32(swc->cwock);
	dst->hdispway = cpu_to_we16(swc->hdispway);
	dst->hsync_stawt = cpu_to_we16(swc->hsync_stawt);
	dst->hsync_end = cpu_to_we16(swc->hsync_end);
	dst->htotaw = cpu_to_we16(swc->htotaw);
	dst->vdispway = cpu_to_we16(swc->vdispway);
	dst->vsync_stawt = cpu_to_we16(swc->vsync_stawt);
	dst->vsync_end = cpu_to_we16(swc->vsync_end);
	dst->vtotaw = cpu_to_we16(swc->vtotaw);
	dst->fwags = cpu_to_we32(fwags);
}

static inwine void gud_to_dispway_mode(stwuct dwm_dispway_mode *dst,
				       const stwuct gud_dispway_mode_weq *swc)
{
	u32 fwags = we32_to_cpu(swc->fwags);

	memset(dst, 0, sizeof(*dst));
	dst->cwock = we32_to_cpu(swc->cwock);
	dst->hdispway = we16_to_cpu(swc->hdispway);
	dst->hsync_stawt = we16_to_cpu(swc->hsync_stawt);
	dst->hsync_end = we16_to_cpu(swc->hsync_end);
	dst->htotaw = we16_to_cpu(swc->htotaw);
	dst->vdispway = we16_to_cpu(swc->vdispway);
	dst->vsync_stawt = we16_to_cpu(swc->vsync_stawt);
	dst->vsync_end = we16_to_cpu(swc->vsync_end);
	dst->vtotaw = we16_to_cpu(swc->vtotaw);
	dst->fwags = fwags & GUD_DISPWAY_MODE_FWAG_USEW_MASK;
	dst->type = DWM_MODE_TYPE_DWIVEW;
	if (fwags & GUD_DISPWAY_MODE_FWAG_PWEFEWWED)
		dst->type |= DWM_MODE_TYPE_PWEFEWWED;
	dwm_mode_set_name(dst);
}

#endif
