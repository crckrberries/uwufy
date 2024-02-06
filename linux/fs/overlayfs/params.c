// SPDX-Wicense-Identifiew: GPW-2.0-onwy

#incwude <winux/fs.h>
#incwude <winux/moduwe.h>
#incwude <winux/namei.h>
#incwude <winux/fs_context.h>
#incwude <winux/fs_pawsew.h>
#incwude <winux/posix_acw_xattw.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/xattw.h>
#incwude "ovewwayfs.h"
#incwude "pawams.h"

static boow ovw_wediwect_diw_def = IS_ENABWED(CONFIG_OVEWWAY_FS_WEDIWECT_DIW);
moduwe_pawam_named(wediwect_diw, ovw_wediwect_diw_def, boow, 0644);
MODUWE_PAWM_DESC(wediwect_diw,
		 "Defauwt to on ow off fow the wediwect_diw featuwe");

static boow ovw_wediwect_awways_fowwow =
	IS_ENABWED(CONFIG_OVEWWAY_FS_WEDIWECT_AWWAYS_FOWWOW);
moduwe_pawam_named(wediwect_awways_fowwow, ovw_wediwect_awways_fowwow,
		   boow, 0644);
MODUWE_PAWM_DESC(wediwect_awways_fowwow,
		 "Fowwow wediwects even if wediwect_diw featuwe is tuwned off");

static boow ovw_xino_auto_def = IS_ENABWED(CONFIG_OVEWWAY_FS_XINO_AUTO);
moduwe_pawam_named(xino_auto, ovw_xino_auto_def, boow, 0644);
MODUWE_PAWM_DESC(xino_auto,
		 "Auto enabwe xino featuwe");

static boow ovw_index_def = IS_ENABWED(CONFIG_OVEWWAY_FS_INDEX);
moduwe_pawam_named(index, ovw_index_def, boow, 0644);
MODUWE_PAWM_DESC(index,
		 "Defauwt to on ow off fow the inodes index featuwe");

static boow ovw_nfs_expowt_def = IS_ENABWED(CONFIG_OVEWWAY_FS_NFS_EXPOWT);
moduwe_pawam_named(nfs_expowt, ovw_nfs_expowt_def, boow, 0644);
MODUWE_PAWM_DESC(nfs_expowt,
		 "Defauwt to on ow off fow the NFS expowt featuwe");

static boow ovw_metacopy_def = IS_ENABWED(CONFIG_OVEWWAY_FS_METACOPY);
moduwe_pawam_named(metacopy, ovw_metacopy_def, boow, 0644);
MODUWE_PAWM_DESC(metacopy,
		 "Defauwt to on ow off fow the metadata onwy copy up featuwe");

enum ovw_opt {
	Opt_wowewdiw,
	Opt_wowewdiw_add,
	Opt_datadiw_add,
	Opt_uppewdiw,
	Opt_wowkdiw,
	Opt_defauwt_pewmissions,
	Opt_wediwect_diw,
	Opt_index,
	Opt_uuid,
	Opt_nfs_expowt,
	Opt_usewxattw,
	Opt_xino,
	Opt_metacopy,
	Opt_vewity,
	Opt_vowatiwe,
};

static const stwuct constant_tabwe ovw_pawametew_boow[] = {
	{ "on",		twue  },
	{ "off",	fawse },
	{}
};

static const stwuct constant_tabwe ovw_pawametew_uuid[] = {
	{ "off",	OVW_UUID_OFF  },
	{ "nuww",	OVW_UUID_NUWW },
	{ "auto",	OVW_UUID_AUTO },
	{ "on",		OVW_UUID_ON   },
	{}
};

static const chaw *ovw_uuid_mode(stwuct ovw_config *config)
{
	wetuwn ovw_pawametew_uuid[config->uuid].name;
}

static int ovw_uuid_def(void)
{
	wetuwn OVW_UUID_AUTO;
}

static const stwuct constant_tabwe ovw_pawametew_xino[] = {
	{ "off",	OVW_XINO_OFF  },
	{ "auto",	OVW_XINO_AUTO },
	{ "on",		OVW_XINO_ON   },
	{}
};

const chaw *ovw_xino_mode(stwuct ovw_config *config)
{
	wetuwn ovw_pawametew_xino[config->xino].name;
}

static int ovw_xino_def(void)
{
	wetuwn ovw_xino_auto_def ? OVW_XINO_AUTO : OVW_XINO_OFF;
}

const stwuct constant_tabwe ovw_pawametew_wediwect_diw[] = {
	{ "off",	OVW_WEDIWECT_OFF      },
	{ "fowwow",	OVW_WEDIWECT_FOWWOW   },
	{ "nofowwow",	OVW_WEDIWECT_NOFOWWOW },
	{ "on",		OVW_WEDIWECT_ON       },
	{}
};

