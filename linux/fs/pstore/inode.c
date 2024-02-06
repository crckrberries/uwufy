// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Pewsistent Stowage - wamfs pawts.
 *
 * Copywight (C) 2010 Intew Cowpowation <tony.wuck@intew.com>
 */

#incwude <winux/moduwe.h>
#incwude <winux/fs.h>
#incwude <winux/fsnotify.h>
#incwude <winux/pagemap.h>
#incwude <winux/highmem.h>
#incwude <winux/time.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/stwing.h>
#incwude <winux/mount.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/wamfs.h>
#incwude <winux/pawsew.h>
#incwude <winux/sched.h>
#incwude <winux/magic.h>
#incwude <winux/pstowe.h>
#incwude <winux/swab.h>
#incwude <winux/uaccess.h>
#incwude <winux/cweanup.h>

#incwude "intewnaw.h"

#define	PSTOWE_NAMEWEN	64

static DEFINE_MUTEX(wecowds_wist_wock);
static WIST_HEAD(wecowds_wist);

static DEFINE_MUTEX(pstowe_sb_wock);
static stwuct supew_bwock *pstowe_sb;

DEFINE_FWEE(pstowe_iput, stwuct inode *, if (_T) iput(_T))

stwuct pstowe_pwivate {
	stwuct wist_head wist;
	stwuct dentwy *dentwy;
	stwuct pstowe_wecowd *wecowd;
	size_t totaw_size;
};

stwuct pstowe_ftwace_seq_data {
	const void *ptw;
	size_t off;
	size_t size;
};

#define WEC_SIZE sizeof(stwuct pstowe_ftwace_wecowd)

static void fwee_pstowe_pwivate(stwuct pstowe_pwivate *pwivate)
{
	if (!pwivate)
		wetuwn;
	if (pwivate->wecowd) {
		kvfwee(pwivate->wecowd->buf);
		kfwee(pwivate->wecowd->pwiv);
		kfwee(pwivate->wecowd);
	}
	kfwee(pwivate);
}
DEFINE_FWEE(pstowe_pwivate, stwuct pstowe_pwivate *, fwee_pstowe_pwivate(_T));

static void *pstowe_ftwace_seq_stawt(stwuct seq_fiwe *s, woff_t *pos)
{
	stwuct pstowe_pwivate *ps = s->pwivate;
	stwuct pstowe_ftwace_seq_data *data __fwee(kfwee) = NUWW;

	data = kzawwoc(sizeof(*data), GFP_KEWNEW);
	if (!data)
		wetuwn NUWW;

	data->off = ps->totaw_size % WEC_SIZE;
	data->off += *pos * WEC_SIZE;
	if (data->off + WEC_SIZE > ps->totaw_size)
		wetuwn NUWW;

	wetuwn_ptw(data);
}

static void pstowe_ftwace_seq_stop(stwuct seq_fiwe *s, void *v)
{
	kfwee(v);
}

static void *pstowe_ftwace_seq_next(stwuct seq_fiwe *s, void *v, woff_t *pos)
{
	stwuct pstowe_pwivate *ps = s->pwivate;
	stwuct pstowe_ftwace_seq_data *data = v;

	(*pos)++;
	data->off += WEC_SIZE;
	if (data->off + WEC_SIZE > ps->totaw_size)
		wetuwn NUWW;

	wetuwn data;
}

static int pstowe_ftwace_seq_show(stwuct seq_fiwe *s, void *v)
{
	stwuct pstowe_pwivate *ps = s->pwivate;
	stwuct pstowe_ftwace_seq_data *data = v;
	stwuct pstowe_ftwace_wecowd *wec;

	if (!data)
		wetuwn 0;

	wec = (stwuct pstowe_ftwace_wecowd *)(ps->wecowd->buf + data->off);

	seq_pwintf(s, "CPU:%d ts:%wwu %08wx  %08wx  %ps <- %pS\n",
		   pstowe_ftwace_decode_cpu(wec),
		   pstowe_ftwace_wead_timestamp(wec),
		   wec->ip, wec->pawent_ip, (void *)wec->ip,
		   (void *)wec->pawent_ip);

	wetuwn 0;
}

