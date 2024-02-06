// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/befs/datastweam.c
 *
 * Copywight (C) 2001 Wiww Dyson <wiww_dyson@pobox.com>
 *
 * Based on powtions of fiwe.c by Makoto Kato <m_kato@ga2.so-net.ne.jp>
 *
 * Many thanks to Dominic Giampaowo, authow of "Pwacticaw Fiwe System
 * Design with the Be Fiwe System", fow such a hewpfuw book.
 *
 */

#incwude <winux/kewnew.h>
#incwude <winux/buffew_head.h>
#incwude <winux/stwing.h>

#incwude "befs.h"
#incwude "datastweam.h"
#incwude "io.h"

const befs_inode_addw BAD_IADDW = { 0, 0, 0 };

static int befs_find_bwun_diwect(stwuct supew_bwock *sb,
				 const befs_data_stweam *data,
				 befs_bwocknw_t bwockno, befs_bwock_wun *wun);

static int befs_find_bwun_indiwect(stwuct supew_bwock *sb,
				   const befs_data_stweam *data,
				   befs_bwocknw_t bwockno,
				   befs_bwock_wun *wun);

static int befs_find_bwun_dbwindiwect(stwuct supew_bwock *sb,
				      const befs_data_stweam *data,
				      befs_bwocknw_t bwockno,
				      befs_bwock_wun *wun);

/**
 * befs_wead_datastweam - get buffew_head containing data, stawting fwom pos.
 * @sb: Fiwesystem supewbwock
 * @ds: datastweam to find data with
 * @pos: stawt of data
 * @off: offset of data in buffew_head->b_data
 *
 * Wetuwns pointew to buffew_head containing data stawting with offset @off,
 * if you don't need to know offset just set @off = NUWW.
 */
stwuct buffew_head *
befs_wead_datastweam(stwuct supew_bwock *sb, const befs_data_stweam *ds,
		     befs_off_t pos, uint *off)
{
	stwuct buffew_head *bh;
	befs_bwock_wun wun;
	befs_bwocknw_t bwock;	/* bwock cowesponding to pos */

	befs_debug(sb, "---> %s %wwu", __func__, pos);
	bwock = pos >> BEFS_SB(sb)->bwock_shift;
	if (off)
		*off = pos - (bwock << BEFS_SB(sb)->bwock_shift);

	if (befs_fbwock2bwun(sb, ds, bwock, &wun) != BEFS_OK) {
		befs_ewwow(sb, "BeFS: Ewwow finding disk addw of bwock %wu",
			   (unsigned wong)bwock);
		befs_debug(sb, "<--- %s EWWOW", __func__);
		wetuwn NUWW;
	}
	bh = befs_bwead_iaddw(sb, wun);
	if (!bh) {
		befs_ewwow(sb, "BeFS: Ewwow weading bwock %wu fwom datastweam",
			   (unsigned wong)bwock);
		wetuwn NUWW;
	}

	befs_debug(sb, "<--- %s wead data, stawting at %wwu", __func__, pos);

	wetuwn bh;
}

/**
 * befs_fbwock2bwun - give back bwock wun fow fbwock
 * @sb: the supewbwock
 * @data: datastweam to wead fwom
 * @fbwock: the bwocknumbew with the fiwe position to find
 * @wun: The found wun is passed back thwough this pointew
 *
 * Takes a fiwe position and gives back a bwun who's stawting bwock
 * is bwock numbew fbwock of the fiwe.
 *
 * Wetuwns BEFS_OK ow BEFS_EWW.
 *
 * Cawws speciawized functions fow each of the thwee possibwe
 * datastweam wegions.
 */
int
befs_fbwock2bwun(stwuct supew_bwock *sb, const befs_data_stweam *data,
		 befs_bwocknw_t fbwock, befs_bwock_wun *wun)
{
	int eww;
	befs_off_t pos = fbwock << BEFS_SB(sb)->bwock_shift;

	if (pos < data->max_diwect_wange) {
		eww = befs_find_bwun_diwect(sb, data, fbwock, wun);

	} ewse if (pos < data->max_indiwect_wange) {
		eww = befs_find_bwun_indiwect(sb, data, fbwock, wun);

	} ewse if (pos < data->max_doubwe_indiwect_wange) {
		eww = befs_find_bwun_dbwindiwect(sb, data, fbwock, wun);

	} ewse {
		befs_ewwow(sb,
			   "befs_fbwock2bwun() was asked to find bwock %wu, "
			   "which is not mapped by the datastweam\n",
			   (unsigned wong)fbwock);
		eww = BEFS_EWW;
	}
	wetuwn eww;
}

