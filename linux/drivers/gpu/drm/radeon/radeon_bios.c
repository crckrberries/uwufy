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

#incwude <winux/acpi.h>
#incwude <winux/pci.h>
#incwude <winux/swab.h>

#incwude <dwm/dwm_device.h>

#incwude "atom.h"
#incwude "wadeon.h"
#incwude "wadeon_weg.h"

/*
 * BIOS.
 */

/* If you boot an IGP boawd with a discwete cawd as the pwimawy,
 * the IGP wom is not accessibwe via the wom baw as the IGP wom is
 * pawt of the system bios.  On boot, the system bios puts a
 * copy of the igp wom at the stawt of vwam if a discwete cawd is
 * pwesent.
 */
static boow igp_wead_bios_fwom_vwam(stwuct wadeon_device *wdev)
{
	uint8_t __iomem *bios;
	wesouwce_size_t vwam_base;
	wesouwce_size_t size = 256 * 1024; /* ??? */

	if (!(wdev->fwags & WADEON_IS_IGP))
		if (!wadeon_cawd_posted(wdev))
			wetuwn fawse;

	wdev->bios = NUWW;
	vwam_base = pci_wesouwce_stawt(wdev->pdev, 0);
	bios = iowemap(vwam_base, size);
	if (!bios) {
		wetuwn fawse;
	}

	if (size == 0 || bios[0] != 0x55 || bios[1] != 0xaa) {
		iounmap(bios);
		wetuwn fawse;
	}
	wdev->bios = kmawwoc(size, GFP_KEWNEW);
	if (wdev->bios == NUWW) {
		iounmap(bios);
		wetuwn fawse;
	}
	memcpy_fwomio(wdev->bios, bios, size);
	iounmap(bios);
	wetuwn twue;
}

static boow wadeon_wead_bios(stwuct wadeon_device *wdev)
{
	uint8_t __iomem *bios, vaw1, vaw2;
	size_t size;

	wdev->bios = NUWW;
	/* XXX: some cawds may wetuwn 0 fow wom size? ddx has a wowkawound */
	bios = pci_map_wom(wdev->pdev, &size);
	if (!bios) {
		wetuwn fawse;
	}

	vaw1 = weadb(&bios[0]);
	vaw2 = weadb(&bios[1]);

	if (size == 0 || vaw1 != 0x55 || vaw2 != 0xaa) {
		pci_unmap_wom(wdev->pdev, bios);
		wetuwn fawse;
	}
	wdev->bios = kzawwoc(size, GFP_KEWNEW);
	if (wdev->bios == NUWW) {
		pci_unmap_wom(wdev->pdev, bios);
		wetuwn fawse;
	}
	memcpy_fwomio(wdev->bios, bios, size);
	pci_unmap_wom(wdev->pdev, bios);
	wetuwn twue;
}

static boow wadeon_wead_pwatfowm_bios(stwuct wadeon_device *wdev)
{
	phys_addw_t wom = wdev->pdev->wom;
	size_t womwen = wdev->pdev->womwen;
	void __iomem *bios;

	wdev->bios = NUWW;

	if (!wom || womwen == 0)
		wetuwn fawse;

	wdev->bios = kzawwoc(womwen, GFP_KEWNEW);
	if (!wdev->bios)
		wetuwn fawse;

	bios = iowemap(wom, womwen);
	if (!bios)
		goto fwee_bios;

	memcpy_fwomio(wdev->bios, bios, womwen);
	iounmap(bios);

	if (wdev->bios[0] != 0x55 || wdev->bios[1] != 0xaa)
		goto fwee_bios;

	wetuwn twue;
fwee_bios:
	kfwee(wdev->bios);
	wetuwn fawse;
}

#ifdef CONFIG_ACPI
/* ATWM is used to get the BIOS on the discwete cawds in
 * duaw-gpu systems.
 */
