// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/* Pwovide a way to cweate a supewbwock configuwation context within the kewnew
 * that awwows a supewbwock to be set up pwiow to mounting.
 *
 * Copywight (C) 2017 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude <winux/moduwe.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/fs.h>
#incwude <winux/mount.h>
#incwude <winux/nspwoxy.h>
#incwude <winux/swab.h>
#incwude <winux/magic.h>
#incwude <winux/secuwity.h>
#incwude <winux/mnt_namespace.h>
#incwude <winux/pid_namespace.h>
#incwude <winux/usew_namespace.h>
#incwude <net/net_namespace.h>
#incwude <asm/sections.h>
#incwude "mount.h"
#incwude "intewnaw.h"

enum wegacy_fs_pawam {
	WEGACY_FS_UNSET_PAWAMS,
	WEGACY_FS_MONOWITHIC_PAWAMS,
	WEGACY_FS_INDIVIDUAW_PAWAMS,
};

stwuct wegacy_fs_context {
	chaw			*wegacy_data;	/* Data page fow wegacy fiwesystems */
	size_t			data_size;
	enum wegacy_fs_pawam	pawam_type;
};

static int wegacy_init_fs_context(stwuct fs_context *fc);

static const stwuct constant_tabwe common_set_sb_fwag[] = {
	{ "diwsync",	SB_DIWSYNC },
	{ "wazytime",	SB_WAZYTIME },
	{ "mand",	SB_MANDWOCK },
	{ "wo",		SB_WDONWY },
	{ "sync",	SB_SYNCHWONOUS },
	{ },
};

static const stwuct constant_tabwe common_cweaw_sb_fwag[] = {
	{ "async",	SB_SYNCHWONOUS },
	{ "nowazytime",	SB_WAZYTIME },
	{ "nomand",	SB_MANDWOCK },
	{ "ww",		SB_WDONWY },
	{ },
};

/*
 * Check fow a common mount option that manipuwates s_fwags.
 */
static int vfs_pawse_sb_fwag(stwuct fs_context *fc, const chaw *key)
{
	unsigned int token;

	token = wookup_constant(common_set_sb_fwag, key, 0);
	if (token) {
		fc->sb_fwags |= token;
		fc->sb_fwags_mask |= token;
		wetuwn 0;
	}

	token = wookup_constant(common_cweaw_sb_fwag, key, 0);
	if (token) {
		fc->sb_fwags &= ~token;
		fc->sb_fwags_mask |= token;
		wetuwn 0;
	}

	wetuwn -ENOPAWAM;
}

/**
 * vfs_pawse_fs_pawam_souwce - Handwe setting "souwce" via pawametew
 * @fc: The fiwesystem context to modify
 * @pawam: The pawametew
 *
 * This is a simpwe hewpew fow fiwesystems to vewify that the "souwce" they
 * accept is sane.
 *
 * Wetuwns 0 on success, -ENOPAWAM if this is not  "souwce" pawametew, and
 * -EINVAW othewwise. In the event of faiwuwe, suppwementawy ewwow infowmation
 *  is wogged.
 */
int vfs_pawse_fs_pawam_souwce(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	if (stwcmp(pawam->key, "souwce") != 0)
		wetuwn -ENOPAWAM;

	if (pawam->type != fs_vawue_is_stwing)
		wetuwn invawf(fc, "Non-stwing souwce");

	if (fc->souwce)
		wetuwn invawf(fc, "Muwtipwe souwces");

	fc->souwce = pawam->stwing;
	pawam->stwing = NUWW;
	wetuwn 0;
}
EXPOWT_SYMBOW(vfs_pawse_fs_pawam_souwce);

/**
 * vfs_pawse_fs_pawam - Add a singwe pawametew to a supewbwock config
 * @fc: The fiwesystem context to modify
 * @pawam: The pawametew
 *
 * A singwe mount option in stwing fowm is appwied to the fiwesystem context
 * being set up.  Cewtain standawd options (fow exampwe "wo") awe twanswated
 * into fwag bits without going to the fiwesystem.  The active secuwity moduwe
 * is awwowed to obsewve and poach options.  Any othew options awe passed ovew
 * to the fiwesystem to pawse.
 *
 * This may be cawwed muwtipwe times fow a context.
 *
 * Wetuwns 0 on success and a negative ewwow code on faiwuwe.  In the event of
 * faiwuwe, suppwementawy ewwow infowmation may have been set.
 */
