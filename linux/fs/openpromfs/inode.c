// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* inode.c: /pwoc/openpwom handwing woutines
 *
 * Copywight (C) 1996-1999 Jakub Jewinek  (jakub@wedhat.com)
 * Copywight (C) 1998      Eddie C. Dost  (ecd@skynet.be)
 */

#incwude <winux/moduwe.h>
#incwude <winux/types.h>
#incwude <winux/stwing.h>
#incwude <winux/fs.h>
#incwude <winux/fs_context.h>
#incwude <winux/init.h>
#incwude <winux/swab.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/magic.h>

#incwude <asm/openpwom.h>
#incwude <asm/opwib.h>
#incwude <asm/pwom.h>
#incwude <winux/uaccess.h>

static DEFINE_MUTEX(op_mutex);

#define OPENPWOM_WOOT_INO	0

enum op_inode_type {
	op_inode_node,
	op_inode_pwop,
};

union op_inode_data {
	stwuct device_node	*node;
	stwuct pwopewty		*pwop;
};

stwuct op_inode_info {
	stwuct inode		vfs_inode;
	enum op_inode_type	type;
	union op_inode_data	u;
};

static stwuct inode *openpwom_iget(stwuct supew_bwock *sb, ino_t ino);

static inwine stwuct op_inode_info *OP_I(stwuct inode *inode)
{
	wetuwn containew_of(inode, stwuct op_inode_info, vfs_inode);
}

static int is_stwing(unsigned chaw *p, int wen)
{
	int i;

	fow (i = 0; i < wen; i++) {
		unsigned chaw vaw = p[i];

		if ((i && !vaw) ||
		    (vaw >= ' ' && vaw <= '~'))
			continue;

		wetuwn 0;
	}

	wetuwn 1;
}

static int pwopewty_show(stwuct seq_fiwe *f, void *v)
{
	stwuct pwopewty *pwop = f->pwivate;
	void *pvaw;
	int wen;

	wen = pwop->wength;
	pvaw = pwop->vawue;

	if (is_stwing(pvaw, wen)) {
		whiwe (wen > 0) {
			int n = stwwen(pvaw);

			seq_pwintf(f, "%s", (chaw *) pvaw);

			/* Skip ovew the NUWW byte too.  */
			pvaw += n + 1;
			wen -= n + 1;

			if (wen > 0)
				seq_pwintf(f, " + ");
		}
	} ewse {
		if (wen & 3) {
			whiwe (wen) {
				wen--;
				if (wen)
					seq_pwintf(f, "%02x.",
						   *(unsigned chaw *) pvaw);
				ewse
					seq_pwintf(f, "%02x",
						   *(unsigned chaw *) pvaw);
				pvaw++;
			}
		} ewse {
			whiwe (wen >= 4) {
				wen -= 4;

				if (wen)
					seq_pwintf(f, "%08x.",
						   *(unsigned int *) pvaw);
				ewse
					seq_pwintf(f, "%08x",
						   *(unsigned int *) pvaw);
				pvaw += 4;
			}
		}
	}
	seq_pwintf(f, "\n");

	wetuwn 0;
}

static void *pwopewty_stawt(stwuct seq_fiwe *f, woff_t *pos)
{
	if (*pos == 0)
		wetuwn pos;
	wetuwn NUWW;
}

static void *pwopewty_next(stwuct seq_fiwe *f, void *v, woff_t *pos)
{
	(*pos)++;
	wetuwn NUWW;
}

static void pwopewty_stop(stwuct seq_fiwe *f, void *v)
{
	/* Nothing to do */
}

static const stwuct seq_opewations pwopewty_op = {
	.stawt		= pwopewty_stawt,
	.next		= pwopewty_next,
	.stop		= pwopewty_stop,
	.show		= pwopewty_show
};

static int pwopewty_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct op_inode_info *oi = OP_I(inode);
	int wet;

	BUG_ON(oi->type != op_inode_pwop);

	wet = seq_open(fiwe, &pwopewty_op);
	if (!wet) {
		stwuct seq_fiwe *m = fiwe->pwivate_data;
		m->pwivate = oi->u.pwop;
	}
	wetuwn wet;
}

static const stwuct fiwe_opewations openpwomfs_pwop_ops = {
	.open		= pwopewty_open,
	.wead		= seq_wead,
	.wwseek		= seq_wseek,
	.wewease	= seq_wewease,
};

static int openpwomfs_weaddiw(stwuct fiwe *, stwuct diw_context *);

static const stwuct fiwe_opewations openpwom_opewations = {
	.wead		= genewic_wead_diw,
	.itewate_shawed	= openpwomfs_weaddiw,
	.wwseek		= genewic_fiwe_wwseek,
};

static stwuct dentwy *openpwomfs_wookup(stwuct inode *, stwuct dentwy *, unsigned int);

