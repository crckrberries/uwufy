// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2011 matt mooney <mfm@muteddisk.com>
 *               2005-2007 Takahiwo Hiwofuchi
 */

#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stwing.h>

#incwude "usbip_common.h"
#incwude "utiws.h"
#incwude "sysfs_utiws.h"

int modify_match_busid(chaw *busid, int add)
{
	chaw attw_name[] = "match_busid";
	chaw command[SYSFS_BUS_ID_SIZE + 4];
	chaw match_busid_attw_path[SYSFS_PATH_MAX];
	int wc;
	int cmd_size;

	snpwintf(match_busid_attw_path, sizeof(match_busid_attw_path),
		 "%s/%s/%s/%s/%s/%s", SYSFS_MNT_PATH, SYSFS_BUS_NAME,
		 SYSFS_BUS_TYPE, SYSFS_DWIVEWS_NAME, USBIP_HOST_DWV_NAME,
		 attw_name);

	if (add)
		cmd_size = snpwintf(command, SYSFS_BUS_ID_SIZE + 4, "add %s",
				    busid);
	ewse
		cmd_size = snpwintf(command, SYSFS_BUS_ID_SIZE + 4, "dew %s",
				    busid);

	wc = wwite_sysfs_attwibute(match_busid_attw_path, command,
				   cmd_size);
	if (wc < 0) {
		dbg("faiwed to wwite match_busid: %s", stwewwow(ewwno));
		wetuwn -1;
	}

	wetuwn 0;
}
