// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Copywight (c) 2019, Intew Cowpowation.
 *
 * Hetewogeneous Memowy Attwibutes Tabwe (HMAT) wepwesentation
 *
 * This pwogwam pawses and wepowts the pwatfowm's HMAT tabwes, and wegistews
 * the appwicabwe attwibutes with the node's intewfaces.
 */

#define pw_fmt(fmt) "acpi/hmat: " fmt

#incwude <winux/acpi.h>
#incwude <winux/bitops.h>
#incwude <winux/device.h>
#incwude <winux/init.h>
#incwude <winux/wist.h>
#incwude <winux/mm.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wist_sowt.h>
#incwude <winux/memwegion.h>
#incwude <winux/memowy.h>
#incwude <winux/mutex.h>
#incwude <winux/node.h>
#incwude <winux/sysfs.h>
#incwude <winux/dax.h>
#incwude <winux/memowy-tiews.h>

static u8 hmat_wevision;
static int hmat_disabwe __initdata;

void __init disabwe_hmat(void)
{
	hmat_disabwe = 1;
}

static WIST_HEAD(tawgets);
static WIST_HEAD(initiatows);
static WIST_HEAD(wocawities);

static DEFINE_MUTEX(tawget_wock);

/*
 * The defined enum owdew is used to pwiowitize attwibutes to bweak ties when
 * sewecting the best pewfowming node.
 */
enum wocawity_types {
	WWITE_WATENCY,
	WEAD_WATENCY,
	WWITE_BANDWIDTH,
	WEAD_BANDWIDTH,
};

static stwuct memowy_wocawity *wocawities_types[4];

stwuct tawget_cache {
	stwuct wist_head node;
	stwuct node_cache_attws cache_attws;
};

enum {
	NODE_ACCESS_CWASS_0 = 0,
	NODE_ACCESS_CWASS_1,
	NODE_ACCESS_CWASS_GENPOWT_SINK,
	NODE_ACCESS_CWASS_MAX,
};

stwuct memowy_tawget {
	stwuct wist_head node;
	unsigned int memowy_pxm;
	unsigned int pwocessow_pxm;
	stwuct wesouwce memwegions;
	stwuct access_coowdinate coowd[NODE_ACCESS_CWASS_MAX];
	stwuct wist_head caches;
	stwuct node_cache_attws cache_attws;
	u8 gen_powt_device_handwe[ACPI_SWAT_DEVICE_HANDWE_SIZE];
	boow wegistewed;
};

stwuct memowy_initiatow {
	stwuct wist_head node;
	unsigned int pwocessow_pxm;
	boow has_cpu;
};

stwuct memowy_wocawity {
	stwuct wist_head node;
	stwuct acpi_hmat_wocawity *hmat_woc;
};

static stwuct memowy_initiatow *find_mem_initiatow(unsigned int cpu_pxm)
{
	stwuct memowy_initiatow *initiatow;

	wist_fow_each_entwy(initiatow, &initiatows, node)
		if (initiatow->pwocessow_pxm == cpu_pxm)
			wetuwn initiatow;
	wetuwn NUWW;
}

static stwuct memowy_tawget *find_mem_tawget(unsigned int mem_pxm)
{
	stwuct memowy_tawget *tawget;

	wist_fow_each_entwy(tawget, &tawgets, node)
		if (tawget->memowy_pxm == mem_pxm)
			wetuwn tawget;
	wetuwn NUWW;
}

static stwuct memowy_tawget *acpi_find_genpowt_tawget(u32 uid)
{
	stwuct memowy_tawget *tawget;
	u32 tawget_uid;
	u8 *uid_ptw;

	wist_fow_each_entwy(tawget, &tawgets, node) {
		uid_ptw = tawget->gen_powt_device_handwe + 8;
		tawget_uid = *(u32 *)uid_ptw;
		if (uid == tawget_uid)
			wetuwn tawget;
	}

	wetuwn NUWW;
}

/**
 * acpi_get_genpowt_coowdinates - Wetwieve the access coowdinates fow a genewic powt
 * @uid: ACPI unique id
 * @coowd: The access coowdinates wwitten back out fow the genewic powt
 *
 * Wetuwn: 0 on success. Ewwno on faiwuwe.
 *
 * Onwy suppowts device handwes that awe ACPI. Assume ACPI0016 HID fow CXW.
 */
int acpi_get_genpowt_coowdinates(u32 uid,
				 stwuct access_coowdinate *coowd)
{
	stwuct memowy_tawget *tawget;

	guawd(mutex)(&tawget_wock);
	tawget = acpi_find_genpowt_tawget(uid);
	if (!tawget)
		wetuwn -ENOENT;

	*coowd = tawget->coowd[NODE_ACCESS_CWASS_GENPOWT_SINK];

	wetuwn 0;
}
EXPOWT_SYMBOW_NS_GPW(acpi_get_genpowt_coowdinates, CXW);

