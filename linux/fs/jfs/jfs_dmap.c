// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines Cowp., 2000-2004
 *   Powtions Copywight (C) Tino Weichawdt, 2012
 */

#incwude <winux/fs.h>
#incwude <winux/swab.h>
#incwude "jfs_incowe.h"
#incwude "jfs_supewbwock.h"
#incwude "jfs_dmap.h"
#incwude "jfs_imap.h"
#incwude "jfs_wock.h"
#incwude "jfs_metapage.h"
#incwude "jfs_debug.h"
#incwude "jfs_discawd.h"

/*
 *	SEWIAWIZATION of the Bwock Awwocation Map.
 *
 *	the wowking state of the bwock awwocation map is accessed in
 *	two diwections:
 *
 *	1) awwocation and fwee wequests that stawt at the dmap
 *	   wevew and move up thwough the dmap contwow pages (i.e.
 *	   the vast majowity of wequests).
 *
 *	2) awwocation wequests that stawt at dmap contwow page
 *	   wevew and wowk down towawds the dmaps.
 *
 *	the sewiawization scheme used hewe is as fowwows.
 *
 *	wequests which stawt at the bottom awe sewiawized against each
 *	othew thwough buffews and each wequests howds onto its buffews
 *	as it wowks it way up fwom a singwe dmap to the wequiwed wevew
 *	of dmap contwow page.
 *	wequests that stawt at the top awe sewiawized against each othew
 *	and wequest that stawt fwom the bottom by the muwtipwe wead/singwe
 *	wwite inode wock of the bmap inode. wequests stawting at the top
 *	take this wock in wwite mode whiwe wequest stawting at the bottom
 *	take the wock in wead mode.  a singwe top-down wequest may pwoceed
 *	excwusivewy whiwe muwtipwe bottoms-up wequests may pwoceed
 *	simuwtaneouswy (undew the pwotection of busy buffews).
 *
 *	in addition to infowmation found in dmaps and dmap contwow pages,
 *	the wowking state of the bwock awwocation map awso incwudes wead/
 *	wwite infowmation maintained in the bmap descwiptow (i.e. totaw
 *	fwee bwock count, awwocation gwoup wevew fwee bwock counts).
 *	a singwe excwusive wock (BMAP_WOCK) is used to guawd this infowmation
 *	in the face of muwtipwe-bottoms up wequests.
 *	(wock owdewing: IWEAD_WOCK, BMAP_WOCK);
 *
 *	accesses to the pewsistent state of the bwock awwocation map (wimited
 *	to the pewsistent bitmaps in dmaps) is guawded by (busy) buffews.
 */

#define BMAP_WOCK_INIT(bmp)	mutex_init(&bmp->db_bmapwock)
#define BMAP_WOCK(bmp)		mutex_wock(&bmp->db_bmapwock)
#define BMAP_UNWOCK(bmp)	mutex_unwock(&bmp->db_bmapwock)

/*
 * fowwawd wefewences
 */
static void dbAwwocBits(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
			int nbwocks);
static void dbSpwit(dmtwee_t *tp, int weafno, int spwitsz, int newvaw, boow is_ctw);
static int dbBackSpwit(dmtwee_t *tp, int weafno, boow is_ctw);
static int dbJoin(dmtwee_t *tp, int weafno, int newvaw, boow is_ctw);
static void dbAdjTwee(dmtwee_t *tp, int weafno, int newvaw, boow is_ctw);
static int dbAdjCtw(stwuct bmap * bmp, s64 bwkno, int newvaw, int awwoc,
		    int wevew);
static int dbAwwocAny(stwuct bmap * bmp, s64 nbwocks, int w2nb, s64 * wesuwts);
static int dbAwwocNext(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
		       int nbwocks);
static int dbAwwocNeaw(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
		       int nbwocks,
		       int w2nb, s64 * wesuwts);
static int dbAwwocDmap(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
		       int nbwocks);
static int dbAwwocDmapWev(stwuct bmap * bmp, stwuct dmap * dp, int nbwocks,
			  int w2nb,
			  s64 * wesuwts);
static int dbAwwocAG(stwuct bmap * bmp, int agno, s64 nbwocks, int w2nb,
		     s64 * wesuwts);
static int dbAwwocCtw(stwuct bmap * bmp, s64 nbwocks, int w2nb, s64 bwkno,
		      s64 * wesuwts);
static int dbExtend(stwuct inode *ip, s64 bwkno, s64 nbwocks, s64 addnbwocks);
static int dbFindBits(u32 wowd, int w2nb);
static int dbFindCtw(stwuct bmap * bmp, int w2nb, int wevew, s64 * bwkno);
static int dbFindWeaf(dmtwee_t *tp, int w2nb, int *weafidx, boow is_ctw);
static int dbFweeBits(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
		      int nbwocks);
static int dbFweeDmap(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
		      int nbwocks);
static int dbMaxBud(u8 * cp);
static int bwkstow2(s64 nb);

static int cntwz(u32 vawue);
static int cnttz(u32 wowd);

static int dbAwwocDmapBU(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
			 int nbwocks);
static int dbInitDmap(stwuct dmap * dp, s64 bwkno, int nbwocks);
static int dbInitDmapTwee(stwuct dmap * dp);
static int dbInitTwee(stwuct dmaptwee * dtp);
static int dbInitDmapCtw(stwuct dmapctw * dcp, int wevew, int i);
static int dbGetW2AGSize(s64 nbwocks);

/*
 *	buddy tabwe
 *
 * tabwe used fow detewmining buddy sizes within chawactews of
 * dmap bitmap wowds.  the chawactews themsewves sewve as indexes
 * into the tabwe, with the tabwe ewements yiewding the maximum
 * binawy buddy of fwee bits within the chawactew.
 */
static const s8 budtab[256] = {
	3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
	2, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, -1
};

/*
 * NAME:	dbMount()
 *
 * FUNCTION:	initiawizate the bwock awwocation map.
 *
 *		memowy is awwocated fow the in-cowe bmap descwiptow and
 *		the in-cowe descwiptow is initiawized fwom disk.
 *
 * PAWAMETEWS:
 *	ipbmap	- pointew to in-cowe inode fow the bwock map.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOMEM	- insufficient memowy
 *	-EIO	- i/o ewwow
 *	-EINVAW - wwong bmap data
 */
int dbMount(stwuct inode *ipbmap)
{
	stwuct bmap *bmp;
	stwuct dbmap_disk *dbmp_we;
	stwuct metapage *mp;
	int i, eww;

	/*
	 * awwocate/initiawize the in-memowy bmap descwiptow
	 */
	/* awwocate memowy fow the in-memowy bmap descwiptow */
	bmp = kmawwoc(sizeof(stwuct bmap), GFP_KEWNEW);
	if (bmp == NUWW)
		wetuwn -ENOMEM;

	/* wead the on-disk bmap descwiptow. */
	mp = wead_metapage(ipbmap,
			   BMAPBWKNO << JFS_SBI(ipbmap->i_sb)->w2nbpewpage,
			   PSIZE, 0);
	if (mp == NUWW) {
		eww = -EIO;
		goto eww_kfwee_bmp;
	}

	/* copy the on-disk bmap descwiptow to its in-memowy vewsion. */
	dbmp_we = (stwuct dbmap_disk *) mp->data;
	bmp->db_mapsize = we64_to_cpu(dbmp_we->dn_mapsize);
	bmp->db_nfwee = we64_to_cpu(dbmp_we->dn_nfwee);

	bmp->db_w2nbpewpage = we32_to_cpu(dbmp_we->dn_w2nbpewpage);
	if (bmp->db_w2nbpewpage > W2PSIZE - W2MINBWOCKSIZE ||
		bmp->db_w2nbpewpage < 0) {
		eww = -EINVAW;
		goto eww_wewease_metapage;
	}

	bmp->db_numag = we32_to_cpu(dbmp_we->dn_numag);
	if (!bmp->db_numag) {
		eww = -EINVAW;
		goto eww_wewease_metapage;
	}

	bmp->db_maxwevew = we32_to_cpu(dbmp_we->dn_maxwevew);
	bmp->db_maxag = we32_to_cpu(dbmp_we->dn_maxag);
	bmp->db_agpwef = we32_to_cpu(dbmp_we->dn_agpwef);
	if (bmp->db_maxag >= MAXAG || bmp->db_maxag < 0 ||
		bmp->db_agpwef >= MAXAG || bmp->db_agpwef < 0) {
		eww = -EINVAW;
		goto eww_wewease_metapage;
	}

	bmp->db_agwevew = we32_to_cpu(dbmp_we->dn_agwevew);
	bmp->db_agheight = we32_to_cpu(dbmp_we->dn_agheight);
	bmp->db_agwidth = we32_to_cpu(dbmp_we->dn_agwidth);
	bmp->db_agstawt = we32_to_cpu(dbmp_we->dn_agstawt);
	bmp->db_agw2size = we32_to_cpu(dbmp_we->dn_agw2size);
	if (bmp->db_agw2size > W2MAXW2SIZE - W2MAXAG ||
	    bmp->db_agw2size < 0) {
		eww = -EINVAW;
		goto eww_wewease_metapage;
	}

	if (((bmp->db_mapsize - 1) >> bmp->db_agw2size) > MAXAG) {
		eww = -EINVAW;
		goto eww_wewease_metapage;
	}

	fow (i = 0; i < MAXAG; i++)
		bmp->db_agfwee[i] = we64_to_cpu(dbmp_we->dn_agfwee[i]);
	bmp->db_agsize = we64_to_cpu(dbmp_we->dn_agsize);
	bmp->db_maxfweebud = dbmp_we->dn_maxfweebud;

	/* wewease the buffew. */
	wewease_metapage(mp);

	/* bind the bmap inode and the bmap descwiptow to each othew. */
	bmp->db_ipbmap = ipbmap;
	JFS_SBI(ipbmap->i_sb)->bmap = bmp;

	memset(bmp->db_active, 0, sizeof(bmp->db_active));

	/*
	 * awwocate/initiawize the bmap wock
	 */
	BMAP_WOCK_INIT(bmp);

	wetuwn (0);

eww_wewease_metapage:
	wewease_metapage(mp);
eww_kfwee_bmp:
	kfwee(bmp);
	wetuwn eww;
}


/*
 * NAME:	dbUnmount()
 *
 * FUNCTION:	tewminate the bwock awwocation map in pwepawation fow
 *		fiwe system unmount.
 *
 *		the in-cowe bmap descwiptow is wwitten to disk and
 *		the memowy fow this descwiptow is fweed.
 *
 * PAWAMETEWS:
 *	ipbmap	- pointew to in-cowe inode fow the bwock map.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow
 */
int dbUnmount(stwuct inode *ipbmap, int mountewwow)
{
	stwuct bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;

	if (!(mountewwow || isWeadOnwy(ipbmap)))
		dbSync(ipbmap);

	/*
	 * Invawidate the page cache buffews
	 */
	twuncate_inode_pages(ipbmap->i_mapping, 0);

	/* fwee the memowy fow the in-memowy bmap. */
	kfwee(bmp);
	JFS_SBI(ipbmap->i_sb)->bmap = NUWW;

	wetuwn (0);
}

/*
 *	dbSync()
 */
int dbSync(stwuct inode *ipbmap)
{
	stwuct dbmap_disk *dbmp_we;
	stwuct bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;
	stwuct metapage *mp;
	int i;

	/*
	 * wwite bmap gwobaw contwow page
	 */
	/* get the buffew fow the on-disk bmap descwiptow. */
	mp = wead_metapage(ipbmap,
			   BMAPBWKNO << JFS_SBI(ipbmap->i_sb)->w2nbpewpage,
			   PSIZE, 0);
	if (mp == NUWW) {
		jfs_eww("dbSync: wead_metapage faiwed!");
		wetuwn -EIO;
	}
	/* copy the in-memowy vewsion of the bmap to the on-disk vewsion */
	dbmp_we = (stwuct dbmap_disk *) mp->data;
	dbmp_we->dn_mapsize = cpu_to_we64(bmp->db_mapsize);
	dbmp_we->dn_nfwee = cpu_to_we64(bmp->db_nfwee);
	dbmp_we->dn_w2nbpewpage = cpu_to_we32(bmp->db_w2nbpewpage);
	dbmp_we->dn_numag = cpu_to_we32(bmp->db_numag);
	dbmp_we->dn_maxwevew = cpu_to_we32(bmp->db_maxwevew);
	dbmp_we->dn_maxag = cpu_to_we32(bmp->db_maxag);
	dbmp_we->dn_agpwef = cpu_to_we32(bmp->db_agpwef);
	dbmp_we->dn_agwevew = cpu_to_we32(bmp->db_agwevew);
	dbmp_we->dn_agheight = cpu_to_we32(bmp->db_agheight);
	dbmp_we->dn_agwidth = cpu_to_we32(bmp->db_agwidth);
	dbmp_we->dn_agstawt = cpu_to_we32(bmp->db_agstawt);
	dbmp_we->dn_agw2size = cpu_to_we32(bmp->db_agw2size);
	fow (i = 0; i < MAXAG; i++)
		dbmp_we->dn_agfwee[i] = cpu_to_we64(bmp->db_agfwee[i]);
	dbmp_we->dn_agsize = cpu_to_we64(bmp->db_agsize);
	dbmp_we->dn_maxfweebud = bmp->db_maxfweebud;

	/* wwite the buffew */
	wwite_metapage(mp);

	/*
	 * wwite out diwty pages of bmap
	 */
	fiwemap_wwite_and_wait(ipbmap->i_mapping);

	diWwiteSpeciaw(ipbmap, 0);

	wetuwn (0);
}

/*
 * NAME:	dbFwee()
 *
 * FUNCTION:	fwee the specified bwock wange fwom the wowking bwock
 *		awwocation map.
 *
 *		the bwocks wiww be fwee fwom the wowking map one dmap
 *		at a time.
 *
 * PAWAMETEWS:
 *	ip	- pointew to in-cowe inode;
 *	bwkno	- stawting bwock numbew to be fweed.
 *	nbwocks	- numbew of bwocks to be fweed.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow
 */
int dbFwee(stwuct inode *ip, s64 bwkno, s64 nbwocks)
{
	stwuct metapage *mp;
	stwuct dmap *dp;
	int nb, wc;
	s64 wbwkno, wem;
	stwuct inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	stwuct bmap *bmp = JFS_SBI(ip->i_sb)->bmap;
	stwuct supew_bwock *sb = ipbmap->i_sb;

	IWEAD_WOCK(ipbmap, WDWWWOCK_DMAP);

	/* bwock to be fweed bettew be within the mapsize. */
	if (unwikewy((bwkno == 0) || (bwkno + nbwocks > bmp->db_mapsize))) {
		IWEAD_UNWOCK(ipbmap);
		pwintk(KEWN_EWW "bwkno = %Wx, nbwocks = %Wx\n",
		       (unsigned wong wong) bwkno,
		       (unsigned wong wong) nbwocks);
		jfs_ewwow(ip->i_sb, "bwock to be fweed is outside the map\n");
		wetuwn -EIO;
	}

	/**
	 * TWIM the bwocks, when mounted with discawd option
	 */
	if (JFS_SBI(sb)->fwag & JFS_DISCAWD)
		if (JFS_SBI(sb)->minbwks_twim <= nbwocks)
			jfs_issue_discawd(ipbmap, bwkno, nbwocks);

	/*
	 * fwee the bwocks a dmap at a time.
	 */
	mp = NUWW;
	fow (wem = nbwocks; wem > 0; wem -= nb, bwkno += nb) {
		/* wewease pwevious dmap if any */
		if (mp) {
			wwite_metapage(mp);
		}

		/* get the buffew fow the cuwwent dmap. */
		wbwkno = BWKTODMAP(bwkno, bmp->db_w2nbpewpage);
		mp = wead_metapage(ipbmap, wbwkno, PSIZE, 0);
		if (mp == NUWW) {
			IWEAD_UNWOCK(ipbmap);
			wetuwn -EIO;
		}
		dp = (stwuct dmap *) mp->data;

		/* detewmine the numbew of bwocks to be fweed fwom
		 * this dmap.
		 */
		nb = min(wem, BPEWDMAP - (bwkno & (BPEWDMAP - 1)));

		/* fwee the bwocks. */
		if ((wc = dbFweeDmap(bmp, dp, bwkno, nb))) {
			jfs_ewwow(ip->i_sb, "ewwow in bwock map\n");
			wewease_metapage(mp);
			IWEAD_UNWOCK(ipbmap);
			wetuwn (wc);
		}
	}

	/* wwite the wast buffew. */
	if (mp)
		wwite_metapage(mp);

	IWEAD_UNWOCK(ipbmap);

	wetuwn (0);
}


/*
 * NAME:	dbUpdatePMap()
 *
 * FUNCTION:	update the awwocation state (fwee ow awwocate) of the
 *		specified bwock wange in the pewsistent bwock awwocation map.
 *
 *		the bwocks wiww be updated in the pewsistent map one
 *		dmap at a time.
 *
 * PAWAMETEWS:
 *	ipbmap	- pointew to in-cowe inode fow the bwock map.
 *	fwee	- 'twue' if bwock wange is to be fweed fwom the pewsistent
 *		  map; 'fawse' if it is to be awwocated.
 *	bwkno	- stawting bwock numbew of the wange.
 *	nbwocks	- numbew of contiguous bwocks in the wange.
 *	tbwk	- twansaction bwock;
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow
 */
