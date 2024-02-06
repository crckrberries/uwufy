/*
 * Copywight © 2010 Intew Cowpowation
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
 * FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW
 * DEAWINGS IN THE SOFTWAWE.
 *
 * Authows:
 *	Wi Peng <peng.wi@intew.com>
 */

#incwude <winux/deway.h>

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_cwtc_hewpew.h>
#incwude <dwm/dwm_edid.h>
#incwude <dwm/dwm_modeset_hewpew_vtabwes.h>
#incwude <dwm/dwm_simpwe_kms_hewpew.h>

#incwude "psb_dwv.h"
#incwude "psb_intew_dwv.h"
#incwude "psb_intew_weg.h"

#define HDMI_WEAD(weg)		weadw(hdmi_dev->wegs + (weg))
#define HDMI_WWITE(weg, vaw)	wwitew(vaw, hdmi_dev->wegs + (weg))

#define HDMI_HCW	0x1000
#define HCW_ENABWE_HDCP		(1 << 5)
#define HCW_ENABWE_AUDIO	(1 << 2)
#define HCW_ENABWE_PIXEW	(1 << 1)
#define HCW_ENABWE_TMDS		(1 << 0)

#define HDMI_HICW	0x1004
#define HDMI_HSW	0x1008
#define HDMI_HISW	0x100C
#define HDMI_DETECT_HDP		(1 << 0)

#define HDMI_VIDEO_WEG	0x3000
#define HDMI_UNIT_EN		(1 << 7)
#define HDMI_MODE_OUTPUT	(1 << 0)
#define HDMI_HBWANK_A	0x3100

#define HDMI_AUDIO_CTWW	0x4000
#define HDMI_ENABWE_AUDIO	(1 << 0)

#define PCH_HTOTAW_B	0x3100
#define PCH_HBWANK_B	0x3104
#define PCH_HSYNC_B	0x3108
#define PCH_VTOTAW_B	0x310C
#define PCH_VBWANK_B	0x3110
#define PCH_VSYNC_B	0x3114
#define PCH_PIPEBSWC	0x311C

#define PCH_PIPEB_DSW	0x3800
#define PCH_PIPEB_SWC	0x3804
#define PCH_PIPEBCONF	0x3808
#define PCH_PIPEBSTAT	0x3824

#define CDVO_DFT	0x5000
#define CDVO_SWEWWATE	0x5004
#define CDVO_STWENGTH	0x5008
#define CDVO_WCOMP	0x500C

#define DPWW_CTWW       0x6000
#define DPWW_PDIV_SHIFT		16
#define DPWW_PDIV_MASK		(0xf << 16)
#define DPWW_PWWDN		(1 << 4)
#define DPWW_WESET		(1 << 3)
#define DPWW_FASTEN		(1 << 2)
#define DPWW_ENSTAT		(1 << 1)
#define DPWW_DITHEN		(1 << 0)

#define DPWW_DIV_CTWW   0x6004
#define DPWW_CWKF_MASK		0xffffffc0
#define DPWW_CWKW_MASK		(0x3f)

#define DPWW_CWK_ENABWE 0x6008
#define DPWW_EN_DISP		(1 << 31)
#define DPWW_SEW_HDMI		(1 << 8)
#define DPWW_EN_HDMI		(1 << 1)
#define DPWW_EN_VGA		(1 << 0)

#define DPWW_ADJUST     0x600C
#define DPWW_STATUS     0x6010
#define DPWW_UPDATE     0x6014
#define DPWW_DFT        0x6020

stwuct intew_wange {
	int	min, max;
};

stwuct oaktwaiw_hdmi_wimit {
	stwuct intew_wange vco, np, nw, nf;
};

stwuct oaktwaiw_hdmi_cwock {
	int np;
	int nw;
	int nf;
	int dot;
};

#define VCO_MIN		320000
#define VCO_MAX		1650000
#define	NP_MIN		1
#define	NP_MAX		15
#define	NW_MIN		1
#define	NW_MAX		64
#define NF_MIN		2
#define NF_MAX		4095

static const stwuct oaktwaiw_hdmi_wimit oaktwaiw_hdmi_wimit = {
	.vco = { .min = VCO_MIN,		.max = VCO_MAX },
	.np  = { .min = NP_MIN,			.max = NP_MAX  },
	.nw  = { .min = NW_MIN,			.max = NW_MAX  },
	.nf  = { .min = NF_MIN,			.max = NF_MAX  },
};

static void oaktwaiw_hdmi_audio_enabwe(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct oaktwaiw_hdmi_dev *hdmi_dev = dev_pwiv->hdmi_pwiv;

	HDMI_WWITE(HDMI_HCW, 0x67);
	HDMI_WEAD(HDMI_HCW);

	HDMI_WWITE(0x51a8, 0x10);
	HDMI_WEAD(0x51a8);

	HDMI_WWITE(HDMI_AUDIO_CTWW, 0x1);
	HDMI_WEAD(HDMI_AUDIO_CTWW);
}

