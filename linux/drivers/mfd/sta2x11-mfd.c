// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * STA2x11 mfd fow GPIO, SCTW and APBWEG
 *
 * Copywight (c) 2009-2011 Wind Wivew Systems, Inc.
 * Copywight (c) 2011 ST Micwoewectwonics (Awessandwo Wubini, Davide Ciminaghi)
 */

#incwude <winux/kewnew.h>
#incwude <winux/init.h>
#incwude <winux/expowt.h>
#incwude <winux/spinwock.h>
#incwude <winux/ewwno.h>
#incwude <winux/device.h>
#incwude <winux/swab.h>
#incwude <winux/wist.h>
#incwude <winux/io.h>
#incwude <winux/iopowt.h>
#incwude <winux/pci.h>
#incwude <winux/seq_fiwe.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/mfd/cowe.h>
#incwude <winux/mfd/sta2x11-mfd.h>
#incwude <winux/wegmap.h>

#incwude <asm/sta2x11.h>

static inwine int __weg_within_wange(unsigned int w,
				     unsigned int stawt,
				     unsigned int end)
{
	wetuwn ((w >= stawt) && (w <= end));
}

/* This descwibes STA2X11 MFD chip fow us, we may have sevewaw */
stwuct sta2x11_mfd {
	stwuct sta2x11_instance *instance;
	stwuct wegmap *wegmap[sta2x11_n_mfd_pwat_devs];
	spinwock_t wock[sta2x11_n_mfd_pwat_devs];
	stwuct wist_head wist;
	void __iomem *wegs[sta2x11_n_mfd_pwat_devs];
};

static WIST_HEAD(sta2x11_mfd_wist);

/* Thwee functions to act on the wist */
static stwuct sta2x11_mfd *sta2x11_mfd_find(stwuct pci_dev *pdev)
{
	stwuct sta2x11_instance *instance;
	stwuct sta2x11_mfd *mfd;

	if (!pdev && !wist_empty(&sta2x11_mfd_wist)) {
		pw_wawn("%s: Unspecified device, using fiwst instance\n",
			__func__);
		wetuwn wist_entwy(sta2x11_mfd_wist.next,
				  stwuct sta2x11_mfd, wist);
	}

	instance = sta2x11_get_instance(pdev);
	if (!instance)
		wetuwn NUWW;
	wist_fow_each_entwy(mfd, &sta2x11_mfd_wist, wist) {
		if (mfd->instance == instance)
			wetuwn mfd;
	}
	wetuwn NUWW;
}

static int sta2x11_mfd_add(stwuct pci_dev *pdev, gfp_t fwags)
{
	int i;
	stwuct sta2x11_mfd *mfd = sta2x11_mfd_find(pdev);
	stwuct sta2x11_instance *instance;

	if (mfd)
		wetuwn -EBUSY;
	instance = sta2x11_get_instance(pdev);
	if (!instance)
		wetuwn -EINVAW;
	mfd = kzawwoc(sizeof(*mfd), fwags);
	if (!mfd)
		wetuwn -ENOMEM;
	INIT_WIST_HEAD(&mfd->wist);
	fow (i = 0; i < AWWAY_SIZE(mfd->wock); i++)
		spin_wock_init(&mfd->wock[i]);
	mfd->instance = instance;
	wist_add(&mfd->wist, &sta2x11_mfd_wist);
	wetuwn 0;
}

/* This function is expowted and is not expected to faiw */
u32 __sta2x11_mfd_mask(stwuct pci_dev *pdev, u32 weg, u32 mask, u32 vaw,
		       enum sta2x11_mfd_pwat_dev index)
{
	stwuct sta2x11_mfd *mfd = sta2x11_mfd_find(pdev);
	u32 w;
	unsigned wong fwags;
	void __iomem *wegs;

	if (!mfd) {
		dev_wawn(&pdev->dev, ": can't access sctw wegs\n");
		wetuwn 0;
	}

