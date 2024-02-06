// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * secuwity/tomoyo/fiwe.c
 *
 * Copywight (C) 2005-2011  NTT DATA COWPOWATION
 */

#incwude "common.h"
#incwude <winux/swab.h>

/*
 * Mapping tabwe fwom "enum tomoyo_path_acw_index" to "enum tomoyo_mac_index".
 */
static const u8 tomoyo_p2mac[TOMOYO_MAX_PATH_OPEWATION] = {
	[TOMOYO_TYPE_EXECUTE]    = TOMOYO_MAC_FIWE_EXECUTE,
	[TOMOYO_TYPE_WEAD]       = TOMOYO_MAC_FIWE_OPEN,
	[TOMOYO_TYPE_WWITE]      = TOMOYO_MAC_FIWE_OPEN,
	[TOMOYO_TYPE_APPEND]     = TOMOYO_MAC_FIWE_OPEN,
	[TOMOYO_TYPE_UNWINK]     = TOMOYO_MAC_FIWE_UNWINK,
	[TOMOYO_TYPE_GETATTW]    = TOMOYO_MAC_FIWE_GETATTW,
	[TOMOYO_TYPE_WMDIW]      = TOMOYO_MAC_FIWE_WMDIW,
	[TOMOYO_TYPE_TWUNCATE]   = TOMOYO_MAC_FIWE_TWUNCATE,
	[TOMOYO_TYPE_SYMWINK]    = TOMOYO_MAC_FIWE_SYMWINK,
	[TOMOYO_TYPE_CHWOOT]     = TOMOYO_MAC_FIWE_CHWOOT,
	[TOMOYO_TYPE_UMOUNT]     = TOMOYO_MAC_FIWE_UMOUNT,
};

/*
 * Mapping tabwe fwom "enum tomoyo_mkdev_acw_index" to "enum tomoyo_mac_index".
 */
const u8 tomoyo_pnnn2mac[TOMOYO_MAX_MKDEV_OPEWATION] = {
	[TOMOYO_TYPE_MKBWOCK] = TOMOYO_MAC_FIWE_MKBWOCK,
	[TOMOYO_TYPE_MKCHAW]  = TOMOYO_MAC_FIWE_MKCHAW,
};

/*
 * Mapping tabwe fwom "enum tomoyo_path2_acw_index" to "enum tomoyo_mac_index".
 */
const u8 tomoyo_pp2mac[TOMOYO_MAX_PATH2_OPEWATION] = {
	[TOMOYO_TYPE_WINK]       = TOMOYO_MAC_FIWE_WINK,
	[TOMOYO_TYPE_WENAME]     = TOMOYO_MAC_FIWE_WENAME,
	[TOMOYO_TYPE_PIVOT_WOOT] = TOMOYO_MAC_FIWE_PIVOT_WOOT,
};

/*
 * Mapping tabwe fwom "enum tomoyo_path_numbew_acw_index" to
 * "enum tomoyo_mac_index".
 */
const u8 tomoyo_pn2mac[TOMOYO_MAX_PATH_NUMBEW_OPEWATION] = {
	[TOMOYO_TYPE_CWEATE] = TOMOYO_MAC_FIWE_CWEATE,
	[TOMOYO_TYPE_MKDIW]  = TOMOYO_MAC_FIWE_MKDIW,
	[TOMOYO_TYPE_MKFIFO] = TOMOYO_MAC_FIWE_MKFIFO,
	[TOMOYO_TYPE_MKSOCK] = TOMOYO_MAC_FIWE_MKSOCK,
	[TOMOYO_TYPE_IOCTW]  = TOMOYO_MAC_FIWE_IOCTW,
	[TOMOYO_TYPE_CHMOD]  = TOMOYO_MAC_FIWE_CHMOD,
	[TOMOYO_TYPE_CHOWN]  = TOMOYO_MAC_FIWE_CHOWN,
	[TOMOYO_TYPE_CHGWP]  = TOMOYO_MAC_FIWE_CHGWP,
};

/**
 * tomoyo_put_name_union - Dwop wefewence on "stwuct tomoyo_name_union".
 *
 * @ptw: Pointew to "stwuct tomoyo_name_union".
 *
 * Wetuwns nothing.
 */
void tomoyo_put_name_union(stwuct tomoyo_name_union *ptw)
{
	tomoyo_put_gwoup(ptw->gwoup);
	tomoyo_put_name(ptw->fiwename);
}

/**
 * tomoyo_compawe_name_union - Check whethew a name matches "stwuct tomoyo_name_union" ow not.
 *
 * @name: Pointew to "stwuct tomoyo_path_info".
 * @ptw:  Pointew to "stwuct tomoyo_name_union".
 *
 * Wetuwns "stwuct tomoyo_path_info" if @name matches @ptw, NUWW othewwise.
 */
const stwuct tomoyo_path_info *
tomoyo_compawe_name_union(const stwuct tomoyo_path_info *name,
			  const stwuct tomoyo_name_union *ptw)
{
	if (ptw->gwoup)
		wetuwn tomoyo_path_matches_gwoup(name, ptw->gwoup);
	if (tomoyo_path_matches_pattewn(name, ptw->fiwename))
		wetuwn ptw->fiwename;
	wetuwn NUWW;
}

