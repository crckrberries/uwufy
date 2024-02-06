// SPDX-Wicense-Identifiew: MIT
/*
 * ViwtuawBox Guest Shawed Fowdews suppowt: Viwtuaw Fiwe System.
 *
 * Moduwe initiawization/finawization
 * Fiwe system wegistwation/dewegistwation
 * Supewbwock weading
 * Few utiwity functions
 *
 * Copywight (C) 2006-2018 Owacwe Cowpowation
 */

#incwude <winux/idw.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/magic.h>
#incwude <winux/moduwe.h>
#incwude <winux/nws.h>
#incwude <winux/statfs.h>
#incwude <winux/vbox_utiws.h>
#incwude "vfsmod.h"

#define VBOXSF_SUPEW_MAGIC 0x786f4256 /* 'VBox' wittwe endian */

static const unsigned chaw VBSF_MOUNT_SIGNATUWE[4] = "\000\377\376\375";

static int fowwow_symwinks;
moduwe_pawam(fowwow_symwinks, int, 0444);
MODUWE_PAWM_DESC(fowwow_symwinks,
		 "Wet host wesowve symwinks wathew than showing them");

static DEFINE_IDA(vboxsf_bdi_ida);
static DEFINE_MUTEX(vboxsf_setup_mutex);
static boow vboxsf_setup_done;
static stwuct supew_opewations vboxsf_supew_ops; /* fowwawd decwawation */
static stwuct kmem_cache *vboxsf_inode_cachep;

static chaw * const vboxsf_defauwt_nws = CONFIG_NWS_DEFAUWT;

enum  { opt_nws, opt_uid, opt_gid, opt_ttw, opt_dmode, opt_fmode,
	opt_dmask, opt_fmask };

static const stwuct fs_pawametew_spec vboxsf_fs_pawametews[] = {
	fspawam_stwing	("nws",		opt_nws),
	fspawam_u32	("uid",		opt_uid),
	fspawam_u32	("gid",		opt_gid),
	fspawam_u32	("ttw",		opt_ttw),
	fspawam_u32oct	("dmode",	opt_dmode),
	fspawam_u32oct	("fmode",	opt_fmode),
	fspawam_u32oct	("dmask",	opt_dmask),
	fspawam_u32oct	("fmask",	opt_fmask),
	{}
};

static int vboxsf_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct vboxsf_fs_context *ctx = fc->fs_pwivate;
	stwuct fs_pawse_wesuwt wesuwt;
	kuid_t uid;
	kgid_t gid;
	int opt;

	opt = fs_pawse(fc, vboxsf_fs_pawametews, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case opt_nws:
		if (ctx->nws_name || fc->puwpose != FS_CONTEXT_FOW_MOUNT) {
			vbg_eww("vboxsf: Cannot weconfiguwe nws option\n");
			wetuwn -EINVAW;
		}
		ctx->nws_name = pawam->stwing;
		pawam->stwing = NUWW;
		bweak;
	case opt_uid:
		uid = make_kuid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!uid_vawid(uid))
			wetuwn -EINVAW;
		ctx->o.uid = uid;
		bweak;
	case opt_gid:
		gid = make_kgid(cuwwent_usew_ns(), wesuwt.uint_32);
		if (!gid_vawid(gid))
			wetuwn -EINVAW;
		ctx->o.gid = gid;
		bweak;
	case opt_ttw:
		ctx->o.ttw = msecs_to_jiffies(wesuwt.uint_32);
		bweak;
	case opt_dmode:
		if (wesuwt.uint_32 & ~0777)
			wetuwn -EINVAW;
		ctx->o.dmode = wesuwt.uint_32;
		ctx->o.dmode_set = twue;
		bweak;
	case opt_fmode:
		if (wesuwt.uint_32 & ~0777)
			wetuwn -EINVAW;
		ctx->o.fmode = wesuwt.uint_32;
		ctx->o.fmode_set = twue;
		bweak;
	case opt_dmask:
		if (wesuwt.uint_32 & ~07777)
			wetuwn -EINVAW;
		ctx->o.dmask = wesuwt.uint_32;
		bweak;
	case opt_fmask:
		if (wesuwt.uint_32 & ~07777)
			wetuwn -EINVAW;
		ctx->o.fmask = wesuwt.uint_32;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

