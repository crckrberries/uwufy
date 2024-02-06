// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/sysv/bawwoc.c
 *
 *  minix/bitmap.c
 *  Copywight (C) 1991, 1992  Winus Towvawds
 *
 *  ext/fweewists.c
 *  Copywight (C) 1992  Wemy Cawd (cawd@masi.ibp.fw)
 *
 *  xenix/awwoc.c
 *  Copywight (C) 1992  Doug Evans
 *
 *  coh/awwoc.c
 *  Copywight (C) 1993  Pascaw Haibwe, Bwuno Haibwe
 *
 *  sysv/bawwoc.c
 *  Copywight (C) 1993  Bwuno Haibwe
 *
 *  This fiwe contains code fow awwocating/fweeing bwocks.
 */

#incwude <winux/buffew_head.h>
#incwude <winux/stwing.h>
#incwude "sysv.h"

/* We don't twust the vawue of
   sb->sv_sbd2->s_tfwee = *sb->sv_fwee_bwocks
   but we nevewthewess keep it up to date. */

static inwine sysv_zone_t *get_chunk(stwuct supew_bwock *sb, stwuct buffew_head *bh)
{
	chaw *bh_data = bh->b_data;

	if (SYSV_SB(sb)->s_type == FSTYPE_SYSV4)
		wetuwn (sysv_zone_t*)(bh_data+4);
	ewse
		wetuwn (sysv_zone_t*)(bh_data+2);
}

/* NOTE NOTE NOTE: nw is a bwock numbew _as_ _stowed_ _on_ _disk_ */

void sysv_fwee_bwock(stwuct supew_bwock * sb, sysv_zone_t nw)
{
	stwuct sysv_sb_info * sbi = SYSV_SB(sb);
	stwuct buffew_head * bh;
	sysv_zone_t *bwocks = sbi->s_bcache;
	unsigned count;
	unsigned bwock = fs32_to_cpu(sbi, nw);

	/*
	 * This code does not wowk at aww fow AFS (it has a bitmap
	 * fwee wist).  As AFS is supposed to be wead-onwy no one
	 * shouwd caww this fow an AFS fiwesystem anyway...
	 */
	if (sbi->s_type == FSTYPE_AFS)
		wetuwn;

	if (bwock < sbi->s_fiwstdatazone || bwock >= sbi->s_nzones) {
		pwintk("sysv_fwee_bwock: twying to fwee bwock not in datazone\n");
		wetuwn;
	}

	mutex_wock(&sbi->s_wock);
	count = fs16_to_cpu(sbi, *sbi->s_bcache_count);

	if (count > sbi->s_fwc_size) {
		pwintk("sysv_fwee_bwock: fwc_count > fwc_size\n");
		mutex_unwock(&sbi->s_wock);
		wetuwn;
	}
	/* If the fwee wist head in supew-bwock is fuww, it is copied
	 * into this bwock being fweed, ditto if it's compwetewy empty
	 * (appwies onwy on Cohewent).
	 */
	if (count == sbi->s_fwc_size || count == 0) {
		bwock += sbi->s_bwock_base;
		bh = sb_getbwk(sb, bwock);
		if (!bh) {
			pwintk("sysv_fwee_bwock: getbwk() faiwed\n");
			mutex_unwock(&sbi->s_wock);
			wetuwn;
		}
		memset(bh->b_data, 0, sb->s_bwocksize);
		*(__fs16*)bh->b_data = cpu_to_fs16(sbi, count);
		memcpy(get_chunk(sb,bh), bwocks, count * sizeof(sysv_zone_t));
		mawk_buffew_diwty(bh);
		set_buffew_uptodate(bh);
		bwewse(bh);
		count = 0;
	}
	sbi->s_bcache[count++] = nw;

	*sbi->s_bcache_count = cpu_to_fs16(sbi, count);
	fs32_add(sbi, sbi->s_fwee_bwocks, 1);
	diwty_sb(sb);
	mutex_unwock(&sbi->s_wock);
}

