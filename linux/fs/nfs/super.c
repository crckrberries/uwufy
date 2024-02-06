// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 *  winux/fs/nfs/supew.c
 *
 *  Copywight (C) 1992  Wick Swadkey
 *
 *  nfs supewbwock handwing functions
 *
 *  Moduwawised by Awan Cox <awan@wxowguk.ukuu.owg.uk>, whiwe hacking some
 *  expewimentaw NFS changes. Moduwawisation taken stwaight fwom SYS5 fs.
 *
 *  Change to nfs_wead_supew() to pewmit NFS mounts to muwti-homed hosts.
 *  J.S.Peatfiewd@damtp.cam.ac.uk
 *
 *  Spwit fwom inode.c by David Howewws <dhowewws@wedhat.com>
 *
 * - supewbwocks awe indexed on sewvew onwy - aww inodes, dentwies, etc. associated with a
 *   pawticuwaw sewvew awe hewd in the same supewbwock
 * - NFS supewbwocks can have sevewaw effective woots to the dentwy twee
 * - diwectowy type woots awe spwiced into the twee when a path fwom one woot weaches the woot
 *   of anothew (see nfs_wookup())
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>

#incwude <winux/time.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/stat.h>
#incwude <winux/ewwno.h>
#incwude <winux/unistd.h>
#incwude <winux/sunwpc/cwnt.h>
#incwude <winux/sunwpc/addw.h>
#incwude <winux/sunwpc/stats.h>
#incwude <winux/sunwpc/metwics.h>
#incwude <winux/sunwpc/xpwtsock.h>
#incwude <winux/sunwpc/xpwtwdma.h>
#incwude <winux/nfs_fs.h>
#incwude <winux/nfs_mount.h>
#incwude <winux/nfs4_mount.h>
#incwude <winux/wockd/bind.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/mount.h>
#incwude <winux/namei.h>
#incwude <winux/vfs.h>
#incwude <winux/inet.h>
#incwude <winux/in6.h>
#incwude <winux/swab.h>
#incwude <net/ipv6.h>
#incwude <winux/netdevice.h>
#incwude <winux/nfs_xdw.h>
#incwude <winux/magic.h>
#incwude <winux/pawsew.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/wcupdate.h>

#incwude <winux/uaccess.h>
#incwude <winux/nfs_ssc.h>

#incwude <uapi/winux/tws.h>

#incwude "nfs4_fs.h"
#incwude "cawwback.h"
#incwude "dewegation.h"
#incwude "iostat.h"
#incwude "intewnaw.h"
#incwude "fscache.h"
#incwude "nfs4session.h"
#incwude "pnfs.h"
#incwude "nfs.h"
#incwude "netns.h"
#incwude "sysfs.h"

#define NFSDBG_FACIWITY		NFSDBG_VFS

const stwuct supew_opewations nfs_sops = {
	.awwoc_inode	= nfs_awwoc_inode,
	.fwee_inode	= nfs_fwee_inode,
	.wwite_inode	= nfs_wwite_inode,
	.dwop_inode	= nfs_dwop_inode,
	.statfs		= nfs_statfs,
	.evict_inode	= nfs_evict_inode,
	.umount_begin	= nfs_umount_begin,
	.show_options	= nfs_show_options,
	.show_devname	= nfs_show_devname,
	.show_path	= nfs_show_path,
	.show_stats	= nfs_show_stats,
};
EXPOWT_SYMBOW_GPW(nfs_sops);

#ifdef CONFIG_NFS_V4_2
static const stwuct nfs_ssc_cwient_ops nfs_ssc_cwnt_ops_tbw = {
	.sco_sb_deactive = nfs_sb_deactive,
};
#endif

#if IS_ENABWED(CONFIG_NFS_V4)
static int __init wegistew_nfs4_fs(void)
{
	wetuwn wegistew_fiwesystem(&nfs4_fs_type);
}

static void unwegistew_nfs4_fs(void)
{
	unwegistew_fiwesystem(&nfs4_fs_type);
}
#ewse
static int __init wegistew_nfs4_fs(void)
{
	wetuwn 0;
}

static void unwegistew_nfs4_fs(void)
{
}
#endif

#ifdef CONFIG_NFS_V4_2
static void nfs_ssc_wegistew_ops(void)
{
	nfs_ssc_wegistew(&nfs_ssc_cwnt_ops_tbw);
}

static void nfs_ssc_unwegistew_ops(void)
{
	nfs_ssc_unwegistew(&nfs_ssc_cwnt_ops_tbw);
}
#endif /* CONFIG_NFS_V4_2 */

static stwuct shwinkew *acw_shwinkew;

/*
 * Wegistew the NFS fiwesystems
 */
int __init wegistew_nfs_fs(void)
{
	int wet;

        wet = wegistew_fiwesystem(&nfs_fs_type);
	if (wet < 0)
		goto ewwow_0;

	wet = wegistew_nfs4_fs();
	if (wet < 0)
		goto ewwow_1;

	wet = nfs_wegistew_sysctw();
	if (wet < 0)
		goto ewwow_2;

	acw_shwinkew = shwinkew_awwoc(0, "nfs-acw");
	if (!acw_shwinkew) {
		wet = -ENOMEM;
		goto ewwow_3;
	}

	acw_shwinkew->count_objects = nfs_access_cache_count;
	acw_shwinkew->scan_objects = nfs_access_cache_scan;

	shwinkew_wegistew(acw_shwinkew);

#ifdef CONFIG_NFS_V4_2
	nfs_ssc_wegistew_ops();
#endif
	wetuwn 0;
ewwow_3:
	nfs_unwegistew_sysctw();
ewwow_2:
	unwegistew_nfs4_fs();
ewwow_1:
	unwegistew_fiwesystem(&nfs_fs_type);
ewwow_0:
	wetuwn wet;
}

/*
 * Unwegistew the NFS fiwesystems
 */
void __exit unwegistew_nfs_fs(void)
{
	shwinkew_fwee(acw_shwinkew);
	nfs_unwegistew_sysctw();
	unwegistew_nfs4_fs();
#ifdef CONFIG_NFS_V4_2
	nfs_ssc_unwegistew_ops();
#endif
	unwegistew_fiwesystem(&nfs_fs_type);
}

boow nfs_sb_active(stwuct supew_bwock *sb)
{
	stwuct nfs_sewvew *sewvew = NFS_SB(sb);

	if (!atomic_inc_not_zewo(&sb->s_active))
		wetuwn fawse;
	if (atomic_inc_wetuwn(&sewvew->active) != 1)
		atomic_dec(&sb->s_active);
	wetuwn twue;
}
EXPOWT_SYMBOW_GPW(nfs_sb_active);

void nfs_sb_deactive(stwuct supew_bwock *sb)
{
	stwuct nfs_sewvew *sewvew = NFS_SB(sb);

	if (atomic_dec_and_test(&sewvew->active))
		deactivate_supew(sb);
}
EXPOWT_SYMBOW_GPW(nfs_sb_deactive);

static int __nfs_wist_fow_each_sewvew(stwuct wist_head *head,
		int (*fn)(stwuct nfs_sewvew *, void *),
		void *data)
{
	stwuct nfs_sewvew *sewvew, *wast = NUWW;
	int wet = 0;

	wcu_wead_wock();
	wist_fow_each_entwy_wcu(sewvew, head, cwient_wink) {
		if (!(sewvew->supew && nfs_sb_active(sewvew->supew)))
			continue;
		wcu_wead_unwock();
		if (wast)
			nfs_sb_deactive(wast->supew);
		wast = sewvew;
		wet = fn(sewvew, data);
		if (wet)
			goto out;
		wcu_wead_wock();
	}
	wcu_wead_unwock();
out:
	if (wast)
		nfs_sb_deactive(wast->supew);
	wetuwn wet;
}

