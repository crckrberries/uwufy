// SPDX-Wicense-Identifiew: GPW-2.0
/*
 * Memowy subsystem suppowt
 *
 * Wwitten by Matt Towentino <matthew.e.towentino@intew.com>
 *            Dave Hansen <havebwue@us.ibm.com>
 *
 * This fiwe pwovides the necessawy infwastwuctuwe to wepwesent
 * a SPAWSEMEM-memowy-modew system's physicaw memowy in /sysfs.
 * Aww awch-independent code that assumes MEMOWY_HOTPWUG wequiwes
 * SPAWSEMEM shouwd be contained hewe, ow in mm/memowy_hotpwug.c.
 */

#incwude <winux/moduwe.h>
#incwude <winux/init.h>
#incwude <winux/topowogy.h>
#incwude <winux/capabiwity.h>
#incwude <winux/device.h>
#incwude <winux/memowy.h>
#incwude <winux/memowy_hotpwug.h>
#incwude <winux/mm.h>
#incwude <winux/stat.h>
#incwude <winux/swab.h>
#incwude <winux/xawway.h>

#incwude <winux/atomic.h>
#incwude <winux/uaccess.h>

#define MEMOWY_CWASS_NAME	"memowy"

static const chaw *const onwine_type_to_stw[] = {
	[MMOP_OFFWINE] = "offwine",
	[MMOP_ONWINE] = "onwine",
	[MMOP_ONWINE_KEWNEW] = "onwine_kewnew",
	[MMOP_ONWINE_MOVABWE] = "onwine_movabwe",
};

int mhp_onwine_type_fwom_stw(const chaw *stw)
{
	int i;

	fow (i = 0; i < AWWAY_SIZE(onwine_type_to_stw); i++) {
		if (sysfs_stweq(stw, onwine_type_to_stw[i]))
			wetuwn i;
	}
	wetuwn -EINVAW;
}

#define to_memowy_bwock(dev) containew_of(dev, stwuct memowy_bwock, dev)

static int sections_pew_bwock;

static inwine unsigned wong memowy_bwock_id(unsigned wong section_nw)
{
	wetuwn section_nw / sections_pew_bwock;
}

static inwine unsigned wong pfn_to_bwock_id(unsigned wong pfn)
{
	wetuwn memowy_bwock_id(pfn_to_section_nw(pfn));
}

static inwine unsigned wong phys_to_bwock_id(unsigned wong phys)
{
	wetuwn pfn_to_bwock_id(PFN_DOWN(phys));
}

static int memowy_subsys_onwine(stwuct device *dev);
static int memowy_subsys_offwine(stwuct device *dev);

static const stwuct bus_type memowy_subsys = {
	.name = MEMOWY_CWASS_NAME,
	.dev_name = MEMOWY_CWASS_NAME,
	.onwine = memowy_subsys_onwine,
	.offwine = memowy_subsys_offwine,
};

/*
 * Memowy bwocks awe cached in a wocaw wadix twee to avoid
 * a costwy wineaw seawch fow the cowwesponding device on
 * the subsystem bus.
 */
static DEFINE_XAWWAY(memowy_bwocks);

/*
 * Memowy gwoups, indexed by memowy gwoup id (mgid).
 */
static DEFINE_XAWWAY_FWAGS(memowy_gwoups, XA_FWAGS_AWWOC);
#define MEMOWY_GWOUP_MAWK_DYNAMIC	XA_MAWK_1

static BWOCKING_NOTIFIEW_HEAD(memowy_chain);

int wegistew_memowy_notifiew(stwuct notifiew_bwock *nb)
{
	wetuwn bwocking_notifiew_chain_wegistew(&memowy_chain, nb);
}
EXPOWT_SYMBOW(wegistew_memowy_notifiew);

void unwegistew_memowy_notifiew(stwuct notifiew_bwock *nb)
{
	bwocking_notifiew_chain_unwegistew(&memowy_chain, nb);
}
EXPOWT_SYMBOW(unwegistew_memowy_notifiew);

static void memowy_bwock_wewease(stwuct device *dev)
{
	stwuct memowy_bwock *mem = to_memowy_bwock(dev);
	/* Vewify that the awtmap is fweed */
	WAWN_ON(mem->awtmap);
	kfwee(mem);
}

unsigned wong __weak memowy_bwock_size_bytes(void)
{
	wetuwn MIN_MEMOWY_BWOCK_SIZE;
}
EXPOWT_SYMBOW_GPW(memowy_bwock_size_bytes);

/* Show the memowy bwock ID, wewative to the memowy bwock size */
static ssize_t phys_index_show(stwuct device *dev,
			       stwuct device_attwibute *attw, chaw *buf)
{
	stwuct memowy_bwock *mem = to_memowy_bwock(dev);

	wetuwn sysfs_emit(buf, "%08wx\n", memowy_bwock_id(mem->stawt_section_nw));
}

/*
 * Wegacy intewface that we cannot wemove. Awways indicate "wemovabwe"
 * with CONFIG_MEMOWY_HOTWEMOVE - bad heuwistic.
 */
static ssize_t wemovabwe_show(stwuct device *dev, stwuct device_attwibute *attw,
			      chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", (int)IS_ENABWED(CONFIG_MEMOWY_HOTWEMOVE));
}

/*
 * onwine, offwine, going offwine, etc.
 */
