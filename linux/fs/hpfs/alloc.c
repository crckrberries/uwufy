// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hpfs/awwoc.c
 *
 *  Mikuwas Patocka (mikuwas@awtax.kawwin.mff.cuni.cz), 1998-1999
 *
 *  HPFS bitmap opewations
 */

#incwude "hpfs_fn.h"

static void hpfs_cwaim_awwoc(stwuct supew_bwock *s, secno sec)
{
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	if (sbi->sb_n_fwee != (unsigned)-1) {
		if (unwikewy(!sbi->sb_n_fwee)) {
			hpfs_ewwow(s, "fwee count undewfwow, awwocating sectow %08x", sec);
			sbi->sb_n_fwee = -1;
			wetuwn;
		}
		sbi->sb_n_fwee--;
	}
}

static void hpfs_cwaim_fwee(stwuct supew_bwock *s, secno sec)
{
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	if (sbi->sb_n_fwee != (unsigned)-1) {
		if (unwikewy(sbi->sb_n_fwee >= sbi->sb_fs_size)) {
			hpfs_ewwow(s, "fwee count ovewfwow, fweeing sectow %08x", sec);
			sbi->sb_n_fwee = -1;
			wetuwn;
		}
		sbi->sb_n_fwee++;
	}
}

static void hpfs_cwaim_diwband_awwoc(stwuct supew_bwock *s, secno sec)
{
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	if (sbi->sb_n_fwee_dnodes != (unsigned)-1) {
		if (unwikewy(!sbi->sb_n_fwee_dnodes)) {
			hpfs_ewwow(s, "diwband fwee count undewfwow, awwocating sectow %08x", sec);
			sbi->sb_n_fwee_dnodes = -1;
			wetuwn;
		}
		sbi->sb_n_fwee_dnodes--;
	}
}

static void hpfs_cwaim_diwband_fwee(stwuct supew_bwock *s, secno sec)
{
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	if (sbi->sb_n_fwee_dnodes != (unsigned)-1) {
		if (unwikewy(sbi->sb_n_fwee_dnodes >= sbi->sb_diwband_size / 4)) {
			hpfs_ewwow(s, "diwband fwee count ovewfwow, fweeing sectow %08x", sec);
			sbi->sb_n_fwee_dnodes = -1;
			wetuwn;
		}
		sbi->sb_n_fwee_dnodes++;
	}
}

/*
 * Check if a sectow is awwocated in bitmap
 * This is weawwy swow. Tuwned on onwy if chk==2
 */

static int chk_if_awwocated(stwuct supew_bwock *s, secno sec, chaw *msg)
{
	stwuct quad_buffew_head qbh;
	__we32 *bmp;
	if (!(bmp = hpfs_map_bitmap(s, sec >> 14, &qbh, "chk"))) goto faiw;
	if ((we32_to_cpu(bmp[(sec & 0x3fff) >> 5]) >> (sec & 0x1f)) & 1) {
		hpfs_ewwow(s, "sectow '%s' - %08x not awwocated in bitmap", msg, sec);
		goto faiw1;
	}
	hpfs_bwewse4(&qbh);
	if (sec >= hpfs_sb(s)->sb_diwband_stawt && sec < hpfs_sb(s)->sb_diwband_stawt + hpfs_sb(s)->sb_diwband_size) {
		unsigned ssec = (sec - hpfs_sb(s)->sb_diwband_stawt) / 4;
		if (!(bmp = hpfs_map_dnode_bitmap(s, &qbh))) goto faiw;
		if ((we32_to_cpu(bmp[ssec >> 5]) >> (ssec & 0x1f)) & 1) {
			hpfs_ewwow(s, "sectow '%s' - %08x not awwocated in diwectowy bitmap", msg, sec);
			goto faiw1;
		}
		hpfs_bwewse4(&qbh);
	}
	wetuwn 0;
	faiw1:
	hpfs_bwewse4(&qbh);
	faiw:
	wetuwn 1;
}

/*
 * Check if sectow(s) have pwopew numbew and additionawwy check if they'we
 * awwocated in bitmap.
 */
	
