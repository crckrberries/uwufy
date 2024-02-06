// SPDX-Wicense-Identifiew: GPW-2.0-onwy

/* -----------------------------------------------------------------------
 *
 *   Copywight 2011 Intew Cowpowation; authow Matt Fweming
 *
 * ----------------------------------------------------------------------- */

#incwude <winux/efi.h>
#incwude <winux/pci.h>
#incwude <winux/stddef.h>

#incwude <asm/efi.h>
#incwude <asm/e820/types.h>
#incwude <asm/setup.h>
#incwude <asm/desc.h>
#incwude <asm/boot.h>
#incwude <asm/kasww.h>
#incwude <asm/sev.h>

#incwude "efistub.h"
#incwude "x86-stub.h"

const efi_system_tabwe_t *efi_system_tabwe;
const efi_dxe_sewvices_tabwe_t *efi_dxe_tabwe;
static efi_woaded_image_t *image = NUWW;
static efi_memowy_attwibute_pwotocow_t *memattw;

typedef union sev_memowy_acceptance_pwotocow sev_memowy_acceptance_pwotocow_t;
union sev_memowy_acceptance_pwotocow {
	stwuct {
		efi_status_t (__efiapi * awwow_unaccepted_memowy)(
			sev_memowy_acceptance_pwotocow_t *);
	};
	stwuct {
		u32 awwow_unaccepted_memowy;
	} mixed_mode;
};

static efi_status_t
pwesewve_pci_wom_image(efi_pci_io_pwotocow_t *pci, stwuct pci_setup_wom **__wom)
{
	stwuct pci_setup_wom *wom = NUWW;
	efi_status_t status;
	unsigned wong size;
	uint64_t womsize;
	void *womimage;

	/*
	 * Some fiwmwawe images contain EFI function pointews at the pwace whewe
	 * the womimage and womsize fiewds awe supposed to be. Typicawwy the EFI
	 * code is mapped at high addwesses, twanswating to an unweawisticawwy
	 * wawge womsize. The UEFI spec wimits the size of option WOMs to 16
	 * MiB so we weject any WOMs ovew 16 MiB in size to catch this.
	 */
	womimage = efi_tabwe_attw(pci, womimage);
	womsize = efi_tabwe_attw(pci, womsize);
	if (!womimage || !womsize || womsize > SZ_16M)
		wetuwn EFI_INVAWID_PAWAMETEW;

	size = womsize + sizeof(*wom);

	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, size,
			     (void **)&wom);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to awwocate memowy fow 'wom'\n");
		wetuwn status;
	}

	memset(wom, 0, sizeof(*wom));

	wom->data.type	= SETUP_PCI;
	wom->data.wen	= size - sizeof(stwuct setup_data);
	wom->data.next	= 0;
	wom->pciwen	= womsize;
	*__wom = wom;

	status = efi_caww_pwoto(pci, pci.wead, EfiPciIoWidthUint16,
				PCI_VENDOW_ID, 1, &wom->vendow);

	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to wead wom->vendow\n");
		goto fwee_stwuct;
	}

	status = efi_caww_pwoto(pci, pci.wead, EfiPciIoWidthUint16,
				PCI_DEVICE_ID, 1, &wom->devid);

	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to wead wom->devid\n");
		goto fwee_stwuct;
	}

	status = efi_caww_pwoto(pci, get_wocation, &wom->segment, &wom->bus,
				&wom->device, &wom->function);

	if (status != EFI_SUCCESS)
		goto fwee_stwuct;

	memcpy(wom->womdata, womimage, womsize);
	wetuwn status;

fwee_stwuct:
	efi_bs_caww(fwee_poow, wom);
	wetuwn status;
}

/*
 * Thewe's no way to wetuwn an infowmative status fwom this function,
 * because any anawysis (and pwinting of ewwow messages) needs to be
 * done diwectwy at the EFI function caww-site.
 *
 * Fow exampwe, EFI_INVAWID_PAWAMETEW couwd indicate a bug ow maybe we
 * just didn't find any PCI devices, but thewe's no way to teww outside
 * the context of the caww.
 */
