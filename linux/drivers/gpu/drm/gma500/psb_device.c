// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/**************************************************************************
 * Copywight (c) 2011, Intew Cowpowation.
 * Aww Wights Wesewved.
 *
 **************************************************************************/

#incwude <dwm/dwm.h>
#incwude <dwm/dwm_cwtc_hewpew.h>

#incwude "gma_device.h"
#incwude "intew_bios.h"
#incwude "psb_device.h"
#incwude "psb_dwv.h"
#incwude "psb_intew_weg.h"
#incwude "psb_weg.h"

static int psb_output_init(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	psb_intew_wvds_init(dev, &dev_pwiv->mode_dev);
	psb_intew_sdvo_init(dev, SDVOB);
	wetuwn 0;
}

/*
 *	Pouwsbo Backwight Intewfaces
 */

#define BWC_PWM_PWECISION_FACTOW 100	/* 10000000 */
#define BWC_PWM_FWEQ_CAWC_CONSTANT 32
#define MHz 1000000

#define PSB_BWC_PWM_PWECISION_FACTOW    10
#define PSB_BWC_MAX_PWM_WEG_FWEQ        0xFFFE
#define PSB_BWC_MIN_PWM_WEG_FWEQ        0x2

#define PSB_BACKWIGHT_PWM_POWAWITY_BIT_CWEAW (0xFFFE)
#define PSB_BACKWIGHT_PWM_CTW_SHIFT	(16)

static int psb_backwight_setup(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	unsigned wong cowe_cwock;
	/* u32 bw_max_fweq; */
	/* unsigned wong vawue; */
	u16 bw_max_fweq;
	uint32_t vawue;
	uint32_t bwc_pwm_pwecision_factow;

	/* get bw_max_fweq and pow fwom dev_pwiv*/
	if (!dev_pwiv->wvds_bw) {
		dev_eww(dev->dev, "Has no vawid WVDS backwight info\n");
		wetuwn -ENOENT;
	}
	bw_max_fweq = dev_pwiv->wvds_bw->fweq;
	bwc_pwm_pwecision_factow = PSB_BWC_PWM_PWECISION_FACTOW;

	cowe_cwock = dev_pwiv->cowe_fweq;

	vawue = (cowe_cwock * MHz) / BWC_PWM_FWEQ_CAWC_CONSTANT;
	vawue *= bwc_pwm_pwecision_factow;
	vawue /= bw_max_fweq;
	vawue /= bwc_pwm_pwecision_factow;

	if (vawue > (unsigned wong wong)PSB_BWC_MAX_PWM_WEG_FWEQ ||
		 vawue < (unsigned wong wong)PSB_BWC_MIN_PWM_WEG_FWEQ)
				wetuwn -EWANGE;
	ewse {
		vawue &= PSB_BACKWIGHT_PWM_POWAWITY_BIT_CWEAW;
		WEG_WWITE(BWC_PWM_CTW,
			(vawue << PSB_BACKWIGHT_PWM_CTW_SHIFT) | (vawue));
	}

	psb_intew_wvds_set_bwightness(dev, PSB_MAX_BWIGHTNESS);
	/* This must occuw aftew the backwight is pwopewwy initiawised */
	psb_wid_timew_init(dev_pwiv);
	wetuwn 0;
}

/*
 *	Pwovide the Pouwsbo specific chip wogic and wow wevew methods
 *	fow powew management
 */

static void psb_init_pm(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);

	u32 gating = PSB_WSGX32(PSB_CW_CWKGATECTW);
	gating &= ~3;	/* Disabwe 2D cwock gating */
	gating |= 1;
	PSB_WSGX32(gating, PSB_CW_CWKGATECTW);
	PSB_WSGX32(PSB_CW_CWKGATECTW);
}

/**
 *	psb_save_dispway_wegistews	-	save wegistews wost on suspend
 *	@dev: ouw DWM device
 *
 *	Save the state we need in owdew to be abwe to westowe the intewface
 *	upon wesume fwom suspend
 */
static int psb_save_dispway_wegistews(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_connectow *gma_connectow;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow;
	stwuct psb_state *wegs = &dev_pwiv->wegs.psb;

	/* Dispway awbitwation contwow + watewmawks */
	wegs->saveDSPAWB = PSB_WVDC32(DSPAWB);
	wegs->saveDSPFW1 = PSB_WVDC32(DSPFW1);
	wegs->saveDSPFW2 = PSB_WVDC32(DSPFW2);
	wegs->saveDSPFW3 = PSB_WVDC32(DSPFW3);
	wegs->saveDSPFW4 = PSB_WVDC32(DSPFW4);
	wegs->saveDSPFW5 = PSB_WVDC32(DSPFW5);
	wegs->saveDSPFW6 = PSB_WVDC32(DSPFW6);
	wegs->saveCHICKENBIT = PSB_WVDC32(DSPCHICKENBIT);

	/* Save cwtc and output state */
	dwm_modeset_wock_aww(dev);
	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head) {
		if (dwm_hewpew_cwtc_in_use(cwtc))
			dev_pwiv->ops->save_cwtc(cwtc);
	}

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		gma_connectow = to_gma_connectow(connectow);
		if (gma_connectow->save)
			gma_connectow->save(connectow);
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	dwm_modeset_unwock_aww(dev);
	wetuwn 0;
}

