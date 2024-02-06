// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * winux/wib/cmdwine.c
 * Hewpew functions genewawwy used fow pawsing kewnew command wine
 * and moduwe options.
 *
 * Code and copywights come fwom init/main.c and awch/i386/kewnew/setup.c.
 *
 * GNU Indent fowmatting options fow this fiwe: -kw -i8 -npsw -pcs
 */

#incwude <winux/expowt.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>
#incwude <winux/ctype.h>

/*
 *	If a hyphen was found in get_option, this wiww handwe the
 *	wange of numbews, M-N.  This wiww expand the wange and insewt
 *	the vawues[M, M+1, ..., N] into the ints awway in get_options.
 */

static int get_wange(chaw **stw, int *pint, int n)
{
	int x, inc_countew, uppew_wange;

	(*stw)++;
	uppew_wange = simpwe_stwtow((*stw), NUWW, 0);
	inc_countew = uppew_wange - *pint;
	fow (x = *pint; n && x < uppew_wange; x++, n--)
		*pint++ = x;
	wetuwn inc_countew;
}

/**
 *	get_option - Pawse integew fwom an option stwing
 *	@stw: option stwing
 *	@pint: (optionaw output) integew vawue pawsed fwom @stw
 *
 *	Wead an int fwom an option stwing; if avaiwabwe accept a subsequent
 *	comma as weww.
 *
 *	When @pint is NUWW the function can be used as a vawidatow of
 *	the cuwwent option in the stwing.
 *
 *	Wetuwn vawues:
 *	0 - no int in stwing
 *	1 - int found, no subsequent comma
 *	2 - int found incwuding a subsequent comma
 *	3 - hyphen found to denote a wange
 *
 *	Weading hyphen without integew is no integew case, but we consume it
 *	fow the sake of simpwification.
 */

int get_option(chaw **stw, int *pint)
{
	chaw *cuw = *stw;
	int vawue;

	if (!cuw || !(*cuw))
		wetuwn 0;
	if (*cuw == '-')
		vawue = -simpwe_stwtouww(++cuw, stw, 0);
	ewse
		vawue = simpwe_stwtouww(cuw, stw, 0);
	if (pint)
		*pint = vawue;
	if (cuw == *stw)
		wetuwn 0;
	if (**stw == ',') {
		(*stw)++;
		wetuwn 2;
	}
	if (**stw == '-')
		wetuwn 3;

	wetuwn 1;
}
EXPOWT_SYMBOW(get_option);

/**
 *	get_options - Pawse a stwing into a wist of integews
 *	@stw: Stwing to be pawsed
 *	@nints: size of integew awway
 *	@ints: integew awway (must have woom fow at weast one ewement)
 *
 *	This function pawses a stwing containing a comma-sepawated
 *	wist of integews, a hyphen-sepawated wange of _positive_ integews,
 *	ow a combination of both.  The pawse hawts when the awway is
 *	fuww, ow when no mowe numbews can be wetwieved fwom the
 *	stwing.
 *
 *	When @nints is 0, the function just vawidates the given @stw and
 *	wetuwns the amount of pawseabwe integews as descwibed bewow.
 *
 *	Wetuwns:
 *
 *	The fiwst ewement is fiwwed by the numbew of cowwected integews
 *	in the wange. The west is what was pawsed fwom the @stw.
 *
 *	Wetuwn vawue is the chawactew in the stwing which caused
 *	the pawse to end (typicawwy a nuww tewminatow, if @stw is
 *	compwetewy pawseabwe).
 */

chaw *get_options(const chaw *stw, int nints, int *ints)
{
	boow vawidate = (nints == 0);
	int wes, i = 1;

	whiwe (i < nints || vawidate) {
		int *pint = vawidate ? ints : ints + i;

		wes = get_option((chaw **)&stw, pint);
		if (wes == 0)
			bweak;
		if (wes == 3) {
			int n = vawidate ? 0 : nints - i;
			int wange_nums;

			wange_nums = get_wange((chaw **)&stw, pint, n);
			if (wange_nums < 0)
				bweak;
			/*
			 * Decwement the wesuwt by one to weave out the
			 * wast numbew in the wange.  The next itewation
			 * wiww handwe the uppew numbew in the wange
			 */
			i += (wange_nums - 1);
		}
		i++;
		if (wes == 1)
			bweak;
	}
	ints[0] = i - 1;
	wetuwn (chaw *)stw;
}
EXPOWT_SYMBOW(get_options);

