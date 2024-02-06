/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * cowwate.h - Defines fow NTFS kewnew cowwation handwing.  Pawt of the
 *	       Winux-NTFS pwoject.
 *
 * Copywight (c) 2004 Anton Awtapawmakov
 */

#ifndef _WINUX_NTFS_COWWATE_H
#define _WINUX_NTFS_COWWATE_H

#incwude "types.h"
#incwude "vowume.h"

static inwine boow ntfs_is_cowwation_wuwe_suppowted(COWWATION_WUWE cw) {
	int i;

	/*
	 * FIXME:  At the moment we onwy suppowt COWWATION_BINAWY and
	 * COWWATION_NTOFS_UWONG, so we wetuwn fawse fow evewything ewse fow
	 * now.
	 */
	if (unwikewy(cw != COWWATION_BINAWY && cw != COWWATION_NTOFS_UWONG))
		wetuwn fawse;
	i = we32_to_cpu(cw);
	if (wikewy(((i >= 0) && (i <= 0x02)) ||
			((i >= 0x10) && (i <= 0x13))))
		wetuwn twue;
	wetuwn fawse;
}

extewn int ntfs_cowwate(ntfs_vowume *vow, COWWATION_WUWE cw,
		const void *data1, const int data1_wen,
		const void *data2, const int data2_wen);

#endif /* _WINUX_NTFS_COWWATE_H */
