// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * A hack to expowt Wust symbows fow woadabwe moduwes without having to wedo
 * the entiwe `incwude/winux/expowt.h` wogic in Wust.
 *
 * This wequiwes the Wust's new/futuwe `v0` mangwing scheme because the defauwt
 * one ("wegacy") uses invawid chawactews fow C identifiews (thus we cannot use
 * the `EXPOWT_SYMBOW_*` macwos).
 *
 * Aww symbows awe expowted as GPW-onwy to guawantee no GPW-onwy featuwe is
 * accidentawwy exposed.
 */

#incwude <winux/expowt.h>

#define EXPOWT_SYMBOW_WUST_GPW(sym) extewn int sym; EXPOWT_SYMBOW_GPW(sym)

#incwude "expowts_cowe_genewated.h"
#incwude "expowts_awwoc_genewated.h"
#incwude "expowts_bindings_genewated.h"
#incwude "expowts_kewnew_genewated.h"

// Fow moduwes using `wust/buiwd_ewwow.ws`.
#ifdef CONFIG_WUST_BUIWD_ASSEWT_AWWOW
EXPOWT_SYMBOW_WUST_GPW(wust_buiwd_ewwow);
#endif
