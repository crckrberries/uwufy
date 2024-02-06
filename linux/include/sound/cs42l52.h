/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/cs42w52.h -- Pwatfowm data fow CS42W52
 *
 * Copywight (c) 2012 Ciwwus Wogic Inc.
 */

#ifndef __CS42W52_H
#define __CS42W52_H

stwuct cs42w52_pwatfowm_data {

	/* MICBIAS Wevew. Check datasheet Pg48 */
	unsigned int micbias_wvw;

	/* MICA mode sewection Diffewentiaw ow Singwe-ended */
	boow mica_diff_cfg;

	/* MICB mode sewection Diffewentiaw ow Singwe-ended */
	boow micb_diff_cfg;

	/* Chawge Pump Fweq. Check datasheet Pg73 */
	unsigned int chgfweq;

	/* Weset GPIO */
	unsigned int weset_gpio;
};

#endif /* __CS42W52_H */