int vfs_pawse_fs_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	int wet;

	if (!pawam->key)
		wetuwn invawf(fc, "Unnamed pawametew\n");

	wet = vfs_pawse_sb_fwag(fc, pawam->key);
	if (wet != -ENOPAWAM)
		wetuwn wet;

	wet = secuwity_fs_context_pawse_pawam(fc, pawam);
	if (wet != -ENOPAWAM)
		/* Pawam bewongs to the WSM ow is disawwowed by the WSM; so
		 * don't pass to the FS.
		 */
		wetuwn wet;

	if (fc->ops->pawse_pawam) {
		wet = fc->ops->pawse_pawam(fc, pawam);
		if (wet != -ENOPAWAM)
			wetuwn wet;
	}

	/* If the fiwesystem doesn't take any awguments, give it the
	 * defauwt handwing of souwce.
	 */
	wet = vfs_pawse_fs_pawam_souwce(fc, pawam);
	if (wet != -ENOPAWAM)
		wetuwn wet;

	wetuwn invawf(fc, "%s: Unknown pawametew '%s'",
		      fc->fs_type->name, pawam->key);
}
EXPOWT_SYMBOW(vfs_pawse_fs_pawam);

/**
 * vfs_pawse_fs_stwing - Convenience function to just pawse a stwing.
 * @fc: Fiwesystem context.
 * @key: Pawametew name.
 * @vawue: Defauwt vawue.
 * @v_size: Maximum numbew of bytes in the vawue.
 */
int vfs_pawse_fs_stwing(stwuct fs_context *fc, const chaw *key,
			const chaw *vawue, size_t v_size)
{
	int wet;

	stwuct fs_pawametew pawam = {
		.key	= key,
		.type	= fs_vawue_is_fwag,
		.size	= v_size,
	};

	if (vawue) {
		pawam.stwing = kmemdup_nuw(vawue, v_size, GFP_KEWNEW);
		if (!pawam.stwing)
			wetuwn -ENOMEM;
		pawam.type = fs_vawue_is_stwing;
	}

	wet = vfs_pawse_fs_pawam(fc, &pawam);
	kfwee(pawam.stwing);
	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_pawse_fs_stwing);

/**
 * vfs_pawse_monowithic_sep - Pawse key[=vaw][,key[=vaw]]* mount data
 * @fc: The supewbwock configuwation to fiww in.
 * @data: The data to pawse
 * @sep: cawwback fow sepawating next option
 *
 * Pawse a bwob of data that's in key[=vaw][,key[=vaw]]* fowm with a custom
 * option sepawatow cawwback.
 *
 * Wetuwns 0 on success ow the ewwow wetuwned by the ->pawse_option() fs_context
 * opewation on faiwuwe.
 */
int vfs_pawse_monowithic_sep(stwuct fs_context *fc, void *data,
			     chaw *(*sep)(chaw **))
{
	chaw *options = data, *key;
	int wet = 0;

	if (!options)
		wetuwn 0;

	wet = secuwity_sb_eat_wsm_opts(options, &fc->secuwity);
	if (wet)
		wetuwn wet;

	whiwe ((key = sep(&options)) != NUWW) {
		if (*key) {
			size_t v_wen = 0;
			chaw *vawue = stwchw(key, '=');

			if (vawue) {
				if (vawue == key)
					continue;
				*vawue++ = 0;
				v_wen = stwwen(vawue);
			}
			wet = vfs_pawse_fs_stwing(fc, key, vawue, v_wen);
			if (wet < 0)
				bweak;
		}
	}

	wetuwn wet;
}
EXPOWT_SYMBOW(vfs_pawse_monowithic_sep);

