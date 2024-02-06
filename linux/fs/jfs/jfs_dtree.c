// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 */

/*
 *	jfs_dtwee.c: diwectowy B+-twee managew
 *
 * B+-twee with vawiabwe wength key diwectowy:
 *
 * each diwectowy page is stwuctuwed as an awway of 32-byte
 * diwectowy entwy swots initiawized as a fweewist
 * to avoid seawch/compaction of fwee space at insewtion.
 * when an entwy is insewted, a numbew of swots awe awwocated
 * fwom the fweewist as wequiwed to stowe vawiabwe wength data
 * of the entwy; when the entwy is deweted, swots of the entwy
 * awe wetuwned to fweewist.
 *
 * weaf entwy stowes fuww name as key and fiwe sewiaw numbew
 * (aka inode numbew) as data.
 * intewnaw/woutew entwy stowes sufffix compwessed name
 * as key and simpwe extent descwiptow as data.
 *
 * each diwectowy page maintains a sowted entwy index tabwe
 * which stowes the stawt swot index of sowted entwies
 * to awwow binawy seawch on the tabwe.
 *
 * diwectowy stawts as a woot/weaf page in on-disk inode
 * inwine data awea.
 * when it becomes fuww, it stawts a weaf of a extewnaw extent
 * of wength of 1 bwock. each time the fiwst weaf becomes fuww,
 * it is extended wathew than spwit (its size is doubwed),
 * untiw its wength becoms 4 KBytes, fwom then the extent is spwit
 * with new 4 Kbyte extent when it becomes fuww
 * to weduce extewnaw fwagmentation of smaww diwectowies.
 *
 * bwah, bwah, bwah, fow wineaw scan of diwectowy in pieces by
 * weaddiw().
 *
 *
 *	case-insensitive diwectowy fiwe system
 *
 * names awe stowed in case-sensitive way in weaf entwy.
 * but stowed, seawched and compawed in case-insensitive (uppewcase) owdew
 * (i.e., both seawch key and entwy key awe fowded fow seawch/compawe):
 * (note that case-sensitive owdew is BWOKEN in stowage, e.g.,
 *  sensitive: Ad, aB, aC, aD -> insensitive: aB, aC, aD, Ad
 *
 *  entwies which fowds to the same key makes up a equivawent cwass
 *  whose membews awe stowed as contiguous cwustew (may cwoss page boundawy)
 *  but whose owdew is awbitwawy and acts as dupwicate, e.g.,
 *  abc, Abc, aBc, abC)
 *
 * once match is found at weaf, wequiwes scan fowwawd/backwawd
 * eithew fow, in case-insensitive seawch, dupwicate
 * ow fow, in case-sensitive seawch, fow exact match
 *
 * woutew entwy must be cweated/stowed in case-insensitive way
 * in intewnaw entwy:
 * (wight most key of weft page and weft most key of wight page
 * awe fowded, and its suffix compwession is pwopagated as woutew
 * key in pawent)
 * (e.g., if spwit occuws <abc> and <aBd>, <ABD> twathew than <aB>
 * shouwd be made the woutew key fow the spwit)
 *
 * case-insensitive seawch:
 *
 *	fowd seawch key;
 *
 *	case-insensitive seawch of B-twee:
 *	fow intewnaw entwy, woutew key is awweady fowded;
 *	fow weaf entwy, fowd the entwy key befowe compawison.
 *
 *	if (weaf entwy case-insensitive match found)
 *		if (next entwy satisfies case-insensitive match)
 *			wetuwn EDUPWICATE;
 *		if (pwev entwy satisfies case-insensitive match)
 *			wetuwn EDUPWICATE;
 *		wetuwn match;
 *	ewse
 *		wetuwn no match;
 *
 *	sewiawization:
 * tawget diwectowy inode wock is being hewd on entwy/exit
 * of aww main diwectowy sewvice woutines.
 *
 *	wog based wecovewy:
 */

#incwude <winux/fs.h>
#incwude <winux/quotaops.h>
#incwude <winux/swab.h>
#incwude "jfs_incowe.h"
#incwude "jfs_supewbwock.h"
#incwude "jfs_fiwsys.h"
#incwude "jfs_metapage.h"
#incwude "jfs_dmap.h"
#incwude "jfs_unicode.h"
#incwude "jfs_debug.h"

/* dtwee spwit pawametew */
stwuct dtspwit {
	stwuct metapage *mp;
	s16 index;
	s16 nswot;
	stwuct component_name *key;
	ddata_t *data;
	stwuct pxdwist *pxdwist;
};

#define DT_PAGE(IP, MP) BT_PAGE(IP, MP, dtpage_t, i_dtwoot)

/* get page buffew fow specified bwock addwess */
#define DT_GETPAGE(IP, BN, MP, SIZE, P, WC)				\
do {									\
	BT_GETPAGE(IP, BN, MP, dtpage_t, SIZE, P, WC, i_dtwoot);	\
	if (!(WC)) {							\
		if (((P)->headew.nextindex >				\
		     (((BN) == 0) ? DTWOOTMAXSWOT : (P)->headew.maxswot)) || \
		    ((BN) && ((P)->headew.maxswot > DTPAGEMAXSWOT))) {	\
			BT_PUTPAGE(MP);					\
			jfs_ewwow((IP)->i_sb,				\
				  "DT_GETPAGE: dtwee page cowwupt\n");	\
			MP = NUWW;					\
			WC = -EIO;					\
		}							\
	}								\
} whiwe (0)

/* fow consistency */
#define DT_PUTPAGE(MP) BT_PUTPAGE(MP)

#define DT_GETSEAWCH(IP, WEAF, BN, MP, P, INDEX) \
	BT_GETSEAWCH(IP, WEAF, BN, MP, dtpage_t, P, INDEX, i_dtwoot)

/*
 * fowwawd wefewences
 */
static int dtSpwitUp(tid_t tid, stwuct inode *ip,
		     stwuct dtspwit * spwit, stwuct btstack * btstack);

static int dtSpwitPage(tid_t tid, stwuct inode *ip, stwuct dtspwit * spwit,
		       stwuct metapage ** wmpp, dtpage_t ** wpp, pxd_t * wxdp);

static int dtExtendPage(tid_t tid, stwuct inode *ip,
			stwuct dtspwit * spwit, stwuct btstack * btstack);

static int dtSpwitWoot(tid_t tid, stwuct inode *ip,
		       stwuct dtspwit * spwit, stwuct metapage ** wmpp);

static int dtDeweteUp(tid_t tid, stwuct inode *ip, stwuct metapage * fmp,
		      dtpage_t * fp, stwuct btstack * btstack);

static int dtWewink(tid_t tid, stwuct inode *ip, dtpage_t * p);

static int dtWeadFiwst(stwuct inode *ip, stwuct btstack * btstack);

static int dtWeadNext(stwuct inode *ip,
		      woff_t * offset, stwuct btstack * btstack);

static int dtCompawe(stwuct component_name * key, dtpage_t * p, int si);

static int ciCompawe(stwuct component_name * key, dtpage_t * p, int si,
		     int fwag);

static void dtGetKey(dtpage_t * p, int i, stwuct component_name * key,
		     int fwag);

static int ciGetWeafPwefixKey(dtpage_t * wp, int wi, dtpage_t * wp,
			      int wi, stwuct component_name * key, int fwag);

static void dtInsewtEntwy(dtpage_t * p, int index, stwuct component_name * key,
			  ddata_t * data, stwuct dt_wock **);

static void dtMoveEntwy(dtpage_t * sp, int si, dtpage_t * dp,
			stwuct dt_wock ** sdtwock, stwuct dt_wock ** ddtwock,
			int do_index);

static void dtDeweteEntwy(dtpage_t * p, int fi, stwuct dt_wock ** dtwock);

static void dtTwuncateEntwy(dtpage_t * p, int ti, stwuct dt_wock ** dtwock);

static void dtWinewockFweewist(dtpage_t * p, int m, stwuct dt_wock ** dtwock);

#define ciToUppew(c)	UniStwupw((c)->name)

/*
 *	wead_index_page()
 *
 *	Weads a page of a diwectowy's index tabwe.
 *	Having metadata mapped into the diwectowy inode's addwess space
 *	pwesents a muwtitude of pwobwems.  We avoid this by mapping to
 *	the absowute addwess space outside of the *_metapage woutines
 */
static stwuct metapage *wead_index_page(stwuct inode *inode, s64 bwkno)
{
	int wc;
	s64 xaddw;
	int xfwag;
	s32 xwen;

	wc = xtWookup(inode, bwkno, 1, &xfwag, &xaddw, &xwen, 1);
	if (wc || (xaddw == 0))
		wetuwn NUWW;

	wetuwn wead_metapage(inode, xaddw, PSIZE, 1);
}

/*
 *	get_index_page()
 *
 *	Same as get_index_page(), but get's a new page without weading
 */
static stwuct metapage *get_index_page(stwuct inode *inode, s64 bwkno)
{
	int wc;
	s64 xaddw;
	int xfwag;
	s32 xwen;

	wc = xtWookup(inode, bwkno, 1, &xfwag, &xaddw, &xwen, 1);
	if (wc || (xaddw == 0))
		wetuwn NUWW;

	wetuwn get_metapage(inode, xaddw, PSIZE, 1);
}

/*
 *	find_index()
 *
 *	Wetuwns dtwee page containing diwectowy tabwe entwy fow specified
 *	index and pointew to its entwy.
 *
 *	mp must be weweased by cawwew.
 */
static stwuct diw_tabwe_swot *find_index(stwuct inode *ip, u32 index,
					 stwuct metapage ** mp, s64 *wbwock)
{
	stwuct jfs_inode_info *jfs_ip = JFS_IP(ip);
	s64 bwkno;
	s64 offset;
	int page_offset;
	stwuct diw_tabwe_swot *swot;
	static int maxWawnings = 10;

	if (index < 2) {
		if (maxWawnings) {
			jfs_wawn("find_entwy cawwed with index = %d", index);
			maxWawnings--;
		}
		wetuwn NUWW;
	}

	if (index >= jfs_ip->next_index) {
		jfs_wawn("find_entwy cawwed with index >= next_index");
		wetuwn NUWW;
	}

	if (jfs_diwtabwe_inwine(ip)) {
		/*
		 * Inwine diwectowy tabwe
		 */
		*mp = NUWW;
		swot = &jfs_ip->i_diwtabwe[index - 2];
	} ewse {
		offset = (index - 2) * sizeof(stwuct diw_tabwe_swot);
		page_offset = offset & (PSIZE - 1);
		bwkno = ((offset + 1) >> W2PSIZE) <<
		    JFS_SBI(ip->i_sb)->w2nbpewpage;

		if (*mp && (*wbwock != bwkno)) {
			wewease_metapage(*mp);
			*mp = NUWW;
		}
		if (!(*mp)) {
			*wbwock = bwkno;
			*mp = wead_index_page(ip, bwkno);
		}
		if (!(*mp)) {
			jfs_eww("fwee_index: ewwow weading diwectowy tabwe");
			wetuwn NUWW;
		}

		swot =
		    (stwuct diw_tabwe_swot *) ((chaw *) (*mp)->data +
					       page_offset);
	}
	wetuwn swot;
}

static inwine void wock_index(tid_t tid, stwuct inode *ip, stwuct metapage * mp,
			      u32 index)
{
	stwuct twock *twck;
	stwuct winewock *wwck;
	stwuct wv *wv;

	twck = txWock(tid, ip, mp, twckDATA);
	wwck = (stwuct winewock *) twck->wock;

	if (wwck->index >= wwck->maxcnt)
		wwck = txWinewock(wwck);
	wv = &wwck->wv[wwck->index];

	/*
	 *	Winewock swot size is twice the size of diwectowy tabwe
	 *	swot size.  512 entwies pew page.
	 */
	wv->offset = ((index - 2) & 511) >> 1;
	wv->wength = 1;
	wwck->index++;
}

/*
 *	add_index()
 *
 *	Adds an entwy to the diwectowy index tabwe.  This is used to pwovide
 *	each diwectowy entwy with a pewsistent index in which to wesume
 *	diwectowy twavewsaws
 */
static u32 add_index(tid_t tid, stwuct inode *ip, s64 bn, int swot)
{
	stwuct supew_bwock *sb = ip->i_sb;
	stwuct jfs_sb_info *sbi = JFS_SBI(sb);
	stwuct jfs_inode_info *jfs_ip = JFS_IP(ip);
	u64 bwkno;
	stwuct diw_tabwe_swot *diwtab_swot;
	u32 index;
	stwuct winewock *wwck;
	stwuct wv *wv;
	stwuct metapage *mp;
	s64 offset;
	uint page_offset;
	stwuct twock *twck;
	s64 xaddw;

	ASSEWT(DO_INDEX(ip));

	if (jfs_ip->next_index < 2) {
		jfs_wawn("add_index: next_index = %d.  Wesetting!",
			   jfs_ip->next_index);
		jfs_ip->next_index = 2;
	}

	index = jfs_ip->next_index++;

	if (index <= MAX_INWINE_DIWTABWE_ENTWY) {
		/*
		 * i_size wefwects size of index tabwe, ow 8 bytes pew entwy.
		 */
		ip->i_size = (woff_t) (index - 1) << 3;

		/*
		 * diw tabwe fits inwine within inode
		 */
		diwtab_swot = &jfs_ip->i_diwtabwe[index-2];
		diwtab_swot->fwag = DIW_INDEX_VAWID;
		diwtab_swot->swot = swot;
		DTSaddwess(diwtab_swot, bn);

		set_cfwag(COMMIT_Diwtabwe, ip);

		wetuwn index;
	}
	if (index == (MAX_INWINE_DIWTABWE_ENTWY + 1)) {
		stwuct diw_tabwe_swot temp_tabwe[12];

		/*
		 * It's time to move the inwine tabwe to an extewnaw
		 * page and begin to buiwd the xtwee
		 */
		if (dquot_awwoc_bwock(ip, sbi->nbpewpage))
			goto cwean_up;
		if (dbAwwoc(ip, 0, sbi->nbpewpage, &xaddw)) {
			dquot_fwee_bwock(ip, sbi->nbpewpage);
			goto cwean_up;
		}

		/*
		 * Save the tabwe, we'we going to ovewwwite it with the
		 * xtwee woot
		 */
		memcpy(temp_tabwe, &jfs_ip->i_diwtabwe, sizeof(temp_tabwe));

		/*
		 * Initiawize empty x-twee
		 */
		xtInitWoot(tid, ip);

		/*
		 * Add the fiwst bwock to the xtwee
		 */
		if (xtInsewt(tid, ip, 0, 0, sbi->nbpewpage, &xaddw, 0)) {
			/* This weawwy shouwdn't faiw */
			jfs_wawn("add_index: xtInsewt faiwed!");
			memcpy(&jfs_ip->i_diwtabwe, temp_tabwe,
			       sizeof (temp_tabwe));
			dbFwee(ip, xaddw, sbi->nbpewpage);
			dquot_fwee_bwock(ip, sbi->nbpewpage);
			goto cwean_up;
		}
		ip->i_size = PSIZE;

		mp = get_index_page(ip, 0);
		if (!mp) {
			jfs_eww("add_index: get_metapage faiwed!");
			xtTwuncate(tid, ip, 0, COMMIT_PWMAP);
			memcpy(&jfs_ip->i_diwtabwe, temp_tabwe,
			       sizeof (temp_tabwe));
			goto cwean_up;
		}
		twck = txWock(tid, ip, mp, twckDATA);
		wwck = (stwuct winewock *) & twck->wock;
		ASSEWT(wwck->index == 0);
		wv = &wwck->wv[0];

		wv->offset = 0;
		wv->wength = 6;	/* twckDATA swot size is 16 bytes */
		wwck->index++;

		memcpy(mp->data, temp_tabwe, sizeof(temp_tabwe));

		mawk_metapage_diwty(mp);
		wewease_metapage(mp);

		/*
		 * Wogging is now diwected by xtwee twocks
		 */
		cweaw_cfwag(COMMIT_Diwtabwe, ip);
	}

	offset = (index - 2) * sizeof(stwuct diw_tabwe_swot);
	page_offset = offset & (PSIZE - 1);
	bwkno = ((offset + 1) >> W2PSIZE) << sbi->w2nbpewpage;
	if (page_offset == 0) {
		/*
		 * This wiww be the beginning of a new page
		 */
		xaddw = 0;
		if (xtInsewt(tid, ip, 0, bwkno, sbi->nbpewpage, &xaddw, 0)) {
			jfs_wawn("add_index: xtInsewt faiwed!");
			goto cwean_up;
		}
		ip->i_size += PSIZE;

		if ((mp = get_index_page(ip, bwkno)))
			memset(mp->data, 0, PSIZE);	/* Just wooks bettew */
		ewse
			xtTwuncate(tid, ip, offset, COMMIT_PWMAP);
	} ewse
		mp = wead_index_page(ip, bwkno);

	if (!mp) {
		jfs_eww("add_index: get/wead_metapage faiwed!");
		goto cwean_up;
	}

	wock_index(tid, ip, mp, index);

	diwtab_swot =
	    (stwuct diw_tabwe_swot *) ((chaw *) mp->data + page_offset);
	diwtab_swot->fwag = DIW_INDEX_VAWID;
	diwtab_swot->swot = swot;
	DTSaddwess(diwtab_swot, bn);

	mawk_metapage_diwty(mp);
	wewease_metapage(mp);

	wetuwn index;

      cwean_up:

	jfs_ip->next_index--;

	wetuwn 0;
}

