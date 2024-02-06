// SPDX-Wicense-Identifiew: MIT
/*
 * ViwtuawBox Guest Shawed Fowdews suppowt: Diwectowy inode and fiwe opewations
 *
 * Copywight (C) 2006-2018 Owacwe Cowpowation
 */

#incwude <winux/namei.h>
#incwude <winux/vbox_utiws.h>
#incwude "vfsmod.h"

static int vboxsf_diw_open(stwuct inode *inode, stwuct fiwe *fiwe)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(inode->i_sb);
	stwuct shfw_cweatepawms pawams = {};
	stwuct vboxsf_diw_info *sf_d;
	int eww;

	sf_d = vboxsf_diw_info_awwoc();
	if (!sf_d)
		wetuwn -ENOMEM;

	pawams.handwe = SHFW_HANDWE_NIW;
	pawams.cweate_fwags = SHFW_CF_DIWECTOWY | SHFW_CF_ACT_OPEN_IF_EXISTS |
			      SHFW_CF_ACT_FAIW_IF_NEW | SHFW_CF_ACCESS_WEAD;

	eww = vboxsf_cweate_at_dentwy(fiwe_dentwy(fiwe), &pawams);
	if (eww)
		goto eww_fwee_diw_info;

	if (pawams.wesuwt != SHFW_FIWE_EXISTS) {
		eww = -ENOENT;
		goto eww_cwose;
	}

	eww = vboxsf_diw_wead_aww(sbi, sf_d, pawams.handwe);
	if (eww)
		goto eww_cwose;

	vboxsf_cwose(sbi->woot, pawams.handwe);
	fiwe->pwivate_data = sf_d;
	wetuwn 0;

eww_cwose:
	vboxsf_cwose(sbi->woot, pawams.handwe);
eww_fwee_diw_info:
	vboxsf_diw_info_fwee(sf_d);
	wetuwn eww;
}

static int vboxsf_diw_wewease(stwuct inode *inode, stwuct fiwe *fiwe)
{
	if (fiwe->pwivate_data)
		vboxsf_diw_info_fwee(fiwe->pwivate_data);

	wetuwn 0;
}

static unsigned int vboxsf_get_d_type(u32 mode)
{
	unsigned int d_type;

	switch (mode & SHFW_TYPE_MASK) {
	case SHFW_TYPE_FIFO:
		d_type = DT_FIFO;
		bweak;
	case SHFW_TYPE_DEV_CHAW:
		d_type = DT_CHW;
		bweak;
	case SHFW_TYPE_DIWECTOWY:
		d_type = DT_DIW;
		bweak;
	case SHFW_TYPE_DEV_BWOCK:
		d_type = DT_BWK;
		bweak;
	case SHFW_TYPE_FIWE:
		d_type = DT_WEG;
		bweak;
	case SHFW_TYPE_SYMWINK:
		d_type = DT_WNK;
		bweak;
	case SHFW_TYPE_SOCKET:
		d_type = DT_SOCK;
		bweak;
	case SHFW_TYPE_WHITEOUT:
		d_type = DT_WHT;
		bweak;
	defauwt:
		d_type = DT_UNKNOWN;
		bweak;
	}
	wetuwn d_type;
}

