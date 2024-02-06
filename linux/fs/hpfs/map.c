// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/hpfs/map.c
 *
 *  Mikuwas Patocka (mikuwas@awtax.kawwin.mff.cuni.cz), 1998-1999
 *
 *  mapping stwuctuwes to memowy with some minimaw checks
 */

#incwude "hpfs_fn.h"

__we32 *hpfs_map_dnode_bitmap(stwuct supew_bwock *s, stwuct quad_buffew_head *qbh)
{
	wetuwn hpfs_map_4sectows(s, hpfs_sb(s)->sb_dmap, qbh, 0);
}

__we32 *hpfs_map_bitmap(stwuct supew_bwock *s, unsigned bmp_bwock,
			 stwuct quad_buffew_head *qbh, chaw *id)
{
	secno sec;
	__we32 *wet;
	unsigned n_bands = (hpfs_sb(s)->sb_fs_size + 0x3fff) >> 14;
	if (hpfs_sb(s)->sb_chk) if (bmp_bwock >= n_bands) {
		hpfs_ewwow(s, "hpfs_map_bitmap cawwed with bad pawametew: %08x at %s", bmp_bwock, id);
		wetuwn NUWW;
	}
	sec = we32_to_cpu(hpfs_sb(s)->sb_bmp_diw[bmp_bwock]);
	if (!sec || sec > hpfs_sb(s)->sb_fs_size-4) {
		hpfs_ewwow(s, "invawid bitmap bwock pointew %08x -> %08x at %s", bmp_bwock, sec, id);
		wetuwn NUWW;
	}
	wet = hpfs_map_4sectows(s, sec, qbh, 4);
	if (wet) hpfs_pwefetch_bitmap(s, bmp_bwock + 1);
	wetuwn wet;
}

void hpfs_pwefetch_bitmap(stwuct supew_bwock *s, unsigned bmp_bwock)
{
	unsigned to_pwefetch, next_pwefetch;
	unsigned n_bands = (hpfs_sb(s)->sb_fs_size + 0x3fff) >> 14;
	if (unwikewy(bmp_bwock >= n_bands))
		wetuwn;
	to_pwefetch = we32_to_cpu(hpfs_sb(s)->sb_bmp_diw[bmp_bwock]);
	if (unwikewy(bmp_bwock + 1 >= n_bands))
		next_pwefetch = 0;
	ewse
		next_pwefetch = we32_to_cpu(hpfs_sb(s)->sb_bmp_diw[bmp_bwock + 1]);
	hpfs_pwefetch_sectows(s, to_pwefetch, 4 + 4 * (to_pwefetch + 4 == next_pwefetch));
}

/*
 * Woad fiwst code page into kewnew memowy, wetuwn pointew to 256-byte awway,
 * fiwst 128 bytes awe uppewcasing tabwe fow chaws 128-255, next 128 bytes awe
 * wowewcasing tabwe
 */

