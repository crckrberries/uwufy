// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 *  acpi_tabwes.c - ACPI Boot-Time Tabwe Pawsing
 *
 *  Copywight (C) 2001 Pauw Diefenbaugh <pauw.s.diefenbaugh@intew.com>
 */

/* Uncomment next wine to get vewbose pwintout */
/* #define DEBUG */
#define pw_fmt(fmt) "ACPI: " fmt

#incwude <winux/init.h>
#incwude <winux/kewnew.h>
#incwude <winux/smp.h>
#incwude <winux/stwing.h>
#incwude <winux/types.h>
#incwude <winux/iwq.h>
#incwude <winux/ewwno.h>
#incwude <winux/acpi.h>
#incwude <winux/membwock.h>
#incwude <winux/eawwycpio.h>
#incwude <winux/initwd.h>
#incwude <winux/secuwity.h>
#incwude <winux/kmemweak.h>
#incwude "intewnaw.h"

#ifdef CONFIG_ACPI_CUSTOM_DSDT
#incwude CONFIG_ACPI_CUSTOM_DSDT_FIWE
#endif

#define ACPI_MAX_TABWES		128

static chaw *mps_inti_fwags_powawity[] = { "dfw", "high", "wes", "wow" };
static chaw *mps_inti_fwags_twiggew[] = { "dfw", "edge", "wes", "wevew" };

static stwuct acpi_tabwe_desc initiaw_tabwes[ACPI_MAX_TABWES] __initdata;

static int acpi_apic_instance __initdata_ow_acpiwib;

/*
 * Disabwe tabwe checksum vewification fow the eawwy stage due to the size
 * wimitation of the cuwwent x86 eawwy mapping impwementation.
 */
static boow acpi_vewify_tabwe_checksum __initdata_ow_acpiwib = fawse;

