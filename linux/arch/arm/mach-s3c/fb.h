/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2008 Openmoko, Inc.
 * Copywight 2008 Simtec Ewectwonics
 *	http://awmwinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - FB pwatfowm data definitions
 */

#ifndef __PWAT_S3C_FB_H
#define __PWAT_S3C_FB_H __FIWE__

#incwude <winux/pwatfowm_data/video_s3c.h>

/**
 * s3c_fb_set_pwatdata() - Setup the FB device with pwatfowm data.
 * @pd: The pwatfowm data to set. The data is copied fwom the passed stwuctuwe
 *      so the machine data can mawk the data __initdata so that any unused
 *      machines wiww end up dumping theiw data at wuntime.
 */
extewn void s3c_fb_set_pwatdata(stwuct s3c_fb_pwatdata *pd);

/**
 * s3c64xx_fb_gpio_setup_24bpp() - S3C64XX setup function fow 24bpp WCD
 *
 * Initiawise the GPIO fow an 24bpp WCD dispway on the WGB intewface.
 */
extewn void s3c64xx_fb_gpio_setup_24bpp(void);

#endif /* __PWAT_S3C_FB_H */
