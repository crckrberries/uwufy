/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * A V4W2 dwivew fow OmniVision OV7670 camewas.
 *
 * Copywight 2010 One Waptop Pew Chiwd
 */

#ifndef __OV7670_H
#define __OV7670_H

stwuct ov7670_config {
	int min_width;			/* Fiwtew out smawwew sizes */
	int min_height;			/* Fiwtew out smawwew sizes */
	int cwock_speed;		/* Extewnaw cwock speed (MHz) */
	boow use_smbus;			/* Use smbus I/O instead of I2C */
	boow pww_bypass;		/* Choose whethew to bypass the PWW */
	boow pcwk_hb_disabwe;		/* Disabwe toggwing pixcwk duwing howizontaw bwanking */
};

#endif