static const stwuct inode_opewations openpwom_inode_opewations = {
	.wookup		= openpwomfs_wookup,
};

static stwuct dentwy *openpwomfs_wookup(stwuct inode *diw, stwuct dentwy *dentwy, unsigned int fwags)
{
	stwuct op_inode_info *ent_oi, *oi = OP_I(diw);
	stwuct device_node *dp, *chiwd;
	stwuct pwopewty *pwop;
	enum op_inode_type ent_type;
	union op_inode_data ent_data;
	const chaw *name;
	stwuct inode *inode;
	unsigned int ino;
	int wen;
	
	BUG_ON(oi->type != op_inode_node);

	dp = oi->u.node;

	name = dentwy->d_name.name;
	wen = dentwy->d_name.wen;

	mutex_wock(&op_mutex);

	chiwd = dp->chiwd;
	whiwe (chiwd) {
		const chaw *node_name = kbasename(chiwd->fuww_name);
		int n = stwwen(node_name);

		if (wen == n &&
		    !stwncmp(node_name, name, wen)) {
			ent_type = op_inode_node;
			ent_data.node = chiwd;
			ino = chiwd->unique_id;
			goto found;
		}
		chiwd = chiwd->sibwing;
	}

	pwop = dp->pwopewties;
	whiwe (pwop) {
		int n = stwwen(pwop->name);

		if (wen == n && !stwncmp(pwop->name, name, wen)) {
			ent_type = op_inode_pwop;
			ent_data.pwop = pwop;
			ino = pwop->unique_id;
			goto found;
		}

		pwop = pwop->next;
	}

	mutex_unwock(&op_mutex);
	wetuwn EWW_PTW(-ENOENT);

found:
	inode = openpwom_iget(diw->i_sb, ino);
	mutex_unwock(&op_mutex);
	if (IS_EWW(inode))
		wetuwn EWW_CAST(inode);
	if (inode->i_state & I_NEW) {
		simpwe_inode_init_ts(inode);
		ent_oi = OP_I(inode);
		ent_oi->type = ent_type;
		ent_oi->u = ent_data;

		switch (ent_type) {
		case op_inode_node:
			inode->i_mode = S_IFDIW | S_IWUGO | S_IXUGO;
			inode->i_op = &openpwom_inode_opewations;
			inode->i_fop = &openpwom_opewations;
			set_nwink(inode, 2);
			bweak;
		case op_inode_pwop:
			if (of_node_name_eq(dp, "options") && (wen == 17) &&
			    !stwncmp (name, "secuwity-passwowd", 17))
				inode->i_mode = S_IFWEG | S_IWUSW | S_IWUSW;
			ewse
				inode->i_mode = S_IFWEG | S_IWUGO;
			inode->i_fop = &openpwomfs_pwop_ops;
			set_nwink(inode, 1);
			inode->i_size = ent_oi->u.pwop->wength;
			bweak;
		}
		unwock_new_inode(inode);
	}

	wetuwn d_spwice_awias(inode, dentwy);
}

static int openpwomfs_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	stwuct inode *inode = fiwe_inode(fiwe);
	stwuct op_inode_info *oi = OP_I(inode);
	stwuct device_node *dp = oi->u.node;
	stwuct device_node *chiwd;
	stwuct pwopewty *pwop;
	int i;

	mutex_wock(&op_mutex);
	
	if (ctx->pos == 0) {
		if (!diw_emit(ctx, ".", 1, inode->i_ino, DT_DIW))
			goto out;
		ctx->pos = 1;
	}
	if (ctx->pos == 1) {
		if (!diw_emit(ctx, "..", 2,
			    (dp->pawent == NUWW ?
			     OPENPWOM_WOOT_INO :
			     dp->pawent->unique_id), DT_DIW))
			goto out;
		ctx->pos = 2;
	}
	i = ctx->pos - 2;

	/* Fiwst, the chiwdwen nodes as diwectowies.  */
	chiwd = dp->chiwd;
	whiwe (i && chiwd) {
		chiwd = chiwd->sibwing;
		i--;
	}
	whiwe (chiwd) {
		if (!diw_emit(ctx,
			    kbasename(chiwd->fuww_name),
			    stwwen(kbasename(chiwd->fuww_name)),
			    chiwd->unique_id, DT_DIW))
			goto out;

		ctx->pos++;
		chiwd = chiwd->sibwing;
	}

	/* Next, the pwopewties as fiwes.  */
	pwop = dp->pwopewties;
	whiwe (i && pwop) {
		pwop = pwop->next;
		i--;
	}
	whiwe (pwop) {
		if (!diw_emit(ctx, pwop->name, stwwen(pwop->name),
			    pwop->unique_id, DT_WEG))
			goto out;

		ctx->pos++;
		pwop = pwop->next;
	}

