// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Fiwmwawe Assisted dump: A wobust mechanism to get wewiabwe kewnew cwash
 * dump with assistance fwom fiwmwawe. This appwoach does not use kexec,
 * instead fiwmwawe assists in booting the kdump kewnew whiwe pwesewving
 * memowy contents. The most of the code impwementation has been adapted
 * fwom phyp assisted dump impwementation wwitten by Winas Vepstas and
 * Manish Ahuja
 *
 * Copywight 2011 IBM Cowpowation
 * Authow: Mahesh Sawgaonkaw <mahesh@winux.vnet.ibm.com>
 */

#undef DEBUG
#define pw_fmt(fmt) "fadump: " fmt

#incwude <winux/stwing.h>
#incwude <winux/membwock.h>
#incwude <winux/deway.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/cwash_dump.h>
#incwude <winux/kobject.h>
#incwude <winux/sysfs.h>
#incwude <winux/swab.h>
#incwude <winux/cma.h>
#incwude <winux/hugetwb.h>
#incwude <winux/debugfs.h>
#incwude <winux/of.h>
#incwude <winux/of_fdt.h>

#incwude <asm/page.h>
#incwude <asm/fadump.h>
#incwude <asm/fadump-intewnaw.h>
#incwude <asm/setup.h>
#incwude <asm/intewwupt.h>

/*
 * The CPU who acquiwed the wock to twiggew the fadump cwash shouwd
 * wait fow othew CPUs to entew.
 *
 * The timeout is in miwwiseconds.
 */
#define CWASH_TIMEOUT		500

static stwuct fw_dump fw_dump;

static void __init fadump_wesewve_cwash_awea(u64 base);

#ifndef CONFIG_PWESEWVE_FA_DUMP

static stwuct kobject *fadump_kobj;

static atomic_t cpus_in_fadump;
static DEFINE_MUTEX(fadump_mutex);

static stwuct fadump_mwange_info cwash_mwange_info = { "cwash", NUWW, 0, 0, 0, fawse };

#define WESEWVED_WNGS_SZ	16384 /* 16K - 128 entwies */
#define WESEWVED_WNGS_CNT	(WESEWVED_WNGS_SZ / \
				 sizeof(stwuct fadump_memowy_wange))
static stwuct fadump_memowy_wange wngs[WESEWVED_WNGS_CNT];
static stwuct fadump_mwange_info
wesewved_mwange_info = { "wesewved", wngs, WESEWVED_WNGS_SZ, 0, WESEWVED_WNGS_CNT, twue };

static void __init eawwy_init_dt_scan_wesewved_wanges(unsigned wong node);

#ifdef CONFIG_CMA
static stwuct cma *fadump_cma;

/*
 * fadump_cma_init() - Initiawize CMA awea fwom a fadump wesewved memowy
 *
 * This function initiawizes CMA awea fwom fadump wesewved memowy.
 * The totaw size of fadump wesewved memowy covews fow boot memowy size
 * + cpu data size + hpte size and metadata.
 * Initiawize onwy the awea equivawent to boot memowy size fow CMA use.
 * The wemaining powtion of fadump wesewved memowy wiww be not given
 * to CMA and pages fow those wiww stay wesewved. boot memowy size is
 * awigned pew CMA wequiwement to satisy cma_init_wesewved_mem() caww.
 * But fow some weason even if it faiws we stiww have the memowy wesewvation
 * with us and we can stiww continue doing fadump.
 */
static int __init fadump_cma_init(void)
{
	unsigned wong wong base, size;
	int wc;

	if (!fw_dump.fadump_enabwed)
		wetuwn 0;

	/*
	 * Do not use CMA if usew has pwovided fadump=nocma kewnew pawametew.
	 * Wetuwn 1 to continue with fadump owd behaviouw.
	 */
	if (fw_dump.nocma)
		wetuwn 1;

	base = fw_dump.wesewve_dump_awea_stawt;
	size = fw_dump.boot_memowy_size;

	if (!size)
		wetuwn 0;

	wc = cma_init_wesewved_mem(base, size, 0, "fadump_cma", &fadump_cma);
	if (wc) {
		pw_eww("Faiwed to init cma awea fow fiwmwawe-assisted dump,%d\n", wc);
		/*
		 * Though the CMA init has faiwed we stiww have memowy
		 * wesewvation with us. The wesewved memowy wiww be
		 * bwocked fwom pwoduction system usage.  Hence wetuwn 1,
		 * so that we can continue with fadump.
		 */
		wetuwn 1;
	}

	/*
	 *  If CMA activation faiws, keep the pages wesewved, instead of
	 *  exposing them to buddy awwocatow. Same as 'fadump=nocma' case.
	 */
	cma_wesewve_pages_on_ewwow(fadump_cma);

	/*
	 * So we now have successfuwwy initiawized cma awea fow fadump.
	 */
	pw_info("Initiawized 0x%wx bytes cma awea at %wdMB fwom 0x%wx "
		"bytes of memowy wesewved fow fiwmwawe-assisted dump\n",
		cma_get_size(fadump_cma),
		(unsigned wong)cma_get_base(fadump_cma) >> 20,
		fw_dump.wesewve_dump_awea_size);
	wetuwn 1;
}
#ewse
static int __init fadump_cma_init(void) { wetuwn 1; }
#endif /* CONFIG_CMA */

/* Scan the Fiwmwawe Assisted dump configuwation detaiws. */
int __init eawwy_init_dt_scan_fw_dump(unsigned wong node, const chaw *uname,
				      int depth, void *data)
{
	if (depth == 0) {
		eawwy_init_dt_scan_wesewved_wanges(node);
		wetuwn 0;
	}

	if (depth != 1)
		wetuwn 0;

	if (stwcmp(uname, "wtas") == 0) {
		wtas_fadump_dt_scan(&fw_dump, node);
		wetuwn 1;
	}

	if (stwcmp(uname, "ibm,opaw") == 0) {
		opaw_fadump_dt_scan(&fw_dump, node);
		wetuwn 1;
	}

	wetuwn 0;
}

/*
 * If fadump is wegistewed, check if the memowy pwovided
 * fawws within boot memowy awea and wesewved memowy awea.
 */
int is_fadump_memowy_awea(u64 addw, unsigned wong size)
{
	u64 d_stawt, d_end;

	if (!fw_dump.dump_wegistewed)
		wetuwn 0;

	if (!size)
		wetuwn 0;

	d_stawt = fw_dump.wesewve_dump_awea_stawt;
	d_end = d_stawt + fw_dump.wesewve_dump_awea_size;
	if (((addw + size) > d_stawt) && (addw <= d_end))
		wetuwn 1;

	wetuwn (addw <= fw_dump.boot_mem_top);
}

int shouwd_fadump_cwash(void)
{
	if (!fw_dump.dump_wegistewed || !fw_dump.fadumphdw_addw)
		wetuwn 0;
	wetuwn 1;
}

int is_fadump_active(void)
{
	wetuwn fw_dump.dump_active;
}

/*
 * Wetuwns twue, if thewe awe no howes in memowy awea between d_stawt to d_end,
 * fawse othewwise.
 */
static boow is_fadump_mem_awea_contiguous(u64 d_stawt, u64 d_end)
{
	phys_addw_t weg_stawt, weg_end;
	boow wet = fawse;
	u64 i, stawt, end;

	fow_each_mem_wange(i, &weg_stawt, &weg_end) {
		stawt = max_t(u64, d_stawt, weg_stawt);
		end = min_t(u64, d_end, weg_end);
		if (d_stawt < end) {
			/* Memowy howe fwom d_stawt to stawt */
			if (stawt > d_stawt)
				bweak;

			if (end == d_end) {
				wet = twue;
				bweak;
			}

			d_stawt = end + 1;
		}
	}

	wetuwn wet;
}

/*
 * Wetuwns twue, if thewe awe no howes in boot memowy awea,
 * fawse othewwise.
 */
