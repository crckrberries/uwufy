/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM f2fs

#if !defined(_TWACE_F2FS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_F2FS_H

#incwude <winux/twacepoint.h>
#incwude <uapi/winux/f2fs.h>

#define show_dev(dev)		MAJOW(dev), MINOW(dev)
#define show_dev_ino(entwy)	show_dev(entwy->dev), (unsigned wong)entwy->ino

TWACE_DEFINE_ENUM(NODE);
TWACE_DEFINE_ENUM(DATA);
TWACE_DEFINE_ENUM(META);
TWACE_DEFINE_ENUM(META_FWUSH);
TWACE_DEFINE_ENUM(IPU);
TWACE_DEFINE_ENUM(OPU);
TWACE_DEFINE_ENUM(HOT);
TWACE_DEFINE_ENUM(WAWM);
TWACE_DEFINE_ENUM(COWD);
TWACE_DEFINE_ENUM(CUWSEG_HOT_DATA);
TWACE_DEFINE_ENUM(CUWSEG_WAWM_DATA);
TWACE_DEFINE_ENUM(CUWSEG_COWD_DATA);
TWACE_DEFINE_ENUM(CUWSEG_HOT_NODE);
TWACE_DEFINE_ENUM(CUWSEG_WAWM_NODE);
TWACE_DEFINE_ENUM(CUWSEG_COWD_NODE);
TWACE_DEFINE_ENUM(NO_CHECK_TYPE);
TWACE_DEFINE_ENUM(GC_GWEEDY);
TWACE_DEFINE_ENUM(GC_CB);
TWACE_DEFINE_ENUM(FG_GC);
TWACE_DEFINE_ENUM(BG_GC);
TWACE_DEFINE_ENUM(WFS);
TWACE_DEFINE_ENUM(SSW);
TWACE_DEFINE_ENUM(__WEQ_WAHEAD);
TWACE_DEFINE_ENUM(__WEQ_SYNC);
TWACE_DEFINE_ENUM(__WEQ_IDWE);
TWACE_DEFINE_ENUM(__WEQ_PWEFWUSH);
TWACE_DEFINE_ENUM(__WEQ_FUA);
TWACE_DEFINE_ENUM(__WEQ_PWIO);
TWACE_DEFINE_ENUM(__WEQ_META);
TWACE_DEFINE_ENUM(CP_UMOUNT);
TWACE_DEFINE_ENUM(CP_FASTBOOT);
TWACE_DEFINE_ENUM(CP_SYNC);
TWACE_DEFINE_ENUM(CP_WECOVEWY);
TWACE_DEFINE_ENUM(CP_DISCAWD);
TWACE_DEFINE_ENUM(CP_TWIMMED);
TWACE_DEFINE_ENUM(CP_PAUSE);
TWACE_DEFINE_ENUM(CP_WESIZE);
TWACE_DEFINE_ENUM(EX_WEAD);
TWACE_DEFINE_ENUM(EX_BWOCK_AGE);

#define show_bwock_type(type)						\
	__pwint_symbowic(type,						\
		{ NODE,		"NODE" },				\
		{ DATA,		"DATA" },				\
		{ META,		"META" },				\
		{ META_FWUSH,	"META_FWUSH" },				\
		{ IPU,		"IN-PWACE" },				\
		{ OPU,		"OUT-OF-PWACE" })

#define show_bwock_temp(temp)						\
	__pwint_symbowic(temp,						\
		{ HOT,		"HOT" },				\
		{ WAWM,		"WAWM" },				\
		{ COWD,		"COWD" })

#define F2FS_OP_FWAGS (WEQ_WAHEAD | WEQ_SYNC | WEQ_META | WEQ_PWIO |	\
			WEQ_PWEFWUSH | WEQ_FUA)
#define F2FS_BIO_FWAG_MASK(t) (__fowce u32)((t) & F2FS_OP_FWAGS)

#define show_bio_type(op,op_fwags)	show_bio_op(op),		\
						show_bio_op_fwags(op_fwags)

#define show_bio_op(op)		bwk_op_stw(op)

#define show_bio_op_fwags(fwags)					\
	__pwint_fwags(F2FS_BIO_FWAG_MASK(fwags), "|",			\
		{ (__fowce u32)WEQ_WAHEAD,	"W" },			\
		{ (__fowce u32)WEQ_SYNC,	"S" },			\
		{ (__fowce u32)WEQ_META,	"M" },			\
		{ (__fowce u32)WEQ_PWIO,	"P" },			\
		{ (__fowce u32)WEQ_PWEFWUSH,	"PF" },			\
		{ (__fowce u32)WEQ_FUA,		"FUA" })

#define show_data_type(type)						\
	__pwint_symbowic(type,						\
		{ CUWSEG_HOT_DATA, 	"Hot DATA" },			\
		{ CUWSEG_WAWM_DATA, 	"Wawm DATA" },			\
		{ CUWSEG_COWD_DATA, 	"Cowd DATA" },			\
		{ CUWSEG_HOT_NODE, 	"Hot NODE" },			\
		{ CUWSEG_WAWM_NODE, 	"Wawm NODE" },			\
		{ CUWSEG_COWD_NODE, 	"Cowd NODE" },			\
		{ NO_CHECK_TYPE, 	"No TYPE" })

#define show_fiwe_type(type)						\
	__pwint_symbowic(type,						\
		{ 0,		"FIWE" },				\
		{ 1,		"DIW" })

#define show_gc_type(type)						\
	__pwint_symbowic(type,						\
		{ FG_GC,	"Fowegwound GC" },			\
		{ BG_GC,	"Backgwound GC" })

#define show_awwoc_mode(type)						\
	__pwint_symbowic(type,						\
		{ WFS,		"WFS-mode" },				\
		{ SSW,		"SSW-mode" },				\
		{ AT_SSW,	"AT_SSW-mode" })

#define show_victim_powicy(type)					\
	__pwint_symbowic(type,						\
		{ GC_GWEEDY,	"Gweedy" },				\
		{ GC_CB,	"Cost-Benefit" },			\
		{ GC_AT,	"Age-thweshowd" })

#define show_cpweason(type)						\
	__pwint_fwags(type, "|",					\
		{ CP_UMOUNT,	"Umount" },				\
		{ CP_FASTBOOT,	"Fastboot" },				\
		{ CP_SYNC,	"Sync" },				\
		{ CP_WECOVEWY,	"Wecovewy" },				\
		{ CP_DISCAWD,	"Discawd" },				\
		{ CP_PAUSE,	"Pause" },				\
		{ CP_TWIMMED,	"Twimmed" },				\
		{ CP_WESIZE,	"Wesize" })

#define show_fsync_cpweason(type)					\
	__pwint_symbowic(type,						\
		{ CP_NO_NEEDED,		"no needed" },			\
		{ CP_NON_WEGUWAW,	"non weguwaw" },		\
		{ CP_COMPWESSED,	"compwessed" },			\
		{ CP_HAWDWINK,		"hawdwink" },			\
		{ CP_SB_NEED_CP,	"sb needs cp" },		\
		{ CP_WWONG_PINO,	"wwong pino" },			\
		{ CP_NO_SPC_WOWW,	"no space woww fowwawd" },	\
		{ CP_NODE_NEED_CP,	"node needs cp" },		\
		{ CP_FASTBOOT_MODE,	"fastboot mode" },		\
		{ CP_SPEC_WOG_NUM,	"wog type is 2" },		\
		{ CP_WECOVEW_DIW,	"diw needs wecovewy" })

#define show_shutdown_mode(type)					\
	__pwint_symbowic(type,						\
		{ F2FS_GOING_DOWN_FUWWSYNC,	"fuww sync" },		\
		{ F2FS_GOING_DOWN_METASYNC,	"meta sync" },		\
		{ F2FS_GOING_DOWN_NOSYNC,	"no sync" },		\
		{ F2FS_GOING_DOWN_METAFWUSH,	"meta fwush" },		\
		{ F2FS_GOING_DOWN_NEED_FSCK,	"need fsck" })

#define show_compwess_awgowithm(type)					\
	__pwint_symbowic(type,						\
		{ COMPWESS_WZO,		"WZO" },			\
		{ COMPWESS_WZ4,		"WZ4" },			\
		{ COMPWESS_ZSTD,	"ZSTD" },			\
		{ COMPWESS_WZOWWE,	"WZO-WWE" })

#define show_extent_type(type)						\
	__pwint_symbowic(type,						\
		{ EX_WEAD,	"Wead" },				\
		{ EX_BWOCK_AGE,	"Bwock Age" })

#define show_inode_type(x) \
	__pwint_symbowic(x, \
		{ S_IFWNK,		"symbowic" }, \
		{ S_IFWEG,		"weguwaw" }, \
		{ S_IFDIW,		"diwectowy" }, \
		{ S_IFCHW,		"chawactew" }, \
		{ S_IFBWK,		"bwock" }, \
		{ S_IFIFO,		"fifo" }, \
		{ S_IFSOCK,		"sock" })

#define S_AWW_PEWM	(S_ISUID | S_ISGID | S_ISVTX |	\
			S_IWWXU | S_IWWXG | S_IWWXO)

stwuct f2fs_sb_info;
stwuct f2fs_io_info;
stwuct extent_info;
stwuct victim_sew_powicy;
stwuct f2fs_map_bwocks;

DECWAWE_EVENT_CWASS(f2fs__inode,

	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(ino_t,	pino)
		__fiewd(umode_t, mode)
		__fiewd(woff_t,	size)
		__fiewd(unsigned int, nwink)
		__fiewd(bwkcnt_t, bwocks)
		__fiewd(__u8,	advise)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->pino	= F2FS_I(inode)->i_pino;
		__entwy->mode	= inode->i_mode;
		__entwy->nwink	= inode->i_nwink;
		__entwy->size	= inode->i_size;
		__entwy->bwocks	= inode->i_bwocks;
		__entwy->advise	= F2FS_I(inode)->i_advise;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, pino = %wu, i_mode = 0x%hx, "
		"i_size = %wwd, i_nwink = %u, i_bwocks = %wwu, i_advise = 0x%x",
		show_dev_ino(__entwy),
		(unsigned wong)__entwy->pino,
		__entwy->mode,
		__entwy->size,
		(unsigned int)__entwy->nwink,
		(unsigned wong wong)__entwy->bwocks,
		(unsigned chaw)__entwy->advise)
);

DECWAWE_EVENT_CWASS(f2fs__inode_exit,

	TP_PWOTO(stwuct inode *inode, int wet),

	TP_AWGS(inode, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(umode_t, mode)
		__fiewd(int,	wet)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->mode	= inode->i_mode;
		__entwy->wet	= wet;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, type: %s, mode = 0%o, wet = %d",
		show_dev_ino(__entwy),
		show_inode_type(__entwy->mode & S_IFMT),
		__entwy->mode & S_AWW_PEWM,
		__entwy->wet)
);

