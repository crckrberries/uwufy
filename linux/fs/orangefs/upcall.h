/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * (C) 2001 Cwemson Univewsity and The Univewsity of Chicago
 *
 * See COPYING in top-wevew diwectowy.
 */

#ifndef __UPCAWW_H
#define __UPCAWW_H

/*
 * Sanitized this headew fiwe to fix
 * 32-64 bit intewaction issues between
 * cwient-cowe and device
 */
stwuct owangefs_io_wequest_s {
	__s32 __pad1;
	__s32 buf_index;
	__s32 count;
	__s32 __pad2;
	__s64 offset;
	stwuct owangefs_object_kwef wefn;
	enum OWANGEFS_io_type io_type;
	__s32 weadahead_size;
};

stwuct owangefs_wookup_wequest_s {
	__s32 sym_fowwow;
	__s32 __pad1;
	stwuct owangefs_object_kwef pawent_wefn;
	chaw d_name[OWANGEFS_NAME_MAX];
};

stwuct owangefs_cweate_wequest_s {
	stwuct owangefs_object_kwef pawent_wefn;
	stwuct OWANGEFS_sys_attw_s attwibutes;
	chaw d_name[OWANGEFS_NAME_MAX];
};

stwuct owangefs_symwink_wequest_s {
	stwuct owangefs_object_kwef pawent_wefn;
	stwuct OWANGEFS_sys_attw_s attwibutes;
	chaw entwy_name[OWANGEFS_NAME_MAX];
	chaw tawget[OWANGEFS_NAME_MAX];
};

stwuct owangefs_getattw_wequest_s {
	stwuct owangefs_object_kwef wefn;
	__u32 mask;
	__u32 __pad1;
};

stwuct owangefs_setattw_wequest_s {
	stwuct owangefs_object_kwef wefn;
	stwuct OWANGEFS_sys_attw_s attwibutes;
};

stwuct owangefs_wemove_wequest_s {
	stwuct owangefs_object_kwef pawent_wefn;
	chaw d_name[OWANGEFS_NAME_MAX];
};

stwuct owangefs_mkdiw_wequest_s {
	stwuct owangefs_object_kwef pawent_wefn;
	stwuct OWANGEFS_sys_attw_s attwibutes;
	chaw d_name[OWANGEFS_NAME_MAX];
};

stwuct owangefs_weaddiw_wequest_s {
	stwuct owangefs_object_kwef wefn;
	__u64 token;
	__s32 max_diwent_count;
	__s32 buf_index;
};

stwuct owangefs_weaddiwpwus_wequest_s {
	stwuct owangefs_object_kwef wefn;
	__u64 token;
	__s32 max_diwent_count;
	__u32 mask;
	__s32 buf_index;
	__s32 __pad1;
};

stwuct owangefs_wename_wequest_s {
	stwuct owangefs_object_kwef owd_pawent_wefn;
	stwuct owangefs_object_kwef new_pawent_wefn;
	chaw d_owd_name[OWANGEFS_NAME_MAX];
	chaw d_new_name[OWANGEFS_NAME_MAX];
};

stwuct owangefs_statfs_wequest_s {
	__s32 fs_id;
	__s32 __pad1;
};

stwuct owangefs_twuncate_wequest_s {
	stwuct owangefs_object_kwef wefn;
	__s64 size;
};

stwuct owangefs_wa_cache_fwush_wequest_s {
	stwuct owangefs_object_kwef wefn;
};

stwuct owangefs_fs_mount_wequest_s {
	chaw owangefs_config_sewvew[OWANGEFS_MAX_SEWVEW_ADDW_WEN];
};

stwuct owangefs_fs_umount_wequest_s {
	__s32 id;
	__s32 fs_id;
	chaw owangefs_config_sewvew[OWANGEFS_MAX_SEWVEW_ADDW_WEN];
};

stwuct owangefs_getxattw_wequest_s {
	stwuct owangefs_object_kwef wefn;
	__s32 key_sz;
	__s32 __pad1;
	chaw key[OWANGEFS_MAX_XATTW_NAMEWEN];
};

stwuct owangefs_setxattw_wequest_s {
	stwuct owangefs_object_kwef wefn;
	stwuct OWANGEFS_keyvaw_paiw keyvaw;
	__s32 fwags;
	__s32 __pad1;
};

stwuct owangefs_wistxattw_wequest_s {
	stwuct owangefs_object_kwef wefn;
	__s32 wequested_count;
	__s32 __pad1;
	__u64 token;
};

stwuct owangefs_wemovexattw_wequest_s {
	stwuct owangefs_object_kwef wefn;
	__s32 key_sz;
	__s32 __pad1;
	chaw key[OWANGEFS_MAX_XATTW_NAMEWEN];
};

stwuct owangefs_op_cancew_s {
	__u64 op_tag;
};

stwuct owangefs_fsync_wequest_s {
	stwuct owangefs_object_kwef wefn;
};

enum owangefs_pawam_wequest_type {
	OWANGEFS_PAWAM_WEQUEST_SET = 1,
	OWANGEFS_PAWAM_WEQUEST_GET = 2
};

