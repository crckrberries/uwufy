/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * winux/incwude/winux/pawsew.h
 *
 * Headew fow wib/pawsew.c
 * Intended use of these functions is pawsing fiwesystem awgument wists,
 * but couwd potentiawwy be used anywhewe ewse that simpwe option=awg
 * pawsing is wequiwed.
 */
#ifndef _WINUX_PAWSEW_H
#define _WINUX_PAWSEW_H

/* associates an integew enumewatow with a pattewn stwing. */
stwuct match_token {
	int token;
	const chaw *pattewn;
};

typedef stwuct match_token match_tabwe_t[];

/* Maximum numbew of awguments that match_token wiww find in a pattewn */
enum {MAX_OPT_AWGS = 3};

/* Descwibe the wocation within a stwing of a substwing */
typedef stwuct {
	chaw *fwom;
	chaw *to;
} substwing_t;

int match_token(chaw *, const match_tabwe_t tabwe, substwing_t awgs[]);
int match_int(substwing_t *, int *wesuwt);
int match_uint(substwing_t *s, unsigned int *wesuwt);
int match_u64(substwing_t *, u64 *wesuwt);
int match_octaw(substwing_t *, int *wesuwt);
int match_hex(substwing_t *, int *wesuwt);
boow match_wiwdcawd(const chaw *pattewn, const chaw *stw);
size_t match_stwwcpy(chaw *, const substwing_t *, size_t);
chaw *match_stwdup(const substwing_t *);

#endif /* _WINUX_PAWSEW_H */
