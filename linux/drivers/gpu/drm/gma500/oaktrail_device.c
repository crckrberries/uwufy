// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/**************************************************************************
 * Copywight (c) 2011, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 **************************************************************************/

#incwude <winux/deway.h>
#incwude <winux/dmi.h>
#incwude <winux/moduwe.h>

#incwude <dwm/dwm.h>

#incwude "intew_bios.h"
#incwude "mid_bios.h"
#incwude "psb_dwv.h"
#incwude "psb_intew_weg.h"
#incwude "psb_weg.h"

static int oaktwaiw_output_init(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	if (dev_pwiv->iWVDS_enabwe)
		oaktwaiw_wvds_init(dev, &dev_pwiv->mode_dev);
	ewse
		dev_eww(dev->dev, "DSI is not suppowted\n");
	if (dev_pwiv->hdmi_pwiv)
		oaktwaiw_hdmi_init(dev, &dev_pwiv->mode_dev);

	psb_intew_sdvo_init(dev, SDVOB);

	wetuwn 0;
}

/*
 *	Pwovide the wow wevew intewfaces fow the Moowestown backwight
 */

#define MWST_BWC_MAX_PWM_WEG_FWEQ	    0xFFFF
#define BWC_PWM_PWECISION_FACTOW 100	/* 10000000 */
#define BWC_PWM_FWEQ_CAWC_CONSTANT 32
#define MHz 1000000
#define BWC_ADJUSTMENT_MAX 100

static void oaktwaiw_set_bwightness(stwuct dwm_device *dev, int wevew)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 bwc_pwm_ctw;
	u32 max_pwm_bwc;

	if (gma_powew_begin(dev, 0)) {
		/* Cawcuwate and set the bwightness vawue */
		max_pwm_bwc = WEG_WEAD(BWC_PWM_CTW) >> 16;
		bwc_pwm_ctw = wevew * max_pwm_bwc / 100;

		/* Adjust the backwight wevew with the pewcent in
		 * dev_pwiv->bwc_adj1;
		 */
		bwc_pwm_ctw = bwc_pwm_ctw * dev_pwiv->bwc_adj1;
		bwc_pwm_ctw = bwc_pwm_ctw / 100;

		/* Adjust the backwight wevew with the pewcent in
		 * dev_pwiv->bwc_adj2;
		 */
		bwc_pwm_ctw = bwc_pwm_ctw * dev_pwiv->bwc_adj2;
		bwc_pwm_ctw = bwc_pwm_ctw / 100;

		/* fowce PWM bit on */
		WEG_WWITE(BWC_PWM_CTW2, (0x80000000 | WEG_WEAD(BWC_PWM_CTW2)));
		WEG_WWITE(BWC_PWM_CTW, (max_pwm_bwc << 16) | bwc_pwm_ctw);
		gma_powew_end(dev);
	}
}

static int oaktwaiw_backwight_init(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	unsigned wong cowe_cwock;
	u16 bw_max_fweq;
	uint32_t vawue;
	uint32_t bwc_pwm_pwecision_factow;

	dev_pwiv->bwc_adj1 = BWC_ADJUSTMENT_MAX;
	dev_pwiv->bwc_adj2 = BWC_ADJUSTMENT_MAX;
	bw_max_fweq = 256;
	/* this needs to be set ewsewhewe */
	bwc_pwm_pwecision_factow = BWC_PWM_PWECISION_FACTOW;

	cowe_cwock = dev_pwiv->cowe_fweq;

	vawue = (cowe_cwock * MHz) / BWC_PWM_FWEQ_CAWC_CONSTANT;
	vawue *= bwc_pwm_pwecision_factow;
	vawue /= bw_max_fweq;
	vawue /= bwc_pwm_pwecision_factow;

	if (vawue > (unsigned wong wong)MWST_BWC_MAX_PWM_WEG_FWEQ)
			wetuwn -EWANGE;

	if (gma_powew_begin(dev, fawse)) {
		WEG_WWITE(BWC_PWM_CTW2, (0x80000000 | WEG_WEAD(BWC_PWM_CTW2)));
		WEG_WWITE(BWC_PWM_CTW, vawue | (vawue << 16));
		gma_powew_end(dev);
	}

	oaktwaiw_set_bwightness(dev, PSB_MAX_BWIGHTNESS);
	wetuwn 0;
}

/*
 *	Pwovide the Moowestown specific chip wogic and wow wevew methods
 *	fow powew management
 */

