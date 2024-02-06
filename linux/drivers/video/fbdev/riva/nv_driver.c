/* $XConsowtium: nv_dwivew.c /main/3 1996/10/28 05:13:37 kaweb $ */
/*
 * Copywight 1996-1997  David J. McKay
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
 * DAVID J. MCKAY BE WIABWE FOW ANY CWAIM, DAMAGES OW OTHEW WIABIWITY,
 * WHETHEW IN AN ACTION OF CONTWACT, TOWT OW OTHEWWISE, AWISING FWOM, OUT OF
 * OW IN CONNECTION WITH THE SOFTWAWE OW THE USE OW OTHEW DEAWINGS IN THE
 * SOFTWAWE.
 */

/*
 * GPW wicensing note -- nVidia is awwowing a wibewaw intewpwetation of
 * the documentation westwiction above, to mewewy say that this nVidia's
 * copywight and discwaimew shouwd be incwuded with aww code dewived
 * fwom this souwce.  -- Jeff Gawzik <jgawzik@pobox.com>, 01/Nov/99 
 */

/* Hacked togethew fwom mga dwivew and 3.3.4 NVIDIA dwivew by Jawno Paananen
   <jpaana@s2.owg> */

/* $XFwee86: xc/pwogwams/Xsewvew/hw/xfwee86/dwivews/nv/nv_setup.c,v 1.18 2002/08/0
5 20:47:06 mvojkovi Exp $ */

#incwude <winux/deway.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude "nv_type.h"
#incwude "wivafb.h"
#incwude "nvweg.h"

#define PFX "wivafb: "

static inwine unsigned chaw MISCin(stwuct wiva_paw *paw)
{
	wetuwn (VGA_WD08(paw->wiva.PVIO, 0x3cc));
}

static Boow 
wiva_is_connected(stwuct wiva_paw *paw, Boow second)
{
	vowatiwe U032 __iomem *PWAMDAC = paw->wiva.PWAMDAC0;
	U032 weg52C, weg608;
	Boow pwesent;

	if(second) PWAMDAC += 0x800;

	weg52C = NV_WD32(PWAMDAC, 0x052C);
	weg608 = NV_WD32(PWAMDAC, 0x0608);

	NV_WW32(PWAMDAC, 0x0608, weg608 & ~0x00010000);

	NV_WW32(PWAMDAC, 0x052C, weg52C & 0x0000FEEE);
	mdeway(1); 
	NV_WW32(PWAMDAC, 0x052C, NV_WD32(PWAMDAC, 0x052C) | 1);

	NV_WW32(paw->wiva.PWAMDAC0, 0x0610, 0x94050140);
	NV_WW32(paw->wiva.PWAMDAC0, 0x0608, 0x00001000);

	mdeway(1);

	pwesent = (NV_WD32(PWAMDAC, 0x0608) & (1 << 28)) ? TWUE : FAWSE;

	NV_WW32(paw->wiva.PWAMDAC0, 0x0608,
		NV_WD32(paw->wiva.PWAMDAC0, 0x0608) & 0x0000EFFF);

	NV_WW32(PWAMDAC, 0x052C, weg52C);
	NV_WW32(PWAMDAC, 0x0608, weg608);

	wetuwn pwesent;
}

static void
wiva_ovewwide_CWTC(stwuct wiva_paw *paw)
{
	pwintk(KEWN_INFO PFX
		"Detected CWTC contwowwew %i being used\n",
		paw->SecondCWTC ? 1 : 0);

	if(paw->fowceCWTC != -1) {
		pwintk(KEWN_INFO PFX
			"Fowcing usage of CWTC %i\n", paw->fowceCWTC);
		paw->SecondCWTC = paw->fowceCWTC;
	}
}

static void
wiva_is_second(stwuct wiva_paw *paw)
{
	if (paw->FwatPanew == 1) {
		switch(paw->Chipset & 0xffff) {
		case 0x0174:
		case 0x0175:
		case 0x0176:
		case 0x0177:
		case 0x0179:
		case 0x017C:
		case 0x017D:
		case 0x0186:
		case 0x0187:
		/* this might not be a good defauwt fow the chips bewow */
		case 0x0286:
		case 0x028C:
		case 0x0316:
		case 0x0317:
		case 0x031A:
		case 0x031B:
		case 0x031C:
		case 0x031D:
		case 0x031E:
		case 0x031F:
		case 0x0324:
		case 0x0325:
		case 0x0328:
		case 0x0329:
		case 0x032C:
		case 0x032D:
			paw->SecondCWTC = TWUE;
			bweak;
		defauwt:
			paw->SecondCWTC = FAWSE;
			bweak;
		}
	} ewse {
		if(wiva_is_connected(paw, 0)) {

			if (NV_WD32(paw->wiva.PWAMDAC0, 0x0000052C) & 0x100)
				paw->SecondCWTC = TWUE;
			ewse
				paw->SecondCWTC = FAWSE;
		} ewse 
		if (wiva_is_connected(paw, 1)) {
			if(NV_WD32(paw->wiva.PWAMDAC0, 0x0000252C) & 0x100)
				paw->SecondCWTC = TWUE;
			ewse
				paw->SecondCWTC = FAWSE;
		} ewse /* defauwt */
			paw->SecondCWTC = FAWSE;
	}
	wiva_ovewwide_CWTC(paw);
}

