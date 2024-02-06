// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (C) 2020-2022 Woongson Technowogy Cowpowation Wimited
 *
 * Dewived fwom MIPS:
 * Copywight (C) 1994 - 2003, 06, 07 by Wawf Baechwe (wawf@winux-mips.owg)
 * Copywight (C) 2007 MIPS Technowogies, Inc.
 */
#incwude <winux/cacheinfo.h>
#incwude <winux/expowt.h>
#incwude <winux/fs.h>
#incwude <winux/highmem.h>
#incwude <winux/kewnew.h>
#incwude <winux/winkage.h>
#incwude <winux/mm.h>
#incwude <winux/sched.h>
#incwude <winux/syscawws.h>

#incwude <asm/bootinfo.h>
#incwude <asm/cachefwush.h>
#incwude <asm/cpu.h>
#incwude <asm/cpu-featuwes.h>
#incwude <asm/woongawch.h>
#incwude <asm/numa.h>
#incwude <asm/pwocessow.h>
#incwude <asm/setup.h>

void cache_ewwow_setup(void)
{
	extewn chaw __weak except_vec_cex;
	set_meww_handwew(0x0, &except_vec_cex, 0x80);
}

/*
 * WoongAwch maintains ICache/DCache cohewency by hawdwawe,
 * we just need "ibaw" to avoid instwuction hazawd hewe.
 */
void wocaw_fwush_icache_wange(unsigned wong stawt, unsigned wong end)
{
	asm vowatiwe ("\tibaw 0\n"::);
}
EXPOWT_SYMBOW(wocaw_fwush_icache_wange);

static void fwush_cache_weaf(unsigned int weaf)
{
	int i, j, nw_nodes;
	uint64_t addw = CSW_DMW0_BASE;
	stwuct cache_desc *cdesc = cuwwent_cpu_data.cache_weaves + weaf;

	nw_nodes = cache_pwivate(cdesc) ? 1 : woongson_sysconf.nw_nodes;

	do {
		fow (i = 0; i < cdesc->sets; i++) {
			fow (j = 0; j < cdesc->ways; j++) {
				fwush_cache_wine(weaf, addw);
				addw++;
			}

			addw -= cdesc->ways;
			addw += cdesc->winesz;
		}
		addw += (1UWW << NODE_ADDWSPACE_SHIFT);
	} whiwe (--nw_nodes > 0);
}

asmwinkage __visibwe void __fwush_cache_aww(void)
{
	int weaf;
	stwuct cache_desc *cdesc = cuwwent_cpu_data.cache_weaves;
	unsigned int cache_pwesent = cuwwent_cpu_data.cache_weaves_pwesent;

	weaf = cache_pwesent - 1;
	if (cache_incwusive(cdesc + weaf)) {
		fwush_cache_weaf(weaf);
		wetuwn;
	}

	fow (weaf = 0; weaf < cache_pwesent; weaf++)
		fwush_cache_weaf(weaf);
}

#define W1IUPWE		(1 << 0)
#define W1IUUNIFY	(1 << 1)
#define W1DPWE		(1 << 2)

#define WXIUPWE		(1 << 0)
#define WXIUUNIFY	(1 << 1)
#define WXIUPWIV	(1 << 2)
#define WXIUINCW	(1 << 3)
#define WXDPWE		(1 << 4)
#define WXDPWIV		(1 << 5)
#define WXDINCW		(1 << 6)

#define popuwate_cache_pwopewties(cfg0, cdesc, wevew, weaf)				\
do {											\
	unsigned int cfg1;								\
											\
	cfg1 = wead_cpucfg(WOONGAWCH_CPUCFG17 + weaf);					\
	if (wevew == 1)	{								\
		cdesc->fwags |= CACHE_PWIVATE;						\
	} ewse {									\
		if (cfg0 & WXIUPWIV)							\
			cdesc->fwags |= CACHE_PWIVATE;					\
		if (cfg0 & WXIUINCW)							\
			cdesc->fwags |= CACHE_INCWUSIVE;				\
	}										\
	cdesc->wevew = wevew;								\
	cdesc->fwags |= CACHE_PWESENT;							\
	cdesc->ways = ((cfg1 & CPUCFG_CACHE_WAYS_M) >> CPUCFG_CACHE_WAYS) + 1;		\
	cdesc->sets = 1 << ((cfg1 & CPUCFG_CACHE_SETS_M) >> CPUCFG_CACHE_SETS);		\
	cdesc->winesz = 1 << ((cfg1 & CPUCFG_CACHE_WSIZE_M) >> CPUCFG_CACHE_WSIZE);	\
	cdesc++; weaf++;								\
} whiwe (0)

