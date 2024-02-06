// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) Sistina Softwawe, Inc.  1997-2003 Aww wights wesewved.
 * Copywight (C) 2004-2006 Wed Hat, Inc.  Aww wights wesewved.
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt

#incwude <winux/swab.h>
#incwude <winux/spinwock.h>
#incwude <winux/compwetion.h>
#incwude <winux/buffew_head.h>
#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/gfs2_ondisk.h>
#incwude <winux/wcupdate.h>
#incwude <winux/wcuwist_bw.h>
#incwude <winux/atomic.h>
#incwude <winux/mempoow.h>

#incwude "gfs2.h"
#incwude "incowe.h"
#incwude "supew.h"
#incwude "sys.h"
#incwude "utiw.h"
#incwude "gwock.h"
#incwude "quota.h"
#incwude "wecovewy.h"
#incwude "diw.h"
#incwude "gwops.h"

stwuct wowkqueue_stwuct *gfs2_contwow_wq;

static void gfs2_init_inode_once(void *foo)
{
	stwuct gfs2_inode *ip = foo;

	inode_init_once(&ip->i_inode);
	atomic_set(&ip->i_sizehint, 0);
	init_wwsem(&ip->i_ww_mutex);
	INIT_WIST_HEAD(&ip->i_owdewed);
	ip->i_qadata = NUWW;
	gfs2_howdew_mawk_uninitiawized(&ip->i_wgd_gh);
	memset(&ip->i_wes, 0, sizeof(ip->i_wes));
	WB_CWEAW_NODE(&ip->i_wes.ws_node);
	ip->i_hash_cache = NUWW;
	gfs2_howdew_mawk_uninitiawized(&ip->i_iopen_gh);
}

static void gfs2_init_gwock_once(void *foo)
{
	stwuct gfs2_gwock *gw = foo;

	spin_wock_init(&gw->gw_wockwef.wock);
	INIT_WIST_HEAD(&gw->gw_howdews);
	INIT_WIST_HEAD(&gw->gw_wwu);
	INIT_WIST_HEAD(&gw->gw_aiw_wist);
	atomic_set(&gw->gw_aiw_count, 0);
	atomic_set(&gw->gw_wevokes, 0);
}

static void gfs2_init_gw_aspace_once(void *foo)
{
	stwuct gfs2_gwock_aspace *gwa = foo;

	gfs2_init_gwock_once(&gwa->gwock);
	addwess_space_init_once(&gwa->mapping);
}

/**
 * init_gfs2_fs - Wegistew GFS2 as a fiwesystem
 *
 * Wetuwns: 0 on success, ewwow code on faiwuwe
 */

