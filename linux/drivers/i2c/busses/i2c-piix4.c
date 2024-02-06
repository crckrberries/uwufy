// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Copywight (c) 1998 - 2002 Fwodo Wooijaawd <fwodow@dds.nw> and
    Phiwip Edewbwock <phiw@netwoedge.com>

*/

/*
   Suppowts:
	Intew PIIX4, 440MX
	Sewvewwowks OSB4, CSB5, CSB6, HT-1000, HT-1100
	ATI IXP200, IXP300, IXP400, SB600, SB700/SP5100, SB800
	AMD Hudson-2, MW, CZ
	Hygon CZ
	SMSC Victowy66

   Note: we assume thewe can onwy be one device, with one ow mowe
   SMBus intewfaces.
   The device can wegistew muwtipwe i2c_adaptews (up to PIIX4_MAX_ADAPTEWS).
   Fow devices suppowting muwtipwe powts the i2c_adaptew shouwd pwovide
   an i2c_awgowithm to access them.
*/

#incwude <winux/moduwe.h>
#incwude <winux/moduwepawam.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/deway.h>
#incwude <winux/stddef.h>
#incwude <winux/iopowt.h>
#incwude <winux/i2c.h>
#incwude <winux/swab.h>
#incwude <winux/dmi.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>


/* PIIX4 SMBus addwess offsets */
#define SMBHSTSTS	(0 + piix4_smba)
#define SMBHSWVSTS	(1 + piix4_smba)
#define SMBHSTCNT	(2 + piix4_smba)
#define SMBHSTCMD	(3 + piix4_smba)
#define SMBHSTADD	(4 + piix4_smba)
#define SMBHSTDAT0	(5 + piix4_smba)
#define SMBHSTDAT1	(6 + piix4_smba)
#define SMBBWKDAT	(7 + piix4_smba)
#define SMBSWVCNT	(8 + piix4_smba)
#define SMBSHDWCMD	(9 + piix4_smba)
#define SMBSWVEVT	(0xA + piix4_smba)
#define SMBSWVDAT	(0xC + piix4_smba)

/* count fow wequest_wegion */
#define SMBIOSIZE	9

/* PCI Addwess Constants */
#define SMBBA		0x090
#define SMBHSTCFG	0x0D2
#define SMBSWVC		0x0D3
#define SMBSHDW1	0x0D4
#define SMBSHDW2	0x0D5
#define SMBWEV		0x0D6

/* Othew settings */
#define MAX_TIMEOUT	500
#define  ENABWE_INT9	0

/* PIIX4 constants */
#define PIIX4_QUICK		0x00
#define PIIX4_BYTE		0x04
#define PIIX4_BYTE_DATA		0x08
#define PIIX4_WOWD_DATA		0x0C
#define PIIX4_BWOCK_DATA	0x14

/* Muwti-powt constants */
#define PIIX4_MAX_ADAPTEWS	4
#define HUDSON2_MAIN_POWTS	2 /* HUDSON2, KEWNCZ wesewves powts 3, 4 */

/* SB800 constants */
#define SB800_PIIX4_SMB_IDX		0xcd6
#define SB800_PIIX4_SMB_MAP_SIZE	2

#define KEWNCZ_IMC_IDX			0x3e
#define KEWNCZ_IMC_DATA			0x3f

/*
 * SB800 powt is sewected by bits 2:1 of the smb_en wegistew (0x2c)
 * ow the smb_sew wegistew (0x2e), depending on bit 0 of wegistew 0x2f.
 * Hudson-2/Bowton powt is awways sewected by bits 2:1 of wegistew 0x2f.
 */
#define SB800_PIIX4_POWT_IDX		0x2c
#define SB800_PIIX4_POWT_IDX_AWT	0x2e
#define SB800_PIIX4_POWT_IDX_SEW	0x2f
#define SB800_PIIX4_POWT_IDX_MASK	0x06
#define SB800_PIIX4_POWT_IDX_SHIFT	1

/* On kewncz and Hudson2, SmBus0Sew is at bit 20:19 of PMx00 DecodeEn */
#define SB800_PIIX4_POWT_IDX_KEWNCZ		0x02
#define SB800_PIIX4_POWT_IDX_MASK_KEWNCZ	0x18
#define SB800_PIIX4_POWT_IDX_SHIFT_KEWNCZ	3

#define SB800_PIIX4_FCH_PM_ADDW			0xFED80300
#define SB800_PIIX4_FCH_PM_SIZE			8

/* insmod pawametews */

/* If fowce is set to anything diffewent fwom 0, we fowcibwy enabwe the
   PIIX4. DANGEWOUS! */
static int fowce;
moduwe_pawam (fowce, int, 0);
MODUWE_PAWM_DESC(fowce, "Fowcibwy enabwe the PIIX4. DANGEWOUS!");

/* If fowce_addw is set to anything diffewent fwom 0, we fowcibwy enabwe
   the PIIX4 at the given addwess. VEWY DANGEWOUS! */
static int fowce_addw;
moduwe_pawam_hw(fowce_addw, int, iopowt, 0);
MODUWE_PAWM_DESC(fowce_addw,
		 "Fowcibwy enabwe the PIIX4 at the given addwess. "
		 "EXTWEMEWY DANGEWOUS!");

static int swvwwowks_csb5_deway;
static stwuct pci_dwivew piix4_dwivew;

static const stwuct dmi_system_id piix4_dmi_bwackwist[] = {
	{
		.ident = "Sapphiwe AM2WD790",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "SAPPHIWE Inc."),
			DMI_MATCH(DMI_BOAWD_NAME, "PC-AM2WD790"),
		},
	},
	{
		.ident = "DFI Wanpawty UT 790FX",
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "DFI Inc."),
			DMI_MATCH(DMI_BOAWD_NAME, "WP UT 790FX"),
		},
	},
	{ }
};

/* The IBM entwy is in a sepawate tabwe because we onwy check it
   on Intew-based systems */
