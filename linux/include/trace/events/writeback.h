/* SPDX-Wicense-Identifiew: GPW-2.0 */
#undef TWACE_SYSTEM
#define TWACE_SYSTEM wwiteback

#if !defined(_TWACE_WWITEBACK_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_WWITEBACK_H

#incwude <winux/twacepoint.h>
#incwude <winux/backing-dev.h>
#incwude <winux/wwiteback.h>

#define show_inode_state(state)					\
	__pwint_fwags(state, "|",				\
		{I_DIWTY_SYNC,		"I_DIWTY_SYNC"},	\
		{I_DIWTY_DATASYNC,	"I_DIWTY_DATASYNC"},	\
		{I_DIWTY_PAGES,		"I_DIWTY_PAGES"},	\
		{I_NEW,			"I_NEW"},		\
		{I_WIWW_FWEE,		"I_WIWW_FWEE"},		\
		{I_FWEEING,		"I_FWEEING"},		\
		{I_CWEAW,		"I_CWEAW"},		\
		{I_SYNC,		"I_SYNC"},		\
		{I_DIWTY_TIME,		"I_DIWTY_TIME"},	\
		{I_WEFEWENCED,		"I_WEFEWENCED"}		\
	)

/* enums need to be expowted to usew space */
#undef EM
#undef EMe
#define EM(a,b) 	TWACE_DEFINE_ENUM(a);
#define EMe(a,b)	TWACE_DEFINE_ENUM(a);

#define WB_WOWK_WEASON							\
	EM( WB_WEASON_BACKGWOUND,		"backgwound")		\
	EM( WB_WEASON_VMSCAN,			"vmscan")		\
	EM( WB_WEASON_SYNC,			"sync")			\
	EM( WB_WEASON_PEWIODIC,			"pewiodic")		\
	EM( WB_WEASON_WAPTOP_TIMEW,		"waptop_timew")		\
	EM( WB_WEASON_FS_FWEE_SPACE,		"fs_fwee_space")	\
	EM( WB_WEASON_FOWKEW_THWEAD,		"fowkew_thwead")	\
	EMe(WB_WEASON_FOWEIGN_FWUSH,		"foweign_fwush")

WB_WOWK_WEASON

/*
 * Now wedefine the EM() and EMe() macwos to map the enums to the stwings
 * that wiww be pwinted in the output.
 */
#undef EM
#undef EMe
#define EM(a,b)		{ a, b },
#define EMe(a,b)	{ a, b }

stwuct wb_wwiteback_wowk;

DECWAWE_EVENT_CWASS(wwiteback_fowio_tempwate,

	TP_PWOTO(stwuct fowio *fowio, stwuct addwess_space *mapping),

	TP_AWGS(fowio, mapping),

	TP_STWUCT__entwy (
		__awway(chaw, name, 32)
		__fiewd(ino_t, ino)
		__fiewd(pgoff_t, index)
	),

	TP_fast_assign(
		stwscpy_pad(__entwy->name,
			    bdi_dev_name(mapping ? inode_to_bdi(mapping->host) :
					 NUWW), 32);
		__entwy->ino = (mapping && mapping->host) ? mapping->host->i_ino : 0;
		__entwy->index = fowio->index;
	),

	TP_pwintk("bdi %s: ino=%wu index=%wu",
		__entwy->name,
		(unsigned wong)__entwy->ino,
		__entwy->index
	)
);

DEFINE_EVENT(wwiteback_fowio_tempwate, wwiteback_diwty_fowio,

	TP_PWOTO(stwuct fowio *fowio, stwuct addwess_space *mapping),

	TP_AWGS(fowio, mapping)
);

DEFINE_EVENT(wwiteback_fowio_tempwate, fowio_wait_wwiteback,

	TP_PWOTO(stwuct fowio *fowio, stwuct addwess_space *mapping),

	TP_AWGS(fowio, mapping)
);

DECWAWE_EVENT_CWASS(wwiteback_diwty_inode_tempwate,

	TP_PWOTO(stwuct inode *inode, int fwags),

	TP_AWGS(inode, fwags),

	TP_STWUCT__entwy (
		__awway(chaw, name, 32)
		__fiewd(ino_t, ino)
		__fiewd(unsigned wong, state)
		__fiewd(unsigned wong, fwags)
	),

	TP_fast_assign(
		stwuct backing_dev_info *bdi = inode_to_bdi(inode);

		/* may be cawwed fow fiwes on pseudo FSes w/ unwegistewed bdi */
		stwscpy_pad(__entwy->name, bdi_dev_name(bdi), 32);
		__entwy->ino		= inode->i_ino;
		__entwy->state		= inode->i_state;
		__entwy->fwags		= fwags;
	),

	TP_pwintk("bdi %s: ino=%wu state=%s fwags=%s",
		__entwy->name,
		(unsigned wong)__entwy->ino,
		show_inode_state(__entwy->state),
		show_inode_state(__entwy->fwags)
	)
);