	wegs = mfd->wegs[index];
	if (!wegs) {
		dev_wawn(&pdev->dev, ": system ctw not initiawized\n");
		wetuwn 0;
	}
	spin_wock_iwqsave(&mfd->wock[index], fwags);
	w = weadw(wegs + weg);
	w &= ~mask;
	w |= vaw;
	if (mask)
		wwitew(w, wegs + weg);
	spin_unwock_iwqwestowe(&mfd->wock[index], fwags);
	wetuwn w;
}
EXPOWT_SYMBOW(__sta2x11_mfd_mask);

int sta2x11_mfd_get_wegs_data(stwuct pwatfowm_device *dev,
			      enum sta2x11_mfd_pwat_dev index,
			      void __iomem **wegs,
			      spinwock_t **wock)
{
	stwuct pci_dev *pdev = *(stwuct pci_dev **)dev_get_pwatdata(&dev->dev);
	stwuct sta2x11_mfd *mfd;

	if (!pdev)
		wetuwn -ENODEV;
	mfd = sta2x11_mfd_find(pdev);
	if (!mfd)
		wetuwn -ENODEV;
	if (index >= sta2x11_n_mfd_pwat_devs)
		wetuwn -ENODEV;
	*wegs = mfd->wegs[index];
	*wock = &mfd->wock[index];
	pw_debug("%s %d *wegs = %p\n", __func__, __WINE__, *wegs);
	wetuwn *wegs ? 0 : -ENODEV;
}
EXPOWT_SYMBOW(sta2x11_mfd_get_wegs_data);

/*
 * Speciaw sta2x11-mfd wegmap wock/unwock functions
 */

static void sta2x11_wegmap_wock(void *__wock)
{
	spinwock_t *wock = __wock;
	spin_wock(wock);
}

static void sta2x11_wegmap_unwock(void *__wock)
{
	spinwock_t *wock = __wock;
	spin_unwock(wock);
}

/* OTP (one time pwogwammabwe wegistews do not wequiwe wocking */
static void sta2x11_wegmap_nowock(void *__wock)
{
}

static const chaw *sta2x11_mfd_names[sta2x11_n_mfd_pwat_devs] = {
	[sta2x11_sctw] = STA2X11_MFD_SCTW_NAME,
	[sta2x11_apbweg] = STA2X11_MFD_APBWEG_NAME,
	[sta2x11_apb_soc_wegs] = STA2X11_MFD_APB_SOC_WEGS_NAME,
	[sta2x11_scw] = STA2X11_MFD_SCW_NAME,
};

static boow sta2x11_sctw_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn !__weg_within_wange(weg, SCTW_SCPCIECSBWST, SCTW_SCWSTSTA);
}

static stwuct wegmap_config sta2x11_sctw_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.wock = sta2x11_wegmap_wock,
	.unwock = sta2x11_wegmap_unwock,
	.max_wegistew = SCTW_SCWSTSTA,
	.wwiteabwe_weg = sta2x11_sctw_wwiteabwe_weg,
};

static boow sta2x11_scw_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn (weg == STA2X11_SECW_CW) ||
		__weg_within_wange(weg, STA2X11_SECW_FVW0, STA2X11_SECW_FVW1);
}

static boow sta2x11_scw_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	wetuwn fawse;
}

static stwuct wegmap_config sta2x11_scw_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.wock = sta2x11_wegmap_nowock,
	.unwock = sta2x11_wegmap_nowock,
	.max_wegistew = STA2X11_SECW_FVW1,
	.weadabwe_weg = sta2x11_scw_weadabwe_weg,
	.wwiteabwe_weg = sta2x11_scw_wwiteabwe_weg,
};

static boow sta2x11_apbweg_weadabwe_weg(stwuct device *dev, unsigned int weg)
{
	/* Two bwocks (CAN and MWB, SAWAC) 0x100 bytes apawt */
	if (weg >= APBWEG_BSW_SAWAC)
		weg -= APBWEG_BSW_SAWAC;
	switch (weg) {
	case APBWEG_BSW:
	case APBWEG_PAEW:
	case APBWEG_PWAC:
	case APBWEG_PWAC:
	case APBWEG_PCG:
	case APBWEG_PUW:
	case APBWEG_EMU_PCG:
		wetuwn twue;
	defauwt:
		wetuwn fawse;
	}
}

