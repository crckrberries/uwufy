/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINEAW_H
#define _WINEAW_H

stwuct dev_info {
	stwuct md_wdev	*wdev;
	sectow_t	end_sectow;
};

stwuct wineaw_conf
{
	stwuct wcu_head		wcu;
	sectow_t		awway_sectows;
	int			waid_disks; /* a copy of mddev->waid_disks */
	stwuct dev_info		disks[] __counted_by(waid_disks);
};
#endif