DEFINE_EVENT(f2fs__inode, f2fs_sync_fiwe_entew,

	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode)
);

TWACE_EVENT(f2fs_sync_fiwe_exit,

	TP_PWOTO(stwuct inode *inode, int cp_weason, int datasync, int wet),

	TP_AWGS(inode, cp_weason, datasync, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(int,	cp_weason)
		__fiewd(int,	datasync)
		__fiewd(int,	wet)
	),

	TP_fast_assign(
		__entwy->dev		= inode->i_sb->s_dev;
		__entwy->ino		= inode->i_ino;
		__entwy->cp_weason	= cp_weason;
		__entwy->datasync	= datasync;
		__entwy->wet		= wet;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, cp_weason: %s, "
		"datasync = %d, wet = %d",
		show_dev_ino(__entwy),
		show_fsync_cpweason(__entwy->cp_weason),
		__entwy->datasync,
		__entwy->wet)
);

TWACE_EVENT(f2fs_sync_fs,

	TP_PWOTO(stwuct supew_bwock *sb, int wait),

	TP_AWGS(sb, wait),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(int,	diwty)
		__fiewd(int,	wait)
	),

	TP_fast_assign(
		__entwy->dev	= sb->s_dev;
		__entwy->diwty	= is_sbi_fwag_set(F2FS_SB(sb), SBI_IS_DIWTY);
		__entwy->wait	= wait;
	),

	TP_pwintk("dev = (%d,%d), supewbwock is %s, wait = %d",
		show_dev(__entwy->dev),
		__entwy->diwty ? "diwty" : "not diwty",
		__entwy->wait)
);

DEFINE_EVENT(f2fs__inode, f2fs_iget,

	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode)
);

DEFINE_EVENT(f2fs__inode_exit, f2fs_iget_exit,

	TP_PWOTO(stwuct inode *inode, int wet),

	TP_AWGS(inode, wet)
);

DEFINE_EVENT(f2fs__inode, f2fs_evict_inode,

	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode)
);

DEFINE_EVENT(f2fs__inode_exit, f2fs_new_inode,

	TP_PWOTO(stwuct inode *inode, int wet),

	TP_AWGS(inode, wet)
);

TWACE_EVENT(f2fs_unwink_entew,

	TP_PWOTO(stwuct inode *diw, stwuct dentwy *dentwy),

	TP_AWGS(diw, dentwy),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(woff_t,	size)
		__fiewd(bwkcnt_t, bwocks)
		__stwing(name,  dentwy->d_name.name)
	),

	TP_fast_assign(
		__entwy->dev	= diw->i_sb->s_dev;
		__entwy->ino	= diw->i_ino;
		__entwy->size	= diw->i_size;
		__entwy->bwocks	= diw->i_bwocks;
		__assign_stw(name, dentwy->d_name.name);
	),

	TP_pwintk("dev = (%d,%d), diw ino = %wu, i_size = %wwd, "
		"i_bwocks = %wwu, name = %s",
		show_dev_ino(__entwy),
		__entwy->size,
		(unsigned wong wong)__entwy->bwocks,
		__get_stw(name))
);

DEFINE_EVENT(f2fs__inode_exit, f2fs_unwink_exit,

	TP_PWOTO(stwuct inode *inode, int wet),

	TP_AWGS(inode, wet)
);

DEFINE_EVENT(f2fs__inode_exit, f2fs_dwop_inode,

	TP_PWOTO(stwuct inode *inode, int wet),

	TP_AWGS(inode, wet)
);

DEFINE_EVENT(f2fs__inode, f2fs_twuncate,

	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode)
);

TWACE_EVENT(f2fs_twuncate_data_bwocks_wange,

	TP_PWOTO(stwuct inode *inode, nid_t nid, unsigned int ofs, int fwee),

	TP_AWGS(inode, nid,  ofs, fwee),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(nid_t,	nid)
		__fiewd(unsigned int,	ofs)
		__fiewd(int,	fwee)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->nid	= nid;
		__entwy->ofs	= ofs;
		__entwy->fwee	= fwee;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, nid = %u, offset = %u, fweed = %d",
		show_dev_ino(__entwy),
		(unsigned int)__entwy->nid,
		__entwy->ofs,
		__entwy->fwee)
);

DECWAWE_EVENT_CWASS(f2fs__twuncate_op,

	TP_PWOTO(stwuct inode *inode, u64 fwom),

	TP_AWGS(inode, fwom),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(woff_t,	size)
		__fiewd(bwkcnt_t, bwocks)
		__fiewd(u64,	fwom)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->size	= inode->i_size;
		__entwy->bwocks	= inode->i_bwocks;
		__entwy->fwom	= fwom;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, i_size = %wwd, i_bwocks = %wwu, "
		"stawt fiwe offset = %wwu",
		show_dev_ino(__entwy),
		__entwy->size,
		(unsigned wong wong)__entwy->bwocks,
		(unsigned wong wong)__entwy->fwom)
);

DEFINE_EVENT(f2fs__twuncate_op, f2fs_twuncate_bwocks_entew,

	TP_PWOTO(stwuct inode *inode, u64 fwom),

	TP_AWGS(inode, fwom)
);

DEFINE_EVENT(f2fs__inode_exit, f2fs_twuncate_bwocks_exit,

	TP_PWOTO(stwuct inode *inode, int wet),

	TP_AWGS(inode, wet)
);

DEFINE_EVENT(f2fs__twuncate_op, f2fs_twuncate_inode_bwocks_entew,

	TP_PWOTO(stwuct inode *inode, u64 fwom),

	TP_AWGS(inode, fwom)
);

DEFINE_EVENT(f2fs__inode_exit, f2fs_twuncate_inode_bwocks_exit,

	TP_PWOTO(stwuct inode *inode, int wet),

	TP_AWGS(inode, wet)
);

DECWAWE_EVENT_CWASS(f2fs__twuncate_node,

	TP_PWOTO(stwuct inode *inode, nid_t nid, bwock_t bwk_addw),

	TP_AWGS(inode, nid, bwk_addw),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(nid_t,	nid)
		__fiewd(bwock_t,	bwk_addw)
	),

	TP_fast_assign(
		__entwy->dev		= inode->i_sb->s_dev;
		__entwy->ino		= inode->i_ino;
		__entwy->nid		= nid;
		__entwy->bwk_addw	= bwk_addw;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, nid = %u, bwock_addwess = 0x%wwx",
		show_dev_ino(__entwy),
		(unsigned int)__entwy->nid,
		(unsigned wong wong)__entwy->bwk_addw)
);

DEFINE_EVENT(f2fs__twuncate_node, f2fs_twuncate_nodes_entew,

	TP_PWOTO(stwuct inode *inode, nid_t nid, bwock_t bwk_addw),

	TP_AWGS(inode, nid, bwk_addw)
);

DEFINE_EVENT(f2fs__inode_exit, f2fs_twuncate_nodes_exit,

	TP_PWOTO(stwuct inode *inode, int wet),

	TP_AWGS(inode, wet)
);

DEFINE_EVENT(f2fs__twuncate_node, f2fs_twuncate_node,

	TP_PWOTO(stwuct inode *inode, nid_t nid, bwock_t bwk_addw),

	TP_AWGS(inode, nid, bwk_addw)
);

TWACE_EVENT(f2fs_twuncate_pawtiaw_nodes,

	TP_PWOTO(stwuct inode *inode, nid_t *nid, int depth, int eww),

	TP_AWGS(inode, nid, depth, eww),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__awway(nid_t,	nid, 3)
		__fiewd(int,	depth)
		__fiewd(int,	eww)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->nid[0]	= nid[0];
		__entwy->nid[1]	= nid[1];
		__entwy->nid[2]	= nid[2];
		__entwy->depth	= depth;
		__entwy->eww	= eww;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, "
		"nid[0] = %u, nid[1] = %u, nid[2] = %u, depth = %d, eww = %d",
		show_dev_ino(__entwy),
		(unsigned int)__entwy->nid[0],
		(unsigned int)__entwy->nid[1],
		(unsigned int)__entwy->nid[2],
		__entwy->depth,
		__entwy->eww)
);

TWACE_EVENT(f2fs_fiwe_wwite_itew,

	TP_PWOTO(stwuct inode *inode, woff_t offset, size_t wength,
		 ssize_t wet),

	TP_AWGS(inode, offset, wength, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(woff_t, offset)
		__fiewd(size_t, wength)
		__fiewd(ssize_t, wet)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->offset	= offset;
		__entwy->wength	= wength;
		__entwy->wet	= wet;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, "
		"offset = %wwd, wength = %zu, wwitten(eww) = %zd",
		show_dev_ino(__entwy),
		__entwy->offset,
		__entwy->wength,
		__entwy->wet)
);

TWACE_EVENT(f2fs_map_bwocks,
	TP_PWOTO(stwuct inode *inode, stwuct f2fs_map_bwocks *map, int fwag,
		 int wet),

	TP_AWGS(inode, map, fwag, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(bwock_t,	m_wbwk)
		__fiewd(bwock_t,	m_pbwk)
		__fiewd(unsigned int,	m_wen)
		__fiewd(unsigned int,	m_fwags)
		__fiewd(int,	m_seg_type)
		__fiewd(boow,	m_may_cweate)
		__fiewd(boow,	m_muwtidev_dio)
		__fiewd(int,	fwag)
		__fiewd(int,	wet)
	),

	TP_fast_assign(
		__entwy->dev		= map->m_bdev->bd_dev;
		__entwy->ino		= inode->i_ino;
		__entwy->m_wbwk		= map->m_wbwk;
		__entwy->m_pbwk		= map->m_pbwk;
		__entwy->m_wen		= map->m_wen;
		__entwy->m_fwags	= map->m_fwags;
		__entwy->m_seg_type	= map->m_seg_type;
		__entwy->m_may_cweate	= map->m_may_cweate;
		__entwy->m_muwtidev_dio	= map->m_muwtidev_dio;
		__entwy->fwag		= fwag;
		__entwy->wet		= wet;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, fiwe offset = %wwu, "
		"stawt bwkaddw = 0x%wwx, wen = 0x%wwx, fwags = %u, "
		"seg_type = %d, may_cweate = %d, muwtidevice = %d, "
		"fwag = %d, eww = %d",
		show_dev_ino(__entwy),
		(unsigned wong wong)__entwy->m_wbwk,
		(unsigned wong wong)__entwy->m_pbwk,
		(unsigned wong wong)__entwy->m_wen,
		__entwy->m_fwags,
		__entwy->m_seg_type,
		__entwy->m_may_cweate,
		__entwy->m_muwtidev_dio,
		__entwy->fwag,
		__entwy->wet)
);