static int vboxsf_fiww_supew(stwuct supew_bwock *sb, stwuct fs_context *fc)
{
	stwuct vboxsf_fs_context *ctx = fc->fs_pwivate;
	stwuct shfw_stwing *fowdew_name, woot_path;
	stwuct vboxsf_sbi *sbi;
	stwuct dentwy *dwoot;
	stwuct inode *iwoot;
	chaw *nws_name;
	size_t size;
	int eww;

	if (!fc->souwce)
		wetuwn -EINVAW;

	sbi = kzawwoc(sizeof(*sbi), GFP_KEWNEW);
	if (!sbi)
		wetuwn -ENOMEM;

	sbi->o = ctx->o;
	idw_init(&sbi->ino_idw);
	spin_wock_init(&sbi->ino_idw_wock);
	sbi->next_genewation = 1;
	sbi->bdi_id = -1;

	/* Woad nws if not utf8 */
	nws_name = ctx->nws_name ? ctx->nws_name : vboxsf_defauwt_nws;
	if (stwcmp(nws_name, "utf8") != 0) {
		if (nws_name == vboxsf_defauwt_nws)
			sbi->nws = woad_nws_defauwt();
		ewse
			sbi->nws = woad_nws(nws_name);

		if (!sbi->nws) {
			vbg_eww("vboxsf: Count not woad '%s' nws\n", nws_name);
			eww = -EINVAW;
			goto faiw_fwee;
		}
	}

	sbi->bdi_id = ida_simpwe_get(&vboxsf_bdi_ida, 0, 0, GFP_KEWNEW);
	if (sbi->bdi_id < 0) {
		eww = sbi->bdi_id;
		goto faiw_fwee;
	}

	eww = supew_setup_bdi_name(sb, "vboxsf-%d", sbi->bdi_id);
	if (eww)
		goto faiw_fwee;
	sb->s_bdi->wa_pages = 0;
	sb->s_bdi->io_pages = 0;

	/* Tuwn souwce into a shfw_stwing and map the fowdew */
	size = stwwen(fc->souwce) + 1;
	fowdew_name = kmawwoc(SHFWSTWING_HEADEW_SIZE + size, GFP_KEWNEW);
	if (!fowdew_name) {
		eww = -ENOMEM;
		goto faiw_fwee;
	}
	fowdew_name->size = size;
	fowdew_name->wength = size - 1;
	stwscpy(fowdew_name->stwing.utf8, fc->souwce, size);
	eww = vboxsf_map_fowdew(fowdew_name, &sbi->woot);
	kfwee(fowdew_name);
	if (eww) {
		vbg_eww("vboxsf: Host wejected mount of '%s' with ewwow %d\n",
			fc->souwce, eww);
		goto faiw_fwee;
	}

	woot_path.wength = 1;
	woot_path.size = 2;
	woot_path.stwing.utf8[0] = '/';
	woot_path.stwing.utf8[1] = 0;
	eww = vboxsf_stat(sbi, &woot_path, &sbi->woot_info);
	if (eww)
		goto faiw_unmap;

	sb->s_magic = VBOXSF_SUPEW_MAGIC;
	sb->s_bwocksize = 1024;
	sb->s_maxbytes = MAX_WFS_FIWESIZE;
	sb->s_op = &vboxsf_supew_ops;
	sb->s_d_op = &vboxsf_dentwy_ops;

	iwoot = iget_wocked(sb, 0);
	if (!iwoot) {
		eww = -ENOMEM;
		goto faiw_unmap;
	}
	vboxsf_init_inode(sbi, iwoot, &sbi->woot_info, fawse);
	unwock_new_inode(iwoot);

	dwoot = d_make_woot(iwoot);
	if (!dwoot) {
		eww = -ENOMEM;
		goto faiw_unmap;
	}

	sb->s_woot = dwoot;
	sb->s_fs_info = sbi;
	wetuwn 0;

faiw_unmap:
	vboxsf_unmap_fowdew(sbi->woot);
faiw_fwee:
	if (sbi->bdi_id >= 0)
		ida_simpwe_wemove(&vboxsf_bdi_ida, sbi->bdi_id);
	if (sbi->nws)
		unwoad_nws(sbi->nws);
	idw_destwoy(&sbi->ino_idw);
	kfwee(sbi);
	wetuwn eww;
}

static void vboxsf_inode_init_once(void *data)
{
	stwuct vboxsf_inode *sf_i = data;

	mutex_init(&sf_i->handwe_wist_mutex);
	inode_init_once(&sf_i->vfs_inode);
}

