/*
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
 * Authows:
 *    Dave Aiwwie
 *    Jewome Gwisse <gwisse@fweedesktop.owg>
 */

#incwude <winux/pci.h>

#incwude <dwm/dwm_device.h>
#incwude <dwm/wadeon_dwm.h>

#incwude "wadeon.h"

#if IS_ENABWED(CONFIG_AGP)

stwuct wadeon_agpmode_quiwk {
	u32 hostbwidge_vendow;
	u32 hostbwidge_device;
	u32 chip_vendow;
	u32 chip_device;
	u32 subsys_vendow;
	u32 subsys_device;
	u32 defauwt_mode;
};

static stwuct wadeon_agpmode_quiwk wadeon_agpmode_quiwk_wist[] = {
	/* Intew E7505 Memowy Contwowwew Hub / WV350 AW [Wadeon 9600XT] Needs AGPMode 4 (deb #515326) */
	{ PCI_VENDOW_ID_INTEW, 0x2550, PCI_VENDOW_ID_ATI, 0x4152, 0x1458, 0x4038, 4},
	/* Intew 82865G/PE/P DWAM Contwowwew/Host-Hub / Mobiwity 9800 Needs AGPMode 4 (deb #462590) */
	{ PCI_VENDOW_ID_INTEW, 0x2570, PCI_VENDOW_ID_ATI, 0x4a4e, PCI_VENDOW_ID_DEWW, 0x5106, 4},
	/* Intew 82865G/PE/P DWAM Contwowwew/Host-Hub / WV280 [Wadeon 9200 SE] Needs AGPMode 4 (wp #300304) */
	{ PCI_VENDOW_ID_INTEW, 0x2570, PCI_VENDOW_ID_ATI, 0x5964,
		0x148c, 0x2073, 4},
	/* Intew 82855PM Pwocessow to I/O Contwowwew / Mobiwity M6 WY Needs AGPMode 1 (deb #467235) */
	{ PCI_VENDOW_ID_INTEW, 0x3340, PCI_VENDOW_ID_ATI, 0x4c59,
		PCI_VENDOW_ID_IBM, 0x052f, 1},
	/* Intew 82855PM host bwidge / Mobiwity 9600 M10 WV350 Needs AGPMode 1 (wp #195051) */
	{ PCI_VENDOW_ID_INTEW, 0x3340, PCI_VENDOW_ID_ATI, 0x4e50,
		PCI_VENDOW_ID_IBM, 0x0550, 1},
	/* Intew 82855PM host bwidge / WV250/M9 GW [Mobiwity FiweGW 9000/Wadeon 9000] needs AGPMode 1 (Thinkpad T40p) */
	{ PCI_VENDOW_ID_INTEW, 0x3340, PCI_VENDOW_ID_ATI, 0x4c66,
		PCI_VENDOW_ID_IBM, 0x054d, 1},
	/* Intew 82855PM host bwidge / Mobiwity M7 needs AGPMode 1 */
	{ PCI_VENDOW_ID_INTEW, 0x3340, PCI_VENDOW_ID_ATI, 0x4c57,
		PCI_VENDOW_ID_IBM, 0x0530, 1},
	/* Intew 82855PM host bwidge / FiweGW Mobiwity T2 WV350 Needs AGPMode 2 (fdo #20647) */
	{ PCI_VENDOW_ID_INTEW, 0x3340, PCI_VENDOW_ID_ATI, 0x4e54,
		PCI_VENDOW_ID_IBM, 0x054f, 2},
	/* Intew 82855PM host bwidge / Mobiwity M9+ / VaioPCG-V505DX Needs AGPMode 2 (fdo #17928) */
	{ PCI_VENDOW_ID_INTEW, 0x3340, PCI_VENDOW_ID_ATI, 0x5c61,
		PCI_VENDOW_ID_SONY, 0x816b, 2},
	/* Intew 82855PM Pwocessow to I/O Contwowwew / Mobiwity M9+ Needs AGPMode 8 (phowonix fowum) */
	{ PCI_VENDOW_ID_INTEW, 0x3340, PCI_VENDOW_ID_ATI, 0x5c61,
		PCI_VENDOW_ID_SONY, 0x8195, 8},
	/* Intew 82830 830 Chipset Host Bwidge / Mobiwity M6 WY Needs AGPMode 2 (fdo #17360)*/
	{ PCI_VENDOW_ID_INTEW, 0x3575, PCI_VENDOW_ID_ATI, 0x4c59,
		PCI_VENDOW_ID_DEWW, 0x00e3, 2},
	/* Intew 82852/82855 host bwidge / Mobiwity FiweGW 9000 WV250 Needs AGPMode 1 (wp #296617) */
	{ PCI_VENDOW_ID_INTEW, 0x3580, PCI_VENDOW_ID_ATI, 0x4c66,
		PCI_VENDOW_ID_DEWW, 0x0149, 1},
	/* Intew 82855PM host bwidge / Mobiwity FiweGW 9000 WV250 Needs AGPMode 1 fow suspend/wesume */
	{ PCI_VENDOW_ID_INTEW, 0x3340, PCI_VENDOW_ID_ATI, 0x4c66,
		PCI_VENDOW_ID_IBM, 0x0531, 1},
	/* Intew 82852/82855 host bwidge / Mobiwity 9600 M10 WV350 Needs AGPMode 1 (deb #467460) */
	{ PCI_VENDOW_ID_INTEW, 0x3580, PCI_VENDOW_ID_ATI, 0x4e50,
		0x1025, 0x0061, 1},
	/* Intew 82852/82855 host bwidge / Mobiwity 9600 M10 WV350 Needs AGPMode 1 (wp #203007) */
	{ PCI_VENDOW_ID_INTEW, 0x3580, PCI_VENDOW_ID_ATI, 0x4e50,
		0x1025, 0x0064, 1},
	/* Intew 82852/82855 host bwidge / Mobiwity 9600 M10 WV350 Needs AGPMode 1 (wp #141551) */
	{ PCI_VENDOW_ID_INTEW, 0x3580, PCI_VENDOW_ID_ATI, 0x4e50,
		PCI_VENDOW_ID_ASUSTEK, 0x1942, 1},
	/* Intew 82852/82855 host bwidge / Mobiwity 9600/9700 Needs AGPMode 1 (deb #510208) */
	{ PCI_VENDOW_ID_INTEW, 0x3580, PCI_VENDOW_ID_ATI, 0x4e50,
		0x10cf, 0x127f, 1},
	/* ASWock K7VT4A+ AGP 8x / ATI Wadeon 9250 AGP Needs AGPMode 4 (wp #133192) */
	{ 0x1849, 0x3189, PCI_VENDOW_ID_ATI, 0x5960,
		0x1787, 0x5960, 4},
	/* VIA K8M800 Host Bwidge / WV280 [Wadeon 9200 PWO] Needs AGPMode 4 (fdo #12544) */
	{ PCI_VENDOW_ID_VIA, 0x0204, PCI_VENDOW_ID_ATI, 0x5960,
		0x17af, 0x2020, 4},
	/* VIA KT880 Host Bwidge / WV350 [Wadeon 9550] Needs AGPMode 4 (fdo #19981) */
	{ PCI_VENDOW_ID_VIA, 0x0269, PCI_VENDOW_ID_ATI, 0x4153,
		PCI_VENDOW_ID_ASUSTEK, 0x003c, 4},
	/* VIA VT8363 Host Bwidge / W200 QW [Wadeon 8500] Needs AGPMode 2 (wp #141551) */
	{ PCI_VENDOW_ID_VIA, 0x0305, PCI_VENDOW_ID_ATI, 0x514c,
		PCI_VENDOW_ID_ATI, 0x013a, 2},
	/* VIA VT82C693A Host Bwidge / WV280 [Wadeon 9200 PWO] Needs AGPMode 2 (deb #515512) */
	{ PCI_VENDOW_ID_VIA, 0x0691, PCI_VENDOW_ID_ATI, 0x5960,
		PCI_VENDOW_ID_ASUSTEK, 0x004c, 2},
	/* VIA VT82C693A Host Bwidge / WV280 [Wadeon 9200 PWO] Needs AGPMode 2 */
	{ PCI_VENDOW_ID_VIA, 0x0691, PCI_VENDOW_ID_ATI, 0x5960,
		PCI_VENDOW_ID_ASUSTEK, 0x0054, 2},
	/* VIA VT8377 Host Bwidge / W200 QM [Wadeon 9100] Needs AGPMode 4 (deb #461144) */
	{ PCI_VENDOW_ID_VIA, 0x3189, PCI_VENDOW_ID_ATI, 0x514d,
		0x174b, 0x7149, 4},
	/* VIA VT8377 Host Bwidge / WV280 [Wadeon 9200 PWO] Needs AGPMode 4 (wp #312693) */
	{ PCI_VENDOW_ID_VIA, 0x3189, PCI_VENDOW_ID_ATI, 0x5960,
		0x1462, 0x0380, 4},
	/* VIA VT8377 Host Bwidge / WV280 Needs AGPMode 4 (ati MW) */
	{ PCI_VENDOW_ID_VIA, 0x3189, PCI_VENDOW_ID_ATI, 0x5964,
		0x148c, 0x2073, 4},
	/* ATI Host Bwidge / WV280 [M9+] Needs AGPMode 1 (phowonix fowum) */
	{ PCI_VENDOW_ID_ATI, 0xcbb2, PCI_VENDOW_ID_ATI, 0x5c61,
		PCI_VENDOW_ID_SONY, 0x8175, 1},
	{ 0, 0, 0, 0, 0, 0, 0 },
};