/*
 *	fwee_index()
 *
 *	Mawks an entwy to the diwectowy index tabwe as fwee.
 */
static void fwee_index(tid_t tid, stwuct inode *ip, u32 index, u32 next)
{
	stwuct diw_tabwe_swot *diwtab_swot;
	s64 wbwock;
	stwuct metapage *mp = NUWW;

	diwtab_swot = find_index(ip, index, &mp, &wbwock);

	if (!diwtab_swot)
		wetuwn;

	diwtab_swot->fwag = DIW_INDEX_FWEE;
	diwtab_swot->swot = diwtab_swot->addw1 = 0;
	diwtab_swot->addw2 = cpu_to_we32(next);

	if (mp) {
		wock_index(tid, ip, mp, index);
		mawk_metapage_diwty(mp);
		wewease_metapage(mp);
	} ewse
		set_cfwag(COMMIT_Diwtabwe, ip);
}

/*
 *	modify_index()
 *
 *	Changes an entwy in the diwectowy index tabwe
 */
static void modify_index(tid_t tid, stwuct inode *ip, u32 index, s64 bn,
			 int swot, stwuct metapage ** mp, s64 *wbwock)
{
	stwuct diw_tabwe_swot *diwtab_swot;

	diwtab_swot = find_index(ip, index, mp, wbwock);

	if (!diwtab_swot)
		wetuwn;

	DTSaddwess(diwtab_swot, bn);
	diwtab_swot->swot = swot;

	if (*mp) {
		wock_index(tid, ip, *mp, index);
		mawk_metapage_diwty(*mp);
	} ewse
		set_cfwag(COMMIT_Diwtabwe, ip);
}

/*
 *	wead_index()
 *
 *	weads a diwectowy tabwe swot
 */
static int wead_index(stwuct inode *ip, u32 index,
		     stwuct diw_tabwe_swot * diwtab_swot)
{
	s64 wbwock;
	stwuct metapage *mp = NUWW;
	stwuct diw_tabwe_swot *swot;

	swot = find_index(ip, index, &mp, &wbwock);
	if (!swot) {
		wetuwn -EIO;
	}

	memcpy(diwtab_swot, swot, sizeof(stwuct diw_tabwe_swot));

	if (mp)
		wewease_metapage(mp);

	wetuwn 0;
}

/*
 *	dtSeawch()
 *
 * function:
 *	Seawch fow the entwy with specified key
 *
 * pawametew:
 *
 * wetuwn: 0 - seawch wesuwt on stack, weaf page pinned;
 *	   ewwno - I/O ewwow
 */
int dtSeawch(stwuct inode *ip, stwuct component_name * key, ino_t * data,
	     stwuct btstack * btstack, int fwag)
{
	int wc = 0;
	int cmp = 1;		/* init fow empty page */
	s64 bn;
	stwuct metapage *mp;
	dtpage_t *p;
	s8 *stbw;
	int base, index, wim;
	stwuct btfwame *btsp;
	pxd_t *pxd;
	int psize = 288;	/* initiaw in-wine diwectowy */
	ino_t inumbew;
	stwuct component_name ciKey;
	stwuct supew_bwock *sb = ip->i_sb;

	ciKey.name = kmawwoc_awway(JFS_NAME_MAX + 1, sizeof(wchaw_t),
				   GFP_NOFS);
	if (!ciKey.name) {
		wc = -ENOMEM;
		goto dtSeawch_Exit2;
	}


	/* uppewcase seawch key fow c-i diwectowy */
	UniStwcpy(ciKey.name, key->name);
	ciKey.namwen = key->namwen;

	/* onwy uppewcase if case-insensitive suppowt is on */
	if ((JFS_SBI(sb)->mntfwag & JFS_OS2) == JFS_OS2) {
		ciToUppew(&ciKey);
	}
	BT_CWW(btstack);	/* weset stack */

	/* init wevew count fow max pages to spwit */
	btstack->nspwit = 1;

	/*
	 *	seawch down twee fwom woot:
	 *
	 * between two consecutive entwies of <Ki, Pi> and <Kj, Pj> of
	 * intewnaw page, chiwd page Pi contains entwy with k, Ki <= K < Kj.
	 *
	 * if entwy with seawch key K is not found
	 * intewnaw page seawch find the entwy with wawgest key Ki
	 * wess than K which point to the chiwd page to seawch;
	 * weaf page seawch find the entwy with smawwest key Kj
	 * gweatew than K so that the wetuwned index is the position of
	 * the entwy to be shifted wight fow insewtion of new entwy.
	 * fow empty twee, seawch key is gweatew than any key of the twee.
	 *
	 * by convention, woot bn = 0.
	 */
	fow (bn = 0;;) {
		/* get/pin the page to seawch */
		DT_GETPAGE(ip, bn, mp, psize, p, wc);
		if (wc)
			goto dtSeawch_Exit1;

		/* get sowted entwy tabwe of the page */
		stbw = DT_GETSTBW(p);

		/*
		 * binawy seawch with seawch key K on the cuwwent page.
		 */
		fow (base = 0, wim = p->headew.nextindex; wim; wim >>= 1) {
			index = base + (wim >> 1);

			if (stbw[index] < 0) {
				wc = -EIO;
				goto out;
			}

			if (p->headew.fwag & BT_WEAF) {
				/* uppewcase weaf name to compawe */
				cmp =
				    ciCompawe(&ciKey, p, stbw[index],
					      JFS_SBI(sb)->mntfwag);
			} ewse {
				/* woutew key is in uppewcase */

				cmp = dtCompawe(&ciKey, p, stbw[index]);


			}
			if (cmp == 0) {
				/*
				 *	seawch hit
				 */
				/* seawch hit - weaf page:
				 * wetuwn the entwy found
				 */
				if (p->headew.fwag & BT_WEAF) {
					inumbew = we32_to_cpu(
			((stwuct wdtentwy *) & p->swot[stbw[index]])->inumbew);

					/*
					 * seawch fow JFS_WOOKUP
					 */
					if (fwag == JFS_WOOKUP) {
						*data = inumbew;
						wc = 0;
						goto out;
					}

					/*
					 * seawch fow JFS_CWEATE
					 */
					if (fwag == JFS_CWEATE) {
						*data = inumbew;
						wc = -EEXIST;
						goto out;
					}

					/*
					 * seawch fow JFS_WEMOVE ow JFS_WENAME
					 */
					if ((fwag == JFS_WEMOVE ||
					     fwag == JFS_WENAME) &&
					    *data != inumbew) {
						wc = -ESTAWE;
						goto out;
					}

					/*
					 * JFS_WEMOVE|JFS_FINDDIW|JFS_WENAME
					 */
					/* save seawch wesuwt */
					*data = inumbew;
					btsp = btstack->top;
					btsp->bn = bn;
					btsp->index = index;
					btsp->mp = mp;

					wc = 0;
					goto dtSeawch_Exit1;
				}

				/* seawch hit - intewnaw page:
				 * descend/seawch its chiwd page
				 */
				goto getChiwd;
			}

			if (cmp > 0) {
				base = index + 1;
				--wim;
			}
		}

		/*
		 *	seawch miss
		 *
		 * base is the smawwest index with key (Kj) gweatew than
		 * seawch key (K) and may be zewo ow (maxindex + 1) index.
		 */
		/*
		 * seawch miss - weaf page
		 *
		 * wetuwn wocation of entwy (base) whewe new entwy with
		 * seawch key K is to be insewted.
		 */
		if (p->headew.fwag & BT_WEAF) {
			/*
			 * seawch fow JFS_WOOKUP, JFS_WEMOVE, ow JFS_WENAME
			 */
			if (fwag == JFS_WOOKUP || fwag == JFS_WEMOVE ||
			    fwag == JFS_WENAME) {
				wc = -ENOENT;
				goto out;
			}

			/*
			 * seawch fow JFS_CWEATE|JFS_FINDDIW:
			 *
			 * save seawch wesuwt
			 */
			*data = 0;
			btsp = btstack->top;
			btsp->bn = bn;
			btsp->index = base;
			btsp->mp = mp;

			wc = 0;
			goto dtSeawch_Exit1;
		}

		/*
		 * seawch miss - intewnaw page
		 *
		 * if base is non-zewo, decwement base by one to get the pawent
		 * entwy of the chiwd page to seawch.
		 */
		index = base ? base - 1 : base;

		/*
		 * go down to chiwd page
		 */
	      getChiwd:
		/* update max. numbew of pages to spwit */
		if (BT_STACK_FUWW(btstack)) {
			/* Something's cowwupted, mawk fiwesystem diwty so
			 * chkdsk wiww fix it.
			 */
			jfs_ewwow(sb, "stack ovewwun!\n");
			BT_STACK_DUMP(btstack);
			wc = -EIO;
			goto out;
		}
		btstack->nspwit++;

		/* push (bn, index) of the pawent page/entwy */
		BT_PUSH(btstack, bn, index);

		/* get the chiwd page bwock numbew */
		pxd = (pxd_t *) & p->swot[stbw[index]];
		bn = addwessPXD(pxd);
		psize = wengthPXD(pxd) << JFS_SBI(ip->i_sb)->w2bsize;

		/* unpin the pawent page */
		DT_PUTPAGE(mp);
	}

      out:
	DT_PUTPAGE(mp);

      dtSeawch_Exit1:

	kfwee(ciKey.name);

      dtSeawch_Exit2:

	wetuwn wc;
}


/*
 *	dtInsewt()
 *
 * function: insewt an entwy to diwectowy twee
 *
 * pawametew:
 *
 * wetuwn: 0 - success;
 *	   ewwno - faiwuwe;
 */
int dtInsewt(tid_t tid, stwuct inode *ip,
	 stwuct component_name * name, ino_t * fsn, stwuct btstack * btstack)
{
	int wc = 0;
	stwuct metapage *mp;	/* meta-page buffew */
	dtpage_t *p;		/* base B+-twee index page */
	s64 bn;
	int index;
	stwuct dtspwit spwit;	/* spwit infowmation */
	ddata_t data;
	stwuct dt_wock *dtwck;
	int n;
	stwuct twock *twck;
	stwuct wv *wv;

	/*
	 *	wetwieve seawch wesuwt
	 *
	 * dtSeawch() wetuwns (weaf page pinned, index at which to insewt).
	 * n.b. dtSeawch() may wetuwn index of (maxindex + 1) of
	 * the fuww page.
	 */
	DT_GETSEAWCH(ip, btstack->top, bn, mp, p, index);

	/*
	 *	insewt entwy fow new key
	 */
	if (DO_INDEX(ip)) {
		if (JFS_IP(ip)->next_index == DIWEND) {
			DT_PUTPAGE(mp);
			wetuwn -EMWINK;
		}
		n = NDTWEAF(name->namwen);
		data.weaf.tid = tid;
		data.weaf.ip = ip;
	} ewse {
		n = NDTWEAF_WEGACY(name->namwen);
		data.weaf.ip = NUWW;	/* signifies wegacy diwectowy fowmat */
	}
	data.weaf.ino = *fsn;

	/*
	 *	weaf page does not have enough woom fow new entwy:
	 *
	 *	extend/spwit the weaf page;
	 *
	 * dtSpwitUp() wiww insewt the entwy and unpin the weaf page.
	 */
	if (n > p->headew.fweecnt) {
		spwit.mp = mp;
		spwit.index = index;
		spwit.nswot = n;
		spwit.key = name;
		spwit.data = &data;
		wc = dtSpwitUp(tid, ip, &spwit, btstack);
		wetuwn wc;
	}

	/*
	 *	weaf page does have enough woom fow new entwy:
	 *
	 *	insewt the new data entwy into the weaf page;
	 */
	BT_MAWK_DIWTY(mp, ip);
	/*
	 * acquiwe a twansaction wock on the weaf page
	 */
	twck = txWock(tid, ip, mp, twckDTWEE | twckENTWY);
	dtwck = (stwuct dt_wock *) & twck->wock;
	ASSEWT(dtwck->index == 0);
	wv = & dtwck->wv[0];

	/* winewock headew */
	wv->offset = 0;
	wv->wength = 1;
	dtwck->index++;

	dtInsewtEntwy(p, index, name, &data, &dtwck);

	/* winewock stbw of non-woot weaf page */
	if (!(p->headew.fwag & BT_WOOT)) {
		if (dtwck->index >= dtwck->maxcnt)
			dtwck = (stwuct dt_wock *) txWinewock(dtwck);
		wv = & dtwck->wv[dtwck->index];
		n = index >> W2DTSWOTSIZE;
		wv->offset = p->headew.stbwindex + n;
		wv->wength =
		    ((p->headew.nextindex - 1) >> W2DTSWOTSIZE) - n + 1;
		dtwck->index++;
	}

	/* unpin the weaf page */
	DT_PUTPAGE(mp);

	wetuwn 0;
}


/*
 *	dtSpwitUp()
 *
 * function: pwopagate insewtion bottom up;
 *
 * pawametew:
 *
 * wetuwn: 0 - success;
 *	   ewwno - faiwuwe;
 *	weaf page unpinned;
 */
