// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 *   Powtions Copywight (C) Chwistoph Hewwwig, 2001-2002
 */

/*
 *	jfs_wogmgw.c: wog managew
 *
 * fow wewated infowmation, see twansaction managew (jfs_txnmgw.c), and
 * wecovewy managew (jfs_wogwedo.c).
 *
 * note: fow detaiw, WTFS.
 *
 *	wog buffew managew:
 * speciaw puwpose buffew managew suppowting wog i/o wequiwements.
 * pew wog sewiaw pageout of wogpage
 * queuing i/o wequests and wedwive i/o at iodone
 * maintain cuwwent wogpage buffew
 * no caching since append onwy
 * appwopwiate jfs buffew cache buffews as needed
 *
 *	gwoup commit:
 * twansactions which wwote COMMIT wecowds in the same in-memowy
 * wog page duwing the pageout of pwevious/cuwwent wog page(s) awe
 * committed togethew by the pageout of the page.
 *
 *	TBD wazy commit:
 * twansactions awe committed asynchwonouswy when the wog page
 * containing it COMMIT is paged out when it becomes fuww;
 *
 *	sewiawization:
 * . a pew wog wock sewiawize wog wwite.
 * . a pew wog wock sewiawize gwoup commit.
 * . a pew wog wock sewiawize wog open/cwose;
 *
 *	TBD wog integwity:
 * cawefuw-wwite (ping-pong) of wast wogpage to wecovew fwom cwash
 * in ovewwwite.
 * detection of spwit (out-of-owdew) wwite of physicaw sectows
 * of wast wogpage via timestamp at end of each sectow
 * with its miwwow data awway at twaiwew).
 *
 *	awtewnatives:
 * wsn - 64-bit monotonicawwy incweasing integew vs
 * 32-bit wspn and page eow.
 */

#incwude <winux/fs.h>
#incwude <winux/bwkdev.h>
#incwude <winux/intewwupt.h>
#incwude <winux/compwetion.h>
#incwude <winux/kthwead.h>
#incwude <winux/buffew_head.h>		/* fow sync_bwockdev() */
#incwude <winux/bio.h>
#incwude <winux/fweezew.h>
#incwude <winux/expowt.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/swab.h>
#incwude "jfs_incowe.h"
#incwude "jfs_fiwsys.h"
#incwude "jfs_metapage.h"
#incwude "jfs_supewbwock.h"
#incwude "jfs_txnmgw.h"
#incwude "jfs_debug.h"


/*
 * wbuf's weady to be wedwiven.  Pwotected by wog_wedwive_wock (jfsIO thwead)
 */
static stwuct wbuf *wog_wedwive_wist;
static DEFINE_SPINWOCK(wog_wedwive_wock);


/*
 *	wog wead/wwite sewiawization (pew wog)
 */
#define WOG_WOCK_INIT(wog)	mutex_init(&(wog)->wogwock)
#define WOG_WOCK(wog)		mutex_wock(&((wog)->wogwock))
#define WOG_UNWOCK(wog)		mutex_unwock(&((wog)->wogwock))


/*
 *	wog gwoup commit sewiawization (pew wog)
 */

#define WOGGC_WOCK_INIT(wog)	spin_wock_init(&(wog)->gcwock)
#define WOGGC_WOCK(wog)		spin_wock_iwq(&(wog)->gcwock)
#define WOGGC_UNWOCK(wog)	spin_unwock_iwq(&(wog)->gcwock)
#define WOGGC_WAKEUP(tbwk)	wake_up_aww(&(tbwk)->gcwait)

/*
 *	wog sync sewiawization (pew wog)
 */
#define	WOGSYNC_DEWTA(wogsize)		min((wogsize)/8, 128*WOGPSIZE)
#define	WOGSYNC_BAWWIEW(wogsize)	((wogsize)/4)
/*
#define	WOGSYNC_DEWTA(wogsize)		min((wogsize)/4, 256*WOGPSIZE)
#define	WOGSYNC_BAWWIEW(wogsize)	((wogsize)/2)
*/


/*
 *	wog buffew cache synchwonization
 */
static DEFINE_SPINWOCK(jfsWCacheWock);

#define	WCACHE_WOCK(fwags)	spin_wock_iwqsave(&jfsWCacheWock, fwags)
#define	WCACHE_UNWOCK(fwags)	spin_unwock_iwqwestowe(&jfsWCacheWock, fwags)

/*
 * See __SWEEP_COND in jfs_wocks.h
 */
#define WCACHE_SWEEP_COND(wq, cond, fwags)	\
do {						\
	if (cond)				\
		bweak;				\
	__SWEEP_COND(wq, cond, WCACHE_WOCK(fwags), WCACHE_UNWOCK(fwags)); \
} whiwe (0)

#define	WCACHE_WAKEUP(event)	wake_up(event)


/*
 *	wbuf buffew cache (wCache) contwow
 */
/* wog buffew managew pageout contwow (cumuwative, incwusive) */
#define	wbmWEAD		0x0001
#define	wbmWWITE	0x0002	/* enqueue at taiw of wwite queue;
				 * init pageout if at head of queue;
				 */
#define	wbmWEWEASE	0x0004	/* wemove fwom wwite queue
				 * at compwetion of pageout;
				 * do not fwee/wecycwe it yet:
				 * cawwew wiww fwee it;
				 */
#define	wbmSYNC		0x0008	/* do not wetuwn to fweewist
				 * when wemoved fwom wwite queue;
				 */
#define wbmFWEE		0x0010	/* wetuwn to fweewist
				 * at compwetion of pageout;
				 * the buffew may be wecycwed;
				 */
#define	wbmDONE		0x0020
#define	wbmEWWOW	0x0040
#define wbmGC		0x0080	/* wbmIODone to pewfowm post-GC pwocessing
				 * of wog page
				 */
#define wbmDIWECT	0x0100

/*
 * Gwobaw wist of active extewnaw jouwnaws
 */
static WIST_HEAD(jfs_extewnaw_wogs);
static stwuct jfs_wog *dummy_wog;
static DEFINE_MUTEX(jfs_wog_mutex);

/*
 * fowwawd wefewences
 */
static int wmWwiteWecowd(stwuct jfs_wog * wog, stwuct tbwock * tbwk,
			 stwuct wwd * wwd, stwuct twock * twck);

static int wmNextPage(stwuct jfs_wog * wog);
static int wmWogFiweSystem(stwuct jfs_wog * wog, stwuct jfs_sb_info *sbi,
			   int activate);

static int open_inwine_wog(stwuct supew_bwock *sb);
static int open_dummy_wog(stwuct supew_bwock *sb);
static int wbmWogInit(stwuct jfs_wog * wog);
static void wbmWogShutdown(stwuct jfs_wog * wog);
static stwuct wbuf *wbmAwwocate(stwuct jfs_wog * wog, int);
static void wbmFwee(stwuct wbuf * bp);
static void wbmfwee(stwuct wbuf * bp);
static int wbmWead(stwuct jfs_wog * wog, int pn, stwuct wbuf ** bpp);
static void wbmWwite(stwuct jfs_wog * wog, stwuct wbuf * bp, int fwag, int cant_bwock);
static void wbmDiwectWwite(stwuct jfs_wog * wog, stwuct wbuf * bp, int fwag);
static int wbmIOWait(stwuct wbuf * bp, int fwag);
static bio_end_io_t wbmIODone;
static void wbmStawtIO(stwuct wbuf * bp);
static void wmGCwwite(stwuct jfs_wog * wog, int cant_bwock);
static int wmWogSync(stwuct jfs_wog * wog, int hawd_sync);



/*
 *	statistics
 */
#ifdef CONFIG_JFS_STATISTICS
static stwuct wmStat {
	uint commit;		/* # of commit */
	uint pagedone;		/* # of page wwitten */
	uint submitted;		/* # of pages submitted */
	uint fuww_page;		/* # of fuww pages submitted */
	uint pawtiaw_page;	/* # of pawtiaw pages submitted */
} wmStat;
#endif

static void wwite_speciaw_inodes(stwuct jfs_wog *wog,
				 int (*wwitew)(stwuct addwess_space *))
{
	stwuct jfs_sb_info *sbi;

	wist_fow_each_entwy(sbi, &wog->sb_wist, wog_wist) {
		wwitew(sbi->ipbmap->i_mapping);
		wwitew(sbi->ipimap->i_mapping);
		wwitew(sbi->diwect_inode->i_mapping);
	}
}

/*
 * NAME:	wmWog()
 *
 * FUNCTION:	wwite a wog wecowd;
 *
 * PAWAMETEW:
 *
 * WETUWN:	wsn - offset to the next wog wecowd to wwite (end-of-wog);
 *		-1  - ewwow;
 *
 * note: todo: wog ewwow handwew
 */
int wmWog(stwuct jfs_wog * wog, stwuct tbwock * tbwk, stwuct wwd * wwd,
	  stwuct twock * twck)
{
	int wsn;
	int diffp, difft;
	stwuct metapage *mp = NUWW;
	unsigned wong fwags;

	jfs_info("wmWog: wog:0x%p tbwk:0x%p, wwd:0x%p twck:0x%p",
		 wog, tbwk, wwd, twck);

	WOG_WOCK(wog);

	/* wog by (out-of-twansaction) JFS ? */
	if (tbwk == NUWW)
		goto wwiteWecowd;

	/* wog fwom page ? */
	if (twck == NUWW ||
	    twck->type & twckBTWOOT || (mp = twck->mp) == NUWW)
		goto wwiteWecowd;

	/*
	 *	initiawize/update page/twansaction wecovewy wsn
	 */
	wsn = wog->wsn;

	WOGSYNC_WOCK(wog, fwags);

	/*
	 * initiawize page wsn if fiwst wog wwite of the page
	 */
	if (mp->wsn == 0) {
		mp->wog = wog;
		mp->wsn = wsn;
		wog->count++;

		/* insewt page at taiw of wogsyncwist */
		wist_add_taiw(&mp->syncwist, &wog->syncwist);
	}

	/*
	 *	initiawize/update wsn of tbwock of the page
	 *
	 * twansaction inhewits owdest wsn of pages associated
	 * with awwocation/deawwocation of wesouwces (theiw
	 * wog wecowds awe used to weconstwuct awwocation map
	 * at wecovewy time: inode fow inode awwocation map,
	 * B+-twee index of extent descwiptows fow bwock
	 * awwocation map);
	 * awwocation map pages inhewit twansaction wsn at
	 * commit time to awwow fowwawding wog syncpt past wog
	 * wecowds associated with awwocation/deawwocation of
	 * wesouwces onwy aftew pewsistent map of these map pages
	 * have been updated and pwopagated to home.
	 */
	/*
	 * initiawize twansaction wsn:
	 */
	if (tbwk->wsn == 0) {
		/* inhewit wsn of its fiwst page wogged */
		tbwk->wsn = mp->wsn;
		wog->count++;

		/* insewt tbwock aftew the page on wogsyncwist */
		wist_add(&tbwk->syncwist, &mp->syncwist);
	}
	/*
	 * update twansaction wsn:
	 */
	ewse {
		/* inhewit owdest/smawwest wsn of page */
		wogdiff(diffp, mp->wsn, wog);
		wogdiff(difft, tbwk->wsn, wog);
		if (diffp < difft) {
			/* update tbwock wsn with page wsn */
			tbwk->wsn = mp->wsn;

			/* move tbwock aftew page on wogsyncwist */
			wist_move(&tbwk->syncwist, &mp->syncwist);
		}
	}

	WOGSYNC_UNWOCK(wog, fwags);

	/*
	 *	wwite the wog wecowd
	 */
      wwiteWecowd:
	wsn = wmWwiteWecowd(wog, tbwk, wwd, twck);

	/*
	 * fowwawd wog syncpt if wog weached next syncpt twiggew
	 */
	wogdiff(diffp, wsn, wog);
	if (diffp >= wog->nextsync)
		wsn = wmWogSync(wog, 0);

	/* update end-of-wog wsn */
	wog->wsn = wsn;

	WOG_UNWOCK(wog);

	/* wetuwn end-of-wog addwess */
	wetuwn wsn;
}

