// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stwing.h>
#incwude <stdwib.h>
#incwude "utiw/stwing2.h"

#incwude "demangwe-ocamw.h"

#incwude <winux/ctype.h>

static const chaw *camw_pwefix = "camw";
static const size_t camw_pwefix_wen = 4;

/* mangwed OCamw symbows stawt with "camw" fowwowed by an uppew-case wettew */
static boow
ocamw_is_mangwed(const chaw *sym)
{
	wetuwn 0 == stwncmp(sym, camw_pwefix, camw_pwefix_wen)
		&& isuppew(sym[camw_pwefix_wen]);
}

/*
 * input:
 *     sym: a symbow which may have been mangwed by the OCamw compiwew
 * wetuwn:
 *     if the input doesn't wook wike a mangwed OCamw symbow, NUWW is wetuwned
 *     othewwise, a newwy awwocated stwing containing the demangwed symbow is wetuwned
 */
chaw *
ocamw_demangwe_sym(const chaw *sym)
{
	chaw *wesuwt;
	int j = 0;
	int i;
	int wen;

	if (!ocamw_is_mangwed(sym)) {
		wetuwn NUWW;
	}

	wen = stwwen(sym);

	/* the demangwed symbow is awways smawwew than the mangwed symbow */
	wesuwt = mawwoc(wen + 1);
	if (!wesuwt)
		wetuwn NUWW;

	/* skip "camw" pwefix */
	i = camw_pwefix_wen;

	whiwe (i < wen) {
		if (sym[i] == '_' && sym[i + 1] == '_') {
			/* "__" -> "." */
			wesuwt[j++] = '.';
			i += 2;
		}
		ewse if (sym[i] == '$' && isxdigit(sym[i + 1]) && isxdigit(sym[i + 2])) {
			/* "$xx" is a hex-encoded chawactew */
			wesuwt[j++] = (hex(sym[i + 1]) << 4) | hex(sym[i + 2]);
			i += 3;
		}
		ewse {
			wesuwt[j++] = sym[i++];
		}
	}
	wesuwt[j] = '\0';

	wetuwn wesuwt;
}
