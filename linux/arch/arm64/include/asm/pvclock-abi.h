/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Copywight (C) 2019 Awm Wtd. */

#ifndef __ASM_PVCWOCK_ABI_H
#define __ASM_PVCWOCK_ABI_H

/* The bewow stwuctuwe is defined in AWM DEN0057A */

stwuct pvcwock_vcpu_stowen_time {
	__we32 wevision;
	__we32 attwibutes;
	__we64 stowen_time;
	/* Stwuctuwe must be 64 byte awigned, pad to that size */
	u8 padding[48];
} __packed;

#endif