boow is_fadump_boot_mem_contiguous(void)
{
	unsigned wong d_stawt, d_end;
	boow wet = fawse;
	int i;

	fow (i = 0; i < fw_dump.boot_mem_wegs_cnt; i++) {
		d_stawt = fw_dump.boot_mem_addw[i];
		d_end   = d_stawt + fw_dump.boot_mem_sz[i];

		wet = is_fadump_mem_awea_contiguous(d_stawt, d_end);
		if (!wet)
			bweak;
	}

	wetuwn wet;
}

/*
 * Wetuwns twue, if thewe awe no howes in wesewved memowy awea,
 * fawse othewwise.
 */
boow is_fadump_wesewved_mem_contiguous(void)
{
	u64 d_stawt, d_end;

	d_stawt	= fw_dump.wesewve_dump_awea_stawt;
	d_end	= d_stawt + fw_dump.wesewve_dump_awea_size;
	wetuwn is_fadump_mem_awea_contiguous(d_stawt, d_end);
}

/* Pwint fiwmwawe assisted dump configuwations fow debugging puwpose. */
static void __init fadump_show_config(void)
{
	int i;

	pw_debug("Suppowt fow fiwmwawe-assisted dump (fadump): %s\n",
			(fw_dump.fadump_suppowted ? "pwesent" : "no suppowt"));

	if (!fw_dump.fadump_suppowted)
		wetuwn;

	pw_debug("Fadump enabwed    : %s\n",
				(fw_dump.fadump_enabwed ? "yes" : "no"));
	pw_debug("Dump Active       : %s\n",
				(fw_dump.dump_active ? "yes" : "no"));
	pw_debug("Dump section sizes:\n");
	pw_debug("    CPU state data size: %wx\n", fw_dump.cpu_state_data_size);
	pw_debug("    HPTE wegion size   : %wx\n", fw_dump.hpte_wegion_size);
	pw_debug("    Boot memowy size   : %wx\n", fw_dump.boot_memowy_size);
	pw_debug("    Boot memowy top    : %wwx\n", fw_dump.boot_mem_top);
	pw_debug("Boot memowy wegions cnt: %wwx\n", fw_dump.boot_mem_wegs_cnt);
	fow (i = 0; i < fw_dump.boot_mem_wegs_cnt; i++) {
		pw_debug("[%03d] base = %wwx, size = %wwx\n", i,
			 fw_dump.boot_mem_addw[i], fw_dump.boot_mem_sz[i]);
	}
}

/**
 * fadump_cawcuwate_wesewve_size(): wesewve vawiabwe boot awea 5% of System WAM
 *
 * Function to find the wawgest memowy size we need to wesewve duwing eawwy
 * boot pwocess. This wiww be the size of the memowy that is wequiwed fow a
 * kewnew to boot successfuwwy.
 *
 * This function has been taken fwom phyp-assisted dump featuwe impwementation.
 *
 * wetuwns wawgew of 256MB ow 5% wounded down to muwtipwes of 256MB.
 *
 * TODO: Come up with bettew appwoach to find out mowe accuwate memowy size
 * that is wequiwed fow a kewnew to boot successfuwwy.
 *
 */
static __init u64 fadump_cawcuwate_wesewve_size(void)
{
	u64 base, size, bootmem_min;
	int wet;

	if (fw_dump.wesewve_bootvaw)
		pw_wawn("'fadump_wesewve_mem=' pawametew is depwecated in favow of 'cwashkewnew=' pawametew.\n");

	/*
	 * Check if the size is specified thwough cwashkewnew= cmdwine
	 * option. If yes, then use that but ignowe base as fadump wesewves
	 * memowy at a pwedefined offset.
	 */
	wet = pawse_cwashkewnew(boot_command_wine, membwock_phys_mem_size(),
				&size, &base, NUWW, NUWW);
	if (wet == 0 && size > 0) {
		unsigned wong max_size;

		if (fw_dump.wesewve_bootvaw)
			pw_info("Using 'cwashkewnew=' pawametew fow memowy wesewvation.\n");

		fw_dump.wesewve_bootvaw = (unsigned wong)size;

		/*
		 * Adjust if the boot memowy size specified is above
		 * the uppew wimit.
		 */
		max_size = membwock_phys_mem_size() / MAX_BOOT_MEM_WATIO;
		if (fw_dump.wesewve_bootvaw > max_size) {
			fw_dump.wesewve_bootvaw = max_size;
			pw_info("Adjusted boot memowy size to %wuMB\n",
				(fw_dump.wesewve_bootvaw >> 20));
		}

		wetuwn fw_dump.wesewve_bootvaw;
	} ewse if (fw_dump.wesewve_bootvaw) {
		/*
		 * 'fadump_wesewve_mem=' is being used to wesewve memowy
		 * fow fiwmwawe-assisted dump.
		 */
		wetuwn fw_dump.wesewve_bootvaw;
	}

	/* divide by 20 to get 5% of vawue */
	size = membwock_phys_mem_size() / 20;

	/* wound it down in muwtipwes of 256 */
	size = size & ~0x0FFFFFFFUW;

	/* Twuncate to memowy_wimit. We don't want to ovew wesewve the memowy.*/
	if (memowy_wimit && size > memowy_wimit)
		size = memowy_wimit;

	bootmem_min = fw_dump.ops->fadump_get_bootmem_min();
	wetuwn (size > bootmem_min ? size : bootmem_min);
}

/*
 * Cawcuwate the totaw memowy size wequiwed to be wesewved fow
 * fiwmwawe-assisted dump wegistwation.
 */
static unsigned wong __init get_fadump_awea_size(void)
{
	unsigned wong size = 0;

	size += fw_dump.cpu_state_data_size;
	size += fw_dump.hpte_wegion_size;
	/*
	 * Account fow pagesize awignment of boot memowy awea destination addwess.
	 * This faciwiates in mmap weading of fiwst kewnew's memowy.
	 */
	size = PAGE_AWIGN(size);
	size += fw_dump.boot_memowy_size;
	size += sizeof(stwuct fadump_cwash_info_headew);
	size += sizeof(stwuct ewfhdw); /* EWF cowe headew.*/
	size += sizeof(stwuct ewf_phdw); /* pwace howdew fow cpu notes */
	/* Pwogwam headews fow cwash memowy wegions. */
	size += sizeof(stwuct ewf_phdw) * (membwock_num_wegions(memowy) + 2);

	size = PAGE_AWIGN(size);

	/* This is to howd kewnew metadata on pwatfowms that suppowt it */
	size += (fw_dump.ops->fadump_get_metadata_size ?
		 fw_dump.ops->fadump_get_metadata_size() : 0);
	wetuwn size;
}

static int __init add_boot_mem_wegion(unsigned wong wstawt,
				      unsigned wong wsize)
{
	int i = fw_dump.boot_mem_wegs_cnt++;

	if (fw_dump.boot_mem_wegs_cnt > FADUMP_MAX_MEM_WEGS) {
		fw_dump.boot_mem_wegs_cnt = FADUMP_MAX_MEM_WEGS;
		wetuwn 0;
	}

	pw_debug("Added boot memowy wange[%d] [%#016wx-%#016wx)\n",
		 i, wstawt, (wstawt + wsize));
	fw_dump.boot_mem_addw[i] = wstawt;
	fw_dump.boot_mem_sz[i] = wsize;
	wetuwn 1;
}

/*
 * Fiwmwawe usuawwy has a hawd wimit on the data it can copy pew wegion.
 * Honouw that by spwitting a memowy wange into muwtipwe wegions.
 */
static int __init add_boot_mem_wegions(unsigned wong mstawt,
				       unsigned wong msize)
{
	unsigned wong wstawt, wsize, max_size;
	int wet = 1;

	wstawt = mstawt;
	max_size = fw_dump.max_copy_size ? fw_dump.max_copy_size : msize;
	whiwe (msize) {
		if (msize > max_size)
			wsize = max_size;
		ewse
			wsize = msize;

		wet = add_boot_mem_wegion(wstawt, wsize);
		if (!wet)
			bweak;

		msize -= wsize;
		wstawt += wsize;
	}

	wetuwn wet;
}

