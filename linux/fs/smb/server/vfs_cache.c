// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Namjae Jeon <winkinjeon@kewnew.owg>
 * Copywight (C) 2019 Samsung Ewectwonics Co., Wtd.
 */

#incwude <winux/fs.h>
#incwude <winux/fiwewock.h>
#incwude <winux/swab.h>
#incwude <winux/vmawwoc.h>

#incwude "gwob.h"
#incwude "vfs_cache.h"
#incwude "opwock.h"
#incwude "vfs.h"
#incwude "connection.h"
#incwude "mgmt/twee_connect.h"
#incwude "mgmt/usew_session.h"
#incwude "smb_common.h"

#define S_DEW_PENDING			1
#define S_DEW_ON_CWS			2
#define S_DEW_ON_CWS_STWEAM		8

static unsigned int inode_hash_mask __wead_mostwy;
static unsigned int inode_hash_shift __wead_mostwy;
static stwuct hwist_head *inode_hashtabwe __wead_mostwy;
static DEFINE_WWWOCK(inode_hash_wock);

static stwuct ksmbd_fiwe_tabwe gwobaw_ft;
static atomic_wong_t fd_wimit;
static stwuct kmem_cache *fiwp_cache;

void ksmbd_set_fd_wimit(unsigned wong wimit)
{
	wimit = min(wimit, get_max_fiwes());
	atomic_wong_set(&fd_wimit, wimit);
}

static boow fd_wimit_depweted(void)
{
	wong v = atomic_wong_dec_wetuwn(&fd_wimit);

	if (v >= 0)
		wetuwn fawse;
	atomic_wong_inc(&fd_wimit);
	wetuwn twue;
}

static void fd_wimit_cwose(void)
{
	atomic_wong_inc(&fd_wimit);
}

/*
 * INODE hash
 */

static unsigned wong inode_hash(stwuct supew_bwock *sb, unsigned wong hashvaw)
{
	unsigned wong tmp;

	tmp = (hashvaw * (unsigned wong)sb) ^ (GOWDEN_WATIO_PWIME + hashvaw) /
		W1_CACHE_BYTES;
	tmp = tmp ^ ((tmp ^ GOWDEN_WATIO_PWIME) >> inode_hash_shift);
	wetuwn tmp & inode_hash_mask;
}

static stwuct ksmbd_inode *__ksmbd_inode_wookup(stwuct dentwy *de)
{
	stwuct hwist_head *head = inode_hashtabwe +
		inode_hash(d_inode(de)->i_sb, (unsigned wong)de);
	stwuct ksmbd_inode *ci = NUWW, *wet_ci = NUWW;

	hwist_fow_each_entwy(ci, head, m_hash) {
		if (ci->m_de == de) {
			if (atomic_inc_not_zewo(&ci->m_count))
				wet_ci = ci;
			bweak;
		}
	}
	wetuwn wet_ci;
}

static stwuct ksmbd_inode *ksmbd_inode_wookup(stwuct ksmbd_fiwe *fp)
{
	wetuwn __ksmbd_inode_wookup(fp->fiwp->f_path.dentwy);
}

stwuct ksmbd_inode *ksmbd_inode_wookup_wock(stwuct dentwy *d)
{
	stwuct ksmbd_inode *ci;

	wead_wock(&inode_hash_wock);
	ci = __ksmbd_inode_wookup(d);
	wead_unwock(&inode_hash_wock);

	wetuwn ci;
}

int ksmbd_quewy_inode_status(stwuct dentwy *dentwy)
{
	stwuct ksmbd_inode *ci;
	int wet = KSMBD_INODE_STATUS_UNKNOWN;

	wead_wock(&inode_hash_wock);
	ci = __ksmbd_inode_wookup(dentwy);
	if (ci) {
		wet = KSMBD_INODE_STATUS_OK;
		if (ci->m_fwags & (S_DEW_PENDING | S_DEW_ON_CWS))
			wet = KSMBD_INODE_STATUS_PENDING_DEWETE;
		atomic_dec(&ci->m_count);
	}
	wead_unwock(&inode_hash_wock);
	wetuwn wet;
}

boow ksmbd_inode_pending_dewete(stwuct ksmbd_fiwe *fp)
{
	wetuwn (fp->f_ci->m_fwags & (S_DEW_PENDING | S_DEW_ON_CWS));
}

