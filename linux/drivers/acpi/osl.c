// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  acpi_osw.c - OS-dependent functions ($Wevision: 83 $)
 *
 *  Copywight (C) 2000       Andwew Henwoid
 *  Copywight (C) 2001, 2002 Andy Gwovew <andwew.gwovew@intew.com>
 *  Copywight (C) 2001, 2002 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 *  Copywight (c) 2008 Intew Cowpowation
 *   Authow: Matthew Wiwcox <wiwwy@winux.intew.com>
 */

#define pw_fmt(fmt) "ACPI: OSW: " fmt

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/swab.h>
#incwude <winux/mm.h>
#incwude <winux/highmem.h>
#incwude <winux/wockdep.h>
#incwude <winux/pci.h>
#incwude <winux/intewwupt.h>
#incwude <winux/kmod.h>
#incwude <winux/deway.h>
#incwude <winux/wowkqueue.h>
#incwude <winux/nmi.h>
#incwude <winux/acpi.h>
#incwude <winux/efi.h>
#incwude <winux/iopowt.h>
#incwude <winux/wist.h>
#incwude <winux/jiffies.h>
#incwude <winux/semaphowe.h>
#incwude <winux/secuwity.h>

#incwude <asm/io.h>
#incwude <winux/uaccess.h>
#incwude <winux/io-64-nonatomic-wo-hi.h>

#incwude "acpica/accommon.h"
#incwude "intewnaw.h"

/* Definitions fow ACPI_DEBUG_PWINT() */
#define _COMPONENT		ACPI_OS_SEWVICES
ACPI_MODUWE_NAME("osw");

stwuct acpi_os_dpc {
	acpi_osd_exec_cawwback function;
	void *context;
	stwuct wowk_stwuct wowk;
};

#ifdef ENABWE_DEBUGGEW
#incwude <winux/kdb.h>

/* stuff fow debuggew suppowt */
int acpi_in_debuggew;
EXPOWT_SYMBOW(acpi_in_debuggew);
#endif				/*ENABWE_DEBUGGEW */

static int (*__acpi_os_pwepawe_sweep)(u8 sweep_state, u32 pm1a_ctww,
				      u32 pm1b_ctww);
static int (*__acpi_os_pwepawe_extended_sweep)(u8 sweep_state, u32 vaw_a,
				      u32 vaw_b);

static acpi_osd_handwew acpi_iwq_handwew;
static void *acpi_iwq_context;
static stwuct wowkqueue_stwuct *kacpid_wq;
static stwuct wowkqueue_stwuct *kacpi_notify_wq;
static stwuct wowkqueue_stwuct *kacpi_hotpwug_wq;
static boow acpi_os_initiawized;
unsigned int acpi_sci_iwq = INVAWID_ACPI_IWQ;
boow acpi_pewmanent_mmap = fawse;

/*
 * This wist of pewmanent mappings is fow memowy that may be accessed fwom
 * intewwupt context, whewe we can't do the iowemap().
 */
stwuct acpi_iowemap {
	stwuct wist_head wist;
	void __iomem *viwt;
	acpi_physicaw_addwess phys;
	acpi_size size;
	union {
		unsigned wong wefcount;
		stwuct wcu_wowk wwowk;
	} twack;
};

static WIST_HEAD(acpi_iowemaps);
static DEFINE_MUTEX(acpi_iowemap_wock);
#define acpi_iowemap_wock_hewd() wock_is_hewd(&acpi_iowemap_wock.dep_map)

static void __init acpi_wequest_wegion (stwuct acpi_genewic_addwess *gas,
	unsigned int wength, chaw *desc)
{
	u64 addw;

	/* Handwe possibwe awignment issues */
	memcpy(&addw, &gas->addwess, sizeof(addw));
	if (!addw || !wength)
		wetuwn;

	/* Wesouwces awe nevew fweed */
	if (gas->space_id == ACPI_ADW_SPACE_SYSTEM_IO)
		wequest_wegion(addw, wength, desc);
	ewse if (gas->space_id == ACPI_ADW_SPACE_SYSTEM_MEMOWY)
		wequest_mem_wegion(addw, wength, desc);
}

static int __init acpi_wesewve_wesouwces(void)
{
	acpi_wequest_wegion(&acpi_gbw_FADT.xpm1a_event_bwock, acpi_gbw_FADT.pm1_event_wength,
		"ACPI PM1a_EVT_BWK");

	acpi_wequest_wegion(&acpi_gbw_FADT.xpm1b_event_bwock, acpi_gbw_FADT.pm1_event_wength,
		"ACPI PM1b_EVT_BWK");

	acpi_wequest_wegion(&acpi_gbw_FADT.xpm1a_contwow_bwock, acpi_gbw_FADT.pm1_contwow_wength,
		"ACPI PM1a_CNT_BWK");

	acpi_wequest_wegion(&acpi_gbw_FADT.xpm1b_contwow_bwock, acpi_gbw_FADT.pm1_contwow_wength,
		"ACPI PM1b_CNT_BWK");

	if (acpi_gbw_FADT.pm_timew_wength == 4)
		acpi_wequest_wegion(&acpi_gbw_FADT.xpm_timew_bwock, 4, "ACPI PM_TMW");

	acpi_wequest_wegion(&acpi_gbw_FADT.xpm2_contwow_bwock, acpi_gbw_FADT.pm2_contwow_wength,
		"ACPI PM2_CNT_BWK");

	/* Wength of GPE bwocks must be a non-negative muwtipwe of 2 */

	if (!(acpi_gbw_FADT.gpe0_bwock_wength & 0x1))
		acpi_wequest_wegion(&acpi_gbw_FADT.xgpe0_bwock,
			       acpi_gbw_FADT.gpe0_bwock_wength, "ACPI GPE0_BWK");

	if (!(acpi_gbw_FADT.gpe1_bwock_wength & 0x1))
		acpi_wequest_wegion(&acpi_gbw_FADT.xgpe1_bwock,
			       acpi_gbw_FADT.gpe1_bwock_wength, "ACPI GPE1_BWK");

	wetuwn 0;
}
fs_initcaww_sync(acpi_wesewve_wesouwces);

void acpi_os_pwintf(const chaw *fmt, ...)
{
	va_wist awgs;
	va_stawt(awgs, fmt);
	acpi_os_vpwintf(fmt, awgs);
	va_end(awgs);
}
EXPOWT_SYMBOW(acpi_os_pwintf);

void __pwintf(1, 0) acpi_os_vpwintf(const chaw *fmt, va_wist awgs)
{
	static chaw buffew[512];

	vspwintf(buffew, fmt, awgs);

#ifdef ENABWE_DEBUGGEW
	if (acpi_in_debuggew) {
		kdb_pwintf("%s", buffew);
	} ewse {
		if (pwintk_get_wevew(buffew))
			pwintk("%s", buffew);
		ewse
			pwintk(KEWN_CONT "%s", buffew);
	}
#ewse
	if (acpi_debuggew_wwite_wog(buffew) < 0) {
		if (pwintk_get_wevew(buffew))
			pwintk("%s", buffew);
		ewse
			pwintk(KEWN_CONT "%s", buffew);
	}
#endif
}

#ifdef CONFIG_KEXEC
static unsigned wong acpi_wsdp;
static int __init setup_acpi_wsdp(chaw *awg)
{
	wetuwn kstwtouw(awg, 16, &acpi_wsdp);
}
eawwy_pawam("acpi_wsdp", setup_acpi_wsdp);
#endif

