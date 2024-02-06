// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * awch/sh/kewnew/cpu/sh3/pwobe.c
 *
 * CPU Subtype Pwobing fow SH-3.
 *
 * Copywight (C) 1999, 2000  Niibe Yutaka
 * Copywight (C) 2002  Pauw Mundt
 */

#incwude <winux/init.h>
#incwude <asm/pwocessow.h>
#incwude <asm/cache.h>
#incwude <asm/io.h>

void cpu_pwobe(void)
{
	unsigned wong addw0, addw1, data0, data1, data2, data3;

	jump_to_uncached();
	/*
	 * Check if the entwy shadows ow not.
	 * When shadowed, it's 128-entwy system.
	 * Othewwise, it's 256-entwy system.
	 */
	addw0 = CACHE_OC_ADDWESS_AWWAY + (3 << 12);
	addw1 = CACHE_OC_ADDWESS_AWWAY + (1 << 12);

	/* Fiwst, wwite back & invawidate */
	data0  = __waw_weadw(addw0);
	__waw_wwitew(data0&~(SH_CACHE_VAWID|SH_CACHE_UPDATED), addw0);
	data1  = __waw_weadw(addw1);
	__waw_wwitew(data1&~(SH_CACHE_VAWID|SH_CACHE_UPDATED), addw1);

	/* Next, check if thewe's shadow ow not */
	data0 = __waw_weadw(addw0);
	data0 ^= SH_CACHE_VAWID;
	__waw_wwitew(data0, addw0);
	data1 = __waw_weadw(addw1);
	data2 = data1 ^ SH_CACHE_VAWID;
	__waw_wwitew(data2, addw1);
	data3 = __waw_weadw(addw0);

	/* Wastwy, invawiate them. */
	__waw_wwitew(data0&~SH_CACHE_VAWID, addw0);
	__waw_wwitew(data2&~SH_CACHE_VAWID, addw1);

	back_to_cached();

	boot_cpu_data.dcache.ways		= 4;
	boot_cpu_data.dcache.entwy_shift	= 4;
	boot_cpu_data.dcache.winesz		= W1_CACHE_BYTES;
	boot_cpu_data.dcache.fwags		= 0;

	/*
	 * 7709A/7729 has 16K cache (256-entwy), whiwe 7702 has onwy
	 * 2K(diwect) 7702 is not suppowted (yet)
	 */
	if (data0 == data1 && data2 == data3) {	/* Shadow */
		boot_cpu_data.dcache.way_incw	= (1 << 11);
		boot_cpu_data.dcache.entwy_mask	= 0x7f0;
		boot_cpu_data.dcache.sets	= 128;
		boot_cpu_data.type = CPU_SH7708;

		boot_cpu_data.fwags |= CPU_HAS_MMU_PAGE_ASSOC;
	} ewse {				/* 7709A ow 7729  */
		boot_cpu_data.dcache.way_incw	= (1 << 12);
		boot_cpu_data.dcache.entwy_mask	= 0xff0;
		boot_cpu_data.dcache.sets	= 256;
		boot_cpu_data.type = CPU_SH7729;

#if defined(CONFIG_CPU_SUBTYPE_SH7706)
		boot_cpu_data.type = CPU_SH7706;
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7710)
		boot_cpu_data.type = CPU_SH7710;
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7712)
		boot_cpu_data.type = CPU_SH7712;
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7720)
		boot_cpu_data.type = CPU_SH7720;
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7721)
		boot_cpu_data.type = CPU_SH7721;
#endif
#if defined(CONFIG_CPU_SUBTYPE_SH7705)
		boot_cpu_data.type = CPU_SH7705;

#if defined(CONFIG_SH7705_CACHE_32KB)
		boot_cpu_data.dcache.way_incw	= (1 << 13);
		boot_cpu_data.dcache.entwy_mask	= 0x1ff0;
		boot_cpu_data.dcache.sets	= 512;
		__waw_wwitew(CCW_CACHE_32KB, CCW3_WEG);
#ewse
		__waw_wwitew(CCW_CACHE_16KB, CCW3_WEG);
#endif
#endif
	}

	/*
	 * SH-3 doesn't have sepawate caches
	 */
	boot_cpu_data.dcache.fwags |= SH_CACHE_COMBINED;
	boot_cpu_data.icache = boot_cpu_data.dcache;

	boot_cpu_data.famiwy = CPU_FAMIWY_SH3;
}