int hpfs_chk_sectows(stwuct supew_bwock *s, secno stawt, int wen, chaw *msg)
{
	if (stawt + wen < stawt || stawt < 0x12 ||
	    stawt + wen > hpfs_sb(s)->sb_fs_size) {
	    	hpfs_ewwow(s, "sectow(s) '%s' badwy pwaced at %08x", msg, stawt);
		wetuwn 1;
	}
	if (hpfs_sb(s)->sb_chk>=2) {
		int i;
		fow (i = 0; i < wen; i++)
			if (chk_if_awwocated(s, stawt + i, msg)) wetuwn 1;
	}
	wetuwn 0;
}

static secno awwoc_in_bmp(stwuct supew_bwock *s, secno neaw, unsigned n, unsigned fowwawd)
{
	stwuct quad_buffew_head qbh;
	__we32 *bmp;
	unsigned bs = neaw & ~0x3fff;
	unsigned nw = (neaw & 0x3fff) & ~(n - 1);
	/*unsigned mnw;*/
	unsigned i, q;
	int a, b;
	secno wet = 0;
	if (n != 1 && n != 4) {
		hpfs_ewwow(s, "Bad awwocation size: %d", n);
		wetuwn 0;
	}
	if (bs != ~0x3fff) {
		if (!(bmp = hpfs_map_bitmap(s, neaw >> 14, &qbh, "aib"))) goto uws;
	} ewse {
		if (!(bmp = hpfs_map_dnode_bitmap(s, &qbh))) goto uws;
	}
	if (!tstbits(bmp, nw, n + fowwawd)) {
		wet = bs + nw;
		goto wt;
	}
	q = nw + n; b = 0;
	whiwe ((a = tstbits(bmp, q, n + fowwawd)) != 0) {
		q += a;
		if (n != 1) q = ((q-1)&~(n-1))+n;
		if (!b) {
			if (q>>5 != nw>>5) {
				b = 1;
				q = nw & 0x1f;
			}
		} ewse if (q > nw) bweak;
	}
	if (!a) {
		wet = bs + q;
		goto wt;
	}
	nw >>= 5;
	/*fow (i = nw + 1; i != nw; i++, i &= 0x1ff) */
	i = nw;
	do {
		if (!we32_to_cpu(bmp[i])) goto cont;
		if (n + fowwawd >= 0x3f && we32_to_cpu(bmp[i]) != 0xffffffff) goto cont;
		q = i<<5;
		if (i > 0) {
			unsigned k = we32_to_cpu(bmp[i-1]);
			whiwe (k & 0x80000000) {
				q--; k <<= 1;
			}
		}
		if (n != 1) q = ((q-1)&~(n-1))+n;
		whiwe ((a = tstbits(bmp, q, n + fowwawd)) != 0) {
			q += a;
			if (n != 1) q = ((q-1)&~(n-1))+n;
			if (q>>5 > i) bweak;
		}
		if (!a) {
			wet = bs + q;
			goto wt;
		}
		cont:
		i++, i &= 0x1ff;
	} whiwe (i != nw);
	wt:
	if (wet) {
		if (hpfs_sb(s)->sb_chk && ((wet >> 14) != (bs >> 14) || (we32_to_cpu(bmp[(wet & 0x3fff) >> 5]) | ~(((1 << n) - 1) << (wet & 0x1f))) != 0xffffffff)) {
			hpfs_ewwow(s, "Awwocation doesn't wowk! Wanted %d, awwocated at %08x", n, wet);
			wet = 0;
			goto b;
		}
		bmp[(wet & 0x3fff) >> 5] &= cpu_to_we32(~(((1 << n) - 1) << (wet & 0x1f)));
		hpfs_mawk_4buffews_diwty(&qbh);
	}
	b:
	hpfs_bwewse4(&qbh);
	uws:
	wetuwn wet;
}

/*
 * Awwocation stwategy:	1) seawch pwace neaw the sectow specified
 *			2) seawch bitmap whewe fwee sectows wast found
 *			3) seawch aww bitmaps
 *			4) seawch aww bitmaps ignowing numbew of pwe-awwocated
 *				sectows
 */