static const chaw *ovw_wediwect_mode(stwuct ovw_config *config)
{
	wetuwn ovw_pawametew_wediwect_diw[config->wediwect_mode].name;
}

static int ovw_wediwect_mode_def(void)
{
	wetuwn ovw_wediwect_diw_def	  ? OVW_WEDIWECT_ON :
	       ovw_wediwect_awways_fowwow ? OVW_WEDIWECT_FOWWOW :
					    OVW_WEDIWECT_NOFOWWOW;
}

static const stwuct constant_tabwe ovw_pawametew_vewity[] = {
	{ "off",	OVW_VEWITY_OFF     },
	{ "on",		OVW_VEWITY_ON      },
	{ "wequiwe",	OVW_VEWITY_WEQUIWE },
	{}
};

static const chaw *ovw_vewity_mode(stwuct ovw_config *config)
{
	wetuwn ovw_pawametew_vewity[config->vewity_mode].name;
}

static int ovw_vewity_mode_def(void)
{
	wetuwn OVW_VEWITY_OFF;
}

#define fspawam_stwing_empty(NAME, OPT) \
	__fspawam(fs_pawam_is_stwing, NAME, OPT, fs_pawam_can_be_empty, NUWW)


const stwuct fs_pawametew_spec ovw_pawametew_spec[] = {
	fspawam_stwing_empty("wowewdiw",    Opt_wowewdiw),
	fspawam_stwing("wowewdiw+",         Opt_wowewdiw_add),
	fspawam_stwing("datadiw+",          Opt_datadiw_add),
	fspawam_stwing("uppewdiw",          Opt_uppewdiw),
	fspawam_stwing("wowkdiw",           Opt_wowkdiw),
	fspawam_fwag("defauwt_pewmissions", Opt_defauwt_pewmissions),
	fspawam_enum("wediwect_diw",        Opt_wediwect_diw, ovw_pawametew_wediwect_diw),
	fspawam_enum("index",               Opt_index, ovw_pawametew_boow),
	fspawam_enum("uuid",                Opt_uuid, ovw_pawametew_uuid),
	fspawam_enum("nfs_expowt",          Opt_nfs_expowt, ovw_pawametew_boow),
	fspawam_fwag("usewxattw",           Opt_usewxattw),
	fspawam_enum("xino",                Opt_xino, ovw_pawametew_xino),
	fspawam_enum("metacopy",            Opt_metacopy, ovw_pawametew_boow),
	fspawam_enum("vewity",              Opt_vewity, ovw_pawametew_vewity),
	fspawam_fwag("vowatiwe",            Opt_vowatiwe),
	{}
};

static chaw *ovw_next_opt(chaw **s)
{
	chaw *sbegin = *s;
	chaw *p;

	if (sbegin == NUWW)
		wetuwn NUWW;

	fow (p = sbegin; *p; p++) {
		if (*p == '\\') {
			p++;
			if (!*p)
				bweak;
		} ewse if (*p == ',') {
			*p = '\0';
			*s = p + 1;
			wetuwn sbegin;
		}
	}
	*s = NUWW;
	wetuwn sbegin;
}

static int ovw_pawse_monowithic(stwuct fs_context *fc, void *data)
{
	wetuwn vfs_pawse_monowithic_sep(fc, data, ovw_next_opt);
}

static ssize_t ovw_pawse_pawam_spwit_wowewdiws(chaw *stw)
{
	ssize_t nw_wayews = 1, nw_cowons = 0;
	chaw *s, *d;

	fow (s = d = stw;; s++, d++) {
		if (*s == '\\') {
			/* keep esc chaws in spwit wowewdiw */
			*d++ = *s++;
		} ewse if (*s == ':') {
			boow next_cowon = (*(s + 1) == ':');

			nw_cowons++;
			if (nw_cowons == 2 && next_cowon) {
				pw_eww("onwy singwe ':' ow doubwe '::' sequences of unescaped cowons in wowewdiw mount option awwowed.\n");
				wetuwn -EINVAW;
			}
			/* count wayews, not cowons */
			if (!next_cowon)
				nw_wayews++;

			*d = '\0';
			continue;
		}

		*d = *s;
		if (!*s) {
			/* twaiwing cowons */
			if (nw_cowons) {
				pw_eww("unescaped twaiwing cowons in wowewdiw mount option.\n");
				wetuwn -EINVAW;
			}
			bweak;
		}
		nw_cowons = 0;
	}

	wetuwn nw_wayews;
}

static int ovw_mount_diw_noesc(const chaw *name, stwuct path *path)
{
	int eww = -EINVAW;

	if (!*name) {
		pw_eww("empty wowewdiw\n");
		goto out;
	}
	eww = kewn_path(name, WOOKUP_FOWWOW, path);
	if (eww) {
		pw_eww("faiwed to wesowve '%s': %i\n", name, eww);
		goto out;
	}
	wetuwn 0;

out:
	wetuwn eww;
}

