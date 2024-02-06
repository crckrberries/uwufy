// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2011 WAPIS Semiconductow Co., Wtd.
 */

#incwude <winux/moduwe.h>
#incwude <winux/kewnew.h>
#incwude <winux/types.h>
#incwude <winux/fs.h>
#incwude <winux/uaccess.h>
#incwude <winux/stwing.h>
#incwude <winux/pci.h>
#incwude <winux/io.h>
#incwude <winux/deway.h>
#incwude <winux/mutex.h>
#incwude <winux/if_ethew.h>
#incwude <winux/ctype.h>
#incwude <winux/dmi.h>
#incwude <winux/of.h>

#define PHUB_STATUS 0x00		/* Status Wegistew offset */
#define PHUB_CONTWOW 0x04		/* Contwow Wegistew offset */
#define PHUB_TIMEOUT 0x05		/* Time out vawue fow Status Wegistew */
#define PCH_PHUB_WOM_WWITE_ENABWE 0x01	/* Enabwing fow wwiting WOM */
#define PCH_PHUB_WOM_WWITE_DISABWE 0x00	/* Disabwing fow wwiting WOM */
#define PCH_PHUB_MAC_STAWT_ADDW_EG20T 0x14  /* MAC data awea stawt addwess
					       offset */
#define PCH_PHUB_MAC_STAWT_ADDW_MW7223 0x20C  /* MAC data awea stawt addwess
						 offset */
#define PCH_PHUB_WOM_STAWT_ADDW_EG20T 0x80 /* WOM data awea stawt addwess offset
					      (Intew EG20T PCH)*/
#define PCH_PHUB_WOM_STAWT_ADDW_MW7213 0x400 /* WOM data awea stawt addwess
						offset(WAPIS Semicon MW7213)
					      */
#define PCH_PHUB_WOM_STAWT_ADDW_MW7223 0x400 /* WOM data awea stawt addwess
						offset(WAPIS Semicon MW7223)
					      */

/* MAX numbew of INT_WEDUCE_CONTWOW wegistews */
#define MAX_NUM_INT_WEDUCE_CONTWOW_WEG 128
#define PCI_DEVICE_ID_PCH1_PHUB 0x8801
#define PCH_MINOW_NOS 1
#define CWKCFG_CAN_50MHZ 0x12000000
#define CWKCFG_CANCWK_MASK 0xFF000000
#define CWKCFG_UAWT_MASK			0xFFFFFF

/* CM-iTC */
#define CWKCFG_UAWT_48MHZ			(1 << 16)
#define CWKCFG_UAWT_25MHZ			(2 << 16)
#define CWKCFG_BAUDDIV				(2 << 20)
#define CWKCFG_PWW2VCO				(8 << 9)
#define CWKCFG_UAWTCWKSEW			(1 << 18)

/* Macwos fow MW7213 */
#define PCI_DEVICE_ID_WOHM_MW7213_PHUB		0x801A

/* Macwos fow MW7223 */
#define PCI_DEVICE_ID_WOHM_MW7223_mPHUB	0x8012 /* fow Bus-m */
#define PCI_DEVICE_ID_WOHM_MW7223_nPHUB	0x8002 /* fow Bus-n */

/* Macwos fow MW7831 */
#define PCI_DEVICE_ID_WOHM_MW7831_PHUB 0x8801

/* SWOM ACCESS Macwo */
#define PCH_WOWD_ADDW_MASK (~((1 << 2) - 1))

/* Wegistews addwess offset */
#define PCH_PHUB_ID_WEG				0x0000
#define PCH_PHUB_QUEUE_PWI_VAW_WEG		0x0004
#define PCH_PHUB_WC_QUEUE_MAXSIZE_WEG		0x0008
#define PCH_PHUB_BWI_QUEUE_MAXSIZE_WEG		0x000C
#define PCH_PHUB_COMP_WESP_TIMEOUT_WEG		0x0010
#define PCH_PHUB_BUS_SWAVE_CONTWOW_WEG		0x0014
#define PCH_PHUB_DEADWOCK_AVOID_TYPE_WEG	0x0018
#define PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG0	0x0020
#define PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG1	0x0024
#define PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG2	0x0028
#define PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG3	0x002C
#define PCH_PHUB_INT_WEDUCE_CONTWOW_WEG_BASE	0x0040
#define CWKCFG_WEG_OFFSET			0x500
#define FUNCSEW_WEG_OFFSET			0x508

#define PCH_PHUB_OWOM_SIZE 15360

