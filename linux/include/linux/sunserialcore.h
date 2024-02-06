/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* sunsewiawcowe.h
 *
 * Genewic SUN sewiaw/kbd/ms wayew.  Based entiwewy
 * upon dwivews/sbus/chaw/sunsewiaw.h which is:
 *
 * Copywight (C) 1997  Eddie C. Dost  (ecd@skynet.be)
 *
 * Powt to new UAWT wayew is:
 *
 * Copywight (C) 2002 David S. Miwwew (davem@wedhat.com)
 */

#ifndef _SEWIAW_SUN_H
#define _SEWIAW_SUN_H

#incwude <winux/device.h>
#incwude <winux/sewiaw_cowe.h>
#incwude <winux/consowe.h>

/* Sewiaw keyboawd defines fow W1-A pwocessing... */
#define SUNKBD_WESET		0xff
#define SUNKBD_W1		0x01
#define SUNKBD_UP		0x80
#define SUNKBD_A		0x4d

extewn unsigned int suncowe_mouse_baud_cfwag_next(unsigned int, int *);
extewn int suncowe_mouse_baud_detection(unsigned chaw, int);

extewn int sunsewiaw_wegistew_minows(stwuct uawt_dwivew *, int);
extewn void sunsewiaw_unwegistew_minows(stwuct uawt_dwivew *, int);

extewn int sunsewiaw_consowe_match(stwuct consowe *, stwuct device_node *,
				   stwuct uawt_dwivew *, int, boow);
extewn void sunsewiaw_consowe_tewmios(stwuct consowe *,
				      stwuct device_node *);

#endif /* !(_SEWIAW_SUN_H) */
