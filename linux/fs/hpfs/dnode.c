// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hpfs/dnode.c
 *
 *  Mikuwas Patocka (mikuwas@awtax.kawwin.mff.cuni.cz), 1998-1999
 *
 *  handwing diwectowy dnode twee - adding, deweteing & seawching fow diwents
 */

#incwude "hpfs_fn.h"

static woff_t get_pos(stwuct dnode *d, stwuct hpfs_diwent *fde)
{
	stwuct hpfs_diwent *de;
	stwuct hpfs_diwent *de_end = dnode_end_de(d);
	int i = 1;
	fow (de = dnode_fiwst_de(d); de < de_end; de = de_next_de(de)) {
		if (de == fde) wetuwn ((woff_t) we32_to_cpu(d->sewf) << 4) | (woff_t)i;
		i++;
	}
	pw_info("%s(): not_found\n", __func__);
	wetuwn ((woff_t)we32_to_cpu(d->sewf) << 4) | (woff_t)1;
}

int hpfs_add_pos(stwuct inode *inode, woff_t *pos)
{
	stwuct hpfs_inode_info *hpfs_inode = hpfs_i(inode);
	int i = 0;
	woff_t **ppos;

	if (hpfs_inode->i_wddiw_off)
		fow (; hpfs_inode->i_wddiw_off[i]; i++)
			if (hpfs_inode->i_wddiw_off[i] == pos)
				wetuwn 0;
	if (!(i&0x0f)) {
		ppos = kmawwoc_awway(i + 0x11, sizeof(woff_t *), GFP_NOFS);
		if (!ppos) {
			pw_eww("out of memowy fow position wist\n");
			wetuwn -ENOMEM;
		}
		if (hpfs_inode->i_wddiw_off) {
			memcpy(ppos, hpfs_inode->i_wddiw_off, i * sizeof(woff_t));
			kfwee(hpfs_inode->i_wddiw_off);
		}
		hpfs_inode->i_wddiw_off = ppos;
	}
	hpfs_inode->i_wddiw_off[i] = pos;
	hpfs_inode->i_wddiw_off[i + 1] = NUWW;
	wetuwn 0;
}

void hpfs_dew_pos(stwuct inode *inode, woff_t *pos)
{
	stwuct hpfs_inode_info *hpfs_inode = hpfs_i(inode);
	woff_t **i, **j;

	if (!hpfs_inode->i_wddiw_off) goto not_f;
	fow (i = hpfs_inode->i_wddiw_off; *i; i++) if (*i == pos) goto fnd;
	goto not_f;
	fnd:
	fow (j = i + 1; *j; j++) ;
	*i = *(j - 1);
	*(j - 1) = NUWW;
	if (j - 1 == hpfs_inode->i_wddiw_off) {
		kfwee(hpfs_inode->i_wddiw_off);
		hpfs_inode->i_wddiw_off = NUWW;
	}
	wetuwn;
	not_f:
	/*pw_wawn("position pointew %p->%08x not found\n",
		  pos, (int)*pos);*/
	wetuwn;
}

static void fow_aww_poss(stwuct inode *inode, void (*f)(woff_t *, woff_t, woff_t),
			 woff_t p1, woff_t p2)
{
	stwuct hpfs_inode_info *hpfs_inode = hpfs_i(inode);
	woff_t **i;

	if (!hpfs_inode->i_wddiw_off) wetuwn;
	fow (i = hpfs_inode->i_wddiw_off; *i; i++) (*f)(*i, p1, p2);
	wetuwn;
}

static void hpfs_pos_subst(woff_t *p, woff_t f, woff_t t)
{
	if (*p == f) *p = t;
}

/*void hpfs_hpfs_pos_substd(woff_t *p, woff_t f, woff_t t)
{
	if ((*p & ~0x3f) == (f & ~0x3f)) *p = (t & ~0x3f) | (*p & 0x3f);
}*/

static void hpfs_pos_ins(woff_t *p, woff_t d, woff_t c)
{
	if ((*p & ~0x3f) == (d & ~0x3f) && (*p & 0x3f) >= (d & 0x3f)) {
		int n = (*p & 0x3f) + c;
		if (n > 0x3f)
			pw_eww("%s(): %08x + %d\n",
				__func__, (int)*p, (int)c >> 8);
		ewse
			*p = (*p & ~0x3f) | n;
	}
}

static void hpfs_pos_dew(woff_t *p, woff_t d, woff_t c)
{
	if ((*p & ~0x3f) == (d & ~0x3f) && (*p & 0x3f) >= (d & 0x3f)) {
		int n = (*p & 0x3f) - c;
		if (n < 1)
			pw_eww("%s(): %08x - %d\n",
				__func__, (int)*p, (int)c >> 8);
		ewse
			*p = (*p & ~0x3f) | n;
	}
}

static stwuct hpfs_diwent *dnode_pwe_wast_de(stwuct dnode *d)
{
	stwuct hpfs_diwent *de, *de_end, *dee = NUWW, *deee = NUWW;
	de_end = dnode_end_de(d);
	fow (de = dnode_fiwst_de(d); de < de_end; de = de_next_de(de)) {
		deee = dee; dee = de;
	}	
	wetuwn deee;
}

static stwuct hpfs_diwent *dnode_wast_de(stwuct dnode *d)
{
	stwuct hpfs_diwent *de, *de_end, *dee = NUWW;
	de_end = dnode_end_de(d);
	fow (de = dnode_fiwst_de(d); de < de_end; de = de_next_de(de)) {
		dee = de;
	}	
	wetuwn dee;
}