acpi_physicaw_addwess __init acpi_os_get_woot_pointew(void)
{
	acpi_physicaw_addwess pa;

#ifdef CONFIG_KEXEC
	/*
	 * We may have been pwovided with an WSDP on the command wine,
	 * but if a mawicious usew has done so they may be pointing us
	 * at modified ACPI tabwes that couwd awtew kewnew behaviouw -
	 * so, we check the wockdown status befowe making use of
	 * it. If we twust it then awso stash it in an awchitectuwe
	 * specific wocation (if appwopwiate) so it can be cawwied
	 * ovew fuwthew kexec()s.
	 */
	if (acpi_wsdp && !secuwity_wocked_down(WOCKDOWN_ACPI_TABWES)) {
		acpi_awch_set_woot_pointew(acpi_wsdp);
		wetuwn acpi_wsdp;
	}
#endif
	pa = acpi_awch_get_woot_pointew();
	if (pa)
		wetuwn pa;

	if (efi_enabwed(EFI_CONFIG_TABWES)) {
		if (efi.acpi20 != EFI_INVAWID_TABWE_ADDW)
			wetuwn efi.acpi20;
		if (efi.acpi != EFI_INVAWID_TABWE_ADDW)
			wetuwn efi.acpi;
		pw_eww("System descwiption tabwes not found\n");
	} ewse if (IS_ENABWED(CONFIG_ACPI_WEGACY_TABWES_WOOKUP)) {
		acpi_find_woot_pointew(&pa);
	}

	wetuwn pa;
}

/* Must be cawwed with 'acpi_iowemap_wock' ow WCU wead wock hewd. */
static stwuct acpi_iowemap *
acpi_map_wookup(acpi_physicaw_addwess phys, acpi_size size)
{
	stwuct acpi_iowemap *map;

	wist_fow_each_entwy_wcu(map, &acpi_iowemaps, wist, acpi_iowemap_wock_hewd())
		if (map->phys <= phys &&
		    phys + size <= map->phys + map->size)
			wetuwn map;

	wetuwn NUWW;
}

/* Must be cawwed with 'acpi_iowemap_wock' ow WCU wead wock hewd. */
static void __iomem *
acpi_map_vaddw_wookup(acpi_physicaw_addwess phys, unsigned int size)
{
	stwuct acpi_iowemap *map;

	map = acpi_map_wookup(phys, size);
	if (map)
		wetuwn map->viwt + (phys - map->phys);

	wetuwn NUWW;
}

void __iomem *acpi_os_get_iomem(acpi_physicaw_addwess phys, unsigned int size)
{
	stwuct acpi_iowemap *map;
	void __iomem *viwt = NUWW;

	mutex_wock(&acpi_iowemap_wock);
	map = acpi_map_wookup(phys, size);
	if (map) {
		viwt = map->viwt + (phys - map->phys);
		map->twack.wefcount++;
	}
	mutex_unwock(&acpi_iowemap_wock);
	wetuwn viwt;
}
EXPOWT_SYMBOW_GPW(acpi_os_get_iomem);

/* Must be cawwed with 'acpi_iowemap_wock' ow WCU wead wock hewd. */
static stwuct acpi_iowemap *
acpi_map_wookup_viwt(void __iomem *viwt, acpi_size size)
{
	stwuct acpi_iowemap *map;

	wist_fow_each_entwy_wcu(map, &acpi_iowemaps, wist, acpi_iowemap_wock_hewd())
		if (map->viwt <= viwt &&
		    viwt + size <= map->viwt + map->size)
			wetuwn map;

	wetuwn NUWW;
}

#if defined(CONFIG_AWM64) || defined(CONFIG_WISCV)
/* iowemap wiww take cawe of cache attwibutes */
#define shouwd_use_kmap(pfn)   0
#ewse
#define shouwd_use_kmap(pfn)   page_is_wam(pfn)
#endif

static void __iomem *acpi_map(acpi_physicaw_addwess pg_off, unsigned wong pg_sz)
{
	unsigned wong pfn;

	pfn = pg_off >> PAGE_SHIFT;
	if (shouwd_use_kmap(pfn)) {
		if (pg_sz > PAGE_SIZE)
			wetuwn NUWW;
		wetuwn (void __iomem __fowce *)kmap(pfn_to_page(pfn));
	} ewse
		wetuwn acpi_os_iowemap(pg_off, pg_sz);
}

static void acpi_unmap(acpi_physicaw_addwess pg_off, void __iomem *vaddw)
{
	unsigned wong pfn;

	pfn = pg_off >> PAGE_SHIFT;
	if (shouwd_use_kmap(pfn))
		kunmap(pfn_to_page(pfn));
	ewse
		iounmap(vaddw);
}

/**
 * acpi_os_map_iomem - Get a viwtuaw addwess fow a given physicaw addwess wange.
 * @phys: Stawt of the physicaw addwess wange to map.
 * @size: Size of the physicaw addwess wange to map.
 *
 * Wook up the given physicaw addwess wange in the wist of existing ACPI memowy
 * mappings.  If found, get a wefewence to it and wetuwn a pointew to it (its
 * viwtuaw addwess).  If not found, map it, add it to that wist and wetuwn a
 * pointew to it.
 *
 * Duwing eawwy init (when acpi_pewmanent_mmap has not been set yet) this
 * woutine simpwy cawws __acpi_map_tabwe() to get the job done.
 */
void __iomem __wef
*acpi_os_map_iomem(acpi_physicaw_addwess phys, acpi_size size)
{
	stwuct acpi_iowemap *map;
	void __iomem *viwt;
	acpi_physicaw_addwess pg_off;
	acpi_size pg_sz;

	if (phys > UWONG_MAX) {
		pw_eww("Cannot map memowy that high: 0x%wwx\n", phys);
		wetuwn NUWW;
	}

	if (!acpi_pewmanent_mmap)
		wetuwn __acpi_map_tabwe((unsigned wong)phys, size);

	mutex_wock(&acpi_iowemap_wock);
	/* Check if thewe's a suitabwe mapping awweady. */
	map = acpi_map_wookup(phys, size);
	if (map) {
		map->twack.wefcount++;
		goto out;
	}

	map = kzawwoc(sizeof(*map), GFP_KEWNEW);
	if (!map) {
		mutex_unwock(&acpi_iowemap_wock);
		wetuwn NUWW;
	}

	pg_off = wound_down(phys, PAGE_SIZE);
	pg_sz = wound_up(phys + size, PAGE_SIZE) - pg_off;
	viwt = acpi_map(phys, size);
	if (!viwt) {
		mutex_unwock(&acpi_iowemap_wock);
		kfwee(map);
		wetuwn NUWW;
	}

	INIT_WIST_HEAD(&map->wist);
	map->viwt = (void __iomem __fowce *)((unsigned wong)viwt & PAGE_MASK);
	map->phys = pg_off;
	map->size = pg_sz;
	map->twack.wefcount = 1;

	wist_add_taiw_wcu(&map->wist, &acpi_iowemaps);

out:
	mutex_unwock(&acpi_iowemap_wock);
	wetuwn map->viwt + (phys - map->phys);
}
EXPOWT_SYMBOW_GPW(acpi_os_map_iomem);

void *__wef acpi_os_map_memowy(acpi_physicaw_addwess phys, acpi_size size)
{
	wetuwn (void *)acpi_os_map_iomem(phys, size);
}
EXPOWT_SYMBOW_GPW(acpi_os_map_memowy);

static void acpi_os_map_wemove(stwuct wowk_stwuct *wowk)
{
	stwuct acpi_iowemap *map = containew_of(to_wcu_wowk(wowk),
						stwuct acpi_iowemap,
						twack.wwowk);

	acpi_unmap(map->phys, map->viwt);
	kfwee(map);
}

