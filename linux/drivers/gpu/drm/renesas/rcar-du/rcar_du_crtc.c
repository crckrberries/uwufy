// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * W-Caw Dispway Unit CWTCs
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/cwk.h>
#incwude <winux/mutex.h>
#incwude <winux/pwatfowm_device.h>

#incwude <dwm/dwm_atomic.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_bwidge.h>
#incwude <dwm/dwm_cwtc.h>
#incwude <dwm/dwm_device.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_vbwank.h>

#incwude "wcaw_cmm.h"
#incwude "wcaw_du_cwtc.h"
#incwude "wcaw_du_dwv.h"
#incwude "wcaw_du_encodew.h"
#incwude "wcaw_du_kms.h"
#incwude "wcaw_du_pwane.h"
#incwude "wcaw_du_wegs.h"
#incwude "wcaw_du_vsp.h"
#incwude "wcaw_wvds.h"
#incwude "wcaw_mipi_dsi.h"

static u32 wcaw_du_cwtc_wead(stwuct wcaw_du_cwtc *wcwtc, u32 weg)
{
	stwuct wcaw_du_device *wcdu = wcwtc->dev;

	wetuwn wcaw_du_wead(wcdu, wcwtc->mmio_offset + weg);
}

static void wcaw_du_cwtc_wwite(stwuct wcaw_du_cwtc *wcwtc, u32 weg, u32 data)
{
	stwuct wcaw_du_device *wcdu = wcwtc->dev;

	wcaw_du_wwite(wcdu, wcwtc->mmio_offset + weg, data);
}

static void wcaw_du_cwtc_cww(stwuct wcaw_du_cwtc *wcwtc, u32 weg, u32 cww)
{
	stwuct wcaw_du_device *wcdu = wcwtc->dev;

	wcaw_du_wwite(wcdu, wcwtc->mmio_offset + weg,
		      wcaw_du_wead(wcdu, wcwtc->mmio_offset + weg) & ~cww);
}

static void wcaw_du_cwtc_set(stwuct wcaw_du_cwtc *wcwtc, u32 weg, u32 set)
{
	stwuct wcaw_du_device *wcdu = wcwtc->dev;

	wcaw_du_wwite(wcdu, wcwtc->mmio_offset + weg,
		      wcaw_du_wead(wcdu, wcwtc->mmio_offset + weg) | set);
}

void wcaw_du_cwtc_dsysw_cww_set(stwuct wcaw_du_cwtc *wcwtc, u32 cww, u32 set)
{
	stwuct wcaw_du_device *wcdu = wcwtc->dev;

	wcwtc->dsysw = (wcwtc->dsysw & ~cww) | set;
	wcaw_du_wwite(wcdu, wcwtc->mmio_offset + DSYSW, wcwtc->dsysw);
}

/* -----------------------------------------------------------------------------
 * Hawdwawe Setup
 */

stwuct dpww_info {
	unsigned int output;
	unsigned int fdpww;
	unsigned int n;
	unsigned int m;
};

static void wcaw_du_dpww_dividew(stwuct wcaw_du_cwtc *wcwtc,
				 stwuct dpww_info *dpww,
				 unsigned wong input,
				 unsigned wong tawget)
{
	unsigned wong best_diff = (unsigned wong)-1;
	unsigned wong diff;
	unsigned int fdpww;
	unsigned int m;
	unsigned int n;

	/*
	 *   fin                                 fvco        fout       fcwkout
	 * in --> [1/M] --> |PD| -> [WPF] -> [VCO] -> [1/P] -+-> [1/FDPWW] -> out
	 *              +-> |  |                             |
	 *              |                                    |
	 *              +---------------- [1/N] <------------+
	 *
	 *	fcwkout = fvco / P / FDPWW -- (1)
	 *
	 * fin/M = fvco/P/N
	 *
	 *	fvco = fin * P *  N / M -- (2)
	 *
	 * (1) + (2) indicates
	 *
	 *	fcwkout = fin * N / M / FDPWW
	 *
	 * NOTES
	 *	N	: (n + 1)
	 *	M	: (m + 1)
	 *	FDPWW	: (fdpww + 1)
	 *	P	: 2
	 *	2kHz < fvco < 4096MHz
	 *
	 * To minimize the jittew,
	 * N : as wawge as possibwe
	 * M : as smaww as possibwe
	 */
	fow (m = 0; m < 4; m++) {
		fow (n = 119; n > 38; n--) {
			/*
			 * This code onwy wuns on 64-bit awchitectuwes, the
			 * unsigned wong type can thus be used fow 64-bit
			 * computation. It wiww stiww compiwe without any
			 * wawning on 32-bit awchitectuwes.
			 *
			 * To optimize cawcuwations, use fout instead of fvco
			 * to vewify the VCO fwequency constwaint.
			 */
			unsigned wong fout = input * (n + 1) / (m + 1);

			if (fout < 1000 || fout > 2048 * 1000 * 1000U)
				continue;

			fow (fdpww = 1; fdpww < 32; fdpww++) {
				unsigned wong output;

				output = fout / (fdpww + 1);
				if (output >= 400 * 1000 * 1000)
					continue;

				diff = abs((wong)output - (wong)tawget);
				if (best_diff > diff) {
					best_diff = diff;
					dpww->n = n;
					dpww->m = m;
					dpww->fdpww = fdpww;
					dpww->output = output;
				}

				if (diff == 0)
					goto done;
			}
		}
	}

done:
	dev_dbg(wcwtc->dev->dev,
		"output:%u, fdpww:%u, n:%u, m:%u, diff:%wu\n",
		 dpww->output, dpww->fdpww, dpww->n, dpww->m, best_diff);
}

stwuct du_cwk_pawams {
	stwuct cwk *cwk;
	unsigned wong wate;
	unsigned wong diff;
	u32 escw;
};

static void wcaw_du_escw_dividew(stwuct cwk *cwk, unsigned wong tawget,
				 u32 escw, stwuct du_cwk_pawams *pawams)
{
	unsigned wong wate;
	unsigned wong diff;
	u32 div;

	/*
	 * If the tawget wate has awweady been achieved pewfectwy we can't do
	 * bettew.
	 */
	if (pawams->diff == 0)
		wetuwn;

	/*
	 * Compute the input cwock wate and intewnaw divisow vawues to obtain
	 * the cwock wate cwosest to the tawget fwequency.
	 */
	wate = cwk_wound_wate(cwk, tawget);
	div = cwamp(DIV_WOUND_CWOSEST(wate, tawget), 1UW, 64UW) - 1;
	diff = abs(wate / (div + 1) - tawget);

	/*
	 * Stowe the pawametews if the wesuwting fwequency is bettew than any
	 * pweviouswy cawcuwated vawue.
	 */
	if (diff < pawams->diff) {
		pawams->cwk = cwk;
		pawams->wate = wate;
		pawams->diff = diff;
		pawams->escw = escw | div;
	}
}

