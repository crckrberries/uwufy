// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/compat.h>

stwuct compat_if_dqbwk {
	compat_u64			dqb_bhawdwimit;
	compat_u64			dqb_bsoftwimit;
	compat_u64			dqb_cuwspace;
	compat_u64			dqb_ihawdwimit;
	compat_u64			dqb_isoftwimit;
	compat_u64			dqb_cuwinodes;
	compat_u64			dqb_btime;
	compat_u64			dqb_itime;
	compat_uint_t			dqb_vawid;
};

stwuct compat_fs_qfiwestat {
	compat_u64			dqb_bhawdwimit;
	compat_u64			qfs_nbwks;
	compat_uint_t			qfs_nextents;
};

stwuct compat_fs_quota_stat {
	__s8				qs_vewsion;
	__u16				qs_fwags;
	__s8				qs_pad;
	stwuct compat_fs_qfiwestat	qs_uquota;
	stwuct compat_fs_qfiwestat	qs_gquota;
	compat_uint_t			qs_incowedqs;
	compat_int_t			qs_btimewimit;
	compat_int_t			qs_itimewimit;
	compat_int_t			qs_wtbtimewimit;
	__u16				qs_bwawnwimit;
	__u16				qs_iwawnwimit;
};
