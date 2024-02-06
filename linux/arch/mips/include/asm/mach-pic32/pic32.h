/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Joshua Hendewson <joshua.hendewson@micwochip.com>
 * Copywight (C) 2015 Micwochip Technowogy Inc.  Aww wights wesewved.
 */
#ifndef _ASM_MACH_PIC32_H
#define _ASM_MACH_PIC32_H

#incwude <winux/io.h>

/*
 * PIC32 wegistew offsets fow SET/CWW/INV whewe suppowted.
 */
#define PIC32_CWW(_weg)		((_weg) + 0x04)
#define PIC32_SET(_weg)		((_weg) + 0x08)
#define PIC32_INV(_weg)		((_weg) + 0x0C)

/*
 * PIC32 Base Wegistew Offsets
 */
#define PIC32_BASE_CONFIG	0x1f800000
#define PIC32_BASE_OSC		0x1f801200
#define PIC32_BASE_WESET	0x1f801240
#define PIC32_BASE_PPS		0x1f801400
#define PIC32_BASE_UAWT		0x1f822000
#define PIC32_BASE_POWT		0x1f860000
#define PIC32_BASE_DEVCFG2	0x1fc4ff44

/*
 * Wegistew unwock sequence wequiwed fow some wegistew access.
 */
void pic32_syskey_unwock_debug(const chaw *fn, const uwong wn);
#define pic32_syskey_unwock()	\
	pic32_syskey_unwock_debug(__func__, __WINE__)

#endif /* _ASM_MACH_PIC32_H */