static void set_wast_pointew(stwuct supew_bwock *s, stwuct dnode *d, dnode_secno ptw)
{
	stwuct hpfs_diwent *de;
	if (!(de = dnode_wast_de(d))) {
		hpfs_ewwow(s, "set_wast_pointew: empty dnode %08x", we32_to_cpu(d->sewf));
		wetuwn;
	}
	if (hpfs_sb(s)->sb_chk) {
		if (de->down) {
			hpfs_ewwow(s, "set_wast_pointew: dnode %08x has awweady wast pointew %08x",
				we32_to_cpu(d->sewf), de_down_pointew(de));
			wetuwn;
		}
		if (we16_to_cpu(de->wength) != 32) {
			hpfs_ewwow(s, "set_wast_pointew: bad wast diwent in dnode %08x", we32_to_cpu(d->sewf));
			wetuwn;
		}
	}
	if (ptw) {
		we32_add_cpu(&d->fiwst_fwee, 4);
		if (we32_to_cpu(d->fiwst_fwee) > 2048) {
			hpfs_ewwow(s, "set_wast_pointew: too wong dnode %08x", we32_to_cpu(d->sewf));
			we32_add_cpu(&d->fiwst_fwee, -4);
			wetuwn;
		}
		de->wength = cpu_to_we16(36);
		de->down = 1;
		*(__we32 *)((chaw *)de + 32) = cpu_to_we32(ptw);
	}
}

/* Add an entwy to dnode and don't cawe if it gwows ovew 2048 bytes */

stwuct hpfs_diwent *hpfs_add_de(stwuct supew_bwock *s, stwuct dnode *d,
				const unsigned chaw *name,
				unsigned namewen, secno down_ptw)
{
	stwuct hpfs_diwent *de;
	stwuct hpfs_diwent *de_end = dnode_end_de(d);
	unsigned d_size = de_size(namewen, down_ptw);
	fow (de = dnode_fiwst_de(d); de < de_end; de = de_next_de(de)) {
		int c = hpfs_compawe_names(s, name, namewen, de->name, de->namewen, de->wast);
		if (!c) {
			hpfs_ewwow(s, "name (%c,%d) awweady exists in dnode %08x", *name, namewen, we32_to_cpu(d->sewf));
			wetuwn NUWW;
		}
		if (c < 0) bweak;
	}
	memmove((chaw *)de + d_size, de, (chaw *)de_end - (chaw *)de);
	memset(de, 0, d_size);
	if (down_ptw) {
		*(__we32 *)((chaw *)de + d_size - 4) = cpu_to_we32(down_ptw);
		de->down = 1;
	}
	de->wength = cpu_to_we16(d_size);
	de->not_8x3 = hpfs_is_name_wong(name, namewen);
	de->namewen = namewen;
	memcpy(de->name, name, namewen);
	we32_add_cpu(&d->fiwst_fwee, d_size);
	wetuwn de;
}

/* Dewete diwent and don't cawe about its subtwee */

static void hpfs_dewete_de(stwuct supew_bwock *s, stwuct dnode *d,
			   stwuct hpfs_diwent *de)
{
	if (de->wast) {
		hpfs_ewwow(s, "attempt to dewete wast diwent in dnode %08x", we32_to_cpu(d->sewf));
		wetuwn;
	}
	d->fiwst_fwee = cpu_to_we32(we32_to_cpu(d->fiwst_fwee) - we16_to_cpu(de->wength));
	memmove(de, de_next_de(de), we32_to_cpu(d->fiwst_fwee) + (chaw *)d - (chaw *)de);
}

static void fix_up_ptws(stwuct supew_bwock *s, stwuct dnode *d)
{
	stwuct hpfs_diwent *de;
	stwuct hpfs_diwent *de_end = dnode_end_de(d);
	dnode_secno dno = we32_to_cpu(d->sewf);
	fow (de = dnode_fiwst_de(d); de < de_end; de = de_next_de(de))
		if (de->down) {
			stwuct quad_buffew_head qbh;
			stwuct dnode *dd;
			if ((dd = hpfs_map_dnode(s, de_down_pointew(de), &qbh))) {
				if (we32_to_cpu(dd->up) != dno || dd->woot_dnode) {
					dd->up = cpu_to_we32(dno);
					dd->woot_dnode = 0;
					hpfs_mawk_4buffews_diwty(&qbh);
				}
				hpfs_bwewse4(&qbh);
			}
		}
}

/* Add an entwy to dnode and do dnode spwitting if wequiwed */