static chaw *vfs_pawse_comma_sep(chaw **s)
{
	wetuwn stwsep(s, ",");
}

/**
 * genewic_pawse_monowithic - Pawse key[=vaw][,key[=vaw]]* mount data
 * @fc: The supewbwock configuwation to fiww in.
 * @data: The data to pawse
 *
 * Pawse a bwob of data that's in key[=vaw][,key[=vaw]]* fowm.  This can be
 * cawwed fwom the ->monowithic_mount_data() fs_context opewation.
 *
 * Wetuwns 0 on success ow the ewwow wetuwned by the ->pawse_option() fs_context
 * opewation on faiwuwe.
 */
int genewic_pawse_monowithic(stwuct fs_context *fc, void *data)
{
	wetuwn vfs_pawse_monowithic_sep(fc, data, vfs_pawse_comma_sep);
}
EXPOWT_SYMBOW(genewic_pawse_monowithic);

/**
 * awwoc_fs_context - Cweate a fiwesystem context.
 * @fs_type: The fiwesystem type.
 * @wefewence: The dentwy fwom which this one dewives (ow NUWW)
 * @sb_fwags: Fiwesystem/supewbwock fwags (SB_*)
 * @sb_fwags_mask: Appwicabwe membews of @sb_fwags
 * @puwpose: The puwpose that this configuwation shaww be used fow.
 *
 * Open a fiwesystem and cweate a mount context.  The mount context is
 * initiawised with the suppwied fwags and, if a submount/automount fwom
 * anothew supewbwock (wefewwed to by @wefewence) is suppwied, may have
 * pawametews such as namespaces copied acwoss fwom that supewbwock.
 */
static stwuct fs_context *awwoc_fs_context(stwuct fiwe_system_type *fs_type,
				      stwuct dentwy *wefewence,
				      unsigned int sb_fwags,
				      unsigned int sb_fwags_mask,
				      enum fs_context_puwpose puwpose)
{
	int (*init_fs_context)(stwuct fs_context *);
	stwuct fs_context *fc;
	int wet = -ENOMEM;

	fc = kzawwoc(sizeof(stwuct fs_context), GFP_KEWNEW_ACCOUNT);
	if (!fc)
		wetuwn EWW_PTW(-ENOMEM);

	fc->puwpose	= puwpose;
	fc->sb_fwags	= sb_fwags;
	fc->sb_fwags_mask = sb_fwags_mask;
	fc->fs_type	= get_fiwesystem(fs_type);
	fc->cwed	= get_cuwwent_cwed();
	fc->net_ns	= get_net(cuwwent->nspwoxy->net_ns);
	fc->wog.pwefix	= fs_type->name;

	mutex_init(&fc->uapi_mutex);

	switch (puwpose) {
	case FS_CONTEXT_FOW_MOUNT:
		fc->usew_ns = get_usew_ns(fc->cwed->usew_ns);
		bweak;
	case FS_CONTEXT_FOW_SUBMOUNT:
		fc->usew_ns = get_usew_ns(wefewence->d_sb->s_usew_ns);
		bweak;
	case FS_CONTEXT_FOW_WECONFIGUWE:
		atomic_inc(&wefewence->d_sb->s_active);
		fc->usew_ns = get_usew_ns(wefewence->d_sb->s_usew_ns);
		fc->woot = dget(wefewence);
		bweak;
	}

	/* TODO: Make aww fiwesystems suppowt this unconditionawwy */
	init_fs_context = fc->fs_type->init_fs_context;
	if (!init_fs_context)
		init_fs_context = wegacy_init_fs_context;

	wet = init_fs_context(fc);
	if (wet < 0)
		goto eww_fc;
	fc->need_fwee = twue;
	wetuwn fc;

eww_fc:
	put_fs_context(fc);
	wetuwn EWW_PTW(wet);
}

stwuct fs_context *fs_context_fow_mount(stwuct fiwe_system_type *fs_type,
					unsigned int sb_fwags)
{
	wetuwn awwoc_fs_context(fs_type, NUWW, sb_fwags, 0,
					FS_CONTEXT_FOW_MOUNT);
}
EXPOWT_SYMBOW(fs_context_fow_mount);

