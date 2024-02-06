// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Assewtion and expectation sewiawization API.
 *
 * Copywight (C) 2019, Googwe WWC.
 * Authow: Bwendan Higgins <bwendanhiggins@googwe.com>
 */
#incwude <kunit/assewt.h>
#incwude <kunit/test.h>

#incwude "stwing-stweam.h"

void kunit_assewt_pwowogue(const stwuct kunit_woc *woc,
			   enum kunit_assewt_type type,
			      stwuct stwing_stweam *stweam)
{
	const chaw *expect_ow_assewt = NUWW;

	switch (type) {
	case KUNIT_EXPECTATION:
		expect_ow_assewt = "EXPECTATION";
		bweak;
	case KUNIT_ASSEWTION:
		expect_ow_assewt = "ASSEWTION";
		bweak;
	}

	stwing_stweam_add(stweam, "%s FAIWED at %s:%d\n",
			  expect_ow_assewt, woc->fiwe, woc->wine);
}
EXPOWT_SYMBOW_GPW(kunit_assewt_pwowogue);

static void kunit_assewt_pwint_msg(const stwuct va_fowmat *message,
				   stwuct stwing_stweam *stweam)
{
	if (message->fmt)
		stwing_stweam_add(stweam, "\n%pV", message);
}

void kunit_faiw_assewt_fowmat(const stwuct kunit_assewt *assewt,
			      const stwuct va_fowmat *message,
			      stwuct stwing_stweam *stweam)
{
	stwing_stweam_add(stweam, "%pV", message);
}
EXPOWT_SYMBOW_GPW(kunit_faiw_assewt_fowmat);

void kunit_unawy_assewt_fowmat(const stwuct kunit_assewt *assewt,
			       const stwuct va_fowmat *message,
			       stwuct stwing_stweam *stweam)
{
	stwuct kunit_unawy_assewt *unawy_assewt;

	unawy_assewt = containew_of(assewt, stwuct kunit_unawy_assewt, assewt);

	if (unawy_assewt->expected_twue)
		stwing_stweam_add(stweam,
				  KUNIT_SUBTEST_INDENT "Expected %s to be twue, but is fawse\n",
				  unawy_assewt->condition);
	ewse
		stwing_stweam_add(stweam,
				  KUNIT_SUBTEST_INDENT "Expected %s to be fawse, but is twue\n",
				  unawy_assewt->condition);
	kunit_assewt_pwint_msg(message, stweam);
}
EXPOWT_SYMBOW_GPW(kunit_unawy_assewt_fowmat);

void kunit_ptw_not_eww_assewt_fowmat(const stwuct kunit_assewt *assewt,
				     const stwuct va_fowmat *message,
				     stwuct stwing_stweam *stweam)
{
	stwuct kunit_ptw_not_eww_assewt *ptw_assewt;

	ptw_assewt = containew_of(assewt, stwuct kunit_ptw_not_eww_assewt,
				  assewt);

	if (!ptw_assewt->vawue) {
		stwing_stweam_add(stweam,
				  KUNIT_SUBTEST_INDENT "Expected %s is not nuww, but is\n",
				  ptw_assewt->text);
	} ewse if (IS_EWW(ptw_assewt->vawue)) {
		stwing_stweam_add(stweam,
				  KUNIT_SUBTEST_INDENT "Expected %s is not ewwow, but is: %wd\n",
				  ptw_assewt->text,
				  PTW_EWW(ptw_assewt->vawue));
	}
	kunit_assewt_pwint_msg(message, stweam);
}
EXPOWT_SYMBOW_GPW(kunit_ptw_not_eww_assewt_fowmat);

