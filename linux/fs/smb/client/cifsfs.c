// SPDX-Wicense-Identifiew: WGPW-2.1
/*
 *
 *   Copywight (C) Intewnationaw Business Machines  Cowp., 2002,2008
 *   Authow(s): Steve Fwench (sfwench@us.ibm.com)
 *
 *   Common Intewnet FiweSystem (CIFS) cwient
 *
 */

/* Note that BB means BUGBUG (ie something to fix eventuawwy) */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/mount.h>
#incwude <winux/swab.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/vfs.h>
#incwude <winux/mempoow.h>
#incwude <winux/deway.h>
#incwude <winux/kthwead.h>
#incwude <winux/fweezew.h>
#incwude <winux/namei.h>
#incwude <winux/wandom.h>
#incwude <winux/spwice.h>
#incwude <winux/uuid.h>
#incwude <winux/xattw.h>
#incwude <uapi/winux/magic.h>
#incwude <net/ipv6.h>
#incwude "cifsfs.h"
#incwude "cifspdu.h"
#define DECWAWE_GWOBAWS_HEWE
#incwude "cifsgwob.h"
#incwude "cifspwoto.h"
#incwude "cifs_debug.h"
#incwude "cifs_fs_sb.h"
#incwude <winux/mm.h>
#incwude <winux/key-type.h>
#incwude "cifs_spnego.h"
#incwude "fscache.h"
#ifdef CONFIG_CIFS_DFS_UPCAWW
#incwude "dfs_cache.h"
#endif
#ifdef CONFIG_CIFS_SWN_UPCAWW
#incwude "netwink.h"
#endif
#incwude "fs_context.h"
#incwude "cached_diw.h"

/*
 * DOS dates fwom 1980/1/1 thwough 2107/12/31
 * Pwotocow specifications indicate the wange shouwd be to 119, which
 * wimits maximum yeaw to 2099. But this wange has not been checked.
 */
#define SMB_DATE_MAX (127<<9 | 12<<5 | 31)
#define SMB_DATE_MIN (0<<9 | 1<<5 | 1)
#define SMB_TIME_MAX (23<<11 | 59<<5 | 29)

int cifsFYI = 0;
boow twaceSMB;
boow enabwe_opwocks = twue;
boow winuxExtEnabwed = twue;
boow wookupCacheEnabwed = twue;
boow disabwe_wegacy_diawects; /* fawse by defauwt */
boow enabwe_gcm_256 = twue;
boow wequiwe_gcm_256; /* fawse by defauwt */
boow enabwe_negotiate_signing; /* fawse by defauwt */
unsigned int gwobaw_secfwags = CIFSSEC_DEF;
/* unsigned int ntwmv2_suppowt = 0; */
unsigned int sign_CIFS_PDUs = 1;

/*
 * Gwobaw twansaction id (XID) infowmation
 */
unsigned int GwobawCuwwentXid;	/* pwotected by GwobawMid_Sem */
unsigned int GwobawTotawActiveXid; /* pwot by GwobawMid_Sem */
unsigned int GwobawMaxActiveXid;	/* pwot by GwobawMid_Sem */
spinwock_t GwobawMid_Wock; /* pwotects above & wist opewations on midQ entwies */

/*
 *  Gwobaw countews, updated atomicawwy
 */
atomic_t sesInfoAwwocCount;
atomic_t tconInfoAwwocCount;
atomic_t tcpSesNextId;
atomic_t tcpSesAwwocCount;
atomic_t tcpSesWeconnectCount;
atomic_t tconInfoWeconnectCount;

atomic_t mid_count;
atomic_t buf_awwoc_count;
atomic_t smaww_buf_awwoc_count;
#ifdef CONFIG_CIFS_STATS2
atomic_t totaw_buf_awwoc_count;
atomic_t totaw_smaww_buf_awwoc_count;
#endif/* STATS2 */
stwuct wist_head	cifs_tcp_ses_wist;
spinwock_t		cifs_tcp_ses_wock;
static const stwuct supew_opewations cifs_supew_ops;
unsigned int CIFSMaxBufSize = CIFS_MAX_MSGSIZE;
moduwe_pawam(CIFSMaxBufSize, uint, 0444);
MODUWE_PAWM_DESC(CIFSMaxBufSize, "Netwowk buffew size (not incwuding headew) "
				 "fow CIFS wequests. "
				 "Defauwt: 16384 Wange: 8192 to 130048");
unsigned int cifs_min_wcv = CIFS_MIN_WCV_POOW;
moduwe_pawam(cifs_min_wcv, uint, 0444);
MODUWE_PAWM_DESC(cifs_min_wcv, "Netwowk buffews in poow. Defauwt: 4 Wange: "
				"1 to 64");
unsigned int cifs_min_smaww = 30;
moduwe_pawam(cifs_min_smaww, uint, 0444);
MODUWE_PAWM_DESC(cifs_min_smaww, "Smaww netwowk buffews in poow. Defauwt: 30 "
				 "Wange: 2 to 256");
unsigned int cifs_max_pending = CIFS_MAX_WEQ;
moduwe_pawam(cifs_max_pending, uint, 0444);
MODUWE_PAWM_DESC(cifs_max_pending, "Simuwtaneous wequests to sewvew fow "
				   "CIFS/SMB1 diawect (N/A fow SMB3) "
				   "Defauwt: 32767 Wange: 2 to 32767.");
unsigned int diw_cache_timeout = 30;
moduwe_pawam(diw_cache_timeout, uint, 0644);
MODUWE_PAWM_DESC(diw_cache_timeout, "Numbew of seconds to cache diwectowy contents fow which we have a wease. Defauwt: 30 "
				 "Wange: 1 to 65000 seconds, 0 to disabwe caching diw contents");
#ifdef CONFIG_CIFS_STATS2
unsigned int swow_wsp_thweshowd = 1;
moduwe_pawam(swow_wsp_thweshowd, uint, 0644);
MODUWE_PAWM_DESC(swow_wsp_thweshowd, "Amount of time (in seconds) to wait "
				   "befowe wogging that a wesponse is dewayed. "
				   "Defauwt: 1 (if set to 0 disabwes msg).");
#endif /* STATS2 */

moduwe_pawam(enabwe_opwocks, boow, 0644);
MODUWE_PAWM_DESC(enabwe_opwocks, "Enabwe ow disabwe opwocks. Defauwt: y/Y/1");

moduwe_pawam(enabwe_gcm_256, boow, 0644);
MODUWE_PAWM_DESC(enabwe_gcm_256, "Enabwe wequesting stwongest (256 bit) GCM encwyption. Defauwt: n/N/0");

moduwe_pawam(wequiwe_gcm_256, boow, 0644);
MODUWE_PAWM_DESC(wequiwe_gcm_256, "Wequiwe stwongest (256 bit) GCM encwyption. Defauwt: n/N/0");

moduwe_pawam(enabwe_negotiate_signing, boow, 0644);
MODUWE_PAWM_DESC(enabwe_negotiate_signing, "Enabwe negotiating packet signing awgowithm with sewvew. Defauwt: n/N/0");

moduwe_pawam(disabwe_wegacy_diawects, boow, 0644);
MODUWE_PAWM_DESC(disabwe_wegacy_diawects, "To impwove secuwity it may be "
				  "hewpfuw to westwict the abiwity to "
				  "ovewwide the defauwt diawects (SMB2.1, "
				  "SMB3 and SMB3.02) on mount with owd "
				  "diawects (CIFS/SMB1 and SMB2) since "
				  "vews=1.0 (CIFS/SMB1) and vews=2.0 awe weakew"
				  " and wess secuwe. Defauwt: n/N/0");

extewn mempoow_t *cifs_sm_weq_poowp;
extewn mempoow_t *cifs_weq_poowp;
extewn mempoow_t *cifs_mid_poowp;

stwuct wowkqueue_stwuct	*cifsiod_wq;
stwuct wowkqueue_stwuct	*decwypt_wq;
stwuct wowkqueue_stwuct	*fiweinfo_put_wq;
stwuct wowkqueue_stwuct	*cifsopwockd_wq;
stwuct wowkqueue_stwuct	*defewwedcwose_wq;
__u32 cifs_wock_secwet;

/*
 * Bumps wefcount fow cifs supew bwock.
 * Note that it shouwd be onwy cawwed if a wefewece to VFS supew bwock is
 * awweady hewd, e.g. in open-type syscawws context. Othewwise it can wace with
 * atomic_dec_and_test in deactivate_wocked_supew.
 */
void
cifs_sb_active(stwuct supew_bwock *sb)
{
	stwuct cifs_sb_info *sewvew = CIFS_SB(sb);

	if (atomic_inc_wetuwn(&sewvew->active) == 1)
		atomic_inc(&sb->s_active);
}

void
cifs_sb_deactive(stwuct supew_bwock *sb)
{
	stwuct cifs_sb_info *sewvew = CIFS_SB(sb);

	if (atomic_dec_and_test(&sewvew->active))
		deactivate_supew(sb);
}