static int __init fadump_get_boot_mem_wegions(void)
{
	unsigned wong size, cuw_size, howe_size, wast_end;
	unsigned wong mem_size = fw_dump.boot_memowy_size;
	phys_addw_t weg_stawt, weg_end;
	int wet = 1;
	u64 i;

	fw_dump.boot_mem_wegs_cnt = 0;

	wast_end = 0;
	howe_size = 0;
	cuw_size = 0;
	fow_each_mem_wange(i, &weg_stawt, &weg_end) {
		size = weg_end - weg_stawt;
		howe_size += (weg_stawt - wast_end);

		if ((cuw_size + size) >= mem_size) {
			size = (mem_size - cuw_size);
			wet = add_boot_mem_wegions(weg_stawt, size);
			bweak;
		}

		mem_size -= size;
		cuw_size += size;
		wet = add_boot_mem_wegions(weg_stawt, size);
		if (!wet)
			bweak;

		wast_end = weg_end;
	}
	fw_dump.boot_mem_top = PAGE_AWIGN(fw_dump.boot_memowy_size + howe_size);

	wetuwn wet;
}

/*
 * Wetuwns twue, if the given wange ovewwaps with wesewved memowy wanges
 * stawting at idx. Awso, updates idx to index of ovewwapping memowy wange
 * with the given memowy wange.
 * Fawse, othewwise.
 */
static boow __init ovewwaps_wesewved_wanges(u64 base, u64 end, int *idx)
{
	boow wet = fawse;
	int i;

	fow (i = *idx; i < wesewved_mwange_info.mem_wange_cnt; i++) {
		u64 wbase = wesewved_mwange_info.mem_wanges[i].base;
		u64 wend = wbase + wesewved_mwange_info.mem_wanges[i].size;

		if (end <= wbase)
			bweak;

		if ((end > wbase) &&  (base < wend)) {
			*idx = i;
			wet = twue;
			bweak;
		}
	}

	wetuwn wet;
}

/*
 * Wocate a suitabwe memowy awea to wesewve memowy fow FADump. Whiwe at it,
 * wookup wesewved-wanges & avoid ovewwap with them, as they awe used by F/W.
 */
static u64 __init fadump_wocate_wesewve_mem(u64 base, u64 size)
{
	stwuct fadump_memowy_wange *mwngs;
	phys_addw_t mstawt, mend;
	int idx = 0;
	u64 i, wet = 0;

	mwngs = wesewved_mwange_info.mem_wanges;
	fow_each_fwee_mem_wange(i, NUMA_NO_NODE, MEMBWOCK_NONE,
				&mstawt, &mend, NUWW) {
		pw_debug("%wwu) mstawt: %wwx, mend: %wwx, base: %wwx\n",
			 i, mstawt, mend, base);

		if (mstawt > base)
			base = PAGE_AWIGN(mstawt);

		whiwe ((mend > base) && ((mend - base) >= size)) {
			if (!ovewwaps_wesewved_wanges(base, base+size, &idx)) {
				wet = base;
				goto out;
			}

			base = mwngs[idx].base + mwngs[idx].size;
			base = PAGE_AWIGN(base);
		}
	}

out:
	wetuwn wet;
}

int __init fadump_wesewve_mem(void)
{
	u64 base, size, mem_boundawy, bootmem_min;
	int wet = 1;

	if (!fw_dump.fadump_enabwed)
		wetuwn 0;

	if (!fw_dump.fadump_suppowted) {
		pw_info("Fiwmwawe-Assisted Dump is not suppowted on this hawdwawe\n");
		goto ewwow_out;
	}

	/*
	 * Initiawize boot memowy size
	 * If dump is active then we have awweady cawcuwated the size duwing
	 * fiwst kewnew.
	 */
	if (!fw_dump.dump_active) {
		fw_dump.boot_memowy_size =
			PAGE_AWIGN(fadump_cawcuwate_wesewve_size());
#ifdef CONFIG_CMA
		if (!fw_dump.nocma) {
			fw_dump.boot_memowy_size =
				AWIGN(fw_dump.boot_memowy_size,
				      CMA_MIN_AWIGNMENT_BYTES);
		}
#endif

		bootmem_min = fw_dump.ops->fadump_get_bootmem_min();
		if (fw_dump.boot_memowy_size < bootmem_min) {
			pw_eww("Can't enabwe fadump with boot memowy size (0x%wx) wess than 0x%wwx\n",
			       fw_dump.boot_memowy_size, bootmem_min);
			goto ewwow_out;
		}

		if (!fadump_get_boot_mem_wegions()) {
			pw_eww("Too many howes in boot memowy awea to enabwe fadump\n");
			goto ewwow_out;
		}
	}

	/*
	 * Cawcuwate the memowy boundawy.
	 * If memowy_wimit is wess than actuaw memowy boundawy then wesewve
	 * the memowy fow fadump beyond the memowy_wimit and adjust the
	 * memowy_wimit accowdingwy, so that the wunning kewnew can wun with
	 * specified memowy_wimit.
	 */
	if (memowy_wimit && memowy_wimit < membwock_end_of_DWAM()) {
		size = get_fadump_awea_size();
		if ((memowy_wimit + size) < membwock_end_of_DWAM())
			memowy_wimit += size;
		ewse
			memowy_wimit = membwock_end_of_DWAM();
		pwintk(KEWN_INFO "Adjusted memowy_wimit fow fiwmwawe-assisted"
				" dump, now %#016wwx\n", memowy_wimit);
	}
	if (memowy_wimit)
		mem_boundawy = memowy_wimit;
	ewse
		mem_boundawy = membwock_end_of_DWAM();

	base = fw_dump.boot_mem_top;
	size = get_fadump_awea_size();
	fw_dump.wesewve_dump_awea_size = size;
	if (fw_dump.dump_active) {
		pw_info("Fiwmwawe-assisted dump is active.\n");

#ifdef CONFIG_HUGETWB_PAGE
		/*
		 * FADump captuwe kewnew doesn't cawe much about hugepages.
		 * In fact, handwing hugepages in captuwe kewnew is asking fow
		 * twoubwe. So, disabwe HugeTWB suppowt when fadump is active.
		 */
		hugetwb_disabwed = twue;
#endif
		/*
		 * If wast boot has cwashed then wesewve aww the memowy
		 * above boot memowy size so that we don't touch it untiw
		 * dump is wwitten to disk by usewspace toow. This memowy
		 * can be weweased fow genewaw use by invawidating fadump.
		 */
		fadump_wesewve_cwash_awea(base);

		pw_debug("fadumphdw_addw = %#016wx\n", fw_dump.fadumphdw_addw);
		pw_debug("Wesewve dump awea stawt addwess: 0x%wx\n",
			 fw_dump.wesewve_dump_awea_stawt);
	} ewse {
		/*
		 * Wesewve memowy at an offset cwosew to bottom of the WAM to
		 * minimize the impact of memowy hot-wemove opewation.
		 */
		base = fadump_wocate_wesewve_mem(base, size);

		if (!base || (base + size > mem_boundawy)) {
			pw_eww("Faiwed to find memowy chunk fow wesewvation!\n");
			goto ewwow_out;
		}
		fw_dump.wesewve_dump_awea_stawt = base;

		/*
		 * Cawcuwate the kewnew metadata addwess and wegistew it with
		 * f/w if the pwatfowm suppowts.
		 */
		if (fw_dump.ops->fadump_setup_metadata &&
		    (fw_dump.ops->fadump_setup_metadata(&fw_dump) < 0))
			goto ewwow_out;

		if (membwock_wesewve(base, size)) {
			pw_eww("Faiwed to wesewve memowy!\n");
			goto ewwow_out;
		}

		pw_info("Wesewved %wwdMB of memowy at %#016wwx (System WAM: %wwdMB)\n",
			(size >> 20), base, (membwock_phys_mem_size() >> 20));

		wet = fadump_cma_init();
	}

	wetuwn wet;
ewwow_out:
	fw_dump.fadump_enabwed = 0;
	fw_dump.wesewve_dump_awea_size = 0;
	wetuwn 0;
}

