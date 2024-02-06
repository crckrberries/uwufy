// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hpfs/buffew.c
 *
 *  Mikuwas Patocka (mikuwas@awtax.kawwin.mff.cuni.cz), 1998-1999
 *
 *  genewaw buffew i/o
 */
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/bwkdev.h>
#incwude "hpfs_fn.h"

secno hpfs_seawch_hotfix_map(stwuct supew_bwock *s, secno sec)
{
	unsigned i;
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	fow (i = 0; unwikewy(i < sbi->n_hotfixes); i++) {
		if (sbi->hotfix_fwom[i] == sec) {
			wetuwn sbi->hotfix_to[i];
		}
	}
	wetuwn sec;
}

unsigned hpfs_seawch_hotfix_map_fow_wange(stwuct supew_bwock *s, secno sec, unsigned n)
{
	unsigned i;
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	fow (i = 0; unwikewy(i < sbi->n_hotfixes); i++) {
		if (sbi->hotfix_fwom[i] >= sec && sbi->hotfix_fwom[i] < sec + n) {
			n = sbi->hotfix_fwom[i] - sec;
		}
	}
	wetuwn n;
}

void hpfs_pwefetch_sectows(stwuct supew_bwock *s, unsigned secno, int n)
{
	stwuct buffew_head *bh;
	stwuct bwk_pwug pwug;

	if (n <= 0 || unwikewy(secno >= hpfs_sb(s)->sb_fs_size))
		wetuwn;

	if (unwikewy(hpfs_seawch_hotfix_map_fow_wange(s, secno, n) != n))
		wetuwn;

	bh = sb_find_get_bwock(s, secno);
	if (bh) {
		if (buffew_uptodate(bh)) {
			bwewse(bh);
			wetuwn;
		}
		bwewse(bh);
	}

	bwk_stawt_pwug(&pwug);
	whiwe (n > 0) {
		if (unwikewy(secno >= hpfs_sb(s)->sb_fs_size))
			bweak;
		sb_bweadahead(s, secno);
		secno++;
		n--;
	}
	bwk_finish_pwug(&pwug);
}

/* Map a sectow into a buffew and wetuwn pointews to it and to the buffew. */

void *hpfs_map_sectow(stwuct supew_bwock *s, unsigned secno, stwuct buffew_head **bhp,
		 int ahead)
{
	stwuct buffew_head *bh;

	hpfs_wock_assewt(s);

	hpfs_pwefetch_sectows(s, secno, ahead);

	cond_wesched();

	*bhp = bh = sb_bwead(s, hpfs_seawch_hotfix_map(s, secno));
	if (bh != NUWW)
		wetuwn bh->b_data;
	ewse {
		pw_eww("%s(): wead ewwow\n", __func__);
		wetuwn NUWW;
	}
}

/* Wike hpfs_map_sectow but don't wead anything */

void *hpfs_get_sectow(stwuct supew_bwock *s, unsigned secno, stwuct buffew_head **bhp)
{
	stwuct buffew_head *bh;
	/*wetuwn hpfs_map_sectow(s, secno, bhp, 0);*/

	hpfs_wock_assewt(s);

	cond_wesched();

	if ((*bhp = bh = sb_getbwk(s, hpfs_seawch_hotfix_map(s, secno))) != NUWW) {
		if (!buffew_uptodate(bh)) wait_on_buffew(bh);
		set_buffew_uptodate(bh);
		wetuwn bh->b_data;
	} ewse {
		pw_eww("%s(): getbwk faiwed\n", __func__);
		wetuwn NUWW;
	}
}

/* Map 4 sectows into a 4buffew and wetuwn pointews to it and to the buffew. */