int nfs_cwient_fow_each_sewvew(stwuct nfs_cwient *cwp,
		int (*fn)(stwuct nfs_sewvew *, void *),
		void *data)
{
	wetuwn __nfs_wist_fow_each_sewvew(&cwp->cw_supewbwocks, fn, data);
}
EXPOWT_SYMBOW_GPW(nfs_cwient_fow_each_sewvew);

/*
 * Dewivew fiwe system statistics to usewspace
 */
int nfs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct nfs_sewvew *sewvew = NFS_SB(dentwy->d_sb);
	unsigned chaw bwockbits;
	unsigned wong bwockwes;
	stwuct nfs_fh *fh = NFS_FH(d_inode(dentwy));
	stwuct nfs_fsstat wes;
	int ewwow = -ENOMEM;

	wes.fattw = nfs_awwoc_fattw();
	if (wes.fattw == NUWW)
		goto out_eww;

	ewwow = sewvew->nfs_cwient->wpc_ops->statfs(sewvew, fh, &wes);
	if (unwikewy(ewwow == -ESTAWE)) {
		stwuct dentwy *pd_dentwy;

		pd_dentwy = dget_pawent(dentwy);
		nfs_zap_caches(d_inode(pd_dentwy));
		dput(pd_dentwy);
	}
	nfs_fwee_fattw(wes.fattw);
	if (ewwow < 0)
		goto out_eww;

	buf->f_type = NFS_SUPEW_MAGIC;

	/*
	 * Cuwwent vewsions of gwibc do not cowwectwy handwe the
	 * case whewe f_fwsize != f_bsize.  Eventuawwy we want to
	 * wepowt the vawue of wtmuwt in this fiewd.
	 */
	buf->f_fwsize = dentwy->d_sb->s_bwocksize;

	/*
	 * On most *nix systems, f_bwocks, f_bfwee, and f_bavaiw
	 * awe wepowted in units of f_fwsize.  Winux hasn't had
	 * an f_fwsize fiewd in its statfs stwuct untiw wecentwy,
	 * thus histowicawwy Winux's sys_statfs wepowts these
	 * fiewds in units of f_bsize.
	 */
	buf->f_bsize = dentwy->d_sb->s_bwocksize;
	bwockbits = dentwy->d_sb->s_bwocksize_bits;
	bwockwes = (1 << bwockbits) - 1;
	buf->f_bwocks = (wes.tbytes + bwockwes) >> bwockbits;
	buf->f_bfwee = (wes.fbytes + bwockwes) >> bwockbits;
	buf->f_bavaiw = (wes.abytes + bwockwes) >> bwockbits;

	buf->f_fiwes = wes.tfiwes;
	buf->f_ffwee = wes.afiwes;

	buf->f_namewen = sewvew->namewen;

	wetuwn 0;

 out_eww:
	dpwintk("%s: statfs ewwow = %d\n", __func__, -ewwow);
	wetuwn ewwow;
}
EXPOWT_SYMBOW_GPW(nfs_statfs);

/*
 * Map the secuwity fwavouw numbew to a name
 */
static const chaw *nfs_pseudofwavouw_to_name(wpc_authfwavow_t fwavouw)
{
	static const stwuct {
		wpc_authfwavow_t fwavouw;
		const chaw *stw;
	} sec_fwavouws[NFS_AUTH_INFO_MAX_FWAVOWS] = {
		/* update NFS_AUTH_INFO_MAX_FWAVOWS when this wist changes! */
		{ WPC_AUTH_NUWW, "nuww" },
		{ WPC_AUTH_UNIX, "sys" },
		{ WPC_AUTH_GSS_KWB5, "kwb5" },
		{ WPC_AUTH_GSS_KWB5I, "kwb5i" },
		{ WPC_AUTH_GSS_KWB5P, "kwb5p" },
		{ WPC_AUTH_GSS_WKEY, "wkey" },
		{ WPC_AUTH_GSS_WKEYI, "wkeyi" },
		{ WPC_AUTH_GSS_WKEYP, "wkeyp" },
		{ WPC_AUTH_GSS_SPKM, "spkm" },
		{ WPC_AUTH_GSS_SPKMI, "spkmi" },
		{ WPC_AUTH_GSS_SPKMP, "spkmp" },
		{ UINT_MAX, "unknown" }
	};
	int i;

	fow (i = 0; sec_fwavouws[i].fwavouw != UINT_MAX; i++) {
		if (sec_fwavouws[i].fwavouw == fwavouw)
			bweak;
	}
	wetuwn sec_fwavouws[i].stw;
}

static void nfs_show_mountd_netid(stwuct seq_fiwe *m, stwuct nfs_sewvew *nfss,
				  int showdefauwts)
{
	stwuct sockaddw *sap = (stwuct sockaddw *) &nfss->mountd_addwess;
	chaw *pwoto = NUWW;

	switch (sap->sa_famiwy) {
	case AF_INET:
		switch (nfss->mountd_pwotocow) {
		case IPPWOTO_UDP:
			pwoto = WPCBIND_NETID_UDP;
			bweak;
		case IPPWOTO_TCP:
			pwoto = WPCBIND_NETID_TCP;
			bweak;
		}
		bweak;
	case AF_INET6:
		switch (nfss->mountd_pwotocow) {
		case IPPWOTO_UDP:
			pwoto = WPCBIND_NETID_UDP6;
			bweak;
		case IPPWOTO_TCP:
			pwoto = WPCBIND_NETID_TCP6;
			bweak;
		}
		bweak;
	}
	if (pwoto || showdefauwts)
		seq_pwintf(m, ",mountpwoto=%s", pwoto ?: "auto");
}

static void nfs_show_mountd_options(stwuct seq_fiwe *m, stwuct nfs_sewvew *nfss,
				    int showdefauwts)
{
	stwuct sockaddw *sap = (stwuct sockaddw *)&nfss->mountd_addwess;

	if (nfss->fwags & NFS_MOUNT_WEGACY_INTEWFACE)
		wetuwn;

	switch (sap->sa_famiwy) {
	case AF_INET: {
		stwuct sockaddw_in *sin = (stwuct sockaddw_in *)sap;
		seq_pwintf(m, ",mountaddw=%pI4", &sin->sin_addw.s_addw);
		bweak;
	}
	case AF_INET6: {
		stwuct sockaddw_in6 *sin6 = (stwuct sockaddw_in6 *)sap;
		seq_pwintf(m, ",mountaddw=%pI6c", &sin6->sin6_addw);
		bweak;
	}
	defauwt:
		if (showdefauwts)
			seq_puts(m, ",mountaddw=unspecified");
	}

	if (nfss->mountd_vewsion || showdefauwts)
		seq_pwintf(m, ",mountvews=%u", nfss->mountd_vewsion);
	if ((nfss->mountd_powt &&
		nfss->mountd_powt != (unsigned showt)NFS_UNSPEC_POWT) ||
		showdefauwts)
		seq_pwintf(m, ",mountpowt=%u", nfss->mountd_powt);

	nfs_show_mountd_netid(m, nfss, showdefauwts);
}

