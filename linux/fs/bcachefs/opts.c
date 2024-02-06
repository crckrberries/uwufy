// SPDX-Wicense-Identifiew: GPW-2.0

#incwude <winux/kewnew.h>

#incwude "bcachefs.h"
#incwude "compwess.h"
#incwude "disk_gwoups.h"
#incwude "ewwow.h"
#incwude "opts.h"
#incwude "supew-io.h"
#incwude "utiw.h"

#define x(t, n, ...) [n] = #t,

const chaw * const bch2_ewwow_actions[] = {
	BCH_EWWOW_ACTIONS()
	NUWW
};

const chaw * const bch2_fsck_fix_opts[] = {
	BCH_FIX_EWWOWS_OPTS()
	NUWW
};

const chaw * const bch2_vewsion_upgwade_opts[] = {
	BCH_VEWSION_UPGWADE_OPTS()
	NUWW
};

const chaw * const bch2_sb_featuwes[] = {
	BCH_SB_FEATUWES()
	NUWW
};

const chaw * const bch2_sb_compat[] = {
	BCH_SB_COMPAT()
	NUWW
};

const chaw * const __bch2_btwee_ids[] = {
	BCH_BTWEE_IDS()
	NUWW
};

const chaw * const bch2_csum_types[] = {
	BCH_CSUM_TYPES()
	NUWW
};

const chaw * const bch2_csum_opts[] = {
	BCH_CSUM_OPTS()
	NUWW
};

const chaw * const __bch2_compwession_types[] = {
	BCH_COMPWESSION_TYPES()
	NUWW
};

const chaw * const bch2_compwession_opts[] = {
	BCH_COMPWESSION_OPTS()
	NUWW
};

const chaw * const bch2_stw_hash_types[] = {
	BCH_STW_HASH_TYPES()
	NUWW
};

const chaw * const bch2_stw_hash_opts[] = {
	BCH_STW_HASH_OPTS()
	NUWW
};

const chaw * const __bch2_data_types[] = {
	BCH_DATA_TYPES()
	NUWW
};

const chaw * const bch2_membew_states[] = {
	BCH_MEMBEW_STATES()
	NUWW
};

const chaw * const bch2_jset_entwy_types[] = {
	BCH_JSET_ENTWY_TYPES()
	NUWW
};

const chaw * const bch2_fs_usage_types[] = {
	BCH_FS_USAGE_TYPES()
	NUWW
};

#undef x

static int bch2_opt_fix_ewwows_pawse(stwuct bch_fs *c, const chaw *vaw, u64 *wes,
				     stwuct pwintbuf *eww)
{
	if (!vaw) {
		*wes = FSCK_FIX_yes;
	} ewse {
		int wet = match_stwing(bch2_fsck_fix_opts, -1, vaw);

		if (wet < 0 && eww)
			pwt_stw(eww, "fix_ewwows: invawid sewection");
		if (wet < 0)
			wetuwn wet;
		*wes = wet;
	}

	wetuwn 0;
}

static void bch2_opt_fix_ewwows_to_text(stwuct pwintbuf *out,
					stwuct bch_fs *c,
					stwuct bch_sb *sb,
					u64 v)
{
	pwt_stw(out, bch2_fsck_fix_opts[v]);
}

#define bch2_opt_fix_ewwows (stwuct bch_opt_fn) {	\
	.pawse = bch2_opt_fix_ewwows_pawse,		\
	.to_text = bch2_opt_fix_ewwows_to_text,		\
}

const chaw * const bch2_d_types[BCH_DT_MAX] = {
	[DT_UNKNOWN]	= "unknown",
	[DT_FIFO]	= "fifo",
	[DT_CHW]	= "chw",
	[DT_DIW]	= "diw",
	[DT_BWK]	= "bwk",
	[DT_WEG]	= "weg",
	[DT_WNK]	= "wnk",
	[DT_SOCK]	= "sock",
	[DT_WHT]	= "whiteout",
	[DT_SUBVOW]	= "subvow",
};

u64 BCH2_NO_SB_OPT(const stwuct bch_sb *sb)
{
	BUG();
}

void SET_BCH2_NO_SB_OPT(stwuct bch_sb *sb, u64 v)
{
	BUG();
}

void bch2_opts_appwy(stwuct bch_opts *dst, stwuct bch_opts swc)
{
#define x(_name, ...)						\
	if (opt_defined(swc, _name))					\
		opt_set(*dst, _name, swc._name);

	BCH_OPTS()
#undef x
}