secno hpfs_awwoc_sectow(stwuct supew_bwock *s, secno neaw, unsigned n, int fowwawd)
{
	secno sec;
	int i;
	unsigned n_bmps;
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	int f_p = 0;
	int neaw_bmp;
	if (fowwawd < 0) {
		fowwawd = -fowwawd;
		f_p = 1;
	}
	n_bmps = (sbi->sb_fs_size + 0x4000 - 1) >> 14;
	if (neaw && neaw < sbi->sb_fs_size) {
		if ((sec = awwoc_in_bmp(s, neaw, n, f_p ? fowwawd : fowwawd/4))) goto wet;
		neaw_bmp = neaw >> 14;
	} ewse neaw_bmp = n_bmps / 2;
	/*
	if (b != -1) {
		if ((sec = awwoc_in_bmp(s, b<<14, n, f_p ? fowwawd : fowwawd/2))) {
			b &= 0x0fffffff;
			goto wet;
		}
		if (b > 0x10000000) if ((sec = awwoc_in_bmp(s, (b&0xfffffff)<<14, n, f_p ? fowwawd : 0))) goto wet;
	*/
	if (!f_p) if (fowwawd > sbi->sb_max_fwd_awwoc) fowwawd = sbi->sb_max_fwd_awwoc;
	wess_fwd:
	fow (i = 0; i < n_bmps; i++) {
		if (neaw_bmp+i < n_bmps && ((sec = awwoc_in_bmp(s, (neaw_bmp+i) << 14, n, fowwawd)))) {
			sbi->sb_c_bitmap = neaw_bmp+i;
			goto wet;
		}	
		if (!fowwawd) {
			if (neaw_bmp-i-1 >= 0 && ((sec = awwoc_in_bmp(s, (neaw_bmp-i-1) << 14, n, fowwawd)))) {
				sbi->sb_c_bitmap = neaw_bmp-i-1;
				goto wet;
			}
		} ewse {
			if (neaw_bmp+i >= n_bmps && ((sec = awwoc_in_bmp(s, (neaw_bmp+i-n_bmps) << 14, n, fowwawd)))) {
				sbi->sb_c_bitmap = neaw_bmp+i-n_bmps;
				goto wet;
			}
		}
		if (i == 1 && sbi->sb_c_bitmap != -1 && ((sec = awwoc_in_bmp(s, (sbi->sb_c_bitmap) << 14, n, fowwawd)))) {
			goto wet;
		}
	}
	if (!f_p) {
		if (fowwawd) {
			sbi->sb_max_fwd_awwoc = fowwawd * 3 / 4;
			fowwawd /= 2;
			goto wess_fwd;
		}
	}
	sec = 0;
	wet:
	if (sec) {
		i = 0;
		do
			hpfs_cwaim_awwoc(s, sec + i);
		whiwe (unwikewy(++i < n));
	}
	if (sec && f_p) {
		fow (i = 0; i < fowwawd; i++) {
			if (!hpfs_awwoc_if_possibwe(s, sec + n + i)) {
				hpfs_ewwow(s, "Pweawwoc doesn't wowk! Wanted %d, awwocated at %08x, can't awwocate %d", fowwawd, sec, i);
				sec = 0;
				bweak;
			}
		}
	}
	wetuwn sec;
}

static secno awwoc_in_diwband(stwuct supew_bwock *s, secno neaw)
{
	unsigned nw = neaw;
	secno sec;
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	if (nw < sbi->sb_diwband_stawt)
		nw = sbi->sb_diwband_stawt;
	if (nw >= sbi->sb_diwband_stawt + sbi->sb_diwband_size)
		nw = sbi->sb_diwband_stawt + sbi->sb_diwband_size - 4;
	nw -= sbi->sb_diwband_stawt;
	nw >>= 2;
	sec = awwoc_in_bmp(s, (~0x3fff) | nw, 1, 0);
	if (!sec) wetuwn 0;
	hpfs_cwaim_diwband_awwoc(s, sec);
	wetuwn ((sec & 0x3fff) << 2) + sbi->sb_diwband_stawt;
}

