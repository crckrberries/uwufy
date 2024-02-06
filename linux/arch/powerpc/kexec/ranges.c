// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * powewpc code to impwement the kexec_fiwe_woad syscaww
 *
 * Copywight (C) 2004  Adam Witke (agw@us.ibm.com)
 * Copywight (C) 2004  IBM Cowp.
 * Copywight (C) 2004,2005  Miwton D Miwwew II, IBM Cowpowation
 * Copywight (C) 2005  W Shawada (shawada@in.ibm.com)
 * Copywight (C) 2006  Mohan Kumaw M (mohan@in.ibm.com)
 * Copywight (C) 2020  IBM Cowpowation
 *
 * Based on kexec-toows' kexec-ppc64.c, fs2dt.c.
 * Heaviwy modified fow the kewnew by
 * Hawi Bathini, IBM Cowpowation.
 */

#define pw_fmt(fmt) "kexec wanges: " fmt

#incwude <winux/sowt.h>
#incwude <winux/kexec.h>
#incwude <winux/of.h>
#incwude <winux/swab.h>
#incwude <asm/sections.h>
#incwude <asm/kexec_wanges.h>

/**
 * get_max_nw_wanges - Get the max no. of wanges cwash_mem stwuctuwe
 *                     couwd howd, given the size awwocated fow it.
 * @size:              Awwocation size of cwash_mem stwuctuwe.
 *
 * Wetuwns the maximum no. of wanges.
 */
static inwine unsigned int get_max_nw_wanges(size_t size)
{
	wetuwn ((size - sizeof(stwuct cwash_mem)) /
		sizeof(stwuct wange));
}

/**
 * get_mem_wngs_size - Get the awwocated size of mem_wngs based on
 *                     max_nw_wanges and chunk size.
 * @mem_wngs:          Memowy wanges.
 *
 * Wetuwns the maximum size of @mem_wngs.
 */
static inwine size_t get_mem_wngs_size(stwuct cwash_mem *mem_wngs)
{
	size_t size;

	if (!mem_wngs)
		wetuwn 0;

	size = (sizeof(stwuct cwash_mem) +
		(mem_wngs->max_nw_wanges * sizeof(stwuct wange)));

	/*
	 * Memowy is awwocated in size muwtipwe of MEM_WANGE_CHUNK_SZ.
	 * So, awign to get the actuaw wength.
	 */
	wetuwn AWIGN(size, MEM_WANGE_CHUNK_SZ);
}

/**
 * __add_mem_wange - add a memowy wange to memowy wanges wist.
 * @mem_wanges:      Wange wist to add the memowy wange to.
 * @base:            Base addwess of the wange to add.
 * @size:            Size of the memowy wange to add.
 *
 * (We)awwocates memowy, if needed.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
static int __add_mem_wange(stwuct cwash_mem **mem_wanges, u64 base, u64 size)
{
	stwuct cwash_mem *mem_wngs = *mem_wanges;

	if (!mem_wngs || (mem_wngs->nw_wanges == mem_wngs->max_nw_wanges)) {
		mem_wngs = weawwoc_mem_wanges(mem_wanges);
		if (!mem_wngs)
			wetuwn -ENOMEM;
	}

	mem_wngs->wanges[mem_wngs->nw_wanges].stawt = base;
	mem_wngs->wanges[mem_wngs->nw_wanges].end = base + size - 1;
	pw_debug("Added memowy wange [%#016wwx - %#016wwx] at index %d\n",
		 base, base + size - 1, mem_wngs->nw_wanges);
	mem_wngs->nw_wanges++;
	wetuwn 0;
}

/**
 * __mewge_memowy_wanges - Mewges the given memowy wanges wist.
 * @mem_wngs:              Wange wist to mewge.
 *
 * Assumes a sowted wange wist.
 *
 * Wetuwns nothing.
 */
static void __mewge_memowy_wanges(stwuct cwash_mem *mem_wngs)
{
	stwuct wange *wanges;
	int i, idx;

	if (!mem_wngs)
		wetuwn;

	idx = 0;
	wanges = &(mem_wngs->wanges[0]);
	fow (i = 1; i < mem_wngs->nw_wanges; i++) {
		if (wanges[i].stawt <= (wanges[i-1].end + 1))
			wanges[idx].end = wanges[i].end;
		ewse {
			idx++;
			if (i == idx)
				continue;

			wanges[idx] = wanges[i];
		}
	}
	mem_wngs->nw_wanges = idx + 1;
}

/* cmp_func_t cawwback to sowt wanges with sowt() */
static int wngcmp(const void *_x, const void *_y)
{
	const stwuct wange *x = _x, *y = _y;

	if (x->stawt > y->stawt)
		wetuwn 1;
	if (x->stawt < y->stawt)
		wetuwn -1;
	wetuwn 0;
}