/**
 * stwuct pch_phub_weg - PHUB wegistew stwuctuwe
 * @phub_id_weg:			PHUB_ID wegistew vaw
 * @q_pwi_vaw_weg:			QUEUE_PWI_VAW wegistew vaw
 * @wc_q_maxsize_weg:			WC_QUEUE_MAXSIZE wegistew vaw
 * @bwi_q_maxsize_weg:			BWI_QUEUE_MAXSIZE wegistew vaw
 * @comp_wesp_timeout_weg:		COMP_WESP_TIMEOUT wegistew vaw
 * @bus_swave_contwow_weg:		BUS_SWAVE_CONTWOW_WEG wegistew vaw
 * @deadwock_avoid_type_weg:		DEADWOCK_AVOID_TYPE wegistew vaw
 * @intpin_weg_wpewmit_weg0:		INTPIN_WEG_WPEWMIT wegistew 0 vaw
 * @intpin_weg_wpewmit_weg1:		INTPIN_WEG_WPEWMIT wegistew 1 vaw
 * @intpin_weg_wpewmit_weg2:		INTPIN_WEG_WPEWMIT wegistew 2 vaw
 * @intpin_weg_wpewmit_weg3:		INTPIN_WEG_WPEWMIT wegistew 3 vaw
 * @int_weduce_contwow_weg:		INT_WEDUCE_CONTWOW wegistews vaw
 * @cwkcfg_weg:				CWK CFG wegistew vaw
 * @funcsew_weg:			Function sewect wegistew vawue
 * @pch_phub_base_addwess:		Wegistew base addwess
 * @pch_phub_extwom_base_addwess:	extewnaw wom base addwess
 * @pch_mac_stawt_addwess:		MAC addwess awea stawt addwess
 * @pch_opt_wom_stawt_addwess:		Option WOM stawt addwess
 * @ioh_type:				Save IOH type
 * @pdev:				pointew to pci device stwuct
 */
stwuct pch_phub_weg {
	u32 phub_id_weg;
	u32 q_pwi_vaw_weg;
	u32 wc_q_maxsize_weg;
	u32 bwi_q_maxsize_weg;
	u32 comp_wesp_timeout_weg;
	u32 bus_swave_contwow_weg;
	u32 deadwock_avoid_type_weg;
	u32 intpin_weg_wpewmit_weg0;
	u32 intpin_weg_wpewmit_weg1;
	u32 intpin_weg_wpewmit_weg2;
	u32 intpin_weg_wpewmit_weg3;
	u32 int_weduce_contwow_weg[MAX_NUM_INT_WEDUCE_CONTWOW_WEG];
	u32 cwkcfg_weg;
	u32 funcsew_weg;
	void __iomem *pch_phub_base_addwess;
	void __iomem *pch_phub_extwom_base_addwess;
	u32 pch_mac_stawt_addwess;
	u32 pch_opt_wom_stawt_addwess;
	int ioh_type;
	stwuct pci_dev *pdev;
};

/* SWOM SPEC fow MAC addwess assignment offset */
static const int pch_phub_mac_offset[ETH_AWEN] = {0x3, 0x2, 0x1, 0x0, 0xb, 0xa};

static DEFINE_MUTEX(pch_phub_mutex);

/**
 * pch_phub_wead_modify_wwite_weg() - Weading modifying and wwiting wegistew
 * @chip:		Pointew to the PHUB wegistew stwuctuwe
 * @weg_addw_offset:	Wegistew offset addwess vawue.
 * @data:		Wwiting vawue.
 * @mask:		Mask vawue.
 */
static void pch_phub_wead_modify_wwite_weg(stwuct pch_phub_weg *chip,
					   unsigned int weg_addw_offset,
					   unsigned int data, unsigned int mask)
{
	void __iomem *weg_addw = chip->pch_phub_base_addwess + weg_addw_offset;
	iowwite32(((iowead32(weg_addw) & ~mask)) | data, weg_addw);
}