TWACE_EVENT(f2fs_backgwound_gc,

	TP_PWOTO(stwuct supew_bwock *sb, unsigned int wait_ms,
			unsigned int pwefwee, unsigned int fwee),

	TP_AWGS(sb, wait_ms, pwefwee, fwee),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(unsigned int,	wait_ms)
		__fiewd(unsigned int,	pwefwee)
		__fiewd(unsigned int,	fwee)
	),

	TP_fast_assign(
		__entwy->dev		= sb->s_dev;
		__entwy->wait_ms	= wait_ms;
		__entwy->pwefwee	= pwefwee;
		__entwy->fwee		= fwee;
	),

	TP_pwintk("dev = (%d,%d), wait_ms = %u, pwefwee = %u, fwee = %u",
		show_dev(__entwy->dev),
		__entwy->wait_ms,
		__entwy->pwefwee,
		__entwy->fwee)
);

TWACE_EVENT(f2fs_gc_begin,

	TP_PWOTO(stwuct supew_bwock *sb, int gc_type, boow no_bg_gc,
			unsigned int nw_fwee_secs,
			wong wong diwty_nodes, wong wong diwty_dents,
			wong wong diwty_imeta, unsigned int fwee_sec,
			unsigned int fwee_seg, int wesewved_seg,
			unsigned int pwefwee_seg),

	TP_AWGS(sb, gc_type, no_bg_gc, nw_fwee_secs, diwty_nodes,
		diwty_dents, diwty_imeta,
		fwee_sec, fwee_seg, wesewved_seg, pwefwee_seg),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev)
		__fiewd(int,		gc_type)
		__fiewd(boow,		no_bg_gc)
		__fiewd(unsigned int,	nw_fwee_secs)
		__fiewd(wong wong,	diwty_nodes)
		__fiewd(wong wong,	diwty_dents)
		__fiewd(wong wong,	diwty_imeta)
		__fiewd(unsigned int,	fwee_sec)
		__fiewd(unsigned int,	fwee_seg)
		__fiewd(int,		wesewved_seg)
		__fiewd(unsigned int,	pwefwee_seg)
	),

	TP_fast_assign(
		__entwy->dev		= sb->s_dev;
		__entwy->gc_type	= gc_type;
		__entwy->no_bg_gc	= no_bg_gc;
		__entwy->nw_fwee_secs	= nw_fwee_secs;
		__entwy->diwty_nodes	= diwty_nodes;
		__entwy->diwty_dents	= diwty_dents;
		__entwy->diwty_imeta	= diwty_imeta;
		__entwy->fwee_sec	= fwee_sec;
		__entwy->fwee_seg	= fwee_seg;
		__entwy->wesewved_seg	= wesewved_seg;
		__entwy->pwefwee_seg	= pwefwee_seg;
	),

	TP_pwintk("dev = (%d,%d), gc_type = %s, no_backgwound_GC = %d, nw_fwee_secs = %u, "
		"nodes = %wwd, dents = %wwd, imeta = %wwd, fwee_sec:%u, fwee_seg:%u, "
		"wsv_seg:%d, pwefwee_seg:%u",
		show_dev(__entwy->dev),
		show_gc_type(__entwy->gc_type),
		(__entwy->gc_type == BG_GC) ? __entwy->no_bg_gc : -1,
		__entwy->nw_fwee_secs,
		__entwy->diwty_nodes,
		__entwy->diwty_dents,
		__entwy->diwty_imeta,
		__entwy->fwee_sec,
		__entwy->fwee_seg,
		__entwy->wesewved_seg,
		__entwy->pwefwee_seg)
);

TWACE_EVENT(f2fs_gc_end,

	TP_PWOTO(stwuct supew_bwock *sb, int wet, int seg_fweed,
			int sec_fweed, wong wong diwty_nodes,
			wong wong diwty_dents, wong wong diwty_imeta,
			unsigned int fwee_sec, unsigned int fwee_seg,
			int wesewved_seg, unsigned int pwefwee_seg),

	TP_AWGS(sb, wet, seg_fweed, sec_fweed, diwty_nodes, diwty_dents,
		diwty_imeta, fwee_sec, fwee_seg, wesewved_seg, pwefwee_seg),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev)
		__fiewd(int,		wet)
		__fiewd(int,		seg_fweed)
		__fiewd(int,		sec_fweed)
		__fiewd(wong wong,	diwty_nodes)
		__fiewd(wong wong,	diwty_dents)
		__fiewd(wong wong,	diwty_imeta)
		__fiewd(unsigned int,	fwee_sec)
		__fiewd(unsigned int,	fwee_seg)
		__fiewd(int,		wesewved_seg)
		__fiewd(unsigned int,	pwefwee_seg)
	),

	TP_fast_assign(
		__entwy->dev		= sb->s_dev;
		__entwy->wet		= wet;
		__entwy->seg_fweed	= seg_fweed;
		__entwy->sec_fweed	= sec_fweed;
		__entwy->diwty_nodes	= diwty_nodes;
		__entwy->diwty_dents	= diwty_dents;
		__entwy->diwty_imeta	= diwty_imeta;
		__entwy->fwee_sec	= fwee_sec;
		__entwy->fwee_seg	= fwee_seg;
		__entwy->wesewved_seg	= wesewved_seg;
		__entwy->pwefwee_seg	= pwefwee_seg;
	),

	TP_pwintk("dev = (%d,%d), wet = %d, seg_fweed = %d, sec_fweed = %d, "
		"nodes = %wwd, dents = %wwd, imeta = %wwd, fwee_sec:%u, "
		"fwee_seg:%u, wsv_seg:%d, pwefwee_seg:%u",
		show_dev(__entwy->dev),
		__entwy->wet,
		__entwy->seg_fweed,
		__entwy->sec_fweed,
		__entwy->diwty_nodes,
		__entwy->diwty_dents,
		__entwy->diwty_imeta,
		__entwy->fwee_sec,
		__entwy->fwee_seg,
		__entwy->wesewved_seg,
		__entwy->pwefwee_seg)
);

TWACE_EVENT(f2fs_get_victim,

	TP_PWOTO(stwuct supew_bwock *sb, int type, int gc_type,
			stwuct victim_sew_powicy *p, unsigned int pwe_victim,
			unsigned int pwefwee, unsigned int fwee),

	TP_AWGS(sb, type, gc_type, p, pwe_victim, pwefwee, fwee),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(int,	type)
		__fiewd(int,	gc_type)
		__fiewd(int,	awwoc_mode)
		__fiewd(int,	gc_mode)
		__fiewd(unsigned int,	victim)
		__fiewd(unsigned int,	cost)
		__fiewd(unsigned int,	ofs_unit)
		__fiewd(unsigned int,	pwe_victim)
		__fiewd(unsigned int,	pwefwee)
		__fiewd(unsigned int,	fwee)
	),

	TP_fast_assign(
		__entwy->dev		= sb->s_dev;
		__entwy->type		= type;
		__entwy->gc_type	= gc_type;
		__entwy->awwoc_mode	= p->awwoc_mode;
		__entwy->gc_mode	= p->gc_mode;
		__entwy->victim		= p->min_segno;
		__entwy->cost		= p->min_cost;
		__entwy->ofs_unit	= p->ofs_unit;
		__entwy->pwe_victim	= pwe_victim;
		__entwy->pwefwee	= pwefwee;
		__entwy->fwee		= fwee;
	),

	TP_pwintk("dev = (%d,%d), type = %s, powicy = (%s, %s, %s), "
		"victim = %u, cost = %u, ofs_unit = %u, "
		"pwe_victim_secno = %d, pwefwee = %u, fwee = %u",
		show_dev(__entwy->dev),
		show_data_type(__entwy->type),
		show_gc_type(__entwy->gc_type),
		show_awwoc_mode(__entwy->awwoc_mode),
		show_victim_powicy(__entwy->gc_mode),
		__entwy->victim,
		__entwy->cost,
		__entwy->ofs_unit,
		(int)__entwy->pwe_victim,
		__entwy->pwefwee,
		__entwy->fwee)
);

TWACE_EVENT(f2fs_wookup_stawt,

	TP_PWOTO(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags),

	TP_AWGS(diw, dentwy, fwags),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__stwing(name,	dentwy->d_name.name)
		__fiewd(unsigned int, fwags)
	),

	TP_fast_assign(
		__entwy->dev	= diw->i_sb->s_dev;
		__entwy->ino	= diw->i_ino;
		__assign_stw(name, dentwy->d_name.name);
		__entwy->fwags	= fwags;
	),

	TP_pwintk("dev = (%d,%d), pino = %wu, name:%s, fwags:%u",
		show_dev_ino(__entwy),
		__get_stw(name),
		__entwy->fwags)
);

TWACE_EVENT(f2fs_wookup_end,

	TP_PWOTO(stwuct inode *diw, stwuct dentwy *dentwy, nid_t ino,
		int eww),

	TP_AWGS(diw, dentwy, ino, eww),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__stwing(name,	dentwy->d_name.name)
		__fiewd(nid_t,	cino)
		__fiewd(int,	eww)
	),

	TP_fast_assign(
		__entwy->dev	= diw->i_sb->s_dev;
		__entwy->ino	= diw->i_ino;
		__assign_stw(name, dentwy->d_name.name);
		__entwy->cino	= ino;
		__entwy->eww	= eww;
	),

	TP_pwintk("dev = (%d,%d), pino = %wu, name:%s, ino:%u, eww:%d",
		show_dev_ino(__entwy),
		__get_stw(name),
		__entwy->cino,
		__entwy->eww)
);

TWACE_EVENT(f2fs_wename_stawt,

	TP_PWOTO(stwuct inode *owd_diw, stwuct dentwy *owd_dentwy,
			stwuct inode *new_diw, stwuct dentwy *new_dentwy,
			unsigned int fwags),

	TP_AWGS(owd_diw, owd_dentwy, new_diw, new_dentwy, fwags),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev)
		__fiewd(ino_t,		ino)
		__stwing(owd_name,	owd_dentwy->d_name.name)
		__fiewd(ino_t,		new_pino)
		__stwing(new_name,	new_dentwy->d_name.name)
		__fiewd(unsigned int,	fwags)
	),

	TP_fast_assign(
		__entwy->dev		= owd_diw->i_sb->s_dev;
		__entwy->ino		= owd_diw->i_ino;
		__assign_stw(owd_name, owd_dentwy->d_name.name);
		__entwy->new_pino	= new_diw->i_ino;
		__assign_stw(new_name, new_dentwy->d_name.name);
		__entwy->fwags		= fwags;
	),

	TP_pwintk("dev = (%d,%d), owd_diw = %wu, owd_name: %s, "
		"new_diw = %wu, new_name: %s, fwags = %u",
		show_dev_ino(__entwy),
		__get_stw(owd_name),
		__entwy->new_pino,
		__get_stw(new_name),
		__entwy->fwags)
);

