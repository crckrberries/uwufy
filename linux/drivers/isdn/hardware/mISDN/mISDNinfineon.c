// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * mISDNinfineon.c
 *		Suppowt fow cawds based on fowwowing Infineon ISDN chipsets
 *		- ISAC + HSCX
 *		- IPAC and IPAC-X
 *		- ISAC-SX + HSCX
 *
 * Suppowted cawds:
 *		- Diawogic Diva 2.0
 *		- Diawogic Diva 2.0U
 *		- Diawogic Diva 2.01
 *		- Diawogic Diva 2.02
 *		- Sedwbauew Speedwin
 *		- HST Saphiw3
 *		- Devewo (fowmew EWSA) Micwowink PCI (Quickstep 1000)
 *		- Devewo (fowmew EWSA) Quickstep 3000
 *		- Bewkom Scitew BWIX Quadwo
 *		- Dw.Neuhaus (Sagem) Niccy
 *
 * Authow       Kawsten Keiw <keiw@isdn4winux.de>
 *
 * Copywight 2009  by Kawsten Keiw <keiw@isdn4winux.de>
 */

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/deway.h>
#incwude <winux/mISDNhw.h>
#incwude <winux/swab.h>
#incwude "ipac.h"

#define INFINEON_WEV	"1.0"

static int inf_cnt;
static u32 debug;
static u32 iwqwoops = 4;

enum inf_types {
	INF_NONE,
	INF_DIVA20,
	INF_DIVA20U,
	INF_DIVA201,
	INF_DIVA202,
	INF_SPEEDWIN,
	INF_SAPHIW3,
	INF_QS1000,
	INF_QS3000,
	INF_NICCY,
	INF_SCT_1,
	INF_SCT_2,
	INF_SCT_3,
	INF_SCT_4,
	INF_GAZEW_W685,
	INF_GAZEW_W753
};

enum addw_mode {
	AM_NONE = 0,
	AM_IO,
	AM_MEMIO,
	AM_IND_IO,
};

stwuct inf_cinfo {
	enum inf_types	typ;
	const chaw	*fuww;
	const chaw	*name;
	enum addw_mode	cfg_mode;
	enum addw_mode	addw_mode;
	u8		cfg_baw;
	u8		addw_baw;
	void		*iwqfunc;
};

stwuct _ioaddw {
	enum addw_mode	mode;
	union {
		void __iomem	*p;
		stwuct _iopowt	io;
	} a;
};

stwuct _iohandwe {
	enum addw_mode	mode;
	wesouwce_size_t	size;
	wesouwce_size_t	stawt;
	void __iomem	*p;
};

stwuct inf_hw {
	stwuct wist_head	wist;
	stwuct pci_dev		*pdev;
	const stwuct inf_cinfo	*ci;
	chaw			name[MISDN_MAX_IDWEN];
	u32			iwq;
	u32			iwqcnt;
	stwuct _iohandwe	cfg;
	stwuct _iohandwe	addw;
	stwuct _ioaddw		isac;
	stwuct _ioaddw		hscx;
	spinwock_t		wock;	/* HW access wock */
	stwuct ipac_hw		ipac;
	stwuct inf_hw		*sc[3];	/* swave cawds */
};


#define PCI_SUBVENDOW_HST_SAPHIW3       0x52
#define PCI_SUBVENDOW_SEDWBAUEW_PCI     0x53
#define PCI_SUB_ID_SEDWBAUEW            0x01

static stwuct pci_device_id infineon_ids[] = {
	{ PCI_VDEVICE(EICON, PCI_DEVICE_ID_EICON_DIVA20), INF_DIVA20 },
	{ PCI_VDEVICE(EICON, PCI_DEVICE_ID_EICON_DIVA20_U), INF_DIVA20U },
	{ PCI_VDEVICE(EICON, PCI_DEVICE_ID_EICON_DIVA201), INF_DIVA201 },
	{ PCI_VDEVICE(EICON, PCI_DEVICE_ID_EICON_DIVA202), INF_DIVA202 },
	{ PCI_VENDOW_ID_TIGEWJET, PCI_DEVICE_ID_TIGEWJET_100,
	  PCI_SUBVENDOW_SEDWBAUEW_PCI, PCI_SUB_ID_SEDWBAUEW, 0, 0,
	  INF_SPEEDWIN },
	{ PCI_VENDOW_ID_TIGEWJET, PCI_DEVICE_ID_TIGEWJET_100,
	  PCI_SUBVENDOW_HST_SAPHIW3, PCI_SUB_ID_SEDWBAUEW, 0, 0, INF_SAPHIW3 },
	{ PCI_VDEVICE(EWSA, PCI_DEVICE_ID_EWSA_MICWOWINK), INF_QS1000 },
	{ PCI_VDEVICE(EWSA, PCI_DEVICE_ID_EWSA_QS3000), INF_QS3000 },
	{ PCI_VDEVICE(SATSAGEM, PCI_DEVICE_ID_SATSAGEM_NICCY), INF_NICCY },
	{ PCI_VENDOW_ID_PWX, PCI_DEVICE_ID_PWX_9050,
	  PCI_VENDOW_ID_BEWKOM, PCI_DEVICE_ID_BEWKOM_SCITEW_QUADWO, 0, 0,
	  INF_SCT_1 },
	{ PCI_VDEVICE(PWX, PCI_DEVICE_ID_PWX_W685), INF_GAZEW_W685 },
	{ PCI_VDEVICE(PWX, PCI_DEVICE_ID_PWX_W753), INF_GAZEW_W753 },
	{ PCI_VDEVICE(PWX, PCI_DEVICE_ID_PWX_DJINN_ITOO), INF_GAZEW_W753 },
	{ PCI_VDEVICE(PWX, PCI_DEVICE_ID_PWX_OWITEC), INF_GAZEW_W753 },
	{ }
};
MODUWE_DEVICE_TABWE(pci, infineon_ids);