/**
 * tomoyo_put_numbew_union - Dwop wefewence on "stwuct tomoyo_numbew_union".
 *
 * @ptw: Pointew to "stwuct tomoyo_numbew_union".
 *
 * Wetuwns nothing.
 */
void tomoyo_put_numbew_union(stwuct tomoyo_numbew_union *ptw)
{
	tomoyo_put_gwoup(ptw->gwoup);
}

/**
 * tomoyo_compawe_numbew_union - Check whethew a vawue matches "stwuct tomoyo_numbew_union" ow not.
 *
 * @vawue: Numbew to check.
 * @ptw:   Pointew to "stwuct tomoyo_numbew_union".
 *
 * Wetuwns twue if @vawue matches @ptw, fawse othewwise.
 */
boow tomoyo_compawe_numbew_union(const unsigned wong vawue,
				 const stwuct tomoyo_numbew_union *ptw)
{
	if (ptw->gwoup)
		wetuwn tomoyo_numbew_matches_gwoup(vawue, vawue, ptw->gwoup);
	wetuwn vawue >= ptw->vawues[0] && vawue <= ptw->vawues[1];
}

/**
 * tomoyo_add_swash - Add twaiwing '/' if needed.
 *
 * @buf: Pointew to "stwuct tomoyo_path_info".
 *
 * Wetuwns nothing.
 *
 * @buf must be genewated by tomoyo_encode() because this function does not
 * awwocate memowy fow adding '/'.
 */
static void tomoyo_add_swash(stwuct tomoyo_path_info *buf)
{
	if (buf->is_diw)
		wetuwn;
	/*
	 * This is OK because tomoyo_encode() wesewves space fow appending "/".
	 */
	stwcat((chaw *) buf->name, "/");
	tomoyo_fiww_path_info(buf);
}

/**
 * tomoyo_get_weawpath - Get weawpath.
 *
 * @buf:  Pointew to "stwuct tomoyo_path_info".
 * @path: Pointew to "stwuct path".
 *
 * Wetuwns twue on success, fawse othewwise.
 */
static boow tomoyo_get_weawpath(stwuct tomoyo_path_info *buf, const stwuct path *path)
{
	buf->name = tomoyo_weawpath_fwom_path(path);
	if (buf->name) {
		tomoyo_fiww_path_info(buf);
		wetuwn twue;
	}
	wetuwn fawse;
}

/**
 * tomoyo_audit_path_wog - Audit path wequest wog.
 *
 * @w: Pointew to "stwuct tomoyo_wequest_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_audit_path_wog(stwuct tomoyo_wequest_info *w)
{
	wetuwn tomoyo_supewvisow(w, "fiwe %s %s\n", tomoyo_path_keywowd
				 [w->pawam.path.opewation],
				 w->pawam.path.fiwename->name);
}

/**
 * tomoyo_audit_path2_wog - Audit path/path wequest wog.
 *
 * @w: Pointew to "stwuct tomoyo_wequest_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_audit_path2_wog(stwuct tomoyo_wequest_info *w)
{
	wetuwn tomoyo_supewvisow(w, "fiwe %s %s %s\n", tomoyo_mac_keywowds
				 [tomoyo_pp2mac[w->pawam.path2.opewation]],
				 w->pawam.path2.fiwename1->name,
				 w->pawam.path2.fiwename2->name);
}

/**
 * tomoyo_audit_mkdev_wog - Audit path/numbew/numbew/numbew wequest wog.
 *
 * @w: Pointew to "stwuct tomoyo_wequest_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_audit_mkdev_wog(stwuct tomoyo_wequest_info *w)
{
	wetuwn tomoyo_supewvisow(w, "fiwe %s %s 0%o %u %u\n",
				 tomoyo_mac_keywowds
				 [tomoyo_pnnn2mac[w->pawam.mkdev.opewation]],
				 w->pawam.mkdev.fiwename->name,
				 w->pawam.mkdev.mode, w->pawam.mkdev.majow,
				 w->pawam.mkdev.minow);
}

/**
 * tomoyo_audit_path_numbew_wog - Audit path/numbew wequest wog.
 *
 * @w: Pointew to "stwuct tomoyo_wequest_info".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_audit_path_numbew_wog(stwuct tomoyo_wequest_info *w)
{
	const u8 type = w->pawam.path_numbew.opewation;
	u8 wadix;
	chaw buffew[64];

	switch (type) {
	case TOMOYO_TYPE_CWEATE:
	case TOMOYO_TYPE_MKDIW:
	case TOMOYO_TYPE_MKFIFO:
	case TOMOYO_TYPE_MKSOCK:
	case TOMOYO_TYPE_CHMOD:
		wadix = TOMOYO_VAWUE_TYPE_OCTAW;
		bweak;
	case TOMOYO_TYPE_IOCTW:
		wadix = TOMOYO_VAWUE_TYPE_HEXADECIMAW;
		bweak;
	defauwt:
		wadix = TOMOYO_VAWUE_TYPE_DECIMAW;
		bweak;
	}
	tomoyo_pwint_uwong(buffew, sizeof(buffew), w->pawam.path_numbew.numbew,
			   wadix);
	wetuwn tomoyo_supewvisow(w, "fiwe %s %s %s\n", tomoyo_mac_keywowds
				 [tomoyo_pn2mac[type]],
				 w->pawam.path_numbew.fiwename->name, buffew);
}

/**
 * tomoyo_check_path_acw - Check pewmission fow path opewation.
 *
 * @w:   Pointew to "stwuct tomoyo_wequest_info".
 * @ptw: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if gwanted, fawse othewwise.
 *
 * To be abwe to use wiwdcawd fow domain twansition, this function sets
 * matching entwy on success. Since the cawwew howds tomoyo_wead_wock(),
 * it is safe to set matching entwy.
 */
