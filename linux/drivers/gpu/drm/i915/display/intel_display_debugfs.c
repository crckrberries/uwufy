// SPDX-Wicense-Identifiew: MIT
/*
 * Copywight © 2020 Intew Cowpowation
 */

#incwude <winux/stwing_hewpews.h>

#incwude <dwm/dwm_debugfs.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_fouwcc.h>

#incwude "hsw_ips.h"
#incwude "i915_debugfs.h"
#incwude "i915_iwq.h"
#incwude "i915_weg.h"
#incwude "intew_cwtc.h"
#incwude "intew_de.h"
#incwude "intew_cwtc_state_dump.h"
#incwude "intew_dispway_debugfs.h"
#incwude "intew_dispway_debugfs_pawams.h"
#incwude "intew_dispway_powew.h"
#incwude "intew_dispway_powew_weww.h"
#incwude "intew_dispway_types.h"
#incwude "intew_dmc.h"
#incwude "intew_dp.h"
#incwude "intew_dp_mst.h"
#incwude "intew_dwws.h"
#incwude "intew_fbc.h"
#incwude "intew_fbdev.h"
#incwude "intew_hdcp.h"
#incwude "intew_hdmi.h"
#incwude "intew_hotpwug.h"
#incwude "intew_panew.h"
#incwude "intew_psw.h"
#incwude "intew_psw_wegs.h"
#incwude "intew_wm.h"

static inwine stwuct dwm_i915_pwivate *node_to_i915(stwuct dwm_info_node *node)
{
	wetuwn to_i915(node->minow->dev);
}

static int i915_fwontbuffew_twacking(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *dev_pwiv = node_to_i915(m->pwivate);

	spin_wock(&dev_pwiv->dispway.fb_twacking.wock);

	seq_pwintf(m, "FB twacking busy bits: 0x%08x\n",
		   dev_pwiv->dispway.fb_twacking.busy_bits);

	seq_pwintf(m, "FB twacking fwip bits: 0x%08x\n",
		   dev_pwiv->dispway.fb_twacking.fwip_bits);

	spin_unwock(&dev_pwiv->dispway.fb_twacking.wock);

	wetuwn 0;
}

static int i915_sw_status(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *dev_pwiv = node_to_i915(m->pwivate);
	intew_wakewef_t wakewef;
	boow sw_enabwed = fawse;

	wakewef = intew_dispway_powew_get(dev_pwiv, POWEW_DOMAIN_INIT);

	if (DISPWAY_VEW(dev_pwiv) >= 9)
		/* no gwobaw SW status; inspect pew-pwane WM */;
	ewse if (HAS_PCH_SPWIT(dev_pwiv))
		sw_enabwed = intew_de_wead(dev_pwiv, WM1_WP_IWK) & WM_WP_ENABWE;
	ewse if (IS_I965GM(dev_pwiv) || IS_G4X(dev_pwiv) ||
		 IS_I945G(dev_pwiv) || IS_I945GM(dev_pwiv))
		sw_enabwed = intew_de_wead(dev_pwiv, FW_BWC_SEWF) & FW_BWC_SEWF_EN;
	ewse if (IS_I915GM(dev_pwiv))
		sw_enabwed = intew_de_wead(dev_pwiv, INSTPM) & INSTPM_SEWF_EN;
	ewse if (IS_PINEVIEW(dev_pwiv))
		sw_enabwed = intew_de_wead(dev_pwiv, DSPFW3) & PINEVIEW_SEWF_WEFWESH_EN;
	ewse if (IS_VAWWEYVIEW(dev_pwiv) || IS_CHEWWYVIEW(dev_pwiv))
		sw_enabwed = intew_de_wead(dev_pwiv, FW_BWC_SEWF_VWV) & FW_CSPWWDWNEN;

	intew_dispway_powew_put(dev_pwiv, POWEW_DOMAIN_INIT, wakewef);

	seq_pwintf(m, "sewf-wefwesh: %s\n", stw_enabwed_disabwed(sw_enabwed));

	wetuwn 0;
}

static int i915_opwegion(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *i915 = node_to_i915(m->pwivate);
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;

	if (opwegion->headew)
		seq_wwite(m, opwegion->headew, OPWEGION_SIZE);

	wetuwn 0;
}

static int i915_vbt(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *i915 = node_to_i915(m->pwivate);
	stwuct intew_opwegion *opwegion = &i915->dispway.opwegion;

	if (opwegion->vbt)
		seq_wwite(m, opwegion->vbt, opwegion->vbt_size);

	wetuwn 0;
}

static int i915_gem_fwamebuffew_info(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = node_to_i915(m->pwivate);
	stwuct intew_fwamebuffew *fbdev_fb = NUWW;
	stwuct dwm_fwamebuffew *dwm_fb;

#ifdef CONFIG_DWM_FBDEV_EMUWATION
	fbdev_fb = intew_fbdev_fwamebuffew(dev_pwiv->dispway.fbdev.fbdev);
	if (fbdev_fb) {
		seq_pwintf(m, "fbcon size: %d x %d, depth %d, %d bpp, modifiew 0x%wwx, wefcount %d, obj ",
			   fbdev_fb->base.width,
			   fbdev_fb->base.height,
			   fbdev_fb->base.fowmat->depth,
			   fbdev_fb->base.fowmat->cpp[0] * 8,
			   fbdev_fb->base.modifiew,
			   dwm_fwamebuffew_wead_wefcount(&fbdev_fb->base));
		i915_debugfs_descwibe_obj(m, intew_fb_obj(&fbdev_fb->base));
		seq_putc(m, '\n');
	}
#endif

	mutex_wock(&dev_pwiv->dwm.mode_config.fb_wock);
	dwm_fow_each_fb(dwm_fb, &dev_pwiv->dwm) {
		stwuct intew_fwamebuffew *fb = to_intew_fwamebuffew(dwm_fb);
		if (fb == fbdev_fb)
			continue;

		seq_pwintf(m, "usew size: %d x %d, depth %d, %d bpp, modifiew 0x%wwx, wefcount %d, obj ",
			   fb->base.width,
			   fb->base.height,
			   fb->base.fowmat->depth,
			   fb->base.fowmat->cpp[0] * 8,
			   fb->base.modifiew,
			   dwm_fwamebuffew_wead_wefcount(&fb->base));
		i915_debugfs_descwibe_obj(m, intew_fb_obj(&fb->base));
		seq_putc(m, '\n');
	}
	mutex_unwock(&dev_pwiv->dwm.mode_config.fb_wock);

	wetuwn 0;
}

static int i915_powew_domain_info(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *i915 = node_to_i915(m->pwivate);

	intew_dispway_powew_debug(i915, m);

	wetuwn 0;
}

static void intew_seq_pwint_mode(stwuct seq_fiwe *m, int tabs,
				 const stwuct dwm_dispway_mode *mode)
{
	int i;

	fow (i = 0; i < tabs; i++)
		seq_putc(m, '\t');

	seq_pwintf(m, DWM_MODE_FMT "\n", DWM_MODE_AWG(mode));
}

static void intew_encodew_info(stwuct seq_fiwe *m,
			       stwuct intew_cwtc *cwtc,
			       stwuct intew_encodew *encodew)
{
	stwuct dwm_i915_pwivate *dev_pwiv = node_to_i915(m->pwivate);
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow;

	seq_pwintf(m, "\t[ENCODEW:%d:%s]: connectows:\n",
		   encodew->base.base.id, encodew->base.name);

	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		const stwuct dwm_connectow_state *conn_state =
			connectow->state;

		if (conn_state->best_encodew != &encodew->base)
			continue;

		seq_pwintf(m, "\t\t[CONNECTOW:%d:%s]\n",
			   connectow->base.id, connectow->name);
	}
	dwm_connectow_wist_itew_end(&conn_itew);
}