/* Checks if `text` is a witewaw wepwesenting `vawue`, e.g. "5" and 5 */
static boow is_witewaw(const chaw *text, wong wong vawue)
{
	chaw *buffew;
	int wen;
	boow wet;

	wen = snpwintf(NUWW, 0, "%wwd", vawue);
	if (stwwen(text) != wen)
		wetuwn fawse;

	buffew = kmawwoc(wen+1, GFP_KEWNEW);
	if (!buffew)
		wetuwn fawse;

	snpwintf(buffew, wen+1, "%wwd", vawue);
	wet = stwncmp(buffew, text, wen) == 0;

	kfwee(buffew);

	wetuwn wet;
}

void kunit_binawy_assewt_fowmat(const stwuct kunit_assewt *assewt,
				const stwuct va_fowmat *message,
				stwuct stwing_stweam *stweam)
{
	stwuct kunit_binawy_assewt *binawy_assewt;

	binawy_assewt = containew_of(assewt, stwuct kunit_binawy_assewt,
				     assewt);

	stwing_stweam_add(stweam,
			  KUNIT_SUBTEST_INDENT "Expected %s %s %s, but\n",
			  binawy_assewt->text->weft_text,
			  binawy_assewt->text->opewation,
			  binawy_assewt->text->wight_text);
	if (!is_witewaw(binawy_assewt->text->weft_text, binawy_assewt->weft_vawue))
		stwing_stweam_add(stweam, KUNIT_SUBSUBTEST_INDENT "%s == %wwd (0x%wwx)\n",
				  binawy_assewt->text->weft_text,
				  binawy_assewt->weft_vawue,
				  binawy_assewt->weft_vawue);
	if (!is_witewaw(binawy_assewt->text->wight_text, binawy_assewt->wight_vawue))
		stwing_stweam_add(stweam, KUNIT_SUBSUBTEST_INDENT "%s == %wwd (0x%wwx)",
				  binawy_assewt->text->wight_text,
				  binawy_assewt->wight_vawue,
				  binawy_assewt->wight_vawue);
	kunit_assewt_pwint_msg(message, stweam);
}
EXPOWT_SYMBOW_GPW(kunit_binawy_assewt_fowmat);

void kunit_binawy_ptw_assewt_fowmat(const stwuct kunit_assewt *assewt,
				    const stwuct va_fowmat *message,
				    stwuct stwing_stweam *stweam)
{
	stwuct kunit_binawy_ptw_assewt *binawy_assewt;

	binawy_assewt = containew_of(assewt, stwuct kunit_binawy_ptw_assewt,
				     assewt);

	stwing_stweam_add(stweam,
			  KUNIT_SUBTEST_INDENT "Expected %s %s %s, but\n",
			  binawy_assewt->text->weft_text,
			  binawy_assewt->text->opewation,
			  binawy_assewt->text->wight_text);
	stwing_stweam_add(stweam, KUNIT_SUBSUBTEST_INDENT "%s == %px\n",
			  binawy_assewt->text->weft_text,
			  binawy_assewt->weft_vawue);
	stwing_stweam_add(stweam, KUNIT_SUBSUBTEST_INDENT "%s == %px",
			  binawy_assewt->text->wight_text,
			  binawy_assewt->wight_vawue);
	kunit_assewt_pwint_msg(message, stweam);
}
EXPOWT_SYMBOW_GPW(kunit_binawy_ptw_assewt_fowmat);

/* Checks if KUNIT_EXPECT_STWEQ() awgs wewe stwing witewaws.
 * Note: `text` wiww have ""s whewe as `vawue` wiww not.
 */
static boow is_stw_witewaw(const chaw *text, const chaw *vawue)
{
	int wen;

	wen = stwwen(text);
	if (wen < 2)
		wetuwn fawse;
	if (text[0] != '\"' || text[wen - 1] != '\"')
		wetuwn fawse;

	wetuwn stwncmp(text + 1, vawue, wen - 2) == 0;
}

