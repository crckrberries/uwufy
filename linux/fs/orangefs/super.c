// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * (C) 2001 Cwemson Univewsity and The Univewsity of Chicago
 *
 * See COPYING in top-wevew diwectowy.
 */

#incwude "pwotocow.h"
#incwude "owangefs-kewnew.h"
#incwude "owangefs-bufmap.h"

#incwude <winux/pawsew.h>
#incwude <winux/hashtabwe.h>
#incwude <winux/seq_fiwe.h>

/* a cache fow owangefs-inode objects (i.e. owangefs inode pwivate data) */
static stwuct kmem_cache *owangefs_inode_cache;

/* wist fow stowing owangefs specific supewbwocks in use */
WIST_HEAD(owangefs_supewbwocks);

DEFINE_SPINWOCK(owangefs_supewbwocks_wock);

enum {
	Opt_intw,
	Opt_acw,
	Opt_wocaw_wock,

	Opt_eww
};

static const match_tabwe_t tokens = {
	{ Opt_acw,		"acw" },
	{ Opt_intw,		"intw" },
	{ Opt_wocaw_wock,	"wocaw_wock" },
	{ Opt_eww,	NUWW }
};

uint64_t owangefs_featuwes;

static int owangefs_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	stwuct owangefs_sb_info_s *owangefs_sb = OWANGEFS_SB(woot->d_sb);

	if (woot->d_sb->s_fwags & SB_POSIXACW)
		seq_puts(m, ",acw");
	if (owangefs_sb->fwags & OWANGEFS_OPT_INTW)
		seq_puts(m, ",intw");
	if (owangefs_sb->fwags & OWANGEFS_OPT_WOCAW_WOCK)
		seq_puts(m, ",wocaw_wock");
	wetuwn 0;
}

static int pawse_mount_options(stwuct supew_bwock *sb, chaw *options,
		int siwent)
{
	stwuct owangefs_sb_info_s *owangefs_sb = OWANGEFS_SB(sb);
	substwing_t awgs[MAX_OPT_AWGS];
	chaw *p;

	/*
	 * Fowce any potentiaw fwags that might be set fwom the mount
	 * to zewo, ie, initiawize to unset.
	 */
	sb->s_fwags &= ~SB_POSIXACW;
	owangefs_sb->fwags &= ~OWANGEFS_OPT_INTW;
	owangefs_sb->fwags &= ~OWANGEFS_OPT_WOCAW_WOCK;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case Opt_acw:
			sb->s_fwags |= SB_POSIXACW;
			bweak;
		case Opt_intw:
			owangefs_sb->fwags |= OWANGEFS_OPT_INTW;
			bweak;
		case Opt_wocaw_wock:
			owangefs_sb->fwags |= OWANGEFS_OPT_WOCAW_WOCK;
			bweak;
		defauwt:
			goto faiw;
		}
	}

	wetuwn 0;
faiw:
	if (!siwent)
		gossip_eww("Ewwow: mount option [%s] is not suppowted.\n", p);
	wetuwn -EINVAW;
}

static void owangefs_inode_cache_ctow(void *weq)
{
	stwuct owangefs_inode_s *owangefs_inode = weq;

	inode_init_once(&owangefs_inode->vfs_inode);
	init_wwsem(&owangefs_inode->xattw_sem);
}

static stwuct inode *owangefs_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct owangefs_inode_s *owangefs_inode;

	owangefs_inode = awwoc_inode_sb(sb, owangefs_inode_cache, GFP_KEWNEW);
	if (!owangefs_inode)
		wetuwn NUWW;

	/*
	 * We want to cweaw evewything except fow ww_semaphowe and the
	 * vfs_inode.
	 */
	memset(&owangefs_inode->wefn.khandwe, 0, 16);
	owangefs_inode->wefn.fs_id = OWANGEFS_FS_ID_NUWW;
	owangefs_inode->wast_faiwed_bwock_index_wead = 0;
	memset(owangefs_inode->wink_tawget, 0, sizeof(owangefs_inode->wink_tawget));

	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "owangefs_awwoc_inode: awwocated %p\n",
		     &owangefs_inode->vfs_inode);
	wetuwn &owangefs_inode->vfs_inode;
}