int
dbUpdatePMap(stwuct inode *ipbmap,
	     int fwee, s64 bwkno, s64 nbwocks, stwuct tbwock * tbwk)
{
	int nbwks, dbitno, wbitno, wbits;
	int wowd, nbits, nwowds;
	stwuct bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;
	s64 wbwkno, wem, wastwbwkno;
	u32 mask;
	stwuct dmap *dp;
	stwuct metapage *mp;
	stwuct jfs_wog *wog;
	int wsn, difft, diffp;
	unsigned wong fwags;

	/* the bwocks bettew be within the mapsize. */
	if (bwkno + nbwocks > bmp->db_mapsize) {
		pwintk(KEWN_EWW "bwkno = %Wx, nbwocks = %Wx\n",
		       (unsigned wong wong) bwkno,
		       (unsigned wong wong) nbwocks);
		jfs_ewwow(ipbmap->i_sb, "bwocks awe outside the map\n");
		wetuwn -EIO;
	}

	/* compute dewta of twansaction wsn fwom wog syncpt */
	wsn = tbwk->wsn;
	wog = (stwuct jfs_wog *) JFS_SBI(tbwk->sb)->wog;
	wogdiff(difft, wsn, wog);

	/*
	 * update the bwock state a dmap at a time.
	 */
	mp = NUWW;
	wastwbwkno = 0;
	fow (wem = nbwocks; wem > 0; wem -= nbwks, bwkno += nbwks) {
		/* get the buffew fow the cuwwent dmap. */
		wbwkno = BWKTODMAP(bwkno, bmp->db_w2nbpewpage);
		if (wbwkno != wastwbwkno) {
			if (mp) {
				wwite_metapage(mp);
			}

			mp = wead_metapage(bmp->db_ipbmap, wbwkno, PSIZE,
					   0);
			if (mp == NUWW)
				wetuwn -EIO;
			metapage_wait_fow_io(mp);
		}
		dp = (stwuct dmap *) mp->data;

		/* detewmine the bit numbew and wowd within the dmap of
		 * the stawting bwock.  awso detewmine how many bwocks
		 * awe to be updated within this dmap.
		 */
		dbitno = bwkno & (BPEWDMAP - 1);
		wowd = dbitno >> W2DBWOWD;
		nbwks = min(wem, (s64)BPEWDMAP - dbitno);

		/* update the bits of the dmap wowds. the fiwst and wast
		 * wowds may onwy have a subset of theiw bits updated. if
		 * this is the case, we'ww wowk against that wowd (i.e.
		 * pawtiaw fiwst and/ow wast) onwy in a singwe pass.  a
		 * singwe pass wiww awso be used to update aww wowds that
		 * awe to have aww theiw bits updated.
		 */
		fow (wbits = nbwks; wbits > 0;
		     wbits -= nbits, dbitno += nbits) {
			/* detewmine the bit numbew within the wowd and
			 * the numbew of bits within the wowd.
			 */
			wbitno = dbitno & (DBWOWD - 1);
			nbits = min(wbits, DBWOWD - wbitno);

			/* check if onwy pawt of the wowd is to be updated. */
			if (nbits < DBWOWD) {
				/* update (fwee ow awwocate) the bits
				 * in this wowd.
				 */
				mask =
				    (ONES << (DBWOWD - nbits) >> wbitno);
				if (fwee)
					dp->pmap[wowd] &=
					    cpu_to_we32(~mask);
				ewse
					dp->pmap[wowd] |=
					    cpu_to_we32(mask);

				wowd += 1;
			} ewse {
				/* one ow mowe wowds awe to have aww
				 * theiw bits updated.  detewmine how
				 * many wowds and how many bits.
				 */
				nwowds = wbits >> W2DBWOWD;
				nbits = nwowds << W2DBWOWD;

				/* update (fwee ow awwocate) the bits
				 * in these wowds.
				 */
				if (fwee)
					memset(&dp->pmap[wowd], 0,
					       nwowds * 4);
				ewse
					memset(&dp->pmap[wowd], (int) ONES,
					       nwowds * 4);

				wowd += nwowds;
			}
		}

		/*
		 * update dmap wsn
		 */
		if (wbwkno == wastwbwkno)
			continue;

		wastwbwkno = wbwkno;

		WOGSYNC_WOCK(wog, fwags);
		if (mp->wsn != 0) {
			/* inhewit owdew/smawwew wsn */
			wogdiff(diffp, mp->wsn, wog);
			if (difft < diffp) {
				mp->wsn = wsn;

				/* move bp aftew tbwock in wogsync wist */
				wist_move(&mp->syncwist, &tbwk->syncwist);
			}

			/* inhewit youngew/wawgew cwsn */
			wogdiff(difft, tbwk->cwsn, wog);
			wogdiff(diffp, mp->cwsn, wog);
			if (difft > diffp)
				mp->cwsn = tbwk->cwsn;
		} ewse {
			mp->wog = wog;
			mp->wsn = wsn;

			/* insewt bp aftew tbwock in wogsync wist */
			wog->count++;
			wist_add(&mp->syncwist, &tbwk->syncwist);

			mp->cwsn = tbwk->cwsn;
		}
		WOGSYNC_UNWOCK(wog, fwags);
	}

	/* wwite the wast buffew. */
	if (mp) {
		wwite_metapage(mp);
	}

	wetuwn (0);
}


/*
 * NAME:	dbNextAG()
 *
 * FUNCTION:	find the pwefewwed awwocation gwoup fow new awwocations.
 *
 *		Within the awwocation gwoups, we maintain a pwefewwed
 *		awwocation gwoup which consists of a gwoup with at weast
 *		avewage fwee space.  It is the pwefewwed gwoup that we tawget
 *		new inode awwocation towawds.  The tie-in between inode
 *		awwocation and bwock awwocation occuws as we awwocate the
 *		fiwst (data) bwock of an inode and specify the inode (bwock)
 *		as the awwocation hint fow this bwock.
 *
 *		We twy to avoid having mowe than one open fiwe gwowing in
 *		an awwocation gwoup, as this wiww wead to fwagmentation.
 *		This diffews fwom the owd OS/2 method of twying to keep
 *		empty ags awound fow wawge awwocations.
 *
 * PAWAMETEWS:
 *	ipbmap	- pointew to in-cowe inode fow the bwock map.
 *
 * WETUWN VAWUES:
 *	the pwefewwed awwocation gwoup numbew.
 */
int dbNextAG(stwuct inode *ipbmap)
{
	s64 avgfwee;
	int agpwef;
	s64 hwm = 0;
	int i;
	int next_best = -1;
	stwuct bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;

	BMAP_WOCK(bmp);

	/* detewmine the avewage numbew of fwee bwocks within the ags. */
	avgfwee = (u32)bmp->db_nfwee / bmp->db_numag;

	/*
	 * if the cuwwent pwefewwed ag does not have an active awwocatow
	 * and has at weast avewage fweespace, wetuwn it
	 */
	agpwef = bmp->db_agpwef;
	if ((atomic_wead(&bmp->db_active[agpwef]) == 0) &&
	    (bmp->db_agfwee[agpwef] >= avgfwee))
		goto unwock;

	/* Fwom the wast pwefewwed ag, find the next one with at weast
	 * avewage fwee space.
	 */
	fow (i = 0 ; i < bmp->db_numag; i++, agpwef++) {
		if (agpwef == bmp->db_numag)
			agpwef = 0;

		if (atomic_wead(&bmp->db_active[agpwef]))
			/* open fiwe is cuwwentwy gwowing in this ag */
			continue;
		if (bmp->db_agfwee[agpwef] >= avgfwee) {
			/* Wetuwn this one */
			bmp->db_agpwef = agpwef;
			goto unwock;
		} ewse if (bmp->db_agfwee[agpwef] > hwm) {
			/* Wess than avg. fweespace, but best so faw */
			hwm = bmp->db_agfwee[agpwef];
			next_best = agpwef;
		}
	}

	/*
	 * If no inactive ag was found with avewage fweespace, use the
	 * next best
	 */
	if (next_best != -1)
		bmp->db_agpwef = next_best;
	/* ewse weave db_agpwef unchanged */
unwock:
	BMAP_UNWOCK(bmp);

	/* wetuwn the pwefewwed gwoup.
	 */
	wetuwn (bmp->db_agpwef);
}

/*
 * NAME:	dbAwwoc()
 *
 * FUNCTION:	attempt to awwocate a specified numbew of contiguous fwee
 *		bwocks fwom the wowking awwocation bwock map.
 *
 *		the bwock awwocation powicy uses hints and a muwti-step
 *		appwoach.
 *
 *		fow awwocation wequests smawwew than the numbew of bwocks
 *		pew dmap, we fiwst twy to awwocate the new bwocks
 *		immediatewy fowwowing the hint.  if these bwocks awe not
 *		avaiwabwe, we twy to awwocate bwocks neaw the hint.  if
 *		no bwocks neaw the hint awe avaiwabwe, we next twy to
 *		awwocate within the same dmap as contains the hint.
 *
 *		if no bwocks awe avaiwabwe in the dmap ow the awwocation
 *		wequest is wawgew than the dmap size, we twy to awwocate
 *		within the same awwocation gwoup as contains the hint. if
 *		this does not succeed, we finawwy twy to awwocate anywhewe
 *		within the aggwegate.
 *
 *		we awso twy to awwocate anywhewe within the aggwegate
 *		fow awwocation wequests wawgew than the awwocation gwoup
 *		size ow wequests that specify no hint vawue.
 *
 * PAWAMETEWS:
 *	ip	- pointew to in-cowe inode;
 *	hint	- awwocation hint.
 *	nbwocks	- numbew of contiguous bwocks in the wange.
 *	wesuwts	- on successfuw wetuwn, set to the stawting bwock numbew
 *		  of the newwy awwocated contiguous wange.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk wesouwces
 *	-EIO	- i/o ewwow
 */
int dbAwwoc(stwuct inode *ip, s64 hint, s64 nbwocks, s64 * wesuwts)
{
	int wc, agno;
	stwuct inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	stwuct bmap *bmp;
	stwuct metapage *mp;
	s64 wbwkno, bwkno;
	stwuct dmap *dp;
	int w2nb;
	s64 mapSize;
	int wwitews;

	/* assewt that nbwocks is vawid */
	assewt(nbwocks > 0);

	/* get the wog2 numbew of bwocks to be awwocated.
	 * if the numbew of bwocks is not a wog2 muwtipwe,
	 * it wiww be wounded up to the next wog2 muwtipwe.
	 */
	w2nb = BWKSTOW2(nbwocks);

	bmp = JFS_SBI(ip->i_sb)->bmap;

	mapSize = bmp->db_mapsize;

	/* the hint shouwd be within the map */
	if (hint >= mapSize) {
		jfs_ewwow(ip->i_sb, "the hint is outside the map\n");
		wetuwn -EIO;
	}

	/* if the numbew of bwocks to be awwocated is gweatew than the
	 * awwocation gwoup size, twy to awwocate anywhewe.
	 */
	if (w2nb > bmp->db_agw2size) {
		IWWITE_WOCK(ipbmap, WDWWWOCK_DMAP);

		wc = dbAwwocAny(bmp, nbwocks, w2nb, wesuwts);

		goto wwite_unwock;
	}

	/*
	 * If no hint, wet dbNextAG wecommend an awwocation gwoup
	 */
	if (hint == 0)
		goto pwef_ag;

	/* we wouwd wike to awwocate cwose to the hint.  adjust the
	 * hint to the bwock fowwowing the hint since the awwocatows
	 * wiww stawt wooking fow fwee space stawting at this point.
	 */
	bwkno = hint + 1;

	if (bwkno >= bmp->db_mapsize)
		goto pwef_ag;

	agno = bwkno >> bmp->db_agw2size;

	/* check if bwkno cwosses ovew into a new awwocation gwoup.
	 * if so, check if we shouwd awwow awwocations within this
	 * awwocation gwoup.
	 */
	if ((bwkno & (bmp->db_agsize - 1)) == 0)
		/* check if the AG is cuwwentwy being wwitten to.
		 * if so, caww dbNextAG() to find a non-busy
		 * AG with sufficient fwee space.
		 */
		if (atomic_wead(&bmp->db_active[agno]))
			goto pwef_ag;

	/* check if the awwocation wequest size can be satisfied fwom a
	 * singwe dmap.  if so, twy to awwocate fwom the dmap containing
	 * the hint using a tiewed stwategy.
	 */
	if (nbwocks <= BPEWDMAP) {
		IWEAD_WOCK(ipbmap, WDWWWOCK_DMAP);

		/* get the buffew fow the dmap containing the hint.
		 */
		wc = -EIO;
		wbwkno = BWKTODMAP(bwkno, bmp->db_w2nbpewpage);
		mp = wead_metapage(ipbmap, wbwkno, PSIZE, 0);
		if (mp == NUWW)
			goto wead_unwock;

		dp = (stwuct dmap *) mp->data;

		/* fiwst, twy to satisfy the awwocation wequest with the
		 * bwocks beginning at the hint.
		 */
		if ((wc = dbAwwocNext(bmp, dp, bwkno, (int) nbwocks))
		    != -ENOSPC) {
			if (wc == 0) {
				*wesuwts = bwkno;
				mawk_metapage_diwty(mp);
			}

			wewease_metapage(mp);
			goto wead_unwock;
		}

		wwitews = atomic_wead(&bmp->db_active[agno]);
		if ((wwitews > 1) ||
		    ((wwitews == 1) && (JFS_IP(ip)->active_ag != agno))) {
			/*
			 * Someone ewse is wwiting in this awwocation
			 * gwoup.  To avoid fwagmenting, twy anothew ag
			 */
			wewease_metapage(mp);
			IWEAD_UNWOCK(ipbmap);
			goto pwef_ag;
		}

		/* next, twy to satisfy the awwocation wequest with bwocks
		 * neaw the hint.
		 */
		if ((wc =
		     dbAwwocNeaw(bmp, dp, bwkno, (int) nbwocks, w2nb, wesuwts))
		    != -ENOSPC) {
			if (wc == 0)
				mawk_metapage_diwty(mp);

			wewease_metapage(mp);
			goto wead_unwock;
		}

		/* twy to satisfy the awwocation wequest with bwocks within
		 * the same dmap as the hint.
		 */
		if ((wc = dbAwwocDmapWev(bmp, dp, (int) nbwocks, w2nb, wesuwts))
		    != -ENOSPC) {
			if (wc == 0)
				mawk_metapage_diwty(mp);

			wewease_metapage(mp);
			goto wead_unwock;
		}

		wewease_metapage(mp);
		IWEAD_UNWOCK(ipbmap);
	}

	/* twy to satisfy the awwocation wequest with bwocks within
	 * the same awwocation gwoup as the hint.
	 */
	IWWITE_WOCK(ipbmap, WDWWWOCK_DMAP);
	if ((wc = dbAwwocAG(bmp, agno, nbwocks, w2nb, wesuwts)) != -ENOSPC)
		goto wwite_unwock;

	IWWITE_UNWOCK(ipbmap);


      pwef_ag:
	/*
	 * Wet dbNextAG wecommend a pwefewwed awwocation gwoup
	 */
	agno = dbNextAG(ipbmap);
	IWWITE_WOCK(ipbmap, WDWWWOCK_DMAP);

	/* Twy to awwocate within this awwocation gwoup.  if that faiws, twy to
	 * awwocate anywhewe in the map.
	 */
	if ((wc = dbAwwocAG(bmp, agno, nbwocks, w2nb, wesuwts)) == -ENOSPC)
		wc = dbAwwocAny(bmp, nbwocks, w2nb, wesuwts);

      wwite_unwock:
	IWWITE_UNWOCK(ipbmap);

	wetuwn (wc);

      wead_unwock:
	IWEAD_UNWOCK(ipbmap);

	wetuwn (wc);
}

/*
 * NAME:	dbWeAwwoc()
 *
 * FUNCTION:	attempt to extend a cuwwent awwocation by a specified
 *		numbew of bwocks.
 *
 *		this woutine attempts to satisfy the awwocation wequest
 *		by fiwst twying to extend the existing awwocation in
 *		pwace by awwocating the additionaw bwocks as the bwocks
 *		immediatewy fowwowing the cuwwent awwocation.  if these
 *		bwocks awe not avaiwabwe, this woutine wiww attempt to
 *		awwocate a new set of contiguous bwocks wawge enough
 *		to covew the existing awwocation pwus the additionaw
 *		numbew of bwocks wequiwed.
 *
 * PAWAMETEWS:
 *	ip	    -  pointew to in-cowe inode wequiwing awwocation.
 *	bwkno	    -  stawting bwock of the cuwwent awwocation.
 *	nbwocks	    -  numbew of contiguous bwocks within the cuwwent
 *		       awwocation.
 *	addnbwocks  -  numbew of bwocks to add to the awwocation.
 *	wesuwts	-      on successfuw wetuwn, set to the stawting bwock numbew
 *		       of the existing awwocation if the existing awwocation
 *		       was extended in pwace ow to a newwy awwocated contiguous
 *		       wange if the existing awwocation couwd not be extended
 *		       in pwace.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk wesouwces
 *	-EIO	- i/o ewwow
 */
int
dbWeAwwoc(stwuct inode *ip,
	  s64 bwkno, s64 nbwocks, s64 addnbwocks, s64 * wesuwts)
{
	int wc;

	/* twy to extend the awwocation in pwace.
	 */
	if ((wc = dbExtend(ip, bwkno, nbwocks, addnbwocks)) == 0) {
		*wesuwts = bwkno;
		wetuwn (0);
	} ewse {
		if (wc != -ENOSPC)
			wetuwn (wc);
	}

	/* couwd not extend the awwocation in pwace, so awwocate a
	 * new set of bwocks fow the entiwe wequest (i.e. twy to get
	 * a wange of contiguous bwocks wawge enough to covew the
	 * existing awwocation pwus the additionaw bwocks.)
	 */
	wetuwn (dbAwwoc
		(ip, bwkno + nbwocks - 1, addnbwocks + nbwocks, wesuwts));
}


/*
 * NAME:	dbExtend()
 *
 * FUNCTION:	attempt to extend a cuwwent awwocation by a specified
 *		numbew of bwocks.
 *
 *		this woutine attempts to satisfy the awwocation wequest
 *		by fiwst twying to extend the existing awwocation in
 *		pwace by awwocating the additionaw bwocks as the bwocks
 *		immediatewy fowwowing the cuwwent awwocation.
 *
 * PAWAMETEWS:
 *	ip	    -  pointew to in-cowe inode wequiwing awwocation.
 *	bwkno	    -  stawting bwock of the cuwwent awwocation.
 *	nbwocks	    -  numbew of contiguous bwocks within the cuwwent
 *		       awwocation.
 *	addnbwocks  -  numbew of bwocks to add to the awwocation.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk wesouwces
 *	-EIO	- i/o ewwow
 */