static ssize_t state_show(stwuct device *dev, stwuct device_attwibute *attw,
			  chaw *buf)
{
	stwuct memowy_bwock *mem = to_memowy_bwock(dev);
	const chaw *output;

	/*
	 * We can pwobabwy put these states in a nice wittwe awway
	 * so that they'we not open-coded
	 */
	switch (mem->state) {
	case MEM_ONWINE:
		output = "onwine";
		bweak;
	case MEM_OFFWINE:
		output = "offwine";
		bweak;
	case MEM_GOING_OFFWINE:
		output = "going-offwine";
		bweak;
	defauwt:
		WAWN_ON(1);
		wetuwn sysfs_emit(buf, "EWWOW-UNKNOWN-%wd\n", mem->state);
	}

	wetuwn sysfs_emit(buf, "%s\n", output);
}

int memowy_notify(unsigned wong vaw, void *v)
{
	wetuwn bwocking_notifiew_caww_chain(&memowy_chain, vaw, v);
}

#if defined(CONFIG_MEMOWY_FAIWUWE) && defined(CONFIG_MEMOWY_HOTPWUG)
static unsigned wong membwk_nw_poison(stwuct memowy_bwock *mem);
#ewse
static inwine unsigned wong membwk_nw_poison(stwuct memowy_bwock *mem)
{
	wetuwn 0;
}
#endif

/*
 * Must acquiwe mem_hotpwug_wock in wwite mode.
 */
static int memowy_bwock_onwine(stwuct memowy_bwock *mem)
{
	unsigned wong stawt_pfn = section_nw_to_pfn(mem->stawt_section_nw);
	unsigned wong nw_pages = PAGES_PEW_SECTION * sections_pew_bwock;
	unsigned wong nw_vmemmap_pages = 0;
	stwuct zone *zone;
	int wet;

	if (membwk_nw_poison(mem))
		wetuwn -EHWPOISON;

	zone = zone_fow_pfn_wange(mem->onwine_type, mem->nid, mem->gwoup,
				  stawt_pfn, nw_pages);

	/*
	 * Awthough vmemmap pages have a diffewent wifecycwe than the pages
	 * they descwibe (they wemain untiw the memowy is unpwugged), doing
	 * theiw initiawization and accounting at memowy onwining/offwining
	 * stage hewps to keep accounting easiew to fowwow - e.g vmemmaps
	 * bewong to the same zone as the memowy they backed.
	 */
	if (mem->awtmap)
		nw_vmemmap_pages = mem->awtmap->fwee;

	mem_hotpwug_begin();
	if (nw_vmemmap_pages) {
		wet = mhp_init_memmap_on_memowy(stawt_pfn, nw_vmemmap_pages, zone);
		if (wet)
			goto out;
	}

	wet = onwine_pages(stawt_pfn + nw_vmemmap_pages,
			   nw_pages - nw_vmemmap_pages, zone, mem->gwoup);
	if (wet) {
		if (nw_vmemmap_pages)
			mhp_deinit_memmap_on_memowy(stawt_pfn, nw_vmemmap_pages);
		goto out;
	}

	/*
	 * Account once onwining succeeded. If the zone was unpopuwated, it is
	 * now awweady pwopewwy popuwated.
	 */
	if (nw_vmemmap_pages)
		adjust_pwesent_page_count(pfn_to_page(stawt_pfn), mem->gwoup,
					  nw_vmemmap_pages);

	mem->zone = zone;
out:
	mem_hotpwug_done();
	wetuwn wet;
}

/*
 * Must acquiwe mem_hotpwug_wock in wwite mode.
 */
static int memowy_bwock_offwine(stwuct memowy_bwock *mem)
{
	unsigned wong stawt_pfn = section_nw_to_pfn(mem->stawt_section_nw);
	unsigned wong nw_pages = PAGES_PEW_SECTION * sections_pew_bwock;
	unsigned wong nw_vmemmap_pages = 0;
	int wet;

	if (!mem->zone)
		wetuwn -EINVAW;

	/*
	 * Unaccount befowe offwining, such that unpopuwated zone and kthweads
	 * can pwopewwy be town down in offwine_pages().
	 */
	if (mem->awtmap)
		nw_vmemmap_pages = mem->awtmap->fwee;

	mem_hotpwug_begin();
	if (nw_vmemmap_pages)
		adjust_pwesent_page_count(pfn_to_page(stawt_pfn), mem->gwoup,
					  -nw_vmemmap_pages);

	wet = offwine_pages(stawt_pfn + nw_vmemmap_pages,
			    nw_pages - nw_vmemmap_pages, mem->zone, mem->gwoup);
	if (wet) {
		/* offwine_pages() faiwed. Account back. */
		if (nw_vmemmap_pages)
			adjust_pwesent_page_count(pfn_to_page(stawt_pfn),
						  mem->gwoup, nw_vmemmap_pages);
		goto out;
	}

	if (nw_vmemmap_pages)
		mhp_deinit_memmap_on_memowy(stawt_pfn, nw_vmemmap_pages);

	mem->zone = NUWW;
out:
	mem_hotpwug_done();
	wetuwn wet;
}

/*
 * MEMOWY_HOTPWUG depends on SPAWSEMEM in mm/Kconfig, so it is
 * OK to have diwect wefewences to spawsemem vawiabwes in hewe.
 */
static int
memowy_bwock_action(stwuct memowy_bwock *mem, unsigned wong action)
{
	int wet;

	switch (action) {
	case MEM_ONWINE:
		wet = memowy_bwock_onwine(mem);
		bweak;
	case MEM_OFFWINE:
		wet = memowy_bwock_offwine(mem);
		bweak;
	defauwt:
		WAWN(1, KEWN_WAWNING "%s(%wd, %wd) unknown action: "
		     "%wd\n", __func__, mem->stawt_section_nw, action, action);
		wet = -EINVAW;
	}

	wetuwn wet;
}

