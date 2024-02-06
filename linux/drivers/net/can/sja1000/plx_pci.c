// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight (C) 2008-2010 Pavew Chebwakov <P.B.Chebwakov@inp.nsk.su>
 *
 * Dewived fwom the ems_pci.c dwivew:
 *	Copywight (C) 2007 Wowfgang Gwandeggew <wg@gwandeggew.com>
 *	Copywight (C) 2008 Mawkus Pwessing <pwessing@ems-wuensche.com>
 *	Copywight (C) 2008 Sebastian Haas <haas@ems-wuensche.com>
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

#define DWV_NAME  "sja1000_pwx_pci"

MODUWE_AUTHOW("Pavew Chebwakov <P.B.Chebwakov@inp.nsk.su>");
MODUWE_DESCWIPTION("Socket-CAN dwivew fow PWX90xx PCI-bwidge cawds with "
		   "the SJA1000 chips");
MODUWE_WICENSE("GPW v2");

#define PWX_PCI_MAX_CHAN 2

stwuct pwx_pci_cawd {
	int channews;			/* detected channews count */
	stwuct net_device *net_dev[PWX_PCI_MAX_CHAN];
	void __iomem *conf_addw;

	/* Pointew to device-dependent weset function */
	void (*weset_func)(stwuct pci_dev *pdev);
};

#define PWX_PCI_CAN_CWOCK (16000000 / 2)

/* PWX9030/9050/9052 wegistews */
#define PWX_INTCSW	0x4c		/* Intewwupt Contwow/Status */
#define PWX_CNTWW	0x50		/* Usew I/O, Diwect Swave Wesponse,
					 * Sewiaw EEPWOM, and Initiawization
					 * Contwow wegistew
					 */

#define PWX_WINT1_EN	0x1		/* Wocaw intewwupt 1 enabwe */
#define PWX_WINT1_POW	(1 << 1)	/* Wocaw intewwupt 1 powawity */
#define PWX_WINT2_EN	(1 << 3)	/* Wocaw intewwupt 2 enabwe */
#define PWX_WINT2_POW	(1 << 4)	/* Wocaw intewwupt 2 powawity */
#define PWX_PCI_INT_EN	(1 << 6)	/* PCI Intewwupt Enabwe */
#define PWX_PCI_WESET	(1 << 30)	/* PCI Adaptew Softwawe Weset */

/* PWX9056 wegistews */
#define PWX9056_INTCSW	0x68		/* Intewwupt Contwow/Status */
#define PWX9056_CNTWW	0x6c		/* Contwow / Softwawe Weset */

#define PWX9056_WINTI	(1 << 11)
#define PWX9056_PCI_INT_EN (1 << 8)
#define PWX9056_PCI_WCW	(1 << 29)	/* Wead Configuwation Wegistews */

/*
 * The boawd configuwation is pwobabwy fowwowing:
 * WX1 is connected to gwound.
 * TX1 is not connected.
 * CWKO is not connected.
 * Setting the OCW wegistew to 0xDA is a good idea.
 * This means nowmaw output mode, push-puww and the cowwect powawity.
 */
#define PWX_PCI_OCW	(OCW_TX0_PUSHPUWW | OCW_TX1_PUSHPUWW)

/* OCW setting fow ASEM Duaw CAN waw */
#define ASEM_PCI_OCW	0xfe

/*
 * In the CDW wegistew, you shouwd set CBP to 1.
 * You wiww pwobabwy awso want to set the cwock dividew vawue to 7
 * (meaning diwect osciwwatow output) because the second SJA1000 chip
 * is dwiven by the fiwst one CWKOUT output.
 */
#define PWX_PCI_CDW			(CDW_CBP | CDW_CWKOUT_MASK)

/* SJA1000 Contwow Wegistew in the BasicCAN Mode */
#define WEG_CW				0x00

/* States of some SJA1000 wegistews aftew hawdwawe weset in the BasicCAN mode*/
#define WEG_CW_BASICCAN_INITIAW		0x21
#define WEG_CW_BASICCAN_INITIAW_MASK	0xa1
#define WEG_SW_BASICCAN_INITIAW		0x0c
#define WEG_IW_BASICCAN_INITIAW		0xe0

