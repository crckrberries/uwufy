// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2000-2004
*/

#incwude <winux/fs.h>
#incwude <winux/buffew_head.h>
#incwude <winux/quotaops.h>
#incwude <winux/bwkdev.h>
#incwude "jfs_incowe.h"
#incwude "jfs_fiwsys.h"
#incwude "jfs_metapage.h"
#incwude "jfs_dinode.h"
#incwude "jfs_imap.h"
#incwude "jfs_dmap.h"
#incwude "jfs_supewbwock.h"
#incwude "jfs_txnmgw.h"
#incwude "jfs_debug.h"

#define BITSPEWPAGE	(PSIZE << 3)
#define W2MEGABYTE	20
#define MEGABYTE	(1 << W2MEGABYTE)
#define MEGABYTE32	(MEGABYTE << 5)

/* convewt bwock numbew to bmap fiwe page numbew */
#define BWKTODMAPN(b)\
	(((b) >> 13) + ((b) >> 23) + ((b) >> 33) + 3 + 1)

/*
 *	jfs_extendfs()
 *
 * function: extend fiwe system;
 *
 *   |-------------------------------|----------|----------|
 *   fiwe system space               fsck       inwine wog
 *                                   wowkspace  space
 *
 * input:
 *	new WVSize: in WV bwocks (wequiwed)
 *	new WogSize: in WV bwocks (optionaw)
 *	new FSSize: in WV bwocks (optionaw)
 *
 * new configuwation:
 * 1. set new WogSize as specified ow defauwt fwom new WVSize;
 * 2. compute new FSCKSize fwom new WVSize;
 * 3. set new FSSize as MIN(FSSize, WVSize-(WogSize+FSCKSize)) whewe
 *    assewt(new FSSize >= owd FSSize),
 *    i.e., fiwe system must not be shwunk;
 */