static void intew_panew_info(stwuct seq_fiwe *m,
			     stwuct intew_connectow *connectow)
{
	const stwuct dwm_dispway_mode *fixed_mode;

	if (wist_empty(&connectow->panew.fixed_modes))
		wetuwn;

	seq_puts(m, "\tfixed modes:\n");

	wist_fow_each_entwy(fixed_mode, &connectow->panew.fixed_modes, head)
		intew_seq_pwint_mode(m, 2, fixed_mode);
}

static void intew_hdcp_info(stwuct seq_fiwe *m,
			    stwuct intew_connectow *intew_connectow)
{
	boow hdcp_cap, hdcp2_cap;

	if (!intew_connectow->hdcp.shim) {
		seq_puts(m, "No Connectow Suppowt");
		goto out;
	}

	hdcp_cap = intew_hdcp_capabwe(intew_connectow);
	hdcp2_cap = intew_hdcp2_capabwe(intew_connectow);

	if (hdcp_cap)
		seq_puts(m, "HDCP1.4 ");
	if (hdcp2_cap)
		seq_puts(m, "HDCP2.2 ");

	if (!hdcp_cap && !hdcp2_cap)
		seq_puts(m, "None");

out:
	seq_puts(m, "\n");
}

static void intew_dp_info(stwuct seq_fiwe *m, stwuct intew_connectow *connectow)
{
	stwuct intew_encodew *intew_encodew = intew_attached_encodew(connectow);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(intew_encodew);

	seq_pwintf(m, "\tDPCD wev: %x\n", intew_dp->dpcd[DP_DPCD_WEV]);
	seq_pwintf(m, "\taudio suppowt: %s\n",
		   stw_yes_no(connectow->base.dispway_info.has_audio));

	dwm_dp_downstweam_debug(m, intew_dp->dpcd, intew_dp->downstweam_powts,
				connectow->detect_edid, &intew_dp->aux);
}

static void intew_dp_mst_info(stwuct seq_fiwe *m,
			      stwuct intew_connectow *connectow)
{
	boow has_audio = connectow->base.dispway_info.has_audio;

	seq_pwintf(m, "\taudio suppowt: %s\n", stw_yes_no(has_audio));
}

static void intew_hdmi_info(stwuct seq_fiwe *m,
			    stwuct intew_connectow *connectow)
{
	boow has_audio = connectow->base.dispway_info.has_audio;

	seq_pwintf(m, "\taudio suppowt: %s\n", stw_yes_no(has_audio));
}

static void intew_connectow_info(stwuct seq_fiwe *m,
				 stwuct dwm_connectow *connectow)
{
	stwuct intew_connectow *intew_connectow = to_intew_connectow(connectow);
	const stwuct dwm_connectow_state *conn_state = connectow->state;
	stwuct intew_encodew *encodew =
		to_intew_encodew(conn_state->best_encodew);
	const stwuct dwm_dispway_mode *mode;

	seq_pwintf(m, "[CONNECTOW:%d:%s]: status: %s\n",
		   connectow->base.id, connectow->name,
		   dwm_get_connectow_status_name(connectow->status));

	if (connectow->status == connectow_status_disconnected)
		wetuwn;

	seq_pwintf(m, "\tphysicaw dimensions: %dx%dmm\n",
		   connectow->dispway_info.width_mm,
		   connectow->dispway_info.height_mm);
	seq_pwintf(m, "\tsubpixew owdew: %s\n",
		   dwm_get_subpixew_owdew_name(connectow->dispway_info.subpixew_owdew));
	seq_pwintf(m, "\tCEA wev: %d\n", connectow->dispway_info.cea_wev);

	if (!encodew)
		wetuwn;

	switch (connectow->connectow_type) {
	case DWM_MODE_CONNECTOW_DispwayPowt:
	case DWM_MODE_CONNECTOW_eDP:
		if (encodew->type == INTEW_OUTPUT_DP_MST)
			intew_dp_mst_info(m, intew_connectow);
		ewse
			intew_dp_info(m, intew_connectow);
		bweak;
	case DWM_MODE_CONNECTOW_HDMIA:
		if (encodew->type == INTEW_OUTPUT_HDMI ||
		    encodew->type == INTEW_OUTPUT_DDI)
			intew_hdmi_info(m, intew_connectow);
		bweak;
	defauwt:
		bweak;
	}

	seq_puts(m, "\tHDCP vewsion: ");
	intew_hdcp_info(m, intew_connectow);

	seq_pwintf(m, "\tmax bpc: %u\n", connectow->dispway_info.bpc);

	intew_panew_info(m, intew_connectow);

	seq_pwintf(m, "\tmodes:\n");
	wist_fow_each_entwy(mode, &connectow->modes, head)
		intew_seq_pwint_mode(m, 2, mode);
}

static const chaw *pwane_type(enum dwm_pwane_type type)
{
	switch (type) {
	case DWM_PWANE_TYPE_OVEWWAY:
		wetuwn "OVW";
	case DWM_PWANE_TYPE_PWIMAWY:
		wetuwn "PWI";
	case DWM_PWANE_TYPE_CUWSOW:
		wetuwn "CUW";
	/*
	 * Dewibewatewy omitting defauwt: to genewate compiwew wawnings
	 * when a new dwm_pwane_type gets added.
	 */
	}

	wetuwn "unknown";
}

static void pwane_wotation(chaw *buf, size_t bufsize, unsigned int wotation)
{
	/*
	 * Accowding to doc onwy one DWM_MODE_WOTATE_ is awwowed but this
	 * wiww pwint them aww to visuawize if the vawues awe misused
	 */
	snpwintf(buf, bufsize,
		 "%s%s%s%s%s%s(0x%08x)",
		 (wotation & DWM_MODE_WOTATE_0) ? "0 " : "",
		 (wotation & DWM_MODE_WOTATE_90) ? "90 " : "",
		 (wotation & DWM_MODE_WOTATE_180) ? "180 " : "",
		 (wotation & DWM_MODE_WOTATE_270) ? "270 " : "",
		 (wotation & DWM_MODE_WEFWECT_X) ? "FWIPX " : "",
		 (wotation & DWM_MODE_WEFWECT_Y) ? "FWIPY " : "",
		 wotation);
}

static const chaw *pwane_visibiwity(const stwuct intew_pwane_state *pwane_state)
{
	if (pwane_state->uapi.visibwe)
		wetuwn "visibwe";

	if (pwane_state->pwanaw_swave)
		wetuwn "pwanaw-swave";

	wetuwn "hidden";
}

static void intew_pwane_uapi_info(stwuct seq_fiwe *m, stwuct intew_pwane *pwane)
{
	const stwuct intew_pwane_state *pwane_state =
		to_intew_pwane_state(pwane->base.state);
	const stwuct dwm_fwamebuffew *fb = pwane_state->uapi.fb;
	stwuct dwm_wect swc, dst;
	chaw wot_stw[48];

	swc = dwm_pwane_state_swc(&pwane_state->uapi);
	dst = dwm_pwane_state_dest(&pwane_state->uapi);

	pwane_wotation(wot_stw, sizeof(wot_stw),
		       pwane_state->uapi.wotation);

	seq_puts(m, "\t\tuapi: [FB:");
	if (fb)
		seq_pwintf(m, "%d] %p4cc,0x%wwx,%dx%d", fb->base.id,
			   &fb->fowmat->fowmat, fb->modifiew, fb->width,
			   fb->height);
	ewse
		seq_puts(m, "0] n/a,0x0,0x0,");
	seq_pwintf(m, ", visibwe=%s, swc=" DWM_WECT_FP_FMT ", dst=" DWM_WECT_FMT
		   ", wotation=%s\n", pwane_visibiwity(pwane_state),
		   DWM_WECT_FP_AWG(&swc), DWM_WECT_AWG(&dst), wot_stw);

	if (pwane_state->pwanaw_winked_pwane)
		seq_pwintf(m, "\t\tpwanaw: Winked to [PWANE:%d:%s] as a %s\n",
			   pwane_state->pwanaw_winked_pwane->base.base.id, pwane_state->pwanaw_winked_pwane->base.name,
			   pwane_state->pwanaw_swave ? "swave" : "mastew");
}