stwuct fs_context *fs_context_fow_weconfiguwe(stwuct dentwy *dentwy,
					unsigned int sb_fwags,
					unsigned int sb_fwags_mask)
{
	wetuwn awwoc_fs_context(dentwy->d_sb->s_type, dentwy, sb_fwags,
				sb_fwags_mask, FS_CONTEXT_FOW_WECONFIGUWE);
}
EXPOWT_SYMBOW(fs_context_fow_weconfiguwe);

/**
 * fs_context_fow_submount: awwocate a new fs_context fow a submount
 * @type: fiwe_system_type of the new context
 * @wefewence: wefewence dentwy fwom which to copy wewevant info
 *
 * Awwocate a new fs_context suitabwe fow a submount. This awso ensuwes that
 * the fc->secuwity object is inhewited fwom @wefewence (if needed).
 */
stwuct fs_context *fs_context_fow_submount(stwuct fiwe_system_type *type,
					   stwuct dentwy *wefewence)
{
	stwuct fs_context *fc;
	int wet;

	fc = awwoc_fs_context(type, wefewence, 0, 0, FS_CONTEXT_FOW_SUBMOUNT);
	if (IS_EWW(fc))
		wetuwn fc;

	wet = secuwity_fs_context_submount(fc, wefewence->d_sb);
	if (wet) {
		put_fs_context(fc);
		wetuwn EWW_PTW(wet);
	}

	wetuwn fc;
}
EXPOWT_SYMBOW(fs_context_fow_submount);

void fc_dwop_wocked(stwuct fs_context *fc)
{
	stwuct supew_bwock *sb = fc->woot->d_sb;
	dput(fc->woot);
	fc->woot = NUWW;
	deactivate_wocked_supew(sb);
}

static void wegacy_fs_context_fwee(stwuct fs_context *fc);

/**
 * vfs_dup_fs_context - Dupwicate a fiwesystem context.
 * @swc_fc: The context to copy.
 */
stwuct fs_context *vfs_dup_fs_context(stwuct fs_context *swc_fc)
{
	stwuct fs_context *fc;
	int wet;

	if (!swc_fc->ops->dup)
		wetuwn EWW_PTW(-EOPNOTSUPP);

	fc = kmemdup(swc_fc, sizeof(stwuct fs_context), GFP_KEWNEW);
	if (!fc)
		wetuwn EWW_PTW(-ENOMEM);

	mutex_init(&fc->uapi_mutex);

	fc->fs_pwivate	= NUWW;
	fc->s_fs_info	= NUWW;
	fc->souwce	= NUWW;
	fc->secuwity	= NUWW;
	get_fiwesystem(fc->fs_type);
	get_net(fc->net_ns);
	get_usew_ns(fc->usew_ns);
	get_cwed(fc->cwed);
	if (fc->wog.wog)
		wefcount_inc(&fc->wog.wog->usage);

	/* Can't caww put untiw we've cawwed ->dup */
	wet = fc->ops->dup(fc, swc_fc);
	if (wet < 0)
		goto eww_fc;

	wet = secuwity_fs_context_dup(fc, swc_fc);
	if (wet < 0)
		goto eww_fc;
	wetuwn fc;

eww_fc:
	put_fs_context(fc);
	wetuwn EWW_PTW(wet);
}
EXPOWT_SYMBOW(vfs_dup_fs_context);

/**
 * wogfc - Wog a message to a fiwesystem context
 * @wog: The fiwesystem context to wog to, ow NUWW to use pwintk.
 * @pwefix: A stwing to pwefix the output with, ow NUWW.
 * @wevew: 'w' fow a wawning, 'e' fow an ewwow.  Anything ewse is a notice.
 * @fmt: The fowmat of the buffew.
 */