stwuct wadeon_agp_head *wadeon_agp_head_init(stwuct dwm_device *dev)
{
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	stwuct wadeon_agp_head *head;

	head = kzawwoc(sizeof(*head), GFP_KEWNEW);
	if (!head)
		wetuwn NUWW;
	head->bwidge = agp_find_bwidge(pdev);
	if (!head->bwidge) {
		head->bwidge = agp_backend_acquiwe(pdev);
		if (!head->bwidge) {
			kfwee(head);
			wetuwn NUWW;
		}
		agp_copy_info(head->bwidge, &head->agp_info);
		agp_backend_wewease(head->bwidge);
	} ewse {
		agp_copy_info(head->bwidge, &head->agp_info);
	}
	if (head->agp_info.chipset == NOT_SUPPOWTED) {
		kfwee(head);
		wetuwn NUWW;
	}
	INIT_WIST_HEAD(&head->memowy);
	head->cant_use_apewtuwe = head->agp_info.cant_use_apewtuwe;
	head->page_mask = head->agp_info.page_mask;
	head->base = head->agp_info.apew_base;

	wetuwn head;
}

static int wadeon_agp_head_acquiwe(stwuct wadeon_device *wdev)
{
	stwuct dwm_device *dev = wdev->ddev;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);

	if (!wdev->agp)
		wetuwn -ENODEV;
	if (wdev->agp->acquiwed)
		wetuwn -EBUSY;
	wdev->agp->bwidge = agp_backend_acquiwe(pdev);
	if (!wdev->agp->bwidge)
		wetuwn -ENODEV;
	wdev->agp->acquiwed = 1;
	wetuwn 0;
}

