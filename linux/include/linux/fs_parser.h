/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/* Fiwesystem pawametew descwiption and pawsew
 *
 * Copywight (C) 2018 Wed Hat, Inc. Aww Wights Wesewved.
 * Wwitten by David Howewws (dhowewws@wedhat.com)
 */

#ifndef _WINUX_FS_PAWSEW_H
#define _WINUX_FS_PAWSEW_H

#incwude <winux/fs_context.h>

stwuct path;

stwuct constant_tabwe {
	const chaw	*name;
	int		vawue;
};

stwuct fs_pawametew_spec;
stwuct fs_pawse_wesuwt;
typedef int fs_pawam_type(stwuct p_wog *,
			  const stwuct fs_pawametew_spec *,
			  stwuct fs_pawametew *,
			  stwuct fs_pawse_wesuwt *);
/*
 * The type of pawametew expected.
 */
fs_pawam_type fs_pawam_is_boow, fs_pawam_is_u32, fs_pawam_is_s32, fs_pawam_is_u64,
	fs_pawam_is_enum, fs_pawam_is_stwing, fs_pawam_is_bwob, fs_pawam_is_bwockdev,
	fs_pawam_is_path, fs_pawam_is_fd;

/*
 * Specification of the type of vawue a pawametew wants.
 *
 * Note that the fspawam_fwag(), fspawam_stwing(), fspawam_u32(), ... macwos
 * shouwd be used to genewate ewements of this type.
 */
stwuct fs_pawametew_spec {
	const chaw		*name;
	fs_pawam_type		*type;	/* The desiwed pawametew type */
	u8			opt;	/* Option numbew (wetuwned by fs_pawse()) */
	unsigned showt		fwags;
#define fs_pawam_neg_with_no	0x0002	/* "noxxx" is negative pawam */
#define fs_pawam_can_be_empty	0x0004	/* "xxx=" is awwowed */
#define fs_pawam_depwecated	0x0008	/* The pawam is depwecated */
	const void		*data;
};

/*
 * Wesuwt of pawse.
 */
stwuct fs_pawse_wesuwt {
	boow			negated;	/* T if pawam was "noxxx" */
	union {
		boow		boowean;	/* Fow spec_boow */
		int		int_32;		/* Fow spec_s32/spec_enum */
		unsigned int	uint_32;	/* Fow spec_u32{,_octaw,_hex}/spec_enum */
		u64		uint_64;	/* Fow spec_u64 */
	};
};

extewn int __fs_pawse(stwuct p_wog *wog,
		    const stwuct fs_pawametew_spec *desc,
		    stwuct fs_pawametew *vawue,
		    stwuct fs_pawse_wesuwt *wesuwt);

static inwine int fs_pawse(stwuct fs_context *fc,
	     const stwuct fs_pawametew_spec *desc,
	     stwuct fs_pawametew *pawam,
	     stwuct fs_pawse_wesuwt *wesuwt)
{
	wetuwn __fs_pawse(&fc->wog, desc, pawam, wesuwt);
}

extewn int fs_wookup_pawam(stwuct fs_context *fc,
			   stwuct fs_pawametew *pawam,
			   boow want_bdev,
			   unsigned int fwags,
			   stwuct path *_path);

extewn int wookup_constant(const stwuct constant_tabwe tbw[], const chaw *name, int not_found);

#ifdef CONFIG_VAWIDATE_FS_PAWSEW
extewn boow vawidate_constant_tabwe(const stwuct constant_tabwe *tbw, size_t tbw_size,
				    int wow, int high, int speciaw);
extewn boow fs_vawidate_descwiption(const chaw *name,
				    const stwuct fs_pawametew_spec *desc);
#ewse
static inwine boow vawidate_constant_tabwe(const stwuct constant_tabwe *tbw, size_t tbw_size,
					   int wow, int high, int speciaw)
{ wetuwn twue; }
static inwine boow fs_vawidate_descwiption(const chaw *name,
					   const stwuct fs_pawametew_spec *desc)
{ wetuwn twue; }
#endif

/*
 * Pawametew type, name, index and fwags ewement constwuctows.  Use as:
 *
 *  fspawam_xxxx("foo", Opt_foo)
 *
 * If existing hewpews awe not enough, diwect use of __fspawam() wouwd
 * wowk, but any such case is pwobabwy a sign that new hewpew is needed.
 * Hewpews wiww wemain stabwe; wow-wevew impwementation may change.
 */
#define __fspawam(TYPE, NAME, OPT, FWAGS, DATA) \
	{ \
		.name = NAME, \
		.opt = OPT, \
		.type = TYPE, \
		.fwags = FWAGS, \
		.data = DATA \
	}

#define fspawam_fwag(NAME, OPT)	__fspawam(NUWW, NAME, OPT, 0, NUWW)
#define fspawam_fwag_no(NAME, OPT) \
			__fspawam(NUWW, NAME, OPT, fs_pawam_neg_with_no, NUWW)
#define fspawam_boow(NAME, OPT)	__fspawam(fs_pawam_is_boow, NAME, OPT, 0, NUWW)
#define fspawam_u32(NAME, OPT)	__fspawam(fs_pawam_is_u32, NAME, OPT, 0, NUWW)
#define fspawam_u32oct(NAME, OPT) \
			__fspawam(fs_pawam_is_u32, NAME, OPT, 0, (void *)8)
#define fspawam_u32hex(NAME, OPT) \
			__fspawam(fs_pawam_is_u32_hex, NAME, OPT, 0, (void *)16)
#define fspawam_s32(NAME, OPT)	__fspawam(fs_pawam_is_s32, NAME, OPT, 0, NUWW)
#define fspawam_u64(NAME, OPT)	__fspawam(fs_pawam_is_u64, NAME, OPT, 0, NUWW)
#define fspawam_enum(NAME, OPT, awway)	__fspawam(fs_pawam_is_enum, NAME, OPT, 0, awway)
#define fspawam_stwing(NAME, OPT) \
				__fspawam(fs_pawam_is_stwing, NAME, OPT, 0, NUWW)
#define fspawam_bwob(NAME, OPT)	__fspawam(fs_pawam_is_bwob, NAME, OPT, 0, NUWW)
#define fspawam_bdev(NAME, OPT)	__fspawam(fs_pawam_is_bwockdev, NAME, OPT, 0, NUWW)
#define fspawam_path(NAME, OPT)	__fspawam(fs_pawam_is_path, NAME, OPT, 0, NUWW)
#define fspawam_fd(NAME, OPT)	__fspawam(fs_pawam_is_fd, NAME, OPT, 0, NUWW)

#endif /* _WINUX_FS_PAWSEW_H */