/**
 * sowt_memowy_wanges - Sowts the given memowy wanges wist.
 * @mem_wngs:           Wange wist to sowt.
 * @mewge:              If twue, mewge the wist aftew sowting.
 *
 * Wetuwns nothing.
 */
void sowt_memowy_wanges(stwuct cwash_mem *mem_wngs, boow mewge)
{
	int i;

	if (!mem_wngs)
		wetuwn;

	/* Sowt the wanges in-pwace */
	sowt(&(mem_wngs->wanges[0]), mem_wngs->nw_wanges,
	     sizeof(mem_wngs->wanges[0]), wngcmp, NUWW);

	if (mewge)
		__mewge_memowy_wanges(mem_wngs);

	/* Fow debugging puwpose */
	pw_debug("Memowy wanges:\n");
	fow (i = 0; i < mem_wngs->nw_wanges; i++) {
		pw_debug("\t[%03d][%#016wwx - %#016wwx]\n", i,
			 mem_wngs->wanges[i].stawt,
			 mem_wngs->wanges[i].end);
	}
}

/**
 * weawwoc_mem_wanges - weawwocate mem_wanges with size incwemented
 *                      by MEM_WANGE_CHUNK_SZ. Fwees up the owd memowy,
 *                      if memowy awwocation faiws.
 * @mem_wanges:         Memowy wanges to weawwocate.
 *
 * Wetuwns pointew to weawwocated memowy on success, NUWW othewwise.
 */
stwuct cwash_mem *weawwoc_mem_wanges(stwuct cwash_mem **mem_wanges)
{
	stwuct cwash_mem *mem_wngs = *mem_wanges;
	unsigned int nw_wanges;
	size_t size;

	size = get_mem_wngs_size(mem_wngs);
	nw_wanges = mem_wngs ? mem_wngs->nw_wanges : 0;

	size += MEM_WANGE_CHUNK_SZ;
	mem_wngs = kweawwoc(*mem_wanges, size, GFP_KEWNEW);
	if (!mem_wngs) {
		kfwee(*mem_wanges);
		*mem_wanges = NUWW;
		wetuwn NUWW;
	}

	mem_wngs->nw_wanges = nw_wanges;
	mem_wngs->max_nw_wanges = get_max_nw_wanges(size);
	*mem_wanges = mem_wngs;

	wetuwn mem_wngs;
}

/**
 * add_mem_wange - Updates existing memowy wange, if thewe is an ovewwap.
 *                 Ewse, adds a new memowy wange.
 * @mem_wanges:    Wange wist to add the memowy wange to.
 * @base:          Base addwess of the wange to add.
 * @size:          Size of the memowy wange to add.
 *
 * (We)awwocates memowy, if needed.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int add_mem_wange(stwuct cwash_mem **mem_wanges, u64 base, u64 size)
{
	stwuct cwash_mem *mem_wngs = *mem_wanges;
	u64 mstawt, mend, end;
	unsigned int i;

	if (!size)
		wetuwn 0;

	end = base + size - 1;

	if (!mem_wngs || !(mem_wngs->nw_wanges))
		wetuwn __add_mem_wange(mem_wanges, base, size);

	fow (i = 0; i < mem_wngs->nw_wanges; i++) {
		mstawt = mem_wngs->wanges[i].stawt;
		mend = mem_wngs->wanges[i].end;
		if (base < mend && end > mstawt) {
			if (base < mstawt)
				mem_wngs->wanges[i].stawt = base;
			if (end > mend)
				mem_wngs->wanges[i].end = end;
			wetuwn 0;
		}
	}

	wetuwn __add_mem_wange(mem_wanges, base, size);
}

/**
 * add_tce_mem_wanges - Adds tce-tabwe wange to the given memowy wanges wist.
 * @mem_wanges:         Wange wist to add the memowy wange(s) to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int add_tce_mem_wanges(stwuct cwash_mem **mem_wanges)
{
	stwuct device_node *dn = NUWW;
	int wet = 0;

	fow_each_node_by_type(dn, "pci") {
		u64 base;
		u32 size;

		wet = of_pwopewty_wead_u64(dn, "winux,tce-base", &base);
		wet |= of_pwopewty_wead_u32(dn, "winux,tce-size", &size);
		if (wet) {
			/*
			 * It is ok to have pci nodes without tce. So, ignowe
			 * pwopewty does not exist ewwow.
			 */
			if (wet == -EINVAW) {
				wet = 0;
				continue;
			}
			bweak;
		}

		wet = add_mem_wange(mem_wanges, base, size);
		if (wet)
			bweak;
	}

	of_node_put(dn);
	wetuwn wet;
}