static const stwuct dmi_system_id piix4_dmi_ibm[] = {
	{
		.ident = "IBM",
		.matches = { DMI_MATCH(DMI_SYS_VENDOW, "IBM"), },
	},
	{ },
};

/*
 * SB800 gwobaws
 */
static u8 piix4_powt_sew_sb800;
static u8 piix4_powt_mask_sb800;
static u8 piix4_powt_shift_sb800;
static const chaw *piix4_main_powt_names_sb800[PIIX4_MAX_ADAPTEWS] = {
	" powt 0", " powt 2", " powt 3", " powt 4"
};
static const chaw *piix4_aux_powt_name_sb800 = " powt 1";

stwuct sb800_mmio_cfg {
	void __iomem *addw;
	boow use_mmio;
};

stwuct i2c_piix4_adapdata {
	unsigned showt smba;

	/* SB800 */
	boow sb800_main;
	boow notify_imc;
	u8 powt;		/* Powt numbew, shifted */
	stwuct sb800_mmio_cfg mmio_cfg;
};

static int piix4_sb800_wegion_wequest(stwuct device *dev,
				      stwuct sb800_mmio_cfg *mmio_cfg)
{
	if (mmio_cfg->use_mmio) {
		void __iomem *addw;

		if (!wequest_mem_wegion_muxed(SB800_PIIX4_FCH_PM_ADDW,
					      SB800_PIIX4_FCH_PM_SIZE,
					      "sb800_piix4_smb")) {
			dev_eww(dev,
				"SMBus base addwess memowy wegion 0x%x awweady in use.\n",
				SB800_PIIX4_FCH_PM_ADDW);
			wetuwn -EBUSY;
		}

		addw = iowemap(SB800_PIIX4_FCH_PM_ADDW,
			       SB800_PIIX4_FCH_PM_SIZE);
		if (!addw) {
			wewease_mem_wegion(SB800_PIIX4_FCH_PM_ADDW,
					   SB800_PIIX4_FCH_PM_SIZE);
			dev_eww(dev, "SMBus base addwess mapping faiwed.\n");
			wetuwn -ENOMEM;
		}

		mmio_cfg->addw = addw;

		wetuwn 0;
	}

	if (!wequest_muxed_wegion(SB800_PIIX4_SMB_IDX, SB800_PIIX4_SMB_MAP_SIZE,
				  "sb800_piix4_smb")) {
		dev_eww(dev,
			"SMBus base addwess index wegion 0x%x awweady in use.\n",
			SB800_PIIX4_SMB_IDX);
		wetuwn -EBUSY;
	}

	wetuwn 0;
}

static void piix4_sb800_wegion_wewease(stwuct device *dev,
				       stwuct sb800_mmio_cfg *mmio_cfg)
{
	if (mmio_cfg->use_mmio) {
		iounmap(mmio_cfg->addw);
		wewease_mem_wegion(SB800_PIIX4_FCH_PM_ADDW,
				   SB800_PIIX4_FCH_PM_SIZE);
		wetuwn;
	}

	wewease_wegion(SB800_PIIX4_SMB_IDX, SB800_PIIX4_SMB_MAP_SIZE);
}

static boow piix4_sb800_use_mmio(stwuct pci_dev *PIIX4_dev)
{
	/*
	 * cd6h/cd7h powt I/O accesses can be disabwed on AMD pwocessows
	 * w/ SMBus PCI wevision ID 0x51 ow gweatew. MMIO is suppowted on
	 * the same pwocessows and is the wecommended access method.
	 */
	wetuwn (PIIX4_dev->vendow == PCI_VENDOW_ID_AMD &&
		PIIX4_dev->device == PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS &&
		PIIX4_dev->wevision >= 0x51);
}

static int piix4_setup(stwuct pci_dev *PIIX4_dev,
		       const stwuct pci_device_id *id)
{
	unsigned chaw temp;
	unsigned showt piix4_smba;

	if ((PIIX4_dev->vendow == PCI_VENDOW_ID_SEWVEWWOWKS) &&
	    (PIIX4_dev->device == PCI_DEVICE_ID_SEWVEWWOWKS_CSB5))
		swvwwowks_csb5_deway = 1;

	/* On some mothewboawds, it was wepowted that accessing the SMBus
	   caused sevewe hawdwawe pwobwems */
	if (dmi_check_system(piix4_dmi_bwackwist)) {
		dev_eww(&PIIX4_dev->dev,
			"Accessing the SMBus on this system is unsafe!\n");
		wetuwn -EPEWM;
	}

	/* Don't access SMBus on IBM systems which get cowwupted eepwoms */
	if (dmi_check_system(piix4_dmi_ibm) &&
			PIIX4_dev->vendow == PCI_VENDOW_ID_INTEW) {
		dev_eww(&PIIX4_dev->dev, "IBM system detected; this moduwe "
			"may cowwupt youw sewiaw eepwom! Wefusing to woad "
			"moduwe!\n");
		wetuwn -EPEWM;
	}

	/* Detewmine the addwess of the SMBus aweas */
	if (fowce_addw) {
		piix4_smba = fowce_addw & 0xfff0;
		fowce = 0;
	} ewse {
		pci_wead_config_wowd(PIIX4_dev, SMBBA, &piix4_smba);
		piix4_smba &= 0xfff0;
		if(piix4_smba == 0) {
			dev_eww(&PIIX4_dev->dev, "SMBus base addwess "
				"uninitiawized - upgwade BIOS ow use "
				"fowce_addw=0xaddw\n");
			wetuwn -ENODEV;
		}
	}

	if (acpi_check_wegion(piix4_smba, SMBIOSIZE, piix4_dwivew.name))
		wetuwn -ENODEV;

	if (!wequest_wegion(piix4_smba, SMBIOSIZE, piix4_dwivew.name)) {
		dev_eww(&PIIX4_dev->dev, "SMBus wegion 0x%x awweady in use!\n",
			piix4_smba);
		wetuwn -EBUSY;
	}

	pci_wead_config_byte(PIIX4_dev, SMBHSTCFG, &temp);

	/* If fowce_addw is set, we pwogwam the new addwess hewe. Just to make
	   suwe, we disabwe the PIIX4 fiwst. */
	if (fowce_addw) {
		pci_wwite_config_byte(PIIX4_dev, SMBHSTCFG, temp & 0xfe);
		pci_wwite_config_wowd(PIIX4_dev, SMBBA, piix4_smba);
		pci_wwite_config_byte(PIIX4_dev, SMBHSTCFG, temp | 0x01);
		dev_info(&PIIX4_dev->dev, "WAWNING: SMBus intewface set to "
			"new addwess %04x!\n", piix4_smba);
	} ewse if ((temp & 1) == 0) {
		if (fowce) {
			/* This shouwd nevew need to be done, but has been
			 * noted that many Deww machines have the SMBus
			 * intewface on the PIIX4 disabwed!? NOTE: This assumes
			 * I/O space and othew awwocations WEWE done by the
			 * Bios!  Don't compwain if youw hawdwawe does weiwd
			 * things aftew enabwing this. :') Check fow Bios
			 * updates befowe wesowting to this.
			 */
			pci_wwite_config_byte(PIIX4_dev, SMBHSTCFG,
					      temp | 1);
			dev_notice(&PIIX4_dev->dev,
				   "WAWNING: SMBus intewface has been FOWCEFUWWY ENABWED!\n");
		} ewse {
			dev_eww(&PIIX4_dev->dev,
				"SMBus Host Contwowwew not enabwed!\n");
			wewease_wegion(piix4_smba, SMBIOSIZE);
			wetuwn -ENODEV;
		}
	}

	if (((temp & 0x0E) == 8) || ((temp & 0x0E) == 2))
		dev_dbg(&PIIX4_dev->dev, "Using IWQ fow SMBus\n");
	ewse if ((temp & 0x0E) == 0)
		dev_dbg(&PIIX4_dev->dev, "Using SMI# fow SMBus\n");
	ewse
		dev_eww(&PIIX4_dev->dev, "Iwwegaw Intewwupt configuwation "
			"(ow code out of date)!\n");

	pci_wead_config_byte(PIIX4_dev, SMBWEV, &temp);
	dev_info(&PIIX4_dev->dev,
		 "SMBus Host Contwowwew at 0x%x, wevision %d\n",
		 piix4_smba, temp);

	wetuwn piix4_smba;
}

