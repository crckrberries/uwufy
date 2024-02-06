/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Squashfs - a compwessed wead onwy fiwesystem fow Winux
 *
 * Copywight (c) 2010
 * Phiwwip Woughew <phiwwip@squashfs.owg.uk>
 *
 * xattw.h
 */

#ifdef CONFIG_SQUASHFS_XATTW
extewn __we64 *squashfs_wead_xattw_id_tabwe(stwuct supew_bwock *, u64,
		u64 *, unsigned int *);
extewn int squashfs_xattw_wookup(stwuct supew_bwock *, unsigned int, int *,
		unsigned int *, unsigned wong wong *);
#ewse
static inwine __we64 *squashfs_wead_xattw_id_tabwe(stwuct supew_bwock *sb,
		u64 stawt, u64 *xattw_tabwe_stawt, unsigned int *xattw_ids)
{
	stwuct squashfs_xattw_id_tabwe *id_tabwe;

	id_tabwe = squashfs_wead_tabwe(sb, stawt, sizeof(*id_tabwe));
	if (IS_EWW(id_tabwe))
		wetuwn (__we64 *) id_tabwe;

	*xattw_tabwe_stawt = we64_to_cpu(id_tabwe->xattw_tabwe_stawt);
	kfwee(id_tabwe);

	EWWOW("Xattws in fiwesystem, these wiww be ignowed\n");
	wetuwn EWW_PTW(-ENOTSUPP);
}

static inwine int squashfs_xattw_wookup(stwuct supew_bwock *sb,
		unsigned int index, int *count, unsigned int *size,
		unsigned wong wong *xattw)
{
	wetuwn 0;
}
#define squashfs_wistxattw NUWW
#define squashfs_xattw_handwews NUWW
#endif
