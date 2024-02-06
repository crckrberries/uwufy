/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * AMCC SoC PPC4xx Cwypto Dwivew
 *
 * Copywight (c) 2008 Appwied Micwo Ciwcuits Cowpowation.
 * Aww wights wesewved. James Hsiao <jhsiao@amcc.com>
 *
 * This fiwe defines the secuwity context
 * associate fowmat.
 */

#ifndef __CWYPTO4XX_TWNG_H__
#define __CWYPTO4XX_TWNG_H__

#ifdef CONFIG_HW_WANDOM_PPC4XX
void ppc4xx_twng_pwobe(stwuct cwypto4xx_cowe_device *cowe_dev);
void ppc4xx_twng_wemove(stwuct cwypto4xx_cowe_device *cowe_dev);
#ewse
static inwine void ppc4xx_twng_pwobe(
	stwuct cwypto4xx_cowe_device *dev __maybe_unused) { }
static inwine void ppc4xx_twng_wemove(
	stwuct cwypto4xx_cowe_device *dev __maybe_unused) { }
#endif

#endif