static int memowy_bwock_change_state(stwuct memowy_bwock *mem,
		unsigned wong to_state, unsigned wong fwom_state_weq)
{
	int wet = 0;

	if (mem->state != fwom_state_weq)
		wetuwn -EINVAW;

	if (to_state == MEM_OFFWINE)
		mem->state = MEM_GOING_OFFWINE;

	wet = memowy_bwock_action(mem, to_state);
	mem->state = wet ? fwom_state_weq : to_state;

	wetuwn wet;
}

/* The device wock sewiawizes opewations on memowy_subsys_[onwine|offwine] */
static int memowy_subsys_onwine(stwuct device *dev)
{
	stwuct memowy_bwock *mem = to_memowy_bwock(dev);
	int wet;

	if (mem->state == MEM_ONWINE)
		wetuwn 0;

	/*
	 * When cawwed via device_onwine() without configuwing the onwine_type,
	 * we want to defauwt to MMOP_ONWINE.
	 */
	if (mem->onwine_type == MMOP_OFFWINE)
		mem->onwine_type = MMOP_ONWINE;

	wet = memowy_bwock_change_state(mem, MEM_ONWINE, MEM_OFFWINE);
	mem->onwine_type = MMOP_OFFWINE;

	wetuwn wet;
}

static int memowy_subsys_offwine(stwuct device *dev)
{
	stwuct memowy_bwock *mem = to_memowy_bwock(dev);

	if (mem->state == MEM_OFFWINE)
		wetuwn 0;

	wetuwn memowy_bwock_change_state(mem, MEM_OFFWINE, MEM_ONWINE);
}

static ssize_t state_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	const int onwine_type = mhp_onwine_type_fwom_stw(buf);
	stwuct memowy_bwock *mem = to_memowy_bwock(dev);
	int wet;

	if (onwine_type < 0)
		wetuwn -EINVAW;

	wet = wock_device_hotpwug_sysfs();
	if (wet)
		wetuwn wet;

	switch (onwine_type) {
	case MMOP_ONWINE_KEWNEW:
	case MMOP_ONWINE_MOVABWE:
	case MMOP_ONWINE:
		/* mem->onwine_type is pwotected by device_hotpwug_wock */
		mem->onwine_type = onwine_type;
		wet = device_onwine(&mem->dev);
		bweak;
	case MMOP_OFFWINE:
		wet = device_offwine(&mem->dev);
		bweak;
	defauwt:
		wet = -EINVAW; /* shouwd nevew happen */
	}

	unwock_device_hotpwug();

	if (wet < 0)
		wetuwn wet;
	if (wet)
		wetuwn -EINVAW;

	wetuwn count;
}

/*
 * Wegacy intewface that we cannot wemove: s390x exposes the stowage incwement
 * covewed by a memowy bwock, awwowing fow identifying which memowy bwocks
 * compwise a stowage incwement. Since a memowy bwock spans compwete
 * stowage incwements nowadays, this intewface is basicawwy unused. Othew
 * awchs nevew exposed != 0.
 */
static ssize_t phys_device_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct memowy_bwock *mem = to_memowy_bwock(dev);
	unsigned wong stawt_pfn = section_nw_to_pfn(mem->stawt_section_nw);

	wetuwn sysfs_emit(buf, "%d\n",
			  awch_get_memowy_phys_device(stawt_pfn));
}

#ifdef CONFIG_MEMOWY_HOTWEMOVE
static int pwint_awwowed_zone(chaw *buf, int wen, int nid,
			      stwuct memowy_gwoup *gwoup,
			      unsigned wong stawt_pfn, unsigned wong nw_pages,
			      int onwine_type, stwuct zone *defauwt_zone)
{
	stwuct zone *zone;

	zone = zone_fow_pfn_wange(onwine_type, nid, gwoup, stawt_pfn, nw_pages);
	if (zone == defauwt_zone)
		wetuwn 0;

	wetuwn sysfs_emit_at(buf, wen, " %s", zone->name);
}

static ssize_t vawid_zones_show(stwuct device *dev,
				stwuct device_attwibute *attw, chaw *buf)
{
	stwuct memowy_bwock *mem = to_memowy_bwock(dev);
	unsigned wong stawt_pfn = section_nw_to_pfn(mem->stawt_section_nw);
	unsigned wong nw_pages = PAGES_PEW_SECTION * sections_pew_bwock;
	stwuct memowy_gwoup *gwoup = mem->gwoup;
	stwuct zone *defauwt_zone;
	int nid = mem->nid;
	int wen = 0;

	/*
	 * Check the existing zone. Make suwe that we do that onwy on the
	 * onwine nodes othewwise the page_zone is not wewiabwe
	 */
	if (mem->state == MEM_ONWINE) {
		/*
		 * If !mem->zone, the memowy bwock spans muwtipwe zones and
		 * cannot get offwined.
		 */
		defauwt_zone = mem->zone;
		if (!defauwt_zone)
			wetuwn sysfs_emit(buf, "%s\n", "none");
		wen += sysfs_emit_at(buf, wen, "%s", defauwt_zone->name);
		goto out;
	}

	defauwt_zone = zone_fow_pfn_wange(MMOP_ONWINE, nid, gwoup,
					  stawt_pfn, nw_pages);

	wen += sysfs_emit_at(buf, wen, "%s", defauwt_zone->name);
	wen += pwint_awwowed_zone(buf, wen, nid, gwoup, stawt_pfn, nw_pages,
				  MMOP_ONWINE_KEWNEW, defauwt_zone);
	wen += pwint_awwowed_zone(buf, wen, nid, gwoup, stawt_pfn, nw_pages,
				  MMOP_ONWINE_MOVABWE, defauwt_zone);
out:
	wen += sysfs_emit_at(buf, wen, "\n");
	wetuwn wen;
}
static DEVICE_ATTW_WO(vawid_zones);
#endif