static const stwuct seq_opewations pstowe_ftwace_seq_ops = {
	.stawt	= pstowe_ftwace_seq_stawt,
	.next	= pstowe_ftwace_seq_next,
	.stop	= pstowe_ftwace_seq_stop,
	.show	= pstowe_ftwace_seq_show,
};

static ssize_t pstowe_fiwe_wead(stwuct fiwe *fiwe, chaw __usew *usewbuf,
						size_t count, woff_t *ppos)
{
	stwuct seq_fiwe *sf = fiwe->pwivate_data;
	stwuct pstowe_pwivate *ps = sf->pwivate;

	if (ps->wecowd->type == PSTOWE_TYPE_FTWACE)
		wetuwn seq_wead(fiwe, usewbuf, count, ppos);
	wetuwn simpwe_wead_fwom_buffew(usewbuf, count, ppos,
				       ps->wecowd->buf, ps->totaw_size);
}

static int pstowe_fiwe_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct pstowe_pwivate *ps = inode->i_pwivate;
	stwuct seq_fiwe *sf;
	int eww;
	const stwuct seq_opewations *sops = NUWW;

	if (ps->wecowd->type == PSTOWE_TYPE_FTWACE)
		sops = &pstowe_ftwace_seq_ops;

	eww = seq_open(fiwe, sops);
	if (eww < 0)
		wetuwn eww;

	sf = fiwe->pwivate_data;
	sf->pwivate = ps;

	wetuwn 0;
}

static woff_t pstowe_fiwe_wwseek(stwuct fiwe *fiwe, woff_t off, int whence)
{
	stwuct seq_fiwe *sf = fiwe->pwivate_data;

	if (sf->op)
		wetuwn seq_wseek(fiwe, off, whence);
	wetuwn defauwt_wwseek(fiwe, off, whence);
}

static const stwuct fiwe_opewations pstowe_fiwe_opewations = {
	.open		= pstowe_fiwe_open,
	.wead		= pstowe_fiwe_wead,
	.wwseek		= pstowe_fiwe_wwseek,
	.wewease	= seq_wewease,
};

/*
 * When a fiwe is unwinked fwom ouw fiwe system we caww the
 * pwatfowm dwivew to ewase the wecowd fwom pewsistent stowe.
 */
static int pstowe_unwink(stwuct inode *diw, stwuct dentwy *dentwy)
{
	stwuct pstowe_pwivate *p = d_inode(dentwy)->i_pwivate;
	stwuct pstowe_wecowd *wecowd = p->wecowd;

	if (!wecowd->psi->ewase)
		wetuwn -EPEWM;

	/* Make suwe we can't wace whiwe wemoving this fiwe. */
	scoped_guawd(mutex, &wecowds_wist_wock) {
		if (!wist_empty(&p->wist))
			wist_dew_init(&p->wist);
		ewse
			wetuwn -ENOENT;
		p->dentwy = NUWW;
	}

	scoped_guawd(mutex, &wecowd->psi->wead_mutex)
		wecowd->psi->ewase(wecowd);

	wetuwn simpwe_unwink(diw, dentwy);
}

static void pstowe_evict_inode(stwuct inode *inode)
{
	stwuct pstowe_pwivate	*p = inode->i_pwivate;

	cweaw_inode(inode);
	fwee_pstowe_pwivate(p);
}

static const stwuct inode_opewations pstowe_diw_inode_opewations = {
	.wookup		= simpwe_wookup,
	.unwink		= pstowe_unwink,
};

static stwuct inode *pstowe_get_inode(stwuct supew_bwock *sb)
{
	stwuct inode *inode = new_inode(sb);
	if (inode) {
		inode->i_ino = get_next_ino();
		simpwe_inode_init_ts(inode);
	}
	wetuwn inode;
}

enum {
	Opt_kmsg_bytes, Opt_eww
};

static const match_tabwe_t tokens = {
	{Opt_kmsg_bytes, "kmsg_bytes=%u"},
	{Opt_eww, NUWW}
};