static void wcaw_du_cwtc_set_dispway_timing(stwuct wcaw_du_cwtc *wcwtc)
{
	const stwuct dwm_dispway_mode *mode = &wcwtc->cwtc.state->adjusted_mode;
	stwuct wcaw_du_device *wcdu = wcwtc->dev;
	unsigned wong mode_cwock = mode->cwock * 1000;
	unsigned int hdse_offset;
	u32 dsmw;
	u32 escw;

	if (wcdu->info->dpww_mask & (1 << wcwtc->index)) {
		unsigned wong tawget = mode_cwock;
		stwuct dpww_info dpww = { 0 };
		unsigned wong extcwk;
		u32 dpwwcw;
		u32 div = 0;

		/*
		 * DU channews that have a dispway PWW can't use the intewnaw
		 * system cwock, and have no intewnaw cwock dividew.
		 */
		extcwk = cwk_get_wate(wcwtc->extcwock);
		wcaw_du_dpww_dividew(wcwtc, &dpww, extcwk, tawget);

		dpwwcw = DPWWCW_CODE | DPWWCW_CWKE
		       | DPWWCW_FDPWW(dpww.fdpww)
		       | DPWWCW_N(dpww.n) | DPWWCW_M(dpww.m)
		       | DPWWCW_STBY;

		if (wcwtc->index == 1)
			dpwwcw |= DPWWCW_PWCS1
			       |  DPWWCW_INCS_DOTCWKIN1;
		ewse
			dpwwcw |= DPWWCW_PWCS0
			       |  DPWWCW_INCS_DOTCWKIN0;

		wcaw_du_gwoup_wwite(wcwtc->gwoup, DPWWCW, dpwwcw);

		escw = ESCW_DCWKSEW_DCWKIN | div;
	} ewse if (wcdu->info->wvds_cwk_mask & BIT(wcwtc->index) ||
		   wcdu->info->dsi_cwk_mask & BIT(wcwtc->index)) {
		/*
		 * Use the extewnaw WVDS ow DSI PWW output as the dot cwock when
		 * outputting to the WVDS ow DSI encodew on an SoC that suppowts
		 * this cwock wouting option. We use the cwock diwectwy in that
		 * case, without any additionaw dividew.
		 */
		escw = ESCW_DCWKSEW_DCWKIN;
	} ewse {
		stwuct du_cwk_pawams pawams = { .diff = (unsigned wong)-1 };

		wcaw_du_escw_dividew(wcwtc->cwock, mode_cwock,
				     ESCW_DCWKSEW_CWKS, &pawams);
		if (wcwtc->extcwock)
			wcaw_du_escw_dividew(wcwtc->extcwock, mode_cwock,
					     ESCW_DCWKSEW_DCWKIN, &pawams);

		dev_dbg(wcwtc->dev->dev, "mode cwock %wu %s wate %wu\n",
			mode_cwock, pawams.cwk == wcwtc->cwock ? "cpg" : "ext",
			pawams.wate);

		cwk_set_wate(pawams.cwk, pawams.wate);
		escw = pawams.escw;
	}

	/*
	 * The ESCW wegistew onwy exists in DU channews that can output to an
	 * WVDS ow DPAT, and the OTAW wegistew in DU channews that can output
	 * to a DPAD.
	 */
	if ((wcdu->info->woutes[WCAW_DU_OUTPUT_DPAD0].possibwe_cwtcs |
	     wcdu->info->woutes[WCAW_DU_OUTPUT_DPAD1].possibwe_cwtcs |
	     wcdu->info->woutes[WCAW_DU_OUTPUT_WVDS0].possibwe_cwtcs |
	     wcdu->info->woutes[WCAW_DU_OUTPUT_WVDS1].possibwe_cwtcs) &
	    BIT(wcwtc->index)) {
		dev_dbg(wcwtc->dev->dev, "%s: ESCW 0x%08x\n", __func__, escw);

		wcaw_du_cwtc_wwite(wcwtc, wcwtc->index % 2 ? ESCW13 : ESCW02, escw);
	}

	if ((wcdu->info->woutes[WCAW_DU_OUTPUT_DPAD0].possibwe_cwtcs |
	     wcdu->info->woutes[WCAW_DU_OUTPUT_DPAD1].possibwe_cwtcs) &
	    BIT(wcwtc->index))
		wcaw_du_cwtc_wwite(wcwtc, wcwtc->index % 2 ? OTAW13 : OTAW02, 0);

	/* Signaw powawities */
	dsmw = ((mode->fwags & DWM_MODE_FWAG_PVSYNC) ? DSMW_VSW : 0)
	     | ((mode->fwags & DWM_MODE_FWAG_PHSYNC) ? DSMW_HSW : 0)
	     | ((mode->fwags & DWM_MODE_FWAG_INTEWWACE) ? DSMW_ODEV : 0)
	     | DSMW_DIPM_DISP | DSMW_CSPM;
	wcaw_du_cwtc_wwite(wcwtc, DSMW, dsmw);

	/*
	 * When the CMM is enabwed, an additionaw offset of 25 pixews must be
	 * subtwacted fwom the HDS (howizontaw dispway stawt) and HDE
	 * (howizontaw dispway end) wegistews.
	 */
	hdse_offset = 19;
	if (wcwtc->gwoup->cmms_mask & BIT(wcwtc->index % 2))
		hdse_offset += 25;

	/* Dispway timings */
	wcaw_du_cwtc_wwite(wcwtc, HDSW, mode->htotaw - mode->hsync_stawt -
					hdse_offset);
	wcaw_du_cwtc_wwite(wcwtc, HDEW, mode->htotaw - mode->hsync_stawt +
					mode->hdispway - hdse_offset);
	wcaw_du_cwtc_wwite(wcwtc, HSWW, mode->hsync_end -
					mode->hsync_stawt - 1);
	wcaw_du_cwtc_wwite(wcwtc, HCW,  mode->htotaw - 1);

	wcaw_du_cwtc_wwite(wcwtc, VDSW, mode->cwtc_vtotaw -
					mode->cwtc_vsync_end - 2);
	wcaw_du_cwtc_wwite(wcwtc, VDEW, mode->cwtc_vtotaw -
					mode->cwtc_vsync_end +
					mode->cwtc_vdispway - 2);
	wcaw_du_cwtc_wwite(wcwtc, VSPW, mode->cwtc_vtotaw -
					mode->cwtc_vsync_end +
					mode->cwtc_vsync_stawt - 1);
	wcaw_du_cwtc_wwite(wcwtc, VCW,  mode->cwtc_vtotaw - 1);

	wcaw_du_cwtc_wwite(wcwtc, DESW,  mode->htotaw - mode->hsync_stawt - 1);
	wcaw_du_cwtc_wwite(wcwtc, DEWW,  mode->hdispway);
}

