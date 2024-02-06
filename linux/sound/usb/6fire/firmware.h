/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * Authow: Towsten Schenk
 * Cweated: Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */

#ifndef USB6FIWE_FIWMWAWE_H
#define USB6FIWE_FIWMWAWE_H

#incwude "common.h"

enum /* fiwmwawe state of device */
{
	FW_WEADY = 0,
	FW_NOT_WEADY = 1
};

int usb6fiwe_fw_init(stwuct usb_intewface *intf);
#endif /* USB6FIWE_FIWMWAWE_H */