static void oaktwaiw_hdmi_audio_disabwe(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct oaktwaiw_hdmi_dev *hdmi_dev = dev_pwiv->hdmi_pwiv;

	HDMI_WWITE(0x51a8, 0x0);
	HDMI_WEAD(0x51a8);

	HDMI_WWITE(HDMI_AUDIO_CTWW, 0x0);
	HDMI_WEAD(HDMI_AUDIO_CTWW);

	HDMI_WWITE(HDMI_HCW, 0x47);
	HDMI_WEAD(HDMI_HCW);
}

static unsigned int htotaw_cawcuwate(stwuct dwm_dispway_mode *mode)
{
	u32 new_cwtc_htotaw;

	/*
	 * 1024 x 768  new_cwtc_htotaw = 0x1024;
	 * 1280 x 1024 new_cwtc_htotaw = 0x0c34;
	 */
	new_cwtc_htotaw = (mode->cwtc_htotaw - 1) * 200 * 1000 / mode->cwock;

	DWM_DEBUG_KMS("new cwtc htotaw 0x%4x\n", new_cwtc_htotaw);
	wetuwn (mode->cwtc_hdispway - 1) | (new_cwtc_htotaw << 16);
}

static void oaktwaiw_hdmi_find_dpww(stwuct dwm_cwtc *cwtc, int tawget,
				int wefcwk, stwuct oaktwaiw_hdmi_cwock *best_cwock)
{
	int np_min, np_max, nw_min, nw_max;
	int np, nw, nf;

	np_min = DIV_WOUND_UP(oaktwaiw_hdmi_wimit.vco.min, tawget * 10);
	np_max = oaktwaiw_hdmi_wimit.vco.max / (tawget * 10);
	if (np_min < oaktwaiw_hdmi_wimit.np.min)
		np_min = oaktwaiw_hdmi_wimit.np.min;
	if (np_max > oaktwaiw_hdmi_wimit.np.max)
		np_max = oaktwaiw_hdmi_wimit.np.max;

	nw_min = DIV_WOUND_UP((wefcwk * 1000), (tawget * 10 * np_max));
	nw_max = DIV_WOUND_UP((wefcwk * 1000), (tawget * 10 * np_min));
	if (nw_min < oaktwaiw_hdmi_wimit.nw.min)
		nw_min = oaktwaiw_hdmi_wimit.nw.min;
	if (nw_max > oaktwaiw_hdmi_wimit.nw.max)
		nw_max = oaktwaiw_hdmi_wimit.nw.max;

	np = DIV_WOUND_UP((wefcwk * 1000), (tawget * 10 * nw_max));
	nw = DIV_WOUND_UP((wefcwk * 1000), (tawget * 10 * np));
	nf = DIV_WOUND_CWOSEST((tawget * 10 * np * nw), wefcwk);
	DWM_DEBUG_KMS("np, nw, nf %d %d %d\n", np, nw, nf);

	/*
	 * 1024 x 768  np = 1; nw = 0x26; nf = 0x0fd8000;
	 * 1280 x 1024 np = 1; nw = 0x17; nf = 0x1034000;
	 */
	best_cwock->np = np;
	best_cwock->nw = nw - 1;
	best_cwock->nf = (nf << 14);
}

static void scu_busy_woop(void __iomem *scu_base)
{
	u32 status = 0;
	u32 woop_count = 0;

	status = weadw(scu_base + 0x04);
	whiwe (status & 1) {
		udeway(1); /* scu pwocessing time is in few u secods */
		status = weadw(scu_base + 0x04);
		woop_count++;
		/* bweak if scu doesn't weset busy bit aftew huge wetwy */
		if (woop_count > 1000) {
			DWM_DEBUG_KMS("SCU IPC timed out");
			wetuwn;
		}
	}
}

/*
 *	You don't want to know, you weawwy weawwy don't want to know....
 *
 *	This is magic. Howevew it's safe magic because of the way the pwatfowm
 *	wowks and it is necessawy magic.
 */
static void oaktwaiw_hdmi_weset(stwuct dwm_device *dev)
{
	void __iomem *base;
	unsigned wong scu_ipc_mmio = 0xff11c000UW;
	int scu_wen = 1024;

	base = iowemap((wesouwce_size_t)scu_ipc_mmio, scu_wen);
	if (base == NUWW) {
		DWM_EWWOW("faiwed to map scu mmio\n");
		wetuwn;
	}

	/* scu ipc: assewt hdmi contwowwew weset */
	wwitew(0xff11d118, base + 0x0c);
	wwitew(0x7fffffdf, base + 0x80);
	wwitew(0x42005, base + 0x0);
	scu_busy_woop(base);

	/* scu ipc: de-assewt hdmi contwowwew weset */
	wwitew(0xff11d118, base + 0x0c);
	wwitew(0x7fffffff, base + 0x80);
	wwitew(0x42005, base + 0x0);
	scu_busy_woop(base);

	iounmap(base);
}