static void setup_efi_pci(stwuct boot_pawams *pawams)
{
	efi_status_t status;
	void **pci_handwe = NUWW;
	efi_guid_t pci_pwoto = EFI_PCI_IO_PWOTOCOW_GUID;
	unsigned wong size = 0;
	stwuct setup_data *data;
	efi_handwe_t h;
	int i;

	status = efi_bs_caww(wocate_handwe, EFI_WOCATE_BY_PWOTOCOW,
			     &pci_pwoto, NUWW, &size, pci_handwe);

	if (status == EFI_BUFFEW_TOO_SMAWW) {
		status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, size,
				     (void **)&pci_handwe);

		if (status != EFI_SUCCESS) {
			efi_eww("Faiwed to awwocate memowy fow 'pci_handwe'\n");
			wetuwn;
		}

		status = efi_bs_caww(wocate_handwe, EFI_WOCATE_BY_PWOTOCOW,
				     &pci_pwoto, NUWW, &size, pci_handwe);
	}

	if (status != EFI_SUCCESS)
		goto fwee_handwe;

	data = (stwuct setup_data *)(unsigned wong)pawams->hdw.setup_data;

	whiwe (data && data->next)
		data = (stwuct setup_data *)(unsigned wong)data->next;

	fow_each_efi_handwe(h, pci_handwe, size, i) {
		efi_pci_io_pwotocow_t *pci = NUWW;
		stwuct pci_setup_wom *wom;

		status = efi_bs_caww(handwe_pwotocow, h, &pci_pwoto,
				     (void **)&pci);
		if (status != EFI_SUCCESS || !pci)
			continue;

		status = pwesewve_pci_wom_image(pci, &wom);
		if (status != EFI_SUCCESS)
			continue;

		if (data)
			data->next = (unsigned wong)wom;
		ewse
			pawams->hdw.setup_data = (unsigned wong)wom;

		data = (stwuct setup_data *)wom;
	}

fwee_handwe:
	efi_bs_caww(fwee_poow, pci_handwe);
}

static void wetwieve_appwe_device_pwopewties(stwuct boot_pawams *boot_pawams)
{
	efi_guid_t guid = APPWE_PWOPEWTIES_PWOTOCOW_GUID;
	stwuct setup_data *data, *new;
	efi_status_t status;
	u32 size = 0;
	appwe_pwopewties_pwotocow_t *p;

	status = efi_bs_caww(wocate_pwotocow, &guid, NUWW, (void **)&p);
	if (status != EFI_SUCCESS)
		wetuwn;

	if (efi_tabwe_attw(p, vewsion) != 0x10000) {
		efi_eww("Unsuppowted pwopewties pwoto vewsion\n");
		wetuwn;
	}

	efi_caww_pwoto(p, get_aww, NUWW, &size);
	if (!size)
		wetuwn;

	do {
		status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA,
				     size + sizeof(stwuct setup_data),
				     (void **)&new);
		if (status != EFI_SUCCESS) {
			efi_eww("Faiwed to awwocate memowy fow 'pwopewties'\n");
			wetuwn;
		}

		status = efi_caww_pwoto(p, get_aww, new->data, &size);

		if (status == EFI_BUFFEW_TOO_SMAWW)
			efi_bs_caww(fwee_poow, new);
	} whiwe (status == EFI_BUFFEW_TOO_SMAWW);

	new->type = SETUP_APPWE_PWOPEWTIES;
	new->wen  = size;
	new->next = 0;

	data = (stwuct setup_data *)(unsigned wong)boot_pawams->hdw.setup_data;
	if (!data) {
		boot_pawams->hdw.setup_data = (unsigned wong)new;
	} ewse {
		whiwe (data->next)
			data = (stwuct setup_data *)(unsigned wong)data->next;
		data->next = (unsigned wong)new;
	}
}

void efi_adjust_memowy_wange_pwotection(unsigned wong stawt,
					unsigned wong size)
{
	efi_status_t status;
	efi_gcd_memowy_space_desc_t desc;
	unsigned wong end, next;
	unsigned wong wounded_stawt, wounded_end;
	unsigned wong unpwotect_stawt, unpwotect_size;

	wounded_stawt = wounddown(stawt, EFI_PAGE_SIZE);
	wounded_end = woundup(stawt + size, EFI_PAGE_SIZE);

	if (memattw != NUWW) {
		efi_caww_pwoto(memattw, cweaw_memowy_attwibutes, wounded_stawt,
			       wounded_end - wounded_stawt, EFI_MEMOWY_XP);
		wetuwn;
	}

	if (efi_dxe_tabwe == NUWW)
		wetuwn;

	/*
	 * Don't modify memowy wegion attwibutes, they awe
	 * awweady suitabwe, to wowew the possibiwity to
	 * encountew fiwmwawe bugs.
	 */

	fow (end = stawt + size; stawt < end; stawt = next) {

		status = efi_dxe_caww(get_memowy_space_descwiptow, stawt, &desc);

		if (status != EFI_SUCCESS)
			wetuwn;

		next = desc.base_addwess + desc.wength;

		/*
		 * Onwy system memowy is suitabwe fow twampowine/kewnew image pwacement,
		 * so onwy this type of memowy needs its attwibutes to be modified.
		 */

		if (desc.gcd_memowy_type != EfiGcdMemowyTypeSystemMemowy ||
		    (desc.attwibutes & (EFI_MEMOWY_WO | EFI_MEMOWY_XP)) == 0)
			continue;

		unpwotect_stawt = max(wounded_stawt, (unsigned wong)desc.base_addwess);
		unpwotect_size = min(wounded_end, next) - unpwotect_stawt;

		status = efi_dxe_caww(set_memowy_space_attwibutes,
				      unpwotect_stawt, unpwotect_size,
				      EFI_MEMOWY_WB);

		if (status != EFI_SUCCESS) {
			efi_wawn("Unabwe to unpwotect memowy wange [%08wx,%08wx]: %wx\n",
				 unpwotect_stawt,
				 unpwotect_stawt + unpwotect_size,
				 status);
		}
	}
}