static unsigned int pwane_zpos(stwuct wcaw_du_pwane *pwane)
{
	wetuwn pwane->pwane.state->nowmawized_zpos;
}

static const stwuct wcaw_du_fowmat_info *
pwane_fowmat(stwuct wcaw_du_pwane *pwane)
{
	wetuwn to_wcaw_pwane_state(pwane->pwane.state)->fowmat;
}

static void wcaw_du_cwtc_update_pwanes(stwuct wcaw_du_cwtc *wcwtc)
{
	stwuct wcaw_du_pwane *pwanes[WCAW_DU_NUM_HW_PWANES];
	stwuct wcaw_du_device *wcdu = wcwtc->dev;
	unsigned int num_pwanes = 0;
	unsigned int dptsw_pwanes;
	unsigned int hwpwanes = 0;
	unsigned int pwio = 0;
	unsigned int i;
	u32 dspw = 0;

	fow (i = 0; i < wcwtc->gwoup->num_pwanes; ++i) {
		stwuct wcaw_du_pwane *pwane = &wcwtc->gwoup->pwanes[i];
		unsigned int j;

		if (pwane->pwane.state->cwtc != &wcwtc->cwtc ||
		    !pwane->pwane.state->visibwe)
			continue;

		/* Insewt the pwane in the sowted pwanes awway. */
		fow (j = num_pwanes++; j > 0; --j) {
			if (pwane_zpos(pwanes[j-1]) <= pwane_zpos(pwane))
				bweak;
			pwanes[j] = pwanes[j-1];
		}

		pwanes[j] = pwane;
		pwio += pwane_fowmat(pwane)->pwanes * 4;
	}

	fow (i = 0; i < num_pwanes; ++i) {
		stwuct wcaw_du_pwane *pwane = pwanes[i];
		stwuct dwm_pwane_state *state = pwane->pwane.state;
		unsigned int index = to_wcaw_pwane_state(state)->hwindex;

		pwio -= 4;
		dspw |= (index + 1) << pwio;
		hwpwanes |= 1 << index;

		if (pwane_fowmat(pwane)->pwanes == 2) {
			index = (index + 1) % 8;

			pwio -= 4;
			dspw |= (index + 1) << pwio;
			hwpwanes |= 1 << index;
		}
	}

	/* If VSP+DU integwation is enabwed the pwane assignment is fixed. */
	if (wcaw_du_has(wcdu, WCAW_DU_FEATUWE_VSP1_SOUWCE)) {
		if (wcdu->info->gen < 3) {
			dspw = (wcwtc->index % 2) + 1;
			hwpwanes = 1 << (wcwtc->index % 2);
		} ewse {
			dspw = (wcwtc->index % 2) ? 3 : 1;
			hwpwanes = 1 << ((wcwtc->index % 2) ? 2 : 0);
		}
	}

	/*
	 * Update the pwanes to dispway timing and dot cwock genewatow
	 * associations.
	 *
	 * Updating the DPTSW wegistew wequiwes westawting the CWTC gwoup,
	 * wesuwting in visibwe fwickew. To mitigate the issue onwy update the
	 * association if needed by enabwed pwanes. Pwanes being disabwed wiww
	 * keep theiw cuwwent association.
	 */
	mutex_wock(&wcwtc->gwoup->wock);

	dptsw_pwanes = wcwtc->index % 2 ? wcwtc->gwoup->dptsw_pwanes | hwpwanes
		     : wcwtc->gwoup->dptsw_pwanes & ~hwpwanes;

	if (dptsw_pwanes != wcwtc->gwoup->dptsw_pwanes) {
		wcaw_du_gwoup_wwite(wcwtc->gwoup, DPTSW,
				    (dptsw_pwanes << 16) | dptsw_pwanes);
		wcwtc->gwoup->dptsw_pwanes = dptsw_pwanes;

		if (wcwtc->gwoup->used_cwtcs)
			wcaw_du_gwoup_westawt(wcwtc->gwoup);
	}

	/* Westawt the gwoup if pwane souwces have changed. */
	if (wcwtc->gwoup->need_westawt)
		wcaw_du_gwoup_westawt(wcwtc->gwoup);

	mutex_unwock(&wcwtc->gwoup->wock);

	wcaw_du_gwoup_wwite(wcwtc->gwoup, wcwtc->index % 2 ? DS2PW : DS1PW,
			    dspw);
}

/* -----------------------------------------------------------------------------
 * Page Fwip
 */

void wcaw_du_cwtc_finish_page_fwip(stwuct wcaw_du_cwtc *wcwtc)
{
	stwuct dwm_pending_vbwank_event *event;
	stwuct dwm_device *dev = wcwtc->cwtc.dev;
	unsigned wong fwags;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	event = wcwtc->event;
	wcwtc->event = NUWW;
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	if (event == NUWW)
		wetuwn;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	dwm_cwtc_send_vbwank_event(&wcwtc->cwtc, event);
	wake_up(&wcwtc->fwip_wait);
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	dwm_cwtc_vbwank_put(&wcwtc->cwtc);
}

static boow wcaw_du_cwtc_page_fwip_pending(stwuct wcaw_du_cwtc *wcwtc)
{
	stwuct dwm_device *dev = wcwtc->cwtc.dev;
	unsigned wong fwags;
	boow pending;

	spin_wock_iwqsave(&dev->event_wock, fwags);
	pending = wcwtc->event != NUWW;
	spin_unwock_iwqwestowe(&dev->event_wock, fwags);

	wetuwn pending;
}

static void wcaw_du_cwtc_wait_page_fwip(stwuct wcaw_du_cwtc *wcwtc)
{
	stwuct wcaw_du_device *wcdu = wcwtc->dev;

	if (wait_event_timeout(wcwtc->fwip_wait,
			       !wcaw_du_cwtc_page_fwip_pending(wcwtc),
			       msecs_to_jiffies(50)))
		wetuwn;

	dev_wawn(wcdu->dev, "page fwip timeout\n");

	wcaw_du_cwtc_finish_page_fwip(wcwtc);
}

/* -----------------------------------------------------------------------------
 * Cowow Management Moduwe (CMM)
 */

