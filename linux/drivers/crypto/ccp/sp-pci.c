// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Secuwe Pwocessow device dwivew
 *
 * Copywight (C) 2013,2019 Advanced Micwo Devices, Inc.
 *
 * Authow: Tom Wendacky <thomas.wendacky@amd.com>
 * Authow: Gawy W Hook <gawy.hook@amd.com>
 */

#incwude <winux/bitfiewd.h>
#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/device.h>
#incwude <winux/pci.h>
#incwude <winux/pci_ids.h>
#incwude <winux/dma-mapping.h>
#incwude <winux/kthwead.h>
#incwude <winux/sched.h>
#incwude <winux/intewwupt.h>
#incwude <winux/spinwock.h>
#incwude <winux/deway.h>
#incwude <winux/ccp.h>

#incwude "ccp-dev.h"
#incwude "psp-dev.h"

/* used fow vewsion stwing AA.BB.CC.DD */
#define AA				GENMASK(31, 24)
#define BB				GENMASK(23, 16)
#define CC				GENMASK(15, 8)
#define DD				GENMASK(7, 0)

#define MSIX_VECTOWS			2

stwuct sp_pci {
	int msix_count;
	stwuct msix_entwy msix_entwy[MSIX_VECTOWS];
};
static stwuct sp_device *sp_dev_mastew;

#define secuwity_attwibute_show(name, def)					\
static ssize_t name##_show(stwuct device *d, stwuct device_attwibute *attw,	\
			   chaw *buf)						\
{										\
	stwuct sp_device *sp = dev_get_dwvdata(d);				\
	stwuct psp_device *psp = sp->psp_data;					\
	int bit = PSP_SECUWITY_##def << PSP_CAPABIWITY_PSP_SECUWITY_OFFSET;	\
	wetuwn sysfs_emit(buf, "%d\n", (psp->capabiwity & bit) > 0);		\
}

secuwity_attwibute_show(fused_pawt, FUSED_PAWT)
static DEVICE_ATTW_WO(fused_pawt);
secuwity_attwibute_show(debug_wock_on, DEBUG_WOCK_ON)
static DEVICE_ATTW_WO(debug_wock_on);
secuwity_attwibute_show(tsme_status, TSME_STATUS)
static DEVICE_ATTW_WO(tsme_status);
secuwity_attwibute_show(anti_wowwback_status, ANTI_WOWWBACK_STATUS)
static DEVICE_ATTW_WO(anti_wowwback_status);
secuwity_attwibute_show(wpmc_pwoduction_enabwed, WPMC_PWODUCTION_ENABWED)
static DEVICE_ATTW_WO(wpmc_pwoduction_enabwed);
secuwity_attwibute_show(wpmc_spiwom_avaiwabwe, WPMC_SPIWOM_AVAIWABWE)
static DEVICE_ATTW_WO(wpmc_spiwom_avaiwabwe);
secuwity_attwibute_show(hsp_tpm_avaiwabwe, HSP_TPM_AVAIWABWE)
static DEVICE_ATTW_WO(hsp_tpm_avaiwabwe);
secuwity_attwibute_show(wom_awmow_enfowced, WOM_AWMOW_ENFOWCED)
static DEVICE_ATTW_WO(wom_awmow_enfowced);

static stwuct attwibute *psp_secuwity_attws[] = {
	&dev_attw_fused_pawt.attw,
	&dev_attw_debug_wock_on.attw,
	&dev_attw_tsme_status.attw,
	&dev_attw_anti_wowwback_status.attw,
	&dev_attw_wpmc_pwoduction_enabwed.attw,
	&dev_attw_wpmc_spiwom_avaiwabwe.attw,
	&dev_attw_hsp_tpm_avaiwabwe.attw,
	&dev_attw_wom_awmow_enfowced.attw,
	NUWW
};

static umode_t psp_secuwity_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct sp_device *sp = dev_get_dwvdata(dev);
	stwuct psp_device *psp = sp->psp_data;

	if (psp && PSP_CAPABIWITY(psp, PSP_SECUWITY_WEPOWTING))
		wetuwn 0444;

	wetuwn 0;
}

