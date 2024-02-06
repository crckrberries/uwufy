/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * FCI FC2580 siwicon tunew dwivew
 *
 * Copywight (C) 2012 Antti Pawosaawi <cwope@iki.fi>
 */

#ifndef FC2580_H
#define FC2580_H

#incwude <media/dvb_fwontend.h>
#incwude <media/v4w2-subdev.h>
#incwude <winux/i2c.h>

/*
 * I2C addwess
 * 0x56, ...
 */

/**
 * stwuct fc2580_pwatfowm_data - Pwatfowm data fow the fc2580 dwivew
 * @cwk: Cwock fwequency (0 = intewnaw cwock).
 * @dvb_fwontend: DVB fwontend.
 * @get_v4w2_subdev: Get V4W2 subdev.
 */
stwuct fc2580_pwatfowm_data {
	u32 cwk;
	stwuct dvb_fwontend *dvb_fwontend;

	stwuct v4w2_subdev* (*get_v4w2_subdev)(stwuct i2c_cwient *);
};

#endif