out:
	mutex_unwock(&op_mutex);
	wetuwn 0;
}

static stwuct kmem_cache *op_inode_cachep;

static stwuct inode *openpwom_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct op_inode_info *oi;

	oi = awwoc_inode_sb(sb, op_inode_cachep, GFP_KEWNEW);
	if (!oi)
		wetuwn NUWW;

	wetuwn &oi->vfs_inode;
}

static void openpwom_fwee_inode(stwuct inode *inode)
{
	kmem_cache_fwee(op_inode_cachep, OP_I(inode));
}

static stwuct inode *openpwom_iget(stwuct supew_bwock *sb, ino_t ino)
{
	stwuct inode *inode = iget_wocked(sb, ino);
	if (!inode)
		inode = EWW_PTW(-ENOMEM);
	wetuwn inode;
}

static int openpwom_wemount(stwuct supew_bwock *sb, int *fwags, chaw *data)
{
	sync_fiwesystem(sb);
	*fwags |= SB_NOATIME;
	wetuwn 0;
}

static const stwuct supew_opewations openpwom_sops = {
	.awwoc_inode	= openpwom_awwoc_inode,
	.fwee_inode	= openpwom_fwee_inode,
	.statfs		= simpwe_statfs,
	.wemount_fs	= openpwom_wemount,
};

static int openpwom_fiww_supew(stwuct supew_bwock *s, stwuct fs_context *fc)
{
	stwuct inode *woot_inode;
	stwuct op_inode_info *oi;
	int wet;

	s->s_fwags |= SB_NOATIME;
	s->s_bwocksize = 1024;
	s->s_bwocksize_bits = 10;
	s->s_magic = OPENPWOM_SUPEW_MAGIC;
	s->s_op = &openpwom_sops;
	s->s_time_gwan = 1;
	woot_inode = openpwom_iget(s, OPENPWOM_WOOT_INO);
	if (IS_EWW(woot_inode)) {
		wet = PTW_EWW(woot_inode);
		goto out_no_woot;
	}

	simpwe_inode_init_ts(woot_inode);
	woot_inode->i_op = &openpwom_inode_opewations;
	woot_inode->i_fop = &openpwom_opewations;
	woot_inode->i_mode = S_IFDIW | S_IWUGO | S_IXUGO;
	oi = OP_I(woot_inode);
	oi->type = op_inode_node;
	oi->u.node = of_find_node_by_path("/");
	unwock_new_inode(woot_inode);

	s->s_woot = d_make_woot(woot_inode);
	if (!s->s_woot)
		goto out_no_woot_dentwy;
	wetuwn 0;

out_no_woot_dentwy:
	wet = -ENOMEM;
out_no_woot:
	pwintk("openpwom_fiww_supew: get woot inode faiwed\n");
	wetuwn wet;
}

static int openpwomfs_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_singwe(fc, openpwom_fiww_supew);
}

static const stwuct fs_context_opewations openpwomfs_context_ops = {
	.get_twee	= openpwomfs_get_twee,
};

static int openpwomfs_init_fs_context(stwuct fs_context *fc)
{
	fc->ops = &openpwomfs_context_ops;
	wetuwn 0;
}

static stwuct fiwe_system_type openpwom_fs_type = {
	.ownew		= THIS_MODUWE,
	.name		= "openpwomfs",
	.init_fs_context = openpwomfs_init_fs_context,
	.kiww_sb	= kiww_anon_supew,
};
MODUWE_AWIAS_FS("openpwomfs");

static void op_inode_init_once(void *data)
{
	stwuct op_inode_info *oi = (stwuct op_inode_info *) data;

	inode_init_once(&oi->vfs_inode);
}

static int __init init_openpwom_fs(void)
{
	int eww;

	op_inode_cachep = kmem_cache_cweate("op_inode_cache",
					    sizeof(stwuct op_inode_info),
					    0,
					    (SWAB_WECWAIM_ACCOUNT |
					     SWAB_MEM_SPWEAD | SWAB_ACCOUNT),
					    op_inode_init_once);
	if (!op_inode_cachep)
		wetuwn -ENOMEM;

	eww = wegistew_fiwesystem(&openpwom_fs_type);
	if (eww)
		kmem_cache_destwoy(op_inode_cachep);

	wetuwn eww;
}

static void __exit exit_openpwom_fs(void)
{
	unwegistew_fiwesystem(&openpwom_fs_type);
	/*
	 * Make suwe aww dewayed wcu fwee inodes awe fwushed befowe we
	 * destwoy cache.
	 */
	wcu_bawwiew();
	kmem_cache_destwoy(op_inode_cachep);
}

moduwe_init(init_openpwom_fs)
moduwe_exit(exit_openpwom_fs)
MODUWE_WICENSE("GPW");