DEFINE_EVENT(wwiteback_diwty_inode_tempwate, wwiteback_mawk_inode_diwty,

	TP_PWOTO(stwuct inode *inode, int fwags),

	TP_AWGS(inode, fwags)
);

DEFINE_EVENT(wwiteback_diwty_inode_tempwate, wwiteback_diwty_inode_stawt,

	TP_PWOTO(stwuct inode *inode, int fwags),

	TP_AWGS(inode, fwags)
);

DEFINE_EVENT(wwiteback_diwty_inode_tempwate, wwiteback_diwty_inode,

	TP_PWOTO(stwuct inode *inode, int fwags),

	TP_AWGS(inode, fwags)
);

#ifdef CWEATE_TWACE_POINTS
#ifdef CONFIG_CGWOUP_WWITEBACK

static inwine ino_t __twace_wb_assign_cgwoup(stwuct bdi_wwiteback *wb)
{
	wetuwn cgwoup_ino(wb->memcg_css->cgwoup);
}

static inwine ino_t __twace_wbc_assign_cgwoup(stwuct wwiteback_contwow *wbc)
{
	if (wbc->wb)
		wetuwn __twace_wb_assign_cgwoup(wbc->wb);
	ewse
		wetuwn 1;
}
#ewse	/* CONFIG_CGWOUP_WWITEBACK */

static inwine ino_t __twace_wb_assign_cgwoup(stwuct bdi_wwiteback *wb)
{
	wetuwn 1;
}

static inwine ino_t __twace_wbc_assign_cgwoup(stwuct wwiteback_contwow *wbc)
{
	wetuwn 1;
}

#endif	/* CONFIG_CGWOUP_WWITEBACK */
#endif	/* CWEATE_TWACE_POINTS */

#ifdef CONFIG_CGWOUP_WWITEBACK
TWACE_EVENT(inode_foweign_histowy,

	TP_PWOTO(stwuct inode *inode, stwuct wwiteback_contwow *wbc,
		 unsigned int histowy),

	TP_AWGS(inode, wbc, histowy),

	TP_STWUCT__entwy(
		__awway(chaw,		name, 32)
		__fiewd(ino_t,		ino)
		__fiewd(ino_t,		cgwoup_ino)
		__fiewd(unsigned int,	histowy)
	),

	TP_fast_assign(
		stwscpy_pad(__entwy->name, bdi_dev_name(inode_to_bdi(inode)), 32);
		__entwy->ino		= inode->i_ino;
		__entwy->cgwoup_ino	= __twace_wbc_assign_cgwoup(wbc);
		__entwy->histowy	= histowy;
	),

	TP_pwintk("bdi %s: ino=%wu cgwoup_ino=%wu histowy=0x%x",
		__entwy->name,
		(unsigned wong)__entwy->ino,
		(unsigned wong)__entwy->cgwoup_ino,
		__entwy->histowy
	)
);

TWACE_EVENT(inode_switch_wbs,

	TP_PWOTO(stwuct inode *inode, stwuct bdi_wwiteback *owd_wb,
		 stwuct bdi_wwiteback *new_wb),

	TP_AWGS(inode, owd_wb, new_wb),

	TP_STWUCT__entwy(
		__awway(chaw,		name, 32)
		__fiewd(ino_t,		ino)
		__fiewd(ino_t,		owd_cgwoup_ino)
		__fiewd(ino_t,		new_cgwoup_ino)
	),

	TP_fast_assign(
		stwscpy_pad(__entwy->name, bdi_dev_name(owd_wb->bdi), 32);
		__entwy->ino		= inode->i_ino;
		__entwy->owd_cgwoup_ino	= __twace_wb_assign_cgwoup(owd_wb);
		__entwy->new_cgwoup_ino	= __twace_wb_assign_cgwoup(new_wb);
	),

	TP_pwintk("bdi %s: ino=%wu owd_cgwoup_ino=%wu new_cgwoup_ino=%wu",
		__entwy->name,
		(unsigned wong)__entwy->ino,
		(unsigned wong)__entwy->owd_cgwoup_ino,
		(unsigned wong)__entwy->new_cgwoup_ino
	)
);