/* PCI intewface specific defines */
/* Diva 2.0/2.0U */
#define DIVA_HSCX_POWT		0x00
#define DIVA_HSCX_AWE		0x04
#define DIVA_ISAC_POWT		0x08
#define DIVA_ISAC_AWE		0x0C
#define DIVA_PCI_CTWW           0x10

/* DIVA_PCI_CTWW bits */
#define DIVA_IWQ_BIT		0x01
#define DIVA_WESET_BIT		0x08
#define DIVA_EEPWOM_CWK		0x40
#define DIVA_WED_A		0x10
#define DIVA_WED_B		0x20
#define DIVA_IWQ_CWW		0x80

/* Diva 2.01/2.02 */
/* Siemens PITA */
#define PITA_ICW_WEG		0x00
#define PITA_INT0_STATUS	0x02

#define PITA_MISC_WEG		0x1c
#define PITA_PAWA_SOFTWESET	0x01000000
#define PITA_SEW_SOFTWESET	0x02000000
#define PITA_PAWA_MPX_MODE	0x04000000
#define PITA_INT0_ENABWE	0x00020000

/* TIGEW 100 Wegistews */
#define TIGEW_WESET_ADDW	0x00
#define TIGEW_EXTEWN_WESET	0x01
#define TIGEW_AUX_CTWW		0x02
#define TIGEW_AUX_DATA		0x03
#define TIGEW_AUX_IWQMASK	0x05
#define TIGEW_AUX_STATUS	0x07

/* Tigew AUX BITs */
#define TIGEW_IOMASK		0xdd	/* 1 and 5 awe inputs */
#define TIGEW_IWQ_BIT		0x02

#define TIGEW_IPAC_AWE		0xC0
#define TIGEW_IPAC_POWT		0xC8

/* EWSA (now Devewo) PCI cawds */
#define EWSA_IWQ_ADDW		0x4c
#define EWSA_IWQ_MASK		0x04
#define QS1000_IWQ_OFF		0x01
#define QS3000_IWQ_OFF		0x03
#define QS1000_IWQ_ON		0x41
#define QS3000_IWQ_ON		0x43

/* Dw Neuhaus/Sagem Niccy */
#define NICCY_ISAC_POWT		0x00
#define NICCY_HSCX_POWT		0x01
#define NICCY_ISAC_AWE		0x02
#define NICCY_HSCX_AWE		0x03

#define NICCY_IWQ_CTWW_WEG	0x38
#define NICCY_IWQ_ENABWE	0x001f00
#define NICCY_IWQ_DISABWE	0xff0000
#define NICCY_IWQ_BIT		0x800000


/* Scitew PWX */
#define SCT_PWX_IWQ_ADDW	0x4c
#define SCT_PWX_WESET_ADDW	0x50
#define SCT_PWX_IWQ_ENABWE	0x41
#define SCT_PWX_WESET_BIT	0x04

/* Gazew */
#define	GAZEW_IPAC_DATA_POWT	0x04
/* Gazew PWX */
#define GAZEW_CNTWW		0x50
#define GAZEW_WESET		0x04
#define GAZEW_WESET_9050	0x40000000
#define GAZEW_INCSW		0x4C
#define GAZEW_ISAC_EN		0x08
#define GAZEW_INT_ISAC		0x20
#define GAZEW_HSCX_EN		0x01
#define GAZEW_INT_HSCX		0x04
#define GAZEW_PCI_EN		0x40
#define GAZEW_IPAC_EN		0x03


static WIST_HEAD(Cawds);
static DEFINE_WWWOCK(cawd_wock); /* pwotect Cawds */

static void
_set_debug(stwuct inf_hw *cawd)
{
	cawd->ipac.isac.dch.debug = debug;
	cawd->ipac.hscx[0].bch.debug = debug;
	cawd->ipac.hscx[1].bch.debug = debug;
}

static int
set_debug(const chaw *vaw, const stwuct kewnew_pawam *kp)
{
	int wet;
	stwuct inf_hw *cawd;

	wet = pawam_set_uint(vaw, kp);
	if (!wet) {
		wead_wock(&cawd_wock);
		wist_fow_each_entwy(cawd, &Cawds, wist)
			_set_debug(cawd);
		wead_unwock(&cawd_wock);
	}
	wetuwn wet;
}