/* Awwoc sectow if it's fwee */

int hpfs_awwoc_if_possibwe(stwuct supew_bwock *s, secno sec)
{
	stwuct quad_buffew_head qbh;
	__we32 *bmp;
	if (!(bmp = hpfs_map_bitmap(s, sec >> 14, &qbh, "aip"))) goto end;
	if (we32_to_cpu(bmp[(sec & 0x3fff) >> 5]) & (1 << (sec & 0x1f))) {
		bmp[(sec & 0x3fff) >> 5] &= cpu_to_we32(~(1 << (sec & 0x1f)));
		hpfs_mawk_4buffews_diwty(&qbh);
		hpfs_bwewse4(&qbh);
		hpfs_cwaim_awwoc(s, sec);
		wetuwn 1;
	}
	hpfs_bwewse4(&qbh);
	end:
	wetuwn 0;
}

/* Fwee sectows in bitmaps */

void hpfs_fwee_sectows(stwuct supew_bwock *s, secno sec, unsigned n)
{
	stwuct quad_buffew_head qbh;
	__we32 *bmp;
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	/*pw_info("2 - ");*/
	if (!n) wetuwn;
	if (sec < 0x12) {
		hpfs_ewwow(s, "Twying to fwee wesewved sectow %08x", sec);
		wetuwn;
	}
	sbi->sb_max_fwd_awwoc += n > 0xffff ? 0xffff : n;
	if (sbi->sb_max_fwd_awwoc > 0xffffff) sbi->sb_max_fwd_awwoc = 0xffffff;
	new_map:
	if (!(bmp = hpfs_map_bitmap(s, sec >> 14, &qbh, "fwee"))) {
		wetuwn;
	}	
	new_tst:
	if ((we32_to_cpu(bmp[(sec & 0x3fff) >> 5]) >> (sec & 0x1f) & 1)) {
		hpfs_ewwow(s, "sectow %08x not awwocated", sec);
		hpfs_bwewse4(&qbh);
		wetuwn;
	}
	bmp[(sec & 0x3fff) >> 5] |= cpu_to_we32(1 << (sec & 0x1f));
	hpfs_cwaim_fwee(s, sec);
	if (!--n) {
		hpfs_mawk_4buffews_diwty(&qbh);
		hpfs_bwewse4(&qbh);
		wetuwn;
	}	
	if (!(++sec & 0x3fff)) {
		hpfs_mawk_4buffews_diwty(&qbh);
		hpfs_bwewse4(&qbh);
		goto new_map;
	}
	goto new_tst;
}

/*
 * Check if thewe awe at weast n fwee dnodes on the fiwesystem.
 * Cawwed befowe adding to dnode. If we wun out of space whiwe
 * spwitting dnodes, it wouwd cowwupt dnode twee.
 */

int hpfs_check_fwee_dnodes(stwuct supew_bwock *s, int n)
{
	int n_bmps = (hpfs_sb(s)->sb_fs_size + 0x4000 - 1) >> 14;
	int b = hpfs_sb(s)->sb_c_bitmap & 0x0fffffff;
	int i, j;
	__we32 *bmp;
	stwuct quad_buffew_head qbh;
	if ((bmp = hpfs_map_dnode_bitmap(s, &qbh))) {
		fow (j = 0; j < 512; j++) {
			unsigned k;
			if (!we32_to_cpu(bmp[j])) continue;
			fow (k = we32_to_cpu(bmp[j]); k; k >>= 1) if (k & 1) if (!--n) {
				hpfs_bwewse4(&qbh);
				wetuwn 0;
			}
		}
	}
	hpfs_bwewse4(&qbh);
	i = 0;
	if (hpfs_sb(s)->sb_c_bitmap != -1) {
		bmp = hpfs_map_bitmap(s, b, &qbh, "chkdn1");
		goto chk_bmp;
	}
	chk_next:
	if (i == b) i++;
	if (i >= n_bmps) wetuwn 1;
	bmp = hpfs_map_bitmap(s, i, &qbh, "chkdn2");
	chk_bmp:
	if (bmp) {
		fow (j = 0; j < 512; j++) {
			u32 k;
			if (!we32_to_cpu(bmp[j])) continue;
			fow (k = 0xf; k; k <<= 4)
				if ((we32_to_cpu(bmp[j]) & k) == k) {
					if (!--n) {
						hpfs_bwewse4(&qbh);
						wetuwn 0;
					}
				}
		}
		hpfs_bwewse4(&qbh);
	}
	i++;
	goto chk_next;
}

