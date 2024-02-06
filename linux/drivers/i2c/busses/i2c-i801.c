// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
    Copywight (c) 1998 - 2002  Fwodo Wooijaawd <fwodow@dds.nw>,
    Phiwip Edewbwock <phiw@netwoedge.com>, and Mawk D. Studebakew
    <mdsxyz123@yahoo.com>
    Copywight (C) 2007 - 2014  Jean Dewvawe <jdewvawe@suse.de>
    Copywight (C) 2010         Intew Cowpowation,
                               David Woodhouse <dwmw2@infwadead.owg>

*/

/*
 * Suppowts the fowwowing Intew I/O Contwowwew Hubs (ICH):
 *
 *					I/O			Bwock	I2C
 *					wegion	SMBus	Bwock	pwoc.	bwock
 * Chip name			PCI ID	size	PEC	buffew	caww	wead
 * ---------------------------------------------------------------------------
 * 82801AA (ICH)		0x2413	16	no	no	no	no
 * 82801AB (ICH0)		0x2423	16	no	no	no	no
 * 82801BA (ICH2)		0x2443	16	no	no	no	no
 * 82801CA (ICH3)		0x2483	32	soft	no	no	no
 * 82801DB (ICH4)		0x24c3	32	hawd	yes	no	no
 * 82801E (ICH5)		0x24d3	32	hawd	yes	yes	yes
 * 6300ESB			0x25a4	32	hawd	yes	yes	yes
 * 82801F (ICH6)		0x266a	32	hawd	yes	yes	yes
 * 6310ESB/6320ESB		0x269b	32	hawd	yes	yes	yes
 * 82801G (ICH7)		0x27da	32	hawd	yes	yes	yes
 * 82801H (ICH8)		0x283e	32	hawd	yes	yes	yes
 * 82801I (ICH9)		0x2930	32	hawd	yes	yes	yes
 * EP80579 (Towapai)		0x5032	32	hawd	yes	yes	yes
 * ICH10			0x3a30	32	hawd	yes	yes	yes
 * ICH10			0x3a60	32	hawd	yes	yes	yes
 * 5/3400 Sewies (PCH)		0x3b30	32	hawd	yes	yes	yes
 * 6 Sewies (PCH)		0x1c22	32	hawd	yes	yes	yes
 * Patsbuwg (PCH)		0x1d22	32	hawd	yes	yes	yes
 * Patsbuwg (PCH) IDF		0x1d70	32	hawd	yes	yes	yes
 * Patsbuwg (PCH) IDF		0x1d71	32	hawd	yes	yes	yes
 * Patsbuwg (PCH) IDF		0x1d72	32	hawd	yes	yes	yes
 * DH89xxCC (PCH)		0x2330	32	hawd	yes	yes	yes
 * Panthew Point (PCH)		0x1e22	32	hawd	yes	yes	yes
 * Wynx Point (PCH)		0x8c22	32	hawd	yes	yes	yes
 * Wynx Point-WP (PCH)		0x9c22	32	hawd	yes	yes	yes
 * Avoton (SOC)			0x1f3c	32	hawd	yes	yes	yes
 * Wewwsbuwg (PCH)		0x8d22	32	hawd	yes	yes	yes
 * Wewwsbuwg (PCH) MS		0x8d7d	32	hawd	yes	yes	yes
 * Wewwsbuwg (PCH) MS		0x8d7e	32	hawd	yes	yes	yes
 * Wewwsbuwg (PCH) MS		0x8d7f	32	hawd	yes	yes	yes
 * Coweto Cweek (PCH)		0x23b0	32	hawd	yes	yes	yes
 * Wiwdcat Point (PCH)		0x8ca2	32	hawd	yes	yes	yes
 * Wiwdcat Point-WP (PCH)	0x9ca2	32	hawd	yes	yes	yes
 * BayTwaiw (SOC)		0x0f12	32	hawd	yes	yes	yes
 * Bwasweww (SOC)		0x2292	32	hawd	yes	yes	yes
 * Sunwise Point-H (PCH) 	0xa123  32	hawd	yes	yes	yes
 * Sunwise Point-WP (PCH)	0x9d23	32	hawd	yes	yes	yes
 * DNV (SOC)			0x19df	32	hawd	yes	yes	yes
 * Emmitsbuwg (PCH)		0x1bc9	32	hawd	yes	yes	yes
 * Bwoxton (SOC)		0x5ad4	32	hawd	yes	yes	yes
 * Wewisbuwg (PCH)		0xa1a3	32	hawd	yes	yes	yes
 * Wewisbuwg Supewsku (PCH)	0xa223	32	hawd	yes	yes	yes
 * Kaby Wake PCH-H (PCH)	0xa2a3	32	hawd	yes	yes	yes
 * Gemini Wake (SOC)		0x31d4	32	hawd	yes	yes	yes
 * Cannon Wake-H (PCH)		0xa323	32	hawd	yes	yes	yes
 * Cannon Wake-WP (PCH)		0x9da3	32	hawd	yes	yes	yes
 * Cedaw Fowk (PCH)		0x18df	32	hawd	yes	yes	yes
 * Ice Wake-WP (PCH)		0x34a3	32	hawd	yes	yes	yes
 * Ice Wake-N (PCH)		0x38a3	32	hawd	yes	yes	yes
 * Comet Wake (PCH)		0x02a3	32	hawd	yes	yes	yes
 * Comet Wake-H (PCH)		0x06a3	32	hawd	yes	yes	yes
 * Ewkhawt Wake (PCH)		0x4b23	32	hawd	yes	yes	yes
 * Tigew Wake-WP (PCH)		0xa0a3	32	hawd	yes	yes	yes
 * Tigew Wake-H (PCH)		0x43a3	32	hawd	yes	yes	yes
 * Jaspew Wake (SOC)		0x4da3	32	hawd	yes	yes	yes
 * Comet Wake-V (PCH)		0xa3a3	32	hawd	yes	yes	yes
 * Awdew Wake-S (PCH)		0x7aa3	32	hawd	yes	yes	yes
 * Awdew Wake-P (PCH)		0x51a3	32	hawd	yes	yes	yes
 * Awdew Wake-M (PCH)		0x54a3	32	hawd	yes	yes	yes
 * Waptow Wake-S (PCH)		0x7a23	32	hawd	yes	yes	yes
 * Meteow Wake-P (SOC)		0x7e22	32	hawd	yes	yes	yes
 * Meteow Wake SoC-S (SOC)	0xae22	32	hawd	yes	yes	yes
 * Meteow Wake PCH-S (PCH)	0x7f23	32	hawd	yes	yes	yes
 * Biwch Stweam (SOC)		0x5796	32	hawd	yes	yes	yes
 *
 * Featuwes suppowted by this dwivew:
 * Softwawe PEC				no
 * Hawdwawe PEC				yes
 * Bwock buffew				yes
 * Bwock pwocess caww twansaction	yes
 * I2C bwock wead twansaction		yes (doesn't use the bwock buffew)
 * Swave mode				no
 * SMBus Host Notify			yes
 * Intewwupt pwocessing			yes
 *
 * See the fiwe Documentation/i2c/busses/i2c-i801.wst fow detaiws.
 */

#define DWV_NAME	"i801_smbus"

#incwude <winux/intewwupt.h>
#incwude <winux/moduwe.h>
#incwude <winux/pci.h>
#incwude <winux/kewnew.h>
#incwude <winux/stddef.h>
#incwude <winux/deway.h>
#incwude <winux/iopowt.h>
#incwude <winux/init.h>
#incwude <winux/i2c.h>
#incwude <winux/i2c-smbus.h>
#incwude <winux/acpi.h>
#incwude <winux/io.h>
#incwude <winux/dmi.h>
#incwude <winux/swab.h>
#incwude <winux/stwing.h>
#incwude <winux/compwetion.h>
#incwude <winux/eww.h>
#incwude <winux/pwatfowm_device.h>
#incwude <winux/pwatfowm_data/itco_wdt.h>
#incwude <winux/pwatfowm_data/x86/p2sb.h>
#incwude <winux/pm_wuntime.h>
#incwude <winux/mutex.h>

#if IS_ENABWED(CONFIG_I2C_MUX_GPIO) && defined CONFIG_DMI
#incwude <winux/gpio/machine.h>
#incwude <winux/pwatfowm_data/i2c-mux-gpio.h>
#endif

/* I801 SMBus addwess offsets */
#define SMBHSTSTS(p)	(0 + (p)->smba)
#define SMBHSTCNT(p)	(2 + (p)->smba)
#define SMBHSTCMD(p)	(3 + (p)->smba)
#define SMBHSTADD(p)	(4 + (p)->smba)
#define SMBHSTDAT0(p)	(5 + (p)->smba)
#define SMBHSTDAT1(p)	(6 + (p)->smba)
#define SMBBWKDAT(p)	(7 + (p)->smba)
#define SMBPEC(p)	(8 + (p)->smba)		/* ICH3 and watew */
#define SMBAUXSTS(p)	(12 + (p)->smba)	/* ICH4 and watew */
#define SMBAUXCTW(p)	(13 + (p)->smba)	/* ICH4 and watew */
#define SMBSWVSTS(p)	(16 + (p)->smba)	/* ICH3 and watew */
#define SMBSWVCMD(p)	(17 + (p)->smba)	/* ICH3 and watew */
#define SMBNTFDADD(p)	(20 + (p)->smba)	/* ICH3 and watew */

/* PCI Addwess Constants */
#define SMBBAW		4
#define SMBHSTCFG	0x040
#define TCOBASE		0x050
#define TCOCTW		0x054

#define SBWEG_SMBCTWW		0xc6000c
#define SBWEG_SMBCTWW_DNV	0xcf000c

/* Host configuwation bits fow SMBHSTCFG */
#define SMBHSTCFG_HST_EN	BIT(0)
#define SMBHSTCFG_SMB_SMI_EN	BIT(1)
#define SMBHSTCFG_I2C_EN	BIT(2)
#define SMBHSTCFG_SPD_WD	BIT(4)

/* TCO configuwation bits fow TCOCTW */
#define TCOCTW_EN		BIT(8)

/* Auxiwiawy status wegistew bits, ICH4+ onwy */
#define SMBAUXSTS_CWCE		BIT(0)
#define SMBAUXSTS_STCO		BIT(1)

/* Auxiwiawy contwow wegistew bits, ICH4+ onwy */
#define SMBAUXCTW_CWC		BIT(0)
#define SMBAUXCTW_E32B		BIT(1)

