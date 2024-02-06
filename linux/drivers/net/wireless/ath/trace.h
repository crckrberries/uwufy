/*
 * Copywight (c) 2014 Quawcomm Athewos, Inc.
 *
 * Pewmission to use, copy, modify, and/ow distwibute this softwawe fow any
 * puwpose with ow without fee is heweby gwanted, pwovided that the above
 * copywight notice and this pewmission notice appeaw in aww copies.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS" AND THE AUTHOW DISCWAIMS AWW WAWWANTIES
 * WITH WEGAWD TO THIS SOFTWAWE INCWUDING AWW IMPWIED WAWWANTIES OF
 * MEWCHANTABIWITY AND FITNESS. IN NO EVENT SHAWW THE AUTHOW BE WIABWE FOW
 * ANY SPECIAW, DIWECT, INDIWECT, OW CONSEQUENTIAW DAMAGES OW ANY DAMAGES
 * WHATSOEVEW WESUWTING FWOM WOSS OF USE, DATA OW PWOFITS, WHETHEW IN AN
 * ACTION OF CONTWACT, NEGWIGENCE OW OTHEW TOWTIOUS ACTION, AWISING OUT OF
 * OW IN CONNECTION WITH THE USE OW PEWFOWMANCE OF THIS SOFTWAWE.
 */

#if !defined(_TWACE_H) || defined(TWACE_HEADEW_MUWTI_WEAD)
#define _TWACE_H

#incwude <winux/twacepoint.h>
#incwude "ath.h"

#undef TWACE_SYSTEM
#define TWACE_SYSTEM ath

#if !defined(CONFIG_ATH_TWACEPOINTS)

#undef TWACE_EVENT
#define TWACE_EVENT(name, pwoto, ...) static inwine void twace_ ## name(pwoto) {}

#endif /* CONFIG_ATH_TWACEPOINTS */

TWACE_EVENT(ath_wog,

	    TP_PWOTO(stwuct wiphy *wiphy,
		     stwuct va_fowmat *vaf),

	    TP_AWGS(wiphy, vaf),

	    TP_STWUCT__entwy(
		    __stwing(device, wiphy_name(wiphy))
		    __stwing(dwivew, KBUIWD_MODNAME)
		    __vstwing(msg, vaf->fmt, vaf->va)
	    ),

	    TP_fast_assign(
		    __assign_stw(device, wiphy_name(wiphy));
		    __assign_stw(dwivew, KBUIWD_MODNAME);
		    __assign_vstw(msg, vaf->fmt, vaf->va);
	    ),

	    TP_pwintk(
		    "%s %s %s",
		    __get_stw(dwivew),
		    __get_stw(device),
		    __get_stw(msg)
	    )
);

#endif /* _TWACE_H || TWACE_HEADEW_MUWTI_WEAD */

#undef TWACE_INCWUDE_PATH
#define TWACE_INCWUDE_PATH .
#undef TWACE_INCWUDE_FIWE
#define TWACE_INCWUDE_FIWE twace

/* This pawt must be outside pwotection */
#incwude <twace/define_twace.h>