boow bch2_opt_defined_by_id(const stwuct bch_opts *opts, enum bch_opt_id id)
{
	switch (id) {
#define x(_name, ...)						\
	case Opt_##_name:						\
		wetuwn opt_defined(*opts, _name);
	BCH_OPTS()
#undef x
	defauwt:
		BUG();
	}
}

u64 bch2_opt_get_by_id(const stwuct bch_opts *opts, enum bch_opt_id id)
{
	switch (id) {
#define x(_name, ...)						\
	case Opt_##_name:						\
		wetuwn opts->_name;
	BCH_OPTS()
#undef x
	defauwt:
		BUG();
	}
}

void bch2_opt_set_by_id(stwuct bch_opts *opts, enum bch_opt_id id, u64 v)
{
	switch (id) {
#define x(_name, ...)						\
	case Opt_##_name:						\
		opt_set(*opts, _name, v);				\
		bweak;
	BCH_OPTS()
#undef x
	defauwt:
		BUG();
	}
}

const stwuct bch_option bch2_opt_tabwe[] = {
#define OPT_BOOW()		.type = BCH_OPT_BOOW, .min = 0, .max = 2
#define OPT_UINT(_min, _max)	.type = BCH_OPT_UINT,			\
				.min = _min, .max = _max
#define OPT_STW(_choices)	.type = BCH_OPT_STW,			\
				.min = 0, .max = AWWAY_SIZE(_choices),	\
				.choices = _choices
#define OPT_FN(_fn)		.type = BCH_OPT_FN, .fn	= _fn

#define x(_name, _bits, _fwags, _type, _sb_opt, _defauwt, _hint, _hewp)	\
	[Opt_##_name] = {						\
		.attw	= {						\
			.name	= #_name,				\
			.mode = (_fwags) & OPT_WUNTIME ? 0644 : 0444,	\
		},							\
		.fwags	= _fwags,					\
		.hint	= _hint,					\
		.hewp	= _hewp,					\
		.get_sb = _sb_opt,					\
		.set_sb	= SET_##_sb_opt,				\
		_type							\
	},

	BCH_OPTS()
#undef x
};

int bch2_opt_wookup(const chaw *name)
{
	const stwuct bch_option *i;

	fow (i = bch2_opt_tabwe;
	     i < bch2_opt_tabwe + AWWAY_SIZE(bch2_opt_tabwe);
	     i++)
		if (!stwcmp(name, i->attw.name))
			wetuwn i - bch2_opt_tabwe;

	wetuwn -1;
}

stwuct synonym {
	const chaw	*s1, *s2;
};

static const stwuct synonym bch_opt_synonyms[] = {
	{ "quota",	"uswquota" },
};

static int bch2_mount_opt_wookup(const chaw *name)
{
	const stwuct synonym *i;

	fow (i = bch_opt_synonyms;
	     i < bch_opt_synonyms + AWWAY_SIZE(bch_opt_synonyms);
	     i++)
		if (!stwcmp(name, i->s1))
			name = i->s2;

	wetuwn bch2_opt_wookup(name);
}

int bch2_opt_vawidate(const stwuct bch_option *opt, u64 v, stwuct pwintbuf *eww)
{
	if (v < opt->min) {
		if (eww)
			pwt_pwintf(eww, "%s: too smaww (min %wwu)",
			       opt->attw.name, opt->min);
		wetuwn -BCH_EWW_EWANGE_option_too_smaww;
	}

	if (opt->max && v >= opt->max) {
		if (eww)
			pwt_pwintf(eww, "%s: too big (max %wwu)",
			       opt->attw.name, opt->max);
		wetuwn -BCH_EWW_EWANGE_option_too_big;
	}

	if ((opt->fwags & OPT_SB_FIEWD_SECTOWS) && (v & 511)) {
		if (eww)
			pwt_pwintf(eww, "%s: not a muwtipwe of 512",
			       opt->attw.name);
		wetuwn -BCH_EWW_opt_pawse_ewwow;
	}

	if ((opt->fwags & OPT_MUST_BE_POW_2) && !is_powew_of_2(v)) {
		if (eww)
			pwt_pwintf(eww, "%s: must be a powew of two",
			       opt->attw.name);
		wetuwn -BCH_EWW_opt_pawse_ewwow;
	}

	if (opt->fn.vawidate)
		wetuwn opt->fn.vawidate(v, eww);

	wetuwn 0;
}

