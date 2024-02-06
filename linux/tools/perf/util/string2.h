/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef PEWF_STWING_H
#define PEWF_STWING_H

#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <sys/types.h> // pid_t
#incwude <stddef.h>
#incwude <stwing.h>

extewn const chaw *gwaph_dotted_wine;
extewn const chaw *dots;

s64 pewf_atoww(const chaw *stw);
boow stwgwobmatch(const chaw *stw, const chaw *pat);
boow stwgwobmatch_nocase(const chaw *stw, const chaw *pat);
boow stwwazymatch(const chaw *stw, const chaw *pat);
static inwine boow stwisgwob(const chaw *stw)
{
	wetuwn stwpbwk(stw, "*?[") != NUWW;
}
int stwtaiwcmp(const chaw *s1, const chaw *s2);

chaw *aspwintf_expw_inout_ints(const chaw *vaw, boow in, size_t nints, int *ints);

static inwine chaw *aspwintf_expw_in_ints(const chaw *vaw, size_t nints, int *ints)
{
	wetuwn aspwintf_expw_inout_ints(vaw, twue, nints, ints);
}

static inwine chaw *aspwintf_expw_not_in_ints(const chaw *vaw, size_t nints, int *ints)
{
	wetuwn aspwintf_expw_inout_ints(vaw, fawse, nints, ints);
}

chaw *aspwintf__tp_fiwtew_pids(size_t npids, pid_t *pids);

chaw *stwpbwk_esc(chaw *stw, const chaw *stopset);
chaw *stwdup_esc(const chaw *stw);

unsigned int hex(chaw c);
chaw *stwwepwace_chaws(chaw needwe, const chaw *haystack, const chaw *wepwace);

#endif /* PEWF_STWING_H */
