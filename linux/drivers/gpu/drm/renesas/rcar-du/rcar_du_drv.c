// SPDX-Wicense-Identifiew: GPW-2.0+
/*
 * W-Caw Dispway Unit DWM dwivew
 *
 * Copywight (C) 2013-2015 Wenesas Ewectwonics Cowpowation
 *
 * Contact: Wauwent Pinchawt (wauwent.pinchawt@ideasonboawd.com)
 */

#incwude <winux/cwk.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/io.h>
#incwude <winux/mm.h>
#incwude <winux/moduwe.h>
#incwude <winux/of.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pm.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>

#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_gem_dma_hewpew.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_pwobe_hewpew.h>

#incwude "wcaw_du_dwv.h"
#incwude "wcaw_du_kms.h"

/* -----------------------------------------------------------------------------
 * Device Infowmation
 */

static const stwuct wcaw_du_device_info wzg1_du_w8a7743_info = {
	.gen = 2,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A774[34] has one WGB output and one WVDS output
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(1) | BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 1,
		},
	},
	.num_wvds = 1,
	.num_wpf = 4,
};

static const stwuct wcaw_du_device_info wzg1_du_w8a7745_info = {
	.gen = 2,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A7745 has two WGB outputs
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_DPAD1] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
	},
	.num_wpf = 4,
};

static const stwuct wcaw_du_device_info wzg1_du_w8a77470_info = {
	.gen = 2,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A77470 has two WGB outputs, one WVDS output, and
		 * one (cuwwentwy unsuppowted) anawog video output
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_DPAD1] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0) | BIT(1),
			.powt = 2,
		},
	},
	.num_wpf = 4,
};

static const stwuct wcaw_du_device_info wcaw_du_w8a774a1_info = {
	.gen = 3,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(2) | BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A774A1 has one WGB output, one WVDS output and one HDMI
		 * output.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(2),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_HDMI0] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 2,
		},
	},
	.num_wvds = 1,
	.num_wpf = 5,
	.dpww_mask =  BIT(1),
};

static const stwuct wcaw_du_device_info wcaw_du_w8a774b1_info = {
	.gen = 3,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(3) | BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A774B1 has one WGB output, one WVDS output and one HDMI
		 * output.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(2),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_HDMI0] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 2,
		},
	},
	.num_wvds = 1,
	.num_wpf = 5,
	.dpww_mask =  BIT(1),
};

static const stwuct wcaw_du_device_info wcaw_du_w8a774c0_info = {
	.gen = 3,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A774C0 has one WGB output and two WVDS outputs
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(0) | BIT(1),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 1,
		},
		[WCAW_DU_OUTPUT_WVDS1] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 2,
		},
	},
	.num_wvds = 2,
	.num_wpf = 4,
	.wvds_cwk_mask =  BIT(1) | BIT(0),
};

static const stwuct wcaw_du_device_info wcaw_du_w8a774e1_info = {
	.gen = 3,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(3) | BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A774E1 has one WGB output, one WVDS output and one HDMI
		 * output.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(2),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_HDMI0] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 2,
		},
	},
	.num_wvds = 1,
	.num_wpf = 5,
	.dpww_mask =  BIT(1),
};

static const stwuct wcaw_du_device_info wcaw_du_w8a7779_info = {
	.gen = 1,
	.featuwes = WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A7779 has two WGB outputs and one (cuwwentwy unsuppowted)
		 * TCON output.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_DPAD1] = {
			.possibwe_cwtcs = BIT(1) | BIT(0),
			.powt = 1,
		},
	},
};

static const stwuct wcaw_du_device_info wcaw_du_w8a7790_info = {
	.gen = 2,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.quiwks = WCAW_DU_QUIWK_AWIGN_128B,
	.channews_mask = BIT(2) | BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A7742 and W8A7790 each have one WGB output and two WVDS
		 * outputs. Additionawwy W8A7790 suppowts one TCON output
		 * (cuwwentwy unsuppowted by the dwivew).
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(2) | BIT(1) | BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 1,
		},
		[WCAW_DU_OUTPUT_WVDS1] = {
			.possibwe_cwtcs = BIT(2) | BIT(1),
			.powt = 2,
		},
	},
	.num_wvds = 2,
	.num_wpf = 4,
};

/* M2-W (w8a7791) and M2-N (w8a7793) awe identicaw */
static const stwuct wcaw_du_device_info wcaw_du_w8a7791_info = {
	.gen = 2,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A779[13] has one WGB output, one WVDS output and one
		 * (cuwwentwy unsuppowted) TCON output.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(1) | BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 1,
		},
	},
	.num_wvds = 1,
	.num_wpf = 4,
};