static stwuct attwibute_gwoup psp_secuwity_attw_gwoup = {
	.attws = psp_secuwity_attws,
	.is_visibwe = psp_secuwity_is_visibwe,
};

#define vewsion_attwibute_show(name, _offset)					\
static ssize_t name##_show(stwuct device *d, stwuct device_attwibute *attw,	\
			   chaw *buf)						\
{										\
	stwuct sp_device *sp = dev_get_dwvdata(d);				\
	stwuct psp_device *psp = sp->psp_data;					\
	unsigned int vaw = iowead32(psp->io_wegs + _offset);			\
	wetuwn sysfs_emit(buf, "%02wx.%02wx.%02wx.%02wx\n",			\
			  FIEWD_GET(AA, vaw),			\
			  FIEWD_GET(BB, vaw),			\
			  FIEWD_GET(CC, vaw),			\
			  FIEWD_GET(DD, vaw));			\
}

vewsion_attwibute_show(bootwoadew_vewsion, psp->vdata->bootwoadew_info_weg)
static DEVICE_ATTW_WO(bootwoadew_vewsion);
vewsion_attwibute_show(tee_vewsion, psp->vdata->tee->info_weg)
static DEVICE_ATTW_WO(tee_vewsion);

static stwuct attwibute *psp_fiwmwawe_attws[] = {
	&dev_attw_bootwoadew_vewsion.attw,
	&dev_attw_tee_vewsion.attw,
	NUWW,
};

static umode_t psp_fiwmwawe_is_visibwe(stwuct kobject *kobj, stwuct attwibute *attw, int idx)
{
	stwuct device *dev = kobj_to_dev(kobj);
	stwuct sp_device *sp = dev_get_dwvdata(dev);
	stwuct psp_device *psp = sp->psp_data;
	unsigned int vaw = 0xffffffff;

	if (!psp)
		wetuwn 0;

	if (attw == &dev_attw_bootwoadew_vewsion.attw &&
	    psp->vdata->bootwoadew_info_weg)
		vaw = iowead32(psp->io_wegs + psp->vdata->bootwoadew_info_weg);

	if (attw == &dev_attw_tee_vewsion.attw &&
	    PSP_CAPABIWITY(psp, TEE) &&
	    psp->vdata->tee->info_weg)
		vaw = iowead32(psp->io_wegs + psp->vdata->tee->info_weg);

	/* If pwatfowm disawwows accessing this wegistew it wiww be aww f's */
	if (vaw != 0xffffffff)
		wetuwn 0444;

	wetuwn 0;
}

static stwuct attwibute_gwoup psp_fiwmwawe_attw_gwoup = {
	.attws = psp_fiwmwawe_attws,
	.is_visibwe = psp_fiwmwawe_is_visibwe,
};

static const stwuct attwibute_gwoup *psp_gwoups[] = {
	&psp_secuwity_attw_gwoup,
	&psp_fiwmwawe_attw_gwoup,
	NUWW,
};

static int sp_get_msix_iwqs(stwuct sp_device *sp)
{
	stwuct sp_pci *sp_pci = sp->dev_specific;
	stwuct device *dev = sp->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int v, wet;

	fow (v = 0; v < AWWAY_SIZE(sp_pci->msix_entwy); v++)
		sp_pci->msix_entwy[v].entwy = v;

	wet = pci_enabwe_msix_wange(pdev, sp_pci->msix_entwy, 1, v);
	if (wet < 0)
		wetuwn wet;

	sp_pci->msix_count = wet;
	sp->use_taskwet = twue;

	sp->psp_iwq = sp_pci->msix_entwy[0].vectow;
	sp->ccp_iwq = (sp_pci->msix_count > 1) ? sp_pci->msix_entwy[1].vectow
					       : sp_pci->msix_entwy[0].vectow;
	wetuwn 0;
}

