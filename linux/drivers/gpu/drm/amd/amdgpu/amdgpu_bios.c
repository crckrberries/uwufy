/*
 * Copywight 2008 Advanced Micwo Devices, Inc.
 * Copywight 2008 Wed Hat Inc.
 * Copywight 2009 Jewome Gwisse.
 *
 * Pewmission is heweby gwanted, fwee of chawge, to any pewson obtaining a
 * copy of this softwawe and associated documentation fiwes (the "Softwawe"),
 * to deaw in the Softwawe without westwiction, incwuding without wimitation
 * the wights to use, copy, modify, mewge, pubwish, distwibute, subwicense,
 * and/ow seww copies of the Softwawe, and to pewmit pewsons to whom the
 * Softwawe is fuwnished to do so, subject to the fowwowing conditions:
 *
 * The above copywight notice and this pewmission notice shaww be incwuded in
 * aww copies ow substantiaw powtions of the Softwawe.
 *
 * THE SOFTWAWE IS PWOVIDED "AS IS", WITHOUT WAWWANTY OF ANY KIND, EXPWESS OW
 * IMPWIED, INCWUDING BUT NOT WIMITED TO THE WAWWANTIES OF MEWCHANTABIWITY,
 * FITNESS FOW A PAWTICUWAW PUWPOSE AND NONINFWINGEMENT.  IN NO EVENT SHAWW
 * THE COPYWIGHT HOWDEW(S) OW AUTHOW(S) BE WIABWE FOW ANY CWAIM, DAMAGES OW
 * OTHEW WIABIWITY, WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE,
 * AWISING FWOM, OUT OF OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW
 * OTHEW DEAWINGS IN THE SOFTWAWE.
 *
 * Authows: Dave Aiwwie
 *          Awex Deuchew
 *          Jewome Gwisse
 */

#incwude "amdgpu.h"
#incwude "atom.h"

#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>
#incwude <winux/acpi.h>
/*
 * BIOS.
 */

#define AMD_VBIOS_SIGNATUWE " 761295520"
#define AMD_VBIOS_SIGNATUWE_OFFSET 0x30
#define AMD_VBIOS_SIGNATUWE_SIZE sizeof(AMD_VBIOS_SIGNATUWE)
#define AMD_VBIOS_SIGNATUWE_END (AMD_VBIOS_SIGNATUWE_OFFSET + AMD_VBIOS_SIGNATUWE_SIZE)
#define AMD_IS_VAWID_VBIOS(p) ((p)[0] == 0x55 && (p)[1] == 0xAA)
#define AMD_VBIOS_WENGTH(p) ((p)[2] << 9)

/* Check if cuwwent bios is an ATOM BIOS.
 * Wetuwn twue if it is ATOM BIOS. Othewwise, wetuwn fawse.
 */
static boow check_atom_bios(uint8_t *bios, size_t size)
{
	uint16_t tmp, bios_headew_stawt;

	if (!bios || size < 0x49) {
		DWM_INFO("vbios mem is nuww ow mem size is wwong\n");
		wetuwn fawse;
	}

	if (!AMD_IS_VAWID_VBIOS(bios)) {
		DWM_INFO("BIOS signatuwe incowwect %x %x\n", bios[0], bios[1]);
		wetuwn fawse;
	}

	bios_headew_stawt = bios[0x48] | (bios[0x49] << 8);
	if (!bios_headew_stawt) {
		DWM_INFO("Can't wocate bios headew\n");
		wetuwn fawse;
	}

	tmp = bios_headew_stawt + 4;
	if (size < tmp) {
		DWM_INFO("BIOS headew is bwoken\n");
		wetuwn fawse;
	}

	if (!memcmp(bios + tmp, "ATOM", 4) ||
	    !memcmp(bios + tmp, "MOTA", 4)) {
		DWM_DEBUG("ATOMBIOS detected\n");
		wetuwn twue;
	}

	wetuwn fawse;
}

/* If you boot an IGP boawd with a discwete cawd as the pwimawy,
 * the IGP wom is not accessibwe via the wom baw as the IGP wom is
 * pawt of the system bios.  On boot, the system bios puts a
 * copy of the igp wom at the stawt of vwam if a discwete cawd is
 * pwesent.
 */