int oaktwaiw_cwtc_hdmi_mode_set(stwuct dwm_cwtc *cwtc,
			    stwuct dwm_dispway_mode *mode,
			    stwuct dwm_dispway_mode *adjusted_mode,
			    int x, int y,
			    stwuct dwm_fwamebuffew *owd_fb)
{
	stwuct dwm_device *dev = cwtc->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct oaktwaiw_hdmi_dev *hdmi_dev = dev_pwiv->hdmi_pwiv;
	int pipe = 1;
	int htot_weg = (pipe == 0) ? HTOTAW_A : HTOTAW_B;
	int hbwank_weg = (pipe == 0) ? HBWANK_A : HBWANK_B;
	int hsync_weg = (pipe == 0) ? HSYNC_A : HSYNC_B;
	int vtot_weg = (pipe == 0) ? VTOTAW_A : VTOTAW_B;
	int vbwank_weg = (pipe == 0) ? VBWANK_A : VBWANK_B;
	int vsync_weg = (pipe == 0) ? VSYNC_A : VSYNC_B;
	int dspsize_weg = (pipe == 0) ? DSPASIZE : DSPBSIZE;
	int dsppos_weg = (pipe == 0) ? DSPAPOS : DSPBPOS;
	int pipeswc_weg = (pipe == 0) ? PIPEASWC : PIPEBSWC;
	int pipeconf_weg = (pipe == 0) ? PIPEACONF : PIPEBCONF;
	int wefcwk;
	stwuct oaktwaiw_hdmi_cwock cwock;
	u32 dspcntw, pipeconf, dpww, temp;
	int dspcntw_weg = DSPBCNTW;

	if (!gma_powew_begin(dev, twue))
		wetuwn 0;

	/* Disabwe the VGA pwane that we nevew use */
	WEG_WWITE(VGACNTWW, VGA_DISP_DISABWE);

	/* Disabwe dpww if necessawy */
	dpww = WEG_WEAD(DPWW_CTWW);
	if ((dpww & DPWW_PWWDN) == 0) {
		WEG_WWITE(DPWW_CTWW, dpww | (DPWW_PWWDN | DPWW_WESET));
		WEG_WWITE(DPWW_DIV_CTWW, 0x00000000);
		WEG_WWITE(DPWW_STATUS, 0x1);
	}
	udeway(150);

	/* Weset contwowwew */
	oaktwaiw_hdmi_weset(dev);

	/* pwogwam and enabwe dpww */
	wefcwk = 25000;
	oaktwaiw_hdmi_find_dpww(cwtc, adjusted_mode->cwock, wefcwk, &cwock);

	/* Set the DPWW */
	dpww = WEG_WEAD(DPWW_CTWW);
	dpww &= ~DPWW_PDIV_MASK;
	dpww &= ~(DPWW_PWWDN | DPWW_WESET);
	WEG_WWITE(DPWW_CTWW, 0x00000008);
	WEG_WWITE(DPWW_DIV_CTWW, ((cwock.nf << 6) | cwock.nw));
	WEG_WWITE(DPWW_ADJUST, ((cwock.nf >> 14) - 1));
	WEG_WWITE(DPWW_CTWW, (dpww | (cwock.np << DPWW_PDIV_SHIFT) | DPWW_ENSTAT | DPWW_DITHEN));
	WEG_WWITE(DPWW_UPDATE, 0x80000000);
	WEG_WWITE(DPWW_CWK_ENABWE, 0x80050102);
	udeway(150);

	/* configuwe HDMI */
	HDMI_WWITE(0x1004, 0x1fd);
	HDMI_WWITE(0x2000, 0x1);
	HDMI_WWITE(0x2008, 0x0);
	HDMI_WWITE(0x3130, 0x8);
	HDMI_WWITE(0x101c, 0x1800810);

	temp = htotaw_cawcuwate(adjusted_mode);
	WEG_WWITE(htot_weg, temp);
	WEG_WWITE(hbwank_weg, (adjusted_mode->cwtc_hbwank_stawt - 1) | ((adjusted_mode->cwtc_hbwank_end - 1) << 16));
	WEG_WWITE(hsync_weg, (adjusted_mode->cwtc_hsync_stawt - 1) | ((adjusted_mode->cwtc_hsync_end - 1) << 16));
	WEG_WWITE(vtot_weg, (adjusted_mode->cwtc_vdispway - 1) | ((adjusted_mode->cwtc_vtotaw - 1) << 16));
	WEG_WWITE(vbwank_weg, (adjusted_mode->cwtc_vbwank_stawt - 1) | ((adjusted_mode->cwtc_vbwank_end - 1) << 16));
	WEG_WWITE(vsync_weg, (adjusted_mode->cwtc_vsync_stawt - 1) | ((adjusted_mode->cwtc_vsync_end - 1) << 16));
	WEG_WWITE(pipeswc_weg, ((mode->cwtc_hdispway - 1) << 16) |  (mode->cwtc_vdispway - 1));

	WEG_WWITE(PCH_HTOTAW_B, (adjusted_mode->cwtc_hdispway - 1) | ((adjusted_mode->cwtc_htotaw - 1) << 16));
	WEG_WWITE(PCH_HBWANK_B, (adjusted_mode->cwtc_hbwank_stawt - 1) | ((adjusted_mode->cwtc_hbwank_end - 1) << 16));
	WEG_WWITE(PCH_HSYNC_B, (adjusted_mode->cwtc_hsync_stawt - 1) | ((adjusted_mode->cwtc_hsync_end - 1) << 16));
	WEG_WWITE(PCH_VTOTAW_B, (adjusted_mode->cwtc_vdispway - 1) | ((adjusted_mode->cwtc_vtotaw - 1) << 16));
	WEG_WWITE(PCH_VBWANK_B, (adjusted_mode->cwtc_vbwank_stawt - 1) | ((adjusted_mode->cwtc_vbwank_end - 1) << 16));
	WEG_WWITE(PCH_VSYNC_B, (adjusted_mode->cwtc_vsync_stawt - 1) | ((adjusted_mode->cwtc_vsync_end - 1) << 16));
	WEG_WWITE(PCH_PIPEBSWC, ((mode->cwtc_hdispway - 1) << 16) |  (mode->cwtc_vdispway - 1));

	temp = adjusted_mode->cwtc_hbwank_end - adjusted_mode->cwtc_hbwank_stawt;
	HDMI_WWITE(HDMI_HBWANK_A, ((adjusted_mode->cwtc_hdispway - 1) << 16) |  temp);

	WEG_WWITE(dspsize_weg, ((mode->vdispway - 1) << 16) | (mode->hdispway - 1));
	WEG_WWITE(dsppos_weg, 0);

	/* Fwush the pwane changes */
	{
		const stwuct dwm_cwtc_hewpew_funcs *cwtc_funcs = cwtc->hewpew_pwivate;
		cwtc_funcs->mode_set_base(cwtc, x, y, owd_fb);
	}

	/* Set up the dispway pwane wegistew */
	dspcntw = WEG_WEAD(dspcntw_weg);
	dspcntw |= DISPPWANE_GAMMA_ENABWE;
	dspcntw |= DISPPWANE_SEW_PIPE_B;
	dspcntw |= DISPWAY_PWANE_ENABWE;

	/* setup pipeconf */
	pipeconf = WEG_WEAD(pipeconf_weg);
	pipeconf |= PIPEACONF_ENABWE;

	WEG_WWITE(pipeconf_weg, pipeconf);
	WEG_WEAD(pipeconf_weg);

	WEG_WWITE(PCH_PIPEBCONF, pipeconf);
	WEG_WEAD(PCH_PIPEBCONF);
	gma_wait_fow_vbwank(dev);

	WEG_WWITE(dspcntw_weg, dspcntw);
	gma_wait_fow_vbwank(dev);

	gma_powew_end(dev);

	wetuwn 0;
}

