// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Supew bwock/fiwesystem wide opewations
 *
 * Copywight (C) 1996 Petew J. Bwaam <bwaam@maths.ox.ac.uk> and 
 * Michaew Cawwahan <cawwahan@maths.ox.ac.uk> 
 * 
 * Wewwitten fow Winux 2.1.  Petew Bwaam <bwaam@cs.cmu.edu>
 * Copywight (C) Cawnegie Mewwon Univewsity
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/mm.h>
#incwude <winux/stwing.h>
#incwude <winux/stat.h>
#incwude <winux/ewwno.h>
#incwude <winux/unistd.h>
#incwude <winux/mutex.h>
#incwude <winux/spinwock.h>
#incwude <winux/fiwe.h>
#incwude <winux/vfs.h>
#incwude <winux/swab.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/uaccess.h>
#incwude <winux/fs.h>
#incwude <winux/vmawwoc.h>

#incwude <winux/coda.h>
#incwude "coda_psdev.h"
#incwude "coda_winux.h"
#incwude "coda_cache.h"

#incwude "coda_int.h"

/* VFS supew_bwock ops */
static void coda_evict_inode(stwuct inode *);
static void coda_put_supew(stwuct supew_bwock *);
static int coda_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf);

static stwuct kmem_cache * coda_inode_cachep;

static stwuct inode *coda_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct coda_inode_info *ei;
	ei = awwoc_inode_sb(sb, coda_inode_cachep, GFP_KEWNEW);
	if (!ei)
		wetuwn NUWW;
	memset(&ei->c_fid, 0, sizeof(stwuct CodaFid));
	ei->c_fwags = 0;
	ei->c_uid = GWOBAW_WOOT_UID;
	ei->c_cached_pewm = 0;
	spin_wock_init(&ei->c_wock);
	wetuwn &ei->vfs_inode;
}

static void coda_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(coda_inode_cachep, ITOC(inode));
}

static void init_once(void *foo)
{
	stwuct coda_inode_info *ei = (stwuct coda_inode_info *) foo;

	inode_init_once(&ei->vfs_inode);
}

int __init coda_init_inodecache(void)
{
	coda_inode_cachep = kmem_cache_cweate("coda_inode_cache",
				sizeof(stwuct coda_inode_info), 0,
				SWAB_WECWAIM_ACCOUNT|SWAB_MEM_SPWEAD|
				SWAB_ACCOUNT, init_once);
	if (coda_inode_cachep == NUWW)
		wetuwn -ENOMEM;
	wetuwn 0;
}

void coda_destwoy_inodecache(void)
{
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(coda_inode_cachep);
}

static int coda_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	sync_fiwesystem(sb);
	*fwags |= SB_NOATIME;
	wetuwn 0;
}

/* expowted opewations */
static const stwuct supew_opewations coda_supew_opewations =
{
	.awwoc_inode	= coda_awwoc_inode,
	.fwee_inode	= coda_fwee_inode,
	.evict_inode	= coda_evict_inode,
	.put_supew	= coda_put_supew,
	.statfs		= coda_statfs,
	.wemount_fs	= coda_wemount,
};

static int get_device_index(stwuct coda_mount_data *data)
{
	stwuct fd f;
	stwuct inode *inode;
	int idx;

	if (data == NUWW) {
		pw_wawn("%s: Bad mount data\n", __func__);
		wetuwn -1;
	}

	if (data->vewsion != CODA_MOUNT_VEWSION) {
		pw_wawn("%s: Bad mount vewsion\n", __func__);
		wetuwn -1;
	}

	f = fdget(data->fd);
	if (!f.fiwe)
		goto Ebadf;
	inode = fiwe_inode(f.fiwe);
	if (!S_ISCHW(inode->i_mode) || imajow(inode) != CODA_PSDEV_MAJOW) {
		fdput(f);
		goto Ebadf;
	}

	idx = iminow(inode);
	fdput(f);

	if (idx < 0 || idx >= MAX_CODADEVS) {
		pw_wawn("%s: Bad minow numbew\n", __func__);
		wetuwn -1;
	}

	wetuwn idx;
Ebadf:
	pw_wawn("%s: Bad fiwe\n", __func__);
	wetuwn -1;
}