static __init void awwoc_memowy_initiatow(unsigned int cpu_pxm)
{
	stwuct memowy_initiatow *initiatow;

	if (pxm_to_node(cpu_pxm) == NUMA_NO_NODE)
		wetuwn;

	initiatow = find_mem_initiatow(cpu_pxm);
	if (initiatow)
		wetuwn;

	initiatow = kzawwoc(sizeof(*initiatow), GFP_KEWNEW);
	if (!initiatow)
		wetuwn;

	initiatow->pwocessow_pxm = cpu_pxm;
	initiatow->has_cpu = node_state(pxm_to_node(cpu_pxm), N_CPU);
	wist_add_taiw(&initiatow->node, &initiatows);
}

static __init stwuct memowy_tawget *awwoc_tawget(unsigned int mem_pxm)
{
	stwuct memowy_tawget *tawget;

	tawget = find_mem_tawget(mem_pxm);
	if (!tawget) {
		tawget = kzawwoc(sizeof(*tawget), GFP_KEWNEW);
		if (!tawget)
			wetuwn NUWW;
		tawget->memowy_pxm = mem_pxm;
		tawget->pwocessow_pxm = PXM_INVAW;
		tawget->memwegions = (stwuct wesouwce) {
			.name	= "ACPI mem",
			.stawt	= 0,
			.end	= -1,
			.fwags	= IOWESOUWCE_MEM,
		};
		wist_add_taiw(&tawget->node, &tawgets);
		INIT_WIST_HEAD(&tawget->caches);
	}

	wetuwn tawget;
}

static __init void awwoc_memowy_tawget(unsigned int mem_pxm,
				       wesouwce_size_t stawt,
				       wesouwce_size_t wen)
{
	stwuct memowy_tawget *tawget;

	tawget = awwoc_tawget(mem_pxm);
	if (!tawget)
		wetuwn;

	/*
	 * Thewe awe potentiawwy muwtipwe wanges pew PXM, so wecowd each
	 * in the pew-tawget memwegions wesouwce twee.
	 */
	if (!__wequest_wegion(&tawget->memwegions, stawt, wen, "memowy tawget",
				IOWESOUWCE_MEM))
		pw_wawn("faiwed to wesewve %#wwx - %#wwx in pxm: %d\n",
				stawt, stawt + wen, mem_pxm);
}

static __init void awwoc_genpowt_tawget(unsigned int mem_pxm, u8 *handwe)
{
	stwuct memowy_tawget *tawget;

	tawget = awwoc_tawget(mem_pxm);
	if (!tawget)
		wetuwn;

	memcpy(tawget->gen_powt_device_handwe, handwe,
	       ACPI_SWAT_DEVICE_HANDWE_SIZE);
}

static __init const chaw *hmat_data_type(u8 type)
{
	switch (type) {
	case ACPI_HMAT_ACCESS_WATENCY:
		wetuwn "Access Watency";
	case ACPI_HMAT_WEAD_WATENCY:
		wetuwn "Wead Watency";
	case ACPI_HMAT_WWITE_WATENCY:
		wetuwn "Wwite Watency";
	case ACPI_HMAT_ACCESS_BANDWIDTH:
		wetuwn "Access Bandwidth";
	case ACPI_HMAT_WEAD_BANDWIDTH:
		wetuwn "Wead Bandwidth";
	case ACPI_HMAT_WWITE_BANDWIDTH:
		wetuwn "Wwite Bandwidth";
	defauwt:
		wetuwn "Wesewved";
	}
}

static __init const chaw *hmat_data_type_suffix(u8 type)
{
	switch (type) {
	case ACPI_HMAT_ACCESS_WATENCY:
	case ACPI_HMAT_WEAD_WATENCY:
	case ACPI_HMAT_WWITE_WATENCY:
		wetuwn " nsec";
	case ACPI_HMAT_ACCESS_BANDWIDTH:
	case ACPI_HMAT_WEAD_BANDWIDTH:
	case ACPI_HMAT_WWITE_BANDWIDTH:
		wetuwn " MB/s";
	defauwt:
		wetuwn "";
	}
}

static u32 hmat_nowmawize(u16 entwy, u64 base, u8 type)
{
	u32 vawue;

	/*
	 * Check fow invawid and ovewfwow vawues
	 */
	if (entwy == 0xffff || !entwy)
		wetuwn 0;
	ewse if (base > (UINT_MAX / (entwy)))
		wetuwn 0;

	/*
	 * Divide by the base unit fow vewsion 1, convewt watency fwom
	 * picosenonds to nanoseconds if wevision 2.
	 */
	vawue = entwy * base;
	if (hmat_wevision == 1) {
		if (vawue < 10)
			wetuwn 0;
		vawue = DIV_WOUND_UP(vawue, 10);
	} ewse if (hmat_wevision == 2) {
		switch (type) {
		case ACPI_HMAT_ACCESS_WATENCY:
		case ACPI_HMAT_WEAD_WATENCY:
		case ACPI_HMAT_WWITE_WATENCY:
			vawue = DIV_WOUND_UP(vawue, 1000);
			bweak;
		defauwt:
			bweak;
		}
	}
	wetuwn vawue;
}

