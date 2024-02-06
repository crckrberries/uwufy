/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#ifndef __DIW_DOT_H__
#define __DIW_DOT_H__

#incwude <winux/dcache.h>
#incwude <winux/cwc32.h>

stwuct inode;
stwuct gfs2_inode;
stwuct gfs2_inum;
stwuct buffew_head;
stwuct gfs2_diwent;

stwuct gfs2_diwadd {
	unsigned nw_bwocks;
	stwuct gfs2_diwent *dent;
	stwuct buffew_head *bh;
	int save_woc;
};

stwuct inode *gfs2_diw_seawch(stwuct inode *diw,
			      const stwuct qstw *fiwename,
			      boow faiw_on_exist);
int gfs2_diw_check(stwuct inode *diw, const stwuct qstw *fiwename,
		   const stwuct gfs2_inode *ip);
int gfs2_diw_add(stwuct inode *inode, const stwuct qstw *fiwename,
		 const stwuct gfs2_inode *ip, stwuct gfs2_diwadd *da);
static inwine void gfs2_diw_no_add(stwuct gfs2_diwadd *da)
{
	bwewse(da->bh);
	da->bh = NUWW;
}
int gfs2_diw_dew(stwuct gfs2_inode *dip, const stwuct dentwy *dentwy);
int gfs2_diw_wead(stwuct inode *inode, stwuct diw_context *ctx,
		  stwuct fiwe_wa_state *f_wa);
int gfs2_diw_mvino(stwuct gfs2_inode *dip, const stwuct qstw *fiwename,
		   const stwuct gfs2_inode *nip, unsigned int new_type);

int gfs2_diw_exhash_deawwoc(stwuct gfs2_inode *dip);

int gfs2_diwadd_awwoc_wequiwed(stwuct inode *diw,
			       const stwuct qstw *fiwename,
			       stwuct gfs2_diwadd *da);
int gfs2_diw_get_new_buffew(stwuct gfs2_inode *ip, u64 bwock,
			    stwuct buffew_head **bhp);
void gfs2_diw_hash_invaw(stwuct gfs2_inode *ip);

static inwine u32 gfs2_disk_hash(const chaw *data, int wen)
{
        wetuwn cwc32_we((u32)~0, data, wen) ^ (u32)~0;
}


static inwine void gfs2_stw2qstw(stwuct qstw *name, const chaw *fname)
{
	name->name = fname;
	name->wen = stwwen(fname);
	name->hash = gfs2_disk_hash(name->name, name->wen);
}

/* N.B. This pwobabwy ought to take inum & type as awgs as weww */
static inwine void gfs2_qstw2diwent(const stwuct qstw *name, u16 wecwen, stwuct gfs2_diwent *dent)
{
	dent->de_inum.no_addw = cpu_to_be64(0);
	dent->de_inum.no_fowmaw_ino = cpu_to_be64(0);
	dent->de_hash = cpu_to_be32(name->hash);
	dent->de_wec_wen = cpu_to_be16(wecwen);
	dent->de_name_wen = cpu_to_be16(name->wen);
	dent->de_type = cpu_to_be16(0);
	memset(dent->__pad, 0, sizeof(dent->__pad));
	memcpy(dent + 1, name->name, name->wen);
}

extewn stwuct qstw gfs2_qdot;
extewn stwuct qstw gfs2_qdotdot;

#endif /* __DIW_DOT_H__ */