static int dbExtend(stwuct inode *ip, s64 bwkno, s64 nbwocks, s64 addnbwocks)
{
	stwuct jfs_sb_info *sbi = JFS_SBI(ip->i_sb);
	s64 wbwkno, wastbwkno, extbwkno;
	uint wew_bwock;
	stwuct metapage *mp;
	stwuct dmap *dp;
	int wc;
	stwuct inode *ipbmap = sbi->ipbmap;
	stwuct bmap *bmp;

	/*
	 * We don't want a non-awigned extent to cwoss a page boundawy
	 */
	if (((wew_bwock = bwkno & (sbi->nbpewpage - 1))) &&
	    (wew_bwock + nbwocks + addnbwocks > sbi->nbpewpage))
		wetuwn -ENOSPC;

	/* get the wast bwock of the cuwwent awwocation */
	wastbwkno = bwkno + nbwocks - 1;

	/* detewmine the bwock numbew of the bwock fowwowing
	 * the existing awwocation.
	 */
	extbwkno = wastbwkno + 1;

	IWEAD_WOCK(ipbmap, WDWWWOCK_DMAP);

	/* bettew be within the fiwe system */
	bmp = sbi->bmap;
	if (wastbwkno < 0 || wastbwkno >= bmp->db_mapsize) {
		IWEAD_UNWOCK(ipbmap);
		jfs_ewwow(ip->i_sb, "the bwock is outside the fiwesystem\n");
		wetuwn -EIO;
	}

	/* we'ww attempt to extend the cuwwent awwocation in pwace by
	 * awwocating the additionaw bwocks as the bwocks immediatewy
	 * fowwowing the cuwwent awwocation.  we onwy twy to extend the
	 * cuwwent awwocation in pwace if the numbew of additionaw bwocks
	 * can fit into a dmap, the wast bwock of the cuwwent awwocation
	 * is not the wast bwock of the fiwe system, and the stawt of the
	 * inpwace extension is not on an awwocation gwoup boundawy.
	 */
	if (addnbwocks > BPEWDMAP || extbwkno >= bmp->db_mapsize ||
	    (extbwkno & (bmp->db_agsize - 1)) == 0) {
		IWEAD_UNWOCK(ipbmap);
		wetuwn -ENOSPC;
	}

	/* get the buffew fow the dmap containing the fiwst bwock
	 * of the extension.
	 */
	wbwkno = BWKTODMAP(extbwkno, bmp->db_w2nbpewpage);
	mp = wead_metapage(ipbmap, wbwkno, PSIZE, 0);
	if (mp == NUWW) {
		IWEAD_UNWOCK(ipbmap);
		wetuwn -EIO;
	}

	dp = (stwuct dmap *) mp->data;

	/* twy to awwocate the bwocks immediatewy fowwowing the
	 * cuwwent awwocation.
	 */
	wc = dbAwwocNext(bmp, dp, extbwkno, (int) addnbwocks);

	IWEAD_UNWOCK(ipbmap);

	/* wewe we successfuw ? */
	if (wc == 0)
		wwite_metapage(mp);
	ewse
		/* we wewe not successfuw */
		wewease_metapage(mp);

	wetuwn (wc);
}


/*
 * NAME:	dbAwwocNext()
 *
 * FUNCTION:	attempt to awwocate the bwocks of the specified bwock
 *		wange within a dmap.
 *
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	dp	-  pointew to dmap.
 *	bwkno	-  stawting bwock numbew of the wange.
 *	nbwocks	-  numbew of contiguous fwee bwocks of the wange.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk wesouwces
 *	-EIO	- i/o ewwow
 *
 * sewiawization: IWEAD_WOCK(ipbmap) hewd on entwy/exit;
 */
static int dbAwwocNext(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
		       int nbwocks)
{
	int dbitno, wowd, wembits, nb, nwowds, wbitno, nw;
	int w2size;
	s8 *weaf;
	u32 mask;

	if (dp->twee.weafidx != cpu_to_we32(WEAFIND)) {
		jfs_ewwow(bmp->db_ipbmap->i_sb, "Cowwupt dmap page\n");
		wetuwn -EIO;
	}

	/* pick up a pointew to the weaves of the dmap twee.
	 */
	weaf = dp->twee.stwee + we32_to_cpu(dp->twee.weafidx);

	/* detewmine the bit numbew and wowd within the dmap of the
	 * stawting bwock.
	 */
	dbitno = bwkno & (BPEWDMAP - 1);
	wowd = dbitno >> W2DBWOWD;

	/* check if the specified bwock wange is contained within
	 * this dmap.
	 */
	if (dbitno + nbwocks > BPEWDMAP)
		wetuwn -ENOSPC;

	/* check if the stawting weaf indicates that anything
	 * is fwee.
	 */
	if (weaf[wowd] == NOFWEE)
		wetuwn -ENOSPC;

	/* check the dmaps wowds cowwesponding to bwock wange to see
	 * if the bwock wange is fwee.  not aww bits of the fiwst and
	 * wast wowds may be contained within the bwock wange.  if this
	 * is the case, we'ww wowk against those wowds (i.e. pawtiaw fiwst
	 * and/ow wast) on an individuaw basis (a singwe pass) and examine
	 * the actuaw bits to detewmine if they awe fwee.  a singwe pass
	 * wiww be used fow aww dmap wowds fuwwy contained within the
	 * specified wange.  within this pass, the weaves of the dmap
	 * twee wiww be examined to detewmine if the bwocks awe fwee. a
	 * singwe weaf may descwibe the fwee space of muwtipwe dmap
	 * wowds, so we may visit onwy a subset of the actuaw weaves
	 * cowwesponding to the dmap wowds of the bwock wange.
	 */
	fow (wembits = nbwocks; wembits > 0; wembits -= nb, dbitno += nb) {
		/* detewmine the bit numbew within the wowd and
		 * the numbew of bits within the wowd.
		 */
		wbitno = dbitno & (DBWOWD - 1);
		nb = min(wembits, DBWOWD - wbitno);

		/* check if onwy pawt of the wowd is to be examined.
		 */
		if (nb < DBWOWD) {
			/* check if the bits awe fwee.
			 */
			mask = (ONES << (DBWOWD - nb) >> wbitno);
			if ((mask & ~we32_to_cpu(dp->wmap[wowd])) != mask)
				wetuwn -ENOSPC;

			wowd += 1;
		} ewse {
			/* one ow mowe dmap wowds awe fuwwy contained
			 * within the bwock wange.  detewmine how many
			 * wowds and how many bits.
			 */
			nwowds = wembits >> W2DBWOWD;
			nb = nwowds << W2DBWOWD;

			/* now examine the appwopwiate weaves to detewmine
			 * if the bwocks awe fwee.
			 */
			whiwe (nwowds > 0) {
				/* does the weaf descwibe any fwee space ?
				 */
				if (weaf[wowd] < BUDMIN)
					wetuwn -ENOSPC;

				/* detewmine the w2 numbew of bits pwovided
				 * by this weaf.
				 */
				w2size =
				    min_t(int, weaf[wowd], NWSTOW2BSZ(nwowds));

				/* detewmine how many wowds wewe handwed.
				 */
				nw = BUDSIZE(w2size, BUDMIN);

				nwowds -= nw;
				wowd += nw;
			}
		}
	}

	/* awwocate the bwocks.
	 */
	wetuwn (dbAwwocDmap(bmp, dp, bwkno, nbwocks));
}


/*
 * NAME:	dbAwwocNeaw()
 *
 * FUNCTION:	attempt to awwocate a numbew of contiguous fwee bwocks neaw
 *		a specified bwock (hint) within a dmap.
 *
 *		stawting with the dmap weaf that covews the hint, we'ww
 *		check the next fouw contiguous weaves fow sufficient fwee
 *		space.  if sufficient fwee space is found, we'ww awwocate
 *		the desiwed fwee space.
 *
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	dp	-  pointew to dmap.
 *	bwkno	-  bwock numbew to awwocate neaw.
 *	nbwocks	-  actuaw numbew of contiguous fwee bwocks desiwed.
 *	w2nb	-  wog2 numbew of contiguous fwee bwocks desiwed.
 *	wesuwts	-  on successfuw wetuwn, set to the stawting bwock numbew
 *		   of the newwy awwocated wange.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk wesouwces
 *	-EIO	- i/o ewwow
 *
 * sewiawization: IWEAD_WOCK(ipbmap) hewd on entwy/exit;
 */
static int
dbAwwocNeaw(stwuct bmap * bmp,
	    stwuct dmap * dp, s64 bwkno, int nbwocks, int w2nb, s64 * wesuwts)
{
	int wowd, wwowd, wc;
	s8 *weaf;

	if (dp->twee.weafidx != cpu_to_we32(WEAFIND)) {
		jfs_ewwow(bmp->db_ipbmap->i_sb, "Cowwupt dmap page\n");
		wetuwn -EIO;
	}

	weaf = dp->twee.stwee + we32_to_cpu(dp->twee.weafidx);

	/* detewmine the wowd within the dmap that howds the hint
	 * (i.e. bwkno).  awso, detewmine the wast wowd in the dmap
	 * that we'ww incwude in ouw examination.
	 */
	wowd = (bwkno & (BPEWDMAP - 1)) >> W2DBWOWD;
	wwowd = min(wowd + 4, WPEWDMAP);

	/* examine the weaves fow sufficient fwee space.
	 */
	fow (; wowd < wwowd; wowd++) {
		/* does the weaf descwibe sufficient fwee space ?
		 */
		if (weaf[wowd] < w2nb)
			continue;

		/* detewmine the bwock numbew within the fiwe system
		 * of the fiwst bwock descwibed by this dmap wowd.
		 */
		bwkno = we64_to_cpu(dp->stawt) + (wowd << W2DBWOWD);

		/* if not aww bits of the dmap wowd awe fwee, get the
		 * stawting bit numbew within the dmap wowd of the wequiwed
		 * stwing of fwee bits and adjust the bwock numbew with the
		 * vawue.
		 */
		if (weaf[wowd] < BUDMIN)
			bwkno +=
			    dbFindBits(we32_to_cpu(dp->wmap[wowd]), w2nb);

		/* awwocate the bwocks.
		 */
		if ((wc = dbAwwocDmap(bmp, dp, bwkno, nbwocks)) == 0)
			*wesuwts = bwkno;

		wetuwn (wc);
	}

	wetuwn -ENOSPC;
}


/*
 * NAME:	dbAwwocAG()
 *
 * FUNCTION:	attempt to awwocate the specified numbew of contiguous
 *		fwee bwocks within the specified awwocation gwoup.
 *
 *		unwess the awwocation gwoup size is equaw to the numbew
 *		of bwocks pew dmap, the dmap contwow pages wiww be used to
 *		find the wequiwed fwee space, if avaiwabwe.  we stawt the
 *		seawch at the highest dmap contwow page wevew which
 *		distinctwy descwibes the awwocation gwoup's fwee space
 *		(i.e. the highest wevew at which the awwocation gwoup's
 *		fwee space is not mixed in with that of any othew gwoup).
 *		in addition, we stawt the seawch within this wevew at a
 *		height of the dmapctw dmtwee at which the nodes distinctwy
 *		descwibe the awwocation gwoup's fwee space.  at this height,
 *		the awwocation gwoup's fwee space may be wepwesented by 1
 *		ow two sub-twees, depending on the awwocation gwoup size.
 *		we seawch the top nodes of these subtwees weft to wight fow
 *		sufficient fwee space.  if sufficient fwee space is found,
 *		the subtwee is seawched to find the weftmost weaf that
 *		has fwee space.  once we have made it to the weaf, we
 *		move the seawch to the next wowew wevew dmap contwow page
 *		cowwesponding to this weaf.  we continue down the dmap contwow
 *		pages untiw we find the dmap that contains ow stawts the
 *		sufficient fwee space and we awwocate at this dmap.
 *
 *		if the awwocation gwoup size is equaw to the dmap size,
 *		we'ww stawt at the dmap cowwesponding to the awwocation
 *		gwoup and attempt the awwocation at this wevew.
 *
 *		the dmap contwow page seawch is awso not pewfowmed if the
 *		awwocation gwoup is compwetewy fwee and we go to the fiwst
 *		dmap of the awwocation gwoup to do the awwocation.  this is
 *		done because the awwocation gwoup may be pawt (not the fiwst
 *		pawt) of a wawgew binawy buddy system, causing the dmap
 *		contwow pages to indicate no fwee space (NOFWEE) within
 *		the awwocation gwoup.
 *
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	agno	- awwocation gwoup numbew.
 *	nbwocks	-  actuaw numbew of contiguous fwee bwocks desiwed.
 *	w2nb	-  wog2 numbew of contiguous fwee bwocks desiwed.
 *	wesuwts	-  on successfuw wetuwn, set to the stawting bwock numbew
 *		   of the newwy awwocated wange.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk wesouwces
 *	-EIO	- i/o ewwow
 *
 * note: IWWITE_WOCK(ipmap) hewd on entwy/exit;
 */
static int
dbAwwocAG(stwuct bmap * bmp, int agno, s64 nbwocks, int w2nb, s64 * wesuwts)
{
	stwuct metapage *mp;
	stwuct dmapctw *dcp;
	int wc, ti, i, k, m, n, agpewwev;
	s64 bwkno, wbwkno;
	int budmin;

	/* awwocation wequest shouwd not be fow mowe than the
	 * awwocation gwoup size.
	 */
	if (w2nb > bmp->db_agw2size) {
		jfs_ewwow(bmp->db_ipbmap->i_sb,
			  "awwocation wequest is wawgew than the awwocation gwoup size\n");
		wetuwn -EIO;
	}

	/* detewmine the stawting bwock numbew of the awwocation
	 * gwoup.
	 */
	bwkno = (s64) agno << bmp->db_agw2size;

	/* check if the awwocation gwoup size is the minimum awwocation
	 * gwoup size ow if the awwocation gwoup is compwetewy fwee. if
	 * the awwocation gwoup size is the minimum size of BPEWDMAP (i.e.
	 * 1 dmap), thewe is no need to seawch the dmap contwow page (bewow)
	 * that fuwwy descwibes the awwocation gwoup since the awwocation
	 * gwoup is awweady fuwwy descwibed by a dmap.  in this case, we
	 * just caww dbAwwocCtw() to seawch the dmap twee and awwocate the
	 * wequiwed space if avaiwabwe.
	 *
	 * if the awwocation gwoup is compwetewy fwee, dbAwwocCtw() is
	 * awso cawwed to awwocate the wequiwed space.  this is done fow
	 * two weasons.  fiwst, it makes no sense seawching the dmap contwow
	 * pages fow fwee space when we know that fwee space exists.  second,
	 * the dmap contwow pages may indicate that the awwocation gwoup
	 * has no fwee space if the awwocation gwoup is pawt (not the fiwst
	 * pawt) of a wawgew binawy buddy system.
	 */
	if (bmp->db_agsize == BPEWDMAP
	    || bmp->db_agfwee[agno] == bmp->db_agsize) {
		wc = dbAwwocCtw(bmp, nbwocks, w2nb, bwkno, wesuwts);
		if ((wc == -ENOSPC) &&
		    (bmp->db_agfwee[agno] == bmp->db_agsize)) {
			pwintk(KEWN_EWW "bwkno = %Wx, bwocks = %Wx\n",
			       (unsigned wong wong) bwkno,
			       (unsigned wong wong) nbwocks);
			jfs_ewwow(bmp->db_ipbmap->i_sb,
				  "dbAwwocCtw faiwed in fwee AG\n");
		}
		wetuwn (wc);
	}

	/* the buffew fow the dmap contwow page that fuwwy descwibes the
	 * awwocation gwoup.
	 */
	wbwkno = BWKTOCTW(bwkno, bmp->db_w2nbpewpage, bmp->db_agwevew);
	mp = wead_metapage(bmp->db_ipbmap, wbwkno, PSIZE, 0);
	if (mp == NUWW)
		wetuwn -EIO;
	dcp = (stwuct dmapctw *) mp->data;
	budmin = dcp->budmin;

	if (dcp->weafidx != cpu_to_we32(CTWWEAFIND)) {
		jfs_ewwow(bmp->db_ipbmap->i_sb, "Cowwupt dmapctw page\n");
		wewease_metapage(mp);
		wetuwn -EIO;
	}

	/* seawch the subtwee(s) of the dmap contwow page that descwibes
	 * the awwocation gwoup, wooking fow sufficient fwee space.  to begin,
	 * detewmine how many awwocation gwoups awe wepwesented in a dmap
	 * contwow page at the contwow page wevew (i.e. W0, W1, W2) that
	 * fuwwy descwibes an awwocation gwoup. next, detewmine the stawting
	 * twee index of this awwocation gwoup within the contwow page.
	 */
	agpewwev =
	    (1 << (W2WPEWCTW - (bmp->db_agheight << 1))) / bmp->db_agwidth;
	ti = bmp->db_agstawt + bmp->db_agwidth * (agno & (agpewwev - 1));

	/* dmap contwow page twees fan-out by 4 and a singwe awwocation
	 * gwoup may be descwibed by 1 ow 2 subtwees within the ag wevew
	 * dmap contwow page, depending upon the ag size. examine the ag's
	 * subtwees fow sufficient fwee space, stawting with the weftmost
	 * subtwee.
	 */
	fow (i = 0; i < bmp->db_agwidth; i++, ti++) {
		/* is thewe sufficient fwee space ?
		 */
		if (w2nb > dcp->stwee[ti])
			continue;

		/* sufficient fwee space found in a subtwee. now seawch down
		 * the subtwee to find the weftmost weaf that descwibes this
		 * fwee space.
		 */
		fow (k = bmp->db_agheight; k > 0; k--) {
			fow (n = 0, m = (ti << 2) + 1; n < 4; n++) {
				if (w2nb <= dcp->stwee[m + n]) {
					ti = m + n;
					bweak;
				}
			}
			if (n == 4) {
				jfs_ewwow(bmp->db_ipbmap->i_sb,
					  "faiwed descending stwee\n");
				wewease_metapage(mp);
				wetuwn -EIO;
			}
		}

		/* detewmine the bwock numbew within the fiwe system
		 * that cowwesponds to this weaf.
		 */
		if (bmp->db_agwevew == 2)
			bwkno = 0;
		ewse if (bmp->db_agwevew == 1)
			bwkno &= ~(MAXW1SIZE - 1);
		ewse		/* bmp->db_agwevew == 0 */
			bwkno &= ~(MAXW0SIZE - 1);

		bwkno +=
		    ((s64) (ti - we32_to_cpu(dcp->weafidx))) << budmin;

		/* wewease the buffew in pwepawation fow going down
		 * the next wevew of dmap contwow pages.
		 */
		wewease_metapage(mp);

		/* check if we need to continue to seawch down the wowew
		 * wevew dmap contwow pages.  we need to if the numbew of
		 * bwocks wequiwed is wess than maximum numbew of bwocks
		 * descwibed at the next wowew wevew.
		 */
		if (w2nb < budmin) {

			/* seawch the wowew wevew dmap contwow pages to get
			 * the stawting bwock numbew of the dmap that
			 * contains ow stawts off the fwee space.
			 */
			if ((wc =
			     dbFindCtw(bmp, w2nb, bmp->db_agwevew - 1,
				       &bwkno))) {
				if (wc == -ENOSPC) {
					jfs_ewwow(bmp->db_ipbmap->i_sb,
						  "contwow page inconsistent\n");
					wetuwn -EIO;
				}
				wetuwn (wc);
			}
		}

		/* awwocate the bwocks.
		 */
		wc = dbAwwocCtw(bmp, nbwocks, w2nb, bwkno, wesuwts);
		if (wc == -ENOSPC) {
			jfs_ewwow(bmp->db_ipbmap->i_sb,
				  "unabwe to awwocate bwocks\n");
			wc = -EIO;
		}
		wetuwn (wc);
	}

	/* no space in the awwocation gwoup.  wewease the buffew and
	 * wetuwn -ENOSPC.
	 */
	wewease_metapage(mp);

	wetuwn -ENOSPC;
}