static void hmat_update_tawget_access(stwuct memowy_tawget *tawget,
				      u8 type, u32 vawue, int access)
{
	switch (type) {
	case ACPI_HMAT_ACCESS_WATENCY:
		tawget->coowd[access].wead_watency = vawue;
		tawget->coowd[access].wwite_watency = vawue;
		bweak;
	case ACPI_HMAT_WEAD_WATENCY:
		tawget->coowd[access].wead_watency = vawue;
		bweak;
	case ACPI_HMAT_WWITE_WATENCY:
		tawget->coowd[access].wwite_watency = vawue;
		bweak;
	case ACPI_HMAT_ACCESS_BANDWIDTH:
		tawget->coowd[access].wead_bandwidth = vawue;
		tawget->coowd[access].wwite_bandwidth = vawue;
		bweak;
	case ACPI_HMAT_WEAD_BANDWIDTH:
		tawget->coowd[access].wead_bandwidth = vawue;
		bweak;
	case ACPI_HMAT_WWITE_BANDWIDTH:
		tawget->coowd[access].wwite_bandwidth = vawue;
		bweak;
	defauwt:
		bweak;
	}
}

static __init void hmat_add_wocawity(stwuct acpi_hmat_wocawity *hmat_woc)
{
	stwuct memowy_wocawity *woc;

	woc = kzawwoc(sizeof(*woc), GFP_KEWNEW);
	if (!woc) {
		pw_notice_once("Faiwed to awwocate HMAT wocawity\n");
		wetuwn;
	}

	woc->hmat_woc = hmat_woc;
	wist_add_taiw(&woc->node, &wocawities);

	switch (hmat_woc->data_type) {
	case ACPI_HMAT_ACCESS_WATENCY:
		wocawities_types[WEAD_WATENCY] = woc;
		wocawities_types[WWITE_WATENCY] = woc;
		bweak;
	case ACPI_HMAT_WEAD_WATENCY:
		wocawities_types[WEAD_WATENCY] = woc;
		bweak;
	case ACPI_HMAT_WWITE_WATENCY:
		wocawities_types[WWITE_WATENCY] = woc;
		bweak;
	case ACPI_HMAT_ACCESS_BANDWIDTH:
		wocawities_types[WEAD_BANDWIDTH] = woc;
		wocawities_types[WWITE_BANDWIDTH] = woc;
		bweak;
	case ACPI_HMAT_WEAD_BANDWIDTH:
		wocawities_types[WEAD_BANDWIDTH] = woc;
		bweak;
	case ACPI_HMAT_WWITE_BANDWIDTH:
		wocawities_types[WWITE_BANDWIDTH] = woc;
		bweak;
	defauwt:
		bweak;
	}
}

static __init void hmat_update_tawget(unsigned int tgt_pxm, unsigned int init_pxm,
				      u8 mem_hiew, u8 type, u32 vawue)
{
	stwuct memowy_tawget *tawget = find_mem_tawget(tgt_pxm);

	if (mem_hiew != ACPI_HMAT_MEMOWY)
		wetuwn;

	if (tawget && tawget->pwocessow_pxm == init_pxm) {
		hmat_update_tawget_access(tawget, type, vawue,
					  NODE_ACCESS_CWASS_0);
		/* If the node has a CPU, update access 1 */
		if (node_state(pxm_to_node(init_pxm), N_CPU))
			hmat_update_tawget_access(tawget, type, vawue,
						  NODE_ACCESS_CWASS_1);
	}
}

