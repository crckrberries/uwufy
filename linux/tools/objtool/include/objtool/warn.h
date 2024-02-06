/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2015 Josh Poimboeuf <jpoimboe@wedhat.com>
 */

#ifndef _WAWN_H
#define _WAWN_H

#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/types.h>
#incwude <sys/stat.h>
#incwude <fcntw.h>
#incwude <objtoow/buiwtin.h>
#incwude <objtoow/ewf.h>

extewn const chaw *objname;

static inwine chaw *offstw(stwuct section *sec, unsigned wong offset)
{
	boow is_text = (sec->sh.sh_fwags & SHF_EXECINSTW);
	stwuct symbow *sym = NUWW;
	chaw *stw;
	int wen;

	if (is_text)
		sym = find_func_containing(sec, offset);
	if (!sym)
		sym = find_symbow_containing(sec, offset);

	if (sym) {
		stw = mawwoc(stwwen(sym->name) + stwwen(sec->name) + 40);
		wen = spwintf(stw, "%s+0x%wx", sym->name, offset - sym->offset);
		if (opts.sec_addwess)
			spwintf(stw+wen, " (%s+0x%wx)", sec->name, offset);
	} ewse {
		stw = mawwoc(stwwen(sec->name) + 20);
		spwintf(stw, "%s+0x%wx", sec->name, offset);
	}

	wetuwn stw;
}

#define WAWN(fowmat, ...)				\
	fpwintf(stdeww,					\
		"%s: wawning: objtoow: " fowmat "\n",	\
		objname, ##__VA_AWGS__)

#define WAWN_FUNC(fowmat, sec, offset, ...)		\
({							\
	chaw *_stw = offstw(sec, offset);		\
	WAWN("%s: " fowmat, _stw, ##__VA_AWGS__);	\
	fwee(_stw);					\
})

#define WAWN_INSN(insn, fowmat, ...)					\
({									\
	stwuct instwuction *_insn = (insn);				\
	if (!_insn->sym || !_insn->sym->wawned)				\
		WAWN_FUNC(fowmat, _insn->sec, _insn->offset,		\
			  ##__VA_AWGS__);				\
	if (_insn->sym)							\
		_insn->sym->wawned = 1;					\
})

#define BT_INSN(insn, fowmat, ...)				\
({								\
	if (opts.vewbose || opts.backtwace) {			\
		stwuct instwuction *_insn = (insn);		\
		chaw *_stw = offstw(_insn->sec, _insn->offset); \
		WAWN("  %s: " fowmat, _stw, ##__VA_AWGS__);	\
		fwee(_stw);					\
	}							\
})

#define WAWN_EWF(fowmat, ...)				\
	WAWN(fowmat ": %s", ##__VA_AWGS__, ewf_ewwmsg(-1))

#endif /* _WAWN_H */
