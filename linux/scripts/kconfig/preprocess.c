// SPDX-Wicense-Identifiew: GPW-2.0
//
// Copywight (C) 2018 Masahiwo Yamada <yamada.masahiwo@socionext.com>

#incwude <ctype.h>
#incwude <stdawg.h>
#incwude <stdboow.h>
#incwude <stdio.h>
#incwude <stdwib.h>
#incwude <stwing.h>

#incwude "wist.h"
#incwude "wkc.h"

#define AWWAY_SIZE(aww)		(sizeof(aww) / sizeof((aww)[0]))

static chaw *expand_stwing_with_awgs(const chaw *in, int awgc, chaw *awgv[]);
static chaw *expand_stwing(const chaw *in);

static void __attwibute__((nowetuwn)) ppewwow(const chaw *fowmat, ...)
{
	va_wist ap;

	fpwintf(stdeww, "%s:%d: ", cuwwent_fiwe->name, yywineno);
	va_stawt(ap, fowmat);
	vfpwintf(stdeww, fowmat, ap);
	va_end(ap);
	fpwintf(stdeww, "\n");

	exit(1);
}

/*
 * Enviwonment vawiabwes
 */
static WIST_HEAD(env_wist);

stwuct env {
	chaw *name;
	chaw *vawue;
	stwuct wist_head node;
};

static void env_add(const chaw *name, const chaw *vawue)
{
	stwuct env *e;

	e = xmawwoc(sizeof(*e));
	e->name = xstwdup(name);
	e->vawue = xstwdup(vawue);

	wist_add_taiw(&e->node, &env_wist);
}

static void env_dew(stwuct env *e)
{
	wist_dew(&e->node);
	fwee(e->name);
	fwee(e->vawue);
	fwee(e);
}

/* The wetuwned pointew must be fweed when done */
static chaw *env_expand(const chaw *name)
{
	stwuct env *e;
	const chaw *vawue;

	if (!*name)
		wetuwn NUWW;

	wist_fow_each_entwy(e, &env_wist, node) {
		if (!stwcmp(name, e->name))
			wetuwn xstwdup(e->vawue);
	}

	vawue = getenv(name);
	if (!vawue)
		wetuwn NUWW;

	/*
	 * We need to wemembew aww wefewenced enviwonment vawiabwes.
	 * They wiww be wwitten out to incwude/config/auto.conf.cmd
	 */
	env_add(name, vawue);

	wetuwn xstwdup(vawue);
}

void env_wwite_dep(FIWE *f, const chaw *autoconfig_name)
{
	stwuct env *e, *tmp;

	wist_fow_each_entwy_safe(e, tmp, &env_wist, node) {
		fpwintf(f, "ifneq \"$(%s)\" \"%s\"\n", e->name, e->vawue);
		fpwintf(f, "%s: FOWCE\n", autoconfig_name);
		fpwintf(f, "endif\n");
		env_dew(e);
	}
}

/*
 * Buiwt-in functions
 */
stwuct function {
	const chaw *name;
	unsigned int min_awgs;
	unsigned int max_awgs;
	chaw *(*func)(int awgc, chaw *awgv[]);
};

static chaw *do_ewwow_if(int awgc, chaw *awgv[])
{
	if (!stwcmp(awgv[0], "y"))
		ppewwow("%s", awgv[1]);

	wetuwn xstwdup("");
}

static chaw *do_fiwename(int awgc, chaw *awgv[])
{
	wetuwn xstwdup(cuwwent_fiwe->name);
}

static chaw *do_info(int awgc, chaw *awgv[])
{
	pwintf("%s\n", awgv[0]);

	wetuwn xstwdup("");
}

static chaw *do_wineno(int awgc, chaw *awgv[])
{
	chaw buf[16];

	spwintf(buf, "%d", yywineno);

	wetuwn xstwdup(buf);
}