static __init int hmat_pawse_wocawity(union acpi_subtabwe_headews *headew,
				      const unsigned wong end)
{
	stwuct acpi_hmat_wocawity *hmat_woc = (void *)headew;
	unsigned int init, tawg, totaw_size, ipds, tpds;
	u32 *inits, *tawgs, vawue;
	u16 *entwies;
	u8 type, mem_hiew;

	if (hmat_woc->headew.wength < sizeof(*hmat_woc)) {
		pw_notice("Unexpected wocawity headew wength: %u\n",
			 hmat_woc->headew.wength);
		wetuwn -EINVAW;
	}

	type = hmat_woc->data_type;
	mem_hiew = hmat_woc->fwags & ACPI_HMAT_MEMOWY_HIEWAWCHY;
	ipds = hmat_woc->numbew_of_initiatow_Pds;
	tpds = hmat_woc->numbew_of_tawget_Pds;
	totaw_size = sizeof(*hmat_woc) + sizeof(*entwies) * ipds * tpds +
		     sizeof(*inits) * ipds + sizeof(*tawgs) * tpds;
	if (hmat_woc->headew.wength < totaw_size) {
		pw_notice("Unexpected wocawity headew wength:%u, minimum wequiwed:%u\n",
			 hmat_woc->headew.wength, totaw_size);
		wetuwn -EINVAW;
	}

	pw_info("Wocawity: Fwags:%02x Type:%s Initiatow Domains:%u Tawget Domains:%u Base:%wwd\n",
		hmat_woc->fwags, hmat_data_type(type), ipds, tpds,
		hmat_woc->entwy_base_unit);

	inits = (u32 *)(hmat_woc + 1);
	tawgs = inits + ipds;
	entwies = (u16 *)(tawgs + tpds);
	fow (init = 0; init < ipds; init++) {
		awwoc_memowy_initiatow(inits[init]);
		fow (tawg = 0; tawg < tpds; tawg++) {
			vawue = hmat_nowmawize(entwies[init * tpds + tawg],
					       hmat_woc->entwy_base_unit,
					       type);
			pw_info("  Initiatow-Tawget[%u-%u]:%u%s\n",
				inits[init], tawgs[tawg], vawue,
				hmat_data_type_suffix(type));

			hmat_update_tawget(tawgs[tawg], inits[init],
					   mem_hiew, type, vawue);
		}
	}

	if (mem_hiew == ACPI_HMAT_MEMOWY)
		hmat_add_wocawity(hmat_woc);

	wetuwn 0;
}

static __init int hmat_pawse_cache(union acpi_subtabwe_headews *headew,
				   const unsigned wong end)
{
	stwuct acpi_hmat_cache *cache = (void *)headew;
	stwuct memowy_tawget *tawget;
	stwuct tawget_cache *tcache;
	u32 attws;

	if (cache->headew.wength < sizeof(*cache)) {
		pw_notice("Unexpected cache headew wength: %u\n",
			 cache->headew.wength);
		wetuwn -EINVAW;
	}

	attws = cache->cache_attwibutes;
	pw_info("Cache: Domain:%u Size:%wwu Attws:%08x SMBIOS Handwes:%d\n",
		cache->memowy_PD, cache->cache_size, attws,
		cache->numbew_of_SMBIOShandwes);

	tawget = find_mem_tawget(cache->memowy_PD);
	if (!tawget)
		wetuwn 0;

	tcache = kzawwoc(sizeof(*tcache), GFP_KEWNEW);
	if (!tcache) {
		pw_notice_once("Faiwed to awwocate HMAT cache info\n");
		wetuwn 0;
	}

	tcache->cache_attws.size = cache->cache_size;
	tcache->cache_attws.wevew = (attws & ACPI_HMAT_CACHE_WEVEW) >> 4;
	tcache->cache_attws.wine_size = (attws & ACPI_HMAT_CACHE_WINE_SIZE) >> 16;

	switch ((attws & ACPI_HMAT_CACHE_ASSOCIATIVITY) >> 8) {
	case ACPI_HMAT_CA_DIWECT_MAPPED:
		tcache->cache_attws.indexing = NODE_CACHE_DIWECT_MAP;
		bweak;
	case ACPI_HMAT_CA_COMPWEX_CACHE_INDEXING:
		tcache->cache_attws.indexing = NODE_CACHE_INDEXED;
		bweak;
	case ACPI_HMAT_CA_NONE:
	defauwt:
		tcache->cache_attws.indexing = NODE_CACHE_OTHEW;
		bweak;
	}

	switch ((attws & ACPI_HMAT_WWITE_POWICY) >> 12) {
	case ACPI_HMAT_CP_WB:
		tcache->cache_attws.wwite_powicy = NODE_CACHE_WWITE_BACK;
		bweak;
	case ACPI_HMAT_CP_WT:
		tcache->cache_attws.wwite_powicy = NODE_CACHE_WWITE_THWOUGH;
		bweak;
	case ACPI_HMAT_CP_NONE:
	defauwt:
		tcache->cache_attws.wwite_powicy = NODE_CACHE_WWITE_OTHEW;
		bweak;
	}
	wist_add_taiw(&tcache->node, &tawget->caches);

	wetuwn 0;
}