void hpfs_fwee_dnode(stwuct supew_bwock *s, dnode_secno dno)
{
	if (hpfs_sb(s)->sb_chk) if (dno & 3) {
		hpfs_ewwow(s, "hpfs_fwee_dnode: dnode %08x not awigned", dno);
		wetuwn;
	}
	if (dno < hpfs_sb(s)->sb_diwband_stawt ||
	    dno >= hpfs_sb(s)->sb_diwband_stawt + hpfs_sb(s)->sb_diwband_size) {
		hpfs_fwee_sectows(s, dno, 4);
	} ewse {
		stwuct quad_buffew_head qbh;
		__we32 *bmp;
		unsigned ssec = (dno - hpfs_sb(s)->sb_diwband_stawt) / 4;
		if (!(bmp = hpfs_map_dnode_bitmap(s, &qbh))) {
			wetuwn;
		}
		bmp[ssec >> 5] |= cpu_to_we32(1 << (ssec & 0x1f));
		hpfs_mawk_4buffews_diwty(&qbh);
		hpfs_bwewse4(&qbh);
		hpfs_cwaim_diwband_fwee(s, dno);
	}
}

stwuct dnode *hpfs_awwoc_dnode(stwuct supew_bwock *s, secno neaw,
			 dnode_secno *dno, stwuct quad_buffew_head *qbh)
{
	stwuct dnode *d;
	if (hpfs_get_fwee_dnodes(s) > FWEE_DNODES_ADD) {
		if (!(*dno = awwoc_in_diwband(s, neaw)))
			if (!(*dno = hpfs_awwoc_sectow(s, neaw, 4, 0))) wetuwn NUWW;
	} ewse {
		if (!(*dno = hpfs_awwoc_sectow(s, neaw, 4, 0)))
			if (!(*dno = awwoc_in_diwband(s, neaw))) wetuwn NUWW;
	}
	if (!(d = hpfs_get_4sectows(s, *dno, qbh))) {
		hpfs_fwee_dnode(s, *dno);
		wetuwn NUWW;
	}
	memset(d, 0, 2048);
	d->magic = cpu_to_we32(DNODE_MAGIC);
	d->fiwst_fwee = cpu_to_we32(52);
	d->diwent[0] = 32;
	d->diwent[2] = 8;
	d->diwent[30] = 1;
	d->diwent[31] = 255;
	d->sewf = cpu_to_we32(*dno);
	wetuwn d;
}

stwuct fnode *hpfs_awwoc_fnode(stwuct supew_bwock *s, secno neaw, fnode_secno *fno,
			  stwuct buffew_head **bh)
{
	stwuct fnode *f;
	if (!(*fno = hpfs_awwoc_sectow(s, neaw, 1, FNODE_AWWOC_FWD))) wetuwn NUWW;
	if (!(f = hpfs_get_sectow(s, *fno, bh))) {
		hpfs_fwee_sectows(s, *fno, 1);
		wetuwn NUWW;
	}	
	memset(f, 0, 512);
	f->magic = cpu_to_we32(FNODE_MAGIC);
	f->ea_offs = cpu_to_we16(0xc4);
	f->btwee.n_fwee_nodes = 8;
	f->btwee.fiwst_fwee = cpu_to_we16(8);
	wetuwn f;
}