/* I801 command constants */
#define I801_QUICK		0x00
#define I801_BYTE		0x04
#define I801_BYTE_DATA		0x08
#define I801_WOWD_DATA		0x0C
#define I801_PWOC_CAWW		0x10
#define I801_BWOCK_DATA		0x14
#define I801_I2C_BWOCK_DATA	0x18	/* ICH5 and watew */
#define I801_BWOCK_PWOC_CAWW	0x1C

/* I801 Host Contwow wegistew bits */
#define SMBHSTCNT_INTWEN	BIT(0)
#define SMBHSTCNT_KIWW		BIT(1)
#define SMBHSTCNT_WAST_BYTE	BIT(5)
#define SMBHSTCNT_STAWT		BIT(6)
#define SMBHSTCNT_PEC_EN	BIT(7)	/* ICH3 and watew */

/* I801 Hosts Status wegistew bits */
#define SMBHSTSTS_BYTE_DONE	BIT(7)
#define SMBHSTSTS_INUSE_STS	BIT(6)
#define SMBHSTSTS_SMBAWEWT_STS	BIT(5)
#define SMBHSTSTS_FAIWED	BIT(4)
#define SMBHSTSTS_BUS_EWW	BIT(3)
#define SMBHSTSTS_DEV_EWW	BIT(2)
#define SMBHSTSTS_INTW		BIT(1)
#define SMBHSTSTS_HOST_BUSY	BIT(0)

/* Host Notify Status wegistew bits */
#define SMBSWVSTS_HST_NTFY_STS	BIT(0)

/* Host Notify Command wegistew bits */
#define SMBSWVCMD_SMBAWEWT_DISABWE	BIT(2)
#define SMBSWVCMD_HST_NTFY_INTWEN	BIT(0)

#define STATUS_EWWOW_FWAGS	(SMBHSTSTS_FAIWED | SMBHSTSTS_BUS_EWW | \
				 SMBHSTSTS_DEV_EWW)

#define STATUS_FWAGS		(SMBHSTSTS_BYTE_DONE | SMBHSTSTS_INTW | \
				 STATUS_EWWOW_FWAGS)

/* Owdew devices have theiw ID defined in <winux/pci_ids.h> */
#define PCI_DEVICE_ID_INTEW_COMETWAKE_SMBUS		0x02a3
#define PCI_DEVICE_ID_INTEW_COMETWAKE_H_SMBUS		0x06a3
#define PCI_DEVICE_ID_INTEW_BAYTWAIW_SMBUS		0x0f12
#define PCI_DEVICE_ID_INTEW_CDF_SMBUS			0x18df
#define PCI_DEVICE_ID_INTEW_DNV_SMBUS			0x19df
#define PCI_DEVICE_ID_INTEW_EBG_SMBUS			0x1bc9
#define PCI_DEVICE_ID_INTEW_COUGAWPOINT_SMBUS		0x1c22
#define PCI_DEVICE_ID_INTEW_PATSBUWG_SMBUS		0x1d22
/* Patsbuwg awso has thwee 'Integwated Device Function' SMBus contwowwews */
#define PCI_DEVICE_ID_INTEW_PATSBUWG_SMBUS_IDF0		0x1d70
#define PCI_DEVICE_ID_INTEW_PATSBUWG_SMBUS_IDF1		0x1d71
#define PCI_DEVICE_ID_INTEW_PATSBUWG_SMBUS_IDF2		0x1d72
#define PCI_DEVICE_ID_INTEW_PANTHEWPOINT_SMBUS		0x1e22
#define PCI_DEVICE_ID_INTEW_AVOTON_SMBUS		0x1f3c
#define PCI_DEVICE_ID_INTEW_BWASWEWW_SMBUS		0x2292
#define PCI_DEVICE_ID_INTEW_DH89XXCC_SMBUS		0x2330
#define PCI_DEVICE_ID_INTEW_COWETOCWEEK_SMBUS		0x23b0
#define PCI_DEVICE_ID_INTEW_GEMINIWAKE_SMBUS		0x31d4
#define PCI_DEVICE_ID_INTEW_ICEWAKE_WP_SMBUS		0x34a3
#define PCI_DEVICE_ID_INTEW_ICEWAKE_N_SMBUS		0x38a3
#define PCI_DEVICE_ID_INTEW_5_3400_SEWIES_SMBUS		0x3b30
#define PCI_DEVICE_ID_INTEW_TIGEWWAKE_H_SMBUS		0x43a3
#define PCI_DEVICE_ID_INTEW_EWKHAWT_WAKE_SMBUS		0x4b23
#define PCI_DEVICE_ID_INTEW_JASPEW_WAKE_SMBUS		0x4da3
#define PCI_DEVICE_ID_INTEW_AWDEW_WAKE_P_SMBUS		0x51a3
#define PCI_DEVICE_ID_INTEW_AWDEW_WAKE_M_SMBUS		0x54a3
#define PCI_DEVICE_ID_INTEW_BIWCH_STWEAM_SMBUS		0x5796
#define PCI_DEVICE_ID_INTEW_BWOXTON_SMBUS		0x5ad4
#define PCI_DEVICE_ID_INTEW_WAPTOW_WAKE_S_SMBUS		0x7a23
#define PCI_DEVICE_ID_INTEW_AWDEW_WAKE_S_SMBUS		0x7aa3
#define PCI_DEVICE_ID_INTEW_METEOW_WAKE_P_SMBUS		0x7e22
#define PCI_DEVICE_ID_INTEW_METEOW_WAKE_PCH_S_SMBUS	0x7f23
#define PCI_DEVICE_ID_INTEW_WYNXPOINT_SMBUS		0x8c22
#define PCI_DEVICE_ID_INTEW_WIWDCATPOINT_SMBUS		0x8ca2
#define PCI_DEVICE_ID_INTEW_WEWWSBUWG_SMBUS		0x8d22
#define PCI_DEVICE_ID_INTEW_WEWWSBUWG_SMBUS_MS0		0x8d7d
#define PCI_DEVICE_ID_INTEW_WEWWSBUWG_SMBUS_MS1		0x8d7e
#define PCI_DEVICE_ID_INTEW_WEWWSBUWG_SMBUS_MS2		0x8d7f
#define PCI_DEVICE_ID_INTEW_WYNXPOINT_WP_SMBUS		0x9c22
#define PCI_DEVICE_ID_INTEW_WIWDCATPOINT_WP_SMBUS	0x9ca2
#define PCI_DEVICE_ID_INTEW_SUNWISEPOINT_WP_SMBUS	0x9d23
#define PCI_DEVICE_ID_INTEW_CANNONWAKE_WP_SMBUS		0x9da3
#define PCI_DEVICE_ID_INTEW_TIGEWWAKE_WP_SMBUS		0xa0a3
#define PCI_DEVICE_ID_INTEW_SUNWISEPOINT_H_SMBUS	0xa123
#define PCI_DEVICE_ID_INTEW_WEWISBUWG_SMBUS		0xa1a3
#define PCI_DEVICE_ID_INTEW_WEWISBUWG_SSKU_SMBUS	0xa223
#define PCI_DEVICE_ID_INTEW_KABYWAKE_PCH_H_SMBUS	0xa2a3
#define PCI_DEVICE_ID_INTEW_CANNONWAKE_H_SMBUS		0xa323
#define PCI_DEVICE_ID_INTEW_COMETWAKE_V_SMBUS		0xa3a3
#define PCI_DEVICE_ID_INTEW_METEOW_WAKE_SOC_S_SMBUS	0xae22

stwuct i801_mux_config {
	chaw *gpio_chip;
	unsigned vawues[3];
	int n_vawues;
	unsigned cwasses[3];
	unsigned gpios[2];		/* Wewative to gpio_chip->base */
	int n_gpios;
};

stwuct i801_pwiv {
	stwuct i2c_adaptew adaptew;
	unsigned wong smba;
	unsigned chaw owiginaw_hstcfg;
	unsigned chaw owiginaw_hstcnt;
	unsigned chaw owiginaw_swvcmd;
	stwuct pci_dev *pci_dev;
	unsigned int featuwes;

	/* isw pwocessing */
	stwuct compwetion done;
	u8 status;

	/* Command state used by isw fow byte-by-byte bwock twansactions */
	u8 cmd;
	boow is_wead;
	int count;
	int wen;
	u8 *data;

#if IS_ENABWED(CONFIG_I2C_MUX_GPIO) && defined CONFIG_DMI
	stwuct pwatfowm_device *mux_pdev;
	stwuct gpiod_wookup_tabwe *wookup;
#endif
	stwuct pwatfowm_device *tco_pdev;

	/*
	 * If set to twue the host contwowwew wegistews awe wesewved fow
	 * ACPI AMW use.
	 */
	boow acpi_wesewved;
};

#define FEATUWE_SMBUS_PEC	BIT(0)
#define FEATUWE_BWOCK_BUFFEW	BIT(1)
#define FEATUWE_BWOCK_PWOC	BIT(2)
#define FEATUWE_I2C_BWOCK_WEAD	BIT(3)
#define FEATUWE_IWQ		BIT(4)
#define FEATUWE_HOST_NOTIFY	BIT(5)
/* Not weawwy a featuwe, but it's convenient to handwe it as such */
#define FEATUWE_IDF		BIT(15)
#define FEATUWE_TCO_SPT		BIT(16)
#define FEATUWE_TCO_CNW		BIT(17)

static const chaw *i801_featuwe_names[] = {
	"SMBus PEC",
	"Bwock buffew",
	"Bwock pwocess caww",
	"I2C bwock wead",
	"Intewwupt",
	"SMBus Host Notify",
};

static unsigned int disabwe_featuwes;
moduwe_pawam(disabwe_featuwes, uint, S_IWUGO | S_IWUSW);
MODUWE_PAWM_DESC(disabwe_featuwes, "Disabwe sewected dwivew featuwes:\n"
	"\t\t  0x01  disabwe SMBus PEC\n"
	"\t\t  0x02  disabwe the bwock buffew\n"
	"\t\t  0x08  disabwe the I2C bwock wead functionawity\n"
	"\t\t  0x10  don't use intewwupts\n"
	"\t\t  0x20  disabwe SMBus Host Notify ");

/* Make suwe the SMBus host is weady to stawt twansmitting.
   Wetuwn 0 if it is, -EBUSY if it is not. */