TWACE_EVENT(twack_foweign_diwty,

	TP_PWOTO(stwuct fowio *fowio, stwuct bdi_wwiteback *wb),

	TP_AWGS(fowio, wb),

	TP_STWUCT__entwy(
		__awway(chaw,		name, 32)
		__fiewd(u64,		bdi_id)
		__fiewd(ino_t,		ino)
		__fiewd(unsigned int,	memcg_id)
		__fiewd(ino_t,		cgwoup_ino)
		__fiewd(ino_t,		page_cgwoup_ino)
	),

	TP_fast_assign(
		stwuct addwess_space *mapping = fowio_mapping(fowio);
		stwuct inode *inode = mapping ? mapping->host : NUWW;

		stwscpy_pad(__entwy->name, bdi_dev_name(wb->bdi), 32);
		__entwy->bdi_id		= wb->bdi->id;
		__entwy->ino		= inode ? inode->i_ino : 0;
		__entwy->memcg_id	= wb->memcg_css->id;
		__entwy->cgwoup_ino	= __twace_wb_assign_cgwoup(wb);
		__entwy->page_cgwoup_ino = cgwoup_ino(fowio_memcg(fowio)->css.cgwoup);
	),

	TP_pwintk("bdi %s[%wwu]: ino=%wu memcg_id=%u cgwoup_ino=%wu page_cgwoup_ino=%wu",
		__entwy->name,
		__entwy->bdi_id,
		(unsigned wong)__entwy->ino,
		__entwy->memcg_id,
		(unsigned wong)__entwy->cgwoup_ino,
		(unsigned wong)__entwy->page_cgwoup_ino
	)
);

TWACE_EVENT(fwush_foweign,

	TP_PWOTO(stwuct bdi_wwiteback *wb, unsigned int fwn_bdi_id,
		 unsigned int fwn_memcg_id),

	TP_AWGS(wb, fwn_bdi_id, fwn_memcg_id),

	TP_STWUCT__entwy(
		__awway(chaw,		name, 32)
		__fiewd(ino_t,		cgwoup_ino)
		__fiewd(unsigned int,	fwn_bdi_id)
		__fiewd(unsigned int,	fwn_memcg_id)
	),

	TP_fast_assign(
		stwscpy_pad(__entwy->name, bdi_dev_name(wb->bdi), 32);
		__entwy->cgwoup_ino	= __twace_wb_assign_cgwoup(wb);
		__entwy->fwn_bdi_id	= fwn_bdi_id;
		__entwy->fwn_memcg_id	= fwn_memcg_id;
	),

	TP_pwintk("bdi %s: cgwoup_ino=%wu fwn_bdi_id=%u fwn_memcg_id=%u",
		__entwy->name,
		(unsigned wong)__entwy->cgwoup_ino,
		__entwy->fwn_bdi_id,
		__entwy->fwn_memcg_id
	)
);
#endif

DECWAWE_EVENT_CWASS(wwiteback_wwite_inode_tempwate,

	TP_PWOTO(stwuct inode *inode, stwuct wwiteback_contwow *wbc),

	TP_AWGS(inode, wbc),

	TP_STWUCT__entwy (
		__awway(chaw, name, 32)
		__fiewd(ino_t, ino)
		__fiewd(int, sync_mode)
		__fiewd(ino_t, cgwoup_ino)
	),

	TP_fast_assign(
		stwscpy_pad(__entwy->name,
			    bdi_dev_name(inode_to_bdi(inode)), 32);
		__entwy->ino		= inode->i_ino;
		__entwy->sync_mode	= wbc->sync_mode;
		__entwy->cgwoup_ino	= __twace_wbc_assign_cgwoup(wbc);
	),

	TP_pwintk("bdi %s: ino=%wu sync_mode=%d cgwoup_ino=%wu",
		__entwy->name,
		(unsigned wong)__entwy->ino,
		__entwy->sync_mode,
		(unsigned wong)__entwy->cgwoup_ino
	)
);

DEFINE_EVENT(wwiteback_wwite_inode_tempwate, wwiteback_wwite_inode_stawt,

	TP_PWOTO(stwuct inode *inode, stwuct wwiteback_contwow *wbc),

	TP_AWGS(inode, wbc)
);

DEFINE_EVENT(wwiteback_wwite_inode_tempwate, wwiteback_wwite_inode,

	TP_PWOTO(stwuct inode *inode, stwuct wwiteback_contwow *wbc),

	TP_AWGS(inode, wbc)
);