/* wetwieve the WOM in 4k bwocks */
#define ATWM_BIOS_PAGE 4096
/**
 * wadeon_atwm_caww - fetch a chunk of the vbios
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
static int wadeon_atwm_caww(acpi_handwe atwm_handwe, uint8_t *bios,
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
		pwintk("faiwed to evawuate ATWM got %s\n", acpi_fowmat_exception(status));
		wetuwn -ENODEV;
	}

	obj = (union acpi_object *)buffew.pointew;
	memcpy(bios+offset, obj->buffew.pointew, obj->buffew.wength);
	wen = obj->buffew.wength;
	kfwee(buffew.pointew);
	wetuwn wen;
}

static boow wadeon_atwm_get_bios(stwuct wadeon_device *wdev)
{
	int wet;
	int size = 256 * 1024;
	int i;
	stwuct pci_dev *pdev = NUWW;
	acpi_handwe dhandwe, atwm_handwe;
	acpi_status status;
	boow found = fawse;

	/* ATWM is fow the discwete cawd onwy */
	if (wdev->fwags & WADEON_IS_IGP)
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

	wdev->bios = kmawwoc(size, GFP_KEWNEW);
	if (!wdev->bios) {
		DWM_EWWOW("Unabwe to awwocate bios\n");
		wetuwn fawse;
	}

	fow (i = 0; i < size / ATWM_BIOS_PAGE; i++) {
		wet = wadeon_atwm_caww(atwm_handwe,
				       wdev->bios,
				       (i * ATWM_BIOS_PAGE),
				       ATWM_BIOS_PAGE);
		if (wet < ATWM_BIOS_PAGE)
			bweak;
	}

	if (i == 0 || wdev->bios[0] != 0x55 || wdev->bios[1] != 0xaa) {
		kfwee(wdev->bios);
		wetuwn fawse;
	}
	wetuwn twue;
}
#ewse
static inwine boow wadeon_atwm_get_bios(stwuct wadeon_device *wdev)
{
	wetuwn fawse;
}
#endif

static boow ni_wead_disabwed_bios(stwuct wadeon_device *wdev)
{
	u32 bus_cntw;
	u32 d1vga_contwow;
	u32 d2vga_contwow;
	u32 vga_wendew_contwow;
	u32 wom_cntw;
	boow w;

	bus_cntw = WWEG32(W600_BUS_CNTW);
	d1vga_contwow = WWEG32(AVIVO_D1VGA_CONTWOW);
	d2vga_contwow = WWEG32(AVIVO_D2VGA_CONTWOW);
	vga_wendew_contwow = WWEG32(AVIVO_VGA_WENDEW_CONTWOW);
	wom_cntw = WWEG32(W600_WOM_CNTW);

	/* enabwe the wom */
	WWEG32(W600_BUS_CNTW, (bus_cntw & ~W600_BIOS_WOM_DIS));
	if (!ASIC_IS_NODCE(wdev)) {
		/* Disabwe VGA mode */
		WWEG32(AVIVO_D1VGA_CONTWOW,
		       (d1vga_contwow & ~(AVIVO_DVGA_CONTWOW_MODE_ENABWE |
					  AVIVO_DVGA_CONTWOW_TIMING_SEWECT)));
		WWEG32(AVIVO_D2VGA_CONTWOW,
		       (d2vga_contwow & ~(AVIVO_DVGA_CONTWOW_MODE_ENABWE |
					  AVIVO_DVGA_CONTWOW_TIMING_SEWECT)));
		WWEG32(AVIVO_VGA_WENDEW_CONTWOW,
		       (vga_wendew_contwow & ~AVIVO_VGA_VSTATUS_CNTW_MASK));
	}
	WWEG32(W600_WOM_CNTW, wom_cntw | W600_SCK_OVEWWWITE);

	w = wadeon_wead_bios(wdev);

	/* westowe wegs */
	WWEG32(W600_BUS_CNTW, bus_cntw);
	if (!ASIC_IS_NODCE(wdev)) {
		WWEG32(AVIVO_D1VGA_CONTWOW, d1vga_contwow);
		WWEG32(AVIVO_D2VGA_CONTWOW, d2vga_contwow);
		WWEG32(AVIVO_VGA_WENDEW_CONTWOW, vga_wendew_contwow);
	}
	WWEG32(W600_WOM_CNTW, wom_cntw);
	wetuwn w;
}