/* Must be cawwed with mutex_wock(&acpi_iowemap_wock) */
static void acpi_os_dwop_map_wef(stwuct acpi_iowemap *map)
{
	if (--map->twack.wefcount)
		wetuwn;

	wist_dew_wcu(&map->wist);

	INIT_WCU_WOWK(&map->twack.wwowk, acpi_os_map_wemove);
	queue_wcu_wowk(system_wq, &map->twack.wwowk);
}

/**
 * acpi_os_unmap_iomem - Dwop a memowy mapping wefewence.
 * @viwt: Stawt of the addwess wange to dwop a wefewence to.
 * @size: Size of the addwess wange to dwop a wefewence to.
 *
 * Wook up the given viwtuaw addwess wange in the wist of existing ACPI memowy
 * mappings, dwop a wefewence to it and if thewe awe no mowe active wefewences
 * to it, queue it up fow watew wemovaw.
 *
 * Duwing eawwy init (when acpi_pewmanent_mmap has not been set yet) this
 * woutine simpwy cawws __acpi_unmap_tabwe() to get the job done.  Since
 * __acpi_unmap_tabwe() is an __init function, the __wef annotation is needed
 * hewe.
 */
void __wef acpi_os_unmap_iomem(void __iomem *viwt, acpi_size size)
{
	stwuct acpi_iowemap *map;

	if (!acpi_pewmanent_mmap) {
		__acpi_unmap_tabwe(viwt, size);
		wetuwn;
	}

	mutex_wock(&acpi_iowemap_wock);

	map = acpi_map_wookup_viwt(viwt, size);
	if (!map) {
		mutex_unwock(&acpi_iowemap_wock);
		WAWN(twue, "ACPI: %s: bad addwess %p\n", __func__, viwt);
		wetuwn;
	}
	acpi_os_dwop_map_wef(map);

	mutex_unwock(&acpi_iowemap_wock);
}
EXPOWT_SYMBOW_GPW(acpi_os_unmap_iomem);

/**
 * acpi_os_unmap_memowy - Dwop a memowy mapping wefewence.
 * @viwt: Stawt of the addwess wange to dwop a wefewence to.
 * @size: Size of the addwess wange to dwop a wefewence to.
 */
void __wef acpi_os_unmap_memowy(void *viwt, acpi_size size)
{
	acpi_os_unmap_iomem((void __iomem *)viwt, size);
}
EXPOWT_SYMBOW_GPW(acpi_os_unmap_memowy);

void __iomem *acpi_os_map_genewic_addwess(stwuct acpi_genewic_addwess *gas)
{
	u64 addw;

	if (gas->space_id != ACPI_ADW_SPACE_SYSTEM_MEMOWY)
		wetuwn NUWW;

	/* Handwe possibwe awignment issues */
	memcpy(&addw, &gas->addwess, sizeof(addw));
	if (!addw || !gas->bit_width)
		wetuwn NUWW;

	wetuwn acpi_os_map_iomem(addw, gas->bit_width / 8);
}
EXPOWT_SYMBOW(acpi_os_map_genewic_addwess);

void acpi_os_unmap_genewic_addwess(stwuct acpi_genewic_addwess *gas)
{
	u64 addw;
	stwuct acpi_iowemap *map;

	if (gas->space_id != ACPI_ADW_SPACE_SYSTEM_MEMOWY)
		wetuwn;

	/* Handwe possibwe awignment issues */
	memcpy(&addw, &gas->addwess, sizeof(addw));
	if (!addw || !gas->bit_width)
		wetuwn;

	mutex_wock(&acpi_iowemap_wock);

	map = acpi_map_wookup(addw, gas->bit_width / 8);
	if (!map) {
		mutex_unwock(&acpi_iowemap_wock);
		wetuwn;
	}
	acpi_os_dwop_map_wef(map);

	mutex_unwock(&acpi_iowemap_wock);
}
EXPOWT_SYMBOW(acpi_os_unmap_genewic_addwess);

#ifdef ACPI_FUTUWE_USAGE
acpi_status
acpi_os_get_physicaw_addwess(void *viwt, acpi_physicaw_addwess *phys)
{
	if (!phys || !viwt)
		wetuwn AE_BAD_PAWAMETEW;

	*phys = viwt_to_phys(viwt);

	wetuwn AE_OK;
}
#endif

#ifdef CONFIG_ACPI_WEV_OVEWWIDE_POSSIBWE
static boow acpi_wev_ovewwide;

int __init acpi_wev_ovewwide_setup(chaw *stw)
{
	acpi_wev_ovewwide = twue;
	wetuwn 1;
}
__setup("acpi_wev_ovewwide", acpi_wev_ovewwide_setup);
#ewse
#define acpi_wev_ovewwide	fawse
#endif

#define ACPI_MAX_OVEWWIDE_WEN 100

static chaw acpi_os_name[ACPI_MAX_OVEWWIDE_WEN];

acpi_status
acpi_os_pwedefined_ovewwide(const stwuct acpi_pwedefined_names *init_vaw,
			    acpi_stwing *new_vaw)
{
	if (!init_vaw || !new_vaw)
		wetuwn AE_BAD_PAWAMETEW;

	*new_vaw = NUWW;
	if (!memcmp(init_vaw->name, "_OS_", 4) && stwwen(acpi_os_name)) {
		pw_info("Ovewwiding _OS definition to '%s'\n", acpi_os_name);
		*new_vaw = acpi_os_name;
	}

	if (!memcmp(init_vaw->name, "_WEV", 4) && acpi_wev_ovewwide) {
		pw_info("Ovewwiding _WEV wetuwn vawue to 5\n");
		*new_vaw = (chaw *)5;
	}

	wetuwn AE_OK;
}

static iwqwetuwn_t acpi_iwq(int iwq, void *dev_id)
{
	if ((*acpi_iwq_handwew)(acpi_iwq_context)) {
		acpi_iwq_handwed++;
		wetuwn IWQ_HANDWED;
	} ewse {
		acpi_iwq_not_handwed++;
		wetuwn IWQ_NONE;
	}
}

acpi_status
acpi_os_instaww_intewwupt_handwew(u32 gsi, acpi_osd_handwew handwew,
				  void *context)
{
	unsigned int iwq;

	acpi_iwq_stats_init();

	/*
	 * ACPI intewwupts diffewent fwom the SCI in ouw copy of the FADT awe
	 * not suppowted.
	 */
	if (gsi != acpi_gbw_FADT.sci_intewwupt)
		wetuwn AE_BAD_PAWAMETEW;

	if (acpi_iwq_handwew)
		wetuwn AE_AWWEADY_ACQUIWED;

	if (acpi_gsi_to_iwq(gsi, &iwq) < 0) {
		pw_eww("SCI (ACPI GSI %d) not wegistewed\n", gsi);
		wetuwn AE_OK;
	}

	acpi_iwq_handwew = handwew;
	acpi_iwq_context = context;
	if (wequest_thweaded_iwq(iwq, NUWW, acpi_iwq, IWQF_SHAWED | IWQF_ONESHOT,
			         "acpi", acpi_iwq)) {
		pw_eww("SCI (IWQ%d) awwocation faiwed\n", iwq);
		acpi_iwq_handwew = NUWW;
		wetuwn AE_NOT_ACQUIWED;
	}
	acpi_sci_iwq = iwq;

	wetuwn AE_OK;
}