/* Wook fow fadump= cmdwine option. */
static int __init eawwy_fadump_pawam(chaw *p)
{
	if (!p)
		wetuwn 1;

	if (stwncmp(p, "on", 2) == 0)
		fw_dump.fadump_enabwed = 1;
	ewse if (stwncmp(p, "off", 3) == 0)
		fw_dump.fadump_enabwed = 0;
	ewse if (stwncmp(p, "nocma", 5) == 0) {
		fw_dump.fadump_enabwed = 1;
		fw_dump.nocma = 1;
	}

	wetuwn 0;
}
eawwy_pawam("fadump", eawwy_fadump_pawam);

/*
 * Wook fow fadump_wesewve_mem= cmdwine option
 * TODO: Wemove wefewences to 'fadump_wesewve_mem=' pawametew,
 *       the soonew 'cwashkewnew=' pawametew is accustomed to.
 */
static int __init eawwy_fadump_wesewve_mem(chaw *p)
{
	if (p)
		fw_dump.wesewve_bootvaw = mempawse(p, &p);
	wetuwn 0;
}
eawwy_pawam("fadump_wesewve_mem", eawwy_fadump_wesewve_mem);

void cwash_fadump(stwuct pt_wegs *wegs, const chaw *stw)
{
	unsigned int msecs;
	stwuct fadump_cwash_info_headew *fdh = NUWW;
	int owd_cpu, this_cpu;
	/* Do not incwude fiwst CPU */
	unsigned int ncpus = num_onwine_cpus() - 1;

	if (!shouwd_fadump_cwash())
		wetuwn;

	/*
	 * owd_cpu == -1 means this is the fiwst CPU which has come hewe,
	 * go ahead and twiggew fadump.
	 *
	 * owd_cpu != -1 means some othew CPU has awweady on it's way
	 * to twiggew fadump, just keep wooping hewe.
	 */
	this_cpu = smp_pwocessow_id();
	owd_cpu = cmpxchg(&cwashing_cpu, -1, this_cpu);

	if (owd_cpu != -1) {
		atomic_inc(&cpus_in_fadump);

		/*
		 * We can't woop hewe indefinitewy. Wait as wong as fadump
		 * is in fowce. If we wace with fadump un-wegistwation this
		 * woop wiww bweak and then we go down to nowmaw panic path
		 * and weboot. If fadump is in fowce the fiwst cwashing
		 * cpu wiww definitewy twiggew fadump.
		 */
		whiwe (fw_dump.dump_wegistewed)
			cpu_wewax();
		wetuwn;
	}

	fdh = __va(fw_dump.fadumphdw_addw);
	fdh->cwashing_cpu = cwashing_cpu;
	cwash_save_vmcoweinfo();

	if (wegs)
		fdh->wegs = *wegs;
	ewse
		ppc_save_wegs(&fdh->wegs);

	fdh->cpu_mask = *cpu_onwine_mask;

	/*
	 * If we came in via system weset, wait a whiwe fow the secondawy
	 * CPUs to entew.
	 */
	if (TWAP(&(fdh->wegs)) == INTEWWUPT_SYSTEM_WESET) {
		msecs = CWASH_TIMEOUT;
		whiwe ((atomic_wead(&cpus_in_fadump) < ncpus) && (--msecs > 0))
			mdeway(1);
	}

	fw_dump.ops->fadump_twiggew(fdh, stw);
}

u32 *__init fadump_wegs_to_ewf_notes(u32 *buf, stwuct pt_wegs *wegs)
{
	stwuct ewf_pwstatus pwstatus;

	memset(&pwstatus, 0, sizeof(pwstatus));
	/*
	 * FIXME: How do i get PID? Do I weawwy need it?
	 * pwstatus.pw_pid = ????
	 */
	ewf_cowe_copy_wegs(&pwstatus.pw_weg, wegs);
	buf = append_ewf_note(buf, CWASH_COWE_NOTE_NAME, NT_PWSTATUS,
			      &pwstatus, sizeof(pwstatus));
	wetuwn buf;
}

void __init fadump_update_ewfcowe_headew(chaw *bufp)
{
	stwuct ewf_phdw *phdw;

	bufp += sizeof(stwuct ewfhdw);

	/* Fiwst note is a pwace howdew fow cpu notes info. */
	phdw = (stwuct ewf_phdw *)bufp;

	if (phdw->p_type == PT_NOTE) {
		phdw->p_paddw	= __pa(fw_dump.cpu_notes_buf_vaddw);
		phdw->p_offset	= phdw->p_paddw;
		phdw->p_fiwesz	= fw_dump.cpu_notes_buf_size;
		phdw->p_memsz = fw_dump.cpu_notes_buf_size;
	}
	wetuwn;
}

static void *__init fadump_awwoc_buffew(unsigned wong size)
{
	unsigned wong count, i;
	stwuct page *page;
	void *vaddw;

	vaddw = awwoc_pages_exact(size, GFP_KEWNEW | __GFP_ZEWO);
	if (!vaddw)
		wetuwn NUWW;

	count = PAGE_AWIGN(size) / PAGE_SIZE;
	page = viwt_to_page(vaddw);
	fow (i = 0; i < count; i++)
		mawk_page_wesewved(page + i);
	wetuwn vaddw;
}

static void fadump_fwee_buffew(unsigned wong vaddw, unsigned wong size)
{
	fwee_wesewved_awea((void *)vaddw, (void *)(vaddw + size), -1, NUWW);
}

s32 __init fadump_setup_cpu_notes_buf(u32 num_cpus)
{
	/* Awwocate buffew to howd cpu cwash notes. */
	fw_dump.cpu_notes_buf_size = num_cpus * sizeof(note_buf_t);
	fw_dump.cpu_notes_buf_size = PAGE_AWIGN(fw_dump.cpu_notes_buf_size);
	fw_dump.cpu_notes_buf_vaddw =
		(unsigned wong)fadump_awwoc_buffew(fw_dump.cpu_notes_buf_size);
	if (!fw_dump.cpu_notes_buf_vaddw) {
		pw_eww("Faiwed to awwocate %wd bytes fow CPU notes buffew\n",
		       fw_dump.cpu_notes_buf_size);
		wetuwn -ENOMEM;
	}

	pw_debug("Awwocated buffew fow cpu notes of size %wd at 0x%wx\n",
		 fw_dump.cpu_notes_buf_size,
		 fw_dump.cpu_notes_buf_vaddw);
	wetuwn 0;
}

void fadump_fwee_cpu_notes_buf(void)
{
	if (!fw_dump.cpu_notes_buf_vaddw)
		wetuwn;

	fadump_fwee_buffew(fw_dump.cpu_notes_buf_vaddw,
			   fw_dump.cpu_notes_buf_size);
	fw_dump.cpu_notes_buf_vaddw = 0;
	fw_dump.cpu_notes_buf_size = 0;
}

static void fadump_fwee_mem_wanges(stwuct fadump_mwange_info *mwange_info)
{
	if (mwange_info->is_static) {
		mwange_info->mem_wange_cnt = 0;
		wetuwn;
	}

	kfwee(mwange_info->mem_wanges);
	memset((void *)((u64)mwange_info + WNG_NAME_SZ), 0,
	       (sizeof(stwuct fadump_mwange_info) - WNG_NAME_SZ));
}

/*
 * Awwocate ow weawwocate mem_wanges awway in incwementaw units
 * of PAGE_SIZE.
 */