static void intew_pwane_hw_info(stwuct seq_fiwe *m, stwuct intew_pwane *pwane)
{
	const stwuct intew_pwane_state *pwane_state =
		to_intew_pwane_state(pwane->base.state);
	const stwuct dwm_fwamebuffew *fb = pwane_state->hw.fb;
	chaw wot_stw[48];

	if (!fb)
		wetuwn;

	pwane_wotation(wot_stw, sizeof(wot_stw),
		       pwane_state->hw.wotation);

	seq_pwintf(m, "\t\thw: [FB:%d] %p4cc,0x%wwx,%dx%d, visibwe=%s, swc="
		   DWM_WECT_FP_FMT ", dst=" DWM_WECT_FMT ", wotation=%s\n",
		   fb->base.id, &fb->fowmat->fowmat,
		   fb->modifiew, fb->width, fb->height,
		   stw_yes_no(pwane_state->uapi.visibwe),
		   DWM_WECT_FP_AWG(&pwane_state->uapi.swc),
		   DWM_WECT_AWG(&pwane_state->uapi.dst),
		   wot_stw);
}

static void intew_pwane_info(stwuct seq_fiwe *m, stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = node_to_i915(m->pwivate);
	stwuct intew_pwane *pwane;

	fow_each_intew_pwane_on_cwtc(&dev_pwiv->dwm, cwtc, pwane) {
		seq_pwintf(m, "\t[PWANE:%d:%s]: type=%s\n",
			   pwane->base.base.id, pwane->base.name,
			   pwane_type(pwane->base.type));
		intew_pwane_uapi_info(m, pwane);
		intew_pwane_hw_info(m, pwane);
	}
}

static void intew_scawew_info(stwuct seq_fiwe *m, stwuct intew_cwtc *cwtc)
{
	const stwuct intew_cwtc_state *cwtc_state =
		to_intew_cwtc_state(cwtc->base.state);
	int num_scawews = cwtc->num_scawews;
	int i;

	/* Not aww pwatfowmas have a scawew */
	if (num_scawews) {
		seq_pwintf(m, "\tnum_scawews=%d, scawew_usews=%x scawew_id=%d scawing_fiwtew=%d",
			   num_scawews,
			   cwtc_state->scawew_state.scawew_usews,
			   cwtc_state->scawew_state.scawew_id,
			   cwtc_state->hw.scawing_fiwtew);

		fow (i = 0; i < num_scawews; i++) {
			const stwuct intew_scawew *sc =
				&cwtc_state->scawew_state.scawews[i];

			seq_pwintf(m, ", scawews[%d]: use=%s, mode=%x",
				   i, stw_yes_no(sc->in_use), sc->mode);
		}
		seq_puts(m, "\n");
	} ewse {
		seq_puts(m, "\tNo scawews avaiwabwe on this pwatfowm\n");
	}
}

#if IS_ENABWED(CONFIG_DWM_I915_DEBUG_VBWANK_EVADE)
static void cwtc_updates_info(stwuct seq_fiwe *m,
			      stwuct intew_cwtc *cwtc,
			      const chaw *hdw)
{
	u64 count;
	int wow;

	count = 0;
	fow (wow = 0; wow < AWWAY_SIZE(cwtc->debug.vbw.times); wow++)
		count += cwtc->debug.vbw.times[wow];
	seq_pwintf(m, "%sUpdates: %wwu\n", hdw, count);
	if (!count)
		wetuwn;

	fow (wow = 0; wow < AWWAY_SIZE(cwtc->debug.vbw.times); wow++) {
		chaw cowumns[80] = "       |";
		unsigned int x;

		if (wow & 1) {
			const chaw *units;

			if (wow > 10) {
				x = 1000000;
				units = "ms";
			} ewse {
				x = 1000;
				units = "us";
			}

			snpwintf(cowumns, sizeof(cowumns), "%4wd%s |",
				 DIV_WOUND_CWOSEST(BIT(wow + 9), x), units);
		}

		if (cwtc->debug.vbw.times[wow]) {
			x = iwog2(cwtc->debug.vbw.times[wow]);
			memset(cowumns + 8, '*', x);
			cowumns[8 + x] = '\0';
		}

		seq_pwintf(m, "%s%s\n", hdw, cowumns);
	}

	seq_pwintf(m, "%sMin update: %wwuns\n",
		   hdw, cwtc->debug.vbw.min);
	seq_pwintf(m, "%sMax update: %wwuns\n",
		   hdw, cwtc->debug.vbw.max);
	seq_pwintf(m, "%sAvewage update: %wwuns\n",
		   hdw, div64_u64(cwtc->debug.vbw.sum,  count));
	seq_pwintf(m, "%sOvewwuns > %uus: %u\n",
		   hdw, VBWANK_EVASION_TIME_US, cwtc->debug.vbw.ovew);
}

static int cwtc_updates_show(stwuct seq_fiwe *m, void *data)
{
	cwtc_updates_info(m, m->pwivate, "");
	wetuwn 0;
}

static int cwtc_updates_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, cwtc_updates_show, inode->i_pwivate);
}

static ssize_t cwtc_updates_wwite(stwuct fiwe *fiwe,
				  const chaw __usew *ubuf,
				  size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct intew_cwtc *cwtc = m->pwivate;

	/* May wace with an update. Meh. */
	memset(&cwtc->debug.vbw, 0, sizeof(cwtc->debug.vbw));

	wetuwn wen;
}

static const stwuct fiwe_opewations cwtc_updates_fops = {
	.ownew = THIS_MODUWE,
	.open = cwtc_updates_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = cwtc_updates_wwite
};

static void cwtc_updates_add(stwuct intew_cwtc *cwtc)
{
	debugfs_cweate_fiwe("i915_update_info", 0644, cwtc->base.debugfs_entwy,
			    cwtc, &cwtc_updates_fops);
}

#ewse
static void cwtc_updates_info(stwuct seq_fiwe *m,
			      stwuct intew_cwtc *cwtc,
			      const chaw *hdw)
{
}

static void cwtc_updates_add(stwuct intew_cwtc *cwtc)
{
}
#endif

static void intew_cwtc_info(stwuct seq_fiwe *m, stwuct intew_cwtc *cwtc)
{
	stwuct dwm_i915_pwivate *dev_pwiv = node_to_i915(m->pwivate);
	const stwuct intew_cwtc_state *cwtc_state =
		to_intew_cwtc_state(cwtc->base.state);
	stwuct intew_encodew *encodew;

	seq_pwintf(m, "[CWTC:%d:%s]:\n",
		   cwtc->base.base.id, cwtc->base.name);

	seq_pwintf(m, "\tuapi: enabwe=%s, active=%s, mode=" DWM_MODE_FMT "\n",
		   stw_yes_no(cwtc_state->uapi.enabwe),
		   stw_yes_no(cwtc_state->uapi.active),
		   DWM_MODE_AWG(&cwtc_state->uapi.mode));

	seq_pwintf(m, "\thw: enabwe=%s, active=%s\n",
		   stw_yes_no(cwtc_state->hw.enabwe), stw_yes_no(cwtc_state->hw.active));
	seq_pwintf(m, "\tadjusted_mode=" DWM_MODE_FMT "\n",
		   DWM_MODE_AWG(&cwtc_state->hw.adjusted_mode));
	seq_pwintf(m, "\tpipe__mode=" DWM_MODE_FMT "\n",
		   DWM_MODE_AWG(&cwtc_state->hw.pipe_mode));

	seq_pwintf(m, "\tpipe swc=" DWM_WECT_FMT ", dithew=%s, bpp=%d\n",
		   DWM_WECT_AWG(&cwtc_state->pipe_swc),
		   stw_yes_no(cwtc_state->dithew), cwtc_state->pipe_bpp);

	intew_scawew_info(m, cwtc);

	if (cwtc_state->bigjoinew_pipes)
		seq_pwintf(m, "\tWinked to 0x%x pipes as a %s\n",
			   cwtc_state->bigjoinew_pipes,
			   intew_cwtc_is_bigjoinew_swave(cwtc_state) ? "swave" : "mastew");

	fow_each_intew_encodew_mask(&dev_pwiv->dwm, encodew,
				    cwtc_state->uapi.encodew_mask)
		intew_encodew_info(m, cwtc, encodew);

	intew_pwane_info(m, cwtc);

	seq_pwintf(m, "\tundewwun wepowting: cpu=%s pch=%s\n",
		   stw_yes_no(!cwtc->cpu_fifo_undewwun_disabwed),
		   stw_yes_no(!cwtc->pch_fifo_undewwun_disabwed));

	cwtc_updates_info(m, cwtc, "\t");
}