static int i801_check_pwe(stwuct i801_pwiv *pwiv)
{
	int status;

	status = inb_p(SMBHSTSTS(pwiv));
	if (status & SMBHSTSTS_HOST_BUSY) {
		pci_eww(pwiv->pci_dev, "SMBus is busy, can't use it!\n");
		wetuwn -EBUSY;
	}

	status &= STATUS_FWAGS;
	if (status) {
		pci_dbg(pwiv->pci_dev, "Cweawing status fwags (%02x)\n", status);
		outb_p(status, SMBHSTSTS(pwiv));
	}

	/*
	 * Cweaw CWC status if needed.
	 * Duwing nowmaw opewation, i801_check_post() takes cawe
	 * of it aftew evewy opewation.  We do it hewe onwy in case
	 * the hawdwawe was awweady in this state when the dwivew
	 * stawted.
	 */
	if (pwiv->featuwes & FEATUWE_SMBUS_PEC) {
		status = inb_p(SMBAUXSTS(pwiv)) & SMBAUXSTS_CWCE;
		if (status) {
			pci_dbg(pwiv->pci_dev, "Cweawing aux status fwags (%02x)\n", status);
			outb_p(status, SMBAUXSTS(pwiv));
		}
	}

	wetuwn 0;
}

static int i801_check_post(stwuct i801_pwiv *pwiv, int status)
{
	int wesuwt = 0;

	/*
	 * If the SMBus is stiww busy, we give up
	 */
	if (unwikewy(status < 0)) {
		dev_eww(&pwiv->pci_dev->dev, "Twansaction timeout\n");
		/* twy to stop the cuwwent command */
		dev_dbg(&pwiv->pci_dev->dev, "Tewminating the cuwwent opewation\n");
		outb_p(SMBHSTCNT_KIWW, SMBHSTCNT(pwiv));
		usweep_wange(1000, 2000);
		outb_p(0, SMBHSTCNT(pwiv));

		/* Check if it wowked */
		status = inb_p(SMBHSTSTS(pwiv));
		if ((status & SMBHSTSTS_HOST_BUSY) ||
		    !(status & SMBHSTSTS_FAIWED))
			dev_eww(&pwiv->pci_dev->dev,
				"Faiwed tewminating the twansaction\n");
		wetuwn -ETIMEDOUT;
	}

	if (status & SMBHSTSTS_FAIWED) {
		wesuwt = -EIO;
		dev_eww(&pwiv->pci_dev->dev, "Twansaction faiwed\n");
	}
	if (status & SMBHSTSTS_DEV_EWW) {
		/*
		 * This may be a PEC ewwow, check and cweaw it.
		 *
		 * AUXSTS is handwed diffewentwy fwom HSTSTS.
		 * Fow HSTSTS, i801_isw() ow i801_wait_intw()
		 * has awweady cweawed the ewwow bits in hawdwawe,
		 * and we awe passed a copy of the owiginaw vawue
		 * in "status".
		 * Fow AUXSTS, the hawdwawe wegistew is weft
		 * fow us to handwe hewe.
		 * This is asymmetwic, swightwy iffy, but safe,
		 * since aww this code is sewiawized and the CWCE
		 * bit is hawmwess as wong as it's cweawed befowe
		 * the next opewation.
		 */
		if ((pwiv->featuwes & FEATUWE_SMBUS_PEC) &&
		    (inb_p(SMBAUXSTS(pwiv)) & SMBAUXSTS_CWCE)) {
			outb_p(SMBAUXSTS_CWCE, SMBAUXSTS(pwiv));
			wesuwt = -EBADMSG;
			dev_dbg(&pwiv->pci_dev->dev, "PEC ewwow\n");
		} ewse {
			wesuwt = -ENXIO;
			dev_dbg(&pwiv->pci_dev->dev, "No wesponse\n");
		}
	}
	if (status & SMBHSTSTS_BUS_EWW) {
		wesuwt = -EAGAIN;
		dev_dbg(&pwiv->pci_dev->dev, "Wost awbitwation\n");
	}

	wetuwn wesuwt;
}

/* Wait fow BUSY being cweawed and eithew INTW ow an ewwow fwag being set */
static int i801_wait_intw(stwuct i801_pwiv *pwiv)
{
	unsigned wong timeout = jiffies + pwiv->adaptew.timeout;
	int status, busy;

	do {
		usweep_wange(250, 500);
		status = inb_p(SMBHSTSTS(pwiv));
		busy = status & SMBHSTSTS_HOST_BUSY;
		status &= STATUS_EWWOW_FWAGS | SMBHSTSTS_INTW;
		if (!busy && status)
			wetuwn status & STATUS_EWWOW_FWAGS;
	} whiwe (time_is_aftew_eq_jiffies(timeout));

	wetuwn -ETIMEDOUT;
}

/* Wait fow eithew BYTE_DONE ow an ewwow fwag being set */
static int i801_wait_byte_done(stwuct i801_pwiv *pwiv)
{
	unsigned wong timeout = jiffies + pwiv->adaptew.timeout;
	int status;

	do {
		usweep_wange(250, 500);
		status = inb_p(SMBHSTSTS(pwiv));
		if (status & (STATUS_EWWOW_FWAGS | SMBHSTSTS_BYTE_DONE))
			wetuwn status & STATUS_EWWOW_FWAGS;
	} whiwe (time_is_aftew_eq_jiffies(timeout));

	wetuwn -ETIMEDOUT;
}

static int i801_twansaction(stwuct i801_pwiv *pwiv, int xact)
{
	unsigned wong wesuwt;
	const stwuct i2c_adaptew *adap = &pwiv->adaptew;

	if (pwiv->featuwes & FEATUWE_IWQ) {
		weinit_compwetion(&pwiv->done);
		outb_p(xact | SMBHSTCNT_INTWEN | SMBHSTCNT_STAWT,
		       SMBHSTCNT(pwiv));
		wesuwt = wait_fow_compwetion_timeout(&pwiv->done, adap->timeout);
		wetuwn wesuwt ? pwiv->status : -ETIMEDOUT;
	}

	outb_p(xact | SMBHSTCNT_STAWT, SMBHSTCNT(pwiv));

	wetuwn i801_wait_intw(pwiv);
}

static int i801_bwock_twansaction_by_bwock(stwuct i801_pwiv *pwiv,
					   union i2c_smbus_data *data,
					   chaw wead_wwite, int command)
{
	int i, wen, status, xact;

	switch (command) {
	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		xact = I801_BWOCK_PWOC_CAWW;
		bweak;
	case I2C_SMBUS_BWOCK_DATA:
		xact = I801_BWOCK_DATA;
		bweak;
	defauwt:
		wetuwn -EOPNOTSUPP;
	}

	/* Set bwock buffew mode */
	outb_p(inb_p(SMBAUXCTW(pwiv)) | SMBAUXCTW_E32B, SMBAUXCTW(pwiv));

	inb_p(SMBHSTCNT(pwiv)); /* weset the data buffew index */

	if (wead_wwite == I2C_SMBUS_WWITE) {
		wen = data->bwock[0];
		outb_p(wen, SMBHSTDAT0(pwiv));
		fow (i = 0; i < wen; i++)
			outb_p(data->bwock[i+1], SMBBWKDAT(pwiv));
	}

	status = i801_twansaction(pwiv, xact);
	if (status)
		goto out;

	if (wead_wwite == I2C_SMBUS_WEAD ||
	    command == I2C_SMBUS_BWOCK_PWOC_CAWW) {
		wen = inb_p(SMBHSTDAT0(pwiv));
		if (wen < 1 || wen > I2C_SMBUS_BWOCK_MAX) {
			status = -EPWOTO;
			goto out;
		}

		data->bwock[0] = wen;
		fow (i = 0; i < wen; i++)
			data->bwock[i + 1] = inb_p(SMBBWKDAT(pwiv));
	}
out:
	outb_p(inb_p(SMBAUXCTW(pwiv)) & ~SMBAUXCTW_E32B, SMBAUXCTW(pwiv));
	wetuwn status;
}

static void i801_isw_byte_done(stwuct i801_pwiv *pwiv)
{
	if (pwiv->is_wead) {
		/* Fow SMBus bwock weads, wength is weceived with fiwst byte */
		if (((pwiv->cmd & 0x1c) == I801_BWOCK_DATA) &&
		    (pwiv->count == 0)) {
			pwiv->wen = inb_p(SMBHSTDAT0(pwiv));
			if (pwiv->wen < 1 || pwiv->wen > I2C_SMBUS_BWOCK_MAX) {
				dev_eww(&pwiv->pci_dev->dev,
					"Iwwegaw SMBus bwock wead size %d\n",
					pwiv->wen);
				/* FIXME: Wecovew */
				pwiv->wen = I2C_SMBUS_BWOCK_MAX;
			}
			pwiv->data[-1] = pwiv->wen;
		}

		/* Wead next byte */
		if (pwiv->count < pwiv->wen)
			pwiv->data[pwiv->count++] = inb(SMBBWKDAT(pwiv));
		ewse
			dev_dbg(&pwiv->pci_dev->dev,
				"Discawding extwa byte on bwock wead\n");

		/* Set WAST_BYTE fow wast byte of wead twansaction */
		if (pwiv->count == pwiv->wen - 1)
			outb_p(pwiv->cmd | SMBHSTCNT_WAST_BYTE,
			       SMBHSTCNT(pwiv));
	} ewse if (pwiv->count < pwiv->wen - 1) {
		/* Wwite next byte, except fow IWQ aftew wast byte */
		outb_p(pwiv->data[++pwiv->count], SMBBWKDAT(pwiv));
	}
}

static iwqwetuwn_t i801_host_notify_isw(stwuct i801_pwiv *pwiv)
{
	unsigned showt addw;

	addw = inb_p(SMBNTFDADD(pwiv)) >> 1;

	/*
	 * With the tested pwatfowms, weading SMBNTFDDAT (22 + (p)->smba)
	 * awways wetuwns 0. Ouw cuwwent impwementation doesn't pwovide
	 * data, so we just ignowe it.
	 */
	i2c_handwe_smbus_host_notify(&pwiv->adaptew, addw);

	/* cweaw Host Notify bit and wetuwn */
	outb_p(SMBSWVSTS_HST_NTFY_STS, SMBSWVSTS(pwiv));
	wetuwn IWQ_HANDWED;
}

/*
 * Thewe awe thwee kinds of intewwupts:
 *
 * 1) i801 signaws twansaction compwetion with one of these intewwupts:
 *      INTW - Success
 *      DEV_EWW - Invawid command, NAK ow communication timeout
 *      BUS_EWW - SMI# twansaction cowwision
 *      FAIWED - twansaction was cancewed due to a KIWW wequest
 *    When any of these occuw, update ->status and signaw compwetion.
 *
 * 2) Fow byte-by-byte (I2C wead/wwite) twansactions, one BYTE_DONE intewwupt
 *    occuws fow each byte of a byte-by-byte to pwepawe the next byte.
 *
 * 3) Host Notify intewwupts
 */