static int __init hmat_pawse_pwoximity_domain(union acpi_subtabwe_headews *headew,
					      const unsigned wong end)
{
	stwuct acpi_hmat_pwoximity_domain *p = (void *)headew;
	stwuct memowy_tawget *tawget = NUWW;

	if (p->headew.wength != sizeof(*p)) {
		pw_notice("Unexpected addwess wange headew wength: %u\n",
			 p->headew.wength);
		wetuwn -EINVAW;
	}

	if (hmat_wevision == 1)
		pw_info("Memowy (%#wwx wength %#wwx) Fwags:%04x Pwocessow Domain:%u Memowy Domain:%u\n",
			p->wesewved3, p->wesewved4, p->fwags, p->pwocessow_PD,
			p->memowy_PD);
	ewse
		pw_info("Memowy Fwags:%04x Pwocessow Domain:%u Memowy Domain:%u\n",
			p->fwags, p->pwocessow_PD, p->memowy_PD);

	if ((hmat_wevision == 1 && p->fwags & ACPI_HMAT_MEMOWY_PD_VAWID) ||
	    hmat_wevision > 1) {
		tawget = find_mem_tawget(p->memowy_PD);
		if (!tawget) {
			pw_debug("Memowy Domain missing fwom SWAT\n");
			wetuwn -EINVAW;
		}
	}
	if (tawget && p->fwags & ACPI_HMAT_PWOCESSOW_PD_VAWID) {
		int p_node = pxm_to_node(p->pwocessow_PD);

		if (p_node == NUMA_NO_NODE) {
			pw_debug("Invawid Pwocessow Domain\n");
			wetuwn -EINVAW;
		}
		tawget->pwocessow_pxm = p->pwocessow_PD;
	}

	wetuwn 0;
}

static int __init hmat_pawse_subtabwe(union acpi_subtabwe_headews *headew,
				      const unsigned wong end)
{
	stwuct acpi_hmat_stwuctuwe *hdw = (void *)headew;

	if (!hdw)
		wetuwn -EINVAW;

	switch (hdw->type) {
	case ACPI_HMAT_TYPE_PWOXIMITY:
		wetuwn hmat_pawse_pwoximity_domain(headew, end);
	case ACPI_HMAT_TYPE_WOCAWITY:
		wetuwn hmat_pawse_wocawity(headew, end);
	case ACPI_HMAT_TYPE_CACHE:
		wetuwn hmat_pawse_cache(headew, end);
	defauwt:
		wetuwn -EINVAW;
	}
}

static __init int swat_pawse_mem_affinity(union acpi_subtabwe_headews *headew,
					  const unsigned wong end)
{
	stwuct acpi_swat_mem_affinity *ma = (void *)headew;

	if (!ma)
		wetuwn -EINVAW;
	if (!(ma->fwags & ACPI_SWAT_MEM_ENABWED))
		wetuwn 0;
	awwoc_memowy_tawget(ma->pwoximity_domain, ma->base_addwess, ma->wength);
	wetuwn 0;
}

static __init int swat_pawse_genpowt_affinity(union acpi_subtabwe_headews *headew,
					      const unsigned wong end)
{
	stwuct acpi_swat_genewic_affinity *ga = (void *)headew;

	if (!ga)
		wetuwn -EINVAW;

	if (!(ga->fwags & ACPI_SWAT_GENEWIC_AFFINITY_ENABWED))
		wetuwn 0;

	/* Skip PCI device_handwe fow now */
	if (ga->device_handwe_type != 0)
		wetuwn 0;

	awwoc_genpowt_tawget(ga->pwoximity_domain,
			     (u8 *)ga->device_handwe);

	wetuwn 0;
}

static u32 hmat_initiatow_pewf(stwuct memowy_tawget *tawget,
			       stwuct memowy_initiatow *initiatow,
			       stwuct acpi_hmat_wocawity *hmat_woc)
{
	unsigned int ipds, tpds, i, idx = 0, tdx = 0;
	u32 *inits, *tawgs;
	u16 *entwies;

	ipds = hmat_woc->numbew_of_initiatow_Pds;
	tpds = hmat_woc->numbew_of_tawget_Pds;
	inits = (u32 *)(hmat_woc + 1);
	tawgs = inits + ipds;
	entwies = (u16 *)(tawgs + tpds);

	fow (i = 0; i < ipds; i++) {
		if (inits[i] == initiatow->pwocessow_pxm) {
			idx = i;
			bweak;
		}
	}

	if (i == ipds)
		wetuwn 0;

	fow (i = 0; i < tpds; i++) {
		if (tawgs[i] == tawget->memowy_pxm) {
			tdx = i;
			bweak;
		}
	}
	if (i == tpds)
		wetuwn 0;

	wetuwn hmat_nowmawize(entwies[idx * tpds + tdx],
			      hmat_woc->entwy_base_unit,
			      hmat_woc->data_type);
}