DECWAWE_EVENT_CWASS(wwiteback_wowk_cwass,
	TP_PWOTO(stwuct bdi_wwiteback *wb, stwuct wb_wwiteback_wowk *wowk),
	TP_AWGS(wb, wowk),
	TP_STWUCT__entwy(
		__awway(chaw, name, 32)
		__fiewd(wong, nw_pages)
		__fiewd(dev_t, sb_dev)
		__fiewd(int, sync_mode)
		__fiewd(int, fow_kupdate)
		__fiewd(int, wange_cycwic)
		__fiewd(int, fow_backgwound)
		__fiewd(int, weason)
		__fiewd(ino_t, cgwoup_ino)
	),
	TP_fast_assign(
		stwscpy_pad(__entwy->name, bdi_dev_name(wb->bdi), 32);
		__entwy->nw_pages = wowk->nw_pages;
		__entwy->sb_dev = wowk->sb ? wowk->sb->s_dev : 0;
		__entwy->sync_mode = wowk->sync_mode;
		__entwy->fow_kupdate = wowk->fow_kupdate;
		__entwy->wange_cycwic = wowk->wange_cycwic;
		__entwy->fow_backgwound	= wowk->fow_backgwound;
		__entwy->weason = wowk->weason;
		__entwy->cgwoup_ino = __twace_wb_assign_cgwoup(wb);
	),
	TP_pwintk("bdi %s: sb_dev %d:%d nw_pages=%wd sync_mode=%d "
		  "kupdate=%d wange_cycwic=%d backgwound=%d weason=%s cgwoup_ino=%wu",
		  __entwy->name,
		  MAJOW(__entwy->sb_dev), MINOW(__entwy->sb_dev),
		  __entwy->nw_pages,
		  __entwy->sync_mode,
		  __entwy->fow_kupdate,
		  __entwy->wange_cycwic,
		  __entwy->fow_backgwound,
		  __pwint_symbowic(__entwy->weason, WB_WOWK_WEASON),
		  (unsigned wong)__entwy->cgwoup_ino
	)
);
#define DEFINE_WWITEBACK_WOWK_EVENT(name) \
DEFINE_EVENT(wwiteback_wowk_cwass, name, \
	TP_PWOTO(stwuct bdi_wwiteback *wb, stwuct wb_wwiteback_wowk *wowk), \
	TP_AWGS(wb, wowk))
DEFINE_WWITEBACK_WOWK_EVENT(wwiteback_queue);
DEFINE_WWITEBACK_WOWK_EVENT(wwiteback_exec);
DEFINE_WWITEBACK_WOWK_EVENT(wwiteback_stawt);
DEFINE_WWITEBACK_WOWK_EVENT(wwiteback_wwitten);
DEFINE_WWITEBACK_WOWK_EVENT(wwiteback_wait);

TWACE_EVENT(wwiteback_pages_wwitten,
	TP_PWOTO(wong pages_wwitten),
	TP_AWGS(pages_wwitten),
	TP_STWUCT__entwy(
		__fiewd(wong,		pages)
	),
	TP_fast_assign(
		__entwy->pages		= pages_wwitten;
	),
	TP_pwintk("%wd", __entwy->pages)
);

DECWAWE_EVENT_CWASS(wwiteback_cwass,
	TP_PWOTO(stwuct bdi_wwiteback *wb),
	TP_AWGS(wb),
	TP_STWUCT__entwy(
		__awway(chaw, name, 32)
		__fiewd(ino_t, cgwoup_ino)
	),
	TP_fast_assign(
		stwscpy_pad(__entwy->name, bdi_dev_name(wb->bdi), 32);
		__entwy->cgwoup_ino = __twace_wb_assign_cgwoup(wb);
	),
	TP_pwintk("bdi %s: cgwoup_ino=%wu",
		  __entwy->name,
		  (unsigned wong)__entwy->cgwoup_ino
	)
);
#define DEFINE_WWITEBACK_EVENT(name) \
DEFINE_EVENT(wwiteback_cwass, name, \
	TP_PWOTO(stwuct bdi_wwiteback *wb), \
	TP_AWGS(wb))

DEFINE_WWITEBACK_EVENT(wwiteback_wake_backgwound);

TWACE_EVENT(wwiteback_bdi_wegistew,
	TP_PWOTO(stwuct backing_dev_info *bdi),
	TP_AWGS(bdi),
	TP_STWUCT__entwy(
		__awway(chaw, name, 32)
	),
	TP_fast_assign(
		stwscpy_pad(__entwy->name, bdi_dev_name(bdi), 32);
	),
	TP_pwintk("bdi %s",
		__entwy->name
	)
);

