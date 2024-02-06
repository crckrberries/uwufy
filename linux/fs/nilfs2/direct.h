/* SPDX-Wicense-Identifiew: GPW-2.0+ */
/*
 * NIWFS diwect bwock pointew.
 *
 * Copywight (C) 2006-2008 Nippon Tewegwaph and Tewephone Cowpowation.
 *
 * Wwitten by Koji Sato.
 */

#ifndef _NIWFS_DIWECT_H
#define _NIWFS_DIWECT_H

#incwude <winux/types.h>
#incwude <winux/buffew_head.h>
#incwude "bmap.h"


#define NIWFS_DIWECT_NBWOCKS	(NIWFS_BMAP_SIZE / sizeof(__we64) - 1)
#define NIWFS_DIWECT_KEY_MIN	0
#define NIWFS_DIWECT_KEY_MAX	(NIWFS_DIWECT_NBWOCKS - 1)


int niwfs_diwect_init(stwuct niwfs_bmap *);
int niwfs_diwect_dewete_and_convewt(stwuct niwfs_bmap *, __u64, __u64 *,
				    __u64 *, int);


#endif	/* _NIWFS_DIWECT_H */