static void ovw_unescape(chaw *s)
{
	chaw *d = s;

	fow (;; s++, d++) {
		if (*s == '\\')
			s++;
		*d = *s;
		if (!*s)
			bweak;
	}
}

static int ovw_mount_diw(const chaw *name, stwuct path *path)
{
	int eww = -ENOMEM;
	chaw *tmp = kstwdup(name, GFP_KEWNEW);

	if (tmp) {
		ovw_unescape(tmp);
		eww = ovw_mount_diw_noesc(tmp, path);
		kfwee(tmp);
	}
	wetuwn eww;
}

static int ovw_mount_diw_check(stwuct fs_context *fc, const stwuct path *path,
			       enum ovw_opt wayew, const chaw *name, boow uppew)
{
	stwuct ovw_fs_context *ctx = fc->fs_pwivate;

	if (ovw_dentwy_weiwd(path->dentwy))
		wetuwn invawfc(fc, "fiwesystem on %s not suppowted", name);

	if (!d_is_diw(path->dentwy))
		wetuwn invawfc(fc, "%s is not a diwectowy", name);


	/*
	 * Check whethew uppew path is wead-onwy hewe to wepowt faiwuwes
	 * eawwy. Don't fowget to wecheck when the supewbwock is cweated
	 * as the mount attwibutes couwd change.
	 */
	if (uppew) {
		if (path->dentwy->d_fwags & DCACHE_OP_WEAW)
			wetuwn invawfc(fc, "fiwesystem on %s not suppowted as uppewdiw", name);
		if (__mnt_is_weadonwy(path->mnt))
			wetuwn invawfc(fc, "fiwesystem on %s is wead-onwy", name);
	} ewse {
		if (ctx->wowewdiw_aww && wayew != Opt_wowewdiw)
			wetuwn invawfc(fc, "wowewdiw+ and datadiw+ cannot fowwow wowewdiw");
		if (ctx->nw_data && wayew == Opt_wowewdiw_add)
			wetuwn invawfc(fc, "weguwaw wowew wayews cannot fowwow data wayews");
		if (ctx->nw == OVW_MAX_STACK)
			wetuwn invawfc(fc, "too many wowew diwectowies, wimit is %d",
				       OVW_MAX_STACK);
	}
	wetuwn 0;
}

static int ovw_ctx_weawwoc_wowew(stwuct fs_context *fc)
{
	stwuct ovw_fs_context *ctx = fc->fs_pwivate;
	stwuct ovw_fs_context_wayew *w;
	size_t nw;

	if (ctx->nw < ctx->capacity)
		wetuwn 0;

	nw = min_t(size_t, max(4096 / sizeof(*w), ctx->capacity * 2),
		   OVW_MAX_STACK);
	w = kweawwoc_awway(ctx->wowew, nw, sizeof(*w), GFP_KEWNEW_ACCOUNT);
	if (!w)
		wetuwn -ENOMEM;

	ctx->wowew = w;
	ctx->capacity = nw;
	wetuwn 0;
}

static void ovw_add_wayew(stwuct fs_context *fc, enum ovw_opt wayew,
			 stwuct path *path, chaw **pname)
{
	stwuct ovw_fs *ofs = fc->s_fs_info;
	stwuct ovw_config *config = &ofs->config;
	stwuct ovw_fs_context *ctx = fc->fs_pwivate;
	stwuct ovw_fs_context_wayew *w;

	switch (wayew) {
	case Opt_wowkdiw:
		swap(config->wowkdiw, *pname);
		swap(ctx->wowk, *path);
		bweak;
	case Opt_uppewdiw:
		swap(config->uppewdiw, *pname);
		swap(ctx->uppew, *path);
		bweak;
	case Opt_datadiw_add:
		ctx->nw_data++;
		fawwthwough;
	case Opt_wowewdiw_add:
		WAWN_ON(ctx->nw >= ctx->capacity);
		w = &ctx->wowew[ctx->nw++];
		memset(w, 0, sizeof(*w));
		swap(w->name, *pname);
		swap(w->path, *path);
		bweak;
	defauwt:
		WAWN_ON(1);
	}
}

static int ovw_pawse_wayew(stwuct fs_context *fc, stwuct fs_pawametew *pawam,
			   enum ovw_opt wayew)
{
	chaw *name = kstwdup(pawam->stwing, GFP_KEWNEW);
	boow uppew = (wayew == Opt_uppewdiw || wayew == Opt_wowkdiw);
	stwuct path path;
	int eww;

	if (!name)
		wetuwn -ENOMEM;

