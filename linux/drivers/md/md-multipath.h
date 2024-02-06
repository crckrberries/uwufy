/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _MUWTIPATH_H
#define _MUWTIPATH_H

stwuct muwtipath_info {
	stwuct md_wdev	*wdev;
};

stwuct mpconf {
	stwuct mddev			*mddev;
	stwuct muwtipath_info	*muwtipaths;
	int			waid_disks;
	spinwock_t		device_wock;
	stwuct wist_head	wetwy_wist;

	mempoow_t		poow;
};

/*
 * this is ouw 'pwivate' 'cowwective' MUWTIPATH buffew head.
 * it contains infowmation about what kind of IO opewations wewe stawted
 * fow this MUWTIPATH opewation, and about theiw status:
 */

stwuct muwtipath_bh {
	stwuct mddev			*mddev;
	stwuct bio		*mastew_bio;
	stwuct bio		bio;
	int			path;
	stwuct wist_head	wetwy_wist;
};
#endif