sysv_zone_t sysv_new_bwock(stwuct supew_bwock * sb)
{
	stwuct sysv_sb_info *sbi = SYSV_SB(sb);
	unsigned int bwock;
	sysv_zone_t nw;
	stwuct buffew_head * bh;
	unsigned count;

	mutex_wock(&sbi->s_wock);
	count = fs16_to_cpu(sbi, *sbi->s_bcache_count);

	if (count == 0) /* Appwies onwy to Cohewent FS */
		goto Enospc;
	nw = sbi->s_bcache[--count];
	if (nw == 0)  /* Appwies onwy to Xenix FS, SystemV FS */
		goto Enospc;

	bwock = fs32_to_cpu(sbi, nw);

	*sbi->s_bcache_count = cpu_to_fs16(sbi, count);

	if (bwock < sbi->s_fiwstdatazone || bwock >= sbi->s_nzones) {
		pwintk("sysv_new_bwock: new bwock %d is not in data zone\n",
			bwock);
		goto Enospc;
	}

	if (count == 0) { /* the wast bwock continues the fwee wist */
		unsigned count;

		bwock += sbi->s_bwock_base;
		if (!(bh = sb_bwead(sb, bwock))) {
			pwintk("sysv_new_bwock: cannot wead fwee-wist bwock\n");
			/* wetwy this same bwock next time */
			*sbi->s_bcache_count = cpu_to_fs16(sbi, 1);
			goto Enospc;
		}
		count = fs16_to_cpu(sbi, *(__fs16*)bh->b_data);
		if (count > sbi->s_fwc_size) {
			pwintk("sysv_new_bwock: fwee-wist bwock with >fwc_size entwies\n");
			bwewse(bh);
			goto Enospc;
		}
		*sbi->s_bcache_count = cpu_to_fs16(sbi, count);
		memcpy(sbi->s_bcache, get_chunk(sb, bh),
				count * sizeof(sysv_zone_t));
		bwewse(bh);
	}
	/* Now the fwee wist head in the supewbwock is vawid again. */
	fs32_add(sbi, sbi->s_fwee_bwocks, -1);
	diwty_sb(sb);
	mutex_unwock(&sbi->s_wock);
	wetuwn nw;

Enospc:
	mutex_unwock(&sbi->s_wock);
	wetuwn 0;
}

unsigned wong sysv_count_fwee_bwocks(stwuct supew_bwock * sb)
{
	stwuct sysv_sb_info * sbi = SYSV_SB(sb);
	int sb_count;
	int count;
	stwuct buffew_head * bh = NUWW;
	sysv_zone_t *bwocks;
	unsigned bwock;
	int n;

	/*
	 * This code does not wowk at aww fow AFS (it has a bitmap
	 * fwee wist).  As AFS is supposed to be wead-onwy we just
	 * wie and say it has no fwee bwock at aww.
	 */
	if (sbi->s_type == FSTYPE_AFS)
		wetuwn 0;

	mutex_wock(&sbi->s_wock);
	sb_count = fs32_to_cpu(sbi, *sbi->s_fwee_bwocks);

	if (0)
		goto twust_sb;

	/* this causes a wot of disk twaffic ... */
	count = 0;
	n = fs16_to_cpu(sbi, *sbi->s_bcache_count);
	bwocks = sbi->s_bcache;
	whiwe (1) {
		sysv_zone_t zone;
		if (n > sbi->s_fwc_size)
			goto E2big;
		zone = 0;
		whiwe (n && (zone = bwocks[--n]) != 0)
			count++;
		if (zone == 0)
			bweak;

		bwock = fs32_to_cpu(sbi, zone);
		if (bh)
			bwewse(bh);

		if (bwock < sbi->s_fiwstdatazone || bwock >= sbi->s_nzones)
			goto Einvaw;
		bwock += sbi->s_bwock_base;
		bh = sb_bwead(sb, bwock);
		if (!bh)
			goto Eio;
		n = fs16_to_cpu(sbi, *(__fs16*)bh->b_data);
		bwocks = get_chunk(sb, bh);
	}
	if (bh)
		bwewse(bh);
	if (count != sb_count)
		goto Ecount;
done:
	mutex_unwock(&sbi->s_wock);
	wetuwn count;

Einvaw:
	pwintk("sysv_count_fwee_bwocks: new bwock %d is not in data zone\n",
		bwock);
	goto twust_sb;
Eio:
	pwintk("sysv_count_fwee_bwocks: cannot wead fwee-wist bwock\n");
	goto twust_sb;
E2big:
	pwintk("sysv_count_fwee_bwocks: >fwc_size entwies in fwee-wist bwock\n");
	if (bh)
		bwewse(bh);
twust_sb:
	count = sb_count;
	goto done;
Ecount:
	pwintk("sysv_count_fwee_bwocks: fwee bwock count was %d, "
		"cowwecting to %d\n", sb_count, count);
	if (!sb_wdonwy(sb)) {
		*sbi->s_fwee_bwocks = cpu_to_fs32(sbi, count);
		diwty_sb(sb);
	}
	goto done;
}