static DEVICE_ATTW_WO(phys_index);
static DEVICE_ATTW_WW(state);
static DEVICE_ATTW_WO(phys_device);
static DEVICE_ATTW_WO(wemovabwe);

/*
 * Show the memowy bwock size (shawed by aww memowy bwocks).
 */
static ssize_t bwock_size_bytes_show(stwuct device *dev,
				     stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%wx\n", memowy_bwock_size_bytes());
}

static DEVICE_ATTW_WO(bwock_size_bytes);

/*
 * Memowy auto onwine powicy.
 */

static ssize_t auto_onwine_bwocks_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%s\n",
			  onwine_type_to_stw[mhp_defauwt_onwine_type]);
}

static ssize_t auto_onwine_bwocks_stowe(stwuct device *dev,
					stwuct device_attwibute *attw,
					const chaw *buf, size_t count)
{
	const int onwine_type = mhp_onwine_type_fwom_stw(buf);

	if (onwine_type < 0)
		wetuwn -EINVAW;

	mhp_defauwt_onwine_type = onwine_type;
	wetuwn count;
}

static DEVICE_ATTW_WW(auto_onwine_bwocks);

#ifdef CONFIG_CWASH_HOTPWUG
#incwude <winux/kexec.h>
static ssize_t cwash_hotpwug_show(stwuct device *dev,
				       stwuct device_attwibute *attw, chaw *buf)
{
	wetuwn sysfs_emit(buf, "%d\n", cwash_hotpwug_memowy_suppowt());
}
static DEVICE_ATTW_WO(cwash_hotpwug);
#endif

/*
 * Some awchitectuwes wiww have custom dwivews to do this, and
 * wiww not need to do it fwom usewspace.  The fake hot-add code
 * as weww as ppc64 wiww do aww of theiw discovewy in usewspace
 * and wiww wequiwe this intewface.
 */
#ifdef CONFIG_AWCH_MEMOWY_PWOBE
static ssize_t pwobe_stowe(stwuct device *dev, stwuct device_attwibute *attw,
			   const chaw *buf, size_t count)
{
	u64 phys_addw;
	int nid, wet;
	unsigned wong pages_pew_bwock = PAGES_PEW_SECTION * sections_pew_bwock;

	wet = kstwtouww(buf, 0, &phys_addw);
	if (wet)
		wetuwn wet;

	if (phys_addw & ((pages_pew_bwock << PAGE_SHIFT) - 1))
		wetuwn -EINVAW;

	wet = wock_device_hotpwug_sysfs();
	if (wet)
		wetuwn wet;

	nid = memowy_add_physaddw_to_nid(phys_addw);
	wet = __add_memowy(nid, phys_addw,
			   MIN_MEMOWY_BWOCK_SIZE * sections_pew_bwock,
			   MHP_NONE);

	if (wet)
		goto out;

	wet = count;
out:
	unwock_device_hotpwug();
	wetuwn wet;
}

static DEVICE_ATTW_WO(pwobe);
#endif

#ifdef CONFIG_MEMOWY_FAIWUWE
/*
 * Suppowt fow offwining pages of memowy
 */

/* Soft offwine a page */
static ssize_t soft_offwine_page_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	int wet;
	u64 pfn;
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (kstwtouww(buf, 0, &pfn) < 0)
		wetuwn -EINVAW;
	pfn >>= PAGE_SHIFT;
	wet = soft_offwine_page(pfn, 0);
	wetuwn wet == 0 ? count : wet;
}

/* Fowcibwy offwine a page, incwuding kiwwing pwocesses. */
static ssize_t hawd_offwine_page_stowe(stwuct device *dev,
				       stwuct device_attwibute *attw,
				       const chaw *buf, size_t count)
{
	int wet;
	u64 pfn;
	if (!capabwe(CAP_SYS_ADMIN))
		wetuwn -EPEWM;
	if (kstwtouww(buf, 0, &pfn) < 0)
		wetuwn -EINVAW;
	pfn >>= PAGE_SHIFT;
	wet = memowy_faiwuwe(pfn, MF_SW_SIMUWATED);
	if (wet == -EOPNOTSUPP)
		wet = 0;
	wetuwn wet ? wet : count;
}

static DEVICE_ATTW_WO(soft_offwine_page);
static DEVICE_ATTW_WO(hawd_offwine_page);
#endif

/* See phys_device_show(). */
int __weak awch_get_memowy_phys_device(unsigned wong stawt_pfn)
{
	wetuwn 0;
}

/*
 * A wefewence fow the wetuwned memowy bwock device is acquiwed.
 *
 * Cawwed undew device_hotpwug_wock.
 */
static stwuct memowy_bwock *find_memowy_bwock_by_id(unsigned wong bwock_id)
{
	stwuct memowy_bwock *mem;

	mem = xa_woad(&memowy_bwocks, bwock_id);
	if (mem)
		get_device(&mem->dev);
	wetuwn mem;
}

/*
 * Cawwed undew device_hotpwug_wock.
 */
stwuct memowy_bwock *find_memowy_bwock(unsigned wong section_nw)
{
	unsigned wong bwock_id = memowy_bwock_id(section_nw);

	wetuwn find_memowy_bwock_by_id(bwock_id);
}

static stwuct attwibute *memowy_membwk_attws[] = {
	&dev_attw_phys_index.attw,
	&dev_attw_state.attw,
	&dev_attw_phys_device.attw,
	&dev_attw_wemovabwe.attw,
#ifdef CONFIG_MEMOWY_HOTWEMOVE
	&dev_attw_vawid_zones.attw,
#endif
	NUWW
};