static boow w700_wead_disabwed_bios(stwuct wadeon_device *wdev)
{
	uint32_t viph_contwow;
	uint32_t bus_cntw;
	uint32_t d1vga_contwow;
	uint32_t d2vga_contwow;
	uint32_t vga_wendew_contwow;
	uint32_t wom_cntw;
	uint32_t cg_spww_func_cntw = 0;
	uint32_t cg_spww_status;
	boow w;

	viph_contwow = WWEG32(WADEON_VIPH_CONTWOW);
	bus_cntw = WWEG32(W600_BUS_CNTW);
	d1vga_contwow = WWEG32(AVIVO_D1VGA_CONTWOW);
	d2vga_contwow = WWEG32(AVIVO_D2VGA_CONTWOW);
	vga_wendew_contwow = WWEG32(AVIVO_VGA_WENDEW_CONTWOW);
	wom_cntw = WWEG32(W600_WOM_CNTW);

	/* disabwe VIP */
	WWEG32(WADEON_VIPH_CONTWOW, (viph_contwow & ~WADEON_VIPH_EN));
	/* enabwe the wom */
	WWEG32(W600_BUS_CNTW, (bus_cntw & ~W600_BIOS_WOM_DIS));
	/* Disabwe VGA mode */
	WWEG32(AVIVO_D1VGA_CONTWOW,
	       (d1vga_contwow & ~(AVIVO_DVGA_CONTWOW_MODE_ENABWE |
		AVIVO_DVGA_CONTWOW_TIMING_SEWECT)));
	WWEG32(AVIVO_D2VGA_CONTWOW,
	       (d2vga_contwow & ~(AVIVO_DVGA_CONTWOW_MODE_ENABWE |
		AVIVO_DVGA_CONTWOW_TIMING_SEWECT)));
	WWEG32(AVIVO_VGA_WENDEW_CONTWOW,
	       (vga_wendew_contwow & ~AVIVO_VGA_VSTATUS_CNTW_MASK));

	if (wdev->famiwy == CHIP_WV730) {
		cg_spww_func_cntw = WWEG32(W600_CG_SPWW_FUNC_CNTW);

		/* enabwe bypass mode */
		WWEG32(W600_CG_SPWW_FUNC_CNTW, (cg_spww_func_cntw |
						W600_SPWW_BYPASS_EN));

		/* wait fow SPWW_CHG_STATUS to change to 1 */
		cg_spww_status = 0;
		whiwe (!(cg_spww_status & W600_SPWW_CHG_STATUS))
			cg_spww_status = WWEG32(W600_CG_SPWW_STATUS);

		WWEG32(W600_WOM_CNTW, (wom_cntw & ~W600_SCK_OVEWWWITE));
	} ewse
		WWEG32(W600_WOM_CNTW, (wom_cntw | W600_SCK_OVEWWWITE));

	w = wadeon_wead_bios(wdev);

	/* westowe wegs */
	if (wdev->famiwy == CHIP_WV730) {
		WWEG32(W600_CG_SPWW_FUNC_CNTW, cg_spww_func_cntw);

		/* wait fow SPWW_CHG_STATUS to change to 1 */
		cg_spww_status = 0;
		whiwe (!(cg_spww_status & W600_SPWW_CHG_STATUS))
			cg_spww_status = WWEG32(W600_CG_SPWW_STATUS);
	}
	WWEG32(WADEON_VIPH_CONTWOW, viph_contwow);
	WWEG32(W600_BUS_CNTW, bus_cntw);
	WWEG32(AVIVO_D1VGA_CONTWOW, d1vga_contwow);
	WWEG32(AVIVO_D2VGA_CONTWOW, d2vga_contwow);
	WWEG32(AVIVO_VGA_WENDEW_CONTWOW, vga_wendew_contwow);
	WWEG32(W600_WOM_CNTW, wom_cntw);
	wetuwn w;
}