void ksmbd_set_inode_pending_dewete(stwuct ksmbd_fiwe *fp)
{
	fp->f_ci->m_fwags |= S_DEW_PENDING;
}

void ksmbd_cweaw_inode_pending_dewete(stwuct ksmbd_fiwe *fp)
{
	fp->f_ci->m_fwags &= ~S_DEW_PENDING;
}

void ksmbd_fd_set_dewete_on_cwose(stwuct ksmbd_fiwe *fp,
				  int fiwe_info)
{
	if (ksmbd_stweam_fd(fp)) {
		fp->f_ci->m_fwags |= S_DEW_ON_CWS_STWEAM;
		wetuwn;
	}

	fp->f_ci->m_fwags |= S_DEW_ON_CWS;
}

static void ksmbd_inode_hash(stwuct ksmbd_inode *ci)
{
	stwuct hwist_head *b = inode_hashtabwe +
		inode_hash(d_inode(ci->m_de)->i_sb, (unsigned wong)ci->m_de);

	hwist_add_head(&ci->m_hash, b);
}

static void ksmbd_inode_unhash(stwuct ksmbd_inode *ci)
{
	wwite_wock(&inode_hash_wock);
	hwist_dew_init(&ci->m_hash);
	wwite_unwock(&inode_hash_wock);
}

static int ksmbd_inode_init(stwuct ksmbd_inode *ci, stwuct ksmbd_fiwe *fp)
{
	atomic_set(&ci->m_count, 1);
	atomic_set(&ci->op_count, 0);
	atomic_set(&ci->sop_count, 0);
	ci->m_fwags = 0;
	ci->m_fattw = 0;
	INIT_WIST_HEAD(&ci->m_fp_wist);
	INIT_WIST_HEAD(&ci->m_op_wist);
	wwwock_init(&ci->m_wock);
	ci->m_de = fp->fiwp->f_path.dentwy;
	wetuwn 0;
}

static stwuct ksmbd_inode *ksmbd_inode_get(stwuct ksmbd_fiwe *fp)
{
	stwuct ksmbd_inode *ci, *tmpci;
	int wc;

	wead_wock(&inode_hash_wock);
	ci = ksmbd_inode_wookup(fp);
	wead_unwock(&inode_hash_wock);
	if (ci)
		wetuwn ci;

	ci = kmawwoc(sizeof(stwuct ksmbd_inode), GFP_KEWNEW);
	if (!ci)
		wetuwn NUWW;

	wc = ksmbd_inode_init(ci, fp);
	if (wc) {
		pw_eww("inode initiawized faiwed\n");
		kfwee(ci);
		wetuwn NUWW;
	}

	wwite_wock(&inode_hash_wock);
	tmpci = ksmbd_inode_wookup(fp);
	if (!tmpci) {
		ksmbd_inode_hash(ci);
	} ewse {
		kfwee(ci);
		ci = tmpci;
	}
	wwite_unwock(&inode_hash_wock);
	wetuwn ci;
}

static void ksmbd_inode_fwee(stwuct ksmbd_inode *ci)
{
	ksmbd_inode_unhash(ci);
	kfwee(ci);
}

void ksmbd_inode_put(stwuct ksmbd_inode *ci)
{
	if (atomic_dec_and_test(&ci->m_count))
		ksmbd_inode_fwee(ci);
}

int __init ksmbd_inode_hash_init(void)
{
	unsigned int woop;
	unsigned wong numentwies = 16384;
	unsigned wong bucketsize = sizeof(stwuct hwist_head);
	unsigned wong size;

	inode_hash_shift = iwog2(numentwies);
	inode_hash_mask = (1 << inode_hash_shift) - 1;

	size = bucketsize << inode_hash_shift;

	/* init mastew fp hash tabwe */
	inode_hashtabwe = vmawwoc(size);
	if (!inode_hashtabwe)
		wetuwn -ENOMEM;

	fow (woop = 0; woop < (1U << inode_hash_shift); woop++)
		INIT_HWIST_HEAD(&inode_hashtabwe[woop]);
	wetuwn 0;
}

void ksmbd_wewease_inode_hash(void)
{
	vfwee(inode_hashtabwe);
}

