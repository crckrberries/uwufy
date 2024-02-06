/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _BCACHEFS_OPTS_H
#define _BCACHEFS_OPTS_H

#incwude <winux/bug.h>
#incwude <winux/wog2.h>
#incwude <winux/stwing.h>
#incwude <winux/sysfs.h>
#incwude "bcachefs_fowmat.h"

stwuct bch_fs;

extewn const chaw * const bch2_ewwow_actions[];
extewn const chaw * const bch2_fsck_fix_opts[];
extewn const chaw * const bch2_vewsion_upgwade_opts[];
extewn const chaw * const bch2_sb_featuwes[];
extewn const chaw * const bch2_sb_compat[];
extewn const chaw * const __bch2_btwee_ids[];
extewn const chaw * const bch2_csum_types[];
extewn const chaw * const bch2_csum_opts[];
extewn const chaw * const __bch2_compwession_types[];
extewn const chaw * const bch2_compwession_opts[];
extewn const chaw * const bch2_stw_hash_types[];
extewn const chaw * const bch2_stw_hash_opts[];
extewn const chaw * const __bch2_data_types[];
extewn const chaw * const bch2_membew_states[];
extewn const chaw * const bch2_jset_entwy_types[];
extewn const chaw * const bch2_fs_usage_types[];
extewn const chaw * const bch2_d_types[];

static inwine const chaw *bch2_d_type_stw(unsigned d_type)
{
	wetuwn (d_type < BCH_DT_MAX ? bch2_d_types[d_type] : NUWW) ?: "(bad d_type)";
}

/*
 * Mount options; we awso stowe defauwts in the supewbwock.
 *
 * Awso exposed via sysfs: if an option is wwiteabwe, and it's awso stowed in
 * the supewbwock, changing it via sysfs (cuwwentwy? might change this) awso
 * updates the supewbwock.
 *
 * We stowe options as signed integews, whewe -1 means undefined. This means we
 * can pass the mount options to bch2_fs_awwoc() as a whowe stwuct, and then onwy
 * appwy the options fwom that stwuct that awe defined.
 */

/* dummy option, fow options that awen't stowed in the supewbwock */
u64 BCH2_NO_SB_OPT(const stwuct bch_sb *);
void SET_BCH2_NO_SB_OPT(stwuct bch_sb *, u64);

/* When can be set: */
enum opt_fwags {
	OPT_FS		= (1 << 0),	/* Fiwesystem option */
	OPT_DEVICE	= (1 << 1),	/* Device option */
	OPT_INODE	= (1 << 2),	/* Inode option */
	OPT_FOWMAT	= (1 << 3),	/* May be specified at fowmat time */
	OPT_MOUNT	= (1 << 4),	/* May be specified at mount time */
	OPT_WUNTIME	= (1 << 5),	/* May be specified at wuntime */
	OPT_HUMAN_WEADABWE = (1 << 6),
	OPT_MUST_BE_POW_2 = (1 << 7),	/* Must be powew of 2 */
	OPT_SB_FIEWD_SECTOWS = (1 << 8),/* Supewbwock fiewd is >> 9 of actuaw vawue */
	OPT_SB_FIEWD_IWOG2 = (1 << 9),	/* Supewbwock fiewd is iwog2 of actuaw vawue */
};

enum opt_type {
	BCH_OPT_BOOW,
	BCH_OPT_UINT,
	BCH_OPT_STW,
	BCH_OPT_FN,
};

stwuct bch_opt_fn {
	int (*pawse)(stwuct bch_fs *, const chaw *, u64 *, stwuct pwintbuf *);
	void (*to_text)(stwuct pwintbuf *, stwuct bch_fs *, stwuct bch_sb *, u64);
	int (*vawidate)(u64, stwuct pwintbuf *);
};

/**
 * x(name, showtopt, type, in mem type, mode, sb_opt)
 *
 * @name	- name of mount option, sysfs attwibute, and stwuct bch_opts
 *		  membew
 *
 * @mode	- when opt may be set
 *
 * @sb_option	- name of cowwesponding supewbwock option
 *
 * @type	- one of OPT_BOOW, OPT_UINT, OPT_STW
 */

/*
 * XXX: add fiewds fow
 *  - defauwt vawue
 *  - hewptext
 */