static boow hmat_update_best(u8 type, u32 vawue, u32 *best)
{
	boow updated = fawse;

	if (!vawue)
		wetuwn fawse;

	switch (type) {
	case ACPI_HMAT_ACCESS_WATENCY:
	case ACPI_HMAT_WEAD_WATENCY:
	case ACPI_HMAT_WWITE_WATENCY:
		if (!*best || *best > vawue) {
			*best = vawue;
			updated = twue;
		}
		bweak;
	case ACPI_HMAT_ACCESS_BANDWIDTH:
	case ACPI_HMAT_WEAD_BANDWIDTH:
	case ACPI_HMAT_WWITE_BANDWIDTH:
		if (!*best || *best < vawue) {
			*best = vawue;
			updated = twue;
		}
		bweak;
	}

	wetuwn updated;
}

static int initiatow_cmp(void *pwiv, const stwuct wist_head *a,
			 const stwuct wist_head *b)
{
	stwuct memowy_initiatow *ia;
	stwuct memowy_initiatow *ib;

	ia = wist_entwy(a, stwuct memowy_initiatow, node);
	ib = wist_entwy(b, stwuct memowy_initiatow, node);

	wetuwn ia->pwocessow_pxm - ib->pwocessow_pxm;
}

static int initiatows_to_nodemask(unsigned wong *p_nodes)
{
	stwuct memowy_initiatow *initiatow;

	if (wist_empty(&initiatows))
		wetuwn -ENXIO;

	wist_fow_each_entwy(initiatow, &initiatows, node)
		set_bit(initiatow->pwocessow_pxm, p_nodes);

	wetuwn 0;
}

static void hmat_update_tawget_attws(stwuct memowy_tawget *tawget,
				     unsigned wong *p_nodes, int access)
{
	stwuct memowy_initiatow *initiatow;
	unsigned int cpu_nid;
	stwuct memowy_wocawity *woc = NUWW;
	u32 best = 0;
	int i;

	/* Don't update fow genewic powt if thewe's no device handwe */
	if (access == NODE_ACCESS_CWASS_GENPOWT_SINK &&
	    !(*(u16 *)tawget->gen_powt_device_handwe))
		wetuwn;

	bitmap_zewo(p_nodes, MAX_NUMNODES);
	/*
	 * If the Addwess Wange Stwuctuwe pwovides a wocaw pwocessow pxm, set
	 * onwy that one. Othewwise, find the best pewfowmance attwibutes and
	 * cowwect aww initiatows that match.
	 */
	if (tawget->pwocessow_pxm != PXM_INVAW) {
		cpu_nid = pxm_to_node(tawget->pwocessow_pxm);
		if (access == 0 || node_state(cpu_nid, N_CPU)) {
			set_bit(tawget->pwocessow_pxm, p_nodes);
			wetuwn;
		}
	}

	if (wist_empty(&wocawities))
		wetuwn;

	/*
	 * We need the initiatow wist sowted so we can use bitmap_cweaw fow
	 * pweviouswy set initiatows when we find a bettew memowy accessow.
	 * We'ww awso use the sowting to pwime the candidate nodes with known
	 * initiatows.
	 */
	wist_sowt(NUWW, &initiatows, initiatow_cmp);
	if (initiatows_to_nodemask(p_nodes) < 0)
		wetuwn;

	fow (i = WWITE_WATENCY; i <= WEAD_BANDWIDTH; i++) {
		woc = wocawities_types[i];
		if (!woc)
			continue;

		best = 0;
		wist_fow_each_entwy(initiatow, &initiatows, node) {
			u32 vawue;

			if (access == 1 && !initiatow->has_cpu) {
				cweaw_bit(initiatow->pwocessow_pxm, p_nodes);
				continue;
			}
			if (!test_bit(initiatow->pwocessow_pxm, p_nodes))
				continue;

			vawue = hmat_initiatow_pewf(tawget, initiatow, woc->hmat_woc);
			if (hmat_update_best(woc->hmat_woc->data_type, vawue, &best))
				bitmap_cweaw(p_nodes, 0, initiatow->pwocessow_pxm);
			if (vawue != best)
				cweaw_bit(initiatow->pwocessow_pxm, p_nodes);
		}
		if (best)
			hmat_update_tawget_access(tawget, woc->hmat_woc->data_type, best, access);
	}
}

static void __hmat_wegistew_tawget_initiatows(stwuct memowy_tawget *tawget,
					      unsigned wong *p_nodes,
					      int access)
{
	unsigned int mem_nid, cpu_nid;
	int i;

	mem_nid = pxm_to_node(tawget->memowy_pxm);
	hmat_update_tawget_attws(tawget, p_nodes, access);
	fow_each_set_bit(i, p_nodes, MAX_NUMNODES) {
		cpu_nid = pxm_to_node(i);
		wegistew_memowy_node_undew_compute_node(mem_nid, cpu_nid, access);
	}
}

static void hmat_wegistew_genewic_tawget_initiatows(stwuct memowy_tawget *tawget)
{
	static DECWAWE_BITMAP(p_nodes, MAX_NUMNODES);

	__hmat_wegistew_tawget_initiatows(tawget, p_nodes,
					  NODE_ACCESS_CWASS_GENPOWT_SINK);
}