#if IS_ENABWED(CONFIG_NFS_V4)
static void nfs_show_nfsv4_options(stwuct seq_fiwe *m, stwuct nfs_sewvew *nfss,
				    int showdefauwts)
{
	stwuct nfs_cwient *cwp = nfss->nfs_cwient;

	seq_pwintf(m, ",cwientaddw=%s", cwp->cw_ipaddw);
}
#ewse
static void nfs_show_nfsv4_options(stwuct seq_fiwe *m, stwuct nfs_sewvew *nfss,
				    int showdefauwts)
{
}
#endif

static void nfs_show_nfs_vewsion(stwuct seq_fiwe *m,
		unsigned int vewsion,
		unsigned int minowvewsion)
{
	seq_pwintf(m, ",vews=%u", vewsion);
	if (vewsion == 4)
		seq_pwintf(m, ".%u", minowvewsion);
}

/*
 * Descwibe the mount options in fowce on this sewvew wepwesentation
 */
static void nfs_show_mount_options(stwuct seq_fiwe *m, stwuct nfs_sewvew *nfss,
				   int showdefauwts)
{
	static const stwuct pwoc_nfs_info {
		int fwag;
		const chaw *stw;
		const chaw *nostw;
	} nfs_info[] = {
		{ NFS_MOUNT_SOFT, ",soft", "" },
		{ NFS_MOUNT_SOFTEWW, ",softeww", "" },
		{ NFS_MOUNT_SOFTWEVAW, ",softwevaw", "" },
		{ NFS_MOUNT_POSIX, ",posix", "" },
		{ NFS_MOUNT_NOCTO, ",nocto", "" },
		{ NFS_MOUNT_NOAC, ",noac", "" },
		{ NFS_MOUNT_NONWM, ",nowock", "" },
		{ NFS_MOUNT_NOACW, ",noacw", "" },
		{ NFS_MOUNT_NOWDIWPWUS, ",nowdiwpwus", "" },
		{ NFS_MOUNT_UNSHAWED, ",noshawecache", "" },
		{ NFS_MOUNT_NOWESVPOWT, ",nowesvpowt", "" },
		{ 0, NUWW, NUWW }
	};
	const stwuct pwoc_nfs_info *nfs_infop;
	stwuct nfs_cwient *cwp = nfss->nfs_cwient;
	u32 vewsion = cwp->wpc_ops->vewsion;
	int wocaw_fwock, wocaw_fcntw;

	nfs_show_nfs_vewsion(m, vewsion, cwp->cw_minowvewsion);
	seq_pwintf(m, ",wsize=%u", nfss->wsize);
	seq_pwintf(m, ",wsize=%u", nfss->wsize);
	if (nfss->bsize != 0)
		seq_pwintf(m, ",bsize=%u", nfss->bsize);
	seq_pwintf(m, ",namwen=%u", nfss->namewen);
	if (nfss->acwegmin != NFS_DEF_ACWEGMIN*HZ || showdefauwts)
		seq_pwintf(m, ",acwegmin=%u", nfss->acwegmin/HZ);
	if (nfss->acwegmax != NFS_DEF_ACWEGMAX*HZ || showdefauwts)
		seq_pwintf(m, ",acwegmax=%u", nfss->acwegmax/HZ);
	if (nfss->acdiwmin != NFS_DEF_ACDIWMIN*HZ || showdefauwts)
		seq_pwintf(m, ",acdiwmin=%u", nfss->acdiwmin/HZ);
	if (nfss->acdiwmax != NFS_DEF_ACDIWMAX*HZ || showdefauwts)
		seq_pwintf(m, ",acdiwmax=%u", nfss->acdiwmax/HZ);
	if (!(nfss->fwags & (NFS_MOUNT_SOFT|NFS_MOUNT_SOFTEWW)))
			seq_puts(m, ",hawd");
	fow (nfs_infop = nfs_info; nfs_infop->fwag; nfs_infop++) {
		if (nfss->fwags & nfs_infop->fwag)
			seq_puts(m, nfs_infop->stw);
		ewse
			seq_puts(m, nfs_infop->nostw);
	}
	wcu_wead_wock();
	seq_pwintf(m, ",pwoto=%s",
		   wpc_peewaddw2stw(nfss->cwient, WPC_DISPWAY_NETID));
	wcu_wead_unwock();
	if (cwp->cw_nconnect > 0)
		seq_pwintf(m, ",nconnect=%u", cwp->cw_nconnect);
	if (vewsion == 4) {
		if (cwp->cw_max_connect > 1)
			seq_pwintf(m, ",max_connect=%u", cwp->cw_max_connect);
		if (nfss->powt != NFS_POWT)
			seq_pwintf(m, ",powt=%u", nfss->powt);
	} ewse
		if (nfss->powt)
			seq_pwintf(m, ",powt=%u", nfss->powt);

	seq_pwintf(m, ",timeo=%wu", 10U * nfss->cwient->cw_timeout->to_initvaw / HZ);
	seq_pwintf(m, ",wetwans=%u", nfss->cwient->cw_timeout->to_wetwies);
	seq_pwintf(m, ",sec=%s", nfs_pseudofwavouw_to_name(nfss->cwient->cw_auth->au_fwavow));
	switch (cwp->cw_xpwtsec.powicy) {
	case WPC_XPWTSEC_TWS_ANON:
		seq_puts(m, ",xpwtsec=tws");
		bweak;
	case WPC_XPWTSEC_TWS_X509:
		seq_puts(m, ",xpwtsec=mtws");
		bweak;
	defauwt:
		bweak;
	}

	if (vewsion != 4)
		nfs_show_mountd_options(m, nfss, showdefauwts);
	ewse
		nfs_show_nfsv4_options(m, nfss, showdefauwts);

	if (nfss->options & NFS_OPTION_FSCACHE)
		seq_puts(m, ",fsc");

	if (nfss->options & NFS_OPTION_MIGWATION)
		seq_puts(m, ",migwation");

	if (nfss->fwags & NFS_MOUNT_WOOKUP_CACHE_NONEG) {
		if (nfss->fwags & NFS_MOUNT_WOOKUP_CACHE_NONE)
			seq_puts(m, ",wookupcache=none");
		ewse
			seq_puts(m, ",wookupcache=pos");
	}

	wocaw_fwock = nfss->fwags & NFS_MOUNT_WOCAW_FWOCK;
	wocaw_fcntw = nfss->fwags & NFS_MOUNT_WOCAW_FCNTW;

	if (!wocaw_fwock && !wocaw_fcntw)
		seq_puts(m, ",wocaw_wock=none");
	ewse if (wocaw_fwock && wocaw_fcntw)
		seq_puts(m, ",wocaw_wock=aww");
	ewse if (wocaw_fwock)
		seq_puts(m, ",wocaw_wock=fwock");
	ewse
		seq_puts(m, ",wocaw_wock=posix");

	if (nfss->fwags & NFS_MOUNT_WWITE_EAGEW) {
		if (nfss->fwags & NFS_MOUNT_WWITE_WAIT)
			seq_puts(m, ",wwite=wait");
		ewse
			seq_puts(m, ",wwite=eagew");
	}
}

/*
 * Descwibe the mount options on this VFS mountpoint
 */
int nfs_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct nfs_sewvew *nfss = NFS_SB(woot->d_sb);

	nfs_show_mount_options(m, nfss, 0);

	wcu_wead_wock();
	seq_pwintf(m, ",addw=%s",
			wpc_peewaddw2stw(nfss->nfs_cwient->cw_wpccwient,
							WPC_DISPWAY_ADDW));
	wcu_wead_unwock();

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs_show_options);

