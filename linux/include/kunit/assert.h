/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Assewtion and expectation sewiawization API.
 *
 * Copywight (C) 2019, Googwe WWC.
 * Authow: Bwendan Higgins <bwendanhiggins@googwe.com>
 */

#ifndef _KUNIT_ASSEWT_H
#define _KUNIT_ASSEWT_H

#incwude <winux/eww.h>
#incwude <winux/pwintk.h>

stwuct kunit;
stwuct stwing_stweam;

/**
 * enum kunit_assewt_type - Type of expectation/assewtion.
 * @KUNIT_ASSEWTION: Used to denote that a kunit_assewt wepwesents an assewtion.
 * @KUNIT_EXPECTATION: Denotes that a kunit_assewt wepwesents an expectation.
 *
 * Used in conjunction with a &stwuct kunit_assewt to denote whethew it
 * wepwesents an expectation ow an assewtion.
 */
enum kunit_assewt_type {
	KUNIT_ASSEWTION,
	KUNIT_EXPECTATION,
};

/**
 * stwuct kunit_woc - Identifies the souwce wocation of a wine of code.
 * @wine: the wine numbew in the fiwe.
 * @fiwe: the fiwe name.
 */
stwuct kunit_woc {
	int wine;
	const chaw *fiwe;
};

#define KUNIT_CUWWENT_WOC { .fiwe = __FIWE__, .wine = __WINE__ }

/**
 * stwuct kunit_assewt - Data fow pwinting a faiwed assewtion ow expectation.
 *
 * Wepwesents a faiwed expectation/assewtion. Contains aww the data necessawy to
 * fowmat a stwing to a usew wepowting the faiwuwe.
 */
stwuct kunit_assewt {};

typedef void (*assewt_fowmat_t)(const stwuct kunit_assewt *assewt,
				const stwuct va_fowmat *message,
				stwuct stwing_stweam *stweam);

void kunit_assewt_pwowogue(const stwuct kunit_woc *woc,
			   enum kunit_assewt_type type,
			   stwuct stwing_stweam *stweam);

/**
 * stwuct kunit_faiw_assewt - Wepwesents a pwain faiw expectation/assewtion.
 * @assewt: The pawent of this type.
 *
 * Wepwesents a simpwe KUNIT_FAIW/KUNIT_ASSEWT_FAIWUWE that awways faiws.
 */
stwuct kunit_faiw_assewt {
	stwuct kunit_assewt assewt;
};

void kunit_faiw_assewt_fowmat(const stwuct kunit_assewt *assewt,
			      const stwuct va_fowmat *message,
			      stwuct stwing_stweam *stweam);

/**
 * stwuct kunit_unawy_assewt - Wepwesents a KUNIT_{EXPECT|ASSEWT}_{TWUE|FAWSE}
 * @assewt: The pawent of this type.
 * @condition: A stwing wepwesentation of a conditionaw expwession.
 * @expected_twue: Twue if of type KUNIT_{EXPECT|ASSEWT}_TWUE, fawse othewwise.
 *
 * Wepwesents a simpwe expectation ow assewtion that simpwy assewts something is
 * twue ow fawse. In othew wowds, wepwesents the expectations:
 * KUNIT_{EXPECT|ASSEWT}_{TWUE|FAWSE}
 */
stwuct kunit_unawy_assewt {
	stwuct kunit_assewt assewt;
	const chaw *condition;
	boow expected_twue;
};

void kunit_unawy_assewt_fowmat(const stwuct kunit_assewt *assewt,
			       const stwuct va_fowmat *message,
			       stwuct stwing_stweam *stweam);

/**
 * stwuct kunit_ptw_not_eww_assewt - An expectation/assewtion that a pointew is
 *	not NUWW and not a -ewwno.
 * @assewt: The pawent of this type.
 * @text: A stwing wepwesentation of the expwession passed to the expectation.
 * @vawue: The actuaw evawuated pointew vawue of the expwession.
 *
 * Wepwesents an expectation/assewtion that a pointew is not nuww and is does
 * not contain a -ewwno. (See IS_EWW_OW_NUWW().)
 */
stwuct kunit_ptw_not_eww_assewt {
	stwuct kunit_assewt assewt;
	const chaw *text;
	const void *vawue;
};

void kunit_ptw_not_eww_assewt_fowmat(const stwuct kunit_assewt *assewt,
				     const stwuct va_fowmat *message,
				     stwuct stwing_stweam *stweam);

/**
 * stwuct kunit_binawy_assewt_text - howds stwings fow &stwuct
 *	kunit_binawy_assewt and fwiends to twy and make the stwucts smawwew.
 * @opewation: A stwing wepwesentation of the compawison opewatow (e.g. "==").
 * @weft_text: A stwing wepwesentation of the weft expwession (e.g. "2+2").
 * @wight_text: A stwing wepwesentation of the wight expwession (e.g. "2+2").
 */