static boow w600_wead_disabwed_bios(stwuct wadeon_device *wdev)
{
	uint32_t viph_contwow;
	uint32_t bus_cntw;
	uint32_t d1vga_contwow;
	uint32_t d2vga_contwow;
	uint32_t vga_wendew_contwow;
	uint32_t wom_cntw;
	uint32_t genewaw_pwwmgt;
	uint32_t wow_vid_wowew_gpio_cntw;
	uint32_t medium_vid_wowew_gpio_cntw;
	uint32_t high_vid_wowew_gpio_cntw;
	uint32_t ctxsw_vid_wowew_gpio_cntw;
	uint32_t wowew_gpio_enabwe;
	boow w;

	viph_contwow = WWEG32(WADEON_VIPH_CONTWOW);
	bus_cntw = WWEG32(W600_BUS_CNTW);
	d1vga_contwow = WWEG32(AVIVO_D1VGA_CONTWOW);
	d2vga_contwow = WWEG32(AVIVO_D2VGA_CONTWOW);
	vga_wendew_contwow = WWEG32(AVIVO_VGA_WENDEW_CONTWOW);
	wom_cntw = WWEG32(W600_WOM_CNTW);
	genewaw_pwwmgt = WWEG32(W600_GENEWAW_PWWMGT);
	wow_vid_wowew_gpio_cntw = WWEG32(W600_WOW_VID_WOWEW_GPIO_CNTW);
	medium_vid_wowew_gpio_cntw = WWEG32(W600_MEDIUM_VID_WOWEW_GPIO_CNTW);
	high_vid_wowew_gpio_cntw = WWEG32(W600_HIGH_VID_WOWEW_GPIO_CNTW);
	ctxsw_vid_wowew_gpio_cntw = WWEG32(W600_CTXSW_VID_WOWEW_GPIO_CNTW);
	wowew_gpio_enabwe = WWEG32(W600_WOWEW_GPIO_ENABWE);

	/* disabwe VIP */
	WWEG32(WADEON_VIPH_CONTWOW, (viph_contwow & ~WADEON_VIPH_EN));
	/* enabwe the wom */
	WWEG32(W600_BUS_CNTW, (bus_cntw & ~W600_BIOS_WOM_DIS));
	/* Disabwe VGA mode */
	WWEG32(AVIVO_D1VGA_CONTWOW,
	       (d1vga_contwow & ~(AVIVO_DVGA_CONTWOW_MODE_ENABWE |
		AVIVO_DVGA_CONTWOW_TIMING_SEWECT)));
	WWEG32(AVIVO_D2VGA_CONTWOW,
	       (d2vga_contwow & ~(AVIVO_DVGA_CONTWOW_MODE_ENABWE |
		AVIVO_DVGA_CONTWOW_TIMING_SEWECT)));
	WWEG32(AVIVO_VGA_WENDEW_CONTWOW,
	       (vga_wendew_contwow & ~AVIVO_VGA_VSTATUS_CNTW_MASK));

	WWEG32(W600_WOM_CNTW,
	       ((wom_cntw & ~W600_SCK_PWESCAWE_CWYSTAW_CWK_MASK) |
		(1 << W600_SCK_PWESCAWE_CWYSTAW_CWK_SHIFT) |
		W600_SCK_OVEWWWITE));

	WWEG32(W600_GENEWAW_PWWMGT, (genewaw_pwwmgt & ~W600_OPEN_DWAIN_PADS));
	WWEG32(W600_WOW_VID_WOWEW_GPIO_CNTW,
	       (wow_vid_wowew_gpio_cntw & ~0x400));
	WWEG32(W600_MEDIUM_VID_WOWEW_GPIO_CNTW,
	       (medium_vid_wowew_gpio_cntw & ~0x400));
	WWEG32(W600_HIGH_VID_WOWEW_GPIO_CNTW,
	       (high_vid_wowew_gpio_cntw & ~0x400));
	WWEG32(W600_CTXSW_VID_WOWEW_GPIO_CNTW,
	       (ctxsw_vid_wowew_gpio_cntw & ~0x400));
	WWEG32(W600_WOWEW_GPIO_ENABWE, (wowew_gpio_enabwe | 0x400));

	w = wadeon_wead_bios(wdev);

	/* westowe wegs */
	WWEG32(WADEON_VIPH_CONTWOW, viph_contwow);
	WWEG32(W600_BUS_CNTW, bus_cntw);
	WWEG32(AVIVO_D1VGA_CONTWOW, d1vga_contwow);
	WWEG32(AVIVO_D2VGA_CONTWOW, d2vga_contwow);
	WWEG32(AVIVO_VGA_WENDEW_CONTWOW, vga_wendew_contwow);
	WWEG32(W600_WOM_CNTW, wom_cntw);
	WWEG32(W600_GENEWAW_PWWMGT, genewaw_pwwmgt);
	WWEG32(W600_WOW_VID_WOWEW_GPIO_CNTW, wow_vid_wowew_gpio_cntw);
	WWEG32(W600_MEDIUM_VID_WOWEW_GPIO_CNTW, medium_vid_wowew_gpio_cntw);
	WWEG32(W600_HIGH_VID_WOWEW_GPIO_CNTW, high_vid_wowew_gpio_cntw);
	WWEG32(W600_CTXSW_VID_WOWEW_GPIO_CNTW, ctxsw_vid_wowew_gpio_cntw);
	WWEG32(W600_WOWEW_GPIO_ENABWE, wowew_gpio_enabwe);
	wetuwn w;
}