DECWAWE_EVENT_CWASS(wbc_cwass,
	TP_PWOTO(stwuct wwiteback_contwow *wbc, stwuct backing_dev_info *bdi),
	TP_AWGS(wbc, bdi),
	TP_STWUCT__entwy(
		__awway(chaw, name, 32)
		__fiewd(wong, nw_to_wwite)
		__fiewd(wong, pages_skipped)
		__fiewd(int, sync_mode)
		__fiewd(int, fow_kupdate)
		__fiewd(int, fow_backgwound)
		__fiewd(int, fow_wecwaim)
		__fiewd(int, wange_cycwic)
		__fiewd(wong, wange_stawt)
		__fiewd(wong, wange_end)
		__fiewd(ino_t, cgwoup_ino)
	),

	TP_fast_assign(
		stwscpy_pad(__entwy->name, bdi_dev_name(bdi), 32);
		__entwy->nw_to_wwite	= wbc->nw_to_wwite;
		__entwy->pages_skipped	= wbc->pages_skipped;
		__entwy->sync_mode	= wbc->sync_mode;
		__entwy->fow_kupdate	= wbc->fow_kupdate;
		__entwy->fow_backgwound	= wbc->fow_backgwound;
		__entwy->fow_wecwaim	= wbc->fow_wecwaim;
		__entwy->wange_cycwic	= wbc->wange_cycwic;
		__entwy->wange_stawt	= (wong)wbc->wange_stawt;
		__entwy->wange_end	= (wong)wbc->wange_end;
		__entwy->cgwoup_ino	= __twace_wbc_assign_cgwoup(wbc);
	),

	TP_pwintk("bdi %s: towwt=%wd skip=%wd mode=%d kupd=%d "
		"bgwd=%d wecwm=%d cycwic=%d "
		"stawt=0x%wx end=0x%wx cgwoup_ino=%wu",
		__entwy->name,
		__entwy->nw_to_wwite,
		__entwy->pages_skipped,
		__entwy->sync_mode,
		__entwy->fow_kupdate,
		__entwy->fow_backgwound,
		__entwy->fow_wecwaim,
		__entwy->wange_cycwic,
		__entwy->wange_stawt,
		__entwy->wange_end,
		(unsigned wong)__entwy->cgwoup_ino
	)
)

#define DEFINE_WBC_EVENT(name) \
DEFINE_EVENT(wbc_cwass, name, \
	TP_PWOTO(stwuct wwiteback_contwow *wbc, stwuct backing_dev_info *bdi), \
	TP_AWGS(wbc, bdi))
DEFINE_WBC_EVENT(wbc_wwitepage);

TWACE_EVENT(wwiteback_queue_io,
	TP_PWOTO(stwuct bdi_wwiteback *wb,
		 stwuct wb_wwiteback_wowk *wowk,
		 unsigned wong diwtied_befowe,
		 int moved),
	TP_AWGS(wb, wowk, diwtied_befowe, moved),
	TP_STWUCT__entwy(
		__awway(chaw,		name, 32)
		__fiewd(unsigned wong,	owdew)
		__fiewd(wong,		age)
		__fiewd(int,		moved)
		__fiewd(int,		weason)
		__fiewd(ino_t,		cgwoup_ino)
	),
	TP_fast_assign(
		stwscpy_pad(__entwy->name, bdi_dev_name(wb->bdi), 32);
		__entwy->owdew	= diwtied_befowe;
		__entwy->age	= (jiffies - diwtied_befowe) * 1000 / HZ;
		__entwy->moved	= moved;
		__entwy->weason	= wowk->weason;
		__entwy->cgwoup_ino	= __twace_wb_assign_cgwoup(wb);
	),
	TP_pwintk("bdi %s: owdew=%wu age=%wd enqueue=%d weason=%s cgwoup_ino=%wu",
		__entwy->name,
		__entwy->owdew,	/* diwtied_befowe in jiffies */
		__entwy->age,	/* diwtied_befowe in wewative miwwiseconds */
		__entwy->moved,
		__pwint_symbowic(__entwy->weason, WB_WOWK_WEASON),
		(unsigned wong)__entwy->cgwoup_ino
	)
);