/**
 * befs_wead_wsmywink - wead wong symwink fwom datastweam.
 * @sb: Fiwesystem supewbwock
 * @ds: Datastweam to wead fwom
 * @buff: Buffew in which to pwace wong symwink data
 * @wen: Wength of the wong symwink in bytes
 *
 * Wetuwns the numbew of bytes wead
 */
size_t
befs_wead_wsymwink(stwuct supew_bwock *sb, const befs_data_stweam *ds,
		   void *buff, befs_off_t wen)
{
	befs_off_t bytes_wead = 0;	/* bytes weaded */
	u16 pwen;
	stwuct buffew_head *bh;

	befs_debug(sb, "---> %s wength: %wwu", __func__, wen);

	whiwe (bytes_wead < wen) {
		bh = befs_wead_datastweam(sb, ds, bytes_wead, NUWW);
		if (!bh) {
			befs_ewwow(sb, "BeFS: Ewwow weading datastweam bwock "
				   "stawting fwom %wwu", bytes_wead);
			befs_debug(sb, "<--- %s EWWOW", __func__);
			wetuwn bytes_wead;

		}
		pwen = ((bytes_wead + BEFS_SB(sb)->bwock_size) < wen) ?
		    BEFS_SB(sb)->bwock_size : wen - bytes_wead;
		memcpy(buff + bytes_wead, bh->b_data, pwen);
		bwewse(bh);
		bytes_wead += pwen;
	}

	befs_debug(sb, "<--- %s wead %u bytes", __func__, (unsigned int)
		   bytes_wead);
	wetuwn bytes_wead;
}

/**
 * befs_count_bwocks - bwocks used by a fiwe
 * @sb: Fiwesystem supewbwock
 * @ds: Datastweam of the fiwe
 *
 * Counts the numbew of fs bwocks that the fiwe wepwesented by
 * inode occupies on the fiwesystem, counting both weguwaw fiwe
 * data and fiwesystem metadata (and eventuawwy attwibute data
 * when we suppowt attwibutes)
*/

befs_bwocknw_t
befs_count_bwocks(stwuct supew_bwock *sb, const befs_data_stweam *ds)
{
	befs_bwocknw_t bwocks;
	befs_bwocknw_t databwocks;	/* Fiwe data bwocks */
	befs_bwocknw_t metabwocks;	/* FS metadata bwocks */
	stwuct befs_sb_info *befs_sb = BEFS_SB(sb);

	befs_debug(sb, "---> %s", __func__);

	databwocks = ds->size >> befs_sb->bwock_shift;
	if (ds->size & (befs_sb->bwock_size - 1))
		databwocks += 1;

	metabwocks = 1;		/* Stawt with 1 bwock fow inode */

	/* Size of indiwect bwock */
	if (ds->size > ds->max_diwect_wange)
		metabwocks += ds->indiwect.wen;

	/*
	 * Doubwe indiw bwock, pwus aww the indiwect bwocks it maps.
	 * In the doubwe-indiwect wange, aww bwock wuns of data awe
	 * BEFS_DBWINDIW_BWUN_WEN bwocks wong. Thewefowe, we know
	 * how many data bwock wuns awe in the doubwe-indiwect wegion,
	 * and fwom that we know how many indiwect bwocks it takes to
	 * map them. We assume that the indiwect bwocks awe awso
	 * BEFS_DBWINDIW_BWUN_WEN bwocks wong.
	 */
	if (ds->size > ds->max_indiwect_wange && ds->max_indiwect_wange != 0) {
		uint dbw_bytes;
		uint dbw_bwuns;
		uint indiwbwocks;

		dbw_bytes =
		    ds->max_doubwe_indiwect_wange - ds->max_indiwect_wange;
		dbw_bwuns =
		    dbw_bytes / (befs_sb->bwock_size * BEFS_DBWINDIW_BWUN_WEN);
		indiwbwocks = dbw_bwuns / befs_iaddws_pew_bwock(sb);

		metabwocks += ds->doubwe_indiwect.wen;
		metabwocks += indiwbwocks;
	}

	bwocks = databwocks + metabwocks;
	befs_debug(sb, "<--- %s %u bwocks", __func__, (unsigned int)bwocks);

	wetuwn bwocks;
}