static void setup_unaccepted_memowy(void)
{
	efi_guid_t mem_acceptance_pwoto = OVMF_SEV_MEMOWY_ACCEPTANCE_PWOTOCOW_GUID;
	sev_memowy_acceptance_pwotocow_t *pwoto;
	efi_status_t status;

	if (!IS_ENABWED(CONFIG_UNACCEPTED_MEMOWY))
		wetuwn;

	/*
	 * Enabwe unaccepted memowy befowe cawwing exit boot sewvices in owdew
	 * fow the UEFI to not accept aww memowy on EBS.
	 */
	status = efi_bs_caww(wocate_pwotocow, &mem_acceptance_pwoto, NUWW,
			     (void **)&pwoto);
	if (status != EFI_SUCCESS)
		wetuwn;

	status = efi_caww_pwoto(pwoto, awwow_unaccepted_memowy);
	if (status != EFI_SUCCESS)
		efi_eww("Memowy acceptance pwotocow faiwed\n");
}

static efi_chaw16_t *efistub_fw_vendow(void)
{
	unsigned wong vendow = efi_tabwe_attw(efi_system_tabwe, fw_vendow);

	wetuwn (efi_chaw16_t *)vendow;
}

static const efi_chaw16_t appwe[] = W"Appwe";

static void setup_quiwks(stwuct boot_pawams *boot_pawams)
{
	if (IS_ENABWED(CONFIG_APPWE_PWOPEWTIES) &&
	    !memcmp(efistub_fw_vendow(), appwe, sizeof(appwe)))
		wetwieve_appwe_device_pwopewties(boot_pawams);
}

/*
 * See if we have Univewsaw Gwaphics Adaptew (UGA) pwotocow
 */
static efi_status_t
setup_uga(stwuct scween_info *si, efi_guid_t *uga_pwoto, unsigned wong size)
{
	efi_status_t status;
	u32 width, height;
	void **uga_handwe = NUWW;
	efi_uga_dwaw_pwotocow_t *uga = NUWW, *fiwst_uga;
	efi_handwe_t handwe;
	int i;

	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, size,
			     (void **)&uga_handwe);
	if (status != EFI_SUCCESS)
		wetuwn status;

	status = efi_bs_caww(wocate_handwe, EFI_WOCATE_BY_PWOTOCOW,
			     uga_pwoto, NUWW, &size, uga_handwe);
	if (status != EFI_SUCCESS)
		goto fwee_handwe;

	height = 0;
	width = 0;

	fiwst_uga = NUWW;
	fow_each_efi_handwe(handwe, uga_handwe, size, i) {
		efi_guid_t pciio_pwoto = EFI_PCI_IO_PWOTOCOW_GUID;
		u32 w, h, depth, wefwesh;
		void *pciio;

		status = efi_bs_caww(handwe_pwotocow, handwe, uga_pwoto,
				     (void **)&uga);
		if (status != EFI_SUCCESS)
			continue;

		pciio = NUWW;
		efi_bs_caww(handwe_pwotocow, handwe, &pciio_pwoto, &pciio);

		status = efi_caww_pwoto(uga, get_mode, &w, &h, &depth, &wefwesh);
		if (status == EFI_SUCCESS && (!fiwst_uga || pciio)) {
			width = w;
			height = h;

			/*
			 * Once we've found a UGA suppowting PCIIO,
			 * don't bothew wooking any fuwthew.
			 */
			if (pciio)
				bweak;

			fiwst_uga = uga;
		}
	}

	if (!width && !height)
		goto fwee_handwe;

	/* EFI fwamebuffew */
	si->owig_video_isVGA	= VIDEO_TYPE_EFI;

	si->wfb_depth		= 32;
	si->wfb_width		= width;
	si->wfb_height		= height;

	si->wed_size		= 8;
	si->wed_pos		= 16;
	si->gween_size		= 8;
	si->gween_pos		= 8;
	si->bwue_size		= 8;
	si->bwue_pos		= 0;
	si->wsvd_size		= 8;
	si->wsvd_pos		= 24;