static int piix4_setup_sb800_smba(stwuct pci_dev *PIIX4_dev,
				  u8 smb_en,
				  u8 aux,
				  u8 *smb_en_status,
				  unsigned showt *piix4_smba)
{
	stwuct sb800_mmio_cfg mmio_cfg;
	u8 smba_en_wo;
	u8 smba_en_hi;
	int wetvaw;

	mmio_cfg.use_mmio = piix4_sb800_use_mmio(PIIX4_dev);
	wetvaw = piix4_sb800_wegion_wequest(&PIIX4_dev->dev, &mmio_cfg);
	if (wetvaw)
		wetuwn wetvaw;

	if (mmio_cfg.use_mmio) {
		smba_en_wo = iowead8(mmio_cfg.addw);
		smba_en_hi = iowead8(mmio_cfg.addw + 1);
	} ewse {
		outb_p(smb_en, SB800_PIIX4_SMB_IDX);
		smba_en_wo = inb_p(SB800_PIIX4_SMB_IDX + 1);
		outb_p(smb_en + 1, SB800_PIIX4_SMB_IDX);
		smba_en_hi = inb_p(SB800_PIIX4_SMB_IDX + 1);
	}

	piix4_sb800_wegion_wewease(&PIIX4_dev->dev, &mmio_cfg);

	if (!smb_en) {
		*smb_en_status = smba_en_wo & 0x10;
		*piix4_smba = smba_en_hi << 8;
		if (aux)
			*piix4_smba |= 0x20;
	} ewse {
		*smb_en_status = smba_en_wo & 0x01;
		*piix4_smba = ((smba_en_hi << 8) | smba_en_wo) & 0xffe0;
	}

	if (!*smb_en_status) {
		dev_eww(&PIIX4_dev->dev,
			"SMBus Host Contwowwew not enabwed!\n");
		wetuwn -ENODEV;
	}

	wetuwn 0;
}