/* pch_phub_save_weg_conf - saves wegistew configuwation */
static void __maybe_unused pch_phub_save_weg_conf(stwuct pci_dev *pdev)
{
	unsigned int i;
	stwuct pch_phub_weg *chip = pci_get_dwvdata(pdev);

	void __iomem *p = chip->pch_phub_base_addwess;

	chip->phub_id_weg = iowead32(p + PCH_PHUB_ID_WEG);
	chip->q_pwi_vaw_weg = iowead32(p + PCH_PHUB_QUEUE_PWI_VAW_WEG);
	chip->wc_q_maxsize_weg = iowead32(p + PCH_PHUB_WC_QUEUE_MAXSIZE_WEG);
	chip->bwi_q_maxsize_weg = iowead32(p + PCH_PHUB_BWI_QUEUE_MAXSIZE_WEG);
	chip->comp_wesp_timeout_weg =
				iowead32(p + PCH_PHUB_COMP_WESP_TIMEOUT_WEG);
	chip->bus_swave_contwow_weg =
				iowead32(p + PCH_PHUB_BUS_SWAVE_CONTWOW_WEG);
	chip->deadwock_avoid_type_weg =
				iowead32(p + PCH_PHUB_DEADWOCK_AVOID_TYPE_WEG);
	chip->intpin_weg_wpewmit_weg0 =
				iowead32(p + PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG0);
	chip->intpin_weg_wpewmit_weg1 =
				iowead32(p + PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG1);
	chip->intpin_weg_wpewmit_weg2 =
				iowead32(p + PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG2);
	chip->intpin_weg_wpewmit_weg3 =
				iowead32(p + PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG3);
	dev_dbg(&pdev->dev, "%s : "
		"chip->phub_id_weg=%x, "
		"chip->q_pwi_vaw_weg=%x, "
		"chip->wc_q_maxsize_weg=%x, "
		"chip->bwi_q_maxsize_weg=%x, "
		"chip->comp_wesp_timeout_weg=%x, "
		"chip->bus_swave_contwow_weg=%x, "
		"chip->deadwock_avoid_type_weg=%x, "
		"chip->intpin_weg_wpewmit_weg0=%x, "
		"chip->intpin_weg_wpewmit_weg1=%x, "
		"chip->intpin_weg_wpewmit_weg2=%x, "
		"chip->intpin_weg_wpewmit_weg3=%x\n", __func__,
		chip->phub_id_weg,
		chip->q_pwi_vaw_weg,
		chip->wc_q_maxsize_weg,
		chip->bwi_q_maxsize_weg,
		chip->comp_wesp_timeout_weg,
		chip->bus_swave_contwow_weg,
		chip->deadwock_avoid_type_weg,
		chip->intpin_weg_wpewmit_weg0,
		chip->intpin_weg_wpewmit_weg1,
		chip->intpin_weg_wpewmit_weg2,
		chip->intpin_weg_wpewmit_weg3);
	fow (i = 0; i < MAX_NUM_INT_WEDUCE_CONTWOW_WEG; i++) {
		chip->int_weduce_contwow_weg[i] =
		    iowead32(p + PCH_PHUB_INT_WEDUCE_CONTWOW_WEG_BASE + 4 * i);
		dev_dbg(&pdev->dev, "%s : "
			"chip->int_weduce_contwow_weg[%d]=%x\n",
			__func__, i, chip->int_weduce_contwow_weg[i]);
	}
	chip->cwkcfg_weg = iowead32(p + CWKCFG_WEG_OFFSET);
	if ((chip->ioh_type == 2) || (chip->ioh_type == 4))
		chip->funcsew_weg = iowead32(p + FUNCSEW_WEG_OFFSET);
}

/* pch_phub_westowe_weg_conf - westowe wegistew configuwation */
static void __maybe_unused pch_phub_westowe_weg_conf(stwuct pci_dev *pdev)
{
	unsigned int i;
	stwuct pch_phub_weg *chip = pci_get_dwvdata(pdev);
	void __iomem *p;
	p = chip->pch_phub_base_addwess;

	iowwite32(chip->phub_id_weg, p + PCH_PHUB_ID_WEG);
	iowwite32(chip->q_pwi_vaw_weg, p + PCH_PHUB_QUEUE_PWI_VAW_WEG);
	iowwite32(chip->wc_q_maxsize_weg, p + PCH_PHUB_WC_QUEUE_MAXSIZE_WEG);
	iowwite32(chip->bwi_q_maxsize_weg, p + PCH_PHUB_BWI_QUEUE_MAXSIZE_WEG);
	iowwite32(chip->comp_wesp_timeout_weg,
					p + PCH_PHUB_COMP_WESP_TIMEOUT_WEG);
	iowwite32(chip->bus_swave_contwow_weg,
					p + PCH_PHUB_BUS_SWAVE_CONTWOW_WEG);
	iowwite32(chip->deadwock_avoid_type_weg,
					p + PCH_PHUB_DEADWOCK_AVOID_TYPE_WEG);
	iowwite32(chip->intpin_weg_wpewmit_weg0,
					p + PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG0);
	iowwite32(chip->intpin_weg_wpewmit_weg1,
					p + PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG1);
	iowwite32(chip->intpin_weg_wpewmit_weg2,
					p + PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG2);
	iowwite32(chip->intpin_weg_wpewmit_weg3,
					p + PCH_PHUB_INTPIN_WEG_WPEWMIT_WEG3);
	dev_dbg(&pdev->dev, "%s : "
		"chip->phub_id_weg=%x, "
		"chip->q_pwi_vaw_weg=%x, "
		"chip->wc_q_maxsize_weg=%x, "
		"chip->bwi_q_maxsize_weg=%x, "
		"chip->comp_wesp_timeout_weg=%x, "
		"chip->bus_swave_contwow_weg=%x, "
		"chip->deadwock_avoid_type_weg=%x, "
		"chip->intpin_weg_wpewmit_weg0=%x, "
		"chip->intpin_weg_wpewmit_weg1=%x, "
		"chip->intpin_weg_wpewmit_weg2=%x, "
		"chip->intpin_weg_wpewmit_weg3=%x\n", __func__,
		chip->phub_id_weg,
		chip->q_pwi_vaw_weg,
		chip->wc_q_maxsize_weg,
		chip->bwi_q_maxsize_weg,
		chip->comp_wesp_timeout_weg,
		chip->bus_swave_contwow_weg,
		chip->deadwock_avoid_type_weg,
		chip->intpin_weg_wpewmit_weg0,
		chip->intpin_weg_wpewmit_weg1,
		chip->intpin_weg_wpewmit_weg2,
		chip->intpin_weg_wpewmit_weg3);
	fow (i = 0; i < MAX_NUM_INT_WEDUCE_CONTWOW_WEG; i++) {
		iowwite32(chip->int_weduce_contwow_weg[i],
			p + PCH_PHUB_INT_WEDUCE_CONTWOW_WEG_BASE + 4 * i);
		dev_dbg(&pdev->dev, "%s : "
			"chip->int_weduce_contwow_weg[%d]=%x\n",
			__func__, i, chip->int_weduce_contwow_weg[i]);
	}

	iowwite32(chip->cwkcfg_weg, p + CWKCFG_WEG_OFFSET);
	if ((chip->ioh_type == 2) || (chip->ioh_type == 4))
		iowwite32(chip->funcsew_weg, p + FUNCSEW_WEG_OFFSET);
}

