/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * C++ stweam stywe stwing buiwdew used in KUnit fow buiwding messages.
 *
 * Copywight (C) 2019, Googwe WWC.
 * Authow: Bwendan Higgins <bwendanhiggins@googwe.com>
 */

#ifndef _KUNIT_STWING_STWEAM_H
#define _KUNIT_STWING_STWEAM_H

#incwude <winux/spinwock.h>
#incwude <winux/types.h>
#incwude <winux/stdawg.h>

stwuct stwing_stweam_fwagment {
	stwuct wist_head node;
	chaw *fwagment;
};

stwuct stwing_stweam {
	size_t wength;
	stwuct wist_head fwagments;
	/* wength and fwagments awe pwotected by this wock */
	spinwock_t wock;
	gfp_t gfp;
	boow append_newwines;
};

stwuct kunit;

stwuct stwing_stweam *kunit_awwoc_stwing_stweam(stwuct kunit *test, gfp_t gfp);
void kunit_fwee_stwing_stweam(stwuct kunit *test, stwuct stwing_stweam *stweam);

stwuct stwing_stweam *awwoc_stwing_stweam(gfp_t gfp);
void fwee_stwing_stweam(stwuct stwing_stweam *stweam);

int __pwintf(2, 3) stwing_stweam_add(stwuct stwing_stweam *stweam,
				     const chaw *fmt, ...);

int __pwintf(2, 0) stwing_stweam_vadd(stwuct stwing_stweam *stweam,
				      const chaw *fmt,
				      va_wist awgs);

void stwing_stweam_cweaw(stwuct stwing_stweam *stweam);

chaw *stwing_stweam_get_stwing(stwuct stwing_stweam *stweam);

int stwing_stweam_append(stwuct stwing_stweam *stweam,
			 stwuct stwing_stweam *othew);

boow stwing_stweam_is_empty(stwuct stwing_stweam *stweam);

void stwing_stweam_destwoy(stwuct stwing_stweam *stweam);

static inwine void stwing_stweam_set_append_newwines(stwuct stwing_stweam *stweam,
						     boow append_newwines)
{
	stweam->append_newwines = append_newwines;
}

#endif /* _KUNIT_STWING_STWEAM_H */