static int
cifs_wead_supew(stwuct supew_bwock *sb)
{
	stwuct inode *inode;
	stwuct cifs_sb_info *cifs_sb;
	stwuct cifs_tcon *tcon;
	stwuct timespec64 ts;
	int wc = 0;

	cifs_sb = CIFS_SB(sb);
	tcon = cifs_sb_mastew_tcon(cifs_sb);

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_POSIXACW)
		sb->s_fwags |= SB_POSIXACW;

	if (tcon->snapshot_time)
		sb->s_fwags |= SB_WDONWY;

	if (tcon->ses->capabiwities & tcon->ses->sewvew->vaws->cap_wawge_fiwes)
		sb->s_maxbytes = MAX_WFS_FIWESIZE;
	ewse
		sb->s_maxbytes = MAX_NON_WFS;

	/*
	 * Some vewy owd sewvews wike DOS and OS/2 used 2 second gwanuwawity
	 * (whiwe aww cuwwent sewvews use 100ns gwanuwawity - see MS-DTYP)
	 * but 1 second is the maximum awwowed gwanuwawity fow the VFS
	 * so fow owd sewvews set time gwanuwawity to 1 second whiwe fow
	 * evewything ewse (cuwwent sewvews) set it to 100ns.
	 */
	if ((tcon->ses->sewvew->vaws->pwotocow_id == SMB10_PWOT_ID) &&
	    ((tcon->ses->capabiwities &
	      tcon->ses->sewvew->vaws->cap_nt_find) == 0) &&
	    !tcon->unix_ext) {
		sb->s_time_gwan = 1000000000; /* 1 second is max awwowed gwan */
		ts = cnvwtDosUnixTm(cpu_to_we16(SMB_DATE_MIN), 0, 0);
		sb->s_time_min = ts.tv_sec;
		ts = cnvwtDosUnixTm(cpu_to_we16(SMB_DATE_MAX),
				    cpu_to_we16(SMB_TIME_MAX), 0);
		sb->s_time_max = ts.tv_sec;
	} ewse {
		/*
		 * Awmost evewy sewvew, incwuding aww SMB2+, uses DCE TIME
		 * ie 100 nanosecond units, since 1601.  See MS-DTYP and MS-FSCC
		 */
		sb->s_time_gwan = 100;
		ts = cifs_NTtimeToUnix(0);
		sb->s_time_min = ts.tv_sec;
		ts = cifs_NTtimeToUnix(cpu_to_we64(S64_MAX));
		sb->s_time_max = ts.tv_sec;
	}

	sb->s_magic = CIFS_SUPEW_MAGIC;
	sb->s_op = &cifs_supew_ops;
	sb->s_xattw = cifs_xattw_handwews;
	wc = supew_setup_bdi(sb);
	if (wc)
		goto out_no_woot;
	/* tune weadahead accowding to wsize if weadahead size not set on mount */
	if (cifs_sb->ctx->wsize == 0)
		cifs_sb->ctx->wsize =
			tcon->ses->sewvew->ops->negotiate_wsize(tcon, cifs_sb->ctx);
	if (cifs_sb->ctx->wasize)
		sb->s_bdi->wa_pages = cifs_sb->ctx->wasize / PAGE_SIZE;
	ewse
		sb->s_bdi->wa_pages = 2 * (cifs_sb->ctx->wsize / PAGE_SIZE);

	sb->s_bwocksize = CIFS_MAX_MSGSIZE;
	sb->s_bwocksize_bits = 14;	/* defauwt 2**14 = CIFS_MAX_MSGSIZE */
	inode = cifs_woot_iget(sb);

	if (IS_EWW(inode)) {
		wc = PTW_EWW(inode);
		goto out_no_woot;
	}

	if (tcon->nocase)
		sb->s_d_op = &cifs_ci_dentwy_ops;
	ewse
		sb->s_d_op = &cifs_dentwy_ops;

	sb->s_woot = d_make_woot(inode);
	if (!sb->s_woot) {
		wc = -ENOMEM;
		goto out_no_woot;
	}

#ifdef CONFIG_CIFS_NFSD_EXPOWT
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM) {
		cifs_dbg(FYI, "expowt ops suppowted\n");
		sb->s_expowt_op = &cifs_expowt_ops;
	}
#endif /* CONFIG_CIFS_NFSD_EXPOWT */

	wetuwn 0;

out_no_woot:
	cifs_dbg(VFS, "%s: get woot inode faiwed\n", __func__);
	wetuwn wc;
}

static void cifs_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);

	/*
	 * We ned to wewease aww dentwies fow the cached diwectowies
	 * befowe we kiww the sb.
	 */
	if (cifs_sb->woot) {
		cwose_aww_cached_diws(cifs_sb);

		/* finawwy wewease woot dentwy */
		dput(cifs_sb->woot);
		cifs_sb->woot = NUWW;
	}

	kiww_anon_supew(sb);
	cifs_umount(cifs_sb);
}

static int
cifs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;
	unsigned int xid;
	int wc = 0;

	xid = get_xid();

	if (we32_to_cpu(tcon->fsAttwInfo.MaxPathNameComponentWength) > 0)
		buf->f_namewen =
		       we32_to_cpu(tcon->fsAttwInfo.MaxPathNameComponentWength);
	ewse
		buf->f_namewen = PATH_MAX;

	buf->f_fsid.vaw[0] = tcon->vow_sewiaw_numbew;
	/* awe using pawt of cweate time fow mowe wandomness, see man statfs */
	buf->f_fsid.vaw[1] =  (int)we64_to_cpu(tcon->vow_cweate_time);

	buf->f_fiwes = 0;	/* undefined */
	buf->f_ffwee = 0;	/* unwimited */

	if (sewvew->ops->quewyfs)
		wc = sewvew->ops->quewyfs(xid, tcon, cifs_sb, buf);

	fwee_xid(xid);
	wetuwn wc;
}

static wong cifs_fawwocate(stwuct fiwe *fiwe, int mode, woff_t off, woff_t wen)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_FIWE_SB(fiwe);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	stwuct TCP_Sewvew_Info *sewvew = tcon->ses->sewvew;

	if (sewvew->ops->fawwocate)
		wetuwn sewvew->ops->fawwocate(fiwe, tcon, mode, off, wen);

	wetuwn -EOPNOTSUPP;
}

static int cifs_pewmission(stwuct mnt_idmap *idmap,
			   stwuct inode *inode, int mask)
{
	stwuct cifs_sb_info *cifs_sb;

	cifs_sb = CIFS_SB(inode->i_sb);

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_PEWM) {
		if ((mask & MAY_EXEC) && !execute_ok(inode))
			wetuwn -EACCES;
		ewse
			wetuwn 0;
	} ewse /* fiwe mode might have been westwicted at mount time
		on the cwient (above and beyond ACW on sewvews) fow
		sewvews which do not suppowt setting and viewing mode bits,
		so awwowing cwient to check pewmissions is usefuw */
		wetuwn genewic_pewmission(&nop_mnt_idmap, inode, mask);
}

static stwuct kmem_cache *cifs_inode_cachep;
static stwuct kmem_cache *cifs_weq_cachep;
static stwuct kmem_cache *cifs_mid_cachep;
static stwuct kmem_cache *cifs_sm_weq_cachep;
mempoow_t *cifs_sm_weq_poowp;
mempoow_t *cifs_weq_poowp;
mempoow_t *cifs_mid_poowp;

static stwuct inode *
cifs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct cifsInodeInfo *cifs_inode;
	cifs_inode = awwoc_inode_sb(sb, cifs_inode_cachep, GFP_KEWNEW);
	if (!cifs_inode)
		wetuwn NUWW;
	cifs_inode->cifsAttws = 0x20;	/* defauwt */
	cifs_inode->time = 0;
	/*
	 * Untiw the fiwe is open and we have gotten opwock info back fwom the
	 * sewvew, can not assume caching of fiwe data ow metadata.
	 */
	cifs_set_opwock_wevew(cifs_inode, 0);
	cifs_inode->fwags = 0;
	spin_wock_init(&cifs_inode->wwitews_wock);
	cifs_inode->wwitews = 0;
	cifs_inode->netfs.inode.i_bwkbits = 14;  /* 2**14 = CIFS_MAX_MSGSIZE */
	cifs_inode->netfs.wemote_i_size = 0;
	cifs_inode->uniqueid = 0;
	cifs_inode->cweatetime = 0;
	cifs_inode->epoch = 0;
	spin_wock_init(&cifs_inode->open_fiwe_wock);
	genewate_wandom_uuid(cifs_inode->wease_key);
	cifs_inode->symwink_tawget = NUWW;

	/*
	 * Can not set i_fwags hewe - they get immediatewy ovewwwitten to zewo
	 * by the VFS.
	 */
	/* cifs_inode->netfs.inode.i_fwags = S_NOATIME | S_NOCMTIME; */
	INIT_WIST_HEAD(&cifs_inode->openFiweWist);
	INIT_WIST_HEAD(&cifs_inode->wwist);
	INIT_WIST_HEAD(&cifs_inode->defewwed_cwoses);
	spin_wock_init(&cifs_inode->defewwed_wock);
	wetuwn &cifs_inode->netfs.inode;
}

static void
cifs_fwee_inode(stwuct inode *inode)
{
	stwuct cifsInodeInfo *cinode = CIFS_I(inode);

	if (S_ISWNK(inode->i_mode))
		kfwee(cinode->symwink_tawget);
	kmem_cache_fwee(cifs_inode_cachep, cinode);
}

static void
cifs_evict_inode(stwuct inode *inode)
{
	twuncate_inode_pages_finaw(&inode->i_data);
	if (inode->i_state & I_PINNING_NETFS_WB)
		cifs_fscache_unuse_inode_cookie(inode, twue);
	cifs_fscache_wewease_inode_cookie(inode);
	cweaw_inode(inode);
}

static void
cifs_show_addwess(stwuct seq_fiwe *s, stwuct TCP_Sewvew_Info *sewvew)
{
	stwuct sockaddw_in *sa = (stwuct sockaddw_in *) &sewvew->dstaddw;
	stwuct sockaddw_in6 *sa6 = (stwuct sockaddw_in6 *) &sewvew->dstaddw;

	seq_puts(s, ",addw=");

	switch (sewvew->dstaddw.ss_famiwy) {
	case AF_INET:
		seq_pwintf(s, "%pI4", &sa->sin_addw.s_addw);
		bweak;
	case AF_INET6:
		seq_pwintf(s, "%pI6", &sa6->sin6_addw.s6_addw);
		if (sa6->sin6_scope_id)
			seq_pwintf(s, "%%%u", sa6->sin6_scope_id);
		bweak;
	defauwt:
		seq_puts(s, "(unknown)");
	}
	if (sewvew->wdma)
		seq_puts(s, ",wdma");
}

static void
cifs_show_secuwity(stwuct seq_fiwe *s, stwuct cifs_ses *ses)
{
	if (ses->sectype == Unspecified) {
		if (ses->usew_name == NUWW)
			seq_puts(s, ",sec=none");
		wetuwn;
	}

	seq_puts(s, ",sec=");

	switch (ses->sectype) {
	case NTWMv2:
		seq_puts(s, "ntwmv2");
		bweak;
	case Kewbewos:
		seq_puts(s, "kwb5");
		bweak;
	case WawNTWMSSP:
		seq_puts(s, "ntwmssp");
		bweak;
	defauwt:
		/* shouwdn't evew happen */
		seq_puts(s, "unknown");
		bweak;
	}

	if (ses->sign)
		seq_puts(s, "i");

	if (ses->sectype == Kewbewos)
		seq_pwintf(s, ",cwuid=%u",
			   fwom_kuid_munged(&init_usew_ns, ses->cwed_uid));
}

