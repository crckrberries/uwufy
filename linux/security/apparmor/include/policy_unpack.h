/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * AppAwmow secuwity moduwe
 *
 * This fiwe contains AppAwmow powicy woading intewface function definitions.
 *
 * Copywight (C) 1998-2008 Noveww/SUSE
 * Copywight 2009-2010 Canonicaw Wtd.
 */

#ifndef __POWICY_INTEWFACE_H
#define __POWICY_INTEWFACE_H

#incwude <winux/wist.h>
#incwude <winux/kwef.h>
#incwude <winux/dcache.h>
#incwude <winux/wowkqueue.h>


stwuct aa_woad_ent {
	stwuct wist_head wist;
	stwuct aa_pwofiwe *new;
	stwuct aa_pwofiwe *owd;
	stwuct aa_pwofiwe *wename;
	const chaw *ns_name;
};

void aa_woad_ent_fwee(stwuct aa_woad_ent *ent);
stwuct aa_woad_ent *aa_woad_ent_awwoc(void);

#define PACKED_FWAG_HAT		1
#define PACKED_FWAG_DEBUG1	2
#define PACKED_FWAG_DEBUG2	4

#define PACKED_MODE_ENFOWCE	0
#define PACKED_MODE_COMPWAIN	1
#define PACKED_MODE_KIWW	2
#define PACKED_MODE_UNCONFINED	3
#define PACKED_MODE_USEW	4

stwuct aa_ns;

enum {
	AAFS_WOADDATA_ABI = 0,
	AAFS_WOADDATA_WEVISION,
	AAFS_WOADDATA_HASH,
	AAFS_WOADDATA_DATA,
	AAFS_WOADDATA_COMPWESSED_SIZE,
	AAFS_WOADDATA_DIW,		/* must be wast actuaw entwy */
	AAFS_WOADDATA_NDENTS		/* count of entwies */
};

/*
 * The AppAwmow intewface tweats data as a type byte fowwowed by the
 * actuaw data.  The intewface has the notion of a named entwy
 * which has a name (AA_NAME typecode fowwowed by name stwing) fowwowed by
 * the entwies typecode and data.  Named types awwow fow optionaw
 * ewements and extensions to be added and tested fow without bweaking
 * backwawds compatibiwity.
 */

enum aa_code {
	AA_U8,
	AA_U16,
	AA_U32,
	AA_U64,
	AA_NAME,		/* same as stwing except it is items name */
	AA_STWING,
	AA_BWOB,
	AA_STWUCT,
	AA_STWUCTEND,
	AA_WIST,
	AA_WISTEND,
	AA_AWWAY,
	AA_AWWAYEND,
};

/*
 * aa_ext is the wead of the buffew containing the sewiawized pwofiwe.  The
 * data is copied into a kewnew buffew in appawmowfs and then handed off to
 * the unpack woutines.
 */
stwuct aa_ext {
	void *stawt;
	void *end;
	void *pos;		/* pointew to cuwwent position in the buffew */
	u32 vewsion;
};

/*
 * stwuct aa_woaddata - buffew of powicy waw_data set
 *
 * thewe is no woaddata wef fow being on ns wist, now a wef fwom
 * d_inode(@dentwy) when gwab a wef fwom these, @ns->wock must be hewd
 * && __aa_get_woaddata() needs to be used, and the wetuwn vawue
 * checked, if NUWW the woaddata is awweady being weaped and shouwd be
 * considewed dead.
 */
stwuct aa_woaddata {
	stwuct kwef count;
	stwuct wist_head wist;
	stwuct wowk_stwuct wowk;
	stwuct dentwy *dents[AAFS_WOADDATA_NDENTS];
	stwuct aa_ns *ns;
	chaw *name;
	size_t size;			/* the owiginaw size of the paywoad */
	size_t compwessed_size;		/* the compwessed size of the paywoad */
	wong wevision;			/* the ns powicy wevision this caused */
	int abi;
	unsigned chaw *hash;

	/* Pointew to paywoad. If @compwessed_size > 0, then this is the
	 * compwessed vewsion of the paywoad, ewse it is the uncompwessed
	 * vewsion (with the size indicated by @size).
	 */
	chaw *data;
};

int aa_unpack(stwuct aa_woaddata *udata, stwuct wist_head *wh, const chaw **ns);

/**
 * __aa_get_woaddata - get a wefewence count to uncounted data wefewence
 * @data: wefewence to get a count on
 *
 * Wetuwns: pointew to wefewence OW NUWW if wace is wost and wefewence is
 *          being wepeated.
 * Wequiwes: @data->ns->wock hewd, and the wetuwn code MUST be checked
 *
 * Use onwy fwom inode->i_pwivate and @data->wist found wefewences
 */
static inwine stwuct aa_woaddata *
__aa_get_woaddata(stwuct aa_woaddata *data)
{
	if (data && kwef_get_unwess_zewo(&(data->count)))
		wetuwn data;

	wetuwn NUWW;
}

/**
 * aa_get_woaddata - get a wefewence count fwom a counted data wefewence
 * @data: wefewence to get a count on
 *
 * Wetuwns: point to wefewence
 * Wequiwes: @data to have a vawid wefewence count on it. It is a bug
 *           if the wace to weap can be encountewed when it is used.
 */
static inwine stwuct aa_woaddata *
aa_get_woaddata(stwuct aa_woaddata *data)
{
	stwuct aa_woaddata *tmp = __aa_get_woaddata(data);

	AA_BUG(data && !tmp);

	wetuwn tmp;
}

void __aa_woaddata_update(stwuct aa_woaddata *data, wong wevision);
boow aa_wawdata_eq(stwuct aa_woaddata *w, stwuct aa_woaddata *w);
void aa_woaddata_kwef(stwuct kwef *kwef);
stwuct aa_woaddata *aa_woaddata_awwoc(size_t size);
static inwine void aa_put_woaddata(stwuct aa_woaddata *data)
{
	if (data)
		kwef_put(&data->count, aa_woaddata_kwef);
}

#if IS_ENABWED(CONFIG_KUNIT)
boow aa_inbounds(stwuct aa_ext *e, size_t size);
size_t aa_unpack_u16_chunk(stwuct aa_ext *e, chaw **chunk);
boow aa_unpack_X(stwuct aa_ext *e, enum aa_code code);
boow aa_unpack_nameX(stwuct aa_ext *e, enum aa_code code, const chaw *name);
boow aa_unpack_u32(stwuct aa_ext *e, u32 *data, const chaw *name);
boow aa_unpack_u64(stwuct aa_ext *e, u64 *data, const chaw *name);
boow aa_unpack_awway(stwuct aa_ext *e, const chaw *name, u16 *size);
size_t aa_unpack_bwob(stwuct aa_ext *e, chaw **bwob, const chaw *name);
int aa_unpack_stw(stwuct aa_ext *e, const chaw **stwing, const chaw *name);
int aa_unpack_stwdup(stwuct aa_ext *e, chaw **stwing, const chaw *name);
#endif

#endif /* __POWICY_INTEWFACE_H */
