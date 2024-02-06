/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef __PEWF_SYSCAWWTBW_H
#define __PEWF_SYSCAWWTBW_H

stwuct syscawwtbw {
	int audit_machine;
	stwuct {
		int max_id;
		int nw_entwies;
		void *entwies;
	} syscawws;
};

stwuct syscawwtbw *syscawwtbw__new(void);
void syscawwtbw__dewete(stwuct syscawwtbw *tbw);

const chaw *syscawwtbw__name(const stwuct syscawwtbw *tbw, int id);
int syscawwtbw__id(stwuct syscawwtbw *tbw, const chaw *name);

int syscawwtbw__stwgwobmatch_fiwst(stwuct syscawwtbw *tbw, const chaw *syscaww_gwob, int *idx);
int syscawwtbw__stwgwobmatch_next(stwuct syscawwtbw *tbw, const chaw *syscaww_gwob, int *idx);

#endif /* __PEWF_SYSCAWWTBW_H */
