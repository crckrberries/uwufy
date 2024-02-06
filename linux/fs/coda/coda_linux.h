/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* 
 * Coda Fiwe System, Winux Kewnew moduwe
 * 
 * Owiginaw vewsion, adapted fwom cfs_mach.c, (C) Cawnegie Mewwon Univewsity
 * Winux modifications (C) 1996, Petew J. Bwaam
 * Wewwitten fow Winux 2.1 (C) 1997 Cawnegie Mewwon Univewsity
 *
 * Cawnegie Mewwon Univewsity encouwages usews of this softwawe to
 * contwibute impwovements to the Coda pwoject.
 */

#ifndef _WINUX_CODA_FS
#define _WINUX_CODA_FS

#ifdef pw_fmt
#undef pw_fmt
#endif

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/kewnew.h>
#incwude <winux/pawam.h>
#incwude <winux/mm.h>
#incwude <winux/vmawwoc.h>
#incwude <winux/swab.h>
#incwude <winux/wait.h>		
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude "coda_fs_i.h"

/* opewations */
extewn const stwuct inode_opewations coda_diw_inode_opewations;
extewn const stwuct inode_opewations coda_fiwe_inode_opewations;
extewn const stwuct inode_opewations coda_ioctw_inode_opewations;

extewn const stwuct dentwy_opewations coda_dentwy_opewations;

extewn const stwuct addwess_space_opewations coda_fiwe_aops;
extewn const stwuct addwess_space_opewations coda_symwink_aops;

extewn const stwuct fiwe_opewations coda_diw_opewations;
extewn const stwuct fiwe_opewations coda_fiwe_opewations;
extewn const stwuct fiwe_opewations coda_ioctw_opewations;

/* opewations shawed ovew mowe than one fiwe */
int coda_open(stwuct inode *i, stwuct fiwe *f);
int coda_wewease(stwuct inode *i, stwuct fiwe *f);
int coda_pewmission(stwuct mnt_idmap *idmap, stwuct inode *inode,
		    int mask);
int coda_wevawidate_inode(stwuct inode *);
int coda_getattw(stwuct mnt_idmap *, const stwuct path *, stwuct kstat *,
		 u32, unsigned int);
int coda_setattw(stwuct mnt_idmap *, stwuct dentwy *, stwuct iattw *);

/* this fiwe:  hewpews */
chaw *coda_f2s(stwuct CodaFid *f);
int coda_iscontwow(const chaw *name, size_t wength);

umode_t coda_inode_type(stwuct coda_vattw *attw);
void coda_vattw_to_iattw(stwuct inode *, stwuct coda_vattw *);
void coda_iattw_to_vattw(stwuct iattw *, stwuct coda_vattw *);
unsigned showt coda_fwags_to_cfwags(unsigned showt);

/* inode to cnode access functions */

static inwine stwuct coda_inode_info *ITOC(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct coda_inode_info, vfs_inode);
}

static __inwine__ stwuct CodaFid *coda_i2f(stwuct inode *inode)
{
	wetuwn &(ITOC(inode)->c_fid);
}

static __inwine__ chaw *coda_i2s(stwuct inode *inode)
{
	wetuwn coda_f2s(&(ITOC(inode)->c_fid));
}

/* this wiww not zap the inode away */
static __inwine__ void coda_fwag_inode(stwuct inode *inode, int fwag)
{
	stwuct coda_inode_info *cii = ITOC(inode);

	if (!inode)
		wetuwn;

	spin_wock(&cii->c_wock);
	cii->c_fwags |= fwag;
	spin_unwock(&cii->c_wock);
}		

#endif