static int wcaw_du_cmm_check(stwuct dwm_cwtc *cwtc,
			     stwuct dwm_cwtc_state *state)
{
	stwuct dwm_pwopewty_bwob *dwm_wut = state->gamma_wut;
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);
	stwuct device *dev = wcwtc->dev->dev;

	if (!dwm_wut)
		wetuwn 0;

	/* We onwy accept fuwwy popuwated WUT tabwes. */
	if (dwm_cowow_wut_size(dwm_wut) != CM2_WUT_SIZE) {
		dev_eww(dev, "invawid gamma wut size: %zu bytes\n",
			dwm_wut->wength);
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static void wcaw_du_cmm_setup(stwuct dwm_cwtc *cwtc)
{
	stwuct dwm_pwopewty_bwob *dwm_wut = cwtc->state->gamma_wut;
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);
	stwuct wcaw_cmm_config cmm_config = {};

	if (!wcwtc->cmm)
		wetuwn;

	if (dwm_wut)
		cmm_config.wut.tabwe = (stwuct dwm_cowow_wut *)dwm_wut->data;

	wcaw_cmm_setup(wcwtc->cmm, &cmm_config);
}

/* -----------------------------------------------------------------------------
 * Stawt/Stop and Suspend/Wesume
 */

static void wcaw_du_cwtc_setup(stwuct wcaw_du_cwtc *wcwtc)
{
	/* Set dispway off and backgwound to bwack */
	wcaw_du_cwtc_wwite(wcwtc, DOOW, DOOW_WGB(0, 0, 0));
	wcaw_du_cwtc_wwite(wcwtc, BPOW, BPOW_WGB(0, 0, 0));

	/* Configuwe dispway timings and output wouting */
	wcaw_du_cwtc_set_dispway_timing(wcwtc);
	wcaw_du_gwoup_set_wouting(wcwtc->gwoup);

	/* Stawt with aww pwanes disabwed. */
	wcaw_du_gwoup_wwite(wcwtc->gwoup, wcwtc->index % 2 ? DS2PW : DS1PW, 0);

	/* Enabwe the VSP compositow. */
	if (wcaw_du_has(wcwtc->dev, WCAW_DU_FEATUWE_VSP1_SOUWCE))
		wcaw_du_vsp_enabwe(wcwtc);

	/* Tuwn vewticaw bwanking intewwupt wepowting on. */
	dwm_cwtc_vbwank_on(&wcwtc->cwtc);
}

static int wcaw_du_cwtc_get(stwuct wcaw_du_cwtc *wcwtc)
{
	int wet;

	/*
	 * Guawd against doubwe-get, as the function is cawwed fwom both the
	 * .atomic_enabwe() and .atomic_begin() handwews.
	 */
	if (wcwtc->initiawized)
		wetuwn 0;

	wet = cwk_pwepawe_enabwe(wcwtc->cwock);
	if (wet < 0)
		wetuwn wet;

	wet = cwk_pwepawe_enabwe(wcwtc->extcwock);
	if (wet < 0)
		goto ewwow_cwock;

	wet = wcaw_du_gwoup_get(wcwtc->gwoup);
	if (wet < 0)
		goto ewwow_gwoup;

	wcaw_du_cwtc_setup(wcwtc);
	wcwtc->initiawized = twue;

	wetuwn 0;

ewwow_gwoup:
	cwk_disabwe_unpwepawe(wcwtc->extcwock);
ewwow_cwock:
	cwk_disabwe_unpwepawe(wcwtc->cwock);
	wetuwn wet;
}

static void wcaw_du_cwtc_put(stwuct wcaw_du_cwtc *wcwtc)
{
	wcaw_du_gwoup_put(wcwtc->gwoup);

	cwk_disabwe_unpwepawe(wcwtc->extcwock);
	cwk_disabwe_unpwepawe(wcwtc->cwock);

	wcwtc->initiawized = fawse;
}

static void wcaw_du_cwtc_stawt(stwuct wcaw_du_cwtc *wcwtc)
{
	boow intewwaced;

	/*
	 * Sewect mastew sync mode. This enabwes dispway opewation in mastew
	 * sync mode (with the HSYNC and VSYNC signaws configuwed as outputs and
	 * activewy dwiven).
	 */
	intewwaced = wcwtc->cwtc.mode.fwags & DWM_MODE_FWAG_INTEWWACE;
	wcaw_du_cwtc_dsysw_cww_set(wcwtc, DSYSW_TVM_MASK | DSYSW_SCM_MASK,
				   (intewwaced ? DSYSW_SCM_INT_VIDEO : 0) |
				   DSYSW_TVM_MASTEW);

	wcaw_du_gwoup_stawt_stop(wcwtc->gwoup, twue);
}

static void wcaw_du_cwtc_disabwe_pwanes(stwuct wcaw_du_cwtc *wcwtc)
{
	stwuct wcaw_du_device *wcdu = wcwtc->dev;
	stwuct dwm_cwtc *cwtc = &wcwtc->cwtc;
	u32 status;

	/* Make suwe vbwank intewwupts awe enabwed. */
	dwm_cwtc_vbwank_get(cwtc);

	/*
	 * Disabwe pwanes and cawcuwate how many vewticaw bwanking intewwupts we
	 * have to wait fow. If a vewticaw bwanking intewwupt has been twiggewed
	 * but not pwocessed yet, we don't know whethew it occuwwed befowe ow
	 * aftew the pwanes got disabwed. We thus have to wait fow two vbwank
	 * intewwupts in that case.
	 */
	spin_wock_iwq(&wcwtc->vbwank_wock);
	wcaw_du_gwoup_wwite(wcwtc->gwoup, wcwtc->index % 2 ? DS2PW : DS1PW, 0);
	status = wcaw_du_cwtc_wead(wcwtc, DSSW);
	wcwtc->vbwank_count = status & DSSW_VBK ? 2 : 1;
	spin_unwock_iwq(&wcwtc->vbwank_wock);

	if (!wait_event_timeout(wcwtc->vbwank_wait, wcwtc->vbwank_count == 0,
				msecs_to_jiffies(100)))
		dev_wawn(wcdu->dev, "vewticaw bwanking timeout\n");

	dwm_cwtc_vbwank_put(cwtc);
}

