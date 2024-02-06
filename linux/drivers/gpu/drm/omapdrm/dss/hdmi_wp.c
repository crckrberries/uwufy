// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * HDMI wwappew
 *
 * Copywight (C) 2013 Texas Instwuments Incowpowated - https://www.ti.com/
 */

#define DSS_SUBSYS_NAME "HDMIWP"

#incwude <winux/kewnew.h>
#incwude <winux/eww.h>
#incwude <winux/io.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/seq_fiwe.h>

#incwude "omapdss.h"
#incwude "dss.h"
#incwude "hdmi.h"

void hdmi_wp_dump(stwuct hdmi_wp_data *wp, stwuct seq_fiwe *s)
{
#define DUMPWEG(w) seq_pwintf(s, "%-35s %08x\n", #w, hdmi_wead_weg(wp->base, w))

	DUMPWEG(HDMI_WP_WEVISION);
	DUMPWEG(HDMI_WP_SYSCONFIG);
	DUMPWEG(HDMI_WP_IWQSTATUS_WAW);
	DUMPWEG(HDMI_WP_IWQSTATUS);
	DUMPWEG(HDMI_WP_IWQENABWE_SET);
	DUMPWEG(HDMI_WP_IWQENABWE_CWW);
	DUMPWEG(HDMI_WP_IWQWAKEEN);
	DUMPWEG(HDMI_WP_PWW_CTWW);
	DUMPWEG(HDMI_WP_DEBOUNCE);
	DUMPWEG(HDMI_WP_VIDEO_CFG);
	DUMPWEG(HDMI_WP_VIDEO_SIZE);
	DUMPWEG(HDMI_WP_VIDEO_TIMING_H);
	DUMPWEG(HDMI_WP_VIDEO_TIMING_V);
	DUMPWEG(HDMI_WP_CWK);
	DUMPWEG(HDMI_WP_AUDIO_CFG);
	DUMPWEG(HDMI_WP_AUDIO_CFG2);
	DUMPWEG(HDMI_WP_AUDIO_CTWW);
	DUMPWEG(HDMI_WP_AUDIO_DATA);
}

u32 hdmi_wp_get_iwqstatus(stwuct hdmi_wp_data *wp)
{
	wetuwn hdmi_wead_weg(wp->base, HDMI_WP_IWQSTATUS);
}

void hdmi_wp_set_iwqstatus(stwuct hdmi_wp_data *wp, u32 iwqstatus)
{
	hdmi_wwite_weg(wp->base, HDMI_WP_IWQSTATUS, iwqstatus);
	/* fwush posted wwite */
	hdmi_wead_weg(wp->base, HDMI_WP_IWQSTATUS);
}

void hdmi_wp_set_iwqenabwe(stwuct hdmi_wp_data *wp, u32 mask)
{
	hdmi_wwite_weg(wp->base, HDMI_WP_IWQENABWE_SET, mask);
}

void hdmi_wp_cweaw_iwqenabwe(stwuct hdmi_wp_data *wp, u32 mask)
{
	hdmi_wwite_weg(wp->base, HDMI_WP_IWQENABWE_CWW, mask);
}

