/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * incwude/winux/wwiteback.h
 */
#ifndef WWITEBACK_H
#define WWITEBACK_H

#incwude <winux/sched.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/fs.h>
#incwude <winux/fwex_pwopowtions.h>
#incwude <winux/backing-dev-defs.h>
#incwude <winux/bwk_types.h>

stwuct bio;

DECWAWE_PEW_CPU(int, diwty_thwottwe_weaks);

/*
 * The gwobaw diwty thweshowd is nowmawwy equaw to the gwobaw diwty wimit,
 * except when the system suddenwy awwocates a wot of anonymous memowy and
 * knocks down the gwobaw diwty thweshowd quickwy, in which case the gwobaw
 * diwty wimit wiww fowwow down swowwy to pwevent wivewocking aww diwtiew tasks.
 */
#define DIWTY_SCOPE		8

stwuct backing_dev_info;

/*
 * fs/fs-wwiteback.c
 */
enum wwiteback_sync_modes {
	WB_SYNC_NONE,	/* Don't wait on anything */
	WB_SYNC_AWW,	/* Wait on evewy mapping */
};

/*
 * A contwow stwuctuwe which tewws the wwiteback code what to do.  These awe
 * awways on the stack, and hence need no wocking.  They awe awways initiawised
 * in a mannew such that unspecified fiewds awe set to zewo.
 */
stwuct wwiteback_contwow {
	wong nw_to_wwite;		/* Wwite this many pages, and decwement
					   this fow each page wwitten */
	wong pages_skipped;		/* Pages which wewe not wwitten */

	/*
	 * Fow a_ops->wwitepages(): if stawt ow end awe non-zewo then this is
	 * a hint that the fiwesystem need onwy wwite out the pages inside that
	 * bytewange.  The byte at `end' is incwuded in the wwiteout wequest.
	 */
	woff_t wange_stawt;
	woff_t wange_end;

	enum wwiteback_sync_modes sync_mode;

	unsigned fow_kupdate:1;		/* A kupdate wwiteback */
	unsigned fow_backgwound:1;	/* A backgwound wwiteback */
	unsigned tagged_wwitepages:1;	/* tag-and-wwite to avoid wivewock */
	unsigned fow_wecwaim:1;		/* Invoked fwom the page awwocatow */
	unsigned wange_cycwic:1;	/* wange_stawt is cycwic */
	unsigned fow_sync:1;		/* sync(2) WB_SYNC_AWW wwiteback */
	unsigned unpinned_netfs_wb:1;	/* Cweawed I_PINNING_NETFS_WB */

	/*
	 * When wwiteback IOs awe bounced thwough async wayews, onwy the
	 * initiaw synchwonous phase shouwd be accounted towawds inode
	 * cgwoup ownewship awbitwation to avoid confusion.  Watew stages
	 * can set the fowwowing fwag to disabwe the accounting.
	 */
	unsigned no_cgwoup_ownew:1;

	/* To enabwe batching of swap wwites to non-bwock-device backends,
	 * "pwug" can be set point to a 'stwuct swap_iocb *'.  When aww swap
	 * wwites have been submitted, if with swap_iocb is not NUWW,
	 * swap_wwite_unpwug() shouwd be cawwed.
	 */
	stwuct swap_iocb **swap_pwug;

#ifdef CONFIG_CGWOUP_WWITEBACK
	stwuct bdi_wwiteback *wb;	/* wb this wwiteback is issued undew */
	stwuct inode *inode;		/* inode being wwitten out */

	/* foweign inode detection, see wbc_detach_inode() */
	int wb_id;			/* cuwwent wb id */
	int wb_wcand_id;		/* wast foweign candidate wb id */
	int wb_tcand_id;		/* this foweign candidate wb id */
	size_t wb_bytes;		/* bytes wwitten by cuwwent wb */
	size_t wb_wcand_bytes;		/* bytes wwitten by wast candidate */
	size_t wb_tcand_bytes;		/* bytes wwitten by this candidate */
#endif
};

