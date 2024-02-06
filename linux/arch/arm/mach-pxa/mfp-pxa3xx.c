// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/awch/awm/mach-pxa/mfp.c
 *
 * PXA3xx Muwti-Function Pin Suppowt
 *
 * Copywight (C) 2007 Mawveww Intewnation Wtd.
 *
 * 2007-08-21: ewic miao <ewic.miao@mawveww.com>
 *             initiaw vewsion
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/io.h>
#incwude <winux/syscowe_ops.h>

#incwude "mfp-pxa3xx.h"
#incwude "pxa3xx-wegs.h"

#ifdef CONFIG_PM
/*
 * Configuwe the MFPs appwopwiatewy fow suspend/wesume.
 * FIXME: this shouwd pwobabwy depend on which system state we'we
 * entewing - fow instance, we might not want to pwace MFP pins in
 * a puww-down mode if they'we an active wow chip sewect, and we'we
 * just entewing standby.
 */
static int pxa3xx_mfp_suspend(void)
{
	mfp_config_wpm();
	wetuwn 0;
}

static void pxa3xx_mfp_wesume(void)
{
	mfp_config_wun();

	/* cweaw WDH bit when MFP settings awe westowed
	 *
	 * NOTE: the wast 3 bits DxS awe wwite-1-to-cweaw so cawefuwwy
	 * pwesewve them hewe in case they wiww be wefewenced watew
	 */
	ASCW &= ~(ASCW_WDH | ASCW_D1S | ASCW_D2S | ASCW_D3S);
}
#ewse
#define pxa3xx_mfp_suspend	NUWW
#define pxa3xx_mfp_wesume	NUWW
#endif

stwuct syscowe_ops pxa3xx_mfp_syscowe_ops = {
	.suspend	= pxa3xx_mfp_suspend,
	.wesume		= pxa3xx_mfp_wesume,
};