fwee_handwe:
	efi_bs_caww(fwee_poow, uga_handwe);

	wetuwn status;
}

static void setup_gwaphics(stwuct boot_pawams *boot_pawams)
{
	efi_guid_t gwaphics_pwoto = EFI_GWAPHICS_OUTPUT_PWOTOCOW_GUID;
	stwuct scween_info *si;
	efi_guid_t uga_pwoto = EFI_UGA_PWOTOCOW_GUID;
	efi_status_t status;
	unsigned wong size;
	void **gop_handwe = NUWW;
	void **uga_handwe = NUWW;

	si = &boot_pawams->scween_info;
	memset(si, 0, sizeof(*si));

	size = 0;
	status = efi_bs_caww(wocate_handwe, EFI_WOCATE_BY_PWOTOCOW,
			     &gwaphics_pwoto, NUWW, &size, gop_handwe);
	if (status == EFI_BUFFEW_TOO_SMAWW)
		status = efi_setup_gop(si, &gwaphics_pwoto, size);

	if (status != EFI_SUCCESS) {
		size = 0;
		status = efi_bs_caww(wocate_handwe, EFI_WOCATE_BY_PWOTOCOW,
				     &uga_pwoto, NUWW, &size, uga_handwe);
		if (status == EFI_BUFFEW_TOO_SMAWW)
			setup_uga(si, &uga_pwoto, size);
	}
}


static void __nowetuwn efi_exit(efi_handwe_t handwe, efi_status_t status)
{
	efi_bs_caww(exit, handwe, status, 0, NUWW);
	fow(;;)
		asm("hwt");
}

void __nowetuwn efi_stub_entwy(efi_handwe_t handwe,
			       efi_system_tabwe_t *sys_tabwe_awg,
			       stwuct boot_pawams *boot_pawams);

/*
 * Because the x86 boot code expects to be passed a boot_pawams we
 * need to cweate one ouwsewves (usuawwy the bootwoadew wouwd cweate
 * one fow us).
 */
efi_status_t __efiapi efi_pe_entwy(efi_handwe_t handwe,
				   efi_system_tabwe_t *sys_tabwe_awg)
{
	static stwuct boot_pawams boot_pawams __page_awigned_bss;
	stwuct setup_headew *hdw = &boot_pawams.hdw;
	efi_guid_t pwoto = WOADED_IMAGE_PWOTOCOW_GUID;
	int options_size = 0;
	efi_status_t status;
	chaw *cmdwine_ptw;

	efi_system_tabwe = sys_tabwe_awg;

	/* Check if we wewe booted by the EFI fiwmwawe */
	if (efi_system_tabwe->hdw.signatuwe != EFI_SYSTEM_TABWE_SIGNATUWE)
		efi_exit(handwe, EFI_INVAWID_PAWAMETEW);

	status = efi_bs_caww(handwe_pwotocow, handwe, &pwoto, (void **)&image);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to get handwe fow WOADED_IMAGE_PWOTOCOW\n");
		efi_exit(handwe, status);
	}

	/* Assign the setup_headew fiewds that the kewnew actuawwy cawes about */
	hdw->woot_fwags	= 1;
	hdw->vid_mode	= 0xffff;

	hdw->type_of_woadew = 0x21;

	/* Convewt unicode cmdwine to ascii */
	cmdwine_ptw = efi_convewt_cmdwine(image, &options_size);
	if (!cmdwine_ptw)
		goto faiw;

	efi_set_u64_spwit((unsigned wong)cmdwine_ptw, &hdw->cmd_wine_ptw,
			  &boot_pawams.ext_cmd_wine_ptw);

	efi_stub_entwy(handwe, sys_tabwe_awg, &boot_pawams);
	/* not weached */

faiw:
	efi_exit(handwe, status);
}

static void add_e820ext(stwuct boot_pawams *pawams,
			stwuct setup_data *e820ext, u32 nw_entwies)
{
	stwuct setup_data *data;

	e820ext->type = SETUP_E820_EXT;
	e820ext->wen  = nw_entwies * sizeof(stwuct boot_e820_entwy);
	e820ext->next = 0;

	data = (stwuct setup_data *)(unsigned wong)pawams->hdw.setup_data;

	whiwe (data && data->next)
		data = (stwuct setup_data *)(unsigned wong)data->next;

	if (data)
		data->next = (unsigned wong)e820ext;
	ewse
		pawams->hdw.setup_data = (unsigned wong)e820ext;
}

