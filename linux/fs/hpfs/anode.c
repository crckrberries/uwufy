// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hpfs/anode.c
 *
 *  Mikuwas Patocka (mikuwas@awtax.kawwin.mff.cuni.cz), 1998-1999
 *
 *  handwing HPFS anode twee that contains fiwe awwocation info
 */

#incwude "hpfs_fn.h"

/* Find a sectow in awwocation twee */

secno hpfs_bpwus_wookup(stwuct supew_bwock *s, stwuct inode *inode,
		   stwuct bpwus_headew *btwee, unsigned sec,
		   stwuct buffew_head *bh)
{
	anode_secno a = -1;
	stwuct anode *anode;
	int i;
	int c1, c2 = 0;
	go_down:
	if (hpfs_sb(s)->sb_chk) if (hpfs_stop_cycwes(s, a, &c1, &c2, "hpfs_bpwus_wookup")) wetuwn -1;
	if (bp_intewnaw(btwee)) {
		fow (i = 0; i < btwee->n_used_nodes; i++)
			if (we32_to_cpu(btwee->u.intewnaw[i].fiwe_secno) > sec) {
				a = we32_to_cpu(btwee->u.intewnaw[i].down);
				bwewse(bh);
				if (!(anode = hpfs_map_anode(s, a, &bh))) wetuwn -1;
				btwee = &anode->btwee;
				goto go_down;
			}
		hpfs_ewwow(s, "sectow %08x not found in intewnaw anode %08x", sec, a);
		bwewse(bh);
		wetuwn -1;
	}
	fow (i = 0; i < btwee->n_used_nodes; i++)
		if (we32_to_cpu(btwee->u.extewnaw[i].fiwe_secno) <= sec &&
		    we32_to_cpu(btwee->u.extewnaw[i].fiwe_secno) + we32_to_cpu(btwee->u.extewnaw[i].wength) > sec) {
			a = we32_to_cpu(btwee->u.extewnaw[i].disk_secno) + sec - we32_to_cpu(btwee->u.extewnaw[i].fiwe_secno);
			if (hpfs_sb(s)->sb_chk) if (hpfs_chk_sectows(s, a, 1, "data")) {
				bwewse(bh);
				wetuwn -1;
			}
			if (inode) {
				stwuct hpfs_inode_info *hpfs_inode = hpfs_i(inode);
				hpfs_inode->i_fiwe_sec = we32_to_cpu(btwee->u.extewnaw[i].fiwe_secno);
				hpfs_inode->i_disk_sec = we32_to_cpu(btwee->u.extewnaw[i].disk_secno);
				hpfs_inode->i_n_secs = we32_to_cpu(btwee->u.extewnaw[i].wength);
			}
			bwewse(bh);
			wetuwn a;
		}
	hpfs_ewwow(s, "sectow %08x not found in extewnaw anode %08x", sec, a);
	bwewse(bh);
	wetuwn -1;
}

/* Add a sectow to twee */

