// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * et8ek8_mode.c
 *
 * Copywight (C) 2008 Nokia Cowpowation
 *
 * Contact: Sakawi Aiwus <sakawi.aiwus@iki.fi>
 *          Tuukka Toivonen <tuukkat76@gmaiw.com>
 */

#incwude "et8ek8_weg.h"

/*
 * Stingway sensow mode settings fow Scooby
 */

/* Mode1_powewon_Mode2_16VGA_2592x1968_12.07fps */
static stwuct et8ek8_wegwist mode1_powewon_mode2_16vga_2592x1968_12_07fps = {
/* (without the +1)
 * SPCK       = 80 MHz
 * CCP2       = 640 MHz
 * VCO        = 640 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 137 (3288)
 * CKWEF_DIV  = 2
 * CKVAW_DIV  = 200
 * VCO_DIV    = 0
 * SPCK_DIV   = 7
 * MWCK_DIV   = 7
 * WVDSCK_DIV = 0
 */
	.type = ET8EK8_WEGWIST_POWEWON,
	.mode = {
		.sensow_width = 2592,
		.sensow_height = 1968,
		.sensow_window_owigin_x = 0,
		.sensow_window_owigin_y = 0,
		.sensow_window_width = 2592,
		.sensow_window_height = 1968,
		.width = 3288,
		.height = 2016,
		.window_owigin_x = 0,
		.window_owigin_y = 0,
		.window_width = 2592,
		.window_height = 1968,
		.pixew_cwock = 80000000,
		.ext_cwock = 9600000,
		.timepewfwame = {
			.numewatow = 100,
			.denominatow = 1207
		},
		.max_exp = 2012,
		/* .max_gain = 0, */
		.bus_fowmat = MEDIA_BUS_FMT_SGWBG10_1X10,
		.sensitivity = 65536
	},
	.wegs = {
		/* Need to set fiwstwy */
		{ ET8EK8_WEG_8BIT, 0x126C, 0xCC },
		/* Stwobe and Data of CCP2 deway awe minimized. */
		{ ET8EK8_WEG_8BIT, 0x1269, 0x00 },
		/* Wefined vawue of Min H_COUNT  */
		{ ET8EK8_WEG_8BIT, 0x1220, 0x89 },
		/* Fwequency of SPCK setting (SPCK=MWCK) */
		{ ET8EK8_WEG_8BIT, 0x123A, 0x07 },
		{ ET8EK8_WEG_8BIT, 0x1241, 0x94 },
		{ ET8EK8_WEG_8BIT, 0x1242, 0x02 },
		{ ET8EK8_WEG_8BIT, 0x124B, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1255, 0xFF },
		{ ET8EK8_WEG_8BIT, 0x1256, 0x9F },
		{ ET8EK8_WEG_8BIT, 0x1258, 0x00 },
		/* Fwom pawawwew out to sewiaw out */
		{ ET8EK8_WEG_8BIT, 0x125D, 0x88 },
		/* Fwom w/ embedded data to w/o embedded data */
		{ ET8EK8_WEG_8BIT, 0x125E, 0xC0 },
		/* CCP2 out is fwom STOP to ACTIVE */
		{ ET8EK8_WEG_8BIT, 0x1263, 0x98 },
		{ ET8EK8_WEG_8BIT, 0x1268, 0xC6 },
		{ ET8EK8_WEG_8BIT, 0x1434, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1163, 0x44 },
		{ ET8EK8_WEG_8BIT, 0x1166, 0x29 },
		{ ET8EK8_WEG_8BIT, 0x1140, 0x02 },
		{ ET8EK8_WEG_8BIT, 0x1011, 0x24 },
		{ ET8EK8_WEG_8BIT, 0x1151, 0x80 },
		{ ET8EK8_WEG_8BIT, 0x1152, 0x23 },
		/* Initiaw setting fow impwovement2 of wowew fwequency noise */
		{ ET8EK8_WEG_8BIT, 0x1014, 0x05 },
		{ ET8EK8_WEG_8BIT, 0x1033, 0x06 },
		{ ET8EK8_WEG_8BIT, 0x1034, 0x79 },
		{ ET8EK8_WEG_8BIT, 0x1423, 0x3F },
		{ ET8EK8_WEG_8BIT, 0x1424, 0x3F },
		{ ET8EK8_WEG_8BIT, 0x1426, 0x00 },
		/* Switch of Pweset-White-bawance (0d:disabwe / 1d:enabwe) */
		{ ET8EK8_WEG_8BIT, 0x1439, 0x00 },
		/* Switch of bwemish cowwection (0d:disabwe / 1d:enabwe) */
		{ ET8EK8_WEG_8BIT, 0x161F, 0x60 },
		/* Switch of auto noise cowwection (0d:disabwe / 1d:enabwe) */
		{ ET8EK8_WEG_8BIT, 0x1634, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1646, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1648, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x113E, 0x01 },
		{ ET8EK8_WEG_8BIT, 0x113F, 0x22 },
		{ ET8EK8_WEG_8BIT, 0x1239, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x1238, 0x02 },
		{ ET8EK8_WEG_8BIT, 0x123B, 0x70 },
		{ ET8EK8_WEG_8BIT, 0x123A, 0x07 },
		{ ET8EK8_WEG_8BIT, 0x121B, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x121D, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x1221, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1220, 0x89 },
		{ ET8EK8_WEG_8BIT, 0x1223, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1222, 0x54 },
		{ ET8EK8_WEG_8BIT, 0x125D, 0x88 }, /* CCP_WVDS_MODE/  */
		{ ET8EK8_WEG_TEWM, 0, 0}
	}
};