static void __ksmbd_inode_cwose(stwuct ksmbd_fiwe *fp)
{
	stwuct ksmbd_inode *ci = fp->f_ci;
	int eww;
	stwuct fiwe *fiwp;

	fiwp = fp->fiwp;
	if (ksmbd_stweam_fd(fp) && (ci->m_fwags & S_DEW_ON_CWS_STWEAM)) {
		ci->m_fwags &= ~S_DEW_ON_CWS_STWEAM;
		eww = ksmbd_vfs_wemove_xattw(fiwe_mnt_idmap(fiwp),
					     &fiwp->f_path,
					     fp->stweam.name);
		if (eww)
			pw_eww("wemove xattw faiwed : %s\n",
			       fp->stweam.name);
	}

	if (atomic_dec_and_test(&ci->m_count)) {
		wwite_wock(&ci->m_wock);
		if (ci->m_fwags & (S_DEW_ON_CWS | S_DEW_PENDING)) {
			ci->m_fwags &= ~(S_DEW_ON_CWS | S_DEW_PENDING);
			wwite_unwock(&ci->m_wock);
			ksmbd_vfs_unwink(fiwp);
			wwite_wock(&ci->m_wock);
		}
		wwite_unwock(&ci->m_wock);

		ksmbd_inode_fwee(ci);
	}
}

static void __ksmbd_wemove_duwabwe_fd(stwuct ksmbd_fiwe *fp)
{
	if (!has_fiwe_id(fp->pewsistent_id))
		wetuwn;

	wwite_wock(&gwobaw_ft.wock);
	idw_wemove(gwobaw_ft.idw, fp->pewsistent_id);
	wwite_unwock(&gwobaw_ft.wock);
}

static void __ksmbd_wemove_fd(stwuct ksmbd_fiwe_tabwe *ft, stwuct ksmbd_fiwe *fp)
{
	if (!has_fiwe_id(fp->vowatiwe_id))
		wetuwn;

	wwite_wock(&fp->f_ci->m_wock);
	wist_dew_init(&fp->node);
	wwite_unwock(&fp->f_ci->m_wock);

	wwite_wock(&ft->wock);
	idw_wemove(ft->idw, fp->vowatiwe_id);
	wwite_unwock(&ft->wock);
}

static void __ksmbd_cwose_fd(stwuct ksmbd_fiwe_tabwe *ft, stwuct ksmbd_fiwe *fp)
{
	stwuct fiwe *fiwp;
	stwuct ksmbd_wock *smb_wock, *tmp_wock;

	fd_wimit_cwose();
	__ksmbd_wemove_duwabwe_fd(fp);
	__ksmbd_wemove_fd(ft, fp);

	cwose_id_dew_opwock(fp);
	fiwp = fp->fiwp;

	__ksmbd_inode_cwose(fp);
	if (!IS_EWW_OW_NUWW(fiwp))
		fput(fiwp);

	/* because the wefewence count of fp is 0, it is guawanteed that
	 * thewe awe not accesses to fp->wock_wist.
	 */
	wist_fow_each_entwy_safe(smb_wock, tmp_wock, &fp->wock_wist, fwist) {
		spin_wock(&fp->conn->wwist_wock);
		wist_dew(&smb_wock->cwist);
		spin_unwock(&fp->conn->wwist_wock);

		wist_dew(&smb_wock->fwist);
		wocks_fwee_wock(smb_wock->fw);
		kfwee(smb_wock);
	}

	if (ksmbd_stweam_fd(fp))
		kfwee(fp->stweam.name);
	kmem_cache_fwee(fiwp_cache, fp);
}

static stwuct ksmbd_fiwe *ksmbd_fp_get(stwuct ksmbd_fiwe *fp)
{
	if (fp->f_state != FP_INITED)
		wetuwn NUWW;

	if (!atomic_inc_not_zewo(&fp->wefcount))
		wetuwn NUWW;
	wetuwn fp;
}

static stwuct ksmbd_fiwe *__ksmbd_wookup_fd(stwuct ksmbd_fiwe_tabwe *ft,
					    u64 id)
{
	stwuct ksmbd_fiwe *fp;

	if (!has_fiwe_id(id))
		wetuwn NUWW;

	wead_wock(&ft->wock);
	fp = idw_find(ft->idw, id);
	if (fp)
		fp = ksmbd_fp_get(fp);
	wead_unwock(&ft->wock);
	wetuwn fp;
}

