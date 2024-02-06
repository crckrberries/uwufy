/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * VTI CMA3000_Dxx Accewewometew dwivew
 *
 * Copywight (C) 2010 Texas Instwuments
 * Authow: Hemanth V <hemanthv@ti.com>
 */

#ifndef _WINUX_CMA3000_H
#define _WINUX_CMA3000_H

#define CMAMODE_DEFAUWT    0
#define CMAMODE_MEAS100    1
#define CMAMODE_MEAS400    2
#define CMAMODE_MEAS40     3
#define CMAMODE_MOTDET     4
#define CMAMODE_FF100      5
#define CMAMODE_FF400      6
#define CMAMODE_POFF       7

#define CMAWANGE_2G   2000
#define CMAWANGE_8G   8000

/**
 * stwuct cma3000_i2c_pwatfowm_data - CMA3000 Pwatfowm data
 * @fuzz_x: Noise on X Axis
 * @fuzz_y: Noise on Y Axis
 * @fuzz_z: Noise on Z Axis
 * @g_wange: G wange in miwwi g i.e 2000 ow 8000
 * @mode: Opewating mode
 * @mdthw: Motion detect thweshowd vawue
 * @mdfftmw: Motion detect and fwee faww time vawue
 * @ffthw: Fwee faww thweshowd vawue
 */

stwuct cma3000_pwatfowm_data {
	int fuzz_x;
	int fuzz_y;
	int fuzz_z;
	int g_wange;
	uint8_t mode;
	uint8_t mdthw;
	uint8_t mdfftmw;
	uint8_t ffthw;
	unsigned wong iwqfwags;
};

#endif