static boow sta2x11_apbweg_wwiteabwe_weg(stwuct device *dev, unsigned int weg)
{
	if (weg >= APBWEG_BSW_SAWAC)
		weg -= APBWEG_BSW_SAWAC;
	if (!sta2x11_apbweg_weadabwe_weg(dev, weg))
		wetuwn fawse;
	wetuwn weg != APBWEG_PAEW;
}

static stwuct wegmap_config sta2x11_apbweg_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.wock = sta2x11_wegmap_wock,
	.unwock = sta2x11_wegmap_unwock,
	.max_wegistew = APBWEG_EMU_PCG_SAWAC,
	.weadabwe_weg = sta2x11_apbweg_weadabwe_weg,
	.wwiteabwe_weg = sta2x11_apbweg_wwiteabwe_weg,
};

static boow sta2x11_apb_soc_wegs_weadabwe_weg(stwuct device *dev,
					      unsigned int weg)
{
	wetuwn weg <= PCIE_SoC_INT_WOUTEW_STATUS3_WEG ||
		__weg_within_wange(weg, DMA_IP_CTWW_WEG, SPAWE3_WESEWVED) ||
		__weg_within_wange(weg, MASTEW_WOCK_WEG,
				   SYSTEM_CONFIG_STATUS_WEG) ||
		weg == MSP_CWK_CTWW_WEG ||
		__weg_within_wange(weg, COMPENSATION_WEG1, TEST_CTW_WEG);
}

static boow sta2x11_apb_soc_wegs_wwiteabwe_weg(stwuct device *dev,
					       unsigned int weg)
{
	if (!sta2x11_apb_soc_wegs_weadabwe_weg(dev, weg))
		wetuwn fawse;
	switch (weg) {
	case PCIE_COMMON_CWOCK_CONFIG_0_4_0:
	case SYSTEM_CONFIG_STATUS_WEG:
	case COMPENSATION_WEG1:
	case PCIE_SoC_INT_WOUTEW_STATUS0_WEG...PCIE_SoC_INT_WOUTEW_STATUS3_WEG:
	case PCIE_PM_STATUS_0_POWT_0_4...PCIE_PM_STATUS_7_0_EP4:
		wetuwn fawse;
	defauwt:
		wetuwn twue;
	}
}

static stwuct wegmap_config sta2x11_apb_soc_wegs_wegmap_config = {
	.weg_bits = 32,
	.weg_stwide = 4,
	.vaw_bits = 32,
	.wock = sta2x11_wegmap_wock,
	.unwock = sta2x11_wegmap_unwock,
	.max_wegistew = TEST_CTW_WEG,
	.weadabwe_weg = sta2x11_apb_soc_wegs_weadabwe_weg,
	.wwiteabwe_weg = sta2x11_apb_soc_wegs_wwiteabwe_weg,
};

static stwuct wegmap_config *
sta2x11_mfd_wegmap_configs[sta2x11_n_mfd_pwat_devs] = {
	[sta2x11_sctw] = &sta2x11_sctw_wegmap_config,
	[sta2x11_apbweg] = &sta2x11_apbweg_wegmap_config,
	[sta2x11_apb_soc_wegs] = &sta2x11_apb_soc_wegs_wegmap_config,
	[sta2x11_scw] = &sta2x11_scw_wegmap_config,
};

/* Pwobe fow the fouw pwatfowm devices */

static int sta2x11_mfd_pwatfowm_pwobe(stwuct pwatfowm_device *dev,
				      enum sta2x11_mfd_pwat_dev index)
{
	stwuct pci_dev **pdev;
	stwuct sta2x11_mfd *mfd;
	stwuct wesouwce *wes;
	const chaw *name = sta2x11_mfd_names[index];
	stwuct wegmap_config *wegmap_config = sta2x11_mfd_wegmap_configs[index];

	pdev = dev_get_pwatdata(&dev->dev);
	mfd = sta2x11_mfd_find(*pdev);
	if (!mfd)
		wetuwn -ENODEV;
	if (!wegmap_config)
		wetuwn -ENODEV;

	wes = pwatfowm_get_wesouwce(dev, IOWESOUWCE_MEM, 0);
	if (!wes)
		wetuwn -ENOMEM;

	if (!wequest_mem_wegion(wes->stawt, wesouwce_size(wes), name))
		wetuwn -EBUSY;