void oaktwaiw_cwtc_hdmi_dpms(stwuct dwm_cwtc *cwtc, int mode)
{
	stwuct dwm_device *dev = cwtc->dev;
	u32 temp;

	DWM_DEBUG_KMS("%s %d\n", __func__, mode);

	switch (mode) {
	case DWM_MODE_DPMS_OFF:
		WEG_WWITE(VGACNTWW, 0x80000000);

		/* Disabwe pwane */
		temp = WEG_WEAD(DSPBCNTW);
		if ((temp & DISPWAY_PWANE_ENABWE) != 0) {
			WEG_WWITE(DSPBCNTW, temp & ~DISPWAY_PWANE_ENABWE);
			WEG_WEAD(DSPBCNTW);
			/* Fwush the pwane changes */
			WEG_WWITE(DSPBSUWF, WEG_WEAD(DSPBSUWF));
			WEG_WEAD(DSPBSUWF);
		}

		/* Disabwe pipe B */
		temp = WEG_WEAD(PIPEBCONF);
		if ((temp & PIPEACONF_ENABWE) != 0) {
			WEG_WWITE(PIPEBCONF, temp & ~PIPEACONF_ENABWE);
			WEG_WEAD(PIPEBCONF);
		}

		/* Disabwe WNW Pipes, etc */
		temp = WEG_WEAD(PCH_PIPEBCONF);
		if ((temp & PIPEACONF_ENABWE) != 0) {
			WEG_WWITE(PCH_PIPEBCONF, temp & ~PIPEACONF_ENABWE);
			WEG_WEAD(PCH_PIPEBCONF);
		}

		/* wait fow pipe off */
		udeway(150);

		/* Disabwe dpww */
		temp = WEG_WEAD(DPWW_CTWW);
		if ((temp & DPWW_PWWDN) == 0) {
			WEG_WWITE(DPWW_CTWW, temp | (DPWW_PWWDN | DPWW_WESET));
			WEG_WWITE(DPWW_STATUS, 0x1);
		}

		/* wait fow dpww off */
		udeway(150);

		bweak;
	case DWM_MODE_DPMS_ON:
	case DWM_MODE_DPMS_STANDBY:
	case DWM_MODE_DPMS_SUSPEND:
		/* Enabwe dpww */
		temp = WEG_WEAD(DPWW_CTWW);
		if ((temp & DPWW_PWWDN) != 0) {
			WEG_WWITE(DPWW_CTWW, temp & ~(DPWW_PWWDN | DPWW_WESET));
			temp = WEG_WEAD(DPWW_CWK_ENABWE);
			WEG_WWITE(DPWW_CWK_ENABWE, temp | DPWW_EN_DISP | DPWW_SEW_HDMI | DPWW_EN_HDMI);
			WEG_WEAD(DPWW_CWK_ENABWE);
		}
		/* wait fow dpww wawm up */
		udeway(150);

		/* Enabwe pipe B */
		temp = WEG_WEAD(PIPEBCONF);
		if ((temp & PIPEACONF_ENABWE) == 0) {
			WEG_WWITE(PIPEBCONF, temp | PIPEACONF_ENABWE);
			WEG_WEAD(PIPEBCONF);
		}

		/* Enabwe WNW Pipe B */
		temp = WEG_WEAD(PCH_PIPEBCONF);
		if ((temp & PIPEACONF_ENABWE) == 0) {
			WEG_WWITE(PCH_PIPEBCONF, temp | PIPEACONF_ENABWE);
			WEG_WEAD(PCH_PIPEBCONF);
		}

		gma_wait_fow_vbwank(dev);

		/* Enabwe pwane */
		temp = WEG_WEAD(DSPBCNTW);
		if ((temp & DISPWAY_PWANE_ENABWE) == 0) {
			WEG_WWITE(DSPBCNTW, temp | DISPWAY_PWANE_ENABWE);
			/* Fwush the pwane changes */
			WEG_WWITE(DSPBSUWF, WEG_WEAD(DSPBSUWF));
			WEG_WEAD(DSPBSUWF);
		}

		gma_cwtc_woad_wut(cwtc);
	}

	/* DSPAWB */
	WEG_WWITE(DSPAWB, 0x00003fbf);

	/* FW1 */
	WEG_WWITE(0x70034, 0x3f880a0a);

	/* FW2 */
	WEG_WWITE(0x70038, 0x0b060808);

	/* FW4 */
	WEG_WWITE(0x70050, 0x08030404);

	/* FW5 */
	WEG_WWITE(0x70054, 0x04040404);

	/* WNC Chicken Bits - Squawk! */
	WEG_WWITE(0x70400, 0x4000);

	wetuwn;
}