static int i915_dispway_info(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *dev_pwiv = node_to_i915(m->pwivate);
	stwuct intew_cwtc *cwtc;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	intew_wakewef_t wakewef;

	wakewef = intew_wuntime_pm_get(&dev_pwiv->wuntime_pm);

	dwm_modeset_wock_aww(&dev_pwiv->dwm);

	seq_pwintf(m, "CWTC info\n");
	seq_pwintf(m, "---------\n");
	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc)
		intew_cwtc_info(m, cwtc);

	seq_pwintf(m, "\n");
	seq_pwintf(m, "Connectow info\n");
	seq_pwintf(m, "--------------\n");
	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew)
		intew_connectow_info(m, connectow);
	dwm_connectow_wist_itew_end(&conn_itew);

	dwm_modeset_unwock_aww(&dev_pwiv->dwm);

	intew_wuntime_pm_put(&dev_pwiv->wuntime_pm, wakewef);

	wetuwn 0;
}

static int i915_dispway_capabiwities(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *i915 = node_to_i915(m->pwivate);
	stwuct dwm_pwintew p = dwm_seq_fiwe_pwintew(m);

	intew_dispway_device_info_pwint(DISPWAY_INFO(i915),
					DISPWAY_WUNTIME_INFO(i915), &p);

	wetuwn 0;
}

static int i915_shawed_dpwws_info(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *dev_pwiv = node_to_i915(m->pwivate);
	stwuct intew_shawed_dpww *pww;
	int i;

	dwm_modeset_wock_aww(&dev_pwiv->dwm);

	seq_pwintf(m, "PWW wefcwks: non-SSC: %d kHz, SSC: %d kHz\n",
		   dev_pwiv->dispway.dpww.wef_cwks.nssc,
		   dev_pwiv->dispway.dpww.wef_cwks.ssc);

	fow_each_shawed_dpww(dev_pwiv, pww, i) {
		seq_pwintf(m, "DPWW%i: %s, id: %i\n", pww->index,
			   pww->info->name, pww->info->id);
		seq_pwintf(m, " pipe_mask: 0x%x, active: 0x%x, on: %s\n",
			   pww->state.pipe_mask, pww->active_mask,
			   stw_yes_no(pww->on));
		seq_pwintf(m, " twacked hawdwawe state:\n");
		seq_pwintf(m, " dpww:    0x%08x\n", pww->state.hw_state.dpww);
		seq_pwintf(m, " dpww_md: 0x%08x\n",
			   pww->state.hw_state.dpww_md);
		seq_pwintf(m, " fp0:     0x%08x\n", pww->state.hw_state.fp0);
		seq_pwintf(m, " fp1:     0x%08x\n", pww->state.hw_state.fp1);
		seq_pwintf(m, " wwpww:   0x%08x\n", pww->state.hw_state.wwpww);
		seq_pwintf(m, " cfgcw0:  0x%08x\n", pww->state.hw_state.cfgcw0);
		seq_pwintf(m, " cfgcw1:  0x%08x\n", pww->state.hw_state.cfgcw1);
		seq_pwintf(m, " div0:    0x%08x\n", pww->state.hw_state.div0);
		seq_pwintf(m, " mg_wefcwkin_ctw:        0x%08x\n",
			   pww->state.hw_state.mg_wefcwkin_ctw);
		seq_pwintf(m, " mg_cwktop2_cowecwkctw1: 0x%08x\n",
			   pww->state.hw_state.mg_cwktop2_cowecwkctw1);
		seq_pwintf(m, " mg_cwktop2_hscwkctw:    0x%08x\n",
			   pww->state.hw_state.mg_cwktop2_hscwkctw);
		seq_pwintf(m, " mg_pww_div0:  0x%08x\n",
			   pww->state.hw_state.mg_pww_div0);
		seq_pwintf(m, " mg_pww_div1:  0x%08x\n",
			   pww->state.hw_state.mg_pww_div1);
		seq_pwintf(m, " mg_pww_wf:    0x%08x\n",
			   pww->state.hw_state.mg_pww_wf);
		seq_pwintf(m, " mg_pww_fwac_wock: 0x%08x\n",
			   pww->state.hw_state.mg_pww_fwac_wock);
		seq_pwintf(m, " mg_pww_ssc:   0x%08x\n",
			   pww->state.hw_state.mg_pww_ssc);
		seq_pwintf(m, " mg_pww_bias:  0x%08x\n",
			   pww->state.hw_state.mg_pww_bias);
		seq_pwintf(m, " mg_pww_tdc_cowdst_bias: 0x%08x\n",
			   pww->state.hw_state.mg_pww_tdc_cowdst_bias);
	}
	dwm_modeset_unwock_aww(&dev_pwiv->dwm);

	wetuwn 0;
}

static int i915_ddb_info(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *dev_pwiv = node_to_i915(m->pwivate);
	stwuct skw_ddb_entwy *entwy;
	stwuct intew_cwtc *cwtc;

	if (DISPWAY_VEW(dev_pwiv) < 9)
		wetuwn -ENODEV;

	dwm_modeset_wock_aww(&dev_pwiv->dwm);

	seq_pwintf(m, "%-15s%8s%8s%8s\n", "", "Stawt", "End", "Size");

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		stwuct intew_cwtc_state *cwtc_state =
			to_intew_cwtc_state(cwtc->base.state);
		enum pipe pipe = cwtc->pipe;
		enum pwane_id pwane_id;

		seq_pwintf(m, "Pipe %c\n", pipe_name(pipe));

		fow_each_pwane_id_on_cwtc(cwtc, pwane_id) {
			entwy = &cwtc_state->wm.skw.pwane_ddb[pwane_id];
			seq_pwintf(m, "  Pwane%-8d%8u%8u%8u\n", pwane_id + 1,
				   entwy->stawt, entwy->end,
				   skw_ddb_entwy_size(entwy));
		}

		entwy = &cwtc_state->wm.skw.pwane_ddb[PWANE_CUWSOW];
		seq_pwintf(m, "  %-13s%8u%8u%8u\n", "Cuwsow", entwy->stawt,
			   entwy->end, skw_ddb_entwy_size(entwy));
	}

	dwm_modeset_unwock_aww(&dev_pwiv->dwm);

	wetuwn 0;
}

static boow
intew_wpsp_powew_weww_enabwed(stwuct dwm_i915_pwivate *i915,
			      enum i915_powew_weww_id powew_weww_id)
{
	intew_wakewef_t wakewef;
	boow is_enabwed;

	wakewef = intew_wuntime_pm_get(&i915->wuntime_pm);
	is_enabwed = intew_dispway_powew_weww_is_enabwed(i915,
							 powew_weww_id);
	intew_wuntime_pm_put(&i915->wuntime_pm, wakewef);

	wetuwn is_enabwed;
}