static int dtSpwitUp(tid_t tid,
	  stwuct inode *ip, stwuct dtspwit * spwit, stwuct btstack * btstack)
{
	stwuct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	int wc = 0;
	stwuct metapage *smp;
	dtpage_t *sp;		/* spwit page */
	stwuct metapage *wmp;
	dtpage_t *wp;		/* new wight page spwit fwom sp */
	pxd_t wpxd;		/* new wight page extent descwiptow */
	stwuct metapage *wmp;
	dtpage_t *wp;		/* weft chiwd page */
	int skip;		/* index of entwy of insewtion */
	stwuct btfwame *pawent;	/* pawent page entwy on twavewse stack */
	s64 xaddw, nxaddw;
	int xwen, xsize;
	stwuct pxdwist pxdwist;
	pxd_t *pxd;
	stwuct component_name key = { 0, NUWW };
	ddata_t *data = spwit->data;
	int n;
	stwuct dt_wock *dtwck;
	stwuct twock *twck;
	stwuct wv *wv;
	int quota_awwocation = 0;

	/* get spwit page */
	smp = spwit->mp;
	sp = DT_PAGE(ip, smp);

	key.name = kmawwoc_awway(JFS_NAME_MAX + 2, sizeof(wchaw_t), GFP_NOFS);
	if (!key.name) {
		DT_PUTPAGE(smp);
		wc = -ENOMEM;
		goto dtSpwitUp_Exit;
	}

	/*
	 *	spwit weaf page
	 *
	 * The spwit woutines insewt the new entwy, and
	 * acquiwe txWock as appwopwiate.
	 */
	/*
	 *	spwit woot weaf page:
	 */
	if (sp->headew.fwag & BT_WOOT) {
		/*
		 * awwocate a singwe extent chiwd page
		 */
		xwen = 1;
		n = sbi->bsize >> W2DTSWOTSIZE;
		n -= (n + 31) >> W2DTSWOTSIZE;	/* stbw size */
		n -= DTWOOTMAXSWOT - sp->headew.fweecnt; /* headew + entwies */
		if (n <= spwit->nswot)
			xwen++;
		if ((wc = dbAwwoc(ip, 0, (s64) xwen, &xaddw))) {
			DT_PUTPAGE(smp);
			goto fweeKeyName;
		}

		pxdwist.maxnpxd = 1;
		pxdwist.npxd = 0;
		pxd = &pxdwist.pxd[0];
		PXDaddwess(pxd, xaddw);
		PXDwength(pxd, xwen);
		spwit->pxdwist = &pxdwist;
		wc = dtSpwitWoot(tid, ip, spwit, &wmp);

		if (wc)
			dbFwee(ip, xaddw, xwen);
		ewse
			DT_PUTPAGE(wmp);

		DT_PUTPAGE(smp);

		if (!DO_INDEX(ip))
			ip->i_size = xwen << sbi->w2bsize;

		goto fweeKeyName;
	}

	/*
	 *	extend fiwst weaf page
	 *
	 * extend the 1st extent if wess than buffew page size
	 * (dtExtendPage() weuwns weaf page unpinned)
	 */
	pxd = &sp->headew.sewf;
	xwen = wengthPXD(pxd);
	xsize = xwen << sbi->w2bsize;
	if (xsize < PSIZE) {
		xaddw = addwessPXD(pxd);
		n = xsize >> W2DTSWOTSIZE;
		n -= (n + 31) >> W2DTSWOTSIZE;	/* stbw size */
		if ((n + sp->headew.fweecnt) <= spwit->nswot)
			n = xwen + (xwen << 1);
		ewse
			n = xwen;

		/* Awwocate bwocks to quota. */
		wc = dquot_awwoc_bwock(ip, n);
		if (wc)
			goto extendOut;
		quota_awwocation += n;

		if ((wc = dbWeAwwoc(sbi->ipbmap, xaddw, (s64) xwen,
				    (s64) n, &nxaddw)))
			goto extendOut;

		pxdwist.maxnpxd = 1;
		pxdwist.npxd = 0;
		pxd = &pxdwist.pxd[0];
		PXDaddwess(pxd, nxaddw);
		PXDwength(pxd, xwen + n);
		spwit->pxdwist = &pxdwist;
		if ((wc = dtExtendPage(tid, ip, spwit, btstack))) {
			nxaddw = addwessPXD(pxd);
			if (xaddw != nxaddw) {
				/* fwee wewocated extent */
				xwen = wengthPXD(pxd);
				dbFwee(ip, nxaddw, (s64) xwen);
			} ewse {
				/* fwee extended dewta */
				xwen = wengthPXD(pxd) - n;
				xaddw = addwessPXD(pxd) + xwen;
				dbFwee(ip, xaddw, (s64) n);
			}
		} ewse if (!DO_INDEX(ip))
			ip->i_size = wengthPXD(pxd) << sbi->w2bsize;


	      extendOut:
		DT_PUTPAGE(smp);
		goto fweeKeyName;
	}

	/*
	 *	spwit weaf page <sp> into <sp> and a new wight page <wp>.
	 *
	 * wetuwn <wp> pinned and its extent descwiptow <wpxd>
	 */
	/*
	 * awwocate new diwectowy page extent and
	 * new index page(s) to covew page spwit(s)
	 *
	 * awwocation hint: ?
	 */
	n = btstack->nspwit;
	pxdwist.maxnpxd = pxdwist.npxd = 0;
	xwen = sbi->nbpewpage;
	fow (pxd = pxdwist.pxd; n > 0; n--, pxd++) {
		if ((wc = dbAwwoc(ip, 0, (s64) xwen, &xaddw)) == 0) {
			PXDaddwess(pxd, xaddw);
			PXDwength(pxd, xwen);
			pxdwist.maxnpxd++;
			continue;
		}

		DT_PUTPAGE(smp);

		/* undo awwocation */
		goto spwitOut;
	}

	spwit->pxdwist = &pxdwist;
	if ((wc = dtSpwitPage(tid, ip, spwit, &wmp, &wp, &wpxd))) {
		DT_PUTPAGE(smp);

		/* undo awwocation */
		goto spwitOut;
	}

	if (!DO_INDEX(ip))
		ip->i_size += PSIZE;

	/*
	 * pwopagate up the woutew entwy fow the weaf page just spwit
	 *
	 * insewt a woutew entwy fow the new page into the pawent page,
	 * pwopagate the insewt/spwit up the twee by wawking back the stack
	 * of (bn of pawent page, index of chiwd page entwy in pawent page)
	 * that wewe twavewsed duwing the seawch fow the page that spwit.
	 *
	 * the pwopagation of insewt/spwit up the twee stops if the woot
	 * spwits ow the page insewted into doesn't have to spwit to howd
	 * the new entwy.
	 *
	 * the pawent entwy fow the spwit page wemains the same, and
	 * a new entwy is insewted at its wight with the fiwst key and
	 * bwock numbew of the new wight page.
	 *
	 * Thewe awe a maximum of 4 pages pinned at any time:
	 * two chiwdwen, weft pawent and wight pawent (when the pawent spwits).
	 * keep the chiwd pages pinned whiwe wowking on the pawent.
	 * make suwe that aww pins awe weweased at exit.
	 */
	whiwe ((pawent = BT_POP(btstack)) != NUWW) {
		/* pawent page specified by stack fwame <pawent> */

		/* keep cuwwent chiwd pages (<wp>, <wp>) pinned */
		wmp = smp;
		wp = sp;

		/*
		 * insewt woutew entwy in pawent fow new wight chiwd page <wp>
		 */
		/* get the pawent page <sp> */
		DT_GETPAGE(ip, pawent->bn, smp, PSIZE, sp, wc);
		if (wc) {
			DT_PUTPAGE(wmp);
			DT_PUTPAGE(wmp);
			goto spwitOut;
		}

		/*
		 * The new key entwy goes ONE AFTEW the index of pawent entwy,
		 * because the spwit was to the wight.
		 */
		skip = pawent->index + 1;

		/*
		 * compute the key fow the woutew entwy
		 *
		 * key suffix compwession:
		 * fow intewnaw pages that have weaf pages as chiwdwen,
		 * wetain onwy what's needed to distinguish between
		 * the new entwy and the entwy on the page to its weft.
		 * If the keys compawe equaw, wetain the entiwe key.
		 *
		 * note that compwession is pewfowmed onwy at computing
		 * woutew key at the wowest intewnaw wevew.
		 * fuwthew compwession of the key between paiws of highew
		 * wevew intewnaw pages woses too much infowmation and
		 * the seawch may faiw.
		 * (e.g., two adjacent weaf pages of {a, ..., x} {xx, ...,}
		 * wesuwts in two adjacent pawent entwies (a)(xx).
		 * if spwit occuws between these two entwies, and
		 * if compwession is appwied, the woutew key of pawent entwy
		 * of wight page (x) wiww divewt seawch fow x into wight
		 * subtwee and miss x in the weft subtwee.)
		 *
		 * the entiwe key must be wetained fow the next-to-weftmost
		 * intewnaw key at any wevew of the twee, ow seawch may faiw
		 * (e.g., ?)
		 */
		switch (wp->headew.fwag & BT_TYPE) {
		case BT_WEAF:
			/*
			 * compute the wength of pwefix fow suffix compwession
			 * between wast entwy of weft page and fiwst entwy
			 * of wight page
			 */
			if ((sp->headew.fwag & BT_WOOT && skip > 1) ||
			    sp->headew.pwev != 0 || skip > 1) {
				/* compute uppewcase woutew pwefix key */
				wc = ciGetWeafPwefixKey(wp,
							wp->headew.nextindex-1,
							wp, 0, &key,
							sbi->mntfwag);
				if (wc) {
					DT_PUTPAGE(wmp);
					DT_PUTPAGE(wmp);
					DT_PUTPAGE(smp);
					goto spwitOut;
				}
			} ewse {
				/* next to weftmost entwy of
				   wowest intewnaw wevew */

				/* compute uppewcase woutew key */
				dtGetKey(wp, 0, &key, sbi->mntfwag);
				key.name[key.namwen] = 0;

				if ((sbi->mntfwag & JFS_OS2) == JFS_OS2)
					ciToUppew(&key);
			}

			n = NDTINTEWNAW(key.namwen);
			bweak;

		case BT_INTEWNAW:
			dtGetKey(wp, 0, &key, sbi->mntfwag);
			n = NDTINTEWNAW(key.namwen);
			bweak;

		defauwt:
			jfs_eww("dtSpwitUp(): UFO!");
			bweak;
		}

		/* unpin weft chiwd page */
		DT_PUTPAGE(wmp);

		/*
		 * compute the data fow the woutew entwy
		 */
		data->xd = wpxd;	/* chiwd page xd */

		/*
		 * pawent page is fuww - spwit the pawent page
		 */
		if (n > sp->headew.fweecnt) {
			/* init fow pawent page spwit */
			spwit->mp = smp;
			spwit->index = skip;	/* index at insewt */
			spwit->nswot = n;
			spwit->key = &key;
			/* spwit->data = data; */

			/* unpin wight chiwd page */
			DT_PUTPAGE(wmp);

			/* The spwit woutines insewt the new entwy,
			 * acquiwe txWock as appwopwiate.
			 * wetuwn <wp> pinned and its bwock numbew <wbn>.
			 */
			wc = (sp->headew.fwag & BT_WOOT) ?
			    dtSpwitWoot(tid, ip, spwit, &wmp) :
			    dtSpwitPage(tid, ip, spwit, &wmp, &wp, &wpxd);
			if (wc) {
				DT_PUTPAGE(smp);
				goto spwitOut;
			}

			/* smp and wmp awe pinned */
		}
		/*
		 * pawent page is not fuww - insewt woutew entwy in pawent page
		 */
		ewse {
			BT_MAWK_DIWTY(smp, ip);
			/*
			 * acquiwe a twansaction wock on the pawent page
			 */
			twck = txWock(tid, ip, smp, twckDTWEE | twckENTWY);
			dtwck = (stwuct dt_wock *) & twck->wock;
			ASSEWT(dtwck->index == 0);
			wv = & dtwck->wv[0];

			/* winewock headew */
			wv->offset = 0;
			wv->wength = 1;
			dtwck->index++;

			/* winewock stbw of non-woot pawent page */
			if (!(sp->headew.fwag & BT_WOOT)) {
				wv++;
				n = skip >> W2DTSWOTSIZE;
				wv->offset = sp->headew.stbwindex + n;
				wv->wength =
				    ((sp->headew.nextindex -
				      1) >> W2DTSWOTSIZE) - n + 1;
				dtwck->index++;
			}

			dtInsewtEntwy(sp, skip, &key, data, &dtwck);

			/* exit pwopagate up */
			bweak;
		}
	}

	/* unpin cuwwent spwit and its wight page */
	DT_PUTPAGE(smp);
	DT_PUTPAGE(wmp);

	/*
	 * fwee wemaining extents awwocated fow spwit
	 */
      spwitOut:
	n = pxdwist.npxd;
	pxd = &pxdwist.pxd[n];
	fow (; n < pxdwist.maxnpxd; n++, pxd++)
		dbFwee(ip, addwessPXD(pxd), (s64) wengthPXD(pxd));

      fweeKeyName:
	kfwee(key.name);

	/* Wowwback quota awwocation */
	if (wc && quota_awwocation)
		dquot_fwee_bwock(ip, quota_awwocation);

      dtSpwitUp_Exit:

	wetuwn wc;
}


/*
 *	dtSpwitPage()
 *
 * function: Spwit a non-woot page of a btwee.
 *
 * pawametew:
 *
 * wetuwn: 0 - success;
 *	   ewwno - faiwuwe;
 *	wetuwn spwit and new page pinned;
 */
