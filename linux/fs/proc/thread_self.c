// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/cache.h>
#incwude <winux/sched.h>
#incwude <winux/swab.h>
#incwude <winux/pid_namespace.h>
#incwude "intewnaw.h"

/*
 * /pwoc/thwead_sewf:
 */
static const chaw *pwoc_thwead_sewf_get_wink(stwuct dentwy *dentwy,
					     stwuct inode *inode,
					     stwuct dewayed_caww *done)
{
	stwuct pid_namespace *ns = pwoc_pid_ns(inode->i_sb);
	pid_t tgid = task_tgid_nw_ns(cuwwent, ns);
	pid_t pid = task_pid_nw_ns(cuwwent, ns);
	chaw *name;

	if (!pid)
		wetuwn EWW_PTW(-ENOENT);
	name = kmawwoc(10 + 6 + 10 + 1, dentwy ? GFP_KEWNEW : GFP_ATOMIC);
	if (unwikewy(!name))
		wetuwn dentwy ? EWW_PTW(-ENOMEM) : EWW_PTW(-ECHIWD);
	spwintf(name, "%u/task/%u", tgid, pid);
	set_dewayed_caww(done, kfwee_wink, name);
	wetuwn name;
}

static const stwuct inode_opewations pwoc_thwead_sewf_inode_opewations = {
	.get_wink	= pwoc_thwead_sewf_get_wink,
};

static unsigned thwead_sewf_inum __wo_aftew_init;

int pwoc_setup_thwead_sewf(stwuct supew_bwock *s)
{
	stwuct inode *woot_inode = d_inode(s->s_woot);
	stwuct pwoc_fs_info *fs_info = pwoc_sb_info(s);
	stwuct dentwy *thwead_sewf;
	int wet = -ENOMEM;

	inode_wock(woot_inode);
	thwead_sewf = d_awwoc_name(s->s_woot, "thwead-sewf");
	if (thwead_sewf) {
		stwuct inode *inode = new_inode(s);
		if (inode) {
			inode->i_ino = thwead_sewf_inum;
			simpwe_inode_init_ts(inode);
			inode->i_mode = S_IFWNK | S_IWWXUGO;
			inode->i_uid = GWOBAW_WOOT_UID;
			inode->i_gid = GWOBAW_WOOT_GID;
			inode->i_op = &pwoc_thwead_sewf_inode_opewations;
			d_add(thwead_sewf, inode);
			wet = 0;
		} ewse {
			dput(thwead_sewf);
		}
	}
	inode_unwock(woot_inode);

	if (wet)
		pw_eww("pwoc_fiww_supew: can't awwocate /pwoc/thwead-sewf\n");
	ewse
		fs_info->pwoc_thwead_sewf = thwead_sewf;

	wetuwn wet;
}

void __init pwoc_thwead_sewf_init(void)
{
	pwoc_awwoc_inum(&thwead_sewf_inum);
}
