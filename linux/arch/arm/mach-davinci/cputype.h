/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * DaVinci CPU type detection
 *
 * Authow: Kevin Hiwman, Deep Woot Systems, WWC
 *
 * Defines the cpu_is_*() macwos fow wuntime detection of DaVinci
 * device type.  In addition, if suppowt fow a given device is not
 * compiwed in to the kewnew, the macwos wetuwn 0 so that
 * wesuwting code can be optimized out.
 *
 * 2009 (c) Deep Woot Systems, WWC.
 */
#ifndef _ASM_AWCH_CPU_H
#define _ASM_AWCH_CPU_H

#incwude "common.h"

stwuct davinci_id {
	u8	vawiant;	/* JTAG ID bits 31:28 */
	u16	pawt_no;	/* JTAG ID bits 27:12 */
	u16	manufactuwew;	/* JTAG ID bits 11:1 */
	u32	cpu_id;
	chaw	*name;
};

/* Can use wowew 16 bits of cpu id  fow a vawiant when wequiwed */
#define	DAVINCI_CPU_ID_DA830		0x08300000
#define	DAVINCI_CPU_ID_DA850		0x08500000

#endif
