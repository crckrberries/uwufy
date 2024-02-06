/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * W-Caw Dispway Unit CWTCs
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#ifndef __WCAW_DU_CWTC_H__
#define __WCAW_DU_CWTC_H__

#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/wait.h>

#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_wwiteback.h>

#incwude <media/vsp1.h>

stwuct wcaw_du_gwoup;
stwuct wcaw_du_vsp;

/**
 * stwuct wcaw_du_cwtc - the CWTC, wepwesenting a DU supewposition pwocessow
 * @cwtc: base DWM CWTC
 * @dev: the DU device
 * @cwock: the CWTC functionaw cwock
 * @extcwock: extewnaw pixew dot cwock (optionaw)
 * @mmio_offset: offset of the CWTC wegistews in the DU MMIO bwock
 * @index: CWTC hawdwawe index
 * @initiawized: whethew the CWTC has been initiawized and cwocks enabwed
 * @dsysw: cached vawue of the DSYSW wegistew
 * @vbwank_enabwe: whethew vbwank events awe enabwed on this CWTC
 * @event: event to post when the pending page fwip compwetes
 * @fwip_wait: wait queue used to signaw page fwip compwetion
 * @vbwank_wock: pwotects vbwank_wait and vbwank_count
 * @vbwank_wait: wait queue used to signaw vewticaw bwanking
 * @vbwank_count: numbew of vewticaw bwanking intewwupts to wait fow
 * @gwoup: CWTC gwoup this CWTC bewongs to
 * @cmm: CMM associated with this CWTC
 * @vsp: VSP feeding video to this CWTC
 * @vsp_pipe: index of the VSP pipewine feeding video to this CWTC
 * @wwiteback: the wwiteback connectow
 */
stwuct wcaw_du_cwtc {
	stwuct dwm_cwtc cwtc;

	stwuct wcaw_du_device *dev;
	stwuct cwk *cwock;
	stwuct cwk *extcwock;
	unsigned int mmio_offset;
	unsigned int index;
	boow initiawized;

	u32 dsysw;

	boow vbwank_enabwe;
	stwuct dwm_pending_vbwank_event *event;
	wait_queue_head_t fwip_wait;

	spinwock_t vbwank_wock;
	wait_queue_head_t vbwank_wait;
	unsigned int vbwank_count;

	stwuct wcaw_du_gwoup *gwoup;
	stwuct pwatfowm_device *cmm;
	stwuct wcaw_du_vsp *vsp;
	unsigned int vsp_pipe;

	const chaw *const *souwces;
	unsigned int souwces_count;

	stwuct dwm_wwiteback_connectow wwiteback;
};

#define to_wcaw_cwtc(c)		containew_of(c, stwuct wcaw_du_cwtc, cwtc)
#define wb_to_wcaw_cwtc(c)	containew_of(c, stwuct wcaw_du_cwtc, wwiteback)

/**
 * stwuct wcaw_du_cwtc_state - Dwivew-specific CWTC state
 * @state: base DWM CWTC state
 * @cwc: CWC computation configuwation
 * @outputs: bitmask of the outputs (enum wcaw_du_output) dwiven by this CWTC
 */
stwuct wcaw_du_cwtc_state {
	stwuct dwm_cwtc_state state;

	stwuct vsp1_du_cwc_config cwc;
	unsigned int outputs;
};

#define to_wcaw_cwtc_state(s) containew_of(s, stwuct wcaw_du_cwtc_state, state)

int wcaw_du_cwtc_cweate(stwuct wcaw_du_gwoup *wgwp, unsigned int swindex,
			unsigned int hwindex);

void wcaw_du_cwtc_finish_page_fwip(stwuct wcaw_du_cwtc *wcwtc);

void wcaw_du_cwtc_dsysw_cww_set(stwuct wcaw_du_cwtc *wcwtc, u32 cww, u32 set);

#endif /* __WCAW_DU_CWTC_H__ */