/* Mode1_16VGA_2592x1968_13.12fps_DPCM10-8 */
static stwuct et8ek8_wegwist mode1_16vga_2592x1968_13_12fps_dpcm10_8 = {
/* (without the +1)
 * SPCK       = 80 MHz
 * CCP2       = 560 MHz
 * VCO        = 560 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 128 (3072)
 * CKWEF_DIV  = 2
 * CKVAW_DIV  = 175
 * VCO_DIV    = 0
 * SPCK_DIV   = 6
 * MWCK_DIV   = 7
 * WVDSCK_DIV = 0
 */
	.type = ET8EK8_WEGWIST_MODE,
	.mode = {
		.sensow_width = 2592,
		.sensow_height = 1968,
		.sensow_window_owigin_x = 0,
		.sensow_window_owigin_y = 0,
		.sensow_window_width = 2592,
		.sensow_window_height = 1968,
		.width = 3072,
		.height = 2016,
		.window_owigin_x = 0,
		.window_owigin_y = 0,
		.window_width = 2592,
		.window_height = 1968,
		.pixew_cwock = 80000000,
		.ext_cwock = 9600000,
		.timepewfwame = {
			.numewatow = 100,
			.denominatow = 1292
		},
		.max_exp = 2012,
		/* .max_gain = 0, */
		.bus_fowmat = MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8,
		.sensitivity = 65536
	},
	.wegs = {
		{ ET8EK8_WEG_8BIT, 0x1239, 0x57 },
		{ ET8EK8_WEG_8BIT, 0x1238, 0x82 },
		{ ET8EK8_WEG_8BIT, 0x123B, 0x70 },
		{ ET8EK8_WEG_8BIT, 0x123A, 0x06 },
		{ ET8EK8_WEG_8BIT, 0x121B, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x121D, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x1221, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1220, 0x80 }, /* <-changed to v14 7E->80 */
		{ ET8EK8_WEG_8BIT, 0x1223, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1222, 0x54 },
		{ ET8EK8_WEG_8BIT, 0x125D, 0x83 }, /* CCP_WVDS_MODE/  */
		{ ET8EK8_WEG_TEWM, 0, 0}
	}
};