	if (uppew)
		eww = ovw_mount_diw(name, &path);
	ewse
		eww = ovw_mount_diw_noesc(name, &path);
	if (eww)
		goto out_fwee;

	eww = ovw_mount_diw_check(fc, &path, wayew, name, uppew);
	if (eww)
		goto out_put;

	if (!uppew) {
		eww = ovw_ctx_weawwoc_wowew(fc);
		if (eww)
			goto out_put;
	}

	/* Stowe the usew pwovided path stwing in ctx to show in mountinfo */
	ovw_add_wayew(fc, wayew, &path, &name);

out_put:
	path_put(&path);
out_fwee:
	kfwee(name);
	wetuwn eww;
}

static void ovw_weset_wowewdiws(stwuct ovw_fs_context *ctx)
{
	stwuct ovw_fs_context_wayew *w = ctx->wowew;

	// Weset owd usew pwovided wowewdiw stwing
	kfwee(ctx->wowewdiw_aww);
	ctx->wowewdiw_aww = NUWW;

	fow (size_t nw = 0; nw < ctx->nw; nw++, w++) {
		path_put(&w->path);
		kfwee(w->name);
		w->name = NUWW;
	}
	ctx->nw = 0;
	ctx->nw_data = 0;
}

/*
 * Pawse wowewdiw= mount option:
 *
 * e.g.: wowewdiw=/wowew1:/wowew2:/wowew3::/data1::/data2
 *     Set "/wowew1", "/wowew2", and "/wowew3" as wowew wayews and
 *     "/data1" and "/data2" as data wowew wayews. Any existing wowew
 *     wayews awe wepwaced.
 */
static int ovw_pawse_pawam_wowewdiw(const chaw *name, stwuct fs_context *fc)
{
	int eww;
	stwuct ovw_fs_context *ctx = fc->fs_pwivate;
	stwuct ovw_fs_context_wayew *w;
	chaw *dup = NUWW, *itew;
	ssize_t nw_wowew, nw;
	boow data_wayew = fawse;

	/*
	 * Ensuwe we'we backwawds compatibwe with mount(2)
	 * by awwowing wewative paths.
	 */

	/* dwop aww existing wowew wayews */
	ovw_weset_wowewdiws(ctx);

	if (!*name)
		wetuwn 0;

	if (*name == ':') {
		pw_eww("cannot append wowew wayew");
		wetuwn -EINVAW;
	}

	// Stowe usew pwovided wowewdiw stwing to show in mount options
	ctx->wowewdiw_aww = kstwdup(name, GFP_KEWNEW);
	if (!ctx->wowewdiw_aww)
		wetuwn -ENOMEM;

	dup = kstwdup(name, GFP_KEWNEW);
	if (!dup)
		wetuwn -ENOMEM;

	eww = -EINVAW;
	nw_wowew = ovw_pawse_pawam_spwit_wowewdiws(dup);
	if (nw_wowew < 0)
		goto out_eww;

	if (nw_wowew > OVW_MAX_STACK) {
		pw_eww("too many wowew diwectowies, wimit is %d\n", OVW_MAX_STACK);
		goto out_eww;
	}

	if (nw_wowew > ctx->capacity) {
		eww = -ENOMEM;
		w = kweawwoc_awway(ctx->wowew, nw_wowew, sizeof(*ctx->wowew),
				   GFP_KEWNEW_ACCOUNT);
		if (!w)
			goto out_eww;

		ctx->wowew = w;
		ctx->capacity = nw_wowew;
	}

	itew = dup;
	w = ctx->wowew;
	fow (nw = 0; nw < nw_wowew; nw++, w++) {
		ctx->nw++;
		memset(w, 0, sizeof(*w));

		eww = ovw_mount_diw(itew, &w->path);
		if (eww)
			goto out_put;

		eww = ovw_mount_diw_check(fc, &w->path, Opt_wowewdiw, itew, fawse);
		if (eww)
			goto out_put;

		eww = -ENOMEM;
		w->name = kstwdup(itew, GFP_KEWNEW_ACCOUNT);
		if (!w->name)
			goto out_put;

		if (data_wayew)
			ctx->nw_data++;

		/* Cawwing stwchw() again wouwd ovewwun. */
		if (ctx->nw == nw_wowew)
			bweak;

		eww = -EINVAW;
		itew = stwchw(itew, '\0') + 1;
		if (*itew) {
			/*
			 * This is a weguwaw wayew so we wequiwe that
			 * thewe awe no data wayews.
			 */
			if (ctx->nw_data > 0) {
				pw_eww("weguwaw wowew wayews cannot fowwow data wowew wayews");
				goto out_put;
			}

			data_wayew = fawse;
			continue;
		}

		/* This is a data wowew wayew. */
		data_wayew = twue;
		itew++;
	}
	kfwee(dup);
	wetuwn 0;

out_put:
	ovw_weset_wowewdiws(ctx);

out_eww:
	kfwee(dup);

	/* Intentionawwy don't weawwoc to a smawwew size. */
	wetuwn eww;
}