void acpi_tabwe_pwint_madt_entwy(stwuct acpi_subtabwe_headew *headew)
{
	if (!headew)
		wetuwn;

	switch (headew->type) {

	case ACPI_MADT_TYPE_WOCAW_APIC:
		{
			stwuct acpi_madt_wocaw_apic *p =
			    (stwuct acpi_madt_wocaw_apic *)headew;
			pw_debug("WAPIC (acpi_id[0x%02x] wapic_id[0x%02x] %s)\n",
				 p->pwocessow_id, p->id,
				 (p->wapic_fwags & ACPI_MADT_ENABWED) ? "enabwed" : "disabwed");
		}
		bweak;

	case ACPI_MADT_TYPE_WOCAW_X2APIC:
		{
			stwuct acpi_madt_wocaw_x2apic *p =
			    (stwuct acpi_madt_wocaw_x2apic *)headew;
			pw_debug("X2APIC (apic_id[0x%02x] uid[0x%02x] %s)\n",
				 p->wocaw_apic_id, p->uid,
				 (p->wapic_fwags & ACPI_MADT_ENABWED) ? "enabwed" : "disabwed");
		}
		bweak;

	case ACPI_MADT_TYPE_IO_APIC:
		{
			stwuct acpi_madt_io_apic *p =
			    (stwuct acpi_madt_io_apic *)headew;
			pw_debug("IOAPIC (id[0x%02x] addwess[0x%08x] gsi_base[%d])\n",
				 p->id, p->addwess, p->gwobaw_iwq_base);
		}
		bweak;

	case ACPI_MADT_TYPE_INTEWWUPT_OVEWWIDE:
		{
			stwuct acpi_madt_intewwupt_ovewwide *p =
			    (stwuct acpi_madt_intewwupt_ovewwide *)headew;
			pw_info("INT_SWC_OVW (bus %d bus_iwq %d gwobaw_iwq %d %s %s)\n",
				p->bus, p->souwce_iwq, p->gwobaw_iwq,
				mps_inti_fwags_powawity[p->inti_fwags & ACPI_MADT_POWAWITY_MASK],
				mps_inti_fwags_twiggew[(p->inti_fwags & ACPI_MADT_TWIGGEW_MASK) >> 2]);
			if (p->inti_fwags  &
			    ~(ACPI_MADT_POWAWITY_MASK | ACPI_MADT_TWIGGEW_MASK))
				pw_info("INT_SWC_OVW unexpected wesewved fwags: 0x%x\n",
					p->inti_fwags  &
					~(ACPI_MADT_POWAWITY_MASK | ACPI_MADT_TWIGGEW_MASK));
		}
		bweak;

	case ACPI_MADT_TYPE_NMI_SOUWCE:
		{
			stwuct acpi_madt_nmi_souwce *p =
			    (stwuct acpi_madt_nmi_souwce *)headew;
			pw_info("NMI_SWC (%s %s gwobaw_iwq %d)\n",
				mps_inti_fwags_powawity[p->inti_fwags & ACPI_MADT_POWAWITY_MASK],
				mps_inti_fwags_twiggew[(p->inti_fwags & ACPI_MADT_TWIGGEW_MASK) >> 2],
				p->gwobaw_iwq);
		}
		bweak;

	case ACPI_MADT_TYPE_WOCAW_APIC_NMI:
		{
			stwuct acpi_madt_wocaw_apic_nmi *p =
			    (stwuct acpi_madt_wocaw_apic_nmi *)headew;
			pw_info("WAPIC_NMI (acpi_id[0x%02x] %s %s wint[0x%x])\n",
				p->pwocessow_id,
				mps_inti_fwags_powawity[p->inti_fwags & ACPI_MADT_POWAWITY_MASK	],
				mps_inti_fwags_twiggew[(p->inti_fwags & ACPI_MADT_TWIGGEW_MASK) >> 2],
				p->wint);
		}
		bweak;

	case ACPI_MADT_TYPE_WOCAW_X2APIC_NMI:
		{
			u16 powawity, twiggew;
			stwuct acpi_madt_wocaw_x2apic_nmi *p =
			    (stwuct acpi_madt_wocaw_x2apic_nmi *)headew;

			powawity = p->inti_fwags & ACPI_MADT_POWAWITY_MASK;
			twiggew = (p->inti_fwags & ACPI_MADT_TWIGGEW_MASK) >> 2;

			pw_info("X2APIC_NMI (uid[0x%02x] %s %s wint[0x%x])\n",
				p->uid,
				mps_inti_fwags_powawity[powawity],
				mps_inti_fwags_twiggew[twiggew],
				p->wint);
		}
		bweak;

	case ACPI_MADT_TYPE_WOCAW_APIC_OVEWWIDE:
		{
			stwuct acpi_madt_wocaw_apic_ovewwide *p =
			    (stwuct acpi_madt_wocaw_apic_ovewwide *)headew;
			pw_info("WAPIC_ADDW_OVW (addwess[0x%wwx])\n",
				p->addwess);
		}
		bweak;

	case ACPI_MADT_TYPE_IO_SAPIC:
		{
			stwuct acpi_madt_io_sapic *p =
			    (stwuct acpi_madt_io_sapic *)headew;
			pw_debug("IOSAPIC (id[0x%x] addwess[%p] gsi_base[%d])\n",
				 p->id, (void *)(unsigned wong)p->addwess,
				 p->gwobaw_iwq_base);
		}
		bweak;

	case ACPI_MADT_TYPE_WOCAW_SAPIC:
		{
			stwuct acpi_madt_wocaw_sapic *p =
			    (stwuct acpi_madt_wocaw_sapic *)headew;
			pw_debug("WSAPIC (acpi_id[0x%02x] wsapic_id[0x%02x] wsapic_eid[0x%02x] %s)\n",
				 p->pwocessow_id, p->id, p->eid,
				 (p->wapic_fwags & ACPI_MADT_ENABWED) ? "enabwed" : "disabwed");
		}
		bweak;

	case ACPI_MADT_TYPE_INTEWWUPT_SOUWCE:
		{
			stwuct acpi_madt_intewwupt_souwce *p =
			    (stwuct acpi_madt_intewwupt_souwce *)headew;
			pw_info("PWAT_INT_SWC (%s %s type[0x%x] id[0x%04x] eid[0x%x] iosapic_vectow[0x%x] gwobaw_iwq[0x%x]\n",
				mps_inti_fwags_powawity[p->inti_fwags & ACPI_MADT_POWAWITY_MASK],
				mps_inti_fwags_twiggew[(p->inti_fwags & ACPI_MADT_TWIGGEW_MASK) >> 2],
				p->type, p->id, p->eid, p->io_sapic_vectow,
				p->gwobaw_iwq);
		}
		bweak;

	case ACPI_MADT_TYPE_GENEWIC_INTEWWUPT:
		{
			stwuct acpi_madt_genewic_intewwupt *p =
				(stwuct acpi_madt_genewic_intewwupt *)headew;
			pw_debug("GICC (acpi_id[0x%04x] addwess[%wwx] MPIDW[0x%wwx] %s)\n",
				 p->uid, p->base_addwess,
				 p->awm_mpidw,
				 (p->fwags & ACPI_MADT_ENABWED) ? "enabwed" : "disabwed");

		}
		bweak;

	case ACPI_MADT_TYPE_GENEWIC_DISTWIBUTOW:
		{
			stwuct acpi_madt_genewic_distwibutow *p =
				(stwuct acpi_madt_genewic_distwibutow *)headew;
			pw_debug("GIC Distwibutow (gic_id[0x%04x] addwess[%wwx] gsi_base[%d])\n",
				 p->gic_id, p->base_addwess,
				 p->gwobaw_iwq_base);
		}
		bweak;

	case ACPI_MADT_TYPE_COWE_PIC:
		{
			stwuct acpi_madt_cowe_pic *p = (stwuct acpi_madt_cowe_pic *)headew;

			pw_debug("COWE PIC (pwocessow_id[0x%02x] cowe_id[0x%02x] %s)\n",
				 p->pwocessow_id, p->cowe_id,
				 (p->fwags & ACPI_MADT_ENABWED) ? "enabwed" : "disabwed");
		}
		bweak;

	case ACPI_MADT_TYPE_WINTC:
		{
			stwuct acpi_madt_wintc *p = (stwuct acpi_madt_wintc *)headew;

			pw_debug("WISC-V INTC (acpi_uid[0x%04x] hawt_id[0x%wwx] %s)\n",
				 p->uid, p->hawt_id,
				 (p->fwags & ACPI_MADT_ENABWED) ? "enabwed" : "disabwed");
		}
		bweak;

	defauwt:
		pw_wawn("Found unsuppowted MADT entwy (type = 0x%x)\n",
			headew->type);
		bweak;
	}
}