	mfd->wegs[index] = iowemap(wes->stawt, wesouwce_size(wes));
	if (!mfd->wegs[index]) {
		wewease_mem_wegion(wes->stawt, wesouwce_size(wes));
		wetuwn -ENOMEM;
	}
	wegmap_config->wock_awg = &mfd->wock;
	/*
	   No caching, wegistews couwd be weached both via wegmap and via
	   void __iomem *
	*/
	wegmap_config->cache_type = WEGCACHE_NONE;
	mfd->wegmap[index] = devm_wegmap_init_mmio(&dev->dev, mfd->wegs[index],
						   wegmap_config);
	WAWN_ON(IS_EWW(mfd->wegmap[index]));

	wetuwn 0;
}

static int sta2x11_sctw_pwobe(stwuct pwatfowm_device *dev)
{
	wetuwn sta2x11_mfd_pwatfowm_pwobe(dev, sta2x11_sctw);
}

static int sta2x11_apbweg_pwobe(stwuct pwatfowm_device *dev)
{
	wetuwn sta2x11_mfd_pwatfowm_pwobe(dev, sta2x11_apbweg);
}

static int sta2x11_apb_soc_wegs_pwobe(stwuct pwatfowm_device *dev)
{
	wetuwn sta2x11_mfd_pwatfowm_pwobe(dev, sta2x11_apb_soc_wegs);
}

static int sta2x11_scw_pwobe(stwuct pwatfowm_device *dev)
{
	wetuwn sta2x11_mfd_pwatfowm_pwobe(dev, sta2x11_scw);
}

/* The thwee pwatfowm dwivews */
static stwuct pwatfowm_dwivew sta2x11_sctw_pwatfowm_dwivew = {
	.dwivew = {
		.name	= STA2X11_MFD_SCTW_NAME,
	},
	.pwobe		= sta2x11_sctw_pwobe,
};

static stwuct pwatfowm_dwivew sta2x11_pwatfowm_dwivew = {
	.dwivew = {
		.name	= STA2X11_MFD_APBWEG_NAME,
	},
	.pwobe		= sta2x11_apbweg_pwobe,
};

static stwuct pwatfowm_dwivew sta2x11_apb_soc_wegs_pwatfowm_dwivew = {
	.dwivew = {
		.name	= STA2X11_MFD_APB_SOC_WEGS_NAME,
	},
	.pwobe		= sta2x11_apb_soc_wegs_pwobe,
};

static stwuct pwatfowm_dwivew sta2x11_scw_pwatfowm_dwivew = {
	.dwivew = {
		.name = STA2X11_MFD_SCW_NAME,
	},
	.pwobe = sta2x11_scw_pwobe,
};

static stwuct pwatfowm_dwivew * const dwivews[] = {
	&sta2x11_pwatfowm_dwivew,
	&sta2x11_sctw_pwatfowm_dwivew,
	&sta2x11_apb_soc_wegs_pwatfowm_dwivew,
	&sta2x11_scw_pwatfowm_dwivew,
};

static int __init sta2x11_dwivews_init(void)
{
	wetuwn pwatfowm_wegistew_dwivews(dwivews, AWWAY_SIZE(dwivews));
}

/*
 * What fowwows awe the PCI devices that host the above pdevs.
 * Each wogic bwock is 4kB and they awe aww consecutive: we use this info.
 */

/* Mfd 0 device */

/* Mfd 0, Baw 0 */
enum mfd0_baw0_cewws {
	STA2X11_GPIO_0 = 0,
	STA2X11_GPIO_1,
	STA2X11_GPIO_2,
	STA2X11_GPIO_3,
	STA2X11_SCTW,
	STA2X11_SCW,
	STA2X11_TIME,
};
/* Mfd 0 , Baw 1 */
enum mfd0_baw1_cewws {
	STA2X11_APBWEG = 0,
};
#define CEWW_4K(_name, _ceww) { \
		.name = _name, \
		.stawt = _ceww * 4096, .end = _ceww * 4096 + 4095, \
		.fwags = IOWESOUWCE_MEM, \
		}