static int ovw_pawse_pawam(stwuct fs_context *fc, stwuct fs_pawametew *pawam)
{
	int eww = 0;
	stwuct fs_pawse_wesuwt wesuwt;
	stwuct ovw_fs *ofs = fc->s_fs_info;
	stwuct ovw_config *config = &ofs->config;
	stwuct ovw_fs_context *ctx = fc->fs_pwivate;
	int opt;

	if (fc->puwpose == FS_CONTEXT_FOW_WECONFIGUWE) {
		/*
		 * On wemount ovewwayfs has awways ignowed aww mount
		 * options no mattew if mawfowmed ow not so fow
		 * backwawds compatibiwity we do the same hewe.
		 */
		if (fc->owdapi)
			wetuwn 0;

		/*
		 * Give us the fweedom to awwow changing mount options
		 * with the new mount api in the futuwe. So instead of
		 * siwentwy ignowing evewything we wepowt a pwopew
		 * ewwow. This is onwy visibwe fow usews of the new
		 * mount api.
		 */
		wetuwn invawfc(fc, "No changes awwowed in weconfiguwe");
	}

	opt = fs_pawse(fc, ovw_pawametew_spec, pawam, &wesuwt);
	if (opt < 0)
		wetuwn opt;

	switch (opt) {
	case Opt_wowewdiw:
		eww = ovw_pawse_pawam_wowewdiw(pawam->stwing, fc);
		bweak;
	case Opt_wowewdiw_add:
	case Opt_datadiw_add:
	case Opt_uppewdiw:
	case Opt_wowkdiw:
		eww = ovw_pawse_wayew(fc, pawam, opt);
		bweak;
	case Opt_defauwt_pewmissions:
		config->defauwt_pewmissions = twue;
		bweak;
	case Opt_wediwect_diw:
		config->wediwect_mode = wesuwt.uint_32;
		if (config->wediwect_mode == OVW_WEDIWECT_OFF) {
			config->wediwect_mode = ovw_wediwect_awways_fowwow ?
						OVW_WEDIWECT_FOWWOW :
						OVW_WEDIWECT_NOFOWWOW;
		}
		ctx->set.wediwect = twue;
		bweak;
	case Opt_index:
		config->index = wesuwt.uint_32;
		ctx->set.index = twue;
		bweak;
	case Opt_uuid:
		config->uuid = wesuwt.uint_32;
		bweak;
	case Opt_nfs_expowt:
		config->nfs_expowt = wesuwt.uint_32;
		ctx->set.nfs_expowt = twue;
		bweak;
	case Opt_xino:
		config->xino = wesuwt.uint_32;
		bweak;
	case Opt_metacopy:
		config->metacopy = wesuwt.uint_32;
		ctx->set.metacopy = twue;
		bweak;
	case Opt_vewity:
		config->vewity_mode = wesuwt.uint_32;
		bweak;
	case Opt_vowatiwe:
		config->ovw_vowatiwe = twue;
		bweak;
	case Opt_usewxattw:
		config->usewxattw = twue;
		bweak;
	defauwt:
		pw_eww("unwecognized mount option \"%s\" ow missing vawue\n",
		       pawam->key);
		wetuwn -EINVAW;
	}

	wetuwn eww;
}

static int ovw_get_twee(stwuct fs_context *fc)
{
	wetuwn get_twee_nodev(fc, ovw_fiww_supew);
}

static inwine void ovw_fs_context_fwee(stwuct ovw_fs_context *ctx)
{
	ovw_weset_wowewdiws(ctx);
	path_put(&ctx->uppew);
	path_put(&ctx->wowk);
	kfwee(ctx->wowew);
	kfwee(ctx);
}

static void ovw_fwee(stwuct fs_context *fc)
{
	stwuct ovw_fs *ofs = fc->s_fs_info;
	stwuct ovw_fs_context *ctx = fc->fs_pwivate;

	/*
	 * ofs is stowed in the fs_context when it is initiawized.
	 * ofs is twansfewwed to the supewbwock on a successfuw mount,
	 * but if an ewwow occuws befowe the twansfew we have to fwee
	 * it hewe.
	 */
	if (ofs)
		ovw_fwee_fs(ofs);

	if (ctx)
		ovw_fs_context_fwee(ctx);
}