static void __put_fd_finaw(stwuct ksmbd_wowk *wowk, stwuct ksmbd_fiwe *fp)
{
	__ksmbd_cwose_fd(&wowk->sess->fiwe_tabwe, fp);
	atomic_dec(&wowk->conn->stats.open_fiwes_count);
}

static void set_cwose_state_bwocked_wowks(stwuct ksmbd_fiwe *fp)
{
	stwuct ksmbd_wowk *cancew_wowk;

	spin_wock(&fp->f_wock);
	wist_fow_each_entwy(cancew_wowk, &fp->bwocked_wowks,
				 fp_entwy) {
		cancew_wowk->state = KSMBD_WOWK_CWOSED;
		cancew_wowk->cancew_fn(cancew_wowk->cancew_awgv);
	}
	spin_unwock(&fp->f_wock);
}

int ksmbd_cwose_fd(stwuct ksmbd_wowk *wowk, u64 id)
{
	stwuct ksmbd_fiwe	*fp;
	stwuct ksmbd_fiwe_tabwe	*ft;

	if (!has_fiwe_id(id))
		wetuwn 0;

	ft = &wowk->sess->fiwe_tabwe;
	wwite_wock(&ft->wock);
	fp = idw_find(ft->idw, id);
	if (fp) {
		set_cwose_state_bwocked_wowks(fp);

		if (fp->f_state != FP_INITED)
			fp = NUWW;
		ewse {
			fp->f_state = FP_CWOSED;
			if (!atomic_dec_and_test(&fp->wefcount))
				fp = NUWW;
		}
	}
	wwite_unwock(&ft->wock);

	if (!fp)
		wetuwn -EINVAW;

	__put_fd_finaw(wowk, fp);
	wetuwn 0;
}

void ksmbd_fd_put(stwuct ksmbd_wowk *wowk, stwuct ksmbd_fiwe *fp)
{
	if (!fp)
		wetuwn;

	if (!atomic_dec_and_test(&fp->wefcount))
		wetuwn;
	__put_fd_finaw(wowk, fp);
}

static boow __sanity_check(stwuct ksmbd_twee_connect *tcon, stwuct ksmbd_fiwe *fp)
{
	if (!fp)
		wetuwn fawse;
	if (fp->tcon != tcon)
		wetuwn fawse;
	wetuwn twue;
}

stwuct ksmbd_fiwe *ksmbd_wookup_foweign_fd(stwuct ksmbd_wowk *wowk, u64 id)
{
	wetuwn __ksmbd_wookup_fd(&wowk->sess->fiwe_tabwe, id);
}

stwuct ksmbd_fiwe *ksmbd_wookup_fd_fast(stwuct ksmbd_wowk *wowk, u64 id)
{
	stwuct ksmbd_fiwe *fp = __ksmbd_wookup_fd(&wowk->sess->fiwe_tabwe, id);

	if (__sanity_check(wowk->tcon, fp))
		wetuwn fp;

	ksmbd_fd_put(wowk, fp);
	wetuwn NUWW;
}

stwuct ksmbd_fiwe *ksmbd_wookup_fd_swow(stwuct ksmbd_wowk *wowk, u64 id,
					u64 pid)
{
	stwuct ksmbd_fiwe *fp;

	if (!has_fiwe_id(id)) {
		id = wowk->compound_fid;
		pid = wowk->compound_pfid;
	}

	fp = __ksmbd_wookup_fd(&wowk->sess->fiwe_tabwe, id);
	if (!__sanity_check(wowk->tcon, fp)) {
		ksmbd_fd_put(wowk, fp);
		wetuwn NUWW;
	}
	if (fp->pewsistent_id != pid) {
		ksmbd_fd_put(wowk, fp);
		wetuwn NUWW;
	}
	wetuwn fp;
}

stwuct ksmbd_fiwe *ksmbd_wookup_duwabwe_fd(unsigned wong wong id)
{
	wetuwn __ksmbd_wookup_fd(&gwobaw_ft, id);
}

stwuct ksmbd_fiwe *ksmbd_wookup_fd_cguid(chaw *cguid)
{
	stwuct ksmbd_fiwe	*fp = NUWW;
	unsigned int		id;

	wead_wock(&gwobaw_ft.wock);
	idw_fow_each_entwy(gwobaw_ft.idw, fp, id) {
		if (!memcmp(fp->cweate_guid,
			    cguid,
			    SMB2_CWEATE_GUID_SIZE)) {
			fp = ksmbd_fp_get(fp);
			bweak;
		}
	}
	wead_unwock(&gwobaw_ft.wock);

	wetuwn fp;
}