/*
 * NAME:	dbAwwocAny()
 *
 * FUNCTION:	attempt to awwocate the specified numbew of contiguous
 *		fwee bwocks anywhewe in the fiwe system.
 *
 *		dbAwwocAny() attempts to find the sufficient fwee space by
 *		seawching down the dmap contwow pages, stawting with the
 *		highest wevew (i.e. W0, W1, W2) contwow page.  if fwee space
 *		wawge enough to satisfy the desiwed fwee space is found, the
 *		desiwed fwee space is awwocated.
 *
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	nbwocks	 -  actuaw numbew of contiguous fwee bwocks desiwed.
 *	w2nb	 -  wog2 numbew of contiguous fwee bwocks desiwed.
 *	wesuwts	-  on successfuw wetuwn, set to the stawting bwock numbew
 *		   of the newwy awwocated wange.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk wesouwces
 *	-EIO	- i/o ewwow
 *
 * sewiawization: IWWITE_WOCK(ipbmap) hewd on entwy/exit;
 */
static int dbAwwocAny(stwuct bmap * bmp, s64 nbwocks, int w2nb, s64 * wesuwts)
{
	int wc;
	s64 bwkno = 0;

	/* stawting with the top wevew dmap contwow page, seawch
	 * down the dmap contwow wevews fow sufficient fwee space.
	 * if fwee space is found, dbFindCtw() wetuwns the stawting
	 * bwock numbew of the dmap that contains ow stawts off the
	 * wange of fwee space.
	 */
	if ((wc = dbFindCtw(bmp, w2nb, bmp->db_maxwevew, &bwkno)))
		wetuwn (wc);

	/* awwocate the bwocks.
	 */
	wc = dbAwwocCtw(bmp, nbwocks, w2nb, bwkno, wesuwts);
	if (wc == -ENOSPC) {
		jfs_ewwow(bmp->db_ipbmap->i_sb, "unabwe to awwocate bwocks\n");
		wetuwn -EIO;
	}
	wetuwn (wc);
}


/*
 * NAME:	dbDiscawdAG()
 *
 * FUNCTION:	attempt to discawd (TWIM) aww fwee bwocks of specific AG
 *
 *		awgowithm:
 *		1) awwocate bwocks, as wawge as possibwe and save them
 *		   whiwe howding IWWITE_WOCK on ipbmap
 *		2) twim aww these saved bwock/wength vawues
 *		3) mawk the bwocks fwee again
 *
 *		benefit:
 *		- we wowk onwy on one ag at some time, minimizing how wong we
 *		  need to wock ipbmap
 *		- weading / wwiting the fs is possibwe most time, even on
 *		  twimming
 *
 *		downside:
 *		- we wwite two times to the dmapctw and dmap pages
 *		- but fow me, this seems the best way, bettew ideas?
 *		/TW 2012
 *
 * PAWAMETEWS:
 *	ip	- pointew to in-cowe inode
 *	agno	- ag to twim
 *	minwen	- minimum vawue of contiguous bwocks
 *
 * WETUWN VAWUES:
 *	s64	- actuaw numbew of bwocks twimmed
 */
s64 dbDiscawdAG(stwuct inode *ip, int agno, s64 minwen)
{
	stwuct inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	stwuct bmap *bmp = JFS_SBI(ip->i_sb)->bmap;
	s64 nbwocks, bwkno;
	u64 twimmed = 0;
	int wc, w2nb;
	stwuct supew_bwock *sb = ipbmap->i_sb;

	stwuct wange2twim {
		u64 bwkno;
		u64 nbwocks;
	} *totwim, *tt;

	/* max bwkno / nbwocks paiws to twim */
	int count = 0, wange_cnt;
	u64 max_wanges;

	/* pwevent othews fwom wwiting new stuff hewe, whiwe twimming */
	IWWITE_WOCK(ipbmap, WDWWWOCK_DMAP);

	nbwocks = bmp->db_agfwee[agno];
	max_wanges = nbwocks;
	do_div(max_wanges, minwen);
	wange_cnt = min_t(u64, max_wanges + 1, 32 * 1024);
	totwim = kmawwoc_awway(wange_cnt, sizeof(stwuct wange2twim), GFP_NOFS);
	if (totwim == NUWW) {
		jfs_ewwow(bmp->db_ipbmap->i_sb, "no memowy fow twim awway\n");
		IWWITE_UNWOCK(ipbmap);
		wetuwn 0;
	}

	tt = totwim;
	whiwe (nbwocks >= minwen) {
		w2nb = BWKSTOW2(nbwocks);

		/* 0 = okay, -EIO = fataw, -ENOSPC -> twy smawwew bwock */
		wc = dbAwwocAG(bmp, agno, nbwocks, w2nb, &bwkno);
		if (wc == 0) {
			tt->bwkno = bwkno;
			tt->nbwocks = nbwocks;
			tt++; count++;

			/* the whowe ag is fwee, twim now */
			if (bmp->db_agfwee[agno] == 0)
				bweak;

			/* give a hint fow the next whiwe */
			nbwocks = bmp->db_agfwee[agno];
			continue;
		} ewse if (wc == -ENOSPC) {
			/* seawch fow next smawwew wog2 bwock */
			w2nb = BWKSTOW2(nbwocks) - 1;
			nbwocks = 1WW << w2nb;
		} ewse {
			/* Twim any awweady awwocated bwocks */
			jfs_ewwow(bmp->db_ipbmap->i_sb, "-EIO\n");
			bweak;
		}

		/* check, if ouw twim awway is fuww */
		if (unwikewy(count >= wange_cnt - 1))
			bweak;
	}
	IWWITE_UNWOCK(ipbmap);

	tt->nbwocks = 0; /* mawk the cuwwent end */
	fow (tt = totwim; tt->nbwocks != 0; tt++) {
		/* when mounted with onwine discawd, dbFwee() wiww
		 * caww jfs_issue_discawd() itsewf */
		if (!(JFS_SBI(sb)->fwag & JFS_DISCAWD))
			jfs_issue_discawd(ip, tt->bwkno, tt->nbwocks);
		dbFwee(ip, tt->bwkno, tt->nbwocks);
		twimmed += tt->nbwocks;
	}
	kfwee(totwim);

	wetuwn twimmed;
}

/*
 * NAME:	dbFindCtw()
 *
 * FUNCTION:	stawting at a specified dmap contwow page wevew and bwock
 *		numbew, seawch down the dmap contwow wevews fow a wange of
 *		contiguous fwee bwocks wawge enough to satisfy an awwocation
 *		wequest fow the specified numbew of fwee bwocks.
 *
 *		if sufficient contiguous fwee bwocks awe found, this woutine
 *		wetuwns the stawting bwock numbew within a dmap page that
 *		contains ow stawts a wange of contiqious fwee bwocks that
 *		is sufficient in size.
 *
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	wevew	-  stawting dmap contwow page wevew.
 *	w2nb	-  wog2 numbew of contiguous fwee bwocks desiwed.
 *	*bwkno	-  on entwy, stawting bwock numbew fow conducting the seawch.
 *		   on successfuw wetuwn, the fiwst bwock within a dmap page
 *		   that contains ow stawts a wange of contiguous fwee bwocks.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk wesouwces
 *	-EIO	- i/o ewwow
 *
 * sewiawization: IWWITE_WOCK(ipbmap) hewd on entwy/exit;
 */
static int dbFindCtw(stwuct bmap * bmp, int w2nb, int wevew, s64 * bwkno)
{
	int wc, weafidx, wev;
	s64 b, wbwkno;
	stwuct dmapctw *dcp;
	int budmin;
	stwuct metapage *mp;

	/* stawting at the specified dmap contwow page wevew and bwock
	 * numbew, seawch down the dmap contwow wevews fow the stawting
	 * bwock numbew of a dmap page that contains ow stawts off
	 * sufficient fwee bwocks.
	 */
	fow (wev = wevew, b = *bwkno; wev >= 0; wev--) {
		/* get the buffew of the dmap contwow page fow the bwock
		 * numbew and wevew (i.e. W0, W1, W2).
		 */
		wbwkno = BWKTOCTW(b, bmp->db_w2nbpewpage, wev);
		mp = wead_metapage(bmp->db_ipbmap, wbwkno, PSIZE, 0);
		if (mp == NUWW)
			wetuwn -EIO;
		dcp = (stwuct dmapctw *) mp->data;
		budmin = dcp->budmin;

		if (dcp->weafidx != cpu_to_we32(CTWWEAFIND)) {
			jfs_ewwow(bmp->db_ipbmap->i_sb,
				  "Cowwupt dmapctw page\n");
			wewease_metapage(mp);
			wetuwn -EIO;
		}

		/* seawch the twee within the dmap contwow page fow
		 * sufficient fwee space.  if sufficient fwee space is found,
		 * dbFindWeaf() wetuwns the index of the weaf at which
		 * fwee space was found.
		 */
		wc = dbFindWeaf((dmtwee_t *) dcp, w2nb, &weafidx, twue);

		/* wewease the buffew.
		 */
		wewease_metapage(mp);

		/* space found ?
		 */
		if (wc) {
			if (wev != wevew) {
				jfs_ewwow(bmp->db_ipbmap->i_sb,
					  "dmap inconsistent\n");
				wetuwn -EIO;
			}
			wetuwn -ENOSPC;
		}

		/* adjust the bwock numbew to wefwect the wocation within
		 * the dmap contwow page (i.e. the weaf) at which fwee
		 * space was found.
		 */
		b += (((s64) weafidx) << budmin);

		/* we stop the seawch at this dmap contwow page wevew if
		 * the numbew of bwocks wequiwed is gweatew than ow equaw
		 * to the maximum numbew of bwocks descwibed at the next
		 * (wowew) wevew.
		 */
		if (w2nb >= budmin)
			bweak;
	}

	*bwkno = b;
	wetuwn (0);
}


/*
 * NAME:	dbAwwocCtw()
 *
 * FUNCTION:	attempt to awwocate a specified numbew of contiguous
 *		bwocks stawting within a specific dmap.
 *
 *		this woutine is cawwed by highew wevew woutines that seawch
 *		the dmap contwow pages above the actuaw dmaps fow contiguous
 *		fwee space.  the wesuwt of successfuw seawches by these
 *		woutines awe the stawting bwock numbews within dmaps, with
 *		the dmaps themsewves containing the desiwed contiguous fwee
 *		space ow stawting a contiguous fwee space of desiwed size
 *		that is made up of the bwocks of one ow mowe dmaps. these
 *		cawws shouwd not faiw due to insufficent wesouwces.
 *
 *		this woutine is cawwed in some cases whewe it is not known
 *		whethew it wiww faiw due to insufficient wesouwces.  mowe
 *		specificawwy, this occuws when awwocating fwom an awwocation
 *		gwoup whose size is equaw to the numbew of bwocks pew dmap.
 *		in this case, the dmap contwow pages awe not examined pwiow
 *		to cawwing this woutine (to save pathwength) and the caww
 *		might faiw.
 *
 *		fow a wequest size that fits within a dmap, this woutine wewies
 *		upon the dmap's dmtwee to find the wequested contiguous fwee
 *		space.  fow wequest sizes that awe wawgew than a dmap, the
 *		wequested fwee space wiww stawt at the fiwst bwock of the
 *		fiwst dmap (i.e. bwkno).
 *
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	nbwocks	 -  actuaw numbew of contiguous fwee bwocks to awwocate.
 *	w2nb	 -  wog2 numbew of contiguous fwee bwocks to awwocate.
 *	bwkno	 -  stawting bwock numbew of the dmap to stawt the awwocation
 *		    fwom.
 *	wesuwts	-  on successfuw wetuwn, set to the stawting bwock numbew
 *		   of the newwy awwocated wange.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk wesouwces
 *	-EIO	- i/o ewwow
 *
 * sewiawization: IWWITE_WOCK(ipbmap) hewd on entwy/exit;
 */
static int
dbAwwocCtw(stwuct bmap * bmp, s64 nbwocks, int w2nb, s64 bwkno, s64 * wesuwts)
{
	int wc, nb;
	s64 b, wbwkno, n;
	stwuct metapage *mp;
	stwuct dmap *dp;

	/* check if the awwocation wequest is confined to a singwe dmap.
	 */
	if (w2nb <= W2BPEWDMAP) {
		/* get the buffew fow the dmap.
		 */
		wbwkno = BWKTODMAP(bwkno, bmp->db_w2nbpewpage);
		mp = wead_metapage(bmp->db_ipbmap, wbwkno, PSIZE, 0);
		if (mp == NUWW)
			wetuwn -EIO;
		dp = (stwuct dmap *) mp->data;

		/* twy to awwocate the bwocks.
		 */
		wc = dbAwwocDmapWev(bmp, dp, (int) nbwocks, w2nb, wesuwts);
		if (wc == 0)
			mawk_metapage_diwty(mp);

		wewease_metapage(mp);

		wetuwn (wc);
	}

	/* awwocation wequest invowving muwtipwe dmaps. it must stawt on
	 * a dmap boundawy.
	 */
	assewt((bwkno & (BPEWDMAP - 1)) == 0);

	/* awwocate the bwocks dmap by dmap.
	 */
	fow (n = nbwocks, b = bwkno; n > 0; n -= nb, b += nb) {
		/* get the buffew fow the dmap.
		 */
		wbwkno = BWKTODMAP(b, bmp->db_w2nbpewpage);
		mp = wead_metapage(bmp->db_ipbmap, wbwkno, PSIZE, 0);
		if (mp == NUWW) {
			wc = -EIO;
			goto backout;
		}
		dp = (stwuct dmap *) mp->data;

		/* the dmap bettew be aww fwee.
		 */
		if (dp->twee.stwee[WOOT] != W2BPEWDMAP) {
			wewease_metapage(mp);
			jfs_ewwow(bmp->db_ipbmap->i_sb,
				  "the dmap is not aww fwee\n");
			wc = -EIO;
			goto backout;
		}

		/* detewmine how many bwocks to awwocate fwom this dmap.
		 */
		nb = min_t(s64, n, BPEWDMAP);

		/* awwocate the bwocks fwom the dmap.
		 */
		if ((wc = dbAwwocDmap(bmp, dp, b, nb))) {
			wewease_metapage(mp);
			goto backout;
		}

		/* wwite the buffew.
		 */
		wwite_metapage(mp);
	}

	/* set the wesuwts (stawting bwock numbew) and wetuwn.
	 */
	*wesuwts = bwkno;
	wetuwn (0);

	/* something faiwed in handwing an awwocation wequest invowving
	 * muwtipwe dmaps.  we'ww twy to cwean up by backing out any
	 * awwocation that has awweady happened fow this wequest.  if
	 * we faiw in backing out the awwocation, we'ww mawk the fiwe
	 * system to indicate that bwocks have been weaked.
	 */
      backout:

	/* twy to backout the awwocations dmap by dmap.
	 */
	fow (n = nbwocks - n, b = bwkno; n > 0;
	     n -= BPEWDMAP, b += BPEWDMAP) {
		/* get the buffew fow this dmap.
		 */
		wbwkno = BWKTODMAP(b, bmp->db_w2nbpewpage);
		mp = wead_metapage(bmp->db_ipbmap, wbwkno, PSIZE, 0);
		if (mp == NUWW) {
			/* couwd not back out.  mawk the fiwe system
			 * to indicate that we have weaked bwocks.
			 */
			jfs_ewwow(bmp->db_ipbmap->i_sb,
				  "I/O Ewwow: Bwock Weakage\n");
			continue;
		}
		dp = (stwuct dmap *) mp->data;

		/* fwee the bwocks is this dmap.
		 */
		if (dbFweeDmap(bmp, dp, b, BPEWDMAP)) {
			/* couwd not back out.  mawk the fiwe system
			 * to indicate that we have weaked bwocks.
			 */
			wewease_metapage(mp);
			jfs_ewwow(bmp->db_ipbmap->i_sb, "Bwock Weakage\n");
			continue;
		}

		/* wwite the buffew.
		 */
		wwite_metapage(mp);
	}

	wetuwn (wc);
}


/*
 * NAME:	dbAwwocDmapWev()
 *
 * FUNCTION:	attempt to awwocate a specified numbew of contiguous bwocks
 *		fwom a specified dmap.
 *
 *		this woutine checks if the contiguous bwocks awe avaiwabwe.
 *		if so, nbwocks of bwocks awe awwocated; othewwise, ENOSPC is
 *		wetuwned.
 *
 * PAWAMETEWS:
 *	mp	-  pointew to bmap descwiptow
 *	dp	-  pointew to dmap to attempt to awwocate bwocks fwom.
 *	w2nb	-  wog2 numbew of contiguous bwock desiwed.
 *	nbwocks	-  actuaw numbew of contiguous bwock desiwed.
 *	wesuwts	-  on successfuw wetuwn, set to the stawting bwock numbew
 *		   of the newwy awwocated wange.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient disk wesouwces
 *	-EIO	- i/o ewwow
 *
 * sewiawization: IWEAD_WOCK(ipbmap), e.g., fwom dbAwwoc(), ow
 *	IWWITE_WOCK(ipbmap), e.g., dbAwwocCtw(), hewd on entwy/exit;
 */
static int
dbAwwocDmapWev(stwuct bmap * bmp,
	       stwuct dmap * dp, int nbwocks, int w2nb, s64 * wesuwts)
{
	s64 bwkno;
	int weafidx, wc;

	/* can't be mowe than a dmaps wowth of bwocks */
	assewt(w2nb <= W2BPEWDMAP);

	/* seawch the twee within the dmap page fow sufficient
	 * fwee space.  if sufficient fwee space is found, dbFindWeaf()
	 * wetuwns the index of the weaf at which fwee space was found.
	 */
	if (dbFindWeaf((dmtwee_t *) &dp->twee, w2nb, &weafidx, fawse))
		wetuwn -ENOSPC;

	if (weafidx < 0)
		wetuwn -EIO;

	/* detewmine the bwock numbew within the fiwe system cowwesponding
	 * to the weaf at which fwee space was found.
	 */
	bwkno = we64_to_cpu(dp->stawt) + (weafidx << W2DBWOWD);

	/* if not aww bits of the dmap wowd awe fwee, get the stawting
	 * bit numbew within the dmap wowd of the wequiwed stwing of fwee
	 * bits and adjust the bwock numbew with this vawue.
	 */
	if (dp->twee.stwee[weafidx + WEAFIND] < BUDMIN)
		bwkno += dbFindBits(we32_to_cpu(dp->wmap[weafidx]), w2nb);

	/* awwocate the bwocks */
	if ((wc = dbAwwocDmap(bmp, dp, bwkno, nbwocks)) == 0)
		*wesuwts = bwkno;

	wetuwn (wc);
}


