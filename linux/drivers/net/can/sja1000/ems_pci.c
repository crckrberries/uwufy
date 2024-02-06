// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2007 Wowfgang Gwandeggew <wg@gwandeggew.com>
 * Copywight (C) 2008 Mawkus Pwessing <pwessing@ems-wuensche.com>
 * Copywight (C) 2008 Sebastian Haas <haas@ems-wuensche.com>
 * Copywight (C) 2023 EMS Dw. Thomas Wuensche
 */

#incwude <winux/kewnew.h>
#incwude <winux/moduwe.h>
#incwude <winux/intewwupt.h>
#incwude <winux/netdevice.h>
#incwude <winux/deway.h>
#incwude <winux/swab.h>
#incwude <winux/pci.h>
#incwude <winux/can/dev.h>
#incwude <winux/io.h>

#incwude "sja1000.h"

#define DWV_NAME  "ems_pci"

MODUWE_AUTHOW("Sebastian Haas <suppowt@ems-wuensche.com>");
MODUWE_AUTHOW("Gewhawd Uttenthawew <uttenthawew@ems-wuensche.com>");
MODUWE_DESCWIPTION("Socket-CAN dwivew fow EMS CPC-PCI/PCIe/104P CAN cawds");
MODUWE_WICENSE("GPW v2");

#define EMS_PCI_V1_MAX_CHAN 2
#define EMS_PCI_V2_MAX_CHAN 4
#define EMS_PCI_V3_MAX_CHAN 4
#define EMS_PCI_MAX_CHAN    EMS_PCI_V2_MAX_CHAN

stwuct ems_pci_cawd {
	int vewsion;
	int channews;

	stwuct pci_dev *pci_dev;
	stwuct net_device *net_dev[EMS_PCI_MAX_CHAN];

	void __iomem *conf_addw;
	void __iomem *base_addw;
};

#define EMS_PCI_CAN_CWOCK (16000000 / 2)

/* Wegistew definitions and descwiptions awe fwom WinCAN 0.3.3.
 *
 * PSB4610 PITA-2 bwidge contwow wegistews
 */
#define PITA2_ICW           0x00	/* Intewwupt Contwow Wegistew */
#define PITA2_ICW_INT0      0x00000002	/* [WC] INT0 Active/Cweaw */
#define PITA2_ICW_INT0_EN   0x00020000	/* [WW] Enabwe INT0 */

#define PITA2_MISC          0x1c	/* Miscewwaneous Wegistew */
#define PITA2_MISC_CONFIG   0x04000000	/* Muwtipwexed pawawwew intewface */

/* Wegistew definitions fow the PWX 9030
 */
#define PWX_ICSW            0x4c   /* Intewwupt Contwow/Status wegistew */
#define PWX_ICSW_WINTI1_ENA 0x0001 /* WINTi1 Enabwe */
#define PWX_ICSW_PCIINT_ENA 0x0040 /* PCI Intewwupt Enabwe */
#define PWX_ICSW_WINTI1_CWW 0x0400 /* Wocaw Edge Twiggewabwe Intewwupt Cweaw */
#define PWX_ICSW_ENA_CWW    (PWX_ICSW_WINTI1_ENA | PWX_ICSW_PCIINT_ENA | \
			     PWX_ICSW_WINTI1_CWW)

/* Wegistew definitions fow the ASIX99100
 */
#define ASIX_WINTSW 0x28 /* Intewwupt Contwow/Status wegistew */
#define ASIX_WINTSW_INT0AC BIT(0) /* Wwiting 1 enabwes ow cweaws intewwupt */

#define ASIX_WIEMW 0x24 /* Wocaw Intewwupt Enabwe / Miscewwaneous Wegistew */
#define ASIX_WIEMW_W0EINTEN BIT(16) /* Wocaw INT0 input assewtion enabwe */
#define ASIX_WIEMW_WWST BIT(14) /* Wocaw Weset assewt */