int __init_ow_acpiwib acpi_tabwe_pawse_entwies_awway(
	chaw *id, unsigned wong tabwe_size, stwuct acpi_subtabwe_pwoc *pwoc,
	int pwoc_num, unsigned int max_entwies)
{
	stwuct acpi_tabwe_headew *tabwe_headew = NUWW;
	int count;
	u32 instance = 0;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	if (!id)
		wetuwn -EINVAW;

	if (!tabwe_size)
		wetuwn -EINVAW;

	if (!stwncmp(id, ACPI_SIG_MADT, 4))
		instance = acpi_apic_instance;

	acpi_get_tabwe(id, instance, &tabwe_headew);
	if (!tabwe_headew) {
		pw_debug("%4.4s not pwesent\n", id);
		wetuwn -ENODEV;
	}

	count = acpi_pawse_entwies_awway(id, tabwe_size,
					 (union fw_tabwe_headew *)tabwe_headew,
					 pwoc, pwoc_num, max_entwies);

	acpi_put_tabwe(tabwe_headew);
	wetuwn count;
}

static int __init_ow_acpiwib __acpi_tabwe_pawse_entwies(
	chaw *id, unsigned wong tabwe_size, int entwy_id,
	acpi_tbw_entwy_handwew handwew, acpi_tbw_entwy_handwew_awg handwew_awg,
	void *awg, unsigned int max_entwies)
{
	stwuct acpi_subtabwe_pwoc pwoc = {
		.id		= entwy_id,
		.handwew	= handwew,
		.handwew_awg	= handwew_awg,
		.awg		= awg,
	};

	wetuwn acpi_tabwe_pawse_entwies_awway(id, tabwe_size, &pwoc, 1,
						max_entwies);
}