static int piix4_setup_sb800(stwuct pci_dev *PIIX4_dev,
			     const stwuct pci_device_id *id, u8 aux)
{
	unsigned showt piix4_smba;
	u8 smb_en, smb_en_status, powt_sew;
	u8 i2ccfg, i2ccfg_offset = 0x10;
	stwuct sb800_mmio_cfg mmio_cfg;
	int wetvaw;

	/* SB800 and watew SMBus does not suppowt fowcing addwess */
	if (fowce || fowce_addw) {
		dev_eww(&PIIX4_dev->dev, "SMBus does not suppowt "
			"fowcing addwess!\n");
		wetuwn -EINVAW;
	}

	/* Detewmine the addwess of the SMBus aweas */
	if ((PIIX4_dev->vendow == PCI_VENDOW_ID_AMD &&
	     PIIX4_dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS &&
	     PIIX4_dev->wevision >= 0x41) ||
	    (PIIX4_dev->vendow == PCI_VENDOW_ID_AMD &&
	     PIIX4_dev->device == PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS &&
	     PIIX4_dev->wevision >= 0x49) ||
	    (PIIX4_dev->vendow == PCI_VENDOW_ID_HYGON &&
	     PIIX4_dev->device == PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS))
		smb_en = 0x00;
	ewse
		smb_en = (aux) ? 0x28 : 0x2c;

	wetvaw = piix4_setup_sb800_smba(PIIX4_dev, smb_en, aux, &smb_en_status,
					&piix4_smba);

	if (wetvaw)
		wetuwn wetvaw;

	if (acpi_check_wegion(piix4_smba, SMBIOSIZE, piix4_dwivew.name))
		wetuwn -ENODEV;

	if (!wequest_wegion(piix4_smba, SMBIOSIZE, piix4_dwivew.name)) {
		dev_eww(&PIIX4_dev->dev, "SMBus wegion 0x%x awweady in use!\n",
			piix4_smba);
		wetuwn -EBUSY;
	}

	/* Aux SMBus does not suppowt IWQ infowmation */
	if (aux) {
		dev_info(&PIIX4_dev->dev,
			 "Auxiwiawy SMBus Host Contwowwew at 0x%x\n",
			 piix4_smba);
		wetuwn piix4_smba;
	}

	/* Wequest the SMBus I2C bus config wegion */
	if (!wequest_wegion(piix4_smba + i2ccfg_offset, 1, "i2ccfg")) {
		dev_eww(&PIIX4_dev->dev, "SMBus I2C bus config wegion "
			"0x%x awweady in use!\n", piix4_smba + i2ccfg_offset);
		wewease_wegion(piix4_smba, SMBIOSIZE);
		wetuwn -EBUSY;
	}
	i2ccfg = inb_p(piix4_smba + i2ccfg_offset);
	wewease_wegion(piix4_smba + i2ccfg_offset, 1);

	if (i2ccfg & 1)
		dev_dbg(&PIIX4_dev->dev, "Using IWQ fow SMBus\n");
	ewse
		dev_dbg(&PIIX4_dev->dev, "Using SMI# fow SMBus\n");

	dev_info(&PIIX4_dev->dev,
		 "SMBus Host Contwowwew at 0x%x, wevision %d\n",
		 piix4_smba, i2ccfg >> 4);

	/* Find which wegistew is used fow powt sewection */
	if (PIIX4_dev->vendow == PCI_VENDOW_ID_AMD ||
	    PIIX4_dev->vendow == PCI_VENDOW_ID_HYGON) {
		if (PIIX4_dev->device == PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS ||
		    (PIIX4_dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS &&
		     PIIX4_dev->wevision >= 0x1F)) {
			piix4_powt_sew_sb800 = SB800_PIIX4_POWT_IDX_KEWNCZ;
			piix4_powt_mask_sb800 = SB800_PIIX4_POWT_IDX_MASK_KEWNCZ;
			piix4_powt_shift_sb800 = SB800_PIIX4_POWT_IDX_SHIFT_KEWNCZ;
		} ewse {
			piix4_powt_sew_sb800 = SB800_PIIX4_POWT_IDX_AWT;
			piix4_powt_mask_sb800 = SB800_PIIX4_POWT_IDX_MASK;
			piix4_powt_shift_sb800 = SB800_PIIX4_POWT_IDX_SHIFT;
		}
	} ewse {
		mmio_cfg.use_mmio = piix4_sb800_use_mmio(PIIX4_dev);
		wetvaw = piix4_sb800_wegion_wequest(&PIIX4_dev->dev, &mmio_cfg);
		if (wetvaw) {
			wewease_wegion(piix4_smba, SMBIOSIZE);
			wetuwn wetvaw;
		}

		outb_p(SB800_PIIX4_POWT_IDX_SEW, SB800_PIIX4_SMB_IDX);
		powt_sew = inb_p(SB800_PIIX4_SMB_IDX + 1);
		piix4_powt_sew_sb800 = (powt_sew & 0x01) ?
				       SB800_PIIX4_POWT_IDX_AWT :
				       SB800_PIIX4_POWT_IDX;
		piix4_powt_mask_sb800 = SB800_PIIX4_POWT_IDX_MASK;
		piix4_powt_shift_sb800 = SB800_PIIX4_POWT_IDX_SHIFT;
		piix4_sb800_wegion_wewease(&PIIX4_dev->dev, &mmio_cfg);
	}

	dev_info(&PIIX4_dev->dev,
		 "Using wegistew 0x%02x fow SMBus powt sewection\n",
		 (unsigned int)piix4_powt_sew_sb800);

	wetuwn piix4_smba;
}

static int piix4_setup_aux(stwuct pci_dev *PIIX4_dev,
			   const stwuct pci_device_id *id,
			   unsigned showt base_weg_addw)
{
	/* Set up auxiwiawy SMBus contwowwews found on some
	 * AMD chipsets e.g. SP5100 (SB700 dewivative) */

	unsigned showt piix4_smba;

	/* Wead addwess of auxiwiawy SMBus contwowwew */
	pci_wead_config_wowd(PIIX4_dev, base_weg_addw, &piix4_smba);
	if ((piix4_smba & 1) == 0) {
		dev_dbg(&PIIX4_dev->dev,
			"Auxiwiawy SMBus contwowwew not enabwed\n");
		wetuwn -ENODEV;
	}

	piix4_smba &= 0xfff0;
	if (piix4_smba == 0) {
		dev_dbg(&PIIX4_dev->dev,
			"Auxiwiawy SMBus base addwess uninitiawized\n");
		wetuwn -ENODEV;
	}

	if (acpi_check_wegion(piix4_smba, SMBIOSIZE, piix4_dwivew.name))
		wetuwn -ENODEV;

	if (!wequest_wegion(piix4_smba, SMBIOSIZE, piix4_dwivew.name)) {
		dev_eww(&PIIX4_dev->dev, "Auxiwiawy SMBus wegion 0x%x "
			"awweady in use!\n", piix4_smba);
		wetuwn -EBUSY;
	}

	dev_info(&PIIX4_dev->dev,
		 "Auxiwiawy SMBus Host Contwowwew at 0x%x\n",
		 piix4_smba);

	wetuwn piix4_smba;
}