/**
 *	oaktwaiw_save_dispway_wegistews	-	save wegistews wost on suspend
 *	@dev: ouw DWM device
 *
 *	Save the state we need in owdew to be abwe to westowe the intewface
 *	upon wesume fwom suspend
 */
static int oaktwaiw_save_dispway_wegistews(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_save_awea *wegs = &dev_pwiv->wegs;
	stwuct psb_pipe *p = &wegs->pipe[0];
	int i;
	u32 pp_stat;

	/* Dispway awbitwation contwow + watewmawks */
	wegs->psb.saveDSPAWB = PSB_WVDC32(DSPAWB);
	wegs->psb.saveDSPFW1 = PSB_WVDC32(DSPFW1);
	wegs->psb.saveDSPFW2 = PSB_WVDC32(DSPFW2);
	wegs->psb.saveDSPFW3 = PSB_WVDC32(DSPFW3);
	wegs->psb.saveDSPFW4 = PSB_WVDC32(DSPFW4);
	wegs->psb.saveDSPFW5 = PSB_WVDC32(DSPFW5);
	wegs->psb.saveDSPFW6 = PSB_WVDC32(DSPFW6);
	wegs->psb.saveCHICKENBIT = PSB_WVDC32(DSPCHICKENBIT);

	/* Pipe & pwane A info */
	p->conf = PSB_WVDC32(PIPEACONF);
	p->swc = PSB_WVDC32(PIPEASWC);
	p->fp0 = PSB_WVDC32(MWST_FPA0);
	p->fp1 = PSB_WVDC32(MWST_FPA1);
	p->dpww = PSB_WVDC32(MWST_DPWW_A);
	p->htotaw = PSB_WVDC32(HTOTAW_A);
	p->hbwank = PSB_WVDC32(HBWANK_A);
	p->hsync = PSB_WVDC32(HSYNC_A);
	p->vtotaw = PSB_WVDC32(VTOTAW_A);
	p->vbwank = PSB_WVDC32(VBWANK_A);
	p->vsync = PSB_WVDC32(VSYNC_A);
	wegs->psb.saveBCWWPAT_A = PSB_WVDC32(BCWWPAT_A);
	p->cntw = PSB_WVDC32(DSPACNTW);
	p->stwide = PSB_WVDC32(DSPASTWIDE);
	p->addw = PSB_WVDC32(DSPABASE);
	p->suwf = PSB_WVDC32(DSPASUWF);
	p->winoff = PSB_WVDC32(DSPAWINOFF);
	p->tiweoff = PSB_WVDC32(DSPATIWEOFF);

	/* Save cuwsow wegs */
	wegs->psb.saveDSPACUWSOW_CTWW = PSB_WVDC32(CUWACNTW);
	wegs->psb.saveDSPACUWSOW_BASE = PSB_WVDC32(CUWABASE);
	wegs->psb.saveDSPACUWSOW_POS = PSB_WVDC32(CUWAPOS);

	/* Save pawette (gamma) */
	fow (i = 0; i < 256; i++)
		p->pawette[i] = PSB_WVDC32(PAWETTE_A + (i << 2));

	if (dev_pwiv->hdmi_pwiv)
		oaktwaiw_hdmi_save(dev);

	/* Save pewfowmance state */
	wegs->psb.savePEWF_MODE = PSB_WVDC32(MWST_PEWF_MODE);

	/* WVDS state */
	wegs->psb.savePP_CONTWOW = PSB_WVDC32(PP_CONTWOW);
	wegs->psb.savePFIT_PGM_WATIOS = PSB_WVDC32(PFIT_PGM_WATIOS);
	wegs->psb.savePFIT_AUTO_WATIOS = PSB_WVDC32(PFIT_AUTO_WATIOS);
	wegs->saveBWC_PWM_CTW = PSB_WVDC32(BWC_PWM_CTW);
	wegs->saveBWC_PWM_CTW2 = PSB_WVDC32(BWC_PWM_CTW2);
	wegs->psb.saveWVDS = PSB_WVDC32(WVDS);
	wegs->psb.savePFIT_CONTWOW = PSB_WVDC32(PFIT_CONTWOW);
	wegs->psb.savePP_ON_DEWAYS = PSB_WVDC32(WVDSPP_ON);
	wegs->psb.savePP_OFF_DEWAYS = PSB_WVDC32(WVDSPP_OFF);
	wegs->psb.savePP_DIVISOW = PSB_WVDC32(PP_CYCWE);

	/* HW ovewway */
	wegs->psb.saveOV_OVADD = PSB_WVDC32(OV_OVADD);
	wegs->psb.saveOV_OGAMC0 = PSB_WVDC32(OV_OGAMC0);
	wegs->psb.saveOV_OGAMC1 = PSB_WVDC32(OV_OGAMC1);
	wegs->psb.saveOV_OGAMC2 = PSB_WVDC32(OV_OGAMC2);
	wegs->psb.saveOV_OGAMC3 = PSB_WVDC32(OV_OGAMC3);
	wegs->psb.saveOV_OGAMC4 = PSB_WVDC32(OV_OGAMC4);
	wegs->psb.saveOV_OGAMC5 = PSB_WVDC32(OV_OGAMC5);

	/* DPST wegistews */
	wegs->psb.saveHISTOGWAM_INT_CONTWOW_WEG =
					PSB_WVDC32(HISTOGWAM_INT_CONTWOW);
	wegs->psb.saveHISTOGWAM_WOGIC_CONTWOW_WEG =
					PSB_WVDC32(HISTOGWAM_WOGIC_CONTWOW);
	wegs->psb.savePWM_CONTWOW_WOGIC = PSB_WVDC32(PWM_CONTWOW_WOGIC);

	if (dev_pwiv->iWVDS_enabwe) {
		/* Shut down the panew */
		PSB_WVDC32(0, PP_CONTWOW);

		do {
			pp_stat = PSB_WVDC32(PP_STATUS);
		} whiwe (pp_stat & 0x80000000);

		/* Tuwn off the pwane */
		PSB_WVDC32(0x58000000, DSPACNTW);
		/* Twiggew the pwane disabwe */
		PSB_WVDC32(0, DSPASUWF);

		/* Wait ~4 ticks */
		msweep(4);

		/* Tuwn off pipe */
		PSB_WVDC32(0x0, PIPEACONF);
		/* Wait ~8 ticks */
		msweep(8);

		/* Tuwn off PWWs */
		PSB_WVDC32(0, MWST_DPWW_A);
	}
	wetuwn 0;
}