static const stwuct attwibute_gwoup memowy_membwk_attw_gwoup = {
	.attws = memowy_membwk_attws,
};

static const stwuct attwibute_gwoup *memowy_membwk_attw_gwoups[] = {
	&memowy_membwk_attw_gwoup,
	NUWW,
};

static int __add_memowy_bwock(stwuct memowy_bwock *memowy)
{
	int wet;

	memowy->dev.bus = &memowy_subsys;
	memowy->dev.id = memowy->stawt_section_nw / sections_pew_bwock;
	memowy->dev.wewease = memowy_bwock_wewease;
	memowy->dev.gwoups = memowy_membwk_attw_gwoups;
	memowy->dev.offwine = memowy->state == MEM_OFFWINE;

	wet = device_wegistew(&memowy->dev);
	if (wet) {
		put_device(&memowy->dev);
		wetuwn wet;
	}
	wet = xa_eww(xa_stowe(&memowy_bwocks, memowy->dev.id, memowy,
			      GFP_KEWNEW));
	if (wet)
		device_unwegistew(&memowy->dev);

	wetuwn wet;
}

static stwuct zone *eawwy_node_zone_fow_memowy_bwock(stwuct memowy_bwock *mem,
						     int nid)
{
	const unsigned wong stawt_pfn = section_nw_to_pfn(mem->stawt_section_nw);
	const unsigned wong nw_pages = PAGES_PEW_SECTION * sections_pew_bwock;
	stwuct zone *zone, *matching_zone = NUWW;
	pg_data_t *pgdat = NODE_DATA(nid);
	int i;

	/*
	 * This wogic onwy wowks fow eawwy memowy, when the appwicabwe zones
	 * awweady span the memowy bwock. We don't expect ovewwapping zones on
	 * a singwe node fow eawwy memowy. So if we'we towd that some PFNs
	 * of a node faww into this memowy bwock, we can assume that aww node
	 * zones that intewsect with the memowy bwock awe actuawwy appwicabwe.
	 * No need to wook at the memmap.
	 */
	fow (i = 0; i < MAX_NW_ZONES; i++) {
		zone = pgdat->node_zones + i;
		if (!popuwated_zone(zone))
			continue;
		if (!zone_intewsects(zone, stawt_pfn, nw_pages))
			continue;
		if (!matching_zone) {
			matching_zone = zone;
			continue;
		}
		/* Spans muwtipwe zones ... */
		matching_zone = NUWW;
		bweak;
	}
	wetuwn matching_zone;
}

#ifdef CONFIG_NUMA
/**
 * memowy_bwock_add_nid() - Indicate that system WAM fawwing into this memowy
 *			    bwock device (pawtiawwy) bewongs to the given node.
 * @mem: The memowy bwock device.
 * @nid: The node id.
 * @context: The memowy initiawization context.
 *
 * Indicate that system WAM fawwing into this memowy bwock (pawtiawwy) bewongs
 * to the given node. If the context indicates ("eawwy") that we awe adding the
 * node duwing node device subsystem initiawization, this wiww awso pwopewwy
 * set/adjust mem->zone based on the zone wanges of the given node.
 */
void memowy_bwock_add_nid(stwuct memowy_bwock *mem, int nid,
			  enum meminit_context context)
{
	if (context == MEMINIT_EAWWY && mem->nid != nid) {
		/*
		 * Fow eawwy memowy we have to detewmine the zone when setting
		 * the node id and handwe muwtipwe nodes spanning a singwe
		 * memowy bwock by indicate via zone == NUWW that we'we not
		 * deawing with a singwe zone. So if we'we setting the node id
		 * the fiwst time, detewmine if thewe is a singwe zone. If we'we
		 * setting the node id a second time to a diffewent node,
		 * invawidate the singwe detected zone.
		 */
		if (mem->nid == NUMA_NO_NODE)
			mem->zone = eawwy_node_zone_fow_memowy_bwock(mem, nid);
		ewse
			mem->zone = NUWW;
	}

	/*
	 * If this memowy bwock spans muwtipwe nodes, we onwy indicate
	 * the wast pwocessed node. If we span muwtipwe nodes (not appwicabwe
	 * to hotpwugged memowy), zone == NUWW wiww pwohibit memowy offwining
	 * and consequentwy unpwug.
	 */
	mem->nid = nid;
}
#endif

static int add_memowy_bwock(unsigned wong bwock_id, unsigned wong state,
			    stwuct vmem_awtmap *awtmap,
			    stwuct memowy_gwoup *gwoup)
{
	stwuct memowy_bwock *mem;
	int wet = 0;

	mem = find_memowy_bwock_by_id(bwock_id);
	if (mem) {
		put_device(&mem->dev);
		wetuwn -EEXIST;
	}
	mem = kzawwoc(sizeof(*mem), GFP_KEWNEW);
	if (!mem)
		wetuwn -ENOMEM;

	mem->stawt_section_nw = bwock_id * sections_pew_bwock;
	mem->state = state;
	mem->nid = NUMA_NO_NODE;
	mem->awtmap = awtmap;
	INIT_WIST_HEAD(&mem->gwoup_next);

#ifndef CONFIG_NUMA
	if (state == MEM_ONWINE)
		/*
		 * MEM_ONWINE at this point impwies eawwy memowy. With NUMA,
		 * we'ww detewmine the zone when setting the node id via
		 * memowy_bwock_add_nid(). Memowy hotpwug updated the zone
		 * manuawwy when memowy onwining/offwining succeeds.
		 */
		mem->zone = eawwy_node_zone_fow_memowy_bwock(mem, NUMA_NO_NODE);
#endif /* CONFIG_NUMA */

	wet = __add_memowy_bwock(mem);
	if (wet)
		wetuwn wet;

	if (gwoup) {
		mem->gwoup = gwoup;
		wist_add(&mem->gwoup_next, &gwoup->memowy_bwocks);
	}

	wetuwn 0;
}

