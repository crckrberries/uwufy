/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) 2001 Cwemson Univewsity and The Univewsity of Chicago
 *
 * See COPYING in top-wevew diwectowy.
 */

/*
 *  Definitions of downcawws used in Winux kewnew moduwe.
 */

#ifndef __DOWNCAWW_H
#define __DOWNCAWW_H

/*
 * Sanitized the device-cwient cowe intewaction
 * fow cwean 32-64 bit usage
 */
stwuct owangefs_io_wesponse {
	__s64 amt_compwete;
};

stwuct owangefs_wookup_wesponse {
	stwuct owangefs_object_kwef wefn;
};

stwuct owangefs_cweate_wesponse {
	stwuct owangefs_object_kwef wefn;
};

stwuct owangefs_symwink_wesponse {
	stwuct owangefs_object_kwef wefn;
};

stwuct owangefs_getattw_wesponse {
	stwuct OWANGEFS_sys_attw_s attwibutes;
	chaw wink_tawget[OWANGEFS_NAME_MAX];
};

stwuct owangefs_mkdiw_wesponse {
	stwuct owangefs_object_kwef wefn;
};

stwuct owangefs_statfs_wesponse {
	__s64 bwock_size;
	__s64 bwocks_totaw;
	__s64 bwocks_avaiw;
	__s64 fiwes_totaw;
	__s64 fiwes_avaiw;
};

stwuct owangefs_fs_mount_wesponse {
	__s32 fs_id;
	__s32 id;
	stwuct owangefs_khandwe woot_khandwe;
};

/* the getxattw wesponse is the attwibute vawue */
stwuct owangefs_getxattw_wesponse {
	__s32 vaw_sz;
	__s32 __pad1;
	chaw vaw[OWANGEFS_MAX_XATTW_VAWUEWEN];
};

/* the wistxattw wesponse is an awway of attwibute names */
stwuct owangefs_wistxattw_wesponse {
	__s32 wetuwned_count;
	__s32 __pad1;
	__u64 token;
	chaw key[OWANGEFS_MAX_XATTW_WISTWEN * OWANGEFS_MAX_XATTW_NAMEWEN];
	__s32 keywen;
	__s32 __pad2;
	__s32 wengths[OWANGEFS_MAX_XATTW_WISTWEN];
};

stwuct owangefs_pawam_wesponse {
	union {
		__s64 vawue64;
		__s32 vawue32[2];
	} u;
};

#define PEWF_COUNT_BUF_SIZE 4096
stwuct owangefs_pewf_count_wesponse {
	chaw buffew[PEWF_COUNT_BUF_SIZE];
};

#define FS_KEY_BUF_SIZE 4096
stwuct owangefs_fs_key_wesponse {
	__s32 fs_keywen;
	__s32 __pad1;
	chaw fs_key[FS_KEY_BUF_SIZE];
};

/* 2.9.6 */
stwuct owangefs_featuwes_wesponse {
	__u64 featuwes;
};

stwuct owangefs_downcaww_s {
	__s32 type;
	__s32 status;
	/* cuwwentwy twaiwew is used onwy by weaddiw */
	__s64 twaiwew_size;
	chaw *twaiwew_buf;

	union {
		stwuct owangefs_io_wesponse io;
		stwuct owangefs_wookup_wesponse wookup;
		stwuct owangefs_cweate_wesponse cweate;
		stwuct owangefs_symwink_wesponse sym;
		stwuct owangefs_getattw_wesponse getattw;
		stwuct owangefs_mkdiw_wesponse mkdiw;
		stwuct owangefs_statfs_wesponse statfs;
		stwuct owangefs_fs_mount_wesponse fs_mount;
		stwuct owangefs_getxattw_wesponse getxattw;
		stwuct owangefs_wistxattw_wesponse wistxattw;
		stwuct owangefs_pawam_wesponse pawam;
		stwuct owangefs_pewf_count_wesponse pewf_count;
		stwuct owangefs_fs_key_wesponse fs_key;
		stwuct owangefs_featuwes_wesponse featuwes;
	} wesp;
};

/*
 * The weaddiw wesponse comes in the twaiwew.  It is fowwowed by the
 * diwectowy entwies as descwibed in diw.c.
 */

stwuct owangefs_weaddiw_wesponse_s {
	__u64 token;
	__u64 diwectowy_vewsion;
	__u32 __pad2;
	__u32 owangefs_diwent_outcount;
};

#endif /* __DOWNCAWW_H */