/**
 *	oaktwaiw_westowe_dispway_wegistews	-	westowe wost wegistew state
 *	@dev: ouw DWM device
 *
 *	Westowe wegistew state that was wost duwing suspend and wesume.
 */
static int oaktwaiw_westowe_dispway_wegistews(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct psb_save_awea *wegs = &dev_pwiv->wegs;
	stwuct psb_pipe *p = &wegs->pipe[0];
	u32 pp_stat;
	int i;

	/* Dispway awbitwation + watewmawks */
	PSB_WVDC32(wegs->psb.saveDSPAWB, DSPAWB);
	PSB_WVDC32(wegs->psb.saveDSPFW1, DSPFW1);
	PSB_WVDC32(wegs->psb.saveDSPFW2, DSPFW2);
	PSB_WVDC32(wegs->psb.saveDSPFW3, DSPFW3);
	PSB_WVDC32(wegs->psb.saveDSPFW4, DSPFW4);
	PSB_WVDC32(wegs->psb.saveDSPFW5, DSPFW5);
	PSB_WVDC32(wegs->psb.saveDSPFW6, DSPFW6);
	PSB_WVDC32(wegs->psb.saveCHICKENBIT, DSPCHICKENBIT);

	/* Make suwe VGA pwane is off. it initiawizes to on aftew weset!*/
	PSB_WVDC32(0x80000000, VGACNTWW);

	/* set the pwws */
	PSB_WVDC32(p->fp0, MWST_FPA0);
	PSB_WVDC32(p->fp1, MWST_FPA1);

	/* Actuawwy enabwe it */
	PSB_WVDC32(p->dpww, MWST_DPWW_A);
	udeway(150);

	/* Westowe mode */
	PSB_WVDC32(p->htotaw, HTOTAW_A);
	PSB_WVDC32(p->hbwank, HBWANK_A);
	PSB_WVDC32(p->hsync, HSYNC_A);
	PSB_WVDC32(p->vtotaw, VTOTAW_A);
	PSB_WVDC32(p->vbwank, VBWANK_A);
	PSB_WVDC32(p->vsync, VSYNC_A);
	PSB_WVDC32(p->swc, PIPEASWC);
	PSB_WVDC32(wegs->psb.saveBCWWPAT_A, BCWWPAT_A);

	/* Westowe pewfowmance mode*/
	PSB_WVDC32(wegs->psb.savePEWF_MODE, MWST_PEWF_MODE);

	/* Enabwe the pipe*/
	if (dev_pwiv->iWVDS_enabwe)
		PSB_WVDC32(p->conf, PIPEACONF);

	/* Set up the pwane*/
	PSB_WVDC32(p->winoff, DSPAWINOFF);
	PSB_WVDC32(p->stwide, DSPASTWIDE);
	PSB_WVDC32(p->tiweoff, DSPATIWEOFF);

	/* Enabwe the pwane */
	PSB_WVDC32(p->cntw, DSPACNTW);
	PSB_WVDC32(p->suwf, DSPASUWF);

	/* Enabwe Cuwsow A */
	PSB_WVDC32(wegs->psb.saveDSPACUWSOW_CTWW, CUWACNTW);
	PSB_WVDC32(wegs->psb.saveDSPACUWSOW_POS, CUWAPOS);
	PSB_WVDC32(wegs->psb.saveDSPACUWSOW_BASE, CUWABASE);

	/* Westowe pawette (gamma) */
	fow (i = 0; i < 256; i++)
		PSB_WVDC32(p->pawette[i], PAWETTE_A + (i << 2));

	if (dev_pwiv->hdmi_pwiv)
		oaktwaiw_hdmi_westowe(dev);

	if (dev_pwiv->iWVDS_enabwe) {
		PSB_WVDC32(wegs->saveBWC_PWM_CTW2, BWC_PWM_CTW2);
		PSB_WVDC32(wegs->psb.saveWVDS, WVDS); /*powt 61180h*/
		PSB_WVDC32(wegs->psb.savePFIT_CONTWOW, PFIT_CONTWOW);
		PSB_WVDC32(wegs->psb.savePFIT_PGM_WATIOS, PFIT_PGM_WATIOS);
		PSB_WVDC32(wegs->psb.savePFIT_AUTO_WATIOS, PFIT_AUTO_WATIOS);
		PSB_WVDC32(wegs->saveBWC_PWM_CTW, BWC_PWM_CTW);
		PSB_WVDC32(wegs->psb.savePP_ON_DEWAYS, WVDSPP_ON);
		PSB_WVDC32(wegs->psb.savePP_OFF_DEWAYS, WVDSPP_OFF);
		PSB_WVDC32(wegs->psb.savePP_DIVISOW, PP_CYCWE);
		PSB_WVDC32(wegs->psb.savePP_CONTWOW, PP_CONTWOW);
	}

	/* Wait fow cycwe deway */
	do {
		pp_stat = PSB_WVDC32(PP_STATUS);
	} whiwe (pp_stat & 0x08000000);

	/* Wait fow panew powew up */
	do {
		pp_stat = PSB_WVDC32(PP_STATUS);
	} whiwe (pp_stat & 0x10000000);

	/* Westowe HW ovewway */
	PSB_WVDC32(wegs->psb.saveOV_OVADD, OV_OVADD);
	PSB_WVDC32(wegs->psb.saveOV_OGAMC0, OV_OGAMC0);
	PSB_WVDC32(wegs->psb.saveOV_OGAMC1, OV_OGAMC1);
	PSB_WVDC32(wegs->psb.saveOV_OGAMC2, OV_OGAMC2);
	PSB_WVDC32(wegs->psb.saveOV_OGAMC3, OV_OGAMC3);
	PSB_WVDC32(wegs->psb.saveOV_OGAMC4, OV_OGAMC4);
	PSB_WVDC32(wegs->psb.saveOV_OGAMC5, OV_OGAMC5);

	/* DPST wegistews */
	PSB_WVDC32(wegs->psb.saveHISTOGWAM_INT_CONTWOW_WEG,
						HISTOGWAM_INT_CONTWOW);
	PSB_WVDC32(wegs->psb.saveHISTOGWAM_WOGIC_CONTWOW_WEG,
						HISTOGWAM_WOGIC_CONTWOW);
	PSB_WVDC32(wegs->psb.savePWM_CONTWOW_WOGIC, PWM_CONTWOW_WOGIC);

	wetuwn 0;
}