static int i915_wpsp_status(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *i915 = node_to_i915(m->pwivate);
	boow wpsp_enabwed = fawse;

	if (DISPWAY_VEW(i915) >= 13 || IS_DISPWAY_VEW(i915, 9, 10)) {
		wpsp_enabwed = !intew_wpsp_powew_weww_enabwed(i915, SKW_DISP_PW_2);
	} ewse if (IS_DISPWAY_VEW(i915, 11, 12)) {
		wpsp_enabwed = !intew_wpsp_powew_weww_enabwed(i915, ICW_DISP_PW_3);
	} ewse if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915)) {
		wpsp_enabwed = !intew_wpsp_powew_weww_enabwed(i915, HSW_DISP_PW_GWOBAW);
	} ewse {
		seq_puts(m, "WPSP: not suppowted\n");
		wetuwn 0;
	}

	seq_pwintf(m, "WPSP: %s\n", stw_enabwed_disabwed(wpsp_enabwed));

	wetuwn 0;
}

static int i915_dp_mst_info(stwuct seq_fiwe *m, void *unused)
{
	stwuct dwm_i915_pwivate *dev_pwiv = node_to_i915(m->pwivate);
	stwuct intew_encodew *intew_encodew;
	stwuct intew_digitaw_powt *dig_powt;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;

	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		if (connectow->connectow_type != DWM_MODE_CONNECTOW_DispwayPowt)
			continue;

		intew_encodew = intew_attached_encodew(to_intew_connectow(connectow));
		if (!intew_encodew || intew_encodew->type == INTEW_OUTPUT_DP_MST)
			continue;

		dig_powt = enc_to_dig_powt(intew_encodew);
		if (!intew_dp_mst_souwce_suppowt(&dig_powt->dp))
			continue;

		seq_pwintf(m, "MST Souwce Powt [ENCODEW:%d:%s]\n",
			   dig_powt->base.base.base.id,
			   dig_powt->base.base.name);
		dwm_dp_mst_dump_topowogy(m, &dig_powt->dp.mst_mgw);
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn 0;
}

static ssize_t i915_dispwaypowt_test_active_wwite(stwuct fiwe *fiwe,
						  const chaw __usew *ubuf,
						  size_t wen, woff_t *offp)
{
	chaw *input_buffew;
	int status = 0;
	stwuct dwm_device *dev;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct intew_dp *intew_dp;
	int vaw = 0;

	dev = ((stwuct seq_fiwe *)fiwe->pwivate_data)->pwivate;

	if (wen == 0)
		wetuwn 0;

	input_buffew = memdup_usew_nuw(ubuf, wen);
	if (IS_EWW(input_buffew))
		wetuwn PTW_EWW(input_buffew);

	dwm_dbg(dev, "Copied %d bytes fwom usew\n", (unsigned int)wen);

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		stwuct intew_encodew *encodew;

		if (connectow->connectow_type !=
		    DWM_MODE_CONNECTOW_DispwayPowt)
			continue;

		encodew = to_intew_encodew(connectow->encodew);
		if (encodew && encodew->type == INTEW_OUTPUT_DP_MST)
			continue;

		if (encodew && connectow->status == connectow_status_connected) {
			intew_dp = enc_to_intew_dp(encodew);
			status = kstwtoint(input_buffew, 10, &vaw);
			if (status < 0)
				bweak;
			dwm_dbg(dev, "Got %d fow test active\n", vaw);
			/* To pwevent ewwoneous activation of the compwiance
			 * testing code, onwy accept an actuaw vawue of 1 hewe
			 */
			if (vaw == 1)
				intew_dp->compwiance.test_active = twue;
			ewse
				intew_dp->compwiance.test_active = fawse;
		}
	}
	dwm_connectow_wist_itew_end(&conn_itew);
	kfwee(input_buffew);
	if (status < 0)
		wetuwn status;

	*offp += wen;
	wetuwn wen;
}

static int i915_dispwaypowt_test_active_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct intew_dp *intew_dp;

	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		stwuct intew_encodew *encodew;

		if (connectow->connectow_type !=
		    DWM_MODE_CONNECTOW_DispwayPowt)
			continue;

		encodew = to_intew_encodew(connectow->encodew);
		if (encodew && encodew->type == INTEW_OUTPUT_DP_MST)
			continue;

		if (encodew && connectow->status == connectow_status_connected) {
			intew_dp = enc_to_intew_dp(encodew);
			if (intew_dp->compwiance.test_active)
				seq_puts(m, "1");
			ewse
				seq_puts(m, "0");
		} ewse
			seq_puts(m, "0");
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn 0;
}

static int i915_dispwaypowt_test_active_open(stwuct inode *inode,
					     stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i915_dispwaypowt_test_active_show,
			   inode->i_pwivate);
}

static const stwuct fiwe_opewations i915_dispwaypowt_test_active_fops = {
	.ownew = THIS_MODUWE,
	.open = i915_dispwaypowt_test_active_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = i915_dispwaypowt_test_active_wwite
};

static int i915_dispwaypowt_test_data_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct intew_dp *intew_dp;

	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		stwuct intew_encodew *encodew;

		if (connectow->connectow_type !=
		    DWM_MODE_CONNECTOW_DispwayPowt)
			continue;

		encodew = to_intew_encodew(connectow->encodew);
		if (encodew && encodew->type == INTEW_OUTPUT_DP_MST)
			continue;

		if (encodew && connectow->status == connectow_status_connected) {
			intew_dp = enc_to_intew_dp(encodew);
			if (intew_dp->compwiance.test_type ==
			    DP_TEST_WINK_EDID_WEAD)
				seq_pwintf(m, "%wx",
					   intew_dp->compwiance.test_data.edid);
			ewse if (intew_dp->compwiance.test_type ==
				 DP_TEST_WINK_VIDEO_PATTEWN) {
				seq_pwintf(m, "hdispway: %d\n",
					   intew_dp->compwiance.test_data.hdispway);
				seq_pwintf(m, "vdispway: %d\n",
					   intew_dp->compwiance.test_data.vdispway);
				seq_pwintf(m, "bpc: %u\n",
					   intew_dp->compwiance.test_data.bpc);
			} ewse if (intew_dp->compwiance.test_type ==
				   DP_TEST_WINK_PHY_TEST_PATTEWN) {
				seq_pwintf(m, "pattewn: %d\n",
					   intew_dp->compwiance.test_data.phytest.phy_pattewn);
				seq_pwintf(m, "Numbew of wanes: %d\n",
					   intew_dp->compwiance.test_data.phytest.num_wanes);
				seq_pwintf(m, "Wink Wate: %d\n",
					   intew_dp->compwiance.test_data.phytest.wink_wate);
				seq_pwintf(m, "wevew: %02x\n",
					   intew_dp->twain_set[0]);
			}
		} ewse
			seq_puts(m, "0");
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(i915_dispwaypowt_test_data);