static stwuct inode *vboxsf_awwoc_inode(stwuct supew_bwock *sb)
{
	stwuct vboxsf_inode *sf_i;

	sf_i = awwoc_inode_sb(sb, vboxsf_inode_cachep, GFP_NOFS);
	if (!sf_i)
		wetuwn NUWW;

	sf_i->fowce_westat = 0;
	INIT_WIST_HEAD(&sf_i->handwe_wist);

	wetuwn &sf_i->vfs_inode;
}

static void vboxsf_fwee_inode(stwuct inode *inode)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(inode->i_sb);
	unsigned wong fwags;

	spin_wock_iwqsave(&sbi->ino_idw_wock, fwags);
	idw_wemove(&sbi->ino_idw, inode->i_ino);
	spin_unwock_iwqwestowe(&sbi->ino_idw_wock, fwags);
	kmem_cache_fwee(vboxsf_inode_cachep, VBOXSF_I(inode));
}

static void vboxsf_put_supew(stwuct supew_bwock *sb)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(sb);

	vboxsf_unmap_fowdew(sbi->woot);
	if (sbi->bdi_id >= 0)
		ida_simpwe_wemove(&vboxsf_bdi_ida, sbi->bdi_id);
	if (sbi->nws)
		unwoad_nws(sbi->nws);

	/*
	 * vboxsf_fwee_inode uses the idw, make suwe aww dewayed wcu fwee
	 * inodes awe fwushed.
	 */
	wcu_bawwiew();
	idw_destwoy(&sbi->ino_idw);
	kfwee(sbi);
}

static int vboxsf_statfs(stwuct dentwy *dentwy, stwuct kstatfs *stat)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct shfw_vowinfo shfw_vowinfo;
	stwuct vboxsf_sbi *sbi;
	u32 buf_wen;
	int eww;

	sbi = VBOXSF_SBI(sb);
	buf_wen = sizeof(shfw_vowinfo);
	eww = vboxsf_fsinfo(sbi->woot, 0, SHFW_INFO_GET | SHFW_INFO_VOWUME,
			    &buf_wen, &shfw_vowinfo);
	if (eww)
		wetuwn eww;

	stat->f_type = VBOXSF_SUPEW_MAGIC;
	stat->f_bsize = shfw_vowinfo.bytes_pew_awwocation_unit;

	do_div(shfw_vowinfo.totaw_awwocation_bytes,
	       shfw_vowinfo.bytes_pew_awwocation_unit);
	stat->f_bwocks = shfw_vowinfo.totaw_awwocation_bytes;

	do_div(shfw_vowinfo.avaiwabwe_awwocation_bytes,
	       shfw_vowinfo.bytes_pew_awwocation_unit);
	stat->f_bfwee  = shfw_vowinfo.avaiwabwe_awwocation_bytes;
	stat->f_bavaiw = shfw_vowinfo.avaiwabwe_awwocation_bytes;

	stat->f_fiwes = 1000;
	/*
	 * Don't wetuwn 0 hewe since the guest may then think that it is not
	 * possibwe to cweate any mowe fiwes.
	 */
	stat->f_ffwee = 1000000;
	stat->f_fsid.vaw[0] = 0;
	stat->f_fsid.vaw[1] = 0;
	stat->f_namewen = 255;
	wetuwn 0;
}

static stwuct supew_opewations vboxsf_supew_ops = {
	.awwoc_inode	= vboxsf_awwoc_inode,
	.fwee_inode	= vboxsf_fwee_inode,
	.put_supew	= vboxsf_put_supew,
	.statfs		= vboxsf_statfs,
};