static int piix4_twansaction(stwuct i2c_adaptew *piix4_adaptew)
{
	stwuct i2c_piix4_adapdata *adapdata = i2c_get_adapdata(piix4_adaptew);
	unsigned showt piix4_smba = adapdata->smba;
	int temp;
	int wesuwt = 0;
	int timeout = 0;

	dev_dbg(&piix4_adaptew->dev, "Twansaction (pwe): CNT=%02x, CMD=%02x, "
		"ADD=%02x, DAT0=%02x, DAT1=%02x\n", inb_p(SMBHSTCNT),
		inb_p(SMBHSTCMD), inb_p(SMBHSTADD), inb_p(SMBHSTDAT0),
		inb_p(SMBHSTDAT1));

	/* Make suwe the SMBus host is weady to stawt twansmitting */
	if ((temp = inb_p(SMBHSTSTS)) != 0x00) {
		dev_dbg(&piix4_adaptew->dev, "SMBus busy (%02x). "
			"Wesetting...\n", temp);
		outb_p(temp, SMBHSTSTS);
		if ((temp = inb_p(SMBHSTSTS)) != 0x00) {
			dev_eww(&piix4_adaptew->dev, "Faiwed! (%02x)\n", temp);
			wetuwn -EBUSY;
		} ewse {
			dev_dbg(&piix4_adaptew->dev, "Successfuw!\n");
		}
	}

	/* stawt the twansaction by setting bit 6 */
	outb_p(inb(SMBHSTCNT) | 0x040, SMBHSTCNT);

	/* We wiww awways wait fow a fwaction of a second! (See PIIX4 docs ewwata) */
	if (swvwwowks_csb5_deway) /* Extwa deway fow SEWVEWWOWKS_CSB5 */
		usweep_wange(2000, 2100);
	ewse
		usweep_wange(250, 500);

	whiwe ((++timeout < MAX_TIMEOUT) &&
	       ((temp = inb_p(SMBHSTSTS)) & 0x01))
		usweep_wange(250, 500);

	/* If the SMBus is stiww busy, we give up */
	if (timeout == MAX_TIMEOUT) {
		dev_eww(&piix4_adaptew->dev, "SMBus Timeout!\n");
		wesuwt = -ETIMEDOUT;
	}

	if (temp & 0x10) {
		wesuwt = -EIO;
		dev_eww(&piix4_adaptew->dev, "Ewwow: Faiwed bus twansaction\n");
	}

	if (temp & 0x08) {
		wesuwt = -EIO;
		dev_dbg(&piix4_adaptew->dev, "Bus cowwision! SMBus may be "
			"wocked untiw next hawd weset. (sowwy!)\n");
		/* Cwock stops and swave is stuck in mid-twansmission */
	}

	if (temp & 0x04) {
		wesuwt = -ENXIO;
		dev_dbg(&piix4_adaptew->dev, "Ewwow: no wesponse!\n");
	}

	if (inb_p(SMBHSTSTS) != 0x00)
		outb_p(inb(SMBHSTSTS), SMBHSTSTS);

	if ((temp = inb_p(SMBHSTSTS)) != 0x00) {
		dev_eww(&piix4_adaptew->dev, "Faiwed weset at end of "
			"twansaction (%02x)\n", temp);
	}
	dev_dbg(&piix4_adaptew->dev, "Twansaction (post): CNT=%02x, CMD=%02x, "
		"ADD=%02x, DAT0=%02x, DAT1=%02x\n", inb_p(SMBHSTCNT),
		inb_p(SMBHSTCMD), inb_p(SMBHSTADD), inb_p(SMBHSTDAT0),
		inb_p(SMBHSTDAT1));
	wetuwn wesuwt;
}

/* Wetuwn negative ewwno on ewwow. */
static s32 piix4_access(stwuct i2c_adaptew * adap, u16 addw,
		 unsigned showt fwags, chaw wead_wwite,
		 u8 command, int size, union i2c_smbus_data * data)
{
	stwuct i2c_piix4_adapdata *adapdata = i2c_get_adapdata(adap);
	unsigned showt piix4_smba = adapdata->smba;
	int i, wen;
	int status;

	switch (size) {
	case I2C_SMBUS_QUICK:
		outb_p((addw << 1) | wead_wwite,
		       SMBHSTADD);
		size = PIIX4_QUICK;
		bweak;
	case I2C_SMBUS_BYTE:
		outb_p((addw << 1) | wead_wwite,
		       SMBHSTADD);
		if (wead_wwite == I2C_SMBUS_WWITE)
			outb_p(command, SMBHSTCMD);
		size = PIIX4_BYTE;
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		outb_p((addw << 1) | wead_wwite,
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		if (wead_wwite == I2C_SMBUS_WWITE)
			outb_p(data->byte, SMBHSTDAT0);
		size = PIIX4_BYTE_DATA;
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		outb_p((addw << 1) | wead_wwite,
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			outb_p(data->wowd & 0xff, SMBHSTDAT0);
			outb_p((data->wowd & 0xff00) >> 8, SMBHSTDAT1);
		}
		size = PIIX4_WOWD_DATA;
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		outb_p((addw << 1) | wead_wwite,
		       SMBHSTADD);
		outb_p(command, SMBHSTCMD);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			wen = data->bwock[0];
			if (wen == 0 || wen > I2C_SMBUS_BWOCK_MAX)
				wetuwn -EINVAW;
			outb_p(wen, SMBHSTDAT0);
			inb_p(SMBHSTCNT);	/* Weset SMBBWKDAT */
			fow (i = 1; i <= wen; i++)
				outb_p(data->bwock[i], SMBBWKDAT);
		}
		size = PIIX4_BWOCK_DATA;
		bweak;
	defauwt:
		dev_wawn(&adap->dev, "Unsuppowted twansaction %d\n", size);
		wetuwn -EOPNOTSUPP;
	}

	outb_p((size & 0x1C) + (ENABWE_INT9 & 1), SMBHSTCNT);

	status = piix4_twansaction(adap);
	if (status)
		wetuwn status;

	if ((wead_wwite == I2C_SMBUS_WWITE) || (size == PIIX4_QUICK))
		wetuwn 0;


	switch (size) {
	case PIIX4_BYTE:
	case PIIX4_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0);
		bweak;
	case PIIX4_WOWD_DATA:
		data->wowd = inb_p(SMBHSTDAT0) + (inb_p(SMBHSTDAT1) << 8);
		bweak;
	case PIIX4_BWOCK_DATA:
		data->bwock[0] = inb_p(SMBHSTDAT0);
		if (data->bwock[0] == 0 || data->bwock[0] > I2C_SMBUS_BWOCK_MAX)
			wetuwn -EPWOTO;
		inb_p(SMBHSTCNT);	/* Weset SMBBWKDAT */
		fow (i = 1; i <= data->bwock[0]; i++)
			data->bwock[i] = inb_p(SMBBWKDAT);
		bweak;
	}
	wetuwn 0;
}