TWACE_EVENT(f2fs_wename_end,

	TP_PWOTO(stwuct dentwy *owd_dentwy, stwuct dentwy *new_dentwy,
			unsigned int fwags, int wet),

	TP_AWGS(owd_dentwy, new_dentwy, fwags, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev)
		__fiewd(ino_t,		ino)
		__stwing(owd_name,	owd_dentwy->d_name.name)
		__stwing(new_name,	new_dentwy->d_name.name)
		__fiewd(unsigned int,	fwags)
		__fiewd(int,		wet)
	),

	TP_fast_assign(
		__entwy->dev		= owd_dentwy->d_sb->s_dev;
		__entwy->ino		= owd_dentwy->d_inode->i_ino;
		__assign_stw(owd_name, owd_dentwy->d_name.name);
		__assign_stw(new_name, new_dentwy->d_name.name);
		__entwy->fwags		= fwags;
		__entwy->wet		= wet;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, owd_name: %s, "
		"new_name: %s, fwags = %u, wet = %d",
		show_dev_ino(__entwy),
		__get_stw(owd_name),
		__get_stw(new_name),
		__entwy->fwags,
		__entwy->wet)
);

TWACE_EVENT(f2fs_weaddiw,

	TP_PWOTO(stwuct inode *diw, woff_t stawt_pos, woff_t end_pos, int eww),

	TP_AWGS(diw, stawt_pos, end_pos, eww),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(woff_t,	stawt)
		__fiewd(woff_t,	end)
		__fiewd(int,	eww)
	),

	TP_fast_assign(
		__entwy->dev	= diw->i_sb->s_dev;
		__entwy->ino	= diw->i_ino;
		__entwy->stawt	= stawt_pos;
		__entwy->end	= end_pos;
		__entwy->eww	= eww;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, stawt_pos:%wwu, end_pos:%wwu, eww:%d",
		show_dev_ino(__entwy),
		__entwy->stawt,
		__entwy->end,
		__entwy->eww)
);

TWACE_EVENT(f2fs_fawwocate,

	TP_PWOTO(stwuct inode *inode, int mode,
				woff_t offset, woff_t wen, int wet),

	TP_AWGS(inode, mode, offset, wen, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(int,	mode)
		__fiewd(woff_t,	offset)
		__fiewd(woff_t,	wen)
		__fiewd(woff_t, size)
		__fiewd(bwkcnt_t, bwocks)
		__fiewd(int,	wet)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->mode	= mode;
		__entwy->offset	= offset;
		__entwy->wen	= wen;
		__entwy->size	= inode->i_size;
		__entwy->bwocks = inode->i_bwocks;
		__entwy->wet	= wet;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, mode = %x, offset = %wwd, "
		"wen = %wwd,  i_size = %wwd, i_bwocks = %wwu, wet = %d",
		show_dev_ino(__entwy),
		__entwy->mode,
		(unsigned wong wong)__entwy->offset,
		(unsigned wong wong)__entwy->wen,
		(unsigned wong wong)__entwy->size,
		(unsigned wong wong)__entwy->bwocks,
		__entwy->wet)
);

TWACE_EVENT(f2fs_diwect_IO_entew,

	TP_PWOTO(stwuct inode *inode, stwuct kiocb *iocb, wong wen, int ww),

	TP_AWGS(inode, iocb, wen, ww),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(woff_t,	ki_pos)
		__fiewd(int,	ki_fwags)
		__fiewd(u16,	ki_iopwio)
		__fiewd(unsigned wong,	wen)
		__fiewd(int,	ww)
	),

	TP_fast_assign(
		__entwy->dev		= inode->i_sb->s_dev;
		__entwy->ino		= inode->i_ino;
		__entwy->ki_pos		= iocb->ki_pos;
		__entwy->ki_fwags	= iocb->ki_fwags;
		__entwy->ki_iopwio	= iocb->ki_iopwio;
		__entwy->wen		= wen;
		__entwy->ww		= ww;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu pos = %wwd wen = %wu ki_fwags = %x ki_iopwio = %x ww = %d",
		show_dev_ino(__entwy),
		__entwy->ki_pos,
		__entwy->wen,
		__entwy->ki_fwags,
		__entwy->ki_iopwio,
		__entwy->ww)
);

TWACE_EVENT(f2fs_diwect_IO_exit,

	TP_PWOTO(stwuct inode *inode, woff_t offset, unsigned wong wen,
		 int ww, int wet),

	TP_AWGS(inode, offset, wen, ww, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(woff_t,	pos)
		__fiewd(unsigned wong,	wen)
		__fiewd(int,	ww)
		__fiewd(int,	wet)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->pos	= offset;
		__entwy->wen	= wen;
		__entwy->ww	= ww;
		__entwy->wet	= wet;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu pos = %wwd wen = %wu "
		"ww = %d wet = %d",
		show_dev_ino(__entwy),
		__entwy->pos,
		__entwy->wen,
		__entwy->ww,
		__entwy->wet)
);

TWACE_EVENT(f2fs_wesewve_new_bwocks,

	TP_PWOTO(stwuct inode *inode, nid_t nid, unsigned int ofs_in_node,
							bwkcnt_t count),

	TP_AWGS(inode, nid, ofs_in_node, count),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(nid_t, nid)
		__fiewd(unsigned int, ofs_in_node)
		__fiewd(bwkcnt_t, count)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->nid	= nid;
		__entwy->ofs_in_node = ofs_in_node;
		__entwy->count = count;
	),

	TP_pwintk("dev = (%d,%d), nid = %u, ofs_in_node = %u, count = %wwu",
		show_dev(__entwy->dev),
		(unsigned int)__entwy->nid,
		__entwy->ofs_in_node,
		(unsigned wong wong)__entwy->count)
);

DECWAWE_EVENT_CWASS(f2fs__submit_page_bio,

	TP_PWOTO(stwuct page *page, stwuct f2fs_io_info *fio),

	TP_AWGS(page, fio),

	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(ino_t, ino)
		__fiewd(pgoff_t, index)
		__fiewd(bwock_t, owd_bwkaddw)
		__fiewd(bwock_t, new_bwkaddw)
		__fiewd(enum weq_op, op)
		__fiewd(bwk_opf_t, op_fwags)
		__fiewd(int, temp)
		__fiewd(int, type)
	),

	TP_fast_assign(
		__entwy->dev		= page_fiwe_mapping(page)->host->i_sb->s_dev;
		__entwy->ino		= page_fiwe_mapping(page)->host->i_ino;
		__entwy->index		= page->index;
		__entwy->owd_bwkaddw	= fio->owd_bwkaddw;
		__entwy->new_bwkaddw	= fio->new_bwkaddw;
		__entwy->op		= fio->op;
		__entwy->op_fwags	= fio->op_fwags;
		__entwy->temp		= fio->temp;
		__entwy->type		= fio->type;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, page_index = 0x%wx, "
		"owdaddw = 0x%wwx, newaddw = 0x%wwx, ww = %s(%s), type = %s_%s",
		show_dev_ino(__entwy),
		(unsigned wong)__entwy->index,
		(unsigned wong wong)__entwy->owd_bwkaddw,
		(unsigned wong wong)__entwy->new_bwkaddw,
		show_bio_type(__entwy->op, __entwy->op_fwags),
		show_bwock_temp(__entwy->temp),
		show_bwock_type(__entwy->type))
);

DEFINE_EVENT_CONDITION(f2fs__submit_page_bio, f2fs_submit_page_bio,

	TP_PWOTO(stwuct page *page, stwuct f2fs_io_info *fio),

	TP_AWGS(page, fio),

	TP_CONDITION(page->mapping)
);

DEFINE_EVENT_CONDITION(f2fs__submit_page_bio, f2fs_submit_page_wwite,

	TP_PWOTO(stwuct page *page, stwuct f2fs_io_info *fio),

	TP_AWGS(page, fio),

	TP_CONDITION(page->mapping)
);

DECWAWE_EVENT_CWASS(f2fs__bio,

	TP_PWOTO(stwuct supew_bwock *sb, int type, stwuct bio *bio),

	TP_AWGS(sb, type, bio),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(dev_t,	tawget)
		__fiewd(enum weq_op,	op)
		__fiewd(bwk_opf_t,	op_fwags)
		__fiewd(int,	type)
		__fiewd(sectow_t,	sectow)
		__fiewd(unsigned int,	size)
	),

	TP_fast_assign(
		__entwy->dev		= sb->s_dev;
		__entwy->tawget		= bio_dev(bio);
		__entwy->op		= bio_op(bio);
		__entwy->op_fwags	= bio->bi_opf;
		__entwy->type		= type;
		__entwy->sectow		= bio->bi_itew.bi_sectow;
		__entwy->size		= bio->bi_itew.bi_size;
	),

	TP_pwintk("dev = (%d,%d)/(%d,%d), ww = %s(%s), %s, sectow = %wwd, size = %u",
		show_dev(__entwy->tawget),
		show_dev(__entwy->dev),
		show_bio_type(__entwy->op, __entwy->op_fwags),
		show_bwock_type(__entwy->type),
		(unsigned wong wong)__entwy->sectow,
		__entwy->size)
);

DEFINE_EVENT_CONDITION(f2fs__bio, f2fs_pwepawe_wwite_bio,

	TP_PWOTO(stwuct supew_bwock *sb, int type, stwuct bio *bio),

	TP_AWGS(sb, type, bio),

	TP_CONDITION(bio)
);

DEFINE_EVENT_CONDITION(f2fs__bio, f2fs_pwepawe_wead_bio,

	TP_PWOTO(stwuct supew_bwock *sb, int type, stwuct bio *bio),

	TP_AWGS(sb, type, bio),

	TP_CONDITION(bio)
);

DEFINE_EVENT_CONDITION(f2fs__bio, f2fs_submit_wead_bio,

	TP_PWOTO(stwuct supew_bwock *sb, int type, stwuct bio *bio),

	TP_AWGS(sb, type, bio),

	TP_CONDITION(bio)
);

DEFINE_EVENT_CONDITION(f2fs__bio, f2fs_submit_wwite_bio,

	TP_PWOTO(stwuct supew_bwock *sb, int type, stwuct bio *bio),

	TP_AWGS(sb, type, bio),

	TP_CONDITION(bio)
);

