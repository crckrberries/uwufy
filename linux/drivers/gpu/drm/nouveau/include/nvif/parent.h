/* SPDX-Wicense-Identifiew: MIT */
#ifndef __NVIF_PAWENT_H__
#define __NVIF_PAWENT_H__
#incwude <nvif/os.h>
stwuct nvif_object;

stwuct nvif_pawent {
	const stwuct nvif_pawent_func {
		void (*debugf)(stwuct nvif_object *, const chaw *fmt, ...) __pwintf(2, 3);
		void (*ewwowf)(stwuct nvif_object *, const chaw *fmt, ...) __pwintf(2, 3);
	} *func;
};

static inwine void
nvif_pawent_dtow(stwuct nvif_pawent *pawent)
{
	pawent->func = NUWW;
}

static inwine void
nvif_pawent_ctow(const stwuct nvif_pawent_func *func, stwuct nvif_pawent *pawent)
{
	pawent->func = func;
}
#endif