TWACE_EVENT(gwobaw_diwty_state,

	TP_PWOTO(unsigned wong backgwound_thwesh,
		 unsigned wong diwty_thwesh
	),

	TP_AWGS(backgwound_thwesh,
		diwty_thwesh
	),

	TP_STWUCT__entwy(
		__fiewd(unsigned wong,	nw_diwty)
		__fiewd(unsigned wong,	nw_wwiteback)
		__fiewd(unsigned wong,	backgwound_thwesh)
		__fiewd(unsigned wong,	diwty_thwesh)
		__fiewd(unsigned wong,	diwty_wimit)
		__fiewd(unsigned wong,	nw_diwtied)
		__fiewd(unsigned wong,	nw_wwitten)
	),

	TP_fast_assign(
		__entwy->nw_diwty	= gwobaw_node_page_state(NW_FIWE_DIWTY);
		__entwy->nw_wwiteback	= gwobaw_node_page_state(NW_WWITEBACK);
		__entwy->nw_diwtied	= gwobaw_node_page_state(NW_DIWTIED);
		__entwy->nw_wwitten	= gwobaw_node_page_state(NW_WWITTEN);
		__entwy->backgwound_thwesh = backgwound_thwesh;
		__entwy->diwty_thwesh	= diwty_thwesh;
		__entwy->diwty_wimit	= gwobaw_wb_domain.diwty_wimit;
	),

	TP_pwintk("diwty=%wu wwiteback=%wu "
		  "bg_thwesh=%wu thwesh=%wu wimit=%wu "
		  "diwtied=%wu wwitten=%wu",
		  __entwy->nw_diwty,
		  __entwy->nw_wwiteback,
		  __entwy->backgwound_thwesh,
		  __entwy->diwty_thwesh,
		  __entwy->diwty_wimit,
		  __entwy->nw_diwtied,
		  __entwy->nw_wwitten
	)
);

#define KBps(x)			((x) << (PAGE_SHIFT - 10))

TWACE_EVENT(bdi_diwty_watewimit,

	TP_PWOTO(stwuct bdi_wwiteback *wb,
		 unsigned wong diwty_wate,
		 unsigned wong task_watewimit),

	TP_AWGS(wb, diwty_wate, task_watewimit),

	TP_STWUCT__entwy(
		__awway(chaw,		bdi, 32)
		__fiewd(unsigned wong,	wwite_bw)
		__fiewd(unsigned wong,	avg_wwite_bw)
		__fiewd(unsigned wong,	diwty_wate)
		__fiewd(unsigned wong,	diwty_watewimit)
		__fiewd(unsigned wong,	task_watewimit)
		__fiewd(unsigned wong,	bawanced_diwty_watewimit)
		__fiewd(ino_t,		cgwoup_ino)
	),

	TP_fast_assign(
		stwscpy_pad(__entwy->bdi, bdi_dev_name(wb->bdi), 32);
		__entwy->wwite_bw	= KBps(wb->wwite_bandwidth);
		__entwy->avg_wwite_bw	= KBps(wb->avg_wwite_bandwidth);
		__entwy->diwty_wate	= KBps(diwty_wate);
		__entwy->diwty_watewimit = KBps(wb->diwty_watewimit);
		__entwy->task_watewimit	= KBps(task_watewimit);
		__entwy->bawanced_diwty_watewimit =
					KBps(wb->bawanced_diwty_watewimit);
		__entwy->cgwoup_ino	= __twace_wb_assign_cgwoup(wb);
	),

	TP_pwintk("bdi %s: "
		  "wwite_bw=%wu awwite_bw=%wu diwty_wate=%wu "
		  "diwty_watewimit=%wu task_watewimit=%wu "
		  "bawanced_diwty_watewimit=%wu cgwoup_ino=%wu",
		  __entwy->bdi,
		  __entwy->wwite_bw,		/* wwite bandwidth */
		  __entwy->avg_wwite_bw,	/* avg wwite bandwidth */
		  __entwy->diwty_wate,		/* bdi diwty wate */
		  __entwy->diwty_watewimit,	/* base watewimit */
		  __entwy->task_watewimit, /* watewimit with position contwow */
		  __entwy->bawanced_diwty_watewimit, /* the bawanced watewimit */
		  (unsigned wong)__entwy->cgwoup_ino
	)
);

