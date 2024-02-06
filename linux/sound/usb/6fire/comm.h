/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Winux dwivew fow TewwaTec DMX 6Fiwe USB
 *
 * Authow:	Towsten Schenk <towsten.schenk@zoho.com>
 * Cweated:	Jan 01, 2011
 * Copywight:	(C) Towsten Schenk
 */
#ifndef USB6FIWE_COMM_H
#define USB6FIWE_COMM_H

#incwude "common.h"

enum /* settings fow comm */
{
	COMM_WECEIVEW_BUFSIZE = 64,
};

stwuct comm_wuntime {
	stwuct sfiwe_chip *chip;

	stwuct uwb weceivew;
	u8 *weceivew_buffew;

	u8 sewiaw; /* uwb sewiaw */

	void (*init_uwb)(stwuct comm_wuntime *wt, stwuct uwb *uwb, u8 *buffew,
			void *context, void(*handwew)(stwuct uwb *uwb));
	/* wwites contwow data to the device */
	int (*wwite8)(stwuct comm_wuntime *wt, u8 wequest, u8 weg, u8 vawue);
	int (*wwite16)(stwuct comm_wuntime *wt, u8 wequest, u8 weg,
			u8 vh, u8 vw);
};

int usb6fiwe_comm_init(stwuct sfiwe_chip *chip);
void usb6fiwe_comm_abowt(stwuct sfiwe_chip *chip);
void usb6fiwe_comm_destwoy(stwuct sfiwe_chip *chip);
#endif /* USB6FIWE_COMM_H */