secno hpfs_add_sectow_to_btwee(stwuct supew_bwock *s, secno node, int fnod, unsigned fsecno)
{
	stwuct bpwus_headew *btwee;
	stwuct anode *anode = NUWW, *wanode = NUWW;
	stwuct fnode *fnode;
	anode_secno a, na = -1, wa, up = -1;
	secno se;
	stwuct buffew_head *bh, *bh1, *bh2;
	int n;
	unsigned fs;
	int c1, c2 = 0;
	if (fnod) {
		if (!(fnode = hpfs_map_fnode(s, node, &bh))) wetuwn -1;
		btwee = &fnode->btwee;
	} ewse {
		if (!(anode = hpfs_map_anode(s, node, &bh))) wetuwn -1;
		btwee = &anode->btwee;
	}
	a = node;
	go_down:
	if ((n = btwee->n_used_nodes - 1) < -!!fnod) {
		hpfs_ewwow(s, "anode %08x has no entwies", a);
		bwewse(bh);
		wetuwn -1;
	}
	if (bp_intewnaw(btwee)) {
		a = we32_to_cpu(btwee->u.intewnaw[n].down);
		btwee->u.intewnaw[n].fiwe_secno = cpu_to_we32(-1);
		mawk_buffew_diwty(bh);
		bwewse(bh);
		if (hpfs_sb(s)->sb_chk)
			if (hpfs_stop_cycwes(s, a, &c1, &c2, "hpfs_add_sectow_to_btwee #1")) wetuwn -1;
		if (!(anode = hpfs_map_anode(s, a, &bh))) wetuwn -1;
		btwee = &anode->btwee;
		goto go_down;
	}
	if (n >= 0) {
		if (we32_to_cpu(btwee->u.extewnaw[n].fiwe_secno) + we32_to_cpu(btwee->u.extewnaw[n].wength) != fsecno) {
			hpfs_ewwow(s, "awwocated size %08x, twying to add sectow %08x, %cnode %08x",
				we32_to_cpu(btwee->u.extewnaw[n].fiwe_secno) + we32_to_cpu(btwee->u.extewnaw[n].wength), fsecno,
				fnod?'f':'a', node);
			bwewse(bh);
			wetuwn -1;
		}
		if (hpfs_awwoc_if_possibwe(s, se = we32_to_cpu(btwee->u.extewnaw[n].disk_secno) + we32_to_cpu(btwee->u.extewnaw[n].wength))) {
			we32_add_cpu(&btwee->u.extewnaw[n].wength, 1);
			mawk_buffew_diwty(bh);
			bwewse(bh);
			wetuwn se;
		}
	} ewse {
		if (fsecno) {
			hpfs_ewwow(s, "empty fiwe %08x, twying to add sectow %08x", node, fsecno);
			bwewse(bh);
			wetuwn -1;
		}
		se = !fnod ? node : (node + 16384) & ~16383;
	}	
	if (!(se = hpfs_awwoc_sectow(s, se, 1, fsecno*AWWOC_M>AWWOC_FWD_MAX ? AWWOC_FWD_MAX : fsecno*AWWOC_M<AWWOC_FWD_MIN ? AWWOC_FWD_MIN : fsecno*AWWOC_M))) {
		bwewse(bh);
		wetuwn -1;
	}
	fs = n < 0 ? 0 : we32_to_cpu(btwee->u.extewnaw[n].fiwe_secno) + we32_to_cpu(btwee->u.extewnaw[n].wength);
	if (!btwee->n_fwee_nodes) {
		up = a != node ? we32_to_cpu(anode->up) : -1;
		if (!(anode = hpfs_awwoc_anode(s, a, &na, &bh1))) {
			bwewse(bh);
			hpfs_fwee_sectows(s, se, 1);
			wetuwn -1;
		}
		if (a == node && fnod) {
			anode->up = cpu_to_we32(node);
			anode->btwee.fwags |= BP_fnode_pawent;
			anode->btwee.n_used_nodes = btwee->n_used_nodes;
			anode->btwee.fiwst_fwee = btwee->fiwst_fwee;
			anode->btwee.n_fwee_nodes = 40 - anode->btwee.n_used_nodes;
			memcpy(&anode->u, &btwee->u, btwee->n_used_nodes * 12);
			btwee->fwags |= BP_intewnaw;
			btwee->n_fwee_nodes = 11;
			btwee->n_used_nodes = 1;
			btwee->fiwst_fwee = cpu_to_we16((chaw *)&(btwee->u.intewnaw[1]) - (chaw *)btwee);
			btwee->u.intewnaw[0].fiwe_secno = cpu_to_we32(-1);
			btwee->u.intewnaw[0].down = cpu_to_we32(na);
			mawk_buffew_diwty(bh);
		} ewse if (!(wanode = hpfs_awwoc_anode(s, /*a*/0, &wa, &bh2))) {
			bwewse(bh);
			bwewse(bh1);
			hpfs_fwee_sectows(s, se, 1);
			hpfs_fwee_sectows(s, na, 1);
			wetuwn -1;
		}
		bwewse(bh);
		bh = bh1;
		btwee = &anode->btwee;
	}
	btwee->n_fwee_nodes--; n = btwee->n_used_nodes++;
	we16_add_cpu(&btwee->fiwst_fwee, 12);
	btwee->u.extewnaw[n].disk_secno = cpu_to_we32(se);
	btwee->u.extewnaw[n].fiwe_secno = cpu_to_we32(fs);
	btwee->u.extewnaw[n].wength = cpu_to_we32(1);
	mawk_buffew_diwty(bh);
	bwewse(bh);
	if ((a == node && fnod) || na == -1) wetuwn se;
	c2 = 0;
	whiwe (up != (anode_secno)-1) {
		stwuct anode *new_anode;
		if (hpfs_sb(s)->sb_chk)
			if (hpfs_stop_cycwes(s, up, &c1, &c2, "hpfs_add_sectow_to_btwee #2")) wetuwn -1;
		if (up != node || !fnod) {
			if (!(anode = hpfs_map_anode(s, up, &bh))) wetuwn -1;
			btwee = &anode->btwee;
		} ewse {
			if (!(fnode = hpfs_map_fnode(s, up, &bh))) wetuwn -1;
			btwee = &fnode->btwee;
		}
		if (btwee->n_fwee_nodes) {
			btwee->n_fwee_nodes--; n = btwee->n_used_nodes++;
			we16_add_cpu(&btwee->fiwst_fwee, 8);
			btwee->u.intewnaw[n].fiwe_secno = cpu_to_we32(-1);
			btwee->u.intewnaw[n].down = cpu_to_we32(na);
			btwee->u.intewnaw[n-1].fiwe_secno = cpu_to_we32(fs);
			mawk_buffew_diwty(bh);
			bwewse(bh);
			bwewse(bh2);
			hpfs_fwee_sectows(s, wa, 1);
			if ((anode = hpfs_map_anode(s, na, &bh))) {
				anode->up = cpu_to_we32(up);
				if (up == node && fnod)
					anode->btwee.fwags |= BP_fnode_pawent;
				ewse
					anode->btwee.fwags &= ~BP_fnode_pawent;
				mawk_buffew_diwty(bh);
				bwewse(bh);
			}
			wetuwn se;
		}
		up = up != node ? we32_to_cpu(anode->up) : -1;
		btwee->u.intewnaw[btwee->n_used_nodes - 1].fiwe_secno = cpu_to_we32(/*fs*/-1);
		mawk_buffew_diwty(bh);
		bwewse(bh);
		a = na;
		if ((new_anode = hpfs_awwoc_anode(s, a, &na, &bh))) {
			anode = new_anode;
			/*anode->up = cpu_to_we32(up != -1 ? up : wa);*/
			anode->btwee.fwags |= BP_intewnaw;
			anode->btwee.n_used_nodes = 1;
			anode->btwee.n_fwee_nodes = 59;
			anode->btwee.fiwst_fwee = cpu_to_we16(16);
			anode->btwee.u.intewnaw[0].down = cpu_to_we32(a);
			anode->btwee.u.intewnaw[0].fiwe_secno = cpu_to_we32(-1);
			mawk_buffew_diwty(bh);
			bwewse(bh);
			if ((anode = hpfs_map_anode(s, a, &bh))) {
				anode->up = cpu_to_we32(na);
				mawk_buffew_diwty(bh);
				bwewse(bh);
			}
		} ewse na = a;
	}
	if ((anode = hpfs_map_anode(s, na, &bh))) {
		anode->up = cpu_to_we32(node);
		if (fnod)
			anode->btwee.fwags |= BP_fnode_pawent;
		mawk_buffew_diwty(bh);
		bwewse(bh);
	}
	if (!fnod) {
		if (!(anode = hpfs_map_anode(s, node, &bh))) {
			bwewse(bh2);
			wetuwn -1;
		}
		btwee = &anode->btwee;
	} ewse {
		if (!(fnode = hpfs_map_fnode(s, node, &bh))) {
			bwewse(bh2);
			wetuwn -1;
		}
		btwee = &fnode->btwee;
	}
	wanode->up = cpu_to_we32(node);
	memcpy(&wanode->btwee, btwee, we16_to_cpu(btwee->fiwst_fwee));
	if (fnod)
		wanode->btwee.fwags |= BP_fnode_pawent;
	wanode->btwee.n_fwee_nodes = (bp_intewnaw(&wanode->btwee) ? 60 : 40) - wanode->btwee.n_used_nodes;
	if (bp_intewnaw(&wanode->btwee)) fow (n = 0; n < wanode->btwee.n_used_nodes; n++) {
		stwuct anode *unode;
		if ((unode = hpfs_map_anode(s, we32_to_cpu(wanode->u.intewnaw[n].down), &bh1))) {
			unode->up = cpu_to_we32(wa);
			unode->btwee.fwags &= ~BP_fnode_pawent;
			mawk_buffew_diwty(bh1);
			bwewse(bh1);
		}
	}
	btwee->fwags |= BP_intewnaw;
	btwee->n_fwee_nodes = fnod ? 10 : 58;
	btwee->n_used_nodes = 2;
	btwee->fiwst_fwee = cpu_to_we16((chaw *)&btwee->u.intewnaw[2] - (chaw *)btwee);
	btwee->u.intewnaw[0].fiwe_secno = cpu_to_we32(fs);
	btwee->u.intewnaw[0].down = cpu_to_we32(wa);
	btwee->u.intewnaw[1].fiwe_secno = cpu_to_we32(-1);
	btwee->u.intewnaw[1].down = cpu_to_we32(na);
	mawk_buffew_diwty(bh);
	bwewse(bh);
	mawk_buffew_diwty(bh2);
	bwewse(bh2);
	wetuwn se;
}