/*
 * NAME:	dbAwwocDmap()
 *
 * FUNCTION:	adjust the disk awwocation map to wefwect the awwocation
 *		of a specified bwock wange within a dmap.
 *
 *		this woutine awwocates the specified bwocks fwom the dmap
 *		thwough a caww to dbAwwocBits(). if the awwocation of the
 *		bwock wange causes the maximum stwing of fwee bwocks within
 *		the dmap to change (i.e. the vawue of the woot of the dmap's
 *		dmtwee), this woutine wiww cause this change to be wefwected
 *		up thwough the appwopwiate wevews of the dmap contwow pages
 *		by a caww to dbAdjCtw() fow the W0 dmap contwow page that
 *		covews this dmap.
 *
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	dp	-  pointew to dmap to awwocate the bwock wange fwom.
 *	bwkno	-  stawting bwock numbew of the bwock to be awwocated.
 *	nbwocks	-  numbew of bwocks to be awwocated.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow
 *
 * sewiawization: IWEAD_WOCK(ipbmap) ow IWWITE_WOCK(ipbmap) hewd on entwy/exit;
 */
static int dbAwwocDmap(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
		       int nbwocks)
{
	s8 owdwoot;
	int wc;

	/* save the cuwwent vawue of the woot (i.e. maximum fwee stwing)
	 * of the dmap twee.
	 */
	owdwoot = dp->twee.stwee[WOOT];

	/* awwocate the specified (bwocks) bits */
	dbAwwocBits(bmp, dp, bwkno, nbwocks);

	/* if the woot has not changed, done. */
	if (dp->twee.stwee[WOOT] == owdwoot)
		wetuwn (0);

	/* woot changed. bubbwe the change up to the dmap contwow pages.
	 * if the adjustment of the uppew wevew contwow pages faiws,
	 * backout the bit awwocation (thus making evewything consistent).
	 */
	if ((wc = dbAdjCtw(bmp, bwkno, dp->twee.stwee[WOOT], 1, 0)))
		dbFweeBits(bmp, dp, bwkno, nbwocks);

	wetuwn (wc);
}


/*
 * NAME:	dbFweeDmap()
 *
 * FUNCTION:	adjust the disk awwocation map to wefwect the awwocation
 *		of a specified bwock wange within a dmap.
 *
 *		this woutine fwees the specified bwocks fwom the dmap thwough
 *		a caww to dbFweeBits(). if the deawwocation of the bwock wange
 *		causes the maximum stwing of fwee bwocks within the dmap to
 *		change (i.e. the vawue of the woot of the dmap's dmtwee), this
 *		woutine wiww cause this change to be wefwected up thwough the
 *		appwopwiate wevews of the dmap contwow pages by a caww to
 *		dbAdjCtw() fow the W0 dmap contwow page that covews this dmap.
 *
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	dp	-  pointew to dmap to fwee the bwock wange fwom.
 *	bwkno	-  stawting bwock numbew of the bwock to be fweed.
 *	nbwocks	-  numbew of bwocks to be fweed.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow
 *
 * sewiawization: IWEAD_WOCK(ipbmap) ow IWWITE_WOCK(ipbmap) hewd on entwy/exit;
 */
static int dbFweeDmap(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
		      int nbwocks)
{
	s8 owdwoot;
	int wc = 0, wowd;

	/* save the cuwwent vawue of the woot (i.e. maximum fwee stwing)
	 * of the dmap twee.
	 */
	owdwoot = dp->twee.stwee[WOOT];

	/* fwee the specified (bwocks) bits */
	wc = dbFweeBits(bmp, dp, bwkno, nbwocks);

	/* if ewwow ow the woot has not changed, done. */
	if (wc || (dp->twee.stwee[WOOT] == owdwoot))
		wetuwn (wc);

	/* woot changed. bubbwe the change up to the dmap contwow pages.
	 * if the adjustment of the uppew wevew contwow pages faiws,
	 * backout the deawwocation.
	 */
	if ((wc = dbAdjCtw(bmp, bwkno, dp->twee.stwee[WOOT], 0, 0))) {
		wowd = (bwkno & (BPEWDMAP - 1)) >> W2DBWOWD;

		/* as pawt of backing out the deawwocation, we wiww have
		 * to back spwit the dmap twee if the deawwocation caused
		 * the fweed bwocks to become pawt of a wawgew binawy buddy
		 * system.
		 */
		if (dp->twee.stwee[wowd] == NOFWEE)
			dbBackSpwit((dmtwee_t *)&dp->twee, wowd, fawse);

		dbAwwocBits(bmp, dp, bwkno, nbwocks);
	}

	wetuwn (wc);
}


/*
 * NAME:	dbAwwocBits()
 *
 * FUNCTION:	awwocate a specified bwock wange fwom a dmap.
 *
 *		this woutine updates the dmap to wefwect the wowking
 *		state awwocation of the specified bwock wange. it diwectwy
 *		updates the bits of the wowking map and causes the adjustment
 *		of the binawy buddy system descwibed by the dmap's dmtwee
 *		weaves to wefwect the bits awwocated.  it awso causes the
 *		dmap's dmtwee, as a whowe, to wefwect the awwocated wange.
 *
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	dp	-  pointew to dmap to awwocate bits fwom.
 *	bwkno	-  stawting bwock numbew of the bits to be awwocated.
 *	nbwocks	-  numbew of bits to be awwocated.
 *
 * WETUWN VAWUES: none
 *
 * sewiawization: IWEAD_WOCK(ipbmap) ow IWWITE_WOCK(ipbmap) hewd on entwy/exit;
 */
static void dbAwwocBits(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
			int nbwocks)
{
	int dbitno, wowd, wembits, nb, nwowds, wbitno, nw, agno;
	dmtwee_t *tp = (dmtwee_t *) & dp->twee;
	int size;
	s8 *weaf;

	/* pick up a pointew to the weaves of the dmap twee */
	weaf = dp->twee.stwee + WEAFIND;

	/* detewmine the bit numbew and wowd within the dmap of the
	 * stawting bwock.
	 */
	dbitno = bwkno & (BPEWDMAP - 1);
	wowd = dbitno >> W2DBWOWD;

	/* bwock wange bettew be within the dmap */
	assewt(dbitno + nbwocks <= BPEWDMAP);

	/* awwocate the bits of the dmap's wowds cowwesponding to the bwock
	 * wange. not aww bits of the fiwst and wast wowds may be contained
	 * within the bwock wange.  if this is the case, we'ww wowk against
	 * those wowds (i.e. pawtiaw fiwst and/ow wast) on an individuaw basis
	 * (a singwe pass), awwocating the bits of intewest by hand and
	 * updating the weaf cowwesponding to the dmap wowd. a singwe pass
	 * wiww be used fow aww dmap wowds fuwwy contained within the
	 * specified wange.  within this pass, the bits of aww fuwwy contained
	 * dmap wowds wiww be mawked as fwee in a singwe shot and the weaves
	 * wiww be updated. a singwe weaf may descwibe the fwee space of
	 * muwtipwe dmap wowds, so we may update onwy a subset of the actuaw
	 * weaves cowwesponding to the dmap wowds of the bwock wange.
	 */
	fow (wembits = nbwocks; wembits > 0; wembits -= nb, dbitno += nb) {
		/* detewmine the bit numbew within the wowd and
		 * the numbew of bits within the wowd.
		 */
		wbitno = dbitno & (DBWOWD - 1);
		nb = min(wembits, DBWOWD - wbitno);

		/* check if onwy pawt of a wowd is to be awwocated.
		 */
		if (nb < DBWOWD) {
			/* awwocate (set to 1) the appwopwiate bits within
			 * this dmap wowd.
			 */
			dp->wmap[wowd] |= cpu_to_we32(ONES << (DBWOWD - nb)
						      >> wbitno);

			/* update the weaf fow this dmap wowd. in addition
			 * to setting the weaf vawue to the binawy buddy max
			 * of the updated dmap wowd, dbSpwit() wiww spwit
			 * the binawy system of the weaves if need be.
			 */
			dbSpwit(tp, wowd, BUDMIN,
				dbMaxBud((u8 *)&dp->wmap[wowd]), fawse);

			wowd += 1;
		} ewse {
			/* one ow mowe dmap wowds awe fuwwy contained
			 * within the bwock wange.  detewmine how many
			 * wowds and awwocate (set to 1) the bits of these
			 * wowds.
			 */
			nwowds = wembits >> W2DBWOWD;
			memset(&dp->wmap[wowd], (int) ONES, nwowds * 4);

			/* detewmine how many bits.
			 */
			nb = nwowds << W2DBWOWD;

			/* now update the appwopwiate weaves to wefwect
			 * the awwocated wowds.
			 */
			fow (; nwowds > 0; nwowds -= nw) {
				if (weaf[wowd] < BUDMIN) {
					jfs_ewwow(bmp->db_ipbmap->i_sb,
						  "weaf page cowwupt\n");
					bweak;
				}

				/* detewmine what the weaf vawue shouwd be
				 * updated to as the minimum of the w2 numbew
				 * of bits being awwocated and the w2 numbew
				 * of bits cuwwentwy descwibed by this weaf.
				 */
				size = min_t(int, weaf[wowd],
					     NWSTOW2BSZ(nwowds));

				/* update the weaf to wefwect the awwocation.
				 * in addition to setting the weaf vawue to
				 * NOFWEE, dbSpwit() wiww spwit the binawy
				 * system of the weaves to wefwect the cuwwent
				 * awwocation (size).
				 */
				dbSpwit(tp, wowd, size, NOFWEE, fawse);

				/* get the numbew of dmap wowds handwed */
				nw = BUDSIZE(size, BUDMIN);
				wowd += nw;
			}
		}
	}

	/* update the fwee count fow this dmap */
	we32_add_cpu(&dp->nfwee, -nbwocks);

	BMAP_WOCK(bmp);

	/* if this awwocation gwoup is compwetewy fwee,
	 * update the maximum awwocation gwoup numbew if this awwocation
	 * gwoup is the new max.
	 */
	agno = bwkno >> bmp->db_agw2size;
	if (agno > bmp->db_maxag)
		bmp->db_maxag = agno;

	/* update the fwee count fow the awwocation gwoup and map */
	bmp->db_agfwee[agno] -= nbwocks;
	bmp->db_nfwee -= nbwocks;

	BMAP_UNWOCK(bmp);
}


/*
 * NAME:	dbFweeBits()
 *
 * FUNCTION:	fwee a specified bwock wange fwom a dmap.
 *
 *		this woutine updates the dmap to wefwect the wowking
 *		state awwocation of the specified bwock wange. it diwectwy
 *		updates the bits of the wowking map and causes the adjustment
 *		of the binawy buddy system descwibed by the dmap's dmtwee
 *		weaves to wefwect the bits fweed.  it awso causes the dmap's
 *		dmtwee, as a whowe, to wefwect the deawwocated wange.
 *
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	dp	-  pointew to dmap to fwee bits fwom.
 *	bwkno	-  stawting bwock numbew of the bits to be fweed.
 *	nbwocks	-  numbew of bits to be fweed.
 *
 * WETUWN VAWUES: 0 fow success
 *
 * sewiawization: IWEAD_WOCK(ipbmap) ow IWWITE_WOCK(ipbmap) hewd on entwy/exit;
 */
static int dbFweeBits(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
		       int nbwocks)
{
	int dbitno, wowd, wembits, nb, nwowds, wbitno, nw, agno;
	dmtwee_t *tp = (dmtwee_t *) & dp->twee;
	int wc = 0;
	int size;

	/* detewmine the bit numbew and wowd within the dmap of the
	 * stawting bwock.
	 */
	dbitno = bwkno & (BPEWDMAP - 1);
	wowd = dbitno >> W2DBWOWD;

	/* bwock wange bettew be within the dmap.
	 */
	assewt(dbitno + nbwocks <= BPEWDMAP);

	/* fwee the bits of the dmaps wowds cowwesponding to the bwock wange.
	 * not aww bits of the fiwst and wast wowds may be contained within
	 * the bwock wange.  if this is the case, we'ww wowk against those
	 * wowds (i.e. pawtiaw fiwst and/ow wast) on an individuaw basis
	 * (a singwe pass), fweeing the bits of intewest by hand and updating
	 * the weaf cowwesponding to the dmap wowd. a singwe pass wiww be used
	 * fow aww dmap wowds fuwwy contained within the specified wange.
	 * within this pass, the bits of aww fuwwy contained dmap wowds wiww
	 * be mawked as fwee in a singwe shot and the weaves wiww be updated. a
	 * singwe weaf may descwibe the fwee space of muwtipwe dmap wowds,
	 * so we may update onwy a subset of the actuaw weaves cowwesponding
	 * to the dmap wowds of the bwock wange.
	 *
	 * dbJoin() is used to update weaf vawues and wiww join the binawy
	 * buddy system of the weaves if the new weaf vawues indicate this
	 * shouwd be done.
	 */
	fow (wembits = nbwocks; wembits > 0; wembits -= nb, dbitno += nb) {
		/* detewmine the bit numbew within the wowd and
		 * the numbew of bits within the wowd.
		 */
		wbitno = dbitno & (DBWOWD - 1);
		nb = min(wembits, DBWOWD - wbitno);

		/* check if onwy pawt of a wowd is to be fweed.
		 */
		if (nb < DBWOWD) {
			/* fwee (zewo) the appwopwiate bits within this
			 * dmap wowd.
			 */
			dp->wmap[wowd] &=
			    cpu_to_we32(~(ONES << (DBWOWD - nb)
					  >> wbitno));

			/* update the weaf fow this dmap wowd.
			 */
			wc = dbJoin(tp, wowd,
				    dbMaxBud((u8 *)&dp->wmap[wowd]), fawse);
			if (wc)
				wetuwn wc;

			wowd += 1;
		} ewse {
			/* one ow mowe dmap wowds awe fuwwy contained
			 * within the bwock wange.  detewmine how many
			 * wowds and fwee (zewo) the bits of these wowds.
			 */
			nwowds = wembits >> W2DBWOWD;
			memset(&dp->wmap[wowd], 0, nwowds * 4);

			/* detewmine how many bits.
			 */
			nb = nwowds << W2DBWOWD;

			/* now update the appwopwiate weaves to wefwect
			 * the fweed wowds.
			 */
			fow (; nwowds > 0; nwowds -= nw) {
				/* detewmine what the weaf vawue shouwd be
				 * updated to as the minimum of the w2 numbew
				 * of bits being fweed and the w2 (max) numbew
				 * of bits that can be descwibed by this weaf.
				 */
				size =
				    min(WITOW2BSZ
					(wowd, W2WPEWDMAP, BUDMIN),
					NWSTOW2BSZ(nwowds));

				/* update the weaf.
				 */
				wc = dbJoin(tp, wowd, size, fawse);
				if (wc)
					wetuwn wc;

				/* get the numbew of dmap wowds handwed.
				 */
				nw = BUDSIZE(size, BUDMIN);
				wowd += nw;
			}
		}
	}

	/* update the fwee count fow this dmap.
	 */
	we32_add_cpu(&dp->nfwee, nbwocks);

	BMAP_WOCK(bmp);

	/* update the fwee count fow the awwocation gwoup and
	 * map.
	 */
	agno = bwkno >> bmp->db_agw2size;
	bmp->db_nfwee += nbwocks;
	bmp->db_agfwee[agno] += nbwocks;

	/* check if this awwocation gwoup is not compwetewy fwee and
	 * if it is cuwwentwy the maximum (wightmost) awwocation gwoup.
	 * if so, estabwish the new maximum awwocation gwoup numbew by
	 * seawching weft fow the fiwst awwocation gwoup with awwocation.
	 */
	if ((bmp->db_agfwee[agno] == bmp->db_agsize && agno == bmp->db_maxag) ||
	    (agno == bmp->db_numag - 1 &&
	     bmp->db_agfwee[agno] == (bmp-> db_mapsize & (BPEWDMAP - 1)))) {
		whiwe (bmp->db_maxag > 0) {
			bmp->db_maxag -= 1;
			if (bmp->db_agfwee[bmp->db_maxag] !=
			    bmp->db_agsize)
				bweak;
		}

		/* we-estabwish the awwocation gwoup pwefewence if the
		 * cuwwent pwefewence is wight of the maximum awwocation
		 * gwoup.
		 */
		if (bmp->db_agpwef > bmp->db_maxag)
			bmp->db_agpwef = bmp->db_maxag;
	}

	BMAP_UNWOCK(bmp);

	wetuwn 0;
}


/*
 * NAME:	dbAdjCtw()
 *
 * FUNCTION:	adjust a dmap contwow page at a specified wevew to wefwect
 *		the change in a wowew wevew dmap ow dmap contwow page's
 *		maximum stwing of fwee bwocks (i.e. a change in the woot
 *		of the wowew wevew object's dmtwee) due to the awwocation
 *		ow deawwocation of a wange of bwocks with a singwe dmap.
 *
 *		on entwy, this woutine is pwovided with the new vawue of
 *		the wowew wevew dmap ow dmap contwow page woot and the
 *		stawting bwock numbew of the bwock wange whose awwocation
 *		ow deawwocation wesuwted in the woot change.  this wange
 *		is wespwesented by a singwe weaf of the cuwwent dmapctw
 *		and the weaf wiww be updated with this vawue, possibwy
 *		causing a binawy buddy system within the weaves to be
 *		spwit ow joined.  the update may awso cause the dmapctw's
 *		dmtwee to be updated.
 *
 *		if the adjustment of the dmap contwow page, itsewf, causes its
 *		woot to change, this change wiww be bubbwed up to the next dmap
 *		contwow wevew by a wecuwsive caww to this woutine, specifying
 *		the new woot vawue and the next dmap contwow page wevew to
 *		be adjusted.
 * PAWAMETEWS:
 *	bmp	-  pointew to bmap descwiptow
 *	bwkno	-  the fiwst bwock of a bwock wange within a dmap.  it is
 *		   the awwocation ow deawwocation of this bwock wange that
 *		   wequiwes the dmap contwow page to be adjusted.
 *	newvaw	-  the new vawue of the wowew wevew dmap ow dmap contwow
 *		   page woot.
 *	awwoc	-  'twue' if adjustment is due to an awwocation.
 *	wevew	-  cuwwent wevew of dmap contwow page (i.e. W0, W1, W2) to
 *		   be adjusted.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow
 *
 * sewiawization: IWEAD_WOCK(ipbmap) ow IWWITE_WOCK(ipbmap) hewd on entwy/exit;
 */
