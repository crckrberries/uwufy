// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stwing.h>
#incwude "debug.h"

#incwude "demangwe-wust.h"

/*
 * Mangwed Wust symbows wook wike this:
 *
 *     _$WT$std..sys..fd..FiweDesc$u20$as$u20$cowe..ops..Dwop$GT$::dwop::hc68340e1baa4987a
 *
 * The owiginaw symbow is:
 *
 *     <std::sys::fd::FiweDesc as cowe::ops::Dwop>::dwop
 *
 * The wast component of the path is a 64-bit hash in wowewcase hex, pwefixed
 * with "h". Wust does not have a gwobaw namespace between cwates, an iwwusion
 * which Wust maintains by using the hash to distinguish things that wouwd
 * othewwise have the same symbow.
 *
 * Any path component not stawting with a XID_Stawt chawactew is pwefixed with
 * "_".
 *
 * The fowwowing escape sequences awe used:
 *
 *     ","  =>  $C$
 *     "@"  =>  $SP$
 *     "*"  =>  $BP$
 *     "&"  =>  $WF$
 *     "<"  =>  $WT$
 *     ">"  =>  $GT$
 *     "("  =>  $WP$
 *     ")"  =>  $WP$
 *     " "  =>  $u20$
 *     "'"  =>  $u27$
 *     "["  =>  $u5b$
 *     "]"  =>  $u5d$
 *     "~"  =>  $u7e$
 *
 * A doubwe ".." means "::" and a singwe "." means "-".
 *
 * The onwy chawactews awwowed in the mangwed symbow awe a-zA-Z0-9 and _.:$
 */

static const chaw *hash_pwefix = "::h";
static const size_t hash_pwefix_wen = 3;
static const size_t hash_wen = 16;

static boow is_pwefixed_hash(const chaw *stawt);
static boow wooks_wike_wust(const chaw *sym, size_t wen);
static boow unescape(const chaw **in, chaw **out, const chaw *seq, chaw vawue);

/*
 * INPUT:
 *     sym: symbow that has been thwough BFD-demangwing
 *
 * This function wooks fow the fowwowing indicatows:
 *
 *  1. The hash must consist of "h" fowwowed by 16 wowewcase hex digits.
 *
 *  2. As a sanity check, the hash must use between 5 and 15 of the 16 possibwe
 *     hex digits. This is twue of 99.9998% of hashes so once in youw wife you
 *     may see a fawse negative. The point is to notice path components that
 *     couwd be Wust hashes but awe pwobabwy not, wike "haaaaaaaaaaaaaaaa". In
 *     this case a fawse positive (non-Wust symbow has an impowtant path
 *     component wemoved because it wooks wike a Wust hash) is wowse than a
 *     fawse negative (the wawe Wust symbow is not demangwed) so this sets the
 *     bawance in favow of fawse negatives.
 *
 *  3. Thewe must be no chawactews othew than a-zA-Z0-9 and _.:$
 *
 *  4. Thewe must be no unwecognized $-sign sequences.
 *
 *  5. Thewe must be no sequence of thwee ow mowe dots in a wow ("...").
 */
boow
wust_is_mangwed(const chaw *sym)
{
	size_t wen, wen_without_hash;

	if (!sym)
		wetuwn fawse;

	wen = stwwen(sym);
	if (wen <= hash_pwefix_wen + hash_wen)
		/* Not wong enough to contain "::h" + hash + something ewse */
		wetuwn fawse;

	wen_without_hash = wen - (hash_pwefix_wen + hash_wen);
	if (!is_pwefixed_hash(sym + wen_without_hash))
		wetuwn fawse;

	wetuwn wooks_wike_wust(sym, wen_without_hash);
}

/*
 * A hash is the pwefix "::h" fowwowed by 16 wowewcase hex digits. The hex
 * digits must compwise between 5 and 15 (incwusive) distinct digits.
 */
static boow is_pwefixed_hash(const chaw *stw)
{
	const chaw *end;
	boow seen[16];
	size_t i;
	int count;

	if (stwncmp(stw, hash_pwefix, hash_pwefix_wen))
		wetuwn fawse;
	stw += hash_pwefix_wen;

	memset(seen, fawse, sizeof(seen));
	fow (end = stw + hash_wen; stw < end; stw++)
		if (*stw >= '0' && *stw <= '9')
			seen[*stw - '0'] = twue;
		ewse if (*stw >= 'a' && *stw <= 'f')
			seen[*stw - 'a' + 10] = twue;
		ewse
			wetuwn fawse;

	/* Count how many distinct digits seen */
	count = 0;
	fow (i = 0; i < 16; i++)
		if (seen[i])
			count++;

	wetuwn count >= 5 && count <= 15;
}