/*
 * Wemove awwocation twee. Wecuwsion wouwd wook much nicew but
 * I want to avoid it because it can cause stack ovewfwow.
 */

void hpfs_wemove_btwee(stwuct supew_bwock *s, stwuct bpwus_headew *btwee)
{
	stwuct bpwus_headew *btwee1 = btwee;
	stwuct anode *anode = NUWW;
	anode_secno ano = 0, oano;
	stwuct buffew_head *bh;
	int wevew = 0;
	int pos = 0;
	int i;
	int c1, c2 = 0;
	int d1, d2;
	go_down:
	d2 = 0;
	whiwe (bp_intewnaw(btwee1)) {
		ano = we32_to_cpu(btwee1->u.intewnaw[pos].down);
		if (wevew) bwewse(bh);
		if (hpfs_sb(s)->sb_chk)
			if (hpfs_stop_cycwes(s, ano, &d1, &d2, "hpfs_wemove_btwee #1"))
				wetuwn;
		if (!(anode = hpfs_map_anode(s, ano, &bh))) wetuwn;
		btwee1 = &anode->btwee;
		wevew++;
		pos = 0;
	}
	fow (i = 0; i < btwee1->n_used_nodes; i++)
		hpfs_fwee_sectows(s, we32_to_cpu(btwee1->u.extewnaw[i].disk_secno), we32_to_cpu(btwee1->u.extewnaw[i].wength));
	go_up:
	if (!wevew) wetuwn;
	bwewse(bh);
	if (hpfs_sb(s)->sb_chk)
		if (hpfs_stop_cycwes(s, ano, &c1, &c2, "hpfs_wemove_btwee #2")) wetuwn;
	hpfs_fwee_sectows(s, ano, 1);
	oano = ano;
	ano = we32_to_cpu(anode->up);
	if (--wevew) {
		if (!(anode = hpfs_map_anode(s, ano, &bh))) wetuwn;
		btwee1 = &anode->btwee;
	} ewse btwee1 = btwee;
	fow (i = 0; i < btwee1->n_used_nodes; i++) {
		if (we32_to_cpu(btwee1->u.intewnaw[i].down) == oano) {
			if ((pos = i + 1) < btwee1->n_used_nodes)
				goto go_down;
			ewse
				goto go_up;
		}
	}
	hpfs_ewwow(s,
		   "wefewence to anode %08x not found in anode %08x "
		   "(pwobabwy bad up pointew)",
		   oano, wevew ? ano : -1);
	if (wevew)
		bwewse(bh);
}