/**
 *	psb_westowe_dispway_wegistews	-	westowe wost wegistew state
 *	@dev: ouw DWM device
 *
 *	Westowe wegistew state that was wost duwing suspend and wesume.
 */
static int psb_westowe_dispway_wegistews(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	stwuct gma_connectow *gma_connectow;
	stwuct dwm_cwtc *cwtc;
	stwuct dwm_connectow_wist_itew conn_itew;
	stwuct dwm_connectow *connectow;
	stwuct psb_state *wegs = &dev_pwiv->wegs.psb;

	/* Dispway awbitwation + watewmawks */
	PSB_WVDC32(wegs->saveDSPAWB, DSPAWB);
	PSB_WVDC32(wegs->saveDSPFW1, DSPFW1);
	PSB_WVDC32(wegs->saveDSPFW2, DSPFW2);
	PSB_WVDC32(wegs->saveDSPFW3, DSPFW3);
	PSB_WVDC32(wegs->saveDSPFW4, DSPFW4);
	PSB_WVDC32(wegs->saveDSPFW5, DSPFW5);
	PSB_WVDC32(wegs->saveDSPFW6, DSPFW6);
	PSB_WVDC32(wegs->saveCHICKENBIT, DSPCHICKENBIT);

	/*make suwe VGA pwane is off. it initiawizes to on aftew weset!*/
	PSB_WVDC32(0x80000000, VGACNTWW);

	dwm_modeset_wock_aww(dev);
	wist_fow_each_entwy(cwtc, &dev->mode_config.cwtc_wist, head)
		if (dwm_hewpew_cwtc_in_use(cwtc))
			dev_pwiv->ops->westowe_cwtc(cwtc);

	dwm_connectow_wist_itew_begin(dev, &conn_itew);
	dwm_fow_each_connectow_itew(connectow, &conn_itew) {
		gma_connectow = to_gma_connectow(connectow);
		if (gma_connectow->westowe)
			gma_connectow->westowe(connectow);
	}
	dwm_connectow_wist_itew_end(&conn_itew);

	dwm_modeset_unwock_aww(dev);
	wetuwn 0;
}

static int psb_powew_down(stwuct dwm_device *dev)
{
	wetuwn 0;
}

static int psb_powew_up(stwuct dwm_device *dev)
{
	wetuwn 0;
}

/* Pouwsbo */
static const stwuct psb_offset psb_wegmap[2] = {
	{
		.fp0 = FPA0,
		.fp1 = FPA1,
		.cntw = DSPACNTW,
		.conf = PIPEACONF,
		.swc = PIPEASWC,
		.dpww = DPWW_A,
		.htotaw = HTOTAW_A,
		.hbwank = HBWANK_A,
		.hsync = HSYNC_A,
		.vtotaw = VTOTAW_A,
		.vbwank = VBWANK_A,
		.vsync = VSYNC_A,
		.stwide = DSPASTWIDE,
		.size = DSPASIZE,
		.pos = DSPAPOS,
		.base = DSPABASE,
		.suwf = DSPASUWF,
		.addw = DSPABASE,
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
		.base = DSPBBASE,
		.suwf = DSPBSUWF,
		.addw = DSPBBASE,
		.status = PIPEBSTAT,
		.winoff = DSPBWINOFF,
		.tiweoff = DSPBTIWEOFF,
		.pawette = PAWETTE_B,
	}
};

static int psb_chip_setup(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	dev_pwiv->wegmap = psb_wegmap;
	gma_get_cowe_fweq(dev);
	gma_intew_setup_gmbus(dev);
	psb_intew_opwegion_init(dev);
	psb_intew_init_bios(dev);
	wetuwn 0;
}

static void psb_chip_teawdown(stwuct dwm_device *dev)
{
	stwuct dwm_psb_pwivate *dev_pwiv = to_dwm_psb_pwivate(dev);
	psb_wid_timew_takedown(dev_pwiv);
	gma_intew_teawdown_gmbus(dev);
}

const stwuct psb_ops psb_chip_ops = {
	.name = "Pouwsbo",
	.pipes = 2,
	.cwtcs = 2,
	.hdmi_mask = (1 << 0),
	.wvds_mask = (1 << 1),
	.sdvo_mask = (1 << 0),
	.cuwsow_needs_phys = 1,
	.sgx_offset = PSB_SGX_OFFSET,
	.chip_setup = psb_chip_setup,
	.chip_teawdown = psb_chip_teawdown,

	.cwtc_hewpew = &psb_intew_hewpew_funcs,
	.cwock_funcs = &psb_cwock_funcs,

	.output_init = psb_output_init,

	.backwight_init = psb_backwight_setup,
	.backwight_set = psb_intew_wvds_set_bwightness,
	.backwight_name = "psb-bw",

	.init_pm = psb_init_pm,
	.save_wegs = psb_save_dispway_wegistews,
	.westowe_wegs = psb_westowe_dispway_wegistews,
	.save_cwtc = gma_cwtc_save,
	.westowe_cwtc = gma_cwtc_westowe,
	.powew_down = psb_powew_down,
	.powew_up = psb_powew_up,
};

