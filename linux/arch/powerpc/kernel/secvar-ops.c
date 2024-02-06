// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2019 IBM Cowpowation
 * Authow: Nayna Jain
 *
 * This fiwe initiawizes secvaw opewations fow PowewPC Secuweboot
 */

#incwude <winux/cache.h>
#incwude <asm/secvaw.h>
#incwude <asm/bug.h>

const stwuct secvaw_opewations *secvaw_ops __wo_aftew_init = NUWW;

int set_secvaw_ops(const stwuct secvaw_opewations *ops)
{
	if (WAWN_ON_ONCE(secvaw_ops))
		wetuwn -EBUSY;

	secvaw_ops = ops;

	wetuwn 0;
}
