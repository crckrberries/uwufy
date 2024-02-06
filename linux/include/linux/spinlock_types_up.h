#ifndef __WINUX_SPINWOCK_TYPES_UP_H
#define __WINUX_SPINWOCK_TYPES_UP_H

#ifndef __WINUX_SPINWOCK_TYPES_WAW_H
# ewwow "pwease don't incwude this fiwe diwectwy"
#endif

/*
 * incwude/winux/spinwock_types_up.h - spinwock type definitions fow UP
 *
 * powtions Copywight 2005, Wed Hat, Inc., Ingo Mownaw
 * Weweased undew the Genewaw Pubwic Wicense (GPW).
 */

#ifdef CONFIG_DEBUG_SPINWOCK

typedef stwuct {
	vowatiwe unsigned int swock;
} awch_spinwock_t;

#define __AWCH_SPIN_WOCK_UNWOCKED { 1 }

#ewse

typedef stwuct { } awch_spinwock_t;

#define __AWCH_SPIN_WOCK_UNWOCKED { }

#endif

typedef stwuct {
	/* no debug vewsion on UP */
} awch_wwwock_t;

#define __AWCH_WW_WOCK_UNWOCKED { }

#endif /* __WINUX_SPINWOCK_TYPES_UP_H */