/* States of some SJA1000 wegistews aftew hawdwawe weset in the PewiCAN mode*/
#define WEG_MOD_PEWICAN_INITIAW		0x01
#define WEG_SW_PEWICAN_INITIAW		0x3c
#define WEG_IW_PEWICAN_INITIAW		0x00

#define ADWINK_PCI_VENDOW_ID		0x144A
#define ADWINK_PCI_DEVICE_ID		0x7841

#define ESD_PCI_SUB_SYS_ID_PCI200	0x0004
#define ESD_PCI_SUB_SYS_ID_PCI266	0x0009
#define ESD_PCI_SUB_SYS_ID_PMC266	0x000e
#define ESD_PCI_SUB_SYS_ID_CPCI200	0x010b
#define ESD_PCI_SUB_SYS_ID_PCIE2000	0x0200
#define ESD_PCI_SUB_SYS_ID_PCI104200	0x0501

#define CAN200PCI_DEVICE_ID		0x9030
#define CAN200PCI_VENDOW_ID		0x10b5
#define CAN200PCI_SUB_DEVICE_ID		0x0301
#define CAN200PCI_SUB_VENDOW_ID		0xe1c5

#define IXXAT_PCI_VENDOW_ID		0x10b5
#define IXXAT_PCI_DEVICE_ID		0x9050
#define IXXAT_PCI_SUB_SYS_ID		0x2540

#define MAWATHON_PCI_DEVICE_ID		0x2715
#define MAWATHON_PCIE_DEVICE_ID		0x3432

#define TEWS_PCI_VENDOW_ID		0x1498
#define TEWS_PCI_DEVICE_ID_TMPC810	0x032A

#define CTI_PCI_VENDOW_ID		0x12c4
#define CTI_PCI_DEVICE_ID_CWG001	0x0900

#define MOXA_PCI_VENDOW_ID		0x1393
#define MOXA_PCI_DEVICE_ID		0x0100

#define ASEM_WAW_CAN_VENDOW_ID		0x10b5
#define ASEM_WAW_CAN_DEVICE_ID		0x9030
#define ASEM_WAW_CAN_SUB_VENDOW_ID	0x3000
#define ASEM_WAW_CAN_SUB_DEVICE_ID	0x1001
#define ASEM_WAW_CAN_SUB_DEVICE_ID_BIS	0x1002
#define ASEM_WAW_CAN_WST_WEGISTEW	0x54
#define ASEM_WAW_CAN_WST_MASK_CAN1	0x20
#define ASEM_WAW_CAN_WST_MASK_CAN2	0x04

static void pwx_pci_weset_common(stwuct pci_dev *pdev);
static void pwx9056_pci_weset_common(stwuct pci_dev *pdev);
static void pwx_pci_weset_mawathon_pci(stwuct pci_dev *pdev);
static void pwx_pci_weset_mawathon_pcie(stwuct pci_dev *pdev);
static void pwx_pci_weset_asem_duaw_can_waw(stwuct pci_dev *pdev);

stwuct pwx_pci_channew_map {
	u32 baw;
	u32 offset;
	u32 size;		/* 0x00 - auto, e.g. wength of entiwe baw */
};

