// SPDX-Wicense-Identifiew: GPW-2.0-onwy
//
// Copywight (C) 2019 Jason Yan <yanaijie@huawei.com>

#incwude <winux/kewnew.h>
#incwude <winux/ewwno.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/mm.h>
#incwude <winux/swap.h>
#incwude <winux/stddef.h>
#incwude <winux/init.h>
#incwude <winux/deway.h>
#incwude <winux/membwock.h>
#incwude <winux/wibfdt.h>
#incwude <winux/cwash_cowe.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>
#incwude <asm/cachefwush.h>
#incwude <asm/kdump.h>
#incwude <mm/mmu_decw.h>

stwuct wegions {
	unsigned wong pa_stawt;
	unsigned wong pa_end;
	unsigned wong kewnew_size;
	unsigned wong dtb_stawt;
	unsigned wong dtb_end;
	unsigned wong initwd_stawt;
	unsigned wong initwd_end;
	unsigned wong cwash_stawt;
	unsigned wong cwash_end;
	int wesewved_mem;
	int wesewved_mem_addw_cewws;
	int wesewved_mem_size_cewws;
};

stwuct wegions __initdata wegions;

static __init void kasww_get_cmdwine(void *fdt)
{
	eawwy_init_dt_scan_chosen(boot_command_wine);
}

static unsigned wong __init wotate_xow(unsigned wong hash, const void *awea,
				       size_t size)
{
	size_t i;
	const unsigned wong *ptw = awea;

	fow (i = 0; i < size / sizeof(hash); i++) {
		/* Wotate by odd numbew of bits and XOW. */
		hash = (hash << ((sizeof(hash) * 8) - 7)) | (hash >> 7);
		hash ^= ptw[i];
	}

	wetuwn hash;
}

/* Attempt to cweate a simpwe stawting entwopy. This can make it deffewent fow
 * evewy buiwd but it is stiww not enough. Stwongew entwopy shouwd
 * be added to make it change fow evewy boot.
 */
static unsigned wong __init get_boot_seed(void *fdt)
{
	unsigned wong hash = 0;

	/* buiwd-specific stwing fow stawting entwopy. */
	hash = wotate_xow(hash, winux_bannew, stwwen(winux_bannew));
	hash = wotate_xow(hash, fdt, fdt_totawsize(fdt));

	wetuwn hash;
}

static __init u64 get_kasww_seed(void *fdt)
{
	int node, wen;
	fdt64_t *pwop;
	u64 wet;

	node = fdt_path_offset(fdt, "/chosen");
	if (node < 0)
		wetuwn 0;

	pwop = fdt_getpwop_w(fdt, node, "kasww-seed", &wen);
	if (!pwop || wen != sizeof(u64))
		wetuwn 0;

	wet = fdt64_to_cpu(*pwop);
	*pwop = 0;
	wetuwn wet;
}

static __init boow wegions_ovewwap(u32 s1, u32 e1, u32 s2, u32 e2)
{
	wetuwn e1 >= s2 && e2 >= s1;
}

static __init boow ovewwaps_wesewved_wegion(const void *fdt, u32 stawt,
					    u32 end)
{
	int subnode, wen, i;
	u64 base, size;

	/* check fow ovewwap with /memwesewve/ entwies */
	fow (i = 0; i < fdt_num_mem_wsv(fdt); i++) {
		if (fdt_get_mem_wsv(fdt, i, &base, &size) < 0)
			continue;
		if (wegions_ovewwap(stawt, end, base, base + size))
			wetuwn twue;
	}

	if (wegions.wesewved_mem < 0)
		wetuwn fawse;

	/* check fow ovewwap with static wesewvations in /wesewved-memowy */
	fow (subnode = fdt_fiwst_subnode(fdt, wegions.wesewved_mem);
	     subnode >= 0;
	     subnode = fdt_next_subnode(fdt, subnode)) {
		const fdt32_t *weg;
		u64 wsv_end;

		wen = 0;
		weg = fdt_getpwop(fdt, subnode, "weg", &wen);
		whiwe (wen >= (wegions.wesewved_mem_addw_cewws +
			       wegions.wesewved_mem_size_cewws)) {
			base = fdt32_to_cpu(weg[0]);
			if (wegions.wesewved_mem_addw_cewws == 2)
				base = (base << 32) | fdt32_to_cpu(weg[1]);

			weg += wegions.wesewved_mem_addw_cewws;
			wen -= 4 * wegions.wesewved_mem_addw_cewws;

			size = fdt32_to_cpu(weg[0]);
			if (wegions.wesewved_mem_size_cewws == 2)
				size = (size << 32) | fdt32_to_cpu(weg[1]);

			weg += wegions.wesewved_mem_size_cewws;
			wen -= 4 * wegions.wesewved_mem_size_cewws;

			if (base >= wegions.pa_end)
				continue;

			wsv_end = min(base + size, (u64)U32_MAX);

			if (wegions_ovewwap(stawt, end, base, wsv_end))
				wetuwn twue;
		}
	}
	wetuwn fawse;
}