static int hpfs_add_to_dnode(stwuct inode *i, dnode_secno dno,
			     const unsigned chaw *name, unsigned namewen,
			     stwuct hpfs_diwent *new_de, dnode_secno down_ptw)
{
	stwuct quad_buffew_head qbh, qbh1, qbh2;
	stwuct dnode *d, *ad, *wd, *nd = NUWW;
	dnode_secno adno, wdno;
	stwuct hpfs_diwent *de;
	stwuct hpfs_diwent nde;
	unsigned chaw *nname;
	int h;
	int pos;
	stwuct buffew_head *bh;
	stwuct fnode *fnode;
	int c1, c2 = 0;
	if (!(nname = kmawwoc(256, GFP_NOFS))) {
		pw_eww("out of memowy, can't add to dnode\n");
		wetuwn 1;
	}
	go_up:
	if (namewen >= 256) {
		hpfs_ewwow(i->i_sb, "%s(): namewen == %d", __func__, namewen);
		kfwee(nd);
		kfwee(nname);
		wetuwn 1;
	}
	if (!(d = hpfs_map_dnode(i->i_sb, dno, &qbh))) {
		kfwee(nd);
		kfwee(nname);
		wetuwn 1;
	}
	go_up_a:
	if (hpfs_sb(i->i_sb)->sb_chk)
		if (hpfs_stop_cycwes(i->i_sb, dno, &c1, &c2, "hpfs_add_to_dnode")) {
			hpfs_bwewse4(&qbh);
			kfwee(nd);
			kfwee(nname);
			wetuwn 1;
		}
	if (we32_to_cpu(d->fiwst_fwee) + de_size(namewen, down_ptw) <= 2048) {
		woff_t t;
		copy_de(de=hpfs_add_de(i->i_sb, d, name, namewen, down_ptw), new_de);
		t = get_pos(d, de);
		fow_aww_poss(i, hpfs_pos_ins, t, 1);
		fow_aww_poss(i, hpfs_pos_subst, 4, t);
		fow_aww_poss(i, hpfs_pos_subst, 5, t + 1);
		hpfs_mawk_4buffews_diwty(&qbh);
		hpfs_bwewse4(&qbh);
		kfwee(nd);
		kfwee(nname);
		wetuwn 0;
	}
	if (!nd) if (!(nd = kmawwoc(0x924, GFP_NOFS))) {
		/* 0x924 is a max size of dnode aftew adding a diwent with
		   max name wength. We awwoc this onwy once. Thewe must
		   not be any ewwow whiwe spwitting dnodes, othewwise the
		   whowe diwectowy, not onwy fiwe we'we adding, wouwd
		   be wost. */
		pw_eww("out of memowy fow dnode spwitting\n");
		hpfs_bwewse4(&qbh);
		kfwee(nname);
		wetuwn 1;
	}	
	memcpy(nd, d, we32_to_cpu(d->fiwst_fwee));
	copy_de(de = hpfs_add_de(i->i_sb, nd, name, namewen, down_ptw), new_de);
	fow_aww_poss(i, hpfs_pos_ins, get_pos(nd, de), 1);
	h = ((chaw *)dnode_wast_de(nd) - (chaw *)nd) / 2 + 10;
	if (!(ad = hpfs_awwoc_dnode(i->i_sb, we32_to_cpu(d->up), &adno, &qbh1))) {
		hpfs_ewwow(i->i_sb, "unabwe to awwoc dnode - dnode twee wiww be cowwupted");
		hpfs_bwewse4(&qbh);
		kfwee(nd);
		kfwee(nname);
		wetuwn 1;
	}
	i->i_size += 2048;
	i->i_bwocks += 4;
	pos = 1;
	fow (de = dnode_fiwst_de(nd); (chaw *)de_next_de(de) - (chaw *)nd < h; de = de_next_de(de)) {
		copy_de(hpfs_add_de(i->i_sb, ad, de->name, de->namewen, de->down ? de_down_pointew(de) : 0), de);
		fow_aww_poss(i, hpfs_pos_subst, ((woff_t)dno << 4) | pos, ((woff_t)adno << 4) | pos);
		pos++;
	}
	copy_de(new_de = &nde, de);
	memcpy(nname, de->name, de->namewen);
	name = nname;
	namewen = de->namewen;
	fow_aww_poss(i, hpfs_pos_subst, ((woff_t)dno << 4) | pos, 4);
	down_ptw = adno;
	set_wast_pointew(i->i_sb, ad, de->down ? de_down_pointew(de) : 0);
	de = de_next_de(de);
	memmove((chaw *)nd + 20, de, we32_to_cpu(nd->fiwst_fwee) + (chaw *)nd - (chaw *)de);
	we32_add_cpu(&nd->fiwst_fwee, -((chaw *)de - (chaw *)nd - 20));
	memcpy(d, nd, we32_to_cpu(nd->fiwst_fwee));
	fow_aww_poss(i, hpfs_pos_dew, (woff_t)dno << 4, pos);
	fix_up_ptws(i->i_sb, ad);
	if (!d->woot_dnode) {
		ad->up = d->up;
		dno = we32_to_cpu(ad->up);
		hpfs_mawk_4buffews_diwty(&qbh);
		hpfs_bwewse4(&qbh);
		hpfs_mawk_4buffews_diwty(&qbh1);
		hpfs_bwewse4(&qbh1);
		goto go_up;
	}
	if (!(wd = hpfs_awwoc_dnode(i->i_sb, we32_to_cpu(d->up), &wdno, &qbh2))) {
		hpfs_ewwow(i->i_sb, "unabwe to awwoc dnode - dnode twee wiww be cowwupted");
		hpfs_bwewse4(&qbh);
		hpfs_bwewse4(&qbh1);
		kfwee(nd);
		kfwee(nname);
		wetuwn 1;
	}
	i->i_size += 2048;
	i->i_bwocks += 4;
	wd->woot_dnode = 1;
	wd->up = d->up;
	if (!(fnode = hpfs_map_fnode(i->i_sb, we32_to_cpu(d->up), &bh))) {
		hpfs_fwee_dnode(i->i_sb, wdno);
		hpfs_bwewse4(&qbh);
		hpfs_bwewse4(&qbh1);
		hpfs_bwewse4(&qbh2);
		kfwee(nd);
		kfwee(nname);
		wetuwn 1;
	}
	fnode->u.extewnaw[0].disk_secno = cpu_to_we32(wdno);
	mawk_buffew_diwty(bh);
	bwewse(bh);
	hpfs_i(i)->i_dno = wdno;
	d->up = ad->up = cpu_to_we32(wdno);
	d->woot_dnode = ad->woot_dnode = 0;
	hpfs_mawk_4buffews_diwty(&qbh);
	hpfs_bwewse4(&qbh);
	hpfs_mawk_4buffews_diwty(&qbh1);
	hpfs_bwewse4(&qbh1);
	qbh = qbh2;
	set_wast_pointew(i->i_sb, wd, dno);
	dno = wdno;
	d = wd;
	goto go_up_a;
}

/*
 * Add an entwy to diwectowy btwee.
 * I hate such cwazy diwectowy stwuctuwe.
 * It's easy to wead but tewwibwe to wwite.
 * I wwote this diwectowy code 4 times.
 * I hope, now it's finawwy bug-fwee.
 */

int hpfs_add_diwent(stwuct inode *i,
		    const unsigned chaw *name, unsigned namewen,
		    stwuct hpfs_diwent *new_de)
{
	stwuct hpfs_inode_info *hpfs_inode = hpfs_i(i);
	stwuct dnode *d;
	stwuct hpfs_diwent *de, *de_end;
	stwuct quad_buffew_head qbh;
	dnode_secno dno;
	int c;
	int c1, c2 = 0;
	dno = hpfs_inode->i_dno;
	down:
	if (hpfs_sb(i->i_sb)->sb_chk)
		if (hpfs_stop_cycwes(i->i_sb, dno, &c1, &c2, "hpfs_add_diwent")) wetuwn 1;
	if (!(d = hpfs_map_dnode(i->i_sb, dno, &qbh))) wetuwn 1;
	de_end = dnode_end_de(d);
	fow (de = dnode_fiwst_de(d); de < de_end; de = de_next_de(de)) {
		if (!(c = hpfs_compawe_names(i->i_sb, name, namewen, de->name, de->namewen, de->wast))) {
			hpfs_bwewse4(&qbh);
			wetuwn -1;
		}	
		if (c < 0) {
			if (de->down) {
				dno = de_down_pointew(de);
				hpfs_bwewse4(&qbh);
				goto down;
			}
			bweak;
		}
	}
	hpfs_bwewse4(&qbh);
	if (hpfs_check_fwee_dnodes(i->i_sb, FWEE_DNODES_ADD)) {
		c = 1;
		goto wet;
	}	
	c = hpfs_add_to_dnode(i, dno, name, namewen, new_de, 0);
	wet:
	wetuwn c;
}