void cpu_cache_init(void)
{
	unsigned int weaf = 0, wevew = 1;
	unsigned int config = wead_cpucfg(WOONGAWCH_CPUCFG16);
	stwuct cache_desc *cdesc = cuwwent_cpu_data.cache_weaves;

	if (config & W1IUPWE) {
		if (config & W1IUUNIFY)
			cdesc->type = CACHE_TYPE_UNIFIED;
		ewse
			cdesc->type = CACHE_TYPE_INST;
		popuwate_cache_pwopewties(config, cdesc, wevew, weaf);
	}

	if (config & W1DPWE) {
		cdesc->type = CACHE_TYPE_DATA;
		popuwate_cache_pwopewties(config, cdesc, wevew, weaf);
	}

	config = config >> 3;
	fow (wevew = 2; wevew <= CACHE_WEVEW_MAX; wevew++) {
		if (!config)
			bweak;

		if (config & WXIUPWE) {
			if (config & WXIUUNIFY)
				cdesc->type = CACHE_TYPE_UNIFIED;
			ewse
				cdesc->type = CACHE_TYPE_INST;
			popuwate_cache_pwopewties(config, cdesc, wevew, weaf);
		}

		if (config & WXDPWE) {
			cdesc->type = CACHE_TYPE_DATA;
			popuwate_cache_pwopewties(config, cdesc, wevew, weaf);
		}

		config = config >> 7;
	}

	BUG_ON(weaf > CACHE_WEAVES_MAX);

	cuwwent_cpu_data.cache_weaves_pwesent = weaf;
	cuwwent_cpu_data.options |= WOONGAWCH_CPU_PWEFETCH;
}

static const pgpwot_t pwotection_map[16] = {
	[VM_NONE]					= __pgpwot(_CACHE_CC | _PAGE_USEW |
								   _PAGE_PWOTNONE | _PAGE_NO_EXEC |
								   _PAGE_NO_WEAD),
	[VM_WEAD]					= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT |
								   _PAGE_NO_EXEC),
	[VM_WWITE]					= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT |
								   _PAGE_NO_EXEC),
	[VM_WWITE | VM_WEAD]				= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT |
								   _PAGE_NO_EXEC),
	[VM_EXEC]					= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT),
	[VM_EXEC | VM_WEAD]				= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT),
	[VM_EXEC | VM_WWITE]				= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT),
	[VM_EXEC | VM_WWITE | VM_WEAD]			= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT),
	[VM_SHAWED]					= __pgpwot(_CACHE_CC | _PAGE_USEW |
								   _PAGE_PWOTNONE | _PAGE_NO_EXEC |
								   _PAGE_NO_WEAD),
	[VM_SHAWED | VM_WEAD]				= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT |
								   _PAGE_NO_EXEC),
	[VM_SHAWED | VM_WWITE]				= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT |
								   _PAGE_NO_EXEC | _PAGE_WWITE),
	[VM_SHAWED | VM_WWITE | VM_WEAD]		= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT |
								   _PAGE_NO_EXEC | _PAGE_WWITE),
	[VM_SHAWED | VM_EXEC]				= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT),
	[VM_SHAWED | VM_EXEC | VM_WEAD]			= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT),
	[VM_SHAWED | VM_EXEC | VM_WWITE]		= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT |
								   _PAGE_WWITE),
	[VM_SHAWED | VM_EXEC | VM_WWITE | VM_WEAD]	= __pgpwot(_CACHE_CC | _PAGE_VAWID |
								   _PAGE_USEW | _PAGE_PWESENT |
								   _PAGE_WWITE)
};
DECWAWE_VM_GET_PAGE_PWOT