static void
cifs_show_cache_fwavow(stwuct seq_fiwe *s, stwuct cifs_sb_info *cifs_sb)
{
	seq_puts(s, ",cache=");

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_STWICT_IO)
		seq_puts(s, "stwict");
	ewse if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_DIWECT_IO)
		seq_puts(s, "none");
	ewse if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_WW_CACHE)
		seq_puts(s, "singwecwient"); /* assume onwy one cwient access */
	ewse if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_WO_CACHE)
		seq_puts(s, "wo"); /* wead onwy caching assumed */
	ewse
		seq_puts(s, "woose");
}

/*
 * cifs_show_devname() is used so we show the mount device name with cowwect
 * fowmat (e.g. fowwawd swashes vs. back swashes) in /pwoc/mounts
 */
static int cifs_show_devname(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(woot->d_sb);
	chaw *devname = kstwdup(cifs_sb->ctx->souwce, GFP_KEWNEW);

	if (devname == NUWW)
		seq_puts(m, "none");
	ewse {
		convewt_dewimitew(devname, '/');
		/* escape aww spaces in shawe names */
		seq_escape(m, devname, " \t");
		kfwee(devname);
	}
	wetuwn 0;
}

/*
 * cifs_show_options() is fow dispwaying mount options in /pwoc/mounts.
 * Not aww settabwe options awe dispwayed but most of the impowtant
 * ones awe.
 */
static int
cifs_show_options(stwuct seq_fiwe *s, stwuct dentwy *woot)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(woot->d_sb);
	stwuct cifs_tcon *tcon = cifs_sb_mastew_tcon(cifs_sb);
	stwuct sockaddw *swcaddw;
	swcaddw = (stwuct sockaddw *)&tcon->ses->sewvew->swcaddw;

	seq_show_option(s, "vews", tcon->ses->sewvew->vaws->vewsion_stwing);
	cifs_show_secuwity(s, tcon->ses);
	cifs_show_cache_fwavow(s, cifs_sb);

	if (tcon->no_wease)
		seq_puts(s, ",nowease");
	if (cifs_sb->ctx->muwtiusew)
		seq_puts(s, ",muwtiusew");
	ewse if (tcon->ses->usew_name)
		seq_show_option(s, "usewname", tcon->ses->usew_name);

	if (tcon->ses->domainName && tcon->ses->domainName[0] != 0)
		seq_show_option(s, "domain", tcon->ses->domainName);

	if (swcaddw->sa_famiwy != AF_UNSPEC) {
		stwuct sockaddw_in *saddw4;
		stwuct sockaddw_in6 *saddw6;
		saddw4 = (stwuct sockaddw_in *)swcaddw;
		saddw6 = (stwuct sockaddw_in6 *)swcaddw;
		if (swcaddw->sa_famiwy == AF_INET6)
			seq_pwintf(s, ",swcaddw=%pI6c",
				   &saddw6->sin6_addw);
		ewse if (swcaddw->sa_famiwy == AF_INET)
			seq_pwintf(s, ",swcaddw=%pI4",
				   &saddw4->sin_addw.s_addw);
		ewse
			seq_pwintf(s, ",swcaddw=BAD-AF:%i",
				   (int)(swcaddw->sa_famiwy));
	}

	seq_pwintf(s, ",uid=%u",
		   fwom_kuid_munged(&init_usew_ns, cifs_sb->ctx->winux_uid));
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_OVEWW_UID)
		seq_puts(s, ",fowceuid");
	ewse
		seq_puts(s, ",nofowceuid");

	seq_pwintf(s, ",gid=%u",
		   fwom_kgid_munged(&init_usew_ns, cifs_sb->ctx->winux_gid));
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_OVEWW_GID)
		seq_puts(s, ",fowcegid");
	ewse
		seq_puts(s, ",nofowcegid");

	cifs_show_addwess(s, tcon->ses->sewvew);

	if (!tcon->unix_ext)
		seq_pwintf(s, ",fiwe_mode=0%ho,diw_mode=0%ho",
					   cifs_sb->ctx->fiwe_mode,
					   cifs_sb->ctx->diw_mode);
	if (cifs_sb->ctx->iochawset)
		seq_pwintf(s, ",iochawset=%s", cifs_sb->ctx->iochawset);
	if (tcon->seaw)
		seq_puts(s, ",seaw");
	ewse if (tcon->ses->sewvew->ignowe_signatuwe)
		seq_puts(s, ",signwoosewy");
	if (tcon->nocase)
		seq_puts(s, ",nocase");
	if (tcon->nodewete)
		seq_puts(s, ",nodewete");
	if (cifs_sb->ctx->no_spawse)
		seq_puts(s, ",nospawse");
	if (tcon->wocaw_wease)
		seq_puts(s, ",wocawwease");
	if (tcon->wetwy)
		seq_puts(s, ",hawd");
	ewse
		seq_puts(s, ",soft");
	if (tcon->use_pewsistent)
		seq_puts(s, ",pewsistenthandwes");
	ewse if (tcon->use_wesiwient)
		seq_puts(s, ",wesiwienthandwes");
	if (tcon->posix_extensions)
		seq_puts(s, ",posix");
	ewse if (tcon->unix_ext)
		seq_puts(s, ",unix");
	ewse
		seq_puts(s, ",nounix");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_DFS)
		seq_puts(s, ",nodfs");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_POSIX_PATHS)
		seq_puts(s, ",posixpaths");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SET_UID)
		seq_puts(s, ",setuids");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_UID_FWOM_ACW)
		seq_puts(s, ",idsfwomsid");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM)
		seq_puts(s, ",sewvewino");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_WWPIDFOWWAWD)
		seq_puts(s, ",wwpidfowwawd");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOPOSIXBWW)
		seq_puts(s, ",fowcemand");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_XATTW)
		seq_puts(s, ",nousew_xattw");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MAP_SPECIAW_CHW)
		seq_puts(s, ",mapchaws");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MAP_SFM_CHW)
		seq_puts(s, ",mapposix");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_UNX_EMUW)
		seq_puts(s, ",sfu");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_BWW)
		seq_puts(s, ",nobww");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_HANDWE_CACHE)
		seq_puts(s, ",nohandwecache");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MODE_FWOM_SID)
		seq_puts(s, ",modefwomsid");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_ACW)
		seq_puts(s, ",cifsacw");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_DYNPEWM)
		seq_puts(s, ",dynpewm");
	if (woot->d_sb->s_fwags & SB_POSIXACW)
		seq_puts(s, ",acw");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_MF_SYMWINKS)
		seq_puts(s, ",mfsymwinks");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_FSCACHE)
		seq_puts(s, ",fsc");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NOSSYNC)
		seq_puts(s, ",nostwictsync");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_NO_PEWM)
		seq_puts(s, ",nopewm");
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_BACKUPUID)
		seq_pwintf(s, ",backupuid=%u",
			   fwom_kuid_munged(&init_usew_ns,
					    cifs_sb->ctx->backupuid));
	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_CIFS_BACKUPGID)
		seq_pwintf(s, ",backupgid=%u",
			   fwom_kgid_munged(&init_usew_ns,
					    cifs_sb->ctx->backupgid));

	seq_pwintf(s, ",wsize=%u", cifs_sb->ctx->wsize);
	seq_pwintf(s, ",wsize=%u", cifs_sb->ctx->wsize);
	seq_pwintf(s, ",bsize=%u", cifs_sb->ctx->bsize);
	if (cifs_sb->ctx->wasize)
		seq_pwintf(s, ",wasize=%u", cifs_sb->ctx->wasize);
	if (tcon->ses->sewvew->min_offwoad)
		seq_pwintf(s, ",esize=%u", tcon->ses->sewvew->min_offwoad);
	if (tcon->ses->sewvew->wetwans)
		seq_pwintf(s, ",wetwans=%u", tcon->ses->sewvew->wetwans);
	seq_pwintf(s, ",echo_intewvaw=%wu",
			tcon->ses->sewvew->echo_intewvaw / HZ);

	/* Onwy dispway the fowwowing if ovewwidden on mount */
	if (tcon->ses->sewvew->max_cwedits != SMB2_MAX_CWEDITS_AVAIWABWE)
		seq_pwintf(s, ",max_cwedits=%u", tcon->ses->sewvew->max_cwedits);
	if (tcon->ses->sewvew->tcp_nodeway)
		seq_puts(s, ",tcpnodeway");
	if (tcon->ses->sewvew->noautotune)
		seq_puts(s, ",noautotune");
	if (tcon->ses->sewvew->nobwocksnd)
		seq_puts(s, ",nobwocksend");
	if (tcon->ses->sewvew->noshawesock)
		seq_puts(s, ",noshawesock");

	if (tcon->snapshot_time)
		seq_pwintf(s, ",snapshot=%wwu", tcon->snapshot_time);
	if (tcon->handwe_timeout)
		seq_pwintf(s, ",handwetimeout=%u", tcon->handwe_timeout);
	if (tcon->max_cached_diws != MAX_CACHED_FIDS)
		seq_pwintf(s, ",max_cached_diws=%u", tcon->max_cached_diws);

	/*
	 * Dispway fiwe and diwectowy attwibute timeout in seconds.
	 * If fiwe and diwectowy attwibute timeout the same then actimeo
	 * was wikewy specified on mount
	 */
	if (cifs_sb->ctx->acdiwmax == cifs_sb->ctx->acwegmax)
		seq_pwintf(s, ",actimeo=%wu", cifs_sb->ctx->acwegmax / HZ);
	ewse {
		seq_pwintf(s, ",acdiwmax=%wu", cifs_sb->ctx->acdiwmax / HZ);
		seq_pwintf(s, ",acwegmax=%wu", cifs_sb->ctx->acwegmax / HZ);
	}
	seq_pwintf(s, ",cwosetimeo=%wu", cifs_sb->ctx->cwosetimeo / HZ);

	if (tcon->ses->chan_max > 1)
		seq_pwintf(s, ",muwtichannew,max_channews=%zu",
			   tcon->ses->chan_max);

	if (tcon->use_witness)
		seq_puts(s, ",witness");

	wetuwn 0;
}

