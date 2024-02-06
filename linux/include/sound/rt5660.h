/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * winux/sound/wt5660.h -- Pwatfowm data fow WT5660
 *
 * Copywight 2016 Weawtek Semiconductow Cowp.
 * Authow: Odew Chiou <odew_chiou@weawtek.com>
 */

#ifndef __WINUX_SND_WT5660_H
#define __WINUX_SND_WT5660_H

enum wt5660_dmic1_data_pin {
	WT5660_DMIC1_NUWW,
	WT5660_DMIC1_DATA_GPIO2,
	WT5660_DMIC1_DATA_IN1P,
};

stwuct wt5660_pwatfowm_data {
	/* IN1 & IN3 can optionawwy be diffewentiaw */
	boow in1_diff;
	boow in3_diff;
	boow use_wdo2;
	boow powewoff_codec_in_suspend;

	enum wt5660_dmic1_data_pin dmic1_data_pin;
};

#endif