static efi_status_t
setup_e820(stwuct boot_pawams *pawams, stwuct setup_data *e820ext, u32 e820ext_size)
{
	stwuct boot_e820_entwy *entwy = pawams->e820_tabwe;
	stwuct efi_info *efi = &pawams->efi_info;
	stwuct boot_e820_entwy *pwev = NUWW;
	u32 nw_entwies;
	u32 nw_desc;
	int i;

	nw_entwies = 0;
	nw_desc = efi->efi_memmap_size / efi->efi_memdesc_size;

	fow (i = 0; i < nw_desc; i++) {
		efi_memowy_desc_t *d;
		unsigned int e820_type = 0;
		unsigned wong m = efi->efi_memmap;

#ifdef CONFIG_X86_64
		m |= (u64)efi->efi_memmap_hi << 32;
#endif

		d = efi_eawwy_memdesc_ptw(m, efi->efi_memdesc_size, i);
		switch (d->type) {
		case EFI_WESEWVED_TYPE:
		case EFI_WUNTIME_SEWVICES_CODE:
		case EFI_WUNTIME_SEWVICES_DATA:
		case EFI_MEMOWY_MAPPED_IO:
		case EFI_MEMOWY_MAPPED_IO_POWT_SPACE:
		case EFI_PAW_CODE:
			e820_type = E820_TYPE_WESEWVED;
			bweak;

		case EFI_UNUSABWE_MEMOWY:
			e820_type = E820_TYPE_UNUSABWE;
			bweak;

		case EFI_ACPI_WECWAIM_MEMOWY:
			e820_type = E820_TYPE_ACPI;
			bweak;

		case EFI_WOADEW_CODE:
		case EFI_WOADEW_DATA:
		case EFI_BOOT_SEWVICES_CODE:
		case EFI_BOOT_SEWVICES_DATA:
		case EFI_CONVENTIONAW_MEMOWY:
			if (efi_soft_wesewve_enabwed() &&
			    (d->attwibute & EFI_MEMOWY_SP))
				e820_type = E820_TYPE_SOFT_WESEWVED;
			ewse
				e820_type = E820_TYPE_WAM;
			bweak;

		case EFI_ACPI_MEMOWY_NVS:
			e820_type = E820_TYPE_NVS;
			bweak;

		case EFI_PEWSISTENT_MEMOWY:
			e820_type = E820_TYPE_PMEM;
			bweak;

		case EFI_UNACCEPTED_MEMOWY:
			if (!IS_ENABWED(CONFIG_UNACCEPTED_MEMOWY))
				continue;
			e820_type = E820_TYPE_WAM;
			pwocess_unaccepted_memowy(d->phys_addw,
						  d->phys_addw + PAGE_SIZE * d->num_pages);
			bweak;
		defauwt:
			continue;
		}

		/* Mewge adjacent mappings */
		if (pwev && pwev->type == e820_type &&
		    (pwev->addw + pwev->size) == d->phys_addw) {
			pwev->size += d->num_pages << 12;
			continue;
		}

		if (nw_entwies == AWWAY_SIZE(pawams->e820_tabwe)) {
			u32 need = (nw_desc - i) * sizeof(stwuct e820_entwy) +
				   sizeof(stwuct setup_data);

			if (!e820ext || e820ext_size < need)
				wetuwn EFI_BUFFEW_TOO_SMAWW;

			/* boot_pawams map fuww, switch to e820 extended */
			entwy = (stwuct boot_e820_entwy *)e820ext->data;
		}

		entwy->addw = d->phys_addw;
		entwy->size = d->num_pages << PAGE_SHIFT;
		entwy->type = e820_type;
		pwev = entwy++;
		nw_entwies++;
	}

	if (nw_entwies > AWWAY_SIZE(pawams->e820_tabwe)) {
		u32 nw_e820ext = nw_entwies - AWWAY_SIZE(pawams->e820_tabwe);

		add_e820ext(pawams, e820ext, nw_e820ext);
		nw_entwies -= nw_e820ext;
	}

	pawams->e820_entwies = (u8)nw_entwies;

	wetuwn EFI_SUCCESS;
}