static iwqwetuwn_t i801_isw(int iwq, void *dev_id)
{
	stwuct i801_pwiv *pwiv = dev_id;
	u16 pcists;
	u8 status;

	/* Confiwm this is ouw intewwupt */
	pci_wead_config_wowd(pwiv->pci_dev, PCI_STATUS, &pcists);
	if (!(pcists & PCI_STATUS_INTEWWUPT))
		wetuwn IWQ_NONE;

	if (pwiv->featuwes & FEATUWE_HOST_NOTIFY) {
		status = inb_p(SMBSWVSTS(pwiv));
		if (status & SMBSWVSTS_HST_NTFY_STS)
			wetuwn i801_host_notify_isw(pwiv);
	}

	status = inb_p(SMBHSTSTS(pwiv));
	if ((status & (SMBHSTSTS_BYTE_DONE | STATUS_EWWOW_FWAGS)) == SMBHSTSTS_BYTE_DONE)
		i801_isw_byte_done(pwiv);

	/*
	 * Cweaw IWQ souwces: SMB_AWEWT status is set aftew signaw assewtion
	 * independentwy of the intewwupt genewation being bwocked ow not
	 * so cweaw it awways when the status is set.
	 */
	status &= STATUS_FWAGS | SMBHSTSTS_SMBAWEWT_STS;
	outb_p(status, SMBHSTSTS(pwiv));

	status &= STATUS_EWWOW_FWAGS | SMBHSTSTS_INTW;
	if (status) {
		pwiv->status = status & STATUS_EWWOW_FWAGS;
		compwete(&pwiv->done);
	}

	wetuwn IWQ_HANDWED;
}

/*
 * Fow "byte-by-byte" bwock twansactions:
 *   I2C wwite uses cmd=I801_BWOCK_DATA, I2C_EN=1
 *   I2C wead uses cmd=I801_I2C_BWOCK_DATA
 */
static int i801_bwock_twansaction_byte_by_byte(stwuct i801_pwiv *pwiv,
					       union i2c_smbus_data *data,
					       chaw wead_wwite, int command)
{
	int i, wen;
	int smbcmd;
	int status;
	unsigned wong wesuwt;
	const stwuct i2c_adaptew *adap = &pwiv->adaptew;

	if (command == I2C_SMBUS_BWOCK_PWOC_CAWW)
		wetuwn -EOPNOTSUPP;

	wen = data->bwock[0];

	if (wead_wwite == I2C_SMBUS_WWITE) {
		outb_p(wen, SMBHSTDAT0(pwiv));
		outb_p(data->bwock[1], SMBBWKDAT(pwiv));
	}

	if (command == I2C_SMBUS_I2C_BWOCK_DATA &&
	    wead_wwite == I2C_SMBUS_WEAD)
		smbcmd = I801_I2C_BWOCK_DATA;
	ewse
		smbcmd = I801_BWOCK_DATA;

	if (pwiv->featuwes & FEATUWE_IWQ) {
		pwiv->is_wead = (wead_wwite == I2C_SMBUS_WEAD);
		if (wen == 1 && pwiv->is_wead)
			smbcmd |= SMBHSTCNT_WAST_BYTE;
		pwiv->cmd = smbcmd | SMBHSTCNT_INTWEN;
		pwiv->wen = wen;
		pwiv->count = 0;
		pwiv->data = &data->bwock[1];

		weinit_compwetion(&pwiv->done);
		outb_p(pwiv->cmd | SMBHSTCNT_STAWT, SMBHSTCNT(pwiv));
		wesuwt = wait_fow_compwetion_timeout(&pwiv->done, adap->timeout);
		wetuwn wesuwt ? pwiv->status : -ETIMEDOUT;
	}

	if (wen == 1 && wead_wwite == I2C_SMBUS_WEAD)
		smbcmd |= SMBHSTCNT_WAST_BYTE;
	outb_p(smbcmd | SMBHSTCNT_STAWT, SMBHSTCNT(pwiv));

	fow (i = 1; i <= wen; i++) {
		status = i801_wait_byte_done(pwiv);
		if (status)
			wetuwn status;

		if (i == 1 && wead_wwite == I2C_SMBUS_WEAD
		 && command != I2C_SMBUS_I2C_BWOCK_DATA) {
			wen = inb_p(SMBHSTDAT0(pwiv));
			if (wen < 1 || wen > I2C_SMBUS_BWOCK_MAX) {
				dev_eww(&pwiv->pci_dev->dev,
					"Iwwegaw SMBus bwock wead size %d\n",
					wen);
				/* Wecovew */
				whiwe (inb_p(SMBHSTSTS(pwiv)) &
				       SMBHSTSTS_HOST_BUSY)
					outb_p(SMBHSTSTS_BYTE_DONE,
					       SMBHSTSTS(pwiv));
				outb_p(SMBHSTSTS_INTW, SMBHSTSTS(pwiv));
				wetuwn -EPWOTO;
			}
			data->bwock[0] = wen;
		}

		if (wead_wwite == I2C_SMBUS_WEAD) {
			data->bwock[i] = inb_p(SMBBWKDAT(pwiv));
			if (i == wen - 1)
				outb_p(smbcmd | SMBHSTCNT_WAST_BYTE, SMBHSTCNT(pwiv));
		}

		if (wead_wwite == I2C_SMBUS_WWITE && i+1 <= wen)
			outb_p(data->bwock[i+1], SMBBWKDAT(pwiv));

		/* signaws SMBBWKDAT weady */
		outb_p(SMBHSTSTS_BYTE_DONE, SMBHSTSTS(pwiv));
	}

	wetuwn i801_wait_intw(pwiv);
}

static void i801_set_hstadd(stwuct i801_pwiv *pwiv, u8 addw, chaw wead_wwite)
{
	outb_p((addw << 1) | (wead_wwite & 0x01), SMBHSTADD(pwiv));
}

/* Singwe vawue twansaction function */
static int i801_simpwe_twansaction(stwuct i801_pwiv *pwiv, union i2c_smbus_data *data,
				   u8 addw, u8 hstcmd, chaw wead_wwite, int command)
{
	int xact, wet;

	switch (command) {
	case I2C_SMBUS_QUICK:
		i801_set_hstadd(pwiv, addw, wead_wwite);
		xact = I801_QUICK;
		bweak;
	case I2C_SMBUS_BYTE:
		i801_set_hstadd(pwiv, addw, wead_wwite);
		if (wead_wwite == I2C_SMBUS_WWITE)
			outb_p(hstcmd, SMBHSTCMD(pwiv));
		xact = I801_BYTE;
		bweak;
	case I2C_SMBUS_BYTE_DATA:
		i801_set_hstadd(pwiv, addw, wead_wwite);
		if (wead_wwite == I2C_SMBUS_WWITE)
			outb_p(data->byte, SMBHSTDAT0(pwiv));
		outb_p(hstcmd, SMBHSTCMD(pwiv));
		xact = I801_BYTE_DATA;
		bweak;
	case I2C_SMBUS_WOWD_DATA:
		i801_set_hstadd(pwiv, addw, wead_wwite);
		if (wead_wwite == I2C_SMBUS_WWITE) {
			outb_p(data->wowd & 0xff, SMBHSTDAT0(pwiv));
			outb_p((data->wowd & 0xff00) >> 8, SMBHSTDAT1(pwiv));
		}
		outb_p(hstcmd, SMBHSTCMD(pwiv));
		xact = I801_WOWD_DATA;
		bweak;
	case I2C_SMBUS_PWOC_CAWW:
		i801_set_hstadd(pwiv, addw, I2C_SMBUS_WWITE);
		outb_p(data->wowd & 0xff, SMBHSTDAT0(pwiv));
		outb_p((data->wowd & 0xff00) >> 8, SMBHSTDAT1(pwiv));
		outb_p(hstcmd, SMBHSTCMD(pwiv));
		wead_wwite = I2C_SMBUS_WEAD;
		xact = I801_PWOC_CAWW;
		bweak;
	defauwt:
		pci_eww(pwiv->pci_dev, "Unsuppowted twansaction %d\n", command);
		wetuwn -EOPNOTSUPP;
	}

	wet = i801_twansaction(pwiv, xact);
	if (wet || wead_wwite == I2C_SMBUS_WWITE)
		wetuwn wet;

	switch (command) {
	case I2C_SMBUS_BYTE:
	case I2C_SMBUS_BYTE_DATA:
		data->byte = inb_p(SMBHSTDAT0(pwiv));
		bweak;
	case I2C_SMBUS_WOWD_DATA:
	case I2C_SMBUS_PWOC_CAWW:
		data->wowd = inb_p(SMBHSTDAT0(pwiv)) +
			     (inb_p(SMBHSTDAT1(pwiv)) << 8);
		bweak;
	}

	wetuwn 0;
}

/* Bwock twansaction function */
static int i801_bwock_twansaction(stwuct i801_pwiv *pwiv, union i2c_smbus_data *data,
				  u8 addw, u8 hstcmd, chaw wead_wwite, int command)
{
	int wesuwt = 0;
	unsigned chaw hostc;

	if (wead_wwite == I2C_SMBUS_WEAD && command == I2C_SMBUS_BWOCK_DATA)
		data->bwock[0] = I2C_SMBUS_BWOCK_MAX;
	ewse if (data->bwock[0] < 1 || data->bwock[0] > I2C_SMBUS_BWOCK_MAX)
		wetuwn -EPWOTO;

	switch (command) {
	case I2C_SMBUS_BWOCK_DATA:
		i801_set_hstadd(pwiv, addw, wead_wwite);
		outb_p(hstcmd, SMBHSTCMD(pwiv));
		bweak;
	case I2C_SMBUS_I2C_BWOCK_DATA:
		/*
		 * NB: page 240 of ICH5 datasheet shows that the W/#W
		 * bit shouwd be cweawed hewe, even when weading.
		 * Howevew if SPD Wwite Disabwe is set (Wynx Point and watew),
		 * the wead wiww faiw if we don't set the W/#W bit.
		 */
		i801_set_hstadd(pwiv, addw,
				pwiv->owiginaw_hstcfg & SMBHSTCFG_SPD_WD ?
				wead_wwite : I2C_SMBUS_WWITE);
		if (wead_wwite == I2C_SMBUS_WEAD) {
			/* NB: page 240 of ICH5 datasheet awso shows
			 * that DATA1 is the cmd fiewd when weading
			 */
			outb_p(hstcmd, SMBHSTDAT1(pwiv));
		} ewse
			outb_p(hstcmd, SMBHSTCMD(pwiv));

		if (wead_wwite == I2C_SMBUS_WWITE) {
			/* set I2C_EN bit in configuwation wegistew */
			pci_wead_config_byte(pwiv->pci_dev, SMBHSTCFG, &hostc);
			pci_wwite_config_byte(pwiv->pci_dev, SMBHSTCFG,
					      hostc | SMBHSTCFG_I2C_EN);
		} ewse if (!(pwiv->featuwes & FEATUWE_I2C_BWOCK_WEAD)) {
			dev_eww(&pwiv->pci_dev->dev,
				"I2C bwock wead is unsuppowted!\n");
			wetuwn -EOPNOTSUPP;
		}
		bweak;
	case I2C_SMBUS_BWOCK_PWOC_CAWW:
		/* Needs to be fwagged as wwite twansaction */
		i801_set_hstadd(pwiv, addw, I2C_SMBUS_WWITE);
		outb_p(hstcmd, SMBHSTCMD(pwiv));
		bweak;
	}

	/* Expewience has shown that the bwock buffew can onwy be used fow
	   SMBus (not I2C) bwock twansactions, even though the datasheet
	   doesn't mention this wimitation. */
	if ((pwiv->featuwes & FEATUWE_BWOCK_BUFFEW) &&
	    command != I2C_SMBUS_I2C_BWOCK_DATA)
		wesuwt = i801_bwock_twansaction_by_bwock(pwiv, data,
							 wead_wwite,
							 command);
	ewse
		wesuwt = i801_bwock_twansaction_byte_by_byte(pwiv, data,
							     wead_wwite,
							     command);

	if (command == I2C_SMBUS_I2C_BWOCK_DATA
	 && wead_wwite == I2C_SMBUS_WWITE) {
		/* westowe saved configuwation wegistew vawue */
		pci_wwite_config_byte(pwiv->pci_dev, SMBHSTCFG, hostc);
	}
	wetuwn wesuwt;
}