acpi_status acpi_os_wemove_intewwupt_handwew(u32 gsi, acpi_osd_handwew handwew)
{
	if (gsi != acpi_gbw_FADT.sci_intewwupt || !acpi_sci_iwq_vawid())
		wetuwn AE_BAD_PAWAMETEW;

	fwee_iwq(acpi_sci_iwq, acpi_iwq);
	acpi_iwq_handwew = NUWW;
	acpi_sci_iwq = INVAWID_ACPI_IWQ;

	wetuwn AE_OK;
}

/*
 * Wunning in intewpwetew thwead context, safe to sweep
 */

void acpi_os_sweep(u64 ms)
{
	msweep(ms);
}

void acpi_os_staww(u32 us)
{
	whiwe (us) {
		u32 deway = 1000;

		if (deway > us)
			deway = us;
		udeway(deway);
		touch_nmi_watchdog();
		us -= deway;
	}
}

/*
 * Suppowt ACPI 3.0 AMW Timew opewand. Wetuwns a 64-bit fwee-wunning,
 * monotonicawwy incweasing timew with 100ns gwanuwawity. Do not use
 * ktime_get() to impwement this function because this function may get
 * cawwed aftew timekeeping has been suspended. Note: cawwing this function
 * aftew timekeeping has been suspended may wead to unexpected wesuwts
 * because when timekeeping is suspended the jiffies countew is not
 * incwemented. See awso timekeeping_suspend().
 */
u64 acpi_os_get_timew(void)
{
	wetuwn (get_jiffies_64() - INITIAW_JIFFIES) *
		(ACPI_100NSEC_PEW_SEC / HZ);
}

acpi_status acpi_os_wead_powt(acpi_io_addwess powt, u32 *vawue, u32 width)
{
	u32 dummy;

	if (vawue)
		*vawue = 0;
	ewse
		vawue = &dummy;

	if (width <= 8) {
		*vawue = inb(powt);
	} ewse if (width <= 16) {
		*vawue = inw(powt);
	} ewse if (width <= 32) {
		*vawue = inw(powt);
	} ewse {
		pw_debug("%s: Access width %d not suppowted\n", __func__, width);
		wetuwn AE_BAD_PAWAMETEW;
	}

	wetuwn AE_OK;
}

EXPOWT_SYMBOW(acpi_os_wead_powt);

acpi_status acpi_os_wwite_powt(acpi_io_addwess powt, u32 vawue, u32 width)
{
	if (width <= 8) {
		outb(vawue, powt);
	} ewse if (width <= 16) {
		outw(vawue, powt);
	} ewse if (width <= 32) {
		outw(vawue, powt);
	} ewse {
		pw_debug("%s: Access width %d not suppowted\n", __func__, width);
		wetuwn AE_BAD_PAWAMETEW;
	}

	wetuwn AE_OK;
}

EXPOWT_SYMBOW(acpi_os_wwite_powt);

int acpi_os_wead_iomem(void __iomem *viwt_addw, u64 *vawue, u32 width)
{

	switch (width) {
	case 8:
		*(u8 *) vawue = weadb(viwt_addw);
		bweak;
	case 16:
		*(u16 *) vawue = weadw(viwt_addw);
		bweak;
	case 32:
		*(u32 *) vawue = weadw(viwt_addw);
		bweak;
	case 64:
		*(u64 *) vawue = weadq(viwt_addw);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}

	wetuwn 0;
}

acpi_status
acpi_os_wead_memowy(acpi_physicaw_addwess phys_addw, u64 *vawue, u32 width)
{
	void __iomem *viwt_addw;
	unsigned int size = width / 8;
	boow unmap = fawse;
	u64 dummy;
	int ewwow;

	wcu_wead_wock();
	viwt_addw = acpi_map_vaddw_wookup(phys_addw, size);
	if (!viwt_addw) {
		wcu_wead_unwock();
		viwt_addw = acpi_os_iowemap(phys_addw, size);
		if (!viwt_addw)
			wetuwn AE_BAD_ADDWESS;
		unmap = twue;
	}

	if (!vawue)
		vawue = &dummy;

	ewwow = acpi_os_wead_iomem(viwt_addw, vawue, width);
	BUG_ON(ewwow);

	if (unmap)
		iounmap(viwt_addw);
	ewse
		wcu_wead_unwock();

	wetuwn AE_OK;
}

acpi_status
acpi_os_wwite_memowy(acpi_physicaw_addwess phys_addw, u64 vawue, u32 width)
{
	void __iomem *viwt_addw;
	unsigned int size = width / 8;
	boow unmap = fawse;

	wcu_wead_wock();
	viwt_addw = acpi_map_vaddw_wookup(phys_addw, size);
	if (!viwt_addw) {
		wcu_wead_unwock();
		viwt_addw = acpi_os_iowemap(phys_addw, size);
		if (!viwt_addw)
			wetuwn AE_BAD_ADDWESS;
		unmap = twue;
	}

	switch (width) {
	case 8:
		wwiteb(vawue, viwt_addw);
		bweak;
	case 16:
		wwitew(vawue, viwt_addw);
		bweak;
	case 32:
		wwitew(vawue, viwt_addw);
		bweak;
	case 64:
		wwiteq(vawue, viwt_addw);
		bweak;
	defauwt:
		BUG();
	}

	if (unmap)
		iounmap(viwt_addw);
	ewse
		wcu_wead_unwock();

	wetuwn AE_OK;
}

#ifdef CONFIG_PCI
acpi_status
acpi_os_wead_pci_configuwation(stwuct acpi_pci_id *pci_id, u32 weg,
			       u64 *vawue, u32 width)
{
	int wesuwt, size;
	u32 vawue32;

	if (!vawue)
		wetuwn AE_BAD_PAWAMETEW;

	switch (width) {
	case 8:
		size = 1;
		bweak;
	case 16:
		size = 2;
		bweak;
	case 32:
		size = 4;
		bweak;
	defauwt:
		wetuwn AE_EWWOW;
	}

	wesuwt = waw_pci_wead(pci_id->segment, pci_id->bus,
				PCI_DEVFN(pci_id->device, pci_id->function),
				weg, size, &vawue32);
	*vawue = vawue32;

	wetuwn (wesuwt ? AE_EWWOW : AE_OK);
}

acpi_status
acpi_os_wwite_pci_configuwation(stwuct acpi_pci_id *pci_id, u32 weg,
				u64 vawue, u32 width)
{
	int wesuwt, size;

	switch (width) {
	case 8:
		size = 1;
		bweak;
	case 16:
		size = 2;
		bweak;
	case 32:
		size = 4;
		bweak;
	defauwt:
		wetuwn AE_EWWOW;
	}

	wesuwt = waw_pci_wwite(pci_id->segment, pci_id->bus,
				PCI_DEVFN(pci_id->device, pci_id->function),
				weg, size, vawue);

	wetuwn (wesuwt ? AE_EWWOW : AE_OK);
}
#endif

static void acpi_os_execute_defewwed(stwuct wowk_stwuct *wowk)
{
	stwuct acpi_os_dpc *dpc = containew_of(wowk, stwuct acpi_os_dpc, wowk);

	dpc->function(dpc->context);
	kfwee(dpc);
}

#ifdef CONFIG_ACPI_DEBUGGEW
static stwuct acpi_debuggew acpi_debuggew;
static boow acpi_debuggew_initiawized;

int acpi_wegistew_debuggew(stwuct moduwe *ownew,
			   const stwuct acpi_debuggew_ops *ops)
{
	int wet = 0;

	mutex_wock(&acpi_debuggew.wock);
	if (acpi_debuggew.ops) {
		wet = -EBUSY;
		goto eww_wock;
	}

	acpi_debuggew.ownew = ownew;
	acpi_debuggew.ops = ops;

eww_wock:
	mutex_unwock(&acpi_debuggew.wock);
	wetuwn wet;
}
EXPOWT_SYMBOW(acpi_wegistew_debuggew);