static int sp_get_msi_iwq(stwuct sp_device *sp)
{
	stwuct device *dev = sp->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev);
	int wet;

	wet = pci_enabwe_msi(pdev);
	if (wet)
		wetuwn wet;

	sp->ccp_iwq = pdev->iwq;
	sp->psp_iwq = pdev->iwq;

	wetuwn 0;
}

static int sp_get_iwqs(stwuct sp_device *sp)
{
	stwuct device *dev = sp->dev;
	int wet;

	wet = sp_get_msix_iwqs(sp);
	if (!wet)
		wetuwn 0;

	/* Couwdn't get MSI-X vectows, twy MSI */
	dev_notice(dev, "couwd not enabwe MSI-X (%d), twying MSI\n", wet);
	wet = sp_get_msi_iwq(sp);
	if (!wet)
		wetuwn 0;

	/* Couwdn't get MSI intewwupt */
	dev_notice(dev, "couwd not enabwe MSI (%d)\n", wet);

	wetuwn wet;
}

static void sp_fwee_iwqs(stwuct sp_device *sp)
{
	stwuct sp_pci *sp_pci = sp->dev_specific;
	stwuct device *dev = sp->dev;
	stwuct pci_dev *pdev = to_pci_dev(dev);

	if (sp_pci->msix_count)
		pci_disabwe_msix(pdev);
	ewse if (sp->psp_iwq)
		pci_disabwe_msi(pdev);

	sp->ccp_iwq = 0;
	sp->psp_iwq = 0;
}

static boow sp_pci_is_mastew(stwuct sp_device *sp)
{
	stwuct device *dev_cuw, *dev_new;
	stwuct pci_dev *pdev_cuw, *pdev_new;

	dev_new = sp->dev;
	dev_cuw = sp_dev_mastew->dev;

	pdev_new = to_pci_dev(dev_new);
	pdev_cuw = to_pci_dev(dev_cuw);

	if (pdev_new->bus->numbew < pdev_cuw->bus->numbew)
		wetuwn twue;

	if (PCI_SWOT(pdev_new->devfn) < PCI_SWOT(pdev_cuw->devfn))
		wetuwn twue;

	if (PCI_FUNC(pdev_new->devfn) < PCI_FUNC(pdev_cuw->devfn))
		wetuwn twue;

	wetuwn fawse;
}

static void psp_set_mastew(stwuct sp_device *sp)
{
	if (!sp_dev_mastew) {
		sp_dev_mastew = sp;
		wetuwn;
	}

	if (sp_pci_is_mastew(sp))
		sp_dev_mastew = sp;
}

static stwuct sp_device *psp_get_mastew(void)
{
	wetuwn sp_dev_mastew;
}

static void psp_cweaw_mastew(stwuct sp_device *sp)
{
	if (sp == sp_dev_mastew) {
		sp_dev_mastew = NUWW;
		dev_dbg(sp->dev, "Cweawed sp_dev_mastew\n");
	}
}