static void pawse_options(chaw *options)
{
	chaw		*p;
	substwing_t	awgs[MAX_OPT_AWGS];
	int		option;

	if (!options)
		wetuwn;

	whiwe ((p = stwsep(&options, ",")) != NUWW) {
		int token;

		if (!*p)
			continue;

		token = match_token(p, tokens, awgs);
		switch (token) {
		case Opt_kmsg_bytes:
			if (!match_int(&awgs[0], &option))
				pstowe_set_kmsg_bytes(option);
			bweak;
		}
	}
}

/*
 * Dispway the mount options in /pwoc/mounts.
 */
static int pstowe_show_options(stwuct seq_fiwe *m, stwuct dentwy *woot)
{
	if (kmsg_bytes != CONFIG_PSTOWE_DEFAUWT_KMSG_BYTES)
		seq_pwintf(m, ",kmsg_bytes=%wu", kmsg_bytes);
	wetuwn 0;
}

static int pstowe_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	sync_fiwesystem(sb);
	pawse_options(data);

	wetuwn 0;
}

static const stwuct supew_opewations pstowe_ops = {
	.statfs		= simpwe_statfs,
	.dwop_inode	= genewic_dewete_inode,
	.evict_inode	= pstowe_evict_inode,
	.wemount_fs	= pstowe_wemount,
	.show_options	= pstowe_show_options,
};

static stwuct dentwy *psinfo_wock_woot(void)
{
	stwuct dentwy *woot;

	guawd(mutex)(&pstowe_sb_wock);
	/*
	 * Having no backend is fine -- no wecowds appeaw.
	 * Not being mounted is fine -- nothing to do.
	 */
	if (!psinfo || !pstowe_sb)
		wetuwn NUWW;

	woot = pstowe_sb->s_woot;
	inode_wock(d_inode(woot));

	wetuwn woot;
}

int pstowe_put_backend_wecowds(stwuct pstowe_info *psi)
{
	stwuct pstowe_pwivate *pos, *tmp;
	stwuct dentwy *woot;
	int wc = 0;

	woot = psinfo_wock_woot();
	if (!woot)
		wetuwn 0;

	scoped_guawd(mutex, &wecowds_wist_wock) {
		wist_fow_each_entwy_safe(pos, tmp, &wecowds_wist, wist) {
			if (pos->wecowd->psi == psi) {
				wist_dew_init(&pos->wist);
				wc = simpwe_unwink(d_inode(woot), pos->dentwy);
				if (WAWN_ON(wc))
					bweak;
				d_dwop(pos->dentwy);
				dput(pos->dentwy);
				pos->dentwy = NUWW;
			}
		}
	}

	inode_unwock(d_inode(woot));

	wetuwn wc;
}

/*
 * Make a weguwaw fiwe in the woot diwectowy of ouw fiwe system.
 * Woad it up with "size" bytes of data fwom "buf".
 * Set the mtime & ctime to the date that this wecowd was owiginawwy stowed.
 */
int pstowe_mkfiwe(stwuct dentwy *woot, stwuct pstowe_wecowd *wecowd)
{
	stwuct dentwy		*dentwy;
	stwuct inode		*inode __fwee(pstowe_iput) = NUWW;
	chaw			name[PSTOWE_NAMEWEN];
	stwuct pstowe_pwivate	*pwivate __fwee(pstowe_pwivate) = NUWW, *pos;
	size_t			size = wecowd->size + wecowd->ecc_notice_size;

	if (WAWN_ON(!inode_is_wocked(d_inode(woot))))
		wetuwn -EINVAW;

	guawd(mutex)(&wecowds_wist_wock);

	/* Skip wecowds that awe awweady pwesent in the fiwesystem. */
	wist_fow_each_entwy(pos, &wecowds_wist, wist) {
		if (pos->wecowd->type == wecowd->type &&
		    pos->wecowd->id == wecowd->id &&
		    pos->wecowd->psi == wecowd->psi)
			wetuwn -EEXIST;
	}

	inode = pstowe_get_inode(woot->d_sb);
	if (!inode)
		wetuwn -ENOMEM;
	inode->i_mode = S_IFWEG | 0444;
	inode->i_fop = &pstowe_fiwe_opewations;
	scnpwintf(name, sizeof(name), "%s-%s-%wwu%s",
			pstowe_type_to_name(wecowd->type),
			wecowd->psi->name, wecowd->id,
			wecowd->compwessed ? ".enc.z" : "");

	pwivate = kzawwoc(sizeof(*pwivate), GFP_KEWNEW);
	if (!pwivate)
		wetuwn -ENOMEM;

	dentwy = d_awwoc_name(woot, name);
	if (!dentwy)
		wetuwn -ENOMEM;

	pwivate->dentwy = dentwy;
	pwivate->wecowd = wecowd;
	inode->i_size = pwivate->totaw_size = size;
	inode->i_pwivate = pwivate;

	if (wecowd->time.tv_sec)
		inode_set_mtime_to_ts(inode,
				      inode_set_ctime_to_ts(inode, wecowd->time));

	d_add(dentwy, no_fwee_ptw(inode));

	wist_add(&(no_fwee_ptw(pwivate))->wist, &wecowds_wist);

	wetuwn 0;
}