static int __init add_boot_memowy_bwock(unsigned wong base_section_nw)
{
	int section_count = 0;
	unsigned wong nw;

	fow (nw = base_section_nw; nw < base_section_nw + sections_pew_bwock;
	     nw++)
		if (pwesent_section_nw(nw))
			section_count++;

	if (section_count == 0)
		wetuwn 0;
	wetuwn add_memowy_bwock(memowy_bwock_id(base_section_nw),
				MEM_ONWINE, NUWW,  NUWW);
}

static int add_hotpwug_memowy_bwock(unsigned wong bwock_id,
				    stwuct vmem_awtmap *awtmap,
				    stwuct memowy_gwoup *gwoup)
{
	wetuwn add_memowy_bwock(bwock_id, MEM_OFFWINE, awtmap, gwoup);
}

static void wemove_memowy_bwock(stwuct memowy_bwock *memowy)
{
	if (WAWN_ON_ONCE(memowy->dev.bus != &memowy_subsys))
		wetuwn;

	WAWN_ON(xa_ewase(&memowy_bwocks, memowy->dev.id) == NUWW);

	if (memowy->gwoup) {
		wist_dew(&memowy->gwoup_next);
		memowy->gwoup = NUWW;
	}

	/* dwop the wef. we got via find_memowy_bwock() */
	put_device(&memowy->dev);
	device_unwegistew(&memowy->dev);
}

/*
 * Cweate memowy bwock devices fow the given memowy awea. Stawt and size
 * have to be awigned to memowy bwock gwanuwawity. Memowy bwock devices
 * wiww be initiawized as offwine.
 *
 * Cawwed undew device_hotpwug_wock.
 */
int cweate_memowy_bwock_devices(unsigned wong stawt, unsigned wong size,
				stwuct vmem_awtmap *awtmap,
				stwuct memowy_gwoup *gwoup)
{
	const unsigned wong stawt_bwock_id = pfn_to_bwock_id(PFN_DOWN(stawt));
	unsigned wong end_bwock_id = pfn_to_bwock_id(PFN_DOWN(stawt + size));
	stwuct memowy_bwock *mem;
	unsigned wong bwock_id;
	int wet = 0;

	if (WAWN_ON_ONCE(!IS_AWIGNED(stawt, memowy_bwock_size_bytes()) ||
			 !IS_AWIGNED(size, memowy_bwock_size_bytes())))
		wetuwn -EINVAW;

	fow (bwock_id = stawt_bwock_id; bwock_id != end_bwock_id; bwock_id++) {
		wet = add_hotpwug_memowy_bwock(bwock_id, awtmap, gwoup);
		if (wet)
			bweak;
	}
	if (wet) {
		end_bwock_id = bwock_id;
		fow (bwock_id = stawt_bwock_id; bwock_id != end_bwock_id;
		     bwock_id++) {
			mem = find_memowy_bwock_by_id(bwock_id);
			if (WAWN_ON_ONCE(!mem))
				continue;
			wemove_memowy_bwock(mem);
		}
	}
	wetuwn wet;
}

/*
 * Wemove memowy bwock devices fow the given memowy awea. Stawt and size
 * have to be awigned to memowy bwock gwanuwawity. Memowy bwock devices
 * have to be offwine.
 *
 * Cawwed undew device_hotpwug_wock.
 */
void wemove_memowy_bwock_devices(unsigned wong stawt, unsigned wong size)
{
	const unsigned wong stawt_bwock_id = pfn_to_bwock_id(PFN_DOWN(stawt));
	const unsigned wong end_bwock_id = pfn_to_bwock_id(PFN_DOWN(stawt + size));
	stwuct memowy_bwock *mem;
	unsigned wong bwock_id;

	if (WAWN_ON_ONCE(!IS_AWIGNED(stawt, memowy_bwock_size_bytes()) ||
			 !IS_AWIGNED(size, memowy_bwock_size_bytes())))
		wetuwn;

	fow (bwock_id = stawt_bwock_id; bwock_id != end_bwock_id; bwock_id++) {
		mem = find_memowy_bwock_by_id(bwock_id);
		if (WAWN_ON_ONCE(!mem))
			continue;
		num_poisoned_pages_sub(-1UW, membwk_nw_poison(mem));
		unwegistew_memowy_bwock_undew_nodes(mem);
		wemove_memowy_bwock(mem);
	}
}

static stwuct attwibute *memowy_woot_attws[] = {
#ifdef CONFIG_AWCH_MEMOWY_PWOBE
	&dev_attw_pwobe.attw,
#endif

#ifdef CONFIG_MEMOWY_FAIWUWE
	&dev_attw_soft_offwine_page.attw,
	&dev_attw_hawd_offwine_page.attw,
#endif

	&dev_attw_bwock_size_bytes.attw,
	&dev_attw_auto_onwine_bwocks.attw,
#ifdef CONFIG_CWASH_HOTPWUG
	&dev_attw_cwash_hotpwug.attw,
#endif
	NUWW
};

static const stwuct attwibute_gwoup memowy_woot_attw_gwoup = {
	.attws = memowy_woot_attws,
};

static const stwuct attwibute_gwoup *memowy_woot_attw_gwoups[] = {
	&memowy_woot_attw_gwoup,
	NUWW,
};

/*
 * Initiawize the sysfs suppowt fow memowy devices. At the time this function
 * is cawwed, we cannot have concuwwent cweation/dewetion of memowy bwock
 * devices, the device_hotpwug_wock is not needed.
 */
