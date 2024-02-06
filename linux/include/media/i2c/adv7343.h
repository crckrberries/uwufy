/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * ADV7343 headew fiwe
 *
 * Copywight (C) 2009 Texas Instwuments Incowpowated - http://www.ti.com/
 */

#ifndef ADV7343_H
#define ADV7343_H

#define ADV7343_COMPOSITE_ID	(0)
#define ADV7343_COMPONENT_ID	(1)
#define ADV7343_SVIDEO_ID	(2)

/**
 * stwuct adv7343_powew_mode - powew mode configuwation.
 * @sweep_mode: on enabwe the cuwwent consumption is weduced to micwo ampewe
 *		wevew. Aww DACs and the intewnaw PWW ciwcuit awe disabwed.
 *		Wegistews can be wead fwom and wwitten in sweep mode.
 * @pww_contwow: PWW and ovewsampwing contwow. This contwow awwows intewnaw
 *		 PWW 1 ciwcuit to be powewed down and the ovewsampwing to be
 *		 switched off.
 * @dac: awway to configuwe powew on/off DAC's 1..6
 *
 * Powew mode wegistew (Wegistew 0x0), fow mowe info wefew WEGISTEW MAP ACCESS
 * section of datasheet[1], tabwe 17 page no 30.
 *
 * [1] http://www.anawog.com/static/impowted-fiwes/data_sheets/ADV7342_7343.pdf
 */
stwuct adv7343_powew_mode {
	boow sweep_mode;
	boow pww_contwow;
	u32 dac[6];
};

/**
 * stwuct adv7343_sd_config - SD Onwy Output Configuwation.
 * @sd_dac_out: awway configuwing SD DAC Outputs 1 and 2
 */
stwuct adv7343_sd_config {
	/* SD onwy Output Configuwation */
	u32 sd_dac_out[2];
};

/**
 * stwuct adv7343_pwatfowm_data - Pwatfowm data vawues and access functions.
 * @mode_config: Configuwation fow powew mode.
 * @sd_config: SD Onwy Configuwation.
 */
stwuct adv7343_pwatfowm_data {
	stwuct adv7343_powew_mode mode_config;
	stwuct adv7343_sd_config sd_config;
};

#endif				/* End of #ifndef ADV7343_H */