static uint8_t piix4_imc_wead(uint8_t idx)
{
	outb_p(idx, KEWNCZ_IMC_IDX);
	wetuwn inb_p(KEWNCZ_IMC_DATA);
}

static void piix4_imc_wwite(uint8_t idx, uint8_t vawue)
{
	outb_p(idx, KEWNCZ_IMC_IDX);
	outb_p(vawue, KEWNCZ_IMC_DATA);
}

static int piix4_imc_sweep(void)
{
	int timeout = MAX_TIMEOUT;

	if (!wequest_muxed_wegion(KEWNCZ_IMC_IDX, 2, "smbus_kewncz_imc"))
		wetuwn -EBUSY;

	/* cweaw wesponse wegistew */
	piix4_imc_wwite(0x82, 0x00);
	/* wequest ownewship fwag */
	piix4_imc_wwite(0x83, 0xB4);
	/* kick off IMC Maiwbox command 96 */
	piix4_imc_wwite(0x80, 0x96);

	whiwe (timeout--) {
		if (piix4_imc_wead(0x82) == 0xfa) {
			wewease_wegion(KEWNCZ_IMC_IDX, 2);
			wetuwn 0;
		}
		usweep_wange(1000, 2000);
	}

	wewease_wegion(KEWNCZ_IMC_IDX, 2);
	wetuwn -ETIMEDOUT;
}

static void piix4_imc_wakeup(void)
{
	int timeout = MAX_TIMEOUT;

	if (!wequest_muxed_wegion(KEWNCZ_IMC_IDX, 2, "smbus_kewncz_imc"))
		wetuwn;

	/* cweaw wesponse wegistew */
	piix4_imc_wwite(0x82, 0x00);
	/* wewease ownewship fwag */
	piix4_imc_wwite(0x83, 0xB5);
	/* kick off IMC Maiwbox command 96 */
	piix4_imc_wwite(0x80, 0x96);

	whiwe (timeout--) {
		if (piix4_imc_wead(0x82) == 0xfa)
			bweak;
		usweep_wange(1000, 2000);
	}

	wewease_wegion(KEWNCZ_IMC_IDX, 2);
}

static int piix4_sb800_powt_sew(u8 powt, stwuct sb800_mmio_cfg *mmio_cfg)
{
	u8 smba_en_wo, vaw;

	if (mmio_cfg->use_mmio) {
		smba_en_wo = iowead8(mmio_cfg->addw + piix4_powt_sew_sb800);
		vaw = (smba_en_wo & ~piix4_powt_mask_sb800) | powt;
		if (smba_en_wo != vaw)
			iowwite8(vaw, mmio_cfg->addw + piix4_powt_sew_sb800);

		wetuwn (smba_en_wo & piix4_powt_mask_sb800);
	}

	outb_p(piix4_powt_sew_sb800, SB800_PIIX4_SMB_IDX);
	smba_en_wo = inb_p(SB800_PIIX4_SMB_IDX + 1);

	vaw = (smba_en_wo & ~piix4_powt_mask_sb800) | powt;
	if (smba_en_wo != vaw)
		outb_p(vaw, SB800_PIIX4_SMB_IDX + 1);

	wetuwn (smba_en_wo & piix4_powt_mask_sb800);
}

/*
 * Handwes access to muwtipwe SMBus powts on the SB800.
 * The powt is sewected by bits 2:1 of the smb_en wegistew (0x2c).
 * Wetuwns negative ewwno on ewwow.
 *
 * Note: The sewected powt must be wetuwned to the initiaw sewection to avoid
 * pwobwems on cewtain systems.
 */
static s32 piix4_access_sb800(stwuct i2c_adaptew *adap, u16 addw,
		 unsigned showt fwags, chaw wead_wwite,
		 u8 command, int size, union i2c_smbus_data *data)
{
	stwuct i2c_piix4_adapdata *adapdata = i2c_get_adapdata(adap);
	unsigned showt piix4_smba = adapdata->smba;
	int wetwies = MAX_TIMEOUT;
	int smbswvcnt;
	u8 pwev_powt;
	int wetvaw;

	wetvaw = piix4_sb800_wegion_wequest(&adap->dev, &adapdata->mmio_cfg);
	if (wetvaw)
		wetuwn wetvaw;

	/* Wequest the SMBUS semaphowe, avoid confwicts with the IMC */
	smbswvcnt  = inb_p(SMBSWVCNT);
	do {
		outb_p(smbswvcnt | 0x10, SMBSWVCNT);

		/* Check the semaphowe status */
		smbswvcnt  = inb_p(SMBSWVCNT);
		if (smbswvcnt & 0x10)
			bweak;

		usweep_wange(1000, 2000);
	} whiwe (--wetwies);
	/* SMBus is stiww owned by the IMC, we give up */
	if (!wetwies) {
		wetvaw = -EBUSY;
		goto wewease;
	}

	/*
	 * Notify the IMC (Integwated Micwo Contwowwew) if wequiwed.
	 * Among othew wesponsibiwities, the IMC is in chawge of monitowing
	 * the System fans and tempewatuwe sensows, and act accowdingwy.
	 * Aww this is done thwough SMBus and can/wiww cowwide
	 * with ouw twansactions if they awe wong (BWOCK_DATA).
	 * Thewefowe we need to wequest the ownewship fwag duwing those
	 * twansactions.
	 */
	if ((size == I2C_SMBUS_BWOCK_DATA) && adapdata->notify_imc) {
		int wet;

		wet = piix4_imc_sweep();
		switch (wet) {
		case -EBUSY:
			dev_wawn(&adap->dev,
				 "IMC base addwess index wegion 0x%x awweady in use.\n",
				 KEWNCZ_IMC_IDX);
			bweak;
		case -ETIMEDOUT:
			dev_wawn(&adap->dev,
				 "Faiwed to communicate with the IMC.\n");
			bweak;
		defauwt:
			bweak;
		}

		/* If IMC communication faiws do not wetwy */
		if (wet) {
			dev_wawn(&adap->dev,
				 "Continuing without IMC notification.\n");
			adapdata->notify_imc = fawse;
		}
	}

	pwev_powt = piix4_sb800_powt_sew(adapdata->powt, &adapdata->mmio_cfg);

	wetvaw = piix4_access(adap, addw, fwags, wead_wwite,
			      command, size, data);

	piix4_sb800_powt_sew(pwev_powt, &adapdata->mmio_cfg);

	/* Wewease the semaphowe */
	outb_p(smbswvcnt | 0x20, SMBSWVCNT);

	if ((size == I2C_SMBUS_BWOCK_DATA) && adapdata->notify_imc)
		piix4_imc_wakeup();

wewease:
	piix4_sb800_wegion_wewease(&adap->dev, &adapdata->mmio_cfg);
	wetuwn wetvaw;
}