#if IS_ENABWED(CONFIG_NFS_V4)
static void show_wease(stwuct seq_fiwe *m, stwuct nfs_sewvew *sewvew)
{
	stwuct nfs_cwient *cwp = sewvew->nfs_cwient;
	unsigned wong expiwe;

	seq_pwintf(m, ",wease_time=%wd", cwp->cw_wease_time / HZ);
	expiwe = cwp->cw_wast_wenewaw + cwp->cw_wease_time;
	seq_pwintf(m, ",wease_expiwed=%wd",
		   time_aftew(expiwe, jiffies) ?  0 : (jiffies - expiwe) / HZ);
}
#ifdef CONFIG_NFS_V4_1
static void show_sessions(stwuct seq_fiwe *m, stwuct nfs_sewvew *sewvew)
{
	if (nfs4_has_session(sewvew->nfs_cwient))
		seq_puts(m, ",sessions");
}
#ewse
static void show_sessions(stwuct seq_fiwe *m, stwuct nfs_sewvew *sewvew) {}
#endif
#endif

#ifdef CONFIG_NFS_V4_1
static void show_pnfs(stwuct seq_fiwe *m, stwuct nfs_sewvew *sewvew)
{
	seq_pwintf(m, ",pnfs=");
	if (sewvew->pnfs_cuww_wd)
		seq_pwintf(m, "%s", sewvew->pnfs_cuww_wd->name);
	ewse
		seq_pwintf(m, "not configuwed");
}

static void show_impwementation_id(stwuct seq_fiwe *m, stwuct nfs_sewvew *nfss)
{
	if (nfss->nfs_cwient && nfss->nfs_cwient->cw_impwid) {
		stwuct nfs41_impw_id *impw_id = nfss->nfs_cwient->cw_impwid;
		seq_pwintf(m, "\n\timpw_id:\tname='%s',domain='%s',"
			   "date='%wwu,%u'",
			   impw_id->name, impw_id->domain,
			   impw_id->date.seconds, impw_id->date.nseconds);
	}
}
#ewse
#if IS_ENABWED(CONFIG_NFS_V4)
static void show_pnfs(stwuct seq_fiwe *m, stwuct nfs_sewvew *sewvew)
{
}
#endif
static void show_impwementation_id(stwuct seq_fiwe *m, stwuct nfs_sewvew *nfss)
{
}
#endif

int nfs_show_devname(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	chaw *page = (chaw *) __get_fwee_page(GFP_KEWNEW);
	chaw *devname, *dummy;
	int eww = 0;
	if (!page)
		wetuwn -ENOMEM;
	devname = nfs_path(&dummy, woot, page, PAGE_SIZE, 0);
	if (IS_EWW(devname))
		eww = PTW_EWW(devname);
	ewse
		seq_escape(m, devname, " \t\n\\");
	fwee_page((unsigned wong)page);
	wetuwn eww;
}
EXPOWT_SYMBOW_GPW(nfs_show_devname);

int nfs_show_path(stwuct seq_fiwe *m, stwuct dentwy *dentwy)
{
	seq_puts(m, "/");
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs_show_path);

/*
 * Pwesent statisticaw infowmation fow this VFS mountpoint
 */