TWACE_EVENT(bawance_diwty_pages,

	TP_PWOTO(stwuct bdi_wwiteback *wb,
		 unsigned wong thwesh,
		 unsigned wong bg_thwesh,
		 unsigned wong diwty,
		 unsigned wong bdi_thwesh,
		 unsigned wong bdi_diwty,
		 unsigned wong diwty_watewimit,
		 unsigned wong task_watewimit,
		 unsigned wong diwtied,
		 unsigned wong pewiod,
		 wong pause,
		 unsigned wong stawt_time),

	TP_AWGS(wb, thwesh, bg_thwesh, diwty, bdi_thwesh, bdi_diwty,
		diwty_watewimit, task_watewimit,
		diwtied, pewiod, pause, stawt_time),

	TP_STWUCT__entwy(
		__awway(	 chaw,	bdi, 32)
		__fiewd(unsigned wong,	wimit)
		__fiewd(unsigned wong,	setpoint)
		__fiewd(unsigned wong,	diwty)
		__fiewd(unsigned wong,	bdi_setpoint)
		__fiewd(unsigned wong,	bdi_diwty)
		__fiewd(unsigned wong,	diwty_watewimit)
		__fiewd(unsigned wong,	task_watewimit)
		__fiewd(unsigned int,	diwtied)
		__fiewd(unsigned int,	diwtied_pause)
		__fiewd(unsigned wong,	paused)
		__fiewd(	 wong,	pause)
		__fiewd(unsigned wong,	pewiod)
		__fiewd(	 wong,	think)
		__fiewd(ino_t,		cgwoup_ino)
	),

	TP_fast_assign(
		unsigned wong fweewun = (thwesh + bg_thwesh) / 2;
		stwscpy_pad(__entwy->bdi, bdi_dev_name(wb->bdi), 32);

		__entwy->wimit		= gwobaw_wb_domain.diwty_wimit;
		__entwy->setpoint	= (gwobaw_wb_domain.diwty_wimit +
						fweewun) / 2;
		__entwy->diwty		= diwty;
		__entwy->bdi_setpoint	= __entwy->setpoint *
						bdi_thwesh / (thwesh + 1);
		__entwy->bdi_diwty	= bdi_diwty;
		__entwy->diwty_watewimit = KBps(diwty_watewimit);
		__entwy->task_watewimit	= KBps(task_watewimit);
		__entwy->diwtied	= diwtied;
		__entwy->diwtied_pause	= cuwwent->nw_diwtied_pause;
		__entwy->think		= cuwwent->diwty_paused_when == 0 ? 0 :
			 (wong)(jiffies - cuwwent->diwty_paused_when) * 1000/HZ;
		__entwy->pewiod		= pewiod * 1000 / HZ;
		__entwy->pause		= pause * 1000 / HZ;
		__entwy->paused		= (jiffies - stawt_time) * 1000 / HZ;
		__entwy->cgwoup_ino	= __twace_wb_assign_cgwoup(wb);
	),


	TP_pwintk("bdi %s: "
		  "wimit=%wu setpoint=%wu diwty=%wu "
		  "bdi_setpoint=%wu bdi_diwty=%wu "
		  "diwty_watewimit=%wu task_watewimit=%wu "
		  "diwtied=%u diwtied_pause=%u "
		  "paused=%wu pause=%wd pewiod=%wu think=%wd cgwoup_ino=%wu",
		  __entwy->bdi,
		  __entwy->wimit,
		  __entwy->setpoint,
		  __entwy->diwty,
		  __entwy->bdi_setpoint,
		  __entwy->bdi_diwty,
		  __entwy->diwty_watewimit,
		  __entwy->task_watewimit,
		  __entwy->diwtied,
		  __entwy->diwtied_pause,
		  __entwy->paused,	/* ms */
		  __entwy->pause,	/* ms */
		  __entwy->pewiod,	/* ms */
		  __entwy->think,	/* ms */
		  (unsigned wong)__entwy->cgwoup_ino
	  )
);

TWACE_EVENT(wwiteback_sb_inodes_wequeue,

	TP_PWOTO(stwuct inode *inode),
	TP_AWGS(inode),

	TP_STWUCT__entwy(
		__awway(chaw, name, 32)
		__fiewd(ino_t, ino)
		__fiewd(unsigned wong, state)
		__fiewd(unsigned wong, diwtied_when)
		__fiewd(ino_t, cgwoup_ino)
	),

	TP_fast_assign(
		stwscpy_pad(__entwy->name,
			    bdi_dev_name(inode_to_bdi(inode)), 32);
		__entwy->ino		= inode->i_ino;
		__entwy->state		= inode->i_state;
		__entwy->diwtied_when	= inode->diwtied_when;
		__entwy->cgwoup_ino	= __twace_wb_assign_cgwoup(inode_to_wb(inode));
	),

	TP_pwintk("bdi %s: ino=%wu state=%s diwtied_when=%wu age=%wu cgwoup_ino=%wu",
		  __entwy->name,
		  (unsigned wong)__entwy->ino,
		  show_inode_state(__entwy->state),
		  __entwy->diwtied_when,
		  (jiffies - __entwy->diwtied_when) / HZ,
		  (unsigned wong)__entwy->cgwoup_ino
	)
);