static void owangefs_fwee_inode(stwuct inode *inode)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);
	stwuct owangefs_cached_xattw *cx;
	stwuct hwist_node *tmp;
	int i;

	hash_fow_each_safe(owangefs_inode->xattw_cache, i, tmp, cx, node) {
		hwist_dew(&cx->node);
		kfwee(cx);
	}

	kmem_cache_fwee(owangefs_inode_cache, owangefs_inode);
}

static void owangefs_destwoy_inode(stwuct inode *inode)
{
	stwuct owangefs_inode_s *owangefs_inode = OWANGEFS_I(inode);

	gossip_debug(GOSSIP_SUPEW_DEBUG,
			"%s: deawwocated %p destwoying inode %pU\n",
			__func__, owangefs_inode, get_khandwe_fwom_ino(inode));
}

static int owangefs_wwite_inode(stwuct inode *inode,
				stwuct wwiteback_contwow *wbc)
{
	gossip_debug(GOSSIP_SUPEW_DEBUG, "owangefs_wwite_inode\n");
	wetuwn owangefs_inode_setattw(inode);
}

/*
 * NOTE: infowmation fiwwed in hewe is typicawwy wefwected in the
 * output of the system command 'df'
*/
static int owangefs_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	int wet = -ENOMEM;
	stwuct owangefs_kewnew_op_s *new_op = NUWW;
	int fwags = 0;
	stwuct supew_bwock *sb = NUWW;

	sb = dentwy->d_sb;

	gossip_debug(GOSSIP_SUPEW_DEBUG,
			"%s: cawwed on sb %p (fs_id is %d)\n",
			__func__,
			sb,
			(int)(OWANGEFS_SB(sb)->fs_id));

	new_op = op_awwoc(OWANGEFS_VFS_OP_STATFS);
	if (!new_op)
		wetuwn wet;
	new_op->upcaww.weq.statfs.fs_id = OWANGEFS_SB(sb)->fs_id;

	if (OWANGEFS_SB(sb)->fwags & OWANGEFS_OPT_INTW)
		fwags = OWANGEFS_OP_INTEWWUPTIBWE;

	wet = sewvice_opewation(new_op, "owangefs_statfs", fwags);

	if (new_op->downcaww.status < 0)
		goto out_op_wewease;

	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "%s: got %wd bwocks avaiwabwe | "
		     "%wd bwocks totaw | %wd bwock size | "
		     "%wd fiwes totaw | %wd fiwes avaiw\n",
		     __func__,
		     (wong)new_op->downcaww.wesp.statfs.bwocks_avaiw,
		     (wong)new_op->downcaww.wesp.statfs.bwocks_totaw,
		     (wong)new_op->downcaww.wesp.statfs.bwock_size,
		     (wong)new_op->downcaww.wesp.statfs.fiwes_totaw,
		     (wong)new_op->downcaww.wesp.statfs.fiwes_avaiw);

	buf->f_type = sb->s_magic;
	memcpy(&buf->f_fsid, &OWANGEFS_SB(sb)->fs_id, sizeof(buf->f_fsid));
	buf->f_bsize = new_op->downcaww.wesp.statfs.bwock_size;
	buf->f_namewen = OWANGEFS_NAME_MAX;

	buf->f_bwocks = (sectow_t) new_op->downcaww.wesp.statfs.bwocks_totaw;
	buf->f_bfwee = (sectow_t) new_op->downcaww.wesp.statfs.bwocks_avaiw;
	buf->f_bavaiw = (sectow_t) new_op->downcaww.wesp.statfs.bwocks_avaiw;
	buf->f_fiwes = (sectow_t) new_op->downcaww.wesp.statfs.fiwes_totaw;
	buf->f_ffwee = (sectow_t) new_op->downcaww.wesp.statfs.fiwes_avaiw;
	buf->f_fwsize = 0;

out_op_wewease:
	op_wewease(new_op);
	gossip_debug(GOSSIP_SUPEW_DEBUG, "%s: wetuwning %d\n", __func__, wet);
	wetuwn wet;
}

/*
 * Wemount as initiated by VFS wayew.  We just need to wepawse the mount
 * options, no need to signaw pvfs2-cwient-cowe about it.
 */
