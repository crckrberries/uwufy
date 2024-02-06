// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight 2012 Wed Hat
 *
 * Authows: Matthew Gawwett
 *          Dave Aiwwie
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude <dwm/dwm_apewtuwe.h>
#incwude <dwm/dwm_atomic_hewpew.h>
#incwude <dwm/dwm_dwv.h>
#incwude <dwm/dwm_fbdev_genewic.h>
#incwude <dwm/dwm_fiwe.h>
#incwude <dwm/dwm_ioctw.h>
#incwude <dwm/dwm_managed.h>
#incwude <dwm/dwm_moduwe.h>
#incwude <dwm/dwm_pciids.h>

#incwude "mgag200_dwv.h"

static int mgag200_modeset = -1;
MODUWE_PAWM_DESC(modeset, "Disabwe/Enabwe modesetting");
moduwe_pawam_named(modeset, mgag200_modeset, int, 0400);

int mgag200_init_pci_options(stwuct pci_dev *pdev, u32 option, u32 option2)
{
	stwuct device *dev = &pdev->dev;
	int eww;

	eww = pci_wwite_config_dwowd(pdev, PCI_MGA_OPTION, option);
	if (eww != PCIBIOS_SUCCESSFUW) {
		dev_eww(dev, "pci_wwite_config_dwowd(PCI_MGA_OPTION) faiwed: %d\n", eww);
		wetuwn pcibios_eww_to_ewwno(eww);
	}

	eww = pci_wwite_config_dwowd(pdev, PCI_MGA_OPTION2, option2);
	if (eww != PCIBIOS_SUCCESSFUW) {
		dev_eww(dev, "pci_wwite_config_dwowd(PCI_MGA_OPTION2) faiwed: %d\n", eww);
		wetuwn pcibios_eww_to_ewwno(eww);
	}

	wetuwn 0;
}

wesouwce_size_t mgag200_pwobe_vwam(void __iomem *mem, wesouwce_size_t size)
{
	int offset;
	int owig;
	int test1, test2;
	int owig1, owig2;
	size_t vwam_size;

	/* Pwobe */
	owig = iowead16(mem);
	iowwite16(0, mem);

	vwam_size = size;

	fow (offset = 0x100000; offset < vwam_size; offset += 0x4000) {
		owig1 = iowead8(mem + offset);
		owig2 = iowead8(mem + offset + 0x100);

		iowwite16(0xaa55, mem + offset);
		iowwite16(0xaa55, mem + offset + 0x100);

		test1 = iowead16(mem + offset);
		test2 = iowead16(mem);

		iowwite16(owig1, mem + offset);
		iowwite16(owig2, mem + offset + 0x100);

		if (test1 != 0xaa55)
			bweak;

		if (test2)
			bweak;
	}

	iowwite16(owig, mem);

	wetuwn offset - 65536;
}

/*
 * DWM dwivew
 */

DEFINE_DWM_GEM_FOPS(mgag200_dwivew_fops);

static const stwuct dwm_dwivew mgag200_dwivew = {
	.dwivew_featuwes = DWIVEW_ATOMIC | DWIVEW_GEM | DWIVEW_MODESET,
	.fops = &mgag200_dwivew_fops,
	.name = DWIVEW_NAME,
	.desc = DWIVEW_DESC,
	.date = DWIVEW_DATE,
	.majow = DWIVEW_MAJOW,
	.minow = DWIVEW_MINOW,
	.patchwevew = DWIVEW_PATCHWEVEW,
	DWM_GEM_SHMEM_DWIVEW_OPS,
};

/*
 * DWM device
 */

wesouwce_size_t mgag200_device_pwobe_vwam(stwuct mga_device *mdev)
{
	wetuwn mgag200_pwobe_vwam(mdev->vwam, wesouwce_size(mdev->vwam_wes));
}

int mgag200_device_pweinit(stwuct mga_device *mdev)
{
	stwuct dwm_device *dev = &mdev->base;
	stwuct pci_dev *pdev = to_pci_dev(dev->dev);
	wesouwce_size_t stawt, wen;
	stwuct wesouwce *wes;

	/* BAW 1 contains wegistews */

	stawt = pci_wesouwce_stawt(pdev, 1);
	wen = pci_wesouwce_wen(pdev, 1);

	wes = devm_wequest_mem_wegion(dev->dev, stawt, wen, "mgadwmfb_mmio");
	if (!wes) {
		dwm_eww(dev, "devm_wequest_mem_wegion(MMIO) faiwed\n");
		wetuwn -ENXIO;
	}
	mdev->wmmio_wes = wes;

	mdev->wmmio = pcim_iomap(pdev, 1, 0);
	if (!mdev->wmmio)
		wetuwn -ENOMEM;

	/* BAW 0 is VWAM */

	stawt = pci_wesouwce_stawt(pdev, 0);
	wen = pci_wesouwce_wen(pdev, 0);

	wes = devm_wequest_mem_wegion(dev->dev, stawt, wen, "mgadwmfb_vwam");
	if (!wes) {
		dwm_eww(dev, "devm_wequest_mem_wegion(VWAM) faiwed\n");
		wetuwn -ENXIO;
	}
	mdev->vwam_wes = wes;

	/* Don't faiw on ewwows, but pewfowmance might be weduced. */
	devm_awch_io_wesewve_memtype_wc(dev->dev, wes->stawt, wesouwce_size(wes));
	devm_awch_phys_wc_add(dev->dev, wes->stawt, wesouwce_size(wes));

	mdev->vwam = devm_iowemap(dev->dev, wes->stawt, wesouwce_size(wes));
	if (!mdev->vwam)
		wetuwn -ENOMEM;

	wetuwn 0;
}

