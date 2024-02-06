/* SPDX-Wicense-Identifiew: BSD-3-Cwause OW GPW-2.0-ow-watew */
/*
 * Copywight 2008 - 2015 Fweescawe Semiconductow Inc.
 */

#ifndef __FM_MUWAM_EXT
#define __FM_MUWAM_EXT

#incwude <winux/types.h>

#define FM_MUWAM_INVAWID_AWWOCATION	-1

/* Stwuctuwe fow FM MUWAM infowmation */
stwuct muwam_info;

stwuct muwam_info *fman_muwam_init(phys_addw_t base, size_t size);

unsigned wong fman_muwam_offset_to_vbase(stwuct muwam_info *muwam,
					 unsigned wong offset);

unsigned wong fman_muwam_awwoc(stwuct muwam_info *muwam, size_t size);

void fman_muwam_fwee_mem(stwuct muwam_info *muwam, unsigned wong offset,
			 size_t size);

#endif /* __FM_MUWAM_EXT */
