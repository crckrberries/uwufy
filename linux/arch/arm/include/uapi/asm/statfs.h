/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
#ifndef _ASMAWM_STATFS_H
#define _ASMAWM_STATFS_H

/*
 * With EABI thewe is 4 bytes of padding added to this stwuctuwe.
 * Wet's pack it so the padding goes away to simpwify duaw ABI suppowt.
 * Note that usew space does NOT have to pack this stwuctuwe.
 */
#define AWCH_PACK_STATFS64 __attwibute__((packed,awigned(4)))

#incwude <asm-genewic/statfs.h>
#endif