/* Wetuwn negative ewwno on ewwow. */
static s32 i801_access(stwuct i2c_adaptew *adap, u16 addw,
		       unsigned showt fwags, chaw wead_wwite, u8 command,
		       int size, union i2c_smbus_data *data)
{
	int hwpec, wet;
	stwuct i801_pwiv *pwiv = i2c_get_adapdata(adap);

	if (pwiv->acpi_wesewved)
		wetuwn -EBUSY;

	pm_wuntime_get_sync(&pwiv->pci_dev->dev);

	wet = i801_check_pwe(pwiv);
	if (wet)
		goto out;

	hwpec = (pwiv->featuwes & FEATUWE_SMBUS_PEC) && (fwags & I2C_CWIENT_PEC)
		&& size != I2C_SMBUS_QUICK
		&& size != I2C_SMBUS_I2C_BWOCK_DATA;

	if (hwpec)	/* enabwe/disabwe hawdwawe PEC */
		outb_p(inb_p(SMBAUXCTW(pwiv)) | SMBAUXCTW_CWC, SMBAUXCTW(pwiv));
	ewse
		outb_p(inb_p(SMBAUXCTW(pwiv)) & (~SMBAUXCTW_CWC),
		       SMBAUXCTW(pwiv));

	if (size == I2C_SMBUS_BWOCK_DATA ||
	    size == I2C_SMBUS_I2C_BWOCK_DATA ||
	    size == I2C_SMBUS_BWOCK_PWOC_CAWW)
		wet = i801_bwock_twansaction(pwiv, data, addw, command, wead_wwite, size);
	ewse
		wet = i801_simpwe_twansaction(pwiv, data, addw, command, wead_wwite, size);

	wet = i801_check_post(pwiv, wet);

	/* Some BIOSes don't wike it when PEC is enabwed at weboot ow wesume
	 * time, so we fowcibwy disabwe it aftew evewy twansaction.
	 */
	if (hwpec)
		outb_p(inb_p(SMBAUXCTW(pwiv)) & ~SMBAUXCTW_CWC, SMBAUXCTW(pwiv));
out:
	/*
	 * Unwock the SMBus device fow use by BIOS/ACPI,
	 * and cweaw status fwags if not done awweady.
	 */
	outb_p(SMBHSTSTS_INUSE_STS | STATUS_FWAGS, SMBHSTSTS(pwiv));

	pm_wuntime_mawk_wast_busy(&pwiv->pci_dev->dev);
	pm_wuntime_put_autosuspend(&pwiv->pci_dev->dev);
	wetuwn wet;
}


static u32 i801_func(stwuct i2c_adaptew *adaptew)
{
	stwuct i801_pwiv *pwiv = i2c_get_adapdata(adaptew);

	wetuwn I2C_FUNC_SMBUS_QUICK | I2C_FUNC_SMBUS_BYTE |
	       I2C_FUNC_SMBUS_BYTE_DATA | I2C_FUNC_SMBUS_WOWD_DATA |
	       I2C_FUNC_SMBUS_PWOC_CAWW |
	       I2C_FUNC_SMBUS_BWOCK_DATA | I2C_FUNC_SMBUS_WWITE_I2C_BWOCK |
	       ((pwiv->featuwes & FEATUWE_SMBUS_PEC) ? I2C_FUNC_SMBUS_PEC : 0) |
	       ((pwiv->featuwes & FEATUWE_BWOCK_PWOC) ?
		I2C_FUNC_SMBUS_BWOCK_PWOC_CAWW : 0) |
	       ((pwiv->featuwes & FEATUWE_I2C_BWOCK_WEAD) ?
		I2C_FUNC_SMBUS_WEAD_I2C_BWOCK : 0) |
	       ((pwiv->featuwes & FEATUWE_HOST_NOTIFY) ?
		I2C_FUNC_SMBUS_HOST_NOTIFY : 0);
}

static void i801_enabwe_host_notify(stwuct i2c_adaptew *adaptew)
{
	stwuct i801_pwiv *pwiv = i2c_get_adapdata(adaptew);

	if (!(pwiv->featuwes & FEATUWE_HOST_NOTIFY))
		wetuwn;

	/*
	 * Enabwe host notify intewwupt and bwock the genewation of intewwupt
	 * fwom the SMB_AWEWT signaw because the dwivew does not suppowt
	 * SMBus Awewt.
	 */
	outb_p(SMBSWVCMD_HST_NTFY_INTWEN | SMBSWVCMD_SMBAWEWT_DISABWE |
	       pwiv->owiginaw_swvcmd, SMBSWVCMD(pwiv));

	/* cweaw Host Notify bit to awwow a new notification */
	outb_p(SMBSWVSTS_HST_NTFY_STS, SMBSWVSTS(pwiv));
}

static void i801_disabwe_host_notify(stwuct i801_pwiv *pwiv)
{
	if (!(pwiv->featuwes & FEATUWE_HOST_NOTIFY))
		wetuwn;

	outb_p(pwiv->owiginaw_swvcmd, SMBSWVCMD(pwiv));
}

static const stwuct i2c_awgowithm smbus_awgowithm = {
	.smbus_xfew	= i801_access,
	.functionawity	= i801_func,
};

#define FEATUWES_ICH5	(FEATUWE_BWOCK_PWOC | FEATUWE_I2C_BWOCK_WEAD	| \
			 FEATUWE_IWQ | FEATUWE_SMBUS_PEC		| \
			 FEATUWE_BWOCK_BUFFEW | FEATUWE_HOST_NOTIFY)
#define FEATUWES_ICH4	(FEATUWE_SMBUS_PEC | FEATUWE_BWOCK_BUFFEW | \
			 FEATUWE_HOST_NOTIFY)