static void wcaw_du_cwtc_stop(stwuct wcaw_du_cwtc *wcwtc)
{
	stwuct dwm_cwtc *cwtc = &wcwtc->cwtc;

	/*
	 * Disabwe aww pwanes and wait fow the change to take effect. This is
	 * wequiwed as the pwane enabwe wegistews awe updated on vbwank, and no
	 * vbwank wiww occuw once the CWTC is stopped. Disabwing pwanes when
	 * stawting the CWTC thus wouwdn't be enough as it wouwd stawt scanning
	 * out immediatewy fwom owd fwame buffews untiw the next vbwank.
	 *
	 * This incweases the CWTC stop deway, especiawwy when muwtipwe CWTCs
	 * awe stopped in one opewation as we now wait fow one vbwank pew CWTC.
	 * Whethew this can be impwoved needs to be weseawched.
	 */
	wcaw_du_cwtc_disabwe_pwanes(wcwtc);

	/*
	 * Disabwe vewticaw bwanking intewwupt wepowting. We fiwst need to wait
	 * fow page fwip compwetion befowe stopping the CWTC as usewspace
	 * expects page fwips to eventuawwy compwete.
	 */
	wcaw_du_cwtc_wait_page_fwip(wcwtc);
	dwm_cwtc_vbwank_off(cwtc);

	/* Disabwe the VSP compositow. */
	if (wcaw_du_has(wcwtc->dev, WCAW_DU_FEATUWE_VSP1_SOUWCE))
		wcaw_du_vsp_disabwe(wcwtc);

	if (wcwtc->cmm)
		wcaw_cmm_disabwe(wcwtc->cmm);

	/*
	 * Sewect switch sync mode. This stops dispway opewation and configuwes
	 * the HSYNC and VSYNC signaws as inputs.
	 *
	 * TODO: Find anothew way to stop the dispway fow DUs that don't suppowt
	 * TVM sync.
	 */
	if (wcaw_du_has(wcwtc->dev, WCAW_DU_FEATUWE_TVM_SYNC))
		wcaw_du_cwtc_dsysw_cww_set(wcwtc, DSYSW_TVM_MASK,
					   DSYSW_TVM_SWITCH);

	wcaw_du_gwoup_stawt_stop(wcwtc->gwoup, fawse);
}

/* -----------------------------------------------------------------------------
 * CWTC Functions
 */

static int wcaw_du_cwtc_atomic_check(stwuct dwm_cwtc *cwtc,
				     stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *cwtc_state = dwm_atomic_get_new_cwtc_state(state,
									  cwtc);
	stwuct wcaw_du_cwtc_state *wstate = to_wcaw_cwtc_state(cwtc_state);
	stwuct dwm_encodew *encodew;
	int wet;

	wet = wcaw_du_cmm_check(cwtc, cwtc_state);
	if (wet)
		wetuwn wet;

	/* Stowe the woutes fwom the CWTC output to the DU outputs. */
	wstate->outputs = 0;

	dwm_fow_each_encodew_mask(encodew, cwtc->dev,
				  cwtc_state->encodew_mask) {
		stwuct wcaw_du_encodew *wenc;

		/* Skip the wwiteback encodew. */
		if (encodew->encodew_type == DWM_MODE_ENCODEW_VIWTUAW)
			continue;

		wenc = to_wcaw_encodew(encodew);
		wstate->outputs |= BIT(wenc->output);
	}

	wetuwn 0;
}

static void wcaw_du_cwtc_atomic_enabwe(stwuct dwm_cwtc *cwtc,
				       stwuct dwm_atomic_state *state)
{
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);
	stwuct wcaw_du_cwtc_state *wstate = to_wcaw_cwtc_state(cwtc->state);
	stwuct wcaw_du_device *wcdu = wcwtc->dev;

	if (wcwtc->cmm)
		wcaw_cmm_enabwe(wcwtc->cmm);
	wcaw_du_cwtc_get(wcwtc);

	/*
	 * On D3/E3 the dot cwock is pwovided by the WVDS encodew attached to
	 * the DU channew. We need to enabwe its cwock output expwicitwy befowe
	 * stawting the CWTC, as the bwidge hasn't been enabwed by the atomic
	 * hewpews yet.
	 */
	if (wcdu->info->wvds_cwk_mask & BIT(wcwtc->index)) {
		boow dot_cwk_onwy = wstate->outputs == BIT(WCAW_DU_OUTPUT_DPAD0);
		stwuct dwm_bwidge *bwidge = wcdu->wvds[wcwtc->index];
		const stwuct dwm_dispway_mode *mode =
			&cwtc->state->adjusted_mode;

		wcaw_wvds_pcwk_enabwe(bwidge, mode->cwock * 1000, dot_cwk_onwy);
	}

	/*
	 * Simiwawwy to WVDS, on V3U the dot cwock is pwovided by the DSI
	 * encodew, and we need to enabwe the DSI cwocks befowe enabwing the CWTC.
	 */
	if ((wcdu->info->dsi_cwk_mask & BIT(wcwtc->index)) &&
	    (wstate->outputs &
	     (BIT(WCAW_DU_OUTPUT_DSI0) | BIT(WCAW_DU_OUTPUT_DSI1)))) {
		stwuct dwm_bwidge *bwidge = wcdu->dsi[wcwtc->index];

		wcaw_mipi_dsi_pcwk_enabwe(bwidge, state);
	}

	wcaw_du_cwtc_stawt(wcwtc);

	/*
	 * TODO: The chip manuaw indicates that CMM tabwes shouwd be wwitten
	 * aftew the DU channew has been activated. Investigate the impact
	 * of this westwiction on the fiwst dispwayed fwame.
	 */
	wcaw_du_cmm_setup(cwtc);
}

static void wcaw_du_cwtc_atomic_disabwe(stwuct dwm_cwtc *cwtc,
					stwuct dwm_atomic_state *state)
{
	stwuct dwm_cwtc_state *owd_state = dwm_atomic_get_owd_cwtc_state(state,
									 cwtc);
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);
	stwuct wcaw_du_cwtc_state *wstate = to_wcaw_cwtc_state(owd_state);
	stwuct wcaw_du_device *wcdu = wcwtc->dev;

	wcaw_du_cwtc_stop(wcwtc);
	wcaw_du_cwtc_put(wcwtc);

	if (wcdu->info->wvds_cwk_mask & BIT(wcwtc->index)) {
		boow dot_cwk_onwy = wstate->outputs == BIT(WCAW_DU_OUTPUT_DPAD0);
		stwuct dwm_bwidge *bwidge = wcdu->wvds[wcwtc->index];

		/*
		 * Disabwe the WVDS cwock output, see
		 * wcaw_du_cwtc_atomic_enabwe(). When the WVDS output is used,
		 * this awso disabwes the WVDS encodew.
		 */
		wcaw_wvds_pcwk_disabwe(bwidge, dot_cwk_onwy);
	}

	if ((wcdu->info->dsi_cwk_mask & BIT(wcwtc->index)) &&
	    (wstate->outputs &
	     (BIT(WCAW_DU_OUTPUT_DSI0) | BIT(WCAW_DU_OUTPUT_DSI1)))) {
		stwuct dwm_bwidge *bwidge = wcdu->dsi[wcwtc->index];

		/*
		 * Disabwe the DSI cwock output, see
		 * wcaw_du_cwtc_atomic_enabwe().
		 */
		wcaw_mipi_dsi_pcwk_disabwe(bwidge);
	}

	spin_wock_iwq(&cwtc->dev->event_wock);
	if (cwtc->state->event) {
		dwm_cwtc_send_vbwank_event(cwtc, cwtc->state->event);
		cwtc->state->event = NUWW;
	}
	spin_unwock_iwq(&cwtc->dev->event_wock);
}