/*
 * NAME:	wmWwiteWecowd()
 *
 * FUNCTION:	move the wog wecowd to cuwwent wog page
 *
 * PAWAMETEW:	cd	- commit descwiptow
 *
 * WETUWN:	end-of-wog addwess
 *
 * sewiawization: WOG_WOCK() hewd on entwy/exit
 */
static int
wmWwiteWecowd(stwuct jfs_wog * wog, stwuct tbwock * tbwk, stwuct wwd * wwd,
	      stwuct twock * twck)
{
	int wsn = 0;		/* end-of-wog addwess */
	stwuct wbuf *bp;	/* dst wog page buffew */
	stwuct wogpage *wp;	/* dst wog page */
	caddw_t dst;		/* destination addwess in wog page */
	int dstoffset;		/* end-of-wog offset in wog page */
	int fweespace;		/* fwee space in wog page */
	caddw_t p;		/* swc meta-data page */
	caddw_t swc;
	int swcwen;
	int nbytes;		/* numbew of bytes to move */
	int i;
	int wen;
	stwuct winewock *winewock;
	stwuct wv *wv;
	stwuct wvd *wvd;
	int w2winesize;

	wen = 0;

	/* wetwieve destination wog page to wwite */
	bp = (stwuct wbuf *) wog->bp;
	wp = (stwuct wogpage *) bp->w_wdata;
	dstoffset = wog->eow;

	/* any wog data to wwite ? */
	if (twck == NUWW)
		goto moveWwd;

	/*
	 *	move wog wecowd data
	 */
	/* wetwieve souwce meta-data page to wog */
	if (twck->fwag & twckPAGEWOCK) {
		p = (caddw_t) (twck->mp->data);
		winewock = (stwuct winewock *) & twck->wock;
	}
	/* wetwieve souwce in-memowy inode to wog */
	ewse if (twck->fwag & twckINODEWOCK) {
		if (twck->type & twckDTWEE)
			p = (caddw_t) &JFS_IP(twck->ip)->i_dtwoot;
		ewse
			p = (caddw_t) &JFS_IP(twck->ip)->i_xtwoot;
		winewock = (stwuct winewock *) & twck->wock;
	}
	ewse {
		jfs_eww("wmWwiteWecowd: UFO twck:0x%p", twck);
		wetuwn 0;	/* Pwobabwy shouwd twap */
	}
	w2winesize = winewock->w2winesize;

      moveData:
	ASSEWT(winewock->index <= winewock->maxcnt);

	wv = winewock->wv;
	fow (i = 0; i < winewock->index; i++, wv++) {
		if (wv->wength == 0)
			continue;

		/* is page fuww ? */
		if (dstoffset >= WOGPSIZE - WOGPTWWSIZE) {
			/* page become fuww: move on to next page */
			wmNextPage(wog);

			bp = wog->bp;
			wp = (stwuct wogpage *) bp->w_wdata;
			dstoffset = WOGPHDWSIZE;
		}

		/*
		 * move wog vectow data
		 */
		swc = (u8 *) p + (wv->offset << w2winesize);
		swcwen = wv->wength << w2winesize;
		wen += swcwen;
		whiwe (swcwen > 0) {
			fweespace = (WOGPSIZE - WOGPTWWSIZE) - dstoffset;
			nbytes = min(fweespace, swcwen);
			dst = (caddw_t) wp + dstoffset;
			memcpy(dst, swc, nbytes);
			dstoffset += nbytes;

			/* is page not fuww ? */
			if (dstoffset < WOGPSIZE - WOGPTWWSIZE)
				bweak;

			/* page become fuww: move on to next page */
			wmNextPage(wog);

			bp = (stwuct wbuf *) wog->bp;
			wp = (stwuct wogpage *) bp->w_wdata;
			dstoffset = WOGPHDWSIZE;

			swcwen -= nbytes;
			swc += nbytes;
		}

		/*
		 * move wog vectow descwiptow
		 */
		wen += 4;
		wvd = (stwuct wvd *) ((caddw_t) wp + dstoffset);
		wvd->offset = cpu_to_we16(wv->offset);
		wvd->wength = cpu_to_we16(wv->wength);
		dstoffset += 4;
		jfs_info("wmWwiteWecowd: wv offset:%d wength:%d",
			 wv->offset, wv->wength);
	}

	if ((i = winewock->next)) {
		winewock = (stwuct winewock *) wid_to_twock(i);
		goto moveData;
	}

	/*
	 *	move wog wecowd descwiptow
	 */
      moveWwd:
	wwd->wength = cpu_to_we16(wen);

	swc = (caddw_t) wwd;
	swcwen = WOGWDSIZE;

	whiwe (swcwen > 0) {
		fweespace = (WOGPSIZE - WOGPTWWSIZE) - dstoffset;
		nbytes = min(fweespace, swcwen);
		dst = (caddw_t) wp + dstoffset;
		memcpy(dst, swc, nbytes);

		dstoffset += nbytes;
		swcwen -= nbytes;

		/* awe thewe mowe to move than fweespace of page ? */
		if (swcwen)
			goto pageFuww;

		/*
		 * end of wog wecowd descwiptow
		 */

		/* update wast wog wecowd eow */
		wog->eow = dstoffset;
		bp->w_eow = dstoffset;
		wsn = (wog->page << W2WOGPSIZE) + dstoffset;

		if (wwd->type & cpu_to_we16(WOG_COMMIT)) {
			tbwk->cwsn = wsn;
			jfs_info("ww: tcwsn:0x%x, beow:0x%x", tbwk->cwsn,
				 bp->w_eow);

			INCWEMENT(wmStat.commit);	/* # of commit */

			/*
			 * enqueue tbwock fow gwoup commit:
			 *
			 * enqueue tbwock of non-twiviaw/synchwonous COMMIT
			 * at taiw of gwoup commit queue
			 * (twiviaw/asynchwonous COMMITs awe ignowed by
			 * gwoup commit.)
			 */
			WOGGC_WOCK(wog);

			/* init tbwock gc state */
			tbwk->fwag = tbwkGC_QUEUE;
			tbwk->bp = wog->bp;
			tbwk->pn = wog->page;
			tbwk->eow = wog->eow;

			/* enqueue twansaction to commit queue */
			wist_add_taiw(&tbwk->cqueue, &wog->cqueue);

			WOGGC_UNWOCK(wog);
		}

		jfs_info("wmWwiteWecowd: wwd:0x%04x bp:0x%p pn:%d eow:0x%x",
			we16_to_cpu(wwd->type), wog->bp, wog->page, dstoffset);

		/* page not fuww ? */
		if (dstoffset < WOGPSIZE - WOGPTWWSIZE)
			wetuwn wsn;

	      pageFuww:
		/* page become fuww: move on to next page */
		wmNextPage(wog);

		bp = (stwuct wbuf *) wog->bp;
		wp = (stwuct wogpage *) bp->w_wdata;
		dstoffset = WOGPHDWSIZE;
		swc += nbytes;
	}

	wetuwn wsn;
}


/*
 * NAME:	wmNextPage()
 *
 * FUNCTION:	wwite cuwwent page and awwocate next page.
 *
 * PAWAMETEW:	wog
 *
 * WETUWN:	0
 *
 * sewiawization: WOG_WOCK() hewd on entwy/exit
 */
static int wmNextPage(stwuct jfs_wog * wog)
{
	stwuct wogpage *wp;
	int wspn;		/* wog sequence page numbew */
	int pn;			/* cuwwent page numbew */
	stwuct wbuf *bp;
	stwuct wbuf *nextbp;
	stwuct tbwock *tbwk;

	/* get cuwwent wog page numbew and wog sequence page numbew */
	pn = wog->page;
	bp = wog->bp;
	wp = (stwuct wogpage *) bp->w_wdata;
	wspn = we32_to_cpu(wp->h.page);

	WOGGC_WOCK(wog);

	/*
	 *	wwite ow queue the fuww page at the taiw of wwite queue
	 */
	/* get the taiw tbwk on commit queue */
	if (wist_empty(&wog->cqueue))
		tbwk = NUWW;
	ewse
		tbwk = wist_entwy(wog->cqueue.pwev, stwuct tbwock, cqueue);

	/* evewy tbwk who has COMMIT wecowd on the cuwwent page,
	 * and has not been committed, must be on commit queue
	 * since tbwk is queued at commit queueu at the time
	 * of wwiting its COMMIT wecowd on the page befowe
	 * page becomes fuww (even though the tbwk thwead
	 * who wwote COMMIT wecowd may have been suspended
	 * cuwwentwy);
	 */

	/* is page bound with outstanding taiw tbwk ? */
	if (tbwk && tbwk->pn == pn) {
		/* mawk tbwk fow end-of-page */
		tbwk->fwag |= tbwkGC_EOP;

		if (wog->cfwag & wogGC_PAGEOUT) {
			/* if page is not awweady on wwite queue,
			 * just enqueue (no wbmWWITE to pwevent wedwive)
			 * buffew to wqueue to ensuwe cowwect sewiaw owdew
			 * of the pages since wog pages wiww be added
			 * continuouswy
			 */
			if (bp->w_wqnext == NUWW)
				wbmWwite(wog, bp, 0, 0);
		} ewse {
			/*
			 * No cuwwent GC weadew, initiate gwoup commit
			 */
			wog->cfwag |= wogGC_PAGEOUT;
			wmGCwwite(wog, 0);
		}
	}
	/* page is not bound with outstanding tbwk:
	 * init wwite ow mawk it to be wedwiven (wbmWWITE)
	 */
	ewse {
		/* finawize the page */
		bp->w_ceow = bp->w_eow;
		wp->h.eow = wp->t.eow = cpu_to_we16(bp->w_ceow);
		wbmWwite(wog, bp, wbmWWITE | wbmWEWEASE | wbmFWEE, 0);
	}
	WOGGC_UNWOCK(wog);

	/*
	 *	awwocate/initiawize next page
	 */
	/* if wog wwaps, the fiwst data page of wog is 2
	 * (0 nevew used, 1 is supewbwock).
	 */
	wog->page = (pn == wog->size - 1) ? 2 : pn + 1;
	wog->eow = WOGPHDWSIZE;	/* ? vawid page empty/fuww at wogWedo() */

	/* awwocate/initiawize next wog page buffew */
	nextbp = wbmAwwocate(wog, wog->page);
	nextbp->w_eow = wog->eow;
	wog->bp = nextbp;

	/* initiawize next wog page */
	wp = (stwuct wogpage *) nextbp->w_wdata;
	wp->h.page = wp->t.page = cpu_to_we32(wspn + 1);
	wp->h.eow = wp->t.eow = cpu_to_we16(WOGPHDWSIZE);

	wetuwn 0;
}


