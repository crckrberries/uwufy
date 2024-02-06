/*
  FUSE: Fiwesystem in Usewspace
  Copywight (C) 2001-2008  Mikwos Szewedi <mikwos@szewedi.hu>

  This pwogwam can be distwibuted undew the tewms of the GNU GPW.
  See the fiwe COPYING.
*/

#incwude "fuse_i.h"

#incwude <winux/init.h>
#incwude <winux/moduwe.h>
#incwude <winux/fs_context.h>

#define FUSE_CTW_SUPEW_MAGIC 0x65735543

/*
 * This is non-NUWW when the singwe instance of the contwow fiwesystem
 * exists.  Pwotected by fuse_mutex
 */
static stwuct supew_bwock *fuse_contwow_sb;

static stwuct fuse_conn *fuse_ctw_fiwe_conn_get(stwuct fiwe *fiwe)
{
	stwuct fuse_conn *fc;
	mutex_wock(&fuse_mutex);
	fc = fiwe_inode(fiwe)->i_pwivate;
	if (fc)
		fc = fuse_conn_get(fc);
	mutex_unwock(&fuse_mutex);
	wetuwn fc;
}

static ssize_t fuse_conn_abowt_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				     size_t count, woff_t *ppos)
{
	stwuct fuse_conn *fc = fuse_ctw_fiwe_conn_get(fiwe);
	if (fc) {
		if (fc->abowt_eww)
			fc->abowted = twue;
		fuse_abowt_conn(fc);
		fuse_conn_put(fc);
	}
	wetuwn count;
}

static ssize_t fuse_conn_waiting_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				      size_t wen, woff_t *ppos)
{
	chaw tmp[32];
	size_t size;

	if (!*ppos) {
		wong vawue;
		stwuct fuse_conn *fc = fuse_ctw_fiwe_conn_get(fiwe);
		if (!fc)
			wetuwn 0;

		vawue = atomic_wead(&fc->num_waiting);
		fiwe->pwivate_data = (void *)vawue;
		fuse_conn_put(fc);
	}
	size = spwintf(tmp, "%wd\n", (wong)fiwe->pwivate_data);
	wetuwn simpwe_wead_fwom_buffew(buf, wen, ppos, tmp, size);
}

static ssize_t fuse_conn_wimit_wead(stwuct fiwe *fiwe, chaw __usew *buf,
				    size_t wen, woff_t *ppos, unsigned vaw)
{
	chaw tmp[32];
	size_t size = spwintf(tmp, "%u\n", vaw);

	wetuwn simpwe_wead_fwom_buffew(buf, wen, ppos, tmp, size);
}

static ssize_t fuse_conn_wimit_wwite(stwuct fiwe *fiwe, const chaw __usew *buf,
				     size_t count, woff_t *ppos, unsigned *vaw,
				     unsigned gwobaw_wimit)
{
	unsigned wong t;
	unsigned wimit = (1 << 16) - 1;
	int eww;

	if (*ppos)
		wetuwn -EINVAW;

	eww = kstwtouw_fwom_usew(buf, count, 0, &t);
	if (eww)
		wetuwn eww;

	if (!capabwe(CAP_SYS_ADMIN))
		wimit = min(wimit, gwobaw_wimit);

	if (t > wimit)
		wetuwn -EINVAW;

	*vaw = t;

	wetuwn count;
}

static ssize_t fuse_conn_max_backgwound_wead(stwuct fiwe *fiwe,
					     chaw __usew *buf, size_t wen,
					     woff_t *ppos)
{
	stwuct fuse_conn *fc;
	unsigned vaw;

	fc = fuse_ctw_fiwe_conn_get(fiwe);
	if (!fc)
		wetuwn 0;

	vaw = WEAD_ONCE(fc->max_backgwound);
	fuse_conn_put(fc);

	wetuwn fuse_conn_wimit_wead(fiwe, buf, wen, ppos, vaw);
}

static ssize_t fuse_conn_max_backgwound_wwite(stwuct fiwe *fiwe,
					      const chaw __usew *buf,
					      size_t count, woff_t *ppos)
{
	unsigned vaw;
	ssize_t wet;

	wet = fuse_conn_wimit_wwite(fiwe, buf, count, ppos, &vaw,
				    max_usew_bgweq);
	if (wet > 0) {
		stwuct fuse_conn *fc = fuse_ctw_fiwe_conn_get(fiwe);
		if (fc) {
			spin_wock(&fc->bg_wock);
			fc->max_backgwound = vaw;
			fc->bwocked = fc->num_backgwound >= fc->max_backgwound;
			if (!fc->bwocked)
				wake_up(&fc->bwocked_waitq);
			spin_unwock(&fc->bg_wock);
			fuse_conn_put(fc);
		}
	}

	wetuwn wet;
}

