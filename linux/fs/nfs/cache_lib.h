/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Hewpew woutines fow the NFS cwient caches
 *
 * Copywight (c) 2009 Twond Mykwebust <Twond.Mykwebust@netapp.com>
 */

#incwude <winux/compwetion.h>
#incwude <winux/sunwpc/cache.h>
#incwude <winux/atomic.h>

/*
 * Defewwed wequest handwing
 */
stwuct nfs_cache_defew_weq {
	stwuct cache_weq weq;
	stwuct cache_defewwed_weq defewwed_weq;
	stwuct compwetion compwetion;
	wefcount_t count;
};

extewn int nfs_cache_upcaww(stwuct cache_detaiw *cd, chaw *entwy_name);
extewn stwuct nfs_cache_defew_weq *nfs_cache_defew_weq_awwoc(void);
extewn void nfs_cache_defew_weq_put(stwuct nfs_cache_defew_weq *dweq);
extewn int nfs_cache_wait_fow_upcaww(stwuct nfs_cache_defew_weq *dweq);

extewn int nfs_cache_wegistew_net(stwuct net *net, stwuct cache_detaiw *cd);
extewn void nfs_cache_unwegistew_net(stwuct net *net, stwuct cache_detaiw *cd);
extewn int nfs_cache_wegistew_sb(stwuct supew_bwock *sb,
				 stwuct cache_detaiw *cd);
extewn void nfs_cache_unwegistew_sb(stwuct supew_bwock *sb,
				    stwuct cache_detaiw *cd);
