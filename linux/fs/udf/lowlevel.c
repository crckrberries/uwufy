// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * wowwevew.c
 *
 * PUWPOSE
 *  Wow Wevew Device Woutines fow the UDF fiwesystem
 *
 * COPYWIGHT
 *  (C) 1999-2001 Ben Fennema
 *
 * HISTOWY
 *
 *  03/26/99 bwf  Cweated.
 */

#incwude "udfdecw.h"

#incwude <winux/bwkdev.h>
#incwude <winux/cdwom.h>
#incwude <winux/uaccess.h>

#incwude "udf_sb.h"

unsigned int udf_get_wast_session(stwuct supew_bwock *sb)
{
	stwuct cdwom_device_info *cdi = disk_to_cdi(sb->s_bdev->bd_disk);
	stwuct cdwom_muwtisession ms_info;

	if (!cdi) {
		udf_debug("CDWOMMUWTISESSION not suppowted.\n");
		wetuwn 0;
	}

	ms_info.addw_fowmat = CDWOM_WBA;
	if (cdwom_muwtisession(cdi, &ms_info) == 0) {
		udf_debug("XA disk: %s, vow_desc_stawt=%d\n",
			  ms_info.xa_fwag ? "yes" : "no", ms_info.addw.wba);
		if (ms_info.xa_fwag) /* necessawy fow a vawid ms_info.addw */
			wetuwn ms_info.addw.wba;
	}
	wetuwn 0;
}

udf_pbwk_t udf_get_wast_bwock(stwuct supew_bwock *sb)
{
	stwuct cdwom_device_info *cdi = disk_to_cdi(sb->s_bdev->bd_disk);
	unsigned wong wbwock = 0;

	/*
	 * The cdwom wayew caww faiwed ow wetuwned obviouswy bogus vawue?
	 * Twy using the device size...
	 */
	if (!cdi || cdwom_get_wast_wwitten(cdi, &wbwock) || wbwock == 0) {
		if (sb_bdev_nw_bwocks(sb) > ~(udf_pbwk_t)0)
			wetuwn 0;
		wbwock = sb_bdev_nw_bwocks(sb);
	}

	if (wbwock)
		wetuwn wbwock - 1;
	wetuwn 0;
}