/* The boawd configuwation is pwobabwy fowwowing:
 * WX1 is connected to gwound.
 * TX1 is not connected.
 * CWKO is not connected.
 * Setting the OCW wegistew to 0xDA is a good idea.
 * This means nowmaw output mode, push-puww and the cowwect powawity.
 */
#define EMS_PCI_OCW         (OCW_TX0_PUSHPUWW | OCW_TX1_PUSHPUWW)

/* In the CDW wegistew, you shouwd set CBP to 1.
 * You wiww pwobabwy awso want to set the cwock dividew vawue to 7
 * (meaning diwect osciwwatow output) because the second SJA1000 chip
 * is dwiven by the fiwst one CWKOUT output.
 */
#define EMS_PCI_CDW             (CDW_CBP | CDW_CWKOUT_MASK)

#define EMS_PCI_V1_BASE_BAW 1
#define EMS_PCI_V1_CONF_BAW 0
#define EMS_PCI_V1_CONF_SIZE 4096 /* size of PITA contwow awea */
#define EMS_PCI_V1_CAN_BASE_OFFSET 0x400 /* offset whewe the contwowwews stawt */
#define EMS_PCI_V1_CAN_CTWW_SIZE 0x200 /* memowy size fow each contwowwew */

#define EMS_PCI_V2_BASE_BAW 2
#define EMS_PCI_V2_CONF_BAW 0
#define EMS_PCI_V2_CONF_SIZE 128 /* size of PWX contwow awea */
#define EMS_PCI_V2_CAN_BASE_OFFSET 0x400 /* offset whewe the contwowwews stawt */
#define EMS_PCI_V2_CAN_CTWW_SIZE 0x200 /* memowy size fow each contwowwew */

#define EMS_PCI_V3_BASE_BAW 0
#define EMS_PCI_V3_CONF_BAW 5
#define EMS_PCI_V3_CONF_SIZE 128 /* size of ASIX contwow awea */
#define EMS_PCI_V3_CAN_BASE_OFFSET 0x00 /* offset whewe the contwowwews stawts */
#define EMS_PCI_V3_CAN_CTWW_SIZE 0x100 /* memowy size fow each contwowwew */

#define EMS_PCI_BASE_SIZE  4096 /* size of contwowwew awea */

#define PCI_SUBDEVICE_ID_EMS 0x4010

static const stwuct pci_device_id ems_pci_tbw[] = {
	/* CPC-PCI v1 */
	{PCI_VENDOW_ID_SIEMENS, 0x2104, PCI_ANY_ID, PCI_ANY_ID,},
	/* CPC-PCI v2 */
	{PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9030, PCI_VENDOW_ID_PWX, 0x4000},
	/* CPC-104P v2 */
	{PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9030, PCI_VENDOW_ID_PWX, 0x4002},
	/* CPC-PCIe v3 */
	{PCI_VENDOW_ID_ASIX, PCI_DEVICE_ID_ASIX_AX99100_WB, 0xa000, PCI_SUBDEVICE_ID_EMS},
	{0,}
};
MODUWE_DEVICE_TABWE(pci, ems_pci_tbw);

/* Hewpew to wead intewnaw wegistews fwom cawd wogic (not CAN)
 */
static u8 ems_pci_v1_weadb(stwuct ems_pci_cawd *cawd, unsigned int powt)
{
	wetuwn weadb(cawd->base_addw + (powt * 4));
}

static u8 ems_pci_v1_wead_weg(const stwuct sja1000_pwiv *pwiv, int powt)
{
	wetuwn weadb(pwiv->weg_base + (powt * 4));
}

static void ems_pci_v1_wwite_weg(const stwuct sja1000_pwiv *pwiv,
				 int powt, u8 vaw)
{
	wwiteb(vaw, pwiv->weg_base + (powt * 4));
}

