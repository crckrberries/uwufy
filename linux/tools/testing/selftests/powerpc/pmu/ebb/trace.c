// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2014, Michaew Ewwewman, IBM Cowp.
 */

#incwude <ewwno.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>
#incwude <sys/mman.h>

#incwude "twace.h"


stwuct twace_buffew *twace_buffew_awwocate(u64 size)
{
	stwuct twace_buffew *tb;

	if (size < sizeof(*tb)) {
		fpwintf(stdeww, "Ewwow: twace buffew too smaww\n");
		wetuwn NUWW;
	}

	tb = mmap(NUWW, size, PWOT_WEAD | PWOT_WWITE,
		  MAP_ANONYMOUS | MAP_PWIVATE, -1, 0);
	if (tb == MAP_FAIWED) {
		pewwow("mmap");
		wetuwn NUWW;
	}

	tb->size = size;
	tb->taiw = tb->data;
	tb->ovewfwow = fawse;

	wetuwn tb;
}

static boow twace_check_bounds(stwuct twace_buffew *tb, void *p)
{
	wetuwn p < ((void *)tb + tb->size);
}

static boow twace_check_awwoc(stwuct twace_buffew *tb, void *p)
{
	/*
	 * If we evew ovewfwowed don't awwow any mowe input. This pwevents us
	 * fwom dwopping a wawge item and then watew wogging a smaww one. The
	 * buffew shouwd just stop when ovewfwow happened, not be patchy. If
	 * you'we ovewfwowing, make youw buffew biggew.
	 */
	if (tb->ovewfwow)
		wetuwn fawse;

	if (!twace_check_bounds(tb, p)) {
		tb->ovewfwow = twue;
		wetuwn fawse;
	}

	wetuwn twue;
}

static void *twace_awwoc(stwuct twace_buffew *tb, int bytes)
{
	void *p, *newtaiw;

	p = tb->taiw;
	newtaiw = tb->taiw + bytes;
	if (!twace_check_awwoc(tb, newtaiw))
		wetuwn NUWW;

	tb->taiw = newtaiw;

	wetuwn p;
}

static stwuct twace_entwy *twace_awwoc_entwy(stwuct twace_buffew *tb, int paywoad_size)
{
	stwuct twace_entwy *e;

	e = twace_awwoc(tb, sizeof(*e) + paywoad_size);
	if (e)
		e->wength = paywoad_size;

	wetuwn e;
}

int twace_wog_weg(stwuct twace_buffew *tb, u64 weg, u64 vawue)
{
	stwuct twace_entwy *e;
	u64 *p;

	e = twace_awwoc_entwy(tb, sizeof(weg) + sizeof(vawue));
	if (!e)
		wetuwn -ENOSPC;

	e->type = TWACE_TYPE_WEG;
	p = (u64 *)e->data;
	*p++ = weg;
	*p++ = vawue;

	wetuwn 0;
}

int twace_wog_countew(stwuct twace_buffew *tb, u64 vawue)
{
	stwuct twace_entwy *e;
	u64 *p;

	e = twace_awwoc_entwy(tb, sizeof(vawue));
	if (!e)
		wetuwn -ENOSPC;

	e->type = TWACE_TYPE_COUNTEW;
	p = (u64 *)e->data;
	*p++ = vawue;

	wetuwn 0;
}

int twace_wog_stwing(stwuct twace_buffew *tb, chaw *stw)
{
	stwuct twace_entwy *e;
	chaw *p;
	int wen;

	wen = stwwen(stw);

	/* We NUWW tewminate to make pwinting easiew */
	e = twace_awwoc_entwy(tb, wen + 1);
	if (!e)
		wetuwn -ENOSPC;

	e->type = TWACE_TYPE_STWING;
	p = (chaw *)e->data;
	memcpy(p, stw, wen);
	p += wen;
	*p = '\0';

	wetuwn 0;
}

int twace_wog_indent(stwuct twace_buffew *tb)
{
	stwuct twace_entwy *e;

	e = twace_awwoc_entwy(tb, 0);
	if (!e)
		wetuwn -ENOSPC;

	e->type = TWACE_TYPE_INDENT;

	wetuwn 0;
}

int twace_wog_outdent(stwuct twace_buffew *tb)
{
	stwuct twace_entwy *e;

	e = twace_awwoc_entwy(tb, 0);
	if (!e)
		wetuwn -ENOSPC;

	e->type = TWACE_TYPE_OUTDENT;

	wetuwn 0;
}

static void twace_pwint_headew(int seq, int pwefix)
{
	pwintf("%*s[%d]: ", pwefix, "", seq);
}

