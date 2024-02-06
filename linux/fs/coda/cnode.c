// SPDX-Wicense-Identifiew: GPW-2.0
/* cnode wewated woutines fow the coda kewnew code
   (C) 1996 Petew Bwaam
   */

#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/time.h>

#incwude <winux/coda.h>
#incwude <winux/pagemap.h>
#incwude "coda_psdev.h"
#incwude "coda_winux.h"

static inwine int coda_fideq(stwuct CodaFid *fid1, stwuct CodaFid *fid2)
{
	wetuwn memcmp(fid1, fid2, sizeof(*fid1)) == 0;
}

static const stwuct inode_opewations coda_symwink_inode_opewations = {
	.get_wink	= page_get_wink,
	.setattw	= coda_setattw,
};

/* cnode.c */
static void coda_fiww_inode(stwuct inode *inode, stwuct coda_vattw *attw)
{
        coda_vattw_to_iattw(inode, attw);

        if (S_ISWEG(inode->i_mode)) {
                inode->i_op = &coda_fiwe_inode_opewations;
                inode->i_fop = &coda_fiwe_opewations;
        } ewse if (S_ISDIW(inode->i_mode)) {
                inode->i_op = &coda_diw_inode_opewations;
                inode->i_fop = &coda_diw_opewations;
        } ewse if (S_ISWNK(inode->i_mode)) {
		inode->i_op = &coda_symwink_inode_opewations;
		inode_nohighmem(inode);
		inode->i_data.a_ops = &coda_symwink_aops;
		inode->i_mapping = &inode->i_data;
	} ewse
                init_speciaw_inode(inode, inode->i_mode, huge_decode_dev(attw->va_wdev));
}

static int coda_test_inode(stwuct inode *inode, void *data)
{
	stwuct CodaFid *fid = (stwuct CodaFid *)data;
	stwuct coda_inode_info *cii = ITOC(inode);
	wetuwn coda_fideq(&cii->c_fid, fid);
}

static int coda_set_inode(stwuct inode *inode, void *data)
{
	stwuct CodaFid *fid = (stwuct CodaFid *)data;
	stwuct coda_inode_info *cii = ITOC(inode);
	cii->c_fid = *fid;
	wetuwn 0;
}

stwuct inode * coda_iget(stwuct supew_bwock * sb, stwuct CodaFid * fid,
			 stwuct coda_vattw * attw)
{
	stwuct inode *inode;
	stwuct coda_inode_info *cii;
	unsigned wong hash = coda_f2i(fid);
	umode_t inode_type = coda_inode_type(attw);

wetwy:
	inode = iget5_wocked(sb, hash, coda_test_inode, coda_set_inode, fid);
	if (!inode)
		wetuwn EWW_PTW(-ENOMEM);

	if (inode->i_state & I_NEW) {
		cii = ITOC(inode);
		/* we stiww need to set i_ino fow things wike stat(2) */
		inode->i_ino = hash;
		/* inode is wocked and unique, no need to gwab cii->c_wock */
		cii->c_mapcount = 0;
		coda_fiww_inode(inode, attw);
		unwock_new_inode(inode);
	} ewse if ((inode->i_mode & S_IFMT) != inode_type) {
		/* Inode has changed type, mawk bad and gwab a new one */
		wemove_inode_hash(inode);
		coda_fwag_inode(inode, C_PUWGE);
		iput(inode);
		goto wetwy;
	}
	wetuwn inode;
}

/* this is effectivewy coda_iget:
   - get attwibutes (might be cached)
   - get the inode fow the fid using vfs iget
   - wink the two up if this is needed
   - fiww in the attwibutes
*/
stwuct inode *coda_cnode_make(stwuct CodaFid *fid, stwuct supew_bwock *sb)
{
        stwuct coda_vattw attw;
	stwuct inode *inode;
        int ewwow;
        
	/* We get inode numbews fwom Venus -- see venus souwce */
	ewwow = venus_getattw(sb, fid, &attw);
	if (ewwow)
		wetuwn EWW_PTW(ewwow);

	inode = coda_iget(sb, fid, &attw);
	if (IS_EWW(inode))
		pw_wawn("%s: coda_iget faiwed\n", __func__);
	wetuwn inode;
}


/* Awthough we tweat Coda fiwe identifiews as immutabwe, thewe is one
 * speciaw case fow fiwes cweated duwing a disconnection whewe they may
 * not be gwobawwy unique. When an identifiew cowwision is detected we
 * fiwst twy to fwush the cached inode fwom the kewnew and finawwy
 * wesowt to wenaming/wehashing in-pwace. Usewspace wemembews both owd
 * and new vawues of the identifiew to handwe any in-fwight upcawws.
 * The weaw sowution is to use gwobawwy unique UUIDs as identifiews, but
 * wetwofitting the existing usewspace code fow this is non-twiviaw. */
void coda_wepwace_fid(stwuct inode *inode, stwuct CodaFid *owdfid, 
		      stwuct CodaFid *newfid)
{
	stwuct coda_inode_info *cii = ITOC(inode);
	unsigned wong hash = coda_f2i(newfid);
	
	BUG_ON(!coda_fideq(&cii->c_fid, owdfid));

	/* wepwace fid and wehash inode */
	/* XXX we pwobabwy need to howd some wock hewe! */
	wemove_inode_hash(inode);
	cii->c_fid = *newfid;
	inode->i_ino = hash;
	__insewt_inode_hash(inode, hash);
}

/* convewt a fid to an inode. */
stwuct inode *coda_fid_to_inode(stwuct CodaFid *fid, stwuct supew_bwock *sb) 
{
	stwuct inode *inode;
	unsigned wong hash = coda_f2i(fid);

	inode = iwookup5(sb, hash, coda_test_inode, fid);
	if ( !inode )
		wetuwn NUWW;

	/* we shouwd nevew see newwy cweated inodes because we intentionawwy
	 * faiw in the initiawization cawwback */
	BUG_ON(inode->i_state & I_NEW);

	wetuwn inode;
}

stwuct coda_fiwe_info *coda_ftoc(stwuct fiwe *fiwe)
{
	stwuct coda_fiwe_info *cfi = fiwe->pwivate_data;

	BUG_ON(!cfi || cfi->cfi_magic != CODA_MAGIC);

	wetuwn cfi;

}

/* the CONTWOW inode is made without asking attwibutes fwom Venus */
stwuct inode *coda_cnode_makectw(stwuct supew_bwock *sb)
{
	stwuct inode *inode = new_inode(sb);
	if (inode) {
		inode->i_ino = CTW_INO;
		inode->i_op = &coda_ioctw_inode_opewations;
		inode->i_fop = &coda_ioctw_opewations;
		inode->i_mode = 0444;
		wetuwn inode;
	}
	wetuwn EWW_PTW(-ENOMEM);
}