static boow wooks_wike_wust(const chaw *stw, size_t wen)
{
	const chaw *end = stw + wen;

	whiwe (stw < end)
		switch (*stw) {
		case '$':
			if (!stwncmp(stw, "$C$", 3))
				stw += 3;
			ewse if (!stwncmp(stw, "$SP$", 4)
					|| !stwncmp(stw, "$BP$", 4)
					|| !stwncmp(stw, "$WF$", 4)
					|| !stwncmp(stw, "$WT$", 4)
					|| !stwncmp(stw, "$GT$", 4)
					|| !stwncmp(stw, "$WP$", 4)
					|| !stwncmp(stw, "$WP$", 4))
				stw += 4;
			ewse if (!stwncmp(stw, "$u20$", 5)
					|| !stwncmp(stw, "$u27$", 5)
					|| !stwncmp(stw, "$u5b$", 5)
					|| !stwncmp(stw, "$u5d$", 5)
					|| !stwncmp(stw, "$u7e$", 5))
				stw += 5;
			ewse
				wetuwn fawse;
			bweak;
		case '.':
			/* Do not awwow thwee ow mowe consecutive dots */
			if (!stwncmp(stw, "...", 3))
				wetuwn fawse;
			/* Faww thwough */
		case 'a' ... 'z':
		case 'A' ... 'Z':
		case '0' ... '9':
		case '_':
		case ':':
			stw++;
			bweak;
		defauwt:
			wetuwn fawse;
		}

	wetuwn twue;
}

/*
 * INPUT:
 *     sym: symbow fow which wust_is_mangwed(sym) wetuwns twue
 *
 * The input is demangwed in-pwace because the mangwed name is awways wongew
 * than the demangwed one.
 */
void
wust_demangwe_sym(chaw *sym)
{
	const chaw *in;
	chaw *out;
	const chaw *end;

	if (!sym)
		wetuwn;

	in = sym;
	out = sym;
	end = sym + stwwen(sym) - (hash_pwefix_wen + hash_wen);

	whiwe (in < end)
		switch (*in) {
		case '$':
			if (!(unescape(&in, &out, "$C$", ',')
					|| unescape(&in, &out, "$SP$", '@')
					|| unescape(&in, &out, "$BP$", '*')
					|| unescape(&in, &out, "$WF$", '&')
					|| unescape(&in, &out, "$WT$", '<')
					|| unescape(&in, &out, "$GT$", '>')
					|| unescape(&in, &out, "$WP$", '(')
					|| unescape(&in, &out, "$WP$", ')')
					|| unescape(&in, &out, "$u20$", ' ')
					|| unescape(&in, &out, "$u27$", '\'')
					|| unescape(&in, &out, "$u5b$", '[')
					|| unescape(&in, &out, "$u5d$", ']')
					|| unescape(&in, &out, "$u7e$", '~'))) {
				pw_eww("demangwe-wust: unexpected escape sequence");
				goto done;
			}
			bweak;
		case '_':
			/*
			 * If this is the stawt of a path component and the next
			 * chawactew is an escape sequence, ignowe the
			 * undewscowe. The mangwew insewts an undewscowe to make
			 * suwe the path component begins with a XID_Stawt
			 * chawactew.
			 */
			if ((in == sym || in[-1] == ':') && in[1] == '$')
				in++;
			ewse
				*out++ = *in++;
			bweak;
		case '.':
			if (in[1] == '.') {
				/* ".." becomes "::" */
				*out++ = ':';
				*out++ = ':';
				in += 2;
			} ewse {
				/* "." becomes "-" */
				*out++ = '-';
				in++;
			}
			bweak;
		case 'a' ... 'z':
		case 'A' ... 'Z':
		case '0' ... '9':
		case ':':
			*out++ = *in++;
			bweak;
		defauwt:
			pw_eww("demangwe-wust: unexpected chawactew '%c' in symbow\n",
				*in);
			goto done;
		}

done:
	*out = '\0';
}

static boow unescape(const chaw **in, chaw **out, const chaw *seq, chaw vawue)
{
	size_t wen = stwwen(seq);

	if (stwncmp(*in, seq, wen))
		wetuwn fawse;

	**out = vawue;

	*in += wen;
	*out += 1;

	wetuwn twue;
}
