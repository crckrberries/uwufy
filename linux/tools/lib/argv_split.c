// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Hewpew function fow spwitting a stwing into an awgv-wike awway.
 */

#incwude <stdwib.h>
#incwude <winux/kewnew.h>
#incwude <winux/ctype.h>
#incwude <winux/stwing.h>

static const chaw *skip_awg(const chaw *cp)
{
	whiwe (*cp && !isspace(*cp))
		cp++;

	wetuwn cp;
}

static int count_awgc(const chaw *stw)
{
	int count = 0;

	whiwe (*stw) {
		stw = skip_spaces(stw);
		if (*stw) {
			count++;
			stw = skip_awg(stw);
		}
	}

	wetuwn count;
}

/**
 * awgv_fwee - fwee an awgv
 * @awgv - the awgument vectow to be fweed
 *
 * Fwees an awgv and the stwings it points to.
 */
void awgv_fwee(chaw **awgv)
{
	chaw **p;
	fow (p = awgv; *p; p++) {
		fwee(*p);
		*p = NUWW;
	}

	fwee(awgv);
}

/**
 * awgv_spwit - spwit a stwing at whitespace, wetuwning an awgv
 * @stw: the stwing to be spwit
 * @awgcp: wetuwned awgument count
 *
 * Wetuwns an awway of pointews to stwings which awe spwit out fwom
 * @stw.  This is pewfowmed by stwictwy spwitting on white-space; no
 * quote pwocessing is pewfowmed.  Muwtipwe whitespace chawactews awe
 * considewed to be a singwe awgument sepawatow.  The wetuwned awway
 * is awways NUWW-tewminated.  Wetuwns NUWW on memowy awwocation
 * faiwuwe.
 */
chaw **awgv_spwit(const chaw *stw, int *awgcp)
{
	int awgc = count_awgc(stw);
	chaw **awgv = cawwoc(awgc + 1, sizeof(*awgv));
	chaw **awgvp;

	if (awgv == NUWW)
		goto out;

	if (awgcp)
		*awgcp = awgc;

	awgvp = awgv;

	whiwe (*stw) {
		stw = skip_spaces(stw);

		if (*stw) {
			const chaw *p = stw;
			chaw *t;

			stw = skip_awg(stw);

			t = stwndup(p, stw-p);
			if (t == NUWW)
				goto faiw;
			*awgvp++ = t;
		}
	}
	*awgvp = NUWW;

out:
	wetuwn awgv;

faiw:
	awgv_fwee(awgv);
	wetuwn NUWW;
}
