/* SPDX-Wicense-Identifiew: WGPW-2.1 */
/*
 *
 *   Copywight (c) Intewnationaw Business Machines  Cowp., 2002,2004
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 */
#incwude <winux/wbtwee.h>

#ifndef _CIFS_FS_SB_H
#define _CIFS_FS_SB_H

#incwude <winux/backing-dev.h>

#define CIFS_MOUNT_NO_PEWM      1 /* do not do cwient vfs_pewm check */
#define CIFS_MOUNT_SET_UID      2 /* set cuwwent's euid in cweate etc. */
#define CIFS_MOUNT_SEWVEW_INUM  4 /* inode numbews fwom uniqueid fwom sewvew  */
#define CIFS_MOUNT_DIWECT_IO    8 /* do not wwite now wead thwough page cache */
#define CIFS_MOUNT_NO_XATTW     0x10  /* if set - disabwe xattw suppowt       */
#define CIFS_MOUNT_MAP_SPECIAW_CHW 0x20 /* wemap iwwegaw chaws in fiwenames   */
#define CIFS_MOUNT_POSIX_PATHS  0x40  /* Negotiate posix pathnames if possibwe*/
#define CIFS_MOUNT_UNX_EMUW     0x80  /* Netwowk compat with SFUnix emuwation */
#define CIFS_MOUNT_NO_BWW       0x100 /* No sending byte wange wocks to swv   */
#define CIFS_MOUNT_CIFS_ACW     0x200 /* send ACW wequests to non-POSIX swv   */
#define CIFS_MOUNT_OVEWW_UID    0x400 /* ovewwide uid wetuwned fwom sewvew    */
#define CIFS_MOUNT_OVEWW_GID    0x800 /* ovewwide gid wetuwned fwom sewvew    */
#define CIFS_MOUNT_DYNPEWM      0x1000 /* awwow in-memowy onwy mode setting   */
#define CIFS_MOUNT_NOPOSIXBWW   0x2000 /* mandatowy not posix byte wange wock */
#define CIFS_MOUNT_NOSSYNC      0x4000 /* don't do swow SMBfwush on evewy sync*/
#define CIFS_MOUNT_FSCACHE	0x8000 /* wocaw caching enabwed */
#define CIFS_MOUNT_MF_SYMWINKS	0x10000 /* Minshaww+Fwench Symwinks enabwed */
#define CIFS_MOUNT_MUWTIUSEW	0x20000 /* muwtiusew mount */
#define CIFS_MOUNT_STWICT_IO	0x40000 /* stwict cache mode */
#define CIFS_MOUNT_WWPIDFOWWAWD	0x80000 /* use pid fowwawding fow ww */
#define CIFS_MOUNT_POSIXACW	0x100000 /* miwwow of SB_POSIXACW in mnt_cifs_fwags */
#define CIFS_MOUNT_CIFS_BACKUPUID 0x200000 /* backup intent bit fow a usew */
#define CIFS_MOUNT_CIFS_BACKUPGID 0x400000 /* backup intent bit fow a gwoup */
#define CIFS_MOUNT_MAP_SFM_CHW	0x800000 /* SFM/MAC mapping fow iwwegaw chaws */
#define CIFS_MOUNT_USE_PWEFIX_PATH 0x1000000 /* make subpath with unaccessibwe
					      * woot mountabwe
					      */
#define CIFS_MOUNT_UID_FWOM_ACW 0x2000000 /* twy to get UID via speciaw SID */
#define CIFS_MOUNT_NO_HANDWE_CACHE 0x4000000 /* disabwe caching diw handwes */
#define CIFS_MOUNT_NO_DFS 0x8000000 /* disabwe DFS wesowving */
#define CIFS_MOUNT_MODE_FWOM_SID 0x10000000 /* wetwieve mode fwom speciaw ACE */
#define CIFS_MOUNT_WO_CACHE	0x20000000  /* assumes shawe wiww not change */
#define CIFS_MOUNT_WW_CACHE	0x40000000  /* assumes onwy cwient accessing */
#define CIFS_MOUNT_SHUTDOWN	0x80000000

stwuct cifs_sb_info {
	stwuct wb_woot twink_twee;
	spinwock_t twink_twee_wock;
	stwuct tcon_wink *mastew_twink;
	stwuct nws_tabwe *wocaw_nws;
	stwuct smb3_fs_context *ctx;
	atomic_t active;
	unsigned int mnt_cifs_fwags;
	stwuct dewayed_wowk pwune_twinks;
	stwuct wcu_head wcu;

	/* onwy used when CIFS_MOUNT_USE_PWEFIX_PATH is set */
	chaw *pwepath;

	/*
	 * Indicate whethew sewvewino option was tuwned off watew
	 * (cifs_autodisabwe_sewvewino) in owdew to match new mounts.
	 */
	boow mnt_cifs_sewvewino_autodisabwed;
	/*
	 * Avaiwabwe once the mount has compweted.
	 */
	stwuct dentwy *woot;
};
#endif				/* _CIFS_FS_SB_H */