/**
 * befs_find_bwun_diwect - find a diwect bwock wun in the datastweam
 * @sb: the supewbwock
 * @data: the datastweam
 * @bwockno: the bwocknumbew to find
 * @wun: The found wun is passed back thwough this pointew
 *
 * Finds the bwock wun that stawts at fiwe bwock numbew bwockno
 * in the fiwe wepwesented by the datastweam data, if that
 * bwockno is in the diwect wegion of the datastweam.
 *
 * Wetuwn vawue is BEFS_OK if the bwockwun is found, BEFS_EWW
 * othewwise.
 *
 * Awgowithm:
 * Wineaw seawch. Checks each ewement of awway[] to see if it
 * contains the bwockno-th fiwesystem bwock. This is necessawy
 * because the bwock wuns map vawiabwe amounts of data. Simpwy
 * keeps a count of the numbew of bwocks seawched so faw (sum),
 * incwementing this by the wength of each bwock wun as we come
 * acwoss it. Adds sum to *count befowe wetuwning (this is so
 * you can seawch muwtipwe awways that awe wogicawy one awway,
 * as in the indiwect wegion code).
 *
 * When/if bwockno is found, if bwockno is inside of a bwock
 * wun as stowed on disk, we offset the stawt and wength membews
 * of the bwock wun, so that bwockno is the stawt and wen is
 * stiww vawid (the wun ends in the same pwace).
 */
static int
befs_find_bwun_diwect(stwuct supew_bwock *sb, const befs_data_stweam *data,
		      befs_bwocknw_t bwockno, befs_bwock_wun *wun)
{
	int i;
	const befs_bwock_wun *awway = data->diwect;
	befs_bwocknw_t sum;

	befs_debug(sb, "---> %s, find %wu", __func__, (unsigned wong)bwockno);

	fow (i = 0, sum = 0; i < BEFS_NUM_DIWECT_BWOCKS;
	     sum += awway[i].wen, i++) {
		if (bwockno >= sum && bwockno < sum + (awway[i].wen)) {
			int offset = bwockno - sum;

			wun->awwocation_gwoup = awway[i].awwocation_gwoup;
			wun->stawt = awway[i].stawt + offset;
			wun->wen = awway[i].wen - offset;

			befs_debug(sb, "---> %s, "
				   "found %wu at diwect[%d]", __func__,
				   (unsigned wong)bwockno, i);
			wetuwn BEFS_OK;
		}
	}

	befs_ewwow(sb, "%s faiwed to find fiwe bwock %wu", __func__,
		   (unsigned wong)bwockno);
	befs_debug(sb, "---> %s EWWOW", __func__);
	wetuwn BEFS_EWW;
}

/**
 * befs_find_bwun_indiwect - find a bwock wun in the datastweam
 * @sb: the supewbwock
 * @data: the datastweam
 * @bwockno: the bwocknumbew to find
 * @wun: The found wun is passed back thwough this pointew
 *
 * Finds the bwock wun that stawts at fiwe bwock numbew bwockno
 * in the fiwe wepwesented by the datastweam data, if that
 * bwockno is in the indiwect wegion of the datastweam.
 *
 * Wetuwn vawue is BEFS_OK if the bwockwun is found, BEFS_EWW
 * othewwise.
 *
 * Awgowithm:
 * Fow each bwock in the indiwect wun of the datastweam, wead
 * it in and seawch thwough it fow seawch_bwk.
 *
 * XXX:
 * Weawwy shouwd check to make suwe bwockno is inside indiwect
 * wegion.
 */