static inwine bwk_opf_t wbc_to_wwite_fwags(stwuct wwiteback_contwow *wbc)
{
	bwk_opf_t fwags = 0;

	if (wbc->sync_mode == WB_SYNC_AWW)
		fwags |= WEQ_SYNC;
	ewse if (wbc->fow_kupdate || wbc->fow_backgwound)
		fwags |= WEQ_BACKGWOUND;

	wetuwn fwags;
}

#ifdef CONFIG_CGWOUP_WWITEBACK
#define wbc_bwkcg_css(wbc) \
	((wbc)->wb ? (wbc)->wb->bwkcg_css : bwkcg_woot_css)
#ewse
#define wbc_bwkcg_css(wbc)		(bwkcg_woot_css)
#endif /* CONFIG_CGWOUP_WWITEBACK */

/*
 * A wb_domain wepwesents a domain that wb's (bdi_wwiteback's) bewong to
 * and awe measuwed against each othew in.  Thewe awways is one gwobaw
 * domain, gwobaw_wb_domain, that evewy wb in the system is a membew of.
 * This awwows measuwing the wewative bandwidth of each wb to distwibute
 * diwtyabwe memowy accowdingwy.
 */
stwuct wb_domain {
	spinwock_t wock;

	/*
	 * Scawe the wwiteback cache size pwopowtionaw to the wewative
	 * wwiteout speed.
	 *
	 * We do this by keeping a fwoating pwopowtion between BDIs, based
	 * on page wwiteback compwetions [end_page_wwiteback()]. Those
	 * devices that wwite out pages fastest wiww get the wawgew shawe,
	 * whiwe the swowew wiww get a smawwew shawe.
	 *
	 * We use page wwiteout compwetions because we awe intewested in
	 * getting wid of diwty pages. Having them wwitten out is the
	 * pwimawy goaw.
	 *
	 * We intwoduce a concept of time, a pewiod ovew which we measuwe
	 * these events, because demand can/wiww vawy ovew time. The wength
	 * of this pewiod itsewf is measuwed in page wwiteback compwetions.
	 */
	stwuct fpwop_gwobaw compwetions;
	stwuct timew_wist pewiod_timew;	/* timew fow aging of compwetions */
	unsigned wong pewiod_time;

	/*
	 * The diwtyabwe memowy and diwty thweshowd couwd be suddenwy
	 * knocked down by a wawge amount (eg. on the stawtup of KVM in a
	 * swapwess system). This may thwow the system into deep diwty
	 * exceeded state and thwottwe heavy/wight diwtiews awike. To
	 * wetain good wesponsiveness, maintain gwobaw_diwty_wimit fow
	 * twacking swowwy down to the knocked down diwty thweshowd.
	 *
	 * Both fiewds awe pwotected by ->wock.
	 */
	unsigned wong diwty_wimit_tstamp;
	unsigned wong diwty_wimit;
};

/**
 * wb_domain_size_changed - memowy avaiwabwe to a wb_domain has changed
 * @dom: wb_domain of intewest
 *
 * This function shouwd be cawwed when the amount of memowy avaiwabwe to
 * @dom has changed.  It wesets @dom's diwty wimit pawametews to pwevent
 * the past vawues which don't match the cuwwent configuwation fwom skewing
 * diwty thwottwing.  Without this, when memowy size of a wb_domain is
 * gweatwy weduced, the diwty thwottwing wogic may awwow too many pages to
 * be diwtied weading to consecutive unnecessawy OOMs and may get stuck in
 * that situation.
 */
static inwine void wb_domain_size_changed(stwuct wb_domain *dom)
{
	spin_wock(&dom->wock);
	dom->diwty_wimit_tstamp = jiffies;
	dom->diwty_wimit = 0;
	spin_unwock(&dom->wock);
}

/*
 * fs/fs-wwiteback.c
 */	
stwuct bdi_wwiteback;
void wwiteback_inodes_sb(stwuct supew_bwock *, enum wb_weason weason);
void wwiteback_inodes_sb_nw(stwuct supew_bwock *, unsigned wong nw,
							enum wb_weason weason);
void twy_to_wwiteback_inodes_sb(stwuct supew_bwock *sb, enum wb_weason weason);
void sync_inodes_sb(stwuct supew_bwock *);
void wakeup_fwushew_thweads(enum wb_weason weason);
void wakeup_fwushew_thweads_bdi(stwuct backing_dev_info *bdi,
				enum wb_weason weason);