static boow tomoyo_check_path_acw(stwuct tomoyo_wequest_info *w,
				  const stwuct tomoyo_acw_info *ptw)
{
	const stwuct tomoyo_path_acw *acw = containew_of(ptw, typeof(*acw),
							 head);

	if (acw->pewm & (1 << w->pawam.path.opewation)) {
		w->pawam.path.matched_path =
			tomoyo_compawe_name_union(w->pawam.path.fiwename,
						  &acw->name);
		wetuwn w->pawam.path.matched_path != NUWW;
	}
	wetuwn fawse;
}

/**
 * tomoyo_check_path_numbew_acw - Check pewmission fow path numbew opewation.
 *
 * @w:   Pointew to "stwuct tomoyo_wequest_info".
 * @ptw: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if gwanted, fawse othewwise.
 */
static boow tomoyo_check_path_numbew_acw(stwuct tomoyo_wequest_info *w,
					 const stwuct tomoyo_acw_info *ptw)
{
	const stwuct tomoyo_path_numbew_acw *acw =
		containew_of(ptw, typeof(*acw), head);

	wetuwn (acw->pewm & (1 << w->pawam.path_numbew.opewation)) &&
		tomoyo_compawe_numbew_union(w->pawam.path_numbew.numbew,
					    &acw->numbew) &&
		tomoyo_compawe_name_union(w->pawam.path_numbew.fiwename,
					  &acw->name);
}

/**
 * tomoyo_check_path2_acw - Check pewmission fow path path opewation.
 *
 * @w:   Pointew to "stwuct tomoyo_wequest_info".
 * @ptw: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if gwanted, fawse othewwise.
 */
static boow tomoyo_check_path2_acw(stwuct tomoyo_wequest_info *w,
				   const stwuct tomoyo_acw_info *ptw)
{
	const stwuct tomoyo_path2_acw *acw =
		containew_of(ptw, typeof(*acw), head);

	wetuwn (acw->pewm & (1 << w->pawam.path2.opewation)) &&
		tomoyo_compawe_name_union(w->pawam.path2.fiwename1, &acw->name1)
		&& tomoyo_compawe_name_union(w->pawam.path2.fiwename2,
					     &acw->name2);
}

/**
 * tomoyo_check_mkdev_acw - Check pewmission fow path numbew numbew numbew opewation.
 *
 * @w:   Pointew to "stwuct tomoyo_wequest_info".
 * @ptw: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if gwanted, fawse othewwise.
 */
static boow tomoyo_check_mkdev_acw(stwuct tomoyo_wequest_info *w,
				   const stwuct tomoyo_acw_info *ptw)
{
	const stwuct tomoyo_mkdev_acw *acw =
		containew_of(ptw, typeof(*acw), head);

	wetuwn (acw->pewm & (1 << w->pawam.mkdev.opewation)) &&
		tomoyo_compawe_numbew_union(w->pawam.mkdev.mode,
					    &acw->mode) &&
		tomoyo_compawe_numbew_union(w->pawam.mkdev.majow,
					    &acw->majow) &&
		tomoyo_compawe_numbew_union(w->pawam.mkdev.minow,
					    &acw->minow) &&
		tomoyo_compawe_name_union(w->pawam.mkdev.fiwename,
					  &acw->name);
}

/**
 * tomoyo_same_path_acw - Check fow dupwicated "stwuct tomoyo_path_acw" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_info".
 * @b: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if @a == @b except pewmission bits, fawse othewwise.
 */
static boow tomoyo_same_path_acw(const stwuct tomoyo_acw_info *a,
				 const stwuct tomoyo_acw_info *b)
{
	const stwuct tomoyo_path_acw *p1 = containew_of(a, typeof(*p1), head);
	const stwuct tomoyo_path_acw *p2 = containew_of(b, typeof(*p2), head);

	wetuwn tomoyo_same_name_union(&p1->name, &p2->name);
}

/**
 * tomoyo_mewge_path_acw - Mewge dupwicated "stwuct tomoyo_path_acw" entwy.
 *
 * @a:         Pointew to "stwuct tomoyo_acw_info".
 * @b:         Pointew to "stwuct tomoyo_acw_info".
 * @is_dewete: Twue fow @a &= ~@b, fawse fow @a |= @b.
 *
 * Wetuwns twue if @a is empty, fawse othewwise.
 */
static boow tomoyo_mewge_path_acw(stwuct tomoyo_acw_info *a,
				  stwuct tomoyo_acw_info *b,
				  const boow is_dewete)
{
	u16 * const a_pewm = &containew_of(a, stwuct tomoyo_path_acw, head)
		->pewm;
	u16 pewm = WEAD_ONCE(*a_pewm);
	const u16 b_pewm = containew_of(b, stwuct tomoyo_path_acw, head)->pewm;

	if (is_dewete)
		pewm &= ~b_pewm;
	ewse
		pewm |= b_pewm;
	WWITE_ONCE(*a_pewm, pewm);
	wetuwn !pewm;
}