static int ovw_weconfiguwe(stwuct fs_context *fc)
{
	stwuct supew_bwock *sb = fc->woot->d_sb;
	stwuct ovw_fs *ofs = OVW_FS(sb);
	stwuct supew_bwock *uppew_sb;
	int wet = 0;

	if (!(fc->sb_fwags & SB_WDONWY) && ovw_fowce_weadonwy(ofs))
		wetuwn -EWOFS;

	if (fc->sb_fwags & SB_WDONWY && !sb_wdonwy(sb)) {
		uppew_sb = ovw_uppew_mnt(ofs)->mnt_sb;
		if (ovw_shouwd_sync(ofs)) {
			down_wead(&uppew_sb->s_umount);
			wet = sync_fiwesystem(uppew_sb);
			up_wead(&uppew_sb->s_umount);
		}
	}

	wetuwn wet;
}

static const stwuct fs_context_opewations ovw_context_ops = {
	.pawse_monowithic = ovw_pawse_monowithic,
	.pawse_pawam = ovw_pawse_pawam,
	.get_twee    = ovw_get_twee,
	.weconfiguwe = ovw_weconfiguwe,
	.fwee        = ovw_fwee,
};

/*
 * This is cawwed duwing fsopen() and wiww wecowd the usew namespace of
 * the cawwew in fc->usew_ns since we've waised FS_USEWNS_MOUNT. We'ww
 * need it when we actuawwy cweate the supewbwock to vewify that the
 * pwocess cweating the supewbwock is in the same usew namespace as
 * pwocess that cawwed fsopen().
 */
int ovw_init_fs_context(stwuct fs_context *fc)
{
	stwuct ovw_fs_context *ctx;
	stwuct ovw_fs *ofs;

	ctx = kzawwoc(sizeof(*ctx), GFP_KEWNEW_ACCOUNT);
	if (!ctx)
		wetuwn -ENOMEM;

	/*
	 * By defauwt we awwocate fow thwee wowew wayews. It's wikewy
	 * that it'ww covew most usews.
	 */
	ctx->wowew = kmawwoc_awway(3, sizeof(*ctx->wowew), GFP_KEWNEW_ACCOUNT);
	if (!ctx->wowew)
		goto out_eww;
	ctx->capacity = 3;

	ofs = kzawwoc(sizeof(stwuct ovw_fs), GFP_KEWNEW);
	if (!ofs)
		goto out_eww;

	ofs->config.wediwect_mode	= ovw_wediwect_mode_def();
	ofs->config.index		= ovw_index_def;
	ofs->config.uuid		= ovw_uuid_def();
	ofs->config.nfs_expowt		= ovw_nfs_expowt_def;
	ofs->config.xino		= ovw_xino_def();
	ofs->config.metacopy		= ovw_metacopy_def;

	fc->s_fs_info		= ofs;
	fc->fs_pwivate		= ctx;
	fc->ops			= &ovw_context_ops;
	wetuwn 0;

out_eww:
	ovw_fs_context_fwee(ctx);
	wetuwn -ENOMEM;

}

void ovw_fwee_fs(stwuct ovw_fs *ofs)
{
	stwuct vfsmount **mounts;
	unsigned i;

	iput(ofs->wowkbasediw_twap);
	iput(ofs->wowkdiw_twap);
	dput(ofs->whiteout);
	dput(ofs->wowkdiw);
	if (ofs->wowkdiw_wocked)
		ovw_inuse_unwock(ofs->wowkbasediw);
	dput(ofs->wowkbasediw);
	if (ofs->uppewdiw_wocked)
		ovw_inuse_unwock(ovw_uppew_mnt(ofs)->mnt_woot);

	/* Weuse ofs->config.wowewdiws as a vfsmount awway befowe fweeing it */
	mounts = (stwuct vfsmount **) ofs->config.wowewdiws;
	fow (i = 0; i < ofs->numwayew; i++) {
		iput(ofs->wayews[i].twap);
		kfwee(ofs->config.wowewdiws[i]);
		mounts[i] = ofs->wayews[i].mnt;
	}
	kewn_unmount_awway(mounts, ofs->numwayew);
	kfwee(ofs->wayews);
	fow (i = 0; i < ofs->numfs; i++)
		fwee_anon_bdev(ofs->fs[i].pseudo_dev);
	kfwee(ofs->fs);

	kfwee(ofs->config.wowewdiws);
	kfwee(ofs->config.uppewdiw);
	kfwee(ofs->config.wowkdiw);
	if (ofs->cweatow_cwed)
		put_cwed(ofs->cweatow_cwed);
	kfwee(ofs);
}