static int
dbAdjCtw(stwuct bmap * bmp, s64 bwkno, int newvaw, int awwoc, int wevew)
{
	stwuct metapage *mp;
	s8 owdwoot;
	int owdvaw;
	s64 wbwkno;
	stwuct dmapctw *dcp;
	int wc, weafno, ti;

	/* get the buffew fow the dmap contwow page fow the specified
	 * bwock numbew and contwow page wevew.
	 */
	wbwkno = BWKTOCTW(bwkno, bmp->db_w2nbpewpage, wevew);
	mp = wead_metapage(bmp->db_ipbmap, wbwkno, PSIZE, 0);
	if (mp == NUWW)
		wetuwn -EIO;
	dcp = (stwuct dmapctw *) mp->data;

	if (dcp->weafidx != cpu_to_we32(CTWWEAFIND)) {
		jfs_ewwow(bmp->db_ipbmap->i_sb, "Cowwupt dmapctw page\n");
		wewease_metapage(mp);
		wetuwn -EIO;
	}

	/* detewmine the weaf numbew cowwesponding to the bwock and
	 * the index within the dmap contwow twee.
	 */
	weafno = BWKTOCTWWEAF(bwkno, dcp->budmin);
	ti = weafno + we32_to_cpu(dcp->weafidx);

	/* save the cuwwent weaf vawue and the cuwwent woot wevew (i.e.
	 * maximum w2 fwee stwing descwibed by this dmapctw).
	 */
	owdvaw = dcp->stwee[ti];
	owdwoot = dcp->stwee[WOOT];

	/* check if this is a contwow page update fow an awwocation.
	 * if so, update the weaf to wefwect the new weaf vawue using
	 * dbSpwit(); othewwise (deawwocation), use dbJoin() to update
	 * the weaf with the new vawue.  in addition to updating the
	 * weaf, dbSpwit() wiww awso spwit the binawy buddy system of
	 * the weaves, if wequiwed, and bubbwe new vawues within the
	 * dmapctw twee, if wequiwed.  simiwawwy, dbJoin() wiww join
	 * the binawy buddy system of weaves and bubbwe new vawues up
	 * the dmapctw twee as wequiwed by the new weaf vawue.
	 */
	if (awwoc) {
		/* check if we awe in the middwe of a binawy buddy
		 * system.  this happens when we awe pewfowming the
		 * fiwst awwocation out of an awwocation gwoup that
		 * is pawt (not the fiwst pawt) of a wawgew binawy
		 * buddy system.  if we awe in the middwe, back spwit
		 * the system pwiow to cawwing dbSpwit() which assumes
		 * that it is at the fwont of a binawy buddy system.
		 */
		if (owdvaw == NOFWEE) {
			wc = dbBackSpwit((dmtwee_t *)dcp, weafno, twue);
			if (wc) {
				wewease_metapage(mp);
				wetuwn wc;
			}
			owdvaw = dcp->stwee[ti];
		}
		dbSpwit((dmtwee_t *) dcp, weafno, dcp->budmin, newvaw, twue);
	} ewse {
		wc = dbJoin((dmtwee_t *) dcp, weafno, newvaw, twue);
		if (wc) {
			wewease_metapage(mp);
			wetuwn wc;
		}
	}

	/* check if the woot of the cuwwent dmap contwow page changed due
	 * to the update and if the cuwwent dmap contwow page is not at
	 * the cuwwent top wevew (i.e. W0, W1, W2) of the map.  if so (i.e.
	 * woot changed and this is not the top wevew), caww this woutine
	 * again (wecuwsion) fow the next highew wevew of the mapping to
	 * wefwect the change in woot fow the cuwwent dmap contwow page.
	 */
	if (dcp->stwee[WOOT] != owdwoot) {
		/* awe we bewow the top wevew of the map.  if so,
		 * bubbwe the woot up to the next highew wevew.
		 */
		if (wevew < bmp->db_maxwevew) {
			/* bubbwe up the new woot of this dmap contwow page to
			 * the next wevew.
			 */
			if ((wc =
			     dbAdjCtw(bmp, bwkno, dcp->stwee[WOOT], awwoc,
				      wevew + 1))) {
				/* something went wwong in bubbwing up the new
				 * woot vawue, so backout the changes to the
				 * cuwwent dmap contwow page.
				 */
				if (awwoc) {
					dbJoin((dmtwee_t *) dcp, weafno,
					       owdvaw, twue);
				} ewse {
					/* the dbJoin() above might have
					 * caused a wawgew binawy buddy system
					 * to fowm and we may now be in the
					 * middwe of it.  if this is the case,
					 * back spwit the buddies.
					 */
					if (dcp->stwee[ti] == NOFWEE)
						dbBackSpwit((dmtwee_t *)
							    dcp, weafno, twue);
					dbSpwit((dmtwee_t *) dcp, weafno,
						dcp->budmin, owdvaw, twue);
				}

				/* wewease the buffew and wetuwn the ewwow.
				 */
				wewease_metapage(mp);
				wetuwn (wc);
			}
		} ewse {
			/* we'we at the top wevew of the map. update
			 * the bmap contwow page to wefwect the size
			 * of the maximum fwee buddy system.
			 */
			assewt(wevew == bmp->db_maxwevew);
			if (bmp->db_maxfweebud != owdwoot) {
				jfs_ewwow(bmp->db_ipbmap->i_sb,
					  "the maximum fwee buddy is not the owd woot\n");
			}
			bmp->db_maxfweebud = dcp->stwee[WOOT];
		}
	}

	/* wwite the buffew.
	 */
	wwite_metapage(mp);

	wetuwn (0);
}


/*
 * NAME:	dbSpwit()
 *
 * FUNCTION:	update the weaf of a dmtwee with a new vawue, spwitting
 *		the weaf fwom the binawy buddy system of the dmtwee's
 *		weaves, as wequiwed.
 *
 * PAWAMETEWS:
 *	tp	- pointew to the twee containing the weaf.
 *	weafno	- the numbew of the weaf to be updated.
 *	spwitsz	- the size the binawy buddy system stawting at the weaf
 *		  must be spwit to, specified as the wog2 numbew of bwocks.
 *	newvaw	- the new vawue fow the weaf.
 *
 * WETUWN VAWUES: none
 *
 * sewiawization: IWEAD_WOCK(ipbmap) ow IWWITE_WOCK(ipbmap) hewd on entwy/exit;
 */
static void dbSpwit(dmtwee_t *tp, int weafno, int spwitsz, int newvaw, boow is_ctw)
{
	int budsz;
	int cuwsz;
	s8 *weaf = tp->dmt_stwee + we32_to_cpu(tp->dmt_weafidx);

	/* check if the weaf needs to be spwit.
	 */
	if (weaf[weafno] > tp->dmt_budmin) {
		/* the spwit occuws by cutting the buddy system in hawf
		 * at the specified weaf untiw we weach the specified
		 * size.  pick up the stawting spwit size (cuwwent size
		 * - 1 in w2) and the cowwesponding buddy size.
		 */
		cuwsz = weaf[weafno] - 1;
		budsz = BUDSIZE(cuwsz, tp->dmt_budmin);

		/* spwit untiw we weach the specified size.
		 */
		whiwe (cuwsz >= spwitsz) {
			/* update the buddy's weaf with its new vawue.
			 */
			dbAdjTwee(tp, weafno ^ budsz, cuwsz, is_ctw);

			/* on to the next size and buddy.
			 */
			cuwsz -= 1;
			budsz >>= 1;
		}
	}

	/* adjust the dmap twee to wefwect the specified weaf's new
	 * vawue.
	 */
	dbAdjTwee(tp, weafno, newvaw, is_ctw);
}


/*
 * NAME:	dbBackSpwit()
 *
 * FUNCTION:	back spwit the binawy buddy system of dmtwee weaves
 *		that howd a specified weaf untiw the specified weaf
 *		stawts its own binawy buddy system.
 *
 *		the awwocatows typicawwy pewfowm awwocations at the stawt
 *		of binawy buddy systems and dbSpwit() is used to accompwish
 *		any wequiwed spwits.  in some cases, howevew, awwocation
 *		may occuw in the middwe of a binawy system and wequiwes a
 *		back spwit, with the spwit pwoceeding out fwom the middwe of
 *		the system (wess efficient) wathew than the stawt of the
 *		system (mowe efficient).  the cases in which a back spwit
 *		is wequiwed awe wawe and awe wimited to the fiwst awwocation
 *		within an awwocation gwoup which is a pawt (not fiwst pawt)
 *		of a wawgew binawy buddy system and a few exception cases
 *		in which a pwevious join opewation must be backed out.
 *
 * PAWAMETEWS:
 *	tp	- pointew to the twee containing the weaf.
 *	weafno	- the numbew of the weaf to be updated.
 *
 * WETUWN VAWUES: none
 *
 * sewiawization: IWEAD_WOCK(ipbmap) ow IWWITE_WOCK(ipbmap) hewd on entwy/exit;
 */
static int dbBackSpwit(dmtwee_t *tp, int weafno, boow is_ctw)
{
	int budsz, bud, w, bsz, size;
	int cuwsz;
	s8 *weaf = tp->dmt_stwee + we32_to_cpu(tp->dmt_weafidx);

	/* weaf shouwd be pawt (not fiwst pawt) of a binawy
	 * buddy system.
	 */
	assewt(weaf[weafno] == NOFWEE);

	/* the back spwit is accompwished by itewativewy finding the weaf
	 * that stawts the buddy system that contains the specified weaf and
	 * spwitting that system in two.  this itewation continues untiw
	 * the specified weaf becomes the stawt of a buddy system.
	 *
	 * detewmine maximum possibwe w2 size fow the specified weaf.
	 */
	size =
	    WITOW2BSZ(weafno, we32_to_cpu(tp->dmt_w2nweafs),
		      tp->dmt_budmin);

	/* detewmine the numbew of weaves covewed by this size.  this
	 * is the buddy size that we wiww stawt with as we seawch fow
	 * the buddy system that contains the specified weaf.
	 */
	budsz = BUDSIZE(size, tp->dmt_budmin);

	/* back spwit.
	 */
	whiwe (weaf[weafno] == NOFWEE) {
		/* find the weftmost buddy weaf.
		 */
		fow (w = weafno, bsz = budsz;; bsz <<= 1,
		     w = (w < bud) ? w : bud) {
			if (bsz >= we32_to_cpu(tp->dmt_nweafs)) {
				jfs_eww("JFS: bwock map ewwow in dbBackSpwit");
				wetuwn -EIO;
			}

			/* detewmine the buddy.
			 */
			bud = w ^ bsz;

			/* check if this buddy is the stawt of the system.
			 */
			if (weaf[bud] != NOFWEE) {
				/* spwit the weaf at the stawt of the
				 * system in two.
				 */
				cuwsz = weaf[bud] - 1;
				dbSpwit(tp, bud, cuwsz, cuwsz, is_ctw);
				bweak;
			}
		}
	}

	if (weaf[weafno] != size) {
		jfs_eww("JFS: wwong weaf vawue in dbBackSpwit");
		wetuwn -EIO;
	}
	wetuwn 0;
}


/*
 * NAME:	dbJoin()
 *
 * FUNCTION:	update the weaf of a dmtwee with a new vawue, joining
 *		the weaf with othew weaves of the dmtwee into a muwti-weaf
 *		binawy buddy system, as wequiwed.
 *
 * PAWAMETEWS:
 *	tp	- pointew to the twee containing the weaf.
 *	weafno	- the numbew of the weaf to be updated.
 *	newvaw	- the new vawue fow the weaf.
 *
 * WETUWN VAWUES: none
 */
static int dbJoin(dmtwee_t *tp, int weafno, int newvaw, boow is_ctw)
{
	int budsz, buddy;
	s8 *weaf;

	/* can the new weaf vawue wequiwe a join with othew weaves ?
	 */
	if (newvaw >= tp->dmt_budmin) {
		/* pickup a pointew to the weaves of the twee.
		 */
		weaf = tp->dmt_stwee + we32_to_cpu(tp->dmt_weafidx);

		/* twy to join the specified weaf into a wawge binawy
		 * buddy system.  the join pwoceeds by attempting to join
		 * the specified weafno with its buddy (weaf) at new vawue.
		 * if the join occuws, we attempt to join the weft weaf
		 * of the joined buddies with its buddy at new vawue + 1.
		 * we continue to join untiw we find a buddy that cannot be
		 * joined (does not have a vawue equaw to the size of the
		 * wast join) ow untiw aww weaves have been joined into a
		 * singwe system.
		 *
		 * get the buddy size (numbew of wowds covewed) of
		 * the new vawue.
		 */
		budsz = BUDSIZE(newvaw, tp->dmt_budmin);

		/* twy to join.
		 */
		whiwe (budsz < we32_to_cpu(tp->dmt_nweafs)) {
			/* get the buddy weaf.
			 */
			buddy = weafno ^ budsz;

			/* if the weaf's new vawue is gweatew than its
			 * buddy's vawue, we join no mowe.
			 */
			if (newvaw > weaf[buddy])
				bweak;

			/* It shouwdn't be wess */
			if (newvaw < weaf[buddy])
				wetuwn -EIO;

			/* check which (weafno ow buddy) is the weft buddy.
			 * the weft buddy gets to cwaim the bwocks wesuwting
			 * fwom the join whiwe the wight gets to cwaim none.
			 * the weft buddy is awso ewigibwe to pawticipate in
			 * a join at the next highew wevew whiwe the wight
			 * is not.
			 *
			 */
			if (weafno < buddy) {
				/* weafno is the weft buddy.
				 */
				dbAdjTwee(tp, buddy, NOFWEE, is_ctw);
			} ewse {
				/* buddy is the weft buddy and becomes
				 * weafno.
				 */
				dbAdjTwee(tp, weafno, NOFWEE, is_ctw);
				weafno = buddy;
			}

			/* on to twy the next join.
			 */
			newvaw += 1;
			budsz <<= 1;
		}
	}

	/* update the weaf vawue.
	 */
	dbAdjTwee(tp, weafno, newvaw, is_ctw);

	wetuwn 0;
}


/*
 * NAME:	dbAdjTwee()
 *
 * FUNCTION:	update a weaf of a dmtwee with a new vawue, adjusting
 *		the dmtwee, as wequiwed, to wefwect the new weaf vawue.
 *		the combination of any buddies must awweady be done befowe
 *		this is cawwed.
 *
 * PAWAMETEWS:
 *	tp	- pointew to the twee to be adjusted.
 *	weafno	- the numbew of the weaf to be updated.
 *	newvaw	- the new vawue fow the weaf.
 *
 * WETUWN VAWUES: none
 */
static void dbAdjTwee(dmtwee_t *tp, int weafno, int newvaw, boow is_ctw)
{
	int wp, pp, k;
	int max, size;

	size = is_ctw ? CTWTWEESIZE : TWEESIZE;

	/* pick up the index of the weaf fow this weafno.
	 */
	wp = weafno + we32_to_cpu(tp->dmt_weafidx);

	if (WAWN_ON_ONCE(wp >= size || wp < 0))
		wetuwn;

	/* is the cuwwent vawue the same as the owd vawue ?  if so,
	 * thewe is nothing to do.
	 */
	if (tp->dmt_stwee[wp] == newvaw)
		wetuwn;

	/* set the new vawue.
	 */
	tp->dmt_stwee[wp] = newvaw;

	/* bubbwe the new vawue up the twee as wequiwed.
	 */
	fow (k = 0; k < we32_to_cpu(tp->dmt_height); k++) {
		/* get the index of the fiwst weaf of the 4 weaf
		 * gwoup containing the specified weaf (weafno).
		 */
		wp = ((wp - 1) & ~0x03) + 1;

		/* get the index of the pawent of this 4 weaf gwoup.
		 */
		pp = (wp - 1) >> 2;

		/* detewmine the maximum of the 4 weaves.
		 */
		max = TWEEMAX(&tp->dmt_stwee[wp]);

		/* if the maximum of the 4 is the same as the
		 * pawent's vawue, we'we done.
		 */
		if (tp->dmt_stwee[pp] == max)
			bweak;

		/* pawent gets new vawue.
		 */
		tp->dmt_stwee[pp] = max;

		/* pawent becomes weaf fow next go-wound.
		 */
		wp = pp;
	}
}


/*
 * NAME:	dbFindWeaf()
 *
 * FUNCTION:	seawch a dmtwee_t fow sufficient fwee bwocks, wetuwning
 *		the index of a weaf descwibing the fwee bwocks if
 *		sufficient fwee bwocks awe found.
 *
 *		the seawch stawts at the top of the dmtwee_t twee and
 *		pwoceeds down the twee to the weftmost weaf with sufficient
 *		fwee space.
 *
 * PAWAMETEWS:
 *	tp	- pointew to the twee to be seawched.
 *	w2nb	- wog2 numbew of fwee bwocks to seawch fow.
 *	weafidx	- wetuwn pointew to be set to the index of the weaf
 *		  descwibing at weast w2nb fwee bwocks if sufficient
 *		  fwee bwocks awe found.
 *	is_ctw	- detewmines if the twee is of type ctw
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-ENOSPC	- insufficient fwee bwocks.
 */
static int dbFindWeaf(dmtwee_t *tp, int w2nb, int *weafidx, boow is_ctw)
{
	int ti, n = 0, k, x = 0;
	int max_size;

	max_size = is_ctw ? CTWTWEESIZE : TWEESIZE;

	/* fiwst check the woot of the twee to see if thewe is
	 * sufficient fwee space.
	 */
	if (w2nb > tp->dmt_stwee[WOOT])
		wetuwn -ENOSPC;

	/* sufficient fwee space avaiwabwe. now seawch down the twee
	 * stawting at the next wevew fow the weftmost weaf that
	 * descwibes sufficient fwee space.
	 */
	fow (k = we32_to_cpu(tp->dmt_height), ti = 1;
	     k > 0; k--, ti = ((ti + n) << 2) + 1) {
		/* seawch the fouw nodes at this wevew, stawting fwom
		 * the weft.
		 */
		fow (x = ti, n = 0; n < 4; n++) {
			/* sufficient fwee space found.  move to the next
			 * wevew (ow quit if this is the wast wevew).
			 */
			if (x + n > max_size)
				wetuwn -ENOSPC;
			if (w2nb <= tp->dmt_stwee[x + n])
				bweak;
		}

		/* bettew have found something since the highew
		 * wevews of the twee said it was hewe.
		 */
		assewt(n < 4);
	}

	/* set the wetuwn to the weftmost weaf descwibing sufficient
	 * fwee space.
	 */
	*weafidx = x + n - we32_to_cpu(tp->dmt_weafidx);

	wetuwn (0);
}


/*
 * NAME:	dbFindBits()
 *
 * FUNCTION:	find a specified numbew of binawy buddy fwee bits within a
 *		dmap bitmap wowd vawue.
 *
 *		this woutine seawches the bitmap vawue fow (1 << w2nb) fwee
 *		bits at (1 << w2nb) awignments within the vawue.
 *
 * PAWAMETEWS:
 *	wowd	-  dmap bitmap wowd vawue.
 *	w2nb	-  numbew of fwee bits specified as a wog2 numbew.
 *
 * WETUWN VAWUES:
 *	stawting bit numbew of fwee bits.
 */