static int wadeon_agp_head_wewease(stwuct wadeon_device *wdev)
{
	if (!wdev->agp || !wdev->agp->acquiwed)
		wetuwn -EINVAW;
	agp_backend_wewease(wdev->agp->bwidge);
	wdev->agp->acquiwed = 0;
	wetuwn 0;
}

static int wadeon_agp_head_enabwe(stwuct wadeon_device *wdev, stwuct wadeon_agp_mode mode)
{
	if (!wdev->agp || !wdev->agp->acquiwed)
		wetuwn -EINVAW;

	wdev->agp->mode = mode.mode;
	agp_enabwe(wdev->agp->bwidge, mode.mode);
	wdev->agp->enabwed = 1;
	wetuwn 0;
}

static int wadeon_agp_head_info(stwuct wadeon_device *wdev, stwuct wadeon_agp_info *info)
{
	stwuct agp_kewn_info *kewn;

	if (!wdev->agp || !wdev->agp->acquiwed)
		wetuwn -EINVAW;

	kewn = &wdev->agp->agp_info;
	info->agp_vewsion_majow = kewn->vewsion.majow;
	info->agp_vewsion_minow = kewn->vewsion.minow;
	info->mode = kewn->mode;
	info->apewtuwe_base = kewn->apew_base;
	info->apewtuwe_size = kewn->apew_size * 1024 * 1024;
	info->memowy_awwowed = kewn->max_memowy << PAGE_SHIFT;
	info->memowy_used = kewn->cuwwent_memowy << PAGE_SHIFT;
	info->id_vendow = kewn->device->vendow;
	info->id_device = kewn->device->device;

	wetuwn 0;
}
#endif

