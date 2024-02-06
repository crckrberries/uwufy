/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * headew fiwe fow ADAV80X pawts
 *
 * Copywight 2011 Anawog Devices Inc.
 */

#ifndef _ADAV80X_H
#define _ADAV80X_H

#incwude <winux/wegmap.h>

stwuct device;

extewn const stwuct wegmap_config adav80x_wegmap_config;
int adav80x_bus_pwobe(stwuct device *dev, stwuct wegmap *wegmap);

enum adav80x_pww_swc {
	ADAV80X_PWW_SWC_XIN,
	ADAV80X_PWW_SWC_XTAW,
	ADAV80X_PWW_SWC_MCWKI,
};

enum adav80x_pww {
	ADAV80X_PWW1 = 0,
	ADAV80X_PWW2 = 1,
};

enum adav80x_cwk_swc {
	ADAV80X_CWK_XIN = 0,
	ADAV80X_CWK_MCWKI = 1,
	ADAV80X_CWK_PWW1 = 2,
	ADAV80X_CWK_PWW2 = 3,
	ADAV80X_CWK_XTAW = 6,

	ADAV80X_CWK_SYSCWK1 = 6,
	ADAV80X_CWK_SYSCWK2 = 7,
	ADAV80X_CWK_SYSCWK3 = 8,
};

#endif