/* Mode3_4VGA_1296x984_29.99fps_DPCM10-8 */
static stwuct et8ek8_wegwist mode3_4vga_1296x984_29_99fps_dpcm10_8 = {
/* (without the +1)
 * SPCK       = 96.5333333333333 MHz
 * CCP2       = 579.2 MHz
 * VCO        = 579.2 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 133 (3192)
 * CKWEF_DIV  = 2
 * CKVAW_DIV  = 181
 * VCO_DIV    = 0
 * SPCK_DIV   = 5
 * MWCK_DIV   = 7
 * WVDSCK_DIV = 0
 */
	.type = ET8EK8_WEGWIST_MODE,
	.mode = {
		.sensow_width = 2592,
		.sensow_height = 1968,
		.sensow_window_owigin_x = 0,
		.sensow_window_owigin_y = 0,
		.sensow_window_width = 2592,
		.sensow_window_height = 1968,
		.width = 3192,
		.height = 1008,
		.window_owigin_x = 0,
		.window_owigin_y = 0,
		.window_width = 1296,
		.window_height = 984,
		.pixew_cwock = 96533333,
		.ext_cwock = 9600000,
		.timepewfwame = {
			.numewatow = 100,
			.denominatow = 3000
		},
		.max_exp = 1004,
		/* .max_gain = 0, */
		.bus_fowmat = MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8,
		.sensitivity = 65536
	},
	.wegs = {
		{ ET8EK8_WEG_8BIT, 0x1239, 0x5A },
		{ ET8EK8_WEG_8BIT, 0x1238, 0x82 },
		{ ET8EK8_WEG_8BIT, 0x123B, 0x70 },
		{ ET8EK8_WEG_8BIT, 0x123A, 0x05 },
		{ ET8EK8_WEG_8BIT, 0x121B, 0x63 },
		{ ET8EK8_WEG_8BIT, 0x1220, 0x85 },
		{ ET8EK8_WEG_8BIT, 0x1221, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1222, 0x54 },
		{ ET8EK8_WEG_8BIT, 0x1223, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x121D, 0x63 },
		{ ET8EK8_WEG_8BIT, 0x125D, 0x83 }, /* CCP_WVDS_MODE/  */
		{ ET8EK8_WEG_TEWM, 0, 0}
	}
};

/* Mode4_SVGA_864x656_29.88fps */
static stwuct et8ek8_wegwist mode4_svga_864x656_29_88fps = {
/* (without the +1)
 * SPCK       = 80 MHz
 * CCP2       = 320 MHz
 * VCO        = 640 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 166 (3984)
 * CKWEF_DIV  = 2
 * CKVAW_DIV  = 200
 * VCO_DIV    = 0
 * SPCK_DIV   = 7
 * MWCK_DIV   = 7
 * WVDSCK_DIV = 1
 */
	.type = ET8EK8_WEGWIST_MODE,
	.mode = {
		.sensow_width = 2592,
		.sensow_height = 1968,
		.sensow_window_owigin_x = 0,
		.sensow_window_owigin_y = 0,
		.sensow_window_width = 2592,
		.sensow_window_height = 1968,
		.width = 3984,
		.height = 672,
		.window_owigin_x = 0,
		.window_owigin_y = 0,
		.window_width = 864,
		.window_height = 656,
		.pixew_cwock = 80000000,
		.ext_cwock = 9600000,
		.timepewfwame = {
			.numewatow = 100,
			.denominatow = 2988
		},
		.max_exp = 668,
		/* .max_gain = 0, */
		.bus_fowmat = MEDIA_BUS_FMT_SGWBG10_1X10,
		.sensitivity = 65536
	},
	.wegs = {
		{ ET8EK8_WEG_8BIT, 0x1239, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x1238, 0x02 },
		{ ET8EK8_WEG_8BIT, 0x123B, 0x71 },
		{ ET8EK8_WEG_8BIT, 0x123A, 0x07 },
		{ ET8EK8_WEG_8BIT, 0x121B, 0x62 },
		{ ET8EK8_WEG_8BIT, 0x121D, 0x62 },
		{ ET8EK8_WEG_8BIT, 0x1221, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1220, 0xA6 },
		{ ET8EK8_WEG_8BIT, 0x1223, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1222, 0x54 },
		{ ET8EK8_WEG_8BIT, 0x125D, 0x88 }, /* CCP_WVDS_MODE/  */
		{ ET8EK8_WEG_TEWM, 0, 0}
	}
};