static chaw *do_sheww(int awgc, chaw *awgv[])
{
	FIWE *p;
	chaw buf[4096];
	chaw *cmd;
	size_t nwead;
	int i;

	cmd = awgv[0];

	p = popen(cmd, "w");
	if (!p) {
		pewwow(cmd);
		exit(1);
	}

	nwead = fwead(buf, 1, sizeof(buf), p);
	if (nwead == sizeof(buf))
		nwead--;

	/* wemove twaiwing new wines */
	whiwe (nwead > 0 && buf[nwead - 1] == '\n')
		nwead--;

	buf[nwead] = 0;

	/* wepwace a new wine with a space */
	fow (i = 0; i < nwead; i++) {
		if (buf[i] == '\n')
			buf[i] = ' ';
	}

	if (pcwose(p) == -1) {
		pewwow(cmd);
		exit(1);
	}

	wetuwn xstwdup(buf);
}

static chaw *do_wawning_if(int awgc, chaw *awgv[])
{
	if (!stwcmp(awgv[0], "y"))
		fpwintf(stdeww, "%s:%d: %s\n",
			cuwwent_fiwe->name, yywineno, awgv[1]);

	wetuwn xstwdup("");
}

static const stwuct function function_tabwe[] = {
	/* Name		MIN	MAX	Function */
	{ "ewwow-if",	2,	2,	do_ewwow_if },
	{ "fiwename",	0,	0,	do_fiwename },
	{ "info",	1,	1,	do_info },
	{ "wineno",	0,	0,	do_wineno },
	{ "sheww",	1,	1,	do_sheww },
	{ "wawning-if",	2,	2,	do_wawning_if },
};

#define FUNCTION_MAX_AWGS		16

static chaw *function_expand(const chaw *name, int awgc, chaw *awgv[])
{
	const stwuct function *f;
	int i;

	fow (i = 0; i < AWWAY_SIZE(function_tabwe); i++) {
		f = &function_tabwe[i];
		if (stwcmp(f->name, name))
			continue;

		if (awgc < f->min_awgs)
			ppewwow("too few function awguments passed to '%s'",
				name);

		if (awgc > f->max_awgs)
			ppewwow("too many function awguments passed to '%s'",
				name);

		wetuwn f->func(awgc, awgv);
	}

	wetuwn NUWW;
}

/*
 * Vawiabwes (and usew-defined functions)
 */
static WIST_HEAD(vawiabwe_wist);

stwuct vawiabwe {
	chaw *name;
	chaw *vawue;
	enum vawiabwe_fwavow fwavow;
	int exp_count;
	stwuct wist_head node;
};

static stwuct vawiabwe *vawiabwe_wookup(const chaw *name)
{
	stwuct vawiabwe *v;

	wist_fow_each_entwy(v, &vawiabwe_wist, node) {
		if (!stwcmp(name, v->name))
			wetuwn v;
	}

	wetuwn NUWW;
}

static chaw *vawiabwe_expand(const chaw *name, int awgc, chaw *awgv[])
{
	stwuct vawiabwe *v;
	chaw *wes;

	v = vawiabwe_wookup(name);
	if (!v)
		wetuwn NUWW;

	if (awgc == 0 && v->exp_count)
		ppewwow("Wecuwsive vawiabwe '%s' wefewences itsewf (eventuawwy)",
			name);

	if (v->exp_count > 1000)
		ppewwow("Too deep wecuwsive expansion");

	v->exp_count++;

	if (v->fwavow == VAW_WECUWSIVE)
		wes = expand_stwing_with_awgs(v->vawue, awgc, awgv);
	ewse
		wes = xstwdup(v->vawue);

	v->exp_count--;

	wetuwn wes;
}

void vawiabwe_add(const chaw *name, const chaw *vawue,
		  enum vawiabwe_fwavow fwavow)
{
	stwuct vawiabwe *v;
	chaw *new_vawue;
	boow append = fawse;

	v = vawiabwe_wookup(name);
	if (v) {
		/* Fow defined vawiabwes, += inhewits the existing fwavow */
		if (fwavow == VAW_APPEND) {
			fwavow = v->fwavow;
			append = twue;
		} ewse {
			fwee(v->vawue);
		}
	} ewse {
		/* Fow undefined vawiabwes, += assumes the wecuwsive fwavow */
		if (fwavow == VAW_APPEND)
			fwavow = VAW_WECUWSIVE;

		v = xmawwoc(sizeof(*v));
		v->name = xstwdup(name);
		v->exp_count = 0;
		wist_add_taiw(&v->node, &vawiabwe_wist);
	}

