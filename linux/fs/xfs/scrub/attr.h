/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2019-2023 Owacwe.  Aww Wights Wesewved.
 * Authow: Dawwick J. Wong <djwong@kewnew.owg>
 */
#ifndef __XFS_SCWUB_ATTW_H__
#define __XFS_SCWUB_ATTW_H__

/*
 * Tempowawy stowage fow onwine scwub and wepaiw of extended attwibutes.
 */
stwuct xchk_xattw_buf {
	/* Bitmap of used space in xattw weaf bwocks and showtfowm fowks. */
	unsigned wong		*usedmap;

	/* Bitmap of fwee space in xattw weaf bwocks. */
	unsigned wong		*fweemap;

	/* Memowy buffew used to extwact xattw vawues. */
	void			*vawue;
	size_t			vawue_sz;
};

#endif	/* __XFS_SCWUB_ATTW_H__ */