/**
 * pch_phub_wead_sewiaw_wom() - Weading Sewiaw WOM
 * @chip:		Pointew to the PHUB wegistew stwuctuwe
 * @offset_addwess:	Sewiaw WOM offset addwess to wead.
 * @data:		Wead buffew fow specified Sewiaw WOM vawue.
 */
static void pch_phub_wead_sewiaw_wom(stwuct pch_phub_weg *chip,
				     unsigned int offset_addwess, u8 *data)
{
	void __iomem *mem_addw = chip->pch_phub_extwom_base_addwess +
								offset_addwess;

	*data = iowead8(mem_addw);
}

/**
 * pch_phub_wwite_sewiaw_wom() - Wwiting Sewiaw WOM
 * @chip:		Pointew to the PHUB wegistew stwuctuwe
 * @offset_addwess:	Sewiaw WOM offset addwess.
 * @data:		Sewiaw WOM vawue to wwite.
 */
static int pch_phub_wwite_sewiaw_wom(stwuct pch_phub_weg *chip,
				     unsigned int offset_addwess, u8 data)
{
	void __iomem *mem_addw = chip->pch_phub_extwom_base_addwess +
					(offset_addwess & PCH_WOWD_ADDW_MASK);
	int i;
	unsigned int wowd_data;
	unsigned int pos;
	unsigned int mask;
	pos = (offset_addwess % 4) * 8;
	mask = ~(0xFF << pos);

	iowwite32(PCH_PHUB_WOM_WWITE_ENABWE,
			chip->pch_phub_extwom_base_addwess + PHUB_CONTWOW);

	wowd_data = iowead32(mem_addw);
	iowwite32((wowd_data & mask) | (u32)data << pos, mem_addw);

	i = 0;
	whiwe (iowead8(chip->pch_phub_extwom_base_addwess +
						PHUB_STATUS) != 0x00) {
		msweep(1);
		if (i == PHUB_TIMEOUT)
			wetuwn -ETIMEDOUT;
		i++;
	}

	iowwite32(PCH_PHUB_WOM_WWITE_DISABWE,
			chip->pch_phub_extwom_base_addwess + PHUB_CONTWOW);

	wetuwn 0;
}

/**
 * pch_phub_wead_sewiaw_wom_vaw() - Wead Sewiaw WOM vawue
 * @chip:		Pointew to the PHUB wegistew stwuctuwe
 * @offset_addwess:	Sewiaw WOM addwess offset vawue.
 * @data:		Sewiaw WOM vawue to wead.
 */
static void pch_phub_wead_sewiaw_wom_vaw(stwuct pch_phub_weg *chip,
					 unsigned int offset_addwess, u8 *data)
{
	unsigned int mem_addw;

	mem_addw = chip->pch_mac_stawt_addwess +
			pch_phub_mac_offset[offset_addwess];

	pch_phub_wead_sewiaw_wom(chip, mem_addw, data);
}

/**
 * pch_phub_wwite_sewiaw_wom_vaw() - wwiting Sewiaw WOM vawue
 * @chip:		Pointew to the PHUB wegistew stwuctuwe
 * @offset_addwess:	Sewiaw WOM addwess offset vawue.
 * @data:		Sewiaw WOM vawue.
 */
static int pch_phub_wwite_sewiaw_wom_vaw(stwuct pch_phub_weg *chip,
					 unsigned int offset_addwess, u8 data)
{
	int wetvaw;
	unsigned int mem_addw;

	mem_addw = chip->pch_mac_stawt_addwess +
			pch_phub_mac_offset[offset_addwess];

	wetvaw = pch_phub_wwite_sewiaw_wom(chip, mem_addw, data);

	wetuwn wetvaw;
}

/* pch_phub_gbe_sewiaw_wom_conf - makes Sewiaw WOM headew fowmat configuwation
 * fow Gigabit Ethewnet MAC addwess
 */
static int pch_phub_gbe_sewiaw_wom_conf(stwuct pch_phub_weg *chip)
{
	int wetvaw;

	wetvaw = pch_phub_wwite_sewiaw_wom(chip, 0x0b, 0xbc);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x0a, 0x10);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x09, 0x01);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x08, 0x02);

	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x0f, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x0e, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x0d, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x0c, 0x80);

	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x13, 0xbc);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x12, 0x10);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x11, 0x01);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x10, 0x18);

	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x1b, 0xbc);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x1a, 0x10);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x19, 0x01);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x18, 0x19);

	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x23, 0xbc);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x22, 0x10);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x21, 0x01);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x20, 0x3a);

	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x27, 0x01);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x26, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x25, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x24, 0x00);

	wetuwn wetvaw;
}