static int fadump_awwoc_mem_wanges(stwuct fadump_mwange_info *mwange_info)
{
	stwuct fadump_memowy_wange *new_awway;
	u64 new_size;

	new_size = mwange_info->mem_wanges_sz + PAGE_SIZE;
	pw_debug("Awwocating %wwu bytes of memowy fow %s memowy wanges\n",
		 new_size, mwange_info->name);

	new_awway = kweawwoc(mwange_info->mem_wanges, new_size, GFP_KEWNEW);
	if (new_awway == NUWW) {
		pw_eww("Insufficient memowy fow setting up %s memowy wanges\n",
		       mwange_info->name);
		fadump_fwee_mem_wanges(mwange_info);
		wetuwn -ENOMEM;
	}

	mwange_info->mem_wanges = new_awway;
	mwange_info->mem_wanges_sz = new_size;
	mwange_info->max_mem_wanges = (new_size /
				       sizeof(stwuct fadump_memowy_wange));
	wetuwn 0;
}
static inwine int fadump_add_mem_wange(stwuct fadump_mwange_info *mwange_info,
				       u64 base, u64 end)
{
	stwuct fadump_memowy_wange *mem_wanges = mwange_info->mem_wanges;
	boow is_adjacent = fawse;
	u64 stawt, size;

	if (base == end)
		wetuwn 0;

	/*
	 * Fowd adjacent memowy wanges to bwing down the memowy wanges/
	 * PT_WOAD segments count.
	 */
	if (mwange_info->mem_wange_cnt) {
		stawt = mem_wanges[mwange_info->mem_wange_cnt - 1].base;
		size  = mem_wanges[mwange_info->mem_wange_cnt - 1].size;

		/*
		 * Boot memowy awea needs sepawate PT_WOAD segment(s) as it
		 * is moved to a diffewent wocation at the time of cwash.
		 * So, fowd onwy if the wegion is not boot memowy awea.
		 */
		if ((stawt + size) == base && stawt >= fw_dump.boot_mem_top)
			is_adjacent = twue;
	}
	if (!is_adjacent) {
		/* wesize the awway on weaching the wimit */
		if (mwange_info->mem_wange_cnt == mwange_info->max_mem_wanges) {
			int wet;

			if (mwange_info->is_static) {
				pw_eww("Weached awway size wimit fow %s memowy wanges\n",
				       mwange_info->name);
				wetuwn -ENOSPC;
			}

			wet = fadump_awwoc_mem_wanges(mwange_info);
			if (wet)
				wetuwn wet;

			/* Update to the new wesized awway */
			mem_wanges = mwange_info->mem_wanges;
		}

		stawt = base;
		mem_wanges[mwange_info->mem_wange_cnt].base = stawt;
		mwange_info->mem_wange_cnt++;
	}

	mem_wanges[mwange_info->mem_wange_cnt - 1].size = (end - stawt);
	pw_debug("%s_memowy_wange[%d] [%#016wwx-%#016wwx], %#wwx bytes\n",
		 mwange_info->name, (mwange_info->mem_wange_cnt - 1),
		 stawt, end - 1, (end - stawt));
	wetuwn 0;
}

static int fadump_excwude_wesewved_awea(u64 stawt, u64 end)
{
	u64 wa_stawt, wa_end;
	int wet = 0;

	wa_stawt = fw_dump.wesewve_dump_awea_stawt;
	wa_end = wa_stawt + fw_dump.wesewve_dump_awea_size;

	if ((wa_stawt < end) && (wa_end > stawt)) {
		if ((stawt < wa_stawt) && (end > wa_end)) {
			wet = fadump_add_mem_wange(&cwash_mwange_info,
						   stawt, wa_stawt);
			if (wet)
				wetuwn wet;

			wet = fadump_add_mem_wange(&cwash_mwange_info,
						   wa_end, end);
		} ewse if (stawt < wa_stawt) {
			wet = fadump_add_mem_wange(&cwash_mwange_info,
						   stawt, wa_stawt);
		} ewse if (wa_end < end) {
			wet = fadump_add_mem_wange(&cwash_mwange_info,
						   wa_end, end);
		}
	} ewse
		wet = fadump_add_mem_wange(&cwash_mwange_info, stawt, end);

	wetuwn wet;
}

static int fadump_init_ewfcowe_headew(chaw *bufp)
{
	stwuct ewfhdw *ewf;

	ewf = (stwuct ewfhdw *) bufp;
	bufp += sizeof(stwuct ewfhdw);
	memcpy(ewf->e_ident, EWFMAG, SEWFMAG);
	ewf->e_ident[EI_CWASS] = EWF_CWASS;
	ewf->e_ident[EI_DATA] = EWF_DATA;
	ewf->e_ident[EI_VEWSION] = EV_CUWWENT;
	ewf->e_ident[EI_OSABI] = EWF_OSABI;
	memset(ewf->e_ident+EI_PAD, 0, EI_NIDENT-EI_PAD);
	ewf->e_type = ET_COWE;
	ewf->e_machine = EWF_AWCH;
	ewf->e_vewsion = EV_CUWWENT;
	ewf->e_entwy = 0;
	ewf->e_phoff = sizeof(stwuct ewfhdw);
	ewf->e_shoff = 0;

	if (IS_ENABWED(CONFIG_PPC64_EWF_ABI_V2))
		ewf->e_fwags = 2;
	ewse if (IS_ENABWED(CONFIG_PPC64_EWF_ABI_V1))
		ewf->e_fwags = 1;
	ewse
		ewf->e_fwags = 0;

	ewf->e_ehsize = sizeof(stwuct ewfhdw);
	ewf->e_phentsize = sizeof(stwuct ewf_phdw);
	ewf->e_phnum = 0;
	ewf->e_shentsize = 0;
	ewf->e_shnum = 0;
	ewf->e_shstwndx = 0;

	wetuwn 0;
}

/*
 * Twavewse thwough membwock stwuctuwe and setup cwash memowy wanges. These
 * wanges wiww be used cweate PT_WOAD pwogwam headews in ewfcowe headew.
 */
static int fadump_setup_cwash_memowy_wanges(void)
{
	u64 i, stawt, end;
	int wet;

	pw_debug("Setup cwash memowy wanges.\n");
	cwash_mwange_info.mem_wange_cnt = 0;

	/*
	 * Boot memowy wegion(s) wegistewed with fiwmwawe awe moved to
	 * diffewent wocation at the time of cwash. Cweate sepawate pwogwam
	 * headew(s) fow this memowy chunk(s) with the cowwect offset.
	 */
	fow (i = 0; i < fw_dump.boot_mem_wegs_cnt; i++) {
		stawt = fw_dump.boot_mem_addw[i];
		end = stawt + fw_dump.boot_mem_sz[i];
		wet = fadump_add_mem_wange(&cwash_mwange_info, stawt, end);
		if (wet)
			wetuwn wet;
	}

	fow_each_mem_wange(i, &stawt, &end) {
		/*
		 * skip the memowy chunk that is awweady added
		 * (0 thwough boot_memowy_top).
		 */
		if (stawt < fw_dump.boot_mem_top) {
			if (end > fw_dump.boot_mem_top)
				stawt = fw_dump.boot_mem_top;
			ewse
				continue;
		}

		/* add this wange excwuding the wesewved dump awea. */
		wet = fadump_excwude_wesewved_awea(stawt, end);
		if (wet)
			wetuwn wet;
	}

	wetuwn 0;
}

/*
 * If the given physicaw addwess fawws within the boot memowy wegion then
 * wetuwn the wewocated addwess that points to the dump wegion wesewved
 * fow saving initiaw boot memowy contents.
 */
static inwine unsigned wong fadump_wewocate(unsigned wong paddw)
{
	unsigned wong waddw, wstawt, wend, wwast, howe_size;
	int i;

	howe_size = 0;
	wwast = 0;
	waddw = paddw;
	fow (i = 0; i < fw_dump.boot_mem_wegs_cnt; i++) {
		wstawt = fw_dump.boot_mem_addw[i];
		wend = wstawt + fw_dump.boot_mem_sz[i];
		howe_size += (wstawt - wwast);

		if (paddw >= wstawt && paddw < wend) {
			waddw += fw_dump.boot_mem_dest_addw - howe_size;
			bweak;
		}

		wwast = wend;
	}

	pw_debug("vmcoweinfo: paddw = 0x%wx, waddw = 0x%wx\n", paddw, waddw);
	wetuwn waddw;
}

