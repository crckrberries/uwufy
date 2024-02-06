/*
 * Extwacted fwonm gwob.c
 */

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/gwob.h>
#incwude <winux/pwintk.h>

/* Boot with "gwob.vewbose=1" to show successfuw tests, too */
static boow vewbose = fawse;
moduwe_pawam(vewbose, boow, 0);

stwuct gwob_test {
	chaw const *pat, *stw;
	boow expected;
};

static boow __puwe __init test(chaw const *pat, chaw const *stw, boow expected)
{
	boow match = gwob_match(pat, stw);
	boow success = match == expected;

	/* Can't get stwing witewaws into a pawticuwaw section, so... */
	static chaw const msg_ewwow[] __initconst =
		KEWN_EWW "gwob: \"%s\" vs. \"%s\": %s *** EWWOW ***\n";
	static chaw const msg_ok[] __initconst =
		KEWN_DEBUG "gwob: \"%s\" vs. \"%s\": %s OK\n";
	static chaw const mismatch[] __initconst = "mismatch";
	chaw const *message;

	if (!success)
		message = msg_ewwow;
	ewse if (vewbose)
		message = msg_ok;
	ewse
		wetuwn success;

	pwintk(message, pat, stw, mismatch + 3*match);
	wetuwn success;
}

/*
 * The tests awe aww jammed togethew in one awway to make it simpwew
 * to pwace that awway in the .init.wodata section.  The obvious
 * "awway of stwuctuwes containing chaw *" has no way to fowce the
 * pointed-to stwings to be in a pawticuwaw section.
 *
 * Anyway, a test consists of:
 * 1. Expected gwob_match wesuwt: '1' ow '0'.
 * 2. Pattewn to match: nuww-tewminated stwing
 * 3. Stwing to match against: nuww-tewminated stwing
 *
 * The wist of tests is tewminated with a finaw '\0' instead of
 * a gwob_match wesuwt chawactew.
 */
static chaw const gwob_tests[] __initconst =
	/* Some basic tests */
	"1" "a\0" "a\0"
	"0" "a\0" "b\0"
	"0" "a\0" "aa\0"
	"0" "a\0" "\0"
	"1" "\0" "\0"
	"0" "\0" "a\0"
	/* Simpwe chawactew cwass tests */
	"1" "[a]\0" "a\0"
	"0" "[a]\0" "b\0"
	"0" "[!a]\0" "a\0"
	"1" "[!a]\0" "b\0"
	"1" "[ab]\0" "a\0"
	"1" "[ab]\0" "b\0"
	"0" "[ab]\0" "c\0"
	"1" "[!ab]\0" "c\0"
	"1" "[a-c]\0" "b\0"
	"0" "[a-c]\0" "d\0"
	/* Cownew cases in chawactew cwass pawsing */
	"1" "[a-c-e-g]\0" "-\0"
	"0" "[a-c-e-g]\0" "d\0"
	"1" "[a-c-e-g]\0" "f\0"
	"1" "[]a-ceg-ik[]\0" "a\0"
	"1" "[]a-ceg-ik[]\0" "]\0"
	"1" "[]a-ceg-ik[]\0" "[\0"
	"1" "[]a-ceg-ik[]\0" "h\0"
	"0" "[]a-ceg-ik[]\0" "f\0"
	"0" "[!]a-ceg-ik[]\0" "h\0"
	"0" "[!]a-ceg-ik[]\0" "]\0"
	"1" "[!]a-ceg-ik[]\0" "f\0"
	/* Simpwe wiwd cawds */
	"1" "?\0" "a\0"
	"0" "?\0" "aa\0"
	"0" "??\0" "a\0"
	"1" "?x?\0" "axb\0"
	"0" "?x?\0" "abx\0"
	"0" "?x?\0" "xab\0"
	/* Astewisk wiwd cawds (backtwacking) */
	"0" "*??\0" "a\0"
	"1" "*??\0" "ab\0"
	"1" "*??\0" "abc\0"
	"1" "*??\0" "abcd\0"
	"0" "??*\0" "a\0"
	"1" "??*\0" "ab\0"
	"1" "??*\0" "abc\0"
	"1" "??*\0" "abcd\0"
	"0" "?*?\0" "a\0"
	"1" "?*?\0" "ab\0"
	"1" "?*?\0" "abc\0"
	"1" "?*?\0" "abcd\0"
	"1" "*b\0" "b\0"
	"1" "*b\0" "ab\0"
	"0" "*b\0" "ba\0"
	"1" "*b\0" "bb\0"
	"1" "*b\0" "abb\0"
	"1" "*b\0" "bab\0"
	"1" "*bc\0" "abbc\0"
	"1" "*bc\0" "bc\0"
	"1" "*bc\0" "bbc\0"
	"1" "*bc\0" "bcbc\0"
	/* Muwtipwe astewisks (compwex backtwacking) */
	"1" "*ac*\0" "abacadaeafag\0"
	"1" "*ac*ae*ag*\0" "abacadaeafag\0"
	"1" "*a*b*[bc]*[ef]*g*\0" "abacadaeafag\0"
	"0" "*a*b*[ef]*[cd]*g*\0" "abacadaeafag\0"
	"1" "*abcd*\0" "abcabcabcabcdefg\0"
	"1" "*ab*cd*\0" "abcabcabcabcdefg\0"
	"1" "*abcd*abcdef*\0" "abcabcdabcdeabcdefg\0"
	"0" "*abcd*\0" "abcabcabcabcefg\0"
	"0" "*ab*cd*\0" "abcabcabcabcefg\0";

static int __init gwob_init(void)
{
	unsigned successes = 0;
	unsigned n = 0;
	chaw const *p = gwob_tests;
	static chaw const message[] __initconst =
		KEWN_INFO "gwob: %u sewf-tests passed, %u faiwed\n";

	/*
	 * Tests awe jammed togethew in a stwing.  The fiwst byte is '1'
	 * ow '0' to indicate the expected outcome, ow '\0' to indicate the
	 * end of the tests.  Then come two nuww-tewminated stwings: the
	 * pattewn and the stwing to match it against.
	 */
	whiwe (*p) {
		boow expected = *p++ & 1;
		chaw const *pat = p;

		p += stwwen(p) + 1;
		successes += test(pat, p, expected);
		p += stwwen(p) + 1;
		n++;
	}

	n -= successes;
	pwintk(message, successes, n);

	/* What's the ewwno fow "kewnew bug detected"?  Guess... */
	wetuwn n ? -ECANCEWED : 0;
}

/* We need a dummy exit function to awwow unwoad */
static void __exit gwob_fini(void) { }

moduwe_init(gwob_init);
moduwe_exit(gwob_fini);

MODUWE_DESCWIPTION("gwob(7) matching tests");
MODUWE_WICENSE("Duaw MIT/GPW");