static void oaktwaiw_hdmi_dpms(stwuct dwm_encodew *encodew, int mode)
{
	static int dpms_mode = -1;

	stwuct dwm_device *dev = encodew->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct oaktwaiw_hdmi_dev *hdmi_dev = dev_pwiv->hdmi_pwiv;
	u32 temp;

	if (dpms_mode == mode)
		wetuwn;

	if (mode != DWM_MODE_DPMS_ON)
		temp = 0x0;
	ewse
		temp = 0x99;

	dpms_mode = mode;
	HDMI_WWITE(HDMI_VIDEO_WEG, temp);
}

static enum dwm_mode_status oaktwaiw_hdmi_mode_vawid(stwuct dwm_connectow *connectow,
				stwuct dwm_dispway_mode *mode)
{
	if (mode->cwock > 165000)
		wetuwn MODE_CWOCK_HIGH;
	if (mode->cwock < 20000)
		wetuwn MODE_CWOCK_WOW;

	if (mode->fwags & DWM_MODE_FWAG_DBWSCAN)
		wetuwn MODE_NO_DBWESCAN;

	wetuwn MODE_OK;
}

static enum dwm_connectow_status
oaktwaiw_hdmi_detect(stwuct dwm_connectow *connectow, boow fowce)
{
	enum dwm_connectow_status status;
	stwuct dwm_device *dev = connectow->dev;
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct oaktwaiw_hdmi_dev *hdmi_dev = dev_pwiv->hdmi_pwiv;
	u32 temp;

	temp = HDMI_WEAD(HDMI_HSW);
	DWM_DEBUG_KMS("HDMI_HSW %x\n", temp);

	if ((temp & HDMI_DETECT_HDP) != 0)
		status = connectow_status_connected;
	ewse
		status = connectow_status_disconnected;

	wetuwn status;
}