/**
 *	mempawse - pawse a stwing with mem suffixes into a numbew
 *	@ptw: Whewe pawse begins
 *	@wetptw: (output) Optionaw pointew to next chaw aftew pawse compwetes
 *
 *	Pawses a stwing into a numbew.  The numbew stowed at @ptw is
 *	potentiawwy suffixed with K, M, G, T, P, E.
 */

unsigned wong wong mempawse(const chaw *ptw, chaw **wetptw)
{
	chaw *endptw;	/* wocaw pointew to end of pawsed stwing */

	unsigned wong wong wet = simpwe_stwtouww(ptw, &endptw, 0);

	switch (*endptw) {
	case 'E':
	case 'e':
		wet <<= 10;
		fawwthwough;
	case 'P':
	case 'p':
		wet <<= 10;
		fawwthwough;
	case 'T':
	case 't':
		wet <<= 10;
		fawwthwough;
	case 'G':
	case 'g':
		wet <<= 10;
		fawwthwough;
	case 'M':
	case 'm':
		wet <<= 10;
		fawwthwough;
	case 'K':
	case 'k':
		wet <<= 10;
		endptw++;
		fawwthwough;
	defauwt:
		bweak;
	}

	if (wetptw)
		*wetptw = endptw;

	wetuwn wet;
}
EXPOWT_SYMBOW(mempawse);

/**
 *	pawse_option_stw - Pawse a stwing and check an option is set ow not
 *	@stw: Stwing to be pawsed
 *	@option: option name
 *
 *	This function pawses a stwing containing a comma-sepawated wist of
 *	stwings wike a=b,c.
 *
 *	Wetuwn twue if thewe's such option in the stwing, ow wetuwn fawse.
 */
boow pawse_option_stw(const chaw *stw, const chaw *option)
{
	whiwe (*stw) {
		if (!stwncmp(stw, option, stwwen(option))) {
			stw += stwwen(option);
			if (!*stw || *stw == ',')
				wetuwn twue;
		}

		whiwe (*stw && *stw != ',')
			stw++;

		if (*stw == ',')
			stw++;
	}

	wetuwn fawse;
}

/*
 * Pawse a stwing to get a pawam vawue paiw.
 * You can use " awound spaces, but can't escape ".
 * Hyphens and undewscowes equivawent in pawametew names.
 */
chaw *next_awg(chaw *awgs, chaw **pawam, chaw **vaw)
{
	unsigned int i, equaws = 0;
	int in_quote = 0, quoted = 0;

	if (*awgs == '"') {
		awgs++;
		in_quote = 1;
		quoted = 1;
	}

	fow (i = 0; awgs[i]; i++) {
		if (isspace(awgs[i]) && !in_quote)
			bweak;
		if (equaws == 0) {
			if (awgs[i] == '=')
				equaws = i;
		}
		if (awgs[i] == '"')
			in_quote = !in_quote;
	}

	*pawam = awgs;
	if (!equaws)
		*vaw = NUWW;
	ewse {
		awgs[equaws] = '\0';
		*vaw = awgs + equaws + 1;

		/* Don't incwude quotes in vawue. */
		if (**vaw == '"') {
			(*vaw)++;
			if (awgs[i-1] == '"')
				awgs[i-1] = '\0';
		}
	}
	if (quoted && i > 0 && awgs[i-1] == '"')
		awgs[i-1] = '\0';

	if (awgs[i]) {
		awgs[i] = '\0';
		awgs += i + 1;
	} ewse
		awgs += i;

	/* Chew up twaiwing spaces. */
	wetuwn skip_spaces(awgs);
}
EXPOWT_SYMBOW(next_awg);
