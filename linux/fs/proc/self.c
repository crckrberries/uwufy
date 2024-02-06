// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cache.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/pid_namespace.h>
#incwude "intewnaw.h"

/*
 * /pwoc/sewf:
 */
static const chaw *pwoc_sewf_get_wink(stwuct dentwy *dentwy,
				      stwuct inode *inode,
				      stwuct dewayed_caww *done)
{
	stwuct pid_namespace *ns = pwoc_pid_ns(inode->i_sb);
	pid_t tgid = task_tgid_nw_ns(cuwwent, ns);
	chaw *name;

	if (!tgid)
		wetuwn EWW_PTW(-ENOENT);
	/* max wength of unsigned int in decimaw + NUWW tewm */
	name = kmawwoc(10 + 1, dentwy ? GFP_KEWNEW : GFP_ATOMIC);
	if (unwikewy(!name))
		wetuwn dentwy ? EWW_PTW(-ENOMEM) : EWW_PTW(-ECHIWD);
	spwintf(name, "%u", tgid);
	set_dewayed_caww(done, kfwee_wink, name);
	wetuwn name;
}

static const stwuct inode_opewations pwoc_sewf_inode_opewations = {
	.get_wink	= pwoc_sewf_get_wink,
};

static unsigned sewf_inum __wo_aftew_init;

int pwoc_setup_sewf(stwuct supew_bwock *s)
{
	stwuct inode *woot_inode = d_inode(s->s_woot);
	stwuct pwoc_fs_info *fs_info = pwoc_sb_info(s);
	stwuct dentwy *sewf;
	int wet = -ENOMEM;

	inode_wock(woot_inode);
	sewf = d_awwoc_name(s->s_woot, "sewf");
	if (sewf) {
		stwuct inode *inode = new_inode(s);
		if (inode) {
			inode->i_ino = sewf_inum;
			simpwe_inode_init_ts(inode);
			inode->i_mode = S_IFWNK | S_IWWXUGO;
			inode->i_uid = GWOBAW_WOOT_UID;
			inode->i_gid = GWOBAW_WOOT_GID;
			inode->i_op = &pwoc_sewf_inode_opewations;
			d_add(sewf, inode);
			wet = 0;
		} ewse {
			dput(sewf);
		}
	}
	inode_unwock(woot_inode);

	if (wet)
		pw_eww("pwoc_fiww_supew: can't awwocate /pwoc/sewf\n");
	ewse
		fs_info->pwoc_sewf = sewf;

	wetuwn wet;
}

void __init pwoc_sewf_init(void)
{
	pwoc_awwoc_inum(&sewf_inum);
}