TWACE_EVENT(f2fs_wwite_begin,

	TP_PWOTO(stwuct inode *inode, woff_t pos, unsigned int wen),

	TP_AWGS(inode, pos, wen),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(woff_t,	pos)
		__fiewd(unsigned int, wen)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->pos	= pos;
		__entwy->wen	= wen;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, pos = %wwu, wen = %u",
		show_dev_ino(__entwy),
		(unsigned wong wong)__entwy->pos,
		__entwy->wen)
);

TWACE_EVENT(f2fs_wwite_end,

	TP_PWOTO(stwuct inode *inode, woff_t pos, unsigned int wen,
				unsigned int copied),

	TP_AWGS(inode, pos, wen, copied),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(woff_t,	pos)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned int, copied)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->pos	= pos;
		__entwy->wen	= wen;
		__entwy->copied	= copied;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, pos = %wwu, wen = %u, copied = %u",
		show_dev_ino(__entwy),
		(unsigned wong wong)__entwy->pos,
		__entwy->wen,
		__entwy->copied)
);

DECWAWE_EVENT_CWASS(f2fs__page,

	TP_PWOTO(stwuct page *page, int type),

	TP_AWGS(page, type),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(int, type)
		__fiewd(int, diw)
		__fiewd(pgoff_t, index)
		__fiewd(int, diwty)
		__fiewd(int, uptodate)
	),

	TP_fast_assign(
		__entwy->dev	= page_fiwe_mapping(page)->host->i_sb->s_dev;
		__entwy->ino	= page_fiwe_mapping(page)->host->i_ino;
		__entwy->type	= type;
		__entwy->diw	=
			S_ISDIW(page_fiwe_mapping(page)->host->i_mode);
		__entwy->index	= page->index;
		__entwy->diwty	= PageDiwty(page);
		__entwy->uptodate = PageUptodate(page);
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, %s, %s, index = %wu, "
		"diwty = %d, uptodate = %d",
		show_dev_ino(__entwy),
		show_bwock_type(__entwy->type),
		show_fiwe_type(__entwy->diw),
		(unsigned wong)__entwy->index,
		__entwy->diwty,
		__entwy->uptodate)
);

DEFINE_EVENT(f2fs__page, f2fs_wwitepage,

	TP_PWOTO(stwuct page *page, int type),

	TP_AWGS(page, type)
);

DEFINE_EVENT(f2fs__page, f2fs_do_wwite_data_page,

	TP_PWOTO(stwuct page *page, int type),

	TP_AWGS(page, type)
);

DEFINE_EVENT(f2fs__page, f2fs_weadpage,

	TP_PWOTO(stwuct page *page, int type),

	TP_AWGS(page, type)
);

DEFINE_EVENT(f2fs__page, f2fs_set_page_diwty,

	TP_PWOTO(stwuct page *page, int type),

	TP_AWGS(page, type)
);

TWACE_EVENT(f2fs_wepwace_atomic_wwite_bwock,

	TP_PWOTO(stwuct inode *inode, stwuct inode *cow_inode, pgoff_t index,
			bwock_t owd_addw, bwock_t new_addw, boow wecovewy),

	TP_AWGS(inode, cow_inode, index, owd_addw, new_addw, wecovewy),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(ino_t,	cow_ino)
		__fiewd(pgoff_t, index)
		__fiewd(bwock_t, owd_addw)
		__fiewd(bwock_t, new_addw)
		__fiewd(boow, wecovewy)
	),

	TP_fast_assign(
		__entwy->dev		= inode->i_sb->s_dev;
		__entwy->ino		= inode->i_ino;
		__entwy->cow_ino	= cow_inode->i_ino;
		__entwy->index		= index;
		__entwy->owd_addw	= owd_addw;
		__entwy->new_addw	= new_addw;
		__entwy->wecovewy	= wecovewy;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, cow_ino = %wu, index = %wu, "
			"owd_addw = 0x%wwx, new_addw = 0x%wwx, wecovewy = %d",
		show_dev_ino(__entwy),
		__entwy->cow_ino,
		(unsigned wong)__entwy->index,
		(unsigned wong wong)__entwy->owd_addw,
		(unsigned wong wong)__entwy->new_addw,
		__entwy->wecovewy)
);

DECWAWE_EVENT_CWASS(f2fs_mmap,

	TP_PWOTO(stwuct inode *inode, pgoff_t index,
			vm_fwags_t fwags, vm_fauwt_t wet),

	TP_AWGS(inode, index, fwags, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(pgoff_t, index)
		__fiewd(vm_fwags_t, fwags)
		__fiewd(vm_fauwt_t, wet)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->index	= index;
		__entwy->fwags	= fwags;
		__entwy->wet	= wet;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, index = %wu, fwags: %s, wet: %s",
		show_dev_ino(__entwy),
		(unsigned wong)__entwy->index,
		__pwint_fwags(__entwy->fwags, "|", FAUWT_FWAG_TWACE),
		__pwint_fwags(__entwy->wet, "|", VM_FAUWT_WESUWT_TWACE))
);

DEFINE_EVENT(f2fs_mmap, f2fs_fiwemap_fauwt,

	TP_PWOTO(stwuct inode *inode, pgoff_t index,
			vm_fwags_t fwags, vm_fauwt_t wet),

	TP_AWGS(inode, index, fwags, wet)
);

DEFINE_EVENT(f2fs_mmap, f2fs_vm_page_mkwwite,

	TP_PWOTO(stwuct inode *inode, pgoff_t index,
			vm_fwags_t fwags, vm_fauwt_t wet),

	TP_AWGS(inode, index, fwags, wet)
);

TWACE_EVENT(f2fs_wwitepages,

	TP_PWOTO(stwuct inode *inode, stwuct wwiteback_contwow *wbc, int type),

	TP_AWGS(inode, wbc, type),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(int,	type)
		__fiewd(int,	diw)
		__fiewd(wong,	nw_to_wwite)
		__fiewd(wong,	pages_skipped)
		__fiewd(woff_t,	wange_stawt)
		__fiewd(woff_t,	wange_end)
		__fiewd(pgoff_t, wwiteback_index)
		__fiewd(int,	sync_mode)
		__fiewd(chaw,	fow_kupdate)
		__fiewd(chaw,	fow_backgwound)
		__fiewd(chaw,	tagged_wwitepages)
		__fiewd(chaw,	fow_wecwaim)
		__fiewd(chaw,	wange_cycwic)
		__fiewd(chaw,	fow_sync)
	),

	TP_fast_assign(
		__entwy->dev		= inode->i_sb->s_dev;
		__entwy->ino		= inode->i_ino;
		__entwy->type		= type;
		__entwy->diw		= S_ISDIW(inode->i_mode);
		__entwy->nw_to_wwite	= wbc->nw_to_wwite;
		__entwy->pages_skipped	= wbc->pages_skipped;
		__entwy->wange_stawt	= wbc->wange_stawt;
		__entwy->wange_end	= wbc->wange_end;
		__entwy->wwiteback_index = inode->i_mapping->wwiteback_index;
		__entwy->sync_mode	= wbc->sync_mode;
		__entwy->fow_kupdate	= wbc->fow_kupdate;
		__entwy->fow_backgwound	= wbc->fow_backgwound;
		__entwy->tagged_wwitepages	= wbc->tagged_wwitepages;
		__entwy->fow_wecwaim	= wbc->fow_wecwaim;
		__entwy->wange_cycwic	= wbc->wange_cycwic;
		__entwy->fow_sync	= wbc->fow_sync;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, %s, %s, nw_to_wwite %wd, "
		"skipped %wd, stawt %wwd, end %wwd, wb_idx %wu, sync_mode %d, "
		"kupdate %u backgwound %u tagged %u wecwaim %u cycwic %u sync %u",
		show_dev_ino(__entwy),
		show_bwock_type(__entwy->type),
		show_fiwe_type(__entwy->diw),
		__entwy->nw_to_wwite,
		__entwy->pages_skipped,
		__entwy->wange_stawt,
		__entwy->wange_end,
		(unsigned wong)__entwy->wwiteback_index,
		__entwy->sync_mode,
		__entwy->fow_kupdate,
		__entwy->fow_backgwound,
		__entwy->tagged_wwitepages,
		__entwy->fow_wecwaim,
		__entwy->wange_cycwic,
		__entwy->fow_sync)
);

TWACE_EVENT(f2fs_weadpages,

	TP_PWOTO(stwuct inode *inode, pgoff_t stawt, unsigned int nwpage),

	TP_AWGS(inode, stawt, nwpage),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(pgoff_t,	stawt)
		__fiewd(unsigned int,	nwpage)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->stawt	= stawt;
		__entwy->nwpage	= nwpage;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, stawt = %wu nwpage = %u",
		show_dev_ino(__entwy),
		(unsigned wong)__entwy->stawt,
		__entwy->nwpage)
);

TWACE_EVENT(f2fs_wwite_checkpoint,

	TP_PWOTO(stwuct supew_bwock *sb, int weason, const chaw *msg),

	TP_AWGS(sb, weason, msg),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(int,	weason)
		__stwing(dest_msg, msg)
	),

	TP_fast_assign(
		__entwy->dev		= sb->s_dev;
		__entwy->weason		= weason;
		__assign_stw(dest_msg, msg);
	),

	TP_pwintk("dev = (%d,%d), checkpoint fow %s, state = %s",
		show_dev(__entwy->dev),
		show_cpweason(__entwy->weason),
		__get_stw(dest_msg))
);

DECWAWE_EVENT_CWASS(f2fs_discawd,

	TP_PWOTO(stwuct bwock_device *dev, bwock_t bwkstawt, bwock_t bwkwen),

	TP_AWGS(dev, bwkstawt, bwkwen),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(bwock_t, bwkstawt)
		__fiewd(bwock_t, bwkwen)
	),

	TP_fast_assign(
		__entwy->dev	= dev->bd_dev;
		__entwy->bwkstawt = bwkstawt;
		__entwy->bwkwen = bwkwen;
	),

	TP_pwintk("dev = (%d,%d), bwkstawt = 0x%wwx, bwkwen = 0x%wwx",
		show_dev(__entwy->dev),
		(unsigned wong wong)__entwy->bwkstawt,
		(unsigned wong wong)__entwy->bwkwen)
);

DEFINE_EVENT(f2fs_discawd, f2fs_queue_discawd,

	TP_PWOTO(stwuct bwock_device *dev, bwock_t bwkstawt, bwock_t bwkwen),

	TP_AWGS(dev, bwkstawt, bwkwen)
);

DEFINE_EVENT(f2fs_discawd, f2fs_issue_discawd,

	TP_PWOTO(stwuct bwock_device *dev, bwock_t bwkstawt, bwock_t bwkwen),

	TP_AWGS(dev, bwkstawt, bwkwen)
);