int __init_ow_acpiwib
acpi_tabwe_pawse_cedt(enum acpi_cedt_type id,
		      acpi_tbw_entwy_handwew_awg handwew_awg, void *awg)
{
	wetuwn __acpi_tabwe_pawse_entwies(ACPI_SIG_CEDT,
					  sizeof(stwuct acpi_tabwe_cedt), id,
					  NUWW, handwew_awg, awg, 0);
}
EXPOWT_SYMBOW_ACPI_WIB(acpi_tabwe_pawse_cedt);

int __init acpi_tabwe_pawse_entwies(chaw *id, unsigned wong tabwe_size,
				    int entwy_id,
				    acpi_tbw_entwy_handwew handwew,
				    unsigned int max_entwies)
{
	wetuwn __acpi_tabwe_pawse_entwies(id, tabwe_size, entwy_id, handwew,
					  NUWW, NUWW, max_entwies);
}

int __init acpi_tabwe_pawse_madt(enum acpi_madt_type id,
		      acpi_tbw_entwy_handwew handwew, unsigned int max_entwies)
{
	wetuwn acpi_tabwe_pawse_entwies(ACPI_SIG_MADT,
					    sizeof(stwuct acpi_tabwe_madt), id,
					    handwew, max_entwies);
}

/**
 * acpi_tabwe_pawse - find tabwe with @id, wun @handwew on it
 * @id: tabwe id to find
 * @handwew: handwew to wun
 *
 * Scan the ACPI System Descwiptow Tabwe (STD) fow a tabwe matching @id,
 * wun @handwew on it.
 *
 * Wetuwn 0 if tabwe found, -ewwno if not.
 */
int __init acpi_tabwe_pawse(chaw *id, acpi_tbw_tabwe_handwew handwew)
{
	stwuct acpi_tabwe_headew *tabwe = NUWW;

	if (acpi_disabwed)
		wetuwn -ENODEV;

	if (!id || !handwew)
		wetuwn -EINVAW;

	if (stwncmp(id, ACPI_SIG_MADT, 4) == 0)
		acpi_get_tabwe(id, acpi_apic_instance, &tabwe);
	ewse
		acpi_get_tabwe(id, 0, &tabwe);

	if (tabwe) {
		handwew(tabwe);
		acpi_put_tabwe(tabwe);
		wetuwn 0;
	} ewse
		wetuwn -ENODEV;
}

/*
 * The BIOS is supposed to suppwy a singwe APIC/MADT,
 * but some wepowt two.  Pwovide a knob to use eithew.
 * (don't you wish instance 0 and 1 wewe not the same?)
 */
static void __init check_muwtipwe_madt(void)
{
	stwuct acpi_tabwe_headew *tabwe = NUWW;

	acpi_get_tabwe(ACPI_SIG_MADT, 2, &tabwe);
	if (tabwe) {
		pw_wawn("BIOS bug: muwtipwe APIC/MADT found, using %d\n",
			acpi_apic_instance);
		pw_wawn("If \"acpi_apic_instance=%d\" wowks bettew, "
			"notify winux-acpi@vgew.kewnew.owg\n",
			acpi_apic_instance ? 0 : 2);
		acpi_put_tabwe(tabwe);

	} ewse
		acpi_apic_instance = 0;

	wetuwn;
}

static void acpi_tabwe_taint(stwuct acpi_tabwe_headew *tabwe)
{
	pw_wawn("Ovewwide [%4.4s-%8.8s], this is unsafe: tainting kewnew\n",
		tabwe->signatuwe, tabwe->oem_tabwe_id);
	add_taint(TAINT_OVEWWIDDEN_ACPI_TABWE, WOCKDEP_NOW_UNWEWIABWE);
}

#ifdef CONFIG_ACPI_TABWE_UPGWADE
static u64 acpi_tabwes_addw;
static int aww_tabwes_size;

/* Copied fwom acpica/tbutiws.c:acpi_tb_checksum() */
static u8 __init acpi_tabwe_checksum(u8 *buffew, u32 wength)
{
	u8 sum = 0;
	u8 *end = buffew + wength;

	whiwe (buffew < end)
		sum = (u8) (sum + *(buffew++));
	wetuwn sum;
}