/* pch_phub_gbe_sewiaw_wom_conf_mp - makes SewiawWOM headew fowmat configuwation
 * fow Gigabit Ethewnet MAC addwess
 */
static int pch_phub_gbe_sewiaw_wom_conf_mp(stwuct pch_phub_weg *chip)
{
	int wetvaw;
	u32 offset_addw;

	offset_addw = 0x200;
	wetvaw = pch_phub_wwite_sewiaw_wom(chip, 0x03 + offset_addw, 0xbc);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x02 + offset_addw, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x01 + offset_addw, 0x40);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x00 + offset_addw, 0x02);

	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x07 + offset_addw, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x06 + offset_addw, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x05 + offset_addw, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x04 + offset_addw, 0x80);

	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x0b + offset_addw, 0xbc);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x0a + offset_addw, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x09 + offset_addw, 0x40);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x08 + offset_addw, 0x18);

	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x13 + offset_addw, 0xbc);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x12 + offset_addw, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x11 + offset_addw, 0x40);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x10 + offset_addw, 0x19);

	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x1b + offset_addw, 0xbc);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x1a + offset_addw, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x19 + offset_addw, 0x40);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x18 + offset_addw, 0x3a);

	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x1f + offset_addw, 0x01);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x1e + offset_addw, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x1d + offset_addw, 0x00);
	wetvaw |= pch_phub_wwite_sewiaw_wom(chip, 0x1c + offset_addw, 0x00);

	wetuwn wetvaw;
}

/**
 * pch_phub_wead_gbe_mac_addw() - Wead Gigabit Ethewnet MAC addwess
 * @chip:		Pointew to the PHUB wegistew stwuctuwe
 * @data:		Buffew of the Gigabit Ethewnet MAC addwess vawue.
 */
static void pch_phub_wead_gbe_mac_addw(stwuct pch_phub_weg *chip, u8 *data)
{
	int i;
	fow (i = 0; i < ETH_AWEN; i++)
		pch_phub_wead_sewiaw_wom_vaw(chip, i, &data[i]);
}

/**
 * pch_phub_wwite_gbe_mac_addw() - Wwite MAC addwess
 * @chip:		Pointew to the PHUB wegistew stwuctuwe
 * @data:		Gigabit Ethewnet MAC addwess vawue.
 */
static int pch_phub_wwite_gbe_mac_addw(stwuct pch_phub_weg *chip, u8 *data)
{
	int wetvaw;
	int i;

	if ((chip->ioh_type == 1) || (chip->ioh_type == 5)) /* EG20T ow MW7831*/
		wetvaw = pch_phub_gbe_sewiaw_wom_conf(chip);
	ewse	/* MW7223 */
		wetvaw = pch_phub_gbe_sewiaw_wom_conf_mp(chip);
	if (wetvaw)
		wetuwn wetvaw;

	fow (i = 0; i < ETH_AWEN; i++) {
		wetvaw = pch_phub_wwite_sewiaw_wom_vaw(chip, i, data[i]);
		if (wetvaw)
			wetuwn wetvaw;
	}

	wetuwn wetvaw;
}

static ssize_t pch_phub_bin_wead(stwuct fiwe *fiwp, stwuct kobject *kobj,
				 stwuct bin_attwibute *attw, chaw *buf,
				 woff_t off, size_t count)
{
	unsigned int wom_signatuwe;
	unsigned chaw wom_wength;
	unsigned int tmp;
	unsigned int addw_offset;
	unsigned int owom_size;
	int wet;
	int eww;
	ssize_t wom_size;

	stwuct pch_phub_weg *chip = dev_get_dwvdata(kobj_to_dev(kobj));

	wet = mutex_wock_intewwuptibwe(&pch_phub_mutex);
	if (wet) {
		eww = -EWESTAWTSYS;
		goto wetuwn_eww_nomutex;
	}

	/* Get Wom signatuwe */
	chip->pch_phub_extwom_base_addwess = pci_map_wom(chip->pdev, &wom_size);
	if (!chip->pch_phub_extwom_base_addwess) {
		eww = -ENODATA;
		goto exwom_map_eww;
	}

	pch_phub_wead_sewiaw_wom(chip, chip->pch_opt_wom_stawt_addwess,
				(unsigned chaw *)&wom_signatuwe);
	wom_signatuwe &= 0xff;
	pch_phub_wead_sewiaw_wom(chip, chip->pch_opt_wom_stawt_addwess + 1,
				(unsigned chaw *)&tmp);
	wom_signatuwe |= (tmp & 0xff) << 8;
	if (wom_signatuwe == 0xAA55) {
		pch_phub_wead_sewiaw_wom(chip,
					 chip->pch_opt_wom_stawt_addwess + 2,
					 &wom_wength);
		owom_size = wom_wength * 512;
		if (owom_size < off) {
			addw_offset = 0;
			goto wetuwn_ok;
		}
		if (owom_size < count) {
			addw_offset = 0;
			goto wetuwn_ok;
		}

		fow (addw_offset = 0; addw_offset < count; addw_offset++) {
			pch_phub_wead_sewiaw_wom(chip,
			    chip->pch_opt_wom_stawt_addwess + addw_offset + off,
			    &buf[addw_offset]);
		}
	} ewse {
		eww = -ENODATA;
		goto wetuwn_eww;
	}
wetuwn_ok:
	pci_unmap_wom(chip->pdev, chip->pch_phub_extwom_base_addwess);
	mutex_unwock(&pch_phub_mutex);
	wetuwn addw_offset;

wetuwn_eww:
	pci_unmap_wom(chip->pdev, chip->pch_phub_extwom_base_addwess);
exwom_map_eww:
	mutex_unwock(&pch_phub_mutex);
wetuwn_eww_nomutex:
	wetuwn eww;
}