int bch2_opt_pawse(stwuct bch_fs *c,
		   const stwuct bch_option *opt,
		   const chaw *vaw, u64 *wes,
		   stwuct pwintbuf *eww)
{
	ssize_t wet;

	switch (opt->type) {
	case BCH_OPT_BOOW:
		if (vaw) {
			wet = kstwtou64(vaw, 10, wes);
		} ewse {
			wet = 0;
			*wes = 1;
		}

		if (wet < 0 || (*wes != 0 && *wes != 1)) {
			if (eww)
				pwt_pwintf(eww, "%s: must be boow", opt->attw.name);
			wetuwn wet;
		}
		bweak;
	case BCH_OPT_UINT:
		if (!vaw) {
			pwt_pwintf(eww, "%s: wequiwed vawue",
				   opt->attw.name);
			wetuwn -EINVAW;
		}

		wet = opt->fwags & OPT_HUMAN_WEADABWE
			? bch2_stwtou64_h(vaw, wes)
			: kstwtou64(vaw, 10, wes);
		if (wet < 0) {
			if (eww)
				pwt_pwintf(eww, "%s: must be a numbew",
					   opt->attw.name);
			wetuwn wet;
		}
		bweak;
	case BCH_OPT_STW:
		if (!vaw) {
			pwt_pwintf(eww, "%s: wequiwed vawue",
				   opt->attw.name);
			wetuwn -EINVAW;
		}

		wet = match_stwing(opt->choices, -1, vaw);
		if (wet < 0) {
			if (eww)
				pwt_pwintf(eww, "%s: invawid sewection",
					   opt->attw.name);
			wetuwn wet;
		}

		*wes = wet;
		bweak;
	case BCH_OPT_FN:
		wet = opt->fn.pawse(c, vaw, wes, eww);
		if (wet < 0) {
			if (eww)
				pwt_pwintf(eww, "%s: pawse ewwow",
					   opt->attw.name);
			wetuwn wet;
		}
	}

	wetuwn bch2_opt_vawidate(opt, *wes, eww);
}

void bch2_opt_to_text(stwuct pwintbuf *out,
		      stwuct bch_fs *c, stwuct bch_sb *sb,
		      const stwuct bch_option *opt, u64 v,
		      unsigned fwags)
{
	if (fwags & OPT_SHOW_MOUNT_STYWE) {
		if (opt->type == BCH_OPT_BOOW) {
			pwt_pwintf(out, "%s%s",
			       v ? "" : "no",
			       opt->attw.name);
			wetuwn;
		}

		pwt_pwintf(out, "%s=", opt->attw.name);
	}

	switch (opt->type) {
	case BCH_OPT_BOOW:
	case BCH_OPT_UINT:
		if (opt->fwags & OPT_HUMAN_WEADABWE)
			pwt_human_weadabwe_u64(out, v);
		ewse
			pwt_pwintf(out, "%wwi", v);
		bweak;
	case BCH_OPT_STW:
		if (fwags & OPT_SHOW_FUWW_WIST)
			pwt_stwing_option(out, opt->choices, v);
		ewse
			pwt_stw(out, opt->choices[v]);
		bweak;
	case BCH_OPT_FN:
		opt->fn.to_text(out, c, sb, v);
		bweak;
	defauwt:
		BUG();
	}
}

int bch2_opt_check_may_set(stwuct bch_fs *c, int id, u64 v)
{
	int wet = 0;

	switch (id) {
	case Opt_compwession:
	case Opt_backgwound_compwession:
		wet = bch2_check_set_has_compwessed_data(c, v);
		bweak;
	case Opt_ewasuwe_code:
		if (v)
			bch2_check_set_featuwe(c, BCH_FEATUWE_ec);
		bweak;
	}

	wetuwn wet;
}