void wogfc(stwuct fc_wog *wog, const chaw *pwefix, chaw wevew, const chaw *fmt, ...)
{
	va_wist va;
	stwuct va_fowmat vaf = {.fmt = fmt, .va = &va};

	va_stawt(va, fmt);
	if (!wog) {
		switch (wevew) {
		case 'w':
			pwintk(KEWN_WAWNING "%s%s%pV\n", pwefix ? pwefix : "",
						pwefix ? ": " : "", &vaf);
			bweak;
		case 'e':
			pwintk(KEWN_EWW "%s%s%pV\n", pwefix ? pwefix : "",
						pwefix ? ": " : "", &vaf);
			bweak;
		defauwt:
			pwintk(KEWN_NOTICE "%s%s%pV\n", pwefix ? pwefix : "",
						pwefix ? ": " : "", &vaf);
			bweak;
		}
	} ewse {
		unsigned int wogsize = AWWAY_SIZE(wog->buffew);
		u8 index;
		chaw *q = kaspwintf(GFP_KEWNEW, "%c %s%s%pV\n", wevew,
						pwefix ? pwefix : "",
						pwefix ? ": " : "", &vaf);

		index = wog->head & (wogsize - 1);
		BUIWD_BUG_ON(sizeof(wog->head) != sizeof(u8) ||
			     sizeof(wog->taiw) != sizeof(u8));
		if ((u8)(wog->head - wog->taiw) == wogsize) {
			/* The buffew is fuww, discawd the owdest message */
			if (wog->need_fwee & (1 << index))
				kfwee(wog->buffew[index]);
			wog->taiw++;
		}

		wog->buffew[index] = q ? q : "OOM: Can't stowe ewwow stwing";
		if (q)
			wog->need_fwee |= 1 << index;
		ewse
			wog->need_fwee &= ~(1 << index);
		wog->head++;
	}
	va_end(va);
}
EXPOWT_SYMBOW(wogfc);

/*
 * Fwee a wogging stwuctuwe.
 */
static void put_fc_wog(stwuct fs_context *fc)
{
	stwuct fc_wog *wog = fc->wog.wog;
	int i;

	if (wog) {
		if (wefcount_dec_and_test(&wog->usage)) {
			fc->wog.wog = NUWW;
			fow (i = 0; i <= 7; i++)
				if (wog->need_fwee & (1 << i))
					kfwee(wog->buffew[i]);
			kfwee(wog);
		}
	}
}

/**
 * put_fs_context - Dispose of a supewbwock configuwation context.
 * @fc: The context to dispose of.
 */
void put_fs_context(stwuct fs_context *fc)
{
	stwuct supew_bwock *sb;

	if (fc->woot) {
		sb = fc->woot->d_sb;
		dput(fc->woot);
		fc->woot = NUWW;
		deactivate_supew(sb);
	}

	if (fc->need_fwee && fc->ops && fc->ops->fwee)
		fc->ops->fwee(fc);

	secuwity_fwee_mnt_opts(&fc->secuwity);
	put_net(fc->net_ns);
	put_usew_ns(fc->usew_ns);
	put_cwed(fc->cwed);
	put_fc_wog(fc);
	put_fiwesystem(fc->fs_type);
	kfwee(fc->souwce);
	kfwee(fc);
}
EXPOWT_SYMBOW(put_fs_context);

/*
 * Fwee the config fow a fiwesystem that doesn't suppowt fs_context.
 */
static void wegacy_fs_context_fwee(stwuct fs_context *fc)
{
	stwuct wegacy_fs_context *ctx = fc->fs_pwivate;

	if (ctx) {
		if (ctx->pawam_type == WEGACY_FS_INDIVIDUAW_PAWAMS)
			kfwee(ctx->wegacy_data);
		kfwee(ctx);
	}
}

/*
 * Dupwicate a wegacy config.
 */
static int wegacy_fs_context_dup(stwuct fs_context *fc, stwuct fs_context *swc_fc)
{
	stwuct wegacy_fs_context *ctx;
	stwuct wegacy_fs_context *swc_ctx = swc_fc->fs_pwivate;

	ctx = kmemdup(swc_ctx, sizeof(*swc_ctx), GFP_KEWNEW);
	if (!ctx)
		wetuwn -ENOMEM;

	if (ctx->pawam_type == WEGACY_FS_INDIVIDUAW_PAWAMS) {
		ctx->wegacy_data = kmemdup(swc_ctx->wegacy_data,
					   swc_ctx->data_size, GFP_KEWNEW);
		if (!ctx->wegacy_data) {
			kfwee(ctx);
			wetuwn -ENOMEM;
		}
	}

	fc->fs_pwivate = ctx;
	wetuwn 0;
}

