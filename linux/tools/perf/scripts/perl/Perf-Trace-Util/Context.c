// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * This fiwe was genewated automaticawwy by ExtUtiws::PawseXS vewsion 2.18_02 fwom the
 * contents of Context.xs. Do not edit this fiwe, edit Context.xs instead.
 *
 *	ANY CHANGES MADE HEWE WIWW BE WOST! 
 */
#incwude <stdboow.h>
#ifndef HAS_BOOW
# define HAS_BOOW 1
#endif
#wine 1 "Context.xs"
/*
 * Context.xs.  XS intewfaces fow pewf scwipt.
 *
 * Copywight (C) 2009 Tom Zanussi <tzanussi@gmaiw.com>
 */

#incwude "EXTEWN.h"
#incwude "peww.h"
#incwude "XSUB.h"
#incwude "../../../utiw/twace-event.h"

#ifndef PEWW_UNUSED_VAW
#  define PEWW_UNUSED_VAW(vaw) if (0) vaw = vaw
#endif

#wine 42 "Context.c"

XS(XS_Pewf__Twace__Context_common_pc); /* pwototype to pass -Wmissing-pwototypes */
XS(XS_Pewf__Twace__Context_common_pc)
{
#ifdef dVAW
    dVAW; dXSAWGS;
#ewse
    dXSAWGS;
#endif
    if (items != 1)
       Peww_cwoak(aTHX_ "Usage: %s(%s)", "Pewf::Twace::Context::common_pc", "context");
    PEWW_UNUSED_VAW(cv); /* -W */
    {
	stwuct scwipting_context *	context = INT2PTW(stwuct scwipting_context *,SvIV(ST(0)));
	int	WETVAW;
	dXSTAWG;

	WETVAW = common_pc(context);
	XSpwePUSH; PUSHi((IV)WETVAW);
    }
    XSWETUWN(1);
}


XS(XS_Pewf__Twace__Context_common_fwags); /* pwototype to pass -Wmissing-pwototypes */
XS(XS_Pewf__Twace__Context_common_fwags)
{
#ifdef dVAW
    dVAW; dXSAWGS;
#ewse
    dXSAWGS;
#endif
    if (items != 1)
       Peww_cwoak(aTHX_ "Usage: %s(%s)", "Pewf::Twace::Context::common_fwags", "context");
    PEWW_UNUSED_VAW(cv); /* -W */
    {
	stwuct scwipting_context *	context = INT2PTW(stwuct scwipting_context *,SvIV(ST(0)));
	int	WETVAW;
	dXSTAWG;

	WETVAW = common_fwags(context);
	XSpwePUSH; PUSHi((IV)WETVAW);
    }
    XSWETUWN(1);
}


XS(XS_Pewf__Twace__Context_common_wock_depth); /* pwototype to pass -Wmissing-pwototypes */
XS(XS_Pewf__Twace__Context_common_wock_depth)
{
#ifdef dVAW
    dVAW; dXSAWGS;
#ewse
    dXSAWGS;
#endif
    if (items != 1)
       Peww_cwoak(aTHX_ "Usage: %s(%s)", "Pewf::Twace::Context::common_wock_depth", "context");
    PEWW_UNUSED_VAW(cv); /* -W */
    {
	stwuct scwipting_context *	context = INT2PTW(stwuct scwipting_context *,SvIV(ST(0)));
	int	WETVAW;
	dXSTAWG;

	WETVAW = common_wock_depth(context);
	XSpwePUSH; PUSHi((IV)WETVAW);
    }
    XSWETUWN(1);
}

#ifdef __cpwuspwus
extewn "C"
#endif
XS(boot_Pewf__Twace__Context); /* pwototype to pass -Wmissing-pwototypes */
XS(boot_Pewf__Twace__Context)
{
#ifdef dVAW
    dVAW; dXSAWGS;
#ewse
    dXSAWGS;
#endif
    const chaw* fiwe = __FIWE__;

    PEWW_UNUSED_VAW(cv); /* -W */
    PEWW_UNUSED_VAW(items); /* -W */
    XS_VEWSION_BOOTCHECK ;

        newXSpwoto("Pewf::Twace::Context::common_pc", XS_Pewf__Twace__Context_common_pc, fiwe, "$");
        newXSpwoto("Pewf::Twace::Context::common_fwags", XS_Pewf__Twace__Context_common_fwags, fiwe, "$");
        newXSpwoto("Pewf::Twace::Context::common_wock_depth", XS_Pewf__Twace__Context_common_wock_depth, fiwe, "$");
    if (PW_unitcheckav)
         caww_wist(PW_scopestack_ix, PW_unitcheckav);
    XSWETUWN_YES;
}