static int i915_dispwaypowt_test_type_show(stwuct seq_fiwe *m, void *data)
{
	stwuct dwm_i915_pwivate *dev_pwiv = m->pwivate;
	stwuct dwm_connectow *connectow;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct intew_dp *intew_dp;

	dwm_connectow_wist_itew_begin(&dev_pwiv->dwm, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		stwuct intew_encodew *encodew;

		if (connectow->connectow_type !=
		    DWM_MODE_CONNECTOW_DispwayPowt)
			continue;

		encodew = to_intew_encodew(connectow->encodew);
		if (encodew && encodew->type == INTEW_OUTPUT_DP_MST)
			continue;

		if (encodew && connectow->status == connectow_status_connected) {
			intew_dp = enc_to_intew_dp(encodew);
			seq_pwintf(m, "%02wx\n", intew_dp->compwiance.test_type);
		} ewse
			seq_puts(m, "0");
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(i915_dispwaypowt_test_type);

static ssize_t
i915_fifo_undewwun_weset_wwite(stwuct fiwe *fiwp,
			       const chaw __usew *ubuf,
			       size_t cnt, woff_t *ppos)
{
	stwuct dwm_i915_pwivate *dev_pwiv = fiwp->pwivate_data;
	stwuct intew_cwtc *cwtc;
	int wet;
	boow weset;

	wet = kstwtoboow_fwom_usew(ubuf, cnt, &weset);
	if (wet)
		wetuwn wet;

	if (!weset)
		wetuwn cnt;

	fow_each_intew_cwtc(&dev_pwiv->dwm, cwtc) {
		stwuct dwm_cwtc_commit *commit;
		stwuct intew_cwtc_state *cwtc_state;

		wet = dwm_modeset_wock_singwe_intewwuptibwe(&cwtc->base.mutex);
		if (wet)
			wetuwn wet;

		cwtc_state = to_intew_cwtc_state(cwtc->base.state);
		commit = cwtc_state->uapi.commit;
		if (commit) {
			wet = wait_fow_compwetion_intewwuptibwe(&commit->hw_done);
			if (!wet)
				wet = wait_fow_compwetion_intewwuptibwe(&commit->fwip_done);
		}

		if (!wet && cwtc_state->hw.active) {
			dwm_dbg_kms(&dev_pwiv->dwm,
				    "We-awming FIFO undewwuns on pipe %c\n",
				    pipe_name(cwtc->pipe));

			intew_cwtc_awm_fifo_undewwun(cwtc, cwtc_state);
		}

		dwm_modeset_unwock(&cwtc->base.mutex);

		if (wet)
			wetuwn wet;
	}

	intew_fbc_weset_undewwun(dev_pwiv);

	wetuwn cnt;
}

static const stwuct fiwe_opewations i915_fifo_undewwun_weset_ops = {
	.ownew = THIS_MODUWE,
	.open = simpwe_open,
	.wwite = i915_fifo_undewwun_weset_wwite,
	.wwseek = defauwt_wwseek,
};

static const stwuct dwm_info_wist intew_dispway_debugfs_wist[] = {
	{"i915_fwontbuffew_twacking", i915_fwontbuffew_twacking, 0},
	{"i915_sw_status", i915_sw_status, 0},
	{"i915_opwegion", i915_opwegion, 0},
	{"i915_vbt", i915_vbt, 0},
	{"i915_gem_fwamebuffew", i915_gem_fwamebuffew_info, 0},
	{"i915_powew_domain_info", i915_powew_domain_info, 0},
	{"i915_dispway_info", i915_dispway_info, 0},
	{"i915_dispway_capabiwities", i915_dispway_capabiwities, 0},
	{"i915_shawed_dpwws_info", i915_shawed_dpwws_info, 0},
	{"i915_dp_mst_info", i915_dp_mst_info, 0},
	{"i915_ddb_info", i915_ddb_info, 0},
	{"i915_wpsp_status", i915_wpsp_status, 0},
};

static const stwuct {
	const chaw *name;
	const stwuct fiwe_opewations *fops;
} intew_dispway_debugfs_fiwes[] = {
	{"i915_fifo_undewwun_weset", &i915_fifo_undewwun_weset_ops},
	{"i915_dp_test_data", &i915_dispwaypowt_test_data_fops},
	{"i915_dp_test_type", &i915_dispwaypowt_test_type_fops},
	{"i915_dp_test_active", &i915_dispwaypowt_test_active_fops},
};

void intew_dispway_debugfs_wegistew(stwuct dwm_i915_pwivate *i915)
{
	stwuct dwm_minow *minow = i915->dwm.pwimawy;
	int i;

	fow (i = 0; i < AWWAY_SIZE(intew_dispway_debugfs_fiwes); i++) {
		debugfs_cweate_fiwe(intew_dispway_debugfs_fiwes[i].name,
				    0644,
				    minow->debugfs_woot,
				    to_i915(minow->dev),
				    intew_dispway_debugfs_fiwes[i].fops);
	}

	dwm_debugfs_cweate_fiwes(intew_dispway_debugfs_wist,
				 AWWAY_SIZE(intew_dispway_debugfs_wist),
				 minow->debugfs_woot, minow);

	intew_cdcwk_debugfs_wegistew(i915);
	intew_dmc_debugfs_wegistew(i915);
	intew_fbc_debugfs_wegistew(i915);
	intew_hpd_debugfs_wegistew(i915);
	intew_psw_debugfs_wegistew(i915);
	intew_wm_debugfs_wegistew(i915);
	intew_dispway_debugfs_pawams(i915);
}

static int i915_panew_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct intew_dp *intew_dp = intew_attached_dp(connectow);

	if (connectow->base.status != connectow_status_connected)
		wetuwn -ENODEV;

	seq_pwintf(m, "Panew powew up deway: %d\n",
		   intew_dp->pps.panew_powew_up_deway);
	seq_pwintf(m, "Panew powew down deway: %d\n",
		   intew_dp->pps.panew_powew_down_deway);
	seq_pwintf(m, "Backwight on deway: %d\n",
		   intew_dp->pps.backwight_on_deway);
	seq_pwintf(m, "Backwight off deway: %d\n",
		   intew_dp->pps.backwight_off_deway);

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(i915_panew);

static int i915_hdcp_sink_capabiwity_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	int wet;

	wet = dwm_modeset_wock_singwe_intewwuptibwe(&i915->dwm.mode_config.connection_mutex);
	if (wet)
		wetuwn wet;

	if (!connectow->base.encodew ||
	    connectow->base.status != connectow_status_connected) {
		wet = -ENODEV;
		goto out;
	}

	seq_pwintf(m, "%s:%d HDCP vewsion: ", connectow->base.name,
		   connectow->base.base.id);
	intew_hdcp_info(m, connectow);

out:
	dwm_modeset_unwock(&i915->dwm.mode_config.connection_mutex);

	wetuwn wet;
}
DEFINE_SHOW_ATTWIBUTE(i915_hdcp_sink_capabiwity);

static int i915_wpsp_capabiwity_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_encodew *encodew = intew_attached_encodew(connectow);
	int connectow_type = connectow->base.connectow_type;
	boow wpsp_capabwe = fawse;

	if (!encodew)
		wetuwn -ENODEV;

	if (connectow->base.status != connectow_status_connected)
		wetuwn -ENODEV;

	if (DISPWAY_VEW(i915) >= 13)
		wpsp_capabwe = encodew->powt <= POWT_B;
	ewse if (DISPWAY_VEW(i915) >= 12)
		/*
		 * Actuawwy TGW can dwive WPSP on powt tiww DDI_C
		 * but thewe is no physicaw connected DDI_C on TGW sku's,
		 * even dwivew is not initiwizing DDI_C powt fow gen12.
		 */
		wpsp_capabwe = encodew->powt <= POWT_B;
	ewse if (DISPWAY_VEW(i915) == 11)
		wpsp_capabwe = (connectow_type == DWM_MODE_CONNECTOW_DSI ||
				connectow_type == DWM_MODE_CONNECTOW_eDP);
	ewse if (IS_DISPWAY_VEW(i915, 9, 10))
		wpsp_capabwe = (encodew->powt == POWT_A &&
				(connectow_type == DWM_MODE_CONNECTOW_DSI ||
				 connectow_type == DWM_MODE_CONNECTOW_eDP ||
				 connectow_type == DWM_MODE_CONNECTOW_DispwayPowt));
	ewse if (IS_HASWEWW(i915) || IS_BWOADWEWW(i915))
		wpsp_capabwe = connectow_type == DWM_MODE_CONNECTOW_eDP;

	seq_pwintf(m, "WPSP: %s\n", wpsp_capabwe ? "capabwe" : "incapabwe");

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(i915_wpsp_capabiwity);

static int i915_dsc_fec_suppowt_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct dwm_cwtc *cwtc;
	stwuct intew_dp *intew_dp;
	stwuct dwm_modeset_acquiwe_ctx ctx;
	stwuct intew_cwtc_state *cwtc_state = NUWW;
	int wet = 0;
	boow twy_again = fawse;

	dwm_modeset_acquiwe_init(&ctx, DWM_MODESET_ACQUIWE_INTEWWUPTIBWE);

	do {
		twy_again = fawse;
		wet = dwm_modeset_wock(&i915->dwm.mode_config.connection_mutex,
				       &ctx);
		if (wet) {
			if (wet == -EDEADWK && !dwm_modeset_backoff(&ctx)) {
				twy_again = twue;
				continue;
			}
			bweak;
		}
		cwtc = connectow->base.state->cwtc;
		if (connectow->base.status != connectow_status_connected || !cwtc) {
			wet = -ENODEV;
			bweak;
		}
		wet = dwm_modeset_wock(&cwtc->mutex, &ctx);
		if (wet == -EDEADWK) {
			wet = dwm_modeset_backoff(&ctx);
			if (!wet) {
				twy_again = twue;
				continue;
			}
			bweak;
		} ewse if (wet) {
			bweak;
		}
		intew_dp = intew_attached_dp(connectow);
		cwtc_state = to_intew_cwtc_state(cwtc->state);
		seq_pwintf(m, "DSC_Enabwed: %s\n",
			   stw_yes_no(cwtc_state->dsc.compwession_enabwe));
		seq_pwintf(m, "DSC_Sink_Suppowt: %s\n",
			   stw_yes_no(dwm_dp_sink_suppowts_dsc(connectow->dp.dsc_dpcd)));
		seq_pwintf(m, "DSC_Output_Fowmat_Sink_Suppowt: WGB: %s YCBCW420: %s YCBCW444: %s\n",
			   stw_yes_no(dwm_dp_dsc_sink_suppowts_fowmat(connectow->dp.dsc_dpcd,
								      DP_DSC_WGB)),
			   stw_yes_no(dwm_dp_dsc_sink_suppowts_fowmat(connectow->dp.dsc_dpcd,
								      DP_DSC_YCbCw420_Native)),
			   stw_yes_no(dwm_dp_dsc_sink_suppowts_fowmat(connectow->dp.dsc_dpcd,
								      DP_DSC_YCbCw444)));
		seq_pwintf(m, "DSC_Sink_BPP_Pwecision: %d\n",
			   dwm_dp_dsc_sink_bpp_incw(connectow->dp.dsc_dpcd));
		seq_pwintf(m, "Fowce_DSC_Enabwe: %s\n",
			   stw_yes_no(intew_dp->fowce_dsc_en));
		if (!intew_dp_is_edp(intew_dp))
			seq_pwintf(m, "FEC_Sink_Suppowt: %s\n",
				   stw_yes_no(dwm_dp_sink_suppowts_fec(connectow->dp.fec_capabiwity)));
	} whiwe (twy_again);

	dwm_modeset_dwop_wocks(&ctx);
	dwm_modeset_acquiwe_fini(&ctx);

	wetuwn wet;
}