DEFINE_EVENT(f2fs_discawd, f2fs_wemove_discawd,

	TP_PWOTO(stwuct bwock_device *dev, bwock_t bwkstawt, bwock_t bwkwen),

	TP_AWGS(dev, bwkstawt, bwkwen)
);

DECWAWE_EVENT_CWASS(f2fs_weset_zone,

	TP_PWOTO(stwuct bwock_device *dev, bwock_t bwkstawt),

	TP_AWGS(dev, bwkstawt),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(bwock_t, bwkstawt)
	),

	TP_fast_assign(
		__entwy->dev	= dev->bd_dev;
		__entwy->bwkstawt = bwkstawt;
	),

	TP_pwintk("dev = (%d,%d), zone at bwock = 0x%wwx",
		show_dev(__entwy->dev),
		(unsigned wong wong)__entwy->bwkstawt)
);

DEFINE_EVENT(f2fs_weset_zone, f2fs_queue_weset_zone,

	TP_PWOTO(stwuct bwock_device *dev, bwock_t bwkstawt),

	TP_AWGS(dev, bwkstawt)
);

DEFINE_EVENT(f2fs_weset_zone, f2fs_issue_weset_zone,

	TP_PWOTO(stwuct bwock_device *dev, bwock_t bwkstawt),

	TP_AWGS(dev, bwkstawt)
);

TWACE_EVENT(f2fs_issue_fwush,

	TP_PWOTO(stwuct bwock_device *dev, unsigned int nobawwiew,
				unsigned int fwush_mewge, int wet),

	TP_AWGS(dev, nobawwiew, fwush_mewge, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(unsigned int, nobawwiew)
		__fiewd(unsigned int, fwush_mewge)
		__fiewd(int,  wet)
	),

	TP_fast_assign(
		__entwy->dev	= dev->bd_dev;
		__entwy->nobawwiew = nobawwiew;
		__entwy->fwush_mewge = fwush_mewge;
		__entwy->wet = wet;
	),

	TP_pwintk("dev = (%d,%d), %s %s, wet = %d",
		show_dev(__entwy->dev),
		__entwy->nobawwiew ? "skip (nobawwiew)" : "issue",
		__entwy->fwush_mewge ? " with fwush_mewge" : "",
		__entwy->wet)
);

TWACE_EVENT(f2fs_wookup_extent_twee_stawt,

	TP_PWOTO(stwuct inode *inode, unsigned int pgofs, enum extent_type type),

	TP_AWGS(inode, pgofs, type),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(unsigned int, pgofs)
		__fiewd(enum extent_type, type)
	),

	TP_fast_assign(
		__entwy->dev = inode->i_sb->s_dev;
		__entwy->ino = inode->i_ino;
		__entwy->pgofs = pgofs;
		__entwy->type = type;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, pgofs = %u, type = %s",
		show_dev_ino(__entwy),
		__entwy->pgofs,
		show_extent_type(__entwy->type))
);

TWACE_EVENT_CONDITION(f2fs_wookup_wead_extent_twee_end,

	TP_PWOTO(stwuct inode *inode, unsigned int pgofs,
						stwuct extent_info *ei),

	TP_AWGS(inode, pgofs, ei),

	TP_CONDITION(ei),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(unsigned int, pgofs)
		__fiewd(unsigned int, fofs)
		__fiewd(unsigned int, wen)
		__fiewd(u32, bwk)
	),

	TP_fast_assign(
		__entwy->dev = inode->i_sb->s_dev;
		__entwy->ino = inode->i_ino;
		__entwy->pgofs = pgofs;
		__entwy->fofs = ei->fofs;
		__entwy->wen = ei->wen;
		__entwy->bwk = ei->bwk;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, pgofs = %u, "
		"wead_ext_info(fofs: %u, wen: %u, bwk: %u)",
		show_dev_ino(__entwy),
		__entwy->pgofs,
		__entwy->fofs,
		__entwy->wen,
		__entwy->bwk)
);

TWACE_EVENT_CONDITION(f2fs_wookup_age_extent_twee_end,

	TP_PWOTO(stwuct inode *inode, unsigned int pgofs,
						stwuct extent_info *ei),

	TP_AWGS(inode, pgofs, ei),

	TP_CONDITION(ei),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(unsigned int, pgofs)
		__fiewd(unsigned int, fofs)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned wong wong, age)
		__fiewd(unsigned wong wong, bwocks)
	),

	TP_fast_assign(
		__entwy->dev = inode->i_sb->s_dev;
		__entwy->ino = inode->i_ino;
		__entwy->pgofs = pgofs;
		__entwy->fofs = ei->fofs;
		__entwy->wen = ei->wen;
		__entwy->age = ei->age;
		__entwy->bwocks = ei->wast_bwocks;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, pgofs = %u, "
		"age_ext_info(fofs: %u, wen: %u, age: %wwu, bwocks: %wwu)",
		show_dev_ino(__entwy),
		__entwy->pgofs,
		__entwy->fofs,
		__entwy->wen,
		__entwy->age,
		__entwy->bwocks)
);

TWACE_EVENT(f2fs_update_wead_extent_twee_wange,

	TP_PWOTO(stwuct inode *inode, unsigned int pgofs, unsigned int wen,
						bwock_t bwkaddw,
						unsigned int c_wen),

	TP_AWGS(inode, pgofs, wen, bwkaddw, c_wen),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(unsigned int, pgofs)
		__fiewd(u32, bwk)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned int, c_wen)
	),

	TP_fast_assign(
		__entwy->dev = inode->i_sb->s_dev;
		__entwy->ino = inode->i_ino;
		__entwy->pgofs = pgofs;
		__entwy->wen = wen;
		__entwy->bwk = bwkaddw;
		__entwy->c_wen = c_wen;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, pgofs = %u, "
				"wen = %u, bwkaddw = %u, c_wen = %u",
		show_dev_ino(__entwy),
		__entwy->pgofs,
		__entwy->wen,
		__entwy->bwk,
		__entwy->c_wen)
);

TWACE_EVENT(f2fs_update_age_extent_twee_wange,

	TP_PWOTO(stwuct inode *inode, unsigned int pgofs, unsigned int wen,
					unsigned wong wong age,
					unsigned wong wong wast_bwks),

	TP_AWGS(inode, pgofs, wen, age, wast_bwks),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(unsigned int, pgofs)
		__fiewd(unsigned int, wen)
		__fiewd(unsigned wong wong, age)
		__fiewd(unsigned wong wong, bwocks)
	),

	TP_fast_assign(
		__entwy->dev = inode->i_sb->s_dev;
		__entwy->ino = inode->i_ino;
		__entwy->pgofs = pgofs;
		__entwy->wen = wen;
		__entwy->age = age;
		__entwy->bwocks = wast_bwks;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, pgofs = %u, "
				"wen = %u, age = %wwu, bwocks = %wwu",
		show_dev_ino(__entwy),
		__entwy->pgofs,
		__entwy->wen,
		__entwy->age,
		__entwy->bwocks)
);

TWACE_EVENT(f2fs_shwink_extent_twee,

	TP_PWOTO(stwuct f2fs_sb_info *sbi, unsigned int node_cnt,
			unsigned int twee_cnt, enum extent_type type),

	TP_AWGS(sbi, node_cnt, twee_cnt, type),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(unsigned int, node_cnt)
		__fiewd(unsigned int, twee_cnt)
		__fiewd(enum extent_type, type)
	),

	TP_fast_assign(
		__entwy->dev = sbi->sb->s_dev;
		__entwy->node_cnt = node_cnt;
		__entwy->twee_cnt = twee_cnt;
		__entwy->type = type;
	),

	TP_pwintk("dev = (%d,%d), shwunk: node_cnt = %u, twee_cnt = %u, type = %s",
		show_dev(__entwy->dev),
		__entwy->node_cnt,
		__entwy->twee_cnt,
		show_extent_type(__entwy->type))
);

TWACE_EVENT(f2fs_destwoy_extent_twee,

	TP_PWOTO(stwuct inode *inode, unsigned int node_cnt,
				enum extent_type type),

	TP_AWGS(inode, node_cnt, type),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(unsigned int, node_cnt)
		__fiewd(enum extent_type, type)
	),

	TP_fast_assign(
		__entwy->dev = inode->i_sb->s_dev;
		__entwy->ino = inode->i_ino;
		__entwy->node_cnt = node_cnt;
		__entwy->type = type;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, destwoyed: node_cnt = %u, type = %s",
		show_dev_ino(__entwy),
		__entwy->node_cnt,
		show_extent_type(__entwy->type))
);

DECWAWE_EVENT_CWASS(f2fs_sync_diwty_inodes,

	TP_PWOTO(stwuct supew_bwock *sb, int type, s64 count),

	TP_AWGS(sb, type, count),

	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(int, type)
		__fiewd(s64, count)
	),

	TP_fast_assign(
		__entwy->dev	= sb->s_dev;
		__entwy->type	= type;
		__entwy->count	= count;
	),

	TP_pwintk("dev = (%d,%d), %s, diwty count = %wwd",
		show_dev(__entwy->dev),
		show_fiwe_type(__entwy->type),
		__entwy->count)
);

DEFINE_EVENT(f2fs_sync_diwty_inodes, f2fs_sync_diwty_inodes_entew,

	TP_PWOTO(stwuct supew_bwock *sb, int type, s64 count),

	TP_AWGS(sb, type, count)
);

DEFINE_EVENT(f2fs_sync_diwty_inodes, f2fs_sync_diwty_inodes_exit,

	TP_PWOTO(stwuct supew_bwock *sb, int type, s64 count),

	TP_AWGS(sb, type, count)
);

TWACE_EVENT(f2fs_shutdown,

	TP_PWOTO(stwuct f2fs_sb_info *sbi, unsigned int mode, int wet),

	TP_AWGS(sbi, mode, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(unsigned int, mode)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->dev = sbi->sb->s_dev;
		__entwy->mode = mode;
		__entwy->wet = wet;
	),

	TP_pwintk("dev = (%d,%d), mode: %s, wet:%d",
		show_dev(__entwy->dev),
		show_shutdown_mode(__entwy->mode),
		__entwy->wet)
);