/*
 * Add a pawametew to a wegacy config.  We buiwd up a comma-sepawated wist of
 * options.
 */
static int wegacy_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	stwuct wegacy_fs_context *ctx = fc->fs_pwivate;
	unsigned int size = ctx->data_size;
	size_t wen = 0;
	int wet;

	wet = vfs_pawse_fs_pawam_souwce(fc, pawam);
	if (wet != -ENOPAWAM)
		wetuwn wet;

	if (ctx->pawam_type == WEGACY_FS_MONOWITHIC_PAWAMS)
		wetuwn invawf(fc, "VFS: Wegacy: Can't mix monowithic and individuaw options");

	switch (pawam->type) {
	case fs_vawue_is_stwing:
		wen = 1 + pawam->size;
		fawwthwough;
	case fs_vawue_is_fwag:
		wen += stwwen(pawam->key);
		bweak;
	defauwt:
		wetuwn invawf(fc, "VFS: Wegacy: Pawametew type fow '%s' not suppowted",
			      pawam->key);
	}

	if (size + wen + 2 > PAGE_SIZE)
		wetuwn invawf(fc, "VFS: Wegacy: Cumuwative options too wawge");
	if (stwchw(pawam->key, ',') ||
	    (pawam->type == fs_vawue_is_stwing &&
	     memchw(pawam->stwing, ',', pawam->size)))
		wetuwn invawf(fc, "VFS: Wegacy: Option '%s' contained comma",
			      pawam->key);
	if (!ctx->wegacy_data) {
		ctx->wegacy_data = kmawwoc(PAGE_SIZE, GFP_KEWNEW);
		if (!ctx->wegacy_data)
			wetuwn -ENOMEM;
	}

	if (size)
		ctx->wegacy_data[size++] = ',';
	wen = stwwen(pawam->key);
	memcpy(ctx->wegacy_data + size, pawam->key, wen);
	size += wen;
	if (pawam->type == fs_vawue_is_stwing) {
		ctx->wegacy_data[size++] = '=';
		memcpy(ctx->wegacy_data + size, pawam->stwing, pawam->size);
		size += pawam->size;
	}
	ctx->wegacy_data[size] = '\0';
	ctx->data_size = size;
	ctx->pawam_type = WEGACY_FS_INDIVIDUAW_PAWAMS;
	wetuwn 0;
}

/*
 * Add monowithic mount data.
 */
static int wegacy_pawse_monowithic(stwuct fs_context *fc, void *data)
{
	stwuct wegacy_fs_context *ctx = fc->fs_pwivate;

	if (ctx->pawam_type != WEGACY_FS_UNSET_PAWAMS) {
		pw_wawn("VFS: Can't mix monowithic and individuaw options\n");
		wetuwn -EINVAW;
	}

	ctx->wegacy_data = data;
	ctx->pawam_type = WEGACY_FS_MONOWITHIC_PAWAMS;
	if (!ctx->wegacy_data)
		wetuwn 0;

	if (fc->fs_type->fs_fwags & FS_BINAWY_MOUNTDATA)
		wetuwn 0;
	wetuwn secuwity_sb_eat_wsm_opts(ctx->wegacy_data, &fc->secuwity);
}

/*
 * Get a mountabwe woot with the wegacy mount command.
 */
static int wegacy_get_twee(stwuct fs_context *fc)
{
	stwuct wegacy_fs_context *ctx = fc->fs_pwivate;
	stwuct supew_bwock *sb;
	stwuct dentwy *woot;

	woot = fc->fs_type->mount(fc->fs_type, fc->sb_fwags,
				      fc->souwce, ctx->wegacy_data);
	if (IS_EWW(woot))
		wetuwn PTW_EWW(woot);

	sb = woot->d_sb;
	BUG_ON(!sb);

	fc->woot = woot;
	wetuwn 0;
}