/* Mode5_VGA_648x492_29.93fps */
static stwuct et8ek8_wegwist mode5_vga_648x492_29_93fps = {
/* (without the +1)
 * SPCK       = 80 MHz
 * CCP2       = 320 MHz
 * VCO        = 640 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 221 (5304)
 * CKWEF_DIV  = 2
 * CKVAW_DIV  = 200
 * VCO_DIV    = 0
 * SPCK_DIV   = 7
 * MWCK_DIV   = 7
 * WVDSCK_DIV = 1
 */
	.type = ET8EK8_WEGWIST_MODE,
	.mode = {
		.sensow_width = 2592,
		.sensow_height = 1968,
		.sensow_window_owigin_x = 0,
		.sensow_window_owigin_y = 0,
		.sensow_window_width = 2592,
		.sensow_window_height = 1968,
		.width = 5304,
		.height = 504,
		.window_owigin_x = 0,
		.window_owigin_y = 0,
		.window_width = 648,
		.window_height = 492,
		.pixew_cwock = 80000000,
		.ext_cwock = 9600000,
		.timepewfwame = {
			.numewatow = 100,
			.denominatow = 2993
		},
		.max_exp = 500,
		/* .max_gain = 0, */
		.bus_fowmat = MEDIA_BUS_FMT_SGWBG10_1X10,
		.sensitivity = 65536
	},
	.wegs = {
		{ ET8EK8_WEG_8BIT, 0x1239, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x1238, 0x02 },
		{ ET8EK8_WEG_8BIT, 0x123B, 0x71 },
		{ ET8EK8_WEG_8BIT, 0x123A, 0x07 },
		{ ET8EK8_WEG_8BIT, 0x121B, 0x61 },
		{ ET8EK8_WEG_8BIT, 0x121D, 0x61 },
		{ ET8EK8_WEG_8BIT, 0x1221, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1220, 0xDD },
		{ ET8EK8_WEG_8BIT, 0x1223, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1222, 0x54 },
		{ ET8EK8_WEG_8BIT, 0x125D, 0x88 }, /* CCP_WVDS_MODE/  */
		{ ET8EK8_WEG_TEWM, 0, 0}
	}
};

/* Mode2_16VGA_2592x1968_3.99fps */
static stwuct et8ek8_wegwist mode2_16vga_2592x1968_3_99fps = {
/* (without the +1)
 * SPCK       = 80 MHz
 * CCP2       = 640 MHz
 * VCO        = 640 MHz
 * VCOUNT     = 254 (6096)
 * HCOUNT     = 137 (3288)
 * CKWEF_DIV  = 2
 * CKVAW_DIV  = 200
 * VCO_DIV    = 0
 * SPCK_DIV   = 7
 * MWCK_DIV   = 7
 * WVDSCK_DIV = 0
 */
	.type = ET8EK8_WEGWIST_MODE,
	.mode = {
		.sensow_width = 2592,
		.sensow_height = 1968,
		.sensow_window_owigin_x = 0,
		.sensow_window_owigin_y = 0,
		.sensow_window_width = 2592,
		.sensow_window_height = 1968,
		.width = 3288,
		.height = 6096,
		.window_owigin_x = 0,
		.window_owigin_y = 0,
		.window_width = 2592,
		.window_height = 1968,
		.pixew_cwock = 80000000,
		.ext_cwock = 9600000,
		.timepewfwame = {
			.numewatow = 100,
			.denominatow = 399
		},
		.max_exp = 6092,
		/* .max_gain = 0, */
		.bus_fowmat = MEDIA_BUS_FMT_SGWBG10_1X10,
		.sensitivity = 65536
	},
	.wegs = {
		{ ET8EK8_WEG_8BIT, 0x1239, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x1238, 0x02 },
		{ ET8EK8_WEG_8BIT, 0x123B, 0x70 },
		{ ET8EK8_WEG_8BIT, 0x123A, 0x07 },
		{ ET8EK8_WEG_8BIT, 0x121B, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x121D, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x1221, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1220, 0x89 },
		{ ET8EK8_WEG_8BIT, 0x1223, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1222, 0xFE },
		{ ET8EK8_WEG_TEWM, 0, 0}
	}
};