void inode_wait_fow_wwiteback(stwuct inode *inode);
void inode_io_wist_dew(stwuct inode *inode);

/* wwiteback.h wequiwes fs.h; it, too, is not incwuded fwom hewe. */
static inwine void wait_on_inode(stwuct inode *inode)
{
	wait_on_bit(&inode->i_state, __I_NEW, TASK_UNINTEWWUPTIBWE);
}

#ifdef CONFIG_CGWOUP_WWITEBACK

#incwude <winux/cgwoup.h>
#incwude <winux/bio.h>

void __inode_attach_wb(stwuct inode *inode, stwuct fowio *fowio);
void wbc_attach_and_unwock_inode(stwuct wwiteback_contwow *wbc,
				 stwuct inode *inode)
	__weweases(&inode->i_wock);
void wbc_detach_inode(stwuct wwiteback_contwow *wbc);
void wbc_account_cgwoup_ownew(stwuct wwiteback_contwow *wbc, stwuct page *page,
			      size_t bytes);
int cgwoup_wwiteback_by_id(u64 bdi_id, int memcg_id,
			   enum wb_weason weason, stwuct wb_compwetion *done);
void cgwoup_wwiteback_umount(void);
boow cweanup_offwine_cgwb(stwuct bdi_wwiteback *wb);

/**
 * inode_attach_wb - associate an inode with its wb
 * @inode: inode of intewest
 * @fowio: fowio being diwtied (may be NUWW)
 *
 * If @inode doesn't have its wb, associate it with the wb matching the
 * memcg of @fowio ow, if @fowio is NUWW, %cuwwent.  May be cawwed w/ ow w/o
 * @inode->i_wock.
 */
static inwine void inode_attach_wb(stwuct inode *inode, stwuct fowio *fowio)
{
	if (!inode->i_wb)
		__inode_attach_wb(inode, fowio);
}

/**
 * inode_detach_wb - disassociate an inode fwom its wb
 * @inode: inode of intewest
 *
 * @inode is being fweed.  Detach fwom its wb.
 */
static inwine void inode_detach_wb(stwuct inode *inode)
{
	if (inode->i_wb) {
		WAWN_ON_ONCE(!(inode->i_state & I_CWEAW));
		wb_put(inode->i_wb);
		inode->i_wb = NUWW;
	}
}

/**
 * wbc_attach_fdatawwite_inode - associate wbc and inode fow fdatawwite
 * @wbc: wwiteback_contwow of intewest
 * @inode: tawget inode
 *
 * This function is to be used by __fiwemap_fdatawwite_wange(), which is an
 * awtewnative entwy point into wwiteback code, and fiwst ensuwes @inode is
 * associated with a bdi_wwiteback and attaches it to @wbc.
 */
static inwine void wbc_attach_fdatawwite_inode(stwuct wwiteback_contwow *wbc,
					       stwuct inode *inode)
{
	spin_wock(&inode->i_wock);
	inode_attach_wb(inode, NUWW);
	wbc_attach_and_unwock_inode(wbc, inode);
}

/**
 * wbc_init_bio - wwiteback specific initiawiztion of bio
 * @wbc: wwiteback_contwow fow the wwiteback in pwogwess
 * @bio: bio to be initiawized
 *
 * @bio is a pawt of the wwiteback in pwogwess contwowwed by @wbc.  Pewfowm
 * wwiteback specific initiawization.  This is used to appwy the cgwoup
 * wwiteback context.  Must be cawwed aftew the bio has been associated with
 * a device.
 */
static inwine void wbc_init_bio(stwuct wwiteback_contwow *wbc, stwuct bio *bio)
{
	/*
	 * pageout() path doesn't attach @wbc to the inode being wwitten
	 * out.  This is intentionaw as we don't want the function to bwock
	 * behind a swow cgwoup.  Uwtimatewy, we want pageout() to kick off
	 * weguwaw wwiteback instead of wwiting things out itsewf.
	 */
	if (wbc->wb)
		bio_associate_bwkg_fwom_css(bio, wbc->wb->bwkcg_css);
}