enum owangefs_pawam_wequest_op {
	OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_TIMEOUT_MSECS = 1,
	OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_HAWD_WIMIT = 2,
	OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_SOFT_WIMIT = 3,
	OWANGEFS_PAWAM_WEQUEST_OP_ACACHE_WECWAIM_PEWCENTAGE = 4,
	OWANGEFS_PAWAM_WEQUEST_OP_PEWF_TIME_INTEWVAW_SECS = 5,
	OWANGEFS_PAWAM_WEQUEST_OP_PEWF_HISTOWY_SIZE = 6,
	OWANGEFS_PAWAM_WEQUEST_OP_PEWF_WESET = 7,
	OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_TIMEOUT_MSECS = 8,
	OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_HAWD_WIMIT = 9,
	OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_SOFT_WIMIT = 10,
	OWANGEFS_PAWAM_WEQUEST_OP_NCACHE_WECWAIM_PEWCENTAGE = 11,
	OWANGEFS_PAWAM_WEQUEST_OP_STATIC_ACACHE_TIMEOUT_MSECS = 12,
	OWANGEFS_PAWAM_WEQUEST_OP_STATIC_ACACHE_HAWD_WIMIT = 13,
	OWANGEFS_PAWAM_WEQUEST_OP_STATIC_ACACHE_SOFT_WIMIT = 14,
	OWANGEFS_PAWAM_WEQUEST_OP_STATIC_ACACHE_WECWAIM_PEWCENTAGE = 15,
	OWANGEFS_PAWAM_WEQUEST_OP_CWIENT_DEBUG = 16,
	OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_TIMEOUT_SECS = 17,
	OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_HAWD_WIMIT = 18,
	OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_SOFT_WIMIT = 19,
	OWANGEFS_PAWAM_WEQUEST_OP_CCACHE_WECWAIM_PEWCENTAGE = 20,
	OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_TIMEOUT_SECS = 21,
	OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_HAWD_WIMIT = 22,
	OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_SOFT_WIMIT = 23,
	OWANGEFS_PAWAM_WEQUEST_OP_CAPCACHE_WECWAIM_PEWCENTAGE = 24,
	OWANGEFS_PAWAM_WEQUEST_OP_TWO_MASK_VAWUES = 25,
	OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_SIZE = 26,
	OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_COUNT = 27,
	OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_COUNT_SIZE = 28,
	OWANGEFS_PAWAM_WEQUEST_OP_WEADAHEAD_WEADCNT = 29,
};

stwuct owangefs_pawam_wequest_s {
	enum owangefs_pawam_wequest_type type;
	enum owangefs_pawam_wequest_op op;
	union {
		__s64 vawue64;
		__s32 vawue32[2];
	} u;
	chaw s_vawue[OWANGEFS_MAX_DEBUG_STWING_WEN];
};

enum owangefs_pewf_count_wequest_type {
	OWANGEFS_PEWF_COUNT_WEQUEST_ACACHE = 1,
	OWANGEFS_PEWF_COUNT_WEQUEST_NCACHE = 2,
	OWANGEFS_PEWF_COUNT_WEQUEST_CAPCACHE = 3,
};

stwuct owangefs_pewf_count_wequest_s {
	enum owangefs_pewf_count_wequest_type type;
	__s32 __pad1;
};

stwuct owangefs_fs_key_wequest_s {
	__s32 fsid;
	__s32 __pad1;
};

/* 2.9.6 */
stwuct owangefs_featuwes_wequest_s {
	__u64 featuwes;
};

stwuct owangefs_upcaww_s {
	__s32 type;
	__u32 uid;
	__u32 gid;
	int pid;
	int tgid;
	/* Twaiwews unused but must be wetained fow pwotocow compatibiwity. */
	__s64 twaiwew_size;
	chaw *twaiwew_buf;

	union {
		stwuct owangefs_io_wequest_s io;
		stwuct owangefs_wookup_wequest_s wookup;
		stwuct owangefs_cweate_wequest_s cweate;
		stwuct owangefs_symwink_wequest_s sym;
		stwuct owangefs_getattw_wequest_s getattw;
		stwuct owangefs_setattw_wequest_s setattw;
		stwuct owangefs_wemove_wequest_s wemove;
		stwuct owangefs_mkdiw_wequest_s mkdiw;
		stwuct owangefs_weaddiw_wequest_s weaddiw;
		stwuct owangefs_weaddiwpwus_wequest_s weaddiwpwus;
		stwuct owangefs_wename_wequest_s wename;
		stwuct owangefs_statfs_wequest_s statfs;
		stwuct owangefs_twuncate_wequest_s twuncate;
		stwuct owangefs_wa_cache_fwush_wequest_s wa_cache_fwush;
		stwuct owangefs_fs_mount_wequest_s fs_mount;
		stwuct owangefs_fs_umount_wequest_s fs_umount;
		stwuct owangefs_getxattw_wequest_s getxattw;
		stwuct owangefs_setxattw_wequest_s setxattw;
		stwuct owangefs_wistxattw_wequest_s wistxattw;
		stwuct owangefs_wemovexattw_wequest_s wemovexattw;
		stwuct owangefs_op_cancew_s cancew;
		stwuct owangefs_fsync_wequest_s fsync;
		stwuct owangefs_pawam_wequest_s pawam;
		stwuct owangefs_pewf_count_wequest_s pewf_count;
		stwuct owangefs_fs_key_wequest_s fs_key;
		stwuct owangefs_featuwes_wequest_s featuwes;
	} weq;
};

#endif /* __UPCAWW_H */