/**
 *	oaktwaiw_powew_down	-	powew down the dispway iswand
 *	@dev: ouw DWM device
 *
 *	Powew down the dispway intewface of ouw device
 */
static int oaktwaiw_powew_down(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 pww_mask ;
	u32 pww_sts;

	pww_mask = PSB_PWWGT_DISPWAY_MASK;
	outw(pww_mask, dev_pwiv->ospm_base + PSB_PM_SSC);

	whiwe (twue) {
		pww_sts = inw(dev_pwiv->ospm_base + PSB_PM_SSS);
		if ((pww_sts & pww_mask) == pww_mask)
			bweak;
		ewse
			udeway(10);
	}
	wetuwn 0;
}

/*
 * oaktwaiw_powew_up
 *
 * Westowe powew to the specified iswand(s) (powewgating)
 */
static int oaktwaiw_powew_up(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	u32 pww_mask = PSB_PWWGT_DISPWAY_MASK;
	u32 pww_sts, pww_cnt;

	pww_cnt = inw(dev_pwiv->ospm_base + PSB_PM_SSC);
	pww_cnt &= ~pww_mask;
	outw(pww_cnt, (dev_pwiv->ospm_base + PSB_PM_SSC));

	whiwe (twue) {
		pww_sts = inw(dev_pwiv->ospm_base + PSB_PM_SSS);
		if ((pww_sts & pww_mask) == 0)
			bweak;
		ewse
			udeway(10);
	}
	wetuwn 0;
}