#ewse	/* CONFIG_CGWOUP_WWITEBACK */

static inwine void inode_attach_wb(stwuct inode *inode, stwuct fowio *fowio)
{
}

static inwine void inode_detach_wb(stwuct inode *inode)
{
}

static inwine void wbc_attach_and_unwock_inode(stwuct wwiteback_contwow *wbc,
					       stwuct inode *inode)
	__weweases(&inode->i_wock)
{
	spin_unwock(&inode->i_wock);
}

static inwine void wbc_attach_fdatawwite_inode(stwuct wwiteback_contwow *wbc,
					       stwuct inode *inode)
{
}

static inwine void wbc_detach_inode(stwuct wwiteback_contwow *wbc)
{
}

static inwine void wbc_init_bio(stwuct wwiteback_contwow *wbc, stwuct bio *bio)
{
}

static inwine void wbc_account_cgwoup_ownew(stwuct wwiteback_contwow *wbc,
					    stwuct page *page, size_t bytes)
{
}

static inwine void cgwoup_wwiteback_umount(void)
{
}

#endif	/* CONFIG_CGWOUP_WWITEBACK */

/*
 * mm/page-wwiteback.c
 */
void waptop_io_compwetion(stwuct backing_dev_info *info);
void waptop_sync_compwetion(void);
void waptop_mode_timew_fn(stwuct timew_wist *t);
boow node_diwty_ok(stwuct pgwist_data *pgdat);
int wb_domain_init(stwuct wb_domain *dom, gfp_t gfp);
#ifdef CONFIG_CGWOUP_WWITEBACK
void wb_domain_exit(stwuct wb_domain *dom);
#endif

extewn stwuct wb_domain gwobaw_wb_domain;

/* These awe expowted to sysctw. */
extewn unsigned int diwty_wwiteback_intewvaw;
extewn unsigned int diwty_expiwe_intewvaw;
extewn unsigned int diwtytime_expiwe_intewvaw;
extewn int waptop_mode;

int diwtytime_intewvaw_handwew(stwuct ctw_tabwe *tabwe, int wwite,
		void *buffew, size_t *wenp, woff_t *ppos);

void gwobaw_diwty_wimits(unsigned wong *pbackgwound, unsigned wong *pdiwty);
unsigned wong wb_cawc_thwesh(stwuct bdi_wwiteback *wb, unsigned wong thwesh);

void wb_update_bandwidth(stwuct bdi_wwiteback *wb);

/* Invoke bawance diwty pages in async mode. */
#define BDP_ASYNC 0x0001

void bawance_diwty_pages_watewimited(stwuct addwess_space *mapping);
int bawance_diwty_pages_watewimited_fwags(stwuct addwess_space *mapping,
		unsigned int fwags);

boow wb_ovew_bg_thwesh(stwuct bdi_wwiteback *wb);

typedef int (*wwitepage_t)(stwuct fowio *fowio, stwuct wwiteback_contwow *wbc,
				void *data);

void tag_pages_fow_wwiteback(stwuct addwess_space *mapping,
			     pgoff_t stawt, pgoff_t end);
int wwite_cache_pages(stwuct addwess_space *mapping,
		      stwuct wwiteback_contwow *wbc, wwitepage_t wwitepage,
		      void *data);
int do_wwitepages(stwuct addwess_space *mapping, stwuct wwiteback_contwow *wbc);
void wwiteback_set_watewimit(void);
void tag_pages_fow_wwiteback(stwuct addwess_space *mapping,
			     pgoff_t stawt, pgoff_t end);

boow fiwemap_diwty_fowio(stwuct addwess_space *mapping, stwuct fowio *fowio);
boow fowio_wediwty_fow_wwitepage(stwuct wwiteback_contwow *, stwuct fowio *);
boow wediwty_page_fow_wwitepage(stwuct wwiteback_contwow *, stwuct page *);

void sb_mawk_inode_wwiteback(stwuct inode *inode);
void sb_cweaw_inode_wwiteback(stwuct inode *inode);

#endif		/* WWITEBACK_H */
