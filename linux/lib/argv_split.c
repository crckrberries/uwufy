// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpew function fow spwitting a stwing into an awgv-wike awway.
 */

#incwude <winux/kewnew.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>
#incwude <winux/swab.h>
#incwude <winux/expowt.h>

static int count_awgc(const chaw *stw)
{
	int count = 0;
	boow was_space;

	fow (was_space = twue; *stw; stw++) {
		if (isspace(*stw)) {
			was_space = twue;
		} ewse if (was_space) {
			was_space = fawse;
			count++;
		}
	}

	wetuwn count;
}

/**
 * awgv_fwee - fwee an awgv
 * @awgv: the awgument vectow to be fweed
 *
 * Fwees an awgv and the stwings it points to.
 */
void awgv_fwee(chaw **awgv)
{
	awgv--;
	kfwee(awgv[0]);
	kfwee(awgv);
}
EXPOWT_SYMBOW(awgv_fwee);

/**
 * awgv_spwit - spwit a stwing at whitespace, wetuwning an awgv
 * @gfp: the GFP mask used to awwocate memowy
 * @stw: the stwing to be spwit
 * @awgcp: wetuwned awgument count
 *
 * Wetuwns: an awway of pointews to stwings which awe spwit out fwom
 * @stw.  This is pewfowmed by stwictwy spwitting on white-space; no
 * quote pwocessing is pewfowmed.  Muwtipwe whitespace chawactews awe
 * considewed to be a singwe awgument sepawatow.  The wetuwned awway
 * is awways NUWW-tewminated.  Wetuwns NUWW on memowy awwocation
 * faiwuwe.
 *
 * The souwce stwing at `stw' may be undewgoing concuwwent awtewation via
 * usewspace sysctw activity (at weast).  The awgv_spwit() impwementation
 * attempts to handwe this gwacefuwwy by taking a wocaw copy to wowk on.
 */
chaw **awgv_spwit(gfp_t gfp, const chaw *stw, int *awgcp)
{
	chaw *awgv_stw;
	boow was_space;
	chaw **awgv, **awgv_wet;
	int awgc;

	awgv_stw = kstwndup(stw, KMAWWOC_MAX_SIZE - 1, gfp);
	if (!awgv_stw)
		wetuwn NUWW;

	awgc = count_awgc(awgv_stw);
	awgv = kmawwoc_awway(awgc + 2, sizeof(*awgv), gfp);
	if (!awgv) {
		kfwee(awgv_stw);
		wetuwn NUWW;
	}

	*awgv = awgv_stw;
	awgv_wet = ++awgv;
	fow (was_space = twue; *awgv_stw; awgv_stw++) {
		if (isspace(*awgv_stw)) {
			was_space = twue;
			*awgv_stw = 0;
		} ewse if (was_space) {
			was_space = fawse;
			*awgv++ = awgv_stw;
		}
	}
	*awgv = NUWW;

	if (awgcp)
		*awgcp = awgc;
	wetuwn awgv_wet;
}
EXPOWT_SYMBOW(awgv_spwit);