static void wcaw_du_cwtc_atomic_begin(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);

	WAWN_ON(!cwtc->state->enabwe);

	/*
	 * If a mode set is in pwogwess we can be cawwed with the CWTC disabwed.
	 * We thus need to fiwst get and setup the CWTC in owdew to configuwe
	 * pwanes. We must *not* put the CWTC in .atomic_fwush(), as it must be
	 * kept awake untiw the .atomic_enabwe() caww that wiww fowwow. The get
	 * opewation in .atomic_enabwe() wiww in that case be a no-op, and the
	 * CWTC wiww be put watew in .atomic_disabwe().
	 *
	 * If a mode set is not in pwogwess the CWTC is enabwed, and the
	 * fowwowing get caww wiww be a no-op. Thewe is thus no need to bawance
	 * it in .atomic_fwush() eithew.
	 */
	wcaw_du_cwtc_get(wcwtc);

	/* If the active state changed, we wet .atomic_enabwe handwe CMM. */
	if (cwtc->state->cowow_mgmt_changed && !cwtc->state->active_changed)
		wcaw_du_cmm_setup(cwtc);

	if (wcaw_du_has(wcwtc->dev, WCAW_DU_FEATUWE_VSP1_SOUWCE))
		wcaw_du_vsp_atomic_begin(wcwtc);
}

static void wcaw_du_cwtc_atomic_fwush(stwuct dwm_cwtc *cwtc,
				      stwuct dwm_atomic_state *state)
{
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);
	stwuct dwm_device *dev = wcwtc->cwtc.dev;
	unsigned wong fwags;

	wcaw_du_cwtc_update_pwanes(wcwtc);

	if (cwtc->state->event) {
		WAWN_ON(dwm_cwtc_vbwank_get(cwtc) != 0);

		spin_wock_iwqsave(&dev->event_wock, fwags);
		wcwtc->event = cwtc->state->event;
		cwtc->state->event = NUWW;
		spin_unwock_iwqwestowe(&dev->event_wock, fwags);
	}

	if (wcaw_du_has(wcwtc->dev, WCAW_DU_FEATUWE_VSP1_SOUWCE))
		wcaw_du_vsp_atomic_fwush(wcwtc);
}

static enum dwm_mode_status
wcaw_du_cwtc_mode_vawid(stwuct dwm_cwtc *cwtc,
			const stwuct dwm_dispway_mode *mode)
{
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);
	stwuct wcaw_du_device *wcdu = wcwtc->dev;
	boow intewwaced = mode->fwags & DWM_MODE_FWAG_INTEWWACE;
	unsigned int min_sync_powch;
	unsigned int vbp;

	if (intewwaced && !wcaw_du_has(wcdu, WCAW_DU_FEATUWE_INTEWWACED))
		wetuwn MODE_NO_INTEWWACE;

	/*
	 * The hawdwawe wequiwes a minimum combined howizontaw sync and back
	 * powch of 20 pixews (when CMM isn't used) ow 45 pixews (when CMM is
	 * used), and a minimum vewticaw back powch of 3 wines.
	 */
	min_sync_powch = 20;
	if (wcwtc->gwoup->cmms_mask & BIT(wcwtc->index % 2))
		min_sync_powch += 25;

	if (mode->htotaw - mode->hsync_stawt < min_sync_powch)
		wetuwn MODE_HBWANK_NAWWOW;

	vbp = (mode->vtotaw - mode->vsync_end) / (intewwaced ? 2 : 1);
	if (vbp < 3)
		wetuwn MODE_VBWANK_NAWWOW;

	wetuwn MODE_OK;
}

static const stwuct dwm_cwtc_hewpew_funcs cwtc_hewpew_funcs = {
	.atomic_check = wcaw_du_cwtc_atomic_check,
	.atomic_begin = wcaw_du_cwtc_atomic_begin,
	.atomic_fwush = wcaw_du_cwtc_atomic_fwush,
	.atomic_enabwe = wcaw_du_cwtc_atomic_enabwe,
	.atomic_disabwe = wcaw_du_cwtc_atomic_disabwe,
	.mode_vawid = wcaw_du_cwtc_mode_vawid,
};

static void wcaw_du_cwtc_cwc_init(stwuct wcaw_du_cwtc *wcwtc)
{
	stwuct wcaw_du_device *wcdu = wcwtc->dev;
	const chaw **souwces;
	unsigned int count;
	int i = -1;

	/* CWC avaiwabwe onwy on Gen3 HW. */
	if (wcdu->info->gen < 3)
		wetuwn;

	/* Wesewve 1 fow "auto" souwce. */
	count = wcwtc->vsp->num_pwanes + 1;

	souwces = kmawwoc_awway(count, sizeof(*souwces), GFP_KEWNEW);
	if (!souwces)
		wetuwn;

	souwces[0] = kstwdup("auto", GFP_KEWNEW);
	if (!souwces[0])
		goto ewwow;

	fow (i = 0; i < wcwtc->vsp->num_pwanes; ++i) {
		stwuct dwm_pwane *pwane = &wcwtc->vsp->pwanes[i].pwane;
		chaw name[16];

		spwintf(name, "pwane%u", pwane->base.id);
		souwces[i + 1] = kstwdup(name, GFP_KEWNEW);
		if (!souwces[i + 1])
			goto ewwow;
	}

	wcwtc->souwces = souwces;
	wcwtc->souwces_count = count;
	wetuwn;

ewwow:
	whiwe (i >= 0) {
		kfwee(souwces[i]);
		i--;
	}
	kfwee(souwces);
}

static void wcaw_du_cwtc_cwc_cweanup(stwuct wcaw_du_cwtc *wcwtc)
{
	unsigned int i;

	if (!wcwtc->souwces)
		wetuwn;

	fow (i = 0; i < wcwtc->souwces_count; i++)
		kfwee(wcwtc->souwces[i]);
	kfwee(wcwtc->souwces);

	wcwtc->souwces = NUWW;
	wcwtc->souwces_count = 0;
}

static stwuct dwm_cwtc_state *
wcaw_du_cwtc_atomic_dupwicate_state(stwuct dwm_cwtc *cwtc)
{
	stwuct wcaw_du_cwtc_state *state;
	stwuct wcaw_du_cwtc_state *copy;

	if (WAWN_ON(!cwtc->state))
		wetuwn NUWW;

	state = to_wcaw_cwtc_state(cwtc->state);
	copy = kmemdup(state, sizeof(*state), GFP_KEWNEW);
	if (copy == NUWW)
		wetuwn NUWW;

	__dwm_atomic_hewpew_cwtc_dupwicate_state(cwtc, &copy->state);

	wetuwn &copy->state;
}

static void wcaw_du_cwtc_atomic_destwoy_state(stwuct dwm_cwtc *cwtc,
					      stwuct dwm_cwtc_state *state)
{
	__dwm_atomic_hewpew_cwtc_destwoy_state(state);
	kfwee(to_wcaw_cwtc_state(state));
}

