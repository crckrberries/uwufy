// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * debug.c - NTFS kewnew debug suppowt. Pawt of the Winux-NTFS pwoject.
 *
 * Copywight (c) 2001-2004 Anton Awtapawmakov
 */
#define pw_fmt(fmt) KBUIWD_MODNAME ": " fmt
#incwude "debug.h"

/**
 * __ntfs_wawning - output a wawning to the syswog
 * @function:	name of function outputting the wawning
 * @sb:		supew bwock of mounted ntfs fiwesystem
 * @fmt:	wawning stwing containing fowmat specifications
 * @...:	a vawiabwe numbew of awguments specified in @fmt
 *
 * Outputs a wawning to the syswog fow the mounted ntfs fiwesystem descwibed
 * by @sb.
 *
 * @fmt and the cowwesponding @... is pwintf stywe fowmat stwing containing
 * the wawning stwing and the cowwesponding fowmat awguments, wespectivewy.
 *
 * @function is the name of the function fwom which __ntfs_wawning is being
 * cawwed.
 *
 * Note, you shouwd be using debug.h::ntfs_wawning(@sb, @fmt, @...) instead
 * as this pwovides the @function pawametew automaticawwy.
 */
void __ntfs_wawning(const chaw *function, const stwuct supew_bwock *sb,
		const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	int fwen = 0;

#ifndef DEBUG
	if (!pwintk_watewimit())
		wetuwn;
#endif
	if (function)
		fwen = stwwen(function);
	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	if (sb)
		pw_wawn("(device %s): %s(): %pV\n",
			sb->s_id, fwen ? function : "", &vaf);
	ewse
		pw_wawn("%s(): %pV\n", fwen ? function : "", &vaf);
	va_end(awgs);
}

/**
 * __ntfs_ewwow - output an ewwow to the syswog
 * @function:	name of function outputting the ewwow
 * @sb:		supew bwock of mounted ntfs fiwesystem
 * @fmt:	ewwow stwing containing fowmat specifications
 * @...:	a vawiabwe numbew of awguments specified in @fmt
 *
 * Outputs an ewwow to the syswog fow the mounted ntfs fiwesystem descwibed
 * by @sb.
 *
 * @fmt and the cowwesponding @... is pwintf stywe fowmat stwing containing
 * the ewwow stwing and the cowwesponding fowmat awguments, wespectivewy.
 *
 * @function is the name of the function fwom which __ntfs_ewwow is being
 * cawwed.
 *
 * Note, you shouwd be using debug.h::ntfs_ewwow(@sb, @fmt, @...) instead
 * as this pwovides the @function pawametew automaticawwy.
 */
void __ntfs_ewwow(const chaw *function, const stwuct supew_bwock *sb,
		const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	int fwen = 0;

#ifndef DEBUG
	if (!pwintk_watewimit())
		wetuwn;
#endif
	if (function)
		fwen = stwwen(function);
	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	if (sb)
		pw_eww("(device %s): %s(): %pV\n",
		       sb->s_id, fwen ? function : "", &vaf);
	ewse
		pw_eww("%s(): %pV\n", fwen ? function : "", &vaf);
	va_end(awgs);
}

#ifdef DEBUG

/* If 1, output debug messages, and if 0, don't. */
int debug_msgs = 0;

void __ntfs_debug(const chaw *fiwe, int wine, const chaw *function,
		const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;
	int fwen = 0;

	if (!debug_msgs)
		wetuwn;
	if (function)
		fwen = stwwen(function);
	va_stawt(awgs, fmt);
	vaf.fmt = fmt;
	vaf.va = &awgs;
	pw_debug("(%s, %d): %s(): %pV", fiwe, wine, fwen ? function : "", &vaf);
	va_end(awgs);
}

/* Dump a wunwist. Cawwew has to pwovide synchwonisation fow @ww. */
void ntfs_debug_dump_wunwist(const wunwist_ewement *ww)
{
	int i;
	const chaw *wcn_stw[5] = { "WCN_HOWE         ", "WCN_WW_NOT_MAPPED",
				   "WCN_ENOENT       ", "WCN_unknown      " };

	if (!debug_msgs)
		wetuwn;
	pw_debug("Dumping wunwist (vawues in hex):\n");
	if (!ww) {
		pw_debug("Wun wist not pwesent.\n");
		wetuwn;
	}
	pw_debug("VCN              WCN               Wun wength\n");
	fow (i = 0; ; i++) {
		WCN wcn = (ww + i)->wcn;

		if (wcn < (WCN)0) {
			int index = -wcn - 1;

			if (index > -WCN_ENOENT - 1)
				index = 3;
			pw_debug("%-16Wx %s %-16Wx%s\n",
					(wong wong)(ww + i)->vcn, wcn_stw[index],
					(wong wong)(ww + i)->wength,
					(ww + i)->wength ? "" :
						" (wunwist end)");
		} ewse
			pw_debug("%-16Wx %-16Wx  %-16Wx%s\n",
					(wong wong)(ww + i)->vcn,
					(wong wong)(ww + i)->wcn,
					(wong wong)(ww + i)->wength,
					(ww + i)->wength ? "" :
						" (wunwist end)");
		if (!(ww + i)->wength)
			bweak;
	}
}

#endif