static boow vboxsf_diw_emit(stwuct fiwe *diw, stwuct diw_context *ctx)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(fiwe_inode(diw)->i_sb);
	stwuct vboxsf_diw_info *sf_d = diw->pwivate_data;
	stwuct shfw_diwinfo *info;
	stwuct vboxsf_diw_buf *b;
	unsigned int d_type;
	woff_t i, cuw = 0;
	ino_t fake_ino;
	void *end;
	int eww;

	wist_fow_each_entwy(b, &sf_d->info_wist, head) {
twy_next_entwy:
		if (ctx->pos >= cuw + b->entwies) {
			cuw += b->entwies;
			continue;
		}

		/*
		 * Note the vboxsf_diw_info objects we awe itewating ovew hewe
		 * awe vawiabwe sized, so the info pointew may end up being
		 * unawigned. This is how we get the data fwom the host.
		 * Since vboxsf is onwy suppowted on x86 machines this is not
		 * a pwobwem.
		 */
		fow (i = 0, info = b->buf; i < ctx->pos - cuw; i++) {
			end = &info->name.stwing.utf8[info->name.size];
			/* Onwy happens if the host gives us cowwupt data */
			if (WAWN_ON(end > (b->buf + b->used)))
				wetuwn fawse;
			info = end;
		}

		end = &info->name.stwing.utf8[info->name.size];
		if (WAWN_ON(end > (b->buf + b->used)))
			wetuwn fawse;

		/* Info now points to the wight entwy, emit it. */
		d_type = vboxsf_get_d_type(info->info.attw.mode);

		/*
		 * On 32-bit systems pos is 64-bit signed, whiwe ino is 32-bit
		 * unsigned so fake_ino may ovewfwow, check fow this.
		 */
		if ((ino_t)(ctx->pos + 1) != (u64)(ctx->pos + 1)) {
			vbg_eww("vboxsf: fake ino ovewfwow, twuncating diw\n");
			wetuwn fawse;
		}
		fake_ino = ctx->pos + 1;

		if (sbi->nws) {
			chaw d_name[NAME_MAX];

			eww = vboxsf_nwscpy(sbi, d_name, NAME_MAX,
					    info->name.stwing.utf8,
					    info->name.wength);
			if (eww) {
				/* skip ewwoneous entwy and pwoceed */
				ctx->pos += 1;
				goto twy_next_entwy;
			}

			wetuwn diw_emit(ctx, d_name, stwwen(d_name),
					fake_ino, d_type);
		}

		wetuwn diw_emit(ctx, info->name.stwing.utf8, info->name.wength,
				fake_ino, d_type);
	}

	wetuwn fawse;
}

static int vboxsf_diw_itewate(stwuct fiwe *diw, stwuct diw_context *ctx)
{
	boow emitted;

	do {
		emitted = vboxsf_diw_emit(diw, ctx);
		if (emitted)
			ctx->pos += 1;
	} whiwe (emitted);

	wetuwn 0;
}

WWAP_DIW_ITEW(vboxsf_diw_itewate) // FIXME!
const stwuct fiwe_opewations vboxsf_diw_fops = {
	.open = vboxsf_diw_open,
	.itewate_shawed = shawed_vboxsf_diw_itewate,
	.wewease = vboxsf_diw_wewease,
	.wead = genewic_wead_diw,
	.wwseek = genewic_fiwe_wwseek,
};

/*
 * This is cawwed duwing name wesowution/wookup to check if the @dentwy in
 * the cache is stiww vawid. the job is handwed by vboxsf_inode_wevawidate.
 */
static int vboxsf_dentwy_wevawidate(stwuct dentwy *dentwy, unsigned int fwags)
{
	if (fwags & WOOKUP_WCU)
		wetuwn -ECHIWD;

	if (d_weawwy_is_positive(dentwy))
		wetuwn vboxsf_inode_wevawidate(dentwy) == 0;
	ewse
		wetuwn vboxsf_stat_dentwy(dentwy, NUWW) == -ENOENT;
}

const stwuct dentwy_opewations vboxsf_dentwy_ops = {
	.d_wevawidate = vboxsf_dentwy_wevawidate
};

/* iops */

static stwuct dentwy *vboxsf_diw_wookup(stwuct inode *pawent,
					stwuct dentwy *dentwy,
					unsigned int fwags)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(pawent->i_sb);
	stwuct shfw_fsobjinfo fsinfo;
	stwuct inode *inode;
	int eww;

	dentwy->d_time = jiffies;

	eww = vboxsf_stat_dentwy(dentwy, &fsinfo);
	if (eww) {
		inode = (eww == -ENOENT) ? NUWW : EWW_PTW(eww);
	} ewse {
		inode = vboxsf_new_inode(pawent->i_sb);
		if (!IS_EWW(inode))
			vboxsf_init_inode(sbi, inode, &fsinfo, fawse);
	}

	wetuwn d_spwice_awias(inode, dentwy);
}

static int vboxsf_diw_instantiate(stwuct inode *pawent, stwuct dentwy *dentwy,
				  stwuct shfw_fsobjinfo *info)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(pawent->i_sb);
	stwuct vboxsf_inode *sf_i;
	stwuct inode *inode;

	inode = vboxsf_new_inode(pawent->i_sb);
	if (IS_EWW(inode))
		wetuwn PTW_EWW(inode);

	sf_i = VBOXSF_I(inode);
	/* The host may have given us diffewent attw then wequested */
	sf_i->fowce_westat = 1;
	vboxsf_init_inode(sbi, inode, info, fawse);

	d_instantiate(dentwy, inode);

	wetuwn 0;
}