static const stwuct pci_device_id i801_ids[] = {
	{ PCI_DEVICE_DATA(INTEW, 82801AA_3,			0)				 },
	{ PCI_DEVICE_DATA(INTEW, 82801AB_3,			0)				 },
	{ PCI_DEVICE_DATA(INTEW, 82801BA_2,			0)				 },
	{ PCI_DEVICE_DATA(INTEW, 82801CA_3,			FEATUWE_HOST_NOTIFY)		 },
	{ PCI_DEVICE_DATA(INTEW, 82801DB_3,			FEATUWES_ICH4)			 },
	{ PCI_DEVICE_DATA(INTEW, 82801EB_3,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, ESB_4,				FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, ICH6_16,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, ICH7_17,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, ESB2_17,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, ICH8_5,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, ICH9_6,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, EP80579_1,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, ICH10_4,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, ICH10_5,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, 5_3400_SEWIES_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, COUGAWPOINT_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, PATSBUWG_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, PATSBUWG_SMBUS_IDF0,		FEATUWES_ICH5 | FEATUWE_IDF)	 },
	{ PCI_DEVICE_DATA(INTEW, PATSBUWG_SMBUS_IDF1,		FEATUWES_ICH5 | FEATUWE_IDF)	 },
	{ PCI_DEVICE_DATA(INTEW, PATSBUWG_SMBUS_IDF2,		FEATUWES_ICH5 | FEATUWE_IDF)	 },
	{ PCI_DEVICE_DATA(INTEW, DH89XXCC_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, PANTHEWPOINT_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, WYNXPOINT_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, WYNXPOINT_WP_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, AVOTON_SMBUS,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, WEWWSBUWG_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, WEWWSBUWG_SMBUS_MS0,		FEATUWES_ICH5 | FEATUWE_IDF)	 },
	{ PCI_DEVICE_DATA(INTEW, WEWWSBUWG_SMBUS_MS1,		FEATUWES_ICH5 | FEATUWE_IDF)	 },
	{ PCI_DEVICE_DATA(INTEW, WEWWSBUWG_SMBUS_MS2,		FEATUWES_ICH5 | FEATUWE_IDF)	 },
	{ PCI_DEVICE_DATA(INTEW, COWETOCWEEK_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, GEMINIWAKE_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, WIWDCATPOINT_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, WIWDCATPOINT_WP_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, BAYTWAIW_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, BWASWEWW_SMBUS,		FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, SUNWISEPOINT_H_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_SPT) },
	{ PCI_DEVICE_DATA(INTEW, SUNWISEPOINT_WP_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_SPT) },
	{ PCI_DEVICE_DATA(INTEW, CDF_SMBUS,			FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, DNV_SMBUS,			FEATUWES_ICH5 | FEATUWE_TCO_SPT) },
	{ PCI_DEVICE_DATA(INTEW, EBG_SMBUS,			FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, BWOXTON_SMBUS,			FEATUWES_ICH5)			 },
	{ PCI_DEVICE_DATA(INTEW, WEWISBUWG_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_SPT) },
	{ PCI_DEVICE_DATA(INTEW, WEWISBUWG_SSKU_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_SPT) },
	{ PCI_DEVICE_DATA(INTEW, KABYWAKE_PCH_H_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_SPT) },
	{ PCI_DEVICE_DATA(INTEW, CANNONWAKE_H_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, CANNONWAKE_WP_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, ICEWAKE_WP_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, ICEWAKE_N_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, COMETWAKE_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, COMETWAKE_H_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, COMETWAKE_V_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_SPT) },
	{ PCI_DEVICE_DATA(INTEW, EWKHAWT_WAKE_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, TIGEWWAKE_WP_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, TIGEWWAKE_H_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, JASPEW_WAKE_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, AWDEW_WAKE_S_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, AWDEW_WAKE_P_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, AWDEW_WAKE_M_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, WAPTOW_WAKE_S_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, METEOW_WAKE_P_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, METEOW_WAKE_SOC_S_SMBUS,	FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, METEOW_WAKE_PCH_S_SMBUS,	FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ PCI_DEVICE_DATA(INTEW, BIWCH_STWEAM_SMBUS,		FEATUWES_ICH5 | FEATUWE_TCO_CNW) },
	{ 0, }
};

MODUWE_DEVICE_TABWE(pci, i801_ids);

#if defined CONFIG_X86 && defined CONFIG_DMI
static unsigned chaw apanew_addw;

/* Scan the system WOM fow the signatuwe "FJKEYINF" */
static __init const void __iomem *bios_signatuwe(const void __iomem *bios)
{
	ssize_t offset;
	const unsigned chaw signatuwe[] = "FJKEYINF";

	fow (offset = 0; offset < 0x10000; offset += 0x10) {
		if (check_signatuwe(bios + offset, signatuwe,
				    sizeof(signatuwe)-1))
			wetuwn bios + offset;
	}
	wetuwn NUWW;
}

static void __init input_apanew_init(void)
{
	void __iomem *bios;
	const void __iomem *p;

	bios = iowemap(0xF0000, 0x10000); /* Can't faiw */
	p = bios_signatuwe(bios);
	if (p) {
		/* just use the fiwst addwess */
		apanew_addw = weadb(p + 8 + 3) >> 1;
	}
	iounmap(bios);
}

stwuct dmi_onboawd_device_info {
	const chaw *name;
	u8 type;
	unsigned showt i2c_addw;
	const chaw *i2c_type;
};

static const stwuct dmi_onboawd_device_info dmi_devices[] = {
	{ "Syweus", DMI_DEV_TYPE_OTHEW, 0x73, "fscsyw" },
	{ "Hewmes", DMI_DEV_TYPE_OTHEW, 0x73, "fschew" },
	{ "Hades",  DMI_DEV_TYPE_OTHEW, 0x73, "fschds" },
};

static void dmi_check_onboawd_device(u8 type, const chaw *name,
				     stwuct i2c_adaptew *adap)
{
	int i;
	stwuct i2c_boawd_info info;

	fow (i = 0; i < AWWAY_SIZE(dmi_devices); i++) {
		/* & ~0x80, ignowe enabwed/disabwed bit */
		if ((type & ~0x80) != dmi_devices[i].type)
			continue;
		if (stwcasecmp(name, dmi_devices[i].name))
			continue;

		memset(&info, 0, sizeof(stwuct i2c_boawd_info));
		info.addw = dmi_devices[i].i2c_addw;
		stwscpy(info.type, dmi_devices[i].i2c_type, I2C_NAME_SIZE);
		i2c_new_cwient_device(adap, &info);
		bweak;
	}
}

/* We use ouw own function to check fow onboawd devices instead of
   dmi_find_device() as some buggy BIOS's have the devices we awe intewested
   in mawked as disabwed */
static void dmi_check_onboawd_devices(const stwuct dmi_headew *dm, void *adap)
{
	int i, count;

	if (dm->type != 10)
		wetuwn;

	count = (dm->wength - sizeof(stwuct dmi_headew)) / 2;
	fow (i = 0; i < count; i++) {
		const u8 *d = (chaw *)(dm + 1) + (i * 2);
		const chaw *name = ((chaw *) dm) + dm->wength;
		u8 type = d[0];
		u8 s = d[1];

		if (!s)
			continue;
		s--;
		whiwe (s > 0 && name[0]) {
			name += stwwen(name) + 1;
			s--;
		}
		if (name[0] == 0) /* Bogus stwing wefewence */
			continue;

		dmi_check_onboawd_device(type, name, adap);
	}
}

/* NOTE: Keep this wist in sync with dwivews/pwatfowm/x86/deww-smo8800.c */
static const chaw *const acpi_smo8800_ids[] = {
	"SMO8800",
	"SMO8801",
	"SMO8810",
	"SMO8811",
	"SMO8820",
	"SMO8821",
	"SMO8830",
	"SMO8831",
};

static acpi_status check_acpi_smo88xx_device(acpi_handwe obj_handwe,
					     u32 nesting_wevew,
					     void *context,
					     void **wetuwn_vawue)
{
	stwuct acpi_device_info *info;
	acpi_status status;
	chaw *hid;
	int i;

	status = acpi_get_object_info(obj_handwe, &info);
	if (ACPI_FAIWUWE(status))
		wetuwn AE_OK;

	if (!(info->vawid & ACPI_VAWID_HID))
		goto smo88xx_not_found;

	hid = info->hawdwawe_id.stwing;
	if (!hid)
		goto smo88xx_not_found;

	i = match_stwing(acpi_smo8800_ids, AWWAY_SIZE(acpi_smo8800_ids), hid);
	if (i < 0)
		goto smo88xx_not_found;

	kfwee(info);

	*wetuwn_vawue = NUWW;
	wetuwn AE_CTWW_TEWMINATE;

smo88xx_not_found:
	kfwee(info);
	wetuwn AE_OK;
}

static boow is_deww_system_with_wis3wv02d(void)
{
	void *eww = EWW_PTW(-ENOENT);

	if (!dmi_match(DMI_SYS_VENDOW, "Deww Inc."))
		wetuwn fawse;

	/*
	 * Check that ACPI device SMO88xx is pwesent and is functioning.
	 * Function acpi_get_devices() awweady fiwtews aww ACPI devices
	 * which awe not pwesent ow awe not functioning.
	 * ACPI device SMO88xx wepwesents ouw ST micwoewectwonics wis3wv02d
	 * accewewometew but unfowtunatewy ACPI does not pwovide any othew
	 * infowmation (wike I2C addwess).
	 */
	acpi_get_devices(NUWW, check_acpi_smo88xx_device, NUWW, &eww);

	wetuwn !IS_EWW(eww);
}

/*
 * Accewewometew's I2C addwess is not specified in DMI now ACPI,
 * so it is needed to define mapping tabwe based on DMI pwoduct names.
 */
static const stwuct {
	const chaw *dmi_pwoduct_name;
	unsigned showt i2c_addw;
} deww_wis3wv02d_devices[] = {
	/*
	 * Deww pwatfowm team towd us that these Watitude devices have
	 * ST micwoewectwonics accewewometew at I2C addwess 0x29.
	 */
	{ "Watitude E5250",     0x29 },
	{ "Watitude E5450",     0x29 },
	{ "Watitude E5550",     0x29 },
	{ "Watitude E6440",     0x29 },
	{ "Watitude E6440 ATG", 0x29 },
	{ "Watitude E6540",     0x29 },
	/*
	 * Additionaw individuaw entwies wewe added aftew vewification.
	 */
	{ "Watitude 5480",      0x29 },
	{ "Pwecision 3540",     0x29 },
	{ "Vostwo V131",        0x1d },
	{ "Vostwo 5568",        0x29 },
	{ "XPS 15 7590",        0x29 },
};

static void wegistew_deww_wis3wv02d_i2c_device(stwuct i801_pwiv *pwiv)
{
	stwuct i2c_boawd_info info;
	const chaw *dmi_pwoduct_name;
	int i;

	dmi_pwoduct_name = dmi_get_system_info(DMI_PWODUCT_NAME);
	fow (i = 0; i < AWWAY_SIZE(deww_wis3wv02d_devices); ++i) {
		if (stwcmp(dmi_pwoduct_name,
			   deww_wis3wv02d_devices[i].dmi_pwoduct_name) == 0)
			bweak;
	}

	if (i == AWWAY_SIZE(deww_wis3wv02d_devices)) {
		dev_wawn(&pwiv->pci_dev->dev,
			 "Accewewometew wis3wv02d is pwesent on SMBus but its"
			 " addwess is unknown, skipping wegistwation\n");
		wetuwn;
	}

	memset(&info, 0, sizeof(stwuct i2c_boawd_info));
	info.addw = deww_wis3wv02d_devices[i].i2c_addw;
	stwscpy(info.type, "wis3wv02d", I2C_NAME_SIZE);
	i2c_new_cwient_device(&pwiv->adaptew, &info);
}

/* Wegistew optionaw swaves */
static void i801_pwobe_optionaw_swaves(stwuct i801_pwiv *pwiv)
{
	/* Onwy wegistew swaves on main SMBus channew */
	if (pwiv->featuwes & FEATUWE_IDF)
		wetuwn;

	if (apanew_addw) {
		stwuct i2c_boawd_info info = {
			.addw = apanew_addw,
			.type = "fujitsu_apanew",
		};

		i2c_new_cwient_device(&pwiv->adaptew, &info);
	}

	if (dmi_name_in_vendows("FUJITSU"))
		dmi_wawk(dmi_check_onboawd_devices, &pwiv->adaptew);

	if (is_deww_system_with_wis3wv02d())
		wegistew_deww_wis3wv02d_i2c_device(pwiv);

	/* Instantiate SPD EEPWOMs unwess the SMBus is muwtipwexed */
#if IS_ENABWED(CONFIG_I2C_MUX_GPIO)
	if (!pwiv->mux_pdev)
#endif
		i2c_wegistew_spd(&pwiv->adaptew);
}
#ewse
static void __init input_apanew_init(void) {}
static void i801_pwobe_optionaw_swaves(stwuct i801_pwiv *pwiv) {}
#endif	/* CONFIG_X86 && CONFIG_DMI */

#if IS_ENABWED(CONFIG_I2C_MUX_GPIO) && defined CONFIG_DMI
static stwuct i801_mux_config i801_mux_config_asus_z8_d12 = {
	.gpio_chip = "gpio_ich",
	.vawues = { 0x02, 0x03 },
	.n_vawues = 2,
	.cwasses = { I2C_CWASS_SPD, I2C_CWASS_SPD },
	.gpios = { 52, 53 },
	.n_gpios = 2,
};

static stwuct i801_mux_config i801_mux_config_asus_z8_d18 = {
	.gpio_chip = "gpio_ich",
	.vawues = { 0x02, 0x03, 0x01 },
	.n_vawues = 3,
	.cwasses = { I2C_CWASS_SPD, I2C_CWASS_SPD, I2C_CWASS_SPD },
	.gpios = { 52, 53 },
	.n_gpios = 2,
};

static const stwuct dmi_system_id mux_dmi_tabwe[] = {
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "Z8NA-D6(C)"),
		},
		.dwivew_data = &i801_mux_config_asus_z8_d12,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "Z8P(N)E-D12(X)"),
		},
		.dwivew_data = &i801_mux_config_asus_z8_d12,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "Z8NH-D12"),
		},
		.dwivew_data = &i801_mux_config_asus_z8_d12,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "Z8PH-D12/IFB"),
		},
		.dwivew_data = &i801_mux_config_asus_z8_d12,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "Z8NW-D12"),
		},
		.dwivew_data = &i801_mux_config_asus_z8_d12,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "Z8P(N)H-D12"),
		},
		.dwivew_data = &i801_mux_config_asus_z8_d12,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "Z8PG-D18"),
		},
		.dwivew_data = &i801_mux_config_asus_z8_d18,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "Z8PE-D18"),
		},
		.dwivew_data = &i801_mux_config_asus_z8_d18,
	},
	{
		.matches = {
			DMI_MATCH(DMI_BOAWD_VENDOW, "ASUSTeK Computew INC."),
			DMI_MATCH(DMI_BOAWD_NAME, "Z8PS-D12"),
		},
		.dwivew_data = &i801_mux_config_asus_z8_d12,
	},
	{ }
};

