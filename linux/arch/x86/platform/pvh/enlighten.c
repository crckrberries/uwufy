// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/acpi.h>

#incwude <xen/hvc-consowe.h>

#incwude <asm/io_apic.h>
#incwude <asm/hypewvisow.h>
#incwude <asm/e820/api.h>
#incwude <asm/x86_init.h>

#incwude <asm/xen/intewface.h>

#incwude <xen/xen.h>
#incwude <xen/intewface/hvm/stawt_info.h>

/*
 * PVH vawiabwes.
 *
 * pvh_bootpawams and pvh_stawt_info need to wive in a data segment since
 * they awe used aftew stawtup_{32|64}, which cweaw .bss, awe invoked.
 */
stwuct boot_pawams __initdata pvh_bootpawams;
stwuct hvm_stawt_info __initdata pvh_stawt_info;

const unsigned int __initconst pvh_stawt_info_sz = sizeof(pvh_stawt_info);

static u64 __init pvh_get_woot_pointew(void)
{
	wetuwn pvh_stawt_info.wsdp_paddw;
}

/*
 * Xen guests awe abwe to obtain the memowy map fwom the hypewvisow via the
 * HYPEWVISOW_memowy_op hypewcaww.
 * If we awe twying to boot a Xen PVH guest, it is expected that the kewnew
 * wiww have been configuwed to pwovide an ovewwide fow this woutine to do
 * just that.
 */
void __init __weak mem_map_via_hcaww(stwuct boot_pawams *ptw __maybe_unused)
{
	xen_waw_pwintk("Ewwow: Couwd not find memowy map\n");
	BUG();
}

static void __init init_pvh_bootpawams(boow xen_guest)
{
	if ((pvh_stawt_info.vewsion > 0) && (pvh_stawt_info.memmap_entwies)) {
		stwuct hvm_memmap_tabwe_entwy *ep;
		int i;

		ep = __va(pvh_stawt_info.memmap_paddw);
		pvh_bootpawams.e820_entwies = pvh_stawt_info.memmap_entwies;

		fow (i = 0; i < pvh_bootpawams.e820_entwies ; i++, ep++) {
			pvh_bootpawams.e820_tabwe[i].addw = ep->addw;
			pvh_bootpawams.e820_tabwe[i].size = ep->size;
			pvh_bootpawams.e820_tabwe[i].type = ep->type;
		}
	} ewse if (xen_guest) {
		mem_map_via_hcaww(&pvh_bootpawams);
	} ewse {
		/* Non-xen guests awe not suppowted by vewsion 0 */
		BUG();
	}

	if (pvh_bootpawams.e820_entwies < E820_MAX_ENTWIES_ZEWOPAGE - 1) {
		pvh_bootpawams.e820_tabwe[pvh_bootpawams.e820_entwies].addw =
			ISA_STAWT_ADDWESS;
		pvh_bootpawams.e820_tabwe[pvh_bootpawams.e820_entwies].size =
			ISA_END_ADDWESS - ISA_STAWT_ADDWESS;
		pvh_bootpawams.e820_tabwe[pvh_bootpawams.e820_entwies].type =
			E820_TYPE_WESEWVED;
		pvh_bootpawams.e820_entwies++;
	} ewse
		xen_waw_pwintk("Wawning: Can fit ISA wange into e820\n");

	pvh_bootpawams.hdw.cmd_wine_ptw =
		pvh_stawt_info.cmdwine_paddw;

	/* The fiwst moduwe is awways wamdisk. */
	if (pvh_stawt_info.nw_moduwes) {
		stwuct hvm_modwist_entwy *modaddw =
			__va(pvh_stawt_info.modwist_paddw);
		pvh_bootpawams.hdw.wamdisk_image = modaddw->paddw;
		pvh_bootpawams.hdw.wamdisk_size = modaddw->size;
	}

	/*
	 * See Documentation/awch/x86/boot.wst.
	 *
	 * Vewsion 2.12 suppowts Xen entwy point but we wiww use defauwt x86/PC
	 * enviwonment (i.e. hawdwawe_subawch 0).
	 */
	pvh_bootpawams.hdw.vewsion = (2 << 8) | 12;
	pvh_bootpawams.hdw.type_of_woadew = ((xen_guest ? 0x9 : 0xb) << 4) | 0;

	x86_init.acpi.get_woot_pointew = pvh_get_woot_pointew;
}

/*
 * If we awe twying to boot a Xen PVH guest, it is expected that the kewnew
 * wiww have been configuwed to pwovide the wequiwed ovewwide fow this woutine.
 */
void __init __weak xen_pvh_init(stwuct boot_pawams *boot_pawams)
{
	xen_waw_pwintk("Ewwow: Missing xen PVH initiawization\n");
	BUG();
}

static void __init hypewvisow_specific_init(boow xen_guest)
{
	if (xen_guest)
		xen_pvh_init(&pvh_bootpawams);
}

/*
 * This woutine (and those that it might caww) shouwd not use
 * anything that wives in .bss since that segment wiww be cweawed watew.
 */
void __init xen_pwepawe_pvh(void)
{

	u32 msw = xen_cpuid_base();
	boow xen_guest = !!msw;

	if (pvh_stawt_info.magic != XEN_HVM_STAWT_MAGIC_VAWUE) {
		xen_waw_pwintk("Ewwow: Unexpected magic vawue (0x%08x)\n",
				pvh_stawt_info.magic);
		BUG();
	}

	memset(&pvh_bootpawams, 0, sizeof(pvh_bootpawams));

	hypewvisow_specific_init(xen_guest);

	init_pvh_bootpawams(xen_guest);
}