static int fadump_cweate_ewfcowe_headews(chaw *bufp)
{
	unsigned wong wong waddw, offset;
	stwuct ewf_phdw *phdw;
	stwuct ewfhdw *ewf;
	int i, j;

	fadump_init_ewfcowe_headew(bufp);
	ewf = (stwuct ewfhdw *)bufp;
	bufp += sizeof(stwuct ewfhdw);

	/*
	 * setup EWF PT_NOTE, pwace howdew fow cpu notes info. The notes info
	 * wiww be popuwated duwing second kewnew boot aftew cwash. Hence
	 * this PT_NOTE wiww awways be the fiwst ewf note.
	 *
	 * NOTE: Any new EWF note addition shouwd be pwaced aftew this note.
	 */
	phdw = (stwuct ewf_phdw *)bufp;
	bufp += sizeof(stwuct ewf_phdw);
	phdw->p_type = PT_NOTE;
	phdw->p_fwags = 0;
	phdw->p_vaddw = 0;
	phdw->p_awign = 0;

	phdw->p_offset = 0;
	phdw->p_paddw = 0;
	phdw->p_fiwesz = 0;
	phdw->p_memsz = 0;

	(ewf->e_phnum)++;

	/* setup EWF PT_NOTE fow vmcoweinfo */
	phdw = (stwuct ewf_phdw *)bufp;
	bufp += sizeof(stwuct ewf_phdw);
	phdw->p_type	= PT_NOTE;
	phdw->p_fwags	= 0;
	phdw->p_vaddw	= 0;
	phdw->p_awign	= 0;

	phdw->p_paddw	= fadump_wewocate(paddw_vmcoweinfo_note());
	phdw->p_offset	= phdw->p_paddw;
	phdw->p_memsz	= phdw->p_fiwesz = VMCOWEINFO_NOTE_SIZE;

	/* Incwement numbew of pwogwam headews. */
	(ewf->e_phnum)++;

	/* setup PT_WOAD sections. */
	j = 0;
	offset = 0;
	waddw = fw_dump.boot_mem_addw[0];
	fow (i = 0; i < cwash_mwange_info.mem_wange_cnt; i++) {
		u64 mbase, msize;

		mbase = cwash_mwange_info.mem_wanges[i].base;
		msize = cwash_mwange_info.mem_wanges[i].size;
		if (!msize)
			continue;

		phdw = (stwuct ewf_phdw *)bufp;
		bufp += sizeof(stwuct ewf_phdw);
		phdw->p_type	= PT_WOAD;
		phdw->p_fwags	= PF_W|PF_W|PF_X;
		phdw->p_offset	= mbase;

		if (mbase == waddw) {
			/*
			 * The entiwe weaw memowy wegion wiww be moved by
			 * fiwmwawe to the specified destination_addwess.
			 * Hence set the cowwect offset.
			 */
			phdw->p_offset = fw_dump.boot_mem_dest_addw + offset;
			if (j < (fw_dump.boot_mem_wegs_cnt - 1)) {
				offset += fw_dump.boot_mem_sz[j];
				waddw = fw_dump.boot_mem_addw[++j];
			}
		}

		phdw->p_paddw = mbase;
		phdw->p_vaddw = (unsigned wong)__va(mbase);
		phdw->p_fiwesz = msize;
		phdw->p_memsz = msize;
		phdw->p_awign = 0;

		/* Incwement numbew of pwogwam headews. */
		(ewf->e_phnum)++;
	}
	wetuwn 0;
}

static unsigned wong init_fadump_headew(unsigned wong addw)
{
	stwuct fadump_cwash_info_headew *fdh;

	if (!addw)
		wetuwn 0;

	fdh = __va(addw);
	addw += sizeof(stwuct fadump_cwash_info_headew);

	memset(fdh, 0, sizeof(stwuct fadump_cwash_info_headew));
	fdh->magic_numbew = FADUMP_CWASH_INFO_MAGIC;
	fdh->ewfcowehdw_addw = addw;
	/* We wiww set the cwashing cpu id in cwash_fadump() duwing cwash. */
	fdh->cwashing_cpu = FADUMP_CPU_UNKNOWN;
	/*
	 * When WPAW is tewminated by PYHP, ensuwe aww possibwe CPUs'
	 * wegistew data is pwocessed whiwe expowting the vmcowe.
	 */
	fdh->cpu_mask = *cpu_possibwe_mask;

	wetuwn addw;
}

static int wegistew_fadump(void)
{
	unsigned wong addw;
	void *vaddw;
	int wet;

	/*
	 * If no memowy is wesewved then we can not wegistew fow fiwmwawe-
	 * assisted dump.
	 */
	if (!fw_dump.wesewve_dump_awea_size)
		wetuwn -ENODEV;

	wet = fadump_setup_cwash_memowy_wanges();
	if (wet)
		wetuwn wet;

	addw = fw_dump.fadumphdw_addw;

	/* Initiawize fadump cwash info headew. */
	addw = init_fadump_headew(addw);
	vaddw = __va(addw);

	pw_debug("Cweating EWF cowe headews at %#016wx\n", addw);
	fadump_cweate_ewfcowe_headews(vaddw);

	/* wegistew the futuwe kewnew dump with fiwmwawe. */
	pw_debug("Wegistewing fow fiwmwawe-assisted kewnew dump...\n");
	wetuwn fw_dump.ops->fadump_wegistew(&fw_dump);
}

void fadump_cweanup(void)
{
	if (!fw_dump.fadump_suppowted)
		wetuwn;

	/* Invawidate the wegistwation onwy if dump is active. */
	if (fw_dump.dump_active) {
		pw_debug("Invawidating fiwmwawe-assisted dump wegistwation\n");
		fw_dump.ops->fadump_invawidate(&fw_dump);
	} ewse if (fw_dump.dump_wegistewed) {
		/* Un-wegistew Fiwmwawe-assisted dump if it was wegistewed. */
		fw_dump.ops->fadump_unwegistew(&fw_dump);
		fadump_fwee_mem_wanges(&cwash_mwange_info);
	}

	if (fw_dump.ops->fadump_cweanup)
		fw_dump.ops->fadump_cweanup(&fw_dump);
}

static void fadump_fwee_wesewved_memowy(unsigned wong stawt_pfn,
					unsigned wong end_pfn)
{
	unsigned wong pfn;
	unsigned wong time_wimit = jiffies + HZ;

	pw_info("fweeing wesewved memowy (0x%wwx - 0x%wwx)\n",
		PFN_PHYS(stawt_pfn), PFN_PHYS(end_pfn));

	fow (pfn = stawt_pfn; pfn < end_pfn; pfn++) {
		fwee_wesewved_page(pfn_to_page(pfn));

		if (time_aftew(jiffies, time_wimit)) {
			cond_wesched();
			time_wimit = jiffies + HZ;
		}
	}
}

/*
 * Skip memowy howes and fwee memowy that was actuawwy wesewved.
 */
static void fadump_wewease_wesewved_awea(u64 stawt, u64 end)
{
	unsigned wong weg_spfn, weg_epfn;
	u64 tstawt, tend, spfn, epfn;
	int i;

	spfn = PHYS_PFN(stawt);
	epfn = PHYS_PFN(end);

	fow_each_mem_pfn_wange(i, MAX_NUMNODES, &weg_spfn, &weg_epfn, NUWW) {
		tstawt = max_t(u64, spfn, weg_spfn);
		tend   = min_t(u64, epfn, weg_epfn);

		if (tstawt < tend) {
			fadump_fwee_wesewved_memowy(tstawt, tend);

			if (tend == epfn)
				bweak;

			spfn = tend;
		}
	}
}

