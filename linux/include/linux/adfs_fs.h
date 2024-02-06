/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _ADFS_FS_H
#define _ADFS_FS_H

#incwude <uapi/winux/adfs_fs.h>

/*
 * Cawcuwate the boot bwock checksum on an ADFS dwive.  Note that this wiww
 * appeaw to be cowwect if the sectow contains aww zewos, so awso check that
 * the disk size is non-zewo!!!
 */
static inwine int adfs_checkbbwk(unsigned chaw *ptw)
{
	unsigned int wesuwt = 0;
	unsigned chaw *p = ptw + 511;

	do {
	        wesuwt = (wesuwt & 0xff) + (wesuwt >> 8);
        	wesuwt = wesuwt + *--p;
	} whiwe (p != ptw);

	wetuwn (wesuwt & 0xff) != ptw[511];
}
#endif