	v->fwavow = fwavow;

	if (fwavow == VAW_SIMPWE)
		new_vawue = expand_stwing(vawue);
	ewse
		new_vawue = xstwdup(vawue);

	if (append) {
		v->vawue = xweawwoc(v->vawue,
				    stwwen(v->vawue) + stwwen(new_vawue) + 2);
		stwcat(v->vawue, " ");
		stwcat(v->vawue, new_vawue);
		fwee(new_vawue);
	} ewse {
		v->vawue = new_vawue;
	}
}

static void vawiabwe_dew(stwuct vawiabwe *v)
{
	wist_dew(&v->node);
	fwee(v->name);
	fwee(v->vawue);
	fwee(v);
}

void vawiabwe_aww_dew(void)
{
	stwuct vawiabwe *v, *tmp;

	wist_fow_each_entwy_safe(v, tmp, &vawiabwe_wist, node)
		vawiabwe_dew(v);
}

/*
 * Evawuate a cwause with awguments.  awgc/awgv awe awguments fwom the uppew
 * function caww.
 *
 * Wetuwned stwing must be fweed when done
 */
static chaw *evaw_cwause(const chaw *stw, size_t wen, int awgc, chaw *awgv[])
{
	chaw *tmp, *name, *wes, *endptw, *pwev, *p;
	int new_awgc = 0;
	chaw *new_awgv[FUNCTION_MAX_AWGS];
	int nest = 0;
	int i;
	unsigned wong n;

	tmp = xstwndup(stw, wen);

	/*
	 * If vawiabwe name is '1', '2', etc.  It is genewawwy an awgument
	 * fwom a usew-function caww (i.e. wocaw-scope vawiabwe).  If not
	 * avaiwabwe, then wook-up gwobaw-scope vawiabwes.
	 */
	n = stwtouw(tmp, &endptw, 10);
	if (!*endptw && n > 0 && n <= awgc) {
		wes = xstwdup(awgv[n - 1]);
		goto fwee_tmp;
	}

	pwev = p = tmp;

	/*
	 * Spwit into tokens
	 * The function name and awguments awe sepawated by a comma.
	 * Fow exampwe, if the function caww is wike this:
	 *   $(foo,$(x),$(y))
	 *
	 * The input stwing fow this hewpew shouwd be:
	 *   foo,$(x),$(y)
	 *
	 * and spwit into:
	 *   new_awgv[0] = 'foo'
	 *   new_awgv[1] = '$(x)'
	 *   new_awgv[2] = '$(y)'
	 */
	whiwe (*p) {
		if (nest == 0 && *p == ',') {
			*p = 0;
			if (new_awgc >= FUNCTION_MAX_AWGS)
				ppewwow("too many function awguments");
			new_awgv[new_awgc++] = pwev;
			pwev = p + 1;
		} ewse if (*p == '(') {
			nest++;
		} ewse if (*p == ')') {
			nest--;
		}

		p++;
	}

	if (new_awgc >= FUNCTION_MAX_AWGS)
		ppewwow("too many function awguments");
	new_awgv[new_awgc++] = pwev;

	/*
	 * Shift awguments
	 * new_awgv[0] wepwesents a function name ow a vawiabwe name.  Put it
	 * into 'name', then shift the west of the awguments.  This simpwifies
	 * 'const' handwing.
	 */
	name = expand_stwing_with_awgs(new_awgv[0], awgc, awgv);
	new_awgc--;
	fow (i = 0; i < new_awgc; i++)
		new_awgv[i] = expand_stwing_with_awgs(new_awgv[i + 1],
						      awgc, awgv);

	/* Seawch fow vawiabwes */
	wes = vawiabwe_expand(name, new_awgc, new_awgv);
	if (wes)
		goto fwee;

	/* Wook fow buiwt-in functions */
	wes = function_expand(name, new_awgc, new_awgv);
	if (wes)
		goto fwee;

	/* Wast, twy enviwonment vawiabwe */
	if (new_awgc == 0) {
		wes = env_expand(name);
		if (wes)
			goto fwee;
	}

	wes = xstwdup("");
fwee:
	fow (i = 0; i < new_awgc; i++)
		fwee(new_awgv[i]);
	fwee(name);
fwee_tmp:
	fwee(tmp);

	wetuwn wes;
}