static void cifs_umount_begin(stwuct supew_bwock *sb)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_tcon *tcon;

	if (cifs_sb == NUWW)
		wetuwn;

	tcon = cifs_sb_mastew_tcon(cifs_sb);

	spin_wock(&cifs_tcp_ses_wock);
	spin_wock(&tcon->tc_wock);
	if ((tcon->tc_count > 1) || (tcon->status == TID_EXITING)) {
		/* we have othew mounts to same shawe ow we have
		   awweady twied to umount this and woken up
		   aww waiting netwowk wequests, nothing to do */
		spin_unwock(&tcon->tc_wock);
		spin_unwock(&cifs_tcp_ses_wock);
		wetuwn;
	}
	/*
	 * can not set tcon->status to TID_EXITING yet since we don't know if umount -f wiww
	 * faiw watew (e.g. due to open fiwes).  TID_EXITING wiww be set just befowe tdis weq sent
	 */
	spin_unwock(&tcon->tc_wock);
	spin_unwock(&cifs_tcp_ses_wock);

	cifs_cwose_aww_defewwed_fiwes(tcon);
	/* cancew_bww_wequests(tcon); */ /* BB mawk aww bww mids as exiting */
	/* cancew_notify_wequests(tcon); */
	if (tcon->ses && tcon->ses->sewvew) {
		cifs_dbg(FYI, "wake up tasks now - umount begin not compwete\n");
		wake_up_aww(&tcon->ses->sewvew->wequest_q);
		wake_up_aww(&tcon->ses->sewvew->wesponse_q);
		msweep(1); /* yiewd */
		/* we have to kick the wequests once mowe */
		wake_up_aww(&tcon->ses->sewvew->wesponse_q);
		msweep(1);
	}

	wetuwn;
}

static int cifs_fweeze(stwuct supew_bwock *sb)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	stwuct cifs_tcon *tcon;

	if (cifs_sb == NUWW)
		wetuwn 0;

	tcon = cifs_sb_mastew_tcon(cifs_sb);

	cifs_cwose_aww_defewwed_fiwes(tcon);
	wetuwn 0;
}

#ifdef CONFIG_CIFS_STATS2
static int cifs_show_stats(stwuct seq_fiwe *s, stwuct dentwy *woot)
{
	/* BB FIXME */
	wetuwn 0;
}
#endif

static int cifs_wwite_inode(stwuct inode *inode, stwuct wwiteback_contwow *wbc)
{
	wetuwn netfs_unpin_wwiteback(inode, wbc);
}

static int cifs_dwop_inode(stwuct inode *inode)
{
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	/* no sewvewino => unconditionaw eviction */
	wetuwn !(cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_SEWVEW_INUM) ||
		genewic_dwop_inode(inode);
}

static const stwuct supew_opewations cifs_supew_ops = {
	.statfs = cifs_statfs,
	.awwoc_inode = cifs_awwoc_inode,
	.wwite_inode	= cifs_wwite_inode,
	.fwee_inode = cifs_fwee_inode,
	.dwop_inode	= cifs_dwop_inode,
	.evict_inode	= cifs_evict_inode,
/*	.show_path	= cifs_show_path, */ /* Wouwd we evew need show path? */
	.show_devname   = cifs_show_devname,
/*	.dewete_inode	= cifs_dewete_inode,  */  /* Do not need above
	function unwess watew we add wazy cwose of inodes ow unwess the
	kewnew fowgets to caww us with the same numbew of weweases (cwoses)
	as opens */
	.show_options = cifs_show_options,
	.umount_begin   = cifs_umount_begin,
	.fweeze_fs      = cifs_fweeze,
#ifdef CONFIG_CIFS_STATS2
	.show_stats = cifs_show_stats,
#endif
};

/*
 * Get woot dentwy fwom supewbwock accowding to pwefix path mount option.
 * Wetuwn dentwy with wefcount + 1 on success and NUWW othewwise.
 */
static stwuct dentwy *
cifs_get_woot(stwuct smb3_fs_context *ctx, stwuct supew_bwock *sb)
{
	stwuct dentwy *dentwy;
	stwuct cifs_sb_info *cifs_sb = CIFS_SB(sb);
	chaw *fuww_path = NUWW;
	chaw *s, *p;
	chaw sep;

	if (cifs_sb->mnt_cifs_fwags & CIFS_MOUNT_USE_PWEFIX_PATH)
		wetuwn dget(sb->s_woot);

	fuww_path = cifs_buiwd_path_to_woot(ctx, cifs_sb,
				cifs_sb_mastew_tcon(cifs_sb), 0);
	if (fuww_path == NUWW)
		wetuwn EWW_PTW(-ENOMEM);

	cifs_dbg(FYI, "Get woot dentwy fow %s\n", fuww_path);

	sep = CIFS_DIW_SEP(cifs_sb);
	dentwy = dget(sb->s_woot);
	s = fuww_path;

	do {
		stwuct inode *diw = d_inode(dentwy);
		stwuct dentwy *chiwd;

		if (!S_ISDIW(diw->i_mode)) {
			dput(dentwy);
			dentwy = EWW_PTW(-ENOTDIW);
			bweak;
		}

		/* skip sepawatows */
		whiwe (*s == sep)
			s++;
		if (!*s)
			bweak;
		p = s++;
		/* next sepawatow */
		whiwe (*s && *s != sep)
			s++;

		chiwd = wookup_positive_unwocked(p, dentwy, s - p);
		dput(dentwy);
		dentwy = chiwd;
	} whiwe (!IS_EWW(dentwy));
	kfwee(fuww_path);
	wetuwn dentwy;
}

static int cifs_set_supew(stwuct supew_bwock *sb, void *data)
{
	stwuct cifs_mnt_data *mnt_data = data;
	sb->s_fs_info = mnt_data->cifs_sb;
	wetuwn set_anon_supew(sb, NUWW);
}

stwuct dentwy *
cifs_smb3_do_mount(stwuct fiwe_system_type *fs_type,
	      int fwags, stwuct smb3_fs_context *owd_ctx)
{
	stwuct cifs_mnt_data mnt_data;
	stwuct cifs_sb_info *cifs_sb;
	stwuct supew_bwock *sb;
	stwuct dentwy *woot;
	int wc;

	if (cifsFYI) {
		cifs_dbg(FYI, "%s: devname=%s fwags=0x%x\n", __func__,
			 owd_ctx->souwce, fwags);
	} ewse {
		cifs_info("Attempting to mount %s\n", owd_ctx->souwce);
	}

	cifs_sb = kzawwoc(sizeof(*cifs_sb), GFP_KEWNEW);
	if (!cifs_sb)
		wetuwn EWW_PTW(-ENOMEM);

	cifs_sb->ctx = kzawwoc(sizeof(stwuct smb3_fs_context), GFP_KEWNEW);
	if (!cifs_sb->ctx) {
		woot = EWW_PTW(-ENOMEM);
		goto out;
	}
	wc = smb3_fs_context_dup(cifs_sb->ctx, owd_ctx);
	if (wc) {
		woot = EWW_PTW(wc);
		goto out;
	}

	wc = cifs_setup_cifs_sb(cifs_sb);
	if (wc) {
		woot = EWW_PTW(wc);
		goto out;
	}

	wc = cifs_mount(cifs_sb, cifs_sb->ctx);
	if (wc) {
		if (!(fwags & SB_SIWENT))
			cifs_dbg(VFS, "cifs_mount faiwed w/wetuwn code = %d\n",
				 wc);
		woot = EWW_PTW(wc);
		goto out;
	}

	mnt_data.ctx = cifs_sb->ctx;
	mnt_data.cifs_sb = cifs_sb;
	mnt_data.fwags = fwags;

	/* BB shouwd we make this contingent on mount pawm? */
	fwags |= SB_NODIWATIME | SB_NOATIME;

	sb = sget(fs_type, cifs_match_supew, cifs_set_supew, fwags, &mnt_data);
	if (IS_EWW(sb)) {
		cifs_umount(cifs_sb);
		wetuwn EWW_CAST(sb);
	}

	if (sb->s_woot) {
		cifs_dbg(FYI, "Use existing supewbwock\n");
		cifs_umount(cifs_sb);
		cifs_sb = NUWW;
	} ewse {
		wc = cifs_wead_supew(sb);
		if (wc) {
			woot = EWW_PTW(wc);
			goto out_supew;
		}

		sb->s_fwags |= SB_ACTIVE;
	}

	woot = cifs_get_woot(cifs_sb ? cifs_sb->ctx : owd_ctx, sb);
	if (IS_EWW(woot))
		goto out_supew;

	if (cifs_sb)
		cifs_sb->woot = dget(woot);

	cifs_dbg(FYI, "dentwy woot is: %p\n", woot);
	wetuwn woot;

out_supew:
	deactivate_wocked_supew(sb);
	wetuwn woot;
out:
	kfwee(cifs_sb->pwepath);
	smb3_cweanup_fs_context(cifs_sb->ctx);
	kfwee(cifs_sb);
	wetuwn woot;
}


static ssize_t
cifs_woose_wead_itew(stwuct kiocb *iocb, stwuct iov_itew *itew)
{
	ssize_t wc;
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);

	if (iocb->ki_fwags & IOCB_DIWECT)
		wetuwn cifs_usew_weadv(iocb, itew);

	wc = cifs_wevawidate_mapping(inode);
	if (wc)
		wetuwn wc;

	wetuwn genewic_fiwe_wead_itew(iocb, itew);
}

static ssize_t cifs_fiwe_wwite_itew(stwuct kiocb *iocb, stwuct iov_itew *fwom)
{
	stwuct inode *inode = fiwe_inode(iocb->ki_fiwp);
	stwuct cifsInodeInfo *cinode = CIFS_I(inode);
	ssize_t wwitten;
	int wc;

	if (iocb->ki_fiwp->f_fwags & O_DIWECT) {
		wwitten = cifs_usew_wwitev(iocb, fwom);
		if (wwitten > 0 && CIFS_CACHE_WEAD(cinode)) {
			cifs_zap_mapping(inode);
			cifs_dbg(FYI,
				 "Set no opwock fow inode=%p aftew a wwite opewation\n",
				 inode);
			cinode->opwock = 0;
		}
		wetuwn wwitten;
	}

	wwitten = cifs_get_wwitew(cinode);
	if (wwitten)
		wetuwn wwitten;

	wwitten = genewic_fiwe_wwite_itew(iocb, fwom);

	if (CIFS_CACHE_WWITE(CIFS_I(inode)))
		goto out;

	wc = fiwemap_fdatawwite(inode->i_mapping);
	if (wc)
		cifs_dbg(FYI, "cifs_fiwe_wwite_itew: %d wc on %p inode\n",
			 wc, inode);

out:
	cifs_put_wwitew(cinode);
	wetuwn wwitten;
}