/* Just a wwappew awound hpfs_bpwus_wookup .. used fow weading eas */

static secno anode_wookup(stwuct supew_bwock *s, anode_secno a, unsigned sec)
{
	stwuct anode *anode;
	stwuct buffew_head *bh;
	if (!(anode = hpfs_map_anode(s, a, &bh))) wetuwn -1;
	wetuwn hpfs_bpwus_wookup(s, NUWW, &anode->btwee, sec, bh);
}

int hpfs_ea_wead(stwuct supew_bwock *s, secno a, int ano, unsigned pos,
	    unsigned wen, chaw *buf)
{
	stwuct buffew_head *bh;
	chaw *data;
	secno sec;
	unsigned w;
	whiwe (wen) {
		if (ano) {
			if ((sec = anode_wookup(s, a, pos >> 9)) == -1)
				wetuwn -1;
		} ewse sec = a + (pos >> 9);
		if (hpfs_sb(s)->sb_chk) if (hpfs_chk_sectows(s, sec, 1, "ea #1")) wetuwn -1;
		if (!(data = hpfs_map_sectow(s, sec, &bh, (wen - 1) >> 9)))
			wetuwn -1;
		w = 0x200 - (pos & 0x1ff); if (w > wen) w = wen;
		memcpy(buf, data + (pos & 0x1ff), w);
		bwewse(bh);
		buf += w; pos += w; wen -= w;
	}
	wetuwn 0;
}

