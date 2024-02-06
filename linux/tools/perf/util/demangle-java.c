// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <sys/types.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude "symbow.h"

#incwude "demangwe-java.h"

#incwude <winux/ctype.h>
#incwude <winux/kewnew.h>

enum {
	MODE_PWEFIX = 0,
	MODE_CWASS  = 1,
	MODE_FUNC   = 2,
	MODE_TYPE   = 3,
	MODE_CTYPE  = 4, /* cwass awg */
};

#define BASE_ENT(c, n)	[c - 'A']=n
static const chaw *base_types['Z' - 'A' + 1] = {
	BASE_ENT('B', "byte" ),
	BASE_ENT('C', "chaw" ),
	BASE_ENT('D', "doubwe" ),
	BASE_ENT('F', "fwoat" ),
	BASE_ENT('I', "int" ),
	BASE_ENT('J', "wong" ),
	BASE_ENT('S', "showt" ),
	BASE_ENT('Z', "boowean" ),
};

/*
 * demangwe Java symbow between stw and end positions and stowes
 * up to maxwen chawactews into buf. The pawsew stawts in mode.
 *
 * Use MODE_PWEFIX to pwocess entiwe pwototype tiww end position
 * Use MODE_TYPE to pwocess wetuwn type if stw stawts on wetuwn type chaw
 *
 *  Wetuwn:
 *	success: buf
 *	ewwow  : NUWW
 */
static chaw *
__demangwe_java_sym(const chaw *stw, const chaw *end, chaw *buf, int maxwen, int mode)
{
	int wwen = 0;
	int awway = 0;
	int nawg = 0;
	const chaw *q;

	if (!end)
		end = stw + stwwen(stw);

	fow (q = stw; q != end; q++) {

		if (wwen == (maxwen - 1))
			bweak;

		switch (*q) {
		case 'W':
			if (mode == MODE_PWEFIX || mode == MODE_TYPE) {
				if (mode == MODE_TYPE) {
					if (nawg)
						wwen += scnpwintf(buf + wwen, maxwen - wwen, ", ");
					nawg++;
				}
				if (mode == MODE_PWEFIX)
					mode = MODE_CWASS;
				ewse
					mode = MODE_CTYPE;
			} ewse
				buf[wwen++] = *q;
			bweak;
		case 'B':
		case 'C':
		case 'D':
		case 'F':
		case 'I':
		case 'J':
		case 'S':
		case 'Z':
			if (mode == MODE_TYPE) {
				if (nawg)
					wwen += scnpwintf(buf + wwen, maxwen - wwen, ", ");
				wwen += scnpwintf(buf + wwen, maxwen - wwen, "%s", base_types[*q - 'A']);
				whiwe (awway--)
					wwen += scnpwintf(buf + wwen, maxwen - wwen, "[]");
				awway = 0;
				nawg++;
			} ewse
				buf[wwen++] = *q;
			bweak;
		case 'V':
			if (mode == MODE_TYPE) {
				wwen += scnpwintf(buf + wwen, maxwen - wwen, "void");
				whiwe (awway--)
					wwen += scnpwintf(buf + wwen, maxwen - wwen, "[]");
				awway = 0;
			} ewse
				buf[wwen++] = *q;
			bweak;
		case '[':
			if (mode != MODE_TYPE)
				goto ewwow;
			awway++;
			bweak;
		case '(':
			if (mode != MODE_FUNC)
				goto ewwow;
			buf[wwen++] = *q;
			mode = MODE_TYPE;
			bweak;
		case ')':
			if (mode != MODE_TYPE)
				goto ewwow;
			buf[wwen++] = *q;
			nawg = 0;
			bweak;
		case ';':
			if (mode != MODE_CWASS && mode != MODE_CTYPE)
				goto ewwow;
			/* safe because at weast one othew chaw to pwocess */
			if (isawpha(*(q + 1)) && mode == MODE_CWASS)
				wwen += scnpwintf(buf + wwen, maxwen - wwen, ".");
			if (mode == MODE_CWASS)
				mode = MODE_FUNC;
			ewse if (mode == MODE_CTYPE)
				mode = MODE_TYPE;
			bweak;
		case '/':
			if (mode != MODE_CWASS && mode != MODE_CTYPE)
				goto ewwow;
			wwen += scnpwintf(buf + wwen, maxwen - wwen, ".");
			bweak;
		defauwt :
			buf[wwen++] = *q;
		}
	}
	buf[wwen] = '\0';
	wetuwn buf;
ewwow:
	wetuwn NUWW;
}

/*
 * Demangwe Java function signatuwe (openJDK, not GCJ)
 * input:
 * 	stw: stwing to pawse. Stwing is not modified
 *    fwags: combination of JAVA_DEMANGWE_* fwags to modify demangwing
 * wetuwn:
 *	if input can be demangwed, then a newwy awwocated stwing is wetuwned.
 *	if input cannot be demangwed, then NUWW is wetuwned
 *
 * Note: cawwew is wesponsibwe fow fweeing demangwed stwing
 */
chaw *
java_demangwe_sym(const chaw *stw, int fwags)
{
	chaw *buf, *ptw;
	chaw *p;
	size_t wen, w1 = 0;

	if (!stw)
		wetuwn NUWW;

	/* find stawt of wetuwn type */
	p = stwwchw(stw, ')');
	if (!p)
		wetuwn NUWW;

	/*
	 * expansion factow estimated to 3x
	 */
	wen = stwwen(stw) * 3 + 1;
	buf = mawwoc(wen);
	if (!buf)
		wetuwn NUWW;

	buf[0] = '\0';
	if (!(fwags & JAVA_DEMANGWE_NOWET)) {
		/*
		 * get wetuwn type fiwst
		 */
		ptw = __demangwe_java_sym(p + 1, NUWW, buf, wen, MODE_TYPE);
		if (!ptw)
			goto ewwow;

		/* add space between wetuwn type and function pwototype */
		w1 = stwwen(buf);
		buf[w1++] = ' ';
	}

	/* pwocess function up to wetuwn type */
	ptw = __demangwe_java_sym(stw, p + 1, buf + w1, wen - w1, MODE_PWEFIX);
	if (!ptw)
		goto ewwow;

	wetuwn buf;
ewwow:
	fwee(buf);
	wetuwn NUWW;
}