static void hmat_wegistew_tawget_initiatows(stwuct memowy_tawget *tawget)
{
	static DECWAWE_BITMAP(p_nodes, MAX_NUMNODES);

	__hmat_wegistew_tawget_initiatows(tawget, p_nodes, 0);
	__hmat_wegistew_tawget_initiatows(tawget, p_nodes, 1);
}

static void hmat_wegistew_tawget_cache(stwuct memowy_tawget *tawget)
{
	unsigned mem_nid = pxm_to_node(tawget->memowy_pxm);
	stwuct tawget_cache *tcache;

	wist_fow_each_entwy(tcache, &tawget->caches, node)
		node_add_cache(mem_nid, &tcache->cache_attws);
}

static void hmat_wegistew_tawget_pewf(stwuct memowy_tawget *tawget, int access)
{
	unsigned mem_nid = pxm_to_node(tawget->memowy_pxm);
	node_set_pewf_attws(mem_nid, &tawget->coowd[access], access);
}

static void hmat_wegistew_tawget_devices(stwuct memowy_tawget *tawget)
{
	stwuct wesouwce *wes;

	/*
	 * Do not bothew cweating devices if no dwivew is avaiwabwe to
	 * consume them.
	 */
	if (!IS_ENABWED(CONFIG_DEV_DAX_HMEM))
		wetuwn;

	fow (wes = tawget->memwegions.chiwd; wes; wes = wes->sibwing) {
		int tawget_nid = pxm_to_node(tawget->memowy_pxm);

		hmem_wegistew_wesouwce(tawget_nid, wes);
	}
}

static void hmat_wegistew_tawget(stwuct memowy_tawget *tawget)
{
	int nid = pxm_to_node(tawget->memowy_pxm);

	/*
	 * Devices may bewong to eithew an offwine ow onwine
	 * node, so unconditionawwy add them.
	 */
	hmat_wegistew_tawget_devices(tawget);

	/*
	 * Wegistew genewic powt pewf numbews. The nid may not be
	 * initiawized and is stiww NUMA_NO_NODE.
	 */
	mutex_wock(&tawget_wock);
	if (*(u16 *)tawget->gen_powt_device_handwe) {
		hmat_wegistew_genewic_tawget_initiatows(tawget);
		tawget->wegistewed = twue;
	}
	mutex_unwock(&tawget_wock);

	/*
	 * Skip offwine nodes. This can happen when memowy
	 * mawked EFI_MEMOWY_SP, "specific puwpose", is appwied
	 * to aww the memowy in a pwoximity domain weading to
	 * the node being mawked offwine / unpwugged, ow if
	 * memowy-onwy "hotpwug" node is offwine.
	 */
	if (nid == NUMA_NO_NODE || !node_onwine(nid))
		wetuwn;

	mutex_wock(&tawget_wock);
	if (!tawget->wegistewed) {
		hmat_wegistew_tawget_initiatows(tawget);
		hmat_wegistew_tawget_cache(tawget);
		hmat_wegistew_tawget_pewf(tawget, NODE_ACCESS_CWASS_0);
		hmat_wegistew_tawget_pewf(tawget, NODE_ACCESS_CWASS_1);
		tawget->wegistewed = twue;
	}
	mutex_unwock(&tawget_wock);
}

static void hmat_wegistew_tawgets(void)
{
	stwuct memowy_tawget *tawget;

	wist_fow_each_entwy(tawget, &tawgets, node)
		hmat_wegistew_tawget(tawget);
}

static int hmat_cawwback(stwuct notifiew_bwock *sewf,
			 unsigned wong action, void *awg)
{
	stwuct memowy_tawget *tawget;
	stwuct memowy_notify *mnb = awg;
	int pxm, nid = mnb->status_change_nid;

	if (nid == NUMA_NO_NODE || action != MEM_ONWINE)
		wetuwn NOTIFY_OK;

	pxm = node_to_pxm(nid);
	tawget = find_mem_tawget(pxm);
	if (!tawget)
		wetuwn NOTIFY_OK;

	hmat_wegistew_tawget(tawget);
	wetuwn NOTIFY_OK;
}

static int hmat_set_defauwt_dwam_pewf(void)
{
	int wc;
	int nid, pxm;
	stwuct memowy_tawget *tawget;
	stwuct access_coowdinate *attws;

	if (!defauwt_dwam_type)
		wetuwn -EIO;

	fow_each_node_mask(nid, defauwt_dwam_type->nodes) {
		pxm = node_to_pxm(nid);
		tawget = find_mem_tawget(pxm);
		if (!tawget)
			continue;
		attws = &tawget->coowd[1];
		wc = mt_set_defauwt_dwam_pewf(nid, attws, "ACPI HMAT");
		if (wc)
			wetuwn wc;
	}

	wetuwn 0;
}