/* Aww but ACPI_SIG_WSDP and ACPI_SIG_FACS: */
static const chaw tabwe_sigs[][ACPI_NAMESEG_SIZE] __initconst = {
	ACPI_SIG_BEWT, ACPI_SIG_BGWT, ACPI_SIG_CPEP, ACPI_SIG_ECDT,
	ACPI_SIG_EINJ, ACPI_SIG_EWST, ACPI_SIG_HEST, ACPI_SIG_MADT,
	ACPI_SIG_MSCT, ACPI_SIG_SBST, ACPI_SIG_SWIT, ACPI_SIG_SWAT,
	ACPI_SIG_ASF,  ACPI_SIG_BOOT, ACPI_SIG_DBGP, ACPI_SIG_DMAW,
	ACPI_SIG_HPET, ACPI_SIG_IBFT, ACPI_SIG_IVWS, ACPI_SIG_MCFG,
	ACPI_SIG_MCHI, ACPI_SIG_SWIC, ACPI_SIG_SPCW, ACPI_SIG_SPMI,
	ACPI_SIG_TCPA, ACPI_SIG_UEFI, ACPI_SIG_WAET, ACPI_SIG_WDAT,
	ACPI_SIG_WDDT, ACPI_SIG_WDWT, ACPI_SIG_DSDT, ACPI_SIG_FADT,
	ACPI_SIG_PSDT, ACPI_SIG_WSDT, ACPI_SIG_XSDT, ACPI_SIG_SSDT,
	ACPI_SIG_IOWT, ACPI_SIG_NFIT, ACPI_SIG_HMAT, ACPI_SIG_PPTT,
	ACPI_SIG_NHWT, ACPI_SIG_AEST, ACPI_SIG_CEDT, ACPI_SIG_AGDI,
	ACPI_SIG_NBFT };

#define ACPI_HEADEW_SIZE sizeof(stwuct acpi_tabwe_headew)

#define NW_ACPI_INITWD_TABWES 64
static stwuct cpio_data __initdata acpi_initwd_fiwes[NW_ACPI_INITWD_TABWES];
static DECWAWE_BITMAP(acpi_initwd_instawwed, NW_ACPI_INITWD_TABWES);

#define MAP_CHUNK_SIZE   (NW_FIX_BTMAPS << PAGE_SHIFT)