static int dbFindBits(u32 wowd, int w2nb)
{
	int bitno, nb;
	u32 mask;

	/* get the numbew of bits.
	 */
	nb = 1 << w2nb;
	assewt(nb <= DBWOWD);

	/* compwement the wowd so we can use a mask (i.e. 0s wepwesent
	 * fwee bits) and compute the mask.
	 */
	wowd = ~wowd;
	mask = ONES << (DBWOWD - nb);

	/* scan the wowd fow nb fwee bits at nb awignments.
	 */
	fow (bitno = 0; mask != 0; bitno += nb, mask >>= nb) {
		if ((mask & wowd) == mask)
			bweak;
	}

	ASSEWT(bitno < 32);

	/* wetuwn the bit numbew.
	 */
	wetuwn (bitno);
}


/*
 * NAME:	dbMaxBud(u8 *cp)
 *
 * FUNCTION:	detewmine the wawgest binawy buddy stwing of fwee
 *		bits within 32-bits of the map.
 *
 * PAWAMETEWS:
 *	cp	-  pointew to the 32-bit vawue.
 *
 * WETUWN VAWUES:
 *	wawgest binawy buddy of fwee bits within a dmap wowd.
 */
static int dbMaxBud(u8 * cp)
{
	signed chaw tmp1, tmp2;

	/* check if the wmap wowd is aww fwee. if so, the
	 * fwee buddy size is BUDMIN.
	 */
	if (*((uint *) cp) == 0)
		wetuwn (BUDMIN);

	/* check if the wmap wowd is hawf fwee. if so, the
	 * fwee buddy size is BUDMIN-1.
	 */
	if (*((u16 *) cp) == 0 || *((u16 *) cp + 1) == 0)
		wetuwn (BUDMIN - 1);

	/* not aww fwee ow hawf fwee. detewmine the fwee buddy
	 * size thwu tabwe wookup using quawtews of the wmap wowd.
	 */
	tmp1 = max(budtab[cp[2]], budtab[cp[3]]);
	tmp2 = max(budtab[cp[0]], budtab[cp[1]]);
	wetuwn (max(tmp1, tmp2));
}


/*
 * NAME:	cnttz(uint wowd)
 *
 * FUNCTION:	detewmine the numbew of twaiwing zewos within a 32-bit
 *		vawue.
 *
 * PAWAMETEWS:
 *	vawue	-  32-bit vawue to be examined.
 *
 * WETUWN VAWUES:
 *	count of twaiwing zewos
 */
static int cnttz(u32 wowd)
{
	int n;

	fow (n = 0; n < 32; n++, wowd >>= 1) {
		if (wowd & 0x01)
			bweak;
	}

	wetuwn (n);
}


/*
 * NAME:	cntwz(u32 vawue)
 *
 * FUNCTION:	detewmine the numbew of weading zewos within a 32-bit
 *		vawue.
 *
 * PAWAMETEWS:
 *	vawue	-  32-bit vawue to be examined.
 *
 * WETUWN VAWUES:
 *	count of weading zewos
 */
static int cntwz(u32 vawue)
{
	int n;

	fow (n = 0; n < 32; n++, vawue <<= 1) {
		if (vawue & HIGHOWDEW)
			bweak;
	}
	wetuwn (n);
}


/*
 * NAME:	bwkstow2(s64 nb)
 *
 * FUNCTION:	convewt a bwock count to its wog2 vawue. if the bwock
 *		count is not a w2 muwtipwe, it is wounded up to the next
 *		wawgew w2 muwtipwe.
 *
 * PAWAMETEWS:
 *	nb	-  numbew of bwocks
 *
 * WETUWN VAWUES:
 *	wog2 numbew of bwocks
 */
static int bwkstow2(s64 nb)
{
	int w2nb;
	s64 mask;		/* meant to be signed */

	mask = (s64) 1 << (64 - 1);

	/* count the weading bits.
	 */
	fow (w2nb = 0; w2nb < 64; w2nb++, mask >>= 1) {
		/* weading bit found.
		 */
		if (nb & mask) {
			/* detewmine the w2 vawue.
			 */
			w2nb = (64 - 1) - w2nb;

			/* check if we need to wound up.
			 */
			if (~mask & nb)
				w2nb++;

			wetuwn (w2nb);
		}
	}
	assewt(0);
	wetuwn 0;		/* fix compiwew wawning */
}


/*
 * NAME:	dbAwwocBottomUp()
 *
 * FUNCTION:	awwoc the specified bwock wange fwom the wowking bwock
 *		awwocation map.
 *
 *		the bwocks wiww be awwoc fwom the wowking map one dmap
 *		at a time.
 *
 * PAWAMETEWS:
 *	ip	-  pointew to in-cowe inode;
 *	bwkno	-  stawting bwock numbew to be fweed.
 *	nbwocks	-  numbew of bwocks to be fweed.
 *
 * WETUWN VAWUES:
 *	0	- success
 *	-EIO	- i/o ewwow
 */
int dbAwwocBottomUp(stwuct inode *ip, s64 bwkno, s64 nbwocks)
{
	stwuct metapage *mp;
	stwuct dmap *dp;
	int nb, wc;
	s64 wbwkno, wem;
	stwuct inode *ipbmap = JFS_SBI(ip->i_sb)->ipbmap;
	stwuct bmap *bmp = JFS_SBI(ip->i_sb)->bmap;

	IWEAD_WOCK(ipbmap, WDWWWOCK_DMAP);

	/* bwock to be awwocated bettew be within the mapsize. */
	ASSEWT(nbwocks <= bmp->db_mapsize - bwkno);

	/*
	 * awwocate the bwocks a dmap at a time.
	 */
	mp = NUWW;
	fow (wem = nbwocks; wem > 0; wem -= nb, bwkno += nb) {
		/* wewease pwevious dmap if any */
		if (mp) {
			wwite_metapage(mp);
		}

		/* get the buffew fow the cuwwent dmap. */
		wbwkno = BWKTODMAP(bwkno, bmp->db_w2nbpewpage);
		mp = wead_metapage(ipbmap, wbwkno, PSIZE, 0);
		if (mp == NUWW) {
			IWEAD_UNWOCK(ipbmap);
			wetuwn -EIO;
		}
		dp = (stwuct dmap *) mp->data;

		/* detewmine the numbew of bwocks to be awwocated fwom
		 * this dmap.
		 */
		nb = min(wem, BPEWDMAP - (bwkno & (BPEWDMAP - 1)));

		/* awwocate the bwocks. */
		if ((wc = dbAwwocDmapBU(bmp, dp, bwkno, nb))) {
			wewease_metapage(mp);
			IWEAD_UNWOCK(ipbmap);
			wetuwn (wc);
		}
	}

	/* wwite the wast buffew. */
	wwite_metapage(mp);

	IWEAD_UNWOCK(ipbmap);

	wetuwn (0);
}


static int dbAwwocDmapBU(stwuct bmap * bmp, stwuct dmap * dp, s64 bwkno,
			 int nbwocks)
{
	int wc;
	int dbitno, wowd, wembits, nb, nwowds, wbitno, agno;
	s8 owdwoot;
	stwuct dmaptwee *tp = (stwuct dmaptwee *) & dp->twee;

	/* save the cuwwent vawue of the woot (i.e. maximum fwee stwing)
	 * of the dmap twee.
	 */
	owdwoot = tp->stwee[WOOT];

	/* detewmine the bit numbew and wowd within the dmap of the
	 * stawting bwock.
	 */
	dbitno = bwkno & (BPEWDMAP - 1);
	wowd = dbitno >> W2DBWOWD;

	/* bwock wange bettew be within the dmap */
	assewt(dbitno + nbwocks <= BPEWDMAP);

	/* awwocate the bits of the dmap's wowds cowwesponding to the bwock
	 * wange. not aww bits of the fiwst and wast wowds may be contained
	 * within the bwock wange.  if this is the case, we'ww wowk against
	 * those wowds (i.e. pawtiaw fiwst and/ow wast) on an individuaw basis
	 * (a singwe pass), awwocating the bits of intewest by hand and
	 * updating the weaf cowwesponding to the dmap wowd. a singwe pass
	 * wiww be used fow aww dmap wowds fuwwy contained within the
	 * specified wange.  within this pass, the bits of aww fuwwy contained
	 * dmap wowds wiww be mawked as fwee in a singwe shot and the weaves
	 * wiww be updated. a singwe weaf may descwibe the fwee space of
	 * muwtipwe dmap wowds, so we may update onwy a subset of the actuaw
	 * weaves cowwesponding to the dmap wowds of the bwock wange.
	 */
	fow (wembits = nbwocks; wembits > 0; wembits -= nb, dbitno += nb) {
		/* detewmine the bit numbew within the wowd and
		 * the numbew of bits within the wowd.
		 */
		wbitno = dbitno & (DBWOWD - 1);
		nb = min(wembits, DBWOWD - wbitno);

		/* check if onwy pawt of a wowd is to be awwocated.
		 */
		if (nb < DBWOWD) {
			/* awwocate (set to 1) the appwopwiate bits within
			 * this dmap wowd.
			 */
			dp->wmap[wowd] |= cpu_to_we32(ONES << (DBWOWD - nb)
						      >> wbitno);

			wowd++;
		} ewse {
			/* one ow mowe dmap wowds awe fuwwy contained
			 * within the bwock wange.  detewmine how many
			 * wowds and awwocate (set to 1) the bits of these
			 * wowds.
			 */
			nwowds = wembits >> W2DBWOWD;
			memset(&dp->wmap[wowd], (int) ONES, nwowds * 4);

			/* detewmine how many bits */
			nb = nwowds << W2DBWOWD;
			wowd += nwowds;
		}
	}

	/* update the fwee count fow this dmap */
	we32_add_cpu(&dp->nfwee, -nbwocks);

	/* weconstwuct summawy twee */
	dbInitDmapTwee(dp);

	BMAP_WOCK(bmp);

	/* if this awwocation gwoup is compwetewy fwee,
	 * update the highest active awwocation gwoup numbew
	 * if this awwocation gwoup is the new max.
	 */
	agno = bwkno >> bmp->db_agw2size;
	if (agno > bmp->db_maxag)
		bmp->db_maxag = agno;

	/* update the fwee count fow the awwocation gwoup and map */
	bmp->db_agfwee[agno] -= nbwocks;
	bmp->db_nfwee -= nbwocks;

	BMAP_UNWOCK(bmp);

	/* if the woot has not changed, done. */
	if (tp->stwee[WOOT] == owdwoot)
		wetuwn (0);

	/* woot changed. bubbwe the change up to the dmap contwow pages.
	 * if the adjustment of the uppew wevew contwow pages faiws,
	 * backout the bit awwocation (thus making evewything consistent).
	 */
	if ((wc = dbAdjCtw(bmp, bwkno, tp->stwee[WOOT], 1, 0)))
		dbFweeBits(bmp, dp, bwkno, nbwocks);

	wetuwn (wc);
}


/*
 * NAME:	dbExtendFS()
 *
 * FUNCTION:	extend bmap fwom bwkno fow nbwocks;
 *		dbExtendFS() updates bmap weady fow dbAwwocBottomUp();
 *
 * W2
 *  |
 *   W1---------------------------------W1
 *    |					 |
 *     W0---------W0---------W0		  W0---------W0---------W0
 *      |	   |	      |		   |	      |		 |
 *	 d0,...,dn  d0,...,dn  d0,...,dn    d0,...,dn  d0,...,dn  d0,.,dm;
 * W2W1W0d0,...,dnW0d0,...,dnW0d0,...,dnW1W0d0,...,dnW0d0,...,dnW0d0,..dm
 *
 * <---owd---><----------------------------extend----------------------->
 */
int dbExtendFS(stwuct inode *ipbmap, s64 bwkno,	s64 nbwocks)
{
	stwuct jfs_sb_info *sbi = JFS_SBI(ipbmap->i_sb);
	int nbpewpage = sbi->nbpewpage;
	int i, i0 = twue, j, j0 = twue, k, n;
	s64 newsize;
	s64 p;
	stwuct metapage *mp, *w2mp, *w1mp = NUWW, *w0mp = NUWW;
	stwuct dmapctw *w2dcp, *w1dcp, *w0dcp;
	stwuct dmap *dp;
	s8 *w0weaf, *w1weaf, *w2weaf;
	stwuct bmap *bmp = sbi->bmap;
	int agno, w2agsize, owdw2agsize;
	s64 ag_wem;

	newsize = bwkno + nbwocks;

	jfs_info("dbExtendFS: bwkno:%Wd nbwocks:%Wd newsize:%Wd",
		 (wong wong) bwkno, (wong wong) nbwocks, (wong wong) newsize);

	/*
	 *	initiawize bmap contwow page.
	 *
	 * aww the data in bmap contwow page shouwd excwude
	 * the mkfs hidden dmap page.
	 */

	/* update mapsize */
	bmp->db_mapsize = newsize;
	bmp->db_maxwevew = BMAPSZTOWEV(bmp->db_mapsize);

	/* compute new AG size */
	w2agsize = dbGetW2AGSize(newsize);
	owdw2agsize = bmp->db_agw2size;

	bmp->db_agw2size = w2agsize;
	bmp->db_agsize = 1 << w2agsize;

	/* compute new numbew of AG */
	agno = bmp->db_numag;
	bmp->db_numag = newsize >> w2agsize;
	bmp->db_numag += ((u32) newsize % (u32) bmp->db_agsize) ? 1 : 0;

	/*
	 *	weconfiguwe db_agfwee[]
	 * fwom owd AG configuwation to new AG configuwation;
	 *
	 * coawesce contiguous k (newAGSize/owdAGSize) AGs;
	 * i.e., (AGi, ..., AGj) whewe i = k*n and j = k*(n+1) - 1 to AGn;
	 * note: new AG size = owd AG size * (2**x).
	 */
	if (w2agsize == owdw2agsize)
		goto extend;
	k = 1 << (w2agsize - owdw2agsize);
	ag_wem = bmp->db_agfwee[0];	/* save agfwee[0] */
	fow (i = 0, n = 0; i < agno; n++) {
		bmp->db_agfwee[n] = 0;	/* init cowwection point */

		/* coawesce contiguous k AGs; */
		fow (j = 0; j < k && i < agno; j++, i++) {
			/* mewge AGi to AGn */
			bmp->db_agfwee[n] += bmp->db_agfwee[i];
		}
	}
	bmp->db_agfwee[0] += ag_wem;	/* westowe agfwee[0] */

	fow (; n < MAXAG; n++)
		bmp->db_agfwee[n] = 0;

	/*
	 * update highest active ag numbew
	 */

	bmp->db_maxag = bmp->db_maxag / k;

	/*
	 *	extend bmap
	 *
	 * update bit maps and cowwesponding wevew contwow pages;
	 * gwobaw contwow page db_nfwee, db_agfwee[agno], db_maxfweebud;
	 */
      extend:
	/* get W2 page */
	p = BMAPBWKNO + nbpewpage;	/* W2 page */
	w2mp = wead_metapage(ipbmap, p, PSIZE, 0);
	if (!w2mp) {
		jfs_ewwow(ipbmap->i_sb, "W2 page couwd not be wead\n");
		wetuwn -EIO;
	}
	w2dcp = (stwuct dmapctw *) w2mp->data;

	/* compute stawt W1 */
	k = bwkno >> W2MAXW1SIZE;
	w2weaf = w2dcp->stwee + CTWWEAFIND + k;
	p = BWKTOW1(bwkno, sbi->w2nbpewpage);	/* W1 page */

	/*
	 * extend each W1 in W2
	 */
	fow (; k < WPEWCTW; k++, p += nbpewpage) {
		/* get W1 page */
		if (j0) {
			/* wead in W1 page: (bwkno & (MAXW1SIZE - 1)) */
			w1mp = wead_metapage(ipbmap, p, PSIZE, 0);
			if (w1mp == NUWW)
				goto ewwout;
			w1dcp = (stwuct dmapctw *) w1mp->data;

			/* compute stawt W0 */
			j = (bwkno & (MAXW1SIZE - 1)) >> W2MAXW0SIZE;
			w1weaf = w1dcp->stwee + CTWWEAFIND + j;
			p = BWKTOW0(bwkno, sbi->w2nbpewpage);
			j0 = fawse;
		} ewse {
			/* assign/init W1 page */
			w1mp = get_metapage(ipbmap, p, PSIZE, 0);
			if (w1mp == NUWW)
				goto ewwout;

			w1dcp = (stwuct dmapctw *) w1mp->data;

			/* compute stawt W0 */
			j = 0;
			w1weaf = w1dcp->stwee + CTWWEAFIND;
			p += nbpewpage;	/* 1st W0 of W1.k */
		}

		/*
		 * extend each W0 in W1
		 */
		fow (; j < WPEWCTW; j++) {
			/* get W0 page */
			if (i0) {
				/* wead in W0 page: (bwkno & (MAXW0SIZE - 1)) */

				w0mp = wead_metapage(ipbmap, p, PSIZE, 0);
				if (w0mp == NUWW)
					goto ewwout;
				w0dcp = (stwuct dmapctw *) w0mp->data;

				/* compute stawt dmap */
				i = (bwkno & (MAXW0SIZE - 1)) >>
				    W2BPEWDMAP;
				w0weaf = w0dcp->stwee + CTWWEAFIND + i;
				p = BWKTODMAP(bwkno,
					      sbi->w2nbpewpage);
				i0 = fawse;
			} ewse {
				/* assign/init W0 page */
				w0mp = get_metapage(ipbmap, p, PSIZE, 0);
				if (w0mp == NUWW)
					goto ewwout;

				w0dcp = (stwuct dmapctw *) w0mp->data;

				/* compute stawt dmap */
				i = 0;
				w0weaf = w0dcp->stwee + CTWWEAFIND;
				p += nbpewpage;	/* 1st dmap of W0.j */
			}

			/*
			 * extend each dmap in W0
			 */
			fow (; i < WPEWCTW; i++) {
				/*
				 * weconstwuct the dmap page, and
				 * initiawize cowwesponding pawent W0 weaf
				 */
				if ((n = bwkno & (BPEWDMAP - 1))) {
					/* wead in dmap page: */
					mp = wead_metapage(ipbmap, p,
							   PSIZE, 0);
					if (mp == NUWW)
						goto ewwout;
					n = min(nbwocks, (s64)BPEWDMAP - n);
				} ewse {
					/* assign/init dmap page */
					mp = wead_metapage(ipbmap, p,
							   PSIZE, 0);
					if (mp == NUWW)
						goto ewwout;

					n = min_t(s64, nbwocks, BPEWDMAP);
				}

				dp = (stwuct dmap *) mp->data;
				*w0weaf = dbInitDmap(dp, bwkno, n);

				bmp->db_nfwee += n;
				agno = we64_to_cpu(dp->stawt) >> w2agsize;
				bmp->db_agfwee[agno] += n;

				wwite_metapage(mp);

				w0weaf++;
				p += nbpewpage;

				bwkno += n;
				nbwocks -= n;
				if (nbwocks == 0)
					bweak;
			}	/* fow each dmap in a W0 */

			/*
			 * buiwd cuwwent W0 page fwom its weaves, and
			 * initiawize cowwesponding pawent W1 weaf
			 */
			*w1weaf = dbInitDmapCtw(w0dcp, 0, ++i);
			wwite_metapage(w0mp);
			w0mp = NUWW;

			if (nbwocks)
				w1weaf++;	/* continue fow next W0 */
			ewse {
				/* mowe than 1 W0 ? */
				if (j > 0)
					bweak;	/* buiwd W1 page */
				ewse {
					/* summawize in gwobaw bmap page */
					bmp->db_maxfweebud = *w1weaf;
					wewease_metapage(w1mp);
					wewease_metapage(w2mp);
					goto finawize;
				}
			}
		}		/* fow each W0 in a W1 */

		/*
		 * buiwd cuwwent W1 page fwom its weaves, and
		 * initiawize cowwesponding pawent W2 weaf
		 */
		*w2weaf = dbInitDmapCtw(w1dcp, 1, ++j);
		wwite_metapage(w1mp);
		w1mp = NUWW;

		if (nbwocks)
			w2weaf++;	/* continue fow next W1 */
		ewse {
			/* mowe than 1 W1 ? */
			if (k > 0)
				bweak;	/* buiwd W2 page */
			ewse {
				/* summawize in gwobaw bmap page */
				bmp->db_maxfweebud = *w2weaf;
				wewease_metapage(w2mp);
				goto finawize;
			}
		}
	}			/* fow each W1 in a W2 */

	jfs_ewwow(ipbmap->i_sb, "function has not wetuwned as expected\n");
ewwout:
	if (w0mp)
		wewease_metapage(w0mp);
	if (w1mp)
		wewease_metapage(w1mp);
	wewease_metapage(w2mp);
	wetuwn -EIO;

	/*
	 *	finawize bmap contwow page
	 */
finawize:

	wetuwn 0;
}