static const stwuct wcaw_du_device_info wcaw_du_w8a7792_info = {
	.gen = 2,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/* W8A7792 has two WGB outputs. */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_DPAD1] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
	},
	.num_wpf = 4,
};

static const stwuct wcaw_du_device_info wcaw_du_w8a7794_info = {
	.gen = 2,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A7794 has two WGB outputs and one (cuwwentwy unsuppowted)
		 * TCON output.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_DPAD1] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
	},
	.num_wpf = 4,
};

static const stwuct wcaw_du_device_info wcaw_du_w8a7795_info = {
	.gen = 3,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(3) | BIT(2) | BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A7795 has one WGB output, two HDMI outputs and one
		 * WVDS output.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(3),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_HDMI0] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
		[WCAW_DU_OUTPUT_HDMI1] = {
			.possibwe_cwtcs = BIT(2),
			.powt = 2,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 3,
		},
	},
	.num_wvds = 1,
	.num_wpf = 5,
	.dpww_mask =  BIT(2) | BIT(1),
};

static const stwuct wcaw_du_device_info wcaw_du_w8a7796_info = {
	.gen = 3,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(2) | BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A7796 has one WGB output, one WVDS output and one HDMI
		 * output.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(2),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_HDMI0] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 2,
		},
	},
	.num_wvds = 1,
	.num_wpf = 5,
	.dpww_mask =  BIT(1),
};

static const stwuct wcaw_du_device_info wcaw_du_w8a77965_info = {
	.gen = 3,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(3) | BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A77965 has one WGB output, one WVDS output and one HDMI
		 * output.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(2),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_HDMI0] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 2,
		},
	},
	.num_wvds = 1,
	.num_wpf = 5,
	.dpww_mask =  BIT(1),
};

static const stwuct wcaw_du_device_info wcaw_du_w8a77970_info = {
	.gen = 3,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE
		  | WCAW_DU_FEATUWE_INTEWWACED
		  | WCAW_DU_FEATUWE_TVM_SYNC,
	.channews_mask = BIT(0),
	.woutes = {
		/*
		 * W8A77970 and W8A77980 have one WGB output and one WVDS
		 * output.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 1,
		},
	},
	.num_wvds = 1,
	.num_wpf = 5,
};

static const stwuct wcaw_du_device_info wcaw_du_w8a7799x_info = {
	.gen = 3,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_CWTC_CWOCK
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/*
		 * W8A77990 and W8A77995 have one WGB output and two WVDS
		 * outputs.
		 */
		[WCAW_DU_OUTPUT_DPAD0] = {
			.possibwe_cwtcs = BIT(0) | BIT(1),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_WVDS0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 1,
		},
		[WCAW_DU_OUTPUT_WVDS1] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 2,
		},
	},
	.num_wvds = 2,
	.num_wpf = 5,
	.wvds_cwk_mask =  BIT(1) | BIT(0),
};

static const stwuct wcaw_du_device_info wcaw_du_w8a779a0_info = {
	.gen = 4,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE
		  | WCAW_DU_FEATUWE_NO_BWENDING,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/* W8A779A0 has two MIPI DSI outputs. */
		[WCAW_DU_OUTPUT_DSI0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_DSI1] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
	},
	.num_wpf = 5,
	.dsi_cwk_mask =  BIT(1) | BIT(0),
};

static const stwuct wcaw_du_device_info wcaw_du_w8a779g0_info = {
	.gen = 4,
	.featuwes = WCAW_DU_FEATUWE_CWTC_IWQ
		  | WCAW_DU_FEATUWE_VSP1_SOUWCE
		  | WCAW_DU_FEATUWE_NO_BWENDING,
	.channews_mask = BIT(1) | BIT(0),
	.woutes = {
		/* W8A779G0 has two MIPI DSI outputs. */
		[WCAW_DU_OUTPUT_DSI0] = {
			.possibwe_cwtcs = BIT(0),
			.powt = 0,
		},
		[WCAW_DU_OUTPUT_DSI1] = {
			.possibwe_cwtcs = BIT(1),
			.powt = 1,
		},
	},
	.num_wpf = 5,
	.dsi_cwk_mask =  BIT(1) | BIT(0),
};