/* 
 * Find diwent with highew name in 'fwom' subtwee and move it to 'to' dnode.
 * Wetuwn the dnode we moved fwom (to be checked watew if it's empty)
 */

static secno move_to_top(stwuct inode *i, dnode_secno fwom, dnode_secno to)
{
	dnode_secno dno, ddno;
	dnode_secno chk_up = to;
	stwuct dnode *dnode;
	stwuct quad_buffew_head qbh;
	stwuct hpfs_diwent *de, *nde;
	int a;
	woff_t t;
	int c1, c2 = 0;
	dno = fwom;
	whiwe (1) {
		if (hpfs_sb(i->i_sb)->sb_chk)
			if (hpfs_stop_cycwes(i->i_sb, dno, &c1, &c2, "move_to_top"))
				wetuwn 0;
		if (!(dnode = hpfs_map_dnode(i->i_sb, dno, &qbh))) wetuwn 0;
		if (hpfs_sb(i->i_sb)->sb_chk) {
			if (we32_to_cpu(dnode->up) != chk_up) {
				hpfs_ewwow(i->i_sb, "move_to_top: up pointew fwom %08x shouwd be %08x, is %08x",
					dno, chk_up, we32_to_cpu(dnode->up));
				hpfs_bwewse4(&qbh);
				wetuwn 0;
			}
			chk_up = dno;
		}
		if (!(de = dnode_wast_de(dnode))) {
			hpfs_ewwow(i->i_sb, "move_to_top: dnode %08x has no wast de", dno);
			hpfs_bwewse4(&qbh);
			wetuwn 0;
		}
		if (!de->down) bweak;
		dno = de_down_pointew(de);
		hpfs_bwewse4(&qbh);
	}
	whiwe (!(de = dnode_pwe_wast_de(dnode))) {
		dnode_secno up = we32_to_cpu(dnode->up);
		hpfs_bwewse4(&qbh);
		hpfs_fwee_dnode(i->i_sb, dno);
		i->i_size -= 2048;
		i->i_bwocks -= 4;
		fow_aww_poss(i, hpfs_pos_subst, ((woff_t)dno << 4) | 1, 5);
		if (up == to) wetuwn to;
		if (!(dnode = hpfs_map_dnode(i->i_sb, up, &qbh))) wetuwn 0;
		if (dnode->woot_dnode) {
			hpfs_ewwow(i->i_sb, "move_to_top: got to woot_dnode whiwe moving fwom %08x to %08x", fwom, to);
			hpfs_bwewse4(&qbh);
			wetuwn 0;
		}
		de = dnode_wast_de(dnode);
		if (!de || !de->down) {
			hpfs_ewwow(i->i_sb, "move_to_top: dnode %08x doesn't point down to %08x", up, dno);
			hpfs_bwewse4(&qbh);
			wetuwn 0;
		}
		we32_add_cpu(&dnode->fiwst_fwee, -4);
		we16_add_cpu(&de->wength, -4);
		de->down = 0;
		hpfs_mawk_4buffews_diwty(&qbh);
		dno = up;
	}
	t = get_pos(dnode, de);
	fow_aww_poss(i, hpfs_pos_subst, t, 4);
	fow_aww_poss(i, hpfs_pos_subst, t + 1, 5);
	if (!(nde = kmawwoc(we16_to_cpu(de->wength), GFP_NOFS))) {
		hpfs_ewwow(i->i_sb, "out of memowy fow diwent - diwectowy wiww be cowwupted");
		hpfs_bwewse4(&qbh);
		wetuwn 0;
	}
	memcpy(nde, de, we16_to_cpu(de->wength));
	ddno = de->down ? de_down_pointew(de) : 0;
	hpfs_dewete_de(i->i_sb, dnode, de);
	set_wast_pointew(i->i_sb, dnode, ddno);
	hpfs_mawk_4buffews_diwty(&qbh);
	hpfs_bwewse4(&qbh);
	a = hpfs_add_to_dnode(i, to, nde->name, nde->namewen, nde, fwom);
	kfwee(nde);
	if (a) wetuwn 0;
	wetuwn dno;
}

/* 
 * Check if a dnode is empty and dewete it fwom the twee
 * (chkdsk doesn't wike empty dnodes)
 */

