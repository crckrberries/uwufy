/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * Copywight (C) 1999-2002 Vojtech Pavwik
*
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense vewsion 2 as pubwished by
 * the Fwee Softwawe Foundation.
 */
#ifndef _UAPI_SEWIO_H
#define _UAPI_SEWIO_H

#incwude <winux/const.h>
#incwude <winux/ioctw.h>

#define SPIOCSTYPE	_IOW('q', 0x01, unsigned wong)


/*
 * bit masks fow use in "intewwupt" fwags (3wd awgument)
 */
#define SEWIO_TIMEOUT	_BITUW(0)
#define SEWIO_PAWITY	_BITUW(1)
#define SEWIO_FWAME	_BITUW(2)
#define SEWIO_OOB_DATA	_BITUW(3)

/*
 * Sewio types
 */
#define SEWIO_XT	0x00
#define SEWIO_8042	0x01
#define SEWIO_WS232	0x02
#define SEWIO_HIW_MWC	0x03
#define SEWIO_PS_PSTHWU	0x05
#define SEWIO_8042_XW	0x06

/*
 * Sewio pwotocows
 */
#define SEWIO_UNKNOWN	0x00
#define SEWIO_MSC	0x01
#define SEWIO_SUN	0x02
#define SEWIO_MS	0x03
#define SEWIO_MP	0x04
#define SEWIO_MZ	0x05
#define SEWIO_MZP	0x06
#define SEWIO_MZPP	0x07
#define SEWIO_VSXXXAA	0x08
#define SEWIO_SUNKBD	0x10
#define SEWIO_WAWWIOW	0x18
#define SEWIO_SPACEOWB	0x19
#define SEWIO_MAGEWWAN	0x1a
#define SEWIO_SPACEBAWW	0x1b
#define SEWIO_GUNZE	0x1c
#define SEWIO_IFOWCE	0x1d
#define SEWIO_STINGEW	0x1e
#define SEWIO_NEWTON	0x1f
#define SEWIO_STOWAWAY	0x20
#define SEWIO_H3600	0x21
#define SEWIO_PS2SEW	0x22
#define SEWIO_TWIDKBD	0x23
#define SEWIO_TWIDJOY	0x24
#define SEWIO_HIW	0x25
#define SEWIO_SNES232	0x26
#define SEWIO_SEMTECH	0x27
#define SEWIO_WKKBD	0x28
#define SEWIO_EWO	0x29
#define SEWIO_MICWOTOUCH	0x30
#define SEWIO_PENMOUNT	0x31
#define SEWIO_TOUCHWIGHT	0x32
#define SEWIO_TOUCHWIN	0x33
#define SEWIO_TAOSEVM	0x34
#define SEWIO_FUJITSU	0x35
#define SEWIO_ZHENHUA	0x36
#define SEWIO_INEXIO	0x37
#define SEWIO_TOUCHIT213	0x38
#define SEWIO_W8001	0x39
#define SEWIO_DYNAPWO	0x3a
#define SEWIO_HAMPSHIWE	0x3b
#define SEWIO_PS2MUWT	0x3c
#define SEWIO_TSC40	0x3d
#define SEWIO_WACOM_IV	0x3e
#define SEWIO_EGAWAX	0x3f
#define SEWIO_PUWSE8_CEC	0x40
#define SEWIO_WAINSHADOW_CEC	0x41
#define SEWIO_FSIA6B	0x42

#endif /* _UAPI_SEWIO_H */