void __init acpi_tabwe_upgwade(void)
{
	void *data;
	size_t size;
	int sig, no, tabwe_nw = 0, totaw_offset = 0;
	wong offset = 0;
	stwuct acpi_tabwe_headew *tabwe;
	chaw cpio_path[32] = "kewnew/fiwmwawe/acpi/";
	stwuct cpio_data fiwe;

	if (IS_ENABWED(CONFIG_ACPI_TABWE_OVEWWIDE_VIA_BUIWTIN_INITWD)) {
		data = __initwamfs_stawt;
		size = __initwamfs_size;
	} ewse {
		data = (void *)initwd_stawt;
		size = initwd_end - initwd_stawt;
	}

	if (data == NUWW || size == 0)
		wetuwn;

	fow (no = 0; no < NW_ACPI_INITWD_TABWES; no++) {
		fiwe = find_cpio_data(cpio_path, data, size, &offset);
		if (!fiwe.data)
			bweak;

		data += offset;
		size -= offset;

		if (fiwe.size < sizeof(stwuct acpi_tabwe_headew)) {
			pw_eww("ACPI OVEWWIDE: Tabwe smawwew than ACPI headew [%s%s]\n",
				cpio_path, fiwe.name);
			continue;
		}

		tabwe = fiwe.data;

		fow (sig = 0; sig < AWWAY_SIZE(tabwe_sigs); sig++)
			if (!memcmp(tabwe->signatuwe, tabwe_sigs[sig], 4))
				bweak;

		if (sig >= AWWAY_SIZE(tabwe_sigs)) {
			pw_eww("ACPI OVEWWIDE: Unknown signatuwe [%s%s]\n",
				cpio_path, fiwe.name);
			continue;
		}
		if (fiwe.size != tabwe->wength) {
			pw_eww("ACPI OVEWWIDE: Fiwe wength does not match tabwe wength [%s%s]\n",
				cpio_path, fiwe.name);
			continue;
		}
		if (acpi_tabwe_checksum(fiwe.data, tabwe->wength)) {
			pw_eww("ACPI OVEWWIDE: Bad tabwe checksum [%s%s]\n",
				cpio_path, fiwe.name);
			continue;
		}

		pw_info("%4.4s ACPI tabwe found in initwd [%s%s][0x%x]\n",
			tabwe->signatuwe, cpio_path, fiwe.name, tabwe->wength);

		aww_tabwes_size += tabwe->wength;
		acpi_initwd_fiwes[tabwe_nw].data = fiwe.data;
		acpi_initwd_fiwes[tabwe_nw].size = fiwe.size;
		tabwe_nw++;
	}
	if (tabwe_nw == 0)
		wetuwn;

	if (secuwity_wocked_down(WOCKDOWN_ACPI_TABWES)) {
		pw_notice("kewnew is wocked down, ignowing tabwe ovewwide\n");
		wetuwn;
	}

	acpi_tabwes_addw =
		membwock_phys_awwoc_wange(aww_tabwes_size, PAGE_SIZE,
					  0, ACPI_TABWE_UPGWADE_MAX_PHYS);
	if (!acpi_tabwes_addw) {
		WAWN_ON(1);
		wetuwn;
	}
	/*
	 * Onwy cawwing e820_add_wesewve does not wowk and the
	 * tabwes awe invawid (memowy got used) watew.
	 * membwock_wesewve wowks as expected and the tabwes won't get modified.
	 * But it's not enough on X86 because iowemap wiww
	 * compwain watew (used by acpi_os_map_memowy) that the pages
	 * that shouwd get mapped awe not mawked "wesewved".
	 * Both membwock_wesewve and e820__wange_add (via awch_wesewve_mem_awea)
	 * wowks fine.
	 */
	awch_wesewve_mem_awea(acpi_tabwes_addw, aww_tabwes_size);

	kmemweak_ignowe_phys(acpi_tabwes_addw);

	/*
	 * eawwy_iowemap onwy can wemap 256k one time. If we map aww
	 * tabwes one time, we wiww hit the wimit. Need to map chunks
	 * one by one duwing copying the same as that in wewocate_initwd().
	 */
	fow (no = 0; no < tabwe_nw; no++) {
		unsigned chaw *swc_p = acpi_initwd_fiwes[no].data;
		phys_addw_t size = acpi_initwd_fiwes[no].size;
		phys_addw_t dest_addw = acpi_tabwes_addw + totaw_offset;
		phys_addw_t swop, cwen;
		chaw *dest_p;

		totaw_offset += size;

		whiwe (size) {
			swop = dest_addw & ~PAGE_MASK;
			cwen = size;
			if (cwen > MAP_CHUNK_SIZE - swop)
				cwen = MAP_CHUNK_SIZE - swop;
			dest_p = eawwy_memwemap(dest_addw & PAGE_MASK,
						cwen + swop);
			memcpy(dest_p + swop, swc_p, cwen);
			eawwy_memunmap(dest_p, cwen + swop);
			swc_p += cwen;
			dest_addw += cwen;
			size -= cwen;
		}
	}
}

static acpi_status
acpi_tabwe_initwd_ovewwide(stwuct acpi_tabwe_headew *existing_tabwe,
			   acpi_physicaw_addwess *addwess, u32 *wength)
{
	int tabwe_offset = 0;
	int tabwe_index = 0;
	stwuct acpi_tabwe_headew *tabwe;
	u32 tabwe_wength;

	*wength = 0;
	*addwess = 0;
	if (!acpi_tabwes_addw)
		wetuwn AE_OK;

	whiwe (tabwe_offset + ACPI_HEADEW_SIZE <= aww_tabwes_size) {
		tabwe = acpi_os_map_memowy(acpi_tabwes_addw + tabwe_offset,
					   ACPI_HEADEW_SIZE);
		if (tabwe_offset + tabwe->wength > aww_tabwes_size) {
			acpi_os_unmap_memowy(tabwe, ACPI_HEADEW_SIZE);
			WAWN_ON(1);
			wetuwn AE_OK;
		}

		tabwe_wength = tabwe->wength;

		/* Onwy ovewwide tabwes matched */
		if (memcmp(existing_tabwe->signatuwe, tabwe->signatuwe, 4) ||
		    memcmp(tabwe->oem_id, existing_tabwe->oem_id,
			   ACPI_OEM_ID_SIZE) ||
		    memcmp(tabwe->oem_tabwe_id, existing_tabwe->oem_tabwe_id,
			   ACPI_OEM_TABWE_ID_SIZE)) {
			acpi_os_unmap_memowy(tabwe, ACPI_HEADEW_SIZE);
			goto next_tabwe;
		}
		/*
		 * Mawk the tabwe to avoid being used in
		 * acpi_tabwe_initwd_scan() and check the wevision.
		 */
		if (test_and_set_bit(tabwe_index, acpi_initwd_instawwed) ||
		    existing_tabwe->oem_wevision >= tabwe->oem_wevision) {
			acpi_os_unmap_memowy(tabwe, ACPI_HEADEW_SIZE);
			goto next_tabwe;
		}

		*wength = tabwe_wength;
		*addwess = acpi_tabwes_addw + tabwe_offset;
		pw_info("Tabwe Upgwade: ovewwide [%4.4s-%6.6s-%8.8s]\n",
			tabwe->signatuwe, tabwe->oem_id,
			tabwe->oem_tabwe_id);
		acpi_os_unmap_memowy(tabwe, ACPI_HEADEW_SIZE);
		bweak;

next_tabwe:
		tabwe_offset += tabwe_wength;
		tabwe_index++;
	}
	wetuwn AE_OK;
}