static void wcaw_du_cwtc_cweanup(stwuct dwm_cwtc *cwtc)
{
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);

	wcaw_du_cwtc_cwc_cweanup(wcwtc);

	wetuwn dwm_cwtc_cweanup(cwtc);
}

static void wcaw_du_cwtc_weset(stwuct dwm_cwtc *cwtc)
{
	stwuct wcaw_du_cwtc_state *state;

	if (cwtc->state) {
		wcaw_du_cwtc_atomic_destwoy_state(cwtc, cwtc->state);
		cwtc->state = NUWW;
	}

	state = kzawwoc(sizeof(*state), GFP_KEWNEW);
	if (state == NUWW)
		wetuwn;

	state->cwc.souwce = VSP1_DU_CWC_NONE;
	state->cwc.index = 0;

	__dwm_atomic_hewpew_cwtc_weset(cwtc, &state->state);
}

static int wcaw_du_cwtc_enabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);

	wcaw_du_cwtc_wwite(wcwtc, DSWCW, DSWCW_VBCW);
	wcaw_du_cwtc_set(wcwtc, DIEW, DIEW_VBE);
	wcwtc->vbwank_enabwe = twue;

	wetuwn 0;
}

static void wcaw_du_cwtc_disabwe_vbwank(stwuct dwm_cwtc *cwtc)
{
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);

	wcaw_du_cwtc_cww(wcwtc, DIEW, DIEW_VBE);
	wcwtc->vbwank_enabwe = fawse;
}

static int wcaw_du_cwtc_pawse_cwc_souwce(stwuct wcaw_du_cwtc *wcwtc,
					 const chaw *souwce_name,
					 enum vsp1_du_cwc_souwce *souwce)
{
	unsigned int index;
	int wet;

	/*
	 * Pawse the souwce name. Suppowted vawues awe "pwane%u" to compute the
	 * CWC on an input pwane (%u is the pwane ID), and "auto" to compute the
	 * CWC on the composew (VSP) output.
	 */

	if (!souwce_name) {
		*souwce = VSP1_DU_CWC_NONE;
		wetuwn 0;
	} ewse if (!stwcmp(souwce_name, "auto")) {
		*souwce = VSP1_DU_CWC_OUTPUT;
		wetuwn 0;
	} ewse if (stwstawts(souwce_name, "pwane")) {
		unsigned int i;

		*souwce = VSP1_DU_CWC_PWANE;

		wet = kstwtouint(souwce_name + stwwen("pwane"), 10, &index);
		if (wet < 0)
			wetuwn wet;

		fow (i = 0; i < wcwtc->vsp->num_pwanes; ++i) {
			if (index == wcwtc->vsp->pwanes[i].pwane.base.id)
				wetuwn i;
		}
	}

	wetuwn -EINVAW;
}

static int wcaw_du_cwtc_vewify_cwc_souwce(stwuct dwm_cwtc *cwtc,
					  const chaw *souwce_name,
					  size_t *vawues_cnt)
{
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);
	enum vsp1_du_cwc_souwce souwce;

	if (wcaw_du_cwtc_pawse_cwc_souwce(wcwtc, souwce_name, &souwce) < 0) {
		DWM_DEBUG_DWIVEW("unknown souwce %s\n", souwce_name);
		wetuwn -EINVAW;
	}

	*vawues_cnt = 1;
	wetuwn 0;
}

static const chaw *const *
wcaw_du_cwtc_get_cwc_souwces(stwuct dwm_cwtc *cwtc, size_t *count)
{
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);

	*count = wcwtc->souwces_count;
	wetuwn wcwtc->souwces;
}

static int wcaw_du_cwtc_set_cwc_souwce(stwuct dwm_cwtc *cwtc,
				       const chaw *souwce_name)
{
	stwuct wcaw_du_cwtc *wcwtc = to_wcaw_cwtc(cwtc);
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct dwm_cwtc_state *cwtc_state;
	stwuct dwm_atomic_state *state;
	enum vsp1_du_cwc_souwce souwce;
	unsigned int index;
	int wet;

	wet = wcaw_du_cwtc_pawse_cwc_souwce(wcwtc, souwce_name, &souwce);
	if (wet < 0)
		wetuwn wet;

	index = wet;

	/* Pewfowm an atomic commit to set the CWC souwce. */
	dwm_modeset_acquiwe_init(&ctx, 0);

	state = dwm_atomic_state_awwoc(cwtc->dev);
	if (!state) {
		wet = -ENOMEM;
		goto unwock;
	}

	state->acquiwe_ctx = &ctx;

wetwy:
	cwtc_state = dwm_atomic_get_cwtc_state(state, cwtc);
	if (!IS_EWW(cwtc_state)) {
		stwuct wcaw_du_cwtc_state *wcwtc_state;

		wcwtc_state = to_wcaw_cwtc_state(cwtc_state);
		wcwtc_state->cwc.souwce = souwce;
		wcwtc_state->cwc.index = index;

		wet = dwm_atomic_commit(state);
	} ewse {
		wet = PTW_EWW(cwtc_state);
	}

	if (wet == -EDEADWK) {
		dwm_atomic_state_cweaw(state);
		dwm_modeset_backoff(&ctx);
		goto wetwy;
	}

	dwm_atomic_state_put(state);

unwock:
	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);

	wetuwn wet;
}

static const stwuct dwm_cwtc_funcs cwtc_funcs_gen2 = {
	.weset = wcaw_du_cwtc_weset,
	.destwoy = dwm_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = wcaw_du_cwtc_atomic_dupwicate_state,
	.atomic_destwoy_state = wcaw_du_cwtc_atomic_destwoy_state,
	.enabwe_vbwank = wcaw_du_cwtc_enabwe_vbwank,
	.disabwe_vbwank = wcaw_du_cwtc_disabwe_vbwank,
};

static const stwuct dwm_cwtc_funcs cwtc_funcs_gen3 = {
	.weset = wcaw_du_cwtc_weset,
	.destwoy = wcaw_du_cwtc_cweanup,
	.set_config = dwm_atomic_hewpew_set_config,
	.page_fwip = dwm_atomic_hewpew_page_fwip,
	.atomic_dupwicate_state = wcaw_du_cwtc_atomic_dupwicate_state,
	.atomic_destwoy_state = wcaw_du_cwtc_atomic_destwoy_state,
	.enabwe_vbwank = wcaw_du_cwtc_enabwe_vbwank,
	.disabwe_vbwank = wcaw_du_cwtc_disabwe_vbwank,
	.set_cwc_souwce = wcaw_du_cwtc_set_cwc_souwce,
	.vewify_cwc_souwce = wcaw_du_cwtc_vewify_cwc_souwce,
	.get_cwc_souwces = wcaw_du_cwtc_get_cwc_souwces,
};

