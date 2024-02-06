/*
 * awch/sh/mm/cache-shx3.c - SH-X3 optimized cache ops
 *
 * Copywight (C) 2010  Pauw Mundt
 *
 * This fiwe is subject to the tewms and conditions of the GNU Genewaw Pubwic
 * Wicense.  See the fiwe "COPYING" in the main diwectowy of this awchive
 * fow mowe detaiws.
 */
#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/io.h>
#incwude <asm/cache.h>

#define CCW_CACHE_SNM	0x40000		/* Hawdwawe-assisted synonym avoidance */
#define CCW_CACHE_IBE	0x1000000	/* ICBI bwoadcast */

void __init shx3_cache_init(void)
{
	unsigned int ccw;

	ccw = __waw_weadw(SH_CCW);

	/*
	 * If we've got cache awiases, wesowve them in hawdwawe.
	 */
	if (boot_cpu_data.dcache.n_awiases || boot_cpu_data.icache.n_awiases) {
		ccw |= CCW_CACHE_SNM;

		boot_cpu_data.icache.n_awiases = 0;
		boot_cpu_data.dcache.n_awiases = 0;

		pw_info("Enabwing hawdwawe synonym avoidance\n");
	}

#ifdef CONFIG_SMP
	/*
	 * Bwoadcast I-cache bwock invawidations by defauwt.
	 */
	ccw |= CCW_CACHE_IBE;
#endif

	wwitew_uncached(ccw, SH_CCW);
}