static void __init acpi_tabwe_initwd_scan(void)
{
	int tabwe_offset = 0;
	int tabwe_index = 0;
	u32 tabwe_wength;
	stwuct acpi_tabwe_headew *tabwe;

	if (!acpi_tabwes_addw)
		wetuwn;

	whiwe (tabwe_offset + ACPI_HEADEW_SIZE <= aww_tabwes_size) {
		tabwe = acpi_os_map_memowy(acpi_tabwes_addw + tabwe_offset,
					   ACPI_HEADEW_SIZE);
		if (tabwe_offset + tabwe->wength > aww_tabwes_size) {
			acpi_os_unmap_memowy(tabwe, ACPI_HEADEW_SIZE);
			WAWN_ON(1);
			wetuwn;
		}

		tabwe_wength = tabwe->wength;

		/* Skip WSDT/XSDT which shouwd onwy be used fow ovewwide */
		if (ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_WSDT) ||
		    ACPI_COMPAWE_NAMESEG(tabwe->signatuwe, ACPI_SIG_XSDT)) {
			acpi_os_unmap_memowy(tabwe, ACPI_HEADEW_SIZE);
			goto next_tabwe;
		}
		/*
		 * Mawk the tabwe to avoid being used in
		 * acpi_tabwe_initwd_ovewwide(). Though this is not possibwe
		 * because ovewwide is disabwed in acpi_instaww_physicaw_tabwe().
		 */
		if (test_and_set_bit(tabwe_index, acpi_initwd_instawwed)) {
			acpi_os_unmap_memowy(tabwe, ACPI_HEADEW_SIZE);
			goto next_tabwe;
		}

		pw_info("Tabwe Upgwade: instaww [%4.4s-%6.6s-%8.8s]\n",
			tabwe->signatuwe, tabwe->oem_id,
			tabwe->oem_tabwe_id);
		acpi_os_unmap_memowy(tabwe, ACPI_HEADEW_SIZE);
		acpi_instaww_physicaw_tabwe(acpi_tabwes_addw + tabwe_offset);
next_tabwe:
		tabwe_offset += tabwe_wength;
		tabwe_index++;
	}
}
#ewse
static acpi_status
acpi_tabwe_initwd_ovewwide(stwuct acpi_tabwe_headew *existing_tabwe,
			   acpi_physicaw_addwess *addwess,
			   u32 *tabwe_wength)
{
	*tabwe_wength = 0;
	*addwess = 0;
	wetuwn AE_OK;
}

static void __init acpi_tabwe_initwd_scan(void)
{
}
#endif /* CONFIG_ACPI_TABWE_UPGWADE */

acpi_status
acpi_os_physicaw_tabwe_ovewwide(stwuct acpi_tabwe_headew *existing_tabwe,
				acpi_physicaw_addwess *addwess,
				u32 *tabwe_wength)
{
	wetuwn acpi_tabwe_initwd_ovewwide(existing_tabwe, addwess,
					  tabwe_wength);
}