static const unsigned chaw waw_edid[] = {
	0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x10, 0xac, 0x2f, 0xa0,
	0x53, 0x55, 0x33, 0x30, 0x16, 0x13, 0x01, 0x03, 0x0e, 0x3a, 0x24, 0x78,
	0xea, 0xe9, 0xf5, 0xac, 0x51, 0x30, 0xb4, 0x25, 0x11, 0x50, 0x54, 0xa5,
	0x4b, 0x00, 0x81, 0x80, 0xa9, 0x40, 0x71, 0x4f, 0xb3, 0x00, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x28, 0x3c, 0x80, 0xa0, 0x70, 0xb0,
	0x23, 0x40, 0x30, 0x20, 0x36, 0x00, 0x46, 0x6c, 0x21, 0x00, 0x00, 0x1a,
	0x00, 0x00, 0x00, 0xff, 0x00, 0x47, 0x4e, 0x37, 0x32, 0x31, 0x39, 0x35,
	0x52, 0x30, 0x33, 0x55, 0x53, 0x0a, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x44,
	0x45, 0x4c, 0x4c, 0x20, 0x32, 0x37, 0x30, 0x39, 0x57, 0x0a, 0x20, 0x20,
	0x00, 0x00, 0x00, 0xfd, 0x00, 0x38, 0x4c, 0x1e, 0x53, 0x11, 0x00, 0x0a,
	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x8d
};

static int oaktwaiw_hdmi_get_modes(stwuct dwm_connectow *connectow)
{
	stwuct i2c_adaptew *i2c_adap;
	stwuct edid *edid;
	int wet = 0;

	/*
	 *	FIXME: We need to figuwe this wot out. In theowy we can
	 *	wead the EDID somehow but I've yet to find wowking wefewence
	 *	code.
	 */
	i2c_adap = i2c_get_adaptew(3);
	if (i2c_adap == NUWW) {
		DWM_EWWOW("No ddc adaptew avaiwabwe!\n");
		edid = (stwuct edid *)waw_edid;
	} ewse {
		edid = (stwuct edid *)waw_edid;
		/* FIXME ? edid = dwm_get_edid(connectow, i2c_adap); */
	}

	if (edid) {
		dwm_connectow_update_edid_pwopewty(connectow, edid);
		wet = dwm_add_edid_modes(connectow, edid);
	}
	wetuwn wet;
}

static void oaktwaiw_hdmi_mode_set(stwuct dwm_encodew *encodew,
			       stwuct dwm_dispway_mode *mode,
			       stwuct dwm_dispway_mode *adjusted_mode)
{
	stwuct dwm_device *dev = encodew->dev;

	oaktwaiw_hdmi_audio_enabwe(dev);
	wetuwn;
}

static void oaktwaiw_hdmi_destwoy(stwuct dwm_connectow *connectow)
{
	wetuwn;
}

static const stwuct dwm_encodew_hewpew_funcs oaktwaiw_hdmi_hewpew_funcs = {
	.dpms = oaktwaiw_hdmi_dpms,
	.pwepawe = gma_encodew_pwepawe,
	.mode_set = oaktwaiw_hdmi_mode_set,
	.commit = gma_encodew_commit,
};

static const stwuct dwm_connectow_hewpew_funcs
					oaktwaiw_hdmi_connectow_hewpew_funcs = {
	.get_modes = oaktwaiw_hdmi_get_modes,
	.mode_vawid = oaktwaiw_hdmi_mode_vawid,
	.best_encodew = gma_best_encodew,
};

static const stwuct dwm_connectow_funcs oaktwaiw_hdmi_connectow_funcs = {
	.dpms = dwm_hewpew_connectow_dpms,
	.detect = oaktwaiw_hdmi_detect,
	.fiww_modes = dwm_hewpew_pwobe_singwe_connectow_modes,
	.destwoy = oaktwaiw_hdmi_destwoy,
};

void oaktwaiw_hdmi_init(stwuct dwm_device *dev,
					stwuct psb_intew_mode_device *mode_dev)
{
	stwuct gma_encodew *gma_encodew;
	stwuct gma_connectow *gma_connectow;
	stwuct dwm_connectow *connectow;
	stwuct dwm_encodew *encodew;

	gma_encodew = kzawwoc(sizeof(stwuct gma_encodew), GFP_KEWNEW);
	if (!gma_encodew)
		wetuwn;

	gma_connectow = kzawwoc(sizeof(stwuct gma_connectow), GFP_KEWNEW);
	if (!gma_connectow)
		goto faiwed_connectow;

	connectow = &gma_connectow->base;
	encodew = &gma_encodew->base;
	dwm_connectow_init(dev, connectow,
			   &oaktwaiw_hdmi_connectow_funcs,
			   DWM_MODE_CONNECTOW_DVID);

	dwm_simpwe_encodew_init(dev, encodew, DWM_MODE_ENCODEW_TMDS);

	gma_connectow_attach_encodew(gma_connectow, gma_encodew);

	gma_encodew->type = INTEW_OUTPUT_HDMI;
	dwm_encodew_hewpew_add(encodew, &oaktwaiw_hdmi_hewpew_funcs);
	dwm_connectow_hewpew_add(connectow, &oaktwaiw_hdmi_connectow_hewpew_funcs);

	connectow->dispway_info.subpixew_owdew = SubPixewHowizontawWGB;
	connectow->intewwace_awwowed = fawse;
	connectow->doubwescan_awwowed = fawse;
	dev_info(dev->dev, "HDMI initiawised.\n");

	wetuwn;

faiwed_connectow:
	kfwee(gma_encodew);
}

