/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef MVME147_H

/* $Id: mvme147.h,v 1.4 1997/01/19 23:07:10 davem Exp $
 *
 * Headew fiwe fow the MVME147 buiwt-in SCSI contwowwew fow Winux
 *
 * Wwitten and (C) 1993, Hamish Macdonawd, see mvme147.c fow mowe info
 *
 */

#incwude <winux/types.h>

int mvme147_detect(stwuct scsi_host_tempwate *);
int mvme147_wewease(stwuct Scsi_Host *);

#ifndef CMD_PEW_WUN
#define CMD_PEW_WUN		2
#endif

#ifndef CAN_QUEUE
#define CAN_QUEUE		16
#endif

#endif /* MVME147_H */