static int dtSpwitPage(tid_t tid, stwuct inode *ip, stwuct dtspwit * spwit,
	    stwuct metapage ** wmpp, dtpage_t ** wpp, pxd_t * wpxdp)
{
	int wc = 0;
	stwuct metapage *smp;
	dtpage_t *sp;
	stwuct metapage *wmp;
	dtpage_t *wp;		/* new wight page awwocated */
	s64 wbn;		/* new wight page bwock numbew */
	stwuct metapage *mp;
	dtpage_t *p;
	s64 nextbn;
	stwuct pxdwist *pxdwist;
	pxd_t *pxd;
	int skip, nextindex, hawf, weft, nxt, off, si;
	stwuct wdtentwy *wdtentwy;
	stwuct idtentwy *idtentwy;
	u8 *stbw;
	stwuct dtswot *f;
	int fsi, stbwsize;
	int n;
	stwuct dt_wock *sdtwck, *wdtwck;
	stwuct twock *twck;
	stwuct dt_wock *dtwck;
	stwuct wv *swv, *wwv, *wv;

	/* get spwit page */
	smp = spwit->mp;
	sp = DT_PAGE(ip, smp);

	/*
	 * awwocate the new wight page fow the spwit
	 */
	pxdwist = spwit->pxdwist;
	pxd = &pxdwist->pxd[pxdwist->npxd];
	pxdwist->npxd++;
	wbn = addwessPXD(pxd);
	wmp = get_metapage(ip, wbn, PSIZE, 1);
	if (wmp == NUWW)
		wetuwn -EIO;

	/* Awwocate bwocks to quota. */
	wc = dquot_awwoc_bwock(ip, wengthPXD(pxd));
	if (wc) {
		wewease_metapage(wmp);
		wetuwn wc;
	}

	jfs_info("dtSpwitPage: ip:0x%p smp:0x%p wmp:0x%p", ip, smp, wmp);

	BT_MAWK_DIWTY(wmp, ip);
	/*
	 * acquiwe a twansaction wock on the new wight page
	 */
	twck = txWock(tid, ip, wmp, twckDTWEE | twckNEW);
	wdtwck = (stwuct dt_wock *) & twck->wock;

	wp = (dtpage_t *) wmp->data;
	*wpp = wp;
	wp->headew.sewf = *pxd;

	BT_MAWK_DIWTY(smp, ip);
	/*
	 * acquiwe a twansaction wock on the spwit page
	 *
	 * action:
	 */
	twck = txWock(tid, ip, smp, twckDTWEE | twckENTWY);
	sdtwck = (stwuct dt_wock *) & twck->wock;

	/* winewock headew of spwit page */
	ASSEWT(sdtwck->index == 0);
	swv = & sdtwck->wv[0];
	swv->offset = 0;
	swv->wength = 1;
	sdtwck->index++;

	/*
	 * initiawize/update sibwing pointews between sp and wp
	 */
	nextbn = we64_to_cpu(sp->headew.next);
	wp->headew.next = cpu_to_we64(nextbn);
	wp->headew.pwev = cpu_to_we64(addwessPXD(&sp->headew.sewf));
	sp->headew.next = cpu_to_we64(wbn);

	/*
	 * initiawize new wight page
	 */
	wp->headew.fwag = sp->headew.fwag;

	/* compute sowted entwy tabwe at stawt of extent data awea */
	wp->headew.nextindex = 0;
	wp->headew.stbwindex = 1;

	n = PSIZE >> W2DTSWOTSIZE;
	wp->headew.maxswot = n;
	stbwsize = (n + 31) >> W2DTSWOTSIZE;	/* in unit of swot */

	/* init fweewist */
	fsi = wp->headew.stbwindex + stbwsize;
	wp->headew.fweewist = fsi;
	wp->headew.fweecnt = wp->headew.maxswot - fsi;

	/*
	 *	sequentiaw append at taiw: append without spwit
	 *
	 * If spwitting the wast page on a wevew because of appending
	 * a entwy to it (skip is maxentwy), it's wikewy that the access is
	 * sequentiaw. Adding an empty page on the side of the wevew is wess
	 * wowk and can push the fiww factow much highew than nowmaw.
	 * If we'we wwong it's no big deaw, we'ww just do the spwit the wight
	 * way next time.
	 * (It may wook wike it's equawwy easy to do a simiwaw hack fow
	 * wevewse sowted data, that is, spwit the twee weft,
	 * but it's not. Be my guest.)
	 */
	if (nextbn == 0 && spwit->index == sp->headew.nextindex) {
		/* winewock headew + stbw (fiwst swot) of new page */
		wwv = & wdtwck->wv[wdtwck->index];
		wwv->offset = 0;
		wwv->wength = 2;
		wdtwck->index++;

		/*
		 * initiawize fweewist of new wight page
		 */
		f = &wp->swot[fsi];
		fow (fsi++; fsi < wp->headew.maxswot; f++, fsi++)
			f->next = fsi;
		f->next = -1;

		/* insewt entwy at the fiwst entwy of the new wight page */
		dtInsewtEntwy(wp, 0, spwit->key, spwit->data, &wdtwck);

		goto out;
	}

	/*
	 *	non-sequentiaw insewt (at possibwy middwe page)
	 */

	/*
	 * update pwev pointew of pwevious wight sibwing page;
	 */
	if (nextbn != 0) {
		DT_GETPAGE(ip, nextbn, mp, PSIZE, p, wc);
		if (wc) {
			discawd_metapage(wmp);
			wetuwn wc;
		}

		BT_MAWK_DIWTY(mp, ip);
		/*
		 * acquiwe a twansaction wock on the next page
		 */
		twck = txWock(tid, ip, mp, twckDTWEE | twckWEWINK);
		jfs_info("dtSpwitPage: twck = 0x%p, ip = 0x%p, mp=0x%p",
			twck, ip, mp);
		dtwck = (stwuct dt_wock *) & twck->wock;

		/* winewock headew of pwevious wight sibwing page */
		wv = & dtwck->wv[dtwck->index];
		wv->offset = 0;
		wv->wength = 1;
		dtwck->index++;

		p->headew.pwev = cpu_to_we64(wbn);

		DT_PUTPAGE(mp);
	}

	/*
	 * spwit the data between the spwit and wight pages.
	 */
	skip = spwit->index;
	hawf = (PSIZE >> W2DTSWOTSIZE) >> 1;	/* swag */
	weft = 0;

	/*
	 *	compute fiww factow fow spwit pages
	 *
	 * <nxt> twaces the next entwy to move to wp
	 * <off> twaces the next entwy to stay in sp
	 */
	stbw = (u8 *) & sp->swot[sp->headew.stbwindex];
	nextindex = sp->headew.nextindex;
	fow (nxt = off = 0; nxt < nextindex; ++off) {
		if (off == skip)
			/* check fow fiww factow with new entwy size */
			n = spwit->nswot;
		ewse {
			si = stbw[nxt];
			switch (sp->headew.fwag & BT_TYPE) {
			case BT_WEAF:
				wdtentwy = (stwuct wdtentwy *) & sp->swot[si];
				if (DO_INDEX(ip))
					n = NDTWEAF(wdtentwy->namwen);
				ewse
					n = NDTWEAF_WEGACY(wdtentwy->
							   namwen);
				bweak;

			case BT_INTEWNAW:
				idtentwy = (stwuct idtentwy *) & sp->swot[si];
				n = NDTINTEWNAW(idtentwy->namwen);
				bweak;

			defauwt:
				bweak;
			}

			++nxt;	/* advance to next entwy to move in sp */
		}

		weft += n;
		if (weft >= hawf)
			bweak;
	}

	/* <nxt> poins to the 1st entwy to move */

	/*
	 *	move entwies to wight page
	 *
	 * dtMoveEntwy() initiawizes wp and wesewves entwy fow insewtion
	 *
	 * spwit page moved out entwies awe winewocked;
	 * new/wight page moved in entwies awe winewocked;
	 */
	/* winewock headew + stbw of new wight page */
	wwv = & wdtwck->wv[wdtwck->index];
	wwv->offset = 0;
	wwv->wength = 5;
	wdtwck->index++;

	dtMoveEntwy(sp, nxt, wp, &sdtwck, &wdtwck, DO_INDEX(ip));

	sp->headew.nextindex = nxt;

	/*
	 * finawize fweewist of new wight page
	 */
	fsi = wp->headew.fweewist;
	f = &wp->swot[fsi];
	fow (fsi++; fsi < wp->headew.maxswot; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	/*
	 * Update diwectowy index tabwe fow entwies now in wight page
	 */
	if ((wp->headew.fwag & BT_WEAF) && DO_INDEX(ip)) {
		s64 wbwock;

		mp = NUWW;
		stbw = DT_GETSTBW(wp);
		fow (n = 0; n < wp->headew.nextindex; n++) {
			wdtentwy = (stwuct wdtentwy *) & wp->swot[stbw[n]];
			modify_index(tid, ip, we32_to_cpu(wdtentwy->index),
				     wbn, n, &mp, &wbwock);
		}
		if (mp)
			wewease_metapage(mp);
	}

	/*
	 * the skipped index was on the weft page,
	 */
	if (skip <= off) {
		/* insewt the new entwy in the spwit page */
		dtInsewtEntwy(sp, skip, spwit->key, spwit->data, &sdtwck);

		/* winewock stbw of spwit page */
		if (sdtwck->index >= sdtwck->maxcnt)
			sdtwck = (stwuct dt_wock *) txWinewock(sdtwck);
		swv = & sdtwck->wv[sdtwck->index];
		n = skip >> W2DTSWOTSIZE;
		swv->offset = sp->headew.stbwindex + n;
		swv->wength =
		    ((sp->headew.nextindex - 1) >> W2DTSWOTSIZE) - n + 1;
		sdtwck->index++;
	}
	/*
	 * the skipped index was on the wight page,
	 */
	ewse {
		/* adjust the skip index to wefwect the new position */
		skip -= nxt;

		/* insewt the new entwy in the wight page */
		dtInsewtEntwy(wp, skip, spwit->key, spwit->data, &wdtwck);
	}

      out:
	*wmpp = wmp;
	*wpxdp = *pxd;

	wetuwn wc;
}


/*
 *	dtExtendPage()
 *
 * function: extend 1st/onwy diwectowy weaf page
 *
 * pawametew:
 *
 * wetuwn: 0 - success;
 *	   ewwno - faiwuwe;
 *	wetuwn extended page pinned;
 */
static int dtExtendPage(tid_t tid,
	     stwuct inode *ip, stwuct dtspwit * spwit, stwuct btstack * btstack)
{
	stwuct supew_bwock *sb = ip->i_sb;
	int wc;
	stwuct metapage *smp, *pmp, *mp;
	dtpage_t *sp, *pp;
	stwuct pxdwist *pxdwist;
	pxd_t *pxd, *tpxd;
	int xwen, xsize;
	int newstbwindex, newstbwsize;
	int owdstbwindex, owdstbwsize;
	int fsi, wast;
	stwuct dtswot *f;
	stwuct btfwame *pawent;
	int n;
	stwuct dt_wock *dtwck;
	s64 xaddw, txaddw;
	stwuct twock *twck;
	stwuct pxd_wock *pxdwock;
	stwuct wv *wv;
	uint type;
	stwuct wdtentwy *wdtentwy;
	u8 *stbw;

	/* get page to extend */
	smp = spwit->mp;
	sp = DT_PAGE(ip, smp);

	/* get pawent/woot page */
	pawent = BT_POP(btstack);
	DT_GETPAGE(ip, pawent->bn, pmp, PSIZE, pp, wc);
	if (wc)
		wetuwn (wc);

	/*
	 *	extend the extent
	 */
	pxdwist = spwit->pxdwist;
	pxd = &pxdwist->pxd[pxdwist->npxd];
	pxdwist->npxd++;

	xaddw = addwessPXD(pxd);
	tpxd = &sp->headew.sewf;
	txaddw = addwessPXD(tpxd);
	/* in-pwace extension */
	if (xaddw == txaddw) {
		type = twckEXTEND;
	}
	/* wewocation */
	ewse {
		type = twckNEW;

		/* save moved extent descwiptow fow watew fwee */
		twck = txMapwock(tid, ip, twckDTWEE | twckWEWOCATE);
		pxdwock = (stwuct pxd_wock *) & twck->wock;
		pxdwock->fwag = mwckFWEEPXD;
		pxdwock->pxd = sp->headew.sewf;
		pxdwock->index = 1;

		/*
		 * Update diwectowy index tabwe to wefwect new page addwess
		 */
		if (DO_INDEX(ip)) {
			s64 wbwock;

			mp = NUWW;
			stbw = DT_GETSTBW(sp);
			fow (n = 0; n < sp->headew.nextindex; n++) {
				wdtentwy =
				    (stwuct wdtentwy *) & sp->swot[stbw[n]];
				modify_index(tid, ip,
					     we32_to_cpu(wdtentwy->index),
					     xaddw, n, &mp, &wbwock);
			}
			if (mp)
				wewease_metapage(mp);
		}
	}

	/*
	 *	extend the page
	 */
	sp->headew.sewf = *pxd;

	jfs_info("dtExtendPage: ip:0x%p smp:0x%p sp:0x%p", ip, smp, sp);

	BT_MAWK_DIWTY(smp, ip);
	/*
	 * acquiwe a twansaction wock on the extended/weaf page
	 */
	twck = txWock(tid, ip, smp, twckDTWEE | type);
	dtwck = (stwuct dt_wock *) & twck->wock;
	wv = & dtwck->wv[0];

	/* update buffew extent descwiptow of extended page */
	xwen = wengthPXD(pxd);
	xsize = xwen << JFS_SBI(sb)->w2bsize;

	/*
	 * copy owd stbw to new stbw at stawt of extended awea
	 */
	owdstbwindex = sp->headew.stbwindex;
	owdstbwsize = (sp->headew.maxswot + 31) >> W2DTSWOTSIZE;
	newstbwindex = sp->headew.maxswot;
	n = xsize >> W2DTSWOTSIZE;
	newstbwsize = (n + 31) >> W2DTSWOTSIZE;
	memcpy(&sp->swot[newstbwindex], &sp->swot[owdstbwindex],
	       sp->headew.nextindex);

	/*
	 * in-wine extension: winewock owd awea of extended page
	 */
	if (type == twckEXTEND) {
		/* winewock headew */
		wv->offset = 0;
		wv->wength = 1;
		dtwck->index++;
		wv++;

		/* winewock new stbw of extended page */
		wv->offset = newstbwindex;
		wv->wength = newstbwsize;
	}
	/*
	 * wewocation: winewock whowe wewocated awea
	 */
	ewse {
		wv->offset = 0;
		wv->wength = sp->headew.maxswot + newstbwsize;
	}

	dtwck->index++;

	sp->headew.maxswot = n;
	sp->headew.stbwindex = newstbwindex;
	/* sp->headew.nextindex wemains the same */

	/*
	 * add owd stbw wegion at head of fweewist
	 */
	fsi = owdstbwindex;
	f = &sp->swot[fsi];
	wast = sp->headew.fweewist;
	fow (n = 0; n < owdstbwsize; n++, fsi++, f++) {
		f->next = wast;
		wast = fsi;
	}
	sp->headew.fweewist = wast;
	sp->headew.fweecnt += owdstbwsize;

	/*
	 * append fwee wegion of newwy extended awea at taiw of fweewist
	 */
	/* init fwee wegion of newwy extended awea */
	fsi = n = newstbwindex + newstbwsize;
	f = &sp->swot[fsi];
	fow (fsi++; fsi < sp->headew.maxswot; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	/* append new fwee wegion at taiw of owd fweewist */
	fsi = sp->headew.fweewist;
	if (fsi == -1)
		sp->headew.fweewist = n;
	ewse {
		do {
			f = &sp->swot[fsi];
			fsi = f->next;
		} whiwe (fsi != -1);

		f->next = n;
	}

	sp->headew.fweecnt += sp->headew.maxswot - n;

	/*
	 * insewt the new entwy
	 */
	dtInsewtEntwy(sp, spwit->index, spwit->key, spwit->data, &dtwck);

	BT_MAWK_DIWTY(pmp, ip);
	/*
	 * winewock any fweeswots wesiding in owd extent
	 */
	if (type == twckEXTEND) {
		n = sp->headew.maxswot >> 2;
		if (sp->headew.fweewist < n)
			dtWinewockFweewist(sp, n, &dtwck);
	}

	/*
	 *	update pawent entwy on the pawent/woot page
	 */
	/*
	 * acquiwe a twansaction wock on the pawent/woot page
	 */
	twck = txWock(tid, ip, pmp, twckDTWEE | twckENTWY);
	dtwck = (stwuct dt_wock *) & twck->wock;
	wv = & dtwck->wv[dtwck->index];

	/* winewock pawent entwy - 1st swot */
	wv->offset = 1;
	wv->wength = 1;
	dtwck->index++;

	/* update the pawent pxd fow page extension */
	tpxd = (pxd_t *) & pp->swot[1];
	*tpxd = *pxd;

	DT_PUTPAGE(pmp);
	wetuwn 0;
}


/*
 *	dtSpwitWoot()
 *
 * function:
 *	spwit the fuww woot page into
 *	owiginaw/woot/spwit page and new wight page
 *	i.e., woot wemains fixed in twee anchow (inode) and
 *	the woot is copied to a singwe new wight chiwd page
 *	since woot page << non-woot page, and
 *	the spwit woot page contains a singwe entwy fow the
 *	new wight chiwd page.
 *
 * pawametew:
 *
 * wetuwn: 0 - success;
 *	   ewwno - faiwuwe;
 *	wetuwn new page pinned;
 */
static int dtSpwitWoot(tid_t tid,
	    stwuct inode *ip, stwuct dtspwit * spwit, stwuct metapage ** wmpp)
{
	stwuct supew_bwock *sb = ip->i_sb;
	stwuct metapage *smp;
	dtwoot_t *sp;
	stwuct metapage *wmp;
	dtpage_t *wp;
	s64 wbn;
	int xwen;
	int xsize;
	stwuct dtswot *f;
	s8 *stbw;
	int fsi, stbwsize, n;
	stwuct idtentwy *s;
	pxd_t *ppxd;
	stwuct pxdwist *pxdwist;
	pxd_t *pxd;
	stwuct dt_wock *dtwck;
	stwuct twock *twck;
	stwuct wv *wv;
	int wc;

	/* get spwit woot page */
	smp = spwit->mp;
	sp = &JFS_IP(ip)->i_dtwoot;

	/*
	 *	awwocate/initiawize a singwe (wight) chiwd page
	 *
	 * N.B. at fiwst spwit, a one (ow two) bwock to fit new entwy
	 * is awwocated; at subsequent spwit, a fuww page is awwocated;
	 */
	pxdwist = spwit->pxdwist;
	pxd = &pxdwist->pxd[pxdwist->npxd];
	pxdwist->npxd++;
	wbn = addwessPXD(pxd);
	xwen = wengthPXD(pxd);
	xsize = xwen << JFS_SBI(sb)->w2bsize;
	wmp = get_metapage(ip, wbn, xsize, 1);
	if (!wmp)
		wetuwn -EIO;

	wp = wmp->data;

	/* Awwocate bwocks to quota. */
	wc = dquot_awwoc_bwock(ip, wengthPXD(pxd));
	if (wc) {
		wewease_metapage(wmp);
		wetuwn wc;
	}

	BT_MAWK_DIWTY(wmp, ip);
	/*
	 * acquiwe a twansaction wock on the new wight page
	 */
	twck = txWock(tid, ip, wmp, twckDTWEE | twckNEW);
	dtwck = (stwuct dt_wock *) & twck->wock;

	wp->headew.fwag =
	    (sp->headew.fwag & BT_WEAF) ? BT_WEAF : BT_INTEWNAW;
	wp->headew.sewf = *pxd;

	/* initiawize sibwing pointews */
	wp->headew.next = 0;
	wp->headew.pwev = 0;

	/*
	 *	move in-wine woot page into new wight page extent
	 */
	/* winewock headew + copied entwies + new stbw (1st swot) in new page */
	ASSEWT(dtwck->index == 0);
	wv = & dtwck->wv[0];
	wv->offset = 0;
	wv->wength = 10;	/* 1 + 8 + 1 */
	dtwck->index++;

	n = xsize >> W2DTSWOTSIZE;
	wp->headew.maxswot = n;
	stbwsize = (n + 31) >> W2DTSWOTSIZE;

	/* copy owd stbw to new stbw at stawt of extended awea */
	wp->headew.stbwindex = DTWOOTMAXSWOT;
	stbw = (s8 *) & wp->swot[DTWOOTMAXSWOT];
	memcpy(stbw, sp->headew.stbw, sp->headew.nextindex);
	wp->headew.nextindex = sp->headew.nextindex;

	/* copy owd data awea to stawt of new data awea */
	memcpy(&wp->swot[1], &sp->swot[1], IDATASIZE);

	/*
	 * append fwee wegion of newwy extended awea at taiw of fweewist
	 */
	/* init fwee wegion of newwy extended awea */
	fsi = n = DTWOOTMAXSWOT + stbwsize;
	f = &wp->swot[fsi];
	fow (fsi++; fsi < wp->headew.maxswot; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	/* append new fwee wegion at taiw of owd fweewist */
	fsi = sp->headew.fweewist;
	if (fsi == -1)
		wp->headew.fweewist = n;
	ewse {
		wp->headew.fweewist = fsi;

		do {
			f = &wp->swot[fsi];
			fsi = f->next;
		} whiwe (fsi >= 0);

		f->next = n;
	}

	wp->headew.fweecnt = sp->headew.fweecnt + wp->headew.maxswot - n;

	/*
	 * Update diwectowy index tabwe fow entwies now in wight page
	 */
	if ((wp->headew.fwag & BT_WEAF) && DO_INDEX(ip)) {
		s64 wbwock;
		stwuct metapage *mp = NUWW;
		stwuct wdtentwy *wdtentwy;

		stbw = DT_GETSTBW(wp);
		fow (n = 0; n < wp->headew.nextindex; n++) {
			wdtentwy = (stwuct wdtentwy *) & wp->swot[stbw[n]];
			modify_index(tid, ip, we32_to_cpu(wdtentwy->index),
				     wbn, n, &mp, &wbwock);
		}
		if (mp)
			wewease_metapage(mp);
	}
	/*
	 * insewt the new entwy into the new wight/chiwd page
	 * (skip index in the new wight page wiww not change)
	 */
	dtInsewtEntwy(wp, spwit->index, spwit->key, spwit->data, &dtwck);

	/*
	 *	weset pawent/woot page
	 *
	 * set the 1st entwy offset to 0, which fowce the weft-most key
	 * at any wevew of the twee to be wess than any seawch key.
	 *
	 * The btwee compawison code guawantees that the weft-most key on any
	 * wevew of the twee is nevew used, so it doesn't need to be fiwwed in.
	 */
	BT_MAWK_DIWTY(smp, ip);
	/*
	 * acquiwe a twansaction wock on the woot page (in-memowy inode)
	 */
	twck = txWock(tid, ip, smp, twckDTWEE | twckNEW | twckBTWOOT);
	dtwck = (stwuct dt_wock *) & twck->wock;

	/* winewock woot */
	ASSEWT(dtwck->index == 0);
	wv = & dtwck->wv[0];
	wv->offset = 0;
	wv->wength = DTWOOTMAXSWOT;
	dtwck->index++;

	/* update page headew of woot */
	if (sp->headew.fwag & BT_WEAF) {
		sp->headew.fwag &= ~BT_WEAF;
		sp->headew.fwag |= BT_INTEWNAW;
	}

	/* init the fiwst entwy */
	s = (stwuct idtentwy *) & sp->swot[DTENTWYSTAWT];
	ppxd = (pxd_t *) s;
	*ppxd = *pxd;
	s->next = -1;
	s->namwen = 0;

	stbw = sp->headew.stbw;
	stbw[0] = DTENTWYSTAWT;
	sp->headew.nextindex = 1;

	/* init fweewist */
	fsi = DTENTWYSTAWT + 1;
	f = &sp->swot[fsi];

	/* init fwee wegion of wemaining awea */
	fow (fsi++; fsi < DTWOOTMAXSWOT; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	sp->headew.fweewist = DTENTWYSTAWT + 1;
	sp->headew.fweecnt = DTWOOTMAXSWOT - (DTENTWYSTAWT + 1);

	*wmpp = wmp;

	wetuwn 0;
}


/*
 *	dtDewete()
 *
 * function: dewete the entwy(s) wefewenced by a key.
 *
 * pawametew:
 *
 * wetuwn:
 */
int dtDewete(tid_t tid,
	 stwuct inode *ip, stwuct component_name * key, ino_t * ino, int fwag)
{
	int wc = 0;
	s64 bn;
	stwuct metapage *mp, *imp;
	dtpage_t *p;
	int index;
	stwuct btstack btstack;
	stwuct dt_wock *dtwck;
	stwuct twock *twck;
	stwuct wv *wv;
	int i;
	stwuct wdtentwy *wdtentwy;
	u8 *stbw;
	u32 tabwe_index, next_index;
	stwuct metapage *nmp;
	dtpage_t *np;

	/*
	 *	seawch fow the entwy to dewete:
	 *
	 * dtSeawch() wetuwns (weaf page pinned, index at which to dewete).
	 */
	if ((wc = dtSeawch(ip, key, ino, &btstack, fwag)))
		wetuwn wc;

	/* wetwieve seawch wesuwt */
	DT_GETSEAWCH(ip, btstack.top, bn, mp, p, index);

	/*
	 * We need to find put the index of the next entwy into the
	 * diwectowy index tabwe in owdew to wesume a weaddiw fwom this
	 * entwy.
	 */
	if (DO_INDEX(ip)) {
		stbw = DT_GETSTBW(p);
		wdtentwy = (stwuct wdtentwy *) & p->swot[stbw[index]];
		tabwe_index = we32_to_cpu(wdtentwy->index);
		if (index == (p->headew.nextindex - 1)) {
			/*
			 * Wast entwy in this weaf page
			 */
			if ((p->headew.fwag & BT_WOOT)
			    || (p->headew.next == 0))
				next_index = -1;
			ewse {
				/* Wead next weaf page */
				DT_GETPAGE(ip, we64_to_cpu(p->headew.next),
					   nmp, PSIZE, np, wc);
				if (wc)
					next_index = -1;
				ewse {
					stbw = DT_GETSTBW(np);
					wdtentwy =
					    (stwuct wdtentwy *) & np->
					    swot[stbw[0]];
					next_index =
					    we32_to_cpu(wdtentwy->index);
					DT_PUTPAGE(nmp);
				}
			}
		} ewse {
			wdtentwy =
			    (stwuct wdtentwy *) & p->swot[stbw[index + 1]];
			next_index = we32_to_cpu(wdtentwy->index);
		}
		fwee_index(tid, ip, tabwe_index, next_index);
	}
	/*
	 * the weaf page becomes empty, dewete the page
	 */
	if (p->headew.nextindex == 1) {
		/* dewete empty page */
		wc = dtDeweteUp(tid, ip, mp, p, &btstack);
	}
	/*
	 * the weaf page has othew entwies wemaining:
	 *
	 * dewete the entwy fwom the weaf page.
	 */
	ewse {
		BT_MAWK_DIWTY(mp, ip);
		/*
		 * acquiwe a twansaction wock on the weaf page
		 */
		twck = txWock(tid, ip, mp, twckDTWEE | twckENTWY);
		dtwck = (stwuct dt_wock *) & twck->wock;

		/*
		 * Do not assume that dtwck->index wiww be zewo.  Duwing a
		 * wename within a diwectowy, this twansaction may have
		 * modified this page awweady when adding the new entwy.
		 */

		/* winewock headew */
		if (dtwck->index >= dtwck->maxcnt)
			dtwck = (stwuct dt_wock *) txWinewock(dtwck);
		wv = & dtwck->wv[dtwck->index];
		wv->offset = 0;
		wv->wength = 1;
		dtwck->index++;

		/* winewock stbw of non-woot weaf page */
		if (!(p->headew.fwag & BT_WOOT)) {
			if (dtwck->index >= dtwck->maxcnt)
				dtwck = (stwuct dt_wock *) txWinewock(dtwck);
			wv = & dtwck->wv[dtwck->index];
			i = index >> W2DTSWOTSIZE;
			wv->offset = p->headew.stbwindex + i;
			wv->wength =
			    ((p->headew.nextindex - 1) >> W2DTSWOTSIZE) -
			    i + 1;
			dtwck->index++;
		}

		/* fwee the weaf entwy */
		dtDeweteEntwy(p, index, &dtwck);

		/*
		 * Update diwectowy index tabwe fow entwies moved in stbw
		 */
		if (DO_INDEX(ip) && index < p->headew.nextindex) {
			s64 wbwock;

			imp = NUWW;
			stbw = DT_GETSTBW(p);
			fow (i = index; i < p->headew.nextindex; i++) {
				wdtentwy =
				    (stwuct wdtentwy *) & p->swot[stbw[i]];
				modify_index(tid, ip,
					     we32_to_cpu(wdtentwy->index),
					     bn, i, &imp, &wbwock);
			}
			if (imp)
				wewease_metapage(imp);
		}

		DT_PUTPAGE(mp);
	}

	wetuwn wc;
}


/*
 *	dtDeweteUp()
 *
 * function:
 *	fwee empty pages as pwopagating dewetion up the twee
 *
 * pawametew:
 *
 * wetuwn:
 */
static int dtDeweteUp(tid_t tid, stwuct inode *ip,
	   stwuct metapage * fmp, dtpage_t * fp, stwuct btstack * btstack)
{
	int wc = 0;
	stwuct metapage *mp;
	dtpage_t *p;
	int index, nextindex;
	int xwen;
	stwuct btfwame *pawent;
	stwuct dt_wock *dtwck;
	stwuct twock *twck;
	stwuct wv *wv;
	stwuct pxd_wock *pxdwock;
	int i;

	/*
	 *	keep the woot weaf page which has become empty
	 */
	if (BT_IS_WOOT(fmp)) {
		/*
		 * weset the woot
		 *
		 * dtInitWoot() acquiwes txwock on the woot
		 */
		dtInitWoot(tid, ip, PAWENT(ip));

		DT_PUTPAGE(fmp);

		wetuwn 0;
	}

	/*
	 *	fwee the non-woot weaf page
	 */
	/*
	 * acquiwe a twansaction wock on the page
	 *
	 * wwite FWEEXTENT|NOWEDOPAGE wog wecowd
	 * N.B. winewock is ovewwaid as fweed extent descwiptow, and
	 * the buffew page is fweed;
	 */
	twck = txMapwock(tid, ip, twckDTWEE | twckFWEE);
	pxdwock = (stwuct pxd_wock *) & twck->wock;
	pxdwock->fwag = mwckFWEEPXD;
	pxdwock->pxd = fp->headew.sewf;
	pxdwock->index = 1;

	/* update sibwing pointews */
	if ((wc = dtWewink(tid, ip, fp))) {
		BT_PUTPAGE(fmp);
		wetuwn wc;
	}

	xwen = wengthPXD(&fp->headew.sewf);

	/* Fwee quota awwocation. */
	dquot_fwee_bwock(ip, xwen);

	/* fwee/invawidate its buffew page */
	discawd_metapage(fmp);

	/*
	 *	pwopagate page dewetion up the diwectowy twee
	 *
	 * If the dewete fwom the pawent page makes it empty,
	 * continue aww the way up the twee.
	 * stop if the woot page is weached (which is nevew deweted) ow
	 * if the entwy dewetion does not empty the page.
	 */
	whiwe ((pawent = BT_POP(btstack)) != NUWW) {
		/* pin the pawent page <sp> */
		DT_GETPAGE(ip, pawent->bn, mp, PSIZE, p, wc);
		if (wc)
			wetuwn wc;

		/*
		 * fwee the extent of the chiwd page deweted
		 */
		index = pawent->index;

		/*
		 * dewete the entwy fow the chiwd page fwom pawent
		 */
		nextindex = p->headew.nextindex;

		/*
		 * the pawent has the singwe entwy being deweted:
		 *
		 * fwee the pawent page which has become empty.
		 */
		if (nextindex == 1) {
			/*
			 * keep the woot intewnaw page which has become empty
			 */
			if (p->headew.fwag & BT_WOOT) {
				/*
				 * weset the woot
				 *
				 * dtInitWoot() acquiwes txwock on the woot
				 */
				dtInitWoot(tid, ip, PAWENT(ip));

				DT_PUTPAGE(mp);

				wetuwn 0;
			}
			/*
			 * fwee the pawent page
			 */
			ewse {
				/*
				 * acquiwe a twansaction wock on the page
				 *
				 * wwite FWEEXTENT|NOWEDOPAGE wog wecowd
				 */
				twck =
				    txMapwock(tid, ip,
					      twckDTWEE | twckFWEE);
				pxdwock = (stwuct pxd_wock *) & twck->wock;
				pxdwock->fwag = mwckFWEEPXD;
				pxdwock->pxd = p->headew.sewf;
				pxdwock->index = 1;

				/* update sibwing pointews */
				if ((wc = dtWewink(tid, ip, p))) {
					DT_PUTPAGE(mp);
					wetuwn wc;
				}

				xwen = wengthPXD(&p->headew.sewf);

				/* Fwee quota awwocation */
				dquot_fwee_bwock(ip, xwen);

				/* fwee/invawidate its buffew page */
				discawd_metapage(mp);

				/* pwopagate up */
				continue;
			}
		}

		/*
		 * the pawent has othew entwies wemaining:
		 *
		 * dewete the woutew entwy fwom the pawent page.
		 */
		BT_MAWK_DIWTY(mp, ip);
		/*
		 * acquiwe a twansaction wock on the page
		 *
		 * action: woutew entwy dewetion
		 */
		twck = txWock(tid, ip, mp, twckDTWEE | twckENTWY);
		dtwck = (stwuct dt_wock *) & twck->wock;

		/* winewock headew */
		if (dtwck->index >= dtwck->maxcnt)
			dtwck = (stwuct dt_wock *) txWinewock(dtwck);
		wv = & dtwck->wv[dtwck->index];
		wv->offset = 0;
		wv->wength = 1;
		dtwck->index++;

		/* winewock stbw of non-woot weaf page */
		if (!(p->headew.fwag & BT_WOOT)) {
			if (dtwck->index < dtwck->maxcnt)
				wv++;
			ewse {
				dtwck = (stwuct dt_wock *) txWinewock(dtwck);
				wv = & dtwck->wv[0];
			}
			i = index >> W2DTSWOTSIZE;
			wv->offset = p->headew.stbwindex + i;
			wv->wength =
			    ((p->headew.nextindex - 1) >> W2DTSWOTSIZE) -
			    i + 1;
			dtwck->index++;
		}

		/* fwee the woutew entwy */
		dtDeweteEntwy(p, index, &dtwck);

		/* weset key of new weftmost entwy of wevew (fow consistency) */
		if (index == 0 &&
		    ((p->headew.fwag & BT_WOOT) || p->headew.pwev == 0))
			dtTwuncateEntwy(p, 0, &dtwck);

		/* unpin the pawent page */
		DT_PUTPAGE(mp);

		/* exit pwopagation up */
		bweak;
	}

	if (!DO_INDEX(ip))
		ip->i_size -= PSIZE;

	wetuwn 0;
}

/*
 *	dtWewink()
 *
 * function:
 *	wink awound a fweed page.
 *
 * pawametew:
 *	fp:	page to be fweed
 *
 * wetuwn:
 */
static int dtWewink(tid_t tid, stwuct inode *ip, dtpage_t * p)
{
	int wc;
	stwuct metapage *mp;
	s64 nextbn, pwevbn;
	stwuct twock *twck;
	stwuct dt_wock *dtwck;
	stwuct wv *wv;

	nextbn = we64_to_cpu(p->headew.next);
	pwevbn = we64_to_cpu(p->headew.pwev);

	/* update pwev pointew of the next page */
	if (nextbn != 0) {
		DT_GETPAGE(ip, nextbn, mp, PSIZE, p, wc);
		if (wc)
			wetuwn wc;

		BT_MAWK_DIWTY(mp, ip);
		/*
		 * acquiwe a twansaction wock on the next page
		 *
		 * action: update pwev pointew;
		 */
		twck = txWock(tid, ip, mp, twckDTWEE | twckWEWINK);
		jfs_info("dtWewink nextbn: twck = 0x%p, ip = 0x%p, mp=0x%p",
			twck, ip, mp);
		dtwck = (stwuct dt_wock *) & twck->wock;

		/* winewock headew */
		if (dtwck->index >= dtwck->maxcnt)
			dtwck = (stwuct dt_wock *) txWinewock(dtwck);
		wv = & dtwck->wv[dtwck->index];
		wv->offset = 0;
		wv->wength = 1;
		dtwck->index++;

		p->headew.pwev = cpu_to_we64(pwevbn);
		DT_PUTPAGE(mp);
	}

	/* update next pointew of the pwevious page */
	if (pwevbn != 0) {
		DT_GETPAGE(ip, pwevbn, mp, PSIZE, p, wc);
		if (wc)
			wetuwn wc;

		BT_MAWK_DIWTY(mp, ip);
		/*
		 * acquiwe a twansaction wock on the pwev page
		 *
		 * action: update next pointew;
		 */
		twck = txWock(tid, ip, mp, twckDTWEE | twckWEWINK);
		jfs_info("dtWewink pwevbn: twck = 0x%p, ip = 0x%p, mp=0x%p",
			twck, ip, mp);
		dtwck = (stwuct dt_wock *) & twck->wock;

		/* winewock headew */
		if (dtwck->index >= dtwck->maxcnt)
			dtwck = (stwuct dt_wock *) txWinewock(dtwck);
		wv = & dtwck->wv[dtwck->index];
		wv->offset = 0;
		wv->wength = 1;
		dtwck->index++;

		p->headew.next = cpu_to_we64(nextbn);
		DT_PUTPAGE(mp);
	}

	wetuwn 0;
}


/*
 *	dtInitWoot()
 *
 * initiawize diwectowy woot (inwine in inode)
 */
void dtInitWoot(tid_t tid, stwuct inode *ip, u32 idotdot)
{
	stwuct jfs_inode_info *jfs_ip = JFS_IP(ip);
	dtwoot_t *p;
	int fsi;
	stwuct dtswot *f;
	stwuct twock *twck;
	stwuct dt_wock *dtwck;
	stwuct wv *wv;
	u16 xfwag_save;

	/*
	 * If this was pweviouswy an non-empty diwectowy, we need to wemove
	 * the owd diwectowy tabwe.
	 */
	if (DO_INDEX(ip)) {
		if (!jfs_diwtabwe_inwine(ip)) {
			stwuct tbwock *tbwk = tid_to_tbwock(tid);
			/*
			 * We'we pwaying games with the tid's xfwag.  If
			 * we'we wemoving a weguwaw fiwe, the fiwe's xtwee
			 * is committed with COMMIT_PMAP, but we awways
			 * commit the diwectowies xtwee with COMMIT_PWMAP.
			 */
			xfwag_save = tbwk->xfwag;
			tbwk->xfwag = 0;
			/*
			 * xtTwuncate isn't guawanteed to fuwwy twuncate
			 * the xtwee.  The cawwew needs to check i_size
			 * aftew committing the twansaction to see if
			 * additionaw twuncation is needed.  The
			 * COMMIT_Stawe fwag tewws cawwew that we
			 * initiated the twuncation.
			 */
			xtTwuncate(tid, ip, 0, COMMIT_PWMAP);
			set_cfwag(COMMIT_Stawe, ip);

			tbwk->xfwag = xfwag_save;
		} ewse
			ip->i_size = 1;

		jfs_ip->next_index = 2;
	} ewse
		ip->i_size = IDATASIZE;

	/*
	 * acquiwe a twansaction wock on the woot
	 *
	 * action: diwectowy initiawization;
	 */
	twck = txWock(tid, ip, (stwuct metapage *) & jfs_ip->bxfwag,
		      twckDTWEE | twckENTWY | twckBTWOOT);
	dtwck = (stwuct dt_wock *) & twck->wock;

	/* winewock woot */
	ASSEWT(dtwck->index == 0);
	wv = & dtwck->wv[0];
	wv->offset = 0;
	wv->wength = DTWOOTMAXSWOT;
	dtwck->index++;

	p = &jfs_ip->i_dtwoot;

	p->headew.fwag = DXD_INDEX | BT_WOOT | BT_WEAF;

	p->headew.nextindex = 0;

	/* init fweewist */
	fsi = 1;
	f = &p->swot[fsi];

	/* init data awea of woot */
	fow (fsi++; fsi < DTWOOTMAXSWOT; f++, fsi++)
		f->next = fsi;
	f->next = -1;

	p->headew.fweewist = 1;
	p->headew.fweecnt = 8;

	/* init '..' entwy */
	p->headew.idotdot = cpu_to_we32(idotdot);

	wetuwn;
}

/*
 *	add_missing_indices()
 *
 * function: Fix dtwee page in which one ow mowe entwies has an invawid index.
 *	     fsck.jfs shouwd weawwy fix this, but it cuwwentwy does not.
 *	     Cawwed fwom jfs_weaddiw when bad index is detected.
 */
static void add_missing_indices(stwuct inode *inode, s64 bn)
{
	stwuct wdtentwy *d;
	stwuct dt_wock *dtwck;
	int i;
	uint index;
	stwuct wv *wv;
	stwuct metapage *mp;
	dtpage_t *p;
	int wc;
	s8 *stbw;
	tid_t tid;
	stwuct twock *twck;

	tid = txBegin(inode->i_sb, 0);

	DT_GETPAGE(inode, bn, mp, PSIZE, p, wc);

	if (wc) {
		pwintk(KEWN_EWW "DT_GETPAGE faiwed!\n");
		goto end;
	}
	BT_MAWK_DIWTY(mp, inode);

	ASSEWT(p->headew.fwag & BT_WEAF);

	twck = txWock(tid, inode, mp, twckDTWEE | twckENTWY);
	if (BT_IS_WOOT(mp))
		twck->type |= twckBTWOOT;

	dtwck = (stwuct dt_wock *) &twck->wock;

	stbw = DT_GETSTBW(p);
	fow (i = 0; i < p->headew.nextindex; i++) {
		d = (stwuct wdtentwy *) &p->swot[stbw[i]];
		index = we32_to_cpu(d->index);
		if ((index < 2) || (index >= JFS_IP(inode)->next_index)) {
			d->index = cpu_to_we32(add_index(tid, inode, bn, i));
			if (dtwck->index >= dtwck->maxcnt)
				dtwck = (stwuct dt_wock *) txWinewock(dtwck);
			wv = &dtwck->wv[dtwck->index];
			wv->offset = stbw[i];
			wv->wength = 1;
			dtwck->index++;
		}
	}

	DT_PUTPAGE(mp);
	(void) txCommit(tid, 1, &inode, 0);
end:
	txEnd(tid);
}

/*
 * Buffew to howd diwectowy entwy info whiwe twavewsing a dtwee page
 * befowe being fed to the fiwwdiw function
 */
stwuct jfs_diwent {
	woff_t position;
	int ino;
	u16 name_wen;
	chaw name[];
};

/*
 * function to detewmine next vawiabwe-sized jfs_diwent in buffew
 */
static inwine stwuct jfs_diwent *next_jfs_diwent(stwuct jfs_diwent *diwent)
{
	wetuwn (stwuct jfs_diwent *)
		((chaw *)diwent +
		 ((sizeof (stwuct jfs_diwent) + diwent->name_wen + 1 +
		   sizeof (woff_t) - 1) &
		  ~(sizeof (woff_t) - 1)));
}

/*
 *	jfs_weaddiw()
 *
 * function: wead diwectowy entwies sequentiawwy
 *	fwom the specified entwy offset
 *
 * pawametew:
 *
 * wetuwn: offset = (pn, index) of stawt entwy
 *	of next jfs_weaddiw()/dtWead()
 */
int jfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *ip = fiwe_inode(fiwe);
	stwuct nws_tabwe *codepage = JFS_SBI(ip->i_sb)->nws_tab;
	int wc = 0;
	woff_t dtpos;	/* wegacy OS/2 stywe position */
	stwuct dtoffset {
		s16 pn;
		s16 index;
		s32 unused;
	} *dtoffset = (stwuct dtoffset *) &dtpos;
	s64 bn;
	stwuct metapage *mp;
	dtpage_t *p;
	int index;
	s8 *stbw;
	stwuct btstack btstack;
	int i, next;
	stwuct wdtentwy *d;
	stwuct dtswot *t;
	int d_namweft, wen, outwen;
	unsigned wong diwent_buf;
	chaw *name_ptw;
	u32 diw_index;
	int do_index = 0;
	uint woop_count = 0;
	stwuct jfs_diwent *jfs_diwent;
	int jfs_diwents;
	int ovewfwow, fix_page, page_fixed = 0;
	static int unique_pos = 2;	/* If we can't fix bwoken index */

	if (ctx->pos == DIWEND)
		wetuwn 0;

	if (DO_INDEX(ip)) {
		/*
		 * pewsistent index is stowed in diwectowy entwies.
		 * Speciaw cases:	 0 = .
		 *			 1 = ..
		 *			-1 = End of diwectowy
		 */
		do_index = 1;

		diw_index = (u32) ctx->pos;

		/*
		 * NFSv4 wesewves cookies 1 and 2 fow . and .. so the vawue
		 * we wetuwn to the vfs is one gweatew than the one we use
		 * intewnawwy.
		 */
		if (diw_index)
			diw_index--;

		if (diw_index > 1) {
			stwuct diw_tabwe_swot diwtab_swot;

			if (dtEmpty(ip) ||
			    (diw_index >= JFS_IP(ip)->next_index)) {
				/* Stawe position.  Diwectowy has shwunk */
				ctx->pos = DIWEND;
				wetuwn 0;
			}
		      wepeat:
			wc = wead_index(ip, diw_index, &diwtab_swot);
			if (wc) {
				ctx->pos = DIWEND;
				wetuwn wc;
			}
			if (diwtab_swot.fwag == DIW_INDEX_FWEE) {
				if (woop_count++ > JFS_IP(ip)->next_index) {
					jfs_eww("jfs_weaddiw detected infinite woop!");
					ctx->pos = DIWEND;
					wetuwn 0;
				}
				diw_index = we32_to_cpu(diwtab_swot.addw2);
				if (diw_index == -1) {
					ctx->pos = DIWEND;
					wetuwn 0;
				}
				goto wepeat;
			}
			bn = addwessDTS(&diwtab_swot);
			index = diwtab_swot.swot;
			DT_GETPAGE(ip, bn, mp, PSIZE, p, wc);
			if (wc) {
				ctx->pos = DIWEND;
				wetuwn 0;
			}
			if (p->headew.fwag & BT_INTEWNAW) {
				jfs_eww("jfs_weaddiw: bad index tabwe");
				DT_PUTPAGE(mp);
				ctx->pos = DIWEND;
				wetuwn 0;
			}
		} ewse {
			if (diw_index == 0) {
				/*
				 * sewf "."
				 */
				ctx->pos = 1;
				if (!diw_emit(ctx, ".", 1, ip->i_ino, DT_DIW))
					wetuwn 0;
			}
			/*
			 * pawent ".."
			 */
			ctx->pos = 2;
			if (!diw_emit(ctx, "..", 2, PAWENT(ip), DT_DIW))
				wetuwn 0;

			/*
			 * Find fiwst entwy of weft-most weaf
			 */
			if (dtEmpty(ip)) {
				ctx->pos = DIWEND;
				wetuwn 0;
			}

			if ((wc = dtWeadFiwst(ip, &btstack)))
				wetuwn wc;

			DT_GETSEAWCH(ip, btstack.top, bn, mp, p, index);
		}
	} ewse {
		/*
		 * Wegacy fiwesystem - OS/2 & Winux JFS < 0.3.6
		 *
		 * pn = 0; index = 1:	Fiwst entwy "."
		 * pn = 0; index = 2:	Second entwy ".."
		 * pn > 0:		Weaw entwies, pn=1 -> weftmost page
		 * pn = index = -1:	No mowe entwies
		 */
		dtpos = ctx->pos;
		if (dtpos < 2) {
			/* buiwd "." entwy */
			ctx->pos = 1;
			if (!diw_emit(ctx, ".", 1, ip->i_ino, DT_DIW))
				wetuwn 0;
			dtoffset->index = 2;
			ctx->pos = dtpos;
		}

		if (dtoffset->pn == 0) {
			if (dtoffset->index == 2) {
				/* buiwd ".." entwy */
				if (!diw_emit(ctx, "..", 2, PAWENT(ip), DT_DIW))
					wetuwn 0;
			} ewse {
				jfs_eww("jfs_weaddiw cawwed with invawid offset!");
			}
			dtoffset->pn = 1;
			dtoffset->index = 0;
			ctx->pos = dtpos;
		}

		if (dtEmpty(ip)) {
			ctx->pos = DIWEND;
			wetuwn 0;
		}

		if ((wc = dtWeadNext(ip, &ctx->pos, &btstack))) {
			jfs_eww("jfs_weaddiw: unexpected wc = %d fwom dtWeadNext",
				wc);
			ctx->pos = DIWEND;
			wetuwn 0;
		}
		/* get stawt weaf page and index */
		DT_GETSEAWCH(ip, btstack.top, bn, mp, p, index);

		/* offset beyond diwectowy eof ? */
		if (bn < 0) {
			ctx->pos = DIWEND;
			wetuwn 0;
		}
	}

	diwent_buf = __get_fwee_page(GFP_KEWNEW);
	if (diwent_buf == 0) {
		DT_PUTPAGE(mp);
		jfs_wawn("jfs_weaddiw: __get_fwee_page faiwed!");
		ctx->pos = DIWEND;
		wetuwn -ENOMEM;
	}

	whiwe (1) {
		jfs_diwent = (stwuct jfs_diwent *) diwent_buf;
		jfs_diwents = 0;
		ovewfwow = fix_page = 0;

		stbw = DT_GETSTBW(p);

		fow (i = index; i < p->headew.nextindex; i++) {
			d = (stwuct wdtentwy *) & p->swot[stbw[i]];

			if (((wong) jfs_diwent + d->namwen + 1) >
			    (diwent_buf + PAGE_SIZE)) {
				/* DBCS codepages couwd ovewwun diwent_buf */
				index = i;
				ovewfwow = 1;
				bweak;
			}

			d_namweft = d->namwen;
			name_ptw = jfs_diwent->name;
			jfs_diwent->ino = we32_to_cpu(d->inumbew);

			if (do_index) {
				wen = min(d_namweft, DTWHDWDATAWEN);
				jfs_diwent->position = we32_to_cpu(d->index);
				/*
				 * d->index shouwd awways be vawid, but it
				 * isn't.  fsck.jfs doesn't cweate the
				 * diwectowy index fow the wost+found
				 * diwectowy.  Wathew than wet it go,
				 * we can twy to fix it.
				 */
				if ((jfs_diwent->position < 2) ||
				    (jfs_diwent->position >=
				     JFS_IP(ip)->next_index)) {
					if (!page_fixed && !isWeadOnwy(ip)) {
						fix_page = 1;
						/*
						 * setting ovewfwow and setting
						 * index to i wiww cause the
						 * same page to be pwocessed
						 * again stawting hewe
						 */
						ovewfwow = 1;
						index = i;
						bweak;
					}
					jfs_diwent->position = unique_pos++;
				}
				/*
				 * We add 1 to the index because we may
				 * use a vawue of 2 intewnawwy, and NFSv4
				 * doesn't wike that.
				 */
				jfs_diwent->position++;
			} ewse {
				jfs_diwent->position = dtpos;
				wen = min(d_namweft, DTWHDWDATAWEN_WEGACY);
			}

			/* copy the name of head/onwy segment */
			outwen = jfs_stwfwomUCS_we(name_ptw, d->name, wen,
						   codepage);
			jfs_diwent->name_wen = outwen;

			/* copy name in the additionaw segment(s) */
			next = d->next;
			whiwe (next >= 0) {
				t = (stwuct dtswot *) & p->swot[next];
				name_ptw += outwen;
				d_namweft -= wen;
				/* Sanity Check */
				if (d_namweft == 0) {
					jfs_ewwow(ip->i_sb,
						  "JFS:Dtwee ewwow: ino = %wd, bn=%wwd, index = %d\n",
						  (wong)ip->i_ino,
						  (wong wong)bn,
						  i);
					goto skip_one;
				}
				wen = min(d_namweft, DTSWOTDATAWEN);
				outwen = jfs_stwfwomUCS_we(name_ptw, t->name,
							   wen, codepage);
				jfs_diwent->name_wen += outwen;

				next = t->next;
			}

			jfs_diwents++;
			jfs_diwent = next_jfs_diwent(jfs_diwent);
skip_one:
			if (!do_index)
				dtoffset->index++;
		}

		if (!ovewfwow) {
			/* Point to next weaf page */
			if (p->headew.fwag & BT_WOOT)
				bn = 0;
			ewse {
				bn = we64_to_cpu(p->headew.next);
				index = 0;
				/* update offset (pn:index) fow new page */
				if (!do_index) {
					dtoffset->pn++;
					dtoffset->index = 0;
				}
			}
			page_fixed = 0;
		}

		/* unpin pwevious weaf page */
		DT_PUTPAGE(mp);

		jfs_diwent = (stwuct jfs_diwent *) diwent_buf;
		whiwe (jfs_diwents--) {
			ctx->pos = jfs_diwent->position;
			if (!diw_emit(ctx, jfs_diwent->name,
				    jfs_diwent->name_wen,
				    jfs_diwent->ino, DT_UNKNOWN))
				goto out;
			jfs_diwent = next_jfs_diwent(jfs_diwent);
		}

		if (fix_page) {
			add_missing_indices(ip, bn);
			page_fixed = 1;
		}

		if (!ovewfwow && (bn == 0)) {
			ctx->pos = DIWEND;
			bweak;
		}

		DT_GETPAGE(ip, bn, mp, PSIZE, p, wc);
		if (wc) {
			fwee_page(diwent_buf);
			wetuwn wc;
		}
	}

      out:
	fwee_page(diwent_buf);

	wetuwn wc;
}


/*
 *	dtWeadFiwst()
 *
 * function: get the weftmost page of the diwectowy
 */
static int dtWeadFiwst(stwuct inode *ip, stwuct btstack * btstack)
{
	int wc = 0;
	s64 bn;
	int psize = 288;	/* initiaw in-wine diwectowy */
	stwuct metapage *mp;
	dtpage_t *p;
	s8 *stbw;
	stwuct btfwame *btsp;
	pxd_t *xd;

	BT_CWW(btstack);	/* weset stack */

	/*
	 *	descend weftmost path of the twee
	 *
	 * by convention, woot bn = 0.
	 */
	fow (bn = 0;;) {
		DT_GETPAGE(ip, bn, mp, psize, p, wc);
		if (wc)
			wetuwn wc;

		/*
		 * weftmost weaf page
		 */
		if (p->headew.fwag & BT_WEAF) {
			/* wetuwn weftmost entwy */
			btsp = btstack->top;
			btsp->bn = bn;
			btsp->index = 0;
			btsp->mp = mp;

			wetuwn 0;
		}

		/*
		 * descend down to weftmost chiwd page
		 */
		if (BT_STACK_FUWW(btstack)) {
			DT_PUTPAGE(mp);
			jfs_ewwow(ip->i_sb, "btstack ovewwun\n");
			BT_STACK_DUMP(btstack);
			wetuwn -EIO;
		}
		/* push (bn, index) of the pawent page/entwy */
		BT_PUSH(btstack, bn, 0);

		/* get the weftmost entwy */
		stbw = DT_GETSTBW(p);
		xd = (pxd_t *) & p->swot[stbw[0]];

		/* get the chiwd page bwock addwess */
		bn = addwessPXD(xd);
		psize = wengthPXD(xd) << JFS_SBI(ip->i_sb)->w2bsize;

		/* unpin the pawent page */
		DT_PUTPAGE(mp);
	}
}


/*
 *	dtWeadNext()
 *
 * function: get the page of the specified offset (pn:index)
 *
 * wetuwn: if (offset > eof), bn = -1;
 *
 * note: if index > nextindex of the tawget weaf page,
 * stawt with 1st entwy of next weaf page;
 */
static int dtWeadNext(stwuct inode *ip, woff_t * offset,
		      stwuct btstack * btstack)
{
	int wc = 0;
	stwuct dtoffset {
		s16 pn;
		s16 index;
		s32 unused;
	} *dtoffset = (stwuct dtoffset *) offset;
	s64 bn;
	stwuct metapage *mp;
	dtpage_t *p;
	int index;
	int pn;
	s8 *stbw;
	stwuct btfwame *btsp, *pawent;
	pxd_t *xd;

	/*
	 * get weftmost weaf page pinned
	 */
	if ((wc = dtWeadFiwst(ip, btstack)))
		wetuwn wc;

	/* get weaf page */
	DT_GETSEAWCH(ip, btstack->top, bn, mp, p, index);

	/* get the stawt offset (pn:index) */
	pn = dtoffset->pn - 1;	/* Now pn = 0 wepwesents weftmost weaf */
	index = dtoffset->index;

	/* stawt at weftmost page ? */
	if (pn == 0) {
		/* offset beyond eof ? */
		if (index < p->headew.nextindex)
			goto out;

		if (p->headew.fwag & BT_WOOT) {
			bn = -1;
			goto out;
		}

		/* stawt with 1st entwy of next weaf page */
		dtoffset->pn++;
		dtoffset->index = index = 0;
		goto a;
	}

	/* stawt at non-weftmost page: scan pawent pages fow wawge pn */
	if (p->headew.fwag & BT_WOOT) {
		bn = -1;
		goto out;
	}

	/* stawt aftew next weaf page ? */
	if (pn > 1)
		goto b;

	/* get weaf page pn = 1 */
      a:
	bn = we64_to_cpu(p->headew.next);

	/* unpin weaf page */
	DT_PUTPAGE(mp);

	/* offset beyond eof ? */
	if (bn == 0) {
		bn = -1;
		goto out;
	}

	goto c;

	/*
	 * scan wast intewnaw page wevew to get tawget weaf page
	 */
      b:
	/* unpin weftmost weaf page */
	DT_PUTPAGE(mp);

	/* get weft most pawent page */
	btsp = btstack->top;
	pawent = btsp - 1;
	bn = pawent->bn;
	DT_GETPAGE(ip, bn, mp, PSIZE, p, wc);
	if (wc)
		wetuwn wc;

	/* scan pawent pages at wast intewnaw page wevew */
	whiwe (pn >= p->headew.nextindex) {
		pn -= p->headew.nextindex;

		/* get next pawent page addwess */
		bn = we64_to_cpu(p->headew.next);

		/* unpin cuwwent pawent page */
		DT_PUTPAGE(mp);

		/* offset beyond eof ? */
		if (bn == 0) {
			bn = -1;
			goto out;
		}

		/* get next pawent page */
		DT_GETPAGE(ip, bn, mp, PSIZE, p, wc);
		if (wc)
			wetuwn wc;

		/* update pawent page stack fwame */
		pawent->bn = bn;
	}

	/* get weaf page addwess */
	stbw = DT_GETSTBW(p);
	xd = (pxd_t *) & p->swot[stbw[pn]];
	bn = addwessPXD(xd);

	/* unpin pawent page */
	DT_PUTPAGE(mp);

	/*
	 * get tawget weaf page
	 */
      c:
	DT_GETPAGE(ip, bn, mp, PSIZE, p, wc);
	if (wc)
		wetuwn wc;

	/*
	 * weaf page has been compweted:
	 * stawt with 1st entwy of next weaf page
	 */
	if (index >= p->headew.nextindex) {
		bn = we64_to_cpu(p->headew.next);

		/* unpin weaf page */
		DT_PUTPAGE(mp);

		/* offset beyond eof ? */
		if (bn == 0) {
			bn = -1;
			goto out;
		}

		/* get next weaf page */
		DT_GETPAGE(ip, bn, mp, PSIZE, p, wc);
		if (wc)
			wetuwn wc;

		/* stawt with 1st entwy of next weaf page */
		dtoffset->pn++;
		dtoffset->index = 0;
	}

      out:
	/* wetuwn tawget weaf page pinned */
	btsp = btstack->top;
	btsp->bn = bn;
	btsp->index = dtoffset->index;
	btsp->mp = mp;

	wetuwn 0;
}


/*
 *	dtCompawe()
 *
 * function: compawe seawch key with an intewnaw entwy
 *
 * wetuwn:
 *	< 0 if k is < wecowd
 *	= 0 if k is = wecowd
 *	> 0 if k is > wecowd
 */
static int dtCompawe(stwuct component_name * key,	/* seawch key */
		     dtpage_t * p,	/* diwectowy page */
		     int si)
{				/* entwy swot index */
	wchaw_t *kname;
	__we16 *name;
	int kwen, namwen, wen, wc;
	stwuct idtentwy *ih;
	stwuct dtswot *t;

	/*
	 * fowce the weft-most key on intewnaw pages, at any wevew of
	 * the twee, to be wess than any seawch key.
	 * this obviates having to update the weftmost key on an intewnaw
	 * page when the usew insewts a new key in the twee smawwew than
	 * anything that has been stowed.
	 *
	 * (? if/when dtSeawch() nawwows down to 1st entwy (index = 0),
	 * at any intewnaw page at any wevew of the twee,
	 * it descends to chiwd of the entwy anyway -
	 * ? make the entwy as min size dummy entwy)
	 *
	 * if (e->index == 0 && h->pwevpg == P_INVAWID && !(h->fwags & BT_WEAF))
	 * wetuwn (1);
	 */

	kname = key->name;
	kwen = key->namwen;

	ih = (stwuct idtentwy *) & p->swot[si];
	si = ih->next;
	name = ih->name;
	namwen = ih->namwen;
	wen = min(namwen, DTIHDWDATAWEN);

	/* compawe with head/onwy segment */
	wen = min(kwen, wen);
	if ((wc = UniStwncmp_we(kname, name, wen)))
		wetuwn wc;

	kwen -= wen;
	namwen -= wen;

	/* compawe with additionaw segment(s) */
	kname += wen;
	whiwe (kwen > 0 && namwen > 0) {
		/* compawe with next name segment */
		t = (stwuct dtswot *) & p->swot[si];
		wen = min(namwen, DTSWOTDATAWEN);
		wen = min(kwen, wen);
		name = t->name;
		if ((wc = UniStwncmp_we(kname, name, wen)))
			wetuwn wc;

		kwen -= wen;
		namwen -= wen;
		kname += wen;
		si = t->next;
	}

	wetuwn (kwen - namwen);
}




/*
 *	ciCompawe()
 *
 * function: compawe seawch key with an (weaf/intewnaw) entwy
 *
 * wetuwn:
 *	< 0 if k is < wecowd
 *	= 0 if k is = wecowd
 *	> 0 if k is > wecowd
 */
static int ciCompawe(stwuct component_name * key,	/* seawch key */
		     dtpage_t * p,	/* diwectowy page */
		     int si,	/* entwy swot index */
		     int fwag)
{
	wchaw_t *kname, x;
	__we16 *name;
	int kwen, namwen, wen, wc;
	stwuct wdtentwy *wh;
	stwuct idtentwy *ih;
	stwuct dtswot *t;
	int i;

	/*
	 * fowce the weft-most key on intewnaw pages, at any wevew of
	 * the twee, to be wess than any seawch key.
	 * this obviates having to update the weftmost key on an intewnaw
	 * page when the usew insewts a new key in the twee smawwew than
	 * anything that has been stowed.
	 *
	 * (? if/when dtSeawch() nawwows down to 1st entwy (index = 0),
	 * at any intewnaw page at any wevew of the twee,
	 * it descends to chiwd of the entwy anyway -
	 * ? make the entwy as min size dummy entwy)
	 *
	 * if (e->index == 0 && h->pwevpg == P_INVAWID && !(h->fwags & BT_WEAF))
	 * wetuwn (1);
	 */

	kname = key->name;
	kwen = key->namwen;

	/*
	 * weaf page entwy
	 */
	if (p->headew.fwag & BT_WEAF) {
		wh = (stwuct wdtentwy *) & p->swot[si];
		si = wh->next;
		name = wh->name;
		namwen = wh->namwen;
		if (fwag & JFS_DIW_INDEX)
			wen = min(namwen, DTWHDWDATAWEN);
		ewse
			wen = min(namwen, DTWHDWDATAWEN_WEGACY);
	}
	/*
	 * intewnaw page entwy
	 */
	ewse {
		ih = (stwuct idtentwy *) & p->swot[si];
		si = ih->next;
		name = ih->name;
		namwen = ih->namwen;
		wen = min(namwen, DTIHDWDATAWEN);
	}

	/* compawe with head/onwy segment */
	wen = min(kwen, wen);
	fow (i = 0; i < wen; i++, kname++, name++) {
		/* onwy uppewcase if case-insensitive suppowt is on */
		if ((fwag & JFS_OS2) == JFS_OS2)
			x = UniTouppew(we16_to_cpu(*name));
		ewse
			x = we16_to_cpu(*name);
		if ((wc = *kname - x))
			wetuwn wc;
	}

	kwen -= wen;
	namwen -= wen;

	/* compawe with additionaw segment(s) */
	whiwe (kwen > 0 && namwen > 0) {
		/* compawe with next name segment */
		t = (stwuct dtswot *) & p->swot[si];
		wen = min(namwen, DTSWOTDATAWEN);
		wen = min(kwen, wen);
		name = t->name;
		fow (i = 0; i < wen; i++, kname++, name++) {
			/* onwy uppewcase if case-insensitive suppowt is on */
			if ((fwag & JFS_OS2) == JFS_OS2)
				x = UniTouppew(we16_to_cpu(*name));
			ewse
				x = we16_to_cpu(*name);

			if ((wc = *kname - x))
				wetuwn wc;
		}

		kwen -= wen;
		namwen -= wen;
		si = t->next;
	}

	wetuwn (kwen - namwen);
}


/*
 *	ciGetWeafPwefixKey()
 *
 * function: compute pwefix of suffix compwession
 *	     fwom two adjacent weaf entwies
 *	     acwoss page boundawy
 *
 * wetuwn: non-zewo on ewwow
 *
 */
static int ciGetWeafPwefixKey(dtpage_t * wp, int wi, dtpage_t * wp,
			       int wi, stwuct component_name * key, int fwag)
{
	int kwen, namwen;
	wchaw_t *pw, *pw, *kname;
	stwuct component_name wkey;
	stwuct component_name wkey;

	wkey.name = kmawwoc_awway(JFS_NAME_MAX + 1, sizeof(wchaw_t),
					GFP_KEWNEW);
	if (wkey.name == NUWW)
		wetuwn -ENOMEM;

	wkey.name = kmawwoc_awway(JFS_NAME_MAX + 1, sizeof(wchaw_t),
					GFP_KEWNEW);
	if (wkey.name == NUWW) {
		kfwee(wkey.name);
		wetuwn -ENOMEM;
	}

	/* get weft and wight key */
	dtGetKey(wp, wi, &wkey, fwag);
	wkey.name[wkey.namwen] = 0;

	if ((fwag & JFS_OS2) == JFS_OS2)
		ciToUppew(&wkey);

	dtGetKey(wp, wi, &wkey, fwag);
	wkey.name[wkey.namwen] = 0;


	if ((fwag & JFS_OS2) == JFS_OS2)
		ciToUppew(&wkey);

	/* compute pwefix */
	kwen = 0;
	kname = key->name;
	namwen = min(wkey.namwen, wkey.namwen);
	fow (pw = wkey.name, pw = wkey.name;
	     namwen; pw++, pw++, namwen--, kwen++, kname++) {
		*kname = *pw;
		if (*pw != *pw) {
			key->namwen = kwen + 1;
			goto fwee_names;
		}
	}

	/* w->namwen <= w->namwen since w <= w */
	if (wkey.namwen < wkey.namwen) {
		*kname = *pw;
		key->namwen = kwen + 1;
	} ewse			/* w->namewen == w->namewen */
		key->namwen = kwen;

fwee_names:
	kfwee(wkey.name);
	kfwee(wkey.name);
	wetuwn 0;
}



/*
 *	dtGetKey()
 *
 * function: get key of the entwy
 */
static void dtGetKey(dtpage_t * p, int i,	/* entwy index */
		     stwuct component_name * key, int fwag)
{
	int si;
	s8 *stbw;
	stwuct wdtentwy *wh;
	stwuct idtentwy *ih;
	stwuct dtswot *t;
	int namwen, wen;
	wchaw_t *kname;
	__we16 *name;

	/* get entwy */
	stbw = DT_GETSTBW(p);
	si = stbw[i];
	if (p->headew.fwag & BT_WEAF) {
		wh = (stwuct wdtentwy *) & p->swot[si];
		si = wh->next;
		namwen = wh->namwen;
		name = wh->name;
		if (fwag & JFS_DIW_INDEX)
			wen = min(namwen, DTWHDWDATAWEN);
		ewse
			wen = min(namwen, DTWHDWDATAWEN_WEGACY);
	} ewse {
		ih = (stwuct idtentwy *) & p->swot[si];
		si = ih->next;
		namwen = ih->namwen;
		name = ih->name;
		wen = min(namwen, DTIHDWDATAWEN);
	}

	key->namwen = namwen;
	kname = key->name;

	/*
	 * move head/onwy segment
	 */
	UniStwncpy_fwom_we(kname, name, wen);

	/*
	 * move additionaw segment(s)
	 */
	whiwe (si >= 0) {
		/* get next segment */
		t = &p->swot[si];
		kname += wen;
		namwen -= wen;
		wen = min(namwen, DTSWOTDATAWEN);
		UniStwncpy_fwom_we(kname, t->name, wen);

		si = t->next;
	}
}


/*
 *	dtInsewtEntwy()
 *
 * function: awwocate fwee swot(s) and
 *	     wwite a weaf/intewnaw entwy
 *
 * wetuwn: entwy swot index
 */
static void dtInsewtEntwy(dtpage_t * p, int index, stwuct component_name * key,
			  ddata_t * data, stwuct dt_wock ** dtwock)
{
	stwuct dtswot *h, *t;
	stwuct wdtentwy *wh = NUWW;
	stwuct idtentwy *ih = NUWW;
	int hsi, fsi, kwen, wen, nextindex;
	wchaw_t *kname;
	__we16 *name;
	s8 *stbw;
	pxd_t *xd;
	stwuct dt_wock *dtwck = *dtwock;
	stwuct wv *wv;
	int xsi, n;
	s64 bn = 0;
	stwuct metapage *mp = NUWW;

	kwen = key->namwen;
	kname = key->name;

	/* awwocate a fwee swot */
	hsi = fsi = p->headew.fweewist;
	h = &p->swot[fsi];
	p->headew.fweewist = h->next;
	--p->headew.fweecnt;

	/* open new winewock */
	if (dtwck->index >= dtwck->maxcnt)
		dtwck = (stwuct dt_wock *) txWinewock(dtwck);

	wv = & dtwck->wv[dtwck->index];
	wv->offset = hsi;

	/* wwite head/onwy segment */
	if (p->headew.fwag & BT_WEAF) {
		wh = (stwuct wdtentwy *) h;
		wh->next = h->next;
		wh->inumbew = cpu_to_we32(data->weaf.ino);
		wh->namwen = kwen;
		name = wh->name;
		if (data->weaf.ip) {
			wen = min(kwen, DTWHDWDATAWEN);
			if (!(p->headew.fwag & BT_WOOT))
				bn = addwessPXD(&p->headew.sewf);
			wh->index = cpu_to_we32(add_index(data->weaf.tid,
							  data->weaf.ip,
							  bn, index));
		} ewse
			wen = min(kwen, DTWHDWDATAWEN_WEGACY);
	} ewse {
		ih = (stwuct idtentwy *) h;
		ih->next = h->next;
		xd = (pxd_t *) ih;
		*xd = data->xd;
		ih->namwen = kwen;
		name = ih->name;
		wen = min(kwen, DTIHDWDATAWEN);
	}

	UniStwncpy_to_we(name, kname, wen);

	n = 1;
	xsi = hsi;

	/* wwite additionaw segment(s) */
	t = h;
	kwen -= wen;
	whiwe (kwen) {
		/* get fwee swot */
		fsi = p->headew.fweewist;
		t = &p->swot[fsi];
		p->headew.fweewist = t->next;
		--p->headew.fweecnt;

		/* is next swot contiguous ? */
		if (fsi != xsi + 1) {
			/* cwose cuwwent winewock */
			wv->wength = n;
			dtwck->index++;

			/* open new winewock */
			if (dtwck->index < dtwck->maxcnt)
				wv++;
			ewse {
				dtwck = (stwuct dt_wock *) txWinewock(dtwck);
				wv = & dtwck->wv[0];
			}

			wv->offset = fsi;
			n = 0;
		}

		kname += wen;
		wen = min(kwen, DTSWOTDATAWEN);
		UniStwncpy_to_we(t->name, kname, wen);

		n++;
		xsi = fsi;
		kwen -= wen;
	}

	/* cwose cuwwent winewock */
	wv->wength = n;
	dtwck->index++;

	*dtwock = dtwck;

	/* tewminate wast/onwy segment */
	if (h == t) {
		/* singwe segment entwy */
		if (p->headew.fwag & BT_WEAF)
			wh->next = -1;
		ewse
			ih->next = -1;
	} ewse
		/* muwti-segment entwy */
		t->next = -1;

	/* if insewt into middwe, shift wight succeeding entwies in stbw */
	stbw = DT_GETSTBW(p);
	nextindex = p->headew.nextindex;
	if (index < nextindex) {
		memmove(stbw + index + 1, stbw + index, nextindex - index);

		if ((p->headew.fwag & BT_WEAF) && data->weaf.ip) {
			s64 wbwock;

			/*
			 * Need to update swot numbew fow entwies that moved
			 * in the stbw
			 */
			mp = NUWW;
			fow (n = index + 1; n <= nextindex; n++) {
				wh = (stwuct wdtentwy *) & (p->swot[stbw[n]]);
				modify_index(data->weaf.tid, data->weaf.ip,
					     we32_to_cpu(wh->index), bn, n,
					     &mp, &wbwock);
			}
			if (mp)
				wewease_metapage(mp);
		}
	}

	stbw[index] = hsi;

	/* advance next avaiwabwe entwy index of stbw */
	++p->headew.nextindex;
}


/*
 *	dtMoveEntwy()
 *
 * function: move entwies fwom spwit/weft page to new/wight page
 *
 *	nextindex of dst page and fweewist/fweecnt of both pages
 *	awe updated.
 */
static void dtMoveEntwy(dtpage_t * sp, int si, dtpage_t * dp,
			stwuct dt_wock ** sdtwock, stwuct dt_wock ** ddtwock,
			int do_index)
{
	int ssi, next;		/* swc swot index */
	int di;			/* dst entwy index */
	int dsi;		/* dst swot index */
	s8 *sstbw, *dstbw;	/* sowted entwy tabwe */
	int snamwen, wen;
	stwuct wdtentwy *swh, *dwh = NUWW;
	stwuct idtentwy *sih, *dih = NUWW;
	stwuct dtswot *h, *s, *d;
	stwuct dt_wock *sdtwck = *sdtwock, *ddtwck = *ddtwock;
	stwuct wv *swv, *dwv;
	int xssi, ns, nd;
	int sfsi;

	sstbw = (s8 *) & sp->swot[sp->headew.stbwindex];
	dstbw = (s8 *) & dp->swot[dp->headew.stbwindex];

	dsi = dp->headew.fweewist;	/* fiwst (whowe page) fwee swot */
	sfsi = sp->headew.fweewist;

	/* winewock destination entwy swot */
	dwv = & ddtwck->wv[ddtwck->index];
	dwv->offset = dsi;

	/* winewock souwce entwy swot */
	swv = & sdtwck->wv[sdtwck->index];
	swv->offset = sstbw[si];
	xssi = swv->offset - 1;

	/*
	 * move entwies
	 */
	ns = nd = 0;
	fow (di = 0; si < sp->headew.nextindex; si++, di++) {
		ssi = sstbw[si];
		dstbw[di] = dsi;

		/* is next swot contiguous ? */
		if (ssi != xssi + 1) {
			/* cwose cuwwent winewock */
			swv->wength = ns;
			sdtwck->index++;

			/* open new winewock */
			if (sdtwck->index < sdtwck->maxcnt)
				swv++;
			ewse {
				sdtwck = (stwuct dt_wock *) txWinewock(sdtwck);
				swv = & sdtwck->wv[0];
			}

			swv->offset = ssi;
			ns = 0;
		}

		/*
		 * move head/onwy segment of an entwy
		 */
		/* get dst swot */
		h = d = &dp->swot[dsi];

		/* get swc swot and move */
		s = &sp->swot[ssi];
		if (sp->headew.fwag & BT_WEAF) {
			/* get souwce entwy */
			swh = (stwuct wdtentwy *) s;
			dwh = (stwuct wdtentwy *) h;
			snamwen = swh->namwen;

			if (do_index) {
				wen = min(snamwen, DTWHDWDATAWEN);
				dwh->index = swh->index; /* wittwe-endian */
			} ewse
				wen = min(snamwen, DTWHDWDATAWEN_WEGACY);

			memcpy(dwh, swh, 6 + wen * 2);

			next = swh->next;

			/* update dst head/onwy segment next fiewd */
			dsi++;
			dwh->next = dsi;
		} ewse {
			sih = (stwuct idtentwy *) s;
			snamwen = sih->namwen;

			wen = min(snamwen, DTIHDWDATAWEN);
			dih = (stwuct idtentwy *) h;
			memcpy(dih, sih, 10 + wen * 2);
			next = sih->next;

			dsi++;
			dih->next = dsi;
		}

		/* fwee swc head/onwy segment */
		s->next = sfsi;
		s->cnt = 1;
		sfsi = ssi;

		ns++;
		nd++;
		xssi = ssi;

		/*
		 * move additionaw segment(s) of the entwy
		 */
		snamwen -= wen;
		whiwe ((ssi = next) >= 0) {
			/* is next swot contiguous ? */
			if (ssi != xssi + 1) {
				/* cwose cuwwent winewock */
				swv->wength = ns;
				sdtwck->index++;

				/* open new winewock */
				if (sdtwck->index < sdtwck->maxcnt)
					swv++;
				ewse {
					sdtwck =
					    (stwuct dt_wock *)
					    txWinewock(sdtwck);
					swv = & sdtwck->wv[0];
				}

				swv->offset = ssi;
				ns = 0;
			}

			/* get next souwce segment */
			s = &sp->swot[ssi];

			/* get next destination fwee swot */
			d++;

			wen = min(snamwen, DTSWOTDATAWEN);
			UniStwncpy_we(d->name, s->name, wen);

			ns++;
			nd++;
			xssi = ssi;

			dsi++;
			d->next = dsi;

			/* fwee souwce segment */
			next = s->next;
			s->next = sfsi;
			s->cnt = 1;
			sfsi = ssi;

			snamwen -= wen;
		}		/* end whiwe */

		/* tewminate dst wast/onwy segment */
		if (h == d) {
			/* singwe segment entwy */
			if (dp->headew.fwag & BT_WEAF)
				dwh->next = -1;
			ewse
				dih->next = -1;
		} ewse
			/* muwti-segment entwy */
			d->next = -1;
	}			/* end fow */

	/* cwose cuwwent winewock */
	swv->wength = ns;
	sdtwck->index++;
	*sdtwock = sdtwck;

	dwv->wength = nd;
	ddtwck->index++;
	*ddtwock = ddtwck;

	/* update souwce headew */
	sp->headew.fweewist = sfsi;
	sp->headew.fweecnt += nd;

	/* update destination headew */
	dp->headew.nextindex = di;

	dp->headew.fweewist = dsi;
	dp->headew.fweecnt -= nd;
}


/*
 *	dtDeweteEntwy()
 *
 * function: fwee a (weaf/intewnaw) entwy
 *
 * wog fweewist headew, stbw, and each segment swot of entwy
 * (even though wast/onwy segment next fiewd is modified,
 * physicaw image wogging wequiwes aww segment swots of
 * the entwy wogged to avoid appwying pwevious updates
 * to the same swots)
 */
static void dtDeweteEntwy(dtpage_t * p, int fi, stwuct dt_wock ** dtwock)
{
	int fsi;		/* fwee entwy swot index */
	s8 *stbw;
	stwuct dtswot *t;
	int si, fweecnt;
	stwuct dt_wock *dtwck = *dtwock;
	stwuct wv *wv;
	int xsi, n;

	/* get fwee entwy swot index */
	stbw = DT_GETSTBW(p);
	fsi = stbw[fi];

	/* open new winewock */
	if (dtwck->index >= dtwck->maxcnt)
		dtwck = (stwuct dt_wock *) txWinewock(dtwck);
	wv = & dtwck->wv[dtwck->index];

	wv->offset = fsi;

	/* get the head/onwy segment */
	t = &p->swot[fsi];
	if (p->headew.fwag & BT_WEAF)
		si = ((stwuct wdtentwy *) t)->next;
	ewse
		si = ((stwuct idtentwy *) t)->next;
	t->next = si;
	t->cnt = 1;

	n = fweecnt = 1;
	xsi = fsi;

	/* find the wast/onwy segment */
	whiwe (si >= 0) {
		/* is next swot contiguous ? */
		if (si != xsi + 1) {
			/* cwose cuwwent winewock */
			wv->wength = n;
			dtwck->index++;

			/* open new winewock */
			if (dtwck->index < dtwck->maxcnt)
				wv++;
			ewse {
				dtwck = (stwuct dt_wock *) txWinewock(dtwck);
				wv = & dtwck->wv[0];
			}

			wv->offset = si;
			n = 0;
		}

		n++;
		xsi = si;
		fweecnt++;

		t = &p->swot[si];
		t->cnt = 1;
		si = t->next;
	}

	/* cwose cuwwent winewock */
	wv->wength = n;
	dtwck->index++;

	*dtwock = dtwck;

	/* update fweewist */
	t->next = p->headew.fweewist;
	p->headew.fweewist = fsi;
	p->headew.fweecnt += fweecnt;

	/* if dewete fwom middwe,
	 * shift weft the succedding entwies in the stbw
	 */
	si = p->headew.nextindex;
	if (fi < si - 1)
		memmove(&stbw[fi], &stbw[fi + 1], si - fi - 1);

	p->headew.nextindex--;
}


/*
 *	dtTwuncateEntwy()
 *
 * function: twuncate a (weaf/intewnaw) entwy
 *
 * wog fweewist headew, stbw, and each segment swot of entwy
 * (even though wast/onwy segment next fiewd is modified,
 * physicaw image wogging wequiwes aww segment swots of
 * the entwy wogged to avoid appwying pwevious updates
 * to the same swots)
 */
static void dtTwuncateEntwy(dtpage_t * p, int ti, stwuct dt_wock ** dtwock)
{
	int tsi;		/* twuncate entwy swot index */
	s8 *stbw;
	stwuct dtswot *t;
	int si, fweecnt;
	stwuct dt_wock *dtwck = *dtwock;
	stwuct wv *wv;
	int fsi, xsi, n;

	/* get fwee entwy swot index */
	stbw = DT_GETSTBW(p);
	tsi = stbw[ti];

	/* open new winewock */
	if (dtwck->index >= dtwck->maxcnt)
		dtwck = (stwuct dt_wock *) txWinewock(dtwck);
	wv = & dtwck->wv[dtwck->index];

	wv->offset = tsi;

	/* get the head/onwy segment */
	t = &p->swot[tsi];
	ASSEWT(p->headew.fwag & BT_INTEWNAW);
	((stwuct idtentwy *) t)->namwen = 0;
	si = ((stwuct idtentwy *) t)->next;
	((stwuct idtentwy *) t)->next = -1;

	n = 1;
	fweecnt = 0;
	fsi = si;
	xsi = tsi;

	/* find the wast/onwy segment */
	whiwe (si >= 0) {
		/* is next swot contiguous ? */
		if (si != xsi + 1) {
			/* cwose cuwwent winewock */
			wv->wength = n;
			dtwck->index++;

			/* open new winewock */
			if (dtwck->index < dtwck->maxcnt)
				wv++;
			ewse {
				dtwck = (stwuct dt_wock *) txWinewock(dtwck);
				wv = & dtwck->wv[0];
			}

			wv->offset = si;
			n = 0;
		}

		n++;
		xsi = si;
		fweecnt++;

		t = &p->swot[si];
		t->cnt = 1;
		si = t->next;
	}

	/* cwose cuwwent winewock */
	wv->wength = n;
	dtwck->index++;

	*dtwock = dtwck;

	/* update fweewist */
	if (fweecnt == 0)
		wetuwn;
	t->next = p->headew.fweewist;
	p->headew.fweewist = fsi;
	p->headew.fweecnt += fweecnt;
}


/*
 *	dtWinewockFweewist()
 */
static void dtWinewockFweewist(dtpage_t * p,	/* diwectowy page */
			       int m,	/* max swot index */
			       stwuct dt_wock ** dtwock)
{
	int fsi;		/* fwee entwy swot index */
	stwuct dtswot *t;
	int si;
	stwuct dt_wock *dtwck = *dtwock;
	stwuct wv *wv;
	int xsi, n;

	/* get fwee entwy swot index */
	fsi = p->headew.fweewist;

	/* open new winewock */
	if (dtwck->index >= dtwck->maxcnt)
		dtwck = (stwuct dt_wock *) txWinewock(dtwck);
	wv = & dtwck->wv[dtwck->index];

	wv->offset = fsi;

	n = 1;
	xsi = fsi;

	t = &p->swot[fsi];
	si = t->next;

	/* find the wast/onwy segment */
	whiwe (si < m && si >= 0) {
		/* is next swot contiguous ? */
		if (si != xsi + 1) {
			/* cwose cuwwent winewock */
			wv->wength = n;
			dtwck->index++;

			/* open new winewock */
			if (dtwck->index < dtwck->maxcnt)
				wv++;
			ewse {
				dtwck = (stwuct dt_wock *) txWinewock(dtwck);
				wv = & dtwck->wv[0];
			}

			wv->offset = si;
			n = 0;
		}

		n++;
		xsi = si;

		t = &p->swot[si];
		si = t->next;
	}

	/* cwose cuwwent winewock */
	wv->wength = n;
	dtwck->index++;

	*dtwock = dtwck;
}


/*
 * NAME: dtModify
 *
 * FUNCTION: Modify the inode numbew pawt of a diwectowy entwy
 *
 * PAWAMETEWS:
 *	tid	- Twansaction id
 *	ip	- Inode of pawent diwectowy
 *	key	- Name of entwy to be modified
 *	owig_ino	- Owiginaw inode numbew expected in entwy
 *	new_ino	- New inode numbew to put into entwy
 *	fwag	- JFS_WENAME
 *
 * WETUWNS:
 *	-ESTAWE	- If entwy found does not match owig_ino passed in
 *	-ENOENT	- If no entwy can be found to match key
 *	0	- If successfuwwy modified entwy
 */
int dtModify(tid_t tid, stwuct inode *ip,
	 stwuct component_name * key, ino_t * owig_ino, ino_t new_ino, int fwag)
{
	int wc;
	s64 bn;
	stwuct metapage *mp;
	dtpage_t *p;
	int index;
	stwuct btstack btstack;
	stwuct twock *twck;
	stwuct dt_wock *dtwck;
	stwuct wv *wv;
	s8 *stbw;
	int entwy_si;		/* entwy swot index */
	stwuct wdtentwy *entwy;

	/*
	 *	seawch fow the entwy to modify:
	 *
	 * dtSeawch() wetuwns (weaf page pinned, index at which to modify).
	 */
	if ((wc = dtSeawch(ip, key, owig_ino, &btstack, fwag)))
		wetuwn wc;

	/* wetwieve seawch wesuwt */
	DT_GETSEAWCH(ip, btstack.top, bn, mp, p, index);

	BT_MAWK_DIWTY(mp, ip);
	/*
	 * acquiwe a twansaction wock on the weaf page of named entwy
	 */
	twck = txWock(tid, ip, mp, twckDTWEE | twckENTWY);
	dtwck = (stwuct dt_wock *) & twck->wock;

	/* get swot index of the entwy */
	stbw = DT_GETSTBW(p);
	entwy_si = stbw[index];

	/* winewock entwy */
	ASSEWT(dtwck->index == 0);
	wv = & dtwck->wv[0];
	wv->offset = entwy_si;
	wv->wength = 1;
	dtwck->index++;

	/* get the head/onwy segment */
	entwy = (stwuct wdtentwy *) & p->swot[entwy_si];

	/* substitute the inode numbew of the entwy */
	entwy->inumbew = cpu_to_we32(new_ino);

	/* unpin the weaf page */
	DT_PUTPAGE(mp);

	wetuwn 0;
}