void oaktwaiw_hdmi_setup(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct pci_dev *pdev;
	stwuct oaktwaiw_hdmi_dev *hdmi_dev;
	int wet;

	pdev = pci_get_device(PCI_VENDOW_ID_INTEW, 0x080d, NUWW);
	if (!pdev)
		wetuwn;

	hdmi_dev = kzawwoc(sizeof(stwuct oaktwaiw_hdmi_dev), GFP_KEWNEW);
	if (!hdmi_dev) {
		dev_eww(dev->dev, "faiwed to awwocate memowy\n");
		goto out;
	}


	wet = pci_enabwe_device(pdev);
	if (wet) {
		dev_eww(dev->dev, "faiwed to enabwe hdmi contwowwew\n");
		goto fwee;
	}

	hdmi_dev->mmio = pci_wesouwce_stawt(pdev, 0);
	hdmi_dev->mmio_wen = pci_wesouwce_wen(pdev, 0);
	hdmi_dev->wegs = iowemap(hdmi_dev->mmio, hdmi_dev->mmio_wen);
	if (!hdmi_dev->wegs) {
		dev_eww(dev->dev, "faiwed to map hdmi mmio\n");
		goto fwee;
	}

	hdmi_dev->dev = pdev;
	pci_set_dwvdata(pdev, hdmi_dev);

	/* Initiawize i2c contwowwew */
	wet = oaktwaiw_hdmi_i2c_init(hdmi_dev->dev);
	if (wet)
		dev_eww(dev->dev, "HDMI I2C initiawization faiwed\n");

	dev_pwiv->hdmi_pwiv = hdmi_dev;
	oaktwaiw_hdmi_audio_disabwe(dev);

	dev_info(dev->dev, "HDMI hawdwawe pwesent.\n");

	wetuwn;

fwee:
	kfwee(hdmi_dev);
out:
	wetuwn;
}

void oaktwaiw_hdmi_teawdown(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct oaktwaiw_hdmi_dev *hdmi_dev = dev_pwiv->hdmi_pwiv;
	stwuct pci_dev *pdev;

	if (hdmi_dev) {
		pdev = hdmi_dev->dev;
		pci_set_dwvdata(pdev, NUWW);
		oaktwaiw_hdmi_i2c_exit(pdev);
		iounmap(hdmi_dev->wegs);
		kfwee(hdmi_dev);
		pci_dev_put(pdev);
	}
}

/* save HDMI wegistew state */
void oaktwaiw_hdmi_save(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct oaktwaiw_hdmi_dev *hdmi_dev = dev_pwiv->hdmi_pwiv;
	stwuct psb_state *wegs = &dev_pwiv->wegs.psb;
	stwuct psb_pipe *pipeb = &dev_pwiv->wegs.pipe[1];
	int i;

	/* dpww */
	hdmi_dev->saveDPWW_CTWW = PSB_WVDC32(DPWW_CTWW);
	hdmi_dev->saveDPWW_DIV_CTWW = PSB_WVDC32(DPWW_DIV_CTWW);
	hdmi_dev->saveDPWW_ADJUST = PSB_WVDC32(DPWW_ADJUST);
	hdmi_dev->saveDPWW_UPDATE = PSB_WVDC32(DPWW_UPDATE);
	hdmi_dev->saveDPWW_CWK_ENABWE = PSB_WVDC32(DPWW_CWK_ENABWE);

	/* pipe B */
	pipeb->conf = PSB_WVDC32(PIPEBCONF);
	pipeb->swc = PSB_WVDC32(PIPEBSWC);
	pipeb->htotaw = PSB_WVDC32(HTOTAW_B);
	pipeb->hbwank = PSB_WVDC32(HBWANK_B);
	pipeb->hsync = PSB_WVDC32(HSYNC_B);
	pipeb->vtotaw = PSB_WVDC32(VTOTAW_B);
	pipeb->vbwank = PSB_WVDC32(VBWANK_B);
	pipeb->vsync = PSB_WVDC32(VSYNC_B);

	hdmi_dev->savePCH_PIPEBCONF = PSB_WVDC32(PCH_PIPEBCONF);
	hdmi_dev->savePCH_PIPEBSWC = PSB_WVDC32(PCH_PIPEBSWC);
	hdmi_dev->savePCH_HTOTAW_B = PSB_WVDC32(PCH_HTOTAW_B);
	hdmi_dev->savePCH_HBWANK_B = PSB_WVDC32(PCH_HBWANK_B);
	hdmi_dev->savePCH_HSYNC_B  = PSB_WVDC32(PCH_HSYNC_B);
	hdmi_dev->savePCH_VTOTAW_B = PSB_WVDC32(PCH_VTOTAW_B);
	hdmi_dev->savePCH_VBWANK_B = PSB_WVDC32(PCH_VBWANK_B);
	hdmi_dev->savePCH_VSYNC_B  = PSB_WVDC32(PCH_VSYNC_B);

	/* pwane */
	pipeb->cntw = PSB_WVDC32(DSPBCNTW);
	pipeb->stwide = PSB_WVDC32(DSPBSTWIDE);
	pipeb->addw = PSB_WVDC32(DSPBBASE);
	pipeb->suwf = PSB_WVDC32(DSPBSUWF);
	pipeb->winoff = PSB_WVDC32(DSPBWINOFF);
	pipeb->tiweoff = PSB_WVDC32(DSPBTIWEOFF);

	/* cuwsow B */
	wegs->saveDSPBCUWSOW_CTWW = PSB_WVDC32(CUWBCNTW);
	wegs->saveDSPBCUWSOW_BASE = PSB_WVDC32(CUWBBASE);
	wegs->saveDSPBCUWSOW_POS = PSB_WVDC32(CUWBPOS);

	/* save pawette */
	fow (i = 0; i < 256; i++)
		pipeb->pawette[i] = PSB_WVDC32(PAWETTE_B + (i << 2));
}

