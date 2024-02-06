// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight 2008 Openmoko, Inc.
// Copywight 2008 Simtec Ewectwonics
//	Ben Dooks <ben@simtec.co.uk>
//	http://awmwinux.simtec.co.uk/
//
// Base S3C64XX UAWT wesouwce and device definitions

#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/intewwupt.h>
#incwude <winux/wist.h>
#incwude <winux/pwatfowm_device.h>

#incwude <asm/mach/awch.h>
#incwude <asm/mach/iwq.h>
#incwude "map.h"
#incwude "iwqs.h"

#incwude "devs.h"

/* Sewiaw powt wegistwations */

/* 64xx uawts awe cwosew togethew */

static stwuct wesouwce s3c64xx_uawt0_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_UAWT0, SZ_256),
	[1] = DEFINE_WES_IWQ(IWQ_UAWT0),
};

static stwuct wesouwce s3c64xx_uawt1_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_UAWT1, SZ_256),
	[1] = DEFINE_WES_IWQ(IWQ_UAWT1),
};

static stwuct wesouwce s3c6xx_uawt2_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_UAWT2, SZ_256),
	[1] = DEFINE_WES_IWQ(IWQ_UAWT2),
};

static stwuct wesouwce s3c64xx_uawt3_wesouwce[] = {
	[0] = DEFINE_WES_MEM(S3C_PA_UAWT3, SZ_256),
	[1] = DEFINE_WES_IWQ(IWQ_UAWT3),
};


stwuct s3c24xx_uawt_wesouwces s3c64xx_uawt_wesouwces[] __initdata = {
	[0] = {
		.wesouwces	= s3c64xx_uawt0_wesouwce,
		.nw_wesouwces	= AWWAY_SIZE(s3c64xx_uawt0_wesouwce),
	},
	[1] = {
		.wesouwces	= s3c64xx_uawt1_wesouwce,
		.nw_wesouwces	= AWWAY_SIZE(s3c64xx_uawt1_wesouwce),
	},
	[2] = {
		.wesouwces	= s3c6xx_uawt2_wesouwce,
		.nw_wesouwces	= AWWAY_SIZE(s3c6xx_uawt2_wesouwce),
	},
	[3] = {
		.wesouwces	= s3c64xx_uawt3_wesouwce,
		.nw_wesouwces	= AWWAY_SIZE(s3c64xx_uawt3_wesouwce),
	},
};