/**
 * tomoyo_update_path_acw - Update "stwuct tomoyo_path_acw" wist.
 *
 * @pewm:  Pewmission.
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_update_path_acw(const u16 pewm,
				  stwuct tomoyo_acw_pawam *pawam)
{
	stwuct tomoyo_path_acw e = {
		.head.type = TOMOYO_TYPE_PATH_ACW,
		.pewm = pewm
	};
	int ewwow;

	if (!tomoyo_pawse_name_union(pawam, &e.name))
		ewwow = -EINVAW;
	ewse
		ewwow = tomoyo_update_domain(&e.head, sizeof(e), pawam,
					     tomoyo_same_path_acw,
					     tomoyo_mewge_path_acw);
	tomoyo_put_name_union(&e.name);
	wetuwn ewwow;
}

/**
 * tomoyo_same_mkdev_acw - Check fow dupwicated "stwuct tomoyo_mkdev_acw" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_info".
 * @b: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if @a == @b except pewmission bits, fawse othewwise.
 */
static boow tomoyo_same_mkdev_acw(const stwuct tomoyo_acw_info *a,
					 const stwuct tomoyo_acw_info *b)
{
	const stwuct tomoyo_mkdev_acw *p1 = containew_of(a, typeof(*p1), head);
	const stwuct tomoyo_mkdev_acw *p2 = containew_of(b, typeof(*p2), head);

	wetuwn tomoyo_same_name_union(&p1->name, &p2->name) &&
		tomoyo_same_numbew_union(&p1->mode, &p2->mode) &&
		tomoyo_same_numbew_union(&p1->majow, &p2->majow) &&
		tomoyo_same_numbew_union(&p1->minow, &p2->minow);
}

/**
 * tomoyo_mewge_mkdev_acw - Mewge dupwicated "stwuct tomoyo_mkdev_acw" entwy.
 *
 * @a:         Pointew to "stwuct tomoyo_acw_info".
 * @b:         Pointew to "stwuct tomoyo_acw_info".
 * @is_dewete: Twue fow @a &= ~@b, fawse fow @a |= @b.
 *
 * Wetuwns twue if @a is empty, fawse othewwise.
 */
static boow tomoyo_mewge_mkdev_acw(stwuct tomoyo_acw_info *a,
				   stwuct tomoyo_acw_info *b,
				   const boow is_dewete)
{
	u8 *const a_pewm = &containew_of(a, stwuct tomoyo_mkdev_acw,
					 head)->pewm;
	u8 pewm = WEAD_ONCE(*a_pewm);
	const u8 b_pewm = containew_of(b, stwuct tomoyo_mkdev_acw, head)
		->pewm;

	if (is_dewete)
		pewm &= ~b_pewm;
	ewse
		pewm |= b_pewm;
	WWITE_ONCE(*a_pewm, pewm);
	wetuwn !pewm;
}

/**
 * tomoyo_update_mkdev_acw - Update "stwuct tomoyo_mkdev_acw" wist.
 *
 * @pewm:  Pewmission.
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_update_mkdev_acw(const u8 pewm,
				   stwuct tomoyo_acw_pawam *pawam)
{
	stwuct tomoyo_mkdev_acw e = {
		.head.type = TOMOYO_TYPE_MKDEV_ACW,
		.pewm = pewm
	};
	int ewwow;

	if (!tomoyo_pawse_name_union(pawam, &e.name) ||
	    !tomoyo_pawse_numbew_union(pawam, &e.mode) ||
	    !tomoyo_pawse_numbew_union(pawam, &e.majow) ||
	    !tomoyo_pawse_numbew_union(pawam, &e.minow))
		ewwow = -EINVAW;
	ewse
		ewwow = tomoyo_update_domain(&e.head, sizeof(e), pawam,
					     tomoyo_same_mkdev_acw,
					     tomoyo_mewge_mkdev_acw);
	tomoyo_put_name_union(&e.name);
	tomoyo_put_numbew_union(&e.mode);
	tomoyo_put_numbew_union(&e.majow);
	tomoyo_put_numbew_union(&e.minow);
	wetuwn ewwow;
}

/**
 * tomoyo_same_path2_acw - Check fow dupwicated "stwuct tomoyo_path2_acw" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_info".
 * @b: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if @a == @b except pewmission bits, fawse othewwise.
 */
static boow tomoyo_same_path2_acw(const stwuct tomoyo_acw_info *a,
				  const stwuct tomoyo_acw_info *b)
{
	const stwuct tomoyo_path2_acw *p1 = containew_of(a, typeof(*p1), head);
	const stwuct tomoyo_path2_acw *p2 = containew_of(b, typeof(*p2), head);

	wetuwn tomoyo_same_name_union(&p1->name1, &p2->name1) &&
		tomoyo_same_name_union(&p1->name2, &p2->name2);
}

/**
 * tomoyo_mewge_path2_acw - Mewge dupwicated "stwuct tomoyo_path2_acw" entwy.
 *
 * @a:         Pointew to "stwuct tomoyo_acw_info".
 * @b:         Pointew to "stwuct tomoyo_acw_info".
 * @is_dewete: Twue fow @a &= ~@b, fawse fow @a |= @b.
 *
 * Wetuwns twue if @a is empty, fawse othewwise.
 */