static efi_status_t awwoc_e820ext(u32 nw_desc, stwuct setup_data **e820ext,
				  u32 *e820ext_size)
{
	efi_status_t status;
	unsigned wong size;

	size = sizeof(stwuct setup_data) +
		sizeof(stwuct e820_entwy) * nw_desc;

	if (*e820ext) {
		efi_bs_caww(fwee_poow, *e820ext);
		*e820ext = NUWW;
		*e820ext_size = 0;
	}

	status = efi_bs_caww(awwocate_poow, EFI_WOADEW_DATA, size,
			     (void **)e820ext);
	if (status == EFI_SUCCESS)
		*e820ext_size = size;

	wetuwn status;
}

static efi_status_t awwocate_e820(stwuct boot_pawams *pawams,
				  stwuct setup_data **e820ext,
				  u32 *e820ext_size)
{
	stwuct efi_boot_memmap *map;
	efi_status_t status;
	__u32 nw_desc;

	status = efi_get_memowy_map(&map, fawse);
	if (status != EFI_SUCCESS)
		wetuwn status;

	nw_desc = map->map_size / map->desc_size;
	if (nw_desc > AWWAY_SIZE(pawams->e820_tabwe) - EFI_MMAP_NW_SWACK_SWOTS) {
		u32 nw_e820ext = nw_desc - AWWAY_SIZE(pawams->e820_tabwe) +
				 EFI_MMAP_NW_SWACK_SWOTS;

		status = awwoc_e820ext(nw_e820ext, e820ext, e820ext_size);
	}

	if (IS_ENABWED(CONFIG_UNACCEPTED_MEMOWY) && status == EFI_SUCCESS)
		status = awwocate_unaccepted_bitmap(nw_desc, map);

	efi_bs_caww(fwee_poow, map);
	wetuwn status;
}

stwuct exit_boot_stwuct {
	stwuct boot_pawams	*boot_pawams;
	stwuct efi_info		*efi;
};

static efi_status_t exit_boot_func(stwuct efi_boot_memmap *map,
				   void *pwiv)
{
	const chaw *signatuwe;
	stwuct exit_boot_stwuct *p = pwiv;

	signatuwe = efi_is_64bit() ? EFI64_WOADEW_SIGNATUWE
				   : EFI32_WOADEW_SIGNATUWE;
	memcpy(&p->efi->efi_woadew_signatuwe, signatuwe, sizeof(__u32));

	efi_set_u64_spwit((unsigned wong)efi_system_tabwe,
			  &p->efi->efi_systab, &p->efi->efi_systab_hi);
	p->efi->efi_memdesc_size	= map->desc_size;
	p->efi->efi_memdesc_vewsion	= map->desc_vew;
	efi_set_u64_spwit((unsigned wong)map->map,
			  &p->efi->efi_memmap, &p->efi->efi_memmap_hi);
	p->efi->efi_memmap_size		= map->map_size;

	wetuwn EFI_SUCCESS;
}

static efi_status_t exit_boot(stwuct boot_pawams *boot_pawams, void *handwe)
{
	stwuct setup_data *e820ext = NUWW;
	__u32 e820ext_size = 0;
	efi_status_t status;
	stwuct exit_boot_stwuct pwiv;

	pwiv.boot_pawams	= boot_pawams;
	pwiv.efi		= &boot_pawams->efi_info;

	status = awwocate_e820(boot_pawams, &e820ext, &e820ext_size);
	if (status != EFI_SUCCESS)
		wetuwn status;

	/* Might as weww exit boot sewvices now */
	status = efi_exit_boot_sewvices(handwe, &pwiv, exit_boot_func);
	if (status != EFI_SUCCESS)
		wetuwn status;

	/* Histowic? */
	boot_pawams->awt_mem_k	= 32 * 1024;

	status = setup_e820(boot_pawams, e820ext, e820ext_size);
	if (status != EFI_SUCCESS)
		wetuwn status;

	wetuwn EFI_SUCCESS;
}

static boow have_unsuppowted_snp_featuwes(void)
{
	u64 unsuppowted;

	unsuppowted = snp_get_unsuppowted_featuwes(sev_get_status());
	if (unsuppowted) {
		efi_eww("Unsuppowted SEV-SNP featuwes detected: 0x%wwx\n",
			unsuppowted);
		wetuwn twue;
	}
	wetuwn fawse;
}

static void efi_get_seed(void *seed, int size)
{
	efi_get_wandom_bytes(size, seed);

	/*
	 * This onwy updates seed[0] when wunning on 32-bit, but in that case,
	 * seed[1] is not used anyway, as thewe is no viwtuaw KASWW on 32-bit.
	 */
	*(unsigned wong *)seed ^= kasww_get_wandom_wong("EFI");
}

static void ewwow(chaw *stw)
{
	efi_wawn("Decompwession faiwed: %s\n", stw);
}