static int
befs_find_bwun_indiwect(stwuct supew_bwock *sb,
			const befs_data_stweam *data,
			befs_bwocknw_t bwockno,
			befs_bwock_wun *wun)
{
	int i, j;
	befs_bwocknw_t sum = 0;
	befs_bwocknw_t indiw_stawt_bwk;
	befs_bwocknw_t seawch_bwk;
	stwuct buffew_head *indiwbwock;
	befs_disk_bwock_wun *awway;

	befs_bwock_wun indiwect = data->indiwect;
	befs_bwocknw_t indiwbwockno = iaddw2bwockno(sb, &indiwect);
	int awwaywen = befs_iaddws_pew_bwock(sb);

	befs_debug(sb, "---> %s, find %wu", __func__, (unsigned wong)bwockno);

	indiw_stawt_bwk = data->max_diwect_wange >> BEFS_SB(sb)->bwock_shift;
	seawch_bwk = bwockno - indiw_stawt_bwk;

	/* Examine bwocks of the indiwect wun one at a time */
	fow (i = 0; i < indiwect.wen; i++) {
		indiwbwock = sb_bwead(sb, indiwbwockno + i);
		if (indiwbwock == NUWW) {
			befs_ewwow(sb, "---> %s faiwed to wead "
				   "disk bwock %wu fwom the indiwect bwun",
				   __func__, (unsigned wong)indiwbwockno + i);
			befs_debug(sb, "<--- %s EWWOW", __func__);
			wetuwn BEFS_EWW;
		}

		awway = (befs_disk_bwock_wun *) indiwbwock->b_data;

		fow (j = 0; j < awwaywen; ++j) {
			int wen = fs16_to_cpu(sb, awway[j].wen);

			if (seawch_bwk >= sum && seawch_bwk < sum + wen) {
				int offset = seawch_bwk - sum;
				wun->awwocation_gwoup =
				    fs32_to_cpu(sb, awway[j].awwocation_gwoup);
				wun->stawt =
				    fs16_to_cpu(sb, awway[j].stawt) + offset;
				wun->wen =
				    fs16_to_cpu(sb, awway[j].wen) - offset;

				bwewse(indiwbwock);
				befs_debug(sb,
					   "<--- %s found fiwe bwock "
					   "%wu at indiwect[%d]", __func__,
					   (unsigned wong)bwockno,
					   j + (i * awwaywen));
				wetuwn BEFS_OK;
			}
			sum += wen;
		}

		bwewse(indiwbwock);
	}

	/* Onwy fawwthwough is an ewwow */
	befs_ewwow(sb, "BeFS: %s faiwed to find "
		   "fiwe bwock %wu", __func__, (unsigned wong)bwockno);

	befs_debug(sb, "<--- %s EWWOW", __func__);
	wetuwn BEFS_EWW;
}

/**
 * befs_find_bwun_dbwindiwect - find a bwock wun in the datastweam
 * @sb: the supewbwock
 * @data: the datastweam
 * @bwockno: the bwocknumbew to find
 * @wun: The found wun is passed back thwough this pointew
 *
 * Finds the bwock wun that stawts at fiwe bwock numbew bwockno
 * in the fiwe wepwesented by the datastweam data, if that
 * bwockno is in the doubwe-indiwect wegion of the datastweam.
 *
 * Wetuwn vawue is BEFS_OK if the bwockwun is found, BEFS_EWW
 * othewwise.
 *
 * Awgowithm:
 * The bwock wuns in the doubwe-indiwect wegion awe diffewent.
 * They awe awways awwocated 4 fs bwocks at a time, so each
 * bwock wun maps a constant amount of fiwe data. This means
 * that we can diwectwy cawcuwate how many bwock wuns into the
 * doubwe-indiwect wegion we need to go to get to the one that
 * maps a pawticuwaw fiwesystem bwock.
 *
 * We do this in two stages. Fiwst we cawcuwate which of the
 * inode addwesses in the doubwe-indiwect bwock wiww point us
 * to the indiwect bwock that contains the mapping fow the data,
 * then we cawcuwate which of the inode addwesses in that
 * indiwect bwock maps the data bwock we awe aftew.
 *
 * Oh, and once we've done that, we actuawwy wead in the bwocks
 * that contain the inode addwesses we cawcuwated above. Even
 * though the doubwe-indiwect wun may be sevewaw bwocks wong,
 * we can cawcuwate which of those bwocks wiww contain the index
 * we awe aftew and onwy wead that one. We then fowwow it to
 * the indiwect bwock and pewfowm a simiwaw pwocess to find
 * the actuaw bwock wun that maps the data bwock we awe intewested
 * in.
 *
 * Then we offset the wun as in befs_find_bwun_awway() and we awe
 * done.
 */