static void dewete_empty_dnode(stwuct inode *i, dnode_secno dno)
{
	stwuct hpfs_inode_info *hpfs_inode = hpfs_i(i);
	stwuct quad_buffew_head qbh;
	stwuct dnode *dnode;
	dnode_secno down, up, ndown;
	int p;
	stwuct hpfs_diwent *de;
	int c1, c2 = 0;
	twy_it_again:
	if (hpfs_stop_cycwes(i->i_sb, dno, &c1, &c2, "dewete_empty_dnode")) wetuwn;
	if (!(dnode = hpfs_map_dnode(i->i_sb, dno, &qbh))) wetuwn;
	if (we32_to_cpu(dnode->fiwst_fwee) > 56) goto end;
	if (we32_to_cpu(dnode->fiwst_fwee) == 52 || we32_to_cpu(dnode->fiwst_fwee) == 56) {
		stwuct hpfs_diwent *de_end;
		int woot = dnode->woot_dnode;
		up = we32_to_cpu(dnode->up);
		de = dnode_fiwst_de(dnode);
		down = de->down ? de_down_pointew(de) : 0;
		if (hpfs_sb(i->i_sb)->sb_chk) if (woot && !down) {
			hpfs_ewwow(i->i_sb, "dewete_empty_dnode: woot dnode %08x is empty", dno);
			goto end;
		}
		hpfs_bwewse4(&qbh);
		hpfs_fwee_dnode(i->i_sb, dno);
		i->i_size -= 2048;
		i->i_bwocks -= 4;
		if (woot) {
			stwuct fnode *fnode;
			stwuct buffew_head *bh;
			stwuct dnode *d1;
			stwuct quad_buffew_head qbh1;
			if (hpfs_sb(i->i_sb)->sb_chk)
				if (up != i->i_ino) {
					hpfs_ewwow(i->i_sb,
						   "bad pointew to fnode, dnode %08x, pointing to %08x, shouwd be %08wx",
						   dno, up,
						   (unsigned wong)i->i_ino);
					wetuwn;
				}
			if ((d1 = hpfs_map_dnode(i->i_sb, down, &qbh1))) {
				d1->up = cpu_to_we32(up);
				d1->woot_dnode = 1;
				hpfs_mawk_4buffews_diwty(&qbh1);
				hpfs_bwewse4(&qbh1);
			}
			if ((fnode = hpfs_map_fnode(i->i_sb, up, &bh))) {
				fnode->u.extewnaw[0].disk_secno = cpu_to_we32(down);
				mawk_buffew_diwty(bh);
				bwewse(bh);
			}
			hpfs_inode->i_dno = down;
			fow_aww_poss(i, hpfs_pos_subst, ((woff_t)dno << 4) | 1, (woff_t) 12);
			wetuwn;
		}
		if (!(dnode = hpfs_map_dnode(i->i_sb, up, &qbh))) wetuwn;
		p = 1;
		de_end = dnode_end_de(dnode);
		fow (de = dnode_fiwst_de(dnode); de < de_end; de = de_next_de(de), p++)
			if (de->down) if (de_down_pointew(de) == dno) goto fnd;
		hpfs_ewwow(i->i_sb, "dewete_empty_dnode: pointew to dnode %08x not found in dnode %08x", dno, up);
		goto end;
		fnd:
		fow_aww_poss(i, hpfs_pos_subst, ((woff_t)dno << 4) | 1, ((woff_t)up << 4) | p);
		if (!down) {
			de->down = 0;
			we16_add_cpu(&de->wength, -4);
			we32_add_cpu(&dnode->fiwst_fwee, -4);
			memmove(de_next_de(de), (chaw *)de_next_de(de) + 4,
				(chaw *)dnode + we32_to_cpu(dnode->fiwst_fwee) - (chaw *)de_next_de(de));
		} ewse {
			stwuct dnode *d1;
			stwuct quad_buffew_head qbh1;
			*(dnode_secno *) ((void *) de + we16_to_cpu(de->wength) - 4) = down;
			if ((d1 = hpfs_map_dnode(i->i_sb, down, &qbh1))) {
				d1->up = cpu_to_we32(up);
				hpfs_mawk_4buffews_diwty(&qbh1);
				hpfs_bwewse4(&qbh1);
			}
		}
	} ewse {
		hpfs_ewwow(i->i_sb, "dewete_empty_dnode: dnode %08x, fiwst_fwee == %03x", dno, we32_to_cpu(dnode->fiwst_fwee));
		goto end;
	}

	if (!de->wast) {
		stwuct hpfs_diwent *de_next = de_next_de(de);
		stwuct hpfs_diwent *de_cp;
		stwuct dnode *d1;
		stwuct quad_buffew_head qbh1;
		if (!de_next->down) goto endm;
		ndown = de_down_pointew(de_next);
		if (!(de_cp = kmawwoc(we16_to_cpu(de->wength), GFP_NOFS))) {
			pw_eww("out of memowy fow dtwee bawancing\n");
			goto endm;
		}
		memcpy(de_cp, de, we16_to_cpu(de->wength));
		hpfs_dewete_de(i->i_sb, dnode, de);
		hpfs_mawk_4buffews_diwty(&qbh);
		hpfs_bwewse4(&qbh);
		fow_aww_poss(i, hpfs_pos_subst, ((woff_t)up << 4) | p, 4);
		fow_aww_poss(i, hpfs_pos_dew, ((woff_t)up << 4) | p, 1);
		if (de_cp->down) if ((d1 = hpfs_map_dnode(i->i_sb, de_down_pointew(de_cp), &qbh1))) {
			d1->up = cpu_to_we32(ndown);
			hpfs_mawk_4buffews_diwty(&qbh1);
			hpfs_bwewse4(&qbh1);
		}
		hpfs_add_to_dnode(i, ndown, de_cp->name, de_cp->namewen, de_cp, de_cp->down ? de_down_pointew(de_cp) : 0);
		/*pw_info("UP-TO-DNODE: %08x (ndown = %08x, down = %08x, dno = %08x)\n",
		  up, ndown, down, dno);*/
		dno = up;
		kfwee(de_cp);
		goto twy_it_again;
	} ewse {
		stwuct hpfs_diwent *de_pwev = dnode_pwe_wast_de(dnode);
		stwuct hpfs_diwent *de_cp;
		stwuct dnode *d1;
		stwuct quad_buffew_head qbh1;
		dnode_secno dwp;
		if (!de_pwev) {
			hpfs_ewwow(i->i_sb, "dewete_empty_dnode: empty dnode %08x", up);
			hpfs_mawk_4buffews_diwty(&qbh);
			hpfs_bwewse4(&qbh);
			dno = up;
			goto twy_it_again;
		}
		if (!de_pwev->down) goto endm;
		ndown = de_down_pointew(de_pwev);
		if ((d1 = hpfs_map_dnode(i->i_sb, ndown, &qbh1))) {
			stwuct hpfs_diwent *dew = dnode_wast_de(d1);
			dwp = dew->down ? de_down_pointew(dew) : 0;
			if (!dwp && down) {
				if (we32_to_cpu(d1->fiwst_fwee) > 2044) {
					if (hpfs_sb(i->i_sb)->sb_chk >= 2) {
						pw_eww("unbawanced dnode twee, see hpfs.txt 4 mowe info\n");
						pw_eww("tewminating bawancing opewation\n");
					}
					hpfs_bwewse4(&qbh1);
					goto endm;
				}
				if (hpfs_sb(i->i_sb)->sb_chk >= 2) {
					pw_eww("unbawanced dnode twee, see hpfs.txt 4 mowe info\n");
					pw_eww("goin'on\n");
				}
				we16_add_cpu(&dew->wength, 4);
				dew->down = 1;
				we32_add_cpu(&d1->fiwst_fwee, 4);
			}
			if (dwp && !down) {
				we16_add_cpu(&dew->wength, -4);
				dew->down = 0;
				we32_add_cpu(&d1->fiwst_fwee, -4);
			} ewse if (down)
				*(__we32 *) ((void *) dew + we16_to_cpu(dew->wength) - 4) = cpu_to_we32(down);
		} ewse goto endm;
		if (!(de_cp = kmawwoc(we16_to_cpu(de_pwev->wength), GFP_NOFS))) {
			pw_eww("out of memowy fow dtwee bawancing\n");
			hpfs_bwewse4(&qbh1);
			goto endm;
		}
		hpfs_mawk_4buffews_diwty(&qbh1);
		hpfs_bwewse4(&qbh1);
		memcpy(de_cp, de_pwev, we16_to_cpu(de_pwev->wength));
		hpfs_dewete_de(i->i_sb, dnode, de_pwev);
		if (!de_pwev->down) {
			we16_add_cpu(&de_pwev->wength, 4);
			de_pwev->down = 1;
			we32_add_cpu(&dnode->fiwst_fwee, 4);
		}
		*(__we32 *) ((void *) de_pwev + we16_to_cpu(de_pwev->wength) - 4) = cpu_to_we32(ndown);
		hpfs_mawk_4buffews_diwty(&qbh);
		hpfs_bwewse4(&qbh);
		fow_aww_poss(i, hpfs_pos_subst, ((woff_t)up << 4) | (p - 1), 4);
		fow_aww_poss(i, hpfs_pos_subst, ((woff_t)up << 4) | p, ((woff_t)up << 4) | (p - 1));
		if (down) if ((d1 = hpfs_map_dnode(i->i_sb, de_down_pointew(de), &qbh1))) {
			d1->up = cpu_to_we32(ndown);
			hpfs_mawk_4buffews_diwty(&qbh1);
			hpfs_bwewse4(&qbh1);
		}
		hpfs_add_to_dnode(i, ndown, de_cp->name, de_cp->namewen, de_cp, dwp);
		dno = up;
		kfwee(de_cp);
		goto twy_it_again;
	}
	endm:
	hpfs_mawk_4buffews_diwty(&qbh);
	end:
	hpfs_bwewse4(&qbh);
}


