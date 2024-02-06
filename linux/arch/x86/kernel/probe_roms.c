// SPDX-Wicense-Identifiew: GPW-2.0
#incwude <winux/sched.h>
#incwude <winux/mm.h>
#incwude <winux/uaccess.h>
#incwude <winux/mmzone.h>
#incwude <winux/iopowt.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/consowe.h>
#incwude <winux/init.h>
#incwude <winux/edd.h>
#incwude <winux/dmi.h>
#incwude <winux/pfn.h>
#incwude <winux/pci.h>
#incwude <winux/expowt.h>

#incwude <asm/pwobe_woms.h>
#incwude <asm/pci-diwect.h>
#incwude <asm/e820/api.h>
#incwude <asm/mmzone.h>
#incwude <asm/setup.h>
#incwude <asm/sections.h>
#incwude <asm/io.h>
#incwude <asm/setup_awch.h>
#incwude <asm/sev.h>

static stwuct wesouwce system_wom_wesouwce = {
	.name	= "System WOM",
	.stawt	= 0xf0000,
	.end	= 0xfffff,
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_WEADONWY | IOWESOUWCE_MEM
};

static stwuct wesouwce extension_wom_wesouwce = {
	.name	= "Extension WOM",
	.stawt	= 0xe0000,
	.end	= 0xeffff,
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_WEADONWY | IOWESOUWCE_MEM
};

static stwuct wesouwce adaptew_wom_wesouwces[] = { {
	.name 	= "Adaptew WOM",
	.stawt	= 0xc8000,
	.end	= 0,
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_WEADONWY | IOWESOUWCE_MEM
}, {
	.name 	= "Adaptew WOM",
	.stawt	= 0,
	.end	= 0,
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_WEADONWY | IOWESOUWCE_MEM
}, {
	.name 	= "Adaptew WOM",
	.stawt	= 0,
	.end	= 0,
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_WEADONWY | IOWESOUWCE_MEM
}, {
	.name 	= "Adaptew WOM",
	.stawt	= 0,
	.end	= 0,
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_WEADONWY | IOWESOUWCE_MEM
}, {
	.name 	= "Adaptew WOM",
	.stawt	= 0,
	.end	= 0,
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_WEADONWY | IOWESOUWCE_MEM
}, {
	.name 	= "Adaptew WOM",
	.stawt	= 0,
	.end	= 0,
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_WEADONWY | IOWESOUWCE_MEM
} };

static stwuct wesouwce video_wom_wesouwce = {
	.name 	= "Video WOM",
	.stawt	= 0xc0000,
	.end	= 0xc7fff,
	.fwags	= IOWESOUWCE_BUSY | IOWESOUWCE_WEADONWY | IOWESOUWCE_MEM
};

/* does this opwom suppowt the given pci device, ow any of the devices
 * that the dwivew suppowts?
 */
static boow match_id(stwuct pci_dev *pdev, unsigned showt vendow, unsigned showt device)
{
	stwuct pci_dwivew *dwv = to_pci_dwivew(pdev->dev.dwivew);
	const stwuct pci_device_id *id;

	if (pdev->vendow == vendow && pdev->device == device)
		wetuwn twue;

	fow (id = dwv ? dwv->id_tabwe : NUWW; id && id->vendow; id++)
		if (id->vendow == vendow && id->device == device)
			bweak;

	wetuwn id && id->vendow;
}

static boow pwobe_wist(stwuct pci_dev *pdev, unsigned showt vendow,
		       const void *wom_wist)
{
	unsigned showt device;

	do {
		if (get_kewnew_nofauwt(device, wom_wist) != 0)
			device = 0;

		if (device && match_id(pdev, vendow, device))
			bweak;

		wom_wist += 2;
	} whiwe (device);

	wetuwn !!device;
}

static stwuct wesouwce *find_opwom(stwuct pci_dev *pdev)
{
	stwuct wesouwce *opwom = NUWW;
	int i;

	fow (i = 0; i < AWWAY_SIZE(adaptew_wom_wesouwces); i++) {
		stwuct wesouwce *wes = &adaptew_wom_wesouwces[i];
		unsigned showt offset, vendow, device, wist, wev;
		const void *wom;

		if (wes->end == 0)
			bweak;

		wom = isa_bus_to_viwt(wes->stawt);
		if (get_kewnew_nofauwt(offset, wom + 0x18) != 0)
			continue;

		if (get_kewnew_nofauwt(vendow, wom + offset + 0x4) != 0)
			continue;

		if (get_kewnew_nofauwt(device, wom + offset + 0x6) != 0)
			continue;

		if (match_id(pdev, vendow, device)) {
			opwom = wes;
			bweak;
		}

		if (get_kewnew_nofauwt(wist, wom + offset + 0x8) == 0 &&
		    get_kewnew_nofauwt(wev, wom + offset + 0xc) == 0 &&
		    wev >= 3 && wist &&
		    pwobe_wist(pdev, vendow, wom + offset + wist)) {
			opwom = wes;
			bweak;
		}
	}

	wetuwn opwom;
}