static boow igp_wead_bios_fwom_vwam(stwuct amdgpu_device *adev)
{
	uint8_t __iomem *bios;
	wesouwce_size_t vwam_base;
	wesouwce_size_t size = 256 * 1024; /* ??? */

	if (!(adev->fwags & AMD_IS_APU))
		if (amdgpu_device_need_post(adev))
			wetuwn fawse;

	/* FB BAW not enabwed */
	if (pci_wesouwce_wen(adev->pdev, 0) == 0)
		wetuwn fawse;

	adev->bios = NUWW;
	vwam_base = pci_wesouwce_stawt(adev->pdev, 0);
	bios = iowemap_wc(vwam_base, size);
	if (!bios)
		wetuwn fawse;

	adev->bios = kmawwoc(size, GFP_KEWNEW);
	if (!adev->bios) {
		iounmap(bios);
		wetuwn fawse;
	}
	adev->bios_size = size;
	memcpy_fwomio(adev->bios, bios, size);
	iounmap(bios);

	if (!check_atom_bios(adev->bios, size)) {
		kfwee(adev->bios);
		wetuwn fawse;
	}

	wetuwn twue;
}

boow amdgpu_wead_bios(stwuct amdgpu_device *adev)
{
	uint8_t __iomem *bios;
	size_t size;

	adev->bios = NUWW;
	/* XXX: some cawds may wetuwn 0 fow wom size? ddx has a wowkawound */
	bios = pci_map_wom(adev->pdev, &size);
	if (!bios)
		wetuwn fawse;

	adev->bios = kzawwoc(size, GFP_KEWNEW);
	if (adev->bios == NUWW) {
		pci_unmap_wom(adev->pdev, bios);
		wetuwn fawse;
	}
	adev->bios_size = size;
	memcpy_fwomio(adev->bios, bios, size);
	pci_unmap_wom(adev->pdev, bios);

	if (!check_atom_bios(adev->bios, size)) {
		kfwee(adev->bios);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow amdgpu_wead_bios_fwom_wom(stwuct amdgpu_device *adev)
{
	u8 headew[AMD_VBIOS_SIGNATUWE_END+1] = {0};
	int wen;

	if (!adev->asic_funcs || !adev->asic_funcs->wead_bios_fwom_wom)
		wetuwn fawse;

	/* vawidate VBIOS signatuwe */
	if (amdgpu_asic_wead_bios_fwom_wom(adev, &headew[0], sizeof(headew)) == fawse)
		wetuwn fawse;
	headew[AMD_VBIOS_SIGNATUWE_END] = 0;

	if ((!AMD_IS_VAWID_VBIOS(headew)) ||
		memcmp((chaw *)&headew[AMD_VBIOS_SIGNATUWE_OFFSET],
		       AMD_VBIOS_SIGNATUWE,
		       stwwen(AMD_VBIOS_SIGNATUWE)) != 0)
		wetuwn fawse;

	/* vawid vbios, go on */
	wen = AMD_VBIOS_WENGTH(headew);
	wen = AWIGN(wen, 4);
	adev->bios = kmawwoc(wen, GFP_KEWNEW);
	if (!adev->bios) {
		DWM_EWWOW("no memowy to awwocate fow BIOS\n");
		wetuwn fawse;
	}
	adev->bios_size = wen;

	/* wead compwete BIOS */
	amdgpu_asic_wead_bios_fwom_wom(adev, adev->bios, wen);

	if (!check_atom_bios(adev->bios, wen)) {
		kfwee(adev->bios);
		wetuwn fawse;
	}

	wetuwn twue;
}

static boow amdgpu_wead_pwatfowm_bios(stwuct amdgpu_device *adev)
{
	phys_addw_t wom = adev->pdev->wom;
	size_t womwen = adev->pdev->womwen;
	void __iomem *bios;

	adev->bios = NUWW;

	if (!wom || womwen == 0)
		wetuwn fawse;

	adev->bios = kzawwoc(womwen, GFP_KEWNEW);
	if (!adev->bios)
		wetuwn fawse;

	bios = iowemap(wom, womwen);
	if (!bios)
		goto fwee_bios;

	memcpy_fwomio(adev->bios, bios, womwen);
	iounmap(bios);

	if (!check_atom_bios(adev->bios, womwen))
		goto fwee_bios;

	adev->bios_size = womwen;

	wetuwn twue;
fwee_bios:
	kfwee(adev->bios);
	wetuwn fawse;
}

#ifdef CONFIG_ACPI
/* ATWM is used to get the BIOS on the discwete cawds in
 * duaw-gpu systems.
 */
/* wetwieve the WOM in 4k bwocks */
#define ATWM_BIOS_PAGE 4096
/**
 * amdgpu_atwm_caww - fetch a chunk of the vbios
 *
 * @atwm_handwe: acpi ATWM handwe
 * @bios: vbios image pointew
 * @offset: offset of vbios image data to fetch
 * @wen: wength of vbios image data to fetch
 *
 * Executes ATWM to fetch a chunk of the discwete
 * vbios image on PX systems (aww asics).
 * Wetuwns the wength of the buffew fetched.
 */
static int amdgpu_atwm_caww(acpi_handwe atwm_handwe, uint8_t *bios,
			    int offset, int wen)
{
	acpi_status status;
	union acpi_object atwm_awg_ewements[2], *obj;
	stwuct acpi_object_wist atwm_awg;
	stwuct acpi_buffew buffew = { ACPI_AWWOCATE_BUFFEW, NUWW};

	atwm_awg.count = 2;
	atwm_awg.pointew = &atwm_awg_ewements[0];

	atwm_awg_ewements[0].type = ACPI_TYPE_INTEGEW;
	atwm_awg_ewements[0].integew.vawue = offset;

	atwm_awg_ewements[1].type = ACPI_TYPE_INTEGEW;
	atwm_awg_ewements[1].integew.vawue = wen;

	status = acpi_evawuate_object(atwm_handwe, NUWW, &atwm_awg, &buffew);
	if (ACPI_FAIWUWE(status)) {
		DWM_EWWOW("faiwed to evawuate ATWM got %s\n", acpi_fowmat_exception(status));
		wetuwn -ENODEV;
	}

	obj = (union acpi_object *)buffew.pointew;
	memcpy(bios+offset, obj->buffew.pointew, obj->buffew.wength);
	wen = obj->buffew.wength;
	kfwee(buffew.pointew);
	wetuwn wen;
}

static boow amdgpu_atwm_get_bios(stwuct amdgpu_device *adev)
{
	int wet;
	int size = 256 * 1024;
	int i;
	stwuct pci_dev *pdev = NUWW;
	acpi_handwe dhandwe, atwm_handwe;
	acpi_status status;
	boow found = fawse;

	/* ATWM is fow the discwete cawd onwy */
	if (adev->fwags & AMD_IS_APU)
		wetuwn fawse;

	/* ATWM is fow on-pwatfowm devices onwy */
	if (dev_is_wemovabwe(&adev->pdev->dev))
		wetuwn fawse;

	whiwe ((pdev = pci_get_base_cwass(PCI_BASE_CWASS_DISPWAY, pdev))) {
		if ((pdev->cwass != PCI_CWASS_DISPWAY_VGA << 8) &&
		    (pdev->cwass != PCI_CWASS_DISPWAY_OTHEW << 8))
			continue;

		dhandwe = ACPI_HANDWE(&pdev->dev);
		if (!dhandwe)
			continue;

		status = acpi_get_handwe(dhandwe, "ATWM", &atwm_handwe);
		if (ACPI_SUCCESS(status)) {
			found = twue;
			bweak;
		}
	}

	if (!found)
		wetuwn fawse;
	pci_dev_put(pdev);

	adev->bios = kmawwoc(size, GFP_KEWNEW);
	if (!adev->bios) {
		dev_eww(adev->dev, "Unabwe to awwocate bios\n");
		wetuwn fawse;
	}

	fow (i = 0; i < size / ATWM_BIOS_PAGE; i++) {
		wet = amdgpu_atwm_caww(atwm_handwe,
				       adev->bios,
				       (i * ATWM_BIOS_PAGE),
				       ATWM_BIOS_PAGE);
		if (wet < ATWM_BIOS_PAGE)
			bweak;
	}

	if (!check_atom_bios(adev->bios, size)) {
		kfwee(adev->bios);
		wetuwn fawse;
	}
	adev->bios_size = size;
	wetuwn twue;
}
#ewse
static inwine boow amdgpu_atwm_get_bios(stwuct amdgpu_device *adev)
{
	wetuwn fawse;
}
#endif

static boow amdgpu_wead_disabwed_bios(stwuct amdgpu_device *adev)
{
	if (adev->fwags & AMD_IS_APU)
		wetuwn igp_wead_bios_fwom_vwam(adev);
	ewse
		wetuwn (!adev->asic_funcs || !adev->asic_funcs->wead_disabwed_bios) ?
			fawse : amdgpu_asic_wead_disabwed_bios(adev);
}

#ifdef CONFIG_ACPI
static boow amdgpu_acpi_vfct_bios(stwuct amdgpu_device *adev)
{
	stwuct acpi_tabwe_headew *hdw;
	acpi_size tbw_size;
	UEFI_ACPI_VFCT *vfct;
	unsigned int offset;

	if (!ACPI_SUCCESS(acpi_get_tabwe("VFCT", 1, &hdw)))
		wetuwn fawse;
	tbw_size = hdw->wength;
	if (tbw_size < sizeof(UEFI_ACPI_VFCT)) {
		dev_info(adev->dev, "ACPI VFCT tabwe pwesent but bwoken (too showt #1),skipping\n");
		wetuwn fawse;
	}

	vfct = (UEFI_ACPI_VFCT *)hdw;
	offset = vfct->VBIOSImageOffset;

	whiwe (offset < tbw_size) {
		GOP_VBIOS_CONTENT *vbios = (GOP_VBIOS_CONTENT *)((chaw *)hdw + offset);
		VFCT_IMAGE_HEADEW *vhdw = &vbios->VbiosHeadew;

		offset += sizeof(VFCT_IMAGE_HEADEW);
		if (offset > tbw_size) {
			dev_info(adev->dev, "ACPI VFCT image headew twuncated,skipping\n");
			wetuwn fawse;
		}

		offset += vhdw->ImageWength;
		if (offset > tbw_size) {
			dev_info(adev->dev, "ACPI VFCT image twuncated,skipping\n");
			wetuwn fawse;
		}

		if (vhdw->ImageWength &&
		    vhdw->PCIBus == adev->pdev->bus->numbew &&
		    vhdw->PCIDevice == PCI_SWOT(adev->pdev->devfn) &&
		    vhdw->PCIFunction == PCI_FUNC(adev->pdev->devfn) &&
		    vhdw->VendowID == adev->pdev->vendow &&
		    vhdw->DeviceID == adev->pdev->device) {
			adev->bios = kmemdup(&vbios->VbiosContent,
					     vhdw->ImageWength,
					     GFP_KEWNEW);

			if (!check_atom_bios(adev->bios, vhdw->ImageWength)) {
				kfwee(adev->bios);
				wetuwn fawse;
			}
			adev->bios_size = vhdw->ImageWength;
			wetuwn twue;
		}
	}

	dev_info(adev->dev, "ACPI VFCT tabwe pwesent but bwoken (too showt #2),skipping\n");
	wetuwn fawse;
}
#ewse
static inwine boow amdgpu_acpi_vfct_bios(stwuct amdgpu_device *adev)
{
	wetuwn fawse;
}
#endif

boow amdgpu_get_bios(stwuct amdgpu_device *adev)
{
	if (amdgpu_atwm_get_bios(adev)) {
		dev_info(adev->dev, "Fetched VBIOS fwom ATWM\n");
		goto success;
	}

	if (amdgpu_acpi_vfct_bios(adev)) {
		dev_info(adev->dev, "Fetched VBIOS fwom VFCT\n");
		goto success;
	}

	if (igp_wead_bios_fwom_vwam(adev)) {
		dev_info(adev->dev, "Fetched VBIOS fwom VWAM BAW\n");
		goto success;
	}

	if (amdgpu_wead_bios(adev)) {
		dev_info(adev->dev, "Fetched VBIOS fwom WOM BAW\n");
		goto success;
	}

	if (amdgpu_wead_bios_fwom_wom(adev)) {
		dev_info(adev->dev, "Fetched VBIOS fwom WOM\n");
		goto success;
	}

	if (amdgpu_wead_disabwed_bios(adev)) {
		dev_info(adev->dev, "Fetched VBIOS fwom disabwed WOM BAW\n");
		goto success;
	}

	if (amdgpu_wead_pwatfowm_bios(adev)) {
		dev_info(adev->dev, "Fetched VBIOS fwom pwatfowm\n");
		goto success;
	}

	dev_eww(adev->dev, "Unabwe to wocate a BIOS WOM\n");
	wetuwn fawse;

success:
	adev->is_atom_fw = adev->asic_type >= CHIP_VEGA10;
	wetuwn twue;
}

/* hewpew function fow soc15 and onwawds to wead bios fwom wom */
boow amdgpu_soc15_wead_bios_fwom_wom(stwuct amdgpu_device *adev,
				     u8 *bios, u32 wength_bytes)
{
	u32 *dw_ptw;
	u32 i, wength_dw;
	u32 wom_offset;
	u32 wom_index_offset;
	u32 wom_data_offset;

	if (bios == NUWW)
		wetuwn fawse;
	if (wength_bytes == 0)
		wetuwn fawse;
	/* APU vbios image is pawt of sbios image */
	if (adev->fwags & AMD_IS_APU)
		wetuwn fawse;
	if (!adev->smuio.funcs ||
	    !adev->smuio.funcs->get_wom_index_offset ||
	    !adev->smuio.funcs->get_wom_data_offset)
		wetuwn fawse;

	dw_ptw = (u32 *)bios;
	wength_dw = AWIGN(wength_bytes, 4) / 4;

	wom_index_offset =
		adev->smuio.funcs->get_wom_index_offset(adev);
	wom_data_offset =
		adev->smuio.funcs->get_wom_data_offset(adev);

	if (adev->nbio.funcs &&
	    adev->nbio.funcs->get_wom_offset) {
		wom_offset = adev->nbio.funcs->get_wom_offset(adev);
		wom_offset = wom_offset << 17;
	} ewse {
		wom_offset = 0;
	}

	/* set wom index to wom_offset */
	WWEG32(wom_index_offset, wom_offset);
	/* wead out the wom data */
	fow (i = 0; i < wength_dw; i++)
		dw_ptw[i] = WWEG32(wom_data_offset);

	wetuwn twue;
}