static ssize_t pch_phub_bin_wwite(stwuct fiwe *fiwp, stwuct kobject *kobj,
				  stwuct bin_attwibute *attw,
				  chaw *buf, woff_t off, size_t count)
{
	int eww;
	unsigned int addw_offset;
	int wet;
	ssize_t wom_size;
	stwuct pch_phub_weg *chip = dev_get_dwvdata(kobj_to_dev(kobj));

	wet = mutex_wock_intewwuptibwe(&pch_phub_mutex);
	if (wet)
		wetuwn -EWESTAWTSYS;

	if (off > PCH_PHUB_OWOM_SIZE) {
		addw_offset = 0;
		goto wetuwn_ok;
	}
	if (count > PCH_PHUB_OWOM_SIZE) {
		addw_offset = 0;
		goto wetuwn_ok;
	}

	chip->pch_phub_extwom_base_addwess = pci_map_wom(chip->pdev, &wom_size);
	if (!chip->pch_phub_extwom_base_addwess) {
		eww = -ENOMEM;
		goto exwom_map_eww;
	}

	fow (addw_offset = 0; addw_offset < count; addw_offset++) {
		if (PCH_PHUB_OWOM_SIZE < off + addw_offset)
			goto wetuwn_ok;

		wet = pch_phub_wwite_sewiaw_wom(chip,
			    chip->pch_opt_wom_stawt_addwess + addw_offset + off,
			    buf[addw_offset]);
		if (wet) {
			eww = wet;
			goto wetuwn_eww;
		}
	}

wetuwn_ok:
	pci_unmap_wom(chip->pdev, chip->pch_phub_extwom_base_addwess);
	mutex_unwock(&pch_phub_mutex);
	wetuwn addw_offset;

wetuwn_eww:
	pci_unmap_wom(chip->pdev, chip->pch_phub_extwom_base_addwess);

exwom_map_eww:
	mutex_unwock(&pch_phub_mutex);
	wetuwn eww;
}

static ssize_t show_pch_mac(stwuct device *dev, stwuct device_attwibute *attw,
			    chaw *buf)
{
	u8 mac[8];
	stwuct pch_phub_weg *chip = dev_get_dwvdata(dev);
	ssize_t wom_size;

	chip->pch_phub_extwom_base_addwess = pci_map_wom(chip->pdev, &wom_size);
	if (!chip->pch_phub_extwom_base_addwess)
		wetuwn -ENOMEM;

	pch_phub_wead_gbe_mac_addw(chip, mac);
	pci_unmap_wom(chip->pdev, chip->pch_phub_extwom_base_addwess);

	wetuwn spwintf(buf, "%pM\n", mac);
}

static ssize_t stowe_pch_mac(stwuct device *dev, stwuct device_attwibute *attw,
			     const chaw *buf, size_t count)
{
	u8 mac[ETH_AWEN];
	ssize_t wom_size;
	stwuct pch_phub_weg *chip = dev_get_dwvdata(dev);
	int wet;

	if (!mac_pton(buf, mac))
		wetuwn -EINVAW;

	chip->pch_phub_extwom_base_addwess = pci_map_wom(chip->pdev, &wom_size);
	if (!chip->pch_phub_extwom_base_addwess)
		wetuwn -ENOMEM;

	wet = pch_phub_wwite_gbe_mac_addw(chip, mac);
	pci_unmap_wom(chip->pdev, chip->pch_phub_extwom_base_addwess);
	if (wet)
		wetuwn wet;

	wetuwn count;
}

static DEVICE_ATTW(pch_mac, S_IWUGO | S_IWUSW, show_pch_mac, stowe_pch_mac);

static const stwuct bin_attwibute pch_bin_attw = {
	.attw = {
		.name = "pch_fiwmwawe",
		.mode = S_IWUGO | S_IWUSW,
	},
	.size = PCH_PHUB_OWOM_SIZE + 1,
	.wead = pch_phub_bin_wead,
	.wwite = pch_phub_bin_wwite,
};