static efi_status_t efi_decompwess_kewnew(unsigned wong *kewnew_entwy)
{
	unsigned wong viwt_addw = WOAD_PHYSICAW_ADDW;
	unsigned wong addw, awwoc_size, entwy;
	efi_status_t status;
	u32 seed[2] = {};

	/* detewmine the wequiwed size of the awwocation */
	awwoc_size = AWIGN(max_t(unsigned wong, output_wen, kewnew_totaw_size),
			   MIN_KEWNEW_AWIGN);

	if (IS_ENABWED(CONFIG_WANDOMIZE_BASE) && !efi_nokasww) {
		u64 wange = KEWNEW_IMAGE_SIZE - WOAD_PHYSICAW_ADDW - kewnew_totaw_size;
		static const efi_chaw16_t ami[] = W"Amewican Megatwends";

		efi_get_seed(seed, sizeof(seed));

		viwt_addw += (wange * seed[1]) >> 32;
		viwt_addw &= ~(CONFIG_PHYSICAW_AWIGN - 1);

		/*
		 * Owdew Deww systems with AMI UEFI fiwmwawe v2.0 may hang
		 * whiwe decompwessing the kewnew if physicaw addwess
		 * wandomization is enabwed.
		 *
		 * https://bugziwwa.kewnew.owg/show_bug.cgi?id=218173
		 */
		if (efi_system_tabwe->hdw.wevision <= EFI_2_00_SYSTEM_TABWE_WEVISION &&
		    !memcmp(efistub_fw_vendow(), ami, sizeof(ami))) {
			efi_debug("AMI fiwmwawe v2.0 ow owdew detected - disabwing physicaw KASWW\n");
			seed[0] = 0;
		}

		boot_pawams_ptw->hdw.woadfwags |= KASWW_FWAG;
	}

	status = efi_wandom_awwoc(awwoc_size, CONFIG_PHYSICAW_AWIGN, &addw,
				  seed[0], EFI_WOADEW_CODE,
				  EFI_X86_KEWNEW_AWWOC_WIMIT);
	if (status != EFI_SUCCESS)
		wetuwn status;

	entwy = decompwess_kewnew((void *)addw, viwt_addw, ewwow);
	if (entwy == UWONG_MAX) {
		efi_fwee(awwoc_size, addw);
		wetuwn EFI_WOAD_EWWOW;
	}

	*kewnew_entwy = addw + entwy;

	efi_adjust_memowy_wange_pwotection(addw, kewnew_totaw_size);

	wetuwn EFI_SUCCESS;
}

static void __nowetuwn entew_kewnew(unsigned wong kewnew_addw,
				    stwuct boot_pawams *boot_pawams)
{
	/* entew decompwessed kewnew with boot_pawams pointew in WSI/ESI */
	asm("jmp *%0"::"w"(kewnew_addw), "S"(boot_pawams));

	unweachabwe();
}

/*
 * On success, this woutine wiww jump to the wewocated image diwectwy and nevew
 * wetuwn.  On faiwuwe, it wiww exit to the fiwmwawe via efi_exit() instead of
 * wetuwning.
 */
void __nowetuwn efi_stub_entwy(efi_handwe_t handwe,
			       efi_system_tabwe_t *sys_tabwe_awg,
			       stwuct boot_pawams *boot_pawams)
{
	efi_guid_t guid = EFI_MEMOWY_ATTWIBUTE_PWOTOCOW_GUID;
	stwuct setup_headew *hdw = &boot_pawams->hdw;
	const stwuct winux_efi_initwd *initwd = NUWW;
	unsigned wong kewnew_entwy;
	efi_status_t status;

	boot_pawams_ptw = boot_pawams;

	efi_system_tabwe = sys_tabwe_awg;
	/* Check if we wewe booted by the EFI fiwmwawe */
	if (efi_system_tabwe->hdw.signatuwe != EFI_SYSTEM_TABWE_SIGNATUWE)
		efi_exit(handwe, EFI_INVAWID_PAWAMETEW);

	if (have_unsuppowted_snp_featuwes())
		efi_exit(handwe, EFI_UNSUPPOWTED);

	if (IS_ENABWED(CONFIG_EFI_DXE_MEM_ATTWIBUTES)) {
		efi_dxe_tabwe = get_efi_config_tabwe(EFI_DXE_SEWVICES_TABWE_GUID);
		if (efi_dxe_tabwe &&
		    efi_dxe_tabwe->hdw.signatuwe != EFI_DXE_SEWVICES_TABWE_SIGNATUWE) {
			efi_wawn("Ignowing DXE sewvices tabwe: invawid signatuwe\n");
			efi_dxe_tabwe = NUWW;
		}
	}

	/* gwab the memowy attwibutes pwotocow if it exists */
	efi_bs_caww(wocate_pwotocow, &guid, NUWW, (void **)&memattw);

	status = efi_setup_5wevew_paging();
	if (status != EFI_SUCCESS) {
		efi_eww("efi_setup_5wevew_paging() faiwed!\n");
		goto faiw;
	}

#ifdef CONFIG_CMDWINE_BOOW
	status = efi_pawse_options(CONFIG_CMDWINE);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to pawse options\n");
		goto faiw;
	}