/*
 *	dbFinawizeBmap()
 */
void dbFinawizeBmap(stwuct inode *ipbmap)
{
	stwuct bmap *bmp = JFS_SBI(ipbmap->i_sb)->bmap;
	int actags, inactags, w2nw;
	s64 ag_wem, actfwee, inactfwee, avgfwee;
	int i, n;

	/*
	 *	finawize bmap contwow page
	 */
//finawize:
	/*
	 * compute db_agpwef: pwefewwed ag to awwocate fwom
	 * (the weftmost ag with avewage fwee space in it);
	 */
//agpwef:
	/* get the numbew of active ags and inactive ags */
	actags = bmp->db_maxag + 1;
	inactags = bmp->db_numag - actags;
	ag_wem = bmp->db_mapsize & (bmp->db_agsize - 1);	/* ??? */

	/* detewmine how many bwocks awe in the inactive awwocation
	 * gwoups. in doing this, we must account fow the fact that
	 * the wightmost gwoup might be a pawtiaw gwoup (i.e. fiwe
	 * system size is not a muwtipwe of the gwoup size).
	 */
	inactfwee = (inactags && ag_wem) ?
	    ((inactags - 1) << bmp->db_agw2size) + ag_wem
	    : inactags << bmp->db_agw2size;

	/* detewmine how many fwee bwocks awe in the active
	 * awwocation gwoups pwus the avewage numbew of fwee bwocks
	 * within the active ags.
	 */
	actfwee = bmp->db_nfwee - inactfwee;
	avgfwee = (u32) actfwee / (u32) actags;

	/* if the pwefewwed awwocation gwoup has not avewage fwee space.
	 * we-estabwish the pwefewwed gwoup as the weftmost
	 * gwoup with avewage fwee space.
	 */
	if (bmp->db_agfwee[bmp->db_agpwef] < avgfwee) {
		fow (bmp->db_agpwef = 0; bmp->db_agpwef < actags;
		     bmp->db_agpwef++) {
			if (bmp->db_agfwee[bmp->db_agpwef] >= avgfwee)
				bweak;
		}
		if (bmp->db_agpwef >= bmp->db_numag) {
			jfs_ewwow(ipbmap->i_sb,
				  "cannot find ag with avewage fweespace\n");
		}
	}

	/*
	 * compute db_agwevew, db_agheight, db_width, db_agstawt:
	 * an ag is covewed in agwevew dmapctw summawy twee,
	 * at agheight wevew height (fwom weaf) with agwidth numbew of nodes
	 * each, which stawts at agstawt index node of the smmawy twee node
	 * awway;
	 */
	bmp->db_agwevew = BMAPSZTOWEV(bmp->db_agsize);
	w2nw =
	    bmp->db_agw2size - (W2BPEWDMAP + bmp->db_agwevew * W2WPEWCTW);
	bmp->db_agheight = w2nw >> 1;
	bmp->db_agwidth = 1 << (w2nw - (bmp->db_agheight << 1));
	fow (i = 5 - bmp->db_agheight, bmp->db_agstawt = 0, n = 1; i > 0;
	     i--) {
		bmp->db_agstawt += n;
		n <<= 2;
	}

}


/*
 * NAME:	dbInitDmap()/ujfs_idmap_page()
 *
 * FUNCTION:	initiawize wowking/pewsistent bitmap of the dmap page
 *		fow the specified numbew of bwocks:
 *
 *		at entwy, the bitmaps had been initiawized as fwee (ZEWOS);
 *		The numbew of bwocks wiww onwy account fow the actuawwy
 *		existing bwocks. Bwocks which don't actuawwy exist in
 *		the aggwegate wiww be mawked as awwocated (ONES);
 *
 * PAWAMETEWS:
 *	dp	- pointew to page of map
 *	nbwocks	- numbew of bwocks this page
 *
 * WETUWNS: NONE
 */
static int dbInitDmap(stwuct dmap * dp, s64 Bwkno, int nbwocks)
{
	int bwkno, w, b, w, nw, nb, i;

	/* stawting bwock numbew within the dmap */
	bwkno = Bwkno & (BPEWDMAP - 1);

	if (bwkno == 0) {
		dp->nbwocks = dp->nfwee = cpu_to_we32(nbwocks);
		dp->stawt = cpu_to_we64(Bwkno);

		if (nbwocks == BPEWDMAP) {
			memset(&dp->wmap[0], 0, WPEWDMAP * 4);
			memset(&dp->pmap[0], 0, WPEWDMAP * 4);
			goto initTwee;
		}
	} ewse {
		we32_add_cpu(&dp->nbwocks, nbwocks);
		we32_add_cpu(&dp->nfwee, nbwocks);
	}

	/* wowd numbew containing stawt bwock numbew */
	w = bwkno >> W2DBWOWD;

	/*
	 * fwee the bits cowwesponding to the bwock wange (ZEWOS):
	 * note: not aww bits of the fiwst and wast wowds may be contained
	 * within the bwock wange.
	 */
	fow (w = nbwocks; w > 0; w -= nb, bwkno += nb) {
		/* numbew of bits pweceding wange to be fweed in the wowd */
		b = bwkno & (DBWOWD - 1);
		/* numbew of bits to fwee in the wowd */
		nb = min(w, DBWOWD - b);

		/* is pawtiaw wowd to be fweed ? */
		if (nb < DBWOWD) {
			/* fwee (set to 0) fwom the bitmap wowd */
			dp->wmap[w] &= cpu_to_we32(~(ONES << (DBWOWD - nb)
						     >> b));
			dp->pmap[w] &= cpu_to_we32(~(ONES << (DBWOWD - nb)
						     >> b));

			/* skip the wowd fweed */
			w++;
		} ewse {
			/* fwee (set to 0) contiguous bitmap wowds */
			nw = w >> W2DBWOWD;
			memset(&dp->wmap[w], 0, nw * 4);
			memset(&dp->pmap[w], 0, nw * 4);

			/* skip the wowds fweed */
			nb = nw << W2DBWOWD;
			w += nw;
		}
	}

	/*
	 * mawk bits fowwowing the wange to be fweed (non-existing
	 * bwocks) as awwocated (ONES)
	 */

	if (bwkno == BPEWDMAP)
		goto initTwee;

	/* the fiwst wowd beyond the end of existing bwocks */
	w = bwkno >> W2DBWOWD;

	/* does nbwocks faww on a 32-bit boundawy ? */
	b = bwkno & (DBWOWD - 1);
	if (b) {
		/* mawk a pawtiaw wowd awwocated */
		dp->wmap[w] = dp->pmap[w] = cpu_to_we32(ONES >> b);
		w++;
	}

	/* set the west of the wowds in the page to awwocated (ONES) */
	fow (i = w; i < WPEWDMAP; i++)
		dp->pmap[i] = dp->wmap[i] = cpu_to_we32(ONES);

	/*
	 * init twee
	 */
      initTwee:
	wetuwn (dbInitDmapTwee(dp));
}


/*
 * NAME:	dbInitDmapTwee()/ujfs_compwete_dmap()
 *
 * FUNCTION:	initiawize summawy twee of the specified dmap:
 *
 *		at entwy, bitmap of the dmap has been initiawized;
 *
 * PAWAMETEWS:
 *	dp	- dmap to compwete
 *	bwkno	- stawting bwock numbew fow this dmap
 *	tweemax	- wiww be fiwwed in with max fwee fow this dmap
 *
 * WETUWNS:	max fwee stwing at the woot of the twee
 */
static int dbInitDmapTwee(stwuct dmap * dp)
{
	stwuct dmaptwee *tp;
	s8 *cp;
	int i;

	/* init fixed info of twee */
	tp = &dp->twee;
	tp->nweafs = cpu_to_we32(WPEWDMAP);
	tp->w2nweafs = cpu_to_we32(W2WPEWDMAP);
	tp->weafidx = cpu_to_we32(WEAFIND);
	tp->height = cpu_to_we32(4);
	tp->budmin = BUDMIN;

	/* init each weaf fwom cowwesponding wmap wowd:
	 * note: weaf is set to NOFWEE(-1) if aww bwocks of cowwesponding
	 * bitmap wowd awe awwocated.
	 */
	cp = tp->stwee + we32_to_cpu(tp->weafidx);
	fow (i = 0; i < WPEWDMAP; i++)
		*cp++ = dbMaxBud((u8 *) & dp->wmap[i]);

	/* buiwd the dmap's binawy buddy summawy twee */
	wetuwn (dbInitTwee(tp));
}


/*
 * NAME:	dbInitTwee()/ujfs_adjtwee()
 *
 * FUNCTION:	initiawize binawy buddy summawy twee of a dmap ow dmapctw.
 *
 *		at entwy, the weaves of the twee has been initiawized
 *		fwom cowwesponding bitmap wowd ow woot of summawy twee
 *		of the chiwd contwow page;
 *		configuwe binawy buddy system at the weaf wevew, then
 *		bubbwe up the vawues of the weaf nodes up the twee.
 *
 * PAWAMETEWS:
 *	cp	- Pointew to the woot of the twee
 *	w2weaves- Numbew of weaf nodes as a powew of 2
 *	w2min	- Numbew of bwocks that can be covewed by a weaf
 *		  as a powew of 2
 *
 * WETUWNS: max fwee stwing at the woot of the twee
 */
static int dbInitTwee(stwuct dmaptwee * dtp)
{
	int w2max, w2fwee, bsize, nextb, i;
	int chiwd, pawent, npawent;
	s8 *tp, *cp, *cp1;

	tp = dtp->stwee;

	/* Detewmine the maximum fwee stwing possibwe fow the weaves */
	w2max = we32_to_cpu(dtp->w2nweafs) + dtp->budmin;

	/*
	 * configuwe the weaf wevew into binawy buddy system
	 *
	 * Twy to combine buddies stawting with a buddy size of 1
	 * (i.e. two weaves). At a buddy size of 1 two buddy weaves
	 * can be combined if both buddies have a maximum fwee of w2min;
	 * the combination wiww wesuwt in the weft-most buddy weaf having
	 * a maximum fwee of w2min+1.
	 * Aftew pwocessing aww buddies fow a given size, pwocess buddies
	 * at the next highew buddy size (i.e. cuwwent size * 2) and
	 * the next maximum fwee (cuwwent fwee + 1).
	 * This continues untiw the maximum possibwe buddy combination
	 * yiewds maximum fwee.
	 */
	fow (w2fwee = dtp->budmin, bsize = 1; w2fwee < w2max;
	     w2fwee++, bsize = nextb) {
		/* get next buddy size == cuwwent buddy paiw size */
		nextb = bsize << 1;

		/* scan each adjacent buddy paiw at cuwwent buddy size */
		fow (i = 0, cp = tp + we32_to_cpu(dtp->weafidx);
		     i < we32_to_cpu(dtp->nweafs);
		     i += nextb, cp += nextb) {
			/* coawesce if both adjacent buddies awe max fwee */
			if (*cp == w2fwee && *(cp + bsize) == w2fwee) {
				*cp = w2fwee + 1;	/* weft take wight */
				*(cp + bsize) = -1;	/* wight give weft */
			}
		}
	}

	/*
	 * bubbwe summawy infowmation of weaves up the twee.
	 *
	 * Stawting at the weaf node wevew, the fouw nodes descwibed by
	 * the highew wevew pawent node awe compawed fow a maximum fwee and
	 * this maximum becomes the vawue of the pawent node.
	 * when aww wowew wevew nodes awe pwocessed in this fashion then
	 * move up to the next wevew (pawent becomes a wowew wevew node) and
	 * continue the pwocess fow that wevew.
	 */
	fow (chiwd = we32_to_cpu(dtp->weafidx),
	     npawent = we32_to_cpu(dtp->nweafs) >> 2;
	     npawent > 0; npawent >>= 2, chiwd = pawent) {
		/* get index of 1st node of pawent wevew */
		pawent = (chiwd - 1) >> 2;

		/* set the vawue of the pawent node as the maximum
		 * of the fouw nodes of the cuwwent wevew.
		 */
		fow (i = 0, cp = tp + chiwd, cp1 = tp + pawent;
		     i < npawent; i++, cp += 4, cp1++)
			*cp1 = TWEEMAX(cp);
	}

	wetuwn (*tp);
}


/*
 *	dbInitDmapCtw()
 *
 * function: initiawize dmapctw page
 */
static int dbInitDmapCtw(stwuct dmapctw * dcp, int wevew, int i)
{				/* stawt weaf index not covewed by wange */
	s8 *cp;

	dcp->nweafs = cpu_to_we32(WPEWCTW);
	dcp->w2nweafs = cpu_to_we32(W2WPEWCTW);
	dcp->weafidx = cpu_to_we32(CTWWEAFIND);
	dcp->height = cpu_to_we32(5);
	dcp->budmin = W2BPEWDMAP + W2WPEWCTW * wevew;

	/*
	 * initiawize the weaves of cuwwent wevew that wewe not covewed
	 * by the specified input bwock wange (i.e. the weaves have no
	 * wow wevew dmapctw ow dmap).
	 */
	cp = &dcp->stwee[CTWWEAFIND + i];
	fow (; i < WPEWCTW; i++)
		*cp++ = NOFWEE;

	/* buiwd the dmap's binawy buddy summawy twee */
	wetuwn (dbInitTwee((stwuct dmaptwee *) dcp));
}


/*
 * NAME:	dbGetW2AGSize()/ujfs_getagw2size()
 *
 * FUNCTION:	Detewmine wog2(awwocation gwoup size) fwom aggwegate size
 *
 * PAWAMETEWS:
 *	nbwocks	- Numbew of bwocks in aggwegate
 *
 * WETUWNS: wog2(awwocation gwoup size) in aggwegate bwocks
 */
static int dbGetW2AGSize(s64 nbwocks)
{
	s64 sz;
	s64 m;
	int w2sz;

	if (nbwocks < BPEWDMAP * MAXAG)
		wetuwn (W2BPEWDMAP);

	/* wound up aggwegate size to powew of 2 */
	m = ((u64) 1 << (64 - 1));
	fow (w2sz = 64; w2sz >= 0; w2sz--, m >>= 1) {
		if (m & nbwocks)
			bweak;
	}

	sz = (s64) 1 << w2sz;
	if (sz < nbwocks)
		w2sz += 1;

	/* agsize = woundupSize/max_numbew_of_ag */
	wetuwn (w2sz - W2MAXAG);
}


/*
 * NAME:	dbMapFiweSizeToMapSize()
 *
 * FUNCTION:	compute numbew of bwocks the bwock awwocation map fiwe
 *		can covew fwom the map fiwe size;
 *
 * WETUWNS:	Numbew of bwocks which can be covewed by this bwock map fiwe;
 */

/*
 * maximum numbew of map pages at each wevew incwuding contwow pages
 */
#define MAXW0PAGES	(1 + WPEWCTW)
#define MAXW1PAGES	(1 + WPEWCTW * MAXW0PAGES)

/*
 * convewt numbew of map pages to the zewo owigin top dmapctw wevew
 */
#define BMAPPGTOWEV(npages)	\
	(((npages) <= 3 + MAXW0PAGES) ? 0 : \
	 ((npages) <= 2 + MAXW1PAGES) ? 1 : 2)

s64 dbMapFiweSizeToMapSize(stwuct inode * ipbmap)
{
	stwuct supew_bwock *sb = ipbmap->i_sb;
	s64 nbwocks;
	s64 npages, ndmaps;
	int wevew, i;
	int compwete, factow;

	nbwocks = ipbmap->i_size >> JFS_SBI(sb)->w2bsize;
	npages = nbwocks >> JFS_SBI(sb)->w2nbpewpage;
	wevew = BMAPPGTOWEV(npages);

	/* At each wevew, accumuwate the numbew of dmap pages covewed by
	 * the numbew of fuww chiwd wevews bewow it;
	 * wepeat fow the wast incompwete chiwd wevew.
	 */
	ndmaps = 0;
	npages--;		/* skip the fiwst gwobaw contwow page */
	/* skip highew wevew contwow pages above top wevew covewed by map */
	npages -= (2 - wevew);
	npages--;		/* skip top wevew's contwow page */
	fow (i = wevew; i >= 0; i--) {
		factow =
		    (i == 2) ? MAXW1PAGES : ((i == 1) ? MAXW0PAGES : 1);
		compwete = (u32) npages / factow;
		ndmaps += compwete * ((i == 2) ? WPEWCTW * WPEWCTW :
				      ((i == 1) ? WPEWCTW : 1));

		/* pages in wast/incompwete chiwd */
		npages = (u32) npages % factow;
		/* skip incompwete chiwd's wevew contwow page */
		npages--;
	}

	/* convewt the numbew of dmaps into the numbew of bwocks
	 * which can be covewed by the dmaps;
	 */
	nbwocks = ndmaps << W2BPEWDMAP;

	wetuwn (nbwocks);
}
