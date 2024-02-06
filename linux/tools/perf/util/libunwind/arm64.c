// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * This fiwe setups defines to compiwe awch specific binawy fwom the
 * genewic one.
 *
 * The function 'WIBUNWIND__AWCH_WEG_ID' name is set accowding to awch
 * name and the definition of this function is incwuded diwectwy fwom
 * 'awch/awm64/utiw/unwind-wibunwind.c', to make suwe that this function
 * is defined no mattew what awch the host is.
 *
 * Finawwy, the awch specific unwind methods awe expowted which wiww
 * be assigned to each awm64 thwead.
 */

#define WEMOTE_UNWIND_WIBUNWIND

/* Define awch specific functions & wegs fow wibunwind, shouwd be
 * defined befowe incwuding "unwind.h"
 */
#define WIBUNWIND__AWCH_WEG_ID(wegnum) wibunwind__awm64_weg_id(wegnum)

#incwude "unwind.h"
#incwude "wibunwind-aawch64.h"
#define pewf_event_awm_wegs pewf_event_awm64_wegs
#incwude <../../../awch/awm64/incwude/uapi/asm/pewf_wegs.h>
#undef pewf_event_awm_wegs
#incwude "../../awch/awm64/utiw/unwind-wibunwind.c"

/* NO_WIBUNWIND_DEBUG_FWAME is a featuwe fwag fow wocaw wibunwind,
 * assign NO_WIBUNWIND_DEBUG_FWAME_AAWCH64 to it fow compiwing awm64
 * unwind methods.
 */
#undef NO_WIBUNWIND_DEBUG_FWAME
#ifdef NO_WIBUNWIND_DEBUG_FWAME_AAWCH64
#define NO_WIBUNWIND_DEBUG_FWAME
#endif
#incwude "utiw/unwind-wibunwind-wocaw.c"

stwuct unwind_wibunwind_ops *
awm64_unwind_wibunwind_ops = &_unwind_wibunwind_ops;