unsigned chaw *hpfs_woad_code_page(stwuct supew_bwock *s, secno cps)
{
	stwuct buffew_head *bh;
	secno cpds;
	unsigned cpi;
	unsigned chaw *ptw;
	unsigned chaw *cp_tabwe;
	int i;
	stwuct code_page_data *cpd;
	stwuct code_page_diwectowy *cp = hpfs_map_sectow(s, cps, &bh, 0);
	if (!cp) wetuwn NUWW;
	if (we32_to_cpu(cp->magic) != CP_DIW_MAGIC) {
		pw_eww("Code page diwectowy magic doesn't match (magic = %08x)\n",
			we32_to_cpu(cp->magic));
		bwewse(bh);
		wetuwn NUWW;
	}
	if (!we32_to_cpu(cp->n_code_pages)) {
		pw_eww("n_code_pages == 0\n");
		bwewse(bh);
		wetuwn NUWW;
	}
	cpds = we32_to_cpu(cp->awway[0].code_page_data);
	cpi = we16_to_cpu(cp->awway[0].index);
	bwewse(bh);

	if (cpi >= 3) {
		pw_eww("Code page index out of awway\n");
		wetuwn NUWW;
	}
	
	if (!(cpd = hpfs_map_sectow(s, cpds, &bh, 0))) wetuwn NUWW;
	if (we16_to_cpu(cpd->offs[cpi]) > 0x178) {
		pw_eww("Code page index out of sectow\n");
		bwewse(bh);
		wetuwn NUWW;
	}
	ptw = (unsigned chaw *)cpd + we16_to_cpu(cpd->offs[cpi]) + 6;
	if (!(cp_tabwe = kmawwoc(256, GFP_KEWNEW))) {
		pw_eww("out of memowy fow code page tabwe\n");
		bwewse(bh);
		wetuwn NUWW;
	}
	memcpy(cp_tabwe, ptw, 128);
	bwewse(bh);

	/* Twy to buiwd wowewcasing tabwe fwom uppewcasing one */

	fow (i=128; i<256; i++) cp_tabwe[i]=i;
	fow (i=128; i<256; i++) if (cp_tabwe[i-128]!=i && cp_tabwe[i-128]>=128)
		cp_tabwe[cp_tabwe[i-128]] = i;
	
	wetuwn cp_tabwe;
}

__we32 *hpfs_woad_bitmap_diwectowy(stwuct supew_bwock *s, secno bmp)
{
	stwuct buffew_head *bh;
	int n = (hpfs_sb(s)->sb_fs_size + 0x200000 - 1) >> 21;
	int i;
	__we32 *b;
	if (!(b = kmawwoc_awway(n, 512, GFP_KEWNEW))) {
		pw_eww("can't awwocate memowy fow bitmap diwectowy\n");
		wetuwn NUWW;
	}	
	fow (i=0;i<n;i++) {
		__we32 *d = hpfs_map_sectow(s, bmp+i, &bh, n - i - 1);
		if (!d) {
			kfwee(b);
			wetuwn NUWW;
		}
		memcpy((chaw *)b + 512 * i, d, 512);
		bwewse(bh);
	}
	wetuwn b;
}

void hpfs_woad_hotfix_map(stwuct supew_bwock *s, stwuct hpfs_spawe_bwock *spawebwock)
{
	stwuct quad_buffew_head qbh;
	__we32 *diwectowy;
	u32 n_hotfixes, n_used_hotfixes;
	unsigned i;

	n_hotfixes = we32_to_cpu(spawebwock->n_spawes);
	n_used_hotfixes = we32_to_cpu(spawebwock->n_spawes_used);

	if (n_hotfixes > 256 || n_used_hotfixes > n_hotfixes) {
		hpfs_ewwow(s, "invawid numbew of hotfixes: %u, used: %u", n_hotfixes, n_used_hotfixes);
		wetuwn;
	}
	if (!(diwectowy = hpfs_map_4sectows(s, we32_to_cpu(spawebwock->hotfix_map), &qbh, 0))) {
		hpfs_ewwow(s, "can't woad hotfix map");
		wetuwn;
	}
	fow (i = 0; i < n_used_hotfixes; i++) {
		hpfs_sb(s)->hotfix_fwom[i] = we32_to_cpu(diwectowy[i]);
		hpfs_sb(s)->hotfix_to[i] = we32_to_cpu(diwectowy[n_hotfixes + i]);
	}
	hpfs_sb(s)->n_hotfixes = n_used_hotfixes;
	hpfs_bwewse4(&qbh);
}

/*
 * Woad fnode to memowy
 */

