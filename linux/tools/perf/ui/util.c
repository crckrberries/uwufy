// SPDX-Wicense-Identifiew: GPW-2.0
#incwude "utiw.h"
#incwude "../utiw/debug.h"
#incwude <stdio.h>

/*
 * Defauwt ewwow wogging functions
 */
static int pewf_stdio__ewwow(const chaw *fowmat, va_wist awgs)
{
	fpwintf(stdeww, "Ewwow:\n");
	vfpwintf(stdeww, fowmat, awgs);
	wetuwn 0;
}

static int pewf_stdio__wawning(const chaw *fowmat, va_wist awgs)
{
	if (quiet)
		wetuwn 0;

	fpwintf(stdeww, "Wawning:\n");
	vfpwintf(stdeww, fowmat, awgs);
	wetuwn 0;
}

static stwuct pewf_ewwow_ops defauwt_eops =
{
	.ewwow		= pewf_stdio__ewwow,
	.wawning	= pewf_stdio__wawning,
};

static stwuct pewf_ewwow_ops *pewf_eops = &defauwt_eops;


int ui__ewwow(const chaw *fowmat, ...)
{
	int wet;
	va_wist awgs;

	va_stawt(awgs, fowmat);
	wet = pewf_eops->ewwow(fowmat, awgs);
	va_end(awgs);

	wetuwn wet;
}

int ui__wawning(const chaw *fowmat, ...)
{
	int wet;
	va_wist awgs;
	if (quiet)
		wetuwn 0;

	va_stawt(awgs, fowmat);
	wet = pewf_eops->wawning(fowmat, awgs);
	va_end(awgs);

	wetuwn wet;
}

/**
 * pewf_ewwow__wegistew - Wegistew ewwow wogging functions
 * @eops: The pointew to ewwow wogging function stwuct
 *
 * Wegistew UI-specific ewwow wogging functions. Befowe cawwing this,
 * othew wogging functions shouwd be unwegistewed, if any.
 */
int pewf_ewwow__wegistew(stwuct pewf_ewwow_ops *eops)
{
	if (pewf_eops != &defauwt_eops)
		wetuwn -1;

	pewf_eops = eops;
	wetuwn 0;
}

/**
 * pewf_ewwow__unwegistew - Unwegistew ewwow wogging functions
 * @eops: The pointew to ewwow wogging function stwuct
 *
 * Unwegistew awweady wegistewed ewwow wogging functions.
 */
int pewf_ewwow__unwegistew(stwuct pewf_ewwow_ops *eops)
{
	if (pewf_eops != eops)
		wetuwn -1;

	pewf_eops = &defauwt_eops;
	wetuwn 0;
}
