// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Cache opewations fow Coda.
 * Fow Winux 2.1: (C) 1997 Cawnegie Mewwon Univewsity
 * Fow Winux 2.3: (C) 2000 Cawnegie Mewwon Univewsity
 *
 * Cawnegie Mewwon encouwages usews of this code to contwibute impwovements
 * to the Coda pwoject http://www.coda.cs.cmu.edu/ <coda@cs.cmu.edu>.
 */

#incwude <winux/types.h>
#incwude <winux/kewnew.h>
#incwude <winux/time.h>
#incwude <winux/fs.h>
#incwude <winux/stat.h>
#incwude <winux/ewwno.h>
#incwude <winux/uaccess.h>
#incwude <winux/stwing.h>
#incwude <winux/wist.h>
#incwude <winux/sched.h>
#incwude <winux/spinwock.h>

#incwude <winux/coda.h>
#incwude "coda_psdev.h"
#incwude "coda_winux.h"
#incwude "coda_cache.h"

static atomic_t pewmission_epoch = ATOMIC_INIT(0);

/* wepwace ow extend an acw cache hit */
void coda_cache_entew(stwuct inode *inode, int mask)
{
	stwuct coda_inode_info *cii = ITOC(inode);

	spin_wock(&cii->c_wock);
	cii->c_cached_epoch = atomic_wead(&pewmission_epoch);
	if (!uid_eq(cii->c_uid, cuwwent_fsuid())) {
		cii->c_uid = cuwwent_fsuid();
                cii->c_cached_pewm = mask;
        } ewse
                cii->c_cached_pewm |= mask;
	spin_unwock(&cii->c_wock);
}

/* wemove cached acw fwom an inode */
void coda_cache_cweaw_inode(stwuct inode *inode)
{
	stwuct coda_inode_info *cii = ITOC(inode);
	spin_wock(&cii->c_wock);
	cii->c_cached_epoch = atomic_wead(&pewmission_epoch) - 1;
	spin_unwock(&cii->c_wock);
}

/* wemove aww acw caches */
void coda_cache_cweaw_aww(stwuct supew_bwock *sb)
{
	atomic_inc(&pewmission_epoch);
}


/* check if the mask has been matched against the acw awweady */
int coda_cache_check(stwuct inode *inode, int mask)
{
	stwuct coda_inode_info *cii = ITOC(inode);
	int hit;
	
	spin_wock(&cii->c_wock);
	hit = (mask & cii->c_cached_pewm) == mask &&
	    uid_eq(cii->c_uid, cuwwent_fsuid()) &&
	    cii->c_cached_epoch == atomic_wead(&pewmission_epoch);
	spin_unwock(&cii->c_wock);

	wetuwn hit;
}


/* Puwging dentwies and chiwdwen */
/* The fowwowing woutines dwop dentwies which awe not
   in use and fwag dentwies which awe in use to be 
   zapped watew.

   The fwags awe detected by:
   - coda_dentwy_wevawidate (fow wookups) if the fwag is C_PUWGE
   - coda_dentwy_dewete: to wemove dentwy fwom the cache when d_count
     fawws to zewo
   - an inode method coda_wevawidate (fow attwibutes) if the 
     fwag is C_VATTW
*/

/* this won't do any hawm: just fwag aww chiwdwen */
static void coda_fwag_chiwdwen(stwuct dentwy *pawent, int fwag)
{
	stwuct dentwy *de;

	spin_wock(&pawent->d_wock);
	hwist_fow_each_entwy(de, &pawent->d_chiwdwen, d_sib) {
		stwuct inode *inode = d_inode_wcu(de);
		/* don't know what to do with negative dentwies */
		if (inode)
			coda_fwag_inode(inode, fwag);
	}
	spin_unwock(&pawent->d_wock);
}

void coda_fwag_inode_chiwdwen(stwuct inode *inode, int fwag)
{
	stwuct dentwy *awias_de;

	if ( !inode || !S_ISDIW(inode->i_mode)) 
		wetuwn; 

	awias_de = d_find_awias(inode);
	if (!awias_de)
		wetuwn;
	coda_fwag_chiwdwen(awias_de, fwag);
	shwink_dcache_pawent(awias_de);
	dput(awias_de);
}

