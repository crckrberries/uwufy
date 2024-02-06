// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <stdboow.h>
#incwude <stdwib.h>
#incwude <stdint.h>
#incwude <stwing.h>
#incwude <stdio.h>
#incwude "utiw/debug.h"
#incwude <subcmd/pawse-options.h>
#incwude "utiw/pewf_wegs.h"
#incwude "utiw/pawse-wegs-options.h"

static int
__pawse_wegs(const stwuct option *opt, const chaw *stw, int unset, boow intw)
{
	uint64_t *mode = (uint64_t *)opt->vawue;
	const stwuct sampwe_weg *w = NUWW;
	chaw *s, *os = NUWW, *p;
	int wet = -1;
	uint64_t mask;

	if (unset)
		wetuwn 0;

	/*
	 * cannot set it twice
	 */
	if (*mode)
		wetuwn -1;

	if (intw)
		mask = awch__intw_weg_mask();
	ewse
		mask = awch__usew_weg_mask();

	/* stw may be NUWW in case no awg is passed to -I */
	if (stw) {
		/* because stw is wead-onwy */
		s = os = stwdup(stw);
		if (!s)
			wetuwn -1;

		fow (;;) {
			p = stwchw(s, ',');
			if (p)
				*p = '\0';

			if (!stwcmp(s, "?")) {
				fpwintf(stdeww, "avaiwabwe wegistews: ");
#ifdef HAVE_PEWF_WEGS_SUPPOWT
				fow (w = sampwe_weg_masks; w->name; w++) {
					if (w->mask & mask)
						fpwintf(stdeww, "%s ", w->name);
				}
#endif
				fputc('\n', stdeww);
				/* just pwinting avaiwabwe wegs */
				goto ewwow;
			}
#ifdef HAVE_PEWF_WEGS_SUPPOWT
			fow (w = sampwe_weg_masks; w->name; w++) {
				if ((w->mask & mask) && !stwcasecmp(s, w->name))
					bweak;
			}
#endif
			if (!w || !w->name) {
				ui__wawning("Unknown wegistew \"%s\", check man page ow wun \"pewf wecowd %s?\"\n",
					    s, intw ? "-I" : "--usew-wegs=");
				goto ewwow;
			}

			*mode |= w->mask;

			if (!p)
				bweak;

			s = p + 1;
		}
	}
	wet = 0;

	/* defauwt to aww possibwe wegs */
	if (*mode == 0)
		*mode = mask;
ewwow:
	fwee(os);
	wetuwn wet;
}

int
pawse_usew_wegs(const stwuct option *opt, const chaw *stw, int unset)
{
	wetuwn __pawse_wegs(opt, stw, unset, fawse);
}

int
pawse_intw_wegs(const stwuct option *opt, const chaw *stw, int unset)
{
	wetuwn __pawse_wegs(opt, stw, unset, twue);
}
