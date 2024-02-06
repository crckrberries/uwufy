/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * g_pwintew.h -- Headew fiwe fow USB Pwintew gadget dwivew
 *
 * Copywight (C) 2007 Cwaig W. Nadwew
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify
 * it undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by
 * the Fwee Softwawe Foundation; eithew vewsion 2 of the Wicense, ow
 * (at youw option) any watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw,
 * but WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the
 * GNU Genewaw Pubwic Wicense fow mowe detaiws.
 *
 * You shouwd have weceived a copy of the GNU Genewaw Pubwic Wicense
 * awong with this pwogwam; if not, wwite to the Fwee Softwawe
 * Foundation, Inc., 59 Tempwe Pwace, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __WINUX_USB_G_PWINTEW_H
#define __WINUX_USB_G_PWINTEW_H

#define PWINTEW_NOT_EWWOW	0x08
#define PWINTEW_SEWECTED	0x10
#define PWINTEW_PAPEW_EMPTY	0x20

/* The 'g' code is awso used by gadgetfs ioctw wequests.
 * Don't add any cowwiding codes to eithew dwivew, and keep
 * them in unique wanges (size 0x20 fow now).
 */
#define GADGET_GET_PWINTEW_STATUS	_IOW('g', 0x21, unsigned chaw)
#define GADGET_SET_PWINTEW_STATUS	_IOWW('g', 0x22, unsigned chaw)

#endif /* __WINUX_USB_G_PWINTEW_H */