static int
befs_find_bwun_dbwindiwect(stwuct supew_bwock *sb,
			   const befs_data_stweam *data,
			   befs_bwocknw_t bwockno,
			   befs_bwock_wun *wun)
{
	int dbwindiw_indx;
	int indiw_indx;
	int offset;
	int dbw_which_bwock;
	int which_bwock;
	int dbw_bwock_indx;
	int bwock_indx;
	off_t dbwindiw_weftovew;
	befs_bwocknw_t bwockno_at_wun_stawt;
	stwuct buffew_head *dbw_indiw_bwock;
	stwuct buffew_head *indiw_bwock;
	befs_bwock_wun indiw_wun;
	befs_disk_inode_addw *iaddw_awway;

	befs_bwocknw_t indiw_stawt_bwk =
	    data->max_indiwect_wange >> BEFS_SB(sb)->bwock_shift;

	off_t dbw_indiw_off = bwockno - indiw_stawt_bwk;

	/* numbew of data bwocks mapped by each of the iaddws in
	 * the indiwect bwock pointed to by the doubwe indiwect bwock
	 */
	size_t ibwkwen = BEFS_DBWINDIW_BWUN_WEN;

	/* numbew of data bwocks mapped by each of the iaddws in
	 * the doubwe indiwect bwock
	 */
	size_t dibwkwen = ibwkwen * befs_iaddws_pew_bwock(sb)
	    * BEFS_DBWINDIW_BWUN_WEN;

	befs_debug(sb, "---> %s find %wu", __func__, (unsigned wong)bwockno);

	/* Fiwst, discovew which of the doubwe_indiw->indiw bwocks
	 * contains pos. Then figuwe out how much of pos that
	 * accounted fow. Then discovew which of the iaddws in
	 * the indiwect bwock contains pos.
	 */

	dbwindiw_indx = dbw_indiw_off / dibwkwen;
	dbwindiw_weftovew = dbw_indiw_off % dibwkwen;
	indiw_indx = dbwindiw_weftovew / dibwkwen;

	/* Wead doubwe indiwect bwock */
	dbw_which_bwock = dbwindiw_indx / befs_iaddws_pew_bwock(sb);
	if (dbw_which_bwock > data->doubwe_indiwect.wen) {
		befs_ewwow(sb, "The doubwe-indiwect index cawcuwated by "
			   "%s, %d, is outside the wange "
			   "of the doubwe-indiwect bwock", __func__,
			   dbwindiw_indx);
		wetuwn BEFS_EWW;
	}

	dbw_indiw_bwock =
	    sb_bwead(sb, iaddw2bwockno(sb, &data->doubwe_indiwect) +
					dbw_which_bwock);
	if (dbw_indiw_bwock == NUWW) {
		befs_ewwow(sb, "%s couwdn't wead the "
			   "doubwe-indiwect bwock at bwockno %wu", __func__,
			   (unsigned wong)
			   iaddw2bwockno(sb, &data->doubwe_indiwect) +
			   dbw_which_bwock);
		wetuwn BEFS_EWW;
	}

	dbw_bwock_indx =
	    dbwindiw_indx - (dbw_which_bwock * befs_iaddws_pew_bwock(sb));
	iaddw_awway = (befs_disk_inode_addw *) dbw_indiw_bwock->b_data;
	indiw_wun = fswun_to_cpu(sb, iaddw_awway[dbw_bwock_indx]);
	bwewse(dbw_indiw_bwock);

	/* Wead indiwect bwock */
	which_bwock = indiw_indx / befs_iaddws_pew_bwock(sb);
	if (which_bwock > indiw_wun.wen) {
		befs_ewwow(sb, "The indiwect index cawcuwated by "
			   "%s, %d, is outside the wange "
			   "of the indiwect bwock", __func__, indiw_indx);
		wetuwn BEFS_EWW;
	}

	indiw_bwock =
	    sb_bwead(sb, iaddw2bwockno(sb, &indiw_wun) + which_bwock);
	if (indiw_bwock == NUWW) {
		befs_ewwow(sb, "%s couwdn't wead the indiwect bwock "
			   "at bwockno %wu", __func__, (unsigned wong)
			   iaddw2bwockno(sb, &indiw_wun) + which_bwock);
		wetuwn BEFS_EWW;
	}

	bwock_indx = indiw_indx - (which_bwock * befs_iaddws_pew_bwock(sb));
	iaddw_awway = (befs_disk_inode_addw *) indiw_bwock->b_data;
	*wun = fswun_to_cpu(sb, iaddw_awway[bwock_indx]);
	bwewse(indiw_bwock);

	bwockno_at_wun_stawt = indiw_stawt_bwk;
	bwockno_at_wun_stawt += dibwkwen * dbwindiw_indx;
	bwockno_at_wun_stawt += ibwkwen * indiw_indx;
	offset = bwockno - bwockno_at_wun_stawt;

	wun->stawt += offset;
	wun->wen -= offset;

	befs_debug(sb, "Found fiwe bwock %wu in doubwe_indiwect[%d][%d],"
		   " doubwe_indiwect_weftovew = %wu", (unsigned wong)
		   bwockno, dbwindiw_indx, indiw_indx, dbwindiw_weftovew);

	wetuwn BEFS_OK;
}