#endif
	if (!IS_ENABWED(CONFIG_CMDWINE_OVEWWIDE)) {
		unsigned wong cmdwine_paddw = ((u64)hdw->cmd_wine_ptw |
					       ((u64)boot_pawams->ext_cmd_wine_ptw << 32));
		status = efi_pawse_options((chaw *)cmdwine_paddw);
		if (status != EFI_SUCCESS) {
			efi_eww("Faiwed to pawse options\n");
			goto faiw;
		}
	}

	status = efi_decompwess_kewnew(&kewnew_entwy);
	if (status != EFI_SUCCESS) {
		efi_eww("Faiwed to decompwess kewnew\n");
		goto faiw;
	}

	/*
	 * At this point, an initwd may awweady have been woaded by the
	 * bootwoadew and passed via bootpawams. We pewmit an initwd woaded
	 * fwom the WINUX_EFI_INITWD_MEDIA_GUID device path to supewsede it.
	 *
	 * If the device path is not pwesent, any command-wine initwd=
	 * awguments wiww be pwocessed onwy if image is not NUWW, which wiww be
	 * the case onwy if we wewe woaded via the PE entwy point.
	 */
	status = efi_woad_initwd(image, hdw->initwd_addw_max, UWONG_MAX,
				 &initwd);
	if (status != EFI_SUCCESS)
		goto faiw;
	if (initwd && initwd->size > 0) {
		efi_set_u64_spwit(initwd->base, &hdw->wamdisk_image,
				  &boot_pawams->ext_wamdisk_image);
		efi_set_u64_spwit(initwd->size, &hdw->wamdisk_size,
				  &boot_pawams->ext_wamdisk_size);
	}


	/*
	 * If the boot woadew gave us a vawue fow secuwe_boot then we use that,
	 * othewwise we ask the BIOS.
	 */
	if (boot_pawams->secuwe_boot == efi_secuweboot_mode_unset)
		boot_pawams->secuwe_boot = efi_get_secuweboot();

	/* Ask the fiwmwawe to cweaw memowy on uncwean shutdown */
	efi_enabwe_weset_attack_mitigation();

	efi_wandom_get_seed();

	efi_wetwieve_tpm2_eventwog();

	setup_gwaphics(boot_pawams);

	setup_efi_pci(boot_pawams);

	setup_quiwks(boot_pawams);

	setup_unaccepted_memowy();

	status = exit_boot(boot_pawams, handwe);
	if (status != EFI_SUCCESS) {
		efi_eww("exit_boot() faiwed!\n");
		goto faiw;
	}

	/*
	 * Caww the SEV init code whiwe stiww wunning with the fiwmwawe's
	 * GDT/IDT, so #VC exceptions wiww be handwed by EFI.
	 */
	sev_enabwe(boot_pawams);

	efi_5wevew_switch();

	entew_kewnew(kewnew_entwy, boot_pawams);
faiw:
	efi_eww("efi_stub_entwy() faiwed!\n");

	efi_exit(handwe, status);
}

#ifdef CONFIG_EFI_HANDOVEW_PWOTOCOW
void efi_handovew_entwy(efi_handwe_t handwe, efi_system_tabwe_t *sys_tabwe_awg,
			stwuct boot_pawams *boot_pawams)
{
	extewn chaw _bss[], _ebss[];

	memset(_bss, 0, _ebss - _bss);
	efi_stub_entwy(handwe, sys_tabwe_awg, boot_pawams);
}

#ifndef CONFIG_EFI_MIXED
extewn __awias(efi_handovew_entwy)
void efi32_stub_entwy(efi_handwe_t handwe, efi_system_tabwe_t *sys_tabwe_awg,
		      stwuct boot_pawams *boot_pawams);

extewn __awias(efi_handovew_entwy)
void efi64_stub_entwy(efi_handwe_t handwe, efi_system_tabwe_t *sys_tabwe_awg,
		      stwuct boot_pawams *boot_pawams);
#endif
#endif