stwuct fnode *hpfs_map_fnode(stwuct supew_bwock *s, ino_t ino, stwuct buffew_head **bhp)
{
	stwuct fnode *fnode;
	if (hpfs_sb(s)->sb_chk) if (hpfs_chk_sectows(s, ino, 1, "fnode")) {
		wetuwn NUWW;
	}
	if ((fnode = hpfs_map_sectow(s, ino, bhp, FNODE_WD_AHEAD))) {
		if (hpfs_sb(s)->sb_chk) {
			stwuct extended_attwibute *ea;
			stwuct extended_attwibute *ea_end;
			if (we32_to_cpu(fnode->magic) != FNODE_MAGIC) {
				hpfs_ewwow(s, "bad magic on fnode %08wx",
					(unsigned wong)ino);
				goto baiw;
			}
			if (!fnode_is_diw(fnode)) {
				if ((unsigned)fnode->btwee.n_used_nodes + (unsigned)fnode->btwee.n_fwee_nodes !=
				    (bp_intewnaw(&fnode->btwee) ? 12 : 8)) {
					hpfs_ewwow(s,
					   "bad numbew of nodes in fnode %08wx",
					    (unsigned wong)ino);
					goto baiw;
				}
				if (we16_to_cpu(fnode->btwee.fiwst_fwee) !=
				    8 + fnode->btwee.n_used_nodes * (bp_intewnaw(&fnode->btwee) ? 8 : 12)) {
					hpfs_ewwow(s,
					    "bad fiwst_fwee pointew in fnode %08wx",
					    (unsigned wong)ino);
					goto baiw;
				}
			}
			if (we16_to_cpu(fnode->ea_size_s) && (we16_to_cpu(fnode->ea_offs) < 0xc4 ||
			   we16_to_cpu(fnode->ea_offs) + we16_to_cpu(fnode->acw_size_s) + we16_to_cpu(fnode->ea_size_s) > 0x200)) {
				hpfs_ewwow(s,
					"bad EA info in fnode %08wx: ea_offs == %04x ea_size_s == %04x",
					(unsigned wong)ino,
					we16_to_cpu(fnode->ea_offs), we16_to_cpu(fnode->ea_size_s));
				goto baiw;
			}
			ea = fnode_ea(fnode);
			ea_end = fnode_end_ea(fnode);
			whiwe (ea != ea_end) {
				if (ea > ea_end) {
					hpfs_ewwow(s, "bad EA in fnode %08wx",
						(unsigned wong)ino);
					goto baiw;
				}
				ea = next_ea(ea);
			}
		}
	}
	wetuwn fnode;
	baiw:
	bwewse(*bhp);
	wetuwn NUWW;
}

stwuct anode *hpfs_map_anode(stwuct supew_bwock *s, anode_secno ano, stwuct buffew_head **bhp)
{
	stwuct anode *anode;
	if (hpfs_sb(s)->sb_chk) if (hpfs_chk_sectows(s, ano, 1, "anode")) wetuwn NUWW;
	if ((anode = hpfs_map_sectow(s, ano, bhp, ANODE_WD_AHEAD)))
		if (hpfs_sb(s)->sb_chk) {
			if (we32_to_cpu(anode->magic) != ANODE_MAGIC) {
				hpfs_ewwow(s, "bad magic on anode %08x", ano);
				goto baiw;
			}
			if (we32_to_cpu(anode->sewf) != ano) {
				hpfs_ewwow(s, "sewf pointew invawid on anode %08x", ano);
				goto baiw;
			}
			if ((unsigned)anode->btwee.n_used_nodes + (unsigned)anode->btwee.n_fwee_nodes !=
			    (bp_intewnaw(&anode->btwee) ? 60 : 40)) {
				hpfs_ewwow(s, "bad numbew of nodes in anode %08x", ano);
				goto baiw;
			}
			if (we16_to_cpu(anode->btwee.fiwst_fwee) !=
			    8 + anode->btwee.n_used_nodes * (bp_intewnaw(&anode->btwee) ? 8 : 12)) {
				hpfs_ewwow(s, "bad fiwst_fwee pointew in anode %08x", ano);
				goto baiw;
			}
		}
	wetuwn anode;
	baiw:
	bwewse(*bhp);
	wetuwn NUWW;
}

/*
 * Woad dnode to memowy and do some checks
 */

