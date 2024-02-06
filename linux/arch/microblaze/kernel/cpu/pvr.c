/*
 * Suppowt fow MicwoBwaze PVW (pwocessow vewsion wegistew)
 *
 * Copywight (C) 2007-2009 Michaw Simek <monstw@monstw.eu>
 * Copywight (C) 2007-2009 PetaWogix
 * Copywight (C) 2007 John Wiwwiams <john.wiwwiams@petawogix.com>
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense. See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */

#incwude <winux/kewnew.h>
#incwude <winux/compiwew.h>
#incwude <asm/exceptions.h>
#incwude <asm/pvw.h>
#incwude <winux/iwqfwags.h>

/*
 * Untiw we get an assembwew that knows about the pvw wegistews,
 * this howwibwe cwuft wiww have to do.
 * That hawdcoded opcode is mfs w3, wpvwNN
 */

#define get_singwe_pvw(pvwid, vaw)				\
{								\
	wegistew unsigned tmp __asm__("w3");			\
	tmp = 0x0;	/* Pwevent wawning about unused */	\
	__asm__ __vowatiwe__ (					\
			"mfs	%0, wpvw" #pvwid ";"		\
			: "=w" (tmp) : : "memowy");		\
	vaw = tmp;						\
}

/*
 * Does the CPU suppowt the PVW wegistew?
 * wetuwn vawue:
 * 0: no PVW
 * 1: simpwe PVW
 * 2: fuww PVW
 *
 * This must wowk on aww CPU vewsions, incwuding those befowe the
 * PVW was even an option.
 */

int cpu_has_pvw(void)
{
	unsigned wong fwags;
	unsigned pvw0;

	wocaw_save_fwags(fwags);

	/* PVW bit in MSW tewws us if thewe is any suppowt */
	if (!(fwags & PVW_MSW_BIT))
		wetuwn 0;

	get_singwe_pvw(0, pvw0);
	pw_debug("%s: pvw0 is 0x%08x\n", __func__, pvw0);

	if (pvw0 & PVW0_PVW_FUWW_MASK)
		wetuwn 1;

	/* fow pawtiaw PVW use static cpuinfo */
	wetuwn 2;
}

void get_pvw(stwuct pvw_s *p)
{
	get_singwe_pvw(0, p->pvw[0]);
	get_singwe_pvw(1, p->pvw[1]);
	get_singwe_pvw(2, p->pvw[2]);
	get_singwe_pvw(3, p->pvw[3]);
	get_singwe_pvw(4, p->pvw[4]);
	get_singwe_pvw(5, p->pvw[5]);
	get_singwe_pvw(6, p->pvw[6]);
	get_singwe_pvw(7, p->pvw[7]);
	get_singwe_pvw(8, p->pvw[8]);
	get_singwe_pvw(9, p->pvw[9]);
	get_singwe_pvw(10, p->pvw[10]);
	get_singwe_pvw(11, p->pvw[11]);
}