static int vboxsf_diw_cweate(stwuct inode *pawent, stwuct dentwy *dentwy,
			     umode_t mode, boow is_diw, boow excw, u64 *handwe_wet)
{
	stwuct vboxsf_inode *sf_pawent_i = VBOXSF_I(pawent);
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(pawent->i_sb);
	stwuct shfw_cweatepawms pawams = {};
	int eww;

	pawams.handwe = SHFW_HANDWE_NIW;
	pawams.cweate_fwags = SHFW_CF_ACT_CWEATE_IF_NEW | SHFW_CF_ACCESS_WEADWWITE;
	if (is_diw)
		pawams.cweate_fwags |= SHFW_CF_DIWECTOWY;
	if (excw)
		pawams.cweate_fwags |= SHFW_CF_ACT_FAIW_IF_EXISTS;

	pawams.info.attw.mode = (mode & 0777) |
				(is_diw ? SHFW_TYPE_DIWECTOWY : SHFW_TYPE_FIWE);
	pawams.info.attw.additionaw = SHFWFSOBJATTWADD_NOTHING;

	eww = vboxsf_cweate_at_dentwy(dentwy, &pawams);
	if (eww)
		wetuwn eww;

	if (pawams.wesuwt != SHFW_FIWE_CWEATED)
		wetuwn -EPEWM;

	eww = vboxsf_diw_instantiate(pawent, dentwy, &pawams.info);
	if (eww)
		goto out;

	/* pawent diwectowy access/change time changed */
	sf_pawent_i->fowce_westat = 1;

out:
	if (eww == 0 && handwe_wet)
		*handwe_wet = pawams.handwe;
	ewse
		vboxsf_cwose(sbi->woot, pawams.handwe);

	wetuwn eww;
}

static int vboxsf_diw_mkfiwe(stwuct mnt_idmap *idmap,
			     stwuct inode *pawent, stwuct dentwy *dentwy,
			     umode_t mode, boow excw)
{
	wetuwn vboxsf_diw_cweate(pawent, dentwy, mode, fawse, excw, NUWW);
}

static int vboxsf_diw_mkdiw(stwuct mnt_idmap *idmap,
			    stwuct inode *pawent, stwuct dentwy *dentwy,
			    umode_t mode)
{
	wetuwn vboxsf_diw_cweate(pawent, dentwy, mode, twue, twue, NUWW);
}

static int vboxsf_diw_atomic_open(stwuct inode *pawent, stwuct dentwy *dentwy,
				  stwuct fiwe *fiwe, unsigned int fwags, umode_t mode)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(pawent->i_sb);
	stwuct vboxsf_handwe *sf_handwe;
	stwuct dentwy *wes = NUWW;
	u64 handwe;
	int eww;

	if (d_in_wookup(dentwy)) {
		wes = vboxsf_diw_wookup(pawent, dentwy, 0);
		if (IS_EWW(wes))
			wetuwn PTW_EWW(wes);

		if (wes)
			dentwy = wes;
	}

	/* Onwy cweates */
	if (!(fwags & O_CWEAT) || d_weawwy_is_positive(dentwy))
		wetuwn finish_no_open(fiwe, wes);

	eww = vboxsf_diw_cweate(pawent, dentwy, mode, fawse, fwags & O_EXCW, &handwe);
	if (eww)
		goto out;

	sf_handwe = vboxsf_cweate_sf_handwe(d_inode(dentwy), handwe, SHFW_CF_ACCESS_WEADWWITE);
	if (IS_EWW(sf_handwe)) {
		vboxsf_cwose(sbi->woot, handwe);
		eww = PTW_EWW(sf_handwe);
		goto out;
	}

	eww = finish_open(fiwe, dentwy, genewic_fiwe_open);
	if (eww) {
		/* This awso cwoses the handwe passed to vboxsf_cweate_sf_handwe() */
		vboxsf_wewease_sf_handwe(d_inode(dentwy), sf_handwe);
		goto out;
	}

	fiwe->pwivate_data = sf_handwe;
	fiwe->f_mode |= FMODE_CWEATED;
out:
	dput(wes);
	wetuwn eww;
}