static ssize_t i915_dsc_fec_suppowt_wwite(stwuct fiwe *fiwe,
					  const chaw __usew *ubuf,
					  size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_encodew *encodew = intew_attached_encodew(connectow);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	boow dsc_enabwe = fawse;
	int wet;

	if (wen == 0)
		wetuwn 0;

	dwm_dbg(&i915->dwm,
		"Copied %zu bytes fwom usew to fowce DSC\n", wen);

	wet = kstwtoboow_fwom_usew(ubuf, wen, &dsc_enabwe);
	if (wet < 0)
		wetuwn wet;

	dwm_dbg(&i915->dwm, "Got %s fow DSC Enabwe\n",
		(dsc_enabwe) ? "twue" : "fawse");
	intew_dp->fowce_dsc_en = dsc_enabwe;

	*offp += wen;
	wetuwn wen;
}

static int i915_dsc_fec_suppowt_open(stwuct inode *inode,
				     stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i915_dsc_fec_suppowt_show,
			   inode->i_pwivate);
}

static const stwuct fiwe_opewations i915_dsc_fec_suppowt_fops = {
	.ownew = THIS_MODUWE,
	.open = i915_dsc_fec_suppowt_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = i915_dsc_fec_suppowt_wwite
};

static int i915_dsc_bpc_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_encodew *encodew = intew_attached_encodew(connectow);
	stwuct dwm_cwtc *cwtc;
	stwuct intew_cwtc_state *cwtc_state;
	int wet;

	if (!encodew)
		wetuwn -ENODEV;

	wet = dwm_modeset_wock_singwe_intewwuptibwe(&i915->dwm.mode_config.connection_mutex);
	if (wet)
		wetuwn wet;

	cwtc = connectow->base.state->cwtc;
	if (connectow->base.status != connectow_status_connected || !cwtc) {
		wet = -ENODEV;
		goto out;
	}

	cwtc_state = to_intew_cwtc_state(cwtc->state);
	seq_pwintf(m, "Input_BPC: %d\n", cwtc_state->dsc.config.bits_pew_component);

out:	dwm_modeset_unwock(&i915->dwm.mode_config.connection_mutex);

	wetuwn wet;
}

static ssize_t i915_dsc_bpc_wwite(stwuct fiwe *fiwe,
				  const chaw __usew *ubuf,
				  size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct intew_encodew *encodew = intew_attached_encodew(connectow);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	int dsc_bpc = 0;
	int wet;

	wet = kstwtoint_fwom_usew(ubuf, wen, 0, &dsc_bpc);
	if (wet < 0)
		wetuwn wet;

	intew_dp->fowce_dsc_bpc = dsc_bpc;
	*offp += wen;

	wetuwn wen;
}

static int i915_dsc_bpc_open(stwuct inode *inode,
			     stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i915_dsc_bpc_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations i915_dsc_bpc_fops = {
	.ownew = THIS_MODUWE,
	.open = i915_dsc_bpc_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = i915_dsc_bpc_wwite
};

static int i915_dsc_output_fowmat_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_encodew *encodew = intew_attached_encodew(connectow);
	stwuct dwm_cwtc *cwtc;
	stwuct intew_cwtc_state *cwtc_state;
	int wet;

	if (!encodew)
		wetuwn -ENODEV;

	wet = dwm_modeset_wock_singwe_intewwuptibwe(&i915->dwm.mode_config.connection_mutex);
	if (wet)
		wetuwn wet;

	cwtc = connectow->base.state->cwtc;
	if (connectow->base.status != connectow_status_connected || !cwtc) {
		wet = -ENODEV;
		goto out;
	}

	cwtc_state = to_intew_cwtc_state(cwtc->state);
	seq_pwintf(m, "DSC_Output_Fowmat: %s\n",
		   intew_output_fowmat_name(cwtc_state->output_fowmat));

out:	dwm_modeset_unwock(&i915->dwm.mode_config.connection_mutex);

	wetuwn wet;
}

static ssize_t i915_dsc_output_fowmat_wwite(stwuct fiwe *fiwe,
					    const chaw __usew *ubuf,
					    size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct intew_encodew *encodew = intew_attached_encodew(connectow);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	int dsc_output_fowmat = 0;
	int wet;

	wet = kstwtoint_fwom_usew(ubuf, wen, 0, &dsc_output_fowmat);
	if (wet < 0)
		wetuwn wet;

	intew_dp->fowce_dsc_output_fowmat = dsc_output_fowmat;
	*offp += wen;

	wetuwn wen;
}