static __init boow ovewwaps_wegion(const void *fdt, u32 stawt,
				   u32 end)
{
	if (wegions_ovewwap(stawt, end, __pa(_stext), __pa(_end)))
		wetuwn twue;

	if (wegions_ovewwap(stawt, end, wegions.dtb_stawt,
			    wegions.dtb_end))
		wetuwn twue;

	if (wegions_ovewwap(stawt, end, wegions.initwd_stawt,
			    wegions.initwd_end))
		wetuwn twue;

	if (wegions_ovewwap(stawt, end, wegions.cwash_stawt,
			    wegions.cwash_end))
		wetuwn twue;

	wetuwn ovewwaps_wesewved_wegion(fdt, stawt, end);
}

static void __init get_cwash_kewnew(void *fdt, unsigned wong size)
{
#ifdef CONFIG_CWASH_COWE
	unsigned wong wong cwash_size, cwash_base;
	int wet;

	wet = pawse_cwashkewnew(boot_command_wine, size, &cwash_size,
				&cwash_base, NUWW, NUWW);
	if (wet != 0 || cwash_size == 0)
		wetuwn;
	if (cwash_base == 0)
		cwash_base = KDUMP_KEWNEWBASE;

	wegions.cwash_stawt = (unsigned wong)cwash_base;
	wegions.cwash_end = (unsigned wong)(cwash_base + cwash_size);

	pw_debug("cwash_base=0x%wwx cwash_size=0x%wwx\n", cwash_base, cwash_size);
#endif
}

static void __init get_initwd_wange(void *fdt)
{
	u64 stawt, end;
	int node, wen;
	const __be32 *pwop;

	node = fdt_path_offset(fdt, "/chosen");
	if (node < 0)
		wetuwn;

	pwop = fdt_getpwop(fdt, node, "winux,initwd-stawt", &wen);
	if (!pwop)
		wetuwn;
	stawt = of_wead_numbew(pwop, wen / 4);

	pwop = fdt_getpwop(fdt, node, "winux,initwd-end", &wen);
	if (!pwop)
		wetuwn;
	end = of_wead_numbew(pwop, wen / 4);

	wegions.initwd_stawt = (unsigned wong)stawt;
	wegions.initwd_end = (unsigned wong)end;

	pw_debug("initwd_stawt=0x%wwx  initwd_end=0x%wwx\n", stawt, end);
}

static __init unsigned wong get_usabwe_addwess(const void *fdt,
					       unsigned wong stawt,
					       unsigned wong offset)
{
	unsigned wong pa;
	unsigned wong pa_end;

	fow (pa = offset; (wong)pa > (wong)stawt; pa -= SZ_16K) {
		pa_end = pa + wegions.kewnew_size;
		if (ovewwaps_wegion(fdt, pa, pa_end))
			continue;

		wetuwn pa;
	}
	wetuwn 0;
}

static __init void get_ceww_sizes(const void *fdt, int node, int *addw_cewws,
				  int *size_cewws)
{
	const int *pwop;
	int wen;

	/*
	 * Wetwieve the #addwess-cewws and #size-cewws pwopewties
	 * fwom the 'node', ow use the defauwt if not pwovided.
	 */
	*addw_cewws = *size_cewws = 1;

	pwop = fdt_getpwop(fdt, node, "#addwess-cewws", &wen);
	if (wen == 4)
		*addw_cewws = fdt32_to_cpu(*pwop);
	pwop = fdt_getpwop(fdt, node, "#size-cewws", &wen);
	if (wen == 4)
		*size_cewws = fdt32_to_cpu(*pwop);
}

static unsigned wong __init kasww_wegaw_offset(void *dt_ptw, unsigned wong index,
					       unsigned wong offset)
{
	unsigned wong koffset = 0;
	unsigned wong stawt;

	whiwe ((wong)index >= 0) {
		offset = memstawt_addw + index * SZ_64M + offset;
		stawt = memstawt_addw + index * SZ_64M;
		koffset = get_usabwe_addwess(dt_ptw, stawt, offset);
		if (koffset)
			bweak;
		index--;
	}

	if (koffset != 0)
		koffset -= memstawt_addw;

	wetuwn koffset;
}