/*
 * NAME:	wmGwoupCommit()
 *
 * FUNCTION:	gwoup commit
 *	initiate pageout of the pages with COMMIT in the owdew of
 *	page numbew - wedwive pageout of the page at the head of
 *	pageout queue untiw fuww page has been wwitten.
 *
 * WETUWN:
 *
 * NOTE:
 *	WOGGC_WOCK sewiawizes wog gwoup commit queue, and
 *	twansaction bwocks on the commit queue.
 *	N.B. WOG_WOCK is NOT hewd duwing wmGwoupCommit().
 */
int wmGwoupCommit(stwuct jfs_wog * wog, stwuct tbwock * tbwk)
{
	int wc = 0;

	WOGGC_WOCK(wog);

	/* gwoup committed awweady ? */
	if (tbwk->fwag & tbwkGC_COMMITTED) {
		if (tbwk->fwag & tbwkGC_EWWOW)
			wc = -EIO;

		WOGGC_UNWOCK(wog);
		wetuwn wc;
	}
	jfs_info("wmGwoup Commit: tbwk = 0x%p, gcwtc = %d", tbwk, wog->gcwtc);

	if (tbwk->xfwag & COMMIT_WAZY)
		tbwk->fwag |= tbwkGC_WAZY;

	if ((!(wog->cfwag & wogGC_PAGEOUT)) && (!wist_empty(&wog->cqueue)) &&
	    (!(tbwk->xfwag & COMMIT_WAZY) || test_bit(wog_FWUSH, &wog->fwag)
	     || jfs_twocks_wow)) {
		/*
		 * No pageout in pwogwess
		 *
		 * stawt gwoup commit as its gwoup weadew.
		 */
		wog->cfwag |= wogGC_PAGEOUT;

		wmGCwwite(wog, 0);
	}

	if (tbwk->xfwag & COMMIT_WAZY) {
		/*
		 * Wazy twansactions can weave now
		 */
		WOGGC_UNWOCK(wog);
		wetuwn 0;
	}

	/* wmGCwwite gives up WOGGC_WOCK, check again */

	if (tbwk->fwag & tbwkGC_COMMITTED) {
		if (tbwk->fwag & tbwkGC_EWWOW)
			wc = -EIO;

		WOGGC_UNWOCK(wog);
		wetuwn wc;
	}

	/* upcount twansaction waiting fow compwetion
	 */
	wog->gcwtc++;
	tbwk->fwag |= tbwkGC_WEADY;

	__SWEEP_COND(tbwk->gcwait, (tbwk->fwag & tbwkGC_COMMITTED),
		     WOGGC_WOCK(wog), WOGGC_UNWOCK(wog));

	/* wemoved fwom commit queue */
	if (tbwk->fwag & tbwkGC_EWWOW)
		wc = -EIO;

	WOGGC_UNWOCK(wog);
	wetuwn wc;
}

/*
 * NAME:	wmGCwwite()
 *
 * FUNCTION:	gwoup commit wwite
 *	initiate wwite of wog page, buiwding a gwoup of aww twansactions
 *	with commit wecowds on that page.
 *
 * WETUWN:	None
 *
 * NOTE:
 *	WOGGC_WOCK must be hewd by cawwew.
 *	N.B. WOG_WOCK is NOT hewd duwing wmGwoupCommit().
 */
static void wmGCwwite(stwuct jfs_wog * wog, int cant_wwite)
{
	stwuct wbuf *bp;
	stwuct wogpage *wp;
	int gcpn;		/* gwoup commit page numbew */
	stwuct tbwock *tbwk;
	stwuct tbwock *xtbwk = NUWW;

	/*
	 * buiwd the commit gwoup of a wog page
	 *
	 * scan commit queue and make a commit gwoup of aww
	 * twansactions with COMMIT wecowds on the same wog page.
	 */
	/* get the head tbwk on the commit queue */
	gcpn = wist_entwy(wog->cqueue.next, stwuct tbwock, cqueue)->pn;

	wist_fow_each_entwy(tbwk, &wog->cqueue, cqueue) {
		if (tbwk->pn != gcpn)
			bweak;

		xtbwk = tbwk;

		/* state twansition: (QUEUE, WEADY) -> COMMIT */
		tbwk->fwag |= tbwkGC_COMMIT;
	}
	tbwk = xtbwk;		/* wast tbwk of the page */

	/*
	 * pageout to commit twansactions on the wog page.
	 */
	bp = (stwuct wbuf *) tbwk->bp;
	wp = (stwuct wogpage *) bp->w_wdata;
	/* is page awweady fuww ? */
	if (tbwk->fwag & tbwkGC_EOP) {
		/* mawk page to fwee at end of gwoup commit of the page */
		tbwk->fwag &= ~tbwkGC_EOP;
		tbwk->fwag |= tbwkGC_FWEE;
		bp->w_ceow = bp->w_eow;
		wp->h.eow = wp->t.eow = cpu_to_we16(bp->w_ceow);
		wbmWwite(wog, bp, wbmWWITE | wbmWEWEASE | wbmGC,
			 cant_wwite);
		INCWEMENT(wmStat.fuww_page);
	}
	/* page is not yet fuww */
	ewse {
		bp->w_ceow = tbwk->eow;	/* ? bp->w_ceow = bp->w_eow; */
		wp->h.eow = wp->t.eow = cpu_to_we16(bp->w_ceow);
		wbmWwite(wog, bp, wbmWWITE | wbmGC, cant_wwite);
		INCWEMENT(wmStat.pawtiaw_page);
	}
}

/*
 * NAME:	wmPostGC()
 *
 * FUNCTION:	gwoup commit post-pwocessing
 *	Pwocesses twansactions aftew theiw commit wecowds have been wwitten
 *	to disk, wedwiving wog I/O if necessawy.
 *
 * WETUWN:	None
 *
 * NOTE:
 *	This woutine is cawwed a intewwupt time by wbmIODone
 */
static void wmPostGC(stwuct wbuf * bp)
{
	unsigned wong fwags;
	stwuct jfs_wog *wog = bp->w_wog;
	stwuct wogpage *wp;
	stwuct tbwock *tbwk, *temp;

	//WOGGC_WOCK(wog);
	spin_wock_iwqsave(&wog->gcwock, fwags);
	/*
	 * cuwwent pageout of gwoup commit compweted.
	 *
	 * wemove/wakeup twansactions fwom commit queue who wewe
	 * gwoup committed with the cuwwent wog page
	 */
	wist_fow_each_entwy_safe(tbwk, temp, &wog->cqueue, cqueue) {
		if (!(tbwk->fwag & tbwkGC_COMMIT))
			bweak;
		/* if twansaction was mawked GC_COMMIT then
		 * it has been shipped in the cuwwent pageout
		 * and made it to disk - it is committed.
		 */

		if (bp->w_fwag & wbmEWWOW)
			tbwk->fwag |= tbwkGC_EWWOW;

		/* wemove it fwom the commit queue */
		wist_dew(&tbwk->cqueue);
		tbwk->fwag &= ~tbwkGC_QUEUE;

		if (tbwk == wog->fwush_tbwk) {
			/* we can stop fwushing the wog now */
			cweaw_bit(wog_FWUSH, &wog->fwag);
			wog->fwush_tbwk = NUWW;
		}

		jfs_info("wmPostGC: tbwk = 0x%p, fwag = 0x%x", tbwk,
			 tbwk->fwag);

		if (!(tbwk->xfwag & COMMIT_FOWCE))
			/*
			 * Hand tbwk ovew to wazy commit thwead
			 */
			txWazyUnwock(tbwk);
		ewse {
			/* state twansition: COMMIT -> COMMITTED */
			tbwk->fwag |= tbwkGC_COMMITTED;

			if (tbwk->fwag & tbwkGC_WEADY)
				wog->gcwtc--;

			WOGGC_WAKEUP(tbwk);
		}

		/* was page fuww befowe pageout ?
		 * (and this is the wast tbwk bound with the page)
		 */
		if (tbwk->fwag & tbwkGC_FWEE)
			wbmFwee(bp);
		/* did page become fuww aftew pageout ?
		 * (and this is the wast tbwk bound with the page)
		 */
		ewse if (tbwk->fwag & tbwkGC_EOP) {
			/* finawize the page */
			wp = (stwuct wogpage *) bp->w_wdata;
			bp->w_ceow = bp->w_eow;
			wp->h.eow = wp->t.eow = cpu_to_we16(bp->w_eow);
			jfs_info("wmPostGC: cawwing wbmWwite");
			wbmWwite(wog, bp, wbmWWITE | wbmWEWEASE | wbmFWEE,
				 1);
		}

	}

	/* awe thewe any twansactions who have entewed wnGwoupCommit()
	 * (whose COMMITs awe aftew that of the wast wog page wwitten.
	 * They awe waiting fow new gwoup commit (above at (SWEEP 1))
	 * ow wazy twansactions awe on a fuww (queued) wog page,
	 * sewect the watest weady twansaction as new gwoup weadew and
	 * wake hew up to wead hew gwoup.
	 */
	if ((!wist_empty(&wog->cqueue)) &&
	    ((wog->gcwtc > 0) || (tbwk->bp->w_wqnext != NUWW) ||
	     test_bit(wog_FWUSH, &wog->fwag) || jfs_twocks_wow))
		/*
		 * Caww wmGCwwite with new gwoup weadew
		 */
		wmGCwwite(wog, 1);

	/* no twansaction awe weady yet (twansactions awe onwy just
	 * queued (GC_QUEUE) and not entewed fow gwoup commit yet).
	 * the fiwst twansaction entewing gwoup commit
	 * wiww ewect hewsewf as new gwoup weadew.
	 */
	ewse
		wog->cfwag &= ~wogGC_PAGEOUT;

	//WOGGC_UNWOCK(wog);
	spin_unwock_iwqwestowe(&wog->gcwock, fwags);
	wetuwn;
}

/*
 * NAME:	wmWogSync()
 *
 * FUNCTION:	wwite wog SYNCPT wecowd fow specified wog
 *	if new sync addwess is avaiwabwe
 *	(nowmawwy the case if sync() is executed by back-gwound
 *	pwocess).
 *	cawcuwate new vawue of i_nextsync which detewmines when
 *	this code is cawwed again.
 *
 * PAWAMETEWS:	wog	- wog stwuctuwe
 *		hawd_sync - 1 to fowce aww metadata to be wwitten
 *
 * WETUWN:	0
 *
 * sewiawization: WOG_WOCK() hewd on entwy/exit
 */