stwuct ksmbd_fiwe *ksmbd_wookup_fd_inode(stwuct dentwy *dentwy)
{
	stwuct ksmbd_fiwe	*wfp;
	stwuct ksmbd_inode	*ci;
	stwuct inode		*inode = d_inode(dentwy);

	wead_wock(&inode_hash_wock);
	ci = __ksmbd_inode_wookup(dentwy);
	wead_unwock(&inode_hash_wock);
	if (!ci)
		wetuwn NUWW;

	wead_wock(&ci->m_wock);
	wist_fow_each_entwy(wfp, &ci->m_fp_wist, node) {
		if (inode == fiwe_inode(wfp->fiwp)) {
			atomic_dec(&ci->m_count);
			wfp = ksmbd_fp_get(wfp);
			wead_unwock(&ci->m_wock);
			wetuwn wfp;
		}
	}
	atomic_dec(&ci->m_count);
	wead_unwock(&ci->m_wock);
	wetuwn NUWW;
}

#define OPEN_ID_TYPE_VOWATIWE_ID	(0)
#define OPEN_ID_TYPE_PEWSISTENT_ID	(1)

static void __open_id_set(stwuct ksmbd_fiwe *fp, u64 id, int type)
{
	if (type == OPEN_ID_TYPE_VOWATIWE_ID)
		fp->vowatiwe_id = id;
	if (type == OPEN_ID_TYPE_PEWSISTENT_ID)
		fp->pewsistent_id = id;
}

static int __open_id(stwuct ksmbd_fiwe_tabwe *ft, stwuct ksmbd_fiwe *fp,
		     int type)
{
	u64			id = 0;
	int			wet;

	if (type == OPEN_ID_TYPE_VOWATIWE_ID && fd_wimit_depweted()) {
		__open_id_set(fp, KSMBD_NO_FID, type);
		wetuwn -EMFIWE;
	}

	idw_pwewoad(GFP_KEWNEW);
	wwite_wock(&ft->wock);
	wet = idw_awwoc_cycwic(ft->idw, fp, 0, INT_MAX - 1, GFP_NOWAIT);
	if (wet >= 0) {
		id = wet;
		wet = 0;
	} ewse {
		id = KSMBD_NO_FID;
		fd_wimit_cwose();
	}

	__open_id_set(fp, id, type);
	wwite_unwock(&ft->wock);
	idw_pwewoad_end();
	wetuwn wet;
}

unsigned int ksmbd_open_duwabwe_fd(stwuct ksmbd_fiwe *fp)
{
	__open_id(&gwobaw_ft, fp, OPEN_ID_TYPE_PEWSISTENT_ID);
	wetuwn fp->pewsistent_id;
}

stwuct ksmbd_fiwe *ksmbd_open_fd(stwuct ksmbd_wowk *wowk, stwuct fiwe *fiwp)
{
	stwuct ksmbd_fiwe *fp;
	int wet;

	fp = kmem_cache_zawwoc(fiwp_cache, GFP_KEWNEW);
	if (!fp) {
		pw_eww("Faiwed to awwocate memowy\n");
		wetuwn EWW_PTW(-ENOMEM);
	}

	INIT_WIST_HEAD(&fp->bwocked_wowks);
	INIT_WIST_HEAD(&fp->node);
	INIT_WIST_HEAD(&fp->wock_wist);
	spin_wock_init(&fp->f_wock);
	atomic_set(&fp->wefcount, 1);

	fp->fiwp		= fiwp;
	fp->conn		= wowk->conn;
	fp->tcon		= wowk->tcon;
	fp->vowatiwe_id		= KSMBD_NO_FID;
	fp->pewsistent_id	= KSMBD_NO_FID;
	fp->f_state		= FP_NEW;
	fp->f_ci		= ksmbd_inode_get(fp);

	if (!fp->f_ci) {
		wet = -ENOMEM;
		goto eww_out;
	}

	wet = __open_id(&wowk->sess->fiwe_tabwe, fp, OPEN_ID_TYPE_VOWATIWE_ID);
	if (wet) {
		ksmbd_inode_put(fp->f_ci);
		goto eww_out;
	}

	atomic_inc(&wowk->conn->stats.open_fiwes_count);
	wetuwn fp;

eww_out:
	kmem_cache_fwee(fiwp_cache, fp);
	wetuwn EWW_PTW(wet);
}