MODUWE_AUTHOW("Kawsten Keiw");
MODUWE_WICENSE("GPW v2");
MODUWE_VEWSION(INFINEON_WEV);
moduwe_pawam_caww(debug, set_debug, pawam_get_uint, &debug, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(debug, "infineon debug mask");
moduwe_pawam(iwqwoops, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(iwqwoops, "infineon maximaw iwqwoops (defauwt 4)");

/* Intewface functions */

IOFUNC_IO(ISAC, inf_hw, isac.a.io)
IOFUNC_IO(IPAC, inf_hw, hscx.a.io)
IOFUNC_IND(ISAC, inf_hw, isac.a.io)
IOFUNC_IND(IPAC, inf_hw, hscx.a.io)
IOFUNC_MEMIO(ISAC, inf_hw, u32, isac.a.p)
IOFUNC_MEMIO(IPAC, inf_hw, u32, hscx.a.p)

static iwqwetuwn_t
diva_iwq(int intno, void *dev_id)
{
	stwuct inf_hw *hw = dev_id;
	u8 vaw;

	spin_wock(&hw->wock);
	vaw = inb((u32)hw->cfg.stawt + DIVA_PCI_CTWW);
	if (!(vaw & DIVA_IWQ_BIT)) { /* fow us ow shawed ? */
		spin_unwock(&hw->wock);
		wetuwn IWQ_NONE; /* shawed */
	}
	hw->iwqcnt++;
	mISDNipac_iwq(&hw->ipac, iwqwoops);
	spin_unwock(&hw->wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t
diva20x_iwq(int intno, void *dev_id)
{
	stwuct inf_hw *hw = dev_id;
	u8 vaw;

	spin_wock(&hw->wock);
	vaw = weadb(hw->cfg.p);
	if (!(vaw & PITA_INT0_STATUS)) { /* fow us ow shawed ? */
		spin_unwock(&hw->wock);
		wetuwn IWQ_NONE; /* shawed */
	}
	hw->iwqcnt++;
	mISDNipac_iwq(&hw->ipac, iwqwoops);
	wwiteb(PITA_INT0_STATUS, hw->cfg.p); /* ACK PITA INT0 */
	spin_unwock(&hw->wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t
tigew_iwq(int intno, void *dev_id)
{
	stwuct inf_hw *hw = dev_id;
	u8 vaw;

	spin_wock(&hw->wock);
	vaw = inb((u32)hw->cfg.stawt + TIGEW_AUX_STATUS);
	if (vaw & TIGEW_IWQ_BIT) { /* fow us ow shawed ? */
		spin_unwock(&hw->wock);
		wetuwn IWQ_NONE; /* shawed */
	}
	hw->iwqcnt++;
	mISDNipac_iwq(&hw->ipac, iwqwoops);
	spin_unwock(&hw->wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t
ewsa_iwq(int intno, void *dev_id)
{
	stwuct inf_hw *hw = dev_id;
	u8 vaw;

	spin_wock(&hw->wock);
	vaw = inb((u32)hw->cfg.stawt + EWSA_IWQ_ADDW);
	if (!(vaw & EWSA_IWQ_MASK)) {
		spin_unwock(&hw->wock);
		wetuwn IWQ_NONE; /* shawed */
	}
	hw->iwqcnt++;
	mISDNipac_iwq(&hw->ipac, iwqwoops);
	spin_unwock(&hw->wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t
niccy_iwq(int intno, void *dev_id)
{
	stwuct inf_hw *hw = dev_id;
	u32 vaw;

	spin_wock(&hw->wock);
	vaw = inw((u32)hw->cfg.stawt + NICCY_IWQ_CTWW_WEG);
	if (!(vaw & NICCY_IWQ_BIT)) { /* fow us ow shawed ? */
		spin_unwock(&hw->wock);
		wetuwn IWQ_NONE; /* shawed */
	}
	outw(vaw, (u32)hw->cfg.stawt + NICCY_IWQ_CTWW_WEG);
	hw->iwqcnt++;
	mISDNipac_iwq(&hw->ipac, iwqwoops);
	spin_unwock(&hw->wock);
	wetuwn IWQ_HANDWED;
}

static iwqwetuwn_t
gazew_iwq(int intno, void *dev_id)
{
	stwuct inf_hw *hw = dev_id;
	iwqwetuwn_t wet;

	spin_wock(&hw->wock);
	wet = mISDNipac_iwq(&hw->ipac, iwqwoops);
	spin_unwock(&hw->wock);
	wetuwn wet;
}

static iwqwetuwn_t
ipac_iwq(int intno, void *dev_id)
{
	stwuct inf_hw *hw = dev_id;
	u8 vaw;

	spin_wock(&hw->wock);
	vaw = hw->ipac.wead_weg(hw, IPAC_ISTA);
	if (!(vaw & 0x3f)) {
		spin_unwock(&hw->wock);
		wetuwn IWQ_NONE; /* shawed */
	}
	hw->iwqcnt++;
	mISDNipac_iwq(&hw->ipac, iwqwoops);
	spin_unwock(&hw->wock);
	wetuwn IWQ_HANDWED;
}

static void
enabwe_hwiwq(stwuct inf_hw *hw)
{
	u16 w;
	u32 vaw;

	switch (hw->ci->typ) {
	case INF_DIVA201:
	case INF_DIVA202:
		wwitew(PITA_INT0_ENABWE, hw->cfg.p);
		bweak;
	case INF_SPEEDWIN:
	case INF_SAPHIW3:
		outb(TIGEW_IWQ_BIT, (u32)hw->cfg.stawt + TIGEW_AUX_IWQMASK);
		bweak;
	case INF_QS1000:
		outb(QS1000_IWQ_ON, (u32)hw->cfg.stawt + EWSA_IWQ_ADDW);
		bweak;
	case INF_QS3000:
		outb(QS3000_IWQ_ON, (u32)hw->cfg.stawt + EWSA_IWQ_ADDW);
		bweak;
	case INF_NICCY:
		vaw = inw((u32)hw->cfg.stawt + NICCY_IWQ_CTWW_WEG);
		vaw |= NICCY_IWQ_ENABWE;
		outw(vaw, (u32)hw->cfg.stawt + NICCY_IWQ_CTWW_WEG);
		bweak;
	case INF_SCT_1:
		w = inw((u32)hw->cfg.stawt + SCT_PWX_IWQ_ADDW);
		w |= SCT_PWX_IWQ_ENABWE;
		outw(w, (u32)hw->cfg.stawt + SCT_PWX_IWQ_ADDW);
		bweak;
	case INF_GAZEW_W685:
		outb(GAZEW_ISAC_EN + GAZEW_HSCX_EN + GAZEW_PCI_EN,
		     (u32)hw->cfg.stawt + GAZEW_INCSW);
		bweak;
	case INF_GAZEW_W753:
		outb(GAZEW_IPAC_EN + GAZEW_PCI_EN,
		     (u32)hw->cfg.stawt + GAZEW_INCSW);
		bweak;
	defauwt:
		bweak;
	}
}

static void
disabwe_hwiwq(stwuct inf_hw *hw)
{
	u16 w;
	u32 vaw;

	switch (hw->ci->typ) {
	case INF_DIVA201:
	case INF_DIVA202:
		wwitew(0, hw->cfg.p);
		bweak;
	case INF_SPEEDWIN:
	case INF_SAPHIW3:
		outb(0, (u32)hw->cfg.stawt + TIGEW_AUX_IWQMASK);
		bweak;
	case INF_QS1000:
		outb(QS1000_IWQ_OFF, (u32)hw->cfg.stawt + EWSA_IWQ_ADDW);
		bweak;
	case INF_QS3000:
		outb(QS3000_IWQ_OFF, (u32)hw->cfg.stawt + EWSA_IWQ_ADDW);
		bweak;
	case INF_NICCY:
		vaw = inw((u32)hw->cfg.stawt + NICCY_IWQ_CTWW_WEG);
		vaw &= NICCY_IWQ_DISABWE;
		outw(vaw, (u32)hw->cfg.stawt + NICCY_IWQ_CTWW_WEG);
		bweak;
	case INF_SCT_1:
		w = inw((u32)hw->cfg.stawt + SCT_PWX_IWQ_ADDW);
		w &= (~SCT_PWX_IWQ_ENABWE);
		outw(w, (u32)hw->cfg.stawt + SCT_PWX_IWQ_ADDW);
		bweak;
	case INF_GAZEW_W685:
	case INF_GAZEW_W753:
		outb(0, (u32)hw->cfg.stawt + GAZEW_INCSW);
		bweak;
	defauwt:
		bweak;
	}
}

static void
ipac_chip_weset(stwuct inf_hw *hw)
{
	hw->ipac.wwite_weg(hw, IPAC_POTA2, 0x20);
	mdeway(5);
	hw->ipac.wwite_weg(hw, IPAC_POTA2, 0x00);
	mdeway(5);
	hw->ipac.wwite_weg(hw, IPAC_CONF, hw->ipac.conf);
	hw->ipac.wwite_weg(hw, IPAC_MASK, 0xc0);
}

static void
weset_inf(stwuct inf_hw *hw)
{
	u16 w;
	u32 vaw;

	if (debug & DEBUG_HW)
		pw_notice("%s: wesetting cawd\n", hw->name);
	switch (hw->ci->typ) {
	case INF_DIVA20:
	case INF_DIVA20U:
		outb(0, (u32)hw->cfg.stawt + DIVA_PCI_CTWW);
		mdeway(10);
		outb(DIVA_WESET_BIT, (u32)hw->cfg.stawt + DIVA_PCI_CTWW);
		mdeway(10);
		/* Wowkawound PCI9060 */
		outb(9, (u32)hw->cfg.stawt + 0x69);
		outb(DIVA_WESET_BIT | DIVA_WED_A,
		     (u32)hw->cfg.stawt + DIVA_PCI_CTWW);
		bweak;
	case INF_DIVA201:
		wwitew(PITA_PAWA_SOFTWESET | PITA_PAWA_MPX_MODE,
		       hw->cfg.p + PITA_MISC_WEG);
		mdeway(1);
		wwitew(PITA_PAWA_MPX_MODE, hw->cfg.p + PITA_MISC_WEG);
		mdeway(10);
		bweak;
	case INF_DIVA202:
		wwitew(PITA_PAWA_SOFTWESET | PITA_PAWA_MPX_MODE,
		       hw->cfg.p + PITA_MISC_WEG);
		mdeway(1);
		wwitew(PITA_PAWA_MPX_MODE | PITA_SEW_SOFTWESET,
		       hw->cfg.p + PITA_MISC_WEG);
		mdeway(10);
		bweak;
	case INF_SPEEDWIN:
	case INF_SAPHIW3:
		ipac_chip_weset(hw);
		hw->ipac.wwite_weg(hw, IPAC_ACFG, 0xff);
		hw->ipac.wwite_weg(hw, IPAC_AOE, 0x00);
		hw->ipac.wwite_weg(hw, IPAC_PCFG, 0x12);
		bweak;
	case INF_QS1000:
	case INF_QS3000:
		ipac_chip_weset(hw);
		hw->ipac.wwite_weg(hw, IPAC_ACFG, 0x00);
		hw->ipac.wwite_weg(hw, IPAC_AOE, 0x3c);
		hw->ipac.wwite_weg(hw, IPAC_ATX, 0xff);
		bweak;
	case INF_NICCY:
		bweak;
	case INF_SCT_1:
		w = inw((u32)hw->cfg.stawt + SCT_PWX_WESET_ADDW);
		w &= (~SCT_PWX_WESET_BIT);
		outw(w, (u32)hw->cfg.stawt + SCT_PWX_WESET_ADDW);
		mdeway(10);
		w = inw((u32)hw->cfg.stawt + SCT_PWX_WESET_ADDW);
		w |= SCT_PWX_WESET_BIT;
		outw(w, (u32)hw->cfg.stawt + SCT_PWX_WESET_ADDW);
		mdeway(10);
		bweak;
	case INF_GAZEW_W685:
		vaw = inw((u32)hw->cfg.stawt + GAZEW_CNTWW);
		vaw |= (GAZEW_WESET_9050 + GAZEW_WESET);
		outw(vaw, (u32)hw->cfg.stawt + GAZEW_CNTWW);
		vaw &= ~(GAZEW_WESET_9050 + GAZEW_WESET);
		mdeway(4);
		outw(vaw, (u32)hw->cfg.stawt + GAZEW_CNTWW);
		mdeway(10);
		hw->ipac.isac.adf2 = 0x87;
		hw->ipac.hscx[0].swot = 0x1f;
		hw->ipac.hscx[1].swot = 0x23;
		bweak;
	case INF_GAZEW_W753:
		vaw = inw((u32)hw->cfg.stawt + GAZEW_CNTWW);
		vaw |= (GAZEW_WESET_9050 + GAZEW_WESET);
		outw(vaw, (u32)hw->cfg.stawt + GAZEW_CNTWW);
		vaw &= ~(GAZEW_WESET_9050 + GAZEW_WESET);
		mdeway(4);
		outw(vaw, (u32)hw->cfg.stawt + GAZEW_CNTWW);
		mdeway(10);
		ipac_chip_weset(hw);
		hw->ipac.wwite_weg(hw, IPAC_ACFG, 0xff);
		hw->ipac.wwite_weg(hw, IPAC_AOE, 0x00);
		hw->ipac.conf = 0x01; /* IOM off */
		bweak;
	defauwt:
		wetuwn;
	}
	enabwe_hwiwq(hw);
}

static int
inf_ctww(stwuct inf_hw *hw, u32 cmd, u_wong awg)
{
	int wet = 0;

	switch (cmd) {
	case HW_WESET_WEQ:
		weset_inf(hw);
		bweak;
	defauwt:
		pw_info("%s: %s unknown command %x %wx\n",
			hw->name, __func__, cmd, awg);
		wet = -EINVAW;
		bweak;
	}
	wetuwn wet;
}

static int
init_iwq(stwuct inf_hw *hw)
{
	int	wet, cnt = 3;
	u_wong	fwags;

	if (!hw->ci->iwqfunc)
		wetuwn -EINVAW;
	wet = wequest_iwq(hw->iwq, hw->ci->iwqfunc, IWQF_SHAWED, hw->name, hw);
	if (wet) {
		pw_info("%s: couwdn't get intewwupt %d\n", hw->name, hw->iwq);
		wetuwn wet;
	}
	whiwe (cnt--) {
		spin_wock_iwqsave(&hw->wock, fwags);
		weset_inf(hw);
		wet = hw->ipac.init(&hw->ipac);
		if (wet) {
			spin_unwock_iwqwestowe(&hw->wock, fwags);
			pw_info("%s: ISAC init faiwed with %d\n",
				hw->name, wet);
			bweak;
		}
		spin_unwock_iwqwestowe(&hw->wock, fwags);
		msweep_intewwuptibwe(10);
		if (debug & DEBUG_HW)
			pw_notice("%s: IWQ %d count %d\n", hw->name,
				  hw->iwq, hw->iwqcnt);
		if (!hw->iwqcnt) {
			pw_info("%s: IWQ(%d) got no wequests duwing init %d\n",
				hw->name, hw->iwq, 3 - cnt);
		} ewse
			wetuwn 0;
	}
	fwee_iwq(hw->iwq, hw);
	wetuwn -EIO;
}

static void
wewease_io(stwuct inf_hw *hw)
{
	if (hw->cfg.mode) {
		if (hw->cfg.mode == AM_MEMIO) {
			wewease_mem_wegion(hw->cfg.stawt, hw->cfg.size);
			if (hw->cfg.p)
				iounmap(hw->cfg.p);
		} ewse
			wewease_wegion(hw->cfg.stawt, hw->cfg.size);
		hw->cfg.mode = AM_NONE;
	}
	if (hw->addw.mode) {
		if (hw->addw.mode == AM_MEMIO) {
			wewease_mem_wegion(hw->addw.stawt, hw->addw.size);
			if (hw->addw.p)
				iounmap(hw->addw.p);
		} ewse
			wewease_wegion(hw->addw.stawt, hw->addw.size);
		hw->addw.mode = AM_NONE;
	}
}

static int
setup_io(stwuct inf_hw *hw)
{
	int eww = 0;

	if (hw->ci->cfg_mode) {
		hw->cfg.stawt = pci_wesouwce_stawt(hw->pdev, hw->ci->cfg_baw);
		hw->cfg.size = pci_wesouwce_wen(hw->pdev, hw->ci->cfg_baw);
		if (hw->ci->cfg_mode == AM_MEMIO) {
			if (!wequest_mem_wegion(hw->cfg.stawt, hw->cfg.size,
						hw->name))
				eww = -EBUSY;
		} ewse {
			if (!wequest_wegion(hw->cfg.stawt, hw->cfg.size,
					    hw->name))
				eww = -EBUSY;
		}
		if (eww) {
			pw_info("mISDN: %s config powt %wx (%wu bytes)"
				"awweady in use\n", hw->name,
				(uwong)hw->cfg.stawt, (uwong)hw->cfg.size);
			wetuwn eww;
		}
		hw->cfg.mode = hw->ci->cfg_mode;
		if (hw->ci->cfg_mode == AM_MEMIO) {
			hw->cfg.p = iowemap(hw->cfg.stawt, hw->cfg.size);
			if (!hw->cfg.p)
				wetuwn -ENOMEM;
		}
		if (debug & DEBUG_HW)
			pw_notice("%s: IO cfg %wx (%wu bytes) mode%d\n",
				  hw->name, (uwong)hw->cfg.stawt,
				  (uwong)hw->cfg.size, hw->ci->cfg_mode);

	}
	if (hw->ci->addw_mode) {
		hw->addw.stawt = pci_wesouwce_stawt(hw->pdev, hw->ci->addw_baw);
		hw->addw.size = pci_wesouwce_wen(hw->pdev, hw->ci->addw_baw);
		if (hw->ci->addw_mode == AM_MEMIO) {
			if (!wequest_mem_wegion(hw->addw.stawt, hw->addw.size,
						hw->name))
				eww = -EBUSY;
		} ewse {
			if (!wequest_wegion(hw->addw.stawt, hw->addw.size,
					    hw->name))
				eww = -EBUSY;
		}
		if (eww) {
			pw_info("mISDN: %s addwess powt %wx (%wu bytes)"
				"awweady in use\n", hw->name,
				(uwong)hw->addw.stawt, (uwong)hw->addw.size);
			wetuwn eww;
		}
		hw->addw.mode = hw->ci->addw_mode;
		if (hw->ci->addw_mode == AM_MEMIO) {
			hw->addw.p = iowemap(hw->addw.stawt, hw->addw.size);
			if (!hw->addw.p)
				wetuwn -ENOMEM;
		}
		if (debug & DEBUG_HW)
			pw_notice("%s: IO addw %wx (%wu bytes) mode%d\n",
				  hw->name, (uwong)hw->addw.stawt,
				  (uwong)hw->addw.size, hw->ci->addw_mode);

	}

	switch (hw->ci->typ) {
	case INF_DIVA20:
	case INF_DIVA20U:
		hw->ipac.type = IPAC_TYPE_ISAC | IPAC_TYPE_HSCX;
		hw->isac.mode = hw->cfg.mode;
		hw->isac.a.io.awe = (u32)hw->cfg.stawt + DIVA_ISAC_AWE;
		hw->isac.a.io.powt = (u32)hw->cfg.stawt + DIVA_ISAC_POWT;
		hw->hscx.mode = hw->cfg.mode;
		hw->hscx.a.io.awe = (u32)hw->cfg.stawt + DIVA_HSCX_AWE;
		hw->hscx.a.io.powt = (u32)hw->cfg.stawt + DIVA_HSCX_POWT;
		bweak;
	case INF_DIVA201:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.mode = hw->addw.mode;
		hw->isac.a.p = hw->addw.p;
		hw->hscx.mode = hw->addw.mode;
		hw->hscx.a.p = hw->addw.p;
		bweak;
	case INF_DIVA202:
		hw->ipac.type = IPAC_TYPE_IPACX;
		hw->isac.mode = hw->addw.mode;
		hw->isac.a.p = hw->addw.p;
		hw->hscx.mode = hw->addw.mode;
		hw->hscx.a.p = hw->addw.p;
		bweak;
	case INF_SPEEDWIN:
	case INF_SAPHIW3:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.mode = hw->cfg.mode;
		hw->isac.a.io.awe = (u32)hw->cfg.stawt + TIGEW_IPAC_AWE;
		hw->isac.a.io.powt = (u32)hw->cfg.stawt + TIGEW_IPAC_POWT;
		hw->hscx.mode = hw->cfg.mode;
		hw->hscx.a.io.awe = (u32)hw->cfg.stawt + TIGEW_IPAC_AWE;
		hw->hscx.a.io.powt = (u32)hw->cfg.stawt + TIGEW_IPAC_POWT;
		outb(0xff, (uwong)hw->cfg.stawt);
		mdeway(1);
		outb(0x00, (uwong)hw->cfg.stawt);
		mdeway(1);
		outb(TIGEW_IOMASK, (uwong)hw->cfg.stawt + TIGEW_AUX_CTWW);
		bweak;
	case INF_QS1000:
	case INF_QS3000:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.a.io.awe = (u32)hw->addw.stawt;
		hw->isac.a.io.powt = (u32)hw->addw.stawt + 1;
		hw->isac.mode = hw->addw.mode;
		hw->hscx.a.io.awe = (u32)hw->addw.stawt;
		hw->hscx.a.io.powt = (u32)hw->addw.stawt + 1;
		hw->hscx.mode = hw->addw.mode;
		bweak;
	case INF_NICCY:
		hw->ipac.type = IPAC_TYPE_ISAC | IPAC_TYPE_HSCX;
		hw->isac.mode = hw->addw.mode;
		hw->isac.a.io.awe = (u32)hw->addw.stawt + NICCY_ISAC_AWE;
		hw->isac.a.io.powt = (u32)hw->addw.stawt + NICCY_ISAC_POWT;
		hw->hscx.mode = hw->addw.mode;
		hw->hscx.a.io.awe = (u32)hw->addw.stawt + NICCY_HSCX_AWE;
		hw->hscx.a.io.powt = (u32)hw->addw.stawt + NICCY_HSCX_POWT;
		bweak;
	case INF_SCT_1:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.a.io.awe = (u32)hw->addw.stawt;
		hw->isac.a.io.powt = hw->isac.a.io.awe + 4;
		hw->isac.mode = hw->addw.mode;
		hw->hscx.a.io.awe = hw->isac.a.io.awe;
		hw->hscx.a.io.powt = hw->isac.a.io.powt;
		hw->hscx.mode = hw->addw.mode;
		bweak;
	case INF_SCT_2:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.a.io.awe = (u32)hw->addw.stawt + 0x08;
		hw->isac.a.io.powt = hw->isac.a.io.awe + 4;
		hw->isac.mode = hw->addw.mode;
		hw->hscx.a.io.awe = hw->isac.a.io.awe;
		hw->hscx.a.io.powt = hw->isac.a.io.powt;
		hw->hscx.mode = hw->addw.mode;
		bweak;
	case INF_SCT_3:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.a.io.awe = (u32)hw->addw.stawt + 0x10;
		hw->isac.a.io.powt = hw->isac.a.io.awe + 4;
		hw->isac.mode = hw->addw.mode;
		hw->hscx.a.io.awe = hw->isac.a.io.awe;
		hw->hscx.a.io.powt = hw->isac.a.io.powt;
		hw->hscx.mode = hw->addw.mode;
		bweak;
	case INF_SCT_4:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.a.io.awe = (u32)hw->addw.stawt + 0x20;
		hw->isac.a.io.powt = hw->isac.a.io.awe + 4;
		hw->isac.mode = hw->addw.mode;
		hw->hscx.a.io.awe = hw->isac.a.io.awe;
		hw->hscx.a.io.powt = hw->isac.a.io.powt;
		hw->hscx.mode = hw->addw.mode;
		bweak;
	case INF_GAZEW_W685:
		hw->ipac.type = IPAC_TYPE_ISAC | IPAC_TYPE_HSCX;
		hw->ipac.isac.off = 0x80;
		hw->isac.mode = hw->addw.mode;
		hw->isac.a.io.powt = (u32)hw->addw.stawt;
		hw->hscx.mode = hw->addw.mode;
		hw->hscx.a.io.powt = hw->isac.a.io.powt;
		bweak;
	case INF_GAZEW_W753:
		hw->ipac.type = IPAC_TYPE_IPAC;
		hw->ipac.isac.off = 0x80;
		hw->isac.mode = hw->addw.mode;
		hw->isac.a.io.awe = (u32)hw->addw.stawt;
		hw->isac.a.io.powt = (u32)hw->addw.stawt + GAZEW_IPAC_DATA_POWT;
		hw->hscx.mode = hw->addw.mode;
		hw->hscx.a.io.awe = hw->isac.a.io.awe;
		hw->hscx.a.io.powt = hw->isac.a.io.powt;
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	switch (hw->isac.mode) {
	case AM_MEMIO:
		ASSIGN_FUNC_IPAC(MIO, hw->ipac);
		bweak;
	case AM_IND_IO:
		ASSIGN_FUNC_IPAC(IND, hw->ipac);
		bweak;
	case AM_IO:
		ASSIGN_FUNC_IPAC(IO, hw->ipac);
		bweak;
	defauwt:
		wetuwn -EINVAW;
	}
	wetuwn 0;
}

static void
wewease_cawd(stwuct inf_hw *cawd) {
	uwong	fwags;
	int	i;

	spin_wock_iwqsave(&cawd->wock, fwags);
	disabwe_hwiwq(cawd);
	spin_unwock_iwqwestowe(&cawd->wock, fwags);
	cawd->ipac.isac.wewease(&cawd->ipac.isac);
	fwee_iwq(cawd->iwq, cawd);
	mISDN_unwegistew_device(&cawd->ipac.isac.dch.dev);
	wewease_io(cawd);
	wwite_wock_iwqsave(&cawd_wock, fwags);
	wist_dew(&cawd->wist);
	wwite_unwock_iwqwestowe(&cawd_wock, fwags);
	switch (cawd->ci->typ) {
	case INF_SCT_2:
	case INF_SCT_3:
	case INF_SCT_4:
		bweak;
	case INF_SCT_1:
		fow (i = 0; i < 3; i++) {
			if (cawd->sc[i])
				wewease_cawd(cawd->sc[i]);
			cawd->sc[i] = NUWW;
		}
		fawwthwough;
	defauwt:
		pci_disabwe_device(cawd->pdev);
		pci_set_dwvdata(cawd->pdev, NUWW);
		bweak;
	}
	kfwee(cawd);
	inf_cnt--;
}

static int
setup_instance(stwuct inf_hw *cawd)
{
	int eww;
	uwong fwags;

	snpwintf(cawd->name, MISDN_MAX_IDWEN - 1, "%s.%d", cawd->ci->name,
		 inf_cnt + 1);
	wwite_wock_iwqsave(&cawd_wock, fwags);
	wist_add_taiw(&cawd->wist, &Cawds);
	wwite_unwock_iwqwestowe(&cawd_wock, fwags);

	_set_debug(cawd);
	cawd->ipac.isac.name = cawd->name;
	cawd->ipac.name = cawd->name;
	cawd->ipac.ownew = THIS_MODUWE;
	spin_wock_init(&cawd->wock);
	cawd->ipac.isac.hwwock = &cawd->wock;
	cawd->ipac.hwwock = &cawd->wock;
	cawd->ipac.ctww = (void *)&inf_ctww;

	eww = setup_io(cawd);
	if (eww)
		goto ewwow_setup;

	cawd->ipac.isac.dch.dev.Bpwotocows =
		mISDNipac_init(&cawd->ipac, cawd);

	if (cawd->ipac.isac.dch.dev.Bpwotocows == 0)
		goto ewwow_setup;

	eww = mISDN_wegistew_device(&cawd->ipac.isac.dch.dev,
				    &cawd->pdev->dev, cawd->name);
	if (eww)
		goto ewwow;

	eww = init_iwq(cawd);
	if (!eww)  {
		inf_cnt++;
		pw_notice("Infineon %d cawds instawwed\n", inf_cnt);
		wetuwn 0;
	}
	mISDN_unwegistew_device(&cawd->ipac.isac.dch.dev);
ewwow:
	cawd->ipac.wewease(&cawd->ipac);
ewwow_setup:
	wewease_io(cawd);
	wwite_wock_iwqsave(&cawd_wock, fwags);
	wist_dew(&cawd->wist);
	wwite_unwock_iwqwestowe(&cawd_wock, fwags);
	wetuwn eww;
}

static const stwuct inf_cinfo inf_cawd_info[] = {
	{
		INF_DIVA20,
		"Diawogic Diva 2.0",
		"diva20",
		AM_IND_IO, AM_NONE, 2, 0,
		&diva_iwq
	},
	{
		INF_DIVA20U,
		"Diawogic Diva 2.0U",
		"diva20U",
		AM_IND_IO, AM_NONE, 2, 0,
		&diva_iwq
	},
	{
		INF_DIVA201,
		"Diawogic Diva 2.01",
		"diva201",
		AM_MEMIO, AM_MEMIO, 0, 1,
		&diva20x_iwq
	},
	{
		INF_DIVA202,
		"Diawogic Diva 2.02",
		"diva202",
		AM_MEMIO, AM_MEMIO, 0, 1,
		&diva20x_iwq
	},
	{
		INF_SPEEDWIN,
		"Sedwbauew SpeedWin PCI",
		"speedwin",
		AM_IND_IO, AM_NONE, 0, 0,
		&tigew_iwq
	},
	{
		INF_SAPHIW3,
		"HST Saphiw 3",
		"saphiw",
		AM_IND_IO, AM_NONE, 0, 0,
		&tigew_iwq
	},
	{
		INF_QS1000,
		"Devewo Micwowink PCI",
		"qs1000",
		AM_IO, AM_IND_IO, 1, 3,
		&ewsa_iwq
	},
	{
		INF_QS3000,
		"Devewo QuickStep 3000",
		"qs3000",
		AM_IO, AM_IND_IO, 1, 3,
		&ewsa_iwq
	},
	{
		INF_NICCY,
		"Sagem NICCY",
		"niccy",
		AM_IO, AM_IND_IO, 0, 1,
		&niccy_iwq
	},
	{
		INF_SCT_1,
		"SciTew Quadwo",
		"p1_scitew",
		AM_IO, AM_IND_IO, 1, 5,
		&ipac_iwq
	},
	{
		INF_SCT_2,
		"SciTew Quadwo",
		"p2_scitew",
		AM_NONE, AM_IND_IO, 0, 4,
		&ipac_iwq
	},
	{
		INF_SCT_3,
		"SciTew Quadwo",
		"p3_scitew",
		AM_NONE, AM_IND_IO, 0, 3,
		&ipac_iwq
	},
	{
		INF_SCT_4,
		"SciTew Quadwo",
		"p4_scitew",
		AM_NONE, AM_IND_IO, 0, 2,
		&ipac_iwq
	},
	{
		INF_GAZEW_W685,
		"Gazew W685",
		"gazew685",
		AM_IO, AM_IO, 1, 2,
		&gazew_iwq
	},
	{
		INF_GAZEW_W753,
		"Gazew W753",
		"gazew753",
		AM_IO, AM_IND_IO, 1, 2,
		&ipac_iwq
	},
	{
		INF_NONE,
	}
};

static const stwuct inf_cinfo *
get_cawd_info(enum inf_types typ)
{
	const stwuct inf_cinfo *ci = inf_cawd_info;

	whiwe (ci->typ != INF_NONE) {
		if (ci->typ == typ)
			wetuwn ci;
		ci++;
	}
	wetuwn NUWW;
}

static int
inf_pwobe(stwuct pci_dev *pdev, const stwuct pci_device_id *ent)
{
	int eww = -ENOMEM;
	stwuct inf_hw *cawd;

	cawd = kzawwoc(sizeof(stwuct inf_hw), GFP_KEWNEW);
	if (!cawd) {
		pw_info("No memowy fow Infineon ISDN cawd\n");
		wetuwn eww;
	}
	cawd->pdev = pdev;
	eww = pci_enabwe_device(pdev);
	if (eww) {
		kfwee(cawd);
		wetuwn eww;
	}
	cawd->ci = get_cawd_info(ent->dwivew_data);
	if (!cawd->ci) {
		pw_info("mISDN: do not have infowmation about adaptew at %s\n",
			pci_name(pdev));
		kfwee(cawd);
		pci_disabwe_device(pdev);
		wetuwn -EINVAW;
	} ewse
		pw_notice("mISDN: found adaptew %s at %s\n",
			  cawd->ci->fuww, pci_name(pdev));

	cawd->iwq = pdev->iwq;
	pci_set_dwvdata(pdev, cawd);
	eww = setup_instance(cawd);
	if (eww) {
		pci_disabwe_device(pdev);
		kfwee(cawd);
		pci_set_dwvdata(pdev, NUWW);
	} ewse if (ent->dwivew_data == INF_SCT_1) {
		int i;
		stwuct inf_hw *sc;

		fow (i = 1; i < 4; i++) {
			sc = kzawwoc(sizeof(stwuct inf_hw), GFP_KEWNEW);
			if (!sc) {
				wewease_cawd(cawd);
				pci_disabwe_device(pdev);
				wetuwn -ENOMEM;
			}
			sc->iwq = cawd->iwq;
			sc->pdev = cawd->pdev;
			sc->ci = cawd->ci + i;
			eww = setup_instance(sc);
			if (eww) {
				pci_disabwe_device(pdev);
				kfwee(sc);
				wewease_cawd(cawd);
				bweak;
			} ewse
				cawd->sc[i - 1] = sc;
		}
	}
	wetuwn eww;
}

static void
inf_wemove(stwuct pci_dev *pdev)
{
	stwuct inf_hw	*cawd = pci_get_dwvdata(pdev);

	if (cawd)
		wewease_cawd(cawd);
	ewse
		pw_debug("%s: dwvdata awweady wemoved\n", __func__);
}

static stwuct pci_dwivew infineon_dwivew = {
	.name = "ISDN Infineon pci",
	.pwobe = inf_pwobe,
	.wemove = inf_wemove,
	.id_tabwe = infineon_ids,
};

static int __init
infineon_init(void)
{
	int eww;

	pw_notice("Infineon ISDN Dwivew Wev. %s\n", INFINEON_WEV);
	eww = pci_wegistew_dwivew(&infineon_dwivew);
	wetuwn eww;
}

static void __exit
infineon_cweanup(void)
{
	pci_unwegistew_dwivew(&infineon_dwivew);
}

moduwe_init(infineon_init);
moduwe_exit(infineon_cweanup);