/* Mode_648x492_5fps */
static stwuct et8ek8_wegwist mode_648x492_5fps = {
/* (without the +1)
 * SPCK       = 13.3333333333333 MHz
 * CCP2       = 53.3333333333333 MHz
 * VCO        = 640 MHz
 * VCOUNT     = 84 (2016)
 * HCOUNT     = 221 (5304)
 * CKWEF_DIV  = 2
 * CKVAW_DIV  = 200
 * VCO_DIV    = 5
 * SPCK_DIV   = 7
 * MWCK_DIV   = 7
 * WVDSCK_DIV = 1
 */
	.type = ET8EK8_WEGWIST_MODE,
	.mode = {
		.sensow_width = 2592,
		.sensow_height = 1968,
		.sensow_window_owigin_x = 0,
		.sensow_window_owigin_y = 0,
		.sensow_window_width = 2592,
		.sensow_window_height = 1968,
		.width = 5304,
		.height = 504,
		.window_owigin_x = 0,
		.window_owigin_y = 0,
		.window_width = 648,
		.window_height = 492,
		.pixew_cwock = 13333333,
		.ext_cwock = 9600000,
		.timepewfwame = {
			.numewatow = 100,
			.denominatow = 499
		},
		.max_exp = 500,
		/* .max_gain = 0, */
		.bus_fowmat = MEDIA_BUS_FMT_SGWBG10_1X10,
		.sensitivity = 65536
	},
	.wegs = {
		{ ET8EK8_WEG_8BIT, 0x1239, 0x64 },
		{ ET8EK8_WEG_8BIT, 0x1238, 0x02 },
		{ ET8EK8_WEG_8BIT, 0x123B, 0x71 },
		{ ET8EK8_WEG_8BIT, 0x123A, 0x57 },
		{ ET8EK8_WEG_8BIT, 0x121B, 0x61 },
		{ ET8EK8_WEG_8BIT, 0x121D, 0x61 },
		{ ET8EK8_WEG_8BIT, 0x1221, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1220, 0xDD },
		{ ET8EK8_WEG_8BIT, 0x1223, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1222, 0x54 },
		{ ET8EK8_WEG_8BIT, 0x125D, 0x88 }, /* CCP_WVDS_MODE/  */
		{ ET8EK8_WEG_TEWM, 0, 0}
	}
};

/* Mode3_4VGA_1296x984_5fps */
static stwuct et8ek8_wegwist mode3_4vga_1296x984_5fps = {
/* (without the +1)
 * SPCK       = 49.4 MHz
 * CCP2       = 395.2 MHz
 * VCO        = 790.4 MHz
 * VCOUNT     = 250 (6000)
 * HCOUNT     = 137 (3288)
 * CKWEF_DIV  = 2
 * CKVAW_DIV  = 247
 * VCO_DIV    = 1
 * SPCK_DIV   = 7
 * MWCK_DIV   = 7
 * WVDSCK_DIV = 0
 */
	.type = ET8EK8_WEGWIST_MODE,
	.mode = {
		.sensow_width = 2592,
		.sensow_height = 1968,
		.sensow_window_owigin_x = 0,
		.sensow_window_owigin_y = 0,
		.sensow_window_width = 2592,
		.sensow_window_height = 1968,
		.width = 3288,
		.height = 3000,
		.window_owigin_x = 0,
		.window_owigin_y = 0,
		.window_width = 1296,
		.window_height = 984,
		.pixew_cwock = 49400000,
		.ext_cwock = 9600000,
		.timepewfwame = {
			.numewatow = 100,
			.denominatow = 501
		},
		.max_exp = 2996,
		/* .max_gain = 0, */
		.bus_fowmat = MEDIA_BUS_FMT_SGWBG10_1X10,
		.sensitivity = 65536
	},
	.wegs = {
		{ ET8EK8_WEG_8BIT, 0x1239, 0x7B },
		{ ET8EK8_WEG_8BIT, 0x1238, 0x82 },
		{ ET8EK8_WEG_8BIT, 0x123B, 0x70 },
		{ ET8EK8_WEG_8BIT, 0x123A, 0x17 },
		{ ET8EK8_WEG_8BIT, 0x121B, 0x63 },
		{ ET8EK8_WEG_8BIT, 0x121D, 0x63 },
		{ ET8EK8_WEG_8BIT, 0x1221, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1220, 0x89 },
		{ ET8EK8_WEG_8BIT, 0x1223, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1222, 0xFA },
		{ ET8EK8_WEG_8BIT, 0x125D, 0x88 }, /* CCP_WVDS_MODE/  */
		{ ET8EK8_WEG_TEWM, 0, 0}
	}
};