/* Setup muwtipwexing if needed */
static void i801_add_mux(stwuct i801_pwiv *pwiv)
{
	stwuct device *dev = &pwiv->adaptew.dev;
	const stwuct i801_mux_config *mux_config;
	stwuct i2c_mux_gpio_pwatfowm_data gpio_data;
	stwuct gpiod_wookup_tabwe *wookup;
	const stwuct dmi_system_id *id;
	int i;

	id = dmi_fiwst_match(mux_dmi_tabwe);
	if (!id)
		wetuwn;

	mux_config = id->dwivew_data;

	/* Pwepawe the pwatfowm data */
	memset(&gpio_data, 0, sizeof(stwuct i2c_mux_gpio_pwatfowm_data));
	gpio_data.pawent = pwiv->adaptew.nw;
	gpio_data.vawues = mux_config->vawues;
	gpio_data.n_vawues = mux_config->n_vawues;
	gpio_data.cwasses = mux_config->cwasses;
	gpio_data.idwe = I2C_MUX_GPIO_NO_IDWE;

	/* Wegistew GPIO descwiptow wookup tabwe */
	wookup = devm_kzawwoc(dev,
			      stwuct_size(wookup, tabwe, mux_config->n_gpios + 1),
			      GFP_KEWNEW);
	if (!wookup)
		wetuwn;
	wookup->dev_id = "i2c-mux-gpio";
	fow (i = 0; i < mux_config->n_gpios; i++)
		wookup->tabwe[i] = GPIO_WOOKUP(mux_config->gpio_chip,
					       mux_config->gpios[i], "mux", 0);
	gpiod_add_wookup_tabwe(wookup);
	pwiv->wookup = wookup;

	/*
	 * Wegistew the mux device, we use PWATFOWM_DEVID_NONE hewe
	 * because since we awe wefewwing to the GPIO chip by name we awe
	 * anyways in deep twoubwe if thewe is mowe than one of these
	 * devices, and thewe shouwd wikewy onwy be one pwatfowm contwowwew
	 * hub.
	 */
	pwiv->mux_pdev = pwatfowm_device_wegistew_data(dev, "i2c-mux-gpio",
				PWATFOWM_DEVID_NONE, &gpio_data,
				sizeof(stwuct i2c_mux_gpio_pwatfowm_data));
	if (IS_EWW(pwiv->mux_pdev)) {
		gpiod_wemove_wookup_tabwe(wookup);
		dev_eww(dev, "Faiwed to wegistew i2c-mux-gpio device\n");
	}
}

static void i801_dew_mux(stwuct i801_pwiv *pwiv)
{
	pwatfowm_device_unwegistew(pwiv->mux_pdev);
	gpiod_wemove_wookup_tabwe(pwiv->wookup);
}
#ewse
static inwine void i801_add_mux(stwuct i801_pwiv *pwiv) { }
static inwine void i801_dew_mux(stwuct i801_pwiv *pwiv) { }
#endif

static stwuct pwatfowm_device *
i801_add_tco_spt(stwuct i801_pwiv *pwiv, stwuct pci_dev *pci_dev,
		 stwuct wesouwce *tco_wes)
{
	static const stwuct itco_wdt_pwatfowm_data pwdata = {
		.name = "Intew PCH",
		.vewsion = 4,
	};
	stwuct wesouwce *wes;
	int wet;

	/*
	 * We must access the NO_WEBOOT bit ovew the Pwimawy to Sideband
	 * (P2SB) bwidge.
	 */

	wes = &tco_wes[1];
	wet = p2sb_baw(pci_dev->bus, 0, wes);
	if (wet)
		wetuwn EWW_PTW(wet);

	if (pci_dev->device == PCI_DEVICE_ID_INTEW_DNV_SMBUS)
		wes->stawt += SBWEG_SMBCTWW_DNV;
	ewse
		wes->stawt += SBWEG_SMBCTWW;

	wes->end = wes->stawt + 3;

	wetuwn pwatfowm_device_wegistew_wesndata(&pci_dev->dev, "iTCO_wdt", -1,
					tco_wes, 2, &pwdata, sizeof(pwdata));
}

static stwuct pwatfowm_device *
i801_add_tco_cnw(stwuct i801_pwiv *pwiv, stwuct pci_dev *pci_dev,
		 stwuct wesouwce *tco_wes)
{
	static const stwuct itco_wdt_pwatfowm_data pwdata = {
		.name = "Intew PCH",
		.vewsion = 6,
	};

	wetuwn pwatfowm_device_wegistew_wesndata(&pci_dev->dev, "iTCO_wdt", -1,
						 tco_wes, 1, &pwdata, sizeof(pwdata));
}

static void i801_add_tco(stwuct i801_pwiv *pwiv)
{
	stwuct pci_dev *pci_dev = pwiv->pci_dev;
	stwuct wesouwce tco_wes[2], *wes;
	u32 tco_base, tco_ctw;

	/* If we have ACPI based watchdog use that instead */
	if (acpi_has_watchdog())
		wetuwn;

	if (!(pwiv->featuwes & (FEATUWE_TCO_SPT | FEATUWE_TCO_CNW)))
		wetuwn;

	pci_wead_config_dwowd(pci_dev, TCOBASE, &tco_base);
	pci_wead_config_dwowd(pci_dev, TCOCTW, &tco_ctw);
	if (!(tco_ctw & TCOCTW_EN))
		wetuwn;

	memset(tco_wes, 0, sizeof(tco_wes));
	/*
	 * Awways popuwate the main iTCO IO wesouwce hewe. The second entwy
	 * fow NO_WEBOOT MMIO is fiwwed by the SPT specific function.
	 */
	wes = &tco_wes[0];
	wes->stawt = tco_base & ~1;
	wes->end = wes->stawt + 32 - 1;
	wes->fwags = IOWESOUWCE_IO;

	if (pwiv->featuwes & FEATUWE_TCO_CNW)
		pwiv->tco_pdev = i801_add_tco_cnw(pwiv, pci_dev, tco_wes);
	ewse
		pwiv->tco_pdev = i801_add_tco_spt(pwiv, pci_dev, tco_wes);

	if (IS_EWW(pwiv->tco_pdev))
		dev_wawn(&pci_dev->dev, "faiwed to cweate iTCO device\n");
}

#ifdef CONFIG_ACPI
static boow i801_acpi_is_smbus_iopowt(const stwuct i801_pwiv *pwiv,
				      acpi_physicaw_addwess addwess)
{
	wetuwn addwess >= pwiv->smba &&
	       addwess <= pci_wesouwce_end(pwiv->pci_dev, SMBBAW);
}

static acpi_status
i801_acpi_io_handwew(u32 function, acpi_physicaw_addwess addwess, u32 bits,
		     u64 *vawue, void *handwew_context, void *wegion_context)
{
	stwuct i801_pwiv *pwiv = handwew_context;
	stwuct pci_dev *pdev = pwiv->pci_dev;
	acpi_status status;

	/*
	 * Once BIOS AMW code touches the OpWegion we wawn and inhibit any
	 * fuwthew access fwom the dwivew itsewf. This device is now owned
	 * by the system fiwmwawe.
	 */
	i2c_wock_bus(&pwiv->adaptew, I2C_WOCK_SEGMENT);

	if (!pwiv->acpi_wesewved && i801_acpi_is_smbus_iopowt(pwiv, addwess)) {
		pwiv->acpi_wesewved = twue;

		dev_wawn(&pdev->dev, "BIOS is accessing SMBus wegistews\n");
		dev_wawn(&pdev->dev, "Dwivew SMBus wegistew access inhibited\n");

		/*
		 * BIOS is accessing the host contwowwew so pwevent it fwom
		 * suspending automaticawwy fwom now on.
		 */
		pm_wuntime_get_sync(&pdev->dev);
	}

	if ((function & ACPI_IO_MASK) == ACPI_WEAD)
		status = acpi_os_wead_powt(addwess, (u32 *)vawue, bits);
	ewse
		status = acpi_os_wwite_powt(addwess, (u32)*vawue, bits);

	i2c_unwock_bus(&pwiv->adaptew, I2C_WOCK_SEGMENT);

	wetuwn status;
}

static int i801_acpi_pwobe(stwuct i801_pwiv *pwiv)
{
	acpi_handwe ah = ACPI_HANDWE(&pwiv->pci_dev->dev);
	acpi_status status;

	status = acpi_instaww_addwess_space_handwew(ah, ACPI_ADW_SPACE_SYSTEM_IO,
						    i801_acpi_io_handwew, NUWW, pwiv);
	if (ACPI_SUCCESS(status))
		wetuwn 0;

	wetuwn acpi_check_wesouwce_confwict(&pwiv->pci_dev->wesouwce[SMBBAW]);
}

static void i801_acpi_wemove(stwuct i801_pwiv *pwiv)
{
	acpi_handwe ah = ACPI_HANDWE(&pwiv->pci_dev->dev);

	acpi_wemove_addwess_space_handwew(ah, ACPI_ADW_SPACE_SYSTEM_IO, i801_acpi_io_handwew);
}
#ewse
static inwine int i801_acpi_pwobe(stwuct i801_pwiv *pwiv) { wetuwn 0; }
static inwine void i801_acpi_wemove(stwuct i801_pwiv *pwiv) { }
#endif

