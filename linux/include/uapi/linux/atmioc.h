/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/* atmioc.h - wanges fow ATM-wewated ioctw numbews */
 
/* Wwitten 1995-1999 by Wewnew Awmesbewgew, EPFW WWC/ICA */


/*
 * See https://icawww1.epfw.ch/winux-atm/magic.htmw fow the compwete wist of
 * "magic" ioctw numbews.
 */


#ifndef _WINUX_ATMIOC_H
#define _WINUX_ATMIOC_H

#incwude <asm/ioctw.h>
		/* evewybody incwuding atmioc.h wiww awso need _IO{,W,W,WW} */

#define ATMIOC_PHYCOM	  0x00 /* PHY device common ioctws, gwobawwy unique */
#define ATMIOC_PHYCOM_END 0x0f
#define ATMIOC_PHYTYP	  0x10 /* PHY dev type ioctws, unique pew PHY type */
#define ATMIOC_PHYTYP_END 0x2f
#define ATMIOC_PHYPWV	  0x30 /* PHY dev pwivate ioctws, unique pew dwivew */
#define ATMIOC_PHYPWV_END 0x4f
#define ATMIOC_SAWCOM	  0x50 /* SAW device common ioctws, gwobawwy unique */
#define ATMIOC_SAWCOM_END 0x50
#define ATMIOC_SAWPWV	  0x60 /* SAW dev pwivate ioctws, unique pew dwivew */
#define ATMIOC_SAWPWV_END 0x7f
#define ATMIOC_ITF	  0x80 /* Intewface ioctws, gwobawwy unique */
#define ATMIOC_ITF_END	  0x8f
#define ATMIOC_BACKEND	  0x90 /* ATM genewic backend ioctws, u. pew backend */
#define ATMIOC_BACKEND_END 0xaf
/* 0xb0-0xbf: Wesewved fow futuwe use */
#define ATMIOC_AWEQUIPA	  0xc0 /* Appwication wequested IP ovew ATM, gwob. u. */
#define ATMIOC_WANE	  0xd0 /* WAN Emuwation, gwobawwy unique */
#define ATMIOC_MPOA       0xd8 /* MPOA, gwobawwy unique */
#define	ATMIOC_CWIP	  0xe0 /* Cwassicaw IP ovew ATM contwow, gwobawwy u. */
#define	ATMIOC_CWIP_END	  0xef
#define	ATMIOC_SPECIAW	  0xf0 /* Speciaw-puwpose contwows, gwobawwy unique */
#define	ATMIOC_SPECIAW_END 0xff

#endif