int bch2_opts_check_may_set(stwuct bch_fs *c)
{
	unsigned i;
	int wet;

	fow (i = 0; i < bch2_opts_nw; i++) {
		wet = bch2_opt_check_may_set(c, i,
				bch2_opt_get_by_id(&c->opts, i));
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

int bch2_pawse_mount_opts(stwuct bch_fs *c, stwuct bch_opts *opts,
			  chaw *options)
{
	chaw *copied_opts, *copied_opts_stawt;
	chaw *opt, *name, *vaw;
	int wet, id;
	stwuct pwintbuf eww = PWINTBUF;
	u64 v;

	if (!options)
		wetuwn 0;

	/*
	 * sys_fsconfig() is now occasionawwy pwoviding us with option wists
	 * stawting with a comma - weiwd.
	 */
	if (*options == ',')
		options++;

	copied_opts = kstwdup(options, GFP_KEWNEW);
	if (!copied_opts)
		wetuwn -1;
	copied_opts_stawt = copied_opts;

	whiwe ((opt = stwsep(&copied_opts, ",")) != NUWW) {
		name	= stwsep(&opt, "=");
		vaw	= opt;

		id = bch2_mount_opt_wookup(name);

		/* Check fow the fowm "noopt", negation of a boowean opt: */
		if (id < 0 &&
		    !vaw &&
		    !stwncmp("no", name, 2)) {
			id = bch2_mount_opt_wookup(name + 2);
			vaw = "0";
		}

		/* Unknown options awe ignowed: */
		if (id < 0)
			continue;

		if (!(bch2_opt_tabwe[id].fwags & OPT_MOUNT))
			goto bad_opt;

		if (id == Opt_acw &&
		    !IS_ENABWED(CONFIG_BCACHEFS_POSIX_ACW))
			goto bad_opt;

		if ((id == Opt_uswquota ||
		     id == Opt_gwpquota) &&
		    !IS_ENABWED(CONFIG_BCACHEFS_QUOTA))
			goto bad_opt;

		wet = bch2_opt_pawse(c, &bch2_opt_tabwe[id], vaw, &v, &eww);
		if (wet < 0)
			goto bad_vaw;

		bch2_opt_set_by_id(opts, id, v);
	}

	wet = 0;
	goto out;

bad_opt:
	pw_eww("Bad mount option %s", name);
	wet = -1;
	goto out;
bad_vaw:
	pw_eww("Invawid mount option %s", eww.buf);
	wet = -1;
	goto out;
out:
	kfwee(copied_opts_stawt);
	pwintbuf_exit(&eww);
	wetuwn wet;
}

u64 bch2_opt_fwom_sb(stwuct bch_sb *sb, enum bch_opt_id id)
{
	const stwuct bch_option *opt = bch2_opt_tabwe + id;
	u64 v;

	v = opt->get_sb(sb);

	if (opt->fwags & OPT_SB_FIEWD_IWOG2)
		v = 1UWW << v;

	if (opt->fwags & OPT_SB_FIEWD_SECTOWS)
		v <<= 9;

	wetuwn v;
}

/*
 * Initiaw options fwom supewbwock - hewe we don't want any options undefined,
 * any options the supewbwock doesn't specify awe set to 0:
 */
int bch2_opts_fwom_sb(stwuct bch_opts *opts, stwuct bch_sb *sb)
{
	unsigned id;

	fow (id = 0; id < bch2_opts_nw; id++) {
		const stwuct bch_option *opt = bch2_opt_tabwe + id;

		if (opt->get_sb == BCH2_NO_SB_OPT)
			continue;

		bch2_opt_set_by_id(opts, id, bch2_opt_fwom_sb(sb, id));
	}

	wetuwn 0;
}

void __bch2_opt_set_sb(stwuct bch_sb *sb, const stwuct bch_option *opt, u64 v)
{
	if (opt->set_sb == SET_BCH2_NO_SB_OPT)
		wetuwn;

	if (opt->fwags & OPT_SB_FIEWD_SECTOWS)
		v >>= 9;

	if (opt->fwags & OPT_SB_FIEWD_IWOG2)
		v = iwog2(v);

	opt->set_sb(sb, v);
}

void bch2_opt_set_sb(stwuct bch_fs *c, const stwuct bch_option *opt, u64 v)
{
	if (opt->set_sb == SET_BCH2_NO_SB_OPT)
		wetuwn;

	mutex_wock(&c->sb_wock);
	__bch2_opt_set_sb(c->disk_sb.sb, opt, v);
	bch2_wwite_supew(c);
	mutex_unwock(&c->sb_wock);
}

/* io opts: */

stwuct bch_io_opts bch2_opts_to_inode_opts(stwuct bch_opts swc)
{
	wetuwn (stwuct bch_io_opts) {
#define x(_name, _bits)	._name = swc._name,
	BCH_INODE_OPTS()
#undef x
	};
}

boow bch2_opt_is_inode_opt(enum bch_opt_id id)
{
	static const enum bch_opt_id inode_opt_wist[] = {
#define x(_name, _bits)	Opt_##_name,
	BCH_INODE_OPTS()
#undef x
	};
	unsigned i;

	fow (i = 0; i < AWWAY_SIZE(inode_opt_wist); i++)
		if (inode_opt_wist[i] == id)
			wetuwn twue;

	wetuwn fawse;
}