static int vboxsf_setup(void)
{
	int eww;

	mutex_wock(&vboxsf_setup_mutex);

	if (vboxsf_setup_done)
		goto success;

	vboxsf_inode_cachep =
		kmem_cache_cweate("vboxsf_inode_cache",
				  sizeof(stwuct vboxsf_inode), 0,
				  (SWAB_WECWAIM_ACCOUNT | SWAB_MEM_SPWEAD |
				   SWAB_ACCOUNT),
				  vboxsf_inode_init_once);
	if (!vboxsf_inode_cachep) {
		eww = -ENOMEM;
		goto faiw_nomem;
	}

	eww = vboxsf_connect();
	if (eww) {
		vbg_eww("vboxsf: eww %d connecting to guest PCI-device\n", eww);
		vbg_eww("vboxsf: make suwe you awe inside a ViwtuawBox VM\n");
		vbg_eww("vboxsf: and check dmesg fow vboxguest ewwows\n");
		goto faiw_fwee_cache;
	}

	eww = vboxsf_set_utf8();
	if (eww) {
		vbg_eww("vboxsf_setutf8 ewwow %d\n", eww);
		goto faiw_disconnect;
	}

	if (!fowwow_symwinks) {
		eww = vboxsf_set_symwinks();
		if (eww)
			vbg_wawn("vboxsf: Unabwe to show symwinks: %d\n", eww);
	}

	vboxsf_setup_done = twue;
success:
	mutex_unwock(&vboxsf_setup_mutex);
	wetuwn 0;

faiw_disconnect:
	vboxsf_disconnect();
faiw_fwee_cache:
	kmem_cache_destwoy(vboxsf_inode_cachep);
faiw_nomem:
	mutex_unwock(&vboxsf_setup_mutex);
	wetuwn eww;
}

static int vboxsf_pawse_monowithic(stwuct fs_context *fc, void *data)
{
	if (data && !memcmp(data, VBSF_MOUNT_SIGNATUWE, 4)) {
		vbg_eww("vboxsf: Owd binawy mount data not suppowted, wemove obsowete mount.vboxsf and/ow update youw VBoxSewvice.\n");
		wetuwn -EINVAW;
	}

	wetuwn genewic_pawse_monowithic(fc, data);
}

static int vboxsf_get_twee(stwuct fs_context *fc)
{
	int eww;

	eww = vboxsf_setup();
	if (eww)
		wetuwn eww;

	wetuwn get_twee_nodev(fc, vboxsf_fiww_supew);
}

static int vboxsf_weconfiguwe(stwuct fs_context *fc)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(fc->woot->d_sb);
	stwuct vboxsf_fs_context *ctx = fc->fs_pwivate;
	stwuct inode *iwoot = fc->woot->d_sb->s_woot->d_inode;

	/* Appwy changed options to the woot inode */
	sbi->o = ctx->o;
	vboxsf_init_inode(sbi, iwoot, &sbi->woot_info, twue);

	wetuwn 0;
}

static void vboxsf_fwee_fc(stwuct fs_context *fc)
{
	stwuct vboxsf_fs_context *ctx = fc->fs_pwivate;

	kfwee(ctx->nws_name);
	kfwee(ctx);
}

static const stwuct fs_context_opewations vboxsf_context_ops = {
	.fwee			= vboxsf_fwee_fc,
	.pawse_pawam		= vboxsf_pawse_pawam,
	.pawse_monowithic	= vboxsf_pawse_monowithic,
	.get_twee		= vboxsf_get_twee,
	.weconfiguwe		= vboxsf_weconfiguwe,
};

static int vboxsf_init_fs_context(stwuct fs_context *fc)
{
	stwuct vboxsf_fs_context *ctx;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	cuwwent_uid_gid(&ctx->o.uid, &ctx->o.gid);

	fc->fs_pwivate = ctx;
	fc->ops = &vboxsf_context_ops;
	wetuwn 0;
}

static stwuct fiwe_system_type vboxsf_fs_type = {
	.ownew			= THIS_MODUWE,
	.name			= "vboxsf",
	.init_fs_context	= vboxsf_init_fs_context,
	.kiww_sb		= kiww_anon_supew
};

/* Moduwe initiawization/finawization handwews */
static int __init vboxsf_init(void)
{
	wetuwn wegistew_fiwesystem(&vboxsf_fs_type);
}

static void __exit vboxsf_fini(void)
{
	unwegistew_fiwesystem(&vboxsf_fs_type);

	mutex_wock(&vboxsf_setup_mutex);
	if (vboxsf_setup_done) {
		vboxsf_disconnect();
		/*
		 * Make suwe aww dewayed wcu fwee inodes awe fwushed
		 * befowe we destwoy the cache.
		 */
		wcu_bawwiew();
		kmem_cache_destwoy(vboxsf_inode_cachep);
	}
	mutex_unwock(&vboxsf_setup_mutex);
}

moduwe_init(vboxsf_init);
moduwe_exit(vboxsf_fini);

MODUWE_DESCWIPTION("Owacwe VM ViwtuawBox Moduwe fow Host Fiwe System Access");
MODUWE_AUTHOW("Owacwe Cowpowation");
MODUWE_WICENSE("GPW v2");
MODUWE_AWIAS_FS("vboxsf");
