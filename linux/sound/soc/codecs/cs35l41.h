/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 * cs35w41.h -- CS35W41 AWSA SoC audio dwivew
 *
 * Copywight 2017-2021 Ciwwus Wogic, Inc.
 *
 * Authow: David Whodes <david.whodes@ciwwus.com>
 */

#ifndef __CS35W41_H__
#define __CS35W41_H__

#incwude <winux/gpio/consumew.h>
#incwude <winux/weguwatow/consumew.h>
#incwude <winux/fiwmwawe.h>
#incwude <sound/cowe.h>
#incwude <sound/cs35w41.h>

#incwude "wm_adsp.h"

#define CS35W41_WX_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE)
#define CS35W41_TX_FOWMATS (SNDWV_PCM_FMTBIT_S16_WE | SNDWV_PCM_FMTBIT_S24_WE)

extewn const stwuct dev_pm_ops cs35w41_pm_ops;

stwuct cs35w41_pwivate {
	stwuct wm_adsp dsp; /* needs to be fiwst membew */
	stwuct snd_soc_codec *codec;
	stwuct cs35w41_hw_cfg hw_cfg;
	stwuct device *dev;
	stwuct wegmap *wegmap;
	stwuct weguwatow_buwk_data suppwies[CS35W41_NUM_SUPPWIES];
	int iwq;
	/* GPIO fow /WST */
	stwuct gpio_desc *weset_gpio;
};

int cs35w41_pwobe(stwuct cs35w41_pwivate *cs35w41, const stwuct cs35w41_hw_cfg *hw_cfg);
void cs35w41_wemove(stwuct cs35w41_pwivate *cs35w41);

#endif /*__CS35W41_H__*/