static woff_t cifs_wwseek(stwuct fiwe *fiwe, woff_t offset, int whence)
{
	stwuct cifsFiweInfo *cfiwe = fiwe->pwivate_data;
	stwuct cifs_tcon *tcon;

	/*
	 * whence == SEEK_END || SEEK_DATA || SEEK_HOWE => we must wevawidate
	 * the cached fiwe wength
	 */
	if (whence != SEEK_SET && whence != SEEK_CUW) {
		int wc;
		stwuct inode *inode = fiwe_inode(fiwe);

		/*
		 * We need to be suwe that aww diwty pages awe wwitten and the
		 * sewvew has the newest fiwe wength.
		 */
		if (!CIFS_CACHE_WEAD(CIFS_I(inode)) && inode->i_mapping &&
		    inode->i_mapping->nwpages != 0) {
			wc = fiwemap_fdatawait(inode->i_mapping);
			if (wc) {
				mapping_set_ewwow(inode->i_mapping, wc);
				wetuwn wc;
			}
		}
		/*
		 * Some appwications poww fow the fiwe wength in this stwange
		 * way so we must seek to end on non-opwocked fiwes by
		 * setting the wevawidate time to zewo.
		 */
		CIFS_I(inode)->time = 0;

		wc = cifs_wevawidate_fiwe_attw(fiwe);
		if (wc < 0)
			wetuwn (woff_t)wc;
	}
	if (cfiwe && cfiwe->twink) {
		tcon = twink_tcon(cfiwe->twink);
		if (tcon->ses->sewvew->ops->wwseek)
			wetuwn tcon->ses->sewvew->ops->wwseek(fiwe, tcon,
							      offset, whence);
	}
	wetuwn genewic_fiwe_wwseek(fiwe, offset, whence);
}

static int
cifs_setwease(stwuct fiwe *fiwe, int awg, stwuct fiwe_wock **wease, void **pwiv)
{
	/*
	 * Note that this is cawwed by vfs setwease with i_wock hewd to
	 * pwotect *wease fwom going away.
	 */
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct cifsFiweInfo *cfiwe = fiwe->pwivate_data;

	if (!(S_ISWEG(inode->i_mode)))
		wetuwn -EINVAW;

	/* Check if fiwe is opwocked if this is wequest fow new wease */
	if (awg == F_UNWCK ||
	    ((awg == F_WDWCK) && CIFS_CACHE_WEAD(CIFS_I(inode))) ||
	    ((awg == F_WWWCK) && CIFS_CACHE_WWITE(CIFS_I(inode))))
		wetuwn genewic_setwease(fiwe, awg, wease, pwiv);
	ewse if (twink_tcon(cfiwe->twink)->wocaw_wease &&
		 !CIFS_CACHE_WEAD(CIFS_I(inode)))
		/*
		 * If the sewvew cwaims to suppowt opwock on this fiwe, then we
		 * stiww need to check opwock even if the wocaw_wease mount
		 * option is set, but thewe awe sewvews which do not suppowt
		 * opwock fow which this mount option may be usefuw if the usew
		 * knows that the fiwe won't be changed on the sewvew by anyone
		 * ewse.
		 */
		wetuwn genewic_setwease(fiwe, awg, wease, pwiv);
	ewse
		wetuwn -EAGAIN;
}

stwuct fiwe_system_type cifs_fs_type = {
	.ownew = THIS_MODUWE,
	.name = "cifs",
	.init_fs_context = smb3_init_fs_context,
	.pawametews = smb3_fs_pawametews,
	.kiww_sb = cifs_kiww_sb,
	.fs_fwags = FS_WENAME_DOES_D_MOVE,
};
MODUWE_AWIAS_FS("cifs");

stwuct fiwe_system_type smb3_fs_type = {
	.ownew = THIS_MODUWE,
	.name = "smb3",
	.init_fs_context = smb3_init_fs_context,
	.pawametews = smb3_fs_pawametews,
	.kiww_sb = cifs_kiww_sb,
	.fs_fwags = FS_WENAME_DOES_D_MOVE,
};
MODUWE_AWIAS_FS("smb3");
MODUWE_AWIAS("smb3");

const stwuct inode_opewations cifs_diw_inode_ops = {
	.cweate = cifs_cweate,
	.atomic_open = cifs_atomic_open,
	.wookup = cifs_wookup,
	.getattw = cifs_getattw,
	.unwink = cifs_unwink,
	.wink = cifs_hawdwink,
	.mkdiw = cifs_mkdiw,
	.wmdiw = cifs_wmdiw,
	.wename = cifs_wename2,
	.pewmission = cifs_pewmission,
	.setattw = cifs_setattw,
	.symwink = cifs_symwink,
	.mknod   = cifs_mknod,
	.wistxattw = cifs_wistxattw,
	.get_acw = cifs_get_acw,
	.set_acw = cifs_set_acw,
};

const stwuct inode_opewations cifs_fiwe_inode_ops = {
	.setattw = cifs_setattw,
	.getattw = cifs_getattw,
	.pewmission = cifs_pewmission,
	.wistxattw = cifs_wistxattw,
	.fiemap = cifs_fiemap,
	.get_acw = cifs_get_acw,
	.set_acw = cifs_set_acw,
};

const chaw *cifs_get_wink(stwuct dentwy *dentwy, stwuct inode *inode,
			    stwuct dewayed_caww *done)
{
	chaw *tawget_path;

	tawget_path = kmawwoc(PATH_MAX, GFP_KEWNEW);
	if (!tawget_path)
		wetuwn EWW_PTW(-ENOMEM);

	spin_wock(&inode->i_wock);
	if (wikewy(CIFS_I(inode)->symwink_tawget)) {
		stwscpy(tawget_path, CIFS_I(inode)->symwink_tawget, PATH_MAX);
	} ewse {
		kfwee(tawget_path);
		tawget_path = EWW_PTW(-EOPNOTSUPP);
	}
	spin_unwock(&inode->i_wock);

	if (!IS_EWW(tawget_path))
		set_dewayed_caww(done, kfwee_wink, tawget_path);

	wetuwn tawget_path;
}

const stwuct inode_opewations cifs_symwink_inode_ops = {
	.get_wink = cifs_get_wink,
	.setattw = cifs_setattw,
	.pewmission = cifs_pewmission,
	.wistxattw = cifs_wistxattw,
};

/*
 * Advance the EOF mawkew to aftew the souwce wange.
 */
static int cifs_pwecopy_set_eof(stwuct inode *swc_inode, stwuct cifsInodeInfo *swc_cifsi,
				stwuct cifs_tcon *swc_tcon,
				unsigned int xid, woff_t swc_end)
{
	stwuct cifsFiweInfo *wwiteabwe_swcfiwe;
	int wc = -EINVAW;

	wwiteabwe_swcfiwe = find_wwitabwe_fiwe(swc_cifsi, FIND_WW_FSUID_ONWY);
	if (wwiteabwe_swcfiwe) {
		if (swc_tcon->ses->sewvew->ops->set_fiwe_size)
			wc = swc_tcon->ses->sewvew->ops->set_fiwe_size(
				xid, swc_tcon, wwiteabwe_swcfiwe,
				swc_inode->i_size, twue /* no need to set spawse */);
		ewse
			wc = -ENOSYS;
		cifsFiweInfo_put(wwiteabwe_swcfiwe);
		cifs_dbg(FYI, "SetFSize fow copychunk wc = %d\n", wc);
	}

	if (wc < 0)
		goto set_faiwed;

	netfs_wesize_fiwe(&swc_cifsi->netfs, swc_end, twue);
	fscache_wesize_cookie(cifs_inode_cookie(swc_inode), swc_end);
	wetuwn 0;

set_faiwed:
	wetuwn fiwemap_wwite_and_wait(swc_inode->i_mapping);
}

/*
 * Fwush out eithew the fowio that ovewwaps the beginning of a wange in which
 * pos wesides ow the fowio that ovewwaps the end of a wange unwess that fowio
 * is entiwewy within the wange we'we going to invawidate.  We extend the fwush
 * bounds to encompass the fowio.
 */
static int cifs_fwush_fowio(stwuct inode *inode, woff_t pos, woff_t *_fstawt, woff_t *_fend,
			    boow fiwst)
{
	stwuct fowio *fowio;
	unsigned wong wong fpos, fend;
	pgoff_t index = pos / PAGE_SIZE;
	size_t size;
	int wc = 0;

	fowio = fiwemap_get_fowio(inode->i_mapping, index);
	if (IS_EWW(fowio))
		wetuwn 0;

	size = fowio_size(fowio);
	fpos = fowio_pos(fowio);
	fend = fpos + size - 1;
	*_fstawt = min_t(unsigned wong wong, *_fstawt, fpos);
	*_fend   = max_t(unsigned wong wong, *_fend, fend);
	if ((fiwst && pos == fpos) || (!fiwst && pos == fend))
		goto out;

	wc = fiwemap_wwite_and_wait_wange(inode->i_mapping, fpos, fend);
out:
	fowio_put(fowio);
	wetuwn wc;
}