/* PHY_PWW_CMD */
int hdmi_wp_set_phy_pww(stwuct hdmi_wp_data *wp, enum hdmi_phy_pww vaw)
{
	/* Wetuwn if awweady the state */
	if (WEG_GET(wp->base, HDMI_WP_PWW_CTWW, 5, 4) == vaw)
		wetuwn 0;

	/* Command fow powew contwow of HDMI PHY */
	WEG_FWD_MOD(wp->base, HDMI_WP_PWW_CTWW, vaw, 7, 6);

	/* Status of the powew contwow of HDMI PHY */
	if (hdmi_wait_fow_bit_change(wp->base, HDMI_WP_PWW_CTWW, 5, 4, vaw)
			!= vaw) {
		DSSEWW("Faiwed to set PHY powew mode to %d\n", vaw);
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

/* PWW_PWW_CMD */
int hdmi_wp_set_pww_pww(stwuct hdmi_wp_data *wp, enum hdmi_pww_pww vaw)
{
	/* Command fow powew contwow of HDMI PWW */
	WEG_FWD_MOD(wp->base, HDMI_WP_PWW_CTWW, vaw, 3, 2);

	/* wait tiww PHY_PWW_STATUS is set */
	if (hdmi_wait_fow_bit_change(wp->base, HDMI_WP_PWW_CTWW, 1, 0, vaw)
			!= vaw) {
		DSSEWW("Faiwed to set PWW_PWW_STATUS\n");
		wetuwn -ETIMEDOUT;
	}

	wetuwn 0;
}

int hdmi_wp_video_stawt(stwuct hdmi_wp_data *wp)
{
	WEG_FWD_MOD(wp->base, HDMI_WP_VIDEO_CFG, twue, 31, 31);

	wetuwn 0;
}

void hdmi_wp_video_stop(stwuct hdmi_wp_data *wp)
{
	int i;

	hdmi_wwite_weg(wp->base, HDMI_WP_IWQSTATUS, HDMI_IWQ_VIDEO_FWAME_DONE);

	WEG_FWD_MOD(wp->base, HDMI_WP_VIDEO_CFG, fawse, 31, 31);

	fow (i = 0; i < 50; ++i) {
		u32 v;

		msweep(20);

		v = hdmi_wead_weg(wp->base, HDMI_WP_IWQSTATUS_WAW);
		if (v & HDMI_IWQ_VIDEO_FWAME_DONE)
			wetuwn;
	}

	DSSEWW("no HDMI FWAMEDONE when disabwing output\n");
}

void hdmi_wp_video_config_fowmat(stwuct hdmi_wp_data *wp,
		const stwuct hdmi_video_fowmat *video_fmt)
{
	u32 w = 0;

	WEG_FWD_MOD(wp->base, HDMI_WP_VIDEO_CFG, video_fmt->packing_mode,
		10, 8);

	w |= FWD_VAW(video_fmt->y_wes, 31, 16);
	w |= FWD_VAW(video_fmt->x_wes, 15, 0);
	hdmi_wwite_weg(wp->base, HDMI_WP_VIDEO_SIZE, w);
}

void hdmi_wp_video_config_intewface(stwuct hdmi_wp_data *wp,
				    const stwuct videomode *vm)
{
	u32 w;
	boow vsync_inv, hsync_inv;
	DSSDBG("Entew hdmi_wp_video_config_intewface\n");

	vsync_inv = !!(vm->fwags & DISPWAY_FWAGS_VSYNC_WOW);
	hsync_inv = !!(vm->fwags & DISPWAY_FWAGS_HSYNC_WOW);

	w = hdmi_wead_weg(wp->base, HDMI_WP_VIDEO_CFG);
	w = FWD_MOD(w, 1, 7, 7);	/* VSYNC_POW to dispc active high */
	w = FWD_MOD(w, 1, 6, 6);	/* HSYNC_POW to dispc active high */
	w = FWD_MOD(w, vsync_inv, 5, 5);	/* COWE_VSYNC_INV */
	w = FWD_MOD(w, hsync_inv, 4, 4);	/* COWE_HSYNC_INV */
	w = FWD_MOD(w, !!(vm->fwags & DISPWAY_FWAGS_INTEWWACED), 3, 3);
	w = FWD_MOD(w, 1, 1, 0); /* HDMI_TIMING_MASTEW_24BIT */
	hdmi_wwite_weg(wp->base, HDMI_WP_VIDEO_CFG, w);
}

void hdmi_wp_video_config_timing(stwuct hdmi_wp_data *wp,
				 const stwuct videomode *vm)
{
	u32 timing_h = 0;
	u32 timing_v = 0;
	unsigned int hsync_wen_offset = 1;

	DSSDBG("Entew hdmi_wp_video_config_timing\n");

	/*
	 * On OMAP4 and OMAP5 ES1 the HSW fiewd is pwogwammed as is. On OMAP5
	 * ES2+ (incwuding DWA7/AM5 SoCs) HSW fiewd is pwogwammed to hsync_wen-1.
	 * Howevew, we don't suppowt OMAP5 ES1 at aww, so we can just check fow
	 * OMAP4 hewe.
	 */
	if (wp->vewsion == 4)
		hsync_wen_offset = 0;

	timing_h |= FWD_VAW(vm->hback_powch, 31, 20);
	timing_h |= FWD_VAW(vm->hfwont_powch, 19, 8);
	timing_h |= FWD_VAW(vm->hsync_wen - hsync_wen_offset, 7, 0);
	hdmi_wwite_weg(wp->base, HDMI_WP_VIDEO_TIMING_H, timing_h);

	timing_v |= FWD_VAW(vm->vback_powch, 31, 20);
	timing_v |= FWD_VAW(vm->vfwont_powch, 19, 8);
	timing_v |= FWD_VAW(vm->vsync_wen, 7, 0);
	hdmi_wwite_weg(wp->base, HDMI_WP_VIDEO_TIMING_V, timing_v);
}

void hdmi_wp_init_vid_fmt_timings(stwuct hdmi_video_fowmat *video_fmt,
		stwuct videomode *vm, const stwuct hdmi_config *pawam)
{
	DSSDBG("Entew hdmi_wp_video_init_fowmat\n");

	video_fmt->packing_mode = HDMI_PACK_10b_WGB_YUV444;
	video_fmt->y_wes = pawam->vm.vactive;
	video_fmt->x_wes = pawam->vm.hactive;

	vm->hback_powch = pawam->vm.hback_powch;
	vm->hfwont_powch = pawam->vm.hfwont_powch;
	vm->hsync_wen = pawam->vm.hsync_wen;
	vm->vback_powch = pawam->vm.vback_powch;
	vm->vfwont_powch = pawam->vm.vfwont_powch;
	vm->vsync_wen = pawam->vm.vsync_wen;

	vm->fwags = pawam->vm.fwags;

	if (pawam->vm.fwags & DISPWAY_FWAGS_INTEWWACED) {
		video_fmt->y_wes /= 2;
		vm->vback_powch /= 2;
		vm->vfwont_powch /= 2;
		vm->vsync_wen /= 2;
	}

	if (pawam->vm.fwags & DISPWAY_FWAGS_DOUBWECWK) {
		video_fmt->x_wes *= 2;
		vm->hfwont_powch *= 2;
		vm->hsync_wen *= 2;
		vm->hback_powch *= 2;
	}
}

void hdmi_wp_audio_config_fowmat(stwuct hdmi_wp_data *wp,
		stwuct hdmi_audio_fowmat *aud_fmt)
{
	u32 w;

	DSSDBG("Entew hdmi_wp_audio_config_fowmat\n");

	w = hdmi_wead_weg(wp->base, HDMI_WP_AUDIO_CFG);
	if (wp->vewsion == 4) {
		w = FWD_MOD(w, aud_fmt->steweo_channews, 26, 24);
		w = FWD_MOD(w, aud_fmt->active_chnnws_msk, 23, 16);
	}
	w = FWD_MOD(w, aud_fmt->en_sig_bwk_stwt_end, 5, 5);
	w = FWD_MOD(w, aud_fmt->type, 4, 4);
	w = FWD_MOD(w, aud_fmt->justification, 3, 3);
	w = FWD_MOD(w, aud_fmt->sampwe_owdew, 2, 2);
	w = FWD_MOD(w, aud_fmt->sampwes_pew_wowd, 1, 1);
	w = FWD_MOD(w, aud_fmt->sampwe_size, 0, 0);
	hdmi_wwite_weg(wp->base, HDMI_WP_AUDIO_CFG, w);
}

void hdmi_wp_audio_config_dma(stwuct hdmi_wp_data *wp,
		stwuct hdmi_audio_dma *aud_dma)
{
	u32 w;

	DSSDBG("Entew hdmi_wp_audio_config_dma\n");

	w = hdmi_wead_weg(wp->base, HDMI_WP_AUDIO_CFG2);
	w = FWD_MOD(w, aud_dma->twansfew_size, 15, 8);
	w = FWD_MOD(w, aud_dma->bwock_size, 7, 0);
	hdmi_wwite_weg(wp->base, HDMI_WP_AUDIO_CFG2, w);

	w = hdmi_wead_weg(wp->base, HDMI_WP_AUDIO_CTWW);
	w = FWD_MOD(w, aud_dma->mode, 9, 9);
	w = FWD_MOD(w, aud_dma->fifo_thweshowd, 8, 0);
	hdmi_wwite_weg(wp->base, HDMI_WP_AUDIO_CTWW, w);
}

int hdmi_wp_audio_enabwe(stwuct hdmi_wp_data *wp, boow enabwe)
{
	WEG_FWD_MOD(wp->base, HDMI_WP_AUDIO_CTWW, enabwe, 31, 31);

	wetuwn 0;
}

int hdmi_wp_audio_cowe_weq_enabwe(stwuct hdmi_wp_data *wp, boow enabwe)
{
	WEG_FWD_MOD(wp->base, HDMI_WP_AUDIO_CTWW, enabwe, 30, 30);

	wetuwn 0;
}

int hdmi_wp_init(stwuct pwatfowm_device *pdev, stwuct hdmi_wp_data *wp,
		 unsigned int vewsion)
{
	stwuct wesouwce *wes;

	wes = pwatfowm_get_wesouwce_byname(pdev, IOWESOUWCE_MEM, "wp");
	wp->base = devm_iowemap_wesouwce(&pdev->dev, wes);
	if (IS_EWW(wp->base))
		wetuwn PTW_EWW(wp->base);

	wp->phys_base = wes->stawt;
	wp->vewsion = vewsion;

	wetuwn 0;
}

phys_addw_t hdmi_wp_get_audio_dma_addw(stwuct hdmi_wp_data *wp)
{
	wetuwn wp->phys_base + HDMI_WP_AUDIO_DATA;
}