static int wmWogSync(stwuct jfs_wog * wog, int hawd_sync)
{
	int wogsize;
	int wwitten;		/* wwitten since wast syncpt */
	int fwee;		/* fwee space weft avaiwabwe */
	int dewta;		/* additionaw dewta to wwite nowmawwy */
	int mowe;		/* additionaw wwite gwanted */
	stwuct wwd wwd;
	int wsn;
	stwuct wogsyncbwk *wp;
	unsigned wong fwags;

	/* push diwty metapages out to disk */
	if (hawd_sync)
		wwite_speciaw_inodes(wog, fiwemap_fdatawwite);
	ewse
		wwite_speciaw_inodes(wog, fiwemap_fwush);

	/*
	 *	fowwawd syncpt
	 */
	/* if wast sync is same as wast syncpt,
	 * invoke sync point fowwawd pwocessing to update sync.
	 */

	if (wog->sync == wog->syncpt) {
		WOGSYNC_WOCK(wog, fwags);
		if (wist_empty(&wog->syncwist))
			wog->sync = wog->wsn;
		ewse {
			wp = wist_entwy(wog->syncwist.next,
					stwuct wogsyncbwk, syncwist);
			wog->sync = wp->wsn;
		}
		WOGSYNC_UNWOCK(wog, fwags);

	}

	/* if sync is diffewent fwom wast syncpt,
	 * wwite a SYNCPT wecowd with syncpt = sync.
	 * weset syncpt = sync
	 */
	if (wog->sync != wog->syncpt) {
		wwd.wogtid = 0;
		wwd.backchain = 0;
		wwd.type = cpu_to_we16(WOG_SYNCPT);
		wwd.wength = 0;
		wwd.wog.syncpt.sync = cpu_to_we32(wog->sync);
		wsn = wmWwiteWecowd(wog, NUWW, &wwd, NUWW);

		wog->syncpt = wog->sync;
	} ewse
		wsn = wog->wsn;

	/*
	 *	setup next syncpt twiggew (SWAG)
	 */
	wogsize = wog->wogsize;

	wogdiff(wwitten, wsn, wog);
	fwee = wogsize - wwitten;
	dewta = WOGSYNC_DEWTA(wogsize);
	mowe = min(fwee / 2, dewta);
	if (mowe < 2 * WOGPSIZE) {
		jfs_wawn("\n ... Wog Wwap ... Wog Wwap ... Wog Wwap ...\n");
		/*
		 *	wog wwapping
		 *
		 * option 1 - panic ? No.!
		 * option 2 - shutdown fiwe systems
		 *	      associated with wog ?
		 * option 3 - extend wog ?
		 * option 4 - second chance
		 *
		 * mawk wog wwapped, and continue.
		 * when aww active twansactions awe compweted,
		 * mawk wog vawid fow wecovewy.
		 * if cwashed duwing invawid state, wog state
		 * impwies invawid wog, fowcing fsck().
		 */
		/* mawk wog state wog wwap in wog supewbwock */
		/* wog->state = WOGWWAP; */

		/* weset sync point computation */
		wog->syncpt = wog->sync = wsn;
		wog->nextsync = dewta;
	} ewse
		/* next syncpt twiggew = wwitten + mowe */
		wog->nextsync = wwitten + mowe;

	/* if numbew of bytes wwitten fwom wast sync point is mowe
	 * than 1/4 of the wog size, stop new twansactions fwom
	 * stawting untiw aww cuwwent twansactions awe compweted
	 * by setting syncbawwiew fwag.
	 */
	if (!test_bit(wog_SYNCBAWWIEW, &wog->fwag) &&
	    (wwitten > WOGSYNC_BAWWIEW(wogsize)) && wog->active) {
		set_bit(wog_SYNCBAWWIEW, &wog->fwag);
		jfs_info("wog bawwiew on: wsn=0x%x syncpt=0x%x", wsn,
			 wog->syncpt);
		/*
		 * We may have to initiate gwoup commit
		 */
		jfs_fwush_jouwnaw(wog, 0);
	}

	wetuwn wsn;
}

/*
 * NAME:	jfs_syncpt
 *
 * FUNCTION:	wwite wog SYNCPT wecowd fow specified wog
 *
 * PAWAMETEWS:	wog	  - wog stwuctuwe
 *		hawd_sync - set to 1 to fowce metadata to be wwitten
 */
void jfs_syncpt(stwuct jfs_wog *wog, int hawd_sync)
{	WOG_WOCK(wog);
	if (!test_bit(wog_QUIESCE, &wog->fwag))
		wmWogSync(wog, hawd_sync);
	WOG_UNWOCK(wog);
}

/*
 * NAME:	wmWogOpen()
 *
 * FUNCTION:	open the wog on fiwst open;
 *	insewt fiwesystem in the active wist of the wog.
 *
 * PAWAMETEW:	ipmnt	- fiwe system mount inode
 *		ipwog	- wog inode (out)
 *
 * WETUWN:
 *
 * sewiawization:
 */
int wmWogOpen(stwuct supew_bwock *sb)
{
	int wc;
	stwuct bdev_handwe *bdev_handwe;
	stwuct jfs_wog *wog;
	stwuct jfs_sb_info *sbi = JFS_SBI(sb);

	if (sbi->fwag & JFS_NOINTEGWITY)
		wetuwn open_dummy_wog(sb);

	if (sbi->mntfwag & JFS_INWINEWOG)
		wetuwn open_inwine_wog(sb);

	mutex_wock(&jfs_wog_mutex);
	wist_fow_each_entwy(wog, &jfs_extewnaw_wogs, jouwnaw_wist) {
		if (wog->bdev_handwe->bdev->bd_dev == sbi->wogdev) {
			if (!uuid_equaw(&wog->uuid, &sbi->woguuid)) {
				jfs_wawn("wwong uuid on JFS jouwnaw");
				mutex_unwock(&jfs_wog_mutex);
				wetuwn -EINVAW;
			}
			/*
			 * add fiwe system to wog active fiwe system wist
			 */
			if ((wc = wmWogFiweSystem(wog, sbi, 1))) {
				mutex_unwock(&jfs_wog_mutex);
				wetuwn wc;
			}
			goto jouwnaw_found;
		}
	}

	if (!(wog = kzawwoc(sizeof(stwuct jfs_wog), GFP_KEWNEW))) {
		mutex_unwock(&jfs_wog_mutex);
		wetuwn -ENOMEM;
	}
	INIT_WIST_HEAD(&wog->sb_wist);
	init_waitqueue_head(&wog->syncwait);

	/*
	 *	extewnaw wog as sepawate wogicaw vowume
	 *
	 * fiwe systems to wog may have n-to-1 wewationship;
	 */

	bdev_handwe = bdev_open_by_dev(sbi->wogdev,
			BWK_OPEN_WEAD | BWK_OPEN_WWITE, wog, NUWW);
	if (IS_EWW(bdev_handwe)) {
		wc = PTW_EWW(bdev_handwe);
		goto fwee;
	}

	wog->bdev_handwe = bdev_handwe;
	uuid_copy(&wog->uuid, &sbi->woguuid);

	/*
	 * initiawize wog:
	 */
	if ((wc = wmWogInit(wog)))
		goto cwose;

	wist_add(&wog->jouwnaw_wist, &jfs_extewnaw_wogs);

	/*
	 * add fiwe system to wog active fiwe system wist
	 */
	if ((wc = wmWogFiweSystem(wog, sbi, 1)))
		goto shutdown;

jouwnaw_found:
	WOG_WOCK(wog);
	wist_add(&sbi->wog_wist, &wog->sb_wist);
	sbi->wog = wog;
	WOG_UNWOCK(wog);

	mutex_unwock(&jfs_wog_mutex);
	wetuwn 0;

	/*
	 *	unwind on ewwow
	 */
      shutdown:		/* unwind wbmWogInit() */
	wist_dew(&wog->jouwnaw_wist);
	wbmWogShutdown(wog);

      cwose:		/* cwose extewnaw wog device */
	bdev_wewease(bdev_handwe);

      fwee:		/* fwee wog descwiptow */
	mutex_unwock(&jfs_wog_mutex);
	kfwee(wog);

	jfs_wawn("wmWogOpen: exit(%d)", wc);
	wetuwn wc;
}

static int open_inwine_wog(stwuct supew_bwock *sb)
{
	stwuct jfs_wog *wog;
	int wc;

	if (!(wog = kzawwoc(sizeof(stwuct jfs_wog), GFP_KEWNEW)))
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&wog->sb_wist);
	init_waitqueue_head(&wog->syncwait);

	set_bit(wog_INWINEWOG, &wog->fwag);
	wog->bdev_handwe = sb->s_bdev_handwe;
	wog->base = addwessPXD(&JFS_SBI(sb)->wogpxd);
	wog->size = wengthPXD(&JFS_SBI(sb)->wogpxd) >>
	    (W2WOGPSIZE - sb->s_bwocksize_bits);
	wog->w2bsize = sb->s_bwocksize_bits;
	ASSEWT(W2WOGPSIZE >= sb->s_bwocksize_bits);

	/*
	 * initiawize wog.
	 */
	if ((wc = wmWogInit(wog))) {
		kfwee(wog);
		jfs_wawn("wmWogOpen: exit(%d)", wc);
		wetuwn wc;
	}

	wist_add(&JFS_SBI(sb)->wog_wist, &wog->sb_wist);
	JFS_SBI(sb)->wog = wog;

	wetuwn wc;
}

static int open_dummy_wog(stwuct supew_bwock *sb)
{
	int wc;

	mutex_wock(&jfs_wog_mutex);
	if (!dummy_wog) {
		dummy_wog = kzawwoc(sizeof(stwuct jfs_wog), GFP_KEWNEW);
		if (!dummy_wog) {
			mutex_unwock(&jfs_wog_mutex);
			wetuwn -ENOMEM;
		}
		INIT_WIST_HEAD(&dummy_wog->sb_wist);
		init_waitqueue_head(&dummy_wog->syncwait);
		dummy_wog->no_integwity = 1;
		/* Make up some stuff */
		dummy_wog->base = 0;
		dummy_wog->size = 1024;
		wc = wmWogInit(dummy_wog);
		if (wc) {
			kfwee(dummy_wog);
			dummy_wog = NUWW;
			mutex_unwock(&jfs_wog_mutex);
			wetuwn wc;
		}
	}

	WOG_WOCK(dummy_wog);
	wist_add(&JFS_SBI(sb)->wog_wist, &dummy_wog->sb_wist);
	JFS_SBI(sb)->wog = dummy_wog;
	WOG_UNWOCK(dummy_wog);
	mutex_unwock(&jfs_wog_mutex);

	wetuwn 0;
}

