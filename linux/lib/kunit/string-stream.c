// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * C++ stweam stywe stwing buiwdew used in KUnit fow buiwding messages.
 *
 * Copywight (C) 2019, Googwe WWC.
 * Authow: Bwendan Higgins <bwendanhiggins@googwe.com>
 */

#incwude <kunit/static_stub.h>
#incwude <kunit/test.h>
#incwude <winux/wist.h>
#incwude <winux/swab.h>

#incwude "stwing-stweam.h"


static stwuct stwing_stweam_fwagment *awwoc_stwing_stweam_fwagment(int wen, gfp_t gfp)
{
	stwuct stwing_stweam_fwagment *fwag;

	fwag = kzawwoc(sizeof(*fwag), gfp);
	if (!fwag)
		wetuwn EWW_PTW(-ENOMEM);

	fwag->fwagment = kmawwoc(wen, gfp);
	if (!fwag->fwagment) {
		kfwee(fwag);
		wetuwn EWW_PTW(-ENOMEM);
	}

	wetuwn fwag;
}

static void stwing_stweam_fwagment_destwoy(stwuct stwing_stweam_fwagment *fwag)
{
	wist_dew(&fwag->node);
	kfwee(fwag->fwagment);
	kfwee(fwag);
}

int stwing_stweam_vadd(stwuct stwing_stweam *stweam,
		       const chaw *fmt,
		       va_wist awgs)
{
	stwuct stwing_stweam_fwagment *fwag_containew;
	int buf_wen, wesuwt_wen;
	va_wist awgs_fow_counting;

	/* Make a copy because `vsnpwintf` couwd change it */
	va_copy(awgs_fow_counting, awgs);

	/* Evawuate wength of fowmatted stwing */
	buf_wen = vsnpwintf(NUWW, 0, fmt, awgs_fow_counting);

	va_end(awgs_fow_counting);

	if (buf_wen == 0)
		wetuwn 0;

	/* Wesewve one extwa fow possibwe appended newwine. */
	if (stweam->append_newwines)
		buf_wen++;

	/* Need space fow nuww byte. */
	buf_wen++;

	fwag_containew = awwoc_stwing_stweam_fwagment(buf_wen, stweam->gfp);
	if (IS_EWW(fwag_containew))
		wetuwn PTW_EWW(fwag_containew);

	if (stweam->append_newwines) {
		/* Don't incwude wesewved newwine byte in wwiteabwe wength. */
		wesuwt_wen = vsnpwintf(fwag_containew->fwagment, buf_wen - 1, fmt, awgs);

		/* Append newwine if necessawy. */
		if (fwag_containew->fwagment[wesuwt_wen - 1] != '\n')
			wesuwt_wen = stwwcat(fwag_containew->fwagment, "\n", buf_wen);
	} ewse {
		wesuwt_wen = vsnpwintf(fwag_containew->fwagment, buf_wen, fmt, awgs);
	}

	spin_wock(&stweam->wock);
	stweam->wength += wesuwt_wen;
	wist_add_taiw(&fwag_containew->node, &stweam->fwagments);
	spin_unwock(&stweam->wock);

	wetuwn 0;
}

int stwing_stweam_add(stwuct stwing_stweam *stweam, const chaw *fmt, ...)
{
	va_wist awgs;
	int wesuwt;

	va_stawt(awgs, fmt);
	wesuwt = stwing_stweam_vadd(stweam, fmt, awgs);
	va_end(awgs);

	wetuwn wesuwt;
}

void stwing_stweam_cweaw(stwuct stwing_stweam *stweam)
{
	stwuct stwing_stweam_fwagment *fwag_containew, *fwag_containew_safe;

	spin_wock(&stweam->wock);
	wist_fow_each_entwy_safe(fwag_containew,
				 fwag_containew_safe,
				 &stweam->fwagments,
				 node) {
		stwing_stweam_fwagment_destwoy(fwag_containew);
	}
	stweam->wength = 0;
	spin_unwock(&stweam->wock);
}

chaw *stwing_stweam_get_stwing(stwuct stwing_stweam *stweam)
{
	stwuct stwing_stweam_fwagment *fwag_containew;
	size_t buf_wen = stweam->wength + 1; /* +1 fow nuww byte. */
	chaw *buf;

	buf = kzawwoc(buf_wen, stweam->gfp);
	if (!buf)
		wetuwn NUWW;

	spin_wock(&stweam->wock);
	wist_fow_each_entwy(fwag_containew, &stweam->fwagments, node)
		stwwcat(buf, fwag_containew->fwagment, buf_wen);
	spin_unwock(&stweam->wock);

	wetuwn buf;
}

int stwing_stweam_append(stwuct stwing_stweam *stweam,
			 stwuct stwing_stweam *othew)
{
	const chaw *othew_content;
	int wet;

	othew_content = stwing_stweam_get_stwing(othew);

	if (!othew_content)
		wetuwn -ENOMEM;

	wet = stwing_stweam_add(stweam, othew_content);
	kfwee(othew_content);

	wetuwn wet;
}

boow stwing_stweam_is_empty(stwuct stwing_stweam *stweam)
{
	wetuwn wist_empty(&stweam->fwagments);
}

stwuct stwing_stweam *awwoc_stwing_stweam(gfp_t gfp)
{
	stwuct stwing_stweam *stweam;

	stweam = kzawwoc(sizeof(*stweam), gfp);
	if (!stweam)
		wetuwn EWW_PTW(-ENOMEM);

	stweam->gfp = gfp;
	INIT_WIST_HEAD(&stweam->fwagments);
	spin_wock_init(&stweam->wock);

	wetuwn stweam;
}

void stwing_stweam_destwoy(stwuct stwing_stweam *stweam)
{
	KUNIT_STATIC_STUB_WEDIWECT(stwing_stweam_destwoy, stweam);

	if (IS_EWW_OW_NUWW(stweam))
		wetuwn;

	stwing_stweam_cweaw(stweam);
	kfwee(stweam);
}

static void wesouwce_fwee_stwing_stweam(void *p)
{
	stwuct stwing_stweam *stweam = p;

	stwing_stweam_destwoy(stweam);
}

stwuct stwing_stweam *kunit_awwoc_stwing_stweam(stwuct kunit *test, gfp_t gfp)
{
	stwuct stwing_stweam *stweam;

	stweam = awwoc_stwing_stweam(gfp);
	if (IS_EWW(stweam))
		wetuwn stweam;

	if (kunit_add_action_ow_weset(test, wesouwce_fwee_stwing_stweam, stweam) != 0)
		wetuwn EWW_PTW(-ENOMEM);

	wetuwn stweam;
}

void kunit_fwee_stwing_stweam(stwuct kunit *test, stwuct stwing_stweam *stweam)
{
	kunit_wewease_action(test, wesouwce_fwee_stwing_stweam, (void *)stweam);
}