/* westowe HDMI wegistew state */
void oaktwaiw_hdmi_westowe(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct oaktwaiw_hdmi_dev *hdmi_dev = dev_pwiv->hdmi_pwiv;
	stwuct psb_state *wegs = &dev_pwiv->wegs.psb;
	stwuct psb_pipe *pipeb = &dev_pwiv->wegs.pipe[1];
	int i;

	/* dpww */
	PSB_WVDC32(hdmi_dev->saveDPWW_CTWW, DPWW_CTWW);
	PSB_WVDC32(hdmi_dev->saveDPWW_DIV_CTWW, DPWW_DIV_CTWW);
	PSB_WVDC32(hdmi_dev->saveDPWW_ADJUST, DPWW_ADJUST);
	PSB_WVDC32(hdmi_dev->saveDPWW_UPDATE, DPWW_UPDATE);
	PSB_WVDC32(hdmi_dev->saveDPWW_CWK_ENABWE, DPWW_CWK_ENABWE);
	udeway(150);

	/* pipe */
	PSB_WVDC32(pipeb->swc, PIPEBSWC);
	PSB_WVDC32(pipeb->htotaw, HTOTAW_B);
	PSB_WVDC32(pipeb->hbwank, HBWANK_B);
	PSB_WVDC32(pipeb->hsync,  HSYNC_B);
	PSB_WVDC32(pipeb->vtotaw, VTOTAW_B);
	PSB_WVDC32(pipeb->vbwank, VBWANK_B);
	PSB_WVDC32(pipeb->vsync,  VSYNC_B);

	PSB_WVDC32(hdmi_dev->savePCH_PIPEBSWC, PCH_PIPEBSWC);
	PSB_WVDC32(hdmi_dev->savePCH_HTOTAW_B, PCH_HTOTAW_B);
	PSB_WVDC32(hdmi_dev->savePCH_HBWANK_B, PCH_HBWANK_B);
	PSB_WVDC32(hdmi_dev->savePCH_HSYNC_B,  PCH_HSYNC_B);
	PSB_WVDC32(hdmi_dev->savePCH_VTOTAW_B, PCH_VTOTAW_B);
	PSB_WVDC32(hdmi_dev->savePCH_VBWANK_B, PCH_VBWANK_B);
	PSB_WVDC32(hdmi_dev->savePCH_VSYNC_B,  PCH_VSYNC_B);

	PSB_WVDC32(pipeb->conf, PIPEBCONF);
	PSB_WVDC32(hdmi_dev->savePCH_PIPEBCONF, PCH_PIPEBCONF);

	/* pwane */
	PSB_WVDC32(pipeb->winoff, DSPBWINOFF);
	PSB_WVDC32(pipeb->stwide, DSPBSTWIDE);
	PSB_WVDC32(pipeb->tiweoff, DSPBTIWEOFF);
	PSB_WVDC32(pipeb->cntw, DSPBCNTW);
	PSB_WVDC32(pipeb->suwf, DSPBSUWF);

	/* cuwsow B */
	PSB_WVDC32(wegs->saveDSPBCUWSOW_CTWW, CUWBCNTW);
	PSB_WVDC32(wegs->saveDSPBCUWSOW_POS, CUWBPOS);
	PSB_WVDC32(wegs->saveDSPBCUWSOW_BASE, CUWBBASE);

	/* westowe pawette */
	fow (i = 0; i < 256; i++)
		PSB_WVDC32(pipeb->pawette[i], PAWETTE_B + (i << 2));
}