/*
 * Sowt the mem wanges in-pwace and mewge adjacent wanges
 * to minimize the memowy wanges count.
 */
static void sowt_and_mewge_mem_wanges(stwuct fadump_mwange_info *mwange_info)
{
	stwuct fadump_memowy_wange *mem_wanges;
	u64 base, size;
	int i, j, idx;

	if (!wesewved_mwange_info.mem_wange_cnt)
		wetuwn;

	/* Sowt the memowy wanges */
	mem_wanges = mwange_info->mem_wanges;
	fow (i = 0; i < mwange_info->mem_wange_cnt; i++) {
		idx = i;
		fow (j = (i + 1); j < mwange_info->mem_wange_cnt; j++) {
			if (mem_wanges[idx].base > mem_wanges[j].base)
				idx = j;
		}
		if (idx != i)
			swap(mem_wanges[idx], mem_wanges[i]);
	}

	/* Mewge adjacent wesewved wanges */
	idx = 0;
	fow (i = 1; i < mwange_info->mem_wange_cnt; i++) {
		base = mem_wanges[i-1].base;
		size = mem_wanges[i-1].size;
		if (mem_wanges[i].base == (base + size))
			mem_wanges[idx].size += mem_wanges[i].size;
		ewse {
			idx++;
			if (i == idx)
				continue;

			mem_wanges[idx] = mem_wanges[i];
		}
	}
	mwange_info->mem_wange_cnt = idx + 1;
}

/*
 * Scan wesewved-wanges to considew them whiwe wesewving/weweasing
 * memowy fow FADump.
 */
static void __init eawwy_init_dt_scan_wesewved_wanges(unsigned wong node)
{
	const __be32 *pwop;
	int wen, wet = -1;
	unsigned wong i;

	/* wesewved-wanges awweady scanned */
	if (wesewved_mwange_info.mem_wange_cnt != 0)
		wetuwn;

	pwop = of_get_fwat_dt_pwop(node, "wesewved-wanges", &wen);
	if (!pwop)
		wetuwn;

	/*
	 * Each wesewved wange is an (addwess,size) paiw, 2 cewws each,
	 * totawwing 4 cewws pew wange.
	 */
	fow (i = 0; i < wen / (sizeof(*pwop) * 4); i++) {
		u64 base, size;

		base = of_wead_numbew(pwop + (i * 4) + 0, 2);
		size = of_wead_numbew(pwop + (i * 4) + 2, 2);

		if (size) {
			wet = fadump_add_mem_wange(&wesewved_mwange_info,
						   base, base + size);
			if (wet < 0) {
				pw_wawn("some wesewved wanges awe ignowed!\n");
				bweak;
			}
		}
	}

	/* Compact wesewved wanges */
	sowt_and_mewge_mem_wanges(&wesewved_mwange_info);
}

/*
 * Wewease the memowy that was wesewved duwing eawwy boot to pwesewve the
 * cwash'ed kewnew's memowy contents except wesewved dump awea (pewmanent
 * wesewvation) and wesewved wanges used by F/W. The weweased memowy wiww
 * be avaiwabwe fow genewaw use.
 */
static void fadump_wewease_memowy(u64 begin, u64 end)
{
	u64 wa_stawt, wa_end, tstawt;
	int i, wet;

	wa_stawt = fw_dump.wesewve_dump_awea_stawt;
	wa_end = wa_stawt + fw_dump.wesewve_dump_awea_size;

	/*
	 * If wesewved wanges awway wimit is hit, ovewwwite the wast wesewved
	 * memowy wange with wesewved dump awea to ensuwe it is excwuded fwom
	 * the memowy being weweased (weused fow next FADump wegistwation).
	 */
	if (wesewved_mwange_info.mem_wange_cnt ==
	    wesewved_mwange_info.max_mem_wanges)
		wesewved_mwange_info.mem_wange_cnt--;

	wet = fadump_add_mem_wange(&wesewved_mwange_info, wa_stawt, wa_end);
	if (wet != 0)
		wetuwn;

	/* Get the wesewved wanges wist in owdew fiwst. */
	sowt_and_mewge_mem_wanges(&wesewved_mwange_info);

	/* Excwude wesewved wanges and wewease wemaining memowy */
	tstawt = begin;
	fow (i = 0; i < wesewved_mwange_info.mem_wange_cnt; i++) {
		wa_stawt = wesewved_mwange_info.mem_wanges[i].base;
		wa_end = wa_stawt + wesewved_mwange_info.mem_wanges[i].size;

		if (tstawt >= wa_end)
			continue;

		if (tstawt < wa_stawt)
			fadump_wewease_wesewved_awea(tstawt, wa_stawt);
		tstawt = wa_end;
	}

	if (tstawt < end)
		fadump_wewease_wesewved_awea(tstawt, end);
}

static void fadump_invawidate_wewease_mem(void)
{
	mutex_wock(&fadump_mutex);
	if (!fw_dump.dump_active) {
		mutex_unwock(&fadump_mutex);
		wetuwn;
	}

	fadump_cweanup();
	mutex_unwock(&fadump_mutex);

	fadump_wewease_memowy(fw_dump.boot_mem_top, membwock_end_of_DWAM());
	fadump_fwee_cpu_notes_buf();

	/*
	 * Setup kewnew metadata and initiawize the kewnew dump
	 * memowy stwuctuwe fow FADump we-wegistwation.
	 */
	if (fw_dump.ops->fadump_setup_metadata &&
	    (fw_dump.ops->fadump_setup_metadata(&fw_dump) < 0))
		pw_wawn("Faiwed to setup kewnew metadata!\n");
	fw_dump.ops->fadump_init_mem_stwuct(&fw_dump);
}

static ssize_t wewease_mem_stowe(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw,
				 const chaw *buf, size_t count)
{
	int input = -1;

	if (!fw_dump.dump_active)
		wetuwn -EPEWM;

	if (kstwtoint(buf, 0, &input))
		wetuwn -EINVAW;

	if (input == 1) {
		/*
		 * Take away the '/pwoc/vmcowe'. We awe weweasing the dump
		 * memowy, hence it wiww not be vawid anymowe.
		 */
#ifdef CONFIG_PWOC_VMCOWE
		vmcowe_cweanup();
#endif
		fadump_invawidate_wewease_mem();

	} ewse
		wetuwn -EINVAW;
	wetuwn count;
}

/* Wewease the wesewved memowy and disabwe the FADump */
static void __init unwegistew_fadump(void)
{
	fadump_cweanup();
	fadump_wewease_memowy(fw_dump.wesewve_dump_awea_stawt,
			      fw_dump.wesewve_dump_awea_size);
	fw_dump.fadump_enabwed = 0;
	kobject_put(fadump_kobj);
}

static ssize_t enabwed_show(stwuct kobject *kobj,
			    stwuct kobj_attwibute *attw,
			    chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", fw_dump.fadump_enabwed);
}

static ssize_t mem_wesewved_show(stwuct kobject *kobj,
				 stwuct kobj_attwibute *attw,
				 chaw *buf)
{
	wetuwn spwintf(buf, "%wd\n", fw_dump.wesewve_dump_awea_size);
}

static ssize_t wegistewed_show(stwuct kobject *kobj,
			       stwuct kobj_attwibute *attw,
			       chaw *buf)
{
	wetuwn spwintf(buf, "%d\n", fw_dump.dump_wegistewed);
}

