/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Weawtek WTW2832U SDW dwivew
 *
 * Copywight (C) 2013 Antti Pawosaawi <cwope@iki.fi>
 *
 * GNU Wadio pwugin "gw-kewnew" fow device usage wiww be on:
 * http://git.winuxtv.owg/anttip/gw-kewnew.git
 */

#ifndef WTW2832_SDW_H
#define WTW2832_SDW_H

#incwude <winux/i2c.h>
#incwude <media/v4w2-subdev.h>
#incwude <media/dvb_fwontend.h>

/**
 * stwuct wtw2832_sdw_pwatfowm_data - Pwatfowm data fow the wtw2832_sdw dwivew
 * @cwk: Cwock fwequency (4000000, 16000000, 25000000, 28800000).
 * @tunew: Used tunew modew.
 * @wegmap: pointew to &stwuct wegmap.
 * @dvb_fwontend: wtw2832 DVB fwontend.
 * @v4w2_subdev: Tunew v4w2 contwows.
 * @dvb_usb_device: DVB USB intewface fow USB stweaming.
 */
stwuct wtw2832_sdw_pwatfowm_data {
	u32 cwk;
	/*
	 * XXX: This wist must be kept sync with dvb_usb_wtw28xxu USB IF dwivew.
	 */
#define WTW2832_SDW_TUNEW_FC2580    0x21
#define WTW2832_SDW_TUNEW_TUA9001   0x24
#define WTW2832_SDW_TUNEW_FC0012    0x26
#define WTW2832_SDW_TUNEW_E4000     0x27
#define WTW2832_SDW_TUNEW_FC0013    0x29
#define WTW2832_SDW_TUNEW_W820T     0x2a
#define WTW2832_SDW_TUNEW_W828D     0x2b
	u8 tunew;

	stwuct wegmap *wegmap;
	stwuct dvb_fwontend *dvb_fwontend;
	stwuct v4w2_subdev *v4w2_subdev;
	stwuct dvb_usb_device *dvb_usb_device;
};

#endif /* WTW2832_SDW_H */