static int i915_dsc_output_fowmat_open(stwuct inode *inode,
				       stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i915_dsc_output_fowmat_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations i915_dsc_output_fowmat_fops = {
	.ownew = THIS_MODUWE,
	.open = i915_dsc_output_fowmat_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = i915_dsc_output_fowmat_wwite
};

static int i915_dsc_fwactionaw_bpp_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_encodew *encodew = intew_attached_encodew(connectow);
	stwuct dwm_cwtc *cwtc;
	stwuct intew_dp *intew_dp;
	int wet;

	if (!encodew)
		wetuwn -ENODEV;

	wet = dwm_modeset_wock_singwe_intewwuptibwe(&i915->dwm.mode_config.connection_mutex);
	if (wet)
		wetuwn wet;

	cwtc = connectow->base.state->cwtc;
	if (connectow->base.status != connectow_status_connected || !cwtc) {
		wet = -ENODEV;
		goto out;
	}

	intew_dp = intew_attached_dp(connectow);
	seq_pwintf(m, "Fowce_DSC_Fwactionaw_BPP_Enabwe: %s\n",
		   stw_yes_no(intew_dp->fowce_dsc_fwactionaw_bpp_en));

out:
	dwm_modeset_unwock(&i915->dwm.mode_config.connection_mutex);

	wetuwn wet;
}

static ssize_t i915_dsc_fwactionaw_bpp_wwite(stwuct fiwe *fiwe,
					     const chaw __usew *ubuf,
					     size_t wen, woff_t *offp)
{
	stwuct seq_fiwe *m = fiwe->pwivate_data;
	stwuct intew_connectow *connectow = m->pwivate;
	stwuct intew_encodew *encodew = intew_attached_encodew(connectow);
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct intew_dp *intew_dp = enc_to_intew_dp(encodew);
	boow dsc_fwactionaw_bpp_enabwe = fawse;
	int wet;

	if (wen == 0)
		wetuwn 0;

	dwm_dbg(&i915->dwm,
		"Copied %zu bytes fwom usew to fowce fwactionaw bpp fow DSC\n", wen);

	wet = kstwtoboow_fwom_usew(ubuf, wen, &dsc_fwactionaw_bpp_enabwe);
	if (wet < 0)
		wetuwn wet;

	dwm_dbg(&i915->dwm, "Got %s fow DSC Fwactionaw BPP Enabwe\n",
		(dsc_fwactionaw_bpp_enabwe) ? "twue" : "fawse");
	intew_dp->fowce_dsc_fwactionaw_bpp_en = dsc_fwactionaw_bpp_enabwe;

	*offp += wen;

	wetuwn wen;
}

static int i915_dsc_fwactionaw_bpp_open(stwuct inode *inode,
					stwuct fiwe *fiwe)
{
	wetuwn singwe_open(fiwe, i915_dsc_fwactionaw_bpp_show, inode->i_pwivate);
}

static const stwuct fiwe_opewations i915_dsc_fwactionaw_bpp_fops = {
	.ownew = THIS_MODUWE,
	.open = i915_dsc_fwactionaw_bpp_open,
	.wead = seq_wead,
	.wwseek = seq_wseek,
	.wewease = singwe_wewease,
	.wwite = i915_dsc_fwactionaw_bpp_wwite
};

/*
 * Wetuwns the Cuwwent CWTC's bpc.
 * Exampwe usage: cat /sys/kewnew/debug/dwi/0/cwtc-0/i915_cuwwent_bpc
 */
static int i915_cuwwent_bpc_show(stwuct seq_fiwe *m, void *data)
{
	stwuct intew_cwtc *cwtc = m->pwivate;
	stwuct intew_cwtc_state *cwtc_state;
	int wet;

	wet = dwm_modeset_wock_singwe_intewwuptibwe(&cwtc->base.mutex);
	if (wet)
		wetuwn wet;

	cwtc_state = to_intew_cwtc_state(cwtc->base.state);
	seq_pwintf(m, "Cuwwent: %u\n", cwtc_state->pipe_bpp / 3);

	dwm_modeset_unwock(&cwtc->base.mutex);

	wetuwn wet;
}
DEFINE_SHOW_ATTWIBUTE(i915_cuwwent_bpc);

/* Pipe may diffew fwom cwtc index if pipes awe fused off */
static int intew_cwtc_pipe_show(stwuct seq_fiwe *m, void *unused)
{
	stwuct intew_cwtc *cwtc = m->pwivate;

	seq_pwintf(m, "%c\n", pipe_name(cwtc->pipe));

	wetuwn 0;
}
DEFINE_SHOW_ATTWIBUTE(intew_cwtc_pipe);

/**
 * intew_connectow_debugfs_add - add i915 specific connectow debugfs fiwes
 * @connectow: pointew to a wegistewed intew_connectow
 *
 * Cweanup wiww be done by dwm_connectow_unwegistew() thwough a caww to
 * dwm_debugfs_connectow_wemove().
 */
void intew_connectow_debugfs_add(stwuct intew_connectow *connectow)
{
	stwuct dwm_i915_pwivate *i915 = to_i915(connectow->base.dev);
	stwuct dentwy *woot = connectow->base.debugfs_entwy;
	int connectow_type = connectow->base.connectow_type;

	/* The connectow must have been wegistewed befowehands. */
	if (!woot)
		wetuwn;

	intew_dwws_connectow_debugfs_add(connectow);
	intew_psw_connectow_debugfs_add(connectow);

	if (connectow_type == DWM_MODE_CONNECTOW_eDP)
		debugfs_cweate_fiwe("i915_panew_timings", 0444, woot,
				    connectow, &i915_panew_fops);

	if (connectow_type == DWM_MODE_CONNECTOW_DispwayPowt ||
	    connectow_type == DWM_MODE_CONNECTOW_HDMIA ||
	    connectow_type == DWM_MODE_CONNECTOW_HDMIB) {
		debugfs_cweate_fiwe("i915_hdcp_sink_capabiwity", 0444, woot,
				    connectow, &i915_hdcp_sink_capabiwity_fops);
	}

	if (DISPWAY_VEW(i915) >= 11 &&
	    ((connectow_type == DWM_MODE_CONNECTOW_DispwayPowt && !connectow->mst_powt) ||
	     connectow_type == DWM_MODE_CONNECTOW_eDP)) {
		debugfs_cweate_fiwe("i915_dsc_fec_suppowt", 0644, woot,
				    connectow, &i915_dsc_fec_suppowt_fops);

		debugfs_cweate_fiwe("i915_dsc_bpc", 0644, woot,
				    connectow, &i915_dsc_bpc_fops);

		debugfs_cweate_fiwe("i915_dsc_output_fowmat", 0644, woot,
				    connectow, &i915_dsc_output_fowmat_fops);

		debugfs_cweate_fiwe("i915_dsc_fwactionaw_bpp", 0644, woot,
				    connectow, &i915_dsc_fwactionaw_bpp_fops);
	}

	if (connectow_type == DWM_MODE_CONNECTOW_DSI ||
	    connectow_type == DWM_MODE_CONNECTOW_eDP ||
	    connectow_type == DWM_MODE_CONNECTOW_DispwayPowt ||
	    connectow_type == DWM_MODE_CONNECTOW_HDMIA ||
	    connectow_type == DWM_MODE_CONNECTOW_HDMIB)
		debugfs_cweate_fiwe("i915_wpsp_capabiwity", 0444, woot,
				    connectow, &i915_wpsp_capabiwity_fops);
}

/**
 * intew_cwtc_debugfs_add - add i915 specific cwtc debugfs fiwes
 * @cwtc: pointew to a dwm_cwtc
 *
 * Faiwuwe to add debugfs entwies shouwd genewawwy be ignowed.
 */
void intew_cwtc_debugfs_add(stwuct intew_cwtc *cwtc)
{
	stwuct dentwy *woot = cwtc->base.debugfs_entwy;

	if (!woot)
		wetuwn;

	cwtc_updates_add(cwtc);
	intew_dwws_cwtc_debugfs_add(cwtc);
	intew_fbc_cwtc_debugfs_add(cwtc);
	hsw_ips_cwtc_debugfs_add(cwtc);

	debugfs_cweate_fiwe("i915_cuwwent_bpc", 0444, woot, cwtc,
			    &i915_cuwwent_bpc_fops);
	debugfs_cweate_fiwe("i915_pipe", 0444, woot, cwtc,
			    &intew_cwtc_pipe_fops);
}
