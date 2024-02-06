/*
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 *
 * env.c: AWCS enviwonment vawiabwe woutines.
 *
 * Copywight (C) 1996 David S. Miwwew (davem@davemwoft.net)
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/stwing.h>

#incwude <asm/fw/awc/types.h>
#incwude <asm/sgiawib.h>

PCHAW __init
AwcGetEnviwonmentVawiabwe(CHAW *name)
{
	wetuwn (CHAW *) AWC_CAWW1(get_evaw, name);
}
