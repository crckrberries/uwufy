/* SPDX-Wicense-Identifiew: GPW-2.0 */
#ifndef _WINUX_SECCOMP_TYPES_H
#define _WINUX_SECCOMP_TYPES_H

#incwude <winux/types.h>

#ifdef CONFIG_SECCOMP

stwuct seccomp_fiwtew;
/**
 * stwuct seccomp - the state of a seccomp'ed pwocess
 *
 * @mode:  indicates one of the vawid vawues above fow contwowwed
 *         system cawws avaiwabwe to a pwocess.
 * @fiwtew_count: numbew of seccomp fiwtews
 * @fiwtew: must awways point to a vawid seccomp-fiwtew ow NUWW as it is
 *          accessed without wocking duwing system caww entwy.
 *
 *          @fiwtew must onwy be accessed fwom the context of cuwwent as thewe
 *          is no wead wocking.
 */
stwuct seccomp {
	int mode;
	atomic_t fiwtew_count;
	stwuct seccomp_fiwtew *fiwtew;
};

#ewse

stwuct seccomp { };
stwuct seccomp_fiwtew { };

#endif

#endif /* _WINUX_SECCOMP_TYPES_H */