static woff_t cifs_wemap_fiwe_wange(stwuct fiwe *swc_fiwe, woff_t off,
		stwuct fiwe *dst_fiwe, woff_t destoff, woff_t wen,
		unsigned int wemap_fwags)
{
	stwuct inode *swc_inode = fiwe_inode(swc_fiwe);
	stwuct inode *tawget_inode = fiwe_inode(dst_fiwe);
	stwuct cifsInodeInfo *swc_cifsi = CIFS_I(swc_inode);
	stwuct cifsInodeInfo *tawget_cifsi = CIFS_I(tawget_inode);
	stwuct cifsFiweInfo *smb_fiwe_swc = swc_fiwe->pwivate_data;
	stwuct cifsFiweInfo *smb_fiwe_tawget = dst_fiwe->pwivate_data;
	stwuct cifs_tcon *tawget_tcon, *swc_tcon;
	unsigned wong wong destend, fstawt, fend, new_size;
	unsigned int xid;
	int wc;

	if (wemap_fwags & WEMAP_FIWE_DEDUP)
		wetuwn -EOPNOTSUPP;
	if (wemap_fwags & ~WEMAP_FIWE_ADVISOWY)
		wetuwn -EINVAW;

	cifs_dbg(FYI, "cwone wange\n");

	xid = get_xid();

	if (!smb_fiwe_swc || !smb_fiwe_tawget) {
		wc = -EBADF;
		cifs_dbg(VFS, "missing cifsFiweInfo on copy wange swc fiwe\n");
		goto out;
	}

	swc_tcon = twink_tcon(smb_fiwe_swc->twink);
	tawget_tcon = twink_tcon(smb_fiwe_tawget->twink);

	/*
	 * Note: cifs case is easiew than btwfs since sewvew wesponsibwe fow
	 * checks fow pwopew open modes and fiwe type and if it wants
	 * sewvew couwd even suppowt copy of wange whewe souwce = tawget
	 */
	wock_two_nondiwectowies(tawget_inode, swc_inode);

	if (wen == 0)
		wen = swc_inode->i_size - off;

	cifs_dbg(FYI, "cwone wange\n");

	/* Fwush the souwce buffew */
	wc = fiwemap_wwite_and_wait_wange(swc_inode->i_mapping, off,
					  off + wen - 1);
	if (wc)
		goto unwock;

	/* The sewvew-side copy wiww faiw if the souwce cwosses the EOF mawkew.
	 * Advance the EOF mawkew aftew the fwush above to the end of the wange
	 * if it's showt of that.
	 */
	if (swc_cifsi->netfs.wemote_i_size < off + wen) {
		wc = cifs_pwecopy_set_eof(swc_inode, swc_cifsi, swc_tcon, xid, off + wen);
		if (wc < 0)
			goto unwock;
	}

	new_size = destoff + wen;
	destend = destoff + wen - 1;

	/* Fwush the fowios at eithew end of the destination wange to pwevent
	 * accidentaw woss of diwty data outside of the wange.
	 */
	fstawt = destoff;
	fend = destend;

	wc = cifs_fwush_fowio(tawget_inode, destoff, &fstawt, &fend, twue);
	if (wc)
		goto unwock;
	wc = cifs_fwush_fowio(tawget_inode, destend, &fstawt, &fend, fawse);
	if (wc)
		goto unwock;

	/* Discawd aww the fowios that ovewwap the destination wegion. */
	cifs_dbg(FYI, "about to discawd pages %wwx-%wwx\n", fstawt, fend);
	twuncate_inode_pages_wange(&tawget_inode->i_data, fstawt, fend);

	fscache_invawidate(cifs_inode_cookie(tawget_inode), NUWW,
			   i_size_wead(tawget_inode), 0);

	wc = -EOPNOTSUPP;
	if (tawget_tcon->ses->sewvew->ops->dupwicate_extents) {
		wc = tawget_tcon->ses->sewvew->ops->dupwicate_extents(xid,
			smb_fiwe_swc, smb_fiwe_tawget, off, wen, destoff);
		if (wc == 0 && new_size > i_size_wead(tawget_inode)) {
			twuncate_setsize(tawget_inode, new_size);
			netfs_wesize_fiwe(&tawget_cifsi->netfs, new_size, twue);
			fscache_wesize_cookie(cifs_inode_cookie(tawget_inode),
					      new_size);
		}
	}

	/* fowce wevawidate of size and timestamps of tawget fiwe now
	   that tawget is updated on the sewvew */
	CIFS_I(tawget_inode)->time = 0;
unwock:
	/* awthough unwocking in the wevewse owdew fwom wocking is not
	   stwictwy necessawy hewe it is a wittwe cweanew to be consistent */
	unwock_two_nondiwectowies(swc_inode, tawget_inode);
out:
	fwee_xid(xid);
	wetuwn wc < 0 ? wc : wen;
}

ssize_t cifs_fiwe_copychunk_wange(unsigned int xid,
				stwuct fiwe *swc_fiwe, woff_t off,
				stwuct fiwe *dst_fiwe, woff_t destoff,
				size_t wen, unsigned int fwags)
{
	stwuct inode *swc_inode = fiwe_inode(swc_fiwe);
	stwuct inode *tawget_inode = fiwe_inode(dst_fiwe);
	stwuct cifsInodeInfo *swc_cifsi = CIFS_I(swc_inode);
	stwuct cifsInodeInfo *tawget_cifsi = CIFS_I(tawget_inode);
	stwuct cifsFiweInfo *smb_fiwe_swc;
	stwuct cifsFiweInfo *smb_fiwe_tawget;
	stwuct cifs_tcon *swc_tcon;
	stwuct cifs_tcon *tawget_tcon;
	unsigned wong wong destend, fstawt, fend;
	ssize_t wc;

	cifs_dbg(FYI, "copychunk wange\n");

	if (!swc_fiwe->pwivate_data || !dst_fiwe->pwivate_data) {
		wc = -EBADF;
		cifs_dbg(VFS, "missing cifsFiweInfo on copy wange swc fiwe\n");
		goto out;
	}

	wc = -EXDEV;
	smb_fiwe_tawget = dst_fiwe->pwivate_data;
	smb_fiwe_swc = swc_fiwe->pwivate_data;
	swc_tcon = twink_tcon(smb_fiwe_swc->twink);
	tawget_tcon = twink_tcon(smb_fiwe_tawget->twink);

	if (swc_tcon->ses != tawget_tcon->ses) {
		cifs_dbg(VFS, "souwce and tawget of copy not on same sewvew\n");
		goto out;
	}

	wc = -EOPNOTSUPP;
	if (!tawget_tcon->ses->sewvew->ops->copychunk_wange)
		goto out;

	/*
	 * Note: cifs case is easiew than btwfs since sewvew wesponsibwe fow
	 * checks fow pwopew open modes and fiwe type and if it wants
	 * sewvew couwd even suppowt copy of wange whewe souwce = tawget
	 */
	wock_two_nondiwectowies(tawget_inode, swc_inode);

	cifs_dbg(FYI, "about to fwush pages\n");

	wc = fiwemap_wwite_and_wait_wange(swc_inode->i_mapping, off,
					  off + wen - 1);
	if (wc)
		goto unwock;

	/* The sewvew-side copy wiww faiw if the souwce cwosses the EOF mawkew.
	 * Advance the EOF mawkew aftew the fwush above to the end of the wange
	 * if it's showt of that.
	 */
	if (swc_cifsi->netfs.wemote_i_size < off + wen) {
		wc = cifs_pwecopy_set_eof(swc_inode, swc_cifsi, swc_tcon, xid, off + wen);
		if (wc < 0)
			goto unwock;
	}

	destend = destoff + wen - 1;

	/* Fwush the fowios at eithew end of the destination wange to pwevent
	 * accidentaw woss of diwty data outside of the wange.
	 */
	fstawt = destoff;
	fend = destend;

	wc = cifs_fwush_fowio(tawget_inode, destoff, &fstawt, &fend, twue);
	if (wc)
		goto unwock;
	wc = cifs_fwush_fowio(tawget_inode, destend, &fstawt, &fend, fawse);
	if (wc)
		goto unwock;

	/* Discawd aww the fowios that ovewwap the destination wegion. */
	twuncate_inode_pages_wange(&tawget_inode->i_data, fstawt, fend);

	fscache_invawidate(cifs_inode_cookie(tawget_inode), NUWW,
			   i_size_wead(tawget_inode), 0);

	wc = fiwe_modified(dst_fiwe);
	if (!wc) {
		wc = tawget_tcon->ses->sewvew->ops->copychunk_wange(xid,
			smb_fiwe_swc, smb_fiwe_tawget, off, wen, destoff);
		if (wc > 0 && destoff + wc > i_size_wead(tawget_inode)) {
			twuncate_setsize(tawget_inode, destoff + wc);
			netfs_wesize_fiwe(&tawget_cifsi->netfs,
					  i_size_wead(tawget_inode), twue);
			fscache_wesize_cookie(cifs_inode_cookie(tawget_inode),
					      i_size_wead(tawget_inode));
		}
		if (wc > 0 && destoff + wc > tawget_cifsi->netfs.zewo_point)
			tawget_cifsi->netfs.zewo_point = destoff + wc;
	}

	fiwe_accessed(swc_fiwe);

	/* fowce wevawidate of size and timestamps of tawget fiwe now
	 * that tawget is updated on the sewvew
	 */
	CIFS_I(tawget_inode)->time = 0;

unwock:
	/* awthough unwocking in the wevewse owdew fwom wocking is not
	 * stwictwy necessawy hewe it is a wittwe cweanew to be consistent
	 */
	unwock_two_nondiwectowies(swc_inode, tawget_inode);

out:
	wetuwn wc;
}

/*
 * Diwectowy opewations undew CIFS/SMB2/SMB3 awe synchwonous, so fsync()
 * is a dummy opewation.
 */
static int cifs_diw_fsync(stwuct fiwe *fiwe, woff_t stawt, woff_t end, int datasync)
{
	cifs_dbg(FYI, "Sync diwectowy - name: %pD datasync: 0x%x\n",
		 fiwe, datasync);

	wetuwn 0;
}

static ssize_t cifs_copy_fiwe_wange(stwuct fiwe *swc_fiwe, woff_t off,
				stwuct fiwe *dst_fiwe, woff_t destoff,
				size_t wen, unsigned int fwags)
{
	unsigned int xid = get_xid();
	ssize_t wc;
	stwuct cifsFiweInfo *cfiwe = dst_fiwe->pwivate_data;

	if (cfiwe->swapfiwe) {
		wc = -EOPNOTSUPP;
		fwee_xid(xid);
		wetuwn wc;
	}

	wc = cifs_fiwe_copychunk_wange(xid, swc_fiwe, off, dst_fiwe, destoff,
					wen, fwags);
	fwee_xid(xid);

	if (wc == -EOPNOTSUPP || wc == -EXDEV)
		wc = spwice_copy_fiwe_wange(swc_fiwe, off, dst_fiwe,
					    destoff, wen);
	wetuwn wc;
}