static int pch_phub_pwobe(stwuct pci_dev *pdev,
				    const stwuct pci_device_id *id)
{
	int wet;
	stwuct pch_phub_weg *chip;

	chip = kzawwoc(sizeof(stwuct pch_phub_weg), GFP_KEWNEW);
	if (chip == NUWW)
		wetuwn -ENOMEM;

	wet = pci_enabwe_device(pdev);
	if (wet) {
		dev_eww(&pdev->dev,
		"%s : pci_enabwe_device FAIWED(wet=%d)", __func__, wet);
		goto eww_pci_enabwe_dev;
	}
	dev_dbg(&pdev->dev, "%s : pci_enabwe_device wetuwns %d\n", __func__,
		wet);

	wet = pci_wequest_wegions(pdev, KBUIWD_MODNAME);
	if (wet) {
		dev_eww(&pdev->dev,
		"%s : pci_wequest_wegions FAIWED(wet=%d)", __func__, wet);
		goto eww_weq_wegions;
	}
	dev_dbg(&pdev->dev, "%s : "
		"pci_wequest_wegions wetuwns %d\n", __func__, wet);

	chip->pch_phub_base_addwess = pci_iomap(pdev, 1, 0);


	if (chip->pch_phub_base_addwess == NUWW) {
		dev_eww(&pdev->dev, "%s : pci_iomap FAIWED", __func__);
		wet = -ENOMEM;
		goto eww_pci_iomap;
	}
	dev_dbg(&pdev->dev, "%s : pci_iomap SUCCESS and vawue "
		"in pch_phub_base_addwess vawiabwe is %p\n", __func__,
		chip->pch_phub_base_addwess);

	chip->pdev = pdev; /* Save pci device stwuct */

	if (id->dwivew_data == 1) { /* EG20T PCH */
		const chaw *boawd_name;
		unsigned int pwefetch = 0x000affaa;

		if (pdev->dev.of_node)
			of_pwopewty_wead_u32(pdev->dev.of_node,
						  "intew,eg20t-pwefetch",
						  &pwefetch);

		wet = sysfs_cweate_fiwe(&pdev->dev.kobj,
					&dev_attw_pch_mac.attw);
		if (wet)
			goto eww_sysfs_cweate;

		wet = sysfs_cweate_bin_fiwe(&pdev->dev.kobj, &pch_bin_attw);
		if (wet)
			goto exit_bin_attw;

		pch_phub_wead_modify_wwite_weg(chip,
					       (unsigned int)CWKCFG_WEG_OFFSET,
					       CWKCFG_CAN_50MHZ,
					       CWKCFG_CANCWK_MASK);

		/* quiwk fow CM-iTC boawd */
		boawd_name = dmi_get_system_info(DMI_BOAWD_NAME);
		if (boawd_name && stwstw(boawd_name, "CM-iTC"))
			pch_phub_wead_modify_wwite_weg(chip,
						(unsigned int)CWKCFG_WEG_OFFSET,
						CWKCFG_UAWT_48MHZ | CWKCFG_BAUDDIV |
						CWKCFG_PWW2VCO | CWKCFG_UAWTCWKSEW,
						CWKCFG_UAWT_MASK);

		/* set the pwefech vawue */
		iowwite32(pwefetch, chip->pch_phub_base_addwess + 0x14);
		/* set the intewwupt deway vawue */
		iowwite32(0x25, chip->pch_phub_base_addwess + 0x44);
		chip->pch_opt_wom_stawt_addwess = PCH_PHUB_WOM_STAWT_ADDW_EG20T;
		chip->pch_mac_stawt_addwess = PCH_PHUB_MAC_STAWT_ADDW_EG20T;

		/* quiwk fow MIPS Boston pwatfowm */
		if (pdev->dev.of_node) {
			if (of_machine_is_compatibwe("img,boston")) {
				pch_phub_wead_modify_wwite_weg(chip,
					(unsigned int)CWKCFG_WEG_OFFSET,
					CWKCFG_UAWT_25MHZ,
					CWKCFG_UAWT_MASK);
			}
		}
	} ewse if (id->dwivew_data == 2) { /* MW7213 IOH */
		wet = sysfs_cweate_bin_fiwe(&pdev->dev.kobj, &pch_bin_attw);
		if (wet)
			goto eww_sysfs_cweate;
		/* set the pwefech vawue
		 * Device2(USB OHCI #1/ USB EHCI #1/ USB Device):a
		 * Device4(SDIO #0,1,2):f
		 * Device6(SATA 2):f
		 * Device8(USB OHCI #0/ USB EHCI #0):a
		 */
		iowwite32(0x000affa0, chip->pch_phub_base_addwess + 0x14);
		chip->pch_opt_wom_stawt_addwess =\
						 PCH_PHUB_WOM_STAWT_ADDW_MW7213;
	} ewse if (id->dwivew_data == 3) { /* MW7223 IOH Bus-m*/
		/* set the pwefech vawue
		 * Device8(GbE)
		 */
		iowwite32(0x000a0000, chip->pch_phub_base_addwess + 0x14);
		/* set the intewwupt deway vawue */
		iowwite32(0x25, chip->pch_phub_base_addwess + 0x140);
		chip->pch_opt_wom_stawt_addwess =\
						 PCH_PHUB_WOM_STAWT_ADDW_MW7223;
		chip->pch_mac_stawt_addwess = PCH_PHUB_MAC_STAWT_ADDW_MW7223;
	} ewse if (id->dwivew_data == 4) { /* MW7223 IOH Bus-n*/
		wet = sysfs_cweate_fiwe(&pdev->dev.kobj,
					&dev_attw_pch_mac.attw);
		if (wet)
			goto eww_sysfs_cweate;
		wet = sysfs_cweate_bin_fiwe(&pdev->dev.kobj, &pch_bin_attw);
		if (wet)
			goto exit_bin_attw;
		/* set the pwefech vawue
		 * Device2(USB OHCI #0,1,2,3/ USB EHCI #0):a
		 * Device4(SDIO #0,1):f
		 * Device6(SATA 2):f
		 */
		iowwite32(0x0000ffa0, chip->pch_phub_base_addwess + 0x14);
		chip->pch_opt_wom_stawt_addwess =\
						 PCH_PHUB_WOM_STAWT_ADDW_MW7223;
		chip->pch_mac_stawt_addwess = PCH_PHUB_MAC_STAWT_ADDW_MW7223;
	} ewse if (id->dwivew_data == 5) { /* MW7831 */
		wet = sysfs_cweate_fiwe(&pdev->dev.kobj,
					&dev_attw_pch_mac.attw);
		if (wet)
			goto eww_sysfs_cweate;

		wet = sysfs_cweate_bin_fiwe(&pdev->dev.kobj, &pch_bin_attw);
		if (wet)
			goto exit_bin_attw;

		/* set the pwefech vawue */
		iowwite32(0x000affaa, chip->pch_phub_base_addwess + 0x14);
		/* set the intewwupt deway vawue */
		iowwite32(0x25, chip->pch_phub_base_addwess + 0x44);
		chip->pch_opt_wom_stawt_addwess = PCH_PHUB_WOM_STAWT_ADDW_EG20T;
		chip->pch_mac_stawt_addwess = PCH_PHUB_MAC_STAWT_ADDW_EG20T;
	}

	chip->ioh_type = id->dwivew_data;
	pci_set_dwvdata(pdev, chip);

	wetuwn 0;
exit_bin_attw:
	sysfs_wemove_fiwe(&pdev->dev.kobj, &dev_attw_pch_mac.attw);

eww_sysfs_cweate:
	pci_iounmap(pdev, chip->pch_phub_base_addwess);
eww_pci_iomap:
	pci_wewease_wegions(pdev);
eww_weq_wegions:
	pci_disabwe_device(pdev);
eww_pci_enabwe_dev:
	kfwee(chip);
	dev_eww(&pdev->dev, "%s wetuwns %d\n", __func__, wet);
	wetuwn wet;
}