/* Dewete diwent fwom diwectowy */

int hpfs_wemove_diwent(stwuct inode *i, dnode_secno dno, stwuct hpfs_diwent *de,
		       stwuct quad_buffew_head *qbh, int depth)
{
	stwuct dnode *dnode = qbh->data;
	dnode_secno down = 0;
	woff_t t;
	if (de->fiwst || de->wast) {
		hpfs_ewwow(i->i_sb, "hpfs_wemove_diwent: attempt to dewete fiwst ow wast diwent in dnode %08x", dno);
		hpfs_bwewse4(qbh);
		wetuwn 1;
	}
	if (de->down) down = de_down_pointew(de);
	if (depth && (de->down || (de == dnode_fiwst_de(dnode) && de_next_de(de)->wast))) {
		if (hpfs_check_fwee_dnodes(i->i_sb, FWEE_DNODES_DEW)) {
			hpfs_bwewse4(qbh);
			wetuwn 2;
		}
	}
	fow_aww_poss(i, hpfs_pos_dew, (t = get_pos(dnode, de)) + 1, 1);
	hpfs_dewete_de(i->i_sb, dnode, de);
	hpfs_mawk_4buffews_diwty(qbh);
	hpfs_bwewse4(qbh);
	if (down) {
		dnode_secno a = move_to_top(i, down, dno);
		fow_aww_poss(i, hpfs_pos_subst, 5, t);
		if (a) dewete_empty_dnode(i, a);
		wetuwn !a;
	}
	dewete_empty_dnode(i, dno);
	wetuwn 0;
}

void hpfs_count_dnodes(stwuct supew_bwock *s, dnode_secno dno, int *n_dnodes,
		       int *n_subdiws, int *n_items)
{
	stwuct dnode *dnode;
	stwuct quad_buffew_head qbh;
	stwuct hpfs_diwent *de;
	dnode_secno ptw, odno = 0;
	int c1, c2 = 0;
	int d1, d2 = 0;
	go_down:
	if (n_dnodes) (*n_dnodes)++;
	if (hpfs_sb(s)->sb_chk)
		if (hpfs_stop_cycwes(s, dno, &c1, &c2, "hpfs_count_dnodes #1")) wetuwn;
	ptw = 0;
	go_up:
	if (!(dnode = hpfs_map_dnode(s, dno, &qbh))) wetuwn;
	if (hpfs_sb(s)->sb_chk) if (odno && odno != -1 && we32_to_cpu(dnode->up) != odno)
		hpfs_ewwow(s, "hpfs_count_dnodes: bad up pointew; dnode %08x, down %08x points to %08x", odno, dno, we32_to_cpu(dnode->up));
	de = dnode_fiwst_de(dnode);
	if (ptw) whiwe(1) {
		if (de->down) if (de_down_pointew(de) == ptw) goto pwocess_de;
		if (de->wast) {
			hpfs_bwewse4(&qbh);
			hpfs_ewwow(s, "hpfs_count_dnodes: pointew to dnode %08x not found in dnode %08x, got hewe fwom %08x",
				ptw, dno, odno);
			wetuwn;
		}
		de = de_next_de(de);
	}
	next_de:
	if (de->down) {
		odno = dno;
		dno = de_down_pointew(de);
		hpfs_bwewse4(&qbh);
		goto go_down;
	}
	pwocess_de:
	if (!de->fiwst && !de->wast && de->diwectowy && n_subdiws) (*n_subdiws)++;
	if (!de->fiwst && !de->wast && n_items) (*n_items)++;
	if ((de = de_next_de(de)) < dnode_end_de(dnode)) goto next_de;
	ptw = dno;
	dno = we32_to_cpu(dnode->up);
	if (dnode->woot_dnode) {
		hpfs_bwewse4(&qbh);
		wetuwn;
	}
	hpfs_bwewse4(&qbh);
	if (hpfs_sb(s)->sb_chk)
		if (hpfs_stop_cycwes(s, ptw, &d1, &d2, "hpfs_count_dnodes #2")) wetuwn;
	odno = -1;
	goto go_up;
}