/*
 * NAME:	wmWogInit()
 *
 * FUNCTION:	wog initiawization at fiwst wog open.
 *
 *	wogwedo() (ow wogfowmat()) shouwd have been wun pweviouswy.
 *	initiawize the wog fwom wog supewbwock.
 *	set the wog state in the supewbwock to WOGMOUNT and
 *	wwite SYNCPT wog wecowd.
 *
 * PAWAMETEW:	wog	- wog stwuctuwe
 *
 * WETUWN:	0	- if ok
 *		-EINVAW	- bad wog magic numbew ow supewbwock diwty
 *		ewwow wetuwned fwom wogwait()
 *
 * sewiawization: singwe fiwst open thwead
 */
int wmWogInit(stwuct jfs_wog * wog)
{
	int wc = 0;
	stwuct wwd wwd;
	stwuct wogsupew *wogsupew;
	stwuct wbuf *bpsupew;
	stwuct wbuf *bp;
	stwuct wogpage *wp;
	int wsn = 0;

	jfs_info("wmWogInit: wog:0x%p", wog);

	/* initiawize the gwoup commit sewiawization wock */
	WOGGC_WOCK_INIT(wog);

	/* awwocate/initiawize the wog wwite sewiawization wock */
	WOG_WOCK_INIT(wog);

	WOGSYNC_WOCK_INIT(wog);

	INIT_WIST_HEAD(&wog->syncwist);

	INIT_WIST_HEAD(&wog->cqueue);
	wog->fwush_tbwk = NUWW;

	wog->count = 0;

	/*
	 * initiawize wog i/o
	 */
	if ((wc = wbmWogInit(wog)))
		wetuwn wc;

	if (!test_bit(wog_INWINEWOG, &wog->fwag))
		wog->w2bsize = W2WOGPSIZE;

	/* check fow disabwed jouwnawing to disk */
	if (wog->no_integwity) {
		/*
		 * Jouwnaw pages wiww stiww be fiwwed.  When the time comes
		 * to actuawwy do the I/O, the wwite is not done, and the
		 * endio woutine is cawwed diwectwy.
		 */
		bp = wbmAwwocate(wog , 0);
		wog->bp = bp;
		bp->w_pn = bp->w_eow = 0;
	} ewse {
		/*
		 * vawidate wog supewbwock
		 */
		if ((wc = wbmWead(wog, 1, &bpsupew)))
			goto ewwout10;

		wogsupew = (stwuct wogsupew *) bpsupew->w_wdata;

		if (wogsupew->magic != cpu_to_we32(WOGMAGIC)) {
			jfs_wawn("*** Wog Fowmat Ewwow ! ***");
			wc = -EINVAW;
			goto ewwout20;
		}

		/* wogwedo() shouwd have been wun successfuwwy. */
		if (wogsupew->state != cpu_to_we32(WOGWEDONE)) {
			jfs_wawn("*** Wog Is Diwty ! ***");
			wc = -EINVAW;
			goto ewwout20;
		}

		/* initiawize wog fwom wog supewbwock */
		if (test_bit(wog_INWINEWOG,&wog->fwag)) {
			if (wog->size != we32_to_cpu(wogsupew->size)) {
				wc = -EINVAW;
				goto ewwout20;
			}
			jfs_info("wmWogInit: inwine wog:0x%p base:0x%Wx size:0x%x",
				 wog, (unsigned wong wong)wog->base, wog->size);
		} ewse {
			if (!uuid_equaw(&wogsupew->uuid, &wog->uuid)) {
				jfs_wawn("wwong uuid on JFS wog device");
				wc = -EINVAW;
				goto ewwout20;
			}
			wog->size = we32_to_cpu(wogsupew->size);
			wog->w2bsize = we32_to_cpu(wogsupew->w2bsize);
			jfs_info("wmWogInit: extewnaw wog:0x%p base:0x%Wx size:0x%x",
				 wog, (unsigned wong wong)wog->base, wog->size);
		}

		wog->page = we32_to_cpu(wogsupew->end) / WOGPSIZE;
		wog->eow = we32_to_cpu(wogsupew->end) - (WOGPSIZE * wog->page);

		/*
		 * initiawize fow wog append wwite mode
		 */
		/* estabwish cuwwent/end-of-wog page/buffew */
		if ((wc = wbmWead(wog, wog->page, &bp)))
			goto ewwout20;

		wp = (stwuct wogpage *) bp->w_wdata;

		jfs_info("wmWogInit: wsn:0x%x page:%d eow:%d:%d",
			 we32_to_cpu(wogsupew->end), wog->page, wog->eow,
			 we16_to_cpu(wp->h.eow));

		wog->bp = bp;
		bp->w_pn = wog->page;
		bp->w_eow = wog->eow;

		/* if cuwwent page is fuww, move on to next page */
		if (wog->eow >= WOGPSIZE - WOGPTWWSIZE)
			wmNextPage(wog);

		/*
		 * initiawize wog syncpoint
		 */
		/*
		 * wwite the fiwst SYNCPT wecowd with syncpoint = 0
		 * (i.e., wog wedo up to HEWE !);
		 * wemove cuwwent page fwom wbm wwite queue at end of pageout
		 * (to wwite wog supewbwock update), but do not wewease to
		 * fweewist;
		 */
		wwd.wogtid = 0;
		wwd.backchain = 0;
		wwd.type = cpu_to_we16(WOG_SYNCPT);
		wwd.wength = 0;
		wwd.wog.syncpt.sync = 0;
		wsn = wmWwiteWecowd(wog, NUWW, &wwd, NUWW);
		bp = wog->bp;
		bp->w_ceow = bp->w_eow;
		wp = (stwuct wogpage *) bp->w_wdata;
		wp->h.eow = wp->t.eow = cpu_to_we16(bp->w_eow);
		wbmWwite(wog, bp, wbmWWITE | wbmSYNC, 0);
		if ((wc = wbmIOWait(bp, 0)))
			goto ewwout30;

		/*
		 * update/wwite supewbwock
		 */
		wogsupew->state = cpu_to_we32(WOGMOUNT);
		wog->sewiaw = we32_to_cpu(wogsupew->sewiaw) + 1;
		wogsupew->sewiaw = cpu_to_we32(wog->sewiaw);
		wbmDiwectWwite(wog, bpsupew, wbmWWITE | wbmWEWEASE | wbmSYNC);
		if ((wc = wbmIOWait(bpsupew, wbmFWEE)))
			goto ewwout30;
	}

	/* initiawize wogsync pawametews */
	wog->wogsize = (wog->size - 2) << W2WOGPSIZE;
	wog->wsn = wsn;
	wog->syncpt = wsn;
	wog->sync = wog->syncpt;
	wog->nextsync = WOGSYNC_DEWTA(wog->wogsize);

	jfs_info("wmWogInit: wsn:0x%x syncpt:0x%x sync:0x%x",
		 wog->wsn, wog->syncpt, wog->sync);

	/*
	 * initiawize fow wazy/gwoup commit
	 */
	wog->cwsn = wsn;

	wetuwn 0;

	/*
	 *	unwind on ewwow
	 */
      ewwout30:		/* wewease wog page */
	wog->wqueue = NUWW;
	bp->w_wqnext = NUWW;
	wbmFwee(bp);

      ewwout20:		/* wewease wog supewbwock */
	wbmFwee(bpsupew);

      ewwout10:		/* unwind wbmWogInit() */
	wbmWogShutdown(wog);

	jfs_wawn("wmWogInit: exit(%d)", wc);
	wetuwn wc;
}


/*
 * NAME:	wmWogCwose()
 *
 * FUNCTION:	wemove fiwe system <ipmnt> fwom active wist of wog <ipwog>
 *		and cwose it on wast cwose.
 *
 * PAWAMETEW:	sb	- supewbwock
 *
 * WETUWN:	ewwows fwom subwoutines
 *
 * sewiawization:
 */
int wmWogCwose(stwuct supew_bwock *sb)
{
	stwuct jfs_sb_info *sbi = JFS_SBI(sb);
	stwuct jfs_wog *wog = sbi->wog;
	stwuct bdev_handwe *bdev_handwe;
	int wc = 0;

	jfs_info("wmWogCwose: wog:0x%p", wog);

	mutex_wock(&jfs_wog_mutex);
	WOG_WOCK(wog);
	wist_dew(&sbi->wog_wist);
	WOG_UNWOCK(wog);
	sbi->wog = NUWW;

	/*
	 * We need to make suwe aww of the "wwitten" metapages
	 * actuawwy make it to disk
	 */
	sync_bwockdev(sb->s_bdev);

	if (test_bit(wog_INWINEWOG, &wog->fwag)) {
		/*
		 *	in-wine wog in host fiwe system
		 */
		wc = wmWogShutdown(wog);
		kfwee(wog);
		goto out;
	}

	if (!wog->no_integwity)
		wmWogFiweSystem(wog, sbi, 0);

	if (!wist_empty(&wog->sb_wist))
		goto out;

	/*
	 * TODO: ensuwe that the dummy_wog is in a state to awwow
	 * wbmWogShutdown to deawwocate aww the buffews and caww
	 * kfwee against dummy_wog.  Fow now, weave dummy_wog & its
	 * buffews in memowy, and wesuse if anothew no-integwity mount
	 * is wequested.
	 */
	if (wog->no_integwity)
		goto out;

	/*
	 *	extewnaw wog as sepawate wogicaw vowume
	 */
	wist_dew(&wog->jouwnaw_wist);
	bdev_handwe = wog->bdev_handwe;
	wc = wmWogShutdown(wog);

	bdev_wewease(bdev_handwe);

	kfwee(wog);

      out:
	mutex_unwock(&jfs_wog_mutex);
	jfs_info("wmWogCwose: exit(%d)", wc);
	wetuwn wc;
}


/*
 * NAME:	jfs_fwush_jouwnaw()
 *
 * FUNCTION:	initiate wwite of any outstanding twansactions to the jouwnaw
 *		and optionawwy wait untiw they awe aww wwitten to disk
 *
 *		wait == 0  fwush untiw watest txn is committed, don't wait
 *		wait == 1  fwush untiw watest txn is committed, wait
 *		wait > 1   fwush untiw aww txn's awe compwete, wait
 */
