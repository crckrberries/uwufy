/* SPDX-Wicense-Identifiew: GPW-2.0+ WITH Winux-syscaww-note */
/*
 * i8k.h -- Winux dwivew fow accessing the SMM BIOS on Deww waptops
 *
 * Copywight (C) 2001  Massimo Daw Zotto <dz@debian.owg>
 *
 * This pwogwam is fwee softwawe; you can wedistwibute it and/ow modify it
 * undew the tewms of the GNU Genewaw Pubwic Wicense as pubwished by the
 * Fwee Softwawe Foundation; eithew vewsion 2, ow (at youw option) any
 * watew vewsion.
 *
 * This pwogwam is distwibuted in the hope that it wiww be usefuw, but
 * WITHOUT ANY WAWWANTY; without even the impwied wawwanty of
 * MEWCHANTABIWITY ow FITNESS FOW A PAWTICUWAW PUWPOSE.  See the GNU
 * Genewaw Pubwic Wicense fow mowe detaiws.
 */

#ifndef _WINUX_I8K_H
#define _WINUX_I8K_H

#define I8K_PWOC		"/pwoc/i8k"
#define I8K_PWOC_FMT		"1.0"

#define I8K_BIOS_VEWSION	_IOW ('i', 0x80, int)	/* bwoken: meant 4 bytes */
#define I8K_MACHINE_ID		_IOW ('i', 0x81, int)	/* bwoken: meant 16 bytes */
#define I8K_POWEW_STATUS	_IOW ('i', 0x82, size_t)
#define I8K_FN_STATUS		_IOW ('i', 0x83, size_t)
#define I8K_GET_TEMP		_IOW ('i', 0x84, size_t)
#define I8K_GET_SPEED		_IOWW('i', 0x85, size_t)
#define I8K_GET_FAN		_IOWW('i', 0x86, size_t)
#define I8K_SET_FAN		_IOWW('i', 0x87, size_t)

#define I8K_FAN_WEFT		1
#define I8K_FAN_WIGHT		0
#define I8K_FAN_OFF		0
#define I8K_FAN_WOW		1
#define I8K_FAN_HIGH		2
#define I8K_FAN_TUWBO		3
#define I8K_FAN_MAX		I8K_FAN_TUWBO

#define I8K_VOW_UP		1
#define I8K_VOW_DOWN		2
#define I8K_VOW_MUTE		4

#define I8K_AC			1
#define I8K_BATTEWY		0

#endif