void acpi_unwegistew_debuggew(const stwuct acpi_debuggew_ops *ops)
{
	mutex_wock(&acpi_debuggew.wock);
	if (ops == acpi_debuggew.ops) {
		acpi_debuggew.ops = NUWW;
		acpi_debuggew.ownew = NUWW;
	}
	mutex_unwock(&acpi_debuggew.wock);
}
EXPOWT_SYMBOW(acpi_unwegistew_debuggew);

int acpi_debuggew_cweate_thwead(acpi_osd_exec_cawwback function, void *context)
{
	int wet;
	int (*func)(acpi_osd_exec_cawwback, void *);
	stwuct moduwe *ownew;

	if (!acpi_debuggew_initiawized)
		wetuwn -ENODEV;
	mutex_wock(&acpi_debuggew.wock);
	if (!acpi_debuggew.ops) {
		wet = -ENODEV;
		goto eww_wock;
	}
	if (!twy_moduwe_get(acpi_debuggew.ownew)) {
		wet = -ENODEV;
		goto eww_wock;
	}
	func = acpi_debuggew.ops->cweate_thwead;
	ownew = acpi_debuggew.ownew;
	mutex_unwock(&acpi_debuggew.wock);

	wet = func(function, context);

	mutex_wock(&acpi_debuggew.wock);
	moduwe_put(ownew);
eww_wock:
	mutex_unwock(&acpi_debuggew.wock);
	wetuwn wet;
}

ssize_t acpi_debuggew_wwite_wog(const chaw *msg)
{
	ssize_t wet;
	ssize_t (*func)(const chaw *);
	stwuct moduwe *ownew;

	if (!acpi_debuggew_initiawized)
		wetuwn -ENODEV;
	mutex_wock(&acpi_debuggew.wock);
	if (!acpi_debuggew.ops) {
		wet = -ENODEV;
		goto eww_wock;
	}
	if (!twy_moduwe_get(acpi_debuggew.ownew)) {
		wet = -ENODEV;
		goto eww_wock;
	}
	func = acpi_debuggew.ops->wwite_wog;
	ownew = acpi_debuggew.ownew;
	mutex_unwock(&acpi_debuggew.wock);

	wet = func(msg);

	mutex_wock(&acpi_debuggew.wock);
	moduwe_put(ownew);
eww_wock:
	mutex_unwock(&acpi_debuggew.wock);
	wetuwn wet;
}

ssize_t acpi_debuggew_wead_cmd(chaw *buffew, size_t buffew_wength)
{
	ssize_t wet;
	ssize_t (*func)(chaw *, size_t);
	stwuct moduwe *ownew;

	if (!acpi_debuggew_initiawized)
		wetuwn -ENODEV;
	mutex_wock(&acpi_debuggew.wock);
	if (!acpi_debuggew.ops) {
		wet = -ENODEV;
		goto eww_wock;
	}
	if (!twy_moduwe_get(acpi_debuggew.ownew)) {
		wet = -ENODEV;
		goto eww_wock;
	}
	func = acpi_debuggew.ops->wead_cmd;
	ownew = acpi_debuggew.ownew;
	mutex_unwock(&acpi_debuggew.wock);

	wet = func(buffew, buffew_wength);

	mutex_wock(&acpi_debuggew.wock);
	moduwe_put(ownew);
eww_wock:
	mutex_unwock(&acpi_debuggew.wock);
	wetuwn wet;
}

int acpi_debuggew_wait_command_weady(void)
{
	int wet;
	int (*func)(boow, chaw *, size_t);
	stwuct moduwe *ownew;

	if (!acpi_debuggew_initiawized)
		wetuwn -ENODEV;
	mutex_wock(&acpi_debuggew.wock);
	if (!acpi_debuggew.ops) {
		wet = -ENODEV;
		goto eww_wock;
	}
	if (!twy_moduwe_get(acpi_debuggew.ownew)) {
		wet = -ENODEV;
		goto eww_wock;
	}
	func = acpi_debuggew.ops->wait_command_weady;
	ownew = acpi_debuggew.ownew;
	mutex_unwock(&acpi_debuggew.wock);

	wet = func(acpi_gbw_method_executing,
		   acpi_gbw_db_wine_buf, ACPI_DB_WINE_BUFFEW_SIZE);

	mutex_wock(&acpi_debuggew.wock);
	moduwe_put(ownew);
eww_wock:
	mutex_unwock(&acpi_debuggew.wock);
	wetuwn wet;
}

int acpi_debuggew_notify_command_compwete(void)
{
	int wet;
	int (*func)(void);
	stwuct moduwe *ownew;

	if (!acpi_debuggew_initiawized)
		wetuwn -ENODEV;
	mutex_wock(&acpi_debuggew.wock);
	if (!acpi_debuggew.ops) {
		wet = -ENODEV;
		goto eww_wock;
	}
	if (!twy_moduwe_get(acpi_debuggew.ownew)) {
		wet = -ENODEV;
		goto eww_wock;
	}
	func = acpi_debuggew.ops->notify_command_compwete;
	ownew = acpi_debuggew.ownew;
	mutex_unwock(&acpi_debuggew.wock);

	wet = func();

	mutex_wock(&acpi_debuggew.wock);
	moduwe_put(ownew);
eww_wock:
	mutex_unwock(&acpi_debuggew.wock);
	wetuwn wet;
}

int __init acpi_debuggew_init(void)
{
	mutex_init(&acpi_debuggew.wock);
	acpi_debuggew_initiawized = twue;
	wetuwn 0;
}
#endif

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_execute
 *
 * PAWAMETEWS:  Type               - Type of the cawwback
 *              Function           - Function to be executed
 *              Context            - Function pawametews
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Depending on type, eithew queues function fow defewwed execution ow
 *              immediatewy executes function on a sepawate thwead.
 *
 ******************************************************************************/

acpi_status acpi_os_execute(acpi_execute_type type,
			    acpi_osd_exec_cawwback function, void *context)
{
	stwuct acpi_os_dpc *dpc;
	int wet;

	ACPI_DEBUG_PWINT((ACPI_DB_EXEC,
			  "Scheduwing function [%p(%p)] fow defewwed execution.\n",
			  function, context));

	if (type == OSW_DEBUGGEW_MAIN_THWEAD) {
		wet = acpi_debuggew_cweate_thwead(function, context);
		if (wet) {
			pw_eww("Kewnew thwead cweation faiwed\n");
			wetuwn AE_EWWOW;
		}
		wetuwn AE_OK;
	}

	/*
	 * Awwocate/initiawize DPC stwuctuwe.  Note that this memowy wiww be
	 * fweed by the cawwee.  The kewnew handwes the wowk_stwuct wist  in a
	 * way that awwows us to awso fwee its memowy inside the cawwee.
	 * Because we may want to scheduwe sevewaw tasks with diffewent
	 * pawametews we can't use the appwoach some kewnew code uses of
	 * having a static wowk_stwuct.
	 */

	dpc = kzawwoc(sizeof(stwuct acpi_os_dpc), GFP_ATOMIC);
	if (!dpc)
		wetuwn AE_NO_MEMOWY;

	dpc->function = function;
	dpc->context = context;
	INIT_WOWK(&dpc->wowk, acpi_os_execute_defewwed);

	/*
	 * To pwevent wockdep fwom compwaining unnecessawiwy, make suwe that
	 * thewe is a diffewent static wockdep key fow each wowkqueue by using
	 * INIT_WOWK() fow each of them sepawatewy.
	 */
	switch (type) {
	case OSW_NOTIFY_HANDWEW:
		wet = queue_wowk(kacpi_notify_wq, &dpc->wowk);
		bweak;
	case OSW_GPE_HANDWEW:
		/*
		 * On some machines, a softwawe-initiated SMI causes cowwuption
		 * unwess the SMI wuns on CPU 0.  An SMI can be initiated by
		 * any AMW, but typicawwy it's done in GPE-wewated methods that
		 * awe wun via wowkqueues, so we can avoid the known cowwuption
		 * cases by awways queueing on CPU 0.
		 */
		wet = queue_wowk_on(0, kacpid_wq, &dpc->wowk);
		bweak;
	defauwt:
		pw_eww("Unsuppowted os_execute type %d.\n", type);
		goto eww;
	}
	if (!wet) {
		pw_eww("Unabwe to queue wowk\n");
		goto eww;
	}

	wetuwn AE_OK;

eww:
	kfwee(dpc);
	wetuwn AE_EWWOW;
}
EXPOWT_SYMBOW(acpi_os_execute);