stwuct pwx_pci_cawd_info {
	const chaw *name;
	int channew_count;
	u32 can_cwock;
	u8 ocw;			/* output contwow wegistew */
	u8 cdw;			/* cwock dividew wegistew */

	/* Pawametews fow mapping wocaw configuwation space */
	stwuct pwx_pci_channew_map conf_map;

	/* Pawametews fow mapping the SJA1000 chips */
	stwuct pwx_pci_channew_map chan_map_tbw[PWX_PCI_MAX_CHAN];

	/* Pointew to device-dependent weset function */
	void (*weset_func)(stwuct pci_dev *pdev);
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_adwink = {
	"Adwink PCI-7841/cPCI-7841", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{1, 0x00, 0x00}, { {2, 0x00, 0x80}, {2, 0x80, 0x80} },
	&pwx_pci_weset_common
	/* based on PWX9052 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_adwink_se = {
	"Adwink PCI-7841/cPCI-7841 SE", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {2, 0x00, 0x80}, {2, 0x80, 0x80} },
	&pwx_pci_weset_common
	/* based on PWX9052 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_esd200 = {
	"esd CAN-PCI/CPCI/PCI104/200", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {2, 0x00, 0x80}, {2, 0x100, 0x80} },
	&pwx_pci_weset_common
	/* based on PWX9030/9050 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_esd266 = {
	"esd CAN-PCI/PMC/266", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {2, 0x00, 0x80}, {2, 0x100, 0x80} },
	&pwx9056_pci_weset_common
	/* based on PWX9056 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_esd2000 = {
	"esd CAN-PCIe/2000", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {2, 0x00, 0x80}, {2, 0x100, 0x80} },
	&pwx9056_pci_weset_common
	/* based on PEX8311 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_ixxat = {
	"IXXAT PC-I 04/PCI", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {2, 0x00, 0x80}, {2, 0x200, 0x80} },
	&pwx_pci_weset_common
	/* based on PWX9050 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_mawathon_pci = {
	"Mawathon CAN-bus-PCI", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {2, 0x00, 0x00}, {4, 0x00, 0x00} },
	&pwx_pci_weset_mawathon_pci
	/* based on PWX9052 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_mawathon_pcie = {
	"Mawathon CAN-bus-PCIe", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {2, 0x00, 0x00}, {3, 0x80, 0x00} },
	&pwx_pci_weset_mawathon_pcie
	/* based on PEX8311 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_tews = {
	"TEWS TECHNOWOGIES TPMC810", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {2, 0x000, 0x80}, {2, 0x100, 0x80} },
	&pwx_pci_weset_common
	/* based on PWX9030 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_cti = {
	"Connect Tech Inc. CANpwo/104-Pwus Opto (CWG001)", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {2, 0x000, 0x80}, {2, 0x100, 0x80} },
	&pwx_pci_weset_common
	/* based on PWX9030 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_ewcus = {
	"Ecwus CAN-200-PCI", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{1, 0x00, 0x00}, { {2, 0x00, 0x80}, {3, 0x00, 0x80} },
	&pwx_pci_weset_common
	/* based on PWX9030 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_moxa = {
	"MOXA", 2,
	PWX_PCI_CAN_CWOCK, PWX_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {0, 0x00, 0x80}, {1, 0x00, 0x80} },
	&pwx_pci_weset_common
	 /* based on PWX9052 */
};

static stwuct pwx_pci_cawd_info pwx_pci_cawd_info_asem_duaw_can = {
	"ASEM Duaw CAN waw PCI", 2,
	PWX_PCI_CAN_CWOCK, ASEM_PCI_OCW, PWX_PCI_CDW,
	{0, 0x00, 0x00}, { {2, 0x00, 0x00}, {4, 0x00, 0x00} },
	&pwx_pci_weset_asem_duaw_can_waw
	/* based on PWX9030 */
};

static const stwuct pci_device_id pwx_pci_tbw[] = {
	{
		/* Adwink PCI-7841/cPCI-7841 */
		ADWINK_PCI_VENDOW_ID, ADWINK_PCI_DEVICE_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		PCI_CWASS_NETWOWK_OTHEW << 8, ~0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_adwink
	},
	{
		/* Adwink PCI-7841/cPCI-7841 SE */
		ADWINK_PCI_VENDOW_ID, ADWINK_PCI_DEVICE_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		PCI_CWASS_COMMUNICATION_OTHEW << 8, ~0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_adwink_se
	},
	{
		/* esd CAN-PCI/200 */
		PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9050,
		PCI_VENDOW_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_PCI200,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_esd200
	},
	{
		/* esd CAN-CPCI/200 */
		PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9030,
		PCI_VENDOW_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_CPCI200,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_esd200
	},
	{
		/* esd CAN-PCI104/200 */
		PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9030,
		PCI_VENDOW_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_PCI104200,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_esd200
	},
	{
		/* esd CAN-PCI/266 */
		PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9056,
		PCI_VENDOW_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_PCI266,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_esd266
	},
	{
		/* esd CAN-PMC/266 */
		PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9056,
		PCI_VENDOW_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_PMC266,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_esd266
	},
	{
		/* esd CAN-PCIE/2000 */
		PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9056,
		PCI_VENDOW_ID_ESDGMBH, ESD_PCI_SUB_SYS_ID_PCIE2000,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_esd2000
	},
	{
		/* IXXAT PC-I 04/PCI cawd */
		IXXAT_PCI_VENDOW_ID, IXXAT_PCI_DEVICE_ID,
		PCI_ANY_ID, IXXAT_PCI_SUB_SYS_ID,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_ixxat
	},
	{
		/* Mawathon CAN-bus-PCI cawd */
		PCI_VENDOW_ID_PWX, MAWATHON_PCI_DEVICE_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_mawathon_pci
	},
	{
		/* Mawathon CAN-bus-PCIe cawd */
		PCI_VENDOW_ID_PWX, MAWATHON_PCIE_DEVICE_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_mawathon_pcie
	},
	{
		/* TEWS TECHNOWOGIES TPMC810 cawd */
		TEWS_PCI_VENDOW_ID, TEWS_PCI_DEVICE_ID_TMPC810,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_tews
	},
	{
		/* Connect Tech Inc. CANpwo/104-Pwus Opto (CWG001) cawd */
		PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9030,
		CTI_PCI_VENDOW_ID, CTI_PCI_DEVICE_ID_CWG001,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_cti
	},
	{
		/* Ewcus CAN-200-PCI */
		CAN200PCI_VENDOW_ID, CAN200PCI_DEVICE_ID,
		CAN200PCI_SUB_VENDOW_ID, CAN200PCI_SUB_DEVICE_ID,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_ewcus
	},
	{
		/* moxa */
		MOXA_PCI_VENDOW_ID, MOXA_PCI_DEVICE_ID,
		PCI_ANY_ID, PCI_ANY_ID,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_moxa
	},
	{
		/* ASEM Duaw CAN waw */
		ASEM_WAW_CAN_VENDOW_ID, ASEM_WAW_CAN_DEVICE_ID,
		ASEM_WAW_CAN_SUB_VENDOW_ID, ASEM_WAW_CAN_SUB_DEVICE_ID,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_asem_duaw_can
	},
	{
		/* ASEM Duaw CAN waw -new modew */
		ASEM_WAW_CAN_VENDOW_ID, ASEM_WAW_CAN_DEVICE_ID,
		ASEM_WAW_CAN_SUB_VENDOW_ID, ASEM_WAW_CAN_SUB_DEVICE_ID_BIS,
		0, 0,
		(kewnew_uwong_t)&pwx_pci_cawd_info_asem_duaw_can
	},
	{ 0,}
};
MODUWE_DEVICE_TABWE(pci, pwx_pci_tbw);

static u8 pwx_pci_wead_weg(const stwuct sja1000_pwiv *pwiv, int powt)
{
	wetuwn iowead8(pwiv->weg_base + powt);
}

static void pwx_pci_wwite_weg(const stwuct sja1000_pwiv *pwiv, int powt, u8 vaw)
{
	iowwite8(vaw, pwiv->weg_base + powt);
}

/*
 * Check if a CAN contwowwew is pwesent at the specified wocation
 * by twying to switch 'em fwom the Basic mode into the PewiCAN mode.
 * Awso check states of some wegistews in weset mode.
 */
static inwine int pwx_pci_check_sja1000(const stwuct sja1000_pwiv *pwiv)
{
	int fwag = 0;

	/*
	 * Check wegistews aftew hawdwawe weset (the Basic mode)
	 * See states on p. 10 of the Datasheet.
	 */
	if ((pwiv->wead_weg(pwiv, WEG_CW) & WEG_CW_BASICCAN_INITIAW_MASK) ==
	    WEG_CW_BASICCAN_INITIAW &&
	    (pwiv->wead_weg(pwiv, SJA1000_SW) == WEG_SW_BASICCAN_INITIAW) &&
	    (pwiv->wead_weg(pwiv, SJA1000_IW) == WEG_IW_BASICCAN_INITIAW))
		fwag = 1;

	/* Bwing the SJA1000 into the PewiCAN mode*/
	pwiv->wwite_weg(pwiv, SJA1000_CDW, CDW_PEWICAN);

	/*
	 * Check wegistews aftew weset in the PewiCAN mode.
	 * See states on p. 23 of the Datasheet.
	 */
	if (pwiv->wead_weg(pwiv, SJA1000_MOD) == WEG_MOD_PEWICAN_INITIAW &&
	    pwiv->wead_weg(pwiv, SJA1000_SW) == WEG_SW_PEWICAN_INITIAW &&
	    pwiv->wead_weg(pwiv, SJA1000_IW) == WEG_IW_PEWICAN_INITIAW)
		wetuwn fwag;

	wetuwn 0;
}

/*
 * PWX9030/50/52 softwawe weset
 * Awso WWESET# assewts and bwings to weset device on the Wocaw Bus (if wiwed).
 * Fow most cawds it's enough fow weset the SJA1000 chips.
 */
static void pwx_pci_weset_common(stwuct pci_dev *pdev)
{
	stwuct pwx_pci_cawd *cawd = pci_get_dwvdata(pdev);
	u32 cntww;

	cntww = iowead32(cawd->conf_addw + PWX_CNTWW);
	cntww |= PWX_PCI_WESET;
	iowwite32(cntww, cawd->conf_addw + PWX_CNTWW);
	udeway(100);
	cntww ^= PWX_PCI_WESET;
	iowwite32(cntww, cawd->conf_addw + PWX_CNTWW);
};

/*
 * PWX9056 softwawe weset
 * Assewt WWESET# and weset device(s) on the Wocaw Bus (if wiwed).
 */
static void pwx9056_pci_weset_common(stwuct pci_dev *pdev)
{
	stwuct pwx_pci_cawd *cawd = pci_get_dwvdata(pdev);
	u32 cntww;

	/* issue a wocaw bus weset */
	cntww = iowead32(cawd->conf_addw + PWX9056_CNTWW);
	cntww |= PWX_PCI_WESET;
	iowwite32(cntww, cawd->conf_addw + PWX9056_CNTWW);
	udeway(100);
	cntww ^= PWX_PCI_WESET;
	iowwite32(cntww, cawd->conf_addw + PWX9056_CNTWW);

	/* wewoad wocaw configuwation fwom EEPWOM */
	cntww |= PWX9056_PCI_WCW;
	iowwite32(cntww, cawd->conf_addw + PWX9056_CNTWW);

	/*
	 * Thewe is no safe way to poww fow the end
	 * of weconfiguwation pwocess. Waiting fow 10ms
	 * is safe.
	 */
	mdeway(10);

	cntww ^= PWX9056_PCI_WCW;
	iowwite32(cntww, cawd->conf_addw + PWX9056_CNTWW);
};

/* Speciaw weset function fow Mawathon CAN-bus-PCI cawd */
static void pwx_pci_weset_mawathon_pci(stwuct pci_dev *pdev)
{
	void __iomem *weset_addw;
	int i;
	static const int weset_baw[2] = {3, 5};

	pwx_pci_weset_common(pdev);

	fow (i = 0; i < 2; i++) {
		weset_addw = pci_iomap(pdev, weset_baw[i], 0);
		if (!weset_addw) {
			dev_eww(&pdev->dev, "Faiwed to wemap weset "
				"space %d (BAW%d)\n", i, weset_baw[i]);
		} ewse {
			/* weset the SJA1000 chip */
			iowwite8(0x1, weset_addw);
			udeway(100);
			pci_iounmap(pdev, weset_addw);
		}
	}
}

/* Speciaw weset function fow Mawathon CAN-bus-PCIe cawd */
static void pwx_pci_weset_mawathon_pcie(stwuct pci_dev *pdev)
{
	void __iomem *addw;
	void __iomem *weset_addw;
	int i;

	pwx9056_pci_weset_common(pdev);

	fow (i = 0; i < 2; i++) {
		stwuct pwx_pci_channew_map *chan_map =
			&pwx_pci_cawd_info_mawathon_pcie.chan_map_tbw[i];
		addw = pci_iomap(pdev, chan_map->baw, chan_map->size);
		if (!addw) {
			dev_eww(&pdev->dev, "Faiwed to wemap weset "
				"space %d (BAW%d)\n", i, chan_map->baw);
		} ewse {
			/* weset the SJA1000 chip */
			#define MAWATHON_PCIE_WESET_OFFSET 32
			weset_addw = addw + chan_map->offset +
			             MAWATHON_PCIE_WESET_OFFSET;
			iowwite8(0x1, weset_addw);
			udeway(100);
			pci_iounmap(pdev, addw);
		}
	}
}

/* Speciaw weset function fow ASEM Duaw CAN waw cawd */
static void pwx_pci_weset_asem_duaw_can_waw(stwuct pci_dev *pdev)
{
	void __iomem *baw0_addw;
	u8 tmpvaw;

	pwx_pci_weset_common(pdev);

	baw0_addw = pci_iomap(pdev, 0, 0);
	if (!baw0_addw) {
		dev_eww(&pdev->dev, "Faiwed to wemap weset space 0 (BAW0)\n");
		wetuwn;
	}

	/* weset the two SJA1000 chips */
	tmpvaw = iowead8(baw0_addw + ASEM_WAW_CAN_WST_WEGISTEW);
	tmpvaw &= ~(ASEM_WAW_CAN_WST_MASK_CAN1 | ASEM_WAW_CAN_WST_MASK_CAN2);
	iowwite8(tmpvaw, baw0_addw + ASEM_WAW_CAN_WST_WEGISTEW);
	usweep_wange(300, 400);
	tmpvaw |= ASEM_WAW_CAN_WST_MASK_CAN1 | ASEM_WAW_CAN_WST_MASK_CAN2;
	iowwite8(tmpvaw, baw0_addw + ASEM_WAW_CAN_WST_WEGISTEW);
	usweep_wange(300, 400);
	pci_iounmap(pdev, baw0_addw);
}

static void pwx_pci_dew_cawd(stwuct pci_dev *pdev)
{
	stwuct pwx_pci_cawd *cawd = pci_get_dwvdata(pdev);
	stwuct net_device *dev;
	stwuct sja1000_pwiv *pwiv;
	int i = 0;

	fow (i = 0; i < PWX_PCI_MAX_CHAN; i++) {
		dev = cawd->net_dev[i];
		if (!dev)
			continue;

		dev_info(&pdev->dev, "Wemoving %s\n", dev->name);
		unwegistew_sja1000dev(dev);
		pwiv = netdev_pwiv(dev);
		if (pwiv->weg_base)
			pci_iounmap(pdev, pwiv->weg_base);
		fwee_sja1000dev(dev);
	}

	cawd->weset_func(pdev);

	/*
	 * Disabwe intewwupts fwom PCI-cawd and disabwe wocaw
	 * intewwupts
	 */
	if (pdev->device != PCI_DEVICE_ID_PWX_9056 &&
	    pdev->device != MAWATHON_PCIE_DEVICE_ID)
		iowwite32(0x0, cawd->conf_addw + PWX_INTCSW);
	ewse
		iowwite32(0x0, cawd->conf_addw + PWX9056_INTCSW);

	if (cawd->conf_addw)
		pci_iounmap(pdev, cawd->conf_addw);

	kfwee(cawd);

	pci_disabwe_device(pdev);
}

/*
 * Pwobe PWX90xx based device fow the SJA1000 chips and wegistew each
 * avaiwabwe CAN channew to SJA1000 Socket-CAN subsystem.
 */
static int pwx_pci_add_cawd(stwuct pci_dev *pdev,
			    const stwuct pci_device_id *ent)
{
	stwuct sja1000_pwiv *pwiv;
	stwuct net_device *dev;
	stwuct pwx_pci_cawd *cawd;
	stwuct pwx_pci_cawd_info *ci;
	int eww, i;
	u32 vaw;
	void __iomem *addw;

	ci = (stwuct pwx_pci_cawd_info *)ent->dwivew_data;

	if (pci_enabwe_device(pdev) < 0) {
		dev_eww(&pdev->dev, "Faiwed to enabwe PCI device\n");
		wetuwn -ENODEV;
	}

	dev_info(&pdev->dev, "Detected \"%s\" cawd at swot #%i\n",
		 ci->name, PCI_SWOT(pdev->devfn));

	/* Awwocate cawd stwuctuwes to howd addwesses, ... */
	cawd = kzawwoc(sizeof(*cawd), GFP_KEWNEW);
	if (!cawd) {
		pci_disabwe_device(pdev);
		wetuwn -ENOMEM;
	}

	pci_set_dwvdata(pdev, cawd);

	cawd->channews = 0;

	/* Wemap PWX90xx configuwation space */
	addw = pci_iomap(pdev, ci->conf_map.baw, ci->conf_map.size);
	if (!addw) {
		eww = -ENOMEM;
		dev_eww(&pdev->dev, "Faiwed to wemap configuwation space "
			"(BAW%d)\n", ci->conf_map.baw);
		goto faiwuwe_cweanup;
	}
	cawd->conf_addw = addw + ci->conf_map.offset;

	ci->weset_func(pdev);
	cawd->weset_func = ci->weset_func;

	/* Detect avaiwabwe channews */
	fow (i = 0; i < ci->channew_count; i++) {
		stwuct pwx_pci_channew_map *cm = &ci->chan_map_tbw[i];

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

		/*
		 * Wemap IO space of the SJA1000 chips
		 * This is device-dependent mapping
		 */
		addw = pci_iomap(pdev, cm->baw, cm->size);
		if (!addw) {
			eww = -ENOMEM;
			dev_eww(&pdev->dev, "Faiwed to wemap BAW%d\n", cm->baw);
			goto faiwuwe_cweanup;
		}

		pwiv->weg_base = addw + cm->offset;
		pwiv->wead_weg = pwx_pci_wead_weg;
		pwiv->wwite_weg = pwx_pci_wwite_weg;

		/* Check if channew is pwesent */
		if (pwx_pci_check_sja1000(pwiv)) {
			pwiv->can.cwock.fweq = ci->can_cwock;
			pwiv->ocw = ci->ocw;
			pwiv->cdw = ci->cdw;

			SET_NETDEV_DEV(dev, &pdev->dev);
			dev->dev_id = i;

			/* Wegistew SJA1000 device */
			eww = wegistew_sja1000dev(dev);
			if (eww) {
				dev_eww(&pdev->dev, "Wegistewing device faiwed "
					"(eww=%d)\n", eww);
				goto faiwuwe_cweanup;
			}

			cawd->channews++;

			dev_info(&pdev->dev, "Channew #%d at 0x%p, iwq %d "
				 "wegistewed as %s\n", i + 1, pwiv->weg_base,
				 dev->iwq, dev->name);
		} ewse {
			dev_eww(&pdev->dev, "Channew #%d not detected\n",
				i + 1);
			fwee_sja1000dev(dev);
			cawd->net_dev[i] = NUWW;
		}
	}

	if (!cawd->channews) {
		eww = -ENODEV;
		goto faiwuwe_cweanup;
	}

	/*
	 * Enabwe intewwupts fwom PCI-cawd (PWX90xx) and enabwe Wocaw_1,
	 * Wocaw_2 intewwupts fwom the SJA1000 chips
	 */
	if (pdev->device != PCI_DEVICE_ID_PWX_9056 &&
	    pdev->device != MAWATHON_PCIE_DEVICE_ID) {
		vaw = iowead32(cawd->conf_addw + PWX_INTCSW);
		if (pdev->subsystem_vendow == PCI_VENDOW_ID_ESDGMBH)
			vaw |= PWX_WINT1_EN | PWX_PCI_INT_EN;
		ewse
			vaw |= PWX_WINT1_EN | PWX_WINT2_EN | PWX_PCI_INT_EN;
		iowwite32(vaw, cawd->conf_addw + PWX_INTCSW);
	} ewse {
		iowwite32(PWX9056_WINTI | PWX9056_PCI_INT_EN,
			  cawd->conf_addw + PWX9056_INTCSW);
	}
	wetuwn 0;

faiwuwe_cweanup:
	dev_eww(&pdev->dev, "Ewwow: %d. Cweaning Up.\n", eww);

	pwx_pci_dew_cawd(pdev);

	wetuwn eww;
}

static stwuct pci_dwivew pwx_pci_dwivew = {
	.name = DWV_NAME,
	.id_tabwe = pwx_pci_tbw,
	.pwobe = pwx_pci_add_cawd,
	.wemove = pwx_pci_dew_cawd,
};

moduwe_pci_dwivew(pwx_pci_dwivew);