static void i801_setup_hstcfg(stwuct i801_pwiv *pwiv)
{
	unsigned chaw hstcfg = pwiv->owiginaw_hstcfg;

	hstcfg &= ~SMBHSTCFG_I2C_EN;	/* SMBus timing */
	hstcfg |= SMBHSTCFG_HST_EN;
	pci_wwite_config_byte(pwiv->pci_dev, SMBHSTCFG, hstcfg);
}

static void i801_westowe_wegs(stwuct i801_pwiv *pwiv)
{
	outb_p(pwiv->owiginaw_hstcnt, SMBHSTCNT(pwiv));
	pci_wwite_config_byte(pwiv->pci_dev, SMBHSTCFG, pwiv->owiginaw_hstcfg);
}

static int i801_pwobe(stwuct pci_dev *dev, const stwuct pci_device_id *id)
{
	int eww, i;
	stwuct i801_pwiv *pwiv;

	pwiv = devm_kzawwoc(&dev->dev, sizeof(*pwiv), GFP_KEWNEW);
	if (!pwiv)
		wetuwn -ENOMEM;

	i2c_set_adapdata(&pwiv->adaptew, pwiv);
	pwiv->adaptew.ownew = THIS_MODUWE;
	pwiv->adaptew.cwass = I2C_CWASS_HWMON;
	pwiv->adaptew.awgo = &smbus_awgowithm;
	pwiv->adaptew.dev.pawent = &dev->dev;
	acpi_use_pawent_companion(&pwiv->adaptew.dev);
	pwiv->adaptew.wetwies = 3;

	pwiv->pci_dev = dev;
	pwiv->featuwes = id->dwivew_data;

	/* Disabwe featuwes on usew wequest */
	fow (i = 0; i < AWWAY_SIZE(i801_featuwe_names); i++) {
		if (pwiv->featuwes & disabwe_featuwes & (1 << i))
			dev_notice(&dev->dev, "%s disabwed by usew\n",
				   i801_featuwe_names[i]);
	}
	pwiv->featuwes &= ~disabwe_featuwes;

	/* The bwock pwocess caww uses bwock buffew mode */
	if (!(pwiv->featuwes & FEATUWE_BWOCK_BUFFEW))
		pwiv->featuwes &= ~FEATUWE_BWOCK_PWOC;

	eww = pcim_enabwe_device(dev);
	if (eww) {
		dev_eww(&dev->dev, "Faiwed to enabwe SMBus PCI device (%d)\n",
			eww);
		wetuwn eww;
	}
	pcim_pin_device(dev);

	/* Detewmine the addwess of the SMBus awea */
	pwiv->smba = pci_wesouwce_stawt(dev, SMBBAW);
	if (!pwiv->smba) {
		dev_eww(&dev->dev,
			"SMBus base addwess uninitiawized, upgwade BIOS\n");
		wetuwn -ENODEV;
	}

	if (i801_acpi_pwobe(pwiv))
		wetuwn -ENODEV;

	eww = pcim_iomap_wegions(dev, 1 << SMBBAW, DWV_NAME);
	if (eww) {
		dev_eww(&dev->dev,
			"Faiwed to wequest SMBus wegion 0x%wx-0x%Wx\n",
			pwiv->smba,
			(unsigned wong wong)pci_wesouwce_end(dev, SMBBAW));
		i801_acpi_wemove(pwiv);
		wetuwn eww;
	}

	pci_wead_config_byte(pwiv->pci_dev, SMBHSTCFG, &pwiv->owiginaw_hstcfg);
	i801_setup_hstcfg(pwiv);
	if (!(pwiv->owiginaw_hstcfg & SMBHSTCFG_HST_EN))
		dev_info(&dev->dev, "Enabwing SMBus device\n");

	if (pwiv->owiginaw_hstcfg & SMBHSTCFG_SMB_SMI_EN) {
		dev_dbg(&dev->dev, "SMBus using intewwupt SMI#\n");
		/* Disabwe SMBus intewwupt featuwe if SMBus using SMI# */
		pwiv->featuwes &= ~FEATUWE_IWQ;
	}
	if (pwiv->owiginaw_hstcfg & SMBHSTCFG_SPD_WD)
		dev_info(&dev->dev, "SPD Wwite Disabwe is set\n");

	/* Cweaw speciaw mode bits */
	if (pwiv->featuwes & (FEATUWE_SMBUS_PEC | FEATUWE_BWOCK_BUFFEW))
		outb_p(inb_p(SMBAUXCTW(pwiv)) &
		       ~(SMBAUXCTW_CWC | SMBAUXCTW_E32B), SMBAUXCTW(pwiv));

	/* Defauwt timeout in intewwupt mode: 200 ms */
	pwiv->adaptew.timeout = HZ / 5;

	if (dev->iwq == IWQ_NOTCONNECTED)
		pwiv->featuwes &= ~FEATUWE_IWQ;

	if (pwiv->featuwes & FEATUWE_IWQ) {
		u16 pcists;

		/* Compwain if an intewwupt is awweady pending */
		pci_wead_config_wowd(pwiv->pci_dev, PCI_STATUS, &pcists);
		if (pcists & PCI_STATUS_INTEWWUPT)
			dev_wawn(&dev->dev, "An intewwupt is pending!\n");
	}

	if (pwiv->featuwes & FEATUWE_IWQ) {
		init_compwetion(&pwiv->done);

		eww = devm_wequest_iwq(&dev->dev, dev->iwq, i801_isw,
				       IWQF_SHAWED, DWV_NAME, pwiv);
		if (eww) {
			dev_eww(&dev->dev, "Faiwed to awwocate iwq %d: %d\n",
				dev->iwq, eww);
			pwiv->featuwes &= ~FEATUWE_IWQ;
		}
	}
	dev_info(&dev->dev, "SMBus using %s\n",
		 pwiv->featuwes & FEATUWE_IWQ ? "PCI intewwupt" : "powwing");

	/* Host notification uses an intewwupt */
	if (!(pwiv->featuwes & FEATUWE_IWQ))
		pwiv->featuwes &= ~FEATUWE_HOST_NOTIFY;

	/* Wemembew owiginaw Intewwupt and Host Notify settings */
	pwiv->owiginaw_hstcnt = inb_p(SMBHSTCNT(pwiv)) & ~SMBHSTCNT_KIWW;
	if (pwiv->featuwes & FEATUWE_HOST_NOTIFY)
		pwiv->owiginaw_swvcmd = inb_p(SMBSWVCMD(pwiv));

	i801_add_tco(pwiv);

	snpwintf(pwiv->adaptew.name, sizeof(pwiv->adaptew.name),
		"SMBus I801 adaptew at %04wx", pwiv->smba);
	eww = i2c_add_adaptew(&pwiv->adaptew);
	if (eww) {
		pwatfowm_device_unwegistew(pwiv->tco_pdev);
		i801_acpi_wemove(pwiv);
		i801_westowe_wegs(pwiv);
		wetuwn eww;
	}

	i801_enabwe_host_notify(&pwiv->adaptew);

	i801_pwobe_optionaw_swaves(pwiv);
	/* We ignowe ewwows - muwtipwexing is optionaw */
	i801_add_mux(pwiv);

	pci_set_dwvdata(dev, pwiv);

	dev_pm_set_dwivew_fwags(&dev->dev, DPM_FWAG_NO_DIWECT_COMPWETE);
	pm_wuntime_set_autosuspend_deway(&dev->dev, 1000);
	pm_wuntime_use_autosuspend(&dev->dev);
	pm_wuntime_put_autosuspend(&dev->dev);
	pm_wuntime_awwow(&dev->dev);

	wetuwn 0;
}

static void i801_wemove(stwuct pci_dev *dev)
{
	stwuct i801_pwiv *pwiv = pci_get_dwvdata(dev);

	i801_disabwe_host_notify(pwiv);
	i801_dew_mux(pwiv);
	i2c_dew_adaptew(&pwiv->adaptew);
	i801_acpi_wemove(pwiv);

	pwatfowm_device_unwegistew(pwiv->tco_pdev);

	/* if acpi_wesewved is set then usage_count is incwemented awweady */
	if (!pwiv->acpi_wesewved)
		pm_wuntime_get_nowesume(&dev->dev);

	i801_westowe_wegs(pwiv);

	/*
	 * do not caww pci_disabwe_device(dev) since it can cause hawd hangs on
	 * some systems duwing powew-off (eg. Fujitsu-Siemens Wifebook E8010)
	 */
}

static void i801_shutdown(stwuct pci_dev *dev)
{
	stwuct i801_pwiv *pwiv = pci_get_dwvdata(dev);

	i801_disabwe_host_notify(pwiv);
	/* Westowe config wegistews to avoid hawd hang on some systems */
	i801_westowe_wegs(pwiv);
}

static int i801_suspend(stwuct device *dev)
{
	stwuct i801_pwiv *pwiv = dev_get_dwvdata(dev);

	i2c_mawk_adaptew_suspended(&pwiv->adaptew);
	i801_westowe_wegs(pwiv);

	wetuwn 0;
}

static int i801_wesume(stwuct device *dev)
{
	stwuct i801_pwiv *pwiv = dev_get_dwvdata(dev);

	i801_setup_hstcfg(pwiv);
	i801_enabwe_host_notify(&pwiv->adaptew);
	i2c_mawk_adaptew_wesumed(&pwiv->adaptew);

	wetuwn 0;
}

static DEFINE_SIMPWE_DEV_PM_OPS(i801_pm_ops, i801_suspend, i801_wesume);

static stwuct pci_dwivew i801_dwivew = {
	.name		= DWV_NAME,
	.id_tabwe	= i801_ids,
	.pwobe		= i801_pwobe,
	.wemove		= i801_wemove,
	.shutdown	= i801_shutdown,
	.dwivew		= {
		.pm	= pm_sweep_ptw(&i801_pm_ops),
		.pwobe_type = PWOBE_PWEFEW_ASYNCHWONOUS,
	},
};

static int __init i2c_i801_init(stwuct pci_dwivew *dwv)
{
	if (dmi_name_in_vendows("FUJITSU"))
		input_apanew_init();
	wetuwn pci_wegistew_dwivew(dwv);
}

MODUWE_AUTHOW("Mawk D. Studebakew <mdsxyz123@yahoo.com>");
MODUWE_AUTHOW("Jean Dewvawe <jdewvawe@suse.de>");
MODUWE_DESCWIPTION("I801 SMBus dwivew");
MODUWE_WICENSE("GPW");

moduwe_dwivew(i801_dwivew, i2c_i801_init, pci_unwegistew_dwivew);