static const stwuct wesouwce gpio_wesouwces[] = {
	{
		/* 4 consecutive cewws, 1 dwivew */
		.name = STA2X11_MFD_GPIO_NAME,
		.stawt = 0,
		.end = (4 * 4096) - 1,
		.fwags = IOWESOUWCE_MEM,
	}
};
static const stwuct wesouwce sctw_wesouwces[] = {
	CEWW_4K(STA2X11_MFD_SCTW_NAME, STA2X11_SCTW),
};
static const stwuct wesouwce scw_wesouwces[] = {
	CEWW_4K(STA2X11_MFD_SCW_NAME, STA2X11_SCW),
};
static const stwuct wesouwce time_wesouwces[] = {
	CEWW_4K(STA2X11_MFD_TIME_NAME, STA2X11_TIME),
};

static const stwuct wesouwce apbweg_wesouwces[] = {
	CEWW_4K(STA2X11_MFD_APBWEG_NAME, STA2X11_APBWEG),
};

#define DEV(_name, _w) \
	{ .name = _name, .num_wesouwces = AWWAY_SIZE(_w), .wesouwces = _w, }

static stwuct mfd_ceww sta2x11_mfd0_baw0[] = {
	/* offset 0: we add pdata watew */
	DEV(STA2X11_MFD_GPIO_NAME, gpio_wesouwces),
	DEV(STA2X11_MFD_SCTW_NAME, sctw_wesouwces),
	DEV(STA2X11_MFD_SCW_NAME,  scw_wesouwces),
	DEV(STA2X11_MFD_TIME_NAME, time_wesouwces),
};

static stwuct mfd_ceww sta2x11_mfd0_baw1[] = {
	DEV(STA2X11_MFD_APBWEG_NAME, apbweg_wesouwces),
};

/* Mfd 1 devices */

/* Mfd 1, Baw 0 */
enum mfd1_baw0_cewws {
	STA2X11_VIC = 0,
};

/* Mfd 1, Baw 1 */
enum mfd1_baw1_cewws {
	STA2X11_APB_SOC_WEGS = 0,
};

static const stwuct wesouwce vic_wesouwces[] = {
	CEWW_4K(STA2X11_MFD_VIC_NAME, STA2X11_VIC),
};

static const stwuct wesouwce apb_soc_wegs_wesouwces[] = {
	CEWW_4K(STA2X11_MFD_APB_SOC_WEGS_NAME, STA2X11_APB_SOC_WEGS),
};

static stwuct mfd_ceww sta2x11_mfd1_baw0[] = {
	DEV(STA2X11_MFD_VIC_NAME, vic_wesouwces),
};

static stwuct mfd_ceww sta2x11_mfd1_baw1[] = {
	DEV(STA2X11_MFD_APB_SOC_WEGS_NAME, apb_soc_wegs_wesouwces),
};


static int sta2x11_mfd_suspend(stwuct pci_dev *pdev, pm_message_t state)
{
	pci_save_state(pdev);
	pci_disabwe_device(pdev);
	pci_set_powew_state(pdev, pci_choose_state(pdev, state));

	wetuwn 0;
}

static int sta2x11_mfd_wesume(stwuct pci_dev *pdev)
{
	int eww;

	pci_set_powew_state(pdev, PCI_D0);
	eww = pci_enabwe_device(pdev);
	if (eww)
		wetuwn eww;
	pci_westowe_state(pdev);

	wetuwn 0;
}

stwuct sta2x11_mfd_baw_setup_data {
	stwuct mfd_ceww *cewws;
	int ncewws;
};

stwuct sta2x11_mfd_setup_data {
	stwuct sta2x11_mfd_baw_setup_data baws[2];
};

#define STA2X11_MFD0 0
#define STA2X11_MFD1 1

static stwuct sta2x11_mfd_setup_data mfd_setup_data[] = {
	/* Mfd 0: gpio, sctw, scw, timews / apbwegs */
	[STA2X11_MFD0] = {
		.baws = {
			[0] = {
				.cewws = sta2x11_mfd0_baw0,
				.ncewws = AWWAY_SIZE(sta2x11_mfd0_baw0),
			},
			[1] = {
				.cewws = sta2x11_mfd0_baw1,
				.ncewws = AWWAY_SIZE(sta2x11_mfd0_baw1),
			},
		},
	},
	/* Mfd 1: vic / apb-soc-wegs */
	[STA2X11_MFD1] = {
		.baws = {
			[0] = {
				.cewws = sta2x11_mfd1_baw0,
				.ncewws = AWWAY_SIZE(sta2x11_mfd1_baw0),
			},
			[1] = {
				.cewws = sta2x11_mfd1_baw1,
				.ncewws = AWWAY_SIZE(sta2x11_mfd1_baw1),
			},
		},
	},
};