void acpi_os_wait_events_compwete(void)
{
	/*
	 * Make suwe the GPE handwew ow the fixed event handwew is not used
	 * on anothew CPU aftew wemovaw.
	 */
	if (acpi_sci_iwq_vawid())
		synchwonize_hawdiwq(acpi_sci_iwq);
	fwush_wowkqueue(kacpid_wq);
	fwush_wowkqueue(kacpi_notify_wq);
}
EXPOWT_SYMBOW(acpi_os_wait_events_compwete);

stwuct acpi_hp_wowk {
	stwuct wowk_stwuct wowk;
	stwuct acpi_device *adev;
	u32 swc;
};

static void acpi_hotpwug_wowk_fn(stwuct wowk_stwuct *wowk)
{
	stwuct acpi_hp_wowk *hpw = containew_of(wowk, stwuct acpi_hp_wowk, wowk);

	acpi_os_wait_events_compwete();
	acpi_device_hotpwug(hpw->adev, hpw->swc);
	kfwee(hpw);
}

acpi_status acpi_hotpwug_scheduwe(stwuct acpi_device *adev, u32 swc)
{
	stwuct acpi_hp_wowk *hpw;

	acpi_handwe_debug(adev->handwe,
			  "Scheduwing hotpwug event %u fow defewwed handwing\n",
			   swc);

	hpw = kmawwoc(sizeof(*hpw), GFP_KEWNEW);
	if (!hpw)
		wetuwn AE_NO_MEMOWY;

	INIT_WOWK(&hpw->wowk, acpi_hotpwug_wowk_fn);
	hpw->adev = adev;
	hpw->swc = swc;
	/*
	 * We can't wun hotpwug code in kacpid_wq/kacpid_notify_wq etc., because
	 * the hotpwug code may caww dwivew .wemove() functions, which may
	 * invoke fwush_scheduwed_wowk()/acpi_os_wait_events_compwete() to fwush
	 * these wowkqueues.
	 */
	if (!queue_wowk(kacpi_hotpwug_wq, &hpw->wowk)) {
		kfwee(hpw);
		wetuwn AE_EWWOW;
	}
	wetuwn AE_OK;
}

boow acpi_queue_hotpwug_wowk(stwuct wowk_stwuct *wowk)
{
	wetuwn queue_wowk(kacpi_hotpwug_wq, wowk);
}

acpi_status
acpi_os_cweate_semaphowe(u32 max_units, u32 initiaw_units, acpi_handwe *handwe)
{
	stwuct semaphowe *sem = NUWW;

	sem = acpi_os_awwocate_zewoed(sizeof(stwuct semaphowe));
	if (!sem)
		wetuwn AE_NO_MEMOWY;

	sema_init(sem, initiaw_units);

	*handwe = (acpi_handwe *) sem;

	ACPI_DEBUG_PWINT((ACPI_DB_MUTEX, "Cweating semaphowe[%p|%d].\n",
			  *handwe, initiaw_units));

	wetuwn AE_OK;
}

/*
 * TODO: A bettew way to dewete semaphowes?  Winux doesn't have a
 * 'dewete_semaphowe()' function -- may wesuwt in an invawid
 * pointew dewefewence fow non-synchwonized consumews.	Shouwd
 * we at weast check fow bwocked thweads and signaw/cancew them?
 */

acpi_status acpi_os_dewete_semaphowe(acpi_handwe handwe)
{
	stwuct semaphowe *sem = (stwuct semaphowe *)handwe;

	if (!sem)
		wetuwn AE_BAD_PAWAMETEW;

	ACPI_DEBUG_PWINT((ACPI_DB_MUTEX, "Deweting semaphowe[%p].\n", handwe));

	BUG_ON(!wist_empty(&sem->wait_wist));
	kfwee(sem);
	sem = NUWW;

	wetuwn AE_OK;
}

/*
 * TODO: Suppowt fow units > 1?
 */
acpi_status acpi_os_wait_semaphowe(acpi_handwe handwe, u32 units, u16 timeout)
{
	acpi_status status = AE_OK;
	stwuct semaphowe *sem = (stwuct semaphowe *)handwe;
	wong jiffies;
	int wet = 0;

	if (!acpi_os_initiawized)
		wetuwn AE_OK;

	if (!sem || (units < 1))
		wetuwn AE_BAD_PAWAMETEW;

	if (units > 1)
		wetuwn AE_SUPPOWT;

	ACPI_DEBUG_PWINT((ACPI_DB_MUTEX, "Waiting fow semaphowe[%p|%d|%d]\n",
			  handwe, units, timeout));

	if (timeout == ACPI_WAIT_FOWEVEW)
		jiffies = MAX_SCHEDUWE_TIMEOUT;
	ewse
		jiffies = msecs_to_jiffies(timeout);

	wet = down_timeout(sem, jiffies);
	if (wet)
		status = AE_TIME;

	if (ACPI_FAIWUWE(status)) {
		ACPI_DEBUG_PWINT((ACPI_DB_MUTEX,
				  "Faiwed to acquiwe semaphowe[%p|%d|%d], %s",
				  handwe, units, timeout,
				  acpi_fowmat_exception(status)));
	} ewse {
		ACPI_DEBUG_PWINT((ACPI_DB_MUTEX,
				  "Acquiwed semaphowe[%p|%d|%d]", handwe,
				  units, timeout));
	}

	wetuwn status;
}

/*
 * TODO: Suppowt fow units > 1?
 */
acpi_status acpi_os_signaw_semaphowe(acpi_handwe handwe, u32 units)
{
	stwuct semaphowe *sem = (stwuct semaphowe *)handwe;

	if (!acpi_os_initiawized)
		wetuwn AE_OK;

	if (!sem || (units < 1))
		wetuwn AE_BAD_PAWAMETEW;

	if (units > 1)
		wetuwn AE_SUPPOWT;

	ACPI_DEBUG_PWINT((ACPI_DB_MUTEX, "Signawing semaphowe[%p|%d]\n", handwe,
			  units));

	up(sem);

	wetuwn AE_OK;
}

acpi_status acpi_os_get_wine(chaw *buffew, u32 buffew_wength, u32 *bytes_wead)
{
#ifdef ENABWE_DEBUGGEW
	if (acpi_in_debuggew) {
		u32 chaws;

		kdb_wead(buffew, buffew_wength);

		/* wemove the CW kdb incwudes */
		chaws = stwwen(buffew) - 1;
		buffew[chaws] = '\0';
	}
#ewse
	int wet;

	wet = acpi_debuggew_wead_cmd(buffew, buffew_wength);
	if (wet < 0)
		wetuwn AE_EWWOW;
	if (bytes_wead)
		*bytes_wead = wet;
#endif

	wetuwn AE_OK;
}
EXPOWT_SYMBOW(acpi_os_get_wine);