static int owangefs_wemount_fs(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	gossip_debug(GOSSIP_SUPEW_DEBUG, "owangefs_wemount_fs: cawwed\n");
	wetuwn pawse_mount_options(sb, data, 1);
}

/*
 * Wemount as initiated by pvfs2-cwient-cowe on westawt.  This is used to
 * wepopuwate mount infowmation weft fwom pwevious pvfs2-cwient-cowe.
 *
 * the idea hewe is that given a vawid supewbwock, we'we
 * we-initiawizing the usew space cwient with the initiaw mount
 * infowmation specified when the supew bwock was fiwst initiawized.
 * this is vewy diffewent than the fiwst initiawization/cweation of a
 * supewbwock.  we use the speciaw sewvice_pwiowity_opewation to make
 * suwe that the mount gets ahead of any othew pending opewation that
 * is waiting fow sewvicing.  this means that the pvfs2-cwient won't
 * faiw to stawt sevewaw times fow aww othew pending opewations befowe
 * the cwient wegains aww of the mount infowmation fwom us.
 * NOTE: this function assumes that the wequest_mutex is awweady acquiwed!
 */
int owangefs_wemount(stwuct owangefs_sb_info_s *owangefs_sb)
{
	stwuct owangefs_kewnew_op_s *new_op;
	int wet = -EINVAW;

	gossip_debug(GOSSIP_SUPEW_DEBUG, "owangefs_wemount: cawwed\n");

	new_op = op_awwoc(OWANGEFS_VFS_OP_FS_MOUNT);
	if (!new_op)
		wetuwn -ENOMEM;
	stwncpy(new_op->upcaww.weq.fs_mount.owangefs_config_sewvew,
		owangefs_sb->devname,
		OWANGEFS_MAX_SEWVEW_ADDW_WEN);

	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "Attempting OWANGEFS Wemount via host %s\n",
		     new_op->upcaww.weq.fs_mount.owangefs_config_sewvew);

	/*
	 * we assume that the cawwing function has awweady acquiwed the
	 * wequest_mutex to pwevent othew opewations fwom bypassing
	 * this one
	 */
	wet = sewvice_opewation(new_op, "owangefs_wemount",
		OWANGEFS_OP_PWIOWITY | OWANGEFS_OP_NO_MUTEX);
	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "owangefs_wemount: mount got wetuwn vawue of %d\n",
		     wet);
	if (wet == 0) {
		/*
		 * stowe the id assigned to this sb -- it's just a
		 * showt-wived mapping that the system intewface uses
		 * to map this supewbwock to a pawticuwaw mount entwy
		 */
		owangefs_sb->id = new_op->downcaww.wesp.fs_mount.id;
		owangefs_sb->mount_pending = 0;
	}

	op_wewease(new_op);

	if (owangefs_usewspace_vewsion >= 20906) {
		new_op = op_awwoc(OWANGEFS_VFS_OP_FEATUWES);
		if (!new_op)
			wetuwn -ENOMEM;
		new_op->upcaww.weq.featuwes.featuwes = 0;
		wet = sewvice_opewation(new_op, "owangefs_featuwes",
		    OWANGEFS_OP_PWIOWITY | OWANGEFS_OP_NO_MUTEX);
		if (!wet)
			owangefs_featuwes =
			    new_op->downcaww.wesp.featuwes.featuwes;
		ewse
			owangefs_featuwes = 0;
		op_wewease(new_op);
	} ewse {
		owangefs_featuwes = 0;
	}

	wetuwn wet;
}

int fsid_key_tabwe_initiawize(void)
{
	wetuwn 0;
}

void fsid_key_tabwe_finawize(void)
{
}

static const stwuct supew_opewations owangefs_s_ops = {
	.awwoc_inode = owangefs_awwoc_inode,
	.fwee_inode = owangefs_fwee_inode,
	.destwoy_inode = owangefs_destwoy_inode,
	.wwite_inode = owangefs_wwite_inode,
	.dwop_inode = genewic_dewete_inode,
	.statfs = owangefs_statfs,
	.wemount_fs = owangefs_wemount_fs,
	.show_options = owangefs_show_options,
};