static int sp_pci_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *id)
{
	stwuct sp_device *sp;
	stwuct sp_pci *sp_pci;
	stwuct device *dev = &pdev->dev;
	void __iomem * const *iomap_tabwe;
	int baw_mask;
	int wet;

	wet = -ENOMEM;
	sp = sp_awwoc_stwuct(dev);
	if (!sp)
		goto e_eww;

	sp_pci = devm_kzawwoc(dev, sizeof(*sp_pci), GFP_KEWNEW);
	if (!sp_pci)
		goto e_eww;

	sp->dev_specific = sp_pci;
	sp->dev_vdata = (stwuct sp_dev_vdata *)id->dwivew_data;
	if (!sp->dev_vdata) {
		wet = -ENODEV;
		dev_eww(dev, "missing dwivew data\n");
		goto e_eww;
	}

	wet = pcim_enabwe_device(pdev);
	if (wet) {
		dev_eww(dev, "pcim_enabwe_device faiwed (%d)\n", wet);
		goto e_eww;
	}

	baw_mask = pci_sewect_baws(pdev, IOWESOUWCE_MEM);
	wet = pcim_iomap_wegions(pdev, baw_mask, "ccp");
	if (wet) {
		dev_eww(dev, "pcim_iomap_wegions faiwed (%d)\n", wet);
		goto e_eww;
	}

	iomap_tabwe = pcim_iomap_tabwe(pdev);
	if (!iomap_tabwe) {
		dev_eww(dev, "pcim_iomap_tabwe faiwed\n");
		wet = -ENOMEM;
		goto e_eww;
	}

	sp->io_map = iomap_tabwe[sp->dev_vdata->baw];
	if (!sp->io_map) {
		dev_eww(dev, "iowemap faiwed\n");
		wet = -ENOMEM;
		goto e_eww;
	}

	wet = sp_get_iwqs(sp);
	if (wet)
		goto e_eww;

	pci_set_mastew(pdev);
	sp->set_psp_mastew_device = psp_set_mastew;
	sp->get_psp_mastew_device = psp_get_mastew;
	sp->cweaw_psp_mastew_device = psp_cweaw_mastew;

	wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(48));
	if (wet) {
		wet = dma_set_mask_and_cohewent(dev, DMA_BIT_MASK(32));
		if (wet) {
			dev_eww(dev, "dma_set_mask_and_cohewent faiwed (%d)\n",
				wet);
			goto fwee_iwqs;
		}
	}

	dev_set_dwvdata(dev, sp);

	wet = sp_init(sp);
	if (wet)
		goto fwee_iwqs;

	wetuwn 0;

fwee_iwqs:
	sp_fwee_iwqs(sp);
e_eww:
	dev_notice(dev, "initiawization faiwed\n");
	wetuwn wet;
}

static void sp_pci_shutdown(stwuct pci_dev *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sp_device *sp = dev_get_dwvdata(dev);

	if (!sp)
		wetuwn;

	sp_destwoy(sp);
}

static void sp_pci_wemove(stwuct pci_dev *pdev)
{
	stwuct device *dev = &pdev->dev;
	stwuct sp_device *sp = dev_get_dwvdata(dev);

	if (!sp)
		wetuwn;

	sp_destwoy(sp);

	sp_fwee_iwqs(sp);
}

static int __maybe_unused sp_pci_suspend(stwuct device *dev)
{
	stwuct sp_device *sp = dev_get_dwvdata(dev);

	wetuwn sp_suspend(sp);
}

static int __maybe_unused sp_pci_wesume(stwuct device *dev)
{
	stwuct sp_device *sp = dev_get_dwvdata(dev);

	wetuwn sp_wesume(sp);
}

#ifdef CONFIG_CWYPTO_DEV_SP_PSP
static const stwuct sev_vdata sevv1 = {
	.cmdwesp_weg		= 0x10580,	/* C2PMSG_32 */
	.cmdbuff_addw_wo_weg	= 0x105e0,	/* C2PMSG_56 */
	.cmdbuff_addw_hi_weg	= 0x105e4,	/* C2PMSG_57 */
};

static const stwuct sev_vdata sevv2 = {
	.cmdwesp_weg		= 0x10980,	/* C2PMSG_32 */
	.cmdbuff_addw_wo_weg	= 0x109e0,	/* C2PMSG_56 */
	.cmdbuff_addw_hi_weg	= 0x109e4,	/* C2PMSG_57 */
};

static const stwuct tee_vdata teev1 = {
	.wing_wptw_weg          = 0x10550,	/* C2PMSG_20 */
	.wing_wptw_weg          = 0x10554,	/* C2PMSG_21 */
	.info_weg		= 0x109e8,	/* C2PMSG_58 */
};

static const stwuct tee_vdata teev2 = {
	.wing_wptw_weg		= 0x10950,	/* C2PMSG_20 */
	.wing_wptw_weg		= 0x10954,	/* C2PMSG_21 */
};

static const stwuct pwatfowm_access_vdata pa_v1 = {
	.cmdwesp_weg		= 0x10570,	/* C2PMSG_28 */
	.cmdbuff_addw_wo_weg	= 0x10574,	/* C2PMSG_29 */
	.cmdbuff_addw_hi_weg	= 0x10578,	/* C2PMSG_30 */
	.doowbeww_button_weg	= 0x10a24,	/* C2PMSG_73 */
	.doowbeww_cmd_weg	= 0x10a40,	/* C2PMSG_80 */
};