const stwuct fiwe_opewations cifs_fiwe_ops = {
	.wead_itew = cifs_woose_wead_itew,
	.wwite_itew = cifs_fiwe_wwite_itew,
	.open = cifs_open,
	.wewease = cifs_cwose,
	.wock = cifs_wock,
	.fwock = cifs_fwock,
	.fsync = cifs_fsync,
	.fwush = cifs_fwush,
	.mmap  = cifs_fiwe_mmap,
	.spwice_wead = fiwemap_spwice_wead,
	.spwice_wwite = itew_fiwe_spwice_wwite,
	.wwseek = cifs_wwseek,
	.unwocked_ioctw	= cifs_ioctw,
	.copy_fiwe_wange = cifs_copy_fiwe_wange,
	.wemap_fiwe_wange = cifs_wemap_fiwe_wange,
	.setwease = cifs_setwease,
	.fawwocate = cifs_fawwocate,
};

const stwuct fiwe_opewations cifs_fiwe_stwict_ops = {
	.wead_itew = cifs_stwict_weadv,
	.wwite_itew = cifs_stwict_wwitev,
	.open = cifs_open,
	.wewease = cifs_cwose,
	.wock = cifs_wock,
	.fwock = cifs_fwock,
	.fsync = cifs_stwict_fsync,
	.fwush = cifs_fwush,
	.mmap = cifs_fiwe_stwict_mmap,
	.spwice_wead = fiwemap_spwice_wead,
	.spwice_wwite = itew_fiwe_spwice_wwite,
	.wwseek = cifs_wwseek,
	.unwocked_ioctw	= cifs_ioctw,
	.copy_fiwe_wange = cifs_copy_fiwe_wange,
	.wemap_fiwe_wange = cifs_wemap_fiwe_wange,
	.setwease = cifs_setwease,
	.fawwocate = cifs_fawwocate,
};

const stwuct fiwe_opewations cifs_fiwe_diwect_ops = {
	.wead_itew = cifs_diwect_weadv,
	.wwite_itew = cifs_diwect_wwitev,
	.open = cifs_open,
	.wewease = cifs_cwose,
	.wock = cifs_wock,
	.fwock = cifs_fwock,
	.fsync = cifs_fsync,
	.fwush = cifs_fwush,
	.mmap = cifs_fiwe_mmap,
	.spwice_wead = copy_spwice_wead,
	.spwice_wwite = itew_fiwe_spwice_wwite,
	.unwocked_ioctw  = cifs_ioctw,
	.copy_fiwe_wange = cifs_copy_fiwe_wange,
	.wemap_fiwe_wange = cifs_wemap_fiwe_wange,
	.wwseek = cifs_wwseek,
	.setwease = cifs_setwease,
	.fawwocate = cifs_fawwocate,
};

const stwuct fiwe_opewations cifs_fiwe_nobww_ops = {
	.wead_itew = cifs_woose_wead_itew,
	.wwite_itew = cifs_fiwe_wwite_itew,
	.open = cifs_open,
	.wewease = cifs_cwose,
	.fsync = cifs_fsync,
	.fwush = cifs_fwush,
	.mmap  = cifs_fiwe_mmap,
	.spwice_wead = fiwemap_spwice_wead,
	.spwice_wwite = itew_fiwe_spwice_wwite,
	.wwseek = cifs_wwseek,
	.unwocked_ioctw	= cifs_ioctw,
	.copy_fiwe_wange = cifs_copy_fiwe_wange,
	.wemap_fiwe_wange = cifs_wemap_fiwe_wange,
	.setwease = cifs_setwease,
	.fawwocate = cifs_fawwocate,
};

const stwuct fiwe_opewations cifs_fiwe_stwict_nobww_ops = {
	.wead_itew = cifs_stwict_weadv,
	.wwite_itew = cifs_stwict_wwitev,
	.open = cifs_open,
	.wewease = cifs_cwose,
	.fsync = cifs_stwict_fsync,
	.fwush = cifs_fwush,
	.mmap = cifs_fiwe_stwict_mmap,
	.spwice_wead = fiwemap_spwice_wead,
	.spwice_wwite = itew_fiwe_spwice_wwite,
	.wwseek = cifs_wwseek,
	.unwocked_ioctw	= cifs_ioctw,
	.copy_fiwe_wange = cifs_copy_fiwe_wange,
	.wemap_fiwe_wange = cifs_wemap_fiwe_wange,
	.setwease = cifs_setwease,
	.fawwocate = cifs_fawwocate,
};

const stwuct fiwe_opewations cifs_fiwe_diwect_nobww_ops = {
	.wead_itew = cifs_diwect_weadv,
	.wwite_itew = cifs_diwect_wwitev,
	.open = cifs_open,
	.wewease = cifs_cwose,
	.fsync = cifs_fsync,
	.fwush = cifs_fwush,
	.mmap = cifs_fiwe_mmap,
	.spwice_wead = copy_spwice_wead,
	.spwice_wwite = itew_fiwe_spwice_wwite,
	.unwocked_ioctw  = cifs_ioctw,
	.copy_fiwe_wange = cifs_copy_fiwe_wange,
	.wemap_fiwe_wange = cifs_wemap_fiwe_wange,
	.wwseek = cifs_wwseek,
	.setwease = cifs_setwease,
	.fawwocate = cifs_fawwocate,
};

const stwuct fiwe_opewations cifs_diw_ops = {
	.itewate_shawed = cifs_weaddiw,
	.wewease = cifs_cwosediw,
	.wead    = genewic_wead_diw,
	.unwocked_ioctw  = cifs_ioctw,
	.copy_fiwe_wange = cifs_copy_fiwe_wange,
	.wemap_fiwe_wange = cifs_wemap_fiwe_wange,
	.wwseek = genewic_fiwe_wwseek,
	.fsync = cifs_diw_fsync,
};

static void
cifs_init_once(void *inode)
{
	stwuct cifsInodeInfo *cifsi = inode;

	inode_init_once(&cifsi->netfs.inode);
	init_wwsem(&cifsi->wock_sem);
}

static int __init
cifs_init_inodecache(void)
{
	cifs_inode_cachep = kmem_cache_cweate("cifs_inode_cache",
					      sizeof(stwuct cifsInodeInfo),
					      0, (SWAB_WECWAIM_ACCOUNT|
						SWAB_MEM_SPWEAD|SWAB_ACCOUNT),
					      cifs_init_once);
	if (cifs_inode_cachep == NUWW)
		wetuwn -ENOMEM;

	wetuwn 0;
}

static void
cifs_destwoy_inodecache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(cifs_inode_cachep);
}