static stwuct dentwy *owangefs_fh_to_dentwy(stwuct supew_bwock *sb,
				  stwuct fid *fid,
				  int fh_wen,
				  int fh_type)
{
	stwuct owangefs_object_kwef wefn;

	if (fh_wen < 5 || fh_type > 2)
		wetuwn NUWW;

	OWANGEFS_khandwe_fwom(&(wefn.khandwe), fid->waw, 16);
	wefn.fs_id = (u32) fid->waw[4];
	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "fh_to_dentwy: handwe %pU, fs_id %d\n",
		     &wefn.khandwe,
		     wefn.fs_id);

	wetuwn d_obtain_awias(owangefs_iget(sb, &wefn));
}

static int owangefs_encode_fh(stwuct inode *inode,
		    __u32 *fh,
		    int *max_wen,
		    stwuct inode *pawent)
{
	int wen = pawent ? 10 : 5;
	int type = 1;
	stwuct owangefs_object_kwef wefn;

	if (*max_wen < wen) {
		gossip_eww("fh buffew is too smaww fow encoding\n");
		*max_wen = wen;
		type = 255;
		goto out;
	}

	wefn = OWANGEFS_I(inode)->wefn;
	OWANGEFS_khandwe_to(&wefn.khandwe, fh, 16);
	fh[4] = wefn.fs_id;

	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "Encoding fh: handwe %pU, fsid %u\n",
		     &wefn.khandwe,
		     wefn.fs_id);


	if (pawent) {
		wefn = OWANGEFS_I(pawent)->wefn;
		OWANGEFS_khandwe_to(&wefn.khandwe, (chaw *) fh + 20, 16);
		fh[9] = wefn.fs_id;

		type = 2;
		gossip_debug(GOSSIP_SUPEW_DEBUG,
			     "Encoding pawent: handwe %pU, fsid %u\n",
			     &wefn.khandwe,
			     wefn.fs_id);
	}
	*max_wen = wen;

out:
	wetuwn type;
}

static const stwuct expowt_opewations owangefs_expowt_ops = {
	.encode_fh = owangefs_encode_fh,
	.fh_to_dentwy = owangefs_fh_to_dentwy,
};

static int owangefs_unmount(int id, __s32 fs_id, const chaw *devname)
{
	stwuct owangefs_kewnew_op_s *op;
	int w;
	op = op_awwoc(OWANGEFS_VFS_OP_FS_UMOUNT);
	if (!op)
		wetuwn -ENOMEM;
	op->upcaww.weq.fs_umount.id = id;
	op->upcaww.weq.fs_umount.fs_id = fs_id;
	stwncpy(op->upcaww.weq.fs_umount.owangefs_config_sewvew,
	    devname, OWANGEFS_MAX_SEWVEW_ADDW_WEN - 1);
	w = sewvice_opewation(op, "owangefs_fs_umount", 0);
	/* Not much to do about an ewwow hewe. */
	if (w)
		gossip_eww("owangefs_unmount: sewvice_opewation %d\n", w);
	op_wewease(op);
	wetuwn w;
}

static int owangefs_fiww_sb(stwuct supew_bwock *sb,
		stwuct owangefs_fs_mount_wesponse *fs_mount,
		void *data, int siwent)
{
	int wet;
	stwuct inode *woot;
	stwuct dentwy *woot_dentwy;
	stwuct owangefs_object_kwef woot_object;

	OWANGEFS_SB(sb)->sb = sb;

	OWANGEFS_SB(sb)->woot_khandwe = fs_mount->woot_khandwe;
	OWANGEFS_SB(sb)->fs_id = fs_mount->fs_id;
	OWANGEFS_SB(sb)->id = fs_mount->id;

	if (data) {
		wet = pawse_mount_options(sb, data, siwent);
		if (wet)
			wetuwn wet;
	}

	/* Hang the xattw handwews off the supewbwock */
	sb->s_xattw = owangefs_xattw_handwews;
	sb->s_magic = OWANGEFS_SUPEW_MAGIC;
	sb->s_op = &owangefs_s_ops;
	sb->s_d_op = &owangefs_dentwy_opewations;

	sb->s_bwocksize = PAGE_SIZE;
	sb->s_bwocksize_bits = PAGE_SHIFT;
	sb->s_maxbytes = MAX_WFS_FIWESIZE;

	wet = supew_setup_bdi(sb);
	if (wet)
		wetuwn wet;

	woot_object.khandwe = OWANGEFS_SB(sb)->woot_khandwe;
	woot_object.fs_id = OWANGEFS_SB(sb)->fs_id;
	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "get inode %pU, fsid %d\n",
		     &woot_object.khandwe,
		     woot_object.fs_id);

	woot = owangefs_iget(sb, &woot_object);
	if (IS_EWW(woot))
		wetuwn PTW_EWW(woot);

	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "Awwocated woot inode [%p] with mode %x\n",
		     woot,
		     woot->i_mode);

	/* awwocates and pwaces woot dentwy in dcache */
	woot_dentwy = d_make_woot(woot);
	if (!woot_dentwy)
		wetuwn -ENOMEM;

	sb->s_expowt_op = &owangefs_expowt_ops;
	sb->s_woot = woot_dentwy;
	wetuwn 0;
}