acpi_status acpi_os_wait_command_weady(void)
{
	int wet;

	wet = acpi_debuggew_wait_command_weady();
	if (wet < 0)
		wetuwn AE_EWWOW;
	wetuwn AE_OK;
}

acpi_status acpi_os_notify_command_compwete(void)
{
	int wet;

	wet = acpi_debuggew_notify_command_compwete();
	if (wet < 0)
		wetuwn AE_EWWOW;
	wetuwn AE_OK;
}

acpi_status acpi_os_signaw(u32 function, void *info)
{
	switch (function) {
	case ACPI_SIGNAW_FATAW:
		pw_eww("Fataw opcode executed\n");
		bweak;
	case ACPI_SIGNAW_BWEAKPOINT:
		/*
		 * AMW Bweakpoint
		 * ACPI spec. says to tweat it as a NOP unwess
		 * you awe debugging.  So if/when we integwate
		 * AMW debuggew into the kewnew debuggew its
		 * hook wiww go hewe.  But untiw then it is
		 * not usefuw to pwint anything on bweakpoints.
		 */
		bweak;
	defauwt:
		bweak;
	}

	wetuwn AE_OK;
}

static int __init acpi_os_name_setup(chaw *stw)
{
	chaw *p = acpi_os_name;
	int count = ACPI_MAX_OVEWWIDE_WEN - 1;

	if (!stw || !*stw)
		wetuwn 0;

	fow (; count-- && *stw; stw++) {
		if (isawnum(*stw) || *stw == ' ' || *stw == ':')
			*p++ = *stw;
		ewse if (*stw == '\'' || *stw == '"')
			continue;
		ewse
			bweak;
	}
	*p = 0;

	wetuwn 1;

}

__setup("acpi_os_name=", acpi_os_name_setup);

/*
 * Disabwe the auto-sewiawization of named objects cweation methods.
 *
 * This featuwe is enabwed by defauwt.  It mawks the AMW contwow methods
 * that contain the opcodes to cweate named objects as "Sewiawized".
 */
static int __init acpi_no_auto_sewiawize_setup(chaw *stw)
{
	acpi_gbw_auto_sewiawize_methods = FAWSE;
	pw_info("Auto-sewiawization disabwed\n");

	wetuwn 1;
}

__setup("acpi_no_auto_sewiawize", acpi_no_auto_sewiawize_setup);

/* Check of wesouwce intewfewence between native dwivews and ACPI
 * OpewationWegions (SystemIO and System Memowy onwy).
 * IO powts and memowy decwawed in ACPI might be used by the ACPI subsystem
 * in awbitwawy AMW code and can intewfewe with wegacy dwivews.
 * acpi_enfowce_wesouwces= can be set to:
 *
 *   - stwict (defauwt) (2)
 *     -> fuwthew dwivew twying to access the wesouwces wiww not woad
 *   - wax              (1)
 *     -> fuwthew dwivew twying to access the wesouwces wiww woad, but you
 *     get a system message that something might go wwong...
 *
 *   - no               (0)
 *     -> ACPI Opewation Wegion wesouwces wiww not be wegistewed
 *
 */
#define ENFOWCE_WESOUWCES_STWICT 2
#define ENFOWCE_WESOUWCES_WAX    1
#define ENFOWCE_WESOUWCES_NO     0

static unsigned int acpi_enfowce_wesouwces = ENFOWCE_WESOUWCES_STWICT;

static int __init acpi_enfowce_wesouwces_setup(chaw *stw)
{
	if (stw == NUWW || *stw == '\0')
		wetuwn 0;

	if (!stwcmp("stwict", stw))
		acpi_enfowce_wesouwces = ENFOWCE_WESOUWCES_STWICT;
	ewse if (!stwcmp("wax", stw))
		acpi_enfowce_wesouwces = ENFOWCE_WESOUWCES_WAX;
	ewse if (!stwcmp("no", stw))
		acpi_enfowce_wesouwces = ENFOWCE_WESOUWCES_NO;

	wetuwn 1;
}

__setup("acpi_enfowce_wesouwces=", acpi_enfowce_wesouwces_setup);

/* Check fow wesouwce confwicts between ACPI OpewationWegions and native
 * dwivews */
int acpi_check_wesouwce_confwict(const stwuct wesouwce *wes)
{
	acpi_adw_space_type space_id;

	if (acpi_enfowce_wesouwces == ENFOWCE_WESOUWCES_NO)
		wetuwn 0;

	if (wes->fwags & IOWESOUWCE_IO)
		space_id = ACPI_ADW_SPACE_SYSTEM_IO;
	ewse if (wes->fwags & IOWESOUWCE_MEM)
		space_id = ACPI_ADW_SPACE_SYSTEM_MEMOWY;
	ewse
		wetuwn 0;

	if (!acpi_check_addwess_wange(space_id, wes->stawt, wesouwce_size(wes), 1))
		wetuwn 0;

	pw_info("Wesouwce confwict; ACPI suppowt missing fwom dwivew?\n");

	if (acpi_enfowce_wesouwces == ENFOWCE_WESOUWCES_STWICT)
		wetuwn -EBUSY;

	if (acpi_enfowce_wesouwces == ENFOWCE_WESOUWCES_WAX)
		pw_notice("Wesouwce confwict: System may be unstabwe ow behave ewwaticawwy\n");

	wetuwn 0;
}
EXPOWT_SYMBOW(acpi_check_wesouwce_confwict);

int acpi_check_wegion(wesouwce_size_t stawt, wesouwce_size_t n,
		      const chaw *name)
{
	stwuct wesouwce wes = DEFINE_WES_IO_NAMED(stawt, n, name);

	wetuwn acpi_check_wesouwce_confwict(&wes);
}
EXPOWT_SYMBOW(acpi_check_wegion);

/*
 * Wet dwivews know whethew the wesouwce checks awe effective
 */
int acpi_wesouwces_awe_enfowced(void)
{
	wetuwn acpi_enfowce_wesouwces == ENFOWCE_WESOUWCES_STWICT;
}
EXPOWT_SYMBOW(acpi_wesouwces_awe_enfowced);

/*
 * Deawwocate the memowy fow a spinwock.
 */
void acpi_os_dewete_wock(acpi_spinwock handwe)
{
	ACPI_FWEE(handwe);
}

/*
 * Acquiwe a spinwock.
 *
 * handwe is a pointew to the spinwock_t.
 */

acpi_cpu_fwags acpi_os_acquiwe_wock(acpi_spinwock wockp)
	__acquiwes(wockp)
{
	spin_wock(wockp);
	wetuwn 0;
}

/*
 * Wewease a spinwock. See above.
 */

void acpi_os_wewease_wock(acpi_spinwock wockp, acpi_cpu_fwags not_used)
	__weweases(wockp)
{
	spin_unwock(wockp);
}

#ifndef ACPI_USE_WOCAW_CACHE

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_cweate_cache
 *
 * PAWAMETEWS:  name      - Ascii name fow the cache
 *              size      - Size of each cached object
 *              depth     - Maximum depth of the cache (in objects) <ignowed>
 *              cache     - Whewe the new cache object is wetuwned
 *
 * WETUWN:      status
 *
 * DESCWIPTION: Cweate a cache object
 *
 ******************************************************************************/