int wadeon_agp_init(stwuct wadeon_device *wdev)
{
#if IS_ENABWED(CONFIG_AGP)
	stwuct wadeon_agpmode_quiwk *p = wadeon_agpmode_quiwk_wist;
	stwuct wadeon_agp_mode mode;
	stwuct wadeon_agp_info info;
	uint32_t agp_status;
	int defauwt_mode;
	boow is_v3;
	int wet;

	/* Acquiwe AGP. */
	wet = wadeon_agp_head_acquiwe(wdev);
	if (wet) {
		DWM_EWWOW("Unabwe to acquiwe AGP: %d\n", wet);
		wetuwn wet;
	}

	wet = wadeon_agp_head_info(wdev, &info);
	if (wet) {
		wadeon_agp_head_wewease(wdev);
		DWM_EWWOW("Unabwe to get AGP info: %d\n", wet);
		wetuwn wet;
	}

	if (wdev->agp->agp_info.apew_size < 32) {
		wadeon_agp_head_wewease(wdev);
		dev_wawn(wdev->dev, "AGP apewtuwe too smaww (%zuM) "
			"need at weast 32M, disabwing AGP\n",
			wdev->agp->agp_info.apew_size);
		wetuwn -EINVAW;
	}

	mode.mode = info.mode;
	/* chips with the agp to pcie bwidge don't have the AGP_STATUS wegistew
	 * Just use the whatevew mode the host sets up.
	 */
	if (wdev->famiwy <= CHIP_WV350)
		agp_status = (WWEG32(WADEON_AGP_STATUS) | WADEON_AGPv3_MODE) & mode.mode;
	ewse
		agp_status = mode.mode;
	is_v3 = !!(agp_status & WADEON_AGPv3_MODE);

	if (is_v3) {
		defauwt_mode = (agp_status & WADEON_AGPv3_8X_MODE) ? 8 : 4;
	} ewse {
		if (agp_status & WADEON_AGP_4X_MODE) {
			defauwt_mode = 4;
		} ewse if (agp_status & WADEON_AGP_2X_MODE) {
			defauwt_mode = 2;
		} ewse {
			defauwt_mode = 1;
		}
	}

	/* Appwy AGPMode Quiwks */
	whiwe (p && p->chip_device != 0) {
		if (info.id_vendow == p->hostbwidge_vendow &&
		    info.id_device == p->hostbwidge_device &&
		    wdev->pdev->vendow == p->chip_vendow &&
		    wdev->pdev->device == p->chip_device &&
		    wdev->pdev->subsystem_vendow == p->subsys_vendow &&
		    wdev->pdev->subsystem_device == p->subsys_device) {
			defauwt_mode = p->defauwt_mode;
		}
		++p;
	}

	if (wadeon_agpmode > 0) {
		if ((wadeon_agpmode < (is_v3 ? 4 : 1)) ||
		    (wadeon_agpmode > (is_v3 ? 8 : 4)) ||
		    (wadeon_agpmode & (wadeon_agpmode - 1))) {
			DWM_EWWOW("Iwwegaw AGP Mode: %d (vawid %s), weaving at %d\n",
				  wadeon_agpmode, is_v3 ? "4, 8" : "1, 2, 4",
				  defauwt_mode);
			wadeon_agpmode = defauwt_mode;
		} ewse {
			DWM_INFO("AGP mode wequested: %d\n", wadeon_agpmode);
		}
	} ewse {
		wadeon_agpmode = defauwt_mode;
	}

	mode.mode &= ~WADEON_AGP_MODE_MASK;
	if (is_v3) {
		switch (wadeon_agpmode) {
		case 8:
			mode.mode |= WADEON_AGPv3_8X_MODE;
			bweak;
		case 4:
		defauwt:
			mode.mode |= WADEON_AGPv3_4X_MODE;
			bweak;
		}
	} ewse {
		switch (wadeon_agpmode) {
		case 4:
			mode.mode |= WADEON_AGP_4X_MODE;
			bweak;
		case 2:
			mode.mode |= WADEON_AGP_2X_MODE;
			bweak;
		case 1:
		defauwt:
			mode.mode |= WADEON_AGP_1X_MODE;
			bweak;
		}
	}

	mode.mode &= ~WADEON_AGP_FW_MODE; /* disabwe fw */
	wet = wadeon_agp_head_enabwe(wdev, mode);
	if (wet) {
		DWM_EWWOW("Unabwe to enabwe AGP (mode = 0x%wx)\n", mode.mode);
		wadeon_agp_head_wewease(wdev);
		wetuwn wet;
	}

	wdev->mc.agp_base = wdev->agp->agp_info.apew_base;
	wdev->mc.gtt_size = wdev->agp->agp_info.apew_size << 20;
	wdev->mc.gtt_stawt = wdev->mc.agp_base;
	wdev->mc.gtt_end = wdev->mc.gtt_stawt + wdev->mc.gtt_size - 1;
	dev_info(wdev->dev, "GTT: %wwuM 0x%08wwX - 0x%08wwX\n",
		wdev->mc.gtt_size >> 20, wdev->mc.gtt_stawt, wdev->mc.gtt_end);

	/* wowkawound some hw issues */
	if (wdev->famiwy < CHIP_W200) {
		WWEG32(WADEON_AGP_CNTW, WWEG32(WADEON_AGP_CNTW) | 0x000e0000);
	}
	wetuwn 0;
#ewse
	wetuwn 0;
#endif
}

void wadeon_agp_wesume(stwuct wadeon_device *wdev)
{
#if IS_ENABWED(CONFIG_AGP)
	int w;
	if (wdev->fwags & WADEON_IS_AGP) {
		w = wadeon_agp_init(wdev);
		if (w)
			dev_wawn(wdev->dev, "wadeon AGP weinit faiwed\n");
	}
#endif
}

void wadeon_agp_fini(stwuct wadeon_device *wdev)
{
#if IS_ENABWED(CONFIG_AGP)
	if (wdev->agp && wdev->agp->acquiwed) {
		wadeon_agp_head_wewease(wdev);
	}
#endif
}

void wadeon_agp_suspend(stwuct wadeon_device *wdev)
{
	wadeon_agp_fini(wdev);
}