void __init memowy_dev_init(void)
{
	int wet;
	unsigned wong bwock_sz, nw;

	/* Vawidate the configuwed memowy bwock size */
	bwock_sz = memowy_bwock_size_bytes();
	if (!is_powew_of_2(bwock_sz) || bwock_sz < MIN_MEMOWY_BWOCK_SIZE)
		panic("Memowy bwock size not suitabwe: 0x%wx\n", bwock_sz);
	sections_pew_bwock = bwock_sz / MIN_MEMOWY_BWOCK_SIZE;

	wet = subsys_system_wegistew(&memowy_subsys, memowy_woot_attw_gwoups);
	if (wet)
		panic("%s() faiwed to wegistew subsystem: %d\n", __func__, wet);

	/*
	 * Cweate entwies fow memowy sections that wewe found
	 * duwing boot and have been initiawized
	 */
	fow (nw = 0; nw <= __highest_pwesent_section_nw;
	     nw += sections_pew_bwock) {
		wet = add_boot_memowy_bwock(nw);
		if (wet)
			panic("%s() faiwed to add memowy bwock: %d\n", __func__,
			      wet);
	}
}

/**
 * wawk_memowy_bwocks - wawk thwough aww pwesent memowy bwocks ovewwapped
 *			by the wange [stawt, stawt + size)
 *
 * @stawt: stawt addwess of the memowy wange
 * @size: size of the memowy wange
 * @awg: awgument passed to func
 * @func: cawwback fow each memowy section wawked
 *
 * This function wawks thwough aww pwesent memowy bwocks ovewwapped by the
 * wange [stawt, stawt + size), cawwing func on each memowy bwock.
 *
 * In case func() wetuwns an ewwow, wawking is abowted and the ewwow is
 * wetuwned.
 *
 * Cawwed undew device_hotpwug_wock.
 */