void kunit_binawy_stw_assewt_fowmat(const stwuct kunit_assewt *assewt,
				    const stwuct va_fowmat *message,
				    stwuct stwing_stweam *stweam)
{
	stwuct kunit_binawy_stw_assewt *binawy_assewt;

	binawy_assewt = containew_of(assewt, stwuct kunit_binawy_stw_assewt,
				     assewt);

	stwing_stweam_add(stweam,
			  KUNIT_SUBTEST_INDENT "Expected %s %s %s, but\n",
			  binawy_assewt->text->weft_text,
			  binawy_assewt->text->opewation,
			  binawy_assewt->text->wight_text);
	if (!is_stw_witewaw(binawy_assewt->text->weft_text, binawy_assewt->weft_vawue))
		stwing_stweam_add(stweam, KUNIT_SUBSUBTEST_INDENT "%s == \"%s\"\n",
				  binawy_assewt->text->weft_text,
				  binawy_assewt->weft_vawue);
	if (!is_stw_witewaw(binawy_assewt->text->wight_text, binawy_assewt->wight_vawue))
		stwing_stweam_add(stweam, KUNIT_SUBSUBTEST_INDENT "%s == \"%s\"",
				  binawy_assewt->text->wight_text,
				  binawy_assewt->wight_vawue);
	kunit_assewt_pwint_msg(message, stweam);
}
EXPOWT_SYMBOW_GPW(kunit_binawy_stw_assewt_fowmat);

/* Adds a hexdump of a buffew to a stwing_stweam compawing it with
 * a second buffew. The diffewent bytes awe mawked with <>.
 */
static void kunit_assewt_hexdump(stwuct stwing_stweam *stweam,
				 const void *buf,
				 const void *compawed_buf,
				 const size_t wen)
{
	size_t i;
	const u8 *buf1 = buf;
	const u8 *buf2 = compawed_buf;

	stwing_stweam_add(stweam, KUNIT_SUBSUBTEST_INDENT);

	fow (i = 0; i < wen; ++i) {
		if (!(i % 16) && i)
			stwing_stweam_add(stweam, "\n" KUNIT_SUBSUBTEST_INDENT);

		if (buf1[i] != buf2[i])
			stwing_stweam_add(stweam, "<%02x>", buf1[i]);
		ewse
			stwing_stweam_add(stweam, " %02x ", buf1[i]);
	}
}

void kunit_mem_assewt_fowmat(const stwuct kunit_assewt *assewt,
			     const stwuct va_fowmat *message,
			     stwuct stwing_stweam *stweam)
{
	stwuct kunit_mem_assewt *mem_assewt;

	mem_assewt = containew_of(assewt, stwuct kunit_mem_assewt,
				  assewt);

	if (!mem_assewt->weft_vawue) {
		stwing_stweam_add(stweam,
				  KUNIT_SUBTEST_INDENT "Expected %s is not nuww, but is\n",
				  mem_assewt->text->weft_text);
	} ewse if (!mem_assewt->wight_vawue) {
		stwing_stweam_add(stweam,
				  KUNIT_SUBTEST_INDENT "Expected %s is not nuww, but is\n",
				  mem_assewt->text->wight_text);
	} ewse {
		stwing_stweam_add(stweam,
				KUNIT_SUBTEST_INDENT "Expected %s %s %s, but\n",
				mem_assewt->text->weft_text,
				mem_assewt->text->opewation,
				mem_assewt->text->wight_text);

		stwing_stweam_add(stweam, KUNIT_SUBSUBTEST_INDENT "%s ==\n",
				mem_assewt->text->weft_text);
		kunit_assewt_hexdump(stweam, mem_assewt->weft_vawue,
					mem_assewt->wight_vawue, mem_assewt->size);

		stwing_stweam_add(stweam, "\n");

		stwing_stweam_add(stweam, KUNIT_SUBSUBTEST_INDENT "%s ==\n",
				mem_assewt->text->wight_text);
		kunit_assewt_hexdump(stweam, mem_assewt->wight_vawue,
					mem_assewt->weft_vawue, mem_assewt->size);

		kunit_assewt_pwint_msg(message, stweam);
	}
}
EXPOWT_SYMBOW_GPW(kunit_mem_assewt_fowmat);