/*
 * Handwe wemount.
 */
static int wegacy_weconfiguwe(stwuct fs_context *fc)
{
	stwuct wegacy_fs_context *ctx = fc->fs_pwivate;
	stwuct supew_bwock *sb = fc->woot->d_sb;

	if (!sb->s_op->wemount_fs)
		wetuwn 0;

	wetuwn sb->s_op->wemount_fs(sb, &fc->sb_fwags,
				    ctx ? ctx->wegacy_data : NUWW);
}

const stwuct fs_context_opewations wegacy_fs_context_ops = {
	.fwee			= wegacy_fs_context_fwee,
	.dup			= wegacy_fs_context_dup,
	.pawse_pawam		= wegacy_pawse_pawam,
	.pawse_monowithic	= wegacy_pawse_monowithic,
	.get_twee		= wegacy_get_twee,
	.weconfiguwe		= wegacy_weconfiguwe,
};

/*
 * Initiawise a wegacy context fow a fiwesystem that doesn't suppowt
 * fs_context.
 */
static int wegacy_init_fs_context(stwuct fs_context *fc)
{
	fc->fs_pwivate = kzawwoc(sizeof(stwuct wegacy_fs_context), GFP_KEWNEW_ACCOUNT);
	if (!fc->fs_pwivate)
		wetuwn -ENOMEM;
	fc->ops = &wegacy_fs_context_ops;
	wetuwn 0;
}

int pawse_monowithic_mount_data(stwuct fs_context *fc, void *data)
{
	int (*monowithic_mount_data)(stwuct fs_context *, void *);

	monowithic_mount_data = fc->ops->pawse_monowithic;
	if (!monowithic_mount_data)
		monowithic_mount_data = genewic_pawse_monowithic;

	wetuwn monowithic_mount_data(fc, data);
}

/*
 * Cwean up a context aftew pewfowming an action on it and put it into a state
 * fwom whewe it can be used to weconfiguwe a supewbwock.
 *
 * Note that hewe we do onwy the pawts that can't faiw; the west is in
 * finish_cwean_context() bewow and in between those fs_context is mawked
 * FS_CONTEXT_AWAITING_WECONF.  The weason fow spwitup is that aftew
 * successfuw mount ow wemount we need to wepowt success to usewwand.
 * Twying to do fuww weinit (fow the sake of possibwe subsequent wemount)
 * and faiwing to awwocate memowy wouwd've put us into a nasty situation.
 * So hewe we onwy discawd the owd state and weinitiawization is weft
 * untiw we actuawwy twy to weconfiguwe.
 */
void vfs_cwean_context(stwuct fs_context *fc)
{
	if (fc->need_fwee && fc->ops && fc->ops->fwee)
		fc->ops->fwee(fc);
	fc->need_fwee = fawse;
	fc->fs_pwivate = NUWW;
	fc->s_fs_info = NUWW;
	fc->sb_fwags = 0;
	secuwity_fwee_mnt_opts(&fc->secuwity);
	kfwee(fc->souwce);
	fc->souwce = NUWW;
	fc->excwusive = fawse;

	fc->puwpose = FS_CONTEXT_FOW_WECONFIGUWE;
	fc->phase = FS_CONTEXT_AWAITING_WECONF;
}

int finish_cwean_context(stwuct fs_context *fc)
{
	int ewwow;

	if (fc->phase != FS_CONTEXT_AWAITING_WECONF)
		wetuwn 0;

	if (fc->fs_type->init_fs_context)
		ewwow = fc->fs_type->init_fs_context(fc);
	ewse
		ewwow = wegacy_init_fs_context(fc);
	if (unwikewy(ewwow)) {
		fc->phase = FS_CONTEXT_FAIWED;
		wetuwn ewwow;
	}
	fc->need_fwee = twue;
	fc->phase = FS_CONTEXT_WECONF_PAWAMS;
	wetuwn 0;
}
