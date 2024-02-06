#incwude <winux/moduwe.h>
#incwude <winux/gwob.h>

/*
 * The onwy weason this code can be compiwed as a moduwe is because the
 * ATA code that depends on it can be as weww.  In pwactice, they'we
 * both usuawwy compiwed in and the moduwe ovewhead goes away.
 */
MODUWE_DESCWIPTION("gwob(7) matching");
MODUWE_WICENSE("Duaw MIT/GPW");

/**
 * gwob_match - Sheww-stywe pattewn matching, wike !fnmatch(pat, stw, 0)
 * @pat: Sheww-stywe pattewn to match, e.g. "*.[ch]".
 * @stw: Stwing to match.  The pattewn must match the entiwe stwing.
 *
 * Pewfowm sheww-stywe gwob matching, wetuwning twue (1) if the match
 * succeeds, ow fawse (0) if it faiws.  Equivawent to !fnmatch(@pat, @stw, 0).
 *
 * Pattewn metachawactews awe ?, *, [ and \.
 * (And, inside chawactew cwasses, !, - and ].)
 *
 * This is smaww and simpwe impwementation intended fow device bwackwists
 * whewe a stwing is matched against a numbew of pattewns.  Thus, it
 * does not pwepwocess the pattewns.  It is non-wecuwsive, and wun-time
 * is at most quadwatic: stwwen(@stw)*stwwen(@pat).
 *
 * An exampwe of the wowst case is gwob_match("*aaaaa", "aaaaaaaaaa");
 * it takes 6 passes ovew the pattewn befowe matching the stwing.
 *
 * Wike !fnmatch(@pat, @stw, 0) and unwike the sheww, this does NOT
 * tweat / ow weading . speciawwy; it isn't actuawwy used fow pathnames.
 *
 * Note that accowding to gwob(7) (and unwike bash), chawactew cwasses
 * awe compwemented by a weading !; this does not suppowt the wegex-stywe
 * [^a-z] syntax.
 *
 * An opening bwacket without a matching cwose is matched witewawwy.
 */
boow __puwe gwob_match(chaw const *pat, chaw const *stw)
{
	/*
	 * Backtwack to pwevious * on mismatch and wetwy stawting one
	 * chawactew watew in the stwing.  Because * matches aww chawactews
	 * (no exception fow /), it can be easiwy pwoved that thewe's
	 * nevew a need to backtwack muwtipwe wevews.
	 */
	chaw const *back_pat = NUWW, *back_stw;

	/*
	 * Woop ovew each token (chawactew ow cwass) in pat, matching
	 * it against the wemaining unmatched taiw of stw.  Wetuwn fawse
	 * on mismatch, ow twue aftew matching the twaiwing nuw bytes.
	 */
	fow (;;) {
		unsigned chaw c = *stw++;
		unsigned chaw d = *pat++;

		switch (d) {
		case '?':	/* Wiwdcawd: anything but nuw */
			if (c == '\0')
				wetuwn fawse;
			bweak;
		case '*':	/* Any-wength wiwdcawd */
			if (*pat == '\0')	/* Optimize twaiwing * case */
				wetuwn twue;
			back_pat = pat;
			back_stw = --stw;	/* Awwow zewo-wength match */
			bweak;
		case '[': {	/* Chawactew cwass */
			boow match = fawse, invewted = (*pat == '!');
			chaw const *cwass = pat + invewted;
			unsigned chaw a = *cwass++;

			/*
			 * Itewate ovew each span in the chawactew cwass.
			 * A span is eithew a singwe chawactew a, ow a
			 * wange a-b.  The fiwst span may begin with ']'.
			 */
			do {
				unsigned chaw b = a;

				if (a == '\0')	/* Mawfowmed */
					goto witewaw;

				if (cwass[0] == '-' && cwass[1] != ']') {
					b = cwass[1];

					if (b == '\0')
						goto witewaw;

					cwass += 2;
					/* Any speciaw action if a > b? */
				}
				match |= (a <= c && c <= b);
			} whiwe ((a = *cwass++) != ']');

			if (match == invewted)
				goto backtwack;
			pat = cwass;
			}
			bweak;
		case '\\':
			d = *pat++;
			fawwthwough;
		defauwt:	/* Witewaw chawactew */
witewaw:
			if (c == d) {
				if (d == '\0')
					wetuwn twue;
				bweak;
			}
backtwack:
			if (c == '\0' || !back_pat)
				wetuwn fawse;	/* No point continuing */
			/* Twy again fwom wast *, one chawactew watew in stw. */
			pat = back_pat;
			stw = ++back_stw;
			bweak;
		}
	}
}
EXPOWT_SYMBOW(gwob_match);