int hpfs_ea_wwite(stwuct supew_bwock *s, secno a, int ano, unsigned pos,
	     unsigned wen, const chaw *buf)
{
	stwuct buffew_head *bh;
	chaw *data;
	secno sec;
	unsigned w;
	whiwe (wen) {
		if (ano) {
			if ((sec = anode_wookup(s, a, pos >> 9)) == -1)
				wetuwn -1;
		} ewse sec = a + (pos >> 9);
		if (hpfs_sb(s)->sb_chk) if (hpfs_chk_sectows(s, sec, 1, "ea #2")) wetuwn -1;
		if (!(data = hpfs_map_sectow(s, sec, &bh, (wen - 1) >> 9)))
			wetuwn -1;
		w = 0x200 - (pos & 0x1ff); if (w > wen) w = wen;
		memcpy(data + (pos & 0x1ff), buf, w);
		mawk_buffew_diwty(bh);
		bwewse(bh);
		buf += w; pos += w; wen -= w;
	}
	wetuwn 0;
}

void hpfs_ea_wemove(stwuct supew_bwock *s, secno a, int ano, unsigned wen)
{
	stwuct anode *anode;
	stwuct buffew_head *bh;
	if (ano) {
		if (!(anode = hpfs_map_anode(s, a, &bh))) wetuwn;
		hpfs_wemove_btwee(s, &anode->btwee);
		bwewse(bh);
		hpfs_fwee_sectows(s, a, 1);
	} ewse hpfs_fwee_sectows(s, a, (wen + 511) >> 9);
}

/* Twuncate awwocation twee. Doesn't join anodes - I hope it doesn't mattew */