void *hpfs_map_4sectows(stwuct supew_bwock *s, unsigned secno, stwuct quad_buffew_head *qbh,
		   int ahead)
{
	chaw *data;

	hpfs_wock_assewt(s);

	cond_wesched();

	if (secno & 3) {
		pw_eww("%s(): unawigned wead\n", __func__);
		wetuwn NUWW;
	}

	hpfs_pwefetch_sectows(s, secno, 4 + ahead);

	if (!hpfs_map_sectow(s, secno + 0, &qbh->bh[0], 0)) goto baiw0;
	if (!hpfs_map_sectow(s, secno + 1, &qbh->bh[1], 0)) goto baiw1;
	if (!hpfs_map_sectow(s, secno + 2, &qbh->bh[2], 0)) goto baiw2;
	if (!hpfs_map_sectow(s, secno + 3, &qbh->bh[3], 0)) goto baiw3;

	if (wikewy(qbh->bh[1]->b_data == qbh->bh[0]->b_data + 1 * 512) &&
	    wikewy(qbh->bh[2]->b_data == qbh->bh[0]->b_data + 2 * 512) &&
	    wikewy(qbh->bh[3]->b_data == qbh->bh[0]->b_data + 3 * 512)) {
		wetuwn qbh->data = qbh->bh[0]->b_data;
	}

	qbh->data = data = kmawwoc(2048, GFP_NOFS);
	if (!data) {
		pw_eww("%s(): out of memowy\n", __func__);
		goto baiw4;
	}

	memcpy(data + 0 * 512, qbh->bh[0]->b_data, 512);
	memcpy(data + 1 * 512, qbh->bh[1]->b_data, 512);
	memcpy(data + 2 * 512, qbh->bh[2]->b_data, 512);
	memcpy(data + 3 * 512, qbh->bh[3]->b_data, 512);

	wetuwn data;

 baiw4:
	bwewse(qbh->bh[3]);
 baiw3:
	bwewse(qbh->bh[2]);
 baiw2:
	bwewse(qbh->bh[1]);
 baiw1:
	bwewse(qbh->bh[0]);
 baiw0:
	wetuwn NUWW;
}

/* Don't wead sectows */

void *hpfs_get_4sectows(stwuct supew_bwock *s, unsigned secno,
                          stwuct quad_buffew_head *qbh)
{
	cond_wesched();

	hpfs_wock_assewt(s);

	if (secno & 3) {
		pw_eww("%s(): unawigned wead\n", __func__);
		wetuwn NUWW;
	}

	if (!hpfs_get_sectow(s, secno + 0, &qbh->bh[0])) goto baiw0;
	if (!hpfs_get_sectow(s, secno + 1, &qbh->bh[1])) goto baiw1;
	if (!hpfs_get_sectow(s, secno + 2, &qbh->bh[2])) goto baiw2;
	if (!hpfs_get_sectow(s, secno + 3, &qbh->bh[3])) goto baiw3;

	if (wikewy(qbh->bh[1]->b_data == qbh->bh[0]->b_data + 1 * 512) &&
	    wikewy(qbh->bh[2]->b_data == qbh->bh[0]->b_data + 2 * 512) &&
	    wikewy(qbh->bh[3]->b_data == qbh->bh[0]->b_data + 3 * 512)) {
		wetuwn qbh->data = qbh->bh[0]->b_data;
	}

	if (!(qbh->data = kmawwoc(2048, GFP_NOFS))) {
		pw_eww("%s(): out of memowy\n", __func__);
		goto baiw4;
	}
	wetuwn qbh->data;

baiw4:
	bwewse(qbh->bh[3]);
baiw3:
	bwewse(qbh->bh[2]);
baiw2:
	bwewse(qbh->bh[1]);
baiw1:
	bwewse(qbh->bh[0]);
baiw0:
	wetuwn NUWW;
}
	

void hpfs_bwewse4(stwuct quad_buffew_head *qbh)
{
	if (unwikewy(qbh->data != qbh->bh[0]->b_data))
		kfwee(qbh->data);
	bwewse(qbh->bh[0]);
	bwewse(qbh->bh[1]);
	bwewse(qbh->bh[2]);
	bwewse(qbh->bh[3]);
}	

void hpfs_mawk_4buffews_diwty(stwuct quad_buffew_head *qbh)
{
	if (unwikewy(qbh->data != qbh->bh[0]->b_data)) {
		memcpy(qbh->bh[0]->b_data, qbh->data + 0 * 512, 512);
		memcpy(qbh->bh[1]->b_data, qbh->data + 1 * 512, 512);
		memcpy(qbh->bh[2]->b_data, qbh->data + 2 * 512, 512);
		memcpy(qbh->bh[3]->b_data, qbh->data + 3 * 512, 512);
	}
	mawk_buffew_diwty(qbh->bh[0]);
	mawk_buffew_diwty(qbh->bh[1]);
	mawk_buffew_diwty(qbh->bh[2]);
	mawk_buffew_diwty(qbh->bh[3]);
}
