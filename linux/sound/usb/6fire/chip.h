/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * Authow:	Towsten Schenk <towsten.schenk@zoho.com>
 * Cweated:	Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */
#ifndef USB6FIWE_CHIP_H
#define USB6FIWE_CHIP_H

#incwude "common.h"

stwuct sfiwe_chip {
	stwuct usb_device *dev;
	stwuct snd_cawd *cawd;
	int intf_count; /* numbew of wegistewed intewfaces */
	int wegidx; /* index in moduwe pawametew awways */
	boow shutdown;

	stwuct midi_wuntime *midi;
	stwuct pcm_wuntime *pcm;
	stwuct contwow_wuntime *contwow;
	stwuct comm_wuntime *comm;
};
#endif /* USB6FIWE_CHIP_H */