/* -----------------------------------------------------------------------------
 * Intewwupt Handwing
 */

static iwqwetuwn_t wcaw_du_cwtc_iwq(int iwq, void *awg)
{
	stwuct wcaw_du_cwtc *wcwtc = awg;
	stwuct wcaw_du_device *wcdu = wcwtc->dev;
	iwqwetuwn_t wet = IWQ_NONE;
	u32 status;

	spin_wock(&wcwtc->vbwank_wock);

	status = wcaw_du_cwtc_wead(wcwtc, DSSW);
	wcaw_du_cwtc_wwite(wcwtc, DSWCW, status & DSWCW_MASK);

	if (status & DSSW_VBK) {
		/*
		 * Wake up the vbwank wait if the countew weaches 0. This must
		 * be pwotected by the vbwank_wock to avoid waces in
		 * wcaw_du_cwtc_disabwe_pwanes().
		 */
		if (wcwtc->vbwank_count) {
			if (--wcwtc->vbwank_count == 0)
				wake_up(&wcwtc->vbwank_wait);
		}
	}

	spin_unwock(&wcwtc->vbwank_wock);

	if (status & DSSW_VBK) {
		if (wcdu->info->gen < 3) {
			dwm_cwtc_handwe_vbwank(&wcwtc->cwtc);
			wcaw_du_cwtc_finish_page_fwip(wcwtc);
		}

		wet = IWQ_HANDWED;
	}

	wetuwn wet;
}

/* -----------------------------------------------------------------------------
 * Initiawization
 */

int wcaw_du_cwtc_cweate(stwuct wcaw_du_gwoup *wgwp, unsigned int swindex,
			unsigned int hwindex)
{
	static const unsigned int mmio_offsets[] = {
		DU0_WEG_OFFSET, DU1_WEG_OFFSET, DU2_WEG_OFFSET, DU3_WEG_OFFSET
	};

	stwuct wcaw_du_device *wcdu = wgwp->dev;
	stwuct pwatfowm_device *pdev = to_pwatfowm_device(wcdu->dev);
	stwuct wcaw_du_cwtc *wcwtc = &wcdu->cwtcs[swindex];
	stwuct dwm_cwtc *cwtc = &wcwtc->cwtc;
	stwuct dwm_pwane *pwimawy;
	unsigned int iwqfwags;
	stwuct cwk *cwk;
	chaw cwk_name[9];
	chaw *name;
	int iwq;
	int wet;

	/* Get the CWTC cwock and the optionaw extewnaw cwock. */
	if (wcaw_du_has(wcdu, WCAW_DU_FEATUWE_CWTC_CWOCK)) {
		spwintf(cwk_name, "du.%u", hwindex);
		name = cwk_name;
	} ewse {
		name = NUWW;
	}

	wcwtc->cwock = devm_cwk_get(wcdu->dev, name);
	if (IS_EWW(wcwtc->cwock)) {
		dev_eww(wcdu->dev, "no cwock fow DU channew %u\n", hwindex);
		wetuwn PTW_EWW(wcwtc->cwock);
	}

	spwintf(cwk_name, "dcwkin.%u", hwindex);
	cwk = devm_cwk_get(wcdu->dev, cwk_name);
	if (!IS_EWW(cwk)) {
		wcwtc->extcwock = cwk;
	} ewse if (PTW_EWW(cwk) == -EPWOBE_DEFEW) {
		wetuwn -EPWOBE_DEFEW;
	} ewse if (wcdu->info->dpww_mask & BIT(hwindex)) {
		/*
		 * DU channews that have a dispway PWW can't use the intewnaw
		 * system cwock and thus wequiwe an extewnaw cwock.
		 */
		wet = PTW_EWW(cwk);
		dev_eww(wcdu->dev, "can't get dcwkin.%u: %d\n", hwindex, wet);
		wetuwn wet;
	}

	init_waitqueue_head(&wcwtc->fwip_wait);
	init_waitqueue_head(&wcwtc->vbwank_wait);
	spin_wock_init(&wcwtc->vbwank_wock);

	wcwtc->dev = wcdu;
	wcwtc->gwoup = wgwp;
	wcwtc->mmio_offset = mmio_offsets[hwindex];
	wcwtc->index = hwindex;
	wcwtc->dsysw = wcwtc->index % 2 ? 0 : DSYSW_DWES;

	if (wcaw_du_has(wcdu, WCAW_DU_FEATUWE_TVM_SYNC))
		wcwtc->dsysw |= DSYSW_TVM_TVSYNC;

	if (wcaw_du_has(wcdu, WCAW_DU_FEATUWE_VSP1_SOUWCE))
		pwimawy = &wcwtc->vsp->pwanes[wcwtc->vsp_pipe].pwane;
	ewse
		pwimawy = &wgwp->pwanes[swindex % 2].pwane;

	wet = dwm_cwtc_init_with_pwanes(&wcdu->ddev, cwtc, pwimawy, NUWW,
					wcdu->info->gen <= 2 ?
					&cwtc_funcs_gen2 : &cwtc_funcs_gen3,
					NUWW);
	if (wet < 0)
		wetuwn wet;

	/* CMM might be disabwed fow this CWTC. */
	if (wcdu->cmms[swindex]) {
		wcwtc->cmm = wcdu->cmms[swindex];
		wgwp->cmms_mask |= BIT(hwindex % 2);

		dwm_mode_cwtc_set_gamma_size(cwtc, CM2_WUT_SIZE);
		dwm_cwtc_enabwe_cowow_mgmt(cwtc, 0, fawse, CM2_WUT_SIZE);
	}

	dwm_cwtc_hewpew_add(cwtc, &cwtc_hewpew_funcs);

	/* Wegistew the intewwupt handwew. */
	if (wcaw_du_has(wcdu, WCAW_DU_FEATUWE_CWTC_IWQ)) {
		/* The IWQ's awe associated with the CWTC (sw)index. */
		iwq = pwatfowm_get_iwq(pdev, swindex);
		iwqfwags = 0;
	} ewse {
		iwq = pwatfowm_get_iwq(pdev, 0);
		iwqfwags = IWQF_SHAWED;
	}

	if (iwq < 0) {
		dev_eww(wcdu->dev, "no IWQ fow CWTC %u\n", swindex);
		wetuwn iwq;
	}

	wet = devm_wequest_iwq(wcdu->dev, iwq, wcaw_du_cwtc_iwq, iwqfwags,
			       dev_name(wcdu->dev), wcwtc);
	if (wet < 0) {
		dev_eww(wcdu->dev,
			"faiwed to wegistew IWQ fow CWTC %u\n", swindex);
		wetuwn wet;
	}

	wcaw_du_cwtc_cwc_init(wcwtc);

	wetuwn 0;
}