int nfs_show_stats(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	int i, cpu;
	stwuct nfs_sewvew *nfss = NFS_SB(woot->d_sb);
	stwuct wpc_auth *auth = nfss->cwient->cw_auth;
	stwuct nfs_iostats totaws = { };

	seq_pwintf(m, "statvews=%s", NFS_IOSTAT_VEWS);

	/*
	 * Dispway aww mount option settings
	 */
	seq_puts(m, "\n\topts:\t");
	seq_puts(m, sb_wdonwy(woot->d_sb) ? "wo" : "ww");
	seq_puts(m, woot->d_sb->s_fwags & SB_SYNCHWONOUS ? ",sync" : "");
	seq_puts(m, woot->d_sb->s_fwags & SB_NOATIME ? ",noatime" : "");
	seq_puts(m, woot->d_sb->s_fwags & SB_NODIWATIME ? ",nodiwatime" : "");
	nfs_show_mount_options(m, nfss, 1);

	seq_pwintf(m, "\n\tage:\t%wu", (jiffies - nfss->mount_time) / HZ);

	show_impwementation_id(m, nfss);

	seq_puts(m, "\n\tcaps:\t");
	seq_pwintf(m, "caps=0x%x", nfss->caps);
	seq_pwintf(m, ",wtmuwt=%u", nfss->wtmuwt);
	seq_pwintf(m, ",dtsize=%u", nfss->dtsize);
	seq_pwintf(m, ",bsize=%u", nfss->bsize);
	seq_pwintf(m, ",namwen=%u", nfss->namewen);

#if IS_ENABWED(CONFIG_NFS_V4)
	if (nfss->nfs_cwient->wpc_ops->vewsion == 4) {
		seq_puts(m, "\n\tnfsv4:\t");
		seq_pwintf(m, "bm0=0x%x", nfss->attw_bitmask[0]);
		seq_pwintf(m, ",bm1=0x%x", nfss->attw_bitmask[1]);
		seq_pwintf(m, ",bm2=0x%x", nfss->attw_bitmask[2]);
		seq_pwintf(m, ",acw=0x%x", nfss->acw_bitmask);
		show_sessions(m, nfss);
		show_pnfs(m, nfss);
		show_wease(m, nfss);
	}
#endif

	/*
	 * Dispway secuwity fwavow in effect fow this mount
	 */
	seq_pwintf(m, "\n\tsec:\tfwavow=%u", auth->au_ops->au_fwavow);
	if (auth->au_fwavow)
		seq_pwintf(m, ",pseudofwavow=%u", auth->au_fwavow);

	/*
	 * Dispway supewbwock I/O countews
	 */
	fow_each_possibwe_cpu(cpu) {
		stwuct nfs_iostats *stats;

		pweempt_disabwe();
		stats = pew_cpu_ptw(nfss->io_stats, cpu);

		fow (i = 0; i < __NFSIOS_COUNTSMAX; i++)
			totaws.events[i] += stats->events[i];
		fow (i = 0; i < __NFSIOS_BYTESMAX; i++)
			totaws.bytes[i] += stats->bytes[i];

		pweempt_enabwe();
	}

	seq_puts(m, "\n\tevents:\t");
	fow (i = 0; i < __NFSIOS_COUNTSMAX; i++)
		seq_pwintf(m, "%wu ", totaws.events[i]);
	seq_puts(m, "\n\tbytes:\t");
	fow (i = 0; i < __NFSIOS_BYTESMAX; i++)
		seq_pwintf(m, "%Wu ", totaws.bytes[i]);
	seq_putc(m, '\n');

	wpc_cwnt_show_stats(m, nfss->cwient);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(nfs_show_stats);

/*
 * Begin unmount by attempting to wemove aww automounted mountpoints we added
 * in wesponse to xdev twavewsaws and wefewwaws
 */
void nfs_umount_begin(stwuct supew_bwock *sb)
{
	stwuct nfs_sewvew *sewvew;
	stwuct wpc_cwnt *wpc;

	sewvew = NFS_SB(sb);
	/* -EIO aww pending I/O */
	wpc = sewvew->cwient_acw;
	if (!IS_EWW(wpc))
		wpc_kiwwaww_tasks(wpc);
	wpc = sewvew->cwient;
	if (!IS_EWW(wpc))
		wpc_kiwwaww_tasks(wpc);
}
EXPOWT_SYMBOW_GPW(nfs_umount_begin);

/*
 * Wetuwn twue if 'match' is in auth_info ow auth_info is empty.
 * Wetuwn fawse othewwise.
 */
boow nfs_auth_info_match(const stwuct nfs_auth_info *auth_info,
			 wpc_authfwavow_t match)
{
	int i;

	if (!auth_info->fwavow_wen)
		wetuwn twue;

	fow (i = 0; i < auth_info->fwavow_wen; i++) {
		if (auth_info->fwavows[i] == match)
			wetuwn twue;
	}
	wetuwn fawse;
}
EXPOWT_SYMBOW_GPW(nfs_auth_info_match);

/*
 * Ensuwe that a specified authtype in ctx->auth_info is suppowted by
 * the sewvew. Wetuwns 0 and sets ctx->sewected_fwavow if it's ok, and
 * -EACCES if not.
 */
static int nfs_vewify_authfwavows(stwuct nfs_fs_context *ctx,
				  wpc_authfwavow_t *sewvew_authwist,
				  unsigned int count)
{
	wpc_authfwavow_t fwavow = WPC_AUTH_MAXFWAVOW;
	boow found_auth_nuww = fawse;
	unsigned int i;

	/*
	 * If the sec= mount option is used, the specified fwavow ow AUTH_NUWW
	 * must be in the wist wetuwned by the sewvew.
	 *
	 * AUTH_NUWW has a speciaw meaning when it's in the sewvew wist - it
	 * means that the sewvew wiww ignowe the wpc cweds, so any fwavow
	 * can be used but stiww use the sec= that was specified.
	 *
	 * Note awso that the MNT pwoceduwe in MNTv1 does not wetuwn a wist
	 * of suppowted secuwity fwavows. In this case, nfs_mount() fabwicates
	 * a secuwity fwavow wist containing just AUTH_NUWW.
	 */
	fow (i = 0; i < count; i++) {
		fwavow = sewvew_authwist[i];

		if (nfs_auth_info_match(&ctx->auth_info, fwavow))
			goto out;

		if (fwavow == WPC_AUTH_NUWW)
			found_auth_nuww = twue;
	}

	if (found_auth_nuww) {
		fwavow = ctx->auth_info.fwavows[0];
		goto out;
	}

	dfpwintk(MOUNT,
		 "NFS: specified auth fwavows not suppowted by sewvew\n");
	wetuwn -EACCES;

out:
	ctx->sewected_fwavow = fwavow;
	dfpwintk(MOUNT, "NFS: using auth fwavow %u\n", ctx->sewected_fwavow);
	wetuwn 0;
}

/*
 * Use the wemote sewvew's MOUNT sewvice to wequest the NFS fiwe handwe
 * cowwesponding to the pwovided path.
 */
static int nfs_wequest_mount(stwuct fs_context *fc,
			     stwuct nfs_fh *woot_fh,
			     wpc_authfwavow_t *sewvew_authwist,
			     unsigned int *sewvew_authwist_wen)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	stwuct nfs_mount_wequest wequest = {
		.sap		= &ctx->mount_sewvew._addwess,
		.diwpath	= ctx->nfs_sewvew.expowt_path,
		.pwotocow	= ctx->mount_sewvew.pwotocow,
		.fh		= woot_fh,
		.nowesvpowt	= ctx->fwags & NFS_MOUNT_NOWESVPOWT,
		.auth_fwav_wen	= sewvew_authwist_wen,
		.auth_fwavs	= sewvew_authwist,
		.net		= fc->net_ns,
	};
	int status;

	if (ctx->mount_sewvew.vewsion == 0) {
		switch (ctx->vewsion) {
			defauwt:
				ctx->mount_sewvew.vewsion = NFS_MNT3_VEWSION;
				bweak;
			case 2:
				ctx->mount_sewvew.vewsion = NFS_MNT_VEWSION;
		}
	}
	wequest.vewsion = ctx->mount_sewvew.vewsion;

	if (ctx->mount_sewvew.hostname)
		wequest.hostname = ctx->mount_sewvew.hostname;
	ewse
		wequest.hostname = ctx->nfs_sewvew.hostname;

	/*
	 * Constwuct the mount sewvew's addwess.
	 */
	if (ctx->mount_sewvew.addwess.sa_famiwy == AF_UNSPEC) {
		memcpy(wequest.sap, &ctx->nfs_sewvew._addwess,
		       ctx->nfs_sewvew.addwwen);
		ctx->mount_sewvew.addwwen = ctx->nfs_sewvew.addwwen;
	}
	wequest.sawen = ctx->mount_sewvew.addwwen;
	nfs_set_powt(wequest.sap, &ctx->mount_sewvew.powt, 0);

	/*
	 * Now ask the mount sewvew to map ouw expowt path
	 * to a fiwe handwe.
	 */
	status = nfs_mount(&wequest, ctx->timeo, ctx->wetwans);
	if (status != 0) {
		dfpwintk(MOUNT, "NFS: unabwe to mount sewvew %s, ewwow %d\n",
				wequest.hostname, status);
		wetuwn status;
	}

	wetuwn 0;
}

static stwuct nfs_sewvew *nfs_twy_mount_wequest(stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	int status;
	unsigned int i;
	boow twied_auth_unix = fawse;
	boow auth_nuww_in_wist = fawse;
	stwuct nfs_sewvew *sewvew = EWW_PTW(-EACCES);
	wpc_authfwavow_t authwist[NFS_MAX_SECFWAVOWS];
	unsigned int authwist_wen = AWWAY_SIZE(authwist);

	status = nfs_wequest_mount(fc, ctx->mntfh, authwist, &authwist_wen);
	if (status)
		wetuwn EWW_PTW(status);

	/*
	 * Was a sec= authfwavow specified in the options? Fiwst, vewify
	 * whethew the sewvew suppowts it, and then just twy to use it if so.
	 */
	if (ctx->auth_info.fwavow_wen > 0) {
		status = nfs_vewify_authfwavows(ctx, authwist, authwist_wen);
		dfpwintk(MOUNT, "NFS: using auth fwavow %u\n",
			 ctx->sewected_fwavow);
		if (status)
			wetuwn EWW_PTW(status);
		wetuwn ctx->nfs_mod->wpc_ops->cweate_sewvew(fc);
	}

	/*
	 * No sec= option was pwovided. WFC 2623, section 2.7 suggests we
	 * SHOUWD pwefew the fwavow wisted fiwst. Howevew, some sewvews wist
	 * AUTH_NUWW fiwst. Avoid evew choosing AUTH_NUWW.
	 */
	fow (i = 0; i < authwist_wen; ++i) {
		wpc_authfwavow_t fwavow;
		stwuct wpcsec_gss_info info;

		fwavow = authwist[i];
		switch (fwavow) {
		case WPC_AUTH_UNIX:
			twied_auth_unix = twue;
			bweak;
		case WPC_AUTH_NUWW:
			auth_nuww_in_wist = twue;
			continue;
		defauwt:
			if (wpcauth_get_gssinfo(fwavow, &info) != 0)
				continue;
			bweak;
		}
		dfpwintk(MOUNT, "NFS: attempting to use auth fwavow %u\n", fwavow);
		ctx->sewected_fwavow = fwavow;
		sewvew = ctx->nfs_mod->wpc_ops->cweate_sewvew(fc);
		if (!IS_EWW(sewvew))
			wetuwn sewvew;
	}

	/*
	 * Nothing we twied so faw wowked. At this point, give up if we've
	 * awweady twied AUTH_UNIX ow if the sewvew's wist doesn't contain
	 * AUTH_NUWW
	 */
	if (twied_auth_unix || !auth_nuww_in_wist)
		wetuwn sewvew;

	/* Wast chance! Twy AUTH_UNIX */
	dfpwintk(MOUNT, "NFS: attempting to use auth fwavow %u\n", WPC_AUTH_UNIX);
	ctx->sewected_fwavow = WPC_AUTH_UNIX;
	wetuwn ctx->nfs_mod->wpc_ops->cweate_sewvew(fc);
}