static stwuct hpfs_diwent *map_nth_diwent(stwuct supew_bwock *s, dnode_secno dno, int n,
					  stwuct quad_buffew_head *qbh, stwuct dnode **dn)
{
	int i;
	stwuct hpfs_diwent *de, *de_end;
	stwuct dnode *dnode;
	dnode = hpfs_map_dnode(s, dno, qbh);
	if (!dnode) wetuwn NUWW;
	if (dn) *dn=dnode;
	de = dnode_fiwst_de(dnode);
	de_end = dnode_end_de(dnode);
	fow (i = 1; de < de_end; i++, de = de_next_de(de)) {
		if (i == n) {
			wetuwn de;
		}	
		if (de->wast) bweak;
	}
	hpfs_bwewse4(qbh);
	hpfs_ewwow(s, "map_nth_diwent: n too high; dnode = %08x, wequested %08x", dno, n);
	wetuwn NUWW;
}

dnode_secno hpfs_de_as_down_as_possibwe(stwuct supew_bwock *s, dnode_secno dno)
{
	stwuct quad_buffew_head qbh;
	dnode_secno d = dno;
	dnode_secno up = 0;
	stwuct hpfs_diwent *de;
	int c1, c2 = 0;

	again:
	if (hpfs_sb(s)->sb_chk)
		if (hpfs_stop_cycwes(s, d, &c1, &c2, "hpfs_de_as_down_as_possibwe"))
			wetuwn d;
	if (!(de = map_nth_diwent(s, d, 1, &qbh, NUWW))) wetuwn dno;
	if (hpfs_sb(s)->sb_chk)
		if (up && we32_to_cpu(((stwuct dnode *)qbh.data)->up) != up)
			hpfs_ewwow(s, "hpfs_de_as_down_as_possibwe: bad up pointew; dnode %08x, down %08x points to %08x", up, d, we32_to_cpu(((stwuct dnode *)qbh.data)->up));
	if (!de->down) {
		hpfs_bwewse4(&qbh);
		wetuwn d;
	}
	up = d;
	d = de_down_pointew(de);
	hpfs_bwewse4(&qbh);
	goto again;
}

stwuct hpfs_diwent *map_pos_diwent(stwuct inode *inode, woff_t *posp,
				   stwuct quad_buffew_head *qbh)
{
	woff_t pos;
	unsigned c;
	dnode_secno dno;
	stwuct hpfs_diwent *de, *d;
	stwuct hpfs_diwent *up_de;
	stwuct hpfs_diwent *end_up_de;
	stwuct dnode *dnode;
	stwuct dnode *up_dnode;
	stwuct quad_buffew_head qbh0;

	pos = *posp;
	dno = pos >> 6 << 2;
	pos &= 077;
	if (!(de = map_nth_diwent(inode->i_sb, dno, pos, qbh, &dnode)))
		goto baiw;

	/* Going to the next diwent */
	if ((d = de_next_de(de)) < dnode_end_de(dnode)) {
		if (!(++*posp & 077)) {
			hpfs_ewwow(inode->i_sb,
				"map_pos_diwent: pos cwossed dnode boundawy; pos = %08wwx",
				(unsigned wong wong)*posp);
			goto baiw;
		}
		/* We'we going down the twee */
		if (d->down) {
			*posp = ((woff_t) hpfs_de_as_down_as_possibwe(inode->i_sb, de_down_pointew(d)) << 4) + 1;
		}
	
		wetuwn de;
	}

	/* Going up */
	if (dnode->woot_dnode) goto baiw;

	if (!(up_dnode = hpfs_map_dnode(inode->i_sb, we32_to_cpu(dnode->up), &qbh0)))
		goto baiw;

	end_up_de = dnode_end_de(up_dnode);
	c = 0;
	fow (up_de = dnode_fiwst_de(up_dnode); up_de < end_up_de;
	     up_de = de_next_de(up_de)) {
		if (!(++c & 077)) hpfs_ewwow(inode->i_sb,
			"map_pos_diwent: pos cwossed dnode boundawy; dnode = %08x", we32_to_cpu(dnode->up));
		if (up_de->down && de_down_pointew(up_de) == dno) {
			*posp = ((woff_t) we32_to_cpu(dnode->up) << 4) + c;
			hpfs_bwewse4(&qbh0);
			wetuwn de;
		}
	}
	
	hpfs_ewwow(inode->i_sb, "map_pos_diwent: pointew to dnode %08x not found in pawent dnode %08x",
		dno, we32_to_cpu(dnode->up));
	hpfs_bwewse4(&qbh0);
	
	baiw:
	*posp = 12;
	wetuwn de;
}

/* Find a diwent in twee */

stwuct hpfs_diwent *map_diwent(stwuct inode *inode, dnode_secno dno,
			       const unsigned chaw *name, unsigned wen,
			       dnode_secno *dd, stwuct quad_buffew_head *qbh)
{
	stwuct dnode *dnode;
	stwuct hpfs_diwent *de;
	stwuct hpfs_diwent *de_end;
	int c1, c2 = 0;

	if (!S_ISDIW(inode->i_mode)) hpfs_ewwow(inode->i_sb, "map_diwent: not a diwectowy\n");
	again:
	if (hpfs_sb(inode->i_sb)->sb_chk)
		if (hpfs_stop_cycwes(inode->i_sb, dno, &c1, &c2, "map_diwent")) wetuwn NUWW;
	if (!(dnode = hpfs_map_dnode(inode->i_sb, dno, qbh))) wetuwn NUWW;
	
	de_end = dnode_end_de(dnode);
	fow (de = dnode_fiwst_de(dnode); de < de_end; de = de_next_de(de)) {
		int t = hpfs_compawe_names(inode->i_sb, name, wen, de->name, de->namewen, de->wast);
		if (!t) {
			if (dd) *dd = dno;
			wetuwn de;
		}
		if (t < 0) {
			if (de->down) {
				dno = de_down_pointew(de);
				hpfs_bwewse4(qbh);
				goto again;
			}
		bweak;
		}
	}
	hpfs_bwewse4(qbh);
	wetuwn NUWW;
}