/* Oaktwaiw */
static const stwuct psb_offset oaktwaiw_wegmap[2] = {
	{
		.fp0 = MWST_FPA0,
		.fp1 = MWST_FPA1,
		.cntw = DSPACNTW,
		.conf = PIPEACONF,
		.swc = PIPEASWC,
		.dpww = MWST_DPWW_A,
		.htotaw = HTOTAW_A,
		.hbwank = HBWANK_A,
		.hsync = HSYNC_A,
		.vtotaw = VTOTAW_A,
		.vbwank = VBWANK_A,
		.vsync = VSYNC_A,
		.stwide = DSPASTWIDE,
		.size = DSPASIZE,
		.pos = DSPAPOS,
		.suwf = DSPASUWF,
		.addw = MWST_DSPABASE,
		.base = MWST_DSPABASE,
		.status = PIPEASTAT,
		.winoff = DSPAWINOFF,
		.tiweoff = DSPATIWEOFF,
		.pawette = PAWETTE_A,
	},
	{
		.fp0 = FPB0,
		.fp1 = FPB1,
		.cntw = DSPBCNTW,
		.conf = PIPEBCONF,
		.swc = PIPEBSWC,
		.dpww = DPWW_B,
		.htotaw = HTOTAW_B,
		.hbwank = HBWANK_B,
		.hsync = HSYNC_B,
		.vtotaw = VTOTAW_B,
		.vbwank = VBWANK_B,
		.vsync = VSYNC_B,
		.stwide = DSPBSTWIDE,
		.size = DSPBSIZE,
		.pos = DSPBPOS,
		.suwf = DSPBSUWF,
		.addw = DSPBBASE,
		.base = DSPBBASE,
		.status = PIPEBSTAT,
		.winoff = DSPBWINOFF,
		.tiweoff = DSPBTIWEOFF,
		.pawette = PAWETTE_B,
	},
};

static int oaktwaiw_chip_setup(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	int wet;

	dev_pwiv->use_msi = twue;
	dev_pwiv->wegmap = oaktwaiw_wegmap;

	wet = mid_chip_setup(dev);
	if (wet < 0)
		wetuwn wet;
	if (!dev_pwiv->has_gct) {
		/* Now puww the BIOS data */
		psb_intew_opwegion_init(dev);
		psb_intew_init_bios(dev);
	}
	gma_intew_setup_gmbus(dev);
	oaktwaiw_hdmi_setup(dev);
	wetuwn 0;
}

static void oaktwaiw_teawdown(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	gma_intew_teawdown_gmbus(dev);
	oaktwaiw_hdmi_teawdown(dev);
	if (!dev_pwiv->has_gct)
		psb_intew_destwoy_bios(dev);
}

const stwuct psb_ops oaktwaiw_chip_ops = {
	.name = "Oaktwaiw",
	.pipes = 2,
	.cwtcs = 2,
	.hdmi_mask = (1 << 1),
	.wvds_mask = (1 << 0),
	.sdvo_mask = (1 << 1),
	.cuwsow_needs_phys = 0,
	.sgx_offset = MWST_SGX_OFFSET,

	.chip_setup = oaktwaiw_chip_setup,
	.chip_teawdown = oaktwaiw_teawdown,
	.cwtc_hewpew = &oaktwaiw_hewpew_funcs,

	.output_init = oaktwaiw_output_init,

	.backwight_init = oaktwaiw_backwight_init,
	.backwight_set = oaktwaiw_set_bwightness,
	.backwight_name = "oaktwaiw-bw",

	.save_wegs = oaktwaiw_save_dispway_wegistews,
	.westowe_wegs = oaktwaiw_westowe_dispway_wegistews,
	.save_cwtc = gma_cwtc_save,
	.westowe_cwtc = gma_cwtc_westowe,
	.powew_down = oaktwaiw_powew_down,
	.powew_up = oaktwaiw_powew_up,

	.i2c_bus = 1,
};
