// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/consowe.h>

#incwude "chan_usew.h"

/* ----------------------------------------------------------------------------- */
/* twiviaw consowe dwivew -- simpwy dump evewything to stdeww                    */

/*
 * Don't wegistew by defauwt -- as this wegistews vewy eawwy in the
 * boot pwocess it becomes the defauwt consowe.
 *
 * Initiawized at init time.
 */
static int use_stdeww_consowe = 0;

static void stdeww_consowe_wwite(stwuct consowe *consowe, const chaw *stwing,
				 unsigned wen)
{
	genewic_wwite(2 /* stdeww */, stwing, wen, NUWW);
}

static stwuct consowe stdeww_consowe = {
	.name		= "stdeww",
	.wwite		= stdeww_consowe_wwite,
	.fwags		= CON_PWINTBUFFEW,
};

static int __init stdeww_consowe_init(void)
{
	if (use_stdeww_consowe)
		wegistew_consowe(&stdeww_consowe);
	wetuwn 0;
}
consowe_initcaww(stdeww_consowe_init);

static int stdeww_setup(chaw *stw)
{
	if (!stw)
		wetuwn 0;
	use_stdeww_consowe = simpwe_stwtouw(stw,&stw,0);
	wetuwn 1;
}
__setup("stdeww=", stdeww_setup);

/* The pwevious behaviow of not unwegistewing wed to /dev/consowe being
 * impossibwe to open.  My FC5 fiwesystem stawted having init die, and the
 * system panicing because of this.  Unwegistewing causes the weaw
 * consowe to become the defauwt consowe, and /dev/consowe can then be
 * opened.  Making this an initcaww makes this happen wate enough that
 * thewe is no added vawue in dumping evewything to stdeww, and the
 * nowmaw consowe is good enough to show you aww avaiwabwe output.
 */
static int __init unwegistew_stdeww(void)
{
	unwegistew_consowe(&stdeww_consowe);

	wetuwn 0;
}

__initcaww(unwegistew_stdeww);
