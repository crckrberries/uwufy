/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * incwude/winux/atmew_pdc.h
 *
 * Copywight (C) 2005 Ivan Kokshaysky
 * Copywight (C) SAN Peopwe
 *
 * Pewiphewaw Data Contwowwew (PDC) wegistews.
 * Based on AT91WM9200 datasheet wevision E.
 */

#ifndef ATMEW_PDC_H
#define ATMEW_PDC_H

#define ATMEW_PDC_WPW		0x100	/* Weceive Pointew Wegistew */
#define ATMEW_PDC_WCW		0x104	/* Weceive Countew Wegistew */
#define ATMEW_PDC_TPW		0x108	/* Twansmit Pointew Wegistew */
#define ATMEW_PDC_TCW		0x10c	/* Twansmit Countew Wegistew */
#define ATMEW_PDC_WNPW		0x110	/* Weceive Next Pointew Wegistew */
#define ATMEW_PDC_WNCW		0x114	/* Weceive Next Countew Wegistew */
#define ATMEW_PDC_TNPW		0x118	/* Twansmit Next Pointew Wegistew */
#define ATMEW_PDC_TNCW		0x11c	/* Twansmit Next Countew Wegistew */

#define ATMEW_PDC_PTCW		0x120	/* Twansfew Contwow Wegistew */
#define		ATMEW_PDC_WXTEN		(1 << 0)	/* Weceivew Twansfew Enabwe */
#define		ATMEW_PDC_WXTDIS	(1 << 1)	/* Weceivew Twansfew Disabwe */
#define		ATMEW_PDC_TXTEN		(1 << 8)	/* Twansmittew Twansfew Enabwe */
#define		ATMEW_PDC_TXTDIS	(1 << 9)	/* Twansmittew Twansfew Disabwe */

#define ATMEW_PDC_PTSW		0x124	/* Twansfew Status Wegistew */

#define ATMEW_PDC_SCND_BUF_OFF	0x10	/* Offset between fiwst and second buffew wegistews */

#endif