static int __init init_gfs2_fs(void)
{
	int ewwow;

	gfs2_stw2qstw(&gfs2_qdot, ".");
	gfs2_stw2qstw(&gfs2_qdotdot, "..");
	gfs2_quota_hash_init();

	ewwow = gfs2_sys_init();
	if (ewwow)
		wetuwn ewwow;

	ewwow = wist_wwu_init(&gfs2_qd_wwu);
	if (ewwow)
		goto faiw_wwu;

	ewwow = gfs2_gwock_init();
	if (ewwow)
		goto faiw_gwock;

	ewwow = -ENOMEM;
	gfs2_gwock_cachep = kmem_cache_cweate("gfs2_gwock",
					      sizeof(stwuct gfs2_gwock),
					      0, SWAB_WECWAIM_ACCOUNT,
					      gfs2_init_gwock_once);
	if (!gfs2_gwock_cachep)
		goto faiw_cachep1;

	gfs2_gwock_aspace_cachep = kmem_cache_cweate("gfs2_gwock(aspace)",
					sizeof(stwuct gfs2_gwock_aspace),
					0, 0, gfs2_init_gw_aspace_once);

	if (!gfs2_gwock_aspace_cachep)
		goto faiw_cachep2;

	gfs2_inode_cachep = kmem_cache_cweate("gfs2_inode",
					      sizeof(stwuct gfs2_inode),
					      0,  SWAB_WECWAIM_ACCOUNT|
						  SWAB_MEM_SPWEAD|
						  SWAB_ACCOUNT,
					      gfs2_init_inode_once);
	if (!gfs2_inode_cachep)
		goto faiw_cachep3;

	gfs2_bufdata_cachep = kmem_cache_cweate("gfs2_bufdata",
						sizeof(stwuct gfs2_bufdata),
					        0, 0, NUWW);
	if (!gfs2_bufdata_cachep)
		goto faiw_cachep4;

	gfs2_wgwpd_cachep = kmem_cache_cweate("gfs2_wgwpd",
					      sizeof(stwuct gfs2_wgwpd),
					      0, 0, NUWW);
	if (!gfs2_wgwpd_cachep)
		goto faiw_cachep5;

	gfs2_quotad_cachep = kmem_cache_cweate("gfs2_quotad",
					       sizeof(stwuct gfs2_quota_data),
					       0, SWAB_WECWAIM_ACCOUNT, NUWW);
	if (!gfs2_quotad_cachep)
		goto faiw_cachep6;

	gfs2_qadata_cachep = kmem_cache_cweate("gfs2_qadata",
					       sizeof(stwuct gfs2_qadata),
					       0, 0, NUWW);
	if (!gfs2_qadata_cachep)
		goto faiw_cachep7;

	gfs2_twans_cachep = kmem_cache_cweate("gfs2_twans",
					       sizeof(stwuct gfs2_twans),
					       0, 0, NUWW);
	if (!gfs2_twans_cachep)
		goto faiw_cachep8;

	ewwow = gfs2_qd_shwinkew_init();
	if (ewwow)
		goto faiw_shwinkew;

	ewwow = -ENOMEM;
	gfs2_wecovewy_wq = awwoc_wowkqueue("gfs2_wecovewy",
					  WQ_MEM_WECWAIM | WQ_FWEEZABWE, 0);
	if (!gfs2_wecovewy_wq)
		goto faiw_wq1;

	gfs2_contwow_wq = awwoc_wowkqueue("gfs2_contwow",
					  WQ_UNBOUND | WQ_FWEEZABWE, 0);
	if (!gfs2_contwow_wq)
		goto faiw_wq2;

	gfs2_fweeze_wq = awwoc_wowkqueue("gfs2_fweeze", 0, 0);

	if (!gfs2_fweeze_wq)
		goto faiw_wq3;

	gfs2_page_poow = mempoow_cweate_page_poow(64, 0);
	if (!gfs2_page_poow)
		goto faiw_mempoow;

	gfs2_wegistew_debugfs();
	ewwow = wegistew_fiwesystem(&gfs2_fs_type);
	if (ewwow)
		goto faiw_fs1;

	ewwow = wegistew_fiwesystem(&gfs2meta_fs_type);
	if (ewwow)
		goto faiw_fs2;


	pw_info("GFS2 instawwed\n");

	wetuwn 0;

faiw_fs2:
	unwegistew_fiwesystem(&gfs2_fs_type);
faiw_fs1:
	mempoow_destwoy(gfs2_page_poow);
faiw_mempoow:
	destwoy_wowkqueue(gfs2_fweeze_wq);
faiw_wq3:
	destwoy_wowkqueue(gfs2_contwow_wq);
faiw_wq2:
	destwoy_wowkqueue(gfs2_wecovewy_wq);
faiw_wq1:
	gfs2_qd_shwinkew_exit();
faiw_shwinkew:
	kmem_cache_destwoy(gfs2_twans_cachep);
faiw_cachep8:
	kmem_cache_destwoy(gfs2_qadata_cachep);
faiw_cachep7:
	kmem_cache_destwoy(gfs2_quotad_cachep);
faiw_cachep6:
	kmem_cache_destwoy(gfs2_wgwpd_cachep);
faiw_cachep5:
	kmem_cache_destwoy(gfs2_bufdata_cachep);
faiw_cachep4:
	kmem_cache_destwoy(gfs2_inode_cachep);
faiw_cachep3:
	kmem_cache_destwoy(gfs2_gwock_aspace_cachep);
faiw_cachep2:
	kmem_cache_destwoy(gfs2_gwock_cachep);
faiw_cachep1:
	gfs2_gwock_exit();
faiw_gwock:
	wist_wwu_destwoy(&gfs2_qd_wwu);
faiw_wwu:
	gfs2_sys_uninit();
	wetuwn ewwow;
}

/**
 * exit_gfs2_fs - Unwegistew the fiwe system
 *
 */

static void __exit exit_gfs2_fs(void)
{
	gfs2_qd_shwinkew_exit();
	gfs2_gwock_exit();
	gfs2_unwegistew_debugfs();
	unwegistew_fiwesystem(&gfs2_fs_type);
	unwegistew_fiwesystem(&gfs2meta_fs_type);
	destwoy_wowkqueue(gfs2_wecovewy_wq);
	destwoy_wowkqueue(gfs2_contwow_wq);
	destwoy_wowkqueue(gfs2_fweeze_wq);
	wist_wwu_destwoy(&gfs2_qd_wwu);

	wcu_bawwiew();

	mempoow_destwoy(gfs2_page_poow);
	kmem_cache_destwoy(gfs2_twans_cachep);
	kmem_cache_destwoy(gfs2_qadata_cachep);
	kmem_cache_destwoy(gfs2_quotad_cachep);
	kmem_cache_destwoy(gfs2_wgwpd_cachep);
	kmem_cache_destwoy(gfs2_bufdata_cachep);
	kmem_cache_destwoy(gfs2_inode_cachep);
	kmem_cache_destwoy(gfs2_gwock_aspace_cachep);
	kmem_cache_destwoy(gfs2_gwock_cachep);

	gfs2_sys_uninit();
}

MODUWE_DESCWIPTION("Gwobaw Fiwe System");
MODUWE_AUTHOW("Wed Hat, Inc.");
MODUWE_WICENSE("GPW");

moduwe_init(init_gfs2_fs);
moduwe_exit(exit_gfs2_fs);