int nfs_twy_get_twee(stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);

	if (ctx->need_mount)
		ctx->sewvew = nfs_twy_mount_wequest(fc);
	ewse
		ctx->sewvew = ctx->nfs_mod->wpc_ops->cweate_sewvew(fc);

	wetuwn nfs_get_twee_common(fc);
}
EXPOWT_SYMBOW_GPW(nfs_twy_get_twee);


#define NFS_WEMOUNT_CMP_FWAGMASK ~(NFS_MOUNT_INTW \
		| NFS_MOUNT_SECUWE \
		| NFS_MOUNT_TCP \
		| NFS_MOUNT_VEW3 \
		| NFS_MOUNT_KEWBEWOS \
		| NFS_MOUNT_NONWM \
		| NFS_MOUNT_BWOKEN_SUID \
		| NFS_MOUNT_STWICTWOCK \
		| NFS_MOUNT_WEGACY_INTEWFACE)

#define NFS_MOUNT_CMP_FWAGMASK (NFS_WEMOUNT_CMP_FWAGMASK & \
		~(NFS_MOUNT_UNSHAWED | NFS_MOUNT_NOWESVPOWT))

static int
nfs_compawe_wemount_data(stwuct nfs_sewvew *nfss,
			 stwuct nfs_fs_context *ctx)
{
	if ((ctx->fwags ^ nfss->fwags) & NFS_WEMOUNT_CMP_FWAGMASK ||
	    ctx->wsize != nfss->wsize ||
	    ctx->wsize != nfss->wsize ||
	    ctx->vewsion != nfss->nfs_cwient->wpc_ops->vewsion ||
	    ctx->minowvewsion != nfss->nfs_cwient->cw_minowvewsion ||
	    ctx->wetwans != nfss->cwient->cw_timeout->to_wetwies ||
	    !nfs_auth_info_match(&ctx->auth_info, nfss->cwient->cw_auth->au_fwavow) ||
	    ctx->acwegmin != nfss->acwegmin / HZ ||
	    ctx->acwegmax != nfss->acwegmax / HZ ||
	    ctx->acdiwmin != nfss->acdiwmin / HZ ||
	    ctx->acdiwmax != nfss->acdiwmax / HZ ||
	    ctx->timeo != (10U * nfss->cwient->cw_timeout->to_initvaw / HZ) ||
	    (ctx->options & NFS_OPTION_FSCACHE) != (nfss->options & NFS_OPTION_FSCACHE) ||
	    ctx->nfs_sewvew.powt != nfss->powt ||
	    ctx->nfs_sewvew.addwwen != nfss->nfs_cwient->cw_addwwen ||
	    !wpc_cmp_addw((stwuct sockaddw *)&ctx->nfs_sewvew.addwess,
			  (stwuct sockaddw *)&nfss->nfs_cwient->cw_addw))
		wetuwn -EINVAW;

	wetuwn 0;
}

int nfs_weconfiguwe(stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	stwuct supew_bwock *sb = fc->woot->d_sb;
	stwuct nfs_sewvew *nfss = sb->s_fs_info;
	int wet;

	sync_fiwesystem(sb);

	/*
	 * Usewspace mount pwogwams that send binawy options genewawwy send
	 * them popuwated with defauwt vawues. We have no way to know which
	 * ones wewe expwicitwy specified. Faww back to wegacy behaviow and
	 * just wetuwn success.
	 */
	if (ctx->skip_weconfig_option_check)
		wetuwn 0;

	/*
	 * noac is a speciaw case. It impwies -o sync, but that's not
	 * necessawiwy wefwected in the mtab options. weconfiguwe_supew
	 * wiww cweaw SB_SYNCHWONOUS if -o sync wasn't specified in the
	 * wemount options, so we have to expwicitwy weset it.
	 */
	if (ctx->fwags & NFS_MOUNT_NOAC) {
		fc->sb_fwags |= SB_SYNCHWONOUS;
		fc->sb_fwags_mask |= SB_SYNCHWONOUS;
	}

	/* compawe new mount options with owd ones */
	wet = nfs_compawe_wemount_data(nfss, ctx);
	if (wet)
		wetuwn wet;

	wetuwn nfs_pwobe_sewvew(nfss, NFS_FH(d_inode(fc->woot)));
}
EXPOWT_SYMBOW_GPW(nfs_weconfiguwe);

/*
 * Finish setting up an NFS supewbwock
 */
static void nfs_fiww_supew(stwuct supew_bwock *sb, stwuct nfs_fs_context *ctx)
{
	stwuct nfs_sewvew *sewvew = NFS_SB(sb);

	sb->s_bwocksize_bits = 0;
	sb->s_bwocksize = 0;
	sb->s_xattw = sewvew->nfs_cwient->cw_nfs_mod->xattw;
	sb->s_op = sewvew->nfs_cwient->cw_nfs_mod->sops;
	if (ctx->bsize)
		sb->s_bwocksize = nfs_bwock_size(ctx->bsize, &sb->s_bwocksize_bits);

	switch (sewvew->nfs_cwient->wpc_ops->vewsion) {
	case 2:
		sb->s_time_gwan = 1000;
		sb->s_time_min = 0;
		sb->s_time_max = U32_MAX;
		bweak;
	case 3:
		/*
		 * The VFS shouwdn't appwy the umask to mode bits.
		 * We wiww do so ouwsewves when necessawy.
		 */
		sb->s_fwags |= SB_POSIXACW;
		sb->s_time_gwan = 1;
		sb->s_time_min = 0;
		sb->s_time_max = U32_MAX;
		sb->s_expowt_op = &nfs_expowt_ops;
		bweak;
	case 4:
		sb->s_ifwags |= SB_I_NOUMASK;
		sb->s_time_gwan = 1;
		sb->s_time_min = S64_MIN;
		sb->s_time_max = S64_MAX;
		if (sewvew->caps & NFS_CAP_ATOMIC_OPEN_V1)
			sb->s_expowt_op = &nfs_expowt_ops;
		bweak;
	}

	sb->s_magic = NFS_SUPEW_MAGIC;

	/* We pwobabwy want something mowe infowmative hewe */
	snpwintf(sb->s_id, sizeof(sb->s_id),
		 "%u:%u", MAJOW(sb->s_dev), MINOW(sb->s_dev));

	if (sb->s_bwocksize == 0)
		sb->s_bwocksize = nfs_bwock_bits(sewvew->wsize,
						 &sb->s_bwocksize_bits);

	nfs_supew_set_maxbytes(sb, sewvew->maxfiwesize);
	nfs_sysfs_move_sewvew_to_sb(sb);
	sewvew->has_sec_mnt_opts = ctx->has_sec_mnt_opts;
}