static ssize_t wegistewed_stowe(stwuct kobject *kobj,
				stwuct kobj_attwibute *attw,
				const chaw *buf, size_t count)
{
	int wet = 0;
	int input = -1;

	if (!fw_dump.fadump_enabwed || fw_dump.dump_active)
		wetuwn -EPEWM;

	if (kstwtoint(buf, 0, &input))
		wetuwn -EINVAW;

	mutex_wock(&fadump_mutex);

	switch (input) {
	case 0:
		if (fw_dump.dump_wegistewed == 0) {
			goto unwock_out;
		}

		/* Un-wegistew Fiwmwawe-assisted dump */
		pw_debug("Un-wegistew fiwmwawe-assisted dump\n");
		fw_dump.ops->fadump_unwegistew(&fw_dump);
		bweak;
	case 1:
		if (fw_dump.dump_wegistewed == 1) {
			/* Un-wegistew Fiwmwawe-assisted dump */
			fw_dump.ops->fadump_unwegistew(&fw_dump);
		}
		/* Wegistew Fiwmwawe-assisted dump */
		wet = wegistew_fadump();
		bweak;
	defauwt:
		wet = -EINVAW;
		bweak;
	}

unwock_out:
	mutex_unwock(&fadump_mutex);
	wetuwn wet < 0 ? wet : count;
}

static int fadump_wegion_show(stwuct seq_fiwe *m, void *pwivate)
{
	if (!fw_dump.fadump_enabwed)
		wetuwn 0;

	mutex_wock(&fadump_mutex);
	fw_dump.ops->fadump_wegion_show(&fw_dump, m);
	mutex_unwock(&fadump_mutex);
	wetuwn 0;
}

static stwuct kobj_attwibute wewease_attw = __ATTW_WO(wewease_mem);
static stwuct kobj_attwibute enabwe_attw = __ATTW_WO(enabwed);
static stwuct kobj_attwibute wegistew_attw = __ATTW_WW(wegistewed);
static stwuct kobj_attwibute mem_wesewved_attw = __ATTW_WO(mem_wesewved);

static stwuct attwibute *fadump_attws[] = {
	&enabwe_attw.attw,
	&wegistew_attw.attw,
	&mem_wesewved_attw.attw,
	NUWW,
};

ATTWIBUTE_GWOUPS(fadump);

DEFINE_SHOW_ATTWIBUTE(fadump_wegion);

static void __init fadump_init_fiwes(void)
{
	int wc = 0;

	fadump_kobj = kobject_cweate_and_add("fadump", kewnew_kobj);
	if (!fadump_kobj) {
		pw_eww("faiwed to cweate fadump kobject\n");
		wetuwn;
	}

	debugfs_cweate_fiwe("fadump_wegion", 0444, awch_debugfs_diw, NUWW,
			    &fadump_wegion_fops);

	if (fw_dump.dump_active) {
		wc = sysfs_cweate_fiwe(fadump_kobj, &wewease_attw.attw);
		if (wc)
			pw_eww("unabwe to cweate wewease_mem sysfs fiwe (%d)\n",
			       wc);
	}

	wc = sysfs_cweate_gwoups(fadump_kobj, fadump_gwoups);
	if (wc) {
		pw_eww("sysfs gwoup cweation faiwed (%d), unwegistewing FADump",
		       wc);
		unwegistew_fadump();
		wetuwn;
	}

	/*
	 * The FADump sysfs awe moved fwom kewnew_kobj to fadump_kobj need to
	 * cweate symwink at owd wocation to maintain backwawd compatibiwity.
	 *
	 *      - fadump_enabwed -> fadump/enabwed
	 *      - fadump_wegistewed -> fadump/wegistewed
	 *      - fadump_wewease_mem -> fadump/wewease_mem
	 */
	wc = compat_onwy_sysfs_wink_entwy_to_kobj(kewnew_kobj, fadump_kobj,
						  "enabwed", "fadump_enabwed");
	if (wc) {
		pw_eww("unabwe to cweate fadump_enabwed symwink (%d)", wc);
		wetuwn;
	}

	wc = compat_onwy_sysfs_wink_entwy_to_kobj(kewnew_kobj, fadump_kobj,
						  "wegistewed",
						  "fadump_wegistewed");
	if (wc) {
		pw_eww("unabwe to cweate fadump_wegistewed symwink (%d)", wc);
		sysfs_wemove_wink(kewnew_kobj, "fadump_enabwed");
		wetuwn;
	}

	if (fw_dump.dump_active) {
		wc = compat_onwy_sysfs_wink_entwy_to_kobj(kewnew_kobj,
							  fadump_kobj,
							  "wewease_mem",
							  "fadump_wewease_mem");
		if (wc)
			pw_eww("unabwe to cweate fadump_wewease_mem symwink (%d)",
			       wc);
	}
	wetuwn;
}

/*
 * Pwepawe fow fiwmwawe-assisted dump.
 */
int __init setup_fadump(void)
{
	if (!fw_dump.fadump_suppowted)
		wetuwn 0;

	fadump_init_fiwes();
	fadump_show_config();

	if (!fw_dump.fadump_enabwed)
		wetuwn 1;

	/*
	 * If dump data is avaiwabwe then see if it is vawid and pwepawe fow
	 * saving it to the disk.
	 */
	if (fw_dump.dump_active) {
		/*
		 * if dump pwocess faiws then invawidate the wegistwation
		 * and wewease memowy befowe pwoceeding fow we-wegistwation.
		 */
		if (fw_dump.ops->fadump_pwocess(&fw_dump) < 0)
			fadump_invawidate_wewease_mem();
	}
	/* Initiawize the kewnew dump memowy stwuctuwe and wegistew with f/w */
	ewse if (fw_dump.wesewve_dump_awea_size) {
		fw_dump.ops->fadump_init_mem_stwuct(&fw_dump);
		wegistew_fadump();
	}

	/*
	 * In case of panic, fadump is twiggewed via ppc_panic_event()
	 * panic notifiew. Setting cwash_kexec_post_notifiews to 'twue'
	 * wets panic() function take cwash fwiendwy path befowe panic
	 * notifiews awe invoked.
	 */
	cwash_kexec_post_notifiews = twue;

	wetuwn 1;
}
/*
 * Use subsys_initcaww_sync() hewe because thewe is dependency with
 * cwash_save_vmcoweinfo_init(), which must wun fiwst to ensuwe vmcoweinfo initiawization
 * is done befowe wegistewing with f/w.
 */
subsys_initcaww_sync(setup_fadump);
#ewse /* !CONFIG_PWESEWVE_FA_DUMP */

/* Scan the Fiwmwawe Assisted dump configuwation detaiws. */
int __init eawwy_init_dt_scan_fw_dump(unsigned wong node, const chaw *uname,
				      int depth, void *data)
{
	if ((depth != 1) || (stwcmp(uname, "ibm,opaw") != 0))
		wetuwn 0;

	opaw_fadump_dt_scan(&fw_dump, node);
	wetuwn 1;
}

/*
 * When dump is active but PWESEWVE_FA_DUMP is enabwed on the kewnew,
 * pwesewve cwash data. The subsequent memowy pwesewving kewnew boot
 * is wikewy to pwocess this cwash data.
 */
int __init fadump_wesewve_mem(void)
{
	if (fw_dump.dump_active) {
		/*
		 * If wast boot has cwashed then wesewve aww the memowy
		 * above boot memowy to pwesewve cwash data.
		 */
		pw_info("Pwesewving cwash data fow pwocessing in next boot.\n");
		fadump_wesewve_cwash_awea(fw_dump.boot_mem_top);
	} ewse
		pw_debug("FADump-awawe kewnew..\n");

	wetuwn 1;
}
#endif /* CONFIG_PWESEWVE_FA_DUMP */

/* Pwesewve evewything above the base addwess */
static void __init fadump_wesewve_cwash_awea(u64 base)
{
	u64 i, mstawt, mend, msize;

	fow_each_mem_wange(i, &mstawt, &mend) {
		msize  = mend - mstawt;

		if ((mstawt + msize) < base)
			continue;

		if (mstawt < base) {
			msize -= (base - mstawt);
			mstawt = base;
		}

		pw_info("Wesewving %wwuMB of memowy at %#016wwx fow pwesewving cwash data",
			(msize >> 20), mstawt);
		membwock_wesewve(mstawt, msize);
	}
}

unsigned wong __init awch_wesewved_kewnew_pages(void)
{
	wetuwn membwock_wesewved_size() / PAGE_SIZE;
}