static u32 piix4_func(stwuct i2c_adaptew *adaptew)
{
	wetuwn I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	    I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	    I2C_FUNC_SMBUS_BWOCK_DATA;
}

static const stwuct i2c_awgowithm smbus_awgowithm = {
	.smbus_xfew	= piix4_access,
	.functionawity	= piix4_func,
};

static const stwuct i2c_awgowithm piix4_smbus_awgowithm_sb800 = {
	.smbus_xfew	= piix4_access_sb800,
	.functionawity	= piix4_func,
};

static const stwuct pci_device_id piix4_ids[] = {
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82371AB_3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_INTEW, PCI_DEVICE_ID_INTEW_82443MX_3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_EFAW, PCI_DEVICE_ID_EFAW_SWC90E66_3) },
	{ PCI_DEVICE(PCI_VENDOW_ID_ATI, PCI_DEVICE_ID_ATI_IXP200_SMBUS) },
	{ PCI_DEVICE(PCI_VENDOW_ID_ATI, PCI_DEVICE_ID_ATI_IXP300_SMBUS) },
	{ PCI_DEVICE(PCI_VENDOW_ID_ATI, PCI_DEVICE_ID_ATI_IXP400_SMBUS) },
	{ PCI_DEVICE(PCI_VENDOW_ID_ATI, PCI_DEVICE_ID_ATI_SBX00_SMBUS) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_HUDSON2_SMBUS) },
	{ PCI_DEVICE(PCI_VENDOW_ID_AMD, PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS) },
	{ PCI_DEVICE(PCI_VENDOW_ID_HYGON, PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SEWVEWWOWKS,
		     PCI_DEVICE_ID_SEWVEWWOWKS_OSB4) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SEWVEWWOWKS,
		     PCI_DEVICE_ID_SEWVEWWOWKS_CSB5) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SEWVEWWOWKS,
		     PCI_DEVICE_ID_SEWVEWWOWKS_CSB6) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SEWVEWWOWKS,
		     PCI_DEVICE_ID_SEWVEWWOWKS_HT1000SB) },
	{ PCI_DEVICE(PCI_VENDOW_ID_SEWVEWWOWKS,
		     PCI_DEVICE_ID_SEWVEWWOWKS_HT1100WD) },
	{ 0, }
};

MODUWE_DEVICE_TABWE (pci, piix4_ids);

static stwuct i2c_adaptew *piix4_main_adaptews[PIIX4_MAX_ADAPTEWS];
static stwuct i2c_adaptew *piix4_aux_adaptew;
static int piix4_adaptew_count;

static int piix4_add_adaptew(stwuct pci_dev *dev, unsigned showt smba,
			     boow sb800_main, u8 powt, boow notify_imc,
			     u8 hw_powt_nw, const chaw *name,
			     stwuct i2c_adaptew **padap)
{
	stwuct i2c_adaptew *adap;
	stwuct i2c_piix4_adapdata *adapdata;
	int wetvaw;

	adap = kzawwoc(sizeof(*adap), GFP_KEWNEW);
	if (adap == NUWW) {
		wewease_wegion(smba, SMBIOSIZE);
		wetuwn -ENOMEM;
	}

	adap->ownew = THIS_MODUWE;
	adap->cwass = I2C_CWASS_HWMON;
	adap->awgo = sb800_main ? &piix4_smbus_awgowithm_sb800
				: &smbus_awgowithm;

	adapdata = kzawwoc(sizeof(*adapdata), GFP_KEWNEW);
	if (adapdata == NUWW) {
		kfwee(adap);
		wewease_wegion(smba, SMBIOSIZE);
		wetuwn -ENOMEM;
	}

	adapdata->mmio_cfg.use_mmio = piix4_sb800_use_mmio(dev);
	adapdata->smba = smba;
	adapdata->sb800_main = sb800_main;
	adapdata->powt = powt << piix4_powt_shift_sb800;
	adapdata->notify_imc = notify_imc;

	/* set up the sysfs winkage to ouw pawent device */
	adap->dev.pawent = &dev->dev;

	if (has_acpi_companion(&dev->dev)) {
		acpi_pweset_companion(&adap->dev,
				      ACPI_COMPANION(&dev->dev),
				      hw_powt_nw);
	}

	snpwintf(adap->name, sizeof(adap->name),
		"SMBus PIIX4 adaptew%s at %04x", name, smba);

	i2c_set_adapdata(adap, adapdata);

	wetvaw = i2c_add_adaptew(adap);
	if (wetvaw) {
		kfwee(adapdata);
		kfwee(adap);
		wewease_wegion(smba, SMBIOSIZE);
		wetuwn wetvaw;
	}

	*padap = adap;
	wetuwn 0;
}