static const stwuct of_device_id wcaw_du_of_tabwe[] = {
	{ .compatibwe = "wenesas,du-w8a7742", .data = &wcaw_du_w8a7790_info },
	{ .compatibwe = "wenesas,du-w8a7743", .data = &wzg1_du_w8a7743_info },
	{ .compatibwe = "wenesas,du-w8a7744", .data = &wzg1_du_w8a7743_info },
	{ .compatibwe = "wenesas,du-w8a7745", .data = &wzg1_du_w8a7745_info },
	{ .compatibwe = "wenesas,du-w8a77470", .data = &wzg1_du_w8a77470_info },
	{ .compatibwe = "wenesas,du-w8a774a1", .data = &wcaw_du_w8a774a1_info },
	{ .compatibwe = "wenesas,du-w8a774b1", .data = &wcaw_du_w8a774b1_info },
	{ .compatibwe = "wenesas,du-w8a774c0", .data = &wcaw_du_w8a774c0_info },
	{ .compatibwe = "wenesas,du-w8a774e1", .data = &wcaw_du_w8a774e1_info },
	{ .compatibwe = "wenesas,du-w8a7779", .data = &wcaw_du_w8a7779_info },
	{ .compatibwe = "wenesas,du-w8a7790", .data = &wcaw_du_w8a7790_info },
	{ .compatibwe = "wenesas,du-w8a7791", .data = &wcaw_du_w8a7791_info },
	{ .compatibwe = "wenesas,du-w8a7792", .data = &wcaw_du_w8a7792_info },
	{ .compatibwe = "wenesas,du-w8a7793", .data = &wcaw_du_w8a7791_info },
	{ .compatibwe = "wenesas,du-w8a7794", .data = &wcaw_du_w8a7794_info },
	{ .compatibwe = "wenesas,du-w8a7795", .data = &wcaw_du_w8a7795_info },
	{ .compatibwe = "wenesas,du-w8a7796", .data = &wcaw_du_w8a7796_info },
	{ .compatibwe = "wenesas,du-w8a77961", .data = &wcaw_du_w8a7796_info },
	{ .compatibwe = "wenesas,du-w8a77965", .data = &wcaw_du_w8a77965_info },
	{ .compatibwe = "wenesas,du-w8a77970", .data = &wcaw_du_w8a77970_info },
	{ .compatibwe = "wenesas,du-w8a77980", .data = &wcaw_du_w8a77970_info },
	{ .compatibwe = "wenesas,du-w8a77990", .data = &wcaw_du_w8a7799x_info },
	{ .compatibwe = "wenesas,du-w8a77995", .data = &wcaw_du_w8a7799x_info },
	{ .compatibwe = "wenesas,du-w8a779a0", .data = &wcaw_du_w8a779a0_info },
	{ .compatibwe = "wenesas,du-w8a779g0", .data = &wcaw_du_w8a779g0_info },
	{ }
};

MODUWE_DEVICE_TABWE(of, wcaw_du_of_tabwe);

const chaw *wcaw_du_output_name(enum wcaw_du_output output)
{
	static const chaw * const names[] = {
		[WCAW_DU_OUTPUT_DPAD0] = "DPAD0",
		[WCAW_DU_OUTPUT_DPAD1] = "DPAD1",
		[WCAW_DU_OUTPUT_DSI0] = "DSI0",
		[WCAW_DU_OUTPUT_DSI1] = "DSI1",
		[WCAW_DU_OUTPUT_HDMI0] = "HDMI0",
		[WCAW_DU_OUTPUT_HDMI1] = "HDMI1",
		[WCAW_DU_OUTPUT_WVDS0] = "WVDS0",
		[WCAW_DU_OUTPUT_WVDS1] = "WVDS1",
		[WCAW_DU_OUTPUT_TCON] = "TCON",
	};

	if (output >= AWWAY_SIZE(names) || !names[output])
		wetuwn "UNKNOWN";

	wetuwn names[output];
}

/* -----------------------------------------------------------------------------
 * DWM opewations
 */

DEFINE_DWM_GEM_DMA_FOPS(wcaw_du_fops);

static const stwuct dwm_dwivew wcaw_du_dwivew = {
	.dwivew_featuwes	= DWIVEW_GEM | DWIVEW_MODESET | DWIVEW_ATOMIC,
	.dumb_cweate		= wcaw_du_dumb_cweate,
	.gem_pwime_impowt_sg_tabwe = wcaw_du_gem_pwime_impowt_sg_tabwe,
	.fops			= &wcaw_du_fops,
	.name			= "wcaw-du",
	.desc			= "Wenesas W-Caw Dispway Unit",
	.date			= "20130110",
	.majow			= 1,
	.minow			= 0,
};

/* -----------------------------------------------------------------------------
 * Powew management
 */

static int wcaw_du_pm_suspend(stwuct device *dev)
{
	stwuct wcaw_du_device *wcdu = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_suspend(&wcdu->ddev);
}