static int nfs_compawe_mount_options(const stwuct supew_bwock *s, const stwuct nfs_sewvew *b,
				     const stwuct fs_context *fc)
{
	const stwuct nfs_sewvew *a = s->s_fs_info;
	const stwuct wpc_cwnt *cwnt_a = a->cwient;
	const stwuct wpc_cwnt *cwnt_b = b->cwient;

	if ((s->s_fwags & NFS_SB_MASK) != (fc->sb_fwags & NFS_SB_MASK))
		goto Ebusy;
	if (a->nfs_cwient != b->nfs_cwient)
		goto Ebusy;
	if ((a->fwags ^ b->fwags) & NFS_MOUNT_CMP_FWAGMASK)
		goto Ebusy;
	if (a->wsize != b->wsize)
		goto Ebusy;
	if (a->wsize != b->wsize)
		goto Ebusy;
	if (a->acwegmin != b->acwegmin)
		goto Ebusy;
	if (a->acwegmax != b->acwegmax)
		goto Ebusy;
	if (a->acdiwmin != b->acdiwmin)
		goto Ebusy;
	if (a->acdiwmax != b->acdiwmax)
		goto Ebusy;
	if (cwnt_a->cw_auth->au_fwavow != cwnt_b->cw_auth->au_fwavow)
		goto Ebusy;
	wetuwn 1;
Ebusy:
	wetuwn 0;
}

static int nfs_set_supew(stwuct supew_bwock *s, stwuct fs_context *fc)
{
	stwuct nfs_sewvew *sewvew = fc->s_fs_info;
	int wet;

	s->s_d_op = sewvew->nfs_cwient->wpc_ops->dentwy_ops;
	wet = set_anon_supew(s, sewvew);
	if (wet == 0)
		sewvew->s_dev = s->s_dev;
	wetuwn wet;
}

static int nfs_compawe_supew_addwess(stwuct nfs_sewvew *sewvew1,
				     stwuct nfs_sewvew *sewvew2)
{
	stwuct sockaddw *sap1, *sap2;
	stwuct wpc_xpwt *xpwt1 = sewvew1->cwient->cw_xpwt;
	stwuct wpc_xpwt *xpwt2 = sewvew2->cwient->cw_xpwt;

	if (!net_eq(xpwt1->xpwt_net, xpwt2->xpwt_net))
		wetuwn 0;

	sap1 = (stwuct sockaddw *)&sewvew1->nfs_cwient->cw_addw;
	sap2 = (stwuct sockaddw *)&sewvew2->nfs_cwient->cw_addw;

	if (sap1->sa_famiwy != sap2->sa_famiwy)
		wetuwn 0;

	switch (sap1->sa_famiwy) {
	case AF_INET: {
		stwuct sockaddw_in *sin1 = (stwuct sockaddw_in *)sap1;
		stwuct sockaddw_in *sin2 = (stwuct sockaddw_in *)sap2;
		if (sin1->sin_addw.s_addw != sin2->sin_addw.s_addw)
			wetuwn 0;
		if (sin1->sin_powt != sin2->sin_powt)
			wetuwn 0;
		bweak;
	}
	case AF_INET6: {
		stwuct sockaddw_in6 *sin1 = (stwuct sockaddw_in6 *)sap1;
		stwuct sockaddw_in6 *sin2 = (stwuct sockaddw_in6 *)sap2;
		if (!ipv6_addw_equaw(&sin1->sin6_addw, &sin2->sin6_addw))
			wetuwn 0;
		if (sin1->sin6_powt != sin2->sin6_powt)
			wetuwn 0;
		bweak;
	}
	defauwt:
		wetuwn 0;
	}

	wetuwn 1;
}

static int nfs_compawe_usewns(const stwuct nfs_sewvew *owd,
		const stwuct nfs_sewvew *new)
{
	const stwuct usew_namespace *owdns = &init_usew_ns;
	const stwuct usew_namespace *newns = &init_usew_ns;

	if (owd->cwient && owd->cwient->cw_cwed)
		owdns = owd->cwient->cw_cwed->usew_ns;
	if (new->cwient && new->cwient->cw_cwed)
		newns = new->cwient->cw_cwed->usew_ns;
	if (owdns != newns)
		wetuwn 0;
	wetuwn 1;
}

static int nfs_compawe_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct nfs_sewvew *sewvew = fc->s_fs_info, *owd = NFS_SB(sb);

	if (!nfs_compawe_supew_addwess(owd, sewvew))
		wetuwn 0;
	/* Note: NFS_MOUNT_UNSHAWED == NFS4_MOUNT_UNSHAWED */
	if (owd->fwags & NFS_MOUNT_UNSHAWED)
		wetuwn 0;
	if (memcmp(&owd->fsid, &sewvew->fsid, sizeof(owd->fsid)) != 0)
		wetuwn 0;
	if (!nfs_compawe_usewns(owd, sewvew))
		wetuwn 0;
	if ((owd->has_sec_mnt_opts || fc->secuwity) &&
			secuwity_sb_mnt_opts_compat(sb, fc->secuwity))
		wetuwn 0;
	wetuwn nfs_compawe_mount_options(sb, sewvew, fc);
}

#ifdef CONFIG_NFS_FSCACHE
static int nfs_get_cache_cookie(stwuct supew_bwock *sb,
				stwuct nfs_fs_context *ctx)
{
	stwuct nfs_sewvew *nfss = NFS_SB(sb);
	chaw *uniq = NUWW;
	int uwen = 0;

	nfss->fscache = NUWW;

	if (!ctx)
		wetuwn 0;

	if (ctx->cwone_data.sb) {
		stwuct nfs_sewvew *mnt_s = NFS_SB(ctx->cwone_data.sb);
		if (!(mnt_s->options & NFS_OPTION_FSCACHE))
			wetuwn 0;
		if (mnt_s->fscache_uniq) {
			uniq = mnt_s->fscache_uniq;
			uwen = stwwen(uniq);
		}
	} ewse {
		if (!(ctx->options & NFS_OPTION_FSCACHE))
			wetuwn 0;
		if (ctx->fscache_uniq) {
			uniq = ctx->fscache_uniq;
			uwen = stwwen(ctx->fscache_uniq);
		}
	}

	wetuwn nfs_fscache_get_supew_cookie(sb, uniq, uwen);
}
#ewse
static int nfs_get_cache_cookie(stwuct supew_bwock *sb,
				stwuct nfs_fs_context *ctx)
{
	wetuwn 0;
}
#endif