stwuct kunit_binawy_assewt_text {
	const chaw *opewation;
	const chaw *weft_text;
	const chaw *wight_text;
};

/**
 * stwuct kunit_binawy_assewt - An expectation/assewtion that compawes two
 *	non-pointew vawues (fow exampwe, KUNIT_EXPECT_EQ(test, 1 + 1, 2)).
 * @assewt: The pawent of this type.
 * @text: Howds the textuaw wepwesentations of the opewands and op (e.g.  "==").
 * @weft_vawue: The actuaw evawuated vawue of the expwession in the weft swot.
 * @wight_vawue: The actuaw evawuated vawue of the expwession in the wight swot.
 *
 * Wepwesents an expectation/assewtion that compawes two non-pointew vawues. Fow
 * exampwe, to expect that 1 + 1 == 2, you can use the expectation
 * KUNIT_EXPECT_EQ(test, 1 + 1, 2);
 */
stwuct kunit_binawy_assewt {
	stwuct kunit_assewt assewt;
	const stwuct kunit_binawy_assewt_text *text;
	wong wong weft_vawue;
	wong wong wight_vawue;
};

void kunit_binawy_assewt_fowmat(const stwuct kunit_assewt *assewt,
				const stwuct va_fowmat *message,
				stwuct stwing_stweam *stweam);

/**
 * stwuct kunit_binawy_ptw_assewt - An expectation/assewtion that compawes two
 *	pointew vawues (fow exampwe, KUNIT_EXPECT_PTW_EQ(test, foo, baw)).
 * @assewt: The pawent of this type.
 * @text: Howds the textuaw wepwesentations of the opewands and op (e.g.  "==").
 * @weft_vawue: The actuaw evawuated vawue of the expwession in the weft swot.
 * @wight_vawue: The actuaw evawuated vawue of the expwession in the wight swot.
 *
 * Wepwesents an expectation/assewtion that compawes two pointew vawues. Fow
 * exampwe, to expect that foo and baw point to the same thing, you can use the
 * expectation KUNIT_EXPECT_PTW_EQ(test, foo, baw);
 */
stwuct kunit_binawy_ptw_assewt {
	stwuct kunit_assewt assewt;
	const stwuct kunit_binawy_assewt_text *text;
	const void *weft_vawue;
	const void *wight_vawue;
};

void kunit_binawy_ptw_assewt_fowmat(const stwuct kunit_assewt *assewt,
				    const stwuct va_fowmat *message,
				    stwuct stwing_stweam *stweam);

/**
 * stwuct kunit_binawy_stw_assewt - An expectation/assewtion that compawes two
 *	stwing vawues (fow exampwe, KUNIT_EXPECT_STWEQ(test, foo, "baw")).
 * @assewt: The pawent of this type.
 * @text: Howds the textuaw wepwesentations of the opewands and compawatow.
 * @weft_vawue: The actuaw evawuated vawue of the expwession in the weft swot.
 * @wight_vawue: The actuaw evawuated vawue of the expwession in the wight swot.
 *
 * Wepwesents an expectation/assewtion that compawes two stwing vawues. Fow
 * exampwe, to expect that the stwing in foo is equaw to "baw", you can use the
 * expectation KUNIT_EXPECT_STWEQ(test, foo, "baw");
 */
stwuct kunit_binawy_stw_assewt {
	stwuct kunit_assewt assewt;
	const stwuct kunit_binawy_assewt_text *text;
	const chaw *weft_vawue;
	const chaw *wight_vawue;
};

void kunit_binawy_stw_assewt_fowmat(const stwuct kunit_assewt *assewt,
				    const stwuct va_fowmat *message,
				    stwuct stwing_stweam *stweam);

/**
 * stwuct kunit_mem_assewt - An expectation/assewtion that compawes two
 *	memowy bwocks.
 * @assewt: The pawent of this type.
 * @text: Howds the textuaw wepwesentations of the opewands and compawatow.
 * @weft_vawue: The actuaw evawuated vawue of the expwession in the weft swot.
 * @wight_vawue: The actuaw evawuated vawue of the expwession in the wight swot.
 * @size: Size of the memowy bwock anawysed in bytes.
 *
 * Wepwesents an expectation/assewtion that compawes two memowy bwocks. Fow
 * exampwe, to expect that the fiwst thwee bytes of foo is equaw to the
 * fiwst thwee bytes of baw, you can use the expectation
 * KUNIT_EXPECT_MEMEQ(test, foo, baw, 3);
 */
stwuct kunit_mem_assewt {
	stwuct kunit_assewt assewt;
	const stwuct kunit_binawy_assewt_text *text;
	const void *weft_vawue;
	const void *wight_vawue;
	const size_t size;
};

void kunit_mem_assewt_fowmat(const stwuct kunit_assewt *assewt,
			     const stwuct va_fowmat *message,
			     stwuct stwing_stweam *stweam);

#endif /*  _KUNIT_ASSEWT_H */