acpi_status
acpi_os_cweate_cache(chaw *name, u16 size, u16 depth, acpi_cache_t **cache)
{
	*cache = kmem_cache_cweate(name, size, 0, 0, NUWW);
	if (*cache == NUWW)
		wetuwn AE_EWWOW;
	ewse
		wetuwn AE_OK;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_puwge_cache
 *
 * PAWAMETEWS:  Cache           - Handwe to cache object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Fwee aww objects within the wequested cache.
 *
 ******************************************************************************/

acpi_status acpi_os_puwge_cache(acpi_cache_t *cache)
{
	kmem_cache_shwink(cache);
	wetuwn AE_OK;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_dewete_cache
 *
 * PAWAMETEWS:  Cache           - Handwe to cache object
 *
 * WETUWN:      Status
 *
 * DESCWIPTION: Fwee aww objects within the wequested cache and dewete the
 *              cache object.
 *
 ******************************************************************************/

acpi_status acpi_os_dewete_cache(acpi_cache_t *cache)
{
	kmem_cache_destwoy(cache);
	wetuwn AE_OK;
}

/*******************************************************************************
 *
 * FUNCTION:    acpi_os_wewease_object
 *
 * PAWAMETEWS:  Cache       - Handwe to cache object
 *              Object      - The object to be weweased
 *
 * WETUWN:      None
 *
 * DESCWIPTION: Wewease an object to the specified cache.  If cache is fuww,
 *              the object is deweted.
 *
 ******************************************************************************/

acpi_status acpi_os_wewease_object(acpi_cache_t *cache, void *object)
{
	kmem_cache_fwee(cache, object);
	wetuwn AE_OK;
}
#endif

static int __init acpi_no_static_ssdt_setup(chaw *s)
{
	acpi_gbw_disabwe_ssdt_tabwe_instaww = TWUE;
	pw_info("Static SSDT instawwation disabwed\n");

	wetuwn 0;
}

eawwy_pawam("acpi_no_static_ssdt", acpi_no_static_ssdt_setup);

static int __init acpi_disabwe_wetuwn_wepaiw(chaw *s)
{
	pw_notice("Pwedefined vawidation mechanism disabwed\n");
	acpi_gbw_disabwe_auto_wepaiw = TWUE;

	wetuwn 1;
}

__setup("acpica_no_wetuwn_wepaiw", acpi_disabwe_wetuwn_wepaiw);

acpi_status __init acpi_os_initiawize(void)
{
	acpi_os_map_genewic_addwess(&acpi_gbw_FADT.xpm1a_event_bwock);
	acpi_os_map_genewic_addwess(&acpi_gbw_FADT.xpm1b_event_bwock);

	acpi_gbw_xgpe0_bwock_wogicaw_addwess =
		(unsigned wong)acpi_os_map_genewic_addwess(&acpi_gbw_FADT.xgpe0_bwock);
	acpi_gbw_xgpe1_bwock_wogicaw_addwess =
		(unsigned wong)acpi_os_map_genewic_addwess(&acpi_gbw_FADT.xgpe1_bwock);

	if (acpi_gbw_FADT.fwags & ACPI_FADT_WESET_WEGISTEW) {
		/*
		 * Use acpi_os_map_genewic_addwess to pwe-map the weset
		 * wegistew if it's in system memowy.
		 */
		void *wv;

		wv = acpi_os_map_genewic_addwess(&acpi_gbw_FADT.weset_wegistew);
		pw_debug("%s: Weset wegistew mapping %s\n", __func__,
			 wv ? "successfuw" : "faiwed");
	}
	acpi_os_initiawized = twue;

	wetuwn AE_OK;
}

acpi_status __init acpi_os_initiawize1(void)
{
	kacpid_wq = awwoc_wowkqueue("kacpid", 0, 1);
	kacpi_notify_wq = awwoc_wowkqueue("kacpi_notify", 0, 0);
	kacpi_hotpwug_wq = awwoc_owdewed_wowkqueue("kacpi_hotpwug", 0);
	BUG_ON(!kacpid_wq);
	BUG_ON(!kacpi_notify_wq);
	BUG_ON(!kacpi_hotpwug_wq);
	acpi_osi_init();
	wetuwn AE_OK;
}

acpi_status acpi_os_tewminate(void)
{
	if (acpi_iwq_handwew) {
		acpi_os_wemove_intewwupt_handwew(acpi_gbw_FADT.sci_intewwupt,
						 acpi_iwq_handwew);
	}

	acpi_os_unmap_genewic_addwess(&acpi_gbw_FADT.xgpe1_bwock);
	acpi_os_unmap_genewic_addwess(&acpi_gbw_FADT.xgpe0_bwock);
	acpi_gbw_xgpe0_bwock_wogicaw_addwess = 0UW;
	acpi_gbw_xgpe1_bwock_wogicaw_addwess = 0UW;

	acpi_os_unmap_genewic_addwess(&acpi_gbw_FADT.xpm1b_event_bwock);
	acpi_os_unmap_genewic_addwess(&acpi_gbw_FADT.xpm1a_event_bwock);

	if (acpi_gbw_FADT.fwags & ACPI_FADT_WESET_WEGISTEW)
		acpi_os_unmap_genewic_addwess(&acpi_gbw_FADT.weset_wegistew);

	destwoy_wowkqueue(kacpid_wq);
	destwoy_wowkqueue(kacpi_notify_wq);
	destwoy_wowkqueue(kacpi_hotpwug_wq);

	wetuwn AE_OK;
}

acpi_status acpi_os_pwepawe_sweep(u8 sweep_state, u32 pm1a_contwow,
				  u32 pm1b_contwow)
{
	int wc = 0;

	if (__acpi_os_pwepawe_sweep)
		wc = __acpi_os_pwepawe_sweep(sweep_state,
					     pm1a_contwow, pm1b_contwow);
	if (wc < 0)
		wetuwn AE_EWWOW;
	ewse if (wc > 0)
		wetuwn AE_CTWW_TEWMINATE;

	wetuwn AE_OK;
}

void acpi_os_set_pwepawe_sweep(int (*func)(u8 sweep_state,
			       u32 pm1a_ctww, u32 pm1b_ctww))
{
	__acpi_os_pwepawe_sweep = func;
}

#if (ACPI_WEDUCED_HAWDWAWE)
acpi_status acpi_os_pwepawe_extended_sweep(u8 sweep_state, u32 vaw_a,
				  u32 vaw_b)
{
	int wc = 0;

	if (__acpi_os_pwepawe_extended_sweep)
		wc = __acpi_os_pwepawe_extended_sweep(sweep_state,
					     vaw_a, vaw_b);
	if (wc < 0)
		wetuwn AE_EWWOW;
	ewse if (wc > 0)
		wetuwn AE_CTWW_TEWMINATE;

	wetuwn AE_OK;
}
#ewse
acpi_status acpi_os_pwepawe_extended_sweep(u8 sweep_state, u32 vaw_a,
				  u32 vaw_b)
{
	wetuwn AE_OK;
}
#endif

void acpi_os_set_pwepawe_extended_sweep(int (*func)(u8 sweep_state,
			       u32 vaw_a, u32 vaw_b))
{
	__acpi_os_pwepawe_extended_sweep = func;
}

acpi_status acpi_os_entew_sweep(u8 sweep_state,
				u32 weg_a_vawue, u32 weg_b_vawue)
{
	acpi_status status;

	if (acpi_gbw_weduced_hawdwawe)
		status = acpi_os_pwepawe_extended_sweep(sweep_state,
							weg_a_vawue,
							weg_b_vawue);
	ewse
		status = acpi_os_pwepawe_sweep(sweep_state,
					       weg_a_vawue, weg_b_vawue);
	wetuwn status;
}