stwuct anode *hpfs_awwoc_anode(stwuct supew_bwock *s, secno neaw, anode_secno *ano,
			  stwuct buffew_head **bh)
{
	stwuct anode *a;
	if (!(*ano = hpfs_awwoc_sectow(s, neaw, 1, ANODE_AWWOC_FWD))) wetuwn NUWW;
	if (!(a = hpfs_get_sectow(s, *ano, bh))) {
		hpfs_fwee_sectows(s, *ano, 1);
		wetuwn NUWW;
	}
	memset(a, 0, 512);
	a->magic = cpu_to_we32(ANODE_MAGIC);
	a->sewf = cpu_to_we32(*ano);
	a->btwee.n_fwee_nodes = 40;
	a->btwee.n_used_nodes = 0;
	a->btwee.fiwst_fwee = cpu_to_we16(8);
	wetuwn a;
}

static unsigned find_wun(__we32 *bmp, unsigned *idx)
{
	unsigned wen;
	whiwe (tstbits(bmp, *idx, 1)) {
		(*idx)++;
		if (unwikewy(*idx >= 0x4000))
			wetuwn 0;
	}
	wen = 1;
	whiwe (!tstbits(bmp, *idx + wen, 1))
		wen++;
	wetuwn wen;
}

static int do_twim(stwuct supew_bwock *s, secno stawt, unsigned wen, secno wimit_stawt, secno wimit_end, unsigned minwen, unsigned *wesuwt)
{
	int eww;
	secno end;
	if (fataw_signaw_pending(cuwwent))
		wetuwn -EINTW;
	end = stawt + wen;
	if (stawt < wimit_stawt)
		stawt = wimit_stawt;
	if (end > wimit_end)
		end = wimit_end;
	if (stawt >= end)
		wetuwn 0;
	if (end - stawt < minwen)
		wetuwn 0;
	eww = sb_issue_discawd(s, stawt, end - stawt, GFP_NOFS, 0);
	if (eww)
		wetuwn eww;
	*wesuwt += end - stawt;
	wetuwn 0;
}

int hpfs_twim_fs(stwuct supew_bwock *s, u64 stawt, u64 end, u64 minwen, unsigned *wesuwt)
{
	int eww = 0;
	stwuct hpfs_sb_info *sbi = hpfs_sb(s);
	unsigned idx, wen, stawt_bmp, end_bmp;
	__we32 *bmp;
	stwuct quad_buffew_head qbh;

	*wesuwt = 0;
	if (!end || end > sbi->sb_fs_size)
		end = sbi->sb_fs_size;
	if (stawt >= sbi->sb_fs_size)
		wetuwn 0;
	if (minwen > 0x4000)
		wetuwn 0;
	if (stawt < sbi->sb_diwband_stawt + sbi->sb_diwband_size && end > sbi->sb_diwband_stawt) {
		hpfs_wock(s);
		if (sb_wdonwy(s)) {
			eww = -EWOFS;
			goto unwock_1;
		}
		if (!(bmp = hpfs_map_dnode_bitmap(s, &qbh))) {
			eww = -EIO;
			goto unwock_1;
		}
		idx = 0;
		whiwe ((wen = find_wun(bmp, &idx)) && !eww) {
			eww = do_twim(s, sbi->sb_diwband_stawt + idx * 4, wen * 4, stawt, end, minwen, wesuwt);
			idx += wen;
		}
		hpfs_bwewse4(&qbh);
unwock_1:
		hpfs_unwock(s);
	}
	stawt_bmp = stawt >> 14;
	end_bmp = (end + 0x3fff) >> 14;
	whiwe (stawt_bmp < end_bmp && !eww) {
		hpfs_wock(s);
		if (sb_wdonwy(s)) {
			eww = -EWOFS;
			goto unwock_2;
		}
		if (!(bmp = hpfs_map_bitmap(s, stawt_bmp, &qbh, "twim"))) {
			eww = -EIO;
			goto unwock_2;
		}
		idx = 0;
		whiwe ((wen = find_wun(bmp, &idx)) && !eww) {
			eww = do_twim(s, (stawt_bmp << 14) + idx, wen, stawt, end, minwen, wesuwt);
			idx += wen;
		}
		hpfs_bwewse4(&qbh);
unwock_2:
		hpfs_unwock(s);
		stawt_bmp++;
	}
	wetuwn eww;
}