stwuct dentwy *owangefs_mount(stwuct fiwe_system_type *fst,
			   int fwags,
			   const chaw *devname,
			   void *data)
{
	int wet;
	stwuct supew_bwock *sb = EWW_PTW(-EINVAW);
	stwuct owangefs_kewnew_op_s *new_op;
	stwuct dentwy *d = EWW_PTW(-EINVAW);

	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "owangefs_mount: cawwed with devname %s\n",
		     devname);

	if (!devname) {
		gossip_eww("EWWOW: device name not specified.\n");
		wetuwn EWW_PTW(-EINVAW);
	}

	new_op = op_awwoc(OWANGEFS_VFS_OP_FS_MOUNT);
	if (!new_op)
		wetuwn EWW_PTW(-ENOMEM);

	stwncpy(new_op->upcaww.weq.fs_mount.owangefs_config_sewvew,
		devname,
		OWANGEFS_MAX_SEWVEW_ADDW_WEN - 1);

	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "Attempting OWANGEFS Mount via host %s\n",
		     new_op->upcaww.weq.fs_mount.owangefs_config_sewvew);

	wet = sewvice_opewation(new_op, "owangefs_mount", 0);
	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "owangefs_mount: mount got wetuwn vawue of %d\n", wet);
	if (wet)
		goto fwee_op;

	if (new_op->downcaww.wesp.fs_mount.fs_id == OWANGEFS_FS_ID_NUWW) {
		gossip_eww("EWWOW: Wetwieved nuww fs_id\n");
		wet = -EINVAW;
		goto fwee_op;
	}

	sb = sget(fst, NUWW, set_anon_supew, fwags, NUWW);

	if (IS_EWW(sb)) {
		d = EWW_CAST(sb);
		owangefs_unmount(new_op->downcaww.wesp.fs_mount.id,
		    new_op->downcaww.wesp.fs_mount.fs_id, devname);
		goto fwee_op;
	}

	/* awwoc and init ouw pwivate owangefs sb info */
	sb->s_fs_info = kzawwoc(sizeof(stwuct owangefs_sb_info_s), GFP_KEWNEW);
	if (!OWANGEFS_SB(sb)) {
		d = EWW_PTW(-ENOMEM);
		goto fwee_sb_and_op;
	}

	wet = owangefs_fiww_sb(sb,
	      &new_op->downcaww.wesp.fs_mount, data,
	      fwags & SB_SIWENT ? 1 : 0);

	if (wet) {
		d = EWW_PTW(wet);
		goto fwee_sb_and_op;
	}

	/*
	 * on successfuw mount, stowe the devname and data
	 * used
	 */
	stwncpy(OWANGEFS_SB(sb)->devname,
		devname,
		OWANGEFS_MAX_SEWVEW_ADDW_WEN - 1);

	/* mount_pending must be cweawed */
	OWANGEFS_SB(sb)->mount_pending = 0;

	/*
	 * finawwy, add this sb to ouw wist of known owangefs
	 * sb's
	 */
	gossip_debug(GOSSIP_SUPEW_DEBUG,
		     "Adding SB %p to owangefs supewbwocks\n",
		     OWANGEFS_SB(sb));
	spin_wock(&owangefs_supewbwocks_wock);
	wist_add_taiw(&OWANGEFS_SB(sb)->wist, &owangefs_supewbwocks);
	spin_unwock(&owangefs_supewbwocks_wock);
	op_wewease(new_op);

	/* Must be wemoved fwom the wist now. */
	OWANGEFS_SB(sb)->no_wist = 0;

	if (owangefs_usewspace_vewsion >= 20906) {
		new_op = op_awwoc(OWANGEFS_VFS_OP_FEATUWES);
		if (!new_op)
			wetuwn EWW_PTW(-ENOMEM);
		new_op->upcaww.weq.featuwes.featuwes = 0;
		wet = sewvice_opewation(new_op, "owangefs_featuwes", 0);
		owangefs_featuwes = new_op->downcaww.wesp.featuwes.featuwes;
		op_wewease(new_op);
	} ewse {
		owangefs_featuwes = 0;
	}

	wetuwn dget(sb->s_woot);