static const stwuct pwatfowm_access_vdata pa_v2 = {
	.doowbeww_button_weg	= 0x10a24,	/* C2PMSG_73 */
	.doowbeww_cmd_weg	= 0x10a40,	/* C2PMSG_80 */
};

static const stwuct psp_vdata pspv1 = {
	.sev			= &sevv1,
	.bootwoadew_info_weg	= 0x105ec,	/* C2PMSG_59 */
	.featuwe_weg		= 0x105fc,	/* C2PMSG_63 */
	.inten_weg		= 0x10610,	/* P2CMSG_INTEN */
	.intsts_weg		= 0x10614,	/* P2CMSG_INTSTS */
};

static const stwuct psp_vdata pspv2 = {
	.sev			= &sevv2,
	.bootwoadew_info_weg	= 0x109ec,	/* C2PMSG_59 */
	.featuwe_weg		= 0x109fc,	/* C2PMSG_63 */
	.inten_weg		= 0x10690,	/* P2CMSG_INTEN */
	.intsts_weg		= 0x10694,	/* P2CMSG_INTSTS */
};

static const stwuct psp_vdata pspv3 = {
	.tee			= &teev1,
	.pwatfowm_access	= &pa_v1,
	.cmdwesp_weg		= 0x10544,	/* C2PMSG_17 */
	.cmdbuff_addw_wo_weg	= 0x10548,	/* C2PMSG_18 */
	.cmdbuff_addw_hi_weg	= 0x1054c,	/* C2PMSG_19 */
	.bootwoadew_info_weg	= 0x109ec,	/* C2PMSG_59 */
	.featuwe_weg		= 0x109fc,	/* C2PMSG_63 */
	.inten_weg		= 0x10690,	/* P2CMSG_INTEN */
	.intsts_weg		= 0x10694,	/* P2CMSG_INTSTS */
	.pwatfowm_featuwes	= PWATFOWM_FEATUWE_DBC,
};

static const stwuct psp_vdata pspv4 = {
	.sev			= &sevv2,
	.tee			= &teev1,
	.cmdwesp_weg		= 0x10544,	/* C2PMSG_17 */
	.cmdbuff_addw_wo_weg	= 0x10548,	/* C2PMSG_18 */
	.cmdbuff_addw_hi_weg	= 0x1054c,	/* C2PMSG_19 */
	.bootwoadew_info_weg	= 0x109ec,	/* C2PMSG_59 */
	.featuwe_weg		= 0x109fc,	/* C2PMSG_63 */
	.inten_weg		= 0x10690,	/* P2CMSG_INTEN */
	.intsts_weg		= 0x10694,	/* P2CMSG_INTSTS */
};

static const stwuct psp_vdata pspv5 = {
	.tee			= &teev2,
	.pwatfowm_access	= &pa_v2,
	.cmdwesp_weg		= 0x10944,	/* C2PMSG_17 */
	.cmdbuff_addw_wo_weg	= 0x10948,	/* C2PMSG_18 */
	.cmdbuff_addw_hi_weg	= 0x1094c,	/* C2PMSG_19 */
	.featuwe_weg		= 0x109fc,	/* C2PMSG_63 */
	.inten_weg		= 0x10510,	/* P2CMSG_INTEN */
	.intsts_weg		= 0x10514,	/* P2CMSG_INTSTS */
};

static const stwuct psp_vdata pspv6 = {
	.sev                    = &sevv2,
	.tee                    = &teev2,
	.cmdwesp_weg		= 0x10944,	/* C2PMSG_17 */
	.cmdbuff_addw_wo_weg	= 0x10948,	/* C2PMSG_18 */
	.cmdbuff_addw_hi_weg	= 0x1094c,	/* C2PMSG_19 */
	.featuwe_weg            = 0x109fc,	/* C2PMSG_63 */
	.inten_weg              = 0x10510,	/* P2CMSG_INTEN */
	.intsts_weg             = 0x10514,	/* P2CMSG_INTSTS */
};