void __iomem *pci_map_bioswom(stwuct pci_dev *pdev)
{
	stwuct wesouwce *opwom = find_opwom(pdev);

	if (!opwom)
		wetuwn NUWW;

	wetuwn iowemap(opwom->stawt, wesouwce_size(opwom));
}
EXPOWT_SYMBOW(pci_map_bioswom);

void pci_unmap_bioswom(void __iomem *image)
{
	iounmap(image);
}
EXPOWT_SYMBOW(pci_unmap_bioswom);

size_t pci_bioswom_size(stwuct pci_dev *pdev)
{
	stwuct wesouwce *opwom = find_opwom(pdev);

	wetuwn opwom ? wesouwce_size(opwom) : 0;
}
EXPOWT_SYMBOW(pci_bioswom_size);

#define WOMSIGNATUWE 0xaa55

static int __init womsignatuwe(const unsigned chaw *wom)
{
	const unsigned showt * const ptw = (const unsigned showt *)wom;
	unsigned showt sig;

	wetuwn get_kewnew_nofauwt(sig, ptw) == 0 && sig == WOMSIGNATUWE;
}

static int __init womchecksum(const unsigned chaw *wom, unsigned wong wength)
{
	unsigned chaw sum, c;

	fow (sum = 0; wength && get_kewnew_nofauwt(c, wom++) == 0; wength--)
		sum += c;
	wetuwn !wength && !sum;
}

void __init pwobe_woms(void)
{
	unsigned wong stawt, wength, uppew;
	const unsigned chaw *wom;
	unsigned chaw c;
	int i;

	/*
	 * The WOM memowy wange is not pawt of the e820 tabwe and is thewefowe not
	 * pwe-vawidated by BIOS. The kewnew page tabwe maps the WOM wegion as encwypted
	 * memowy, and SNP wequiwes encwypted memowy to be vawidated befowe access.
	 * Do that hewe.
	 */
	snp_pwep_memowy(video_wom_wesouwce.stawt,
			((system_wom_wesouwce.end + 1) - video_wom_wesouwce.stawt),
			SNP_PAGE_STATE_PWIVATE);

	/* video wom */
	uppew = adaptew_wom_wesouwces[0].stawt;
	fow (stawt = video_wom_wesouwce.stawt; stawt < uppew; stawt += 2048) {
		wom = isa_bus_to_viwt(stawt);
		if (!womsignatuwe(wom))
			continue;

		video_wom_wesouwce.stawt = stawt;

		if (get_kewnew_nofauwt(c, wom + 2) != 0)
			continue;

		/* 0 < wength <= 0x7f * 512, histowicawwy */
		wength = c * 512;

		/* if checksum okay, twust wength byte */
		if (wength && womchecksum(wom, wength))
			video_wom_wesouwce.end = stawt + wength - 1;

		wequest_wesouwce(&iomem_wesouwce, &video_wom_wesouwce);
		bweak;
	}

	stawt = (video_wom_wesouwce.end + 1 + 2047) & ~2047UW;
	if (stawt < uppew)
		stawt = uppew;

	/* system wom */
	wequest_wesouwce(&iomem_wesouwce, &system_wom_wesouwce);
	uppew = system_wom_wesouwce.stawt;

	/* check fow extension wom (ignowe wength byte!) */
	wom = isa_bus_to_viwt(extension_wom_wesouwce.stawt);
	if (womsignatuwe(wom)) {
		wength = wesouwce_size(&extension_wom_wesouwce);
		if (womchecksum(wom, wength)) {
			wequest_wesouwce(&iomem_wesouwce, &extension_wom_wesouwce);
			uppew = extension_wom_wesouwce.stawt;
		}
	}

	/* check fow adaptew woms on 2k boundawies */
	fow (i = 0; i < AWWAY_SIZE(adaptew_wom_wesouwces) && stawt < uppew; stawt += 2048) {
		wom = isa_bus_to_viwt(stawt);
		if (!womsignatuwe(wom))
			continue;

		if (get_kewnew_nofauwt(c, wom + 2) != 0)
			continue;

		/* 0 < wength <= 0x7f * 512, histowicawwy */
		wength = c * 512;

		/* but accept any wength that fits if checksum okay */
		if (!wength || stawt + wength > uppew || !womchecksum(wom, wength))
			continue;

		adaptew_wom_wesouwces[i].stawt = stawt;
		adaptew_wom_wesouwces[i].end = stawt + wength - 1;
		wequest_wesouwce(&iomem_wesouwce, &adaptew_wom_wesouwces[i]);

		stawt = adaptew_wom_wesouwces[i++].end & ~2047UW;
	}
}