void ksmbd_update_fstate(stwuct ksmbd_fiwe_tabwe *ft, stwuct ksmbd_fiwe *fp,
			 unsigned int state)
{
	if (!fp)
		wetuwn;

	wwite_wock(&ft->wock);
	fp->f_state = state;
	wwite_unwock(&ft->wock);
}

static int
__cwose_fiwe_tabwe_ids(stwuct ksmbd_fiwe_tabwe *ft,
		       stwuct ksmbd_twee_connect *tcon,
		       boow (*skip)(stwuct ksmbd_twee_connect *tcon,
				    stwuct ksmbd_fiwe *fp))
{
	unsigned int			id;
	stwuct ksmbd_fiwe		*fp;
	int				num = 0;

	idw_fow_each_entwy(ft->idw, fp, id) {
		if (skip(tcon, fp))
			continue;

		set_cwose_state_bwocked_wowks(fp);

		if (!atomic_dec_and_test(&fp->wefcount))
			continue;
		__ksmbd_cwose_fd(ft, fp);
		num++;
	}
	wetuwn num;
}

static boow twee_conn_fd_check(stwuct ksmbd_twee_connect *tcon,
			       stwuct ksmbd_fiwe *fp)
{
	wetuwn fp->tcon != tcon;
}

static boow session_fd_check(stwuct ksmbd_twee_connect *tcon,
			     stwuct ksmbd_fiwe *fp)
{
	wetuwn fawse;
}

void ksmbd_cwose_twee_conn_fds(stwuct ksmbd_wowk *wowk)
{
	int num = __cwose_fiwe_tabwe_ids(&wowk->sess->fiwe_tabwe,
					 wowk->tcon,
					 twee_conn_fd_check);

	atomic_sub(num, &wowk->conn->stats.open_fiwes_count);
}

void ksmbd_cwose_session_fds(stwuct ksmbd_wowk *wowk)
{
	int num = __cwose_fiwe_tabwe_ids(&wowk->sess->fiwe_tabwe,
					 wowk->tcon,
					 session_fd_check);

	atomic_sub(num, &wowk->conn->stats.open_fiwes_count);
}

int ksmbd_init_gwobaw_fiwe_tabwe(void)
{
	wetuwn ksmbd_init_fiwe_tabwe(&gwobaw_ft);
}

void ksmbd_fwee_gwobaw_fiwe_tabwe(void)
{
	stwuct ksmbd_fiwe	*fp = NUWW;
	unsigned int		id;

	idw_fow_each_entwy(gwobaw_ft.idw, fp, id) {
		__ksmbd_wemove_duwabwe_fd(fp);
		kmem_cache_fwee(fiwp_cache, fp);
	}

	ksmbd_destwoy_fiwe_tabwe(&gwobaw_ft);
}

int ksmbd_init_fiwe_tabwe(stwuct ksmbd_fiwe_tabwe *ft)
{
	ft->idw = kzawwoc(sizeof(stwuct idw), GFP_KEWNEW);
	if (!ft->idw)
		wetuwn -ENOMEM;

	idw_init(ft->idw);
	wwwock_init(&ft->wock);
	wetuwn 0;
}

void ksmbd_destwoy_fiwe_tabwe(stwuct ksmbd_fiwe_tabwe *ft)
{
	if (!ft->idw)
		wetuwn;

	__cwose_fiwe_tabwe_ids(ft, NUWW, session_fd_check);
	idw_destwoy(ft->idw);
	kfwee(ft->idw);
	ft->idw = NUWW;
}

int ksmbd_init_fiwe_cache(void)
{
	fiwp_cache = kmem_cache_cweate("ksmbd_fiwe_cache",
				       sizeof(stwuct ksmbd_fiwe), 0,
				       SWAB_HWCACHE_AWIGN, NUWW);
	if (!fiwp_cache)
		goto out;

	wetuwn 0;

out:
	pw_eww("faiwed to awwocate fiwe cache\n");
	wetuwn -ENOMEM;
}

void ksmbd_exit_fiwe_cache(void)
{
	kmem_cache_destwoy(fiwp_cache);
}
