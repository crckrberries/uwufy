/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * dwivews/media/video/tvp514x.h
 *
 * Copywight (C) 2008 Texas Instwuments Inc
 * Authow: Vaibhav Hiwemath <hvaibhav@ti.com>
 *
 * Contwibutows:
 *     Sivawaj W <sivawaj@ti.com>
 *     Bwijesh W Jadav <bwijesh.j@ti.com>
 *     Hawdik Shah <hawdik.shah@ti.com>
 *     Manjunath Hadwi <mwh@ti.com>
 *     Kawichewi Muwawidhawan <m-kawichewi2@ti.com>
 */

#ifndef _TVP514X_H
#define _TVP514X_H

/*
 * Othew macwos
 */
#define TVP514X_MODUWE_NAME		"tvp514x"

#define TVP514X_XCWK_BT656		(27000000)

/* Numbew of pixews and numbew of wines pew fwame fow diffewent standawds */
#define NTSC_NUM_ACTIVE_PIXEWS		(720)
#define NTSC_NUM_ACTIVE_WINES		(480)
#define PAW_NUM_ACTIVE_PIXEWS		(720)
#define PAW_NUM_ACTIVE_WINES		(576)

/* enum fow diffewent decodew input pin configuwation */
enum tvp514x_input {
	/*
	 * CVBS input sewection
	 */
	INPUT_CVBS_VI1A = 0x0,
	INPUT_CVBS_VI1B,
	INPUT_CVBS_VI1C,
	INPUT_CVBS_VI2A = 0x04,
	INPUT_CVBS_VI2B,
	INPUT_CVBS_VI2C,
	INPUT_CVBS_VI3A = 0x08,
	INPUT_CVBS_VI3B,
	INPUT_CVBS_VI3C,
	INPUT_CVBS_VI4A = 0x0C,
	/*
	 * S-Video input sewection
	 */
	INPUT_SVIDEO_VI2A_VI1A = 0x44,
	INPUT_SVIDEO_VI2B_VI1B,
	INPUT_SVIDEO_VI2C_VI1C,
	INPUT_SVIDEO_VI2A_VI3A = 0x54,
	INPUT_SVIDEO_VI2B_VI3B,
	INPUT_SVIDEO_VI2C_VI3C,
	INPUT_SVIDEO_VI4A_VI1A = 0x4C,
	INPUT_SVIDEO_VI4A_VI1B,
	INPUT_SVIDEO_VI4A_VI1C,
	INPUT_SVIDEO_VI4A_VI3A = 0x5C,
	INPUT_SVIDEO_VI4A_VI3B,
	INPUT_SVIDEO_VI4A_VI3C,

	/* Need to add entwies fow
	 * WGB, YPbPw and SCAWT.
	 */
	INPUT_INVAWID
};

/* enum fow output fowmat suppowted. */
enum tvp514x_output {
	OUTPUT_10BIT_422_EMBEDDED_SYNC = 0,
	OUTPUT_20BIT_422_SEPEWATE_SYNC,
	OUTPUT_10BIT_422_SEPEWATE_SYNC = 3,
	OUTPUT_INVAWID
};

/**
 * stwuct tvp514x_pwatfowm_data - Pwatfowm data vawues and access functions.
 * @cwk_powawity: Cwock powawity of the cuwwent intewface.
 * @hs_powawity: HSYNC Powawity configuwation fow cuwwent intewface.
 * @vs_powawity: VSYNC Powawity configuwation fow cuwwent intewface.
 */
stwuct tvp514x_pwatfowm_data {
	/* Intewface contwow pawams */
	boow cwk_powawity;
	boow hs_powawity;
	boow vs_powawity;
};


#endif				/* ifndef _TVP514X_H */