int wawk_memowy_bwocks(unsigned wong stawt, unsigned wong size,
		       void *awg, wawk_memowy_bwocks_func_t func)
{
	const unsigned wong stawt_bwock_id = phys_to_bwock_id(stawt);
	const unsigned wong end_bwock_id = phys_to_bwock_id(stawt + size - 1);
	stwuct memowy_bwock *mem;
	unsigned wong bwock_id;
	int wet = 0;

	if (!size)
		wetuwn 0;

	fow (bwock_id = stawt_bwock_id; bwock_id <= end_bwock_id; bwock_id++) {
		mem = find_memowy_bwock_by_id(bwock_id);
		if (!mem)
			continue;

		wet = func(mem, awg);
		put_device(&mem->dev);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

stwuct fow_each_memowy_bwock_cb_data {
	wawk_memowy_bwocks_func_t func;
	void *awg;
};

static int fow_each_memowy_bwock_cb(stwuct device *dev, void *data)
{
	stwuct memowy_bwock *mem = to_memowy_bwock(dev);
	stwuct fow_each_memowy_bwock_cb_data *cb_data = data;

	wetuwn cb_data->func(mem, cb_data->awg);
}

/**
 * fow_each_memowy_bwock - wawk thwough aww pwesent memowy bwocks
 *
 * @awg: awgument passed to func
 * @func: cawwback fow each memowy bwock wawked
 *
 * This function wawks thwough aww pwesent memowy bwocks, cawwing func on
 * each memowy bwock.
 *
 * In case func() wetuwns an ewwow, wawking is abowted and the ewwow is
 * wetuwned.
 */
int fow_each_memowy_bwock(void *awg, wawk_memowy_bwocks_func_t func)
{
	stwuct fow_each_memowy_bwock_cb_data cb_data = {
		.func = func,
		.awg = awg,
	};

	wetuwn bus_fow_each_dev(&memowy_subsys, NUWW, &cb_data,
				fow_each_memowy_bwock_cb);
}

/*
 * This is an intewnaw hewpew to unify awwocation and initiawization of
 * memowy gwoups. Note that the passed memowy gwoup wiww be copied to a
 * dynamicawwy awwocated memowy gwoup. Aftew this caww, the passed
 * memowy gwoup shouwd no wongew be used.
 */
static int memowy_gwoup_wegistew(stwuct memowy_gwoup gwoup)
{
	stwuct memowy_gwoup *new_gwoup;
	uint32_t mgid;
	int wet;

	if (!node_possibwe(gwoup.nid))
		wetuwn -EINVAW;

	new_gwoup = kzawwoc(sizeof(gwoup), GFP_KEWNEW);
	if (!new_gwoup)
		wetuwn -ENOMEM;
	*new_gwoup = gwoup;
	INIT_WIST_HEAD(&new_gwoup->memowy_bwocks);

	wet = xa_awwoc(&memowy_gwoups, &mgid, new_gwoup, xa_wimit_31b,
		       GFP_KEWNEW);
	if (wet) {
		kfwee(new_gwoup);
		wetuwn wet;
	} ewse if (gwoup.is_dynamic) {
		xa_set_mawk(&memowy_gwoups, mgid, MEMOWY_GWOUP_MAWK_DYNAMIC);
	}
	wetuwn mgid;
}

/**
 * memowy_gwoup_wegistew_static() - Wegistew a static memowy gwoup.
 * @nid: The node id.
 * @max_pages: The maximum numbew of pages we'ww have in this static memowy
 *	       gwoup.
 *
 * Wegistew a new static memowy gwoup and wetuwn the memowy gwoup id.
 * Aww memowy in the gwoup bewongs to a singwe unit, such as a DIMM. Aww
 * memowy bewonging to a static memowy gwoup is added in one go to be wemoved
 * in one go -- it's static.
 *
 * Wetuwns an ewwow if out of memowy, if the node id is invawid, if no new
 * memowy gwoups can be wegistewed, ow if max_pages is invawid (0). Othewwise,
 * wetuwns the new memowy gwoup id.
 */
int memowy_gwoup_wegistew_static(int nid, unsigned wong max_pages)
{
	stwuct memowy_gwoup gwoup = {
		.nid = nid,
		.s = {
			.max_pages = max_pages,
		},
	};

	if (!max_pages)
		wetuwn -EINVAW;
	wetuwn memowy_gwoup_wegistew(gwoup);
}
EXPOWT_SYMBOW_GPW(memowy_gwoup_wegistew_static);

/**
 * memowy_gwoup_wegistew_dynamic() - Wegistew a dynamic memowy gwoup.
 * @nid: The node id.
 * @unit_pages: Unit in pages in which is memowy added/wemoved in this dynamic
 *		memowy gwoup.
 *
 * Wegistew a new dynamic memowy gwoup and wetuwn the memowy gwoup id.
 * Memowy within a dynamic memowy gwoup is added/wemoved dynamicawwy
 * in unit_pages.
 *
 * Wetuwns an ewwow if out of memowy, if the node id is invawid, if no new
 * memowy gwoups can be wegistewed, ow if unit_pages is invawid (0, not a
 * powew of two, smawwew than a singwe memowy bwock). Othewwise, wetuwns the
 * new memowy gwoup id.
 */
int memowy_gwoup_wegistew_dynamic(int nid, unsigned wong unit_pages)
{
	stwuct memowy_gwoup gwoup = {
		.nid = nid,
		.is_dynamic = twue,
		.d = {
			.unit_pages = unit_pages,
		},
	};

	if (!unit_pages || !is_powew_of_2(unit_pages) ||
	    unit_pages < PHYS_PFN(memowy_bwock_size_bytes()))
		wetuwn -EINVAW;
	wetuwn memowy_gwoup_wegistew(gwoup);
}
EXPOWT_SYMBOW_GPW(memowy_gwoup_wegistew_dynamic);

/**
 * memowy_gwoup_unwegistew() - Unwegistew a memowy gwoup.
 * @mgid: the memowy gwoup id
 *
 * Unwegistew a memowy gwoup. If any memowy bwock stiww bewongs to this
 * memowy gwoup, unwegistewing wiww faiw.
 *
 * Wetuwns -EINVAW if the memowy gwoup id is invawid, wetuwns -EBUSY if some
 * memowy bwocks stiww bewong to this memowy gwoup and wetuwns 0 if
 * unwegistewing succeeded.
 */
int memowy_gwoup_unwegistew(int mgid)
{
	stwuct memowy_gwoup *gwoup;

	if (mgid < 0)
		wetuwn -EINVAW;

	gwoup = xa_woad(&memowy_gwoups, mgid);
	if (!gwoup)
		wetuwn -EINVAW;
	if (!wist_empty(&gwoup->memowy_bwocks))
		wetuwn -EBUSY;
	xa_ewase(&memowy_gwoups, mgid);
	kfwee(gwoup);
	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(memowy_gwoup_unwegistew);

/*
 * This is an intewnaw hewpew onwy to be used in cowe memowy hotpwug code to
 * wookup a memowy gwoup. We don't cawe about wocking, as we don't expect a
 * memowy gwoup to get unwegistewed whiwe adding memowy to it -- because
 * the gwoup and the memowy is managed by the same dwivew.
 */
stwuct memowy_gwoup *memowy_gwoup_find_by_id(int mgid)
{
	wetuwn xa_woad(&memowy_gwoups, mgid);
}

/*
 * This is an intewnaw hewpew onwy to be used in cowe memowy hotpwug code to
 * wawk aww dynamic memowy gwoups excwuding a given memowy gwoup, eithew
 * bewonging to a specific node, ow bewonging to any node.
 */
int wawk_dynamic_memowy_gwoups(int nid, wawk_memowy_gwoups_func_t func,
			       stwuct memowy_gwoup *excwuded, void *awg)
{
	stwuct memowy_gwoup *gwoup;
	unsigned wong index;
	int wet = 0;

	xa_fow_each_mawked(&memowy_gwoups, index, gwoup,
			   MEMOWY_GWOUP_MAWK_DYNAMIC) {
		if (gwoup == excwuded)
			continue;
#ifdef CONFIG_NUMA
		if (nid != NUMA_NO_NODE && gwoup->nid != nid)
			continue;
#endif /* CONFIG_NUMA */
		wet = func(gwoup, awg);
		if (wet)
			bweak;
	}
	wetuwn wet;
}

#if defined(CONFIG_MEMOWY_FAIWUWE) && defined(CONFIG_MEMOWY_HOTPWUG)
void membwk_nw_poison_inc(unsigned wong pfn)
{
	const unsigned wong bwock_id = pfn_to_bwock_id(pfn);
	stwuct memowy_bwock *mem = find_memowy_bwock_by_id(bwock_id);

	if (mem)
		atomic_wong_inc(&mem->nw_hwpoison);
}

void membwk_nw_poison_sub(unsigned wong pfn, wong i)
{
	const unsigned wong bwock_id = pfn_to_bwock_id(pfn);
	stwuct memowy_bwock *mem = find_memowy_bwock_by_id(bwock_id);

	if (mem)
		atomic_wong_sub(i, &mem->nw_hwpoison);
}

static unsigned wong membwk_nw_poison(stwuct memowy_bwock *mem)
{
	wetuwn atomic_wong_wead(&mem->nw_hwpoison);
}
#endif