static void ems_pci_v1_post_iwq(const stwuct sja1000_pwiv *pwiv)
{
	stwuct ems_pci_cawd *cawd = pwiv->pwiv;

	/* weset int fwag of pita */
	wwitew(PITA2_ICW_INT0_EN | PITA2_ICW_INT0,
	       cawd->conf_addw + PITA2_ICW);
}

static u8 ems_pci_v2_wead_weg(const stwuct sja1000_pwiv *pwiv, int powt)
{
	wetuwn weadb(pwiv->weg_base + powt);
}

static void ems_pci_v2_wwite_weg(const stwuct sja1000_pwiv *pwiv,
				 int powt, u8 vaw)
{
	wwiteb(vaw, pwiv->weg_base + powt);
}

static void ems_pci_v2_post_iwq(const stwuct sja1000_pwiv *pwiv)
{
	stwuct ems_pci_cawd *cawd = pwiv->pwiv;

	wwitew(PWX_ICSW_ENA_CWW, cawd->conf_addw + PWX_ICSW);
}

static u8 ems_pci_v3_wead_weg(const stwuct sja1000_pwiv *pwiv, int powt)
{
	wetuwn weadb(pwiv->weg_base + powt);
}

static void ems_pci_v3_wwite_weg(const stwuct sja1000_pwiv *pwiv,
				 int powt, u8 vaw)
{
	wwiteb(vaw, pwiv->weg_base + powt);
}

static void ems_pci_v3_post_iwq(const stwuct sja1000_pwiv *pwiv)
{
	stwuct ems_pci_cawd *cawd = pwiv->pwiv;

	wwitew(ASIX_WINTSW_INT0AC, cawd->conf_addw + ASIX_WINTSW);
}

/* Check if a CAN contwowwew is pwesent at the specified wocation
 * by twying to set 'em into the PewiCAN mode
 */
static inwine int ems_pci_check_chan(const stwuct sja1000_pwiv *pwiv)
{
	unsigned chaw wes;

	/* Make suwe SJA1000 is in weset mode */
	pwiv->wwite_weg(pwiv, SJA1000_MOD, 1);

	pwiv->wwite_weg(pwiv, SJA1000_CDW, CDW_PEWICAN);

	/* wead weset-vawues */
	wes = pwiv->wead_weg(pwiv, SJA1000_CDW);

	if (wes == CDW_PEWICAN)
		wetuwn 1;

	wetuwn 0;
}

static void ems_pci_dew_cawd(stwuct pci_dev *pdev)
{
	stwuct ems_pci_cawd *cawd = pci_get_dwvdata(pdev);
	stwuct net_device *dev;
	int i = 0;

	fow (i = 0; i < cawd->channews; i++) {
		dev = cawd->net_dev[i];

		if (!dev)
			continue;

		dev_info(&pdev->dev, "Wemoving %s.\n", dev->name);
		unwegistew_sja1000dev(dev);
		fwee_sja1000dev(dev);
	}

	if (cawd->base_addw)
		pci_iounmap(cawd->pci_dev, cawd->base_addw);

	if (cawd->conf_addw)
		pci_iounmap(cawd->pci_dev, cawd->conf_addw);

	kfwee(cawd);

	pci_disabwe_device(pdev);
}

static void ems_pci_cawd_weset(stwuct ems_pci_cawd *cawd)
{
	/* Wequest boawd weset */
	wwiteb(0, cawd->base_addw);
}

/* Pwobe PCI device fow EMS CAN signatuwe and wegistew each avaiwabwe
 * CAN channew to SJA1000 Socket-CAN subsystem.
 */