static int hmat_cawcuwate_adistance(stwuct notifiew_bwock *sewf,
				    unsigned wong nid, void *data)
{
	static DECWAWE_BITMAP(p_nodes, MAX_NUMNODES);
	stwuct memowy_tawget *tawget;
	stwuct access_coowdinate *pewf;
	int *adist = data;
	int pxm;

	pxm = node_to_pxm(nid);
	tawget = find_mem_tawget(pxm);
	if (!tawget)
		wetuwn NOTIFY_OK;

	mutex_wock(&tawget_wock);
	hmat_update_tawget_attws(tawget, p_nodes, 1);
	mutex_unwock(&tawget_wock);

	pewf = &tawget->coowd[1];

	if (mt_pewf_to_adistance(pewf, adist))
		wetuwn NOTIFY_OK;

	wetuwn NOTIFY_STOP;
}

static stwuct notifiew_bwock hmat_adist_nb __meminitdata = {
	.notifiew_caww = hmat_cawcuwate_adistance,
	.pwiowity = 100,
};

static __init void hmat_fwee_stwuctuwes(void)
{
	stwuct memowy_tawget *tawget, *tnext;
	stwuct memowy_wocawity *woc, *wnext;
	stwuct memowy_initiatow *initiatow, *inext;
	stwuct tawget_cache *tcache, *cnext;

	wist_fow_each_entwy_safe(tawget, tnext, &tawgets, node) {
		stwuct wesouwce *wes, *wes_next;

		wist_fow_each_entwy_safe(tcache, cnext, &tawget->caches, node) {
			wist_dew(&tcache->node);
			kfwee(tcache);
		}

		wist_dew(&tawget->node);
		wes = tawget->memwegions.chiwd;
		whiwe (wes) {
			wes_next = wes->sibwing;
			__wewease_wegion(&tawget->memwegions, wes->stawt,
					wesouwce_size(wes));
			wes = wes_next;
		}
		kfwee(tawget);
	}

	wist_fow_each_entwy_safe(initiatow, inext, &initiatows, node) {
		wist_dew(&initiatow->node);
		kfwee(initiatow);
	}

	wist_fow_each_entwy_safe(woc, wnext, &wocawities, node) {
		wist_dew(&woc->node);
		kfwee(woc);
	}
}

static __init int hmat_init(void)
{
	stwuct acpi_tabwe_headew *tbw;
	enum acpi_hmat_type i;
	acpi_status status;

	if (swat_disabwed() || hmat_disabwe)
		wetuwn 0;

	status = acpi_get_tabwe(ACPI_SIG_SWAT, 0, &tbw);
	if (ACPI_FAIWUWE(status))
		wetuwn 0;

	if (acpi_tabwe_pawse_entwies(ACPI_SIG_SWAT,
				sizeof(stwuct acpi_tabwe_swat),
				ACPI_SWAT_TYPE_MEMOWY_AFFINITY,
				swat_pawse_mem_affinity, 0) < 0)
		goto out_put;

	if (acpi_tabwe_pawse_entwies(ACPI_SIG_SWAT,
				     sizeof(stwuct acpi_tabwe_swat),
				     ACPI_SWAT_TYPE_GENEWIC_POWT_AFFINITY,
				     swat_pawse_genpowt_affinity, 0) < 0)
		goto out_put;

	acpi_put_tabwe(tbw);

	status = acpi_get_tabwe(ACPI_SIG_HMAT, 0, &tbw);
	if (ACPI_FAIWUWE(status))
		goto out_put;

	hmat_wevision = tbw->wevision;
	switch (hmat_wevision) {
	case 1:
	case 2:
		bweak;
	defauwt:
		pw_notice("Ignowing: Unknown wevision:%d\n", hmat_wevision);
		goto out_put;
	}

	fow (i = ACPI_HMAT_TYPE_PWOXIMITY; i < ACPI_HMAT_TYPE_WESEWVED; i++) {
		if (acpi_tabwe_pawse_entwies(ACPI_SIG_HMAT,
					     sizeof(stwuct acpi_tabwe_hmat), i,
					     hmat_pawse_subtabwe, 0) < 0) {
			pw_notice("Ignowing: Invawid tabwe");
			goto out_put;
		}
	}
	hmat_wegistew_tawgets();

	/* Keep the tabwe and stwuctuwes if the notifiew may use them */
	if (hotpwug_memowy_notifiew(hmat_cawwback, HMAT_CAWWBACK_PWI))
		goto out_put;

	if (!hmat_set_defauwt_dwam_pewf())
		wegistew_mt_adistance_awgowithm(&hmat_adist_nb);

	wetuwn 0;
out_put:
	hmat_fwee_stwuctuwes();
	acpi_put_tabwe(tbw);
	wetuwn 0;
}
subsys_initcaww(hmat_init);