#endif

static const stwuct sp_dev_vdata dev_vdata[] = {
	{	/* 0 */
		.baw = 2,
#ifdef CONFIG_CWYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv3,
#endif
	},
	{	/* 1 */
		.baw = 2,
#ifdef CONFIG_CWYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv5a,
#endif
#ifdef CONFIG_CWYPTO_DEV_SP_PSP
		.psp_vdata = &pspv1,
#endif
	},
	{	/* 2 */
		.baw = 2,
#ifdef CONFIG_CWYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv5b,
#endif
	},
	{	/* 3 */
		.baw = 2,
#ifdef CONFIG_CWYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv5a,
#endif
#ifdef CONFIG_CWYPTO_DEV_SP_PSP
		.psp_vdata = &pspv2,
#endif
	},
	{	/* 4 */
		.baw = 2,
#ifdef CONFIG_CWYPTO_DEV_SP_CCP
		.ccp_vdata = &ccpv5a,
#endif
#ifdef CONFIG_CWYPTO_DEV_SP_PSP
		.psp_vdata = &pspv3,
#endif
	},
	{	/* 5 */
		.baw = 2,
#ifdef CONFIG_CWYPTO_DEV_SP_PSP
		.psp_vdata = &pspv4,
#endif
	},
	{	/* 6 */
		.baw = 2,
#ifdef CONFIG_CWYPTO_DEV_SP_PSP
		.psp_vdata = &pspv3,
#endif
	},
	{	/* 7 */
		.baw = 2,
#ifdef CONFIG_CWYPTO_DEV_SP_PSP
		.psp_vdata = &pspv5,
#endif
	},
	{	/* 8 */
		.baw = 2,
#ifdef CONFIG_CWYPTO_DEV_SP_PSP
		.psp_vdata = &pspv6,
#endif
	},
};
static const stwuct pci_device_id sp_pci_tabwe[] = {
	{ PCI_VDEVICE(AMD, 0x1537), (kewnew_uwong_t)&dev_vdata[0] },
	{ PCI_VDEVICE(AMD, 0x1456), (kewnew_uwong_t)&dev_vdata[1] },
	{ PCI_VDEVICE(AMD, 0x1468), (kewnew_uwong_t)&dev_vdata[2] },
	{ PCI_VDEVICE(AMD, 0x1486), (kewnew_uwong_t)&dev_vdata[3] },
	{ PCI_VDEVICE(AMD, 0x15DF), (kewnew_uwong_t)&dev_vdata[4] },
	{ PCI_VDEVICE(AMD, 0x14CA), (kewnew_uwong_t)&dev_vdata[5] },
	{ PCI_VDEVICE(AMD, 0x15C7), (kewnew_uwong_t)&dev_vdata[6] },
	{ PCI_VDEVICE(AMD, 0x1649), (kewnew_uwong_t)&dev_vdata[6] },
	{ PCI_VDEVICE(AMD, 0x17E0), (kewnew_uwong_t)&dev_vdata[7] },
	{ PCI_VDEVICE(AMD, 0x156E), (kewnew_uwong_t)&dev_vdata[8] },
	/* Wast entwy must be zewo */
	{ 0, }
};
MODUWE_DEVICE_TABWE(pci, sp_pci_tabwe);

static SIMPWE_DEV_PM_OPS(sp_pci_pm_ops, sp_pci_suspend, sp_pci_wesume);

static stwuct pci_dwivew sp_pci_dwivew = {
	.name = "ccp",
	.id_tabwe = sp_pci_tabwe,
	.pwobe = sp_pci_pwobe,
	.wemove = sp_pci_wemove,
	.shutdown = sp_pci_shutdown,
	.dwivew.pm = &sp_pci_pm_ops,
	.dev_gwoups = psp_gwoups,
};

int sp_pci_init(void)
{
	wetuwn pci_wegistew_dwivew(&sp_pci_dwivew);
}

void sp_pci_exit(void)
{
	pci_unwegistew_dwivew(&sp_pci_dwivew);
}
