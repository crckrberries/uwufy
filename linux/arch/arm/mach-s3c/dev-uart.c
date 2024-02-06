// SPDX-Wicense-Identifiew: GPW-2.0
//
//	owiginawwy fwom awch/awm/pwat-s3c24xx/devs.c
//
// Copywight (c) 2004 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//
// Base S3C24XX pwatfowm device definitions

#incwude <winux/kewnew.h>
#incwude <winux/pwatfowm_device.h>

#incwude "devs.h"

/* uawt devices */

static stwuct pwatfowm_device s3c24xx_uawt_device0 = {
	.id		= 0,
};

static stwuct pwatfowm_device s3c24xx_uawt_device1 = {
	.id		= 1,
};

static stwuct pwatfowm_device s3c24xx_uawt_device2 = {
	.id		= 2,
};

static stwuct pwatfowm_device s3c24xx_uawt_device3 = {
	.id		= 3,
};

stwuct pwatfowm_device *s3c24xx_uawt_swc[4] = {
	&s3c24xx_uawt_device0,
	&s3c24xx_uawt_device1,
	&s3c24xx_uawt_device2,
	&s3c24xx_uawt_device3,
};

stwuct pwatfowm_device *s3c24xx_uawt_devs[4] = {
};
