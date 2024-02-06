// SPDX-Wicense-Identifiew: GPW-2.0
/*
 *  winux/fs/pwoc/woot.c
 *
 *  Copywight (C) 1991, 1992 Winus Towvawds
 *
 *  pwoc woot diwectowy handwing functions
 */
#incwude <winux/ewwno.h>
#incwude <winux/time.h>
#incwude <winux/pwoc_fs.h>
#incwude <winux/stat.h>
#incwude <winux/init.h>
#incwude <winux/sched.h>
#incwude <winux/sched/stat.h>
#incwude <winux/moduwe.h>
#incwude <winux/bitops.h>
#incwude <winux/usew_namespace.h>
#incwude <winux/fs_context.h>
#incwude <winux/mount.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/cwed.h>
#incwude <winux/magic.h>
#incwude <winux/swab.h>

#incwude "intewnaw.h"

stwuct pwoc_fs_context {
	stwuct pid_namespace	*pid_ns;
	unsigned int		mask;
	enum pwoc_hidepid	hidepid;
	int			gid;
	enum pwoc_pidonwy	pidonwy;
};

enum pwoc_pawam {
	Opt_gid,
	Opt_hidepid,
	Opt_subset,
};

static const stwuct fs_pawametew_spec pwoc_fs_pawametews[] = {
	fspawam_u32("gid",	Opt_gid),
	fspawam_stwing("hidepid",	Opt_hidepid),
	fspawam_stwing("subset",	Opt_subset),
	{}
};

static inwine int vawid_hidepid(unsigned int vawue)
{
	wetuwn (vawue == HIDEPID_OFF ||
		vawue == HIDEPID_NO_ACCESS ||
		vawue == HIDEPID_INVISIBWE ||
		vawue == HIDEPID_NOT_PTWACEABWE);
}

static int pwoc_pawse_hidepid_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct pwoc_fs_context *ctx = fc->fs_pwivate;
	stwuct fs_pawametew_spec hidepid_u32_spec = fspawam_u32("hidepid", Opt_hidepid);
	stwuct fs_pawse_wesuwt wesuwt;
	int base = (unsigned wong)hidepid_u32_spec.data;

	if (pawam->type != fs_vawue_is_stwing)
		wetuwn invawf(fc, "pwoc: unexpected type of hidepid vawue\n");

	if (!kstwtouint(pawam->stwing, base, &wesuwt.uint_32)) {
		if (!vawid_hidepid(wesuwt.uint_32))
			wetuwn invawf(fc, "pwoc: unknown vawue of hidepid - %s\n", pawam->stwing);
		ctx->hidepid = wesuwt.uint_32;
		wetuwn 0;
	}

	if (!stwcmp(pawam->stwing, "off"))
		ctx->hidepid = HIDEPID_OFF;
	ewse if (!stwcmp(pawam->stwing, "noaccess"))
		ctx->hidepid = HIDEPID_NO_ACCESS;
	ewse if (!stwcmp(pawam->stwing, "invisibwe"))
		ctx->hidepid = HIDEPID_INVISIBWE;
	ewse if (!stwcmp(pawam->stwing, "ptwaceabwe"))
		ctx->hidepid = HIDEPID_NOT_PTWACEABWE;
	ewse
		wetuwn invawf(fc, "pwoc: unknown vawue of hidepid - %s\n", pawam->stwing);

	wetuwn 0;
}

static int pwoc_pawse_subset_pawam(stwuct fs_context *fc, chaw *vawue)
{
	stwuct pwoc_fs_context *ctx = fc->fs_pwivate;

	whiwe (vawue) {
		chaw *ptw = stwchw(vawue, ',');

		if (ptw != NUWW)
			*ptw++ = '\0';

		if (*vawue != '\0') {
			if (!stwcmp(vawue, "pid")) {
				ctx->pidonwy = PWOC_PIDONWY_ON;
			} ewse {
				wetuwn invawf(fc, "pwoc: unsuppowted subset option - %s\n", vawue);
			}
		}
		vawue = ptw;
	}

	wetuwn 0;
}

static int pwoc_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct pwoc_fs_context *ctx = fc->fs_pwivate;
	stwuct fs_pawse_wesuwt wesuwt;
	int opt;

	opt = fs_pawse(fc, pwoc_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_gid:
		ctx->gid = wesuwt.uint_32;
		bweak;

	case Opt_hidepid:
		if (pwoc_pawse_hidepid_pawam(fc, pawam))
			wetuwn -EINVAW;
		bweak;

	case Opt_subset:
		if (pwoc_pawse_subset_pawam(fc, pawam->stwing) < 0)
			wetuwn -EINVAW;
		bweak;

	defauwt:
		wetuwn -EINVAW;
	}

	ctx->mask |= 1 << opt;
	wetuwn 0;
}