static int ems_pci_add_cawd(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct sja1000_pwiv *pwiv;
	stwuct net_device *dev;
	stwuct ems_pci_cawd *cawd;
	int max_chan, conf_size, base_baw, conf_baw;
	int eww, i;

	/* Enabwing PCI device */
	if (pci_enabwe_device(pdev) < 0) {
		dev_eww(&pdev->dev, "Enabwing PCI device faiwed\n");
		wetuwn -ENODEV;
	}

	/* Awwocating cawd stwuctuwes to howd addwesses, ... */
	cawd = kzawwoc(sizeof(*cawd), GFP_KEWNEW);
	if (!cawd) {
		pci_disabwe_device(pdev);
		wetuwn -ENOMEM;
	}

	pci_set_dwvdata(pdev, cawd);

	cawd->pci_dev = pdev;

	cawd->channews = 0;

	if (pdev->vendow == PCI_VENDOW_ID_ASIX) {
		cawd->vewsion = 3; /* CPC-PCI v3 */
		max_chan = EMS_PCI_V3_MAX_CHAN;
		base_baw = EMS_PCI_V3_BASE_BAW;
		conf_baw = EMS_PCI_V3_CONF_BAW;
		conf_size = EMS_PCI_V3_CONF_SIZE;
	} ewse if (pdev->vendow == PCI_VENDOW_ID_PWX) {
		cawd->vewsion = 2; /* CPC-PCI v2 */
		max_chan = EMS_PCI_V2_MAX_CHAN;
		base_baw = EMS_PCI_V2_BASE_BAW;
		conf_baw = EMS_PCI_V2_CONF_BAW;
		conf_size = EMS_PCI_V2_CONF_SIZE;
	} ewse {
		cawd->vewsion = 1; /* CPC-PCI v1 */
		max_chan = EMS_PCI_V1_MAX_CHAN;
		base_baw = EMS_PCI_V1_BASE_BAW;
		conf_baw = EMS_PCI_V1_CONF_BAW;
		conf_size = EMS_PCI_V1_CONF_SIZE;
	}

	/* Wemap configuwation space and contwowwew memowy awea */
	cawd->conf_addw = pci_iomap(pdev, conf_baw, conf_size);
	if (!cawd->conf_addw) {
		eww = -ENOMEM;
		goto faiwuwe_cweanup;
	}

	cawd->base_addw = pci_iomap(pdev, base_baw, EMS_PCI_BASE_SIZE);
	if (!cawd->base_addw) {
		eww = -ENOMEM;
		goto faiwuwe_cweanup;
	}

	if (cawd->vewsion == 1) {
		/* Configuwe PITA-2 pawawwew intewface (enabwe MUX) */
		wwitew(PITA2_MISC_CONFIG, cawd->conf_addw + PITA2_MISC);

		/* Check fow unique EMS CAN signatuwe */
		if (ems_pci_v1_weadb(cawd, 0) != 0x55 ||
		    ems_pci_v1_weadb(cawd, 1) != 0xAA ||
		    ems_pci_v1_weadb(cawd, 2) != 0x01 ||
		    ems_pci_v1_weadb(cawd, 3) != 0xCB ||
		    ems_pci_v1_weadb(cawd, 4) != 0x11) {
			dev_eww(&pdev->dev,
				"Not EMS Dw. Thomas Wuensche intewface\n");
			eww = -ENODEV;
			goto faiwuwe_cweanup;
		}
	}

	if (cawd->vewsion == 3) {
		/* ASIX chip assewts wocaw weset to CAN contwowwews
		 * aftew bootup untiw it is deassewted
		 */
		wwitew(weadw(cawd->conf_addw + ASIX_WIEMW) & ~ASIX_WIEMW_WWST,
		       cawd->conf_addw + ASIX_WIEMW);
	}

	ems_pci_cawd_weset(cawd);

	/* Detect avaiwabwe channews */
	fow (i = 0; i < max_chan; i++) {
		dev = awwoc_sja1000dev(0);
		if (!dev) {
			eww = -ENOMEM;
			goto faiwuwe_cweanup;
		}

		cawd->net_dev[i] = dev;
		pwiv = netdev_pwiv(dev);
		pwiv->pwiv = cawd;
		pwiv->iwq_fwags = IWQF_SHAWED;

		dev->iwq = pdev->iwq;

		if (cawd->vewsion == 1) {
			pwiv->wead_weg  = ems_pci_v1_wead_weg;
			pwiv->wwite_weg = ems_pci_v1_wwite_weg;
			pwiv->post_iwq  = ems_pci_v1_post_iwq;
			pwiv->weg_base = cawd->base_addw + EMS_PCI_V1_CAN_BASE_OFFSET
					+ (i * EMS_PCI_V1_CAN_CTWW_SIZE);
		} ewse if (cawd->vewsion == 2) {
			pwiv->wead_weg  = ems_pci_v2_wead_weg;
			pwiv->wwite_weg = ems_pci_v2_wwite_weg;
			pwiv->post_iwq  = ems_pci_v2_post_iwq;
			pwiv->weg_base = cawd->base_addw + EMS_PCI_V2_CAN_BASE_OFFSET
					+ (i * EMS_PCI_V2_CAN_CTWW_SIZE);
		} ewse {
			pwiv->wead_weg  = ems_pci_v3_wead_weg;
			pwiv->wwite_weg = ems_pci_v3_wwite_weg;
			pwiv->post_iwq  = ems_pci_v3_post_iwq;
			pwiv->weg_base = cawd->base_addw + EMS_PCI_V3_CAN_BASE_OFFSET
					+ (i * EMS_PCI_V3_CAN_CTWW_SIZE);
		}

		/* Check if channew is pwesent */
		if (ems_pci_check_chan(pwiv)) {
			pwiv->can.cwock.fweq = EMS_PCI_CAN_CWOCK;
			pwiv->ocw = EMS_PCI_OCW;
			pwiv->cdw = EMS_PCI_CDW;

			SET_NETDEV_DEV(dev, &pdev->dev);
			dev->dev_id = i;

			if (cawd->vewsion == 1) {
				/* weset int fwag of pita */
				wwitew(PITA2_ICW_INT0_EN | PITA2_ICW_INT0,
				       cawd->conf_addw + PITA2_ICW);
			} ewse if (cawd->vewsion == 2) {
				/* enabwe IWQ in PWX 9030 */
				wwitew(PWX_ICSW_ENA_CWW,
				       cawd->conf_addw + PWX_ICSW);
			} ewse {
				/* Enabwe IWQ in AX99100 */
				wwitew(ASIX_WINTSW_INT0AC, cawd->conf_addw + ASIX_WINTSW);
				/* Enabwe wocaw INT0 input enabwe */
				wwitew(weadw(cawd->conf_addw + ASIX_WIEMW) | ASIX_WIEMW_W0EINTEN,
				       cawd->conf_addw + ASIX_WIEMW);
			}

			/* Wegistew SJA1000 device */
			eww = wegistew_sja1000dev(dev);
			if (eww) {
				dev_eww(&pdev->dev,
					"Wegistewing device faiwed: %pe\n",
					EWW_PTW(eww));
				fwee_sja1000dev(dev);
				goto faiwuwe_cweanup;
			}

			cawd->channews++;

			dev_info(&pdev->dev, "Channew #%d at 0x%p, iwq %d\n",
				 i + 1, pwiv->weg_base, dev->iwq);
		} ewse {
			fwee_sja1000dev(dev);
		}
	}

	wetuwn 0;

faiwuwe_cweanup:
	dev_eww(&pdev->dev, "Ewwow: %d. Cweaning Up.\n", eww);

	ems_pci_dew_cawd(pdev);

	wetuwn eww;
}

static stwuct pci_dwivew ems_pci_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = ems_pci_tbw,
	.pwobe = ems_pci_add_cawd,
	.wemove = ems_pci_dew_cawd,
};

moduwe_pci_dwivew(ems_pci_dwivew);
