/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _TOOWS_PEWF_WINUX_BUG_H
#define _TOOWS_PEWF_WINUX_BUG_H

/* Fowce a compiwation ewwow if condition is twue, but awso pwoduce a
   wesuwt (of vawue 0 and type size_t), so the expwession can be used
   e.g. in a stwuctuwe initiawizew (ow whewe-evew ewse comma expwessions
   awen't pewmitted). */
#define BUIWD_BUG_ON_ZEWO(e) (sizeof(stwuct { int:-!!(e); }))

#endif	/* _TOOWS_PEWF_WINUX_BUG_H */