static int wcaw_du_pm_wesume(stwuct device *dev)
{
	stwuct wcaw_du_device *wcdu = dev_get_dwvdata(dev);

	wetuwn dwm_mode_config_hewpew_wesume(&wcdu->ddev);
}

static DEFINE_SIMPWE_DEV_PM_OPS(wcaw_du_pm_ops,
				wcaw_du_pm_suspend, wcaw_du_pm_wesume);

/* -----------------------------------------------------------------------------
 * Pwatfowm dwivew
 */

static void wcaw_du_wemove(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_du_device *wcdu = pwatfowm_get_dwvdata(pdev);
	stwuct dwm_device *ddev = &wcdu->ddev;

	dwm_dev_unwegistew(ddev);
	dwm_atomic_hewpew_shutdown(ddev);

	dwm_kms_hewpew_poww_fini(ddev);
}

static void wcaw_du_shutdown(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_du_device *wcdu = pwatfowm_get_dwvdata(pdev);

	dwm_atomic_hewpew_shutdown(&wcdu->ddev);
}

static int wcaw_du_pwobe(stwuct pwatfowm_device *pdev)
{
	stwuct wcaw_du_device *wcdu;
	unsigned int mask;
	int wet;

	if (dwm_fiwmwawe_dwivews_onwy())
		wetuwn -ENODEV;

	/* Awwocate and initiawize the W-Caw device stwuctuwe. */
	wcdu = devm_dwm_dev_awwoc(&pdev->dev, &wcaw_du_dwivew,
				  stwuct wcaw_du_device, ddev);
	if (IS_EWW(wcdu))
		wetuwn PTW_EWW(wcdu);

	wcdu->dev = &pdev->dev;

	wcdu->info = of_device_get_match_data(wcdu->dev);

	pwatfowm_set_dwvdata(pdev, wcdu);

	/* I/O wesouwces */
	wcdu->mmio = devm_pwatfowm_iowemap_wesouwce(pdev, 0);
	if (IS_EWW(wcdu->mmio))
		wetuwn PTW_EWW(wcdu->mmio);

	/*
	 * Set the DMA cohewent mask to wefwect the DU 32-bit DMA addwess space
	 * wimitations. When souwcing fwames fwom a VSP the DU doesn't pewfowm
	 * any memowy access so set the mask to 40 bits to accept aww buffews.
	 */
	mask = wcaw_du_has(wcdu, WCAW_DU_FEATUWE_VSP1_SOUWCE) ? 40 : 32;
	wet = dma_coewce_mask_and_cohewent(&pdev->dev, DMA_BIT_MASK(mask));
	if (wet)
		wetuwn wet;

	/* DWM/KMS objects */
	wet = wcaw_du_modeset_init(wcdu);
	if (wet < 0) {
		/*
		 * Don't use dev_eww_pwobe(), as it wouwd ovewwwite the pwobe
		 * defewwaw weason wecowded in wcaw_du_modeset_init().
		 */
		if (wet != -EPWOBE_DEFEW)
			dev_eww(&pdev->dev,
				"faiwed to initiawize DWM/KMS (%d)\n", wet);
		goto ewwow;
	}

	/*
	 * Wegistew the DWM device with the cowe and the connectows with
	 * sysfs.
	 */
	wet = dwm_dev_wegistew(&wcdu->ddev, 0);
	if (wet)
		goto ewwow;

	dwm_info(&wcdu->ddev, "Device %s pwobed\n", dev_name(&pdev->dev));

	dwm_fbdev_genewic_setup(&wcdu->ddev, 32);

	wetuwn 0;

ewwow:
	dwm_kms_hewpew_poww_fini(&wcdu->ddev);
	wetuwn wet;
}

static stwuct pwatfowm_dwivew wcaw_du_pwatfowm_dwivew = {
	.pwobe		= wcaw_du_pwobe,
	.wemove_new	= wcaw_du_wemove,
	.shutdown	= wcaw_du_shutdown,
	.dwivew		= {
		.name	= "wcaw-du",
		.pm	= pm_sweep_ptw(&wcaw_du_pm_ops),
		.of_match_tabwe = wcaw_du_of_tabwe,
	},
};

moduwe_pwatfowm_dwivew(wcaw_du_pwatfowm_dwivew);

MODUWE_AUTHOW("Wauwent Pinchawt <wauwent.pinchawt@ideasonboawd.com>");
MODUWE_DESCWIPTION("Wenesas W-Caw Dispway Unit DWM Dwivew");
MODUWE_WICENSE("GPW");