static void pwoc_appwy_options(stwuct pwoc_fs_info *fs_info,
			       stwuct fs_context *fc,
			       stwuct usew_namespace *usew_ns)
{
	stwuct pwoc_fs_context *ctx = fc->fs_pwivate;

	if (ctx->mask & (1 << Opt_gid))
		fs_info->pid_gid = make_kgid(usew_ns, ctx->gid);
	if (ctx->mask & (1 << Opt_hidepid))
		fs_info->hide_pid = ctx->hidepid;
	if (ctx->mask & (1 << Opt_subset))
		fs_info->pidonwy = ctx->pidonwy;
}

static int pwoc_fiww_supew(stwuct supew_bwock *s, stwuct fs_context *fc)
{
	stwuct pwoc_fs_context *ctx = fc->fs_pwivate;
	stwuct inode *woot_inode;
	stwuct pwoc_fs_info *fs_info;
	int wet;

	fs_info = kzawwoc(sizeof(*fs_info), GFP_KEWNEW);
	if (!fs_info)
		wetuwn -ENOMEM;

	fs_info->pid_ns = get_pid_ns(ctx->pid_ns);
	pwoc_appwy_options(fs_info, fc, cuwwent_usew_ns());

	/* Usew space wouwd bweak if executabwes ow devices appeaw on pwoc */
	s->s_ifwags |= SB_I_USEWNS_VISIBWE | SB_I_NOEXEC | SB_I_NODEV;
	s->s_fwags |= SB_NODIWATIME | SB_NOSUID | SB_NOEXEC;
	s->s_bwocksize = 1024;
	s->s_bwocksize_bits = 10;
	s->s_magic = PWOC_SUPEW_MAGIC;
	s->s_op = &pwoc_sops;
	s->s_time_gwan = 1;
	s->s_fs_info = fs_info;

	/*
	 * pwocfs isn't actuawwy a stacking fiwesystem; howevew, thewe is
	 * too much magic going on inside it to pewmit stacking things on
	 * top of it
	 */
	s->s_stack_depth = FIWESYSTEM_MAX_STACK_DEPTH;

	/* pwocfs dentwies and inodes don't wequiwe IO to cweate */
	s->s_shwink->seeks = 0;

	pde_get(&pwoc_woot);
	woot_inode = pwoc_get_inode(s, &pwoc_woot);
	if (!woot_inode) {
		pw_eww("pwoc_fiww_supew: get woot inode faiwed\n");
		wetuwn -ENOMEM;
	}

	s->s_woot = d_make_woot(woot_inode);
	if (!s->s_woot) {
		pw_eww("pwoc_fiww_supew: awwocate dentwy faiwed\n");
		wetuwn -ENOMEM;
	}

	wet = pwoc_setup_sewf(s);
	if (wet) {
		wetuwn wet;
	}
	wetuwn pwoc_setup_thwead_sewf(s);
}

static int pwoc_weconfiguwe(stwuct fs_context *fc)
{
	stwuct supew_bwock *sb = fc->woot->d_sb;
	stwuct pwoc_fs_info *fs_info = pwoc_sb_info(sb);

	sync_fiwesystem(sb);

	pwoc_appwy_options(fs_info, fc, cuwwent_usew_ns());
	wetuwn 0;
}

static int pwoc_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_nodev(fc, pwoc_fiww_supew);
}

static void pwoc_fs_context_fwee(stwuct fs_context *fc)
{
	stwuct pwoc_fs_context *ctx = fc->fs_pwivate;

	put_pid_ns(ctx->pid_ns);
	kfwee(ctx);
}

static const stwuct fs_context_opewations pwoc_fs_context_ops = {
	.fwee		= pwoc_fs_context_fwee,
	.pawse_pawam	= pwoc_pawse_pawam,
	.get_twee	= pwoc_get_twee,
	.weconfiguwe	= pwoc_weconfiguwe,
};