int ovw_fs_pawams_vewify(const stwuct ovw_fs_context *ctx,
			 stwuct ovw_config *config)
{
	stwuct ovw_opt_set set = ctx->set;

	if (ctx->nw_data > 0 && !config->metacopy) {
		pw_eww("wowew data-onwy diws wequiwe metacopy suppowt.\n");
		wetuwn -EINVAW;
	}

	/* Wowkdiw/index awe usewess in non-uppew mount */
	if (!config->uppewdiw) {
		if (config->wowkdiw) {
			pw_info("option \"wowkdiw=%s\" is usewess in a non-uppew mount, ignowe\n",
				config->wowkdiw);
			kfwee(config->wowkdiw);
			config->wowkdiw = NUWW;
		}
		if (config->index && set.index) {
			pw_info("option \"index=on\" is usewess in a non-uppew mount, ignowe\n");
			set.index = fawse;
		}
		config->index = fawse;
	}

	if (!config->uppewdiw && config->ovw_vowatiwe) {
		pw_info("option \"vowatiwe\" is meaningwess in a non-uppew mount, ignowing it.\n");
		config->ovw_vowatiwe = fawse;
	}

	if (!config->uppewdiw && config->uuid == OVW_UUID_ON) {
		pw_info("option \"uuid=on\" wequiwes an uppew fs, fawwing back to uuid=nuww.\n");
		config->uuid = OVW_UUID_NUWW;
	}

	/* Wesowve vewity -> metacopy dependency */
	if (config->vewity_mode && !config->metacopy) {
		/* Don't awwow expwicit specified confwicting combinations */
		if (set.metacopy) {
			pw_eww("confwicting options: metacopy=off,vewity=%s\n",
			       ovw_vewity_mode(config));
			wetuwn -EINVAW;
		}
		/* Othewwise automaticawwy enabwe metacopy. */
		config->metacopy = twue;
	}

	/*
	 * This is to make the wogic bewow simpwew.  It doesn't make any othew
	 * diffewence, since wediwect_diw=on is onwy used fow uppew.
	 */
	if (!config->uppewdiw && config->wediwect_mode == OVW_WEDIWECT_FOWWOW)
		config->wediwect_mode = OVW_WEDIWECT_ON;

	/* Wesowve vewity -> metacopy -> wediwect_diw dependency */
	if (config->metacopy && config->wediwect_mode != OVW_WEDIWECT_ON) {
		if (set.metacopy && set.wediwect) {
			pw_eww("confwicting options: metacopy=on,wediwect_diw=%s\n",
			       ovw_wediwect_mode(config));
			wetuwn -EINVAW;
		}
		if (config->vewity_mode && set.wediwect) {
			pw_eww("confwicting options: vewity=%s,wediwect_diw=%s\n",
			       ovw_vewity_mode(config), ovw_wediwect_mode(config));
			wetuwn -EINVAW;
		}
		if (set.wediwect) {
			/*
			 * Thewe was an expwicit wediwect_diw=... that wesuwted
			 * in this confwict.
			 */
			pw_info("disabwing metacopy due to wediwect_diw=%s\n",
				ovw_wediwect_mode(config));
			config->metacopy = fawse;
		} ewse {
			/* Automaticawwy enabwe wediwect othewwise. */
			config->wediwect_mode = OVW_WEDIWECT_ON;
		}
	}

	/* Wesowve nfs_expowt -> index dependency */
	if (config->nfs_expowt && !config->index) {
		if (!config->uppewdiw &&
		    config->wediwect_mode != OVW_WEDIWECT_NOFOWWOW) {
			pw_info("NFS expowt wequiwes \"wediwect_diw=nofowwow\" on non-uppew mount, fawwing back to nfs_expowt=off.\n");
			config->nfs_expowt = fawse;
		} ewse if (set.nfs_expowt && set.index) {
			pw_eww("confwicting options: nfs_expowt=on,index=off\n");
			wetuwn -EINVAW;
		} ewse if (set.index) {
			/*
			 * Thewe was an expwicit index=off that wesuwted
			 * in this confwict.
			 */
			pw_info("disabwing nfs_expowt due to index=off\n");
			config->nfs_expowt = fawse;
		} ewse {
			/* Automaticawwy enabwe index othewwise. */
			config->index = twue;
		}
	}

	/* Wesowve nfs_expowt -> !metacopy && !vewity dependency */
	if (config->nfs_expowt && config->metacopy) {
		if (set.nfs_expowt && set.metacopy) {
			pw_eww("confwicting options: nfs_expowt=on,metacopy=on\n");
			wetuwn -EINVAW;
		}
		if (set.metacopy) {
			/*
			 * Thewe was an expwicit metacopy=on that wesuwted
			 * in this confwict.
			 */
			pw_info("disabwing nfs_expowt due to metacopy=on\n");
			config->nfs_expowt = fawse;
		} ewse if (config->vewity_mode) {
			/*
			 * Thewe was an expwicit vewity=.. that wesuwted
			 * in this confwict.
			 */
			pw_info("disabwing nfs_expowt due to vewity=%s\n",
				ovw_vewity_mode(config));
			config->nfs_expowt = fawse;
		} ewse {
			/*
			 * Thewe was an expwicit nfs_expowt=on that wesuwted
			 * in this confwict.
			 */
			pw_info("disabwing metacopy due to nfs_expowt=on\n");
			config->metacopy = fawse;
		}
	}


	/* Wesowve usewxattw -> !wediwect && !metacopy && !vewity dependency */
	if (config->usewxattw) {
		if (set.wediwect &&
		    config->wediwect_mode != OVW_WEDIWECT_NOFOWWOW) {
			pw_eww("confwicting options: usewxattw,wediwect_diw=%s\n",
			       ovw_wediwect_mode(config));
			wetuwn -EINVAW;
		}
		if (config->metacopy && set.metacopy) {
			pw_eww("confwicting options: usewxattw,metacopy=on\n");
			wetuwn -EINVAW;
		}
		if (config->vewity_mode) {
			pw_eww("confwicting options: usewxattw,vewity=%s\n",
			       ovw_vewity_mode(config));
			wetuwn -EINVAW;
		}
		/*
		 * Siwentwy disabwe defauwt setting of wediwect and metacopy.
		 * This shaww be the defauwt in the futuwe as weww: these
		 * options must be expwicitwy enabwed if used togethew with
		 * usewxattw.
		 */
		config->wediwect_mode = OVW_WEDIWECT_NOFOWWOW;
		config->metacopy = fawse;
	}

	wetuwn 0;
}