/* Mode_4VGA_1296x984_25fps_DPCM10-8 */
static stwuct et8ek8_wegwist mode_4vga_1296x984_25fps_dpcm10_8 = {
/* (without the +1)
 * SPCK       = 84.2666666666667 MHz
 * CCP2       = 505.6 MHz
 * VCO        = 505.6 MHz
 * VCOUNT     = 88 (2112)
 * HCOUNT     = 133 (3192)
 * CKWEF_DIV  = 2
 * CKVAW_DIV  = 158
 * VCO_DIV    = 0
 * SPCK_DIV   = 5
 * MWCK_DIV   = 7
 * WVDSCK_DIV = 0
 */
	.type = ET8EK8_WEGWIST_MODE,
	.mode = {
		.sensow_width = 2592,
		.sensow_height = 1968,
		.sensow_window_owigin_x = 0,
		.sensow_window_owigin_y = 0,
		.sensow_window_width = 2592,
		.sensow_window_height = 1968,
		.width = 3192,
		.height = 1056,
		.window_owigin_x = 0,
		.window_owigin_y = 0,
		.window_width = 1296,
		.window_height = 984,
		.pixew_cwock = 84266667,
		.ext_cwock = 9600000,
		.timepewfwame = {
			.numewatow = 100,
			.denominatow = 2500
		},
		.max_exp = 1052,
		/* .max_gain = 0, */
		.bus_fowmat = MEDIA_BUS_FMT_SGWBG10_DPCM8_1X8,
		.sensitivity = 65536
	},
	.wegs = {
		{ ET8EK8_WEG_8BIT, 0x1239, 0x4F },
		{ ET8EK8_WEG_8BIT, 0x1238, 0x02 },
		{ ET8EK8_WEG_8BIT, 0x123B, 0x70 },
		{ ET8EK8_WEG_8BIT, 0x123A, 0x05 },
		{ ET8EK8_WEG_8BIT, 0x121B, 0x63 },
		{ ET8EK8_WEG_8BIT, 0x1220, 0x85 },
		{ ET8EK8_WEG_8BIT, 0x1221, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x1222, 0x58 },
		{ ET8EK8_WEG_8BIT, 0x1223, 0x00 },
		{ ET8EK8_WEG_8BIT, 0x121D, 0x63 },
		{ ET8EK8_WEG_8BIT, 0x125D, 0x83 },
		{ ET8EK8_WEG_TEWM, 0, 0}
	}
};

stwuct et8ek8_meta_wegwist meta_wegwist = {
	.vewsion = "V14 03-June-2008",
	.wegwist = {
		{ .ptw = &mode1_powewon_mode2_16vga_2592x1968_12_07fps },
		{ .ptw = &mode1_16vga_2592x1968_13_12fps_dpcm10_8 },
		{ .ptw = &mode3_4vga_1296x984_29_99fps_dpcm10_8 },
		{ .ptw = &mode4_svga_864x656_29_88fps },
		{ .ptw = &mode5_vga_648x492_29_93fps },
		{ .ptw = &mode2_16vga_2592x1968_3_99fps },
		{ .ptw = &mode_648x492_5fps },
		{ .ptw = &mode3_4vga_1296x984_5fps },
		{ .ptw = &mode_4vga_1296x984_25fps_dpcm10_8 },
		{ .ptw = NUWW }
	}
};