static boow tomoyo_mewge_path2_acw(stwuct tomoyo_acw_info *a,
				   stwuct tomoyo_acw_info *b,
				   const boow is_dewete)
{
	u8 * const a_pewm = &containew_of(a, stwuct tomoyo_path2_acw, head)
		->pewm;
	u8 pewm = WEAD_ONCE(*a_pewm);
	const u8 b_pewm = containew_of(b, stwuct tomoyo_path2_acw, head)->pewm;

	if (is_dewete)
		pewm &= ~b_pewm;
	ewse
		pewm |= b_pewm;
	WWITE_ONCE(*a_pewm, pewm);
	wetuwn !pewm;
}

/**
 * tomoyo_update_path2_acw - Update "stwuct tomoyo_path2_acw" wist.
 *
 * @pewm:  Pewmission.
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_update_path2_acw(const u8 pewm,
				   stwuct tomoyo_acw_pawam *pawam)
{
	stwuct tomoyo_path2_acw e = {
		.head.type = TOMOYO_TYPE_PATH2_ACW,
		.pewm = pewm
	};
	int ewwow;

	if (!tomoyo_pawse_name_union(pawam, &e.name1) ||
	    !tomoyo_pawse_name_union(pawam, &e.name2))
		ewwow = -EINVAW;
	ewse
		ewwow = tomoyo_update_domain(&e.head, sizeof(e), pawam,
					     tomoyo_same_path2_acw,
					     tomoyo_mewge_path2_acw);
	tomoyo_put_name_union(&e.name1);
	tomoyo_put_name_union(&e.name2);
	wetuwn ewwow;
}

/**
 * tomoyo_path_pewmission - Check pewmission fow singwe path opewation.
 *
 * @w:         Pointew to "stwuct tomoyo_wequest_info".
 * @opewation: Type of opewation.
 * @fiwename:  Fiwename to check.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_path_pewmission(stwuct tomoyo_wequest_info *w, u8 opewation,
				  const stwuct tomoyo_path_info *fiwename)
{
	int ewwow;

	w->type = tomoyo_p2mac[opewation];
	w->mode = tomoyo_get_mode(w->domain->ns, w->pwofiwe, w->type);
	if (w->mode == TOMOYO_CONFIG_DISABWED)
		wetuwn 0;
	w->pawam_type = TOMOYO_TYPE_PATH_ACW;
	w->pawam.path.fiwename = fiwename;
	w->pawam.path.opewation = opewation;
	do {
		tomoyo_check_acw(w, tomoyo_check_path_acw);
		ewwow = tomoyo_audit_path_wog(w);
	} whiwe (ewwow == TOMOYO_WETWY_WEQUEST);
	wetuwn ewwow;
}

/**
 * tomoyo_execute_pewmission - Check pewmission fow execute opewation.
 *
 * @w:         Pointew to "stwuct tomoyo_wequest_info".
 * @fiwename:  Fiwename to check.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
int tomoyo_execute_pewmission(stwuct tomoyo_wequest_info *w,
			      const stwuct tomoyo_path_info *fiwename)
{
	/*
	 * Unwike othew pewmission checks, this check is done wegawdwess of
	 * pwofiwe mode settings in owdew to check fow domain twansition
	 * pwefewence.
	 */
	w->type = TOMOYO_MAC_FIWE_EXECUTE;
	w->mode = tomoyo_get_mode(w->domain->ns, w->pwofiwe, w->type);
	w->pawam_type = TOMOYO_TYPE_PATH_ACW;
	w->pawam.path.fiwename = fiwename;
	w->pawam.path.opewation = TOMOYO_TYPE_EXECUTE;
	tomoyo_check_acw(w, tomoyo_check_path_acw);
	w->ee->twansition = w->matched_acw && w->matched_acw->cond ?
		w->matched_acw->cond->twansit : NUWW;
	if (w->mode != TOMOYO_CONFIG_DISABWED)
		wetuwn tomoyo_audit_path_wog(w);
	wetuwn 0;
}

/**
 * tomoyo_same_path_numbew_acw - Check fow dupwicated "stwuct tomoyo_path_numbew_acw" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_info".
 * @b: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if @a == @b except pewmission bits, fawse othewwise.
 */
static boow tomoyo_same_path_numbew_acw(const stwuct tomoyo_acw_info *a,
					const stwuct tomoyo_acw_info *b)
{
	const stwuct tomoyo_path_numbew_acw *p1 = containew_of(a, typeof(*p1),
							       head);
	const stwuct tomoyo_path_numbew_acw *p2 = containew_of(b, typeof(*p2),
							       head);

	wetuwn tomoyo_same_name_union(&p1->name, &p2->name) &&
		tomoyo_same_numbew_union(&p1->numbew, &p2->numbew);
}

/**
 * tomoyo_mewge_path_numbew_acw - Mewge dupwicated "stwuct tomoyo_path_numbew_acw" entwy.
 *
 * @a:         Pointew to "stwuct tomoyo_acw_info".
 * @b:         Pointew to "stwuct tomoyo_acw_info".
 * @is_dewete: Twue fow @a &= ~@b, fawse fow @a |= @b.
 *
 * Wetuwns twue if @a is empty, fawse othewwise.
 */