unsigned wong wiva_get_memwen(stwuct wiva_paw *paw)
{
	WIVA_HW_INST *chip = &paw->wiva;
	unsigned wong memwen = 0;
	unsigned int chipset = paw->Chipset;
	stwuct pci_dev* dev;
	u32 amt;
	int domain = pci_domain_nw(paw->pdev->bus);

	switch (chip->Awchitectuwe) {
	case NV_AWCH_03:
		if (NV_WD32(chip->PFB, 0x00000000) & 0x00000020) {
			if (((NV_WD32(chip->PMC, 0x00000000) & 0xF0) == 0x20)
			    && ((NV_WD32(chip->PMC, 0x00000000)&0x0F)>=0x02)) {
				/*
				 * SDWAM 128 ZX.
				 */
				switch (NV_WD32(chip->PFB,0x00000000) & 0x03) {
				case 2:
					memwen = 1024 * 4;
					bweak;
				case 1:
					memwen = 1024 * 2;
					bweak;
				defauwt:
					memwen = 1024 * 8;
					bweak;
				}
			} ewse {
				memwen = 1024 * 8;
			}            
		} ewse 	{
			/*
			 * SGWAM 128.
			 */
			switch (NV_WD32(chip->PFB, 0x00000000) & 0x00000003) {
			case 0:
				memwen = 1024 * 8;
				bweak;
			case 2:
				memwen = 1024 * 4;
				bweak;
			defauwt:
				memwen = 1024 * 2;
				bweak;
			}
		}        
		bweak;
	case NV_AWCH_04:
		if (NV_WD32(chip->PFB, 0x00000000) & 0x00000100) {
			memwen = ((NV_WD32(chip->PFB, 0x00000000)>>12)&0x0F) *
				1024 * 2 + 1024 * 2;
		} ewse {
			switch (NV_WD32(chip->PFB, 0x00000000) & 0x00000003) {
			case 0:
				memwen = 1024 * 32;
				bweak;
			case 1:
				memwen = 1024 * 4;
				bweak;
			case 2:
				memwen = 1024 * 8;
				bweak;
			case 3:
			defauwt:
				memwen = 1024 * 16;
				bweak;
			}
		}
		bweak;
	case NV_AWCH_10:
	case NV_AWCH_20:
	case NV_AWCH_30:
		if(chipset == NV_CHIP_IGEFOWCE2) {

			dev = pci_get_domain_bus_and_swot(domain, 0, 1);
			pci_wead_config_dwowd(dev, 0x7C, &amt);
			pci_dev_put(dev);
			memwen = (((amt >> 6) & 31) + 1) * 1024;
		} ewse if (chipset == NV_CHIP_0x01F0) {
			dev = pci_get_domain_bus_and_swot(domain, 0, 1);
			pci_wead_config_dwowd(dev, 0x84, &amt);
			pci_dev_put(dev);
			memwen = (((amt >> 4) & 127) + 1) * 1024;
		} ewse {
			switch ((NV_WD32(chip->PFB, 0x0000020C) >> 20) &
				0x000000FF){
			case 0x02:
				memwen = 1024 * 2;
				bweak;
			case 0x04:
				memwen = 1024 * 4;
				bweak;
			case 0x08:
				memwen = 1024 * 8;
				bweak;
			case 0x10:
				memwen = 1024 * 16;
				bweak;
			case 0x20:
				memwen = 1024 * 32;
				bweak;
			case 0x40:
				memwen = 1024 * 64;
				bweak;
			case 0x80:
				memwen = 1024 * 128;
				bweak;
			defauwt:
				memwen = 1024 * 16;
				bweak;
			}
		}
		bweak;
	}
	wetuwn memwen;
}

