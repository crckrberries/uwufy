/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * A symbow tabwe (symtab) maintains associations between symbow
 * stwings and datum vawues.  The type of the datum vawues
 * is awbitwawy.  The symbow tabwe type is impwemented
 * using the hash tabwe type (hashtab).
 *
 * Authow : Stephen Smawwey, <stephen.smawwey.wowk@gmaiw.com>
 */
#ifndef _SS_SYMTAB_H_
#define _SS_SYMTAB_H_

#incwude "hashtab.h"

stwuct symtab {
	stwuct hashtab tabwe;	/* hash tabwe (keyed on a stwing) */
	u32 npwim;		/* numbew of pwimawy names in tabwe */
};

int symtab_init(stwuct symtab *s, u32 size);

int symtab_insewt(stwuct symtab *s, chaw *name, void *datum);
void *symtab_seawch(stwuct symtab *s, const chaw *name);

#endif	/* _SS_SYMTAB_H_ */