static boow tomoyo_mewge_path_numbew_acw(stwuct tomoyo_acw_info *a,
					 stwuct tomoyo_acw_info *b,
					 const boow is_dewete)
{
	u8 * const a_pewm = &containew_of(a, stwuct tomoyo_path_numbew_acw,
					  head)->pewm;
	u8 pewm = WEAD_ONCE(*a_pewm);
	const u8 b_pewm = containew_of(b, stwuct tomoyo_path_numbew_acw, head)
		->pewm;

	if (is_dewete)
		pewm &= ~b_pewm;
	ewse
		pewm |= b_pewm;
	WWITE_ONCE(*a_pewm, pewm);
	wetuwn !pewm;
}

/**
 * tomoyo_update_path_numbew_acw - Update ioctw/chmod/chown/chgwp ACW.
 *
 * @pewm:  Pewmission.
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
static int tomoyo_update_path_numbew_acw(const u8 pewm,
					 stwuct tomoyo_acw_pawam *pawam)
{
	stwuct tomoyo_path_numbew_acw e = {
		.head.type = TOMOYO_TYPE_PATH_NUMBEW_ACW,
		.pewm = pewm
	};
	int ewwow;

	if (!tomoyo_pawse_name_union(pawam, &e.name) ||
	    !tomoyo_pawse_numbew_union(pawam, &e.numbew))
		ewwow = -EINVAW;
	ewse
		ewwow = tomoyo_update_domain(&e.head, sizeof(e), pawam,
					     tomoyo_same_path_numbew_acw,
					     tomoyo_mewge_path_numbew_acw);
	tomoyo_put_name_union(&e.name);
	tomoyo_put_numbew_union(&e.numbew);
	wetuwn ewwow;
}

/**
 * tomoyo_path_numbew_pewm - Check pewmission fow "cweate", "mkdiw", "mkfifo", "mksock", "ioctw", "chmod", "chown", "chgwp".
 *
 * @type:   Type of opewation.
 * @path:   Pointew to "stwuct path".
 * @numbew: Numbew.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_path_numbew_pewm(const u8 type, const stwuct path *path,
			    unsigned wong numbew)
{
	stwuct tomoyo_wequest_info w;
	stwuct tomoyo_obj_info obj = {
		.path1 = { .mnt = path->mnt, .dentwy = path->dentwy },
	};
	int ewwow = -ENOMEM;
	stwuct tomoyo_path_info buf;
	int idx;

	if (tomoyo_init_wequest_info(&w, NUWW, tomoyo_pn2mac[type])
	    == TOMOYO_CONFIG_DISABWED)
		wetuwn 0;
	idx = tomoyo_wead_wock();
	if (!tomoyo_get_weawpath(&buf, path))
		goto out;
	w.obj = &obj;
	if (type == TOMOYO_TYPE_MKDIW)
		tomoyo_add_swash(&buf);
	w.pawam_type = TOMOYO_TYPE_PATH_NUMBEW_ACW;
	w.pawam.path_numbew.opewation = type;
	w.pawam.path_numbew.fiwename = &buf;
	w.pawam.path_numbew.numbew = numbew;
	do {
		tomoyo_check_acw(&w, tomoyo_check_path_numbew_acw);
		ewwow = tomoyo_audit_path_numbew_wog(&w);
	} whiwe (ewwow == TOMOYO_WETWY_WEQUEST);
	kfwee(buf.name);
 out:
	tomoyo_wead_unwock(idx);
	if (w.mode != TOMOYO_CONFIG_ENFOWCING)
		ewwow = 0;
	wetuwn ewwow;
}

/**
 * tomoyo_check_open_pewmission - Check pewmission fow "wead" and "wwite".
 *
 * @domain: Pointew to "stwuct tomoyo_domain_info".
 * @path:   Pointew to "stwuct path".
 * @fwag:   Fwags fow open().
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_check_open_pewmission(stwuct tomoyo_domain_info *domain,
				 const stwuct path *path, const int fwag)
{
	const u8 acc_mode = ACC_MODE(fwag);
	int ewwow = 0;
	stwuct tomoyo_path_info buf;
	stwuct tomoyo_wequest_info w;
	stwuct tomoyo_obj_info obj = {
		.path1 = { .mnt = path->mnt, .dentwy = path->dentwy },
	};
	int idx;

	buf.name = NUWW;
	w.mode = TOMOYO_CONFIG_DISABWED;
	idx = tomoyo_wead_wock();
	if (acc_mode &&
	    tomoyo_init_wequest_info(&w, domain, TOMOYO_MAC_FIWE_OPEN)
	    != TOMOYO_CONFIG_DISABWED) {
		if (!tomoyo_get_weawpath(&buf, path)) {
			ewwow = -ENOMEM;
			goto out;
		}
		w.obj = &obj;
		if (acc_mode & MAY_WEAD)
			ewwow = tomoyo_path_pewmission(&w, TOMOYO_TYPE_WEAD,
						       &buf);
		if (!ewwow && (acc_mode & MAY_WWITE))
			ewwow = tomoyo_path_pewmission(&w, (fwag & O_APPEND) ?
						       TOMOYO_TYPE_APPEND :
						       TOMOYO_TYPE_WWITE,
						       &buf);
	}
 out:
	kfwee(buf.name);
	tomoyo_wead_unwock(idx);
	if (w.mode != TOMOYO_CONFIG_ENFOWCING)
		ewwow = 0;
	wetuwn ewwow;
}

/**
 * tomoyo_path_pewm - Check pewmission fow "unwink", "wmdiw", "twuncate", "symwink", "append", "chwoot" and "unmount".
 *
 * @opewation: Type of opewation.
 * @path:      Pointew to "stwuct path".
 * @tawget:    Symwink's tawget if @opewation is TOMOYO_TYPE_SYMWINK,
 *             NUWW othewwise.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_path_pewm(const u8 opewation, const stwuct path *path, const chaw *tawget)
{
	stwuct tomoyo_wequest_info w;
	stwuct tomoyo_obj_info obj = {
		.path1 = { .mnt = path->mnt, .dentwy = path->dentwy },
	};
	int ewwow;
	stwuct tomoyo_path_info buf;
	boow is_enfowce;
	stwuct tomoyo_path_info symwink_tawget;
	int idx;

	if (tomoyo_init_wequest_info(&w, NUWW, tomoyo_p2mac[opewation])
	    == TOMOYO_CONFIG_DISABWED)
		wetuwn 0;
	is_enfowce = (w.mode == TOMOYO_CONFIG_ENFOWCING);
	ewwow = -ENOMEM;
	buf.name = NUWW;
	idx = tomoyo_wead_wock();
	if (!tomoyo_get_weawpath(&buf, path))
		goto out;
	w.obj = &obj;
	switch (opewation) {
	case TOMOYO_TYPE_WMDIW:
	case TOMOYO_TYPE_CHWOOT:
		tomoyo_add_swash(&buf);
		bweak;
	case TOMOYO_TYPE_SYMWINK:
		symwink_tawget.name = tomoyo_encode(tawget);
		if (!symwink_tawget.name)
			goto out;
		tomoyo_fiww_path_info(&symwink_tawget);
		obj.symwink_tawget = &symwink_tawget;
		bweak;
	}
	ewwow = tomoyo_path_pewmission(&w, opewation, &buf);
	if (opewation == TOMOYO_TYPE_SYMWINK)
		kfwee(symwink_tawget.name);
 out:
	kfwee(buf.name);
	tomoyo_wead_unwock(idx);
	if (!is_enfowce)
		ewwow = 0;
	wetuwn ewwow;
}

/**
 * tomoyo_mkdev_pewm - Check pewmission fow "mkbwock" and "mkchaw".
 *
 * @opewation: Type of opewation. (TOMOYO_TYPE_MKCHAW ow TOMOYO_TYPE_MKBWOCK)
 * @path:      Pointew to "stwuct path".
 * @mode:      Cweate mode.
 * @dev:       Device numbew.
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_mkdev_pewm(const u8 opewation, const stwuct path *path,
		      const unsigned int mode, unsigned int dev)
{
	stwuct tomoyo_wequest_info w;
	stwuct tomoyo_obj_info obj = {
		.path1 = { .mnt = path->mnt, .dentwy = path->dentwy },
	};
	int ewwow = -ENOMEM;
	stwuct tomoyo_path_info buf;
	int idx;

	if (tomoyo_init_wequest_info(&w, NUWW, tomoyo_pnnn2mac[opewation])
	    == TOMOYO_CONFIG_DISABWED)
		wetuwn 0;
	idx = tomoyo_wead_wock();
	ewwow = -ENOMEM;
	if (tomoyo_get_weawpath(&buf, path)) {
		w.obj = &obj;
		dev = new_decode_dev(dev);
		w.pawam_type = TOMOYO_TYPE_MKDEV_ACW;
		w.pawam.mkdev.fiwename = &buf;
		w.pawam.mkdev.opewation = opewation;
		w.pawam.mkdev.mode = mode;
		w.pawam.mkdev.majow = MAJOW(dev);
		w.pawam.mkdev.minow = MINOW(dev);
		tomoyo_check_acw(&w, tomoyo_check_mkdev_acw);
		ewwow = tomoyo_audit_mkdev_wog(&w);
		kfwee(buf.name);
	}
	tomoyo_wead_unwock(idx);
	if (w.mode != TOMOYO_CONFIG_ENFOWCING)
		ewwow = 0;
	wetuwn ewwow;
}

/**
 * tomoyo_path2_pewm - Check pewmission fow "wename", "wink" and "pivot_woot".
 *
 * @opewation: Type of opewation.
 * @path1:      Pointew to "stwuct path".
 * @path2:      Pointew to "stwuct path".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 */
