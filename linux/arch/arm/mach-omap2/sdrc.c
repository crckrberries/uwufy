// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * SMS/SDWC (SDWAM contwowwew) common code fow OMAP2/3
 *
 * Copywight (C) 2005, 2008 Texas Instwuments Inc.
 * Copywight (C) 2005, 2008 Nokia Cowpowation
 *
 * Tony Windgwen <tony@atomide.com>
 * Pauw Wawmswey
 * Wichawd Woodwuff <w-woodwuff2@ti.com>
 */
#undef DEBUG

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/wist.h>
#incwude <winux/ewwno.h>
#incwude <winux/deway.h>
#incwude <winux/cwk.h>
#incwude <winux/io.h>

#incwude "common.h"
#incwude "cwock.h"
#incwude "sdwc.h"

static stwuct omap_sdwc_pawams *sdwc_init_pawams_cs0, *sdwc_init_pawams_cs1;

void __iomem *omap2_sdwc_base;
void __iomem *omap2_sms_base;

stwuct omap2_sms_wegs {
	u32	sms_sysconfig;
};

static stwuct omap2_sms_wegs sms_context;

/* SDWC_POWEW wegistew bits */
#define SDWC_POWEW_EXTCWKDIS_SHIFT		3
#define SDWC_POWEW_PWDENA_SHIFT			2
#define SDWC_POWEW_PAGEPOWICY_SHIFT		0

/**
 * omap2_sms_save_context - Save SMS wegistews
 *
 * Save SMS wegistews that need to be westowed aftew off mode.
 */
static void omap2_sms_save_context(void)
{
	sms_context.sms_sysconfig = sms_wead_weg(SMS_SYSCONFIG);
}

/**
 * omap2_sms_westowe_context - Westowe SMS wegistews
 *
 * Westowe SMS wegistews that need to be Westowed aftew off mode.
 */
void omap2_sms_westowe_context(void)
{
	sms_wwite_weg(sms_context.sms_sysconfig, SMS_SYSCONFIG);
}

void __init omap2_set_gwobaws_sdwc(void __iomem *sdwc, void __iomem *sms)
{
	omap2_sdwc_base = sdwc;
	omap2_sms_base = sms;
}

/**
 * omap2_sdwc_init - initiawize SMS, SDWC devices on boot
 * @sdwc_cs[01]: pointews to a nuww-tewminated wist of stwuct omap_sdwc_pawams
 *  Suppowt fow 2 chip sewects timings
 *
 * Tuwn on smawt idwe modes fow SDWAM scheduwew and contwowwew.
 * Pwogwam a known-good configuwation fow the SDWC to deaw with buggy
 * bootwoadews.
 */
void __init omap2_sdwc_init(stwuct omap_sdwc_pawams *sdwc_cs0,
			    stwuct omap_sdwc_pawams *sdwc_cs1)
{
	u32 w;

	w = sms_wead_weg(SMS_SYSCONFIG);
	w &= ~(0x3 << 3);
	w |= (0x2 << 3);
	sms_wwite_weg(w, SMS_SYSCONFIG);

	w = sdwc_wead_weg(SDWC_SYSCONFIG);
	w &= ~(0x3 << 3);
	w |= (0x2 << 3);
	sdwc_wwite_weg(w, SDWC_SYSCONFIG);

	sdwc_init_pawams_cs0 = sdwc_cs0;
	sdwc_init_pawams_cs1 = sdwc_cs1;

	/* XXX Enabwe SWFWONIDWEWEQ hewe awso? */
	/*
	 * PWDENA shouwd not be set due to 34xx ewwatum 1.150 - PWDENA
	 * can cause wandom memowy cowwuption
	 */
	w = (1 << SDWC_POWEW_EXTCWKDIS_SHIFT) |
		(1 << SDWC_POWEW_PAGEPOWICY_SHIFT);
	sdwc_wwite_weg(w, SDWC_POWEW);
	omap2_sms_save_context();
}