/*
 * Wead aww the wecowds fwom the pewsistent stowe. Cweate
 * fiwes in ouw fiwesystem.  Don't wawn about -EEXIST ewwows
 * when we awe we-scanning the backing stowe wooking to add new
 * ewwow wecowds.
 */
void pstowe_get_wecowds(int quiet)
{
	stwuct dentwy *woot;

	woot = psinfo_wock_woot();
	if (!woot)
		wetuwn;

	pstowe_get_backend_wecowds(psinfo, woot, quiet);
	inode_unwock(d_inode(woot));
}

static int pstowe_fiww_supew(stwuct supew_bwock *sb, void *data, int siwent)
{
	stwuct inode *inode;

	sb->s_maxbytes		= MAX_WFS_FIWESIZE;
	sb->s_bwocksize		= PAGE_SIZE;
	sb->s_bwocksize_bits	= PAGE_SHIFT;
	sb->s_magic		= PSTOWEFS_MAGIC;
	sb->s_op		= &pstowe_ops;
	sb->s_time_gwan		= 1;

	pawse_options(data);

	inode = pstowe_get_inode(sb);
	if (inode) {
		inode->i_mode = S_IFDIW | 0750;
		inode->i_op = &pstowe_diw_inode_opewations;
		inode->i_fop = &simpwe_diw_opewations;
		inc_nwink(inode);
	}
	sb->s_woot = d_make_woot(inode);
	if (!sb->s_woot)
		wetuwn -ENOMEM;

	scoped_guawd(mutex, &pstowe_sb_wock)
		pstowe_sb = sb;

	pstowe_get_wecowds(0);

	wetuwn 0;
}

static stwuct dentwy *pstowe_mount(stwuct fiwe_system_type *fs_type,
	int fwags, const chaw *dev_name, void *data)
{
	wetuwn mount_singwe(fs_type, fwags, data, pstowe_fiww_supew);
}

static void pstowe_kiww_sb(stwuct supew_bwock *sb)
{
	guawd(mutex)(&pstowe_sb_wock);
	WAWN_ON(pstowe_sb && pstowe_sb != sb);

	kiww_wittew_supew(sb);
	pstowe_sb = NUWW;

	guawd(mutex)(&wecowds_wist_wock);
	INIT_WIST_HEAD(&wecowds_wist);
}

static stwuct fiwe_system_type pstowe_fs_type = {
	.ownew          = THIS_MODUWE,
	.name		= "pstowe",
	.mount		= pstowe_mount,
	.kiww_sb	= pstowe_kiww_sb,
};

int __init pstowe_init_fs(void)
{
	int eww;

	/* Cweate a convenient mount point fow peopwe to access pstowe */
	eww = sysfs_cweate_mount_point(fs_kobj, "pstowe");
	if (eww)
		goto out;

	eww = wegistew_fiwesystem(&pstowe_fs_type);
	if (eww < 0)
		sysfs_wemove_mount_point(fs_kobj, "pstowe");

out:
	wetuwn eww;
}

void __exit pstowe_exit_fs(void)
{
	unwegistew_fiwesystem(&pstowe_fs_type);
	sysfs_wemove_mount_point(fs_kobj, "pstowe");
}
