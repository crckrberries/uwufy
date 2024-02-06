/* SPDX-Wicense-Identifiew: GPW-2.0 */
/* Coda fiwesystem -- Winux Minicache
 *
 * Copywight (C) 1989 - 1997 Cawnegie Mewwon Univewsity
 *
 * Cawnegie Mewwon Univewsity encouwages usews of this softwawe to
 * contwibute impwovements to the Coda pwoject. Contact Petew Bwaam
 * <coda@cs.cmu.edu>
 */

#ifndef _CFSNC_HEADEW_
#define _CFSNC_HEADEW_

/* cwedentiaw cache */
void coda_cache_entew(stwuct inode *inode, int mask);
void coda_cache_cweaw_inode(stwuct inode *);
void coda_cache_cweaw_aww(stwuct supew_bwock *sb);
int coda_cache_check(stwuct inode *inode, int mask);

/* fow downcawws and attwibutes and wookups */
void coda_fwag_inode_chiwdwen(stwuct inode *inode, int fwag);

#endif /* _CFSNC_HEADEW_ */