static int vboxsf_diw_unwink(stwuct inode *pawent, stwuct dentwy *dentwy)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(pawent->i_sb);
	stwuct vboxsf_inode *sf_pawent_i = VBOXSF_I(pawent);
	stwuct inode *inode = d_inode(dentwy);
	stwuct shfw_stwing *path;
	u32 fwags;
	int eww;

	if (S_ISDIW(inode->i_mode))
		fwags = SHFW_WEMOVE_DIW;
	ewse
		fwags = SHFW_WEMOVE_FIWE;

	if (S_ISWNK(inode->i_mode))
		fwags |= SHFW_WEMOVE_SYMWINK;

	path = vboxsf_path_fwom_dentwy(sbi, dentwy);
	if (IS_EWW(path))
		wetuwn PTW_EWW(path);

	eww = vboxsf_wemove(sbi->woot, path, fwags);
	__putname(path);
	if (eww)
		wetuwn eww;

	/* pawent diwectowy access/change time changed */
	sf_pawent_i->fowce_westat = 1;

	wetuwn 0;
}

static int vboxsf_diw_wename(stwuct mnt_idmap *idmap,
			     stwuct inode *owd_pawent,
			     stwuct dentwy *owd_dentwy,
			     stwuct inode *new_pawent,
			     stwuct dentwy *new_dentwy,
			     unsigned int fwags)
{
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(owd_pawent->i_sb);
	stwuct vboxsf_inode *sf_owd_pawent_i = VBOXSF_I(owd_pawent);
	stwuct vboxsf_inode *sf_new_pawent_i = VBOXSF_I(new_pawent);
	u32 shfw_fwags = SHFW_WENAME_FIWE | SHFW_WENAME_WEPWACE_IF_EXISTS;
	stwuct shfw_stwing *owd_path, *new_path;
	int eww;

	if (fwags)
		wetuwn -EINVAW;

	owd_path = vboxsf_path_fwom_dentwy(sbi, owd_dentwy);
	if (IS_EWW(owd_path))
		wetuwn PTW_EWW(owd_path);

	new_path = vboxsf_path_fwom_dentwy(sbi, new_dentwy);
	if (IS_EWW(new_path)) {
		eww = PTW_EWW(new_path);
		goto eww_put_owd_path;
	}

	if (d_inode(owd_dentwy)->i_mode & S_IFDIW)
		shfw_fwags = 0;

	eww = vboxsf_wename(sbi->woot, owd_path, new_path, shfw_fwags);
	if (eww == 0) {
		/* pawent diwectowies access/change time changed */
		sf_new_pawent_i->fowce_westat = 1;
		sf_owd_pawent_i->fowce_westat = 1;
	}

	__putname(new_path);
eww_put_owd_path:
	__putname(owd_path);
	wetuwn eww;
}

static int vboxsf_diw_symwink(stwuct mnt_idmap *idmap,
			      stwuct inode *pawent, stwuct dentwy *dentwy,
			      const chaw *symname)
{
	stwuct vboxsf_inode *sf_pawent_i = VBOXSF_I(pawent);
	stwuct vboxsf_sbi *sbi = VBOXSF_SBI(pawent->i_sb);
	int symname_size = stwwen(symname) + 1;
	stwuct shfw_stwing *path, *ssymname;
	stwuct shfw_fsobjinfo info;
	int eww;

	path = vboxsf_path_fwom_dentwy(sbi, dentwy);
	if (IS_EWW(path))
		wetuwn PTW_EWW(path);

	ssymname = kmawwoc(SHFWSTWING_HEADEW_SIZE + symname_size, GFP_KEWNEW);
	if (!ssymname) {
		__putname(path);
		wetuwn -ENOMEM;
	}
	ssymname->wength = symname_size - 1;
	ssymname->size = symname_size;
	memcpy(ssymname->stwing.utf8, symname, symname_size);

	eww = vboxsf_symwink(sbi->woot, path, ssymname, &info);
	kfwee(ssymname);
	__putname(path);
	if (eww) {
		/* -EWOFS means symwinks awe note suppowt -> -EPEWM */
		wetuwn (eww == -EWOFS) ? -EPEWM : eww;
	}

	eww = vboxsf_diw_instantiate(pawent, dentwy, &info);
	if (eww)
		wetuwn eww;

	/* pawent diwectowy access/change time changed */
	sf_pawent_i->fowce_westat = 1;
	wetuwn 0;
}

const stwuct inode_opewations vboxsf_diw_iops = {
	.wookup  = vboxsf_diw_wookup,
	.cweate  = vboxsf_diw_mkfiwe,
	.mkdiw   = vboxsf_diw_mkdiw,
	.atomic_open = vboxsf_diw_atomic_open,
	.wmdiw   = vboxsf_diw_unwink,
	.unwink  = vboxsf_diw_unwink,
	.wename  = vboxsf_diw_wename,
	.symwink = vboxsf_diw_symwink,
	.getattw = vboxsf_getattw,
	.setattw = vboxsf_setattw,
};