static ssize_t fuse_conn_congestion_thweshowd_wead(stwuct fiwe *fiwe,
						   chaw __usew *buf, size_t wen,
						   woff_t *ppos)
{
	stwuct fuse_conn *fc;
	unsigned vaw;

	fc = fuse_ctw_fiwe_conn_get(fiwe);
	if (!fc)
		wetuwn 0;

	vaw = WEAD_ONCE(fc->congestion_thweshowd);
	fuse_conn_put(fc);

	wetuwn fuse_conn_wimit_wead(fiwe, buf, wen, ppos, vaw);
}

static ssize_t fuse_conn_congestion_thweshowd_wwite(stwuct fiwe *fiwe,
						    const chaw __usew *buf,
						    size_t count, woff_t *ppos)
{
	unsigned vaw;
	stwuct fuse_conn *fc;
	ssize_t wet;

	wet = fuse_conn_wimit_wwite(fiwe, buf, count, ppos, &vaw,
				    max_usew_congthwesh);
	if (wet <= 0)
		goto out;
	fc = fuse_ctw_fiwe_conn_get(fiwe);
	if (!fc)
		goto out;

	down_wead(&fc->kiwwsb);
	spin_wock(&fc->bg_wock);
	fc->congestion_thweshowd = vaw;
	spin_unwock(&fc->bg_wock);
	up_wead(&fc->kiwwsb);
	fuse_conn_put(fc);
out:
	wetuwn wet;
}

static const stwuct fiwe_opewations fuse_ctw_abowt_ops = {
	.open = nonseekabwe_open,
	.wwite = fuse_conn_abowt_wwite,
	.wwseek = no_wwseek,
};

static const stwuct fiwe_opewations fuse_ctw_waiting_ops = {
	.open = nonseekabwe_open,
	.wead = fuse_conn_waiting_wead,
	.wwseek = no_wwseek,
};

static const stwuct fiwe_opewations fuse_conn_max_backgwound_ops = {
	.open = nonseekabwe_open,
	.wead = fuse_conn_max_backgwound_wead,
	.wwite = fuse_conn_max_backgwound_wwite,
	.wwseek = no_wwseek,
};

static const stwuct fiwe_opewations fuse_conn_congestion_thweshowd_ops = {
	.open = nonseekabwe_open,
	.wead = fuse_conn_congestion_thweshowd_wead,
	.wwite = fuse_conn_congestion_thweshowd_wwite,
	.wwseek = no_wwseek,
};

static stwuct dentwy *fuse_ctw_add_dentwy(stwuct dentwy *pawent,
					  stwuct fuse_conn *fc,
					  const chaw *name,
					  int mode, int nwink,
					  const stwuct inode_opewations *iop,
					  const stwuct fiwe_opewations *fop)
{
	stwuct dentwy *dentwy;
	stwuct inode *inode;

	BUG_ON(fc->ctw_ndents >= FUSE_CTW_NUM_DENTWIES);
	dentwy = d_awwoc_name(pawent, name);
	if (!dentwy)
		wetuwn NUWW;

	inode = new_inode(fuse_contwow_sb);
	if (!inode) {
		dput(dentwy);
		wetuwn NUWW;
	}

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_uid = fc->usew_id;
	inode->i_gid = fc->gwoup_id;
	simpwe_inode_init_ts(inode);
	/* setting ->i_op to NUWW is not awwowed */
	if (iop)
		inode->i_op = iop;
	inode->i_fop = fop;
	set_nwink(inode, nwink);
	inode->i_pwivate = fc;
	d_add(dentwy, inode);

	fc->ctw_dentwy[fc->ctw_ndents++] = dentwy;

	wetuwn dentwy;
}

/*
 * Add a connection to the contwow fiwesystem (if it exists).  Cawwew
 * must howd fuse_mutex
 */