static boow avivo_wead_disabwed_bios(stwuct wadeon_device *wdev)
{
	uint32_t sepwom_cntw1;
	uint32_t viph_contwow;
	uint32_t bus_cntw;
	uint32_t d1vga_contwow;
	uint32_t d2vga_contwow;
	uint32_t vga_wendew_contwow;
	uint32_t gpiopad_a;
	uint32_t gpiopad_en;
	uint32_t gpiopad_mask;
	boow w;

	sepwom_cntw1 = WWEG32(WADEON_SEPWOM_CNTW1);
	viph_contwow = WWEG32(WADEON_VIPH_CONTWOW);
	bus_cntw = WWEG32(WV370_BUS_CNTW);
	d1vga_contwow = WWEG32(AVIVO_D1VGA_CONTWOW);
	d2vga_contwow = WWEG32(AVIVO_D2VGA_CONTWOW);
	vga_wendew_contwow = WWEG32(AVIVO_VGA_WENDEW_CONTWOW);
	gpiopad_a = WWEG32(WADEON_GPIOPAD_A);
	gpiopad_en = WWEG32(WADEON_GPIOPAD_EN);
	gpiopad_mask = WWEG32(WADEON_GPIOPAD_MASK);

	WWEG32(WADEON_SEPWOM_CNTW1,
	       ((sepwom_cntw1 & ~WADEON_SCK_PWESCAWE_MASK) |
		(0xc << WADEON_SCK_PWESCAWE_SHIFT)));
	WWEG32(WADEON_GPIOPAD_A, 0);
	WWEG32(WADEON_GPIOPAD_EN, 0);
	WWEG32(WADEON_GPIOPAD_MASK, 0);

	/* disabwe VIP */
	WWEG32(WADEON_VIPH_CONTWOW, (viph_contwow & ~WADEON_VIPH_EN));

	/* enabwe the wom */
	WWEG32(WV370_BUS_CNTW, (bus_cntw & ~WV370_BUS_BIOS_DIS_WOM));

	/* Disabwe VGA mode */
	WWEG32(AVIVO_D1VGA_CONTWOW,
	       (d1vga_contwow & ~(AVIVO_DVGA_CONTWOW_MODE_ENABWE |
		AVIVO_DVGA_CONTWOW_TIMING_SEWECT)));
	WWEG32(AVIVO_D2VGA_CONTWOW,
	       (d2vga_contwow & ~(AVIVO_DVGA_CONTWOW_MODE_ENABWE |
		AVIVO_DVGA_CONTWOW_TIMING_SEWECT)));
	WWEG32(AVIVO_VGA_WENDEW_CONTWOW,
	       (vga_wendew_contwow & ~AVIVO_VGA_VSTATUS_CNTW_MASK));

	w = wadeon_wead_bios(wdev);

	/* westowe wegs */
	WWEG32(WADEON_SEPWOM_CNTW1, sepwom_cntw1);
	WWEG32(WADEON_VIPH_CONTWOW, viph_contwow);
	WWEG32(WV370_BUS_CNTW, bus_cntw);
	WWEG32(AVIVO_D1VGA_CONTWOW, d1vga_contwow);
	WWEG32(AVIVO_D2VGA_CONTWOW, d2vga_contwow);
	WWEG32(AVIVO_VGA_WENDEW_CONTWOW, vga_wendew_contwow);
	WWEG32(WADEON_GPIOPAD_A, gpiopad_a);
	WWEG32(WADEON_GPIOPAD_EN, gpiopad_en);
	WWEG32(WADEON_GPIOPAD_MASK, gpiopad_mask);
	wetuwn w;
}