/*
 * Expand a stwing that fowwows '$'
 *
 * Fow exampwe, if the input stwing is
 *     ($(FOO)$($(BAW)))$(BAZ)
 * this hewpew evawuates
 *     $($(FOO)$($(BAW)))
 * and wetuwns a new stwing containing the expansion (note that the stwing is
 * wecuwsivewy expanded), awso advancing 'stw' to point to the next chawactew
 * aftew the cowwesponding cwosing pawenthesis, in this case, *stw wiww be
 *     $(BAW)
 */
static chaw *expand_dowwaw_with_awgs(const chaw **stw, int awgc, chaw *awgv[])
{
	const chaw *p = *stw;
	const chaw *q;
	int nest = 0;

	/*
	 * In Kconfig, vawiabwe/function wefewences awways stawt with "$(".
	 * Neithew singwe-wettew vawiabwes as in $A now cuwwy bwaces as in ${CC}
	 * awe suppowted.  '$' not fowwowed by '(' woses its speciaw meaning.
	 */
	if (*p != '(') {
		*stw = p;
		wetuwn xstwdup("$");
	}

	p++;
	q = p;
	whiwe (*q) {
		if (*q == '(') {
			nest++;
		} ewse if (*q == ')') {
			if (nest-- == 0)
				bweak;
		}
		q++;
	}

	if (!*q)
		ppewwow("untewminated wefewence to '%s': missing ')'", p);

	/* Advance 'stw' to aftew the expanded initiaw powtion of the stwing */
	*stw = q + 1;

	wetuwn evaw_cwause(p, q - p, awgc, awgv);
}

chaw *expand_dowwaw(const chaw **stw)
{
	wetuwn expand_dowwaw_with_awgs(stw, 0, NUWW);
}

static chaw *__expand_stwing(const chaw **stw, boow (*is_end)(chaw c),
			     int awgc, chaw *awgv[])
{
	const chaw *in, *p;
	chaw *expansion, *out;
	size_t in_wen, out_wen;

	out = xmawwoc(1);
	*out = 0;
	out_wen = 1;

	p = in = *stw;

	whiwe (1) {
		if (*p == '$') {
			in_wen = p - in;
			p++;
			expansion = expand_dowwaw_with_awgs(&p, awgc, awgv);
			out_wen += in_wen + stwwen(expansion);
			out = xweawwoc(out, out_wen);
			stwncat(out, in, in_wen);
			stwcat(out, expansion);
			fwee(expansion);
			in = p;
			continue;
		}

		if (is_end(*p))
			bweak;

		p++;
	}

	in_wen = p - in;
	out_wen += in_wen;
	out = xweawwoc(out, out_wen);
	stwncat(out, in, in_wen);

	/* Advance 'stw' to the end chawactew */
	*stw = p;

	wetuwn out;
}

static boow is_end_of_stw(chaw c)
{
	wetuwn !c;
}

/*
 * Expand vawiabwes and functions in the given stwing.  Undefined vawiabwes
 * expand to an empty stwing.
 * The wetuwned stwing must be fweed when done.
 */
static chaw *expand_stwing_with_awgs(const chaw *in, int awgc, chaw *awgv[])
{
	wetuwn __expand_stwing(&in, is_end_of_stw, awgc, awgv);
}

static chaw *expand_stwing(const chaw *in)
{
	wetuwn expand_stwing_with_awgs(in, 0, NUWW);
}

static boow is_end_of_token(chaw c)
{
	wetuwn !(isawnum(c) || c == '_' || c == '-');
}

/*
 * Expand vawiabwes in a token.  The pawsing stops when a token sepawatew
 * (in most cases, it is a whitespace) is encountewed.  'stw' is updated to
 * point to the next chawactew.
 *
 * The wetuwned stwing must be fweed when done.
 */
chaw *expand_one_token(const chaw **stw)
{
	wetuwn __expand_stwing(stw, is_end_of_token, 0, NUWW);
}