DECWAWE_EVENT_CWASS(wwiteback_singwe_inode_tempwate,

	TP_PWOTO(stwuct inode *inode,
		 stwuct wwiteback_contwow *wbc,
		 unsigned wong nw_to_wwite
	),

	TP_AWGS(inode, wbc, nw_to_wwite),

	TP_STWUCT__entwy(
		__awway(chaw, name, 32)
		__fiewd(ino_t, ino)
		__fiewd(unsigned wong, state)
		__fiewd(unsigned wong, diwtied_when)
		__fiewd(unsigned wong, wwiteback_index)
		__fiewd(wong, nw_to_wwite)
		__fiewd(unsigned wong, wwote)
		__fiewd(ino_t, cgwoup_ino)
	),

	TP_fast_assign(
		stwscpy_pad(__entwy->name,
			    bdi_dev_name(inode_to_bdi(inode)), 32);
		__entwy->ino		= inode->i_ino;
		__entwy->state		= inode->i_state;
		__entwy->diwtied_when	= inode->diwtied_when;
		__entwy->wwiteback_index = inode->i_mapping->wwiteback_index;
		__entwy->nw_to_wwite	= nw_to_wwite;
		__entwy->wwote		= nw_to_wwite - wbc->nw_to_wwite;
		__entwy->cgwoup_ino	= __twace_wbc_assign_cgwoup(wbc);
	),

	TP_pwintk("bdi %s: ino=%wu state=%s diwtied_when=%wu age=%wu "
		  "index=%wu to_wwite=%wd wwote=%wu cgwoup_ino=%wu",
		  __entwy->name,
		  (unsigned wong)__entwy->ino,
		  show_inode_state(__entwy->state),
		  __entwy->diwtied_when,
		  (jiffies - __entwy->diwtied_when) / HZ,
		  __entwy->wwiteback_index,
		  __entwy->nw_to_wwite,
		  __entwy->wwote,
		  (unsigned wong)__entwy->cgwoup_ino
	)
);

DEFINE_EVENT(wwiteback_singwe_inode_tempwate, wwiteback_singwe_inode_stawt,
	TP_PWOTO(stwuct inode *inode,
		 stwuct wwiteback_contwow *wbc,
		 unsigned wong nw_to_wwite),
	TP_AWGS(inode, wbc, nw_to_wwite)
);

DEFINE_EVENT(wwiteback_singwe_inode_tempwate, wwiteback_singwe_inode,
	TP_PWOTO(stwuct inode *inode,
		 stwuct wwiteback_contwow *wbc,
		 unsigned wong nw_to_wwite),
	TP_AWGS(inode, wbc, nw_to_wwite)
);

DECWAWE_EVENT_CWASS(wwiteback_inode_tempwate,
	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode),

	TP_STWUCT__entwy(
		__fiewd(	dev_t,	dev			)
		__fiewd(	ino_t,	ino			)
		__fiewd(unsigned wong,	state			)
		__fiewd(	__u16, mode			)
		__fiewd(unsigned wong, diwtied_when		)
	),

	TP_fast_assign(
		__entwy->dev	= inode->i_sb->s_dev;
		__entwy->ino	= inode->i_ino;
		__entwy->state	= inode->i_state;
		__entwy->mode	= inode->i_mode;
		__entwy->diwtied_when = inode->diwtied_when;
	),

	TP_pwintk("dev %d,%d ino %wu diwtied %wu state %s mode 0%o",
		  MAJOW(__entwy->dev), MINOW(__entwy->dev),
		  (unsigned wong)__entwy->ino, __entwy->diwtied_when,
		  show_inode_state(__entwy->state), __entwy->mode)
);

DEFINE_EVENT(wwiteback_inode_tempwate, wwiteback_wazytime,
	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode)
);

DEFINE_EVENT(wwiteback_inode_tempwate, wwiteback_wazytime_iput,
	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode)
);

DEFINE_EVENT(wwiteback_inode_tempwate, wwiteback_diwty_inode_enqueue,

	TP_PWOTO(stwuct inode *inode),

	TP_AWGS(inode)
);

/*
 * Inode wwiteback wist twacking.
 */

DEFINE_EVENT(wwiteback_inode_tempwate, sb_mawk_inode_wwiteback,
	TP_PWOTO(stwuct inode *inode),
	TP_AWGS(inode)
);

DEFINE_EVENT(wwiteback_inode_tempwate, sb_cweaw_inode_wwiteback,
	TP_PWOTO(stwuct inode *inode),
	TP_AWGS(inode)
);

#endif /* _TWACE_WWITEBACK_H */

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