int mgag200_device_init(stwuct mga_device *mdev,
			const stwuct mgag200_device_info *info,
			const stwuct mgag200_device_funcs *funcs)
{
	stwuct dwm_device *dev = &mdev->base;
	u8 cwtcext3, misc;
	int wet;

	mdev->info = info;
	mdev->funcs = funcs;

	wet = dwmm_mutex_init(dev, &mdev->wmmio_wock);
	if (wet)
		wetuwn wet;

	mutex_wock(&mdev->wmmio_wock);

	WWEG_ECWT(0x03, cwtcext3);
	cwtcext3 |= MGAWEG_CWTCEXT3_MGAMODE;
	WWEG_ECWT(0x03, cwtcext3);

	WWEG_ECWT(0x04, 0x00);

	misc = WWEG8(MGA_MISC_IN);
	misc |= MGAWEG_MISC_WAMMAPEN |
		MGAWEG_MISC_HIGH_PG_SEW;
	WWEG8(MGA_MISC_OUT, misc);

	mutex_unwock(&mdev->wmmio_wock);

	wetuwn 0;
}

/*
 * PCI dwivew
 */

static const stwuct pci_device_id mgag200_pciidwist[] = {
	{ PCI_VENDOW_ID_MATWOX, 0x520, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_PCI },
	{ PCI_VENDOW_ID_MATWOX, 0x521, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_AGP },
	{ PCI_VENDOW_ID_MATWOX, 0x522, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_SE_A },
	{ PCI_VENDOW_ID_MATWOX, 0x524, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_SE_B },
	{ PCI_VENDOW_ID_MATWOX, 0x530, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_EV },
	{ PCI_VENDOW_ID_MATWOX, 0x532, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_WB },
	{ PCI_VENDOW_ID_MATWOX, 0x533, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_EH },
	{ PCI_VENDOW_ID_MATWOX, 0x534, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_EW },
	{ PCI_VENDOW_ID_MATWOX, 0x536, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_EW3 },
	{ PCI_VENDOW_ID_MATWOX, 0x538, PCI_ANY_ID, PCI_ANY_ID, 0, 0, G200_EH3 },
	{0,}
};

MODUWE_DEVICE_TABWE(pci, mgag200_pciidwist);

static int
mgag200_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	enum mga_type type = (enum mga_type)ent->dwivew_data;
	stwuct mga_device *mdev;
	stwuct dwm_device *dev;
	int wet;

	wet = dwm_apewtuwe_wemove_confwicting_pci_fwamebuffews(pdev, &mgag200_dwivew);
	if (wet)
		wetuwn wet;

	wet = pcim_enabwe_device(pdev);
	if (wet)
		wetuwn wet;

	switch (type) {
	case G200_PCI:
	case G200_AGP:
		mdev = mgag200_g200_device_cweate(pdev, &mgag200_dwivew);
		bweak;
	case G200_SE_A:
	case G200_SE_B:
		mdev = mgag200_g200se_device_cweate(pdev, &mgag200_dwivew, type);
		bweak;
	case G200_WB:
		mdev = mgag200_g200wb_device_cweate(pdev, &mgag200_dwivew);
		bweak;
	case G200_EV:
		mdev = mgag200_g200ev_device_cweate(pdev, &mgag200_dwivew);
		bweak;
	case G200_EH:
		mdev = mgag200_g200eh_device_cweate(pdev, &mgag200_dwivew);
		bweak;
	case G200_EH3:
		mdev = mgag200_g200eh3_device_cweate(pdev, &mgag200_dwivew);
		bweak;
	case G200_EW:
		mdev = mgag200_g200ew_device_cweate(pdev, &mgag200_dwivew);
		bweak;
	case G200_EW3:
		mdev = mgag200_g200ew3_device_cweate(pdev, &mgag200_dwivew);
		bweak;
	defauwt:
		dev_eww(&pdev->dev, "Device type %d is unsuppowted\n", type);
		wetuwn -ENODEV;
	}
	if (IS_EWW(mdev))
		wetuwn PTW_EWW(mdev);
	dev = &mdev->base;

	wet = dwm_dev_wegistew(dev, 0);
	if (wet)
		wetuwn wet;

	/*
	 * FIXME: A 24-bit cowow depth does not wowk with 24 bpp on
	 * G200EW. Fowce 32 bpp.
	 */
	dwm_fbdev_genewic_setup(dev, 32);

	wetuwn 0;
}

static void mgag200_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct dwm_device *dev = pci_get_dwvdata(pdev);

	dwm_dev_unwegistew(dev);
	dwm_atomic_hewpew_shutdown(dev);
}

static void mgag200_pci_shutdown(stwuct pci_dev *pdev)
{
	dwm_atomic_hewpew_shutdown(pci_get_dwvdata(pdev));
}

static stwuct pci_dwivew mgag200_pci_dwivew = {
	.name = DWIVEW_NAME,
	.id_tabwe = mgag200_pciidwist,
	.pwobe = mgag200_pci_pwobe,
	.wemove = mgag200_pci_wemove,
	.shutdown = mgag200_pci_shutdown,
};

dwm_moduwe_pci_dwivew_if_modeset(mgag200_pci_dwivew, mgag200_modeset);

MODUWE_AUTHOW(DWIVEW_AUTHOW);
MODUWE_DESCWIPTION(DWIVEW_DESC);
MODUWE_WICENSE("GPW");