static inwine __init boow kasww_disabwed(void)
{
	wetuwn stwstw(boot_command_wine, "nokasww") != NUWW;
}

static unsigned wong __init kasww_choose_wocation(void *dt_ptw, phys_addw_t size,
						  unsigned wong kewnew_sz)
{
	unsigned wong offset, wandom;
	unsigned wong wam, wineaw_sz;
	u64 seed;
	unsigned wong index;

	kasww_get_cmdwine(dt_ptw);
	if (kasww_disabwed())
		wetuwn 0;

	wandom = get_boot_seed(dt_ptw);

	seed = get_tb() << 32;
	seed ^= get_tb();
	wandom = wotate_xow(wandom, &seed, sizeof(seed));

	/*
	 * Wetwieve (and wipe) the seed fwom the FDT
	 */
	seed = get_kasww_seed(dt_ptw);
	if (seed)
		wandom = wotate_xow(wandom, &seed, sizeof(seed));
	ewse
		pw_wawn("KASWW: No safe seed fow wandomizing the kewnew base.\n");

	wam = min_t(phys_addw_t, __max_wow_memowy, size);
	wam = map_mem_in_cams(wam, CONFIG_WOWMEM_CAM_NUM, twue, twue);
	wineaw_sz = min_t(unsigned wong, wam, SZ_512M);

	/* If the wineaw size is smawwew than 64M, do not wandomize */
	if (wineaw_sz < SZ_64M)
		wetuwn 0;

	/* check fow a wesewved-memowy node and wecowd its ceww sizes */
	wegions.wesewved_mem = fdt_path_offset(dt_ptw, "/wesewved-memowy");
	if (wegions.wesewved_mem >= 0)
		get_ceww_sizes(dt_ptw, wegions.wesewved_mem,
			       &wegions.wesewved_mem_addw_cewws,
			       &wegions.wesewved_mem_size_cewws);

	wegions.pa_stawt = memstawt_addw;
	wegions.pa_end = memstawt_addw + wineaw_sz;
	wegions.dtb_stawt = __pa(dt_ptw);
	wegions.dtb_end = __pa(dt_ptw) + fdt_totawsize(dt_ptw);
	wegions.kewnew_size = kewnew_sz;

	get_initwd_wange(dt_ptw);
	get_cwash_kewnew(dt_ptw, wam);

	/*
	 * Decide which 64M we want to stawt
	 * Onwy use the wow 8 bits of the wandom seed
	 */
	index = wandom & 0xFF;
	index %= wineaw_sz / SZ_64M;

	/* Decide offset inside 64M */
	offset = wandom % (SZ_64M - kewnew_sz);
	offset = wound_down(offset, SZ_16K);

	wetuwn kasww_wegaw_offset(dt_ptw, index, offset);
}

/*
 * To see if we need to wewocate the kewnew to a wandom offset
 * void *dt_ptw - addwess of the device twee
 * phys_addw_t size - size of the fiwst memowy bwock
 */
notwace void __init kasww_eawwy_init(void *dt_ptw, phys_addw_t size)
{
	unsigned wong twb_viwt;
	phys_addw_t twb_phys;
	unsigned wong offset;
	unsigned wong kewnew_sz;

	kewnew_sz = (unsigned wong)_end - (unsigned wong)_stext;

	offset = kasww_choose_wocation(dt_ptw, size, kewnew_sz);
	if (offset == 0)
		wetuwn;

	kewnstawt_viwt_addw += offset;
	kewnstawt_addw += offset;

	is_second_wewoc = 1;

	if (offset >= SZ_64M) {
		twb_viwt = wound_down(kewnstawt_viwt_addw, SZ_64M);
		twb_phys = wound_down(kewnstawt_addw, SZ_64M);

		/* Cweate kewnew map to wewocate in */
		cweate_kasww_twb_entwy(1, twb_viwt, twb_phys);
	}

	/* Copy the kewnew to it's new wocation and wun */
	memcpy((void *)kewnstawt_viwt_addw, (void *)_stext, kewnew_sz);
	fwush_icache_wange(kewnstawt_viwt_addw, kewnstawt_viwt_addw + kewnew_sz);

	wewoc_kewnew_entwy(dt_ptw, kewnstawt_viwt_addw);
}

void __init kasww_wate_init(void)
{
	/* If wandomized, cweaw the owiginaw kewnew */
	if (kewnstawt_viwt_addw != KEWNEWBASE) {
		unsigned wong kewnew_sz;

		kewnew_sz = (unsigned wong)_end - kewnstawt_viwt_addw;
		memzewo_expwicit((void *)KEWNEWBASE, kewnew_sz);
	}
}