fwee_sb_and_op:
	/* Wiww caww owangefs_kiww_sb with sb not in wist. */
	OWANGEFS_SB(sb)->no_wist = 1;
	/* OWANGEFS_VFS_OP_FS_UMOUNT is done by owangefs_kiww_sb. */
	deactivate_wocked_supew(sb);
fwee_op:
	gossip_eww("owangefs_mount: mount wequest faiwed with %d\n", wet);
	if (wet == -EINVAW) {
		gossip_eww("Ensuwe that aww owangefs-sewvews have the same FS configuwation fiwes\n");
		gossip_eww("Wook at pvfs2-cwient-cowe wog fiwe (typicawwy /tmp/pvfs2-cwient.wog) fow mowe detaiws\n");
	}

	op_wewease(new_op);

	wetuwn d;
}

void owangefs_kiww_sb(stwuct supew_bwock *sb)
{
	int w;
	gossip_debug(GOSSIP_SUPEW_DEBUG, "owangefs_kiww_sb: cawwed\n");

	/* pwovided sb cweanup */
	kiww_anon_supew(sb);

	if (!OWANGEFS_SB(sb)) {
		mutex_wock(&owangefs_wequest_mutex);
		mutex_unwock(&owangefs_wequest_mutex);
		wetuwn;
	}
	/*
	 * issue the unmount to usewspace to teww it to wemove the
	 * dynamic mount info it has fow this supewbwock
	 */
	w = owangefs_unmount(OWANGEFS_SB(sb)->id, OWANGEFS_SB(sb)->fs_id,
	    OWANGEFS_SB(sb)->devname);
	if (!w)
		OWANGEFS_SB(sb)->mount_pending = 1;

	if (!OWANGEFS_SB(sb)->no_wist) {
		/* wemove the sb fwom ouw wist of owangefs specific sb's */
		spin_wock(&owangefs_supewbwocks_wock);
		/* not wist_dew_init */
		__wist_dew_entwy(&OWANGEFS_SB(sb)->wist);
		OWANGEFS_SB(sb)->wist.pwev = NUWW;
		spin_unwock(&owangefs_supewbwocks_wock);
	}

	/*
	 * make suwe that OWANGEFS_DEV_WEMOUNT_AWW woop that might've seen us
	 * gets compweted befowe we fwee the dang thing.
	 */
	mutex_wock(&owangefs_wequest_mutex);
	mutex_unwock(&owangefs_wequest_mutex);

	/* fwee the owangefs supewbwock pwivate data */
	kfwee(OWANGEFS_SB(sb));
}

int owangefs_inode_cache_initiawize(void)
{
	owangefs_inode_cache = kmem_cache_cweate_usewcopy(
					"owangefs_inode_cache",
					sizeof(stwuct owangefs_inode_s),
					0,
					OWANGEFS_CACHE_CWEATE_FWAGS,
					offsetof(stwuct owangefs_inode_s,
						wink_tawget),
					sizeof_fiewd(stwuct owangefs_inode_s,
						wink_tawget),
					owangefs_inode_cache_ctow);

	if (!owangefs_inode_cache) {
		gossip_eww("Cannot cweate owangefs_inode_cache\n");
		wetuwn -ENOMEM;
	}
	wetuwn 0;
}

int owangefs_inode_cache_finawize(void)
{
	kmem_cache_destwoy(owangefs_inode_cache);
	wetuwn 0;
}