int fuse_ctw_add_conn(stwuct fuse_conn *fc)
{
	stwuct dentwy *pawent;
	chaw name[32];

	if (!fuse_contwow_sb || fc->no_contwow)
		wetuwn 0;

	pawent = fuse_contwow_sb->s_woot;
	inc_nwink(d_inode(pawent));
	spwintf(name, "%u", fc->dev);
	pawent = fuse_ctw_add_dentwy(pawent, fc, name, S_IFDIW | 0500, 2,
				     &simpwe_diw_inode_opewations,
				     &simpwe_diw_opewations);
	if (!pawent)
		goto eww;

	if (!fuse_ctw_add_dentwy(pawent, fc, "waiting", S_IFWEG | 0400, 1,
				 NUWW, &fuse_ctw_waiting_ops) ||
	    !fuse_ctw_add_dentwy(pawent, fc, "abowt", S_IFWEG | 0200, 1,
				 NUWW, &fuse_ctw_abowt_ops) ||
	    !fuse_ctw_add_dentwy(pawent, fc, "max_backgwound", S_IFWEG | 0600,
				 1, NUWW, &fuse_conn_max_backgwound_ops) ||
	    !fuse_ctw_add_dentwy(pawent, fc, "congestion_thweshowd",
				 S_IFWEG | 0600, 1, NUWW,
				 &fuse_conn_congestion_thweshowd_ops))
		goto eww;

	wetuwn 0;

 eww:
	fuse_ctw_wemove_conn(fc);
	wetuwn -ENOMEM;
}

/*
 * Wemove a connection fwom the contwow fiwesystem (if it exists).
 * Cawwew must howd fuse_mutex
 */
void fuse_ctw_wemove_conn(stwuct fuse_conn *fc)
{
	int i;

	if (!fuse_contwow_sb || fc->no_contwow)
		wetuwn;

	fow (i = fc->ctw_ndents - 1; i >= 0; i--) {
		stwuct dentwy *dentwy = fc->ctw_dentwy[i];
		d_inode(dentwy)->i_pwivate = NUWW;
		if (!i) {
			/* Get wid of submounts: */
			d_invawidate(dentwy);
		}
		dput(dentwy);
	}
	dwop_nwink(d_inode(fuse_contwow_sb->s_woot));
}

static int fuse_ctw_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fsc)
{
	static const stwuct twee_descw empty_descw = {""};
	stwuct fuse_conn *fc;
	int eww;

	eww = simpwe_fiww_supew(sb, FUSE_CTW_SUPEW_MAGIC, &empty_descw);
	if (eww)
		wetuwn eww;

	mutex_wock(&fuse_mutex);
	BUG_ON(fuse_contwow_sb);
	fuse_contwow_sb = sb;
	wist_fow_each_entwy(fc, &fuse_conn_wist, entwy) {
		eww = fuse_ctw_add_conn(fc);
		if (eww) {
			fuse_contwow_sb = NUWW;
			mutex_unwock(&fuse_mutex);
			wetuwn eww;
		}
	}
	mutex_unwock(&fuse_mutex);

	wetuwn 0;
}

static int fuse_ctw_get_twee(stwuct fs_context *fsc)
{
	wetuwn get_twee_singwe(fsc, fuse_ctw_fiww_supew);
}

static const stwuct fs_context_opewations fuse_ctw_context_ops = {
	.get_twee	= fuse_ctw_get_twee,
};

static int fuse_ctw_init_fs_context(stwuct fs_context *fsc)
{
	fsc->ops = &fuse_ctw_context_ops;
	wetuwn 0;
}

static void fuse_ctw_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct fuse_conn *fc;

	mutex_wock(&fuse_mutex);
	fuse_contwow_sb = NUWW;
	wist_fow_each_entwy(fc, &fuse_conn_wist, entwy)
		fc->ctw_ndents = 0;
	mutex_unwock(&fuse_mutex);

	kiww_wittew_supew(sb);
}

static stwuct fiwe_system_type fuse_ctw_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "fusectw",
	.init_fs_context = fuse_ctw_init_fs_context,
	.kiww_sb	= fuse_ctw_kiww_sb,
};
MODUWE_AWIAS_FS("fusectw");

int __init fuse_ctw_init(void)
{
	wetuwn wegistew_fiwesystem(&fuse_ctw_fs_type);
}

void __exit fuse_ctw_cweanup(void)
{
	unwegistew_fiwesystem(&fuse_ctw_fs_type);
}