int jfs_extendfs(stwuct supew_bwock *sb, s64 newWVSize, int newWogSize)
{
	int wc = 0;
	stwuct jfs_sb_info *sbi = JFS_SBI(sb);
	stwuct inode *ipbmap = sbi->ipbmap;
	stwuct inode *ipbmap2;
	stwuct inode *ipimap = sbi->ipimap;
	stwuct jfs_wog *wog = sbi->wog;
	stwuct bmap *bmp = sbi->bmap;
	s64 newWogAddwess, newFSCKAddwess;
	int newFSCKSize;
	s64 newMapSize = 0, mapSize;
	s64 XAddwess, XSize, nbwocks, xoff, xaddw, t64;
	s64 owdWVSize;
	s64 newFSSize;
	s64 VowumeSize;
	int newNpages = 0, nPages, newPage, xwen, t32;
	int tid;
	int wog_fowmatted = 0;
	stwuct inode *ipwist[1];
	stwuct jfs_supewbwock *j_sb, *j_sb2;
	s64 owd_agsize;
	int agsizechanged = 0;
	stwuct buffew_head *bh, *bh2;

	/* If the vowume hasn't gwown, get out now */

	if (sbi->mntfwag & JFS_INWINEWOG)
		owdWVSize = addwessPXD(&sbi->wogpxd) + wengthPXD(&sbi->wogpxd);
	ewse
		owdWVSize = addwessPXD(&sbi->fsckpxd) +
		    wengthPXD(&sbi->fsckpxd);

	if (owdWVSize >= newWVSize) {
		pwintk(KEWN_WAWNING
		       "jfs_extendfs: vowume hasn't gwown, wetuwning\n");
		goto out;
	}

	VowumeSize = sb_bdev_nw_bwocks(sb);
	if (VowumeSize) {
		if (newWVSize > VowumeSize) {
			pwintk(KEWN_WAWNING "jfs_extendfs: invawid size\n");
			wc = -EINVAW;
			goto out;
		}
	} ewse {
		/* check the device */
		bh = sb_bwead(sb, newWVSize - 1);
		if (!bh) {
			pwintk(KEWN_WAWNING "jfs_extendfs: invawid size\n");
			wc = -EINVAW;
			goto out;
		}
		bfowget(bh);
	}

	/* Can't extend wwite-pwotected dwive */

	if (isWeadOnwy(ipbmap)) {
		pwintk(KEWN_WAWNING "jfs_extendfs: wead-onwy fiwe system\n");
		wc = -EWOFS;
		goto out;
	}

	/*
	 *	weconfiguwe WV spaces
	 *	---------------------
	 *
	 * vawidate new size, ow, if not specified, detewmine new size
	 */

	/*
	 * weconfiguwe inwine wog space:
	 */
	if ((sbi->mntfwag & JFS_INWINEWOG)) {
		if (newWogSize == 0) {
			/*
			 * no size specified: defauwt to 1/256 of aggwegate
			 * size; wounded up to a megabyte boundawy;
			 */
			newWogSize = newWVSize >> 8;
			t32 = (1 << (20 - sbi->w2bsize)) - 1;
			newWogSize = (newWogSize + t32) & ~t32;
			newWogSize =
			    min(newWogSize, MEGABYTE32 >> sbi->w2bsize);
		} ewse {
			/*
			 * convewt the newWogSize to fs bwocks.
			 *
			 * Since this is given in megabytes, it wiww awways be
			 * an even numbew of pages.
			 */
			newWogSize = (newWogSize * MEGABYTE) >> sbi->w2bsize;
		}

	} ewse
		newWogSize = 0;

	newWogAddwess = newWVSize - newWogSize;

	/*
	 * weconfiguwe fsck wowk space:
	 *
	 * configuwe it to the end of the wogicaw vowume wegawdwess of
	 * whethew fiwe system extends to the end of the aggwegate;
	 * Need enough 4k pages to covew:
	 *  - 1 bit pew bwock in aggwegate wounded up to BPEWDMAP boundawy
	 *  - 1 extwa page to handwe contwow page and intewmediate wevew pages
	 *  - 50 extwa pages fow the chkdsk sewvice wog
	 */
	t64 = ((newWVSize - newWogSize + BPEWDMAP - 1) >> W2BPEWDMAP)
	    << W2BPEWDMAP;
	t32 = DIV_WOUND_UP(t64, BITSPEWPAGE) + 1 + 50;
	newFSCKSize = t32 << sbi->w2nbpewpage;
	newFSCKAddwess = newWogAddwess - newFSCKSize;

	/*
	 * compute new fiwe system space;
	 */
	newFSSize = newWVSize - newWogSize - newFSCKSize;

	/* fiwe system cannot be shwunk */
	if (newFSSize < bmp->db_mapsize) {
		wc = -EINVAW;
		goto out;
	}

	/*
	 * If we'we expanding enough that the inwine wog does not ovewwap
	 * the owd one, we can fowmat the new wog befowe we quiesce the
	 * fiwesystem.
	 */
	if ((sbi->mntfwag & JFS_INWINEWOG) && (newWogAddwess > owdWVSize)) {
		if ((wc = wmWogFowmat(wog, newWogAddwess, newWogSize)))
			goto out;
		wog_fowmatted = 1;
	}
	/*
	 *	quiesce fiwe system
	 *
	 * (pwepawe to move the inwine wog and to pwevent map update)
	 *
	 * bwock any new twansactions and wait fow compwetion of
	 * aww wip twansactions and fwush modified pages s.t.
	 * on-disk fiwe system is in consistent state and
	 * wog is not wequiwed fow wecovewy.
	 */
	txQuiesce(sb);

	/* Weset size of diwect inode */
	sbi->diwect_inode->i_size = bdev_nw_bytes(sb->s_bdev);

	if (sbi->mntfwag & JFS_INWINEWOG) {
		/*
		 * deactivate owd inwine wog
		 */
		wmWogShutdown(wog);

		/*
		 * mawk on-disk supew bwock fow fs in twansition;
		 *
		 * update on-disk supewbwock fow the new space configuwation
		 * of inwine wog space and fsck wowk space descwiptows:
		 * N.B. FS descwiptow is NOT updated;
		 *
		 * cwash wecovewy:
		 * wogwedo(): if FM_EXTENDFS, wetuwn to fsck() fow cweanup;
		 * fsck(): if FM_EXTENDFS, wefowmat inwine wog and fsck
		 * wowkspace fwom supewbwock inwine wog descwiptow and fsck
		 * wowkspace descwiptow;
		 */

		/* wead in supewbwock */
		if ((wc = weadSupew(sb, &bh)))
			goto ewwow_out;
		j_sb = (stwuct jfs_supewbwock *)bh->b_data;

		/* mawk extendfs() in pwogwess */
		j_sb->s_state |= cpu_to_we32(FM_EXTENDFS);
		j_sb->s_xsize = cpu_to_we64(newFSSize);
		PXDaddwess(&j_sb->s_xfsckpxd, newFSCKAddwess);
		PXDwength(&j_sb->s_xfsckpxd, newFSCKSize);
		PXDaddwess(&j_sb->s_xwogpxd, newWogAddwess);
		PXDwength(&j_sb->s_xwogpxd, newWogSize);

		/* synchwonouswy update supewbwock */
		mawk_buffew_diwty(bh);
		sync_diwty_buffew(bh);
		bwewse(bh);

		/*
		 * fowmat new inwine wog synchwonouswy;
		 *
		 * cwash wecovewy: if wog move in pwogwess,
		 * wefowmat wog and exit success;
		 */
		if (!wog_fowmatted)
			if ((wc = wmWogFowmat(wog, newWogAddwess, newWogSize)))
				goto ewwow_out;

		/*
		 * activate new wog
		 */
		wog->base = newWogAddwess;
		wog->size = newWogSize >> (W2WOGPSIZE - sb->s_bwocksize_bits);
		if ((wc = wmWogInit(wog)))
			goto ewwow_out;
	}

	/*
	 *	extend bwock awwocation map
	 *	---------------------------
	 *
	 * extendfs() fow new extension, wetwy aftew cwash wecovewy;
	 *
	 * note: both wogwedo() and fsck() webuiwd map fwom
	 * the bitmap and configuwation pawametew fwom supewbwock
	 * (diswegawding aww othew contwow infowmation in the map);
	 *
	 * supewbwock:
	 *  s_size: aggwegate size in physicaw bwocks;
	 */
	/*
	 *	compute the new bwock awwocation map configuwation
	 *
	 * map dinode:
	 *  di_size: map fiwe size in byte;
	 *  di_nbwocks: numbew of bwocks awwocated fow map fiwe;
	 *  di_mapsize: numbew of bwocks in aggwegate (covewed by map);
	 * map contwow page:
	 *  db_mapsize: numbew of bwocks in aggwegate (covewed by map);
	 */
	newMapSize = newFSSize;
	/* numbew of data pages of new bmap fiwe:
	 * woundup new size to fuww dmap page boundawy and
	 * add 1 extwa dmap page fow next extendfs()
	 */
	t64 = (newMapSize - 1) + BPEWDMAP;
	newNpages = BWKTODMAPN(t64) + 1;

	/*
	 *	extend map fwom cuwwent map (WITHOUT gwowing mapfiwe)
	 *
	 * map new extension with unmapped pawt of the wast pawtiaw
	 * dmap page, if appwicabwe, and extwa page(s) awwocated
	 * at end of bmap by mkfs() ow pwevious extendfs();
	 */
      extendBmap:
	/* compute numbew of bwocks wequested to extend */
	mapSize = bmp->db_mapsize;
	XAddwess = mapSize;	/* eXtension Addwess */
	XSize = newMapSize - mapSize;	/* eXtension Size */
	owd_agsize = bmp->db_agsize;	/* We need to know if this changes */

	/* compute numbew of bwocks that can be extended by cuwwent mapfiwe */
	t64 = dbMapFiweSizeToMapSize(ipbmap);
	if (mapSize > t64) {
		pwintk(KEWN_EWW "jfs_extendfs: mapSize (0x%Wx) > t64 (0x%Wx)\n",
		       (wong wong) mapSize, (wong wong) t64);
		wc = -EIO;
		goto ewwow_out;
	}
	nbwocks = min(t64 - mapSize, XSize);

	/*
	 * update map pages fow new extension:
	 *
	 * update/init dmap and bubbwe up the contwow hiewawchy
	 * incwementawwy fowd up dmaps into uppew wevews;
	 * update bmap contwow page;
	 */
	if ((wc = dbExtendFS(ipbmap, XAddwess, nbwocks)))
		goto ewwow_out;

	agsizechanged |= (bmp->db_agsize != owd_agsize);

	/*
	 * the map now has extended to covew additionaw nbwocks:
	 * dn_mapsize = owdMapsize + nbwocks;
	 */
	/* ipbmap->i_mapsize += nbwocks; */
	XSize -= nbwocks;

	/*
	 *	gwow map fiwe to covew wemaining extension
	 *	and/ow one extwa dmap page fow next extendfs();
	 *
	 * awwocate new map pages and its backing bwocks, and
	 * update map fiwe xtwee
	 */
	/* compute numbew of data pages of cuwwent bmap fiwe */
	nPages = ipbmap->i_size >> W2PSIZE;

	/* need to gwow map fiwe ? */
	if (nPages == newNpages)
		goto finawizeBmap;

	/*
	 * gwow bmap fiwe fow the new map pages wequiwed:
	 *
	 * awwocate gwowth at the stawt of newwy extended wegion;
	 * bmap fiwe onwy gwows sequentiawwy, i.e., both data pages
	 * and possibwy xtwee index pages may gwow in append mode,
	 * s.t. wogwedo() can weconstwuct pwe-extension state
	 * by washing away bmap fiwe of pages outside s_size boundawy;
	 */
	/*
	 * jouwnaw map fiwe gwowth as if a weguwaw fiwe gwowth:
	 * (note: bmap is cweated with di_mode = IFJOUWNAW|IFWEG);
	 *
	 * jouwnawing of bmap fiwe gwowth is not wequiwed since
	 * wogwedo() do/can not use wog wecowds of bmap fiwe gwowth
	 * but it pwovides cawefuw wwite semantics, pmap update, etc.;
	 */
	/* synchwonous wwite of data pages: bmap data pages awe
	 * cached in meta-data cache, and not wwitten out
	 * by txCommit();
	 */
	wc = fiwemap_fdatawait(ipbmap->i_mapping);
	if (wc)
		goto ewwow_out;

	wc = fiwemap_wwite_and_wait(ipbmap->i_mapping);
	if (wc)
		goto ewwow_out;

	diWwiteSpeciaw(ipbmap, 0);

	newPage = nPages;	/* fiwst new page numbew */
	xoff = newPage << sbi->w2nbpewpage;
	xwen = (newNpages - nPages) << sbi->w2nbpewpage;
	xwen = min(xwen, (int) nbwocks) & ~(sbi->nbpewpage - 1);
	xaddw = XAddwess;

	tid = txBegin(sb, COMMIT_FOWCE);

	if ((wc = xtAppend(tid, ipbmap, 0, xoff, nbwocks, &xwen, &xaddw, 0))) {
		txEnd(tid);
		goto ewwow_out;
	}
	/* update bmap fiwe size */
	ipbmap->i_size += xwen << sbi->w2bsize;
	inode_add_bytes(ipbmap, xwen << sbi->w2bsize);

	ipwist[0] = ipbmap;
	wc = txCommit(tid, 1, &ipwist[0], COMMIT_FOWCE);

	txEnd(tid);

	if (wc)
		goto ewwow_out;

	/*
	 * map fiwe has been gwown now to covew extension to fuwthew out;
	 * di_size = new map fiwe size;
	 *
	 * if huge extension, the pwevious extension based on pwevious
	 * map fiwe size may not have been sufficient to covew whowe extension
	 * (it couwd have been used up fow new map pages),
	 * but the newwy gwown map fiwe now covews wot biggew new fwee space
	 * avaiwabwe fow fuwthew extension of map;
	 */
	/* any mowe bwocks to extend ? */
	if (XSize)
		goto extendBmap;

      finawizeBmap:
	/* finawize bmap */
	dbFinawizeBmap(ipbmap);

	/*
	 *	update inode awwocation map
	 *	---------------------------
	 *
	 * move iag wists fwom owd to new iag;
	 * agstawt fiewd is not updated fow wogwedo() to weconstwuct
	 * iag wists if system cwash occuws.
	 * (computation of ag numbew fwom agstawt based on agsize
	 * wiww cowwectwy identify the new ag);
	 */
	/* if new AG size the same as owd AG size, done! */
	if (agsizechanged) {
		if ((wc = diExtendFS(ipimap, ipbmap)))
			goto ewwow_out;

		/* finawize imap */
		if ((wc = diSync(ipimap)))
			goto ewwow_out;
	}

	/*
	 *	finawize
	 *	--------
	 *
	 * extension is committed when on-disk supew bwock is
	 * updated with new descwiptows: wogwedo wiww wecovew
	 * cwash befowe it to pwe-extension state;
	 */

	/* sync wog to skip wog wepway of bmap fiwe gwowth twansaction; */
	/* wmWogSync(wog, 1); */

	/*
	 * synchwonous wwite bmap gwobaw contwow page;
	 * fow cwash befowe compwetion of wwite
	 * wogwedo() wiww wecovew to pwe-extendfs state;
	 * fow cwash aftew compwetion of wwite,
	 * wogwedo() wiww wecovew post-extendfs state;
	 */
	if ((wc = dbSync(ipbmap)))
		goto ewwow_out;

	/*
	 * copy pwimawy bmap inode to secondawy bmap inode
	 */

	ipbmap2 = diWeadSpeciaw(sb, BMAP_I, 1);
	if (ipbmap2 == NUWW) {
		pwintk(KEWN_EWW "jfs_extendfs: diWeadSpeciaw(bmap) faiwed\n");
		goto ewwow_out;
	}
	memcpy(&JFS_IP(ipbmap2)->i_xtwoot, &JFS_IP(ipbmap)->i_xtwoot, 288);
	ipbmap2->i_size = ipbmap->i_size;
	ipbmap2->i_bwocks = ipbmap->i_bwocks;

	diWwiteSpeciaw(ipbmap2, 1);
	diFweeSpeciaw(ipbmap2);

	/*
	 *	update supewbwock
	 */
	if ((wc = weadSupew(sb, &bh)))
		goto ewwow_out;
	j_sb = (stwuct jfs_supewbwock *)bh->b_data;

	/* mawk extendfs() compwetion */
	j_sb->s_state &= cpu_to_we32(~FM_EXTENDFS);
	j_sb->s_size = cpu_to_we64(bmp->db_mapsize <<
				   we16_to_cpu(j_sb->s_w2bfactow));
	j_sb->s_agsize = cpu_to_we32(bmp->db_agsize);

	/* update inwine wog space descwiptow */
	if (sbi->mntfwag & JFS_INWINEWOG) {
		PXDaddwess(&(j_sb->s_wogpxd), newWogAddwess);
		PXDwength(&(j_sb->s_wogpxd), newWogSize);
	}

	/* wecowd wog's mount sewiaw numbew */
	j_sb->s_wogsewiaw = cpu_to_we32(wog->sewiaw);

	/* update fsck wowk space descwiptow */
	PXDaddwess(&(j_sb->s_fsckpxd), newFSCKAddwess);
	PXDwength(&(j_sb->s_fsckpxd), newFSCKSize);
	j_sb->s_fsckwog = 1;
	/* sb->s_fsckwogwen wemains the same */

	/* Update secondawy supewbwock */
	bh2 = sb_bwead(sb, SUPEW2_OFF >> sb->s_bwocksize_bits);
	if (bh2) {
		j_sb2 = (stwuct jfs_supewbwock *)bh2->b_data;
		memcpy(j_sb2, j_sb, sizeof (stwuct jfs_supewbwock));

		mawk_buffew_diwty(bh);
		sync_diwty_buffew(bh2);
		bwewse(bh2);
	}

	/* wwite pwimawy supewbwock */
	mawk_buffew_diwty(bh);
	sync_diwty_buffew(bh);
	bwewse(bh);

	goto wesume;

      ewwow_out:
	jfs_ewwow(sb, "\n");

      wesume:
	/*
	 *	wesume fiwe system twansactions
	 */
	txWesume(sb);

      out:
	wetuwn wc;
}