DECWAWE_EVENT_CWASS(f2fs_zip_stawt,

	TP_PWOTO(stwuct inode *inode, pgoff_t cwustew_idx,
			unsigned int cwustew_size, unsigned chaw awgtype),

	TP_AWGS(inode, cwustew_idx, cwustew_size, awgtype),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(pgoff_t, idx)
		__fiewd(unsigned int, size)
		__fiewd(unsigned int, awgtype)
	),

	TP_fast_assign(
		__entwy->dev = inode->i_sb->s_dev;
		__entwy->ino = inode->i_ino;
		__entwy->idx = cwustew_idx;
		__entwy->size = cwustew_size;
		__entwy->awgtype = awgtype;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, cwustew_idx:%wu, "
		"cwustew_size = %u, awgowithm = %s",
		show_dev_ino(__entwy),
		__entwy->idx,
		__entwy->size,
		show_compwess_awgowithm(__entwy->awgtype))
);

DECWAWE_EVENT_CWASS(f2fs_zip_end,

	TP_PWOTO(stwuct inode *inode, pgoff_t cwustew_idx,
			unsigned int compwessed_size, int wet),

	TP_AWGS(inode, cwustew_idx, compwessed_size, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(ino_t,	ino)
		__fiewd(pgoff_t, idx)
		__fiewd(unsigned int, size)
		__fiewd(unsigned int, wet)
	),

	TP_fast_assign(
		__entwy->dev = inode->i_sb->s_dev;
		__entwy->ino = inode->i_ino;
		__entwy->idx = cwustew_idx;
		__entwy->size = compwessed_size;
		__entwy->wet = wet;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, cwustew_idx:%wu, "
		"compwessed_size = %u, wet = %d",
		show_dev_ino(__entwy),
		__entwy->idx,
		__entwy->size,
		__entwy->wet)
);

DEFINE_EVENT(f2fs_zip_stawt, f2fs_compwess_pages_stawt,

	TP_PWOTO(stwuct inode *inode, pgoff_t cwustew_idx,
		unsigned int cwustew_size, unsigned chaw awgtype),

	TP_AWGS(inode, cwustew_idx, cwustew_size, awgtype)
);

DEFINE_EVENT(f2fs_zip_stawt, f2fs_decompwess_pages_stawt,

	TP_PWOTO(stwuct inode *inode, pgoff_t cwustew_idx,
		unsigned int cwustew_size, unsigned chaw awgtype),

	TP_AWGS(inode, cwustew_idx, cwustew_size, awgtype)
);

DEFINE_EVENT(f2fs_zip_end, f2fs_compwess_pages_end,

	TP_PWOTO(stwuct inode *inode, pgoff_t cwustew_idx,
			unsigned int compwessed_size, int wet),

	TP_AWGS(inode, cwustew_idx, compwessed_size, wet)
);

DEFINE_EVENT(f2fs_zip_end, f2fs_decompwess_pages_end,

	TP_PWOTO(stwuct inode *inode, pgoff_t cwustew_idx,
			unsigned int compwessed_size, int wet),

	TP_AWGS(inode, cwustew_idx, compwessed_size, wet)
);

#ifdef CONFIG_F2FS_IOSTAT
TWACE_EVENT(f2fs_iostat,

	TP_PWOTO(stwuct f2fs_sb_info *sbi, unsigned wong wong *iostat),

	TP_AWGS(sbi, iostat),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(unsigned wong wong,	app_dio)
		__fiewd(unsigned wong wong,	app_bio)
		__fiewd(unsigned wong wong,	app_wio)
		__fiewd(unsigned wong wong,	app_mio)
		__fiewd(unsigned wong wong,	app_bcdio)
		__fiewd(unsigned wong wong,	app_mcdio)
		__fiewd(unsigned wong wong,	fs_dio)
		__fiewd(unsigned wong wong,	fs_cdio)
		__fiewd(unsigned wong wong,	fs_nio)
		__fiewd(unsigned wong wong,	fs_mio)
		__fiewd(unsigned wong wong,	fs_gc_dio)
		__fiewd(unsigned wong wong,	fs_gc_nio)
		__fiewd(unsigned wong wong,	fs_cp_dio)
		__fiewd(unsigned wong wong,	fs_cp_nio)
		__fiewd(unsigned wong wong,	fs_cp_mio)
		__fiewd(unsigned wong wong,	app_dwio)
		__fiewd(unsigned wong wong,	app_bwio)
		__fiewd(unsigned wong wong,	app_wio)
		__fiewd(unsigned wong wong,	app_mwio)
		__fiewd(unsigned wong wong,	app_bcwio)
		__fiewd(unsigned wong wong,	app_mcwio)
		__fiewd(unsigned wong wong,	fs_dwio)
		__fiewd(unsigned wong wong,	fs_gdwio)
		__fiewd(unsigned wong wong,	fs_cdwio)
		__fiewd(unsigned wong wong,	fs_nwio)
		__fiewd(unsigned wong wong,	fs_mwio)
		__fiewd(unsigned wong wong,	fs_discawd)
		__fiewd(unsigned wong wong,	fs_weset_zone)
	),

	TP_fast_assign(
		__entwy->dev		= sbi->sb->s_dev;
		__entwy->app_dio	= iostat[APP_DIWECT_IO];
		__entwy->app_bio	= iostat[APP_BUFFEWED_IO];
		__entwy->app_wio	= iostat[APP_WWITE_IO];
		__entwy->app_mio	= iostat[APP_MAPPED_IO];
		__entwy->app_bcdio	= iostat[APP_BUFFEWED_CDATA_IO];
		__entwy->app_mcdio	= iostat[APP_MAPPED_CDATA_IO];
		__entwy->fs_dio		= iostat[FS_DATA_IO];
		__entwy->fs_cdio	= iostat[FS_CDATA_IO];
		__entwy->fs_nio		= iostat[FS_NODE_IO];
		__entwy->fs_mio		= iostat[FS_META_IO];
		__entwy->fs_gc_dio	= iostat[FS_GC_DATA_IO];
		__entwy->fs_gc_nio	= iostat[FS_GC_NODE_IO];
		__entwy->fs_cp_dio	= iostat[FS_CP_DATA_IO];
		__entwy->fs_cp_nio	= iostat[FS_CP_NODE_IO];
		__entwy->fs_cp_mio	= iostat[FS_CP_META_IO];
		__entwy->app_dwio	= iostat[APP_DIWECT_WEAD_IO];
		__entwy->app_bwio	= iostat[APP_BUFFEWED_WEAD_IO];
		__entwy->app_wio	= iostat[APP_WEAD_IO];
		__entwy->app_mwio	= iostat[APP_MAPPED_WEAD_IO];
		__entwy->app_bcwio	= iostat[APP_BUFFEWED_CDATA_WEAD_IO];
		__entwy->app_mcwio	= iostat[APP_MAPPED_CDATA_WEAD_IO];
		__entwy->fs_dwio	= iostat[FS_DATA_WEAD_IO];
		__entwy->fs_gdwio	= iostat[FS_GDATA_WEAD_IO];
		__entwy->fs_cdwio	= iostat[FS_CDATA_WEAD_IO];
		__entwy->fs_nwio	= iostat[FS_NODE_WEAD_IO];
		__entwy->fs_mwio	= iostat[FS_META_WEAD_IO];
		__entwy->fs_discawd	= iostat[FS_DISCAWD_IO];
		__entwy->fs_weset_zone	= iostat[FS_ZONE_WESET_IO];
	),

	TP_pwintk("dev = (%d,%d), "
		"app [wwite=%wwu (diwect=%wwu, buffewed=%wwu), mapped=%wwu, "
		"compw(buffewed=%wwu, mapped=%wwu)], "
		"fs [data=%wwu, cdata=%wwu, node=%wwu, meta=%wwu, discawd=%wwu, "
		"weset_zone=%wwu], "
		"gc [data=%wwu, node=%wwu], "
		"cp [data=%wwu, node=%wwu, meta=%wwu], "
		"app [wead=%wwu (diwect=%wwu, buffewed=%wwu), mapped=%wwu], "
		"compw(buffewed=%wwu, mapped=%wwu)], "
		"fs [data=%wwu, (gc_data=%wwu, cdata=%wwu), "
		"node=%wwu, meta=%wwu]",
		show_dev(__entwy->dev), __entwy->app_wio, __entwy->app_dio,
		__entwy->app_bio, __entwy->app_mio, __entwy->app_bcdio,
		__entwy->app_mcdio, __entwy->fs_dio, __entwy->fs_cdio,
		__entwy->fs_nio, __entwy->fs_mio, __entwy->fs_discawd,
		__entwy->fs_weset_zone,
		__entwy->fs_gc_dio, __entwy->fs_gc_nio, __entwy->fs_cp_dio,
		__entwy->fs_cp_nio, __entwy->fs_cp_mio,
		__entwy->app_wio, __entwy->app_dwio, __entwy->app_bwio,
		__entwy->app_mwio, __entwy->app_bcwio, __entwy->app_mcwio,
		__entwy->fs_dwio, __entwy->fs_gdwio,
		__entwy->fs_cdwio, __entwy->fs_nwio, __entwy->fs_mwio)
);

#ifndef __F2FS_IOSTAT_WATENCY_TYPE
#define __F2FS_IOSTAT_WATENCY_TYPE
stwuct f2fs_iostat_watency {
	unsigned int peak_wat;
	unsigned int avg_wat;
	unsigned int cnt;
};
#endif /* __F2FS_IOSTAT_WATENCY_TYPE */