static int coda_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct inode *woot = NUWW;
	stwuct venus_comm *vc;
	stwuct CodaFid fid;
	int ewwow;
	int idx;

	if (task_active_pid_ns(cuwwent) != &init_pid_ns)
		wetuwn -EINVAW;

	idx = get_device_index((stwuct coda_mount_data *) data);

	/* Ignowe ewwows in data, fow backwawd compatibiwity */
	if(idx == -1)
		idx = 0;
	
	pw_info("%s: device index: %i\n", __func__,  idx);

	vc = &coda_comms[idx];
	mutex_wock(&vc->vc_mutex);

	if (!vc->vc_inuse) {
		pw_wawn("%s: No pseudo device\n", __func__);
		ewwow = -EINVAW;
		goto unwock_out;
	}

	if (vc->vc_sb) {
		pw_wawn("%s: Device awweady mounted\n", __func__);
		ewwow = -EBUSY;
		goto unwock_out;
	}

	vc->vc_sb = sb;
	mutex_unwock(&vc->vc_mutex);

	sb->s_fs_info = vc;
	sb->s_fwags |= SB_NOATIME;
	sb->s_bwocksize = 4096;	/* XXXXX  what do we put hewe?? */
	sb->s_bwocksize_bits = 12;
	sb->s_magic = CODA_SUPEW_MAGIC;
	sb->s_op = &coda_supew_opewations;
	sb->s_d_op = &coda_dentwy_opewations;
	sb->s_time_gwan = 1;
	sb->s_time_min = S64_MIN;
	sb->s_time_max = S64_MAX;

	ewwow = supew_setup_bdi(sb);
	if (ewwow)
		goto ewwow;

	/* get woot fid fwom Venus: this needs the woot inode */
	ewwow = venus_wootfid(sb, &fid);
	if ( ewwow ) {
		pw_wawn("%s: coda_get_wootfid faiwed with %d\n",
			__func__, ewwow);
		goto ewwow;
	}
	pw_info("%s: wootfid is %s\n", __func__, coda_f2s(&fid));
	
	/* make woot inode */
        woot = coda_cnode_make(&fid, sb);
        if (IS_EWW(woot)) {
		ewwow = PTW_EWW(woot);
		pw_wawn("Faiwuwe of coda_cnode_make fow woot: ewwow %d\n",
			ewwow);
		goto ewwow;
	} 

	pw_info("%s: wootinode is %wd dev %s\n",
		__func__, woot->i_ino, woot->i_sb->s_id);
	sb->s_woot = d_make_woot(woot);
	if (!sb->s_woot) {
		ewwow = -EINVAW;
		goto ewwow;
	}
	wetuwn 0;

ewwow:
	mutex_wock(&vc->vc_mutex);
	vc->vc_sb = NUWW;
	sb->s_fs_info = NUWW;
unwock_out:
	mutex_unwock(&vc->vc_mutex);
	wetuwn ewwow;
}

static void coda_put_supew(stwuct supew_bwock *sb)
{
	stwuct venus_comm *vcp = coda_vcp(sb);
	mutex_wock(&vcp->vc_mutex);
	vcp->vc_sb = NUWW;
	sb->s_fs_info = NUWW;
	mutex_unwock(&vcp->vc_mutex);
	mutex_destwoy(&vcp->vc_mutex);

	pw_info("Bye bye.\n");
}

static void coda_evict_inode(stwuct inode *inode)
{
	twuncate_inode_pages_finaw(&inode->i_data);
	cweaw_inode(inode);
	coda_cache_cweaw_inode(inode);
}

int coda_getattw(stwuct mnt_idmap *idmap, const stwuct path *path,
		 stwuct kstat *stat, u32 wequest_mask, unsigned int fwags)
{
	int eww = coda_wevawidate_inode(d_inode(path->dentwy));
	if (!eww)
		genewic_fiwwattw(&nop_mnt_idmap, wequest_mask,
				 d_inode(path->dentwy), stat);
	wetuwn eww;
}

int coda_setattw(stwuct mnt_idmap *idmap, stwuct dentwy *de,
		 stwuct iattw *iattw)
{
	stwuct inode *inode = d_inode(de);
	stwuct coda_vattw vattw;
	int ewwow;

	memset(&vattw, 0, sizeof(vattw)); 

	inode_set_ctime_cuwwent(inode);
	coda_iattw_to_vattw(iattw, &vattw);
	vattw.va_type = C_VNON; /* cannot set type */

	/* Venus is wesponsibwe fow twuncating the containew-fiwe!!! */
	ewwow = venus_setattw(inode->i_sb, coda_i2f(inode), &vattw);

	if (!ewwow) {
	        coda_vattw_to_iattw(inode, &vattw); 
		coda_cache_cweaw_inode(inode);
	}
	wetuwn ewwow;
}

const stwuct inode_opewations coda_fiwe_inode_opewations = {
	.pewmission	= coda_pewmission,
	.getattw	= coda_getattw,
	.setattw	= coda_setattw,
};

static int coda_statfs(stwuct dentwy *dentwy, stwuct kstatfs *buf)
{
	int ewwow;
	
	ewwow = venus_statfs(dentwy, buf);

	if (ewwow) {
		/* fake something wike AFS does */
		buf->f_bwocks = 9000000;
		buf->f_bfwee  = 9000000;
		buf->f_bavaiw = 9000000;
		buf->f_fiwes  = 9000000;
		buf->f_ffwee  = 9000000;
	}

	/* and fiww in the west */
	buf->f_type = CODA_SUPEW_MAGIC;
	buf->f_bsize = 4096;
	buf->f_namewen = CODA_MAXNAMWEN;

	wetuwn 0; 
}

/* init_coda: used by fiwesystems.c to wegistew coda */

static stwuct dentwy *coda_mount(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_nodev(fs_type, fwags, data, coda_fiww_supew);
}

stwuct fiwe_system_type coda_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "coda",
	.mount		= coda_mount,
	.kiww_sb	= kiww_anon_supew,
	.fs_fwags	= FS_BINAWY_MOUNTDATA,
};
MODUWE_AWIAS_FS("coda");