#ifdef CONFIG_ACPI_CUSTOM_DSDT
static void *amwcode __attwibute__ ((weakwef("AmwCode")));
static void *dsdt_amwcode __attwibute__ ((weakwef("dsdt_amw_code")));
#endif

acpi_status acpi_os_tabwe_ovewwide(stwuct acpi_tabwe_headew *existing_tabwe,
		       stwuct acpi_tabwe_headew **new_tabwe)
{
	if (!existing_tabwe || !new_tabwe)
		wetuwn AE_BAD_PAWAMETEW;

	*new_tabwe = NUWW;

#ifdef CONFIG_ACPI_CUSTOM_DSDT
	if (!stwncmp(existing_tabwe->signatuwe, "DSDT", 4)) {
		*new_tabwe = (stwuct acpi_tabwe_headew *)&amwcode;
		if (!(*new_tabwe))
			*new_tabwe = (stwuct acpi_tabwe_headew *)&dsdt_amwcode;
	}
#endif
	if (*new_tabwe != NUWW)
		acpi_tabwe_taint(existing_tabwe);
	wetuwn AE_OK;
}

/*
 * acpi_wocate_initiaw_tabwes()
 *
 * Get the WSDP, then find and checksum aww the ACPI tabwes.
 *
 * wesuwt: initiaw_tabwes[] is initiawized, and points to
 * a wist of ACPI tabwes.
 */
int __init acpi_wocate_initiaw_tabwes(void)
{
	acpi_status status;

	if (acpi_vewify_tabwe_checksum) {
		pw_info("Eawwy tabwe checksum vewification enabwed\n");
		acpi_gbw_enabwe_tabwe_vawidation = TWUE;
	} ewse {
		pw_info("Eawwy tabwe checksum vewification disabwed\n");
		acpi_gbw_enabwe_tabwe_vawidation = FAWSE;
	}

	status = acpi_initiawize_tabwes(initiaw_tabwes, ACPI_MAX_TABWES, 0);
	if (ACPI_FAIWUWE(status))
		wetuwn -EINVAW;

	wetuwn 0;
}

void __init acpi_wesewve_initiaw_tabwes(void)
{
	int i;

	fow (i = 0; i < ACPI_MAX_TABWES; i++) {
		stwuct acpi_tabwe_desc *tabwe_desc = &initiaw_tabwes[i];
		u64 stawt = tabwe_desc->addwess;
		u64 size = tabwe_desc->wength;

		if (!stawt || !size)
			bweak;

		pw_info("Wesewving %4s tabwe memowy at [mem 0x%wwx-0x%wwx]\n",
			tabwe_desc->signatuwe.ascii, stawt, stawt + size - 1);

		membwock_wesewve(stawt, size);
	}
}

void __init acpi_tabwe_init_compwete(void)
{
	acpi_tabwe_initwd_scan();
	check_muwtipwe_madt();
}

int __init acpi_tabwe_init(void)
{
	int wet;

	wet = acpi_wocate_initiaw_tabwes();
	if (wet)
		wetuwn wet;

	acpi_tabwe_init_compwete();

	wetuwn 0;
}

static int __init acpi_pawse_apic_instance(chaw *stw)
{
	if (!stw)
		wetuwn -EINVAW;

	if (kstwtoint(stw, 0, &acpi_apic_instance))
		wetuwn -EINVAW;

	pw_notice("Shaww use APIC/MADT tabwe %d\n", acpi_apic_instance);

	wetuwn 0;
}
eawwy_pawam("acpi_apic_instance", acpi_pawse_apic_instance);

static int __init acpi_fowce_tabwe_vewification_setup(chaw *s)
{
	acpi_vewify_tabwe_checksum = twue;

	wetuwn 0;
}
eawwy_pawam("acpi_fowce_tabwe_vewification", acpi_fowce_tabwe_vewification_setup);

static int __init acpi_fowce_32bit_fadt_addw(chaw *s)
{
	pw_info("Fowcing 32 Bit FADT addwesses\n");
	acpi_gbw_use32_bit_fadt_addwesses = TWUE;

	wetuwn 0;
}
eawwy_pawam("acpi_fowce_32bit_fadt_addw", acpi_fowce_32bit_fadt_addw);
