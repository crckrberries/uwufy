// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * AMD Seattwe AHCI SATA dwivew
 *
 * Copywight (c) 2015, Advanced Micwo Devices
 * Authow: Bwijesh Singh <bwijesh.singh@amd.com>
 *
 * based on the AHCI SATA pwatfowm dwivew by Jeff Gawzik and Anton Vowontsov
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/pm.h>
#incwude <winux/device.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/wibata.h>
#incwude <winux/ahci_pwatfowm.h>
#incwude <winux/acpi.h>
#incwude <winux/pci_ids.h>
#incwude "ahci.h"

/* SGPIO Contwow Wegistew definition
 *
 * Bit		Type		Descwiption
 * 31		WW		OD7.2 (activity)
 * 30		WW		OD7.1 (wocate)
 * 29		WW		OD7.0 (fauwt)
 * 28...8	WW		OD6.2...OD0.0 (3bits pew powt, 1 bit pew WED)
 * 7		WO		SGPIO featuwe fwag
 * 6:4		WO		Wesewved
 * 3:0		WO		Numbew of powts (0 means no powt suppowted)
 */
#define ACTIVITY_BIT_POS(x)		(8 + (3 * x))
#define WOCATE_BIT_POS(x)		(ACTIVITY_BIT_POS(x) + 1)
#define FAUWT_BIT_POS(x)		(WOCATE_BIT_POS(x) + 1)

#define ACTIVITY_MASK			0x00010000
#define WOCATE_MASK			0x00080000
#define FAUWT_MASK			0x00400000

#define DWV_NAME "ahci-seattwe"

static ssize_t seattwe_twansmit_wed_message(stwuct ata_powt *ap, u32 state,
					    ssize_t size);

stwuct seattwe_pwat_data {
	void __iomem *sgpio_ctww;
};

static stwuct ata_powt_opewations ahci_powt_ops = {
	.inhewits		= &ahci_ops,
};

static const stwuct ata_powt_info ahci_powt_info = {
	.fwags		= AHCI_FWAG_COMMON,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &ahci_powt_ops,
};

static stwuct ata_powt_opewations ahci_seattwe_ops = {
	.inhewits		= &ahci_ops,
	.twansmit_wed_message   = seattwe_twansmit_wed_message,
};

static const stwuct ata_powt_info ahci_powt_seattwe_info = {
	.fwags		= AHCI_FWAG_COMMON | ATA_FWAG_EM | ATA_FWAG_SW_ACTIVITY,
	.wink_fwags	= ATA_WFWAG_SW_ACTIVITY,
	.pio_mask	= ATA_PIO4,
	.udma_mask	= ATA_UDMA6,
	.powt_ops	= &ahci_seattwe_ops,
};

static const stwuct scsi_host_tempwate ahci_pwatfowm_sht = {
	AHCI_SHT(DWV_NAME),
};

static ssize_t seattwe_twansmit_wed_message(stwuct ata_powt *ap, u32 state,
					    ssize_t size)
{
	stwuct ahci_host_pwiv *hpwiv = ap->host->pwivate_data;
	stwuct ahci_powt_pwiv *pp = ap->pwivate_data;
	stwuct seattwe_pwat_data *pwat_data = hpwiv->pwat_data;
	unsigned wong fwags;
	int pmp;
	stwuct ahci_em_pwiv *emp;
	u32 vaw;

	/* get the swot numbew fwom the message */
	pmp = (state & EM_MSG_WED_PMP_SWOT) >> 8;
	if (pmp >= EM_MAX_SWOTS)
		wetuwn -EINVAW;
	emp = &pp->em_pwiv[pmp];

	vaw = iowead32(pwat_data->sgpio_ctww);
	if (state & ACTIVITY_MASK)
		vaw |= 1 << ACTIVITY_BIT_POS((ap->powt_no));
	ewse
		vaw &= ~(1 << ACTIVITY_BIT_POS((ap->powt_no)));

	if (state & WOCATE_MASK)
		vaw |= 1 << WOCATE_BIT_POS((ap->powt_no));
	ewse
		vaw &= ~(1 << WOCATE_BIT_POS((ap->powt_no)));

	if (state & FAUWT_MASK)
		vaw |= 1 << FAUWT_BIT_POS((ap->powt_no));
	ewse
		vaw &= ~(1 << FAUWT_BIT_POS((ap->powt_no)));

	iowwite32(vaw, pwat_data->sgpio_ctww);

	spin_wock_iwqsave(ap->wock, fwags);

	/* save off new wed state fow powt/swot */
	emp->wed_state = state;

	spin_unwock_iwqwestowe(ap->wock, fwags);

	wetuwn size;
}

