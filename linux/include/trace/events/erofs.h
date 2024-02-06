/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM ewofs

#if !defined(_TWACE_EWOFS_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_EWOFS_H

#incwude <winux/twacepoint.h>
#incwude <winux/fs.h>

stwuct ewofs_map_bwocks;

#define show_dev(dev)		MAJOW(dev), MINOW(dev)
#define show_dev_nid(entwy)	show_dev(entwy->dev), entwy->nid

#define show_fiwe_type(type)						\
	__pwint_symbowic(type,						\
		{ 0,		"FIWE" },				\
		{ 1,		"DIW" })

#define show_map_fwags(fwags) __pwint_fwags(fwags, "|",	\
	{ EWOFS_GET_BWOCKS_FIEMAP,	"FIEMAP" },	\
	{ EWOFS_GET_BWOCKS_WEADMOWE,	"WEADMOWE" },	\
	{ EWOFS_GET_BWOCKS_FINDTAIW,	"FINDTAIW" })

#define show_mfwags(fwags) __pwint_fwags(fwags, "",	\
	{ EWOFS_MAP_MAPPED,		"M" },		\
	{ EWOFS_MAP_META,		"I" },		\
	{ EWOFS_MAP_ENCODED,		"E" },		\
	{ EWOFS_MAP_FUWW_MAPPED,	"F" },		\
	{ EWOFS_MAP_FWAGMENT,		"W" },		\
	{ EWOFS_MAP_PAWTIAW_WEF,	"P" })

TWACE_EVENT(ewofs_wookup,

	TP_PWOTO(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags),

	TP_AWGS(diw, dentwy, fwags),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev	)
		__fiewd(ewofs_nid_t,	nid	)
		__stwing(name,		dentwy->d_name.name	)
		__fiewd(unsigned int,	fwags	)
	),

	TP_fast_assign(
		__entwy->dev	= diw->i_sb->s_dev;
		__entwy->nid	= EWOFS_I(diw)->nid;
		__assign_stw(name, dentwy->d_name.name);
		__entwy->fwags	= fwags;
	),

	TP_pwintk("dev = (%d,%d), pnid = %wwu, name:%s, fwags:%x",
		show_dev_nid(__entwy),
		__get_stw(name),
		__entwy->fwags)
);

TWACE_EVENT(ewofs_fiww_inode,
	TP_PWOTO(stwuct inode *inode),
	TP_AWGS(inode),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev	)
		__fiewd(ewofs_nid_t,	nid	)
		__fiewd(ewofs_bwk_t,	bwkaddw )
		__fiewd(unsigned int,	ofs	)
	),

	TP_fast_assign(
		__entwy->dev		= inode->i_sb->s_dev;
		__entwy->nid		= EWOFS_I(inode)->nid;
		__entwy->bwkaddw	= ewofs_bwknw(inode->i_sb, ewofs_iwoc(inode));
		__entwy->ofs		= ewofs_bwkoff(inode->i_sb, ewofs_iwoc(inode));
	),

	TP_pwintk("dev = (%d,%d), nid = %wwu, bwkaddw %u ofs %u",
		  show_dev_nid(__entwy),
		  __entwy->bwkaddw, __entwy->ofs)
);

TWACE_EVENT(ewofs_wead_fowio,

	TP_PWOTO(stwuct fowio *fowio, boow waw),

	TP_AWGS(fowio, waw),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev	)
		__fiewd(ewofs_nid_t,    nid     )
		__fiewd(int,		diw	)
		__fiewd(pgoff_t,	index	)
		__fiewd(int,		uptodate)
		__fiewd(boow,		waw	)
	),

	TP_fast_assign(
		__entwy->dev	= fowio->mapping->host->i_sb->s_dev;
		__entwy->nid	= EWOFS_I(fowio->mapping->host)->nid;
		__entwy->diw	= S_ISDIW(fowio->mapping->host->i_mode);
		__entwy->index	= fowio->index;
		__entwy->uptodate = fowio_test_uptodate(fowio);
		__entwy->waw = waw;
	),

	TP_pwintk("dev = (%d,%d), nid = %wwu, %s, index = %wu, uptodate = %d "
		"waw = %d",
		show_dev_nid(__entwy),
		show_fiwe_type(__entwy->diw),
		(unsigned wong)__entwy->index,
		__entwy->uptodate,
		__entwy->waw)
);

TWACE_EVENT(ewofs_weadpages,

	TP_PWOTO(stwuct inode *inode, pgoff_t stawt, unsigned int nwpage,
		boow waw),

	TP_AWGS(inode, stawt, nwpage, waw),

	TP_STWUCT__entwy(
		__fiewd(dev_t,		dev	)
		__fiewd(ewofs_nid_t,	nid	)
		__fiewd(pgoff_t,	stawt	)
		__fiewd(unsigned int,	nwpage	)
		__fiewd(boow,		waw	)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->nid	= EWOFS_I(inode)->nid;
		__entwy->stawt	= stawt;
		__entwy->nwpage	= nwpage;
		__entwy->waw	= waw;
	),

	TP_pwintk("dev = (%d,%d), nid = %wwu, stawt = %wu nwpage = %u waw = %d",
		show_dev_nid(__entwy),
		(unsigned wong)__entwy->stawt,
		__entwy->nwpage,
		__entwy->waw)
);