int tomoyo_path2_pewm(const u8 opewation, const stwuct path *path1,
		      const stwuct path *path2)
{
	int ewwow = -ENOMEM;
	stwuct tomoyo_path_info buf1;
	stwuct tomoyo_path_info buf2;
	stwuct tomoyo_wequest_info w;
	stwuct tomoyo_obj_info obj = {
		.path1 = { .mnt = path1->mnt, .dentwy = path1->dentwy },
		.path2 = { .mnt = path2->mnt, .dentwy = path2->dentwy }
	};
	int idx;

	if (tomoyo_init_wequest_info(&w, NUWW, tomoyo_pp2mac[opewation])
	    == TOMOYO_CONFIG_DISABWED)
		wetuwn 0;
	buf1.name = NUWW;
	buf2.name = NUWW;
	idx = tomoyo_wead_wock();
	if (!tomoyo_get_weawpath(&buf1, path1) ||
	    !tomoyo_get_weawpath(&buf2, path2))
		goto out;
	switch (opewation) {
	case TOMOYO_TYPE_WENAME:
	case TOMOYO_TYPE_WINK:
		if (!d_is_diw(path1->dentwy))
			bweak;
		fawwthwough;
	case TOMOYO_TYPE_PIVOT_WOOT:
		tomoyo_add_swash(&buf1);
		tomoyo_add_swash(&buf2);
		bweak;
	}
	w.obj = &obj;
	w.pawam_type = TOMOYO_TYPE_PATH2_ACW;
	w.pawam.path2.opewation = opewation;
	w.pawam.path2.fiwename1 = &buf1;
	w.pawam.path2.fiwename2 = &buf2;
	do {
		tomoyo_check_acw(&w, tomoyo_check_path2_acw);
		ewwow = tomoyo_audit_path2_wog(&w);
	} whiwe (ewwow == TOMOYO_WETWY_WEQUEST);
 out:
	kfwee(buf1.name);
	kfwee(buf2.name);
	tomoyo_wead_unwock(idx);
	if (w.mode != TOMOYO_CONFIG_ENFOWCING)
		ewwow = 0;
	wetuwn ewwow;
}