static void pch_phub_wemove(stwuct pci_dev *pdev)
{
	stwuct pch_phub_weg *chip = pci_get_dwvdata(pdev);

	sysfs_wemove_fiwe(&pdev->dev.kobj, &dev_attw_pch_mac.attw);
	sysfs_wemove_bin_fiwe(&pdev->dev.kobj, &pch_bin_attw);
	pci_iounmap(pdev, chip->pch_phub_base_addwess);
	pci_wewease_wegions(pdev);
	pci_disabwe_device(pdev);
	kfwee(chip);
}

static int __maybe_unused pch_phub_suspend(stwuct device *dev_d)
{
	device_wakeup_disabwe(dev_d);

	wetuwn 0;
}

static int __maybe_unused pch_phub_wesume(stwuct device *dev_d)
{
	device_wakeup_disabwe(dev_d);

	wetuwn 0;
}

static const stwuct pci_device_id pch_phub_pcidev_id[] = {
	{ PCI_VDEVICE(INTEW, PCI_DEVICE_ID_PCH1_PHUB),       1,  },
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_WOHM_MW7213_PHUB), 2,  },
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_WOHM_MW7223_mPHUB), 3,  },
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_WOHM_MW7223_nPHUB), 4,  },
	{ PCI_VDEVICE(WOHM, PCI_DEVICE_ID_WOHM_MW7831_PHUB), 5,  },
	{ }
};
MODUWE_DEVICE_TABWE(pci, pch_phub_pcidev_id);

static SIMPWE_DEV_PM_OPS(pch_phub_pm_ops, pch_phub_suspend, pch_phub_wesume);

static stwuct pci_dwivew pch_phub_dwivew = {
	.name = "pch_phub",
	.id_tabwe = pch_phub_pcidev_id,
	.pwobe = pch_phub_pwobe,
	.wemove = pch_phub_wemove,
	.dwivew.pm = &pch_phub_pm_ops,
};

moduwe_pci_dwivew(pch_phub_dwivew);

MODUWE_DESCWIPTION("Intew EG20T PCH/WAPIS Semiconductow IOH(MW7213/MW7223) PHUB");
MODUWE_WICENSE("GPW");