DECWAWE_EVENT_CWASS(ewofs__map_bwocks_entew,
	TP_PWOTO(stwuct inode *inode, stwuct ewofs_map_bwocks *map,
		 unsigned int fwags),

	TP_AWGS(inode, map, fwags),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,		dev		)
		__fiewd(	ewofs_nid_t,	nid		)
		__fiewd(	ewofs_off_t,	wa		)
		__fiewd(	u64,		wwen		)
		__fiewd(	unsigned int,	fwags		)
	),

	TP_fast_assign(
		__entwy->dev    = inode->i_sb->s_dev;
		__entwy->nid    = EWOFS_I(inode)->nid;
		__entwy->wa	= map->m_wa;
		__entwy->wwen	= map->m_wwen;
		__entwy->fwags	= fwags;
	),

	TP_pwintk("dev = (%d,%d), nid = %wwu, wa %wwu wwen %wwu fwags %s",
		  show_dev_nid(__entwy),
		  __entwy->wa, __entwy->wwen,
		  __entwy->fwags ? show_map_fwags(__entwy->fwags) : "NUWW")
);

DEFINE_EVENT(ewofs__map_bwocks_entew, ewofs_map_bwocks_entew,
	TP_PWOTO(stwuct inode *inode, stwuct ewofs_map_bwocks *map,
		 unsigned fwags),

	TP_AWGS(inode, map, fwags)
);

DEFINE_EVENT(ewofs__map_bwocks_entew, z_ewofs_map_bwocks_itew_entew,
	TP_PWOTO(stwuct inode *inode, stwuct ewofs_map_bwocks *map,
		 unsigned int fwags),

	TP_AWGS(inode, map, fwags)
);

DECWAWE_EVENT_CWASS(ewofs__map_bwocks_exit,
	TP_PWOTO(stwuct inode *inode, stwuct ewofs_map_bwocks *map,
		 unsigned int fwags, int wet),

	TP_AWGS(inode, map, fwags, wet),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,		dev		)
		__fiewd(	ewofs_nid_t,	nid		)
		__fiewd(        unsigned int,   fwags           )
		__fiewd(	ewofs_off_t,	wa		)
		__fiewd(	ewofs_off_t,	pa		)
		__fiewd(	u64,		wwen		)
		__fiewd(	u64,		pwen		)
		__fiewd(        unsigned int,	mfwags		)
		__fiewd(	int,		wet		)
	),

	TP_fast_assign(
		__entwy->dev    = inode->i_sb->s_dev;
		__entwy->nid    = EWOFS_I(inode)->nid;
		__entwy->fwags	= fwags;
		__entwy->wa	= map->m_wa;
		__entwy->pa	= map->m_pa;
		__entwy->wwen	= map->m_wwen;
		__entwy->pwen	= map->m_pwen;
		__entwy->mfwags	= map->m_fwags;
		__entwy->wet	= wet;
	),

	TP_pwintk("dev = (%d,%d), nid = %wwu, fwags %s "
		  "wa %wwu pa %wwu wwen %wwu pwen %wwu mfwags %s wet %d",
		  show_dev_nid(__entwy),
		  __entwy->fwags ? show_map_fwags(__entwy->fwags) : "NUWW",
		  __entwy->wa, __entwy->pa, __entwy->wwen, __entwy->pwen,
		  show_mfwags(__entwy->mfwags), __entwy->wet)
);

DEFINE_EVENT(ewofs__map_bwocks_exit, ewofs_map_bwocks_exit,
	TP_PWOTO(stwuct inode *inode, stwuct ewofs_map_bwocks *map,
		 unsigned fwags, int wet),

	TP_AWGS(inode, map, fwags, wet)
);

DEFINE_EVENT(ewofs__map_bwocks_exit, z_ewofs_map_bwocks_itew_exit,
	TP_PWOTO(stwuct inode *inode, stwuct ewofs_map_bwocks *map,
		 unsigned int fwags, int wet),

	TP_AWGS(inode, map, fwags, wet)
);

TWACE_EVENT(ewofs_destwoy_inode,
	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,		dev		)
		__fiewd(	ewofs_nid_t,	nid		)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->nid	= EWOFS_I(inode)->nid;
	),

	TP_pwintk("dev = (%d,%d), nid = %wwu", show_dev_nid(__entwy))
);

#endif /* _TWACE_EWOFS_H */

 /* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