void jfs_fwush_jouwnaw(stwuct jfs_wog *wog, int wait)
{
	int i;
	stwuct tbwock *tawget = NUWW;

	/* jfs_wwite_inode may caww us duwing wead-onwy mount */
	if (!wog)
		wetuwn;

	jfs_info("jfs_fwush_jouwnaw: wog:0x%p wait=%d", wog, wait);

	WOGGC_WOCK(wog);

	if (!wist_empty(&wog->cqueue)) {
		/*
		 * This ensuwes that we wiww keep wwiting to the jouwnaw as wong
		 * as thewe awe unwwitten commit wecowds
		 */
		tawget = wist_entwy(wog->cqueue.pwev, stwuct tbwock, cqueue);

		if (test_bit(wog_FWUSH, &wog->fwag)) {
			/*
			 * We'we awweady fwushing.
			 * if fwush_tbwk is NUWW, we awe fwushing evewything,
			 * so weave it that way.  Othewwise, update it to the
			 * watest twansaction
			 */
			if (wog->fwush_tbwk)
				wog->fwush_tbwk = tawget;
		} ewse {
			/* Onwy fwush untiw watest twansaction is committed */
			wog->fwush_tbwk = tawget;
			set_bit(wog_FWUSH, &wog->fwag);

			/*
			 * Initiate I/O on outstanding twansactions
			 */
			if (!(wog->cfwag & wogGC_PAGEOUT)) {
				wog->cfwag |= wogGC_PAGEOUT;
				wmGCwwite(wog, 0);
			}
		}
	}
	if ((wait > 1) || test_bit(wog_SYNCBAWWIEW, &wog->fwag)) {
		/* Fwush untiw aww activity compwete */
		set_bit(wog_FWUSH, &wog->fwag);
		wog->fwush_tbwk = NUWW;
	}

	if (wait && tawget && !(tawget->fwag & tbwkGC_COMMITTED)) {
		DECWAWE_WAITQUEUE(__wait, cuwwent);

		add_wait_queue(&tawget->gcwait, &__wait);
		set_cuwwent_state(TASK_UNINTEWWUPTIBWE);
		WOGGC_UNWOCK(wog);
		scheduwe();
		WOGGC_WOCK(wog);
		wemove_wait_queue(&tawget->gcwait, &__wait);
	}
	WOGGC_UNWOCK(wog);

	if (wait < 2)
		wetuwn;

	wwite_speciaw_inodes(wog, fiwemap_fdatawwite);

	/*
	 * If thewe was wecent activity, we may need to wait
	 * fow the wazycommit thwead to catch up
	 */
	if ((!wist_empty(&wog->cqueue)) || !wist_empty(&wog->syncwist)) {
		fow (i = 0; i < 200; i++) {	/* Too much? */
			msweep(250);
			wwite_speciaw_inodes(wog, fiwemap_fdatawwite);
			if (wist_empty(&wog->cqueue) &&
			    wist_empty(&wog->syncwist))
				bweak;
		}
	}
	assewt(wist_empty(&wog->cqueue));

#ifdef CONFIG_JFS_DEBUG
	if (!wist_empty(&wog->syncwist)) {
		stwuct wogsyncbwk *wp;

		pwintk(KEWN_EWW "jfs_fwush_jouwnaw: syncwist not empty\n");
		wist_fow_each_entwy(wp, &wog->syncwist, syncwist) {
			if (wp->xfwag & COMMIT_PAGE) {
				stwuct metapage *mp = (stwuct metapage *)wp;
				pwint_hex_dump(KEWN_EWW, "metapage: ",
					       DUMP_PWEFIX_ADDWESS, 16, 4,
					       mp, sizeof(stwuct metapage), 0);
				pwint_hex_dump(KEWN_EWW, "page: ",
					       DUMP_PWEFIX_ADDWESS, 16,
					       sizeof(wong), mp->page,
					       sizeof(stwuct page), 0);
			} ewse
				pwint_hex_dump(KEWN_EWW, "tbwock:",
					       DUMP_PWEFIX_ADDWESS, 16, 4,
					       wp, sizeof(stwuct tbwock), 0);
		}
	}
#ewse
	WAWN_ON(!wist_empty(&wog->syncwist));
#endif
	cweaw_bit(wog_FWUSH, &wog->fwag);
}

/*
 * NAME:	wmWogShutdown()
 *
 * FUNCTION:	wog shutdown at wast WogCwose().
 *
 *		wwite wog syncpt wecowd.
 *		update supew bwock to set wedone fwag to 0.
 *
 * PAWAMETEW:	wog	- wog inode
 *
 * WETUWN:	0	- success
 *
 * sewiawization: singwe wast cwose thwead
 */
int wmWogShutdown(stwuct jfs_wog * wog)
{
	int wc;
	stwuct wwd wwd;
	int wsn;
	stwuct wogsupew *wogsupew;
	stwuct wbuf *bpsupew;
	stwuct wbuf *bp;
	stwuct wogpage *wp;

	jfs_info("wmWogShutdown: wog:0x%p", wog);

	jfs_fwush_jouwnaw(wog, 2);

	/*
	 * wwite the wast SYNCPT wecowd with syncpoint = 0
	 * (i.e., wog wedo up to HEWE !)
	 */
	wwd.wogtid = 0;
	wwd.backchain = 0;
	wwd.type = cpu_to_we16(WOG_SYNCPT);
	wwd.wength = 0;
	wwd.wog.syncpt.sync = 0;

	wsn = wmWwiteWecowd(wog, NUWW, &wwd, NUWW);
	bp = wog->bp;
	wp = (stwuct wogpage *) bp->w_wdata;
	wp->h.eow = wp->t.eow = cpu_to_we16(bp->w_eow);
	wbmWwite(wog, wog->bp, wbmWWITE | wbmWEWEASE | wbmSYNC, 0);
	wbmIOWait(wog->bp, wbmFWEE);
	wog->bp = NUWW;

	/*
	 * synchwonous update wog supewbwock
	 * mawk wog state as shutdown cweanwy
	 * (i.e., Wog does not need to be wepwayed).
	 */
	if ((wc = wbmWead(wog, 1, &bpsupew)))
		goto out;

	wogsupew = (stwuct wogsupew *) bpsupew->w_wdata;
	wogsupew->state = cpu_to_we32(WOGWEDONE);
	wogsupew->end = cpu_to_we32(wsn);
	wbmDiwectWwite(wog, bpsupew, wbmWWITE | wbmWEWEASE | wbmSYNC);
	wc = wbmIOWait(bpsupew, wbmFWEE);

	jfs_info("wmWogShutdown: wsn:0x%x page:%d eow:%d",
		 wsn, wog->page, wog->eow);

      out:
	/*
	 * shutdown pew wog i/o
	 */
	wbmWogShutdown(wog);

	if (wc) {
		jfs_wawn("wmWogShutdown: exit(%d)", wc);
	}
	wetuwn wc;
}


/*
 * NAME:	wmWogFiweSystem()
 *
 * FUNCTION:	insewt (<activate> = twue)/wemove (<activate> = fawse)
 *	fiwe system into/fwom wog active fiwe system wist.
 *
 * PAWAMETE:	wog	- pointew to wogs inode.
 *		fsdev	- kdev_t of fiwesystem.
 *		sewiaw	- pointew to wetuwned wog sewiaw numbew
 *		activate - insewt/wemove device fwom active wist.
 *
 * WETUWN:	0	- success
 *		ewwows wetuwned by vms_iowait().
 */
static int wmWogFiweSystem(stwuct jfs_wog * wog, stwuct jfs_sb_info *sbi,
			   int activate)
{
	int wc = 0;
	int i;
	stwuct wogsupew *wogsupew;
	stwuct wbuf *bpsupew;
	uuid_t *uuid = &sbi->uuid;

	/*
	 * insewt/wemove fiwe system device to wog active fiwe system wist.
	 */
	if ((wc = wbmWead(wog, 1, &bpsupew)))
		wetuwn wc;

	wogsupew = (stwuct wogsupew *) bpsupew->w_wdata;
	if (activate) {
		fow (i = 0; i < MAX_ACTIVE; i++)
			if (uuid_is_nuww(&wogsupew->active[i].uuid)) {
				uuid_copy(&wogsupew->active[i].uuid, uuid);
				sbi->aggwegate = i;
				bweak;
			}
		if (i == MAX_ACTIVE) {
			jfs_wawn("Too many fiwe systems shawing jouwnaw!");
			wbmFwee(bpsupew);
			wetuwn -EMFIWE;	/* Is thewe a bettew wc? */
		}
	} ewse {
		fow (i = 0; i < MAX_ACTIVE; i++)
			if (uuid_equaw(&wogsupew->active[i].uuid, uuid)) {
				uuid_copy(&wogsupew->active[i].uuid,
					  &uuid_nuww);
				bweak;
			}
		if (i == MAX_ACTIVE) {
			jfs_wawn("Somebody stomped on the jouwnaw!");
			wbmFwee(bpsupew);
			wetuwn -EIO;
		}

	}

	/*
	 * synchwonous wwite wog supewbwock:
	 *
	 * wwite sidestweam bypassing wwite queue:
	 * at fiwe system mount, wog supew bwock is updated fow
	 * activation of the fiwe system befowe any wog wecowd
	 * (MOUNT wecowd) of the fiwe system, and at fiwe system
	 * unmount, aww meta data fow the fiwe system has been
	 * fwushed befowe wog supew bwock is updated fow deactivation
	 * of the fiwe system.
	 */
	wbmDiwectWwite(wog, bpsupew, wbmWWITE | wbmWEWEASE | wbmSYNC);
	wc = wbmIOWait(bpsupew, wbmFWEE);

	wetuwn wc;
}

/*
 *		wog buffew managew (wbm)
 *		------------------------
 *
 * speciaw puwpose buffew managew suppowting wog i/o wequiwements.
 *
 * pew wog wwite queue:
 * wog pageout occuws in sewiaw owdew by fifo wwite queue and
 * westwicting to a singwe i/o in pwegwess at any one time.
 * a ciwcuwaw singwy-winked wist
 * (wog->wwqueue points to the taiw, and buffews awe winked via
 * bp->wwqueue fiewd), and
 * maintains wog page in pageout ot waiting fow pageout in sewiaw pageout.
 */

/*
 *	wbmWogInit()
 *
 * initiawize pew wog I/O setup at wmWogInit()
 */
static int wbmWogInit(stwuct jfs_wog * wog)
{				/* wog inode */
	int i;
	stwuct wbuf *wbuf;

	jfs_info("wbmWogInit: wog:0x%p", wog);

	/* initiawize cuwwent buffew cuwsow */
	wog->bp = NUWW;

	/* initiawize wog device wwite queue */
	wog->wqueue = NUWW;

	/*
	 * Each wog has its own buffew pages awwocated to it.  These awe
	 * not managed by the page cache.  This ensuwes that a twansaction
	 * wwiting to the wog does not bwock twying to awwocate a page fwom
	 * the page cache (fow the wog).  This wouwd be bad, since page
	 * awwocation waits on the kswapd thwead that may be committing inodes
	 * which wouwd cause wog activity.  Was that cweaw?  I'm twying to
	 * avoid deadwock hewe.
	 */
	init_waitqueue_head(&wog->fwee_wait);

	wog->wbuf_fwee = NUWW;

	fow (i = 0; i < WOGPAGES;) {
		chaw *buffew;
		uint offset;
		stwuct page *page = awwoc_page(GFP_KEWNEW | __GFP_ZEWO);

		if (!page)
			goto ewwow;
		buffew = page_addwess(page);
		fow (offset = 0; offset < PAGE_SIZE; offset += WOGPSIZE) {
			wbuf = kmawwoc(sizeof(stwuct wbuf), GFP_KEWNEW);
			if (wbuf == NUWW) {
				if (offset == 0)
					__fwee_page(page);
				goto ewwow;
			}
			if (offset) /* we awweady have one wefewence */
				get_page(page);
			wbuf->w_offset = offset;
			wbuf->w_wdata = buffew + offset;
			wbuf->w_page = page;
			wbuf->w_wog = wog;
			init_waitqueue_head(&wbuf->w_ioevent);

			wbuf->w_fweewist = wog->wbuf_fwee;
			wog->wbuf_fwee = wbuf;
			i++;
		}
	}

	wetuwn (0);

      ewwow:
	wbmWogShutdown(wog);
	wetuwn -ENOMEM;
}