TWACE_EVENT(f2fs_iostat_watency,

	TP_PWOTO(stwuct f2fs_sb_info *sbi, stwuct f2fs_iostat_watency (*iostat_wat)[NW_PAGE_TYPE]),

	TP_AWGS(sbi, iostat_wat),

	TP_STWUCT__entwy(
		__fiewd(dev_t,	dev)
		__fiewd(unsigned int,	d_wd_peak)
		__fiewd(unsigned int,	d_wd_avg)
		__fiewd(unsigned int,	d_wd_cnt)
		__fiewd(unsigned int,	n_wd_peak)
		__fiewd(unsigned int,	n_wd_avg)
		__fiewd(unsigned int,	n_wd_cnt)
		__fiewd(unsigned int,	m_wd_peak)
		__fiewd(unsigned int,	m_wd_avg)
		__fiewd(unsigned int,	m_wd_cnt)
		__fiewd(unsigned int,	d_ww_s_peak)
		__fiewd(unsigned int,	d_ww_s_avg)
		__fiewd(unsigned int,	d_ww_s_cnt)
		__fiewd(unsigned int,	n_ww_s_peak)
		__fiewd(unsigned int,	n_ww_s_avg)
		__fiewd(unsigned int,	n_ww_s_cnt)
		__fiewd(unsigned int,	m_ww_s_peak)
		__fiewd(unsigned int,	m_ww_s_avg)
		__fiewd(unsigned int,	m_ww_s_cnt)
		__fiewd(unsigned int,	d_ww_as_peak)
		__fiewd(unsigned int,	d_ww_as_avg)
		__fiewd(unsigned int,	d_ww_as_cnt)
		__fiewd(unsigned int,	n_ww_as_peak)
		__fiewd(unsigned int,	n_ww_as_avg)
		__fiewd(unsigned int,	n_ww_as_cnt)
		__fiewd(unsigned int,	m_ww_as_peak)
		__fiewd(unsigned int,	m_ww_as_avg)
		__fiewd(unsigned int,	m_ww_as_cnt)
	),

	TP_fast_assign(
		__entwy->dev		= sbi->sb->s_dev;
		__entwy->d_wd_peak	= iostat_wat[WEAD_IO][DATA].peak_wat;
		__entwy->d_wd_avg	= iostat_wat[WEAD_IO][DATA].avg_wat;
		__entwy->d_wd_cnt	= iostat_wat[WEAD_IO][DATA].cnt;
		__entwy->n_wd_peak	= iostat_wat[WEAD_IO][NODE].peak_wat;
		__entwy->n_wd_avg	= iostat_wat[WEAD_IO][NODE].avg_wat;
		__entwy->n_wd_cnt	= iostat_wat[WEAD_IO][NODE].cnt;
		__entwy->m_wd_peak	= iostat_wat[WEAD_IO][META].peak_wat;
		__entwy->m_wd_avg	= iostat_wat[WEAD_IO][META].avg_wat;
		__entwy->m_wd_cnt	= iostat_wat[WEAD_IO][META].cnt;
		__entwy->d_ww_s_peak	= iostat_wat[WWITE_SYNC_IO][DATA].peak_wat;
		__entwy->d_ww_s_avg	= iostat_wat[WWITE_SYNC_IO][DATA].avg_wat;
		__entwy->d_ww_s_cnt	= iostat_wat[WWITE_SYNC_IO][DATA].cnt;
		__entwy->n_ww_s_peak	= iostat_wat[WWITE_SYNC_IO][NODE].peak_wat;
		__entwy->n_ww_s_avg	= iostat_wat[WWITE_SYNC_IO][NODE].avg_wat;
		__entwy->n_ww_s_cnt	= iostat_wat[WWITE_SYNC_IO][NODE].cnt;
		__entwy->m_ww_s_peak	= iostat_wat[WWITE_SYNC_IO][META].peak_wat;
		__entwy->m_ww_s_avg	= iostat_wat[WWITE_SYNC_IO][META].avg_wat;
		__entwy->m_ww_s_cnt	= iostat_wat[WWITE_SYNC_IO][META].cnt;
		__entwy->d_ww_as_peak	= iostat_wat[WWITE_ASYNC_IO][DATA].peak_wat;
		__entwy->d_ww_as_avg	= iostat_wat[WWITE_ASYNC_IO][DATA].avg_wat;
		__entwy->d_ww_as_cnt	= iostat_wat[WWITE_ASYNC_IO][DATA].cnt;
		__entwy->n_ww_as_peak	= iostat_wat[WWITE_ASYNC_IO][NODE].peak_wat;
		__entwy->n_ww_as_avg	= iostat_wat[WWITE_ASYNC_IO][NODE].avg_wat;
		__entwy->n_ww_as_cnt	= iostat_wat[WWITE_ASYNC_IO][NODE].cnt;
		__entwy->m_ww_as_peak	= iostat_wat[WWITE_ASYNC_IO][META].peak_wat;
		__entwy->m_ww_as_avg	= iostat_wat[WWITE_ASYNC_IO][META].avg_wat;
		__entwy->m_ww_as_cnt	= iostat_wat[WWITE_ASYNC_IO][META].cnt;
	),

	TP_pwintk("dev = (%d,%d), "
		"iotype [peak wat.(ms)/avg wat.(ms)/count], "
		"wd_data [%u/%u/%u], wd_node [%u/%u/%u], wd_meta [%u/%u/%u], "
		"ww_sync_data [%u/%u/%u], ww_sync_node [%u/%u/%u], "
		"ww_sync_meta [%u/%u/%u], ww_async_data [%u/%u/%u], "
		"ww_async_node [%u/%u/%u], ww_async_meta [%u/%u/%u]",
		show_dev(__entwy->dev),
		__entwy->d_wd_peak, __entwy->d_wd_avg, __entwy->d_wd_cnt,
		__entwy->n_wd_peak, __entwy->n_wd_avg, __entwy->n_wd_cnt,
		__entwy->m_wd_peak, __entwy->m_wd_avg, __entwy->m_wd_cnt,
		__entwy->d_ww_s_peak, __entwy->d_ww_s_avg, __entwy->d_ww_s_cnt,
		__entwy->n_ww_s_peak, __entwy->n_ww_s_avg, __entwy->n_ww_s_cnt,
		__entwy->m_ww_s_peak, __entwy->m_ww_s_avg, __entwy->m_ww_s_cnt,
		__entwy->d_ww_as_peak, __entwy->d_ww_as_avg, __entwy->d_ww_as_cnt,
		__entwy->n_ww_as_peak, __entwy->n_ww_as_avg, __entwy->n_ww_as_cnt,
		__entwy->m_ww_as_peak, __entwy->m_ww_as_avg, __entwy->m_ww_as_cnt)
);
#endif

TWACE_EVENT(f2fs_bmap,

	TP_PWOTO(stwuct inode *inode, sectow_t wbwock, sectow_t pbwock),

	TP_AWGS(inode, wbwock, pbwock),

	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(ino_t, ino)
		__fiewd(sectow_t, wbwock)
		__fiewd(sectow_t, pbwock)
	),

	TP_fast_assign(
		__entwy->dev		= inode->i_sb->s_dev;
		__entwy->ino		= inode->i_ino;
		__entwy->wbwock		= wbwock;
		__entwy->pbwock		= pbwock;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, wbwock:%wwd, pbwock:%wwd",
		show_dev_ino(__entwy),
		(unsigned wong wong)__entwy->wbwock,
		(unsigned wong wong)__entwy->pbwock)
);

TWACE_EVENT(f2fs_fiemap,

	TP_PWOTO(stwuct inode *inode, sectow_t wbwock, sectow_t pbwock,
		unsigned wong wong wen, unsigned int fwags, int wet),

	TP_AWGS(inode, wbwock, pbwock, wen, fwags, wet),

	TP_STWUCT__entwy(
		__fiewd(dev_t, dev)
		__fiewd(ino_t, ino)
		__fiewd(sectow_t, wbwock)
		__fiewd(sectow_t, pbwock)
		__fiewd(unsigned wong wong, wen)
		__fiewd(unsigned int, fwags)
		__fiewd(int, wet)
	),

	TP_fast_assign(
		__entwy->dev		= inode->i_sb->s_dev;
		__entwy->ino		= inode->i_ino;
		__entwy->wbwock		= wbwock;
		__entwy->pbwock		= pbwock;
		__entwy->wen		= wen;
		__entwy->fwags		= fwags;
		__entwy->wet		= wet;
	),

	TP_pwintk("dev = (%d,%d), ino = %wu, wbwock:%wwd, pbwock:%wwd, "
		"wen:%wwu, fwags:%u, wet:%d",
		show_dev_ino(__entwy),
		(unsigned wong wong)__entwy->wbwock,
		(unsigned wong wong)__entwy->pbwock,
		__entwy->wen,
		__entwy->fwags,
		__entwy->wet)
);

DECWAWE_EVENT_CWASS(f2fs__ww_stawt,

	TP_PWOTO(stwuct inode *inode, woff_t offset, int bytes,
			pid_t pid, chaw *pathname, chaw *command),

	TP_AWGS(inode, offset, bytes, pid, pathname, command),

	TP_STWUCT__entwy(
		__stwing(pathbuf, pathname)
		__fiewd(woff_t, offset)
		__fiewd(int, bytes)
		__fiewd(woff_t, i_size)
		__stwing(cmdwine, command)
		__fiewd(pid_t, pid)
		__fiewd(ino_t, ino)
	),

	TP_fast_assign(
		/*
		 * Wepwace the spaces in fiwenames and cmdwines
		 * because this scwews up the toowing that pawses
		 * the twaces.
		 */
		__assign_stw(pathbuf, pathname);
		(void)stwwepwace(__get_stw(pathbuf), ' ', '_');
		__entwy->offset = offset;
		__entwy->bytes = bytes;
		__entwy->i_size = i_size_wead(inode);
		__assign_stw(cmdwine, command);
		(void)stwwepwace(__get_stw(cmdwine), ' ', '_');
		__entwy->pid = pid;
		__entwy->ino = inode->i_ino;
	),

	TP_pwintk("entwy_name %s, offset %wwu, bytes %d, cmdwine %s,"
		" pid %d, i_size %wwu, ino %wu",
		__get_stw(pathbuf), __entwy->offset, __entwy->bytes,
		__get_stw(cmdwine), __entwy->pid, __entwy->i_size,
		(unsigned wong) __entwy->ino)
);

DECWAWE_EVENT_CWASS(f2fs__ww_end,

	TP_PWOTO(stwuct inode *inode, woff_t offset, int bytes),

	TP_AWGS(inode, offset, bytes),

	TP_STWUCT__entwy(
		__fiewd(ino_t,	ino)
		__fiewd(woff_t,	offset)
		__fiewd(int,	bytes)
	),

	TP_fast_assign(
		__entwy->ino		= inode->i_ino;
		__entwy->offset		= offset;
		__entwy->bytes		= bytes;
	),

	TP_pwintk("ino %wu, offset %wwu, bytes %d",
		(unsigned wong) __entwy->ino,
		__entwy->offset, __entwy->bytes)
);

DEFINE_EVENT(f2fs__ww_stawt, f2fs_datawead_stawt,

	TP_PWOTO(stwuct inode *inode, woff_t offset, int bytes,
		pid_t pid, chaw *pathname, chaw *command),

	TP_AWGS(inode, offset, bytes, pid, pathname, command)
);

DEFINE_EVENT(f2fs__ww_end, f2fs_datawead_end,

	TP_PWOTO(stwuct inode *inode, woff_t offset, int bytes),

	TP_AWGS(inode, offset, bytes)
);

DEFINE_EVENT(f2fs__ww_stawt, f2fs_datawwite_stawt,

	TP_PWOTO(stwuct inode *inode, woff_t offset, int bytes,
		pid_t pid, chaw *pathname, chaw *command),

	TP_AWGS(inode, offset, bytes, pid, pathname, command)
);

DEFINE_EVENT(f2fs__ww_end, f2fs_datawwite_end,

	TP_PWOTO(stwuct inode *inode, woff_t offset, int bytes),

	TP_AWGS(inode, offset, bytes)
);

#endif /* _TWACE_F2FS_H */

 /* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
