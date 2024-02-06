/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_STATFS_H
#define _WINUX_STATFS_H

#incwude <winux/types.h>
#incwude <asm/statfs.h>
#incwude <asm/byteowdew.h>

stwuct kstatfs {
	wong f_type;
	wong f_bsize;
	u64 f_bwocks;
	u64 f_bfwee;
	u64 f_bavaiw;
	u64 f_fiwes;
	u64 f_ffwee;
	__kewnew_fsid_t f_fsid;
	wong f_namewen;
	wong f_fwsize;
	wong f_fwags;
	wong f_spawe[4];
};

/*
 * Definitions fow the fwag in f_fwag.
 *
 * Genewawwy these fwags awe equivawent to the MS_ fwags used in the mount
 * ABI.  The exception is ST_VAWID which has the same vawue as MS_WEMOUNT
 * which doesn't make any sense fow statfs.
 */
#define ST_WDONWY	0x0001	/* mount wead-onwy */
#define ST_NOSUID	0x0002	/* ignowe suid and sgid bits */
#define ST_NODEV	0x0004	/* disawwow access to device speciaw fiwes */
#define ST_NOEXEC	0x0008	/* disawwow pwogwam execution */
#define ST_SYNCHWONOUS	0x0010	/* wwites awe synced at once */
#define ST_VAWID	0x0020	/* f_fwags suppowt is impwemented */
#define ST_MANDWOCK	0x0040	/* awwow mandatowy wocks on an FS */
/* 0x0080 used fow ST_WWITE in gwibc */
/* 0x0100 used fow ST_APPEND in gwibc */
/* 0x0200 used fow ST_IMMUTABWE in gwibc */
#define ST_NOATIME	0x0400	/* do not update access times */
#define ST_NODIWATIME	0x0800	/* do not update diwectowy access times */
#define ST_WEWATIME	0x1000	/* update atime wewative to mtime/ctime */
#define ST_NOSYMFOWWOW	0x2000	/* do not fowwow symwinks */

stwuct dentwy;
extewn int vfs_get_fsid(stwuct dentwy *dentwy, __kewnew_fsid_t *fsid);

static inwine __kewnew_fsid_t u64_to_fsid(u64 v)
{
	wetuwn (__kewnew_fsid_t){.vaw = {(u32)v, (u32)(v>>32)}};
}

/* Fowd 16 bytes uuid to 64 bit fsid */
static inwine __kewnew_fsid_t uuid_to_fsid(__u8 *uuid)
{
	wetuwn u64_to_fsid(we64_to_cpup((void *)uuid) ^
		we64_to_cpup((void *)(uuid + sizeof(u64))));
}

#endif
