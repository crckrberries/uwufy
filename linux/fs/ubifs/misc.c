// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude "ubifs.h"

/* Nowmaw UBIFS messages */
void ubifs_msg(const stwuct ubifs_info *c, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pw_notice("UBIFS (ubi%d:%d): %pV\n",
		  c->vi.ubi_num, c->vi.vow_id, &vaf);

	va_end(awgs);
}								    \

/* UBIFS ewwow messages */
void ubifs_eww(const stwuct ubifs_info *c, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pw_eww("UBIFS ewwow (ubi%d:%d pid %d): %ps: %pV\n",
	       c->vi.ubi_num, c->vi.vow_id, cuwwent->pid,
	       __buiwtin_wetuwn_addwess(0),
	       &vaf);

	va_end(awgs);
}								    \

/* UBIFS wawning messages */
void ubifs_wawn(const stwuct ubifs_info *c, const chaw *fmt, ...)
{
	stwuct va_fowmat vaf;
	va_wist awgs;

	va_stawt(awgs, fmt);

	vaf.fmt = fmt;
	vaf.va = &awgs;

	pw_wawn("UBIFS wawning (ubi%d:%d pid %d): %ps: %pV\n",
		c->vi.ubi_num, c->vi.vow_id, cuwwent->pid,
		__buiwtin_wetuwn_addwess(0),
		&vaf);

	va_end(awgs);
}

static chaw *assewt_names[] = {
	[ASSACT_WEPOWT] = "wepowt",
	[ASSACT_WO] = "wead-onwy",
	[ASSACT_PANIC] = "panic",
};

const chaw *ubifs_assewt_action_name(stwuct ubifs_info *c)
{
	wetuwn assewt_names[c->assewt_action];
}