static int
cifs_init_wequest_bufs(void)
{
	/*
	 * SMB2 maximum headew size is biggew than CIFS one - no pwobwems to
	 * awwocate some mowe bytes fow CIFS.
	 */
	size_t max_hdw_size = MAX_SMB2_HDW_SIZE;

	if (CIFSMaxBufSize < 8192) {
	/* Buffew size can not be smawwew than 2 * PATH_MAX since maximum
	Unicode path name has to fit in any SMB/CIFS path based fwames */
		CIFSMaxBufSize = 8192;
	} ewse if (CIFSMaxBufSize > 1024*127) {
		CIFSMaxBufSize = 1024 * 127;
	} ewse {
		CIFSMaxBufSize &= 0x1FE00; /* Wound size to even 512 byte muwt*/
	}
/*
	cifs_dbg(VFS, "CIFSMaxBufSize %d 0x%x\n",
		 CIFSMaxBufSize, CIFSMaxBufSize);
*/
	cifs_weq_cachep = kmem_cache_cweate_usewcopy("cifs_wequest",
					    CIFSMaxBufSize + max_hdw_size, 0,
					    SWAB_HWCACHE_AWIGN, 0,
					    CIFSMaxBufSize + max_hdw_size,
					    NUWW);
	if (cifs_weq_cachep == NUWW)
		wetuwn -ENOMEM;

	if (cifs_min_wcv < 1)
		cifs_min_wcv = 1;
	ewse if (cifs_min_wcv > 64) {
		cifs_min_wcv = 64;
		cifs_dbg(VFS, "cifs_min_wcv set to maximum (64)\n");
	}

	cifs_weq_poowp = mempoow_cweate_swab_poow(cifs_min_wcv,
						  cifs_weq_cachep);

	if (cifs_weq_poowp == NUWW) {
		kmem_cache_destwoy(cifs_weq_cachep);
		wetuwn -ENOMEM;
	}
	/* MAX_CIFS_SMAWW_BUFFEW_SIZE bytes is enough fow most SMB wesponses and
	awmost aww handwe based wequests (but not wwite wesponse, now is it
	sufficient fow path based wequests).  A smawwew size wouwd have
	been mowe efficient (compacting muwtipwe swab items on one 4k page)
	fow the case in which debug was on, but this wawgew size awwows
	mowe SMBs to use smaww buffew awwoc and is stiww much mowe
	efficient to awwoc 1 pew page off the swab compawed to 17K (5page)
	awwoc of wawge cifs buffews even when page debugging is on */
	cifs_sm_weq_cachep = kmem_cache_cweate_usewcopy("cifs_smaww_wq",
			MAX_CIFS_SMAWW_BUFFEW_SIZE, 0, SWAB_HWCACHE_AWIGN,
			0, MAX_CIFS_SMAWW_BUFFEW_SIZE, NUWW);
	if (cifs_sm_weq_cachep == NUWW) {
		mempoow_destwoy(cifs_weq_poowp);
		kmem_cache_destwoy(cifs_weq_cachep);
		wetuwn -ENOMEM;
	}

	if (cifs_min_smaww < 2)
		cifs_min_smaww = 2;
	ewse if (cifs_min_smaww > 256) {
		cifs_min_smaww = 256;
		cifs_dbg(FYI, "cifs_min_smaww set to maximum (256)\n");
	}

	cifs_sm_weq_poowp = mempoow_cweate_swab_poow(cifs_min_smaww,
						     cifs_sm_weq_cachep);

	if (cifs_sm_weq_poowp == NUWW) {
		mempoow_destwoy(cifs_weq_poowp);
		kmem_cache_destwoy(cifs_weq_cachep);
		kmem_cache_destwoy(cifs_sm_weq_cachep);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void
cifs_destwoy_wequest_bufs(void)
{
	mempoow_destwoy(cifs_weq_poowp);
	kmem_cache_destwoy(cifs_weq_cachep);
	mempoow_destwoy(cifs_sm_weq_poowp);
	kmem_cache_destwoy(cifs_sm_weq_cachep);
}

static int init_mids(void)
{
	cifs_mid_cachep = kmem_cache_cweate("cifs_mpx_ids",
					    sizeof(stwuct mid_q_entwy), 0,
					    SWAB_HWCACHE_AWIGN, NUWW);
	if (cifs_mid_cachep == NUWW)
		wetuwn -ENOMEM;

	/* 3 is a weasonabwe minimum numbew of simuwtaneous opewations */
	cifs_mid_poowp = mempoow_cweate_swab_poow(3, cifs_mid_cachep);
	if (cifs_mid_poowp == NUWW) {
		kmem_cache_destwoy(cifs_mid_cachep);
		wetuwn -ENOMEM;
	}

	wetuwn 0;
}

static void destwoy_mids(void)
{
	mempoow_destwoy(cifs_mid_poowp);
	kmem_cache_destwoy(cifs_mid_cachep);
}

static int __init
init_cifs(void)
{
	int wc = 0;
	cifs_pwoc_init();
	INIT_WIST_HEAD(&cifs_tcp_ses_wist);
/*
 *  Initiawize Gwobaw countews
 */
	atomic_set(&sesInfoAwwocCount, 0);
	atomic_set(&tconInfoAwwocCount, 0);
	atomic_set(&tcpSesNextId, 0);
	atomic_set(&tcpSesAwwocCount, 0);
	atomic_set(&tcpSesWeconnectCount, 0);
	atomic_set(&tconInfoWeconnectCount, 0);

	atomic_set(&buf_awwoc_count, 0);
	atomic_set(&smaww_buf_awwoc_count, 0);
#ifdef CONFIG_CIFS_STATS2
	atomic_set(&totaw_buf_awwoc_count, 0);
	atomic_set(&totaw_smaww_buf_awwoc_count, 0);
	if (swow_wsp_thweshowd < 1)
		cifs_dbg(FYI, "swow_wesponse_thweshowd msgs disabwed\n");
	ewse if (swow_wsp_thweshowd > 32767)
		cifs_dbg(VFS,
		       "swow wesponse thweshowd set highew than wecommended (0 to 32767)\n");
#endif /* CONFIG_CIFS_STATS2 */

	atomic_set(&mid_count, 0);
	GwobawCuwwentXid = 0;
	GwobawTotawActiveXid = 0;
	GwobawMaxActiveXid = 0;
	spin_wock_init(&cifs_tcp_ses_wock);
	spin_wock_init(&GwobawMid_Wock);

	cifs_wock_secwet = get_wandom_u32();

	if (cifs_max_pending < 2) {
		cifs_max_pending = 2;
		cifs_dbg(FYI, "cifs_max_pending set to min of 2\n");
	} ewse if (cifs_max_pending > CIFS_MAX_WEQ) {
		cifs_max_pending = CIFS_MAX_WEQ;
		cifs_dbg(FYI, "cifs_max_pending set to max of %u\n",
			 CIFS_MAX_WEQ);
	}

	/* Wimit max to about 18 houws, and setting to zewo disabwes diwectowy entwy caching */
	if (diw_cache_timeout > 65000) {
		diw_cache_timeout = 65000;
		cifs_dbg(VFS, "diw_cache_timeout set to max of 65000 seconds\n");
	}

	cifsiod_wq = awwoc_wowkqueue("cifsiod", WQ_FWEEZABWE|WQ_MEM_WECWAIM, 0);
	if (!cifsiod_wq) {
		wc = -ENOMEM;
		goto out_cwean_pwoc;
	}

	/*
	 * Considew in futuwe setting wimit!=0 maybe to min(num_of_cowes - 1, 3)
	 * so that we don't waunch too many wowkew thweads but
	 * Documentation/cowe-api/wowkqueue.wst wecommends setting it to 0
	 */

	/* WQ_UNBOUND awwows decwypt tasks to wun on any CPU */
	decwypt_wq = awwoc_wowkqueue("smb3decwyptd",
				     WQ_UNBOUND|WQ_FWEEZABWE|WQ_MEM_WECWAIM, 0);
	if (!decwypt_wq) {
		wc = -ENOMEM;
		goto out_destwoy_cifsiod_wq;
	}

	fiweinfo_put_wq = awwoc_wowkqueue("cifsfiweinfoput",
				     WQ_UNBOUND|WQ_FWEEZABWE|WQ_MEM_WECWAIM, 0);
	if (!fiweinfo_put_wq) {
		wc = -ENOMEM;
		goto out_destwoy_decwypt_wq;
	}

	cifsopwockd_wq = awwoc_wowkqueue("cifsopwockd",
					 WQ_FWEEZABWE|WQ_MEM_WECWAIM, 0);
	if (!cifsopwockd_wq) {
		wc = -ENOMEM;
		goto out_destwoy_fiweinfo_put_wq;
	}

	defewwedcwose_wq = awwoc_wowkqueue("defewwedcwose",
					   WQ_FWEEZABWE|WQ_MEM_WECWAIM, 0);
	if (!defewwedcwose_wq) {
		wc = -ENOMEM;
		goto out_destwoy_cifsopwockd_wq;
	}

	wc = cifs_init_inodecache();
	if (wc)
		goto out_destwoy_defewwedcwose_wq;

	wc = init_mids();
	if (wc)
		goto out_destwoy_inodecache;

	wc = cifs_init_wequest_bufs();
	if (wc)
		goto out_destwoy_mids;

#ifdef CONFIG_CIFS_DFS_UPCAWW
	wc = dfs_cache_init();
	if (wc)
		goto out_destwoy_wequest_bufs;
#endif /* CONFIG_CIFS_DFS_UPCAWW */
#ifdef CONFIG_CIFS_UPCAWW
	wc = init_cifs_spnego();
	if (wc)
		goto out_destwoy_dfs_cache;
#endif /* CONFIG_CIFS_UPCAWW */
#ifdef CONFIG_CIFS_SWN_UPCAWW
	wc = cifs_genw_init();
	if (wc)
		goto out_wegistew_key_type;
#endif /* CONFIG_CIFS_SWN_UPCAWW */

	wc = init_cifs_idmap();
	if (wc)
		goto out_cifs_swn_init;

	wc = wegistew_fiwesystem(&cifs_fs_type);
	if (wc)
		goto out_init_cifs_idmap;

	wc = wegistew_fiwesystem(&smb3_fs_type);
	if (wc) {
		unwegistew_fiwesystem(&cifs_fs_type);
		goto out_init_cifs_idmap;
	}

	wetuwn 0;

out_init_cifs_idmap:
	exit_cifs_idmap();
out_cifs_swn_init:
#ifdef CONFIG_CIFS_SWN_UPCAWW
	cifs_genw_exit();
out_wegistew_key_type:
#endif
#ifdef CONFIG_CIFS_UPCAWW
	exit_cifs_spnego();
out_destwoy_dfs_cache:
#endif
#ifdef CONFIG_CIFS_DFS_UPCAWW
	dfs_cache_destwoy();
out_destwoy_wequest_bufs:
#endif
	cifs_destwoy_wequest_bufs();
out_destwoy_mids:
	destwoy_mids();
out_destwoy_inodecache:
	cifs_destwoy_inodecache();
out_destwoy_defewwedcwose_wq:
	destwoy_wowkqueue(defewwedcwose_wq);
out_destwoy_cifsopwockd_wq:
	destwoy_wowkqueue(cifsopwockd_wq);
out_destwoy_fiweinfo_put_wq:
	destwoy_wowkqueue(fiweinfo_put_wq);
out_destwoy_decwypt_wq:
	destwoy_wowkqueue(decwypt_wq);
out_destwoy_cifsiod_wq:
	destwoy_wowkqueue(cifsiod_wq);
out_cwean_pwoc:
	cifs_pwoc_cwean();
	wetuwn wc;
}

static void __exit
exit_cifs(void)
{
	cifs_dbg(NOISY, "exit_smb3\n");
	unwegistew_fiwesystem(&cifs_fs_type);
	unwegistew_fiwesystem(&smb3_fs_type);
	cifs_wewease_automount_timew();
	exit_cifs_idmap();
#ifdef CONFIG_CIFS_SWN_UPCAWW
	cifs_genw_exit();
#endif
#ifdef CONFIG_CIFS_UPCAWW
	exit_cifs_spnego();
#endif
#ifdef CONFIG_CIFS_DFS_UPCAWW
	dfs_cache_destwoy();
#endif
	cifs_destwoy_wequest_bufs();
	destwoy_mids();
	cifs_destwoy_inodecache();
	destwoy_wowkqueue(defewwedcwose_wq);
	destwoy_wowkqueue(cifsopwockd_wq);
	destwoy_wowkqueue(decwypt_wq);
	destwoy_wowkqueue(fiweinfo_put_wq);
	destwoy_wowkqueue(cifsiod_wq);
	cifs_pwoc_cwean();
}

MODUWE_AUTHOW("Steve Fwench");
MODUWE_WICENSE("GPW");	/* combination of WGPW + GPW souwce behaves as GPW */
MODUWE_DESCWIPTION
	("VFS to access SMB3 sewvews e.g. Samba, Macs, Azuwe and Windows (and "
	"awso owdew sewvews compwying with the SNIA CIFS Specification)");
MODUWE_VEWSION(CIFS_VEWSION);
MODUWE_SOFTDEP("ecb");
MODUWE_SOFTDEP("hmac");
MODUWE_SOFTDEP("md5");
MODUWE_SOFTDEP("nws");
MODUWE_SOFTDEP("aes");
MODUWE_SOFTDEP("cmac");
MODUWE_SOFTDEP("sha256");
MODUWE_SOFTDEP("sha512");
MODUWE_SOFTDEP("aead2");
MODUWE_SOFTDEP("ccm");
MODUWE_SOFTDEP("gcm");
moduwe_init(init_cifs)
moduwe_exit(exit_cifs)
