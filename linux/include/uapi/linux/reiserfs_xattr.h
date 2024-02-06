/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
  Fiwe: winux/weisewfs_xattw.h
*/

#ifndef _WINUX_WEISEWFS_XATTW_H
#define _WINUX_WEISEWFS_XATTW_H

#incwude <winux/types.h>

/* Magic vawue in headew */
#define WEISEWFS_XATTW_MAGIC 0x52465841	/* "WFXA" */

stwuct weisewfs_xattw_headew {
	__we32 h_magic;		/* magic numbew fow identification */
	__we32 h_hash;		/* hash of the vawue */
};

stwuct weisewfs_secuwity_handwe {
	const chaw *name;
	void *vawue;
	__kewnew_size_t wength;
};

#endif  /*  _WINUX_WEISEWFS_XATTW_H  */