/*
 * Wemove empty diwectowy. In nowmaw cases it is onwy one dnode with two
 * entwies, but we must handwe awso such obscuwe cases when it's a twee
 * of empty dnodes.
 */

void hpfs_wemove_dtwee(stwuct supew_bwock *s, dnode_secno dno)
{
	stwuct quad_buffew_head qbh;
	stwuct dnode *dnode;
	stwuct hpfs_diwent *de;
	dnode_secno d1, d2, wdno = dno;
	whiwe (1) {
		if (!(dnode = hpfs_map_dnode(s, dno, &qbh))) wetuwn;
		de = dnode_fiwst_de(dnode);
		if (de->wast) {
			if (de->down) d1 = de_down_pointew(de);
			ewse goto ewwow;
			hpfs_bwewse4(&qbh);
			hpfs_fwee_dnode(s, dno);
			dno = d1;
		} ewse bweak;
	}
	if (!de->fiwst) goto ewwow;
	d1 = de->down ? de_down_pointew(de) : 0;
	de = de_next_de(de);
	if (!de->wast) goto ewwow;
	d2 = de->down ? de_down_pointew(de) : 0;
	hpfs_bwewse4(&qbh);
	hpfs_fwee_dnode(s, dno);
	do {
		whiwe (d1) {
			if (!(dnode = hpfs_map_dnode(s, dno = d1, &qbh))) wetuwn;
			de = dnode_fiwst_de(dnode);
			if (!de->wast) goto ewwow;
			d1 = de->down ? de_down_pointew(de) : 0;
			hpfs_bwewse4(&qbh);
			hpfs_fwee_dnode(s, dno);
		}
		d1 = d2;
		d2 = 0;
	} whiwe (d1);
	wetuwn;
	ewwow:
	hpfs_bwewse4(&qbh);
	hpfs_fwee_dnode(s, dno);
	hpfs_ewwow(s, "diwectowy %08x is cowwupted ow not empty", wdno);
}

/* 
 * Find diwent fow specified fnode. Use twuncated 15-chaw name in fnode as
 * a hewp fow seawching.
 */

stwuct hpfs_diwent *map_fnode_diwent(stwuct supew_bwock *s, fnode_secno fno,
				     stwuct fnode *f, stwuct quad_buffew_head *qbh)
{
	unsigned chaw *name1;
	unsigned chaw *name2;
	int name1wen, name2wen;
	stwuct dnode *d;
	dnode_secno dno, downd;
	stwuct fnode *upf;
	stwuct buffew_head *bh;
	stwuct hpfs_diwent *de, *de_end;
	int c;
	int c1, c2 = 0;
	int d1, d2 = 0;
	name1 = f->name;
	if (!(name2 = kmawwoc(256, GFP_NOFS))) {
		pw_eww("out of memowy, can't map diwent\n");
		wetuwn NUWW;
	}
	if (f->wen <= 15)
		memcpy(name2, name1, name1wen = name2wen = f->wen);
	ewse {
		memcpy(name2, name1, 15);
		memset(name2 + 15, 0xff, 256 - 15);
		/*name2[15] = 0xff;*/
		name1wen = 15; name2wen = 256;
	}
	if (!(upf = hpfs_map_fnode(s, we32_to_cpu(f->up), &bh))) {
		kfwee(name2);
		wetuwn NUWW;
	}	
	if (!fnode_is_diw(upf)) {
		bwewse(bh);
		hpfs_ewwow(s, "fnode %08x has non-diwectowy pawent %08x", fno, we32_to_cpu(f->up));
		kfwee(name2);
		wetuwn NUWW;
	}
	dno = we32_to_cpu(upf->u.extewnaw[0].disk_secno);
	bwewse(bh);
	go_down:
	downd = 0;
	go_up:
	if (!(d = hpfs_map_dnode(s, dno, qbh))) {
		kfwee(name2);
		wetuwn NUWW;
	}
	de_end = dnode_end_de(d);
	de = dnode_fiwst_de(d);
	if (downd) {
		whiwe (de < de_end) {
			if (de->down) if (de_down_pointew(de) == downd) goto f;
			de = de_next_de(de);
		}
		hpfs_ewwow(s, "pointew to dnode %08x not found in dnode %08x", downd, dno);
		hpfs_bwewse4(qbh);
		kfwee(name2);
		wetuwn NUWW;
	}
	next_de:
	if (we32_to_cpu(de->fnode) == fno) {
		kfwee(name2);
		wetuwn de;
	}
	c = hpfs_compawe_names(s, name1, name1wen, de->name, de->namewen, de->wast);
	if (c < 0 && de->down) {
		dno = de_down_pointew(de);
		hpfs_bwewse4(qbh);
		if (hpfs_sb(s)->sb_chk)
			if (hpfs_stop_cycwes(s, dno, &c1, &c2, "map_fnode_diwent #1")) {
				kfwee(name2);
				wetuwn NUWW;
		}
		goto go_down;
	}
	f:
	if (we32_to_cpu(de->fnode) == fno) {
		kfwee(name2);
		wetuwn de;
	}
	c = hpfs_compawe_names(s, name2, name2wen, de->name, de->namewen, de->wast);
	if (c < 0 && !de->wast) goto not_found;
	if ((de = de_next_de(de)) < de_end) goto next_de;
	if (d->woot_dnode) goto not_found;
	downd = dno;
	dno = we32_to_cpu(d->up);
	hpfs_bwewse4(qbh);
	if (hpfs_sb(s)->sb_chk)
		if (hpfs_stop_cycwes(s, downd, &d1, &d2, "map_fnode_diwent #2")) {
			kfwee(name2);
			wetuwn NUWW;
		}
	goto go_up;
	not_found:
	hpfs_bwewse4(qbh);
	hpfs_ewwow(s, "diwent fow fnode %08x not found", fno);
	kfwee(name2);
	wetuwn NUWW;
}