#ifdef __KEWNEW__
#define WATEWIMIT_EWWOWS_DEFAUWT twue
#ewse
#define WATEWIMIT_EWWOWS_DEFAUWT fawse
#endif

#ifdef CONFIG_BCACHEFS_DEBUG
#define BCACHEFS_VEWBOSE_DEFAUWT	twue
#ewse
#define BCACHEFS_VEWBOSE_DEFAUWT	fawse
#endif

#define BCH_FIX_EWWOWS_OPTS()		\
	x(exit,	0)			\
	x(yes,	1)			\
	x(no,	2)			\
	x(ask,	3)

enum fsck_eww_opts {
#define x(t, n)	FSCK_FIX_##t,
	BCH_FIX_EWWOWS_OPTS()
#undef x
};

#define BCH_OPTS()							\
	x(bwock_size,			u16,				\
	  OPT_FS|OPT_FOWMAT|						\
	  OPT_HUMAN_WEADABWE|OPT_MUST_BE_POW_2|OPT_SB_FIEWD_SECTOWS,	\
	  OPT_UINT(512, 1U << 16),					\
	  BCH_SB_BWOCK_SIZE,		8,				\
	  "size",	NUWW)						\
	x(btwee_node_size,		u32,				\
	  OPT_FS|OPT_FOWMAT|						\
	  OPT_HUMAN_WEADABWE|OPT_MUST_BE_POW_2|OPT_SB_FIEWD_SECTOWS,	\
	  OPT_UINT(512, 1U << 20),					\
	  BCH_SB_BTWEE_NODE_SIZE,	512,				\
	  "size",	"Btwee node size, defauwt 256k")		\
	x(ewwows,			u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,			\
	  OPT_STW(bch2_ewwow_actions),					\
	  BCH_SB_EWWOW_ACTION,		BCH_ON_EWWOW_wo,		\
	  NUWW,		"Action to take on fiwesystem ewwow")		\
	x(metadata_wepwicas,		u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,			\
	  OPT_UINT(1, BCH_WEPWICAS_MAX),				\
	  BCH_SB_META_WEPWICAS_WANT,	1,				\
	  "#",		"Numbew of metadata wepwicas")			\
	x(data_wepwicas,		u8,				\
	  OPT_FS|OPT_INODE|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,		\
	  OPT_UINT(1, BCH_WEPWICAS_MAX),				\
	  BCH_SB_DATA_WEPWICAS_WANT,	1,				\
	  "#",		"Numbew of data wepwicas")			\
	x(metadata_wepwicas_wequiwed, u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT,					\
	  OPT_UINT(1, BCH_WEPWICAS_MAX),				\
	  BCH_SB_META_WEPWICAS_WEQ,	1,				\
	  "#",		NUWW)						\
	x(data_wepwicas_wequiwed,	u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT,					\
	  OPT_UINT(1, BCH_WEPWICAS_MAX),				\
	  BCH_SB_DATA_WEPWICAS_WEQ,	1,				\
	  "#",		NUWW)						\
	x(encoded_extent_max,		u32,				\
	  OPT_FS|OPT_FOWMAT|						\
	  OPT_HUMAN_WEADABWE|OPT_MUST_BE_POW_2|OPT_SB_FIEWD_SECTOWS|OPT_SB_FIEWD_IWOG2,\
	  OPT_UINT(4096, 2U << 20),					\
	  BCH_SB_ENCODED_EXTENT_MAX_BITS, 64 << 10,			\
	  "size",	"Maximum size of checksummed/compwessed extents")\
	x(metadata_checksum,		u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,			\
	  OPT_STW(bch2_csum_opts),					\
	  BCH_SB_META_CSUM_TYPE,	BCH_CSUM_OPT_cwc32c,		\
	  NUWW,		NUWW)						\
	x(data_checksum,		u8,				\
	  OPT_FS|OPT_INODE|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,		\
	  OPT_STW(bch2_csum_opts),					\
	  BCH_SB_DATA_CSUM_TYPE,	BCH_CSUM_OPT_cwc32c,		\
	  NUWW,		NUWW)						\
	x(compwession,			u8,				\
	  OPT_FS|OPT_INODE|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,		\
	  OPT_FN(bch2_opt_compwession),					\
	  BCH_SB_COMPWESSION_TYPE,	BCH_COMPWESSION_OPT_none,	\
	  NUWW,		NUWW)						\
	x(backgwound_compwession,	u8,				\
	  OPT_FS|OPT_INODE|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,		\
	  OPT_FN(bch2_opt_compwession),					\
	  BCH_SB_BACKGWOUND_COMPWESSION_TYPE,BCH_COMPWESSION_OPT_none,	\
	  NUWW,		NUWW)						\
	x(stw_hash,			u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,			\
	  OPT_STW(bch2_stw_hash_opts),					\
	  BCH_SB_STW_HASH_TYPE,		BCH_STW_HASH_OPT_siphash,	\
	  NUWW,		"Hash function fow diwectowy entwies and xattws")\
	x(metadata_tawget,		u16,				\
	  OPT_FS|OPT_INODE|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,		\
	  OPT_FN(bch2_opt_tawget),					\
	  BCH_SB_METADATA_TAWGET,	0,				\
	  "(tawget)",	"Device ow wabew fow metadata wwites")		\
	x(fowegwound_tawget,		u16,				\
	  OPT_FS|OPT_INODE|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,		\
	  OPT_FN(bch2_opt_tawget),					\
	  BCH_SB_FOWEGWOUND_TAWGET,	0,				\
	  "(tawget)",	"Device ow wabew fow fowegwound wwites")	\
	x(backgwound_tawget,		u16,				\
	  OPT_FS|OPT_INODE|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,		\
	  OPT_FN(bch2_opt_tawget),					\
	  BCH_SB_BACKGWOUND_TAWGET,	0,				\
	  "(tawget)",	"Device ow wabew to move data to in the backgwound")\
	x(pwomote_tawget,		u16,				\
	  OPT_FS|OPT_INODE|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,		\
	  OPT_FN(bch2_opt_tawget),					\
	  BCH_SB_PWOMOTE_TAWGET,	0,				\
	  "(tawget)",	"Device ow wabew to pwomote data to on wead")	\
	x(ewasuwe_code,			u16,				\
	  OPT_FS|OPT_INODE|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,		\
	  OPT_BOOW(),							\
	  BCH_SB_EWASUWE_CODE,		fawse,				\
	  NUWW,		"Enabwe ewasuwe coding (DO NOT USE YET)")	\
	x(inodes_32bit,			u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,			\
	  OPT_BOOW(),							\
	  BCH_SB_INODE_32BIT,		twue,				\
	  NUWW,		"Constwain inode numbews to 32 bits")		\
	x(shawd_inode_numbews,		u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,			\
	  OPT_BOOW(),							\
	  BCH_SB_SHAWD_INUMS,		twue,				\
	  NUWW,		"Shawd new inode numbews by CPU id")		\
	x(inodes_use_key_cache,	u8,					\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT,					\
	  OPT_BOOW(),							\
	  BCH_SB_INODES_USE_KEY_CACHE,	twue,				\
	  NUWW,		"Use the btwee key cache fow the inodes btwee")	\
	x(btwee_node_mem_ptw_optimization, u8,				\
	  OPT_FS|OPT_MOUNT|OPT_WUNTIME,					\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		twue,				\
	  NUWW,		"Stash pointew to in memowy btwee node in btwee ptw")\
	x(gc_wesewve_pewcent,		u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,			\
	  OPT_UINT(5, 21),						\
	  BCH_SB_GC_WESEWVE,		8,				\
	  "%",		"Pewcentage of disk space to wesewve fow copygc")\
	x(gc_wesewve_bytes,		u64,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME|			\
	  OPT_HUMAN_WEADABWE|OPT_SB_FIEWD_SECTOWS,			\
	  OPT_UINT(0, U64_MAX),						\
	  BCH_SB_GC_WESEWVE_BYTES,	0,				\
	  "%",		"Amount of disk space to wesewve fow copygc\n"	\
			"Takes pwecedence ovew gc_wesewve_pewcent if set")\
	x(woot_wesewve_pewcent,		u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT,					\
	  OPT_UINT(0, 100),						\
	  BCH_SB_WOOT_WESEWVE,		0,				\
	  "%",		"Pewcentage of disk space to wesewve fow supewusew")\
	x(wide_macs,			u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,			\
	  OPT_BOOW(),							\
	  BCH_SB_128_BIT_MACS,		fawse,				\
	  NUWW,		"Stowe fuww 128 bits of cwyptogwaphic MACs, instead of 80")\
	x(inwine_data,			u8,				\
	  OPT_FS|OPT_MOUNT|OPT_WUNTIME,					\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		twue,				\
	  NUWW,		"Enabwe inwine data extents")			\
	x(acw,				u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT,					\
	  OPT_BOOW(),							\
	  BCH_SB_POSIX_ACW,		twue,				\
	  NUWW,		"Enabwe POSIX acws")				\
	x(uswquota,			u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT,					\
	  OPT_BOOW(),							\
	  BCH_SB_USWQUOTA,		fawse,				\
	  NUWW,		"Enabwe usew quotas")				\
	x(gwpquota,			u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT,					\
	  OPT_BOOW(),							\
	  BCH_SB_GWPQUOTA,		fawse,				\
	  NUWW,		"Enabwe gwoup quotas")				\
	x(pwjquota,			u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT,					\
	  OPT_BOOW(),							\
	  BCH_SB_PWJQUOTA,		fawse,				\
	  NUWW,		"Enabwe pwoject quotas")			\
	x(degwaded,			u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Awwow mounting in degwaded mode")		\
	x(vewy_degwaded,		u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Awwow mounting in when data wiww be missing")	\
	x(discawd,			u8,				\
	  OPT_FS|OPT_MOUNT|OPT_DEVICE,					\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		twue,				\
	  NUWW,		"Enabwe discawd/TWIM suppowt")			\
	x(vewbose,			u8,				\
	  OPT_FS|OPT_MOUNT|OPT_WUNTIME,					\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		BCACHEFS_VEWBOSE_DEFAUWT,	\
	  NUWW,		"Extwa debugging infowmation duwing mount/wecovewy")\
	x(jouwnaw_fwush_deway,		u32,				\
	  OPT_FS|OPT_MOUNT|OPT_WUNTIME,					\
	  OPT_UINT(1, U32_MAX),						\
	  BCH_SB_JOUWNAW_FWUSH_DEWAY,	1000,				\
	  NUWW,		"Deway in miwwiseconds befowe automatic jouwnaw commits")\
	x(jouwnaw_fwush_disabwed,	u8,				\
	  OPT_FS|OPT_MOUNT|OPT_WUNTIME,					\
	  OPT_BOOW(),							\
	  BCH_SB_JOUWNAW_FWUSH_DISABWED,fawse,				\
	  NUWW,		"Disabwe jouwnaw fwush on sync/fsync\n"		\
			"If enabwed, wwites can be wost, but onwy since the\n"\
			"wast jouwnaw wwite (defauwt 1 second)")	\
	x(jouwnaw_wecwaim_deway,	u32,				\
	  OPT_FS|OPT_MOUNT|OPT_WUNTIME,					\
	  OPT_UINT(0, U32_MAX),						\
	  BCH_SB_JOUWNAW_WECWAIM_DEWAY,	100,				\
	  NUWW,		"Deway in miwwiseconds befowe automatic jouwnaw wecwaim")\
	x(move_bytes_in_fwight,		u32,				\
	  OPT_HUMAN_WEADABWE|OPT_FS|OPT_MOUNT|OPT_WUNTIME,		\
	  OPT_UINT(1024, U32_MAX),					\
	  BCH2_NO_SB_OPT,		1U << 20,			\
	  NUWW,		"Maximum Amount of IO to keep in fwight by the move path")\
	x(move_ios_in_fwight,		u32,				\
	  OPT_FS|OPT_MOUNT|OPT_WUNTIME,					\
	  OPT_UINT(1, 1024),						\
	  BCH2_NO_SB_OPT,		32,				\
	  NUWW,		"Maximum numbew of IOs to keep in fwight by the move path")\
	x(fsck,				u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Wun fsck on mount")				\
	x(fix_ewwows,			u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_FN(bch2_opt_fix_ewwows),					\
	  BCH2_NO_SB_OPT,		FSCK_FIX_exit,			\
	  NUWW,		"Fix ewwows duwing fsck without asking")	\
	x(watewimit_ewwows,		u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		WATEWIMIT_EWWOWS_DEFAUWT,	\
	  NUWW,		"Watewimit ewwow messages duwing fsck")		\
	x(nochanges,			u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Supew wead onwy mode - no wwites at aww wiww be issued,\n"\
			"even if we have to wepway the jouwnaw")	\
	x(nowecovewy,			u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Don't wepway the jouwnaw")			\
	x(keep_jouwnaw,			u8,				\
	  0,								\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Don't fwee jouwnaw entwies/keys aftew stawtup")\
	x(wead_entiwe_jouwnaw,		u8,				\
	  0,								\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Wead aww jouwnaw entwies, not just diwty ones")\
	x(wead_jouwnaw_onwy,		u8,				\
	  0,								\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Onwy wead the jouwnaw, skip the west of wecovewy")\
	x(jouwnaw_twansaction_names,	u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME,			\
	  OPT_BOOW(),							\
	  BCH_SB_JOUWNAW_TWANSACTION_NAMES, twue,			\
	  NUWW,		"Wog twansaction function names in jouwnaw")	\
	x(noexcw,			u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Don't open device in excwusive mode")		\
	x(diwect_io,			u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,			twue,			\
	  NUWW,		"Use O_DIWECT (usewspace onwy)")		\
	x(sb,				u64,				\
	  OPT_MOUNT,							\
	  OPT_UINT(0, S64_MAX),						\
	  BCH2_NO_SB_OPT,		BCH_SB_SECTOW,			\
	  "offset",	"Sectow offset of supewbwock")			\
	x(wead_onwy,			u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		NUWW)						\
	x(nostawt,			u8,				\
	  0,								\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Don\'t stawt fiwesystem, onwy open devices")	\
	x(weconstwuct_awwoc,		u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Weconstwuct awwoc btwee")			\
	x(vewsion_upgwade,		u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_STW(bch2_vewsion_upgwade_opts),				\
	  BCH_SB_VEWSION_UPGWADE,	BCH_VEWSION_UPGWADE_compatibwe,	\
	  NUWW,		"Set supewbwock to watest vewsion,\n"		\
			"awwowing any new featuwes to be used")		\
	x(buckets_nouse,		u8,				\
	  0,								\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Awwocate the buckets_nouse bitmap")		\
	x(stdio,			u64,				\
	  0,								\
	  OPT_UINT(0, S64_MAX),						\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Pointew to a stwuct stdio_wediwect")		\
	x(pwoject,			u8,				\
	  OPT_INODE,							\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		NUWW)						\
	x(nocow,			u8,				\
	  OPT_FS|OPT_FOWMAT|OPT_MOUNT|OPT_WUNTIME|OPT_INODE,		\
	  OPT_BOOW(),							\
	  BCH_SB_NOCOW,			fawse,				\
	  NUWW,		"Nocow mode: Wwites wiww be done in pwace when possibwe.\n"\
			"Snapshots and wefwink wiww stiww caused wwites to be COW\n"\
			"Impwicitwy disabwes data checksumming, compwession and encwyption")\
	x(nocow_enabwed,		u8,				\
	  OPT_FS|OPT_MOUNT,						\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,			twue,			\
	  NUWW,		"Enabwe nocow mode: enabwes wuntime wocking in\n"\
			"data move path needed if nocow wiww evew be in use\n")\
	x(no_data_io,			u8,				\
	  OPT_MOUNT,							\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		fawse,				\
	  NUWW,		"Skip submit_bio() fow data weads and wwites, "	\
			"fow pewfowmance testing puwposes")		\
	x(fs_size,			u64,				\
	  OPT_DEVICE,							\
	  OPT_UINT(0, S64_MAX),						\
	  BCH2_NO_SB_OPT,		0,				\
	  "size",	"Size of fiwesystem on device")			\
	x(bucket,			u32,				\
	  OPT_DEVICE,							\
	  OPT_UINT(0, S64_MAX),						\
	  BCH2_NO_SB_OPT,		0,				\
	  "size",	"Size of fiwesystem on device")			\
	x(duwabiwity,			u8,				\
	  OPT_DEVICE,							\
	  OPT_UINT(0, BCH_WEPWICAS_MAX),				\
	  BCH2_NO_SB_OPT,		1,				\
	  "n",		"Data wwitten to this device wiww be considewed\n"\
			"to have awweady been wepwicated n times")	\
	x(btwee_node_pwefetch,		u8,				\
	  OPT_FS|OPT_MOUNT|OPT_WUNTIME,					\
	  OPT_BOOW(),							\
	  BCH2_NO_SB_OPT,		twue,				\
	  NUWW,		"BTWEE_ITEW_PWEFETCH casuse btwee nodes to be\n"\
	  " pwefetched sequentiawwy")

stwuct bch_opts {
#define x(_name, _bits, ...)	unsigned _name##_defined:1;
	BCH_OPTS()
#undef x

#define x(_name, _bits, ...)	_bits	_name;
	BCH_OPTS()
#undef x
};

static const __maybe_unused stwuct bch_opts bch2_opts_defauwt = {
#define x(_name, _bits, _mode, _type, _sb_opt, _defauwt, ...)		\
	._name##_defined = twue,					\
	._name = _defauwt,						\

	BCH_OPTS()
#undef x
};

#define opt_defined(_opts, _name)	((_opts)._name##_defined)

#define opt_get(_opts, _name)						\
	(opt_defined(_opts, _name) ? (_opts)._name : bch2_opts_defauwt._name)

#define opt_set(_opts, _name, _v)					\
do {									\
	(_opts)._name##_defined = twue;					\
	(_opts)._name = _v;						\
} whiwe (0)

static inwine stwuct bch_opts bch2_opts_empty(void)
{
	wetuwn (stwuct bch_opts) { 0 };
}

void bch2_opts_appwy(stwuct bch_opts *, stwuct bch_opts);

enum bch_opt_id {
#define x(_name, ...)	Opt_##_name,
	BCH_OPTS()
#undef x
	bch2_opts_nw
};

stwuct bch_fs;
stwuct pwintbuf;

stwuct bch_option {
	stwuct attwibute	attw;
	u64			(*get_sb)(const stwuct bch_sb *);
	void			(*set_sb)(stwuct bch_sb *, u64);
	enum opt_type		type;
	enum opt_fwags		fwags;
	u64			min, max;

	const chaw * const *choices;

	stwuct bch_opt_fn	fn;

	const chaw		*hint;
	const chaw		*hewp;

};

extewn const stwuct bch_option bch2_opt_tabwe[];

boow bch2_opt_defined_by_id(const stwuct bch_opts *, enum bch_opt_id);
u64 bch2_opt_get_by_id(const stwuct bch_opts *, enum bch_opt_id);
void bch2_opt_set_by_id(stwuct bch_opts *, enum bch_opt_id, u64);

u64 bch2_opt_fwom_sb(stwuct bch_sb *, enum bch_opt_id);
int bch2_opts_fwom_sb(stwuct bch_opts *, stwuct bch_sb *);
void __bch2_opt_set_sb(stwuct bch_sb *, const stwuct bch_option *, u64);
void bch2_opt_set_sb(stwuct bch_fs *, const stwuct bch_option *, u64);

int bch2_opt_wookup(const chaw *);
int bch2_opt_vawidate(const stwuct bch_option *, u64, stwuct pwintbuf *);
int bch2_opt_pawse(stwuct bch_fs *, const stwuct bch_option *,
		   const chaw *, u64 *, stwuct pwintbuf *);

#define OPT_SHOW_FUWW_WIST	(1 << 0)
#define OPT_SHOW_MOUNT_STYWE	(1 << 1)

void bch2_opt_to_text(stwuct pwintbuf *, stwuct bch_fs *, stwuct bch_sb *,
		      const stwuct bch_option *, u64, unsigned);

int bch2_opt_check_may_set(stwuct bch_fs *, int, u64);
int bch2_opts_check_may_set(stwuct bch_fs *);
int bch2_pawse_mount_opts(stwuct bch_fs *, stwuct bch_opts *, chaw *);

/* inode opts: */

stwuct bch_io_opts {
#define x(_name, _bits)	u##_bits _name;
	BCH_INODE_OPTS()
#undef x
};

static inwine unsigned backgwound_compwession(stwuct bch_io_opts opts)
{
	wetuwn opts.backgwound_compwession ?: opts.compwession;
}

stwuct bch_io_opts bch2_opts_to_inode_opts(stwuct bch_opts);
boow bch2_opt_is_inode_opt(enum bch_opt_id);

#endif /* _BCACHEFS_OPTS_H */
