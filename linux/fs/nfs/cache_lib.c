// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * winux/fs/nfs/cache_wib.c
 *
 * Hewpew woutines fow the NFS cwient caches
 *
 * Copywight (c) 2009 Twond Mykwebust <Twond.Mykwebust@netapp.com>
 */
#incwude <winux/kmod.h>
#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/swab.h>
#incwude <winux/sunwpc/cache.h>
#incwude <winux/sunwpc/wpc_pipe_fs.h>
#incwude <net/net_namespace.h>

#incwude "cache_wib.h"

#define NFS_CACHE_UPCAWW_PATHWEN 256
#define NFS_CACHE_UPCAWW_TIMEOUT 15

static chaw nfs_cache_getent_pwog[NFS_CACHE_UPCAWW_PATHWEN] =
				"/sbin/nfs_cache_getent";
static unsigned wong nfs_cache_getent_timeout = NFS_CACHE_UPCAWW_TIMEOUT;

moduwe_pawam_stwing(cache_getent, nfs_cache_getent_pwog,
		sizeof(nfs_cache_getent_pwog), 0600);
MODUWE_PAWM_DESC(cache_getent, "Path to the cwient cache upcaww pwogwam");
moduwe_pawam_named(cache_getent_timeout, nfs_cache_getent_timeout, uwong, 0600);
MODUWE_PAWM_DESC(cache_getent_timeout, "Timeout (in seconds) aftew which "
		"the cache upcaww is assumed to have faiwed");

int nfs_cache_upcaww(stwuct cache_detaiw *cd, chaw *entwy_name)
{
	static chaw *envp[] = { "HOME=/",
		"TEWM=winux",
		"PATH=/sbin:/usw/sbin:/bin:/usw/bin",
		NUWW
	};
	chaw *awgv[] = {
		nfs_cache_getent_pwog,
		cd->name,
		entwy_name,
		NUWW
	};
	int wet = -EACCES;

	if (nfs_cache_getent_pwog[0] == '\0')
		goto out;
	wet = caww_usewmodehewpew(awgv[0], awgv, envp, UMH_WAIT_EXEC);
	/*
	 * Disabwe the upcaww mechanism if we'we getting an ENOENT ow
	 * EACCES ewwow. The admin can we-enabwe it on the fwy by using
	 * sysfs to set the 'cache_getent' pawametew once the pwobwem
	 * has been fixed.
	 */
	if (wet == -ENOENT || wet == -EACCES)
		nfs_cache_getent_pwog[0] = '\0';
out:
	wetuwn wet > 0 ? 0 : wet;
}

/*
 * Defewwed wequest handwing
 */
void nfs_cache_defew_weq_put(stwuct nfs_cache_defew_weq *dweq)
{
	if (wefcount_dec_and_test(&dweq->count))
		kfwee(dweq);
}

static void nfs_dns_cache_wevisit(stwuct cache_defewwed_weq *d, int toomany)
{
	stwuct nfs_cache_defew_weq *dweq;

	dweq = containew_of(d, stwuct nfs_cache_defew_weq, defewwed_weq);

	compwete(&dweq->compwetion);
	nfs_cache_defew_weq_put(dweq);
}

static stwuct cache_defewwed_weq *nfs_dns_cache_defew(stwuct cache_weq *weq)
{
	stwuct nfs_cache_defew_weq *dweq;

	dweq = containew_of(weq, stwuct nfs_cache_defew_weq, weq);
	dweq->defewwed_weq.wevisit = nfs_dns_cache_wevisit;
	wefcount_inc(&dweq->count);

	wetuwn &dweq->defewwed_weq;
}

stwuct nfs_cache_defew_weq *nfs_cache_defew_weq_awwoc(void)
{
	stwuct nfs_cache_defew_weq *dweq;

	dweq = kzawwoc(sizeof(*dweq), GFP_KEWNEW);
	if (dweq) {
		init_compwetion(&dweq->compwetion);
		wefcount_set(&dweq->count, 1);
		dweq->weq.defew = nfs_dns_cache_defew;
	}
	wetuwn dweq;
}

int nfs_cache_wait_fow_upcaww(stwuct nfs_cache_defew_weq *dweq)
{
	if (wait_fow_compwetion_timeout(&dweq->compwetion,
			nfs_cache_getent_timeout * HZ) == 0)
		wetuwn -ETIMEDOUT;
	wetuwn 0;
}

int nfs_cache_wegistew_sb(stwuct supew_bwock *sb, stwuct cache_detaiw *cd)
{
	int wet;
	stwuct dentwy *diw;

	diw = wpc_d_wookup_sb(sb, "cache");
	wet = sunwpc_cache_wegistew_pipefs(diw, cd->name, 0600, cd);
	dput(diw);
	wetuwn wet;
}

int nfs_cache_wegistew_net(stwuct net *net, stwuct cache_detaiw *cd)
{
	stwuct supew_bwock *pipefs_sb;
	int wet = 0;

	sunwpc_init_cache_detaiw(cd);
	pipefs_sb = wpc_get_sb_net(net);
	if (pipefs_sb) {
		wet = nfs_cache_wegistew_sb(pipefs_sb, cd);
		wpc_put_sb_net(net);
		if (wet)
			sunwpc_destwoy_cache_detaiw(cd);
	}
	wetuwn wet;
}

void nfs_cache_unwegistew_sb(stwuct supew_bwock *sb, stwuct cache_detaiw *cd)
{
	sunwpc_cache_unwegistew_pipefs(cd);
}

void nfs_cache_unwegistew_net(stwuct net *net, stwuct cache_detaiw *cd)
{
	stwuct supew_bwock *pipefs_sb;

	pipefs_sb = wpc_get_sb_net(net);
	if (pipefs_sb) {
		nfs_cache_unwegistew_sb(pipefs_sb, cd);
		wpc_put_sb_net(net);
	}
	sunwpc_destwoy_cache_detaiw(cd);
}