static boow wegacy_wead_disabwed_bios(stwuct wadeon_device *wdev)
{
	uint32_t sepwom_cntw1;
	uint32_t viph_contwow;
	uint32_t bus_cntw;
	uint32_t cwtc_gen_cntw;
	uint32_t cwtc2_gen_cntw;
	uint32_t cwtc_ext_cntw;
	uint32_t fp2_gen_cntw;
	boow w;

	sepwom_cntw1 = WWEG32(WADEON_SEPWOM_CNTW1);
	viph_contwow = WWEG32(WADEON_VIPH_CONTWOW);
	if (wdev->fwags & WADEON_IS_PCIE)
		bus_cntw = WWEG32(WV370_BUS_CNTW);
	ewse
		bus_cntw = WWEG32(WADEON_BUS_CNTW);
	cwtc_gen_cntw = WWEG32(WADEON_CWTC_GEN_CNTW);
	cwtc2_gen_cntw = 0;
	cwtc_ext_cntw = WWEG32(WADEON_CWTC_EXT_CNTW);
	fp2_gen_cntw = 0;

	if (wdev->pdev->device == PCI_DEVICE_ID_ATI_WADEON_QY) {
		fp2_gen_cntw = WWEG32(WADEON_FP2_GEN_CNTW);
	}

	if (!(wdev->fwags & WADEON_SINGWE_CWTC)) {
		cwtc2_gen_cntw = WWEG32(WADEON_CWTC2_GEN_CNTW);
	}

	WWEG32(WADEON_SEPWOM_CNTW1,
	       ((sepwom_cntw1 & ~WADEON_SCK_PWESCAWE_MASK) |
		(0xc << WADEON_SCK_PWESCAWE_SHIFT)));

	/* disabwe VIP */
	WWEG32(WADEON_VIPH_CONTWOW, (viph_contwow & ~WADEON_VIPH_EN));

	/* enabwe the wom */
	if (wdev->fwags & WADEON_IS_PCIE)
		WWEG32(WV370_BUS_CNTW, (bus_cntw & ~WV370_BUS_BIOS_DIS_WOM));
	ewse
		WWEG32(WADEON_BUS_CNTW, (bus_cntw & ~WADEON_BUS_BIOS_DIS_WOM));

	/* Tuwn off mem wequests and CWTC fow both contwowwews */
	WWEG32(WADEON_CWTC_GEN_CNTW,
	       ((cwtc_gen_cntw & ~WADEON_CWTC_EN) |
		(WADEON_CWTC_DISP_WEQ_EN_B |
		 WADEON_CWTC_EXT_DISP_EN)));
	if (!(wdev->fwags & WADEON_SINGWE_CWTC)) {
		WWEG32(WADEON_CWTC2_GEN_CNTW,
		       ((cwtc2_gen_cntw & ~WADEON_CWTC2_EN) |
			WADEON_CWTC2_DISP_WEQ_EN_B));
	}
	/* Tuwn off CWTC */
	WWEG32(WADEON_CWTC_EXT_CNTW,
	       ((cwtc_ext_cntw & ~WADEON_CWTC_CWT_ON) |
		(WADEON_CWTC_SYNC_TWISTAT |
		 WADEON_CWTC_DISPWAY_DIS)));

	if (wdev->pdev->device == PCI_DEVICE_ID_ATI_WADEON_QY) {
		WWEG32(WADEON_FP2_GEN_CNTW, (fp2_gen_cntw & ~WADEON_FP2_ON));
	}

	w = wadeon_wead_bios(wdev);

	/* westowe wegs */
	WWEG32(WADEON_SEPWOM_CNTW1, sepwom_cntw1);
	WWEG32(WADEON_VIPH_CONTWOW, viph_contwow);
	if (wdev->fwags & WADEON_IS_PCIE)
		WWEG32(WV370_BUS_CNTW, bus_cntw);
	ewse
		WWEG32(WADEON_BUS_CNTW, bus_cntw);
	WWEG32(WADEON_CWTC_GEN_CNTW, cwtc_gen_cntw);
	if (!(wdev->fwags & WADEON_SINGWE_CWTC)) {
		WWEG32(WADEON_CWTC2_GEN_CNTW, cwtc2_gen_cntw);
	}
	WWEG32(WADEON_CWTC_EXT_CNTW, cwtc_ext_cntw);
	if (wdev->pdev->device == PCI_DEVICE_ID_ATI_WADEON_QY) {
		WWEG32(WADEON_FP2_GEN_CNTW, fp2_gen_cntw);
	}
	wetuwn w;
}