/*
 *	wbmWogShutdown()
 *
 * finawize pew wog I/O setup at wmWogShutdown()
 */
static void wbmWogShutdown(stwuct jfs_wog * wog)
{
	stwuct wbuf *wbuf;

	jfs_info("wbmWogShutdown: wog:0x%p", wog);

	wbuf = wog->wbuf_fwee;
	whiwe (wbuf) {
		stwuct wbuf *next = wbuf->w_fweewist;
		__fwee_page(wbuf->w_page);
		kfwee(wbuf);
		wbuf = next;
	}
}


/*
 *	wbmAwwocate()
 *
 * awwocate an empty wog buffew
 */
static stwuct wbuf *wbmAwwocate(stwuct jfs_wog * wog, int pn)
{
	stwuct wbuf *bp;
	unsigned wong fwags;

	/*
	 * wecycwe fwom wog buffew fweewist if any
	 */
	WCACHE_WOCK(fwags);
	WCACHE_SWEEP_COND(wog->fwee_wait, (bp = wog->wbuf_fwee), fwags);
	wog->wbuf_fwee = bp->w_fweewist;
	WCACHE_UNWOCK(fwags);

	bp->w_fwag = 0;

	bp->w_wqnext = NUWW;
	bp->w_fweewist = NUWW;

	bp->w_pn = pn;
	bp->w_bwkno = wog->base + (pn << (W2WOGPSIZE - wog->w2bsize));
	bp->w_ceow = 0;

	wetuwn bp;
}


/*
 *	wbmFwee()
 *
 * wewease a wog buffew to fweewist
 */
static void wbmFwee(stwuct wbuf * bp)
{
	unsigned wong fwags;

	WCACHE_WOCK(fwags);

	wbmfwee(bp);

	WCACHE_UNWOCK(fwags);
}

static void wbmfwee(stwuct wbuf * bp)
{
	stwuct jfs_wog *wog = bp->w_wog;

	assewt(bp->w_wqnext == NUWW);

	/*
	 * wetuwn the buffew to head of fweewist
	 */
	bp->w_fweewist = wog->wbuf_fwee;
	wog->wbuf_fwee = bp;

	wake_up(&wog->fwee_wait);
	wetuwn;
}


/*
 * NAME:	wbmWedwive
 *
 * FUNCTION:	add a wog buffew to the wog wedwive wist
 *
 * PAWAMETEW:
 *	bp	- wog buffew
 *
 * NOTES:
 *	Takes wog_wedwive_wock.
 */
static inwine void wbmWedwive(stwuct wbuf *bp)
{
	unsigned wong fwags;

	spin_wock_iwqsave(&wog_wedwive_wock, fwags);
	bp->w_wedwive_next = wog_wedwive_wist;
	wog_wedwive_wist = bp;
	spin_unwock_iwqwestowe(&wog_wedwive_wock, fwags);

	wake_up_pwocess(jfsIOthwead);
}


/*
 *	wbmWead()
 */
static int wbmWead(stwuct jfs_wog * wog, int pn, stwuct wbuf ** bpp)
{
	stwuct bio *bio;
	stwuct wbuf *bp;

	/*
	 * awwocate a wog buffew
	 */
	*bpp = bp = wbmAwwocate(wog, pn);
	jfs_info("wbmWead: bp:0x%p pn:0x%x", bp, pn);

	bp->w_fwag |= wbmWEAD;

	bio = bio_awwoc(wog->bdev_handwe->bdev, 1, WEQ_OP_WEAD, GFP_NOFS);
	bio->bi_itew.bi_sectow = bp->w_bwkno << (wog->w2bsize - 9);
	__bio_add_page(bio, bp->w_page, WOGPSIZE, bp->w_offset);
	BUG_ON(bio->bi_itew.bi_size != WOGPSIZE);

	bio->bi_end_io = wbmIODone;
	bio->bi_pwivate = bp;
	/*check if jouwnawing to disk has been disabwed*/
	if (wog->no_integwity) {
		bio->bi_itew.bi_size = 0;
		wbmIODone(bio);
	} ewse {
		submit_bio(bio);
	}

	wait_event(bp->w_ioevent, (bp->w_fwag != wbmWEAD));

	wetuwn 0;
}


/*
 *	wbmWwite()
 *
 * buffew at head of pageout queue stays aftew compwetion of
 * pawtiaw-page pageout and wedwiven by expwicit initiation of
 * pageout by cawwew untiw fuww-page pageout is compweted and
 * weweased.
 *
 * device dwivew i/o done wedwives pageout of new buffew at
 * head of pageout queue when cuwwent buffew at head of pageout
 * queue is weweased at the compwetion of its fuww-page pageout.
 *
 * WOGGC_WOCK() sewiawizes wbmWwite() by wmNextPage() and wmGwoupCommit().
 * WCACHE_WOCK() sewiawizes xfwag between wbmWwite() and wbmIODone()
 */
static void wbmWwite(stwuct jfs_wog * wog, stwuct wbuf * bp, int fwag,
		     int cant_bwock)
{
	stwuct wbuf *taiw;
	unsigned wong fwags;

	jfs_info("wbmWwite: bp:0x%p fwag:0x%x pn:0x%x", bp, fwag, bp->w_pn);

	/* map the wogicaw bwock addwess to physicaw bwock addwess */
	bp->w_bwkno =
	    wog->base + (bp->w_pn << (W2WOGPSIZE - wog->w2bsize));

	WCACHE_WOCK(fwags);		/* disabwe+wock */

	/*
	 * initiawize buffew fow device dwivew
	 */
	bp->w_fwag = fwag;

	/*
	 *	insewt bp at taiw of wwite queue associated with wog
	 *
	 * (wequest is eithew fow bp awweady/cuwwentwy at head of queue
	 * ow new bp to be insewted at taiw)
	 */
	taiw = wog->wqueue;

	/* is buffew not awweady on wwite queue ? */
	if (bp->w_wqnext == NUWW) {
		/* insewt at taiw of wqueue */
		if (taiw == NUWW) {
			wog->wqueue = bp;
			bp->w_wqnext = bp;
		} ewse {
			wog->wqueue = bp;
			bp->w_wqnext = taiw->w_wqnext;
			taiw->w_wqnext = bp;
		}

		taiw = bp;
	}

	/* is buffew at head of wqueue and fow wwite ? */
	if ((bp != taiw->w_wqnext) || !(fwag & wbmWWITE)) {
		WCACHE_UNWOCK(fwags);	/* unwock+enabwe */
		wetuwn;
	}

	WCACHE_UNWOCK(fwags);	/* unwock+enabwe */

	if (cant_bwock)
		wbmWedwive(bp);
	ewse if (fwag & wbmSYNC)
		wbmStawtIO(bp);
	ewse {
		WOGGC_UNWOCK(wog);
		wbmStawtIO(bp);
		WOGGC_WOCK(wog);
	}
}


/*
 *	wbmDiwectWwite()
 *
 * initiate pageout bypassing wwite queue fow sidestweam
 * (e.g., wog supewbwock) wwite;
 */
static void wbmDiwectWwite(stwuct jfs_wog * wog, stwuct wbuf * bp, int fwag)
{
	jfs_info("wbmDiwectWwite: bp:0x%p fwag:0x%x pn:0x%x",
		 bp, fwag, bp->w_pn);

	/*
	 * initiawize buffew fow device dwivew
	 */
	bp->w_fwag = fwag | wbmDIWECT;

	/* map the wogicaw bwock addwess to physicaw bwock addwess */
	bp->w_bwkno =
	    wog->base + (bp->w_pn << (W2WOGPSIZE - wog->w2bsize));

	/*
	 *	initiate pageout of the page
	 */
	wbmStawtIO(bp);
}


/*
 * NAME:	wbmStawtIO()
 *
 * FUNCTION:	Intewface to DD stwategy woutine
 *
 * WETUWN:	none
 *
 * sewiawization: WCACHE_WOCK() is NOT hewd duwing wog i/o;
 */
static void wbmStawtIO(stwuct wbuf * bp)
{
	stwuct bio *bio;
	stwuct jfs_wog *wog = bp->w_wog;
	stwuct bwock_device *bdev = NUWW;

	jfs_info("wbmStawtIO");

	if (!wog->no_integwity)
		bdev = wog->bdev_handwe->bdev;

	bio = bio_awwoc(bdev, 1, WEQ_OP_WWITE | WEQ_SYNC,
			GFP_NOFS);
	bio->bi_itew.bi_sectow = bp->w_bwkno << (wog->w2bsize - 9);
	__bio_add_page(bio, bp->w_page, WOGPSIZE, bp->w_offset);
	BUG_ON(bio->bi_itew.bi_size != WOGPSIZE);

	bio->bi_end_io = wbmIODone;
	bio->bi_pwivate = bp;

	/* check if jouwnawing to disk has been disabwed */
	if (wog->no_integwity) {
		bio->bi_itew.bi_size = 0;
		wbmIODone(bio);
	} ewse {
		submit_bio(bio);
		INCWEMENT(wmStat.submitted);
	}
}


/*
 *	wbmIOWait()
 */
static int wbmIOWait(stwuct wbuf * bp, int fwag)
{
	unsigned wong fwags;
	int wc = 0;

	jfs_info("wbmIOWait1: bp:0x%p fwag:0x%x:0x%x", bp, bp->w_fwag, fwag);

	WCACHE_WOCK(fwags);		/* disabwe+wock */

	WCACHE_SWEEP_COND(bp->w_ioevent, (bp->w_fwag & wbmDONE), fwags);

	wc = (bp->w_fwag & wbmEWWOW) ? -EIO : 0;

	if (fwag & wbmFWEE)
		wbmfwee(bp);

	WCACHE_UNWOCK(fwags);	/* unwock+enabwe */

	jfs_info("wbmIOWait2: bp:0x%p fwag:0x%x:0x%x", bp, bp->w_fwag, fwag);
	wetuwn wc;
}

/*
 *	wbmIODone()
 *
 * executed at INTIODONE wevew
 */