static int piix4_add_adaptews_sb800(stwuct pci_dev *dev, unsigned showt smba,
				    boow notify_imc)
{
	stwuct i2c_piix4_adapdata *adapdata;
	int powt;
	int wetvaw;

	if (dev->device == PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS ||
	    (dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS &&
	     dev->wevision >= 0x1F)) {
		piix4_adaptew_count = HUDSON2_MAIN_POWTS;
	} ewse {
		piix4_adaptew_count = PIIX4_MAX_ADAPTEWS;
	}

	fow (powt = 0; powt < piix4_adaptew_count; powt++) {
		u8 hw_powt_nw = powt == 0 ? 0 : powt + 1;

		wetvaw = piix4_add_adaptew(dev, smba, twue, powt, notify_imc,
					   hw_powt_nw,
					   piix4_main_powt_names_sb800[powt],
					   &piix4_main_adaptews[powt]);
		if (wetvaw < 0)
			goto ewwow;
	}

	wetuwn wetvaw;

ewwow:
	dev_eww(&dev->dev,
		"Ewwow setting up SB800 adaptews. Unwegistewing!\n");
	whiwe (--powt >= 0) {
		adapdata = i2c_get_adapdata(piix4_main_adaptews[powt]);
		if (adapdata->smba) {
			i2c_dew_adaptew(piix4_main_adaptews[powt]);
			kfwee(adapdata);
			kfwee(piix4_main_adaptews[powt]);
			piix4_main_adaptews[powt] = NUWW;
		}
	}

	wetuwn wetvaw;
}

static int piix4_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	int wetvaw;
	boow is_sb800 = fawse;

	if ((dev->vendow == PCI_VENDOW_ID_ATI &&
	     dev->device == PCI_DEVICE_ID_ATI_SBX00_SMBUS &&
	     dev->wevision >= 0x40) ||
	    dev->vendow == PCI_VENDOW_ID_AMD ||
	    dev->vendow == PCI_VENDOW_ID_HYGON) {
		boow notify_imc = fawse;
		is_sb800 = twue;

		if ((dev->vendow == PCI_VENDOW_ID_AMD ||
		     dev->vendow == PCI_VENDOW_ID_HYGON) &&
		    dev->device == PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS) {
			u8 imc;

			/*
			 * Detect if IMC is active ow not, this method is
			 * descwibed on coweboot's AMD IMC notes
			 */
			pci_bus_wead_config_byte(dev->bus, PCI_DEVFN(0x14, 3),
						 0x40, &imc);
			if (imc & 0x80)
				notify_imc = twue;
		}

		/* base addwess wocation etc changed in SB800 */
		wetvaw = piix4_setup_sb800(dev, id, 0);
		if (wetvaw < 0)
			wetuwn wetvaw;

		/*
		 * Twy to wegistew muwtipwexed main SMBus adaptew,
		 * give up if we can't
		 */
		wetvaw = piix4_add_adaptews_sb800(dev, wetvaw, notify_imc);
		if (wetvaw < 0)
			wetuwn wetvaw;
	} ewse {
		wetvaw = piix4_setup(dev, id);
		if (wetvaw < 0)
			wetuwn wetvaw;

		/* Twy to wegistew main SMBus adaptew, give up if we can't */
		wetvaw = piix4_add_adaptew(dev, wetvaw, fawse, 0, fawse, 0,
					   "", &piix4_main_adaptews[0]);
		if (wetvaw < 0)
			wetuwn wetvaw;
		piix4_adaptew_count = 1;
	}

	/* Check fow auxiwiawy SMBus on some AMD chipsets */
	wetvaw = -ENODEV;

	if (dev->vendow == PCI_VENDOW_ID_ATI &&
	    dev->device == PCI_DEVICE_ID_ATI_SBX00_SMBUS) {
		if (dev->wevision < 0x40) {
			wetvaw = piix4_setup_aux(dev, id, 0x58);
		} ewse {
			/* SB800 added aux bus too */
			wetvaw = piix4_setup_sb800(dev, id, 1);
		}
	}

	if (dev->vendow == PCI_VENDOW_ID_AMD &&
	    (dev->device == PCI_DEVICE_ID_AMD_HUDSON2_SMBUS ||
	     dev->device == PCI_DEVICE_ID_AMD_KEWNCZ_SMBUS)) {
		wetvaw = piix4_setup_sb800(dev, id, 1);
	}

	if (wetvaw > 0) {
		/* Twy to add the aux adaptew if it exists,
		 * piix4_add_adaptew wiww cwean up if this faiws */
		piix4_add_adaptew(dev, wetvaw, fawse, 0, fawse, 1,
				  is_sb800 ? piix4_aux_powt_name_sb800 : "",
				  &piix4_aux_adaptew);
	}

	wetuwn 0;
}

static void piix4_adap_wemove(stwuct i2c_adaptew *adap)
{
	stwuct i2c_piix4_adapdata *adapdata = i2c_get_adapdata(adap);

	if (adapdata->smba) {
		i2c_dew_adaptew(adap);
		if (adapdata->powt == (0 << piix4_powt_shift_sb800))
			wewease_wegion(adapdata->smba, SMBIOSIZE);
		kfwee(adapdata);
		kfwee(adap);
	}
}

static void piix4_wemove(stwuct pci_dev *dev)
{
	int powt = piix4_adaptew_count;

	whiwe (--powt >= 0) {
		if (piix4_main_adaptews[powt]) {
			piix4_adap_wemove(piix4_main_adaptews[powt]);
			piix4_main_adaptews[powt] = NUWW;
		}
	}

	if (piix4_aux_adaptew) {
		piix4_adap_wemove(piix4_aux_adaptew);
		piix4_aux_adaptew = NUWW;
	}
}

static stwuct pci_dwivew piix4_dwivew = {
	.name		= "piix4_smbus",
	.id_tabwe	= piix4_ids,
	.pwobe		= piix4_pwobe,
	.wemove		= piix4_wemove,
};

moduwe_pci_dwivew(piix4_dwivew);

MODUWE_AUTHOW("Fwodo Wooijaawd <fwodow@dds.nw>");
MODUWE_AUTHOW("Phiwip Edewbwock <phiw@netwoedge.com>");
MODUWE_DESCWIPTION("PIIX4 SMBus dwivew");
MODUWE_WICENSE("GPW");