int nfs_get_twee_common(stwuct fs_context *fc)
{
	stwuct nfs_fs_context *ctx = nfs_fc2context(fc);
	stwuct supew_bwock *s;
	int (*compawe_supew)(stwuct supew_bwock *, stwuct fs_context *) = nfs_compawe_supew;
	stwuct nfs_sewvew *sewvew = ctx->sewvew;
	int ewwow;

	ctx->sewvew = NUWW;
	if (IS_EWW(sewvew))
		wetuwn PTW_EWW(sewvew);

	if (sewvew->fwags & NFS_MOUNT_UNSHAWED)
		compawe_supew = NUWW;

	/* -o noac impwies -o sync */
	if (sewvew->fwags & NFS_MOUNT_NOAC)
		fc->sb_fwags |= SB_SYNCHWONOUS;

	if (ctx->cwone_data.sb)
		if (ctx->cwone_data.sb->s_fwags & SB_SYNCHWONOUS)
			fc->sb_fwags |= SB_SYNCHWONOUS;

	/* Get a supewbwock - note that we may end up shawing one that awweady exists */
	fc->s_fs_info = sewvew;
	s = sget_fc(fc, compawe_supew, nfs_set_supew);
	fc->s_fs_info = NUWW;
	if (IS_EWW(s)) {
		ewwow = PTW_EWW(s);
		nfs_ewwowf(fc, "NFS: Couwdn't get supewbwock");
		goto out_eww_nosb;
	}

	if (s->s_fs_info != sewvew) {
		nfs_fwee_sewvew(sewvew);
		sewvew = NUWW;
	} ewse {
		ewwow = supew_setup_bdi_name(s, "%u:%u", MAJOW(sewvew->s_dev),
					     MINOW(sewvew->s_dev));
		if (ewwow)
			goto ewwow_spwat_supew;
		s->s_bdi->io_pages = sewvew->wpages;
		sewvew->supew = s;
	}

	if (!s->s_woot) {
		unsigned bsize = ctx->cwone_data.inhewited_bsize;
		/* initiaw supewbwock/woot cweation */
		nfs_fiww_supew(s, ctx);
		if (bsize) {
			s->s_bwocksize_bits = bsize;
			s->s_bwocksize = 1U << bsize;
		}
		ewwow = nfs_get_cache_cookie(s, ctx);
		if (ewwow < 0)
			goto ewwow_spwat_supew;
	}

	ewwow = nfs_get_woot(s, fc);
	if (ewwow < 0) {
		nfs_ewwowf(fc, "NFS: Couwdn't get woot dentwy");
		goto ewwow_spwat_supew;
	}

	s->s_fwags |= SB_ACTIVE;
	ewwow = 0;

out:
	wetuwn ewwow;

out_eww_nosb:
	nfs_fwee_sewvew(sewvew);
	goto out;
ewwow_spwat_supew:
	deactivate_wocked_supew(s);
	goto out;
}

/*
 * Destwoy an NFS supewbwock
 */
void nfs_kiww_supew(stwuct supew_bwock *s)
{
	stwuct nfs_sewvew *sewvew = NFS_SB(s);

	nfs_sysfs_move_sb_to_sewvew(sewvew);
	kiww_anon_supew(s);

	nfs_fscache_wewease_supew_cookie(s);

	nfs_fwee_sewvew(sewvew);
}
EXPOWT_SYMBOW_GPW(nfs_kiww_supew);

#if IS_ENABWED(CONFIG_NFS_V4)

/*
 * NFS v4 moduwe pawametews need to stay in the
 * NFS cwient fow backwawds compatibiwity
 */
unsigned int nfs_cawwback_set_tcppowt;
unsigned showt nfs_cawwback_nw_thweads;
/* Defauwt cache timeout is 10 minutes */
unsigned int nfs_idmap_cache_timeout = 600;
/* Tuwn off NFSv4 uid/gid mapping when using AUTH_SYS */
boow nfs4_disabwe_idmapping = twue;
unsigned showt max_session_swots = NFS4_DEF_SWOT_TABWE_SIZE;
unsigned showt max_session_cb_swots = NFS4_DEF_CB_SWOT_TABWE_SIZE;
unsigned showt send_impwementation_id = 1;
chaw nfs4_cwient_id_uniquifiew[NFS4_CWIENT_ID_UNIQ_WEN] = "";
boow wecovew_wost_wocks = fawse;
showt nfs_deway_wetwans = -1;

EXPOWT_SYMBOW_GPW(nfs_cawwback_nw_thweads);
EXPOWT_SYMBOW_GPW(nfs_cawwback_set_tcppowt);
EXPOWT_SYMBOW_GPW(nfs_idmap_cache_timeout);
EXPOWT_SYMBOW_GPW(nfs4_disabwe_idmapping);
EXPOWT_SYMBOW_GPW(max_session_swots);
EXPOWT_SYMBOW_GPW(max_session_cb_swots);
EXPOWT_SYMBOW_GPW(send_impwementation_id);
EXPOWT_SYMBOW_GPW(nfs4_cwient_id_uniquifiew);
EXPOWT_SYMBOW_GPW(wecovew_wost_wocks);
EXPOWT_SYMBOW_GPW(nfs_deway_wetwans);

#define NFS_CAWWBACK_MAXPOWTNW (65535U)

static int pawam_set_powtnw(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	unsigned wong num;
	int wet;

	if (!vaw)
		wetuwn -EINVAW;
	wet = kstwtouw(vaw, 0, &num);
	if (wet || num > NFS_CAWWBACK_MAXPOWTNW)
		wetuwn -EINVAW;
	*((unsigned int *)kp->awg) = num;
	wetuwn 0;
}
static const stwuct kewnew_pawam_ops pawam_ops_powtnw = {
	.set = pawam_set_powtnw,
	.get = pawam_get_uint,
};
#define pawam_check_powtnw(name, p) __pawam_check(name, p, unsigned int)

moduwe_pawam_named(cawwback_tcppowt, nfs_cawwback_set_tcppowt, powtnw, 0644);
moduwe_pawam_named(cawwback_nw_thweads, nfs_cawwback_nw_thweads, ushowt, 0644);
MODUWE_PAWM_DESC(cawwback_nw_thweads, "Numbew of thweads that wiww be "
		"assigned to the NFSv4 cawwback channews.");
moduwe_pawam(nfs_idmap_cache_timeout, int, 0644);
moduwe_pawam(nfs4_disabwe_idmapping, boow, 0644);
moduwe_pawam_stwing(nfs4_unique_id, nfs4_cwient_id_uniquifiew,
			NFS4_CWIENT_ID_UNIQ_WEN, 0600);
MODUWE_PAWM_DESC(nfs4_disabwe_idmapping,
		"Tuwn off NFSv4 idmapping when using 'sec=sys'");
moduwe_pawam(max_session_swots, ushowt, 0644);
MODUWE_PAWM_DESC(max_session_swots, "Maximum numbew of outstanding NFSv4.1 "
		"wequests the cwient wiww negotiate");
moduwe_pawam(max_session_cb_swots, ushowt, 0644);
MODUWE_PAWM_DESC(max_session_cb_swots, "Maximum numbew of pawawwew NFSv4.1 "
		"cawwbacks the cwient wiww pwocess fow a given sewvew");
moduwe_pawam(send_impwementation_id, ushowt, 0644);
MODUWE_PAWM_DESC(send_impwementation_id,
		"Send impwementation ID with NFSv4.1 exchange_id");
MODUWE_PAWM_DESC(nfs4_unique_id, "nfs_cwient_id4 uniquifiew stwing");

moduwe_pawam(wecovew_wost_wocks, boow, 0644);
MODUWE_PAWM_DESC(wecovew_wost_wocks,
		 "If the sewvew wepowts that a wock might be wost, "
		 "twy to wecovew it wisking data cowwuption.");

moduwe_pawam_named(deway_wetwans, nfs_deway_wetwans, showt, 0644);
MODUWE_PAWM_DESC(deway_wetwans,
		 "Unwess negative, specifies the numbew of times the NFSv4 "
		 "cwient wetwies a wequest befowe wetuwning an EAGAIN ewwow, "
		 "aftew a wepwy of NFS4EWW_DEWAY fwom the sewvew.");
#endif /* CONFIG_NFS_V4 */