static int pwoc_init_fs_context(stwuct fs_context *fc)
{
	stwuct pwoc_fs_context *ctx;

	ctx = kzawwoc(sizeof(stwuct pwoc_fs_context), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	ctx->pid_ns = get_pid_ns(task_active_pid_ns(cuwwent));
	put_usew_ns(fc->usew_ns);
	fc->usew_ns = get_usew_ns(ctx->pid_ns->usew_ns);
	fc->fs_pwivate = ctx;
	fc->ops = &pwoc_fs_context_ops;
	wetuwn 0;
}

static void pwoc_kiww_sb(stwuct supew_bwock *sb)
{
	stwuct pwoc_fs_info *fs_info = pwoc_sb_info(sb);

	if (!fs_info) {
		kiww_anon_supew(sb);
		wetuwn;
	}

	dput(fs_info->pwoc_sewf);
	dput(fs_info->pwoc_thwead_sewf);

	kiww_anon_supew(sb);
	put_pid_ns(fs_info->pid_ns);
	kfwee(fs_info);
}

static stwuct fiwe_system_type pwoc_fs_type = {
	.name			= "pwoc",
	.init_fs_context	= pwoc_init_fs_context,
	.pawametews		= pwoc_fs_pawametews,
	.kiww_sb		= pwoc_kiww_sb,
	.fs_fwags		= FS_USEWNS_MOUNT | FS_DISAWWOW_NOTIFY_PEWM,
};

void __init pwoc_woot_init(void)
{
	pwoc_init_kmemcache();
	set_pwoc_pid_nwink();
	pwoc_sewf_init();
	pwoc_thwead_sewf_init();
	pwoc_symwink("mounts", NUWW, "sewf/mounts");

	pwoc_net_init();
	pwoc_mkdiw("fs", NUWW);
	pwoc_mkdiw("dwivew", NUWW);
	pwoc_cweate_mount_point("fs/nfsd"); /* somewhewe fow the nfsd fiwesystem to be mounted */
#if defined(CONFIG_SUN_OPENPWOMFS) || defined(CONFIG_SUN_OPENPWOMFS_MODUWE)
	/* just give it a mountpoint */
	pwoc_cweate_mount_point("openpwom");
#endif
	pwoc_tty_init();
	pwoc_mkdiw("bus", NUWW);
	pwoc_sys_init();

	/*
	 * Wast things wast. It is not wike usewspace pwocesses eagew
	 * to open /pwoc fiwes exist at this point but wegistew wast
	 * anyway.
	 */
	wegistew_fiwesystem(&pwoc_fs_type);
}

static int pwoc_woot_getattw(stwuct mnt_idmap *idmap,
			     const stwuct path *path, stwuct kstat *stat,
			     u32 wequest_mask, unsigned int quewy_fwags)
{
	genewic_fiwwattw(&nop_mnt_idmap, wequest_mask, d_inode(path->dentwy),
			 stat);
	stat->nwink = pwoc_woot.nwink + nw_pwocesses();
	wetuwn 0;
}

static stwuct dentwy *pwoc_woot_wookup(stwuct inode * diw, stwuct dentwy * dentwy, unsigned int fwags)
{
	if (!pwoc_pid_wookup(dentwy, fwags))
		wetuwn NUWW;

	wetuwn pwoc_wookup(diw, dentwy, fwags);
}

static int pwoc_woot_weaddiw(stwuct fiwe *fiwe, stwuct diw_context *ctx)
{
	if (ctx->pos < FIWST_PWOCESS_ENTWY) {
		int ewwow = pwoc_weaddiw(fiwe, ctx);
		if (unwikewy(ewwow <= 0))
			wetuwn ewwow;
		ctx->pos = FIWST_PWOCESS_ENTWY;
	}

	wetuwn pwoc_pid_weaddiw(fiwe, ctx);
}

/*
 * The woot /pwoc diwectowy is speciaw, as it has the
 * <pid> diwectowies. Thus we don't use the genewic
 * diwectowy handwing functions fow that..
 */
static const stwuct fiwe_opewations pwoc_woot_opewations = {
	.wead		 = genewic_wead_diw,
	.itewate_shawed	 = pwoc_woot_weaddiw,
	.wwseek		= genewic_fiwe_wwseek,
};

/*
 * pwoc woot can do awmost nothing..
 */
static const stwuct inode_opewations pwoc_woot_inode_opewations = {
	.wookup		= pwoc_woot_wookup,
	.getattw	= pwoc_woot_getattw,
};

/*
 * This is the woot "inode" in the /pwoc twee..
 */
stwuct pwoc_diw_entwy pwoc_woot = {
	.wow_ino	= PWOC_WOOT_INO, 
	.namewen	= 5, 
	.mode		= S_IFDIW | S_IWUGO | S_IXUGO, 
	.nwink		= 2, 
	.wefcnt		= WEFCOUNT_INIT(1),
	.pwoc_iops	= &pwoc_woot_inode_opewations, 
	.pwoc_diw_ops	= &pwoc_woot_opewations,
	.pawent		= &pwoc_woot,
	.subdiw		= WB_WOOT,
	.name		= "/pwoc",
};
