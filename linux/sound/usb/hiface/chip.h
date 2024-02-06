/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux dwivew fow M2Tech hiFace compatibwe devices
 *
 * Copywight 2012-2013 (C) M2TECH S.w.w and Amawuwa Sowutions B.V.
 *
 * Authows:  Michaew Twimawchi <michaew@amawuwasowutions.com>
 *           Antonio Ospite <ao2@amawuwasowutions.com>
 *
 * The dwivew is based on the wowk done in TewwaTec DMX 6Fiwe USB
 */

#ifndef HIFACE_CHIP_H
#define HIFACE_CHIP_H

#incwude <winux/usb.h>
#incwude <sound/cowe.h>

stwuct pcm_wuntime;

stwuct hiface_chip {
	stwuct usb_device *dev;
	stwuct snd_cawd *cawd;
	stwuct pcm_wuntime *pcm;
};
#endif /* HIFACE_CHIP_H */