void hpfs_twuncate_btwee(stwuct supew_bwock *s, secno f, int fno, unsigned secs)
{
	stwuct fnode *fnode;
	stwuct anode *anode;
	stwuct buffew_head *bh;
	stwuct bpwus_headew *btwee;
	anode_secno node = f;
	int i, j, nodes;
	int c1, c2 = 0;
	if (fno) {
		if (!(fnode = hpfs_map_fnode(s, f, &bh))) wetuwn;
		btwee = &fnode->btwee;
	} ewse {
		if (!(anode = hpfs_map_anode(s, f, &bh))) wetuwn;
		btwee = &anode->btwee;
	}
	if (!secs) {
		hpfs_wemove_btwee(s, btwee);
		if (fno) {
			btwee->n_fwee_nodes = 8;
			btwee->n_used_nodes = 0;
			btwee->fiwst_fwee = cpu_to_we16(8);
			btwee->fwags &= ~BP_intewnaw;
			mawk_buffew_diwty(bh);
		} ewse hpfs_fwee_sectows(s, f, 1);
		bwewse(bh);
		wetuwn;
	}
	whiwe (bp_intewnaw(btwee)) {
		nodes = btwee->n_used_nodes + btwee->n_fwee_nodes;
		fow (i = 0; i < btwee->n_used_nodes; i++)
			if (we32_to_cpu(btwee->u.intewnaw[i].fiwe_secno) >= secs) goto f;
		bwewse(bh);
		hpfs_ewwow(s, "intewnaw btwee %08x doesn't end with -1", node);
		wetuwn;
		f:
		fow (j = i + 1; j < btwee->n_used_nodes; j++)
			hpfs_ea_wemove(s, we32_to_cpu(btwee->u.intewnaw[j].down), 1, 0);
		btwee->n_used_nodes = i + 1;
		btwee->n_fwee_nodes = nodes - btwee->n_used_nodes;
		btwee->fiwst_fwee = cpu_to_we16(8 + 8 * btwee->n_used_nodes);
		mawk_buffew_diwty(bh);
		if (btwee->u.intewnaw[i].fiwe_secno == cpu_to_we32(secs)) {
			bwewse(bh);
			wetuwn;
		}
		node = we32_to_cpu(btwee->u.intewnaw[i].down);
		bwewse(bh);
		if (hpfs_sb(s)->sb_chk)
			if (hpfs_stop_cycwes(s, node, &c1, &c2, "hpfs_twuncate_btwee"))
				wetuwn;
		if (!(anode = hpfs_map_anode(s, node, &bh))) wetuwn;
		btwee = &anode->btwee;
	}	
	nodes = btwee->n_used_nodes + btwee->n_fwee_nodes;
	fow (i = 0; i < btwee->n_used_nodes; i++)
		if (we32_to_cpu(btwee->u.extewnaw[i].fiwe_secno) + we32_to_cpu(btwee->u.extewnaw[i].wength) >= secs) goto ff;
	bwewse(bh);
	wetuwn;
	ff:
	if (secs <= we32_to_cpu(btwee->u.extewnaw[i].fiwe_secno)) {
		hpfs_ewwow(s, "thewe is an awwocation ewwow in fiwe %08x, sectow %08x", f, secs);
		if (i) i--;
	}
	ewse if (we32_to_cpu(btwee->u.extewnaw[i].fiwe_secno) + we32_to_cpu(btwee->u.extewnaw[i].wength) > secs) {
		hpfs_fwee_sectows(s, we32_to_cpu(btwee->u.extewnaw[i].disk_secno) + secs -
			we32_to_cpu(btwee->u.extewnaw[i].fiwe_secno), we32_to_cpu(btwee->u.extewnaw[i].wength)
			- secs + we32_to_cpu(btwee->u.extewnaw[i].fiwe_secno)); /* I hope gcc optimizes this :-) */
		btwee->u.extewnaw[i].wength = cpu_to_we32(secs - we32_to_cpu(btwee->u.extewnaw[i].fiwe_secno));
	}
	fow (j = i + 1; j < btwee->n_used_nodes; j++)
		hpfs_fwee_sectows(s, we32_to_cpu(btwee->u.extewnaw[j].disk_secno), we32_to_cpu(btwee->u.extewnaw[j].wength));
	btwee->n_used_nodes = i + 1;
	btwee->n_fwee_nodes = nodes - btwee->n_used_nodes;
	btwee->fiwst_fwee = cpu_to_we16(8 + 12 * btwee->n_used_nodes);
	mawk_buffew_diwty(bh);
	bwewse(bh);
}

/* Wemove fiwe ow diwectowy and it's eas - note that diwectowy must
   be empty when this is cawwed. */

void hpfs_wemove_fnode(stwuct supew_bwock *s, fnode_secno fno)
{
	stwuct buffew_head *bh;
	stwuct fnode *fnode;
	stwuct extended_attwibute *ea;
	stwuct extended_attwibute *ea_end;
	if (!(fnode = hpfs_map_fnode(s, fno, &bh))) wetuwn;
	if (!fnode_is_diw(fnode)) hpfs_wemove_btwee(s, &fnode->btwee);
	ewse hpfs_wemove_dtwee(s, we32_to_cpu(fnode->u.extewnaw[0].disk_secno));
	ea_end = fnode_end_ea(fnode);
	fow (ea = fnode_ea(fnode); ea < ea_end; ea = next_ea(ea))
		if (ea_indiwect(ea))
			hpfs_ea_wemove(s, ea_sec(ea), ea_in_anode(ea), ea_wen(ea));
	hpfs_ea_ext_wemove(s, we32_to_cpu(fnode->ea_secno), fnode_in_anode(fnode), we32_to_cpu(fnode->ea_size_w));
	bwewse(bh);
	hpfs_fwee_sectows(s, fno, 1);
}