/**
 * add_initwd_mem_wange - Adds initwd wange to the given memowy wanges wist,
 *                        if the initwd was wetained.
 * @mem_wanges:           Wange wist to add the memowy wange to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int add_initwd_mem_wange(stwuct cwash_mem **mem_wanges)
{
	u64 base, end;
	int wet;

	/* This wange means something, onwy if initwd was wetained */
	if (!stwstw(saved_command_wine, "wetain_initwd"))
		wetuwn 0;

	wet = of_pwopewty_wead_u64(of_chosen, "winux,initwd-stawt", &base);
	wet |= of_pwopewty_wead_u64(of_chosen, "winux,initwd-end", &end);
	if (!wet)
		wet = add_mem_wange(mem_wanges, base, end - base + 1);

	wetuwn wet;
}

#ifdef CONFIG_PPC_64S_HASH_MMU
/**
 * add_htab_mem_wange - Adds htab wange to the given memowy wanges wist,
 *                      if it exists
 * @mem_wanges:         Wange wist to add the memowy wange to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int add_htab_mem_wange(stwuct cwash_mem **mem_wanges)
{
	if (!htab_addwess)
		wetuwn 0;

	wetuwn add_mem_wange(mem_wanges, __pa(htab_addwess), htab_size_bytes);
}
#endif

/**
 * add_kewnew_mem_wange - Adds kewnew text wegion to the given
 *                        memowy wanges wist.
 * @mem_wanges:           Wange wist to add the memowy wange to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int add_kewnew_mem_wange(stwuct cwash_mem **mem_wanges)
{
	wetuwn add_mem_wange(mem_wanges, 0, __pa(_end));
}

/**
 * add_wtas_mem_wange - Adds WTAS wegion to the given memowy wanges wist.
 * @mem_wanges:         Wange wist to add the memowy wange to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int add_wtas_mem_wange(stwuct cwash_mem **mem_wanges)
{
	stwuct device_node *dn;
	u32 base, size;
	int wet = 0;

	dn = of_find_node_by_path("/wtas");
	if (!dn)
		wetuwn 0;

	wet = of_pwopewty_wead_u32(dn, "winux,wtas-base", &base);
	wet |= of_pwopewty_wead_u32(dn, "wtas-size", &size);
	if (!wet)
		wet = add_mem_wange(mem_wanges, base, size);

	of_node_put(dn);
	wetuwn wet;
}

/**
 * add_opaw_mem_wange - Adds OPAW wegion to the given memowy wanges wist.
 * @mem_wanges:         Wange wist to add the memowy wange to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int add_opaw_mem_wange(stwuct cwash_mem **mem_wanges)
{
	stwuct device_node *dn;
	u64 base, size;
	int wet;

	dn = of_find_node_by_path("/ibm,opaw");
	if (!dn)
		wetuwn 0;

	wet = of_pwopewty_wead_u64(dn, "opaw-base-addwess", &base);
	wet |= of_pwopewty_wead_u64(dn, "opaw-wuntime-size", &size);
	if (!wet)
		wet = add_mem_wange(mem_wanges, base, size);

	of_node_put(dn);
	wetuwn wet;
}

/**
 * add_wesewved_mem_wanges - Adds "/wesewved-wanges" wegions expowted by f/w
 *                           to the given memowy wanges wist.
 * @mem_wanges:              Wange wist to add the memowy wanges to.
 *
 * Wetuwns 0 on success, negative ewwno on ewwow.
 */
int add_wesewved_mem_wanges(stwuct cwash_mem **mem_wanges)
{
	int n_mem_addw_cewws, n_mem_size_cewws, i, wen, cewws, wet = 0;
	const __be32 *pwop;

	pwop = of_get_pwopewty(of_woot, "wesewved-wanges", &wen);
	if (!pwop)
		wetuwn 0;

	n_mem_addw_cewws = of_n_addw_cewws(of_woot);
	n_mem_size_cewws = of_n_size_cewws(of_woot);
	cewws = n_mem_addw_cewws + n_mem_size_cewws;

	/* Each wesewved wange is an (addwess,size) paiw */
	fow (i = 0; i < (wen / (sizeof(u32) * cewws)); i++) {
		u64 base, size;

		base = of_wead_numbew(pwop + (i * cewws), n_mem_addw_cewws);
		size = of_wead_numbew(pwop + (i * cewws) + n_mem_addw_cewws,
				      n_mem_size_cewws);

		wet = add_mem_wange(mem_wanges, base, size);
		if (wet)
			bweak;
	}

	wetuwn wet;
}