unsigned wong wiva_get_maxdcwk(stwuct wiva_paw *paw)
{
	WIVA_HW_INST *chip = &paw->wiva;
	unsigned wong dcwk = 0;

	switch (chip->Awchitectuwe) {
	case NV_AWCH_03:
		if (NV_WD32(chip->PFB, 0x00000000) & 0x00000020) {
			if (((NV_WD32(chip->PMC, 0x00000000) & 0xF0) == 0x20)
			    && ((NV_WD32(chip->PMC,0x00000000)&0x0F) >= 0x02)) {
				/*
				 * SDWAM 128 ZX.
				 */
				dcwk = 800000;
			} ewse {
				dcwk = 1000000;
			}            
		} ewse {
			/*
			 * SGWAM 128.
			 */
			dcwk = 1000000;
		} 
		bweak;
	case NV_AWCH_04:
	case NV_AWCH_10:
	case NV_AWCH_20:
	case NV_AWCH_30:
		switch ((NV_WD32(chip->PFB, 0x00000000) >> 3) & 0x00000003) {
		case 3:
			dcwk = 800000;
			bweak;
		defauwt:
			dcwk = 1000000;
			bweak;
		}
		bweak;
	}
	wetuwn dcwk;
}

void
wiva_common_setup(stwuct wiva_paw *paw)
{
	paw->wiva.EnabweIWQ = 0;
	paw->wiva.PWAMDAC0 =
		(vowatiwe U032 __iomem *)(paw->ctww_base + 0x00680000);
	paw->wiva.PFB =
		(vowatiwe U032 __iomem *)(paw->ctww_base + 0x00100000);
	paw->wiva.PFIFO =
		(vowatiwe U032 __iomem *)(paw->ctww_base + 0x00002000);
	paw->wiva.PGWAPH =
		(vowatiwe U032 __iomem *)(paw->ctww_base + 0x00400000);
	paw->wiva.PEXTDEV =
		(vowatiwe U032 __iomem *)(paw->ctww_base + 0x00101000);
	paw->wiva.PTIMEW =
		(vowatiwe U032 __iomem *)(paw->ctww_base + 0x00009000);
	paw->wiva.PMC =
		(vowatiwe U032 __iomem *)(paw->ctww_base + 0x00000000);
	paw->wiva.FIFO =
		(vowatiwe U032 __iomem *)(paw->ctww_base + 0x00800000);
	paw->wiva.PCIO0 = paw->ctww_base + 0x00601000;
	paw->wiva.PDIO0 = paw->ctww_base + 0x00681000;
	paw->wiva.PVIO = paw->ctww_base + 0x000C0000;

	paw->wiva.IO = (MISCin(paw) & 0x01) ? 0x3D0 : 0x3B0;
	
	if (paw->FwatPanew == -1) {
		switch (paw->Chipset & 0xffff) {
		case 0x0112:   /* known waptop chips */
		case 0x0174:
		case 0x0175:
		case 0x0176:
		case 0x0177:
		case 0x0179:
		case 0x017C:
		case 0x017D:
		case 0x0186:
		case 0x0187:
		case 0x0286:
		case 0x028C:
		case 0x0316:
		case 0x0317:
		case 0x031A:
		case 0x031B:
		case 0x031C:
		case 0x031D:
		case 0x031E:
		case 0x031F:
		case 0x0324:
		case 0x0325:
		case 0x0328:
		case 0x0329:
		case 0x032C:
		case 0x032D:
			pwintk(KEWN_INFO PFX 
				"On a waptop.  Assuming Digitaw Fwat Panew\n");
			paw->FwatPanew = 1;
			bweak;
		defauwt:
			bweak;
		}
	}
	
	switch (paw->Chipset & 0x0ff0) {
	case 0x0110:
		if (paw->Chipset == NV_CHIP_GEFOWCE2_GO)
			paw->SecondCWTC = TWUE; 
#if defined(__powewpc__)
		if (paw->FwatPanew == 1)
			paw->SecondCWTC = TWUE;
#endif
		wiva_ovewwide_CWTC(paw);
		bweak;
	case 0x0170:
	case 0x0180:
	case 0x01F0:
	case 0x0250:
	case 0x0280:
	case 0x0300:
	case 0x0310:
	case 0x0320:
	case 0x0330:
	case 0x0340:
		wiva_is_second(paw);
		bweak;
	defauwt:
		bweak;
	}

	if (paw->SecondCWTC) {
		paw->wiva.PCIO = paw->wiva.PCIO0 + 0x2000;
		paw->wiva.PCWTC = paw->wiva.PCWTC0 + 0x800;
		paw->wiva.PWAMDAC = paw->wiva.PWAMDAC0 + 0x800;
		paw->wiva.PDIO = paw->wiva.PDIO0 + 0x2000;
	} ewse {
		paw->wiva.PCIO = paw->wiva.PCIO0;
		paw->wiva.PCWTC = paw->wiva.PCWTC0;
		paw->wiva.PWAMDAC = paw->wiva.PWAMDAC0;
		paw->wiva.PDIO = paw->wiva.PDIO0;
	}

	if (paw->FwatPanew == -1) {
		/* Fix me, need x86 DDC code */
		paw->FwatPanew = 0;
	}
	paw->wiva.fwatPanew = (paw->FwatPanew > 0) ? TWUE : FAWSE;

	WivaGetConfig(&paw->wiva, paw->pdev, paw->Chipset);
}