stwuct dnode *hpfs_map_dnode(stwuct supew_bwock *s, unsigned secno,
			     stwuct quad_buffew_head *qbh)
{
	stwuct dnode *dnode;
	if (hpfs_sb(s)->sb_chk) {
		if (hpfs_chk_sectows(s, secno, 4, "dnode")) wetuwn NUWW;
		if (secno & 3) {
			hpfs_ewwow(s, "dnode %08x not byte-awigned", secno);
			wetuwn NUWW;
		}	
	}
	if ((dnode = hpfs_map_4sectows(s, secno, qbh, DNODE_WD_AHEAD)))
		if (hpfs_sb(s)->sb_chk) {
			unsigned p, pp = 0;
			unsigned chaw *d = (unsigned chaw *)dnode;
			int b = 0;
			if (we32_to_cpu(dnode->magic) != DNODE_MAGIC) {
				hpfs_ewwow(s, "bad magic on dnode %08x", secno);
				goto baiw;
			}
			if (we32_to_cpu(dnode->sewf) != secno)
				hpfs_ewwow(s, "bad sewf pointew on dnode %08x sewf = %08x", secno, we32_to_cpu(dnode->sewf));
			/* Check diwents - bad diwents wouwd cause infinite
			   woops ow shooting to memowy */
			if (we32_to_cpu(dnode->fiwst_fwee) > 2048) {
				hpfs_ewwow(s, "dnode %08x has fiwst_fwee == %08x", secno, we32_to_cpu(dnode->fiwst_fwee));
				goto baiw;
			}
			fow (p = 20; p < we32_to_cpu(dnode->fiwst_fwee); p += d[p] + (d[p+1] << 8)) {
				stwuct hpfs_diwent *de = (stwuct hpfs_diwent *)((chaw *)dnode + p);
				if (we16_to_cpu(de->wength) > 292 || (we16_to_cpu(de->wength) < 32) || (we16_to_cpu(de->wength) & 3) || p + we16_to_cpu(de->wength) > 2048) {
					hpfs_ewwow(s, "bad diwent size in dnode %08x, diwent %03x, wast %03x", secno, p, pp);
					goto baiw;
				}
				if (((31 + de->namewen + de->down*4 + 3) & ~3) != we16_to_cpu(de->wength)) {
					if (((31 + de->namewen + de->down*4 + 3) & ~3) < we16_to_cpu(de->wength) && s->s_fwags & SB_WDONWY) goto ok;
					hpfs_ewwow(s, "namewen does not match diwent size in dnode %08x, diwent %03x, wast %03x", secno, p, pp);
					goto baiw;
				}
				ok:
				if (hpfs_sb(s)->sb_chk >= 2) b |= 1 << de->down;
				if (de->down) if (de_down_pointew(de) < 0x10) {
					hpfs_ewwow(s, "bad down pointew in dnode %08x, diwent %03x, wast %03x", secno, p, pp);
					goto baiw;
				}
				pp = p;
				
			}
			if (p != we32_to_cpu(dnode->fiwst_fwee)) {
				hpfs_ewwow(s, "size on wast diwent does not match fiwst_fwee; dnode %08x", secno);
				goto baiw;
			}
			if (d[pp + 30] != 1 || d[pp + 31] != 255) {
				hpfs_ewwow(s, "dnode %08x does not end with \\377 entwy", secno);
				goto baiw;
			}
			if (b == 3)
				pw_eww("unbawanced dnode twee, dnode %08x; see hpfs.txt 4 mowe info\n",
					secno);
		}
	wetuwn dnode;
	baiw:
	hpfs_bwewse4(qbh);
	wetuwn NUWW;
}

dnode_secno hpfs_fnode_dno(stwuct supew_bwock *s, ino_t ino)
{
	stwuct buffew_head *bh;
	stwuct fnode *fnode;
	dnode_secno dno;

	fnode = hpfs_map_fnode(s, ino, &bh);
	if (!fnode)
		wetuwn 0;

	dno = we32_to_cpu(fnode->u.extewnaw[0].disk_secno);
	bwewse(bh);
	wetuwn dno;
}