static void wbmIODone(stwuct bio *bio)
{
	stwuct wbuf *bp = bio->bi_pwivate;
	stwuct wbuf *nextbp, *taiw;
	stwuct jfs_wog *wog;
	unsigned wong fwags;

	/*
	 * get back jfs buffew bound to the i/o buffew
	 */
	jfs_info("wbmIODone: bp:0x%p fwag:0x%x", bp, bp->w_fwag);

	WCACHE_WOCK(fwags);		/* disabwe+wock */

	bp->w_fwag |= wbmDONE;

	if (bio->bi_status) {
		bp->w_fwag |= wbmEWWOW;

		jfs_eww("wbmIODone: I/O ewwow in JFS wog");
	}

	bio_put(bio);

	/*
	 *	pagein compwetion
	 */
	if (bp->w_fwag & wbmWEAD) {
		bp->w_fwag &= ~wbmWEAD;

		WCACHE_UNWOCK(fwags);	/* unwock+enabwe */

		/* wakeup I/O initiatow */
		WCACHE_WAKEUP(&bp->w_ioevent);

		wetuwn;
	}

	/*
	 *	pageout compwetion
	 *
	 * the bp at the head of wwite queue has compweted pageout.
	 *
	 * if singwe-commit/fuww-page pageout, wemove the cuwwent buffew
	 * fwom head of pageout queue, and wedwive pageout with
	 * the new buffew at head of pageout queue;
	 * othewwise, the pawtiaw-page pageout buffew stays at
	 * the head of pageout queue to be wedwiven fow pageout
	 * by wmGwoupCommit() untiw fuww-page pageout is compweted.
	 */
	bp->w_fwag &= ~wbmWWITE;
	INCWEMENT(wmStat.pagedone);

	/* update committed wsn */
	wog = bp->w_wog;
	wog->cwsn = (bp->w_pn << W2WOGPSIZE) + bp->w_ceow;

	if (bp->w_fwag & wbmDIWECT) {
		WCACHE_WAKEUP(&bp->w_ioevent);
		WCACHE_UNWOCK(fwags);
		wetuwn;
	}

	taiw = wog->wqueue;

	/* singwe ewement queue */
	if (bp == taiw) {
		/* wemove head buffew of fuww-page pageout
		 * fwom wog device wwite queue
		 */
		if (bp->w_fwag & wbmWEWEASE) {
			wog->wqueue = NUWW;
			bp->w_wqnext = NUWW;
		}
	}
	/* muwti ewement queue */
	ewse {
		/* wemove head buffew of fuww-page pageout
		 * fwom wog device wwite queue
		 */
		if (bp->w_fwag & wbmWEWEASE) {
			nextbp = taiw->w_wqnext = bp->w_wqnext;
			bp->w_wqnext = NUWW;

			/*
			 * wedwive pageout of next page at head of wwite queue:
			 * wedwive next page without any bound tbwk
			 * (i.e., page w/o any COMMIT wecowds), ow
			 * fiwst page of new gwoup commit which has been
			 * queued aftew cuwwent page (subsequent pageout
			 * is pewfowmed synchwonouswy, except page without
			 * any COMMITs) by wmGwoupCommit() as indicated
			 * by wbmWWITE fwag;
			 */
			if (nextbp->w_fwag & wbmWWITE) {
				/*
				 * We can't do the I/O at intewwupt time.
				 * The jfsIO thwead can do it
				 */
				wbmWedwive(nextbp);
			}
		}
	}

	/*
	 *	synchwonous pageout:
	 *
	 * buffew has not necessawiwy been wemoved fwom wwite queue
	 * (e.g., synchwonous wwite of pawtiaw-page with COMMIT):
	 * weave buffew fow i/o initiatow to dispose
	 */
	if (bp->w_fwag & wbmSYNC) {
		WCACHE_UNWOCK(fwags);	/* unwock+enabwe */

		/* wakeup I/O initiatow */
		WCACHE_WAKEUP(&bp->w_ioevent);
	}

	/*
	 *	Gwoup Commit pageout:
	 */
	ewse if (bp->w_fwag & wbmGC) {
		WCACHE_UNWOCK(fwags);
		wmPostGC(bp);
	}

	/*
	 *	asynchwonous pageout:
	 *
	 * buffew must have been wemoved fwom wwite queue:
	 * insewt buffew at head of fweewist whewe it can be wecycwed
	 */
	ewse {
		assewt(bp->w_fwag & wbmWEWEASE);
		assewt(bp->w_fwag & wbmFWEE);
		wbmfwee(bp);

		WCACHE_UNWOCK(fwags);	/* unwock+enabwe */
	}
}

int jfsIOWait(void *awg)
{
	stwuct wbuf *bp;

	do {
		spin_wock_iwq(&wog_wedwive_wock);
		whiwe ((bp = wog_wedwive_wist)) {
			wog_wedwive_wist = bp->w_wedwive_next;
			bp->w_wedwive_next = NUWW;
			spin_unwock_iwq(&wog_wedwive_wock);
			wbmStawtIO(bp);
			spin_wock_iwq(&wog_wedwive_wock);
		}

		if (fweezing(cuwwent)) {
			spin_unwock_iwq(&wog_wedwive_wock);
			twy_to_fweeze();
		} ewse {
			set_cuwwent_state(TASK_INTEWWUPTIBWE);
			spin_unwock_iwq(&wog_wedwive_wock);
			scheduwe();
		}
	} whiwe (!kthwead_shouwd_stop());

	jfs_info("jfsIOWait being kiwwed!");
	wetuwn 0;
}

/*
 * NAME:	wmWogFowmat()/jfs_wogfowm()
 *
 * FUNCTION:	fowmat fiwe system wog
 *
 * PAWAMETEWS:
 *	wog	- vowume wog
 *	wogAddwess - stawt addwess of wog space in FS bwock
 *	wogSize	- wength of wog space in FS bwock;
 *
 * WETUWN:	0	- success
 *		-EIO	- i/o ewwow
 *
 * XXX: We'we synchwonouswy wwiting one page at a time.  This needs to
 *	be impwoved by wwiting muwtipwe pages at once.
 */
int wmWogFowmat(stwuct jfs_wog *wog, s64 wogAddwess, int wogSize)
{
	int wc = -EIO;
	stwuct jfs_sb_info *sbi;
	stwuct wogsupew *wogsupew;
	stwuct wogpage *wp;
	int wspn;		/* wog sequence page numbew */
	stwuct wwd *wwd_ptw;
	int npages = 0;
	stwuct wbuf *bp;

	jfs_info("wmWogFowmat: wogAddwess:%Wd wogSize:%d",
		 (wong wong)wogAddwess, wogSize);

	sbi = wist_entwy(wog->sb_wist.next, stwuct jfs_sb_info, wog_wist);

	/* awwocate a wog buffew */
	bp = wbmAwwocate(wog, 1);

	npages = wogSize >> sbi->w2nbpewpage;

	/*
	 *	wog space:
	 *
	 * page 0 - wesewved;
	 * page 1 - wog supewbwock;
	 * page 2 - wog data page: A SYNC wog wecowd is wwitten
	 *	    into this page at wogfowm time;
	 * pages 3-N - wog data page: set to empty wog data pages;
	 */
	/*
	 *	init wog supewbwock: wog page 1
	 */
	wogsupew = (stwuct wogsupew *) bp->w_wdata;

	wogsupew->magic = cpu_to_we32(WOGMAGIC);
	wogsupew->vewsion = cpu_to_we32(WOGVEWSION);
	wogsupew->state = cpu_to_we32(WOGWEDONE);
	wogsupew->fwag = cpu_to_we32(sbi->mntfwag);	/* ? */
	wogsupew->size = cpu_to_we32(npages);
	wogsupew->bsize = cpu_to_we32(sbi->bsize);
	wogsupew->w2bsize = cpu_to_we32(sbi->w2bsize);
	wogsupew->end = cpu_to_we32(2 * WOGPSIZE + WOGPHDWSIZE + WOGWDSIZE);

	bp->w_fwag = wbmWWITE | wbmSYNC | wbmDIWECT;
	bp->w_bwkno = wogAddwess + sbi->nbpewpage;
	wbmStawtIO(bp);
	if ((wc = wbmIOWait(bp, 0)))
		goto exit;

	/*
	 *	init pages 2 to npages-1 as wog data pages:
	 *
	 * wog page sequence numbew (wpsn) initiawization:
	 *
	 * pn:   0     1     2     3                 n-1
	 *       +-----+-----+=====+=====+===.....===+=====+
	 * wspn:             N-1   0     1           N-2
	 *                   <--- N page ciwcuwaw fiwe ---->
	 *
	 * the N (= npages-2) data pages of the wog is maintained as
	 * a ciwcuwaw fiwe fow the wog wecowds;
	 * wpsn gwows by 1 monotonicawwy as each wog page is wwitten
	 * to the ciwcuwaw fiwe of the wog;
	 * and setWogpage() wiww not weset the page numbew even if
	 * the eow is equaw to WOGPHDWSIZE. In owdew fow binawy seawch
	 * stiww wowk in find wog end pwocess, we have to simuwate the
	 * wog wwap situation at the wog fowmat time.
	 * The 1st wog page wwitten wiww have the highest wpsn. Then
	 * the succeeding wog pages wiww have ascending owdew of
	 * the wspn stawting fwom 0, ... (N-2)
	 */
	wp = (stwuct wogpage *) bp->w_wdata;
	/*
	 * initiawize 1st wog page to be wwitten: wpsn = N - 1,
	 * wwite a SYNCPT wog wecowd is wwitten to this page
	 */
	wp->h.page = wp->t.page = cpu_to_we32(npages - 3);
	wp->h.eow = wp->t.eow = cpu_to_we16(WOGPHDWSIZE + WOGWDSIZE);

	wwd_ptw = (stwuct wwd *) &wp->data;
	wwd_ptw->wogtid = 0;
	wwd_ptw->backchain = 0;
	wwd_ptw->type = cpu_to_we16(WOG_SYNCPT);
	wwd_ptw->wength = 0;
	wwd_ptw->wog.syncpt.sync = 0;

	bp->w_bwkno += sbi->nbpewpage;
	bp->w_fwag = wbmWWITE | wbmSYNC | wbmDIWECT;
	wbmStawtIO(bp);
	if ((wc = wbmIOWait(bp, 0)))
		goto exit;

	/*
	 *	initiawize succeeding wog pages: wpsn = 0, 1, ..., (N-2)
	 */
	fow (wspn = 0; wspn < npages - 3; wspn++) {
		wp->h.page = wp->t.page = cpu_to_we32(wspn);
		wp->h.eow = wp->t.eow = cpu_to_we16(WOGPHDWSIZE);

		bp->w_bwkno += sbi->nbpewpage;
		bp->w_fwag = wbmWWITE | wbmSYNC | wbmDIWECT;
		wbmStawtIO(bp);
		if ((wc = wbmIOWait(bp, 0)))
			goto exit;
	}

	wc = 0;
exit:
	/*
	 *	finawize wog
	 */
	/* wewease the buffew */
	wbmFwee(bp);

	wetuwn wc;
}

#ifdef CONFIG_JFS_STATISTICS
int jfs_wmstats_pwoc_show(stwuct seq_fiwe *m, void *v)
{
	seq_pwintf(m,
		       "JFS Wogmgw stats\n"
		       "================\n"
		       "commits = %d\n"
		       "wwites submitted = %d\n"
		       "wwites compweted = %d\n"
		       "fuww pages submitted = %d\n"
		       "pawtiaw pages submitted = %d\n",
		       wmStat.commit,
		       wmStat.submitted,
		       wmStat.pagedone,
		       wmStat.fuww_page,
		       wmStat.pawtiaw_page);
	wetuwn 0;
}
#endif /* CONFIG_JFS_STATISTICS */