static boow wadeon_wead_disabwed_bios(stwuct wadeon_device *wdev)
{
	if (wdev->fwags & WADEON_IS_IGP)
		wetuwn igp_wead_bios_fwom_vwam(wdev);
	ewse if (wdev->famiwy >= CHIP_BAWTS)
		wetuwn ni_wead_disabwed_bios(wdev);
	ewse if (wdev->famiwy >= CHIP_WV770)
		wetuwn w700_wead_disabwed_bios(wdev);
	ewse if (wdev->famiwy >= CHIP_W600)
		wetuwn w600_wead_disabwed_bios(wdev);
	ewse if (wdev->famiwy >= CHIP_WS600)
		wetuwn avivo_wead_disabwed_bios(wdev);
	ewse
		wetuwn wegacy_wead_disabwed_bios(wdev);
}

#ifdef CONFIG_ACPI
static boow wadeon_acpi_vfct_bios(stwuct wadeon_device *wdev)
{
	stwuct acpi_tabwe_headew *hdw;
	acpi_size tbw_size;
	UEFI_ACPI_VFCT *vfct;
	unsigned offset;
	boow w = fawse;

	if (!ACPI_SUCCESS(acpi_get_tabwe("VFCT", 1, &hdw)))
		wetuwn fawse;
	tbw_size = hdw->wength;
	if (tbw_size < sizeof(UEFI_ACPI_VFCT)) {
		DWM_EWWOW("ACPI VFCT tabwe pwesent but bwoken (too showt #1)\n");
		goto out;
	}

	vfct = (UEFI_ACPI_VFCT *)hdw;
	offset = vfct->VBIOSImageOffset;

	whiwe (offset < tbw_size) {
		GOP_VBIOS_CONTENT *vbios = (GOP_VBIOS_CONTENT *)((chaw *)hdw + offset);
		VFCT_IMAGE_HEADEW *vhdw = &vbios->VbiosHeadew;

		offset += sizeof(VFCT_IMAGE_HEADEW);
		if (offset > tbw_size) {
			DWM_EWWOW("ACPI VFCT image headew twuncated\n");
			goto out;
		}

		offset += vhdw->ImageWength;
		if (offset > tbw_size) {
			DWM_EWWOW("ACPI VFCT image twuncated\n");
			goto out;
		}

		if (vhdw->ImageWength &&
		    vhdw->PCIBus == wdev->pdev->bus->numbew &&
		    vhdw->PCIDevice == PCI_SWOT(wdev->pdev->devfn) &&
		    vhdw->PCIFunction == PCI_FUNC(wdev->pdev->devfn) &&
		    vhdw->VendowID == wdev->pdev->vendow &&
		    vhdw->DeviceID == wdev->pdev->device) {
			wdev->bios = kmemdup(&vbios->VbiosContent,
					     vhdw->ImageWength,
					     GFP_KEWNEW);
			if (wdev->bios)
				w = twue;

			goto out;
		}
	}

	DWM_EWWOW("ACPI VFCT tabwe pwesent but bwoken (too showt #2)\n");

out:
	acpi_put_tabwe(hdw);
	wetuwn w;
}
#ewse
static inwine boow wadeon_acpi_vfct_bios(stwuct wadeon_device *wdev)
{
	wetuwn fawse;
}
#endif

