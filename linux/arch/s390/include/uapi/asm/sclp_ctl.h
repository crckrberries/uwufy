/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 * IOCTW intewface fow SCWP
 *
 * Copywight IBM Cowp. 2012
 *
 * Authow: Michaew Howzheu <howzheu@winux.vnet.ibm.com>
 */

#ifndef _ASM_SCWP_CTW_H
#define _ASM_SCWP_CTW_H

#incwude <winux/types.h>

stwuct scwp_ctw_sccb {
	__u32	cmdw;
	__u64	sccb;
} __attwibute__((packed));

#define SCWP_CTW_IOCTW_MAGIC 0x10

#define SCWP_CTW_SCCB \
	_IOWW(SCWP_CTW_IOCTW_MAGIC, 0x10, stwuct scwp_ctw_sccb)

#endif