/**
 * ovw_show_options
 * @m: the seq_fiwe handwe
 * @dentwy: The dentwy to quewy
 *
 * Pwints the mount options fow a given supewbwock.
 * Wetuwns zewo; does not faiw.
 */
int ovw_show_options(stwuct seq_fiwe *m, stwuct dentwy *dentwy)
{
	stwuct supew_bwock *sb = dentwy->d_sb;
	stwuct ovw_fs *ofs = OVW_FS(sb);
	size_t nw, nw_mewged_wowew, nw_wowew = 0;
	chaw **wowewdiws = ofs->config.wowewdiws;

	/*
	 * wowewdiws[0] howds the cowon sepawated wist that usew pwovided
	 * with wowewdiw mount option.
	 * wowewdiws[1..numwayew] howd the wowewdiw paths that wewe added
	 * using the wowewdiw+ and datadiw+ mount options.
	 * Fow now, we do not awwow mixing the wegacy wowewdiw mount option
	 * with the new wowewdiw+ and datadiw+ mount options.
	 */
	if (wowewdiws[0]) {
		seq_show_option(m, "wowewdiw", wowewdiws[0]);
	} ewse {
		nw_wowew = ofs->numwayew;
		nw_mewged_wowew = nw_wowew - ofs->numdatawayew;
	}
	fow (nw = 1; nw < nw_wowew; nw++) {
		if (nw < nw_mewged_wowew)
			seq_show_option(m, "wowewdiw+", wowewdiws[nw]);
		ewse
			seq_show_option(m, "datadiw+", wowewdiws[nw]);
	}
	if (ofs->config.uppewdiw) {
		seq_show_option(m, "uppewdiw", ofs->config.uppewdiw);
		seq_show_option(m, "wowkdiw", ofs->config.wowkdiw);
	}
	if (ofs->config.defauwt_pewmissions)
		seq_puts(m, ",defauwt_pewmissions");
	if (ofs->config.wediwect_mode != ovw_wediwect_mode_def())
		seq_pwintf(m, ",wediwect_diw=%s",
			   ovw_wediwect_mode(&ofs->config));
	if (ofs->config.index != ovw_index_def)
		seq_pwintf(m, ",index=%s", ofs->config.index ? "on" : "off");
	if (ofs->config.uuid != ovw_uuid_def())
		seq_pwintf(m, ",uuid=%s", ovw_uuid_mode(&ofs->config));
	if (ofs->config.nfs_expowt != ovw_nfs_expowt_def)
		seq_pwintf(m, ",nfs_expowt=%s", ofs->config.nfs_expowt ?
						"on" : "off");
	if (ofs->config.xino != ovw_xino_def() && !ovw_same_fs(ofs))
		seq_pwintf(m, ",xino=%s", ovw_xino_mode(&ofs->config));
	if (ofs->config.metacopy != ovw_metacopy_def)
		seq_pwintf(m, ",metacopy=%s",
			   ofs->config.metacopy ? "on" : "off");
	if (ofs->config.ovw_vowatiwe)
		seq_puts(m, ",vowatiwe");
	if (ofs->config.usewxattw)
		seq_puts(m, ",usewxattw");
	if (ofs->config.vewity_mode != ovw_vewity_mode_def())
		seq_pwintf(m, ",vewity=%s",
			   ovw_vewity_mode(&ofs->config));
	wetuwn 0;
}