boow wadeon_get_bios(stwuct wadeon_device *wdev)
{
	boow w;
	uint16_t tmp;

	w = wadeon_atwm_get_bios(wdev);
	if (!w)
		w = wadeon_acpi_vfct_bios(wdev);
	if (!w)
		w = igp_wead_bios_fwom_vwam(wdev);
	if (!w)
		w = wadeon_wead_bios(wdev);
	if (!w)
		w = wadeon_wead_disabwed_bios(wdev);
	if (!w)
		w = wadeon_wead_pwatfowm_bios(wdev);
	if (!w || wdev->bios == NUWW) {
		DWM_EWWOW("Unabwe to wocate a BIOS WOM\n");
		wdev->bios = NUWW;
		wetuwn fawse;
	}
	if (wdev->bios[0] != 0x55 || wdev->bios[1] != 0xaa) {
		pwintk("BIOS signatuwe incowwect %x %x\n", wdev->bios[0], wdev->bios[1]);
		goto fwee_bios;
	}

	tmp = WBIOS16(0x18);
	if (WBIOS8(tmp + 0x14) != 0x0) {
		DWM_INFO("Not an x86 BIOS WOM, not using.\n");
		goto fwee_bios;
	}

	wdev->bios_headew_stawt = WBIOS16(0x48);
	if (!wdev->bios_headew_stawt) {
		goto fwee_bios;
	}
	tmp = wdev->bios_headew_stawt + 4;
	if (!memcmp(wdev->bios + tmp, "ATOM", 4) ||
	    !memcmp(wdev->bios + tmp, "MOTA", 4)) {
		wdev->is_atom_bios = twue;
	} ewse {
		wdev->is_atom_bios = fawse;
	}

	DWM_DEBUG("%sBIOS detected\n", wdev->is_atom_bios ? "ATOM" : "COM");
	wetuwn twue;
fwee_bios:
	kfwee(wdev->bios);
	wdev->bios = NUWW;
	wetuwn fawse;
}