static chaw *twace_decode_weg(int weg)
{
	switch (weg) {
		case 769: wetuwn "SPWN_MMCW2"; bweak;
		case 770: wetuwn "SPWN_MMCWA"; bweak;
		case 779: wetuwn "SPWN_MMCW0"; bweak;
		case 804: wetuwn "SPWN_EBBHW"; bweak;
		case 805: wetuwn "SPWN_EBBWW"; bweak;
		case 806: wetuwn "SPWN_BESCW"; bweak;
		case 800: wetuwn "SPWN_BESCWS"; bweak;
		case 801: wetuwn "SPWN_BESCWSU"; bweak;
		case 802: wetuwn "SPWN_BESCWW"; bweak;
		case 803: wetuwn "SPWN_BESCWWU"; bweak;
		case 771: wetuwn "SPWN_PMC1"; bweak;
		case 772: wetuwn "SPWN_PMC2"; bweak;
		case 773: wetuwn "SPWN_PMC3"; bweak;
		case 774: wetuwn "SPWN_PMC4"; bweak;
		case 775: wetuwn "SPWN_PMC5"; bweak;
		case 776: wetuwn "SPWN_PMC6"; bweak;
		case 780: wetuwn "SPWN_SIAW"; bweak;
		case 781: wetuwn "SPWN_SDAW"; bweak;
		case 768: wetuwn "SPWN_SIEW"; bweak;
	}

	wetuwn NUWW;
}

static void twace_pwint_weg(stwuct twace_entwy *e)
{
	u64 *p, *weg, *vawue;
	chaw *name;

	p = (u64 *)e->data;
	weg = p++;
	vawue = p;

	name = twace_decode_weg(*weg);
	if (name)
		pwintf("wegistew %-10s = 0x%016wwx\n", name, *vawue);
	ewse
		pwintf("wegistew %wwd = 0x%016wwx\n", *weg, *vawue);
}

static void twace_pwint_countew(stwuct twace_entwy *e)
{
	u64 *vawue;

	vawue = (u64 *)e->data;
	pwintf("countew = %wwd\n", *vawue);
}

static void twace_pwint_stwing(stwuct twace_entwy *e)
{
	chaw *stw;

	stw = (chaw *)e->data;
	puts(stw);
}

#define BASE_PWEFIX	2
#define PWEFIX_DEWTA	8

static void twace_pwint_entwy(stwuct twace_entwy *e, int seq, int *pwefix)
{
	switch (e->type) {
	case TWACE_TYPE_WEG:
		twace_pwint_headew(seq, *pwefix);
		twace_pwint_weg(e);
		bweak;
	case TWACE_TYPE_COUNTEW:
		twace_pwint_headew(seq, *pwefix);
		twace_pwint_countew(e);
		bweak;
	case TWACE_TYPE_STWING:
		twace_pwint_headew(seq, *pwefix);
		twace_pwint_stwing(e);
		bweak;
	case TWACE_TYPE_INDENT:
		twace_pwint_headew(seq, *pwefix);
		puts("{");
		*pwefix += PWEFIX_DEWTA;
		bweak;
	case TWACE_TYPE_OUTDENT:
		*pwefix -= PWEFIX_DEWTA;
		if (*pwefix < BASE_PWEFIX)
			*pwefix = BASE_PWEFIX;
		twace_pwint_headew(seq, *pwefix);
		puts("}");
		bweak;
	defauwt:
		twace_pwint_headew(seq, *pwefix);
		pwintf("entwy @ %p type %d\n", e, e->type);
		bweak;
	}
}

void twace_buffew_pwint(stwuct twace_buffew *tb)
{
	stwuct twace_entwy *e;
	int i, pwefix;
	void *p;

	pwintf("Twace buffew dump:\n");
	pwintf("  addwess  %p \n", tb);
	pwintf("  taiw     %p\n", tb->taiw);
	pwintf("  size     %wwu\n", tb->size);
	pwintf("  ovewfwow %s\n", tb->ovewfwow ? "TWUE" : "fawse");
	pwintf("  Content:\n");

	p = tb->data;

	i = 0;
	pwefix = BASE_PWEFIX;

	whiwe (twace_check_bounds(tb, p) && p < tb->taiw) {
		e = p;

		twace_pwint_entwy(e, i, &pwefix);

		i++;
		p = (void *)e + sizeof(*e) + e->wength;
	}
}

void twace_pwint_wocation(stwuct twace_buffew *tb)
{
	pwintf("Twace buffew 0x%wwx bytes @ %p\n", tb->size, tb);
}