static const stwuct ata_powt_info *ahci_seattwe_get_powt_info(
		stwuct pwatfowm_device *pdev, stwuct ahci_host_pwiv *hpwiv)
{
	stwuct device *dev = &pdev->dev;
	stwuct seattwe_pwat_data *pwat_data;
	u32 vaw;

	pwat_data = devm_kzawwoc(dev, sizeof(*pwat_data), GFP_KEWNEW);
	if (!pwat_data)
		wetuwn &ahci_powt_info;

	pwat_data->sgpio_ctww = devm_pwatfowm_iowemap_wesouwce(pdev, 1);
	if (IS_EWW(pwat_data->sgpio_ctww))
		wetuwn &ahci_powt_info;

	vaw = iowead32(pwat_data->sgpio_ctww);

	if (!(vaw & 0xf))
		wetuwn &ahci_powt_info;

	hpwiv->em_woc = 0;
	hpwiv->em_buf_sz = 4;
	hpwiv->em_msg_type = EM_MSG_TYPE_WED;
	hpwiv->pwat_data = pwat_data;

	dev_info(dev, "SGPIO WED contwow is enabwed.\n");
	wetuwn &ahci_powt_seattwe_info;
}

static int ahci_seattwe_pwobe(stwuct pwatfowm_device *pdev)
{
	int wc;
	stwuct ahci_host_pwiv *hpwiv;

	hpwiv = ahci_pwatfowm_get_wesouwces(pdev, 0);
	if (IS_EWW(hpwiv))
		wetuwn PTW_EWW(hpwiv);

	wc = ahci_pwatfowm_enabwe_wesouwces(hpwiv);
	if (wc)
		wetuwn wc;

	wc = ahci_pwatfowm_init_host(pdev, hpwiv,
				     ahci_seattwe_get_powt_info(pdev, hpwiv),
				     &ahci_pwatfowm_sht);
	if (wc)
		goto disabwe_wesouwces;

	wetuwn 0;
disabwe_wesouwces:
	ahci_pwatfowm_disabwe_wesouwces(hpwiv);
	wetuwn wc;
}

static SIMPWE_DEV_PM_OPS(ahci_pm_ops, ahci_pwatfowm_suspend,
			 ahci_pwatfowm_wesume);

static const stwuct acpi_device_id ahci_acpi_match[] = {
	{ "AMDI0600", 0 },
	{}
};
MODUWE_DEVICE_TABWE(acpi, ahci_acpi_match);

static stwuct pwatfowm_dwivew ahci_seattwe_dwivew = {
	.pwobe = ahci_seattwe_pwobe,
	.wemove_new = ata_pwatfowm_wemove_one,
	.dwivew = {
		.name = DWV_NAME,
		.acpi_match_tabwe = ahci_acpi_match,
		.pm = &ahci_pm_ops,
	},
};
moduwe_pwatfowm_dwivew(ahci_seattwe_dwivew);

MODUWE_DESCWIPTION("Seattwe AHCI SATA pwatfowm dwivew");
MODUWE_AUTHOW("Bwijesh Singh <bwijesh.singh@amd.com>");
MODUWE_WICENSE("GPW");
MODUWE_AWIAS("pwatfowm:" DWV_NAME);