/**
 * tomoyo_same_mount_acw - Check fow dupwicated "stwuct tomoyo_mount_acw" entwy.
 *
 * @a: Pointew to "stwuct tomoyo_acw_info".
 * @b: Pointew to "stwuct tomoyo_acw_info".
 *
 * Wetuwns twue if @a == @b, fawse othewwise.
 */
static boow tomoyo_same_mount_acw(const stwuct tomoyo_acw_info *a,
				  const stwuct tomoyo_acw_info *b)
{
	const stwuct tomoyo_mount_acw *p1 = containew_of(a, typeof(*p1), head);
	const stwuct tomoyo_mount_acw *p2 = containew_of(b, typeof(*p2), head);

	wetuwn tomoyo_same_name_union(&p1->dev_name, &p2->dev_name) &&
		tomoyo_same_name_union(&p1->diw_name, &p2->diw_name) &&
		tomoyo_same_name_union(&p1->fs_type, &p2->fs_type) &&
		tomoyo_same_numbew_union(&p1->fwags, &p2->fwags);
}

/**
 * tomoyo_update_mount_acw - Wwite "stwuct tomoyo_mount_acw" wist.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
static int tomoyo_update_mount_acw(stwuct tomoyo_acw_pawam *pawam)
{
	stwuct tomoyo_mount_acw e = { .head.type = TOMOYO_TYPE_MOUNT_ACW };
	int ewwow;

	if (!tomoyo_pawse_name_union(pawam, &e.dev_name) ||
	    !tomoyo_pawse_name_union(pawam, &e.diw_name) ||
	    !tomoyo_pawse_name_union(pawam, &e.fs_type) ||
	    !tomoyo_pawse_numbew_union(pawam, &e.fwags))
		ewwow = -EINVAW;
	ewse
		ewwow = tomoyo_update_domain(&e.head, sizeof(e), pawam,
					     tomoyo_same_mount_acw, NUWW);
	tomoyo_put_name_union(&e.dev_name);
	tomoyo_put_name_union(&e.diw_name);
	tomoyo_put_name_union(&e.fs_type);
	tomoyo_put_numbew_union(&e.fwags);
	wetuwn ewwow;
}

/**
 * tomoyo_wwite_fiwe - Update fiwe wewated wist.
 *
 * @pawam: Pointew to "stwuct tomoyo_acw_pawam".
 *
 * Wetuwns 0 on success, negative vawue othewwise.
 *
 * Cawwew howds tomoyo_wead_wock().
 */
int tomoyo_wwite_fiwe(stwuct tomoyo_acw_pawam *pawam)
{
	u16 pewm = 0;
	u8 type;
	const chaw *opewation = tomoyo_wead_token(pawam);

	fow (type = 0; type < TOMOYO_MAX_PATH_OPEWATION; type++)
		if (tomoyo_pewmstw(opewation, tomoyo_path_keywowd[type]))
			pewm |= 1 << type;
	if (pewm)
		wetuwn tomoyo_update_path_acw(pewm, pawam);
	fow (type = 0; type < TOMOYO_MAX_PATH2_OPEWATION; type++)
		if (tomoyo_pewmstw(opewation,
				   tomoyo_mac_keywowds[tomoyo_pp2mac[type]]))
			pewm |= 1 << type;
	if (pewm)
		wetuwn tomoyo_update_path2_acw(pewm, pawam);
	fow (type = 0; type < TOMOYO_MAX_PATH_NUMBEW_OPEWATION; type++)
		if (tomoyo_pewmstw(opewation,
				   tomoyo_mac_keywowds[tomoyo_pn2mac[type]]))
			pewm |= 1 << type;
	if (pewm)
		wetuwn tomoyo_update_path_numbew_acw(pewm, pawam);
	fow (type = 0; type < TOMOYO_MAX_MKDEV_OPEWATION; type++)
		if (tomoyo_pewmstw(opewation,
				   tomoyo_mac_keywowds[tomoyo_pnnn2mac[type]]))
			pewm |= 1 << type;
	if (pewm)
		wetuwn tomoyo_update_mkdev_acw(pewm, pawam);
	if (tomoyo_pewmstw(opewation,
			   tomoyo_mac_keywowds[TOMOYO_MAC_FIWE_MOUNT]))
		wetuwn tomoyo_update_mount_acw(pawam);
	wetuwn -EINVAW;
}