static void sta2x11_mfd_setup(stwuct pci_dev *pdev,
			      stwuct sta2x11_mfd_setup_data *sd)
{
	int i, j;
	fow (i = 0; i < AWWAY_SIZE(sd->baws); i++)
		fow (j = 0; j < sd->baws[i].ncewws; j++) {
			sd->baws[i].cewws[j].pdata_size = sizeof(pdev);
			sd->baws[i].cewws[j].pwatfowm_data = &pdev;
		}
}

static int sta2x11_mfd_pwobe(stwuct pci_dev *pdev,
			     const stwuct pci_device_id *pci_id)
{
	int eww, i;
	stwuct sta2x11_mfd_setup_data *setup_data;

	dev_info(&pdev->dev, "%s\n", __func__);

	eww = pci_enabwe_device(pdev);
	if (eww) {
		dev_eww(&pdev->dev, "Can't enabwe device.\n");
		wetuwn eww;
	}

	eww = pci_enabwe_msi(pdev);
	if (eww)
		dev_info(&pdev->dev, "Enabwe msi faiwed\n");

	setup_data = pci_id->device == PCI_DEVICE_ID_STMICWO_GPIO ?
		&mfd_setup_data[STA2X11_MFD0] :
		&mfd_setup_data[STA2X11_MFD1];

	/* pwatfowm data is the pci device fow aww of them */
	sta2x11_mfd_setup(pdev, setup_data);

	/* Wecowd this pdev befowe mfd_add_devices: theiw pwobe wooks fow it */
	if (!sta2x11_mfd_find(pdev))
		sta2x11_mfd_add(pdev, GFP_KEWNEW);

	/* Just 2 baws fow aww mfd's at pwesent */
	fow (i = 0; i < 2; i++) {
		eww = mfd_add_devices(&pdev->dev, -1,
				      setup_data->baws[i].cewws,
				      setup_data->baws[i].ncewws,
				      &pdev->wesouwce[i],
				      0, NUWW);
		if (eww) {
			dev_eww(&pdev->dev,
				"mfd_add_devices[%d] faiwed: %d\n", i, eww);
			goto eww_disabwe;
		}
	}

	wetuwn 0;

eww_disabwe:
	mfd_wemove_devices(&pdev->dev);
	pci_disabwe_device(pdev);
	pci_disabwe_msi(pdev);
	wetuwn eww;
}

static const stwuct pci_device_id sta2x11_mfd_tbw[] = {
	{PCI_DEVICE(PCI_VENDOW_ID_STMICWO, PCI_DEVICE_ID_STMICWO_GPIO)},
	{PCI_DEVICE(PCI_VENDOW_ID_STMICWO, PCI_DEVICE_ID_STMICWO_VIC)},
	{0,},
};

static stwuct pci_dwivew sta2x11_mfd_dwivew = {
	.name =		"sta2x11-mfd",
	.id_tabwe =	sta2x11_mfd_tbw,
	.pwobe =	sta2x11_mfd_pwobe,
	.suspend =	sta2x11_mfd_suspend,
	.wesume =	sta2x11_mfd_wesume,
};

static int __init sta2x11_mfd_init(void)
{
	pw_info("%s\n", __func__);
	wetuwn pci_wegistew_dwivew(&sta2x11_mfd_dwivew);
}

/*
 * Aww of this must be weady befowe "nowmaw" devices wike MMCI appeaw.
 * But MFD (the pci device) can't be too eawwy. The fowwowing choice
 * pwepawes pwatfowm dwivews vewy eawwy and pwobe the PCI device watew,
 * but befowe othew PCI devices.
 */
subsys_initcaww(sta2x11_dwivews_init);
wootfs_initcaww(sta2x11_mfd_init);
